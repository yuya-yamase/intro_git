/* ADCDIAG-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*      ADC DIAG Driver : Low Driver layer for RH850U2A/U2B                                     */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
#ifndef ADCDIAG_PIL_H
#define ADCDIAG_PIL_H

/*==============================================================================================*/
/*  include files                                                                               */
/*==============================================================================================*/

/*==============================================================================================*/
/*  defines / data types / structs / unions / macros                                            */
/*==============================================================================================*/
typedef enum {
    ADCDIAG_PIL_OVERLAPERROR,
    ADCDIAG_PIL_PARITYPERROR,
    ADCDIAG_PIL_IDERROR
} AdcDiag_Pil_ErrorType;

typedef struct {
    const uint8* pu1PhysicalChannels;
    uint32 u4TimeoutValueA;
    uint32 u4TimeoutValueB;
    uint8 u1HWUnit;
    uint8 u1ScanGroup;
    uint8 u1StartPointer;
    uint8 u1StopPointer;
    uint8 u1PhysicalChannelsNo;
    uint8 u1VoltageLevelAtStart;
    uint8 u1VoltageLevelAfterChange;
} AdcDiag_Pil_THData;

#define u1ADCDIAG_PIL_NOT_APPLICABLE                            ((uint8)0U)
#define u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE1         ((uint8)1U)
#define u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE2         ((uint8)2U)
#define u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE1              ((uint8)3U)
#define u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE2              ((uint8)4U)
#define u1ADCDIAG_PIL_PIN_LEVEL                                 ((uint8)5U)
#define u1ADCDIAG_PIL_AD_CORE                                   ((uint8)6U)

#define u1ADCDIAG_PIL_NO_ERROR                    ((uint8)0xFFU)

/*==============================================================================================*/
/* functions                                                                                    */
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*  API Functions                                                                               */
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

/************************************************************************************************/
/* Service name         : AdcDiag_Pil_Init                                                      */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*  t_u1IndexHWUnit     : HW Unit Number                                                        */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Enable error interrupts                                               */
/************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_Init(
    CONST(uint8,  ADCDIAG_CONST)    t_u1IndexHWUnit
);

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_GetErrorData                                              */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1IndexHWUnit             : HW Unit Number                                                        */
/*  t_udAdcDiag_Pil_AdcErrorType: Adc Error Type                                                        */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 :                                                                       */
/*  t_u1ErrorData               : Informations about the error                                          */
/* Description                  : Provide more informations about the error                             */
/********************************************************************************************************/
FUNC(uint8, ADCDIAG_CODE) AdcDiag_Pil_GetErrorData(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetCnvData                                                */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1IndexHWUnit     : HW Unit Number                                                        */
/*      t_u1VirtualChannel  : Virtual Channel                                                       */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint16              : Conversion result                                                     */
/* Description              : Reads the group conversion result                                     */
/****************************************************************************************************/
FUNC(uint16, ADCDIAG_CODE) AdcDiag_Pil_GetCnvData(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(uint8, ADCDIAG_CONST)   t_u1VirtualChannel
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ClearDIR                                                  */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1IndexHWUnit     : HW Unit Number                                                        */
/*      t_u1VirtualChannel  : Virtual Channel                                                       */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Clear Data Supplementary Information Register                         */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ClearDIR(
    CONST(uint8, ADCDIAG_CONST)   t_u1IndexHWUnit,
    CONST(uint8, ADCDIAG_CONST)   t_u1VirtualChannel
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetClocksUsed                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          : None                                                                  */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint32              : ADC clocks status                                                     */
/* Description              : Provide the status of ADC clocks                                      */
/****************************************************************************************************/
FUNC(uint32, ADCDIAG_CODE) AdcDiag_Pil_GetClocksUsed(void);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_EnableClocks                                              */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*  t_u4ClocksUsed          : Backup value for ADC clocks that were enabled before reset            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Re-enable only the ADC clocks that were supplied before reset         */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_EnableClocks(
    CONST(uint32, ADCDIAG_CONST)   t_u4ClocksUsed
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ConfigureSampling                                         */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : Hw Unit Number                                                        */
/*      t_u1Amplifier       : Value of Buffer Amplifier (RRAMP)                                     */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Configure sampling. Configure Buffer Amplifier (RRAMP)                */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ConfigureSampling(
    CONST(uint8,  ADCDIAG_CONST)    t_u1HWUnit,
    CONST(uint8,  ADCDIAG_CONST)    t_u1Amplifier
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetMultiCycle                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/*      t_u1MutiCycleValue  : Scan count value                                                      */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set the scan count in multicycle mode                                 */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetMultiCycle(
    CONST(uint8,  ADCDIAG_CONST)    t_u1HWUnit,
    CONST(uint8,  ADCDIAG_CONST)    t_u1ScanGroup,
    CONST(uint8,  ADCDIAG_CONST)    t_u1MutiCycleValue
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_InitialSettingFlow                                        */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit ID                                                            */
/*    t_u1DataFormat        : Data Format	                                                        */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Settings according to the initial setting procedure                   */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_InitialSettingFlow(
    CONST(uint8, ADCDIAG_CONST) t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST) t_u1DataFormat
);

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_SetChannelConfig                                          */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1HWUnit                  : HW Unit Number                                                        */
/*  t_pu1PhysicalChannels(Sync) : Pointer to list of physical channels                                  */
/*  t_u1PsysicalChannelIndex    : Index for list of physical channels                                   */
/*  t_u1VirtualChannel          : Virtual Channel                                                       */
/*  t_u1SelfDiagMode            : Diagnostic mode                                                       */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 : None                                                                  */
/* Description                  : Configure VCR register for all diagnostic modes                       */
/********************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetChannelConfig(
    CONST(uint8,   ADCDIAG_CONST)        t_u1HWUnit,
    P2CONST(uint8,AUTOMATIC, ADCDIAG_CONST)    t_pu1PhysicalChannels,
    CONST(uint8,   ADCDIAG_CONST)        t_u1PsysicalChannelIndex,
    CONST(uint8,   ADCDIAG_CONST)        t_u1VirtualChannel,
    CONST(uint8,   ADCDIAG_CONST)        t_u1SelfDiagMode
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetChannelPointer                                         */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/*      t_u1StartPointer    : Start Pointer                                                         */
/*      t_u1StartPointer    : Stop Pointer                                                          */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Configure Start and Stop Pointer                                      */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetChannelPointer(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint8, ADCDIAG_CONST)     t_u1StartPointer,
    CONST(uint8, ADCDIAG_CONST)     t_u1StopPointer
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_SetRegWiringBreakDetectionMode1                           */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*t_u1HWUnit                : HW Unit Number                                                        */
/*t_u1ScanGroup             : Scan Group                                                            */
/*t_u1ConversionNo          : Scan count in multicycle scan mode                                    */
/*t_u2PulseWidthWiringBreak1: Wiring-Break Detection Pulse Width                                    */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Setting the registers used for Wiring-Break Detection for Mode 1      */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_SetRegWiringBreakDetectionMode1(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint8, ADCDIAG_CONST)     t_u1ConversionNo,
    CONST(uint16, ADCDIAG_CONST)    t_u2PulseWidthWiringBreak1
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StartScan                                                 */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Start A/D conversion                                                  */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_StartScan(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_GetScanStatus                                             */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*      t_u1HWUnit          : HW Unit Number                                                        */
/*      t_u1ScanGroup       : Scan Group                                                            */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             :                                                                       */
/*      uint8               : Conversion status                                                     */
/* Description              : Reads scan group status                                               */
/****************************************************************************************************/
FUNC(uint8, ADCDIAG_CODE) AdcDiag_Pil_GetScanStatus(
    CONST(uint8, ADCDIAG_CONST)   t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)   t_u1ScanGroup
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StartSelfDiagTH                                           */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_udPilTHData(Sync)  : Pointer to T&H data structure                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : boolean                                                               */
/*     TRUE                 : No timeout occurred                                                   */
/*     FALSE                : Timeout occurred                                                      */
/* Description              : Start Self-Diagnosis T&H                                              */
/****************************************************************************************************/
FUNC(boolean, ADCDIAG_CODE) AdcDiag_Pil_DoSelfDiagTH(
	CONSTP2VAR(AdcDiag_Pil_THData, AUTOMATIC, ADCDIAG_CONST)     t_udPilTHData
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_Set3PointVoltageGenerator                                 */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit Number                                                        */
/*    t_u1VoltageLevel      : Voltage Level                                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set voltage settings for the 3 point voltage generator                */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_Set3PointVoltageGenerator(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1VoltageLevel
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ChangeADCoreVoltageLevel                                  */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*    t_u1HWUnit            : HW Unit Number                                                        */
/*    t_u1VirtualChannel    : Virtual Channel                                                       */
/*    t_u1VoltageLevel      : Voltage Level                                                         */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : Set AdCore voltage value                                              */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ChangeADCoreVoltageLevel(
	CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
	CONST(uint8, ADCDIAG_CONST)     t_u1VirtualChannel,
	CONST(uint8, ADCDIAG_CONST)     t_u1VoltageLevel
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_StopAllScan                                               */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_u1HWUnit           : HW Unit Number                                                        */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : None                                                                  */
/* Description              : All Scan Groups of Module Scan Stop Function                          */
/****************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_StopAllScan(
	CONST(uint8, ADCDIAG_CONST)   t_u1HWUnit
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_ModuleReset                                               */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/*     t_u4TimeoutValue	    : Timeout value for reset                                               */
/*     t_u4ClocksUsed       : Which clock is supplied                                               */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : Std_ReturnType                                                        */
/*     E_OK                 : No timeout occurred                                                   */
/*     E_NOT_OK             : Timeout occurred                                                      */
/* Description              : Software Module Reset Assertion Register for ADC                      */
/****************************************************************************************************/
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_Pil_ModuleReset(
    CONST(uint32, ADCDIAG_CONST)        t_u4TimeoutValue,
    CONST(uint32, ADCDIAG_CONST)        t_u4ClocksUsed
);

/****************************************************************************************************/
/* Service name             : AdcDiag_Pil_IsConversionCompleted                                     */
/* Sync/Async               : Synchronous                                                           */
/* Reentrancy               : Non Reentrant                                                         */
/* Parameters (in)          :                                                                       */
/* 		t_cu1HWUnit	        : HW Unit Number														*/
/* 		t_cu1ScanGroup      : Scan Group Number														*/
/*      t_u4TimeoutValue	: Timeout value                                                         */
/*      t_cbUseStartPointer : Value to check which virtual channel pointer are used                 */
/* Parameters (inout)       : None                                                                  */
/* Parameters (out)         : None                                                                  */
/* Return value             : boolean                                                               */
/*     TRUE                 : No timeout occurred                                                   */
/*     FALSE                : Timeout occurred                                                      */
/* Description              : Wait until the flag is set for the last or first virtual channel      */
/****************************************************************************************************/
FUNC(boolean, ADCDIAG_CODE) AdcDiag_Pil_IsConversionCompleted(
    CONST(uint8, ADCDIAG_CONST)	     t_cu1HWUnit,
    CONST(uint8, ADCDIAG_CONST)	     t_cu1ScanGroup,
    CONST(uint32, ADCDIAG_CONST)     t_cu4TimeoutValue,
    CONST(boolean, ADCDIAG_CONST)	 t_cbUseStartPointer
);

/********************************************************************************************************/
/* Service name                 : AdcDiag_Pil_ClearErrorFlag                                            */
/* Sync/Async                   : Synchronous                                                           */
/* Reentrancy                   : Non Reentrant                                                         */
/* Parameters (in)              :                                                                       */
/*  t_u1IndexHWUnit             : HW Unit Number                                                        */
/*  t_udAdcDiag_Pil_AdcErrorType: Adc Error Type                                                        */
/* Parameters (inout)           : None                                                                  */
/* Parameters (out)             : None                                                                  */
/* Return value                 : None                                                                  */
/* Description                  : Clear the error flags                                                 */
/********************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Pil_ClearErrorFlag(
    CONST(uint8, ADCDIAG_CONST)    t_u1IndexHWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
);

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

#endif /* ADCDIAG_PIL_H */

/*------------------------------------ End Of File --------------------------------------------------*/
