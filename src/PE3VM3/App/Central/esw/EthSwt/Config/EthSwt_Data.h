/* -------------------------------------------------------------------------- */
/* file name  :  EthSwt_Data.h                                                */
/* -------------------------------------------------------------------------- */
#ifndef ETHSWT_DATA_H
#define ETHSWT_DATA_H
/* -------------------------------------------------------------------------- */
#include <Std_Types.h>
/* -------------------------------------------------------------------------- */
#include <EthSwt_SWIC_Cfg.h>
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_DATA_CYCLE                 (5U)
#define D_ETHSWT_DATA_GET_LINK_CYCLE        (5U)
#define D_ETHSWT_DATA_GET_MIB_CYCLE         (100U)
#define D_ETHSWT_DATA_GET_SQI_CYCLE         (5U)
#define D_ETHSWT_DATA_GET_QCI_CYCLE         (20U)
/* -------------------------------------------------------------------------- */
#define D_ETHSWT_DATA_LINK_ADC_ID           (0U)
#define D_ETHSWT_DATA_LINK_DCM_ID           (1U)
#define D_ETHSWT_DATA_LINK_SAIL_ID          (2U)
#define D_ETHSWT_DATA_LINK_TOOL_ID          (3U)
#define D_ETHSWT_DATA_LINK_LINUX_ID         (4U)
#define D_ETHSWT_DATA_LINK_ANDROID_ID       (5U)
#define D_ETHSWT_DATA_LINK_NUM              (6U)

#define D_ETHSWT_DATA_MIB_ADC_ID            (0U)
#define D_ETHSWT_DATA_MIB_DCM_ID            (1U)
#define D_ETHSWT_DATA_MIB_SAIL_ID           (2U)
#define D_ETHSWT_DATA_MIB_TOOL_ID           (3U)
#define D_ETHSWt_DATA_MIB_LINUX_ID          (4U)
#define D_ETHSWT_DATA_MIB_ANDROID_ID        (5U)
#define D_ETHSWT_DATA_MIB_NUM               (6U)

#define D_ETHSWT_DATA_SQI_ADC_ID            (0U)
#define D_ETHSWT_DATA_SQI_DCM_ID            (1U)
#define D_ETHSWT_DATA_SQI_NUM               (2U)

#define D_ETHSWT_DATA_QCI_DCM_TCP_ID        (0U)
#define D_ETHSWT_DATA_QCI_DCM_UDP_ID        (1U)
#define D_ETHSWT_DATA_QCI_DCM_ICMP_ID       (2U)
#define D_ETHSWT_DATA_QCI_DLC_TCP_ID        (3U)
#define D_ETHSWT_DATA_QCI_DLC_UDP_ID        (4U)
#define D_ETHSWT_DATA_QCI_NUM               (5U)

#define D_ETHSWT_DATA_USE_PORT_NUM          (6U)

#define D_ETHSWT_SWIC_ADC_PORT_ID           (0U)
#define D_ETHSWT_SWIC_DCM_PORT_ID           (1U)
#define D_ETHSWT_SWIC_SAIL_PORT_ID          (4U)
#define D_ETHSWT_SWIC_TOOL_PORT_ID          (5U)
#define D_ETHSWT_SWIC_LINUX_PORT_ID         (6U)
#define D_ETHSWT_SWIC_ANDROID_PORT_ID       (7U)
/* -------------------------------------------------------------------------- */

#pragma pack(1)
/* -------------------------------------------------------------------------- */
typedef struct {
    Std_ReturnType                  linkGetResult;                          /* 1byte */
    EthTrcv_LinkStateType           linkStatus;                             /* 1byte */
} S_ETHSWT_DATA_LINK_PER_PORT;                                              /* Total: 2byte */

typedef struct {
    S_ETHSWT_DATA_LINK_PER_PORT     link[D_ETHSWT_DATA_LINK_NUM];           /* 12byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_LINK;                                                       /* Total: 16byte */
/* -------------------------------------------------------------------------- */
// typedef struct {
//     uint32                          InFCSErr;                               /* 4byte */
//     uint32                          InDiscards;                             /* 4byte */
//     uint32                          InFiltered;                             /* 4byte */
//     uint32                          InOversize;                             /* 4byte */
//     uint32                          InUndersize;                            /* 4byte */
//     uint32                          Tcam0;                                  /* 4byte */
//     uint32                          Tcam1;                                  /* 4byte */
//     uint32                          Tcam2;                                  /* 4byte */
//     uint32                          Tcam3;                                  /* 4byte */
//     uint32                          reserved;                               /* 4byte */
// } S_ETHSWT_DATA_MIB_PER_PORT;                                               /* Total: 20byte */

typedef struct {
    uint32                          mib[D_ETHSWT_DATA_MIB_NUM][D_ETHSWT_SWIC_MIB_NUM + 1];             /* 240byte */ /* +1‚Íreserve*/
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_MIB;                                                        /* Total: 244byte */
/* -------------------------------------------------------------------------- */
typedef struct {
    Std_ReturnType                  sqiGetResult;                           /* 1byte */
    uint8                           sqiValue;                               /* 1byte */   
} S_ETHSWT_DATA_SQI_PER_PORT;                                               /* Total: 2byte */

typedef struct {
    S_ETHSWT_DATA_SQI_PER_PORT      sqi[D_ETHSWT_DATA_SQI_NUM];             /* 4byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_SQI;                                                        /* Total: 8byte */
/* -------------------------------------------------------------------------- */
typedef struct {
    uint32                          qciCount[D_ETHSWT_DATA_QCI_NUM];        /* 20byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_QCI;                                                        /* Total: 24byte */
/* -------------------------------------------------------------------------- */
#pragma pack()
/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void);
void EthSwt_Data_LoProc(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_DATA_H */
/* -------------------------------------------------------------------------- */
