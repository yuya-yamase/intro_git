#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_STM.h>
#include <EthSwt_SWIC_Core_Cfg.h>
#include <EthSwt_SWIC_PWR.h>
#include <EthSwt_SWIC_Init.h>
#include <EthSwt_SWIC_Define.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_ST_UNINIT                         (0U)
#define D_ETHSWT_SWIC_ST_INIT                           (1U)
#define D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED            (2U)
#define D_ETHSWT_SWIC_ST_SET_RELAY_ON                   (3U)
#define D_ETHSWT_SWIC_ST_ACTIVE                         (4U)
#define D_ETHSWT_SWIC_ST_SET_RELAY_OFF                  (5U)
#define D_ETHSWT_SWIC_ST_NUM                            (6U)

#define D_ETHSWT_SWIC_EV_AVAILABLE                      (0U)
#define D_ETHSWT_SWIC_EV_INIT_DONE                      (1U)
#define D_ETHSWT_SWIC_EV_START_RELAY                    (2U)
#define D_ETHSWT_SWIC_EV_RELAYON_DONE                   (3U)
#define D_ETHSWT_SWIC_EV_STOP_RELAY                     (4U)
#define D_ETHSWT_SWIC_EV_RELAYOFF_DONE                  (5U)
#define D_ETHSWT_SWIC_EV_UNAVAILABLE                    (6U)
#define D_ETHSWT_SWIC_EV_CRC_ERROR                      (7U)
#define D_ETHSWT_SWIC_EV_BUSYBIT_OUT                    (8U)
#define D_ETHSWT_SWIC_EV_INTN_ERROR                     (9U)
#define D_ETHSWT_SWIC_EV_RESET_DETECT                   (10U)
#define D_ETHSWT_SWIC_EV_NUM                            (11U)

/* -------------------------------------------------------------------------- */
static uint32 G_SWIC_Status;

/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_uninitProc (void);
static void ethswt_swic_stm_initProc (void);
static void ethswt_swic_stm_portInitCompletedProc (void);
static void ethswt_swic_stm_setRelayOnProc (void);
static void ethswt_swic_stm_activeProc (void);
static void ethswt_swic_stm_setRelayOffProc (void);
static void ethswt_swic_stm_action (uint32 event);
static uint32 ethswt_swic_stm_act_move_init (void);
static uint32 ethswt_swic_stm_act_move_port_init_completed (void);
static uint32 ethswt_swic_stm_act_move_set_relay_on (void);
static uint32 ethswt_swic_stm_act_move_active (void);
static uint32 ethswt_swic_stm_act_move_set_relay_off (void);
static uint32 ethswt_swic_stm_act_unavailable (void);
static uint32 ethswt_swic_stm_act_reset (void);
static uint32 ethswt_swic_stm_act_none (void);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_Init (void)
{
    G_SWIC_Status = D_ETHSWT_SWIC_ST_UNINIT;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_Background (void)
{
    switch (G_SWIC_Status) {
    case D_ETHSWT_SWIC_ST_UNINIT:
        ethswt_swic_stm_uninitProc();
        break;
    case D_ETHSWT_SWIC_ST_INIT:
        ethswt_swic_stm_initProc();
        break;
    case D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED:
        ethswt_swic_stm_portInitCompletedProc();
        break;
    case D_ETHSWT_SWIC_ST_SET_RELAY_ON:
        ethswt_swic_stm_setRelayOnProc();
        break;
    case D_ETHSWT_SWIC_ST_ACTIVE:
        ethswt_swic_stm_activeProc();
        break;
    case D_ETHSWT_SWIC_ST_SET_RELAY_OFF:
        ethswt_swic_stm_setRelayOffProc();
        break;
    default:
        break;
    }
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_uninitProc (void)
{
    Std_ReturnType swicAvailable;

    swicAvailable = EthSwt_SWIC_STM_CheckAvailable();
    if (swicAvailable == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_AVAILABLE);
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_initProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_REG_FACT_NONE;

    result = EthSwt_SWIC_Init_Setting(&errFactor);
    if (result == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_INIT_DONE);
    } else {
        switch (errFactor) {
        case D_ETHSWT_SWIC_REG_FACT_CRC:
            ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_CRC_ERROR);
            break;
        case D_ETHSWT_SWIC_REG_FACT_BSY:
            ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_BUSYBIT_OUT);
            break;
        default:
            /* àŸèÌån */
            break;
        }
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_portInitCompletedProc (void)
{
    Std_ReturnType result;

    result = EthSwt_SWIC_STM_CanRelay();
    if (result == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_START_RELAY);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_setRelayOnProc (void)
{

}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_activeProc (void)
{

}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_setRelayOffProc (void)
{

}
/* -------------------------------------------------------------------------- */
typedef uint32 (*SWIC_STM_ACT)();
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_action (uint32 event)
{
    static const SWIC_STM_ACT   action_tbl[D_ETHSWT_SWIC_EV_NUM][D_ETHSWT_SWIC_ST_NUM] =
                        /*  { {S0:ST_UNINIT                     , S1:ST_INIT                                    , S2:ST_PORT_INIT_COMPLETED             , S3:ST_SET_RELAY_ON                , S4:ST_ACTIVE                              , S5:SET_RELAY_OFF                              }}*/
    /* EV_AVAILABLE     */  { {ethswt_swic_stm_act_move_init    , ethswt_swic_stm_act_none                      , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_none                      }
    /* EV_INIT_DONE     */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_move_port_init_completed  , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_none                      }
    /* EV_START_RELAY   */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_none                      , ethswt_swic_stm_act_move_set_relay_on , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_none                      }
    /* EV_RELAYON_DONE  */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_none                      , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_move_active   , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_none                      }
    /* EV_STOP_RELAY    */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_none                      , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_move_set_relay_off    , ethswt_swic_stm_act_none                      }
    /* EV_RELAYOFF_DONE */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_none                      , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_move_port_init_completed  }
    /* EV_UNAVAILABLE   */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_unavailable               , ethswt_swic_stm_act_unavailable       , ethswt_swic_stm_act_unavailable   , ethswt_swic_stm_act_unavailable           , ethswt_swic_stm_act_unavailable               }
    /* EV_CRC_ERROR     */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
    /* EV_BUSYBIT_OUT   */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
    /* EV_INTN_ERROR    */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
    /* EV_RESET_DETECT  */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
                            };
    G_SWIC_Status = action_tbl[event][G_SWIC_Status]();

    return;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_move_init (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_INIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_move_port_init_completed (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_move_set_relay_on (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_SET_RELAY_ON;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_move_active (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_ACTIVE;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_move_set_relay_off (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_SET_RELAY_OFF;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_unavailable (void)
{
    /* do nothing */
    return D_ETHSWT_SWIC_ST_UNINIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_reset (void)
{
    EthSwt_SWIC_PWR_ResetReq();

    return D_ETHSWT_SWIC_ST_UNINIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_none (void)
{
    /* do nothing */
    return G_SWIC_Status;
}
