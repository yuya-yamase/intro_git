/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Pwr.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "EthSwt_SWIC_Pwr.h"
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_ST_WAIT               (0U)
#define D_ETHSWT_SWIC_PWR_ST_TURNING_ON         (1U)
#define D_ETHSWT_SWIC_PWR_ST_AVAILABLE          (2U)
#define D_ETHSWT_SWIC_PWR_ST_NUM                (3U)
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_EV_SAIL_ON            (0U)
#define D_ETHSWT_SWIC_PWR_EV_SAIL_OFF           (1U)
#define D_ETHSWT_SWIC_PWR_EV_NUM                (2U)
/* -------------------------------------------------------------------------- */
uint32 swicState;
uint32 timerForSWIC;
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_drive_stm(uint32 event);
static uint32 ethswt_swic_pwr_act_pminOn(void);
static uint32 ethswt_swic_pwr_act_timerCount(void);
static uint32 ethswt_swic_pwr_act_spiModeOn(void);
static uint32 ethswt_swic_pwr_act_pmicOff(void);
static uint32 ethswt_swic_pwr_act_stop(void);
static uint32 ethswt_swic_pwr_act_None(void);
static void ethswt_swic_pwr_spiMode(void);
static void ethswt_swic_pwr_gpioMode(void);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Pwr_Init(void)
{
    swicState = D_ETHSWT_SWIC_PWR_ST_WAIT;
    timerForSWIC = 0;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_Pwr_HiProc(void)
{
    uint8 sail_resout_n;

    sail_resout_n = ETHSWT_SWIC_PWR_GET_SAIL_RESOUT_N;
    if (sail_resout_n == STD_LOW) {
        ethswt_swic_pwr_drive_stm(D_ETHSWT_SWIC_PWR_EV_SAIL_OFF);
    } else {
        ethswt_swic_pwr_drive_stm(D_ETHSWT_SWIC_PWR_EV_SAIL_ON);
    }

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_Pwr_GetSWICState(void)
{
    Std_ReturnType ret;
    
    switch (swicState) {
    case D_ETHSWT_SWIC_PWR_ST_WAIT:
    case D_ETHSWT_SWIC_PWR_ST_TURNING_ON:
        ret = STD_OFF;
        break;
    case D_ETHSWT_SWIC_PWR_ST_AVAILABLE:
        ret = STD_ON;
        break;
    default:
        break;
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
typedef uint32 (*PWR_ACT)(void);
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_drive_stm(uint32 event)
{
    static const PWR_ACT   action_tbl[D_ETHSWT_SWIC_PWR_EV_NUM][D_ETHSWT_SWIC_PWR_ST_NUM] =
                            /*  { { S0:ST_WAIT                      , S1:ST_TURNING_ON                  , S2:AVAILABLE                      }} */
    /* EV_SAIL_ON           */  { { ethswt_swic_pwr_act_pminOn      , ethswt_swic_pwr_act_timerCount    , ethswt_swic_pwr_act_None          }
    /* EV_SAIL_OFF          */  , { ethswt_swic_pwr_act_None        , ethswt_swic_pwr_act_pmicOff       , ethswt_swic_pwr_act_stop          }
                                };

    swicState = action_tbl[event][swicState]();

    return;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_pminOn(void)
{
    ETHSWT_SWIC_PWR_ETHER_PWR_EN_HIGH;
    ETHSWT_SWIC_PWR_ETH_U2A_RESET_N_HIGH;
    timerForSWIC = 0;

    return D_ETHSWT_SWIC_PWR_ST_TURNING_ON;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_timerCount(void)
{
    uint32 next = D_ETHSWT_SWIC_PWR_ST_TURNING_ON;

    timerForSWIC += D_ETHSWT_SWIC_PWR_TICK_TIME;
    if (timerForSWIC >= D_ETHSWT_SWIC_PWR_WAITE_SPI) {
        next = ethswt_swic_pwr_act_spiModeOn();
    }

    return next;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_spiModeOn(void)
{
    ethswt_swic_pwr_spiMode();

    return D_ETHSWT_SWIC_PWR_ST_AVAILABLE;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_pmicOff(void)
{
    ETHSWT_SWIC_PWR_ETH_U2A_RESET_N_LOW;
    ETHSWT_SWIC_PWR_ETHER_PWR_EN_LOW;

    return D_ETHSWT_SWIC_PWR_ST_WAIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_stop(void)
{
    ethswt_swic_pwr_gpioMode();
    ETHSWT_SWIC_PWR_ETH_U2A_RESET_N_LOW;
    ETHSWT_SWIC_PWR_ETHER_PWR_EN_LOW;

    return D_ETHSWT_SWIC_PWR_ST_WAIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_None(void)
{
    /* do nothing */

    return swicState;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_spiMode(void)
{
    ETHSWT_SWIC_PWR_ETHERSW_TXD_SPI;
    ETHSWT_SWIC_PWR_ETHERSW_RXD_SPI;
    ETHSWT_SWIC_PWR_ETHERSW_CS_SPI;
    ETHSWT_SWIC_PWR_ETHERSW_CLK_SPI;

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_gpioMode(void)
{
    ETHSWT_SWIC_PWR_ETHERSW_TXD_GPIO;
    ETHSWT_SWIC_PWR_ETHERSW_RXD_GPIO;
    ETHSWT_SWIC_PWR_ETHERSW_CS_GPIO;
    ETHSWT_SWIC_PWR_ETHERSW_CLK_GPIO;

    return;
}
