/* -------------------------------------------------------------------------- */
/* file name   : EthDLC.c                                                     */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthDLC_ACTL.h>
#include <EthDLC_STM.h>
#include <EthDLC_Cfg.h>
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
void EthDLC_Init (void)
{
	EthDLC_ACTL_Init();
	EthDLC_STM_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthDLC_LoProc (void)
{
	EthDLC_ACTL_Observe();
	EthDLC_STM_LoProc();
	EthDLC_Indicate_Cycle();

	return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthDLC_GetACTLState (void)
{
	return EthDLC_ACTL_GetState();
}
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
