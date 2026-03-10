/* vcan_pbcfg_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCAN/PBCFG/CODE                                           */
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

#if (BSW_BSWM_CS_FUNC_VCAN == BSW_USE)

#include "VCan_Cfg.h"
#include <vcan/bsw_vcan.h>

#include "../inc/bsw_vcan_rx.h"
#include "../inc/bsw_vcan_tx.h"
#include "../inc/bsw_vcan_config.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

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
/************************************************/
/*  Virtual-HOH Configuration Table             */
/************************************************/
BswConst BswU1 bsw_vcan_stVirtualHohTbl[ BSW_VCAN_VHOHNUM ] =
{
  /*   Virtual ControllerID    */
  /*--- VM Reception(VHRH)    -----------------------------*/
     ( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [0] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [1] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [2] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [3] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [4] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [5] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [6] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [7] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [8] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [9] */
  /*--- VM Transmission(VHTH) -----------------------------*/
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [10] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [11] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [12] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [13] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [14] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [15] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [16] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [17] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [18] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [19] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [20] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [21] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [22] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [23] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [24] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [25] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [26] */
    ,( (BswU1)BSW_VCAN_VCONTROLLER0 )   /* [27] */
};

/************************************************/
/*  Receive-Message Table                       */
/************************************************/
#if ( BSW_VCAN_VHRHNUM != 0U )
BswConst Bsw_VCan_RxTblType bsw_vcan_stRxMessageTbl[ BSW_VCAN_VHRHNUM ] =
{
  /*   CAN ID      , Mask              */
  /*--- VM Reception(VHRH) ------------*/
     { 0x40000000UL, 0xFFFFFC00UL }   /* [0] */
    ,{ 0x00000200UL, 0xFFFFFEEEUL }   /* [1] */
    ,{ 0x00000400UL, 0xBFFFFF00UL }   /* [2] */
    ,{ 0x40000500UL, 0xFFFFFF00UL }   /* [3] */
    ,{ 0x40000600UL, 0xFFFFFF00UL }   /* [4] */
    ,{ 0x98DA1CE0UL, 0xBFFFFFFEUL }   /* [5] */
    ,{ 0x98DBEFE0UL, 0xBFFFFFFEUL }   /* [6] */
    ,{ 0x98000000UL, 0xBFFFFC00UL }   /* [7] */
    ,{ 0x98002000UL, 0xBFFFFE00UL }   /* [8] */
    ,{ 0x98008000UL, 0xBFFFFF00UL }   /* [9] */
};
#endif /* ( BSW_VCAN_VHRHNUM != 0U ) */

/**************************************************************************************/
/*  Reception Node Table                                                              */
/*   {                                                                                */
/*     Rx Node Id (QueID for VCC / NodeID for IPC), Rx Timing(INTERRUPT/POLLING),     */
/*     Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2                     */
/*   }                                                                                */
/**************************************************************************************/
#if ( BSW_VCAN_CFG_RXNUM_VCONTROL0 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl0[ BSW_VCAN_CFG_RXNUM_VCONTROL0 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
    { (BswU4)0x00000004, (BswU1)BSW_VCAN_POLLING,   (BswU1)0, (BswU2)56,    (BswU2)0,     (BswU2)0 }   /* [0] */
   ,{ (BswU4)0x00000005, (BswU1)BSW_VCAN_POLLING,   (BswU1)0, (BswU2)20,    (BswU2)0,     (BswU2)0 }   /* [1] */
   ,{ (BswU4)0x00000007, (BswU1)BSW_VCAN_POLLING,   (BswU1)0, (BswU2)20,    (BswU2)0,     (BswU2)0 }   /* [2] */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL0 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL1 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl1[ BSW_VCAN_CFG_RXNUM_VCONTROL1 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL1 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL2 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl2[ BSW_VCAN_CFG_RXNUM_VCONTROL2 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL2 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL3 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl3[ BSW_VCAN_CFG_RXNUM_VCONTROL3 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL3 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL4 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl4[ BSW_VCAN_CFG_RXNUM_VCONTROL4 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL4 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL5 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl5[ BSW_VCAN_CFG_RXNUM_VCONTROL5 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL5 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL6 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl6[ BSW_VCAN_CFG_RXNUM_VCONTROL6 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL6 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL7 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl7[ BSW_VCAN_CFG_RXNUM_VCONTROL7 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL7 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL8 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl8[ BSW_VCAN_CFG_RXNUM_VCONTROL8 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL8 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL9 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl9[ BSW_VCAN_CFG_RXNUM_VCONTROL9 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL9 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL10 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl10[ BSW_VCAN_CFG_RXNUM_VCONTROL10 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL10 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL11 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl11[ BSW_VCAN_CFG_RXNUM_VCONTROL11 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL11 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL12 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl12[ BSW_VCAN_CFG_RXNUM_VCONTROL12 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL12 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL13 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl13[ BSW_VCAN_CFG_RXNUM_VCONTROL13 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL13 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL14 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl14[ BSW_VCAN_CFG_RXNUM_VCONTROL14 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL14 != 0U ) */

#if ( BSW_VCAN_CFG_RXNUM_VCONTROL15 != 0U )
BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl15[ BSW_VCAN_CFG_RXNUM_VCONTROL15 ] =
{
    /* Rx Node Id, Rx Timing, Extend1, Rx MaxNum(Polling), Rx MaxNum(Interrupt), Extend2 */
};
#endif /* ( BSW_VCAN_CFG_RXNUM_VCONTROL15 != 0U ) */


/************************************************/
/*  Transmit Virtual MBOX Table                 */
/************************************************/
#if ( BSW_VCAN_TX_VMBOXNUM_0 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl0[ BSW_VCAN_TX_VMBOXNUM_0 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
    (BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [0] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [1] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [2] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [3] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [4] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [5] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [6] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [7] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [8] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [9] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [10] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [11] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [12] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [13] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [14] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [15] */
   ,(BswU1)(BSW_VCAN_INTERRUPT | BSW_VCAN_KIND_TRANSMIT )   /* [16] */
   ,(BswU1)(BSW_VCAN_POLLING   | BSW_VCAN_KIND_TRANSMIT )   /* [17] */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_0 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_1 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl1[ BSW_VCAN_TX_VMBOXNUM_1 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_1 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_2 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl2[ BSW_VCAN_TX_VMBOXNUM_2 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_2 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_3 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl3[ BSW_VCAN_TX_VMBOXNUM_3 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_3 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_4 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl4[ BSW_VCAN_TX_VMBOXNUM_4 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_4 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_5 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl5[ BSW_VCAN_TX_VMBOXNUM_5 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_5 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_6 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl6[ BSW_VCAN_TX_VMBOXNUM_6 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_6 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_7 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl7[ BSW_VCAN_TX_VMBOXNUM_7 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_7 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_8 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl8[ BSW_VCAN_TX_VMBOXNUM_8 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_8 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_9 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl9[ BSW_VCAN_TX_VMBOXNUM_9 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_9 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_10 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl10[ BSW_VCAN_TX_VMBOXNUM_10 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_10 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_11 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl11[ BSW_VCAN_TX_VMBOXNUM_11 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_11 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_12 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl12[ BSW_VCAN_TX_VMBOXNUM_12 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_12 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_13 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl13[ BSW_VCAN_TX_VMBOXNUM_13 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_13 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_14 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl14[ BSW_VCAN_TX_VMBOXNUM_14 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_14 != 0U ) */

#if ( BSW_VCAN_TX_VMBOXNUM_15 != 0U )
BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl15[ BSW_VCAN_TX_VMBOXNUM_15 ] =
{
    /* Virtual MBOX Setting (Timing|TxKind) */
};

#endif /* ( BSW_VCAN_TX_VMBOXNUM_15 != 0U ) */


#endif /* (BSW_BSWM_CS_FUNC_VCAN == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/03                                             */
/*  v2-1-0          :2022/07/08                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
