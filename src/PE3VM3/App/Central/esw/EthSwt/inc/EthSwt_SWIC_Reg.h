#ifndef ETHSWT_SWIC_REG_H
#define ETHSWT_SWIC_REG_H
#include <Std_Types.h>
#include <EthSwt_SWIC.h>

void EthSwt_SWIC_Reg_Init(void);
void EthSwt_SWIC_Port1ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
void EthSwt_SWIC_Port2ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
void EthSwt_SWIC_Port5ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
void EthSwt_SWIC_Port6ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
void EthSwt_SWIC_Port7ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
void EthSwt_SWIC_Port8ModeReq(const uint16 transreq_len, const uint8* const transreq_data);
#if 0    /* VN-HILSとしては不要なため無効化 */
Std_ReturnType EthSwt_SWIC_Reg_GetLinkState(const uint8 SwitchPortIdx, EthTrcv_LinkStateType *const LinkStatePtr);
Std_ReturnType EthSwt_SWIC_Reg_GetFrameInfo(const uint8 SwitchPortIdx, EthSwt_DiscardInfoType *const FrameInfoPtr);
Std_ReturnType EthSwt_SWIC_Reg_ClearFrameInfo(const uint8 SwitchPortIdx);
Std_ReturnType EthSwt_SWIC_Reg_GetIDS_TcamInfo(const uint8 SwitchPortIdx, uint32 *const IDSInfo);
Std_ReturnType EthSwt_SWIC_Reg_GetIDS_FiltFrmInfo(const uint8 SwitchPortIdx, uint32 *const IDSInfo);
#endif    /* VN-HILSとしては不要なため無効化 */
#endif /* ETHSWT_SWIC_REG_H */
