/* 1.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* Sound Middleware (CRI) Control                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SOUND_CRI_OWIDX_H
#define SOUND_CRI_OWIDX_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CRI_OWIDX_H_MAJOR                  (1)
#define SOUND_CRI_OWIDX_H_MINOR                  (7)
#define SOUND_CRI_OWIDX_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CH_00                              (0U)        /* Sounding CH for the Active Test                                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_OW_WAV_IDX_NUM                     (20U)        /* Number of Active Test ID for buzzer/speaker action                  */

#define SOUND_AT_CLESON_FRS                      (0U)         /* Clearance sonar Fr detection (Closest approach/Short distance)      */
#define SOUND_AT_CLESON_FRM                      (1U)         /* Clearance sonar Fr detection (Medium distance)                      */
#define SOUND_AT_CLESON_FRL                      (2U)         /* Clearance sonar Fr detection (Long distance)                        */
#define SOUND_AT_CLESON_FRF                      (3U)         /* Clearance sonar Fr detection (Farthest distance)                    */
#define SOUND_AT_CLESON_RRS                      (4U)         /* Clearance sonar Rr detection (Closest approach/Short distance)      */
#define SOUND_AT_CLESON_RRM                      (5U)         /* Clearance sonar Rr detection (Medium distance)                      */
#define SOUND_AT_CLESON_RRL                      (6U)         /* Clearance sonar Rr detection (Long distance)                        */
#define SOUND_AT_CLESON_RRF                      (7U)         /* Clearance sonar Rr detection (Farthest distance)                    */
#define SOUND_AT_CLESON_FRRRS                    (8U)         /* Clearance sonar Fr & Rr detection (Closest approach/Short distance) */
#define SOUND_AT_CLESON_FRRRM                    (9U)         /* Clearance sonar Fr & Rr detection (Medium distance)                 */
#define SOUND_AT_CLESON_FRRRL                    (10U)        /* Clearance sonar Fr & Rr detection (Long distance)                   */
#define SOUND_AT_CLESON_FRRRF                    (11U)        /* Clearance sonar Fr & Rr detection (Farthest distance)               */
#define SOUND_AT_SBW_REVERSE_IN                  (12U)        /* SBW reverse buzzer                                                  */
#define SOUND_AT_SEAREM_FMV                      (13U)        /* Seatbelt reminder buzzer (Regulation intermittence)                 */
#define SOUND_AT_SEAREM_LV2                      (14U)        /* Seatbelt reminder buzzer (Level 2)                                  */
#define SOUND_AT_SEAREM_LV1                      (15U)        /* Seatbelt reminder buzzer (Level 1)                                  */
#define SOUND_AT_SEAREM_SI                       (16U)        /* Unbuckle notification buzzer                                        */
#define SOUND_AT_MET_CBZ_BASE_NOTICE1            (17U)        /* Master caution buzzer                                               */
#define SOUND_AT_MMTURHAZ_STA                    (18U)        /* Flasher operating sound (Start of lighting)                         */
#define SOUND_AT_MMTURHAZ_FIN                    (19U)        /* Flasher operating sound (End of lighting)                           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* SOUND_CRI_OWIDX_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  sound_cri_mgr.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
