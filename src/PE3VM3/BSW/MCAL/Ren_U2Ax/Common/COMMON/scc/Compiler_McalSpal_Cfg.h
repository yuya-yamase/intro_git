/* Common-r04-31700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL Compiler Config Header																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef COMPILER_MCALSPAL_CFG_H
#define COMPILER_MCALSPAL_CFG_H

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
#define ADCDIAG_CODE /* Used for code */
#define ADCDIAG_CODE_FAST /* Used for code entering fast code memory segments */

#define ADC_CODE /* Used for code */
/* #define ADC_<CN>_CODE */ /* Used for callout codes */
#define ADC_CODE_FAST /* Used for code entering fast code memory segments */
#define ADC_CODE_SLOW /* Used for code entering a slow code memory segment */
#define ADC_CONST /* Used for global or static constants */
#define ADC_CALIB /* Use for calibration constants */
#define ADC_CONFIG_DATA /* Used for module configuration constants */
#define ADC_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ADC_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ADC_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ADC_APPL_DATA /* Used to reference application data (expected in RAM or ROM) passed through the API */
#define ADC_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define ADC_VAR_NO_INIT /* Used for all global or static variables */
#define ADC_VAR_CLEARED /* Used for all global or static variables */
#define ADC_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define ADC_VAR_INIT /* Used for all global or static variables */
#define ADC_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define ADC_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define ADC_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define ADC_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define ADC_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define ADC_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define ADC_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define ADC_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define ADC_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define ADC_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define ADC_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define ADC_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define ADC_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define ADC_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define ADC_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define ADC_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define ADC_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define ADC_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define ADC_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define DIO_CODE /* Used for code */
/* #define DIO_<CN>_CODE */ /* Used for callout codes */
#define DIO_CODE_FAST /* Used for code entering fast-code memory segments */
#define DIO_CODE_SLOW /* Used for code entering slow code memory segments */
#define DIO_CONST /* Used for global or static constants */
#define DIO_CALIB /* Use for calibration constants */
#define DIO_CONFIG_DATA /* Used for module configuration constants */
#define DIO_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define DIO_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define DIO_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define DIO_APPL_DATA /* Used to reference application data (expected to be in RAM or ROM) passed through the API */
#define DIO_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define DIO_VAR_NO_INIT /* Used for all global or static variables */
#define DIO_VAR_CLEARED /* Used for all global or static variables */
#define DIO_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define DIO_VAR_INIT /* Used for all global or static variables */
#define DIO_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define DIO_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define DIO_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define DIO_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define DIO_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define DIO_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define DIO_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define DIO_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define DIO_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define DIO_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define DIO_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define DIO_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define DIO_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define DIO_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define DIO_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define DIO_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define DIO_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define DIO_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define DIO_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define GPT_CODE /* Used for code */
/* #define GPT_<CN>_CODE */ /* Used for callout codes */
#define GPT_CODE_FAST /* Used for code entering fast code memory segments */
#define GPT_CODE_SLOW /* Used for code entering slow code memory segments */
#define GPT_CONST /* Used for global or static constants */
#define GPT_CALIB /* Use for calibration constants */
#define GPT_CONFIG_DATA /* Used for module setting constants */
#define GPT_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define GPT_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define GPT_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define GPT_APPL_DATA /* Used to reference application data (expected to be in RAM or ROM) passed through the API */
#define GPT_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define GPT_VAR_NO_INIT /* Used for all global or static variables */
#define GPT_VAR_CLEARED /* Used for all global or static variables */
#define GPT_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define GPT_VAR_INIT /* Used for all global or static variables */
#define GPT_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define GPT_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define GPT_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define GPT_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define GPT_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define GPT_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define GPT_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define GPT_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define GPT_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define GPT_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define GPT_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define GPT_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define GPT_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define GPT_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define GPT_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define GPT_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define GPT_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define GPT_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define GPT_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define ICU_CODE /* used for code */
/* #define ICU_<CN>_CODE */ /* Used for callout codes */
#define ICU_CODE_FAST /* Used for code entering fast-code memory segments */
#define ICU_CODE_SLOW /* Used for code entering slow code memory segments */
#define ICU_CONST /* Used for global or static constants */
#define ICU_CALIB /* Use for calibration constants */
#define ICU_CONFIG_DATA /* Used for module configuration constants */
#define ICU_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ICU_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ICU_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define ICU_APPL_DATA /* Used to reference application data (expected in RAM or ROM) passed via API */
#define ICU_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed via API */
#define ICU_VAR_NO_INIT /* Used for all global or static variables */
#define ICU_VAR_CLEARED /* Used for all global or static variables */
#define ICU_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define ICU_VAR_INIT /* Used for all global or static variables */
#define ICU_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define ICU_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define ICU_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define ICU_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define ICU_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define ICU_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define ICU_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define ICU_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define ICU_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define ICU_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define ICU_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define ICU_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define ICU_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define ICU_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define ICU_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define ICU_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define ICU_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define ICU_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define ICU_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define MCU_CODE /* used for code */
/* #define MCU_<CN>_CODE */ /* Used for callout codes */
#define MCU_CODE_FAST /* Used for code entering fast-code memory segments */
#define MCU_CODE_SLOW /* Used for code entering slow code memory segments */
#define MCU_CONST /* Used for global or static constants */
#define MCU_CALIB /* Use for calibration constants */
#define MCU_CONFIG_DATA /* Used for module configuration constants */
#define MCU_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define MCU_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define MCU_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define MCU_APPL_DATA /* Used to reference application data (expected to be in RAM or ROM) passed through the API */
#define MCU_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed via API */
#define MCU_VAR_NO_INIT /* Used for all global or static variables */
#define MCU_VAR_CLEARED /* Used for all global or static variables */
#define MCU_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define MCU_VAR_INIT /* Used for all global or static variables */
#define MCU_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define MCU_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define MCU_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define MCU_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define MCU_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define MCU_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define MCU_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define MCU_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define MCU_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define MCU_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define MCU_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define MCU_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define MCU_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define MCU_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define MCU_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define MCU_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define MCU_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define MCU_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define MCU_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define PORT_CODE /* Used for code */
/* #define PORT_<CN>_CODE */ /* Used for callout codes */
#define PORT_CODE_FAST /* Used for code entering fast code memory segments */
#define PORT_CODE_SLOW /* Used for code entering a slow code memory segment */
#define PORT_CONST /* Used for global or static constants */
#define PORT_CALIB /* Use for calibration constants */
#define PORT_CONFIG_DATA /* Used for module configuration constants */
#define PORT_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PORT_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PORT_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PORT_APPL_DATA /* Used to reference application data (expected to be in RAM or ROM) passed through the API */
#define PORT_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define PORT_VAR_NO_INIT /* Used for all global or static variables */
#define PORT_VAR_CLEARED /* Used for all global or static variables */
#define PORT_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define PORT_VAR_INIT /* Used for all global or static variables */
#define PORT_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define PORT_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define PORT_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define PORT_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define PORT_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define PORT_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define PORT_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define PORT_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define PORT_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define PORT_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define PORT_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define PORT_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define PORT_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define PORT_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define PORT_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define PORT_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define PORT_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define PORT_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define PORT_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define PWM_CODE /* Used for code */
/* #define PWM_<CN>_CODE */ /* Used for callout codes */
#define PWM_CODE_FAST /* Used for code entering fast code memory segments */
#define PWM_CODE_SLOW /* Used for code entering slow code memory segments */
#define PWM_CONST /* Used for global or static constants */
#define PWM_CALIB /* Use for calibration constants */
#define PWM_CONFIG_DATA /* Used for module configuration constants */
#define PWM_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PWM_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PWM_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define PWM_APPL_DATA /* Used to reference application data (expected in RAM or ROM) passed through the API */
#define PWM_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define PWM_VAR_NO_INIT /* Used for all global or static variables */
#define PWM_VAR_CLEARED /* Used for all global or static variables */
#define PWM_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define PWM_VAR_INIT /* Used for all global or static variables */
#define PWM_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define PWM_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define PWM_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define PWM_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define PWM_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define PWM_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define PWM_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define PWM_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define PWM_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define PWM_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define PWM_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define PWM_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define PWM_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define PWM_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define PWM_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define PWM_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define PWM_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define PWM_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define PWM_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define SPI_CODE /* used for code */
/* #define SPI_<CN>_CODE */ /* Used for callout codes */
#define SPI_CODE_FAST /* Used for code entering fast-code memory segments */
#define SPI_CODE_SLOW /* Used for code entering a slow code memory segment */
#define SPI_CONST /* Used for global or static constants */
#define SPI_CALIB /* Use for calibration constants */
#define SPI_CONFIG_DATA /* Used for module configuration constants */
#define SPI_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define SPI_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define SPI_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define SPI_APPL_DATA /* Used to reference application data (expected in RAM or ROM) passed through the API */
#define SPI_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define SPI_VAR_NO_INIT /* Used for all global or static variables */
#define SPI_VAR_CLEARED /* Used for all global or static variables */
#define SPI_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define SPI_VAR_INIT /* Used for all global or static variables */
#define SPI_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define SPI_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define SPI_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define SPI_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define SPI_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define SPI_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define SPI_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define SPI_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define SPI_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define SPI_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define SPI_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define SPI_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define SPI_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define SPI_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define SPI_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define SPI_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define SPI_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define SPI_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define SPI_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define WDG_CODE /* Used for code */
/* #define WDG_<CN>_CODE */ /* Used for callout codes */
#define WDG_CODE_FAST /* Used for code entering fast-code memory segments */
#define WDG_CODE_SLOW /* Used for code entering slow code memory segments */
#define WDG_CONST /* Used for global or static constants */
#define WDG_CALIB /* Use for calibration constants */
#define WDG_CONFIG_DATA /* Used for module configuration constants */
#define WDG_CONST_SAVED_RECOVERY_ZONE8 /* Used for ROM buffer of variables stored in non-volatile memory */
#define WDG_CONST_SAVED_RECOVERY_ZONE16 /* Used for ROM buffer of variables stored in non-volatile memory */
#define WDG_CONST_SAVED_RECOVERY_ZONE32 /* Used for ROM buffer of variables stored in non-volatile memory */
#define WDG_APPL_DATA /* Used to reference application data (expected to be in RAM or ROM) passed through the API */
#define WDG_APPL_CONST /* Used to reference application constants (For example, it is expected to be reliably present in ROMs such as the Init function pointer) passed through the API */
#define WDG_VAR_NO_INIT /* Used for all global or static variables */
#define WDG_VAR_CLEARED /* Used for all global or static variables */
#define WDG_VAR_POWER_ON_CLEARED /* Used for all global or static variables */
#define WDG_VAR_INIT /* Used for all global or static variables */
#define WDG_VAR_POWER_ON_INIT /* Used for all global or static variables */
#define WDG_VAR_FAST_NO_INIT /* Used for all frequently accessed global or static variables */
#define WDG_VAR_FAST_CLEARED /* Used for all frequently accessed global or static variables */
#define WDG_VAR_FAST_POWER_ON_CLEARED /* Used for all frequently accessed global or static variables */
#define WDG_VAR_FAST_INIT /* Used for all frequently accessed global or static variables */
#define WDG_VAR_FAST_POWER_ON_INIT /* Used for all frequently accessed global or static variables */
#define WDG_VAR_SLOW_NO_INIT /* Used for all infrequently accessed global or static variables */
#define WDG_VAR_SLOW_CLEARED /* Used for all infrequently accessed global or static variables */
#define WDG_VAR_SLOW_POWER_ON_CLEARED /* Used for all infrequently accessed global or static variables */
#define WDG_VAR_SLOW_INIT /* Used for all infrequently accessed global or static variables */
#define WDG_VAR_SLOW_POWER_ON_INIT /* Used for all infrequently accessed global or static variables */
#define WDG_INTERNAL_VAR_NO_INIT /* Used for global or static variables accessible from calibration tools */
#define WDG_INTERNAL_VAR_CLEARED /* Used for global or static variables accessible from calibration tools */
#define WDG_INTERNAL_VAR_POWER_ON_CLEARED /* Used for global or static variables accessible from calibration tools */
#define WDG_INTERNAL_VAR_INIT /* Used for global or static variables accessible from calibration tools */
#define WDG_INTERNAL_VAR_POWER_ON_INIT /* Used for global or static variables accessible from calibration tools */
#define WDG_VAR_SAVED_ZONE8 /* Used for RAM buffer of variables stored in non-volatile memory */
#define WDG_VAR_SAVED_ZONE16 /* Used for RAM buffer of variables stored in non-volatile memory */
#define WDG_VAR_SAVED_ZONE32 /* Used for RAM buffer of variables stored in non-volatile memory */



#define MCALCOMMON_CODE /* Used for code */
#define MCALCOMMON_CODE_VAR_NO_INIT /* Used for all global or static variables */

#endif /* COMPILER_MCALSPAL_CFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
