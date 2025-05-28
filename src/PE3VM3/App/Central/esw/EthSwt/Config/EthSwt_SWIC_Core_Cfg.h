/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_Core_Cfg.h                                       */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_CORE_CFG_H
#define ETHSWT_SWIC_CORE_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
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
#endif /* ETHSWT_SWIC_CORE_CFG_H */
/* -------------------------------------------------------------------------- */
