/* bsw_canif_fs_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANIF/FS/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_CANIF_FS_H
#define     BSW_CANIF_FS_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/****************************************************/
/* State value                                           */
/*--------------------------------------------------*/
/* -Identify the state with two or more bits                       */
/* -All 0 is not used                              */
/* -All 1 is not used                              */
/****************************************************/
/* Update the internal CANIF failure state Set value */
#define BSW_CANIF_FS_FST_NONE_FAIL             (0x5555U)   /* For FailSts No Fail          */
#define BSW_CANIF_FS_FST_NONE_BUSOFF           (0x0040U)   /* BusOff No failure            */
#define BSW_CANIF_FS_FST_NONE_USERFAIL         (0x0010U)   /* No UserFail fail            */
#define BSW_CANIF_FS_FST_NONE_SNDLOCK          (0x0004U)   /* No SndLock fail            */
#define BSW_CANIF_FS_FST_NONE_MPUFAIL          (0x0001U)   /* MpuFail No fail            */
#define BSW_CANIF_FS_FST_NONE_NMTXTOST         (0x0100U)   /* NmTxTimeoutStable No fail   */
#define BSW_CANIF_FS_FST_EXIST_BUSOFF          (0x0080U)   /* BusOff failure available            */
#define BSW_CANIF_FS_FST_EXIST_USERFAIL        (0x0020U)   /* UserFail fail exists            */
#define BSW_CANIF_FS_FST_EXIST_SNDLOCK         (0x0008U)   /* SndLock fail exists            */
#define BSW_CANIF_FS_FST_EXIST_MPUFAIL         (0x0002U)   /* MpuFail fail exists            */
#define BSW_CANIF_FS_FST_EXIST_NMTXTOST        (0x0200U)   /* NmTxTimeoutStable fail exists   */
#define BSW_CANIF_FS_NMTXTOUS_NONE             (0x55U)     /* NmTxTimeoutUnStable No fail */
#define BSW_CANIF_FS_NMTXTOUS_EXIST            (0xAAU)     /* NmTxTimeoutUnStable fail exists */
#define BSW_CANIF_FS_RCVLOCK_NONE              (0x55U)     /* No RcvLock fail            */
#define BSW_CANIF_FS_RCVLOCK_EXIST             (0xAAU)     /* RcvLock fail exists            */
#define BSW_CANIF_FS_RSST_NONE_REGSTCK         (0x4BU)     /* No RegStuck fail            */
#define BSW_CANIF_FS_RSST_EXIST_REGSTCK        (0xB4U)     /* RegStuck fail exists            */
#define BSW_CANIF_FS_RSST_EXIST_UNUSREG        (0xA5U)     /* UnusedRegStuck fail exists      */
#define BSW_CANIF_FS_RSST_EXIST_INITNG         (0x5AU)     /* INITNG fail exists              */

/* internal CANIF fail state Mask Value */                       /* Mask the following fail      */
#define BSW_CANIF_FS_FST_MSK_BUSOFF            (0xFF3FU)   /* BusOff                  */
#define BSW_CANIF_FS_FST_MSK_USER              (0xFFCFU)   /* UserFail                */
#define BSW_CANIF_FS_FST_MSK_SNDLOCK           (0xFFF3U)   /* SndLock                 */
#define BSW_CANIF_FS_FST_MSK_MPUFAIL           (0xFFFCU)   /* MpuFail                 */
#define BSW_CANIF_FS_FST_MSK_NMTXTOST          (0xFCFFU)   /* NmTxTimeoutStable       */
#define BSW_CANIF_FS_FST_MSK_NOTMPUFAIL        (0x0003U)   /* Except MpuFail             */
#define BSW_CANIF_FS_FST_MSK_NOTSNDLOCK        (0x000CU)   /* Except SndLock             */
#define BSW_CANIF_FS_FST_MSK_NOTBUSOFF         (0x00C0U)   /* Non BusOff              */
#define BSW_CANIF_FS_FST_MSK_NOTUSER           (0x0030U)   /* Except UserFail fail            */
#define BSW_CANIF_FS_FST_MSK_NOTNMTXTST        (0x0300U)   /* Other than NmTxTlimeoutStabe   */

/* Update the internal CANIF failure state Clear type */
#define BSW_CANIF_FS_CLR_ALLFAIL               (0U)        /* All fails clear   */
#define BSW_CANIF_FS_CLR_NOTREGSTUCKMPU        (1U)        /* Clear except RegStuck and MpuFail */
#define BSW_CANIF_FS_CLR_NOTREGSTUCK           (2U)        /* Clear except for RegStuck */

/* Unit internal public definition */
/* Receive lock detection control state */
#define BSW_CANIF_FS_RCVLOCKSTS_DISABLE        (0x69U)     /* Disable receive lock detection   */
#define BSW_CANIF_FS_RCVLOCKSTS_ENABLE         (0x5AU)     /* Enable receive lock detection   */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Unit internal public definition */
typedef struct {
    PduIdType              u2PduId;
    BswU1                  u1BytePos;
    BswU1                  u1BitPos;
} Bsw_CanIf_SumInfoType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_canif_fs_MainFunction( void );                              /* Failure Periodic processing                 */
void  bsw_canif_fs_ClrFailSts( BswU1 u1Ch, BswU1 u1ClrKind );         /* Clear failure               */
BswU1 bsw_canif_fs_DtctRegStuck( BswU1 u1Ch );                        /* Register sticking failure detected                 */
void  bsw_canif_fs_SetSndLockCnt( BswU1 u1Ch, BswU1 u1HthIdx );       /* Set the transmission lock detection counter       */
void  bsw_canif_fs_ClrSndLockCnt( BswU1 u1Ch, BswU1 u1HthIdx );       /* Clear the transmission lock detection counter     */
void  bsw_canif_fs_SetMpuFail( BswU1 u1Ch );                          /* Set MPU failure status            */

void  bsw_canif_fs_InitRcvLock( BswU1 u1Ch );                         /* Initialize receive lock detection             */
void  bsw_canif_fs_ClrRcvLockCnt( BswU1 u1Ch );                       /* Clear the receive lock detection counter     */
void  bsw_canif_fs_RstRcvLock( BswU1 u1Ch );                          /* Reset receive lock detection             */

void  bsw_canif_fs_InitRcvLockNone( BswU1 u1Ch );                     /* Initialize receive lock detection (Dummy function)   */
void  bsw_canif_fs_ClrRcvLockCntNone( BswU1 u1Ch );                   /* Clear the receive lock detection counter (Dummy function) */
void  bsw_canif_fs_RstRcvLockNone( BswU1 u1Ch );                      /* Reset receive lock detection (Dummy function)   */

void  bsw_canif_fs_SetRegStuckStatus( BswU1 u1Ch, BswU1 u1FailStatus ); /* Set register sticking check state */
Std_ReturnType bsw_canif_fs_DlcCheck0( BswU1 u1Comp, PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_DlcCheck1( BswU1 u1Comp, PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_DlcCheckNone( BswU1 u1Comp, PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );

void bsw_canif_fs_CheckSumTx0( Bsw_CanIf_PduType *ptCanTrsMsg );
void bsw_canif_fs_CheckSumTx1( Bsw_CanIf_PduType *ptCanTrsMsg );
void bsw_canif_fs_CheckSumTx2( Bsw_CanIf_PduType *ptCanTrsMsg );
void bsw_canif_fs_CheckSumTx3( Bsw_CanIf_PduType *ptCanTrsMsg );
void bsw_canif_fs_CheckSumTxNone( Bsw_CanIf_PduType *ptCanTrsMsg );

Std_ReturnType bsw_canif_fs_CheckSumRx0( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_CheckSumRx1( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_CheckSumRx2( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_CheckSumRx3( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
Std_ReturnType bsw_canif_fs_CheckSumRxNone( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );

/* Unit internal public definition */
BswU1 bsw_canif_fs_DtctSndLock( BswU1 u1Ch );                        /* Detect transmission lock                   */
void  bsw_canif_fs_DtctRcvLock( BswU1 u1Ch );                        /* Receive lock detection                   */
BswU1 bsw_canif_fs_ChkU2Dat( BswU2 u2Val );                          /* Check mirror BswU2 type data        */
BswU1 bsw_canif_fs_ChkU1Dat( BswU1 u1Val );                          /* Check mirror BswU1 type data        */
BswU1 bsw_canif_fs_ChkQueIdx( BswConstR Bsw_CanIf_QueIdxType* ptQueIdx, BswU2 u2Size );
                                                                     /* Queue consistency check               */
BswU1 bsw_canif_fs_DtctMpuFailTx( BswU1 u1Ch );                      /* Detect MPU failure(transmission)                */
BswU1 bsw_canif_fs_DtctSndLockNone( BswU1 u1Ch );                    /* Detect transmission lock (Dummy function)         */
void  bsw_canif_fs_DtctRcvLockNone( BswU1 u1Ch );                    /* Receive lock detection (Dummy function)         */
BswU1 bsw_canif_fs_DtctMpuFailTxNone( BswU1 u1Ch );                  /* Detect MPU failure(transmission)(Dummy function)      */


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU2                              bsw_canif_fs_u2FailSts[];
extern BswU1                              bsw_canif_fs_u1RcvLockFailSts[];
extern BswU1                              bsw_canif_fs_u1NmTxTimeoutUsSts[];
extern BswU1                              bsw_canif_fs_u1RegStuckSts[];

/* Unit internal public definition */
extern BswU1                              bsw_canif_fs_u1RcvLockSts[];
extern BswU2                              bsw_canif_fs_u2RcvLockCnt[];


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1                     bsw_canif_fs_u1RegCheckNum;

extern void (* BswConst bsw_canif_fs_ptInitRcvLockFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_fs_ptClrRcvLckCntFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_fs_ptRstRcvLockFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_fs_ptChkSumFuncTx[])( Bsw_CanIf_PduType *ptCanTrsMsg );
extern Std_ReturnType (* BswConst bsw_canif_fs_ptChkSumFuncRx[])( PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
extern Std_ReturnType (* BswConst bsw_canif_fs_ptDlcChkFuncRx[])( BswU1 u1Comp, PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );
extern Std_ReturnType (* BswConst bsw_canif_fs_ptCanTpDlcFunc[])( BswU1 u1Comp, PduIdType u2PduIndex, BswConstR Bsw_CanIf_PduType *ptCanRcvMsg );

/* Unit internal public definition */
extern BswConst BswU2                     bsw_canif_fs_u2TXSUMMSGNUM;
extern BswConst BswU2                     bsw_canif_fs_u2RXSUMMSGNUM;
extern BswConst BswU1                     bsw_canif_fs_u1UnusedRegChkTxRx;
extern BswConst BswU2                     bsw_canif_fs_u2SndLockTim[];
extern BswU2 * BswConst                   bsw_canif_fs_ptSndLockCnt[];
extern BswConst BswU2                     bsw_canif_fs_u2RcvLockTim[];
extern BswConst Bsw_CanIf_SumInfoType     bsw_canif_fs_stSum2TxInfo[];
extern BswConst Bsw_CanIf_SumInfoType     bsw_canif_fs_stSum2RxInfo[];

extern BswU1 (* BswConst bsw_canif_fs_ptDtctSndLockFunc)( BswU1 u1Ch );
extern void (* BswConst bsw_canif_fs_ptDtctRcvLockFunc)( BswU1 u1Ch );
extern BswU1 (* BswConst bsw_canif_fs_ptDctMpuFailTxFunc)( BswU1 u1Ch );


#endif  /* BSW_CANIF_FS_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/27                                             */
/*  v1-1-0          :2018/07/06                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
