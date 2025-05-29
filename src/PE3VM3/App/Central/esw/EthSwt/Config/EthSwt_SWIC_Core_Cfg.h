/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Core_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_CORE_CFG_H
#define ETHSWT_SWIC_CORE_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
/* Common */
#include "EthSwt_BSW_define.h" /* モビコンでは Eth_GeneralTypes.h */
#define D_ETHSWT_SWIC_PERIOD                        (1U)
#define D_ETHSWT_SWIC_PORT_NUM                      (9U)
extern const Eth_ModeType G_ETHSWT_SWIC_PORT_MODE[D_ETHSWT_SWIC_PORT_NUM];

// #define D_ETHSWT_SWIC_PORT1_MODE                    ETH_MODE_ACTIVE /* A-DC Port */
// #define D_ETHSWT_SWIC_PORT2_MODE                    ETH_MODE_ACTIVE /* DCM Port */
// #define D_ETHSWT_SWIC_PORT3_MODE                    ETH_MODE_DOWN   /* 未使用 */
// #define D_ETHSWT_SWIC_PORT4_MODE                    ETH_MODE_DOWN   /* 未使用 */
// #define D_ETHSWT_SWIC_PORT5_MODE                    ETH_MODE_ACTIVE /* SAIL Port */
// #define D_ETHSWT_SWIC_PORT6_MODE                    ETH_MODE_DOWN   /* DLC Port */
// #define D_ETHSWT_SWIC_PORT7_MODE                    ETH_MODE_ACTIVE /* Linux Port */
// #define D_ETHSWT_SWIC_PORT8_MODE                    ETH_MODE_ACTIVE /* QNX Port */
// #define D_ETHSWT_SWIC_PORT9_MODE                    ETH_MODE_DOWN   /* 未使用 */

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_PWR */
#define D_ETHSWT_SWIC_PWR_CYCLE                     (5U)
#define D_ETHSWT_SWIC_PWR_ON_WAIT                   (105U)  /* 35ms(T8) + 60ms(T9) + 5ms(PwrCtrlが先に動作するため) + (CPUクロック誤差考慮) */
#define D_ETHSWT_SWIC_PWR_ASSERT_WAIT               (5U)    /* 1ms(T1) + (CPUクロック誤差) */
#define D_ETHSWT_SWIC_PWR_DEASSERT_WAIT             (20U)   /* 15ms(T2) + (CPUクロック誤差) */

void EthSwt_SWIC_PWR_SetGPIOMode(void);
void EthSwt_SWIC_PWR_SetSpiMode(void);
void EthSwt_SWIC_PWR_PowerOn(void);
void EthSwt_SWIC_PWR_PowerOff(void);
void EthSwt_SWIC_PWR_ResetAssert(void);
void EthSwt_SWIC_PWR_ResetDeassert(void);
/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_STM */
Std_ReturnType EthSwt_SWIC_STM_CheckAvailable(void);
Std_ReturnType EthSwt_SWIC_STM_CanRelay(void);

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_Init */
#define g_regListSeqSetP3ActDis NULL_PTR
#define g_regListSeqSetP4ActDis NULL_PTR
#define g_regListSeqSetP9ActDis NULL_PTR

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_Link */
#define D_ETHSWT_SWIC_LINK_FAST_GET_TMO             (70U)
#define D_ETHSWT_SWIC_LINK_GET_CYCLE                (100U)

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_CORE_CFG_H */
/* -------------------------------------------------------------------------- */
