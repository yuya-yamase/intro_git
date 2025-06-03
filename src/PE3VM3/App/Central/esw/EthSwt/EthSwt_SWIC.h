#ifndef ETHSWT_SWIC_H
#define ETHSWT_SWIC_H
#include <Std_Types.h>
#include <EthSwt_BSW_define.h>		/* C-DC MCUÇ…ÇÕBSW ETHÇ™ç⁄Ç¡ÇƒÇ¢Ç»Ç¢ÇΩÇﬂÅAë„ÇÌÇËÇ…íËã` */
#include <EthSwt.h>

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr);
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType *LinkStatePtr);
void EthSwt_SWIC_HiProc(void);
void EthSwt_SWIC_LoProc(void);
void EthSwt_SWIC_BackgroundTask(void);

#endif /*ETHSWT_SWIC_H*/
