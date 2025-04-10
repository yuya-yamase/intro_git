/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / Digital Input Logger                                                                         */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  tydocan_dil_channel.h is included in tydocan_dil.h                                                                               */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*===================================================================================================================================*/

#ifndef TYDOCAN_DIL_CHANNEL_H
#define TYDOCAN_DIL_CHANNEL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DIL_CHANNEL_H_MAJOR              (1)
#define TYDOCAN_DIL_CHANNEL_H_MINOR              (0)
#define TYDOCAN_DIL_CHANNEL_H_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------- */
/* WARNING :                                                                                                   */
/* ----------------------------------------------------------------------------------------------------------- */
/* Following #defines are refered by lib/xid/tydocan_met_did_xxx.                                              */
/*                                                                                                             */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                              */
/*                                                                                                             */
#define TYDC_DIL_TX_1001                         (0U)        /* reserved by lib_ipc_tycan_xxx.a                */
#define TYDC_DIL_TX_1002                         (1U)        /* reserved by lib_ipc_tycan_xxx.a                */
#define TYDC_DIL_TX_10A5                         (2U)        /* reserved by lib_ipc_tycan_xxx.a                */
#define TYDC_DIL_TX_1101                         (3U)        /* reserved by lib_ipc_tycan_xxx.a                */
#define TYDC_DIL_TX_1201                         (4U)        /* reserved by lib_ipc_tycan_xxx.a                */
#define TYDC_DIL_TX_1401                         (5U)        /* reserved by lib_ipc_tycan_xxx.a                */
/*                                                                                                             */
/* Above #defines are refered by lib/xid/tydocan_met_did_xxx.                                                  */
/*                                                                                                             */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                              */
/* ----------------------------------------------------------------------------------------------------------- */
    
#define TYDC_DIL_NUM_TX                          (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Group 0 / NvM       */
/* Group 1 / Backup-RAM */
#define TYDC_DIL_CH_OT_SEL                       (0U)        /*  0 : Odo/Trip Selection                        */
#define TYDC_DIL_CH_OT_RES                       (1U)        /*  1 : Odo/Trip Reset                            */
#define TYDC_DIL_CH_MI_SEL                       (2U)        /*  2 : Multi-Info. Selection                     */
#define TYDC_DIL_CH_TAI_CN                       (3U)        /*  3 : Tail Cancel                               */
#define TYDC_DIL_CH_DIM_UP                       (4U)        /*  4 : Dimming Up (1input type or 2input type)   */
#define TYDC_DIL_CH_DIM_DW                       (5U)        /*  5 : Dimming Down (1input type)                */
#define TYDC_DIL_CH_DIM_2IN_DW                   (6U)        /*  6 : Dimming Down (2input type)                */
#define TYDC_DIL_CH_TIM_PLU                      (7U)        /*  7 : Time Adjust/Plus                          */
#define TYDC_DIL_CH_TIM_MIN                      (8U)        /*  8 : Time Adjust/Minus                         */
#define TYDC_DIL_CH_TIM_SYN                      (9U)        /*  9 : Time Adjust/Reset                         */
#define TYDC_DIL_CH_TIM_1B                       (10U)       /* 10 : Time Adjust/1 Button                      */
#define TYDC_DIL_CH_STE_L0_UP                    (11U)       /* 11 : Steering Button Layout 0/Up               */
#define TYDC_DIL_CH_STE_L0_DW                    (12U)       /* 12 : Steering Button Layout 0/Down             */
#define TYDC_DIL_CH_STE_L0_LE                    (13U)       /* 13 : Steering Button Layout 0/Left             */
#define TYDC_DIL_CH_STE_L0_RI                    (14U)       /* 14 : Steering Button Layout 0/Right            */
#define TYDC_DIL_CH_STE_L0_EN                    (15U)       /* 15 : Steering Button Layout 0/Enter            */
#define TYDC_DIL_CH_STE_L0_BA                    (16U)       /* 16 : Steering Button Layout 0/Back             */
#define TYDC_DIL_CH_STE_L0_TO                    (17U)       /* 17 : Steering Button Layout 0/Top              */
#define TYDC_DIL_CH_BLT_BK_D                     (18U)       /* 18 : Seatbelt Buckle/Driver                    */
#define TYDC_DIL_CH_BLT_BK_P                     (19U)       /* 19 : Seatbelt Buckle/Passenger                 */
#define TYDC_DIL_CH_SEA_P                        (20U)       /* 20 : Seat-On/Passenger                         */
#define TYDC_DIL_CH_BLT_P                        (21U)       /* 21 : Seatbelt Buckle & Seat-On/Passenger       */
#define TYDC_DIL_CH_BLT_2ND_R                    (22U)       /* 22 : Seatbelt Buckle & Seat-On/2nd Rear Right  */
#define TYDC_DIL_CH_BLT_2ND_L                    (23U)       /* 23 : Seatbelt Buckle & Seat-On/2nd Rear Left   */
#define TYDC_DIL_CH_BLT_2ND_C                    (24U)       /* 24 : Seatbelt Buckle & Seat-On/2nd Rear Center */
#define TYDC_DIL_CH_BLT_3RD_R                    (25U)       /* 25 : Seatbelt Buckle & Seat-On/3rd Rear Right  */
#define TYDC_DIL_CH_BLT_3RD_L                    (26U)       /* 26 : Seatbelt Buckle & Seat-On/3rd Rear Left   */
#define TYDC_DIL_CH_BLT_3RD_C                    (27U)       /* 27 : Seatbelt Buckle & Seat-On/3rd Rear Center */
#define TYDC_DIL_CH_TURN_L                       (28U)       /* 28 : Turn Left                                 */
#define TYDC_DIL_CH_TURN_R                       (29U)       /* 29 : Turn Right                                */
#define TYDC_DIL_CH_FLA_CR                       (30U)       /* 30 : Flasher CR                                */
#define TYDC_DIL_CH_HAZ                          (31U)       /* 31 : Hazard                                    */

/* Group 2 / Backup-RAM */
#define TYDC_DIL_CH_OIL_PR                       (32U)       /* 32 : Oil Pressure                              */
#define TYDC_DIL_CH_OIL_LV                       (33U)       /* 33 : Oil Level                                 */
#define TYDC_DIL_CH_FU_SED                       (34U)       /* 34 : Fuel Sedimentor/Diesel                    */
#define TYDC_DIL_CH_FU_FIL                       (35U)       /* 35 : Fuel Filter/Diesel                        */
#define TYDC_DIL_CH_PARK                         (36U)       /* 36 : Pack                                      */
#define TYDC_DIL_CH_BRK_VA                       (37U)       /* 37 : Bake Vacuum                               */
#define TYDC_DIL_CH_STR_HEAT                     (38U)       /* 38 : Steering Heater                           */
#define TYDC_DIL_CH_BRK_PAD                      (39U)       /* 39 : Brake Pad                                 */
#define TYDC_DIL_CH_BLT_4TH_R                    (40U)       /* 40 : Seatbelt Buckle & Seat-On/4th Rear Right  */
#define TYDC_DIL_CH_BLT_4TH_L                    (41U)       /* 41 : Seatbelt Buckle & Seat-On/4th Rear Left   */
#define TYDC_DIL_CH_BLT_4TH_C                    (42U)       /* 42 : Seatbelt Buckle & Seat-On/4th Rear Center */
#define TYDC_DIL_CH_BLT_BK_C                     (43U)       /* 43 : Seatbelt Buckle/Center                    */
#define TYDC_DIL_CH_SEA_C                        (44U)       /* 44 : Seat-On/Center                            */
#define TYDC_DIL_CH_BLT_C                        (45U)       /* 45 : Seatbelt Buckle & Seat-On/Center          */
#define TYDC_DIL_CH_FLO_SW                       (46U)       /* 46 : Fuel Lid Opner SW                         */
#define TYDC_DIL_CH_HUD_SW                       (47U)       /* 47 : HUD MainSW Status                         */

#define TYDC_DIL_CH_STE_L1_MD                    (48U)       /* 48 : Steering Button Layout 1/Mode             */
#define TYDC_DIL_CH_STE_L1_SE                    (49U)       /* 49 : Steering Button Layout 1/Seek             */
#define TYDC_DIL_CH_STE_L1_EN                    (50U)       /* 50 : Steering Button Layout 1/Enter            */
#define TYDC_DIL_CH_STE_L1_AS                    (51U)       /* 51 : Steering Button Layout 1/Asl              */
#define TYDC_DIL_CH_STE_L1_RI                    (52U)       /* 52 : Steering Button Layout 1/Right            */
#define TYDC_DIL_CH_STE_L1_LD                    (53U)       /* 53 : Steering Button Layout 1/LDA              */
#define TYDC_DIL_CH_STE_L1_MA                    (54U)       /* 54 : Steering Button Layout 1/Main             */
#define TYDC_DIL_CH_STOP_SW                      (55U)       /* 55 : Stop SW Status                            */


#define TYDC_DIL_NUM_CH                          (56U)
#define TYDC_DIL_NUM_GR                          (2U)
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

#endif      /* TYDOCAN_DIL_CHANNEL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tydocan_dil_cfg.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
