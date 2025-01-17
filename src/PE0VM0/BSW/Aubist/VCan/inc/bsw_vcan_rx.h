/* bsw_vcan_rx_h_v2-1-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/RX/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_VCAN_RX_H
#define     BSW_VCAN_RX_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VCAN_MSGBUF_ARRAYSIZE       (20U)
#define BSW_VCAN_u4MSGBUF_BYTESIZE      ((BswU4)((BswU4)BSW_VCAN_MSGBUF_ARRAYSIZE << 2U))

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Received message type */
typedef struct
{
    BswU4           u4CanId;           /* CAN ID           */
    BswU4           u4CanIdMask;       /* Mask CAN ID     */
} Bsw_VCan_RxTblType;

/* Received node table type */
typedef struct
{
    BswU4           u4RxNodeId;        /* Receive queue number(VCC),NodeID(IPC)   */
    BswU1           u1RxTiming;        /* Receiving process timing                */
    BswU1           u1Extend1;         /* For future extension                    */
    BswU2           u2PolNumMax;       /* Maximum Receive Number for Polling      */
    BswU2           u2IntNumMax;       /* Maximum Receive Number for Interrupt    */
    BswU2           u2Extend2;         /* For future extension                    */
} Bsw_VCan_RxNodeTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_vcan_rx_init( void );
void   bsw_vcan_rx_RxIndication( BswU1 u1VController, BswU4 *ptData, BswU4 u4Length );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU2 bsw_vcan_rx_u2VirtualHrhNum;

extern BswConst BswU1  bsw_vcan_rx_u1RxNodeNum[];
extern BswConst Bsw_VCan_RxNodeTblType* BswConst bsw_vcan_rx_ptRxNodeIdTbl[];
extern BswConst Bsw_VCan_RxTblType bsw_vcan_stRxMessageTbl[];
extern BswConst BswU1  bsw_vcan_rx_u1VhrhNum[];
extern BswConst BswU2  bsw_vcan_rx_u2VhrhTop[];
extern BswConst BswU1  bsw_vcan_rx_u1RxVMboxTop[];
extern BswU2* BswConst bsw_vcan_rx_u2RxIntCount[];

extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl0[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl1[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl2[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl3[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl4[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl5[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl6[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl7[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl8[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl9[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl10[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl11[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl12[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl13[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl14[];
extern BswConst Bsw_VCan_RxNodeTblType bsw_vcan_stRxNodeTbl_VControl15[];

#endif  /* BSW_VCAN_RX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/03/21                                              */
/*  v2-1-0         :2022/07/07                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
