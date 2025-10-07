/* can_rscf3c_h_m10700_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3C/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3C_H
#define     CAN_RSCF3C_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if(CAN_CFG_CV == CAN_USE)

/*▼▼▼▼▼ 対象CANIP指定 編集対象 ▼▼▼▼▼▼▼▼▼▼*/
#define CAN_CV_IP                       (CAN_IP_RSCF3C)
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/

/*▼▼▼▼▼ IP番号指定  編集対象外 ▼▼▼▼▼▼▼▼▼▼*/
#if(CAN_CFG_IP0 == CAN_CV_IP)
#define CAN_CV_CONVERT_NAME(x)          (Can_IP0##x)
#define CAN_CV_CONVERT_NAME_CV(x)       (Can_cv_IP0##x)
#else  /* (CAN_CFG_IP0 != CAN_CV_IP) */
#define CAN_CV_CONVERT_NAME(x)          (Can_IP1##x)
#define CAN_CV_CONVERT_NAME_CV(x)       (Can_cv_IP1##x)
#endif /* (CAN_CFG_IP0) */
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/

/*▼▼▼▼▼ マイコン共通シンボル  編集対象外 ▼▼▼▼▼*/
/* 公開関数 */
#define Can_Init                        (CAN_CV_CONVERT_NAME(_Init))
#define Can_InitController              (CAN_CV_CONVERT_NAME(_InitController))
#define Can_SetControllerMode           (CAN_CV_CONVERT_NAME(_SetControllerMode))
#define Can_MainFunction_Mode           (CAN_CV_CONVERT_NAME(_MainFunction_Mode))
#define Can_Shutdown                    (CAN_CV_CONVERT_NAME(_Shutdown))
#define Can_ResetController             (CAN_CV_CONVERT_NAME(_ResetController))
#define Can_SetBaudrate                 (CAN_CV_CONVERT_NAME(_SetBaudrate))
#define Can_CheckStopCompletion         (CAN_CV_CONVERT_NAME(_CheckStopCompletion))
#define Can_GetControllerStatus         (CAN_CV_CONVERT_NAME(_GetControllerStatus))

#define Can_Write                       (CAN_CV_CONVERT_NAME(_Write))
#define Can_MainFunction_Write          (CAN_CV_CONVERT_NAME(_MainFunction_Write))
#define Can_AbortSend                   (CAN_CV_CONVERT_NAME(_AbortSend))
#define Can_TxReq                       (CAN_CV_CONVERT_NAME(_TxReq))

#define Can_MainFunction_Read           (CAN_CV_CONVERT_NAME(_MainFunction_Read))

#define Can_MainFunction_BusOff         (CAN_CV_CONVERT_NAME(_MainFunction_BusOff))
#define Can_IllegalInterrupt_Global     (CAN_CV_CONVERT_NAME(_IllegalInterrupt_Global))
#define Can_CheckStuckRegister          (CAN_CV_CONVERT_NAME(_CheckStuckRegister))
#define Can_RefreshRegister             (CAN_CV_CONVERT_NAME(_RefreshRegister))
#define Can_MainFunction_Fail           (CAN_CV_CONVERT_NAME(_MainFunction_Fail))
#define Can_GetErrorStatus              (CAN_CV_CONVERT_NAME(_GetErrorStatus))

#if(CAN_CFG_IP1 == CAN_CV_IP)
#define Can_TxFinish_0                  (Can_TxFinish_8)
#define Can_TxFinish_1                  (Can_TxFinish_9)
#define Can_TxFinish_2                  (Can_TxFinish_10)
#define Can_TxFinish_3                  (Can_TxFinish_11)
#define Can_TxFinish_4                  (Can_TxFinish_12)
#define Can_TxFinish_5                  (Can_TxFinish_13)
#define Can_TxFinish_6                  (Can_TxFinish_14)
#define Can_TxFinish_7                  (Can_TxFinish_15)

#define Can_RxFinish_0                  (Can_RxFinish_8)
#define Can_RxFinish_1                  (Can_RxFinish_9)
#define Can_RxFinish_2                  (Can_RxFinish_10)
#define Can_RxFinish_3                  (Can_RxFinish_11)
#define Can_RxFinish_4                  (Can_RxFinish_12)
#define Can_RxFinish_5                  (Can_RxFinish_13)
#define Can_RxFinish_6                  (Can_RxFinish_14)
#define Can_RxFinish_7                  (Can_RxFinish_15)

#define Can_IllegalInterrupt_0          (Can_IllegalInterrupt_8)
#define Can_IllegalInterrupt_1          (Can_IllegalInterrupt_9)
#define Can_IllegalInterrupt_2          (Can_IllegalInterrupt_10)
#define Can_IllegalInterrupt_3          (Can_IllegalInterrupt_11)
#define Can_IllegalInterrupt_4          (Can_IllegalInterrupt_12)
#define Can_IllegalInterrupt_5          (Can_IllegalInterrupt_13)
#define Can_IllegalInterrupt_6          (Can_IllegalInterrupt_14)
#define Can_IllegalInterrupt_7          (Can_IllegalInterrupt_15)
#endif /* (CAN_CFG_IP1 == CAN_CV_IP) */

#define Can_EdgeInit                    (CAN_CV_CONVERT_NAME(_EdgeInit))
#define Can_EdgeEnableDetect            (CAN_CV_CONVERT_NAME(_EdgeEnableDetect))
#define Can_EdgeDisableDetect           (CAN_CV_CONVERT_NAME(_EdgeDisableDetect))
#define Can_EdgeClearStatus             (CAN_CV_CONVERT_NAME(_EdgeClearStatus))
#define Can_EdgeGetStatus               (CAN_CV_CONVERT_NAME(_EdgeGetStatus))

#define Can_UTxConfirmation             (CAN_CV_CONVERT_NAME(_UTxConfirmation))
#define Can_URxIndication               (CAN_CV_CONVERT_NAME(_URxIndication))
#define Can_UPreStart                   (CAN_CV_CONVERT_NAME(_UPreStart))

/* 内部関数 */
#define Can_st_ControllerStop           (CAN_CV_CONVERT_NAME(_st_ControllerStop))
#define Can_st_StopInd                  (CAN_CV_CONVERT_NAME(_st_StopInd))
#define Can_st_PreStart                 (CAN_CV_CONVERT_NAME(_st_PreStart))
#define Can_st_InitReg                  (CAN_CV_CONVERT_NAME(_st_InitReg))
#define Can_st_SetControl               (CAN_CV_CONVERT_NAME(_st_SetControl))
#define Can_st_Start                    (CAN_CV_CONVERT_NAME(_st_Start))
#define Can_st_Stop                     (CAN_CV_CONVERT_NAME(_st_Stop))
#define Can_st_Reset                    (CAN_CV_CONVERT_NAME(_st_Reset))
#define Can_st_ChkStart                 (CAN_CV_CONVERT_NAME(_st_ChkStart))
#define Can_st_ChkStop                  (CAN_CV_CONVERT_NAME(_st_ChkStop))
#define Can_st_ChkReset                 (CAN_CV_CONVERT_NAME(_st_ChkReset))
#define Can_st_ShutdownReg              (CAN_CV_CONVERT_NAME(_st_ShutdownReg))
#define Can_st_SetConfigMbox            (CAN_CV_CONVERT_NAME(_st_SetConfigMbox))
#define Can_st_SetBaudrate              (CAN_CV_CONVERT_NAME(_st_SetBaudrate))

#define Can_tx_Init                     (CAN_CV_CONVERT_NAME(_tx_Init))
#define Can_tx_ClearTxInf               (CAN_CV_CONVERT_NAME(_tx_ClearTxInf))
#define Can_tx_TxConfMbox               (CAN_CV_CONVERT_NAME(_tx_TxConfMbox))
#define Can_tx_TxReq_CanFrame           (CAN_CV_CONVERT_NAME(_tx_TxReq_CanFrame))
#define Can_tx_TxReq_CanFdFrame         (CAN_CV_CONVERT_NAME(_tx_TxReq_CanFdFrame))
#define Can_tx_ChkTxFinMbox             (CAN_CV_CONVERT_NAME(_tx_ChkTxFinMbox))
#define Can_tx_TxAbt                    (CAN_CV_CONVERT_NAME(_tx_TxAbt))
#define Can_tx_ChkTxAbtMbox             (CAN_CV_CONVERT_NAME(_tx_ChkTxAbtMbox))

#define Can_rx_RxIndMbox                (CAN_CV_CONVERT_NAME(_rx_RxIndMbox))
#define Can_rx_ChkRxFinMbox             (CAN_CV_CONVERT_NAME(_rx_ChkRxFinMbox))

#define Can_fs_CheckRamU2               (CAN_CV_CONVERT_NAME(_fs_CheckRamU2))

#define Can_fs_Init                     (CAN_CV_CONVERT_NAME(_fs_Init))
#define Can_fs_ClearBusOffStatus        (CAN_CV_CONVERT_NAME(_fs_ClearBusOffStatus))
#define Can_fs_BusOffInd                (CAN_CV_CONVERT_NAME(_fs_BusOffInd))
#define Can_fs_PrepChkRegRetry          (CAN_CV_CONVERT_NAME(_fs_PrepChkRegRetry))
#define Can_fs_ChkBusOff                (CAN_CV_CONVERT_NAME(_fs_ChkBusOff))
#define Can_fs_BusOffRecovery           (CAN_CV_CONVERT_NAME(_fs_BusOffRecovery))
#define Can_fs_ChkReg                   (CAN_CV_CONVERT_NAME(_fs_ChkReg))
#define Can_fs_CheckMpu                 (CAN_CV_CONVERT_NAME(_fs_CheckMpu))
#define Can_fs_ResetInterrupt           (CAN_CV_CONVERT_NAME(_fs_ResetInterrupt))
#define Can_fs_DisableInterrupt         (CAN_CV_CONVERT_NAME(_fs_DisableInterrupt))
#define Can_fs_GetErrorStatus           (CAN_CV_CONVERT_NAME(_fs_GetErrorStatus))
#define Can_fs_ChkParameter             (CAN_CV_CONVERT_NAME(_fs_ChkParameter))
#define Can_fs_PhyPrepChkRegRetry       (CAN_CV_CONVERT_NAME(_fs_PhyPrepChkRegRetry))

/* 上位層通知関数 */
#define CanIf_ControllerModeIndication  (CAN_CV_CONVERT_NAME_CV(_CntrlMdInd))
#define CanIf_TxConfirmation            (CAN_CV_CONVERT_NAME_CV(_TxConfirmation))
#define CanIf_RxIndication              (CAN_CV_CONVERT_NAME_CV(_RxIndication))
#define CanIf_ControllerBusOff          (CAN_CV_CONVERT_NAME_CV(_ControllerBusOff))
#define CanIf_ControllerFail            (CAN_CV_CONVERT_NAME_CV(_ControllerFail))

/* log層公開変数 */
#define Can_st_u2ControllerStatus       (CAN_CV_CONVERT_NAME(_st_u2ControllerStatus))

/* log層公開定数 */
#define Can_tb_stControllerCfgTbl       (CAN_CV_CONVERT_NAME(_tb_stControllerCfgTbl))
#define Can_tb_stHohMbAlloc             (CAN_CV_CONVERT_NAME(_tb_stHohMbAlloc))
#define Can_tb_ptHohCfgTbl              (CAN_CV_CONVERT_NAME(_tb_ptHohCfgTbl))
#define Can_tb_u1RegChkNum              (CAN_CV_CONVERT_NAME(_tb_u1RegChkNum))
#define Can_tb_u1ControllerNumMax       (CAN_CV_CONVERT_NAME(_tb_u1ControllerNumMax))
#define Can_tb_u2HrhNumMax              (CAN_CV_CONVERT_NAME(_tb_u2HrhNumMax))
#define Can_tb_u2HthNumMax              (CAN_CV_CONVERT_NAME(_tb_u2HthNumMax))
#define Can_tb_stUTxMbAlloc             (CAN_CV_CONVERT_NAME(_tb_stUTxMbAlloc))

/* log層静的変数 */
#define Can_tx_u2TxPduId                (CAN_CV_CONVERT_NAME(_tx_u2TxPduId))

#define Can_fs_u1BusOffStatus           (CAN_CV_CONVERT_NAME(_fs_u1BusOffStatus))
#define Can_fs_u1RegChkWaitCnt          (CAN_CV_CONVERT_NAME(_fs_u1RegChkWaitCnt))
#define Can_fs_u1RegChkHist             (CAN_CV_CONVERT_NAME(_fs_u1RegChkHist))

/* ユーザ定義テーブル */
#define Can_stHohCfgTbl                 (CAN_CV_CONVERT_NAME(_stHohCfgTbl))
#define Can_stBaudrateSwtCfgTbl         (CAN_CV_CONVERT_NAME(_stBdrtSwtCfgTbl))
#define Can_stBRSwtCfgTbl_ARYSIZE       (CAN_CV_CONVERT_NAME(_stBRSwtCfgTbl_ARYSZ))
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/

/*▼▼▼▼▼ マイコン個別シンボル  編集対象外 ▼▼▼▼▼*/
#if(CAN_CV_IP == CAN_IP_RSCF3C)

/* 内部関数 */
#define Can_st_GlobalMode_Reset2Test    (CAN_CV_CONVERT_NAME(_st_GlblMd_Rst2Tst))
#define Can_st_GlobalMode_Any2Reset     (CAN_CV_CONVERT_NAME(_st_GlblMd_Any2Rst))

#define Can_st_GlobalMode_Reset2Stop    (CAN_CV_CONVERT_NAME(_st_GlblMd_Rst2Stp))
#define Can_st_GlobalMode_Reset2Comm    (CAN_CV_CONVERT_NAME(_st_GlblMd_Rst2Com))
#define Can_st_ChannelMode_Any2Reset    (CAN_CV_CONVERT_NAME(_st_ChMd_Any2Rst))
#define Can_st_ChannelMode_Reset2Stop   (CAN_CV_CONVERT_NAME(_st_ChMd_Rst2Stp))
#define Can_st_ChannelMode_Reset2Comm   (CAN_CV_CONVERT_NAME(_st_ChMd_Rst2Com))
#define Can_st_GlobalRegCheck           (CAN_CV_CONVERT_NAME(_st_GlobalRegCheck))
#define Can_st_InitGlobalReg            (CAN_CV_CONVERT_NAME(_st_InitGlobalReg))
#define Can_st_InitChannelReg           (CAN_CV_CONVERT_NAME(_st_InitChannelReg))
#define Can_st_SetGlobalReg             (CAN_CV_CONVERT_NAME(_st_SetGlobalReg))
#define Can_st_SetChannelReg            (CAN_CV_CONVERT_NAME(_st_SetChannelReg))
#define Can_st_StopGlobal               (CAN_CV_CONVERT_NAME(_st_StopGlobal))
#define Can_st_StopChannel              (CAN_CV_CONVERT_NAME(_st_StopChannel))
#define Can_st_StartGlobal              (CAN_CV_CONVERT_NAME(_st_StartGlobal))
#define Can_st_StartChannel             (CAN_CV_CONVERT_NAME(_st_StartChannel))
#define Can_st_ResetGlobal              (CAN_CV_CONVERT_NAME(_st_ResetGlobal))
#define Can_st_ResetChannel             (CAN_CV_CONVERT_NAME(_st_ResetChannel))
#define Can_st_SetRxRule                (CAN_CV_CONVERT_NAME(_st_SetRxRule))
#define Can_st_PhyInit                  (CAN_CV_CONVERT_NAME(_st_PhyInit))

#define Can_tx_TxAbtAll                 (CAN_CV_CONVERT_NAME(_tx_TxAbtAll))

#define Can_tx_SetTxReg                 (CAN_CV_CONVERT_NAME(_tx_SetTxReg))
#define Can_tx_TxFinish                 (CAN_CV_CONVERT_NAME(_tx_TxFinish))

#define Can_rx_RxFinish                 (CAN_CV_CONVERT_NAME(_rx_RxFinish))

#define Can_fs_PhyInit                  (CAN_CV_CONVERT_NAME(_fs_PhyInit))
#define Can_fs_MpuFailInd               (CAN_CV_CONVERT_NAME(_fs_MpuFailInd))

#define Can_fs_IllegalInterrupt         (CAN_CV_CONVERT_NAME(_fs_IllegalInterrupt))
#define Can_fs_RAMTest                  (CAN_CV_CONVERT_NAME(_fs_RAMTest))
#define Can_fs_RAMTestPage              (CAN_CV_CONVERT_NAME(_fs_RAMTestPage))
#define Can_fs_RAMTestEnable            (CAN_CV_CONVERT_NAME(_fs_RAMTestEnable))
#define Can_fs_RAMTestDisable           (CAN_CV_CONVERT_NAME(_fs_RAMTestDisable))

#define Can_tb_SYNCP                    (CAN_CV_CONVERT_NAME(_tb_SYNCP))

/* phy層公開変数 */
#define Can_st_u1BRSUse                 (CAN_CV_CONVERT_NAME(_st_u1BRSUse))

/* phy層公開定数 */
#define Can_tb_stCtrlInfo               (CAN_CV_CONVERT_NAME(_tb_stCtrlInfo))
#define Can_tb_stMbNum                  (CAN_CV_CONVERT_NAME(_tb_stMbNum))
#define Can_tb_stTxMbBit                (CAN_CV_CONVERT_NAME(_tb_stTxMbBit))
#define Can_tb_u4RxMask                 (CAN_CV_CONVERT_NAME(_tb_u4RxMask))
#define Can_tb_stCheckStuckPara         (CAN_CV_CONVERT_NAME(_tb_stCheckStuckPara))
#define Can_tb_stRxRuleSetting          (CAN_CV_CONVERT_NAME(_tb_stRxRuleSetting))
#define Can_tb_stChReg                  (CAN_CV_CONVERT_NAME(_tb_stChReg))
#define Can_tb_stGlobalReg              (CAN_CV_CONVERT_NAME(_tb_stGlobalReg))
#define Can_tb_stSetRSCANReg            (CAN_CV_CONVERT_NAME(_tb_stSetRSCANReg))
#define Can_tb_u1BRSInitConf            (CAN_CV_CONVERT_NAME(_tb_u1BRSInitConf))
#define Can_tb_ptBaudrateSwtCfgTbl      (CAN_CV_CONVERT_NAME(_tb_ptBdrtSwtCfgTbl))
#define Can_tb_ptBRSwtCfgTbl_ARYSIZE    (CAN_CV_CONVERT_NAME(_tb_ptBRSwtCfgTbl_ARYSZ))
#define Can_tb_u4RAMInitCycleMax        (CAN_CV_CONVERT_NAME(_tb_u4RAMInitCycleMax))
#define Can_tb_u2CmodeRst2ComWaitCnt    (CAN_CV_CONVERT_NAME(_tb_u2CmodeRst2ComWtCnt))
#define Can_tb_u2CmodeAny2RstWaitCnt    (CAN_CV_CONVERT_NAME(_tb_u2CmodeAny2RstWtCnt))
#define Can_tb_u2GmodeAny2RstWaitCnt    (CAN_CV_CONVERT_NAME(_tb_u2GmodeAny2RstWtCnt))
#define Can_tb_u1CtrlNum                (CAN_CV_CONVERT_NAME(_tb_u1CtrlNum))
#define Can_tb_u2MaxNumRxRule           (CAN_CV_CONVERT_NAME(_tb_u2MaxNumRxRule))
#define Can_tb_u1RxRulePageNum          (CAN_CV_CONVERT_NAME(_tb_u1RxRulePageNum))
#define Can_tb_u2LastTestpage           (CAN_CV_CONVERT_NAME(_tb_u2LstTstpage))
#define Can_tb_u1LastTestpageRegNum     (CAN_CV_CONVERT_NAME(_tb_u1LastTestpageRegNum))
#define Can_tb_u4GAFLCFG0Conf           (CAN_CV_CONVERT_NAME(_tb_u4GAFLCFG0Conf))
#define Can_tb_u4GAFLCFG1Conf           (CAN_CV_CONVERT_NAME(_tb_u4GAFLCFG1Conf))
#define Can_tb_u4GCFGConf               (CAN_CV_CONVERT_NAME(_tb_u4GCFGConf))
#define Can_tb_u4GFDCFGConf             (CAN_CV_CONVERT_NAME(_tb_u4GFDCFGConf))
#define Can_tb_u1FifoReadSize           (CAN_CV_CONVERT_NAME(_tb_u1FifoReadSize))

/* phy層静的変数 */
#define Can_fs_u1RegChkStatus           (CAN_CV_CONVERT_NAME(_fs_u1RegChkStatus))
#define Can_fs_u1MpuFail                (CAN_CV_CONVERT_NAME(_fs_u1MpuFail))

/* phy層静的定数 */
#define Can_tx_u1DlcVal                 (CAN_CV_CONVERT_NAME(_tx_u1DlcVal))
#define Can_tx_u1DataSize               (CAN_CV_CONVERT_NAME(_tx_u1DataSize))

#define Can_rx_u1DataLengthVal          (CAN_CV_CONVERT_NAME(_rx_u1DataLengthVal))

#endif/* (CAN_CV_IP == CAN_IP_RSCF3C) */
/*▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* (CAN_CFG_CV == CAN_USE) */
#endif /* CAN_RSCF3C_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
