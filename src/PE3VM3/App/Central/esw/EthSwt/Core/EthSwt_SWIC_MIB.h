/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_SWIC_MIB.h                                           */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_SWIC_MIB_H
#define ETHSWT_SWIC_MIB_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
typedef struct {
	uint32	IngressCount;
	uint32	EgressCount;
} S_ETHSWT_SWIC_MIB_COUNT;


/* -------------------------------------------------------------------------- */
void EthSwt_SWIC_MIB_Init (void);
void EthSwt_SWIC_MIB_TimerUpdate (void);
void EthSwt_SWIC_MIB_Clear (void);
Std_ReturnType EthtSwt_SWIC_MIB_ReadDiscard (uint32 * const errFactor);
Std_ReturnType EthSwt_SWIC_MIB_Action (uint32 * const errFactor);
Std_ReturnType EthSwt_SWIC_MIB_Get(uint8 SwitchPortIdx, uint32 Mib, S_ETHSWT_SWIC_MIB_COUNT *MibListPtr);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_SWIC_MIB_H */
/* -------------------------------------------------------------------------- */
