/* v0-3-0-mcu03 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  chipcom_config.h                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/


#ifndef CHIPCOM_CONFIG_H
#define CHIPCOM_CONFIG_H

#include "Std_Types.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef enum {
    CHIPCOM_DATAID_DUMMY = 0x00U,
    CHIPCOM_DATAID_CANIFPROXY_TRANSMIT,
    CHIPCOM_DATAID_CANIFPROXY_CANCELTRANSMIT,
    CHIPCOM_DATAID_CANTP_TPTXCONF,                          /* TpTxConfirmation */
    CHIPCOM_DATAID_CANTP_RXIND,                             /* RxIndication */
    CHIPCOM_DATAID_ETHERSWT_RIDCLEAR,
    CHIPCOM_DATAID_VIS_TIME,
    CHIPCOM_DATAID_MAX
} CHIPCOM_DATAID;

typedef enum {
    CHIPCOM_PERIODICID_ETHERSWT_PORT1MODEREQ = 0x00U,
    CHIPCOM_PERIODICID_ETHERSWT_PORT2MODEREQ,
    CHIPCOM_PERIODICID_ETHERSWT_PORT5MODEREQ,
    CHIPCOM_PERIODICID_ETHERSWT_PORT6MODEREQ,
    CHIPCOM_PERIODICID_ETHERSWT_PORT7MODEREQ,
    CHIPCOM_PERIODICID_ETHERSWT_PORT8MODEREQ,
    CHIPCOM_PERIODICID_ETHERSWT_MCUINFO,
    CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR,
    CHIPCOM_PERIODICID_VIS_UTC,
    CHIPCOM_PERIODICID_VIS_ODO,
    CHIPCOM_PERIODICID_VIS_VOLT,
    CHIPCOM_PERIODICID_VIS_TRIP,
    CHIPCOM_PERIODICID_VIS_SPD,
    CHIPCOM_PERIODICID_VIS_RDYSTS,
    CHIPCOM_PERIODICID_VIS_BASICSTATE,
    CHIPCOM_PERIODICID_VIS_SPECIALSTATE,
    CHIPCOM_PERIODICID_VIS_TRANSFLG,
    CHIPCOM_PERIODICID_VIS_OTASWACT,
    CHIPCOM_PERIODICID_VIS_PWRERRST,
    CHIPCOM_PERIODICID_VIS_CRLYOF,
    CHIPCOM_PERIODICID_VIS_VIN,
    CHIPCOM_PERIODICID_VIS_COMPWR,
    CHIPCOM_PERIODICID_ETHERSWT_REGERRSTS,
    CHIPCOM_PERIODICID_ETHERMGR_MACADDR,
    CHIPCOM_PERIODICID_VSM_SLEEPNG,
    CHIPCOM_PERIODICID_ETHERSWT_SWIC_LINKINFO,
    CHIPCOM_PERIODICID_ETHERSWT_SWIC_MIB,
    CHIPCOM_PERIODICID_ETHERSWT_SWIC_SQI,
    CHIPCOM_PERIODICID_ETHERSWT_SWIC_DATAUSAGEEXCEED,
    CHIPCOM_PERIODICID_MAX
} CHIPCOM_PERIODICID;

#define CHIPCOM_LENGTH_ETHERSWT_PORT1MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_PORT2MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_PORT5MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_PORT6MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_PORT7MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_PORT8MODEREQ            ((uint16)4U)
#define CHIPCOM_LENGTH_ETHERSWT_MCUINFO                 ((uint16)181U)
#define CHIPCOM_LENGTH_DOIPMGR_DOIPCOMPWR               ((uint16)1U)
#define CHIPCOM_LENGTH_VIS_UTC                          ((uint16)6U)
#define CHIPCOM_LENGTH_VIS_ODO                          ((uint16)4U)
#define CHIPCOM_LENGTH_VIS_VOLT                         ((uint16)1U)
#define CHIPCOM_LENGTH_VIS_TRIP                         ((uint16)3U)
#define CHIPCOM_LENGTH_VIS_SPD                          ((uint16)1U)
#define CHIPCOM_LENGTH_VIS_RDYSTS                       ((uint16)1U)
#define CHIPCOM_LENGTH_VIS_BASICSTATE                   ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_SPECIALSTATE                 ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_TRANSFLG                     ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_OTASWACT                     ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_PWRERRST                     ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_CRLYOF                       ((uint16)2U)
#define CHIPCOM_LENGTH_VIS_VIN                          ((uint16)18U)
#define CHIPCOM_LENGTH_VIS_COMPWR                       ((uint16)1U)
#define CHIPCOM_LENGTH_ETHERSWT_REGERRSTS               ((uint16)2U)
#define CHIPCOM_LENGTH_ETHERMGR_MACADDR                 ((uint16)6U)
#define CHIPCOM_LENGTH_VSM_SLEEPNG                      ((uint16)1U)
#define	CHIPCOM_LENGTH_ETHERSWT_SWIC_LINKINFO           ((uint16)16U)
#define	CHIPCOM_LENGTH_ETHERSWT_SWIC_MIB                ((uint16)244U)
#define	CHIPCOM_LENGTH_ETHERSWT_SWIC_SQI                ((uint16)8U)
#define	CHIPCOM_LENGTH_ETHERSWT_SWIC_DATAUSAGEEXCEED    ((uint16)24U)


extern uint8 ChipCom_Initval_EtherSwt_Port1ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_Port2ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_Port5ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_Port6ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_Port7ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_Port8ModeReq  			[];
extern uint8 ChipCom_Initval_EtherSwt_McuInfo       			[];
extern uint8 ChipCom_Initval_DoIPMgr_DoIPComPwr     			[];
extern uint8 ChipCom_Initval_Vis_Utc                			[];
extern uint8 ChipCom_Initval_Vis_Odo                			[];
extern uint8 ChipCom_Initval_Vis_Volt               			[];
extern uint8 ChipCom_Initval_Vis_Trip               			[];
extern uint8 ChipCom_Initval_Vis_Spd                			[];
extern uint8 ChipCom_Initval_Vis_RdySts             			[];
extern uint8 ChipCom_Initval_Vis_BasicState         			[];
extern uint8 ChipCom_Initval_Vis_SpecialState       			[];
extern uint8 ChipCom_Initval_Vis_TransFlg           			[];
extern uint8 ChipCom_Initval_Vis_OtaSwAct           			[];
extern uint8 ChipCom_Initval_Vis_PwrErrSt           			[];
extern uint8 ChipCom_Initval_Vis_CRlyOf             			[];
extern uint8 ChipCom_Initval_Vis_Vin                			[];
extern uint8 ChipCom_Initval_Vis_ComPwr             			[];
extern uint8 ChipCom_Initval_EtherSwt_RegErrSts     			[];
extern uint8 ChipCom_Initval_EtherMgr_MacAddr       			[];
extern uint8 ChipCom_Initval_Vsm_SleepNg            		    [];
extern uint8 ChipCom_Initval_EtherSwt_Swic_LinkInfo             [];
extern uint8 ChipCom_Initval_EtherSwt_Swic_MIB                  [];
extern uint8 ChipCom_Initval_EtherSwt_Swic_SQI                  [];
extern uint8 ChipCom_Initval_EtherSwt_Swic_DataUsageExceed      [];

#define CHIPCOM_MCU_SETTING

#ifdef CHIPCOM_MCU_SETTING  /* MCU ChipCom */
#define CHIPCOM_POS_TX_ETHERSWT_PORT1MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_PORT2MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_PORT5MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_PORT6MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_PORT7MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_PORT8MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_MCUINFO                     ((uint16) 14U)
#define CHIPCOM_POS_TX_DOIPMGR_DOIPCOMPWR                   ((uint16)196U)
#define CHIPCOM_POS_TX_VIS_UTC                              ((uint16)197U)
#define CHIPCOM_POS_TX_VIS_ODO                              ((uint16)203U)
#define CHIPCOM_POS_TX_VIS_VOLT                             ((uint16)207U)
#define CHIPCOM_POS_TX_VIS_TRIP                             ((uint16)208U)
#define CHIPCOM_POS_TX_VIS_SPD                              ((uint16)211U)
#define CHIPCOM_POS_TX_VIS_RDYSTS                           ((uint16)212U)
#define CHIPCOM_POS_TX_VIS_BASICSTATE                       ((uint16)213U)
#define CHIPCOM_POS_TX_VIS_SPECIALSTATE                     ((uint16)215U)
#define CHIPCOM_POS_TX_VIS_TRANSFLG                         ((uint16)217U)
#define CHIPCOM_POS_TX_VIS_OTASWACT                         ((uint16)219U)
#define CHIPCOM_POS_TX_VIS_PWRERRST                         ((uint16)221U)
#define CHIPCOM_POS_TX_VIS_CRLYOF                           ((uint16)223U)
#define CHIPCOM_POS_TX_VIS_VIN                              ((uint16)225U)
#define CHIPCOM_POS_TX_VIS_COMPWR                           ((uint16)243U)
#define CHIPCOM_POS_TX_ETHERSWT_REGERRSTS                   ((uint16)244U)
#define CHIPCOM_POS_TX_ETHERMGR_MACADDR                     ((uint16)246U)
#define CHIPCOM_POS_TX_VSM_SLEEPNG                          ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_LINKINFO               ((uint16)252U)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_MIB                    ((uint16)268U)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_SQI                    ((uint16)512U)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_DATAUSAGEEXCEED        ((uint16)520U)
#define CHIPCOM_POS_TX_EVENTDATA_OFFSET                     ((uint16)544U)


#define CHIPCOM_POS_RX_ETHERSWT_PORT1MODEREQ                ((uint16) 14U)
#define CHIPCOM_POS_RX_ETHERSWT_PORT2MODEREQ                ((uint16) 18U)
#define CHIPCOM_POS_RX_ETHERSWT_PORT5MODEREQ                ((uint16) 22U)
#define CHIPCOM_POS_RX_ETHERSWT_PORT6MODEREQ                ((uint16) 26U)
#define CHIPCOM_POS_RX_ETHERSWT_PORT7MODEREQ                ((uint16) 30U)
#define CHIPCOM_POS_RX_ETHERSWT_PORT8MODEREQ                ((uint16) 34U)
#define CHIPCOM_POS_RX_ETHERSWT_MCUINFO                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_DOIPMGR_DOIPCOMPWR                   ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_UTC                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_ODO                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_VOLT                             ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_TRIP                             ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_SPD                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_RDYSTS                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_BASICSTATE                       ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_SPECIALSTATE                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_TRANSFLG                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_OTASWACT                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_PWRERRST                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_CRLYOF                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_VIN                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VIS_COMPWR                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_REGERRSTS                   ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERMGR_MACADDR                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_VSM_SLEEPNG                          ((uint16) 38U)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_LINKINFO               ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_MIB                    ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_SQI                    ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_DATAUSAGEEXCEED        ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_EVENTDATA_OFFSET                     ((uint16) 39U)

#else   /* SAIL ChipCom */
#define CHIPCOM_POS_TX_ETHERSWT_PORT1MODEREQ                ((uint16) 14U)
#define CHIPCOM_POS_TX_ETHERSWT_PORT2MODEREQ                ((uint16) 18U)
#define CHIPCOM_POS_TX_ETHERSWT_PORT5MODEREQ                ((uint16) 22U)
#define CHIPCOM_POS_TX_ETHERSWT_PORT6MODEREQ                ((uint16) 26U)
#define CHIPCOM_POS_TX_ETHERSWT_PORT7MODEREQ                ((uint16) 30U)
#define CHIPCOM_POS_TX_ETHERSWT_PORT8MODEREQ                ((uint16) 34U)
#define CHIPCOM_POS_TX_ETHERSWT_MCUINFO                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_DOIPMGR_DOIPCOMPWR                   ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_UTC                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_ODO                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_VOLT                             ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_TRIP                             ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_SPD                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_RDYSTS                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_BASICSTATE                       ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_SPECIALSTATE                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_TRANSFLG                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_OTASWACT                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_PWRERRST                         ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_CRLYOF                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_VIN                              ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VIS_COMPWR                           ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_REGERRSTS                   ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERMGR_MACADDR                     ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_VSM_SLEEPNG                          ((uint16) 38U)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_LINKINFO               ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_MIB                    ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_SQI                    ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_ETHERSWT_SWIC_DATAUSAGEEXCEED        ((uint16)0xFFFFU)
#define CHIPCOM_POS_TX_EVENTDATA_OFFSET                     ((uint16) 39U)


#define CHIPCOM_POS_RX_ETHERSWT_PORT1MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_PORT2MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_PORT5MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_PORT6MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_PORT7MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_PORT8MODEREQ                ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_MCUINFO                     ((uint16) 14U)
#define CHIPCOM_POS_RX_DOIPMGR_DOIPCOMPWR                   ((uint16)196U)
#define CHIPCOM_POS_RX_VIS_UTC                              ((uint16)197U)
#define CHIPCOM_POS_RX_VIS_ODO                              ((uint16)203U)
#define CHIPCOM_POS_RX_VIS_VOLT                             ((uint16)207U)
#define CHIPCOM_POS_RX_VIS_TRIP                             ((uint16)208U)
#define CHIPCOM_POS_RX_VIS_SPD                              ((uint16)211U)
#define CHIPCOM_POS_RX_VIS_RDYSTS                           ((uint16)212U)
#define CHIPCOM_POS_RX_VIS_BASICSTATE                       ((uint16)213U)
#define CHIPCOM_POS_RX_VIS_SPECIALSTATE                     ((uint16)215U)
#define CHIPCOM_POS_RX_VIS_TRANSFLG                         ((uint16)217U)
#define CHIPCOM_POS_RX_VIS_OTASWACT                         ((uint16)219U)
#define CHIPCOM_POS_RX_VIS_PWRERRST                         ((uint16)221U)
#define CHIPCOM_POS_RX_VIS_CRLYOF                           ((uint16)223U)
#define CHIPCOM_POS_RX_VIS_VIN                              ((uint16)225U)
#define CHIPCOM_POS_RX_VIS_COMPWR                           ((uint16)243U)
#define CHIPCOM_POS_RX_ETHERSWT_REGERRSTS                   ((uint16)244U)
#define CHIPCOM_POS_RX_ETHERMGR_MACADDR                     ((uint16)246U)
#define CHIPCOM_POS_RX_VSM_SLEEPNG                          ((uint16)0xFFFFU)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_LINKINFO               ((uint16)252U)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_MIB                    ((uint16)268U)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_SQI                    ((uint16)512U)
#define CHIPCOM_POS_RX_ETHERSWT_SWIC_DATAUSAGEEXCEED        ((uint16)520U)
#define CHIPCOM_POS_RX_EVENTDATA_OFFSET                     ((uint16)544U)

#endif

#define CHIPCOM_DISABLE_INTERRUPT()     LIB_DI()
#define CHIPCOM_ENABLE_INTERRUPT()      LIB_EI()

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef void(*FUNC_PTR)(const uint16, const uint8* const);

typedef struct {
    uint8 DataId;
    FUNC_PTR NotificationFuncPtr;
} NotifcataionTable;

typedef struct {
    uint8   DataId;
    uint16  DataLen;
    uint16  TxPos;
    uint16  RxPos;
    uint8*  InitVal;
} PeriodicTable;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern NotifcataionTable NotificationFunction[CHIPCOM_DATAID_MAX];
extern PeriodicTable PeriodicRelation[CHIPCOM_PERIODICID_MAX];

#endif  /* CHIPCOM_CONFIG_H */
/**** End of File ***********************************************************/


