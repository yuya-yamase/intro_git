/* bswm_cs_cfg_h_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSWM/CS/CFG/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CS_CFG_H
#define BSW_BSWM_CS_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_CFG_MPU_TICKTIME          (1000UL)
#define BSW_BSWM_CS_CFG_TICKTIME_HIGH         (1U)
#define BSW_BSWM_CS_CFG_TICKTIME_MID          (5U)
#define BSW_BSWM_CS_CFG_MSGDELIVER            (BSW_BSWM_CS_MSGDELIVER_MIDDLE)
#define BSW_BSWM_CS_CFG_ECU_SLEEP             (BSW_USE)
#define BSW_BSWM_CS_CFG_ECU_FAIL              (BSW_USE)

#define BSW_BSWM_CS_CFG_FUNC_CS               (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_COM              (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_LDCOM            (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_UPPERCDD1        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_UPPERCDD2        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_DCM              (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_BSWMCS           (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_COMM             (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_PDUR             (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_NM               (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_XCP              (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_VDAT             (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_FUNC_BSWMCAN          (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANSM            (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANIF            (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANNM            (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANRX            (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANTX            (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANTX_PHY        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_CANTX_VIR        (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANTP            (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_CANCDD1          (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_CANCDD2          (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_CANTRCV          (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_CANDRV           (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_VCAN             (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_J1939TP          (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_FUNC_LIN              (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_LINTP            (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_LINCDD1          (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_LINCDD2          (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_FUNC_ETH              (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_DOIP             (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_ETHCDD1          (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_ETHCDD2          (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_VETH             (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_ETHTSYN          (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_FUNC_SECOC            (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_IPDUM            (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_SOMEIPTP         (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_SD               (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_FUNC_BSWM_VPS         (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_CHRSTCTRL             (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_DMCTRL                (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_XCP_KIND              (BSW_BSWM_CS_XCP_KIND_NONE)

#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_0        (BSW_USE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_1        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_2        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_3        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_4        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_5        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_6        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_7        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_8        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_9        (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_10       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_11       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_12       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_13       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_14       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_15       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_16       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_17       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_18       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_19       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_20       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_21       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_22       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_23       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_24       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_25       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_26       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_27       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_28       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_29       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_30       (BSW_NOUSE)
#define BSW_BSWM_CS_CFG_FUNC_PNCIPDU_31       (BSW_NOUSE)

#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_0         (BSW_BSWM_CS_TXCTRL_STOPALL)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_1         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_2         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_3         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_4         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_5         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_6         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_7         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_8         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_9         (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_10        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_11        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_12        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_13        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_14        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_15        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_16        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_17        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_18        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_19        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_20        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_21        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_22        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_23        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_24        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_25        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_26        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_27        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_28        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_29        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_30        (BSW_BSWM_CS_TXCTRL_NOUSE)
#define BSW_BSWM_CS_CFG_TXCTRL_TYPE_31        (BSW_BSWM_CS_TXCTRL_NOUSE)

#define BSW_BSWM_CS_CFG_SENDSTART_PW_0        (300U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_1        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_2        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_3        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_4        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_5        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_6        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_7        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_8        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_9        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_10       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_11       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_12       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_13       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_14       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_15       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_16       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_17       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_18       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_19       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_20       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_21       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_22       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_23       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_24       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_25       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_26       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_27       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_28       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_29       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_30       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PW_31       (0U)

#define BSW_BSWM_CS_CFG_SENDSTART_PN_0        (150U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_1        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_2        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_3        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_4        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_5        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_6        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_7        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_8        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_9        (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_10       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_11       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_12       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_13       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_14       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_15       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_16       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_17       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_18       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_19       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_20       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_21       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_22       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_23       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_24       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_25       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_26       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_27       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_28       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_29       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_30       (0U)
#define BSW_BSWM_CS_CFG_SENDSTART_PN_31       (0U)

#define BSW_BSWM_CS_CFG_ENABLPERI_PN_0        (300U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_1        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_2        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_3        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_4        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_5        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_6        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_7        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_8        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_9        (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_10       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_11       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_12       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_13       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_14       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_15       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_16       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_17       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_18       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_19       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_20       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_21       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_22       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_23       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_24       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_25       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_26       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_27       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_28       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_29       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_30       (0U)
#define BSW_BSWM_CS_CFG_ENABLPERI_PN_31       (0U)

#define BSW_BSWM_CS_CFG_EVTAWAKE_0            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_1            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_2            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_3            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_4            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_5            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_6            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_7            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_8            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_9            (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_10           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_11           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_12           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_13           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_14           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_15           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_16           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_17           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_18           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_19           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_20           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_21           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_22           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_23           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_24           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_25           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_26           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_27           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_28           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_29           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_30           (0U)
#define BSW_BSWM_CS_CFG_EVTAWAKE_31           (0U)

#define BSW_BSWM_CS_CFG_MUX_MA_PTN            (BSW_BSWM_CS_MUX_MA_NONE)

#define BSW_BSWM_CS_CFG_PNCIPDU_RX_0          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_1          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_2          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_3          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_4          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_5          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_6          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_7          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_8          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_9          (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_10         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_11         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_12         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_13         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_14         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_15         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_16         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_17         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_18         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_19         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_20         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_21         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_22         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_23         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_24         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_25         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_26         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_27         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_28         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_29         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_30         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)
#define BSW_BSWM_CS_CFG_PNCIPDU_RX_31         (BSW_BSWM_CS_PNCIPDU_RXTYPE_CH)

/* Symbolic Name Reference - SysStatus */
#define BswM_CSConf_SysStatusName_BAT                       (BSW_BSWM_CS_SYSSTAT_BAT)
#define BswM_CSConf_SysStatusName_ACC                       (BSW_BSWM_CS_SYSSTAT_ACC)
#define BswM_CSConf_SysStatusName_IG                        (BSW_BSWM_CS_SYSSTAT_IG)
#define BswM_CSConf_SysStatusName_PBA                       (BSW_BSWM_CS_SYSSTAT_USER1)
#define BswM_CSConf_SysStatusName_IGR                       (BSW_BSWM_CS_SYSSTAT_USER2)
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CS_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-0-1          :2018/01/30                                             */
/*  v1-1-0          :2018/12/03                                             */
/*  v2-0-0          :2022/02/23                                             */
/*  v2-1-0          :2023/01/26                                             */
/*  v2-2-0          :2023/05/09                                             */
/*  v3-0-0          :2025/01/23                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
