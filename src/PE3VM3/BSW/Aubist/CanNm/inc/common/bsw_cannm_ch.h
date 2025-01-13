/* bsw_cannm_ch_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/CH/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_CH_H
#define BSW_CANNM_CH_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_u2ALLBIT               ((BswU2)0xFFFFU)
#define BSW_CANNM_u4MSK_CANFD            (0xBFFFFFFFUL)          /* CAN-FD Message Mask */
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    void            (*Init)( BswConst Bsw_CanNm_ConfigType* cannmConfigPtr );
    void            (*DeInit)( void );
    void            (*MainFunction)( void );
    uint8           (*CheckAwake)( NetworkHandleType nmChannelHandle );
    Std_ReturnType  (*PassiveStartUp)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*NetworkRequest)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*NetworkRelease)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*GetState)( NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );
    uint8           (*GetIPDUState)( NetworkHandleType nmChannelHandle );
    void            (*SetBusOff)( NetworkHandleType nmChannelHandle );
    void            (*TxConfirmation)(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result);
    void            (*RxIndication)(PduIdType RxPduId, NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);
} Bsw_CanNm_FuncTblType;

typedef struct
{
    void            (*Wakeup)( BswConst Bsw_CanNm_ConfigType* cannmConfigPtr );
    void            (*Sleep)( void );
    uint16          (*GetBackupData)( NetworkHandleType nmChannelHandle );
    void            (*SetBackupData)( NetworkHandleType nmChannelHandle, uint16 BackupData );
} Bsw_CanNm_SlpFuncTblType;

typedef struct
{
    Std_ReturnType  (*DisableComm)( NetworkHandleType NetworkHandle );
    Std_ReturnType  (*EnableComm)( NetworkHandleType NetworkHandle );
} Bsw_CanNm_ComFuncTblType;

typedef struct
{
    Std_ReturnType  (*SetUserData)( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
    Std_ReturnType  (*GetUserData)( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
} Bsw_CanNm_UsrDatFuncTblType;

typedef struct
{
    Std_ReturnType  (*GetNodeIdentifier)( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
    Std_ReturnType  (*GetLocalNodeIdentifier)( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
} Bsw_CanNm_NodeFuncTblType;

typedef struct
{
    Std_ReturnType  (*GetPduData)( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );
} Bsw_CanNm_PduFuncTblType;

typedef struct
{
    void  (*CheckRam)( void );
} Bsw_CanNm_ChkRamFuncTblType;

typedef struct
{
    Std_ReturnType  (*ReqSyncPncSlp)( NetworkHandleType nmChannelHandle, PNCHandleType PNC );
    Std_ReturnType  (*CancelSyncPncSlp)( NetworkHandleType nmChannelHandle, PNCHandleType PNC );
} Bsw_CanNm_SyncPncSlpFuncTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* Component internal publication definition */
void            bsw_cannm_ch_InitNone(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);                                                /* Initialization                           */
void            bsw_cannm_ch_DeInitNone(void);                                                                                   /* Shutdown                   */
Std_ReturnType  bsw_cannm_ch_PassiveStrtUpNone(NetworkHandleType NetworkHandle);                                                 /* Request network startup             */
Std_ReturnType  bsw_cannm_ch_NetworkReqNone(NetworkHandleType NetworkHandle);                                                    /* Request to start network             */
Std_ReturnType  bsw_cannm_ch_NetworkRelNone(NetworkHandleType NetworkHandle);                                                    /* Request network release             */
Std_ReturnType  bsw_cannm_ch_DisableComNone( NetworkHandleType NetworkHandle );                                                  /* Communication function disablement request               */
Std_ReturnType  bsw_cannm_ch_EnableComNone( NetworkHandleType NetworkHandle );                                                   /* Communication function enablement request               */
Std_ReturnType  bsw_cannm_ch_GetStateNone(NetworkHandleType nmNetworkHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr);  /* Request for acquisition of CanNm state              */
void            bsw_cannm_ch_MainFuncNone(void);                                                                                 /* Periodic processing                         */
uint8           bsw_cannm_ch_CheckAwakeNone( NetworkHandleType nmChannelHandle );                                                /* CPUAwake get request                 */
uint8           bsw_cannm_ch_GetIPDUStateNone( NetworkHandleType nmChannelHandle );                                              /* COM transmission availability state acquisition request          */
void            bsw_cannm_ch_SetBusOffNone( NetworkHandleType nmChannelHandle );                                                 /* Notify bus-off                     */
uint16          bsw_cannm_ch_TrEvWkupNone( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_ch_ClEvWkupNone( NetworkHandleType nmNetworkHandle );
void            bsw_cannm_ch_CheckRamNone( void );                                                                               /* RAM Check                      */

void            bsw_cannm_ch_WakeupNone(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);                                              /* Wake-up initialization             */
void            bsw_cannm_ch_SleepNone(void);                                                                                    /* Sleep                         */
uint16          bsw_cannm_ch_GetBackupDataNone( NetworkHandleType nmChannelHandle );                                             /* Get backup data           */
void            bsw_cannm_ch_SetBackupDataNone( NetworkHandleType nmChannelHandle, uint16 BackupData );                          /* Set backup data           */

void            bsw_cannm_ch_TxConfirmationNone(PduIdType TxPduId, NetworkHandleType nmChannelHandle, Std_ReturnType result);                       /* Notify transmission completion           */
void            bsw_cannm_ch_RxIndicationNone(PduIdType RxPduId, NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr);             /* Notify receiving               */

Std_ReturnType  bsw_cannm_ch_GetNodeIdNone( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_ch_GetLNodeIdNone( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_ch_SetUserDataNone( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_ch_GetUserDataNone( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_ch_GetPduDataNone( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );

Std_ReturnType  bsw_cannm_ch_SetSlpReadyBitNone( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit );
Std_ReturnType  bsw_cannm_ch_RequestBusSyncNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_ReqSyncPncSlpNone( NetworkHandleType nmChannelHandle, PNCHandleType PNC );
Std_ReturnType  bsw_cannm_ch_CancelSyncPncSlpNone( NetworkHandleType nmChannelHandle, PNCHandleType PNC );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1                                 bsw_cannm_ch_u1ChOffset;
extern BswConst BswU1                                 bsw_cannm_ch_u1FuncTblSize;
extern BswConst BswU1                                 bsw_cannm_ch_u1UseNmTypeNum;

extern BswConst BswU1                                 bsw_cannm_ch_u1Ch2IdxTbl[];
extern BswConst BswU1                                 bsw_cannm_ch_u1BusSleepTbl[];
extern BswConst Bsw_CanNm_FuncTblType*       BswConst bsw_cannm_ch_ptFuncTbl[];
extern BswConst Bsw_CanNm_FuncTblType*       BswConst bsw_cannm_ch_ptUseNmTypeFuncTbl[];
extern BswConst Bsw_CanNm_SlpFuncTblType*    BswConst bsw_cannm_ch_ptSlpFuncTbl[];
extern BswConst Bsw_CanNm_ComFuncTblType*    BswConst bsw_cannm_ch_ptComFuncTbl[];
extern BswConst Bsw_CanNm_UsrDatFuncTblType* BswConst bsw_cannm_ch_ptUsrDatFuncTbl[];
extern BswConst Bsw_CanNm_NodeFuncTblType*   BswConst bsw_cannm_ch_ptNodeFuncTbl[];
extern BswConst Bsw_CanNm_PduFuncTblType*    BswConst bsw_cannm_ch_ptPduFuncTbl[];
extern BswConst Bsw_CanNm_ChkRamFuncTblType* BswConst bsw_cannm_ch_ptChkRamFuncTbl[];
extern BswConst Bsw_CanNm_SyncPncSlpFuncTblType* BswConst bsw_cannm_ch_ptPncSyncFuncTbl[];

extern BswConst BswU1                                 bsw_cannm_ch_u1PduOffset[];

extern uint16 (* BswConst bsw_cannm_ch_ptTransEvtWkupFunc[])( NetworkHandleType nmNetworkHandle );
extern void (* BswConst bsw_cannm_ch_ptEvtWkupClFunc[])( NetworkHandleType nmNetworkHandle );
extern Std_ReturnType (* BswConst bsw_cannm_ch_ptSetSRBFunc[])( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit );
extern Std_ReturnType (* BswConst bsw_cannm_ch_ptRqBusSyncFunc[])( NetworkHandleType nmChannelHandle );

#endif  /* BSW_CANNM_CH_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/07/13                                             */
/*  v1-0-1          :2018/05/11                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2022/01/06                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
