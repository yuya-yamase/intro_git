/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Cfg.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_CFG_H
#define ETHDLC_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <Dio.h>
#include <EthSwt_SWIC.h>
#include <EthDLC.h>
/* -------------------------------------------------------------------------- */
/* Config for EthDLC_ACTL.c                                                   */
/* -------------------------------------------------------------------------- */
#define ETHDLC_GET_ACTL_SIGNAL              Dio_ReadChannel(DIO_ID_PORT10_CH14)
#define D_ETHDLC_ACTL_ON_FILTER		        (15U)		/* [ms] */
#define D_ETHDLC_ACTL_OFF_FILTER	        (210U)		/* [ms] */

/* -------------------------------------------------------------------------- */
/* Config for EthDLC_STM.c                                                    */
/* -------------------------------------------------------------------------- */
#define EthDLC_Power_GetState()             (STD_ON)
Std_ReturnType EthDLC_Port_GetState(void);
#define EthDLC_Port_Active()                (void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_ACTIVE)
#define EthDLC_Port_Down()                  (void)EthSwt_SWIC_SetSwitchPortMode(D_ETH_SWITCH_DLC, D_ETH_PORT_DLC, ETH_MODE_DOWN)
#define EthDLC_Indicate_DLCOn()
#define EthDLC_Indicate_DLCOff()
#define EthDLC_Indicate_ACTLOn()
#define EthDLC_Indicate_ACTLOff()
void EthDLC_Indicate_Cycle(void);

#endif /* ETHDLC_CFG_H */
