/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Pwr.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_PWR_H
#define ETHSWT_SWIC_PWR_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <Dio.h>
#include <Dio_Symbols.h>
#include <Port_Cfg.h>
#include <Port.h>
/* -------------------------------------------------------------------------- */
#define ETHSWT_SWIC_PWR_GET_SAIL_RESOUT_N       Dio_ReadChannel(DIO_ID_PORT8_CH8)

#define ETHSWT_SWIC_PWR_ETHER_PWR_EN_HIGH       Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_HIGH)
#define ETHSWT_SWIC_PWR_ETHER_PWR_EN_LOW        Dio_WriteChannel(DIO_ID_APORT4_CH11, STD_LOW)
#define ETHSWT_SWIC_PWR_ETH_U2A_RESET_N_HIGH    Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_HIGH)
#define ETHSWT_SWIC_PWR_ETH_U2A_RESET_N_LOW     Dio_WriteChannel( DIO_ID_APORT4_CH1, STD_LOW)

#define ETHSWT_SWIC_PWR_ETHERSW_TXD_SPI         Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_MSPI0SO )
#define ETHSWT_SWIC_PWR_ETHERSW_RXD_SPI         Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_MSPI0SI )
#define ETHSWT_SWIC_PWR_ETHERSW_CS_SPI          Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_MSPI0CSS0 )
#define ETHSWT_SWIC_PWR_ETHERSW_CLK_SPI         Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_MSPI0SC )
#define ETHSWT_SWIC_PWR_ETHERSW_TXD_GPIO        Port_SetPinMode( PORT_ID_PORT2_PIN13, PORT_MODE_CFG_P2_13_DO_LO )
#define ETHSWT_SWIC_PWR_ETHERSW_RXD_GPIO        Port_SetPinMode( PORT_ID_PORT2_PIN11, PORT_MODE_CFG_P2_11_DI )
#define ETHSWT_SWIC_PWR_ETHERSW_CS_GPIO         Port_SetPinMode( PORT_ID_PORT2_PIN14, PORT_MODE_CFG_P2_14_DO_LO )
#define ETHSWT_SWIC_PWR_ETHERSW_CLK_GPIO        Port_SetPinMode( PORT_ID_PORT2_PIN12, PORT_MODE_CFG_P2_12_DO_LO )
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_TICK_TIME             (1U)    /* periodic time[ms]	*/
#define D_ETHSWT_SWIC_PWR_WAITE_SPI             (65U)   /* T7(30ms)+T8(35ms) = 65ms */          //Åö åÎç∑ÇÇ‹Çæçló∂ÇµÇƒÇ»Ç¢
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Pwr_Init(void);
void EthSwt_SWIC_Pwr_HiProc(void);
Std_ReturnType EthSwt_SWIC_Pwr_GetSWICState(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_PWR_H */
/* -------------------------------------------------------------------------- */
