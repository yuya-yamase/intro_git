/* EthSwt_SWIC_STM.c専用ヘッダファイル */

/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_STM_Cfg.h                                        */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_STM_CFG_H
#define ETHSWT_SWIC_STM_CFG_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Link.h>
#include <EthSwt_SWIC_Port.h>
/* -------------------------------------------------------------------------- */
typedef void (*EthSwt_HiPorcFunc)(void);
const EthSwt_HiPorcFunc G_ETHSWT_SWIC_HIPROC_FUNCS[] = 
{
    EthSwt_SWIC_Link_TimerUpdate
};
#define D_ETHSWT_SWIC_HIPROC_FUNCS_NUM              (sizeof(G_ETHSWT_SWIC_HIPROC_FUNCS) / sizeof(G_ETHSWT_SWIC_HIPROC_FUNCS[0]))

typedef Std_ReturnType (*EthSwt_Background_Func)(uint32 * const);
const EthSwt_Background_Func G_ETHSWT_SWIC_ACTIVE_FUNCS[] =
{
    EthSwt_SWIC_Link_Action
,   EthSwt_SWIC_Link_FastGet
,   EthSwt_SWIC_Port_Action
};
#define D_ETHSWT_SWIC_ACTIVE_FUNS_NUM               (sizeof(G_ETHSWT_SWIC_ACTIVE_FUNCS) /sizeof(G_ETHSWT_SWIC_ACTIVE_FUNCS[0]))

/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_STM_CFG_H */
/* -------------------------------------------------------------------------- */
