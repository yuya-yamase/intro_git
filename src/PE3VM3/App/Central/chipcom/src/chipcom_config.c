#include "chipcom.h"
#include "chipcom_config.h"
/* #include "EthSwt_SWIC_Reg.h" */
/* #include "CanIfProxy.h" */

#ifdef CHIPCOM_MCU_SETTING  /* MCU ChipCom */ /* See chipcom_config.h */
NotifcataionTable NotificationFunction[CHIPCOM_DATAID_MAX] = {
    /* {DataId,                                   FunctionPtr} */
    {CHIPCOM_DATAID_DUMMY                      ,  ChipCom_Nop                       },   /* Index 0 not support */
    {CHIPCOM_DATAID_CANIFPROXY_TRANSMIT        ,  ChipCom_Nop                       },   /* MCU receive     CanIfProxy_Transmit*/
    {CHIPCOM_DATAID_CANIFPROXY_CANCELTRANSMIT  ,  ChipCom_Nop                       },   /* MCU receive     CanIfProxy_CancelTransmit*/
    {CHIPCOM_DATAID_CANTP_TPTXCONF             ,  ChipCom_Nop                       },   /* MCU not receive CanTp_TpTxConfiramtion */
    {CHIPCOM_DATAID_CANTP_RXIND                ,  ChipCom_Nop                       },   /* MCU not receive CanTp_RxIndication */
    {CHIPCOM_DATAID_ETHERSWT_RIDCLEAR          ,  ChipCom_Nop                       },   /* MCU receive     EthSwt_SWIC_Reg_RidClear */
    {CHIPCOM_DATAID_VIS_TIME                   ,  ChipCom_Nop                       },   /* MCU receive     Vis_TimeStsReq */
};
#else /* SAIL ChipCom */
NotifcataionTable NotificationFunction[CHIPCOM_DATAID_MAX] = {
    /* {DataId,                                   FunctionPtr} */
    {CHIPCOM_DATAID_DUMMY                      ,  ChipCom_Nop                       },   /* Index 0 not support */
    {CHIPCOM_DATAID_CANIFPROXY_TRANSMIT        ,  ChipCom_Nop                       },   /* SAIL not receive CanIfProxy_Transmit*/
    {CHIPCOM_DATAID_CANIFPROXY_CANCELTRANSMIT  ,  ChipCom_Nop                       },   /* SAIL not receive CanIfProxy_CancelTransmit*/
    {CHIPCOM_DATAID_CANTP_TPTXCONF             ,  ChipCom_Nop                       },   /* SAIL receive     CanIfStub_TxConfiramtion */
    {CHIPCOM_DATAID_CANTP_RXIND                ,  ChipCom_Nop                       },   /* SAIL receive     CanIfStub_RxIndication */
    {CHIPCOM_DATAID_ETHERSWT_RIDCLEAR          ,  ChipCom_Nop                       },   /* SAIL not receive EthSwt_SWIC_Reg_RidClear */
    {CHIPCOM_DATAID_VIS_TIME                   ,  ChipCom_Nop                       },   /* SAIL not receive Vis_TimeStsReq */
};
#endif


uint8 ChipCom_Initval_EtherSwt_Port1ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT1MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_Port2ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT2MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_Port5ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT5MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_Port6ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT6MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_Port7ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT7MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_Port8ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT8MODEREQ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_EtherSwt_McuInfo     [CHIPCOM_LENGTH_ETHERSWT_MCUINFO     ] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*50*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*100*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*150*/
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00
};
uint8 ChipCom_Initval_DoIPMgr_DoIPComPwr   [CHIPCOM_LENGTH_DOIPMGR_DOIPCOMPWR   ] = {
    0x00
};
uint8 ChipCom_Initval_Vis_Utc              [CHIPCOM_LENGTH_VIS_UTC              ] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};
uint8 ChipCom_Initval_Vis_Odo              [CHIPCOM_LENGTH_VIS_ODO              ] = {
    0x00, 0x00, 0x00, 0x00
};
uint8 ChipCom_Initval_Vis_Volt             [CHIPCOM_LENGTH_VIS_VOLT             ] = {
    0x00
};
uint8 ChipCom_Initval_Vis_Trip             [CHIPCOM_LENGTH_VIS_TRIP             ] = {
    0xFF, 0xFF, 0x00
};
uint8 ChipCom_Initval_Vis_Spd              [CHIPCOM_LENGTH_VIS_SPD              ] = {
    0xFF
};
uint8 ChipCom_Initval_Vis_RdySts           [CHIPCOM_LENGTH_VIS_RDYSTS           ] = {
    0x00
};
uint8 ChipCom_Initval_Vis_BasicState       [CHIPCOM_LENGTH_VIS_BASICSTATE       ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_SpecialState     [CHIPCOM_LENGTH_VIS_SPECIALSTATE     ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_TransFlg         [CHIPCOM_LENGTH_VIS_TRANSFLG         ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_OtaSwAct         [CHIPCOM_LENGTH_VIS_OTASWACT         ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_PwrErrSt         [CHIPCOM_LENGTH_VIS_PWRERRST         ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_CRlyOf           [CHIPCOM_LENGTH_VIS_CRLYOF           ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_Vis_Vin              [CHIPCOM_LENGTH_VIS_VIN              ] = {
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 
    0x3F, 0x3F, 0x00
};
uint8 ChipCom_Initval_Vis_ComPwr           [CHIPCOM_LENGTH_VIS_COMPWR           ] = {
    0x00
};
uint8 ChipCom_Initval_EtherSwt_RegErrSts   [CHIPCOM_LENGTH_ETHERSWT_REGERRSTS   ] = {
    0x00, 0x00
};
uint8 ChipCom_Initval_EtherMgr_MacAddr     [CHIPCOM_LENGTH_ETHERMGR_MACADDR     ] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

PeriodicTable PeriodicRelation[CHIPCOM_PERIODICID_MAX] = {
    /*PeriodicId                                    DataLen                                 TxDataPos                               RxDataPos                               INIT                                */
    {CHIPCOM_PERIODICID_ETHERSWT_PORT1MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT1MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT1MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT1MODEREQ  , ChipCom_Initval_EtherSwt_Port1ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_PORT2MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT2MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT2MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT2MODEREQ  , ChipCom_Initval_EtherSwt_Port2ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_PORT5MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT5MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT5MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT5MODEREQ  , ChipCom_Initval_EtherSwt_Port5ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_PORT6MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT6MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT6MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT6MODEREQ  , ChipCom_Initval_EtherSwt_Port6ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_PORT7MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT7MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT7MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT7MODEREQ  , ChipCom_Initval_EtherSwt_Port7ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_PORT8MODEREQ    ,  CHIPCOM_LENGTH_ETHERSWT_PORT8MODEREQ  , CHIPCOM_POS_TX_ETHERSWT_PORT8MODEREQ  , CHIPCOM_POS_RX_ETHERSWT_PORT8MODEREQ  , ChipCom_Initval_EtherSwt_Port8ModeReq   },
    {CHIPCOM_PERIODICID_ETHERSWT_MCUINFO         ,  CHIPCOM_LENGTH_ETHERSWT_MCUINFO       , CHIPCOM_POS_TX_ETHERSWT_MCUINFO       , CHIPCOM_POS_RX_ETHERSWT_MCUINFO       , ChipCom_Initval_EtherSwt_McuInfo        },
    {CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR       ,  CHIPCOM_LENGTH_DOIPMGR_DOIPCOMPWR     , CHIPCOM_POS_TX_DOIPMGR_DOIPCOMPWR     , CHIPCOM_POS_RX_DOIPMGR_DOIPCOMPWR     , ChipCom_Initval_DoIPMgr_DoIPComPwr      },
    {CHIPCOM_PERIODICID_VIS_UTC                  ,  CHIPCOM_LENGTH_VIS_UTC                , CHIPCOM_POS_TX_VIS_UTC                , CHIPCOM_POS_RX_VIS_UTC                , ChipCom_Initval_Vis_Utc                 },
    {CHIPCOM_PERIODICID_VIS_ODO                  ,  CHIPCOM_LENGTH_VIS_ODO                , CHIPCOM_POS_TX_VIS_ODO                , CHIPCOM_POS_RX_VIS_ODO                , ChipCom_Initval_Vis_Odo                 },
    {CHIPCOM_PERIODICID_VIS_VOLT                 ,  CHIPCOM_LENGTH_VIS_VOLT               , CHIPCOM_POS_TX_VIS_VOLT               , CHIPCOM_POS_RX_VIS_VOLT               , ChipCom_Initval_Vis_Volt                },
    {CHIPCOM_PERIODICID_VIS_TRIP                 ,  CHIPCOM_LENGTH_VIS_TRIP               , CHIPCOM_POS_TX_VIS_TRIP               , CHIPCOM_POS_RX_VIS_TRIP               , ChipCom_Initval_Vis_Trip                },
    {CHIPCOM_PERIODICID_VIS_SPD                  ,  CHIPCOM_LENGTH_VIS_SPD                , CHIPCOM_POS_TX_VIS_SPD                , CHIPCOM_POS_RX_VIS_SPD                , ChipCom_Initval_Vis_Spd                 },
    {CHIPCOM_PERIODICID_VIS_RDYSTS               ,  CHIPCOM_LENGTH_VIS_RDYSTS             , CHIPCOM_POS_TX_VIS_RDYSTS             , CHIPCOM_POS_RX_VIS_RDYSTS             , ChipCom_Initval_Vis_RdySts              },
    {CHIPCOM_PERIODICID_VIS_BASICSTATE           ,  CHIPCOM_LENGTH_VIS_BASICSTATE         , CHIPCOM_POS_TX_VIS_BASICSTATE         , CHIPCOM_POS_RX_VIS_BASICSTATE         , ChipCom_Initval_Vis_BasicState          },
    {CHIPCOM_PERIODICID_VIS_SPECIALSTATE         ,  CHIPCOM_LENGTH_VIS_SPECIALSTATE       , CHIPCOM_POS_TX_VIS_SPECIALSTATE       , CHIPCOM_POS_RX_VIS_SPECIALSTATE       , ChipCom_Initval_Vis_SpecialState        },
    {CHIPCOM_PERIODICID_VIS_TRANSFLG             ,  CHIPCOM_LENGTH_VIS_TRANSFLG           , CHIPCOM_POS_TX_VIS_TRANSFLG           , CHIPCOM_POS_RX_VIS_TRANSFLG           , ChipCom_Initval_Vis_TransFlg            },
    {CHIPCOM_PERIODICID_VIS_OTASWACT             ,  CHIPCOM_LENGTH_VIS_OTASWACT           , CHIPCOM_POS_TX_VIS_OTASWACT           , CHIPCOM_POS_RX_VIS_OTASWACT           , ChipCom_Initval_Vis_OtaSwAct            },
    {CHIPCOM_PERIODICID_VIS_PWRERRST             ,  CHIPCOM_LENGTH_VIS_PWRERRST           , CHIPCOM_POS_TX_VIS_PWRERRST           , CHIPCOM_POS_RX_VIS_PWRERRST           , ChipCom_Initval_Vis_PwrErrSt            },
    {CHIPCOM_PERIODICID_VIS_CRLYOF               ,  CHIPCOM_LENGTH_VIS_CRLYOF             , CHIPCOM_POS_TX_VIS_CRLYOF             , CHIPCOM_POS_RX_VIS_CRLYOF             , ChipCom_Initval_Vis_CRlyOf              },
    {CHIPCOM_PERIODICID_VIS_VIN                  ,  CHIPCOM_LENGTH_VIS_VIN                , CHIPCOM_POS_TX_VIS_VIN                , CHIPCOM_POS_RX_VIS_VIN                , ChipCom_Initval_Vis_Vin                 },
    {CHIPCOM_PERIODICID_VIS_COMPWR               ,  CHIPCOM_LENGTH_VIS_COMPWR             , CHIPCOM_POS_TX_VIS_COMPWR             , CHIPCOM_POS_RX_VIS_COMPWR             , ChipCom_Initval_Vis_ComPwr              },
    {CHIPCOM_PERIODICID_ETHERSWT_REGERRSTS       ,  CHIPCOM_LENGTH_ETHERSWT_REGERRSTS     , CHIPCOM_POS_TX_ETHERSWT_REGERRSTS     , CHIPCOM_POS_RX_ETHERSWT_REGERRSTS     , ChipCom_Initval_EtherSwt_RegErrSts      },
    {CHIPCOM_PERIODICID_ETHERMGR_MACADDR         ,  CHIPCOM_LENGTH_ETHERMGR_MACADDR       , CHIPCOM_POS_TX_ETHERMGR_MACADDR       , CHIPCOM_POS_RX_ETHERMGR_MACADDR       , ChipCom_Initval_EtherMgr_MacAddr        },
};
