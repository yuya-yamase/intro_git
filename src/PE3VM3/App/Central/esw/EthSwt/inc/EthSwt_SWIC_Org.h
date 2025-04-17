#ifndef ETHSWT_SWIC_ORG_H
#define ETHSWT_SWIC_ORG_H

void EthSwt_SWIC_Org_WaitMS(const uint32 tmo);
void EthSwt_SWIC_Org_WaitSPI(void);
void EthSwt_SWIC_Org_Reset(void);
Std_ReturnType EthSwt_SWIC_Org_INTN(void);
void EthSwt_SWIC_Org_ResetSig_Hi(void);
void EthSwt_SWIC_Org_ResetSig_Lo(void);
void EthSwt_SWIC_Org_Init(void);
void EthSwt_SWIC_Org_DeInit(void);
void EthSwt_SWIC_Org_MainFunction(void);

#endif /* ETHSWT_SWIC_ORG_H */
