/* bsw_com_data_h_v2-2-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/DATA/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_DATA_H
#define BSW_COM_DATA_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_MSGST_INIT_VALUE        (BSW_COM_NO_RX)     /* Rx message is "NO_RX", but the Tx message is "FST_TX". */

/* Operate buffers */
#define BSW_COM_SHIFT_1BYTE            (8U)
#define BSW_COM_SHIFT_2BYTE            (16U)
#define BSW_COM_SHIFT_3BYTE            (24U)
#define BSW_COM_SHIFT_4BYTE            (32U)
#define BSW_COM_SHIFT_5BYTE            (40U)
#define BSW_COM_SHIFT_6BYTE            (48U)
#define BSW_COM_SHIFT_7BYTE            (56U)

#define BSW_COM_MSK_1BYTE              (0xFFU)

#define BSW_COM_SIZE_1BYTE             (8U)
#define BSW_COM_SIZE_2BYTE             (16U)
#define BSW_COM_SIZE_4BYTE             (32U)

#define BSW_COM_SIZE_32BIT             (32U)
#define BSW_COM_MSK_32BIT              (0xFFFFFFFFUL)

#define BSW_COM_SIZE_64BIT             (64U)

#define BSW_COM_DATPOS_0               (0U)
#define BSW_COM_DATPOS_1               (1U)
#define BSW_COM_DATPOS_2               (2U)
#define BSW_COM_DATPOS_3               (3U)
#define BSW_COM_DATPOS_4               (4U)
#define BSW_COM_DATPOS_5               (5U)
#define BSW_COM_DATPOS_6               (6U)
#define BSW_COM_DATPOS_7               (7U)
#define BSW_COM_DATPOS_8               (8U)

#define BSW_COM_u1UPPER5BITMASK        ((BswU1)0xF8)
#define BSW_COM_DATA_LEN_ROUNDUP       (7U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef BswU1       Bsw_Com_DataInfoType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                bsw_com_data_InitMsg( BswU2 u2SeqKind );
BswU1               bsw_com_data_ChkChPncUse( NetworkHandleType Network );
BswU1               bsw_com_data_ChkChPncUseNone( NetworkHandleType Network );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  BswU1               bsw_com_data_u1MsgStat[];             /* Message status         */
extern  BswU1               bsw_com_data_u1MsgBuf[];              /* Message buffers           */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
extern  BswConst BswU2                   bsw_com_rom_u2FAILSIZE;
extern  BswConst BswU2                   bsw_com_rom_u2MSGBUFSIZE;
extern  BswConst BswU2                   bsw_com_rom_u2BACKUPPDUNUM;
extern  BswConst BswU1                   bsw_com_rom_u1CPUBYTEORDERTYPE;

extern  BswConst BswU1                   bsw_com_data_u1MsgBufInit[];            /* Message buffer initial value table             */
extern  BswConst BswU1                   bsw_com_data_u1MsgBufFail[];            /* Fail safe value table                     */
extern  BswConst BswU1                   bsw_com_data_u1FailMskTbl[];            /* Fail safe value mask table               */
extern  BswConst Bsw_Com_DataInfoType    bsw_com_stDataInfoTbl[];                /* Data information table                           */
extern  BswConst PduIdType               bsw_com_u2DataHdl2MsgHdl[];             /* Message ID conversion dictionary for data ID               */
extern  BswConst PduIdType               bsw_com_data_u2BackupPduId[];           /* I-PDU ID of the backup target                     */

extern  void            (* BswConst bsw_com_rom_ptAlvCntFuncPosTx[])( PduIdType u2PduId, Bsw_Com_AlvCntPosType *ptAlvCntPos );
extern  BswU1           (* BswConst bsw_com_rom_ptChkChPncUseFunc)( NetworkHandleType Network );

#endif /* BSW_COM_DATA_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/07/11                                             */
/*  v1-2-0          :2019/10/04                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/08/10                                             */
/*  v2-2-0          :2023/05/23                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
