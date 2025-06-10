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
    Eth_ModeType            portMode __attribute__((aligned(4)));                               /* 4byte */
    uint8                   indMode __attribute__((aligned(4)));                                /* 1byte */
    EthTrcv_LinkStateType   linkStatus __attribute__((aligned(4)));                             /* 1byte */
    Std_ReturnType          linkGetResult __attribute__((aligned(4)));                          /* 1byte */
    uint8                   frameDiscardFactor[5] __attribute__((aligned(4)));                  /* 5byte */
    uint32                  ingressDiscardNum __attribute__((aligned(4)));                      /* 4byte */
    uint32                  egressDiscardNum __attribute__((aligned(4)));                       /* 4byte */
    uint8                   tcamInfo[4] __attribute__((aligned(4)));                            /* 4byte */
    uint8                   flowMeterInfo[4] __attribute__((aligned(4)));                       /* 4byte */
    uint8                   sqiValue __attribute__((aligned(4)));                               /* 1byte */
    uint8                   sqiGetResult __attribute__((aligned(4)));                           /* 1byte */
} S_ETHSWT_DATA_FOR_PORT;                                           /* Total: 30byte */

typedef struct {
    EthSwt_StateType        ethswtStatus;                           /* 1byte */
    S_ETHSWT_DATA_FOR_PORT  portData[D_ETHSWT_DATA_USE_PORT_NUM] __attribute__((aligned(4)));   /* 180byte */
} S_ETHSWT_DATA_CHIPCOM;                                            /* Total: 181byte */
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void);
void EthSwt_Data_LoProc(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_DATA_H */
/* -------------------------------------------------------------------------- */
