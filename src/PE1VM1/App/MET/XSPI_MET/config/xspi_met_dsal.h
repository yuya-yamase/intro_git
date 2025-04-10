/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI / Diag Service Application Layer                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef XSPI_DSAL_H
#define XSPI_DSAL_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSAL_H_MAJOR                    (1)
#define XSPI_DSAL_H_MINOR                    (1)
#define XSPI_DSAL_H_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DTC_NUM_RX                      (3U)
#define XSPI_DTC_RX_B1510                    (0U)               /* GVIF/HUD->MET                                          */
#define XSPI_DTC_RX_B1328                    (1U)               /* Ether/ADS                                              */
#define XSPI_DTC_RX_B1511                    (2U)               /* GVIF/MET->HUD                                          */



#define XSPI_DTC_RX_FAI                      (0x01U)
#define XSPI_DTC_RX_RUN                      (0x02U)
#define XSPI_DTC_RX_ENA                      (0x04U)
#define XSPI_DTC_RX_UNK                      (0x08U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSR_NUM_CH                      (11U)
#define XSPI_DSR_2F_MID                      (0U)               /* SID 0x2F / DID 0x2831                                  */
#define XSPI_DSR_2F_HUD                      (1U)               /* SID 0x2F / DID 0x2B01                                  */
#define XSPI_DSR_BA_TFT                      (2U)               /* SID 0xBA / ECU Shipping Inspection / Segment Check     */
#define XSPI_DSR_31_ROB                      (3U)               /* SID 0x31 / RID 0x1004                                  */
#define XSPI_DSR_31_ESO                      (4U)               /* SID 0x31 / RID 0x11FF                                  */
#define XSPI_DSR_BA_LED                      (5U)               /* SID 0xBA / ECU Shipping Inspection / TFT Backlight LED */
#define XSPI_DSR_BA_ETH                      (6U)               /* SID 0xBA / ECU Shipping Inspection / Ether-Phy Reg R/W */
#define XSPI_DSR_BA_NVM                      (7U)               /* SID 0xBA / ECU Shipping Inspection / NvM Reset         */
#define XSPI_DSR_14_DTC                      (8U)               /* SID 0x14 / DTC Clear Finalized                         */
#define XSPI_DSR_85_MSK                      (9U)               /* SID 0x85 / DTC Mask  Finalized                         */
#define XSPI_DSR_BA_STB                      (10U)              /* SID 0xBA / ECU Shipping Inspection / TFT_STBYB         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSR_UNLOCK                      (0x12f0425aU)

#define XSPI_DSR_TRX_RUN                     (0x0000U)
#define XSPI_DSR_TRX_SUC                     (0x0001U)
#define XSPI_DSR_TRX_FAI                     (0x0002U)
#define XSPI_DSR_TRX_UNK                     (0x0003U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_TESMD_SW_INACT                  (0U)
#define XSPI_TESMD_SW_ACT                    (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x22 */
#define XSPI_DS22_NUM_CH                     (2U)
#define XSPI_DS22_1025                       (0U)
#define XSPI_DS22_10AC                       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x2F DID 0x2831 */
#define XSPI_MID_INI                         (0x40U)
#define XSPI_MID_WHI                         (0x80U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x2F DID 0x2B01 */
#define XSPI_HUD_BLA                         (0x80U)
#define XSPI_HUD_WHI                         (0x40U)
#define XSPI_HUD_RED                         (0x20U)
#define XSPI_HUD_GRE                         (0x10U)
#define XSPI_HUD_BLU                         (0x08U)
#define XSPI_HUD_COL                         (0x04U)
#define XSPI_HUD_ADJ                         (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x31 RID 0x1004 */
#define XSPI_ROB_RES_RUN                     (XSPI_DSR_TRX_RUN)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x31 RID 0x11FF */
#define XSPI_ESO_RES_RUN                     (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0xBA TFT        */
#define XSPI_TFT_01                          (1U)
#define XSPI_TFT_02                          (2U)
#define XSPI_TFT_03                          (3U)
#define XSPI_TFT_04                          (4U)
#define XSPI_TFT_05                          (5U)
#define XSPI_TFT_06                          (6U)
#define XSPI_TFT_07                          (7U)
#define XSPI_TFT_08                          (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0x14 DTC Clear Finalized */
#define XSPI_DTC_CLR_FIN                     (0x01U)
/* Diag SID 0x85 DTC Mask  Finalized */
#define XSPI_DTC_MSK_FIN                     (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_ETHR_RW_UNK                     (0x80000000U)
#define XSPI_ETHR_RW_DIR                     (0x40000000U)
#define XSPI_ETHR_RW_RSL                     (0x20000000U)
#define XSPI_ETHR_RW_ADD                     (0x00ff0000U)
#define XSPI_ETHR_RW_VAL                     (0x0000ffffU) 

#define XSPI_ETHR_RW_DIR_WR                  (0x40000000U)      /* operation request : write                              */
#define XSPI_ETHR_RW_DIR_RE                  (0x00000000U)      /* operatoin request : read                               */

#define XSPI_ETHR_RW_RSL_SU                  (0x20000000U)      /* operatoin result  : success                            */
#define XSPI_ETHR_RW_RSL_FA                  (0x00000000U)      /* operation result  : failure                            */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Diag SID 0xBA NVM Reset  */
#define XSPI_NVM_RES_RUN                     (XSPI_DSR_TRX_RUN)
#define XSPI_NVM_RES_SUC                     (XSPI_DSR_TRX_SUC)
#define XSPI_NVM_RES_FAI                     (XSPI_DSR_TRX_FAI)
#define XSPI_NVM_RES_UNK                     (XSPI_DSR_TRX_UNK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_ROB_TX_NBYTE                    (17U)              /* Tripcount + Odo                                        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_SPN_RX_LB3                      (0U)
#define XSPI_SPN_RX_LB4                      (1U)
#define XSPI_SPN_RX_LB5                      (2U)
#define XSPI_SPN_RX_LB6                      (3U)
#define XSPI_SPN_RX_HUD                      (4U)
#define XSPI_SPN_RX_DISP                     (5U)
#define XSPI_SPN_RX_VER                      (6U)

#define XSPI_SPN_NB_LB3                      (12U)
#define XSPI_SPN_NB_LB4                      (12U)
#define XSPI_SPN_NB_LB5                      (12U)
#define XSPI_SPN_NB_LB6                      (12U)
#define XSPI_SPN_NB_HUD                      (12U)
#define XSPI_SPN_NB_DISP                     (12U)
#define XSPI_SPN_NB_VER                      (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_BA_EVC_NW_SS                    (1U)
#define XSPI_BA_SS_UNK                       (0xffff0000U)
#define XSPI_BA_SS_LSB_KMPH                  (16U)               /* 0.01 [km/h]                                            */
#define XSPI_BA_SS_LSB_EV_RX                 (0U)               /* RCAR hardware malfunciton Rx                           */
                                                                    /* b12 : TFT Panel                                        */
                                                                    /* b11 : Back Light                                       */
                                                                    /* b10 : GVIF Circuit                                     */
                                                                    /* b9  : GVIF Input                                       */
                                                                    /* b8  : GVIF Sequence                                    */
                                                                    /* b7  : Fan                                              */
                                                                    /* b6  : RCAR CoreLimit                                   */
                                                                    /* b1  : Ethernet PHY                                     */

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
void    vd_g_XSpiDsalInit(void);                                                  /* shall be invoked after vd_g_XSpiNvmInit() */
void    vd_g_XSpiDsalMainTask(void);

void    vd_g_XSpiDsalRx(const U4 * u4_ap_PDU_RX);
void    vd_g_XSpiDsalTx(U4 * u4_ap_pdu_tx);

U1      u1_g_XSpiDtcRx(const U1 u1_a_DTC_RX);

void    vd_g_XSpiDsrUnlock(const U4 u4_a_KEY);
void    vd_g_XSpiDsrTx(const U1 u1_a_CH, const U4 u4_a_REQ_TX);
void    vd_g_XSpiDsrTesmdOw(const U1 u1_a_DATA);

U1      u1_g_XSpiDsBA_NvmResRslt(void);                                           /* Return : XSPI_NVM_RES_XXX */
U4      u4_g_XSpiDsBA_EthrRWRslt(void);                                           /* Return : XSPI_ETHR_RW_XXX */

U2      u2_g_XSpiDsBA_ThermTemp(void);

void    vd_g_XSpiDsHudRead(const U1 u1_a_DS22_DID, U1 * u1_ap_ans);

void    vd_g_XSpiRobStampTx(const U1 * u1_ap_TX, const U2 u2_a_NBYTE);
U1      u1_g_XSpiSpnRx(const U1 u1_a_SPN, U1 * u1_ap_spn_rx, const U1 u1_a_NBYTE); /* Return : TRUE = rxed, FALSE = not rxed */

U1      u1_g_XSpiDsBAEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss);
U1      u1_g_XSpiDsHudEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss);

U2      u2_g_XSpiCursorCntRead(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* XSPI_DSAL_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  xspi_met_dsal.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
