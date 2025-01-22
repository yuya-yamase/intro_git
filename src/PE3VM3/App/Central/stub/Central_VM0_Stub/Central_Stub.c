/* 暫定_EtherSwitch起動用スタブ */
#include "Central_Stub.h"

#define ETH_PMIC_OFF  (0x00)
#define ETH_PMIC_ON   (0x01)

static U1	u1_s_pmic_state;

void vd_Central_Stub_Init(void){
	u1_s_pmic_state  =(U1)ETH_PMIC_OFF;		/* PMIC OFF */
	EthSwt_SWIC_Init(NULL_PTR);				/* EthSwt初期化 */
}
void vd_Central_Stub_Midtask(void){
	U1 pw_sts;

	/* 電源起動シーケンス完了判定 */
	#warning "VM_Layout"
	/* pw_sts = (U1)u1_g_Mcu_PwrCtrl_Status(); */
	#warning "VM_Layout"
	/*
	if( pw_sts == (U1)MCU_PWRCTRL_NO_REQ){
		電源起動シーケンス完了後、1度実施
		if(u1_s_pmic_state == (U1)ETH_PMIC_OFF){
			Pmic_PowerOnEthSwitch();			Eth PMIC = ON : ETHER_PWR_EN = High
			EthSwt_SWIC_RESET_N_Hi();			Eth PMIC = ON : ETH_U2A_RESET_N = High
			u1_s_pmic_state = (U1)ETH_PMIC_ON;	PMIC ON
		}
		PMIC ON後実施
		else{
			EthSwt_SWIC_MainFunction1MS(); 
			EthSwt_SWIC_MainFunction5MS();
		}
	}
	*/
}
void vd_Central_Stub_Lowtask(void){
	/* PMIC ON後実施 */
	if(u1_s_pmic_state == (U1)ETH_PMIC_ON){
		/* EthSwtバックグラウンドタスク */
		EthSwt_SWIC_BackgroundTask();
	}
}
