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
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_CYCLE                     (5U)
#define D_ETHSWT_SWIC_PWR_ON_WAIT                   (105U)  /* 35ms(T8) + 60ms(T9) + PwrCtrlがEthSwtよりも先にコールされる + (タスク・CPUクロック誤差考慮) */
#define D_ETHSWT_SWIC_PWR_ASSERT_WAIT               (10U)    /* 1ms(T1) + (タスク・CPUクロック誤差) */
#define D_ETHSWT_SWIC_PWR_DEASSERT_WAIT             (20U)   /* 15ms(T2) + (タスク・CPUクロック誤差) */

void EthSwt_SWIC_SetGPIOMode(void);
void EthSwt_SWIC_SetSPIMode(void);
void EthSwt_SWIC_SetPowerOn(void);
void EthSwt_SWIC_SetPowerOff(void);
void EthSwt_SWIC_SetResetAssert(void);
void EthSwt_SWIC_SetResetDeassert(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_AllowRelay(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_AllowSetRegister(void);

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
/* Config for EthSwt_SWIC_MIB.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_MIB_GET_CYCLE	                (100U)

#define D_ETHSWT_SWIC_MIB_INFCSERR					(0U)
#define D_ETHSWT_SWIC_MIB_INDISCARDS				(1U)
#define D_ETHSWT_SWIC_MIB_INFILTERED				(2U)
#define D_ETHSWT_SWIC_MIB_INOVERSIZE				(3U)
#define D_ETHSWT_SWIC_MIB_INUNDERSIZE				(4U)
#define D_ETHSWT_SWIC_MIB_TCAM0						(5U)
#define D_ETHSWT_SWIC_MIB_TCAM1						(6U)
#define D_ETHSWT_SWIC_MIB_TCAM2						(7U)
#define D_ETHSWT_SWIC_MIB_TCAM3						(8U)
#define D_ETHSWT_SWIC_MIB_NUM						(9U)


/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_CFG_H */
/* -------------------------------------------------------------------------- */
