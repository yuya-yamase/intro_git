/* Dcm_Main_EvtDistr_Cfg_c(v5-9-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_EvtDistr_Cfg/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Main/cfg/Dcm_Main_EvtDistr_Cfg.h"
#include <Dcm.h>

#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Dsp_SID10.h>
#include <Dcm/Dcm_Dsp_SID14.h>
#include <Dcm/Dcm_Dsp_SID19_Sub02.h>
#include <Dcm/Dcm_Dsp_SID19_Sub03.h>
#include <Dcm/Dcm_Dsp_SID19_Sub04.h>
#include <Dcm/Dcm_Dsp_SID19_Sub17.h>
#include <Dcm/Dcm_Dsp_SID19_Sub18.h>
#include <Dcm/Dcm_Dsp_SID27.h>
#include <Dcm/Dcm_Dsp_SID28.h>
#include <Dcm/Dcm_Dsp_SID86.h>
#include <Dcm/Dcm_Apl_SID22.h>
#include <Dcm/Dcm_Apl_SID2E.h>
#include <Dcm/Dcm_Apl_SID2F.h>
#include <Dcm/Dcm_Apl_SID31.h>
#include <Dcm/Dcm_Apl_SIDBA.h>
#include <Dcm/Dcm_Dsp_StorageMng.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_IdToIndex[ DCM_M_EVTDISTR_DEFINED_ALL_ID_NUM ] = 
{
    (uint8)0U,                    /* DCM_M_EVTID_DSL_RECEIVE            */
    (uint8)1U,                    /* DCM_M_EVTID_DSL_TRANSMIT           */
    (uint8)2U,                    /* DCM_M_EVTID_DSL_CANCELRECEIVE      */
    (uint8)3U,                    /* DCM_M_EVTID_DSL_CANCELTXSERVICE    */
    (uint8)4U,                    /* DCM_M_EVTID_DSL_CONF_FUNCTIONALITY */
    (uint8)5U,                    /* DCM_M_EVTID_DSL_SETDEFSES          */
    (uint8)6U,                    /* DCM_M_EVTID_DSL_TXRETRY            */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_DSL_RESPREQ_AFRST      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_DSL_COMM_ACTIVE        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_DSL_PAGEDBUFFER        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_DSL_RESETTODEFSES      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID04_ALLCLEARDTC      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID04_CLEARCHK         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID09_GET_INFOTYPE     */
    (uint8)7U,                    /* DCM_M_EVTID_SID10_SETPROG          */
    (uint8)8U,                    /* DCM_M_EVTID_SID10_CHKSESCTRL       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID11_GETPRERESET      */
    (uint8)9U,                    /* DCM_M_EVTID_SID14_CLEARDTC         */
    (uint8)10U,                   /* DCM_M_EVTID_SID14_CLEARCHK         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB01_GETNOD     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB02_GETSIZE    */
    (uint8)11U,                   /* DCM_M_EVTID_SID19_SUB02_GETDTC     */
    (uint8)12U,                   /* DCM_M_EVTID_SID19_SUB03_GETRECORD  */
    (uint8)13U,                   /* DCM_M_EVTID_SID19_SUB04_DISREC     */
    (uint8)14U,                   /* DCM_M_EVTID_SID19_SUB04_GETSTS     */
    (uint8)15U,                   /* DCM_M_EVTID_SID19_SUB04_GETSIZE    */
    (uint8)16U,                   /* DCM_M_EVTID_SID19_SUB04_RMNASIZE   */
    (uint8)17U,                   /* DCM_M_EVTID_SID19_SUB04_GETFFDT    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB05_STDSDATA   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB05_GETSIZE    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB05_GETDSDT    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB06_DISREC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB06_GETEDR     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB0A_GETSIZE    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB0A_GETDTC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB17_GETSIZE    */
    (uint8)18U,                   /* DCM_M_EVTID_SID19_SUB17_GETDTC     */
    (uint8)19U,                   /* DCM_M_EVTID_SID19_SUB18_DISREC     */
    (uint8)20U,                   /* DCM_M_EVTID_SID19_SUB18_GETSTS     */
    (uint8)21U,                   /* DCM_M_EVTID_SID19_SUB18_GETSIZE    */
    (uint8)22U,                   /* DCM_M_EVTID_SID19_SUB18_GETFFDT    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB19_DISREC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB19_GETEDR     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB1A_GETSIZE    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB1A_GETDTC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB42_GETSIZE    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB42_GETDTC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB55_GETDTC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB56_GETSIZE    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID19_SUB56_GETDTC     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_DIDAVAILABLE     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_RANGE_DATA_LEN   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_CHKSUP_CYCLE     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_READ_DID_DATA    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_READ_CYCLE       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_UPDATEPAGE       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID22_UPDATERCRRP      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID23_READMEM          */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID23_UPDATEPAGE       */
    (uint8)23U,                   /* DCM_M_EVTID_SID27_GET_SEED         */
    (uint8)24U,                   /* DCM_M_EVTID_SID27_COMPARE_KEY      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID27_READCONF         */
    (uint8)25U,                   /* DCM_M_EVTID_SID28_COMPCOMCTRL      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID29_VRFYCERTUNIDIR   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID29_VRFYCERTBIDIR    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID29_VRFYPOWN         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2A_DIDAVAILABLE     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2A_RANGE_DATA_LEN   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2C_DIDAVAILABLE     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2C_CHKPOSSIZE       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2E_DIDAVAILABLE     */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2E_RANGE_DATA_LEN   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2E_WRITE_DID_DATA   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2F_IO_CONTROL       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID2F_READ_DATA        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID31_EXECUTE          */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID31_UPDATEPAGE       */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID31_UPDATERCRRP      */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID34_CHKDFID          */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID34_PROCREQDL        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID35_CHKDFID          */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID35_PROCREQUL        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_CHKMSGLEN        */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_CHKREQSEQUENCE   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_CHKREQSEQUENCEUL */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_CHKTFRDATSUSPEND */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_CHKTFRDATSUSPENDUL */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_PROCTFRDATAWRITE */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID36_PROCTFRDATAREAD */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID37_CHKPROGPROCFIN   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID37_PROCREQTFREXIT   */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID3D_WRITEMEM         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID85_SUB01_ENA_DTC    */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SID85_SUB02_DIS_DTC    */
    (uint8)26U,                   /* DCM_M_EVTID_SID86_SERVTORESPTO     */
    (uint8)27U,                   /* DCM_M_EVTID_SID86_RESPQUEOVER      */
    (uint8)28U,                   /* DCM_M_EVTID_SID86_READCOMP         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SIDA4_CLEARDTC         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SIDA4_CLEARCHK         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SIDA4_CLEAROBS         */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_SIDBA_GETBEHAVIORMEMORY */
    DCM_M_EVTDISTR_INVALID_VAL,   /* DCM_M_EVTID_DSL_TXIFRETRY          */
    (uint8)29U,                   /* DCM_M_EVTID_STORAGEMNG_READALL     */
    (uint8)30U,                   /* DCM_M_EVTID_STORAGEMNG_READBLOCK   */
    (uint8)31U,                   /* DCM_M_EVTID_STORAGEMNG_WRITEGETSTS */
    (uint8)32U,                   /* DCM_M_EVTID_STORAGEMNG_WRITEDEQ    */
    (uint8)33U                    /* DCM_M_EVTID_STORAGEMNG_WRITERETRY  */
};

CONST( AB_83_ConstV Dcm_M_EvtDistr_FuncType, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_NoticeTable[ DCM_M_EVTDISTR_ID_NUM ] = 
{
    &Dcm_Dsl_ReceiveCbk,                    /* DCM_M_EVTID_DSL_RECEIVE            */
    &Dcm_Dsl_TransmitCbk,                   /* DCM_M_EVTID_DSL_TRANSMIT           */
    &Dcm_Dsl_CancelReceiveCbk,              /* DCM_M_EVTID_DSL_CANCELRECEIVE      */
    &Dcm_Dsl_CancelTxCancelServiceCbk,      /* DCM_M_EVTID_DSL_CANCELTXSERVICE    */
    &Dcm_Dsl_DataConfFunctionalityCbk,      /* DCM_M_EVTID_DSL_CONF_FUNCTIONALITY */
    &Dcm_Dsl_SetDefSesCbk,                  /* DCM_M_EVTID_DSL_SETDEFSES          */
    &Dcm_Dsl_TxRetryCbk,                    /* DCM_M_EVTID_DSL_TXRETRY            */
    &Dcm_Dsp_SID10_Cbk,                     /* DCM_M_EVTID_SID10_SETPROG          */
    &Dcm_Dsp_SID10_ChkSesCtrlCbk,           /* DCM_M_EVTID_SID10_CHKSESCTRL       */
    &Dcm_Dsp_SID14_Cbk,                     /* DCM_M_EVTID_SID14_CLEARDTC         */
    &Dcm_Dsp_SID14_ClearCheckCbk,           /* DCM_M_EVTID_SID14_CLEARCHK         */
    &Dcm_Dsp_SID19_Sub02_GetDTCCbk,         /* DCM_M_EVTID_SID19_SUB02_GETDTC     */
    &Dcm_Dsp_SID19_Sub03_Cbk,               /* DCM_M_EVTID_SID19_SUB03_GETRECORD  */
    &Dcm_Dsp_SID19_Sub04_DisUpdCbk,         /* DCM_M_EVTID_SID19_SUB04_DISREC     */
    &Dcm_Dsp_SID19_Sub04_GetDtcStCbk,       /* DCM_M_EVTID_SID19_SUB04_GETSTS     */
    &Dcm_Dsp_SID19_Sub04_GetSzFrzCbk,       /* DCM_M_EVTID_SID19_SUB04_GETSIZE    */
    &Dcm_Dsp_SID19_Sub04_RmNASzCbk,         /* DCM_M_EVTID_SID19_SUB04_RMNASIZE   */
    &Dcm_Dsp_SID19_Sub04_GetFrzDtCbk,       /* DCM_M_EVTID_SID19_SUB04_GETFFDT    */
    &Dcm_Dsp_SID19_Sub17_GetDTCCbk,         /* DCM_M_EVTID_SID19_SUB17_GETDTC     */
    &Dcm_Dsp_SID19_Sub18_DisUpdCbk,         /* DCM_M_EVTID_SID19_SUB18_DISREC     */
    &Dcm_Dsp_SID19_Sub18_GetDtcStCbk,       /* DCM_M_EVTID_SID19_SUB18_GETSTS     */
    &Dcm_Dsp_SID19_Sub18_GetSzFrzCbk,       /* DCM_M_EVTID_SID19_SUB18_GETSIZE    */
    &Dcm_Dsp_SID19_Sub18_GetFrzDtCbk,       /* DCM_M_EVTID_SID19_SUB18_GETFFDT    */
    &Dcm_Dsp_SID27_GetSeedCbk,              /* DCM_M_EVTID_SID27_GET_SEED         */
    &Dcm_Dsp_SID27_CompareKeyCbk,           /* DCM_M_EVTID_SID27_COMPARE_KEY      */
    &Dcm_Dsp_SID28_Cbk,                     /* DCM_M_EVTID_SID28_COMPCOMCTRL      */
    &Dcm_Dsp_SID86_TrigServToRespTo_Cbk,    /* DCM_M_EVTID_SID86_SERVTORESPTO     */
    &Dcm_Dsp_SID86_RespQueueOver_Cbk,       /* DCM_M_EVTID_SID86_RESPQUEOVER      */
    &Dcm_Dsp_SID86_AllReadCompleteCbk,      /* DCM_M_EVTID_SID86_READCOMP         */
    &Dcm_Dsp_StorageMng_ReReadAllCbk,       /* DCM_M_EVTID_STORAGEMNG_READALL     */
    &Dcm_Dsp_StorageMng_ReReadBlockCbk,     /* DCM_M_EVTID_STORAGEMNG_READBLOCK   */
    &Dcm_Dsp_StorageMng_GetErrorStsCbk,     /* DCM_M_EVTID_STORAGEMNG_WRITEGETSTS */
    &Dcm_Dsp_StorageMng_DeQueueCbk,         /* DCM_M_EVTID_STORAGEMNG_WRITEDEQ    */
    &Dcm_Dsp_StorageMng_RewriteCbk          /* DCM_M_EVTID_STORAGEMNG_WRITERETRY  */
};

CONST( AB_83_ConstV Dcm_M_EvtDistr_FuncType, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_NoticeTable_Ex[ DCM_M_EVTDISTR_ID_EX_TBL ] = 
{
    NULL_PTR
};

CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_u1EventIdNum = DCM_M_EVTDISTR_ID_NUM;
CONST( AB_83_ConstV uint8, DCM_CONFIG_DATA ) Dcm_M_EvtDistr_u1EventIdExNum = DCM_M_EVTDISTR_ID_EX_NUM;

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-02-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
