/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Core_Cfg.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_CORE_CFG_H
#define ETHDLC_CORE_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Config for EthDLC_ACTL.c                                                   */
/* -------------------------------------------------------------------------- */
#include <Dio.h>

#define ETHDLC_GET_ACTL_SIGNAL              Dio_ReadChannel(DIO_ID_PORT10_CH14)
#define D_ETHDLC_ACTL_ON_FILTER		        (15U)		/* [ms] */
#define D_ETHDLC_ACTL_OFF_FILTER	        (210U)		/* [ms] */

/* -------------------------------------------------------------------------- */
/* Config for EthDLC_STM.c                                                    */
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC.h>
#include <EthDLC.h>

Std_ReturnType EthDLC_Power_GetState(void);
Std_ReturnType EthDLC_Port_GetState(void);
#define EthDLC_Port_Active()                (void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_ACTIVE)
#define EthDLC_Port_Down()                  (void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_DOWN)
void EthDLC_Indicate_DLCOn(void);
void EthDLC_Indicate_DLCOff(void);
#define EthDLC_Indicate_ACTLOn()
#define EthDLC_Indicate_ACTLOff()
void EthDLC_Indicate_Cycle(void);

#endif /* ETHDLC_CORE_CFG_H */
