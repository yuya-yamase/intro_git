/* -------------------------------------------------------------------------- */
/* file name	:	EthSW_Task.c											  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthSwt.h>
#include <EthSW_Task.h>
#include <EthSwt_SWIC.h>
#include "EthDLC.h"
#include <EthSwt_Data.h>
/* -------------------------------------------------------------------------- */
void EthSW_StaBonInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthSwt_Data_Init();
	EthDLC_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaRstInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthSwt_Data_Init();
	EthDLC_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaWkupInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthSwt_Data_Init();
	EthDLC_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_MediumTask (void)
{
	EthDLC_LoProc();
	EthSwt_SWIC_LoProc();
	EthSwt_Data_LoProc();
	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_HighTask (void)
{
	EthSwt_SWIC_HiProc();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_BackgroundTask (void)
{
	EthSwt_SWIC_BackgroundTask();
	return;
}
