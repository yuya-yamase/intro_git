/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  DENSO ICT1 Coding Style Standard Template                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef HMIMCST_H
#define HMIMCST_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMCST_H_MAJOR                         (2)
#define HMIMCST_H_MINOR                         (4)
#define HMIMCST_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mcst_bf.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIMCST_ID_NUM                          (34U)

/*  Ether communication signal                                                                            */
#define HMIMCST_L_TACHO_SW                      ( 0U)       /*  0:Tachometer setting                      */
#define HMIMCST_L_REV_IND_A                     ( 1U)       /*  1:REV indicator                           */
#define HMIMCST_L_RV_PK_A                       ( 2U)       /*  2:REV peak                                */
#define HMIMCST_L_REV_SET_A                     ( 3U)       /*  3:REV setting                             */
#define HMIMCST_L_STSWLHCSTM1_UP                ( 4U)       /*  4:Left  STSW assignment (Top)             */
#define HMIMCST_L_STSWLHCSTM2_DOWN              ( 5U)       /*  5:Left  STSW assignment (Down)            */
#define HMIMCST_L_STSWLHCSTM3_LEFT              ( 6U)       /*  6:Left  STSW assignment (Left)            */
#define HMIMCST_L_STSWLHCSTM4_RIGHT             ( 7U)       /*  7:Left  STSW assignment (Right)           */
#define HMIMCST_L_STSWRHCSTM1_UP                ( 8U)       /*  8:right STSW assignment (Top)             */
#define HMIMCST_L_STSWRHCSTM2_DOWN              ( 9U)       /*  9:right STSW assignment (Down)            */
#define HMIMCST_L_STSWRHCSTM3_LEFT              (10U)       /* 10:right STSW assignment (Left)            */
#define HMIMCST_L_STSWRHCSTM4_RIGHT             (11U)       /* 11:right STSW assignment (Right)           */
#define HMIMCST_L_STSWRH_A                      (12U)       /* 12:Preset group (Right STSW)               */
#define HMIMCST_L_STSWLH_A                      (13U)       /* 13:Preset group (Left STSW)                */
#define HMIMCST_L_CONT_C                        (14U)       /* 14:Display switching                       */
#define HMIMCST_L_AR_SW                         (15U)       /* 15:AR ON/OFF                               */
#define HMIMCST_L_HUD_SW                        (16U)       /* 16:HUD display setting (MM)                */
#define HMIMCST_L_HUD_SC_SW                     (17U)       /* 17:HUD display setting (MM)                */
#define HMIMCST_L_HUD_MSW                       (18U)       /* 18:HUD ON/OFF (MM)                         */
#define HMIMCST_L_HUDRTCW                       (19U)       /* 19:HUD rotation CW                         */
#define HMIMCST_L_HUDRTCCW                      (20U)       /* 20:HUD rotation CCW                        */
#define HMIMCST_L_GRV_SW                        (21U)       /* 21:Sensitivity setting                     */
#define HMIMCST_L_MET_TYP_C                     (22U)       /* 22:Meter Type                              */
#define HMIMCST_L_ECO_IND_A                     (23U)       /* 23:ECO indicator                           */
#define HMIMCST_L_EV_IND_A                      (24U)       /* 24:EV  indicator                           */
#define HMIMCST_L_RESET_M                       (25U)       /* 25:Customize Reset                         */
/*  Signal other than Ether communication                                                                 */
#define HMIMCST_STSW_HUD                        (26U)       /* 26:HUD ON/OFF (STSW)                       */
#define HMIMCST_STSW_HUDMODE                    (27U)       /* 27:HUD display setting (STSW)              */
#define HMIMCST_GV_SYS_HW_ERR                   (28U)       /* 28:HUD Hardware Erron                      */
#define HMIMCST_GVIF_LINKDOWN                   (29U)       /* 29:HUD LinkDown                            */
#define HMIMCST_CSTM_HUDRTCW                    (30U)       /* 30:HUD ON/OFF (CSTMZ)                      */
#define HMIMCST_CSTM_HUDRTCCW                   (31U)       /* 31:HUD ON/OFF (CSTMZ)                      */
#define HMIMCST_CSTM_DIMSW                      (32U)       /* 32:Dimmer SW (CSTMZ)                       */
#define HMIMCST_L_MET_TST_C                     (33U)       /* 33:MET DESIGN (MM)                         */

/* Number of User Name Data Array                                                                         */
#define HMIMCST_USER_DTA_NUM                    (16U)
/* Number of Nickname Data Array                                                                          */
#define HMIMCST_NICKNAME_U4_DTA_NUM             ( 5U)
#define HMIMCST_NICKNAME_U2_DTA_NUM             (10U)

/* MET-M_MWVCUS-CSTD-                                                                                     */
#define HMIMCST_MWVC_OPE_INIT                   (7U)
#define HMIMCST_MWVC_OPE_MAX                    (2U)
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
void    vd_g_HmiMcstInit(void);
void    vd_g_HmiMcstMainTask(void);
void    vd_g_HmiMcstPut(const U1 u1_a_ID, const U1 u1_a_SIG);
void    vd_g_HmiCstmPut(const U4 * u4_ap_PDU_RX);
void    vd_g_HmiTftcnttsPut(const U4 * u4_ap_PDU_RX);
void    vd_g_HmiMcstUser1Put(const U4 *u4_ap_REQ);
void    vd_g_HmiMcstUser2Put(const U4 *u4_ap_REQ);
void    vd_g_HmiMcstUser3Put(const U4 *u4_ap_REQ);
void    vd_g_HmiMcstMMUserPut(const U2 * u2_ap_USRDAT,const U1 u1_a_SYNCID, const U1 u1_a_USRNUM);
void    vd_g_HmiMcstNickname1Put(const U4 *u4_ap_REQ);
void    vd_g_HmiMcstNickname2Put(const U4 *u4_ap_REQ);
void    vd_g_HmiMcstNickname3Put(const U4 *u4_ap_REQ);
#if ((defined(MCST_CSTMLST_SUPPORT)) && (MCST_CSTMLST_SUPPORT == 1))
#else
U1      u1_g_HmiMcstELSENS(void);
#endif
U1      u1_g_HmiMcstJdgHUDFail(const U1 u1_a_NOW);
void    vd_g_HmiMcstRefHook(void);
#if ((defined(MCST_PHASE2_SUPPORT)) && (MCST_PHASE2_SUPPORT == 1))
#else
void    vd_g_HmiTrlCstmPut(U4 * u4_ap_PDU_TX);
void    vd_g_HmiTrlCstmSet(const U4 * u4_ap_PDU_RX);
#endif
U1      u1_g_HmiMcstGetMWVCOpe(void);
U1      u1_g_HmiMcstGetChargeMode(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* HMIMCST_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  hmimcst.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
