/* -------------------------------------------------------------------------- */
/* file name	:	EthSW_Task.c											  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthSwt.h>
#include <EthSW_Task.h>
#include <EthSwt_SWIC.h>
#include "EthDLC.h"
#include "EthSwt_Data.h"
/* -------------------------------------------------------------------------- */
void EthSW_StaBonInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthDLC_Init();
	EthSwt_Data_Init();
	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaRstInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthDLC_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaWkupInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);
	EthDLC_Init();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_MediumTask (void)
{
	EthDLC_LoProc();
	EthSwt_Data_MidProc();
	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_HighTask (void)
{
	EthSwt_SWIC_MainFunction();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_LowTask (void)
{
	EthSwt_SWIC_BackgroundTask();
	return;
}
