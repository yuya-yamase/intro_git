/* bsw_vcan_st_h_v3-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/ST/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_VCAN_ST_H
#define     BSW_VCAN_ST_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VCAN_u1OK                     ((BswU1)0U)         /* OK                       */
#define BSW_VCAN_u1NG                     ((BswU1)1U)         /* NG                       */
#define BSW_VCAN_u1OVERWRITE_OCCURS       ((BswU1)2U)         /* Overwrite Occurs         */

/* Controller ID */
#define BSW_VCAN_u1VIRTUAL_CH_MASK        ((BswU1)0x80U)      /* Virtual ch mask  */
#define BSW_VCAN_u1VMCTRL_ID_MASK         ((BswU1)0x7FU)      /* Virtual controller ID mask  */

/* CAN controller state */
#define BSW_VCAN_u2ST_CTRL_UNINIT        ((BswU2)0x6E91U)     /* Uninitialized        */
#define BSW_VCAN_u2ST_CTRL_INIT          ((BswU2)0x6D92U)     /* Initialized        */
#define BSW_VCAN_u2ST_CTRL_STOPPED       ((BswU2)0x6B94U)     /* Stoped Communication        */
#define BSW_VCAN_u2ST_CTRL_STARTED       ((BswU2)0x57A8U)     /* Started Communication          */

/* Virtual communication data position */
#define BSW_VCAN_DATAPOS_DATACANID31_24     (0U)
#define BSW_VCAN_DATAPOS_DATACANID23_16     (1U)
#define BSW_VCAN_DATAPOS_DATACANID15_8      (2U)
#define BSW_VCAN_DATAPOS_DATACANID7_0       (3U)
#define BSW_VCAN_DATAPOS_DATADLC0           (4U)
#define BSW_VCAN_DATAPOS_DATADLC1           (5U)
#define BSW_VCAN_DATAPOS_DATAPAYLOADTOP     (8U)

/* Virtual communication data size */
#define BSW_VCAN_u4LENGTH_DATAFRAMEMIN      (8UL)

/* Bit shift */
#define BSW_VCAN_SHIFT_1BYTE            (8U)
#define BSW_VCAN_SHIFT_2BYTE            (16U)
#define BSW_VCAN_SHIFT_3BYTE            (24U)
#define BSW_VCAN_SHIFT_2BIT             (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Function type of virtual communication module */
typedef void    (*Bsw_VCan_InitNodeType)( BswU1 u1VController );
typedef void    (*Bsw_VCan_StartNodeType)( BswU1 u1VController );
typedef BswU1   (*Bsw_VCan_TransmitType)( BswU1 u1VBusId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4 u4TxMsgLength );
typedef BswU1   (*Bsw_VCan_ReceiveType)( BswU1 u1VBusId, BswU4 u4RxVNodeId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4* u4RxMsgLength );
typedef void    (*Bsw_VCan_DeInitNodeType)( BswU1 u1VController );

/* Structure for defining functions of the virtual communication module */
typedef struct
{
    Bsw_VCan_InitNodeType              ptInitNode;            /* Initialize Node    */
    Bsw_VCan_StartNodeType             ptStartNode;           /* Start Node         */
    Bsw_VCan_TransmitType              ptTransmit;            /* Transmit           */
    Bsw_VCan_ReceiveType               ptReceive;             /* Receive            */
    Bsw_VCan_DeInitNodeType            ptDeInitNode;          /* Shutdown Node      */
}Bsw_VCan_IpcFuncTblType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* Dummy function */
void    bsw_vcan_st_InitNodeNone( BswU1 u1VController );
void    bsw_vcan_st_StartNodeNone( BswU1 u1VController );
BswU1   bsw_vcan_st_ReceiveNone( BswU1 u1VBusId, BswU4 u4RxVNodeId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4* u4RxMsgLength );
BswU1   bsw_vcan_st_TransmitNone( BswU1 u1VBusId, BswU4 u4TxVNodeId, BswU4 *ptData, BswU4 u4TxMsgLength );
void    bsw_vcan_st_DeInitNodeNone( BswU1 u1VController );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/* Virtual ch */
extern BswU2                     bsw_vcan_st_u2ControllerStatus[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1 bsw_vcan_st_u1VirtualCtrlNum;

extern BswConst BswU1 bsw_vcan_u1SwChIpcVirtualTbl[];
extern BswConst Bsw_VCan_IpcFuncTblType bsw_vcan_stChIpcTbl[];

#endif  /* BSW_VCAN_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/04                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
