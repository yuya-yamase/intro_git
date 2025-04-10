/* bsw_vcan_config_c_v3-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/CONFIG/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_vcan_MemMap.h"
#include <ComStack_Types.h>

#include <bswm_cs/bsw_bswm_cs.h>
#include <comm/bsw_comm.h>
#include <canif/bsw_canif.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include "../../CanIf/inc/bsw_canif_config.h"

#if ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE )

#include <vcan/bsw_vcan.h>
#include <Can.h>

#include "../cfg/VCan_Cfg.h"
#include "../inc/bsw_vcan_config.h"
#include "../inc/bsw_vcan_st.h"
#include "../inc/bsw_vcan_rx.h"
#include "../inc/bsw_vcan_tx.h"
#include "../inc/bsw_vcan_vcc.h"
#include "../inc/bsw_vcan_ipc.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VCAN_VIRTUAL_CH_NUM         (BSW_CANIF_MPU_VCTRLNUM)

/* Number of elements in dummy table */
#define BSW_VCAN_TBL_DUMMY_SIZE         (1U)

/* Virtual communication module count (Idx[0]:IPC, Idx[1]:VCC) */
#define BSW_VCAN_SW_CH_IPC_NUM          (2U)

/* Switch the virtual communication module interface */
#if (BSW_VCAN_IPC_FUNC == BSW_USE)
#define BSW_VCAN_IPC_FUNC_INITNODE           (&bsw_vcan_ipc_InitNode)
#define BSW_VCAN_IPC_FUNC_STARTNODE          (&bsw_vcan_ipc_StartNode)
#define BSW_VCAN_IPC_FUNC_TRANSMIT           (&bsw_vcan_ipc_Transmit)
#define BSW_VCAN_IPC_FUNC_RECEIVE            (&bsw_vcan_ipc_Receive)
#define BSW_VCAN_IPC_FUNC_DEINITNODE         (&bsw_vcan_ipc_DeInitNode)
#else
#define BSW_VCAN_IPC_FUNC_INITNODE           (&bsw_vcan_st_InitNodeNone)
#define BSW_VCAN_IPC_FUNC_STARTNODE          (&bsw_vcan_st_StartNodeNone)
#define BSW_VCAN_IPC_FUNC_TRANSMIT           (&bsw_vcan_st_TransmitNone)
#define BSW_VCAN_IPC_FUNC_RECEIVE            (&bsw_vcan_st_ReceiveNone)
#define BSW_VCAN_IPC_FUNC_DEINITNODE         (&bsw_vcan_st_DeInitNodeNone)
#endif /* (BSW_VCAN_IPC_FUNC == BSW_USE) */

#if (BSW_VCAN_VCC_FUNC == BSW_USE)
#define BSW_VCAN_VCC_FUNC_INITNODE           (&bsw_vcan_vcc_InitNode)
#define BSW_VCAN_VCC_FUNC_STARTNODE          (&bsw_vcan_vcc_StartNode)
#define BSW_VCAN_VCC_FUNC_TRANSMIT           (&bsw_vcan_vcc_Transmit)
#define BSW_VCAN_VCC_FUNC_RECEIVE            (&bsw_vcan_vcc_Receive)
#define BSW_VCAN_VCC_FUNC_DEINITNODE         (&bsw_vcan_vcc_DeInitNode)
#else
#define BSW_VCAN_VCC_FUNC_INITNODE           (&bsw_vcan_st_InitNodeNone)
#define BSW_VCAN_VCC_FUNC_STARTNODE          (&bsw_vcan_st_StartNodeNone)
#define BSW_VCAN_VCC_FUNC_TRANSMIT           (&bsw_vcan_st_TransmitNone)
#define BSW_VCAN_VCC_FUNC_RECEIVE            (&bsw_vcan_st_ReceiveNone)
#define BSW_VCAN_VCC_FUNC_DEINITNODE         (&bsw_vcan_st_DeInitNodeNone)
#endif /* (BSW_VCAN_VCC_FUNC == BSW_USE) */

/* Switch the unction pointer by function use/nouse */
#if( BSW_VCAN_VHTHNUM > 0U )
#define BSW_VCAN_TX_INIT_FUNC                (&bsw_vcan_tx_InitTx)
#define BSW_VCAN_TX_INITCONFTX_FUNC          (&bsw_vcan_tx_InitConfTx)
#define BSW_VCAN_TX_TXCONF_FUNC              (&bsw_vcan_tx_TxConfirm)
#else
#define BSW_VCAN_TX_INIT_FUNC                (&bsw_vcan_tx_InitTxNone)
#define BSW_VCAN_TX_INITCONFTX_FUNC          (&bsw_vcan_tx_InitConfTxNone)
#define BSW_VCAN_TX_TXCONF_FUNC              (&bsw_vcan_tx_TxConfNone)
#endif  /* BSW_VCAN_VHTHNUM > 0U */

#if( BSW_VCAN_USERTX_VMBOXNUM > 0U )
#define BSW_VCAN_UTX_INIT_FUNC               (&bsw_vcan_tx_InitUTx)
#define BSW_VCAN_UTX_INITCONFTX_FUNC         (&bsw_vcan_tx_InitConfUTx)
#define BSW_VCAN_UTX_TXCONF_FUNC             (&bsw_vcan_tx_UTxConfirm)
#else
#define BSW_VCAN_UTX_INIT_FUNC               (&bsw_vcan_tx_InitUTxNone)
#define BSW_VCAN_UTX_INITCONFTX_FUNC         (&bsw_vcan_tx_InitConfUTxNone)
#define BSW_VCAN_UTX_TXCONF_FUNC             (&bsw_vcan_tx_UTxConfNone)
#endif  /* BSW_VCAN_USERTX_VMBOXNUM > 0U */


/* Virtual HTH offset position */
#define BSW_VCAN_HTH_OFFSET_0          (0U)
#define BSW_VCAN_HTH_OFFSET_1          (BSW_VCAN_CFG_VHTHNUM_0)
#define BSW_VCAN_HTH_OFFSET_2          (BSW_VCAN_HTH_OFFSET_1 + BSW_VCAN_CFG_VHTHNUM_1)
#define BSW_VCAN_HTH_OFFSET_3          (BSW_VCAN_HTH_OFFSET_2 + BSW_VCAN_CFG_VHTHNUM_2)
#define BSW_VCAN_HTH_OFFSET_4          (BSW_VCAN_HTH_OFFSET_3 + BSW_VCAN_CFG_VHTHNUM_3)
#define BSW_VCAN_HTH_OFFSET_5          (BSW_VCAN_HTH_OFFSET_4 + BSW_VCAN_CFG_VHTHNUM_4)
#define BSW_VCAN_HTH_OFFSET_6          (BSW_VCAN_HTH_OFFSET_5 + BSW_VCAN_CFG_VHTHNUM_5)
#define BSW_VCAN_HTH_OFFSET_7          (BSW_VCAN_HTH_OFFSET_6 + BSW_VCAN_CFG_VHTHNUM_6)
#define BSW_VCAN_HTH_OFFSET_8          (BSW_VCAN_HTH_OFFSET_7 + BSW_VCAN_CFG_VHTHNUM_7)
#define BSW_VCAN_HTH_OFFSET_9          (BSW_VCAN_HTH_OFFSET_8 + BSW_VCAN_CFG_VHTHNUM_8)
#define BSW_VCAN_HTH_OFFSET_10         (BSW_VCAN_HTH_OFFSET_9 + BSW_VCAN_CFG_VHTHNUM_9)
#define BSW_VCAN_HTH_OFFSET_11         (BSW_VCAN_HTH_OFFSET_10 + BSW_VCAN_CFG_VHTHNUM_10)
#define BSW_VCAN_HTH_OFFSET_12         (BSW_VCAN_HTH_OFFSET_11 + BSW_VCAN_CFG_VHTHNUM_11)
#define BSW_VCAN_HTH_OFFSET_13         (BSW_VCAN_HTH_OFFSET_12 + BSW_VCAN_CFG_VHTHNUM_12)
#define BSW_VCAN_HTH_OFFSET_14         (BSW_VCAN_HTH_OFFSET_13 + BSW_VCAN_CFG_VHTHNUM_13)
#define BSW_VCAN_HTH_OFFSET_15         (BSW_VCAN_HTH_OFFSET_14 + BSW_VCAN_CFG_VHTHNUM_14)

/* Virtual HRH offset position */
#define BSW_VCAN_VHRH_OFFSET_0          (0U)
#define BSW_VCAN_VHRH_OFFSET_1          (BSW_VCAN_CFG_VHRHNUM_0)
#define BSW_VCAN_VHRH_OFFSET_2          (BSW_VCAN_VHRH_OFFSET_1 + BSW_VCAN_CFG_VHRHNUM_1)
#define BSW_VCAN_VHRH_OFFSET_3          (BSW_VCAN_VHRH_OFFSET_2 + BSW_VCAN_CFG_VHRHNUM_2)
#define BSW_VCAN_VHRH_OFFSET_4          (BSW_VCAN_VHRH_OFFSET_3 + BSW_VCAN_CFG_VHRHNUM_3)
#define BSW_VCAN_VHRH_OFFSET_5          (BSW_VCAN_VHRH_OFFSET_4 + BSW_VCAN_CFG_VHRHNUM_4)
#define BSW_VCAN_VHRH_OFFSET_6          (BSW_VCAN_VHRH_OFFSET_5 + BSW_VCAN_CFG_VHRHNUM_5)
#define BSW_VCAN_VHRH_OFFSET_7          (BSW_VCAN_VHRH_OFFSET_6 + BSW_VCAN_CFG_VHRHNUM_6)
#define BSW_VCAN_VHRH_OFFSET_8          (BSW_VCAN_VHRH_OFFSET_7 + BSW_VCAN_CFG_VHRHNUM_7)
#define BSW_VCAN_VHRH_OFFSET_9          (BSW_VCAN_VHRH_OFFSET_8 + BSW_VCAN_CFG_VHRHNUM_8)
#define BSW_VCAN_VHRH_OFFSET_10         (BSW_VCAN_VHRH_OFFSET_9 + BSW_VCAN_CFG_VHRHNUM_9)
#define BSW_VCAN_VHRH_OFFSET_11         (BSW_VCAN_VHRH_OFFSET_10 + BSW_VCAN_CFG_VHRHNUM_10)
#define BSW_VCAN_VHRH_OFFSET_12         (BSW_VCAN_VHRH_OFFSET_11 + BSW_VCAN_CFG_VHRHNUM_11)
#define BSW_VCAN_VHRH_OFFSET_13         (BSW_VCAN_VHRH_OFFSET_12 + BSW_VCAN_CFG_VHRHNUM_12)
#define BSW_VCAN_VHRH_OFFSET_14         (BSW_VCAN_VHRH_OFFSET_13 + BSW_VCAN_CFG_VHRHNUM_13)
#define BSW_VCAN_VHRH_OFFSET_15         (BSW_VCAN_VHRH_OFFSET_14 + BSW_VCAN_CFG_VHRHNUM_14)

/* UserTx Virtual MBOX offset position */
#define BSW_VCAN_UTX_VMBOX_OFFSET_0     (0U)
#define BSW_VCAN_UTX_VMBOX_OFFSET_1     (BSW_VCAN_CFG_USERTX_VMBOXNUM_0)
#define BSW_VCAN_UTX_VMBOX_OFFSET_2     (BSW_VCAN_UTX_VMBOX_OFFSET_1 + BSW_VCAN_CFG_USERTX_VMBOXNUM_1)
#define BSW_VCAN_UTX_VMBOX_OFFSET_3     (BSW_VCAN_UTX_VMBOX_OFFSET_2 + BSW_VCAN_CFG_USERTX_VMBOXNUM_2)
#define BSW_VCAN_UTX_VMBOX_OFFSET_4     (BSW_VCAN_UTX_VMBOX_OFFSET_3 + BSW_VCAN_CFG_USERTX_VMBOXNUM_3)
#define BSW_VCAN_UTX_VMBOX_OFFSET_5     (BSW_VCAN_UTX_VMBOX_OFFSET_4 + BSW_VCAN_CFG_USERTX_VMBOXNUM_4)
#define BSW_VCAN_UTX_VMBOX_OFFSET_6     (BSW_VCAN_UTX_VMBOX_OFFSET_5 + BSW_VCAN_CFG_USERTX_VMBOXNUM_5)
#define BSW_VCAN_UTX_VMBOX_OFFSET_7     (BSW_VCAN_UTX_VMBOX_OFFSET_6 + BSW_VCAN_CFG_USERTX_VMBOXNUM_6)
#define BSW_VCAN_UTX_VMBOX_OFFSET_8     (BSW_VCAN_UTX_VMBOX_OFFSET_7 + BSW_VCAN_CFG_USERTX_VMBOXNUM_7)
#define BSW_VCAN_UTX_VMBOX_OFFSET_9     (BSW_VCAN_UTX_VMBOX_OFFSET_8 + BSW_VCAN_CFG_USERTX_VMBOXNUM_8)
#define BSW_VCAN_UTX_VMBOX_OFFSET_10    (BSW_VCAN_UTX_VMBOX_OFFSET_9 + BSW_VCAN_CFG_USERTX_VMBOXNUM_9)
#define BSW_VCAN_UTX_VMBOX_OFFSET_11    (BSW_VCAN_UTX_VMBOX_OFFSET_10 + BSW_VCAN_CFG_USERTX_VMBOXNUM_10)
#define BSW_VCAN_UTX_VMBOX_OFFSET_12    (BSW_VCAN_UTX_VMBOX_OFFSET_11 + BSW_VCAN_CFG_USERTX_VMBOXNUM_11)
#define BSW_VCAN_UTX_VMBOX_OFFSET_13    (BSW_VCAN_UTX_VMBOX_OFFSET_12 + BSW_VCAN_CFG_USERTX_VMBOXNUM_12)
#define BSW_VCAN_UTX_VMBOX_OFFSET_14    (BSW_VCAN_UTX_VMBOX_OFFSET_13 + BSW_VCAN_CFG_USERTX_VMBOXNUM_13)
#define BSW_VCAN_UTX_VMBOX_OFFSET_15    (BSW_VCAN_UTX_VMBOX_OFFSET_14 + BSW_VCAN_CFG_USERTX_VMBOXNUM_14)

/* List of received node IDs for each virtual controller(Dummy table) */
static BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeDummyTbl[ BSW_VCAN_TBL_DUMMY_SIZE ] =
{
    /* Rx Node Id,                      Rx Timing,              Extend1,     Rx Num(Polling), Rx Num(Interrupt), Extend2 */
    { (BswU4)BSW_VCAN_INVALID_NODE_ID, (BswU1)BSW_VCAN_POLLING, (BswU1)0x00, (BswU2)0x0000,   (BswU2)0x0000,     (BswU2)0x0000 }
};

/* List of received node IDs for each virtual controller */
#define BSW_VCAN_VCTRL0_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL0 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl0[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL1_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL1 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl1[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL2_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL2 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl2[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL3_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL3 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl3[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL4_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL4 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl4[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL5_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL5 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl5[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL6_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL6 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl6[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL7_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL7 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl7[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL8_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL8 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl8[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL9_RXNODETBL    ( (BSW_VCAN_CFG_RXNUM_VCONTROL9 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl9[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL10_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL10 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl10[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL11_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL11 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl11[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL12_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL12 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl12[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL13_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL13 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl13[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL14_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL14 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl14[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )
#define BSW_VCAN_VCTRL15_RXNODETBL   ( (BSW_VCAN_CFG_RXNUM_VCONTROL15 != 0U) ? (&bsw_vcan_stRxNodeTbl_VControl15[0U]) : (&bsw_vcan_stRxNodeDummyTbl[0U]) )


/* Transmission VMBOX list for each virtual controller(Dummy table) */
static BswConst BswU1 bsw_vcan_stTxVMBoxDummyTbl[ BSW_VCAN_TBL_DUMMY_SIZE ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
    ( (BswU1)(BSW_VCAN_POLLING | BSW_VCAN_KIND_TRANSMIT) )
};

/* Transmission VMBOX list for each virtual controller */
#define BSW_VCAN_VCTRL0_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_0 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl0[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL1_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_1 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl1[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL2_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_2 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl2[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL3_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_3 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl3[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL4_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_4 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl4[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL5_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_5 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl5[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL6_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_6 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl6[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL7_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_7 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl7[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL8_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_8 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl8[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL9_TXVMBOXTBL   ( (BSW_VCAN_TX_VMBOXNUM_9 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl9[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL10_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_10 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl10[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL11_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_11 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl11[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL12_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_12 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl12[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL13_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_13 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl13[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL14_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_14 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl14[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )
#define BSW_VCAN_VCTRL15_TXVMBOXTBL  ( (BSW_VCAN_TX_VMBOXNUM_15 != 0U) ? (&bsw_vcan_u1TxMBoxTbl_VControl15[0U]) : (&bsw_vcan_stTxVMBoxDummyTbl[0U]) )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
BswU2                    bsw_vcan_st_u2ControllerStatus[ BSW_VCAN_VIRTUAL_CH_NUM ];
BswU1                    bsw_vcan_tx_u1TxCount[ BSW_VCAN_VIRTUAL_CH_NUM ];

#if( BSW_VCAN_VHTHNUM > 0U )
PduIdType                bsw_vcan_tx_stConfirmedPdu[ BSW_VCAN_VHTHNUM ];
#endif  /* BSW_VCAN_VHTHNUM > 0U */

#if( BSW_VCAN_USERTX_VMBOXNUM > 0U )
BswU1                    bsw_vcan_tx_stConfirmedMBox[ BSW_VCAN_USERTX_VMBOXNUM ];
#endif  /* BSW_VCAN_USERTX_VMBOXNUM > 0U */


static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl0[ BSW_VCAN_CFG_RXNUM_VCONTROL0 ];
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl1[ BSW_VCAN_CFG_RXNUM_VCONTROL1 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl2[ BSW_VCAN_CFG_RXNUM_VCONTROL2 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl3[ BSW_VCAN_CFG_RXNUM_VCONTROL3 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl4[ BSW_VCAN_CFG_RXNUM_VCONTROL4 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl5[ BSW_VCAN_CFG_RXNUM_VCONTROL5 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl6[ BSW_VCAN_CFG_RXNUM_VCONTROL6 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl7[ BSW_VCAN_CFG_RXNUM_VCONTROL7 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl8[ BSW_VCAN_CFG_RXNUM_VCONTROL8 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl9[ BSW_VCAN_CFG_RXNUM_VCONTROL9 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl10[ BSW_VCAN_CFG_RXNUM_VCONTROL10 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl11[ BSW_VCAN_CFG_RXNUM_VCONTROL11 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl12[ BSW_VCAN_CFG_RXNUM_VCONTROL12 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl13[ BSW_VCAN_CFG_RXNUM_VCONTROL13 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl14[ BSW_VCAN_CFG_RXNUM_VCONTROL14 ];
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
static BswU2 bsw_vcan_rx_u2RxIntCnt_VCtrl15[ BSW_VCAN_CFG_RXNUM_VCONTROL15 ];
#endif

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
BswConst BswU1 bsw_vcan_st_u1VirtualCtrlNum    = (BswU1)BSW_VCAN_VIRTUAL_CH_NUM;
BswConst BswU2 bsw_vcan_rx_u2VirtualHrhNum     = (BswU2)BSW_VCAN_VHRHNUM;
BswConst BswU2 bsw_vcan_tx_u2VirtualHthNum     = (BswU2)BSW_VCAN_VHTHNUM;

/* Switch the virtual communication module function */
BswConst Bsw_VCan_IpcFuncTblType bsw_vcan_stChIpcTbl[ BSW_VCAN_SW_CH_IPC_NUM ] = 
{
    {
          BSW_VCAN_IPC_FUNC_INITNODE
         ,BSW_VCAN_IPC_FUNC_STARTNODE
         ,BSW_VCAN_IPC_FUNC_TRANSMIT
         ,BSW_VCAN_IPC_FUNC_RECEIVE
         ,BSW_VCAN_IPC_FUNC_DEINITNODE
    }
   ,{
          BSW_VCAN_VCC_FUNC_INITNODE
         ,BSW_VCAN_VCC_FUNC_STARTNODE
         ,BSW_VCAN_VCC_FUNC_TRANSMIT
         ,BSW_VCAN_VCC_FUNC_RECEIVE
         ,BSW_VCAN_VCC_FUNC_DEINITNODE
    }
};

/* Switch the unction pointer by function use/nouse */
void (* BswConst bsw_vcan_tx_ptInitTxFunc)( void )  = BSW_VCAN_TX_INIT_FUNC;
void (* BswConst bsw_vcan_tx_ptInitConfTxFunc)( BswU1 u1VController )  = BSW_VCAN_TX_INITCONFTX_FUNC;
void (* BswConst bsw_vcan_tx_ptTxConfFunc)( BswU1 u1VController, BswU1 u1TxTiming )  = BSW_VCAN_TX_TXCONF_FUNC;

void (* BswConst bsw_vcan_tx_ptInitUTxFunc)( void ) = BSW_VCAN_UTX_INIT_FUNC;
void (* BswConst bsw_vcan_tx_ptInitConfUTxFunc)( BswU1 u1VController )  = BSW_VCAN_UTX_INITCONFTX_FUNC;
void (* BswConst bsw_vcan_tx_ptUTxConfFunc)( BswU1 u1VController, BswU1 u1TxTiming ) = BSW_VCAN_UTX_TXCONF_FUNC;


/* ============================= */
/*  Definition for virtual controller   */
/* ============================= */
/* Bus ID table */
BswConst BswU1 bsw_vcan_u1IpcVirtualCtrlBus[BSW_VCAN_VIRTUAL_CH_NUM] = 
{
    (BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER0
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER1
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER2
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER3
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER4
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER5
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER6
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER7
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER8
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER9
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER10
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER11
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER12
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER13
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER14
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU1)BSW_VCAN_CFG_BUS_VCONTROLLER15
#endif
};

/* Number of virtual receiving nodes */
BswConst BswU1 bsw_vcan_rx_u1RxNodeNum[BSW_VCAN_VIRTUAL_CH_NUM] = 
{
    (BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL0
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL1
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL2
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL3
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL4
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL5
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL6
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL7
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL8
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL9
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL10
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL11
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL12
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL13
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL14
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU1)BSW_VCAN_CFG_RXNUM_VCONTROL15
#endif
};

/* Virtual receiving node table */
BswConst Bsw_VCan_RxNodeTblType* BswConst bsw_vcan_rx_ptRxNodeIdTbl[BSW_VCAN_VIRTUAL_CH_NUM] = 
{
    BSW_VCAN_VCTRL0_RXNODETBL
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,BSW_VCAN_VCTRL1_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,BSW_VCAN_VCTRL2_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,BSW_VCAN_VCTRL3_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,BSW_VCAN_VCTRL4_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,BSW_VCAN_VCTRL5_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,BSW_VCAN_VCTRL6_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,BSW_VCAN_VCTRL7_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,BSW_VCAN_VCTRL8_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,BSW_VCAN_VCTRL9_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,BSW_VCAN_VCTRL10_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,BSW_VCAN_VCTRL11_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,BSW_VCAN_VCTRL12_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,BSW_VCAN_VCTRL13_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,BSW_VCAN_VCTRL14_RXNODETBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,BSW_VCAN_VCTRL15_RXNODETBL
#endif
};

/* Virtual communication module switching index table*/
BswConst BswU1 bsw_vcan_u1SwChIpcVirtualTbl[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_VIRTUALTBL_INDEX(0)
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(1)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(2)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(3)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(4)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(5)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(6)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(7)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(8)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(9)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(10)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(11)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(12)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(13)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(14)
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU1)BSW_VCAN_VIRTUALTBL_INDEX(15)
#endif
};

/* Number of times to limit transmissions per cycle */
BswConst BswU1 bsw_vcan_tx_u1TxLimit[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR0
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR1
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR2
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR3
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR4
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR5
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR6
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR7
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR8
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR9
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR10
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR11
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR12
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR13
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR14
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU1)BSW_VCAN_CFG_TX_LIMIT_VCTRLLR15
#endif
};

/* Use/Nouse of Continuous TxReq */
BswConst BswU1 bsw_vcan_tx_u1UserTxContinue[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX0
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX1
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX2
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX3
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX4
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX5
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX6
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX7
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX8
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX9
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX10
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX11
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX12
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX13
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX14
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU1)BSW_VCAN_CFG_USER_CONTINUE_TX15
#endif
};

/* Transmit queue number(VCC)/NodeID(IPC) */
BswConst BswU4 bsw_vcan_tx_u4VirtualCtrlToNode[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU4)BSW_VCAN_CFG_TX_VCONTROLLER0
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER1
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER2
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER3
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER4
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER5
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER6
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER7
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER8
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER9
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER10
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER11
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER12
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER13
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER14
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,(BswU4)BSW_VCAN_CFG_TX_VCONTROLLER15
#endif
};

/* Transmit Virtual MBOX Table */
BswConst BswU1* BswConst bsw_vcan_tx_u1TxVMboxTbl[BSW_VCAN_VIRTUAL_CH_NUM] = 
{
    BSW_VCAN_VCTRL0_TXVMBOXTBL
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,BSW_VCAN_VCTRL1_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,BSW_VCAN_VCTRL2_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,BSW_VCAN_VCTRL3_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,BSW_VCAN_VCTRL4_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,BSW_VCAN_VCTRL5_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,BSW_VCAN_VCTRL6_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,BSW_VCAN_VCTRL7_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,BSW_VCAN_VCTRL8_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,BSW_VCAN_VCTRL9_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,BSW_VCAN_VCTRL10_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,BSW_VCAN_VCTRL11_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,BSW_VCAN_VCTRL12_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,BSW_VCAN_VCTRL13_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,BSW_VCAN_VCTRL14_TXVMBOXTBL
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,BSW_VCAN_VCTRL15_TXVMBOXTBL
#endif
};

/******************************************/
/*  Rx                                    */
/******************************************/
/* VHRH Num */
BswConst BswU1 bsw_vcan_rx_u1VhrhNum[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_VHRHNUM_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_VHRHNUM_15
#endif
};

/* Top position of virtual HRH */
BswConst BswU2 bsw_vcan_rx_u2VhrhTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU2)BSW_VCAN_VHRH_OFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU2)BSW_VCAN_VHRH_OFFSET_15
#endif
};

/* Top position of virtual MBOX for VHRH  */
BswConst BswU1 bsw_vcan_rx_u1RxVMboxTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_RXOFFSET_15
#endif
};

/* Receive Interrupt Count */
BswU2* BswConst bsw_vcan_rx_u2RxIntCount[BSW_VCAN_VIRTUAL_CH_NUM] = 
{
    &bsw_vcan_rx_u2RxIntCnt_VCtrl0[0U]
#if (BSW_VCAN_VIRTUAL_CH_NUM > 1U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl1[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 2U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl2[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 3U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl3[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 4U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl4[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 5U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl5[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 6U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl6[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 7U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl7[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 8U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl8[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 9U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl9[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 10U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl10[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 11U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl11[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 12U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl12[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 13U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl13[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 14U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl14[0U]
#endif
#if (BSW_VCAN_VIRTUAL_CH_NUM > 15U)
   ,&bsw_vcan_rx_u2RxIntCnt_VCtrl15[0U]
#endif
};

/*  Receive-Message Table(Dummy table) */
#if ( BSW_VCAN_VHRHNUM == 0U )
BswConst Bsw_VCan_RxTblType bsw_vcan_stRxMessageTbl[ BSW_VCAN_TBL_DUMMY_SIZE ] =
{
  /*   CAN ID      , Mask              */
  /*--- VM Reception(VHRH) ------------*/
  { 0x00000000UL   , 0x00000000UL       }
};
#endif /* ( BSW_VCAN_VHRHNUM == 0U ) */

/******************************************/
/*  Tx                                    */
/******************************************/
/* VHTH Num */
BswConst BswU1 bsw_vcan_tx_u1VhthNum[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_VHTHNUM_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_VHTHNUM_15
#endif
};

/* Top position of virtual HTH */
BswConst BswU2 bsw_vcan_tx_u2VhthTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU2)BSW_VCAN_HTH_OFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU2)BSW_VCAN_HTH_OFFSET_15
#endif
};

/* Top position of virtual MBOX for VHTH */
BswConst BswU1 bsw_vcan_tx_u1TxVMboxTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_TXOFFSET_15
#endif
};

/******************************************/
/*  UserTx                                */
/******************************************/
/* UserTx VMBOX number */
BswConst BswU1 bsw_vcan_tx_u1UserTxMBoxNum[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_USERTX_VMBOXNUM_15
#endif
};

/* Top position of virtual MBOX for UserTx */
BswConst BswU2 bsw_vcan_tx_u2UserTxVMboxTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU2)BSW_VCAN_UTX_VMBOX_OFFSET_15
#endif
};

/* Top position of virtual MBOX for UserTx by virtual controller  */
BswConst BswU1 bsw_vcan_tx_u1UTxVMboxVCtrlTop[ BSW_VCAN_VIRTUAL_CH_NUM ] =
{
    (BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_0
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 1U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_1
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 2U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_2
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 3U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_3
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 4U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_4
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 5U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_5
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 6U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_6
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 7U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_7
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 8U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_8
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 9U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_9
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 10U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_10
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 11U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_11
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 12U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_12
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 13U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_13
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 14U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_14
#endif
#if ( BSW_VCAN_VIRTUAL_CH_NUM > 15U )
   ,(BswU1)BSW_VCAN_CFG_VMBOX_UTXOFFSET_15
#endif
};

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* ( BSW_BSWM_CS_FUNC_VCAN == BSW_USE ) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/04                                             */
/*  v2-1-0          :2022/07/11                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
