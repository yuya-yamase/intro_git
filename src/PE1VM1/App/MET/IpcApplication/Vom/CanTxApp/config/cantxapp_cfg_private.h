/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Can Tx Application                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef CANTXAPP_CFG_PRIVATE_H
#define CANTXAPP_CFG_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CANTXAPP_CFG_PRIVATE_H_MAJOR                 (0)
#define CANTXAPP_CFG_PRIVATE_H_MINOR                 (0)
#define CANTXAPP_CFG_PRIVATE_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CANTXAPP_NBYTE_PAYLOAD2                      (2U)
#define CANTXAPP_NBYTE_PAYLOAD8                      (8U)

#define CANTXAPP_POS_1_0                             (0U)
#define CANTXAPP_POS_1_1                             (1U)
#define CANTXAPP_POS_1_2                             (2U)
#define CANTXAPP_POS_1_3                             (3U)
#define CANTXAPP_POS_1_4                             (4U)
#define CANTXAPP_POS_1_5                             (5U)
#define CANTXAPP_POS_1_6                             (6U)
#define CANTXAPP_POS_1_7                             (7U)
#define CANTXAPP_POS_2_0                             (8U)
#define CANTXAPP_POS_2_1                             (9U)
#define CANTXAPP_POS_2_2                             (10U)
#define CANTXAPP_POS_2_3                             (11U)
#define CANTXAPP_POS_2_4                             (12U)
#define CANTXAPP_POS_2_5                             (13U)
#define CANTXAPP_POS_2_6                             (14U)
#define CANTXAPP_POS_2_7                             (15U)
#define CANTXAPP_POS_3_0                             (16U)
#define CANTXAPP_POS_3_1                             (17U)
#define CANTXAPP_POS_3_2                             (18U)
#define CANTXAPP_POS_3_3                             (19U)
#define CANTXAPP_POS_3_4                             (20U)
#define CANTXAPP_POS_3_5                             (21U)
#define CANTXAPP_POS_3_6                             (22U)
#define CANTXAPP_POS_3_7                             (23U)
#define CANTXAPP_POS_4_0                             (24U)
#define CANTXAPP_POS_4_1                             (25U)
#define CANTXAPP_POS_4_2                             (26U)
#define CANTXAPP_POS_4_3                             (27U)
#define CANTXAPP_POS_4_4                             (28U)
#define CANTXAPP_POS_4_5                             (29U)
#define CANTXAPP_POS_4_6                             (30U)
#define CANTXAPP_POS_4_7                             (31U)
#define CANTXAPP_POS_5_0                             (0U)
#define CANTXAPP_POS_5_1                             (1U)
#define CANTXAPP_POS_5_2                             (2U)
#define CANTXAPP_POS_5_3                             (3U)
#define CANTXAPP_POS_5_4                             (4U)
#define CANTXAPP_POS_5_5                             (5U)
#define CANTXAPP_POS_5_6                             (6U)
#define CANTXAPP_POS_5_7                             (7U)
#define CANTXAPP_POS_6_0                             (8U)
#define CANTXAPP_POS_6_1                             (9U)
#define CANTXAPP_POS_6_2                             (10U)
#define CANTXAPP_POS_6_3                             (11U)
#define CANTXAPP_POS_6_4                             (12U)
#define CANTXAPP_POS_6_5                             (13U)
#define CANTXAPP_POS_6_6                             (14U)
#define CANTXAPP_POS_6_7                             (15U)
#define CANTXAPP_POS_7_0                             (16U)
#define CANTXAPP_POS_7_1                             (17U)
#define CANTXAPP_POS_7_2                             (18U)
#define CANTXAPP_POS_7_3                             (19U)
#define CANTXAPP_POS_7_4                             (20U)
#define CANTXAPP_POS_7_5                             (21U)
#define CANTXAPP_POS_7_6                             (22U)
#define CANTXAPP_POS_7_7                             (23U)
#define CANTXAPP_POS_8_0                             (24U)
#define CANTXAPP_POS_8_1                             (25U)
#define CANTXAPP_POS_8_2                             (26U)
#define CANTXAPP_POS_8_3                             (27U)
#define CANTXAPP_POS_8_4                             (28U)
#define CANTXAPP_POS_8_5                             (29U)
#define CANTXAPP_POS_8_6                             (30U)
#define CANTXAPP_POS_8_7                             (31U)
#define CANTXAPP_POS_9_1                             (1U)
#define CANTXAPP_POS_11_6                            (22U)
#define CANTXAPP_POS_16_4                            (28U)
#define CANTXAPP_POS_17_1                            (1U)
#define CANTXAPP_POS_20_5                            (29U)
#define CANTXAPP_POS_21_5                            (5U)
#define CANTXAPP_POS_24_4                            (28U)

#define CANTXAPP_LEN_1                               (1U)
#define CANTXAPP_LEN_2                               (2U)
#define CANTXAPP_LEN_3                               (3U)
#define CANTXAPP_LEN_4                               (4U)
#define CANTXAPP_LEN_5                               (5U)
#define CANTXAPP_LEN_6                               (6U)
#define CANTXAPP_LEN_7                               (7U)
#define CANTXAPP_LEN_8                               (8U)

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
void    vd_g_CanTxAppMET1S02_Init(void);
void    vd_g_CanTxAppMET1S27_Init(void);
void    vd_g_CanTxAppMET1S29_Init(void);
void    vd_g_CanTxAppMET1S30_Init(void);
void    vd_g_CanTxAppMET1S62_Init(void);
void    vd_g_CanTxAppMET1S70_Init(void);

void    vd_g_CanTxAppMET1S02_Send(void);
void    vd_g_CanTxAppMET1S27_Send(void);
void    vd_g_CanTxAppMET1S29_Send(void);
void    vd_g_CanTxAppMET1S30_Send(void);
void    vd_g_CanTxAppMET1S62_Send(void);
void    vd_g_CanTxAppMET1S70_Send(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* CANTXAPP_CFG_PRIVATE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  cantxapp_cfg.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
