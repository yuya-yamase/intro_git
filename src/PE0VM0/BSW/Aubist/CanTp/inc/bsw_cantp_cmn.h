/* bsw_cantp_cmn_h_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/CMN/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_CMN_H
#define BSW_CANTP_CMN_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*---------------------------*/
/* Internal processing value */
/*---------------------------*/
/* CanTp standard return value */
#define BSW_CANTP_E_OK                      (0U)
#define BSW_CANTP_E_NOT_OK                  (1U)

/* Define value for the bit operation */
#define BSW_CANTP_BIT0                      (0x01U)                     /* Bit 0 ON                  */
#define BSW_CANTP_BITNUM_U1                 (8U)                        /* U1 data bit num           */
#define BSW_CANTP_BIT_SHIFT8                (8U)                        /*  8Bit Shift               */
#define BSW_CANTP_BIT_SHIFT16               (16U)                       /* 16Bit Shift               */
#define BSW_CANTP_BIT_SHIFT24               (24U)                       /* 24Bit Shift               */
#define BSW_CANTP_u2LOW8BITMASK             ((uint16)0x00FFU)           /* 16bit data low  8bit mask */
#define BSW_CANTP_u4LOW8BITMASK             (0x000000FFUL)              /* 32bit data low  8bit mask */

/* Offset value for the sequence data operation */
#define BSW_CANTP_OFFSET0                   (0U)                        /* OFFSET0                   */
#define BSW_CANTP_OFFSET1                   (1U)                        /* OFFSET1                   */
#define BSW_CANTP_OFFSET2                   (2U)                        /* OFFSET2                   */
#define BSW_CANTP_OFFSET3                   (3U)                        /* OFFSET3                   */
#define BSW_CANTP_OFFSET4                   (4U)                        /* OFFSET4                   */
#define BSW_CANTP_OFFSET5                   (5U)                        /* OFFSET5                   */
#define BSW_CANTP_OFFSET6                   (6U)                        /* OFFSET6                   */
#define BSW_CANTP_OFFSET7                   (7U)                        /* OFFSET7                   */

/* Invalid ID */
#define BSW_CANTP_u2NPDUID_NA               ((uint16)0xFFFFU)           /* Invalid NPduId            */
#define BSW_CANTP_u2NSDUID_NA               ((uint16)0xFFFFU)           /* Invalid NSduId            */

/* Addressing format */
#define BSW_CANTP_ADDRESSING_NUM            (5U)                        /* Number of Address format  */

/* FFDL */
#define BSW_CANTP_u4FFDL_4095               (4095UL)                    /* FFDL(4095)                */
#define BSW_CANTP_u4FFDL_4096               (4096UL)                    /* FFDL(4096)                */

/* Define value for NPCI */
#define BSW_CANTP_u1PCI_SF                  ((uint8)0x00U)              /* SF                        */
#define BSW_CANTP_u1PCI_FF                  ((uint8)0x10U)              /* FF                        */
#define BSW_CANTP_u1PCI_CF                  ((uint8)0x20U)              /* CF                        */
#define BSW_CANTP_u1PCI_FC                  ((uint8)0x30U)              /* FC                        */
#define BSW_CANTP_u1PCI_UNKNOWN             ((uint8)0xFFU)              /* Unknow PCI                */

#define BSW_CANTP_u1PCI_FIRSTBYTE_SF_ES     ((uint8)0x00U)              /* SF(CAN_DL > 8)            */
#define BSW_CANTP_u1PCI_FIRSTBYTE_FF_ES     ((uint8)0x10U)              /* FF(FF_DL > 4095)          */
#define BSW_CANTP_u1PCI_SECNDBYTE_FF_ES     ((uint8)0x00U)              /* FF(FF_DL > 4095)          */

/* Size of N_PCI */
#define BSW_CANTP_u1PCI_SIZE_SF             ((uint8)1U)                 /* SF                        */
#define BSW_CANTP_u1PCI_SIZE_SF_ES          ((uint8)2U)                 /* SF(CAN_DL > 8)            */
#define BSW_CANTP_u1PCI_SIZE_FF             ((uint8)2U)                 /* FF                        */
#define BSW_CANTP_u1PCI_SIZE_FF_ES          ((uint8)6U)                 /* FF(FF_DL > 4095)          */
#define BSW_CANTP_u1PCI_SIZE_CF             ((uint8)1U)                 /* CF                        */
#define BSW_CANTP_u1PCI_SIZE_FC             ((uint8)3U)                 /* FC                        */

/* Mask value for N_PCI */
#define BSW_CANTP_u1MASK_PCI                ((uint8)0xF0U)              /* Mask value for PCI        */
#define BSW_CANTP_u1MASK_SF_SFDL            ((uint8)0x0FU)              /* Mask value for SFDL       */
#define BSW_CANTP_u1MASK_FF_FFDL_H          ((uint8)0x0FU)              /* Mask value for FFDL-High  */
#define BSW_CANTP_u1MASK_CF_SN              ((uint8)0x0FU)              /* Mask value for SFDL       */
#define BSW_CANTP_u1MASK_FC_FS              ((uint8)0x0FU)              /* Mask value for FS         */

/* Sequence number */
#define BSW_CANTP_u1SN_FIRST                ((uint8)0x01U)              /* SN value for First CF     */
#define BSW_CANTP_u1SN_INIT                 ((uint8)0xFFU)              /* Initial value for SN RAM  */

/* Flow status for sender unit */
#define BSW_CANTP_u1FS_SENDER_CTS           ((Bsw_CanTp_st_FSType)0x00U)       /* Continue to send          */
#define BSW_CANTP_u1FS_SENDER_WT            ((Bsw_CanTp_st_FSType)0x01U)       /* Wait                      */
#define BSW_CANTP_u1FS_SENDER_OVFL          ((Bsw_CanTp_st_FSType)0x02U)       /* Overflow                  */

/* Flow status for receiver unit */
#define BSW_CANTP_u1FS_RECEIVER_CTS         ((Bsw_CanTp_st_FSType)0xF0U)       /* Continue to send          */
#define BSW_CANTP_u1FS_RECEIVER_WT          ((Bsw_CanTp_st_FSType)0xE1U)       /* Wait                      */
#define BSW_CANTP_u1FS_RECEIVER_OVFL        ((Bsw_CanTp_st_FSType)0xD2U)       /* Overflow                  */

/* data length */
#define BSW_CANTP_u1CAN_DL_INVAL            ((uint8)0U)

#define BSW_CANTP_u1CAN_DL_01               ((uint8)1U)
#define BSW_CANTP_u1CAN_DL_02               ((uint8)2U)
#define BSW_CANTP_u1CAN_DL_03               ((uint8)3U)
#define BSW_CANTP_u1CAN_DL_04               ((uint8)4U)
#define BSW_CANTP_u1CAN_DL_05               ((uint8)5U)
#define BSW_CANTP_u1CAN_DL_06               ((uint8)6U)
#define BSW_CANTP_u1CAN_DL_07               ((uint8)7U)
#define BSW_CANTP_u1CAN_DL_08               ((uint8)8U)
#define BSW_CANTP_u1CAN_DL_10               ((uint8)10U)
#define BSW_CANTP_u1CAN_DL_12               ((uint8)12U)
#define BSW_CANTP_u1CAN_DL_16               ((uint8)16U)
#define BSW_CANTP_u1CAN_DL_20               ((uint8)20U)
#define BSW_CANTP_u1CAN_DL_24               ((uint8)24U)
#define BSW_CANTP_u1CAN_DL_32               ((uint8)32U)
#define BSW_CANTP_u1CAN_DL_48               ((uint8)48U)
#define BSW_CANTP_u1CAN_DL_64               ((uint8)64U)
#define BSW_CANTP_u1CAN_DL_65               ((uint8)65U)

#define BSW_CANTP_u4NDATA_LEN_01            (1UL)

/* MainFunction cycle count */
#define BSW_CANTP_u2MAIN_CYCLE_SINGLE       ((uint16)1U)
#define BSW_CANTP_u2MAIN_CYCLE_DOUBLE       ((uint16)2U)

/* RAM Fail */
#define BSW_CANTP_u1RAMERR                  ((uint8)0x0FU)
#define BSW_CANTP_u1ERRNONE                 ((uint8)0xF0U)

/* padding size for structure */
#define BSW_CANTP_PAD_SIZE2                 (2U)
#define BSW_CANTP_PAD_SIZE3                 (3U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Bsw_CanTp_ReturnType;       /* CanTp Common Return Type             */

typedef struct
{
    uint8 *     ptSduData;              /* uint8-pointer to the SDU of the PDU  */
    uint32      u4SduLength;            /* length of the SDU in bytes           */
}Bsw_CanTp_PduInfoType;

typedef struct
{
    uint16  u2BS;                       /* Receiver Block Size                  */
    uint16  u2STmin;                    /* Receiver STmin                       */
}Bsw_CanTp_BSSTminType;

#if( BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE )
typedef struct
{
    uint16  u2CfgTblIdx;                /* RxNSdu Config Table Index            */
    uint8   u1ParentChId;               /* Parent Channel Id                    */
    uint8   u1Extend;                   /* Extend                               */

    uint16  u2NSduId;                   /* NSduId                               */
    uint16  u2NPduId;                   /* NPduId                               */
    uint16  u2FcNPduId;                 /* FC NPduId                            */
    uint16  u2PduR_RxIndId;             /* PduR RxIndication Id                 */
    uint16  u2CanIf_FcPduId;            /* CanIf PduId                          */

    uint8   u1AddressFormat;            /* Addressing Format                    */
    uint8   u1TaType;                   /* TaType                               */
    uint8   u1NTa;                      /* NTa                                  */
    uint8   u1NSa;                      /* NSa                                  */

    uint16  u2NarCycle;                 /* N_Ar(MainFunction cycle count)       */
    uint16  u2NcrCycle;                 /* N_Cr(MainFunction cycle count)       */

    uint8   u1BlockSize;                /* BlockSize                            */
    uint8   u1STmin;                    /* STmin                                */
    uint16  u2WFTMax;                   /* WFTmax                               */
    uint8   u1PaddingAct;               /* SF/FF/CF RX PaddingActivation        */
    uint8   u1FcTxPaddingAct;           /* FC Tx PaddingActivation              */
    uint8   u1NAe;                      /* NAe                                  */
    uint8   u1Priority;                 /* Priority                             */
}Bsw_CanTp_RxNSduCfgType;

typedef struct
{
    uint16  u2CfgTblIdx;                /* TxNSdu Config Table Index            */
    uint8   u1ParentChId;               /* Parent Channel Id                    */
    uint8   u1Extend1;                  /* Extend                               */

    uint16  u2NSduId;                   /* NSduId                               */
    uint16  u2NPduId;                   /* NPduId                               */
    uint16  u2FcNPduId;                 /* FC NPduId                            */
    uint16  u2PduR_TxConfId;            /* PduR TxConfirmation Id               */
    uint16  u2CanIf_PduId;              /* CanIf PduId                          */

    uint8   u1AddressFormat;            /* Addressing Format                    */
    uint8   u1TaType;                   /* TaType                               */
    uint8   u1NTa;                      /* NTa                                  */
    uint8   u1NSa;                      /* NSa                                  */

    uint16  u2NasCycle;                 /* N_As(MainFunction cycle count)       */
    uint16  u2NbsCycle;                 /* N_Bs(MainFunction cycle count)       */

    uint8   u1TxNPduLength;             /* Transmit NPdu Length                 */
    uint8   u1TxCancel;                 /* Transmit Cancel                      */
    uint8   u1NewMsgRxInLastMsgTx;      /* New Msg Rx Handling In Last Msg Tx   */
    uint8   u1PaddingAct;               /* SF/FF/CF TX PaddingActivation        */
    uint8   u1FcRxPaddingAct;           /* FC Rx PaddingActivation              */
    uint8   u1NAe;                      /* NAe                                  */
    uint8   u1Priority;                 /* Priority                             */
    uint8   u1Extend2;                  /* Extend                               */
}Bsw_CanTp_TxNSduCfgType;

#else /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */
typedef struct
{
    uint16  u2NPduId;                   /* NPduId                               */
    uint16  u2CanIf_FcPduId;            /* CanIf PduId                          */

    uint8   u1ParentChId;               /* Parent Channel Id                    */

    uint8   u1AddressFormat;            /* Addressing Format                    */
    uint8   u1TaType;                   /* TaType                               */
    uint8   u1NTa;                      /* NTa                                  */
    uint8   u1NSa;                      /* NSa                                  */

    uint8   u1RxParamPtn;               /* Rx Parameter Pattern                 */

    uint8   u1NAe;                      /* NAe                                  */
    uint8   u1Priority;                 /* Priority                             */
}Bsw_CanTp_RxNSduCfgType;

typedef struct
{
    uint16  u2FcNPduId;                 /* FC NPduId                            */
    uint16  u2CanIf_PduId;              /* CanIf PduId                          */

    uint8   u1ParentChId;               /* Parent Channel Id                    */

    uint8   u1AddressFormat;            /* Addressing Format                    */
    uint8   u1TaType;                   /* TaType                               */
    uint8   u1NTa;                      /* NTa                                  */
    uint8   u1NSa;                      /* NSa                                  */

    uint8   u1TxParamPtn;               /* Tx Parameter Pattern                 */

    uint8   u1NAe;                      /* NAe                                  */
    uint8   u1Priority;                 /* Priority                             */
}Bsw_CanTp_TxNSduCfgType;

#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION != BSW_USE */

typedef struct
{
    uint16  u2NarCycle;                 /* N_Ar(MainFunction cycle count)       */
    uint16  u2NcrCycle;                 /* N_Cr(MainFunction cycle count)       */

    uint8   u1BlockSize;                /* BlockSize                            */
    uint8   u1STmin;                    /* STmin                                */
    uint16  u2WFTMax;                   /* WFTmax                               */
    uint8   u1PaddingAct;               /* SF/FF/CF RX PaddingActivation        */
    uint8   u1FcTxPaddingAct;           /* FC Tx PaddingActivation              */
}Bsw_CanTp_RxNSduParamType;

typedef struct
{
    uint16  u2NasCycle;                 /* N_As(MainFunction cycle count)       */
    uint16  u2NbsCycle;                 /* N_Bs(MainFunction cycle count)       */

    uint8   u1TxNPduLength;             /* Transmit NPdu Length                 */
    uint8   u1PaddingAct;               /* SF/FF/CF TX PaddingActivation        */
    uint8   u1FcRxPaddingAct;           /* FC Rx PaddingActivation              */
    uint8   u1Extend;                   /* Extend                               */
}Bsw_CanTp_TxNSduParamType;

typedef struct
{
    BswConst Bsw_CanTp_RxNSduCfgType *  ptRxNSduCfgTbl;                 /* Pointer to RxNSduCfgTbl       */
    BswConst Bsw_CanTp_TxNSduCfgType *  ptTxNSduCfgTbl;                 /* Pointer to TxNSduCfgTbl       */
    uint16                              u2RxNSduNum;                    /* The number of RxNSdu          */
    uint16                              u2TxNSduNum;                    /* The number of TxNSdu          */
    uint8                               u1ChMode;                       /* Connection Channel Mode       */
    uint8                               u1ChId;                         /* Connection Channel ID         */
    uint8                               u1Padding[BSW_CANTP_PAD_SIZE2]; /* Padding                       */
}Bsw_CanTp_ChCfgType;

typedef struct
{
    BswConst Bsw_CanTp_ChCfgType *      ptChCfgTbl;                     /* Pointer to ChCfgTbl               */
    uint16                              u2MinRxNSduId;                  /* Minimum RxNSduId                  */
    uint16                              u2MinTxNSduId;                  /* Minimum TxNSduId                  */
    uint16                              u2MinRxNPduId;                  /* Minimum RxNPduId                  */
    uint16                              u2MinTxNPduId;                  /* Minimum TxNPduId                  */
    uint16                              u2TotalRxNSduNum;               /* The total number of RxNSdu        */
    uint16                              u2TotalTxNSduNum;               /* The total number of TxNSdu        */
    uint16                              u2TotalRxNPduNum;               /* The total number of RxNPdu        */
    uint16                              u2TotalTxNPduNum;               /* The total number of TxNPdu        */
    uint8                               u1ChNum;                        /* The number of Connection Channels */
    uint8                               u1Padding[BSW_CANTP_PAD_SIZE3]; /* Padding                           */
}Bsw_CanTp_CfgType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
BswConst Bsw_CanTp_CfgType *            bsw_cantp_cmn_GetConfigTbl( void );
BswConst Bsw_CanTp_RxNSduCfgType *      bsw_cantp_cmn_GetRxNSduCfgTbl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2RxNSduId );
BswConst Bsw_CanTp_TxNSduCfgType *      bsw_cantp_cmn_GetTxNSduCfgTbl( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2TxNSduId );
uint8                                   bsw_cantp_cmn_GetOptimizedCanDl( uint8 u1SduLen );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern uint8                            bsw_cantp_cmn_u1TxBuffer[BSW_CANTP_u1CAN_DL_64];
extern uint8                            bsw_cantp_cmn_u1ErrState;
#if( BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE )
extern uint16                           bsw_cantp_cmn_u2LatestRxNSduId;
#endif /* BSW_CANTP_CFG_LOWCOSTOPERATION == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst uint8   bsw_cantp_cmn_u1PciOffSetTbl[BSW_CANTP_ADDRESSING_NUM];

#endif /* BSW_CANTP_CMN_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/09/25                                              */
/*  v1-1-0         :2018/12/13                                              */
/*  v1-2-0         :2020/02/16                                              */
/*  v2-0-0         :2021/09/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
