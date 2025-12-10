/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_PWR.c                                            */
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
#include "EthSwt_SWIC_PWR.h"
#include <LIB.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_ST_OFF                (0U)
#define D_ETHSWT_SWIC_PWR_ST_WAITSUPLY          (1U)
#define D_ETHSWT_SWIC_PWR_ST_WAITON             (2U)
#define D_ETHSWT_SWIC_PWR_ST_ON                 (3U)
#define D_ETHSWT_SWIC_PWR_ST_RSTASRT            (4U)
#define D_ETHSWT_SWIC_PWR_ST_RSTDASRT           (5U)
#define D_ETHSWT_SWIC_PWR_ST_NUM                (6U)

#define D_ETHSWT_SWIC_PWR_EV_START              (0U)
#define D_ETHSWT_SWIC_PWR_EV_SUPLY              (1U)
#define D_ETHSWT_SWIC_PWR_EV_PMICON             (2U)
#define D_ETHSWT_SWIC_PWR_EV_RST                (3U)
#define D_ETHSWT_SWIC_PWR_EV_ASRTDONE           (4U)
#define D_ETHSWT_SWIC_PWR_EV_DASRTDONE          (5U)
#define D_ETHSWT_SWIC_PWR_EV_PMICOFF            (6U)
#define D_ETHSWT_SWIC_PWR_EV_STOP               (7U)
#define D_ETHSWT_SWIC_PWR_EV_FORCEOFF           (8U)
#define D_ETHSWT_SWIC_PWR_EV_NUM                (9U)

#define D_ETHSWT_SWIC_PWR_PWR_ON_TIME           (D_ETHSWT_SWIC_PWR_ON_WAIT / D_ETHSWT_SWIC_PWR_CYCLE)
#define D_ETHSWT_SWIC_PWR_ASSERT_TIME           (D_ETHSWT_SWIC_PWR_ASSERT_WAIT / D_ETHSWT_SWIC_PWR_CYCLE)
#define D_ETHSWT_SWIC_PWR_DEASSERT_TIME         (D_ETHSWT_SWIC_PWR_DEASSERT_WAIT / D_ETHSWT_SWIC_PWR_CYCLE)
/* -------------------------------------------------------------------------- */
static uint32   G_SWIC_PWR_Status;
static uint32   G_SWIC_PWR_PowerOnCount;
static uint8    G_SWIC_PWR_ResetReq;
static uint32   G_SWIC_PWR_ResetAssertCount;
static uint32   G_SWIC_PWR_ResetDeassertCount;
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_offProc (void);
static void ethswt_swic_pwr_waitSuplyProc (void);
static void ethswt_swic_pwr_waitOnProc (void);
static void ethswt_swic_pwr_onProc (void);
static void ethswt_swic_pwr_rstAsrtProc (void);
static void ethswt_swic_pwr_rstDasrtProc (void);
static void ethswt_swic_pwr_stm (const uint32 event);

static Std_ReturnType ethswt_swic_pwr_checkPowerCond (void);
static Std_ReturnType ethswt_swic_pwr_checkSuply (void);

static uint32 ethswt_swic_pwr_act_powerOn (void);
static uint32 ethswt_swic_pwr_act_moveWaitOn (void);
static uint32 ethswt_swic_pwr_act_setSpiMode (void);
static uint32 ethswt_swic_pwr_act_rstAsrt (void);
static uint32 ethswt_swic_pwr_act_rstDasrt (void);
static uint32 ethswt_swic_pwr_act_resume (void);
static uint32 ethswt_swic_pwr_act_powerOff (void);
static uint32 ethswt_swic_pwr_act_none (void);
/* -------------------------------------------------------------------------- */
typedef void (*ETHSWT_SWIC_PWR_PROC)();
static const ETHSWT_SWIC_PWR_PROC G_ETHSWT_SWIC_PWR_PROC_LIST[D_ETHSWT_SWIC_PWR_ST_NUM] =
{
    ethswt_swic_pwr_offProc
,   ethswt_swic_pwr_waitSuplyProc
,   ethswt_swic_pwr_waitOnProc
,   ethswt_swic_pwr_onProc
,   ethswt_swic_pwr_rstAsrtProc
,   ethswt_swic_pwr_rstDasrtProc
};
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_Init(void)
{
    G_SWIC_PWR_PowerOnCount = 0;
    G_SWIC_PWR_ResetReq = STD_OFF;
    G_SWIC_PWR_ResetAssertCount = 0;
    G_SWIC_PWR_ResetDeassertCount = 0;

    EthSwt_SWIC_Cfg_SetGPIOMode();          /* OEM Config */
    EthSwt_SWIC_Cfg_SetPowerOff();             /* OEM Config */

    G_SWIC_PWR_Status = D_ETHSWT_SWIC_PWR_ST_OFF;

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_LoProc(void)
{
    G_ETHSWT_SWIC_PWR_PROC_LIST[G_SWIC_PWR_Status]();

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_ForceOffReq(void)
{
    ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_FORCEOFF);
    
    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_ResetReq(void)
{
    LIB_DI();
    G_SWIC_PWR_ResetReq = STD_ON;
    LIB_EI();

    return;
}
/* -------------------------------------------------------------------------- */
Std_ReturnType EthSwt_SWIC_PWR_GetSWICPower(void)
{
    Std_ReturnType  state = STD_OFF;
    uint32          pwrStatus;
    uint32          resetReq;

    LIB_DI();
    pwrStatus = G_SWIC_PWR_Status;
    resetReq = G_SWIC_PWR_ResetReq;
    LIB_EI();

    if (pwrStatus == D_ETHSWT_SWIC_PWR_ST_ON && resetReq == STD_OFF)
    {
        state = STD_ON;
    }

    return state;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_offProc (void)
{
    Std_ReturnType  isPowerOnCond;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }             /* break不要だが、他実装と合わせる */
    } while (0);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_waitSuplyProc (void)
{
    Std_ReturnType  isPowerOnCond;
    Std_ReturnType  isSupply;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }
        
        isSupply = ethswt_swic_pwr_checkSuply();
        if (isSupply != STD_ON) { break; }                  /* break不要だが、他実装と合わせる */
    } while (0);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_waitOnProc (void)
{
    Std_ReturnType  isPowerOnCond;
    Std_ReturnType  isSupply;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }
        
        isSupply = ethswt_swic_pwr_checkSuply();
        if (isSupply != STD_ON) { break; }

        G_SWIC_PWR_PowerOnCount++;
        if (G_SWIC_PWR_PowerOnCount >= D_ETHSWT_SWIC_PWR_PWR_ON_TIME)
        {
            ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_PMICON);
        }
    } while (0);
    
    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_onProc (void)
{
    Std_ReturnType  isPowerOnCond;
    Std_ReturnType  isSupply;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }
        
        isSupply = ethswt_swic_pwr_checkSuply();
        if (isSupply != STD_ON) { break; }
        
        if (G_SWIC_PWR_ResetReq == STD_ON)
        {
            G_SWIC_PWR_ResetReq = STD_OFF;
            ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_RST);
        }
    } while (0);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_rstAsrtProc (void)
{
    Std_ReturnType  isPowerOnCond;
    Std_ReturnType  isSupply;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }
        
        isSupply = ethswt_swic_pwr_checkSuply();
        if (isSupply != STD_ON) { break; }
        
        G_SWIC_PWR_ResetAssertCount++;
        if (G_SWIC_PWR_ResetAssertCount >= D_ETHSWT_SWIC_PWR_ASSERT_TIME)
        {
            ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_ASRTDONE);
        }
    } while (0);

    return;
}
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_rstDasrtProc (void)
{
    Std_ReturnType  isPowerOnCond;
    Std_ReturnType  isSupply;
    do {
        isPowerOnCond = ethswt_swic_pwr_checkPowerCond();
        if (isPowerOnCond != STD_ON) { break; }
        
        isSupply = ethswt_swic_pwr_checkSuply();
        if (isSupply != STD_ON) { break; }
        
        G_SWIC_PWR_ResetDeassertCount++;
        if (G_SWIC_PWR_ResetDeassertCount >= D_ETHSWT_SWIC_PWR_DEASSERT_TIME)
        {
            ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_DASRTDONE);
        }
    } while (0);

    return;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_pwr_checkPowerCond (void)
{
    Std_ReturnType  ret;

    ret = EthSwt_SWIC_Cfg_CheckPowerCond();

    if (ret == STD_ON) {
        ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_START);
    } else {
        ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_STOP);
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
static Std_ReturnType ethswt_swic_pwr_checkSuply (void)
{
    Std_ReturnType  ret;

    ret = EthSwt_SWIC_Cfg_CheckSuplyState();

    if (ret == STD_ON) {
        ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_SUPLY);
    } else {
        ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_PMICOFF);
    }

    return ret;
}
/* -------------------------------------------------------------------------- */
typedef uint32 (*SWIC_PWR_ACT)();
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_stm (const uint32 event)
{
    static const SWIC_PWR_ACT   action_tbl[D_ETHSWT_SWIC_PWR_EV_NUM][D_ETHSWT_SWIC_PWR_ST_NUM] =
                        /*  { { S0:ST_OFF                   , S1:ST_WAITSUPLY               , S2:ST_WAITON                  , S3:ST_ON                      , S4:ST_RSTASRT                 , S5:ST_RSTDASRT                }} */
    /* EV_START         */  { {ethswt_swic_pwr_act_powerOn  , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      }
    /* EV_SUPLY         */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_moveWaitOn, ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      }
    /* EV_PMICON        */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_setSpiMode, ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      }
    /* EV_RST           */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_rstAsrt   , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      }
    /* EV_ASRTDONE      */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_rstDasrt  , ethswt_swic_pwr_act_none      }
    /* EV_DASRTDONE     */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_resume    }
    /* EV_PMICOFF       */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  }
    /* EV_STOP          */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  }
    /* EV_FORCEOFF      */  , {ethswt_swic_pwr_act_none     , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  }
                            };
    
    G_SWIC_PWR_Status = action_tbl[event][G_SWIC_PWR_Status]();

    return;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_powerOn (void)
{
    EthSwt_SWIC_Cfg_SetPowerOn();              /* OEM Config */

    return D_ETHSWT_SWIC_PWR_ST_WAITSUPLY;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_moveWaitOn (void)
{
    return D_ETHSWT_SWIC_PWR_ST_WAITON;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_setSpiMode (void)
{
    EthSwt_SWIC_Cfg_SetSPIMode();           /* OEM Config */

    return D_ETHSWT_SWIC_PWR_ST_ON;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_rstAsrt (void)
{
    EthSwt_SWIC_Cfg_SetResetAssert();       /* OEM Config */

    return D_ETHSWT_SWIC_PWR_ST_RSTASRT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_rstDasrt (void)
{
    EthSwt_SWIC_Cfg_SetResetDeassert();     /* OEM Config */

    return D_ETHSWT_SWIC_PWR_ST_RSTDASRT;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_resume (void)
{
    G_SWIC_PWR_ResetAssertCount = 0;
    G_SWIC_PWR_ResetDeassertCount = 0;

    ETHSWT_SWIC_PWR_NOTIFY();
    
    return D_ETHSWT_SWIC_PWR_ST_ON;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_powerOff (void)
{
    EthSwt_SWIC_Cfg_SetGPIOMode();          /* OEM Config */
    EthSwt_SWIC_Cfg_SetPowerOff();             /* OEM Config */

    G_SWIC_PWR_PowerOnCount = 0;
    G_SWIC_PWR_ResetReq = STD_OFF;
    G_SWIC_PWR_ResetAssertCount = 0;
    G_SWIC_PWR_ResetDeassertCount = 0;

    return D_ETHSWT_SWIC_PWR_ST_OFF;
}
/* -------------------------------------------------------------------------- */
static uint32 ethswt_swic_pwr_act_none (void)
{
    /* do nothing */
    return G_SWIC_PWR_Status;
}
