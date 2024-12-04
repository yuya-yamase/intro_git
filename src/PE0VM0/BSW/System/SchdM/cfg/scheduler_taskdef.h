/* 2.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Scheduler                                                                                                                        */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  scheduler_taskdef.h is included in scheduler.h.                                                                                  */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef SCHDLR_TASKDEF_H
#define SCHDLR_TASKDEF_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_TASKDEF_H_MAJOR (3)
#define SCHDLR_TASKDEF_H_MINOR (0)
#define SCHDLR_TASKDEF_H_PATCH (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SCHDLR_TASKBIT___5MS                     (0x00000002U)                        /*   5 ms   task flag       */
#define SCHDLR_TASKBIT__10MS_A                   (0x00000004U)                        /*  10 ms A task flag       */
#define SCHDLR_TASKBIT__10MS_B                   (0x00000008U)                        /*  10 ms B task flag       */
#define SCHDLR_TASKBIT__20MS_A                   (0x00000010U)                        /*  20 ms A task flag       */
#define SCHDLR_TASKBIT__20MS_B                   (0x00000020U)                        /*  20 ms B task flag       */
#define SCHDLR_TASKBIT__50MS_A                   (0x00000040U)                        /*  50 ms A task flag       */
#define SCHDLR_TASKBIT__50MS_B                   (0x00000080U)                        /*  50 ms B task flag       */
#define SCHDLR_TASKBIT__50MS_C                   (0x00000100U)                        /*  50 ms C task flag       */
#define SCHDLR_TASKBIT__50MS_D                   (0x00000200U)                        /*  50 ms D task flag       */
#define SCHDLR_TASKBIT__50MS_E                   (0x00000400U)                        /*  50 ms E task flag       */
#define SCHDLR_TASKBIT_100MS_A                   (0x00000800U)                        /* 100 ms A task flag       */
#define SCHDLR_TASKBIT_100MS_B                   (0x00001000U)                        /* 100 ms B task flag       */
#define SCHDLR_TASKBIT_100MS_C                   (0x00002000U)                        /* 100 ms C task flag       */
#define SCHDLR_TASKBIT_100MS_D                   (0x00004000U)                        /* 100 ms D task flag       */
#define SCHDLR_TASKBIT_100MS_E                   (0x00008000U)                        /* 100 ms E task flag       */
#define SCHDLR_TASKBIT_100MS_F                   (0x00010000U)                        /* 100 ms F task flag       */
#define SCHDLR_TASKBIT_100MS_G                   (0x00020000U)                        /* 100 ms G task flag       */
#define SCHDLR_TASKBIT_100MS_H                   (0x00040000U)                        /* 100 ms H task flag       */
#define SCHDLR_TASKBIT_100MS_I                   (0x00080000U)                        /* 100 ms I task flag       */
#define SCHDLR_TASKBIT_100MS_J                   (0x00100000U)                        /* 100 ms J task flag       */

// 上位 16ビットがtick周期に対する分周比。
// 下位 16ビットがオフセット(tick周期 LSB)
#define SCHDLR_TASKBIT___5MS_CAL   (0x00010000U) /*   5 ms   task flag       */

#define SCHDLR_TASKBIT__10MS_A_CAL (0x00020000U) /*  10 ms A task flag       */
#define SCHDLR_TASKBIT__10MS_B_CAL (0x00020001U) /*  10 ms B task flag       */

#define SCHDLR_TASKBIT__20MS_A_CAL (0x00040000U) /*  20 ms A task flag       */
#define SCHDLR_TASKBIT__20MS_B_CAL (0x00040002U) /*  20 ms B task flag       */

#define SCHDLR_TASKBIT__50MS_A_CAL (0x000A0000U) /*  50 ms A task flag       */
#define SCHDLR_TASKBIT__50MS_B_CAL (0x000A0002U) /*  50 ms B task flag       */
#define SCHDLR_TASKBIT__50MS_C_CAL (0x000A0004U) /*  50 ms C task flag       */
#define SCHDLR_TASKBIT__50MS_D_CAL (0x000A0006U) /*  50 ms D task flag       */
#define SCHDLR_TASKBIT__50MS_E_CAL (0x000A0008U) /*  50 ms E task flag       */

#define SCHDLR_TASKBIT_100MS_A_CAL (0x00140000U) /* 100 ms A task flag       */
#define SCHDLR_TASKBIT_100MS_B_CAL (0x00140002U) /* 100 ms B task flag       */
#define SCHDLR_TASKBIT_100MS_C_CAL (0x00140004U) /* 100 ms C task flag       */
#define SCHDLR_TASKBIT_100MS_D_CAL (0x00140006U) /* 100 ms D task flag       */
#define SCHDLR_TASKBIT_100MS_E_CAL (0x00140008U) /* 100 ms E task flag       */
#define SCHDLR_TASKBIT_100MS_F_CAL (0x0014000AU) /* 100 ms F task flag       */
#define SCHDLR_TASKBIT_100MS_G_CAL (0x0014000CU) /* 100 ms G task flag       */
#define SCHDLR_TASKBIT_100MS_H_CAL (0x0014000EU) /* 100 ms H task flag       */
#define SCHDLR_TASKBIT_100MS_I_CAL (0x00140010U) /* 100 ms I task flag       */
#define SCHDLR_TASKBIT_100MS_J_CAL (0x00140012U) /* 100 ms J task flag       */

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

#endif /* #ifndef SCHDLR_TASKDEF_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see scheduler_cfg.c                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
