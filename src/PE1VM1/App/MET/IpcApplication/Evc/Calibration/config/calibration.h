/* 1.3.0 */
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
#define CALIBRATION_H_MINOR                        (3)
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
#define CALIB_MCUID0021_MIN                         (0U)             /* HUD MAIN Hard SW MIN                                         */
#define CALIB_MCUID0021_MAX                         (1U)             /* HUD MAIN Hard SW MAX                                         */
#define CALIB_MCUID0022_MAX                         (1U)             /* Fuel Main Sender MAX                                         */
#define CALIB_MCUID0023_12INCH                      (3U)             /* Display 12.3inch                                             */
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
#define CALIB_MCUID0026_1MOT_HV_FF                  (1U)             /* 1MOT HV FF                                                   */
#define CALIB_MCUID0233_MIN                         (0U)             /* Rear Seat Door MIN                                           */
#define CALIB_MCUID0233_MAX                         (1U)             /* Rear Seat Door MAX                                           */
#define CALIB_MCUID0234_MIN                         (0U)             /* Walkthrough MIN                                              */
#define CALIB_MCUID0234_MAX                         (1U)             /* Walkthrough MAX                                              */
#define CALIB_MCUID0237_NE1                         (0U)             /* NE1                                                          */
#define CALIB_MCUID0241_MAX                         (84200U)         /* FulEff MAX                                                   */
#define CALIB_MCUID0244_MAX                         (84200U)         /* EFFUPR MAX                                                   */
#define CALIB_MCUID0245_MAX                         (84200U)         /* EFFLOW MAX                                                   */
#define CALIB_MCUID0268_BUTTON_1                    (0U)             /* 1 BUTTON                                                     */
#define CALIB_MCUID0340_MAX                         (21U)            /* Rheostat Position Night MAX                                  */
#define CALIB_MCUID0430_1_INPUT                     (0U)             /* 1 INPUT                                                      */
#define CALIB_MCUID0430_2_INPUT                     (1U)             /* 2 INPUT                                                      */
#define CALIB_MCUID0430_THUMB_WHEEL                 (2U)             /* THUMB WHEEL                                                  */
#define CALIB_MCUID0430_SOFTSW                      (3U)             /* SOFT SW                                                      */
#define CALIB_MCUID0432_LID_NON                     (0U)             /* LID NON                                                      */
#define CALIB_MCUID0432_LSTM                        (1U)             /* LSTM                                                         */
#define CALIB_MCUID0432_LST1                        (2U)             /* LST1                                                         */
#define CALIB_MCUID0558_RESISTANCE                  (1U)             /* RESISTANCE                                                   */
#define CALIB_MCUID0560_MIN                         (1U)             /* ATCaluNum MIN                                                */
#define CALIB_MCUID0573_MIN                         (0U)             /* Fuel Sub Sender MIN                                          */
#define CALIB_MCUID0573_MAX                         (1U)             /* Fuel Sub Sender                                              */
#define CALIB_MCUID0578_MIN                         (1U)             /* Deg_RTStep MIN                                               */
#define CALIB_MCUID0578_MAX                         (U1_MAX)         /* Deg_RTStepl MAX                                              */
#define CALIB_MCUID0603_TO_MCUID0607_NUM            (3U)             /* SeatBelt Regulation NUM                                      */
#define CALIB_MCUID0639_MIN                         (1U)             /* N1 MIN                                                       */
#define CALIB_MCUID0640_MIN                         (1U)             /* N2 MIN                                                       */
#define CALIB_MCUID0809_FMVSS                       (0U)             /* Mexico FMVSS                                                 */
#define CALIB_MCUID0810_FMVSS                       (0U)             /* Korea FMVSS                                                  */
#define CALIB_MCUID0797_MIN                         (0U)             /* Constant write flag MIN                                      */
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
#define CALIB_SOUND_PRESS_RATE_MIN                  (0U)             /* Sound Pressure Rate MIN MCUID0029-0039,0067-0208,0744-0753   */
#define CALIB_SP_TOLER_CORPT_NUM                    (20U)            /* Num of Speed Toler Cor Points MCUID0757-0776,0777-0796       */


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
extern volatile const U2 u2_CALIB_DUMMY_0001;              /* MCUCONST_v019 MCUID0024 (AT reverse buzzer MID)                        */
extern volatile const U2 u2_CALIB_DUMMY_0002;              /* MCUCONST_v019 MCUID0744 (AT reverse buzzer MAX)                        */
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
extern volatile const U2 u2_CALIB_MCUID0035_MC_MID;        /* Master Caution MID                                                     */
extern volatile const U2 u2_CALIB_MCUID0036_MC_MAX;        /* Master Caution MAX                                                     */
extern volatile const U2 u2_CALIB_MCUID0037_ACC_MID;       /* ACC Auto Start MID                                                     */
extern volatile const U2 u2_CALIB_MCUID0751_ACC_MAX;       /* ACC Auto Start MAX                                                     */
extern volatile const U2 u2_CALIB_MCUID0038_TMN_MID;       /* TMN MID                                                                */
extern volatile const U2 u2_CALIB_MCUID0752_TMN_MAX;       /* TMN MAX                                                                */
extern volatile const U2 u2_CALIB_MCUID0039_RSA_MID;       /* RSA MID                                                                */
extern volatile const U2 u2_CALIB_MCUID0753_RSA_MAX;       /* RSA MAX                                                                */
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
extern volatile const U2 u2_CALIB_MCUID0799_800HZ_57DB;    /* single frequency buzzer 800hz 57db                                     */
extern volatile const U2 u2_CALIB_MCUID0800_800HZ_61DB;    /* single frequency buzzer 800hz 61db                                     */
extern volatile const U2 u2_CALIB_MCUID0801_800HZ_63DB;    /* single frequency buzzer 800hz 63db                                     */
extern volatile const U2 u2_CALIB_MCUID0802_800HZ_67DB;    /* single frequency buzzer 800hz 67db                                     */
extern volatile const U2 u2_CALIB_MCUID0803_1600HZ_63DB;   /* single frequency buzzer 1600hz 63db                                    */
extern volatile const U2 u2_CALIB_MCUID0804_1600HZ_67DB;   /* single frequency buzzer 1600hz 67db                                    */
extern volatile const U2 u2_CALIB_MCUID0805_1600HZ_73DB;   /* single frequency buzzer 1600hz 73db                                    */
extern volatile const U2 u2_CALIB_MCUID0806_1600HZ_77DB;   /* single frequency buzzer 1600hz 77db                                    */
extern volatile const U2 u2_CALIB_MCUID0807_2400HZ_63DB;   /* single frequency buzzer 2400hz 63db                                    */
extern volatile const U2 u2_CALIB_MCUID0808_2400HZ_67DB;   /* single frequency buzzer 2400hz 67db                                    */
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
extern volatile const U2 u2_CALIB_MCUID0239_FULFUL;        /* FulFul                                                                 */
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
extern volatile const U1 u1_CALIB_DUMMY_0003;              /* MCUCONST_v019 MCUID0588 (OM_MLG)                                       */
extern volatile const U1 u1_CALIB_DUMMY_0004;              /* MCUCONST_v019 MCUID0589 (PR_OM_FL)                                     */
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
extern volatile const U2 u2_CALIB_MCUID0609_KPAOLPL;       /* kPaOLPL                                                                */
extern volatile const U2 u2_CALIB_MCUID0610_KPAOLPH;       /* kPaOLPH                                                                */
extern volatile const U2 u2_CALIB_DUMMY_0005;              /* MCUCONST_v019 U2 MCUID0611 (barOLPL)                                   */
extern volatile const U2 u2_CALIB_DUMMY_0006;              /* MCUCONST_v019 U2 MCUID0612 (barOLPH)                                   */
extern volatile const U2 u2_CALIB_MCUID0613_PSIOLPL;       /* psiOLPL                                                                */
extern volatile const U2 u2_CALIB_MCUID0614_PSIOLPH;       /* psiOLPH                                                                */
extern volatile const U1 u1_CALIB_MCUID0653_KPAOLPMAX;     /* kPaOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0654_KPAOLPMIN;     /* kPaOLPMin                                                              */
extern volatile const U1 u1_CALIB_MCUID0655_BAROLPMAX;     /* barOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0656_BAROLPMIN;     /* barOLPMin                                                              */
extern volatile const U1 u1_CALIB_MCUID0657_PSIOLPMAX;     /* psiOLPMax                                                              */
extern volatile const U1 u1_CALIB_MCUID0658_PSIOLPMIN;     /* psiOLPMin                                                              */
extern volatile const U1 u1_CALIB_MCUID0623_OLTTLC;        /* OLTtlC                                                                 */
extern volatile const U1 u1_CALIB_MCUID0624_OLTTLH;        /* OLTtlH                                                                 */
extern volatile const U2 u2_CALIB_MCUID0625_OLTMAXC;       /* OLTMaxC                                                                */
extern volatile const U2 u2_CALIB_MCUID0626_OLTMINC;       /* OLTMinC                                                                */
extern volatile const U2 u2_CALIB_MCUID0627_OLTMAXF;       /* OLTMaxF                                                                */
extern volatile const U2 u2_CALIB_MCUID0628_OLTMINF;       /* OLTMinF                                                                */
extern volatile const U1 u1_CALIB_MCUID0629_HYS;           /* hys                                                                    */
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
extern volatile const U1 u1_CALIB_MCUID0647_METHVSYSIND;   /* MET HV System Indicator                                                */
extern volatile const U1 u1_CALIB_MCUID0648_HUDHVSYSIND;   /* HUD HV System Indicator                                                */
extern volatile const U1 u1_CALIB_MCUID0649_METNORM;       /* MET Normal Display                                                     */
extern volatile const U1 u1_CALIB_MCUID0650_HUDNORM;       /* HUD Normal Display                                                     */
extern volatile const U1 u1_CALIB_MCUID0651_HUDNORM1;      /* HUD Normal Display 1                                                   */
extern volatile const U1 u1_CALIB_DUMMY_0007;              /* MCUCONST_v019 U2 MCUID0659 (MTS Normal Mode)                           */
extern volatile const U1 u1_CALIB_MCUID0660_XMODE;         /* X-MODE                                                                 */
extern volatile const U1 u1_CALIB_MCUID0661_OFFROAD_VIEW;  /* Off-Road-View                                                          */
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
extern volatile const U1 u1_CALIB_MCUID0797_CNST_WRITEFLG; /* Constant write flag                                                    */

extern volatile const U1 u1_CALIB_MCUID_DUM_1B_0221;       /* Deleted content 1B-0221(Presence of AT oil temperature)                */
extern volatile const U1 u1_CALIB_MCUID0611_BAROLPL;       /* barOLPL                                                                */
extern volatile const U1 u1_CALIB_MCUID0612_BAROLPH;       /* barOLPH                                                                */
extern volatile const U1 u1_CALIB_MCUID0914_SOLAR_CHARGE;  /* Solar charging ON/OFF Default                                          */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0326;       /* Reserve_1B-0326                                                        */
extern volatile const U1 u1_CALIB_MCUID1120_DESIGN_PTN;    /* Vehicle design pattern                                                 */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0328;       /* Reserve_1B-0328                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0329;       /* Reserve_1B-0329                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0330;       /* Reserve_1B-0330                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0331;       /* Reserve_1B-0331                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0332;       /* Reserve_1B-0332                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0333;       /* Reserve_1B-0333                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0334;       /* Reserve_1B-0334                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0335;       /* Reserve_1B-0335                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0336;       /* Reserve_1B-0336                                                        */
extern volatile const U1 u1_CALIB_MCUID0831_PITCH_MAX;     /* Angle of caution indication start (pitch)                              */
extern volatile const U1 u1_CALIB_MCUID0832_ROLL_MAX;      /* Angle of caution indication start (roll)                               */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0339;       /* Reserve_1B-0339                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0340;       /* Reserve_1B-0340                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0341;       /* Reserve_1B-0341                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0342;       /* Reserve_1B-0342                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0343;       /* Reserve_1B-0343                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0344;       /* Reserve_1B-0344                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0345;       /* Reserve_1B-0345                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0346;       /* Reserve_1B-0346                                                        */
extern volatile const U1 u1_CALIB_MCUID_DUM_1B_0347;       /* Deleted content 1B-0347(Boost pressure Upper boundary)                 */
extern volatile const U1 u1_CALIB_MCUID_DUM_1B_0348;       /* Deleted content 1B-0348(Boost pressure Lower boundary)                 */
extern volatile const U1 u1_CALIB_MCUID1115_BSTPR_S_TM;    /* Boost pressure Sampling time                                           */
extern volatile const U1 u1_CALIB_MCUID1116_BSTPR_N_AVE;   /* Boost pressure The number of averaging processing                      */
extern volatile const U1 u1_CALIB_MCUID1118_BSTPR_JDG;     /* Boost pressure function presence detection value                       */
extern volatile const U1 u1_CALIB_MCUID1119_MGPWR_JDG;     /* MG Gauge function presence detection value                             */
extern volatile const U1 u1_CALIB_MCUID1121_BSTPR_LOGO;    /* Boost gauge/MG gauge presence determination value                      */
extern volatile const U1 u1_CALIB_MCUID1117_I_EXHAUST_OP;  /* I_EXHAUST_OP                                                           */
extern volatile const U1 u1_CALIB_MCUID1123_M_GVIF_FLG;    /* M_GVIF_FLG                                                             */
extern volatile const U1 u1_CALIB_MCUID1122_AT_OIL_TEMP;   /* Presence of AT oil temperature indication function                     */
extern volatile const U1 u1_CALIB_MCUID1113_BSTPR_UP;      /* Boost pressure Upper boundary of gauge                                 */
extern volatile const U1 u1_CALIB_MCUID1114_BSTPR_LO;      /* Boost pressure Lower boundary of gauge                                 */
extern volatile const U1 u1_CALIB_MCUID1124_HUD_SIZE;      /* HUD Size                                                               */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0360;       /* Reserve_1B-0360                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0361;       /* Reserve_1B-0361                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0362;       /* Reserve_1B-0362                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0363;       /* Reserve_1B-0363                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0364;       /* Reserve_1B-0364                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0365;       /* Reserve_1B-0365                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0366;       /* Reserve_1B-0366                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0367;       /* Reserve_1B-0367                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0368;       /* Reserve_1B-0368                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0369;       /* Reserve_1B-0369                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0370;       /* Reserve_1B-0370                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0371;       /* Reserve_1B-0371                                                        */
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
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0757;       /* Reserve_1B-0757                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0758;       /* Reserve_1B-0758                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0759;       /* Reserve_1B-0759                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0760;       /* Reserve_1B-0760                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0761;       /* Reserve_1B-0761                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0762;       /* Reserve_1B-0762                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0763;       /* Reserve_1B-0763                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0764;       /* Reserve_1B-0764                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0765;       /* Reserve_1B-0765                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0766;       /* Reserve_1B-0766                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0767;       /* Reserve_1B-0767                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0768;       /* Reserve_1B-0768                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0769;       /* Reserve_1B-0769                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0770;       /* Reserve_1B-0770                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0771;       /* Reserve_1B-0771                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0772;       /* Reserve_1B-0772                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0773;       /* Reserve_1B-0773                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0774;       /* Reserve_1B-0774                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0775;       /* Reserve_1B-0775                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0776;       /* Reserve_1B-0776                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0777;       /* Reserve_1B-0777                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0778;       /* Reserve_1B-0778                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0779;       /* Reserve_1B-0779                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0780;       /* Reserve_1B-0780                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0781;       /* Reserve_1B-0781                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0782;       /* Reserve_1B-0782                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0783;       /* Reserve_1B-0783                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0784;       /* Reserve_1B-0784                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0785;       /* Reserve_1B-0785                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0786;       /* Reserve_1B-0786                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0787;       /* Reserve_1B-0787                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0788;       /* Reserve_1B-0788                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0789;       /* Reserve_1B-0789                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0790;       /* Reserve_1B-0790                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0791;       /* Reserve_1B-0791                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0792;       /* Reserve_1B-0792                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0793;       /* Reserve_1B-0793                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0794;       /* Reserve_1B-0794                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0795;       /* Reserve_1B-0795                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0796;       /* Reserve_1B-0796                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0797;       /* Reserve_1B-0797                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0798;       /* Reserve_1B-0798                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0799;       /* Reserve_1B-0799                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0800;       /* Reserve_1B-0800                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0801;       /* Reserve_1B-0801                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0802;       /* Reserve_1B-0802                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0803;       /* Reserve_1B-0803                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0804;       /* Reserve_1B-0804                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0805;       /* Reserve_1B-0805                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0806;       /* Reserve_1B-0806                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0807;       /* Reserve_1B-0807                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0808;       /* Reserve_1B-0808                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0809;       /* Reserve_1B-0809                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0810;       /* Reserve_1B-0810                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0811;       /* Reserve_1B-0811                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0812;       /* Reserve_1B-0812                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0813;       /* Reserve_1B-0813                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0814;       /* Reserve_1B-0814                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0815;       /* Reserve_1B-0815                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0816;       /* Reserve_1B-0816                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0817;       /* Reserve_1B-0817                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0818;       /* Reserve_1B-0818                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0819;       /* Reserve_1B-0819                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0820;       /* Reserve_1B-0820                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0821;       /* Reserve_1B-0821                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0822;       /* Reserve_1B-0822                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0823;       /* Reserve_1B-0823                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0824;       /* Reserve_1B-0824                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0825;       /* Reserve_1B-0825                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0826;       /* Reserve_1B-0826                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0827;       /* Reserve_1B-0827                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0828;       /* Reserve_1B-0828                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0829;       /* Reserve_1B-0829                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0830;       /* Reserve_1B-0830                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0831;       /* Reserve_1B-0831                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0832;       /* Reserve_1B-0832                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0833;       /* Reserve_1B-0833                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0834;       /* Reserve_1B-0834                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0835;       /* Reserve_1B-0835                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0836;       /* Reserve_1B-0836                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0837;       /* Reserve_1B-0837                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0838;       /* Reserve_1B-0838                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0839;       /* Reserve_1B-0839                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0840;       /* Reserve_1B-0840                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0841;       /* Reserve_1B-0841                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0842;       /* Reserve_1B-0842                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0843;       /* Reserve_1B-0843                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0844;       /* Reserve_1B-0844                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0845;       /* Reserve_1B-0845                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0846;       /* Reserve_1B-0846                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0847;       /* Reserve_1B-0847                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0848;       /* Reserve_1B-0848                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0849;       /* Reserve_1B-0849                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0850;       /* Reserve_1B-0850                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0851;       /* Reserve_1B-0851                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0852;       /* Reserve_1B-0852                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0853;       /* Reserve_1B-0853                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0854;       /* Reserve_1B-0854                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0855;       /* Reserve_1B-0855                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0856;       /* Reserve_1B-0856                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0857;       /* Reserve_1B-0857                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0858;       /* Reserve_1B-0858                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0859;       /* Reserve_1B-0859                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0860;       /* Reserve_1B-0860                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0861;       /* Reserve_1B-0861                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0862;       /* Reserve_1B-0862                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0863;       /* Reserve_1B-0863                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0864;       /* Reserve_1B-0864                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0865;       /* Reserve_1B-0865                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0866;       /* Reserve_1B-0866                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0867;       /* Reserve_1B-0867                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0868;       /* Reserve_1B-0868                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0869;       /* Reserve_1B-0869                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0870;       /* Reserve_1B-0870                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0871;       /* Reserve_1B-0871                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0872;       /* Reserve_1B-0872                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0873;       /* Reserve_1B-0873                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0874;       /* Reserve_1B-0874                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0875;       /* Reserve_1B-0875                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0876;       /* Reserve_1B-0876                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0877;       /* Reserve_1B-0877                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0878;       /* Reserve_1B-0878                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0879;       /* Reserve_1B-0879                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0880;       /* Reserve_1B-0880                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0881;       /* Reserve_1B-0881                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0882;       /* Reserve_1B-0882                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0883;       /* Reserve_1B-0883                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0884;       /* Reserve_1B-0884                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0885;       /* Reserve_1B-0885                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0886;       /* Reserve_1B-0886                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0887;       /* Reserve_1B-0887                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0888;       /* Reserve_1B-0888                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0889;       /* Reserve_1B-0889                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0890;       /* Reserve_1B-0890                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0891;       /* Reserve_1B-0891                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0892;       /* Reserve_1B-0892                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0893;       /* Reserve_1B-0893                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0894;       /* Reserve_1B-0894                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0895;       /* Reserve_1B-0895                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0896;       /* Reserve_1B-0896                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0897;       /* Reserve_1B-0897                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0898;       /* Reserve_1B-0898                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0899;       /* Reserve_1B-0899                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0900;       /* Reserve_1B-0900                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0901;       /* Reserve_1B-0901                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0902;       /* Reserve_1B-0902                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0903;       /* Reserve_1B-0903                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0904;       /* Reserve_1B-0904                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0905;       /* Reserve_1B-0905                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0906;       /* Reserve_1B-0906                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0907;       /* Reserve_1B-0907                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0908;       /* Reserve_1B-0908                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0909;       /* Reserve_1B-0909                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0910;       /* Reserve_1B-0910                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0911;       /* Reserve_1B-0911                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0912;       /* Reserve_1B-0912                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0913;       /* Reserve_1B-0913                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0914;       /* Reserve_1B-0914                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0915;       /* Reserve_1B-0915                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0916;       /* Reserve_1B-0916                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0917;       /* Reserve_1B-0917                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0918;       /* Reserve_1B-0918                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0919;       /* Reserve_1B-0919                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0920;       /* Reserve_1B-0920                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0921;       /* Reserve_1B-0921                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0922;       /* Reserve_1B-0922                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0923;       /* Reserve_1B-0923                                                        */
extern volatile const U1 u1_CALIB_MCUID_RSV_1B_0924;       /* Reserve_1B-0924                                                        */

extern volatile const U2 u2_CALIB_MCUID0915_CSR_RCTA_0;    /* RCTA buzzer CSR_VOL:0                                                  */
extern volatile const U2 u2_CALIB_MCUID0916_CSR_RCTA_1;    /* RCTA buzzer CSR_VOL:1                                                  */
extern volatile const U2 u2_CALIB_MCUID0917_CSR_RCTA_2;    /* RCTA buzzer CSR_VOL:2                                                  */
extern volatile const U2 u2_CALIB_MCUID0918_CSR_RCTA_3;    /* RCTA buzzer CSR_VOL:3                                                  */
extern volatile const U2 u2_CALIB_MCUID0919_CSR_RCTA_4;    /* RCTA buzzer CSR_VOL:4                                                  */
extern volatile const U2 u2_CALIB_MCUID0920_CSR_RCTA_5;    /* RCTA buzzer CSR_VOL:5                                                  */
extern volatile const U2 u2_CALIB_MCUID0921_CSR_RCTA_6;    /* RCTA buzzer CSR_VOL:6                                                  */
extern volatile const U2 u2_CALIB_MCUID0922_CSR_RCTA_7;    /* RCTA buzzer CSR_VOL:7                                                  */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0155;       /* Reserve_2B-0155                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0156;       /* Reserve_2B-0156                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0157;       /* Reserve_2B-0157                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0158;       /* Reserve_2B-0158                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0159;       /* Reserve_2B-0159                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0160;       /* Reserve_2B-0160                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0161;       /* Reserve_2B-0161                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0162;       /* Reserve_2B-0162                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0163;       /* Reserve_2B-0163                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0164;       /* Reserve_2B-0164                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0165;       /* Reserve_2B-0165                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0166;       /* Reserve_2B-0166                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0167;       /* Reserve_2B-0167                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0168;       /* Reserve_2B-0168                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0169;       /* Reserve_2B-0169                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0170;       /* Reserve_2B-0170                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0171;       /* Reserve_2B-0171                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0172;       /* Reserve_2B-0172                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0173;       /* Reserve_2B-0173                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0174;       /* Reserve_2B-0174                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0175;       /* Reserve_2B-0175                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0176;       /* Reserve_2B-0176                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0177;       /* Reserve_2B-0177                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0178;       /* Reserve_2B-0178                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0179;       /* Reserve_2B-0179                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0180;       /* Reserve_2B-0180                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0181;       /* Reserve_2B-0181                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0182;       /* Reserve_2B-0182                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0183;       /* Reserve_2B-0183                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0184;       /* Reserve_2B-0184                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0185;       /* Reserve_2B-0185                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0186;       /* Reserve_2B-0186                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0187;       /* Reserve_2B-0187                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0188;       /* Reserve_2B-0188                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0189;       /* Reserve_2B-0189                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0190;       /* Reserve_2B-0190                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0191;       /* Reserve_2B-0191                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0192;       /* Reserve_2B-0192                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0193;       /* Reserve_2B-0193                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0194;       /* Reserve_2B-0194                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0195;       /* Reserve_2B-0195                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0196;       /* Reserve_2B-0196                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0197;       /* Reserve_2B-0197                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0198;       /* Reserve_2B-0198                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0199;       /* Reserve_2B-0199                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0200;       /* Reserve_2B-0200                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0201;       /* Reserve_2B-0201                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0202;       /* Reserve_2B-0202                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0203;       /* Reserve_2B-0203                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0204;       /* Reserve_2B-0204                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0205;       /* Reserve_2B-0205                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0206;       /* Reserve_2B-0206                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0207;       /* Reserve_2B-0207                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0208;       /* Reserve_2B-0208                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0209;       /* Reserve_2B-0209                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0210;       /* Reserve_2B-0210                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0211;       /* Reserve_2B-0211                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0212;       /* Reserve_2B-0212                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0213;       /* Reserve_2B-0213                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0214;       /* Reserve_2B-0214                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0215;       /* Reserve_2B-0215                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0216;       /* Reserve_2B-0216                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0217;       /* Reserve_2B-0217                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0218;       /* Reserve_2B-0218                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0219;       /* Reserve_2B-0219                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0220;       /* Reserve_2B-0220                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0221;       /* Reserve_2B-0221                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0222;       /* Reserve_2B-0222                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0223;       /* Reserve_2B-0223                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0224;       /* Reserve_2B-0224                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0225;       /* Reserve_2B-0225                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0226;       /* Reserve_2B-0226                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0227;       /* Reserve_2B-0227                                                        */
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
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0820;       /* Reserve_2B-0820                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0821;       /* Reserve_2B-0821                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0822;       /* Reserve_2B-0822                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0823;       /* Reserve_2B-0823                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0824;       /* Reserve_2B-0824                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0825;       /* Reserve_2B-0825                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0826;       /* Reserve_2B-0826                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0827;       /* Reserve_2B-0827                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0828;       /* Reserve_2B-0828                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0829;       /* Reserve_2B-0829                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0830;       /* Reserve_2B-0830                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0831;       /* Reserve_2B-0831                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0832;       /* Reserve_2B-0832                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0833;       /* Reserve_2B-0833                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0834;       /* Reserve_2B-0834                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0835;       /* Reserve_2B-0835                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0836;       /* Reserve_2B-0836                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0837;       /* Reserve_2B-0837                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0838;       /* Reserve_2B-0838                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0839;       /* Reserve_2B-0839                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0840;       /* Reserve_2B-0840                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0841;       /* Reserve_2B-0841                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0842;       /* Reserve_2B-0842                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0843;       /* Reserve_2B-0843                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0844;       /* Reserve_2B-0844                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0845;       /* Reserve_2B-0845                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0846;       /* Reserve_2B-0846                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0847;       /* Reserve_2B-0847                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0848;       /* Reserve_2B-0848                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0849;       /* Reserve_2B-0849                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0850;       /* Reserve_2B-0850                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0851;       /* Reserve_2B-0851                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0852;       /* Reserve_2B-0852                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0853;       /* Reserve_2B-0853                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0854;       /* Reserve_2B-0854                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0855;       /* Reserve_2B-0855                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0856;       /* Reserve_2B-0856                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0857;       /* Reserve_2B-0857                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0858;       /* Reserve_2B-0858                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0859;       /* Reserve_2B-0859                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0860;       /* Reserve_2B-0860                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0861;       /* Reserve_2B-0861                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0862;       /* Reserve_2B-0862                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0863;       /* Reserve_2B-0863                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0864;       /* Reserve_2B-0864                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0865;       /* Reserve_2B-0865                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0866;       /* Reserve_2B-0866                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0867;       /* Reserve_2B-0867                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0868;       /* Reserve_2B-0868                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0869;       /* Reserve_2B-0869                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0870;       /* Reserve_2B-0870                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0871;       /* Reserve_2B-0871                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0872;       /* Reserve_2B-0872                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0873;       /* Reserve_2B-0873                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0874;       /* Reserve_2B-0874                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0875;       /* Reserve_2B-0875                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0876;       /* Reserve_2B-0876                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0877;       /* Reserve_2B-0877                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0878;       /* Reserve_2B-0878                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0879;       /* Reserve_2B-0879                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0880;       /* Reserve_2B-0880                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0881;       /* Reserve_2B-0881                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0882;       /* Reserve_2B-0882                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0883;       /* Reserve_2B-0883                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0884;       /* Reserve_2B-0884                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0885;       /* Reserve_2B-0885                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0886;       /* Reserve_2B-0886                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0887;       /* Reserve_2B-0887                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0888;       /* Reserve_2B-0888                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0889;       /* Reserve_2B-0889                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0890;       /* Reserve_2B-0890                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0891;       /* Reserve_2B-0891                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0892;       /* Reserve_2B-0892                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0893;       /* Reserve_2B-0893                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0894;       /* Reserve_2B-0894                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0895;       /* Reserve_2B-0895                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0896;       /* Reserve_2B-0896                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0897;       /* Reserve_2B-0897                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0898;       /* Reserve_2B-0898                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0899;       /* Reserve_2B-0899                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0900;       /* Reserve_2B-0900                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0901;       /* Reserve_2B-0901                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0902;       /* Reserve_2B-0902                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0903;       /* Reserve_2B-0903                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0904;       /* Reserve_2B-0904                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0905;       /* Reserve_2B-0905                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0906;       /* Reserve_2B-0906                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0907;       /* Reserve_2B-0907                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0908;       /* Reserve_2B-0908                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0909;       /* Reserve_2B-0909                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0910;       /* Reserve_2B-0910                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0911;       /* Reserve_2B-0911                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0912;       /* Reserve_2B-0912                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0913;       /* Reserve_2B-0913                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0914;       /* Reserve_2B-0914                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0915;       /* Reserve_2B-0915                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0916;       /* Reserve_2B-0916                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0917;       /* Reserve_2B-0917                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0918;       /* Reserve_2B-0918                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0919;       /* Reserve_2B-0919                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0920;       /* Reserve_2B-0920                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0921;       /* Reserve_2B-0921                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0922;       /* Reserve_2B-0922                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0923;       /* Reserve_2B-0923                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0924;       /* Reserve_2B-0924                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0925;       /* Reserve_2B-0925                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0926;       /* Reserve_2B-0926                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0927;       /* Reserve_2B-0927                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0928;       /* Reserve_2B-0928                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0929;       /* Reserve_2B-0929                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0930;       /* Reserve_2B-0930                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0931;       /* Reserve_2B-0931                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0932;       /* Reserve_2B-0932                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0933;       /* Reserve_2B-0933                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0934;       /* Reserve_2B-0934                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0935;       /* Reserve_2B-0935                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0936;       /* Reserve_2B-0936                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0937;       /* Reserve_2B-0937                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0938;       /* Reserve_2B-0938                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0939;       /* Reserve_2B-0939                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0940;       /* Reserve_2B-0940                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0941;       /* Reserve_2B-0941                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0942;       /* Reserve_2B-0942                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0943;       /* Reserve_2B-0943                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0944;       /* Reserve_2B-0944                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0945;       /* Reserve_2B-0945                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0946;       /* Reserve_2B-0946                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0947;       /* Reserve_2B-0947                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0948;       /* Reserve_2B-0948                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0949;       /* Reserve_2B-0949                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0950;       /* Reserve_2B-0950                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0951;       /* Reserve_2B-0951                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0952;       /* Reserve_2B-0952                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0953;       /* Reserve_2B-0953                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0954;       /* Reserve_2B-0954                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0955;       /* Reserve_2B-0955                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0956;       /* Reserve_2B-0956                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0957;       /* Reserve_2B-0957                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0958;       /* Reserve_2B-0958                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0959;       /* Reserve_2B-0959                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0960;       /* Reserve_2B-0960                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0961;       /* Reserve_2B-0961                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0962;       /* Reserve_2B-0962                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0963;       /* Reserve_2B-0963                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0964;       /* Reserve_2B-0964                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0965;       /* Reserve_2B-0965                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0966;       /* Reserve_2B-0966                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0967;       /* Reserve_2B-0967                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0968;       /* Reserve_2B-0968                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0969;       /* Reserve_2B-0969                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0970;       /* Reserve_2B-0970                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0971;       /* Reserve_2B-0971                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0972;       /* Reserve_2B-0972                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0973;       /* Reserve_2B-0973                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0974;       /* Reserve_2B-0974                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0975;       /* Reserve_2B-0975                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0976;       /* Reserve_2B-0976                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0977;       /* Reserve_2B-0977                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0978;       /* Reserve_2B-0978                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0979;       /* Reserve_2B-0979                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0980;       /* Reserve_2B-0980                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0981;       /* Reserve_2B-0981                                                        */
extern volatile const U2 u2_CALIB_MCUID_RSV_2B_0982;       /* Reserve_2B-0982                                                        */

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
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0061;       /* Reserve_4B-0061                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0062;       /* Reserve_4B-0062                                                        */
extern volatile const U4 u4_CALIB_MCUID_RSV_4B_0063;       /* Reserve_4B-0063                                                        */

extern volatile const U1 u1_CALIB_MCUID0270_RHEO_PCT[CALIB_MCUID0270_RHEO_STEP];              /* MCUID0270 to MCUID0291              */
extern volatile const U2 u2_CALIB_MCUID0292_TR2_PCT[CALIB_MCUID0292_TR2_STEP];                /* MCUID0292 to MCUID0313              */
extern volatile const U2 u2_CALIB_MCUID0314_IL2_PCT[CALIB_MCUID0314_IL2_STEP];                /* MCUID0314 to MCUID0335              */
extern volatile const U1 u1_CALIB_MCUID0342_BL_PCT_DAY[CALIB_MCUID0342_BL_STEP_DAY];          /* MCUID0342 to MCUID0363              */
extern volatile const U1 u1_CALIB_MCUID0364_RGB_ALPHA_DAY[CALIB_MCUID0364_RGB_STEP_DAY];      /* MCUID0364 to MCUID0385              */
extern volatile const U1 u1_CALIB_MCUID0386_BL_PCT_NIGHT[CALIB_MCUID0386_BL_STEP_NIGHT];      /* MCUID0386 to MCUID0407              */
extern volatile const U1 u1_CALIB_MCUID0408_RGB_ALPHA_NGT[CALIB_MCUID0408_RGB_STEP_NIGHT];    /* MCUID0408 to MCUID0429              */
extern volatile const U2 u2_CALIB_MCUID0433_FU_ANALITMA[CALIB_MCUID0433_FU_ANALITMA];         /* MCUID0433 to MCUID0450              */
extern volatile const U2 u2_CALIB_MCUID0451_FU_ANAVLTMA[CALIB_MCUID0451_FU_ANAVLTMA];         /* MCUID0451 to MCUID0468              */
extern volatile const U2 u2_CALIB_MCUID0469_FU_ANALITSU[CALIB_MCUID0469_FU_ANALITSU];         /* MCUID0469 to MCUID0486              */
extern volatile const U2 u2_CALIB_MCUID0487_FU_ANAVLTSU[CALIB_MCUID0487_FU_ANAVLTSU];         /* MCUID0487 to MCUID0504              */
extern volatile const U2 u2_CALIB_MCUID0757_SP_USA_CAN[CALIB_SP_TOLER_CORPT_NUM];             /* MCUID0757 to MCUID0776              */
extern volatile const U2 u2_CALIB_MCUID0777_SP_UNR_AUS[CALIB_SP_TOLER_CORPT_NUM];             /* MCUID0777 to MCUID0796              */

#endif
