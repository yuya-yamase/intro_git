/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_Data.h                                                */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_DATA_H
#define ETHSWT_DATA_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Core_Cfg.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_DATA_USE_PORT_NUM          (6U)
/* -------------------------------------------------------------------------- */
typedef struct {
    Eth_ModeType            portMode;
    uint8                   indMode;
    EthTrcv_LinkStateType   linkStatus;
    Std_ReturnType          linkGetResult;
    uint8                   frameDiscardFactor[5];
    uint32                  ingressDiscardNum;
    uint32                  egressDiscardNum;
    uint8                   tcamInfo[4];
    uint8                   flowMeterInfo[4];
    uint8                   sqiValue;
    uint8                   sqiGetResult;
} S_ETHSWT_DATA_FOR_PORT;

typedef struct {
    EthSwt_StateType        ethswtStatus;
    S_ETHSWT_DATA_FOR_PORT  portData[D_ETHSWT_DATA_USE_PORT_NUM];
} S_ETHSWT_DATA_CHIPCOM;
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void);
void EthSwt_Data_LoProc(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_DATA_H */
/* -------------------------------------------------------------------------- */
