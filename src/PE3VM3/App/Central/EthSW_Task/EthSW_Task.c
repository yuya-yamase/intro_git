#include <Std_Types.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include <EthSW_Task.h>
#include <EthSwt_SWIC.h>
#include "Pmic_Pwr.h"

#define ETH_PMIC_OFF  (0x00)
#define ETH_PMIC_ON   (0x01)

static U1 u1_s_ether_pmic_state;

void EthSW_Sch_PowerOnInit (void)
{
	u1_s_ether_pmic_state = (U1)ETH_PMIC_OFF;					/* PMIC ON状態 */
	EthSwt_SWIC_Init(NULL_PTR);									/* EthSwt初期化 */
}

void EthSW_MediumTask (void)
{
	/* 暫定：SAIL_RESOUT_NによるEthernetSW起動 */
	U1 u1_t_sail_resout_n;

	u1_t_sail_resout_n = Dio_ReadChannel(DIO_ID_PORT8_CH8);		/* SAIL_RESOUT_N参照 */
	if(u1_t_sail_resout_n == STD_HIGH){
		/* SAIL_RESOUT_N = Hi検知後、1度実施 */
		if(u1_s_ether_pmic_state == (U1)ETH_PMIC_OFF){
			Pmic_PowerOnEthSwitch();							/* Eth PMIC = ON(ETHER_PWR_EN = High) */
			EthSwt_SWIC_RESET_N_Hi();							/* Eth PMIC = ON(ETH_U2A_RESET_N = High) */
			u1_s_ether_pmic_state = (U1)ETH_PMIC_ON;			/* PMIC ON状態 */
		}
		/* PMIC ON後、周期処理 */
		else{
			EthSwt_SWIC_MainFunction5MS();						/* EthSwt 5msMidタスク */
		}
	}
	else{
		/* PMIC ON中にSAIL_RESOUT_N = Lo検知後、1度実施 */
		if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON)
		{
			EthSwt_SWIC_DeInit();								/* SPI通信ラインをGPIOに変更 */
			EthSwt_SWIC_RESET_N_Lo();							/* Eth PMIC = OFF(ETH_U2A_RESET_N = Low) */
			Pmic_PowerOffEthSwitch();							/* Eth PMIC = OFF(ETHER_PWR_EN = Low) */
			u1_s_ether_pmic_state = (U1)ETH_PMIC_OFF;			/* PMIC OFF状態 */
		}
	}
	return;
}

void EthSW_HighTask (void)
{
	/* PMIC ON後実施 */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON){
		/* EthSwtバックグラウンドタスク */
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

void EthSW_Sch_Stop (void){
	/* シャットダウンシーケンス未実施の場合、シャットダウン処理を行う */
	if(u1_s_ether_pmic_state == (U1)ETH_PMIC_ON)
	{
		EthSwt_SWIC_DeInit();								/* SPI通信ラインをGPIOに変更 */
		EthSwt_SWIC_RESET_N_Lo();							/* Eth PMIC = OFF(ETH_U2A_RESET_N = Low) */
		Pmic_PowerOffEthSwitch();							/* Eth PMIC = OFF(ETHER_PWR_EN = Low) */
		u1_s_ether_pmic_state = (U1)ETH_PMIC_OFF;			/* PMIC OFF状態 */
	}
}
