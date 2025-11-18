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
#include <EthSwt_SWIC_PWR.h>
#include <PwrCtrl_Main.h>
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
    Std_ReturnType  din2_stat = STD_OFF;

    din2_stat = STD_ON;                  /* �b�� �̂��ɑ�API�ɕύX */

    if (din2_stat == STD_ON) {
        ret = STD_ON;
    }

    return ret;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetGPIOMode(void)
{
    /* - OEM Custom�FSPI�ʐM���C����GPIO���[�h�֕ύX - */
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
    /* - OEM Custom�FSPI�ʐM���C����SPI���[�h�֕ύX - */
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
    /* - OEM Custom�FSWIC�d��ON - */
    /* ETHER_PWR_EN��High�ݒ肵����ɁAETH_U2A_RESET_N��High�ݒ� */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);                         /* ETHER_PWR_EN */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetPowerOff(void)
{
    /* - OEM Custom�FSWIC�d��OFF - */
    /* ETH_U2A_RESET_N��Low�ݒ肵����ɁAETHER_PWR_EN��Low�ݒ� */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW);                          /* ETHER_PWR_EN */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetResetAssert(void)
{
    /* - OEM Custom�FSWIC���Z�b�g�A�T�[�g - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */

    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Cfg_SetResetDeassert(void)
{
    /* - OEM Custom�FSWIC���Z�b�g�f�B�A�T�[�g - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */
    
    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowRelay(void)
{
    /* - OEM Custom�F���p���\�ȏ�Ԃ��m�F���� - */
    Std_ReturnType ret = E_NOT_OK;
    volatile Std_ReturnType result;
    result = u1_g_VISPwrGetEthChPwr();
    if (result == STD_ON) {
        ret = E_OK;
    }
    
    return ret;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Cfg_AllowSetRegister(void)
{
    /* - OEM Custom�F���W�X�^�ݒ肪�\�ȏ�Ԃ��m�F���� - */
    /* C-DC�̏ꍇ�́APWR���W���[���ɉ����ASAIL_RESOUT_N���m�F���� */
    Std_ReturnType swicAvailable = E_NOT_OK;
    Std_ReturnType swicPowerStatus;
    Std_ReturnType sailResoutN;

    swicPowerStatus = EthSwt_SWIC_PWR_GetSWICPower();
    sailResoutN = Dio_ReadChannel(DIO_ID_PORT8_CH8);

    if (swicPowerStatus == STD_ON && sailResoutN == STD_ON) {
        swicAvailable = E_OK;
    }

    return swicAvailable;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_RstDtct.c                                           */
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Define.h"
Std_ReturnType EthSwt_SWIC_RstDtct_IsNeedDtct()
{
    Std_ReturnType result = E_NOT_OK;
    Std_ReturnType ether_pwr_en =           Dio_ReadChannel(DIO_ID_PORT8_CH8);
    uint8 sail_resout_n =                   u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_SAIL_RES);
    Std_ReturnType aoss_sleep_entry_exit =  u1_g_PwrCtrlMainGetPinInfo(PWRCTRL_MAIN_PINID_AOSS_SLP);


    if (STD_HIGH == ether_pwr_en)
    {
        if (STD_HIGH == sail_resout_n)
        {
            if (STD_LOW == aoss_sleep_entry_exit)
            {
                // リセット検出確認要求あり
                result = E_OK;
            }
        }
    }

    return result;
}
