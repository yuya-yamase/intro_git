/* ChipCom_Test_c_v1-0-0                                                    */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_Test/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Os.h"
#include "ChipCom.h"
#include "ChipCom_Cfg.h"
#include "ChipCom_Lcfg.h"

#if CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_TEST_PHASE_COUNTUP (0U)
#define CHIPCOM_TEST_PHASE_CONST (1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void ChipCom_TestTx( void );
void ChipCom_TestRx( void );
void ChipCom_TestSts( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>
/* Tick */
uint8 u1TestTick;
/* Phase */
uint8 u1TestPhase;
/* SPI status */
uint8 u1TestSpiSts;
/* Tx Return */
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST
uint8 u1TextTxRetOBCTXMODENOTIF;
uint8 u1TextTxRetCANWKUPSLP;
uint8 u1TextTxRetDOIPCOMPWR;
uint8 u1TextTxRetREGACCESSFAILURE;
uint8 u1TextTxRetMAC;
uint8 u1TextTxRetETHSWTLINK;
uint8 u1TextTxRetETHSWMIBINFO;
uint8 u1TextTxRetETHSWTSQI;
uint8 u1TextTxRetETHSWTTRAFFICOVR;
uint8 u1TextTxRetETHSWTMCUINFO;
uint8 u1TextTxRetUTC;
uint8 u1TextTxRetODD;
uint8 u1TextTxRetVBAT;
uint8 u1TextTxRetTRIPCNT;
uint8 u1TextTxRetSPD;
uint8 u1TextTxRetRDYSYS;
uint8 u1TextTxRetVPWRBASICSTATE;
uint8 u1TextTxRetVPWRSPCIALSTATE;
uint8 u1TextTxRetVPWRSPCIALSTATETRANSFLG;
uint8 u1TextTxRetOTAREPROG;
uint8 u1TextTxRetVPWRSTATUS;
uint8 u1TextTxRetCENTERRLYOFF;
uint8 u1TextTxRetVIN;
uint8 u1TextTxRetCOMPWRSTATUS;
uint8 u1TextTxRetSAILRESET;
uint8 u1TextTxRetETHSWTRESET;
uint8 u1TextTxRetSAILDATARSTREQ;
#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
uint8 u1TextTxRetMCUSLEEPINFO;
uint8 u1TextTxRetOBCTXMODEREQ;
uint8 u1TextTxRetSAILDATARSTRES;

#endif
/* Rx Return */
uint8 u1TextRxRetSEQCDT1S01;
uint8 u1TextRxRetMCUSLEEPINFO;
uint8 u1TextRxRetSEQCDT1S02;
uint8 u1TextRxRetOBCTXMODEREQ;
uint8 u1TextRxRetSEQCDT1S10;
uint8 u1TextRxRetSAILDATARSTRES;
uint8 u1TextRxRetSEQCDT1M01;
uint8 u1TextRxRetOBCTXMODENOTIF;
uint8 u1TextRxRetSEQCDT1M02;
uint8 u1TextRxRetCANWKUPSLP;
uint8 u1TextRxRetDOIPCOMPWR;
uint8 u1TextRxRetREGACCESSFAILURE;
uint8 u1TextRxRetMAC;
uint8 u1TextRxRetETHSWTLINK;
uint8 u1TextRxRetETHSWMIBINFO;
uint8 u1TextRxRetETHSWTSQI;
uint8 u1TextRxRetETHSWTTRAFFICOVR;
uint8 u1TextRxRetETHSWTMCUINFO;
uint8 u1TextRxRetUTC;
uint8 u1TextRxRetODD;
uint8 u1TextRxRetVBAT;
uint8 u1TextRxRetTRIPCNT;
uint8 u1TextRxRetSPD;
uint8 u1TextRxRetRDYSYS;
uint8 u1TextRxRetVPWRBASICSTATE;
uint8 u1TextRxRetVPWRSPCIALSTATE;
uint8 u1TextRxRetVPWRSPCIALSTATETRANSFLG;
uint8 u1TextRxRetOTAREPROG;
uint8 u1TextRxRetVPWRSTATUS;
uint8 u1TextRxRetCENTERRLYOFF;
uint8 u1TextRxRetVIN;
uint8 u1TextRxRetCOMPWRSTATUS;
uint8 u1TextRxRetSAILRESET;
uint8 u1TextRxRetSEQCDT1M03;
uint8 u1TextRxRetETHSWTRESET;
uint8 u1TextRxRetSEQCDT1M10;
uint8 u1TextRxRetSAILDATARSTREQ;

/* Data Status */
uint8 u1TestDatStsSEQCDT1S01;
uint8 u1TestDatStsMCUSLEEPINFO;
uint8 u1TestDatStsSEQCDT1S02;
uint8 u1TestDatStsOBCTXMODEREQ;
uint8 u1TestDatStsSEQCDT1S10;
uint8 u1TestDatStsSAILDATARSTRES;
uint8 u1TestDatStsSEQCDT1M01;
uint8 u1TestDatStsOBCTXMODENOTIF;
uint8 u1TestDatStsSEQCDT1M02;
uint8 u1TestDatStsCANWKUPSLP;
uint8 u1TestDatStsDOIPCOMPWR;
uint8 u1TestDatStsREGACCESSFAILURE;
uint8 u1TestDatStsMAC;
uint8 u1TestDatStsETHSWTLINK;
uint8 u1TestDatStsETHSWMIBINFO;
uint8 u1TestDatStsETHSWTSQI;
uint8 u1TestDatStsETHSWTTRAFFICOVR;
uint8 u1TestDatStsETHSWTMCUINFO;
uint8 u1TestDatStsUTC;
uint8 u1TestDatStsODD;
uint8 u1TestDatStsVBAT;
uint8 u1TestDatStsTRIPCNT;
uint8 u1TestDatStsSPD;
uint8 u1TestDatStsRDYSYS;
uint8 u1TestDatStsVPWRBASICSTATE;
uint8 u1TestDatStsVPWRSPCIALSTATE;
uint8 u1TestDatStsVPWRSPCIALSTATETRANSFLG;
uint8 u1TestDatStsOTAREPROG;
uint8 u1TestDatStsVPWRSTATUS;
uint8 u1TestDatStsCENTERRLYOFF;
uint8 u1TestDatStsVIN;
uint8 u1TestDatStsCOMPWRSTATUS;
uint8 u1TestDatStsSAILRESET;
uint8 u1TestDatStsSEQCDT1M03;
uint8 u1TestDatStsETHSWTRESET;
uint8 u1TestDatStsSEQCDT1M10;
uint8 u1TestDatStsSAILDATARSTREQ;

#define CHIPCOM_STOP_SEC_VAR_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_VAR_POWER_ON_CLEARED_32
#include <ChipCom_MemMap.h>

#define CHIPCOM_START_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>
/* Tx Data */
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST
uint8 u1TestTxDatOBCTXMODENOTIF[1] = { (uint8)0x00 };
uint8 u1TestTxDatCANWKUPSLP[1] = { (uint8)0x00 };
uint8 u1TestTxDatDOIPCOMPWR[1] = { (uint8)0x00 };
uint8 u1TestTxDatREGACCESSFAILURE[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatMAC[6] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatETHSWTLINK[16] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatETHSWMIBINFO[244] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatETHSWTSQI[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatETHSWTTRAFFICOVR[24] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatETHSWTMCUINFO[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatUTC[6] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatODD[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatVBAT[1] = { (uint8)0x00 };
uint8 u1TestTxDatTRIPCNT[3] = { (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatSPD[1] = { (uint8)0x00 };
uint8 u1TestTxDatRDYSYS[1] = { (uint8)0x00 };
uint8 u1TestTxDatVPWRBASICSTATE[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatVPWRSPCIALSTATE[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatVPWRSPCIALSTATETRANSFLG[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatOTAREPROG[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatVPWRSTATUS[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatCENTERRLYOFF[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatVIN[18] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatCOMPWRSTATUS[1] = { (uint8)0x00 };
uint8 u1TestTxDatSAILRESET[1] = { (uint8)0x00 };
uint8 u1TestTxDatETHSWTRESET[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestTxDatSAILDATARSTREQ[1] = { (uint8)0x00 };

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
uint8 u1TestTxDatMCUSLEEPINFO[1] = { (uint8)0x00 };
uint8 u1TestTxDatOBCTXMODEREQ[1] = { (uint8)0x00 };
uint8 u1TestTxDatSAILDATARSTRES[1] = { (uint8)0x00 };

#endif

/* Data Max */
uint8 u1TestDatMaxMCUSLEEPINFO[1] = { (uint8)0xFF };
uint8 u1TestDatMaxOBCTXMODEREQ[1] = { (uint8)0xFF };
uint8 u1TestDatMaxSAILDATARSTRES[1] = { (uint8)0xFF };
uint8 u1TestDatMaxOBCTXMODENOTIF[1] = { (uint8)0xFF };
uint8 u1TestDatMaxCANWKUPSLP[1] = { (uint8)0xFF };
uint8 u1TestDatMaxDOIPCOMPWR[1] = { (uint8)0xFF };
uint8 u1TestDatMaxREGACCESSFAILURE[8] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxMAC[6] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxETHSWTLINK[16] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxETHSWMIBINFO[244] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxETHSWTSQI[8] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxETHSWTTRAFFICOVR[24] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxETHSWTMCUINFO[8] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxUTC[6] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxODD[4] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxVBAT[1] = { (uint8)0xFF };
uint8 u1TestDatMaxTRIPCNT[3] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxSPD[1] = { (uint8)0xFF };
uint8 u1TestDatMaxRDYSYS[1] = { (uint8)0xFF };
uint8 u1TestDatMaxVPWRBASICSTATE[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxVPWRSPCIALSTATE[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxVPWRSPCIALSTATETRANSFLG[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxOTAREPROG[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxVPWRSTATUS[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxCENTERRLYOFF[2] = { (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxVIN[18] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxCOMPWRSTATUS[1] = { (uint8)0xFF };
uint8 u1TestDatMaxSAILRESET[1] = { (uint8)0xFF };
uint8 u1TestDatMaxETHSWTRESET[4] = { (uint8)0xFF, (uint8)0xFF, (uint8)0xFF, (uint8)0xFF };
uint8 u1TestDatMaxSAILDATARSTREQ[1] = { (uint8)0xFF };

/* Rx Data */
uint8 u1TestRxDatSEQCDT1S01[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatMCUSLEEPINFO[1] = { (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1S02[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatOBCTXMODEREQ[1] = { (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1S10[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatSAILDATARSTRES[1] = { (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1M01[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatOBCTXMODENOTIF[1] = { (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1M02[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatCANWKUPSLP[1] = { (uint8)0x00 };
uint8 u1TestRxDatDOIPCOMPWR[1] = { (uint8)0x00 };
uint8 u1TestRxDatREGACCESSFAILURE[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatMAC[6] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWTLINK[16] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWMIBINFO[244] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWTSQI[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWTTRAFFICOVR[24] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWTMCUINFO[8] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatUTC[6] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatODD[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatVBAT[1] = { (uint8)0x00 };
uint8 u1TestRxDatTRIPCNT[3] = { (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatSPD[1] = { (uint8)0x00 };
uint8 u1TestRxDatRDYSYS[1] = { (uint8)0x00 };
uint8 u1TestRxDatVPWRBASICSTATE[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatVPWRSPCIALSTATE[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatVPWRSPCIALSTATETRANSFLG[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatOTAREPROG[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatVPWRSTATUS[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatCENTERRLYOFF[2] = { (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatVIN[18] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatCOMPWRSTATUS[1] = { (uint8)0x00 };
uint8 u1TestRxDatSAILRESET[1] = { (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1M03[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatETHSWTRESET[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatSEQCDT1M10[4] = { (uint8)0x00, (uint8)0x00, (uint8)0x00, (uint8)0x00 };
uint8 u1TestRxDatSAILDATARSTREQ[1] = { (uint8)0x00 };

#define CHIPCOM_STOP_SEC_VAR_INIT_32
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CONST
#include <ChipCom_MemMap.h>
#define CHIPCOM_STOP_SEC_CONST
#include <ChipCom_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Functions                                                                */
/*--------------------------------------------------------------------------*/
#define CHIPCOM_START_SEC_CODE
#include <ChipCom_MemMap.h>
/****************************************************************************/
/* Scheduled Functions                                                      */
/****************************************************************************/
/* Main */
void ChipCom_MainFunctionTest( void )
{
	uint8 t_u1XspiErrInfo;

	ChipCom_TestRx();
	ChipCom_TestSts();
	ChipCom_TestTx();

	/* Count-up tick */
	u1TestTick++;

	/* Transit Phase */
	if ( u1TestTick == (uint8)0U )
	{
		if ( u1TestPhase == CHIPCOM_TEST_PHASE_COUNTUP )
		{
			u1TestPhase = CHIPCOM_TEST_PHASE_CONST;
		}
		else
		{
			u1TestPhase = CHIPCOM_TEST_PHASE_COUNTUP;
		}
	}

	/* Log */
	if ( (u1TestTick & (uint8)0x07U) == (uint8)0U )
	{
		t_u1XspiErrInfo = xspi_GetErrInfo( ChipCom_cu1XspiCh );

		CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom: Tick=[%u], SpiInfo=[%u], MsgSts[0]=[%u], Msg[0]=[%u], MsgSts[6]=[%u], Msg[6]=[%u]\r\n",
				ChipCom_u2SrvTick, t_u1XspiErrInfo,
				ChipCom_u1MsgStatus[0U], ChipCom_u1MsgBuff[3U],
				ChipCom_u1MsgStatus[6U], ChipCom_u1MsgBuff[18U]
				);

//		CHIPCOM_LOG_MSG( DEBUGLOG_INFO,"ChipCom: Tick=[%u], SpiInfo=[%u], MsgSts0=[%u], Msg0=[0x%02X%02X%02X%02X], MsgSts6=[%u], Msg6=[0x%02X%02X%02X%02X], TxBuf=[0x%08X %08X], RxBuf=[0x%08X %08X], TxVlaNum=[0x%02X%02X], TxCanId=[0x%02X%02X%02X%02X], TxCanLen=[0x%02X], RxVlaNum=[0x%02X%02X], RxCanId=[0x%02X%02X%02X%02X], RxCanLen=[0x%02X]\r\n",
//			ChipCom_u2SrvTick, t_u1XspiErrInfo,
//			ChipCom_u1MsgStatus[0U], ChipCom_u1MsgBuff[0U],ChipCom_u1MsgBuff[1U],ChipCom_u1MsgBuff[2U],ChipCom_u1MsgBuff[3U],
//			ChipCom_u1MsgStatus[6U], ChipCom_u1MsgBuff[15U],ChipCom_u1MsgBuff[16U],ChipCom_u1MsgBuff[17U],ChipCom_u1MsgBuff[18U],
//			ChipCom_u4TxBuff[2U], ChipCom_u4TxBuff[3U],
//			ChipCom_u4RxBuff[2U], ChipCom_u4RxBuff[3U],
//			ChipCom_pu1TxBuffVla[0U], ChipCom_pu1TxBuffVla[1U],
//			ChipCom_pu1TxBuffVla[3U], ChipCom_pu1TxBuffVla[4U], ChipCom_pu1TxBuffVla[5U], ChipCom_pu1TxBuffVla[6U],
//			ChipCom_pu1TxBuffVla[7U],
//			ChipCom_pu1RxBuffVla[0U], ChipCom_pu1RxBuffVla[1U],
//			ChipCom_pu1RxBuffVla[3U], ChipCom_pu1RxBuffVla[4U], ChipCom_pu1RxBuffVla[5U], ChipCom_pu1RxBuffVla[6U],
//			ChipCom_pu1RxBuffVla[7U] );

	}

	return;
}

/****************************************************************************/
/* Service API                                                              */
/****************************************************************************/
/* ChipCom_SendSignal dummy */
uint8 ChipCom_SendSignalDummy( Com_SignalIdType t_u2SignalId, const void* t_pvdSignalDataPtr )
{
	return (uint8)E_OK;
}

/****************************************************************************/
/* Callback Functions and Notifications                                     */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/*---------------------------------------------------------------------------*/
void ChipCom_TestTx( void )
{

#if CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR
	uint32 t_u4CoreId;
	t_u4CoreId = GetCoreID();
#endif


	if ( u1TestPhase == CHIPCOM_TEST_PHASE_COUNTUP )
	{

#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

//u1TestTxDatOBCTXMODENOTIF[0U] = u1TestTick + (uint8)7U;
u1TestTxDatCANWKUPSLP[0U] = u1TestTick + (uint8)9U;
u1TestTxDatDOIPCOMPWR[0U] = u1TestTick + (uint8)10U;
u1TestTxDatREGACCESSFAILURE[0U] = u1TestTick + (uint8)11U;
u1TestTxDatMAC[0U] = u1TestTick + (uint8)12U;
u1TestTxDatETHSWTLINK[0U] = u1TestTick + (uint8)13U;
u1TestTxDatETHSWMIBINFO[0U] = u1TestTick + (uint8)14U;
u1TestTxDatETHSWTSQI[0U] = u1TestTick + (uint8)15U;
u1TestTxDatETHSWTTRAFFICOVR[0U] = u1TestTick + (uint8)16U;
u1TestTxDatETHSWTMCUINFO[0U] = u1TestTick + (uint8)17U;
u1TestTxDatUTC[0U] = u1TestTick + (uint8)18U;
u1TestTxDatODD[0U] = u1TestTick + (uint8)19U;
u1TestTxDatVBAT[0U] = u1TestTick + (uint8)20U;
u1TestTxDatTRIPCNT[0U] = u1TestTick + (uint8)21U;
u1TestTxDatSPD[0U] = u1TestTick + (uint8)22U;
u1TestTxDatRDYSYS[0U] = u1TestTick + (uint8)23U;
u1TestTxDatVPWRBASICSTATE[0U] = u1TestTick + (uint8)24U;
u1TestTxDatVPWRSPCIALSTATE[0U] = u1TestTick + (uint8)25U;
u1TestTxDatVPWRSPCIALSTATETRANSFLG[0U] = u1TestTick + (uint8)26U;
u1TestTxDatOTAREPROG[0U] = u1TestTick + (uint8)27U;
u1TestTxDatVPWRSTATUS[0U] = u1TestTick + (uint8)28U;
u1TestTxDatCENTERRLYOFF[0U] = u1TestTick + (uint8)29U;
u1TestTxDatVIN[0U] = u1TestTick + (uint8)30U;
u1TestTxDatCOMPWRSTATUS[0U] = u1TestTick + (uint8)31U;
u1TestTxDatSAILRESET[0U] = u1TestTick + (uint8)32U;
u1TestTxDatETHSWTRESET[0U] = u1TestTick + (uint8)34U;
u1TestTxDatSAILDATARSTREQ[0U] = u1TestTick + (uint8)36U;

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */

	if ( t_u4CoreId == (uint32)1U )
	{
u1TestTxDatMCUSLEEPINFO[0U] = u1TestTick + (uint8)1U;
u1TestTxDatSAILDATARSTRES[0U] = u1TestTick + (uint8)5U;
	}
	else if ( t_u4CoreId == (uint32)2U )
	{
//u1TestTxDatOBCTXMODEREQ[0U] = u1TestTick + (uint8)3U;
	}
	else
	{
		/* No processing */
	}

#endif

	}
	else /* u1TestPhase == CHIPCOM_TEST_PHASE_CONST */
	{


#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

//u1TestTxDatOBCTXMODENOTIF[0U] = (uint8)7U;
u1TestTxDatCANWKUPSLP[0U] = (uint8)9U;
u1TestTxDatDOIPCOMPWR[0U] = (uint8)10U;
u1TestTxDatREGACCESSFAILURE[0U] = (uint8)11U;
u1TestTxDatMAC[0U] = (uint8)12U;
u1TestTxDatETHSWTLINK[0U] = (uint8)13U;
u1TestTxDatETHSWMIBINFO[0U] = (uint8)14U;
u1TestTxDatETHSWTSQI[0U] = (uint8)15U;
u1TestTxDatETHSWTTRAFFICOVR[0U] = (uint8)16U;
u1TestTxDatETHSWTMCUINFO[0U] = (uint8)17U;
u1TestTxDatUTC[0U] = (uint8)18U;
u1TestTxDatODD[0U] = (uint8)19U;
u1TestTxDatVBAT[0U] = (uint8)20U;
u1TestTxDatTRIPCNT[0U] = (uint8)21U;
u1TestTxDatSPD[0U] = (uint8)22U;
u1TestTxDatRDYSYS[0U] = (uint8)23U;
u1TestTxDatVPWRBASICSTATE[0U] = (uint8)24U;
u1TestTxDatVPWRSPCIALSTATE[0U] = (uint8)25U;
u1TestTxDatVPWRSPCIALSTATETRANSFLG[0U] = (uint8)26U;
u1TestTxDatOTAREPROG[0U] = (uint8)27U;
u1TestTxDatVPWRSTATUS[0U] = (uint8)28U;
u1TestTxDatCENTERRLYOFF[0U] = (uint8)29U;
u1TestTxDatVIN[0U] = (uint8)30U;
u1TestTxDatCOMPWRSTATUS[0U] = (uint8)31U;
u1TestTxDatSAILRESET[0U] = (uint8)32U;
u1TestTxDatETHSWTRESET[0U] = (uint8)34U;
u1TestTxDatSAILDATARSTREQ[0U] = (uint8)36U;

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */

	if ( t_u4CoreId == (uint32)1U )
	{
u1TestTxDatMCUSLEEPINFO[0U] = (uint8)1U;
u1TestTxDatSAILDATARSTRES[0U] = (uint8)5U;
	}
	else if ( t_u4CoreId == (uint32)2U )
	{
//u1TestTxDatOBCTXMODEREQ[0U] = (uint8)3U;
	}
	else
	{
		/* No processing */
	}

#endif

	}

	if ( ( u1TestPhase == CHIPCOM_TEST_PHASE_COUNTUP )
			|| ( u1TestTick < (uint8)0x80U ) )
	{

#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

//u1TextTxRetOBCTXMODENOTIF = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF, &u1TestTxDatOBCTXMODENOTIF[0U] );
u1TextTxRetCANWKUPSLP = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1TestTxDatCANWKUPSLP[0U] );
u1TextTxRetDOIPCOMPWR = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_DOIPCOMPWR, &u1TestTxDatDOIPCOMPWR[0U] );
u1TextTxRetREGACCESSFAILURE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_REGACCESSFAILURE, &u1TestTxDatREGACCESSFAILURE[0U] );
u1TextTxRetMAC = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_MAC, &u1TestTxDatMAC[0U] );
u1TextTxRetETHSWTLINK = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTLINK, &u1TestTxDatETHSWTLINK[0U] );
u1TextTxRetETHSWMIBINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWMIBINFO, &u1TestTxDatETHSWMIBINFO[0U] );
u1TextTxRetETHSWTSQI = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTSQI, &u1TestTxDatETHSWTSQI[0U] );
u1TextTxRetETHSWTTRAFFICOVR = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTTRAFFICOVR, &u1TestTxDatETHSWTTRAFFICOVR[0U] );
u1TextTxRetETHSWTMCUINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTMCUINFO, &u1TestTxDatETHSWTMCUINFO[0U] );
u1TextTxRetUTC = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_UTC, &u1TestTxDatUTC[0U] );
u1TextTxRetODD = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_ODD, &u1TestTxDatODD[0U] );
u1TextTxRetVBAT = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VBAT, &u1TestTxDatVBAT[0U] );
u1TextTxRetTRIPCNT = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_TRIPCNT, &u1TestTxDatTRIPCNT[0U] );
u1TextTxRetSPD = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SPD, &u1TestTxDatSPD[0U] );
u1TextTxRetRDYSYS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_RDYSYS, &u1TestTxDatRDYSYS[0U] );
u1TextTxRetVPWRBASICSTATE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRBASICSTATE, &u1TestTxDatVPWRBASICSTATE[0U] );
u1TextTxRetVPWRSPCIALSTATE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATE, &u1TestTxDatVPWRSPCIALSTATE[0U] );
u1TextTxRetVPWRSPCIALSTATETRANSFLG = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATETRANSFLG, &u1TestTxDatVPWRSPCIALSTATETRANSFLG[0U] );
u1TextTxRetOTAREPROG = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_OTAREPROG, &u1TestTxDatOTAREPROG[0U] );
u1TextTxRetVPWRSTATUS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSTATUS, &u1TestTxDatVPWRSTATUS[0U] );
u1TextTxRetCENTERRLYOFF = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_CENTERRLYOFF, &u1TestTxDatCENTERRLYOFF[0U] );
u1TextTxRetVIN = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VIN, &u1TestTxDatVIN[0U] );
u1TextTxRetCOMPWRSTATUS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_COMPWRSTATUS, &u1TestTxDatCOMPWRSTATUS[0U] );
u1TextTxRetSAILRESET = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SAILRESET, &u1TestTxDatSAILRESET[0U] );
u1TextTxRetETHSWTRESET = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M03_ETHSWTRESET, &u1TestTxDatETHSWTRESET[0U] );
u1TextTxRetSAILDATARSTREQ = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CEN1M10_SAILDATARSTREQ, &u1TestTxDatSAILDATARSTREQ[0U] );


#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */

		if ( t_u4CoreId == (uint32)1U )
		{
u1TextTxRetMCUSLEEPINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CSS1S01_MCUSLEEPINFO, &u1TestTxDatMCUSLEEPINFO[0U] );
u1TextTxRetSAILDATARSTRES = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CEN1S10_SAILDATARSTRES, &u1TestTxDatSAILDATARSTRES[0U] );
		}
		else if ( t_u4CoreId == (uint32)2U )
		{
//u1TextTxRetOBCTXMODEREQ = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ, &u1TestTxDatOBCTXMODEREQ[0U] );
		}
		else
		{
			/* No processing */
		}

#endif
	}
	else
	{
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

//u1TextTxRetOBCTXMODENOTIF = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF, &u1TestDatMaxOBCTXMODENOTIF[0U] );
u1TextTxRetCANWKUPSLP = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1TestDatMaxCANWKUPSLP[0U] );
u1TextTxRetDOIPCOMPWR = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_DOIPCOMPWR, &u1TestDatMaxDOIPCOMPWR[0U] );
u1TextTxRetREGACCESSFAILURE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_REGACCESSFAILURE, &u1TestDatMaxREGACCESSFAILURE[0U] );
u1TextTxRetMAC = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_MAC, &u1TestDatMaxMAC[0U] );
u1TextTxRetETHSWTLINK = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTLINK, &u1TestDatMaxETHSWTLINK[0U] );
u1TextTxRetETHSWMIBINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWMIBINFO, &u1TestDatMaxETHSWMIBINFO[0U] );
u1TextTxRetETHSWTSQI = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTSQI, &u1TestDatMaxETHSWTSQI[0U] );
u1TextTxRetETHSWTTRAFFICOVR = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTTRAFFICOVR, &u1TestDatMaxETHSWTTRAFFICOVR[0U] );
u1TextTxRetETHSWTMCUINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTMCUINFO, &u1TestDatMaxETHSWTMCUINFO[0U] );
u1TextTxRetUTC = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_UTC, &u1TestDatMaxUTC[0U] );
u1TextTxRetODD = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_ODD, &u1TestDatMaxODD[0U] );
u1TextTxRetVBAT = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VBAT, &u1TestDatMaxVBAT[0U] );
u1TextTxRetTRIPCNT = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_TRIPCNT, &u1TestDatMaxTRIPCNT[0U] );
u1TextTxRetSPD = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SPD, &u1TestDatMaxSPD[0U] );
u1TextTxRetRDYSYS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_RDYSYS, &u1TestDatMaxRDYSYS[0U] );
u1TextTxRetVPWRBASICSTATE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRBASICSTATE, &u1TestDatMaxVPWRBASICSTATE[0U] );
u1TextTxRetVPWRSPCIALSTATE = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATE, &u1TestDatMaxVPWRSPCIALSTATE[0U] );
u1TextTxRetVPWRSPCIALSTATETRANSFLG = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATETRANSFLG, &u1TestDatMaxVPWRSPCIALSTATETRANSFLG[0U] );
u1TextTxRetOTAREPROG = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_OTAREPROG, &u1TestDatMaxOTAREPROG[0U] );
u1TextTxRetVPWRSTATUS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSTATUS, &u1TestDatMaxVPWRSTATUS[0U] );
u1TextTxRetCENTERRLYOFF = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_CENTERRLYOFF, &u1TestDatMaxCENTERRLYOFF[0U] );
u1TextTxRetVIN = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VIN, &u1TestDatMaxVIN[0U] );
u1TextTxRetCOMPWRSTATUS = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_COMPWRSTATUS, &u1TestDatMaxCOMPWRSTATUS[0U] );
u1TextTxRetSAILRESET = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SAILRESET, &u1TestDatMaxSAILRESET[0U] );
u1TextTxRetETHSWTRESET = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_ETH1M03_ETHSWTRESET, &u1TestDatMaxETHSWTRESET[0U] );
u1TextTxRetSAILDATARSTREQ = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CEN1M10_SAILDATARSTREQ, &u1TestDatMaxSAILDATARSTREQ[0U] );

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */

		if ( t_u4CoreId == (uint32)1U )
		{
u1TextTxRetMCUSLEEPINFO = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CSS1S01_MCUSLEEPINFO, &u1TestDatMaxMCUSLEEPINFO[0U] );
u1TextTxRetSAILDATARSTRES = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_CEN1S10_SAILDATARSTRES, &u1TestDatMaxSAILDATARSTRES[0U] );

		}
		else if ( t_u4CoreId == (uint32)2U )
		{
//u1TextTxRetOBCTXMODEREQ = ChipCom_SendSignal( SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ, &u1TestDatMaxOBCTXMODEREQ[0U] );
		}
		else
		{
			/* No processing */
		}

#endif
	}

	return;
}
/*---------------------------------------------------------------------------*/
void ChipCom_TestRx( void )
{
#if CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR
	uint32 t_u4CoreId;
	t_u4CoreId = GetCoreID();
#endif

#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

u1TextRxRetSEQCDT1S01 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1S01_SEQCDT1S01, &u1TestRxDatSEQCDT1S01[0U] );
u1TextRxRetMCUSLEEPINFO = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CSS1S01_MCUSLEEPINFO, &u1TestRxDatMCUSLEEPINFO[0U] );
u1TextRxRetSEQCDT1S02 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1S02_SEQCDT1S02, &u1TestRxDatSEQCDT1S02[0U] );
u1TextRxRetOBCTXMODEREQ = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ, &u1TestRxDatOBCTXMODEREQ[0U] );
u1TextRxRetSEQCDT1S10 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1S10_SEQCDT1S10, &u1TestRxDatSEQCDT1S10[0U] );
u1TextRxRetSAILDATARSTRES = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CEN1S10_SAILDATARSTRES, &u1TestRxDatSAILDATARSTRES[0U] );

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
		if ( t_u4CoreId == (uint32)1U )
		{

u1TextRxRetSEQCDT1M02 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1M02_SEQCDT1M02, &u1TestRxDatSEQCDT1M02[0U] );
u1TextRxRetCANWKUPSLP = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1TestRxDatCANWKUPSLP[0U] );
u1TextRxRetDOIPCOMPWR = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_DOIPCOMPWR, &u1TestRxDatDOIPCOMPWR[0U] );
u1TextRxRetREGACCESSFAILURE = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_REGACCESSFAILURE, &u1TestRxDatREGACCESSFAILURE[0U] );
u1TextRxRetMAC = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_MAC, &u1TestRxDatMAC[0U] );
u1TextRxRetETHSWTLINK = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTLINK, &u1TestRxDatETHSWTLINK[0U] );
u1TextRxRetETHSWMIBINFO = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWMIBINFO, &u1TestRxDatETHSWMIBINFO[0U] );
u1TextRxRetETHSWTSQI = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTSQI, &u1TestRxDatETHSWTSQI[0U] );
u1TextRxRetETHSWTTRAFFICOVR = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTTRAFFICOVR, &u1TestRxDatETHSWTTRAFFICOVR[0U] );
u1TextRxRetETHSWTMCUINFO = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTMCUINFO, &u1TestRxDatETHSWTMCUINFO[0U] );
u1TextRxRetUTC = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_UTC, &u1TestRxDatUTC[0U] );
u1TextRxRetODD = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_ODD, &u1TestRxDatODD[0U] );
u1TextRxRetVBAT = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VBAT, &u1TestRxDatVBAT[0U] );
u1TextRxRetTRIPCNT = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_TRIPCNT, &u1TestRxDatTRIPCNT[0U] );
u1TextRxRetSPD = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SPD, &u1TestRxDatSPD[0U] );
u1TextRxRetRDYSYS = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_RDYSYS, &u1TestRxDatRDYSYS[0U] );
u1TextRxRetVPWRBASICSTATE = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRBASICSTATE, &u1TestRxDatVPWRBASICSTATE[0U] );
u1TextRxRetVPWRSPCIALSTATE = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATE, &u1TestRxDatVPWRSPCIALSTATE[0U] );
u1TextRxRetVPWRSPCIALSTATETRANSFLG = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATETRANSFLG, &u1TestRxDatVPWRSPCIALSTATETRANSFLG[0U] );
u1TextRxRetOTAREPROG = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_OTAREPROG, &u1TestRxDatOTAREPROG[0U] );
u1TextRxRetVPWRSTATUS = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSTATUS, &u1TestRxDatVPWRSTATUS[0U] );
u1TextRxRetCENTERRLYOFF = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_CENTERRLYOFF, &u1TestRxDatCENTERRLYOFF[0U] );
u1TextRxRetVIN = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_VIN, &u1TestRxDatVIN[0U] );
u1TextRxRetCOMPWRSTATUS = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_COMPWRSTATUS, &u1TestRxDatCOMPWRSTATUS[0U] );
u1TextRxRetSAILRESET = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_VIS1M01_SAILRESET, &u1TestRxDatSAILRESET[0U] );
u1TextRxRetSEQCDT1M03 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1M03_SEQCDT1M03, &u1TestRxDatSEQCDT1M03[0U] );
u1TextRxRetETHSWTRESET = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_ETH1M03_ETHSWTRESET, &u1TestRxDatETHSWTRESET[0U] );
u1TextRxRetSEQCDT1M10 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1M10_SEQCDT1M10, &u1TestRxDatSEQCDT1M10[0U] );
u1TextRxRetSAILDATARSTREQ = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CEN1M10_SAILDATARSTREQ, &u1TestRxDatSAILDATARSTREQ[0U] );

		}
		else if ( t_u4CoreId == (uint32)2U )
		{

u1TextRxRetSEQCDT1M01 = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_CDT1M01_SEQCDT1M01, &u1TestRxDatSEQCDT1M01[0U] );
u1TextRxRetOBCTXMODENOTIF = ChipCom_ReceiveSignal( SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF, &u1TestRxDatOBCTXMODENOTIF[0U] );

		}
		else
		{
			/* No processing */
		}
#endif

	return;
}
/*---------------------------------------------------------------------------*/
void ChipCom_TestSts( void )
{
#if CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR
	uint32 t_u4CoreId;
	t_u4CoreId = GetCoreID();
#endif

	/* Spi Status */
	u1TestSpiSts = ChipCom_GetErrInfo();

	/* Data Status */
#if CHIPCOM_BSW == CHIPCOM_BSW_AUBIST

u1TestDatStsSEQCDT1S01 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1S01_SEQCDT1S01 );
u1TestDatStsMCUSLEEPINFO = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CSS1S01_MCUSLEEPINFO );
u1TestDatStsSEQCDT1S02 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1S02_SEQCDT1S02 );
u1TestDatStsOBCTXMODEREQ = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_OBC1S01_OBCTXMODEREQ );
u1TestDatStsSEQCDT1S10 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1S10_SEQCDT1S10 );
u1TestDatStsSAILDATARSTRES = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CEN1S10_SAILDATARSTRES );

#else /* CHIPCOM_BSW == CHIPCOM_BSW_MICROSAR */
		if ( t_u4CoreId == (uint32)1U )
		{

u1TestDatStsSEQCDT1M02 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1M02_SEQCDT1M02 );
u1TestDatStsCANWKUPSLP = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP );
u1TestDatStsDOIPCOMPWR = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_DOIPCOMPWR );
u1TestDatStsREGACCESSFAILURE = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_REGACCESSFAILURE );
u1TestDatStsMAC = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_MAC );
u1TestDatStsETHSWTLINK = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTLINK );
u1TestDatStsETHSWMIBINFO = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWMIBINFO );
u1TestDatStsETHSWTSQI = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTSQI );
u1TestDatStsETHSWTTRAFFICOVR = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTTRAFFICOVR );
u1TestDatStsETHSWTMCUINFO = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M01_ETHSWTMCUINFO );
u1TestDatStsUTC = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_UTC );
u1TestDatStsODD = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_ODD );
u1TestDatStsVBAT = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VBAT );
u1TestDatStsTRIPCNT = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_TRIPCNT );
u1TestDatStsSPD = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_SPD );
u1TestDatStsRDYSYS = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_RDYSYS );
u1TestDatStsVPWRBASICSTATE = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRBASICSTATE );
u1TestDatStsVPWRSPCIALSTATE = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATE );
u1TestDatStsVPWRSPCIALSTATETRANSFLG = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSPCIALSTATETRANSFLG );
u1TestDatStsOTAREPROG = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_OTAREPROG );
u1TestDatStsVPWRSTATUS = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VPWRSTATUS );
u1TestDatStsCENTERRLYOFF = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_CENTERRLYOFF );
u1TestDatStsVIN = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_VIN );
u1TestDatStsCOMPWRSTATUS = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_COMPWRSTATUS );
u1TestDatStsSAILRESET = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_VIS1M01_SAILRESET );
u1TestDatStsSEQCDT1M03 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1M03_SEQCDT1M03 );
u1TestDatStsETHSWTRESET = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_ETH1M03_ETHSWTRESET );
u1TestDatStsSEQCDT1M10 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1M10_SEQCDT1M10 );
u1TestDatStsSAILDATARSTREQ = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CEN1M10_SAILDATARSTREQ );

		}
		else if ( t_u4CoreId == (uint32)2U )
		{

u1TestDatStsSEQCDT1M01 = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_CDT1M01_SEQCDT1M01 );
u1TestDatStsOBCTXMODENOTIF = ChipCom_GetSignalStatus( SIGNAL_CHIPCOM_BUS_OBC1M01_OBCTXMODENOTIF );

		}
		else
		{
			/* No processing */
		}
#endif

	return;
}

#define CHIPCOM_STOP_SEC_CODE
#include <ChipCom_MemMap.h>

#endif /* CHIPCOM_TEST_MD == CHIPCOM_TEST_MD_DRV */

/**** End of File ***********************************************************/
