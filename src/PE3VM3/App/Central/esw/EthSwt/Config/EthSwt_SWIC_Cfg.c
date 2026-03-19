/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Cfg.c                                       */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Cfg.h"
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>
#include <VIS.h>
#include <LIB.h>
#include <EthSwt_SWIC_PWR.h>
#include <PwrCtrl_Main.h>
#include <ivdsh.h>
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_CFG_MCUPMIC_ON        (1U)
#define D_ETHSWT_SWIC_CFG_DIN2STAT_SIZE     (1U)
/* -------------------------------------------------------------------------- */
/* Common */
const Eth_ModeType G_ETHSWT_SWIC_PORT_DEFINE[D_ETHSWT_SWIC_PORT_NUM] =
{
    ETH_MODE_ACTIVE         /* Port1 */
,   ETH_MODE_ACTIVE         /* Port2 */
,   ETH_MODE_DOWN           /* Port3 */
,   ETH_MODE_DOWN           /* Port4 */
,   ETH_MODE_ACTIVE         /* Port5 */
,   ETH_MODE_DOWN           /* Port6 */
,   ETH_MODE_ACTIVE         /* Port7 */
,   ETH_MODE_ACTIVE         /* Port8 */
,   ETH_MODE_DOWN           /* Port9 */
};

static Std_ReturnType   S_ETHSWT_SWIC_POWERONREQ;

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC.c                                                   */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_Init(void)
{
    S_ETHSWT_SWIC_POWERONREQ = STD_OFF;

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC.c                                                   */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_PowerOnReq(void)
{
    S_ETHSWT_SWIC_POWERONREQ = STD_ON;

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC.c                                                   */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_PowerOffReq(void)
{
    S_ETHSWT_SWIC_POWERONREQ = STD_OFF;
    EthSwt_SWIC_PWR_ForceOffReq();

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_CheckPowerCond(void)
{
    Std_ReturnType  ret = STD_OFF;
    uint8           sail_resout_n;
    uint8           aoss_sleep_entry_exit;

    sail_resout_n = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_SAIL_RES);
    aoss_sleep_entry_exit = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_AOSS_SLP);

    if (S_ETHSWT_SWIC_POWERONREQ == STD_ON && sail_resout_n == STD_HIGH && aoss_sleep_entry_exit == STD_LOW) {
        ret = STD_ON;
    }
    
    return ret;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_CheckSuplyState(void)
{
    Std_ReturnType  ret = STD_OFF;
    uint8           readResult;
    uint32          din2_stat;

    readResult = u1_g_iVDshReabyDid(IVDSH_DID_REA_VM2TO3_DIN2_STAT, &din2_stat, (uint16)D_ETHSWT_SWIC_CFG_DIN2STAT_SIZE);

    if(readResult != IVDSH_NO_REA) {    /* DIN2_STAT情報取得の条件確認 */
        if (din2_stat == (uint32)D_ETHSWT_SWIC_CFG_MCUPMIC_ON) {
            ret = STD_ON;
        }
    }

    return ret;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetGPIOMode(void)
{
    /* - OEM Custom：SPI通信ラインをGPIOモードへ変更 - */
    Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_DI );         /* ETHERSW-RXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_DO_LO );      /* ETHERSW-CLK */
    Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_DO_LO );      /* ETHERSW-TXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_DO_LO );      /* ETHERSW-CS */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetSPIMode(void)
{
    /* - OEM Custom：SPI通信ラインをSPIモードへ変更 - */
    Port_SetPinMode(PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI);      /* ETHERSW-RXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC);      /* ETHERSW-CLK */
    Port_SetPinMode(PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO);      /* ETHERSW-TXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0);    /* ETHERSW-CS */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetPowerOn(void)
{
    /* - OEM Custom：SWIC電源ON - */
    /* ETHER_PWR_ENをHigh設定した後に、ETH_U2A_RESET_NをHigh設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);                         /* ETHER_PWR_EN */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetPowerOff(void)
{
    /* - OEM Custom：SWIC電源OFF - */
    /* ETH_U2A_RESET_NをLow設定した後に、ETHER_PWR_ENをLow設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW);                          /* ETHER_PWR_EN */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetResetAssert(void)
{
    /* - OEM Custom：SWICリセットアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetResetDeassert(void)
{
    /* - OEM Custom：SWICリセットディアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */
    
    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowRelay(void)
{
    /* - OEM Custom：中継が可能な状態か確認する - */
    Std_ReturnType ret = E_NOT_OK;
    volatile Std_ReturnType result;
    result = u1_g_VISPwrGetEthChPwr();
    if (result == STD_ON) {
        ret = E_OK;
    }
    
    return ret;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_WaitUS(const uint16 waitUSTime)
{
	const uint32	startTime = LIB_GetFreeRunCount1us();
	uint32			i;

	for (i = 0U; i < ((uint32)waitUSTime * D_ETHSWT_SWIC_CLOCK_PER_US); i++) {      /* 1ループ1クロック前提（実際はそれ以上のクロックがある）にガード実装 */
		const uint32	nowTime = LIB_GetFreeRunCount1us();
		if ((nowTime - startTime) > (uint32)waitUSTime)	{ break; }                  /* ラップアラウンドはC規格上問題なし */
	}

	return;
}


/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowSetRegister(void)
{
    /* - OEM Custom：レジスタ設定が可能な状態か確認する - */
    Std_ReturnType swicAvailable = E_NOT_OK;
    Std_ReturnType swicPowerStatus;
    uint8           sail_resout_n;
    uint8           aoss_sleep_entry_exit;

    swicPowerStatus = EthSwt_SWIC_PWR_GetSWICPower();
    sail_resout_n = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_SAIL_RES);
    aoss_sleep_entry_exit = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_AOSS_SLP);
    /* DIN2_Stateビットの確認も後に加える */

    if (swicPowerStatus == STD_ON && sail_resout_n == STD_HIGH && aoss_sleep_entry_exit == STD_LOW) {
        swicAvailable = E_OK;
    }

    return swicAvailable;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_RstDtct.c                                           */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_RstDtct_IsNeedDtct()
{
    Std_ReturnType  ret = E_NOT_OK;
    uint8           readResult;
    uint32          din2_stat;
    uint8           sail_resout_n;
    uint8           aoss_sleep_entry_exit;
    
    LIB_DI();
    readResult  = u1_g_iVDshReabyDid(IVDSH_DID_REA_VM2TO3_DIN2_STAT, &din2_stat, (uint16)D_ETHSWT_SWIC_CFG_DIN2STAT_SIZE);
    LIB_EI();
    sail_resout_n = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_SAIL_RES);
    aoss_sleep_entry_exit = u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_AOSS_SLP);

    if(readResult != IVDSH_NO_REA) {    /* DIN2_STAT情報取得の条件確認 */
        if (din2_stat == D_ETHSWT_SWIC_CFG_MCUPMIC_ON
            && sail_resout_n == STD_HIGH
            && aoss_sleep_entry_exit == STD_LOW) {
            ret = E_OK;
        }
    }

    return ret;
}
