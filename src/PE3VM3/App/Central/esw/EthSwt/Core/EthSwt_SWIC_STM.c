/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_STM.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include <EthSwt_SWIC_STM_Cfg.h>
#include "EthSwt_SWIC_STM.h"
#include "EthSwt_SWIC_PWR.h"
#include "EthSwt_SWIC_Init.h"
#include "EthSwt_SWIC_Port.h"
#include "EthSwt_SWIC_Define.h"
/* -------------------------------------------------------------------------- */
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
#define D_ETHSWT_SWIC_EV_READ_WRONG                     (11U)
#define D_ETHSWT_SWIC_EV_FAIL_INIT                      (12U)
#define D_ETHSWT_SWIC_EV_NO_PROC                        (13U)
#define D_ETHSWT_SWIC_EV_NUM                            (14U)

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
static void ethswt_swic_err (uint32 resetFactor);
static uint32 ethswt_swic_stm_act_move_init (void);
static uint32 ethswt_swic_stm_act_move_port_init_completed (void);
static uint32 ethswt_swic_stm_act_move_set_relay_on (void);
static uint32 ethswt_swic_stm_act_move_active (void);
static uint32 ethswt_swic_stm_act_move_set_relay_off (void);
static uint32 ethswt_swic_stm_act_unavailable (void);
static uint32 ethswt_swic_stm_act_reset (void);
static uint32 ethswt_swic_stm_act_none (void);
static void ethswt_swic_stm_clear (void);
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_Init (void)
{
    uint8 idx;

    G_SWIC_Status = D_ETHSWT_SWIC_ST_UNINIT;

    for(idx = 0; idx < D_ETHSWT_SWIC_INIT_FUNC_NUM; idx++) {
        G_ETHSWT_SWIC_INIT_FUNC_LIST[idx]();
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_HiProc (void)
{
    uint8 idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_HIPROC_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[idx][G_SWIC_Status] == NULL_PTR) { continue; }
        G_ETHSWT_SWIC_HIPROC_FUNC_TABLE[idx][G_SWIC_Status]();
    }

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_Background (void)
{
    Std_ReturnType swicAvailable;

    swicAvailable = EthSwt_SWIC_AllowSetRegister();
    if (swicAvailable == E_OK) {
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
    } else {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_UNAVAILABLE);
    }
}
/* -------------------------------------------------------------------------- */
EthSwt_StateType EthSwt_SWIC_STM_GetStatus (void)
{
    EthSwt_StateType ret;

    switch (G_SWIC_Status) {
    case D_ETHSWT_SWIC_ST_UNINIT:
        ret = ETHSWT_STATE_UNINIT;
        break;
    case D_ETHSWT_SWIC_ST_INIT:
        ret = ETHSWT_STATE_INIT;
        break;
    case D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED:
    case D_ETHSWT_SWIC_ST_SET_RELAY_ON:
    case D_ETHSWT_SWIC_ST_SET_RELAY_OFF:
        ret = ETHSWT_STATE_PORTINIT_COMPLETED;
        break;
    case D_ETHSWT_SWIC_ST_ACTIVE:
        ret = ETHSWT_STATE_ACTIVE;
        break;
    default:
        ret = ETHSWT_STATE_UNINIT;
        break;
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_uninitProc (void)
{
    ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_AVAILABLE);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_initProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_ERR_NONE;
    uint8 idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_BACK_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_INIT] == NULL_PTR) { continue; }
        result = G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_INIT](&errFactor);
        if (result != E_OK) { break; }
    }

    if (result == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_INIT_DONE);
    } else {
        ethswt_swic_err(errFactor);
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_portInitCompletedProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_ERR_NONE;
    uint8 idx;
    Std_ReturnType allowRelay;

    for (idx = 0; idx < D_ETHSWT_SWIC_BACK_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED] == NULL_PTR) { continue; }
        result = G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED](&errFactor);
        if (result != E_OK) { break; }
    }

    if (result == E_OK) {
        allowRelay = EthSwt_SWIC_AllowRelay();
        if (allowRelay == E_OK) {
             ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_START_RELAY);
        }
    } else {
        ethswt_swic_err(errFactor);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_setRelayOnProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_ERR_NONE;
    uint8 idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_BACK_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_SET_RELAY_ON] == NULL_PTR) { continue; }
        result = G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_SET_RELAY_ON](&errFactor);
        if (result != E_OK) { break; }
    }

    if (result == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_RELAYON_DONE);
    } else {
        ethswt_swic_err(errFactor);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_activeProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_ERR_NONE;
    uint8 idx;
    Std_ReturnType allowRelay;

    for (idx = 0; idx < D_ETHSWT_SWIC_BACK_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_ACTIVE] == NULL_PTR) { continue; }
        result = G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_ACTIVE](&errFactor);
        if (result != E_OK) { break; }
    }

    if (result == E_OK) {
        allowRelay = EthSwt_SWIC_AllowRelay();
        if (allowRelay != E_OK) {
             ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_STOP_RELAY);
        }
    } else {
        ethswt_swic_err(errFactor);
    }
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_setRelayOffProc (void)
{
    Std_ReturnType result;
    uint32 errFactor = D_ETHSWT_SWIC_ERR_NONE;
    uint8 idx;

    for (idx = 0; idx < D_ETHSWT_SWIC_BACK_FUNC_NUM; idx++) {
        if (G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_SET_RELAY_OFF] == NULL_PTR) { continue; }
        result = G_ETHSWT_SWIC_BACK_FUNC_TABLE[idx][D_ETHSWT_SWIC_ST_SET_RELAY_OFF](&errFactor);
        if (result != E_OK) { break; }
    }

    if (result == E_OK) {
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_RELAYOFF_DONE);
    } else {
        ethswt_swic_err(errFactor);
    }

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_err (uint32 resetFactor)
{
    switch (resetFactor) {
    case D_ETHSWT_SWIC_ERR_POWEROFF:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_UNAVAILABLE);
        break;
    case D_ETHSWT_SWIC_ERR_CRC:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_CRC_ERROR);
        break;
    case D_ETHSWT_SWIC_ERR_BUSY:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_BUSYBIT_OUT);
        break;
    case D_ETHSWT_SWIC_ERR_WRONGVALUE:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_READ_WRONG);
        break;
    case D_ETHSWT_SWIC_ERR_INIT:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_FAIL_INIT);
        break;
    case D_ETHSWT_SWIC_ERR_INTN:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_INTN_ERROR);
        break;
    case D_ETHSWT_SWIC_ERR_RESET:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_RESET_DETECT);
        break;
    case D_ETHSWT_SWIC_ERR_NOPROC:
        ethswt_swic_stm_action(D_ETHSWT_SWIC_EV_NO_PROC);
        break;
    default:
        break;  /* ƒrƒbƒg‰»‚¯ ‰½‚à‚µ‚È‚¢*/
    }

    return;
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
    /* EV_READ_WRONG    */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
    /* EV_FAIL_INIT     */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_none              , ethswt_swic_stm_act_none          , ethswt_swic_stm_act_none                  , ethswt_swic_stm_act_none                      }
    /* EV_NO_PROC       */  , {ethswt_swic_stm_act_none         , ethswt_swic_stm_act_reset                     , ethswt_swic_stm_act_reset             , ethswt_swic_stm_act_reset         , ethswt_swic_stm_act_reset                 , ethswt_swic_stm_act_reset                     }
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
    ethswt_swic_stm_clear();

    return D_ETHSWT_SWIC_ST_SET_RELAY_OFF;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_unavailable (void)
{
    ethswt_swic_stm_clear();

    return D_ETHSWT_SWIC_ST_UNINIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_reset (void)
{
    EthSwt_SWIC_PWR_ResetReq();
    ethswt_swic_stm_clear();

    return D_ETHSWT_SWIC_ST_UNINIT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_stm_act_none (void)
{
    /* do nothing */
    return G_SWIC_Status;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_stm_clear (void)
{
    uint8 idx;
    
    for(idx = 0; idx < D_ETHSWT_SWIC_CLEAR_FUNC_NUM; idx++) {
        G_ETHSWT_SWIC_CLEAR_FULC_LIST[idx]();
    }
    return;
}
/* -------------------------------------------------------------------------- */
