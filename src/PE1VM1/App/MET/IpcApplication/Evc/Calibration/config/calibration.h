/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CALIBRATION                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CALIBRATION_H
#define CALIBRATION_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CALIBRATION_H_MAJOR                        (1)
#define CALIBRATION_H_MINOR                        (1)
#define CALIBRATION_H_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "calibration_def.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CALIB_MCUID0001_MIN                         (48U)            /* MCU Software version No.1 MIN                                */
#define CALIB_MCUID0001_MAX                         (90U)            /* MCU Software version No.1 MAX                                */
#define CALIB_MCUID0002_MIN                         (48U)            /* MCU Software version No.2 MIN                                */
#define CALIB_MCUID0002_MAX                         (90U)            /* MCU Software version No.2 MAX                                */
#define CALIB_MCUID0003_MIN                         (48U)            /* MCU Software version No.3 MIN                                */
#define CALIB_MCUID0003_MAX                         (90U)            /* MCU Software version No.3 MAX                                */
#define CALIB_MCUID0004_MIN                         (48U)            /* MCU Software version No.4 MIN                                */
#define CALIB_MCUID0004_MAX                         (90U)            /* MCU Software version No.4 MAX                                */
#define CALIB_MCUID0005_MIN                         (48U)            /* MCU Software version No.5 MIN                                */
#define CALIB_MCUID0005_MAX                         (90U)            /* MCU Software version No.5 MAX                                */
#define CALIB_MCUID0006_MIN                         (48U)            /* MCU Software version No.6 MIN                                */
#define CALIB_MCUID0006_MAX                         (90U)            /* MCU Software version No.6 MAX                                */
#define CALIB_MCUID0007_MIN                         (48U)            /* MCU Software version No.7 MIN                                */
#define CALIB_MCUID0007_MAX                         (90U)            /* MCU Software version No.7 MAX                                */
#define CALIB_MCUID0008_MIN                         (48U)            /* MCU Software version No.8 MIN                                */
#define CALIB_MCUID0008_MAX                         (90U)            /* MCU Software version No.8 MAX                                */
#define CALIB_MCUID0009_MIN                         (48U)            /* MCU Software version No.9 MIN                                */
#define CALIB_MCUID0009_MAX                         (90U)            /* MCU Software version No.9 MAX                                */
#define CALIB_MCUID0010_MIN                         (48U)            /* MCU Software version No.10 MIN                               */
#define CALIB_MCUID0010_MAX                         (90U)            /* MCU Software version No.10 MAX                               */
#define CALIB_MCUID0011_MIN                         (33U)            /* MCU Software version No.11 MIN                               */
#define CALIB_MCUID0011_MAX                         (90U)            /* MCU Software version No.11 MAX                               */
#define CALIB_MCUID0012_MIN                         (33U)            /* MCU Software version No.12 MIN                               */
#define CALIB_MCUID0012_MAX                         (90U)            /* MCU Software version No.12 MAX                               */
#define CALIB_MCUID0013_TO_MCUID0020_MIN            (32U)            /* Speed Meter ID MIN                                           */
#define CALIB_MCUID0013_TO_MCUID0020_MAX            (90U)            /* Speed Meter ID MAX                                           */
#define CALIB_MCUID0021_MIN                         (0U)             /* HUD MAIN Hard SW MIN                                         */
#define CALIB_MCUID0021_MAX                         (1U)             /* HUD MAIN Hard SW MAX                                         */
#define CALIB_MCUID0022_MIN                         (0U)             /* Fuel Main Sender MIN                                         */
#define CALIB_MCUID0022_MAX                         (1U)             /* Fuel Main Sender MAX                                         */
#define CALIB_MCUID0023_NUM                         (5U)             /* Display Type NUM                                             */
#define CALIB_MCUID0023_NON                         (0U)             /* Display NON                                                  */
#define CALIB_MCUID0023_AIS                         (1U)             /* Display Ais                                                  */
#define CALIB_MCUID0023_7INCH                       (2U)             /* Display 7inch                                                */
#define CALIB_MCUID0023_12INCH                      (3U)             /* Display 12.3inch                                             */
#define CALIB_MCUID0023_8INCH                       (4U)             /* Display 8.8inch                                              */
#define CALIB_MCUID0024_NUM                         (3U)             /* Brand NUM                                                    */
#define CALIB_MCUID0024_TOYOTA                      (0U)             /* TOYOTA                                                       */
#define CALIB_MCUID0024_LEXUS                       (1U)             /* LEXUS                                                        */
#define CALIB_MCUID0024_SUBARU                      (2U)             /* SUBARU                                                       */
#define CALIB_MCUID0025_NUM                         (7U)             /* Sports Switching NUM                                         */
#define CALIB_MCUID0025_NON                         (0U)             /* Switch NON                                                   */
#define CALIB_MCUID0025_GRS                         (1U)             /* GR-S                                                         */
#define CALIB_MCUID0025_GR                          (2U)             /* GR                                                           */
#define CALIB_MCUID0025_GRMN                        (3U)             /* GRMN                                                         */
#define CALIB_MCUID0025_FSPORT                      (4U)             /* F-SPORT                                                      */
#define CALIB_MCUID0025_F                           (5U)             /* F                                                            */
#define CALIB_MCUID0025_070D                        (6U)             /* 070D                                                         */
#define CALIB_MCUID0026_NUM                         (3U)             /* 1MOT HV Drive Wheel NUM                                      */
#define CALIB_MCUID0026_1MOT_HV_OTH                 (0U)             /* 1MOT HV Other                                                */
#define CALIB_MCUID0026_1MOT_HV_FF                  (1U)             /* 1MOT HV FF                                                   */
#define CALIB_MCUID0026_1MOT_HV_FR                  (2U)             /* 1MOT HV FR                                                   */
#define CALIB_MCUID0209_MIN                         (0U)             /* RRCYM MIN                                                    */
#define CALIB_MCUID0209_MAX                         (1U)             /* RRCYM MAX                                                    */
#define CALIB_MCUID0210_MIN                         (0U)             /* RLCYM MIN                                                    */
#define CALIB_MCUID0210_MAX                         (1U)             /* RLCYM MAX                                                    */
#define CALIB_MCUID0211_MIN                         (0U)             /* BCTYM MIN                                                    */
#define CALIB_MCUID0211_MAX                         (1U)             /* BCTYM MAX                                                    */
#define CALIB_MCUID0212_MIN                         (0U)             /* LGCYM MIN                                                    */
#define CALIB_MCUID0212_MAX                         (1U)             /* LGCYM MAX                                                    */
#define CALIB_MCUID0213_MIN                         (0U)             /* HDCY_BDBM MIN                                                */
#define CALIB_MCUID0213_MAX                         (1U)             /* HDCY_BDBM MAX                                                */
#define CALIB_MCUID0214_MIN                         (0U)             /* RPSDWARNM MIN                                                */
#define CALIB_MCUID0214_MAX                         (1U)             /* RPSDWARNM MAX                                                */
#define CALIB_MCUID0215_MIN                         (0U)             /* LPSDWARNM MIN                                                */
#define CALIB_MCUID0215_MAX                         (1U)             /* LPSDWARNM MAX                                                */
#define CALIB_MCUID0217_MIN                         (0U)             /* steering angle gauge MIN                                     */
#define CALIB_MCUID0217_MAX                         (U1_MAX)         /* steering angle gauge MAX                                     */
#define CALIB_MCUID0218_MIN                         (0U)             /* accelerator brake MIN                                        */
#define CALIB_MCUID0218_MAX                         (U1_MAX)         /* accelerator brake MAX                                        */
#define CALIB_MCUID0219_MIN                         (0U)             /* G_Gauge MAX MAX                                              */
#define CALIB_MCUID0219_MAX                         (U1_MAX)         /* G_Gauge MAX MIN                                              */
#define CALIB_MCUID0220_MIN                         (0U)             /* GTrajectory2 MIN                                             */
#define CALIB_MCUID0220_MAX                         (U1_MAX)         /* GTrajectory2 MAX                                             */
#define CALIB_MCUID0221_MIN                         (0U)             /* G_Display MAX                                                */
#define CALIB_MCUID0221_MAX                         (U1_MAX)         /* G_Display MIN                                                */
#define CALIB_MCUID0222_MIN                         (0U)             /* P Seat Senser SW MIN                                         */
#define CALIB_MCUID0222_MAX                         (1U)             /* P Seat Senser SW MAX                                         */
#define CALIB_MCUID0223_MIN                         (0U)             /* FrCtr Seat Senser SW MIN                                     */
#define CALIB_MCUID0223_MAX                         (1U)             /* FrCtr Seat Senser SW MAX                                     */
#define CALIB_MCUID0224_MIN                         (0U)             /* RR Seat Senser SW MIN                                        */
#define CALIB_MCUID0224_MAX                         (1U)             /* RR Seat Senser SW MAX                                        */
#define CALIB_MCUID0225_MIN                         (0U)             /* RC Seat Senser SW MIN                                        */
#define CALIB_MCUID0225_MAX                         (1U)             /* RC Seat Senser SW MAX                                        */
#define CALIB_MCUID0226_MIN                         (0U)             /* RL Seat Senser SW MIN                                        */
#define CALIB_MCUID0226_MAX                         (1U)             /* RL Seat Senser SW MAX                                        */
#define CALIB_MCUID0227_MIN                         (0U)             /* RR2 Seat Senser SW MIN                                       */
#define CALIB_MCUID0227_MAX                         (1U)             /* RR2 Seat Senser SW MAX                                       */
#define CALIB_MCUID0228_MIN                         (0U)             /* RC2 Seat Senser SW MIN                                       */
#define CALIB_MCUID0228_MAX                         (1U)             /* RC2 Seat Senser SW MAX                                       */
#define CALIB_MCUID0229_MIN                         (0U)             /* RL2 Seat Senser SW MIN                                       */
#define CALIB_MCUID0229_MAX                         (1U)             /* RL2 Seat Senser SW MAX                                       */
#define CALIB_MCUID0230_MIN                         (0U)             /* RR3 Seat Senser SW MIN                                       */
#define CALIB_MCUID0230_MAX                         (1U)             /* RR3 Seat Senser SW MAX                                       */
#define CALIB_MCUID0231_MIN                         (0U)             /* RC3 Seat Senser SW MIN                                       */
#define CALIB_MCUID0231_MAX                         (1U)             /* RC3 Seat Senser SW MAX                                       */
#define CALIB_MCUID0232_MIN                         (0U)             /* RL3 Seat Senser SW MIN                                       */
#define CALIB_MCUID0232_MAX                         (1U)             /* RL3 Seat Senser SW MAX                                       */
#define CALIB_MCUID0233_MIN                         (0U)             /* Rear Seat Door MIN                                           */
#define CALIB_MCUID0233_MAX                         (1U)             /* Rear Seat Door MAX                                           */
#define CALIB_MCUID0234_MIN                         (0U)             /* Walkthrough MIN                                              */
#define CALIB_MCUID0234_MAX                         (1U)             /* Walkthrough MAX                                              */
#define CALIB_MCUID0235_NUM                         (9U)             /* Bodyshape NUM                                                */
#define CALIB_MCUID0235_SEDAN                       (0U)             /* Bodyshape SEDAN                                              */
#define CALIB_MCUID0235_WAGON                       (1U)             /* Bodyshape WAGON                                              */
#define CALIB_MCUID0235_HATCHBACK                   (2U)             /* Bodyshape HATCHBACK                                          */
#define CALIB_MCUID0235_COUPE                       (3U)             /* Bodyshape COUPE                                              */
#define CALIB_MCUID0235_VAN                         (4U)             /* Bodyshape VAN                                                */
#define CALIB_MCUID0235_MINIVAN                     (5U)             /* Bodyshape MINIVAN                                            */
#define CALIB_MCUID0235_COMPACT                     (6U)             /* Bodyshape COMPACT                                            */
#define CALIB_MCUID0235_SUV                         (7U)             /* Bodyshape SUV                                                */
#define CALIB_MCUID0235_PICKUP_TRUCK                (8U)             /* Bodyshape PICKUP TRUCK                                       */
#define CALIB_MCUID0236_MIN                         (0U)             /* NoOptTm MIN                                                  */
#define CALIB_MCUID0236_MAX                         (U1_MAX)         /* NoOptTm MAX                                                  */
#define CALIB_MCUID0237_NUM                         (2U)             /* CAN MOVE FLAG NUM                                            */
#define CALIB_MCUID0237_NE1                         (0U)             /* NE1                                                          */
#define CALIB_MCUID0237_RDYIND                      (1U)             /* RDYIND                                                       */
#define CALIB_MCUID0238_MIN                         (0U)             /* XM Mode MIN                                                  */
#define CALIB_MCUID0238_MAX                         (1U)             /* XM Mode MAX                                                  */
#define CALIB_MCUID0239_MIN                         (0U)             /* FulFul MIN                                                   */
#define CALIB_MCUID0239_MAX                         (U2_MAX)         /* FulFul MAX                                                   */
#define CALIB_MCUID0240_MIN                         (0U)             /* FulMEnp MIN                                                  */
#define CALIB_MCUID0240_MAX                         (U2_MAX)         /* FulMEnp MAX                                                  */
#define CALIB_MCUID0241_MIN                         (0U)             /* FulEff MIN                                                   */
#define CALIB_MCUID0241_MAX                         (84200U)         /* FulEff MAX                                                   */
#define CALIB_MCUID0242_MIN                         (0U)             /* DDFFuCe MIN                                                  */
#define CALIB_MCUID0242_MAX                         (100U)           /* DDFFuCe MAX                                                  */
#define CALIB_MCUID0243_MIN                         (0U)             /* DKHCoef MIN                                                  */
#define CALIB_MCUID0243_MAX                         (U1_MAX)         /* DKHCoef MAX                                                  */
#define CALIB_MCUID0244_MIN                         (0U)             /* EFFUPR MIN                                                   */
#define CALIB_MCUID0244_MAX                         (84200U)         /* EFFUPR MAX                                                   */
#define CALIB_MCUID0245_MIN                         (0U)             /* EFFLOW MIN                                                   */
#define CALIB_MCUID0245_MAX                         (84200U)         /* EFFLOW MAX                                                   */
#define CALIB_MCUID0246_MIN                         (0U)             /* FulCoef MIN                                                  */
#define CALIB_MCUID0246_MAX                         (U1_MAX)         /* FulCoef MAX                                                  */
#define CALIB_MCUID0247_MIN                         (0U)             /* GCoefM MIN                                                   */
#define CALIB_MCUID0247_MAX                         (U1_MAX)         /* GCoefM MAX                                                   */
#define CALIB_MCUID0248_MIN                         (0U)             /* GcoefC MIN                                                   */
#define CALIB_MCUID0248_MAX                         (U1_MAX)         /* GcoefC MAX                                                   */
#define CALIB_MCUID0249_MIN                         (0U)             /* GCoefP MIN                                                   */
#define CALIB_MCUID0249_MAX                         (U1_MAX)         /* GCoefP MAX                                                   */
#define CALIB_MCUID0250_MIN                         (1U)             /* fuel efficiency CONV MIN                                     */
#define CALIB_MCUID0250_MAX                         (6U)             /* fuel efficiency CONV MAX                                     */
#define CALIB_MCUID0251_MIN                         (1U)             /* fuel efficiency HV MIN                                       */
#define CALIB_MCUID0251_MAX                         (6U)             /* fuel efficiency HV MAX                                       */
#define CALIB_MCUID0252_MIN                         (1U)             /* fuel efficiency PHV MIN                                      */
#define CALIB_MCUID0252_MAX                         (6U)             /* fuel efficiency PHV MAX                                      */
#define CALIB_MCUID0253_MIN                         (1U)             /* fuel efficiency FC MIN                                       */
#define CALIB_MCUID0253_MAX                         (6U)             /* fuel efficiency FC MAX                                       */
#define CALIB_MCUID0254_MIN                         (1U)             /* power expense PHV MIN                                        */
#define CALIB_MCUID0254_MAX                         (6U)             /* power expense PHV MAX                                        */
#define CALIB_MCUID0255_MIN                         (1U)             /* ower expense EV MIN                                          */
#define CALIB_MCUID0255_MAX                         (6U)             /* ower expense EV MAX                                          */
#define CALIB_MCUID0256_MIN                         (0U)             /* TOLER_A USA CANADA MIN                                       */
#define CALIB_MCUID0256_MAX                         (62U)            /* TOLER_A USA CANADA MAX                                       */
#define CALIB_MCUID0257_MIN                         (-31)            /* TOLER_B USA CANADA MIN                                       */
#define CALIB_MCUID0257_MAX                         (31)             /* TOLER_B USA CANADA MAX                                       */
#define CALIB_MCUID0260_MIN                         (0U)             /* TOLER_A UNR AUS MIN                                          */
#define CALIB_MCUID0260_MAX                         (62U)            /* TOLER_A UNR AUS MAX                                          */
#define CALIB_MCUID0261_MIN                         (-31)            /* TOLER_B UNR AUS MIN                                          */
#define CALIB_MCUID0261_MAX                         (31)             /* TOLER_B UNR AUS MAX                                          */
#define CALIB_MCUID0757_TO_MCUID0776_MIN            (0)              /* Digital meter vehicle speed for Usa/Canada MIN               */
#define CALIB_MCUID0757_TO_MCUID0776_MAX            (U2_MAX)         /* Digital meter vehicle speed for Usa/Canada MAX               */
#define CALIB_MCUID0777_TO_MCUID0796_MIN            (0)              /* Digital meter vehicle speed for UNR/Australia/others MIN     */
#define CALIB_MCUID0777_TO_MCUID0796_MAX            (U2_MAX)         /* Digital meter vehicle speed for UNR/Australia/others MAX     */
#define CALIB_MCUID0262_MIN                         (0U)             /* Max Speed km MIN                                             */
#define CALIB_MCUID0262_MAX                         (U2_MAX)         /* Max Speed km MAX                                             */
#define CALIB_MCUID0263_MIN                         (0U)             /* Max Speed mph MIN                                            */
#define CALIB_MCUID0263_MAX                         (U2_MAX)         /* Max Speed mph MAX                                            */
#define CALIB_MCUID0264_NUM                         (2U)             /* Fspo NUM                                                     */
#define CALIB_MCUID0264_NORMAL                      (0U)             /* Fspo NORMAL                                                  */
#define CALIB_MCUID0264_FSPORT                      (1U)             /* Fspo F-SPORT                                                 */
#define CALIB_MCUID0265_MIN                         (0U)             /* REVIND MIN                                                   */
#define CALIB_MCUID0265_MAX                         (1U)             /* REVIND MAX                                                   */
#define CALIB_MCUID0266_MIN                         (2000U)          /* RevInit MIN                                                  */
#define CALIB_MCUID0266_MAX                         (9000U)          /* RevInit MAX                                                  */
#define CALIB_MCUID0267_MIN                         (1U)             /* RevLSB MIN                                                   */
#define CALIB_MCUID0267_MAX                         (90U)            /* RevLSB MAX                                                   */
#define CALIB_MCUID0268_NUM                         (3U)             /* SWnum NUM                                                    */
#define CALIB_MCUID0268_BUTTON_1                    (0U)             /* 1 BUTTON                                                     */
#define CALIB_MCUID0268_BUTTON_2                    (1U)             /* 2 BUTTON                                                     */
#define CALIB_MCUID0268_BUTTON_NON                  (2U)             /* BUTTON NON                                                   */
#define CALIB_MCUID0269_NUM                         (3U)             /* SWposi NUM                                                   */
#define CALIB_MCUID0269_BUTTON_INSIDE               (0U)             /* BUTTON Position is INSIDE                                    */
#define CALIB_MCUID0269_BUTTON_OUTSIDE              (1U)             /* BUTTON Position is OUTSIDE                                   */
#define CALIB_MCUID0269_BUTTON_NON                  (2U)             /* BUTTON NON                                                   */
#define CALIB_MCUID0270_TO_MCUID0291_MIN            (0U)             /* CAN:RHEOSTAT(%) MIN                                          */
#define CALIB_MCUID0270_TO_MCUID0291_MAX            (100U)           /* CAN:RHEOSTAT(%) MAX                                          */
#define CALIB_MCUID0292_TO_MCUID0313_MIN            (0U)             /* CAN:TR2_DUTY(%) MIN                                          */
#define CALIB_MCUID0292_TO_MCUID0313_MAX            (1000U)          /* CAN:TR2_DUTY(%) MAX                                          */
#define CALIB_MCUID0314_TO_MCUID0335_MIN            (0U)             /* CAN:IL2_DUTY(%) MIN                                          */
#define CALIB_MCUID0314_TO_MCUID0335_MAX            (1000U)          /* CAN:IL2_DUTY(%) MAX                                          */
#define CALIB_MCUID0336_MIN                         (0U)             /* ILL_OF Level MIN                                             */
#define CALIB_MCUID0336_MAX                         (U1_MAX)         /* ILL_OF Level                                                 */
#define CALIB_MCUID0337_MIN                         (0U)             /* ILL_OF Cancel Level MIN                                      */
#define CALIB_MCUID0337_MAX                         (U1_MAX)         /* ILL_OF Cancel Level MAX                                      */
#define CALIB_MCUID0338_MIN                         (0U)             /* external dimming output MIN                                  */
#define CALIB_MCUID0338_MAX                         (1U)             /* external dimming output MAX                                  */
#define CALIB_MCUID0339_MIN                         (0U)             /* external dimming output(vehicle speed linkage) MIN           */
#define CALIB_MCUID0339_MAX                         (1U)             /* external dimming output(vehicle speed linkage) MAX           */
#define CALIB_MCUID0340_MIN                         (0U)             /* Rheostat Position Night MIN                                  */
#define CALIB_MCUID0340_MAX                         (21U)            /* Rheostat Position Night MAX                                  */
#define CALIB_MCUID0341_MIN                         (0U)             /* TAIL Apply MIN                                               */
#define CALIB_MCUID0341_MAX                         (1U)             /* TAIL Apply MAX                                               */
#define CALIB_MCUID0342_TO_MCUID0363_MIN            (0U)             /* BACKLIGHT(%) DAY MIN                                         */
#define CALIB_MCUID0342_TO_MCUID0363_MAX            (100U)           /* BACKLIGHT(%) DAY MAX                                         */
#define CALIB_MCUID0364_TO_MCUID0385_MIN            (0U)             /* RGB(%) DAY MIN                                               */
#define CALIB_MCUID0364_TO_MCUID0385_MAX            (U1_MAX)         /* RGB(%) DAY MAX                                               */
#define CALIB_MCUID0386_TO_MCUID0407_MIN            (0U)             /* BACKLIGHT(%) NIGHT MIN                                       */
#define CALIB_MCUID0386_TO_MCUID0407_MAX            (100U)           /* BACKLIGHT(%) NIGHT MAX                                       */
#define CALIB_MCUID0408_TO_MCUID0429_MIN            (0U)             /* RGB(%) NIGHT MIN                                             */
#define CALIB_MCUID0408_TO_MCUID0429_MAX            (U1_MAX)         /* RGB(%) NIGHT MAX                                             */
#define CALIB_MCUID0430_NUM                         (4U)             /* Rheostat SW Apply NUM                                        */
#define CALIB_MCUID0430_1_INPUT                     (0U)             /* 1 INPUT                                                      */
#define CALIB_MCUID0430_2_INPUT                     (1U)             /* 2 INPUT                                                      */
#define CALIB_MCUID0430_THUMB_WHEEL                 (2U)             /* THUMB WHEEL                                                  */
#define CALIB_MCUID0430_SOFTSW                      (3U)             /* SOFT SW                                                      */
#define CALIB_MCUID0432_NUM                         (3U)             /* FUEL LID NUM                                                 */
#define CALIB_MCUID0432_LID_NON                     (0U)             /* LID NON                                                      */
#define CALIB_MCUID0432_LSTM                        (1U)             /* LSTM                                                         */
#define CALIB_MCUID0432_LST1                        (2U)             /* LST1                                                         */
#define CALIB_MCUID0433_TO_MCUID0450_MIN            (0U)             /* ANALOG MAIN FUEL LIT MIN                                     */
#define CALIB_MCUID0433_TO_MCUID0450_MAX            (35000U)         /* ANALOG MAIN FUEL LIT MAX                                     */
#define CALIB_MCUID0451_TO_MCUID0468_MIN            (0U)             /* ANALOG MAIN FUEL VOLT MIN                                    */
#define CALIB_MCUID0451_TO_MCUID0468_MAX            (U2_MAX)         /* ANALOG MAIN FUEL VOLT MAX                                    */
#define CALIB_MCUID0469_TO_MCUID0486_MIN            (0U)             /* ANALOG SUB FUEL LIT MIN                                      */
#define CALIB_MCUID0469_TO_MCUID0486_MAX            (35000U)         /* ANALOG SUB FUEL LIT MAX                                      */
#define CALIB_MCUID0487_TO_MCUID0504_MIN            (0U)             /* ANALOG SUB FUEL VOLT MIN                                     */
#define CALIB_MCUID0487_TO_MCUID0504_MAX            (U2_MAX)         /* ANALOG SUB FUEL VOLT MAX                                     */
#define CALIB_MCUID0505_TO_MCUID0517_MIN            (0U)             /* 8SEG MAIN FUEL LIT MIN                                       */
#define CALIB_MCUID0505_TO_MCUID0517_MAX            (35000U)         /* 8SEG MAIN FUEL LIT MAX                                       */
#define CALIB_MCUID0518_TO_MCUID0530_MIN            (0U)             /* 8SEG MAIN FUEL VOLT MIN                                      */
#define CALIB_MCUID0518_TO_MCUID0530_MAX            (U2_MAX)         /* 8SEG MAIN FUEL VOLT MAX                                      */
#define CALIB_MCUID0531_TO_MCUID0543_MIN            (0U)             /* 8SEG SUB FUEL LIT MIN                                        */
#define CALIB_MCUID0531_TO_MCUID0543_MAX            (35000U)         /* 8SEG SUB FUEL LIT MAX                                        */
#define CALIB_MCUID0544_TO_MCUID0556_MIN            (0U)             /* 8SEG SUB FUEL VOLT MIN                                       */
#define CALIB_MCUID0544_TO_MCUID0556_MAX            (U2_MAX)         /* 8SEG SUB FUEL VOLT MAX                                       */
#define CALIB_MCUID0557_MIN                         (0U)             /* ShtJdg MIN                                                   */
#define CALIB_MCUID0557_MAX                         (1U)             /* ShtJdg MAX                                                   */
#define CALIB_MCUID0558_NUM                         (2U)             /* FStype NUM                                                   */
#define CALIB_MCUID0558_HALL_IC                     (0U)             /* HALL IC                                                      */
#define CALIB_MCUID0558_RESISTANCE                  (1U)             /* RESISTANCE                                                   */
#define CALIB_MCUID0559_MIN                         (0U)             /* FOpen MIN                                                    */
#define CALIB_MCUID0559_MAX                         (U2_MAX)         /* FOpen MAX                                                    */
#define CALIB_MCUID0560_MIN                         (1U)             /* ATCaluNum MIN                                                */
#define CALIB_MCUID0560_MAX                         (U1_MAX)         /* ATCaluNum MAX                                                */
#define CALIB_MCUID0561_MIN                         (0U)             /* StpJdg MIN                                                   */
#define CALIB_MCUID0561_MAX                         (U2_MAX)         /* StpJdg MAX                                                   */
#define CALIB_MCUID0562_MIN                         (0U)             /* LubJdgPN MIN                                                 */
#define CALIB_MCUID0562_MAX                         (U2_MAX)         /* LubJdgPN MAX                                                 */
#define CALIB_MCUID0563_MIN                         (0U)             /* LubJdgPL MIN                                                 */
#define CALIB_MCUID0563_MAX                         (U2_MAX)         /* LubJdgPL MAX                                                 */
#define CALIB_MCUID0564_MIN                         (0U)             /* UpdateJdg MIN                                                */
#define CALIB_MCUID0564_MAX                         (U2_MAX)         /* UpdateJdg MAX                                                */
#define CALIB_MCUID0565_MIN                         (0U)             /* RemWrnOn MIN                                                 */
#define CALIB_MCUID0565_MAX                         (U2_MAX)         /* RemWrnOn MAX                                                 */
#define CALIB_MCUID0566_MIN                         (0U)             /* FC_Hosei MIN                                                 */
#define CALIB_MCUID0566_MAX                         (U2_MAX)         /* FC_Hosei MAX                                                 */
#define CALIB_MCUID0567_MIN                         (0U)             /* AutoSTOPL MIN                                                */
#define CALIB_MCUID0567_MAX                         (U2_MAX)         /* AutoSTOPL MAX                                                */
#define CALIB_MCUID0568_MIN                         (0U)             /* MinjudgeL MIN                                                */
#define CALIB_MCUID0568_MAX                         (U2_MAX)         /* MinjudgeL MAX                                                */
#define CALIB_MCUID0569_MIN                         (0U)             /* NslTnkSP MIN                                                 */
#define CALIB_MCUID0569_MAX                         (U2_MAX)         /* NslTnkSP MAX                                                 */
#define CALIB_MCUID0570_MIN                         (0U)             /* Kminval MIN                                                  */
#define CALIB_MCUID0570_MAX                         (U1_MAX)         /* Kminval MAX                                                  */
#define CALIB_MCUID0571_MIN                         (0U)             /* Kmaxval MIN                                                  */
#define CALIB_MCUID0571_MAX                         (U1_MAX)         /* Kmaxval MAX                                                  */
#define CALIB_MCUID0572_NUM                         (3U)             /* Fuel Port Position NUM                                       */
#define CALIB_MCUID0572_FUEL_PORT_NON               (0U)             /* FUEL PORT NON                                                */
#define CALIB_MCUID0572_FUEL_PORT_RIGHT             (1U)             /* FUEL PORT RIGHT                                              */
#define CALIB_MCUID0572_FUEL_PORT_LEFT              (2U)             /* FUEL PORT LEFT                                               */
#define CALIB_MCUID0573_MIN                         (0U)             /* Fuel Sub Sender MIN                                          */
#define CALIB_MCUID0573_MAX                         (1U)             /* Fuel Sub Sender                                              */
#define CALIB_MCUID0574_MIN                         (2000U)          /* CAL_DEF MIN                                                  */
#define CALIB_MCUID0574_MAX                         (2099U)          /* CAL_DEF                                                      */
#define CALIB_MCUID0575_MIN                         (2000U)          /* CAL_MIN MIN                                                  */
#define CALIB_MCUID0575_MAX                         (2099U)          /* CAL_MINl MAX                                                 */
#define CALIB_MCUID0576_MIN                         (0U)             /* DegCW MIN                                                    */
#define CALIB_MCUID0576_MAX                         (U1_MAX)         /* DegCWl MAX                                                   */
#define CALIB_MCUID0577_MIN                         (0U)             /* DegCCW MIN                                                   */
#define CALIB_MCUID0577_MAX                         (U1_MAX)         /* DegCCWl MAX                                                  */
#define CALIB_MCUID0578_MIN                         (1U)             /* Deg_RTStep MIN                                               */
#define CALIB_MCUID0578_MAX                         (U1_MAX)         /* Deg_RTStepl MAX                                              */
#define CALIB_MCUID0579_MIN                         (0U)             /* ResTime MIN                                                  */
#define CALIB_MCUID0579_MAX                         (U1_MAX)         /* ResTimel MAX                                                 */
#define CALIB_MCUID0580_MIN                         (1U)             /* ACon_MvAveCnt MIN                                            */
#define CALIB_MCUID0580_MAX                         (U1_MAX)         /* ACon_MvAveCntl MAX                                           */
#define CALIB_MCUID0581_MIN                         (1U)             /* ACon_UpAveCnt MIN                                            */
#define CALIB_MCUID0581_MAX                         (U1_MAX)         /* ACon_UpAveCntl MAX                                           */
#define CALIB_MCUID0582_MIN                         (1U)             /* ACon_DnAveCnt MIN                                            */
#define CALIB_MCUID0582_MAX                         (U1_MAX)         /* ACon_DnAveCntl MAX                                           */
#define CALIB_MCUID0583_MIN                         (0U)             /* ATss_AorNA MIN                                               */
#define CALIB_MCUID0583_MAX                         (1U)             /* ATss_AorNAl MAX                                              */
#define CALIB_MCUID0584_MIN                         (1U)             /* ATss_UpAveCnt MIN                                            */
#define CALIB_MCUID0584_MAX                         (U1_MAX)         /* ATss_UpAveCntl MAX                                           */
#define CALIB_MCUID0585_MIN                         (1U)             /* ATss_DnAveCnt MIN                                            */
#define CALIB_MCUID0585_MAX                         (U1_MAX)         /* ATss_DnAveCntl MAX                                           */
#define CALIB_MCUID0586_MIN                         (1U)             /* HUDLm_AveCnt MIN                                             */
#define CALIB_MCUID0586_MAX                         (U1_MAX)         /* HUDLm_AveCntl MAX                                            */
#define CALIB_MCUID0588_MIN                         (0U)             /* OM_MLG MIN                                                   */
#define CALIB_MCUID0588_MAX                         (1U)             /* OM_MLGl MAX                                                  */
#define CALIB_MCUID0589_MIN                         (0U)             /* PR_OM_FL MIN                                                 */
#define CALIB_MCUID0589_MAX                         (1U)             /* PR_OM_FL MAX                                                 */
#define CALIB_MCUID0590_NUM                         (3U)             /* SOC Port Position NUM                                        */
#define CALIB_MCUID0590_SOC_PORT_NON                (0U)             /* SOC PORT NON                                                 */
#define CALIB_MCUID0590_SOC_PORT_RIGHT              (1U)             /* SOC PORT RIGHT                                               */
#define CALIB_MCUID0590_SOC_PORT_LEFT               (2U)             /* SOC PORT LEFT                                                */
#define CALIB_MCUID0591_MIN                         (0U)             /* UREA Apply MIN                                               */
#define CALIB_MCUID0591_MAX                         (1U)             /* UREA Apply MAX                                               */
#define CALIB_MCUID0592_NUM                         (3U)             /* SeatBelt Reminder Telltale Type NUM                          */
#define CALIB_MCUID0592_1RRSEAT                     (0U)             /* 1REARSEAT                                                    */
#define CALIB_MCUID0592_1RRSEAT_CTRSEAT             (1U)             /* 1REARSEAT + CENTERSEAT                                       */
#define CALIB_MCUID0592_2RRSEAT                     (2U)             /* 2REARSEAT                                                    */
#define CALIB_MCUID0593_MIN                         (0U)             /* ATTEMP_LO MIN                                                */
#define CALIB_MCUID0593_MAX                         (200U)           /* ATTEMP_LO MAX                                                */
#define CALIB_MCUID0594_MIN                         (0U)             /* ATTEMP_MIDL MIN                                              */
#define CALIB_MCUID0594_MAX                         (200U)           /* ATTEMP_MIDL MAX                                              */
#define CALIB_MCUID0595_MIN                         (0U)             /* ATTEMP_MIDH MIN                                              */
#define CALIB_MCUID0595_MAX                         (200U)           /* ATTEMP_MIDH MAX                                              */
#define CALIB_MCUID0596_MIN                         (0U)             /* ATTEMP_HI MIN                                                */
#define CALIB_MCUID0596_MAX                         (200U)           /* ATTEMP_HI MAX                                                */
#define CALIB_MCUID0597_MIN                         (0U)             /* Flash_Start MIN                                              */
#define CALIB_MCUID0597_MAX                         (200U)           /* Flash_Start MAX                                              */
#define CALIB_MCUID0598_MIN                         (0U)             /* Flash_Stop MIN                                               */
#define CALIB_MCUID0598_MAX                         (200U)           /* Flash_Stop MAX                                               */
#define CALIB_MCUID0599_MIN                         (0U)             /* Red_Zone_Start MIN                                           */
#define CALIB_MCUID0599_MAX                         (200U)           /* Red_Zone_Start MAX                                           */
#define CALIB_MCUID0600_MIN                         (0U)             /* ATTEMPVAL_LO MIN                                             */
#define CALIB_MCUID0600_MAX                         (200U)           /* ATTEMPVAL_LO MAX                                             */
#define CALIB_MCUID0601_MIN                         (0U)             /* ATTEMPVAL_HI MIN                                             */
#define CALIB_MCUID0601_MAX                         (200U)           /* ATTEMPVAL_HI MAX                                             */
#define CALIB_MCUID0602_MIN                         (0U)             /* LAUNCH_Time MIN                                              */
#define CALIB_MCUID0602_MAX                         (U1_MAX)         /* LAUNCH_Time MAX                                              */
#define CALIB_MCUID0603_TO_MCUID0607_NUM            (3U)             /* SeatBelt Regulation NUM                                      */
#define CALIB_MCUID0603_TO_MCUID0607_USA            (0U)             /* SeatBelt Regulation USA                                      */
#define CALIB_MCUID0603_TO_MCUID0607_AUS            (1U)             /* SeatBelt Regulation AUS                                      */
#define CALIB_MCUID0603_TO_MCUID0607_CHN            (2U)             /* SeatBelt Regulation CHN                                      */
#define CALIB_MCUID0608_MIN                         (0U)             /* OLPtlP MIN                                                   */
#define CALIB_MCUID0608_MAX                         (U2_MAX)         /* OLPtlP MAX                                                   */
#define CALIB_MCUID0609_MIN                         (0U)             /* kPaOLPL MIN                                                  */
#define CALIB_MCUID0609_MAX                         (U2_MAX)         /* kPaOLPL MAX                                                  */
#define CALIB_MCUID0610_MIN                         (0U)             /* kPaOLPH MIN                                                  */
#define CALIB_MCUID0610_MAX                         (U2_MAX)         /* kPaOLPH MAX                                                  */
#define CALIB_MCUID0611_MIN                         (0U)             /* barOLPL MIN                                                  */
#define CALIB_MCUID0611_MAX                         (U2_MAX)         /* barOLPL MAX                                                  */
#define CALIB_MCUID0612_MIN                         (0U)             /* barOLPH MIN                                                  */
#define CALIB_MCUID0612_MAX                         (U2_MAX)         /* barOLPH MAX                                                  */
#define CALIB_MCUID0613_MIN                         (0U)             /* psiOLPL MIN                                                  */
#define CALIB_MCUID0613_MAX                         (U2_MAX)         /* psiOLPL MAX                                                  */
#define CALIB_MCUID0614_MIN                         (0U)             /* psiOLPH MIN                                                  */
#define CALIB_MCUID0614_MAX                         (U2_MAX)         /* psiOLPH MAX                                                  */
#define CALIB_MCUID0653_MIN                         (0U)             /* kPaOLPMax MIN                                                */
#define CALIB_MCUID0653_MAX                         (80U)            /* kPaOLPMax MAX                                                */
#define CALIB_MCUID0654_MIN                         (0U)             /* kPaOLPMin MIN                                                */
#define CALIB_MCUID0654_MAX                         (80U)            /* kPaOLPMin MAX                                                */
#define CALIB_MCUID0655_MIN                         (0U)             /* barOLPMax MIN                                                */
#define CALIB_MCUID0655_MAX                         (80U)            /* barOLPMax MAX                                                */
#define CALIB_MCUID0656_MIN                         (0U)             /* barOLPMin MIN                                                */
#define CALIB_MCUID0656_MAX                         (80U)            /* barOLPMin MAX                                                */
#define CALIB_MCUID0657_MIN                         (0U)             /* psiOLPMax MIN                                                */
#define CALIB_MCUID0657_MAX                         (116U)           /* psiOLPMax MAX                                                */
#define CALIB_MCUID0658_MIN                         (0U)             /* psiOLPMin MIN                                                */
#define CALIB_MCUID0658_MAX                         (116U)           /* psiOLPMin MAX                                                */
#define CALIB_MCUID0622_MIN                         (0U)             /* OLTtlP MIN                                                   */
#define CALIB_MCUID0622_MAX                         (U2_MAX)         /* OLTtlP MAX                                                   */
#define CALIB_MCUID0623_MIN                         (0U)             /* OLTtlC MIN                                                   */
#define CALIB_MCUID0623_MAX                         (U1_MAX)         /* OLTtlC MAX                                                   */
#define CALIB_MCUID0624_MIN                         (0U)             /* OLTtlH MIN                                                   */
#define CALIB_MCUID0624_MAX                         (U1_MAX)         /* OLTtlH MAX                                                   */
#define CALIB_MCUID0625_MIN                         (0U)             /* OLTMaxC MIN                                                  */
#define CALIB_MCUID0625_MAX                         (200U)           /* OLTMaxC MAX                                                  */
#define CALIB_MCUID0626_MIN                         (0U)             /* OLTMinC MIN                                                  */
#define CALIB_MCUID0626_MAX                         (200U)           /* OLTMinC MAX                                                  */
#define CALIB_MCUID0627_MIN                         (0U)             /* OLTMaxF MIN                                                  */
#define CALIB_MCUID0627_MAX                         (360U)           /* OLTMaxF MAX                                                  */
#define CALIB_MCUID0628_MIN                         (0U)             /* OLTMinF MIN                                                  */
#define CALIB_MCUID0628_MAX                         (360U)           /* OLTMinF MAX                                                  */
#define CALIB_MCUID0629_MIN                         (0U)             /* hys MIN                                                      */
#define CALIB_MCUID0629_MAX                         (U1_MAX)         /* hys MAX                                                      */
#define CALIB_MCUID0630_MIN                         (0U)             /* TtlP MIN                                                     */
#define CALIB_MCUID0630_MAX                         (U2_MAX)         /* TtlP MAX                                                     */
#define CALIB_MCUID0631_MIN                         (0U)             /* TtlC MIN                                                     */
#define CALIB_MCUID0631_MAX                         (U1_MAX)         /* TtlC MAX                                                     */
#define CALIB_MCUID0632_MIN                         (0U)             /* TtlH MIN                                                     */
#define CALIB_MCUID0632_MAX                         (U1_MAX)         /* TtlH MAX                                                     */
#define CALIB_MCUID0633_MIN                         (0U)             /* TtlMaxC MIN                                                  */
#define CALIB_MCUID0633_MAX                         (180U)           /* TtlMaxC MAX                                                  */
#define CALIB_MCUID0634_MIN                         (0U)             /* TtlMinC MIN                                                  */
#define CALIB_MCUID0634_MAX                         (180U)           /* TtlMinC MAX                                                  */
#define CALIB_MCUID0635_MIN                         (0U)             /* TtlMaxF MIN                                                  */
#define CALIB_MCUID0635_MAX                         (324U)           /* TtlMaxF MAX                                                  */
#define CALIB_MCUID0636_MIN                         (0U)             /* TtlMinF MIN                                                  */
#define CALIB_MCUID0636_MAX                         (324U)           /* TtlMinF MAX                                                  */
#define CALIB_MCUID0637_MIN                         (0U)             /* ovht MIN                                                     */
#define CALIB_MCUID0637_MAX                         (U1_MAX)         /* ovht MAX                                                     */
#define CALIB_MCUID0638_MIN                         (0U)             /* hys MIN                                                      */
#define CALIB_MCUID0638_MAX                         (U1_MAX)         /* hys MAX                                                      */
#define CALIB_MCUID0639_MIN                         (1U)             /* N1 MIN                                                       */
#define CALIB_MCUID0639_MAX                         (U1_MAX)         /* N1 MAX                                                       */
#define CALIB_MCUID0640_MIN                         (1U)             /* N2 MIN                                                       */
#define CALIB_MCUID0640_MAX                         (U1_MAX)         /* N2 MAX                                                       */
#define CALIB_MCUID0641_MIN                         (0U)             /* RevSet MIN                                                   */
#define CALIB_MCUID0641_MAX                         (U2_MAX)         /* RevSet MAX                                                   */
#define CALIB_MCUID0642_MIN                         (0U)             /* RevDispHys MIN                                               */
#define CALIB_MCUID0642_MAX                         (U2_MAX)         /* RevDispHys MAX                                               */
#define CALIB_MCUID0643_MIN                         (0U)             /* RevNoiseHys MIN                                              */
#define CALIB_MCUID0643_MAX                         (U2_MAX)         /* RevNoiseHys MAX                                              */
#define CALIB_MCUID0644_MIN                         (0U)             /* Red Zone RPM MAX MIN                                         */
#define CALIB_MCUID0644_MAX                         (U2_MAX)         /* Red Zone RPM MAX MAX                                         */
#define CALIB_MCUID0645_MIN                         (0U)             /* Red Zone RPM MIN MIN                                         */
#define CALIB_MCUID0645_MAX                         (U2_MAX)         /* Red Zone RPM MIN MAX                                         */
#define CALIB_MCUID0646_MIN                         (0U)             /* Tacho IND MIN                                                */
#define CALIB_MCUID0646_MAX                         (1U)             /* Tacho IND MAX                                                */
#define CALIB_MCUID0647_MIN                         (0U)             /* MET HV System Indicator MIN                                  */
#define CALIB_MCUID0647_MAX                         (1U)             /* MET HV System Indicator MAX                                  */
#define CALIB_MCUID0648_MIN                         (0U)             /* HUD HV System Indicator MIN                                  */
#define CALIB_MCUID0648_MAX                         (1U)             /* HUD HV System Indicator MAX                                  */
#define CALIB_MCUID0649_NUM                         (3U)             /* MET Normal Display Type NUM                                  */
#define CALIB_MCUID0649_NON                         (0U)             /* MET Normal Display NON                                       */
#define CALIB_MCUID0649_HVIND                       (1U)             /* MET Normal Display HV System Indicator                       */
#define CALIB_MCUID0649_TACHO                       (2U)             /* MET Normal Display TACHO Meter                               */
#define CALIB_MCUID0650_NUM                         (3U)             /* HUD Normal Display Type NUM                                  */
#define CALIB_MCUID0650_NON                         (0U)             /* HUD Normal Display NON                                       */
#define CALIB_MCUID0650_TACHO                       (1U)             /* HUD Normal Display TACHO Meter                               */
#define CALIB_MCUID0650_ECOBAR                      (2U)             /* HUD Normal Display ECO Bar                                   */
#define CALIB_MCUID0651_NUM                         (3U)             /* HUD Normal Display Type NUM                                  */
#define CALIB_MCUID0651_NON                         (0U)             /* HUD Normal Display NON                                       */
#define CALIB_MCUID0651_HVIND                       (1U)             /* HUD Normal Display HV System Indicator                       */
#define CALIB_MCUID0651_TACHO                       (2U)             /* HUD Normal Display TACHO Meter                               */
#define CALIB_MCUID0652_MIN                         (0U)             /* TC MIN                                                       */
#define CALIB_MCUID0652_MAX                         (1U)             /* TC MAX                                                       */
#define CALIB_MCUID0659_MIN                         (0U)             /* MTS Normal Mode MIN                                          */
#define CALIB_MCUID0659_MAX                         (1U)             /* MTS Normal Mode MAX                                          */
#define CALIB_MCUID0660_MIN                         (0U)             /* X-MODE MIN                                                   */
#define CALIB_MCUID0660_MAX                         (1U)             /* X-MODE MAX                                                   */
#define CALIB_MCUID0661_MIN                         (0U)             /* GFX Dispay Switching MIN                                     */
#define CALIB_MCUID0661_MAX                         (1U)             /* GFX Dispay Switching MAX                                     */
#define CALIB_MCUID0662_MIN                         (0U)             /* 0dial-View ON/OFF Default MIN                                */
#define CALIB_MCUID0662_MAX                         (1U)             /* 0dial-View ON/OFF Default MAX                                */
#define CALIB_MCUID0663_MIN                         (0U)             /* 1dial-View ON/OFF Default MIN                                */
#define CALIB_MCUID0663_MAX                         (1U)             /* 1dial-View ON/OFF Default MAX                                */
#define CALIB_MCUID0664_MIN                         (0U)             /* 2dial-View ON/OFF Default MIN                                */
#define CALIB_MCUID0664_MAX                         (1U)             /* 2dial-View ON/OFF Default MAX                                */
#define CALIB_MCUID0665_MIN                         (0U)             /* MAP-View ON/OFF Default MIN                                  */
#define CALIB_MCUID0665_MAX                         (1U)             /* MAP-View ON/OFF Default MAX                                  */
#define CALIB_MCUID0666_MIN                         (0U)             /* ADAS-View ON/OFF Default MIN                                 */
#define CALIB_MCUID0666_MAX                         (1U)             /* ADAS-View ON/OFF Default MAX                                 */
#define CALIB_MCUID0667_MIN                         (0U)             /* ECO-View ON/OFF Default MIN                                  */
#define CALIB_MCUID0667_MAX                         (1U)             /* ECO-View ON/OFF Default MAX                                  */
#define CALIB_MCUID0668_MIN                         (0U)             /* 1dial Track-View ON/OFF Default MIN                          */
#define CALIB_MCUID0668_MAX                         (1U)             /* 1dial Track-View ON/OFF Default MAX                          */
#define CALIB_MCUID0669_MIN                         (0U)             /* Shift Up Ind-View ON/OFF Default MIN                         */
#define CALIB_MCUID0669_MAX                         (1U)             /* Shift Up Ind-View ON/OFF Default MAX                         */
#define CALIB_MCUID0670_MIN                         (0U)             /* Off-Road-View ON/OFF Default MIN                             */
#define CALIB_MCUID0670_MAX                         (1U)             /* Off-Road-View ON/OFF Default MAX                             */
#define CALIB_MCUID0671_MIN                         (0U)             /* 6dial-View ON/OFF Default MIN                                */
#define CALIB_MCUID0671_MAX                         (1U)             /* 6dial-View ON/OFF Default MAX                                */
#define CALIB_MCUID0672_MIN                         (0U)             /* Fuel Economy ON/OFF Default MIN                              */
#define CALIB_MCUID0672_MAX                         (1U)             /* Fuel Economy ON/OFF Default MAX                              */
#define CALIB_MCUID0673_MIN                         (0U)             /* Power Consumption ON/OFF Default MIN                         */
#define CALIB_MCUID0673_MAX                         (1U)             /* Power Consumption ON/OFF Default MAX                         */
#define CALIB_MCUID0674_MIN                         (0U)             /* PHEV Fuel Economy ON/OFF Default MIN                         */
#define CALIB_MCUID0674_MAX                         (1U)             /* PHEV Fuel Economy ON/OFF Default MAX                         */
#define CALIB_MCUID0675_MIN                         (0U)             /* Eco Indicator ON/OFF Default MIN                             */
#define CALIB_MCUID0675_MAX                         (1U)             /* Eco Indicator ON/OFF Default MAX                             */
#define CALIB_MCUID0676_MIN                         (0U)             /* HEV/FCEV Eco Score ON/OFF Default MIN                        */
#define CALIB_MCUID0676_MAX                         (1U)             /* HEV/FCEV Eco Score ON/OFF Default MAX                        */
#define CALIB_MCUID0677_MIN                         (0U)             /* EV Ratio ON/OFF Default MIN                                  */
#define CALIB_MCUID0677_MAX                         (1U)             /* EV Ratio ON/OFF Default MAX                                  */
#define CALIB_MCUID0678_MIN                         (0U)             /* Navigation ON/OFF Default MIN                                */
#define CALIB_MCUID0678_MAX                         (1U)             /* Navigation ON/OFF Default MAX                                */
#define CALIB_MCUID0679_MIN                         (0U)             /* Audio ON/OFF Default MIN                                     */
#define CALIB_MCUID0679_MAX                         (1U)             /* Audio ON/OFF Default MAX                                     */
#define CALIB_MCUID0680_MIN                         (0U)             /* Drive Info ON/OFF Default                                    */
#define CALIB_MCUID0680_MAX                         (1U)             /* Drive Info ON/OFF Default                                    */
#define CALIB_MCUID0681_MIN                         (0U)             /* Trip A ON/OFF Default MIN                                    */
#define CALIB_MCUID0681_MAX                         (1U)             /* Trip A ON/OFF Default MAX                                    */
#define CALIB_MCUID0682_MIN                         (0U)             /* Trip B ON/OFF Default MIN                                    */
#define CALIB_MCUID0682_MAX                         (1U)             /* Trip B ON/OFF Default MAX                                    */
#define CALIB_MCUID0683_MIN                         (0U)             /* Energy Monitor ON/OFF Default MIN                            */
#define CALIB_MCUID0683_MAX                         (1U)             /* Energy Monitor ON/OFF Default MAX                            */
#define CALIB_MCUID0684_MIN                         (0U)             /* TPMS ON/OFF Default MIN                                      */
#define CALIB_MCUID0684_MAX                         (1U)             /* TPMS ON/OFF Default MAX                                      */
#define CALIB_MCUID0685_MIN                         (0U)             /* 4WD ON/OFF Default MIN                                       */
#define CALIB_MCUID0685_MAX                         (1U)             /* 4WD ON/OFF Default MAX                                       */
#define CALIB_MCUID0686_MIN                         (0U)             /* TRC ON/OFF Default MIN                                       */
#define CALIB_MCUID0686_MAX                         (1U)             /* TRC ON/OFF Default MAX                                       */
#define CALIB_MCUID0687_MIN                         (0U)             /* Steering angle ON/OFF Default MIN                            */
#define CALIB_MCUID0687_MAX                         (1U)             /* Steering angle ON/OFF Default MAX                            */
#define CALIB_MCUID0688_MIN                         (0U)             /* Pitch and Roll ON/OFF Default MIN                            */
#define CALIB_MCUID0688_MAX                         (1U)             /* Pitch and Roll ON/OFF Default MAX                            */
#define CALIB_MCUID0689_MIN                         (0U)             /* Trailer Brake ON/OFF Default MIN                             */
#define CALIB_MCUID0689_MAX                         (1U)             /* Trailer Brake ON/OFF Default MAX                             */
#define CALIB_MCUID0690_MIN                         (0U)             /* Trailer Mode BSM ON/OFF Default MIN                          */
#define CALIB_MCUID0690_MAX                         (1U)             /* Trailer Mode BSM ON/OFF Default MAX                          */
#define CALIB_MCUID0691_MIN                         (0U)             /* Voltmeter ON/OFF Default MIN                                 */
#define CALIB_MCUID0691_MAX                         (1U)             /* Voltmeter ON/OFF Default MAX                                 */
#define CALIB_MCUID0692_MIN                         (0U)             /* Oil Pressure/Voltmeter ON/OFF Default MIN                    */
#define CALIB_MCUID0692_MAX                         (1U)             /* Oil Pressure/Voltmeter ON/OFF Default MAX                    */
#define CALIB_MCUID0693_MIN                         (0U)             /* Engine/AT Oil Temp ON/OFF Default MIN                        */
#define CALIB_MCUID0693_MAX                         (1U)             /* Engine/AT Oil Temp ON/OFF Default MAX                        */
#define CALIB_MCUID0694_MIN                         (0U)             /* Engine Oil Temp ON/OFF Default MIN                           */
#define CALIB_MCUID0694_MAX                         (1U)             /* Engine Oil Temp ON/OFF Default MAX                           */
#define CALIB_MCUID0695_MIN                         (0U)             /* AT Oil Temp ON/OFF Default MIN                               */
#define CALIB_MCUID0695_MAX                         (1U)             /* AT Oil Temp ON/OFF Default MAX                               */
#define CALIB_MCUID0696_MIN                         (0U)             /* Turbo Gauge(CONV)(With Logo) ON/OFF Default MIN              */
#define CALIB_MCUID0696_MAX                         (1U)             /* Turbo Gauge(CONV)(With Logo) ON/OFF Default MAX              */
#define CALIB_MCUID0697_MIN                         (0U)             /* Turbo Gauge(CONV)(Without Logo) ON/OFF Default MIN           */
#define CALIB_MCUID0697_MAX                         (1U)             /* Turbo Gauge(CONV)(Without Logo) ON/OFF Default MAX           */
#define CALIB_MCUID0698_MIN                         (0U)             /* Boost Gauge(CONV)(With Logo) ON/OFF Default MIN              */
#define CALIB_MCUID0698_MAX                         (1U)             /* Boost Gauge(CONV)(With Logo) ON/OFF Default MAX              */
#define CALIB_MCUID0699_MIN                         (0U)             /* Boost Gauge(CONV)(Without Logo) ON/OFF Default MIN           */
#define CALIB_MCUID0699_MAX                         (1U)             /* Boost Gauge(CONV)(Without Logo) ON/OFF Default MAX           */
#define CALIB_MCUID0700_MIN                         (0U)             /* Motor Power(48V-MHV) ON/OFF Default MIN                      */
#define CALIB_MCUID0700_MAX                         (1U)             /* Motor Power(48V-MHV) ON/OFF Default MAX                      */
#define CALIB_MCUID0701_MIN                         (0U)             /* Sports Gauges ON/OFF Default MIN                             */
#define CALIB_MCUID0701_MAX                         (1U)             /* Sports Gauges ON/OFF Default MAX                             */
#define CALIB_MCUID0702_MIN                         (0U)             /* G-Force ON/OFF Default MIN                                   */
#define CALIB_MCUID0702_MAX                         (1U)             /* G-Force ON/OFF Default MAX                                   */
#define CALIB_MCUID0703_MIN                         (0U)             /* AdBlue ON/OFF Default MIN                                    */
#define CALIB_MCUID0703_MAX                         (1U)             /* AdBlue ON/OFF Default MAX                                    */
#define CALIB_MCUID0704_MIN                         (0U)             /* Energy consumption ON/OFF Default MIN                        */
#define CALIB_MCUID0704_MAX                         (1U)             /* Energy consumption ON/OFF Default MAX                        */
#define CALIB_MCUID0705_NUM                         (3U)             /* MET CENTER DIAL Tachometer Type NUM                          */
#define CALIB_MCUID0705_CSTM_OFF                    (0U)             /* MET CENTER DIAL Tachometer CSTM OFF                          */
#define CALIB_MCUID0705_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL Tachometer CSTM ON (Non Default)             */
#define CALIB_MCUID0705_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL Tachometer CSTM ON (Default)                 */
#define CALIB_MCUID0706_NUM                         (3U)             /* MET CENTER DIAL Speed Type NUM                               */
#define CALIB_MCUID0706_CSTM_OFF                    (0U)             /* MET CENTER DIAL Speed CSTM OFF                               */
#define CALIB_MCUID0706_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL Speed CSTM ON (Non Default)                  */
#define CALIB_MCUID0706_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL Speed CSTM ON (Default)                      */
#define CALIB_MCUID0707_NUM                         (3U)             /* MET CENTER DIAL HVIndicator Type NUM                         */
#define CALIB_MCUID0707_CSTM_OFF                    (0U)             /* MET CENTER DIAL HVIndicator CSTM OFF                         */
#define CALIB_MCUID0707_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL HVIndicator CSTM ON (Non Default)            */
#define CALIB_MCUID0707_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL HVIndicator CSTM ON (Default)                */
#define CALIB_MCUID0708_NUM                         (3U)             /* MET CENTER DIAL FCIndicator Type NUM                         */
#define CALIB_MCUID0708_CSTM_OFF                    (0U)             /* MET CENTER DIAL FCIndicator CSTM OFF                         */
#define CALIB_MCUID0708_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL FCIndicator CSTM ON (Non Default)            */
#define CALIB_MCUID0708_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL FCIndicator CSTM ON (Default)                */
#define CALIB_MCUID0709_NUM                         (3U)             /* MET CENTER DIAL Pwrmeter Type NUM                            */
#define CALIB_MCUID0709_CSTM_OFF                    (0U)             /* MET CENTER DIAL Pwrmeter CSTM OFF                            */
#define CALIB_MCUID0709_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL Pwrmeter CSTM ON (Non Default)               */
#define CALIB_MCUID0709_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL Pwrmeter CSTM ON (Default)                   */
#define CALIB_MCUID0754_CSTM_ON_NONDEF              (1U)             /* MET CENTER DIAL DriveMode Interlocking CSTM ON (Non Default) */
#define CALIB_MCUID0754_CSTM_ON_DEF                 (2U)             /* MET CENTER DIAL DriveMode Interlocking CSTM ON (Default)     */
#define CALIB_MCUID0710_NUM                         (3U)             /* MET LEFT DIAL Tachometer Type NUM                            */
#define CALIB_MCUID0710_CSTM_OFF                    (0U)             /* MET LEFT DIAL Tachometer CSTM OFF                            */
#define CALIB_MCUID0710_CSTM_ON_NONDEF              (1U)             /* MET LEFT DIAL Tachometer CSTM ON (Non Default)               */
#define CALIB_MCUID0710_CSTM_ON_DEF                 (2U)             /* MET LEFT DIAL Tachometer CSTM ON (Default)                   */
#define CALIB_MCUID0711_NUM                         (3U)             /* MET LEFT DIAL HVIndicator Type NUM                           */
#define CALIB_MCUID0711_CSTM_OFF                    (0U)             /* MET LEFT DIAL HVIndicator CSTM OFF                           */
#define CALIB_MCUID0711_CSTM_ON_NONDEF              (1U)             /* MET LEFT DIAL HVIndicator CSTM ON (Non Default)              */
#define CALIB_MCUID0711_CSTM_ON_DEF                 (2U)             /* MET LEFT DIAL HVIndicator CSTM ON (Default)                  */
#define CALIB_MCUID0712_NUM                         (3U)             /* MET LEFT DIAL FCIndicator Type NUM                           */
#define CALIB_MCUID0712_CSTM_OFF                    (0U)             /* MET LEFT DIAL FCIndicator CSTM OFF                           */
#define CALIB_MCUID0712_CSTM_ON_NONDEF              (1U)             /* MET LEFT DIAL FCIndicator CSTM ON (Non Default)              */
#define CALIB_MCUID0712_CSTM_ON_DEF                 (2U)             /* MET LEFT DIAL FCIndicator CSTM ON (Default)                  */
#define CALIB_MCUID0713_NUM                         (3U)             /* MET LEFT DIAL Pwrmeter Type NUM                              */
#define CALIB_MCUID0713_CSTM_OFF                    (0U)             /* MET LEFT DIAL Pwrmeter CSTM OFF                              */
#define CALIB_MCUID0713_CSTM_ON_NONDEF              (1U)             /* MET LEFT DIAL Pwrmeter CSTM ON (Non Default)                 */
#define CALIB_MCUID0713_CSTM_ON_DEF                 (2U)             /* MET LEFT DIAL Pwrmeter CSTM ON (Default)                     */
#define CALIB_MCUID0755_CSTM_ON_NONDEF              (1U)             /* MET LEFT DIAL DriveMode Interlocking CSTM ON (Non Default)   */
#define CALIB_MCUID0755_CSTM_ON_DEF                 (2U)             /* MET LEFT DIAL DriveMode Interlocking CSTM ON (Default)       */
#define CALIB_MCUID0715_NUM                         (3U)             /* HUD AnalogTachometer Type NUM                                */
#define CALIB_MCUID0715_CSTM_OFF                    (0U)             /* HUD AnalogTachometer CSTM OFF                                */
#define CALIB_MCUID0715_CSTM_ON_NONDEF              (1U)             /* HUD AnalogTachometer CSTM ON (Non Default)                   */
#define CALIB_MCUID0715_CSTM_ON_DEF                 (2U)             /* HUD AnalogTachometer CSTM ON (Default)                       */
#define CALIB_MCUID0716_NUM                         (3U)             /* HUD AnalogEcodriveIndicator Type NUM                         */
#define CALIB_MCUID0716_CSTM_OFF                    (0U)             /* HUD AnalogEcodriveIndicator CSTM OFF                         */
#define CALIB_MCUID0716_CSTM_ON_NONDEF              (1U)             /* HUD AnalogEcodriveIndicator CSTM ON (Non Default)            */
#define CALIB_MCUID0716_CSTM_ON_DEF                 (2U)             /* HUD AnalogEcodriveIndicator CSTM ON (Default)                */
#define CALIB_MCUID0717_NUM                         (3U)             /* HUD AnalogHVIndicator Type NUM                               */
#define CALIB_MCUID0717_CSTM_OFF                    (0U)             /* HUD AnalogHVIndicator CSTM OFF                               */
#define CALIB_MCUID0717_CSTM_ON_NONDEF              (1U)             /* HUD AnalogHVIndicator CSTM ON (Non Default)                  */
#define CALIB_MCUID0717_CSTM_ON_DEF                 (2U)             /* HUD AnalogHVIndicator CSTM ON (Default)                      */
#define CALIB_MCUID0718_NUM                         (3U)             /* HUD AnalogFCIndicator Type NUM                               */
#define CALIB_MCUID0718_CSTM_OFF                    (0U)             /* HUD AnalogFCIndicator CSTM OFF                               */
#define CALIB_MCUID0718_CSTM_ON_NONDEF              (1U)             /* HUD AnalogFCIndicator CSTM ON (Non Default)                  */
#define CALIB_MCUID0718_CSTM_ON_DEF                 (2U)             /* HUD AnalogFCIndicator CSTM ON (Default)                      */
#define CALIB_MCUID0719_NUM                         (3U)             /* HUD Pwrmeter Type NUM                                        */
#define CALIB_MCUID0719_CSTM_OFF                    (0U)             /* HUD Pwrmeter CSTM OFF                                        */
#define CALIB_MCUID0719_CSTM_ON_NONDEF              (1U)             /* HUD Pwrmeter CSTM ON (Non Default)                           */
#define CALIB_MCUID0719_CSTM_ON_DEF                 (2U)             /* HUD Pwrmeter CSTM ON (Default)                               */
#define CALIB_MCUID0756_CSTM_ON_NONDEF              (1U)             /* HUD DriveMode Interlocking CSTM ON (Non Default)             */
#define CALIB_MCUID0756_CSTM_ON_DEF                 (2U)             /* HUD DriveMode Interlocking CSTM ON (Default)                 */
#define CALIB_MCUID0720_MIN                         (0U)             /* PARK_S MIN                                                   */
#define CALIB_MCUID0720_MAX                         (1U)             /* PARK_S MAX                                                   */
#define CALIB_MCUID0721_MIN                         (0U)             /* PARK MIN                                                     */
#define CALIB_MCUID0721_MAX                         (1U)             /* PARK MAX                                                     */
#define CALIB_MCUID0722_MIN                         (0U)             /* LUD MIN                                                      */
#define CALIB_MCUID0722_MAX                         (1U)             /* LUD MAX                                                      */
#define CALIB_MCUID0723_MIN                         (0U)             /* Powertrain System Run Distance After starting MIN            */
#define CALIB_MCUID0723_MAX                         (1U)             /* Powertrain System Run Distance After starting MAX            */
#define CALIB_MCUID0726_MIN                         (0U)             /* Powertrain System Run Time After starting MIN                */
#define CALIB_MCUID0726_MAX                         (1U)             /* Powertrain System Run Time After starting MAX                */
#define CALIB_MCUID0729_MIN                         (0U)             /* Average Fuel Economy After starting MIN                      */
#define CALIB_MCUID0729_MAX                         (1U)             /* Average Fuel Economy After starting MAX                      */
#define CALIB_MCUID0732_MIN                         (0U)             /* EV Ratio MIN                                                 */
#define CALIB_MCUID0732_MAX                         (1U)             /* EV Ratio MAX                                                 */
#define CALIB_MCUID0735_MIN                         (0U)             /* Average Electric Economy After starting MIN                  */
#define CALIB_MCUID0735_MAX                         (1U)             /* Average Electric Economy After starting MAX                  */
#define CALIB_MCUID0738_MIN                         (0U)             /* Timeout Time MIN                                             */
#define CALIB_MCUID0738_MAX                         (U2_MAX)         /* Timeout Time MAX                                             */
#define CALIB_MCUID0740_MIN                         (0U)             /* Oil Level ON/OFF Default MIN                                 */
#define CALIB_MCUID0740_MAX                         (1U)             /* Oil Level ON/OFF Default MAX                                 */
#define CALIB_MCUID0741_MIN                         (0U)             /* IL2OUTILLRun MIN                                             */
#define CALIB_MCUID0741_MAX                         (1U)             /* IL2OUTILLRun MAX                                             */
#define CALIB_MCUID0742_MIN                         (0U)             /* IOUTILLRun MIN                                               */
#define CALIB_MCUID0742_MAX                         (1000U)          /* IOUTILLRun MAX                                               */
#define CALIB_MCUID0743_MIN                         (0U)             /* IOUTILLRunmax MIN                                            */
#define CALIB_MCUID0743_MAX                         (1000U)          /* IOUTILLRunmax MAX                                            */
#define CALIB_MCUID0797_MIN                         (0U)             /* Constant write flag MIN                                      */
#define CALIB_MCUID0797_MAX                         (1U)             /* Constant write flag MAX                                      */
#define CALIB_BL_STEP                               (22U)            /* BACKLIGHT STEP NUM                                           */
#define CALIB_RGB_STEP                              (22U)            /* RGB STEP NUM                                                 */
#define CALIB_FU_MA_ANA                             (18U)            /* Main Tank Table Array Ana                                    */
#define CALIB_FU_SU_ANA                             (18U)            /* Sub Tank Table Array Ana                                     */
#define CALIB_FU_MA_SEG                             (13U)            /* Main Tank Table Array Seg                                    */
#define CALIB_FU_SU_SEG                             (13U)            /* Sub Tank Table Array Seg                                     */
#define CALIB_MCUID0270_RHEO_STEP                   (22U)            /* RHEOSTAT STEP NUM                                            */
#define CALIB_MCUID0292_TR2_STEP                    (22U)            /* TR2 STEP NUM                                                 */
#define CALIB_MCUID0314_IL2_STEP                    (22U)            /* IL2 STEP NUM                                                 */
#define CALIB_MCUID0342_BL_STEP_DAY                 (CALIB_BL_STEP)  /* BACKLIGHT STEP NUM(Daylight brightness table)                */
#define CALIB_MCUID0364_RGB_STEP_DAY                (CALIB_RGB_STEP) /* RGB STEP NUM(Daylight brightness table)                      */
#define CALIB_MCUID0386_BL_STEP_NIGHT               (CALIB_BL_STEP)  /* BACKLIGHT STEP NUM(Night brightness table)                   */
#define CALIB_MCUID0408_RGB_STEP_NIGHT              (CALIB_RGB_STEP) /* RGB STEP NUM(Night brightness table)                         */

#define CALIB_MCUID0433_FU_ANALITMA                 (CALIB_FU_MA_ANA)/* Remaining amount Table Array(L) Ana Main: Num of Arrays      */
#define CALIB_MCUID0433_FU_LITMA_SF                 (0U)             /* Remaining amount Table Array(L) Ana Main: SF                 */
#define CALIB_MCUID0434_FU_LITMA_MFP5               (1U)             /* Remaining amount Table Array(L) Ana Main: MF+5deg            */
#define CALIB_MCUID0435_FU_LITMA_MF                 (2U)             /* Remaining amount Table Array(L) Ana Main: MF                 */
#define CALIB_MCUID0436_FU_LITMA_ANG90              (3U)             /* Remaining amount Table Array(L) Ana Main: Swing Angle 90%    */
#define CALIB_MCUID0437_FU_LITMA_ANG80              (4U)             /* Remaining amount Table Array(L) Ana Main: Swing Angle 80%    */
#define CALIB_MCUID0438_FU_LITMA_3QRTS              (5U)             /* Remaining amount Table Array(L) Ana Main: Meter 3/4          */
#define CALIB_MCUID0439_FU_LITMA_ANG70              (6U)             /* Remaining amount Table Array(L) Ana Main: Swing Angle 70%    */
#define CALIB_MCUID0440_FU_LITMA_ANG60              (7U)             /* Remaining amount Table Array(L) Ana Main: Swing Angle 60%    */
#define CALIB_MCUID0441_FU_LITMA_HALF               (8U)             /* Remaining amount Table Array(L) Ana Main: Meter 1/2          */
#define CALIB_MCUID0442_FU_LITMA_ANG40              (9U)             /* Remaining amount Table Array(L) Ana Main: Swing Angle 40%    */
#define CALIB_MCUID0443_FU_LITMA_ANG30              (10U)            /* Remaining amount Table Array(L) Ana Main: Swing Angle 30%    */
#define CALIB_MCUID0444_FU_LITMA_1QRTS              (11U)            /* Remaining amount Table Array(L) Ana Main: Meter 1/4          */
#define CALIB_MCUID0445_FU_LITMA_ANG20              (12U)            /* Remaining amount Table Array(L) Ana Main: Swing Angle 20%    */
#define CALIB_MCUID0446_FU_LITMA_ANG10              (13U)            /* Remaining amount Table Array(L) Ana Main: Swing Angle 10%    */
#define CALIB_MCUID0447_FU_LITMA_WNG_ON             (14U)            /* Remaining amount Table Array(L) Ana Main: WNG lit            */
#define CALIB_MCUID0448_FU_LITMA_ME                 (15U)            /* Remaining amount Table Array(L) Ana Main: ME                 */
#define CALIB_MCUID0449_FU_LITMA_MEM5               (16U)            /* Remaining amount Table Array(L) Ana Main: ME-5deg            */
#define CALIB_MCUID0450_FU_LITMA_SE                 (17U)            /* Remaining amount Table Array(L) Ana Main: SE                 */
#define CALIB_MCUID0451_FU_ANAVLTMA                 (CALIB_FU_MA_ANA)/* Sender voltage Table Array(V) Ana Main: Num of Arrays        */
#define CALIB_MCUID0451_FU_VLTMA_SF                 (0U)             /* Sender voltage Table Array(V) Ana Main: SF                   */
#define CALIB_MCUID0452_FU_VLTMA_MFP5               (1U)             /* Sender voltage Table Array(V) Ana Main: MF+5deg              */
#define CALIB_MCUID0453_FU_VLTMA_MF                 (2U)             /* Sender voltage Table Array(V) Ana Main: MF                   */
#define CALIB_MCUID0454_FU_VLTMA_ANG90              (3U)             /* Sender voltage Table Array(V) Ana Main: Swing Angle 90%      */
#define CALIB_MCUID0455_FU_VLTMA_ANG80              (4U)             /* Sender voltage Table Array(V) Ana Main: Swing Angle 80%      */
#define CALIB_MCUID0456_FU_VLTMA_3QRTS              (5U)             /* Sender voltage Table Array(V) Ana Main: Meter 3/4            */
#define CALIB_MCUID0457_FU_VLTMA_ANG70              (6U)             /* Sender voltage Table Array(V) Ana Main: Swing Angle 70%      */
#define CALIB_MCUID0458_FU_VLTMA_ANG60              (7U)             /* Sender voltage Table Array(V) Ana Main: Swing Angle 60%      */
#define CALIB_MCUID0459_FU_VLTMA_HALF               (8U)             /* Sender voltage Table Array(V) Ana Main: Meter 1/2            */
#define CALIB_MCUID0460_FU_VLTMA_ANG40              (9U)             /* Sender voltage Table Array(V) Ana Main: Swing Angle 40%      */
#define CALIB_MCUID0461_FU_VLTMA_ANG30              (10U)            /* Sender voltage Table Array(V) Ana Main: Swing Angle 30%      */
#define CALIB_MCUID0462_FU_VLTMA_1QRTS              (11U)            /* Sender voltage Table Array(V) Ana Main: Meter 1/4            */
#define CALIB_MCUID0463_FU_VLTMA_ANG20              (12U)            /* Sender voltage Table Array(V) Ana Main: Swing Angle 20%      */
#define CALIB_MCUID0464_FU_VLTMA_ANG10              (13U)            /* Sender voltage Table Array(V) Ana Main: Swing Angle 10%      */
#define CALIB_MCUID0465_FU_VLTMA_WNG_ON             (14U)            /* Sender voltage Table Array(V) Ana Main: WNG lit              */
#define CALIB_MCUID0466_FU_VLTMA_ME                 (15U)            /* Sender voltage Table Array(V) Ana Main: ME                   */
#define CALIB_MCUID0467_FU_VLTMA_MEM5               (16U)            /* Sender voltage Table Array(V) Ana Main: ME-5deg              */
#define CALIB_MCUID0468_FU_VLTMA_SE                 (17U)            /* Sender voltage Table Array(V) Ana Main: SE                   */
#define CALIB_MCUID0469_FU_ANALITSU                 (CALIB_FU_SU_ANA)/* Remaining amount Table Array(L) Ana Sub: Num of Arrays       */
#define CALIB_MCUID0469_FU_LITSU_SF                 (0U)             /* Remaining amount Table Array(L) Ana Sub: SF                  */
#define CALIB_MCUID0470_FU_LITSU_MFP5               (1U)             /* Remaining amount Table Array(L) Ana Sub: MF+5deg             */
#define CALIB_MCUID0471_FU_LITSU_MF                 (2U)             /* Remaining amount Table Array(L) Ana Sub: MF                  */
#define CALIB_MCUID0472_FU_LITSU_ANG90              (3U)             /* Remaining amount Table Array(L) Ana Sub: Swing Angle 90%     */
#define CALIB_MCUID0473_FU_LITSU_ANG80              (4U)             /* Remaining amount Table Array(L) Ana Sub: Swing Angle 80%     */
#define CALIB_MCUID0474_FU_LITSU_3QRTS              (5U)             /* Remaining amount Table Array(L) Ana Sub: Meter 3/4           */
#define CALIB_MCUID0475_FU_LITSU_ANG70              (6U)             /* Remaining amount Table Array(L) Ana Sub: Swing Angle 70%     */
#define CALIB_MCUID0476_FU_LITSU_ANG60              (7U)             /* Remaining amount Table Array(L) Ana Sub: Swing Angle 60%     */
#define CALIB_MCUID0477_FU_LITSU_HALF               (8U)             /* Remaining amount Table Array(L) Ana Sub: Meter 1/2           */
#define CALIB_MCUID0478_FU_LITSU_ANG40              (9U)             /* Remaining amount Table Array(L) Ana Sub: Swing Angle 40%     */
#define CALIB_MCUID0479_FU_LITSU_ANG30              (10U)            /* Remaining amount Table Array(L) Ana Sub: Swing Angle 30%     */
#define CALIB_MCUID0480_FU_LITSU_1QRTS              (11U)            /* Remaining amount Table Array(L) Ana Sub: Meter 1/4           */
#define CALIB_MCUID0481_FU_LITSU_ANG20              (12U)            /* Remaining amount Table Array(L) Ana Sub: Swing Angle 20%     */
#define CALIB_MCUID0482_FU_LITSU_ANG10              (13U)            /* Remaining amount Table Array(L) Ana Sub: Swing Angle 10%     */
#define CALIB_MCUID0483_FU_LITSU_WNG_ON             (14U)            /* Remaining amount Table Array(L) Ana Sub: WNG lit             */
#define CALIB_MCUID0484_FU_LITSU_ME                 (15U)            /* Remaining amount Table Array(L) Ana Sub: ME                  */
#define CALIB_MCUID0485_FU_LITSU_MEM5               (16U)            /* Remaining amount Table Array(L) Ana Sub: ME-5deg             */
#define CALIB_MCUID0486_FU_LITSU_SE                 (17U)            /* Remaining amount Table Array(L) Ana Sub: SE                  */
#define CALIB_MCUID0487_FU_ANAVLTSU                 (CALIB_FU_SU_ANA)/* Sender voltage Table Array(V) Ana Sub: Num of Arrays         */
#define CALIB_MCUID0487_FU_VLTSU_SF                 (0U)             /* Sender voltage Table Array(V) Ana Sub: SF                    */
#define CALIB_MCUID0488_FU_VLTSU_MFP5               (1U)             /* Sender voltage Table Array(V) Ana Sub: MF+5deg               */
#define CALIB_MCUID0489_FU_VLTSU_MF                 (2U)             /* Sender voltage Table Array(V) Ana Sub: MF                    */
#define CALIB_MCUID0490_FU_VLTSU_ANG90              (3U)             /* Sender voltage Table Array(V) Ana Sub: Swing Angle 90%       */
#define CALIB_MCUID0491_FU_VLTSU_ANG80              (4U)             /* Sender voltage Table Array(V) Ana Sub: Swing Angle 80%       */
#define CALIB_MCUID0492_FU_VLTSU_3QRTS              (5U)             /* Sender voltage Table Array(V) Ana Sub: Meter 3/4             */
#define CALIB_MCUID0493_FU_VLTSU_ANG70              (6U)             /* Sender voltage Table Array(V) Ana Sub: Swing Angle 70%       */
#define CALIB_MCUID0494_FU_VLTSU_ANG60              (7U)             /* Sender voltage Table Array(V) Ana Sub: Swing Angle 60%       */
#define CALIB_MCUID0495_FU_VLTSU_HALF               (8U)             /* Sender voltage Table Array(V) Ana Sub: Meter 1/2             */
#define CALIB_MCUID0496_FU_VLTSU_ANG40              (9U)             /* Sender voltage Table Array(V) Ana Sub: Swing Angle 40%       */
#define CALIB_MCUID0497_FU_VLTSU_ANG30              (10U)            /* Sender voltage Table Array(V) Ana Sub: Swing Angle 30%       */
#define CALIB_MCUID0498_FU_VLTSU_1QRTS              (11U)            /* Sender voltage Table Array(V) Ana Sub: Meter 1/4             */
#define CALIB_MCUID0499_FU_VLTSU_ANG20              (12U)            /* Sender voltage Table Array(V) Ana Sub: Swing Angle 20%       */
#define CALIB_MCUID0500_FU_VLTSU_ANG10              (13U)            /* Sender voltage Table Array(V) Ana Sub: Swing Angle 10%       */
#define CALIB_MCUID0501_FU_VLTSU_WNG_ON             (14U)            /* Sender voltage Table Array(V) Ana Sub: WNG lit               */
#define CALIB_MCUID0502_FU_VLTSU_ME                 (15U)            /* Sender voltage Table Array(V) Ana Sub: ME                    */
#define CALIB_MCUID0503_FU_VLTSU_MEM5               (16U)            /* Sender voltage Table Array(V) Ana Sub: ME-5deg               */
#define CALIB_MCUID0504_FU_VLTSU_SE                 (17U)            /* Sender voltage Table Array(V) Ana Sub: SE                    */
#define CALIB_MCUID0505_FU_SEGLITMA                 (CALIB_FU_MA_SEG)/* Remaining amount Table Array(L) Seg Main: Num of Arrays      */
#define CALIB_MCUID0518_FU_SEGVLTMA                 (CALIB_FU_MA_SEG)/* Sender voltage Table Array(V) Seg Main: Num of Arrays        */
#define CALIB_MCUID0531_FU_SEGLITSU                 (CALIB_FU_SU_SEG)/* Remaining amount Table Array(L) Seg Sub: Num of Arrays       */
#define CALIB_MCUID0544_FU_SEGVLTSU                 (CALIB_FU_SU_SEG)/* Sender voltage Table Array(V) Seg Sub: Num of Arrays         */
#define CALIB_TOTAL_MAIN_AND_SUB_MAX                (35000U)         /* Main and Sub Lit MAX 0433-0450,0469-0486,0505-0517,0531-0543 */
#define CALIB_SOUND_PRESS_RATE_MIN                  (0U)             /* Sound Pressure Rate MIN MCUID0027-0039,0067-0208,0744-0753   */
#define CALIB_SOUND_PRESS_RATE_MAX                  (100U)           /* Sound Pressure Rate MAX MCUID0027-0039,0067-0208,0744-0753   */
#define CALIB_SP_TOLER_CORPT_NUM                    (20U)            /* Num of Speed Toler Cor Points MCUID0757-0776,0777-0796       */
#define CALIB_MCUID0809_MEXICO_LOW_MIN              (0U)             /* Mexico lows and regulations MIN                              */
#define CALIB_MCUID0809_MEXICO_LOW_MAX              (1U)             /* Mexico lows and regulations MAX                              */
#define CALIB_MCUID0810_KOREA_LOW_MIN               (0U)             /* Korea lows and regulations MIN                               */
#define CALIB_MCUID0810_KOREA_LOW_MAX               (1U)             /* Korea lows and regulations MAX                               */
#define CALIB_MCUID0028_SBW_SI_MID_MIN              (0U)             /* SBW reverse buzzer Single MID MIN                            */
#define CALIB_MCUID0028_SBW_SI_MID_MAX              (100U)           /* SBW reverse buzzer Single MID MAX                            */
#define CALIB_MCUID0745_SBW_SI_MAX_MIN              (0U)             /* SBW reverse buzzer Single MAX MIN                            */
#define CALIB_MCUID0745_SBW_SI_MAX_MAX              (100U)           /* SBW reverse buzzer Single MAX MAX                            */
#define CALIB_MCUID0238_XVMODE_MIN                  (0U)             /* XV Mode MIN                                                  */
#define CALIB_MCUID0238_XVMODE_MAX                  (1U)             /* XV Mode MAX                                                  */
#define CALIB_MCUID0240_FULMENP_MIN                 (0U)             /* FulMEnp MIN                                                  */
#define CALIB_MCUID0240_FULMENP_MAX                 (U2_MAX)         /* FulMEnp MAX                                                  */
#define CALIB_MCUID0338_EXDIMOUT_MIN                (0U)             /* external dimming output MIN                                  */
#define CALIB_MCUID0338_EXDIMOUT_MAX                (1U)             /* external dimming output MAX                                  */
#define CALIB_MCUID0339_EXDIMOUT_SPD_MIN            (0U)             /* external dimming output(vehicle speed linkage) MIN           */
#define CALIB_MCUID0339_EXDIMOUT_SPD_MAX            (1U)             /* external dimming output(vehicle speed linkage) MAX           */
#define CALIB_MCUID0608_OLPTLP_MIN                  (0U)             /* OLPtlP MIN                                                   */
#define CALIB_MCUID0608_OLPTLP_MAX                  (U2_MAX)         /* OLPtlP MAX                                                   */
#define CALIB_MCUID0622_OLTTLP_MIN                  (0U)             /* OLTtlP MIN                                                   */
#define CALIB_MCUID0622_OLTTLP_MAX                  (U2_MAX)         /* OLTtlP MAX                                                   */
#define CALIB_MCUID0630_TTLP_MIN                    (0U)             /* TtlP MIN                                                     */
#define CALIB_MCUID0630_TTLP_MAX                    (U2_MAX)         /* TtlP MAX                                                     */
#define CALIB_MCUID0644_RZ_RPM_MAX_MIN              (0U)             /* Red Zone RPM MAX MIN                                         */
#define CALIB_MCUID0644_RZ_RPM_MAX_MAX              (U2_MAX)         /* Red Zone RPM MAX MAX                                         */
#define CALIB_MCUID0645_RZ_RPM_MIN_MIN              (0U)             /* Red Zone RPM MIN MIN                                         */
#define CALIB_MCUID0645_RZ_RPM_MIN_MAX              (U2_MAX)         /* Red Zone RPM MIN MAX                                         */
#define CALIB_MCUID0646_TACHO_IND_MIN               (0U)             /* Tacho IND MIN                                                */
#define CALIB_MCUID0646_TACHO_IND_MAX               (1U)             /* Tacho IND MAX                                                */
#define CALIB_MCUID0722_LUD_MIN                     (0U)             /* LUD MIN                                                      */
#define CALIB_MCUID0722_LUD_MAX                     (1U)             /* LUD MAX                                                      */
#define CALIB_MCUID3000_RAIN_SEN_ADJ_MIN            (1U)             /* Raindrop Sensitivity Adjustment Steps MIN                    */
#define CALIB_MCUID3000_RAIN_SEN_ADJ_MAX            (8U)             /* Raindrop Sensitivity Adjustment Steps MAX                    */
#define CALIB_MCUID3001_INT_TIM_ADJ_MIN             (1U)             /* INT Time Adjustment Steps MIN                                */
#define CALIB_MCUID3001_INT_TIM_ADJ_MAX             (8U)             /* INT Time Adjustment Steps MAX                                */


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern volatile const U1 u1_CALIB_MCUID0001_MCUID1;        /* MCU Software version No.1                                              */
extern volatile const U1 u1_CALIB_MCUID0002_MCUID2;        /* MCU Software version No.2                                              */
extern volatile const U1 u1_CALIB_MCUID0003_MCUID3;        /* MCU Software version No.3                                              */
extern volatile const U1 u1_CALIB_MCUID0004_MCUID4;        /* MCU Software version No.4                                              */
extern volatile const U1 u1_CALIB_MCUID0005_MCUID5;        /* MCU Software version No.5                                              */
extern volatile const U1 u1_CALIB_MCUID0006_MCUID6;        /* MCU Software version No.6                                              */
extern volatile const U1 u1_CALIB_MCUID0007_MCUID7;        /* MCU Software version No.7                                              */
extern volatile const U1 u1_CALIB_MCUID0008_MCUID8;        /* MCU Software version No.8                                              */
extern volatile const U1 u1_CALIB_MCUID0009_MCUID9;        /* MCU Software version No.9                                              */
extern volatile const U1 u1_CALIB_MCUID0010_MCUID10;       /* MCU Software version No.10                                             */
extern volatile const U1 u1_CALIB_MCUID0011_MCUID11;       /* MCU Software version No.11                                             */
extern volatile const U1 u1_CALIB_MCUID0012_MCUID12;       /* MCU Software version No.12                                             */
extern volatile const U1 u1_CALIB_MCUID0013_SPDID1;        /* Speed Meter ID No.1                                                    */
extern volatile const U1 u1_CALIB_MCUID0014_SPDID2;        /* Speed Meter ID No.2                                                    */
extern volatile const U1 u1_CALIB_MCUID0015_SPDID3;        /* Speed Meter ID No.3                                                    */
extern volatile const U1 u1_CALIB_MCUID0016_SPDID4;        /* Speed Meter ID No.4                                                    */
extern volatile const U1 u1_CALIB_MCUID0017_SPDID5;        /* Speed Meter ID No.5                                                    */
extern volatile const U1 u1_CALIB_MCUID0018_SPDID6;        /* Speed Meter ID No.6                                                    */
extern volatile const U1 u1_CALIB_MCUID0019_SPDID7;        /* Speed Meter ID No.7                                                    */
extern volatile const U1 u1_CALIB_MCUID0020_SPDID8;        /* Speed Meter ID No.8                                                    */
extern volatile const U1 u1_CALIB_MCUID0021_HUDSW;         /* HUD MAIN Hard SW                                                       */
extern volatile const U1 u1_CALIB_MCUID0022_FU_MA;         /* Fuel Main Sender                                                       */
extern volatile const U1 u1_CALIB_MCUID0023_DISPTYPE;      /* Display Type                                                           */
extern volatile const U1 u1_CALIB_MCUID0024_BRAND;         /* Brand                                                                  */
extern volatile const U1 u1_CALIB_MCUID0025_SPORTS;        /* Sports Switching                                                       */
extern volatile const U1 u1_CALIB_MCUID0026_1MOTHV;        /* 1MOT HV Drive Wheel                                                    */
extern volatile const U1 u1_CALIB_MCUID3002_ANUNC_MID;     /* Annunciation Sound MID                                                 */
extern volatile const U1 u1_CALIB_MCUID3003_ANUNC_SP_MID;  /* Annunciation Sound(SP) MID                                             */
extern volatile const U1 u1_CALIB_MCUID3004_RECEP_MID;     /* Reception Sound MID                                                    */
extern volatile const U1 u1_CALIB_MCUID3005_REJECT_MID;    /* Reject Sound MID                                                       */
extern volatile const U1 u1_CALIB_MCUID3006_URGEN_MIN_MID; /* Intermittent Sound(Degree of urgency MIN) MID                          */
extern volatile const U1 u1_CALIB_MCUID3007_URGEN_MID_MID; /* Intermittent Sound(Degree of urgency MID) MID                          */
extern volatile const U1 u1_CALIB_MCUID3008_URGEN_MAX_MID; /* Intermittent Sound(Degree of urgency MAX) MID                          */
extern volatile const U1 u1_CALIB_MCUID3009_CONTIN_MID;    /* Continuous Sound MID                                                   */
extern volatile const U1 u1_CALIB_MCUID3010_PREDOT_MID;    /* PreDOT Sound MID                                                       */
extern volatile const U1 u1_CALIB_MCUID3011_ANUNC_MAX;     /* Annunciation Sound MAX                                                 */
extern volatile const U1 u1_CALIB_MCUID3012_ANUNC_SP_MAX;  /* Annunciation Sound(SP) MAX                                             */
extern volatile const U1 u1_CALIB_MCUID3013_RECEP_MAX;     /* Reception Sound MAX                                                    */
extern volatile const U1 u1_CALIB_MCUID3014_REJECT_MAX;    /* Reject Sound MAX                                                       */
extern volatile const U1 u1_CALIB_MCUID3015_URGEN_MIN_MAX; /* Intermittent Sound(Degree of urgency MIN) MAX                          */
extern volatile const U1 u1_CALIB_MCUID3016_URGEN_MID_MAX; /* Intermittent Sound(Degree of urgency MID) MAX                          */
extern volatile const U1 u1_CALIB_MCUID3017_URGEN_MAX_MAX; /* Intermittent Sound(Degree of urgency MAX) MAX                          */
extern volatile const U1 u1_CALIB_MCUID3018_CONTIN_MAX;    /* Continuous Sound MAX                                                   */
extern volatile const U1 u1_CALIB_MCUID3019_PREDOT_MAX;    /* PreDOT Sound MAX                                                       */
extern volatile const U1 u1_CALIB_MCUID0027_ATR_MID;       /* AT reverse buzzer MID                                                  */
extern volatile const U1 u1_CALIB_MCUID0744_ATR_MAX;       /* AT reverse buzzer MAX                                                  */
extern volatile const U1 u1_CALIB_MCUID0028_SBW_SI_MID;    /* SBW reverse buzzer Single MID                                          */
extern volatile const U1 u1_CALIB_MCUID0745_SBW_SI_MAX;    /* SBW reverse buzzer Single MAX                                          */
extern volatile const U1 u1_CALIB_MCUID0029_SBW_IN_MID;    /* SBW reverse buzzer Intermittent MID                                    */
extern volatile const U1 u1_CALIB_MCUID0746_SBW_IN_MAX;    /* SBW reverse buzzer Intermittent MAX                                    */
extern volatile const U1 u1_CALIB_MCUID0030_SBELT_FMV_MID; /* seatbelt reminder buzzer(fmv) MID                                      */
extern volatile const U1 u1_CALIB_MCUID0747_SBELT_FMV_MAX; /* seatbelt reminder buzzer(fmv) MAX                                      */
extern volatile const U1 u1_CALIB_MCUID0031_SBELT_LV1_MID; /* seatbelt reminder buzzer(level 1) MID                                  */
extern volatile const U1 u1_CALIB_MCUID0748_SBELT_LV1_MAX; /* seatbelt reminder buzzer(level 1) MAX                                  */
extern volatile const U1 u1_CALIB_MCUID0032_SBELT_LV2_MID; /* seatbelt reminder buzzer(level 2) MID                                  */
extern volatile const U1 u1_CALIB_MCUID0749_SBELT_LV2_MAX; /* seatbelt reminder buzzer(level 2) MAX                                  */
extern volatile const U1 u1_CALIB_MCUID0033_SBELT_SI_MID;  /* seatbelt reminder buzzer(si) MID                                       */
extern volatile const U1 u1_CALIB_MCUID0750_SBELT_SI_MAX;  /* seatbelt reminder buzzer(si) MAX                                       */
extern volatile const U1 u1_CALIB_MCUID0034_MC_MIN;        /* Master Caution MIN                                                     */
extern volatile const U1 u1_CALIB_MCUID0035_MC_MID;        /* Master Caution MID                                                     */
extern volatile const U1 u1_CALIB_MCUID0036_MC_MAX;        /* Master Caution MAX                                                     */
extern volatile const U1 u1_CALIB_MCUID0037_ACC_MID;       /* ACC Auto Start MID                                                     */
extern volatile const U1 u1_CALIB_MCUID0751_ACC_MAX;       /* ACC Auto Start MAX                                                     */
extern volatile const U1 u1_CALIB_MCUID0038_TMN_MID;       /* TMN MID                                                                */
extern volatile const U1 u1_CALIB_MCUID0752_TMN_MAX;       /* TMN MAX                                                                */
extern volatile const U1 u1_CALIB_MCUID0039_ADAS_MID;      /* ADAS MID                                                               */
extern volatile const U1 u1_CALIB_MCUID0753_ADAS_MAX;      /* ADAS MAX                                                               */
extern volatile const U1 u1_CALIB_MCUID0067_CSR_FRSD0;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0068_CSR_FRSD1;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0069_CSR_FRSD2;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0070_CSR_FRSD3;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0071_CSR_FRSD4;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0072_CSR_FRSD5;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0073_CSR_FRSD6;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0074_CSR_FRSD7;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0075_CSR_FRMD0;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0076_CSR_FRMD1;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0077_CSR_FRMD2;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0078_CSR_FRMD3;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0079_CSR_FRMD4;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0080_CSR_FRMD5;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0081_CSR_FRMD6;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0082_CSR_FRMD7;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0083_CSR_FRLD0;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0084_CSR_FRLD1;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0085_CSR_FRLD2;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0086_CSR_FRLD3;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0087_CSR_FRLD4;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0088_CSR_FRLD5;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0089_CSR_FRLD6;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0090_CSR_FRLD7;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0091_CSR_FRFD0;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0092_CSR_FRFD1;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0093_CSR_FRFD2;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0094_CSR_FRFD3;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0095_CSR_FRFD4;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0096_CSR_FRFD5;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0097_CSR_FRFD6;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0098_CSR_FRFD7;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0099_CSR_RRSD0;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0100_CSR_RRSD1;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0101_CSR_RRSD2;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0102_CSR_RRSD3;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0103_CSR_RRSD4;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0104_CSR_RRSD5;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0105_CSR_RRSD6;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0106_CSR_RRSD7;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0107_CSR_RRMD0;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0108_CSR_RRMD1;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0109_CSR_RRMD2;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0110_CSR_RRMD3;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0111_CSR_RRMD4;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0112_CSR_RRMD5;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0113_CSR_RRMD6;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0114_CSR_RRMD7;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0115_CSR_RRLD0;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0116_CSR_RRLD1;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0117_CSR_RRLD2;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0118_CSR_RRLD3;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0119_CSR_RRLD4;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0120_CSR_RRLD5;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0121_CSR_RRLD6;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0122_CSR_RRLD7;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0123_CSR_RRFD0;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:0                                */
extern volatile const U1 u1_CALIB_MCUID0124_CSR_RRFD1;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:1                                */
extern volatile const U1 u1_CALIB_MCUID0125_CSR_RRFD2;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:2                                */
extern volatile const U1 u1_CALIB_MCUID0126_CSR_RRFD3;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:3                                */
extern volatile const U1 u1_CALIB_MCUID0127_CSR_RRFD4;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:4                                */
extern volatile const U1 u1_CALIB_MCUID0128_CSR_RRFD5;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:5                                */
extern volatile const U1 u1_CALIB_MCUID0129_CSR_RRFD6;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:6                                */
extern volatile const U1 u1_CALIB_MCUID0130_CSR_RRFD7;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:7                                */
extern volatile const U1 u1_CALIB_MCUID0131_CSR_FRRRSD0;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0                             */
extern volatile const U1 u1_CALIB_MCUID0132_CSR_FRRRSD1;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1                             */
extern volatile const U1 u1_CALIB_MCUID0133_CSR_FRRRSD2;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2                             */
extern volatile const U1 u1_CALIB_MCUID0134_CSR_FRRRSD3;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3                             */
extern volatile const U1 u1_CALIB_MCUID0135_CSR_FRRRSD4;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4                             */
extern volatile const U1 u1_CALIB_MCUID0136_CSR_FRRRSD5;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5                             */
extern volatile const U1 u1_CALIB_MCUID0137_CSR_FRRRSD6;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6                             */
extern volatile const U1 u1_CALIB_MCUID0138_CSR_FRRRSD7;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7                             */
extern volatile const U1 u1_CALIB_MCUID0139_CSR_FRRRFRMD0; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0140_CSR_FRRRFRMD1; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0141_CSR_FRRRFRMD2; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0142_CSR_FRRRFRMD3; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0143_CSR_FRRRFRMD4; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0144_CSR_FRRRFRMD5; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0145_CSR_FRRRFRMD6; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0146_CSR_FRRRFRMD7; /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0147_CSR_FRRRRRMD0; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0148_CSR_FRRRRRMD1; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0149_CSR_FRRRRRMD2; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0150_CSR_FRRRRRMD3; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0151_CSR_FRRRRRMD4; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0152_CSR_FRRRRRMD5; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0153_CSR_FRRRRRMD6; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0154_CSR_FRRRRRMD7; /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0155_CSR_FRRRFRLD0; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0156_CSR_FRRRFRLD1; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0157_CSR_FRRRFRLD2; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0158_CSR_FRRRFRLD3; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0159_CSR_FRRRFRLD4; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0160_CSR_FRRRFRLD5; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0161_CSR_FRRRFRLD6; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0162_CSR_FRRRFRLD7; /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0163_CSR_FRRRRRLD0; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0164_CSR_FRRRRRLD1; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0165_CSR_FRRRRRLD2; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0166_CSR_FRRRRRLD3; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0167_CSR_FRRRRRLD4; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0168_CSR_FRRRRRLD5; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0169_CSR_FRRRRRLD6; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0170_CSR_FRRRRRLD7; /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0171_CSR_FRRRFRFD0; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0172_CSR_FRRRFRFD1; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0173_CSR_FRRRFRFD2; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0174_CSR_FRRRFRFD3; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0175_CSR_FRRRFRFD4; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0176_CSR_FRRRFRFD5; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0177_CSR_FRRRFRFD6; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0178_CSR_FRRRFRFD7; /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0179_CSR_FRRRRRFD0; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:0                         */
extern volatile const U1 u1_CALIB_MCUID0180_CSR_FRRRRRFD1; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:1                         */
extern volatile const U1 u1_CALIB_MCUID0181_CSR_FRRRRRFD2; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:2                         */
extern volatile const U1 u1_CALIB_MCUID0182_CSR_FRRRRRFD3; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:3                         */
extern volatile const U1 u1_CALIB_MCUID0183_CSR_FRRRRRFD4; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:4                         */
extern volatile const U1 u1_CALIB_MCUID0184_CSR_FRRRRRFD5; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:5                         */
extern volatile const U1 u1_CALIB_MCUID0185_CSR_FRRRRRFD6; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:6                         */
extern volatile const U1 u1_CALIB_MCUID0186_CSR_FRRRRRFD7; /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:7                         */
extern volatile const U1 u1_CALIB_MCUID0187_FLSTA_LOLO;    /* flasher start sound(low customize, low speed)                          */
extern volatile const U1 u1_CALIB_MCUID0188_FLSTA_LOMI;    /* flasher start sound(low customize, mid speed)                          */
extern volatile const U1 u1_CALIB_MCUID0189_FLSTA_LOHI;    /* flasher start sound(low customize, high speed)                         */
extern volatile const U1 u1_CALIB_MCUID0190_FLSTA_MILO;    /* flasher start sound(mid customize, low speed)                          */
extern volatile const U1 u1_CALIB_MCUID0191_FLSTA_MIMI;    /* flasher start sound(mid customize, mid speed)                          */
extern volatile const U1 u1_CALIB_MCUID0192_FLSTA_MIHI;    /* flasher start sound(mid customize, high speed)                         */
extern volatile const U1 u1_CALIB_MCUID0193_FLSTA_HILO;    /* flasher start sound(high customize, low speed)                         */
extern volatile const U1 u1_CALIB_MCUID0194_FLSTA_HIMI;    /* flasher start sound(high customize, mid speed)                         */
extern volatile const U1 u1_CALIB_MCUID0195_FLSTA_HIHI;    /* flasher start sound(high customize, high speed)                        */
extern volatile const U1 u1_CALIB_MCUID0196_FLFIN_LOLO;    /* flasher finish sound(low customize, low speed)                         */
extern volatile const U1 u1_CALIB_MCUID0197_FLFIN_LOMI;    /* flasher finish sound(low customize, mid speed)                         */
extern volatile const U1 u1_CALIB_MCUID0198_FLFIN_LOHI;    /* flasher finish sound(low customize, high speed)                        */
extern volatile const U1 u1_CALIB_MCUID0199_FLFIN_MILO;    /* flasher finish sound(mid customize, low speed)                         */
extern volatile const U1 u1_CALIB_MCUID0200_FLFIN_MIMI;    /* flasher finish sound(mid customize, mid speed)                         */
extern volatile const U1 u1_CALIB_MCUID0201_FLFIN_MIHI;    /* flasher finish sound(mid customize, high speed)                        */
extern volatile const U1 u1_CALIB_MCUID0202_FLFIN_HILO;    /* flasher finish sound(high customize, low speed)                        */
extern volatile const U1 u1_CALIB_MCUID0203_FLFIN_HIMI;    /* flasher finish sound(high customize, mid speed)                        */
extern volatile const U1 u1_CALIB_MCUID0204_FLFIN_HIHI;    /* flasher finish sound(high customize, high speed)                       */
extern volatile const U1 u1_CALIB_MCUID0205_2CH;           /* 2 channels multiplex playing                                           */
extern volatile const U1 u1_CALIB_MCUID0206_3CH;           /* 3 channels multiplex playing                                           */
extern volatile const U1 u1_CALIB_MCUID0207_4CH;           /* 4 channels multiplex playing                                           */
extern volatile const U1 u1_CALIB_MCUID0208_5CH;           /* 5 channels multiplex playing                                           */
extern volatile const U1 u1_CALIB_MCUID0209_RRCYM;         /* RRCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0210_RLCYM;         /* RLCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0211_BCTYM;         /* BCTYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0212_LGCYM;         /* LGCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0213_HDCY_BDBM;     /* HDCY_BDBM                                                              */
extern volatile const U1 u1_CALIB_MCUID0214_RPSDWARNM;     /* RPSDWARNM                                                              */
extern volatile const U1 u1_CALIB_MCUID0215_LPSDWARNM;     /* LPSDWARNM                                                              */
extern volatile const U1 u1_CALIB_MCUID0217_STR_ANG;       /* steering angle gauge                                                   */
extern volatile const U1 u1_CALIB_MCUID0218_ACCELERATOR;   /* accelerator brake                                                      */
extern volatile const U1 u1_CALIB_MCUID0219_G_GAUGE_MAX;   /* G_Gauge MAX                                                            */
extern volatile const U1 u1_CALIB_MCUID0220_GTRAJECTORY2;  /* GTrajectory2                                                           */
extern volatile const U1 u1_CALIB_MCUID0221_G_DISP_MAX;    /* G_Display MAX                                                          */
extern volatile const U1 u1_CALIB_MCUID0222_P_SEATSW;      /* P Seat Senser SW                                                       */
extern volatile const U1 u1_CALIB_MCUID0223_FRCTR_SEATSW;  /* FrCtr Seat Senser SW                                                   */
extern volatile const U1 u1_CALIB_MCUID0224_RR_SEATSW;     /* RR Seat Senser SW                                                      */
extern volatile const U1 u1_CALIB_MCUID0225_RC_SEATSW;     /* RC Seat Senser SW                                                      */
extern volatile const U1 u1_CALIB_MCUID0226_RL_SEATSW;     /* RL Seat Senser SW                                                      */
extern volatile const U1 u1_CALIB_MCUID0227_RR2_SEATSW;    /* RR2 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0228_RC2_SEATSW;    /* RC2 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0229_RL2_SEATSW;    /* RL2 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0230_RR3_SEATSW;    /* RR3 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0231_RC3_SEATSW;    /* RC3 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0232_RL3_SEATSW;    /* RL3 Seat Senser SW                                                     */
extern volatile const U1 u1_CALIB_MCUID0233_RDOOR;         /* Rear Seat Door                                                         */
extern volatile const U1 u1_CALIB_MCUID0234_WALKTHROUGH;   /* Walkthrough                                                            */
extern volatile const U1 u1_CALIB_MCUID0235_BODYSHAPE;     /* Bodyshape                                                              */
extern volatile const U1 u1_CALIB_MCUID0236_NOOPTTM;       /* NoOptTm                                                                */
extern volatile const U1 u1_CALIB_MCUID0237_CANMOVEFLAG;   /* NE1 or RDYIND                                                          */
extern volatile const U1 u1_CALIB_MCUID0238_XVMODE;        /* XV Mode                                                                */
extern volatile const U2 u2_CALIB_MCUID0239_FULFUL;        /* FulFul                                                                 */
extern volatile const U2 u2_CALIB_MCUID0240_FULMENP;       /* FulMEnp                                                                */
extern volatile const U4 u4_CALIB_MCUID0241_FULEFF;        /* FulEff                                                                 */
extern volatile const U1 u1_CALIB_MCUID0242_DDFFUCE;       /* DDFFuCe                                                                */
extern volatile const U1 u1_CALIB_MCUID0243_DKHCOEF;       /* DKHCoef                                                                */
extern volatile const U4 u4_CALIB_MCUID0244_EFFUPR;        /* EFFUPR                                                                 */
extern volatile const U4 u4_CALIB_MCUID0245_EFFLOW;        /* EFFLOW                                                                 */
extern volatile const U1 u1_CALIB_MCUID0246_FULCOEF;       /* FulCoef                                                                */
extern volatile const U1 u1_CALIB_MCUID0247_GCOEFM;        /* GCoefM                                                                 */
extern volatile const U1 u1_CALIB_MCUID0248_GCOEFC;        /* GcoefC                                                                 */
extern volatile const U1 u1_CALIB_MCUID0249_GCOEFP;        /* GCoefP                                                                 */
extern volatile const U1 u1_CALIB_MCUID0250_FE_CONV;       /* fuel efficiency CONV                                                   */
extern volatile const U1 u1_CALIB_MCUID0251_FE_HV;         /* fuel efficiency HV                                                     */
extern volatile const U1 u1_CALIB_MCUID0252_FE_PHV;        /* fuel efficiency PHV                                                    */
extern volatile const U1 u1_CALIB_MCUID0253_FE_FC;         /* fuel efficiency FC                                                     */
extern volatile const U1 u1_CALIB_MCUID0254_PE_PHV;        /* power expense PHV                                                      */
extern volatile const U1 u1_CALIB_MCUID0255_PE_EV;         /* power expense EV                                                       */
extern volatile const U1 u1_CALIB_MCUID0256_TOLA_USA_CAN;  /* TOLER_A USA/CANADA                                                     */
extern volatile const S1 s1_CALIB_MCUID0257_TOLB_USA_CAN;  /* TOLER_B USA/CANADA                                                     */
extern volatile const U1 u1_CALIB_MCUID0260_TOLA_UNR_AUS;  /* TOLER_A UNR/AUS                                                        */
extern volatile const S1 s1_CALIB_MCUID0261_TOLB_UNR_AUS;  /* TOLER_B UNR/AUS                                                        */
extern volatile const U2 u2_CALIB_MCUID0262_MAXSPEED_KM;   /* Max Speed km                                                           */
extern volatile const U2 u2_CALIB_MCUID0263_MAXSPEED_MPH;  /* Max Speed mph                                                          */
extern volatile const U1 u1_CALIB_MCUID0264_FSPO;          /* Fspo                                                                   */
extern volatile const U1 u1_CALIB_MCUID0265_REVIND;        /* REVIND                                                                 */
extern volatile const U2 u2_CALIB_MCUID0266_REVINIT;       /* RevInit                                                                */
extern volatile const U1 u1_CALIB_MCUID0267_REVLSB;        /* RevLSB                                                                 */
extern volatile const U1 u1_CALIB_MCUID0268_SWNUM;         /* SWnum                                                                  */
extern volatile const U1 u1_CALIB_MCUID0269_SWPOSI;        /* SWposi                                                                 */
extern volatile const U1 u1_CALIB_MCUID0336_ILLOF_LV;      /* ILL_OF Level                                                           */
extern volatile const U1 u1_CALIB_MCUID0337_ILLOF_CAN_LV;  /* ILL_OF Cancel Level                                                    */
extern volatile const U1 u1_CALIB_MCUID0338_EXDIMOUT;      /* external dimming output                                                */
extern volatile const U1 u1_CALIB_MCUID0339_EXDIMOUT_SPD;  /* external dimming output(vehicle speed linkage)                         */
extern volatile const U1 u1_CALIB_MCUID0340_RHEOPOS_NIGHT; /* Rheostat Position Night                                                */
extern volatile const U1 u1_CALIB_MCUID0341_TAIL;          /* TAIL Apply                                                             */
extern volatile const U1 u1_CALIB_MCUID0430_RHEOSW;        /* Rheostat SW Apply                                                      */
extern volatile const U1 u1_CALIB_MCUID0432_LIDINFO;       /* LSTM or LST1                                                           */
extern volatile const U1 u1_CALIB_MCUID0557_SHTJDG;        /* ShtJdg                                                                 */
extern volatile const U1 u1_CALIB_MCUID0558_FSTYPE;        /* FStype                                                                 */
extern volatile const U2 u2_CALIB_MCUID0559_FOPEN;         /* FOpen                                                                  */
extern volatile const U1 u1_CALIB_MCUID0560_ATCALNUM;      /* ATCaluNum                                                              */
extern volatile const U2 u2_CALIB_MCUID0561_STPJDG;        /* StpJdg                                                                 */
extern volatile const U2 u2_CALIB_MCUID0562_LUBJDGPN;      /* LubJdgPN                                                               */
extern volatile const U2 u2_CALIB_MCUID0563_LUBJDGPL;      /* LubJdgPL                                                               */
extern volatile const U2 u2_CALIB_MCUID0564_UPDATEJDG;     /* UpdateJdg                                                              */
extern volatile const U2 u2_CALIB_MCUID0565_REMWRNON;      /* RemWrnOn                                                               */
extern volatile const U2 u2_CALIB_MCUID0566_FC_HOSEI;      /* FC_Hosei                                                               */
extern volatile const U2 u2_CALIB_MCUID0567_AUTOSTOPL;     /* AutoSTOPL                                                              */
extern volatile const U2 u2_CALIB_MCUID0568_MINJUDGEL;     /* MinjudgeL                                                              */
extern volatile const U2 u2_CALIB_MCUID0569_NSLTNKSP;      /* NslTnkSP                                                               */
extern volatile const U1 u1_CALIB_MCUID0570_KMINVAL;       /* Kminval                                                                */
extern volatile const U1 u1_CALIB_MCUID0571_KMAXVAL;       /* Kmaxval                                                                */
extern volatile const U1 u1_CALIB_MCUID0572_FU_PORTPOS;    /* Fuel Port Position                                                     */
extern volatile const U1 u1_CALIB_MCUID0573_FU_SU;         /* Fuel Sub Sender                                                        */
extern volatile const U2 u2_CALIB_MCUID0574_CAL_DEF;       /* CAL_DEF                                                                */
extern volatile const U2 u2_CALIB_MCUID0575_CAL_MIN;       /* CAL_MIN                                                                */
extern volatile const U1 u1_CALIB_MCUID0576_DEGCW;         /* DegCW                                                                  */
extern volatile const U1 u1_CALIB_MCUID0577_DEGCCW;        /* DegCCW                                                                 */
extern volatile const U1 u1_CALIB_MCUID0578_DEG_RTSTEP;    /* Deg_RTStep                                                             */
extern volatile const U1 u1_CALIB_MCUID0579_RESTIME;       /* ResTime                                                                */
extern volatile const U1 u1_CALIB_MCUID0580_ACONMVAVECNT;  /* ACon_MvAveCnt                                                          */
extern volatile const U1 u1_CALIB_MCUID0581_ACONUPAVECNT;  /* ACon_UpAveCnt                                                          */
extern volatile const U1 u1_CALIB_MCUID0582_ACONDNAVECNT;  /* ACon_DnAveCnt                                                          */
extern volatile const U1 u1_CALIB_MCUID0583_ATSSAORNA;     /* ATss_AorNA                                                             */
extern volatile const U1 u1_CALIB_MCUID0584_ATSSUPAVECNT;  /* ATss_UpAveCnt                                                          */
extern volatile const U1 u1_CALIB_MCUID0585_ATSSDNAVECNT;  /* ATss_DnAveCnt                                                          */
extern volatile const U1 u1_CALIB_MCUID0586_HUDLMAVECNT;   /* HUDLm_AveCnt                                                           */
extern volatile const U1 u1_CALIB_MCUID0588_OM_MLG;        /* OM_MLG                                                                 */
extern volatile const U1 u1_CALIB_MCUID0589_PR_OM_FL;      /* PR_OM_FL                                                               */
extern volatile const U1 u1_CALIB_MCUID0590_SOC_PORTPOS;   /* SOC Port Position                                                      */
extern volatile const U1 u1_CALIB_MCUID0591_UREA;          /* UREA Apply                                                             */
extern volatile const U1 u1_CALIB_MCUID0592_SBELT_TT;      /* SeatBelt Reminder Telltale Type                                        */
extern volatile const U1 u1_CALIB_MCUID0593_ATTEMP_LO;     /* ATTEMP_LO                                                              */
extern volatile const U1 u1_CALIB_MCUID0594_ATTEMP_MIDL;   /* ATTEMP_MIDL                                                            */
extern volatile const U1 u1_CALIB_MCUID0595_ATTEMP_MIDH;   /* ATTEMP_MIDH                                                            */
extern volatile const U1 u1_CALIB_MCUID0596_ATTEMP_HI;     /* ATTEMP_HI                                                              */
extern volatile const U1 u1_CALIB_MCUID0597_FLASHSTART;    /* Flash_Start                                                            */
extern volatile const U1 u1_CALIB_MCUID0598_FLASHSTOP;     /* Flash_Stop                                                             */
extern volatile const U1 u1_CALIB_MCUID0599_RZSTART;       /* Red_Zone_Start                                                         */
extern volatile const U1 u1_CALIB_MCUID0600_ATTEMPVAL_LO;  /* ATTEMPVAL_LO                                                           */
extern volatile const U1 u1_CALIB_MCUID0601_ATTEMPVAL_HI;  /* ATTEMPVAL_HI                                                           */
extern volatile const U1 u1_CALIB_MCUID0602_LAUNCHTIME;    /* LAUNCH_Time                                                            */
extern volatile const U1 u1_CALIB_MCUID0603_SBELT_USA;     /* SeatBelt Regulation USA                                                */
extern volatile const U1 u1_CALIB_MCUID0604_SBELT_MEXICO;  /* SeatBelt Regulation MEXICO                                             */
extern volatile const U1 u1_CALIB_MCUID0605_SBELT_EU;      /* SeatBelt Regulation EU                                                 */
extern volatile const U1 u1_CALIB_MCUID0606_SBELT_KOREA;   /* SeatBelt Regulation KOREA                                              */
extern volatile const U1 u1_CALIB_MCUID0607_SBELT_CHINA;   /* SeatBelt Regulation CHINA                                              */
extern volatile const U2 u2_CALIB_MCUID0608_OLPTLP;        /* OLPtlP                                                                 */
extern volatile const U2 u2_CALIB_MCUID0609_KPAOLPL;       /* kPaOLPL                                                                */
extern volatile const U2 u2_CALIB_MCUID0610_KPAOLPH;       /* kPaOLPH                                                                */
extern volatile const U2 u2_CALIB_MCUID0611_BAROLPL;       /* barOLPL                                                                */
extern volatile const U2 u2_CALIB_MCUID0612_BAROLPH;       /* barOLPH                                                                */
extern volatile const U2 u2_CALIB_MCUID0613_PSIOLPL;       /* psiOLPL                                                                */
extern volatile const U2 u2_CALIB_MCUID0614_PSIOLPH;       /* psiOLPH                                                                */
extern volatile const U1 u1_CALIB_MCUID0653_KPAOLPMAX;     /* kPaOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0654_KPAOLPMIN;     /* kPaOLPMin                                                              */
extern volatile const U1 u1_CALIB_MCUID0655_BAROLPMAX;     /* barOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0656_BAROLPMIN;     /* barOLPMin                                                              */
extern volatile const U1 u1_CALIB_MCUID0657_PSIOLPMAX;     /* psiOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0658_PSIOLPMIN;     /* psiOLPMin                                                              */
extern volatile const U2 u2_CALIB_MCUID0622_OLTTLP;        /* OLTtlP                                                                 */
extern volatile const U1 u1_CALIB_MCUID0623_OLTTLC;        /* OLTtlC                                                                 */
extern volatile const U1 u1_CALIB_MCUID0624_OLTTLH;        /* OLTtlH                                                                 */
extern volatile const U2 u2_CALIB_MCUID0625_OLTMAXC;       /* OLTMaxC                                                                */
extern volatile const U2 u2_CALIB_MCUID0626_OLTMINC;       /* OLTMinC                                                                */
extern volatile const U2 u2_CALIB_MCUID0627_OLTMAXF;       /* OLTMaxF                                                                */
extern volatile const U2 u2_CALIB_MCUID0628_OLTMINF;       /* OLTMinF                                                                */
extern volatile const U1 u1_CALIB_MCUID0629_HYS;           /* hys                                                                    */
extern volatile const U2 u2_CALIB_MCUID0630_TTLP;          /* TtlP                                                                   */
extern volatile const U1 u1_CALIB_MCUID0631_TTLC;          /* TtlC                                                                   */
extern volatile const U1 u1_CALIB_MCUID0632_TTLH;          /* TtlH                                                                   */
extern volatile const U2 u2_CALIB_MCUID0633_TTLMAXC;       /* TtlMaxC                                                                */
extern volatile const U2 u2_CALIB_MCUID0634_TTLMINC;       /* TtlMinC                                                                */
extern volatile const U2 u2_CALIB_MCUID0635_TTLMAXF;       /* TtlMaxF                                                                */
extern volatile const U2 u2_CALIB_MCUID0636_TTLMINF;       /* TtlMinF                                                                */
extern volatile const U1 u1_CALIB_MCUID0637_OVHT;          /* ovht                                                                   */
extern volatile const U1 u1_CALIB_MCUID0638_HYS;           /* hys                                                                    */
extern volatile const U1 u1_CALIB_MCUID0639_N1;            /* N1                                                                     */
extern volatile const U1 u1_CALIB_MCUID0640_N2;            /* N2                                                                     */
extern volatile const U2 u2_CALIB_MCUID0641_REVSET;        /* RevSet                                                                 */
extern volatile const U2 u2_CALIB_MCUID0642_REVDISPHYS;    /* RevDispHys                                                             */
extern volatile const U2 u2_CALIB_MCUID0643_REVNOISEHYS;   /* RevNoiseHys                                                            */
extern volatile const U2 u2_CALIB_MCUID0644_RZ_RPM_MAX;    /* Red Zone RPM MAX                                                       */
extern volatile const U2 u2_CALIB_MCUID0645_RZ_RPM_MIN;    /* Red Zone RPM MIN                                                       */
extern volatile const U1 u1_CALIB_MCUID0646_TACHO_IND;     /* Tacho IND                                                              */
extern volatile const U1 u1_CALIB_MCUID0647_METHVSYSIND;   /* MET HV System Indicator                                                */
extern volatile const U1 u1_CALIB_MCUID0648_HUDHVSYSIND;   /* HUD HV System Indicator                                                */
extern volatile const U1 u1_CALIB_MCUID0649_METNORM;       /* MET Normal Display                                                     */
extern volatile const U1 u1_CALIB_MCUID0650_HUDNORM;       /* HUD Normal Display                                                     */
extern volatile const U1 u1_CALIB_MCUID0651_HUDNORM1;      /* HUD Normal Display 1                                                   */
extern volatile const U1 u1_CALIB_MCUID0652_TC;            /* TC                                                                     */
extern volatile const U1 u1_CALIB_MCUID0659_MTSNORM;       /* MTS Normal Mode                                                        */
extern volatile const U1 u1_CALIB_MCUID0660_XMODE;         /* X-MODE                                                                 */
extern volatile const U1 u1_CALIB_MCUID0661_GFX_DISSWING;  /* GFX Dispay Switching                                                   */
extern volatile const U1 u1_CALIB_MCUID0662_0DIAL_VIEW;    /* 0dial-View ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0663_1DIAL_VIEW;    /* 1dial-View ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0664_2DIAL_VIEW;    /* 2dial-View ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0665_MAP_VIEW;      /* MAP-View ON/OFF Default                                                */
extern volatile const U1 u1_CALIB_MCUID0666_ADAS_VIEW;     /* ADAS-View ON/OFF Default                                               */
extern volatile const U1 u1_CALIB_MCUID0667_ECO_VIEW;      /* ECO-View ON/OFF Default                                                */
extern volatile const U1 u1_CALIB_MCUID0668_1DIAL_TR_VIEW; /* 1dial Track-View ON/OFF Default                                        */
extern volatile const U1 u1_CALIB_MCUID0669_SHTUPIND_VIEW; /* Shift Up Ind-View ON/OFF Default                                       */
extern volatile const U1 u1_CALIB_MCUID0670_OFFROAD_VIEW;  /* Off-Road-View ON/OFF Default                                           */
extern volatile const U1 u1_CALIB_MCUID0671_6DIAL_VIEW;    /* 6dial-View ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0672_FC_DEF;        /* Fuel Economy ON/OFF Default                                            */
extern volatile const U1 u1_CALIB_MCUID0673_PWR_DEF;       /* Power Consumption ON/OFF Default                                       */
extern volatile const U1 u1_CALIB_MCUID0674_PHEV_FC_DEF;   /* PHEV Fuel Economy ON/OFF Default                                       */
extern volatile const U1 u1_CALIB_MCUID0675_ECOIND_DEF;    /* Eco Indicator ON/OFF Default                                           */
extern volatile const U1 u1_CALIB_MCUID0676_ECOSCR_DEF;    /* HEV/FCEV Eco Score ON/OFF Default                                      */
extern volatile const U1 u1_CALIB_MCUID0677_EVRATIO;       /* EV Ratio ON/OFF Default                                                */
extern volatile const U1 u1_CALIB_MCUID0678_NAVI_DEF;      /* Navigation ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0679_AUDIO_DEF;     /* Audio ON/OFF Default                                                   */
extern volatile const U1 u1_CALIB_MCUID0680_DRVINFO_DEF;   /* Drive Info ON/OFF Default                                              */
extern volatile const U1 u1_CALIB_MCUID0681_TRIPA_DEF;     /* Trip A ON/OFF Default                                                  */
extern volatile const U1 u1_CALIB_MCUID0682_TRIPB_DEF;     /* Trip B ON/OFF Default                                                  */
extern volatile const U1 u1_CALIB_MCUID0683_EGMNTR_DEF;    /* Energy Monitor ON/OFF Default                                          */
extern volatile const U1 u1_CALIB_MCUID0684_TPMS_DEF;      /* TPMS ON/OFF Default                                                    */
extern volatile const U1 u1_CALIB_MCUID0685_4WD_DEF;       /* 4WD ON/OFF Default                                                     */
extern volatile const U1 u1_CALIB_MCUID0686_TRC_DEF;       /* TRC ON/OFF Default                                                     */
extern volatile const U1 u1_CALIB_MCUID0687_STR_DEF;       /* Steering angle ON/OFF Default                                          */
extern volatile const U1 u1_CALIB_MCUID0688_PTCHROLL_DEF;  /* Pitch and Roll ON/OFF Default                                          */
extern volatile const U1 u1_CALIB_MCUID0689_TRABRK_DEF;    /* Trailer Brake ON/OFF Default                                           */
extern volatile const U1 u1_CALIB_MCUID0690_TRABSM_DEF;    /* Trailer Mode BSM ON/OFF Default                                        */
extern volatile const U1 u1_CALIB_MCUID0691_VOLTMET_DEF;   /* Voltmeter ON/OFF Default                                               */
extern volatile const U1 u1_CALIB_MCUID0692_OILPRS_DEF;    /* Oil Pressure/Voltmeter ON/OFF Default                                  */
extern volatile const U1 u1_CALIB_MCUID0693_EATOILTMP_DEF; /* Engine/AT Oil Temp ON/OFF Default                                      */
extern volatile const U1 u1_CALIB_MCUID0694_EOILTMP_DEF;   /* Engine Oil Temp ON/OFF Default                                         */
extern volatile const U1 u1_CALIB_MCUID0695_ATOILTMP_DEF;  /* AT Oil Temp ON/OFF Default                                             */
extern volatile const U1 u1_CALIB_MCUID0696_TRBOGAG_W_L;   /* Turbo Gauge(CONV)(With Logo) ON/OFF Default                            */
extern volatile const U1 u1_CALIB_MCUID0697_TRBOGAG_WO_L;  /* Turbo Gauge(CONV)(Without Logo) ON/OFF Default                         */
extern volatile const U1 u1_CALIB_MCUID0698_BOSTGAG_W_L;   /* Boost Gauge(CONV)(With Logo) ON/OFF Default                            */
extern volatile const U1 u1_CALIB_MCUID0699_BOSTGAG_WO_L;  /* Boost Gauge(CONV)(Without Logo) ON/OFF Default                         */
extern volatile const U1 u1_CALIB_MCUID0700_MTRPWR;        /* Motor Power(48V-MHV) ON/OFF Default                                    */
extern volatile const U1 u1_CALIB_MCUID0701_SPRTSGAG;      /* Sports Gauges ON/OFF Default                                           */
extern volatile const U1 u1_CALIB_MCUID0702_GFORCE;        /* G-Force ON/OFF Default                                                 */
extern volatile const U1 u1_CALIB_MCUID0703_ADBLUE;        /* AdBlue ON/OFF Default                                                  */
extern volatile const U1 u1_CALIB_MCUID0704_ENGCNSMP;      /* Energy consumption ON/OFF Default                                      */
extern volatile const U1 u1_CALIB_MCUID0705_MET_CD_TACHO;  /* MET CENTER DIAL Tachometer                                             */
extern volatile const U1 u1_CALIB_MCUID0706_MET_CD_SPEED;  /* MET CENTER DIAL Speed                                                  */
extern volatile const U1 u1_CALIB_MCUID0707_MET_CD_HVIND;  /* MET CENTER DIAL HVIndicator                                            */
extern volatile const U1 u1_CALIB_MCUID0708_MET_CD_FCIND;  /* MET CENTER DIAL FCIndicator                                            */
extern volatile const U1 u1_CALIB_MCUID0709_MET_CD_PWR;    /* MET CENTER DIAL Pwrmeter                                               */
extern volatile const U1 u1_CALIB_MCUID0754_MET_CD_DRVMD;  /* MET CENTER DIAL DriveMode Interlocking                                 */
extern volatile const U1 u1_CALIB_MCUID0710_MET_LD_TACHO;  /* MET LEFT DIAL Tachometer                                               */
extern volatile const U1 u1_CALIB_MCUID0711_MET_LD_HVIND;  /* MET LEFT DIAL HVIndicator                                              */
extern volatile const U1 u1_CALIB_MCUID0712_MET_LD_FCIND;  /* MET LEFT DIAL FCIndicator                                              */
extern volatile const U1 u1_CALIB_MCUID0713_MET_LD_PWR;    /* MET LEFT DIAL Pwrmeter                                                 */
extern volatile const U1 u1_CALIB_MCUID0755_MET_LD_DRVMD;  /* MET LEFT DIAL DriveMode Interlocking                                   */
extern volatile const U1 u1_CALIB_MCUID0715_HUD_TACHO;     /* HUD AnalogTachometer                                                   */
extern volatile const U1 u1_CALIB_MCUID0716_HUD_ECOIND;    /* HUD AnalogEcodriveIndicator                                            */
extern volatile const U1 u1_CALIB_MCUID0717_HUD_HVIND;     /* HUD AnalogHVIndicator                                                  */
extern volatile const U1 u1_CALIB_MCUID0718_HUD_FCIND;     /* HUD FCIndicator                                                        */
extern volatile const U1 u1_CALIB_MCUID0719_HUD_PWR;       /* HUD Pwrmeter                                                           */
extern volatile const U1 u1_CALIB_MCUID0756_HUD_DRVMD;     /* HUD DriveMode Interlocking                                             */
extern volatile const U1 u1_CALIB_MCUID0720_PARK_S;        /* PARK_S                                                                 */
extern volatile const U1 u1_CALIB_MCUID0721_PARK;          /* PARK                                                                   */
extern volatile const U1 u1_CALIB_MCUID0722_LUD;           /* LUD                                                                    */
extern volatile const U1 u1_CALIB_MCUID0723_DIST_AFTSTRT;  /* Powertrain System Run Distance After starting                          */
extern volatile const U1 u1_CALIB_MCUID0726_DRVTM_AFTSTRT; /* Powertrain System Run Time After starting                              */
extern volatile const U1 u1_CALIB_MCUID0729_AVGFE_AFTSTRT; /* Average Fuel Economy After starting                                    */
extern volatile const U1 u1_CALIB_MCUID0732_EVRATIO;       /* EV Ratio                                                               */
extern volatile const U1 u1_CALIB_MCUID0735_AVGEE_AFTSTRT; /* Average Electric Economy After starting                                */
extern volatile const U2 u2_CALIB_MCUID0738_TIMEOUT_TM;    /* Timeout Time                                                           */
extern volatile const U1 u1_CALIB_MCUID0740_OILLVL_DEF;    /* Oil Level ON/OFF Default                                               */
extern volatile const U1 u1_CALIB_MCUID0741_IL2OUTILLRUN;  /* IL2OUTILLRun                                                           */
extern volatile const U2 u2_CALIB_MCUID0742_IOUTILLRUN;    /* IOUTILLRun                                                             */
extern volatile const U2 u2_CALIB_MCUID0743_IOUTILLRUNMAX; /* IOUTILLRunmax                                                          */
extern volatile const U1 u1_CALIB_MCUID0798_TRNLMPCLR;     /* Turn signal lamp color of your vehicle                                 */
extern volatile const U1 u1_CALIB_MCUID0809_MEXICO_LOW;    /* Mexico lows and regulations                                            */
extern volatile const U1 u1_CALIB_MCUID0810_KOREA_LOW;     /* Korea lows and regulations                                             */
extern volatile const U1 u1_CALIB_MCUID3000_RAIN_SEN_ADJ;  /* Raindrop Sensitivity Adjustment Steps                                  */
extern volatile const U1 u1_CALIB_MCUID3001_INT_TIM_ADJ;   /* INT Time Adjustment Steps                                              */
extern volatile const U1 u1_CALIB_MCUID0797_CNST_WRITEFLG; /* Constant write flag                                                    */
extern volatile const U1 u1_CALIB_MCUID0270_RHEO_PCT[CALIB_MCUID0270_RHEO_STEP];              /* MCUID0270 to MCUID0291              */
extern volatile const U2 u2_CALIB_MCUID0292_TR2_PCT[CALIB_MCUID0292_TR2_STEP];                /* MCUID0292 to MCUID0313              */
extern volatile const U2 u2_CALIB_MCUID0314_IL2_PCT[CALIB_MCUID0314_IL2_STEP];                /* MCUID0314 to MCUID0335              */
extern volatile const U1 u1_CALIB_MCUID0342_BL_PCT_DAY[CALIB_MCUID0342_BL_STEP_DAY];          /* MCUID0342 to MCUID0363              */
extern volatile const U1 u1_CALIB_MCUID0364_RGB_PCT_DAY[CALIB_MCUID0364_RGB_STEP_DAY];        /* MCUID0364 to MCUID0385              */
extern volatile const U1 u1_CALIB_MCUID0386_BL_PCT_NIGHT[CALIB_MCUID0386_BL_STEP_NIGHT];      /* MCUID0386 to MCUID0407              */
extern volatile const U1 u1_CALIB_MCUID0408_RGB_PCT_NIGHT[CALIB_MCUID0408_RGB_STEP_NIGHT];    /* MCUID0408 to MCUID0429              */
extern volatile const U2 u2_CALIB_MCUID0433_FU_ANALITMA[CALIB_MCUID0433_FU_ANALITMA];         /* MCUID0433 to MCUID0450              */
extern volatile const U2 u2_CALIB_MCUID0451_FU_ANAVLTMA[CALIB_MCUID0451_FU_ANAVLTMA];         /* MCUID0451 to MCUID0468              */
extern volatile const U2 u2_CALIB_MCUID0469_FU_ANALITSU[CALIB_MCUID0469_FU_ANALITSU];         /* MCUID0469 to MCUID0486              */
extern volatile const U2 u2_CALIB_MCUID0487_FU_ANAVLTSU[CALIB_MCUID0487_FU_ANAVLTSU];         /* MCUID0487 to MCUID0504              */
extern volatile const U2 u2_CALIB_MCUID0505_FU_SEGLITMA[CALIB_MCUID0505_FU_SEGLITMA];         /* MCUID0505 to MCUID0517              */
extern volatile const U2 u2_CALIB_MCUID0518_FU_SEGVLTMA[CALIB_MCUID0518_FU_SEGVLTMA];         /* MCUID0518 to MCUID0530              */
extern volatile const U2 u2_CALIB_MCUID0531_FU_SEGLITSU[CALIB_MCUID0531_FU_SEGLITSU];         /* MCUID0531 to MCUID0543              */
extern volatile const U2 u2_CALIB_MCUID0544_FU_SEGVLTSU[CALIB_MCUID0544_FU_SEGVLTSU];         /* MCUID0544 to MCUID0556              */
extern volatile const U2 u2_CALIB_MCUID0757_SP_USA_CAN[CALIB_SP_TOLER_CORPT_NUM];             /* MCUID0757 to MCUID0776              */
extern volatile const U2 u2_CALIB_MCUID0777_SP_UNR_AUS[CALIB_SP_TOLER_CORPT_NUM];             /* MCUID0777 to MCUID0796              */

#endif
