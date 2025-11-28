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

#define D_ETHSWT_DATA_INFCSERR_ID           D_ETHSWT_SWIC_MIB_INFCSERR
#define D_ETHSWT_DATA_INDISCARDS_ID         D_ETHSWT_SWIC_MIB_INDISCARDS
#define D_ETHSWT_DATA_INFILTERED_ID         D_ETHSWT_SWIC_MIB_INFILTERED
#define D_ETHSWT_DATA_INOVERSIZE_ID         D_ETHSWT_SWIC_MIB_INOVERSIZE
#define D_ETHSWT_DATA_INUNDERSIZE_ID        D_ETHSWT_SWIC_MIB_INUNDERSIZE
#define D_ETHSWT_DATA_TCAM0_ID              D_ETHSWT_SWIC_MIB_TCAM0
#define D_ETHSWT_DATA_TCAM1_ID              D_ETHSWT_SWIC_MIB_TCAM1
#define D_ETHSWT_DATA_TCAM2_ID              D_ETHSWT_SWIC_MIB_TCAM2
#define D_ETHSWT_DATA_TCAM3_ID              D_ETHSWT_SWIC_MIB_TCAM3
#define D_ETHSWT_DATA_RESERVED              (9U)
#define D_ETHSWT_DATA_MIB_ID_NUM            (10U)

#define D_ETHSWT_DATA_SQI_ADC_ID            (0U)
#define D_ETHSWT_DATA_SQI_DCM_ID            (1U)
#define D_ETHSWT_DATA_SQI_NUM               (2U)

#define D_ETHSWT_DATA_QCI_DCM_TCP_ID        (0U)
#define D_ETHSWT_DATA_QCI_DCM_UDP_ID        (1U)
#define D_ETHSWT_DATA_QCI_DCM_ICMP_ID       (2U)
#define D_ETHSWT_DATA_QCI_DLC_TCP_ID        (3U)
#define D_ETHSWT_DATA_QCI_DLC_UDP_ID        (4U)
#define D_ETHSWT_DATA_QCI_NUM               (5U)

#define D_ETHSWT_DATA_REGACCESS_SAIL_ID     (0U)
#define D_ETHSWT_DATA_REGACCESS_NUM         (1U)
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
    Std_ReturnType                  linkGetResult;                          /* 1byte */
    EthTrcv_LinkStateType           linkStatus;                             /* 1byte */
} S_ETHSWT_DATA_LINK_PER_PORT;                                              /* Total: 2byte */

typedef struct {
    S_ETHSWT_DATA_LINK_PER_PORT     link[D_ETHSWT_DATA_LINK_NUM];           /* 12byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_LINK;                                                       /* Total: 16byte */
#pragma pack()
/* -------------------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
    uint32                          mib[D_ETHSWT_DATA_MIB_NUM][D_ETHSWT_DATA_MIB_ID_NUM];             /* 240byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_MIB;                                                        /* Total: 244byte */
#pragma pack()
/* -------------------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
    Std_ReturnType                  sqiGetResult;                           /* 1byte */
    uint8                           sqiValue;                               /* 1byte */   
} S_ETHSWT_DATA_SQI_PER_PORT;                                               /* Total: 2byte */

typedef struct {
    S_ETHSWT_DATA_SQI_PER_PORT      sqi[D_ETHSWT_DATA_SQI_NUM];             /* 4byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_SQI;                                                        /* Total: 8byte */
#pragma pack()
/* -------------------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
    uint32                          qciCount[D_ETHSWT_DATA_QCI_NUM];        /* 20byte */
    uint32                          id;                                     /* 4byte */
} S_ETHSWT_DATA_QCI;                                                        /* Total: 24byte */
#pragma pack()
/* -------------------------------------------------------------------------- */
#pragma pack(1)
typedef struct {
	Std_ReturnType                  getRegAccessResult;                       /* 1byte */
    uint32                          id;                                      /* 4byte */
} S_ETHSWT_DATA_REGACCESS;                                                   /* Total: 5byte */
#pragma pack()
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
void EthSwt_Data_Init(void);
void EthSwt_Data_LoProc(void);
void EthSwt_Data_NotifyLink(const uint8 SwitchPortIdx, const Std_ReturnType getLinkResult, const EthTrcv_LinkStateType linkState);
void EthSwt_Data_NotifyMIB(const uint8 SwitchPortIdx, const uint32 *const MIBArray);
void EthSwt_Data_NotifySQI(const uint8 SwtichPortIdx, const Std_ReturnType getSQIResult, const uint8 SQIValue);
void EthSwt_Data_NotifyQci(const uint8 QciIdx, const uint32 QciCount);
void EthSwt_Data_NotifyRegAccess(const Std_ReturnType getRegAccessResult);
void EthSwt_Data_NotifySWICReset(void);
/* -------------------------------------------------------------------------- */
#endif /* ETHSWT_DATA_H */
/* -------------------------------------------------------------------------- */
