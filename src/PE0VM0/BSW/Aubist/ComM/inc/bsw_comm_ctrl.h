/* bsw_comm_ctrl_h_v2-2-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COMM/CTRL/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_COMM_CTRL_H
#define BSW_COMM_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Intra unit public definition macro *****************************************************/
#define BSW_COMM_u2NO_REQUEST                  ((BswU2)0x00FFU)   /* No request                 */
#define BSW_COMM_u2EXIST_REQUEST               ((BswU2)0x01FEU)   /* Request exists                 */

#define BSW_COMM_u1NO_NM_START_IND             ((BswU1)0x1EU)     /* No NM start notification           */
#define BSW_COMM_u1EXIST_NM_START_IND          ((BswU1)0xE1U)     /* NM start notification available           */

#define BSW_COMM_u1NO_ECUM_WKUP_IND            ((BswU1)0x1EU)     /* No Wake-up request notification  */
#define BSW_COMM_u1EXIST_ECUM_WKUP_IND         ((BswU1)0xE1U)     /* Wake-up request notification exists */

#define BSW_COMM_u1NO_WAKEUP_REQ               ((BswU1)0x1EU)     /* No Wake-up request  */
#define BSW_COMM_u1EXIST_WAKEUP_REQ            ((BswU1)0xE1U)     /* Wake-up request exists */

#define BSW_COMM_u1MAX_NUM_PWR_USRAWK          ((Bsw_ComM_UserHandleType)16U)  /* Maximum number of power supplies/users Awake    */

#define BSW_COMM_u2MASK_LOW                    ((BswU2)0x00FFU)   /* Lower 1BYTE mask          */
#define BSW_COMM_u2ALLBIT                      ((BswU2)0xFFFFU)   /* For inverting bits             */
#define BSW_COMM_u4ALLBIT                      (0xFFFFFFFFUL)     /* For inverting bits             */

#define BSW_COMM_u1INDEX_0                     ((BswU1)0U)        /* Index for array access */
#define BSW_COMM_u1INDEX_1                     ((BswU1)1U)        /* Index for array access */
#define BSW_COMM_u1INDEX_2                     ((BswU1)2U)        /* Index for array access */
#define BSW_COMM_u1INDEX_3                     ((BswU1)3U)        /* Index for array access */
#define BSW_COMM_u1INDEX_4                     ((BswU1)4U)        /* Index for array access */
#define BSW_COMM_u1INDEX_5                     ((BswU1)5U)        /* Index for array access */
#define BSW_COMM_u1INDEX_6                     ((BswU1)6U)        /* Index for array access */
#define BSW_COMM_u1INDEX_7                     ((BswU1)7U)        /* Index for array access */
#define BSW_COMM_u1INDEX_8                     ((BswU1)8U)        /* Index for array access */
#define BSW_COMM_u1INDEX_9                     ((BswU1)9U)        /* Index for array access */
#define BSW_COMM_u1INDEX_10                    ((BswU1)10U)       /* Index for array access */
#define BSW_COMM_u1INDEX_11                    ((BswU1)11U)       /* Index for array access */
#define BSW_COMM_u1INDEX_12                    ((BswU1)12U)       /* Index for array access */
#define BSW_COMM_u1INDEX_13                    ((BswU1)13U)       /* Index for array access */
#define BSW_COMM_u1INDEX_14                    ((BswU1)14U)       /* Index for array access */
#define BSW_COMM_u1INDEX_15                    ((BswU1)15U)       /* Index for array access */
#define BSW_COMM_u1INDEX_16                    ((BswU1)16U)       /* Index for array access */
#define BSW_COMM_u1INDEX_17                    ((BswU1)17U)       /* Index for array access */
#define BSW_COMM_u1INDEX_18                    ((BswU1)18U)       /* Index for array access */
#define BSW_COMM_u1INDEX_19                    ((BswU1)19U)       /* Index for array access */
#define BSW_COMM_u1INDEX_20                    ((BswU1)20U)       /* Index for array access */
#define BSW_COMM_u1INDEX_21                    ((BswU1)21U)       /* Index for array access */
#define BSW_COMM_u1INDEX_22                    ((BswU1)22U)       /* Index for array access */
#define BSW_COMM_u1INDEX_23                    ((BswU1)23U)       /* Index for array access */
#define BSW_COMM_u1INDEX_24                    ((BswU1)24U)       /* Index for array access */
#define BSW_COMM_u1INDEX_25                    ((BswU1)25U)       /* Index for array access */
#define BSW_COMM_u1INDEX_26                    ((BswU1)26U)       /* Index for array access */
#define BSW_COMM_u1INDEX_27                    ((BswU1)27U)       /* Index for array access */
#define BSW_COMM_u1INDEX_28                    ((BswU1)28U)       /* Index for array access */
#define BSW_COMM_u1INDEX_29                    ((BswU1)29U)       /* Index for array access */
#define BSW_COMM_u1INDEX_30                    ((BswU1)30U)       /* Index for array access */
#define BSW_COMM_u1INDEX_31                    ((BswU1)31U)       /* Index for array access */

/*  The lower 1 byte is a mirror value of the upper 1 byte. */
#define BSW_COMM_u2NO_COM                      ((BswU2)0x00FFU)   /* Communication stop state             */
#define BSW_COMM_u2FULL_COM_NW_REQ_ACT         ((BswU2)0x01FEU)   /* Communication started state (Active) */
#define BSW_COMM_u2FULL_COM_READY_SLEEP        ((BswU2)0x02FDU)   /* Sleep preparation state         */
#define BSW_COMM_u2SILENT_COM                  ((BswU2)0x03FCU)   /* Transmission disabled state             */
#define BSW_COMM_u2INVALID_COM                 ((BswU2)0x04FBU)   /* ComM state failure             */
#define BSW_COMM_u2FULL_COM_NW_REQ_PSV         ((BswU2)0x05FAU)   /* Communication started state (Passive)   */
#define BSW_COMM_u2UNINIT                      ((BswU2)0x06F9U)   /* Uninitialized                 */

/*  The lower 1 byte is a mirror value of the upper 1 byte. */
#define BSW_COMM_u2PNC_NO_COM                  ((BswU2)0x00FFU)   /* PNC communication stop state          */
#define BSW_COMM_u2PNC_REQUESTED               ((BswU2)0x02FDU)   /* PNC communication activation state (active) */
#define BSW_COMM_u2PNC_READY_SLEEP             ((BswU2)0x03FCU)   /* PNC Ready sleep state          */
#define BSW_COMM_u2PNC_PREPARE_SLEEP           ((BswU2)0x04FBU)   /* PNC Prepare sleep state      */
#define BSW_COMM_u2PNC_INVALID_COM             ((BswU2)0x05FAU)   /* PNC state failure              */

#define BSW_COMM_u1NO_REQUEST                  ((BswU1)0x00U)     /* No request                 */
#define BSW_COMM_u1EXIST_REQUEST               ((BswU1)0x01U)     /* Request exists                 */
#define BSW_COMM_u4ALL_USER_NO_COM             (0x00000000UL)     /* No user communication request       */

#define BSW_COMM_PNC_REQNUM                    (BSW_COMM_PNCMAXNUM >> 5U) /* Number of 4 bytes for PNC (bit) */
#define BSW_COMM_u4PNC_AWAKE_NONE              (0x00000000UL)     /* No PNC communication request (4 bytes) */
#define BSW_COMM_u1USRHNDL_MSK_PNC             ((BswU1)0x80U)     /* User handle PNC judgment mask */
#define BSW_COMM_u1USRHNDL_MSK_PNCIND          ((BswU1)0x7FU)     /* User handle PNC index mask */
#define BSW_COMM_u1HANDLE_BIT_MASK             ((BswU1)0x1FU)
#define BSW_COMM_u4USER_REQ_POS                (0x00000001UL)
#define BSW_COMM_SHIFT_HANDLE_IDX              (5U)

#define BSW_COMM_SHIFT1BYTE                    (8U)               /* Top address of 64bit upper data            */
#define BSW_COMM_SHIFT2BYTE                    (16U)              /* 16-bit shift           */
#define BSW_COMM_SHIFT3BYTE                    (24U)              /* 24-bit shift           */
#define BSW_COMM_u4MASK_BIT0                   (0x00000001UL)     /* 0-bit mask (4 bytes)     */

#define BSW_COMM_u2TIMER_STOP                  ((BswU2)0U)        /* Stop timer           */

#define BSW_COMM_u1ACTIVE_AWAKE                ((BswU1)(BSW_COMM_BUSAWAKE_KIND_OWN | BSW_COMM_BUSAWAKE_KIND_CO)) /* Own-node awake factor exists */
#define BSW_COMM_u1EXCEPT_OTHER_AWAKE          ((BswU1)(BSW_COMM_BUSAWAKE_KIND_OWN | BSW_COMM_BUSAWAKE_KIND_CO \
                                                | BSW_COMM_BUSAWAKE_KIND_ECU)) /* Other non-Awake factors are available */

/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* Unit internal public definition ----------------------------------------------------------*/
/* State by channel */
typedef struct
{
    BswU2  u2StateTimer;
    BswU2  u2CurrentState;
    BswU2  u2CommunicationAllowed;
    BswU2  u2DcmRequest;
    BswU2  u2EventAwake;
    BswU2  u2BusAwake;
    BswU2  u2SyncAwake;
    BswU1  u1NmStartInd;
    BswU1  u1ReqNmStartInd;
    BswU1  u1CoBusAwake;
    BswU1  u1EcumWkupInd;
    BswU1  u1WakeupReq;
    BswU1  u1ChBusAwake;
} Bsw_ComM_ChStsType;

/* Bus type switching function table */
typedef struct
{
    Std_ReturnType (*RequestComMode)( NetworkHandleType network, Bsw_ComM_ModeType ComM_Mode );
    Std_ReturnType (*GetCurrentComMode)( NetworkHandleType network, Bsw_ComM_ModeType* ComM_ModePtr );
} Bsw_ComM_BusFuncTblType;

/* State by PNC */
typedef struct
{
    BswU2  u2StateTimer;
    BswU2  u2CurrentState;
    BswU2  u2SendStartTimer;
    BswU1  u1SendStartTimerSetting;
    BswU1  u1dmy;
} Bsw_ComM_PncStsType;

/* PNC Index */
typedef struct
{
    BswU1 u1IdInternal;
    BswU1 u1ByteIndex;
    BswU1 u1BitIndex;
} Bsw_ComM_PncIndexType;

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Dummy function for protocol switching (Open to the public in the unit) ***************************/
Std_ReturnType bsw_comm_ctrl_ReqComMode_Inv( NetworkHandleType network, Bsw_ComM_ModeType ComM_Mode );
Std_ReturnType bsw_comm_ctrl_GetCurComMod_Inv( NetworkHandleType network, Bsw_ComM_ModeType* ComM_ModePtr );
/****************************************************************************/

/* Unit internal public definition ***********************************************************/
BswU2 bsw_comm_ctrl_NoComSt( BswU1 u1Channel, BswU1 u1BusAwake, BswU1 u1JdgChPow );
BswU2 bsw_comm_ctrl_FullComNetReqSt( BswU1 u1Channel, BswU1 u1BusAwake, BswU1 u1JdgChPow );
BswU2 bsw_comm_ctrl_FullComPsvSt( BswU1 u1Channel, BswU1 u1BusAwake, BswU1 u1JdgChPow );
BswU2 bsw_comm_ctrl_FullComRdySlpSt( BswU1 u1Channel, BswU1 u1BusAwake, BswU1 u1JdgChPow );
BswU2 bsw_comm_ctrl_SilentComSt( BswU1 u1Channel, BswU1 u1BusAwake, BswU1 u1JdgChPow );
BswU1 bsw_comm_ctrl_GtBsAwkKndForTran( BswU1 u1Channel );
void bsw_comm_ctrl_MainFunc( void );

void bsw_comm_ctrl_InitPnc( void );
BswU2 bsw_comm_ctrl_SumU2Dat( BswU2 u2Dat );
BswU1 bsw_comm_ctrl_RequestComModePNC( BswU1 u1User, BswU1 u1ComMode );
BswU1 bsw_comm_ctrl_GetCoPncReq( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_GetPncReqExcCo( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_GetFixedPncReq( BswU1 u1Channel );
void bsw_comm_ctrl_CheckNewPncReq( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_ChkRamPnc( void );
void bsw_comm_ctrl_ClrAllCoPncAwk( void );
void bsw_comm_ctrl_MainFuncPnc( void );
void bsw_comm_ctrl_MainFuncEira( void );
void bsw_comm_ctrl_PNCEcuMWakeUpInd( BswU1 u1Channel );
void bsw_comm_ctrl_UpdPncAwake( BswU1 u1Channel, BswU1 u1PncIndex, BswU4* ptPncOwnAwake );

void bsw_comm_ctrl_RqCmMdWkupRqToReq( BswU1 u1Channel, BswU1 u1BusAwake );
void bsw_comm_ctrl_RqCmMdWkupRqToRdy( BswU1 u1Channel );
void bsw_comm_ctrl_RqCmMdWkupRqFlReq( BswU1 u1Channel );
void bsw_comm_ctrl_ReqComModeToReq( BswU1 u1Channel, BswU1 u1BusAwake );
void bsw_comm_ctrl_ReqComModeToReady( BswU1 u1Channel );
void bsw_comm_ctrl_ReqCmMdFulCmToReq( BswU1 u1Channel );

void bsw_comm_ctrl_InitPncNone( void );
BswU1 bsw_comm_ctrl_RqstCmMdPNCNone( BswU1 u1User, BswU1 u1ComMode );
BswU1 bsw_comm_ctrl_GetCoPncReqNn( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_GetPncReqExcCoNn( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_GetFixedPncReqNn( BswU1 u1Channel );
void bsw_comm_ctrl_CheckNewPncReqNn( BswU1 u1Channel );
BswU1 bsw_comm_ctrl_ChkRamPncNone( void );
void bsw_comm_ctrl_ClrAllCoPncAwkNn( void );
void bsw_comm_ctrl_PNCEcuMWkUpIndNn( BswU1 u1Channel );
void bsw_comm_ctrl_MainFuncEiraNone( void );
void bsw_comm_ctrl_UpdPncAwakeNone( BswU1 u1Channel, BswU1 u1PncIndex, BswU4* ptPncOwnAwake );

/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  Bsw_ComM_ChStsType bsw_comm_ctrl_stChSts[];                             /* State by channel     */
extern  BswU2              bsw_comm_ctrl_u2ReqComMode;                          /* User request         */
extern  BswU2              bsw_comm_ctrl_u2ReqComModeMrr;                       /* User request (mirror) */

extern  Bsw_ComM_PncStsType* BswConst bsw_comm_ctrl_ptPncSts[];                 /* State by PNC          */
extern  BswU4 bsw_comm_ctrl_u4PncOwnAwake[][BSW_COMM_PNC_REQNUM];               /* Internal factor           */
extern  BswU4 bsw_comm_ctrl_u4TmpEira[][BSW_COMM_PNC_REQNUM];                   /* External factor           */
extern  BswU4 bsw_comm_ctrl_u4FixedEira[][BSW_COMM_PNC_REQNUM];                 /* External factor(Fix)           */
extern  BswU4 bsw_comm_ctrl_u4FixedEiraStatus[][BSW_COMM_PNC_REQNUM];           /* External factor(fix and public use) */
extern  BswU4 bsw_comm_ctrl_u4PncToChNewReq[][BSW_COMM_PNC_REQNUM];             /* New communication request status for each PNC (bit) */
extern  BswU4 bsw_comm_ctrl_u4RqCmMdPNC[][BSW_COMM_PNC_REQNUM];                 /* User request for PNC  */
extern  BswU4 bsw_comm_ctrl_u4RqCmMdPNCMrr[][BSW_COMM_PNC_REQNUM];              /* User request for PNC(mirror) */
extern  BswU4 bsw_comm_ctrl_u4CoPncAwake[][BSW_COMM_PNC_REQNUM];                /* Cooperative PNC Awake factor */
extern  BswU4 bsw_comm_ctrl_u4CoPncAwakeNoReq[][BSW_COMM_PNC_REQNUM];           /* Cooperative PNC Awake factor (No external wake-up request) */
extern  BswU4 bsw_comm_ctrl_u4EcumWkupIndPNC[][BSW_COMM_PNC_REQNUM];            /* PNC Ecum Wakeup indication */

extern  BswU4 bsw_comm_ctrl_u4PncReqRdyStatus[][BSW_COMM_PNC_REQNUM];           /* PNC Requeste/Ready-Sleep Status */
extern  BswU4 bsw_comm_ctrl_u4PncPrpSlpStatus[][BSW_COMM_PNC_REQNUM];           /* PNC Prepare-Sleep Status */
extern  BswU4 bsw_comm_ctrl_u4PncEnableTxStat[][BSW_COMM_PNC_REQNUM];           /* PNC EnableTx Status */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern  BswConst   BswU1  bsw_comm_ctrl_u1ChToIdxTbl[];                            /* Channel -> Index conversion */
extern  BswConst   Bsw_ComM_BusFuncTblType* BswConst bsw_comm_ctrl_ptBusFuncTbl[]; /* Public function table */
extern  BswConst   BswU1  bsw_comm_ctrl_u1ChNum;                                   /* Channel count */
extern  BswConst   BswU2  bsw_comm_ctrl_u2UserPerCh[];                             /* Request user communication per channel */
extern  BswConst   BswU2  bsw_comm_ctrl_u2AwakeHoldTimer[];                        /* Own-node Awake hold time per channel */
extern  BswConst   BswU1  bsw_comm_ctrl_u1CHPowSupply[];                           /* Channel power per channel */

extern  BswConst   BswU1 bsw_comm_ctrl_u1PncNum[];                                 /* Number of PNC */
extern  BswConst   BswU2 bsw_comm_ctrl_u2PncResetTime[];                           /* EIRA reset time */
extern  BswConst   BswU2 bsw_comm_ctrl_u2PncPreSlpTime[];                          /* PNC Ready sleep time */
extern  BswConst   Bsw_ComM_PncIndexType* BswConst bsw_comm_ctrl_ptPncIdx[];       /* PNC Index */

extern  BswConst   BswU4 bsw_comm_ctrl_u4PncPerCh[][BSW_COMM_PNC_REQNUM];          /* Channel starting factor */
extern  BswConst   BswU1 bsw_comm_ctrl_u1PncUseSingleCh;                           /* First channel using PNC */

extern  BswConst   BswU1 bsw_comm_ctrl_u1PncWakeupReq[];
extern  BswConst   BswU1 bsw_comm_ctrl_u1PncSyncWakeup[];
extern  BswConst   BswU1 bsw_comm_ctrl_u1ChWakeupReq[];
extern  BswConst   BswU1 bsw_comm_ctrl_u1ChPsvWakeupReq[];
extern  BswConst   BswU1* BswConst bsw_comm_ctrl_u1PNCAwakePW[];
extern  BswConst   BswU2 bsw_comm_ctrl_u2PncSendStartTm[];

extern  void (* BswConst bsw_comm_ctrl_ptInitPNCFunc)( void );
extern  BswU1 (* BswConst bsw_comm_ctrl_ptRqstCmMdPNCFunc)( BswU1 u1User, BswU1 u1ComMode );
extern  BswU1 (* BswConst bsw_comm_ctrl_ptGetCoPncReqFn)( BswU1 u1Channel );
extern  BswU1 (* BswConst bsw_comm_ctrl_ptGetPncReqExCoFn)( BswU1 u1Channel );
extern  BswU1 (* BswConst bsw_comm_ctrl_ptGetFixedPncRqFn)( BswU1 u1Channel );
extern  void (* BswConst bsw_comm_ctrl_ptChkNewPncReqFn)( BswU1 u1Channel );
extern  BswU1 (* BswConst bsw_comm_ctrl_ptChkRamPncFunc)( void );
extern  void (* BswConst bsw_comm_ctrl_ptClrAllCoPnAwkFn)( void );
extern  void (* BswConst bsw_comm_ctrl_ptMainFunction)( void );
extern  void (* BswConst bsw_comm_ctrl_ptMainFuncEira)( void );
extern  void (* BswConst bsw_comm_ctrl_ptPnEcumWkupIndFn)( BswU1 u1Channel );
extern  void (* BswConst bsw_comm_ctrl_ptUpdPncAwakeFunc)( BswU1 u1Channel, BswU1 u1PncIndex, BswU4* ptPncOwnAwake );

extern  void (* BswConst bsw_comm_ctrl_ptRqCmMdToReqFn)( BswU1 u1Channel, BswU1 u1BusAwake );
extern  void (* BswConst bsw_comm_ctrl_ptRqCmMdToRdyFn)( BswU1 u1Channel );
extern  void (* BswConst bsw_comm_ctrl_ptRqCmMdFlToReqFn)( BswU1 u1Channel );


#endif /* BSW_COMM_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/14                                             */
/*  v1-1-0          :2018/11/19                                             */
/*  v2-0-0          :2022/01/07                                             */
/*  v2-1-0          :2022/10/14                                             */
/*  v2-2-0          :2023/05/08                                             */
/****************************************************************************/
/**** End of File ***********************************************************/
