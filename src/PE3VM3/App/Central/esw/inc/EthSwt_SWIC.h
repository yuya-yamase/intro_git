#ifndef ETHSWT_SWIC_H
#define ETHSWT_SWIC_H
#include <Std_Types.h>
#include <EthSwt_BSW_define.h>		/* C-DC MCUÇ…ÇÕBSW ETHÇ™ç⁄Ç¡ÇƒÇ¢Ç»Ç¢ÇΩÇﬂÅAë„ÇÌÇËÇ…íËã` */
#include <EthSwt.h>

void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr);
void EthSwt_SWIC_DeInit(void);
Std_ReturnType EthSwt_SWIC_SetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType PortMode);
Std_ReturnType EthSwt_SWIC_GetSwitchPortMode(uint8 SwitchIdx, uint8 SwitchPortIdx, Eth_ModeType *SwitchModePtr);
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType *LinkStatePtr);
Std_ReturnType EthSwt_SWIC_PortLinkStateRequest(uint8 SwitchIdx, uint8 PortIdx, EthTrcv_LinkStateType PortLinkState);
Std_ReturnType EthSwt_SWIC_CheckWakeup(uint8 SwitchIdx);
Std_ReturnType EthSwt_SWIC_GetSwitchPortWakeupReason(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_WakeupReasonType *Reason);
Std_ReturnType EthSwt_SWIC_PortEnableTimeStamp(uint8 CtrlIdx, Eth_BufIdxType BufIdx, EthSwt_MgmtInfoType *MgmtInfoPtr);
Std_ReturnType EthSwt_SWIC_SetMgmtInfo(uint8 CtrlIdx, Eth_BufIdxType BufIdx, const EthSwt_MgmtInfoType *MgmtInfoPtr);
Std_ReturnType EthSwt_SWIC_GetRxMgmtObject(uint8 CtrlIdx, const Eth_DataType *DataPtr, EthSwt_MgmtObjectType* *MgmtObjectPtr);
Std_ReturnType EthSwt_SWIC_GetTxMgmtObject(uint8 CtrlIdx, Eth_BufIdxType BufIdx, EthSwt_MgmtObjectType* *MgmtObjectPtr);
void EthSwt_SWIC_MainFunction(void);
void EthSwt_SWIC_MainFunction1MS(void);
// void EthSwt_SWIC_MainFunction5MSpre(void);
void EthSwt_SWIC_BackgroundTask(void);
// void EthSwt_SWIC_ClearDTC(void);
// EthSwt_StateType EthSwt_SWIC_GetState(void);
// uint8 EthSwt_SWIC_GetDTC(void);
// uint8 EthSwt_SWIC_GetDTCDetail(void);
// Std_ReturnType EthSwt_SWIC_PortPhyResetRequest(const uint8 SwitchIdx, const uint8 SwitchPortIdx);
// Std_ReturnType EthSwt_SWIC_GetIDSInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint32 *const IDSInfo);
// Std_ReturnType EthSwt_SWIC_GetSqiValue(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint8 *const SqiValuePrt);

#endif /*ETHSWT_SWIC_H*/
