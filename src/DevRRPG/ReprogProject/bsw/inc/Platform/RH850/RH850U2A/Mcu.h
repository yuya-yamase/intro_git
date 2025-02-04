/* Mcu_h */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Mcu/HEADER                                       */
/******************************************************************************/
#ifndef MCU_H
#define MCU_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Clock Type */
#define MCU_CLOCKTYPE_CLK_CPU       ((U2)0x0000U)           /* Clock Type:CLK_CPU           */

/* Clock Setting ID */
#define MCU_CLOCKSETTING_ID         (0U)                    /* Clock Setting ID             */

/* Reset Type */
#define MCU_RESETTYPE_SW            ((U1)0x00U)             /* Reset Type:Software System Reset */

/* Clock Device Type */
#define MCU_DEVCLOCKTYPE_CLK_RLIN   ((U1)0x00U)             /* Clock Device Type:CLK_RLIN   */
#define MCU_DEVCLOCKTYPE_CLK_ADC    ((U1)0x01U)             /* Clock Device Type:CLK_ADC    */
#define MCU_DEVCLOCKTYPE_CLK_MSPI   ((U1)0x02U)             /* Clock Device Type:CLK_MSPI   */
#define MCU_DEVCLOCKTYPE_CLK_WDT    ((U1)0x03U)             /* Clock Device Type:CLK_WDT    */
#define MCU_DEVCLOCKTYPE_CLKA_WDT   ((U1)0x04U)             /* Clock Device Type:CLKA_WDT   */
#define MCU_DEVCLOCKTYPE_CLKA_TAUJ  ((U1)0x05U)             /* Clock Device Type:CLKA_TAUJ  */
#define MCU_DEVCLOCKTYPE_CLKA_RTCA  ((U1)0x06U)             /* Clock Device Type:CLKA_RTCA  */
#define MCU_DEVCLOCKTYPE_CLKA_ADC   ((U1)0x07U)             /* Clock Device Type:CLKA_ADCA  */
#define MCU_DEVCLOCKTYPE_EXTCLK0O   ((U1)0x08U)             /* Clock Device Type:EXTCLK0O   */
#define MCU_DEVCLOCKTYPE_EXTCLK1O   ((U1)0x09U)             /* Clock Device Type:EXTCLK1O   */


/* Source Clock Type */
#define MCU_SRCCLKTYPE_CLK_RLIN_CLK_MOSC      ((U1)0x00U)   /* Source Clock Type for CLK_RLIN:MainOSC    */
#define MCU_SRCCLKTYPE_CLK_RLIN_CLK_MOSC4     ((U1)0x02U)   /* Source Clock Type for CLK_RLIN:MainOSC4   */
#define MCU_SRCCLKTYPE_CLK_RLIN_CLK_MOSC8     ((U1)0x03U)   /* Source Clock Type for CLK_RLIN:MainOSC8   */
#define MCU_SRCCLKTYPE_CLK_RLIN_CLK_HSB       ((U1)0x01U)   /* Source Clock Type for CLK_RLIN:HSB        */
#define MCU_SRCCLKTYPE_CLK_ADC_CLK_LSB        ((U1)0x00U)   /* Source Clock Type for CLK_ADC: LSB        */
#define MCU_SRCCLKTYPE_CLK_ADC_CLK_LSB2       ((U1)0x01U)   /* Source Clock Type for CLK_ADC: LSB2       */
#define MCU_SRCCLKTYPE_CLK_MSPI_CLK_MOSC      ((U1)0x00U)   /* Source Clock Type for CLK_MSPI:MainOSC    */
#define MCU_SRCCLKTYPE_CLK_MSPI_CLK_HSB       ((U1)0x01U)   /* Source Clock Type for CLK_MSPI:HSB        */
#define MCU_SRCCLKTYPE_CLK_WDT_CLK_HSIOSC20   ((U1)0x00U)   /* Source Clock Type for CLK_WDT: HSIOSC20   */
#define MCU_SRCCLKTYPE_CLK_WDT_CLK_HSIOSC640  ((U1)0x01U)   /* Source Clock Type for CLK_WDT: HSIOSC640  */
#define MCU_SRCCLKTYPE_CLKA_WDT_CLK_LSIOSC    ((U1)0x00U)   /* Source Clock Type for CLKA_WDT:LSIOSC     */
#define MCU_SRCCLKTYPE_CLKA_WDT_CLK_LSIOSC128 ((U1)0x01U)   /* Source Clock Type for CLKA_WDT:LSIOSC128  */
#define MCU_SRCCLKTYPE_CLKA_TAUJ_CLK_MOSC     ((U1)0x02U)   /* Source Clock Type for CLKA_TAUJ:MainOSC   */
#define MCU_SRCCLKTYPE_CLKA_TAUJ_CLK_HSIOSC20 ((U1)0x01U)   /* Source Clock Type for CLKA_TAUJ:HSIOSC20  */
#define MCU_SRCCLKTYPE_CLKA_TAUJ_CLK_LSIOSC   ((U1)0x00U)   /* Source Clock Type for CLKA_TAUJ:LSIOSC    */
#define MCU_SRCCLKTYPE_CLKA_TAUJ_CLK_HSB      ((U1)0x03U)   /* Source Clock Type for CLKA_TAUJ:HSB       */
#define MCU_SRCCLKTYPE_CLKA_RTCA_CLK_MOSC16   ((U1)0x00U)   /* Source Clock Type for CLKA_RTCA:MainOSC16 */
#define MCU_SRCCLKTYPE_CLKA_RTCA_CLK_LSIOSC   ((U1)0x01U)   /* Source Clock Type for CLKA_RTCA:LSIOSC    */
#define MCU_SRCCLKTYPE_CLKA_ADC_CLK_MOSC      ((U1)0x00U)   /* Source Clock Type for CLKA_ADC :MainOSC   */
#define MCU_SRCCLKTYPE_CLKA_ADC_CLK_HSIOSC20  ((U1)0x01U)   /* Source Clock Type for CLKA_ADC :HSIOSC20  */
#define MCU_SRCCLKTYPE_CLKA_ADC_CLK_LSB       ((U1)0x02U)   /* Source Clock Type for CLKA_ADC :LSB       */
#define MCU_SRCCLKTYPE_EXTCLKO_CLK_MOSC       ((U1)0x00U)   /* Source Clock Type for EXTCLKO  :MainOSC   */
#define MCU_SRCCLKTYPE_EXTCLKO_CLK_HSIOSC20   ((U1)0x04U)   /* Source Clock Type for EXTCLKO  :HSIOSC20  */
#define MCU_SRCCLKTYPE_EXTCLKO_CLK_LSIOSC     ((U1)0x03U)   /* Source Clock Type for EXTCLKO  :LSIOSC    */
#define MCU_SRCCLKTYPE_EXTCLKO_CLK_HSB        ((U1)0x01U)   /* Source Clock Type for EXTCLKO  :HSB       */

/* Clock Divider Type */
#define MCU_CLKDIVTYPE_CLK_RLIN_DIV_1       ((U2)0x0000U)   /* Clock Divider Type for CLK_RLIN :Divide by 1 */
#define MCU_CLKDIVTYPE_CLK_ADC_DIV_1        ((U2)0x0000U)   /* Clock Divider Type for CLK_ADC  :Divide by 1 */
#define MCU_CLKDIVTYPE_CLK_MSPI_DIV_1       ((U2)0x0000U)   /* Clock Divider Type for CLK_MSPI :Divide by 1 */
#define MCU_CLKDIVTYPE_CLK_WDT_DIV_1        ((U2)0x0000U)   /* Clock Divider Type for CLK_WDT  :Divide by 1 */
#define MCU_CLKDIVTYPE_CLKA_WDT_DIV_1       ((U2)0x0000U)   /* Clock Divider Type for CLKA_WDT :Divide by 1 */
#define MCU_CLKDIVTYPE_CLKA_TAUJ_DIV_1      ((U2)0x0000U)   /* Clock Divider Type for CLKA_TAUJ:Divide by 1 */
#define MCU_CLKDIVTYPE_CLKA_RTCA_DIV_1      ((U2)0x0000U)   /* Clock Divider Type for CLKA_RTCA:Divide by 1 */
#define MCU_CLKDIVTYPE_CLKA_ADC_DIV_1       ((U2)0x0001U)   /* Clock Divider Type for CLKA_ADC :Divide by 1 */
#define MCU_CLKDIVTYPE_CLKA_ADC_DIV_2       ((U2)0x0000U)   /* Clock Divider Type for CLKA_ADC :Divide by 2 */
#define MCU_CLKDIVTYPE_EXTCLKO_DISABLE      ((U2)0x0000U)   /* Clock Divider Type for EXTCLKnO :Disable     */

/* Module ID */
#define MCU_MODULE_ID               ((U2)0x0003U)           /* Module ID for MCU Driver     */

/* API ID */
#define MCU_API_ID_INIT             ((U1)0x00U)             /* API ID for Mcu_Init          */
#define MCU_API_ID_GETPLLSTATUS     ((U1)0x01U)             /* API ID for Mcu_GetPllStatus  */
#define MCU_API_ID_DEINIT           ((U1)0x02U)             /* API ID for Mcu_DeInit        */

/* Error Code for MCU Driver */
#define MCU_E_CONFIG                ((U1)0x01U)             /* Configuration Error          */
#define MCU_E_UNINIT                ((U1)0x02U)             /* Non-initialization Error     */
#define MCU_E_INIT_FAILURE          ((U1)0x03U)             /* Mcu_Init Error               */
#define MCU_E_DEINIT_FAILURE        ((U1)0x04U)             /* Mcu_DeInit Error             */

/* MCU PLL Status Type */
#define MCU_PLL_LOCKED              ((U1)0U)                /* PLL is locked                */
#define MCU_PLL_UNLOCKED            ((U1)1U)                /* PLL is unlocked              */
#define MCU_PLL_STATUS_UNDEFINED    ((U1)2U)                /* PLL Status is unknown        */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* MCU Clock Type */
typedef     U4                  Mcu_ClockType;

/* MCU PLL Status Type */
typedef     U1                  Mcu_PllStatusType;

/* MCU Clock Common Configuration Type */
typedef struct
{
    U2      ExtOscillatorClock;                         /* External Oscillator Clock Frequency[MHz] */
    U1      PllUse;                                     /* Use of PLL                               */
} Mcu_ClockCommonConfigType;

/* MCU Clock Information Configuration Type */
typedef struct
{
    U2      ClockType;                                  /* Clock Type           */
    U2      Clock;                                      /* Clock Frequency[MHz] */
} Mcu_ClockInfoConfigType;

/* MCU Clock Setting Configuration Type */
typedef struct
{
    U1                              ClockSettingNum;    /* Number of Clock Setting                                    */
    const Mcu_ClockInfoConfigType*  ClockInfo;          /* Start Address of MCU Clock Information Configuration Table */
} Mcu_ClockSettingConfigType;

/* MCU Reset Setting Configuration Type */
typedef struct
{
    U1      ResetType;                                  /* Reset Type   */
} Mcu_ResetSettingConfigType;

/* MCU Configuration Type */
typedef struct
{
    const Mcu_ClockCommonConfigType*    ClockCommon;    /* Start Address of MCU Clock Common Configuration Table      */
    const Mcu_ClockSettingConfigType*   ClockSetting;   /* Start Address of MCU Clock Setting Configuration Table     */
    const Mcu_ResetSettingConfigType*   ResetSetting;   /* Start Address of MCU Reset Setting Configuration Table     */
} Mcu_ConfigType;

/* [Device Individuality Config] MCU Device Clock Information Configuration Type */
typedef struct
{
    U1      DevClockType;                               /* Clock Type           */
    U1      SourceClockType;                            /* Source Clock Type    */
    U2      ClockDivType;                               /* Clock Divider Type   */
} Mcu_DevClockInfoConfigType;

/* [Device Individuality Config] MCU Device Clock Setting Configuration Type */
typedef struct
{
    U1     DevClockSettingNum;                          /* Number of Clock Setting                                    */
    const  Mcu_DevClockInfoConfigType* DevClockInfo;    /* Start Address of MCU ClockInformation Configuration Table  */
} Mcu_DevClockSettingConfigType;

/* [Device Individuality Config] MCU Device Individuality Configuration Type */
typedef struct
{
    const Mcu_DevClockSettingConfigType* DevClockSetting; /* Start Address of MCU Clock Setting Configuration Table   */
} Mcu_DevConfigType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#pragma ghs callmode = far
#pragma ghs section text = ".P_MCU"
void                Mcu_Init(const Mcu_ConfigType* Config);
Std_ReturnType      Mcu_InitClock(Mcu_ClockType ClockSetting);
Mcu_PllStatusType   Mcu_GetPllStatus(void);
Std_ReturnType      Mcu_DistributePllClock(void);
void                Mcu_PerformReset(void);
void                Mcu_DeInit(void);
#pragma ghs section text = default
#pragma ghs callmode = default


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_MCU"
extern const Mcu_ConfigType MCU_CFG_DATA;
extern const Mcu_DevConfigType MCU_DEVCFG_DATA;
#pragma ghs section rosdata = default


#endif  /* MCU_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/04/30 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

