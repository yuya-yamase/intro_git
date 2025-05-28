#include <Std_Types.h>
#include "EthSwt_SWIC_PWR.h"
#include "EthSwt_SWIC_Core_Cfg.h"
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_PWR_ST_INIT_POINT         (0U)
#define D_ETHSWT_SWIC_PWR_ST_OFF                (1U)
#define D_ETHSWT_SWIC_PWR_ST_WAITON             (2U)
#define D_ETHSWT_SWIC_PWR_ST_ON                 (3U)
#define D_ETHSWT_SWIC_PWR_ST_RESET_ASSERT       (4U)
#define D_ETHSWT_SWIC_PWR_ST_RESET_DEASSERT     (5U)
#define D_ETHSWT_SWIC_PWR_ST_NUM                (6U)

#define D_ETHSWT_SWIC_PWR_EV_INIT               (0U)
#define D_ETHSWT_SWIC_PWR_EV_START              (1U)
#define D_ETHSWT_SWIC_PWR_EV_PMIC_WAIT          (2U)
#define D_ETHSWT_SWIC_PWR_EV_RESET              (3U)
#define D_ETHSWT_SWIC_PWR_EV_ASSERT_WAIT        (4U)
#define D_ETHSWT_SWIC_PWR_EV_DEASSERT_WAIT      (5U)
#define D_ETHSWT_SWIC_PWR_EV_STOP               (6U)
#define D_ETHSWT_SWIC_PWR_EV_NUM                (7U)

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
static void ethswt_swic_pwr_stm (uint32 event);
static uint32 ethswt_swic_pwr_act_initilize (void);
static uint32 ethswt_swic_pwr_act_powerOn (void);
static uint32 ethswt_swic_pwr_act_setSpiMode (void);
static uint32 ethswt_swic_pwr_act_resetAssert (void);
static uint32 ethswt_swic_pwr_act_resetDeassert (void);
static uint32 ethswt_swic_pwr_act_resume (void);
static uint32 ethswt_swic_pwr_act_powerOff (void);
static uint32 ethswt_swic_pwr_act_none (void);

/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_Init(void)
{
    ethswt_swic_pwr_stm(D_ETHSWT_SWIC_PWR_EV_INIT);

    return;
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_LoProc(void)
{

}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_PowerOnReq(void)
{
    
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_PowerOffReq(void)
{
    
}
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_PWR_ResetReq(void)
{

}
/* -------------------------------------------------------------------------- */
uint8 EthSwt_SWIC_PWR_GetState(void);

/* -------------------------------------------------------------------------- */
typedef uint32 (*SWIC_PWR_ACT);
/* -------------------------------------------------------------------------- */
static void ethswt_swic_pwr_stm (uint32 event)
{
    static const SWIC_PWR_ACT   action_tbl[D_ETHSWT_SWIC_PWR_EV_NUM][D_ETHSWT_SWIC_PWR_ST_NUM] =
                        /*  { { S0:ST_INIT_POINT                , S1:ST_OFF                     , S2:ST_WAITON                  , S3:ST_ON                          , S4:ST_RESET_ASSERT                , S5:ST_RESET_DEASSERT          }}*/
    /* EV_INIT          */  { { ethswt_swic_pwr_act_initilize   , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none      }
    /* EV_START         */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_powerOn   , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none      }
    /* EV_PMIC_WAIT     */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_setSpiMode, ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none      }
    /* EV_RESET         */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_resetAssert   , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none      }
    /* EV_ASSERT_WAIT   */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_resetDeassert , ethswt_swic_pwr_act_none      }
    /* EV_DEASSERT_WAIT */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none      , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_none          , ethswt_swic_pwr_act_resume    }
    /* EV_STOP          */  , { ethswt_swic_pwr_act_none        , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff  , ethswt_swic_pwr_act_powerOff      , ethswt_swic_pwr_act_powerOff      , ethswt_swic_pwr_act_powerOff  }
                            };
    
    G_SWIC_PWR_Status = action_tbl[event][G_SWIC_PWR_Status];

    return;
}

static uint32 ethswt_swic_pwr_act_initilize (void)
{
    G_SWIC_PWR_PowerOnCount = 0;
    G_SWIC_PWR_ResetReq = STD_OFF;
    G_SWIC_PWR_ResetAssertCount = 0;
    G_SWIC_PWR_ResetDeassertCount = 0;

    // SPI GPIOモード、電源OFFにしとく

    return D_ETHSWT_SWIC_PWR_ST_OFF;
}
static uint32 ethswt_swic_pwr_act_powerOn (void)
{
    EthSwt_SWIC_PWR_PowerOn();

    return D_ETHSWT_SWIC_PWR_ST_WAITON;
}
static uint32 ethswt_swic_pwr_act_setSpiMode (void)
{

    return D_ETHSWT_SWIC_PWR_ST_ON;
}
static uint32 ethswt_swic_pwr_act_resetAssert (void)
{
    return D_ETHSWT_SWIC_PWR_ST_RESET_ASSERT;
}
static uint32 ethswt_swic_pwr_act_resetDeassert (void)
{
    return D_ETHSWT_SWIC_PWR_ST_RESET_DEASSERT;
}
static uint32 ethswt_swic_pwr_act_resume (void)
{
    return D_ETHSWT_SWIC_PWR_ST_ON;
}
static uint32 ethswt_swic_pwr_act_powerOff (void)
{
    return D_ETHSWT_SWIC_PWR_ST_OFF;
}
static uint32 ethswt_swic_pwr_act_none (void)
{
    /* do nothing */
    return G_SWIC_PWR_Status;
}