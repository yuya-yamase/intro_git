/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
//#include "LcomSpi_Fake.h"
#include "chipcom.h"
#include "chipcom_user_fake.h"
#include "xspi.h"


#ifdef CHIPCOM_MCU_SETTING  /* MCU ChipCom */ /* See chipcom_config.h */
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
volatile uint8 u1_send_flag = 0x00;

static uint8 FakeBuff_EtherSwt_Port1ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT1MODEREQ];
static uint8 FakeBuff_EtherSwt_Port2ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT2MODEREQ];
static uint8 FakeBuff_EtherSwt_Port5ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT5MODEREQ];
static uint8 FakeBuff_EtherSwt_Port6ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT6MODEREQ];
static uint8 FakeBuff_EtherSwt_Port7ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT7MODEREQ];
static uint8 FakeBuff_EtherSwt_Port8ModeReq[CHIPCOM_LENGTH_ETHERSWT_PORT8MODEREQ];

static uint8 FakeBuff_McuInfo[CHIPCOM_LENGTH_ETHERSWT_MCUINFO] = { 0x80, 
0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 
0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60, 
0x59, 0x58, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 
0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 
0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 
0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 
0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 
0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 
0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90, 
0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 
0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 
0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60, 
0x59, 0x58, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50, 
0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 
0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 
0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 
0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 
0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00 };
static uint8 FakeBuff_DoIPComPwr[1]    = { 0x11 };
static uint8 FakeBuff_Utc[6]           = { 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6 };
static uint8 FakeBuff_Odo[4]           = { 0xE1, 0xE2, 0xE3, 0xE4 };
static uint8 FakeBuff_Volt[1]          = { 0xF1 };
static uint8 FakeBuff_Trip[2]          = { 0x15, 0x16 };
static uint8 FakeBuff_Spd[1]           = { 0x25 };
static uint8 FakeBuff_Rdysts[1]        = { 0x35 };
static uint8 FakeBuff_BasicSts[2]      = { 0x21, 0x22 };
static uint8 FakeBuff_SpecialSts[2]    = { 0x31, 0x32 };
static uint8 FakeBuff_TransFlg[2]      = { 0x41, 0x42 };
static uint8 FakeBuff_Ota[2]           = { 0x51, 0x52 };
static uint8 FakeBuff_Pwr[2]           = { 0x61, 0x62 };
static uint8 FakeBuff_Rly[2]           = { 0x71, 0x72 };
static uint8 FakeBuff_Vin[18]          = { 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x90, 0x91, 0x92 };
static uint8 FakeBuff_ComPwr[1]        = { 0xB1 };
static uint8 FakeBuff_Event[2]         = { 0xC1, 0xC2 };

volatile static uint16 rcvLen_CanIfTransmit = 0x00;
volatile static uint8 rcvData_CanIfTransmit[4] = {0xFF, 0xFF, 0xFF, 0xFF};
volatile static uint16 rcvLen_CanIfCancelTransmit = 0x00;
volatile static uint8 rcvData_CanIfCancelTransmit[4] = {0xFF, 0xFF, 0xFF, 0xFF};
volatile static uint16 rcvLen_RidClear = 0x00;
volatile static uint8 rcvData_RidClear[2] = {0xFF, 0xFF};
volatile static uint16 rcvLen_TimeSts = 0x00;
volatile static uint8 rcvData_TimeSts[2] = {0xFF, 0xFF};

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
void ChipComUserFake_Main( void )
{
    static uint8 u1_add = 0;
    static uint8 u1_CycleCnt = 0;
    uint8 i = 0;
    uint32 seq_no = 0;
    uint16 rcvPeriodicLen = 0;

    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT1MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port1ModeReq, &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT2MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port2ModeReq, &seq_no);

    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT5MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port5ModeReq, &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT6MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port6ModeReq, &seq_no);

    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT7MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port7ModeReq, &seq_no);

    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_PORT8MODEREQ, &rcvPeriodicLen, FakeBuff_EtherSwt_Port8ModeReq, &seq_no);


    if( (u1_CycleCnt == 100) && (u1_send_flag == 1)) {
        for(i=0; i < ETHERSWTFAKE_SIZE_MCUINFO; i++) {
            FakeBuff_McuInfo[i] = u1_add++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO, ETHERSWTFAKE_SIZE_MCUINFO, FakeBuff_McuInfo);

        FakeBuff_DoIPComPwr[0] = u1_add++;
        
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, 1, FakeBuff_DoIPComPwr);

#if 0
        FakeBuff_Utc[0] = u1_add++;
        FakeBuff_Utc[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_UTC, CHIPCOM_LENGTH_VIS_UTC, FakeBuff_Utc);

        FakeBuff_Odo[0] = u1_add++;
        FakeBuff_Odo[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_ODO, CHIPCOM_LENGTH_VIS_ODO, FakeBuff_Odo);

        FakeBuff_Volt[0] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_VOLT, CHIPCOM_LENGTH_VIS_VOLT, FakeBuff_Volt);

        FakeBuff_Trip[0] = u1_add++;
        FakeBuff_Trip[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_TRIP, CHIPCOM_LENGTH_VIS_TRIP, FakeBuff_Trip);

        FakeBuff_Spd[0] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_SPD, CHIPCOM_LENGTH_VIS_SPD, FakeBuff_Spd);

        FakeBuff_Rdysts[0] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_RDYSTS, CHIPCOM_LENGTH_VIS_RDYSTS, FakeBuff_Rdysts);



        FakeBuff_BasicSts[0] = u1_add++;
        FakeBuff_BasicSts[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_BASICSTATE, 2, FakeBuff_BasicSts);

        FakeBuff_SpecialSts[0] = u1_add++;
        FakeBuff_SpecialSts[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_SPECIALSTATE, 2, FakeBuff_SpecialSts);

        FakeBuff_TransFlg[0] = u1_add++;
        FakeBuff_TransFlg[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_TRANSFLG, 2, FakeBuff_TransFlg);

        FakeBuff_Ota[0] = u1_add++;
        FakeBuff_Ota[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_OTASWACT, 2, FakeBuff_Ota);

        FakeBuff_Pwr[0] = u1_add++;
        FakeBuff_Pwr[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_PWRERRST, 2, FakeBuff_Pwr);

        FakeBuff_Rly[0] = u1_add++;
        FakeBuff_Rly[1] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_CRLYOF, 2, FakeBuff_Rly);

        for(i=0; i < 18; i++) {
            FakeBuff_Vin[i] = u1_add++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_VIN, 18, FakeBuff_Vin);

        FakeBuff_ComPwr[0] = u1_add++;
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_VIS_COMPWR, 1, FakeBuff_ComPwr);
#endif

        ChipCom_Transmit(CHIPCOM_DATAID_CANTP_TPTXCONF, 2, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;

        ChipCom_Transmit(CHIPCOM_DATAID_CANTP_RXIND, 2, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;

        FakeBuff_Event[1]++;

        u1_CycleCnt = 0;
    } else {
        u1_CycleCnt++;
    }    
}

/* MCU receive */
void CanIfProxy_Transmit(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;

	rcvLen_CanIfTransmit = receive_len;
	for (i = 0; i < rcvLen_CanIfTransmit; i++) {
		rcvData_CanIfTransmit[i] = receive_data[i];
	}

    return;
}

/* MCU receive */
void CanIfProxy_CancelTransmit(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;

	rcvLen_CanIfCancelTransmit = receive_len;
	for (i = 0; i < rcvLen_CanIfCancelTransmit; i++) {
		rcvData_CanIfCancelTransmit[i] = receive_data[i];
	}

    return;
}

/* MCU receive */
void EthSwt_SWIC_Reg_RidClear(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;
    
	rcvLen_RidClear = receive_len;
	for (i = 0; i < rcvLen_RidClear; i++) {
		rcvData_RidClear[i] = receive_data[i];
	}

    return;
}
/* MCU receive */
void Vis_TimeStsReq(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;

	rcvLen_TimeSts = receive_len;
	for (i = 0; i < rcvLen_TimeSts; i++) {
		rcvData_TimeSts[i] = receive_data[i];
	}

    return;
}

#else   /* SAIL ChipCom */
#include "CDD_DebugLog.h"
#if 0
#define CHIPCOM_DEBUGLOG((log_str),(array_addr),(array_length)) \
     DEBUGLOG_LOG_NOTIMESTAMP(DEBUGLOG_DEBUG, (log_str)) \
     for(uint8 i=0; i < (array_length); i++) {DEBUGLOG_LOG_NOTIMESTAMP(DEBUGLOG_DEBUG, "%x ", (array_addr)[i])};
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void CHIPCOM_DEBUGLOG(char* log_str,uint8* array_addr,uint16 const array_length);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
static uint8 u1_send_flag = 0x01;

uint8 FakeBuff_PeriodicCommon[4] = { 0x41, 0x42, 0x43, 0x44 };
uint8 FakeBuff_Event[2]         = { 0xC1, 0xC2 };

static uint8 FakeBuff_EtherSwt_McuInfo     [CHIPCOM_LENGTH_ETHERSWT_MCUINFO     ];
static uint8 FakeBuff_DoIPMgr_DoIPComPwr   [CHIPCOM_LENGTH_DOIPMGR_DOIPCOMPWR   ];
static uint8 FakeBuff_Vis_Utc              [CHIPCOM_LENGTH_VIS_UTC              ];
static uint8 FakeBuff_Vis_Odo              [CHIPCOM_LENGTH_VIS_ODO              ];
static uint8 FakeBuff_Vis_Volt             [CHIPCOM_LENGTH_VIS_VOLT             ];
static uint8 FakeBuff_Vis_Trip             [CHIPCOM_LENGTH_VIS_TRIP             ];
static uint8 FakeBuff_Vis_Spd              [CHIPCOM_LENGTH_VIS_SPD              ];
static uint8 FakeBuff_Vis_RdySts           [CHIPCOM_LENGTH_VIS_RDYSTS           ];
static uint8 FakeBuff_Vis_BasicState       [CHIPCOM_LENGTH_VIS_BASICSTATE       ];
static uint8 FakeBuff_Vis_SpecialState     [CHIPCOM_LENGTH_VIS_SPECIALSTATE     ];
static uint8 FakeBuff_Vis_TransFlg         [CHIPCOM_LENGTH_VIS_TRANSFLG         ];
static uint8 FakeBuff_Vis_OtaSwAct         [CHIPCOM_LENGTH_VIS_OTASWACT         ];
static uint8 FakeBuff_Vis_PwrErrSt         [CHIPCOM_LENGTH_VIS_PWRERRST         ];
static uint8 FakeBuff_Vis_CRlyOf           [CHIPCOM_LENGTH_VIS_CRLYOF           ];
static uint8 FakeBuff_Vis_Vin              [CHIPCOM_LENGTH_VIS_VIN              ];
static uint8 FakeBuff_Vis_ComPwr           [CHIPCOM_LENGTH_VIS_COMPWR           ];

volatile static uint16 rcvLen_TimeSts = 0x00;
volatile static uint8 rcvData_TimeSts[2] = {0xFF, 0xFF};
volatile static uint16 rcvLen_EventCommon = 0x00;
volatile static uint8 rcvData_EventCommon[200] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
void ChipComUserFake_Main( void )
{
    static uint8 u1_add = 0;
    static uint8 u1_add_Send = 0;
    uint8 i = 0;
    static uint32 seq_no = 0;
    uint16 rcvPeriodicLen = 0;

/*    DEBUGLOG_LOG(DEBUGLOG_SAIL_INFO, "PM0(%i): %s\n\r", strlen((char*)buf)-1, &buf);*/
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_ETHERSWT_MCUINFO  , &rcvPeriodicLen, FakeBuff_EtherSwt_McuInfo    , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR, &rcvPeriodicLen, FakeBuff_DoIPMgr_DoIPComPwr  , &seq_no);

#if 0
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_UTC           , &rcvPeriodicLen, FakeBuff_Vis_Utc             , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_ODO           , &rcvPeriodicLen, FakeBuff_Vis_Odo             , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_VOLT          , &rcvPeriodicLen, FakeBuff_Vis_Volt            , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_TRIP          , &rcvPeriodicLen, FakeBuff_Vis_Trip            , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_SPD           , &rcvPeriodicLen, FakeBuff_Vis_Spd             , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_RDYSTS        , &rcvPeriodicLen, FakeBuff_Vis_RdySts          , &seq_no);

    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_BASICSTATE    , &rcvPeriodicLen, FakeBuff_Vis_BasicState      , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_SPECIALSTATE  , &rcvPeriodicLen, FakeBuff_Vis_SpecialState    , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_TRANSFLG      , &rcvPeriodicLen, FakeBuff_Vis_TransFlg        , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_OTASWACT      , &rcvPeriodicLen, FakeBuff_Vis_OtaSwAct        , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_PWRERRST      , &rcvPeriodicLen, FakeBuff_Vis_PwrErrSt        , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_CRLYOF        , &rcvPeriodicLen, FakeBuff_Vis_CRlyOf          , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_VIN           , &rcvPeriodicLen, FakeBuff_Vis_Vin             , &seq_no);
    ChipCom_GetPeriodicRxData(CHIPCOM_PERIODICID_VIS_COMPWR        , &rcvPeriodicLen, FakeBuff_Vis_ComPwr          , &seq_no);
#endif

    if((u1_add % 100) == 0) {
        DEBUGLOG_LOG(DEBUGLOG_SAIL_INFO, "ChipComDebugLog Start \n\r");
        DEBUGLOG_LOG(DEBUGLOG_INFO, "seq_no:%8X ", seq_no);
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_DOIPMGR_DOIPCOMPWR:"), (FakeBuff_DoIPMgr_DoIPComPwr   ),  (1));
#if 0
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_UTC:           "), (FakeBuff_Vis_Utc              ),  (6));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_ODO:           "), (FakeBuff_Vis_Odo              ),  (4));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_VOLT:          "), (FakeBuff_Vis_Volt             ),  (1));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_TRIP:          "), (FakeBuff_Vis_Trip             ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_SPD:           "), (FakeBuff_Vis_Spd              ),  (1));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_RDYSTS:        "), (FakeBuff_Vis_RdySts           ),  (1));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_BASICSTATE:    "), (FakeBuff_Vis_BasicState       ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_SPECIALSTATE:  "), (FakeBuff_Vis_SpecialState     ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_TRANSFLG:      "), (FakeBuff_Vis_TransFlg         ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_OTASWACT:      "), (FakeBuff_Vis_OtaSwAct         ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_PWRERRST:      "), (FakeBuff_Vis_PwrErrSt         ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_CRLYOF:        "), (FakeBuff_Vis_CRlyOf           ),  (2));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_VIN:           "), (FakeBuff_Vis_Vin              ), (18));
        CHIPCOM_DEBUGLOG(("CHIPCOM_PERIODICID_VIS_COMPWR:        "), (FakeBuff_Vis_ComPwr           ),  (1));
#endif
        DEBUGLOG_LOG(DEBUGLOG_SAIL_INFO, "ChipComDebugLog End \n\r");
    }


    switch(u1_send_flag)
    {
    case 1:
        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT1MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);


        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT2MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);


        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT5MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);


        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT6MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);

        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT7MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);


        for(i=0; i < 4; i++) {
            FakeBuff_PeriodicCommon[i] = u1_add_Send++;
        }
        ChipCom_SetPeriodicTxData(CHIPCOM_PERIODICID_ETHERSWT_PORT8MODEREQ, (uint16)4, FakeBuff_PeriodicCommon);

        ChipCom_Transmit(CHIPCOM_DATAID_CANIFPROXY_TRANSMIT, (uint16)2, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;
        ChipCom_Transmit(CHIPCOM_DATAID_CANIFPROXY_CANCELTRANSMIT, (uint16)2, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;
        ChipCom_Transmit(CHIPCOM_DATAID_ETHERSWT_RIDCLEAR, (uint16)0, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;
        ChipCom_Transmit(CHIPCOM_DATAID_VIS_TIME, (uint16)2, FakeBuff_Event);
        FakeBuff_Event[0]++;
        FakeBuff_Event[1]++;

        u1_add++;
        
        break;
    default:
        /* do nothing */
        break;
    }


}
/* SAIL receive */
void CanIfStub_TxConfiramtion(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;

	rcvLen_EventCommon = receive_len;
	for (i = 0; i < rcvLen_EventCommon; i++) {
		rcvData_EventCommon[i] = receive_data[i];
	}
    DEBUGLOG_LOG(DEBUGLOG_SAIL_INFO, "CanIfStub_TxConfiramtion:               %x\n\r", rcvData_EventCommon[0]);

    return;
}

/* SAIL receive */
void CanIfStub_RxIndication(const uint16 receive_len, const uint8* const receive_data)
{
    uint16 i = 0;

	rcvLen_EventCommon = receive_len;
	for (i = 0; i < rcvLen_EventCommon; i++) {
		rcvData_EventCommon[i] = receive_data[i];
	}
    DEBUGLOG_LOG(DEBUGLOG_SAIL_INFO, "CanIfStub_RxIndication:               %x\n\r", rcvData_EventCommon[0]);

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
void CHIPCOM_DEBUGLOG(char* log_str,uint8* array_addr,uint16 const array_length)
{
    uint8 i=0;

    DEBUGLOG_LOG(DEBUGLOG_INFO, (log_str));
    for(i=0; i < array_length; i++) {
        DEBUGLOG_LOG_NOTIMESTAMP(DEBUGLOG_INFO, "%x ", (array_addr)[i]);
    };
    DEBUGLOG_LOG_NOTIMESTAMP(DEBUGLOG_INFO, "\n\r");
}
#endif

/**** End of File ***********************************************************/
