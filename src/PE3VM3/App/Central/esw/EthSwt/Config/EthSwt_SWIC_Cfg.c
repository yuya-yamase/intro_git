/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Cfg.c                                       */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Cfg.h"
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

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_PWR.c                                               */
/* -------------------------------------------------------------------------- */
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>
void EthSwt_SWIC_SetGPIOMode(void)
{
    /* - OEM Custom：SPI通信ラインをGPIOモードへ変更 - */
    Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_DI );         /* ETHERSW-RXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_DO_LO );      /* ETHERSW-CLK */
    Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_DO_LO );      /* ETHERSW-TXD */
    Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_DO_LO );      /* ETHERSW-CS */

    return;
}
void EthSwt_SWIC_SetSPIMode(void)
{
    /* - OEM Custom：SPI通信ラインをSPIモードへ変更 - */
    Port_SetPinMode(PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI);      /* ETHERSW-RXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC);      /* ETHERSW-CLK */
    Port_SetPinMode(PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO);      /* ETHERSW-TXD */
    Port_SetPinMode(PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0);    /* ETHERSW-CS */

    return;
}
void EthSwt_SWIC_SetPowerOn(void)
{
    /* - OEM Custom：SWIC電源ON - */
    /* ETHER_PWR_ENをHigh設定した後に、ETH_U2A_RESET_NをHigh設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH);                         /* ETHER_PWR_EN */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */

    return;
}
void EthSwt_SWIC_SetPowerOff(void)
{
    /* - OEM Custom：SWIC電源OFF - */
    /* ETH_U2A_RESET_NをLow設定した後に、ETHER_PWR_ENをLow設定 */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */
    Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW);                          /* ETHER_PWR_EN */

    return;
}
void EthSwt_SWIC_SetResetAssert(void)
{
    /* - OEM Custom：SWICリセットアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_LOW);                           /* ETH_U2A_RESET_N */

    return;
}
void EthSwt_SWIC_SetResetDeassert(void)
{
    /* - OEM Custom：SWICリセットディアサート - */
    Dio_WriteChannel(DIO_ID_APORT4_CH1, STD_HIGH);                          /* ETH_U2A_RESET_N */
    
    return;
}

/* -------------------------------------------------------------------------- */
/* Config for EthSwt_SWIC_STM.c                                               */
/* -------------------------------------------------------------------------- */
#include <VIS.h>
Std_ReturnType EthSwt_SWIC_AllowRelay(void)
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
/* Config for EthSwt_SWIC_STM.c                                               */
/* Config for EthSwt_SWIC_Reg.c                                               */
/* -------------------------------------------------------------------------- */
#include <Dio.h>
#include <Dio_Symbols.h>
#include <EthSwt_SWIC_PWR.h>
Std_ReturnType EthSwt_SWIC_AllowSetRegister(void)
{
    /* - OEM Custom：レジスタ設定が可能な状態か確認する - */
    /* C-DCの場合は、PWRモジュールに加え、SAIL_RESOUT_Nも確認する */
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
/* Config for EthSwt_SWIC_MIB.c                                               */
/* -------------------------------------------------------------------------- */
#include "EthSwt_SWIC_Define.h"
Std_ReturnType EthSwt_SWIC_RstDtct_IsNeedDtct()
{
    Std_ReturnType result = E_NOT_OK;
    Std_ReturnType ether_pwr_en =           Dio_ReadChannel(DIO_ID_PORT8_CH8);
    Std_ReturnType sail_resout_n =          Dio_ReadChannel(DIO_ID_APORT4_CH11);
    Std_ReturnType aoss_sleep_entry_exit =  Dio_ReadChannel(DIO_ID_PORT17_CH0);


    if (STD_HIGH == ether_pwr_en)
    {
        if (STD_HIGH == sail_resout_n)
        {
            if (STD_HIGH == aoss_sleep_entry_exit)
            {
                // リセット検出確認要求あり
                result = E_OK;
            }
        }
    }

    return result;
}