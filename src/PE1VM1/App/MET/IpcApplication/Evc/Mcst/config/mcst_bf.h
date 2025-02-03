/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Meter Customize                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef MCST_BF_H
#define MCST_BF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_BF_H_MAJOR                          (2)
#define MCST_BF_H_MINOR                          (4)
#define MCST_BF_H_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "locale.h"
#include "gagdst_revind.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Caution! MCST_NUM_WORD is limited to 31 or less */
/* Used in "esi_nvmr_cfg.c"                        */
#define MCST_NUM_RIM                             ( 1U)    /* Number of MCST IDs stored in RIM */

#define MCST_BF_INI                              (0xFFFFFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Number of Common Areas */
#define MCST_NUM_WORD_COMMON                     (4U)
/* Number of Personal Areas */
#define MCST_NUM_WORD_PERSONAL                   (16U)
/* Number of NVM Common Areas */
#define MCST_NUM_NVM_COMMON                      (1U)
/* Number of NVM Personal Areas */
#define MCST_NUM_NVM_PERSONAL                    (4U)

#define MCST_NUM_WORD                            (MCST_NUM_WORD_COMMON + (MCST_NUM_WORD_PERSONAL*4U))   /* 68U */
#define MCST_NUM_NVM                             (MCST_NUM_NVM_COMMON + (MCST_NUM_NVM_PERSONAL*4U))     /* 17U */

/* Offset is added to this area */
#define MCST_NUM_WORD_USER                       (MCST_NUM_WORD_COMMON + MCST_NUM_WORD_PERSONAL)
/* Start position offset */
#define MCST_BF_OFFSET_GUEST                     (0U)                                                   /*  0U */
#define MCST_BF_OFFSET_USER1                     (MCST_BF_OFFSET_GUEST + MCST_NUM_WORD_PERSONAL)        /* 16U */
#define MCST_BF_OFFSET_USER2                     (MCST_BF_OFFSET_USER1 + MCST_NUM_WORD_PERSONAL)        /* 32U */
#define MCST_BF_OFFSET_USER3                     (MCST_BF_OFFSET_USER2 + MCST_NUM_WORD_PERSONAL)        /* 48U */
/* Area start position */
#define MCST_BF_OFFSET_GUEST_INI                 (MCST_NUM_WORD_COMMON)                                 /*  4U */
#define MCST_BF_OFFSET_USER1_INI                 (MCST_BF_OFFSET_GUEST_INI + MCST_NUM_WORD_PERSONAL)    /* 20U */
#define MCST_BF_OFFSET_USER2_INI                 (MCST_BF_OFFSET_USER1_INI + MCST_NUM_WORD_PERSONAL)    /* 36U */
#define MCST_BF_OFFSET_USER3_INI                 (MCST_BF_OFFSET_USER2_INI + MCST_NUM_WORD_PERSONAL)    /* 52U */
/* Area end position */
#define MCST_BF_OFFSET_GUEST_MAX                 (MCST_BF_OFFSET_GUEST_INI + MCST_NUM_WORD_PERSONAL)    /* 20U */
#define MCST_BF_OFFSET_USER1_MAX                 (MCST_BF_OFFSET_USER1_INI + MCST_NUM_WORD_PERSONAL)    /* 36U */
#define MCST_BF_OFFSET_USER2_MAX                 (MCST_BF_OFFSET_USER2_INI + MCST_NUM_WORD_PERSONAL)    /* 52U */
#define MCST_BF_OFFSET_USER3_MAX                 (MCST_BF_OFFSET_USER3_INI + MCST_NUM_WORD_PERSONAL)    /* 68U */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_NUM_BF                              (119U)

#define MCST_BFI_FC_IND                          (0U)            /* FC Indicator                             */
#define MCST_BFI_ELE_CO_HIS                      (1U)            /* Electric cost graph History              */
#define MCST_BFI_FUEL_CO_HIS                     (2U)            /* Fuel cost graph History                  */
#define MCST_BFI_ELE_CO_GRH                      (3U)            /* Electric cost graph                      */
#define MCST_BFI_FUEL_CO_GRH                     (4U)            /* Fuel cost graph                          */
#define MCST_BFI_AMBTMP                          (5U)            /* Unit Ambient Temparature                 */
#define MCST_BFI_SPEED                           (6U)            /* Unit Speed                               */
#define MCST_BFI_DIST                            (7U)            /* Unit Distance                            */
#define MCST_BFI_FUECO                           (8U)            /* Unit Fuel Economy                        */
#define MCST_BFI_ELECO                           (9U)            /* Unit Electronic Economy                  */
#define MCST_BFI_REV_ST                          (10U)           /* REV setting                              */
#define MCST_BFI_REV_LIM                         (11U)           /* REV limit                                */
#define MCST_BFI_REV_IND                         (12U)           /* REV indicator                            */
#define MCST_BFI_REV_PK                          (13U)           /* REV peak                                 */
#define MCST_BFI_TRIP_A_UP                       (14U)           /* Trip A Up                                */
#define MCST_BFI_TRIP_A_DN                       (15U)           /* Trip A Down                              */
#define MCST_BFI_TRIP_B_UP                       (16U)           /* Trip B Up                                */
#define MCST_BFI_TRIP_B_DN                       (17U)           /* Trip B Down                              */
#define MCST_BFI_TAST_FLG                        (18U)           /* Meter Taste Diag Flag                    */
#define MCST_BFI_NAME_DRV1                       (19U)           /* Nick Name with or without Driver1        */
#define MCST_BFI_NAME_DRV2                       (20U)           /* Nick Name with or without Driver2        */
#define MCST_BFI_NAME_DRV3                       (21U)           /* Nick Name with or without Driver3        */
#define MCST_BFI_LANG                            (22U)           /* Language                                 */
#define MCST_BFI_WDG_EYE0                        (23U)           /* Simple Widget WI                         */
#define MCST_BFI_WDG_EYE1                        (24U)           /* 1dial Widget ON                          */
#define MCST_BFI_WDG_NAVI                        (25U)           /* Navi Widget ON                           */
#define MCST_BFI_WDG_ADAS                        (26U)           /* ADAS Widget ON                           */
#define MCST_BFI_WDG_ECO                         (27U)           /* Eco Widget ON                            */
#define MCST_BFI_ANALOG_EYE1                     (28U)           /* Analog Meter Change (1dial)              */
#define MCST_BFI_ANALOG_EYE2                     (29U)           /* Analog Meter Change (2dial)              */
#define MCST_BFI_ANALOG                          (30U)           /* Analog Meter Change (4/7inch)            */
#define MCST_BFI_AUDIO_TAB                       (31U)           /* Audio Tab ON/OFF                         */
#define MCST_BFI_ENEMON                          (32U)           /* Energy Monitor Tab ON/OFF                */
#define MCST_BFI_4WD                             (33U)           /* 4WD Tab ON/OFF                           */
#define MCST_BFI_DRVINF_OPE                      (34U)           /* Drive Info Operation                     */
#define MCST_BFI_DRVINF_UP                       (35U)           /* Drive Info Upper row                     */
#define MCST_BFI_DRVINF_DN                       (36U)           /* Drive Info Lower row                     */
#define MCST_BFI_NOW_RUN                         (37U)           /* Now Run                                  */
#define MCST_BFI_EV_DRINFO                       (38U)           /* EV Drive Info                            */
#define MCST_BFI_CROSS_ADV                       (39U)           /* Crossroad Advice                         */
#define MCST_BFI_TEL                             (40U)           /* Tel ON                                   */
#define MCST_BFI_AUDIO_OPE                       (41U)           /* Audio Operation ON                       */
#define MCST_BFI_VOL_OPE                         (42U)           /* Volume Operation On                      */
#define MCST_BFI_VRCTRL                          (43U)           /* VRctrl ON                                */
#define MCST_BFI_STS_TIM                         (44U)           /* Status Time                              */
#define MCST_BFI_STS_ACT                         (45U)           /* Status Notice                            */
#define MCST_BFI_CAR_APP                         (46U)           /* Car Approach                             */
#define MCST_BFI_ILLUMI_ADJ                      (47U)           /* Illumi Adjust ON                         */
#define MCST_BFI_VIEW_EYE0                       (48U)           /* Simple View WI                           */
#define MCST_BFI_VIEW_EYE1                       (49U)           /* 1dial View ON                            */
#define MCST_BFI_VIEW_EYE2                       (50U)           /* 2dial View ON                            */
#define MCST_BFI_VIEW_NAVI                       (51U)           /* Navi View ON                             */
#define MCST_BFI_VIEW_ADAS                       (52U)           /* ADAS View ON                             */
#define MCST_BFI_VIEW_ECO                        (53U)           /* Eco View ON                              */
#define MCST_BFI_VIEW_TRACK                      (54U)           /* 1dialTrack View ON                       */
#define MCST_BFI_VIEW_SHIFT                      (55U)           /* Shift Up Ind View ON                     */
#define MCST_BFI_VIEW_OFFROAD                    (56U)           /* OffRoad View ON                          */
#define MCST_BFI_VIEW_EYE6                       (57U)           /* 6dial View ON                            */
#define MCST_BFI_TACHO                           (58U)           /* Tacho HV Switch                          */
#define MCST_BFI_LEFT_FU_ECO                     (59U)           /* Fuel Cost Graph Info ON                  */
#define MCST_BFI_LEFT_EL_ECO                     (60U)           /* Electric Cost Graph Info ON              */
#define MCST_BFI_LEFT_CONSUMP                    (61U)           /* Consump Info ON                          */
#define MCST_BFI_LEFT_ECO_IND                    (62U)           /* Eco Ind Info ON                          */
#define MCST_BFI_LEFT_ECO_JDG                    (63U)           /* Eco Judge Info ON                        */
#define MCST_BFI_LEFT_EV_RATIO                   (64U)           /* EV Ratio Info ON                         */
#define MCST_BFI_LEFT_NAVI                       (65U)           /* Navigation Info ON                       */
#define MCST_BFI_LEFT_AUDIO                      (66U)           /* Audio Info ON                            */
#define MCST_BFI_LEFT_DRV_INFO                   (67U)           /* Drive Info Info ON                       */
#define MCST_BFI_LEFT_TRIP_A                     (68U)           /* Trip A Info ON                           */
#define MCST_BFI_LEFT_TRIP_B                     (69U)           /* Trip B Info ON                           */
#define MCST_BFI_LEFT_ENE_MON                    (70U)           /* Energy Monitor Info ON                   */
#define MCST_BFI_LEFT_4WD                        (71U)           /* 4WD Info ON                              */
#define MCST_BFI_LEFT_TRAC                       (72U)           /* Traction Monitor Info ON                 */
#define MCST_BFI_LEFT_ANGEL                      (73U)           /* Angel Info ON                            */
#define MCST_BFI_LEFT_PITCH                      (74U)           /* Pitch & Roll Info ON                     */
#define MCST_BFI_LEFT_TR_BRAKE                   (75U)           /* Trailer Brake Info ON                    */
#define MCST_BFI_LEFT_TR_BSM                     (76U)           /* Trailer Mode BSM Info ON                 */
#define MCST_BFI_LEFT_VOLT                       (77U)           /* Volt Info ON                             */
#define MCST_BFI_LEFT_OIL_VOLT                   (78U)           /* Oil & Volt Info ON                       */
#define MCST_BFI_LEFT_ENG_AT                     (79U)           /* Engine & AT OilTemp Info ON              */
#define MCST_BFI_LEFT_ENGINE                     (80U)           /* Engine OilTemp Info ON                   */
#define MCST_BFI_LEFT_AT                         (81U)           /* AT OilTemp Info ON                       */
#define MCST_BFI_LEFT_TURBO                      (82U)           /* Turbo Gauge Info ON                      */
#define MCST_BFI_LEFT_BOOST                      (83U)           /* Boost Gauge Info ON                      */
#define MCST_BFI_LEFT_MOTOR                      (84U)           /* Motor Power Info ON                      */
#define MCST_BFI_LEFT_SPORTS                     (85U)           /* Sports Gage Info ON                      */
#define MCST_BFI_LEFT_G_FORCE                    (86U)           /* G Monitor Info ON                        */
#define MCST_BFI_LEFT_ADBLUE                     (87U)           /* AdBlue Info ON                           */
#define MCST_BFI_LEFT_TPMS                       (88U)           /* TPMS Info ON                             */
#define MCST_BFI_LEFT_OILLVL                     (89U)           /* Oil Level Info ON                        */
#define MCST_BFI_LEFT_FU_ECO_PHV                 (90U)           /* PHV Fuel Cost Graph Info ON              */
#define MCST_BFI_ECO_IND                         (91U)           /* ECO indicator                            */
#define MCST_BFI_EV_IND                          (92U)           /* EV indicator                             */
#define MCST_BFI_HVIND                           (93U)           /* HV system Indicator                      */
#define MCST_BFI_MM_TIMEFMT                      (94U)           /* Time format 12h(MM)                      */
#define MCST_BFI_MM_OFFSET_TIME                  (95U)           /* Offset Time(MM)                          */
#define MCST_BFI_RHEO_NIGHT                      (96U)           /* Night Brightness                         */
#define MCST_BFI_HUDILL                          (97U)           /* HUD Brightness                           */
#define MCST_BFI_HUD_ST                          (98U)           /* HUD Display Setting                      */
#define MCST_BFI_HUD                             (99U)           /* HUD ON/OFF                               */
#define MCST_BFI_AR                              (100U)          /* AR ON/OFF                                */
#define MCST_BFI_HUD_ANALOG                      (101U)          /* HUD Analog Meter                         */
#define MCST_BFI_HUD_ROT                         (102U)          /* HUD Rotation                             */
#define MCST_BFI_DISP_VIEW                       (103U)          /* Now View                                 */
#define MCST_BFI_DISP_EYE0                       (104U)          /* Now Left(0dial)                          */
#define MCST_BFI_DISP_EYE1                       (105U)          /* Now Left(1dial)                          */
#define MCST_BFI_DISP_EYE2                       (106U)          /* Now Left(2dial)                          */
#define MCST_BFI_DISP_MAP                        (107U)          /* Now Left(MAP)                            */
#define MCST_BFI_DISP_ADAS                       (108U)          /* Now Left(ADAS)                           */
#define MCST_BFI_DISP_ECO                        (109U)          /* Now Left(Eco)                            */
#define MCST_BFI_DISP_TRACK                      (110U)          /* Now Left(1dialTrack)                     */
#define MCST_BFI_DISP_SHIFT                      (111U)          /* Now Left(ShiftUpInd)                     */
#define MCST_BFI_DISP_OFFROAD                    (112U)          /* Now Left(Offroad)                        */
#define MCST_BFI_DISP_EYE6                       (113U)          /* Now Left(6dial)                          */
#define MCST_BFI_DISP_CHARGEMODE                 (114U)          /* Now Left(ChargeMode)                     */
#define MCST_BFI_RHEO_DAY                        (115U)          /* Day   Brightness                         */
#define MCST_BFI_TIMEFMT                         (116U)          /* Time Format 12h                          */
#define MCST_BFI_OFFSET_TIME                     (117U)          /* Offset Time                              */
#define MCST_BFI_METWRNCSTM                      (118U)          /* Volume of Meter Warning (M_MWVCUS-)      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_SUP_FC_IND                          (TRUE)
#define MCST_SUP_ELE_CO_HIS                      (TRUE)
#define MCST_SUP_FUEL_CO_HIS                     (TRUE)
#define MCST_SUP_ELE_CO_GRH                      (TRUE)
#define MCST_SUP_FUEL_CO_GRH                     (TRUE)
#define MCST_SUP_AMBTMP                          (TRUE)
#define MCST_SUP_SPEED                           (TRUE)
#define MCST_SUP_DIST                            (TRUE)
#define MCST_SUP_FUECO                           (TRUE)
#define MCST_SUP_ELECO                           (TRUE)
#define MCST_SUP_REV_ST                          (TRUE)
#define MCST_SUP_REV_LIM                         (TRUE)
#define MCST_SUP_REV_IND                         (TRUE)
#define MCST_SUP_REV_PK                          (TRUE)
#define MCST_SUP_TRIP_A_UP                       (TRUE)
#define MCST_SUP_TRIP_A_DN                       (TRUE)
#define MCST_SUP_TRIP_B_UP                       (TRUE)
#define MCST_SUP_TRIP_B_DN                       (TRUE)
#define MCST_SUP_TAST_FLG                        (TRUE)
#define MCST_SUP_NAME_DRV1                       (TRUE)
#define MCST_SUP_NAME_DRV2                       (TRUE)
#define MCST_SUP_NAME_DRV3                       (TRUE)
#define MCST_SUP_LANG                            (TRUE)
#define MCST_SUP_WDG_EYE0                        (TRUE)
#define MCST_SUP_WDG_EYE1                        (TRUE)
#define MCST_SUP_WDG_NAVI                        (TRUE)
#define MCST_SUP_WDG_ADAS                        (TRUE)
#define MCST_SUP_WDG_ECO                         (TRUE)
#define MCST_SUP_ANALOG_EYE1                     (TRUE)
#define MCST_SUP_ANALOG_EYE2                     (TRUE)
#define MCST_SUP_ANALOG                          (TRUE)
#define MCST_SUP_AUDIO_TAB                       (TRUE)
#define MCST_SUP_ENEMON                          (TRUE)
#define MCST_SUP_4WD                             (TRUE)
#define MCST_SUP_DRVINF_OPE                      (TRUE)
#define MCST_SUP_DRVINF_UP                       (TRUE)
#define MCST_SUP_DRVINF_DN                       (TRUE)
#define MCST_SUP_NOW_RUN                         (TRUE)
#define MCST_SUP_EV_DRINFO                       (TRUE)
#define MCST_SUP_CROSS_ADV                       (TRUE)
#define MCST_SUP_TEL                             (TRUE)
#define MCST_SUP_AUDIO_OPE                       (TRUE)
#define MCST_SUP_VOL_OPE                         (TRUE)
#define MCST_SUP_VRCTRL                          (TRUE)
#define MCST_SUP_STS_TIM                         (TRUE)
#define MCST_SUP_STS_ACT                         (TRUE)
#define MCST_SUP_CAR_APP                         (TRUE)
#define MCST_SUP_ILLUMI_ADJ                      (TRUE)
#define MCST_SUP_VIEW_EYE0                       (TRUE)
#define MCST_SUP_VIEW_EYE1                       (TRUE)
#define MCST_SUP_VIEW_EYE2                       (TRUE)
#define MCST_SUP_VIEW_NAVI                       (TRUE)
#define MCST_SUP_VIEW_ADAS                       (TRUE)
#define MCST_SUP_VIEW_ECO                        (TRUE)
#define MCST_SUP_VIEW_TRACK                      (TRUE)
#define MCST_SUP_VIEW_SHIFT                      (TRUE)
#define MCST_SUP_VIEW_OFFROAD                    (TRUE)
#define MCST_SUP_VIEW_EYE6                       (TRUE)
#define MCST_SUP_TACHO                           (TRUE)
#define MCST_SUP_LEFT_FU_ECO                     (TRUE)
#define MCST_SUP_LEFT_EL_ECO                     (TRUE)
#define MCST_SUP_LEFT_CONSUMP                    (TRUE)
#define MCST_SUP_LEFT_ECO_IND                    (TRUE)
#define MCST_SUP_LEFT_ECO_JDG                    (TRUE)
#define MCST_SUP_LEFT_EV_RATIO                   (TRUE)
#define MCST_SUP_LEFT_NAVI                       (TRUE)
#define MCST_SUP_LEFT_AUDIO                      (TRUE)
#define MCST_SUP_LEFT_DRV_INFO                   (TRUE)
#define MCST_SUP_LEFT_TRIP_A                     (TRUE)
#define MCST_SUP_LEFT_TRIP_B                     (TRUE)
#define MCST_SUP_LEFT_ENE_MON                    (TRUE)
#define MCST_SUP_LEFT_4WD                        (TRUE)
#define MCST_SUP_LEFT_TRAC                       (TRUE)
#define MCST_SUP_LEFT_ANGEL                      (TRUE)
#define MCST_SUP_LEFT_PITCH                      (TRUE)
#define MCST_SUP_LEFT_TR_BRAKE                   (TRUE)
#define MCST_SUP_LEFT_TR_BSM                     (TRUE)
#define MCST_SUP_LEFT_VOLT                       (TRUE)
#define MCST_SUP_LEFT_OIL_VOLT                   (TRUE)
#define MCST_SUP_LEFT_ENG_AT                     (TRUE)
#define MCST_SUP_LEFT_ENGINE                     (TRUE)
#define MCST_SUP_LEFT_AT                         (TRUE)
#define MCST_SUP_LEFT_TURBO                      (TRUE)
#define MCST_SUP_LEFT_BOOST                      (TRUE)
#define MCST_SUP_LEFT_MOTOR                      (TRUE)
#define MCST_SUP_LEFT_SPORTS                     (TRUE)
#define MCST_SUP_LEFT_G_FORCE                    (TRUE)
#define MCST_SUP_LEFT_ADBLUE                     (TRUE)
#define MCST_SUP_LEFT_TPMS                       (TRUE)
#define MCST_SUP_LEFT_OILLVL                     (TRUE)
#define MCST_SUP_LEFT_FU_ECO_PHV                 (TRUE)
#define MCST_SUP_ECO_IND                         (TRUE)
#define MCST_SUP_EV_IND                          (TRUE)
#define MCST_SUP_HVIND                           (TRUE)
#define MCST_SUP_MM_TIMEFMT                      (TRUE)
#define MCST_SUP_MM_OFFSET_TIME                  (TRUE)
#define MCST_SUP_RHEO_NIGHT                      (TRUE)
#define MCST_SUP_HUDILL                          (TRUE)
#define MCST_SUP_HUD_ST                          (TRUE)
#define MCST_SUP_HUD                             (TRUE)
#define MCST_SUP_AR                              (TRUE)
#define MCST_SUP_HUD_ANALOG                      (TRUE)
#define MCST_SUP_HUD_ROT                         (TRUE)
#define MCST_SUP_DISP_VIEW                       (TRUE)
#define MCST_SUP_DISP_EYE0                       (TRUE)
#define MCST_SUP_DISP_EYE1                       (TRUE)
#define MCST_SUP_DISP_EYE2                       (TRUE)
#define MCST_SUP_DISP_MAP                        (TRUE)
#define MCST_SUP_DISP_ADAS                       (TRUE)
#define MCST_SUP_DISP_ECO                        (TRUE)
#define MCST_SUP_DISP_TRACK                      (TRUE)
#define MCST_SUP_DISP_SHIFT                      (TRUE)
#define MCST_SUP_DISP_OFFROAD                    (TRUE)
#define MCST_SUP_DISP_EYE6                       (TRUE)
#define MCST_SUP_DISP_CHARGEMODE                 (TRUE)
#define MCST_SUP_RHEO_DAY                        (TRUE)
#define MCST_SUP_TIMEFMT                         (TRUE)
#define MCST_SUP_OFFSET_TIME                     (TRUE)
#define MCST_SUP_METWRNCSTM                      (TRUE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_INI_FC_IND                            (0x00000000U)
#define MCST_INI_ELE_CO_HIS                        (0x00000000U)
#define MCST_INI_FUEL_CO_HIS                       (0x00000000U)
#define MCST_INI_ELE_CO_GRH                        (0x00000001U)
#define MCST_INI_FUEL_CO_GRH                       (0x00000001U)
#define MCST_INI_AMBTMP                            (0x00000003U)
#define MCST_INI_SPEED                             (0x00000003U)
#define MCST_INI_DIST                              (0x00000003U)
#define MCST_INI_FUECO                             (0x00000007U)
#define MCST_INI_ELECO                             (0x00000007U)
#define MCST_INI_REV_ST                            (0x0000007FU)
#define MCST_INI_REV_LIM                           (0x00000000U)
#define MCST_INI_REV_IND                           (0x00000003U)
#define MCST_INI_REV_PK                            (0x00000003U)
#define MCST_INI_TRIP_A_UP                         (0x00000001U)
#define MCST_INI_TRIP_A_DN                         (0x00000002U)
#define MCST_INI_TRIP_B_UP                         (0x00000001U)
#define MCST_INI_TRIP_B_DN                         (0x00000002U)
#define MCST_INI_TAST_FLG                          (0x00000000U)
#define MCST_INI_NAME_DRV1                         (0x00000000U)
#define MCST_INI_NAME_DRV2                         (0x00000000U)
#define MCST_INI_NAME_DRV3                         (0x00000000U)
#define MCST_INI_LANG                              (0x0000003FU)
#define MCST_INI_WDG_EYE0                          (0x00000000U)
#define MCST_INI_WDG_EYE1                          (0x00000000U)
#define MCST_INI_WDG_NAVI                          (0x00000000U)
#define MCST_INI_WDG_ADAS                          (0x00000000U)
#define MCST_INI_WDG_ECO                           (0x00000000U)
#define MCST_INI_ANALOG_EYE1                       (0x00000007U)
#define MCST_INI_ANALOG_EYE2                       (0x00000007U)
#define MCST_INI_ANALOG                            (0x00000000U)
#define MCST_INI_AUDIO_TAB                         (0x00000000U)
#define MCST_INI_ENEMON                            (0x00000000U)
#define MCST_INI_4WD                               (0x00000000U)
#define MCST_INI_DRVINF_OPE                        (0x00000000U)
#define MCST_INI_DRVINF_UP                         (0x00000001U)
#define MCST_INI_DRVINF_DN                         (0x00000002U)
#define MCST_INI_NOW_RUN                           (0x00000000U)
#define MCST_INI_EV_DRINFO                         (0x00000000U)
#define MCST_INI_CROSS_ADV                         (0x00000001U)
#define MCST_INI_TEL                               (0x00000003U)
#define MCST_INI_AUDIO_OPE                         (0x00000003U)
#define MCST_INI_VOL_OPE                           (0x00000003U)
#define MCST_INI_VRCTRL                            (0x00000003U)
#define MCST_INI_STS_TIM                           (0x00000001U)
#define MCST_INI_STS_ACT                           (0x00000001U)
#define MCST_INI_CAR_APP                           (0x00000001U)
#define MCST_INI_ILLUMI_ADJ                        (0x00000003U)
#define MCST_INI_VIEW_EYE0                         (0x00000003U)
#define MCST_INI_VIEW_EYE1                         (0x00000003U)
#define MCST_INI_VIEW_EYE2                         (0x00000003U)
#define MCST_INI_VIEW_NAVI                         (0x00000003U)
#define MCST_INI_VIEW_ADAS                         (0x00000003U)
#define MCST_INI_VIEW_ECO                          (0x00000003U)
#define MCST_INI_VIEW_TRACK                        (0x00000003U)
#define MCST_INI_VIEW_SHIFT                        (0x00000003U)
#define MCST_INI_VIEW_OFFROAD                      (0x00000003U)
#define MCST_INI_VIEW_EYE6                         (0x00000003U)
#define MCST_INI_TACHO                             (0x00000000U)
#define MCST_INI_LEFT_FU_ECO                       (0x00000003U)
#define MCST_INI_LEFT_EL_ECO                       (0x00000003U)
#define MCST_INI_LEFT_CONSUMP                      (0x00000003U)
#define MCST_INI_LEFT_ECO_IND                      (0x00000003U)
#define MCST_INI_LEFT_ECO_JDG                      (0x00000003U)
#define MCST_INI_LEFT_EV_RATIO                     (0x00000003U)
#define MCST_INI_LEFT_NAVI                         (0x00000003U)
#define MCST_INI_LEFT_AUDIO                        (0x00000003U)
#define MCST_INI_LEFT_DRV_INFO                     (0x00000003U)
#define MCST_INI_LEFT_TRIP_A                       (0x00000003U)
#define MCST_INI_LEFT_TRIP_B                       (0x00000003U)
#define MCST_INI_LEFT_ENE_MON                      (0x00000003U)
#define MCST_INI_LEFT_4WD                          (0x00000003U)
#define MCST_INI_LEFT_TRAC                         (0x00000003U)
#define MCST_INI_LEFT_ANGEL                        (0x00000003U)
#define MCST_INI_LEFT_PITCH                        (0x00000003U)
#define MCST_INI_LEFT_TR_BRAKE                     (0x00000003U)
#define MCST_INI_LEFT_TR_BSM                       (0x00000003U)
#define MCST_INI_LEFT_VOLT                         (0x00000003U)
#define MCST_INI_LEFT_OIL_VOLT                     (0x00000003U)
#define MCST_INI_LEFT_ENG_AT                       (0x00000003U)
#define MCST_INI_LEFT_ENGINE                       (0x00000003U)
#define MCST_INI_LEFT_AT                           (0x00000003U)
#define MCST_INI_LEFT_TURBO                        (0x00000003U)
#define MCST_INI_LEFT_BOOST                        (0x00000003U)
#define MCST_INI_LEFT_MOTOR                        (0x00000003U)
#define MCST_INI_LEFT_SPORTS                       (0x00000003U)
#define MCST_INI_LEFT_G_FORCE                      (0x00000003U)
#define MCST_INI_LEFT_ADBLUE                       (0x00000003U)
#define MCST_INI_LEFT_TPMS                         (0x00000003U)
#define MCST_INI_LEFT_OILLVL                       (0x00000003U)
#define MCST_INI_LEFT_FU_ECO_PHV                   (0x00000003U)
#define MCST_INI_ECO_IND                           (0x00000003U)
#define MCST_INI_EV_IND                            (0x00000003U)
#define MCST_INI_HVIND                             (0x00000003U)
#define MCST_INI_MM_TIMEFMT                        (0x00000003U)
#define MCST_INI_MM_OFFSET_TIME                    (0x00000000U)
#define MCST_INI_RHEO_NIGHT                        (0x0000001FU)
#define MCST_INI_HUDILL                            (0x00000014U)
#define MCST_INI_HUD_ST                            (0x00000002U)
#define MCST_INI_HUD                               (0x00000003U)
#define MCST_INI_AR                                (0x00000000U)
#define MCST_INI_HUD_ANALOG                        (0x00000007U)
#define MCST_INI_HUD_ROT                           (0x00000000U)
#define MCST_INI_DISP_VIEW                         (0x00000001U)
#define MCST_INI_DISP_EYE0                         (0x0000000BU)
#define MCST_INI_DISP_EYE1                         (0x0000000BU)
#define MCST_INI_DISP_EYE2                         (0x0000000BU)
#define MCST_INI_DISP_MAP                          (0x0000000BU)
#define MCST_INI_DISP_ADAS                         (0x0000000BU)
#define MCST_INI_DISP_ECO                          (0x0000000BU)
#define MCST_INI_DISP_TRACK                        (0x0000000BU)
#define MCST_INI_DISP_SHIFT                        (0x0000000BU)
#define MCST_INI_DISP_OFFROAD                      (0x0000000BU)
#define MCST_INI_DISP_EYE6                         (0x0000000BU)
#define MCST_INI_DISP_CHARGEMODE                   (0x0000000BU)
#define MCST_INI_RHEO_DAY                          (0x00000015U)
#define MCST_INI_TIMEFMT                           (0x00000003U)
#define MCST_INI_OFFSET_TIME                       (0x00000000U)
#define MCST_INI_METWRNCSTM                        (0x00000001U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define METCSTM_SUPPORT                           (0U)         /* TODO                                    */
#define METCSTM_TACHO_SUPPORT                     (0U)         /* TACHO only support in HEV/HV)           */
#define MCST_DESIGN_TYPE_SUPPORT                  (0U)         /* METCSTM > Meter Design Type             */
#define MCST_PERSET_SUPPORT                       (1U)         /* PERSET(only 115D/117D/100D/330D)        */
#define MCST_PHASE2_SUPPORT                       (1U)         /* only phase2                             */
#define MCST_CSTMLST_SUPPORT                      (1U)         /* only non Ais                            */
#define MCST_FACEID_SUPPORT                       (1U)         /* FaceId support                          */
#define MCST_12INCH_SUPPORT                       (1U)         /* 12inch support                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_FUNC_NUM                             (23U)

#define MCST_L_HUD_FUNC                           ( 0U)       /*  0:HUD                 function existence     */
#define MCST_L_AR_FUNC                            ( 1U)       /*  1:AR                  function existence     */
#define MCST_L_MET_TYFN                           ( 2U)       /*  2:Meter type          function existence     */
#define MCST_L_TACHO_FUNC                         ( 3U)       /*  3:Tachometer setting  function existence     */
#define MCST_L_RHEOF                              ( 4U)       /*  4:Rheostat            function existence     */
#define MCST_L_CONT_FUNC                          ( 5U)       /*  5:Meter contents      function existence     */
#define MCST_L_ECO_FUNC                           ( 6U)       /*  6:ECO drive indicator function existence     */
#define MCST_L_EV_FUNC                            ( 7U)       /*  7:EV drive indicator  function existence     */
#define MCST_L_REV_FUNC                           ( 8U)       /*  8:REV indicator       function existence     */
#define MCST_L_RV_PK_F                            ( 9U)       /*  9:REV peak            function existence     */
#define MCST_L_MANTE                              (10U)       /* 10:Maintenance         function existence     */
#define MCST_L_OMAINTE                            (11U)       /* 11:Oil Maintenance     function existence     */
#define MCST_L_VS_FUNC                            (12U)       /* 12:Vehicle setting existence                  */
#define MCST_L_STSWLHCSTM1                        (13U)       /* 13:Selectable Custom Function LH 1            */
#define MCST_L_STSWLHCSTM2                        (14U)       /* 14:Selectable Custom Function LH 2            */
#define MCST_L_STSWRHCSTM1                        (15U)       /* 15:Selectable Custom Function RH 1            */
#define MCST_L_STSWRHCSTM2                        (16U)       /* 16:Selectable Custom Function RH 2            */
#define MCST_L_STSWRHCSTM3                        (17U)       /* 17:Selectable Custom Function RH 3            */
#define MCST_L_STSWLH                             (18U)       /* 18:Steering SW Customize LH Selectable Preset */
#define MCST_L_STSWRH                             (19U)       /* 19:Steering SW Customize RH Selectable Preset */
#define MCST_L_STSW_FUNC                          (20U)       /* 20:Steering SW Customize Function ON/OFF      */
#define MCST_L_GRV_FUNC                           (21U)       /* 21:Winter groves mode function existence      */
#define MCST_L_MET_TSTFN                          (22U)       /* 22:Meter design type   function existence     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_DIAG_NUM                             (45U)

#define MCST_DIAG_HUD                             ( 0U)       /*  0: DID:10A8 (HUD ON/OFF)                     */
#define MCST_DIAG_HUD_ILL                         ( 1U)       /*  1: DID:10A8 (HUD Brightness)                 */
#define MCST_DIAG_HUD_ST                          ( 2U)       /*  2: DID:10A8 (HUD Display Setting)            */
#define MCST_DIAG_MM_MET_TYP                      ( 3U)       /*  3: DID:10A8 (METCSTM:Meter Type)             */
#define MCST_DIAG_MM_TACHO                        ( 4U)       /*  4: DID:10A8 (METCSTM:Tacho Meter)            */
#define MCST_DIAG_RHEO                            ( 5U)       /*  5: DID:10A8 (Brightness)                     */
#define MCST_DIAG_MM_ECO_IND                      ( 6U)       /*  6: DID:10A8 (METCSTM:ECO Indicator)          */
#define MCST_DIAG_MM_EV_IND                       ( 7U)       /*  7: DID:10A8 (METCSTM:EV Indicator)           */
#define MCST_DIAG_MM_REV_IND                      ( 8U)       /*  8: DID:10A8 (METCSTM:REV Indicator)          */
#define MCST_DIAG_MM_REV_ST                       ( 9U)       /*  9: DID:10A8 (METCSTM:REV Setting)            */
#define MCST_DIAG_MM_REV_PK                       (10U)       /* 10: DID:10A8 (METCSTM:REV Peak)               */
#define MCST_DIAG_MM_MET_DSP                      (11U)       /* 11: DID:10A8 (METCSTM:Meter Display Setting)  */
#define MCST_DIAG_MM_ANALOG_MET                   (12U)
#define MCST_DIAG_MM_ECO_DRV_IND                  (13U)
#define MCST_DIAG_MM_EV_IND_DSP                   (14U)
#define MCST_DIAG_MM_HV_SYS_IND                   (15U)
#define MCST_DIAG_MM_MET_DSP_7INCH                (16U)
#define MCST_DIAG_MM_MET_DSP_LT                   (17U)
#define MCST_DIAG_MM_MET_DSP_CT                   (18U)
#define MCST_DIAG_MM_MET_DSP_RT                   (19U)
#define MCST_DIAG_MM_MET_DSP_PRESET               (20U)
#define MCST_DIAG_MM_MET_LAYOUT                   (21U)
#define MCST_DIAG_MM_MET_DESIGN                   (22U)
#define MCST_DIAG_MM_CURCNT_LBYTE                 (23U)
#define MCST_DIAG_MM_CURCNT_HBYTE                 (24U)
#define MCST_DIAG_MM_FUEL_FLG                     (25U)
#define MCST_DIAG_MM_ELEC_FLG                     (26U)
#define MCST_DIAG_MM_POP_CROSS                    (27U)
#define MCST_DIAG_MM_POP_TEL                      (28U)
#define MCST_DIAG_MM_POP_AUDIO                    (29U)
#define MCST_DIAG_MM_POP_VOLUME                   (30U)
#define MCST_DIAG_MM_POP_VOICE                    (31U)
#define MCST_DIAG_MM_POP_TIME                     (32U)
#define MCST_DIAG_MM_POP_NOTIFY                   (33U)
#define MCST_DIAG_MM_POP_DIM                      (34U)
#define MCST_DIAG_MM_EV_DRVINF                    (35U)
#define MCST_DIAG_MM_DRVINF_CALC                  (36U)
#define MCST_DIAG_MM_DRVINF_UP                    (37U)
#define MCST_DIAG_MM_DRVINF_DN                    (38U)
#define MCST_DIAG_MM_MET_TRIP_A_UP                (39U)
#define MCST_DIAG_MM_MET_TRIP_A_DN                (40U)
#define MCST_DIAG_MM_MET_TRIP_B_UP                (41U)
#define MCST_DIAG_MM_MET_TRIP_B_DN                (42U)
#define MCST_DIAG_MM_ENG_MONI                     (43U)
#define MCST_DIAG_MM_4WD_AWD                      (44U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LANG                           */
#define MCST_LANG_JPN                        (LANG_VAL__________JPN)   /* Japan               : Japanese               */
#define MCST_LANG_USA_ENG                    (LANG_VAL______USA_ENG)   /* USA                 : English                */
#define MCST_LANG_BRI_ENG                    (LANG_VAL______BRI_ENG)   /* United Kingdom      : English                */
#define MCST_LANG_FRENCH                     (LANG_VAL_______FRENCH)   /* France              : French                 */
#define MCST_LANG_GERMAN                     (LANG_VAL_______GERMAN)   /* Germany             : German                 */
#define MCST_LANG_ITALIAN                    (LANG_VAL______ITALIAN)   /* Italy               : Italian                */
#define MCST_LANG_DUTCH                      (LANG_VAL________DUTCH)   /* Netherlands         : Dutch                  */
#define MCST_LANG_SPANISH                    (LANG_VAL______SPANISH)   /* Spain               : Spanish                */
#define MCST_LANG_SWEDISH                    (LANG_VAL______SWEDISH)   /* Sweden              : Swedish                */
#define MCST_LANG_DANISH                     (LANG_VAL_______DANISH)   /* Denmark             : Danish                 */
#define MCST_LANG_NORWEGIAN                  (LANG_VAL____NORWEGIAN)   /* Norway              : Norwegian              */
#define MCST_LANG_PORTUGUESE                 (LANG_VAL___PORTUGUESE)   /* Portugal            : Portuguese             */
#define MCST_LANG_RUSSIAN                    (LANG_VAL______RUSSIAN)   /* Russia              : Russian                */
#define MCST_LANG_GREEK                      (LANG_VAL________GREEK)   /* Greece              : Greek                  */
#define MCST_LANG_POLISH                     (LANG_VAL_______POLISH)   /* Poland              : Polish                 */
#define MCST_LANG_FINNISH                    (LANG_VAL______FINNISH)   /* Finland             : Finnish                */
#define MCST_LANG_CHN_SMP                    (LANG_VAL______CHN_SMP)   /* China               : Simplified             */
#define MCST_LANG_CHN_TRA                    (LANG_VAL______CHN_TRA)   /* China               : Traditional            */
#define MCST_LANG_KOREAN                     (LANG_VAL_______KOREAN)   /* Korea               : Korean                 */
#define MCST_LANG_UKRAINIAN                  (LANG_VAL____UKRAINIAN)   /* Ukraine             : Ukrainian              */
#define MCST_LANG_TURKISH                    (LANG_VAL______TURKISH)   /* Turkey              : Turkish                */
#define MCST_LANG_HUNGARIAN                  (LANG_VAL____HUNGARIAN)   /* Hungary             : Hungarian              */
#define MCST_LANG_CZECH                      (LANG_VAL________CZECH)   /* the Czech Repubic   : Czech                  */
#define MCST_LANG_SLOVAK                     (LANG_VAL_______SLOVAK)   /* Slovakia            : Slovak                 */
#define MCST_LANG_ROMANIAN                   (LANG_VAL_____ROMANIAN)   /* Romania             : Romanian               */
#define MCST_LANG_ARABIC                     (LANG_VAL_______ARABIC)   /* Middle East         : Arabic                 */
#define MCST_LANG_THAI                       (LANG_VAL_________THAI)   /* Thailand            : Thai                   */
#define MCST_LANG_BRA_PORTUGU                (LANG_VAL__BRA_PORTUGU)   /* Brazil              : Portuguese             */
#define MCST_LANG_SA_SPANISH                 (LANG_VAL___SA_SPANISH)   /* South America       : Spanish                */
#define MCST_LANG_MIDEAST_ENG                (LANG_VAL__MIDEAST_ENG)   /* Middle East         : English                */
#define MCST_LANG_JPN_ENGLISH                (LANG_VAL__JPN_ENGLISH)   /* Japan               : English                */
#define MCST_LANG_CAN_FRENCH                 (LANG_VAL___CAN_FRENCH)   /* Canada              : French                 */
#define MCST_LANG_MEX_SPANISH                (LANG_VAL__MEX_SPANISH)   /* Mexico              : Spanish                */
#define MCST_LANG_MALAY                      (LANG_VAL________MALAY)   /* Malaysia            : Malay                  */
#define MCST_LANG_INDONESIAN                 (LANG_VAL___INDONESIAN)   /* Indonesia           : Indonesian             */
#define MCST_LANG_EUSKARA                    (LANG_VAL______EUSKARA)   /* Euskal Herria       : euskara                */
#define MCST_LANG_BULGARIAN                  (LANG_VAL____BULGARIAN)   /* Bulgaria            : Bulgarian              */
#define MCST_LANG_VLAAMS                     (LANG_VAL_______VLAAMS)   /* Belgium             : Vlaams                 */
#define MCST_LANG_AU_ENG                     (LANG_VAL_______AU_ENG)   /* Australia           : English                */
#define MCST_LANG_TAIWANESE                  (LANG_VAL____TAIWANESE)   /* Taiwan              : Taiwanese              */
#define MCST_LANG_INDIA_ENG                  (LANG_VAL____INDIA_ENG)   /* India               : English                */
#define MCST_LANG_HINDI                      (LANG_VAL________HINDI)   /* India               : Hindi                  */
#define MCST_LANG_VIETNAMESE                 (LANG_VAL___VIETNAMESE)   /* Vietnam             : Vietnamese             */
#define MCST_LANG_FILIPINO                   (LANG_VAL_____FILIPINO)   /* Philippines         : Filipino               */
#define MCST_LANG_TAMIL                      (LANG_VAL________TAMIL)   /* South India         : Tamil                  */
#define MCST_LANG_PERSIAN                    (LANG_VAL______PERSIAN)   /* Middle East         : Persian                */
#define MCST_LANG_HEBREW                     (LANG_VAL_______HEBREW)   /* Israel              : Hebrew                 */
#define MCST_LANG_ISRAEL                     (LANG_VAL_______ISRAEL)   /* Israel              : Israel                 */
#define MCST_LANG_UNDEF                      (63U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ECO_IND                        */
#define MCST_ECO_IND_OFF                     (0U)
#define MCST_ECO_IND_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_EV_IND                         */
#define MCST_EV_IND_OFF                      (0U)
#define MCST_EV_IND_ON                       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_AMBTMP                         */
#define MCST_AMBTEMP_CEL                     (UNIT_VAL_AMBTMP_CEL)
#define MCST_AMBTEMP_FAH                     (UNIT_VAL_AMBTMP_FAH)
#define MCST_AMBTEMP_UNDEF1                  (2U)
#define MCST_AMBTEMP_UNDEF2                  (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_SPEED                          */
#define MCST_SPEED_KMPH                      (UNIT_VAL_SPEED_KMPH)
#define MCST_SPEED_MPH                       (UNIT_VAL_SPEED_MPH )
#define MCST_SPEED_UNDEF1                    (2U)
#define MCST_SPEED_UNDEF2                    (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DIST_OPE                       */
#define MCST_DIST_KM                         (UNIT_VAL_DIST_KM  )
#define MCST_DIST_MILE                       (UNIT_VAL_DIST_MILE)
#define MCST_DIST_UNDEF1                     (2U)
#define MCST_DIST_UNDEF2                     (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_FUECO                          */
#define MCST_FUECO_KMPL                      (UNIT_VAL_FUECO_KMPL    )
#define MCST_FUECO_LP100KM                   (UNIT_VAL_FUECO_LP100KM )
#define MCST_FUECO_MPG_USA                   (UNIT_VAL_FUECO_MPG_USA )
#define MCST_FUECO_MPG_UK                    (UNIT_VAL_FUECO_MPG_UK  )
#define MCST_FUECO_MPG_E                     (UNIT_VAL_FUECO_MPG_E   )
#define MCST_FUECO_KMPKG                     (UNIT_VAL_FUECO_KMPKG   )
#define MCST_FUECO_KGP100KM                  (UNIT_VAL_FUECO_KGP100KM)
#define MCST_FUECO_UNDEF1                    ( 7U)
#define MCST_FUECO_UNDEF2                    ( 8U)
#define MCST_FUECO_UNDEF3                    ( 9U)
#define MCST_FUECO_UNDEF4                    (10U)
#define MCST_FUECO_UNDEF5                    (11U)
#define MCST_FUECO_UNDEF6                    (12U)
#define MCST_FUECO_UNDEF7                    (13U)
#define MCST_FUECO_UNDEF8                    (14U)
#define MCST_FUECO_UNDEF9                    (15U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ELECO                          */
#define MCST_ELECO_WHPKM                     (UNIT_VAL_ELECO_WHPKM    )
#define MCST_ELECO_KWHPKM                    (UNIT_VAL_ELECO_KWHPKM   )
#define MCST_ELECO_WHPMILE                   (UNIT_VAL_ELECO_WHPMILE  )
#define MCST_ELECO_KWHPMILE                  (UNIT_VAL_ELECO_KWHPMILE )
#define MCST_ELECO_KMPKWH                    (UNIT_VAL_ELECO_KMPKWH   )
#define MCST_ELECO_KWHP100KM                 (UNIT_VAL_ELECO_KWHP100KM)
#define MCST_ELECO_MILEPKWH                  (UNIT_VAL_ELECO_MILEPKWH )
#define MCST_ELECO_UNDEF1                    ( 7U)
#define MCST_ELECO_UNDEF2                    ( 8U)
#define MCST_ELECO_UNDEF3                    ( 9U)
#define MCST_ELECO_UNDEF4                    (10U)
#define MCST_ELECO_UNDEF5                    (11U)
#define MCST_ELECO_UNDEF6                    (12U)
#define MCST_ELECO_UNDEF7                    (13U)
#define MCST_ELECO_UNDEF8                    (14U)
#define MCST_ELECO_UNDEF9                    (15U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_CROSS_ADV                      */
#define MCST_CROSS_ADV_OFF                   (0U)
#define MCST_CROSS_ADV_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DRVINF_OPE                     */
#define MCST_DRVINF_OPE_AFT_STRT             (0U)
#define MCST_DRVINF_OPE_AFT_RST              (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DRVINF_UP                      */
#define MCST_DRVINF_UP_AVG_SPD               (0U)
#define MCST_DRVINF_UP_MIL                   (1U)
#define MCST_DRVINF_UP_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DRVINF_DN                      */
#define MCST_DRVINF_DN_AVG_SPD               (0U)
#define MCST_DRVINF_DN_MIL                   (1U)
#define MCST_DRVINF_DN_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_AUDIO_OPE                      */
#define MCST_DRVINF_AUDIO_OPE_OFF            (0U)
#define MCST_DRVINF_AUDIO_OPE_ON             (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_RHEO_DAY                       */
#define MCST_RHEO_DAY_MIN_HOLD               ( 0U)
#define MCST_RHEO_DAY_BRIGHTNESS01           ( 1U)
#define MCST_RHEO_DAY_BRIGHTNESS02           ( 2U)
#define MCST_RHEO_DAY_BRIGHTNESS03           ( 3U)
#define MCST_RHEO_DAY_BRIGHTNESS04           ( 4U)
#define MCST_RHEO_DAY_BRIGHTNESS05           ( 5U)
#define MCST_RHEO_DAY_BRIGHTNESS06           ( 6U)
#define MCST_RHEO_DAY_BRIGHTNESS07           ( 7U)
#define MCST_RHEO_DAY_BRIGHTNESS08           ( 8U)
#define MCST_RHEO_DAY_BRIGHTNESS09           ( 9U)
#define MCST_RHEO_DAY_BRIGHTNESS10           (10U)
#define MCST_RHEO_DAY_BRIGHTNESS11           (11U)
#define MCST_RHEO_DAY_BRIGHTNESS12           (12U)
#define MCST_RHEO_DAY_BRIGHTNESS13           (13U)
#define MCST_RHEO_DAY_BRIGHTNESS14           (14U)
#define MCST_RHEO_DAY_BRIGHTNESS15           (15U)
#define MCST_RHEO_DAY_BRIGHTNESS16           (16U)
#define MCST_RHEO_DAY_BRIGHTNESS17           (17U)
#define MCST_RHEO_DAY_BRIGHTNESS18           (18U)
#define MCST_RHEO_DAY_BRIGHTNESS19           (19U)
#define MCST_RHEO_DAY_BRIGHTNESS20           (20U)
#define MCST_RHEO_DAY_MAX_HOLD               (21U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_RHEO_NIGHT                     */
#define MCST_RHEO_NIGHT_MIN_HOLD             ( 0U)
#define MCST_RHEO_NIGHT_BRIGHTNESS01         ( 1U)
#define MCST_RHEO_NIGHT_BRIGHTNESS02         ( 2U)
#define MCST_RHEO_NIGHT_BRIGHTNESS03         ( 3U)
#define MCST_RHEO_NIGHT_BRIGHTNESS04         ( 4U)
#define MCST_RHEO_NIGHT_BRIGHTNESS05         ( 5U)
#define MCST_RHEO_NIGHT_BRIGHTNESS06         ( 6U)
#define MCST_RHEO_NIGHT_BRIGHTNESS07         ( 7U)
#define MCST_RHEO_NIGHT_BRIGHTNESS08         ( 8U)
#define MCST_RHEO_NIGHT_BRIGHTNESS09         ( 9U)
#define MCST_RHEO_NIGHT_BRIGHTNESS10         (10U)
#define MCST_RHEO_NIGHT_BRIGHTNESS11         (11U)
#define MCST_RHEO_NIGHT_BRIGHTNESS12         (12U)
#define MCST_RHEO_NIGHT_BRIGHTNESS13         (13U)
#define MCST_RHEO_NIGHT_BRIGHTNESS14         (14U)
#define MCST_RHEO_NIGHT_BRIGHTNESS15         (15U)
#define MCST_RHEO_NIGHT_BRIGHTNESS16         (16U)
#define MCST_RHEO_NIGHT_BRIGHTNESS17         (17U)
#define MCST_RHEO_NIGHT_BRIGHTNESS18         (18U)
#define MCST_RHEO_NIGHT_BRIGHTNESS19         (19U)
#define MCST_RHEO_NIGHT_BRIGHTNESS20         (20U)
#define MCST_RHEO_NIGHT_MAX_HOLD             (21U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HVIND                          */
#define MCST_HVIND_OFF                       (0U)
#define MCST_HVIND_ON                        (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_FUEL_CO_GRH                    */
#define MCST_FUE_CO_GRH_AFT_STRT             (0U)
#define MCST_FUE_CO_GRH_AFT_RST              (1U)
#define MCST_FUE_CO_GRH_AFT_FUEL             (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_OFFSET_TIME                    */
#define MCST_OFFSET_TIME_MIN                 (0xABA0)
#define MCST_OFFSET_TIME_DEF                 (0x00)
#define MCST_OFFSET_TIME_MAX                 (0x5460)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WIDGET                         */
#define MCST_WIDGET_OFF                      (0U)
#define MCST_WIDGET_ON                       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_NOW_RUN                        */
#define MCST_NOW_RUN_DRIVEINFO               (0U)
#define MCST_NOW_RUN_ECOJUDGE                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ANALOG_EYE1                         */
#define MCST_ANALOG_EYE1_TACHOMET                 (0U)
#define MCST_ANALOG_EYE1_SPEEDMET                 (1U)
#define MCST_ANALOG_EYE1_HVIND                    (2U)
#define MCST_ANALOG_EYE1_FCIND                    (3U)
#define MCST_ANALOG_EYE1_POWER                    (4U)
#define MCST_ANALOG_EYE1_DMODE                    (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ANALOG_EYE2                         */
#define MCST_ANALOG_EYE2_TACHOMET                 (0U)
#define MCST_ANALOG_EYE2_HVIND                    (1U)
#define MCST_ANALOG_EYE2_FCIND                    (2U)
#define MCST_ANALOG_EYE2_POWER                    (3U)
#define MCST_ANALOG_EYE2_DMODE                    (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TIMEFMT                        */
#define MCST_TIMEFMT_24H                     (TIMEFMT_VAL_24H)
#define MCST_TIMEFMT_12H                     (TIMEFMT_VAL_12H)
#define MCST_TIMEFMT_UNDEF1                  (2U)
#define MCST_TIMEFMT_UNDEF2                  (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TEL                            */
#define MCST_TEL_OFF                         (0U)
#define MCST_TEL_ON                          (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VOL_OPE                        */
#define MCST_VOL_OPE_OFF                     (0U)
#define MCST_VOL_OPE_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VRCTRL                         */
#define MCST_VRCTRL_OFF                      (0U)
#define MCST_VRCTRL_ON                       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_STS_TIM                        */
#define MCST_STS_TIM_OFF                     (0U)
#define MCST_STS_TIM_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_STS_ACT                        */
#define MCST_STS_ACT_OFF                     (0U)
#define MCST_STS_ACT_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ILLUMI_ADJ                        */
#define MCST_ILLUMI_ADJ_OFF                   (0U)
#define MCST_ILLUMI_ADJ_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_EV_DRINFO                        */
#define MCST_EV_DRINFO_ENE                    (0U)
#define MCST_EV_DRINFO_DIS                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TACHO                          */
#define MCST_TACHO_UNDEF                     (0U)
#define MCST_TACHO_AUTO_SWCH                 (1U)
#define MCST_TACHO_TACHOMET                  (2U)
#define MCST_TACHO_HVMET                     (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_REV_IND                        */
#define MCST_REV_IND_OFF                     (0U)
#define MCST_REV_IND_ON                      (1U)
#define MCST_REV_IND_UNDEF1                  (2U)
#define MCST_REV_IND_UNDEF2                  (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_REV_PK                         */
#define MCST_REV_PK_OFF                      (0U)
#define MCST_REV_PK_ON                       (1U)
#define MCST_REV_PK_UNDEF1                   (2U)
#define MCST_REV_PK_UNDEF2                   (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_REV_LIM                        */
#define MCST_REV_LIM_MIN                     (  0U)        /*  5000 rpm  LSB:50rpm  offset:5000     */
#define MCST_REV_LIM_MAX                     (100U)        /* 10000 rpm  LSB:50rpm                  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_REV_ST                         */
#define MCST_REV_ST_MIN                      (GAGDST_REVIND_OPTTH_MIN)        /* LSB:100rpm         */
#define MCST_REV_ST_MAX                      (GAGDST_REVIND_OPTTH_MAX)        /* LSB:100rpm         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ENDING                         */
#define MCST_ENDING_OFF                      (0U)
#define MCST_ENDING_ON                       (1U)
#define MCST_ENDING_UNDEF1                   (2U)
#define MCST_ENDING_UNDEF2                   (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_CONT                           */
#define MCST_CONT_UNDEF                     (0U)
#define MCST_CONT_INS_FUECO                 (1U)
#define MCST_CONT_AVBL_RNG                  (2U)
#define MCST_CONT_AUDIO_STS                 (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_AR                             */
#define MCST_AR_OFF                         (0U)
#define MCST_AR_ON                          (1U)
#define MCST_AR_UNDEF1                      (2U)
#define MCST_AR_UNDEF2                      (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HUD_ST                         */
#define MCST_HUD_ST_UNDEF                   (0U)
#define MCST_HUD_ST_FULL                    (1U)
#define MCST_HUD_ST_STD                     (2U)
#define MCST_HUD_ST_MIN                     (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HUD                            */
#define MCST_HUD_OFF                        (0U)
#define MCST_HUD_ON                         (1U)
#define MCST_HUD_UNDEF1                     (2U)
#define MCST_HUD_UNDEF2                     (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HUD_ANALOG                     */
#define MCST_HUD_ANALOG_TACHOMET            (0U)
#define MCST_HUD_ANALOG_ECOIND              (1U)
#define MCST_HUD_ANALOG_HVIND               (2U)
#define MCST_HUD_ANALOG_FCIND               (3U)
#define MCST_HUD_ANALOG_POWER               (4U)
#define MCST_HUD_ANALOG_DMODE               (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HUDILL                         */
#define MCST_HUDILL_UNDEF1                  ( 0U)
#define MCST_HUDILL_BRIGHTNESS01            ( 1U)
#define MCST_HUDILL_BRIGHTNESS02            ( 2U)
#define MCST_HUDILL_BRIGHTNESS03            ( 3U)
#define MCST_HUDILL_BRIGHTNESS04            ( 4U)
#define MCST_HUDILL_BRIGHTNESS05            ( 5U)
#define MCST_HUDILL_BRIGHTNESS06            ( 6U)
#define MCST_HUDILL_BRIGHTNESS07            ( 7U)
#define MCST_HUDILL_BRIGHTNESS08            ( 8U)
#define MCST_HUDILL_BRIGHTNESS09            ( 9U)
#define MCST_HUDILL_BRIGHTNESS10            (10U)
#define MCST_HUDILL_BRIGHTNESS11            (11U)
#define MCST_HUDILL_BRIGHTNESS12            (12U)
#define MCST_HUDILL_BRIGHTNESS13            (13U)
#define MCST_HUDILL_BRIGHTNESS14            (14U)
#define MCST_HUDILL_BRIGHTNESS15            (15U)
#define MCST_HUDILL_BRIGHTNESS16            (16U)
#define MCST_HUDILL_BRIGHTNESS17            (17U)
#define MCST_HUDILL_BRIGHTNESS18            (18U)
#define MCST_HUDILL_BRIGHTNESS19            (19U)
#define MCST_HUDILL_BRIGHTNESS20            (20U)
#define MCST_HUDILL_BRIGHTNESS21            (21U)
#define MCST_HUDILL_BRIGHTNESS22            (22U)
#define MCST_HUDILL_BRIGHTNESS23            (23U)
#define MCST_HUDILL_BRIGHTNESS24            (24U)
#define MCST_HUDILL_BRIGHTNESS25            (25U)
#define MCST_HUDILL_BRIGHTNESS26            (26U)
#define MCST_HUDILL_BRIGHTNESS27            (27U)
#define MCST_HUDILL_BRIGHTNESS28            (28U)
#define MCST_HUDILL_BRIGHTNESS29            (29U)
#define MCST_HUDILL_BRIGHTNESS30            (30U)
#define MCST_HUDILL_BRIGHTNESS31            (31U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_HUD_ROT                        */
#define MCST_HUDROT_CW10                    (0x0AU)
#define MCST_HUDROT_CW9                     (0x09U)
#define MCST_HUDROT_CW8                     (0x08U)
#define MCST_HUDROT_CW7                     (0x07U)
#define MCST_HUDROT_CW6                     (0x06U)
#define MCST_HUDROT_CW5                     (0x05U)
#define MCST_HUDROT_CW4                     (0x04U)
#define MCST_HUDROT_CW3                     (0x03U)
#define MCST_HUDROT_CW2                     (0x02U)
#define MCST_HUDROT_CW1                     (0x01U)
#define MCST_HUDROT_NO_CORRECTION           (0x00U)
#define MCST_HUDROT_CCW1                    (0xFFU)
#define MCST_HUDROT_CCW2                    (0xFEU)
#define MCST_HUDROT_CCW3                    (0xFDU)
#define MCST_HUDROT_CCW4                    (0xFCU)
#define MCST_HUDROT_CCW5                    (0xFBU)
#define MCST_HUDROT_CCW6                    (0xFAU)
#define MCST_HUDROT_CCW7                    (0xF9U)
#define MCST_HUDROT_CCW8                    (0xF8U)
#define MCST_HUDROT_CCW9                    (0xF7U)
#define MCST_HUDROT_CCW10                   (0xF6U)

/* HUD Rotation Angle Limit                                                     */
#define MCST_HUDROT_CW_LMT                  (MCST_HUDROT_CW10 )
#define MCST_HUDROT_CCW_LMT                 (MCST_HUDROT_CCW10)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WDG_EYE0                       */
#define MCST_WDG_EYE0_OFF                    (0U)
#define MCST_WDG_EYE0_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WDG_EYE1                       */
#define MCST_WDG_EYE1_OFF                    (0U)
#define MCST_WDG_EYE1_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WDG_NAVI                       */
#define MCST_WDG_NAVI_OFF                    (0U)
#define MCST_WDG_NAVI_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WDG_ADAS                       */
#define MCST_WDG_ADAS_OFF                    (0U)
#define MCST_WDG_ADAS_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_WDG_ECO                        */
#define MCST_WDG_ECO_OFF                     (0U)
#define MCST_WDG_ECO_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_EYE0                      */
#define MCST_VIEW_EYE0_OFF                   (0U)
#define MCST_VIEW_EYE0_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_EYE01                     */
#define MCST_VIEW_EYE1_OFF                   (0U)
#define MCST_VIEW_EYE1_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_NAVI                      */
#define MCST_VIEW_NAVI_OFF                   (0U)
#define MCST_VIEW_NAVI_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_ADAS                      */
#define MCST_VIEW_ADAS_OFF                   (0U)
#define MCST_VIEW_ADAS_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_ECO                       */
#define MCST_VIEW_ECO_OFF                    (0U)
#define MCST_VIEW_ECO_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_TRACK                     */
#define MCST_VIEW_TRACK_OFF                  (0U)
#define MCST_VIEW_TRACK_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_SHIFT                     */
#define MCST_VIEW_SHIFT_OFF                  (0U)
#define MCST_VIEW_SHIFT_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_OFFROAD                   */
#define MCST_OFFROAD_EYE0_OFF                (0U)
#define MCST_OFFROAD_EYE0_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_VIEW_EYE6                      */
#define MCST_VIEW_EYE6_OFF                   (0U)
#define MCST_VIEW_EYE6_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_FU_ECO                    */
#define MCST_LEFT_FU_ECO_OFF                 (0U)
#define MCST_LEFT_FU_ECO_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_EL_ECO                    */
#define MCST_LEFT_EL_ECO_OFF                 (0U)
#define MCST_LEFT_EL_ECO_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_FU_ECO                    */
#define MCST_LEFT_FU_ECO_OFF                 (0U)
#define MCST_LEFT_FU_ECO_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_FU_ECO                    */
#define MCST_LEFT_FU_ECO_OFF                 (0U)
#define MCST_LEFT_FU_ECO_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_CONSUMP                   */
#define MCST_LEFT_CONSUMP_OFF                (0U)
#define MCST_LEFT_CONSUMP_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ECO_IND                   */
#define MCST_LEFT_ECO_IND_OFF                (0U)
#define MCST_LEFT_ECO_IND_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ECO_JDG                   */
#define MCST_LEFT_ECO_JDG_OFF                (0U)
#define MCST_LEFT_ECO_JDG_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_EV_RATIO                  */
#define MCST_LEFT_EV_RATIO_OFF               (0U)
#define MCST_LEFT_EV_RATIO_ON                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_NAVI                      */
#define MCST_LEFT_NAVI_OFF                   (0U)
#define MCST_LEFT_NAVI_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_AUDIO                     */
#define MCST_LEFT_AUDIO_OFF                  (0U)
#define MCST_LEFT_AUDIO_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_DRV_INFO                  */
#define MCST_LEFT_DRV_INFO_OFF               (0U)
#define MCST_LEFT_DRV_INFO_ON                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TRIP_A                    */
#define MCST_LEFT_TRIP_A_OFF                 (0U)
#define MCST_LEFT_TRIP_A_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TRIP_B                    */
#define MCST_LEFT_TRIP_B_OFF                 (0U)
#define MCST_LEFT_TRIP_B_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ENE_MON                   */
#define MCST_LEFT_ENE_MON_OFF                (0U)
#define MCST_LEFT_ENE_MON_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_4WD                       */
#define MCST_LEFT_4WD_OFF                    (0U)
#define MCST_LEFT_4WD_ON                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TRAC                      */
#define MCST_LEFT_TRAC_OFF                   (0U)
#define MCST_LEFT_TRAC_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ANGEL                     */
#define MCST_LEFT_ANGEL_OFF                  (0U)
#define MCST_LEFT_ANGEL_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_PITCH                     */
#define MCST_LEFT_PITCH_OFF                  (0U)
#define MCST_LEFT_PITCH_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TR_BRAKE                  */
#define MCST_LEFT_TR_BRAKE_OFF               (0U)
#define MCST_LEFT_TR_BRAKE_ON                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TR_BSM                    */
#define MCST_LEFT_TR_BSM_OFF                 (0U)
#define MCST_LEFT_TR_BSM_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_VOLT                      */
#define MCST_LEFT_VOLT_OFF                   (0U)
#define MCST_LEFT_VOLT_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_OIL_VOLT                  */
#define MCST_LEFT_OIL_VOLT_OFF               (0U)
#define MCST_LEFT_OIL_VOLT_ON                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ENG_AT                    */
#define MCST_LEFT_ENG_AT_OFF                 (0U)
#define MCST_LEFT_ENG_AT_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ENGINE                    */
#define MCST_LEFT_ENGINE_OFF                 (0U)
#define MCST_LEFT_ENGINE_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ENG_AT                    */
#define MCST_LEFT_ENG_AT_OFF                 (0U)
#define MCST_LEFT_ENG_AT_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_AT                        */
#define MCST_LEFT_AT_OFF                     (0U)
#define MCST_LEFT_AT_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TURBO                     */
#define MCST_LEFT_TURBO_OFF                  (0U)
#define MCST_LEFT_TURBO_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_BOOST                     */
#define MCST_LEFT_BOOST_OFF                  (0U)
#define MCST_LEFT_BOOST_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_MOTOR                     */
#define MCST_LEFT_MOTOR_OFF                  (0U)
#define MCST_LEFT_MOTOR_ON                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_SPORTS                    */
#define MCST_LEFT_SPORTS_OFF                 (0U)
#define MCST_LEFT_SPORTS_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_G_FORCE                   */
#define MCST_LEFT_G_FORCE_OFF                (0U)
#define MCST_LEFT_G_FORCE_ON                 (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_ADBLUE                    */
#define MCST_LEFT_ADBLUE_OFF                 (0U)
#define MCST_LEFT_ADBLUE_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_TPMS                      */
#define MCST_LEFT_TPMS_OFF                   (0U)
#define MCST_LEFT_TPMS_ON                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_LEFT_OILLVL                    */
#define MCST_LEFT_OILLVL_OFF                 (0U)
#define MCST_LEFT_OILLVL_ON                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_BUST_PK                        */
#define MCST_BUST_PK_OFF                     (0U)
#define MCST_BUST_PK_ON                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ELE_CO_GRH                     */
#define MCST_ELE_CO_GRH_AFT_STRT             (0U)
#define MCST_ELE_CO_GRH_AFT_RST              (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TRIP_A_UP                      */
#define MCST_TRIP_A_UP_AVG_SPD               (0U)
#define MCST_TRIP_A_UP_MIL                   (1U)
#define MCST_TRIP_A_UP_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TRIP_A_DN                      */
#define MCST_TRIP_A_DN_AVG_SPD               (0U)
#define MCST_TRIP_A_DN_MIL                   (1U)
#define MCST_TRIP_A_DN_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TRIP_B_UP                      */
#define MCST_TRIP_B_UP_AVG_SPD               (0U)
#define MCST_TRIP_B_UP_MIL                   (1U)
#define MCST_TRIP_B_UP_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TRIP_B_DN                      */
#define MCST_TRIP_B_DN_AVG_SPD               (0U)
#define MCST_TRIP_B_DN_MIL                   (1U)
#define MCST_TRIP_B_DN_DRV_TIM               (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_FUEL_CO_HIS                    */
#define MCST_FUEL_CO_HIS_1MIN                (0U)
#define MCST_FUEL_CO_HIS_TOTAL               (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_ELE_CO_HIS                     */
#define MCST_ELE_CO_HIS_1MIN                 (0U)
#define MCST_ELE_CO_HIS_TOTAL                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_VIEW                   */
#define MCST_DISP_VIEW_EYE0                  (0U)
#define MCST_DISP_VIEW_EYE1                  (1U)
#define MCST_DISP_VIEW_EYE2                  (2U)
#define MCST_DISP_VIEW_MAP                   (3U)
#define MCST_DISP_VIEW_ADAS                  (4U)
#define MCST_DISP_VIEW_ECO                   (5U)
#define MCST_DISP_VIEW_TRACK                 (6U)
#define MCST_DISP_VIEW_SHIFT                 (7U)
#define MCST_DISP_VIEW_OFFROAD               (8U)
#define MCST_DISP_VIEW_EYE6                  (9U)
#define MCST_DISP_VIEW_CHARGEMODE            (10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_EYE0                   */
#define MCST_DISP_EYE0_BLANK                 (0U)
#define MCST_DISP_EYE0_FUEL_CO               (1U)
#define MCST_DISP_EYE0_ELE_CO                (2U)
#define MCST_DISP_EYE0_FUEL_CO_PHV           (3U)
#define MCST_DISP_EYE0_ECO_BAR               (4U)
#define MCST_DISP_EYE0_ECOJDG                (5U)
#define MCST_DISP_EYE0_EV_RUN_RATE           (6U)
#define MCST_DISP_EYE0_NAVI                  (7U)
#define MCST_DISP_EYE0_AUDIO_STS             (8U)
#define MCST_DISP_EYE0_DRVINF                (9U)
#define MCST_DISP_EYE0_TRIP_A                (10U)
#define MCST_DISP_EYE0_TRIP_B                (11U)
#define MCST_DISP_EYE0_ENEMON                (12U)
#define MCST_DISP_EYE0_TPMS                  (13U)
#define MCST_DISP_EYE0_4WD                   (14U)
#define MCST_DISP_EYE0_TRACT                 (15U)
#define MCST_DISP_EYE0_STEER                 (16U)
#define MCST_DISP_EYE0_PITCH                 (17U)
#define MCST_DISP_EYE0_TRAILBRK              (18U)
#define MCST_DISP_EYE0_TRAILBSM              (19U)
#define MCST_DISP_EYE0_VOLT                  (20U)
#define MCST_DISP_EYE0_OILP_VOLT             (21U)
#define MCST_DISP_EYE0_ENGAT_TEMP            (22U)
#define MCST_DISP_EYE0_ENG_TEMP              (23U)
#define MCST_DISP_EYE0_AT_TEMP               (24U)
#define MCST_DISP_EYE0_TURBO                 (25U)
#define MCST_DISP_EYE0_BUST                  (26U)
#define MCST_DISP_EYE0_MOTOR                 (27U)
#define MCST_DISP_EYE0_SPORTS                (28U)
#define MCST_DISP_EYE0_GMON                  (29U)
#define MCST_DISP_EYE0_ADBLUE                (30U)
#define MCST_DISP_EYE0_HTANK                 (31U)
#define MCST_DISP_EYE0_SOH                   (32U)
#define MCST_DISP_EYE0_MSG                   (33U)
#define MCST_DISP_EYE0_SETTING               (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_EYE1                   */
#define MCST_DISP_EYE1_BLANK                 (0U)
#define MCST_DISP_EYE1_FUEL_CO               (1U)
#define MCST_DISP_EYE1_ELE_CO                (2U)
#define MCST_DISP_EYE1_FUEL_CO_PHV           (3U)
#define MCST_DISP_EYE1_ECO_BAR               (4U)
#define MCST_DISP_EYE1_ECOJDG                (5U)
#define MCST_DISP_EYE1_EV_RUN_RATE           (6U)
#define MCST_DISP_EYE1_NAVI                  (7U)
#define MCST_DISP_EYE1_AUDIO_STS             (8U)
#define MCST_DISP_EYE1_DRVINF                (9U)
#define MCST_DISP_EYE1_TRIP_A                (10U)
#define MCST_DISP_EYE1_TRIP_B                (11U)
#define MCST_DISP_EYE1_ENEMON                (12U)
#define MCST_DISP_EYE1_TPMS                  (13U)
#define MCST_DISP_EYE1_4WD                   (14U)
#define MCST_DISP_EYE1_TRACT                 (15U)
#define MCST_DISP_EYE1_STEER                 (16U)
#define MCST_DISP_EYE1_PITCH                 (17U)
#define MCST_DISP_EYE1_TRAILBRK              (18U)
#define MCST_DISP_EYE1_TRAILBSM              (19U)
#define MCST_DISP_EYE1_VOLT                  (20U)
#define MCST_DISP_EYE1_OILP_VOLT             (21U)
#define MCST_DISP_EYE1_ENGAT_TEMP            (22U)
#define MCST_DISP_EYE1_ENG_TEMP              (23U)
#define MCST_DISP_EYE1_AT_TEMP               (24U)
#define MCST_DISP_EYE1_TURBO                 (25U)
#define MCST_DISP_EYE1_BUST                  (26U)
#define MCST_DISP_EYE1_MOTOR                 (27U)
#define MCST_DISP_EYE1_SPORTS                (28U)
#define MCST_DISP_EYE1_GMON                  (29U)
#define MCST_DISP_EYE1_ADBLUE                (30U)
#define MCST_DISP_EYE1_HTANK                 (31U)
#define MCST_DISP_EYE1_SOH                   (32U)
#define MCST_DISP_EYE1_MSG                   (33U)
#define MCST_DISP_EYE1_SETTING               (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_EYE2                   */
#define MCST_DISP_EYE2_BLANK                 (0U)
#define MCST_DISP_EYE2_FUEL_CO               (1U)
#define MCST_DISP_EYE2_ELE_CO                (2U)
#define MCST_DISP_EYE2_FUEL_CO_PHV           (3U)
#define MCST_DISP_EYE2_ECO_BAR               (4U)
#define MCST_DISP_EYE2_ECOJDG                (5U)
#define MCST_DISP_EYE2_EV_RUN_RATE           (6U)
#define MCST_DISP_EYE2_NAVI                  (7U)
#define MCST_DISP_EYE2_AUDIO_STS             (8U)
#define MCST_DISP_EYE2_DRVINF                (9U)
#define MCST_DISP_EYE2_TRIP_A                (10U)
#define MCST_DISP_EYE2_TRIP_B                (11U)
#define MCST_DISP_EYE2_ENEMON                (12U)
#define MCST_DISP_EYE2_TPMS                  (13U)
#define MCST_DISP_EYE2_4WD                   (14U)
#define MCST_DISP_EYE2_TRACT                 (15U)
#define MCST_DISP_EYE2_STEER                 (16U)
#define MCST_DISP_EYE2_PITCH                 (17U)
#define MCST_DISP_EYE2_TRAILBRK              (18U)
#define MCST_DISP_EYE2_TRAILBSM              (19U)
#define MCST_DISP_EYE2_VOLT                  (20U)
#define MCST_DISP_EYE2_OILP_VOLT             (21U)
#define MCST_DISP_EYE2_ENGAT_TEMP            (22U)
#define MCST_DISP_EYE2_ENG_TEMP              (23U)
#define MCST_DISP_EYE2_AT_TEMP               (24U)
#define MCST_DISP_EYE2_TURBO                 (25U)
#define MCST_DISP_EYE2_BUST                  (26U)
#define MCST_DISP_EYE2_MOTOR                 (27U)
#define MCST_DISP_EYE2_SPORTS                (28U)
#define MCST_DISP_EYE2_GMON                  (29U)
#define MCST_DISP_EYE2_ADBLUE                (30U)
#define MCST_DISP_EYE2_HTANK                 (31U)
#define MCST_DISP_EYE2_SOH                   (32U)
#define MCST_DISP_EYE2_MSG                   (33U)
#define MCST_DISP_EYE2_SETTING               (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_MAP                    */
#define MCST_DISP_MAP_BLANK                  (0U)
#define MCST_DISP_MAP_FUEL_CO                (1U)
#define MCST_DISP_MAP_ELE_CO                 (2U)
#define MCST_DISP_MAP_FUEL_CO_PHV            (3U)
#define MCST_DISP_MAP_ECO_BAR                (4U)
#define MCST_DISP_MAP_ECOJDG                 (5U)
#define MCST_DISP_MAP_EV_RUN_RATE            (6U)
#define MCST_DISP_MAP_NAVI                   (7U)
#define MCST_DISP_MAP_AUDIO_STS              (8U)
#define MCST_DISP_MAP_DRVINF                 (9U)
#define MCST_DISP_MAP_TRIP_A                 (10U)
#define MCST_DISP_MAP_TRIP_B                 (11U)
#define MCST_DISP_MAP_ENEMON                 (12U)
#define MCST_DISP_MAP_TPMS                   (13U)
#define MCST_DISP_MAP_4WD                    (14U)
#define MCST_DISP_MAP_TRACT                  (15U)
#define MCST_DISP_MAP_STEER                  (16U)
#define MCST_DISP_MAP_PITCH                  (17U)
#define MCST_DISP_MAP_TRAILBRK               (18U)
#define MCST_DISP_MAP_TRAILBSM               (19U)
#define MCST_DISP_MAP_VOLT                   (20U)
#define MCST_DISP_MAP_OILP_VOLT              (21U)
#define MCST_DISP_MAP_ENGAT_TEMP             (22U)
#define MCST_DISP_MAP_ENG_TEMP               (23U)
#define MCST_DISP_MAP_AT_TEMP                (24U)
#define MCST_DISP_MAP_TURBO                  (25U)
#define MCST_DISP_MAP_BUST                   (26U)
#define MCST_DISP_MAP_MOTOR                  (27U)
#define MCST_DISP_MAP_SPORTS                 (28U)
#define MCST_DISP_MAP_GMON                   (29U)
#define MCST_DISP_MAP_ADBLUE                 (30U)
#define MCST_DISP_MAP_HTANK                  (31U)
#define MCST_DISP_MAP_SOH                    (32U)
#define MCST_DISP_MAP_MSG                    (33U)
#define MCST_DISP_MAP_SETTING                (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_ADAS                   */
#define MCST_DISP_ADAS_BLANK                 (0U)
#define MCST_DISP_ADAS_FUEL_CO               (1U)
#define MCST_DISP_ADAS_ELE_CO                (2U)
#define MCST_DISP_ADAS_FUEL_CO_PHV           (3U)
#define MCST_DISP_ADAS_ECO_BAR               (4U)
#define MCST_DISP_ADAS_ECOJDG                (5U)
#define MCST_DISP_ADAS_EV_RUN_RATE           (6U)
#define MCST_DISP_ADAS_NAVI                  (7U)
#define MCST_DISP_ADAS_AUDIO_STS             (8U)
#define MCST_DISP_ADAS_DRVINF                (9U)
#define MCST_DISP_ADAS_TRIP_A                (10U)
#define MCST_DISP_ADAS_TRIP_B                (11U)
#define MCST_DISP_ADAS_ENEMON                (12U)
#define MCST_DISP_ADAS_TPMS                  (13U)
#define MCST_DISP_ADAS_4WD                   (14U)
#define MCST_DISP_ADAS_TRACT                 (15U)
#define MCST_DISP_ADAS_STEER                 (16U)
#define MCST_DISP_ADAS_PITCH                 (17U)
#define MCST_DISP_ADAS_TRAILBRK              (18U)
#define MCST_DISP_ADAS_TRAILBSM              (19U)
#define MCST_DISP_ADAS_VOLT                  (20U)
#define MCST_DISP_ADAS_OILP_VOLT             (21U)
#define MCST_DISP_ADAS_ENGAT_TEMP            (22U)
#define MCST_DISP_ADAS_ENG_TEMP              (23U)
#define MCST_DISP_ADAS_AT_TEMP               (24U)
#define MCST_DISP_ADAS_TURBO                 (25U)
#define MCST_DISP_ADAS_BUST                  (26U)
#define MCST_DISP_ADAS_MOTOR                 (27U)
#define MCST_DISP_ADAS_SPORTS                (28U)
#define MCST_DISP_ADAS_GMON                  (29U)
#define MCST_DISP_ADAS_ADBLUE                (30U)
#define MCST_DISP_ADAS_HTANK                 (31U)
#define MCST_DISP_ADAS_SOH                   (32U)
#define MCST_DISP_ADAS_MSG                   (33U)
#define MCST_DISP_ADAS_SETTING               (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_ECO                    */
#define MCST_DISP_ECO_BLANK                  (0U)
#define MCST_DISP_ECO_FUEL_CO                (1U)
#define MCST_DISP_ECO_ELE_CO                 (2U)
#define MCST_DISP_ECO_FUEL_CO_PHV            (3U)
#define MCST_DISP_ECO_ECO_BAR                (4U)
#define MCST_DISP_ECO_ECOJDG                 (5U)
#define MCST_DISP_ECO_EV_RUN_RATE            (6U)
#define MCST_DISP_ECO_NAVI                   (7U)
#define MCST_DISP_ECO_AUDIO_STS              (8U)
#define MCST_DISP_ECO_DRVINF                 (9U)
#define MCST_DISP_ECO_TRIP_A                 (10U)
#define MCST_DISP_ECO_TRIP_B                 (11U)
#define MCST_DISP_ECO_ENEMON                 (12U)
#define MCST_DISP_ECO_TPMS                   (13U)
#define MCST_DISP_ECO_4WD                    (14U)
#define MCST_DISP_ECO_TRACT                  (15U)
#define MCST_DISP_ECO_STEER                  (16U)
#define MCST_DISP_ECO_PITCH                  (17U)
#define MCST_DISP_ECO_TRAILBRK               (18U)
#define MCST_DISP_ECO_TRAILBSM               (19U)
#define MCST_DISP_ECO_VOLT                   (20U)
#define MCST_DISP_ECO_OILP_VOLT              (21U)
#define MCST_DISP_ECO_ENGAT_TEMP             (22U)
#define MCST_DISP_ECO_ENG_TEMP               (23U)
#define MCST_DISP_ECO_AT_TEMP                (24U)
#define MCST_DISP_ECO_TURBO                  (25U)
#define MCST_DISP_ECO_BUST                   (26U)
#define MCST_DISP_ECO_MOTOR                  (27U)
#define MCST_DISP_ECO_SPORTS                 (28U)
#define MCST_DISP_ECO_GMON                   (29U)
#define MCST_DISP_ECO_ADBLUE                 (30U)
#define MCST_DISP_ECO_HTANK                  (31U)
#define MCST_DISP_ECO_SOH                    (32U)
#define MCST_DISP_ECO_MSG                    (33U)
#define MCST_DISP_ECO_SETTING                (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_TRACK                  */
#define MCST_DISP_TRACK_BLANK                (0U)
#define MCST_DISP_TRACK_FUEL_CO              (1U)
#define MCST_DISP_TRACK_ELE_CO               (2U)
#define MCST_DISP_TRACK_FUEL_CO_PHV          (3U)
#define MCST_DISP_TRACK_ECO_BAR              (4U)
#define MCST_DISP_TRACK_ECOJDG               (5U)
#define MCST_DISP_TRACK_EV_RUN_RATE          (6U)
#define MCST_DISP_TRACK_NAVI                 (7U)
#define MCST_DISP_TRACK_AUDIO_STS            (8U)
#define MCST_DISP_TRACK_DRVINF               (9U)
#define MCST_DISP_TRACK_TRIP_A               (10U)
#define MCST_DISP_TRACK_TRIP_B               (11U)
#define MCST_DISP_TRACK_ENEMON               (12U)
#define MCST_DISP_TRACK_TPMS                 (13U)
#define MCST_DISP_TRACK_4WD                  (14U)
#define MCST_DISP_TRACK_TRACT                (15U)
#define MCST_DISP_TRACK_STEER                (16U)
#define MCST_DISP_TRACK_PITCH                (17U)
#define MCST_DISP_TRACK_TRAILBRK             (18U)
#define MCST_DISP_TRACK_TRAILBSM             (19U)
#define MCST_DISP_TRACK_VOLT                 (20U)
#define MCST_DISP_TRACK_OILP_VOLT            (21U)
#define MCST_DISP_TRACK_ENGAT_TEMP           (22U)
#define MCST_DISP_TRACK_ENG_TEMP             (23U)
#define MCST_DISP_TRACK_AT_TEMP              (24U)
#define MCST_DISP_TRACK_TURBO                (25U)
#define MCST_DISP_TRACK_BUST                 (26U)
#define MCST_DISP_TRACK_MOTOR                (27U)
#define MCST_DISP_TRACK_SPORTS               (28U)
#define MCST_DISP_TRACK_GMON                 (29U)
#define MCST_DISP_TRACK_ADBLUE               (30U)
#define MCST_DISP_TRACK_HTANK                (31U)
#define MCST_DISP_TRACK_SOH                  (32U)
#define MCST_DISP_TRACK_MSG                  (33U)
#define MCST_DISP_TRACK_SETTING              (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_SHIFT                  */
#define MCST_DISP_SHIFT_BLANK                (0U)
#define MCST_DISP_SHIFT_FUEL_CO              (1U)
#define MCST_DISP_SHIFT_ELE_CO               (2U)
#define MCST_DISP_SHIFT_FUEL_CO_PHV          (3U)
#define MCST_DISP_SHIFT_ECO_BAR              (4U)
#define MCST_DISP_SHIFT_ECOJDG               (5U)
#define MCST_DISP_SHIFT_EV_RUN_RATE          (6U)
#define MCST_DISP_SHIFT_NAVI                 (7U)
#define MCST_DISP_SHIFT_AUDIO_STS            (8U)
#define MCST_DISP_SHIFT_DRVINF               (9U)
#define MCST_DISP_SHIFT_TRIP_A               (10U)
#define MCST_DISP_SHIFT_TRIP_B               (11U)
#define MCST_DISP_SHIFT_ENEMON               (12U)
#define MCST_DISP_SHIFT_TPMS                 (13U)
#define MCST_DISP_SHIFT_4WD                  (14U)
#define MCST_DISP_SHIFT_TRACT                (15U)
#define MCST_DISP_SHIFT_STEER                (16U)
#define MCST_DISP_SHIFT_PITCH                (17U)
#define MCST_DISP_SHIFT_TRAILBRK             (18U)
#define MCST_DISP_SHIFT_TRAILBSM             (19U)
#define MCST_DISP_SHIFT_VOLT                 (20U)
#define MCST_DISP_SHIFT_OILP_VOLT            (21U)
#define MCST_DISP_SHIFT_ENGAT_TEMP           (22U)
#define MCST_DISP_SHIFT_ENG_TEMP             (23U)
#define MCST_DISP_SHIFT_AT_TEMP              (24U)
#define MCST_DISP_SHIFT_TURBO                (25U)
#define MCST_DISP_SHIFT_BUST                 (26U)
#define MCST_DISP_SHIFT_MOTOR                (27U)
#define MCST_DISP_SHIFT_SPORTS               (28U)
#define MCST_DISP_SHIFT_GMON                 (29U)
#define MCST_DISP_SHIFT_ADBLUE               (30U)
#define MCST_DISP_SHIFT_HTANK                (31U)
#define MCST_DISP_SHIFT_SOH                  (32U)
#define MCST_DISP_SHIFT_MSG                  (33U)
#define MCST_DISP_SHIFT_SETTING              (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_OFFROAD                */
#define MCST_DISP_OFFROAD_BLANK              (0U)
#define MCST_DISP_OFFROAD_FUEL_CO            (1U)
#define MCST_DISP_OFFROAD_ELE_CO             (2U)
#define MCST_DISP_OFFROAD_FUEL_CO_PHV        (3U)
#define MCST_DISP_OFFROAD_ECO_BAR            (4U)
#define MCST_DISP_OFFROAD_ECOJDG             (5U)
#define MCST_DISP_OFFROAD_EV_RUN_RA          (6U)
#define MCST_DISP_OFFROAD_NAVI               (7U)
#define MCST_DISP_OFFROAD_AUDIO_ST           (8U)
#define MCST_DISP_OFFROAD_DRVINF             (9U)
#define MCST_DISP_OFFROAD_TRIP_A             (10U)
#define MCST_DISP_OFFROAD_TRIP_B             (11U)
#define MCST_DISP_OFFROAD_ENEMON             (12U)
#define MCST_DISP_OFFROAD_TPMS               (13U)
#define MCST_DISP_OFFROAD_4WD                (14U)
#define MCST_DISP_OFFROAD_TRACT              (15U)
#define MCST_DISP_OFFROAD_STEER              (16U)
#define MCST_DISP_OFFROAD_PITCH              (17U)
#define MCST_DISP_OFFROAD_TRAILBRK           (18U)
#define MCST_DISP_OFFROAD_TRAILBSM           (19U)
#define MCST_DISP_OFFROAD_VOLT               (20U)
#define MCST_DISP_OFFROAD_OILP_VOLT          (21U)
#define MCST_DISP_OFFROAD_ENGAT_TEMP         (22U)
#define MCST_DISP_OFFROAD_ENG_TEMP           (23U)
#define MCST_DISP_OFFROAD_AT_TEMP            (24U)
#define MCST_DISP_OFFROAD_TURBO              (25U)
#define MCST_DISP_OFFROAD_BUST               (26U)
#define MCST_DISP_OFFROAD_MOTOR              (27U)
#define MCST_DISP_OFFROAD_SPORTS             (28U)
#define MCST_DISP_OFFROAD_GMON               (29U)
#define MCST_DISP_OFFROAD_ADBLUE             (30U)
#define MCST_DISP_OFFROAD_HTANK              (31U)
#define MCST_DISP_OFFROAD_SOH                (32U)
#define MCST_DISP_OFFROAD_MSG                (33U)
#define MCST_DISP_OFFROAD_SETTING            (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_DISP_EYE6                   */
#define MCST_DISP_EYE6_BLANK                 (0U)
#define MCST_DISP_EYE6_FUEL_CO               (1U)
#define MCST_DISP_EYE6_ELE_CO                (2U)
#define MCST_DISP_EYE6_FUEL_CO_PHV           (3U)
#define MCST_DISP_EYE6_ECO_BAR               (4U)
#define MCST_DISP_EYE6_ECOJDG                (5U)
#define MCST_DISP_EYE6_EV_RUN_RATE           (6U)
#define MCST_DISP_EYE6_NAVI                  (7U)
#define MCST_DISP_EYE6_AUDIO_STS             (8U)
#define MCST_DISP_EYE6_DRVINF                (9U)
#define MCST_DISP_EYE6_TRIP_A                (10U)
#define MCST_DISP_EYE6_TRIP_B                (11U)
#define MCST_DISP_EYE6_ENEMON                (12U)
#define MCST_DISP_EYE6_TPMS                  (13U)
#define MCST_DISP_EYE6_4WD                   (14U)
#define MCST_DISP_EYE6_TRACT                 (15U)
#define MCST_DISP_EYE6_STEER                 (16U)
#define MCST_DISP_EYE6_PITCH                 (17U)
#define MCST_DISP_EYE6_TRAILBRK              (18U)
#define MCST_DISP_EYE6_TRAILBSM              (19U)
#define MCST_DISP_EYE6_VOLT                  (20U)
#define MCST_DISP_EYE6_OILP_VOLT             (21U)
#define MCST_DISP_EYE6_ENGAT_TEMP            (22U)
#define MCST_DISP_EYE6_ENG_TEMP              (23U)
#define MCST_DISP_EYE6_AT_TEMP               (24U)
#define MCST_DISP_EYE6_TURBO                 (25U)
#define MCST_DISP_EYE6_BUST                  (26U)
#define MCST_DISP_EYE6_MOTOR                 (27U)
#define MCST_DISP_EYE6_SPORTS                (28U)
#define MCST_DISP_EYE6_GMON                  (29U)
#define MCST_DISP_EYE6_ADBLUE                (30U)
#define MCST_DISP_EYE6_HTANK                 (31U)
#define MCST_DISP_EYE6_SOH                   (32U)
#define MCST_DISP_EYE6_MSG                   (33U)
#define MCST_DISP_EYE6_SETTING               (34U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_NAME_DRV1                      */
/* #define MCST_BFI_NAME_DRV2                      */
/* #define MCST_BFI_NAME_DRV3                      */
#define MCST_BFI_NAME_OFF                   (0U)
#define MCST_BFI_NAME_ON                    (1U)
#define MCST_BFI_NAME_UNDEF1                (2U)
#define MCST_BFI_NAME_UNDEF2                (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_BFI_TAST_FLG                       */
#define MCST_TAST_FLG_FLG8         (0x00000001U)           /* bit0:FLAG8     */
#define MCST_TAST_FLG_FLG7         (0x00000002U)           /* bit1:FLAG7     */
#define MCST_TAST_FLG_FLG6         (0x00000004U)           /* bit2:FLAG6     */
#define MCST_TAST_FLG_FLG5         (0x00000008U)           /* bit3:FLAG5     */
#define MCST_TAST_FLG_FLG4         (0x00000010U)           /* bit4:FLAG4     */
#define MCST_TAST_FLG_FLG3         (0x00000020U)           /* bit5:FLAG3     */
#define MCST_TAST_FLG_FLG2         (0x00000040U)           /* bit6:FLAG2     */
#define MCST_TAST_FLG_FLG1         (0x00000080U)           /* bit7:FLAG1     */

#define MCST_TAST_FLG_METALLIC     (MCST_TAST_FLG_FLG2)    /* bit6:FLAG2     */
#define MCST_TAST_FLG_CLASSIC      (MCST_TAST_FLG_FLG1)    /* bit7:FLAG1     */

#define MCST_TAST_FLG_UNDEF        (0x00000100U)           /* Undef(default) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define MCST_METWRNCSTM                       */
#define MCST_METWRNCSTM_NUM        ( 3U)
#define MCST_METWRNCSTM_MIN        ( 0U)
#define MCST_METWRNCSTM_MID        ( 1U)
#define MCST_METWRNCSTM_MAX        ( 2U)

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

#endif      /* MCST_BF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  mcst_cfg.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
