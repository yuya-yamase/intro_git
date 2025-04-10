/* ADCDIAG-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*      ADC DIAG Driver : Upper layer for RH850U2A/U2B                                          */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
/*==============================================================================================*/
/* include files                                                                                */
/*==============================================================================================*/
#include    "Std_Types.h"
#include    "Mcal_SpalCmn.h"
#include    "McalCommon_lib.h"

#include    "AdcDiag.h"
#include    "Reg_Adc.h"

#include    "AdcDiag_Pil.h"

#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
#include "Det.h"
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
/*==============================================================================================*/
/* defines / data types / structs / unions  / macros                                            */
/*==============================================================================================*/
#define u1ADCDIAG_TH_RANGES_VALUE_NUMBER_OF_ROWS            ((uint8)4U)
#define u1ADCDIAG_TH_RANGES_VALUE_NUMBER_OF_COLUMNS         ((uint8)4U)
#define ADCDIAG_ZERO                                        (0U)
#define u1ADCDIAG_MAX_VALUE_ERROR_DATA                      ((uint8)255U)

/* Scan count in multicycle scan mode */
#define u1ADCDIAG_SCAN_COUNT_DEFAULT_VALUE                  ((uint8)0U)

/* Number of virtual channels for T&H that are not contain data that is relevant for the judgment */
#define u1ADCDIAG_TH_VIRTUAL_CHANNELS_NOT_USED                  ((uint8)2U)
/*==============================================================================================*/
/* prototype for local functions                                                                */
/*==============================================================================================*/
#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

/************************************************************************************************/
/* Service name                 : AdcDiag_DoInitialSettings                                     */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1HwUnitIndex         : Hw Unit Number                                                */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : None                                                          */
/* Description                  : Do settings according to the initial setting procedure        */
/************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_DoInitialSettings(
    CONST(uint8,  ADCDIAG_CONST) t_u1HwUnitIndex
);

/************************************************************************************************/
/* Service name                 : AdcDiag_DoDiagWiringBreakFlow                                 */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1AdcDiagGroup        : Group Id                                                      */
/*      t_u1IsSelfTest          : Use to distinct if group is for Self Diagnostic or not        */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Return value                 : boolean                                                       */
/*      TRUE                    : conversion finished with success                              */
/*      FALSE                   : Timeout occurred                                              */
/* Description                  : Do settings for Wiring Break Detection Mode 1 and 2           */
/************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_DoDiagWiringBreakFlow(
    CONST(uint8,  ADCDIAG_CONST) t_u1AdcDiagGroup,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr,
    CONST(boolean,  ADCDIAG_CONST) t_u1IsSelfTest
);

/************************************************************************************************/
/* Service name                 : AdcDiag_DoSelfDiagTH                                          */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*   t_u1AdcDiagGroup           : Group Id                                                      */
/*   t_u1VoltageLevelAtStart    : Voltage level set before starting conversation                */
/*   t_u1VoltageLevelAfterChange: Voltage level set after starting conversation                 */

/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*   t_pu2DataBufferPtr(Sync)   : Pointer to conversion results buffer                          */
/* Return value                 : boolean                                                       */
/*      TRUE                    : conversion finished with success                              */
/*      FALSE                   : Timeout occurred                                              */
/* Description                  : Do settings for setting for Self-Diagnostic T&H               */
/************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_DoSelfDiagTH(
    CONST(uint8,  ADCDIAG_CONST)             t_u1AdcDiagGroup,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageLevelAtStart,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageLevelAfterChange,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
);

/************************************************************************************************/
/* Service name                 : AdcDiag_IsInRange                                             */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*     t_u2ConversionValue      : Conversion results                                            */
/*     t_u2RangesValue(Sync)    : Accepted ranges value                                         */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_IsInRange(
    VAR(uint16,  ADCDIAG_VAR_INIT)            t_u2ConversionValue,
    P2CONST(uint16, AUTOMATIC, ADCDIAG_CONST)      t_u2RangesValue
);

/************************************************************************************************/
/* Service name                 : AdcDiag_JudgeSelfDiagWiringBreakMode2                         */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_JudgeSelfDiagWiringBreakMode2(
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
);

/************************************************************************************************/
/* Service name                 : AdcDiag_CheckSelfDiagTH                                       */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1NumberOfChannels    : Number of physical channels                                   */
/*      t_u1VoltageAtStart      : Voltage level set before starting conversation                */
/*      t_u1VoltageAtEnd        : Voltage level set after starting conversation                 */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_CheckSelfDiagTH(
    CONST(uint8,  ADCDIAG_CONST)             t_u1NumberOfChannels,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageAtStart,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageAtEnd,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
);

/************************************************************************************************/
/* Service name                 : AdcDiag_CopyConversionResults                                 */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1HWUnit              : HW Unit Number                                                */
/*      t_u1StartPointer        : Start pointer                                                 */
/*      t_u1StopPointer         : Stop pointer                                                  */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Return value                 : None                                                          */
/* Description                  : Copy the conversion results from register in result buffer    */
/************************************************************************************************/
static  FUNC(void, ADCDIAG_CODE) AdcDiag_CopyConversionResults(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1StartPointer,
    CONST(uint8, ADCDIAG_CONST)     t_u1StopPointer,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
);

/****************************************************************************************************/
/* Service name                 : AdcDiag_WaitForStatusRegister                                     */
/* Sync/Async                   : Synchronous                                                       */
/* Reentrancy                   : Non Reentrant                                                     */
/* Parameters (in)              :                                                                   */
/*      t_u1HWUnit              : HW Unit Number                                                    */
/*      t_u1ScanGroup           : Scan Group                                                        */
/*      t_u4TimeoutValue        : Accepted timeout                                                  */
/* Parameters (inout)           : None                                                              */
/* Parameters (out)             : None                                                              */
/* Return value                 : boolean                                                           */
/*      TRUE                    : Conversion finished with success                                  */
/*      FALSE                   : Timeout occurred                                                  */
/* Description                  : Wait for conversion to be finished or timeout to be reached       */
/*                              : Scan Group Status Register is polled to get the conversion status */
/* Limitation                   : This API shall not be used for scan groups where multicycle > 0   */
/****************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_WaitForStatusRegister(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint32, ADCDIAG_CONST)    t_u4TimeoutValue
);

/************************************************************************************************/
/* Service name                 : AdcDiag_ModuleReset                                           */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/* t_u4ClocksUsed               : Which clock is supplied                                       */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Module reset executed with success                            */
/*      E_NOT_OK                : Timeout occurred                                              */
/* Description                  : Execute ADC module reset                                      */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_ModuleReset(
    CONST(uint32, ADCDIAG_CONST)    t_u4ClocksUsed
);

/*******************************************************************************************************/
/* Service name                : AdcDiag_ReadClearErrorInfo                                            */
/* Sync/Async                  : Synchronous                                                           */
/* Reentrancy                  : Non Reentrant                                                         */
/* Parameters (in)             :                                                                       */
/* t_udAdcDiag_Pil_AdcErrorType: ADC Error Type                                                        */
/* Parameters (inout)          : None                                                                  */
/* Parameters (out)            :                                                                       */
/* t_pstAdcErrorInfo(Sync)     : Pointer to information errors                                         */
/* Return value                : None                                                                  */
/* Description                 : Provide the error informations                                        */
/*******************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_ReadClearErrorInfo(
    CONST(uint8, ADCDIAG_CONST)                   t_u1HWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType,
    CONSTP2VAR(AdcDiag_ErrorInformationType, AUTOMATIC,  ADCDIAG_CONST)   t_pstAdcErrorInfo
);

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )

#define ADCDIAG_START_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

/************************************************************************************************/
/* Service name         : AdcDiag_CheckErrorFlagAndNotify                                       */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*      t_u1HWUnit      : Hw Unit Number                                                        */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Check the ADC interrupts flag and send the notification               */
/************************************************************************************************/
static FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_CheckErrorFlagAndNotify(
    CONST(uint8, ADCDIAG_CONST)        t_u1HWUnit
);

/*******************************************************************************************************/
/* Service name                : AdcDiag_ProvideErrorFlag                                              */
/* Sync/Async                  : Synchronous                                                           */
/* Reentrancy                  : Non Reentrant                                                         */
/* Parameters (in)             :                                                                       */
/*     t_u1HWUnit              : Hw Unit Number                                                        */
/* t_udAdcDiag_Pil_AdcErrorType: ADC Error Type                                                        */
/* Parameters (inout)          : None                                                                  */
/* Parameters (out)            : None                                                                  */
/* Return value                : boolean                                                               */
/*      TRUE                   : Error flag is set                                                     */
/*      FALSE                  : No error flag                                                         */
/* Description                 : Provide the error flag                                                */
/*******************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE_FAST) AdcDiag_ProvideErrorFlag(
    CONST(uint8, ADCDIAG_CONST)                   t_u1HWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
);

#define ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */

/*==============================================================================================*/
/* constants                                                                                    */
/*==============================================================================================*/
#define ADCDIAG_START_SEC_CONST_UNSPECIFIED
#include "AdcDiag_MemMap.h"

#define ADCDIAG_STOP_SEC_CONST_UNSPECIFIED
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CONST_16
#include "AdcDiag_MemMap.h"

static CONST(uint16, ADCDIAG_CONST) s_cstAdcDiag_THRangesValue[u1ADCDIAG_TH_RANGES_VALUE_NUMBER_OF_ROWS][u1ADCDIAG_TH_RANGES_VALUE_NUMBER_OF_COLUMNS] = {
    { (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VCC,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VCC },
    { (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VCC,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VCC,    (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VSS },
    { (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MIN_RANGE_1_2VCC, (uint16)ADCDIAG_CFG_TH_MAX_RANGE_1_2VCC },
    { (uint16)ADCDIAG_CFG_TH_MIN_RANGE_1_2VCC, (uint16)ADCDIAG_CFG_TH_MAX_RANGE_1_2VCC, (uint16)ADCDIAG_CFG_TH_MIN_RANGE_VSS,    (uint16)ADCDIAG_CFG_TH_MAX_RANGE_VSS }
};

#define ADCDIAG_STOP_SEC_CONST_16
#include "AdcDiag_MemMap.h"
/*==============================================================================================*/
/* variables                                                                                    */
/*==============================================================================================*/
#define ADCDIAG_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "AdcDiag_MemMap.h"

#define ADCDIAG_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "AdcDiag_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* Public API                                                                                   */
/*----------------------------------------------------------------------------------------------*/
#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

/************************************************************************************************/
/* Service name         : AdcDiag_PreAdcInit                                                    */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      : None                                                                  */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         :                                                                       */
/*    Std_ReturnType    : E_OK/ E_NOT_OK                                                        */
/* Description          : Execute Self-Diagnosis Function                                       */
/* Limitation           : This API needs to be called after Mcu_Init() and before Adc_Init()    */
/************************************************************************************************/

FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_PreAdcInit( void )
{
    VAR(uint16, ADCDIAG_VAR_NO_INIT)   t_au2AdcDiag_SelfDiagResults[ADCDIAG_CFG_MAX_BUFFER_SIZE];
    VAR(uint32, ADCDIAG_VAR_NO_INIT)   t_u4PeripheralClocksUsed;
    VAR(uint32, ADCDIAG_VAR_NO_INIT)   t_u4AdcClocksUsed;
    VAR(AdcDiag_DiagType, ADCDIAG_VAR_NO_INIT)  t_udConfigDiagMode;
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    t_udErrorStatus;
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    t_udErrorStatusModuleReset;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1AdcDiagGroup;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1IndexVoltage;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1IndexHwUnit;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1IndexVoltageLevelAfterChange;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1IndexVoltageLevelAtStart;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1NumberOfPhysicalChannels;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)  t_u1IsConversionCompleted;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)  t_bHwUnitUsed;

    t_u1AdcDiagGroup = (uint8)0U;
    t_u4AdcClocksUsed = (uint32)0U;
    t_udErrorStatus = (Std_ReturnType)E_OK;

    while( ( t_u1AdcDiagGroup != (uint8)ADCDIAG_CFG_GRP_SIZE) && ( t_udErrorStatus != (Std_ReturnType)E_NOT_OK ) ) {

        t_u1IndexHwUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1HWUnit;
        AdcDiag_DoInitialSettings(t_u1IndexHwUnit);

        t_udConfigDiagMode = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cudDiagType;

        switch ( t_udConfigDiagMode ) {
            case ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1:
                /* Execute Self-Diagnostic Wiring Break Detection Mode 1 */
                t_u1IsConversionCompleted = AdcDiag_DoDiagWiringBreakFlow( t_u1AdcDiagGroup, (uint16*)&t_au2AdcDiag_SelfDiagResults[0], (boolean)TRUE);
               /* Judge only if timeout did not occur */
                if ( t_u1IsConversionCompleted == (boolean)TRUE ) {
                    /* Judge if the conversion results of Self-Diagnostic Wiring Break Detection Mode 1 are in accepted range */
                    t_udErrorStatus = AdcDiag_IsInRange( t_au2AdcDiag_SelfDiagResults[0], &cstAdcDiag_UserConfig.cpstWBRangeVal[0][0]);
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                    if( t_udErrorStatus == (Std_ReturnType)E_NOT_OK ) {
                        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_WIRING_BREAK_MODE1 );
                    }
                    else {
                        /* No error occurred */
                    }
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                }
                else {
                    t_udErrorStatus = (Std_ReturnType)E_NOT_OK;

#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                    (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_TIMEOUT_SELF_DIAG_WIRING_BREAK_MODE1 );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                }
                break;
            case ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2:
                /* Execute Self-Diagnostic Wiring Break Detection Mode 2 */
                t_u1IsConversionCompleted = AdcDiag_DoDiagWiringBreakFlow(t_u1AdcDiagGroup, (uint16*)&t_au2AdcDiag_SelfDiagResults[0], (boolean)TRUE);
                /* Judge only if timeout did not occur */
                if ( t_u1IsConversionCompleted == (boolean)TRUE ) {
                    /* Judge if the conversion results of Self-Diagnostic Wiring Break Detection Mode 2 are in accepted range */
                    t_udErrorStatus = AdcDiag_JudgeSelfDiagWiringBreakMode2( (uint16*)&t_au2AdcDiag_SelfDiagResults[0] );
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                    if( t_udErrorStatus == (Std_ReturnType)E_NOT_OK ) {
                        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_WIRING_BREAK_MODE2 );
                    }
                    else {
                        /* No error occurred */
                    }
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                }
                else {
                    t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                    (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_TIMEOUT_SELF_DIAG_WIRING_BREAK_MODE2 );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                }
                break;
            case ADCDIAG_SELF_DIAG_TH:
                t_u1NumberOfPhysicalChannels = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1PhysicalChannelsNo;
                t_u1IndexVoltage = (uint8)0U;

                while ( ( t_u1IndexVoltage < (uint8)ADCDIAG_CFG_TH_VOLTAGE_LEVEL_TOTAL_COMBINATION ) && ( t_udErrorStatus != (Std_ReturnType)E_NOT_OK ) ) {

                    t_u1IndexVoltageLevelAtStart = cstAdcDiag_UserConfig.cpstVoltLlvComb[t_u1IndexVoltage].cu1AtStart;
                    t_u1IndexVoltageLevelAfterChange = cstAdcDiag_UserConfig.cpstVoltLlvComb[t_u1IndexVoltage].cu1AfterStart;

                    /* Execute Pin-Level Self-Diagnosis of the T&H Path */
                    t_u1IsConversionCompleted = AdcDiag_DoSelfDiagTH(t_u1AdcDiagGroup, t_u1IndexVoltageLevelAtStart, t_u1IndexVoltageLevelAfterChange, (uint16 *)&t_au2AdcDiag_SelfDiagResults[0]);
                    /* Judge only if timeout did not occur */
                    if ( t_u1IsConversionCompleted == (boolean)TRUE ) {
                        /* Judge if the conversion results of Pin-Level Self-Diagnosis of the T&H Path are in accepted range */
                        t_udErrorStatus = AdcDiag_CheckSelfDiagTH( t_u1NumberOfPhysicalChannels, t_u1IndexVoltageLevelAtStart, t_u1IndexVoltageLevelAfterChange, (uint16*)&t_au2AdcDiag_SelfDiagResults[0] );
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                        if( t_udErrorStatus == (Std_ReturnType)E_NOT_OK ) {
                            (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_TH );
                        }
                        else {
                            /* No error occurred */
                        }
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                        t_u1IndexVoltage++;
                    }
                    else {
                        t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_TIMEOUT_SELF_DIAG_TH );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                    }
                }
                break;
            default:
                /* Do nothing */
                break;
        }
        t_u1AdcDiagGroup++;
    }
    /* The value is bit encoded, if the bit is 0 then the clock is supplied and if the bit is 1 then the clock is stopped */
    t_u4PeripheralClocksUsed = AdcDiag_Pil_GetClocksUsed();

    /* Take into account if one of the ADC HW Unit is not used but the corresponding clock is supplied */
    for ( t_u1IndexHwUnit = (uint8)0U; t_u1IndexHwUnit < (uint8)ADC_HWUNIT_NUM; t_u1IndexHwUnit++ )
    {
        t_bHwUnitUsed = cstAdcDiag_UserConfig.cpstHWConfig[t_u1IndexHwUnit].cbHwUnitUsed;
        if ( t_bHwUnitUsed == (boolean)FALSE )
        {
            t_u4AdcClocksUsed |= (uint32)( t_u4PeripheralClocksUsed | ( (uint32)1U << (uint32)t_u1IndexHwUnit ) );
        }
    }
    /* Reset only ADC HW Units that are used if not timeout occurred */
    t_udErrorStatusModuleReset = AdcDiag_ModuleReset( t_u4AdcClocksUsed );

    if ( t_udErrorStatusModuleReset == (Std_ReturnType)E_OK )
    {
        /* Re-enable only the ADC clocks that were supplied before reset */
        AdcDiag_Pil_EnableClocks( t_u4PeripheralClocksUsed );
    }
    else
    {
        t_udErrorStatus = t_udErrorStatusModuleReset;
    }

    return ( t_udErrorStatus );
}

/************************************************************************************************/
/* Service name         : AdcDiag_Init                                                          */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      : None                                                                  */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Perform AdcDiag initialization sequence                               */
/************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_Init( void )
{
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1IndexHWUnit;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)  t_bIndexHWUnitUsed;

    for ( t_u1IndexHWUnit = (uint8)0U; t_u1IndexHWUnit < (uint8)ADC_HWUNIT_NUM; t_u1IndexHWUnit++ ) {
        t_bIndexHWUnitUsed = cstAdcDiag_UserConfig.cpstHWConfig[t_u1IndexHWUnit].cbHwUnitUsed;
        if ( t_bIndexHWUnitUsed == (boolean)TRUE) {
            AdcDiag_Pil_Init( t_u1IndexHWUnit );
        }
    }
}

/******************************************************************************************************/
/* Service name               : AdcDiag_StartWiringBreakDetection                                     */
/* Sync/Async                 : Synchronous                                                           */
/* Reentrancy                 : Non Reentrant                                                         */
/* Parameters (in)            :                                                                       */
/*   t_u1AdcDiagGroup         : Numeric ID of requested ADC DIAG channel group.                       */
/* Parameters (inout)         : None                                                                  */
/* Parameters (out)           :                                                                       */
/*   t_pu2DataBufferPtr(Sync) : Pointer to result data buffer                                         */
/* Return value               :                                                                       */
/*   Std_ReturnType           : E_NOT_OK / E_OK                                                       */
/* Description                : Execute Wiring-Break Detection in configured mode                     */
/******************************************************************************************************/
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_StartWiringBreakDetection(
    CONST(uint8,  ADCDIAG_CONST) t_u1AdcDiagGroup,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
)
{
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
    VAR(AdcDiag_DiagType, ADCDIAG_VAR_NO_INIT)    t_udConfigDiagMode;
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)     t_u1ErrorStatus;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)            t_u1IsConversionCompleted;

#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
    t_udConfigDiagMode = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cudDiagType;
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
    t_u1ErrorStatus = (Std_ReturnType)E_OK;

    t_u1IsConversionCompleted = AdcDiag_DoDiagWiringBreakFlow( t_u1AdcDiagGroup, t_pu2DataBufferPtr, (boolean)FALSE );

    if ( t_u1IsConversionCompleted == (boolean)FALSE)
    {
        t_u1ErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
        if ( t_udConfigDiagMode == ADCDIAG_WIRING_BREAK_DETECTION_MODE1 ) {
            (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_WIRING_BREAK_DETECTION, u1ADCDIAG_E_TIMEOUT_WIRING_BREAK_MODE1 );
        }
        else
        {
            (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_WIRING_BREAK_DETECTION, u1ADCDIAG_E_TIMEOUT_WIRING_BREAK_MODE2 );
        }
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
    }

    return ( t_u1ErrorStatus );
}

/******************************************************************************************************/
/* Service name               : AdcDiag_StartAdCoreSelfDiag                                           */
/* Sync/Async                 : Synchronous                                                           */
/* Reentrancy                 : Non Reentrant                                                         */
/* Parameters (in)            :                                                                       */
/*    t_u1AdcDiagGroup        : Numeric ID of requested ADC DIAG channel group.                       */
/*    t_u1VoltageLevel        : Voltage level used for testing the AD core                            */
/* Parameters (inout)         : None                                                                  */
/* Parameters (out)           :                                                                       */
/*    t_pu2DataBufferPtr(Sync): Pointer to result data buffer                                         */
/* Return value               :                                                                       */
/*    Std_ReturnType          : E_NOT_OK / E_OK                                                       */
/* Description                : Execute AdCore diagnostic                                             */
/******************************************************************************************************/
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_StartAdCoreSelfDiag(
	CONST(uint8, ADCDIAG_CONST) t_u1AdcDiagGrp,
	CONST(uint8, ADCDIAG_CONST) t_u1VoltageLevel,
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST) t_pu2DataBufferPtr
)
{
	VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    	t_u1ErrorStatus;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1HWUnit;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1ScanGroup;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StartPointer;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StopPointer;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1VirtualChannel;

    t_u1HWUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1HWUnit;
    t_u1StartPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1StartChannel;
    t_u1StopPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1StopChannel;
    t_u1ScanGroup = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1SG;

    t_u1ErrorStatus = (Std_ReturnType)E_OK;

    for( t_u1VirtualChannel = t_u1StartPointer; t_u1VirtualChannel <= t_u1StopPointer; t_u1VirtualChannel++ )
    {
        AdcDiag_Pil_SetChannelConfig( t_u1HWUnit, NULL_PTR,(uint8)( t_u1VirtualChannel - t_u1StartPointer ), t_u1VirtualChannel, u1ADCDIAG_PIL_AD_CORE );    /* Set the VCR register */
        AdcDiag_Pil_ChangeADCoreVoltageLevel( t_u1HWUnit, t_u1VirtualChannel, t_u1VoltageLevel ); /* Set A/D core self-diagnosis voltage level in GCTRL */
    }

    AdcDiag_Pil_SetChannelPointer( t_u1HWUnit, t_u1ScanGroup, t_u1StartPointer, t_u1StopPointer );  /* Set Start and End Pointer */

    /* Set scan count in multicycle mode to default value */
    AdcDiag_Pil_SetMultiCycle( t_u1HWUnit, t_u1ScanGroup, u1ADCDIAG_SCAN_COUNT_DEFAULT_VALUE );

    /* Clear ADCnDIRj.WFLAG before starting a new conversion */
    AdcDiag_Pil_ClearDIR( t_u1HWUnit, t_u1StopPointer );

    AdcDiag_Pil_StartScan( t_u1HWUnit, t_u1ScanGroup ); /* Start A/D conversion */

    /* Wait for the ADCnDIRj.WFLAG to be set for last virtual channel and copy the results only if timeout did not occur */

    if ( AdcDiag_Pil_IsConversionCompleted( t_u1HWUnit, t_u1ScanGroup, cstAdcDiag_UserConfig.cpstTimeoutVal->cu4AdCoreTimeout, (boolean)FALSE ) == (boolean)TRUE )
    {
        AdcDiag_CopyConversionResults( t_u1HWUnit, t_u1StartPointer, t_u1StopPointer, t_pu2DataBufferPtr );
    }
    else
    {
        t_u1ErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_AD_CORE, u1ADCDIAG_E_TIMEOUT_AD_CORE );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
    }

    return ( t_u1ErrorStatus );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_StartPinLevel                                         */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1AdcDiagGroup        : Numeric ID of requested ADC DIAG channel group.               */
/*      t_u1VoltageLevel        : Voltage level used for testing the Pin Level                  */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to result data buffer                                 */
/* Return value                 :                                                               */
/*      Std_ReturnType          : E_NOT_OK / E_OK                                               */
/* Description                  : Execute Pin level diagnostic                                  */
/************************************************************************************************/
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_StartPinLevel(
	CONST(uint8, ADCDIAG_CONST) t_u1AdcDiagGrp,
	CONST(uint8, ADCDIAG_CONST) t_u1VoltageLevel,
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST) t_pu2DataBufferPtr
)
{
    P2CONST(uint8,AUTOMATIC, ADCDIAG_VAR_NO_INIT)   t_u1PhysicalChannels;
	VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    	t_u1ErrorStatus;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1HWUnit;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1ScanGroup;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StartPointer;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StopPointer;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1VirtualChannel;

    t_u1HWUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1HWUnit;
    t_u1StartPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1StartChannel;
    t_u1StopPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1StopChannel;
    t_u1ScanGroup = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1SG;
    t_u1PhysicalChannels = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cstPhysicalChannels;

	t_u1ErrorStatus = (Std_ReturnType)E_OK;

    for( t_u1VirtualChannel = t_u1StartPointer; t_u1VirtualChannel <= t_u1StopPointer; t_u1VirtualChannel++ )
    {
        AdcDiag_Pil_SetChannelConfig( t_u1HWUnit, t_u1PhysicalChannels, (uint8)( t_u1VirtualChannel - t_u1StartPointer ), t_u1VirtualChannel, u1ADCDIAG_PIL_PIN_LEVEL );  /* Set the VCR register */
    }

    AdcDiag_Pil_Set3PointVoltageGenerator( t_u1HWUnit, t_u1VoltageLevel );

    AdcDiag_Pil_SetChannelPointer( t_u1HWUnit, t_u1ScanGroup, t_u1StartPointer, t_u1StopPointer );  /* Set Start and End Pointer */

    /* Set scan count in multicycle mode to default value */
    AdcDiag_Pil_SetMultiCycle( t_u1HWUnit, t_u1ScanGroup, u1ADCDIAG_SCAN_COUNT_DEFAULT_VALUE );

    /* Clear ADCnDIRj.WFLAG before starting a new conversion */
    AdcDiag_Pil_ClearDIR( t_u1HWUnit, t_u1StopPointer );

    AdcDiag_Pil_StartScan( t_u1HWUnit, t_u1ScanGroup ); /* Start A/D conversion */

    /* Wait for the ADCnDIRj.WFLAG to be set for last virtual channel and copy the results only if timeout did not occur */

    if ( AdcDiag_Pil_IsConversionCompleted( t_u1HWUnit, t_u1ScanGroup, cstAdcDiag_UserConfig.cpstTimeoutVal->cu4PinLvlTimeout, (boolean)FALSE ) == (boolean)TRUE )
    {
        AdcDiag_CopyConversionResults( t_u1HWUnit, t_u1StartPointer, t_u1StopPointer, t_pu2DataBufferPtr );
    }
    else
    {
        t_u1ErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PIN_LEVEL, u1ADCDIAG_E_TIMEOUT_PIN_LEVEL );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
    }

    return ( t_u1ErrorStatus );
}

/******************************************************************************************************/
/* Service name               : AdcDiag_GetErrorStatus                                                */
/* Sync/Async                 : Synchronous                                                           */
/* Reentrancy                 : Non Reentrant                                                         */
/* Parameters (in)            :                                                                       */
/*    t_u1AdcDiagGroup        : Numeric ID of requested ADC DIAG channel group.                       */
/* Parameters (inout)         : None                                                                  */
/* Parameters (out)           :                                                                       */
/*    t_pstAdcErrorInfo(Sync) : Pointer to detail information about errors                            */
/* Return value               : None                                                                  */
/* Description                : Read ADC error flags and provide detail information to upper layer    */
/*                            : Error flags are cleared inside Adc HW                                 */
/******************************************************************************************************/
FUNC(void, ADCDIAG_CODE) AdcDiag_GetErrorStatus(
	CONST(uint8, ADCDIAG_CONST) t_u1AdcDiagGrp,
	CONSTP2VAR(AdcDiag_ErrorInformationType, AUTOMATIC,  ADCDIAG_CONST)   t_pstAdcErrorInfo
)
{
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1HWUnit;

    /* If no error is found, this is the status reported to upper layer*/
    t_u1HWUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGrp].cu1HWUnit;

    AdcDiag_ReadClearErrorInfo( t_u1HWUnit, ADCDIAG_PIL_OVERLAPERROR, t_pstAdcErrorInfo );

    if ( t_pstAdcErrorInfo->udErrorId == ADCDIAG_E_OK ) {
        AdcDiag_ReadClearErrorInfo( t_u1HWUnit, ADCDIAG_PIL_PARITYPERROR, t_pstAdcErrorInfo );
    }

    if ( t_pstAdcErrorInfo->udErrorId == ADCDIAG_E_OK ) {
        AdcDiag_ReadClearErrorInfo( t_u1HWUnit, ADCDIAG_PIL_IDERROR, t_pstAdcErrorInfo );
    }
}

/************************************************************************************************/
/* Service name         : AdcDiag_ErrorNotification                                             */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*      t_u1HWUnit      : HW Unit Number                                                        */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Notify user that error A/D error occurred                             */
/************************************************************************************************/
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
FUNC(void, ADCDIAG_CODE) AdcDiag_ErrorNotification(
    CONST(uint8, ADCDIAG_CONST) t_u1HWUnit
)
{
    AdcDiag_NotifFunc                       t_pvdNotifyFunc;

    t_pvdNotifyFunc = cstAdcDiag_UserConfig.cpstHWConfig[t_u1HWUnit].pvdNotifyFunc;
    if ( t_pvdNotifyFunc != NULL_PTR ) {
        t_pvdNotifyFunc( t_u1HWUnit );
    }
}
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* Function from ISR                                                                            */
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name         : AdcDiag_Intrpt                                                        */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      : None                                                                  */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Function from each ISR (Interrupt Service Routines)                   */
/************************************************************************************************/

/* ISR(ADCDIAG) */
#if ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT0_ERR ) )
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit0_Err(void)
{
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
    AdcDiag_CheckErrorFlagAndNotify((uint8)ADC_HWUNIT0);
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
}
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT0_ERR ) ) */

#if ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT1_ERR ) )
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit1_Err(void)
{
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
    AdcDiag_CheckErrorFlagAndNotify((uint8)ADC_HWUNIT1);
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
}
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT1_ERR ) )  */

#if ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT2_ERR ) )
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit2_Err(void)
{
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
    AdcDiag_CheckErrorFlagAndNotify((uint8)ADC_HWUNIT2);
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
}
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT2_ERR ) ) */

#define ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

#define ADCDIAG_START_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"
/*----------------------------------------------------------------------------------------------*/
/* Private API                                                                                  */
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name                 : AdcDiag_DoInitialSettings                                     */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1HwUnitIndex         : Hw Unit Number                                                */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : None                                                          */
/* Description                  : Do settings according to the initial setting procedure        */
/************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_DoInitialSettings(
    CONST(uint8,  ADCDIAG_CONST) t_u1HwUnitIndex)
{
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)    t_u1DataFormat;

    t_u1DataFormat = cstAdcDiag_UserConfig.cpstHWConfig[t_u1HwUnitIndex].cu1DataFormat;

     /* Settings according to the initial setting procedure */
    AdcDiag_Pil_InitialSettingFlow( t_u1HwUnitIndex, t_u1DataFormat);
}

/************************************************************************************************/
/* Service name                 : AdcDiag_DoDiagWiringBreakFlow                                 */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1AdcDiagGroup        : Group Id                                                      */
/*      t_u1IsSelfTest          : Use to distinct if group is for Self Diagnostic or not        */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Return value                 : boolean                                                       */
/*      TRUE                    : conversion finished with success                              */
/*      FALSE                   : Timeout occurred                                              */
/* Description                  : Do settings for Wiring Break Detection Mode 1 and 2           */
/************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_DoDiagWiringBreakFlow(
    CONST(uint8,  ADCDIAG_CONST) t_u1AdcDiagGroup,
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr,
    CONST(boolean,  ADCDIAG_CONST) t_u1IsSelfTest)
{
    P2CONST(uint8,AUTOMATIC, ADCDIAG_VAR_NO_INIT)   t_pu1PhysicalChannels;
    VAR(AdcDiag_DiagType, ADCDIAG_VAR_NO_INIT)      t_udConfigDiagMode;
    VAR(uint32, ADCDIAG_VAR_NO_INIT)                t_u4TimeoutValue;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)               t_u1IsConversionCompleted;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1DiagMode;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1HWUnit;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1ScanGroup;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StartPointer;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1StopPointer;

    t_udConfigDiagMode = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cudDiagType;
    t_u1HWUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1HWUnit;
    t_u1StartPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1StartChannel;
    t_u1StopPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1StopChannel;
    t_u1ScanGroup = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1SG;
    t_pu1PhysicalChannels = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cstPhysicalChannels;

    t_u1IsConversionCompleted = (boolean)TRUE;

    /* Based on the configured wire breaking mode, execute the self diagnostic */
    if ( t_u1IsSelfTest == (boolean)TRUE )
    {
        t_u4TimeoutValue = cstAdcDiag_UserConfig.cpstTimeoutVal->cu4SelfDiagWiringBreakTimeout;
        if ( t_udConfigDiagMode == ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1 )
        {
            t_u1DiagMode = u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE1;
        }
        else if ( t_udConfigDiagMode == ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2 )
        {
            t_u1DiagMode = u1ADCDIAG_PIL_SELF_WIRING_BREAK_DETECTION_MODE2;
        }
        else
        {
            t_u1DiagMode = u1ADCDIAG_PIL_NOT_APPLICABLE;

        }
    }
    else
    {
        t_u4TimeoutValue = cstAdcDiag_UserConfig.cpstTimeoutVal->cu4WiringBreakTimeout;
        if ( t_udConfigDiagMode == ADCDIAG_WIRING_BREAK_DETECTION_MODE1 )
        {
            t_u1DiagMode = u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE1;
        }
        else if ( t_udConfigDiagMode == ADCDIAG_WIRING_BREAK_DETECTION_MODE2 )
        {
            t_u1DiagMode = u1ADCDIAG_PIL_WIRING_BREAK_DETECTION_MODE2;
        }
        else
        {
            t_u1DiagMode = u1ADCDIAG_PIL_NOT_APPLICABLE;

        }
    }

    if ( t_u1DiagMode != u1ADCDIAG_PIL_NOT_APPLICABLE ) {

        AdcDiag_Pil_SetChannelConfig( t_u1HWUnit, t_pu1PhysicalChannels, ADCDIAG_ZERO, t_u1StartPointer, t_u1DiagMode ); /* Set the VCR register */

        AdcDiag_Pil_SetChannelPointer( t_u1HWUnit, t_u1ScanGroup, t_u1StartPointer, t_u1StopPointer );  /* Set Start and End Pointer */

        /* Extra configuration needs to be done */
        if ( t_udConfigDiagMode == ADCDIAG_WIRING_BREAK_DETECTION_MODE1 )
        {
            /* For Wiring Break Detection Mode 1, the BUFAMPD is configured by the application */
            AdcDiag_Pil_SetRegWiringBreakDetectionMode1( t_u1HWUnit, t_u1ScanGroup, (uint8)ADCDIAG_CFG_SG_MULTICYCLE, (uint16)ADCDIAG_CFG_PULSE_WIDTH_WIRING_BREAK_1 );
        }
        else if ( t_udConfigDiagMode == ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1 )
        {
            AdcDiag_Pil_SetRegWiringBreakDetectionMode1( t_u1HWUnit, t_u1ScanGroup, (uint8)ADCDIAG_CFG_SG_MULTICYCLE, (uint16)ADCDIAG_CFG_PULSE_WIDTH_WIRING_BREAK_1 );
            AdcDiag_Pil_ConfigureSampling( t_u1HWUnit, ADC_SMPCR_BUFAMPD_ENABLE );
        }
        else
        {
            /* Set scan count in multicycle mode to default value */
            AdcDiag_Pil_SetMultiCycle(t_u1HWUnit, t_u1ScanGroup, u1ADCDIAG_SCAN_COUNT_DEFAULT_VALUE );
        }

        /* Wiring Break Detection Mode 2 and Self-Wiring Break Mode 2 must use the ADCnDIRj.WFLAG to verify that the A/D conversion values are stored in Data Register */
        if ( ( t_udConfigDiagMode == ADCDIAG_WIRING_BREAK_DETECTION_MODE2 )
          || ( t_udConfigDiagMode == ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2 ) )
        {
            /* Clear ADCnDIRj.WFLAG before starting a new conversion */
            AdcDiag_Pil_ClearDIR( t_u1HWUnit, t_u1StopPointer );

            AdcDiag_Pil_StartScan( t_u1HWUnit, t_u1ScanGroup ); /* Start A/D conversion */

            /* Wait for the ADCnDIRj.WFLAG to be set for last virtual channel */
            t_u1IsConversionCompleted = AdcDiag_Pil_IsConversionCompleted( t_u1HWUnit, t_u1ScanGroup, t_u4TimeoutValue, (boolean)FALSE );
        }
        /* Wiring Break Detection Mode 1 and Self-Wiring Break Mode 1 must use the status register flag to verify that the AD conversion is completed */
        else
        {
            AdcDiag_Pil_StartScan( t_u1HWUnit, t_u1ScanGroup ); /* Start A/D conversion */
            /* Wait until the conversion is finished */
            t_u1IsConversionCompleted = AdcDiag_WaitForStatusRegister( t_u1HWUnit, t_u1ScanGroup, t_u4TimeoutValue );
        }
        if ( t_u1IsConversionCompleted == (boolean)TRUE )
        {
            /* Copy results for all channels configured */
            AdcDiag_CopyConversionResults( t_u1HWUnit, t_u1StartPointer, t_u1StopPointer, t_pu2DataBufferPtr );
        }
    }

    return ( t_u1IsConversionCompleted );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_DoSelfDiagTH                                          */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*   t_u1AdcDiagGroup           : Group Id                                                      */
/*   t_u1VoltageLevelAtStart    : Voltage level set before starting conversation                */
/*   t_u1VoltageLevelAfterChange: Voltage level set after starting conversation                 */

/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*   t_pu2DataBufferPtr(Sync)   : Pointer to conversion results buffer                          */
/* Return value                 : boolean                                                       */
/*      TRUE                    : conversion finished with success                              */
/*      FALSE                   : Timeout occurred                                              */
/* Description                  : Do settings for setting for Self-Diagnostic T&H               */
/************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_DoSelfDiagTH(
    CONST(uint8,  ADCDIAG_CONST)             t_u1AdcDiagGroup,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageLevelAtStart,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageLevelAfterChange,
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
)
{
    VAR(AdcDiag_Pil_THData, ADCDIAG_VAR_NO_INIT) t_udPilTHData;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)            t_u1IsConversionCompleted;

    t_udPilTHData.u1HWUnit = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1HWUnit;
    t_udPilTHData.u1ScanGroup = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1SG;
    t_udPilTHData.u1StartPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1StartChannel;
    t_udPilTHData.u1StopPointer = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1StopChannel;
    t_udPilTHData.u1PhysicalChannelsNo = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cu1PhysicalChannelsNo;
    t_udPilTHData.u4TimeoutValueA = cstAdcDiag_UserConfig.cpstTimeoutVal->cu4SelfDiagTh_Vch0Timeout;
    t_udPilTHData.u4TimeoutValueB = cstAdcDiag_UserConfig.cpstTimeoutVal->cu4SelfDiagThTimeout;
    t_udPilTHData.u1VoltageLevelAtStart = t_u1VoltageLevelAtStart;
    t_udPilTHData.u1VoltageLevelAfterChange = t_u1VoltageLevelAfterChange;
    t_udPilTHData.pu1PhysicalChannels = cstAdcDiag_UserConfig.cpstGroupConfig[t_u1AdcDiagGroup].cstPhysicalChannels;

    t_u1IsConversionCompleted = (boolean)TRUE;

    /* Do diagnostics steps and copy results if no timeout occurs. */
    if ( AdcDiag_Pil_DoSelfDiagTH( &t_udPilTHData ) == (boolean)TRUE )
    {
        /* The first 2 channels do not contain data that is relevant for the judgment */
        AdcDiag_CopyConversionResults( t_udPilTHData.u1HWUnit, t_udPilTHData.u1StartPointer + u1ADCDIAG_TH_VIRTUAL_CHANNELS_NOT_USED, t_udPilTHData.u1StopPointer, t_pu2DataBufferPtr); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
    }
    else
    {
    	t_u1IsConversionCompleted = (boolean)FALSE;
    }

    return ( t_u1IsConversionCompleted );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_IsInRange                                             */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*     t_u2ConversionValue      : Conversion results                                            */
/*     t_u2RangesValue(Sync)    : Accepted ranges value                                         */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_IsInRange(
	VAR(uint16,  ADCDIAG_VAR_INIT)            t_u2ConversionValue,
	P2CONST(uint16, AUTOMATIC, ADCDIAG_CONST)      t_u2RangesValue
)
{
	VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    t_udErrorStatus;

	if ( ( t_u2ConversionValue >= t_u2RangesValue[0] ) && ( t_u2ConversionValue <= t_u2RangesValue[1] ) ) {
		/* The conversion results are in accepted range */
		t_udErrorStatus = (Std_ReturnType)E_OK;
	}
	else{

		/* The conversion results are not in accepted range */
		t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
	}

	return ( t_udErrorStatus );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_JudgeSelfDiagWiringBreakMode2                         */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_JudgeSelfDiagWiringBreakMode2(
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
)
{
	VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    t_udErrorStatus;

	t_udErrorStatus  = AdcDiag_IsInRange(t_pu2DataBufferPtr[0], &cstAdcDiag_UserConfig.cpstWBRangeVal[0][0]);
	t_udErrorStatus |= AdcDiag_IsInRange(t_pu2DataBufferPtr[1], &cstAdcDiag_UserConfig.cpstWBRangeVal[1][0]);

	return ( t_udErrorStatus );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_CheckSelfDiagTH                                       */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1NumberOfChannels    : Number of physical channels                                   */
/*      t_u1VoltageAtStart      : Voltage level set before starting conversation                */
/*      t_u1VoltageAtEnd        : Voltage level set after starting conversation                 */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Conversion results are in accepted range                      */
/*      E_NOT_OK                : Conversion results are not in accepted range                  */
/* Description                  : Check if the conversion results are in accepted range         */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_CheckSelfDiagTH(
    CONST(uint8,  ADCDIAG_CONST)             t_u1NumberOfChannels,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageAtStart,
    CONST(uint8,  ADCDIAG_CONST)             t_u1VoltageAtEnd,
    CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
)
{
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)    t_u1ErrorStatus;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1Iterator;
    VAR(uint8, ADCDIAG_VAR_NO_INIT)    t_u1Index;

    t_u1Iterator = (uint8)0U;
    t_u1ErrorStatus = (Std_ReturnType)E_OK;

    while ( (t_u1Iterator < t_u1NumberOfChannels) && (t_u1ErrorStatus != (Std_ReturnType)E_NOT_OK) )
    {
        t_u1Index = (uint8)( (uint8)2U * ( t_u1Iterator % (uint8)2U ) );
        t_u1ErrorStatus = AdcDiag_IsInRange(t_pu2DataBufferPtr[t_u1Iterator], &s_cstAdcDiag_THRangesValue[t_u1VoltageAtStart][t_u1Index]);

        t_u1Iterator++;
    }

    while ( ( t_u1Iterator < ( t_u1NumberOfChannels * (uint8)2U ) ) && ( t_u1ErrorStatus != (Std_ReturnType)E_NOT_OK ) )
    {
        t_u1Index = (uint8)( (uint8)2U * ( (uint8)1U - (t_u1Iterator % (uint8)2U) ) );
        t_u1ErrorStatus = AdcDiag_IsInRange(t_pu2DataBufferPtr[t_u1Iterator], &s_cstAdcDiag_THRangesValue[t_u1VoltageAtEnd][t_u1Index]);

        t_u1Iterator++;
    }

    return ( t_u1ErrorStatus );
}

/************************************************************************************************/
/* Service name                 : AdcDiag_CopyConversionResults                                 */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/*      t_u1HWUnit              : HW Unit Number                                                */
/*      t_u1StartPointer        : Start pointer                                                 */
/*      t_u1StopPointer         : Stop pointer                                                  */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             :                                                               */
/*      t_pu2DataBufferPtr(Sync): Pointer to conversion results buffer                          */
/* Return value                 : None                                                          */
/* Description                  : Copy the conversion results from register in result buffer    */
/************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_CopyConversionResults(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1StartPointer,
    CONST(uint8, ADCDIAG_CONST)     t_u1StopPointer,
	CONSTP2VAR(uint16, AUTOMATIC, ADCDIAG_CONST)  t_pu2DataBufferPtr
    )
{
    VAR(uint8, ADCDIAG_VAR_NO_INIT)                 t_u1VirtualChannel;

    for( t_u1VirtualChannel = t_u1StartPointer; t_u1VirtualChannel <= t_u1StopPointer; t_u1VirtualChannel++ ) {
        t_pu2DataBufferPtr[t_u1VirtualChannel - t_u1StartPointer] = AdcDiag_Pil_GetCnvData( t_u1HWUnit, t_u1VirtualChannel );
    }
}

/****************************************************************************************************/
/* Service name                 : AdcDiag_WaitForStatusRegister                                     */
/* Sync/Async                   : Synchronous                                                       */
/* Reentrancy                   : Non Reentrant                                                     */
/* Parameters (in)              :                                                                   */
/*      t_u1HWUnit              : HW Unit Number                                                    */
/*      t_u1ScanGroup           : Scan Group                                                        */
/*      t_u4TimeoutValue        : Accepted timeout                                                  */
/* Parameters (inout)           : None                                                              */
/* Parameters (out)             : None                                                              */
/* Return value                 : boolean                                                           */
/*      TRUE                    : Conversion finished with success                                  */
/*      FALSE                   : Timeout occurred                                                  */
/* Description                  : Wait for conversion to be finished or timeout to be reached       */
/*                              : Scan Group Status Register is polled to get the conversion status */
/* Limitation                   : This API shall not be used for scan groups where multicycle > 0   */
/****************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE) AdcDiag_WaitForStatusRegister(
    CONST(uint8, ADCDIAG_CONST)     t_u1HWUnit,
    CONST(uint8, ADCDIAG_CONST)     t_u1ScanGroup,
    CONST(uint32, ADCDIAG_CONST)    t_u4TimeoutValue
)
{
    VAR(uint32, ADCDIAG_VAR_NO_INIT)                t_u4CountVal;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)               t_u1IsConversionCompleted;

    t_u4CountVal = (uint32)ADCDIAG_ZERO;
    t_u1IsConversionCompleted = (boolean)TRUE;

    while ( AdcDiag_Pil_GetScanStatus( t_u1HWUnit, t_u1ScanGroup ) != (uint8)ADCDIAG_ZERO )
    {
        t_u4CountVal ++; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
        if ( t_u4CountVal == t_u4TimeoutValue )
        {
            t_u1IsConversionCompleted = (boolean)FALSE;
            break;
        }
    }
    return t_u1IsConversionCompleted;
}
/************************************************************************************************/
/* Service name                 : AdcDiag_ModuleReset                                           */
/* Sync/Async                   : Synchronous                                                   */
/* Reentrancy                   : Non Reentrant                                                 */
/* Parameters (in)              :                                                               */
/* t_u4ClocksUsed               : Which clock is supplied                                       */
/* Parameters (inout)           : None                                                          */
/* Parameters (out)             : None                                                          */
/* Return value                 : Std_ReturnType                                                */
/*      E_OK                    : Module reset executed with success                            */
/*      E_NOT_OK                : Timeout occurred                                              */
/* Description                  : Execute ADC module reset                                      */
/************************************************************************************************/
static FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_ModuleReset(
    CONST(uint32, ADCDIAG_CONST)    t_u4ClocksUsed
)
{
    VAR(Std_ReturnType, ADCDIAG_VAR_NO_INIT)     t_udErrorStatus;
    VAR(uint32, ADCDIAG_VAR_NO_INIT)    t_u4CountVal;
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)    t_u1IndexHWUnit;
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)    t_u1ScanGroup;
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)    t_u1NumberOfGroups;
    VAR(boolean, ADCDIAG_VAR_NO_INIT)   t_bHwUnitUsed;

    t_udErrorStatus = (Std_ReturnType)E_OK;

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B )
    t_u1NumberOfGroups = (uint8)ADC_HWUNIT_NUM;
#elif ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
    /* ADCJ2 cannot be reset, no need to re-enable the clock */
    t_u1NumberOfGroups = (uint8)ADC_HWUNIT_NUM - (uint8)1U;
#endif /* ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B ) - */

    for ( t_u1IndexHWUnit = (uint8)0U; t_u1IndexHWUnit < t_u1NumberOfGroups; t_u1IndexHWUnit++ ) {
        /* If the clock for ADC unit is not used, there is no conversion to finish */
        t_bHwUnitUsed = cstAdcDiag_UserConfig.cpstHWConfig[t_u1IndexHWUnit].cbHwUnitUsed;
        if ( t_bHwUnitUsed == (boolean)TRUE )
        {
            AdcDiag_Pil_StopAllScan( t_u1IndexHWUnit );
        }
    }

    for ( t_u1IndexHWUnit = (uint8)0U; t_u1IndexHWUnit < t_u1NumberOfGroups; t_u1IndexHWUnit++ ) {
        /* If the clock for ADC unit is not used, there is no conversion to finish */
        t_bHwUnitUsed = cstAdcDiag_UserConfig.cpstHWConfig[t_u1IndexHWUnit].cbHwUnitUsed;
        if ( t_bHwUnitUsed == (boolean)TRUE )
        {
            for ( t_u1ScanGroup = (uint8)0U; t_u1ScanGroup < (uint8)ADC_SG_NUM; t_u1ScanGroup++ ) {
                /* Reset timeout counter for each scan group */
                t_u4CountVal = (uint32)0U;
                /* Wait until all scan groups are stops */
                while ( AdcDiag_Pil_GetScanStatus( t_u1IndexHWUnit, t_u1ScanGroup ) != (uint8)0U ){
                    t_u4CountVal ++; /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
                    if ( t_u4CountVal == cstAdcDiag_UserConfig.cpstTimeoutVal->cu4ResetTimeout )
                    {
                        t_udErrorStatus = (Std_ReturnType)E_NOT_OK;
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
                        (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_TIMEOUT_STOP_AD_CONVERSION );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
                        break;
                    }
                }
            }
        }
    }
    /* If there was no timeout during the transition of the SG to Idle state following a force stop, reset ADC HW units if a clock signal is provided */
    if ( t_udErrorStatus == (Std_ReturnType)E_OK ) {
        t_udErrorStatus = AdcDiag_Pil_ModuleReset(cstAdcDiag_UserConfig.cpstTimeoutVal->cu4ResetTimeout, t_u4ClocksUsed );
        if ( t_udErrorStatus == (Std_ReturnType)E_NOT_OK )
        {
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
            (void)Det_ReportRuntimeError( u2ADCDIAG_MODULE_ID, u1ADCDIAG_INSTANCE_ID, u1ADCDIAG_AID_PRE_ADCINIT, u1ADCDIAG_E_TIMEOUT_MODULE_RESET );
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */
        }
    }

    return ( t_udErrorStatus );
}

/*******************************************************************************************************/
/* Service name                : AdcDiag_ReadClearErrorInfo                                            */
/* Sync/Async                  : Synchronous                                                           */
/* Reentrancy                  : Non Reentrant                                                         */
/* Parameters (in)             :                                                                       */
/* t_udAdcDiag_Pil_AdcErrorType: ADC Error Type                                                        */
/* Parameters (inout)          : None                                                                  */
/* Parameters (out)            :                                                                       */
/* t_pstAdcErrorInfo(Sync)     : Pointer to information errors                                         */
/* Return value                : None                                                                  */
/* Description                 : Provide the error informations                                        */
/*******************************************************************************************************/
static FUNC(void, ADCDIAG_CODE) AdcDiag_ReadClearErrorInfo(
	CONST(uint8, ADCDIAG_CONST)                   t_u1HWUnit,
	CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType,
    CONSTP2VAR(AdcDiag_ErrorInformationType, AUTOMATIC,  ADCDIAG_CONST)   t_pstAdcErrorInfo
)
{
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)                t_u1ErrorDetailedInfo;
    VAR(AdcDiag_ErrorId, ADCDIAG_VAR_NO_INIT)       t_udErrorId;

    t_u1ErrorDetailedInfo = AdcDiag_Pil_GetErrorData( t_u1HWUnit, t_udAdcDiag_Pil_AdcErrorType );
    t_udErrorId = ADCDIAG_E_OK;

    if ( t_u1ErrorDetailedInfo != u1ADCDIAG_PIL_NO_ERROR ) {

        switch(t_udAdcDiag_Pil_AdcErrorType)
        {
        case ADCDIAG_PIL_OVERLAPERROR:
            t_udErrorId = ADCDIAG_E_TRIGGER_OVERLAP;
            break;
        case ADCDIAG_PIL_PARITYPERROR:
            t_udErrorId = ADCDIAG_E_PARITY;
            break;
        case ADCDIAG_PIL_IDERROR:
            t_udErrorId = ADCDIAG_E_ID_ERROR;
            break;
        default:
            /* Do nothing */
            break;
        }
        AdcDiag_Pil_ClearErrorFlag( t_u1HWUnit, t_udAdcDiag_Pil_AdcErrorType );
    }

    t_pstAdcErrorInfo->udErrorId = t_udErrorId;
    t_pstAdcErrorInfo->u1ErrorDetailInfo = t_u1ErrorDetailedInfo;
}

#define ADCDIAG_STOP_SEC_CODE_GLOBAL
#include "AdcDiag_MemMap.h"

#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )

#define ADCDIAG_START_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"
/************************************************************************************************/
/* Service name         : AdcDiag_CheckErrorFlagAndNotify                                       */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*      t_u1HWUnit      : Hw Unit Number                                                        */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     : None                                                                  */
/* Return value         : None                                                                  */
/* Description          : Check the ADC interrupts flag and send the notification               */
/************************************************************************************************/
static FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_CheckErrorFlagAndNotify(
    CONST(uint8, ADCDIAG_CONST)        t_u1HWUnit
)
{
    VAR(boolean, ADCDIAG_VAR_NO_INIT)               t_u1ErrorFlag;

    t_u1ErrorFlag = AdcDiag_ProvideErrorFlag( t_u1HWUnit,ADCDIAG_PIL_OVERLAPERROR );

    if ( t_u1ErrorFlag == (boolean)FALSE ) {
            t_u1ErrorFlag = AdcDiag_ProvideErrorFlag( t_u1HWUnit,ADCDIAG_PIL_PARITYPERROR );
        }

    if ( t_u1ErrorFlag == (boolean)FALSE ) {
            t_u1ErrorFlag = AdcDiag_ProvideErrorFlag( t_u1HWUnit,ADCDIAG_PIL_IDERROR );
        }

    if ( t_u1ErrorFlag == (boolean)TRUE )
    {
        AdcDiag_ErrorNotification( t_u1HWUnit );
    }
}

/*******************************************************************************************************/
/* Service name                : AdcDiag_ProvideErrorFlag                                              */
/* Sync/Async                  : Synchronous                                                           */
/* Reentrancy                  : Non Reentrant                                                         */
/* Parameters (in)             :                                                                       */
/*     t_u1HWUnit              : Hw Unit Number                                                        */
/* t_udAdcDiag_Pil_AdcErrorType: ADC Error Type                                                        */
/* Parameters (inout)          : None                                                                  */
/* Parameters (out)            : None                                                                  */
/* Return value                : boolean                                                               */
/*      TRUE                   : Error flag is set                                                     */
/*      FALSE                  : No error flag                                                         */
/* Description                 : Provide the error flag                                                */
/*******************************************************************************************************/
static FUNC(boolean, ADCDIAG_CODE_FAST) AdcDiag_ProvideErrorFlag(
    CONST(uint8, ADCDIAG_CONST)                   t_u1HWUnit,
    CONST(AdcDiag_Pil_ErrorType, ADCDIAG_CONST)   t_udAdcDiag_Pil_AdcErrorType
)
{
    VAR(boolean, ADCDIAG_VAR_NO_INIT)               t_u1ErrorFlag;
    VAR(uint8,  ADCDIAG_VAR_NO_INIT)                t_u1ErrorDetailedInfo;

    t_u1ErrorFlag = (boolean)FALSE;

    t_u1ErrorDetailedInfo = AdcDiag_Pil_GetErrorData( t_u1HWUnit, t_udAdcDiag_Pil_AdcErrorType );
    if ( t_u1ErrorDetailedInfo != u1ADCDIAG_MAX_VALUE_ERROR_DATA ) {
        t_u1ErrorFlag = (boolean)TRUE;
    }
    return ( t_u1ErrorFlag );
}

#define ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */

/*------------------------------- End Of File ----------------------------------------------------*/
