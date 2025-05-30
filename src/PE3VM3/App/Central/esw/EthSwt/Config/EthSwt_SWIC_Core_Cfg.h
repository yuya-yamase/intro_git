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

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_PWR */
#define D_ETHSWT_SWIC_PWR_CYCLE                     (5U)
#define D_ETHSWT_SWIC_PWR_ON_WAIT                   (105U)  /* 35ms(T8) + 60ms(T9) + 5ms(PwrCtrlが先に動作するため) + (CPUクロック誤差考慮) */
#define D_ETHSWT_SWIC_PWR_ASSERT_WAIT               (5U)    /* 1ms(T1) + (CPUクロック誤差) */
#define D_ETHSWT_SWIC_PWR_DEASSERT_WAIT             (20U)   /* 15ms(T2) + (CPUクロック誤差) */

typedef struct {
    void (*timerUpdateFunc)(void);                      /* 1ms高優先でタイマー更新する関数 */
    Std_ReturnType (*checkActionFunc)(void);            /* backgroundで実行するかどうか見る箇所 */
    Std_ReturnType (*ActionFunc)(uint32 * const errFactor);                 /* backgroundで実施する箇所 */
} EthSwt_Func;

extern const EthSwt_Func G_ETHSWT_SWIC_ACTIVE_FUNC_LIST[];

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
