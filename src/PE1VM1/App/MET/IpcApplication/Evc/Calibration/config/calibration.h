/* 1.4.0 */
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
#define CALIBRATION_H_MINOR                        (4)
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
#define CALIB_MCUID0233_MIN                         (0U)             /* Rear Seat Door MIN                                           */
#define CALIB_MCUID0233_MAX                         (1U)             /* Rear Seat Door MAX                                           */
#define CALIB_MCUID0234_MIN                         (0U)             /* Walkthrough MIN                                              */
#define CALIB_MCUID0234_MAX                         (1U)             /* Walkthrough MAX                                              */
#define CALIB_MCUID0268_NUM                         (2U)             /* ODO/TRIP SW NUM                                              */
#define CALIB_MCUID0268_BUTTON_1                    (0U)             /* 1 BUTTON                                                     */
#define CALIB_MCUID0268_BUTTON_NON                  (1U)             /* No button                                                    */
#define CALIB_MCUID0340_MAX                         (21U)            /* Rheostat Position Night MAX                                  */
#define CALIB_MCUID0430_NUM                         (4U)             /* Rheostat SW Type NUM                                         */
#define CALIB_MCUID0430_1_INPUT                     (0U)             /* 1 INPUT                                                      */
#define CALIB_MCUID0430_2_INPUT                     (1U)             /* 2 INPUT                                                      */
#define CALIB_MCUID0430_THUMB_WHEEL                 (2U)             /* THUMB WHEEL                                                  */
#define CALIB_MCUID0430_SOFTSW                      (3U)             /* SOFT SW                                                      */
#define CALIB_MCUID0578_MIN                         (1U)             /* Deg_RTStep MIN                                               */
#define CALIB_MCUID0578_MAX                         (U1_MAX)         /* Deg_RTStepl MAX                                              */
#define CALIB_MCUID0604_TO_MCUID0607_NUM            (3U)             /* SeatBelt Regulation NUM                                      */
#define CALIB_MCUID0809_NUM                         (2U)             /* MCUID0809 Num                                                */
#define CALIB_MCUID0809_FMVSS                       (0U)             /* Mexico FMVSS                                                 */
#define CALIB_MCUID0809_UNR                         (1U)             /* Mexico UN-R                                                  */
#define CALIB_MCUID0810_NUM                         (2U)             /* MCUID0810 Num                                                */
#define CALIB_MCUID0810_FMVSS                       (0U)             /* Korea FMVSS                                                  */
#define CALIB_MCUID0810_UNR                         (1U)             /* Korea UN-R                                                   */
#define CALIB_MCUID0797_MIN                         (0U)             /* Constant write flag MIN                                      */
#define CALIB_MCUID0798_NUM                         (2U)             /* MCUID0798 Num                                                */
#define CALIB_MCUID0798_YL                          (0U)             /* Yellow                                                       */
#define CALIB_MCUID0798_RD                          (1U)             /* Red                                                          */
#define CALIB_MCUID0209_NUM                         (2U)             /* MCUID0209 Num                                                */
#define CALIB_MCUID0209_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0209_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0210_NUM                         (2U)             /* MCUID0210 Num                                                */
#define CALIB_MCUID0210_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0210_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0211_NUM                         (2U)             /* MCUID0211 Num                                                */
#define CALIB_MCUID0211_OFF                         (0U)             /* B/D Off, Trunk On                                            */
#define CALIB_MCUID0211_ON                          (1U)             /* B/D On, Trunk Off                                            */
#define CALIB_MCUID0212_NUM                         (2U)             /* MCUID0212 Num                                                */
#define CALIB_MCUID0212_OFF                         (0U)             /* B/D Off, Trunk On                                            */
#define CALIB_MCUID0212_ON                          (1U)             /* B/D On, Trunk Off                                            */
#define CALIB_MCUID0213_NUM                         (2U)             /* MCUID0213 Num                                                */
#define CALIB_MCUID0213_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0213_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0214_NUM                         (2U)             /* MCUID0214 Num                                                */
#define CALIB_MCUID0214_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0214_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0215_NUM                         (2U)             /* MCUID0215 Num                                                */
#define CALIB_MCUID0215_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0215_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0233_NUM                         (2U)             /* MCUID0233 Num                                                */
#define CALIB_MCUID0233_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0233_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0224_NUM                         (2U)             /* MCUID0224 Num                                                */
#define CALIB_MCUID0224_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0224_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0225_NUM                         (2U)             /* MCUID0225 Num                                                */
#define CALIB_MCUID0225_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0225_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0226_NUM                         (2U)             /* MCUID0226 Num                                                */
#define CALIB_MCUID0226_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0226_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0227_NUM                         (2U)             /* MCUID0227 Num                                                */
#define CALIB_MCUID0227_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0227_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0228_NUM                         (2)              /* MCUID0228 Num                                                */
#define CALIB_MCUID0228_OFF                         (0)              /* Off                                                          */
#define CALIB_MCUID0228_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0229_NUM                         (2U)             /* MCUID0229 Num                                                */
#define CALIB_MCUID0229_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0229_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0230_NUM                         (2U)             /* MCUID0230 Num                                                */
#define CALIB_MCUID0230_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0230_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0231_NUM                         (2U)             /* MCUID0231 Num                                                */
#define CALIB_MCUID0231_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0231_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0232_NUM                         (2U)             /* MCUID0232 Num                                                */
#define CALIB_MCUID0232_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0232_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID0234_NUM                         (2U)             /* MCUID0234 Num                                                */
#define CALIB_MCUID0234_OFF                         (0U)             /* Off                                                          */
#define CALIB_MCUID0234_ON                          (1U)             /* On                                                           */
#define CALIB_MCUID1138_NUM                         (4U)             /* MCUID1138 Num                                                */
#define CALIB_MCUID1138_FMVSS_2R                    (0U)             /* Rear 1st row + no center seat                                */
#define CALIB_MCUID1138_FMVSS_2RC                   (1U)             /* Rear 1st row + center seat                                   */
#define CALIB_MCUID1138_FMVSS_3R                    (2U)             /* Rear 2nd row                                                 */
#define CALIB_MCUID1138_FMVSS_1R                    (3U)             /* No rear  seat                                                */
#define CALIB_MCUID0590_NUM                         (3U)             /* MCUID0590 Num                                                */
#define CALIB_MCUID0590_NON                         (0U)             /* None                                                         */
#define CALIB_MCUID0590_RIGHT                       (1U)             /* Right                                                        */
#define CALIB_MCUID0590_LEFT                        (2U)             /* Left                                                         */
#define CALIB_MCUID0262_120KM                       (120U)           /* 120km/h                                                      */
#define CALIB_MCUID0262_140KM                       (140U)           /* 140km/h                                                      */
#define CALIB_MCUID0262_160KM                       (160U)           /* 160km/h                                                      */
#define CALIB_MCUID0262_170KM                       (170U)           /* 170km/h                                                      */
#define CALIB_MCUID0262_180KM                       (180U)           /* 180km/h                                                      */
#define CALIB_MCUID0262_200KM                       (200U)           /* 200km/h                                                      */
#define CALIB_MCUID0262_220KM                       (220U)           /* 220km/h                                                      */
#define CALIB_MCUID0262_240KM                       (240U)           /* 240km/h                                                      */
#define CALIB_MCUID0262_260KM                       (260U)           /* 260km/h                                                      */
#define CALIB_MCUID0262_280KM                       (280U)           /* 280km/h                                                      */
#define CALIB_MCUID0262_360KM                       (360U)           /* 360km/h                                                      */
#define CALIB_MCUID0263_120MPH                      (120U)           /* 120MPH                                                       */
#define CALIB_MCUID0263_140MPH                      (140)            /* 140MPH                                                       */
#define CALIB_MCUID0263_160MPH                      (160U)           /* 160MPH                                                       */
#define CALIB_MCUID0263_170MPH                      (170U)           /* 170MPH                                                       */
#define CALIB_MCUID0263_180MPH                      (180U)           /* 180MPH                                                       */
#define CALIB_MCUID0263_200MPH                      (200U)           /* 200MPH                                                       */
#define CALIB_MCUID0263_220MPH                      (220U)           /* 220MPH                                                       */
#define CALIB_MCUID0263_240MPH                      (240U)           /* 240MPH                                                       */
#define CALIB_MCUID0263_260MPH                      (260U)           /* 260MPH                                                       */
#define CALIB_MCUID0263_280MPH                      (280U)           /* 280MPH                                                       */
#define CALIB_MCUID0263_360MPH                      (360U)           /* 360MPH                                                       */
#define CALIB_MCUID0264_NUM                         (2U)             /* MCUID0264 Num                                                */
#define CALIB_MCUID0264_NORMAL                      (0U)             /* Normal                                                       */
#define CALIB_MCUID0264_FSPORT                      (1U)             /* F-Sport                                                      */
#define CALIB_MCUID0341_NUM                         (2U)             /* MCUID0341 Num                                                */
#define CALIB_MCUID0341_ON                          (1U)             /* ON                                                           */
#define CALIB_MCUID0341_OFF                         (0U)             /* OFF                                                          */
#define CALIB_MCUID1135_NUM                         (3U)             /* MCUID1135 Num                                                */
#define CALIB_MCUID1135_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID1135_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID1135_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID1136_NUM                         (3U)             /* MCUID1136 Num                                                */
#define CALIB_MCUID1136_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID1136_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID1136_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID0604_NUM                         (3U)             /* MCUID0604 Num                                                */
#define CALIB_MCUID0604_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID0604_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID0604_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID0605_NUM                         (3U)             /* MCUID0605 Num                                                */
#define CALIB_MCUID0605_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID0605_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID0605_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID0606_NUM                         (3U)             /* MCUID0606 Num                                                */
#define CALIB_MCUID0606_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID0606_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID0606_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID0607_NUM                         (3U)             /* MCUID0607 Num                                                */
#define CALIB_MCUID0607_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID0607_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID0607_CHN                         (2U)             /* CHN                                                          */
#define CALIB_MCUID3020_NUM                         (2U)             /* MCUID3020 Num                                                */
#define CALIB_MCUID3020_FMVSS                       (0U)             /* FMVSS                                                        */
#define CALIB_MCUID3020_UNR                         (1U)             /* UNR                                                          */
#define CALIB_MCUID0235_NUM                         (9U)             /* MCUID0235 Num                                                */
#define CALIB_MCUID0235_OTHER                       (0U)             /* Without Pickup Truck                                         */
#define CALIB_MCUID0235_PICKUP_TRUCK                (8U)             /* Pickup Truck                                                 */
#define CALIB_MCUID0250_MIN                         (1U)             /* MCUID0250 Min                                                */
#define CALIB_MCUID0250_NO_1                        (1U)             /* CONV: Max No.1                                               */
#define CALIB_MCUID0250_NO_2                        (2U)             /* CONV: Max No.2                                               */
#define CALIB_MCUID0250_NO_3                        (3U)             /* CONV: Max No.3                                               */
#define CALIB_MCUID0250_NO_4                        (4U)             /* CONV: Max No.4                                               */
#define CALIB_MCUID0250_NO_5                        (5U)             /* CONV: Max No.5                                               */
#define CALIB_MCUID0250_NO_6                        (6U)             /* CONV: Max No.6                                               */
#define CALIB_MCUID0250_MAX                         (6U)             /* MCUID0250 Max                                                */
#define CALIB_MCUID0251_MIN                         (1U)             /* MCUID0251 Min                                                */
#define CALIB_MCUID0251_NO_1                        (1U)             /* HV: Max No.1                                                 */
#define CALIB_MCUID0251_NO_2                        (2U)             /* HV: Max No.2                                                 */
#define CALIB_MCUID0251_NO_3                        (3U)             /* HV: Max No.3                                                 */
#define CALIB_MCUID0251_NO_4                        (4U)             /* HV: Max No.4                                                 */
#define CALIB_MCUID0251_NO_5                        (5U)             /* HV: Max No.5                                                 */
#define CALIB_MCUID0251_NO_6                        (6U)             /* HV: Max No.6                                                 */
#define CALIB_MCUID0251_MAX                         (6U)             /* MCUID0251 Max                                                */
#define CALIB_MCUID0252_MIN                         (1U)             /* MCUID0252 Min                                                */
#define CALIB_MCUID0252_NO_1                        (1U)             /* PHV: Max No.1                                                */
#define CALIB_MCUID0252_NO_2                        (2U)             /* PHV: Max No.2                                                */
#define CALIB_MCUID0252_NO_3                        (3U)             /* PHV: Max No.3                                                */
#define CALIB_MCUID0252_NO_4                        (4U)             /* PHV: Max No.4                                                */
#define CALIB_MCUID0252_NO_5                        (5U)             /* PHV: Max No.5                                                */
#define CALIB_MCUID0252_NO_6                        (6U)             /* PHV: Max No.6                                                */
#define CALIB_MCUID0252_MAX                         (6U)             /* MCUID0252 Max                                                */
#define CALIB_MCUID0253_MIN                         (1U)             /* MCUID0253 Min                                                */
#define CALIB_MCUID0253_NO_1                        (1U)             /* FC: Max No.1                                                 */
#define CALIB_MCUID0253_NO_2                        (2U)             /* FC: Max No.2                                                 */
#define CALIB_MCUID0253_NO_3                        (3U)             /* FC: Max No.3                                                 */
#define CALIB_MCUID0253_NO_4                        (4U)             /* FC: Max No.4                                                 */
#define CALIB_MCUID0253_NO_5                        (5U)             /* FC: Max No.5                                                 */
#define CALIB_MCUID0253_NO_6                        (6U)             /* FC: Max No.6                                                 */
#define CALIB_MCUID0253_MAX                         (6U)             /* MCUID0253 Max                                                */
#define CALIB_MCUID0254_MIN                         (1U)             /* MCUID0254 Min                                                */
#define CALIB_MCUID0254_NO_1                        (1U)             /* PHV: Max No.1                                                */
#define CALIB_MCUID0254_NO_2                        (2U)             /* PHV: Max No.2                                                */
#define CALIB_MCUID0254_NO_3                        (3U)             /* PHV: Max No.3                                                */
#define CALIB_MCUID0254_NO_4                        (4U)             /* PHV: Max No.4                                                */
#define CALIB_MCUID0254_NO_5                        (5U)             /* PHV: Max No.5                                                */
#define CALIB_MCUID0254_NO_6                        (6U)             /* PHV: Max No.6                                                */
#define CALIB_MCUID0254_MAX                         (6U)             /* MCUID0254 Max                                                */
#define CALIB_MCUID0255_MIN                         (1U)             /* MCUID0255 Min                                                */
#define CALIB_MCUID0255_NO_1                        (1U)             /* EV: Max No.1                                                 */
#define CALIB_MCUID0255_NO_2                        (2U)             /* EV: Max No.2                                                 */
#define CALIB_MCUID0255_NO_3                        (3U)             /* EV: Max No.3                                                 */
#define CALIB_MCUID0255_NO_4                        (4U)             /* EV: Max No.4                                                 */
#define CALIB_MCUID0255_NO_5                        (5U)             /* EV: Max No.5                                                 */
#define CALIB_MCUID0255_NO_6                        (6U)             /* EV: Max No.6                                                 */
#define CALIB_MCUID0255_MAX                         (6U)             /* MCUID0255 Max                                                */
#define CALIB_MCUID3025_NUM                         (2U)             /* MCUID3025 Num                                                */
#define CALIB_MCUID3025_R_LIT_L_WIP                 (0U)             /* R:LIGHT L:WIPER                                              */
#define CALIB_MCUID3025_R_WIP_L_LIT                 (1U)             /* R:WIPER L:LIGHT                                              */
#define CALIB_MCUID1137_NUM                         (2U)             /* number of FMVSS208                                           */
#define CALIB_MCUID1137_FMVSS208_OTHER              (0U)             /* New FMVSS208 not applied                                     */
#define CALIB_MCUID1137_FMVSS208                    (1U)             /* New FMVSS208 applied                                         */
#define CALIB_SOUND_PRESS_RATE_MIN                  (0U)             /* Sound Pressure Rate MIN MCUID0029-0039,0067-0208,0744-0753   */

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
extern volatile const U1 u1_CALIB_MCUID0024_BRAND;         /* Brand                                                                  */
extern volatile const U1 u1_CALIB_MCUID0025_SPORTS;        /* Sports Switching                                                       */
extern volatile const U1 u1_CALIB_MCUID0209_RRCYM;         /* RRCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0210_RLCYM;         /* RLCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0211_BCTYM;         /* BCTYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0212_LGCYM;         /* LGCYM                                                                  */
extern volatile const U1 u1_CALIB_MCUID0213_HDCY_BDBM;     /* HDCY_BDBM                                                              */
extern volatile const U1 u1_CALIB_MCUID0214_RPSDWARNM;     /* RPSDWARNM                                                              */
extern volatile const U1 u1_CALIB_MCUID0215_LPSDWARNM;     /* LPSDWARNM                                                              */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0030;       /* Reserve_1B_0030                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0031;       /* Reserve_1B_0031                                                        */
extern volatile const U1 u1_CALIB_MCUID0219_G_GAUGE_MAX;   /* G_Gauge MAX                                                            */
extern volatile const U1 u1_CALIB_MCUID0220_GTRAJECTORY2;  /* GTrajectory2                                                           */
extern volatile const U1 u1_CALIB_MCUID0221_G_DISP_MAX;    /* G_Display MAX                                                          */
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
extern volatile const U1 u1_CALIB_MCUID0264_FSPO;          /* Fspo                                                                   */
extern volatile const U1 u1_CALIB_MCUID0268_SWNUM;         /* SWnum                                                                  */
extern volatile const U1 u1_CALIB_MCUID0270_RHEO_MAX;      /* CAN:RHEOSTAT(%):light control is max hold                              */
extern volatile const U1 u1_CALIB_MCUID0271_RHEO_LV1;      /* CAN:RHEOSTAT(%):light control level (1)                                */
extern volatile const U1 u1_CALIB_MCUID0272_RHEO_LV2;      /* CAN:RHEOSTAT(%):light control level (2)                                */
extern volatile const U1 u1_CALIB_MCUID0273_RHEO_LV3;      /* CAN:RHEOSTAT(%):light control level (3)                                */
extern volatile const U1 u1_CALIB_MCUID0274_RHEO_LV4;      /* CAN:RHEOSTAT(%):light control level (4)                                */
extern volatile const U1 u1_CALIB_MCUID0275_RHEO_LV5;      /* CAN:RHEOSTAT(%):light control level (5)                                */
extern volatile const U1 u1_CALIB_MCUID0276_RHEO_LV6;      /* CAN:RHEOSTAT(%):light control level (6)                                */
extern volatile const U1 u1_CALIB_MCUID0277_RHEO_LV7;      /* CAN:RHEOSTAT(%):light control level (7)                                */
extern volatile const U1 u1_CALIB_MCUID0278_RHEO_LV8;      /* CAN:RHEOSTAT(%):light control level (8)                                */
extern volatile const U1 u1_CALIB_MCUID0279_RHEO_LV9;      /* CAN:RHEOSTAT(%):light control level (9)                                */
extern volatile const U1 u1_CALIB_MCUID0280_RHEO_LV10;     /* CAN:RHEOSTAT(%):light control level (10)                               */
extern volatile const U1 u1_CALIB_MCUID0281_RHEO_LV11;     /* CAN:RHEOSTAT(%):light control level (11)                               */
extern volatile const U1 u1_CALIB_MCUID0282_RHEO_LV12;     /* CAN:RHEOSTAT(%):light control level (12)                               */
extern volatile const U1 u1_CALIB_MCUID0283_RHEO_LV13;     /* CAN:RHEOSTAT(%):light control level (13)                               */
extern volatile const U1 u1_CALIB_MCUID0284_RHEO_LV14;     /* CAN:RHEOSTAT(%):light control level (14)                               */
extern volatile const U1 u1_CALIB_MCUID0285_RHEO_LV15;     /* CAN:RHEOSTAT(%):light control level (15)                               */
extern volatile const U1 u1_CALIB_MCUID0286_RHEO_LV16;     /* CAN:RHEOSTAT(%):light control level (16)                               */
extern volatile const U1 u1_CALIB_MCUID0287_RHEO_LV17;     /* CAN:RHEOSTAT(%):light control level (17)                               */
extern volatile const U1 u1_CALIB_MCUID0288_RHEO_LV18;     /* CAN:RHEOSTAT(%):light control level (18)                               */
extern volatile const U1 u1_CALIB_MCUID0289_RHEO_LV19;     /* CAN:RHEOSTAT(%):light control level (19)                               */
extern volatile const U1 u1_CALIB_MCUID0290_RHEO_LV20;     /* CAN:RHEOSTAT(%):light control level (20)                               */
extern volatile const U1 u1_CALIB_MCUID0291_RHEO_MIN;      /* CAN:RHEOSTAT(%): light control is min hold                             */
extern volatile const U1 u1_CALIB_MCUID0336_ILLOF_LV;      /* ILL_OF Level                                                           */
extern volatile const U1 u1_CALIB_MCUID0337_ILLOF_CAN_LV;  /* ILL_OF Cancel Level                                                    */
extern volatile const U1 u1_CALIB_MCUID0340_RHEOPOS_NIGHT; /* Rheostat Position Night                                                */
extern volatile const U1 u1_CALIB_MCUID0341_TAIL;          /* TAIL Apply                                                             */
extern volatile const U1 u1_CALIB_MCUID0342_BL_DAY_MAX;    /* Daytime Back-light control(%):light control is max hold                */
extern volatile const U1 u1_CALIB_MCUID0343_BL_DAY_LV1;    /* Daytime Back-light control(%):light control level (1)                  */
extern volatile const U1 u1_CALIB_MCUID0344_BL_DAY_LV2;    /* Daytime Back-light control(%):light control level (2)                  */
extern volatile const U1 u1_CALIB_MCUID0345_BL_DAY_LV3;    /* Daytime Back-light control(%):light control level (3)                  */
extern volatile const U1 u1_CALIB_MCUID0346_BL_DAY_LV4;    /* Daytime Back-light control(%):light control level (4)                  */
extern volatile const U1 u1_CALIB_MCUID0347_BL_DAY_LV5;    /* Daytime Back-light control(%):light control level (5)                  */
extern volatile const U1 u1_CALIB_MCUID0348_BL_DAY_LV6;    /* Daytime Back-light control(%):light control level (6)                  */
extern volatile const U1 u1_CALIB_MCUID0349_BL_DAY_LV7;    /* Daytime Back-light control(%):light control level (7)                  */
extern volatile const U1 u1_CALIB_MCUID0350_BL_DAY_LV8;    /* Daytime Back-light control(%):light control level (8)                  */
extern volatile const U1 u1_CALIB_MCUID0351_BL_DAY_LV9;    /* Daytime Back-light control(%):light control level (9)                  */
extern volatile const U1 u1_CALIB_MCUID0352_BL_DAY_LV10;   /* Daytime Back-light control(%):light control level (10)                 */
extern volatile const U1 u1_CALIB_MCUID0353_BL_DAY_LV11;   /* Daytime Back-light control(%):light control level (11)                 */
extern volatile const U1 u1_CALIB_MCUID0354_BL_DAY_LV12;   /* Daytime Back-light control(%):light control level (12)                 */
extern volatile const U1 u1_CALIB_MCUID0355_BL_DAY_LV13;   /* Daytime Back-light control(%):light control level (13)                 */
extern volatile const U1 u1_CALIB_MCUID0356_BL_DAY_LV14;   /* Daytime Back-light control(%):light control level (14)                 */
extern volatile const U1 u1_CALIB_MCUID0357_BL_DAY_LV15;   /* Daytime Back-light control(%):light control level (15)                 */
extern volatile const U1 u1_CALIB_MCUID0358_BL_DAY_LV16;   /* Daytime Back-light control(%):light control level (16)                 */
extern volatile const U1 u1_CALIB_MCUID0359_BL_DAY_LV17;   /* Daytime Back-light control(%):light control level (17)                 */
extern volatile const U1 u1_CALIB_MCUID0360_BL_DAY_LV18;   /* Daytime Back-light control(%):light control level (18)                 */
extern volatile const U1 u1_CALIB_MCUID0361_BL_DAY_LV19;   /* Daytime Back-light control(%):light control level (19)                 */
extern volatile const U1 u1_CALIB_MCUID0362_BL_DAY_LV20;   /* Daytime Back-light control(%):light control level (20)                 */
extern volatile const U1 u1_CALIB_MCUID0363_BL_DAY_MIN;    /* Daytime Back-light control(%): light control is min hold               */
extern volatile const U1 u1_CALIB_MCUID0364_RGB_DAY_MAX;   /* Daytime RGB control(%):light control is max hold                       */
extern volatile const U1 u1_CALIB_MCUID0365_RGB_DAY_LV1;   /* Daytime RGB control(%):light control level (1)                         */
extern volatile const U1 u1_CALIB_MCUID0366_RGB_DAY_LV2;   /* Daytime RGB control(%):light control level (2)                         */
extern volatile const U1 u1_CALIB_MCUID0367_RGB_DAY_LV3;   /* Daytime RGB control(%):light control level (3)                         */
extern volatile const U1 u1_CALIB_MCUID0368_RGB_DAY_LV4;   /* Daytime RGB control(%):light control level (4)                         */
extern volatile const U1 u1_CALIB_MCUID0369_RGB_DAY_LV5;   /* Daytime RGB control(%):light control level (5)                         */
extern volatile const U1 u1_CALIB_MCUID0370_RGB_DAY_LV6;   /* Daytime RGB control(%):light control level (6)                         */
extern volatile const U1 u1_CALIB_MCUID0371_RGB_DAY_LV7;   /* Daytime RGB control(%):light control level (7)                         */
extern volatile const U1 u1_CALIB_MCUID0372_RGB_DAY_LV8;   /* Daytime RGB control(%):light control level (8)                         */
extern volatile const U1 u1_CALIB_MCUID0373_RGB_DAY_LV9;   /* Daytime RGB control(%):light control level (9)                         */
extern volatile const U1 u1_CALIB_MCUID0374_RGB_DAY_LV10;  /* Daytime RGB control(%):light control level (10)                        */
extern volatile const U1 u1_CALIB_MCUID0375_RGB_DAY_LV11;  /* Daytime RGB control(%):light control level (11)                        */
extern volatile const U1 u1_CALIB_MCUID0376_RGB_DAY_LV12;  /* Daytime RGB control(%):light control level (12)                        */
extern volatile const U1 u1_CALIB_MCUID0377_RGB_DAY_LV13;  /* Daytime RGB control(%):light control level (13)                        */
extern volatile const U1 u1_CALIB_MCUID0378_RGB_DAY_LV14;  /* Daytime RGB control(%):light control level (14)                        */
extern volatile const U1 u1_CALIB_MCUID0379_RGB_DAY_LV15;  /* Daytime RGB control(%):light control level (15)                        */
extern volatile const U1 u1_CALIB_MCUID0380_RGB_DAY_LV16;  /* Daytime RGB control(%):light control level (16)                        */
extern volatile const U1 u1_CALIB_MCUID0381_RGB_DAY_LV17;  /* Daytime RGB control(%):light control level (17)                        */
extern volatile const U1 u1_CALIB_MCUID0382_RGB_DAY_LV18;  /* Daytime RGB control(%):light control level (18)                        */
extern volatile const U1 u1_CALIB_MCUID0383_RGB_DAY_LV19;  /* Daytime RGB control(%):light control level (19)                        */
extern volatile const U1 u1_CALIB_MCUID0384_RGB_DAY_LV20;  /* Daytime RGB control(%):light control level (20)                        */
extern volatile const U1 u1_CALIB_MCUID0385_RGB_DAY_MIN;   /* Daytime RGB control(%): light control is min hold                      */
extern volatile const U1 u1_CALIB_MCUID0386_BL_NGT_MAX;    /* Nighttime Back-light control(%):light control is max hold              */
extern volatile const U1 u1_CALIB_MCUID0387_BL_NGT_LV1;    /* Nighttime Back-light control(%):light control level (1)                */
extern volatile const U1 u1_CALIB_MCUID0388_BL_NGT_LV2;    /* Nighttime Back-light control(%):light control level (2)                */
extern volatile const U1 u1_CALIB_MCUID0389_BL_NGT_LV3;    /* Nighttime Back-light control(%):light control level (3)                */
extern volatile const U1 u1_CALIB_MCUID0390_BL_NGT_LV4;    /* Nighttime Back-light control(%):light control level (4)                */
extern volatile const U1 u1_CALIB_MCUID0391_BL_NGT_LV5;    /* Nighttime Back-light control(%):light control level (5)                */
extern volatile const U1 u1_CALIB_MCUID0392_BL_NGT_LV6;    /* Nighttime Back-light control(%):light control level (6)                */
extern volatile const U1 u1_CALIB_MCUID0393_BL_NGT_LV7;    /* Nighttime Back-light control(%):light control level (7)                */
extern volatile const U1 u1_CALIB_MCUID0394_BL_NGT_LV8;    /* Nighttime Back-light control(%):light control level (8)                */
extern volatile const U1 u1_CALIB_MCUID0395_BL_NGT_LV9;    /* Nighttime Back-light control(%):light control level (9)                */
extern volatile const U1 u1_CALIB_MCUID0396_BL_NGT_LV10;   /* Nighttime Back-light control(%):light control level (10)               */
extern volatile const U1 u1_CALIB_MCUID0397_BL_NGT_LV11;   /* Nighttime Back-light control(%):light control level (11)               */
extern volatile const U1 u1_CALIB_MCUID0398_BL_NGT_LV12;   /* Nighttime Back-light control(%):light control level (12)               */
extern volatile const U1 u1_CALIB_MCUID0399_BL_NGT_LV13;   /* Nighttime Back-light control(%):light control level (13)               */
extern volatile const U1 u1_CALIB_MCUID0400_BL_NGT_LV14;   /* Nighttime Back-light control(%):light control level (14)               */
extern volatile const U1 u1_CALIB_MCUID0401_BL_NGT_LV15;   /* Nighttime Back-light control(%):light control level (15)               */
extern volatile const U1 u1_CALIB_MCUID0402_BL_NGT_LV16;   /* Nighttime Back-light control(%):light control level (16)               */
extern volatile const U1 u1_CALIB_MCUID0403_BL_NGT_LV17;   /* Nighttime Back-light control(%):light control level (17)               */
extern volatile const U1 u1_CALIB_MCUID0404_BL_NGT_LV18;   /* Nighttime Back-light control(%):light control level (18)               */
extern volatile const U1 u1_CALIB_MCUID0405_BL_NGT_LV19;   /* Nighttime Back-light control(%):light control level (19)               */
extern volatile const U1 u1_CALIB_MCUID0406_BL_NGT_LV20;   /* Nighttime Back-light control(%):light control level (20)               */
extern volatile const U1 u1_CALIB_MCUID0407_BL_NGT_MIN;    /* Nighttime Back-light control(%): light control is min hold             */
extern volatile const U1 u1_CALIB_MCUID0408_RGB_NGT_MAX;   /* Nighttime RGB control(%):light control is max hold                     */
extern volatile const U1 u1_CALIB_MCUID0409_RGB_NGT_LV1;   /* Nighttime RGB control(%):light control level (1)                       */
extern volatile const U1 u1_CALIB_MCUID0410_RGB_NGT_LV2;   /* Nighttime RGB control(%):light control level (2)                       */
extern volatile const U1 u1_CALIB_MCUID0411_RGB_NGT_LV3;   /* Nighttime RGB control(%):light control level (3)                       */
extern volatile const U1 u1_CALIB_MCUID0412_RGB_NGT_LV4;   /* Nighttime RGB control(%):light control level (4)                       */
extern volatile const U1 u1_CALIB_MCUID0413_RGB_NGT_LV5;   /* Nighttime RGB control(%):light control level (5)                       */
extern volatile const U1 u1_CALIB_MCUID0414_RGB_NGT_LV6;   /* Nighttime RGB control(%):light control level (6)                       */
extern volatile const U1 u1_CALIB_MCUID0415_RGB_NGT_LV7;   /* Nighttime RGB control(%):light control level (7)                       */
extern volatile const U1 u1_CALIB_MCUID0416_RGB_NGT_LV8;   /* Nighttime RGB control(%):light control level (8)                       */
extern volatile const U1 u1_CALIB_MCUID0417_RGB_NGT_LV9;   /* Nighttime RGB control(%):light control level (9)                       */
extern volatile const U1 u1_CALIB_MCUID0418_RGB_NGT_LV10;  /* Nighttime RGB control(%):light control level (10)                      */
extern volatile const U1 u1_CALIB_MCUID0419_RGB_NGT_LV11;  /* Nighttime RGB control(%):light control level (11)                      */
extern volatile const U1 u1_CALIB_MCUID0420_RGB_NGT_LV12;  /* Nighttime RGB control(%):light control level (12)                      */
extern volatile const U1 u1_CALIB_MCUID0421_RGB_NGT_LV13;  /* Nighttime RGB control(%):light control level (13)                      */
extern volatile const U1 u1_CALIB_MCUID0422_RGB_NGT_LV14;  /* Nighttime RGB control(%):light control level (14)                      */
extern volatile const U1 u1_CALIB_MCUID0423_RGB_NGT_LV15;  /* Nighttime RGB control(%):light control level (15)                      */
extern volatile const U1 u1_CALIB_MCUID0424_RGB_NGT_LV16;  /* Nighttime RGB control(%):light control level (16)                      */
extern volatile const U1 u1_CALIB_MCUID0425_RGB_NGT_LV17;  /* Nighttime RGB control(%):light control level (17)                      */
extern volatile const U1 u1_CALIB_MCUID0426_RGB_NGT_LV18;  /* Nighttime RGB control(%):light control level (18)                      */
extern volatile const U1 u1_CALIB_MCUID0427_RGB_NGT_LV19;  /* Nighttime RGB control(%):light control level (19)                      */
extern volatile const U1 u1_CALIB_MCUID0428_RGB_NGT_LV20;  /* Nighttime RGB control(%):light control level (20)                      */
extern volatile const U1 u1_CALIB_MCUID0429_RGB_NGT_MIN;   /* Nighttime RGB control(%): light control is min hold                    */
extern volatile const U1 u1_CALIB_MCUID0430_RHEOSW;        /* Rheostat SW Apply                                                      */
extern volatile const U1 u1_CALIB_MCUID0590_SOC_PORTPOS;   /* SOC Port Position                                                      */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0175;       /* Reserve_1B_0175                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0176;       /* Reserve_1B_0176                                                        */
extern volatile const U1 u1_CALIB_MCUID0604_SBELT_MEXICO;  /* SeatBelt Regulation MEXICO                                             */
extern volatile const U1 u1_CALIB_MCUID0605_SBELT_EU;      /* SeatBelt Regulation EU                                                 */
extern volatile const U1 u1_CALIB_MCUID0606_SBELT_KOREA;   /* SeatBelt Regulation KOREA                                              */
extern volatile const U1 u1_CALIB_MCUID0607_SBELT_CHINA;   /* SeatBelt Regulation CHINA                                              */
extern volatile const U1 u1_CALIB_MCUID0741_IL2OUTILLRUN;  /* IL2OUTILLRun                                                           */
extern volatile const U1 u1_CALIB_MCUID0798_TRNLMPCLR;     /* Turn signal lamp color of your vehicle                                 */
extern volatile const U1 u1_CALIB_MCUID0809_MEXICO_LOW;    /* Mexico lows and regulations                                            */
extern volatile const U1 u1_CALIB_MCUID0810_KOREA_LOW;     /* Korea lows and regulations                                             */
extern volatile const U1 u1_CALIB_MCUID3020_GEN_LOW;       /* Regulations requiring compliance for General Transportation            */
extern volatile const U1 u1_CALIB_MCUID3025_COMB_SW_POS;   /* Combination switch position                                            */
extern volatile const U1 u1_CALIB_MCUID0933_FUECO_UNIT_1;  /* Judgment country 1 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0934_FUECO_UNIT_2;  /* Judgment country 2 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0935_FUECO_UNIT_3;  /* Judgment country 3 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0936_FUECO_UNIT_4;  /* Judgment country 4 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0937_FUECO_UNIT_5;  /* Judgment country 5 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0938_FUECO_UNIT_6;  /* Judgment country 6 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0939_FUECO_UNIT_7;  /* Judgment country 7 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0940_FUECO_UNIT_8;  /* Judgment country 8 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0941_FUECO_UNIT_9;  /* Judgment country 9 Fuel economy unit                                   */
extern volatile const U1 u1_CALIB_MCUID0942_FUECO_UNIT_10; /* Judgment country 10 Fuel economy unit                                  */
extern volatile const U1 u1_CALIB_MCUID0943_UNIT_SW_1;     /* Judgment country 1 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0944_UNIT_SW_2;     /* Judgment country 2 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0945_UNIT_SW_3;     /* Judgment country 3 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0946_UNIT_SW_4;     /* Judgment country 4 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0947_UNIT_SW_5;     /* Judgment country 5 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0948_UNIT_SW_6;     /* Judgment country 6 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0949_UNIT_SW_7;     /* Judgment country 7 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0950_UNIT_SW_8;     /* Judgment country 8 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0951_UNIT_SW_9;     /* Judgment country 9 unit switching                                      */
extern volatile const U1 u1_CALIB_MCUID0952_UNIT_SW_10;    /* Judgment country 10 unit switching                                     */
extern volatile const U1 u1_CALIB_MCUID0953_BUZ_REV_1;     /* Judgment country 1 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0954_BUZ_REV_2;     /* Judgment country 2 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0955_BUZ_REV_3;     /* Judgment country 3 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0956_BUZ_REV_4;     /* Judgment country 4 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0957_BUZ_REV_5;     /* Judgment country 5 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0958_BUZ_REV_6;     /* Judgment country 6 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0959_BUZ_REV_7;     /* Judgment country 7 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0960_BUZ_REV_8;     /* Judgment country 8 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0961_BUZ_REV_9;     /* Judgment country 9 Buzzer (reverse buzzer)                             */
extern volatile const U1 u1_CALIB_MCUID0962_BUZ_REV_10;    /* Judgment country 10 Buzzer (reverse buzzer)                            */
extern volatile const U1 u1_CALIB_MCUID0963_BUZ_GSO_1;     /* Judgment country 1 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0964_BUZ_GSO_2;     /* Judgment country 2 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0965_BUZ_GSO_3;     /* Judgment country 3 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0966_BUZ_GSO_4;     /* Judgment country 4 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0967_BUZ_GSO_5;     /* Judgment country 5 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0968_BUZ_GSO_6;     /* Judgment country 6 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0969_BUZ_GSO_7;     /* Judgment country 7 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0970_BUZ_GSO_8;     /* Judgment country 8 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0971_BUZ_GSO_9;     /* Judgment country 9 Regulation Buzzer/warning (GSO)                     */
extern volatile const U1 u1_CALIB_MCUID0972_BUZ_GSO_10;    /* Judgment country 10 Regulation Buzzer/warning (GSO)                    */
extern volatile const U1 u1_CALIB_MCUID0973_BUZ_AIS_1;     /* Judgment country 1 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0974_BUZ_AIS_2;     /* Judgment country 2 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0975_BUZ_AIS_3;     /* Judgment country 3 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0976_BUZ_AIS_4;     /* Judgment country 4 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0977_BUZ_AIS_5;     /* Judgment country 5 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0978_BUZ_AIS_6;     /* Judgment country 6 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0979_BUZ_AIS_7;     /* Judgment country 7 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0980_BUZ_AIS_8;     /* Judgment country 8 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0981_BUZ_AIS_9;     /* Judgment country 9 Regulation Buzzer (AIS)                             */
extern volatile const U1 u1_CALIB_MCUID0982_BUZ_AIS_10;    /* Judgment country 10 Regulation Buzzer (AIS)                            */
extern volatile const U1 u1_CALIB_MCUID0983_BUZ_NOT_1;     /* Judgment country 1 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0984_BUZ_NOT_2;     /* Judgment country 2 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0985_BUZ_NOT_3;     /* Judgment country 3 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0986_BUZ_NOT_4;     /* Judgment country 4 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0987_BUZ_NOT_5;     /* Judgment country 5 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0988_BUZ_NOT_6;     /* Judgment country 6 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0989_BUZ_NOT_7;     /* Judgment country 7 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0990_BUZ_NOT_8;     /* Judgment country 8 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0991_BUZ_NOT_9;     /* Judgment country 9 Regulation Buzzer (Notification)                    */
extern volatile const U1 u1_CALIB_MCUID0992_BUZ_NOT_10;    /* Judgment country 10 Regulation Buzzer (Notification)                   */
extern volatile const U1 u1_CALIB_MCUID0993_SP_UNIT_1;     /* Judgment country 1 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0994_SP_UNIT_2;     /* Judgment country 2 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0995_SP_UNIT_3;     /* Judgment country 3 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0996_SP_UNIT_4;     /* Judgment country 4 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0997_SP_UNIT_5;     /* Judgment country 5 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0998_SP_UNIT_6;     /* Judgment country 6 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID0999_SP_UNIT_7;     /* Judgment country 7 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID1000_SP_UNIT_8;     /* Judgment country 8 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID1001_SP_UNIT_9;     /* Judgment country 9 Speed Reg Speed Unit                                */
extern volatile const U1 u1_CALIB_MCUID1002_SP_UNIT_10;    /* Judgment country 10 Speed Reg Speed Unit                               */
extern volatile const U1 u1_CALIB_MCUID1003_SPUN_MSSW_1;   /* Judgment country 1 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1004_SPUN_MSSW_2;   /* Judgment country 2 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1005_SPUN_MSSW_3;   /* Judgment country 3 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1006_SPUN_MSSW_4;   /* Judgment country 4 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1007_SPUN_MSSW_5;   /* Judgment country 5 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1008_SPUN_MSSW_6;   /* Judgment country 6 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1009_SPUN_MSSW_7;   /* Judgment country 7 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1010_SPUN_MSSW_8;   /* Judgment country 8 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1011_SPUN_MSSW_9;   /* Judgment country 9 Speed Reg Veh Speed Unit W/O Main/Sub Sw            */
extern volatile const U1 u1_CALIB_MCUID1012_SPUN_MSSW_10;  /* Judgment country 10 Speed Reg Veh Speed Unit W/O Main/Sub Sw           */
extern volatile const U1 u1_CALIB_MCUID1013_SUB_SP_DIS_1;  /* Judgment country 1 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1014_SUB_SP_DIS_2;  /* Judgment country 2 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1015_SUB_SP_DIS_3;  /* Judgment country 3 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1016_SUB_SP_DIS_4;  /* Judgment country 4 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1017_SUB_SP_DIS_5;  /* Judgment country 5 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1018_SUB_SP_DIS_6;  /* Judgment country 6 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1019_SUB_SP_DIS_7;  /* Judgment country 7 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1020_SUB_SP_DIS_8;  /* Judgment country 8 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1021_SUB_SP_DIS_9;  /* Judgment country 9 Speed Reg Sub Speed Display                         */
extern volatile const U1 u1_CALIB_MCUID1022_SUB_SP_DIS_10; /* Judgment country 10 Speed Reg Sub Speed Display                        */
extern volatile const U1 u1_CALIB_MCUID1023_SP_TOL_1;      /* Judgment country 1 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1024_SP_TOL_2;      /* Judgment country 2 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1025_SP_TOL_3;      /* Judgment country 3 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1026_SP_TOL_4;      /* Judgment country 4 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1027_SP_TOL_5;      /* Judgment country 5 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1028_SP_TOL_6;      /* Judgment country 6 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1029_SP_TOL_7;      /* Judgment country 7 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1030_SP_TOL_8;      /* Judgment country 8 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1031_SP_TOL_9;      /* Judgment country 9 Speed Reg Veh Speed Tol                             */
extern volatile const U1 u1_CALIB_MCUID1032_SP_TOL_10;     /* Judgment country 10 Speed Reg Veh Speed Tol                            */
extern volatile const U1 u1_CALIB_MCUID1033_CH_REG_GB_1;   /* Judgment country 1 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1034_CH_REG_GB_2;   /* Judgment country 2 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1035_CH_REG_GB_3;   /* Judgment country 3 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1036_CH_REG_GB_4;   /* Judgment country 4 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1037_CH_REG_GB_5;   /* Judgment country 5 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1038_CH_REG_GB_6;   /* Judgment country 6 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1039_CH_REG_GB_7;   /* Judgment country 7 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1040_CH_REG_GB_8;   /* Judgment country 8 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1041_CH_REG_GB_9;   /* Judgment country 9 China unique regulation (GB)                        */
extern volatile const U1 u1_CALIB_MCUID1042_CH_REG_GB_10;  /* Judgment country 10 China unique regulation (GB)                       */
extern volatile const U1 u1_CALIB_MCUID1043_FMV_BRATT_1;   /* Judgment country 1 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1044_FMV_BRATT_2;   /* Judgment country 2 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1045_FMV_BRATT_3;   /* Judgment country 3 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1046_FMV_BRATT_4;   /* Judgment country 4 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1047_FMV_BRATT_5;   /* Judgment country 5 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1048_FMV_BRATT_6;   /* Judgment country 6 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1049_FMV_BRATT_7;   /* Judgment country 7 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1050_FMV_BRATT_8;   /* Judgment country 8 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1051_FMV_BRATT_9;   /* Judgment country 9 Regulation (FMVSS) BRAKE telltale                   */
extern volatile const U1 u1_CALIB_MCUID1052_FMV_BRATT_10;  /* Judgment country 10 Regulation (FMVSS) BRAKE telltale                  */
extern volatile const U1 u1_CALIB_MCUID1053_FMV_ABSTT_1;   /* Judgment country 1 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1054_FMV_ABSTT_2;   /* Judgment country 2 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1055_FMV_ABSTT_3;   /* Judgment country 3 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1056_FMV_ABSTT_4;   /* Judgment country 4 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1057_FMV_ABSTT_5;   /* Judgment country 5 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1058_FMV_ABSTT_6;   /* Judgment country 6 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1059_FMV_ABSTT_7;   /* Judgment country 7 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1060_FMV_ABSTT_8;   /* Judgment country 8 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1061_FMV_ABSTT_9;   /* Judgment country 9 Regulation (FMVSS) ABS telltale                     */
extern volatile const U1 u1_CALIB_MCUID1062_FMV_ABSTT_10;  /* Judgment country 10 Regulation (FMVSS) ABS telltale                    */
extern volatile const U1 u1_CALIB_MCUID1063_FMV_EPTT_1;    /* Judgment country 1 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1064_FMV_EPTT_2;    /* Judgment country 2 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1065_FMV_EPTT_3;    /* Judgment country 3 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1066_FMV_EPTT_4;    /* Judgment country 4 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1067_FMV_EPTT_5;    /* Judgment country 5 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1068_FMV_EPTT_6;    /* Judgment country 6 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1069_FMV_EPTT_7;    /* Judgment country 7 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1070_FMV_EPTT_8;    /* Judgment country 8 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1071_FMV_EPTT_9;    /* Judgment country 9 Regulation (FMVSS) EPB/PKB telltale                 */
extern volatile const U1 u1_CALIB_MCUID1072_FMV_EPTT_10;   /* Judgment country 10 Regulation (FMVSS) EPB/PKB telltale                */
extern volatile const U1 u1_CALIB_MCUID1073_FMV_THTT_1;    /* Judgment country 1 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1074_FMV_THTT_2;    /* Judgment country 2 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1075_FMV_THTT_3;    /* Judgment country 3 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1076_FMV_THTT_4;    /* Judgment country 4 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1077_FMV_THTT_5;    /* Judgment country 5 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1078_FMV_THTT_6;    /* Judgment country 6 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1079_FMV_THTT_7;    /* Judgment country 7 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1080_FMV_THTT_8;    /* Judgment country 8 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1081_FMV_THTT_9;    /* Judgment country 9 Regulation (FMVSS) TAIL/HEAD telltale               */
extern volatile const U1 u1_CALIB_MCUID1082_FMV_THTT_10;   /* Judgment country 10 Regulation (FMVSS) TAIL/HEAD telltale              */
extern volatile const U1 u1_CALIB_MCUID1093_BUZ_BELT_1;    /* Judgment country 1 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1094_BUZ_BELT_2;    /* Judgment country 2 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1095_BUZ_BELT_3;    /* Judgment country 3 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1096_BUZ_BELT_4;    /* Judgment country 4 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1097_BUZ_BELT_5;    /* Judgment country 5 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1098_BUZ_BELT_6;    /* Judgment country 6 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1099_BUZ_BELT_7;    /* Judgment country 7 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1100_BUZ_BELT_8;    /* Judgment country 8 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1101_BUZ_BELT_9;    /* Judgment country 9 Regulation Buzzer/IND (Belt reminder)               */
extern volatile const U1 u1_CALIB_MCUID1102_BUZ_BELT_10;   /* Judgment country 10 Regulation Buzzer/IND (Belt reminder)              */
extern volatile const U1 u1_CALIB_MCUID1103_JUDG_RES_1;    /* Judgment result 1                                                      */
extern volatile const U1 u1_CALIB_MCUID1104_JUDG_RES_2;    /* Judgment result 2                                                      */
extern volatile const U1 u1_CALIB_MCUID1105_JUDG_RES_3;    /* Judgment result 3                                                      */
extern volatile const U1 u1_CALIB_MCUID1106_JUDG_RES_4;    /* Judgment result 4                                                      */
extern volatile const U1 u1_CALIB_MCUID1107_JUDG_RES_5;    /* Judgment result 5                                                      */
extern volatile const U1 u1_CALIB_MCUID1108_JUDG_RES_6;    /* Judgment result 6                                                      */
extern volatile const U1 u1_CALIB_MCUID1109_JUDG_RES_7;    /* Judgment result 7                                                      */
extern volatile const U1 u1_CALIB_MCUID1110_JUDG_RES_8;    /* Judgment result 8                                                      */
extern volatile const U1 u1_CALIB_MCUID1111_JUDG_RES_9;    /* Judgment result 9                                                      */
extern volatile const U1 u1_CALIB_MCUID1112_JUDG_RES_10;   /* Judgment result 10                                                     */
extern volatile const U1 u1_CALIB_MCUID1135_SBELT_USA;     /* SeatBelt Regulation USA                                                */
extern volatile const U1 u1_CALIB_MCUID1136_SBELT_CAN;     /* SeatBelt Regulation CAN                                                */
extern volatile const U1 u1_CALIB_MCUID1137_NEW_FMVSS208;  /* New FMVSS applied or not                                               */
extern volatile const U1 u1_CALIB_MCUID1138_SBR_TT_TYPE;   /* SeatBelt Reminder Telltale Type                                        */
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
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0372;       /* Reserve_1B-0372                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0373;       /* Reserve_1B-0373                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0374;       /* Reserve_1B-0374                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0375;       /* Reserve_1B-0375                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0376;       /* Reserve_1B-0376                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0377;       /* Reserve_1B-0377                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0378;       /* Reserve_1B-0378                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0379;       /* Reserve_1B-0379                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0380;       /* Reserve_1B-0380                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0381;       /* Reserve_1B-0381                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0382;       /* Reserve_1B-0382                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0383;       /* Reserve_1B-0383                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0384;       /* Reserve_1B-0384                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0385;       /* Reserve_1B-0385                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0386;       /* Reserve_1B-0386                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0387;       /* Reserve_1B-0387                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0388;       /* Reserve_1B-0388                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0389;       /* Reserve_1B-0389                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0390;       /* Reserve_1B-0390                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0391;       /* Reserve_1B-0391                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0392;       /* Reserve_1B-0392                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0393;       /* Reserve_1B-0393                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0394;       /* Reserve_1B-0394                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0395;       /* Reserve_1B-0395                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0396;       /* Reserve_1B-0396                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0397;       /* Reserve_1B-0397                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0398;       /* Reserve_1B-0398                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0399;       /* Reserve_1B-0399                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0400;       /* Reserve_1B-0400                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0401;       /* Reserve_1B-0401                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0402;       /* Reserve_1B-0402                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0403;       /* Reserve_1B-0403                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0404;       /* Reserve_1B-0404                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0405;       /* Reserve_1B-0405                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0406;       /* Reserve_1B-0406                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0407;       /* Reserve_1B-0407                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0408;       /* Reserve_1B-0408                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0409;       /* Reserve_1B-0409                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0410;       /* Reserve_1B-0410                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0411;       /* Reserve_1B-0411                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0412;       /* Reserve_1B-0412                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0413;       /* Reserve_1B-0413                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0414;       /* Reserve_1B-0414                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0415;       /* Reserve_1B-0415                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0416;       /* Reserve_1B-0416                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0417;       /* Reserve_1B-0417                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0418;       /* Reserve_1B-0418                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0419;       /* Reserve_1B-0419                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0420;       /* Reserve_1B-0420                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0421;       /* Reserve_1B-0421                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0422;       /* Reserve_1B-0422                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0423;       /* Reserve_1B-0423                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0424;       /* Reserve_1B-0424                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0425;       /* Reserve_1B-0425                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0426;       /* Reserve_1B-0426                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0427;       /* Reserve_1B-0427                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0428;       /* Reserve_1B-0428                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0429;       /* Reserve_1B-0429                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0430;       /* Reserve_1B-0430                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0431;       /* Reserve_1B-0431                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0432;       /* Reserve_1B-0432                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0433;       /* Reserve_1B-0433                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0434;       /* Reserve_1B-0434                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0435;       /* Reserve_1B-0435                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0436;       /* Reserve_1B-0436                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0437;       /* Reserve_1B-0437                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0438;       /* Reserve_1B-0438                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0439;       /* Reserve_1B-0439                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0440;       /* Reserve_1B-0440                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0441;       /* Reserve_1B-0441                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0442;       /* Reserve_1B-0442                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0443;       /* Reserve_1B-0443                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0444;       /* Reserve_1B-0444                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0445;       /* Reserve_1B-0445                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0446;       /* Reserve_1B-0446                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0447;       /* Reserve_1B-0447                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0448;       /* Reserve_1B-0448                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0449;       /* Reserve_1B-0449                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0450;       /* Reserve_1B-0450                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0451;       /* Reserve_1B-0451                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0452;       /* Reserve_1B-0452                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0453;       /* Reserve_1B-0453                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0454;       /* Reserve_1B-0454                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0455;       /* Reserve_1B-0455                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0456;       /* Reserve_1B-0456                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0457;       /* Reserve_1B-0457                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0458;       /* Reserve_1B-0458                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0459;       /* Reserve_1B-0459                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0460;       /* Reserve_1B-0460                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0461;       /* Reserve_1B-0461                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0462;       /* Reserve_1B-0462                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0463;       /* Reserve_1B-0463                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0464;       /* Reserve_1B-0464                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0465;       /* Reserve_1B-0465                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0466;       /* Reserve_1B-0466                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0467;       /* Reserve_1B-0467                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0468;       /* Reserve_1B-0468                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0469;       /* Reserve_1B-0469                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0470;       /* Reserve_1B-0470                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0471;       /* Reserve_1B-0471                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0472;       /* Reserve_1B-0472                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0473;       /* Reserve_1B-0473                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0474;       /* Reserve_1B-0474                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0475;       /* Reserve_1B-0475                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0476;       /* Reserve_1B-0476                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0477;       /* Reserve_1B-0477                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0478;       /* Reserve_1B-0478                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0479;       /* Reserve_1B-0479                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0480;       /* Reserve_1B-0480                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0481;       /* Reserve_1B-0481                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0482;       /* Reserve_1B-0482                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0483;       /* Reserve_1B-0483                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0484;       /* Reserve_1B-0484                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0485;       /* Reserve_1B-0485                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0486;       /* Reserve_1B-0486                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0487;       /* Reserve_1B-0487                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0488;       /* Reserve_1B-0488                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0489;       /* Reserve_1B-0489                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0490;       /* Reserve_1B-0490                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0491;       /* Reserve_1B-0491                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0492;       /* Reserve_1B-0492                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0493;       /* Reserve_1B-0493                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0494;       /* Reserve_1B-0494                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0495;       /* Reserve_1B-0495                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0496;       /* Reserve_1B-0496                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0497;       /* Reserve_1B-0497                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0498;       /* Reserve_1B-0498                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0499;       /* Reserve_1B-0499                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0500;       /* Reserve_1B-0500                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0501;       /* Reserve_1B-0501                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0502;       /* Reserve_1B-0502                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0503;       /* Reserve_1B-0503                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0504;       /* Reserve_1B-0504                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0505;       /* Reserve_1B-0505                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0506;       /* Reserve_1B-0506                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0507;       /* Reserve_1B-0507                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0508;       /* Reserve_1B-0508                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0509;       /* Reserve_1B-0509                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0510;       /* Reserve_1B-0510                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0511;       /* Reserve_1B-0511                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0512;       /* Reserve_1B-0512                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0513;       /* Reserve_1B-0513                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0514;       /* Reserve_1B-0514                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0515;       /* Reserve_1B-0515                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0516;       /* Reserve_1B-0516                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0517;       /* Reserve_1B-0517                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0518;       /* Reserve_1B-0518                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0519;       /* Reserve_1B-0519                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0520;       /* Reserve_1B-0520                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0521;       /* Reserve_1B-0521                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0522;       /* Reserve_1B-0522                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0523;       /* Reserve_1B-0523                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0524;       /* Reserve_1B-0524                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0525;       /* Reserve_1B-0525                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0526;       /* Reserve_1B-0526                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0527;       /* Reserve_1B-0527                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0528;       /* Reserve_1B-0528                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0529;       /* Reserve_1B-0529                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0530;       /* Reserve_1B-0530                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0531;       /* Reserve_1B-0531                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0532;       /* Reserve_1B-0532                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0533;       /* Reserve_1B-0533                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0534;       /* Reserve_1B-0534                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0535;       /* Reserve_1B-0535                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0536;       /* Reserve_1B-0536                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0537;       /* Reserve_1B-0537                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0538;       /* Reserve_1B-0538                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0539;       /* Reserve_1B-0539                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0540;       /* Reserve_1B-0540                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0541;       /* Reserve_1B-0541                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0542;       /* Reserve_1B-0542                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0543;       /* Reserve_1B-0543                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0544;       /* Reserve_1B-0544                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0545;       /* Reserve_1B-0545                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0546;       /* Reserve_1B-0546                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0547;       /* Reserve_1B-0547                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0548;       /* Reserve_1B-0548                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0549;       /* Reserve_1B-0549                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0550;       /* Reserve_1B-0550                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0551;       /* Reserve_1B-0551                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0552;       /* Reserve_1B-0552                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0553;       /* Reserve_1B-0553                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0554;       /* Reserve_1B-0554                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0555;       /* Reserve_1B-0555                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0556;       /* Reserve_1B-0556                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0557;       /* Reserve_1B-0557                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0558;       /* Reserve_1B-0558                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0559;       /* Reserve_1B-0559                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0560;       /* Reserve_1B-0560                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0561;       /* Reserve_1B-0561                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0562;       /* Reserve_1B-0562                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0563;       /* Reserve_1B-0563                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0564;       /* Reserve_1B-0564                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0565;       /* Reserve_1B-0565                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0566;       /* Reserve_1B-0566                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0567;       /* Reserve_1B-0567                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0568;       /* Reserve_1B-0568                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0569;       /* Reserve_1B-0569                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0570;       /* Reserve_1B-0570                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0571;       /* Reserve_1B-0571                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0572;       /* Reserve_1B-0572                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0573;       /* Reserve_1B-0573                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0574;       /* Reserve_1B-0574                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0575;       /* Reserve_1B-0575                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0576;       /* Reserve_1B-0576                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0577;       /* Reserve_1B-0577                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0578;       /* Reserve_1B-0578                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0579;       /* Reserve_1B-0579                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0580;       /* Reserve_1B-0580                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0581;       /* Reserve_1B-0581                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0582;       /* Reserve_1B-0582                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0583;       /* Reserve_1B-0583                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0584;       /* Reserve_1B-0584                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0585;       /* Reserve_1B-0585                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0586;       /* Reserve_1B-0586                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0587;       /* Reserve_1B-0587                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0588;       /* Reserve_1B-0588                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0589;       /* Reserve_1B-0589                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0590;       /* Reserve_1B-0590                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0591;       /* Reserve_1B-0591                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0592;       /* Reserve_1B-0592                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0593;       /* Reserve_1B-0593                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0594;       /* Reserve_1B-0594                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0595;       /* Reserve_1B-0595                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0596;       /* Reserve_1B-0596                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0597;       /* Reserve_1B-0597                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0598;       /* Reserve_1B-0598                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0599;       /* Reserve_1B-0599                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0600;       /* Reserve_1B-0600                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0601;       /* Reserve_1B-0601                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0602;       /* Reserve_1B-0602                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0603;       /* Reserve_1B-0603                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0604;       /* Reserve_1B-0604                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0605;       /* Reserve_1B-0605                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0606;       /* Reserve_1B-0606                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0607;       /* Reserve_1B-0607                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0608;       /* Reserve_1B-0608                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0609;       /* Reserve_1B-0609                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0610;       /* Reserve_1B-0610                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0611;       /* Reserve_1B-0611                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0612;       /* Reserve_1B-0612                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0613;       /* Reserve_1B-0613                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0614;       /* Reserve_1B-0614                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0615;       /* Reserve_1B-0615                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0616;       /* Reserve_1B-0616                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0617;       /* Reserve_1B-0617                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0618;       /* Reserve_1B-0618                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0619;       /* Reserve_1B-0619                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0620;       /* Reserve_1B-0620                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0621;       /* Reserve_1B-0621                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0622;       /* Reserve_1B-0622                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0623;       /* Reserve_1B-0623                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0624;       /* Reserve_1B-0624                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0625;       /* Reserve_1B-0625                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0626;       /* Reserve_1B-0626                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0627;       /* Reserve_1B-0627                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0628;       /* Reserve_1B-0628                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0629;       /* Reserve_1B-0629                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0630;       /* Reserve_1B-0630                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0631;       /* Reserve_1B-0631                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0632;       /* Reserve_1B-0632                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0633;       /* Reserve_1B-0633                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0634;       /* Reserve_1B-0634                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0635;       /* Reserve_1B-0635                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0636;       /* Reserve_1B-0636                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0637;       /* Reserve_1B-0637                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0638;       /* Reserve_1B-0638                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0639;       /* Reserve_1B-0639                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0640;       /* Reserve_1B-0640                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0641;       /* Reserve_1B-0641                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0642;       /* Reserve_1B-0642                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0643;       /* Reserve_1B-0643                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0644;       /* Reserve_1B-0644                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0645;       /* Reserve_1B-0645                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0646;       /* Reserve_1B-0646                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0647;       /* Reserve_1B-0647                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0648;       /* Reserve_1B-0648                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0649;       /* Reserve_1B-0649                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0650;       /* Reserve_1B-0650                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0651;       /* Reserve_1B-0651                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0652;       /* Reserve_1B-0652                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0653;       /* Reserve_1B-0653                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0654;       /* Reserve_1B-0654                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0655;       /* Reserve_1B-0655                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0656;       /* Reserve_1B-0656                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0657;       /* Reserve_1B-0657                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0658;       /* Reserve_1B-0658                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0659;       /* Reserve_1B-0659                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0660;       /* Reserve_1B-0660                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0661;       /* Reserve_1B-0661                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0662;       /* Reserve_1B-0662                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0663;       /* Reserve_1B-0663                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0664;       /* Reserve_1B-0664                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0665;       /* Reserve_1B-0665                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0666;       /* Reserve_1B-0666                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0667;       /* Reserve_1B-0667                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0668;       /* Reserve_1B-0668                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0669;       /* Reserve_1B-0669                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0670;       /* Reserve_1B-0670                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0671;       /* Reserve_1B-0671                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0672;       /* Reserve_1B-0672                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0673;       /* Reserve_1B-0673                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0674;       /* Reserve_1B-0674                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0675;       /* Reserve_1B-0675                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0676;       /* Reserve_1B-0676                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0677;       /* Reserve_1B-0677                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0678;       /* Reserve_1B-0678                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0679;       /* Reserve_1B-0679                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0680;       /* Reserve_1B-0680                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0681;       /* Reserve_1B-0681                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0682;       /* Reserve_1B-0682                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0683;       /* Reserve_1B-0683                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0684;       /* Reserve_1B-0684                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0685;       /* Reserve_1B-0685                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0686;       /* Reserve_1B-0686                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0687;       /* Reserve_1B-0687                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0688;       /* Reserve_1B-0688                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0689;       /* Reserve_1B-0689                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0690;       /* Reserve_1B-0690                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0691;       /* Reserve_1B-0691                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0692;       /* Reserve_1B-0692                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0693;       /* Reserve_1B-0693                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0694;       /* Reserve_1B-0694                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0695;       /* Reserve_1B-0695                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0696;       /* Reserve_1B-0696                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0697;       /* Reserve_1B-0697                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0698;       /* Reserve_1B-0698                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0699;       /* Reserve_1B-0699                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0700;       /* Reserve_1B-0700                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0701;       /* Reserve_1B-0701                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0702;       /* Reserve_1B-0702                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0703;       /* Reserve_1B-0703                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0704;       /* Reserve_1B-0704                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0705;       /* Reserve_1B-0705                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0706;       /* Reserve_1B-0706                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0707;       /* Reserve_1B-0707                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0708;       /* Reserve_1B-0708                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0709;       /* Reserve_1B-0709                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0710;       /* Reserve_1B-0710                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0711;       /* Reserve_1B-0711                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0712;       /* Reserve_1B-0712                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0713;       /* Reserve_1B-0713                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0714;       /* Reserve_1B-0714                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0715;       /* Reserve_1B-0715                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0716;       /* Reserve_1B-0716                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0717;       /* Reserve_1B-0717                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0718;       /* Reserve_1B-0718                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0719;       /* Reserve_1B-0719                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0720;       /* Reserve_1B-0720                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0721;       /* Reserve_1B-0721                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0722;       /* Reserve_1B-0722                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0723;       /* Reserve_1B-0723                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0724;       /* Reserve_1B-0724                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0725;       /* Reserve_1B-0725                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0726;       /* Reserve_1B-0726                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0727;       /* Reserve_1B-0727                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0728;       /* Reserve_1B-0728                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0729;       /* Reserve_1B-0729                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0730;       /* Reserve_1B-0730                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0731;       /* Reserve_1B-0731                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0732;       /* Reserve_1B-0732                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0733;       /* Reserve_1B-0733                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0734;       /* Reserve_1B-0734                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0735;       /* Reserve_1B-0735                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0736;       /* Reserve_1B-0736                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0737;       /* Reserve_1B-0737                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0738;       /* Reserve_1B-0738                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0739;       /* Reserve_1B-0739                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0740;       /* Reserve_1B-0740                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0741;       /* Reserve_1B-0741                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0742;       /* Reserve_1B-0742                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0743;       /* Reserve_1B-0743                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0744;       /* Reserve_1B-0744                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0745;       /* Reserve_1B-0745                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0746;       /* Reserve_1B-0746                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0747;       /* Reserve_1B-0747                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0748;       /* Reserve_1B-0748                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0749;       /* Reserve_1B-0749                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0750;       /* Reserve_1B-0750                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0751;       /* Reserve_1B-0751                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0752;       /* Reserve_1B-0752                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0753;       /* Reserve_1B-0753                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0754;       /* Reserve_1B-0754                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0755;       /* Reserve_1B-0755                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0756;       /* Reserve_1B-0756                                                        */
extern volatile const U1 u1_CALIB_MCUID0797_CNST_WRITEFLG; /* Constant write flag                                                    */

extern volatile const U2 u2_CALIB_MCUID3002_ANUNC_MID;     /* Basic 7 Tones Reporting Tone Medium                                    */
extern volatile const U2 u2_CALIB_MCUID3003_ANUNC_SP_MID;  /* Basic 7 Tones Reporting Tone (Special) Medium                          */
extern volatile const U2 u2_CALIB_MCUID3004_RECEP_MID;     /* Basic 7 tones Reception tone Medium                                    */
extern volatile const U2 u2_CALIB_MCUID3005_REJECT_MID;    /* Basic 7 tones Reject tone Medium                                       */
extern volatile const U2 u2_CALIB_MCUID3006_URGEN_MIN_MID; /* Basic 7 Tones Continuous Tone (low urgency) Medium                     */
extern volatile const U2 u2_CALIB_MCUID3007_URGEN_MID_MID; /* Basic 7 Tones Break off (medium urgency) Medium                        */
extern volatile const U2 u2_CALIB_MCUID3008_URGEN_MAX_MID; /* Basic 7 tones Break off the procedure (high urgency) Medium            */
extern volatile const U2 u2_CALIB_MCUID3009_CONTIN_MID;    /* Basic 7 tone Continuous tone Medium                                    */
extern volatile const U2 u2_CALIB_MCUID3010_PREDOT_MID;    /* Special sound (intermittent) PreDOT sound Medium                       */
extern volatile const U2 u2_CALIB_MCUID3011_ANUNC_MAX;     /* Basic 7 Tone Reporting Large                                           */
extern volatile const U2 u2_CALIB_MCUID3012_ANUNC_SP_MAX;  /* Basic 7 Tone Reporting (Special) Large                                 */
extern volatile const U2 u2_CALIB_MCUID3013_RECEP_MAX;     /* Basic 7 tones Reception tone Large                                     */
extern volatile const U2 u2_CALIB_MCUID3014_REJECT_MAX;    /* Basic 7 tone rejection Large                                           */
extern volatile const U2 u2_CALIB_MCUID3015_URGEN_MIN_MAX; /* Basic 7 Tones Continuous Tone (Less Tightness) Large                   */
extern volatile const U2 u2_CALIB_MCUID3016_URGEN_MID_MAX; /* Basic 7 Tones Continuous Tone (Medium Tightness) Large                 */
extern volatile const U2 u2_CALIB_MCUID3017_URGEN_MAX_MAX; /* Basic 7 Tones Continuous Tone (High Tension) Large                     */
extern volatile const U2 u2_CALIB_MCUID3018_CONTIN_MAX;    /* Basic 7 tone Continuous tone Large                                     */
extern volatile const U2 u2_CALIB_MCUID3019_PREDOT_MAX;    /* Special sound (intermittent) PreDOT sound Large                        */
extern volatile const U2 u2_CALIB_MCUID3021_SEA_MID;       /* Regulatory/Assessment: SEA door open rejecting Medium                  */
extern volatile const U2 u2_CALIB_MCUID3022_SEA_MAX;       /* Regulations/Assessments: SEA Door Open Reject Large                    */
extern volatile const U2 u2_CALIB_MCUID3023_PCS_MID;       /* Regulations/Assessments: PCS Warning, SEA Warning Medium               */
extern volatile const U2 u2_CALIB_MCUID3024_PCS_MAX;       /* Regulations/Assessments: PCS Warning, SEA Warning Large                */
extern volatile const U2 u2_CALIB_MCUID0029_REV_IN_MID;    /* Reverse buzzer Intermittent MID                                        */
extern volatile const U2 u2_CALIB_MCUID0746_REV_IN_MAX;    /* Reverse buzzer Intermittent MAX                                        */
extern volatile const U2 u2_CALIB_MCUID0030_SBELT_FMV_MID; /* seatbelt reminder buzzer(fmv) MID                                      */
extern volatile const U2 u2_CALIB_MCUID0747_SBELT_FMV_MAX; /* seatbelt reminder buzzer(fmv) MAX                                      */
extern volatile const U2 u2_CALIB_MCUID0031_SBELT_LV1_MID; /* seatbelt reminder buzzer(level 1) MID                                  */
extern volatile const U2 u2_CALIB_MCUID0748_SBELT_LV1_MAX; /* seatbelt reminder buzzer(level 1) MAX                                  */
extern volatile const U2 u2_CALIB_MCUID0032_SBELT_LV2_MID; /* seatbelt reminder buzzer(level 2) MID                                  */
extern volatile const U2 u2_CALIB_MCUID0749_SBELT_LV2_MAX; /* seatbelt reminder buzzer(level 2) MAX                                  */
extern volatile const U2 u2_CALIB_MCUID0033_SBELT_SI_MID;  /* seatbelt reminder buzzer(si) MID                                       */
extern volatile const U2 u2_CALIB_MCUID0750_SBELT_SI_MAX;  /* seatbelt reminder buzzer(si) MAX                                       */
extern volatile const U2 u2_CALIB_MCUID0067_CSR_FRSD0;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0068_CSR_FRSD1;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0069_CSR_FRSD2;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0070_CSR_FRSD3;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0071_CSR_FRSD4;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0072_CSR_FRSD5;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0073_CSR_FRSD6;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0074_CSR_FRSD7;     /* Clearance sonar buzzer Fr(SD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0075_CSR_FRMD0;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0076_CSR_FRMD1;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0077_CSR_FRMD2;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0078_CSR_FRMD3;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0079_CSR_FRMD4;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0080_CSR_FRMD5;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0081_CSR_FRMD6;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0082_CSR_FRMD7;     /* Clearance sonar buzzer Fr(MD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0083_CSR_FRLD0;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0084_CSR_FRLD1;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0085_CSR_FRLD2;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0086_CSR_FRLD3;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0087_CSR_FRLD4;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0088_CSR_FRLD5;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0089_CSR_FRLD6;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0090_CSR_FRLD7;     /* Clearance sonar buzzer Fr(LD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0091_CSR_FRFD0;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0092_CSR_FRFD1;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0093_CSR_FRFD2;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0094_CSR_FRFD3;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0095_CSR_FRFD4;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0096_CSR_FRFD5;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0097_CSR_FRFD6;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0098_CSR_FRFD7;     /* Clearance sonar buzzer Fr(FD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0099_CSR_RRSD0;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0100_CSR_RRSD1;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0101_CSR_RRSD2;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0102_CSR_RRSD3;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0103_CSR_RRSD4;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0104_CSR_RRSD5;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0105_CSR_RRSD6;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0106_CSR_RRSD7;     /* Clearance sonar buzzer Rr(SD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0107_CSR_RRMD0;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0108_CSR_RRMD1;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0109_CSR_RRMD2;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0110_CSR_RRMD3;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0111_CSR_RRMD4;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0112_CSR_RRMD5;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0113_CSR_RRMD6;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0114_CSR_RRMD7;     /* Clearance sonar buzzer Rr(MD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0115_CSR_RRLD0;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0116_CSR_RRLD1;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0117_CSR_RRLD2;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0118_CSR_RRLD3;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0119_CSR_RRLD4;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0120_CSR_RRLD5;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0121_CSR_RRLD6;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0122_CSR_RRLD7;     /* Clearance sonar buzzer Rr(LD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0123_CSR_RRFD0;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:0                                */
extern volatile const U2 u2_CALIB_MCUID0124_CSR_RRFD1;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:1                                */
extern volatile const U2 u2_CALIB_MCUID0125_CSR_RRFD2;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:2                                */
extern volatile const U2 u2_CALIB_MCUID0126_CSR_RRFD3;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:3                                */
extern volatile const U2 u2_CALIB_MCUID0127_CSR_RRFD4;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:4                                */
extern volatile const U2 u2_CALIB_MCUID0128_CSR_RRFD5;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:5                                */
extern volatile const U2 u2_CALIB_MCUID0129_CSR_RRFD6;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:6                                */
extern volatile const U2 u2_CALIB_MCUID0130_CSR_RRFD7;     /* Clearance sonar buzzer Rr(FD) CSR_VOL:7                                */
extern volatile const U2 u2_CALIB_MCUID0131_CSR_FRRRSD0;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0                             */
extern volatile const U2 u2_CALIB_MCUID0132_CSR_FRRRSD1;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1                             */
extern volatile const U2 u2_CALIB_MCUID0133_CSR_FRRRSD2;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2                             */
extern volatile const U2 u2_CALIB_MCUID0134_CSR_FRRRSD3;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3                             */
extern volatile const U2 u2_CALIB_MCUID0135_CSR_FRRRSD4;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4                             */
extern volatile const U2 u2_CALIB_MCUID0136_CSR_FRRRSD5;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5                             */
extern volatile const U2 u2_CALIB_MCUID0137_CSR_FRRRSD6;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6                             */
extern volatile const U2 u2_CALIB_MCUID0138_CSR_FRRRSD7;   /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7                             */
extern volatile const U2 u2_CALIB_MCUID0139_CSR_FRRRMD0;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:0                             */
extern volatile const U2 u2_CALIB_MCUID0140_CSR_FRRRMD1;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:1                             */
extern volatile const U2 u2_CALIB_MCUID0141_CSR_FRRRMD2;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:2                             */
extern volatile const U2 u2_CALIB_MCUID0142_CSR_FRRRMD3;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:3                             */
extern volatile const U2 u2_CALIB_MCUID0143_CSR_FRRRMD4;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:4                             */
extern volatile const U2 u2_CALIB_MCUID0144_CSR_FRRRMD5;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:5                             */
extern volatile const U2 u2_CALIB_MCUID0145_CSR_FRRRMD6;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:6                             */
extern volatile const U2 u2_CALIB_MCUID0146_CSR_FRRRMD7;   /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:7                             */
extern volatile const U2 u2_CALIB_MCUID0155_CSR_FRRRLD0;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:0                             */
extern volatile const U2 u2_CALIB_MCUID0156_CSR_FRRRLD1;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:1                             */
extern volatile const U2 u2_CALIB_MCUID0157_CSR_FRRRLD2;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:2                             */
extern volatile const U2 u2_CALIB_MCUID0158_CSR_FRRRLD3;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:3                             */
extern volatile const U2 u2_CALIB_MCUID0159_CSR_FRRRLD4;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:4                             */
extern volatile const U2 u2_CALIB_MCUID0160_CSR_FRRRLD5;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:5                             */
extern volatile const U2 u2_CALIB_MCUID0161_CSR_FRRRLD6;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:6                             */
extern volatile const U2 u2_CALIB_MCUID0162_CSR_FRRRLD7;   /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:7                             */
extern volatile const U2 u2_CALIB_MCUID0171_CSR_FRRRFD0;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:0                             */
extern volatile const U2 u2_CALIB_MCUID0172_CSR_FRRRFD1;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:1                             */
extern volatile const U2 u2_CALIB_MCUID0173_CSR_FRRRFD2;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:2                             */
extern volatile const U2 u2_CALIB_MCUID0174_CSR_FRRRFD3;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:3                             */
extern volatile const U2 u2_CALIB_MCUID0175_CSR_FRRRFD4;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:4                             */
extern volatile const U2 u2_CALIB_MCUID0176_CSR_FRRRFD5;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:5                             */
extern volatile const U2 u2_CALIB_MCUID0177_CSR_FRRRFD6;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:6                             */
extern volatile const U2 u2_CALIB_MCUID0178_CSR_FRRRFD7;   /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:7                             */
extern volatile const U2 u2_CALIB_MCUID0187_FLSTA_LOLO;    /* flasher start sound(low customize, low speed)                          */
extern volatile const U2 u2_CALIB_MCUID0188_FLSTA_LOMI;    /* flasher start sound(low customize, mid speed)                          */
extern volatile const U2 u2_CALIB_MCUID0189_FLSTA_LOHI;    /* flasher start sound(low customize, high speed)                         */
extern volatile const U2 u2_CALIB_MCUID0190_FLSTA_MILO;    /* flasher start sound(mid customize, low speed)                          */
extern volatile const U2 u2_CALIB_MCUID0191_FLSTA_MIMI;    /* flasher start sound(mid customize, mid speed)                          */
extern volatile const U2 u2_CALIB_MCUID0192_FLSTA_MIHI;    /* flasher start sound(mid customize, high speed)                         */
extern volatile const U2 u2_CALIB_MCUID0193_FLSTA_HILO;    /* flasher start sound(high customize, low speed)                         */
extern volatile const U2 u2_CALIB_MCUID0194_FLSTA_HIMI;    /* flasher start sound(high customize, mid speed)                         */
extern volatile const U2 u2_CALIB_MCUID0195_FLSTA_HIHI;    /* flasher start sound(high customize, high speed)                        */
extern volatile const U2 u2_CALIB_MCUID0196_FLFIN_LOLO;    /* flasher finish sound(low customize, low speed)                         */
extern volatile const U2 u2_CALIB_MCUID0197_FLFIN_LOMI;    /* flasher finish sound(low customize, mid speed)                         */
extern volatile const U2 u2_CALIB_MCUID0198_FLFIN_LOHI;    /* flasher finish sound(low customize, high speed)                        */
extern volatile const U2 u2_CALIB_MCUID0199_FLFIN_MILO;    /* flasher finish sound(mid customize, low speed)                         */
extern volatile const U2 u2_CALIB_MCUID0200_FLFIN_MIMI;    /* flasher finish sound(mid customize, mid speed)                         */
extern volatile const U2 u2_CALIB_MCUID0201_FLFIN_MIHI;    /* flasher finish sound(mid customize, high speed)                        */
extern volatile const U2 u2_CALIB_MCUID0202_FLFIN_HILO;    /* flasher finish sound(high customize, low speed)                        */
extern volatile const U2 u2_CALIB_MCUID0203_FLFIN_HIMI;    /* flasher finish sound(high customize, mid speed)                        */
extern volatile const U2 u2_CALIB_MCUID0204_FLFIN_HIHI;    /* flasher finish sound(high customize, high speed)                       */
extern volatile const U2 u2_CALIB_MCUID0205_2CH;           /* 2 channels multiplex playing                                           */
extern volatile const U2 u2_CALIB_MCUID0206_3CH;           /* 3 channels multiplex playing                                           */
extern volatile const U2 u2_CALIB_MCUID0207_4CH;           /* 4 channels multiplex playing                                           */
extern volatile const U2 u2_CALIB_MCUID0208_5CH;           /* 5 channels multiplex playing                                           */
extern volatile const U2 u2_CALIB_MCUID0915_CSR_RCTA_0;    /* RCTA buzzer CSR_VOL:0                                                  */
extern volatile const U2 u2_CALIB_MCUID0916_CSR_RCTA_1;    /* RCTA buzzer CSR_VOL:1                                                  */
extern volatile const U2 u2_CALIB_MCUID0917_CSR_RCTA_2;    /* RCTA buzzer CSR_VOL:2                                                  */
extern volatile const U2 u2_CALIB_MCUID0918_CSR_RCTA_3;    /* RCTA buzzer CSR_VOL:3                                                  */
extern volatile const U2 u2_CALIB_MCUID0919_CSR_RCTA_4;    /* RCTA buzzer CSR_VOL:4                                                  */
extern volatile const U2 u2_CALIB_MCUID0920_CSR_RCTA_5;    /* RCTA buzzer CSR_VOL:5                                                  */
extern volatile const U2 u2_CALIB_MCUID0921_CSR_RCTA_6;    /* RCTA buzzer CSR_VOL:6                                                  */
extern volatile const U2 u2_CALIB_MCUID0922_CSR_RCTA_7;    /* RCTA buzzer CSR_VOL:7                                                  */
extern volatile const U2 u2_CALIB_MCUID0757_SP_USA_20KM;   /* Digital meter vehicle speed for Usa/Canada(20 km/h)                    */
extern volatile const U2 u2_CALIB_MCUID0758_SP_USA_40KM;   /* Digital meter vehicle speed for Usa/Canada(40 km/h)                    */
extern volatile const U2 u2_CALIB_MCUID0759_SP_USA_59KM;   /* Digital meter vehicle speed for Usa/Canada(59 km/h)                    */
extern volatile const U2 u2_CALIB_MCUID0760_SP_USA_80KM;   /* Digital meter vehicle speed for Usa/Canada(80 km/h)                    */
extern volatile const U2 u2_CALIB_MCUID0761_SP_USA_100KM;  /* Digital meter vehicle speed for Usa/Canada(100 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0762_SP_USA_120KM;  /* Digital meter vehicle speed for Usa/Canada(120 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0763_SP_USA_140KM;  /* Digital meter vehicle speed for Usa/Canada(140 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0764_SP_USA_160KM;  /* Digital meter vehicle speed for Usa/Canada(160 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0765_SP_USA_180KM;  /* Digital meter vehicle speed for Usa/Canada(180 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0766_SP_USA_200KM;  /* Digital meter vehicle speed for Usa/Canada(200 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0767_SP_USA_220KM;  /* Digital meter vehicle speed for Usa/Canada(220 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0768_SP_USA_240KM;  /* Digital meter vehicle speed for Usa/Canada(240 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0769_SP_USA_260KM;  /* Digital meter vehicle speed for Usa/Canada(260 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0770_SP_USA_280KM;  /* Digital meter vehicle speed for Usa/Canada(280 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0771_SP_USA_300KM;  /* Digital meter vehicle speed for Usa/Canada(300 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0772_SP_USA_320KM;  /* Digital meter vehicle speed for Usa/Canada(320 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0773_SP_USA_340KM;  /* Digital meter vehicle speed for Usa/Canada(340 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0774_SP_USA_360KM;  /* Digital meter vehicle speed for Usa/Canada(360 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0775_SP_USA_380KM;  /* Digital meter vehicle speed for Usa/Canada(380 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0776_SP_USA_400KM;  /* Digital meter vehicle speed for Usa/Canada(400 km/h)                   */
extern volatile const U2 u2_CALIB_MCUID0777_SP_UNR_20KM;   /* Digital meter vehicle speed for UNR/AUS/others(20 km/h)                */
extern volatile const U2 u2_CALIB_MCUID0778_SP_UNR_40KM;   /* Digital meter vehicle speed for UNR/AUS/others(40 km/h)                */
extern volatile const U2 u2_CALIB_MCUID0779_SP_UNR_59KM;   /* Digital meter vehicle speed for UNR/AUS/others(59 km/h)                */
extern volatile const U2 u2_CALIB_MCUID0780_SP_UNR_80KM;   /* Digital meter vehicle speed for UNR/AUS/others(80 km/h)                */
extern volatile const U2 u2_CALIB_MCUID0781_SP_UNR_100KM;  /* Digital meter vehicle speed for UNR/AUS/others(100 km/h)               */
extern volatile const U2 u2_CALIB_MCUID0782_SP_UNR_120KM;  /* Digital meter vehicle speed for UNR/AUS/others(120 km/h)               */
extern volatile const U2 u2_CALIB_MCUID0783_SP_UNR_140KM;  /* Digital meter vehicle speed for UNR/AUS/others(140 km/h)               */
extern volatile const U2 u2_CALIB_MCUID0784_SP_UNR_160KM;  /* Digital meter vehicle speed for UNR/AUS/others (160 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0785_SP_UNR_180KM;  /* Digital meter vehicle speed for UNR/AUS/others (180 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0786_SP_UNR_200KM;  /* Digital meter vehicle speed for UNR/AUS/others (200 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0787_SP_UNR_220KM;  /* Digital meter vehicle speed for UNR/AUS/others (200 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0788_SP_UNR_240KM;  /* Digital meter vehicle speed for UNR/AUS/others (240 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0789_SP_UNR_260KM;  /* Digital meter vehicle speed for UNR/AUS/others (260 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0790_SP_UNR_280KM;  /* Digital meter vehicle speed for UNR/AUS/others (280 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0791_SP_UNR_300KM;  /* Digital meter vehicle speed for UNR/AUS/others (300 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0792_SP_UNR_320KM;  /* Digital meter vehicle speed for UNR/AUS/others (320 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0793_SP_UNR_340KM;  /* Digital meter vehicle speed for UNR/AUS/others (340 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0794_SP_UNR_360KM;  /* Digital meter vehicle speed for UNR/AUS/others (360 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0795_SP_UNR_380KM;  /* Digital meter vehicle speed for UNR/AUS/others (380 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0796_SP_UNR_400KM;  /* Digital meter vehicle speed for UNR/AUS/others (400 km/h)              */
extern volatile const U2 u2_CALIB_MCUID0262_MAXSPEED_KM;   /* Max Speed km                                                           */
extern volatile const U2 u2_CALIB_MCUID0263_MAXSPEED_MPH;  /* Max Speed mph                                                          */
extern volatile const U2 u2_CALIB_MCUID0292_TR2_DUTY_MAX;  /* CAN:TR2_DUTY(%):light control is max hold                              */
extern volatile const U2 u2_CALIB_MCUID0293_TR2_DUTY_LV1;  /* CAN:TR2_DUTY(%):light control level (1)                                */
extern volatile const U2 u2_CALIB_MCUID0294_TR2_DUTY_LV2;  /* CAN:TR2_DUTY(%):light control level (2)                                */
extern volatile const U2 u2_CALIB_MCUID0295_TR2_DUTY_LV3;  /* CAN:TR2_DUTY(%):light control level (3)                                */
extern volatile const U2 u2_CALIB_MCUID0296_TR2_DUTY_LV4;  /* CAN:TR2_DUTY(%):light control level (4)                                */
extern volatile const U2 u2_CALIB_MCUID0297_TR2_DUTY_LV5;  /* CAN:TR2_DUTY(%):light control level (5)                                */
extern volatile const U2 u2_CALIB_MCUID0298_TR2_DUTY_LV6;  /* CAN:TR2_DUTY(%):light control level (6)                                */
extern volatile const U2 u2_CALIB_MCUID0299_TR2_DUTY_LV7;  /* CAN:TR2_DUTY(%):light control level (7)                                */
extern volatile const U2 u2_CALIB_MCUID0300_TR2_DUTY_LV8;  /* CAN:TR2_DUTY(%):light control level (8)                                */
extern volatile const U2 u2_CALIB_MCUID0301_TR2_DUTY_LV9;  /* CAN:TR2_DUTY(%):light control level (9)                                */
extern volatile const U2 u2_CALIB_MCUID0302_TR2_DUTY_LV10; /* CAN:TR2_DUTY(%):light control level (10)                               */
extern volatile const U2 u2_CALIB_MCUID0303_TR2_DUTY_LV11; /* CAN:TR2_DUTY(%):light control level (11)                               */
extern volatile const U2 u2_CALIB_MCUID0304_TR2_DUTY_LV12; /* CAN:TR2_DUTY(%):light control level (12)                               */
extern volatile const U2 u2_CALIB_MCUID0305_TR2_DUTY_LV13; /* CAN:TR2_DUTY(%):light control level (13)                               */
extern volatile const U2 u2_CALIB_MCUID0306_TR2_DUTY_LV14; /* CAN:TR2_DUTY(%):light control level (14)                               */
extern volatile const U2 u2_CALIB_MCUID0307_TR2_DUTY_LV15; /* CAN:TR2_DUTY(%):light control level (15)                               */
extern volatile const U2 u2_CALIB_MCUID0308_TR2_DUTY_LV16; /* CAN:TR2_DUTY(%):light control level (16)                               */
extern volatile const U2 u2_CALIB_MCUID0309_TR2_DUTY_LV17; /* CAN:TR2_DUTY(%):light control level (17)                               */
extern volatile const U2 u2_CALIB_MCUID0310_TR2_DUTY_LV18; /* CAN:TR2_DUTY(%):light control level (18)                               */
extern volatile const U2 u2_CALIB_MCUID0311_TR2_DUTY_LV19; /* CAN:TR2_DUTY(%):light control level (19)                               */
extern volatile const U2 u2_CALIB_MCUID0312_TR2_DUTY_LV20; /* CAN:TR2_DUTY(%):light control level (20)                               */
extern volatile const U2 u2_CALIB_MCUID0313_TR2_DUTY_MIN;  /* CAN:TR2_DUTY(%): light control is min hold                             */
extern volatile const U2 u2_CALIB_MCUID0314_IL2_DUTY_MAX;  /* CAN:IL2_DUTY(%):light control is max hold                              */
extern volatile const U2 u2_CALIB_MCUID0315_IL2_DUTY_LV1;  /* CAN:IL2_DUTY(%):light control level (1)                                */
extern volatile const U2 u2_CALIB_MCUID0316_IL2_DUTY_LV2;  /* CAN:IL2_DUTY(%):light control level (2)                                */
extern volatile const U2 u2_CALIB_MCUID0317_IL2_DUTY_LV3;  /* CAN:IL2_DUTY(%):light control level (3)                                */
extern volatile const U2 u2_CALIB_MCUID0318_IL2_DUTY_LV4;  /* CAN:IL2_DUTY(%):light control level (4)                                */
extern volatile const U2 u2_CALIB_MCUID0319_IL2_DUTY_LV5;  /* CAN:IL2_DUTY(%):light control level (5)                                */
extern volatile const U2 u2_CALIB_MCUID0320_IL2_DUTY_LV6;  /* CAN:IL2_DUTY(%):light control level (6)                                */
extern volatile const U2 u2_CALIB_MCUID0321_IL2_DUTY_LV7;  /* CAN:IL2_DUTY(%):light control level (7)                                */
extern volatile const U2 u2_CALIB_MCUID0322_IL2_DUTY_LV8;  /* CAN:IL2_DUTY(%):light control level (8)                                */
extern volatile const U2 u2_CALIB_MCUID0323_IL2_DUTY_LV9;  /* CAN:IL2_DUTY(%):light control level (9)                                */
extern volatile const U2 u2_CALIB_MCUID0324_IL2_DUTY_LV10; /* CAN:IL2_DUTY(%):light control level (10)                               */
extern volatile const U2 u2_CALIB_MCUID0325_IL2_DUTY_LV11; /* CAN:IL2_DUTY(%):light control level (11)                               */
extern volatile const U2 u2_CALIB_MCUID0326_IL2_DUTY_LV12; /* CAN:IL2_DUTY(%):light control level (12)                               */
extern volatile const U2 u2_CALIB_MCUID0327_IL2_DUTY_LV13; /* CAN:IL2_DUTY(%):light control level (13)                               */
extern volatile const U2 u2_CALIB_MCUID0328_IL2_DUTY_LV14; /* CAN:IL2_DUTY(%):light control level (14)                               */
extern volatile const U2 u2_CALIB_MCUID0329_IL2_DUTY_LV15; /* CAN:IL2_DUTY(%):light control level (15)                               */
extern volatile const U2 u2_CALIB_MCUID0330_IL2_DUTY_LV16; /* CAN:IL2_DUTY(%):light control level (16)                               */
extern volatile const U2 u2_CALIB_MCUID0331_IL2_DUTY_LV17; /* CAN:IL2_DUTY(%):light control level (17)                               */
extern volatile const U2 u2_CALIB_MCUID0332_IL2_DUTY_LV18; /* CAN:IL2_DUTY(%):light control level (18)                               */
extern volatile const U2 u2_CALIB_MCUID0333_IL2_DUTY_LV19; /* CAN:IL2_DUTY(%):light control level (19)                               */
extern volatile const U2 u2_CALIB_MCUID0334_IL2_DUTY_LV20; /* CAN:IL2_DUTY(%):light control level (20)                               */
extern volatile const U2 u2_CALIB_MCUID0335_IL2_DUTY_MIN;  /* CAN:IL2_DUTY(%): light control is min hold                             */
extern volatile const U2 u2_CALIB_MCUID0574_CAL_DEF;       /* CAL_DEF                                                                */
extern volatile const U2 u2_CALIB_MCUID0575_CAL_MIN;       /* CAL_MIN                                                                */
extern volatile const U2 u2_CALIB_MCUID0738_TIMEOUT_TM;    /* Timeout Time                                                           */
extern volatile const U2 u2_CALIB_MCUID0742_IOUTILLRUN;    /* IOUTILLRun                                                             */
extern volatile const U2 u2_CALIB_MCUID0743_IOUTILLRUNMAX; /* IOUTILLRunmax                                                          */
extern volatile const U2 u2_CALIB_MCUID0923_CNTY_CODE_1;   /* Special destination for judgement Country code 1                       */
extern volatile const U2 u2_CALIB_MCUID0924_CNTY_CODE_2;   /* Special destination for judgement Country code 2                       */
extern volatile const U2 u2_CALIB_MCUID0925_CNTY_CODE_3;   /* Special destination for judgement Country code 3                       */
extern volatile const U2 u2_CALIB_MCUID0926_CNTY_CODE_4;   /* Special destination for judgement Country code 4                       */
extern volatile const U2 u2_CALIB_MCUID0927_CNTY_CODE_5;   /* Special destination for judgement Country code 5                       */
extern volatile const U2 u2_CALIB_MCUID0928_CNTY_CODE_6;   /* Special destination for judgement Country code 6                       */
extern volatile const U2 u2_CALIB_MCUID0929_CNTY_CODE_7;   /* Special destination for judgement Country code 7                       */
extern volatile const U2 u2_CALIB_MCUID0930_CNTY_CODE_8;   /* Special destination for judgement Country code 8                       */
extern volatile const U2 u2_CALIB_MCUID0931_CNTY_CODE_9;   /* Special destination for judgement Country code 9                       */
extern volatile const U2 u2_CALIB_MCUID0932_CNTY_CODE_10;  /* Special destination for judgement Country code 10                      */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0260;       /* Reserve_2B-0260                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0261;       /* Reserve_2B-0261                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0262;       /* Reserve_2B-0262                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0263;       /* Reserve_2B-0263                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0264;       /* Reserve_2B-0264                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0265;       /* Reserve_2B-0265                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0266;       /* Reserve_2B-0266                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0267;       /* Reserve_2B-0267                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0268;       /* Reserve_2B-0268                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0269;       /* Reserve_2B-0269                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0270;       /* Reserve_2B-0270                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0271;       /* Reserve_2B-0271                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0272;       /* Reserve_2B-0272                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0273;       /* Reserve_2B-0273                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0274;       /* Reserve_2B-0274                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0275;       /* Reserve_2B-0275                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0276;       /* Reserve_2B-0276                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0277;       /* Reserve_2B-0277                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0278;       /* Reserve_2B-0278                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0279;       /* Reserve_2B-0279                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0280;       /* Reserve_2B-0280                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0281;       /* Reserve_2B-0281                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0282;       /* Reserve_2B-0282                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0283;       /* Reserve_2B-0283                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0284;       /* Reserve_2B-0284                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0285;       /* Reserve_2B-0285                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0286;       /* Reserve_2B-0286                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0287;       /* Reserve_2B-0287                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0288;       /* Reserve_2B-0288                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0289;       /* Reserve_2B-0289                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0290;       /* Reserve_2B-0290                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0291;       /* Reserve_2B-0291                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0292;       /* Reserve_2B-0292                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0293;       /* Reserve_2B-0293                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0294;       /* Reserve_2B-0294                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0295;       /* Reserve_2B-0295                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0296;       /* Reserve_2B-0296                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0297;       /* Reserve_2B-0297                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0298;       /* Reserve_2B-0298                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0299;       /* Reserve_2B-0299                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0300;       /* Reserve_2B-0300                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0301;       /* Reserve_2B-0301                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0302;       /* Reserve_2B-0302                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0303;       /* Reserve_2B-0303                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0304;       /* Reserve_2B-0304                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0305;       /* Reserve_2B-0305                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0306;       /* Reserve_2B-0306                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0307;       /* Reserve_2B-0307                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0308;       /* Reserve_2B-0308                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0309;       /* Reserve_2B-0309                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0310;       /* Reserve_2B-0310                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0311;       /* Reserve_2B-0311                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0312;       /* Reserve_2B-0312                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0313;       /* Reserve_2B-0313                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0314;       /* Reserve_2B-0314                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0315;       /* Reserve_2B-0315                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0316;       /* Reserve_2B-0316                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0317;       /* Reserve_2B-0317                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0318;       /* Reserve_2B-0318                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0319;       /* Reserve_2B-0319                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0320;       /* Reserve_2B-0320                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0321;       /* Reserve_2B-0321                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0322;       /* Reserve_2B-0322                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0323;       /* Reserve_2B-0323                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0324;       /* Reserve_2B-0324                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0325;       /* Reserve_2B-0325                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0326;       /* Reserve_2B-0326                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0327;       /* Reserve_2B-0327                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0328;       /* Reserve_2B-0328                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0329;       /* Reserve_2B-0329                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0330;       /* Reserve_2B-0330                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0331;       /* Reserve_2B-0331                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0332;       /* Reserve_2B-0332                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0333;       /* Reserve_2B-0333                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0334;       /* Reserve_2B-0334                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0335;       /* Reserve_2B-0335                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0336;       /* Reserve_2B-0336                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0337;       /* Reserve_2B-0337                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0338;       /* Reserve_2B-0338                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0339;       /* Reserve_2B-0339                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0340;       /* Reserve_2B-0340                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0341;       /* Reserve_2B-0341                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0342;       /* Reserve_2B-0342                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0343;       /* Reserve_2B-0343                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0344;       /* Reserve_2B-0344                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0345;       /* Reserve_2B-0345                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0346;       /* Reserve_2B-0346                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0347;       /* Reserve_2B-0347                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0348;       /* Reserve_2B-0348                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0349;       /* Reserve_2B-0349                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0350;       /* Reserve_2B-0350                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0351;       /* Reserve_2B-0351                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0352;       /* Reserve_2B-0352                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0353;       /* Reserve_2B-0353                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0354;       /* Reserve_2B-0354                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0355;       /* Reserve_2B-0355                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0356;       /* Reserve_2B-0356                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0357;       /* Reserve_2B-0357                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0358;       /* Reserve_2B-0358                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0359;       /* Reserve_2B-0359                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0360;       /* Reserve_2B-0360                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0361;       /* Reserve_2B-0361                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0362;       /* Reserve_2B-0362                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0363;       /* Reserve_2B-0363                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0364;       /* Reserve_2B-0364                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0365;       /* Reserve_2B-0365                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0366;       /* Reserve_2B-0366                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0367;       /* Reserve_2B-0367                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0368;       /* Reserve_2B-0368                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0369;       /* Reserve_2B-0369                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0370;       /* Reserve_2B-0370                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0371;       /* Reserve_2B-0371                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0372;       /* Reserve_2B-0372                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0373;       /* Reserve_2B-0373                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0374;       /* Reserve_2B-0374                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0375;       /* Reserve_2B-0375                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0376;       /* Reserve_2B-0376                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0377;       /* Reserve_2B-0377                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0378;       /* Reserve_2B-0378                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0379;       /* Reserve_2B-0379                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0380;       /* Reserve_2B-0380                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0381;       /* Reserve_2B-0381                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0382;       /* Reserve_2B-0382                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0383;       /* Reserve_2B-0383                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0384;       /* Reserve_2B-0384                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0385;       /* Reserve_2B-0385                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0386;       /* Reserve_2B-0386                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0387;       /* Reserve_2B-0387                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0388;       /* Reserve_2B-0388                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0389;       /* Reserve_2B-0389                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0390;       /* Reserve_2B-0390                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0391;       /* Reserve_2B-0391                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0392;       /* Reserve_2B-0392                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0393;       /* Reserve_2B-0393                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0394;       /* Reserve_2B-0394                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0395;       /* Reserve_2B-0395                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0396;       /* Reserve_2B-0396                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0397;       /* Reserve_2B-0397                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0398;       /* Reserve_2B-0398                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0399;       /* Reserve_2B-0399                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0400;       /* Reserve_2B-0400                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0401;       /* Reserve_2B-0401                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0402;       /* Reserve_2B-0402                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0403;       /* Reserve_2B-0403                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0404;       /* Reserve_2B-0404                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0405;       /* Reserve_2B-0405                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0406;       /* Reserve_2B-0406                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0407;       /* Reserve_2B-0407                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0408;       /* Reserve_2B-0408                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0409;       /* Reserve_2B-0409                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0410;       /* Reserve_2B-0410                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0411;       /* Reserve_2B-0411                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0412;       /* Reserve_2B-0412                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0413;       /* Reserve_2B-0413                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0414;       /* Reserve_2B-0414                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0415;       /* Reserve_2B-0415                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0416;       /* Reserve_2B-0416                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0417;       /* Reserve_2B-0417                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0418;       /* Reserve_2B-0418                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0419;       /* Reserve_2B-0419                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0420;       /* Reserve_2B-0420                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0421;       /* Reserve_2B-0421                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0422;       /* Reserve_2B-0422                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0423;       /* Reserve_2B-0423                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0424;       /* Reserve_2B-0424                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0425;       /* Reserve_2B-0425                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0426;       /* Reserve_2B-0426                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0427;       /* Reserve_2B-0427                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0428;       /* Reserve_2B-0428                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0429;       /* Reserve_2B-0429                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0430;       /* Reserve_2B-0430                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0431;       /* Reserve_2B-0431                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0432;       /* Reserve_2B-0432                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0433;       /* Reserve_2B-0433                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0434;       /* Reserve_2B-0434                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0435;       /* Reserve_2B-0435                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0436;       /* Reserve_2B-0436                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0437;       /* Reserve_2B-0437                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0438;       /* Reserve_2B-0438                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0439;       /* Reserve_2B-0439                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0440;       /* Reserve_2B-0440                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0441;       /* Reserve_2B-0441                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0442;       /* Reserve_2B-0442                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0443;       /* Reserve_2B-0443                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0444;       /* Reserve_2B-0444                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0445;       /* Reserve_2B-0445                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0446;       /* Reserve_2B-0446                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0447;       /* Reserve_2B-0447                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0448;       /* Reserve_2B-0448                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0449;       /* Reserve_2B-0449                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0450;       /* Reserve_2B-0450                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0451;       /* Reserve_2B-0451                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0452;       /* Reserve_2B-0452                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0453;       /* Reserve_2B-0453                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0454;       /* Reserve_2B-0454                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0455;       /* Reserve_2B-0455                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0456;       /* Reserve_2B-0456                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0457;       /* Reserve_2B-0457                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0458;       /* Reserve_2B-0458                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0459;       /* Reserve_2B-0459                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0460;       /* Reserve_2B-0460                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0461;       /* Reserve_2B-0461                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0462;       /* Reserve_2B-0462                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0463;       /* Reserve_2B-0463                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0464;       /* Reserve_2B-0464                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0465;       /* Reserve_2B-0465                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0466;       /* Reserve_2B-0466                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0467;       /* Reserve_2B-0467                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0468;       /* Reserve_2B-0468                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0469;       /* Reserve_2B-0469                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0470;       /* Reserve_2B-0470                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0471;       /* Reserve_2B-0471                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0472;       /* Reserve_2B-0472                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0473;       /* Reserve_2B-0473                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0474;       /* Reserve_2B-0474                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0475;       /* Reserve_2B-0475                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0476;       /* Reserve_2B-0476                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0477;       /* Reserve_2B-0477                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0478;       /* Reserve_2B-0478                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0479;       /* Reserve_2B-0479                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0480;       /* Reserve_2B-0480                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0481;       /* Reserve_2B-0481                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0482;       /* Reserve_2B-0482                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0483;       /* Reserve_2B-0483                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0484;       /* Reserve_2B-0484                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0485;       /* Reserve_2B-0485                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0486;       /* Reserve_2B-0486                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0487;       /* Reserve_2B-0487                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0488;       /* Reserve_2B-0488                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0489;       /* Reserve_2B-0489                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0490;       /* Reserve_2B-0490                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0491;       /* Reserve_2B-0491                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0492;       /* Reserve_2B-0492                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0493;       /* Reserve_2B-0493                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0494;       /* Reserve_2B-0494                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0495;       /* Reserve_2B-0495                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0496;       /* Reserve_2B-0496                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0497;       /* Reserve_2B-0497                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0498;       /* Reserve_2B-0498                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0499;       /* Reserve_2B-0499                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0500;       /* Reserve_2B-0500                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0501;       /* Reserve_2B-0501                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0502;       /* Reserve_2B-0502                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0503;       /* Reserve_2B-0503                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0504;       /* Reserve_2B-0504                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0505;       /* Reserve_2B-0505                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0506;       /* Reserve_2B-0506                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0507;       /* Reserve_2B-0507                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0508;       /* Reserve_2B-0508                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0509;       /* Reserve_2B-0509                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0510;       /* Reserve_2B-0510                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0511;       /* Reserve_2B-0511                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0512;       /* Reserve_2B-0512                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0513;       /* Reserve_2B-0513                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0514;       /* Reserve_2B-0514                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0515;       /* Reserve_2B-0515                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0516;       /* Reserve_2B-0516                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0517;       /* Reserve_2B-0517                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0518;       /* Reserve_2B-0518                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0519;       /* Reserve_2B-0519                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0520;       /* Reserve_2B-0520                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0521;       /* Reserve_2B-0521                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0522;       /* Reserve_2B-0522                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0523;       /* Reserve_2B-0523                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0524;       /* Reserve_2B-0524                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0525;       /* Reserve_2B-0525                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0526;       /* Reserve_2B-0526                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0527;       /* Reserve_2B-0527                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0528;       /* Reserve_2B-0528                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0529;       /* Reserve_2B-0529                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0530;       /* Reserve_2B-0530                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0531;       /* Reserve_2B-0531                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0532;       /* Reserve_2B-0532                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0533;       /* Reserve_2B-0533                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0534;       /* Reserve_2B-0534                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0535;       /* Reserve_2B-0535                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0536;       /* Reserve_2B-0536                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0537;       /* Reserve_2B-0537                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0538;       /* Reserve_2B-0538                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0539;       /* Reserve_2B-0539                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0540;       /* Reserve_2B-0540                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0541;       /* Reserve_2B-0541                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0542;       /* Reserve_2B-0542                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0543;       /* Reserve_2B-0543                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0544;       /* Reserve_2B-0544                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0545;       /* Reserve_2B-0545                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0546;       /* Reserve_2B-0546                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0547;       /* Reserve_2B-0547                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0548;       /* Reserve_2B-0548                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0549;       /* Reserve_2B-0549                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0550;       /* Reserve_2B-0550                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0551;       /* Reserve_2B-0551                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0552;       /* Reserve_2B-0552                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0553;       /* Reserve_2B-0553                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0554;       /* Reserve_2B-0554                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0555;       /* Reserve_2B-0555                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0556;       /* Reserve_2B-0556                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0557;       /* Reserve_2B-0557                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0558;       /* Reserve_2B-0558                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0559;       /* Reserve_2B-0559                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0560;       /* Reserve_2B-0560                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0561;       /* Reserve_2B-0561                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0562;       /* Reserve_2B-0562                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0563;       /* Reserve_2B-0563                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0564;       /* Reserve_2B-0564                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0565;       /* Reserve_2B-0565                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0566;       /* Reserve_2B-0566                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0567;       /* Reserve_2B-0567                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0568;       /* Reserve_2B-0568                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0569;       /* Reserve_2B-0569                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0570;       /* Reserve_2B-0570                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0571;       /* Reserve_2B-0571                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0572;       /* Reserve_2B-0572                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0573;       /* Reserve_2B-0573                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0574;       /* Reserve_2B-0574                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0575;       /* Reserve_2B-0575                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0576;       /* Reserve_2B-0576                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0577;       /* Reserve_2B-0577                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0578;       /* Reserve_2B-0578                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0579;       /* Reserve_2B-0579                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0580;       /* Reserve_2B-0580                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0581;       /* Reserve_2B-0581                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0582;       /* Reserve_2B-0582                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0583;       /* Reserve_2B-0583                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0584;       /* Reserve_2B-0584                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0585;       /* Reserve_2B-0585                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0586;       /* Reserve_2B-0586                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0587;       /* Reserve_2B-0587                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0588;       /* Reserve_2B-0588                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0589;       /* Reserve_2B-0589                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0590;       /* Reserve_2B-0590                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0591;       /* Reserve_2B-0591                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0592;       /* Reserve_2B-0592                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0593;       /* Reserve_2B-0593                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0594;       /* Reserve_2B-0594                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0595;       /* Reserve_2B-0595                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0596;       /* Reserve_2B-0596                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0597;       /* Reserve_2B-0597                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0598;       /* Reserve_2B-0598                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0599;       /* Reserve_2B-0599                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0600;       /* Reserve_2B-0600                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0601;       /* Reserve_2B-0601                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0602;       /* Reserve_2B-0602                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0603;       /* Reserve_2B-0603                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0604;       /* Reserve_2B-0604                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0605;       /* Reserve_2B-0605                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0606;       /* Reserve_2B-0606                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0607;       /* Reserve_2B-0607                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0608;       /* Reserve_2B-0608                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0609;       /* Reserve_2B-0609                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0610;       /* Reserve_2B-0610                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0611;       /* Reserve_2B-0611                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0612;       /* Reserve_2B-0612                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0613;       /* Reserve_2B-0613                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0614;       /* Reserve_2B-0614                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0615;       /* Reserve_2B-0615                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0616;       /* Reserve_2B-0616                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0617;       /* Reserve_2B-0617                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0618;       /* Reserve_2B-0618                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0619;       /* Reserve_2B-0619                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0620;       /* Reserve_2B-0620                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0621;       /* Reserve_2B-0621                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0622;       /* Reserve_2B-0622                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0623;       /* Reserve_2B-0623                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0624;       /* Reserve_2B-0624                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0625;       /* Reserve_2B-0625                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0626;       /* Reserve_2B-0626                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0627;       /* Reserve_2B-0627                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0628;       /* Reserve_2B-0628                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0629;       /* Reserve_2B-0629                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0630;       /* Reserve_2B-0630                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0631;       /* Reserve_2B-0631                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0632;       /* Reserve_2B-0632                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0633;       /* Reserve_2B-0633                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0634;       /* Reserve_2B-0634                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0635;       /* Reserve_2B-0635                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0636;       /* Reserve_2B-0636                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0637;       /* Reserve_2B-0637                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0638;       /* Reserve_2B-0638                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0639;       /* Reserve_2B-0639                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0640;       /* Reserve_2B-0640                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0641;       /* Reserve_2B-0641                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0642;       /* Reserve_2B-0642                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0643;       /* Reserve_2B-0643                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0644;       /* Reserve_2B-0644                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0645;       /* Reserve_2B-0645                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0646;       /* Reserve_2B-0646                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0647;       /* Reserve_2B-0647                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0648;       /* Reserve_2B-0648                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0649;       /* Reserve_2B-0649                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0650;       /* Reserve_2B-0650                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0651;       /* Reserve_2B-0651                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0652;       /* Reserve_2B-0652                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0653;       /* Reserve_2B-0653                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0654;       /* Reserve_2B-0654                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0655;       /* Reserve_2B-0655                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0656;       /* Reserve_2B-0656                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0657;       /* Reserve_2B-0657                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0658;       /* Reserve_2B-0658                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0659;       /* Reserve_2B-0659                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0660;       /* Reserve_2B-0660                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0661;       /* Reserve_2B-0661                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0662;       /* Reserve_2B-0662                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0663;       /* Reserve_2B-0663                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0664;       /* Reserve_2B-0664                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0665;       /* Reserve_2B-0665                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0666;       /* Reserve_2B-0666                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0667;       /* Reserve_2B-0667                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0668;       /* Reserve_2B-0668                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0669;       /* Reserve_2B-0669                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0670;       /* Reserve_2B-0670                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0671;       /* Reserve_2B-0671                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0672;       /* Reserve_2B-0672                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0673;       /* Reserve_2B-0673                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0674;       /* Reserve_2B-0674                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0675;       /* Reserve_2B-0675                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0676;       /* Reserve_2B-0676                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0677;       /* Reserve_2B-0677                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0678;       /* Reserve_2B-0678                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0679;       /* Reserve_2B-0679                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0680;       /* Reserve_2B-0680                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0681;       /* Reserve_2B-0681                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0682;       /* Reserve_2B-0682                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0683;       /* Reserve_2B-0683                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0684;       /* Reserve_2B-0684                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0685;       /* Reserve_2B-0685                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0686;       /* Reserve_2B-0686                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0687;       /* Reserve_2B-0687                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0688;       /* Reserve_2B-0688                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0689;       /* Reserve_2B-0689                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0690;       /* Reserve_2B-0690                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0691;       /* Reserve_2B-0691                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0692;       /* Reserve_2B-0692                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0693;       /* Reserve_2B-0693                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0694;       /* Reserve_2B-0694                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0695;       /* Reserve_2B-0695                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0696;       /* Reserve_2B-0696                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0697;       /* Reserve_2B-0697                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0698;       /* Reserve_2B-0698                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0699;       /* Reserve_2B-0699                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0700;       /* Reserve_2B-0700                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0701;       /* Reserve_2B-0701                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0702;       /* Reserve_2B-0702                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0703;       /* Reserve_2B-0703                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0704;       /* Reserve_2B-0704                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0705;       /* Reserve_2B-0705                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0706;       /* Reserve_2B-0706                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0707;       /* Reserve_2B-0707                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0708;       /* Reserve_2B-0708                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0709;       /* Reserve_2B-0709                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0710;       /* Reserve_2B-0710                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0711;       /* Reserve_2B-0711                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0712;       /* Reserve_2B-0712                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0713;       /* Reserve_2B-0713                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0714;       /* Reserve_2B-0714                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0715;       /* Reserve_2B-0715                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0716;       /* Reserve_2B-0716                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0717;       /* Reserve_2B-0717                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0718;       /* Reserve_2B-0718                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0719;       /* Reserve_2B-0719                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0720;       /* Reserve_2B-0720                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0721;       /* Reserve_2B-0721                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0722;       /* Reserve_2B-0722                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0723;       /* Reserve_2B-0723                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0724;       /* Reserve_2B-0724                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0725;       /* Reserve_2B-0725                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0726;       /* Reserve_2B-0726                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0727;       /* Reserve_2B-0727                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0728;       /* Reserve_2B-0728                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0729;       /* Reserve_2B-0729                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0730;       /* Reserve_2B-0730                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0731;       /* Reserve_2B-0731                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0732;       /* Reserve_2B-0732                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0733;       /* Reserve_2B-0733                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0734;       /* Reserve_2B-0734                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0735;       /* Reserve_2B-0735                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0736;       /* Reserve_2B-0736                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0737;       /* Reserve_2B-0737                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0738;       /* Reserve_2B-0738                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0739;       /* Reserve_2B-0739                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0740;       /* Reserve_2B-0740                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0741;       /* Reserve_2B-0741                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0742;       /* Reserve_2B-0742                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0743;       /* Reserve_2B-0743                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0744;       /* Reserve_2B-0744                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0745;       /* Reserve_2B-0745                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0746;       /* Reserve_2B-0746                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0747;       /* Reserve_2B-0747                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0748;       /* Reserve_2B-0748                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0749;       /* Reserve_2B-0749                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0750;       /* Reserve_2B-0750                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0751;       /* Reserve_2B-0751                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0752;       /* Reserve_2B-0752                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0753;       /* Reserve_2B-0753                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0754;       /* Reserve_2B-0754                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0755;       /* Reserve_2B-0755                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0756;       /* Reserve_2B-0756                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0757;       /* Reserve_2B-0757                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0758;       /* Reserve_2B-0758                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0759;       /* Reserve_2B-0759                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0760;       /* Reserve_2B-0760                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0761;       /* Reserve_2B-0761                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0762;       /* Reserve_2B-0762                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0763;       /* Reserve_2B-0763                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0764;       /* Reserve_2B-0764                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0765;       /* Reserve_2B-0765                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0766;       /* Reserve_2B-0766                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0767;       /* Reserve_2B-0767                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0768;       /* Reserve_2B-0768                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0769;       /* Reserve_2B-0769                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0770;       /* Reserve_2B-0770                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0771;       /* Reserve_2B-0771                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0772;       /* Reserve_2B-0772                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0773;       /* Reserve_2B-0773                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0774;       /* Reserve_2B-0774                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0775;       /* Reserve_2B-0775                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0776;       /* Reserve_2B-0776                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0777;       /* Reserve_2B-0777                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0778;       /* Reserve_2B-0778                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0779;       /* Reserve_2B-0779                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0780;       /* Reserve_2B-0780                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0781;       /* Reserve_2B-0781                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0782;       /* Reserve_2B-0782                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0783;       /* Reserve_2B-0783                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0784;       /* Reserve_2B-0784                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0785;       /* Reserve_2B-0785                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0786;       /* Reserve_2B-0786                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0787;       /* Reserve_2B-0787                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0788;       /* Reserve_2B-0788                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0789;       /* Reserve_2B-0789                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0790;       /* Reserve_2B-0790                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0791;       /* Reserve_2B-0791                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0792;       /* Reserve_2B-0792                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0793;       /* Reserve_2B-0793                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0794;       /* Reserve_2B-0794                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0795;       /* Reserve_2B-0795                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0796;       /* Reserve_2B-0796                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0797;       /* Reserve_2B-0797                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0798;       /* Reserve_2B-0798                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0799;       /* Reserve_2B-0799                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0800;       /* Reserve_2B-0800                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0801;       /* Reserve_2B-0801                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0802;       /* Reserve_2B-0802                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0803;       /* Reserve_2B-0803                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0804;       /* Reserve_2B-0804                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0805;       /* Reserve_2B-0805                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0806;       /* Reserve_2B-0806                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0807;       /* Reserve_2B-0807                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0808;       /* Reserve_2B-0808                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0809;       /* Reserve_2B-0809                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0810;       /* Reserve_2B-0810                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0811;       /* Reserve_2B-0811                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0812;       /* Reserve_2B-0812                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0813;       /* Reserve_2B-0813                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0814;       /* Reserve_2B-0814                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0815;       /* Reserve_2B-0815                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0816;       /* Reserve_2B-0816                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0817;       /* Reserve_2B-0817                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0818;       /* Reserve_2B-0818                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0819;       /* Reserve_2B-0819                                                        */

extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0001;       /* Reserve_4B-0001                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0002;       /* Reserve_4B-0002                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0003;       /* Reserve_4B-0003                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0004;       /* Reserve_4B-0004                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0005;       /* Reserve_4B-0005                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0006;       /* Reserve_4B-0006                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0007;       /* Reserve_4B-0007                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0008;       /* Reserve_4B-0008                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0009;       /* Reserve_4B-0009                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0010;       /* Reserve_4B-0010                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0011;       /* Reserve_4B-0011                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0012;       /* Reserve_4B-0012                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0013;       /* Reserve_4B-0013                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0014;       /* Reserve_4B-0014                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0015;       /* Reserve_4B-0015                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0016;       /* Reserve_4B-0016                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0017;       /* Reserve_4B-0017                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0018;       /* Reserve_4B-0018                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0019;       /* Reserve_4B-0019                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0020;       /* Reserve_4B-0020                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0021;       /* Reserve_4B-0021                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0022;       /* Reserve_4B-0022                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0023;       /* Reserve_4B-0023                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0024;       /* Reserve_4B-0024                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0025;       /* Reserve_4B-0025                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0026;       /* Reserve_4B-0026                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0027;       /* Reserve_4B-0027                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0028;       /* Reserve_4B-0028                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0029;       /* Reserve_4B-0029                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0030;       /* Reserve_4B-0030                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0031;       /* Reserve_4B-0031                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0032;       /* Reserve_4B-0032                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0033;       /* Reserve_4B-0033                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0034;       /* Reserve_4B-0034                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0035;       /* Reserve_4B-0035                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0036;       /* Reserve_4B-0036                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0037;       /* Reserve_4B-0037                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0038;       /* Reserve_4B-0038                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0039;       /* Reserve_4B-0039                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0040;       /* Reserve_4B-0040                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0041;       /* Reserve_4B-0041                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0042;       /* Reserve_4B-0042                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0043;       /* Reserve_4B-0043                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0044;       /* Reserve_4B-0044                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0045;       /* Reserve_4B-0045                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0046;       /* Reserve_4B-0046                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0047;       /* Reserve_4B-0047                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0048;       /* Reserve_4B-0048                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0049;       /* Reserve_4B-0049                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0050;       /* Reserve_4B-0050                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0051;       /* Reserve_4B-0051                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0052;       /* Reserve_4B-0052                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0053;       /* Reserve_4B-0053                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0054;       /* Reserve_4B-0054                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0055;       /* Reserve_4B-0055                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0056;       /* Reserve_4B-0056                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0057;       /* Reserve_4B-0057                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0058;       /* Reserve_4B-0058                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0059;       /* Reserve_4B-0059                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0060;       /* Reserve_4B-0060                                                        */

#endif
