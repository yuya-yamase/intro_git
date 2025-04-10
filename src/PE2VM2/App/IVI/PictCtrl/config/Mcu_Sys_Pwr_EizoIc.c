/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_Sys_Pwr_EizoIc.h"
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
const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU1[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU2[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU3[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x99U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU4[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0xC0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU5[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU6[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0xA3U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU7[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU8[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU9[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x55U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU10[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU11[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU12[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x87U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU13[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x88U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU14[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU15[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x90U,    /* Write Address */
    (U1)0x23U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU16[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x91U,    /* Write Address */
    (U1)0x3FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU17[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x93U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU18[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x94U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU19[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x95U,    /* Write Address */
    (U1)0x0BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU20[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x96U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU21[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU22[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x98U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU23[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x99U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU24[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9AU,    /* Write Address */
    (U1)0x0BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU25[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9BU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU26[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU27[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9DU,    /* Write Address */
    (U1)0x19U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU28[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x90U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU29[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xAAU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU30[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xAEU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU31[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xAFU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU32[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB0U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU33[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU34[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU35[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU36[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x0EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU37[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU38[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU39[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU40[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU41[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU42[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU43[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x86U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU44[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU45[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0xC5U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU46[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU47[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU48[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU49[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU50[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU51[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU52[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU53[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU54[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU55[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU56[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU57[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU58[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU59[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU60[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU61[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU62[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU63[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU64[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2DU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU65[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x50U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU66[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU67[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x3FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU68[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x2AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU69[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x8FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU70[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0x77U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU71[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU72[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU73[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU74[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD8U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU75[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD9U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU76[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDAU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU77[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDBU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU78[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDCU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU79[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDDU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU80[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDEU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU81[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDFU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU82[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU83[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU84[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU85[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU86[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU87[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU88[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU89[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU90[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU91[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU92[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU93[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU94[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU95[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU96[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU97[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU,    /* Write Address */
    (U1)0xA2U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU98[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU99[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU100[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU101[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU102[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x55U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU103[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU104[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU105[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU106[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU107[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU108[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU109[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU110[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU111[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x85U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU112[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU113[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x87U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU114[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x88U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU115[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU116[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8AU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU117[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU118[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU119[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU120[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU121[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU122[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x90U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU123[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x91U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU124[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x92U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU125[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x93U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU126[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x94U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU127[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x95U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU128[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x96U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU129[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU130[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x98U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU131[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x99U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU132[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9AU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU133[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9BU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU134[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU135[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA8U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU136[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU137[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xAAU,    /* Write Address */
    (U1)0x6EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU138[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xABU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU139[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xBDU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU140[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xBEU,    /* Write Address */
    (U1)0x3FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU141[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC4U,    /* Write Address */
    (U1)0x61U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU142[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU143[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU144[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x4FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU145[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU146[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU147[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU148[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU149[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU150[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x28U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU151[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU152[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0xA4U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU153[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU154[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x46U,    /* Write Address */
    (U1)0x64U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU155[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU156[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x48U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU157[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU158[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU159[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU160[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU161[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU162[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU163[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU164[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU165[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU166[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU167[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU168[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU169[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x92U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU170[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU171[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0xFCU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU172[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU173[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x84U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU174[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU175[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU176[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU177[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU178[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU179[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU180[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU181[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU182[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU183[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU184[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x24U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU185[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU186[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU187[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU188[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2DU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU189[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU190[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU191[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU192[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x31U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU193[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x32U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU194[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x33U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU195[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x70U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU196[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU197[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU198[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU199[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU200[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU201[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU202[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU203[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU204[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU205[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x8CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU206[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU207[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x26U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU208[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU209[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU210[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU211[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU212[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU213[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x24U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU214[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU215[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU216[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU217[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x1AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU218[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU219[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU220[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU221[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU222[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0xC9U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU223[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU224[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x57U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU225[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x47U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU226[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x98U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU227[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x27U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU228[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU229[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU230[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x4CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU231[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU232[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU233[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU234[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU235[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU236[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU237[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU238[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU239[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU240[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU241[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2DU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU242[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU243[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU244[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU245[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x31U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU246[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x32U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU247[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x33U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU248[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x34U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU249[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x35U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU250[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x36U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU251[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x5EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU252[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU253[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU254[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU255[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU256[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x26U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU257[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU258[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU259[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3FU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU260[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x45U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU261[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU262[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU263[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU264[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U,    /* Write Address */
    (U1)0x42U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU265[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU266[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x46U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU267[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU268[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x48U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU269[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU270[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU271[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU272[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU273[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU274[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU275[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU276[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x50U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU277[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x51U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU278[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x52U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU279[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x53U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU280[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU281[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x55U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU282[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x56U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU283[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU284[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU285[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU286[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU287[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU288[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU289[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5DU,    /* Write Address */
    (U1)0xFCU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU290[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU291[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU,    /* Write Address */
    (U1)0x43U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU292[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x61U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU293[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x72U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU294[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU295[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU296[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x75U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU297[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x64U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU298[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x69U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU299[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU300[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU301[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU302[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU303[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU304[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU305[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU306[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU307[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0xFDU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU308[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU309[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x3BU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU310[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x3DU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU311[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU312[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x2EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU313[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU314[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU315[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU316[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU317[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU318[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU319[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU320[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU321[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU322[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU323[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU324[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU325[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU326[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU327[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU328[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU329[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x45U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU330[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU331[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU332[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU333[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU334[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU335[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x23U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU336[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU337[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU338[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU339[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU340[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU341[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU342[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU343[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x65U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU344[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU345[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU346[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU347[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU348[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU349[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU350[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU351[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU352[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU353[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU354[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU355[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU356[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU357[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU358[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU359[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU360[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU361[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU362[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU363[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU364[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU365[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU366[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU367[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU368[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU369[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU370[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU371[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU372[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU373[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU374[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x31U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU375[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x32U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU376[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x33U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU377[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x34U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU378[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x35U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU379[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x36U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU380[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU381[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU382[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU383[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU384[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU385[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU386[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU387[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU388[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU389[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU390[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU391[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU392[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU393[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU394[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU395[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x46U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU396[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU397[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x48U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU398[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU399[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU400[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU401[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU402[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU403[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU404[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x4FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU405[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x50U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU406[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x51U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU407[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x52U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU408[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x53U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU409[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x54U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU410[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x55U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU411[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x56U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU412[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x57U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU413[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU414[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x59U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU415[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU416[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU417[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU418[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU419[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU420[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU421[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU422[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU423[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU424[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU425[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU426[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU427[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU428[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU429[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU430[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU431[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU432[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU433[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU434[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU435[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU436[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU437[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU438[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU439[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU440[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU441[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU442[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU443[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU444[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU445[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU446[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU447[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU448[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU449[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU450[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU451[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU452[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x64U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU453[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU454[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x59U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU455[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU456[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU457[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU458[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU472[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU473[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU474[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU475[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU476[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU477[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU459[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU460[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU461[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU462[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU463[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU464[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU465[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU466[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU467[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x32U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU468[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x46U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU469[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU470[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x48U,    /* Write Address */
    (U1)0x64U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU471[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU1[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU2[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU3[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU4[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU1[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU2[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU3[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU4[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU5[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU6[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x37U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU7[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU8[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU9[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU10[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU11[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU12[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU13[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU14[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU15[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU16[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU17[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU18[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU19[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU20[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU21[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU22[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU23[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU24[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU25[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU26[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU27[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU28[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU29[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU30[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU31[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU32[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU33[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU34[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU35[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU36[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU37[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU38[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU39[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU40[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU41[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU42[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU43[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU44[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU45[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU46[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU47[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU48[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU49[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU50[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU51[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU52[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU53[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU54[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU55[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU56[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU57[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU58[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU59[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU60[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU61[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU62[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU63[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU64[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU65[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU66[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU67[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU68[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU69[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU70[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU71[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU72[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU73[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU74[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU75[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU76[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU77[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU78[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU79[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU80[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU81[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU82[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU83[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU84[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU85[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU86[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU87[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU88[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU89[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU90[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU91[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU92[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU93[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU94[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU95[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU96[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU97[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU98[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU99[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU100[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU101[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU102[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU103[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU104[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU105[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU106[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU107[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU108[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU109[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU110[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU111[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU112[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU113[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU114[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU115[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU116[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU117[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU118[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU119[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU120[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU121[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU122[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU123[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU124[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU125[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU126[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU127[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU128[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU129[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU130[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU131[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU132[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU133[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU134[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU135[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU136[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU137[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU138[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU139[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU140[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU141[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU142[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU143[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU1[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU2[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU3[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU4[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU5[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU6[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU7[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU8[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU9[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU10[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU11[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU12[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU13[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU14[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU15[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU16[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU17[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU18[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU19[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU20[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU21[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU22[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU23[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU24[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU25[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU26[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU27[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU28[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU29[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU30[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU31[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU32[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU33[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU34[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU35[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU36[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU37[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU38[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU39[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU40[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU41[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU42[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU43[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU44[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU45[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU46[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU47[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU48[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU49[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU50[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU51[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU52[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU53[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU54[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU55[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU56[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU57[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU58[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU59[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU60[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU61[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU62[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU63[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU64[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU65[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU66[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU67[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU68[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU69[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU70[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU71[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU72[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU73[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU74[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU75[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU76[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU77[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU78[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU79[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU80[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU81[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU82[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU83[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU84[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU85[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU86[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU87[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU88[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU89[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU90[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU91[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU92[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU93[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU94[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU95[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU96[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU97[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU98[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU99[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU100[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU101[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU102[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU103[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU104[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU105[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU106[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU107[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU108[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU109[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU110[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU111[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU112[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU113[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU114[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU115[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU116[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU117[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU118[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU119[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU120[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU121[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU122[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU123[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU124[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU125[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU126[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU127[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU128[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU129[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU130[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU131[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU132[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU133[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU134[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU135[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU136[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU137[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU138[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU139[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU140[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU141[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU142[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU143[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU1[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU2[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU3[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU4[MCU_SYS_PWR_EIZOIC_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_EIZOIC_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x92U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT[MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU1[0],
        (U4)0x10040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU2[0],
        (U4)0x10080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU3[0],
        (U4)0x100C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU4[0],
        (U4)0x10100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU5[0],
        (U4)0x10140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU6[0],
        (U4)0x10180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU7[0],
        (U4)0x101C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU8[0],
        (U4)0x10200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU9[0],
        (U4)0x10240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU10[0],
        (U4)0x10280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU11[0],
        (U4)0x102C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU12[0],
        (U4)0x10300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU13[0],
        (U4)0x10340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU14[0],
        (U4)0x10380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU15[0],
        (U4)0x103C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU16[0],
        (U4)0x10400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU17[0],
        (U4)0x10440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU18[0],
        (U4)0x10480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU19[0],
        (U4)0x104C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU20[0],
        (U4)0x10500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU21[0],
        (U4)0x10540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU22[0],
        (U4)0x10580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU23[0],
        (U4)0x105C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU24[0],
        (U4)0x10600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU25[0],
        (U4)0x10640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU26[0],
        (U4)0x10680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU27[0],
        (U4)0x106C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU28[0],
        (U4)0x10700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU29[0],
        (U4)0x10740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU30[0],
        (U4)0x10780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU31[0],
        (U4)0x107C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU32[0],
        (U4)0x10800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU33[0],
        (U4)0x10840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU34[0],
        (U4)0x10880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU35[0],
        (U4)0x108C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU36[0],
        (U4)0x10900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU37[0],
        (U4)0x10940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU38[0],
        (U4)0x10980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU39[0],
        (U4)0x109C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU40[0],
        (U4)0x10A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU41[0],
        (U4)0x10A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU42[0],
        (U4)0x10A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU43[0],
        (U4)0x10AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU44[0],
        (U4)0x10B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU45[0],
        (U4)0x10B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU46[0],
        (U4)0x10B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU47[0],
        (U4)0x10BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU48[0],
        (U4)0x10C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU49[0],
        (U4)0x10C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU50[0],
        (U4)0x10C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU51[0],
        (U4)0x10CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU52[0],
        (U4)0x10D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU53[0],
        (U4)0x10D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU54[0],
        (U4)0x10D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU55[0],
        (U4)0x10DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU56[0],
        (U4)0x10E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU57[0],
        (U4)0x10E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU58[0],
        (U4)0x10E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU59[0],
        (U4)0x10EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU60[0],
        (U4)0x10F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU61[0],
        (U4)0x10F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU62[0],
        (U4)0x10F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU63[0],
        (U4)0x10FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU64[0],
        (U4)0x11000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU65[0],
        (U4)0x11040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU66[0],
        (U4)0x11080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU67[0],
        (U4)0x110C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU68[0],
        (U4)0x11100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU69[0],
        (U4)0x11140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU70[0],
        (U4)0x11180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU71[0],
        (U4)0x111C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU72[0],
        (U4)0x11200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU73[0],
        (U4)0x11240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU74[0],
        (U4)0x11280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU75[0],
        (U4)0x112C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU76[0],
        (U4)0x11300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU77[0],
        (U4)0x11340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU78[0],
        (U4)0x11380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU79[0],
        (U4)0x113C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU80[0],
        (U4)0x11400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU81[0],
        (U4)0x11440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU82[0],
        (U4)0x11480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU83[0],
        (U4)0x114C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU84[0],
        (U4)0x11500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU85[0],
        (U4)0x11540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU86[0],
        (U4)0x11580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU87[0],
        (U4)0x115C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU88[0],
        (U4)0x11600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU89[0],
        (U4)0x11640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU90[0],
        (U4)0x11680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU91[0],
        (U4)0x116C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU92[0],
        (U4)0x11700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU93[0],
        (U4)0x11740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU94[0],
        (U4)0x11780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU95[0],
        (U4)0x117C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU96[0],
        (U4)0x11800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU97[0],
        (U4)0x11840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU98[0],
        (U4)0x11880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU99[0],
        (U4)0x118C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU100[0],
        (U4)0x11900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU101[0],
        (U4)0x11940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU102[0],
        (U4)0x11980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU103[0],
        (U4)0x119C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU104[0],
        (U4)0x11A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU105[0],
        (U4)0x11A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU106[0],
        (U4)0x11A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU107[0],
        (U4)0x11AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU108[0],
        (U4)0x11B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU109[0],
        (U4)0x11B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU110[0],
        (U4)0x11B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU111[0],
        (U4)0x11BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU112[0],
        (U4)0x11C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU113[0],
        (U4)0x11C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU114[0],
        (U4)0x11C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU115[0],
        (U4)0x11CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU116[0],
        (U4)0x11D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU117[0],
        (U4)0x11D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU118[0],
        (U4)0x11D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU119[0],
        (U4)0x11DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU120[0],
        (U4)0x11E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU121[0],
        (U4)0x11E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU122[0],
        (U4)0x11E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU123[0],
        (U4)0x11EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU124[0],
        (U4)0x11F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU125[0],
        (U4)0x11F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU126[0],
        (U4)0x11F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU127[0],
        (U4)0x11FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU128[0],
        (U4)0x12000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU129[0],
        (U4)0x12040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU130[0],
        (U4)0x12080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU131[0],
        (U4)0x120C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU132[0],
        (U4)0x12100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU133[0],
        (U4)0x12140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU134[0],
        (U4)0x12180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU135[0],
        (U4)0x121C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU136[0],
        (U4)0x12200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU137[0],
        (U4)0x12240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU138[0],
        (U4)0x12280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU139[0],
        (U4)0x122C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU140[0],
        (U4)0x12300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU141[0],
        (U4)0x12340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU142[0],
        (U4)0x12380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU143[0],
        (U4)0x123C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU144[0],
        (U4)0x12400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU145[0],
        (U4)0x12440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU146[0],
        (U4)0x12480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU147[0],
        (U4)0x124C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU148[0],
        (U4)0x12500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU149[0],
        (U4)0x12540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU150[0],
        (U4)0x12580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU151[0],
        (U4)0x125C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU152[0],
        (U4)0x12600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU153[0],
        (U4)0x12640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU154[0],
        (U4)0x12680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU155[0],
        (U4)0x126C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU156[0],
        (U4)0x12700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU157[0],
        (U4)0x12740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU158[0],
        (U4)0x12780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU159[0],
        (U4)0x127C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU160[0],
        (U4)0x12800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU161[0],
        (U4)0x12840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU162[0],
        (U4)0x12880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU163[0],
        (U4)0x128C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU164[0],
        (U4)0x12900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU165[0],
        (U4)0x12940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU166[0],
        (U4)0x12980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU167[0],
        (U4)0x129C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU168[0],
        (U4)0x12A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU169[0],
        (U4)0x12A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU170[0],
        (U4)0x12A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU171[0],
        (U4)0x12AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU172[0],
        (U4)0x12B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU173[0],
        (U4)0x12B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU174[0],
        (U4)0x12B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU175[0],
        (U4)0x12BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU176[0],
        (U4)0x12C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU177[0],
        (U4)0x12C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU178[0],
        (U4)0x12C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU179[0],
        (U4)0x12CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU180[0],
        (U4)0x12D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU181[0],
        (U4)0x12D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU182[0],
        (U4)0x12D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU183[0],
        (U4)0x12DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU184[0],
        (U4)0x12E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU185[0],
        (U4)0x12E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU186[0],
        (U4)0x12E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU187[0],
        (U4)0x12EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU188[0],
        (U4)0x12F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU189[0],
        (U4)0x12F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU190[0],
        (U4)0x12F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU191[0],
        (U4)0x12FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU192[0],
        (U4)0x13000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU193[0],
        (U4)0x13040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU194[0],
        (U4)0x13080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU195[0],
        (U4)0x130C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU196[0],
        (U4)0x13100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU197[0],
        (U4)0x13140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU198[0],
        (U4)0x13180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU199[0],
        (U4)0x131C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU200[0],
        (U4)0x13200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU201[0],
        (U4)0x13240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU202[0],
        (U4)0x13280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU203[0],
        (U4)0x132C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU204[0],
        (U4)0x13300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU205[0],
        (U4)0x13340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU206[0],
        (U4)0x13380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU207[0],
        (U4)0x133C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU208[0],
        (U4)0x13400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU209[0],
        (U4)0x13440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU210[0],
        (U4)0x13480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU211[0],
        (U4)0x134C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU212[0],
        (U4)0x13500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU213[0],
        (U4)0x13540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU214[0],
        (U4)0x13580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU215[0],
        (U4)0x135C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU216[0],
        (U4)0x13600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU217[0],
        (U4)0x13640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU218[0],
        (U4)0x13680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU219[0],
        (U4)0x136C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU220[0],
        (U4)0x13700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU221[0],
        (U4)0x13740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU222[0],
        (U4)0x13780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU223[0],
        (U4)0x137C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU224[0],
        (U4)0x13800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU225[0],
        (U4)0x13840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU226[0],
        (U4)0x13880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU227[0],
        (U4)0x138C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU228[0],
        (U4)0x13900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU229[0],
        (U4)0x13940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU230[0],
        (U4)0x13980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU231[0],
        (U4)0x139C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU232[0],
        (U4)0x13A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU233[0],
        (U4)0x13A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU234[0],
        (U4)0x13A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU235[0],
        (U4)0x13AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU236[0],
        (U4)0x13B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU237[0],
        (U4)0x13B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU238[0],
        (U4)0x13B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU239[0],
        (U4)0x13BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU240[0],
        (U4)0x13C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU241[0],
        (U4)0x13C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU242[0],
        (U4)0x13C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU243[0],
        (U4)0x13CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU244[0],
        (U4)0x13D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU245[0],
        (U4)0x13D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU246[0],
        (U4)0x13D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU247[0],
        (U4)0x13DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU248[0],
        (U4)0x13E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU249[0],
        (U4)0x13E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU250[0],
        (U4)0x13E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU251[0],
        (U4)0x13EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU252[0],
        (U4)0x13F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU253[0],
        (U4)0x13F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU254[0],
        (U4)0x13F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU255[0],
        (U4)0x13FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU256[0],
        (U4)0x14000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU257[0],
        (U4)0x14040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU258[0],
        (U4)0x14080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU259[0],
        (U4)0x140C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU260[0],
        (U4)0x14100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU261[0],
        (U4)0x14140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU262[0],
        (U4)0x14180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU263[0],
        (U4)0x141C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU264[0],
        (U4)0x14200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU265[0],
        (U4)0x14240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU266[0],
        (U4)0x14280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU267[0],
        (U4)0x142C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU268[0],
        (U4)0x14300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU269[0],
        (U4)0x14340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU270[0],
        (U4)0x14380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU271[0],
        (U4)0x143C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU272[0],
        (U4)0x14400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU273[0],
        (U4)0x14440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU274[0],
        (U4)0x14480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU275[0],
        (U4)0x144C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU276[0],
        (U4)0x14500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU277[0],
        (U4)0x14540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU278[0],
        (U4)0x14580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU279[0],
        (U4)0x145C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU280[0],
        (U4)0x14600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU281[0],
        (U4)0x14640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU282[0],
        (U4)0x14680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU283[0],
        (U4)0x146C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU284[0],
        (U4)0x14700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU285[0],
        (U4)0x14740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU286[0],
        (U4)0x14780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU287[0],
        (U4)0x147C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU288[0],
        (U4)0x14800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU289[0],
        (U4)0x14840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU290[0],
        (U4)0x14880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU291[0],
        (U4)0x148C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU292[0],
        (U4)0x14900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU293[0],
        (U4)0x14940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU294[0],
        (U4)0x14980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU295[0],
        (U4)0x149C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU296[0],
        (U4)0x14A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU297[0],
        (U4)0x14A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU298[0],
        (U4)0x14A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU299[0],
        (U4)0x14AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU300[0],
        (U4)0x14B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU301[0],
        (U4)0x14B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU302[0],
        (U4)0x14B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU303[0],
        (U4)0x14BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU304[0],
        (U4)0x14C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU305[0],
        (U4)0x14C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU306[0],
        (U4)0x14C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU307[0],
        (U4)0x14CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU308[0],
        (U4)0x14D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU309[0],
        (U4)0x14D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU310[0],
        (U4)0x14D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU311[0],
        (U4)0x14DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU312[0],
        (U4)0x14E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU313[0],
        (U4)0x14E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU314[0],
        (U4)0x14E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU315[0],
        (U4)0x14EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU316[0],
        (U4)0x14F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU317[0],
        (U4)0x14F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU318[0],
        (U4)0x14F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU319[0],
        (U4)0x14FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU320[0],
        (U4)0x15000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU321[0],
        (U4)0x15040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU322[0],
        (U4)0x15080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU323[0],
        (U4)0x150C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU324[0],
        (U4)0x15100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU325[0],
        (U4)0x15140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU326[0],
        (U4)0x15180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU327[0],
        (U4)0x151C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU328[0],
        (U4)0x15200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU329[0],
        (U4)0x15240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU330[0],
        (U4)0x15280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU331[0],
        (U4)0x152C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU332[0],
        (U4)0x15300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU333[0],
        (U4)0x15340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU334[0],
        (U4)0x15380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU335[0],
        (U4)0x153C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU336[0],
        (U4)0x15400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU337[0],
        (U4)0x15440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU338[0],
        (U4)0x15480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU339[0],
        (U4)0x154C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU340[0],
        (U4)0x15500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU341[0],
        (U4)0x15540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU342[0],
        (U4)0x15580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU343[0],
        (U4)0x155C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU344[0],
        (U4)0x15600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU345[0],
        (U4)0x15640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU346[0],
        (U4)0x15680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU347[0],
        (U4)0x156C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU348[0],
        (U4)0x15700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU349[0],
        (U4)0x15740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU350[0],
        (U4)0x15780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU351[0],
        (U4)0x157C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU352[0],
        (U4)0x15800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU353[0],
        (U4)0x15840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU354[0],
        (U4)0x15880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU355[0],
        (U4)0x158C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU356[0],
        (U4)0x15900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU357[0],
        (U4)0x15940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU358[0],
        (U4)0x15980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU359[0],
        (U4)0x159C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU360[0],
        (U4)0x15A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU361[0],
        (U4)0x15A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU362[0],
        (U4)0x15A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU363[0],
        (U4)0x15AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU364[0],
        (U4)0x15B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU365[0],
        (U4)0x15B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU366[0],
        (U4)0x15B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU367[0],
        (U4)0x15BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU368[0],
        (U4)0x15C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU369[0],
        (U4)0x15C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU370[0],
        (U4)0x15C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU371[0],
        (U4)0x15CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU372[0],
        (U4)0x15D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU373[0],
        (U4)0x15D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU374[0],
        (U4)0x15D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU375[0],
        (U4)0x15DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU376[0],
        (U4)0x15E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU377[0],
        (U4)0x15E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU378[0],
        (U4)0x15E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU379[0],
        (U4)0x15EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU380[0],
        (U4)0x15F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU381[0],
        (U4)0x15F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU382[0],
        (U4)0x15F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU383[0],
        (U4)0x15FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU384[0],
        (U4)0x16000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU385[0],
        (U4)0x16040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU386[0],
        (U4)0x16080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU387[0],
        (U4)0x160C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU388[0],
        (U4)0x16100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU389[0],
        (U4)0x16140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU390[0],
        (U4)0x16180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU391[0],
        (U4)0x161C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU392[0],
        (U4)0x16200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU393[0],
        (U4)0x16240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU394[0],
        (U4)0x16280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU395[0],
        (U4)0x162C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU396[0],
        (U4)0x16300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU397[0],
        (U4)0x16340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU398[0],
        (U4)0x16380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU399[0],
        (U4)0x163C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU400[0],
        (U4)0x16400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU401[0],
        (U4)0x16440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU402[0],
        (U4)0x16480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU403[0],
        (U4)0x164C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU404[0],
        (U4)0x16500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU405[0],
        (U4)0x16540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU406[0],
        (U4)0x16580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU407[0],
        (U4)0x165C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU408[0],
        (U4)0x16600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU409[0],
        (U4)0x16640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU410[0],
        (U4)0x16680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU411[0],
        (U4)0x166C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU412[0],
        (U4)0x16700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU413[0],
        (U4)0x16740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU414[0],
        (U4)0x16780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU415[0],
        (U4)0x167C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU416[0],
        (U4)0x16800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU417[0],
        (U4)0x16840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU418[0],
        (U4)0x16880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU419[0],
        (U4)0x168C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU420[0],
        (U4)0x16900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU421[0],
        (U4)0x16940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU422[0],
        (U4)0x16980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU423[0],
        (U4)0x169C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU424[0],
        (U4)0x16A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU425[0],
        (U4)0x16A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU426[0],
        (U4)0x16A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU427[0],
        (U4)0x16AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU428[0],
        (U4)0x16B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU429[0],
        (U4)0x16B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU430[0],
        (U4)0x16B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU431[0],
        (U4)0x16BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU432[0],
        (U4)0x16C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU433[0],
        (U4)0x16C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU434[0],
        (U4)0x16C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU435[0],
        (U4)0x16CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU436[0],
        (U4)0x16D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU437[0],
        (U4)0x16D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU438[0],
        (U4)0x16D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU439[0],
        (U4)0x16DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU440[0],
        (U4)0x16E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU441[0],
        (U4)0x16E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU442[0],
        (U4)0x16E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU443[0],
        (U4)0x16EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU444[0],
        (U4)0x16F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU445[0],
        (U4)0x16F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU446[0],
        (U4)0x16F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU447[0],
        (U4)0x16FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU448[0],
        (U4)0x17000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU449[0],
        (U4)0x17040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU450[0],
        (U4)0x17080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU451[0],
        (U4)0x170C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU452[0],
        (U4)0x17100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU453[0],
        (U4)0x17140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU454[0],
        (U4)0x17180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU455[0],
        (U4)0x171C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU456[0],
        (U4)0x17200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU457[0],
        (U4)0x17240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU458[0],
        (U4)0x17280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU472[0],
        (U4)0x1BF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU473[0],
        (U4)0x1BFC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU474[0],
        (U4)0x1C000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU475[0],
        (U4)0x1C040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU476[0],
        (U4)0x1C080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU477[0],
        (U4)0x1C0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU459[0],
        (U4)0x172C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU460[0],
        (U4)0x17300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU461[0],
        (U4)0x17340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU462[0],
        (U4)0x17380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU463[0],
        (U4)0x173C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU464[0],
        (U4)0x17400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU465[0],
        (U4)0x17440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU466[0],
        (U4)0x17480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU467[0],
        (U4)0x174C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU468[0],
        (U4)0x17500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU469[0],
        (U4)0x17540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU470[0],
        (U4)0x17580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_INIT_PDU471[0],
        (U4)0x175C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP[MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU1[0],
        (U4)0x17600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU2[0],
        (U4)0x17640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU3[0],
        (U4)0x17680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_SIP_PDU4[0],
        (U4)0x176C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080[MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU1[0],
        (U4)0x17700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU2[0],
        (U4)0x17740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU3[0],
        (U4)0x17780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU4[0],
        (U4)0x177C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU5[0],
        (U4)0x17800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU6[0],
        (U4)0x17840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU7[0],
        (U4)0x17880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU8[0],
        (U4)0x178C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU9[0],
        (U4)0x17900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU10[0],
        (U4)0x17940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU11[0],
        (U4)0x17980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU12[0],
        (U4)0x179C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU13[0],
        (U4)0x17A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU14[0],
        (U4)0x17A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU15[0],
        (U4)0x17A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU16[0],
        (U4)0x17AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU17[0],
        (U4)0x17B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU18[0],
        (U4)0x17B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU19[0],
        (U4)0x17B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU20[0],
        (U4)0x17BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU21[0],
        (U4)0x17C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU22[0],
        (U4)0x17C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU23[0],
        (U4)0x17C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU24[0],
        (U4)0x17CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU25[0],
        (U4)0x17D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU26[0],
        (U4)0x17D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU27[0],
        (U4)0x17D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU28[0],
        (U4)0x17DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU29[0],
        (U4)0x17E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU30[0],
        (U4)0x17E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU31[0],
        (U4)0x17E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU32[0],
        (U4)0x17EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU33[0],
        (U4)0x17F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU34[0],
        (U4)0x17F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU35[0],
        (U4)0x17F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU36[0],
        (U4)0x17FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU37[0],
        (U4)0x18000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU38[0],
        (U4)0x18040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU39[0],
        (U4)0x18080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU40[0],
        (U4)0x180C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU41[0],
        (U4)0x18100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU42[0],
        (U4)0x18140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU43[0],
        (U4)0x18180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU44[0],
        (U4)0x181C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU45[0],
        (U4)0x18200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU46[0],
        (U4)0x18240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU47[0],
        (U4)0x18280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU48[0],
        (U4)0x182C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU49[0],
        (U4)0x18300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU50[0],
        (U4)0x18340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU51[0],
        (U4)0x18380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU52[0],
        (U4)0x183C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU53[0],
        (U4)0x18400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU54[0],
        (U4)0x18440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU55[0],
        (U4)0x18480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU56[0],
        (U4)0x184C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU57[0],
        (U4)0x18500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU58[0],
        (U4)0x18540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU59[0],
        (U4)0x18580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU60[0],
        (U4)0x185C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU61[0],
        (U4)0x18600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU62[0],
        (U4)0x18640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU63[0],
        (U4)0x18680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU64[0],
        (U4)0x186C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU65[0],
        (U4)0x18700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU66[0],
        (U4)0x18740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU67[0],
        (U4)0x18780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU68[0],
        (U4)0x187C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU69[0],
        (U4)0x18800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU70[0],
        (U4)0x18840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU71[0],
        (U4)0x18880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU72[0],
        (U4)0x188C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU73[0],
        (U4)0x18900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU74[0],
        (U4)0x18940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU75[0],
        (U4)0x18980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU76[0],
        (U4)0x189C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU77[0],
        (U4)0x18A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU78[0],
        (U4)0x18A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU79[0],
        (U4)0x18A80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU80[0],
        (U4)0x18AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU81[0],
        (U4)0x18B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU82[0],
        (U4)0x18B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU83[0],
        (U4)0x18B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU84[0],
        (U4)0x18BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU85[0],
        (U4)0x18C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU86[0],
        (U4)0x18C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU87[0],
        (U4)0x18C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU88[0],
        (U4)0x18CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU89[0],
        (U4)0x18D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU90[0],
        (U4)0x18D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU91[0],
        (U4)0x18D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU92[0],
        (U4)0x18DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU93[0],
        (U4)0x18E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU94[0],
        (U4)0x18E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU95[0],
        (U4)0x18E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU96[0],
        (U4)0x18EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU97[0],
        (U4)0x18F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU98[0],
        (U4)0x18F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU99[0],
        (U4)0x18F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU100[0],
        (U4)0x18FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU101[0],
        (U4)0x19000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU102[0],
        (U4)0x19040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU103[0],
        (U4)0x19080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU104[0],
        (U4)0x190C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU105[0],
        (U4)0x19100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU106[0],
        (U4)0x19140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU107[0],
        (U4)0x19180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU108[0],
        (U4)0x191C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU109[0],
        (U4)0x19200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU110[0],
        (U4)0x19240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU111[0],
        (U4)0x19280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU112[0],
        (U4)0x192C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU113[0],
        (U4)0x19300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU114[0],
        (U4)0x19340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU115[0],
        (U4)0x19380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU116[0],
        (U4)0x193C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU117[0],
        (U4)0x19400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU118[0],
        (U4)0x19440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU119[0],
        (U4)0x19480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU120[0],
        (U4)0x194C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU121[0],
        (U4)0x19500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU122[0],
        (U4)0x19540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU123[0],
        (U4)0x19580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU124[0],
        (U4)0x195C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU125[0],
        (U4)0x19600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU126[0],
        (U4)0x19640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU127[0],
        (U4)0x19680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU128[0],
        (U4)0x196C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU129[0],
        (U4)0x19700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU130[0],
        (U4)0x19740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU131[0],
        (U4)0x19780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU132[0],
        (U4)0x197C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU133[0],
        (U4)0x19800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU134[0],
        (U4)0x19840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU135[0],
        (U4)0x19880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU136[0],
        (U4)0x198C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU137[0],
        (U4)0x19900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU138[0],
        (U4)0x19940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU139[0],
        (U4)0x19980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU140[0],
        (U4)0x199C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU141[0],
        (U4)0x19A00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU142[0],
        (U4)0x19A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_1080_PDU143[0],
        (U4)0x19A80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON[MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU1[0],
        (U4)0x19AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU2[0],
        (U4)0x19B00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU3[0],
        (U4)0x19B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU4[0],
        (U4)0x19B80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU5[0],
        (U4)0x19BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU6[0],
        (U4)0x19C00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU7[0],
        (U4)0x19C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU8[0],
        (U4)0x19C80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU9[0],
        (U4)0x19CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU10[0],
        (U4)0x19D00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU11[0],
        (U4)0x19D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU12[0],
        (U4)0x19D80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU13[0],
        (U4)0x19DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU14[0],
        (U4)0x19E00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU15[0],
        (U4)0x19E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU16[0],
        (U4)0x19E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU17[0],
        (U4)0x19EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU18[0],
        (U4)0x19F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU19[0],
        (U4)0x19F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU20[0],
        (U4)0x19F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU21[0],
        (U4)0x19FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU22[0],
        (U4)0x1A000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU23[0],
        (U4)0x1A040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU24[0],
        (U4)0x1A080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU25[0],
        (U4)0x1A0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU26[0],
        (U4)0x1A100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU27[0],
        (U4)0x1A140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU28[0],
        (U4)0x1A180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU29[0],
        (U4)0x1A1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU30[0],
        (U4)0x1A200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU31[0],
        (U4)0x1A240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU32[0],
        (U4)0x1A280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU33[0],
        (U4)0x1A2C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU34[0],
        (U4)0x1A300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU35[0],
        (U4)0x1A340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU36[0],
        (U4)0x1A380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU37[0],
        (U4)0x1A3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU38[0],
        (U4)0x1A400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU39[0],
        (U4)0x1A440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU40[0],
        (U4)0x1A480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU41[0],
        (U4)0x1A4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU42[0],
        (U4)0x1A500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU43[0],
        (U4)0x1A540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU44[0],
        (U4)0x1A580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU45[0],
        (U4)0x1A5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU46[0],
        (U4)0x1A600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU47[0],
        (U4)0x1A640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU48[0],
        (U4)0x1A680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU49[0],
        (U4)0x1A6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU50[0],
        (U4)0x1A700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU51[0],
        (U4)0x1A740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU52[0],
        (U4)0x1A780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU53[0],
        (U4)0x1A7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU54[0],
        (U4)0x1A800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU55[0],
        (U4)0x1A840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU56[0],
        (U4)0x1A880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU57[0],
        (U4)0x1A8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU58[0],
        (U4)0x1A900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU59[0],
        (U4)0x1A940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU60[0],
        (U4)0x1A980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU61[0],
        (U4)0x1A9C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU62[0],
        (U4)0x1AA00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU63[0],
        (U4)0x1AA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU64[0],
        (U4)0x1AA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU65[0],
        (U4)0x1AAC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU66[0],
        (U4)0x1AB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU67[0],
        (U4)0x1AB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU68[0],
        (U4)0x1AB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU69[0],
        (U4)0x1ABC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU70[0],
        (U4)0x1AC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU71[0],
        (U4)0x1AC40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU72[0],
        (U4)0x1AC80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU73[0],
        (U4)0x1ACC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU74[0],
        (U4)0x1AD00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU75[0],
        (U4)0x1AD40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU76[0],
        (U4)0x1AD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU77[0],
        (U4)0x1ADC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU78[0],
        (U4)0x1AE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU79[0],
        (U4)0x1AE40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU80[0],
        (U4)0x1AE80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU81[0],
        (U4)0x1AEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU82[0],
        (U4)0x1AF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU83[0],
        (U4)0x1AF40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU84[0],
        (U4)0x1AF80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU85[0],
        (U4)0x1AFC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU86[0],
        (U4)0x1B000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU87[0],
        (U4)0x1B040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU88[0],
        (U4)0x1B080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU89[0],
        (U4)0x1B0C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU90[0],
        (U4)0x1B100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU91[0],
        (U4)0x1B140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU92[0],
        (U4)0x1B180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU93[0],
        (U4)0x1B1C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU94[0],
        (U4)0x1B200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU95[0],
        (U4)0x1B240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU96[0],
        (U4)0x1B280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU97[0],
        (U4)0x1B2C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU98[0],
        (U4)0x1B300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU99[0],
        (U4)0x1B340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU100[0],
        (U4)0x1B380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU101[0],
        (U4)0x1B3C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU102[0],
        (U4)0x1B400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU103[0],
        (U4)0x1B440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU104[0],
        (U4)0x1B480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU105[0],
        (U4)0x1B4C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU106[0],
        (U4)0x1B500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU107[0],
        (U4)0x1B540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU108[0],
        (U4)0x1B580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU109[0],
        (U4)0x1B5C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU110[0],
        (U4)0x1B600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU111[0],
        (U4)0x1B640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU112[0],
        (U4)0x1B680003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU113[0],
        (U4)0x1B6C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU114[0],
        (U4)0x1B700003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU115[0],
        (U4)0x1B740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU116[0],
        (U4)0x1B780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU117[0],
        (U4)0x1B7C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU118[0],
        (U4)0x1B800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU119[0],
        (U4)0x1B840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU120[0],
        (U4)0x1B880003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU121[0],
        (U4)0x1B8C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU122[0],
        (U4)0x1B900003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU123[0],
        (U4)0x1B940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU124[0],
        (U4)0x1B980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU125[0],
        (U4)0x1B9C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU126[0],
        (U4)0x1BA00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU127[0],
        (U4)0x1BA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU128[0],
        (U4)0x1BA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU129[0],
        (U4)0x1BAC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU130[0],
        (U4)0x1BB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU131[0],
        (U4)0x1BB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU132[0],
        (U4)0x1BB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU133[0],
        (U4)0x1BBC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU134[0],
        (U4)0x1BC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU135[0],
        (U4)0x1BC40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU136[0],
        (U4)0x1BC80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU137[0],
        (U4)0x1BCC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU138[0],
        (U4)0x1BD00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU139[0],
        (U4)0x1BD40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU140[0],
        (U4)0x1BD80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU141[0],
        (U4)0x1BDC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU142[0],
        (U4)0x1BE00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NON_PDU143[0],
        (U4)0x1BE40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON[MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU1[0],
        (U4)0x1BE80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU2[0],
        (U4)0x1BEC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU3[0],
        (U4)0x1BF00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CENTERDISP_ON_PDU4[0],
        (U4)0x1BF40003U
    }
};


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
