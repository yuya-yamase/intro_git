/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_Indicator.c                                           */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
/* - OEM Custom --------- */

/* - OEM Custom --------- */
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
void EthDLC_Indicate_Init (void)
{
/* - OEM Custom --------- */
	/* ChipComへDoIP起動条件 OFF通知*/

/* - OEM Custom --------- */
}
/* -------------------------------------------------------------------------- */
void EthDLC_Indicate_DLCOn (void)
{
/* - OEM Custom --------- */
	/* ChipComへDoIP起動条件 ON通知*/

/* - OEM Custom --------- */

	return;
}
/* -------------------------------------------------------------------------- */
void EthDLC_Indicate_DLCOff (void)
{
/* - OEM Custom --------- */
	/* ChipComへDoIP起動条件 OFF通知*/

/* - OEM Custom --------- */

	return;
}
/* -------------------------------------------------------------------------- */
#ifndef EthDLC_Indicate_ACTLOn
void EthDLC_Indicate_ACTLOn (void)
{
/* - OEM Custom --------- */
/* - OEM Custom --------- */

	return;
}
#endif /* EthDLC_Indicate_ACTLOn */
/* -------------------------------------------------------------------------- */
#ifndef EthDLC_Indicate_ACTLOff
void EthDLC_Indicate_ACTLOff (void)
{
/* - OEM Custom --------- */
/* - OEM Custom --------- */

	return;
}
#endif /* EthDLC_Indicate_ACTLOff */
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
