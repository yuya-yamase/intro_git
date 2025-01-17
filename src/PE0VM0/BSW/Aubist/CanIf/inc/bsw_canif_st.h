/* bsw_canif_st_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANIF/ST/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_ST_H
#define     BSW_CANIF_ST_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANIF_OK                   (0U)            /* OK                       */
#define BSW_CANIF_NG                   (1U)            /* NG                       */
#define BSW_CANIF_WAIT                 (2U)            /* WAIT                     */
#define BSW_CANIF_WARNING              (3U)            /* WARNING                  */
#define BSW_CANIF_FAIL_REGSTUCK        (8U)            /* Stuck Register Detected  */
#define BSW_CANIF_FAIL_UNUSEDREGSTUCK    (9U)          /* Stuck Register Detected(unused mbox)  */
#define BSW_CANIF_ON                   (1U)            /* ON                       */
#define BSW_CANIF_OFF                  (0U)            /* OFF                      */
#define BSW_CANIF_u4EXTCANID_BIT       (0x80000000UL)  /* Extended CAN ID Bit      */
#define BSW_CANIF_ILLEGAL              (99U)           /* ILLEGAL                  */
#define BSW_CANIF_u1COMP_BIT_TX        ((BswU1)0x80U)  /* Component:TX (for receiving)   */

/* For setting message information */
#define BSW_CANIF_CHECKSUM_USE         (0x01U)
#define BSW_CANIF_CHECKSUM_NOUSE       (0x00U)
#define BSW_CANIF_NMMSG_USE            (0x02U)
#define BSW_CANIF_NMMSG_NOUSE          (0x00U)
#define BSW_CANIF_MSGID_USE            (0x04U)
#define BSW_CANIF_MSGID_NOUSE          (0x00U)
#define BSW_CANIF_AVCLAN_USE           (0x08U)
#define BSW_CANIF_AVCLAN_NOUSE         (0x00U)
#define BSW_CANIF_PRETRXMSG_USE        (0x10U)
#define BSW_CANIF_PRETRXMSG_NOUSE      (0x00U)

#define BSW_CANIF_CHECKSUM_MASK        (0x01U)
#define BSW_CANIF_NMMSG_MASK           (0x02U)
#define BSW_CANIF_MSGID_MASK           (0x04U)
#define BSW_CANIF_AVCLAN_MASK          (0x08U)
#define BSW_CANIF_PRETRXMSG_MASK       (0x10U)

/* Size for dummy array */
#define BSW_CANIF_TBL_DUMMY_SIZE        (1U)

/* Size of the array guard */
#define BSW_CANIF_TBL_SNTNL_SIZE        (1U)

/* Maximum number of upper component */
#define BSW_CANIF_TBL_MAX_UPCMPNUM      (6U)

/* Index for array access */
/* Use BswU1 type macro to avoid increasing processing time and stack consumption */
#define BSW_CANIF_TBL_u1IDX_0           ((BswU1)(0U))
#define BSW_CANIF_TBL_u1IDX_1           ((BswU1)(1U))
#define BSW_CANIF_TBL_u1IDX_2           ((BswU1)(2U))
#define BSW_CANIF_TBL_u1IDX_3           ((BswU1)(3U))
#define BSW_CANIF_TBL_u1IDX_4           ((BswU1)(4U))
#define BSW_CANIF_TBL_u1IDX_5           ((BswU1)(5U))
#define BSW_CANIF_TBL_u1IDX_6           ((BswU1)(6U))
#define BSW_CANIF_TBL_u1IDX_7           ((BswU1)(7U))

/* For array access */
#define BSW_CANIF_TBL_u1NEXT_IDX        ((BswU1)(1U))

/* For queue operation */
#define BSW_CANIF_SHIFT_1BIT            (1U)
#define BSW_CANIF_SHIFT_2BIT            (2U)
#define BSW_CANIF_SHIFT_3BIT            (3U)
#define BSW_CANIF_SHIFT_1BYTE           (8U)
#define BSW_CANIF_SHIFT_2BYTE           (16U)
#define BSW_CANIF_SHIFT_3BYTE           (24U)
#define BSW_CANIF_QUE_INFO_POS          (0U)
#define BSW_CANIF_QUE_INFO_MIR_POS      (1U)
#define BSW_CANIF_QUE_CANID_POS         (2U)
#define BSW_CANIF_QUE_DATA_POS          (3U)
#define BSW_CANIF_QUE_HEADER_SIZE       (3U)
#define BSW_CANIF_QUE_INFO_SIZE         (2U)
#define BSW_CANIF_QUE_MINMSG_SIZE       (5U)
#define BSW_CANIF_u4QUE_EMPTY           (0xFFFFFFFFUL)
#define BSW_CANIF_DATA_LEN_ROUNDUP      (7U)
#define BSW_CANIF_TBL_COPY_SIZE         (4U)
#define BSW_CANIF_u1ALLBIT              ((BswU1)0xFFU)
#define BSW_CANIF_u4ALLBIT              (0xFFFFFFFFUL)
#define BSW_CANIF_u4VERIFY_KEY_B32      (0xFFFFFFFFUL)
#define BSW_CANIF_MSGSIZE_8             (8U)

#define BSW_CANIF_MSK_1BYTE             (0xFFU)

/* Message type identifier                      */
/* x0xx xxxx xxxx xxxx   CAN message       */
/* x1xx xxxx xxxx xxxx   CAN FD messages    */
#define BSW_CANIF_u4MSK_MSGFMTBIT       (0x40000000UL)
#define BSW_CANIF_u4FD_MSGFMTBIT_OFF    (0x00000000UL)

#define BSW_CANIF_u4MSK_CAN11BITID      (0x000007FFUL)
#define BSW_CANIF_u4MSK_CAN29BITID      (0x1FFFFFFFUL)

#define BSW_CANIF_SET_EVENTBIT          (0x80U)
#define BSW_CANIF_SET_EVENTBIT_NOT      (0x7FU)

/* Maximum message size */
#define BSW_CANIF_MSGSIZE_MAX           (8U)
#define BSW_CANIF_MSGSIZE_MAX_CANFD     (64U)

/* Define the data position */
#define BSW_CANIF_1BYTE_POS_DATA0       (0U)
#define BSW_CANIF_1BYTE_POS_DATA1       (1U)

/* Controller ID identifier mask value */
#define BSW_CANIF_MSK_CTRLID_ATTRIBUTE  (0x80U)

/* HOH identifier mask value */
#define BSW_CANIF_MSK_HOH_VIRTUAL       (0x8000U)

/****************************************************/
/* State value                                           */
/*--------------------------------------------------*/
/* -Identify the state with two or more bits                       */
/* -All 0 is not used                              */
/* -All 1 is not used                              */
/****************************************************/
/* Internal CANIF status */
#define BSW_CANIF_ST_CANIFSTS_MPUINIT          (0x6E91U)   /* MPU-INIT             */
#define BSW_CANIF_ST_CANIFSTS_INIT             (0x6D92U)   /* INIT                 */
#define BSW_CANIF_ST_CANIFSTS_READY            (0x6B94U)   /* READY                */
#define BSW_CANIF_ST_CANIFSTS_RUN              (0x57A8U)   /* RUN                  */

/* Transmission registration control state */
#define BSW_CANIF_ST_SNDSTS_DISABLE            (0x69U)     /* Disable  transmission registration         */
#define BSW_CANIF_ST_SNDSTS_ENABLE             (0x5AU)     /* Enable transmission registration         */

/* Unit internal public definition */
/* CANIF startup state */
#define BSW_CANIF_ST_INITCNTL_CNTL             (0x69U)     /* CAN controller startup      */
#define BSW_CANIF_ST_INITCNTL_CNTLOK           (0x96U)     /* CAN controller startup complete  */
#define BSW_CANIF_ST_INITCNTL_REG              (0x5AU)     /* Check for register sticking     */
#define BSW_CANIF_ST_INITCNTL_REGOK            (0xA5U)     /* Register sticking check completed */
#define BSW_CANIF_ST_INITCNTL_REGFAIL          (0x3CU)     /* Register sticking failure detected         */
#define BSW_CANIF_ST_INITCNTL_NG               (0xC3U)     /* Failed to startup                 */
#define BSW_CANIF_ST_INITCNTL_REGWARN          (0x1EU)     /* Register sticking failure detected (Not used MBOX) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    BswU2  u2Wp;                       /* Queue write position               */
    BswU2  u2Rp;                       /* Queue read position               */
    BswU2  u2Num;                      /* Number of queues stored                     */
} Bsw_CanIf_QueIdxType;                /* Queue index type               */

/* Can/vBus switching */
typedef Can_ReturnType (*Bsw_Canif_InitCtrllrType)( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
typedef Can_ReturnType (*Bsw_Canif_SetCtrllrModeType)( uint8 Controller, Can_StateTransitionType Transition );
typedef void           (*Bsw_Canif_ResetCtrllrType)( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
typedef Can_ReturnType (*Bsw_Canif_WriteType)( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
typedef Can_ReturnType (*Bsw_Canif_AbortSendType)( Can_HwHandleType Hth );
typedef void           (*Bsw_Canif_EdgeInitType)( uint8 Controller );
typedef void           (*Bsw_Canif_EdgeEnableDetectType)( uint8 Controller );
typedef void           (*Bsw_Canif_EdgeDisableDetectType)( uint8 Controller );
typedef void           (*Bsw_Canif_EdgeClearStatusType)( uint8 Controller );
typedef Can_ReturnType (*Bsw_Canif_EdgeGetStatusType)( uint8 Controller );
typedef Can_ReturnType (*Bsw_Canif_ChkStopCompletionType)( uint8 Controller );
typedef Can_ReturnType (*Bsw_Canif_ChkStuckRegisterType)( uint8 Controller );
typedef Can_ErrStType  (*Bsw_Canif_GetErrorStatusType)( uint8 Controller );

/* Switch CanTrcv. */
typedef Std_ReturnType (*Bsw_Canif_SetTrcvvModeType)( uint8 TransceiverId, Bsw_CanTrcv_TrcvModeType TransceiverMode );
typedef Std_ReturnType (*Bsw_Canif_GetTrcvModeType)( Bsw_CanTrcv_TrcvModeType* TransceiverModePtr, uint8 TransceiverId );
typedef Std_ReturnType (*Bsw_Canif_GetTrcvWkupReasonType)( uint8 TransceiverId, Bsw_CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr );
typedef Std_ReturnType (*Bsw_Canif_ClrTrcvWufFlagType)( uint8 TransceiverId );

typedef struct
{
    Bsw_Canif_InitCtrllrType           ptInitController;    /* InitController    */
    Bsw_Canif_SetCtrllrModeType        ptSetControllerMode; /* SetControllerMode */
    Bsw_Canif_ResetCtrllrType          ptResetController;   /* ResetController   */
    Bsw_Canif_WriteType                ptWrite;             /* Write             */
    Bsw_Canif_AbortSendType            ptAbortSend;         /* AbortSend         */
    Bsw_Canif_EdgeInitType             ptEdgeInit;          /* EdgeInit          */
    Bsw_Canif_EdgeEnableDetectType     ptEdgeEnableDetect;  /* EdgeEnableDetect  */
    Bsw_Canif_EdgeDisableDetectType    ptEdgeDisableDetect; /* EdgeDisableDetect */
    Bsw_Canif_EdgeClearStatusType      ptEdgeClearStatus;   /* EdgeClearStatus   */
    Bsw_Canif_EdgeGetStatusType        ptEdgeGetStatus;     /* EdgeGetStatus     */
    Bsw_Canif_ChkStopCompletionType    ptChkStopCompletion; /* ChkStopCompletion */
    Bsw_Canif_ChkStuckRegisterType     ptChkStuckRegister;  /* ChkStuckRegister  */
    Bsw_Canif_GetErrorStatusType       ptGetErrorStatus;    /* GetErrorStatus    */
}Bsw_Canif_CanFuncTblType;

typedef struct
{
    Bsw_Canif_SetTrcvvModeType         ptSetTrcvMode;       /* SetTrcvMode       */
    Bsw_Canif_GetTrcvModeType          ptGetTrcvMode;       /* GetTrcvMode       */
    Bsw_Canif_GetTrcvWkupReasonType    ptGetTrcvWkupReason; /* GetTrcvWkupReason */
    Bsw_Canif_ClrTrcvWufFlagType       ptClrTrcvWufFlag;    /* ClrTrcvWufFlag  */
}Bsw_Canif_CanTrcvFnTbType;

typedef struct
{
    BswConst BswU1                    *ptControllerToCh;     /* ControllerToChTbl */
    BswConst BswU4                    *ptCtrlToWkupSrc;      /* CtrlToWkupSrcTbl  */
    BswConst BswU1                     u1ControllerNum;      /* ControllerNum     */
    BswConst BswU1                     u1ChAttBit;           /* ChAttributeBit    */
    BswConst BswU2                     u2ChHohAttBit;        /* ChHohAttributeBit */
    BswConst Bsw_Canif_CanFuncTblType  stCanFuncTbl;         /* CanFuncTbl        */
    BswConst Bsw_Canif_CanTrcvFnTbType stCanTrcvFuncTbl;     /* CanTcvFuncTbl     */
}Bsw_Canif_ChAttTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
void  bsw_canif_st_Strt( BswU1 u1Ch );                /* CANIF communication start                */
void  bsw_canif_st_Stp( BswU1 u1Ch );                 /* CANIF communication stop                */

/* When CanDrv/vCan is not used */
Can_ReturnType bsw_canif_st_InitControllerNone( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType bsw_canif_st_SetCtrllrModeNone( uint8 Controller, Can_StateTransitionType Transition );
void           bsw_canif_st_ResetCtrllerNone( uint8 Controller, uint8 CanControllerBaudrateConfigSet );
Can_ReturnType bsw_canif_st_WriteNone( Can_HwHandleType Hth, CanConstR Can_PduType* PduInfo );
Can_ReturnType bsw_canif_st_AbortSendNone( Can_HwHandleType Hth );
void           bsw_canif_st_EdgeInitNone( uint8 Controller );
void           bsw_canif_st_EdgeEnDtctNone( uint8 Controller );
void           bsw_canif_st_EdgeDisDtctNone( uint8 Controller );
void           bsw_canif_st_EdgeClrStsNone( uint8 Controller );
Can_ReturnType bsw_canif_st_EdgeGetStsNone( uint8 Controller );
Can_ReturnType bsw_canif_st_ChkStpCmpltnNone( uint8 Controller );
Can_ReturnType bsw_canif_st_ChkStckRegNone( uint8 Controller );
Can_ErrStType  bsw_canif_st_GetErrStsNone( uint8 Controller );

/* Switch CanTrcv. */
/* Physical */
/* CAN Transceiver Noise Removal Function None */
Std_ReturnType bsw_canif_st_SetTrMdPhysical( uint8 TransceiverId, Bsw_CanTrcv_TrcvModeType TransceiverMode );
/* CAN Transceiver Noise Removal Function Exist */
Std_ReturnType bsw_canif_st_SetTrMdPhysNoiseRm( uint8 TransceiverId, Bsw_CanTrcv_TrcvModeType TransceiverMode );
Std_ReturnType bsw_canif_st_GetTrMdPhysical( Bsw_CanTrcv_TrcvModeType* TransceiverModePtr, uint8 TransceiverId );
Std_ReturnType bsw_canif_st_GetTrWkRsPhysical( uint8 TransceiverId, Bsw_CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr );
Std_ReturnType bsw_canif_st_ClrTrWuFgPhysical( uint8 TransceiverId );
/* Virtual */
Std_ReturnType bsw_canif_st_SetTrMdVirtual( uint8 TransceiverId, Bsw_CanTrcv_TrcvModeType TransceiverMode );
Std_ReturnType bsw_canif_st_GetTrMdVirtual( Bsw_CanTrcv_TrcvModeType* TransceiverModePtr, uint8 TransceiverId );
Std_ReturnType bsw_canif_st_GetTrWkRsVirtual( uint8 TransceiverId, Bsw_CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr );
Std_ReturnType bsw_canif_st_ClrTrWuFgVirtual( uint8 TransceiverId );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU2                               bsw_canif_st_u2CanifSts  [];
extern BswU1                               bsw_canif_st_u1SndSts[];

/* Unit internal public definition */
extern BswU1                               bsw_canif_st_u1InitCntlSts[];
extern BswU1                               bsw_canif_st_u1InitCntlTim[];
extern BswU1                               bsw_canif_st_u1RegChkTim[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1                      bsw_canif_st_u1ChNum;
extern BswConst BswU1                      bsw_canif_st_u1ControllerNum;
extern BswConst BswU1                      bsw_canif_st_u1ControllerToCh[];
extern BswConst uint32                     bsw_canif_st_u4CtrlToWkupSrc[];
extern BswConst BswU1                      bsw_canif_st_u1VControllerNum;
extern BswConst uint32                     bsw_canif_st_u4VCtrlToWkupSrc[];
extern BswConst BswU1                      bsw_canif_u1MsgInfo[];
extern BswConst BswU1                      bsw_canif_u1MsgIdTbl[];

/* Unit internal public definition */
extern BswConst BswU1                      bsw_canif_st_u1InitTimeout;
extern BswConst BswU1                      bsw_canif_st_u1SwChAttTbl[];
extern BswConst Bsw_Canif_ChAttTblType     bsw_canif_st_stChAttTbl[];

#endif  /* BSW_CANIF_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/11/15                                             */
/*  v2-0-0          :2022/02/07                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
