#ifndef ETH_GENERALTYPES_H          /* BSW ETH‚Å’è‹`‚µ‚Ä‚¢‚é‚à‚Ì‚ð–Í‹[‚µ‚Ä‚¢‚é */
#define ETH_GENERALTYPES_H

#ifndef ETHSWT_BSW_DEFINE_H
#define ETHSWT_BSW_DEFINE_H

/*--------------------------------------------------------------------------*/
/* Ethernet Driver                                                          */
/*--------------------------------------------------------------------------*/
typedef uint32 Eth_ModeType;    /* Enumeration */
#define ETH_MODE_DOWN                           (0U)
#define ETH_MODE_ACTIVE                         (1U)
#define ETH_MODE_ACTIVE_WITH_WAKEUP_REQUEST     (2U)

typedef uint8 Eth_DataType;     /* uint8 / uint16 / uint32 */

typedef uint32 Eth_BufIdxType;

typedef struct {
    uint32 nanoseconds;
    uint32 seconds;
    uint16 secondsHi;
} Eth_TimeStampType;

/*--------------------------------------------------------------------------*/
/* Ethernet Transceiver Driver                                              */
/*--------------------------------------------------------------------------*/
typedef uint8 EthTrcv_LinkStateType; /* Enumeration */
#define ETHTRCV_LINK_STATE_DOWN                 (0U)
#define ETHTRCV_LINK_STATE_ACTIVE               (1U)

typedef uint8 EthTrcv_WakeupReasonType; /* Enumeration */
#define ETHTRCV_WUR_NONE                        (0U)
#define ETHTRCV_WUR_GENERAL                     (1U)
#define ETHTRCV_WUR_BUS                         (2U)
#define ETHTRCV_WUR_INTERNAL                    (3U)
#define ETHTRCV_WUR_RESET                       (4U)
#define ETHTRCV_WUR_POWER_ON                    (5U)
#define ETHTRCV_WUR_PIN                         (6U)
#define ETHTRCV_WUR_SYSERR                      (7U)
#define ETHTRCV_WUR_WODL_WUP                    (8U)
#define ETHTRCV_WUR_WODL_WUR                    (9U)
#define ETHTRCV_WUR_TRANSFER                    (10U)

/*--------------------------------------------------------------------------*/
/* Ethernet Switch Driver                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8 EthSwt_StateType; /* Enumeration */
#define ETHSWT_STATE_UNINIT                     (0x00U)
#define ETHSWT_STATE_INIT                       (0x01U)
#define ETHSWT_STATE_PORTINIT_COMPLETED         (0x02U)
#define ETHSWT_STATE_ACTIVE                     (0x03U)

typedef struct {
    uint8 SwitchIdx;
    uint8 SwitchPortIdx;
} EthSwt_MgmtInfoType;

typedef uint8 EthSwt_MgmtOwner; /* Enumeration */
#define ETHSWT_MGMT_OBJ_UNUSED                  (0x00U)
#define ETHSWT_MGMT_OBJ_OWNED_BY_ETHSWT         (0x01U)
#define ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER    (0x02U)

typedef struct {
    Std_ReturnType IngressTimestampValid;
    Std_ReturnType EgressTimestampValid;
    Std_ReturnType MgmtInfoValid;
} EthSwt_MgmtObjectValidType;

typedef struct {
    EthSwt_MgmtObjectValidType Validation;
    Eth_TimeStampType IngressTimestamp;
    Eth_TimeStampType EgressTimestamp;
    EthSwt_MgmtInfoType MgmtInfo;
    EthSwt_MgmtOwner Ownership;
} EthSwt_MgmtObjectType;


#endif  /* ETHSWT_BSW_DEFINE_H */
#endif  /* ETH_GENERALTYPES_H */
