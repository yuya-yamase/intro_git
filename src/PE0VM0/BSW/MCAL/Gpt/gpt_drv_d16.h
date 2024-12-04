/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : Timer Array Unit D                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef GPT_DRV_D16_H
#define GPT_DRV_D16_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_DRV_D16_H_MAJOR                      (1)
#define GPT_DRV_D16_H_MINOR                      (0)
#define GPT_DRV_D16_H_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_d16_channel.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U2      u2_g_Gpt_D16GetTimeElapsed(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)                                                    */
/*  U2      u2_g_Gpt_D16GetTimeCaptured(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_TMELPSD_NUM_PARAM                (2U)
#define GPT_D16_TMELPSD_BASE                     (0U)
#define GPT_D16_TMELPSD_CRRNT                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_Gpt_D16Start(const U1 u1_a_D16_CH, const U2 * u2_ap_START)                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_START_NUM_CFG                    (2U)
#define GPT_D16_START_CTRL                       (0U)
#define GPT_D16_START_PERI                       (1U)

#define GPT_D16_START_CTRL_BIT_ELVL              (0x0003U)
#define GPT_D16_START_CTRL_ELVL_FA               (0x0000U)  /* Falling Edge                      */
#define GPT_D16_START_CTRL_ELVL_RI               (0x0001U)  /* Rising Edge                       */
#define GPT_D16_START_CTRL_ELVL_FA_RI            (0x0002U)  /* Both Edge    FA : Start, RI Stop  */
#define GPT_D16_START_CTRL_ELVL_RI_FA            (0x0003U)  /* Both Edge    RI : Start, FA Stop  */

#define GPT_D16_START_CTRL_BIT_IRQ_EN            (0x0010U)
#define GPT_D16_START_CTRL_BIT_IRQ_CL            (0x0020U)
#define GPT_D16_START_CTRL_BIT_TRG_ST            (0x0040U)

/* ------------------------------------------------------------------------------------- */
/*  Attention :                                                                          */
/* ------------------------------------------------------------------------------------- */
/*  If a timer is configured as interval timer and 0xffff expects to be set to           */
/*  compare clear threshold, GPT_D16_PERI_MAX shall be used and passed as 2nd parameter  */
/*  of vd_g_Gpt_D16Start.                                                                */
/* ------------------------------------------------------------------------------------- */
#define GPT_D16_PERI_MAX                         (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U1      u1_g_Gpt_D16IRQenabled(const U1 u1_a_D16_CH)                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_IRQEN_BIT_CMPR                   (0x01U)
#define GPT_D16_IRQEN_BIT_CNTE                   (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  U1      u1_g_Gpt_D16IRQst(const U1 u1_a_D16_CH, const U1 u1_a_W_CLR)                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_IRQST_BIT_IRQ                    (0x01U)
#define GPT_D16_IRQST_BIT_OVF                    (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  void    vd_g_Gpt_D16SyncStart(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                   */
/*  void    vd_g_Gpt_D16SyncStop(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                    */
/*  U1      u1_g_Gpt_D16SyncReload(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_SYNC_CHBIT_00                    (0x0001U)
#define GPT_D16_SYNC_CHBIT_01                    (0x0002U)
#define GPT_D16_SYNC_CHBIT_02                    (0x0004U)
#define GPT_D16_SYNC_CHBIT_03                    (0x0008U)
#define GPT_D16_SYNC_CHBIT_04                    (0x0010U)
#define GPT_D16_SYNC_CHBIT_05                    (0x0020U)
#define GPT_D16_SYNC_CHBIT_06                    (0x0040U)
#define GPT_D16_SYNC_CHBIT_07                    (0x0080U)
#define GPT_D16_SYNC_CHBIT_08                    (0x0100U)
#define GPT_D16_SYNC_CHBIT_09                    (0x0200U)
#define GPT_D16_SYNC_CHBIT_10                    (0x0400U)
#define GPT_D16_SYNC_CHBIT_11                    (0x0800U)
#define GPT_D16_SYNC_CHBIT_12                    (0x1000U)
#define GPT_D16_SYNC_CHBIT_13                    (0x2000U)
#define GPT_D16_SYNC_CHBIT_14                    (0x4000U)
#define GPT_D16_SYNC_CHBIT_15                    (0x8000U)

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
/* AUTOSAR v4 API                                                                */
/* void            Gpt_Init(const Gpt_ConfigType* ConfigPtr)                     */
/* void            Gpt_DeInit(void);                                             */
/* Gpt_ValueType   Gpt_GetTimeElapsed(Gpt_ChannelType Channel)                   */
/* Gpt_ValueType   Gpt_GetTimeRemaining(Gpt_ChannelType Channel)                 */
/* void            Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)  */
/* void            Gpt_StopTimer(Gpt_ChannelType Channel)                        */
/* void            Gpt_EnableNotification(Gpt_ChannelType Channel)               */
/* void            Gpt_DisableNotification(Gpt_ChannelType Channel)              */
/* void            Gpt_SetMode(Gpt_ModeType Mode)                                */
/* void            Gpt_DisableWakeup(Gpt_ChannelType Channel)                    */
/* void            Gpt_EnableWakeup(Gpt_ChannelType Channel)                     */
/* void            Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource)           */

void    vd_g_Gpt_D16Init(void);
void    vd_g_Gpt_D16DeInit(void);
U2      u2_g_Gpt_D16GetTimeElapsed(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp);
                                                                           /* if u2_ap_d16stamp == vdp_PTR_NA, return current stamp */
U2      u2_g_Gpt_D16GetTimeCaptured(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp);

void    vd_g_Gpt_D16Start(const U1 u1_a_D16_CH, const U2 * u2_ap_START);
void    vd_g_Gpt_D16Stop(const U1 u1_a_D16_CH);

void    vd_g_Gpt_D16SyncStart(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT);
void    vd_g_Gpt_D16SyncStop(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT);

U1      u1_g_Gpt_D16SyncReload(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT); /* Return : TRUE = Reloadble, FALSE=Not Reloadable */

void    vd_g_Gpt_D16EI(const U1 u1_a_D16_CH);
void    vd_g_Gpt_D16DI(const U1 u1_a_D16_CH);

U1      u1_g_Gpt_D16IRQst(const U1 u1_a_D16_CH, const U1 u1_a_W_CLR);            /* Return and u1_a_W_CLR : GPT_D16_IRQST_BIT_XXX   */
U1      u1_g_Gpt_D16IRQenabled(const U1 u1_a_D16_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* GPT_DRV_D16_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see gpt_drv_d16.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
