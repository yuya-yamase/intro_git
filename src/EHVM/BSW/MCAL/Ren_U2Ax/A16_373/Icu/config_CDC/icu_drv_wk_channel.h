/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : Input Caputure Wakeup Factor Detection                                                                       */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  icu_drv_wk_channel.h is included in icu_drv_wk.h.                                                                                */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef ICU_DRV_WK_CHANNEL_H
#define ICU_DRV_WK_CHANNEL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_DRV_WK_CHANNEL_H_MAJOR               (1)
#define ICU_DRV_WK_CHANNEL_H_MINOR               (1)
#define ICU_DRV_WK_CHANNEL_H_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_WK_NUM_CFG                           (3U)
#define ICU_WK_CFG_MCU_STA_BY_RST                (0U) /* reserved by BSW. don't delete */
#define ICU_WK_CFG_MCU_STA_BY_WK                 (1U) /* reserved by BSW. don't delete */
#define ICU_WK_CFG_PREP_MCU_TO_LPM               (2U) /* reserved by BSW. don't delete */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_WK_CH_TNMI                           (0U)
#define ICU_WK_CH_INTWDTBA                       (5U)
#define ICU_WK_CH_INTP0                          (6U)
#define ICU_WK_CH_INTP1                          (7U)
#define ICU_WK_CH_INTP2                          (8U)
#define ICU_WK_CH_INTP3                          (9U)
#define ICU_WK_CH_INTP4                          (10U)
#define ICU_WK_CH_INTP5                          (11U)
#define ICU_WK_CH_INTP6                          (12U)
#define ICU_WK_CH_INTP7                          (13U)
#define ICU_WK_CH_INTP8                          (14U)
#define ICU_WK_CH_INTP9                          (15U)
#define ICU_WK_CH_INTP10                         (16U)
#define ICU_WK_CH_INTP11                         (17U)
#define ICU_WK_CH_INTP12                         (18U)
#define ICU_WK_CH_INTP13                         (19U)
#define ICU_WK_CH_INTP14                         (20U)
#define ICU_WK_CH_INTP15                         (21U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define ICU_WK_GR_A1 (1U) */
#define ICU_WK_CH_INTP16                         (32U)
#define ICU_WK_CH_INTP17                         (33U)
#define ICU_WK_CH_INTP18                         (34U)
#define ICU_WK_CH_INTP19                         (35U)
#define ICU_WK_CH_INTP20                         (36U)
#define ICU_WK_CH_INTP21                         (37U)
#define ICU_WK_CH_INTP22                         (38U)
#define ICU_WK_CH_INTP23                         (39U)
#define ICU_WK_CH_INTP24                         (40U)
#define ICU_WK_CH_INTP25                         (41U)
#define ICU_WK_CH_INTP26                         (42U)
#define ICU_WK_CH_INTP27                         (43U)
#define ICU_WK_CH_INTP28                         (44U)
#define ICU_WK_CH_INTP29                         (45U)
#define ICU_WK_CH_INTP30                         (46U)
#define ICU_WK_CH_INTP31                         (47U)
#define ICU_WK_CH_INTP32                         (48U)
#define ICU_WK_CH_INTP33                         (49U)
#define ICU_WK_CH_INTP34                         (50U)
#define ICU_WK_CH_INTP35                         (51U)
#define ICU_WK_CH_INTP36                         (52U)
#define ICU_WK_CH_INTP37                         (53U)
#define ICU_WK_CH_INTP38                         (54U)
#define ICU_WK_CH_INTP39                         (55U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define ICU_WK_GR_A2 (2U) */
#define ICU_WK_CH_WUTRG0                         (64U)
#define ICU_WK_CH_WUTRG1                         (65U)
#define ICU_WK_CH_INTDCUTDI                      (66U)
#define ICU_WK_CH_INTTAUJ2I0                     (67U)
#define ICU_WK_CH_INTTAUJ2I1                     (68U)
#define ICU_WK_CH_INTTAUJ2I2                     (69U)
#define ICU_WK_CH_INTTAUJ2I3                     (70U)
#define ICU_WK_CH_INTTAUJ3I0                     (71U)
#define ICU_WK_CH_INTTAUJ3I1                     (72U)
#define ICU_WK_CH_INTTAUJ3I2                     (73U)
#define ICU_WK_CH_INTTAUJ3I3                     (74U)
#define ICU_WK_CH_INTRTCA01S                     (75U)
#define ICU_WK_CH_INTRTCA0AL                     (76U)
#define ICU_WK_CH_INTRTCA0R                      (77U)
#define ICU_WK_CH_INTADCJ2I0                     (78U)
#define ICU_WK_CH_INTADCJ2I1                     (79U)
#define ICU_WK_CH_INTADCJ2I2                     (80U)
#define ICU_WK_CH_INTADCJ2I3                     (81U)
#define ICU_WK_CH_INTADCJ2I4                     (82U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define ICU_WK_GR_A0 (0U) */
#define ICU_WK_WRQ_TNMI                          (0x00000001U)
#define ICU_WK_WRQ_INTWDTBA                      (0x00000020U)
#define ICU_WK_WRQ_INTP0                         (0x00000040U)
#define ICU_WK_WRQ_INTP1                         (0x00000080U)
#define ICU_WK_WRQ_INTP2                         (0x00000100U)
#define ICU_WK_WRQ_INTP3                         (0x00000200U)
#define ICU_WK_WRQ_INTP4                         (0x00000400U)
#define ICU_WK_WRQ_INTP5                         (0x00000800U)
#define ICU_WK_WRQ_INTP6                         (0x00001000U)
#define ICU_WK_WRQ_INTP7                         (0x00002000U)
#define ICU_WK_WRQ_INTP8                         (0x00004000U)
#define ICU_WK_WRQ_INTP9                         (0x00008000U)
#define ICU_WK_WRQ_INTP10                        (0x00010000U)
#define ICU_WK_WRQ_INTP11                        (0x00020000U)
#define ICU_WK_WRQ_INTP12                        (0x00040000U)
#define ICU_WK_WRQ_INTP13                        (0x00080000U)
#define ICU_WK_WRQ_INTP14                        (0x00100000U)
#define ICU_WK_WRQ_INTP15                        (0x00200000U)
#define ICU_WK_WRQ_GR_A0                         (0x003FFFE1U)

#define ICU_WK_WRQ_INTP16                        (0x00000001U)
#define ICU_WK_WRQ_INTP17                        (0x00000002U)
#define ICU_WK_WRQ_INTP18                        (0x00000004U)
#define ICU_WK_WRQ_INTP19                        (0x00000008U)
#define ICU_WK_WRQ_INTP20                        (0x00000010U)
#define ICU_WK_WRQ_INTP21                        (0x00000020U)
#define ICU_WK_WRQ_INTP22                        (0x00000040U)
#define ICU_WK_WRQ_INTP23                        (0x00000080U)
#define ICU_WK_WRQ_INTP24                        (0x00000100U)
#define ICU_WK_WRQ_INTP25                        (0x00000200U)
#define ICU_WK_WRQ_INTP26                        (0x00000400U)
#define ICU_WK_WRQ_INTP27                        (0x00000800U)
#define ICU_WK_WRQ_INTP28                        (0x00001000U)
#define ICU_WK_WRQ_INTP29                        (0x00002000U)
#define ICU_WK_WRQ_INTP30                        (0x00004000U)
#define ICU_WK_WRQ_INTP31                        (0x00008000U)
#define ICU_WK_WRQ_INTP32                        (0x00010000U)
#define ICU_WK_WRQ_INTP33                        (0x00020000U)
#define ICU_WK_WRQ_INTP34                        (0x00040000U)
#define ICU_WK_WRQ_INTP35                        (0x00080000U)
#define ICU_WK_WRQ_INTP36                        (0x00100000U)
#define ICU_WK_WRQ_INTP37                        (0x00200000U)
#define ICU_WK_WRQ_INTP38                        (0x00400000U)
#define ICU_WK_WRQ_INTP39                        (0x00800000U)
#define ICU_WK_WRQ_GR_A1                         (0x00FFFFFFU)

#define ICU_WK_WRQ_WUTRG0                        (0x00000001U)
#define ICU_WK_WRQ_WUTRG1                        (0x00000002U)
#define ICU_WK_WRQ_INTDCUTDI                     (0x00000004U)
#define ICU_WK_WRQ_INTTAUJ2I0                    (0x00000008U)
#define ICU_WK_WRQ_INTTAUJ2I1                    (0x00000010U)
#define ICU_WK_WRQ_INTTAUJ2I2                    (0x00000020U)
#define ICU_WK_WRQ_INTTAUJ2I3                    (0x00000040U)
#define ICU_WK_WRQ_INTTAUJ3I0                    (0x00000080U)
#define ICU_WK_WRQ_INTTAUJ3I1                    (0x00000100U)
#define ICU_WK_WRQ_INTTAUJ3I2                    (0x00000200U)
#define ICU_WK_WRQ_INTTAUJ3I3                    (0x00000400U)
#define ICU_WK_WRQ_INTRTCA01S                    (0x00000800U)
#define ICU_WK_WRQ_INTRTCA0AL                    (0x00001000U)
#define ICU_WK_WRQ_INTRTCA0R                     (0x00002000U)
#define ICU_WK_WRQ_INTADCJ2I0                    (0x00004000U)
#define ICU_WK_WRQ_INTADCJ2I1                    (0x00008000U)
#define ICU_WK_WRQ_INTADCJ2I2                    (0x00010000U)
#define ICU_WK_WRQ_INTADCJ2I3                    (0x00020000U)
#define ICU_WK_WRQ_INTADCJ2I4                    (0x00040000U)
#define ICU_WK_WRQ_GR_A2                         (0x0007FFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_WK_WRQ_HWI_WK                        (0x00000500U)  /* /BU_DET : INTP_4, BOOT : INTP_2  */
#define ICU_WK_WRQ_CAN_VEH                       (0x00000a00U)  /* CAN5: INTP_5, CAN3: INTP_3 */

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

#endif  /* ICU_DRV_WK_CHANNEL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see icu_drv_wk_cfg.c                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

