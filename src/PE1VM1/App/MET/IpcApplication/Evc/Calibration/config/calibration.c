/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CALIBRATION                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CALIBRATION_C_MAJOR                     (1)
#define CALIBRATION_C_MINOR                     (0)
#define CALIBRATION_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata  = ".calibration_area"

#include "aip_common.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CALIBRATION_C_MAJOR != CALIBRATION_H_MAJOR) || \
     (CALIBRATION_C_MINOR != CALIBRATION_H_MINOR) || \
     (CALIBRATION_C_PATCH != CALIBRATION_H_PATCH))
#error "calibration.c and calibration.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
volatile const U1 u1_CALIB_MCUID0001_MCUID1        = (U1)48U;       /* MCU Software version No.1                                     */
volatile const U1 u1_CALIB_MCUID0002_MCUID2        = (U1)48U;       /* MCU Software version No.2                                     */
volatile const U1 u1_CALIB_MCUID0003_MCUID3        = (U1)48U;       /* MCU Software version No.3                                     */
volatile const U1 u1_CALIB_MCUID0004_MCUID4        = (U1)48U;       /* MCU Software version No.4                                     */
volatile const U1 u1_CALIB_MCUID0005_MCUID5        = (U1)48U;       /* MCU Software version No.5                                     */
volatile const U1 u1_CALIB_MCUID0006_MCUID6        = (U1)48U;       /* MCU Software version No.6                                     */
volatile const U1 u1_CALIB_MCUID0007_MCUID7        = (U1)48U;       /* MCU Software version No.7                                     */
volatile const U1 u1_CALIB_MCUID0008_MCUID8        = (U1)48U;       /* MCU Software version No.8                                     */
volatile const U1 u1_CALIB_MCUID0009_MCUID9        = (U1)48U;       /* MCU Software version No.9                                     */
volatile const U1 u1_CALIB_MCUID0010_MCUID10       = (U1)48U;       /* MCU Software version No.10                                    */
volatile const U1 u1_CALIB_MCUID0011_MCUID11       = (U1)33U;       /* MCU Software version No.11                                    */
volatile const U1 u1_CALIB_MCUID0012_MCUID12       = (U1)33U;       /* MCU Software version No.12                                    */
volatile const U1 u1_CALIB_MCUID0013_SPDID1        = (U1)32U;       /* Speed Meter ID No.1                                           */
volatile const U1 u1_CALIB_MCUID0014_SPDID2        = (U1)32U;       /* Speed Meter ID No.2                                           */
volatile const U1 u1_CALIB_MCUID0015_SPDID3        = (U1)32U;       /* Speed Meter ID No.3                                           */
volatile const U1 u1_CALIB_MCUID0016_SPDID4        = (U1)32U;       /* Speed Meter ID No.4                                           */
volatile const U1 u1_CALIB_MCUID0017_SPDID5        = (U1)32U;       /* Speed Meter ID No.5                                           */
volatile const U1 u1_CALIB_MCUID0018_SPDID6        = (U1)32U;       /* Speed Meter ID No.6                                           */
volatile const U1 u1_CALIB_MCUID0019_SPDID7        = (U1)32U;       /* Speed Meter ID No.7                                           */
volatile const U1 u1_CALIB_MCUID0020_SPDID8        = (U1)32U;       /* Speed Meter ID No.8                                           */
volatile const U1 u1_CALIB_MCUID0021_HUDSW         = (U1)0U;        /* HUD MAIN Hard SW                                              */
volatile const U1 u1_CALIB_MCUID0022_FU_MA         = (U1)0U;        /* Fuel Main Sender                                              */
volatile const U1 u1_CALIB_MCUID0023_DISPTYPE      = (U1)0U;        /* Display Type                                                  */
volatile const U1 u1_CALIB_MCUID0024_BRAND         = (U1)0U;        /* Brand                                                         */
volatile const U1 u1_CALIB_MCUID0025_SPORTS        = (U1)0U;        /* Sports Switching                                              */
volatile const U1 u1_CALIB_MCUID0026_1MOTHV        = (U1)1U;        /* 1MOT HV Drive Wheel                                           */
volatile const U1 u1_CALIB_MCUID0027_ATR_MID       = (U1)40U;       /* AT reverse buzzer MID                                         */
volatile const U1 u1_CALIB_MCUID0744_ATR_MAX       = (U1)50U;       /* AT reverse buzzer MAX                                         */
volatile const U1 u1_CALIB_MCUID0028_SBW_SI_MID    = (U1)40U;       /* SBW reverse buzzer Single MID                                 */
volatile const U1 u1_CALIB_MCUID0745_SBW_SI_MAX    = (U1)50U;       /* SBW reverse buzzer Single MAX                                 */
volatile const U1 u1_CALIB_MCUID0029_SBW_IN_MID    = (U1)40U;       /* SBW reverse buzzer Intermittent MID                           */
volatile const U1 u1_CALIB_MCUID0746_SBW_IN_MAX    = (U1)50U;       /* SBW reverse buzzer Intermittent MAX                           */
volatile const U1 u1_CALIB_MCUID0030_SBELT_FMV_MID = (U1)40U;       /* seatbelt reminder buzzer(fmv) MID                             */
volatile const U1 u1_CALIB_MCUID0747_SBELT_FMV_MAX = (U1)50U;       /* seatbelt reminder buzzer(fmv) MAX                             */
volatile const U1 u1_CALIB_MCUID0031_SBELT_LV1_MID = (U1)40U;       /* seatbelt reminder buzzer(level 1) MID                         */
volatile const U1 u1_CALIB_MCUID0748_SBELT_LV1_MAX = (U1)50U;       /* seatbelt reminder buzzer(level 1) MAX                         */
volatile const U1 u1_CALIB_MCUID0032_SBELT_LV2_MID = (U1)40U;       /* seatbelt reminder buzzer(level 2) MID                         */
volatile const U1 u1_CALIB_MCUID0749_SBELT_LV2_MAX = (U1)50U;       /* seatbelt reminder buzzer(level 2) MAX                         */
volatile const U1 u1_CALIB_MCUID0033_SBELT_SI_MID  = (U1)40U;       /* seatbelt reminder buzzer(si) MID                              */
volatile const U1 u1_CALIB_MCUID0750_SBELT_SI_MAX  = (U1)50U;       /* seatbelt reminder buzzer(si) MAX                              */
volatile const U1 u1_CALIB_MCUID0034_MC_MIN        = (U1)35U;       /* Master Caution MIN                                            */
volatile const U1 u1_CALIB_MCUID0035_MC_MID        = (U1)40U;       /* Master Caution MID                                            */
volatile const U1 u1_CALIB_MCUID0036_MC_MAX        = (U1)50U;       /* Master Caution MAX                                            */
volatile const U1 u1_CALIB_MCUID0037_ACC_MID       = (U1)40U;       /* ACC Auto Start MID                                            */
volatile const U1 u1_CALIB_MCUID0751_ACC_MAX       = (U1)50U;       /* ACC Auto Start MAX                                            */
volatile const U1 u1_CALIB_MCUID0038_TMN_MID       = (U1)40U;       /* TMN MID                                                       */
volatile const U1 u1_CALIB_MCUID0752_TMN_MAX       = (U1)50U;       /* TMN MAX                                                       */
volatile const U1 u1_CALIB_MCUID0039_ADAS_MID      = (U1)40U;       /* ADAS MID                                                      */
volatile const U1 u1_CALIB_MCUID0753_ADAS_MAX      = (U1)50U;       /* ADAS MAX                                                      */
volatile const U1 u1_CALIB_MCUID0067_CSR_FRSD0     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0068_CSR_FRSD1     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0069_CSR_FRSD2     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0070_CSR_FRSD3     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0071_CSR_FRSD4     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0072_CSR_FRSD5     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0073_CSR_FRSD6     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0074_CSR_FRSD7     = (U1)40U;       /* Clearance sonar buzzer Fr(SD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0075_CSR_FRMD0     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0076_CSR_FRMD1     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0077_CSR_FRMD2     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0078_CSR_FRMD3     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0079_CSR_FRMD4     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0080_CSR_FRMD5     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0081_CSR_FRMD6     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0082_CSR_FRMD7     = (U1)40U;       /* Clearance sonar buzzer Fr(MD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0083_CSR_FRLD0     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0084_CSR_FRLD1     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0085_CSR_FRLD2     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0086_CSR_FRLD3     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0087_CSR_FRLD4     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0088_CSR_FRLD5     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0089_CSR_FRLD6     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0090_CSR_FRLD7     = (U1)40U;       /* Clearance sonar buzzer Fr(LD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0091_CSR_FRFD0     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0092_CSR_FRFD1     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0093_CSR_FRFD2     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0094_CSR_FRFD3     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0095_CSR_FRFD4     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0096_CSR_FRFD5     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0097_CSR_FRFD6     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0098_CSR_FRFD7     = (U1)40U;       /* Clearance sonar buzzer Fr(FD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0099_CSR_RRSD0     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0100_CSR_RRSD1     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0101_CSR_RRSD2     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0102_CSR_RRSD3     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0103_CSR_RRSD4     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0104_CSR_RRSD5     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0105_CSR_RRSD6     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0106_CSR_RRSD7     = (U1)40U;       /* Clearance sonar buzzer Rr(SD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0107_CSR_RRMD0     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0108_CSR_RRMD1     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0109_CSR_RRMD2     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0110_CSR_RRMD3     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0111_CSR_RRMD4     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0112_CSR_RRMD5     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0113_CSR_RRMD6     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0114_CSR_RRMD7     = (U1)40U;       /* Clearance sonar buzzer Rr(MD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0115_CSR_RRLD0     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0116_CSR_RRLD1     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0117_CSR_RRLD2     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0118_CSR_RRLD3     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0119_CSR_RRLD4     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0120_CSR_RRLD5     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0121_CSR_RRLD6     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0122_CSR_RRLD7     = (U1)40U;       /* Clearance sonar buzzer Rr(LD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0123_CSR_RRFD0     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:0                       */
volatile const U1 u1_CALIB_MCUID0124_CSR_RRFD1     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:1                       */
volatile const U1 u1_CALIB_MCUID0125_CSR_RRFD2     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:2                       */
volatile const U1 u1_CALIB_MCUID0126_CSR_RRFD3     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:3                       */
volatile const U1 u1_CALIB_MCUID0127_CSR_RRFD4     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:4                       */
volatile const U1 u1_CALIB_MCUID0128_CSR_RRFD5     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:5                       */
volatile const U1 u1_CALIB_MCUID0129_CSR_RRFD6     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:6                       */
volatile const U1 u1_CALIB_MCUID0130_CSR_RRFD7     = (U1)40U;       /* Clearance sonar buzzer Rr(FD) CSR_VOL:7                       */
volatile const U1 u1_CALIB_MCUID0131_CSR_FRRRSD0   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0                    */
volatile const U1 u1_CALIB_MCUID0132_CSR_FRRRSD1   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1                    */
volatile const U1 u1_CALIB_MCUID0133_CSR_FRRRSD2   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2                    */
volatile const U1 u1_CALIB_MCUID0134_CSR_FRRRSD3   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3                    */
volatile const U1 u1_CALIB_MCUID0135_CSR_FRRRSD4   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4                    */
volatile const U1 u1_CALIB_MCUID0136_CSR_FRRRSD5   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5                    */
volatile const U1 u1_CALIB_MCUID0137_CSR_FRRRSD6   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6                    */
volatile const U1 u1_CALIB_MCUID0138_CSR_FRRRSD7   = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7                    */
volatile const U1 u1_CALIB_MCUID0139_CSR_FRRRFRMD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0140_CSR_FRRRFRMD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0141_CSR_FRRRFRMD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0142_CSR_FRRRFRMD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0143_CSR_FRRRFRMD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0144_CSR_FRRRFRMD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0145_CSR_FRRRFRMD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0146_CSR_FRRRFRMD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(MD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0147_CSR_FRRRRRMD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0148_CSR_FRRRRRMD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0149_CSR_FRRRRRMD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0150_CSR_FRRRRRMD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0151_CSR_FRRRRRMD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0152_CSR_FRRRRRMD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0153_CSR_FRRRRRMD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0154_CSR_FRRRRRMD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(MD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0155_CSR_FRRRFRLD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0156_CSR_FRRRFRLD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0157_CSR_FRRRFRLD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0158_CSR_FRRRFRLD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0159_CSR_FRRRFRLD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0160_CSR_FRRRFRLD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0161_CSR_FRRRFRLD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0162_CSR_FRRRFRLD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(LD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0163_CSR_FRRRRRLD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0164_CSR_FRRRRRLD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0165_CSR_FRRRRRLD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0166_CSR_FRRRRRLD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0167_CSR_FRRRRRLD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0168_CSR_FRRRRRLD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0169_CSR_FRRRRRLD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0170_CSR_FRRRRRLD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(LD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0171_CSR_FRRRFRFD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0172_CSR_FRRRFRFD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0173_CSR_FRRRFRFD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0174_CSR_FRRRFRFD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0175_CSR_FRRRFRFD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0176_CSR_FRRRFRFD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0177_CSR_FRRRFRFD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0178_CSR_FRRRFRFD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(FR)(FD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0179_CSR_FRRRRRFD0 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:0                */
volatile const U1 u1_CALIB_MCUID0180_CSR_FRRRRRFD1 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:1                */
volatile const U1 u1_CALIB_MCUID0181_CSR_FRRRRRFD2 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:2                */
volatile const U1 u1_CALIB_MCUID0182_CSR_FRRRRRFD3 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:3                */
volatile const U1 u1_CALIB_MCUID0183_CSR_FRRRRRFD4 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:4                */
volatile const U1 u1_CALIB_MCUID0184_CSR_FRRRRRFD5 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:5                */
volatile const U1 u1_CALIB_MCUID0185_CSR_FRRRRRFD6 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:6                */
volatile const U1 u1_CALIB_MCUID0186_CSR_FRRRRRFD7 = (U1)40U;       /* Clearance sonar buzzer Fr+Rr(RR)(FD) CSR_VOL:7                */
volatile const U1 u1_CALIB_MCUID0187_FLSTA_LOLO    = (U1)40U;       /* flasher start sound(low customize, low speed)                 */
volatile const U1 u1_CALIB_MCUID0188_FLSTA_LOMI    = (U1)40U;       /* flasher start sound(low customize, mid speed)                 */
volatile const U1 u1_CALIB_MCUID0189_FLSTA_LOHI    = (U1)40U;       /* flasher start sound(low customize, high speed)                */
volatile const U1 u1_CALIB_MCUID0190_FLSTA_MILO    = (U1)40U;       /* flasher start sound(mid customize, low speed)                 */
volatile const U1 u1_CALIB_MCUID0191_FLSTA_MIMI    = (U1)40U;       /* flasher start sound(mid customize, mid speed)                 */
volatile const U1 u1_CALIB_MCUID0192_FLSTA_MIHI    = (U1)40U;       /* flasher start sound(mid customize, high speed)                */
volatile const U1 u1_CALIB_MCUID0193_FLSTA_HILO    = (U1)40U;       /* flasher start sound(high customize, low speed)                */
volatile const U1 u1_CALIB_MCUID0194_FLSTA_HIMI    = (U1)40U;       /* flasher start sound(high customize, mid speed)                */
volatile const U1 u1_CALIB_MCUID0195_FLSTA_HIHI    = (U1)40U;       /* flasher start sound(high customize, high speed)               */
volatile const U1 u1_CALIB_MCUID0196_FLFIN_LOLO    = (U1)40U;       /* flasher finish sound(low customize, low speed)                */
volatile const U1 u1_CALIB_MCUID0197_FLFIN_LOMI    = (U1)40U;       /* flasher finish sound(low customize, mid speed)                */
volatile const U1 u1_CALIB_MCUID0198_FLFIN_LOHI    = (U1)40U;       /* flasher finish sound(low customize, high speed)               */
volatile const U1 u1_CALIB_MCUID0199_FLFIN_MILO    = (U1)40U;       /* flasher finish sound(mid customize, low speed)                */
volatile const U1 u1_CALIB_MCUID0200_FLFIN_MIMI    = (U1)40U;       /* flasher finish sound(mid customize, mid speed)                */
volatile const U1 u1_CALIB_MCUID0201_FLFIN_MIHI    = (U1)40U;       /* flasher finish sound(mid customize, high speed)               */
volatile const U1 u1_CALIB_MCUID0202_FLFIN_HILO    = (U1)40U;       /* flasher finish sound(high customize, low speed)               */
volatile const U1 u1_CALIB_MCUID0203_FLFIN_HIMI    = (U1)40U;       /* flasher finish sound(high customize, mid speed)               */
volatile const U1 u1_CALIB_MCUID0204_FLFIN_HIHI    = (U1)40U;       /* flasher finish sound(high customize, high speed)              */
volatile const U1 u1_CALIB_MCUID0205_2CH           = (U1)40U;       /* 2 channels multiplex playing                                  */
volatile const U1 u1_CALIB_MCUID0206_3CH           = (U1)40U;       /* 3 channels multiplex playing                                  */
volatile const U1 u1_CALIB_MCUID0207_4CH           = (U1)40U;       /* 4 channels multiplex playing                                  */
volatile const U1 u1_CALIB_MCUID0208_5CH           = (U1)40U;       /* 5 channels multiplex playing                                  */
volatile const U1 u1_CALIB_MCUID0209_RRCYM         = (U1)0U;        /* RRCYM                                                         */
volatile const U1 u1_CALIB_MCUID0210_RLCYM         = (U1)0U;        /* RLCYM                                                         */
volatile const U1 u1_CALIB_MCUID0211_BCTYM         = (U1)0U;        /* BCTYM                                                         */
volatile const U1 u1_CALIB_MCUID0212_LGCYM         = (U1)0U;        /* LGCYM                                                         */
volatile const U1 u1_CALIB_MCUID0213_HDCY_BDBM     = (U1)0U;        /* HDCY_BDBM                                                     */
volatile const U1 u1_CALIB_MCUID0214_RPSDWARNM     = (U1)0U;        /* RPSDWARNM                                                     */
volatile const U1 u1_CALIB_MCUID0215_LPSDWARNM     = (U1)0U;        /* LPSDWARNM                                                     */
volatile const U1 u1_CALIB_MCUID0217_STR_ANG       = (U1)57U;       /* steering angle gauge                                          */
volatile const U1 u1_CALIB_MCUID0218_ACCELERATOR   = (U1)65U;       /* accelerator brake                                             */
volatile const U1 u1_CALIB_MCUID0219_G_GAUGE_MAX   = (U1)8U;        /* G_Gauge MAX                                                   */
volatile const U1 u1_CALIB_MCUID0220_GTRAJECTORY2  = (U1)0U;        /* GTrajectory2                                                  */
volatile const U1 u1_CALIB_MCUID0221_G_DISP_MAX    = (U1)8U;        /* G_Display MAX                                                 */
volatile const U1 u1_CALIB_MCUID0222_P_SEATSW      = (U1)0U;        /* P Seat Senser SW                                              */
volatile const U1 u1_CALIB_MCUID0223_FRCTR_SEATSW  = (U1)0U;        /* FrCtr Seat Senser SW                                          */
volatile const U1 u1_CALIB_MCUID0224_RR_SEATSW     = (U1)0U;        /* RR Seat Senser SW                                             */
volatile const U1 u1_CALIB_MCUID0225_RC_SEATSW     = (U1)0U;        /* RC Seat Senser SW                                             */
volatile const U1 u1_CALIB_MCUID0226_RL_SEATSW     = (U1)0U;        /* RL Seat Senser SW                                             */
volatile const U1 u1_CALIB_MCUID0227_RR2_SEATSW    = (U1)0U;        /* RR2 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0228_RC2_SEATSW    = (U1)0U;        /* RC2 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0229_RL2_SEATSW    = (U1)0U;        /* RL2 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0230_RR3_SEATSW    = (U1)0U;        /* RR3 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0231_RC3_SEATSW    = (U1)0U;        /* RC3 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0232_RL3_SEATSW    = (U1)0U;        /* RL3 Seat Senser SW                                            */
volatile const U1 u1_CALIB_MCUID0233_RDOOR         = (U1)1U;        /* Rear Seat Door                                                */
volatile const U1 u1_CALIB_MCUID0234_WALKTHROUGH   = (U1)0U;        /* Walkthrough                                                   */
volatile const U1 u1_CALIB_MCUID0235_BODYSHAPE     = (U1)7U;        /* Bodyshape                                                     */
volatile const U1 u1_CALIB_MCUID0236_NOOPTTM       = (U1)16U;       /* NoOptTm                                                       */
volatile const U1 u1_CALIB_MCUID0237_CANMOVEFLAG   = (U1)1U;        /* NE1 or RDYIND                                                 */
volatile const U1 u1_CALIB_MCUID0238_XVMODE        = (U1)0U;        /* XV Mode                                                       */
volatile const U2 u2_CALIB_MCUID0239_FULFUL        = (U2)5500U;     /* FulFul                                                        */
volatile const U2 u2_CALIB_MCUID0240_FULMENP       = (U2)550U;      /* FulMEnp                                                       */
volatile const U4 u4_CALIB_MCUID0241_FULEFF        = (U4)21600U;    /* FulEff                                                        */
volatile const U1 u1_CALIB_MCUID0242_DDFFUCE       = (U1)100U;      /* DDFFuCe                                                       */
volatile const U1 u1_CALIB_MCUID0243_DKHCOEF       = (U1)100U;      /* DKHCoef                                                       */
volatile const U4 u4_CALIB_MCUID0244_EFFUPR        = (U4)32400U;    /* EFFUPR                                                        */
volatile const U4 u4_CALIB_MCUID0245_EFFLOW        = (U4)14472U;    /* EFFLOW                                                        */
volatile const U1 u1_CALIB_MCUID0246_FULCOEF       = (U1)98U;       /* FulCoef                                                       */
volatile const U1 u1_CALIB_MCUID0247_GCOEFM        = (U1)50U;       /* GCoefM                                                        */
volatile const U1 u1_CALIB_MCUID0248_GCOEFC        = (U1)100U;      /* GcoefC                                                        */
volatile const U1 u1_CALIB_MCUID0249_GCOEFP        = (U1)200U;      /* GCoefP                                                        */
volatile const U1 u1_CALIB_MCUID0250_FE_CONV       = (U1)3U;        /* fuel efficiency CONV                                          */
volatile const U1 u1_CALIB_MCUID0251_FE_HV         = (U1)4U;        /* fuel efficiency HV                                            */
volatile const U1 u1_CALIB_MCUID0252_FE_PHV        = (U1)4U;        /* fuel efficiency PHV                                           */
volatile const U1 u1_CALIB_MCUID0253_FE_FC         = (U1)2U;        /* fuel efficiency FC                                            */
volatile const U1 u1_CALIB_MCUID0254_PE_PHV        = (U1)2U;        /* power expense PHV                                             */
volatile const U1 u1_CALIB_MCUID0255_PE_EV         = (U1)2U;        /* power expense EV                                              */
volatile const U1 u1_CALIB_MCUID0256_TOLA_USA_CAN  = (U1)48U;       /* TOLER_A USA/CANADA                                            */
volatile const S1 s1_CALIB_MCUID0257_TOLB_USA_CAN  = (S1)1;         /* TOLER_B USA/CANADA                                            */
volatile const U1 u1_CALIB_MCUID0260_TOLA_UNR_AUS  = (U1)44U;       /* TOLER_A UNR/AUS                                               */
volatile const S1 s1_CALIB_MCUID0261_TOLB_UNR_AUS  = (S1)4;         /* TOLER_B UNR/AUS                                               */
volatile const U2 u2_CALIB_MCUID0262_MAXSPEED_KM   = (U2)180U;      /* Max Speed km                                                  */
volatile const U2 u2_CALIB_MCUID0263_MAXSPEED_MPH  = (U2)160U;      /* Max Speed mph                                                 */
volatile const U1 u1_CALIB_MCUID0264_FSPO          = (U1)0U;        /* Fspo                                                          */
volatile const U1 u1_CALIB_MCUID0265_REVIND        = (U1)0U;        /* REVIND                                                        */
volatile const U2 u2_CALIB_MCUID0266_REVINIT       = (U2)3000U;     /* RevInit                                                       */
volatile const U1 u1_CALIB_MCUID0267_REVLSB        = (U1)2U;        /* RevLSB                                                        */
volatile const U1 u1_CALIB_MCUID0268_SWNUM         = (U1)2U;        /* SWnum                                                         */
volatile const U1 u1_CALIB_MCUID0269_SWPOSI        = (U1)2U;        /* SWposi                                                        */
volatile const U1 u1_CALIB_MCUID0336_ILLOF_LV      = (U1)0U;        /* ILL_OF Level                                                  */
volatile const U1 u1_CALIB_MCUID0337_ILLOF_CAN_LV  = (U1)1U;        /* ILL_OF Cancel Level                                           */
volatile const U1 u1_CALIB_MCUID0338_EXDIMOUT      = (U1)1U;        /* external dimming output                                       */
volatile const U1 u1_CALIB_MCUID0339_EXDIMOUT_SPD  = (U1)1U;        /* external dimming output(vehicle speed linkage)                */
volatile const U1 u1_CALIB_MCUID0340_RHEOPOS_NIGHT = (U1)10U;       /* Rheostat Position Night                                       */
volatile const U1 u1_CALIB_MCUID0341_TAIL          = (U1)1U;        /* TAIL Apply                                                    */
volatile const U1 u1_CALIB_MCUID0430_RHEOSW        = (U1)1U;        /* Rheostat SW Apply                                             */
volatile const U1 u1_CALIB_MCUID0432_LIDINFO       = (U1)1U;        /* LSTM or LST1                                                  */
volatile const U1 u1_CALIB_MCUID0557_SHTJDG        = (U1)0U;        /* ShtJdg                                                        */
volatile const U1 u1_CALIB_MCUID0558_FSTYPE        = (U1)0U;        /* FStype                                                        */
volatile const U2 u2_CALIB_MCUID0559_FOPEN         = (U2)630U;      /* FOpen                                                         */
volatile const U1 u1_CALIB_MCUID0560_ATCALNUM      = (U1)128U;      /* ATCaluNum                                                     */
volatile const U2 u2_CALIB_MCUID0561_STPJDG        = (U2)100U;      /* StpJdg                                                        */
volatile const U2 u2_CALIB_MCUID0562_LUBJDGPN      = (U2)200U;      /* LubJdgPN                                                      */
volatile const U2 u2_CALIB_MCUID0563_LUBJDGPL      = (U2)200U;      /* LubJdgPL                                                      */
volatile const U2 u2_CALIB_MCUID0564_UPDATEJDG     = (U2)1500U;     /* UpdateJdg                                                     */
volatile const U2 u2_CALIB_MCUID0565_REMWRNON      = (U2)825U;      /* RemWrnOn                                                      */
volatile const U2 u2_CALIB_MCUID0566_FC_HOSEI      = (U2)110U;      /* FC_Hosei                                                      */
volatile const U2 u2_CALIB_MCUID0567_AUTOSTOPL     = (U2)5141U;     /* AutoSTOPL                                                     */
volatile const U2 u2_CALIB_MCUID0568_MINJUDGEL     = (U2)200U;      /* MinjudgeL                                                     */
volatile const U2 u2_CALIB_MCUID0569_NSLTNKSP      = (U2)0U;        /* NslTnkSP                                                      */
volatile const U1 u1_CALIB_MCUID0570_KMINVAL       = (U1)0U;        /* Kminval                                                       */
volatile const U1 u1_CALIB_MCUID0571_KMAXVAL       = (U1)100U;      /* Kmaxval                                                       */
volatile const U1 u1_CALIB_MCUID0572_FU_PORTPOS    = (U1)0U;        /* Fuel Port Position                                            */
volatile const U1 u1_CALIB_MCUID0573_FU_SU         = (U1)0U;        /* Fuel Sub Sender                                               */
volatile const U2 u2_CALIB_MCUID0574_CAL_DEF       = (U2)2050U;     /* CAL_DEF                                                       */
volatile const U2 u2_CALIB_MCUID0575_CAL_MIN       = (U2)2020U;     /* CAL_MIN                                                       */
volatile const U1 u1_CALIB_MCUID0576_DEGCW         = (U1)24U;       /* DegCW                                                         */
volatile const U1 u1_CALIB_MCUID0577_DEGCCW        = (U1)231U;      /* DegCCW                                                        */
volatile const U1 u1_CALIB_MCUID0578_DEG_RTSTEP    = (U1)24U;       /* Deg_RTStep                                                    */
volatile const U1 u1_CALIB_MCUID0579_RESTIME       = (U1)30U;       /* ResTime                                                       */
volatile const U1 u1_CALIB_MCUID0580_ACONMVAVECNT  = (U1)100U;      /* ACon_MvAveCnt                                                 */
volatile const U1 u1_CALIB_MCUID0581_ACONUPAVECNT  = (U1)8U;        /* ACon_UpAveCnt                                                 */
volatile const U1 u1_CALIB_MCUID0582_ACONDNAVECNT  = (U1)2U;        /* ACon_DnAveCnt                                                 */
volatile const U1 u1_CALIB_MCUID0583_ATSSAORNA     = (U1)1U;        /* ATss_AorNA                                                    */
volatile const U1 u1_CALIB_MCUID0584_ATSSUPAVECNT  = (U1)8U;        /* ATss_UpAveCnt                                                 */
volatile const U1 u1_CALIB_MCUID0585_ATSSDNAVECNT  = (U1)2U;        /* ATss_DnAveCnt                                                 */
volatile const U1 u1_CALIB_MCUID0586_HUDLMAVECNT   = (U1)32U;       /* HUDLm_AveCnt                                                  */
volatile const U1 u1_CALIB_MCUID0588_OM_MLG        = (U1)1U;        /* OM_MLG                                                        */
volatile const U1 u1_CALIB_MCUID0589_PR_OM_FL      = (U1)1U;        /* PR_OM_FL                                                      */
volatile const U1 u1_CALIB_MCUID0590_SOC_PORTPOS   = (U1)0U;        /* SOC Port Position                                             */
volatile const U1 u1_CALIB_MCUID0591_UREA          = (U1)0U;        /* UREA Apply                                                    */
volatile const U1 u1_CALIB_MCUID0592_SBELT_TT      = (U1)1U;        /* SeatBelt Reminder Telltale Type                               */
volatile const U1 u1_CALIB_MCUID0593_ATTEMP_LO     = (U1)80U;       /* ATTEMP_LO                                                     */
volatile const U1 u1_CALIB_MCUID0594_ATTEMP_MIDL   = (U1)140U;      /* ATTEMP_MIDL                                                   */
volatile const U1 u1_CALIB_MCUID0595_ATTEMP_MIDH   = (U1)140U;      /* ATTEMP_MIDH                                                   */
volatile const U1 u1_CALIB_MCUID0596_ATTEMP_HI     = (U1)200U;      /* ATTEMP_HI                                                     */
volatile const U1 u1_CALIB_MCUID0597_FLASHSTART    = (U1)175U;      /* Flash_Start                                                   */
volatile const U1 u1_CALIB_MCUID0598_FLASHSTOP     = (U1)174U;      /* Flash_Stop                                                    */
volatile const U1 u1_CALIB_MCUID0599_RZSTART       = (U1)175U;      /* Red_Zone_Start                                                */
volatile const U1 u1_CALIB_MCUID0600_ATTEMPVAL_LO  = (U1)0U;        /* ATTEMPVAL_LO                                                  */
volatile const U1 u1_CALIB_MCUID0601_ATTEMPVAL_HI  = (U1)200U;      /* ATTEMPVAL_HI                                                  */
volatile const U1 u1_CALIB_MCUID0602_LAUNCHTIME    = (U1)6U;        /* LAUNCH_Time                                                   */
volatile const U1 u1_CALIB_MCUID0603_SBELT_USA     = (U1)0U;        /* SeatBelt Regulation USA                                       */
volatile const U1 u1_CALIB_MCUID0604_SBELT_MEXICO  = (U1)0U;        /* SeatBelt Regulation MEXICO                                    */
volatile const U1 u1_CALIB_MCUID0605_SBELT_EU      = (U1)1U;        /* SeatBelt Regulation EU                                        */
volatile const U1 u1_CALIB_MCUID0606_SBELT_KOREA   = (U1)0U;        /* SeatBelt Regulation KOREA                                     */
volatile const U1 u1_CALIB_MCUID0607_SBELT_CHINA   = (U1)2U;        /* SeatBelt Regulation CHINA                                     */
volatile const U2 u2_CALIB_MCUID0608_OLPTLP        = (U2)253U;      /* OLPtlP                                                        */
volatile const U2 u2_CALIB_MCUID0609_KPAOLPL       = (U2)0U;        /* kPaOLPL                                                       */
volatile const U2 u2_CALIB_MCUID0610_KPAOLPH       = (U2)80U;       /* kPaOLPH                                                       */
volatile const U2 u2_CALIB_MCUID0611_BAROLPL       = (U2)0U;        /* barOLPL                                                       */
volatile const U2 u2_CALIB_MCUID0612_BAROLPH       = (U2)80U;       /* barOLPH                                                       */
volatile const U2 u2_CALIB_MCUID0613_PSIOLPL       = (U2)0U;        /* psiOLPL                                                       */
volatile const U2 u2_CALIB_MCUID0614_PSIOLPH       = (U2)116U;      /* psiOLPH                                                       */
volatile const U1 u1_CALIB_MCUID0653_KPAOLPMAX     = (U1)80U;       /* kPaOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0654_KPAOLPMIN     = (U1)0U;        /* kPaOLPMin                                                     */
volatile const U1 u1_CALIB_MCUID0655_BAROLPMAX     = (U1)80U;       /* barOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0656_BAROLPMIN     = (U1)0U;        /* barOLPMin                                                     */
volatile const U1 u1_CALIB_MCUID0657_PSIOLPMAX     = (U1)116U;      /* psiOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0658_PSIOLPMIN     = (U1)0U;        /* psiOLPMin                                                     */
volatile const U2 u2_CALIB_MCUID0622_OLTTLP        = (U2)253U;      /* OLTtlP                                                        */
volatile const U1 u1_CALIB_MCUID0623_OLTTLC        = (U1)40U;       /* OLTtlC                                                        */
volatile const U1 u1_CALIB_MCUID0624_OLTTLH        = (U1)160U;      /* OLTtlH                                                        */
volatile const U2 u2_CALIB_MCUID0625_OLTMAXC       = (U2)200U;      /* OLTMaxC                                                       */
volatile const U2 u2_CALIB_MCUID0626_OLTMINC       = (U2)0U;        /* OLTMinC                                                       */
volatile const U2 u2_CALIB_MCUID0627_OLTMAXF       = (U2)360U;      /* OLTMaxF                                                       */
volatile const U2 u2_CALIB_MCUID0628_OLTMINF       = (U2)0U;        /* OLTMinF                                                       */
volatile const U1 u1_CALIB_MCUID0629_HYS           = (U1)1U;        /* hys                                                           */
volatile const U2 u2_CALIB_MCUID0630_TTLP          = (U2)253U;      /* TtlP                                                          */
volatile const U1 u1_CALIB_MCUID0631_TTLC          = (U1)65U;       /* TtlC                                                          */
volatile const U1 u1_CALIB_MCUID0632_TTLH          = (U1)125U;      /* TtlH                                                          */
volatile const U2 u2_CALIB_MCUID0633_TTLMAXC       = (U2)180U;      /* TtlMaxC                                                       */
volatile const U2 u2_CALIB_MCUID0634_TTLMINC       = (U2)0U;        /* TtlMinC                                                       */
volatile const U2 u2_CALIB_MCUID0635_TTLMAXF       = (U2)324U;      /* TtlMaxF                                                       */
volatile const U2 u2_CALIB_MCUID0636_TTLMINF       = (U2)0U;        /* TtlMinF                                                       */
volatile const U1 u1_CALIB_MCUID0637_OVHT          = (U1)120U;      /* ovht                                                          */
volatile const U1 u1_CALIB_MCUID0638_HYS           = (U1)2U;        /* hys                                                           */
volatile const U1 u1_CALIB_MCUID0639_N1            = (U1)3U;        /* N1                                                            */
volatile const U1 u1_CALIB_MCUID0640_N2            = (U1)6U;        /* N2                                                            */
volatile const U2 u2_CALIB_MCUID0641_REVSET        = (U2)5000U;     /* RevSet                                                        */
volatile const U2 u2_CALIB_MCUID0642_REVDISPHYS    = (U2)100U;      /* RevDispHys                                                    */
volatile const U2 u2_CALIB_MCUID0643_REVNOISEHYS   = (U2)100U;      /* RevNoiseHys                                                   */
volatile const U2 u2_CALIB_MCUID0644_RZ_RPM_MAX    = (U2)8000U;     /* Red Zone RPM MAX                                              */
volatile const U2 u2_CALIB_MCUID0645_RZ_RPM_MIN    = (U2)6700U;     /* Red Zone RPM MIN                                              */
volatile const U1 u1_CALIB_MCUID0646_TACHO_IND     = (U1)0U;        /* Tacho IND                                                     */
volatile const U1 u1_CALIB_MCUID0647_METHVSYSIND   = (U1)1U;        /* MET HV System Indicator                                       */
volatile const U1 u1_CALIB_MCUID0648_HUDHVSYSIND   = (U1)1U;        /* HUD HV System Indicator                                       */
volatile const U1 u1_CALIB_MCUID0649_METNORM       = (U1)2U;        /* MET Normal Display                                            */
volatile const U1 u1_CALIB_MCUID0650_HUDNORM       = (U1)2U;        /* HUD Normal Display                                            */
volatile const U1 u1_CALIB_MCUID0651_HUDNORM1      = (U1)0U;        /* HUD Normal Display 1                                          */
volatile const U1 u1_CALIB_MCUID0652_TC            = (U1)1U;        /* TC                                                            */
volatile const U1 u1_CALIB_MCUID0659_MTSNORM       = (U1)0U;        /* MTS Normal Mode                                               */
volatile const U1 u1_CALIB_MCUID0660_XMODE         = (U1)0U;        /* X-MODE                                                        */
volatile const U1 u1_CALIB_MCUID0661_GFX_DISSWING  = (U1)1U;        /* GFX Dispay Switching                                          */
volatile const U1 u1_CALIB_MCUID0662_0DIAL_VIEW    = (U1)1U;        /* 0dial-View ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0663_1DIAL_VIEW    = (U1)1U;        /* 1dial-View ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0664_2DIAL_VIEW    = (U1)1U;        /* 2dial-View ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0665_MAP_VIEW      = (U1)1U;        /* MAP-View ON/OFF Default                                       */
volatile const U1 u1_CALIB_MCUID0666_ADAS_VIEW     = (U1)1U;        /* ADAS-View ON/OFF Default                                      */
volatile const U1 u1_CALIB_MCUID0667_ECO_VIEW      = (U1)1U;        /* ECO-View ON/OFF Default                                       */
volatile const U1 u1_CALIB_MCUID0668_1DIAL_TR_VIEW = (U1)1U;        /* 1dial Track-View ON/OFF Default                               */
volatile const U1 u1_CALIB_MCUID0669_SHTUPIND_VIEW = (U1)1U;        /* Shift Up Ind-View ON/OFF Default                              */
volatile const U1 u1_CALIB_MCUID0670_OFFROAD_VIEW  = (U1)1U;        /* Off-Road-View ON/OFF Default                                  */
volatile const U1 u1_CALIB_MCUID0671_6DIAL_VIEW    = (U1)1U;        /* 6dial-View ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0672_FC_DEF        = (U1)1U;        /* Fuel Economy ON/OFF Default                                   */
volatile const U1 u1_CALIB_MCUID0673_PWR_DEF       = (U1)1U;        /* Power Consumption ON/OFF Default                              */
volatile const U1 u1_CALIB_MCUID0674_PHEV_FC_DEF   = (U1)1U;        /* PHEV Fuel Economy ON/OFF Default                              */
volatile const U1 u1_CALIB_MCUID0675_ECOIND_DEF    = (U1)1U;        /* Eco Indicator ON/OFF Default                                  */
volatile const U1 u1_CALIB_MCUID0676_ECOSCR_DEF    = (U1)1U;        /* HEV/FCEV Eco Score ON/OFF Default                             */
volatile const U1 u1_CALIB_MCUID0677_EVRATIO       = (U1)1U;        /* EV Ratio ON/OFF Default                                       */
volatile const U1 u1_CALIB_MCUID0678_NAVI_DEF      = (U1)1U;        /* Navigation ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0679_AUDIO_DEF     = (U1)1U;        /* Audio ON/OFF Default                                          */
volatile const U1 u1_CALIB_MCUID0680_DRVINFO_DEF   = (U1)1U;        /* Drive Info ON/OFF Default                                     */
volatile const U1 u1_CALIB_MCUID0681_TRIPA_DEF     = (U1)1U;        /* Trip A ON/OFF Default                                         */
volatile const U1 u1_CALIB_MCUID0682_TRIPB_DEF     = (U1)1U;        /* Trip B ON/OFF Default                                         */
volatile const U1 u1_CALIB_MCUID0683_EGMNTR_DEF    = (U1)1U;        /* Energy Monitor ON/OFF Default                                 */
volatile const U1 u1_CALIB_MCUID0684_TPMS_DEF      = (U1)1U;        /* TPMS ON/OFF Default                                           */
volatile const U1 u1_CALIB_MCUID0685_4WD_DEF       = (U1)1U;        /* 4WD ON/OFF Default                                            */
volatile const U1 u1_CALIB_MCUID0686_TRC_DEF       = (U1)1U;        /* TRC ON/OFF Default                                            */
volatile const U1 u1_CALIB_MCUID0687_STR_DEF       = (U1)1U;        /* Steering angle ON/OFF Default                                 */
volatile const U1 u1_CALIB_MCUID0688_PTCHROLL_DEF  = (U1)1U;        /* Pitch and Roll ON/OFF Default                                 */
volatile const U1 u1_CALIB_MCUID0689_TRABRK_DEF    = (U1)1U;        /* Trailer Brake ON/OFF Default                                  */
volatile const U1 u1_CALIB_MCUID0690_TRABSM_DEF    = (U1)1U;        /* Trailer Mode BSM ON/OFF Default                               */
volatile const U1 u1_CALIB_MCUID0691_VOLTMET_DEF   = (U1)1U;        /* Voltmeter ON/OFF Default                                      */
volatile const U1 u1_CALIB_MCUID0692_OILPRS_DEF    = (U1)1U;        /* Oil Pressure/Voltmeter ON/OFF Default                         */
volatile const U1 u1_CALIB_MCUID0693_EATOILTMP_DEF = (U1)1U;        /* Engine/AT Oil Temp ON/OFF Default                             */
volatile const U1 u1_CALIB_MCUID0694_EOILTMP_DEF   = (U1)1U;        /* Engine Oil Temp ON/OFF Default                                */
volatile const U1 u1_CALIB_MCUID0695_ATOILTMP_DEF  = (U1)1U;        /* AT Oil Temp ON/OFF Default                                    */
volatile const U1 u1_CALIB_MCUID0696_TRBOGAG_W_L   = (U1)1U;        /* Turbo Gauge(CONV)(With Logo) ON/OFF Default                   */
volatile const U1 u1_CALIB_MCUID0697_TRBOGAG_WO_L  = (U1)1U;        /* Turbo Gauge(CONV)(Without Logo) ON/OFF Default                */
volatile const U1 u1_CALIB_MCUID0698_BOSTGAG_W_L   = (U1)1U;        /* Boost Gauge(CONV)(With Logo) ON/OFF Default                   */
volatile const U1 u1_CALIB_MCUID0699_BOSTGAG_WO_L  = (U1)1U;        /* Boost Gauge(CONV)(Without Logo) ON/OFF Default                */
volatile const U1 u1_CALIB_MCUID0700_MTRPWR        = (U1)1U;        /* Motor Power(48V-MHV) ON/OFF Default                           */
volatile const U1 u1_CALIB_MCUID0701_SPRTSGAG      = (U1)1U;        /* Sports Gauges ON/OFF Default                                  */
volatile const U1 u1_CALIB_MCUID0702_GFORCE        = (U1)1U;        /* G-Force ON/OFF Default                                        */
volatile const U1 u1_CALIB_MCUID0703_ADBLUE        = (U1)1U;        /* AdBlue ON/OFF Default                                         */
volatile const U1 u1_CALIB_MCUID0704_ENGCNSMP      = (U1)1U;        /* Energy consumption ON/OFF Default                             */
volatile const U1 u1_CALIB_MCUID0705_MET_CD_TACHO  = (U1)1U;        /* MET CENTER DIAL Tachometer                                    */
volatile const U1 u1_CALIB_MCUID0706_MET_CD_SPEED  = (U1)1U;        /* MET CENTER DIAL Speed                                         */
volatile const U1 u1_CALIB_MCUID0707_MET_CD_HVIND  = (U1)1U;        /* MET CENTER DIAL HVIndicator                                   */
volatile const U1 u1_CALIB_MCUID0708_MET_CD_FCIND  = (U1)1U;        /* MET CENTER DIAL FCIndicator                                   */
volatile const U1 u1_CALIB_MCUID0709_MET_CD_PWR    = (U1)1U;        /* MET CENTER DIAL Pwrmeter                                      */
volatile const U1 u1_CALIB_MCUID0754_MET_CD_DRVMD  = (U1)1U;        /* MET CENTER DIAL DriveMode Interlocking                        */
volatile const U1 u1_CALIB_MCUID0710_MET_LD_TACHO  = (U1)1U;        /* MET LEFT DIAL Tachometer                                      */
volatile const U1 u1_CALIB_MCUID0711_MET_LD_HVIND  = (U1)1U;        /* MET LEFT DIAL HVIndicator                                     */
volatile const U1 u1_CALIB_MCUID0712_MET_LD_FCIND  = (U1)1U;        /* MET LEFT DIAL FCIndicator                                     */
volatile const U1 u1_CALIB_MCUID0713_MET_LD_PWR    = (U1)1U;        /* MET LEFT DIAL Pwrmeter                                        */
volatile const U1 u1_CALIB_MCUID0755_MET_LD_DRVMD  = (U1)1U;        /* MET LEFT DIAL DriveMode Interlocking                          */
volatile const U1 u1_CALIB_MCUID0715_HUD_TACHO     = (U1)1U;        /* HUD AnalogTachometer                                          */
volatile const U1 u1_CALIB_MCUID0716_HUD_ECOIND    = (U1)1U;        /* HUD AnalogEcodriveIndicator                                   */
volatile const U1 u1_CALIB_MCUID0717_HUD_HVIND     = (U1)1U;        /* HUD AnalogHVIndicator                                         */
volatile const U1 u1_CALIB_MCUID0718_HUD_FCIND     = (U1)1U;        /* HUD FCIndicator                                               */
volatile const U1 u1_CALIB_MCUID0719_HUD_PWR       = (U1)1U;        /* HUD Pwrmeter                                                  */
volatile const U1 u1_CALIB_MCUID0756_HUD_DRVMD     = (U1)1U;        /* HUD DriveMode Interlocking                                    */
volatile const U1 u1_CALIB_MCUID0720_PARK_S        = (U1)0U;        /* PARK_S                                                        */
volatile const U1 u1_CALIB_MCUID0721_PARK          = (U1)0U;        /* PARK                                                          */
volatile const U1 u1_CALIB_MCUID0722_LUD           = (U1)0U;        /* LUD                                                           */
volatile const U1 u1_CALIB_MCUID0723_DIST_AFTSTRT  = (U1)1U;        /* Powertrain System Run Distance After starting                 */
volatile const U1 u1_CALIB_MCUID0726_DRVTM_AFTSTRT = (U1)1U;        /* Powertrain System Run Time After starting                     */
volatile const U1 u1_CALIB_MCUID0729_AVGFE_AFTSTRT = (U1)0U;        /* Average Fuel Economy After starting                           */
volatile const U1 u1_CALIB_MCUID0732_EVRATIO       = (U1)0U;        /* EV Ratio                                                      */
volatile const U1 u1_CALIB_MCUID0735_AVGEE_AFTSTRT = (U1)0U;        /* Average Electric Economy After starting                       */
volatile const U2 u2_CALIB_MCUID0738_TIMEOUT_TM    = (U2)30U;       /* Timeout Time                                                  */
volatile const U1 u1_CALIB_MCUID0740_OILLVL_DEF    = (U1)1U;        /* Oil Level ON/OFF Default                                      */
volatile const U1 u1_CALIB_MCUID0741_IL2OUTILLRUN  = (U1)0U;        /* IL2OUTILLRun                                                  */
volatile const U2 u2_CALIB_MCUID0742_IOUTILLRUN    = (U2)125U;      /* IOUTILLRun                                                    */
volatile const U2 u2_CALIB_MCUID0743_IOUTILLRUNMAX = (U2)250U;      /* IOUTILLRunmax                                                 */
volatile const U1 u1_CALIB_MCUID0797_CNST_WRITEFLG = (U1)0U;        /* Constant write flag                                           */

volatile const U1 u1_CALIB_MCUID0270_RHEO_PCT[CALIB_MCUID0270_RHEO_STEP] = {
     (U1)100U,                                        /* MCUID0270                                                                   */
     (U1)100U,                                        /* MCUID0271                                                                   */
     (U1)94U,                                         /* MCUID0272                                                                   */
     (U1)83U,                                         /* MCUID0273                                                                   */
     (U1)74U,                                         /* MCUID0274                                                                   */
     (U1)66U,                                         /* MCUID0275                                                                   */
     (U1)59U,                                         /* MCUID0276                                                                   */
     (U1)53U,                                         /* MCUID0277                                                                   */
     (U1)48U,                                         /* MCUID0278                                                                   */
     (U1)43U,                                         /* MCUID0279                                                                   */
     (U1)38U,                                         /* MCUID0280                                                                   */
     (U1)34U,                                         /* MCUID0281                                                                   */
     (U1)31U,                                         /* MCUID0282                                                                   */
     (U1)28U,                                         /* MCUID0283                                                                   */
     (U1)25U,                                         /* MCUID0284                                                                   */
     (U1)22U,                                         /* MCUID0285                                                                   */
     (U1)20U,                                         /* MCUID0286                                                                   */
     (U1)18U,                                         /* MCUID0287                                                                   */
     (U1)16U,                                         /* MCUID0288                                                                   */
     (U1)14U,                                         /* MCUID0289                                                                   */
     (U1)12U,                                         /* MCUID0290                                                                   */
     (U1)12U                                          /* MCUID0291                                                                   */
};

volatile const U2 u2_CALIB_MCUID0292_TR2_PCT[CALIB_MCUID0292_TR2_STEP] = {
     (U2)1000U,                                       /* MCUID0292                                                                   */
     (U2)1000U,                                       /* MCUID0293                                                                   */
     (U2)940U,                                        /* MCUID0294                                                                   */
     (U2)830U,                                        /* MCUID0295                                                                   */
     (U2)740U,                                        /* MCUID0296                                                                   */
     (U2)670U,                                        /* MCUID0297                                                                   */
     (U2)600U,                                        /* MCUID0298                                                                   */
     (U2)540U,                                        /* MCUID0299                                                                   */
     (U2)480U,                                        /* MCUID0300                                                                   */
     (U2)430U,                                        /* MCUID0301                                                                   */
     (U2)390U,                                        /* MCUID0302                                                                   */
     (U2)350U,                                        /* MCUID0303                                                                   */
     (U2)310U,                                        /* MCUID0304                                                                   */
     (U2)280U,                                        /* MCUID0305                                                                   */
     (U2)250U,                                        /* MCUID0306                                                                   */
     (U2)230U,                                        /* MCUID0307                                                                   */
     (U2)200U,                                        /* MCUID0308                                                                   */
     (U2)180U,                                        /* MCUID0309                                                                   */
     (U2)160U,                                        /* MCUID0310                                                                   */
     (U2)140U,                                        /* MCUID0311                                                                   */
     (U2)130U,                                        /* MCUID0312                                                                   */
     (U2)130U                                         /* MCUID0313                                                                   */
};

volatile const U2 u2_CALIB_MCUID0314_IL2_PCT[CALIB_MCUID0314_IL2_STEP] = {
     (U2)1000U,                                       /* MCUID0314                                                                   */
     (U2)1000U,                                       /* MCUID0315                                                                   */
     (U2)940U,                                        /* MCUID0316                                                                   */
     (U2)830U,                                        /* MCUID0317                                                                   */
     (U2)740U,                                        /* MCUID0318                                                                   */
     (U2)670U,                                        /* MCUID0319                                                                   */
     (U2)600U,                                        /* MCUID0320                                                                   */
     (U2)540U,                                        /* MCUID0321                                                                   */
     (U2)480U,                                        /* MCUID0322                                                                   */
     (U2)430U,                                        /* MCUID0323                                                                   */
     (U2)390U,                                        /* MCUID0324                                                                   */
     (U2)350U,                                        /* MCUID0325                                                                   */
     (U2)310U,                                        /* MCUID0326                                                                   */
     (U2)280U,                                        /* MCUID0327                                                                   */
     (U2)250U,                                        /* MCUID0328                                                                   */
     (U2)230U,                                        /* MCUID0329                                                                   */
     (U2)200U,                                        /* MCUID0330                                                                   */
     (U2)180U,                                        /* MCUID0331                                                                   */
     (U2)160U,                                        /* MCUID0332                                                                   */
     (U2)140U,                                        /* MCUID0333                                                                   */
     (U2)130U,                                        /* MCUID0334                                                                   */
     (U2)130U                                         /* MCUID0335                                                                   */
};

volatile const U1 u1_CALIB_MCUID0342_BL_PCT_DAY[CALIB_MCUID0342_BL_STEP_DAY] = {
     (U1)100U,                                        /* MCUID0342                                                                   */
     (U1)96U,                                         /* MCUID0343                                                                   */
     (U1)92U,                                         /* MCUID0344                                                                   */
     (U1)88U,                                         /* MCUID0345                                                                   */
     (U1)83U,                                         /* MCUID0346                                                                   */
     (U1)79U,                                         /* MCUID0347                                                                   */
     (U1)79U,                                         /* MCUID0348                                                                   */
     (U1)79U,                                         /* MCUID0349                                                                   */
     (U1)79U,                                         /* MCUID0350                                                                   */
     (U1)79U,                                         /* MCUID0351                                                                   */
     (U1)79U,                                         /* MCUID0352                                                                   */
     (U1)79U,                                         /* MCUID0353                                                                   */
     (U1)79U,                                         /* MCUID0354                                                                   */
     (U1)79U,                                         /* MCUID0355                                                                   */
     (U1)79U,                                         /* MCUID0356                                                                   */
     (U1)79U,                                         /* MCUID0357                                                                   */
     (U1)79U,                                         /* MCUID0358                                                                   */
     (U1)79U,                                         /* MCUID0359                                                                   */
     (U1)79U,                                         /* MCUID0360                                                                   */
     (U1)79U,                                         /* MCUID0361                                                                   */
     (U1)79U,                                         /* MCUID0362                                                                   */
     (U1)79U                                          /* MCUID0363                                                                   */
};

volatile const U1 u1_CALIB_MCUID0364_RGB_PCT_DAY[CALIB_MCUID0364_RGB_STEP_DAY] = {
     (U1)0U,                                          /* MCUID0364                                                                   */
     (U1)0U,                                          /* MCUID0365                                                                   */
     (U1)0U,                                          /* MCUID0366                                                                   */
     (U1)0U,                                          /* MCUID0367                                                                   */
     (U1)0U,                                          /* MCUID0368                                                                   */
     (U1)0U,                                          /* MCUID0369                                                                   */
     (U1)0U,                                          /* MCUID0370                                                                   */
     (U1)0U,                                          /* MCUID0371                                                                   */
     (U1)0U,                                          /* MCUID0372                                                                   */
     (U1)0U,                                          /* MCUID0373                                                                   */
     (U1)0U,                                          /* MCUID0374                                                                   */
     (U1)0U,                                          /* MCUID0375                                                                   */
     (U1)0U,                                          /* MCUID0376                                                                   */
     (U1)0U,                                          /* MCUID0377                                                                   */
     (U1)0U,                                          /* MCUID0378                                                                   */
     (U1)0U,                                          /* MCUID0379                                                                   */
     (U1)0U,                                          /* MCUID0380                                                                   */
     (U1)0U,                                          /* MCUID0381                                                                   */
     (U1)0U,                                          /* MCUID0382                                                                   */
     (U1)0U,                                          /* MCUID0383                                                                   */
     (U1)0U,                                          /* MCUID0384                                                                   */
     (U1)0U                                           /* MCUID0385                                                                   */
};

volatile const U1 u1_CALIB_MCUID0386_BL_PCT_NIGHT[CALIB_MCUID0386_BL_STEP_NIGHT] = {
     (U1)55U,                                         /* MCUID0386                                                                   */
     (U1)52U,                                         /* MCUID0387                                                                   */
     (U1)49U,                                         /* MCUID0388                                                                   */
     (U1)46U,                                         /* MCUID0389                                                                   */
     (U1)43U,                                         /* MCUID0390                                                                   */
     (U1)40U,                                         /* MCUID0391                                                                   */
     (U1)37U,                                         /* MCUID0392                                                                   */
     (U1)34U,                                         /* MCUID0393                                                                   */
     (U1)31U,                                         /* MCUID0394                                                                   */
     (U1)28U,                                         /* MCUID0395                                                                   */
     (U1)25U,                                         /* MCUID0396                                                                   */
     (U1)22U,                                         /* MCUID0397                                                                   */
     (U1)19U,                                         /* MCUID0398                                                                   */
     (U1)17U,                                         /* MCUID0399                                                                   */
     (U1)17U,                                         /* MCUID0400                                                                   */
     (U1)17U,                                         /* MCUID0401                                                                   */
     (U1)17U,                                         /* MCUID0402                                                                   */
     (U1)17U,                                         /* MCUID0403                                                                   */
     (U1)17U,                                         /* MCUID0404                                                                   */
     (U1)17U,                                         /* MCUID0405                                                                   */
     (U1)17U,                                         /* MCUID0406                                                                   */
     (U1)17U                                          /* MCUID0407                                                                   */
};

volatile const U1 u1_CALIB_MCUID0408_RGB_PCT_NIGHT[CALIB_MCUID0408_RGB_STEP_NIGHT] = {
     (U1)0U,                                          /* MCUID0408                                                                   */
     (U1)0U,                                          /* MCUID0409                                                                   */
     (U1)0U,                                          /* MCUID0410                                                                   */
     (U1)0U,                                          /* MCUID0411                                                                   */
     (U1)0U,                                          /* MCUID0412                                                                   */
     (U1)0U,                                          /* MCUID0413                                                                   */
     (U1)0U,                                          /* MCUID0414                                                                   */
     (U1)0U,                                          /* MCUID0415                                                                   */
     (U1)0U,                                          /* MCUID0416                                                                   */
     (U1)0U,                                          /* MCUID0417                                                                   */
     (U1)0U,                                          /* MCUID0418                                                                   */
     (U1)0U,                                          /* MCUID0419                                                                   */
     (U1)0U,                                          /* MCUID0420                                                                   */
     (U1)0U,                                          /* MCUID0421                                                                   */
     (U1)0U,                                          /* MCUID0422                                                                   */
     (U1)0U,                                          /* MCUID0423                                                                   */
     (U1)0U,                                          /* MCUID0424                                                                   */
     (U1)0U,                                          /* MCUID0425                                                                   */
     (U1)0U,                                          /* MCUID0426                                                                   */
     (U1)0U,                                          /* MCUID0427                                                                   */
     (U1)0U,                                          /* MCUID0428                                                                   */
     (U1)0U                                           /* MCUID0429                                                                   */
};

volatile const U2 u2_CALIB_MCUID0433_FU_ANALITMA[CALIB_MCUID0433_FU_ANALITMA] = {
     (U2)5630U,                                       /* MCUID0433                                                                   */
     (U2)5198U,                                       /* MCUID0434                                                                   */
     (U2)4766U,                                       /* MCUID0435                                                                   */
     (U2)4363U,                                       /* MCUID0436                                                                   */
     (U2)3960U,                                       /* MCUID0437                                                                   */
     (U2)3758U,                                       /* MCUID0438                                                                   */
     (U2)3556U,                                       /* MCUID0439                                                                   */
     (U2)3153U,                                       /* MCUID0440                                                                   */
     (U2)2750U,                                       /* MCUID0441                                                                   */
     (U2)2200U,                                       /* MCUID0442                                                                   */
     (U2)1650U,                                       /* MCUID0443                                                                   */
     (U2)1375U,                                       /* MCUID0444                                                                   */
     (U2)1220U,                                       /* MCUID0445                                                                   */
     (U2)900U,                                        /* MCUID0446                                                                   */
     (U2)825U,                                        /* MCUID0447                                                                   */
     (U2)550U,                                        /* MCUID0448                                                                   */
     (U2)456U,                                        /* MCUID0449                                                                   */
     (U2)337U                                         /* MCUID0450                                                                   */
};

volatile const U2 u2_CALIB_MCUID0451_FU_ANAVLTMA[CALIB_MCUID0451_FU_ANAVLTMA] = {
     (U2)4400U,                                       /* MCUID0451                                                                   */
     (U2)4290U,                                       /* MCUID0452                                                                   */
     (U2)4121U,                                       /* MCUID0453                                                                   */
     (U2)3846U,                                       /* MCUID0454                                                                   */
     (U2)3566U,                                       /* MCUID0455                                                                   */
     (U2)3427U,                                       /* MCUID0456                                                                   */
     (U2)3288U,                                       /* MCUID0457                                                                   */
     (U2)3004U,                                       /* MCUID0458                                                                   */
     (U2)2709U,                                       /* MCUID0459                                                                   */
     (U2)2345U,                                       /* MCUID0460                                                                   */
     (U2)1805U,                                       /* MCUID0461                                                                   */
     (U2)1611U,                                       /* MCUID0462                                                                   */
     (U2)1482U,                                       /* MCUID0463                                                                   */
     (U2)1204U,                                       /* MCUID0464                                                                   */
     (U2)1114U,                                       /* MCUID0465                                                                   */
     (U2)781U,                                        /* MCUID0466                                                                   */
     (U2)690U,                                        /* MCUID0467                                                                   */
     (U2)550U                                         /* MCUID0468                                                                   */
};

volatile const U2 u2_CALIB_MCUID0469_FU_ANALITSU[CALIB_MCUID0469_FU_ANALITSU] = {
     (U2)0U,                                          /* MCUID0469                                                                   */
     (U2)0U,                                          /* MCUID0470                                                                   */
     (U2)0U,                                          /* MCUID0471                                                                   */
     (U2)0U,                                          /* MCUID0472                                                                   */
     (U2)0U,                                          /* MCUID0473                                                                   */
     (U2)0U,                                          /* MCUID0474                                                                   */
     (U2)0U,                                          /* MCUID0475                                                                   */
     (U2)0U,                                          /* MCUID0476                                                                   */
     (U2)0U,                                          /* MCUID0477                                                                   */
     (U2)0U,                                          /* MCUID0478                                                                   */
     (U2)0U,                                          /* MCUID0479                                                                   */
     (U2)0U,                                          /* MCUID0480                                                                   */
     (U2)0U,                                          /* MCUID0481                                                                   */
     (U2)0U,                                          /* MCUID0482                                                                   */
     (U2)0U,                                          /* MCUID0483                                                                   */
     (U2)0U,                                          /* MCUID0484                                                                   */
     (U2)0U,                                          /* MCUID0485                                                                   */
     (U2)0U                                           /* MCUID0486                                                                   */
};

volatile const U2 u2_CALIB_MCUID0487_FU_ANAVLTSU[CALIB_MCUID0487_FU_ANAVLTSU] = {
     (U2)0U,                                          /* MCUID0487                                                                   */
     (U2)0U,                                          /* MCUID0488                                                                   */
     (U2)0U,                                          /* MCUID0489                                                                   */
     (U2)0U,                                          /* MCUID0490                                                                   */
     (U2)0U,                                          /* MCUID0491                                                                   */
     (U2)0U,                                          /* MCUID0492                                                                   */
     (U2)0U,                                          /* MCUID0493                                                                   */
     (U2)0U,                                          /* MCUID0494                                                                   */
     (U2)0U,                                          /* MCUID0495                                                                   */
     (U2)0U,                                          /* MCUID0496                                                                   */
     (U2)0U,                                          /* MCUID0497                                                                   */
     (U2)0U,                                          /* MCUID0498                                                                   */
     (U2)0U,                                          /* MCUID0499                                                                   */
     (U2)0U,                                          /* MCUID0500                                                                   */
     (U2)0U,                                          /* MCUID0501                                                                   */
     (U2)0U,                                          /* MCUID0502                                                                   */
     (U2)0U,                                          /* MCUID0503                                                                   */
     (U2)0U                                           /* MCUID0504                                                                   */
};

volatile const U2 u2_CALIB_MCUID0505_FU_SEGLITMA[CALIB_MCUID0505_FU_SEGLITMA] = {
     (U2)5158U,                                       /* MCUID0505                                                                   */
     (U2)4970U,                                       /* MCUID0506                                                                   */
     (U2)4770U,                                       /* MCUID0507                                                                   */
     (U2)4170U,                                       /* MCUID0508                                                                   */
     (U2)3560U,                                       /* MCUID0509                                                                   */
     (U2)2960U,                                       /* MCUID0510                                                                   */
     (U2)2350U,                                       /* MCUID0511                                                                   */
     (U2)1750U,                                       /* MCUID0512                                                                   */
     (U2)1150U,                                       /* MCUID0513                                                                   */
     (U2)830U,                                        /* MCUID0514                                                                   */
     (U2)550U,                                        /* MCUID0515                                                                   */
     (U2)456U,                                        /* MCUID0516                                                                   */
     (U2)337U                                         /* MCUID0517                                                                   */
};

volatile const U2 u2_CALIB_MCUID0518_FU_SEGVLTMA[CALIB_MCUID0518_FU_SEGVLTMA] = {
     (U2)4400U,                                       /* MCUID0518                                                                   */
     (U2)4255U,                                       /* MCUID0519                                                                   */
     (U2)4090U,                                       /* MCUID0520                                                                   */
     (U2)3610U,                                       /* MCUID0521                                                                   */
     (U2)3120U,                                       /* MCUID0522                                                                   */
     (U2)2640U,                                       /* MCUID0523                                                                   */
     (U2)2160U,                                       /* MCUID0524                                                                   */
     (U2)1680U,                                       /* MCUID0525                                                                   */
     (U2)1200U,                                       /* MCUID0526                                                                   */
     (U2)940U,                                        /* MCUID0527                                                                   */
     (U2)720U,                                        /* MCUID0528                                                                   */
     (U2)695U,                                        /* MCUID0529                                                                   */
     (U2)550U                                         /* MCUID0530                                                                   */
};

volatile const U2 u2_CALIB_MCUID0531_FU_SEGLITSU[CALIB_MCUID0531_FU_SEGLITSU] = {
     (U2)0U,                                          /* MCUID0531                                                                   */
     (U2)0U,                                          /* MCUID0532                                                                   */
     (U2)0U,                                          /* MCUID0533                                                                   */
     (U2)0U,                                          /* MCUID0534                                                                   */
     (U2)0U,                                          /* MCUID0535                                                                   */
     (U2)0U,                                          /* MCUID0536                                                                   */
     (U2)0U,                                          /* MCUID0537                                                                   */
     (U2)0U,                                          /* MCUID0538                                                                   */
     (U2)0U,                                          /* MCUID0539                                                                   */
     (U2)0U,                                          /* MCUID0540                                                                   */
     (U2)0U,                                          /* MCUID0541                                                                   */
     (U2)0U,                                          /* MCUID0542                                                                   */
     (U2)0U                                           /* MCUID0543                                                                   */
};

volatile const U2 u2_CALIB_MCUID0544_FU_SEGVLTSU[CALIB_MCUID0544_FU_SEGVLTSU] = {
     (U2)0U,                                          /* MCUID0544                                                                   */
     (U2)0U,                                          /* MCUID0545                                                                   */
     (U2)0U,                                          /* MCUID0546                                                                   */
     (U2)0U,                                          /* MCUID0547                                                                   */
     (U2)0U,                                          /* MCUID0548                                                                   */
     (U2)0U,                                          /* MCUID0549                                                                   */
     (U2)0U,                                          /* MCUID0550                                                                   */
     (U2)0U,                                          /* MCUID0551                                                                   */
     (U2)0U,                                          /* MCUID0552                                                                   */
     (U2)0U,                                          /* MCUID0553                                                                   */
     (U2)0U,                                          /* MCUID0554                                                                   */
     (U2)0U,                                          /* MCUID0555                                                                   */
     (U2)0U                                           /* MCUID0556                                                                   */
};

volatile const U2 u2_CALIB_MCUID0757_SP_USA_CAN[CALIB_SP_TOLER_CORPT_NUM] = {
     (U2)217U,                                        /* MCUID0757                                                                   */
     (U2)428U,                                        /* MCUID0758                                                                   */
     (U2)628U,                                        /* MCUID0759                                                                   */
     (U2)843U,                                        /* MCUID0760                                                                   */
     (U2)1047U,                                       /* MCUID0761                                                                   */
     (U2)1254U,                                       /* MCUID0762                                                                   */
     (U2)1460U,                                       /* MCUID0763                                                                   */
     (U2)1668U,                                       /* MCUID0764                                                                   */
     (U2)1875U,                                       /* MCUID0765                                                                   */
     (U2)2082U,                                       /* MCUID0766                                                                   */
     (U2)2289U,                                       /* MCUID0767                                                                   */
     (U2)2496U,                                       /* MCUID0768                                                                   */
     (U2)2704U,                                       /* MCUID0769                                                                   */
     (U2)2911U,                                       /* MCUID0770                                                                   */
     (U2)3118U,                                       /* MCUID0771                                                                   */
     (U2)3325U,                                       /* MCUID0772                                                                   */
     (U2)3532U,                                       /* MCUID0773                                                                   */
     (U2)3740U,                                       /* MCUID0774                                                                   */
     (U2)3947U,                                       /* MCUID0775                                                                   */
     (U2)4154U                                        /* MCUID0776                                                                   */
};

volatile const U2 u2_CALIB_MCUID0777_SP_UNR_AUS[CALIB_SP_TOLER_CORPT_NUM] = {
     (U2)217U,                                        /* MCUID0777                                                                   */
     (U2)428U,                                        /* MCUID0778                                                                   */
     (U2)628U,                                        /* MCUID0779                                                                   */
     (U2)843U,                                        /* MCUID0780                                                                   */
     (U2)1047U,                                       /* MCUID0781                                                                   */
     (U2)1254U,                                       /* MCUID0782                                                                   */
     (U2)1460U,                                       /* MCUID0783                                                                   */
     (U2)1668U,                                       /* MCUID0784                                                                   */
     (U2)1875U,                                       /* MCUID0785                                                                   */
     (U2)2082U,                                       /* MCUID0786                                                                   */
     (U2)2289U,                                       /* MCUID0787                                                                   */
     (U2)2496U,                                       /* MCUID0788                                                                   */
     (U2)2704U,                                       /* MCUID0789                                                                   */
     (U2)2911U,                                       /* MCUID0790                                                                   */
     (U2)3118U,                                       /* MCUID0791                                                                   */
     (U2)3325U,                                       /* MCUID0792                                                                   */
     (U2)3532U,                                       /* MCUID0793                                                                   */
     (U2)3740U,                                       /* MCUID0794                                                                   */
     (U2)3947U,                                       /* MCUID0795                                                                   */
     (U2)4154U                                        /* MCUID0796                                                                   */
};


#pragma ghs section rodata  = default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    05/29/2023  SH       Define sound pressure decreasing rate.                                                             */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
