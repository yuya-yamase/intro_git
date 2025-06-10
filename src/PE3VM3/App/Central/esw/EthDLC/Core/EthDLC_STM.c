/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_STM.c                                                 */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include "EthDLC_STM.h"
#include <LIB.h>
#include "EthDLC_ACTL.h"
#include <EthDLC_Core_Cfg.h>
/* -------------------------------------------------------------------------- */
#define D_ETHDLC_ST_INIT_POINT		(0U)
#define D_ETHDLC_ST_LINK_DOWN		(1U)
#define D_ETHDLC_ST_LINK_WAIT		(2U)
#define D_ETHDLC_ST_LINK_UP			(3U)
#define D_ETHDLC_ST_NUM				(4U)

#define D_ETHDLC_EV_NONE			(0U)
#define D_ETHDLC_EV_INIT			(1U << 0U)
#define D_ETHDLC_EV_DLC_ON			(1U << 1U)
#define D_ETHDLC_EV_DLC_OFF 		(1U << 2U)
#define D_ETHDLC_EV_LINK_UP			(1U << 3U)
/* -------------------------------------------------------------------------- */
#define D_ETHDLC_RECORD_PER_ST_NUM	(2U)
/* -------------------------------------------------------------------------- */
typedef uint8 (*ETHDLC_ACT)(void);
typedef struct
{
	uint8		Event;
	ETHDLC_ACT	Action;
} S_ETHDLC_ACTION;
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_VAR
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
static uint8 G_DLC_Status;
static uint8 G_DLC_Event;
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_VAR
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
static void  ethdlc_dlc_event_set(uint8 event);
static uint8 ethdlc_dlc_event_get(void);
static uint8 ethdlc_dlc_get_dlc_on_event(void);
static uint8 ethdlc_dlc_get_linkup_event(void);
static void  ethdlc_dlc_action(uint8 event);
static uint8 ethdlc_dlc_action_None (void);
static uint8 ethdlc_dlc_action_Init(void);
static uint8 ethdlc_dlc_action_DLCOn(void);
static uint8 ethdlc_dlc_action_LinkUp(void);
static uint8 ethdlc_dlc_action_DLCOff(void);
/* -------------------------------------------------------------------------- */
#define EthDLC_START_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_STM_Init>                                        */
/* -------------------------------------------------------------------------- */
void EthDLC_STM_Init (void)
{
	G_DLC_Status = D_ETHDLC_ST_INIT_POINT;
	G_DLC_Event  = D_ETHDLC_EV_NONE;

	ethdlc_dlc_event_set(D_ETHDLC_EV_INIT);

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_STM_LoProc>                                      */
/* -------------------------------------------------------------------------- */
void EthDLC_STM_LoProc (void)
{
	uint8	event;


	event = ethdlc_dlc_event_get();

	ethdlc_dlc_action(event);

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_STM_GetDoIPStart>                                */
/* -------------------------------------------------------------------------- */
StatusType EthDLC_STM_GetDoIPStart(void)
{
	Std_ReturnType doipStart;

	switch(G_DLC_Status) {
	case D_ETHDLC_ST_LINK_UP:
		doipStart = E_OK;
		break;
	case D_ETHDLC_ST_INIT_POINT:
	case D_ETHDLC_ST_LINK_DOWN:
	case D_ETHDLC_ST_LINK_WAIT:
	default:
		doipStart = E_NOT_OK;
		break;
	}

	return doipStart;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_event_set>                                   */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_event_set (uint8 event)
{
	G_DLC_Event |= event;

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_event_get>                                   */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_event_get (void)
{
	uint8	event = G_DLC_Event;


	G_DLC_Event = D_ETHDLC_EV_NONE;

	event |= ethdlc_dlc_get_dlc_on_event();
	event |= ethdlc_dlc_get_linkup_event();

	return event;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_get_dlc_on_event>                            */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_get_dlc_on_event(void)
{
	uint8			event;
	Std_ReturnType	actl;
	Std_ReturnType	power;


	actl  = EthDLC_ACTL_GetState();
	power = EthDLC_Power_GetState();
	if ((actl == STD_ON) && (power == STD_ON))
	{
		event = D_ETHDLC_EV_DLC_ON;
	}
	else
	{
		event = D_ETHDLC_EV_DLC_OFF;
	}

    return event;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_get_linkup_event>                            */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_get_linkup_event (void)
{
	uint8			event;
	Std_ReturnType	linkState;


	linkState = EthDLC_Port_GetState();
	if (linkState == STD_ON)
	{
		event = D_ETHDLC_EV_LINK_UP;
	}
	else
	{
		event = D_ETHDLC_EV_NONE;
	}

    return event;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action>                                      */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_action (uint8 event)
{
	static const S_ETHDLC_ACTION	action_tbl[ D_ETHDLC_ST_NUM ][ D_ETHDLC_RECORD_PER_ST_NUM ] = 
/*D_ETHDLC_ST_INIT_POINT */	{/*	{	Event				, Action						} */
							{	{	D_ETHDLC_EV_INIT	, ethdlc_dlc_action_Init		}
							,	{	D_ETHDLC_EV_NONE	, ethdlc_dlc_action_None		}
							}
/*D_ETHDLC_ST_LINK_DOWN  */	,/*	{	Event				, Action						} */
							{	{	D_ETHDLC_EV_DLC_ON	, ethdlc_dlc_action_DLCOn		}
							,	{	D_ETHDLC_EV_NONE	, ethdlc_dlc_action_None		}
							}
/*D_ETHDLC_ST_LINK_WAIT  */	,/*	{	{	Event			, Action						} */
							{	{	D_ETHDLC_EV_DLC_OFF , ethdlc_dlc_action_DLCOff		}
							,	{	D_ETHDLC_EV_LINK_UP	, ethdlc_dlc_action_LinkUp		}
							}
/*D_ETHDLC_ST_LINK_UP    */	,/*	{	Event				, Action						} */
							{	{	D_ETHDLC_EV_DLC_OFF , ethdlc_dlc_action_DLCOff	    }
							,	{	D_ETHDLC_EV_NONE	, ethdlc_dlc_action_None		}
							}
							};
	uint8	idx1 = G_DLC_Status;
	uint8	idx2;


	if (idx1 < D_ETHDLC_ST_NUM)
	{
		for (idx2 = 0U; idx2 < D_ETHDLC_RECORD_PER_ST_NUM; idx2 ++)
		{
			if ((action_tbl[ idx1 ][ idx2 ].Event & event) != 0U)
			{
				{	/* start critical section */
					LIB_DI();

					G_DLC_Status = action_tbl[ idx1 ][ idx2 ].Action();

					LIB_EI();
				}	/* end critical section */

				break;
			}
		}
	}

	return;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_None>                                 */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_None (void)
{
	/* do nothing */

	return G_DLC_Status;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_Init>                                 */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_Init (void)
{
	/* do nothing */

	return D_ETHDLC_ST_LINK_DOWN;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_DLCOn>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_DLCOn (void)
{
	EthDLC_Port_Active();
	EthDLC_Indicate_ACTLOn();

	return D_ETHDLC_ST_LINK_WAIT;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_LinkUp>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_LinkUp (void)
{
	EthDLC_Indicate_DLCOn();

	return D_ETHDLC_ST_LINK_UP;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_DLCOff>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_DLCOff (void)
{
	EthDLC_Port_Down();

	EthDLC_Indicate_ACTLOff();
	EthDLC_Indicate_DLCOff();

	return D_ETHDLC_ST_LINK_DOWN;
}
/* -------------------------------------------------------------------------- */
#define EthDLC_STOP_SEC_CODE
#include <EthDLC_MemMap.h>
/* -------------------------------------------------------------------------- */
