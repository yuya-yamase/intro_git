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

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU8[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU9[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU10[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x55U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU11[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU12[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU13[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU14[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU15[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU16[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xAEU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU17[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU18[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU19[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU20[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU21[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU22[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU23[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU24[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU25[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU26[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU27[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU28[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU29[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU30[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU31[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU32[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU33[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU34[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU35[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU36[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU37[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU38[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU39[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU40[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU41[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU42[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU43[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU44[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU45[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU46[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU47[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU48[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU49[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU50[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU51[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x28U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU52[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU53[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU54[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU55[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU56[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU57[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU58[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU59[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU60[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU61[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU62[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU63[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU64[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU65[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU66[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU67[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU68[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU69[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU70[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU71[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU72[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU73[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU74[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU75[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU76[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU77[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU78[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU79[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU80[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU81[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xA1U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU82[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU83[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU84[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU85[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU86[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU87[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xA2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU88[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU89[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU90[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU91[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU92[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU93[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xA3U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU94[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU95[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU96[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU97[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU98[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU99[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU100[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU101[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU102[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU103[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU104[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU105[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU106[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU107[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU108[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU109[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU110[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU111[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU112[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU113[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU114[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU115[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU116[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU117[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU118[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU119[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU120[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU121[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU122[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU123[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU124[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU125[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU126[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU127[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU128[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU129[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU130[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU131[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU132[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU133[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU134[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU135[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU136[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU137[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU138[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU139[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU140[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU141[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU142[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU143[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU144[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU145[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU146[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU147[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU148[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x22U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU149[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU150[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU151[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU152[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU153[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU154[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU155[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU156[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU157[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU158[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU159[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU160[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x44U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU161[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU162[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU163[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU164[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU165[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU166[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU167[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU168[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU169[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU170[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU171[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU172[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU173[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU174[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU175[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU176[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU177[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU178[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x22U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU179[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU180[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU181[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU182[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU183[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU184[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU185[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU186[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU187[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU188[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU189[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU190[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x44U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU191[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU192[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU193[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU194[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU195[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU196[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU197[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU198[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU199[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU200[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU201[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU202[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU203[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU204[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU205[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU206[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU207[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU208[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU209[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU210[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU211[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU212[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU213[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU214[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU215[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU216[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU217[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU218[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU219[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU220[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU221[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU222[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU223[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU224[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU225[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU226[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU227[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU228[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU229[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU230[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU231[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU232[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU233[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU234[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU235[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU236[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU237[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU238[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xD7U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU239[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU240[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU241[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU242[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU243[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU244[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU245[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU246[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU247[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU248[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU249[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU250[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xF2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU251[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU252[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU253[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU254[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU255[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU256[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU257[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU258[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU259[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU260[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU261[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU262[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU263[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU264[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU265[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU266[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU267[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU268[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU269[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU270[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU271[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU272[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU273[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU274[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x43U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU275[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU276[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU277[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU278[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU279[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x17U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU280[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU281[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU282[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU283[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU284[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU285[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU286[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xAFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU287[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU288[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU289[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU290[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU291[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x19U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU292[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU293[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU294[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU295[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU296[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU297[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU298[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x1BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU299[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU300[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU301[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU302[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU303[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU304[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU305[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU306[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU307[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU308[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU309[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU310[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x29U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU311[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU312[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU313[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU314[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU315[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU316[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU317[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU318[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU319[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU320[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU321[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU322[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU323[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU324[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU325[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU326[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU327[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU328[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x42U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU329[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU330[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU331[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU332[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU333[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU334[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU335[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU336[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU337[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU338[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU339[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x22U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU340[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x53U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU341[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU342[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU343[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU344[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU345[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x23U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU346[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE1U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU347[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU348[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU349[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU350[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU351[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x24U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU352[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x53U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU353[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU354[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU355[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU356[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU357[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU358[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU359[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU360[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU361[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU362[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU363[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x26U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU364[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x53U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU365[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU366[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU367[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU368[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU369[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x27U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU370[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE3U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU371[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU372[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU373[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU374[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU375[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x28U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU376[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU377[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU378[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU379[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU380[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU381[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x29U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU382[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE4U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU383[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU384[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU385[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU386[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU387[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU388[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU389[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU390[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU391[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU392[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU393[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU394[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE5U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU395[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU396[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU397[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU398[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU399[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU400[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU401[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU402[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU403[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU404[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU405[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x2DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU406[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU407[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU408[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU409[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU410[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU411[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU412[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU413[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU414[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU415[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU416[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU417[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x35U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU418[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU419[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU420[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU421[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU422[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU423[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU424[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU425[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU426[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU427[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU428[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU429[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU430[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU431[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU432[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU433[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU434[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU435[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x42U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU436[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU437[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU438[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU439[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU440[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU441[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x43U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU442[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU443[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU444[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU445[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU446[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU447[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x44U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU448[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU449[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU450[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU451[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU452[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU453[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x45U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU454[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU455[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU456[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU457[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU458[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU459[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x46U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU460[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU461[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU462[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU463[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU464[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU465[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x47U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU466[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU467[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU468[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU469[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU470[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU471[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU472[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU473[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU474[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU475[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU476[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU477[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x49U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU478[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU479[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU480[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU481[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU482[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU483[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU484[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x32U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU485[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU486[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU487[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU488[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU489[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x61U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU490[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU491[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU492[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU493[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU494[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU495[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x62U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU496[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU497[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU498[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU499[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU500[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU501[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x63U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU502[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU503[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU504[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU505[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU506[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU507[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x64U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU508[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xF0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU509[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU510[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU511[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU512[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU513[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x65U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU514[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU515[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU516[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU517[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU518[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU519[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x66U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU520[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xE0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU521[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU522[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU523[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU524[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU525[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x67U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU526[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU527[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU528[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU529[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU530[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU531[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x68U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU532[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xDAU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU533[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU534[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU535[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU536[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU537[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x69U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU538[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU539[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU540[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU541[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU542[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU543[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x6AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU544[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU545[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU546[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU547[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU548[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU549[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x6BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU550[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU551[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU552[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU553[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU554[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU555[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x6CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU556[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU557[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU558[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU559[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU560[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU561[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU562[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU563[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU564[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU565[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU566[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU567[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x70U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU568[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xA3U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU569[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU570[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU571[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU572[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU573[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x71U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU574[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU575[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU576[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU577[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU578[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU579[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x72U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU580[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x62U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU581[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU582[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU583[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU584[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU585[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x73U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU586[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU587[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU588[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU589[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU590[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU591[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x74U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU592[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU593[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU594[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU595[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU596[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU597[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x75U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU598[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU599[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU600[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU601[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU602[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU603[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x76U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU604[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU605[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU606[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU607[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU608[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU609[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x77U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU610[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU611[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU612[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU613[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU614[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU615[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU616[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x24U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU617[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU618[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU619[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU620[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU621[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x79U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU622[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU623[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU624[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU625[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU626[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU627[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU628[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU629[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU630[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU631[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU632[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU633[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU634[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU635[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU636[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU637[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU638[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU639[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC1U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU640[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU641[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU642[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU643[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU644[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU645[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU646[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU647[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU648[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU649[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU650[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU651[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC3U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU652[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU653[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU654[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU655[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU656[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU657[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU658[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU659[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU660[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU661[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU662[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU663[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xC9U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU664[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU665[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU666[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU667[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU668[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU669[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xCAU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU670[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU671[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU672[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU673[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU674[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU675[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xCBU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU676[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU677[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU678[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU679[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU680[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU681[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU682[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU683[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU684[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU685[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU686[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU687[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xF0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU688[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU689[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU690[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU8[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU9[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU10[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU11[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU12[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU13[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU14[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU15[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU16[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xC4U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU17[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU18[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU19[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU20[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU21[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU22[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x81U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU23[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU24[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU25[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU26[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU27[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU28[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU29[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU30[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU31[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU32[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU33[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU34[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU35[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU36[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU37[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU38[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU39[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU40[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU41[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU42[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU43[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU44[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU45[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU46[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU47[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU48[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU49[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU50[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU51[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU52[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU53[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU54[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU55[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU56[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU57[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU58[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xA4U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU59[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU60[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU61[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU62[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU63[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU64[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU65[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU66[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU67[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU68[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU69[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU70[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU71[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU72[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU73[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU74[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU75[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU76[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x2AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU77[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU78[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU79[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU80[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU81[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU82[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x76U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU83[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU84[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU85[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU86[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU87[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU88[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x2FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU89[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU90[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU91[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU92[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU93[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU94[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0xBCU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU95[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU96[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU97[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU98[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU99[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x17U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU100[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU101[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU102[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU103[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU104[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU105[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU106[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU107[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU108[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU109[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU110[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU111[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x19U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU112[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x3FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU113[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU114[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU115[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU116[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU117[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU118[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU119[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU120[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU121[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU122[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU123[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU124[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x54U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU125[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU126[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU127[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU128[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU129[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU130[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU131[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU132[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU133[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU134[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU135[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x1DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU136[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x69U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU137[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU138[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU139[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU140[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU141[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU142[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU143[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU144[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU145[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU146[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU147[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU148[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU149[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU150[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU151[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU152[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU153[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU154[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU155[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
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
    (U1)0x01U     /* Write Data */
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
    (U1)0x73U     /* Write Data */
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

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
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

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE6];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_ENCRYPT_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP9_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP2_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP10_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];


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
        (U4)0x30680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU2[0],
        (U4)0x306C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU3[0],
        (U4)0x30700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU4[0],
        (U4)0x30740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU5[0],
        (U4)0x30780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU6[0],
        (U4)0x307C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU7[0],
        (U4)0x30800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU8[0],
        (U4)0x30840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU9[0],
        (U4)0x30880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU10[0],
        (U4)0x308C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU11[0],
        (U4)0x30900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU12[0],
        (U4)0x30940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU13[0],
        (U4)0x30980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU14[0],
        (U4)0x309C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU15[0],
        (U4)0x30A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU16[0],
        (U4)0x30A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU17[0],
        (U4)0x30A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU18[0],
        (U4)0x30AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU19[0],
        (U4)0x30B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU20[0],
        (U4)0x30B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU21[0],
        (U4)0x30B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU22[0],
        (U4)0x30BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU23[0],
        (U4)0x30C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU24[0],
        (U4)0x30C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU25[0],
        (U4)0x30C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU26[0],
        (U4)0x30CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU27[0],
        (U4)0x30D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU28[0],
        (U4)0x30D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU29[0],
        (U4)0x30D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU30[0],
        (U4)0x30DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU31[0],
        (U4)0x30E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU32[0],
        (U4)0x30E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU33[0],
        (U4)0x30E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU34[0],
        (U4)0x30EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU35[0],
        (U4)0x30F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU36[0],
        (U4)0x30F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU37[0],
        (U4)0x30F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU38[0],
        (U4)0x30FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU39[0],
        (U4)0x31000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU40[0],
        (U4)0x31040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU41[0],
        (U4)0x31080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU42[0],
        (U4)0x310C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU43[0],
        (U4)0x31100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU44[0],
        (U4)0x31140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU45[0],
        (U4)0x31180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU46[0],
        (U4)0x311C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU47[0],
        (U4)0x31200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU48[0],
        (U4)0x31240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU49[0],
        (U4)0x31280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU50[0],
        (U4)0x312C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU51[0],
        (U4)0x31300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU52[0],
        (U4)0x31340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU53[0],
        (U4)0x31380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU54[0],
        (U4)0x313C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU55[0],
        (U4)0x31400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU56[0],
        (U4)0x31440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU57[0],
        (U4)0x31480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU58[0],
        (U4)0x314C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU59[0],
        (U4)0x31500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU60[0],
        (U4)0x31540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU61[0],
        (U4)0x31580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU62[0],
        (U4)0x315C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU63[0],
        (U4)0x31600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU64[0],
        (U4)0x31640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU65[0],
        (U4)0x31680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU66[0],
        (U4)0x316C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU67[0],
        (U4)0x31700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU68[0],
        (U4)0x31740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU69[0],
        (U4)0x31780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU70[0],
        (U4)0x317C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU71[0],
        (U4)0x31800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU72[0],
        (U4)0x31840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU73[0],
        (U4)0x31880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU74[0],
        (U4)0x318C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU75[0],
        (U4)0x31900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU76[0],
        (U4)0x31940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU77[0],
        (U4)0x31980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU78[0],
        (U4)0x319C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU79[0],
        (U4)0x31A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU80[0],
        (U4)0x31A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU81[0],
        (U4)0x31A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU82[0],
        (U4)0x31AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU83[0],
        (U4)0x31B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU84[0],
        (U4)0x31B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU85[0],
        (U4)0x31B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU86[0],
        (U4)0x31BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU87[0],
        (U4)0x31C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU88[0],
        (U4)0x31C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU89[0],
        (U4)0x31C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU90[0],
        (U4)0x31CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU91[0],
        (U4)0x31D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU92[0],
        (U4)0x31D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU93[0],
        (U4)0x31D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU94[0],
        (U4)0x31DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU95[0],
        (U4)0x31E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU96[0],
        (U4)0x31E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU97[0],
        (U4)0x31E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU98[0],
        (U4)0x31EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU99[0],
        (U4)0x31F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU100[0],
        (U4)0x31F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU101[0],
        (U4)0x31F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU102[0],
        (U4)0x31FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU103[0],
        (U4)0x32000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU104[0],
        (U4)0x32040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU105[0],
        (U4)0x32080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU106[0],
        (U4)0x320C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU107[0],
        (U4)0x32100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU108[0],
        (U4)0x32140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU109[0],
        (U4)0x32180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU110[0],
        (U4)0x321C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU111[0],
        (U4)0x32200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU112[0],
        (U4)0x32240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU113[0],
        (U4)0x32280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU114[0],
        (U4)0x322C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU115[0],
        (U4)0x32300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU116[0],
        (U4)0x32340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU117[0],
        (U4)0x32380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU118[0],
        (U4)0x323C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU119[0],
        (U4)0x32400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU120[0],
        (U4)0x32440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU121[0],
        (U4)0x32480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU122[0],
        (U4)0x324C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU123[0],
        (U4)0x32500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU124[0],
        (U4)0x32540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU125[0],
        (U4)0x32580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU126[0],
        (U4)0x325C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU127[0],
        (U4)0x32600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU128[0],
        (U4)0x32640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU129[0],
        (U4)0x32680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU130[0],
        (U4)0x326C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU131[0],
        (U4)0x32700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU132[0],
        (U4)0x32740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU133[0],
        (U4)0x32780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU134[0],
        (U4)0x327C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU135[0],
        (U4)0x32800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU136[0],
        (U4)0x32840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU137[0],
        (U4)0x32880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU138[0],
        (U4)0x328C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU139[0],
        (U4)0x32900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU140[0],
        (U4)0x32940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU141[0],
        (U4)0x32980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU142[0],
        (U4)0x329C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU143[0],
        (U4)0x32A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU144[0],
        (U4)0x32A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU145[0],
        (U4)0x32A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU146[0],
        (U4)0x32AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU147[0],
        (U4)0x32B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU148[0],
        (U4)0x32B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU149[0],
        (U4)0x32B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU150[0],
        (U4)0x32BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU151[0],
        (U4)0x32C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU152[0],
        (U4)0x32C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU153[0],
        (U4)0x32C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU154[0],
        (U4)0x32CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU155[0],
        (U4)0x32D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU156[0],
        (U4)0x32D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU157[0],
        (U4)0x32D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU158[0],
        (U4)0x32DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU159[0],
        (U4)0x32E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU160[0],
        (U4)0x32E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU161[0],
        (U4)0x32E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU162[0],
        (U4)0x32EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU163[0],
        (U4)0x32F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU164[0],
        (U4)0x32F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU165[0],
        (U4)0x32F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU166[0],
        (U4)0x32FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU167[0],
        (U4)0x33000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU168[0],
        (U4)0x33040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU169[0],
        (U4)0x33080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU170[0],
        (U4)0x330C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU171[0],
        (U4)0x33100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU172[0],
        (U4)0x33140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU173[0],
        (U4)0x33180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU174[0],
        (U4)0x331C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU175[0],
        (U4)0x33200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU176[0],
        (U4)0x33240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU177[0],
        (U4)0x33280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU178[0],
        (U4)0x332C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU179[0],
        (U4)0x33300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU180[0],
        (U4)0x33340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU181[0],
        (U4)0x33380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU182[0],
        (U4)0x333C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU183[0],
        (U4)0x33400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU184[0],
        (U4)0x33440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU185[0],
        (U4)0x33480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU186[0],
        (U4)0x334C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU187[0],
        (U4)0x33500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU188[0],
        (U4)0x33540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU189[0],
        (U4)0x33580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU190[0],
        (U4)0x335C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU191[0],
        (U4)0x33600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU192[0],
        (U4)0x33640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU193[0],
        (U4)0x33680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU194[0],
        (U4)0x336C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU195[0],
        (U4)0x33700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU196[0],
        (U4)0x33740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU197[0],
        (U4)0x33780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU198[0],
        (U4)0x337C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU199[0],
        (U4)0x33800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU200[0],
        (U4)0x33840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU201[0],
        (U4)0x33880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU202[0],
        (U4)0x338C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU203[0],
        (U4)0x33900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU204[0],
        (U4)0x33940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU205[0],
        (U4)0x33980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU206[0],
        (U4)0x339C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU207[0],
        (U4)0x33A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU208[0],
        (U4)0x33A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU209[0],
        (U4)0x33A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU210[0],
        (U4)0x33AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU211[0],
        (U4)0x33B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU212[0],
        (U4)0x33B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU213[0],
        (U4)0x33B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU214[0],
        (U4)0x33BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU215[0],
        (U4)0x33C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU216[0],
        (U4)0x33C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU217[0],
        (U4)0x33C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU218[0],
        (U4)0x33CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU219[0],
        (U4)0x33D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU220[0],
        (U4)0x33D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU221[0],
        (U4)0x33D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU222[0],
        (U4)0x33DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU223[0],
        (U4)0x33E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU224[0],
        (U4)0x33E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU225[0],
        (U4)0x33E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU226[0],
        (U4)0x33EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU227[0],
        (U4)0x33F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU228[0],
        (U4)0x33F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU229[0],
        (U4)0x33F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU230[0],
        (U4)0x33FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU231[0],
        (U4)0x34000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU232[0],
        (U4)0x34040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU233[0],
        (U4)0x34080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU234[0],
        (U4)0x340C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU235[0],
        (U4)0x34100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU236[0],
        (U4)0x34140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU237[0],
        (U4)0x34180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU238[0],
        (U4)0x341C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU239[0],
        (U4)0x34200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU240[0],
        (U4)0x34240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU241[0],
        (U4)0x34280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU242[0],
        (U4)0x342C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU243[0],
        (U4)0x34300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU244[0],
        (U4)0x34340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU245[0],
        (U4)0x34380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU246[0],
        (U4)0x343C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU247[0],
        (U4)0x34400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU248[0],
        (U4)0x34440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU249[0],
        (U4)0x34480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU250[0],
        (U4)0x344C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU251[0],
        (U4)0x34500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU252[0],
        (U4)0x34540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU253[0],
        (U4)0x34580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU254[0],
        (U4)0x345C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU255[0],
        (U4)0x34600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU256[0],
        (U4)0x34640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU257[0],
        (U4)0x34680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU258[0],
        (U4)0x346C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU259[0],
        (U4)0x34700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU260[0],
        (U4)0x34740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU261[0],
        (U4)0x34780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU262[0],
        (U4)0x347C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU263[0],
        (U4)0x34800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU264[0],
        (U4)0x34840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU265[0],
        (U4)0x34880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU266[0],
        (U4)0x348C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU267[0],
        (U4)0x34900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU268[0],
        (U4)0x34940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU269[0],
        (U4)0x34980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU270[0],
        (U4)0x349C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU271[0],
        (U4)0x34A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU272[0],
        (U4)0x34A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU273[0],
        (U4)0x34A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU274[0],
        (U4)0x34AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU275[0],
        (U4)0x34B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU276[0],
        (U4)0x34B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU277[0],
        (U4)0x34B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU278[0],
        (U4)0x34BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU279[0],
        (U4)0x34C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU280[0],
        (U4)0x34C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU281[0],
        (U4)0x34C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU282[0],
        (U4)0x34CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU283[0],
        (U4)0x34D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU284[0],
        (U4)0x34D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU285[0],
        (U4)0x34D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU286[0],
        (U4)0x34DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU287[0],
        (U4)0x34E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU288[0],
        (U4)0x34E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU289[0],
        (U4)0x34E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU290[0],
        (U4)0x34EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU291[0],
        (U4)0x34F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU292[0],
        (U4)0x34F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU293[0],
        (U4)0x34F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU294[0],
        (U4)0x34FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU295[0],
        (U4)0x35000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU296[0],
        (U4)0x35040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU297[0],
        (U4)0x35080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU298[0],
        (U4)0x350C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU299[0],
        (U4)0x35100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU300[0],
        (U4)0x35140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU301[0],
        (U4)0x35180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU302[0],
        (U4)0x351C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU303[0],
        (U4)0x35200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU304[0],
        (U4)0x35240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU305[0],
        (U4)0x35280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU306[0],
        (U4)0x352C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU307[0],
        (U4)0x35300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU308[0],
        (U4)0x35340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU309[0],
        (U4)0x35380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU310[0],
        (U4)0x353C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU311[0],
        (U4)0x35400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU312[0],
        (U4)0x35440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU313[0],
        (U4)0x35480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU314[0],
        (U4)0x354C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU315[0],
        (U4)0x35500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU316[0],
        (U4)0x35540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU317[0],
        (U4)0x35580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU318[0],
        (U4)0x355C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU319[0],
        (U4)0x35600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU320[0],
        (U4)0x35640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU321[0],
        (U4)0x35680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU322[0],
        (U4)0x356C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU323[0],
        (U4)0x35700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU324[0],
        (U4)0x35740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU325[0],
        (U4)0x35780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU326[0],
        (U4)0x357C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU327[0],
        (U4)0x35800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU328[0],
        (U4)0x35840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU329[0],
        (U4)0x35880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU330[0],
        (U4)0x358C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU331[0],
        (U4)0x35900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU332[0],
        (U4)0x35940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU333[0],
        (U4)0x35980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU334[0],
        (U4)0x359C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU335[0],
        (U4)0x35A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU336[0],
        (U4)0x35A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU337[0],
        (U4)0x35A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU338[0],
        (U4)0x35AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU339[0],
        (U4)0x35B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU340[0],
        (U4)0x35B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU341[0],
        (U4)0x35B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU342[0],
        (U4)0x35BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU343[0],
        (U4)0x35C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU344[0],
        (U4)0x35C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU345[0],
        (U4)0x35C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU346[0],
        (U4)0x35CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU347[0],
        (U4)0x35D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU348[0],
        (U4)0x35D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU349[0],
        (U4)0x35D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU350[0],
        (U4)0x35DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU351[0],
        (U4)0x35E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU352[0],
        (U4)0x35E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU353[0],
        (U4)0x35E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU354[0],
        (U4)0x35EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU355[0],
        (U4)0x35F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU356[0],
        (U4)0x35F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU357[0],
        (U4)0x35F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU358[0],
        (U4)0x35FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU359[0],
        (U4)0x36000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU360[0],
        (U4)0x36040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU361[0],
        (U4)0x36080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU362[0],
        (U4)0x360C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU363[0],
        (U4)0x36100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU364[0],
        (U4)0x36140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU365[0],
        (U4)0x36180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU366[0],
        (U4)0x361C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU367[0],
        (U4)0x36200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU368[0],
        (U4)0x36240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU369[0],
        (U4)0x36280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU370[0],
        (U4)0x362C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU371[0],
        (U4)0x36300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU372[0],
        (U4)0x36340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU373[0],
        (U4)0x36380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU374[0],
        (U4)0x363C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU375[0],
        (U4)0x36400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU376[0],
        (U4)0x36440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU377[0],
        (U4)0x36480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU378[0],
        (U4)0x364C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU379[0],
        (U4)0x36500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU380[0],
        (U4)0x36540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU381[0],
        (U4)0x36580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU382[0],
        (U4)0x365C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU383[0],
        (U4)0x36600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU384[0],
        (U4)0x36640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU385[0],
        (U4)0x36680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU386[0],
        (U4)0x366C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU387[0],
        (U4)0x36700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU388[0],
        (U4)0x36740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU389[0],
        (U4)0x36780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU390[0],
        (U4)0x367C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU391[0],
        (U4)0x36800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU392[0],
        (U4)0x36840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU393[0],
        (U4)0x36880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU394[0],
        (U4)0x368C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU395[0],
        (U4)0x36900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU396[0],
        (U4)0x36940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU397[0],
        (U4)0x36980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU398[0],
        (U4)0x369C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU399[0],
        (U4)0x36A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU400[0],
        (U4)0x36A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU401[0],
        (U4)0x36A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU402[0],
        (U4)0x36AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU403[0],
        (U4)0x36B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU404[0],
        (U4)0x36B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU405[0],
        (U4)0x36B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU406[0],
        (U4)0x36BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU407[0],
        (U4)0x36C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU408[0],
        (U4)0x36C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU409[0],
        (U4)0x36C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU410[0],
        (U4)0x36CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU411[0],
        (U4)0x36D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU412[0],
        (U4)0x36D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU413[0],
        (U4)0x36D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU414[0],
        (U4)0x36DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU415[0],
        (U4)0x36E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU416[0],
        (U4)0x36E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU417[0],
        (U4)0x36E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU418[0],
        (U4)0x36EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU419[0],
        (U4)0x36F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU420[0],
        (U4)0x36F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU421[0],
        (U4)0x36F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU422[0],
        (U4)0x36FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU423[0],
        (U4)0x37000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU424[0],
        (U4)0x37040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU425[0],
        (U4)0x37080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU426[0],
        (U4)0x370C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU427[0],
        (U4)0x37100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU428[0],
        (U4)0x37140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU429[0],
        (U4)0x37180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU430[0],
        (U4)0x371C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU431[0],
        (U4)0x37200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU432[0],
        (U4)0x37240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU433[0],
        (U4)0x37280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU434[0],
        (U4)0x372C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU435[0],
        (U4)0x37300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU436[0],
        (U4)0x37340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU437[0],
        (U4)0x37380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU438[0],
        (U4)0x373C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU439[0],
        (U4)0x37400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU440[0],
        (U4)0x37440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU441[0],
        (U4)0x37480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU442[0],
        (U4)0x374C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU443[0],
        (U4)0x37500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU444[0],
        (U4)0x37540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU445[0],
        (U4)0x37580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU446[0],
        (U4)0x375C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU447[0],
        (U4)0x37600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU448[0],
        (U4)0x37640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU449[0],
        (U4)0x37680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU450[0],
        (U4)0x376C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU451[0],
        (U4)0x37700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU452[0],
        (U4)0x37740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU453[0],
        (U4)0x37780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU454[0],
        (U4)0x377C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU455[0],
        (U4)0x37800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU456[0],
        (U4)0x37840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU457[0],
        (U4)0x37880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU458[0],
        (U4)0x378C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU459[0],
        (U4)0x37900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU460[0],
        (U4)0x37940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU461[0],
        (U4)0x37980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU462[0],
        (U4)0x379C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU463[0],
        (U4)0x37A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU464[0],
        (U4)0x37A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU465[0],
        (U4)0x37A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU466[0],
        (U4)0x37AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU467[0],
        (U4)0x37B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU468[0],
        (U4)0x37B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU469[0],
        (U4)0x37B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU470[0],
        (U4)0x37BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU471[0],
        (U4)0x37C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU472[0],
        (U4)0x37C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU473[0],
        (U4)0x37C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU474[0],
        (U4)0x37CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU475[0],
        (U4)0x37D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU476[0],
        (U4)0x37D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU477[0],
        (U4)0x37D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU478[0],
        (U4)0x37DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU479[0],
        (U4)0x37E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU480[0],
        (U4)0x37E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU481[0],
        (U4)0x37E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU482[0],
        (U4)0x37EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU483[0],
        (U4)0x37F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU484[0],
        (U4)0x37F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU485[0],
        (U4)0x37F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU486[0],
        (U4)0x37FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU487[0],
        (U4)0x38000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU488[0],
        (U4)0x38040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU489[0],
        (U4)0x38080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU490[0],
        (U4)0x380C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU491[0],
        (U4)0x38100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU492[0],
        (U4)0x38140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU493[0],
        (U4)0x38180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU494[0],
        (U4)0x381C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU495[0],
        (U4)0x38200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU496[0],
        (U4)0x38240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU497[0],
        (U4)0x38280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU498[0],
        (U4)0x382C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU499[0],
        (U4)0x38300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU500[0],
        (U4)0x38340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU501[0],
        (U4)0x38380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU502[0],
        (U4)0x383C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU503[0],
        (U4)0x38400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU504[0],
        (U4)0x38440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU505[0],
        (U4)0x38480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU506[0],
        (U4)0x384C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU507[0],
        (U4)0x38500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU508[0],
        (U4)0x38540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU509[0],
        (U4)0x38580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU510[0],
        (U4)0x385C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU511[0],
        (U4)0x38600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU512[0],
        (U4)0x38640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU513[0],
        (U4)0x38680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU514[0],
        (U4)0x386C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU515[0],
        (U4)0x38700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU516[0],
        (U4)0x38740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU517[0],
        (U4)0x38780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU518[0],
        (U4)0x387C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU519[0],
        (U4)0x38800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU520[0],
        (U4)0x38840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU521[0],
        (U4)0x38880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU522[0],
        (U4)0x388C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU523[0],
        (U4)0x38900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU524[0],
        (U4)0x38940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU525[0],
        (U4)0x38980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU526[0],
        (U4)0x389C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU527[0],
        (U4)0x38A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU528[0],
        (U4)0x38A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU529[0],
        (U4)0x38A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU530[0],
        (U4)0x38AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU531[0],
        (U4)0x38B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU532[0],
        (U4)0x38B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU533[0],
        (U4)0x38B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU534[0],
        (U4)0x38BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU535[0],
        (U4)0x38C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU536[0],
        (U4)0x38C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU537[0],
        (U4)0x38C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU538[0],
        (U4)0x38CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU539[0],
        (U4)0x38D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU540[0],
        (U4)0x38D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU541[0],
        (U4)0x38D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU542[0],
        (U4)0x38DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU543[0],
        (U4)0x38E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU544[0],
        (U4)0x38E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU545[0],
        (U4)0x38E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU546[0],
        (U4)0x38EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU547[0],
        (U4)0x38F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU548[0],
        (U4)0x38F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU549[0],
        (U4)0x38F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU550[0],
        (U4)0x38FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU551[0],
        (U4)0x39000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU552[0],
        (U4)0x39040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU553[0],
        (U4)0x39080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU554[0],
        (U4)0x390C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU555[0],
        (U4)0x39100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU556[0],
        (U4)0x39140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU557[0],
        (U4)0x39180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU558[0],
        (U4)0x391C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU559[0],
        (U4)0x39200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU560[0],
        (U4)0x39240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU561[0],
        (U4)0x39280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU562[0],
        (U4)0x392C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU563[0],
        (U4)0x39300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU564[0],
        (U4)0x39340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU565[0],
        (U4)0x39380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU566[0],
        (U4)0x393C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU567[0],
        (U4)0x39400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU568[0],
        (U4)0x39440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU569[0],
        (U4)0x39480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU570[0],
        (U4)0x394C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU571[0],
        (U4)0x39500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU572[0],
        (U4)0x39540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU573[0],
        (U4)0x39580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU574[0],
        (U4)0x395C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU575[0],
        (U4)0x39600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU576[0],
        (U4)0x39640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU577[0],
        (U4)0x39680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU578[0],
        (U4)0x396C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU579[0],
        (U4)0x39700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU580[0],
        (U4)0x39740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU581[0],
        (U4)0x39780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU582[0],
        (U4)0x397C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU583[0],
        (U4)0x39800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU584[0],
        (U4)0x39840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU585[0],
        (U4)0x39880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU586[0],
        (U4)0x398C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU587[0],
        (U4)0x39900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU588[0],
        (U4)0x39940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU589[0],
        (U4)0x39980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU590[0],
        (U4)0x399C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU591[0],
        (U4)0x39A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU592[0],
        (U4)0x39A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU593[0],
        (U4)0x39A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU594[0],
        (U4)0x39AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU595[0],
        (U4)0x39B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU596[0],
        (U4)0x39B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU597[0],
        (U4)0x39B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU598[0],
        (U4)0x39BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU599[0],
        (U4)0x39C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU600[0],
        (U4)0x39C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU601[0],
        (U4)0x39C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU602[0],
        (U4)0x39CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU603[0],
        (U4)0x39D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU604[0],
        (U4)0x39D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU605[0],
        (U4)0x39D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU606[0],
        (U4)0x39DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU607[0],
        (U4)0x39E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU608[0],
        (U4)0x39E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU609[0],
        (U4)0x39E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU610[0],
        (U4)0x39EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU611[0],
        (U4)0x39F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU612[0],
        (U4)0x39F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU613[0],
        (U4)0x39F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU614[0],
        (U4)0x39FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU615[0],
        (U4)0x3A000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU616[0],
        (U4)0x3A040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU617[0],
        (U4)0x3A080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU618[0],
        (U4)0x3A0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU619[0],
        (U4)0x3A100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU620[0],
        (U4)0x3A140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU621[0],
        (U4)0x3A180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU622[0],
        (U4)0x3A1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU623[0],
        (U4)0x3A200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU624[0],
        (U4)0x3A240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU625[0],
        (U4)0x3A280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU626[0],
        (U4)0x3A2C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU627[0],
        (U4)0x3A300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU628[0],
        (U4)0x3A340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU629[0],
        (U4)0x3A380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU630[0],
        (U4)0x3A3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU631[0],
        (U4)0x3A400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU632[0],
        (U4)0x3A440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU633[0],
        (U4)0x3A480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU634[0],
        (U4)0x3A4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU635[0],
        (U4)0x3A500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU636[0],
        (U4)0x3A540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU637[0],
        (U4)0x3A580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU638[0],
        (U4)0x3A5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU639[0],
        (U4)0x3A600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU640[0],
        (U4)0x3A640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU641[0],
        (U4)0x3A680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU642[0],
        (U4)0x3A6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU643[0],
        (U4)0x3A700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU644[0],
        (U4)0x3A740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU645[0],
        (U4)0x3A780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU646[0],
        (U4)0x3A7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU647[0],
        (U4)0x3A800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU648[0],
        (U4)0x3A840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU649[0],
        (U4)0x3A880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU650[0],
        (U4)0x3A8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU651[0],
        (U4)0x3A900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU652[0],
        (U4)0x3A940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU653[0],
        (U4)0x3A980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU654[0],
        (U4)0x3A9C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU655[0],
        (U4)0x3AA00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU656[0],
        (U4)0x3AA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU657[0],
        (U4)0x3AA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU658[0],
        (U4)0x3AAC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU659[0],
        (U4)0x3AB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU660[0],
        (U4)0x3AB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU661[0],
        (U4)0x3AB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU662[0],
        (U4)0x3ABC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU663[0],
        (U4)0x3AC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU664[0],
        (U4)0x3AC40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU665[0],
        (U4)0x3AC80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU666[0],
        (U4)0x3ACC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU667[0],
        (U4)0x3AD00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU668[0],
        (U4)0x3AD40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU669[0],
        (U4)0x3AD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU670[0],
        (U4)0x3ADC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU671[0],
        (U4)0x3AE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU672[0],
        (U4)0x3AE40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU673[0],
        (U4)0x3AE80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU674[0],
        (U4)0x3AEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU675[0],
        (U4)0x3AF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU676[0],
        (U4)0x3AF40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU677[0],
        (U4)0x3AF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU678[0],
        (U4)0x3AFC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU679[0],
        (U4)0x3B000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU680[0],
        (U4)0x3B040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU681[0],
        (U4)0x3B080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU682[0],
        (U4)0x3B0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU683[0],
        (U4)0x3B100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU684[0],
        (U4)0x3B140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU685[0],
        (U4)0x3B180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU686[0],
        (U4)0x3B1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU687[0],
        (U4)0x3B200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU688[0],
        (U4)0x3B240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU689[0],
        (U4)0x3B280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU690[0],
        (U4)0x3B2C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD[MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU1[0],
        (U4)0x3B300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU2[0],
        (U4)0x3B340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU3[0],
        (U4)0x3B380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU4[0],
        (U4)0x3B3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU5[0],
        (U4)0x3B400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU6[0],
        (U4)0x3B440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU7[0],
        (U4)0x3B480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU8[0],
        (U4)0x3B4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU9[0],
        (U4)0x3B500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU10[0],
        (U4)0x3B540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU11[0],
        (U4)0x3B580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU12[0],
        (U4)0x3B5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU13[0],
        (U4)0x3B600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU14[0],
        (U4)0x3B640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU15[0],
        (U4)0x3B680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU16[0],
        (U4)0x3B6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU17[0],
        (U4)0x3B700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU18[0],
        (U4)0x3B740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU19[0],
        (U4)0x3B780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU20[0],
        (U4)0x3B7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU21[0],
        (U4)0x3B800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU22[0],
        (U4)0x3B840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU23[0],
        (U4)0x3B880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU24[0],
        (U4)0x3B8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU25[0],
        (U4)0x3B900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU26[0],
        (U4)0x3B940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU27[0],
        (U4)0x3B980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU28[0],
        (U4)0x3B9C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU29[0],
        (U4)0x3BA00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU30[0],
        (U4)0x3BA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU31[0],
        (U4)0x3BA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU32[0],
        (U4)0x3BAC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU33[0],
        (U4)0x3BB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU34[0],
        (U4)0x3BB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU35[0],
        (U4)0x3BB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU36[0],
        (U4)0x3BBC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU37[0],
        (U4)0x3BC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU38[0],
        (U4)0x3BC40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU39[0],
        (U4)0x3BC80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU40[0],
        (U4)0x3BCC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU41[0],
        (U4)0x3BD00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU42[0],
        (U4)0x3BD40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU43[0],
        (U4)0x3BD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU44[0],
        (U4)0x3BDC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU45[0],
        (U4)0x3BE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU46[0],
        (U4)0x3BE40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU47[0],
        (U4)0x3BE80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU48[0],
        (U4)0x3BEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU49[0],
        (U4)0x3BF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU50[0],
        (U4)0x3BF40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU51[0],
        (U4)0x3BF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU52[0],
        (U4)0x3BFC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU53[0],
        (U4)0x3C000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU54[0],
        (U4)0x3C040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU55[0],
        (U4)0x3C080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU56[0],
        (U4)0x3C0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU57[0],
        (U4)0x3C100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU58[0],
        (U4)0x3C140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU59[0],
        (U4)0x3C180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU60[0],
        (U4)0x3C1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU61[0],
        (U4)0x3C200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU62[0],
        (U4)0x3C240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU63[0],
        (U4)0x3C280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU64[0],
        (U4)0x3C2C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU65[0],
        (U4)0x3C300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU66[0],
        (U4)0x3C340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU67[0],
        (U4)0x3C380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU68[0],
        (U4)0x3C3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU69[0],
        (U4)0x3C400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU70[0],
        (U4)0x3C440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU71[0],
        (U4)0x3C480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU72[0],
        (U4)0x3C4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU73[0],
        (U4)0x3C500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU74[0],
        (U4)0x3C540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU75[0],
        (U4)0x3C580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU76[0],
        (U4)0x3C5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU77[0],
        (U4)0x3C600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU78[0],
        (U4)0x3C640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU79[0],
        (U4)0x3C680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU80[0],
        (U4)0x3C6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU81[0],
        (U4)0x3C700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU82[0],
        (U4)0x3C740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU83[0],
        (U4)0x3C780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU84[0],
        (U4)0x3C7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU85[0],
        (U4)0x3C800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU86[0],
        (U4)0x3C840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU87[0],
        (U4)0x3C880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU88[0],
        (U4)0x3C8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU89[0],
        (U4)0x3C900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU90[0],
        (U4)0x3C940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU91[0],
        (U4)0x3C980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU92[0],
        (U4)0x3C9C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU93[0],
        (U4)0x3CA00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU94[0],
        (U4)0x3CA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU95[0],
        (U4)0x3CA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU96[0],
        (U4)0x3CAC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU97[0],
        (U4)0x3CB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU98[0],
        (U4)0x3CB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU99[0],
        (U4)0x3CB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU100[0],
        (U4)0x3CBC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU101[0],
        (U4)0x3CC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU102[0],
        (U4)0x3CC40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU103[0],
        (U4)0x3CC80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU104[0],
        (U4)0x3CCC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU105[0],
        (U4)0x3CD00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU106[0],
        (U4)0x3CD40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU107[0],
        (U4)0x3CD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU108[0],
        (U4)0x3CDC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU109[0],
        (U4)0x3CE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU110[0],
        (U4)0x3CE40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU111[0],
        (U4)0x3CE80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU112[0],
        (U4)0x3CEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU113[0],
        (U4)0x3CF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU114[0],
        (U4)0x3CF40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU115[0],
        (U4)0x3CF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU116[0],
        (U4)0x3CFC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU117[0],
        (U4)0x3D000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU118[0],
        (U4)0x3D040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU119[0],
        (U4)0x3D080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU120[0],
        (U4)0x3D0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU121[0],
        (U4)0x3D100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU122[0],
        (U4)0x3D140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU123[0],
        (U4)0x3D180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU124[0],
        (U4)0x3D1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU125[0],
        (U4)0x3D200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU126[0],
        (U4)0x3D240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU127[0],
        (U4)0x3D280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU128[0],
        (U4)0x3D2C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU129[0],
        (U4)0x3D300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU130[0],
        (U4)0x3D340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU131[0],
        (U4)0x3D380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU132[0],
        (U4)0x3D3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU133[0],
        (U4)0x3D400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU134[0],
        (U4)0x3D440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU135[0],
        (U4)0x3D480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU136[0],
        (U4)0x3D4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU137[0],
        (U4)0x3D500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU138[0],
        (U4)0x3D540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU139[0],
        (U4)0x3D580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU140[0],
        (U4)0x3D5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU141[0],
        (U4)0x3D600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU142[0],
        (U4)0x3D640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU143[0],
        (U4)0x3D680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU144[0],
        (U4)0x3D6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU145[0],
        (U4)0x3D700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU146[0],
        (U4)0x3D740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU147[0],
        (U4)0x3D780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU148[0],
        (U4)0x3D7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU149[0],
        (U4)0x3D800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU150[0],
        (U4)0x3D840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU151[0],
        (U4)0x3D880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU152[0],
        (U4)0x3D8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU153[0],
        (U4)0x3D900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU154[0],
        (U4)0x3D940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU155[0],
        (U4)0x3D980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU156[0],
        (U4)0x3D9C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2[MCU_SYS_PWR_GVIFSNDR_EDPSET2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2_PDU1[0],
        (U4)0x3DA00003U
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
        (U4)0x3DC80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1[MCU_SYS_PWR_GVIFSNDR_OUTSET1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1_PDU1[0],
        (U4)0x3DCC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU1[0],
        (U4)0x3DD00002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[0],
        (U4)0x3DD40002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2[MCU_SYS_PWR_GVIFSNDR_OUTSET2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU1[0],
        (U4)0x3DD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU2[0],
        (U4)0x3DDC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU3[0],
        (U4)0x3DE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU4[0],
        (U4)0x3DE40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU5[0],
        (U4)0x3DE80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1[MCU_SYS_PWR_GVIFSNDR_HDCP1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU1[0],
        (U4)0x3DEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU2[0],
        (U4)0x3DF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU3[0],
        (U4)0x3DF40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU4[0],
        (U4)0x3DF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU5[0],
        (U4)0x3DFC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2[MCU_SYS_PWR_GVIFSNDR_HDCP2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2_PDU1[0],
        (U4)0x3E000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3[MCU_SYS_PWR_GVIFSNDR_HDCP3_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3_PDU1[0],
        (U4)0x3E040003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4[MCU_SYS_PWR_GVIFSNDR_HDCP4_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU1[0],
        (U4)0x3E080003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5[MCU_SYS_PWR_GVIFSNDR_HDCP5_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5_PDU1[0],
        (U4)0x3E0C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6[MCU_SYS_PWR_GVIFSNDR_HDCP6_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6_PDU1[0],
        (U4)0x3E100003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU1[0],
        (U4)0x3E140002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0],
        (U4)0x3E180002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU1[0],
        (U4)0x3E1C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0],
        (U4)0x3E200002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7[MCU_SYS_PWR_GVIFSNDR_HDCP7_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU1[0],
        (U4)0x3E240003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU1[0],
        (U4)0x3E280002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU2[0],
        (U4)0x3E2C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU1[0],
        (U4)0x3E300002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU2[0],
        (U4)0x3E340002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0],
        (U4)0x3E380002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0],
        (U4)0x3E3C0006U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_ENCRYPT[MCU_SYS_PWR_GVIFSNDR_ENCRYPT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_ENCRYPT_PDU1[0],
        (U4)0x3E600003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8[MCU_SYS_PWR_GVIFSNDR_HDCP8_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8_PDU1[0],
        (U4)0x3E600003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU1[0],
        (U4)0x3E640002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[0],
        (U4)0x3E680002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP9[MCU_SYS_PWR_GVIFSNDR_HDCP9_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP9_PDU1[0],
        (U4)0x3E6C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1[MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1_PDU1[0],
        (U4)0x3E700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP1_PDU2[0],
        (U4)0x3E740003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP2[MCU_SYS_PWR_GVIFSNDR_HDCPSTOP2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP2_PDU1[0],
        (U4)0x3E780003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP10[MCU_SYS_PWR_GVIFSNDR_HDCP10_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP10_PDU1[0],
        (U4)0x3E7C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD[MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[0],
        (U4)0x3E800002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[0],
        (U4)0x3E840002U
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
    u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[1] = (U1)0xFFU;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_DEVS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_MAX_CASCADE_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* Receiver ID取得 5Byte Read 書込み用テーブル(Write Address可変)初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[1] = (U1)0x50U;    /* Write Address初期値(定期処理内で更新) */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (uint32)1U; mcu_cnt < (uint32)6U; mcu_cnt++) {
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
