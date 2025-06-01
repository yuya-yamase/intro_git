#include <Std_Types.h>
#include "EthSwt_SWIC_Core_Cfg.h"
/* -------------------------------------------------------------------------- */
/* Common */
const Eth_ModeType G_ETHSWT_SWIC_PORT_DEFINE[D_ETHSWT_SWIC_PORT_NUM] =
{
    ETH_MODE_DOWN           /* Port9 */
,   ETH_MODE_ACTIVE         /* Port1 */
,   ETH_MODE_ACTIVE         /* Port2 */
,   ETH_MODE_DOWN           /* Port3 */
,   ETH_MODE_DOWN           /* Port4 */
,   ETH_MODE_ACTIVE         /* Port5 */
,   ETH_MODE_DOWN           /* Port6 */
,   ETH_MODE_ACTIVE         /* Port7 */
,   ETH_MODE_ACTIVE         /* Port8 */
};

/* -------------------------------------------------------------------------- */
/* For EthSwt_SWIC_STM */
#include <Dio.h>
#include <Dio_Symbols.h>
#include <EthSwt_SWIC_PWR.h>
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_SWIC_Port.h>
#include <EthSwt_StubDriver.h> /* Ç†Ç∆Ç≈è¡Ç∑ */


const EthSwt_HiPorcFunc G_ETHSWT_SWIC_HIPROC_FUNCS[] =
{
    EthSwt_SWIC_Link_TimerUpdate
};

const EthSwt_Background_Func G_ETHSWT_SWIC_ACTIVE_FUNCS[] =
{
    EthSwt_SWIC_Link_Action
,   EthSwt_SWIC_Link_FastGet
,   EthSwt_SWIC_Port_Action
};
/* -------------------------------------------------------------------------- */
