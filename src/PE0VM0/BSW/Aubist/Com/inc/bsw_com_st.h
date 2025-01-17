/* bsw_com_st_h_v2-2-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/ST/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_ST_H
#define BSW_COM_ST_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_u1FAIL                 ((BswU1)0x5AU)  /* Detect COM failure   */
#define BSW_COM_u1NORMAL               ((BswU1)0xA5U)  /* Undetected COM failure */

#define BSW_COM_SEQ_INIT               (0x01U)                     /* Initialization                               */
#define BSW_COM_SEQ_CPUWKUP            (0x04U)                     /* Wake-up initialization                 */
#define BSW_COM_SEQ_RESET              (0x20U)                     /* Reset                             */

/* Status Position Definition */
#define BSW_COM_ST_SENDSTART           (0x04U)                     /* Waiting for transmission start(enable only inside COM)      */
#define BSW_COM_ST_CHGPRDIPDU          (0x08U)                     /* During period switching (Only used in COM)      */
#define BSW_COM_ST_FSTDELAY            (0x40U)                     /* Waiting for initial transmission (Use only in COM)      */
#define BSW_COM_ST_FST_TX              (0x01U)                     /* First transmission (Use only in COM. Tx message only.) */
#define BSW_COM_ST_TXRTY               (0x02U)                     /* Retrying to transmission (Use only in COM. Tx message only.) */

/* For inverting bits */
#define BSW_COM_u1ALLBIT               ((BswU1)0xFFU)
#define BSW_COM_u4ALLBIT               (0xFFFFFFFFUL)

#define BSW_COM_CH_MAX                 (32U)
#define BSW_COM_IPDUGRPSIZE_MAX        (BSW_COM_CH_MAX << 1U)

#define BSW_COM_s1D_OK                 ((Bsw_Com_RetStatusType)(0))
#define BSW_COM_s1D_TX_REQ_ERR         ((Bsw_Com_RetStatusType)(-5))
#define BSW_COM_s1D_ENABLE             ((Bsw_Com_RetStatusType)(-12))
#define BSW_COM_s1D_DISABLE            ((Bsw_Com_RetStatusType)(-13))
#define BSW_COM_s1D_DLL_ERR            ((Bsw_Com_RetStatusType)(-19))
#define BSW_COM_s1D_NOT_REQ            ((Bsw_Com_RetStatusType)(-21))
#define BSW_COM_s1D_OK_PERIOD          ((Bsw_Com_RetStatusType)(1))
#define BSW_COM_s1D_OK_EVENT           ((Bsw_Com_RetStatusType)(2))
#define BSW_COM_s1D_EMPTY              ((Bsw_Com_RetStatusType)(-20))

#define BSW_COM_u2TIMJIT_CNTIMMAFTRSET ((BswU2)1U)

#define BSW_COM_u1IPDUGROUP_NONE       ((BswU1)BSW_COM_IPDUGROUP_NONE)
#define BSW_COM_u1IPDUGROUP_BAT        ((BswU1)BSW_COM_IPDUGROUP_BAT)
#define BSW_COM_u1IPDUGROUP_ACC        ((BswU1)BSW_COM_IPDUGROUP_ACC)
#define BSW_COM_u1IPDUGROUP_IG         ((BswU1)BSW_COM_IPDUGROUP_IG)
#define BSW_COM_u1IPDUGROUP_USER1      ((BswU1)BSW_COM_IPDUGROUP_USER1)
#define BSW_COM_u1IPDUGROUP_USER2      ((BswU1)BSW_COM_IPDUGROUP_USER2)
#define BSW_COM_u1IPDUGROUP_USER3      ((BswU1)BSW_COM_IPDUGROUP_USER3)
#define BSW_COM_u1IPDUGROUP_USER4      ((BswU1)BSW_COM_IPDUGROUP_USER4)
#define BSW_COM_u1IPDUGROUP_USER5      ((BswU1)BSW_COM_IPDUGROUP_USER5)

#define BSW_COM_DUMMY_SIZE             (1U)            /* Structure dummy size */

#define BSW_COM_PNCMAXNUM              (64U)                        /* Maximum number of PNCs           */
#define BSW_COM_PNC_REQNUM             (BSW_COM_PNCMAXNUM >> 5U)    /* Number of 4 bytes for PNC (bit)  */
#define BSW_COM_PNCNUM_NONE            (0U)            /* Number of PNCIDs when PNC is not used */

#define BSW_COM_u1INDEX_0              ((BswU1)0U)     /* Index for array access */
#define BSW_COM_u1INDEX_1              ((BswU1)1U)     /* Index for array access */

/* Change in I-PDU group status */
#define BSW_COM_u1STATBIT_OFF          ((BswU1)0x01)   /* Status:OFF             */
#define BSW_COM_u1STATBIT_ON           ((BswU1)0x02)   /* Status:ON              */
#define BSW_COM_u1STATBIT_OFFCHG       ((BswU1)0x10)   /* Status:ON->OFF         */
#define BSW_COM_u1STATBIT_ONCHG        ((BswU1)0x20)   /* Status:OFF->ON         */

#define BSW_COM_u1STATCHG_OFF          (BSW_COM_u1STATBIT_OFF)                              /* No change(OFF)         */
#define BSW_COM_u1STATCHG_ON           (BSW_COM_u1STATBIT_ON)                               /* No change(NO)          */
#define BSW_COM_u1STATCHG_TOOFF        (BSW_COM_u1STATBIT_OFFCHG)                           /* Changed(OFF)           */
#define BSW_COM_u1STATCHG_TOON         (BSW_COM_u1STATBIT_ONCHG)                            /* Changed(ON)            */

#define BSW_COM_u1STATCHG_CHANGED      (BSW_COM_u1STATBIT_ONCHG|BSW_COM_u1STATBIT_OFFCHG)   /* Changed(ON or OFF)     */
#define BSW_COM_u1STATCHG_NOCHANGE     ((BswU1)0x00U)                                       /* No Change              */

#define BSW_COM_u1PNCIPDU_OFF          (BSW_COM_u1STATBIT_OFF)   /* PNC I-PDU condision : not available */
#define BSW_COM_u1PNCIPDU_ON           (BSW_COM_u1STATBIT_ON)    /* PNC I-PDU condision : available     */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef sint8               Bsw_Com_RetStatusType;

typedef BswU2               Bsw_Com_TickTimeType;
typedef BswU1               Bsw_Com_NetworkType;

typedef struct {
    Bsw_Com_TickTimeType    u2PeriodTime;
    BswU1                   u1Network;
    BswU1                   u1Extend;
    BswU2                   u2MsgSize;
    BswU1                   u1TxFunc;
    BswU1                   u1Hook;
} Bsw_Com_MsgInfoType;

typedef struct {
    PduIdType               u2Top;
    BswU2                   u2MsgNum;
} Bsw_Com_NetInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
void                        bsw_com_st_InitCom( BswU2 u2SeqKind );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern  BswConst BswU2      bsw_com_rom_u2MSGNUM;
extern  BswConst BswU2      bsw_com_rom_u2TXMSGNUM;
extern  BswConst BswU1      bsw_com_rom_u1NETWORKNUM;
extern  BswConst BswU1      bsw_com_rom_u1CHGPERIODUSE;
extern  BswConst BswU2      bsw_com_rom_u2CHGPRDCH[];

extern BswConst Bsw_Com_MsgInfoType     bsw_com_stMsgInfoTbl[];            /* Message information                 */
extern BswConst BswU1                   bsw_com_u1SysStatTbl[];            /* System status table                 */
extern BswConst Bsw_Com_MsgOffsetType   bsw_com_u2MsgOffsTbl[];            /* Message buffer offset table         */
extern BswConst BswU4                   bsw_com_u4PncStatTbl[][BSW_COM_PNC_REQNUM]; /* PNC Awake factor table     */
extern BswConst BswU1                   bsw_com_rom_u1PncNum[];            /* Target PNC count for control        */

/* Unit internal public definition */
extern  void                (* BswConst bsw_com_rom_ptInitAllTxReqFunc)( void );
extern  void                (* BswConst bsw_com_rom_ptInitSndNTimFunc)( void );
extern  void                (* BswConst bsw_com_rom_ptInitChgPrdFunc)( void );

#endif /* BSW_COM_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/11/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/06/08                                             */
/*  v2-2-0          :2023/06/08                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
