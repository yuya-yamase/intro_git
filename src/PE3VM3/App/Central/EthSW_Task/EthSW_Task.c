#include <Std_Types.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include <EthSW_Task.h>
#include <EthSwt_SWIC.h>
#include "Pmic_Pwr.h"

#define ETH_PMIC_OFF        (0x00)   /* PMIC OFF状態 */
#define ETH_PMIC_ON         (0x01)   /* PMIC ON状態  */
#define ETH_PMIC_SAIL_WAIT  (0x02)   /* PMIC SAIL_RESOUT_N=Hi待ち状態 */

static U1 u1_s_ether_pmic_state;

void EthSW_Sch_PowerOnInit (void)
{
	/* +B,Wakup,Reset時 */
	u1_s_ether_pmic_state = (U1)ETH_PMIC_OFF;					/* PMIC ON状態 */
	EthSwt_SWIC_Init(NULL_PTR);									/* EthSwt初期化 */
}

void EthSW_MediumTask (void)
{
	U1 u1_t_sail_resout_n;

	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON){
	/* PMIC ON後、周期処理 */
		EthSwt_SWIC_MainFunction5MS();							/* EthSwt 5msMidタスク */
	}
	else if(u1_s_ether_pmic_state == (U1)ETH_PMIC_SAIL_WAIT){
	u1_t_sail_resout_n = Dio_ReadChannel(DIO_ID_PORT8_CH8);		/* SAIL_RESOUT_N参照 */
	if(u1_t_sail_resout_n == STD_HIGH){
			Pmic_PowerOnEthSwitch();							/* Eth PMIC = ON(ETHER_PWR_EN = High) */
			EthSwt_SWIC_RESET_N_Hi();							/* Eth PMIC = ON(ETH_U2A_RESET_N = High) */
			u1_s_ether_pmic_state = (U1)ETH_PMIC_ON;			/* PMIC ON状態 */
		}
	}
	else{
		/* 何もしない */
	}
	return;
}

void EthSW_HighTask (void)
{
	/* PMIC ON後、周期処理 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON){
		EthSwt_SWIC_MainFunction1MS();							/* EthSwt 1msHighタスク */
	}
	return;
}

void EthSW_LowTask (void)
{
	/* PMIC ON後、周期処理 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON){
		EthSwt_SWIC_BackgroundTask();							/* EthSwtバックグラウンドタスク */
	}
	return;
}

void EthSW_PowerON_Req_Bon (void)
{
	/* Ethernet SW 電源ON用制御 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_OFF){
		Pmic_PowerOnEthSwitch();								/* Eth PMIC = ON(ETHER_PWR_EN = High) */
		EthSwt_SWIC_RESET_N_Hi();								/* Eth PMIC = ON(ETH_U2A_RESET_N = High) */
		u1_s_ether_pmic_state = (U1)ETH_PMIC_ON;				/* PMIC ON状態 */
	}
}

void EthSW_PowerOn_Req_Wakeup (void)
{
	U1 u1_t_sail_resout_n;

	/* Ethernet SW 電源ON用制御 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_OFF){
		u1_t_sail_resout_n = Dio_ReadChannel(DIO_ID_PORT8_CH8);	/* SAIL_RESOUT_N参照 */
		if(u1_t_sail_resout_n == STD_HIGH){
			Pmic_PowerOnEthSwitch();							/* Eth PMIC = ON(ETHER_PWR_EN = High) */
			EthSwt_SWIC_RESET_N_Hi();							/* Eth PMIC = ON(ETH_U2A_RESET_N = High) */
			u1_s_ether_pmic_state = (U1)ETH_PMIC_ON;			/* PMIC ON状態 */
		}
		else{
			/* Wakeup時にSAIL_RESOUT_NがHiではない(電源状態異常) */
			u1_s_ether_pmic_state = (U1)ETH_PMIC_SAIL_WAIT;		/* PMIC SAIL_RESOUT_N=Hi待ち状態 */
		}
	}
}

void EthSW_PowerOff_Req (void)
{
	/* Ethernet SW 電源OFF用制御 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON)
	{
		EthSwt_SWIC_DeInit();								/* SPI通信ラインをGPIOに変更 */
		EthSwt_SWIC_RESET_N_Lo();							/* Eth PMIC = OFF(ETH_U2A_RESET_N = Low) */
		Pmic_PowerOffEthSwitch();							/* Eth PMIC = OFF(ETHER_PWR_EN = Low) */
		u1_s_ether_pmic_state = (U1)ETH_PMIC_OFF;			/* PMIC OFF状態 */
	}
}
