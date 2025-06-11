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
#pragma pack(1)
typedef struct {
    Eth_ModeType            portMode;                               /* 4byte */
    uint8                   indMode;                                /* 1byte */
    EthTrcv_LinkStateType   linkStatus;                             /* 1byte */
    Std_ReturnType          linkGetResult;                          /* 1byte */
    uint8                   frameDiscardFactor[5];                  /* 5byte */
    uint32                  ingressDiscardNum;                      /* 4byte */
    uint32                  egressDiscardNum;                       /* 4byte */
    uint8                   tcamInfo[4];                            /* 4byte */
    uint8                   flowMeterInfo[4];                       /* 4byte */
    uint8                   sqiValue;                               /* 1byte */
    uint8                   sqiGetResult;                           /* 1byte */
} S_ETHSWT_DATA_FOR_PORT;                                           /* Total: 30byte */

typedef struct {
    EthSwt_StateType        ethswtStatus;                           /* 1byte */
    S_ETHSWT_DATA_FOR_PORT  portData[D_ETHSWT_DATA_USE_PORT_NUM];   /* 180byte */
} S_ETHSWT_DATA_CHIPCOM;                                            /* Total: 181byte */
#pragma pack()
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void);
void EthSwt_Data_LoProc(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_DATA_H */
/* -------------------------------------------------------------------------- */
