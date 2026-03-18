/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_CFG_H
#define ETHSWT_SWIC_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDebugLog.h>
/* -------------------------------------------------------------------------- */
/* Common */
#include <EthSwt_BSW_define.h>								/* BSWに合わせてヘッダファイル変更 */

#define D_ETHSWT_SWIC_PORT_NUM                      (9U)
extern const Eth_ModeType G_ETHSWT_SWIC_PORT_DEFINE[D_ETHSWT_SWIC_PORT_NUM];
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_Init(void);
/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_CYCLE                     (5U)
#define D_ETHSWT_SWIC_PWR_ON_WAIT                   (105U)  /* 35ms(T8) + 60ms(T9) + 5ms(PwrCtrlがEthSwtよりも先にコールされる) + 5ms(タスク・CPUクロック誤差考慮) */
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

#define ETHSWT_SWIC_PWR_NOTIFY()                  	EthSwt_Data_NotifySWICReset()

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
#define ETHSWT_SWIC_UNINIT_START()
#define ETHSWT_SWIC_INIT_START()
#define ETHSWT_SWIC_PORT_INIT_COMPLETED_START()
#define ETHSWT_SWIC_SET_RELAY_ON_START()
#define ETHSWT_SWIC_ACTIVE_START()					EthDebugLog_Notify(E_ETHDEBUGLOG_EV_LINKUPREADY)
#define ETHSWT_SWIC_SET_RELAY_OFF_START()

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


#define D_ETHSWT_SWIC_CLOCK_PER_US					(400U)			/* 1usあたりのクロック数 */
void EthSwt_SWIC_Cfg_WaitUS(const uint32 waitUSTime);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_Link.c                                              */
/* -------------------------------------------------------------------------- */
#include <EthSwt_Data.h>
#define D_ETHSWT_SWIC_LINK_GET_CYCLE                (100U)

#define ETHSWT_SWIC_LINK_NOTIFY(SwitchPortIdx, result, state)		EthSwt_Data_NotifyLink(SwitchPortIdx, result, state)

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

#define ETHSWT_SWIC_MIB_NOTIFY(SwitchPortIdx, MIBArray)				EthSwt_Data_NotifyMIB(SwitchPortIdx, MIBArray)

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_Qci.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_QCI_GET_CYCLE	                (20U)

#define D_ETHSWT_SWIC_QCI_ID_DCM_TCP				(0U)
#define D_ETHSWT_SWIC_QCI_ID_DCM_UDP				(1U)
#define D_ETHSWT_SWIC_QCI_ID_DCM_ICMP				(2U)
#define D_ETHSWT_SWIC_QCI_ID_DLC_TCP				(3U)
#define D_ETHSWT_SWIC_QCI_ID_DLC_UDP				(4U)
#define D_ETHSWT_SWIC_QCI_ID_NUM					(5U)

#define ETHSWT_SWIC_QCI_NOTIFY(qciIdx, qciCount)					EthSwt_Data_NotifyQci(qciIdx, qciCount)

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_RstDtct.c                                           */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_RSTDTCT_GET_CYCLE             (50U)	/* リセット検出周期(50ms) */
Std_ReturnType EthSwt_SWIC_RstDtct_IsNeedDtct(void);

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_IntErr.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_INTERR_GET_CYCLE	            (5U)	/* 内部エラー検出周期(5ms) */

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_SQI.c                                               */
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_SQI_GET_CYCLE                 (100U)	/* SQI値取得周期(100ms) */

#define ETHSWT_SWIC_SQI_NOTIFY(SwtichPortIdx, getSQIResult, SQIValue)		EthSwt_Data_NotifySQI(SwtichPortIdx, getSQIResult, SQIValue)
/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_RegAccess.c                                         */
/* -------------------------------------------------------------------------- */
#define G_ETHSWT_SWIC_REGACCESS_N_REGMONERREET      (3U)	/* レジスタ書き込み結果取得の試行回数 */

#define ETHSWT_SWIC_REGACCESS_NOTIFY(getRegAccessResult)		EthSwt_Data_NotifyRegAccess(getRegAccessResult)

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_CFG_H */
/* -------------------------------------------------------------------------- */
