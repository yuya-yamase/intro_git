/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CALIBRATION                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CALIBRATION_DEF_H
#define CALIBRATION_DEF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CALIBRATION_DEF_H_MAJOR                     (1)
#define CALIBRATION_DEF_H_MINOR                     (4)
#define CALIBRATION_DEF_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CALIB_MCUID0001_DEF                         (56U)            /* MCU Software version No.1                                    */
#define CALIB_MCUID0002_DEF                         (65U)            /* MCU Software version No.2                                    */
#define CALIB_MCUID0003_DEF                         (52U)            /* MCU Software version No.3                                    */
#define CALIB_MCUID0004_DEF                         (65U)            /* MCU Software version No.4                                    */
#define CALIB_MCUID0005_DEF                         (49U)            /* MCU Software version No.5                                    */
#define CALIB_MCUID0006_DEF                         (52U)            /* MCU Software version No.6                                    */
#define CALIB_MCUID0007_DEF                         (55U)            /* MCU Software version No.7                                    */
#define CALIB_MCUID0008_DEF                         (48U)            /* MCU Software version No.8                                    */
#define CALIB_MCUID0009_DEF                         (50U)            /* MCU Software version No.9                                    */
#define CALIB_MCUID0010_DEF                         (48U)            /* MCU Software version No.10                                   */
#define CALIB_MCUID0011_DEF                         (48U)            /* MCU Software version No.11                                   */
#define CALIB_MCUID0012_DEF                         (48U)            /* MCU Software version No.12                                   */
#define CALIB_MCUID0013_DEF                         (32U)            /* Speed Meter ID No.1                                          */
#define CALIB_MCUID0014_DEF                         (32U)            /* Speed Meter ID No.2                                          */
#define CALIB_MCUID0015_DEF                         (32U)            /* Speed Meter ID No.3                                          */
#define CALIB_MCUID0016_DEF                         (32U)            /* Speed Meter ID No.4                                          */
#define CALIB_MCUID0017_DEF                         (32U)            /* Speed Meter ID No.5                                          */
#define CALIB_MCUID0018_DEF                         (32U)            /* Speed Meter ID No.6                                          */
#define CALIB_MCUID0019_DEF                         (32U)            /* Speed Meter ID No.7                                          */
#define CALIB_MCUID0020_DEF                         (32U)            /* Speed Meter ID No.8                                          */
#define CALIB_MCUID0024_DEF                         (0U)             /* Brand                                                        */
#define CALIB_MCUID0025_DEF                         (0U)             /* Sports Switching                                             */
#define CALIB_MCUID0209_DEF                         (0U)             /* RRCYM                                                        */
#define CALIB_MCUID0210_DEF                         (0U)             /* RLCYM                                                        */
#define CALIB_MCUID0211_DEF                         (0U)             /* BCTYM                                                        */
#define CALIB_MCUID0212_DEF                         (0U)             /* LGCYM                                                        */
#define CALIB_MCUID0213_DEF                         (0U)             /* HDCY_BDBM                                                    */
#define CALIB_MCUID0214_DEF                         (0U)             /* RPSDWARNM                                                    */
#define CALIB_MCUID0215_DEF                         (0U)             /* LPSDWARNM                                                    */
#define CALIB_MCUID_RSV_1B_0030_DEF                 (0U)             /* Reserve_1B_0030                                              */
#define CALIB_MCUID_RSV_1B_0031_DEF                 (0U)             /* Reserve_1B_0031                                              */
#define CALIB_MCUID0219_DEF                         (8U)             /* G_Gauge MAX                                                  */
#define CALIB_MCUID0220_DEF                         (0U)             /* GTrajectory2                                                 */
#define CALIB_MCUID0221_DEF                         (8U)             /* G_Display MAX                                                */
#define CALIB_MCUID0224_DEF                         (0U)             /* RR Seat Senser SW                                            */
#define CALIB_MCUID0225_DEF                         (0U)             /* RC Seat Senser SW                                            */
#define CALIB_MCUID0226_DEF                         (0U)             /* RL Seat Senser SW                                            */
#define CALIB_MCUID0227_DEF                         (0U)             /* RR2 Seat Senser SW                                           */
#define CALIB_MCUID0228_DEF                         (0U)             /* RC2 Seat Senser SW                                           */
#define CALIB_MCUID0229_DEF                         (0U)             /* RL2 Seat Senser SW                                           */
#define CALIB_MCUID0230_DEF                         (0U)             /* RR3 Seat Senser SW                                           */
#define CALIB_MCUID0231_DEF                         (0U)             /* RC3 Seat Senser SW                                           */
#define CALIB_MCUID0232_DEF                         (0U)             /* RL3 Seat Senser SW                                           */
#define CALIB_MCUID0233_DEF                         (1U)             /* Rear Seat Door                                               */
#define CALIB_MCUID0234_DEF                         (0U)             /* Walkthrough                                                  */
#define CALIB_MCUID0235_DEF                         (0U)             /* Bodyshape                                                    */
#define CALIB_MCUID0250_DEF                         (3U)             /* fuel efficiency CONV                                         */
#define CALIB_MCUID0251_DEF                         (4U)             /* fuel efficiency HV                                           */
#define CALIB_MCUID0252_DEF                         (4U)             /* fuel efficiency PHV                                          */
#define CALIB_MCUID0253_DEF                         (2U)             /* fuel efficiency FC                                           */
#define CALIB_MCUID0254_DEF                         (2U)             /* power expense PHV                                            */
#define CALIB_MCUID0255_DEF                         (2U)             /* power expense EV                                             */
#define CALIB_MCUID0256_DEF                         (48U)            /* TOLER_A USA/CANADA                                           */
#define CALIB_MCUID0257_DEF                         (1)              /* TOLER_B USA/CANADA                                           */
#define CALIB_MCUID0260_DEF                         (44U)            /* TOLER_A UNR/AUS                                              */
#define CALIB_MCUID0261_DEF                         (4)              /* TOLER_B UNR/AUS                                              */
#define CALIB_MCUID0264_DEF                         (0U)             /* Fspo                                                         */
#define CALIB_MCUID0268_DEF                         (1U)             /* SWnum                                                        */
#define CALIB_MCUID0270_DEF                         (100U)           /* CAN:RHEOSTAT(%):light control is max hold                    */
#define CALIB_MCUID0271_DEF                         (100U)           /* CAN:RHEOSTAT(%):light control level (1)                      */
#define CALIB_MCUID0272_DEF                         (94U)            /* CAN:RHEOSTAT(%):light control level (2)                      */
#define CALIB_MCUID0273_DEF                         (83U)            /* CAN:RHEOSTAT(%):light control level (3)                      */
#define CALIB_MCUID0274_DEF                         (74U)            /* CAN:RHEOSTAT(%):light control level (4)                      */
#define CALIB_MCUID0275_DEF                         (66U)            /* CAN:RHEOSTAT(%):light control level (5)                      */
#define CALIB_MCUID0276_DEF                         (59U)            /* CAN:RHEOSTAT(%):light control level (6)                      */
#define CALIB_MCUID0277_DEF                         (53U)            /* CAN:RHEOSTAT(%):light control level (7)                      */
#define CALIB_MCUID0278_DEF                         (48U)            /* CAN:RHEOSTAT(%):light control level (8)                      */
#define CALIB_MCUID0279_DEF                         (43U)            /* CAN:RHEOSTAT(%):light control level (9)                      */
#define CALIB_MCUID0280_DEF                         (38U)            /* CAN:RHEOSTAT(%):light control level (10)                     */
#define CALIB_MCUID0281_DEF                         (34U)            /* CAN:RHEOSTAT(%):light control level (11)                     */
#define CALIB_MCUID0282_DEF                         (31U)            /* CAN:RHEOSTAT(%):light control level (12)                     */
#define CALIB_MCUID0283_DEF                         (28U)            /* CAN:RHEOSTAT(%):light control level (13)                     */
#define CALIB_MCUID0284_DEF                         (25U)            /* CAN:RHEOSTAT(%):light control level (14)                     */
#define CALIB_MCUID0285_DEF                         (22U)            /* CAN:RHEOSTAT(%):light control level (15)                     */
#define CALIB_MCUID0286_DEF                         (20U)            /* CAN:RHEOSTAT(%):light control level (16)                     */
#define CALIB_MCUID0287_DEF                         (18U)            /* CAN:RHEOSTAT(%):light control level (17)                     */
#define CALIB_MCUID0288_DEF                         (16U)            /* CAN:RHEOSTAT(%):light control level (18)                     */
#define CALIB_MCUID0289_DEF                         (14U)            /* CAN:RHEOSTAT(%):light control level (19)                     */
#define CALIB_MCUID0290_DEF                         (12U)            /* CAN:RHEOSTAT(%):light control level (20)                     */
#define CALIB_MCUID0291_DEF                         (12U)            /* CAN:RHEOSTAT(%): light control is min hold                   */
#define CALIB_MCUID0336_DEF                         (0U)             /* ILL_OF Level                                                 */
#define CALIB_MCUID0337_DEF                         (1U)             /* ILL_OF Cancel Level                                          */
#define CALIB_MCUID0340_DEF                         (10U)            /* Rheostat Position Night                                      */
#define CALIB_MCUID0341_DEF                         (1U)             /* TAIL Apply                                                   */
#define CALIB_MCUID0342_DEF                         (100U)           /* Daytime Back-light control(%):light control is max hold      */
#define CALIB_MCUID0343_DEF                         (84U)            /* Daytime Back-light control(%):light control level (1)        */
#define CALIB_MCUID0344_DEF                         (70U)            /* Daytime Back-light control(%):light control level (2)        */
#define CALIB_MCUID0345_DEF                         (59U)            /* Daytime Back-light control(%):light control level (3)        */
#define CALIB_MCUID0346_DEF                         (50U)            /* Daytime Back-light control(%):light control level (4)        */
#define CALIB_MCUID0347_DEF                         (42U)            /* Daytime Back-light control(%):light control level (5)        */
#define CALIB_MCUID0348_DEF                         (35U)            /* Daytime Back-light control(%):light control level (6)        */
#define CALIB_MCUID0349_DEF                         (29U)            /* Daytime Back-light control(%):light control level (7)        */
#define CALIB_MCUID0350_DEF                         (25U)            /* Daytime Back-light control(%):light control level (8)        */
#define CALIB_MCUID0351_DEF                         (21U)            /* Daytime Back-light control(%):light control level (9)        */
#define CALIB_MCUID0352_DEF                         (17U)            /* Daytime Back-light control(%):light control level (10)       */
#define CALIB_MCUID0353_DEF                         (17U)            /* Daytime Back-light control(%):light control level (11)       */
#define CALIB_MCUID0354_DEF                         (17U)            /* Daytime Back-light control(%):light control level (12)       */
#define CALIB_MCUID0355_DEF                         (17U)            /* Daytime Back-light control(%):light control level (13)       */
#define CALIB_MCUID0356_DEF                         (17U)            /* Daytime Back-light control(%):light control level (14)       */
#define CALIB_MCUID0357_DEF                         (17U)            /* Daytime Back-light control(%):light control level (15)       */
#define CALIB_MCUID0358_DEF                         (17U)            /* Daytime Back-light control(%):light control level (16)       */
#define CALIB_MCUID0359_DEF                         (17U)            /* Daytime Back-light control(%):light control level (17)       */
#define CALIB_MCUID0360_DEF                         (17U)            /* Daytime Back-light control(%):light control level (18)       */
#define CALIB_MCUID0361_DEF                         (17U)            /* Daytime Back-light control(%):light control level (19)       */
#define CALIB_MCUID0362_DEF                         (17U)            /* Daytime Back-light control(%):light control level (20)       */
#define CALIB_MCUID0363_DEF                         (17U)            /* Daytime Back-light control(%): light control is min hold     */
#define CALIB_MCUID0364_DEF                         (0U)             /* Daytime RGB control(%):light control is max hold             */
#define CALIB_MCUID0365_DEF                         (0U)             /* Daytime RGB control(%):light control level (1)               */
#define CALIB_MCUID0366_DEF                         (0U)             /* Daytime RGB control(%):light control level (2)               */
#define CALIB_MCUID0367_DEF                         (0U)             /* Daytime RGB control(%):light control level (3)               */
#define CALIB_MCUID0368_DEF                         (0U)             /* Daytime RGB control(%):light control level (4)               */
#define CALIB_MCUID0369_DEF                         (0U)             /* Daytime RGB control(%):light control level (5)               */
#define CALIB_MCUID0370_DEF                         (0U)             /* Daytime RGB control(%):light control level (6)               */
#define CALIB_MCUID0371_DEF                         (0U)             /* Daytime RGB control(%):light control level (7)               */
#define CALIB_MCUID0372_DEF                         (0U)             /* Daytime RGB control(%):light control level (8)               */
#define CALIB_MCUID0373_DEF                         (0U)             /* Daytime RGB control(%):light control level (9)               */
#define CALIB_MCUID0374_DEF                         (0U)             /* Daytime RGB control(%):light control level (10)              */
#define CALIB_MCUID0375_DEF                         (20U)            /* Daytime RGB control(%):light control level (11)              */
#define CALIB_MCUID0376_DEF                         (38U)            /* Daytime RGB control(%):light control level (12)              */
#define CALIB_MCUID0377_DEF                         (54U)            /* Daytime RGB control(%):light control level (13)              */
#define CALIB_MCUID0378_DEF                         (70U)            /* Daytime RGB control(%):light control level (14)              */
#define CALIB_MCUID0379_DEF                         (84U)            /* Daytime RGB control(%):light control level (15)              */
#define CALIB_MCUID0380_DEF                         (97U)            /* Daytime RGB control(%):light control level (16)              */
#define CALIB_MCUID0381_DEF                         (109U)           /* Daytime RGB control(%):light control level (17)              */
#define CALIB_MCUID0382_DEF                         (120U)           /* Daytime RGB control(%):light control level (18)              */
#define CALIB_MCUID0383_DEF                         (131U)           /* Daytime RGB control(%):light control level (19)              */
#define CALIB_MCUID0384_DEF                         (140U)           /* Daytime RGB control(%):light control level (20)              */
#define CALIB_MCUID0385_DEF                         (149U)           /* Daytime RGB control(%): light control is min hold            */
#define CALIB_MCUID0386_DEF                         (20U)            /* Nighttime Back-light control(%):light control is max hold    */
#define CALIB_MCUID0387_DEF                         (16U)            /* Nighttime Back-light control(%):light control level (1)      */
#define CALIB_MCUID0388_DEF                         (12U)            /* Nighttime Back-light control(%):light control level (2)      */
#define CALIB_MCUID0389_DEF                         (9U)             /* Nighttime Back-light control(%):light control level (3)      */
#define CALIB_MCUID0390_DEF                         (7U)             /* Nighttime Back-light control(%):light control level (4)      */
#define CALIB_MCUID0391_DEF                         (6U)             /* Nighttime Back-light control(%):light control level (5)      */
#define CALIB_MCUID0392_DEF                         (4U)             /* Nighttime Back-light control(%):light control level (6)      */
#define CALIB_MCUID0393_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (7)      */
#define CALIB_MCUID0394_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (8)      */
#define CALIB_MCUID0395_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (9)      */
#define CALIB_MCUID0396_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (10)     */
#define CALIB_MCUID0397_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (11)     */
#define CALIB_MCUID0398_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (12)     */
#define CALIB_MCUID0399_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (13)     */
#define CALIB_MCUID0400_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (14)     */
#define CALIB_MCUID0401_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (15)     */
#define CALIB_MCUID0402_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (16)     */
#define CALIB_MCUID0403_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (17)     */
#define CALIB_MCUID0404_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (18)     */
#define CALIB_MCUID0405_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (19)     */
#define CALIB_MCUID0406_DEF                         (3U)             /* Nighttime Back-light control(%):light control level (20)     */
#define CALIB_MCUID0407_DEF                         (3U)             /* Nighttime Back-light control(%): light control is min hold   */
#define CALIB_MCUID0408_DEF                         (0U)             /* Nighttime RGB control(%):light control is max hold           */
#define CALIB_MCUID0409_DEF                         (0U)             /* Nighttime RGB control(%):light control level (1)             */
#define CALIB_MCUID0410_DEF                         (0U)             /* Nighttime RGB control(%):light control level (2)             */
#define CALIB_MCUID0411_DEF                         (0U)             /* Nighttime RGB control(%):light control level (3)             */
#define CALIB_MCUID0412_DEF                         (0U)             /* Nighttime RGB control(%):light control level (4)             */
#define CALIB_MCUID0413_DEF                         (0U)             /* Nighttime RGB control(%):light control level (5)             */
#define CALIB_MCUID0414_DEF                         (0U)             /* Nighttime RGB control(%):light control level (6)             */
#define CALIB_MCUID0415_DEF                         (0U)             /* Nighttime RGB control(%):light control level (7)             */
#define CALIB_MCUID0416_DEF                         (28U)            /* Nighttime RGB control(%):light control level (8)             */
#define CALIB_MCUID0417_DEF                         (52U)            /* Nighttime RGB control(%):light control level (9)             */
#define CALIB_MCUID0418_DEF                         (74U)            /* Nighttime RGB control(%):light control level (10)            */
#define CALIB_MCUID0419_DEF                         (94U)            /* Nighttime RGB control(%):light control level (11)            */
#define CALIB_MCUID0420_DEF                         (111U)           /* Nighttime RGB control(%):light control level (12)            */
#define CALIB_MCUID0421_DEF                         (127U)           /* Nighttime RGB control(%):light control level (13)            */
#define CALIB_MCUID0422_DEF                         (141U)           /* Nighttime RGB control(%):light control level (14)            */
#define CALIB_MCUID0423_DEF                         (153U)           /* Nighttime RGB control(%):light control level (15)            */
#define CALIB_MCUID0424_DEF                         (164U)           /* Nighttime RGB control(%):light control level (16)            */
#define CALIB_MCUID0425_DEF                         (174U)           /* Nighttime RGB control(%):light control level (17)            */
#define CALIB_MCUID0426_DEF                         (183U)           /* Nighttime RGB control(%):light control level (18)            */
#define CALIB_MCUID0427_DEF                         (191U)           /* Nighttime RGB control(%):light control level (19)            */
#define CALIB_MCUID0428_DEF                         (198U)           /* Nighttime RGB control(%):light control level (20)            */
#define CALIB_MCUID0429_DEF                         (204U)           /* Nighttime RGB control(%): light control is min hold          */
#define CALIB_MCUID0430_DEF                         (3U)             /* Rheostat SW Apply                                            */
#define CALIB_MCUID0590_DEF                         (0U)             /* SOC Port Position                                            */
#define CALIB_MCUID_RSV_1B_0175_DEF                 (0U)             /* Reserve_1B_0175                                              */
#define CALIB_MCUID_RSV_1B_0176_DEF                 (0U)             /* Reserve_1B_0176                                              */
#define CALIB_MCUID0604_DEF                         (0U)             /* SeatBelt Regulation MEXICO                                   */
#define CALIB_MCUID0605_DEF                         (1U)             /* SeatBelt Regulation EU                                       */
#define CALIB_MCUID0606_DEF                         (0U)             /* SeatBelt Regulation KOREA                                    */
#define CALIB_MCUID0607_DEF                         (2U)             /* SeatBelt Regulation CHINA                                    */
#define CALIB_MCUID0741_DEF                         (0U)             /* IL2OUTILLRun                                                 */
#define CALIB_MCUID0798_DEF                         (0U)             /* Turn signal lamp color of your vehicle                       */
#define CALIB_MCUID0809_DEF                         (0U)             /* Mexico lows and regulations                                  */
#define CALIB_MCUID0810_DEF                         (1U)             /* Korea lows and regulations                                   */
#define CALIB_MCUID3020_DEF                         (0U)             /* Regulations requiring compliance for General Transportation  */
#define CALIB_MCUID3025_DEF                         (0U)             /* Combination switch position                                  */
#define CALIB_MCUID0933_DEF                         (0U)             /* Judgment country 1 Fuel economy unit                         */
#define CALIB_MCUID0934_DEF                         (0U)             /* Judgment country 2 Fuel economy unit                         */
#define CALIB_MCUID0935_DEF                         (0U)             /* Judgment country 3 Fuel economy unit                         */
#define CALIB_MCUID0936_DEF                         (0U)             /* Judgment country 4 Fuel economy unit                         */
#define CALIB_MCUID0937_DEF                         (0U)             /* Judgment country 5 Fuel economy unit                         */
#define CALIB_MCUID0938_DEF                         (0U)             /* Judgment country 6 Fuel economy unit                         */
#define CALIB_MCUID0939_DEF                         (0U)             /* Judgment country 7 Fuel economy unit                         */
#define CALIB_MCUID0940_DEF                         (0U)             /* Judgment country 8 Fuel economy unit                         */
#define CALIB_MCUID0941_DEF                         (0U)             /* Judgment country 9 Fuel economy unit                         */
#define CALIB_MCUID0942_DEF                         (0U)             /* Judgment country 10 Fuel economy unit                        */
#define CALIB_MCUID0943_DEF                         (0U)             /* Judgment country 1 unit switching                            */
#define CALIB_MCUID0944_DEF                         (0U)             /* Judgment country 2 unit switching                            */
#define CALIB_MCUID0945_DEF                         (0U)             /* Judgment country 3 unit switching                            */
#define CALIB_MCUID0946_DEF                         (0U)             /* Judgment country 4 unit switching                            */
#define CALIB_MCUID0947_DEF                         (0U)             /* Judgment country 5 unit switching                            */
#define CALIB_MCUID0948_DEF                         (0U)             /* Judgment country 6 unit switching                            */
#define CALIB_MCUID0949_DEF                         (0U)             /* Judgment country 7 unit switching                            */
#define CALIB_MCUID0950_DEF                         (0U)             /* Judgment country 8 unit switching                            */
#define CALIB_MCUID0951_DEF                         (0U)             /* Judgment country 9 unit switching                            */
#define CALIB_MCUID0952_DEF                         (0U)             /* Judgment country 10 unit switching                           */
#define CALIB_MCUID0953_DEF                         (0U)             /* Judgment country 1 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0954_DEF                         (0U)             /* Judgment country 2 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0955_DEF                         (0U)             /* Judgment country 3 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0956_DEF                         (0U)             /* Judgment country 4 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0957_DEF                         (0U)             /* Judgment country 5 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0958_DEF                         (0U)             /* Judgment country 6 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0959_DEF                         (0U)             /* Judgment country 7 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0960_DEF                         (0U)             /* Judgment country 8 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0961_DEF                         (0U)             /* Judgment country 9 Buzzer (reverse buzzer)                   */
#define CALIB_MCUID0962_DEF                         (0U)             /* Judgment country 10 Buzzer (reverse buzzer)                  */
#define CALIB_MCUID0963_DEF                         (0U)             /* Judgment country 1 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0964_DEF                         (0U)             /* Judgment country 2 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0965_DEF                         (0U)             /* Judgment country 3 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0966_DEF                         (0U)             /* Judgment country 4 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0967_DEF                         (0U)             /* Judgment country 5 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0968_DEF                         (0U)             /* Judgment country 6 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0969_DEF                         (0U)             /* Judgment country 7 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0970_DEF                         (0U)             /* Judgment country 8 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0971_DEF                         (0U)             /* Judgment country 9 Regulation Buzzer/warning (GSO)           */
#define CALIB_MCUID0972_DEF                         (0U)             /* Judgment country 10 Regulation Buzzer/warning (GSO)          */
#define CALIB_MCUID0973_DEF                         (0U)             /* Judgment country 1 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0974_DEF                         (0U)             /* Judgment country 2 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0975_DEF                         (0U)             /* Judgment country 3 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0976_DEF                         (0U)             /* Judgment country 4 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0977_DEF                         (0U)             /* Judgment country 5 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0978_DEF                         (0U)             /* Judgment country 6 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0979_DEF                         (0U)             /* Judgment country 7 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0980_DEF                         (0U)             /* Judgment country 8 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0981_DEF                         (0U)             /* Judgment country 9 Regulation Buzzer (AIS)                   */
#define CALIB_MCUID0982_DEF                         (0U)             /* Judgment country 10 Regulation Buzzer (AIS)                  */
#define CALIB_MCUID0983_DEF                         (0U)             /* Judgment country 1 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0984_DEF                         (0U)             /* Judgment country 2 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0985_DEF                         (0U)             /* Judgment country 3 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0986_DEF                         (0U)             /* Judgment country 4 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0987_DEF                         (0U)             /* Judgment country 5 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0988_DEF                         (0U)             /* Judgment country 6 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0989_DEF                         (0U)             /* Judgment country 7 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0990_DEF                         (0U)             /* Judgment country 8 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0991_DEF                         (0U)             /* Judgment country 9 Regulation Buzzer (Notification)          */
#define CALIB_MCUID0992_DEF                         (0U)             /* Judgment country 10 Regulation Buzzer (Notification)         */
#define CALIB_MCUID0993_DEF                         (0U)             /* Judgment country 1 Speed Reg Speed Unit                      */
#define CALIB_MCUID0994_DEF                         (0U)             /* Judgment country 2 Speed Reg Speed Unit                      */
#define CALIB_MCUID0995_DEF                         (0U)             /* Judgment country 3 Speed Reg Speed Unit                      */
#define CALIB_MCUID0996_DEF                         (0U)             /* Judgment country 4 Speed Reg Speed Unit                      */
#define CALIB_MCUID0997_DEF                         (0U)             /* Judgment country 5 Speed Reg Speed Unit                      */
#define CALIB_MCUID0998_DEF                         (0U)             /* Judgment country 6 Speed Reg Speed Unit                      */
#define CALIB_MCUID0999_DEF                         (0U)             /* Judgment country 7 Speed Reg Speed Unit                      */
#define CALIB_MCUID1000_DEF                         (0U)             /* Judgment country 8 Speed Reg Speed Unit                      */
#define CALIB_MCUID1001_DEF                         (0U)             /* Judgment country 9 Speed Reg Speed Unit                      */
#define CALIB_MCUID1002_DEF                         (0U)             /* Judgment country 10 Speed Reg Speed Unit                     */
#define CALIB_MCUID1003_DEF                         (0U)             /* Judgment country 1 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1004_DEF                         (0U)             /* Judgment country 2 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1005_DEF                         (0U)             /* Judgment country 3 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1006_DEF                         (0U)             /* Judgment country 4 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1007_DEF                         (0U)             /* Judgment country 5 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1008_DEF                         (0U)             /* Judgment country 6 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1009_DEF                         (0U)             /* Judgment country 7 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1010_DEF                         (0U)             /* Judgment country 8 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1011_DEF                         (0U)             /* Judgment country 9 Speed Reg Veh Speed Unit W/O Main/Sub Sw  */
#define CALIB_MCUID1012_DEF                         (0U)             /* Judgment country 10 Speed Reg Veh Speed Unit W/O Main/Sub Sw */
#define CALIB_MCUID1013_DEF                         (0U)             /* Judgment country 1 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1014_DEF                         (0U)             /* Judgment country 2 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1015_DEF                         (0U)             /* Judgment country 3 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1016_DEF                         (0U)             /* Judgment country 4 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1017_DEF                         (0U)             /* Judgment country 5 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1018_DEF                         (0U)             /* Judgment country 6 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1019_DEF                         (0U)             /* Judgment country 7 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1020_DEF                         (0U)             /* Judgment country 8 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1021_DEF                         (0U)             /* Judgment country 9 Speed Reg Sub Speed Display               */
#define CALIB_MCUID1022_DEF                         (0U)             /* Judgment country 10 Speed Reg Sub Speed Display              */
#define CALIB_MCUID1023_DEF                         (0U)             /* Judgment country 1 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1024_DEF                         (0U)             /* Judgment country 2 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1025_DEF                         (0U)             /* Judgment country 3 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1026_DEF                         (0U)             /* Judgment country 4 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1027_DEF                         (0U)             /* Judgment country 5 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1028_DEF                         (0U)             /* Judgment country 6 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1029_DEF                         (0U)             /* Judgment country 7 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1030_DEF                         (0U)             /* Judgment country 8 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1031_DEF                         (0U)             /* Judgment country 9 Speed Reg Veh Speed Tol                   */
#define CALIB_MCUID1032_DEF                         (0U)             /* Judgment country 10 Speed Reg Veh Speed Tol                  */
#define CALIB_MCUID1033_DEF                         (0U)             /* Judgment country 1 China unique regulation (GB)              */
#define CALIB_MCUID1034_DEF                         (0U)             /* Judgment country 2 China unique regulation (GB)              */
#define CALIB_MCUID1035_DEF                         (0U)             /* Judgment country 3 China unique regulation (GB)              */
#define CALIB_MCUID1036_DEF                         (0U)             /* Judgment country 4 China unique regulation (GB)              */
#define CALIB_MCUID1037_DEF                         (0U)             /* Judgment country 5 China unique regulation (GB)              */
#define CALIB_MCUID1038_DEF                         (0U)             /* Judgment country 6 China unique regulation (GB)              */
#define CALIB_MCUID1039_DEF                         (0U)             /* Judgment country 7 China unique regulation (GB)              */
#define CALIB_MCUID1040_DEF                         (0U)             /* Judgment country 8 China unique regulation (GB)              */
#define CALIB_MCUID1041_DEF                         (0U)             /* Judgment country 9 China unique regulation (GB)              */
#define CALIB_MCUID1042_DEF                         (0U)             /* Judgment country 10 China unique regulation (GB)             */
#define CALIB_MCUID1043_DEF                         (0U)             /* Judgment country 1 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1044_DEF                         (0U)             /* Judgment country 2 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1045_DEF                         (0U)             /* Judgment country 3 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1046_DEF                         (0U)             /* Judgment country 4 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1047_DEF                         (0U)             /* Judgment country 5 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1048_DEF                         (0U)             /* Judgment country 6 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1049_DEF                         (0U)             /* Judgment country 7 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1050_DEF                         (0U)             /* Judgment country 8 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1051_DEF                         (0U)             /* Judgment country 9 Regulation (FMVSS) BRAKE telltale         */
#define CALIB_MCUID1052_DEF                         (0U)             /* Judgment country 10 Regulation (FMVSS) BRAKE telltale        */
#define CALIB_MCUID1053_DEF                         (0U)             /* Judgment country 1 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1054_DEF                         (0U)             /* Judgment country 2 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1055_DEF                         (0U)             /* Judgment country 3 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1056_DEF                         (0U)             /* Judgment country 4 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1057_DEF                         (0U)             /* Judgment country 5 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1058_DEF                         (0U)             /* Judgment country 6 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1059_DEF                         (0U)             /* Judgment country 7 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1060_DEF                         (0U)             /* Judgment country 8 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1061_DEF                         (0U)             /* Judgment country 9 Regulation (FMVSS) ABS telltale           */
#define CALIB_MCUID1062_DEF                         (0U)             /* Judgment country 10 Regulation (FMVSS) ABS telltale          */
#define CALIB_MCUID1063_DEF                         (0U)             /* Judgment country 1 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1064_DEF                         (0U)             /* Judgment country 2 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1065_DEF                         (0U)             /* Judgment country 3 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1066_DEF                         (0U)             /* Judgment country 4 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1067_DEF                         (0U)             /* Judgment country 5 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1068_DEF                         (0U)             /* Judgment country 6 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1069_DEF                         (0U)             /* Judgment country 7 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1070_DEF                         (0U)             /* Judgment country 8 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1071_DEF                         (0U)             /* Judgment country 9 Regulation (FMVSS) EPB/PKB telltale       */
#define CALIB_MCUID1072_DEF                         (0U)             /* Judgment country 10 Regulation (FMVSS) EPB/PKB telltale      */
#define CALIB_MCUID1073_DEF                         (0U)             /* Judgment country 1 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1074_DEF                         (0U)             /* Judgment country 2 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1075_DEF                         (0U)             /* Judgment country 3 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1076_DEF                         (0U)             /* Judgment country 4 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1077_DEF                         (0U)             /* Judgment country 5 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1078_DEF                         (0U)             /* Judgment country 6 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1079_DEF                         (0U)             /* Judgment country 7 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1080_DEF                         (0U)             /* Judgment country 8 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1081_DEF                         (0U)             /* Judgment country 9 Regulation (FMVSS) TAIL/HEAD telltale     */
#define CALIB_MCUID1082_DEF                         (0U)             /* Judgment country 10 Regulation (FMVSS) TAIL/HEAD telltale    */
#define CALIB_MCUID1093_DEF                         (0U)             /* Judgment country 1 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1094_DEF                         (0U)             /* Judgment country 2 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1095_DEF                         (0U)             /* Judgment country 3 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1096_DEF                         (0U)             /* Judgment country 4 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1097_DEF                         (0U)             /* Judgment country 5 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1098_DEF                         (0U)             /* Judgment country 6 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1099_DEF                         (0U)             /* Judgment country 7 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1100_DEF                         (0U)             /* Judgment country 8 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1101_DEF                         (0U)             /* Judgment country 9 Regulation Buzzer/IND (Belt reminder)     */
#define CALIB_MCUID1102_DEF                         (0U)             /* Judgment country 10 Regulation Buzzer/IND (Belt reminder)    */
#define CALIB_MCUID1103_DEF                         (0U)             /* Judgment result 1                                            */
#define CALIB_MCUID1104_DEF                         (0U)             /* Judgment result 2                                            */
#define CALIB_MCUID1105_DEF                         (0U)             /* Judgment result 3                                            */
#define CALIB_MCUID1106_DEF                         (0U)             /* Judgment result 4                                            */
#define CALIB_MCUID1107_DEF                         (0U)             /* Judgment result 5                                            */
#define CALIB_MCUID1108_DEF                         (0U)             /* Judgment result 6                                            */
#define CALIB_MCUID1109_DEF                         (0U)             /* Judgment result 7                                            */
#define CALIB_MCUID1110_DEF                         (0U)             /* Judgment result 8                                            */
#define CALIB_MCUID1111_DEF                         (0U)             /* Judgment result 9                                            */
#define CALIB_MCUID1112_DEF                         (0U)             /* Judgment result 10                                           */
#define CALIB_MCUID1135_DEF                         (0U)             /* SeatBelt Regulation USA                                      */
#define CALIB_MCUID1136_DEF                         (0U)             /* SeatBelt Regulation CAN                                      */
#define CALIB_MCUID1137_DEF                         (0U)             /* New FMVSS applied or not                                     */
#define CALIB_MCUID1138_DEF                         (1U)             /* SeatBelt Reminder Telltale Type                              */
#define CALIB_MCUID0576_DEF                         (24U)            /* DegCW                                                        */
#define CALIB_MCUID0577_DEF                         (231U)           /* DegCCW                                                       */
#define CALIB_MCUID0578_DEF                         (24U)            /* Deg_RTStep                                                   */
#define CALIB_MCUID0579_DEF                         (30U)            /* ResTime                                                      */
#define CALIB_MCUID0580_DEF                         (100U)           /* ACon_MvAveCnt                                                */
#define CALIB_MCUID0581_DEF                         (8U)             /* ACon_UpAveCnt                                                */
#define CALIB_MCUID0582_DEF                         (2U)             /* ACon_DnAveCnt                                                */
#define CALIB_MCUID0583_DEF                         (1U)             /* ATss_AorNA                                                   */
#define CALIB_MCUID0584_DEF                         (8U)             /* ATss_UpAveCnt                                                */
#define CALIB_MCUID0585_DEF                         (2U)             /* ATss_DnAveCnt                                                */
#define CALIB_MCUID0586_DEF                         (32U)            /* HUDLm_AveCnt                                                 */
#define CALIB_MCUID_RSV_1B_0372_DEF                 (0U)             /* Reserve_1B-0372                                              */
#define CALIB_MCUID_RSV_1B_0373_DEF                 (0U)             /* Reserve_1B-0373                                              */
#define CALIB_MCUID_RSV_1B_0374_DEF                 (0U)             /* Reserve_1B-0374                                              */
#define CALIB_MCUID_RSV_1B_0375_DEF                 (0U)             /* Reserve_1B-0375                                              */
#define CALIB_MCUID_RSV_1B_0376_DEF                 (0U)             /* Reserve_1B-0376                                              */
#define CALIB_MCUID_RSV_1B_0377_DEF                 (0U)             /* Reserve_1B-0377                                              */
#define CALIB_MCUID_RSV_1B_0378_DEF                 (0U)             /* Reserve_1B-0378                                              */
#define CALIB_MCUID_RSV_1B_0379_DEF                 (0U)             /* Reserve_1B-0379                                              */
#define CALIB_MCUID_RSV_1B_0380_DEF                 (0U)             /* Reserve_1B-0380                                              */
#define CALIB_MCUID_RSV_1B_0381_DEF                 (0U)             /* Reserve_1B-0381                                              */
#define CALIB_MCUID_RSV_1B_0382_DEF                 (0U)             /* Reserve_1B-0382                                              */
#define CALIB_MCUID_RSV_1B_0383_DEF                 (0U)             /* Reserve_1B-0383                                              */
#define CALIB_MCUID_RSV_1B_0384_DEF                 (0U)             /* Reserve_1B-0384                                              */
#define CALIB_MCUID_RSV_1B_0385_DEF                 (0U)             /* Reserve_1B-0385                                              */
#define CALIB_MCUID_RSV_1B_0386_DEF                 (0U)             /* Reserve_1B-0386                                              */
#define CALIB_MCUID_RSV_1B_0387_DEF                 (0U)             /* Reserve_1B-0387                                              */
#define CALIB_MCUID_RSV_1B_0388_DEF                 (0U)             /* Reserve_1B-0388                                              */
#define CALIB_MCUID_RSV_1B_0389_DEF                 (0U)             /* Reserve_1B-0389                                              */
#define CALIB_MCUID_RSV_1B_0390_DEF                 (0U)             /* Reserve_1B-0390                                              */
#define CALIB_MCUID_RSV_1B_0391_DEF                 (0U)             /* Reserve_1B-0391                                              */
#define CALIB_MCUID_RSV_1B_0392_DEF                 (0U)             /* Reserve_1B-0392                                              */
#define CALIB_MCUID_RSV_1B_0393_DEF                 (0U)             /* Reserve_1B-0393                                              */
#define CALIB_MCUID_RSV_1B_0394_DEF                 (0U)             /* Reserve_1B-0394                                              */
#define CALIB_MCUID_RSV_1B_0395_DEF                 (0U)             /* Reserve_1B-0395                                              */
#define CALIB_MCUID_RSV_1B_0396_DEF                 (0U)             /* Reserve_1B-0396                                              */
#define CALIB_MCUID_RSV_1B_0397_DEF                 (0U)             /* Reserve_1B-0397                                              */
#define CALIB_MCUID_RSV_1B_0398_DEF                 (0U)             /* Reserve_1B-0398                                              */
#define CALIB_MCUID_RSV_1B_0399_DEF                 (0U)             /* Reserve_1B-0399                                              */
#define CALIB_MCUID_RSV_1B_0400_DEF                 (0U)             /* Reserve_1B-0400                                              */
#define CALIB_MCUID_RSV_1B_0401_DEF                 (0U)             /* Reserve_1B-0401                                              */
#define CALIB_MCUID_RSV_1B_0402_DEF                 (0U)             /* Reserve_1B-0402                                              */
#define CALIB_MCUID_RSV_1B_0403_DEF                 (0U)             /* Reserve_1B-0403                                              */
#define CALIB_MCUID_RSV_1B_0404_DEF                 (0U)             /* Reserve_1B-0404                                              */
#define CALIB_MCUID_RSV_1B_0405_DEF                 (0U)             /* Reserve_1B-0405                                              */
#define CALIB_MCUID_RSV_1B_0406_DEF                 (0U)             /* Reserve_1B-0406                                              */
#define CALIB_MCUID_RSV_1B_0407_DEF                 (0U)             /* Reserve_1B-0407                                              */
#define CALIB_MCUID_RSV_1B_0408_DEF                 (0U)             /* Reserve_1B-0408                                              */
#define CALIB_MCUID_RSV_1B_0409_DEF                 (0U)             /* Reserve_1B-0409                                              */
#define CALIB_MCUID_RSV_1B_0410_DEF                 (0U)             /* Reserve_1B-0410                                              */
#define CALIB_MCUID_RSV_1B_0411_DEF                 (0U)             /* Reserve_1B-0411                                              */
#define CALIB_MCUID_RSV_1B_0412_DEF                 (0U)             /* Reserve_1B-0412                                              */
#define CALIB_MCUID_RSV_1B_0413_DEF                 (0U)             /* Reserve_1B-0413                                              */
#define CALIB_MCUID_RSV_1B_0414_DEF                 (0U)             /* Reserve_1B-0414                                              */
#define CALIB_MCUID_RSV_1B_0415_DEF                 (0U)             /* Reserve_1B-0415                                              */
#define CALIB_MCUID_RSV_1B_0416_DEF                 (0U)             /* Reserve_1B-0416                                              */
#define CALIB_MCUID_RSV_1B_0417_DEF                 (0U)             /* Reserve_1B-0417                                              */
#define CALIB_MCUID_RSV_1B_0418_DEF                 (0U)             /* Reserve_1B-0418                                              */
#define CALIB_MCUID_RSV_1B_0419_DEF                 (0U)             /* Reserve_1B-0419                                              */
#define CALIB_MCUID_RSV_1B_0420_DEF                 (0U)             /* Reserve_1B-0420                                              */
#define CALIB_MCUID_RSV_1B_0421_DEF                 (0U)             /* Reserve_1B-0421                                              */
#define CALIB_MCUID_RSV_1B_0422_DEF                 (0U)             /* Reserve_1B-0422                                              */
#define CALIB_MCUID_RSV_1B_0423_DEF                 (0U)             /* Reserve_1B-0423                                              */
#define CALIB_MCUID_RSV_1B_0424_DEF                 (0U)             /* Reserve_1B-0424                                              */
#define CALIB_MCUID_RSV_1B_0425_DEF                 (0U)             /* Reserve_1B-0425                                              */
#define CALIB_MCUID_RSV_1B_0426_DEF                 (0U)             /* Reserve_1B-0426                                              */
#define CALIB_MCUID_RSV_1B_0427_DEF                 (0U)             /* Reserve_1B-0427                                              */
#define CALIB_MCUID_RSV_1B_0428_DEF                 (0U)             /* Reserve_1B-0428                                              */
#define CALIB_MCUID_RSV_1B_0429_DEF                 (0U)             /* Reserve_1B-0429                                              */
#define CALIB_MCUID_RSV_1B_0430_DEF                 (0U)             /* Reserve_1B-0430                                              */
#define CALIB_MCUID_RSV_1B_0431_DEF                 (0U)             /* Reserve_1B-0431                                              */
#define CALIB_MCUID_RSV_1B_0432_DEF                 (0U)             /* Reserve_1B-0432                                              */
#define CALIB_MCUID_RSV_1B_0433_DEF                 (0U)             /* Reserve_1B-0433                                              */
#define CALIB_MCUID_RSV_1B_0434_DEF                 (0U)             /* Reserve_1B-0434                                              */
#define CALIB_MCUID_RSV_1B_0435_DEF                 (0U)             /* Reserve_1B-0435                                              */
#define CALIB_MCUID_RSV_1B_0436_DEF                 (0U)             /* Reserve_1B-0436                                              */
#define CALIB_MCUID_RSV_1B_0437_DEF                 (0U)             /* Reserve_1B-0437                                              */
#define CALIB_MCUID_RSV_1B_0438_DEF                 (0U)             /* Reserve_1B-0438                                              */
#define CALIB_MCUID_RSV_1B_0439_DEF                 (0U)             /* Reserve_1B-0439                                              */
#define CALIB_MCUID_RSV_1B_0440_DEF                 (0U)             /* Reserve_1B-0440                                              */
#define CALIB_MCUID_RSV_1B_0441_DEF                 (0U)             /* Reserve_1B-0441                                              */
#define CALIB_MCUID_RSV_1B_0442_DEF                 (0U)             /* Reserve_1B-0442                                              */
#define CALIB_MCUID_RSV_1B_0443_DEF                 (0U)             /* Reserve_1B-0443                                              */
#define CALIB_MCUID_RSV_1B_0444_DEF                 (0U)             /* Reserve_1B-0444                                              */
#define CALIB_MCUID_RSV_1B_0445_DEF                 (0U)             /* Reserve_1B-0445                                              */
#define CALIB_MCUID_RSV_1B_0446_DEF                 (0U)             /* Reserve_1B-0446                                              */
#define CALIB_MCUID_RSV_1B_0447_DEF                 (0U)             /* Reserve_1B-0447                                              */
#define CALIB_MCUID_RSV_1B_0448_DEF                 (0U)             /* Reserve_1B-0448                                              */
#define CALIB_MCUID_RSV_1B_0449_DEF                 (0U)             /* Reserve_1B-0449                                              */
#define CALIB_MCUID_RSV_1B_0450_DEF                 (0U)             /* Reserve_1B-0450                                              */
#define CALIB_MCUID_RSV_1B_0451_DEF                 (0U)             /* Reserve_1B-0451                                              */
#define CALIB_MCUID_RSV_1B_0452_DEF                 (0U)             /* Reserve_1B-0452                                              */
#define CALIB_MCUID_RSV_1B_0453_DEF                 (0U)             /* Reserve_1B-0453                                              */
#define CALIB_MCUID_RSV_1B_0454_DEF                 (0U)             /* Reserve_1B-0454                                              */
#define CALIB_MCUID_RSV_1B_0455_DEF                 (0U)             /* Reserve_1B-0455                                              */
#define CALIB_MCUID_RSV_1B_0456_DEF                 (0U)             /* Reserve_1B-0456                                              */
#define CALIB_MCUID_RSV_1B_0457_DEF                 (0U)             /* Reserve_1B-0457                                              */
#define CALIB_MCUID_RSV_1B_0458_DEF                 (0U)             /* Reserve_1B-0458                                              */
#define CALIB_MCUID_RSV_1B_0459_DEF                 (0U)             /* Reserve_1B-0459                                              */
#define CALIB_MCUID_RSV_1B_0460_DEF                 (0U)             /* Reserve_1B-0460                                              */
#define CALIB_MCUID_RSV_1B_0461_DEF                 (0U)             /* Reserve_1B-0461                                              */
#define CALIB_MCUID_RSV_1B_0462_DEF                 (0U)             /* Reserve_1B-0462                                              */
#define CALIB_MCUID_RSV_1B_0463_DEF                 (0U)             /* Reserve_1B-0463                                              */
#define CALIB_MCUID_RSV_1B_0464_DEF                 (0U)             /* Reserve_1B-0464                                              */
#define CALIB_MCUID_RSV_1B_0465_DEF                 (0U)             /* Reserve_1B-0465                                              */
#define CALIB_MCUID_RSV_1B_0466_DEF                 (0U)             /* Reserve_1B-0466                                              */
#define CALIB_MCUID_RSV_1B_0467_DEF                 (0U)             /* Reserve_1B-0467                                              */
#define CALIB_MCUID_RSV_1B_0468_DEF                 (0U)             /* Reserve_1B-0468                                              */
#define CALIB_MCUID_RSV_1B_0469_DEF                 (0U)             /* Reserve_1B-0469                                              */
#define CALIB_MCUID_RSV_1B_0470_DEF                 (0U)             /* Reserve_1B-0470                                              */
#define CALIB_MCUID_RSV_1B_0471_DEF                 (0U)             /* Reserve_1B-0471                                              */
#define CALIB_MCUID_RSV_1B_0472_DEF                 (0U)             /* Reserve_1B-0472                                              */
#define CALIB_MCUID_RSV_1B_0473_DEF                 (0U)             /* Reserve_1B-0473                                              */
#define CALIB_MCUID_RSV_1B_0474_DEF                 (0U)             /* Reserve_1B-0474                                              */
#define CALIB_MCUID_RSV_1B_0475_DEF                 (0U)             /* Reserve_1B-0475                                              */
#define CALIB_MCUID_RSV_1B_0476_DEF                 (0U)             /* Reserve_1B-0476                                              */
#define CALIB_MCUID_RSV_1B_0477_DEF                 (0U)             /* Reserve_1B-0477                                              */
#define CALIB_MCUID_RSV_1B_0478_DEF                 (0U)             /* Reserve_1B-0478                                              */
#define CALIB_MCUID_RSV_1B_0479_DEF                 (0U)             /* Reserve_1B-0479                                              */
#define CALIB_MCUID_RSV_1B_0480_DEF                 (0U)             /* Reserve_1B-0480                                              */
#define CALIB_MCUID_RSV_1B_0481_DEF                 (0U)             /* Reserve_1B-0481                                              */
#define CALIB_MCUID_RSV_1B_0482_DEF                 (0U)             /* Reserve_1B-0482                                              */
#define CALIB_MCUID_RSV_1B_0483_DEF                 (0U)             /* Reserve_1B-0483                                              */
#define CALIB_MCUID_RSV_1B_0484_DEF                 (0U)             /* Reserve_1B-0484                                              */
#define CALIB_MCUID_RSV_1B_0485_DEF                 (0U)             /* Reserve_1B-0485                                              */
#define CALIB_MCUID_RSV_1B_0486_DEF                 (0U)             /* Reserve_1B-0486                                              */
#define CALIB_MCUID_RSV_1B_0487_DEF                 (0U)             /* Reserve_1B-0487                                              */
#define CALIB_MCUID_RSV_1B_0488_DEF                 (0U)             /* Reserve_1B-0488                                              */
#define CALIB_MCUID_RSV_1B_0489_DEF                 (0U)             /* Reserve_1B-0489                                              */
#define CALIB_MCUID_RSV_1B_0490_DEF                 (0U)             /* Reserve_1B-0490                                              */
#define CALIB_MCUID_RSV_1B_0491_DEF                 (0U)             /* Reserve_1B-0491                                              */
#define CALIB_MCUID_RSV_1B_0492_DEF                 (0U)             /* Reserve_1B-0492                                              */
#define CALIB_MCUID_RSV_1B_0493_DEF                 (0U)             /* Reserve_1B-0493                                              */
#define CALIB_MCUID_RSV_1B_0494_DEF                 (0U)             /* Reserve_1B-0494                                              */
#define CALIB_MCUID_RSV_1B_0495_DEF                 (0U)             /* Reserve_1B-0495                                              */
#define CALIB_MCUID_RSV_1B_0496_DEF                 (0U)             /* Reserve_1B-0496                                              */
#define CALIB_MCUID_RSV_1B_0497_DEF                 (0U)             /* Reserve_1B-0497                                              */
#define CALIB_MCUID_RSV_1B_0498_DEF                 (0U)             /* Reserve_1B-0498                                              */
#define CALIB_MCUID_RSV_1B_0499_DEF                 (0U)             /* Reserve_1B-0499                                              */
#define CALIB_MCUID_RSV_1B_0500_DEF                 (0U)             /* Reserve_1B-0500                                              */
#define CALIB_MCUID_RSV_1B_0501_DEF                 (0U)             /* Reserve_1B-0501                                              */
#define CALIB_MCUID_RSV_1B_0502_DEF                 (0U)             /* Reserve_1B-0502                                              */
#define CALIB_MCUID_RSV_1B_0503_DEF                 (0U)             /* Reserve_1B-0503                                              */
#define CALIB_MCUID_RSV_1B_0504_DEF                 (0U)             /* Reserve_1B-0504                                              */
#define CALIB_MCUID_RSV_1B_0505_DEF                 (0U)             /* Reserve_1B-0505                                              */
#define CALIB_MCUID_RSV_1B_0506_DEF                 (0U)             /* Reserve_1B-0506                                              */
#define CALIB_MCUID_RSV_1B_0507_DEF                 (0U)             /* Reserve_1B-0507                                              */
#define CALIB_MCUID_RSV_1B_0508_DEF                 (0U)             /* Reserve_1B-0508                                              */
#define CALIB_MCUID_RSV_1B_0509_DEF                 (0U)             /* Reserve_1B-0509                                              */
#define CALIB_MCUID_RSV_1B_0510_DEF                 (0U)             /* Reserve_1B-0510                                              */
#define CALIB_MCUID_RSV_1B_0511_DEF                 (0U)             /* Reserve_1B-0511                                              */
#define CALIB_MCUID_RSV_1B_0512_DEF                 (0U)             /* Reserve_1B-0512                                              */
#define CALIB_MCUID_RSV_1B_0513_DEF                 (0U)             /* Reserve_1B-0513                                              */
#define CALIB_MCUID_RSV_1B_0514_DEF                 (0U)             /* Reserve_1B-0514                                              */
#define CALIB_MCUID_RSV_1B_0515_DEF                 (0U)             /* Reserve_1B-0515                                              */
#define CALIB_MCUID_RSV_1B_0516_DEF                 (0U)             /* Reserve_1B-0516                                              */
#define CALIB_MCUID_RSV_1B_0517_DEF                 (0U)             /* Reserve_1B-0517                                              */
#define CALIB_MCUID_RSV_1B_0518_DEF                 (0U)             /* Reserve_1B-0518                                              */
#define CALIB_MCUID_RSV_1B_0519_DEF                 (0U)             /* Reserve_1B-0519                                              */
#define CALIB_MCUID_RSV_1B_0520_DEF                 (0U)             /* Reserve_1B-0520                                              */
#define CALIB_MCUID_RSV_1B_0521_DEF                 (0U)             /* Reserve_1B-0521                                              */
#define CALIB_MCUID_RSV_1B_0522_DEF                 (0U)             /* Reserve_1B-0522                                              */
#define CALIB_MCUID_RSV_1B_0523_DEF                 (0U)             /* Reserve_1B-0523                                              */
#define CALIB_MCUID_RSV_1B_0524_DEF                 (0U)             /* Reserve_1B-0524                                              */
#define CALIB_MCUID_RSV_1B_0525_DEF                 (0U)             /* Reserve_1B-0525                                              */
#define CALIB_MCUID_RSV_1B_0526_DEF                 (0U)             /* Reserve_1B-0526                                              */
#define CALIB_MCUID_RSV_1B_0527_DEF                 (0U)             /* Reserve_1B-0527                                              */
#define CALIB_MCUID_RSV_1B_0528_DEF                 (0U)             /* Reserve_1B-0528                                              */
#define CALIB_MCUID_RSV_1B_0529_DEF                 (0U)             /* Reserve_1B-0529                                              */
#define CALIB_MCUID_RSV_1B_0530_DEF                 (0U)             /* Reserve_1B-0530                                              */
#define CALIB_MCUID_RSV_1B_0531_DEF                 (0U)             /* Reserve_1B-0531                                              */
#define CALIB_MCUID_RSV_1B_0532_DEF                 (0U)             /* Reserve_1B-0532                                              */
#define CALIB_MCUID_RSV_1B_0533_DEF                 (0U)             /* Reserve_1B-0533                                              */
#define CALIB_MCUID_RSV_1B_0534_DEF                 (0U)             /* Reserve_1B-0534                                              */
#define CALIB_MCUID_RSV_1B_0535_DEF                 (0U)             /* Reserve_1B-0535                                              */
#define CALIB_MCUID_RSV_1B_0536_DEF                 (0U)             /* Reserve_1B-0536                                              */
#define CALIB_MCUID_RSV_1B_0537_DEF                 (0U)             /* Reserve_1B-0537                                              */
#define CALIB_MCUID_RSV_1B_0538_DEF                 (0U)             /* Reserve_1B-0538                                              */
#define CALIB_MCUID_RSV_1B_0539_DEF                 (0U)             /* Reserve_1B-0539                                              */
#define CALIB_MCUID_RSV_1B_0540_DEF                 (0U)             /* Reserve_1B-0540                                              */
#define CALIB_MCUID_RSV_1B_0541_DEF                 (0U)             /* Reserve_1B-0541                                              */
#define CALIB_MCUID_RSV_1B_0542_DEF                 (0U)             /* Reserve_1B-0542                                              */
#define CALIB_MCUID_RSV_1B_0543_DEF                 (0U)             /* Reserve_1B-0543                                              */
#define CALIB_MCUID_RSV_1B_0544_DEF                 (0U)             /* Reserve_1B-0544                                              */
#define CALIB_MCUID_RSV_1B_0545_DEF                 (0U)             /* Reserve_1B-0545                                              */
#define CALIB_MCUID_RSV_1B_0546_DEF                 (0U)             /* Reserve_1B-0546                                              */
#define CALIB_MCUID_RSV_1B_0547_DEF                 (0U)             /* Reserve_1B-0547                                              */
#define CALIB_MCUID_RSV_1B_0548_DEF                 (0U)             /* Reserve_1B-0548                                              */
#define CALIB_MCUID_RSV_1B_0549_DEF                 (0U)             /* Reserve_1B-0549                                              */
#define CALIB_MCUID_RSV_1B_0550_DEF                 (0U)             /* Reserve_1B-0550                                              */
#define CALIB_MCUID_RSV_1B_0551_DEF                 (0U)             /* Reserve_1B-0551                                              */
#define CALIB_MCUID_RSV_1B_0552_DEF                 (0U)             /* Reserve_1B-0552                                              */
#define CALIB_MCUID_RSV_1B_0553_DEF                 (0U)             /* Reserve_1B-0553                                              */
#define CALIB_MCUID_RSV_1B_0554_DEF                 (0U)             /* Reserve_1B-0554                                              */
#define CALIB_MCUID_RSV_1B_0555_DEF                 (0U)             /* Reserve_1B-0555                                              */
#define CALIB_MCUID_RSV_1B_0556_DEF                 (0U)             /* Reserve_1B-0556                                              */
#define CALIB_MCUID_RSV_1B_0557_DEF                 (0U)             /* Reserve_1B-0557                                              */
#define CALIB_MCUID_RSV_1B_0558_DEF                 (0U)             /* Reserve_1B-0558                                              */
#define CALIB_MCUID_RSV_1B_0559_DEF                 (0U)             /* Reserve_1B-0559                                              */
#define CALIB_MCUID_RSV_1B_0560_DEF                 (0U)             /* Reserve_1B-0560                                              */
#define CALIB_MCUID_RSV_1B_0561_DEF                 (0U)             /* Reserve_1B-0561                                              */
#define CALIB_MCUID_RSV_1B_0562_DEF                 (0U)             /* Reserve_1B-0562                                              */
#define CALIB_MCUID_RSV_1B_0563_DEF                 (0U)             /* Reserve_1B-0563                                              */
#define CALIB_MCUID_RSV_1B_0564_DEF                 (0U)             /* Reserve_1B-0564                                              */
#define CALIB_MCUID_RSV_1B_0565_DEF                 (0U)             /* Reserve_1B-0565                                              */
#define CALIB_MCUID_RSV_1B_0566_DEF                 (0U)             /* Reserve_1B-0566                                              */
#define CALIB_MCUID_RSV_1B_0567_DEF                 (0U)             /* Reserve_1B-0567                                              */
#define CALIB_MCUID_RSV_1B_0568_DEF                 (0U)             /* Reserve_1B-0568                                              */
#define CALIB_MCUID_RSV_1B_0569_DEF                 (0U)             /* Reserve_1B-0569                                              */
#define CALIB_MCUID_RSV_1B_0570_DEF                 (0U)             /* Reserve_1B-0570                                              */
#define CALIB_MCUID_RSV_1B_0571_DEF                 (0U)             /* Reserve_1B-0571                                              */
#define CALIB_MCUID_RSV_1B_0572_DEF                 (0U)             /* Reserve_1B-0572                                              */
#define CALIB_MCUID_RSV_1B_0573_DEF                 (0U)             /* Reserve_1B-0573                                              */
#define CALIB_MCUID_RSV_1B_0574_DEF                 (0U)             /* Reserve_1B-0574                                              */
#define CALIB_MCUID_RSV_1B_0575_DEF                 (0U)             /* Reserve_1B-0575                                              */
#define CALIB_MCUID_RSV_1B_0576_DEF                 (0U)             /* Reserve_1B-0576                                              */
#define CALIB_MCUID_RSV_1B_0577_DEF                 (0U)             /* Reserve_1B-0577                                              */
#define CALIB_MCUID_RSV_1B_0578_DEF                 (0U)             /* Reserve_1B-0578                                              */
#define CALIB_MCUID_RSV_1B_0579_DEF                 (0U)             /* Reserve_1B-0579                                              */
#define CALIB_MCUID_RSV_1B_0580_DEF                 (0U)             /* Reserve_1B-0580                                              */
#define CALIB_MCUID_RSV_1B_0581_DEF                 (0U)             /* Reserve_1B-0581                                              */
#define CALIB_MCUID_RSV_1B_0582_DEF                 (0U)             /* Reserve_1B-0582                                              */
#define CALIB_MCUID_RSV_1B_0583_DEF                 (0U)             /* Reserve_1B-0583                                              */
#define CALIB_MCUID_RSV_1B_0584_DEF                 (0U)             /* Reserve_1B-0584                                              */
#define CALIB_MCUID_RSV_1B_0585_DEF                 (0U)             /* Reserve_1B-0585                                              */
#define CALIB_MCUID_RSV_1B_0586_DEF                 (0U)             /* Reserve_1B-0586                                              */
#define CALIB_MCUID_RSV_1B_0587_DEF                 (0U)             /* Reserve_1B-0587                                              */
#define CALIB_MCUID_RSV_1B_0588_DEF                 (0U)             /* Reserve_1B-0588                                              */
#define CALIB_MCUID_RSV_1B_0589_DEF                 (0U)             /* Reserve_1B-0589                                              */
#define CALIB_MCUID_RSV_1B_0590_DEF                 (0U)             /* Reserve_1B-0590                                              */
#define CALIB_MCUID_RSV_1B_0591_DEF                 (0U)             /* Reserve_1B-0591                                              */
#define CALIB_MCUID_RSV_1B_0592_DEF                 (0U)             /* Reserve_1B-0592                                              */
#define CALIB_MCUID_RSV_1B_0593_DEF                 (0U)             /* Reserve_1B-0593                                              */
#define CALIB_MCUID_RSV_1B_0594_DEF                 (0U)             /* Reserve_1B-0594                                              */
#define CALIB_MCUID_RSV_1B_0595_DEF                 (0U)             /* Reserve_1B-0595                                              */
#define CALIB_MCUID_RSV_1B_0596_DEF                 (0U)             /* Reserve_1B-0596                                              */
#define CALIB_MCUID_RSV_1B_0597_DEF                 (0U)             /* Reserve_1B-0597                                              */
#define CALIB_MCUID_RSV_1B_0598_DEF                 (0U)             /* Reserve_1B-0598                                              */
#define CALIB_MCUID_RSV_1B_0599_DEF                 (0U)             /* Reserve_1B-0599                                              */
#define CALIB_MCUID_RSV_1B_0600_DEF                 (0U)             /* Reserve_1B-0600                                              */
#define CALIB_MCUID_RSV_1B_0601_DEF                 (0U)             /* Reserve_1B-0601                                              */
#define CALIB_MCUID_RSV_1B_0602_DEF                 (0U)             /* Reserve_1B-0602                                              */
#define CALIB_MCUID_RSV_1B_0603_DEF                 (0U)             /* Reserve_1B-0603                                              */
#define CALIB_MCUID_RSV_1B_0604_DEF                 (0U)             /* Reserve_1B-0604                                              */
#define CALIB_MCUID_RSV_1B_0605_DEF                 (0U)             /* Reserve_1B-0605                                              */
#define CALIB_MCUID_RSV_1B_0606_DEF                 (0U)             /* Reserve_1B-0606                                              */
#define CALIB_MCUID_RSV_1B_0607_DEF                 (0U)             /* Reserve_1B-0607                                              */
#define CALIB_MCUID_RSV_1B_0608_DEF                 (0U)             /* Reserve_1B-0608                                              */
#define CALIB_MCUID_RSV_1B_0609_DEF                 (0U)             /* Reserve_1B-0609                                              */
#define CALIB_MCUID_RSV_1B_0610_DEF                 (0U)             /* Reserve_1B-0610                                              */
#define CALIB_MCUID_RSV_1B_0611_DEF                 (0U)             /* Reserve_1B-0611                                              */
#define CALIB_MCUID_RSV_1B_0612_DEF                 (0U)             /* Reserve_1B-0612                                              */
#define CALIB_MCUID_RSV_1B_0613_DEF                 (0U)             /* Reserve_1B-0613                                              */
#define CALIB_MCUID_RSV_1B_0614_DEF                 (0U)             /* Reserve_1B-0614                                              */
#define CALIB_MCUID_RSV_1B_0615_DEF                 (0U)             /* Reserve_1B-0615                                              */
#define CALIB_MCUID_RSV_1B_0616_DEF                 (0U)             /* Reserve_1B-0616                                              */
#define CALIB_MCUID_RSV_1B_0617_DEF                 (0U)             /* Reserve_1B-0617                                              */
#define CALIB_MCUID_RSV_1B_0618_DEF                 (0U)             /* Reserve_1B-0618                                              */
#define CALIB_MCUID_RSV_1B_0619_DEF                 (0U)             /* Reserve_1B-0619                                              */
#define CALIB_MCUID_RSV_1B_0620_DEF                 (0U)             /* Reserve_1B-0620                                              */
#define CALIB_MCUID_RSV_1B_0621_DEF                 (0U)             /* Reserve_1B-0621                                              */
#define CALIB_MCUID_RSV_1B_0622_DEF                 (0U)             /* Reserve_1B-0622                                              */
#define CALIB_MCUID_RSV_1B_0623_DEF                 (0U)             /* Reserve_1B-0623                                              */
#define CALIB_MCUID_RSV_1B_0624_DEF                 (0U)             /* Reserve_1B-0624                                              */
#define CALIB_MCUID_RSV_1B_0625_DEF                 (0U)             /* Reserve_1B-0625                                              */
#define CALIB_MCUID_RSV_1B_0626_DEF                 (0U)             /* Reserve_1B-0626                                              */
#define CALIB_MCUID_RSV_1B_0627_DEF                 (0U)             /* Reserve_1B-0627                                              */
#define CALIB_MCUID_RSV_1B_0628_DEF                 (0U)             /* Reserve_1B-0628                                              */
#define CALIB_MCUID_RSV_1B_0629_DEF                 (0U)             /* Reserve_1B-0629                                              */
#define CALIB_MCUID_RSV_1B_0630_DEF                 (0U)             /* Reserve_1B-0630                                              */
#define CALIB_MCUID_RSV_1B_0631_DEF                 (0U)             /* Reserve_1B-0631                                              */
#define CALIB_MCUID_RSV_1B_0632_DEF                 (0U)             /* Reserve_1B-0632                                              */
#define CALIB_MCUID_RSV_1B_0633_DEF                 (0U)             /* Reserve_1B-0633                                              */
#define CALIB_MCUID_RSV_1B_0634_DEF                 (0U)             /* Reserve_1B-0634                                              */
#define CALIB_MCUID_RSV_1B_0635_DEF                 (0U)             /* Reserve_1B-0635                                              */
#define CALIB_MCUID_RSV_1B_0636_DEF                 (0U)             /* Reserve_1B-0636                                              */
#define CALIB_MCUID_RSV_1B_0637_DEF                 (0U)             /* Reserve_1B-0637                                              */
#define CALIB_MCUID_RSV_1B_0638_DEF                 (0U)             /* Reserve_1B-0638                                              */
#define CALIB_MCUID_RSV_1B_0639_DEF                 (0U)             /* Reserve_1B-0639                                              */
#define CALIB_MCUID_RSV_1B_0640_DEF                 (0U)             /* Reserve_1B-0640                                              */
#define CALIB_MCUID_RSV_1B_0641_DEF                 (0U)             /* Reserve_1B-0641                                              */
#define CALIB_MCUID_RSV_1B_0642_DEF                 (0U)             /* Reserve_1B-0642                                              */
#define CALIB_MCUID_RSV_1B_0643_DEF                 (0U)             /* Reserve_1B-0643                                              */
#define CALIB_MCUID_RSV_1B_0644_DEF                 (0U)             /* Reserve_1B-0644                                              */
#define CALIB_MCUID_RSV_1B_0645_DEF                 (0U)             /* Reserve_1B-0645                                              */
#define CALIB_MCUID_RSV_1B_0646_DEF                 (0U)             /* Reserve_1B-0646                                              */
#define CALIB_MCUID_RSV_1B_0647_DEF                 (0U)             /* Reserve_1B-0647                                              */
#define CALIB_MCUID_RSV_1B_0648_DEF                 (0U)             /* Reserve_1B-0648                                              */
#define CALIB_MCUID_RSV_1B_0649_DEF                 (0U)             /* Reserve_1B-0649                                              */
#define CALIB_MCUID_RSV_1B_0650_DEF                 (0U)             /* Reserve_1B-0650                                              */
#define CALIB_MCUID_RSV_1B_0651_DEF                 (0U)             /* Reserve_1B-0651                                              */
#define CALIB_MCUID_RSV_1B_0652_DEF                 (0U)             /* Reserve_1B-0652                                              */
#define CALIB_MCUID_RSV_1B_0653_DEF                 (0U)             /* Reserve_1B-0653                                              */
#define CALIB_MCUID_RSV_1B_0654_DEF                 (0U)             /* Reserve_1B-0654                                              */
#define CALIB_MCUID_RSV_1B_0655_DEF                 (0U)             /* Reserve_1B-0655                                              */
#define CALIB_MCUID_RSV_1B_0656_DEF                 (0U)             /* Reserve_1B-0656                                              */
#define CALIB_MCUID_RSV_1B_0657_DEF                 (0U)             /* Reserve_1B-0657                                              */
#define CALIB_MCUID_RSV_1B_0658_DEF                 (0U)             /* Reserve_1B-0658                                              */
#define CALIB_MCUID_RSV_1B_0659_DEF                 (0U)             /* Reserve_1B-0659                                              */
#define CALIB_MCUID_RSV_1B_0660_DEF                 (0U)             /* Reserve_1B-0660                                              */
#define CALIB_MCUID_RSV_1B_0661_DEF                 (0U)             /* Reserve_1B-0661                                              */
#define CALIB_MCUID_RSV_1B_0662_DEF                 (0U)             /* Reserve_1B-0662                                              */
#define CALIB_MCUID_RSV_1B_0663_DEF                 (0U)             /* Reserve_1B-0663                                              */
#define CALIB_MCUID_RSV_1B_0664_DEF                 (0U)             /* Reserve_1B-0664                                              */
#define CALIB_MCUID_RSV_1B_0665_DEF                 (0U)             /* Reserve_1B-0665                                              */
#define CALIB_MCUID_RSV_1B_0666_DEF                 (0U)             /* Reserve_1B-0666                                              */
#define CALIB_MCUID_RSV_1B_0667_DEF                 (0U)             /* Reserve_1B-0667                                              */
#define CALIB_MCUID_RSV_1B_0668_DEF                 (0U)             /* Reserve_1B-0668                                              */
#define CALIB_MCUID_RSV_1B_0669_DEF                 (0U)             /* Reserve_1B-0669                                              */
#define CALIB_MCUID_RSV_1B_0670_DEF                 (0U)             /* Reserve_1B-0670                                              */
#define CALIB_MCUID_RSV_1B_0671_DEF                 (0U)             /* Reserve_1B-0671                                              */
#define CALIB_MCUID_RSV_1B_0672_DEF                 (0U)             /* Reserve_1B-0672                                              */
#define CALIB_MCUID_RSV_1B_0673_DEF                 (0U)             /* Reserve_1B-0673                                              */
#define CALIB_MCUID_RSV_1B_0674_DEF                 (0U)             /* Reserve_1B-0674                                              */
#define CALIB_MCUID_RSV_1B_0675_DEF                 (0U)             /* Reserve_1B-0675                                              */
#define CALIB_MCUID_RSV_1B_0676_DEF                 (0U)             /* Reserve_1B-0676                                              */
#define CALIB_MCUID_RSV_1B_0677_DEF                 (0U)             /* Reserve_1B-0677                                              */
#define CALIB_MCUID_RSV_1B_0678_DEF                 (0U)             /* Reserve_1B-0678                                              */
#define CALIB_MCUID_RSV_1B_0679_DEF                 (0U)             /* Reserve_1B-0679                                              */
#define CALIB_MCUID_RSV_1B_0680_DEF                 (0U)             /* Reserve_1B-0680                                              */
#define CALIB_MCUID_RSV_1B_0681_DEF                 (0U)             /* Reserve_1B-0681                                              */
#define CALIB_MCUID_RSV_1B_0682_DEF                 (0U)             /* Reserve_1B-0682                                              */
#define CALIB_MCUID_RSV_1B_0683_DEF                 (0U)             /* Reserve_1B-0683                                              */
#define CALIB_MCUID_RSV_1B_0684_DEF                 (0U)             /* Reserve_1B-0684                                              */
#define CALIB_MCUID_RSV_1B_0685_DEF                 (0U)             /* Reserve_1B-0685                                              */
#define CALIB_MCUID_RSV_1B_0686_DEF                 (0U)             /* Reserve_1B-0686                                              */
#define CALIB_MCUID_RSV_1B_0687_DEF                 (0U)             /* Reserve_1B-0687                                              */
#define CALIB_MCUID_RSV_1B_0688_DEF                 (0U)             /* Reserve_1B-0688                                              */
#define CALIB_MCUID_RSV_1B_0689_DEF                 (0U)             /* Reserve_1B-0689                                              */
#define CALIB_MCUID_RSV_1B_0690_DEF                 (0U)             /* Reserve_1B-0690                                              */
#define CALIB_MCUID_RSV_1B_0691_DEF                 (0U)             /* Reserve_1B-0691                                              */
#define CALIB_MCUID_RSV_1B_0692_DEF                 (0U)             /* Reserve_1B-0692                                              */
#define CALIB_MCUID_RSV_1B_0693_DEF                 (0U)             /* Reserve_1B-0693                                              */
#define CALIB_MCUID_RSV_1B_0694_DEF                 (0U)             /* Reserve_1B-0694                                              */
#define CALIB_MCUID_RSV_1B_0695_DEF                 (0U)             /* Reserve_1B-0695                                              */
#define CALIB_MCUID_RSV_1B_0696_DEF                 (0U)             /* Reserve_1B-0696                                              */
#define CALIB_MCUID_RSV_1B_0697_DEF                 (0U)             /* Reserve_1B-0697                                              */
#define CALIB_MCUID_RSV_1B_0698_DEF                 (0U)             /* Reserve_1B-0698                                              */
#define CALIB_MCUID_RSV_1B_0699_DEF                 (0U)             /* Reserve_1B-0699                                              */
#define CALIB_MCUID_RSV_1B_0700_DEF                 (0U)             /* Reserve_1B-0700                                              */
#define CALIB_MCUID_RSV_1B_0701_DEF                 (0U)             /* Reserve_1B-0701                                              */
#define CALIB_MCUID_RSV_1B_0702_DEF                 (0U)             /* Reserve_1B-0702                                              */
#define CALIB_MCUID_RSV_1B_0703_DEF                 (0U)             /* Reserve_1B-0703                                              */
#define CALIB_MCUID_RSV_1B_0704_DEF                 (0U)             /* Reserve_1B-0704                                              */
#define CALIB_MCUID_RSV_1B_0705_DEF                 (0U)             /* Reserve_1B-0705                                              */
#define CALIB_MCUID_RSV_1B_0706_DEF                 (0U)             /* Reserve_1B-0706                                              */
#define CALIB_MCUID_RSV_1B_0707_DEF                 (0U)             /* Reserve_1B-0707                                              */
#define CALIB_MCUID_RSV_1B_0708_DEF                 (0U)             /* Reserve_1B-0708                                              */
#define CALIB_MCUID_RSV_1B_0709_DEF                 (0U)             /* Reserve_1B-0709                                              */
#define CALIB_MCUID_RSV_1B_0710_DEF                 (0U)             /* Reserve_1B-0710                                              */
#define CALIB_MCUID_RSV_1B_0711_DEF                 (0U)             /* Reserve_1B-0711                                              */
#define CALIB_MCUID_RSV_1B_0712_DEF                 (0U)             /* Reserve_1B-0712                                              */
#define CALIB_MCUID_RSV_1B_0713_DEF                 (0U)             /* Reserve_1B-0713                                              */
#define CALIB_MCUID_RSV_1B_0714_DEF                 (0U)             /* Reserve_1B-0714                                              */
#define CALIB_MCUID_RSV_1B_0715_DEF                 (0U)             /* Reserve_1B-0715                                              */
#define CALIB_MCUID_RSV_1B_0716_DEF                 (0U)             /* Reserve_1B-0716                                              */
#define CALIB_MCUID_RSV_1B_0717_DEF                 (0U)             /* Reserve_1B-0717                                              */
#define CALIB_MCUID_RSV_1B_0718_DEF                 (0U)             /* Reserve_1B-0718                                              */
#define CALIB_MCUID_RSV_1B_0719_DEF                 (0U)             /* Reserve_1B-0719                                              */
#define CALIB_MCUID_RSV_1B_0720_DEF                 (0U)             /* Reserve_1B-0720                                              */
#define CALIB_MCUID_RSV_1B_0721_DEF                 (0U)             /* Reserve_1B-0721                                              */
#define CALIB_MCUID_RSV_1B_0722_DEF                 (0U)             /* Reserve_1B-0722                                              */
#define CALIB_MCUID_RSV_1B_0723_DEF                 (0U)             /* Reserve_1B-0723                                              */
#define CALIB_MCUID_RSV_1B_0724_DEF                 (0U)             /* Reserve_1B-0724                                              */
#define CALIB_MCUID_RSV_1B_0725_DEF                 (0U)             /* Reserve_1B-0725                                              */
#define CALIB_MCUID_RSV_1B_0726_DEF                 (0U)             /* Reserve_1B-0726                                              */
#define CALIB_MCUID_RSV_1B_0727_DEF                 (0U)             /* Reserve_1B-0727                                              */
#define CALIB_MCUID_RSV_1B_0728_DEF                 (0U)             /* Reserve_1B-0728                                              */
#define CALIB_MCUID_RSV_1B_0729_DEF                 (0U)             /* Reserve_1B-0729                                              */
#define CALIB_MCUID_RSV_1B_0730_DEF                 (0U)             /* Reserve_1B-0730                                              */
#define CALIB_MCUID_RSV_1B_0731_DEF                 (0U)             /* Reserve_1B-0731                                              */
#define CALIB_MCUID_RSV_1B_0732_DEF                 (0U)             /* Reserve_1B-0732                                              */
#define CALIB_MCUID_RSV_1B_0733_DEF                 (0U)             /* Reserve_1B-0733                                              */
#define CALIB_MCUID_RSV_1B_0734_DEF                 (0U)             /* Reserve_1B-0734                                              */
#define CALIB_MCUID_RSV_1B_0735_DEF                 (0U)             /* Reserve_1B-0735                                              */
#define CALIB_MCUID_RSV_1B_0736_DEF                 (0U)             /* Reserve_1B-0736                                              */
#define CALIB_MCUID_RSV_1B_0737_DEF                 (0U)             /* Reserve_1B-0737                                              */
#define CALIB_MCUID_RSV_1B_0738_DEF                 (0U)             /* Reserve_1B-0738                                              */
#define CALIB_MCUID_RSV_1B_0739_DEF                 (0U)             /* Reserve_1B-0739                                              */
#define CALIB_MCUID_RSV_1B_0740_DEF                 (0U)             /* Reserve_1B-0740                                              */
#define CALIB_MCUID_RSV_1B_0741_DEF                 (0U)             /* Reserve_1B-0741                                              */
#define CALIB_MCUID_RSV_1B_0742_DEF                 (0U)             /* Reserve_1B-0742                                              */
#define CALIB_MCUID_RSV_1B_0743_DEF                 (0U)             /* Reserve_1B-0743                                              */
#define CALIB_MCUID_RSV_1B_0744_DEF                 (0U)             /* Reserve_1B-0744                                              */
#define CALIB_MCUID_RSV_1B_0745_DEF                 (0U)             /* Reserve_1B-0745                                              */
#define CALIB_MCUID_RSV_1B_0746_DEF                 (0U)             /* Reserve_1B-0746                                              */
#define CALIB_MCUID_RSV_1B_0747_DEF                 (0U)             /* Reserve_1B-0747                                              */
#define CALIB_MCUID_RSV_1B_0748_DEF                 (0U)             /* Reserve_1B-0748                                              */
#define CALIB_MCUID_RSV_1B_0749_DEF                 (0U)             /* Reserve_1B-0749                                              */
#define CALIB_MCUID_RSV_1B_0750_DEF                 (0U)             /* Reserve_1B-0750                                              */
#define CALIB_MCUID_RSV_1B_0751_DEF                 (0U)             /* Reserve_1B-0751                                              */
#define CALIB_MCUID_RSV_1B_0752_DEF                 (0U)             /* Reserve_1B-0752                                              */
#define CALIB_MCUID_RSV_1B_0753_DEF                 (0U)             /* Reserve_1B-0753                                              */
#define CALIB_MCUID_RSV_1B_0754_DEF                 (0U)             /* Reserve_1B-0754                                              */
#define CALIB_MCUID_RSV_1B_0755_DEF                 (0U)             /* Reserve_1B-0755                                              */
#define CALIB_MCUID_RSV_1B_0756_DEF                 (0U)             /* Reserve_1B-0756                                              */
#define CALIB_MCUID0797_DEF                         (1U)             /* Constant write flag                                          */

#define CALIB_MCUID3002_DEF                         (400U)           /* Basic 7 Tones Reporting Tone Medium                          */
#define CALIB_MCUID3003_DEF                         (400U)           /* Basic 7 Tones Reporting Tone (Special) Medium                */
#define CALIB_MCUID3004_DEF                         (400U)           /* Basic 7 tones Reception tone Medium                          */
#define CALIB_MCUID3005_DEF                         (400U)           /* Basic 7 tones Reject tone Medium                             */
#define CALIB_MCUID3006_DEF                         (400U)           /* Basic 7 Tones Continuous Tone (low urgency) Medium           */
#define CALIB_MCUID3007_DEF                         (400U)           /* Basic 7 Tones Break off (medium urgency) Medium              */
#define CALIB_MCUID3008_DEF                         (400U)           /* Basic 7 tones Break off the procedure (high urgency) Medium  */
#define CALIB_MCUID3009_DEF                         (400U)           /* Basic 7 tone Continuous tone Medium                          */
#define CALIB_MCUID3010_DEF                         (400U)           /* Special sound (intermittent) PreDOT sound Medium             */
#define CALIB_MCUID3011_DEF                         (500U)           /* Basic 7 Tone Reporting Large                                 */
#define CALIB_MCUID3012_DEF                         (500U)           /* Basic 7 Tone Reporting (Special) Large                       */
#define CALIB_MCUID3013_DEF                         (500U)           /* Basic 7 tones Reception tone Large                           */
#define CALIB_MCUID3014_DEF                         (500U)           /* Basic 7 tone rejection Large                                 */
#define CALIB_MCUID3015_DEF                         (500U)           /* Basic 7 Tones Continuous Tone (Less Tightness) Large         */
#define CALIB_MCUID3016_DEF                         (500U)           /* Basic 7 Tones Continuous Tone (Medium Tightness) Large       */
#define CALIB_MCUID3017_DEF                         (500U)           /* Basic 7 Tones Continuous Tone (High Tension) Large           */
#define CALIB_MCUID3018_DEF                         (500U)           /* Basic 7 tone Continuous tone Large                           */
#define CALIB_MCUID3019_DEF                         (500U)           /* Special sound (intermittent) PreDOT sound Large              */
#define CALIB_MCUID3021_DEF                         (400U)           /* Regulatory/Assessment: SEA door open rejecting Medium        */
#define CALIB_MCUID3022_DEF                         (500U)           /* Regulations/Assessments: SEA Door Open Reject Large          */
#define CALIB_MCUID3023_DEF                         (400U)           /* Regulations/Assessments: PCS Warning, SEA Warning Medium     */
#define CALIB_MCUID3024_DEF                         (500U)           /* Regulations/Assessments: PCS Warning, SEA Warning Large      */
#define CALIB_MCUID0029_DEF                         (400U)           /* Reverse buzzer Intermittent MID                              */
#define CALIB_MCUID0746_DEF                         (500U)           /* Reverse buzzer Intermittent MAX                              */
#define CALIB_MCUID0030_DEF                         (400U)           /* seatbelt reminder buzzer(fmv) MID                            */
#define CALIB_MCUID0747_DEF                         (500U)           /* seatbelt reminder buzzer(fmv) MAX                            */
#define CALIB_MCUID0031_DEF                         (400U)           /* seatbelt reminder buzzer(level 1) MID                        */
#define CALIB_MCUID0748_DEF                         (500U)           /* seatbelt reminder buzzer(level 1) MAX                        */
#define CALIB_MCUID0032_DEF                         (400U)           /* seatbelt reminder buzzer(level 2) MID                        */
#define CALIB_MCUID0749_DEF                         (500U)           /* seatbelt reminder buzzer(level 2) MAX                        */
#define CALIB_MCUID0033_DEF                         (400U)           /* seatbelt reminder buzzer(si) MID                             */
#define CALIB_MCUID0750_DEF                         (500U)           /* seatbelt reminder buzzer(si) MAX                             */
#define CALIB_MCUID0067_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:0                      */
#define CALIB_MCUID0068_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:1                      */
#define CALIB_MCUID0069_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:2                      */
#define CALIB_MCUID0070_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:3                      */
#define CALIB_MCUID0071_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:4                      */
#define CALIB_MCUID0072_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:5                      */
#define CALIB_MCUID0073_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:6                      */
#define CALIB_MCUID0074_DEF                         (400U)           /* Clearance sonar buzzer Fr(SD) CSR_VOL:7                      */
#define CALIB_MCUID0075_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:0                      */
#define CALIB_MCUID0076_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:1                      */
#define CALIB_MCUID0077_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:2                      */
#define CALIB_MCUID0078_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:3                      */
#define CALIB_MCUID0079_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:4                      */
#define CALIB_MCUID0080_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:5                      */
#define CALIB_MCUID0081_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:6                      */
#define CALIB_MCUID0082_DEF                         (400U)           /* Clearance sonar buzzer Fr(MD) CSR_VOL:7                      */
#define CALIB_MCUID0083_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:0                      */
#define CALIB_MCUID0084_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:1                      */
#define CALIB_MCUID0085_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:2                      */
#define CALIB_MCUID0086_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:3                      */
#define CALIB_MCUID0087_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:4                      */
#define CALIB_MCUID0088_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:5                      */
#define CALIB_MCUID0089_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:6                      */
#define CALIB_MCUID0090_DEF                         (400U)           /* Clearance sonar buzzer Fr(LD) CSR_VOL:7                      */
#define CALIB_MCUID0091_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:0                      */
#define CALIB_MCUID0092_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:1                      */
#define CALIB_MCUID0093_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:2                      */
#define CALIB_MCUID0094_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:3                      */
#define CALIB_MCUID0095_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:4                      */
#define CALIB_MCUID0096_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:5                      */
#define CALIB_MCUID0097_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:6                      */
#define CALIB_MCUID0098_DEF                         (400U)           /* Clearance sonar buzzer Fr(FD) CSR_VOL:7                      */
#define CALIB_MCUID0099_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:0                      */
#define CALIB_MCUID0100_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:1                      */
#define CALIB_MCUID0101_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:2                      */
#define CALIB_MCUID0102_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:3                      */
#define CALIB_MCUID0103_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:4                      */
#define CALIB_MCUID0104_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:5                      */
#define CALIB_MCUID0105_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:6                      */
#define CALIB_MCUID0106_DEF                         (400U)           /* Clearance sonar buzzer Rr(SD) CSR_VOL:7                      */
#define CALIB_MCUID0107_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:0                      */
#define CALIB_MCUID0108_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:1                      */
#define CALIB_MCUID0109_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:2                      */
#define CALIB_MCUID0110_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:3                      */
#define CALIB_MCUID0111_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:4                      */
#define CALIB_MCUID0112_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:5                      */
#define CALIB_MCUID0113_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:6                      */
#define CALIB_MCUID0114_DEF                         (400U)           /* Clearance sonar buzzer Rr(MD) CSR_VOL:7                      */
#define CALIB_MCUID0115_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:0                      */
#define CALIB_MCUID0116_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:1                      */
#define CALIB_MCUID0117_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:2                      */
#define CALIB_MCUID0118_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:3                      */
#define CALIB_MCUID0119_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:4                      */
#define CALIB_MCUID0120_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:5                      */
#define CALIB_MCUID0121_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:6                      */
#define CALIB_MCUID0122_DEF                         (400U)           /* Clearance sonar buzzer Rr(LD) CSR_VOL:7                      */
#define CALIB_MCUID0123_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:0                      */
#define CALIB_MCUID0124_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:1                      */
#define CALIB_MCUID0125_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:2                      */
#define CALIB_MCUID0126_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:3                      */
#define CALIB_MCUID0127_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:4                      */
#define CALIB_MCUID0128_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:5                      */
#define CALIB_MCUID0129_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:6                      */
#define CALIB_MCUID0130_DEF                         (400U)           /* Clearance sonar buzzer Rr(FD) CSR_VOL:7                      */
#define CALIB_MCUID0131_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0                   */
#define CALIB_MCUID0132_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1                   */
#define CALIB_MCUID0133_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2                   */
#define CALIB_MCUID0134_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3                   */
#define CALIB_MCUID0135_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4                   */
#define CALIB_MCUID0136_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5                   */
#define CALIB_MCUID0137_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6                   */
#define CALIB_MCUID0138_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7                   */
#define CALIB_MCUID0139_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:0                   */
#define CALIB_MCUID0140_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:1                   */
#define CALIB_MCUID0141_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:2                   */
#define CALIB_MCUID0142_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:3                   */
#define CALIB_MCUID0143_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:4                   */
#define CALIB_MCUID0144_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:5                   */
#define CALIB_MCUID0145_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:6                   */
#define CALIB_MCUID0146_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:7                   */
#define CALIB_MCUID0155_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:0                   */
#define CALIB_MCUID0156_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:1                   */
#define CALIB_MCUID0157_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:2                   */
#define CALIB_MCUID0158_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:3                   */
#define CALIB_MCUID0159_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:4                   */
#define CALIB_MCUID0160_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:5                   */
#define CALIB_MCUID0161_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:6                   */
#define CALIB_MCUID0162_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:7                   */
#define CALIB_MCUID0171_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:0                   */
#define CALIB_MCUID0172_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:1                   */
#define CALIB_MCUID0173_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:2                   */
#define CALIB_MCUID0174_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:3                   */
#define CALIB_MCUID0175_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:4                   */
#define CALIB_MCUID0176_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:5                   */
#define CALIB_MCUID0177_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:6                   */
#define CALIB_MCUID0178_DEF                         (400U)           /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:7                   */
#define CALIB_MCUID0187_DEF                         (400U)           /* flasher start sound(low customize, low speed)                */
#define CALIB_MCUID0188_DEF                         (400U)           /* flasher start sound(low customize, mid speed)                */
#define CALIB_MCUID0189_DEF                         (400U)           /* flasher start sound(low customize, high speed)               */
#define CALIB_MCUID0190_DEF                         (400U)           /* flasher start sound(mid customize, low speed)                */
#define CALIB_MCUID0191_DEF                         (400U)           /* flasher start sound(mid customize, mid speed)                */
#define CALIB_MCUID0192_DEF                         (400U)           /* flasher start sound(mid customize, high speed)               */
#define CALIB_MCUID0193_DEF                         (500U)           /* flasher start sound(high customize, low speed)               */
#define CALIB_MCUID0194_DEF                         (500U)           /* flasher start sound(high customize, mid speed)               */
#define CALIB_MCUID0195_DEF                         (500U)           /* flasher start sound(high customize, high speed)              */
#define CALIB_MCUID0196_DEF                         (400U)           /* flasher finish sound(low customize, low speed)               */
#define CALIB_MCUID0197_DEF                         (400U)           /* flasher finish sound(low customize, mid speed)               */
#define CALIB_MCUID0198_DEF                         (400U)           /* flasher finish sound(low customize, high speed)              */
#define CALIB_MCUID0199_DEF                         (400U)           /* flasher finish sound(mid customize, low speed)               */
#define CALIB_MCUID0200_DEF                         (400U)           /* flasher finish sound(mid customize, mid speed)               */
#define CALIB_MCUID0201_DEF                         (400U)           /* flasher finish sound(mid customize, high speed)              */
#define CALIB_MCUID0202_DEF                         (500U)           /* flasher finish sound(high customize, low speed)              */
#define CALIB_MCUID0203_DEF                         (500U)           /* flasher finish sound(high customize, mid speed)              */
#define CALIB_MCUID0204_DEF                         (500U)           /* flasher finish sound(high customize, high speed)             */
#define CALIB_MCUID0205_DEF                         (400U)           /* 2 channels multiplex playing                                 */
#define CALIB_MCUID0206_DEF                         (400U)           /* 3 channels multiplex playing                                 */
#define CALIB_MCUID0207_DEF                         (400U)           /* 4 channels multiplex playing                                 */
#define CALIB_MCUID0208_DEF                         (400U)           /* 5 channels multiplex playing                                 */
#define CALIB_MCUID0915_DEF                         (50U)            /* RCTA buzzer CSR_VOL:0                                        */
#define CALIB_MCUID0916_DEF                         (60U)            /* RCTA buzzer CSR_VOL:1                                        */
#define CALIB_MCUID0917_DEF                         (80U)            /* RCTA buzzer CSR_VOL:2                                        */
#define CALIB_MCUID0918_DEF                         (100U)           /* RCTA buzzer CSR_VOL:3                                        */
#define CALIB_MCUID0919_DEF                         (120U)           /* RCTA buzzer CSR_VOL:4                                        */
#define CALIB_MCUID0920_DEF                         (150U)           /* RCTA buzzer CSR_VOL:5                                        */
#define CALIB_MCUID0921_DEF                         (190U)           /* RCTA buzzer CSR_VOL:6                                        */
#define CALIB_MCUID0922_DEF                         (240U)           /* RCTA buzzer CSR_VOL:7                                        */
#define CALIB_MCUID0757_DEF                         (217U)           /* Digital meter vehicle speed for Usa/Canada(20 km/h)          */
#define CALIB_MCUID0758_DEF                         (428U)           /* Digital meter vehicle speed for Usa/Canada(40 km/h)          */
#define CALIB_MCUID0759_DEF                         (628U)           /* Digital meter vehicle speed for Usa/Canada(59 km/h)          */
#define CALIB_MCUID0760_DEF                         (843U)           /* Digital meter vehicle speed for Usa/Canada(80 km/h)          */
#define CALIB_MCUID0761_DEF                         (1047U)          /* Digital meter vehicle speed for Usa/Canada(100 km/h)         */
#define CALIB_MCUID0762_DEF                         (1254U)          /* Digital meter vehicle speed for Usa/Canada(120 km/h)         */
#define CALIB_MCUID0763_DEF                         (1460U)          /* Digital meter vehicle speed for Usa/Canada(140 km/h)         */
#define CALIB_MCUID0764_DEF                         (1668U)          /* Digital meter vehicle speed for Usa/Canada(160 km/h)         */
#define CALIB_MCUID0765_DEF                         (1875U)          /* Digital meter vehicle speed for Usa/Canada(180 km/h)         */
#define CALIB_MCUID0766_DEF                         (2082U)          /* Digital meter vehicle speed for Usa/Canada(200 km/h)         */
#define CALIB_MCUID0767_DEF                         (2289U)          /* Digital meter vehicle speed for Usa/Canada(220 km/h)         */
#define CALIB_MCUID0768_DEF                         (2496U)          /* Digital meter vehicle speed for Usa/Canada(240 km/h)         */
#define CALIB_MCUID0769_DEF                         (2704U)          /* Digital meter vehicle speed for Usa/Canada(260 km/h)         */
#define CALIB_MCUID0770_DEF                         (2911U)          /* Digital meter vehicle speed for Usa/Canada(280 km/h)         */
#define CALIB_MCUID0771_DEF                         (3118U)          /* Digital meter vehicle speed for Usa/Canada(300 km/h)         */
#define CALIB_MCUID0772_DEF                         (3325U)          /* Digital meter vehicle speed for Usa/Canada(320 km/h)         */
#define CALIB_MCUID0773_DEF                         (3532U)          /* Digital meter vehicle speed for Usa/Canada(340 km/h)         */
#define CALIB_MCUID0774_DEF                         (3740U)          /* Digital meter vehicle speed for Usa/Canada(360 km/h)         */
#define CALIB_MCUID0775_DEF                         (3947U)          /* Digital meter vehicle speed for Usa/Canada(380 km/h)         */
#define CALIB_MCUID0776_DEF                         (4154U)          /* Digital meter vehicle speed for Usa/Canada(400 km/h)         */
#define CALIB_MCUID0777_DEF                         (217U)           /* Digital meter vehicle speed for UNR/AUS/others(20 km/h)      */
#define CALIB_MCUID0778_DEF                         (428U)           /* Digital meter vehicle speed for UNR/AUS/others(40 km/h)      */
#define CALIB_MCUID0779_DEF                         (628U)           /* Digital meter vehicle speed for UNR/AUS/others(59 km/h)      */
#define CALIB_MCUID0780_DEF                         (843U)           /* Digital meter vehicle speed for UNR/AUS/others(80 km/h)      */
#define CALIB_MCUID0781_DEF                         (1047U)          /* Digital meter vehicle speed for UNR/AUS/others(100 km/h)     */
#define CALIB_MCUID0782_DEF                         (1254U)          /* Digital meter vehicle speed for UNR/AUS/others(120 km/h)     */
#define CALIB_MCUID0783_DEF                         (1460U)          /* Digital meter vehicle speed for UNR/AUS/others(140 km/h)     */
#define CALIB_MCUID0784_DEF                         (1668U)          /* Digital meter vehicle speed for UNR/AUS/others (160 km/h)    */
#define CALIB_MCUID0785_DEF                         (1875U)          /* Digital meter vehicle speed for UNR/AUS/others (180 km/h)    */
#define CALIB_MCUID0786_DEF                         (2082U)          /* Digital meter vehicle speed for UNR/AUS/others (200 km/h)    */
#define CALIB_MCUID0787_DEF                         (2289U)          /* Digital meter vehicle speed for UNR/AUS/others (200 km/h)    */
#define CALIB_MCUID0788_DEF                         (2496U)          /* Digital meter vehicle speed for UNR/AUS/others (240 km/h)    */
#define CALIB_MCUID0789_DEF                         (2704U)          /* Digital meter vehicle speed for UNR/AUS/others (260 km/h)    */
#define CALIB_MCUID0790_DEF                         (2911U)          /* Digital meter vehicle speed for UNR/AUS/others (280 km/h)    */
#define CALIB_MCUID0791_DEF                         (3118U)          /* Digital meter vehicle speed for UNR/AUS/others (300 km/h)    */
#define CALIB_MCUID0792_DEF                         (3325U)          /* Digital meter vehicle speed for UNR/AUS/others (320 km/h)    */
#define CALIB_MCUID0793_DEF                         (3532U)          /* Digital meter vehicle speed for UNR/AUS/others (340 km/h)    */
#define CALIB_MCUID0794_DEF                         (3740U)          /* Digital meter vehicle speed for UNR/AUS/others (360 km/h)    */
#define CALIB_MCUID0795_DEF                         (3947U)          /* Digital meter vehicle speed for UNR/AUS/others (380 km/h)    */
#define CALIB_MCUID0796_DEF                         (4154U)          /* Digital meter vehicle speed for UNR/AUS/others (400 km/h)    */
#define CALIB_MCUID0262_DEF                         (180U)           /* Max Speed km                                                 */
#define CALIB_MCUID0263_DEF                         (160U)           /* Max Speed mph                                                */
#define CALIB_MCUID0292_DEF                         (1000U)          /* CAN:TR2_DUTY(%):light control is max hold                    */
#define CALIB_MCUID0293_DEF                         (1000U)          /* CAN:TR2_DUTY(%):light control level (1)                      */
#define CALIB_MCUID0294_DEF                         (940U)           /* CAN:TR2_DUTY(%):light control level (2)                      */
#define CALIB_MCUID0295_DEF                         (830U)           /* CAN:TR2_DUTY(%):light control level (3)                      */
#define CALIB_MCUID0296_DEF                         (743U)           /* CAN:TR2_DUTY(%):light control level (4)                      */
#define CALIB_MCUID0297_DEF                         (666U)           /* CAN:TR2_DUTY(%):light control level (5)                      */
#define CALIB_MCUID0298_DEF                         (598U)           /* CAN:TR2_DUTY(%):light control level (6)                      */
#define CALIB_MCUID0299_DEF                         (536U)           /* CAN:TR2_DUTY(%):light control level (7)                      */
#define CALIB_MCUID0300_DEF                         (481U)           /* CAN:TR2_DUTY(%):light control level (8)                      */
#define CALIB_MCUID0301_DEF                         (432U)           /* CAN:TR2_DUTY(%):light control level (9)                      */
#define CALIB_MCUID0302_DEF                         (388U)           /* CAN:TR2_DUTY(%):light control level (10)                     */
#define CALIB_MCUID0303_DEF                         (348U)           /* CAN:TR2_DUTY(%):light control level (11)                     */
#define CALIB_MCUID0304_DEF                         (313U)           /* CAN:TR2_DUTY(%):light control level (12)                     */
#define CALIB_MCUID0305_DEF                         (280U)           /* CAN:TR2_DUTY(%):light control level (13)                     */
#define CALIB_MCUID0306_DEF                         (251U)           /* CAN:TR2_DUTY(%):light control level (14)                     */
#define CALIB_MCUID0307_DEF                         (225U)           /* CAN:TR2_DUTY(%):light control level (15)                     */
#define CALIB_MCUID0308_DEF                         (202U)           /* CAN:TR2_DUTY(%):light control level (16)                     */
#define CALIB_MCUID0309_DEF                         (180U)           /* CAN:TR2_DUTY(%):light control level (17)                     */
#define CALIB_MCUID0310_DEF                         (160U)           /* CAN:TR2_DUTY(%):light control level (18)                     */
#define CALIB_MCUID0311_DEF                         (142U)           /* CAN:TR2_DUTY(%):light control level (19)                     */
#define CALIB_MCUID0312_DEF                         (125U)           /* CAN:TR2_DUTY(%):light control level (20)                     */
#define CALIB_MCUID0313_DEF                         (125U)           /* CAN:TR2_DUTY(%): light control is min hold                   */
#define CALIB_MCUID0314_DEF                         (1000U)          /* CAN:IL2_DUTY(%):light control is max hold                    */
#define CALIB_MCUID0315_DEF                         (1000U)          /* CAN:IL2_DUTY(%):light control level (1)                      */
#define CALIB_MCUID0316_DEF                         (940U)           /* CAN:IL2_DUTY(%):light control level (2)                      */
#define CALIB_MCUID0317_DEF                         (830U)           /* CAN:IL2_DUTY(%):light control level (3)                      */
#define CALIB_MCUID0318_DEF                         (743U)           /* CAN:IL2_DUTY(%):light control level (4)                      */
#define CALIB_MCUID0319_DEF                         (666U)           /* CAN:IL2_DUTY(%):light control level (5)                      */
#define CALIB_MCUID0320_DEF                         (598U)           /* CAN:IL2_DUTY(%):light control level (6)                      */
#define CALIB_MCUID0321_DEF                         (536U)           /* CAN:IL2_DUTY(%):light control level (7)                      */
#define CALIB_MCUID0322_DEF                         (481U)           /* CAN:IL2_DUTY(%):light control level (8)                      */
#define CALIB_MCUID0323_DEF                         (432U)           /* CAN:IL2_DUTY(%):light control level (9)                      */
#define CALIB_MCUID0324_DEF                         (388U)           /* CAN:IL2_DUTY(%):light control level (10)                     */
#define CALIB_MCUID0325_DEF                         (348U)           /* CAN:IL2_DUTY(%):light control level (11)                     */
#define CALIB_MCUID0326_DEF                         (313U)           /* CAN:IL2_DUTY(%):light control level (12)                     */
#define CALIB_MCUID0327_DEF                         (280U)           /* CAN:IL2_DUTY(%):light control level (13)                     */
#define CALIB_MCUID0328_DEF                         (251U)           /* CAN:IL2_DUTY(%):light control level (14)                     */
#define CALIB_MCUID0329_DEF                         (225U)           /* CAN:IL2_DUTY(%):light control level (15)                     */
#define CALIB_MCUID0330_DEF                         (202U)           /* CAN:IL2_DUTY(%):light control level (16)                     */
#define CALIB_MCUID0331_DEF                         (180U)           /* CAN:IL2_DUTY(%):light control level (17)                     */
#define CALIB_MCUID0332_DEF                         (160U)           /* CAN:IL2_DUTY(%):light control level (18)                     */
#define CALIB_MCUID0333_DEF                         (142U)           /* CAN:IL2_DUTY(%):light control level (19)                     */
#define CALIB_MCUID0334_DEF                         (125U)           /* CAN:IL2_DUTY(%):light control level (20)                     */
#define CALIB_MCUID0335_DEF                         (125U)           /* CAN:IL2_DUTY(%): light control is min hold                   */
#define CALIB_MCUID0574_DEF                         (2050U)          /* CAL_DEF                                                      */
#define CALIB_MCUID0575_DEF                         (2021U)          /* CAL_MIN                                                      */
#define CALIB_MCUID0738_DEF                         (30U)            /* Timeout Time                                                 */
#define CALIB_MCUID0742_DEF                         (0U)             /* IOUTILLRun                                                   */
#define CALIB_MCUID0743_DEF                         (0U)             /* IOUTILLRunmax                                                */
#define CALIB_MCUID0923_DEF                         (0U)             /* Special destination for judgement Country code 1             */
#define CALIB_MCUID0924_DEF                         (0U)             /* Special destination for judgement Country code 2             */
#define CALIB_MCUID0925_DEF                         (0U)             /* Special destination for judgement Country code 3             */
#define CALIB_MCUID0926_DEF                         (0U)             /* Special destination for judgement Country code 4             */
#define CALIB_MCUID0927_DEF                         (0U)             /* Special destination for judgement Country code 5             */
#define CALIB_MCUID0928_DEF                         (0U)             /* Special destination for judgement Country code 6             */
#define CALIB_MCUID0929_DEF                         (0U)             /* Special destination for judgement Country code 7             */
#define CALIB_MCUID0930_DEF                         (0U)             /* Special destination for judgement Country code 8             */
#define CALIB_MCUID0931_DEF                         (0U)             /* Special destination for judgement Country code 9             */
#define CALIB_MCUID0932_DEF                         (0U)             /* Special destination for judgement Country code 10            */
#define CALIB_MCUID_RSV_2B_0260_DEF                 (0U)             /* Reserve_2B-0260                                              */
#define CALIB_MCUID_RSV_2B_0261_DEF                 (0U)             /* Reserve_2B-0261                                              */
#define CALIB_MCUID_RSV_2B_0262_DEF                 (0U)             /* Reserve_2B-0262                                              */
#define CALIB_MCUID_RSV_2B_0263_DEF                 (0U)             /* Reserve_2B-0263                                              */
#define CALIB_MCUID_RSV_2B_0264_DEF                 (0U)             /* Reserve_2B-0264                                              */
#define CALIB_MCUID_RSV_2B_0265_DEF                 (0U)             /* Reserve_2B-0265                                              */
#define CALIB_MCUID_RSV_2B_0266_DEF                 (0U)             /* Reserve_2B-0266                                              */
#define CALIB_MCUID_RSV_2B_0267_DEF                 (0U)             /* Reserve_2B-0267                                              */
#define CALIB_MCUID_RSV_2B_0268_DEF                 (0U)             /* Reserve_2B-0268                                              */
#define CALIB_MCUID_RSV_2B_0269_DEF                 (0U)             /* Reserve_2B-0269                                              */
#define CALIB_MCUID_RSV_2B_0270_DEF                 (0U)             /* Reserve_2B-0270                                              */
#define CALIB_MCUID_RSV_2B_0271_DEF                 (0U)             /* Reserve_2B-0271                                              */
#define CALIB_MCUID_RSV_2B_0272_DEF                 (0U)             /* Reserve_2B-0272                                              */
#define CALIB_MCUID_RSV_2B_0273_DEF                 (0U)             /* Reserve_2B-0273                                              */
#define CALIB_MCUID_RSV_2B_0274_DEF                 (0U)             /* Reserve_2B-0274                                              */
#define CALIB_MCUID_RSV_2B_0275_DEF                 (0U)             /* Reserve_2B-0275                                              */
#define CALIB_MCUID_RSV_2B_0276_DEF                 (0U)             /* Reserve_2B-0276                                              */
#define CALIB_MCUID_RSV_2B_0277_DEF                 (0U)             /* Reserve_2B-0277                                              */
#define CALIB_MCUID_RSV_2B_0278_DEF                 (0U)             /* Reserve_2B-0278                                              */
#define CALIB_MCUID_RSV_2B_0279_DEF                 (0U)             /* Reserve_2B-0279                                              */
#define CALIB_MCUID_RSV_2B_0280_DEF                 (0U)             /* Reserve_2B-0280                                              */
#define CALIB_MCUID_RSV_2B_0281_DEF                 (0U)             /* Reserve_2B-0281                                              */
#define CALIB_MCUID_RSV_2B_0282_DEF                 (0U)             /* Reserve_2B-0282                                              */
#define CALIB_MCUID_RSV_2B_0283_DEF                 (0U)             /* Reserve_2B-0283                                              */
#define CALIB_MCUID_RSV_2B_0284_DEF                 (0U)             /* Reserve_2B-0284                                              */
#define CALIB_MCUID_RSV_2B_0285_DEF                 (0U)             /* Reserve_2B-0285                                              */
#define CALIB_MCUID_RSV_2B_0286_DEF                 (0U)             /* Reserve_2B-0286                                              */
#define CALIB_MCUID_RSV_2B_0287_DEF                 (0U)             /* Reserve_2B-0287                                              */
#define CALIB_MCUID_RSV_2B_0288_DEF                 (0U)             /* Reserve_2B-0288                                              */
#define CALIB_MCUID_RSV_2B_0289_DEF                 (0U)             /* Reserve_2B-0289                                              */
#define CALIB_MCUID_RSV_2B_0290_DEF                 (0U)             /* Reserve_2B-0290                                              */
#define CALIB_MCUID_RSV_2B_0291_DEF                 (0U)             /* Reserve_2B-0291                                              */
#define CALIB_MCUID_RSV_2B_0292_DEF                 (0U)             /* Reserve_2B-0292                                              */
#define CALIB_MCUID_RSV_2B_0293_DEF                 (0U)             /* Reserve_2B-0293                                              */
#define CALIB_MCUID_RSV_2B_0294_DEF                 (0U)             /* Reserve_2B-0294                                              */
#define CALIB_MCUID_RSV_2B_0295_DEF                 (0U)             /* Reserve_2B-0295                                              */
#define CALIB_MCUID_RSV_2B_0296_DEF                 (0U)             /* Reserve_2B-0296                                              */
#define CALIB_MCUID_RSV_2B_0297_DEF                 (0U)             /* Reserve_2B-0297                                              */
#define CALIB_MCUID_RSV_2B_0298_DEF                 (0U)             /* Reserve_2B-0298                                              */
#define CALIB_MCUID_RSV_2B_0299_DEF                 (0U)             /* Reserve_2B-0299                                              */
#define CALIB_MCUID_RSV_2B_0300_DEF                 (0U)             /* Reserve_2B-0300                                              */
#define CALIB_MCUID_RSV_2B_0301_DEF                 (0U)             /* Reserve_2B-0301                                              */
#define CALIB_MCUID_RSV_2B_0302_DEF                 (0U)             /* Reserve_2B-0302                                              */
#define CALIB_MCUID_RSV_2B_0303_DEF                 (0U)             /* Reserve_2B-0303                                              */
#define CALIB_MCUID_RSV_2B_0304_DEF                 (0U)             /* Reserve_2B-0304                                              */
#define CALIB_MCUID_RSV_2B_0305_DEF                 (0U)             /* Reserve_2B-0305                                              */
#define CALIB_MCUID_RSV_2B_0306_DEF                 (0U)             /* Reserve_2B-0306                                              */
#define CALIB_MCUID_RSV_2B_0307_DEF                 (0U)             /* Reserve_2B-0307                                              */
#define CALIB_MCUID_RSV_2B_0308_DEF                 (0U)             /* Reserve_2B-0308                                              */
#define CALIB_MCUID_RSV_2B_0309_DEF                 (0U)             /* Reserve_2B-0309                                              */
#define CALIB_MCUID_RSV_2B_0310_DEF                 (0U)             /* Reserve_2B-0310                                              */
#define CALIB_MCUID_RSV_2B_0311_DEF                 (0U)             /* Reserve_2B-0311                                              */
#define CALIB_MCUID_RSV_2B_0312_DEF                 (0U)             /* Reserve_2B-0312                                              */
#define CALIB_MCUID_RSV_2B_0313_DEF                 (0U)             /* Reserve_2B-0313                                              */
#define CALIB_MCUID_RSV_2B_0314_DEF                 (0U)             /* Reserve_2B-0314                                              */
#define CALIB_MCUID_RSV_2B_0315_DEF                 (0U)             /* Reserve_2B-0315                                              */
#define CALIB_MCUID_RSV_2B_0316_DEF                 (0U)             /* Reserve_2B-0316                                              */
#define CALIB_MCUID_RSV_2B_0317_DEF                 (0U)             /* Reserve_2B-0317                                              */
#define CALIB_MCUID_RSV_2B_0318_DEF                 (0U)             /* Reserve_2B-0318                                              */
#define CALIB_MCUID_RSV_2B_0319_DEF                 (0U)             /* Reserve_2B-0319                                              */
#define CALIB_MCUID_RSV_2B_0320_DEF                 (0U)             /* Reserve_2B-0320                                              */
#define CALIB_MCUID_RSV_2B_0321_DEF                 (0U)             /* Reserve_2B-0321                                              */
#define CALIB_MCUID_RSV_2B_0322_DEF                 (0U)             /* Reserve_2B-0322                                              */
#define CALIB_MCUID_RSV_2B_0323_DEF                 (0U)             /* Reserve_2B-0323                                              */
#define CALIB_MCUID_RSV_2B_0324_DEF                 (0U)             /* Reserve_2B-0324                                              */
#define CALIB_MCUID_RSV_2B_0325_DEF                 (0U)             /* Reserve_2B-0325                                              */
#define CALIB_MCUID_RSV_2B_0326_DEF                 (0U)             /* Reserve_2B-0326                                              */
#define CALIB_MCUID_RSV_2B_0327_DEF                 (0U)             /* Reserve_2B-0327                                              */
#define CALIB_MCUID_RSV_2B_0328_DEF                 (0U)             /* Reserve_2B-0328                                              */
#define CALIB_MCUID_RSV_2B_0329_DEF                 (0U)             /* Reserve_2B-0329                                              */
#define CALIB_MCUID_RSV_2B_0330_DEF                 (0U)             /* Reserve_2B-0330                                              */
#define CALIB_MCUID_RSV_2B_0331_DEF                 (0U)             /* Reserve_2B-0331                                              */
#define CALIB_MCUID_RSV_2B_0332_DEF                 (0U)             /* Reserve_2B-0332                                              */
#define CALIB_MCUID_RSV_2B_0333_DEF                 (0U)             /* Reserve_2B-0333                                              */
#define CALIB_MCUID_RSV_2B_0334_DEF                 (0U)             /* Reserve_2B-0334                                              */
#define CALIB_MCUID_RSV_2B_0335_DEF                 (0U)             /* Reserve_2B-0335                                              */
#define CALIB_MCUID_RSV_2B_0336_DEF                 (0U)             /* Reserve_2B-0336                                              */
#define CALIB_MCUID_RSV_2B_0337_DEF                 (0U)             /* Reserve_2B-0337                                              */
#define CALIB_MCUID_RSV_2B_0338_DEF                 (0U)             /* Reserve_2B-0338                                              */
#define CALIB_MCUID_RSV_2B_0339_DEF                 (0U)             /* Reserve_2B-0339                                              */
#define CALIB_MCUID_RSV_2B_0340_DEF                 (0U)             /* Reserve_2B-0340                                              */
#define CALIB_MCUID_RSV_2B_0341_DEF                 (0U)             /* Reserve_2B-0341                                              */
#define CALIB_MCUID_RSV_2B_0342_DEF                 (0U)             /* Reserve_2B-0342                                              */
#define CALIB_MCUID_RSV_2B_0343_DEF                 (0U)             /* Reserve_2B-0343                                              */
#define CALIB_MCUID_RSV_2B_0344_DEF                 (0U)             /* Reserve_2B-0344                                              */
#define CALIB_MCUID_RSV_2B_0345_DEF                 (0U)             /* Reserve_2B-0345                                              */
#define CALIB_MCUID_RSV_2B_0346_DEF                 (0U)             /* Reserve_2B-0346                                              */
#define CALIB_MCUID_RSV_2B_0347_DEF                 (0U)             /* Reserve_2B-0347                                              */
#define CALIB_MCUID_RSV_2B_0348_DEF                 (0U)             /* Reserve_2B-0348                                              */
#define CALIB_MCUID_RSV_2B_0349_DEF                 (0U)             /* Reserve_2B-0349                                              */
#define CALIB_MCUID_RSV_2B_0350_DEF                 (0U)             /* Reserve_2B-0350                                              */
#define CALIB_MCUID_RSV_2B_0351_DEF                 (0U)             /* Reserve_2B-0351                                              */
#define CALIB_MCUID_RSV_2B_0352_DEF                 (0U)             /* Reserve_2B-0352                                              */
#define CALIB_MCUID_RSV_2B_0353_DEF                 (0U)             /* Reserve_2B-0353                                              */
#define CALIB_MCUID_RSV_2B_0354_DEF                 (0U)             /* Reserve_2B-0354                                              */
#define CALIB_MCUID_RSV_2B_0355_DEF                 (0U)             /* Reserve_2B-0355                                              */
#define CALIB_MCUID_RSV_2B_0356_DEF                 (0U)             /* Reserve_2B-0356                                              */
#define CALIB_MCUID_RSV_2B_0357_DEF                 (0U)             /* Reserve_2B-0357                                              */
#define CALIB_MCUID_RSV_2B_0358_DEF                 (0U)             /* Reserve_2B-0358                                              */
#define CALIB_MCUID_RSV_2B_0359_DEF                 (0U)             /* Reserve_2B-0359                                              */
#define CALIB_MCUID_RSV_2B_0360_DEF                 (0U)             /* Reserve_2B-0360                                              */
#define CALIB_MCUID_RSV_2B_0361_DEF                 (0U)             /* Reserve_2B-0361                                              */
#define CALIB_MCUID_RSV_2B_0362_DEF                 (0U)             /* Reserve_2B-0362                                              */
#define CALIB_MCUID_RSV_2B_0363_DEF                 (0U)             /* Reserve_2B-0363                                              */
#define CALIB_MCUID_RSV_2B_0364_DEF                 (0U)             /* Reserve_2B-0364                                              */
#define CALIB_MCUID_RSV_2B_0365_DEF                 (0U)             /* Reserve_2B-0365                                              */
#define CALIB_MCUID_RSV_2B_0366_DEF                 (0U)             /* Reserve_2B-0366                                              */
#define CALIB_MCUID_RSV_2B_0367_DEF                 (0U)             /* Reserve_2B-0367                                              */
#define CALIB_MCUID_RSV_2B_0368_DEF                 (0U)             /* Reserve_2B-0368                                              */
#define CALIB_MCUID_RSV_2B_0369_DEF                 (0U)             /* Reserve_2B-0369                                              */
#define CALIB_MCUID_RSV_2B_0370_DEF                 (0U)             /* Reserve_2B-0370                                              */
#define CALIB_MCUID_RSV_2B_0371_DEF                 (0U)             /* Reserve_2B-0371                                              */
#define CALIB_MCUID_RSV_2B_0372_DEF                 (0U)             /* Reserve_2B-0372                                              */
#define CALIB_MCUID_RSV_2B_0373_DEF                 (0U)             /* Reserve_2B-0373                                              */
#define CALIB_MCUID_RSV_2B_0374_DEF                 (0U)             /* Reserve_2B-0374                                              */
#define CALIB_MCUID_RSV_2B_0375_DEF                 (0U)             /* Reserve_2B-0375                                              */
#define CALIB_MCUID_RSV_2B_0376_DEF                 (0U)             /* Reserve_2B-0376                                              */
#define CALIB_MCUID_RSV_2B_0377_DEF                 (0U)             /* Reserve_2B-0377                                              */
#define CALIB_MCUID_RSV_2B_0378_DEF                 (0U)             /* Reserve_2B-0378                                              */
#define CALIB_MCUID_RSV_2B_0379_DEF                 (0U)             /* Reserve_2B-0379                                              */
#define CALIB_MCUID_RSV_2B_0380_DEF                 (0U)             /* Reserve_2B-0380                                              */
#define CALIB_MCUID_RSV_2B_0381_DEF                 (0U)             /* Reserve_2B-0381                                              */
#define CALIB_MCUID_RSV_2B_0382_DEF                 (0U)             /* Reserve_2B-0382                                              */
#define CALIB_MCUID_RSV_2B_0383_DEF                 (0U)             /* Reserve_2B-0383                                              */
#define CALIB_MCUID_RSV_2B_0384_DEF                 (0U)             /* Reserve_2B-0384                                              */
#define CALIB_MCUID_RSV_2B_0385_DEF                 (0U)             /* Reserve_2B-0385                                              */
#define CALIB_MCUID_RSV_2B_0386_DEF                 (0U)             /* Reserve_2B-0386                                              */
#define CALIB_MCUID_RSV_2B_0387_DEF                 (0U)             /* Reserve_2B-0387                                              */
#define CALIB_MCUID_RSV_2B_0388_DEF                 (0U)             /* Reserve_2B-0388                                              */
#define CALIB_MCUID_RSV_2B_0389_DEF                 (0U)             /* Reserve_2B-0389                                              */
#define CALIB_MCUID_RSV_2B_0390_DEF                 (0U)             /* Reserve_2B-0390                                              */
#define CALIB_MCUID_RSV_2B_0391_DEF                 (0U)             /* Reserve_2B-0391                                              */
#define CALIB_MCUID_RSV_2B_0392_DEF                 (0U)             /* Reserve_2B-0392                                              */
#define CALIB_MCUID_RSV_2B_0393_DEF                 (0U)             /* Reserve_2B-0393                                              */
#define CALIB_MCUID_RSV_2B_0394_DEF                 (0U)             /* Reserve_2B-0394                                              */
#define CALIB_MCUID_RSV_2B_0395_DEF                 (0U)             /* Reserve_2B-0395                                              */
#define CALIB_MCUID_RSV_2B_0396_DEF                 (0U)             /* Reserve_2B-0396                                              */
#define CALIB_MCUID_RSV_2B_0397_DEF                 (0U)             /* Reserve_2B-0397                                              */
#define CALIB_MCUID_RSV_2B_0398_DEF                 (0U)             /* Reserve_2B-0398                                              */
#define CALIB_MCUID_RSV_2B_0399_DEF                 (0U)             /* Reserve_2B-0399                                              */
#define CALIB_MCUID_RSV_2B_0400_DEF                 (0U)             /* Reserve_2B-0400                                              */
#define CALIB_MCUID_RSV_2B_0401_DEF                 (0U)             /* Reserve_2B-0401                                              */
#define CALIB_MCUID_RSV_2B_0402_DEF                 (0U)             /* Reserve_2B-0402                                              */
#define CALIB_MCUID_RSV_2B_0403_DEF                 (0U)             /* Reserve_2B-0403                                              */
#define CALIB_MCUID_RSV_2B_0404_DEF                 (0U)             /* Reserve_2B-0404                                              */
#define CALIB_MCUID_RSV_2B_0405_DEF                 (0U)             /* Reserve_2B-0405                                              */
#define CALIB_MCUID_RSV_2B_0406_DEF                 (0U)             /* Reserve_2B-0406                                              */
#define CALIB_MCUID_RSV_2B_0407_DEF                 (0U)             /* Reserve_2B-0407                                              */
#define CALIB_MCUID_RSV_2B_0408_DEF                 (0U)             /* Reserve_2B-0408                                              */
#define CALIB_MCUID_RSV_2B_0409_DEF                 (0U)             /* Reserve_2B-0409                                              */
#define CALIB_MCUID_RSV_2B_0410_DEF                 (0U)             /* Reserve_2B-0410                                              */
#define CALIB_MCUID_RSV_2B_0411_DEF                 (0U)             /* Reserve_2B-0411                                              */
#define CALIB_MCUID_RSV_2B_0412_DEF                 (0U)             /* Reserve_2B-0412                                              */
#define CALIB_MCUID_RSV_2B_0413_DEF                 (0U)             /* Reserve_2B-0413                                              */
#define CALIB_MCUID_RSV_2B_0414_DEF                 (0U)             /* Reserve_2B-0414                                              */
#define CALIB_MCUID_RSV_2B_0415_DEF                 (0U)             /* Reserve_2B-0415                                              */
#define CALIB_MCUID_RSV_2B_0416_DEF                 (0U)             /* Reserve_2B-0416                                              */
#define CALIB_MCUID_RSV_2B_0417_DEF                 (0U)             /* Reserve_2B-0417                                              */
#define CALIB_MCUID_RSV_2B_0418_DEF                 (0U)             /* Reserve_2B-0418                                              */
#define CALIB_MCUID_RSV_2B_0419_DEF                 (0U)             /* Reserve_2B-0419                                              */
#define CALIB_MCUID_RSV_2B_0420_DEF                 (0U)             /* Reserve_2B-0420                                              */
#define CALIB_MCUID_RSV_2B_0421_DEF                 (0U)             /* Reserve_2B-0421                                              */
#define CALIB_MCUID_RSV_2B_0422_DEF                 (0U)             /* Reserve_2B-0422                                              */
#define CALIB_MCUID_RSV_2B_0423_DEF                 (0U)             /* Reserve_2B-0423                                              */
#define CALIB_MCUID_RSV_2B_0424_DEF                 (0U)             /* Reserve_2B-0424                                              */
#define CALIB_MCUID_RSV_2B_0425_DEF                 (0U)             /* Reserve_2B-0425                                              */
#define CALIB_MCUID_RSV_2B_0426_DEF                 (0U)             /* Reserve_2B-0426                                              */
#define CALIB_MCUID_RSV_2B_0427_DEF                 (0U)             /* Reserve_2B-0427                                              */
#define CALIB_MCUID_RSV_2B_0428_DEF                 (0U)             /* Reserve_2B-0428                                              */
#define CALIB_MCUID_RSV_2B_0429_DEF                 (0U)             /* Reserve_2B-0429                                              */
#define CALIB_MCUID_RSV_2B_0430_DEF                 (0U)             /* Reserve_2B-0430                                              */
#define CALIB_MCUID_RSV_2B_0431_DEF                 (0U)             /* Reserve_2B-0431                                              */
#define CALIB_MCUID_RSV_2B_0432_DEF                 (0U)             /* Reserve_2B-0432                                              */
#define CALIB_MCUID_RSV_2B_0433_DEF                 (0U)             /* Reserve_2B-0433                                              */
#define CALIB_MCUID_RSV_2B_0434_DEF                 (0U)             /* Reserve_2B-0434                                              */
#define CALIB_MCUID_RSV_2B_0435_DEF                 (0U)             /* Reserve_2B-0435                                              */
#define CALIB_MCUID_RSV_2B_0436_DEF                 (0U)             /* Reserve_2B-0436                                              */
#define CALIB_MCUID_RSV_2B_0437_DEF                 (0U)             /* Reserve_2B-0437                                              */
#define CALIB_MCUID_RSV_2B_0438_DEF                 (0U)             /* Reserve_2B-0438                                              */
#define CALIB_MCUID_RSV_2B_0439_DEF                 (0U)             /* Reserve_2B-0439                                              */
#define CALIB_MCUID_RSV_2B_0440_DEF                 (0U)             /* Reserve_2B-0440                                              */
#define CALIB_MCUID_RSV_2B_0441_DEF                 (0U)             /* Reserve_2B-0441                                              */
#define CALIB_MCUID_RSV_2B_0442_DEF                 (0U)             /* Reserve_2B-0442                                              */
#define CALIB_MCUID_RSV_2B_0443_DEF                 (0U)             /* Reserve_2B-0443                                              */
#define CALIB_MCUID_RSV_2B_0444_DEF                 (0U)             /* Reserve_2B-0444                                              */
#define CALIB_MCUID_RSV_2B_0445_DEF                 (0U)             /* Reserve_2B-0445                                              */
#define CALIB_MCUID_RSV_2B_0446_DEF                 (0U)             /* Reserve_2B-0446                                              */
#define CALIB_MCUID_RSV_2B_0447_DEF                 (0U)             /* Reserve_2B-0447                                              */
#define CALIB_MCUID_RSV_2B_0448_DEF                 (0U)             /* Reserve_2B-0448                                              */
#define CALIB_MCUID_RSV_2B_0449_DEF                 (0U)             /* Reserve_2B-0449                                              */
#define CALIB_MCUID_RSV_2B_0450_DEF                 (0U)             /* Reserve_2B-0450                                              */
#define CALIB_MCUID_RSV_2B_0451_DEF                 (0U)             /* Reserve_2B-0451                                              */
#define CALIB_MCUID_RSV_2B_0452_DEF                 (0U)             /* Reserve_2B-0452                                              */
#define CALIB_MCUID_RSV_2B_0453_DEF                 (0U)             /* Reserve_2B-0453                                              */
#define CALIB_MCUID_RSV_2B_0454_DEF                 (0U)             /* Reserve_2B-0454                                              */
#define CALIB_MCUID_RSV_2B_0455_DEF                 (0U)             /* Reserve_2B-0455                                              */
#define CALIB_MCUID_RSV_2B_0456_DEF                 (0U)             /* Reserve_2B-0456                                              */
#define CALIB_MCUID_RSV_2B_0457_DEF                 (0U)             /* Reserve_2B-0457                                              */
#define CALIB_MCUID_RSV_2B_0458_DEF                 (0U)             /* Reserve_2B-0458                                              */
#define CALIB_MCUID_RSV_2B_0459_DEF                 (0U)             /* Reserve_2B-0459                                              */
#define CALIB_MCUID_RSV_2B_0460_DEF                 (0U)             /* Reserve_2B-0460                                              */
#define CALIB_MCUID_RSV_2B_0461_DEF                 (0U)             /* Reserve_2B-0461                                              */
#define CALIB_MCUID_RSV_2B_0462_DEF                 (0U)             /* Reserve_2B-0462                                              */
#define CALIB_MCUID_RSV_2B_0463_DEF                 (0U)             /* Reserve_2B-0463                                              */
#define CALIB_MCUID_RSV_2B_0464_DEF                 (0U)             /* Reserve_2B-0464                                              */
#define CALIB_MCUID_RSV_2B_0465_DEF                 (0U)             /* Reserve_2B-0465                                              */
#define CALIB_MCUID_RSV_2B_0466_DEF                 (0U)             /* Reserve_2B-0466                                              */
#define CALIB_MCUID_RSV_2B_0467_DEF                 (0U)             /* Reserve_2B-0467                                              */
#define CALIB_MCUID_RSV_2B_0468_DEF                 (0U)             /* Reserve_2B-0468                                              */
#define CALIB_MCUID_RSV_2B_0469_DEF                 (0U)             /* Reserve_2B-0469                                              */
#define CALIB_MCUID_RSV_2B_0470_DEF                 (0U)             /* Reserve_2B-0470                                              */
#define CALIB_MCUID_RSV_2B_0471_DEF                 (0U)             /* Reserve_2B-0471                                              */
#define CALIB_MCUID_RSV_2B_0472_DEF                 (0U)             /* Reserve_2B-0472                                              */
#define CALIB_MCUID_RSV_2B_0473_DEF                 (0U)             /* Reserve_2B-0473                                              */
#define CALIB_MCUID_RSV_2B_0474_DEF                 (0U)             /* Reserve_2B-0474                                              */
#define CALIB_MCUID_RSV_2B_0475_DEF                 (0U)             /* Reserve_2B-0475                                              */
#define CALIB_MCUID_RSV_2B_0476_DEF                 (0U)             /* Reserve_2B-0476                                              */
#define CALIB_MCUID_RSV_2B_0477_DEF                 (0U)             /* Reserve_2B-0477                                              */
#define CALIB_MCUID_RSV_2B_0478_DEF                 (0U)             /* Reserve_2B-0478                                              */
#define CALIB_MCUID_RSV_2B_0479_DEF                 (0U)             /* Reserve_2B-0479                                              */
#define CALIB_MCUID_RSV_2B_0480_DEF                 (0U)             /* Reserve_2B-0480                                              */
#define CALIB_MCUID_RSV_2B_0481_DEF                 (0U)             /* Reserve_2B-0481                                              */
#define CALIB_MCUID_RSV_2B_0482_DEF                 (0U)             /* Reserve_2B-0482                                              */
#define CALIB_MCUID_RSV_2B_0483_DEF                 (0U)             /* Reserve_2B-0483                                              */
#define CALIB_MCUID_RSV_2B_0484_DEF                 (0U)             /* Reserve_2B-0484                                              */
#define CALIB_MCUID_RSV_2B_0485_DEF                 (0U)             /* Reserve_2B-0485                                              */
#define CALIB_MCUID_RSV_2B_0486_DEF                 (0U)             /* Reserve_2B-0486                                              */
#define CALIB_MCUID_RSV_2B_0487_DEF                 (0U)             /* Reserve_2B-0487                                              */
#define CALIB_MCUID_RSV_2B_0488_DEF                 (0U)             /* Reserve_2B-0488                                              */
#define CALIB_MCUID_RSV_2B_0489_DEF                 (0U)             /* Reserve_2B-0489                                              */
#define CALIB_MCUID_RSV_2B_0490_DEF                 (0U)             /* Reserve_2B-0490                                              */
#define CALIB_MCUID_RSV_2B_0491_DEF                 (0U)             /* Reserve_2B-0491                                              */
#define CALIB_MCUID_RSV_2B_0492_DEF                 (0U)             /* Reserve_2B-0492                                              */
#define CALIB_MCUID_RSV_2B_0493_DEF                 (0U)             /* Reserve_2B-0493                                              */
#define CALIB_MCUID_RSV_2B_0494_DEF                 (0U)             /* Reserve_2B-0494                                              */
#define CALIB_MCUID_RSV_2B_0495_DEF                 (0U)             /* Reserve_2B-0495                                              */
#define CALIB_MCUID_RSV_2B_0496_DEF                 (0U)             /* Reserve_2B-0496                                              */
#define CALIB_MCUID_RSV_2B_0497_DEF                 (0U)             /* Reserve_2B-0497                                              */
#define CALIB_MCUID_RSV_2B_0498_DEF                 (0U)             /* Reserve_2B-0498                                              */
#define CALIB_MCUID_RSV_2B_0499_DEF                 (0U)             /* Reserve_2B-0499                                              */
#define CALIB_MCUID_RSV_2B_0500_DEF                 (0U)             /* Reserve_2B-0500                                              */
#define CALIB_MCUID_RSV_2B_0501_DEF                 (0U)             /* Reserve_2B-0501                                              */
#define CALIB_MCUID_RSV_2B_0502_DEF                 (0U)             /* Reserve_2B-0502                                              */
#define CALIB_MCUID_RSV_2B_0503_DEF                 (0U)             /* Reserve_2B-0503                                              */
#define CALIB_MCUID_RSV_2B_0504_DEF                 (0U)             /* Reserve_2B-0504                                              */
#define CALIB_MCUID_RSV_2B_0505_DEF                 (0U)             /* Reserve_2B-0505                                              */
#define CALIB_MCUID_RSV_2B_0506_DEF                 (0U)             /* Reserve_2B-0506                                              */
#define CALIB_MCUID_RSV_2B_0507_DEF                 (0U)             /* Reserve_2B-0507                                              */
#define CALIB_MCUID_RSV_2B_0508_DEF                 (0U)             /* Reserve_2B-0508                                              */
#define CALIB_MCUID_RSV_2B_0509_DEF                 (0U)             /* Reserve_2B-0509                                              */
#define CALIB_MCUID_RSV_2B_0510_DEF                 (0U)             /* Reserve_2B-0510                                              */
#define CALIB_MCUID_RSV_2B_0511_DEF                 (0U)             /* Reserve_2B-0511                                              */
#define CALIB_MCUID_RSV_2B_0512_DEF                 (0U)             /* Reserve_2B-0512                                              */
#define CALIB_MCUID_RSV_2B_0513_DEF                 (0U)             /* Reserve_2B-0513                                              */
#define CALIB_MCUID_RSV_2B_0514_DEF                 (0U)             /* Reserve_2B-0514                                              */
#define CALIB_MCUID_RSV_2B_0515_DEF                 (0U)             /* Reserve_2B-0515                                              */
#define CALIB_MCUID_RSV_2B_0516_DEF                 (0U)             /* Reserve_2B-0516                                              */
#define CALIB_MCUID_RSV_2B_0517_DEF                 (0U)             /* Reserve_2B-0517                                              */
#define CALIB_MCUID_RSV_2B_0518_DEF                 (0U)             /* Reserve_2B-0518                                              */
#define CALIB_MCUID_RSV_2B_0519_DEF                 (0U)             /* Reserve_2B-0519                                              */
#define CALIB_MCUID_RSV_2B_0520_DEF                 (0U)             /* Reserve_2B-0520                                              */
#define CALIB_MCUID_RSV_2B_0521_DEF                 (0U)             /* Reserve_2B-0521                                              */
#define CALIB_MCUID_RSV_2B_0522_DEF                 (0U)             /* Reserve_2B-0522                                              */
#define CALIB_MCUID_RSV_2B_0523_DEF                 (0U)             /* Reserve_2B-0523                                              */
#define CALIB_MCUID_RSV_2B_0524_DEF                 (0U)             /* Reserve_2B-0524                                              */
#define CALIB_MCUID_RSV_2B_0525_DEF                 (0U)             /* Reserve_2B-0525                                              */
#define CALIB_MCUID_RSV_2B_0526_DEF                 (0U)             /* Reserve_2B-0526                                              */
#define CALIB_MCUID_RSV_2B_0527_DEF                 (0U)             /* Reserve_2B-0527                                              */
#define CALIB_MCUID_RSV_2B_0528_DEF                 (0U)             /* Reserve_2B-0528                                              */
#define CALIB_MCUID_RSV_2B_0529_DEF                 (0U)             /* Reserve_2B-0529                                              */
#define CALIB_MCUID_RSV_2B_0530_DEF                 (0U)             /* Reserve_2B-0530                                              */
#define CALIB_MCUID_RSV_2B_0531_DEF                 (0U)             /* Reserve_2B-0531                                              */
#define CALIB_MCUID_RSV_2B_0532_DEF                 (0U)             /* Reserve_2B-0532                                              */
#define CALIB_MCUID_RSV_2B_0533_DEF                 (0U)             /* Reserve_2B-0533                                              */
#define CALIB_MCUID_RSV_2B_0534_DEF                 (0U)             /* Reserve_2B-0534                                              */
#define CALIB_MCUID_RSV_2B_0535_DEF                 (0U)             /* Reserve_2B-0535                                              */
#define CALIB_MCUID_RSV_2B_0536_DEF                 (0U)             /* Reserve_2B-0536                                              */
#define CALIB_MCUID_RSV_2B_0537_DEF                 (0U)             /* Reserve_2B-0537                                              */
#define CALIB_MCUID_RSV_2B_0538_DEF                 (0U)             /* Reserve_2B-0538                                              */
#define CALIB_MCUID_RSV_2B_0539_DEF                 (0U)             /* Reserve_2B-0539                                              */
#define CALIB_MCUID_RSV_2B_0540_DEF                 (0U)             /* Reserve_2B-0540                                              */
#define CALIB_MCUID_RSV_2B_0541_DEF                 (0U)             /* Reserve_2B-0541                                              */
#define CALIB_MCUID_RSV_2B_0542_DEF                 (0U)             /* Reserve_2B-0542                                              */
#define CALIB_MCUID_RSV_2B_0543_DEF                 (0U)             /* Reserve_2B-0543                                              */
#define CALIB_MCUID_RSV_2B_0544_DEF                 (0U)             /* Reserve_2B-0544                                              */
#define CALIB_MCUID_RSV_2B_0545_DEF                 (0U)             /* Reserve_2B-0545                                              */
#define CALIB_MCUID_RSV_2B_0546_DEF                 (0U)             /* Reserve_2B-0546                                              */
#define CALIB_MCUID_RSV_2B_0547_DEF                 (0U)             /* Reserve_2B-0547                                              */
#define CALIB_MCUID_RSV_2B_0548_DEF                 (0U)             /* Reserve_2B-0548                                              */
#define CALIB_MCUID_RSV_2B_0549_DEF                 (0U)             /* Reserve_2B-0549                                              */
#define CALIB_MCUID_RSV_2B_0550_DEF                 (0U)             /* Reserve_2B-0550                                              */
#define CALIB_MCUID_RSV_2B_0551_DEF                 (0U)             /* Reserve_2B-0551                                              */
#define CALIB_MCUID_RSV_2B_0552_DEF                 (0U)             /* Reserve_2B-0552                                              */
#define CALIB_MCUID_RSV_2B_0553_DEF                 (0U)             /* Reserve_2B-0553                                              */
#define CALIB_MCUID_RSV_2B_0554_DEF                 (0U)             /* Reserve_2B-0554                                              */
#define CALIB_MCUID_RSV_2B_0555_DEF                 (0U)             /* Reserve_2B-0555                                              */
#define CALIB_MCUID_RSV_2B_0556_DEF                 (0U)             /* Reserve_2B-0556                                              */
#define CALIB_MCUID_RSV_2B_0557_DEF                 (0U)             /* Reserve_2B-0557                                              */
#define CALIB_MCUID_RSV_2B_0558_DEF                 (0U)             /* Reserve_2B-0558                                              */
#define CALIB_MCUID_RSV_2B_0559_DEF                 (0U)             /* Reserve_2B-0559                                              */
#define CALIB_MCUID_RSV_2B_0560_DEF                 (0U)             /* Reserve_2B-0560                                              */
#define CALIB_MCUID_RSV_2B_0561_DEF                 (0U)             /* Reserve_2B-0561                                              */
#define CALIB_MCUID_RSV_2B_0562_DEF                 (0U)             /* Reserve_2B-0562                                              */
#define CALIB_MCUID_RSV_2B_0563_DEF                 (0U)             /* Reserve_2B-0563                                              */
#define CALIB_MCUID_RSV_2B_0564_DEF                 (0U)             /* Reserve_2B-0564                                              */
#define CALIB_MCUID_RSV_2B_0565_DEF                 (0U)             /* Reserve_2B-0565                                              */
#define CALIB_MCUID_RSV_2B_0566_DEF                 (0U)             /* Reserve_2B-0566                                              */
#define CALIB_MCUID_RSV_2B_0567_DEF                 (0U)             /* Reserve_2B-0567                                              */
#define CALIB_MCUID_RSV_2B_0568_DEF                 (0U)             /* Reserve_2B-0568                                              */
#define CALIB_MCUID_RSV_2B_0569_DEF                 (0U)             /* Reserve_2B-0569                                              */
#define CALIB_MCUID_RSV_2B_0570_DEF                 (0U)             /* Reserve_2B-0570                                              */
#define CALIB_MCUID_RSV_2B_0571_DEF                 (0U)             /* Reserve_2B-0571                                              */
#define CALIB_MCUID_RSV_2B_0572_DEF                 (0U)             /* Reserve_2B-0572                                              */
#define CALIB_MCUID_RSV_2B_0573_DEF                 (0U)             /* Reserve_2B-0573                                              */
#define CALIB_MCUID_RSV_2B_0574_DEF                 (0U)             /* Reserve_2B-0574                                              */
#define CALIB_MCUID_RSV_2B_0575_DEF                 (0U)             /* Reserve_2B-0575                                              */
#define CALIB_MCUID_RSV_2B_0576_DEF                 (0U)             /* Reserve_2B-0576                                              */
#define CALIB_MCUID_RSV_2B_0577_DEF                 (0U)             /* Reserve_2B-0577                                              */
#define CALIB_MCUID_RSV_2B_0578_DEF                 (0U)             /* Reserve_2B-0578                                              */
#define CALIB_MCUID_RSV_2B_0579_DEF                 (0U)             /* Reserve_2B-0579                                              */
#define CALIB_MCUID_RSV_2B_0580_DEF                 (0U)             /* Reserve_2B-0580                                              */
#define CALIB_MCUID_RSV_2B_0581_DEF                 (0U)             /* Reserve_2B-0581                                              */
#define CALIB_MCUID_RSV_2B_0582_DEF                 (0U)             /* Reserve_2B-0582                                              */
#define CALIB_MCUID_RSV_2B_0583_DEF                 (0U)             /* Reserve_2B-0583                                              */
#define CALIB_MCUID_RSV_2B_0584_DEF                 (0U)             /* Reserve_2B-0584                                              */
#define CALIB_MCUID_RSV_2B_0585_DEF                 (0U)             /* Reserve_2B-0585                                              */
#define CALIB_MCUID_RSV_2B_0586_DEF                 (0U)             /* Reserve_2B-0586                                              */
#define CALIB_MCUID_RSV_2B_0587_DEF                 (0U)             /* Reserve_2B-0587                                              */
#define CALIB_MCUID_RSV_2B_0588_DEF                 (0U)             /* Reserve_2B-0588                                              */
#define CALIB_MCUID_RSV_2B_0589_DEF                 (0U)             /* Reserve_2B-0589                                              */
#define CALIB_MCUID_RSV_2B_0590_DEF                 (0U)             /* Reserve_2B-0590                                              */
#define CALIB_MCUID_RSV_2B_0591_DEF                 (0U)             /* Reserve_2B-0591                                              */
#define CALIB_MCUID_RSV_2B_0592_DEF                 (0U)             /* Reserve_2B-0592                                              */
#define CALIB_MCUID_RSV_2B_0593_DEF                 (0U)             /* Reserve_2B-0593                                              */
#define CALIB_MCUID_RSV_2B_0594_DEF                 (0U)             /* Reserve_2B-0594                                              */
#define CALIB_MCUID_RSV_2B_0595_DEF                 (0U)             /* Reserve_2B-0595                                              */
#define CALIB_MCUID_RSV_2B_0596_DEF                 (0U)             /* Reserve_2B-0596                                              */
#define CALIB_MCUID_RSV_2B_0597_DEF                 (0U)             /* Reserve_2B-0597                                              */
#define CALIB_MCUID_RSV_2B_0598_DEF                 (0U)             /* Reserve_2B-0598                                              */
#define CALIB_MCUID_RSV_2B_0599_DEF                 (0U)             /* Reserve_2B-0599                                              */
#define CALIB_MCUID_RSV_2B_0600_DEF                 (0U)             /* Reserve_2B-0600                                              */
#define CALIB_MCUID_RSV_2B_0601_DEF                 (0U)             /* Reserve_2B-0601                                              */
#define CALIB_MCUID_RSV_2B_0602_DEF                 (0U)             /* Reserve_2B-0602                                              */
#define CALIB_MCUID_RSV_2B_0603_DEF                 (0U)             /* Reserve_2B-0603                                              */
#define CALIB_MCUID_RSV_2B_0604_DEF                 (0U)             /* Reserve_2B-0604                                              */
#define CALIB_MCUID_RSV_2B_0605_DEF                 (0U)             /* Reserve_2B-0605                                              */
#define CALIB_MCUID_RSV_2B_0606_DEF                 (0U)             /* Reserve_2B-0606                                              */
#define CALIB_MCUID_RSV_2B_0607_DEF                 (0U)             /* Reserve_2B-0607                                              */
#define CALIB_MCUID_RSV_2B_0608_DEF                 (0U)             /* Reserve_2B-0608                                              */
#define CALIB_MCUID_RSV_2B_0609_DEF                 (0U)             /* Reserve_2B-0609                                              */
#define CALIB_MCUID_RSV_2B_0610_DEF                 (0U)             /* Reserve_2B-0610                                              */
#define CALIB_MCUID_RSV_2B_0611_DEF                 (0U)             /* Reserve_2B-0611                                              */
#define CALIB_MCUID_RSV_2B_0612_DEF                 (0U)             /* Reserve_2B-0612                                              */
#define CALIB_MCUID_RSV_2B_0613_DEF                 (0U)             /* Reserve_2B-0613                                              */
#define CALIB_MCUID_RSV_2B_0614_DEF                 (0U)             /* Reserve_2B-0614                                              */
#define CALIB_MCUID_RSV_2B_0615_DEF                 (0U)             /* Reserve_2B-0615                                              */
#define CALIB_MCUID_RSV_2B_0616_DEF                 (0U)             /* Reserve_2B-0616                                              */
#define CALIB_MCUID_RSV_2B_0617_DEF                 (0U)             /* Reserve_2B-0617                                              */
#define CALIB_MCUID_RSV_2B_0618_DEF                 (0U)             /* Reserve_2B-0618                                              */
#define CALIB_MCUID_RSV_2B_0619_DEF                 (0U)             /* Reserve_2B-0619                                              */
#define CALIB_MCUID_RSV_2B_0620_DEF                 (0U)             /* Reserve_2B-0620                                              */
#define CALIB_MCUID_RSV_2B_0621_DEF                 (0U)             /* Reserve_2B-0621                                              */
#define CALIB_MCUID_RSV_2B_0622_DEF                 (0U)             /* Reserve_2B-0622                                              */
#define CALIB_MCUID_RSV_2B_0623_DEF                 (0U)             /* Reserve_2B-0623                                              */
#define CALIB_MCUID_RSV_2B_0624_DEF                 (0U)             /* Reserve_2B-0624                                              */
#define CALIB_MCUID_RSV_2B_0625_DEF                 (0U)             /* Reserve_2B-0625                                              */
#define CALIB_MCUID_RSV_2B_0626_DEF                 (0U)             /* Reserve_2B-0626                                              */
#define CALIB_MCUID_RSV_2B_0627_DEF                 (0U)             /* Reserve_2B-0627                                              */
#define CALIB_MCUID_RSV_2B_0628_DEF                 (0U)             /* Reserve_2B-0628                                              */
#define CALIB_MCUID_RSV_2B_0629_DEF                 (0U)             /* Reserve_2B-0629                                              */
#define CALIB_MCUID_RSV_2B_0630_DEF                 (0U)             /* Reserve_2B-0630                                              */
#define CALIB_MCUID_RSV_2B_0631_DEF                 (0U)             /* Reserve_2B-0631                                              */
#define CALIB_MCUID_RSV_2B_0632_DEF                 (0U)             /* Reserve_2B-0632                                              */
#define CALIB_MCUID_RSV_2B_0633_DEF                 (0U)             /* Reserve_2B-0633                                              */
#define CALIB_MCUID_RSV_2B_0634_DEF                 (0U)             /* Reserve_2B-0634                                              */
#define CALIB_MCUID_RSV_2B_0635_DEF                 (0U)             /* Reserve_2B-0635                                              */
#define CALIB_MCUID_RSV_2B_0636_DEF                 (0U)             /* Reserve_2B-0636                                              */
#define CALIB_MCUID_RSV_2B_0637_DEF                 (0U)             /* Reserve_2B-0637                                              */
#define CALIB_MCUID_RSV_2B_0638_DEF                 (0U)             /* Reserve_2B-0638                                              */
#define CALIB_MCUID_RSV_2B_0639_DEF                 (0U)             /* Reserve_2B-0639                                              */
#define CALIB_MCUID_RSV_2B_0640_DEF                 (0U)             /* Reserve_2B-0640                                              */
#define CALIB_MCUID_RSV_2B_0641_DEF                 (0U)             /* Reserve_2B-0641                                              */
#define CALIB_MCUID_RSV_2B_0642_DEF                 (0U)             /* Reserve_2B-0642                                              */
#define CALIB_MCUID_RSV_2B_0643_DEF                 (0U)             /* Reserve_2B-0643                                              */
#define CALIB_MCUID_RSV_2B_0644_DEF                 (0U)             /* Reserve_2B-0644                                              */
#define CALIB_MCUID_RSV_2B_0645_DEF                 (0U)             /* Reserve_2B-0645                                              */
#define CALIB_MCUID_RSV_2B_0646_DEF                 (0U)             /* Reserve_2B-0646                                              */
#define CALIB_MCUID_RSV_2B_0647_DEF                 (0U)             /* Reserve_2B-0647                                              */
#define CALIB_MCUID_RSV_2B_0648_DEF                 (0U)             /* Reserve_2B-0648                                              */
#define CALIB_MCUID_RSV_2B_0649_DEF                 (0U)             /* Reserve_2B-0649                                              */
#define CALIB_MCUID_RSV_2B_0650_DEF                 (0U)             /* Reserve_2B-0650                                              */
#define CALIB_MCUID_RSV_2B_0651_DEF                 (0U)             /* Reserve_2B-0651                                              */
#define CALIB_MCUID_RSV_2B_0652_DEF                 (0U)             /* Reserve_2B-0652                                              */
#define CALIB_MCUID_RSV_2B_0653_DEF                 (0U)             /* Reserve_2B-0653                                              */
#define CALIB_MCUID_RSV_2B_0654_DEF                 (0U)             /* Reserve_2B-0654                                              */
#define CALIB_MCUID_RSV_2B_0655_DEF                 (0U)             /* Reserve_2B-0655                                              */
#define CALIB_MCUID_RSV_2B_0656_DEF                 (0U)             /* Reserve_2B-0656                                              */
#define CALIB_MCUID_RSV_2B_0657_DEF                 (0U)             /* Reserve_2B-0657                                              */
#define CALIB_MCUID_RSV_2B_0658_DEF                 (0U)             /* Reserve_2B-0658                                              */
#define CALIB_MCUID_RSV_2B_0659_DEF                 (0U)             /* Reserve_2B-0659                                              */
#define CALIB_MCUID_RSV_2B_0660_DEF                 (0U)             /* Reserve_2B-0660                                              */
#define CALIB_MCUID_RSV_2B_0661_DEF                 (0U)             /* Reserve_2B-0661                                              */
#define CALIB_MCUID_RSV_2B_0662_DEF                 (0U)             /* Reserve_2B-0662                                              */
#define CALIB_MCUID_RSV_2B_0663_DEF                 (0U)             /* Reserve_2B-0663                                              */
#define CALIB_MCUID_RSV_2B_0664_DEF                 (0U)             /* Reserve_2B-0664                                              */
#define CALIB_MCUID_RSV_2B_0665_DEF                 (0U)             /* Reserve_2B-0665                                              */
#define CALIB_MCUID_RSV_2B_0666_DEF                 (0U)             /* Reserve_2B-0666                                              */
#define CALIB_MCUID_RSV_2B_0667_DEF                 (0U)             /* Reserve_2B-0667                                              */
#define CALIB_MCUID_RSV_2B_0668_DEF                 (0U)             /* Reserve_2B-0668                                              */
#define CALIB_MCUID_RSV_2B_0669_DEF                 (0U)             /* Reserve_2B-0669                                              */
#define CALIB_MCUID_RSV_2B_0670_DEF                 (0U)             /* Reserve_2B-0670                                              */
#define CALIB_MCUID_RSV_2B_0671_DEF                 (0U)             /* Reserve_2B-0671                                              */
#define CALIB_MCUID_RSV_2B_0672_DEF                 (0U)             /* Reserve_2B-0672                                              */
#define CALIB_MCUID_RSV_2B_0673_DEF                 (0U)             /* Reserve_2B-0673                                              */
#define CALIB_MCUID_RSV_2B_0674_DEF                 (0U)             /* Reserve_2B-0674                                              */
#define CALIB_MCUID_RSV_2B_0675_DEF                 (0U)             /* Reserve_2B-0675                                              */
#define CALIB_MCUID_RSV_2B_0676_DEF                 (0U)             /* Reserve_2B-0676                                              */
#define CALIB_MCUID_RSV_2B_0677_DEF                 (0U)             /* Reserve_2B-0677                                              */
#define CALIB_MCUID_RSV_2B_0678_DEF                 (0U)             /* Reserve_2B-0678                                              */
#define CALIB_MCUID_RSV_2B_0679_DEF                 (0U)             /* Reserve_2B-0679                                              */
#define CALIB_MCUID_RSV_2B_0680_DEF                 (0U)             /* Reserve_2B-0680                                              */
#define CALIB_MCUID_RSV_2B_0681_DEF                 (0U)             /* Reserve_2B-0681                                              */
#define CALIB_MCUID_RSV_2B_0682_DEF                 (0U)             /* Reserve_2B-0682                                              */
#define CALIB_MCUID_RSV_2B_0683_DEF                 (0U)             /* Reserve_2B-0683                                              */
#define CALIB_MCUID_RSV_2B_0684_DEF                 (0U)             /* Reserve_2B-0684                                              */
#define CALIB_MCUID_RSV_2B_0685_DEF                 (0U)             /* Reserve_2B-0685                                              */
#define CALIB_MCUID_RSV_2B_0686_DEF                 (0U)             /* Reserve_2B-0686                                              */
#define CALIB_MCUID_RSV_2B_0687_DEF                 (0U)             /* Reserve_2B-0687                                              */
#define CALIB_MCUID_RSV_2B_0688_DEF                 (0U)             /* Reserve_2B-0688                                              */
#define CALIB_MCUID_RSV_2B_0689_DEF                 (0U)             /* Reserve_2B-0689                                              */
#define CALIB_MCUID_RSV_2B_0690_DEF                 (0U)             /* Reserve_2B-0690                                              */
#define CALIB_MCUID_RSV_2B_0691_DEF                 (0U)             /* Reserve_2B-0691                                              */
#define CALIB_MCUID_RSV_2B_0692_DEF                 (0U)             /* Reserve_2B-0692                                              */
#define CALIB_MCUID_RSV_2B_0693_DEF                 (0U)             /* Reserve_2B-0693                                              */
#define CALIB_MCUID_RSV_2B_0694_DEF                 (0U)             /* Reserve_2B-0694                                              */
#define CALIB_MCUID_RSV_2B_0695_DEF                 (0U)             /* Reserve_2B-0695                                              */
#define CALIB_MCUID_RSV_2B_0696_DEF                 (0U)             /* Reserve_2B-0696                                              */
#define CALIB_MCUID_RSV_2B_0697_DEF                 (0U)             /* Reserve_2B-0697                                              */
#define CALIB_MCUID_RSV_2B_0698_DEF                 (0U)             /* Reserve_2B-0698                                              */
#define CALIB_MCUID_RSV_2B_0699_DEF                 (0U)             /* Reserve_2B-0699                                              */
#define CALIB_MCUID_RSV_2B_0700_DEF                 (0U)             /* Reserve_2B-0700                                              */
#define CALIB_MCUID_RSV_2B_0701_DEF                 (0U)             /* Reserve_2B-0701                                              */
#define CALIB_MCUID_RSV_2B_0702_DEF                 (0U)             /* Reserve_2B-0702                                              */
#define CALIB_MCUID_RSV_2B_0703_DEF                 (0U)             /* Reserve_2B-0703                                              */
#define CALIB_MCUID_RSV_2B_0704_DEF                 (0U)             /* Reserve_2B-0704                                              */
#define CALIB_MCUID_RSV_2B_0705_DEF                 (0U)             /* Reserve_2B-0705                                              */
#define CALIB_MCUID_RSV_2B_0706_DEF                 (0U)             /* Reserve_2B-0706                                              */
#define CALIB_MCUID_RSV_2B_0707_DEF                 (0U)             /* Reserve_2B-0707                                              */
#define CALIB_MCUID_RSV_2B_0708_DEF                 (0U)             /* Reserve_2B-0708                                              */
#define CALIB_MCUID_RSV_2B_0709_DEF                 (0U)             /* Reserve_2B-0709                                              */
#define CALIB_MCUID_RSV_2B_0710_DEF                 (0U)             /* Reserve_2B-0710                                              */
#define CALIB_MCUID_RSV_2B_0711_DEF                 (0U)             /* Reserve_2B-0711                                              */
#define CALIB_MCUID_RSV_2B_0712_DEF                 (0U)             /* Reserve_2B-0712                                              */
#define CALIB_MCUID_RSV_2B_0713_DEF                 (0U)             /* Reserve_2B-0713                                              */
#define CALIB_MCUID_RSV_2B_0714_DEF                 (0U)             /* Reserve_2B-0714                                              */
#define CALIB_MCUID_RSV_2B_0715_DEF                 (0U)             /* Reserve_2B-0715                                              */
#define CALIB_MCUID_RSV_2B_0716_DEF                 (0U)             /* Reserve_2B-0716                                              */
#define CALIB_MCUID_RSV_2B_0717_DEF                 (0U)             /* Reserve_2B-0717                                              */
#define CALIB_MCUID_RSV_2B_0718_DEF                 (0U)             /* Reserve_2B-0718                                              */
#define CALIB_MCUID_RSV_2B_0719_DEF                 (0U)             /* Reserve_2B-0719                                              */
#define CALIB_MCUID_RSV_2B_0720_DEF                 (0U)             /* Reserve_2B-0720                                              */
#define CALIB_MCUID_RSV_2B_0721_DEF                 (0U)             /* Reserve_2B-0721                                              */
#define CALIB_MCUID_RSV_2B_0722_DEF                 (0U)             /* Reserve_2B-0722                                              */
#define CALIB_MCUID_RSV_2B_0723_DEF                 (0U)             /* Reserve_2B-0723                                              */
#define CALIB_MCUID_RSV_2B_0724_DEF                 (0U)             /* Reserve_2B-0724                                              */
#define CALIB_MCUID_RSV_2B_0725_DEF                 (0U)             /* Reserve_2B-0725                                              */
#define CALIB_MCUID_RSV_2B_0726_DEF                 (0U)             /* Reserve_2B-0726                                              */
#define CALIB_MCUID_RSV_2B_0727_DEF                 (0U)             /* Reserve_2B-0727                                              */
#define CALIB_MCUID_RSV_2B_0728_DEF                 (0U)             /* Reserve_2B-0728                                              */
#define CALIB_MCUID_RSV_2B_0729_DEF                 (0U)             /* Reserve_2B-0729                                              */
#define CALIB_MCUID_RSV_2B_0730_DEF                 (0U)             /* Reserve_2B-0730                                              */
#define CALIB_MCUID_RSV_2B_0731_DEF                 (0U)             /* Reserve_2B-0731                                              */
#define CALIB_MCUID_RSV_2B_0732_DEF                 (0U)             /* Reserve_2B-0732                                              */
#define CALIB_MCUID_RSV_2B_0733_DEF                 (0U)             /* Reserve_2B-0733                                              */
#define CALIB_MCUID_RSV_2B_0734_DEF                 (0U)             /* Reserve_2B-0734                                              */
#define CALIB_MCUID_RSV_2B_0735_DEF                 (0U)             /* Reserve_2B-0735                                              */
#define CALIB_MCUID_RSV_2B_0736_DEF                 (0U)             /* Reserve_2B-0736                                              */
#define CALIB_MCUID_RSV_2B_0737_DEF                 (0U)             /* Reserve_2B-0737                                              */
#define CALIB_MCUID_RSV_2B_0738_DEF                 (0U)             /* Reserve_2B-0738                                              */
#define CALIB_MCUID_RSV_2B_0739_DEF                 (0U)             /* Reserve_2B-0739                                              */
#define CALIB_MCUID_RSV_2B_0740_DEF                 (0U)             /* Reserve_2B-0740                                              */
#define CALIB_MCUID_RSV_2B_0741_DEF                 (0U)             /* Reserve_2B-0741                                              */
#define CALIB_MCUID_RSV_2B_0742_DEF                 (0U)             /* Reserve_2B-0742                                              */
#define CALIB_MCUID_RSV_2B_0743_DEF                 (0U)             /* Reserve_2B-0743                                              */
#define CALIB_MCUID_RSV_2B_0744_DEF                 (0U)             /* Reserve_2B-0744                                              */
#define CALIB_MCUID_RSV_2B_0745_DEF                 (0U)             /* Reserve_2B-0745                                              */
#define CALIB_MCUID_RSV_2B_0746_DEF                 (0U)             /* Reserve_2B-0746                                              */
#define CALIB_MCUID_RSV_2B_0747_DEF                 (0U)             /* Reserve_2B-0747                                              */
#define CALIB_MCUID_RSV_2B_0748_DEF                 (0U)             /* Reserve_2B-0748                                              */
#define CALIB_MCUID_RSV_2B_0749_DEF                 (0U)             /* Reserve_2B-0749                                              */
#define CALIB_MCUID_RSV_2B_0750_DEF                 (0U)             /* Reserve_2B-0750                                              */
#define CALIB_MCUID_RSV_2B_0751_DEF                 (0U)             /* Reserve_2B-0751                                              */
#define CALIB_MCUID_RSV_2B_0752_DEF                 (0U)             /* Reserve_2B-0752                                              */
#define CALIB_MCUID_RSV_2B_0753_DEF                 (0U)             /* Reserve_2B-0753                                              */
#define CALIB_MCUID_RSV_2B_0754_DEF                 (0U)             /* Reserve_2B-0754                                              */
#define CALIB_MCUID_RSV_2B_0755_DEF                 (0U)             /* Reserve_2B-0755                                              */
#define CALIB_MCUID_RSV_2B_0756_DEF                 (0U)             /* Reserve_2B-0756                                              */
#define CALIB_MCUID_RSV_2B_0757_DEF                 (0U)             /* Reserve_2B-0757                                              */
#define CALIB_MCUID_RSV_2B_0758_DEF                 (0U)             /* Reserve_2B-0758                                              */
#define CALIB_MCUID_RSV_2B_0759_DEF                 (0U)             /* Reserve_2B-0759                                              */
#define CALIB_MCUID_RSV_2B_0760_DEF                 (0U)             /* Reserve_2B-0760                                              */
#define CALIB_MCUID_RSV_2B_0761_DEF                 (0U)             /* Reserve_2B-0761                                              */
#define CALIB_MCUID_RSV_2B_0762_DEF                 (0U)             /* Reserve_2B-0762                                              */
#define CALIB_MCUID_RSV_2B_0763_DEF                 (0U)             /* Reserve_2B-0763                                              */
#define CALIB_MCUID_RSV_2B_0764_DEF                 (0U)             /* Reserve_2B-0764                                              */
#define CALIB_MCUID_RSV_2B_0765_DEF                 (0U)             /* Reserve_2B-0765                                              */
#define CALIB_MCUID_RSV_2B_0766_DEF                 (0U)             /* Reserve_2B-0766                                              */
#define CALIB_MCUID_RSV_2B_0767_DEF                 (0U)             /* Reserve_2B-0767                                              */
#define CALIB_MCUID_RSV_2B_0768_DEF                 (0U)             /* Reserve_2B-0768                                              */
#define CALIB_MCUID_RSV_2B_0769_DEF                 (0U)             /* Reserve_2B-0769                                              */
#define CALIB_MCUID_RSV_2B_0770_DEF                 (0U)             /* Reserve_2B-0770                                              */
#define CALIB_MCUID_RSV_2B_0771_DEF                 (0U)             /* Reserve_2B-0771                                              */
#define CALIB_MCUID_RSV_2B_0772_DEF                 (0U)             /* Reserve_2B-0772                                              */
#define CALIB_MCUID_RSV_2B_0773_DEF                 (0U)             /* Reserve_2B-0773                                              */
#define CALIB_MCUID_RSV_2B_0774_DEF                 (0U)             /* Reserve_2B-0774                                              */
#define CALIB_MCUID_RSV_2B_0775_DEF                 (0U)             /* Reserve_2B-0775                                              */
#define CALIB_MCUID_RSV_2B_0776_DEF                 (0U)             /* Reserve_2B-0776                                              */
#define CALIB_MCUID_RSV_2B_0777_DEF                 (0U)             /* Reserve_2B-0777                                              */
#define CALIB_MCUID_RSV_2B_0778_DEF                 (0U)             /* Reserve_2B-0778                                              */
#define CALIB_MCUID_RSV_2B_0779_DEF                 (0U)             /* Reserve_2B-0779                                              */
#define CALIB_MCUID_RSV_2B_0780_DEF                 (0U)             /* Reserve_2B-0780                                              */
#define CALIB_MCUID_RSV_2B_0781_DEF                 (0U)             /* Reserve_2B-0781                                              */
#define CALIB_MCUID_RSV_2B_0782_DEF                 (0U)             /* Reserve_2B-0782                                              */
#define CALIB_MCUID_RSV_2B_0783_DEF                 (0U)             /* Reserve_2B-0783                                              */
#define CALIB_MCUID_RSV_2B_0784_DEF                 (0U)             /* Reserve_2B-0784                                              */
#define CALIB_MCUID_RSV_2B_0785_DEF                 (0U)             /* Reserve_2B-0785                                              */
#define CALIB_MCUID_RSV_2B_0786_DEF                 (0U)             /* Reserve_2B-0786                                              */
#define CALIB_MCUID_RSV_2B_0787_DEF                 (0U)             /* Reserve_2B-0787                                              */
#define CALIB_MCUID_RSV_2B_0788_DEF                 (0U)             /* Reserve_2B-0788                                              */
#define CALIB_MCUID_RSV_2B_0789_DEF                 (0U)             /* Reserve_2B-0789                                              */
#define CALIB_MCUID_RSV_2B_0790_DEF                 (0U)             /* Reserve_2B-0790                                              */
#define CALIB_MCUID_RSV_2B_0791_DEF                 (0U)             /* Reserve_2B-0791                                              */
#define CALIB_MCUID_RSV_2B_0792_DEF                 (0U)             /* Reserve_2B-0792                                              */
#define CALIB_MCUID_RSV_2B_0793_DEF                 (0U)             /* Reserve_2B-0793                                              */
#define CALIB_MCUID_RSV_2B_0794_DEF                 (0U)             /* Reserve_2B-0794                                              */
#define CALIB_MCUID_RSV_2B_0795_DEF                 (0U)             /* Reserve_2B-0795                                              */
#define CALIB_MCUID_RSV_2B_0796_DEF                 (0U)             /* Reserve_2B-0796                                              */
#define CALIB_MCUID_RSV_2B_0797_DEF                 (0U)             /* Reserve_2B-0797                                              */
#define CALIB_MCUID_RSV_2B_0798_DEF                 (0U)             /* Reserve_2B-0798                                              */
#define CALIB_MCUID_RSV_2B_0799_DEF                 (0U)             /* Reserve_2B-0799                                              */
#define CALIB_MCUID_RSV_2B_0800_DEF                 (0U)             /* Reserve_2B-0800                                              */
#define CALIB_MCUID_RSV_2B_0801_DEF                 (0U)             /* Reserve_2B-0801                                              */
#define CALIB_MCUID_RSV_2B_0802_DEF                 (0U)             /* Reserve_2B-0802                                              */
#define CALIB_MCUID_RSV_2B_0803_DEF                 (0U)             /* Reserve_2B-0803                                              */
#define CALIB_MCUID_RSV_2B_0804_DEF                 (0U)             /* Reserve_2B-0804                                              */
#define CALIB_MCUID_RSV_2B_0805_DEF                 (0U)             /* Reserve_2B-0805                                              */
#define CALIB_MCUID_RSV_2B_0806_DEF                 (0U)             /* Reserve_2B-0806                                              */
#define CALIB_MCUID_RSV_2B_0807_DEF                 (0U)             /* Reserve_2B-0807                                              */
#define CALIB_MCUID_RSV_2B_0808_DEF                 (0U)             /* Reserve_2B-0808                                              */
#define CALIB_MCUID_RSV_2B_0809_DEF                 (0U)             /* Reserve_2B-0809                                              */
#define CALIB_MCUID_RSV_2B_0810_DEF                 (0U)             /* Reserve_2B-0810                                              */
#define CALIB_MCUID_RSV_2B_0811_DEF                 (0U)             /* Reserve_2B-0811                                              */
#define CALIB_MCUID_RSV_2B_0812_DEF                 (0U)             /* Reserve_2B-0812                                              */
#define CALIB_MCUID_RSV_2B_0813_DEF                 (0U)             /* Reserve_2B-0813                                              */
#define CALIB_MCUID_RSV_2B_0814_DEF                 (0U)             /* Reserve_2B-0814                                              */
#define CALIB_MCUID_RSV_2B_0815_DEF                 (0U)             /* Reserve_2B-0815                                              */
#define CALIB_MCUID_RSV_2B_0816_DEF                 (0U)             /* Reserve_2B-0816                                              */
#define CALIB_MCUID_RSV_2B_0817_DEF                 (0U)             /* Reserve_2B-0817                                              */
#define CALIB_MCUID_RSV_2B_0818_DEF                 (0U)             /* Reserve_2B-0818                                              */
#define CALIB_MCUID_RSV_2B_0819_DEF                 (0U)             /* Reserve_2B-0819                                              */

#define CALIB_MCUID_RSV_4B_0001_DEF                 (0U)             /* Reserve_4B-0001                                              */
#define CALIB_MCUID_RSV_4B_0002_DEF                 (0U)             /* Reserve_4B-0002                                              */
#define CALIB_MCUID_RSV_4B_0003_DEF                 (0U)             /* Reserve_4B-0003                                              */
#define CALIB_MCUID_RSV_4B_0004_DEF                 (0U)             /* Reserve_4B-0004                                              */
#define CALIB_MCUID_RSV_4B_0005_DEF                 (0U)             /* Reserve_4B-0005                                              */
#define CALIB_MCUID_RSV_4B_0006_DEF                 (0U)             /* Reserve_4B-0006                                              */
#define CALIB_MCUID_RSV_4B_0007_DEF                 (0U)             /* Reserve_4B-0007                                              */
#define CALIB_MCUID_RSV_4B_0008_DEF                 (0U)             /* Reserve_4B-0008                                              */
#define CALIB_MCUID_RSV_4B_0009_DEF                 (0U)             /* Reserve_4B-0009                                              */
#define CALIB_MCUID_RSV_4B_0010_DEF                 (0U)             /* Reserve_4B-0010                                              */
#define CALIB_MCUID_RSV_4B_0011_DEF                 (0U)             /* Reserve_4B-0011                                              */
#define CALIB_MCUID_RSV_4B_0012_DEF                 (0U)             /* Reserve_4B-0012                                              */
#define CALIB_MCUID_RSV_4B_0013_DEF                 (0U)             /* Reserve_4B-0013                                              */
#define CALIB_MCUID_RSV_4B_0014_DEF                 (0U)             /* Reserve_4B-0014                                              */
#define CALIB_MCUID_RSV_4B_0015_DEF                 (0U)             /* Reserve_4B-0015                                              */
#define CALIB_MCUID_RSV_4B_0016_DEF                 (0U)             /* Reserve_4B-0016                                              */
#define CALIB_MCUID_RSV_4B_0017_DEF                 (0U)             /* Reserve_4B-0017                                              */
#define CALIB_MCUID_RSV_4B_0018_DEF                 (0U)             /* Reserve_4B-0018                                              */
#define CALIB_MCUID_RSV_4B_0019_DEF                 (0U)             /* Reserve_4B-0019                                              */
#define CALIB_MCUID_RSV_4B_0020_DEF                 (0U)             /* Reserve_4B-0020                                              */
#define CALIB_MCUID_RSV_4B_0021_DEF                 (0U)             /* Reserve_4B-0021                                              */
#define CALIB_MCUID_RSV_4B_0022_DEF                 (0U)             /* Reserve_4B-0022                                              */
#define CALIB_MCUID_RSV_4B_0023_DEF                 (0U)             /* Reserve_4B-0023                                              */
#define CALIB_MCUID_RSV_4B_0024_DEF                 (0U)             /* Reserve_4B-0024                                              */
#define CALIB_MCUID_RSV_4B_0025_DEF                 (0U)             /* Reserve_4B-0025                                              */
#define CALIB_MCUID_RSV_4B_0026_DEF                 (0U)             /* Reserve_4B-0026                                              */
#define CALIB_MCUID_RSV_4B_0027_DEF                 (0U)             /* Reserve_4B-0027                                              */
#define CALIB_MCUID_RSV_4B_0028_DEF                 (0U)             /* Reserve_4B-0028                                              */
#define CALIB_MCUID_RSV_4B_0029_DEF                 (0U)             /* Reserve_4B-0029                                              */
#define CALIB_MCUID_RSV_4B_0030_DEF                 (0U)             /* Reserve_4B-0030                                              */
#define CALIB_MCUID_RSV_4B_0031_DEF                 (0U)             /* Reserve_4B-0031                                              */
#define CALIB_MCUID_RSV_4B_0032_DEF                 (0U)             /* Reserve_4B-0032                                              */
#define CALIB_MCUID_RSV_4B_0033_DEF                 (0U)             /* Reserve_4B-0033                                              */
#define CALIB_MCUID_RSV_4B_0034_DEF                 (0U)             /* Reserve_4B-0034                                              */
#define CALIB_MCUID_RSV_4B_0035_DEF                 (0U)             /* Reserve_4B-0035                                              */
#define CALIB_MCUID_RSV_4B_0036_DEF                 (0U)             /* Reserve_4B-0036                                              */
#define CALIB_MCUID_RSV_4B_0037_DEF                 (0U)             /* Reserve_4B-0037                                              */
#define CALIB_MCUID_RSV_4B_0038_DEF                 (0U)             /* Reserve_4B-0038                                              */
#define CALIB_MCUID_RSV_4B_0039_DEF                 (0U)             /* Reserve_4B-0039                                              */
#define CALIB_MCUID_RSV_4B_0040_DEF                 (0U)             /* Reserve_4B-0040                                              */
#define CALIB_MCUID_RSV_4B_0041_DEF                 (0U)             /* Reserve_4B-0041                                              */
#define CALIB_MCUID_RSV_4B_0042_DEF                 (0U)             /* Reserve_4B-0042                                              */
#define CALIB_MCUID_RSV_4B_0043_DEF                 (0U)             /* Reserve_4B-0043                                              */
#define CALIB_MCUID_RSV_4B_0044_DEF                 (0U)             /* Reserve_4B-0044                                              */
#define CALIB_MCUID_RSV_4B_0045_DEF                 (0U)             /* Reserve_4B-0045                                              */
#define CALIB_MCUID_RSV_4B_0046_DEF                 (0U)             /* Reserve_4B-0046                                              */
#define CALIB_MCUID_RSV_4B_0047_DEF                 (0U)             /* Reserve_4B-0047                                              */
#define CALIB_MCUID_RSV_4B_0048_DEF                 (0U)             /* Reserve_4B-0048                                              */
#define CALIB_MCUID_RSV_4B_0049_DEF                 (0U)             /* Reserve_4B-0049                                              */
#define CALIB_MCUID_RSV_4B_0050_DEF                 (0U)             /* Reserve_4B-0050                                              */
#define CALIB_MCUID_RSV_4B_0051_DEF                 (0U)             /* Reserve_4B-0051                                              */
#define CALIB_MCUID_RSV_4B_0052_DEF                 (0U)             /* Reserve_4B-0052                                              */
#define CALIB_MCUID_RSV_4B_0053_DEF                 (0U)             /* Reserve_4B-0053                                              */
#define CALIB_MCUID_RSV_4B_0054_DEF                 (0U)             /* Reserve_4B-0054                                              */
#define CALIB_MCUID_RSV_4B_0055_DEF                 (0U)             /* Reserve_4B-0055                                              */
#define CALIB_MCUID_RSV_4B_0056_DEF                 (0U)             /* Reserve_4B-0056                                              */
#define CALIB_MCUID_RSV_4B_0057_DEF                 (0U)             /* Reserve_4B-0057                                              */
#define CALIB_MCUID_RSV_4B_0058_DEF                 (0U)             /* Reserve_4B-0058                                              */
#define CALIB_MCUID_RSV_4B_0059_DEF                 (0U)             /* Reserve_4B-0059                                              */
#define CALIB_MCUID_RSV_4B_0060_DEF                 (0U)             /* Reserve_4B-0060                                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif
