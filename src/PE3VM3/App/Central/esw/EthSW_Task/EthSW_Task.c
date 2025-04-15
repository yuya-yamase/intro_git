/* -------------------------------------------------------------------------- */
/* file name	:	EthSW_Task.c											  */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthSwt.h>
#include <EthSW_Task.h>
#include <EthSwt_SWIC.h>
/* -------------------------------------------------------------------------- */
void EthSW_StaBonInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaRstInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_StaWkupInit(void)
{
	EthSwt_SWIC_Init(NULL_PTR);

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_MediumTask (void)
{
	
	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_HighTask (void)
{
	EthSwt_MainFunction();

	return;
}
/* -------------------------------------------------------------------------- */
void EthSW_LowTask (void)
{
	
	return;
}
