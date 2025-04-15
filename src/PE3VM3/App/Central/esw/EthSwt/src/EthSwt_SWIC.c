#include <Std_Types.h>
#include <EthSwt_SWIC.h>
#include <EthSwt.h>
#include "EthSwt_SWIC_Reg.h"
#include "EthSwt_SWIC_Pwr.h"

#define	ETHSWT_START_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
void EthSwt_SWIC_Init(const EthSwt_ConfigType *CfgPtr)
{
	(void)CfgPtr;

	EthSwt_SWIC_Pwr_Init();
	EthSwt_SWIC_Reg_Init();		/* èâä˙âªÇénÇﬂÇÈÇÃÇ≈ç≈å„ */
	
}

void EthSwt_SWIC_MainFunction(void)
{
	EthSwt_SWIC_Pwr_HiProc();
	EthSwt_SWIC_MainFunction1MS();
}

#if 0    /* ñ¢ëŒâû */
Std_ReturnType EthSwt_SWIC_GetLinkState(uint8 SwitchIdx, uint8 SwitchPortIdx, EthTrcv_LinkStateType* LinkStatePtr)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_GetLinkState(SwitchPortIdx, LinkStatePtr);
}
Std_ReturnType EthSwt_SWIC_ClearFrameInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_ClearFrameInfo(SwitchPortIdx);
}
Std_ReturnType EthSwt_SWIC_GetDiscardInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, EthSwt_DiscardInfoType *const DiscardInfoPtr)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_GetFrameInfo(SwitchPortIdx, DiscardInfoPtr);
}
Std_ReturnType EthSwt_SWIC_GetIDS_TcamInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint32 *const IDSInfo)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_GetIDS_TcamInfo(SwitchPortIdx, IDSInfo);
}
Std_ReturnType EthSwt_SWIC_GetIDS_FiltFrmInfo(const uint8 SwitchIdx, const uint8 SwitchPortIdx, uint32 *const IDSInfo)
{
	if (SwitchIdx != ETHSWT_SWIC_IDX)	{ return E_NOT_OK; }
	return EthSwt_SWIC_Reg_GetIDS_FiltFrmInfo(SwitchPortIdx, IDSInfo);
}
#endif    /*ñ¢ëŒâû */
#define	ETHSWT_STOP_SEC_CODE
#include <EthSwt_SWIC_MemMap.h>
