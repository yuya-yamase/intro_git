/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_DLC.c                                                 */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthDLC_ACTL.h>
#include <EthDLC_DLC.h>
#include <LIB.h>
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

#define D_ETHDLC_RECORD_PER_ST_NUM	(2U)
/* -------------------------------------------------------------------------- */
typedef uint8 (*ETHDLC_ACT)(void);
typedef struct
{
	uint8		Event;
	ETHDLC_ACT	Action;
} S_ETHDLC_ACTION;
/* -------------------------------------------------------------------------- */
static uint8 G_DLC_Status;
static uint8 G_DLC_Event;
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_drive_stm(void);
static void ethdlc_dlc_event_set(uint8 event);
static uint8 ethdlc_dlc_event_get(void);
static void ethdlc_dlc_action(uint8 event);
static uint8 ethdlc_dlc_action_None (void);
static uint8 ethdlc_dlc_action_Init(void);
static uint8 ethdlc_dlc_action_DLCOn(void);
static uint8 ethdlc_dlc_action_LinkUp(void);
static uint8 ethdlc_dlc_action_DLCOff(void);
static uint8 ethdlc_dlc_get_dlc_event (void);
static uint8 ethdlc_dlc_get_linkup_event (void);
static Std_ReturnType ethdlc_dlc_checkPwrState(void);
static void ethdlc_dlc_notifyDoIPAction(void);

/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_DLC_Init>                                        */
/* -------------------------------------------------------------------------- */
void EthDLC_DLC_Init (void)
{
	G_DLC_Status = D_ETHDLC_ST_INIT_POINT;
	G_DLC_Event  = D_ETHDLC_EV_NONE;

	ethdlc_dlc_event_set(D_ETHDLC_EV_INIT);
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-EthDLC_DLC_LoProc>                                      */
/* -------------------------------------------------------------------------- */
void EthDLC_DLC_LoProc (void)
{
	ethdlc_dlc_drive_stm();

    ethdlc_dlc_notifyDoIPAction();
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_drive_stm>                                   */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_drive_stm (void)
{
	uint8	evt;


	evt = ethdlc_dlc_event_get();

	ethdlc_dlc_action(evt);
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_event_set>                                   */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_event_set (uint8 event)
{
	G_DLC_Event |= event;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_event_get>                                   */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_event_get (void)
{
	uint8			event;

	event = G_DLC_Event | ethdlc_dlc_get_dlc_event() | ethdlc_dlc_get_linkup_event();

	G_DLC_Event = D_ETHDLC_EV_NONE;

	return event;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_get_dlc_event>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_get_dlc_event (void)
{
    uint8           ret;
	Std_ReturnType	actl;
    Std_ReturnType  PwrState;

    actl = EthDLC_ACTL_GetPortSatus();
    PwrState = ethdlc_dlc_checkPwrState();
    if (actl == STD_ON && PwrState == STD_ON)
	{
		ret = D_ETHDLC_EV_DLC_ON;
	}
	else
	{
		ret = D_ETHDLC_EV_DLC_OFF;
	}

    return ret;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_checkPwrState>                               */
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethdlc_dlc_checkPwrState(void)
{
    /* VISから車両電源基本ステートを取得して判断する	*/
	/* 暫定でONを返す								*/
    return STD_ON;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_get_linkup_event>                            */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_get_linkup_event (void)
{
    uint8                   ret;
    EthTrcv_LinkStateType   linkState;

    ETHDLC_GET_DLC_LINK_STATE(&linkState);

    if (linkState == ETHTRCV_LINK_STATE_ACTIVE)
    {
        ret = D_ETHDLC_EV_LINK_UP;
    } else {
        ret = D_ETHDLC_EV_NONE;
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action>                                      */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_action (uint8 event)
{
	const S_ETHDLC_ACTION	action_tbl[ D_ETHDLC_ST_NUM ][ D_ETHDLC_RECORD_PER_ST_NUM ] = 
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
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_None>                                 */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_None (void)
{
	return G_DLC_Status;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_Init>                                 */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_Init (void)
{
	return D_ETHDLC_ST_LINK_DOWN;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_DLCOn>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_DLCOn (void)
{
	ETHDLC_DLC_PORT_ON;

	return D_ETHDLC_ST_LINK_WAIT;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_LinkUp>                               */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_LinkUp (void)
{
	return D_ETHDLC_ST_LINK_UP;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_action_DLCOff>                              */
/* -------------------------------------------------------------------------- */
static uint8 ethdlc_dlc_action_DLCOff (void)
{
	ETHDLC_DLC_PORT_OFF;

	return D_ETHDLC_ST_LINK_DOWN;
}
/* -------------------------------------------------------------------------- */
/* tag         : <ESW-ethdlc_dlc_notifyDoIPAction>                               */
/* -------------------------------------------------------------------------- */
static void ethdlc_dlc_notifyDoIPAction(void)
{
    switch (G_DLC_Status) {
    case D_ETHDLC_ST_LINK_UP:
        /* ChipComへDoIP起動条件 ON通知*/
        break;
    case D_ETHDLC_ST_INIT_POINT:
    case D_ETHDLC_ST_LINK_DOWN:
    case D_ETHDLC_ST_LINK_WAIT:
    default:
        /* ChipComへDoIP起動条件 OFF通知*/
        break;
    }
}
/* -------------------------------------------------------------------------- */
