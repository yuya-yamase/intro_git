/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_CFG_H
#define ETHSWT_SWIC_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
/* Common */
#include <EthSwt_BSW_define.h>								/* BSWに合わせてヘッダファイル変更 */

#define D_ETHSWT_SWIC_PERIOD                        (1U)
#define D_ETHSWT_SWIC_PORT_NUM                      (9U)
extern const Eth_ModeType G_ETHSWT_SWIC_PORT_DEFINE[D_ETHSWT_SWIC_PORT_NUM];
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_Init(void);
/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_CYCLE                     (5U)
#define D_ETHSWT_SWIC_PWR_ON_WAIT                   (155U)  /* 35ms(T8) + 60ms(T9) + PwrCtrlがEthSwtよりも先にコールされる + (タスク・CPUクロック誤差考慮) */ /* 暫定 */
#define D_ETHSWT_SWIC_PWR_ASSERT_WAIT               (10U)    /* 1ms(T1) + (タスク・CPUクロック誤差) */
#define D_ETHSWT_SWIC_PWR_DEASSERT_WAIT             (20U)   /* 15ms(T2) + (タスク・CPUクロック誤差) */

void EthSwt_SWIC_Cfg_PowerOnReq(void);
void EthSwt_SWIC_Cfg_PowerOffReq(void);
Std_ReturnType EthSwt_SWIC_Cfg_CheckPowerCond(void);
Std_ReturnType EthSwt_SWIC_Cfg_CheckSuplyState(void);
void EthSwt_SWIC_Cfg_SetGPIOMode(void);
void EthSwt_SWIC_Cfg_SetSPIMode(void);
void EthSwt_SWIC_Cfg_SetPowerOn(void);
void EthSwt_SWIC_Cfg_SetPowerOff(void);
void EthSwt_SWIC_Cfg_SetResetAssert(void);
void EthSwt_SWIC_Cfg_SetResetDeassert(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowRelay(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowSetRegister(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
#define	SWIC_REG_WAIT	(31u)	/* 30ms(REG_CTRL_READ.SURVEILLANCE_ON待ち時間) + クロック誤差 */
#define	SWIC_REG_WAIT_L	(((SWIC_REG_WAIT*1000000u)/2410u)+1u) /* ループガード値 */
								/* クロック2(20MHz)で1要求(6byte+10ns)=2410ns */
								/* ※クロックは10MHzなので倍になる */
								/* ※実測値の5倍程度になる */
 

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_Link.c                                              */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_LINK_FAST_GET_TMO             (70U)
#define D_ETHSWT_SWIC_LINK_GET_CYCLE                (100U)



/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_CFG_H */
/* -------------------------------------------------------------------------- */
