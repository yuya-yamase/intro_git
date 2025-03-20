/* 1.6.0 */
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
#define SOUND_CRI_OWIDX_H_MINOR                  (6)
#define SOUND_CRI_OWIDX_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_CH_00                              (0U)        /* Sounding CH for the Active Test                                      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SOUND_OW_WAV_IDX_NUM                     (63U)        /* Number of Active Test ID for buzzer/speaker action                  */

#define SOUND_AT_0P8_LRG_0P8_IN_1P2              (0U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 1.2s Intermissive  */
#define SOUND_AT_0P8_LRG_0P8_IN_0P7              (1U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 0.7s Intermissive  */
#define SOUND_AT_0P8_LRG_0P8_IN_0P5              (2U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 0.5s Intermissive  */
#define SOUND_AT_0P8_LRG_0P8_IN_0P4              (3U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 0.4s Intermissive  */
#define SOUND_AT_0P8_LRG_0P8_SI                  (4U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 0.9s Single shot   */
#define SOUND_AT_0P8_LRG_0P8_TW                  (5U)         /* Frequency:0.8kHz, Volume:High, Decrement:T=0.8s, 0.2s Double shot   */
#define SOUND_AT_MET_CBZ_BASE_CONTWARN1          (6U)         /* Frequency:1.6kHz, Volume:High, Decrement:None,   Continuation       */
#define SOUND_AT_0P8_LRG_NONE_IN_1P2             (7U)         /* Frequency:0.8kHz, Volume:High, Decrement:None,   1.2s Intermissive  */
#define SOUND_AT_0P8_LRG_NONE_IN_0P7             (8U)         /* Frequency:0.8kHz, Volume:High, Decrement:None,   0.7s Intermissive  */
#define SOUND_AT_0P8_LRG_NONE_IN_0P5             (9U)         /* Frequency:0.8kHz, Volume:High, Decrement:None,   0.5s Intermissive  */
#define SOUND_AT_0P8_LRG_NONE_IN_0P4             (10U)        /* Frequency:0.8kHz, Volume:High, Decrement:None,   0.4s Intermissive  */
#define SOUND_AT_MET_CBZ_BASE_NOTICE1_1          (11U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.9s Single shot   */
#define SOUND_AT_0P8_LRG_NONE_TW                 (12U)        /* Frequency:0.8kHz, Volume:High, Decrement:None,   0.2s Double shot   */
#define SOUND_AT_MET_CBZ_BASE_CONTWARN2          (13U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   Continuation       */
#define SOUND_AT_0P8_SML_0P8_IN_1P2              (14U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 1.2s Intermissive  */
#define SOUND_AT_0P8_SML_0P8_IN_0P7              (15U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 0.7s Intermissive  */
#define SOUND_AT_0P8_SML_0P8_IN_0P5              (16U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 0.5s Intermissive  */
#define SOUND_AT_0P8_SML_0P8_IN_0P4              (17U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 0.4s Intermissive  */
#define SOUND_AT_0P8_SML_0P8_SI                  (18U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 0.9s Single shot   */
#define SOUND_AT_0P8_SML_0P8_TW                  (19U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:T=0.8s, 0.2s Double shot   */
#define SOUND_AT_MET_CBZ_BASE_CONTWARN3          (20U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   Continuation       */
#define SOUND_AT_0P8_SML_NONE_IN_1P2             (21U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:None,   1.2s Intermissive  */
#define SOUND_AT_0P8_SML_NONE_IN_0P7             (22U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:None,   0.7s Intermissive  */
#define SOUND_AT_0P8_SML_NONE_IN_0P5             (23U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:None,   0.5s Intermissive  */
#define SOUND_AT_0P8_SML_NONE_IN_0P4             (24U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:None,   0.4s Intermissive  */
#define SOUND_AT_MET_CBZ_BASE_NOTICE1_2          (25U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.9s Single shot   */
#define SOUND_AT_0P8_SML_NONE_TW                 (26U)        /* Frequency:0.8kHz, Volume:Low,  Decrement:None,   0.2s Double shot   */
#define SOUND_AT_MET_CBZ_BASE_CONTWARN4          (27U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   Continuation       */
#define SOUND_AT_1P6_SML_NONE_IN_1P2             (28U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   1.2s Intermissive  */
#define SOUND_AT_1P6_SML_NONE_IN_0P7             (29U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   0.7s Intermissive  */
#define SOUND_AT_1P6_SML_NONE_IN_0P5             (30U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   0.5s Intermissive  */
#define SOUND_AT_1P6_SML_NONE_IN_0P4             (31U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   0.4s Intermissive  */
#define SOUND_AT_1P6_SML_NONE_SI                 (32U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   0.9s Single shot   */
#define SOUND_AT_1P6_SML_NONE_TW                 (33U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   0.2s Double shot   */
#define SOUND_AT_1P6_SML_NONE_CO                 (34U)        /* Frequency:1.6kHz, Volume:Low,  Decrement:None,   Continuation       */
#define SOUND_AT_2P4_LRG_NONE_IN_1P2             (35U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   1.2s Intermissive  */
#define SOUND_AT_2P4_LRG_NONE_IN_0P7             (36U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.7s Intermissive  */
#define SOUND_AT_2P4_LRG_NONE_IN_0P5             (37U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.5s Intermissive  */
#define SOUND_AT_2P4_LRG_NONE_IN_0P4             (38U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.4s Intermissive  */
#define SOUND_AT_2P4_LRG_NONE_SI                 (39U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.9s Single shot   */
#define SOUND_AT_2P4_LRG_NONE_TW                 (40U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   0.2s Double shot   */
#define SOUND_AT_2P4_LRG_NONE_CO                 (41U)        /* Frequency:1.6kHz, Volume:High, Decrement:None,   Continuation       */
#define SOUND_AT_CLESON_FRS1                     (42U)        /* Clearance sonar Fr detection (Closest approach/Short distance)      */
#define SOUND_AT_CLESON_FRM                      (43U)        /* Clearance sonar Fr detection (Medium distance)                      */
#define SOUND_AT_CLESON_FRL                      (44U)        /* Clearance sonar Fr detection (Long distance)                        */
#define SOUND_AT_CLESON_FRF                      (45U)        /* Clearance sonar Fr detection (Farthest distance)                    */
#define SOUND_AT_CLESON_RRS                      (46U)        /* Clearance sonar Rr detection (Closest approach/Short distance)      */
#define SOUND_AT_CLESON_RRM                      (47U)        /* Clearance sonar Rr detection (Medium distance)                      */
#define SOUND_AT_CLESON_RRL                      (48U)        /* Clearance sonar Rr detection (Long distance)                        */
#define SOUND_AT_CLESON_RRF                      (49U)        /* Clearance sonar Rr detection (Farthest distance)                    */
#define SOUND_AT_CLESON_FRS2                     (50U)        /* Clearance sonar Fr & Rr detection (Closest approach/Short distance) */
#define SOUND_AT_CLESON_FRRRM                    (51U)        /* Clearance sonar Fr & Rr detection (Medium distance)                 */
#define SOUND_AT_CLESON_FRRRL                    (52U)        /* Clearance sonar Fr & Rr detection (Long distance)                   */
#define SOUND_AT_CLESON_FRRRF                    (53U)        /* Clearance sonar Fr & Rr detection (Farthest distance)               */
#define SOUND_AT_AT_REVERSE_IN                   (54U)        /* A/T reverse buzzer                                                  */
#define SOUND_AT_SBW_REVERSE_IN                  (55U)        /* SBW reverse buzzer                                                  */
#define SOUND_AT_SEAREM_FMV                      (56U)        /* Seatbelt reminder buzzer (Regulation intermittence)                 */
#define SOUND_AT_SEAREM_LV2                      (57U)        /* Seatbelt reminder buzzer (Level 2)                                  */
#define SOUND_AT_SEAREM_LV1                      (58U)        /* Seatbelt reminder buzzer (Level 1)                                  */
#define SOUND_AT_SEAREM_SI                       (59U)        /* Unbuckle notification buzzer                                        */
#define SOUND_AT_MET_CBZ_BASE_NOTICE1_3          (60U)        /* Master caution buzzer                                               */
#define SOUND_AT_MMTURHAZ_STA                    (61U)        /* Flasher operating sound (Start of lighting)                         */
#define SOUND_AT_MMTURHAZ_FIN                    (62U)        /* Flasher operating sound (End of lighting)                           */

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
