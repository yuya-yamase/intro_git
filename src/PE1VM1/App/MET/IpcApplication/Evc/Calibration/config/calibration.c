/* 1.3.0 */
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
#define CALIBRATION_C_MINOR                     (3)
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
volatile const U1 u1_CALIB_MCUID0011_MCUID11       = (U1)35U;       /* MCU Software version No.11                                    */
volatile const U1 u1_CALIB_MCUID0012_MCUID12       = (U1)48U;       /* MCU Software version No.12                                    */
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
volatile const U2 u2_CALIB_DUMMY_0001              = (U2)0U;        /* MCUCONST_v019 MCUID0024 (AT reverse buzzer MID)               */
volatile const U2 u2_CALIB_DUMMY_0002              = (U2)0U;        /* MCUCONST_v019 MCUID0744 (AT reverse buzzer MAX)               */
volatile const U2 u2_CALIB_MCUID0029_REV_IN_MID    = (U2)400U;      /* Reverse buzzer Intermittent MID                               */
volatile const U2 u2_CALIB_MCUID0746_REV_IN_MAX    = (U2)500U;      /* Reverse buzzer Intermittent MAX                               */
volatile const U2 u2_CALIB_MCUID0030_SBELT_FMV_MID = (U2)400U;      /* seatbelt reminder buzzer(fmv) MID                             */
volatile const U2 u2_CALIB_MCUID0747_SBELT_FMV_MAX = (U2)500U;      /* seatbelt reminder buzzer(fmv) MAX                             */
volatile const U2 u2_CALIB_MCUID0031_SBELT_LV1_MID = (U2)400U;      /* seatbelt reminder buzzer(level 1) MID                         */
volatile const U2 u2_CALIB_MCUID0748_SBELT_LV1_MAX = (U2)500U;      /* seatbelt reminder buzzer(level 1) MAX                         */
volatile const U2 u2_CALIB_MCUID0032_SBELT_LV2_MID = (U2)400U;      /* seatbelt reminder buzzer(level 2) MID                         */
volatile const U2 u2_CALIB_MCUID0749_SBELT_LV2_MAX = (U2)500U;      /* seatbelt reminder buzzer(level 2) MAX                         */
volatile const U2 u2_CALIB_MCUID0033_SBELT_SI_MID  = (U2)400U;      /* seatbelt reminder buzzer(si) MID                              */
volatile const U2 u2_CALIB_MCUID0750_SBELT_SI_MAX  = (U2)500U;      /* seatbelt reminder buzzer(si) MAX                              */
volatile const U2 u2_CALIB_MCUID0035_MC_MID        = (U2)400U;      /* Master Caution MID                                            */
volatile const U2 u2_CALIB_MCUID0036_MC_MAX        = (U2)500U;      /* Master Caution MAX                                            */
volatile const U2 u2_CALIB_MCUID0037_ACC_MID       = (U2)400U;      /* ACC Auto Start MID                                            */
volatile const U2 u2_CALIB_MCUID0751_ACC_MAX       = (U2)500U;      /* ACC Auto Start MAX                                            */
volatile const U2 u2_CALIB_MCUID0038_TMN_MID       = (U2)400U;      /* TMN MID                                                       */
volatile const U2 u2_CALIB_MCUID0752_TMN_MAX       = (U2)500U;      /* TMN MAX                                                       */
volatile const U2 u2_CALIB_MCUID0039_RSA_MID       = (U2)400U;      /* RSA MID                                                       */
volatile const U2 u2_CALIB_MCUID0753_RSA_MAX       = (U2)500U;      /* RSA MAX                                                       */
volatile const U2 u2_CALIB_MCUID0067_CSR_FRSD0     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0068_CSR_FRSD1     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0069_CSR_FRSD2     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0070_CSR_FRSD3     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0071_CSR_FRSD4     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0072_CSR_FRSD5     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0073_CSR_FRSD6     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0074_CSR_FRSD7     = (U2)400U;      /* Clearance sonar buzzer Fr(SD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0075_CSR_FRMD0     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0076_CSR_FRMD1     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0077_CSR_FRMD2     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0078_CSR_FRMD3     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0079_CSR_FRMD4     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0080_CSR_FRMD5     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0081_CSR_FRMD6     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0082_CSR_FRMD7     = (U2)400U;      /* Clearance sonar buzzer Fr(MD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0083_CSR_FRLD0     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0084_CSR_FRLD1     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0085_CSR_FRLD2     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0086_CSR_FRLD3     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0087_CSR_FRLD4     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0088_CSR_FRLD5     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0089_CSR_FRLD6     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0090_CSR_FRLD7     = (U2)400U;      /* Clearance sonar buzzer Fr(LD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0091_CSR_FRFD0     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0092_CSR_FRFD1     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0093_CSR_FRFD2     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0094_CSR_FRFD3     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0095_CSR_FRFD4     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0096_CSR_FRFD5     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0097_CSR_FRFD6     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0098_CSR_FRFD7     = (U2)400U;      /* Clearance sonar buzzer Fr(FD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0099_CSR_RRSD0     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0100_CSR_RRSD1     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0101_CSR_RRSD2     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0102_CSR_RRSD3     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0103_CSR_RRSD4     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0104_CSR_RRSD5     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0105_CSR_RRSD6     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0106_CSR_RRSD7     = (U2)400U;      /* Clearance sonar buzzer Rr(SD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0107_CSR_RRMD0     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0108_CSR_RRMD1     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0109_CSR_RRMD2     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0110_CSR_RRMD3     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0111_CSR_RRMD4     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0112_CSR_RRMD5     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0113_CSR_RRMD6     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0114_CSR_RRMD7     = (U2)400U;      /* Clearance sonar buzzer Rr(MD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0115_CSR_RRLD0     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0116_CSR_RRLD1     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0117_CSR_RRLD2     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0118_CSR_RRLD3     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0119_CSR_RRLD4     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0120_CSR_RRLD5     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0121_CSR_RRLD6     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0122_CSR_RRLD7     = (U2)400U;      /* Clearance sonar buzzer Rr(LD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0123_CSR_RRFD0     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:0                       */
volatile const U2 u2_CALIB_MCUID0124_CSR_RRFD1     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:1                       */
volatile const U2 u2_CALIB_MCUID0125_CSR_RRFD2     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:2                       */
volatile const U2 u2_CALIB_MCUID0126_CSR_RRFD3     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:3                       */
volatile const U2 u2_CALIB_MCUID0127_CSR_RRFD4     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:4                       */
volatile const U2 u2_CALIB_MCUID0128_CSR_RRFD5     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:5                       */
volatile const U2 u2_CALIB_MCUID0129_CSR_RRFD6     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:6                       */
volatile const U2 u2_CALIB_MCUID0130_CSR_RRFD7     = (U2)400U;      /* Clearance sonar buzzer Rr(FD) CSR_VOL:7                       */
volatile const U2 u2_CALIB_MCUID0131_CSR_FRRRSD0   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:0                    */
volatile const U2 u2_CALIB_MCUID0132_CSR_FRRRSD1   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:1                    */
volatile const U2 u2_CALIB_MCUID0133_CSR_FRRRSD2   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:2                    */
volatile const U2 u2_CALIB_MCUID0134_CSR_FRRRSD3   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:3                    */
volatile const U2 u2_CALIB_MCUID0135_CSR_FRRRSD4   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:4                    */
volatile const U2 u2_CALIB_MCUID0136_CSR_FRRRSD5   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:5                    */
volatile const U2 u2_CALIB_MCUID0137_CSR_FRRRSD6   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:6                    */
volatile const U2 u2_CALIB_MCUID0138_CSR_FRRRSD7   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(SD) CSR_VOL:7                    */
volatile const U2 u2_CALIB_MCUID0139_CSR_FRRRMD0   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:0                    */
volatile const U2 u2_CALIB_MCUID0140_CSR_FRRRMD1   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:1                    */
volatile const U2 u2_CALIB_MCUID0141_CSR_FRRRMD2   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:2                    */
volatile const U2 u2_CALIB_MCUID0142_CSR_FRRRMD3   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:3                    */
volatile const U2 u2_CALIB_MCUID0143_CSR_FRRRMD4   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:4                    */
volatile const U2 u2_CALIB_MCUID0144_CSR_FRRRMD5   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:5                    */
volatile const U2 u2_CALIB_MCUID0145_CSR_FRRRMD6   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:6                    */
volatile const U2 u2_CALIB_MCUID0146_CSR_FRRRMD7   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(MD) CSR_VOL:7                    */
volatile const U2 u2_CALIB_MCUID0155_CSR_FRRRLD0   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:0                    */
volatile const U2 u2_CALIB_MCUID0156_CSR_FRRRLD1   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:1                    */
volatile const U2 u2_CALIB_MCUID0157_CSR_FRRRLD2   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:2                    */
volatile const U2 u2_CALIB_MCUID0158_CSR_FRRRLD3   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:3                    */
volatile const U2 u2_CALIB_MCUID0159_CSR_FRRRLD4   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:4                    */
volatile const U2 u2_CALIB_MCUID0160_CSR_FRRRLD5   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:5                    */
volatile const U2 u2_CALIB_MCUID0161_CSR_FRRRLD6   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:6                    */
volatile const U2 u2_CALIB_MCUID0162_CSR_FRRRLD7   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(LD) CSR_VOL:7                    */
volatile const U2 u2_CALIB_MCUID0171_CSR_FRRRFD0   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:0                    */
volatile const U2 u2_CALIB_MCUID0172_CSR_FRRRFD1   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:1                    */
volatile const U2 u2_CALIB_MCUID0173_CSR_FRRRFD2   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:2                    */
volatile const U2 u2_CALIB_MCUID0174_CSR_FRRRFD3   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:3                    */
volatile const U2 u2_CALIB_MCUID0175_CSR_FRRRFD4   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:4                    */
volatile const U2 u2_CALIB_MCUID0176_CSR_FRRRFD5   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:5                    */
volatile const U2 u2_CALIB_MCUID0177_CSR_FRRRFD6   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:6                    */
volatile const U2 u2_CALIB_MCUID0178_CSR_FRRRFD7   = (U2)400U;      /* Clearance sonar buzzer Fr+Rr(FD) CSR_VOL:7                    */
volatile const U2 u2_CALIB_MCUID0187_FLSTA_LOLO    = (U2)400U;      /* flasher start sound(low customize, low speed)                 */
volatile const U2 u2_CALIB_MCUID0188_FLSTA_LOMI    = (U2)400U;      /* flasher start sound(low customize, mid speed)                 */
volatile const U2 u2_CALIB_MCUID0189_FLSTA_LOHI    = (U2)400U;      /* flasher start sound(low customize, high speed)                */
volatile const U2 u2_CALIB_MCUID0190_FLSTA_MILO    = (U2)400U;      /* flasher start sound(mid customize, low speed)                 */
volatile const U2 u2_CALIB_MCUID0191_FLSTA_MIMI    = (U2)400U;      /* flasher start sound(mid customize, mid speed)                 */
volatile const U2 u2_CALIB_MCUID0192_FLSTA_MIHI    = (U2)400U;      /* flasher start sound(mid customize, high speed)                */
volatile const U2 u2_CALIB_MCUID0193_FLSTA_HILO    = (U2)500U;      /* flasher start sound(high customize, low speed)                */
volatile const U2 u2_CALIB_MCUID0194_FLSTA_HIMI    = (U2)500U;      /* flasher start sound(high customize, mid speed)                */
volatile const U2 u2_CALIB_MCUID0195_FLSTA_HIHI    = (U2)500U;      /* flasher start sound(high customize, high speed)               */
volatile const U2 u2_CALIB_MCUID0196_FLFIN_LOLO    = (U2)400U;      /* flasher finish sound(low customize, low speed)                */
volatile const U2 u2_CALIB_MCUID0197_FLFIN_LOMI    = (U2)400U;      /* flasher finish sound(low customize, mid speed)                */
volatile const U2 u2_CALIB_MCUID0198_FLFIN_LOHI    = (U2)400U;      /* flasher finish sound(low customize, high speed)               */
volatile const U2 u2_CALIB_MCUID0199_FLFIN_MILO    = (U2)400U;      /* flasher finish sound(mid customize, low speed)                */
volatile const U2 u2_CALIB_MCUID0200_FLFIN_MIMI    = (U2)400U;      /* flasher finish sound(mid customize, mid speed)                */
volatile const U2 u2_CALIB_MCUID0201_FLFIN_MIHI    = (U2)400U;      /* flasher finish sound(mid customize, high speed)               */
volatile const U2 u2_CALIB_MCUID0202_FLFIN_HILO    = (U2)500U;      /* flasher finish sound(high customize, low speed)               */
volatile const U2 u2_CALIB_MCUID0203_FLFIN_HIMI    = (U2)500U;      /* flasher finish sound(high customize, mid speed)               */
volatile const U2 u2_CALIB_MCUID0204_FLFIN_HIHI    = (U2)500U;      /* flasher finish sound(high customize, high speed)              */
volatile const U2 u2_CALIB_MCUID0205_2CH           = (U2)400U;      /* 2 channels multiplex playing                                  */
volatile const U2 u2_CALIB_MCUID0206_3CH           = (U2)400U;      /* 3 channels multiplex playing                                  */
volatile const U2 u2_CALIB_MCUID0207_4CH           = (U2)400U;      /* 4 channels multiplex playing                                  */
volatile const U2 u2_CALIB_MCUID0208_5CH           = (U2)400U;      /* 5 channels multiplex playing                                  */
volatile const U2 u2_CALIB_MCUID0799_800HZ_57DB    = (U2)20U;       /* single frequency buzzer 800hz 57db                            */
volatile const U2 u2_CALIB_MCUID0800_800HZ_61DB    = (U2)20U;       /* single frequency buzzer 800hz 61db                            */
volatile const U2 u2_CALIB_MCUID0801_800HZ_63DB    = (U2)30U;       /* single frequency buzzer 800hz 63db                            */
volatile const U2 u2_CALIB_MCUID0802_800HZ_67DB    = (U2)30U;       /* single frequency buzzer 800hz 67db                            */
volatile const U2 u2_CALIB_MCUID0803_1600HZ_63DB   = (U2)100U;      /* single frequency buzzer 1600hz 63db                           */
volatile const U2 u2_CALIB_MCUID0804_1600HZ_67DB   = (U2)150U;      /* single frequency buzzer 1600hz 67db                           */
volatile const U2 u2_CALIB_MCUID0805_1600HZ_73DB   = (U2)310U;      /* single frequency buzzer 1600hz 73db                           */
volatile const U2 u2_CALIB_MCUID0806_1600HZ_77DB   = (U2)310U;      /* single frequency buzzer 1600hz 77db                           */
volatile const U2 u2_CALIB_MCUID0807_2400HZ_63DB   = (U2)100U;      /* single frequency buzzer 2400hz 63db                           */
volatile const U2 u2_CALIB_MCUID0808_2400HZ_67DB   = (U2)170U;      /* single frequency buzzer 2400hz 67db                           */
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
volatile const U2 u2_CALIB_MCUID0239_FULFUL        = (U2)5500U;     /* FulFul                                                        */
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
volatile const U1 u1_CALIB_MCUID0268_SWNUM         = (U1)1U;        /* SWnum                                                         */
volatile const U1 u1_CALIB_MCUID0269_SWPOSI        = (U1)2U;        /* SWposi                                                        */
volatile const U1 u1_CALIB_MCUID0336_ILLOF_LV      = (U1)0U;        /* ILL_OF Level                                                  */
volatile const U1 u1_CALIB_MCUID0337_ILLOF_CAN_LV  = (U1)1U;        /* ILL_OF Cancel Level                                           */
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
volatile const U1 u1_CALIB_DUMMY_0003              = (U1)0U;        /* MCUCONST_v019 MCUID0588 (OM_MLG)                              */
volatile const U1 u1_CALIB_DUMMY_0004              = (U1)0U;        /* MCUCONST_v019 MCUID0589 (PR_OM_FL)                            */
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
volatile const U2 u2_CALIB_MCUID0609_KPAOLPL       = (U2)0U;        /* kPaOLPL                                                       */
volatile const U2 u2_CALIB_MCUID0610_KPAOLPH       = (U2)8000U;     /* kPaOLPH                                                       */
volatile const U2 u2_CALIB_DUMMY_0005              = (U2)0U;        /* MCUCONST_v019 U2 MCUID0611 (barOLPL)                          */
volatile const U2 u2_CALIB_DUMMY_0006              = (U2)0U;        /* MCUCONST_v019 U2 MCUID0612 (barOLPH)                          */
volatile const U2 u2_CALIB_MCUID0613_PSIOLPL       = (U2)0U;        /* psiOLPL                                                       */
volatile const U2 u2_CALIB_MCUID0614_PSIOLPH       = (U2)1160U;     /* psiOLPH                                                       */
volatile const U1 u1_CALIB_MCUID0653_KPAOLPMAX     = (U1)80U;       /* kPaOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0654_KPAOLPMIN     = (U1)0U;        /* kPaOLPMin                                                     */
volatile const U1 u1_CALIB_MCUID0655_BAROLPMAX     = (U1)80U;       /* barOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0656_BAROLPMIN     = (U1)0U;        /* barOLPMin                                                     */
volatile const U1 u1_CALIB_MCUID0657_PSIOLPMAX     = (U1)116U;      /* psiOLPMax                                                     */
volatile const U1 u1_CALIB_MCUID0658_PSIOLPMIN     = (U1)0U;        /* psiOLPMin                                                     */
volatile const U1 u1_CALIB_MCUID0623_OLTTLC        = (U1)40U;       /* OLTtlC                                                        */
volatile const U1 u1_CALIB_MCUID0624_OLTTLH        = (U1)160U;      /* OLTtlH                                                        */
volatile const U2 u2_CALIB_MCUID0625_OLTMAXC       = (U2)200U;      /* OLTMaxC                                                       */
volatile const U2 u2_CALIB_MCUID0626_OLTMINC       = (U2)0U;        /* OLTMinC                                                       */
volatile const U2 u2_CALIB_MCUID0627_OLTMAXF       = (U2)360U;      /* OLTMaxF                                                       */
volatile const U2 u2_CALIB_MCUID0628_OLTMINF       = (U2)0U;        /* OLTMinF                                                       */
volatile const U1 u1_CALIB_MCUID0629_HYS           = (U1)1U;        /* hys                                                           */
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
volatile const U1 u1_CALIB_MCUID0647_METHVSYSIND   = (U1)1U;        /* MET HV System Indicator                                       */
volatile const U1 u1_CALIB_MCUID0648_HUDHVSYSIND   = (U1)1U;        /* HUD HV System Indicator                                       */
volatile const U1 u1_CALIB_MCUID0649_METNORM       = (U1)2U;        /* MET Normal Display                                            */
volatile const U1 u1_CALIB_MCUID0650_HUDNORM       = (U1)2U;        /* HUD Normal Display                                            */
volatile const U1 u1_CALIB_MCUID0651_HUDNORM1      = (U1)0U;        /* HUD Normal Display 1                                          */
volatile const U1 u1_CALIB_DUMMY_0007              = (U1)0U;        /* MCUCONST_v019 U2 MCUID0659 (MTS Normal Mode)                  */
volatile const U1 u1_CALIB_MCUID0660_XMODE         = (U1)0U;        /* X-MODE                                                        */
volatile const U1 u1_CALIB_MCUID0661_OFFROAD_VIEW  = (U1)0U;        /* Off-Road-View                                                 */
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
volatile const U1 u1_CALIB_MCUID0798_TRNLMPCLR     = (U1)0U;        /* Turn signal lamp color of your vehicle                        */
volatile const U1 u1_CALIB_MCUID0809_MEXICO_LOW    = (U1)0U;        /* Mexico lows and regulations                                   */
volatile const U1 u1_CALIB_MCUID0810_KOREA_LOW     = (U1)1U;        /* Korea lows and regulations                                    */
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

volatile const U1 u1_CALIB_MCUID0364_RGB_ALPHA_DAY[CALIB_MCUID0364_RGB_STEP_DAY] = {
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

volatile const U1 u1_CALIB_MCUID0408_RGB_ALPHA_NGT[CALIB_MCUID0408_RGB_STEP_NIGHT] = {
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

#pragma ghs section rodata  = ".calibration_area_u1"
volatile const U1 u1_CALIB_MCUID_DUM_1B_0221       = (U1)0U;        /* Deleted content 1B-0221(Presence of AT oil temperature)       */
volatile const U1 u1_CALIB_MCUID0611_BAROLPL       = (U1)0U;        /* barOLPL                                                       */
volatile const U1 u1_CALIB_MCUID0612_BAROLPH       = (U1)80U;       /* barOLPH                                                       */
volatile const U1 u1_CALIB_MCUID0914_SOLAR_CHARGE  = (U1)1U;        /* Solar charging ON/OFF Default                                 */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0326       = (U1)0U;        /* Reserve_1B-0326                                               */
volatile const U1 u1_CALIB_MCUID1120_DESIGN_PTN    = (U1)0U;        /* Vehicle design pattern                                        */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0328       = (U1)0U;        /* Reserve_1B-0328                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0329       = (U1)0U;        /* Reserve_1B-0329                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0330       = (U1)0U;        /* Reserve_1B-0330                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0331       = (U1)0U;        /* Reserve_1B-0331                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0332       = (U1)0U;        /* Reserve_1B-0332                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0333       = (U1)0U;        /* Reserve_1B-0333                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0334       = (U1)0U;        /* Reserve_1B-0334                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0335       = (U1)0U;        /* Reserve_1B-0335                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0336       = (U1)0U;        /* Reserve_1B-0336                                               */
volatile const U1 u1_CALIB_MCUID0831_PITCH_MAX     = (U1)0U;        /* Angle of caution indication start (pitch)                     */
volatile const U1 u1_CALIB_MCUID0832_ROLL_MAX      = (U1)0U;        /* Angle of caution indication start (roll)                      */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0339       = (U1)0U;        /* Reserve_1B-0339                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0340       = (U1)0U;        /* Reserve_1B-0340                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0341       = (U1)0U;        /* Reserve_1B-0341                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0342       = (U1)0U;        /* Reserve_1B-0342                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0343       = (U1)0U;        /* Reserve_1B-0343                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0344       = (U1)0U;        /* Reserve_1B-0344                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0345       = (U1)0U;        /* Reserve_1B-0345                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0346       = (U1)0U;        /* Reserve_1B-0346                                               */
volatile const U1 u1_CALIB_MCUID_DUM_1B_0347       = (U1)0U;        /* Deleted content 1B-0347(Boost pressure Upper boundary)        */
volatile const U1 u1_CALIB_MCUID_DUM_1B_0348       = (U1)0U;        /* Deleted content 1B-0348(Boost pressure Lower boundary)        */
volatile const U1 u1_CALIB_MCUID1115_BSTPR_S_TM    = (U1)1U;        /* Boost pressure Sampling time                                  */
volatile const U1 u1_CALIB_MCUID1116_BSTPR_N_AVE   = (U1)4U;        /* Boost pressure The number of averaging processing             */
volatile const U1 u1_CALIB_MCUID1118_BSTPR_JDG     = (U1)0U;        /* Boost pressure function presence detection value              */
volatile const U1 u1_CALIB_MCUID1119_MGPWR_JDG     = (U1)0U;        /* MG Gauge function presence detection value                    */
volatile const U1 u1_CALIB_MCUID1121_BSTPR_LOGO    = (U1)0U;        /* Boost gauge/MG gauge presence determination value             */
volatile const U1 u1_CALIB_MCUID1117_I_EXHAUST_OP  = (U1)0U;        /* I_EXHAUST_OP                                                  */
volatile const U1 u1_CALIB_MCUID1123_M_GVIF_FLG    = (U1)0U;        /* M_GVIF_FLG                                                    */
volatile const U1 u1_CALIB_MCUID1122_AT_OIL_TEMP   = (U1)0U;        /* Presence of AT oil temperature indication function            */
volatile const U1 u1_CALIB_MCUID1113_BSTPR_UP      = (U1)30U;       /* Boost pressure Upper boundary of gauge                        */
volatile const U1 u1_CALIB_MCUID1114_BSTPR_LO      = (U1)10U;       /* Boost pressure Lower boundary of gauge                        */
volatile const U1 u1_CALIB_MCUID1124_HUD_SIZE      = (U1)1U;        /* HUD Size                                                      */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0360       = (U1)0U;        /* Reserve_1B-0360                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0361       = (U1)0U;        /* Reserve_1B-0361                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0362       = (U1)0U;        /* Reserve_1B-0362                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0363       = (U1)0U;        /* Reserve_1B-0363                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0364       = (U1)0U;        /* Reserve_1B-0364                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0365       = (U1)0U;        /* Reserve_1B-0365                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0366       = (U1)0U;        /* Reserve_1B-0366                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0367       = (U1)0U;        /* Reserve_1B-0367                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0368       = (U1)0U;        /* Reserve_1B-0368                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0369       = (U1)0U;        /* Reserve_1B-0369                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0370       = (U1)0U;        /* Reserve_1B-0370                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0371       = (U1)0U;        /* Reserve_1B-0371                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0372       = (U1)0U;        /* Reserve_1B-0372                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0373       = (U1)0U;        /* Reserve_1B-0373                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0374       = (U1)0U;        /* Reserve_1B-0374                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0375       = (U1)0U;        /* Reserve_1B-0375                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0376       = (U1)0U;        /* Reserve_1B-0376                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0377       = (U1)0U;        /* Reserve_1B-0377                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0378       = (U1)0U;        /* Reserve_1B-0378                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0379       = (U1)0U;        /* Reserve_1B-0379                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0380       = (U1)0U;        /* Reserve_1B-0380                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0381       = (U1)0U;        /* Reserve_1B-0381                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0382       = (U1)0U;        /* Reserve_1B-0382                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0383       = (U1)0U;        /* Reserve_1B-0383                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0384       = (U1)0U;        /* Reserve_1B-0384                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0385       = (U1)0U;        /* Reserve_1B-0385                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0386       = (U1)0U;        /* Reserve_1B-0386                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0387       = (U1)0U;        /* Reserve_1B-0387                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0388       = (U1)0U;        /* Reserve_1B-0388                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0389       = (U1)0U;        /* Reserve_1B-0389                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0390       = (U1)0U;        /* Reserve_1B-0390                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0391       = (U1)0U;        /* Reserve_1B-0391                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0392       = (U1)0U;        /* Reserve_1B-0392                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0393       = (U1)0U;        /* Reserve_1B-0393                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0394       = (U1)0U;        /* Reserve_1B-0394                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0395       = (U1)0U;        /* Reserve_1B-0395                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0396       = (U1)0U;        /* Reserve_1B-0396                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0397       = (U1)0U;        /* Reserve_1B-0397                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0398       = (U1)0U;        /* Reserve_1B-0398                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0399       = (U1)0U;        /* Reserve_1B-0399                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0400       = (U1)0U;        /* Reserve_1B-0400                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0401       = (U1)0U;        /* Reserve_1B-0401                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0402       = (U1)0U;        /* Reserve_1B-0402                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0403       = (U1)0U;        /* Reserve_1B-0403                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0404       = (U1)0U;        /* Reserve_1B-0404                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0405       = (U1)0U;        /* Reserve_1B-0405                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0406       = (U1)0U;        /* Reserve_1B-0406                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0407       = (U1)0U;        /* Reserve_1B-0407                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0408       = (U1)0U;        /* Reserve_1B-0408                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0409       = (U1)0U;        /* Reserve_1B-0409                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0410       = (U1)0U;        /* Reserve_1B-0410                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0411       = (U1)0U;        /* Reserve_1B-0411                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0412       = (U1)0U;        /* Reserve_1B-0412                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0413       = (U1)0U;        /* Reserve_1B-0413                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0414       = (U1)0U;        /* Reserve_1B-0414                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0415       = (U1)0U;        /* Reserve_1B-0415                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0416       = (U1)0U;        /* Reserve_1B-0416                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0417       = (U1)0U;        /* Reserve_1B-0417                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0418       = (U1)0U;        /* Reserve_1B-0418                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0419       = (U1)0U;        /* Reserve_1B-0419                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0420       = (U1)0U;        /* Reserve_1B-0420                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0421       = (U1)0U;        /* Reserve_1B-0421                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0422       = (U1)0U;        /* Reserve_1B-0422                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0423       = (U1)0U;        /* Reserve_1B-0423                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0424       = (U1)0U;        /* Reserve_1B-0424                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0425       = (U1)0U;        /* Reserve_1B-0425                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0426       = (U1)0U;        /* Reserve_1B-0426                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0427       = (U1)0U;        /* Reserve_1B-0427                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0428       = (U1)0U;        /* Reserve_1B-0428                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0429       = (U1)0U;        /* Reserve_1B-0429                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0430       = (U1)0U;        /* Reserve_1B-0430                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0431       = (U1)0U;        /* Reserve_1B-0431                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0432       = (U1)0U;        /* Reserve_1B-0432                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0433       = (U1)0U;        /* Reserve_1B-0433                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0434       = (U1)0U;        /* Reserve_1B-0434                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0435       = (U1)0U;        /* Reserve_1B-0435                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0436       = (U1)0U;        /* Reserve_1B-0436                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0437       = (U1)0U;        /* Reserve_1B-0437                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0438       = (U1)0U;        /* Reserve_1B-0438                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0439       = (U1)0U;        /* Reserve_1B-0439                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0440       = (U1)0U;        /* Reserve_1B-0440                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0441       = (U1)0U;        /* Reserve_1B-0441                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0442       = (U1)0U;        /* Reserve_1B-0442                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0443       = (U1)0U;        /* Reserve_1B-0443                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0444       = (U1)0U;        /* Reserve_1B-0444                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0445       = (U1)0U;        /* Reserve_1B-0445                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0446       = (U1)0U;        /* Reserve_1B-0446                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0447       = (U1)0U;        /* Reserve_1B-0447                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0448       = (U1)0U;        /* Reserve_1B-0448                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0449       = (U1)0U;        /* Reserve_1B-0449                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0450       = (U1)0U;        /* Reserve_1B-0450                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0451       = (U1)0U;        /* Reserve_1B-0451                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0452       = (U1)0U;        /* Reserve_1B-0452                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0453       = (U1)0U;        /* Reserve_1B-0453                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0454       = (U1)0U;        /* Reserve_1B-0454                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0455       = (U1)0U;        /* Reserve_1B-0455                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0456       = (U1)0U;        /* Reserve_1B-0456                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0457       = (U1)0U;        /* Reserve_1B-0457                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0458       = (U1)0U;        /* Reserve_1B-0458                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0459       = (U1)0U;        /* Reserve_1B-0459                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0460       = (U1)0U;        /* Reserve_1B-0460                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0461       = (U1)0U;        /* Reserve_1B-0461                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0462       = (U1)0U;        /* Reserve_1B-0462                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0463       = (U1)0U;        /* Reserve_1B-0463                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0464       = (U1)0U;        /* Reserve_1B-0464                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0465       = (U1)0U;        /* Reserve_1B-0465                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0466       = (U1)0U;        /* Reserve_1B-0466                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0467       = (U1)0U;        /* Reserve_1B-0467                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0468       = (U1)0U;        /* Reserve_1B-0468                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0469       = (U1)0U;        /* Reserve_1B-0469                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0470       = (U1)0U;        /* Reserve_1B-0470                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0471       = (U1)0U;        /* Reserve_1B-0471                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0472       = (U1)0U;        /* Reserve_1B-0472                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0473       = (U1)0U;        /* Reserve_1B-0473                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0474       = (U1)0U;        /* Reserve_1B-0474                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0475       = (U1)0U;        /* Reserve_1B-0475                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0476       = (U1)0U;        /* Reserve_1B-0476                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0477       = (U1)0U;        /* Reserve_1B-0477                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0478       = (U1)0U;        /* Reserve_1B-0478                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0479       = (U1)0U;        /* Reserve_1B-0479                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0480       = (U1)0U;        /* Reserve_1B-0480                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0481       = (U1)0U;        /* Reserve_1B-0481                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0482       = (U1)0U;        /* Reserve_1B-0482                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0483       = (U1)0U;        /* Reserve_1B-0483                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0484       = (U1)0U;        /* Reserve_1B-0484                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0485       = (U1)0U;        /* Reserve_1B-0485                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0486       = (U1)0U;        /* Reserve_1B-0486                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0487       = (U1)0U;        /* Reserve_1B-0487                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0488       = (U1)0U;        /* Reserve_1B-0488                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0489       = (U1)0U;        /* Reserve_1B-0489                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0490       = (U1)0U;        /* Reserve_1B-0490                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0491       = (U1)0U;        /* Reserve_1B-0491                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0492       = (U1)0U;        /* Reserve_1B-0492                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0493       = (U1)0U;        /* Reserve_1B-0493                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0494       = (U1)0U;        /* Reserve_1B-0494                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0495       = (U1)0U;        /* Reserve_1B-0495                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0496       = (U1)0U;        /* Reserve_1B-0496                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0497       = (U1)0U;        /* Reserve_1B-0497                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0498       = (U1)0U;        /* Reserve_1B-0498                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0499       = (U1)0U;        /* Reserve_1B-0499                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0500       = (U1)0U;        /* Reserve_1B-0500                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0501       = (U1)0U;        /* Reserve_1B-0501                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0502       = (U1)0U;        /* Reserve_1B-0502                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0503       = (U1)0U;        /* Reserve_1B-0503                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0504       = (U1)0U;        /* Reserve_1B-0504                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0505       = (U1)0U;        /* Reserve_1B-0505                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0506       = (U1)0U;        /* Reserve_1B-0506                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0507       = (U1)0U;        /* Reserve_1B-0507                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0508       = (U1)0U;        /* Reserve_1B-0508                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0509       = (U1)0U;        /* Reserve_1B-0509                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0510       = (U1)0U;        /* Reserve_1B-0510                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0511       = (U1)0U;        /* Reserve_1B-0511                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0512       = (U1)0U;        /* Reserve_1B-0512                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0513       = (U1)0U;        /* Reserve_1B-0513                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0514       = (U1)0U;        /* Reserve_1B-0514                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0515       = (U1)0U;        /* Reserve_1B-0515                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0516       = (U1)0U;        /* Reserve_1B-0516                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0517       = (U1)0U;        /* Reserve_1B-0517                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0518       = (U1)0U;        /* Reserve_1B-0518                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0519       = (U1)0U;        /* Reserve_1B-0519                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0520       = (U1)0U;        /* Reserve_1B-0520                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0521       = (U1)0U;        /* Reserve_1B-0521                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0522       = (U1)0U;        /* Reserve_1B-0522                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0523       = (U1)0U;        /* Reserve_1B-0523                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0524       = (U1)0U;        /* Reserve_1B-0524                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0525       = (U1)0U;        /* Reserve_1B-0525                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0526       = (U1)0U;        /* Reserve_1B-0526                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0527       = (U1)0U;        /* Reserve_1B-0527                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0528       = (U1)0U;        /* Reserve_1B-0528                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0529       = (U1)0U;        /* Reserve_1B-0529                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0530       = (U1)0U;        /* Reserve_1B-0530                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0531       = (U1)0U;        /* Reserve_1B-0531                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0532       = (U1)0U;        /* Reserve_1B-0532                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0533       = (U1)0U;        /* Reserve_1B-0533                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0534       = (U1)0U;        /* Reserve_1B-0534                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0535       = (U1)0U;        /* Reserve_1B-0535                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0536       = (U1)0U;        /* Reserve_1B-0536                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0537       = (U1)0U;        /* Reserve_1B-0537                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0538       = (U1)0U;        /* Reserve_1B-0538                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0539       = (U1)0U;        /* Reserve_1B-0539                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0540       = (U1)0U;        /* Reserve_1B-0540                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0541       = (U1)0U;        /* Reserve_1B-0541                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0542       = (U1)0U;        /* Reserve_1B-0542                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0543       = (U1)0U;        /* Reserve_1B-0543                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0544       = (U1)0U;        /* Reserve_1B-0544                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0545       = (U1)0U;        /* Reserve_1B-0545                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0546       = (U1)0U;        /* Reserve_1B-0546                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0547       = (U1)0U;        /* Reserve_1B-0547                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0548       = (U1)0U;        /* Reserve_1B-0548                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0549       = (U1)0U;        /* Reserve_1B-0549                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0550       = (U1)0U;        /* Reserve_1B-0550                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0551       = (U1)0U;        /* Reserve_1B-0551                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0552       = (U1)0U;        /* Reserve_1B-0552                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0553       = (U1)0U;        /* Reserve_1B-0553                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0554       = (U1)0U;        /* Reserve_1B-0554                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0555       = (U1)0U;        /* Reserve_1B-0555                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0556       = (U1)0U;        /* Reserve_1B-0556                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0557       = (U1)0U;        /* Reserve_1B-0557                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0558       = (U1)0U;        /* Reserve_1B-0558                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0559       = (U1)0U;        /* Reserve_1B-0559                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0560       = (U1)0U;        /* Reserve_1B-0560                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0561       = (U1)0U;        /* Reserve_1B-0561                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0562       = (U1)0U;        /* Reserve_1B-0562                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0563       = (U1)0U;        /* Reserve_1B-0563                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0564       = (U1)0U;        /* Reserve_1B-0564                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0565       = (U1)0U;        /* Reserve_1B-0565                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0566       = (U1)0U;        /* Reserve_1B-0566                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0567       = (U1)0U;        /* Reserve_1B-0567                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0568       = (U1)0U;        /* Reserve_1B-0568                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0569       = (U1)0U;        /* Reserve_1B-0569                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0570       = (U1)0U;        /* Reserve_1B-0570                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0571       = (U1)0U;        /* Reserve_1B-0571                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0572       = (U1)0U;        /* Reserve_1B-0572                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0573       = (U1)0U;        /* Reserve_1B-0573                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0574       = (U1)0U;        /* Reserve_1B-0574                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0575       = (U1)0U;        /* Reserve_1B-0575                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0576       = (U1)0U;        /* Reserve_1B-0576                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0577       = (U1)0U;        /* Reserve_1B-0577                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0578       = (U1)0U;        /* Reserve_1B-0578                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0579       = (U1)0U;        /* Reserve_1B-0579                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0580       = (U1)0U;        /* Reserve_1B-0580                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0581       = (U1)0U;        /* Reserve_1B-0581                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0582       = (U1)0U;        /* Reserve_1B-0582                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0583       = (U1)0U;        /* Reserve_1B-0583                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0584       = (U1)0U;        /* Reserve_1B-0584                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0585       = (U1)0U;        /* Reserve_1B-0585                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0586       = (U1)0U;        /* Reserve_1B-0586                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0587       = (U1)0U;        /* Reserve_1B-0587                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0588       = (U1)0U;        /* Reserve_1B-0588                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0589       = (U1)0U;        /* Reserve_1B-0589                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0590       = (U1)0U;        /* Reserve_1B-0590                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0591       = (U1)0U;        /* Reserve_1B-0591                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0592       = (U1)0U;        /* Reserve_1B-0592                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0593       = (U1)0U;        /* Reserve_1B-0593                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0594       = (U1)0U;        /* Reserve_1B-0594                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0595       = (U1)0U;        /* Reserve_1B-0595                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0596       = (U1)0U;        /* Reserve_1B-0596                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0597       = (U1)0U;        /* Reserve_1B-0597                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0598       = (U1)0U;        /* Reserve_1B-0598                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0599       = (U1)0U;        /* Reserve_1B-0599                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0600       = (U1)0U;        /* Reserve_1B-0600                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0601       = (U1)0U;        /* Reserve_1B-0601                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0602       = (U1)0U;        /* Reserve_1B-0602                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0603       = (U1)0U;        /* Reserve_1B-0603                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0604       = (U1)0U;        /* Reserve_1B-0604                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0605       = (U1)0U;        /* Reserve_1B-0605                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0606       = (U1)0U;        /* Reserve_1B-0606                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0607       = (U1)0U;        /* Reserve_1B-0607                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0608       = (U1)0U;        /* Reserve_1B-0608                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0609       = (U1)0U;        /* Reserve_1B-0609                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0610       = (U1)0U;        /* Reserve_1B-0610                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0611       = (U1)0U;        /* Reserve_1B-0611                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0612       = (U1)0U;        /* Reserve_1B-0612                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0613       = (U1)0U;        /* Reserve_1B-0613                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0614       = (U1)0U;        /* Reserve_1B-0614                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0615       = (U1)0U;        /* Reserve_1B-0615                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0616       = (U1)0U;        /* Reserve_1B-0616                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0617       = (U1)0U;        /* Reserve_1B-0617                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0618       = (U1)0U;        /* Reserve_1B-0618                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0619       = (U1)0U;        /* Reserve_1B-0619                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0620       = (U1)0U;        /* Reserve_1B-0620                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0621       = (U1)0U;        /* Reserve_1B-0621                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0622       = (U1)0U;        /* Reserve_1B-0622                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0623       = (U1)0U;        /* Reserve_1B-0623                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0624       = (U1)0U;        /* Reserve_1B-0624                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0625       = (U1)0U;        /* Reserve_1B-0625                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0626       = (U1)0U;        /* Reserve_1B-0626                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0627       = (U1)0U;        /* Reserve_1B-0627                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0628       = (U1)0U;        /* Reserve_1B-0628                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0629       = (U1)0U;        /* Reserve_1B-0629                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0630       = (U1)0U;        /* Reserve_1B-0630                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0631       = (U1)0U;        /* Reserve_1B-0631                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0632       = (U1)0U;        /* Reserve_1B-0632                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0633       = (U1)0U;        /* Reserve_1B-0633                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0634       = (U1)0U;        /* Reserve_1B-0634                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0635       = (U1)0U;        /* Reserve_1B-0635                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0636       = (U1)0U;        /* Reserve_1B-0636                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0637       = (U1)0U;        /* Reserve_1B-0637                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0638       = (U1)0U;        /* Reserve_1B-0638                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0639       = (U1)0U;        /* Reserve_1B-0639                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0640       = (U1)0U;        /* Reserve_1B-0640                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0641       = (U1)0U;        /* Reserve_1B-0641                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0642       = (U1)0U;        /* Reserve_1B-0642                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0643       = (U1)0U;        /* Reserve_1B-0643                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0644       = (U1)0U;        /* Reserve_1B-0644                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0645       = (U1)0U;        /* Reserve_1B-0645                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0646       = (U1)0U;        /* Reserve_1B-0646                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0647       = (U1)0U;        /* Reserve_1B-0647                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0648       = (U1)0U;        /* Reserve_1B-0648                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0649       = (U1)0U;        /* Reserve_1B-0649                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0650       = (U1)0U;        /* Reserve_1B-0650                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0651       = (U1)0U;        /* Reserve_1B-0651                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0652       = (U1)0U;        /* Reserve_1B-0652                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0653       = (U1)0U;        /* Reserve_1B-0653                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0654       = (U1)0U;        /* Reserve_1B-0654                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0655       = (U1)0U;        /* Reserve_1B-0655                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0656       = (U1)0U;        /* Reserve_1B-0656                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0657       = (U1)0U;        /* Reserve_1B-0657                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0658       = (U1)0U;        /* Reserve_1B-0658                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0659       = (U1)0U;        /* Reserve_1B-0659                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0660       = (U1)0U;        /* Reserve_1B-0660                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0661       = (U1)0U;        /* Reserve_1B-0661                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0662       = (U1)0U;        /* Reserve_1B-0662                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0663       = (U1)0U;        /* Reserve_1B-0663                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0664       = (U1)0U;        /* Reserve_1B-0664                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0665       = (U1)0U;        /* Reserve_1B-0665                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0666       = (U1)0U;        /* Reserve_1B-0666                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0667       = (U1)0U;        /* Reserve_1B-0667                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0668       = (U1)0U;        /* Reserve_1B-0668                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0669       = (U1)0U;        /* Reserve_1B-0669                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0670       = (U1)0U;        /* Reserve_1B-0670                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0671       = (U1)0U;        /* Reserve_1B-0671                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0672       = (U1)0U;        /* Reserve_1B-0672                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0673       = (U1)0U;        /* Reserve_1B-0673                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0674       = (U1)0U;        /* Reserve_1B-0674                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0675       = (U1)0U;        /* Reserve_1B-0675                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0676       = (U1)0U;        /* Reserve_1B-0676                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0677       = (U1)0U;        /* Reserve_1B-0677                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0678       = (U1)0U;        /* Reserve_1B-0678                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0679       = (U1)0U;        /* Reserve_1B-0679                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0680       = (U1)0U;        /* Reserve_1B-0680                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0681       = (U1)0U;        /* Reserve_1B-0681                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0682       = (U1)0U;        /* Reserve_1B-0682                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0683       = (U1)0U;        /* Reserve_1B-0683                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0684       = (U1)0U;        /* Reserve_1B-0684                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0685       = (U1)0U;        /* Reserve_1B-0685                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0686       = (U1)0U;        /* Reserve_1B-0686                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0687       = (U1)0U;        /* Reserve_1B-0687                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0688       = (U1)0U;        /* Reserve_1B-0688                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0689       = (U1)0U;        /* Reserve_1B-0689                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0690       = (U1)0U;        /* Reserve_1B-0690                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0691       = (U1)0U;        /* Reserve_1B-0691                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0692       = (U1)0U;        /* Reserve_1B-0692                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0693       = (U1)0U;        /* Reserve_1B-0693                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0694       = (U1)0U;        /* Reserve_1B-0694                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0695       = (U1)0U;        /* Reserve_1B-0695                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0696       = (U1)0U;        /* Reserve_1B-0696                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0697       = (U1)0U;        /* Reserve_1B-0697                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0698       = (U1)0U;        /* Reserve_1B-0698                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0699       = (U1)0U;        /* Reserve_1B-0699                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0700       = (U1)0U;        /* Reserve_1B-0700                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0701       = (U1)0U;        /* Reserve_1B-0701                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0702       = (U1)0U;        /* Reserve_1B-0702                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0703       = (U1)0U;        /* Reserve_1B-0703                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0704       = (U1)0U;        /* Reserve_1B-0704                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0705       = (U1)0U;        /* Reserve_1B-0705                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0706       = (U1)0U;        /* Reserve_1B-0706                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0707       = (U1)0U;        /* Reserve_1B-0707                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0708       = (U1)0U;        /* Reserve_1B-0708                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0709       = (U1)0U;        /* Reserve_1B-0709                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0710       = (U1)0U;        /* Reserve_1B-0710                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0711       = (U1)0U;        /* Reserve_1B-0711                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0712       = (U1)0U;        /* Reserve_1B-0712                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0713       = (U1)0U;        /* Reserve_1B-0713                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0714       = (U1)0U;        /* Reserve_1B-0714                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0715       = (U1)0U;        /* Reserve_1B-0715                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0716       = (U1)0U;        /* Reserve_1B-0716                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0717       = (U1)0U;        /* Reserve_1B-0717                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0718       = (U1)0U;        /* Reserve_1B-0718                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0719       = (U1)0U;        /* Reserve_1B-0719                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0720       = (U1)0U;        /* Reserve_1B-0720                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0721       = (U1)0U;        /* Reserve_1B-0721                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0722       = (U1)0U;        /* Reserve_1B-0722                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0723       = (U1)0U;        /* Reserve_1B-0723                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0724       = (U1)0U;        /* Reserve_1B-0724                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0725       = (U1)0U;        /* Reserve_1B-0725                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0726       = (U1)0U;        /* Reserve_1B-0726                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0727       = (U1)0U;        /* Reserve_1B-0727                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0728       = (U1)0U;        /* Reserve_1B-0728                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0729       = (U1)0U;        /* Reserve_1B-0729                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0730       = (U1)0U;        /* Reserve_1B-0730                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0731       = (U1)0U;        /* Reserve_1B-0731                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0732       = (U1)0U;        /* Reserve_1B-0732                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0733       = (U1)0U;        /* Reserve_1B-0733                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0734       = (U1)0U;        /* Reserve_1B-0734                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0735       = (U1)0U;        /* Reserve_1B-0735                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0736       = (U1)0U;        /* Reserve_1B-0736                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0737       = (U1)0U;        /* Reserve_1B-0737                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0738       = (U1)0U;        /* Reserve_1B-0738                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0739       = (U1)0U;        /* Reserve_1B-0739                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0740       = (U1)0U;        /* Reserve_1B-0740                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0741       = (U1)0U;        /* Reserve_1B-0741                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0742       = (U1)0U;        /* Reserve_1B-0742                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0743       = (U1)0U;        /* Reserve_1B-0743                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0744       = (U1)0U;        /* Reserve_1B-0744                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0745       = (U1)0U;        /* Reserve_1B-0745                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0746       = (U1)0U;        /* Reserve_1B-0746                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0747       = (U1)0U;        /* Reserve_1B-0747                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0748       = (U1)0U;        /* Reserve_1B-0748                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0749       = (U1)0U;        /* Reserve_1B-0749                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0750       = (U1)0U;        /* Reserve_1B-0750                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0751       = (U1)0U;        /* Reserve_1B-0751                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0752       = (U1)0U;        /* Reserve_1B-0752                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0753       = (U1)0U;        /* Reserve_1B-0753                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0754       = (U1)0U;        /* Reserve_1B-0754                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0755       = (U1)0U;        /* Reserve_1B-0755                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0756       = (U1)0U;        /* Reserve_1B-0756                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0757       = (U1)0U;        /* Reserve_1B-0757                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0758       = (U1)0U;        /* Reserve_1B-0758                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0759       = (U1)0U;        /* Reserve_1B-0759                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0760       = (U1)0U;        /* Reserve_1B-0760                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0761       = (U1)0U;        /* Reserve_1B-0761                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0762       = (U1)0U;        /* Reserve_1B-0762                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0763       = (U1)0U;        /* Reserve_1B-0763                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0764       = (U1)0U;        /* Reserve_1B-0764                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0765       = (U1)0U;        /* Reserve_1B-0765                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0766       = (U1)0U;        /* Reserve_1B-0766                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0767       = (U1)0U;        /* Reserve_1B-0767                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0768       = (U1)0U;        /* Reserve_1B-0768                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0769       = (U1)0U;        /* Reserve_1B-0769                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0770       = (U1)0U;        /* Reserve_1B-0770                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0771       = (U1)0U;        /* Reserve_1B-0771                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0772       = (U1)0U;        /* Reserve_1B-0772                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0773       = (U1)0U;        /* Reserve_1B-0773                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0774       = (U1)0U;        /* Reserve_1B-0774                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0775       = (U1)0U;        /* Reserve_1B-0775                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0776       = (U1)0U;        /* Reserve_1B-0776                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0777       = (U1)0U;        /* Reserve_1B-0777                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0778       = (U1)0U;        /* Reserve_1B-0778                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0779       = (U1)0U;        /* Reserve_1B-0779                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0780       = (U1)0U;        /* Reserve_1B-0780                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0781       = (U1)0U;        /* Reserve_1B-0781                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0782       = (U1)0U;        /* Reserve_1B-0782                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0783       = (U1)0U;        /* Reserve_1B-0783                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0784       = (U1)0U;        /* Reserve_1B-0784                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0785       = (U1)0U;        /* Reserve_1B-0785                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0786       = (U1)0U;        /* Reserve_1B-0786                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0787       = (U1)0U;        /* Reserve_1B-0787                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0788       = (U1)0U;        /* Reserve_1B-0788                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0789       = (U1)0U;        /* Reserve_1B-0789                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0790       = (U1)0U;        /* Reserve_1B-0790                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0791       = (U1)0U;        /* Reserve_1B-0791                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0792       = (U1)0U;        /* Reserve_1B-0792                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0793       = (U1)0U;        /* Reserve_1B-0793                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0794       = (U1)0U;        /* Reserve_1B-0794                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0795       = (U1)0U;        /* Reserve_1B-0795                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0796       = (U1)0U;        /* Reserve_1B-0796                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0797       = (U1)0U;        /* Reserve_1B-0797                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0798       = (U1)0U;        /* Reserve_1B-0798                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0799       = (U1)0U;        /* Reserve_1B-0799                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0800       = (U1)0U;        /* Reserve_1B-0800                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0801       = (U1)0U;        /* Reserve_1B-0801                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0802       = (U1)0U;        /* Reserve_1B-0802                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0803       = (U1)0U;        /* Reserve_1B-0803                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0804       = (U1)0U;        /* Reserve_1B-0804                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0805       = (U1)0U;        /* Reserve_1B-0805                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0806       = (U1)0U;        /* Reserve_1B-0806                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0807       = (U1)0U;        /* Reserve_1B-0807                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0808       = (U1)0U;        /* Reserve_1B-0808                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0809       = (U1)0U;        /* Reserve_1B-0809                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0810       = (U1)0U;        /* Reserve_1B-0810                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0811       = (U1)0U;        /* Reserve_1B-0811                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0812       = (U1)0U;        /* Reserve_1B-0812                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0813       = (U1)0U;        /* Reserve_1B-0813                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0814       = (U1)0U;        /* Reserve_1B-0814                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0815       = (U1)0U;        /* Reserve_1B-0815                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0816       = (U1)0U;        /* Reserve_1B-0816                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0817       = (U1)0U;        /* Reserve_1B-0817                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0818       = (U1)0U;        /* Reserve_1B-0818                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0819       = (U1)0U;        /* Reserve_1B-0819                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0820       = (U1)0U;        /* Reserve_1B-0820                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0821       = (U1)0U;        /* Reserve_1B-0821                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0822       = (U1)0U;        /* Reserve_1B-0822                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0823       = (U1)0U;        /* Reserve_1B-0823                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0824       = (U1)0U;        /* Reserve_1B-0824                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0825       = (U1)0U;        /* Reserve_1B-0825                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0826       = (U1)0U;        /* Reserve_1B-0826                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0827       = (U1)0U;        /* Reserve_1B-0827                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0828       = (U1)0U;        /* Reserve_1B-0828                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0829       = (U1)0U;        /* Reserve_1B-0829                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0830       = (U1)0U;        /* Reserve_1B-0830                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0831       = (U1)0U;        /* Reserve_1B-0831                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0832       = (U1)0U;        /* Reserve_1B-0832                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0833       = (U1)0U;        /* Reserve_1B-0833                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0834       = (U1)0U;        /* Reserve_1B-0834                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0835       = (U1)0U;        /* Reserve_1B-0835                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0836       = (U1)0U;        /* Reserve_1B-0836                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0837       = (U1)0U;        /* Reserve_1B-0837                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0838       = (U1)0U;        /* Reserve_1B-0838                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0839       = (U1)0U;        /* Reserve_1B-0839                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0840       = (U1)0U;        /* Reserve_1B-0840                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0841       = (U1)0U;        /* Reserve_1B-0841                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0842       = (U1)0U;        /* Reserve_1B-0842                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0843       = (U1)0U;        /* Reserve_1B-0843                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0844       = (U1)0U;        /* Reserve_1B-0844                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0845       = (U1)0U;        /* Reserve_1B-0845                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0846       = (U1)0U;        /* Reserve_1B-0846                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0847       = (U1)0U;        /* Reserve_1B-0847                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0848       = (U1)0U;        /* Reserve_1B-0848                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0849       = (U1)0U;        /* Reserve_1B-0849                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0850       = (U1)0U;        /* Reserve_1B-0850                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0851       = (U1)0U;        /* Reserve_1B-0851                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0852       = (U1)0U;        /* Reserve_1B-0852                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0853       = (U1)0U;        /* Reserve_1B-0853                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0854       = (U1)0U;        /* Reserve_1B-0854                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0855       = (U1)0U;        /* Reserve_1B-0855                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0856       = (U1)0U;        /* Reserve_1B-0856                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0857       = (U1)0U;        /* Reserve_1B-0857                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0858       = (U1)0U;        /* Reserve_1B-0858                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0859       = (U1)0U;        /* Reserve_1B-0859                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0860       = (U1)0U;        /* Reserve_1B-0860                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0861       = (U1)0U;        /* Reserve_1B-0861                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0862       = (U1)0U;        /* Reserve_1B-0862                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0863       = (U1)0U;        /* Reserve_1B-0863                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0864       = (U1)0U;        /* Reserve_1B-0864                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0865       = (U1)0U;        /* Reserve_1B-0865                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0866       = (U1)0U;        /* Reserve_1B-0866                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0867       = (U1)0U;        /* Reserve_1B-0867                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0868       = (U1)0U;        /* Reserve_1B-0868                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0869       = (U1)0U;        /* Reserve_1B-0869                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0870       = (U1)0U;        /* Reserve_1B-0870                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0871       = (U1)0U;        /* Reserve_1B-0871                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0872       = (U1)0U;        /* Reserve_1B-0872                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0873       = (U1)0U;        /* Reserve_1B-0873                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0874       = (U1)0U;        /* Reserve_1B-0874                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0875       = (U1)0U;        /* Reserve_1B-0875                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0876       = (U1)0U;        /* Reserve_1B-0876                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0877       = (U1)0U;        /* Reserve_1B-0877                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0878       = (U1)0U;        /* Reserve_1B-0878                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0879       = (U1)0U;        /* Reserve_1B-0879                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0880       = (U1)0U;        /* Reserve_1B-0880                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0881       = (U1)0U;        /* Reserve_1B-0881                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0882       = (U1)0U;        /* Reserve_1B-0882                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0883       = (U1)0U;        /* Reserve_1B-0883                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0884       = (U1)0U;        /* Reserve_1B-0884                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0885       = (U1)0U;        /* Reserve_1B-0885                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0886       = (U1)0U;        /* Reserve_1B-0886                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0887       = (U1)0U;        /* Reserve_1B-0887                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0888       = (U1)0U;        /* Reserve_1B-0888                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0889       = (U1)0U;        /* Reserve_1B-0889                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0890       = (U1)0U;        /* Reserve_1B-0890                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0891       = (U1)0U;        /* Reserve_1B-0891                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0892       = (U1)0U;        /* Reserve_1B-0892                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0893       = (U1)0U;        /* Reserve_1B-0893                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0894       = (U1)0U;        /* Reserve_1B-0894                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0895       = (U1)0U;        /* Reserve_1B-0895                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0896       = (U1)0U;        /* Reserve_1B-0896                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0897       = (U1)0U;        /* Reserve_1B-0897                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0898       = (U1)0U;        /* Reserve_1B-0898                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0899       = (U1)0U;        /* Reserve_1B-0899                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0900       = (U1)0U;        /* Reserve_1B-0900                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0901       = (U1)0U;        /* Reserve_1B-0901                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0902       = (U1)0U;        /* Reserve_1B-0902                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0903       = (U1)0U;        /* Reserve_1B-0903                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0904       = (U1)0U;        /* Reserve_1B-0904                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0905       = (U1)0U;        /* Reserve_1B-0905                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0906       = (U1)0U;        /* Reserve_1B-0906                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0907       = (U1)0U;        /* Reserve_1B-0907                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0908       = (U1)0U;        /* Reserve_1B-0908                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0909       = (U1)0U;        /* Reserve_1B-0909                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0910       = (U1)0U;        /* Reserve_1B-0910                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0911       = (U1)0U;        /* Reserve_1B-0911                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0912       = (U1)0U;        /* Reserve_1B-0912                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0913       = (U1)0U;        /* Reserve_1B-0913                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0914       = (U1)0U;        /* Reserve_1B-0914                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0915       = (U1)0U;        /* Reserve_1B-0915                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0916       = (U1)0U;        /* Reserve_1B-0916                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0917       = (U1)0U;        /* Reserve_1B-0917                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0918       = (U1)0U;        /* Reserve_1B-0918                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0919       = (U1)0U;        /* Reserve_1B-0919                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0920       = (U1)0U;        /* Reserve_1B-0920                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0921       = (U1)0U;        /* Reserve_1B-0921                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0922       = (U1)0U;        /* Reserve_1B-0922                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0923       = (U1)0U;        /* Reserve_1B-0923                                               */
volatile const U1 u1_CALIB_MCUID_RSV_1B_0924       = (U1)0U;        /* Reserve_1B-0924                                               */

#pragma ghs section rodata  = ".calibration_area_u2"
volatile const U2 u2_CALIB_MCUID0915_CSR_RCTA_0    = (U2)50U;       /* RCTA buzzer CSR_VOL:0                                         */
volatile const U2 u2_CALIB_MCUID0916_CSR_RCTA_1    = (U2)60U;       /* RCTA buzzer CSR_VOL:1                                         */
volatile const U2 u2_CALIB_MCUID0917_CSR_RCTA_2    = (U2)80U;       /* RCTA buzzer CSR_VOL:2                                         */
volatile const U2 u2_CALIB_MCUID0918_CSR_RCTA_3    = (U2)100U;      /* RCTA buzzer CSR_VOL:3                                         */
volatile const U2 u2_CALIB_MCUID0919_CSR_RCTA_4    = (U2)120U;      /* RCTA buzzer CSR_VOL:4                                         */
volatile const U2 u2_CALIB_MCUID0920_CSR_RCTA_5    = (U2)150U;      /* RCTA buzzer CSR_VOL:5                                         */
volatile const U2 u2_CALIB_MCUID0921_CSR_RCTA_6    = (U2)190U;      /* RCTA buzzer CSR_VOL:6                                         */
volatile const U2 u2_CALIB_MCUID0922_CSR_RCTA_7    = (U2)240U;      /* RCTA buzzer CSR_VOL:7                                         */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0155       = (U2)0U;        /* Reserve_2B-0155                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0156       = (U2)0U;        /* Reserve_2B-0156                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0157       = (U2)0U;        /* Reserve_2B-0157                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0158       = (U2)0U;        /* Reserve_2B-0158                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0159       = (U2)0U;        /* Reserve_2B-0159                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0160       = (U2)0U;        /* Reserve_2B-0160                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0161       = (U2)0U;        /* Reserve_2B-0161                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0162       = (U2)0U;        /* Reserve_2B-0162                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0163       = (U2)0U;        /* Reserve_2B-0163                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0164       = (U2)0U;        /* Reserve_2B-0164                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0165       = (U2)0U;        /* Reserve_2B-0165                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0166       = (U2)0U;        /* Reserve_2B-0166                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0167       = (U2)0U;        /* Reserve_2B-0167                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0168       = (U2)0U;        /* Reserve_2B-0168                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0169       = (U2)0U;        /* Reserve_2B-0169                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0170       = (U2)0U;        /* Reserve_2B-0170                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0171       = (U2)0U;        /* Reserve_2B-0171                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0172       = (U2)0U;        /* Reserve_2B-0172                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0173       = (U2)0U;        /* Reserve_2B-0173                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0174       = (U2)0U;        /* Reserve_2B-0174                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0175       = (U2)0U;        /* Reserve_2B-0175                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0176       = (U2)0U;        /* Reserve_2B-0176                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0177       = (U2)0U;        /* Reserve_2B-0177                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0178       = (U2)0U;        /* Reserve_2B-0178                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0179       = (U2)0U;        /* Reserve_2B-0179                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0180       = (U2)0U;        /* Reserve_2B-0180                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0181       = (U2)0U;        /* Reserve_2B-0181                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0182       = (U2)0U;        /* Reserve_2B-0182                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0183       = (U2)0U;        /* Reserve_2B-0183                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0184       = (U2)0U;        /* Reserve_2B-0184                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0185       = (U2)0U;        /* Reserve_2B-0185                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0186       = (U2)0U;        /* Reserve_2B-0186                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0187       = (U2)0U;        /* Reserve_2B-0187                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0188       = (U2)0U;        /* Reserve_2B-0188                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0189       = (U2)0U;        /* Reserve_2B-0189                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0190       = (U2)0U;        /* Reserve_2B-0190                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0191       = (U2)0U;        /* Reserve_2B-0191                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0192       = (U2)0U;        /* Reserve_2B-0192                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0193       = (U2)0U;        /* Reserve_2B-0193                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0194       = (U2)0U;        /* Reserve_2B-0194                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0195       = (U2)0U;        /* Reserve_2B-0195                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0196       = (U2)0U;        /* Reserve_2B-0196                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0197       = (U2)0U;        /* Reserve_2B-0197                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0198       = (U2)0U;        /* Reserve_2B-0198                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0199       = (U2)0U;        /* Reserve_2B-0199                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0200       = (U2)0U;        /* Reserve_2B-0200                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0201       = (U2)0U;        /* Reserve_2B-0201                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0202       = (U2)0U;        /* Reserve_2B-0202                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0203       = (U2)0U;        /* Reserve_2B-0203                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0204       = (U2)0U;        /* Reserve_2B-0204                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0205       = (U2)0U;        /* Reserve_2B-0205                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0206       = (U2)0U;        /* Reserve_2B-0206                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0207       = (U2)0U;        /* Reserve_2B-0207                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0208       = (U2)0U;        /* Reserve_2B-0208                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0209       = (U2)0U;        /* Reserve_2B-0209                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0210       = (U2)0U;        /* Reserve_2B-0210                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0211       = (U2)0U;        /* Reserve_2B-0211                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0212       = (U2)0U;        /* Reserve_2B-0212                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0213       = (U2)0U;        /* Reserve_2B-0213                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0214       = (U2)0U;        /* Reserve_2B-0214                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0215       = (U2)0U;        /* Reserve_2B-0215                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0216       = (U2)0U;        /* Reserve_2B-0216                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0217       = (U2)0U;        /* Reserve_2B-0217                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0218       = (U2)0U;        /* Reserve_2B-0218                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0219       = (U2)0U;        /* Reserve_2B-0219                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0220       = (U2)0U;        /* Reserve_2B-0220                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0221       = (U2)0U;        /* Reserve_2B-0221                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0222       = (U2)0U;        /* Reserve_2B-0222                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0223       = (U2)0U;        /* Reserve_2B-0223                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0224       = (U2)0U;        /* Reserve_2B-0224                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0225       = (U2)0U;        /* Reserve_2B-0225                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0226       = (U2)0U;        /* Reserve_2B-0226                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0227       = (U2)0U;        /* Reserve_2B-0227                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0414       = (U2)0U;        /* Reserve_2B-0414                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0415       = (U2)0U;        /* Reserve_2B-0415                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0416       = (U2)0U;        /* Reserve_2B-0416                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0417       = (U2)0U;        /* Reserve_2B-0417                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0418       = (U2)0U;        /* Reserve_2B-0418                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0419       = (U2)0U;        /* Reserve_2B-0419                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0420       = (U2)0U;        /* Reserve_2B-0420                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0421       = (U2)0U;        /* Reserve_2B-0421                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0422       = (U2)0U;        /* Reserve_2B-0422                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0423       = (U2)0U;        /* Reserve_2B-0423                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0424       = (U2)0U;        /* Reserve_2B-0424                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0425       = (U2)0U;        /* Reserve_2B-0425                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0426       = (U2)0U;        /* Reserve_2B-0426                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0427       = (U2)0U;        /* Reserve_2B-0427                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0428       = (U2)0U;        /* Reserve_2B-0428                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0429       = (U2)0U;        /* Reserve_2B-0429                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0430       = (U2)0U;        /* Reserve_2B-0430                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0431       = (U2)0U;        /* Reserve_2B-0431                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0432       = (U2)0U;        /* Reserve_2B-0432                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0433       = (U2)0U;        /* Reserve_2B-0433                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0434       = (U2)0U;        /* Reserve_2B-0434                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0435       = (U2)0U;        /* Reserve_2B-0435                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0436       = (U2)0U;        /* Reserve_2B-0436                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0437       = (U2)0U;        /* Reserve_2B-0437                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0438       = (U2)0U;        /* Reserve_2B-0438                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0439       = (U2)0U;        /* Reserve_2B-0439                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0440       = (U2)0U;        /* Reserve_2B-0440                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0441       = (U2)0U;        /* Reserve_2B-0441                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0442       = (U2)0U;        /* Reserve_2B-0442                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0443       = (U2)0U;        /* Reserve_2B-0443                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0444       = (U2)0U;        /* Reserve_2B-0444                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0445       = (U2)0U;        /* Reserve_2B-0445                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0446       = (U2)0U;        /* Reserve_2B-0446                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0447       = (U2)0U;        /* Reserve_2B-0447                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0448       = (U2)0U;        /* Reserve_2B-0448                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0449       = (U2)0U;        /* Reserve_2B-0449                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0450       = (U2)0U;        /* Reserve_2B-0450                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0451       = (U2)0U;        /* Reserve_2B-0451                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0452       = (U2)0U;        /* Reserve_2B-0452                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0453       = (U2)0U;        /* Reserve_2B-0453                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0454       = (U2)0U;        /* Reserve_2B-0454                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0455       = (U2)0U;        /* Reserve_2B-0455                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0456       = (U2)0U;        /* Reserve_2B-0456                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0457       = (U2)0U;        /* Reserve_2B-0457                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0458       = (U2)0U;        /* Reserve_2B-0458                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0459       = (U2)0U;        /* Reserve_2B-0459                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0460       = (U2)0U;        /* Reserve_2B-0460                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0461       = (U2)0U;        /* Reserve_2B-0461                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0462       = (U2)0U;        /* Reserve_2B-0462                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0463       = (U2)0U;        /* Reserve_2B-0463                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0464       = (U2)0U;        /* Reserve_2B-0464                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0465       = (U2)0U;        /* Reserve_2B-0465                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0466       = (U2)0U;        /* Reserve_2B-0466                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0467       = (U2)0U;        /* Reserve_2B-0467                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0468       = (U2)0U;        /* Reserve_2B-0468                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0469       = (U2)0U;        /* Reserve_2B-0469                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0470       = (U2)0U;        /* Reserve_2B-0470                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0471       = (U2)0U;        /* Reserve_2B-0471                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0472       = (U2)0U;        /* Reserve_2B-0472                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0473       = (U2)0U;        /* Reserve_2B-0473                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0474       = (U2)0U;        /* Reserve_2B-0474                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0475       = (U2)0U;        /* Reserve_2B-0475                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0476       = (U2)0U;        /* Reserve_2B-0476                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0477       = (U2)0U;        /* Reserve_2B-0477                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0478       = (U2)0U;        /* Reserve_2B-0478                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0479       = (U2)0U;        /* Reserve_2B-0479                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0480       = (U2)0U;        /* Reserve_2B-0480                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0481       = (U2)0U;        /* Reserve_2B-0481                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0482       = (U2)0U;        /* Reserve_2B-0482                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0483       = (U2)0U;        /* Reserve_2B-0483                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0484       = (U2)0U;        /* Reserve_2B-0484                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0485       = (U2)0U;        /* Reserve_2B-0485                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0486       = (U2)0U;        /* Reserve_2B-0486                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0487       = (U2)0U;        /* Reserve_2B-0487                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0488       = (U2)0U;        /* Reserve_2B-0488                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0489       = (U2)0U;        /* Reserve_2B-0489                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0490       = (U2)0U;        /* Reserve_2B-0490                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0491       = (U2)0U;        /* Reserve_2B-0491                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0492       = (U2)0U;        /* Reserve_2B-0492                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0493       = (U2)0U;        /* Reserve_2B-0493                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0494       = (U2)0U;        /* Reserve_2B-0494                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0495       = (U2)0U;        /* Reserve_2B-0495                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0496       = (U2)0U;        /* Reserve_2B-0496                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0497       = (U2)0U;        /* Reserve_2B-0497                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0498       = (U2)0U;        /* Reserve_2B-0498                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0499       = (U2)0U;        /* Reserve_2B-0499                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0500       = (U2)0U;        /* Reserve_2B-0500                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0501       = (U2)0U;        /* Reserve_2B-0501                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0502       = (U2)0U;        /* Reserve_2B-0502                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0503       = (U2)0U;        /* Reserve_2B-0503                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0504       = (U2)0U;        /* Reserve_2B-0504                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0505       = (U2)0U;        /* Reserve_2B-0505                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0506       = (U2)0U;        /* Reserve_2B-0506                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0507       = (U2)0U;        /* Reserve_2B-0507                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0508       = (U2)0U;        /* Reserve_2B-0508                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0509       = (U2)0U;        /* Reserve_2B-0509                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0510       = (U2)0U;        /* Reserve_2B-0510                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0511       = (U2)0U;        /* Reserve_2B-0511                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0512       = (U2)0U;        /* Reserve_2B-0512                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0513       = (U2)0U;        /* Reserve_2B-0513                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0514       = (U2)0U;        /* Reserve_2B-0514                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0515       = (U2)0U;        /* Reserve_2B-0515                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0516       = (U2)0U;        /* Reserve_2B-0516                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0517       = (U2)0U;        /* Reserve_2B-0517                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0518       = (U2)0U;        /* Reserve_2B-0518                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0519       = (U2)0U;        /* Reserve_2B-0519                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0520       = (U2)0U;        /* Reserve_2B-0520                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0521       = (U2)0U;        /* Reserve_2B-0521                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0522       = (U2)0U;        /* Reserve_2B-0522                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0523       = (U2)0U;        /* Reserve_2B-0523                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0524       = (U2)0U;        /* Reserve_2B-0524                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0525       = (U2)0U;        /* Reserve_2B-0525                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0526       = (U2)0U;        /* Reserve_2B-0526                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0527       = (U2)0U;        /* Reserve_2B-0527                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0528       = (U2)0U;        /* Reserve_2B-0528                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0529       = (U2)0U;        /* Reserve_2B-0529                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0530       = (U2)0U;        /* Reserve_2B-0530                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0531       = (U2)0U;        /* Reserve_2B-0531                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0532       = (U2)0U;        /* Reserve_2B-0532                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0533       = (U2)0U;        /* Reserve_2B-0533                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0534       = (U2)0U;        /* Reserve_2B-0534                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0535       = (U2)0U;        /* Reserve_2B-0535                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0536       = (U2)0U;        /* Reserve_2B-0536                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0537       = (U2)0U;        /* Reserve_2B-0537                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0538       = (U2)0U;        /* Reserve_2B-0538                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0539       = (U2)0U;        /* Reserve_2B-0539                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0540       = (U2)0U;        /* Reserve_2B-0540                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0541       = (U2)0U;        /* Reserve_2B-0541                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0542       = (U2)0U;        /* Reserve_2B-0542                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0543       = (U2)0U;        /* Reserve_2B-0543                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0544       = (U2)0U;        /* Reserve_2B-0544                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0545       = (U2)0U;        /* Reserve_2B-0545                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0546       = (U2)0U;        /* Reserve_2B-0546                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0547       = (U2)0U;        /* Reserve_2B-0547                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0548       = (U2)0U;        /* Reserve_2B-0548                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0549       = (U2)0U;        /* Reserve_2B-0549                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0550       = (U2)0U;        /* Reserve_2B-0550                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0551       = (U2)0U;        /* Reserve_2B-0551                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0552       = (U2)0U;        /* Reserve_2B-0552                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0553       = (U2)0U;        /* Reserve_2B-0553                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0554       = (U2)0U;        /* Reserve_2B-0554                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0555       = (U2)0U;        /* Reserve_2B-0555                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0556       = (U2)0U;        /* Reserve_2B-0556                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0557       = (U2)0U;        /* Reserve_2B-0557                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0558       = (U2)0U;        /* Reserve_2B-0558                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0559       = (U2)0U;        /* Reserve_2B-0559                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0560       = (U2)0U;        /* Reserve_2B-0560                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0561       = (U2)0U;        /* Reserve_2B-0561                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0562       = (U2)0U;        /* Reserve_2B-0562                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0563       = (U2)0U;        /* Reserve_2B-0563                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0564       = (U2)0U;        /* Reserve_2B-0564                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0565       = (U2)0U;        /* Reserve_2B-0565                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0566       = (U2)0U;        /* Reserve_2B-0566                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0567       = (U2)0U;        /* Reserve_2B-0567                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0568       = (U2)0U;        /* Reserve_2B-0568                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0569       = (U2)0U;        /* Reserve_2B-0569                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0570       = (U2)0U;        /* Reserve_2B-0570                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0571       = (U2)0U;        /* Reserve_2B-0571                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0572       = (U2)0U;        /* Reserve_2B-0572                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0573       = (U2)0U;        /* Reserve_2B-0573                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0574       = (U2)0U;        /* Reserve_2B-0574                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0575       = (U2)0U;        /* Reserve_2B-0575                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0576       = (U2)0U;        /* Reserve_2B-0576                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0577       = (U2)0U;        /* Reserve_2B-0577                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0578       = (U2)0U;        /* Reserve_2B-0578                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0579       = (U2)0U;        /* Reserve_2B-0579                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0580       = (U2)0U;        /* Reserve_2B-0580                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0581       = (U2)0U;        /* Reserve_2B-0581                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0582       = (U2)0U;        /* Reserve_2B-0582                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0583       = (U2)0U;        /* Reserve_2B-0583                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0584       = (U2)0U;        /* Reserve_2B-0584                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0585       = (U2)0U;        /* Reserve_2B-0585                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0586       = (U2)0U;        /* Reserve_2B-0586                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0587       = (U2)0U;        /* Reserve_2B-0587                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0588       = (U2)0U;        /* Reserve_2B-0588                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0589       = (U2)0U;        /* Reserve_2B-0589                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0590       = (U2)0U;        /* Reserve_2B-0590                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0591       = (U2)0U;        /* Reserve_2B-0591                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0592       = (U2)0U;        /* Reserve_2B-0592                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0593       = (U2)0U;        /* Reserve_2B-0593                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0594       = (U2)0U;        /* Reserve_2B-0594                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0595       = (U2)0U;        /* Reserve_2B-0595                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0596       = (U2)0U;        /* Reserve_2B-0596                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0597       = (U2)0U;        /* Reserve_2B-0597                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0598       = (U2)0U;        /* Reserve_2B-0598                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0599       = (U2)0U;        /* Reserve_2B-0599                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0600       = (U2)0U;        /* Reserve_2B-0600                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0601       = (U2)0U;        /* Reserve_2B-0601                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0602       = (U2)0U;        /* Reserve_2B-0602                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0603       = (U2)0U;        /* Reserve_2B-0603                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0604       = (U2)0U;        /* Reserve_2B-0604                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0605       = (U2)0U;        /* Reserve_2B-0605                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0606       = (U2)0U;        /* Reserve_2B-0606                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0607       = (U2)0U;        /* Reserve_2B-0607                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0608       = (U2)0U;        /* Reserve_2B-0608                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0609       = (U2)0U;        /* Reserve_2B-0609                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0610       = (U2)0U;        /* Reserve_2B-0610                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0611       = (U2)0U;        /* Reserve_2B-0611                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0612       = (U2)0U;        /* Reserve_2B-0612                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0613       = (U2)0U;        /* Reserve_2B-0613                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0614       = (U2)0U;        /* Reserve_2B-0614                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0615       = (U2)0U;        /* Reserve_2B-0615                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0616       = (U2)0U;        /* Reserve_2B-0616                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0617       = (U2)0U;        /* Reserve_2B-0617                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0618       = (U2)0U;        /* Reserve_2B-0618                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0619       = (U2)0U;        /* Reserve_2B-0619                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0620       = (U2)0U;        /* Reserve_2B-0620                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0621       = (U2)0U;        /* Reserve_2B-0621                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0622       = (U2)0U;        /* Reserve_2B-0622                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0623       = (U2)0U;        /* Reserve_2B-0623                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0624       = (U2)0U;        /* Reserve_2B-0624                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0625       = (U2)0U;        /* Reserve_2B-0625                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0626       = (U2)0U;        /* Reserve_2B-0626                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0627       = (U2)0U;        /* Reserve_2B-0627                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0628       = (U2)0U;        /* Reserve_2B-0628                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0629       = (U2)0U;        /* Reserve_2B-0629                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0630       = (U2)0U;        /* Reserve_2B-0630                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0631       = (U2)0U;        /* Reserve_2B-0631                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0632       = (U2)0U;        /* Reserve_2B-0632                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0633       = (U2)0U;        /* Reserve_2B-0633                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0634       = (U2)0U;        /* Reserve_2B-0634                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0635       = (U2)0U;        /* Reserve_2B-0635                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0636       = (U2)0U;        /* Reserve_2B-0636                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0637       = (U2)0U;        /* Reserve_2B-0637                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0638       = (U2)0U;        /* Reserve_2B-0638                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0639       = (U2)0U;        /* Reserve_2B-0639                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0640       = (U2)0U;        /* Reserve_2B-0640                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0641       = (U2)0U;        /* Reserve_2B-0641                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0642       = (U2)0U;        /* Reserve_2B-0642                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0643       = (U2)0U;        /* Reserve_2B-0643                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0644       = (U2)0U;        /* Reserve_2B-0644                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0645       = (U2)0U;        /* Reserve_2B-0645                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0646       = (U2)0U;        /* Reserve_2B-0646                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0647       = (U2)0U;        /* Reserve_2B-0647                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0648       = (U2)0U;        /* Reserve_2B-0648                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0649       = (U2)0U;        /* Reserve_2B-0649                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0650       = (U2)0U;        /* Reserve_2B-0650                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0651       = (U2)0U;        /* Reserve_2B-0651                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0652       = (U2)0U;        /* Reserve_2B-0652                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0653       = (U2)0U;        /* Reserve_2B-0653                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0654       = (U2)0U;        /* Reserve_2B-0654                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0655       = (U2)0U;        /* Reserve_2B-0655                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0656       = (U2)0U;        /* Reserve_2B-0656                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0657       = (U2)0U;        /* Reserve_2B-0657                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0658       = (U2)0U;        /* Reserve_2B-0658                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0659       = (U2)0U;        /* Reserve_2B-0659                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0660       = (U2)0U;        /* Reserve_2B-0660                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0661       = (U2)0U;        /* Reserve_2B-0661                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0662       = (U2)0U;        /* Reserve_2B-0662                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0663       = (U2)0U;        /* Reserve_2B-0663                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0664       = (U2)0U;        /* Reserve_2B-0664                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0665       = (U2)0U;        /* Reserve_2B-0665                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0666       = (U2)0U;        /* Reserve_2B-0666                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0667       = (U2)0U;        /* Reserve_2B-0667                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0668       = (U2)0U;        /* Reserve_2B-0668                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0669       = (U2)0U;        /* Reserve_2B-0669                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0670       = (U2)0U;        /* Reserve_2B-0670                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0671       = (U2)0U;        /* Reserve_2B-0671                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0672       = (U2)0U;        /* Reserve_2B-0672                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0673       = (U2)0U;        /* Reserve_2B-0673                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0674       = (U2)0U;        /* Reserve_2B-0674                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0675       = (U2)0U;        /* Reserve_2B-0675                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0676       = (U2)0U;        /* Reserve_2B-0676                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0677       = (U2)0U;        /* Reserve_2B-0677                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0678       = (U2)0U;        /* Reserve_2B-0678                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0679       = (U2)0U;        /* Reserve_2B-0679                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0680       = (U2)0U;        /* Reserve_2B-0680                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0681       = (U2)0U;        /* Reserve_2B-0681                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0682       = (U2)0U;        /* Reserve_2B-0682                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0683       = (U2)0U;        /* Reserve_2B-0683                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0684       = (U2)0U;        /* Reserve_2B-0684                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0685       = (U2)0U;        /* Reserve_2B-0685                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0686       = (U2)0U;        /* Reserve_2B-0686                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0687       = (U2)0U;        /* Reserve_2B-0687                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0688       = (U2)0U;        /* Reserve_2B-0688                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0689       = (U2)0U;        /* Reserve_2B-0689                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0690       = (U2)0U;        /* Reserve_2B-0690                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0691       = (U2)0U;        /* Reserve_2B-0691                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0692       = (U2)0U;        /* Reserve_2B-0692                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0693       = (U2)0U;        /* Reserve_2B-0693                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0694       = (U2)0U;        /* Reserve_2B-0694                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0695       = (U2)0U;        /* Reserve_2B-0695                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0696       = (U2)0U;        /* Reserve_2B-0696                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0697       = (U2)0U;        /* Reserve_2B-0697                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0698       = (U2)0U;        /* Reserve_2B-0698                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0699       = (U2)0U;        /* Reserve_2B-0699                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0700       = (U2)0U;        /* Reserve_2B-0700                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0701       = (U2)0U;        /* Reserve_2B-0701                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0702       = (U2)0U;        /* Reserve_2B-0702                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0703       = (U2)0U;        /* Reserve_2B-0703                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0704       = (U2)0U;        /* Reserve_2B-0704                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0705       = (U2)0U;        /* Reserve_2B-0705                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0706       = (U2)0U;        /* Reserve_2B-0706                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0707       = (U2)0U;        /* Reserve_2B-0707                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0708       = (U2)0U;        /* Reserve_2B-0708                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0709       = (U2)0U;        /* Reserve_2B-0709                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0710       = (U2)0U;        /* Reserve_2B-0710                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0711       = (U2)0U;        /* Reserve_2B-0711                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0712       = (U2)0U;        /* Reserve_2B-0712                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0713       = (U2)0U;        /* Reserve_2B-0713                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0714       = (U2)0U;        /* Reserve_2B-0714                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0715       = (U2)0U;        /* Reserve_2B-0715                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0716       = (U2)0U;        /* Reserve_2B-0716                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0717       = (U2)0U;        /* Reserve_2B-0717                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0718       = (U2)0U;        /* Reserve_2B-0718                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0719       = (U2)0U;        /* Reserve_2B-0719                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0720       = (U2)0U;        /* Reserve_2B-0720                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0721       = (U2)0U;        /* Reserve_2B-0721                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0722       = (U2)0U;        /* Reserve_2B-0722                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0723       = (U2)0U;        /* Reserve_2B-0723                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0724       = (U2)0U;        /* Reserve_2B-0724                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0725       = (U2)0U;        /* Reserve_2B-0725                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0726       = (U2)0U;        /* Reserve_2B-0726                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0727       = (U2)0U;        /* Reserve_2B-0727                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0728       = (U2)0U;        /* Reserve_2B-0728                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0729       = (U2)0U;        /* Reserve_2B-0729                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0730       = (U2)0U;        /* Reserve_2B-0730                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0731       = (U2)0U;        /* Reserve_2B-0731                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0732       = (U2)0U;        /* Reserve_2B-0732                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0733       = (U2)0U;        /* Reserve_2B-0733                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0734       = (U2)0U;        /* Reserve_2B-0734                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0735       = (U2)0U;        /* Reserve_2B-0735                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0736       = (U2)0U;        /* Reserve_2B-0736                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0737       = (U2)0U;        /* Reserve_2B-0737                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0738       = (U2)0U;        /* Reserve_2B-0738                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0739       = (U2)0U;        /* Reserve_2B-0739                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0740       = (U2)0U;        /* Reserve_2B-0740                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0741       = (U2)0U;        /* Reserve_2B-0741                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0742       = (U2)0U;        /* Reserve_2B-0742                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0743       = (U2)0U;        /* Reserve_2B-0743                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0744       = (U2)0U;        /* Reserve_2B-0744                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0745       = (U2)0U;        /* Reserve_2B-0745                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0746       = (U2)0U;        /* Reserve_2B-0746                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0747       = (U2)0U;        /* Reserve_2B-0747                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0748       = (U2)0U;        /* Reserve_2B-0748                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0749       = (U2)0U;        /* Reserve_2B-0749                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0750       = (U2)0U;        /* Reserve_2B-0750                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0751       = (U2)0U;        /* Reserve_2B-0751                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0752       = (U2)0U;        /* Reserve_2B-0752                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0753       = (U2)0U;        /* Reserve_2B-0753                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0754       = (U2)0U;        /* Reserve_2B-0754                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0755       = (U2)0U;        /* Reserve_2B-0755                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0756       = (U2)0U;        /* Reserve_2B-0756                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0757       = (U2)0U;        /* Reserve_2B-0757                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0758       = (U2)0U;        /* Reserve_2B-0758                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0759       = (U2)0U;        /* Reserve_2B-0759                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0760       = (U2)0U;        /* Reserve_2B-0760                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0761       = (U2)0U;        /* Reserve_2B-0761                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0762       = (U2)0U;        /* Reserve_2B-0762                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0763       = (U2)0U;        /* Reserve_2B-0763                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0764       = (U2)0U;        /* Reserve_2B-0764                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0765       = (U2)0U;        /* Reserve_2B-0765                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0766       = (U2)0U;        /* Reserve_2B-0766                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0767       = (U2)0U;        /* Reserve_2B-0767                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0768       = (U2)0U;        /* Reserve_2B-0768                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0769       = (U2)0U;        /* Reserve_2B-0769                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0770       = (U2)0U;        /* Reserve_2B-0770                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0771       = (U2)0U;        /* Reserve_2B-0771                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0772       = (U2)0U;        /* Reserve_2B-0772                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0773       = (U2)0U;        /* Reserve_2B-0773                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0774       = (U2)0U;        /* Reserve_2B-0774                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0775       = (U2)0U;        /* Reserve_2B-0775                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0776       = (U2)0U;        /* Reserve_2B-0776                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0777       = (U2)0U;        /* Reserve_2B-0777                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0778       = (U2)0U;        /* Reserve_2B-0778                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0779       = (U2)0U;        /* Reserve_2B-0779                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0780       = (U2)0U;        /* Reserve_2B-0780                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0781       = (U2)0U;        /* Reserve_2B-0781                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0782       = (U2)0U;        /* Reserve_2B-0782                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0783       = (U2)0U;        /* Reserve_2B-0783                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0784       = (U2)0U;        /* Reserve_2B-0784                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0785       = (U2)0U;        /* Reserve_2B-0785                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0786       = (U2)0U;        /* Reserve_2B-0786                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0787       = (U2)0U;        /* Reserve_2B-0787                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0788       = (U2)0U;        /* Reserve_2B-0788                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0789       = (U2)0U;        /* Reserve_2B-0789                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0790       = (U2)0U;        /* Reserve_2B-0790                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0791       = (U2)0U;        /* Reserve_2B-0791                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0792       = (U2)0U;        /* Reserve_2B-0792                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0793       = (U2)0U;        /* Reserve_2B-0793                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0794       = (U2)0U;        /* Reserve_2B-0794                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0795       = (U2)0U;        /* Reserve_2B-0795                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0796       = (U2)0U;        /* Reserve_2B-0796                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0797       = (U2)0U;        /* Reserve_2B-0797                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0798       = (U2)0U;        /* Reserve_2B-0798                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0799       = (U2)0U;        /* Reserve_2B-0799                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0800       = (U2)0U;        /* Reserve_2B-0800                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0801       = (U2)0U;        /* Reserve_2B-0801                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0802       = (U2)0U;        /* Reserve_2B-0802                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0803       = (U2)0U;        /* Reserve_2B-0803                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0804       = (U2)0U;        /* Reserve_2B-0804                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0805       = (U2)0U;        /* Reserve_2B-0805                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0806       = (U2)0U;        /* Reserve_2B-0806                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0807       = (U2)0U;        /* Reserve_2B-0807                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0808       = (U2)0U;        /* Reserve_2B-0808                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0809       = (U2)0U;        /* Reserve_2B-0809                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0810       = (U2)0U;        /* Reserve_2B-0810                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0811       = (U2)0U;        /* Reserve_2B-0811                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0812       = (U2)0U;        /* Reserve_2B-0812                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0813       = (U2)0U;        /* Reserve_2B-0813                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0814       = (U2)0U;        /* Reserve_2B-0814                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0815       = (U2)0U;        /* Reserve_2B-0815                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0816       = (U2)0U;        /* Reserve_2B-0816                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0817       = (U2)0U;        /* Reserve_2B-0817                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0818       = (U2)0U;        /* Reserve_2B-0818                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0819       = (U2)0U;        /* Reserve_2B-0819                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0820       = (U2)0U;        /* Reserve_2B-0820                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0821       = (U2)0U;        /* Reserve_2B-0821                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0822       = (U2)0U;        /* Reserve_2B-0822                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0823       = (U2)0U;        /* Reserve_2B-0823                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0824       = (U2)0U;        /* Reserve_2B-0824                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0825       = (U2)0U;        /* Reserve_2B-0825                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0826       = (U2)0U;        /* Reserve_2B-0826                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0827       = (U2)0U;        /* Reserve_2B-0827                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0828       = (U2)0U;        /* Reserve_2B-0828                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0829       = (U2)0U;        /* Reserve_2B-0829                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0830       = (U2)0U;        /* Reserve_2B-0830                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0831       = (U2)0U;        /* Reserve_2B-0831                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0832       = (U2)0U;        /* Reserve_2B-0832                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0833       = (U2)0U;        /* Reserve_2B-0833                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0834       = (U2)0U;        /* Reserve_2B-0834                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0835       = (U2)0U;        /* Reserve_2B-0835                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0836       = (U2)0U;        /* Reserve_2B-0836                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0837       = (U2)0U;        /* Reserve_2B-0837                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0838       = (U2)0U;        /* Reserve_2B-0838                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0839       = (U2)0U;        /* Reserve_2B-0839                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0840       = (U2)0U;        /* Reserve_2B-0840                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0841       = (U2)0U;        /* Reserve_2B-0841                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0842       = (U2)0U;        /* Reserve_2B-0842                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0843       = (U2)0U;        /* Reserve_2B-0843                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0844       = (U2)0U;        /* Reserve_2B-0844                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0845       = (U2)0U;        /* Reserve_2B-0845                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0846       = (U2)0U;        /* Reserve_2B-0846                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0847       = (U2)0U;        /* Reserve_2B-0847                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0848       = (U2)0U;        /* Reserve_2B-0848                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0849       = (U2)0U;        /* Reserve_2B-0849                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0850       = (U2)0U;        /* Reserve_2B-0850                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0851       = (U2)0U;        /* Reserve_2B-0851                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0852       = (U2)0U;        /* Reserve_2B-0852                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0853       = (U2)0U;        /* Reserve_2B-0853                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0854       = (U2)0U;        /* Reserve_2B-0854                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0855       = (U2)0U;        /* Reserve_2B-0855                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0856       = (U2)0U;        /* Reserve_2B-0856                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0857       = (U2)0U;        /* Reserve_2B-0857                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0858       = (U2)0U;        /* Reserve_2B-0858                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0859       = (U2)0U;        /* Reserve_2B-0859                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0860       = (U2)0U;        /* Reserve_2B-0860                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0861       = (U2)0U;        /* Reserve_2B-0861                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0862       = (U2)0U;        /* Reserve_2B-0862                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0863       = (U2)0U;        /* Reserve_2B-0863                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0864       = (U2)0U;        /* Reserve_2B-0864                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0865       = (U2)0U;        /* Reserve_2B-0865                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0866       = (U2)0U;        /* Reserve_2B-0866                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0867       = (U2)0U;        /* Reserve_2B-0867                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0868       = (U2)0U;        /* Reserve_2B-0868                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0869       = (U2)0U;        /* Reserve_2B-0869                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0870       = (U2)0U;        /* Reserve_2B-0870                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0871       = (U2)0U;        /* Reserve_2B-0871                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0872       = (U2)0U;        /* Reserve_2B-0872                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0873       = (U2)0U;        /* Reserve_2B-0873                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0874       = (U2)0U;        /* Reserve_2B-0874                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0875       = (U2)0U;        /* Reserve_2B-0875                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0876       = (U2)0U;        /* Reserve_2B-0876                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0877       = (U2)0U;        /* Reserve_2B-0877                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0878       = (U2)0U;        /* Reserve_2B-0878                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0879       = (U2)0U;        /* Reserve_2B-0879                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0880       = (U2)0U;        /* Reserve_2B-0880                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0881       = (U2)0U;        /* Reserve_2B-0881                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0882       = (U2)0U;        /* Reserve_2B-0882                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0883       = (U2)0U;        /* Reserve_2B-0883                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0884       = (U2)0U;        /* Reserve_2B-0884                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0885       = (U2)0U;        /* Reserve_2B-0885                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0886       = (U2)0U;        /* Reserve_2B-0886                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0887       = (U2)0U;        /* Reserve_2B-0887                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0888       = (U2)0U;        /* Reserve_2B-0888                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0889       = (U2)0U;        /* Reserve_2B-0889                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0890       = (U2)0U;        /* Reserve_2B-0890                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0891       = (U2)0U;        /* Reserve_2B-0891                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0892       = (U2)0U;        /* Reserve_2B-0892                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0893       = (U2)0U;        /* Reserve_2B-0893                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0894       = (U2)0U;        /* Reserve_2B-0894                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0895       = (U2)0U;        /* Reserve_2B-0895                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0896       = (U2)0U;        /* Reserve_2B-0896                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0897       = (U2)0U;        /* Reserve_2B-0897                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0898       = (U2)0U;        /* Reserve_2B-0898                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0899       = (U2)0U;        /* Reserve_2B-0899                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0900       = (U2)0U;        /* Reserve_2B-0900                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0901       = (U2)0U;        /* Reserve_2B-0901                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0902       = (U2)0U;        /* Reserve_2B-0902                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0903       = (U2)0U;        /* Reserve_2B-0903                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0904       = (U2)0U;        /* Reserve_2B-0904                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0905       = (U2)0U;        /* Reserve_2B-0905                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0906       = (U2)0U;        /* Reserve_2B-0906                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0907       = (U2)0U;        /* Reserve_2B-0907                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0908       = (U2)0U;        /* Reserve_2B-0908                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0909       = (U2)0U;        /* Reserve_2B-0909                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0910       = (U2)0U;        /* Reserve_2B-0910                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0911       = (U2)0U;        /* Reserve_2B-0911                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0912       = (U2)0U;        /* Reserve_2B-0912                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0913       = (U2)0U;        /* Reserve_2B-0913                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0914       = (U2)0U;        /* Reserve_2B-0914                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0915       = (U2)0U;        /* Reserve_2B-0915                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0916       = (U2)0U;        /* Reserve_2B-0916                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0917       = (U2)0U;        /* Reserve_2B-0917                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0918       = (U2)0U;        /* Reserve_2B-0918                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0919       = (U2)0U;        /* Reserve_2B-0919                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0920       = (U2)0U;        /* Reserve_2B-0920                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0921       = (U2)0U;        /* Reserve_2B-0921                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0922       = (U2)0U;        /* Reserve_2B-0922                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0923       = (U2)0U;        /* Reserve_2B-0923                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0924       = (U2)0U;        /* Reserve_2B-0924                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0925       = (U2)0U;        /* Reserve_2B-0925                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0926       = (U2)0U;        /* Reserve_2B-0926                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0927       = (U2)0U;        /* Reserve_2B-0927                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0928       = (U2)0U;        /* Reserve_2B-0928                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0929       = (U2)0U;        /* Reserve_2B-0929                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0930       = (U2)0U;        /* Reserve_2B-0930                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0931       = (U2)0U;        /* Reserve_2B-0931                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0932       = (U2)0U;        /* Reserve_2B-0932                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0933       = (U2)0U;        /* Reserve_2B-0933                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0934       = (U2)0U;        /* Reserve_2B-0934                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0935       = (U2)0U;        /* Reserve_2B-0935                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0936       = (U2)0U;        /* Reserve_2B-0936                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0937       = (U2)0U;        /* Reserve_2B-0937                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0938       = (U2)0U;        /* Reserve_2B-0938                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0939       = (U2)0U;        /* Reserve_2B-0939                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0940       = (U2)0U;        /* Reserve_2B-0940                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0941       = (U2)0U;        /* Reserve_2B-0941                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0942       = (U2)0U;        /* Reserve_2B-0942                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0943       = (U2)0U;        /* Reserve_2B-0943                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0944       = (U2)0U;        /* Reserve_2B-0944                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0945       = (U2)0U;        /* Reserve_2B-0945                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0946       = (U2)0U;        /* Reserve_2B-0946                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0947       = (U2)0U;        /* Reserve_2B-0947                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0948       = (U2)0U;        /* Reserve_2B-0948                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0949       = (U2)0U;        /* Reserve_2B-0949                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0950       = (U2)0U;        /* Reserve_2B-0950                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0951       = (U2)0U;        /* Reserve_2B-0951                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0952       = (U2)0U;        /* Reserve_2B-0952                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0953       = (U2)0U;        /* Reserve_2B-0953                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0954       = (U2)0U;        /* Reserve_2B-0954                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0955       = (U2)0U;        /* Reserve_2B-0955                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0956       = (U2)0U;        /* Reserve_2B-0956                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0957       = (U2)0U;        /* Reserve_2B-0957                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0958       = (U2)0U;        /* Reserve_2B-0958                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0959       = (U2)0U;        /* Reserve_2B-0959                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0960       = (U2)0U;        /* Reserve_2B-0960                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0961       = (U2)0U;        /* Reserve_2B-0961                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0962       = (U2)0U;        /* Reserve_2B-0962                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0963       = (U2)0U;        /* Reserve_2B-0963                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0964       = (U2)0U;        /* Reserve_2B-0964                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0965       = (U2)0U;        /* Reserve_2B-0965                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0966       = (U2)0U;        /* Reserve_2B-0966                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0967       = (U2)0U;        /* Reserve_2B-0967                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0968       = (U2)0U;        /* Reserve_2B-0968                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0969       = (U2)0U;        /* Reserve_2B-0969                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0970       = (U2)0U;        /* Reserve_2B-0970                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0971       = (U2)0U;        /* Reserve_2B-0971                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0972       = (U2)0U;        /* Reserve_2B-0972                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0973       = (U2)0U;        /* Reserve_2B-0973                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0974       = (U2)0U;        /* Reserve_2B-0974                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0975       = (U2)0U;        /* Reserve_2B-0975                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0976       = (U2)0U;        /* Reserve_2B-0976                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0977       = (U2)0U;        /* Reserve_2B-0977                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0978       = (U2)0U;        /* Reserve_2B-0978                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0979       = (U2)0U;        /* Reserve_2B-0979                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0980       = (U2)0U;        /* Reserve_2B-0980                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0981       = (U2)0U;        /* Reserve_2B-0981                                               */
volatile const U2 u2_CALIB_MCUID_RSV_2B_0982       = (U2)0U;        /* Reserve_2B-0982                                               */

#pragma ghs section rodata  = ".calibration_area_u4"
volatile const U4 u4_CALIB_MCUID_RSV_4B_0004       = (U4)0U;        /* Reserve_4B-0004                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0005       = (U4)0U;        /* Reserve_4B-0005                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0006       = (U4)0U;        /* Reserve_4B-0006                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0007       = (U4)0U;        /* Reserve_4B-0007                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0008       = (U4)0U;        /* Reserve_4B-0008                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0009       = (U4)0U;        /* Reserve_4B-0009                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0010       = (U4)0U;        /* Reserve_4B-0010                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0011       = (U4)0U;        /* Reserve_4B-0011                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0012       = (U4)0U;        /* Reserve_4B-0012                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0013       = (U4)0U;        /* Reserve_4B-0013                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0014       = (U4)0U;        /* Reserve_4B-0014                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0015       = (U4)0U;        /* Reserve_4B-0015                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0016       = (U4)0U;        /* Reserve_4B-0016                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0017       = (U4)0U;        /* Reserve_4B-0017                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0018       = (U4)0U;        /* Reserve_4B-0018                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0019       = (U4)0U;        /* Reserve_4B-0019                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0020       = (U4)0U;        /* Reserve_4B-0020                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0021       = (U4)0U;        /* Reserve_4B-0021                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0022       = (U4)0U;        /* Reserve_4B-0022                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0023       = (U4)0U;        /* Reserve_4B-0023                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0024       = (U4)0U;        /* Reserve_4B-0024                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0025       = (U4)0U;        /* Reserve_4B-0025                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0026       = (U4)0U;        /* Reserve_4B-0026                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0027       = (U4)0U;        /* Reserve_4B-0027                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0028       = (U4)0U;        /* Reserve_4B-0028                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0029       = (U4)0U;        /* Reserve_4B-0029                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0030       = (U4)0U;        /* Reserve_4B-0030                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0031       = (U4)0U;        /* Reserve_4B-0031                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0032       = (U4)0U;        /* Reserve_4B-0032                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0033       = (U4)0U;        /* Reserve_4B-0033                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0034       = (U4)0U;        /* Reserve_4B-0034                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0035       = (U4)0U;        /* Reserve_4B-0035                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0036       = (U4)0U;        /* Reserve_4B-0036                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0037       = (U4)0U;        /* Reserve_4B-0037                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0038       = (U4)0U;        /* Reserve_4B-0038                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0039       = (U4)0U;        /* Reserve_4B-0039                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0040       = (U4)0U;        /* Reserve_4B-0040                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0041       = (U4)0U;        /* Reserve_4B-0041                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0042       = (U4)0U;        /* Reserve_4B-0042                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0043       = (U4)0U;        /* Reserve_4B-0043                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0044       = (U4)0U;        /* Reserve_4B-0044                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0045       = (U4)0U;        /* Reserve_4B-0045                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0046       = (U4)0U;        /* Reserve_4B-0046                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0047       = (U4)0U;        /* Reserve_4B-0047                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0048       = (U4)0U;        /* Reserve_4B-0048                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0049       = (U4)0U;        /* Reserve_4B-0049                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0050       = (U4)0U;        /* Reserve_4B-0050                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0051       = (U4)0U;        /* Reserve_4B-0051                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0052       = (U4)0U;        /* Reserve_4B-0052                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0053       = (U4)0U;        /* Reserve_4B-0053                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0054       = (U4)0U;        /* Reserve_4B-0054                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0055       = (U4)0U;        /* Reserve_4B-0055                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0056       = (U4)0U;        /* Reserve_4B-0056                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0057       = (U4)0U;        /* Reserve_4B-0057                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0058       = (U4)0U;        /* Reserve_4B-0058                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0059       = (U4)0U;        /* Reserve_4B-0059                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0060       = (U4)0U;        /* Reserve_4B-0060                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0061       = (U4)0U;        /* Reserve_4B-0061                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0062       = (U4)0U;        /* Reserve_4B-0062                                               */
volatile const U4 u4_CALIB_MCUID_RSV_4B_0063       = (U4)0U;        /* Reserve_4B-0063                                               */

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
/*  1.1.0    09/05/2024  TN       Update for MET-M_MCUCONST-CSTD-A0-017-XXXD-XX.                                                     */
/*  1.2.0    10/23/2024  TN       Update for MET-M_MCUCONST-CSTD-A0-019-XXXD-XX.                                                     */
/*  1.3.0    04/07/2025  SH       Update for MET-M_MCUCONST-CSTD-A0-023-A-XX-XXXX-X.                                                 */
/*                                                                                                                                   */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * TN   = Testsushi Nakano, Denso Techno                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
