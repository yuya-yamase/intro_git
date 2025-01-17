/* ADCDIAG-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*      ADC DIAG Driver : Upper layer for RH850U2A/U2B                                          */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
#ifndef ADCDIAG_H
#define ADCDIAG_H

/*==============================================================================================*/
/* include files                                                                                */
/*==============================================================================================*/
#include "AdcDiag_Cfg.h"
/*==============================================================================================*/
/* defines                                                                                      */
/*==============================================================================================*/
#if ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON )
/* Module ID */
#define	u2ADCDIAG_MODULE_ID								((uint16)123U)

/* The identifier of the index based instance of a module */
#define	u1ADCDIAG_INSTANCE_ID							((uint8)(0U))			/* Multi core not support				*/

/* Api ID :API Service ID */
#define u1ADCDIAG_AID_PRE_ADCINIT						((uint8)0xF0U)				/* AdcDiag_PreAdcInit					*/
#define u1ADCDIAG_AID_WIRING_BREAK_DETECTION			((uint8)0xF1U)				/* AdcDiag_StartWiringBreakDetection	*/
#define u1ADCDIAG_AID_AD_CORE							((uint8)0xF2U)				/* AdcDiag_StartAdCoreSelfDiag			*/
#define u1ADCDIAG_AID_PIN_LEVEL							((uint8)0xF3U)				/* AdcDiag_StartPinLevel				*/

/* Error ID:ID of detected runtime error */
#define u1ADCDIAG_E_TIMEOUT_SELF_DIAG_WIRING_BREAK_MODE1						((uint8)0xF0U)
#define u1ADCDIAG_E_TIMEOUT_SELF_DIAG_WIRING_BREAK_MODE2						((uint8)0xF1U)
#define u1ADCDIAG_E_TIMEOUT_SELF_DIAG_TH										((uint8)0xF2U)
#define u1ADCDIAG_E_TIMEOUT_MODULE_RESET										((uint8)0xF3U)
#define u1ADCDIAG_E_TIMEOUT_STOP_AD_CONVERSION								    ((uint8)0xF4U)
#define u1ADCDIAG_E_TIMEOUT_WIRING_BREAK_MODE1									((uint8)0xF5U)
#define u1ADCDIAG_E_TIMEOUT_WIRING_BREAK_MODE2									((uint8)0xF6U)
#define u1ADCDIAG_E_TIMEOUT_AD_CORE												((uint8)0xF7U)
#define u1ADCDIAG_E_TIMEOUT_PIN_LEVEL											((uint8)0xF8U)
#define u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_WIRING_BREAK_MODE1					((uint8)0xF9U)
#define u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_WIRING_BREAK_MODE2					((uint8)0xFAU)
#define u1ADCDIAG_E_OUTSIDE_RANGE_SELF_DIAG_TH									((uint8)0xFBU)
#endif /* ( ADCDIAG_CFG_DET_REPORT_RUNTIMEERROR == STD_ON ) - */

/* Voltage values for A/Dcore Self-Diagnosis Function */
#define u1ADCDIAG_ADCORE_VREFH_1           					((uint8)0x10U)
#define u1ADCDIAG_ADCORE_VREFH_3_4         					((uint8)0x0CU)
#define u1ADCDIAG_ADCORE_VREFH_1_2        					((uint8)0x08U)
#define u1ADCDIAG_ADCORE_VREFH_1_4         					((uint8)0x04U)
#define u1ADCDIAG_ADCORE_VREFH_0           					((uint8)0x00U)

/* Number of total accepted ranges value combination for Wiring Break Detection and T&H */
#define u1ADCDIAG_WIRING_BREAK_TOTAL_COMBINATION   			((uint8)2U)

/*==============================================================================================*/
/* data types / structs / unions / macros                                                       */
/*==============================================================================================*/
/* All AD Error used in AdcDiag*/
typedef enum {
    ADCDIAG_E_OK,
    ADCDIAG_E_TRIGGER_OVERLAP,
    ADCDIAG_E_ID_ERROR,
    ADCDIAG_E_PARITY,
    ADCDIAG_E_NOK
} AdcDiag_ErrorId;

/* Enumeration for all Diagnostic Modes used */
typedef enum {
    ADCDIAG_WIRING_BREAK_DETECTION_MODE1,
    ADCDIAG_WIRING_BREAK_DETECTION_MODE2,
    ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE1,
    ADCDIAG_SELF_DIAG_WIRING_BREAK_DETECTION_MODE2,
    ADCDIAG_SELF_DIAG_TH,
    ADCDIAG_PIN_LEVEL,
    ADCDIAG_AD_CORE_SELF_DIAG
} AdcDiag_DiagType;

/* Structure used to store detail information about ADC errors */
typedef struct {
    AdcDiag_ErrorId             udErrorId;
    uint8                       u1ErrorDetailInfo;
} AdcDiag_ErrorInformationType;

typedef void (* AdcDiag_NotifFunc)(uint8 t_u1Arg);

/* Group Configuration */
typedef struct {
    const uint8                         cu1HWUnit;                                  /* HW Unit                                      */
    const uint8                         cu1SG;                                      /* Scan Group                                   */
    const uint8                         cu1PhysicalChannelsNo;                      /* Number of physical channels from group       */
    const uint8*                        cstPhysicalChannels;                        /* Physical Channels                            */
    const uint8                         cu1StartChannel;                            /* Start Channel Pointer                        */
    const uint8                         cu1StopChannel;                             /* Stop Channel Pointer                         */
    const AdcDiag_DiagType              cudDiagType;                                /* Diagnostic Type				                */
} AdcDiag_GroupConfigType;

typedef struct {
    const uint8                         cu1DataFormat;							    /* Data Format */
#if ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON )
    AdcDiag_NotifFunc                   pvdNotifyFunc;                              /* Notification */
#endif /* ( ADCDIAG_CFG_ERR_NOTIF_CAPABILITY == STD_ON ) - */
    const boolean                       cbHwUnitUsed;							    /* Hw Unit Used */
} AdcDiag_HWConfigType;

/* Structure used to store Voltage Levels used in the TH diagnostics procedure */
typedef struct {
    const uint8                     cu1AtStart;
    const uint8                     cu1AfterStart;
} AdcDiag_LevelVoltage;

/* Structure used to store Timeout values */
typedef struct {
    const uint32                    cu4SelfDiagWiringBreakTimeout;
    const uint32                    cu4SelfDiagThTimeout;
    const uint32                    cu4SelfDiagTh_Vch0Timeout;
    const uint32                    cu4WiringBreakTimeout;
    const uint32                    cu4PinLvlTimeout;
    const uint32                    cu4AdCoreTimeout;
    const uint32                    cu4ResetTimeout;
} AdcDiag_TimeoutValue;

typedef struct {
    const AdcDiag_GroupConfigType*          cpstGroupConfig;
    const AdcDiag_HWConfigType*             cpstHWConfig;
    const AdcDiag_LevelVoltage*             cpstVoltLlvComb;
    const uint16                            (*cpstWBRangeVal)[u1ADCDIAG_WIRING_BREAK_TOTAL_COMBINATION];
    const AdcDiag_TimeoutValue*             cpstTimeoutVal;
} AdcDiag_ConfigType;
/*==============================================================================================*/
/* external symbols                                                                             */
/*==============================================================================================*/
/* AdcDiag Configuration */
extern CONST(AdcDiag_ConfigType, ADCDIAG_CONST) cstAdcDiag_UserConfig;

/*==============================================================================================*/
/* functions                                                                                    */
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* Public API                                                                                   */
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions                                                                                */
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
FUNC(Std_ReturnType, ADCDIAG_CODE) AdcDiag_PreAdcInit( void );

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
FUNC(void, ADCDIAG_CODE) AdcDiag_Init( void );

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
);

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
);

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
);

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
);

/************************************************************************************************/
/* Service name         : AdcDiag_ReadDataRegister                                              */
/* Sync/Async           : Synchronous                                                           */
/* Reentrancy           : Non Reentrant                                                         */
/* Parameters (in)      :                                                                       */
/*    t_u1HWUnit        : Hw Unit Number.                                                       */
/*    t_u1VirtualChannel: Virtual channel                                                       */
/* Parameters (inout)   : None                                                                  */
/* Parameters (out)     :                                                                       */
/*      DataBufferPtr   : Pointer to result Data Buffer                                         */
/* Return value         : None                                                                  */
/* Description          : Get the conversion results                                            */
/************************************************************************************************/
#define AdcDiag_ReadDataRegister(t_u1HWUnit, t_u1VirtualChannel) ( AdcDiag_Pil_GetCnvData( t_u1HWUnit, t_u1VirtualChannel ))

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
);
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
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit0_Err(void);
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT0_ERR ) ) */

#if ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT1_ERR ) )
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit1_Err(void);
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT1_ERR ) ) */

#if ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT2_ERR ) )
FUNC(void, ADCDIAG_CODE_FAST) AdcDiag_Intrpt_HWUnit2_Err(void);
#endif /* ( defined ( ADCDIAG_CFG_USE_ISR_ADC_HWUNIT2_ERR ) ) */

#define ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#include "AdcDiag_MemMap.h"

#endif /* ADCDIAG_H */

/*------------------------------- End Of File ----------------------------------------------------*/
