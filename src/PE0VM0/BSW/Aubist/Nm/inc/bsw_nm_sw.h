/* bsw_nm_sw_h_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/NM/SW/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NM_SW_H
#define BSW_NM_SW_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for protocol switching */
typedef struct
{
    Std_ReturnType  (*PassiveStartUp)( NetworkHandleType nmChannelHandle );
    Std_ReturnType  (*NetworkRequest)( NetworkHandleType nmChannelHandle );
    Std_ReturnType  (*NetworkRelease)( NetworkHandleType nmChannelHandle );
    Std_ReturnType  (*GetState)( NetworkHandleType nmChannelHandle, Bsw_Nm_StateType* nmStatePtr, Bsw_Nm_ModeType* nmModePtr );
} Bsw_Nm_FuncTblType;

typedef struct
{
    Std_ReturnType  (*DisableComm)( NetworkHandleType nmChannelHandle );
    Std_ReturnType  (*EnableComm)( NetworkHandleType nmChannelHandle );
} Bsw_Nm_ComFuncTblType;

typedef struct
{
    Std_ReturnType  (*SetUserData)( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
    Std_ReturnType  (*GetUserData)( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
} Bsw_Nm_UsrDatFuncTblType;

typedef struct
{
    Std_ReturnType  (*GetNodeIdentifier)( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
    Std_ReturnType  (*GetLocalNodeIdentifier)( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
} Bsw_Nm_NodeFuncTblType;

typedef struct
{
    Std_ReturnType  (*GetPduData)( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );
} Bsw_Nm_PduFuncTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* List of inter unit open definition functions */
Std_ReturnType  bsw_nm_sw_SetSleepReadyBit( NetworkHandleType NetworkHandle, boolean nmSleepReadyBit );
Std_ReturnType  bsw_nm_sw_RequestBusSync( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_ReqSyncPncSlp( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );
Std_ReturnType  bsw_nm_sw_CancelSyncPncSlp( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );

/* List of inter unit open definition functions(Dummy function) */
Std_ReturnType  bsw_nm_sw_PassiveStUpNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_NetworkReqNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_NetworkRelNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_GetStateNone( NetworkHandleType nmChannelHandle, Bsw_Nm_StateType* nmStatePtr, Bsw_Nm_ModeType* nmModePtr );
Std_ReturnType  bsw_nm_sw_GetNodeIdNone( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_nm_sw_GetLNodeIdNone( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_nm_sw_GetPduDataNone( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );
Std_ReturnType  bsw_nm_sw_DisableCommNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_EnableCommNone( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_nm_sw_SetUserDataNone( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_nm_sw_GetUserDataNone( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_nm_sw_SetSleepReadyBitNone( NetworkHandleType NetworkHandle, boolean nmSleepReadyBit );
Std_ReturnType  bsw_nm_sw_ReqSyncPncSlpNone( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );
Std_ReturnType  bsw_nm_sw_CancelSyncPncSlpNone( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );
void            bsw_nm_sw_StopSyncSleepNone( NetworkHandleType NetworkHandle );
void            bsw_nm_sw_StopSleepDelayNone( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_RequestBusSyncNone( NetworkHandleType nmChannelHandle );

uint16          bsw_nm_sw_TransmitEvWakeupNone( NetworkHandleType nmChannelHandle );
void            bsw_nm_sw_CancelEvWakeupNone( NetworkHandleType nmChannelHandle );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst   BswU1                              bsw_nm_sw_u1Ch2IdxTbl[];     /* Channel -> Index conversion   */
extern BswConst   Bsw_Nm_FuncTblType*       BswConst bsw_nm_sw_ptFuncTbl[];       /* Public function table             */
extern BswConst   Bsw_Nm_ComFuncTblType*    BswConst bsw_nm_sw_ptComFuncTbl[];    /* Communication restriction function table         */
extern BswConst   Bsw_Nm_UsrDatFuncTblType* BswConst bsw_nm_sw_ptUsrDatFuncTbl[]; /* Table of user data functions     */
extern BswConst   Bsw_Nm_NodeFuncTblType*   BswConst bsw_nm_sw_ptNodeFuncTbl[];   /* Node ID provider function table     */
extern BswConst   Bsw_Nm_PduFuncTblType*    BswConst bsw_nm_sw_ptPduFuncTbl[];    /* NM-PDU provided function table     */
extern uint16      (* BswConst bsw_nm_sw_ptEvtWkupFuncTbl[])( NetworkHandleType nmChannelHandle );    /* Event wake-up frame transmission function table */
extern void        (* BswConst bsw_nm_sw_ptEvtWkupClFuncTbl[])( NetworkHandleType nmChannelHandle );  /* Event wake-up frame transmission cancellation function table */

extern void                      (* BswConst bsw_nm_sw_ptStopSyncSleepFunc)( NetworkHandleType NetworkHandle );                                /* Stop cooperation bus-sleep */
extern void                      (* BswConst bsw_nm_sw_ptStopSleepDelayFunc)( NetworkHandleType NetworkHandle );                               /* Request to stop the sleep delay */
extern Std_ReturnType            (* BswConst bsw_nm_sw_ptSetSlpRdyBitFuncTbl[])( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit ); /* Sleep Ready Bit Setting Function Table */
extern Std_ReturnType            (* BswConst bsw_nm_sw_ptRqBusSyncFuncTbl[])( NetworkHandleType nmChannelHandle );                             /* Bus synchronization request table */
extern Std_ReturnType            (* BswConst bsw_nm_sw_ptSyncPncShutdownFuncTbl[])( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );          /* Cooperative PN sleep start timing notification function table */
extern Std_ReturnType            (* BswConst bsw_nm_sw_ptCancelReqSyncPncShutdownFuncTbl[])( NetworkHandleType nmNetworkHandle, PNCHandleType PNC ); /* Cooperative PN sleep cancellation function table */

#endif /* BSW_NM_SW_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-0-1          :2018/06/08                                             */
/*  v1-1-0          :2018/07/11                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2022/01/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
