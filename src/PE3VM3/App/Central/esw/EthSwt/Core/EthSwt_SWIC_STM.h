/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_STM.h                                            */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_STM_H
#define ETHSWT_SWIC_STM_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_SWIC_ST_UNINIT                         (0U)
#define D_ETHSWT_SWIC_ST_INIT                           (1U)
#define D_ETHSWT_SWIC_ST_PORT_INIT_COMPLETED            (2U)
#define D_ETHSWT_SWIC_ST_SET_RELAY_ON                   (3U)
#define D_ETHSWT_SWIC_ST_ACTIVE                         (4U)
#define D_ETHSWT_SWIC_ST_SET_RELAY_OFF                  (5U)
#define D_ETHSWT_SWIC_ST_NUM                            (6U)
/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_STM_Init (void);
void EthSwt_SWIC_STM_HiProc (void);
void EthSwt_SWIC_STM_Background (void);
EthSwt_StateType EthSwt_SWIC_STM_GetStatus (void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_STM_H */
/* -------------------------------------------------------------------------- */
