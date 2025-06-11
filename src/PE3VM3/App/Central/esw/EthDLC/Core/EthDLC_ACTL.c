/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_ACTL.c                                                */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDLC_Cfg.h>
#include "EthDLC_ACTL.h"
/* -------------------------------------------------------------------------- */
#define D_ETHDLC_ACTL_TIME_CLEAR		(0UL)
#define D_ETHDLC_ACTL_ON_FILTER_CNT		(D_ETHDLC_ACTL_ON_FILTER  / 5UL)
#define D_ETHDLC_ACTL_OFF_FILTER_CNT	(D_ETHDLC_ACTL_OFF_FILTER / 5UL)
/* -------------------------------------------------------------------------- */
typedef struct
{
	uint8		Status;		/* decisioned signal status : STD_LOW , STD_HIGH */
	uint32		TimeON;		/* ON  decision waiting tick */
	uint32		TimeOFF;	/* OFF decision waiting tick */
} S_ETHDLC_ACTL;
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_VAR
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
static S_ETHDLC_ACTL	G_ETHDLC_ACTL;
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_VAR
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
static void ethdlc_actl_TimeCount(uint8 status);
static void ethdlc_actl_DecisionStatus(void);
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_ACTL_Init>                                       */
/* -------------------------------------------------------------------------- */
void EthDLC_ACTL_Init (void)
{
	G_ETHDLC_ACTL.Status  = STD_OFF;
	G_ETHDLC_ACTL.TimeON  = D_ETHDLC_ACTL_TIME_CLEAR;
	G_ETHDLC_ACTL.TimeOFF = D_ETHDLC_ACTL_TIME_CLEAR;

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_ACTL_Observe>                                    */
/* -------------------------------------------------------------------------- */
void EthDLC_ACTL_Observe (void)
{
	Std_ReturnType	status;


	status = ETHDLC_GET_ACTL_SIGNAL;

	ethdlc_actl_TimeCount(status);

	ethdlc_actl_DecisionStatus();

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_ACTL_GetState>                                   */
/* -------------------------------------------------------------------------- */
Std_ReturnType EthDLC_ACTL_GetState (void)
{
	return G_ETHDLC_ACTL.Status;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_actl_TimeCount>                                  */
/* -------------------------------------------------------------------------- */
static void ethdlc_actl_TimeCount (uint8 status)
{
	/* ON/OFF status count */
	if (status == STD_LOW)
	{	/* ON detecting */
		G_ETHDLC_ACTL.TimeON  ++;
		G_ETHDLC_ACTL.TimeOFF = D_ETHDLC_ACTL_TIME_CLEAR;
	}
	else
	{	/* OFF detecting */
		G_ETHDLC_ACTL.TimeON  = D_ETHDLC_ACTL_TIME_CLEAR;
		G_ETHDLC_ACTL.TimeOFF ++;
	}

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_actl_DecisionStatus>                             */
/* -------------------------------------------------------------------------- */
static void ethdlc_actl_DecisionStatus (void)
{
	if (G_ETHDLC_ACTL.TimeOFF > D_ETHDLC_ACTL_OFF_FILTER_CNT)
	{	/* decision OFF */
		G_ETHDLC_ACTL.Status  = STD_OFF;
		G_ETHDLC_ACTL.TimeOFF = D_ETHDLC_ACTL_OFF_FILTER_CNT;
	}
	else
	if (G_ETHDLC_ACTL.TimeON > D_ETHDLC_ACTL_ON_FILTER_CNT)
	{	/* decision ON */
		G_ETHDLC_ACTL.Status = STD_ON;
		G_ETHDLC_ACTL.TimeON = D_ETHDLC_ACTL_ON_FILTER_CNT;
	}
	else
	{	/* no changed */
		/* do nothing */
	}

	return;
}
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
