/* -------------------------------------------------------------------------- */
/* file name   : EthDLC_DLC.h                                                 */
/* -------------------------------------------------------------------------- */
#ifndef ETHDLC_DLC_H_
#define ETHDLC_DLC_H_
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
#include <EthSwt.h>
/* -------------------------------------------------------------------------- */
#define DLC_PORT_IDX                    6u
#define ETHDLC_DLC_PORT_ON              EthSwt_SetSwitchPortMode(DLC_PORT_IDX, DLC_PORT_IDX, ETH_MODE_ACTIVE)
#define ETHDLC_DLC_PORT_OFF             EthSwt_SetSwitchPortMode(DLC_PORT_IDX, DLC_PORT_IDX, ETH_MODE_DOWN)
#define ETHDLC_GET_DLC_LINK_STATE(ptr)  EthSwt_GetLinkState(DLC_PORT_IDX, DLC_PORT_IDX, ptr)
/* -------------------------------------------------------------------------- */
void EthDLC_DLC_Init(void);
void EthDLC_DLC_LoProc(void);
Std_ReturnType EthDLC_DLC_GetACTLStatus(void);
/* -------------------------------------------------------------------------- */
#endif/*ETHDLC_DLC_H_*/
