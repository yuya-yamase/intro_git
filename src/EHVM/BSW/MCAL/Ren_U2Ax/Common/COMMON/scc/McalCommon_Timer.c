/* Common-r04-r04-307 */
/************************************************************************************************/
/*																								*/
/*		McalCommon_lib(Timer)																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"McalCommon_Timer.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
typedef	struct {
	uint8	u1Ck0;
	uint8	u1Ck1;
	uint8	u1Ck2;
	uint8	u1Ck3Pre;
	uint8	u1Ck3Brs;
} Mcalcommon_PsSet;

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#define MCALCOMMON_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "McalCommon_MemMap.h"

static VAR(Mcalcommon_PsSet, MCALCOMMON_CODE_VAR_NO_INIT) s_stPsConfigDat[MCALCOMMON_UNIT_MAX];

#define MCALCOMMON_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "McalCommon_MemMap.h"

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define MCALCOMMON_START_SEC_CODE_GLOBAL
#include "McalCommon_MemMap.h"

/************************************************************************************************/
/* Service name		:	mcalcommon_SetPrescalerCfgVal											*/
/* Reentrancy		:	Non-Reentrant															*/
/* Parameters(in)	:	t_enUnit : unit															*/
/* Parameters(in)	:	t_enType : Prescale type												*/
/* Parameters(in)	:	t_u1Value : set value													*/
/* Return value		:	none																	*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(void, MCALCOMMON_CODE) mcalcommon_SetPrescalerCfgVal(
	VAR(Mcalcommon_PsUnit, AUTOMATIC)	t_enUnit,
	VAR(Mcalcommon_PsType, AUTOMATIC)	t_enType,
	VAR(uint8, AUTOMATIC)				t_u1Value)
{
	switch (t_enType)
	{
		default:
		case MCALCOMMON_PS_CK0:
			s_stPsConfigDat[(uint32)t_enUnit].u1Ck0 = t_u1Value;
			break;

		case MCALCOMMON_PS_CK1:
			s_stPsConfigDat[(uint32)t_enUnit].u1Ck1 = t_u1Value;
			break;

		case MCALCOMMON_PS_CK2:
			s_stPsConfigDat[(uint32)t_enUnit].u1Ck2 = t_u1Value;
			break;

		case MCALCOMMON_PS_CK3_PRE:
			s_stPsConfigDat[(uint32)t_enUnit].u1Ck3Pre = t_u1Value;
			break;

		case MCALCOMMON_PS_CK3_BRS:
			s_stPsConfigDat[(uint32)t_enUnit].u1Ck3Brs = t_u1Value;
			break;
	}
}

/************************************************************************************************/
/* Service name		:	mcalcommon_GetPrescalerCfgVal											*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	t_enUnit : unit															*/
/* Parameters(in)	:	t_enType : Prescale type												*/
/* Return value		:	Prescale value															*/
/* Limitation		:	none																	*/
/************************************************************************************************/
FUNC(uint8, MCALCOMMON_CODE) mcalcommon_GetPrescalerCfgVal(
	VAR(Mcalcommon_PsUnit, AUTOMATIC)	t_enUnit,
	VAR(Mcalcommon_PsType, AUTOMATIC)	t_enType)
{
	VAR(uint8, AUTOMATIC)	t_u1Value;

	switch (t_enType)
	{
		default:
		case MCALCOMMON_PS_CK0:
			t_u1Value = s_stPsConfigDat[(uint32)t_enUnit].u1Ck0;
			break;

		case MCALCOMMON_PS_CK1:
			t_u1Value = s_stPsConfigDat[(uint32)t_enUnit].u1Ck1;
			break;

		case MCALCOMMON_PS_CK2:
			t_u1Value = s_stPsConfigDat[(uint32)t_enUnit].u1Ck2;
			break;

		case MCALCOMMON_PS_CK3_PRE:
			t_u1Value = s_stPsConfigDat[(uint32)t_enUnit].u1Ck3Pre;
			break;

		case MCALCOMMON_PS_CK3_BRS:
			t_u1Value = s_stPsConfigDat[(uint32)t_enUnit].u1Ck3Brs;
			break;
	}

	return (t_u1Value);
}

#define MCALCOMMON_STOP_SEC_CODE_GLOBAL
#include "McalCommon_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
