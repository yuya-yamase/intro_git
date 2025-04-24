/* メインタスクコードに移管するまでの仮置き */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_GYRO_TASK_TIME              (1U)    /* 周期の時間指定(LSB:1ms) */

/* フロー */
/* SENSOR-ON端子 ⇒ Hi (GPIO端子処理)：別プロセスで実施 */
/* Wati t3 (SENSOR-ON High → I2Cアクセス可能までの時間)：Mcu_Dev_Pwron_Gyro_RegSetting()で監視 */
#define MCU_STEP_GYRO1_OVERALL_1        (1U)    /* Set Watchdog Timer (Gyro) */
#define MCU_STEP_GYRO1_OVERALL_2        (2U)    /* Set Watchdog Timer (Gセンサ) */
#define MCU_STEP_GYRO1_OVERALL_3        (3U)    /* Mode Change (Gセンサ) ON suspend mode ⇒ normal mode */
#define MCU_STEP_GYRO1_OVERALL_4        (4U)    /* Wait t11 (デバイス仕様：50ms (Gセンサのモード切替後wait時間)) */
#define MCU_STEP_GYRO1_OVERALL_5        (5U)    /* Setup Sensor (Gyro) */
#define MCU_STEP_GYRO1_OVERALL_6        (6U)    /* Self-Test (Gyro) */
#define MCU_STEP_GYRO1_OVERALL_7        (7U)    /* Setup Sensor (Gyro) */
#define MCU_STEP_GYRO1_OVERALL_8        (8U)    /* Setup Sensor (Gセンサ2) */
#define MCU_STEP_GYRO1_OVERALL_9        (9U)    /* Self-Test (Gセンサ) */
#define MCU_STEP_GYRO1_OVERALL_10       (10U)   /* Setup Sensor (Gセンサ1) */
#define MCU_STEP_GYRO1_OVERALL_11       (11U)   /* Mode Change (Gyro) OFF normal mode ⇒ suspend mode */
#define MCU_STEP_GYRO1_OVERALL_FIN      (12U)   

#define MCU_STEP_GYRO2_OVERALL_0        (0U)    /* 起動フロー(1)完了まで待機 */
#define MCU_STEP_GYRO2_OVERALL_1        (1U)    /* V33-Peri-ON監視 */
#define MCU_STEP_GYRO2_OVERALL_2        (2U)    /* Gセンサ 0x40に0xA8をWrite */
#define MCU_STEP_GYRO2_OVERALL_3        (3U)    /* Mode Change (Gyro) ON suspend mode ⇒ normal mode */
#define MCU_STEP_GYRO2_OVERALL_4        (4U)    /* Wait t10 (Gyroセンサsuspend mode時のwait time) */
#define MCU_STEP_GYRO2_OVERALL_FIN      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    gyro_Init( void );
void    gyro_main( void );

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern uint8    Mcu_OnStep_Gyro_1_OVRALL;
extern uint8    Mcu_OnStep_Gyro_2_OVRALL;