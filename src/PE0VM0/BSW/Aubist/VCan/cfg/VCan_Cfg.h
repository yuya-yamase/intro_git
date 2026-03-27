/* vcan_cfg_h_v3-0-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCAN/CFG/HEADER                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_VCAN_CFG_H
#define     BSW_VCAN_CFG_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/******************************************/
/*   Connection IPC                       */
/******************************************/
#define BSW_VCAN_CFG_IPC_VCONTROLLER0           (BSW_VCAN_VCC)
#define BSW_VCAN_CFG_IPC_VCONTROLLER1           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER2           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER3           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER4           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER5           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER6           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER7           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER8           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER9           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER10          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER11          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER12          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER13          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER14          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_IPC_VCONTROLLER15          (BSW_VCAN_NOUSE)

/******************************************/
/*   Tx Limit                             */
/******************************************/
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR0          (1U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR1          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR2          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR3          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR4          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR5          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR6          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR7          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR8          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR9          (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR10         (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR11         (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR12         (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR13         (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR14         (0U)
#define BSW_VCAN_CFG_TX_LIMIT_VCTRLLR15         (0U)

/******************************************/
/*   Continuous Tx Mode for User Tx       */
/******************************************/
#define BSW_VCAN_CFG_USER_CONTINUE_TX0          (BSW_USE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX1          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX2          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX3          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX4          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX5          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX6          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX7          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX8          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX9          (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX10         (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX11         (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX12         (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX13         (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX14         (BSW_NOUSE)
#define BSW_VCAN_CFG_USER_CONTINUE_TX15         (BSW_NOUSE)

/******************************************/
/*   Bus ID for Ipc module only           */
/******************************************/
#define BSW_VCAN_CFG_BUS_VCONTROLLER0           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER1           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER2           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER3           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER4           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER5           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER6           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER7           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER8           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER9           (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER10          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER11          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER12          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER13          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER14          (BSW_VCAN_NOUSE)
#define BSW_VCAN_CFG_BUS_VCONTROLLER15          (BSW_VCAN_NOUSE)

/***********************************************/
/*  Transmit QUE ID for VCC / Node ID for Ipc  */
/***********************************************/
#define BSW_VCAN_CFG_TX_VCONTROLLER0            (0x00000004)
#define BSW_VCAN_CFG_TX_VCONTROLLER1            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER2            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER3            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER4            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER5            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER6            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER7            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER8            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER9            (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER10           (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER11           (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER12           (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER13           (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER14           (BSW_VCAN_INVALID_NODE_ID)
#define BSW_VCAN_CFG_TX_VCONTROLLER15           (BSW_VCAN_INVALID_NODE_ID)

/******************************************************/
/*  Receive QUE Number for VCC / Node Number for Ipc  */
/******************************************************/
#define BSW_VCAN_CFG_RXNUM_VCONTROL0            (3U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL1            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL2            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL3            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL4            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL5            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL6            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL7            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL8            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL9            (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL10           (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL11           (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL12           (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL13           (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL14           (0U)
#define BSW_VCAN_CFG_RXNUM_VCONTROL15           (0U)

/******************************************/
/*  Transmit Virtual MBOX Setting         */
/*  (Each Virtual Controller)             */
/******************************************/
/* Tx VHOH(VHTH) Number */
#define BSW_VCAN_CFG_VHTHNUM_0                  (1U)
#define BSW_VCAN_CFG_VHTHNUM_1                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_2                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_3                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_4                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_5                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_6                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_7                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_8                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_9                  (0U)
#define BSW_VCAN_CFG_VHTHNUM_10                 (0U)
#define BSW_VCAN_CFG_VHTHNUM_11                 (0U)
#define BSW_VCAN_CFG_VHTHNUM_12                 (0U)
#define BSW_VCAN_CFG_VHTHNUM_13                 (0U)
#define BSW_VCAN_CFG_VHTHNUM_14                 (0U)
#define BSW_VCAN_CFG_VHTHNUM_15                 (0U)

/* First Virtual MBOX Number for VHTH */
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_0           (7U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_1           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_2           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_3           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_4           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_5           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_6           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_7           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_8           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_9           (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_10          (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_11          (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_12          (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_13          (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_14          (0U)
#define BSW_VCAN_CFG_VMBOX_TXOFFSET_15          (0U)

/******************************************/
/*  User Transmit Virtual MBOX Setting    */
/*  (Each Virtual Controller)             */
/******************************************/
/* Virtual MBOX Number for UserTx */
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_0         (1U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_1         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_2         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_3         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_4         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_5         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_6         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_7         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_8         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_9         (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_10        (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_11        (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_12        (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_13        (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_14        (0U)
#define BSW_VCAN_CFG_USERTX_VMBOXNUM_15        (0U)

/* First Virtual MBOX Number fot UserTx */
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_0         (6U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_1         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_2         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_3         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_4         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_5         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_6         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_7         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_8         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_9         (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_10        (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_11        (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_12        (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_13        (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_14        (0U)
#define BSW_VCAN_CFG_VMBOX_UTXOFFSET_15        (0U)

/******************************************/
/*  Receive Virtual MBOX Setting          */
/*  (Each Virtual Controller)             */
/******************************************/
/* Rx VHOH(VHRH) Number */
#define BSW_VCAN_CFG_VHRHNUM_0                  (6U)
#define BSW_VCAN_CFG_VHRHNUM_1                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_2                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_3                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_4                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_5                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_6                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_7                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_8                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_9                  (0U)
#define BSW_VCAN_CFG_VHRHNUM_10                 (0U)
#define BSW_VCAN_CFG_VHRHNUM_11                 (0U)
#define BSW_VCAN_CFG_VHRHNUM_12                 (0U)
#define BSW_VCAN_CFG_VHRHNUM_13                 (0U)
#define BSW_VCAN_CFG_VHRHNUM_14                 (0U)
#define BSW_VCAN_CFG_VHRHNUM_15                 (0U)

/* First Virtual MBOX Number for VHRH */
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_0           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_1           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_2           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_3           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_4           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_5           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_6           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_7           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_8           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_9           (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_10          (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_11          (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_12          (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_13          (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_14          (0U)
#define BSW_VCAN_CFG_VMBOX_RXOFFSET_15          (0U)

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


#endif  /* BSW_VCAN_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/11/25                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
