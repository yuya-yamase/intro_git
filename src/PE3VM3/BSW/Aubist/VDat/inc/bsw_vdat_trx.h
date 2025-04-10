/* bsw_vdat_trx_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VDAT/TRX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_VDAT_TRX_H
#define BSW_VDAT_TRX_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VDAT_FUNC_TBL_NUM           (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef Bsw_VDat_ReturnType (*Bsw_VDat_InitNodeType)( BswU1 u1ConnectionId, BswU1 u1NodeId );
typedef void                (*Bsw_VDat_StartNodeType)( BswU1 u1ConnectionId, BswU1 u1NodeId );
typedef Bsw_VDat_ReturnType (*Bsw_VDat_ReceiveType)( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4BufSize, BswU4 *u4DataLength );
typedef Bsw_VDat_ReturnType (*Bsw_VDat_TransmitType)( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4DataLength );
typedef void                (*Bsw_VDat_DeInitNodeType)( BswU1 u1ConnectionId, BswU1 u1NodeId );

typedef struct
{
    Bsw_VDat_InitNodeType               ptInitNode;
    Bsw_VDat_StartNodeType              ptStartNode;
    Bsw_VDat_ReceiveType                ptReceive;
    Bsw_VDat_TransmitType               ptTransmit;
    Bsw_VDat_DeInitNodeType             ptDeInitNode;
} Bsw_VDat_FuncTblType;

typedef Bsw_VDat_ReturnType (*Bsw_VDat_InitNodePubType)( BswU1 ConnectionId, BswU1 NodeId );
typedef void (*Bsw_VDat_StartNodePubType)( BswU1 ConnectionId, BswU1 NodeId );
typedef Bsw_VDat_ReturnType (*Bsw_VDat_ReceivePubType)( BswU1 ConnectionId, BswU1 NodeId, BswU4* Data, BswU4 BufSize, BswU4* Size );
typedef Bsw_VDat_ReturnType (*Bsw_VDat_TransmitPubType)( BswU1 ConnectionId, BswU1 NodeId, BswU4* Data, BswU4 Size );
typedef void (*Bsw_VDat_DeInitNodePubType)( BswU1 ConnectionId, BswU1 NodeId );

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
Bsw_VDat_ReturnType bsw_vdat_trx_InitNodeNone( BswU1 u1ConnectionId, BswU1 u1NodeId );
void                bsw_vdat_trx_StartNodeNone( BswU1 u1ConnectionId, BswU1 u1NodeId );
Bsw_VDat_ReturnType bsw_vdat_trx_ReceiveNone( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4BufSize, BswU4 *u4DataLength );
Bsw_VDat_ReturnType bsw_vdat_trx_TransmitNone( BswU1 u1ConnectionId, BswU1 u1NodeId, BswU4 *ptData, BswU4 u4DataLength );
void                bsw_vdat_trx_DeInitNodeNone( BswU1 u1ConnectionId, BswU1 u1NodeId );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_00[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_01[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_02[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_03[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_04[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_05[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_06[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_07[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_08[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_09[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_10[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_11[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_12[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_13[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_14[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_15[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_16[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_17[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_18[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_19[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_20[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_21[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_22[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_23[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_24[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_25[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_26[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_27[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_28[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_29[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_30[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_31[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_32[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_33[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_34[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_35[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_36[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_37[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_38[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_39[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_40[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_41[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_42[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_43[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_44[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_45[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_46[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_47[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_48[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_49[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_50[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_51[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_52[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_53[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_54[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_55[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_56[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_57[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_58[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_59[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_60[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_61[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_62[];
extern BswConst BswU4 bsw_vdat_u4QueueIDTbl_63[];

extern BswConst BswU1 bsw_vdat_trx_u1ConnectionNum;
extern BswConst BswU1 bsw_vdat_trx_u1NodeNum[];
extern BswConst BswU1 bsw_vdat_trx_u1ComFunc[];
extern BswConst BswU1 bsw_vdat_trx_u1IpcBusId[];
extern BswConst BswU4 * BswConst bsw_vdat_trx_u4QueueIDTbl[];
extern BswConst Bsw_VDat_FuncTblType bsw_vdat_trx_stFuncTbl[];

extern BswConst Bsw_VDat_InitNodePubType    bsw_vdat_InitNodePubFunc;
extern BswConst Bsw_VDat_StartNodePubType   bsw_vdat_StartNodePubFunc;
extern BswConst Bsw_VDat_ReceivePubType     bsw_vdat_ReceivePubFunc;
extern BswConst Bsw_VDat_TransmitPubType    bsw_vdat_TransmitPubFunc;
extern BswConst Bsw_VDat_DeInitNodePubType  bsw_vdat_DeInitNodePubFunc;

#endif  /* BSW_VDAT_TRX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/04/08                                             */
/*  v2-1-0          :2022/05/24                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
