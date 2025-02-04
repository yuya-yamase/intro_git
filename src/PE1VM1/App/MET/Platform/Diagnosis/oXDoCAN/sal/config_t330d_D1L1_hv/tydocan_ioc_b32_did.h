/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN I/O Control / Request Message Bitfield Max 32 Bits                                                                       */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  tydocan_ioc_b32_did.h is included in tydocan_ioc_b32.h                                                                           */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*===================================================================================================================================*/

#ifndef TYDOCAN_IOC_B32_DID_H
#define TYDOCAN_IOC_B32_DID_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_IOC_B32_DID_H_MAJOR              (2)
#define TYDOCAN_IOC_B32_DID_H_MINOR              (0)
#define TYDOCAN_IOC_B32_DID_H_PATCH              (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------------------------------------------- */
/* WARNING :                                                                                                              */
/* ---------------------------------------------------------------------------------------------------------------------- */
/* Following #defines are refered by lib/xid/tydocan_met_did_xxx.                                                         */
/*                                                                                                                        */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                                         */
/*                                                                                                                        */
#define TYDC_IOC_B32_2801                        (0U)         /*  Gauge          : Vehicle Speed                          */
#define TYDC_IOC_B32_2802                        (1U)         /*  Gauge          : Engine Speed                           */
#define TYDC_IOC_B32_2803                        (2U)         /*  Gauge          : Fuel                                   */
#define TYDC_IOC_B32_2804                        (3U)         /*  Gauge          : Sub Fuel                               */
#define TYDC_IOC_B32_2805                        (4U)         /*  Gauge          : Power-train System Coolant Temperature */
#define TYDC_IOC_B32_2806                        (5U)         /*  Gauge          : Battery Voltage                        */
#define TYDC_IOC_B32_2807                        (6U)         /*  Gauge          : Oil Pressure                           */
#define TYDC_IOC_B32_2808                        (7U)         /*  Gauge          : Hybrid System Indicator                */
#define TYDC_IOC_B32_2809                        (8U)         /*  Gauge          : State of Charge                        */
#define TYDC_IOC_B32_280A                        (9U)         /*  Gauge          : Compressed Natural Gas                 */
/* #define TYDC_IOC_B32_280B                                      HUD            : Brightness                             */
/* #define TYDC_IOC_B32_280C                                      HUD            : Position                               */
#define TYDC_IOC_B32_2821                        (10U)        /*  Buzzer/Speaker : 0.8kHz VR H                            */
#define TYDC_IOC_B32_2822                        (11U)        /*  Buzzer/Speaker : 0.8kHz NR H                            */
#define TYDC_IOC_B32_2823                        (12U)        /*  Buzzer/Speaker : 0.8kHz VR L                            */
#define TYDC_IOC_B32_2824                        (13U)        /*  Buzzer/Speaker : 0.8kHz NR L                            */
#define TYDC_IOC_B32_2825                        (14U)        /*  Buzzer/Speaker : 1.6kHz NR L                            */
#define TYDC_IOC_B32_2826                        (15U)        /*  Buzzer/Speaker : 2.0kHz NR L                            */
#define TYDC_IOC_B32_2827                        (16U)        /*  Buzzer/Speaker : 2.4kHz NR L                            */
#define TYDC_IOC_B32_2829                        (17U)        /*  Speaker        : Sound File                             */
#define TYDC_IOC_B32_2831                        (18U)        /*  Display        : Multi-Information                      */
#define TYDC_IOC_B32_2832                        (19U)        /*  Display        : Segment LCD                            */
#define TYDC_IOC_B32_2901                        (20U)        /*  Telltale       : Main                                   */
#define TYDC_IOC_B32_2911                        (21U)        /*  Telltale       : Body #1                                */
#define TYDC_IOC_B32_2912                        (22U)        /*  Telltale       : Body #2                                */
#define TYDC_IOC_B32_2921                        (23U)        /*  Telltale       : Power-train #1                         */
#define TYDC_IOC_B32_2922                        (24U)        /*  Telltale       : Power-train #2                         */
#define TYDC_IOC_B32_2931                        (25U)        /*  Telltale       : Drive-train #1                         */
#define TYDC_IOC_B32_2932                        (26U)        /*  Telltale       : Drive-train #2                         */
#define TYDC_IOC_B32_2933                        (27U)        /*  Telltale       : Drive-train #3                         */
#define TYDC_IOC_B32_2941                        (28U)        /*  Telltale       : Chassis #1                             */
#define TYDC_IOC_B32_2942                        (29U)        /*  Telltale       : Chassis #2                             */
#define TYDC_IOC_B32_2943                        (30U)        /*  Telltale       : Chassis #3                             */
#define TYDC_IOC_B32_2951                        (31U)        /*  Telltale       : Driving Assist #1                      */
#define TYDC_IOC_B32_2952                        (32U)        /*  Telltale       : Driving Assist #2                      */
#define TYDC_IOC_B32_2961                        (33U)        /*  Telltale       : xEV #1                                 */
/* #define TYDC_IOC_B32_2971                                      Telltale       : Multi-Media #1                         */
#define TYDC_IOC_B32_2981                        (34U)        /*  Telltale       : Misc #1                                */
#define TYDC_IOC_B32_2A01                        (35U)        /*  Input Signal   : Vehicle Speed                          */
#define TYDC_IOC_B32_2A21                        (36U)        /*  User Button    : Misc                                   */
#define TYDC_IOC_B32_2A22                        (37U)        /*  User Button    : Steering                               */
#define TYDC_IOC_B32_2B01                        (38U)        /*  Display        : Hud                                    */
/*                                                                                                                        */
/* Above #defines are refered by lib/xid/tydocan_met_did_xxx.                                                             */
/*                                                                                                                        */
/* If #defines are modified, lib_ipc_tycan_xxx.a shall be recompiled and rebuilt.                                         */
/* ---------------------------------------------------------------------------------------------------------------------- */

#define TYDC_IOC_B32_NUM_DID                     (39U)

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

#endif /* TYDOCAN_IOC_B32_DID_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tydocan_ioc_b32_cfg.c                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
