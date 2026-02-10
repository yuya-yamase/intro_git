/* 3.0.0 */
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
#define MCST_BF_H_MAJOR                          (3)
#define MCST_BF_H_MINOR                          (0)
#define MCST_BF_H_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "locale.h"

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
/* Number of Personal Areas */
#define MCST_NUM_WORD_PERSONAL                   (8U)
/* Number of NVM Personal Areas */
#define MCST_NUM_NVM_PERSONAL                    (2U)

#define MCST_NUM_WORD                            (MCST_NUM_WORD_PERSONAL*4U)    /* 32U */
#define MCST_NUM_NVM                             (MCST_NUM_NVM_PERSONAL*4U)     /*  8U */

/* Offset is added to this area */
#define MCST_NUM_WORD_USER                       (MCST_NUM_WORD_PERSONAL)
/* Start position offset */
#define MCST_BF_OFFSET_GUEST                     (0U)                                                   /*  0U */
#define MCST_BF_OFFSET_USER1                     (MCST_BF_OFFSET_GUEST + MCST_NUM_WORD_PERSONAL)        /*  8U */
#define MCST_BF_OFFSET_USER2                     (MCST_BF_OFFSET_USER1 + MCST_NUM_WORD_PERSONAL)        /* 16U */
#define MCST_BF_OFFSET_USER3                     (MCST_BF_OFFSET_USER2 + MCST_NUM_WORD_PERSONAL)        /* 24U */
/* Area start position */
#define MCST_BF_OFFSET_GUEST_INI                 (0U)                                                   /*  0U */
#define MCST_BF_OFFSET_USER1_INI                 (MCST_NUM_WORD_PERSONAL)                               /*  8U */
#define MCST_BF_OFFSET_USER2_INI                 (MCST_BF_OFFSET_USER1_INI + MCST_NUM_WORD_PERSONAL)    /* 16U */
#define MCST_BF_OFFSET_USER3_INI                 (MCST_BF_OFFSET_USER2_INI + MCST_NUM_WORD_PERSONAL)    /* 24U */
/* Area end position */
#define MCST_BF_OFFSET_GUEST_MAX                 (MCST_BF_OFFSET_GUEST_INI + MCST_NUM_WORD_PERSONAL)    /*  8U */
#define MCST_BF_OFFSET_USER1_MAX                 (MCST_BF_OFFSET_USER1_INI + MCST_NUM_WORD_PERSONAL)    /* 16U */
#define MCST_BF_OFFSET_USER2_MAX                 (MCST_BF_OFFSET_USER2_INI + MCST_NUM_WORD_PERSONAL)    /* 24U */
#define MCST_BF_OFFSET_USER3_MAX                 (MCST_BF_OFFSET_USER3_INI + MCST_NUM_WORD_PERSONAL)    /* 32U */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_NUM_BF                              (10U)

#define MCST_BFI_SPEED                           (0U)            /* Unit Speed                               */
#define MCST_BFI_DIST                            (1U)            /* Unit Distance                            */
#define MCST_BFI_ELECO                           (2U)            /* Unit Electronic Economy                  */
#define MCST_BFI_TIMEFMT                         (3U)            /* Time Format 12h                          */
#define MCST_BFI_RHEO_DAY                        (4U)            /* Day   Brightness                         */
#define MCST_BFI_RHEO_NIGHT                      (5U)            /* Night Brightness                         */
#define MCST_BFI_METWRNCSTM                      (6U)            /* Volume of Meter Warning (M_MWVCUS-)      */
#define MCST_BFI_HUD                             (7U)            /* HUD ON/OFF                               */
#define MCST_BFI_HUDILL                          (8U)            /* HUD Brightness                           */
#define MCST_BFI_HUD_ROT                         (9U)            /* HUD Rotation                             */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_SUP_SPEED                           (TRUE)
#define MCST_SUP_DIST                            (TRUE)
#define MCST_SUP_ELECO                           (TRUE)
#define MCST_SUP_TIMEFMT                         (TRUE)
#define MCST_SUP_RHEO_DAY                        (TRUE)
#define MCST_SUP_RHEO_NIGHT                      (TRUE)
#define MCST_SUP_METWRNCSTM                      (TRUE)
#define MCST_SUP_HUD                             (TRUE)
#define MCST_SUP_HUDILL                          (TRUE)
#define MCST_SUP_HUD_ROT                         (TRUE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_INI_SPEED                             (0x00000003U)
#define MCST_INI_DIST                              (0x00000003U)
#define MCST_INI_ELECO                             (0x00000007U)
#define MCST_INI_TIMEFMT                           (0x00000003U)
#define MCST_INI_RHEO_DAY                          (0x00000015U)
#define MCST_INI_RHEO_NIGHT                        (0x0000001FU)
#define MCST_INI_METWRNCSTM                        (0x00000001U)
#define MCST_INI_HUD                               (0x00000003U)
#define MCST_INI_HUDILL                            (0x00000007U)
#define MCST_INI_HUD_ROT                           (0x00000000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_SPEED */
#define MCST_SPEED_KMPH                        (UNIT_VAL_SPEED_KMPH)
#define MCST_SPEED_MPH                         (UNIT_VAL_SPEED_MPH )
#define MCST_SPEED_UNDEF1                      (2U)
#define MCST_SPEED_UNDEF2                      (3U)
#define MCST_SPEED_MAX                         (MCST_SPEED_MPH)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_DIST */
#define MCST_DIST_KM                           (UNIT_VAL_DIST_KM  )
#define MCST_DIST_MILE                         (UNIT_VAL_DIST_MILE)
#define MCST_DIST_UNDEF1                       (2U)
#define MCST_DIST_UNDEF2                       (3U)
#define MCST_DIST_MAX                          (MCST_DIST_MILE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_ELECO */
#define MCST_ELECO_WHPKM                       (UNIT_VAL_ELECO_WHPKM    )
#define MCST_ELECO_KWHPKM                      (UNIT_VAL_ELECO_KWHPKM   )
#define MCST_ELECO_WHPMILE                     (UNIT_VAL_ELECO_WHPMILE  )
#define MCST_ELECO_KWHPMILE                    (UNIT_VAL_ELECO_KWHPMILE )
#define MCST_ELECO_KMPKWH                      (UNIT_VAL_ELECO_KMPKWH   )
#define MCST_ELECO_KWHP100KM                   (UNIT_VAL_ELECO_KWHP100KM)
#define MCST_ELECO_MILEPKWH                    (UNIT_VAL_ELECO_MILEPKWH )
#define MCST_ELECO_UNDEF1                      (7U)
#define MCST_ELECO_MAX                         (MCST_ELECO_MILEPKWH)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_RHEO_DAY */
#define MCST_RHEO_DAY_STEP_MIN_HOLD            (0U)
#define MCST_RHEO_DAY_STEP_01                  (1U)
#define MCST_RHEO_DAY_STEP_02                  (2U)
#define MCST_RHEO_DAY_STEP_03                  (3U)
#define MCST_RHEO_DAY_STEP_04                  (4U)
#define MCST_RHEO_DAY_STEP_05                  (5U)
#define MCST_RHEO_DAY_STEP_06                  (6U)
#define MCST_RHEO_DAY_STEP_07                  (7U)
#define MCST_RHEO_DAY_STEP_08                  (8U)
#define MCST_RHEO_DAY_STEP_09                  (9U)
#define MCST_RHEO_DAY_STEP_10                  (10U)
#define MCST_RHEO_DAY_STEP_11                  (11U)
#define MCST_RHEO_DAY_STEP_12                  (12U)
#define MCST_RHEO_DAY_STEP_13                  (13U)
#define MCST_RHEO_DAY_STEP_14                  (14U)
#define MCST_RHEO_DAY_STEP_15                  (15U)
#define MCST_RHEO_DAY_STEP_16                  (16U)
#define MCST_RHEO_DAY_STEP_17                  (17U)
#define MCST_RHEO_DAY_STEP_18                  (18U)
#define MCST_RHEO_DAY_STEP_19                  (19U)
#define MCST_RHEO_DAY_STEP_20                  (20U)
#define MCST_RHEO_DAY_STEP_MAX_HOLD            (21U)

#define MCST_RHEO_DAY_MAX                      (MCST_RHEO_DAY_STEP_MAX_HOLD)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_RHEO_NIGHT */
#define MCST_RHEO_NIGHT_STEP_MIN_HOLD          (0U)
#define MCST_RHEO_NIGHT_STEP_01                (1U)
#define MCST_RHEO_NIGHT_STEP_02                (2U)
#define MCST_RHEO_NIGHT_STEP_03                (3U)
#define MCST_RHEO_NIGHT_STEP_04                (4U)
#define MCST_RHEO_NIGHT_STEP_05                (5U)
#define MCST_RHEO_NIGHT_STEP_06                (6U)
#define MCST_RHEO_NIGHT_STEP_07                (7U)
#define MCST_RHEO_NIGHT_STEP_08                (8U)
#define MCST_RHEO_NIGHT_STEP_09                (9U)
#define MCST_RHEO_NIGHT_STEP_10                (10U)
#define MCST_RHEO_NIGHT_STEP_11                (11U)
#define MCST_RHEO_NIGHT_STEP_12                (12U)
#define MCST_RHEO_NIGHT_STEP_13                (13U)
#define MCST_RHEO_NIGHT_STEP_14                (14U)
#define MCST_RHEO_NIGHT_STEP_15                (15U)
#define MCST_RHEO_NIGHT_STEP_16                (16U)
#define MCST_RHEO_NIGHT_STEP_17                (17U)
#define MCST_RHEO_NIGHT_STEP_18                (18U)
#define MCST_RHEO_NIGHT_STEP_19                (19U)
#define MCST_RHEO_NIGHT_STEP_20                (20U)
#define MCST_RHEO_NIGHT_STEP_MAX_HOLD          (21U)

#define MCST_RHEO_NIGHT_MAX                    (MCST_RHEO_NIGHT_STEP_MAX_HOLD)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_TIMEFMT */
#define MCST_TIMEFMT_24H                       (TIMEFMT_VAL_24H)
#define MCST_TIMEFMT_12H                       (TIMEFMT_VAL_12H)
#define MCST_TIMEFMT_UNDEF1                    (2U)
#define MCST_TIMEFMT_UNDEF2                    (3U)
#define MCST_TIMEFMT_MAX                       (MCST_TIMEFMT_12H)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_HUD */
#define MCST_HUD_OFF                           (0U)
#define MCST_HUD_ON                            (1U)
#define MCST_HUD_UNDEF1                        (2U)
#define MCST_HUD_UNDEF2                        (3U)
#define MCST_HUD_MAX                           (MCST_HUD_ON)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_HUDILL */
#define MCST_HUDILL_UNDEF1                     (0U)
#define MCST_HUDILL_BRIGHTNESS01               (1U)
#define MCST_HUDILL_BRIGHTNESS02               (2U)
#define MCST_HUDILL_BRIGHTNESS03               (3U)
#define MCST_HUDILL_BRIGHTNESS04               (4U)
#define MCST_HUDILL_BRIGHTNESS05               (5U)
#define MCST_HUDILL_BRIGHTNESS06               (6U)
#define MCST_HUDILL_BRIGHTNESS07               (7U)
#define MCST_HUDILL_BRIGHTNESS08               (8U)
#define MCST_HUDILL_BRIGHTNESS09               (9U)
#define MCST_HUDILL_BRIGHTNESS10               (10U)
#define MCST_HUDILL_BRIGHTNESS11               (11U)

#define MCST_HUDILL_MAX                        (MCST_HUDILL_BRIGHTNESS11)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_HUD_ROT */
#define MCST_HUDROT_NO_CORRECTION              (0x00U)

#define MCST_HUDROT_CW_LMT                     (0x7FU)
#define MCST_HUDROT_CCW_LMT                    (0x81U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MCST_BFI_METWRNCSTM */
#define MCST_METWRNCSTM_VOL_NUM                (3U)
#define MCST_METWRNCSTM_VOL_MIN                (0U)
#define MCST_METWRNCSTM_VOL_MID                (1U)
#define MCST_METWRNCSTM_VOL_MAX                (2U)

#define MCST_METWRNCSTM_MAX                    (MCST_METWRNCSTM_VOL_MAX)

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
