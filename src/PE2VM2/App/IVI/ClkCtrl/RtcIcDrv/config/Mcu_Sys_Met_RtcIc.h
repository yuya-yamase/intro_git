/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef MCU_SYS_MET_CRTIC_H
#define MCU_SYS_MET_CRTIC_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpi2c_ma.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_SYS_MET_RTCIC_SLAVEADR_WR                       (0x64U)
#define MCU_SYS_MET_RTCIC_SLAVEADR_RD                       (0x65U)

#define MCU_SYS_MET_RTCIC_RWC_BYTE1                         (1U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE2                         (2U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE3                         (3U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE4                         (4U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE5                         (5U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE6                         (6U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE7                         (7U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE8                         (8U)
#define MCU_SYS_MET_RTCIC_RWC_BYTE9                         (9U)

#define MCU_SYS_MET_RTCIC_SETREG_CLK_NUM                    (4U)
#define MCU_SYS_MET_RTCIC_SETREG_DAYSET_NUM                 (1U)
#define MCU_SYS_MET_RTCIC_SETREG_VLF_NUM                    (1U)

#define MCU_SYS_MET_RTCIC_READREG_VLF_NUM                   (2U)
#define MCU_SYS_MET_RTCIC_READREG_CLK_NUM                   (2U)
#define MCU_SYS_MET_RTCIC_READREG_CONT_NUM                  (2U)
#define MCU_SYS_MET_RTCIC_READREG_BACKUP_NUM                (2U)
#define MCU_SYS_MET_RTCIC_READREG_RAM_NUM                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U1 u1_sp_MCU_SYS_MET_RTCIC_SETREG_CLK_RD_PDU2[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void Mcu_Sys_Met_RtcIc_Clk_Init(const U4 u4_ap_HHMMSS_24H, const U4 u4_a_daycnt);
void Mcu_Sys_Met_RtcIc_Vlf_Rd_Init(void);
U1   Mcu_Sys_Met_RtcIc_Vlf_Rd_Read(void);
void Mcu_Sys_Met_RtcIc_Clk_Rd_Init(void);
void Mcu_Sys_Met_RtcIc_Clk_Rd_Read(U4* u4_ap_HHMMSS_24H, U4* u4_ap_daycnt);
void Mcu_Sys_Met_RtcIc_Day_Set(const U4 u4_a_daycnt);

void Mcu_Sys_Met_RtcIc_ContReg_Rd_Init(void);
void Mcu_Sys_Met_RtcIc_Backup_Rd_Init(void);
void Mcu_Sys_Met_RtcIc_Ram_Rd_Init(void);

U1   Mcu_Sys_Met_RtcIc_ContReg_Rd_Cmp(void);
U1   Mcu_Sys_Met_RtcIc_Backup_Rd_Cmp(void);
U1   Mcu_Sys_Met_RtcIc_Ram_Rd_Cmp(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_SETREG_CLK[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_SETREG_DAYSET[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_READREG_VLF[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_READREG_CLK[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_READREG_CONT[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_READREG_BACKUP[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_READREG_RAM[];
extern const ST_GP_I2C_MA_REQ     st_sp_MCU_SYS_MET_RTCIC_SETREG_VLF[];

#endif      /* MCU_SYS_MET_CRTIC_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  Mcu_Sys_Met_CrtIc.c                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
