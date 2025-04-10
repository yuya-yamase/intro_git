/* Gdn_CanTp_c_00_0003 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | ダイアグCAN通信トランスポート層                              */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/05/15   DN毛     新規作成                                  */
/*  00_0001   2018/02/13   AUBASS   リプログ対応                              */
/*  00_0002   2020/03/10   AUBASS   Update                                    */
/*  00_0003   2022/12/06   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn_Types.h>
#include <Gdn_Ucfg.h>
#include <PduR/Gdn_PduR.h>
#include <GdnWrapper/Gdn_CanIf.h>
#include <GdnWrapper/Gdn_TmrSrv.h>
#include <ReprogOpt.h>
#include "Gdn_CanTp.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_UINT8_MAX     ((gdn_uint8)0xFFU)

/******************************** DATA PROCESS ********************************/
#define GDN_CANTP_Shift1Byte    ((gdn_uint8)8U)
#define GDN_CANTP_MaxTimerIdx   ((gdn_uint8)0U)
#define GDN_CANTP_MinTimerIdx   ((gdn_uint8)1U)

/******************************** CANTP STATUS ********************************/
#define GDN_CANTP_Idle          ((Gdn_CanTp_StatusType)0x00U)   /* 00 000 000 */
#define GDN_CANTP_RxSendCTS     ((Gdn_CanTp_StatusType)0x49U)   /* 01 001 001 */
#define GDN_CANTP_RxSendOVFL    ((Gdn_CanTp_StatusType)0x4AU)   /* 01 001 010 */
#define GDN_CANTP_RxSendWT      ((Gdn_CanTp_StatusType)0x4CU)   /* 01 001 100 */
#define GDN_CANTP_RxDelayCTS    ((Gdn_CanTp_StatusType)0x51U)   /* 01 010 001 */
#define GDN_CANTP_RxDelayOVFL   ((Gdn_CanTp_StatusType)0x52U)   /* 01 010 010 */
#define GDN_CANTP_RxBusy        ((Gdn_CanTp_StatusType)0x54U)   /* 01 010 100 */
#define GDN_CANTP_RxWaitCF      ((Gdn_CanTp_StatusType)0x61U)   /* 01 100 001 */
#define GDN_CANTP_TxSendFF      ((Gdn_CanTp_StatusType)0x89U)   /* 10 001 001 */
#define GDN_CANTP_TxSendSF      ((Gdn_CanTp_StatusType)0x8AU)   /* 10 001 010 */
#define GDN_CANTP_TxSendCF      ((Gdn_CanTp_StatusType)0x8CU)   /* 10 001 100 */
#define GDN_CANTP_TxWaitFC1     ((Gdn_CanTp_StatusType)0x91U)   /* 10 010 001 */
#define GDN_CANTP_TxWaitFCx     ((Gdn_CanTp_StatusType)0x92U)   /* 10 010 010 */
#define GDN_CANTP_TxDelayCF     ((Gdn_CanTp_StatusType)0xA1U)   /* 10 100 001 */
#define GDN_CANTP_TxGetDelay    ((Gdn_CanTp_StatusType)0xA2U)   /* 10 100 010 */
#define GDN_CANTP_TxGetNoDelay  ((Gdn_CanTp_StatusType)0xA4U)   /* 10 100 100 */

#define GDN_CANTP_ShutDown      ((gdn_uint8)0x00U)  /* AUTOSAR: CANTP_OFF */
#define GDN_CANTP_Active        ((gdn_uint8)0xA5U)  /* AUTOSAR: CANTP_ON  */

/********************************* N_PCI TYPE *********************************/
#define GDN_CANTP_SF            ((gdn_uint8)0x00U)
#define GDN_CANTP_FF            ((gdn_uint8)0x10U)
#define GDN_CANTP_CF            ((gdn_uint8)0x20U)
#define GDN_CANTP_FC            ((gdn_uint8)0x30U)
#define GDN_CANTP_HiNibbleMask  ((gdn_uint8)0xF0U)
#define GDN_CANTP_LoNibbleMask  ((gdn_uint8)0x0FU)
#define GDN_CANTP_FCCTS         ((gdn_uint8)0x30U)
#define GDN_CANTP_FCWT          ((gdn_uint8)0x31U)
#define GDN_CANTP_FCOVFL        ((gdn_uint8)0x32U)
#define GDN_CANTP_NPCISizeSF    ((Gdn_PduLengthType)1U)
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
#define GDN_CANTP_FD_NPCISizeSF ((Gdn_PduLengthType)2U)
#endif
#define GDN_CANTP_NPCISizeFF    ((Gdn_PduLengthType)2U)
#define GDN_CANTP_NPCISizeCF    ((Gdn_PduLengthType)1U)
#define GDN_CANTP_NPCISizeFC    ((Gdn_PduLengthType)3U)

/******************************** N_PCI CHECK *********************************/
#define GDN_CANTP_BSMaxValue    ((Gdn_CanTp_BlockSizeType)255U)
#define GDN_CANTP_BSMinValue    ((Gdn_CanTp_BlockSizeType)0U)
#define GDN_CANTP_STminMaxValue ((Gdn_CanTp_STminType)127U)
#define GDN_CANTP_STminMinValue ((Gdn_CanTp_STminType)0U)
#define GDN_CANTP_STmin1ms      ((Gdn_CanTp_STminType)1U)
#define GDN_CANTP_STminMicroMin ((Gdn_CanTp_STminType)0xF1U)
#define GDN_CANTP_STminMicroMax ((Gdn_CanTp_STminType)0xF9U)

/********************************* DLC CHECK **********************************/
#define GDN_CANTP_NPCIOffSet_N  ((Gdn_PduLengthType)0U)
#define GDN_CANTP_NPCIOffSet_E  ((Gdn_PduLengthType)1U)
#define GDN_CANTP_DLCMinSize_N  ((Gdn_PduLengthType)2U)
#define GDN_CANTP_DLCMinSize_E  ((Gdn_PduLengthType)3U)
#define GDN_CANTP_DLCMaxSize    ((Gdn_PduLengthType)8U)
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
#define GDN_CANTP_FD_DLCMaxSize ((Gdn_PduLengthType)64U)
#endif
#define GDN_CANTP_MaxTxLength   ((Gdn_PduLengthType)0xFFFU)
#define GDN_CANTP_FCMinSize_N   (GDN_CANTP_NPCIOffSet_N + GDN_CANTP_NPCISizeFC)
#define GDN_CANTP_FCMinSize_E   (GDN_CANTP_NPCIOffSet_E + GDN_CANTP_NPCISizeFC)
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
#define GDN_CANTP_CAN_DL_8       ((Gdn_PduLengthType)8U)
#define GDN_CANTP_CAN_DL_12      ((Gdn_PduLengthType)12U)
#define GDN_CANTP_CAN_DL_16      ((Gdn_PduLengthType)16U)
#define GDN_CANTP_CAN_DL_20      ((Gdn_PduLengthType)20U)
#define GDN_CANTP_CAN_DL_24      ((Gdn_PduLengthType)24U)
#define GDN_CANTP_CAN_DL_32      ((Gdn_PduLengthType)32U)
#define GDN_CANTP_CAN_DL_48      ((Gdn_PduLengthType)48U)
#define GDN_CANTP_CAN_DL_64      ((Gdn_PduLengthType)64U)
#define GDN_CANTP_OptiTblSize    ((gdn_uint8)65U)
#define GDN_CANTP_SFDLMin_8      ((Gdn_PduLengthType)8U)
#define GDN_CANTP_SFDLMin_11     ((Gdn_PduLengthType)11U)
#define GDN_CANTP_SFDLMin_15     ((Gdn_PduLengthType)15U)
#define GDN_CANTP_SFDLMin_19     ((Gdn_PduLengthType)19U)
#define GDN_CANTP_SFDLMin_23     ((Gdn_PduLengthType)23U)
#define GDN_CANTP_SFDLMin_31     ((Gdn_PduLengthType)31U)
#define GDN_CANTP_SFDLMin_47     ((Gdn_PduLengthType)47U)
#define GDN_CANTP_SFDLMinTblSize ((gdn_uint8)7U)
#define GDN_CANTP_SFDLInvalid    ((Gdn_PduLengthType)0xFFFFU)
#define GDN_CANTP_FD_SFDLIndex   ((Gdn_PduLengthType)1U)
#define GDN_CANTP_FD_SFFisrtByte ((gdn_uint8)0x00U)
#define GDN_CANTP_FFDLMinGapVal  ((Gdn_PduLengthType)1U)
#endif

#define GDN_CANTP_SFDLMaxSize_N (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_N - GDN_CANTP_NPCISizeSF)
#define GDN_CANTP_SFDLMaxSize_E (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_E - GDN_CANTP_NPCISizeSF)
#define GDN_CANTP_FFDLMinSize_N (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_N)
#define GDN_CANTP_FFDLMinSize_E (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_E)
#define GDN_CANTP_FFDataSize_N  (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_N - GDN_CANTP_NPCISizeFF)
#define GDN_CANTP_FFDataSize_E  (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_E - GDN_CANTP_NPCISizeFF)
#define GDN_CANTP_CFDLMaxSize_N (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_N - GDN_CANTP_NPCISizeCF)
#define GDN_CANTP_CFDLMaxSize_E (GDN_CANTP_DLCMaxSize - GDN_CANTP_NPCIOffSet_E - GDN_CANTP_NPCISizeCF)

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
#define GDN_CANTP_FD_SFNPCITotalSize_N     (GDN_CANTP_NPCIOffSet_N + GDN_CANTP_FD_NPCISizeSF)
#define GDN_CANTP_FD_SFNPCITotalSize_E     (GDN_CANTP_NPCIOffSet_E + GDN_CANTP_FD_NPCISizeSF)
#define GDN_CANTP_FD_FFTotalGapSize_N      (GDN_CANTP_NPCIOffSet_N + GDN_CANTP_FFDLMinGapVal)
#define GDN_CANTP_FD_FFTotalGapSize_E      (GDN_CANTP_NPCIOffSet_E + GDN_CANTP_FFDLMinGapVal)
#define GDN_CANTP_FD_FFNPCITotalSize_N     (GDN_CANTP_NPCIOffSet_N + GDN_CANTP_NPCISizeFF)
#define GDN_CANTP_FD_FFNPCITotalSize_E     (GDN_CANTP_NPCIOffSet_E + GDN_CANTP_NPCISizeFF)
#define GDN_CANTP_FD_CFNPCITotalSize_N     (GDN_CANTP_NPCIOffSet_N + GDN_CANTP_NPCISizeCF)
#define GDN_CANTP_FD_CFNPCITotalSize_E     (GDN_CANTP_NPCIOffSet_E + GDN_CANTP_NPCISizeCF)
#define GDN_CANTP_FD_SFDLMaxSize_N( Size ) (( Size ) - GDN_CANTP_FD_SFNPCITotalSize_N)
#define GDN_CANTP_FD_SFDLMaxSize_E( Size ) (( Size ) - GDN_CANTP_FD_SFNPCITotalSize_E)
#define GDN_CANTP_FD_FFDLMinSize_N( Size ) (( Size ) - GDN_CANTP_FD_FFTotalGapSize_N)
#define GDN_CANTP_FD_FFDLMinSize_E( Size ) (( Size ) - GDN_CANTP_FD_FFTotalGapSize_E)
#define GDN_CANTP_FD_FFDataSize_N( Size )  (( Size ) - GDN_CANTP_FD_FFNPCITotalSize_N)
#define GDN_CANTP_FD_FFDataSize_E( Size )  (( Size ) - GDN_CANTP_FD_FFNPCITotalSize_E)
#define GDN_CANTP_FD_CFDLMaxSize_N( Size ) (( Size ) - GDN_CANTP_FD_CFNPCITotalSize_N)
#define GDN_CANTP_FD_CFDLMaxSize_E( Size ) (( Size ) - GDN_CANTP_FD_CFNPCITotalSize_E)
#endif

/*----------------------------------------------------------------------------*/
/* Local Types                                                                */
/*----------------------------------------------------------------------------*/
typedef gdn_uint8 Gdn_CanTp_StatusType;

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
typedef struct {
    gdn_uint8 DlcSize;
    gdn_uint8 MinSize;
}Gdn_CanTp_DlcMinSizeTblType;
#endif

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
    /* 検索処理 */
static gdn_uint8 Gdn_CanTp_SearchNAI( Gdn_PduIdType RxPduId, const gdn_uint8 RxFrame[], gdn_uint8* N_PCIType );
static Gdn_CanTp_ChannelType Gdn_CanTp_SearchTxChannel( Gdn_PduIdType TxPduId );

    /* フレーム受信時の条件判定と調停処理 */
static void Gdn_CanTp_JudgeSF( gdn_uint8 N_AI, Gdn_PduLengthType DLC,       gdn_uint8 RxFrame[] );
static void Gdn_CanTp_JudgeFF( gdn_uint8 N_AI, Gdn_PduLengthType DLC,       gdn_uint8 RxFrame[] );
static void Gdn_CanTp_JudgeCF( gdn_uint8 N_AI, Gdn_PduLengthType DLC,       gdn_uint8 RxFrame[] );
static void Gdn_CanTp_JudgeFC( gdn_uint8 N_AI, Gdn_PduLengthType DLC, const gdn_uint8 RxFrame[] );
static gdn_bool Gdn_CanTp_RxMediation( Gdn_CanTp_ChannelType RxChannel, gdn_uint8 NewN_AI );
static gdn_bool Gdn_CanTp_TxMediation( Gdn_CanTp_ChannelType TxChannel, gdn_uint8 NewN_AI );

    /* フレーム受信処理 */
static void Gdn_CanTp_ReceiveSF( gdn_uint8 N_AI, Gdn_PduLengthType DataSize, gdn_uint8 RxData[] );
static void Gdn_CanTp_ReceiveFF( gdn_uint8 N_AI, Gdn_PduLengthType DataSize, gdn_uint8 RxData[] );
static void Gdn_CanTp_ReceiveCF( gdn_uint8 N_AI, Gdn_PduLengthType DataSize, gdn_uint8 RxData[] );
static void Gdn_CanTp_ReceiveFCCTS( Gdn_CanTp_ChannelType RxChannel );

    /* フレーム送信処理 */
#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
static Gdn_Std_ReturnType Gdn_CanTp_SendFF( Gdn_PduIdType TxSduId, Gdn_PduLengthType MessageSize );
static Gdn_Std_ReturnType Gdn_CanTp_SendSF( Gdn_PduIdType TxSduId, Gdn_PduLengthType MessageSize );
#endif
static void               Gdn_CanTp_SendCF    ( gdn_uint8 TxN_AI );
static void               Gdn_CanTp_SendFCOVFL( gdn_uint8 RxN_AI );
static void               Gdn_CanTp_SendFCCTS ( gdn_uint8 RxN_AI );
static void               Gdn_CanTp_SendFCWT  ( gdn_uint8 RxN_AI );

    /* フレーム送信完了 */
static void Gdn_CanTp_FCWTConfirmation( Gdn_CanTp_ChannelType TxChannel );
static void Gdn_CanTp_CFConfirmation  ( Gdn_CanTp_ChannelType TxChannel );

    /* 送受信バッファ取得処理 */
static void Gdn_CanTp_RxDataRetry( Gdn_CanTp_ChannelType RxChannel );
static void Gdn_CanTp_TxDataRetry( Gdn_CanTp_ChannelType TxChannel );
static void Gdn_CanTp_GetRxBuffer( Gdn_CanTp_ChannelType RxChannel, gdn_uint8 RxN_AI );
static void Gdn_CanTp_GetTxBuffer( Gdn_CanTp_ChannelType TxChannel, gdn_uint8 TxN_AI, Gdn_TimeoutValueType MinTimer );

    /* タイムアウト処理 */
static void Gdn_CanTp_MinTimerTimeout( Gdn_CanTp_ChannelType TargetChannel );
static void Gdn_CanTp_MaxTimerTimeout( Gdn_CanTp_ChannelType TargetChannel );

static void Gdn_CanTp_SetTimer( Gdn_CanTp_ChannelType SetChannel, gdn_uint8 TimerIdx, Gdn_TimeoutValueType TimeoutValue );
static void Gdn_CanTp_ReleaseTimer( Gdn_CanTp_ChannelType SetChannel, gdn_uint8 TimerIdx );
static void Gdn_CanTp_UseNewParameter( Gdn_CanTp_ChannelType RxChannel, Gdn_CanTp_BlockSizeType TxBS, Gdn_CanTp_STminType TxSTmin );

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_START_SEC_VAR
#include <Gdn_CanTp_MemMap.h>

static gdn_uint8                Gdn_CanTp_InitStatus;                                   /* CanTp有効化状態      */
#if ( GDN_CANTP_FullDuplexSupport == GDN_OFF )  /* 半2重 */
static Gdn_CanTp_StatusType     Gdn_CanTp_ChannelStatus     [GDN_CANTP_MaxChannelCnt];  /* チャネル状態         */
static gdn_uint8                Gdn_CanTp_NAIidx            [GDN_CANTP_MaxChannelCnt];  /* 送受信中のN_AI       */
static gdn_uint8                Gdn_CanTp_CFSN              [GDN_CANTP_MaxChannelCnt];  /* CF送受信中のSN       */
static Gdn_PduLengthType        Gdn_CanTp_DataSizeRemained  [GDN_CANTP_MaxChannelCnt];  /* 送受信残データ       */
static Gdn_CanTp_BlockSizeType  Gdn_CanTp_FrameCnt          [GDN_CANTP_MaxChannelCnt];  /* 送受信フレーム数     */
static Gdn_CanTp_BlockSizeType  Gdn_CanTp_BlockSize         [GDN_CANTP_MaxChannelCnt];  /* 送信時のBS値         */
static Gdn_CanTp_STminType      Gdn_CanTp_STmin             [GDN_CANTP_MaxChannelCnt];  /* 送信時のSTmin値      */
static Gdn_CanTp_WFTMaxType     Gdn_CanTp_WaitCnt           [GDN_CANTP_MaxChannelCnt];  /* 受信時のFC.WT数      */
static gdn_uint8                Gdn_CanTp_Synchronizer      [GDN_CANTP_MaxChannelCnt]
                                                            [GDN_CANTP_TimerCnt];       /* タイマ同期用カウンタ */
  #if ( GDN_CANTP_CanFDSupport == GDN_ON )
  static Gdn_PduLengthType      Gdn_CanTp_ReceiveSize_FF    [GDN_CANTP_MaxChannelCnt];  /* FF受信時のデータ長   */
  #endif
#else   /* 全2重 */
static Gdn_CanTp_StatusType     Gdn_CanTp_ChannelStatus     [GDN_CANTP_MaxChannelCnt][2];
static gdn_uint8                Gdn_CanTp_NAIidx            [GDN_CANTP_MaxChannelCnt][2];
static gdn_uint8                Gdn_CanTp_CFSN              [GDN_CANTP_MaxChannelCnt][2];
static Gdn_PduLengthType        Gdn_CanTp_DataSizeRemained  [GDN_CANTP_MaxChannelCnt][2];
static Gdn_CanTp_BlockSizeType  Gdn_CanTp_FrameCnt          [GDN_CANTP_MaxChannelCnt][2];
static Gdn_CanTp_BlockSizeType  Gdn_CanTp_BlockSize         [GDN_CANTP_MaxChannelCnt];
static Gdn_CanTp_STminType      Gdn_CanTp_STmin             [GDN_CANTP_MaxChannelCnt];
static Gdn_CanTp_WFTMaxType     Gdn_CanTp_WaitCnt           [GDN_CANTP_MaxChannelCnt][2];
static gdn_uint8                Gdn_CanTp_Synchronizer      [GDN_CANTP_MaxChannelCnt][2]
                                                            [GDN_CANTP_TimerCnt];
  #if ( GDN_CANTP_CanFDSupport == GDN_ON )
  static Gdn_PduLengthType      Gdn_CanTp_ReceiveSize_FF    [GDN_CANTP_MaxChannelCnt][2];
  #endif
#endif

#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
static gdn_bool                 Gdn_CanTp_BSValueChanged    [GDN_CANTP_MaxRxNAICnt];    /* ユーザ設定BSの使用有無    */
static gdn_bool                 Gdn_CanTp_STminValueChanged [GDN_CANTP_MaxRxNAICnt];    /* ユーザ設定STminの使用有無 */
static Gdn_CanTp_BlockSizeType  Gdn_CanTp_UserBSValue       [GDN_CANTP_MaxRxNAICnt];    /* ユーザ設定のBS値          */
static Gdn_CanTp_STminType      Gdn_CanTp_UserSTminValue    [GDN_CANTP_MaxRxNAICnt];    /* ユーザ設定のSTmin値       */
#endif

#define GDN_CANTP_STOP_SEC_VAR
#include <Gdn_CanTp_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_CANTP_START_SEC_CST
#include <Gdn_CanTp_MemMap.h>

static GdnConst Gdn_CanTp_ChannelType Gdn_CanTp_MaxChannel = GDN_CANTP_MaxChannelCnt;
static GdnConst gdn_uint8 Gdn_CanTp_MaxTxNAI = GDN_CANTP_MaxTxNAICnt;

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
static GdnConst Gdn_CanTp_DlcMinSizeTblType Gdn_CanTp_SF_DLMinSizeTbl[GDN_CANTP_SFDLMinTblSize] =
{
     {  (gdn_uint8)GDN_CANTP_CAN_DL_64, (gdn_uint8)GDN_CANTP_SFDLMin_47  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_48, (gdn_uint8)GDN_CANTP_SFDLMin_31  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_32, (gdn_uint8)GDN_CANTP_SFDLMin_23  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_24, (gdn_uint8)GDN_CANTP_SFDLMin_19  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_20, (gdn_uint8)GDN_CANTP_SFDLMin_15  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_16, (gdn_uint8)GDN_CANTP_SFDLMin_11  }
    ,{  (gdn_uint8)GDN_CANTP_CAN_DL_12, (gdn_uint8)GDN_CANTP_SFDLMin_8   }
};

static GdnConst gdn_uint8 Gdn_CanTp_OptimizeSendLengthTbl[GDN_CANTP_OptiTblSize] =
{
     (gdn_uint8)GDN_CANTP_CAN_DL_8  /*  0 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  1 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  2 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  3 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  4 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  5 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  6 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  7 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_8  /*  8 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_12 /*  9 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_12 /* 10 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_12 /* 11 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_12 /* 12 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_16 /* 13 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_16 /* 14 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_16 /* 15 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_16 /* 16 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_20 /* 17 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_20 /* 18 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_20 /* 19 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_20 /* 20 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_24 /* 21 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_24 /* 22 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_24 /* 23 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_24 /* 24 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 25 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 26 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 27 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 28 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 29 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 30 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 31 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_32 /* 32 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 33 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 34 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 35 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 36 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 37 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 38 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 39 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 40 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 41 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 42 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 43 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 44 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 45 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 46 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 47 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_48 /* 48 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 49 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 50 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 51 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 52 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 53 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 54 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 55 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 56 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 57 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 58 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 59 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 60 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 61 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 62 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 63 */
    ,(gdn_uint8)GDN_CANTP_CAN_DL_64 /* 64 */
};
#endif

#define GDN_CANTP_STOP_SEC_CST
#include <Gdn_CanTp_MemMap.h>

/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define GDN_CANTP_START_SEC_CODE
#include <Gdn_CanTp_MemMap.h>

/******************************************************************************/
/* Function Name | Gdn_CanTp_Init                                             */
/* Description   | CanTpの初期化処理                                          */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_Init (void)
{
    Gdn_CanTp_ChannelType   Cnt;
    Gdn_CanTp_ChannelType   CntMax;
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
    gdn_uint8               N_AICnt;
#endif

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        CntMax = Gdn_CanTp_MaxChannel;
        for ( Cnt = (Gdn_CanTp_ChannelType)0; Cnt < CntMax; Cnt++ ) {
            Gdn_CanTp_ChannelStatus   [Cnt] = GDN_CANTP_Idle;
            Gdn_CanTp_NAIidx          [Cnt] = (gdn_uint8)0;
            Gdn_CanTp_CFSN            [Cnt] = (gdn_uint8)0;
            Gdn_CanTp_DataSizeRemained[Cnt] = (Gdn_PduLengthType)0;
            Gdn_CanTp_FrameCnt        [Cnt] = GDN_CANTP_BSMinValue;
            Gdn_CanTp_BlockSize       [Cnt] = GDN_CANTP_BSMinValue;
            Gdn_CanTp_STmin           [Cnt] = GDN_CANTP_STminMinValue;
            Gdn_CanTp_WaitCnt         [Cnt] = (Gdn_CanTp_WFTMaxType)0;

            Gdn_CanTp_Synchronizer[Cnt][GDN_CANTP_MaxTimerIdx] = (gdn_uint8)0;
            Gdn_CanTp_Synchronizer[Cnt][GDN_CANTP_MinTimerIdx] = (gdn_uint8)0;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            Gdn_CanTp_ReceiveSize_FF  [Cnt] = (Gdn_PduLengthType)0;
#endif
        }
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        for ( N_AICnt = (gdn_uint8)0; N_AICnt < (gdn_uint8)GDN_CANTP_MaxRxNAICnt; N_AICnt++ ) {
            Gdn_CanTp_BSValueChanged   [N_AICnt] = GDN_FALSE;
            Gdn_CanTp_STminValueChanged[N_AICnt] = GDN_FALSE;
            Gdn_CanTp_UserBSValue      [N_AICnt] = GDN_CANTP_BSMinValue;
            Gdn_CanTp_UserSTminValue   [N_AICnt] = GDN_CANTP_STminMinValue;
        }
#endif
        Gdn_CanTp_InitStatus = GDN_CANTP_Active;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_Shutdown                                         */
/* Description   | CanTpの終了処理                                            */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_Shutdown (void)
{
    Gdn_CanTp_ChannelType Cnt;
    Gdn_CanTp_ChannelType CntMax;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        Gdn_CanTp_InitStatus = GDN_CANTP_ShutDown;
        CntMax = Gdn_CanTp_MaxChannel;
        for ( Cnt = (Gdn_CanTp_ChannelType)0; Cnt < CntMax; Cnt++ ) {
            Gdn_CanTp_ChannelStatus[Cnt] = GDN_CANTP_Idle;
            /* AUTOSAR: 上位層ERROR通知しない */
        }
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_MainFunction                                     */
/* Description   | CanTpの送受信リトライ処理                                  */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_MainFunction (void)
{
    Gdn_CanTp_ChannelType Cnt;
    Gdn_CanTp_ChannelType CntMax;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else if ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) {
        CntMax = Gdn_CanTp_MaxChannel;
        for ( Cnt = (Gdn_CanTp_ChannelType)0; Cnt < CntMax; Cnt++ ) {
            switch ( Gdn_CanTp_ChannelStatus[Cnt] ) {
                case GDN_CANTP_RxBusy:
                    Gdn_CanTp_RxDataRetry( Cnt );   /* 受信リトライ処理 */
                    break;

                case GDN_CANTP_TxGetDelay:
                case GDN_CANTP_TxGetNoDelay:
                    Gdn_CanTp_TxDataRetry( Cnt );   /* 送信リトライ処理 */
                    break;

                default:    /* 他の状態の場合、処理せずに終了 */
                    break;
            }
        }
    } else {
        /* No process */
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_RxIndication                                     */
/* Description   | 受信通知（L_Data.indication）                              */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_RxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) RxPduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANTP_APPL_CONST) PduInfoPtr
)
{
    Gdn_PduLengthType DLC;
    gdn_uint8*        RxFrame;
    gdn_uint8         N_AI;
    gdn_uint8         N_PCIType;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else {
        DLC = PduInfoPtr->SduLength;    /* ポインタの有効性判定は実施しない */

        if ( ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) &&          /* CanTp初期化完了 */
            ( RxPduId < (Gdn_PduIdType)GDN_CANTP_MaxRxPduIdCnt ) &&    /* RxPduIdが有効   */
            ( DLC >= GDN_CANTP_DLCMinSize_N ) &&                       /* DLC ≧ 2バイト  */
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            ( DLC <= GDN_CANTP_FD_DLCMaxSize ) ) {                     /* DLC ≦ 64バイト */
#else
            ( DLC <= GDN_CANTP_DLCMaxSize ) ) {                        /* DLC ≦ 8バイト  */
#endif

            RxFrame   = PduInfoPtr->SduDataPtr;
            N_PCIType = GDN_CANTP_HiNibbleMask; /* 初期値 */
            N_AI      = Gdn_CanTp_SearchNAI( RxPduId, RxFrame, &N_PCIType );

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            if ( ( N_AI < (gdn_uint8)GDN_CANTP_MaxRxNAICnt ) &&     /* 受信N_AIが有効 */
                ( ( ( gdn_cantp_RxNAIInformation[N_AI].IsPadding == GDN_FALSE ) && ( DLC < GDN_CANTP_CAN_DL_8 ) ) ||
                ( DLC == GDN_CANTP_CAN_DL_8 ) ||
                ( DLC == GDN_CANTP_CAN_DL_12 ) ||
                ( DLC == GDN_CANTP_CAN_DL_16 ) ||
                ( DLC == GDN_CANTP_CAN_DL_20 ) ||
                ( DLC == GDN_CANTP_CAN_DL_24 ) ||
                ( DLC == GDN_CANTP_CAN_DL_32 ) ||
                ( DLC == GDN_CANTP_CAN_DL_48 ) ||
                ( DLC == GDN_CANTP_CAN_DL_64 ) ) ) {     /* パディングチェック */
#else
            if ( ( N_AI < (gdn_uint8)GDN_CANTP_MaxRxNAICnt ) &&     /* 受信N_AIが有効 */
                ( ( gdn_cantp_RxNAIInformation[N_AI].IsPadding == GDN_FALSE ) ||
                ( DLC == GDN_CANTP_DLCMaxSize ) ) ) {    /* パディングチェック */
#endif

                /* 半2重受信処理 */
                switch ( N_PCIType ) {
                    case GDN_CANTP_SF:
                        Gdn_CanTp_JudgeSF( N_AI, DLC, RxFrame );
                        break;

                    case GDN_CANTP_FF:
                        Gdn_CanTp_JudgeFF( N_AI, DLC, RxFrame );
                        break;

                    case GDN_CANTP_CF:
                        Gdn_CanTp_JudgeCF( N_AI, DLC, RxFrame );
                        break;

                    case GDN_CANTP_FC:
                        Gdn_CanTp_JudgeFC( N_AI, DLC, RxFrame );
                        break;

                    default:
                        /* 受信N_PCITypeが0～3ではない場合、受信通知を無視する */
                        break;
                }
            }
            /* else 受信フレームを無視する */
        }
        /* else 受信フレームを無視する */
    }
}

#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
/******************************************************************************/
/* Function Name | Gdn_CanTp_Transmit                                         */
/* Description   | 送信要求（N_USData.request）                               */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_Transmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpTxSduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr
)
{
    Gdn_Std_ReturnType                t_Result;
    Gdn_PduLengthType                 MessageSize;
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_CanTp_StatusType              ChannelStatus;
    Gdn_PduLengthType                 SF_DL_Max;

    t_Result      = GDN_E_NOT_OK;
    MessageSize = CanTpTxInfoPtr->SduLength;    /* ポインタの有効性判定は実施しない */

    if ( ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) &&              /* CanTp初期化完了 */
         ( CanTpTxSduId < (Gdn_PduIdType)GDN_CANTP_MaxTxSduIdCnt ) &&   /* TxSduIdが有効   */
         ( MessageSize > (Gdn_PduLengthType)0 ) &&                      /* 送信メッセージ  */
         ( MessageSize <= GDN_CANTP_MaxTxLength ) ) {                   /* サイズが有効    */

        N_AIInfo  = &gdn_cantp_TxNAIInformation[CanTpTxSduId];

        /* 半2重送信処理 */
        ChannelStatus = Gdn_CanTp_ChannelStatus[N_AIInfo->Channel];
        if ( ( ChannelStatus == GDN_CANTP_Idle ) ||
             ( ( ChannelStatus != GDN_CANTP_RxSendCTS    ) &&   /* RAM化け対策 */
               ( ChannelStatus != GDN_CANTP_RxSendOVFL   ) &&
               ( ChannelStatus != GDN_CANTP_RxSendWT     ) &&
               ( ChannelStatus != GDN_CANTP_RxDelayCTS   ) &&
               ( ChannelStatus != GDN_CANTP_RxDelayOVFL  ) &&
               ( ChannelStatus != GDN_CANTP_RxBusy       ) &&
               ( ChannelStatus != GDN_CANTP_RxWaitCF     ) &&
               ( ChannelStatus != GDN_CANTP_TxSendFF     ) &&
               ( ChannelStatus != GDN_CANTP_TxSendSF     ) &&
               ( ChannelStatus != GDN_CANTP_TxSendCF     ) &&
               ( ChannelStatus != GDN_CANTP_TxWaitFC1    ) &&
               ( ChannelStatus != GDN_CANTP_TxWaitFCx    ) &&
               ( ChannelStatus != GDN_CANTP_TxDelayCF    ) &&
               ( ChannelStatus != GDN_CANTP_TxGetDelay   ) &&
               ( ChannelStatus != GDN_CANTP_TxGetNoDelay ) ) ) {
            /* AUTOSARでは、受け付けと送信処理は非同期で実施するが              */
            /* GUARDIANは同期で実施するため、受信処理中に送信される可能性がある */
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            if ( ( N_AIInfo->SendSize >= GDN_CANTP_CAN_DL_8 ) &&
                 ( N_AIInfo->SendSize <= GDN_CANTP_CAN_DL_64 ) ) {

                /* SFのフォーマットによってSF_DLの最大サイズが変わるため、送信サイズで処理を分ける */
                if ( N_AIInfo->SendSize == GDN_CANTP_CAN_DL_8 ) {
                    SF_DL_Max = GDN_CANTP_SFDLMaxSize_N;
                    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                        SF_DL_Max = GDN_CANTP_SFDLMaxSize_E;
                    }
                } else {
                    SF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_SFDLMaxSize_N( N_AIInfo->SendSize );
                    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                        SF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_SFDLMaxSize_E( N_AIInfo->SendSize );
                    }
                }

                if ( MessageSize > SF_DL_Max ) {    /* FF送信 */
                    t_Result = Gdn_CanTp_SendFF( CanTpTxSduId, MessageSize );
                } else {                            /* SF送信 */
                    t_Result = Gdn_CanTp_SendSF( CanTpTxSduId, MessageSize );
                }
            }
#else
            SF_DL_Max = GDN_CANTP_SFDLMaxSize_N;
            if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                SF_DL_Max = GDN_CANTP_SFDLMaxSize_E;
            }

            if ( MessageSize > SF_DL_Max ) {    /* FF送信 */
                t_Result = Gdn_CanTp_SendFF( CanTpTxSduId, MessageSize );

            } else {    /* SF送信 */
                t_Result = Gdn_CanTp_SendSF( CanTpTxSduId, MessageSize );
            }
#endif
        }
        /* else 送信要求を実施しない */
    }
    /* else 送信要求を実施しない */

    return t_Result;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_CanTp_TxConfirmation                                   */
/* Description   | 送信完了通知（L_Data.confirmation）                        */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_TxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) TxPduId
)
{
    Gdn_CanTp_ChannelType   TxChannel;
    Gdn_CanTp_ChannelType   MaxChannelCnt;
    Gdn_TimeoutValueType    N_Cr;
    Gdn_TimeoutValueType    N_Bs;

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else if ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) { /* CanTp初期化完了 */

        TxChannel = Gdn_CanTp_SearchTxChannel( TxPduId );
        MaxChannelCnt = Gdn_CanTp_MaxChannel;

        if ( TxChannel < MaxChannelCnt ) {

            Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MaxTimerIdx ); /* N_A停止 */

            switch ( Gdn_CanTp_ChannelStatus[TxChannel] ) {
                case GDN_CANTP_RxSendCTS:
                    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_RxWaitCF;
                    N_Cr = gdn_cantp_RxNAIInformation[ Gdn_CanTp_NAIidx[TxChannel] ].N_Cr;
                    Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_Cr );
                    break;

                case GDN_CANTP_RxSendOVFL:
                    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
                    break;

                case GDN_CANTP_RxSendWT:
                    Gdn_CanTp_FCWTConfirmation( TxChannel );
                    break;

                case GDN_CANTP_TxSendFF:
                    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxWaitFC1;
                    N_Bs = gdn_cantp_TxNAIInformation[ Gdn_CanTp_NAIidx[TxChannel] ].N_Bs;
                    Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_Bs );
                    break;

                case GDN_CANTP_TxSendSF:
                    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
                    Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)Gdn_CanTp_NAIidx[TxChannel], GDN_NTFRSLT_OK );
                    break;

                case GDN_CANTP_TxSendCF:
                    Gdn_CanTp_CFConfirmation( TxChannel );
                    break;

                default:
                    /* SearchTxChannelで状態のガードがあるため、到達できない */
                    break;
            }
        }
        /* else 送信完了通知を無視する */
    } else {
        /* No process */
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_TimeoutIndication                                */
/* Description   | タイムアウト通知                                           */
/******************************************************************************/
FUNC(void, CANTP_CODE_SLOW) Gdn_CanTp_TimeoutIndication
(
    VAR(Gdn_TimerIdType, AUTOMATIC) TimerId,
    VAR(gdn_uint16, AUTOMATIC) Synchronizer
)
{
    Gdn_CanTp_ChannelType     SynchronizedChannel;
    GdnConst Gdn_TimerIdType  (*TimerIdInfo)[GDN_CANTP_TimerCnt];
    gdn_uint8                 LocalSynchronizer;
    gdn_uint8                 (*ExpectedSynchronizer)[GDN_CANTP_TimerCnt];

    if( ReprogOpt_CanDisableConfig == (uint8)STD_ON ) {
        /* No process */
    } else if ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) { /* CanTp初期化完了 */

        SynchronizedChannel  = (Gdn_CanTp_ChannelType)( Synchronizer >> GDN_CANTP_Shift1Byte );
        LocalSynchronizer    = (gdn_uint8)Synchronizer;
        TimerIdInfo          = &gdn_cantp_TimerId[SynchronizedChannel];
        ExpectedSynchronizer = &Gdn_CanTp_Synchronizer[SynchronizedChannel];

        if ( ( TimerId == (*TimerIdInfo)[GDN_CANTP_MinTimerIdx] ) &&
             ( LocalSynchronizer == (*ExpectedSynchronizer)[GDN_CANTP_MinTimerIdx] ) ) {

            Gdn_CanTp_MinTimerTimeout( SynchronizedChannel );

        } else if ( ( TimerId == (*TimerIdInfo)[GDN_CANTP_MaxTimerIdx] ) &&
                    ( LocalSynchronizer == (*ExpectedSynchronizer)[GDN_CANTP_MaxTimerIdx] ) ) {

            Gdn_CanTp_MaxTimerTimeout( SynchronizedChannel );

        } else {
            /* タイマIDが異なる場合は、通知を無視する */
            /* タイマ入れ違いの発生時は通知を無視する */
        }
    } else {
        /* No process */
    }
}

#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
  #if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
/******************************************************************************/
/* Function Name | Gdn_CanTp_ChangeParameter                                  */
/* Description   | 受信パラメータ変更要求（N_ChangeParameter.request）        */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_ChangeParameter
(
    VAR(Gdn_PduIdType, AUTOMATIC) id,
    VAR(Gdn_TPParameterType, AUTOMATIC) parameter,
    VAR(gdn_uint16, AUTOMATIC) value
)
{
    Gdn_Std_ReturnType                t_Result;
    gdn_uint8                         RxN_AI;
    GdnConst Gdn_CanTp_RxNAIInfoType* RxN_AIInfo;
    Gdn_CanTp_StatusType              ChannelStatus;

    t_Result = GDN_E_NOT_OK;

    /* Init時にすべて設定が初期化されるため、ShutDown状態を判定しない */
    for ( RxN_AI = (gdn_uint8)0; RxN_AI < (gdn_uint8)GDN_CANTP_MaxRxNAICnt; RxN_AI++ ) {

        RxN_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];

        if ( RxN_AIInfo->SduId == id ) {    /* SduId一致 */

            ChannelStatus = Gdn_CanTp_ChannelStatus[RxN_AIInfo->Channel];

            if ( ( ( ChannelStatus != GDN_CANTP_RxSendCTS   ) &&
                   ( ChannelStatus != GDN_CANTP_RxSendOVFL  ) &&
                   ( ChannelStatus != GDN_CANTP_RxSendWT    ) &&
                   ( ChannelStatus != GDN_CANTP_RxDelayCTS  ) &&
                   ( ChannelStatus != GDN_CANTP_RxDelayOVFL ) &&
                   ( ChannelStatus != GDN_CANTP_RxBusy      ) &&
                   ( ChannelStatus != GDN_CANTP_RxWaitCF    ) ) ||
                 ( Gdn_CanTp_NAIidx[RxN_AIInfo->Channel] != RxN_AI ) ) {
                /* SduIdが受信中ではない */
                if ( ( parameter == GDN_TP_BS ) &&
                     ( value <= (gdn_uint16)GDN_CANTP_BSMaxValue ) ) {
                    /* BS設定 */
                    Gdn_CanTp_BSValueChanged[RxN_AI] = GDN_TRUE;
                    Gdn_CanTp_UserBSValue[RxN_AI]    = (Gdn_CanTp_BlockSizeType)value;
                    t_Result = GDN_E_OK;

                } else if ( ( parameter == GDN_TP_STMIN ) &&
                            ( value <= (gdn_uint16)GDN_CANTP_STminMaxValue ) ) {
                    /* STmin設定 */
                    Gdn_CanTp_STminValueChanged[RxN_AI] = GDN_TRUE;
                    Gdn_CanTp_UserSTminValue[RxN_AI]    = (Gdn_CanTp_STminType)value;
                    t_Result = GDN_E_OK;

                } else if ( ( parameter == GDN_TP_BS ) ||
                            ( parameter == GDN_TP_STMIN ) ) {   /* サポートしない値 */
                    t_Result = GDN_E_CANTP_WRONG_VALUE;

                } else {    /* サポートしないパラメータ */
                    t_Result = GDN_E_CANTP_WRONG_PARAMETER;
                }

            } else {    /* SduIdが受信中の場合は、要求を実施しない */
                t_Result = GDN_E_CANTP_RX_ON;
            }
            break;
        }
        /* else 次のSduIdを判定 */
    }

    return t_Result;
}
  #endif  /* GDN_CANTP_ChangeParameterApi == GDN_ON */

/******************************************************************************/
/* Function Name | Gdn_CanTp_CancelTransmit                                   */
/* Description   | 送信中止要求                                               */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_CancelTransmit
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpTxSduId
)
{
    Gdn_Std_ReturnType                t_Result;
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             TxChannel;
    Gdn_CanTp_StatusType              ChannelStatus;
    Gdn_PduIdType                     PduId;

    t_Result = GDN_E_NOT_OK;

    if ( ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) &&              /* CanTp初期化完了 */
         ( CanTpTxSduId < (Gdn_PduIdType)GDN_CANTP_MaxTxSduIdCnt ) ) {  /* TxSduIdが有効   */

        N_AIInfo  = &gdn_cantp_TxNAIInformation[CanTpTxSduId];
        TxChannel = N_AIInfo->Channel;
        ChannelStatus = Gdn_CanTp_ChannelStatus[TxChannel];

        if ( ( ChannelStatus == GDN_CANTP_TxSendFF     ) ||
             ( ChannelStatus == GDN_CANTP_TxSendSF     ) ||
             ( ChannelStatus == GDN_CANTP_TxSendCF     ) ||
             ( ChannelStatus == GDN_CANTP_TxWaitFC1    ) ||
             ( ChannelStatus == GDN_CANTP_TxWaitFCx    ) ||
             ( ChannelStatus == GDN_CANTP_TxDelayCF    ) ||
             ( ChannelStatus == GDN_CANTP_TxGetDelay   ) ||
             ( ChannelStatus == GDN_CANTP_TxGetNoDelay ) ) {    /* 送信状態 */
            /* フレーム送信のキャンセル処理 */
            if ( ( ChannelStatus == GDN_CANTP_TxSendFF ) ||
                 ( ChannelStatus == GDN_CANTP_TxSendSF ) ||
                 ( ChannelStatus == GDN_CANTP_TxSendCF ) ) {    /* フレーム送信中 */
                PduId = N_AIInfo->PduId;
                (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
            }
            /* メッセージ送信のキャンセル処理 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
            Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MaxTimerIdx );
            Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MinTimerIdx );
            Gdn_PduR_CanTpTxConfirmation( CanTpTxSduId, GDN_NTFRSLT_E_NOT_OK );
            t_Result = GDN_E_OK;
        }
        /* else 要求を無視する */
    }
    /* else 要求を無視する */

    return t_Result;
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_CancelReceive                                    */
/* Description   | 受信中止要求                                               */
/******************************************************************************/
FUNC(Gdn_Std_ReturnType, CANTP_CODE_SLOW) Gdn_CanTp_CancelReceive
(
    VAR(Gdn_PduIdType, AUTOMATIC) CanTpRxSduId
)
{
    Gdn_Std_ReturnType                t_Result;
    gdn_uint8                         RxN_AI;
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_CanTp_StatusType              ChannelStatus;
    gdn_uint8                         TxN_AI;
    Gdn_PduIdType                     PduId;

    t_Result = GDN_E_NOT_OK;

    if ( Gdn_CanTp_InitStatus != GDN_CANTP_ShutDown ) {    /* CanTp初期化完了 */

        for ( RxN_AI = (gdn_uint8)0; RxN_AI < (gdn_uint8)GDN_CANTP_MaxRxNAICnt; RxN_AI++ ) {

            N_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];

            if ( N_AIInfo->SduId == CanTpRxSduId ) {    /* SduId一致 */

                RxChannel     = N_AIInfo->Channel;
                ChannelStatus = Gdn_CanTp_ChannelStatus[RxChannel];

                if ( ( ChannelStatus == GDN_CANTP_RxSendCTS   ) ||
                     ( ChannelStatus == GDN_CANTP_RxSendOVFL  ) ||
                     ( ChannelStatus == GDN_CANTP_RxSendWT    ) ||
                     ( ChannelStatus == GDN_CANTP_RxDelayCTS  ) ||
                     ( ChannelStatus == GDN_CANTP_RxDelayOVFL ) ||
                     ( ChannelStatus == GDN_CANTP_RxBusy      ) ||
                     ( ChannelStatus == GDN_CANTP_RxWaitCF    ) ) { /* 受信状態 */
                    /* フレーム送信のキャンセル処理 */
                    if ( ( ChannelStatus == GDN_CANTP_RxSendCTS  ) ||
                         ( ChannelStatus == GDN_CANTP_RxSendOVFL ) ||
                         ( ChannelStatus == GDN_CANTP_RxSendWT   ) ) {  /* フレーム送信中 */
                        TxN_AI = gdn_cantp_RxNAIInformation[RxN_AI].TxN_AIidx;
                        PduId = gdn_cantp_TxNAIInformation[TxN_AI].PduId;
                        (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
                    }
                    /* 受信キャンセル処理 */
                    Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
                    Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx );
                    Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MinTimerIdx );
                    Gdn_PduR_CanTpRxIndication( CanTpRxSduId, GDN_NTFRSLT_E_NOT_OK );
                    t_Result = GDN_E_OK;
                }
                /* else 要求を無視する */
                break;
            }
        }
    }
    /* else 要求を無視する */

    return t_Result;
}
#endif  /* REPROG_CFG_SUBMICON_USE_SUB != STD_ON */

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Gdn_CanTp_SearchNAI                                        */
/* Description   | 受信フレームのN_AIとN_PCIを取得する                        */
/* Re-entrancy   | Reentrant                                                  */
/* Parameters    | (in)  RxPduId   : 受信PDUID                                */
/*               | (in)  RxFrame   : 受信フレームのバッファ                   */
/*               | (out) N_PCIType : 受信フレームのN_PCIType                  */
/* Return Value  | 受信N_AIのインデックス                                     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static gdn_uint8 Gdn_CanTp_SearchNAI(       Gdn_PduIdType RxPduId,
                                      const gdn_uint8     RxFrame[],
                                            gdn_uint8*    N_PCIType )
{
    gdn_uint8     N_AI;
    Gdn_PduIdType PduIdTbl;
    gdn_bool      IsBreak;

    N_AI    = (gdn_uint8)RxPduId;   /* 受信PduIdの値を検索開始位置とする */
    IsBreak = GDN_FALSE;

    while ( ( N_AI < (gdn_uint8)GDN_CANTP_MaxRxNAICnt ) &&
            ( IsBreak == GDN_FALSE ) ) {

        PduIdTbl = gdn_cantp_RxNAIInformation[N_AI].PduId;

        if ( RxPduId == PduIdTbl ) {    /* 受信PDUIDが一致 */
            if ( gdn_cantp_RxNAIInformation[N_AI].AddressFormat == GDN_CANTP_Normal ) {
                /* 通常アドレスフォーマット */
                *N_PCIType = RxFrame[GDN_CANTP_NPCIOffSet_N] & GDN_CANTP_HiNibbleMask;
                IsBreak = GDN_TRUE;

            } else if ( (Gdn_CanTp_TargetAddressType)RxFrame[0] == gdn_cantp_RxNAIInformation[N_AI].TargetAddress ) {
                /* 拡張アドレスフォーマットでN_TAが一致 */
                *N_PCIType = RxFrame[GDN_CANTP_NPCIOffSet_E] & GDN_CANTP_HiNibbleMask;
                IsBreak = GDN_TRUE;

            } else {
                N_AI++;
            }

        } else if ( RxPduId < PduIdTbl ) {              /* 受信N_AIは非サポートの場合 */
            N_AI = (gdn_uint8)GDN_CANTP_MaxRxNAICnt;    /* N_AIを無効値にする         */

        } else {    /* RxPduId > PduIdTbl */
            N_AI++; /* no wrap around */
        }
    }

    return N_AI;
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SearchTxChannel                                  */
/* Description   | 送信完了通知の通知先チャネルを検索する                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxPduId : 送信PDUID                                   */
/* Return Value  | 送信完了通知を期待するチャネル                             */
/* Notes         | 同じ送信PduIdを使用する異なる送信N_AIは、必ず同じチャネル  */
/*               | で送信すること。                                           */
/******************************************************************************/
static Gdn_CanTp_ChannelType Gdn_CanTp_SearchTxChannel( Gdn_PduIdType TxPduId )
{
    Gdn_CanTp_ChannelType             TxChannel;
    gdn_uint8                         SearchN_AI;
    GdnConst Gdn_CanTp_TxNAIInfoType* SearchN_AIInfo;
    Gdn_CanTp_StatusType              ChannelStatus;
    gdn_uint8                         RxN_AI;
    gdn_uint8                         TxN_AI;
    gdn_uint8                         CntMax;
    Gdn_PduIdType                     ExpectedTxPduId;

    TxChannel = Gdn_CanTp_MaxChannel;    /* TxChannelを無効値にする */
    CntMax = Gdn_CanTp_MaxTxNAI;

    for ( SearchN_AI = (gdn_uint8)0; SearchN_AI < CntMax; SearchN_AI++ ) {

        SearchN_AIInfo = &gdn_cantp_TxNAIInformation[SearchN_AI];

        if ( SearchN_AIInfo->PduId == TxPduId ) {

            TxChannel = SearchN_AIInfo->Channel;
            ChannelStatus = Gdn_CanTp_ChannelStatus[TxChannel];

            if ( ( ChannelStatus == GDN_CANTP_RxSendCTS  ) ||
                 ( ChannelStatus == GDN_CANTP_RxSendOVFL ) ||
                 ( ChannelStatus == GDN_CANTP_RxSendWT   ) ) {

                RxN_AI = Gdn_CanTp_NAIidx[TxChannel];
                TxN_AI = gdn_cantp_RxNAIInformation[RxN_AI].TxN_AIidx;
                ExpectedTxPduId = gdn_cantp_TxNAIInformation[TxN_AI].PduId;

                if ( TxPduId != ExpectedTxPduId ) { /* FC送信用TxPduIdと不一致 */
                    TxChannel = Gdn_CanTp_MaxChannel;
                }

            } else if ( ( ChannelStatus == GDN_CANTP_TxSendSF ) ||
                        ( ChannelStatus == GDN_CANTP_TxSendFF ) ||
                        ( ChannelStatus == GDN_CANTP_TxSendCF ) ) {

                TxN_AI = Gdn_CanTp_NAIidx[TxChannel];
                ExpectedTxPduId = gdn_cantp_TxNAIInformation[TxN_AI].PduId;

                if ( TxPduId != ExpectedTxPduId ) { /* 送信用TxPduIdと不一致 */
                    TxChannel = Gdn_CanTp_MaxChannel;
                }

            } else {    /* 送信中ではない場合、送信完了通知を無視する */
                TxChannel = Gdn_CanTp_MaxChannel;
            }

            break;
        }
        /* PduId不一致で、次のN_AIを検索 */
    }

    return TxChannel;
}


/******************************************************************************/
/* Function Name | Gdn_CanTp_JudgeSF                                          */
/* Description   | SF受信時の条件判定と調停処理                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI    : 受信N_AI                                    */
/*               | (in) DLC     : 受信フレームサイズ                          */
/*               | (in) RxFrame : 受信フレームのバッファ                      */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_JudgeSF( gdn_uint8         N_AI,
                               Gdn_PduLengthType DLC,
                               gdn_uint8         RxFrame[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_PduLengthType                 OffSet;
    Gdn_PduLengthType                 SF_DL_Max;
    Gdn_PduLengthType                 SFGapSize;    /* SF_DLとDLCの差分 */
    Gdn_PduLengthType                 SF_DL;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_CanTp_StatusType              DetailStatus;
    gdn_bool                          ReceiveRx;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    Gdn_PduLengthType                 SF_DL_Min;
    Gdn_PduLengthType                 AddressOffSet;
    gdn_bool                          IsReceiveSF;
    gdn_uint8                         Cnt;
#endif

    N_AIInfo = &gdn_cantp_RxNAIInformation[N_AI];

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    IsReceiveSF = GDN_FALSE;
    OffSet      = GDN_CANTP_NPCIOffSet_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

    if ( DLC <= GDN_CANTP_CAN_DL_8 ) {

        SF_DL_Max = GDN_CANTP_SFDLMaxSize_N;
        SFGapSize = GDN_CANTP_NPCIOffSet_N + GDN_CANTP_NPCISizeSF;
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            SF_DL_Max = GDN_CANTP_SFDLMaxSize_E;
            SFGapSize = GDN_CANTP_NPCIOffSet_E + GDN_CANTP_NPCISizeSF;
        }

        SF_DL = (Gdn_PduLengthType)RxFrame[OffSet] & (Gdn_PduLengthType)GDN_CANTP_LoNibbleMask;

        if ( ( SF_DL > (Gdn_PduLengthType)0 ) &&
             ( SF_DL <= SF_DL_Max ) &&
             ( DLC >= ( SF_DL + SFGapSize ) ) ) {

            IsReceiveSF = GDN_TRUE;
        }
    } else {

        AddressOffSet = OffSet;
        SFGapSize = OffSet + GDN_CANTP_FD_NPCISizeSF;

        /* N_PCI 0byte目が0x00か確認 */
        if ( RxFrame[OffSet] == GDN_CANTP_FD_SFFisrtByte ) {

            /* N_PCI 1byte目からSF_DL取得 */
            OffSet += GDN_CANTP_FD_SFDLIndex;   /* no wrap around */
            SF_DL = (Gdn_PduLengthType)RxFrame[OffSet];

            /* DLCからSF_DLの最小値、最大値を取得して範囲チェックする */
            SF_DL_Min = GDN_CANTP_SFDLInvalid;
            for ( Cnt = (gdn_uint8)0; Cnt < GDN_CANTP_SFDLMinTblSize; Cnt++ ) {
                if ( DLC == (Gdn_PduLengthType)Gdn_CanTp_SF_DLMinSizeTbl[Cnt].DlcSize ) {
                    SF_DL_Min = (Gdn_PduLengthType)Gdn_CanTp_SF_DLMinSizeTbl[Cnt].MinSize - AddressOffSet;
                    break;
                }
            }
            SF_DL_Max = DLC - SFGapSize;

            if ( ( SF_DL >= SF_DL_Min ) &&
                 ( SF_DL <= SF_DL_Max ) ) {

                IsReceiveSF = GDN_TRUE;
            }
        }
    }

    if ( IsReceiveSF == GDN_TRUE ) {
#else
    OffSet    = GDN_CANTP_NPCIOffSet_N;
    SF_DL_Max = GDN_CANTP_SFDLMaxSize_N;
    SFGapSize = GDN_CANTP_NPCIOffSet_N + GDN_CANTP_NPCISizeSF;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        OffSet    = GDN_CANTP_NPCIOffSet_E;
        SF_DL_Max = GDN_CANTP_SFDLMaxSize_E;
        SFGapSize = GDN_CANTP_NPCIOffSet_E + GDN_CANTP_NPCISizeSF;
    }

    SF_DL = (Gdn_PduLengthType)RxFrame[OffSet] & (Gdn_PduLengthType)GDN_CANTP_LoNibbleMask;

    if ( ( SF_DL > (Gdn_PduLengthType)0 ) &&
         ( SF_DL <= SF_DL_Max ) &&
         ( DLC >= ( SF_DL + SFGapSize ) ) ) {
#endif

        RxChannel    = N_AIInfo->Channel;
        DetailStatus = Gdn_CanTp_ChannelStatus[RxChannel];
        ReceiveRx    = GDN_TRUE;

        if ( ( DetailStatus == GDN_CANTP_RxSendCTS   ) ||
             ( DetailStatus == GDN_CANTP_RxSendOVFL  ) ||
             ( DetailStatus == GDN_CANTP_RxSendWT    ) ||
             ( DetailStatus == GDN_CANTP_RxDelayCTS  ) ||
             ( DetailStatus == GDN_CANTP_RxDelayOVFL ) ||
             ( DetailStatus == GDN_CANTP_RxBusy      ) ||
             ( DetailStatus == GDN_CANTP_RxWaitCF    ) ) {
            /* 受信状態の調停 */
            ReceiveRx = Gdn_CanTp_RxMediation( RxChannel, N_AI );

        } else if ( ( DetailStatus == GDN_CANTP_TxSendFF     ) ||
                    ( DetailStatus == GDN_CANTP_TxSendSF     ) ||
                    ( DetailStatus == GDN_CANTP_TxSendCF     ) ||
                    ( DetailStatus == GDN_CANTP_TxWaitFC1    ) ||
                    ( DetailStatus == GDN_CANTP_TxWaitFCx    ) ||
                    ( DetailStatus == GDN_CANTP_TxDelayCF    ) ||
                    ( DetailStatus == GDN_CANTP_TxGetDelay   ) ||
                    ( DetailStatus == GDN_CANTP_TxGetNoDelay ) ) {
            /* 送信状態の調停 */
            ReceiveRx = Gdn_CanTp_TxMediation( RxChannel, N_AI );

        } else {    /* GDN_CANTP_Idle */
        }

        if ( ReceiveRx == GDN_TRUE ) {
            OffSet++;   /* no wrap around */
            Gdn_CanTp_ReceiveSF( N_AI, SF_DL, &RxFrame[OffSet] );
        }
    }
    /* else 受信フレームを無視する */
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_JudgeFF                                          */
/* Description   | FF受信時の条件判定と調停処理                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI    : 受信N_AI                                    */
/*               | (in) DLC     : 受信フレームサイズ                          */
/*               | (in) RxFrame : 受信フレームのバッファ                      */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_JudgeFF( gdn_uint8         N_AI,
                               Gdn_PduLengthType DLC,
                               gdn_uint8         RxFrame[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_PduLengthType                 OffSet;
    Gdn_PduLengthType                 FF_DL_Min;
    Gdn_PduLengthType                 FF_DL;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_CanTp_StatusType              DetailStatus;
    gdn_bool                          ReceiveRx;

    N_AIInfo = &gdn_cantp_RxNAIInformation[N_AI];

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    OffSet = GDN_CANTP_NPCIOffSet_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

    if ( DLC <= GDN_CANTP_CAN_DL_8 ) {
        FF_DL_Min = GDN_CANTP_FFDLMinSize_N;
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            FF_DL_Min = GDN_CANTP_FFDLMinSize_E;
        }
    } else {
        FF_DL_Min = GDN_CANTP_FD_FFDLMinSize_N( DLC );
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            FF_DL_Min = GDN_CANTP_FD_FFDLMinSize_E( DLC );
        }
    }
#else
    OffSet    = GDN_CANTP_NPCIOffSet_N;
    FF_DL_Min = GDN_CANTP_FFDLMinSize_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        OffSet    = GDN_CANTP_NPCIOffSet_E;
        FF_DL_Min = GDN_CANTP_FFDLMinSize_E;
    }
#endif

    FF_DL = (Gdn_PduLengthType)RxFrame[OffSet] & (Gdn_PduLengthType)GDN_CANTP_LoNibbleMask;
    OffSet++;   /* no wrap around */
    FF_DL <<= GDN_CANTP_Shift1Byte;
    FF_DL += (Gdn_PduLengthType)RxFrame[OffSet];    /* no wrap around */

    if ( ( N_AIInfo->N_TaType == GDN_CANTP_Physical ) &&
         ( FF_DL >= FF_DL_Min ) &&
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
         /* ～7,8,12,16,20,24,32,48,64byteのいずれかであることは確認済み */
         /* 7byte以下を無視するため最小範囲をチェックする */
         ( DLC >= GDN_CANTP_CAN_DL_8 ) ) {
#else
         ( DLC == GDN_CANTP_DLCMaxSize ) ) {
#endif

        RxChannel    = N_AIInfo->Channel;
        DetailStatus = Gdn_CanTp_ChannelStatus[RxChannel];
        ReceiveRx    = GDN_TRUE;

        if ( ( DetailStatus == GDN_CANTP_RxSendCTS   ) ||
             ( DetailStatus == GDN_CANTP_RxSendOVFL  ) ||
             ( DetailStatus == GDN_CANTP_RxSendWT    ) ||
             ( DetailStatus == GDN_CANTP_RxDelayCTS  ) ||
             ( DetailStatus == GDN_CANTP_RxDelayOVFL ) ||
             ( DetailStatus == GDN_CANTP_RxBusy      ) ||
             ( DetailStatus == GDN_CANTP_RxWaitCF    ) ) {
            /* 受信状態の調停 */
            ReceiveRx = Gdn_CanTp_RxMediation( RxChannel, N_AI );

        } else if ( ( DetailStatus == GDN_CANTP_TxSendFF     ) ||
                    ( DetailStatus == GDN_CANTP_TxSendSF     ) ||
                    ( DetailStatus == GDN_CANTP_TxSendCF     ) ||
                    ( DetailStatus == GDN_CANTP_TxWaitFC1    ) ||
                    ( DetailStatus == GDN_CANTP_TxWaitFCx    ) ||
                    ( DetailStatus == GDN_CANTP_TxDelayCF    ) ||
                    ( DetailStatus == GDN_CANTP_TxGetDelay   ) ||
                    ( DetailStatus == GDN_CANTP_TxGetNoDelay ) ) {
            /* 送信状態の調停 */
            ReceiveRx = Gdn_CanTp_TxMediation( RxChannel, N_AI );

        } else {    /* GDN_CANTP_Idle */
        }

        if ( ReceiveRx == GDN_TRUE ) {
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            /* FFで受信したDLCを保持する */
            Gdn_CanTp_ReceiveSize_FF[RxChannel] = DLC;
#endif
            OffSet++;   /* no wrap around */
            Gdn_CanTp_ReceiveFF( N_AI, FF_DL, &RxFrame[OffSet] );
        }
    }
    /* else 受信フレームを無視する */
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_JudgeCF                                          */
/* Description   | CF受信時の条件判定と調停処理                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI    : 受信N_AI                                    */
/*               | (in) DLC     : 受信フレームサイズ                          */
/*               | (in) RxFrame : 受信フレームのバッファ                      */
/* Return Value  | なし                                                       */
/* Notes         | 送信完了通知と受信通知の逆転時の対策として、FC.CTS送信中状 */
/*               | 態の場合もCFフレームを受信する                             */
/******************************************************************************/
static void Gdn_CanTp_JudgeCF( gdn_uint8         N_AI,
                               Gdn_PduLengthType DLC,
                               gdn_uint8         RxFrame[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_PduLengthType                 OffSet;
    Gdn_PduLengthType                 CF_DL;
    Gdn_PduLengthType                 DLC_Min;
    Gdn_PduLengthType                 DataRemained;
    Gdn_PduIdType                     SduId;
    gdn_uint8                         CF_SN;
    gdn_uint8                         ExpectedCF_SN;

    N_AIInfo     = &gdn_cantp_RxNAIInformation[N_AI];
    RxChannel    = N_AIInfo->Channel;

    if ( ( N_AIInfo->N_TaType == GDN_CANTP_Physical ) &&
         ( Gdn_CanTp_ChannelStatus[RxChannel] == GDN_CANTP_RxWaitCF) && /* CF待ち */
         ( N_AI == Gdn_CanTp_NAIidx[RxChannel] ) ) {

        OffSet = GDN_CANTP_NPCIOffSet_N;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        CF_DL  = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            OffSet = GDN_CANTP_NPCIOffSet_E;
            CF_DL  = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
        }

        DLC_Min = Gdn_CanTp_ReceiveSize_FF[RxChannel];
#else
        CF_DL  = GDN_CANTP_CFDLMaxSize_N;
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            OffSet = GDN_CANTP_NPCIOffSet_E;
            CF_DL  = GDN_CANTP_CFDLMaxSize_E;
        }

        DLC_Min = GDN_CANTP_DLCMaxSize;
#endif
        DataRemained = Gdn_CanTp_DataSizeRemained[RxChannel];
        if ( DataRemained < CF_DL ) {   /* 最後のCF受信の場合 */
            DLC_Min = DataRemained + OffSet + GDN_CANTP_NPCISizeCF;
            CF_DL   = DataRemained;
        }

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        /* CF途中:DLCがFF受信時のサイズか */
        /* CF最終:データサイズ+ヘッダサイズ以上 かつ DLCがFF受信時のサイズ以下か */
        if ( ( DLC >= DLC_Min ) &&
             ( DLC <= Gdn_CanTp_ReceiveSize_FF[RxChannel] ) ) {
#else
        if ( DLC >= DLC_Min ) {
#endif

            CF_SN = RxFrame[OffSet] & GDN_CANTP_LoNibbleMask;
            ExpectedCF_SN = Gdn_CanTp_CFSN[RxChannel];
            ExpectedCF_SN++;    /* no wrap around */
            ExpectedCF_SN &= GDN_CANTP_LoNibbleMask;    /* ExpSN = (SN+1)%16 */

            Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx ); /* N_Cr停止 */

            if ( CF_SN == ExpectedCF_SN ) {
                OffSet++;   /* no wrap around */
                Gdn_CanTp_ReceiveCF( N_AI, CF_DL, &RxFrame[OffSet] );

            } else {
                /* 受信キャンセル処理 */
                Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
                SduId = N_AIInfo->SduId;
                Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_WRONG_SN );
            }
        }
        /* else 受信フレームを無視する */
    }
    /* else 受信フレームを無視する */
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_JudgeFC                                          */
/* Description   | FC受信時の条件判定と調停処理                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI    : 受信N_AI                                    */
/*               | (in) DLC     : 受信フレームサイズ                          */
/*               | (in) RxFrame : 受信フレームのバッファ                      */
/* Return Value  | なし                                                       */
/* Notes         | 送信完了通知と受信通知の逆転時の対策として、FF送信中状態及 */
/*               | びブロック内の最後のCF送信中状態の場合もFCフレーム受信する */
/******************************************************************************/
static void Gdn_CanTp_JudgeFC(       gdn_uint8         N_AI,
                                     Gdn_PduLengthType DLC,
                               const gdn_uint8         RxFrame[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_CanTp_StatusType              DetailStatus;
    gdn_uint8                         TxN_AI;
    Gdn_PduLengthType                 OffSet;
    Gdn_PduLengthType                 DLC_Min;
    Gdn_CanTp_BlockSizeType           TxBS;
    Gdn_CanTp_STminType               TxSTmin;
    Gdn_TimeoutValueType              N_Bs;

    N_AIInfo     = &gdn_cantp_RxNAIInformation[N_AI];
    RxChannel    = N_AIInfo->Channel;
    DetailStatus = Gdn_CanTp_ChannelStatus[RxChannel];
    TxN_AI       = Gdn_CanTp_NAIidx[RxChannel];

    if ( ( ( DetailStatus == GDN_CANTP_TxWaitFC1 ) ||   /* 最初のFC.CTS待ち         */
           ( DetailStatus == GDN_CANTP_TxWaitFCx ) ) && /* 2回目以降のFC.CTS待ち    */
         ( N_AI == gdn_cantp_TxNAIInformation[TxN_AI].RxN_AIidx ) ) {

        OffSet  = GDN_CANTP_NPCIOffSet_N;
        DLC_Min = GDN_CANTP_FCMinSize_N;
        if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            OffSet  = GDN_CANTP_NPCIOffSet_E;
            DLC_Min = GDN_CANTP_FCMinSize_E;
        }

        if ( DLC >= DLC_Min ) {

            Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx ); /* N_Bs停止 */
            switch ( RxFrame[OffSet] ) {
                case GDN_CANTP_FCCTS:
                    OffSet++;   /* no wrap around */
                    TxBS    = (Gdn_CanTp_BlockSizeType)RxFrame[OffSet];
                    OffSet++;   /* no wrap around */
                    TxSTmin = (Gdn_CanTp_STminType)RxFrame[OffSet];
                    Gdn_CanTp_UseNewParameter( RxChannel, TxBS, TxSTmin );
                    Gdn_CanTp_ReceiveFCCTS( RxChannel );
                    break;

                case GDN_CANTP_FCWT:
                    N_Bs = gdn_cantp_TxNAIInformation[TxN_AI].N_Bs;
                    Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Bs );

                    break;

                case GDN_CANTP_FCOVFL:
                    Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
                    Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_NO_BUFFER );
                    break;

                default:    /* 未定義のFS受信時、送信中止 */
                    Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
                    Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_INVALID_FS );
                    break;
            }
        }
        /* else 受信フレームを無視する */
    }
    /* else 受信フレームを無視する */
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_RxMediation                                      */
/* Description   | 受信状態の調停処理                                         */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxChannel : 受信中のチャネル                          */
/*               | (in) NewN_AI   : 受信フレームのN_AI                        */
/* Return Value  | フレームの受信処理                                         */
/*               |   GDN_TRUE  受信フレームを処理する                         */
/*               |   GDN_FALSE 受信フレームを無視する                         */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static gdn_bool Gdn_CanTp_RxMediation( Gdn_CanTp_ChannelType RxChannel,
                                       gdn_uint8             NewN_AI )
{
    gdn_bool             ReceiveRx;
    gdn_uint8            CurrentN_AI;
    Gdn_CanTp_StatusType ChannelStatus;
    gdn_uint8            CancelN_AI;
    Gdn_PduIdType        PduId;
    Gdn_PduIdType        SduId;

    ReceiveRx   = GDN_FALSE;
    CurrentN_AI = Gdn_CanTp_NAIidx[RxChannel];

    if ( ( NewN_AI == CurrentN_AI ) ||
         ( gdn_cantp_RxNAIInformation[NewN_AI].Priority < gdn_cantp_RxNAIInformation[CurrentN_AI].Priority ) ) {
        /* 同じN_AI or 異なる受信N_AIの優先度 > 現在処理の優先度 */
        /* 注意：数字が低いほど優先度が高い                      */
        ReceiveRx = GDN_TRUE;
        /* フレーム送信のキャンセル処理 */
        ChannelStatus = Gdn_CanTp_ChannelStatus[RxChannel];
        if ( ( ChannelStatus == GDN_CANTP_RxSendOVFL ) ||
             ( ChannelStatus == GDN_CANTP_RxSendWT   ) ||
             ( ChannelStatus == GDN_CANTP_RxSendCTS  ) ) {  /* FC送信中 */
            CancelN_AI = gdn_cantp_RxNAIInformation[CurrentN_AI].TxN_AIidx;
            PduId = gdn_cantp_TxNAIInformation[CancelN_AI].PduId;
            (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
        }
        /* 受信キャンセル処理 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx );
        Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MinTimerIdx );
        SduId = gdn_cantp_RxNAIInformation[CurrentN_AI].SduId;
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_UNEXP_PDU );
    }
    /* else 受信を無視する */

    return ReceiveRx;
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_TxMediation                                      */
/* Description   | 送信状態の調停処理                                         */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxChannel : 送信中のチャネル                          */
/*               | (in) NewN_AI   : 受信フレームのN_AI                        */
/* Return Value  | フレームの受信処理                                         */
/*               |   GDN_TRUE  受信フレームを処理する                         */
/*               |   GDN_FALSE 受信フレームを無視する                         */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static gdn_bool Gdn_CanTp_TxMediation( Gdn_CanTp_ChannelType TxChannel,
                                       gdn_uint8             NewN_AI )
{
    gdn_bool             ReceiveRx;
    gdn_uint8            CurrentN_AI;
    Gdn_CanTp_StatusType ChannelStatus;
    Gdn_PduIdType        PduId;

    ReceiveRx   = GDN_FALSE;
    CurrentN_AI = Gdn_CanTp_NAIidx[TxChannel];

    if ( gdn_cantp_RxNAIInformation[NewN_AI].Priority < gdn_cantp_TxNAIInformation[CurrentN_AI].Priority ) {
        /* 受信N_AIの優先度 > 現在処理の優先度 */
        /* 注意：数字が低いほど優先度が高い    */
        ReceiveRx = GDN_TRUE;
        /* フレーム送信のキャンセル処理 */
        ChannelStatus = Gdn_CanTp_ChannelStatus[TxChannel];
        if ( ( ChannelStatus == GDN_CANTP_TxSendSF ) ||
             ( ChannelStatus == GDN_CANTP_TxSendFF ) ||
             ( ChannelStatus == GDN_CANTP_TxSendCF ) ) {    /* フレーム送信中 */
            PduId = gdn_cantp_TxNAIInformation[CurrentN_AI].PduId;
            (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
        }
        /* 送信キャンセル処理 */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MaxTimerIdx );
        Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MinTimerIdx );
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)CurrentN_AI, GDN_NTFRSLT_E_UNEXP_PDU );
    }
    /* else 受信を無視する */

    return ReceiveRx;
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_ReceiveSF                                        */
/* Description   | SF受信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI      : 受信N_AI                                  */
/*               | (in) DataSize  : SF_DL                                     */
/*               | (in) RxData    : N_Data                                    */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_ReceiveSF( gdn_uint8         N_AI,
                                 Gdn_PduLengthType DataSize,
                                 gdn_uint8         RxData[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_PduIdType                     RxSduId;
    Gdn_PduLengthType                 BufferRemained;
    Gdn_PduInfoType                   RxPdu;
    Gdn_BufReq_ReturnType             GetBufferResult;

    N_AIInfo         = &gdn_cantp_RxNAIInformation[N_AI];
    RxChannel        = N_AIInfo->Channel;
    RxSduId          = N_AIInfo->SduId;
    BufferRemained   = (Gdn_PduLengthType)0;
    RxPdu.SduDataPtr = &RxData[0];
    RxPdu.SduLength  = DataSize;

    Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxBusy;
    /* 受信開始通知 */
    GetBufferResult = Gdn_PduR_CanTpStartOfReception( RxSduId, &RxPdu, DataSize, &BufferRemained );

    if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&
         ( BufferRemained >= DataSize ) ) {     /* 受信可能 */
        /* 受信データコピー */
        GetBufferResult = Gdn_PduR_CanTpCopyRxData( RxSduId, &RxPdu, &BufferRemained );
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        /* 受信通知 */
        if ( GetBufferResult == GDN_BUFREQ_OK ) {
            Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_OK );
        } else {
            Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_E_NOT_OK );
        }

    } else if ( GetBufferResult == GDN_BUFREQ_OK ) {    /* バッファサイズ不足 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_E_NO_BUFFER );

    } else {    /* SF受信不可 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_ReceiveFF                                        */
/* Description   | FF受信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI     : 受信N_AI                                   */
/*               | (in) DataSize : FF_DL                                      */
/*               | (in) RxData   : FFフレームで受信したN_Data                 */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_ReceiveFF( gdn_uint8         N_AI,
                                 Gdn_PduLengthType DataSize,
                                 gdn_uint8         RxData[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_PduIdType                     RxSduId;
    Gdn_PduLengthType                 BufferRemained;
    Gdn_PduInfoType                   RxPdu;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_PduLengthType                 DataSizeRemained;
    Gdn_TimeoutValueType              N_Br;
    Gdn_TimeoutValueType              N_Br_min;

    N_AIInfo       = &gdn_cantp_RxNAIInformation[N_AI];
    RxChannel      = N_AIInfo->Channel;
    RxSduId        = N_AIInfo->SduId;
    BufferRemained = (Gdn_PduLengthType)0;

    RxPdu.SduDataPtr = &RxData[0];
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    RxPdu.SduLength  = (Gdn_PduLengthType)GDN_CANTP_FD_FFDataSize_N( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        RxPdu.SduLength = (Gdn_PduLengthType)GDN_CANTP_FD_FFDataSize_E( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
    }
#else
    RxPdu.SduLength  = GDN_CANTP_FFDataSize_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        RxPdu.SduLength = GDN_CANTP_FFDataSize_E;
    }
#endif

    Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxBusy;
    /* 受信開始通知 */
    GetBufferResult = Gdn_PduR_CanTpStartOfReception( RxSduId, &RxPdu, DataSize, &BufferRemained );

    if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&
         ( BufferRemained >= RxPdu.SduLength ) ) {  /* 受信可能 */
        /* 受信データコピー */
        GetBufferResult = Gdn_PduR_CanTpCopyRxData( RxSduId, &RxPdu, &BufferRemained );

        if ( GetBufferResult == GDN_BUFREQ_OK ) {
            DataSizeRemained = DataSize - RxPdu.SduLength;  /* JudgeFFでガード */
            Gdn_CanTp_NAIidx[RxChannel]           = N_AI;
            Gdn_CanTp_CFSN[RxChannel]             = (gdn_uint8)0;
            Gdn_CanTp_DataSizeRemained[RxChannel] = DataSizeRemained;
            Gdn_CanTp_FrameCnt[RxChannel]         = GDN_CANTP_BSMinValue;
            Gdn_CanTp_WaitCnt[RxChannel]          = (Gdn_CanTp_WFTMaxType)0;

            if ( N_AIInfo->N_Br_min != (Gdn_TimeoutValueType)0 ) {  /* Br_min使用 */
                Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxDelayCTS;
                N_Br_min = N_AIInfo->N_Br_min;
                N_Br     = N_AIInfo->N_Br;
                Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MinTimerIdx, N_Br_min );
                Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Br );

            } else {
                Gdn_CanTp_GetRxBuffer( RxChannel, N_AI );
            }
        } else {    /* 受信データコピー失敗 */
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
            Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_E_NOT_OK );
        }

    } else if ( ( GetBufferResult == GDN_BUFREQ_OK ) ||
                ( GetBufferResult == GDN_BUFREQ_E_OVFL ) ) {    /* オーバーフロー */

        Gdn_CanTp_NAIidx[RxChannel] = N_AI;
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxDelayOVFL;
        if ( GetBufferResult == GDN_BUFREQ_OK ) {
            /* オーバーフロー時、FC.OVFL送信を待たずに上位層へ異常受信を通知する */
            /* 理由：ISO上、OVERFLOW時にUS_Data.FF_indicationを発行しないため    */
            /*       上位層がアイドルで、CanTpがFC.OVFL送信中の状態が存在する    */
            Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_E_NO_BUFFER );
        }

        if ( N_AIInfo->N_Br_min != (Gdn_TimeoutValueType)0 ) {  /* Br_min使用 */
            N_Br_min = N_AIInfo->N_Br_min;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MinTimerIdx, N_Br_min );

        } else {    /* Br_min不使用 */
            Gdn_CanTp_SendFCOVFL( N_AI );
        }

    } else {    /* FF受信不可 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_ReceiveCF                                        */
/* Description   | CF受信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) N_AI      : 受信N_AI                                  */
/*               | (in) DataSize  : CF_DL                                     */
/*               | (in) RxData    : CFフレームで受信したN_Data                */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_ReceiveCF( gdn_uint8         N_AI,
                                 Gdn_PduLengthType DataSize,
                                 gdn_uint8         RxData[] )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_PduIdType                     RxSduId;
    Gdn_PduLengthType                 BufferRemained;
    Gdn_PduInfoType                   RxPdu;
    Gdn_BufReq_ReturnType             GetBufferResult;
    gdn_uint8                         CF_SN;
    Gdn_CanTp_BlockSizeType           TxBlockSize;
    Gdn_CanTp_BlockSizeType           FrameCnt;
    Gdn_TimeoutValueType              N_Cr;
    Gdn_TimeoutValueType              N_Br;
    Gdn_TimeoutValueType              N_Br_min;

    N_AIInfo         = &gdn_cantp_RxNAIInformation[N_AI];
    RxChannel        = N_AIInfo->Channel;
    RxSduId          = N_AIInfo->SduId;
    BufferRemained   = (Gdn_PduLengthType)0;
    RxPdu.SduDataPtr = &RxData[0];
    RxPdu.SduLength  = DataSize;
    /* 受信データコピー */
    GetBufferResult = Gdn_PduR_CanTpCopyRxData( RxSduId, &RxPdu, &BufferRemained );

    if ( GetBufferResult != GDN_BUFREQ_OK ) {   /* CF受信失敗 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_E_NOT_OK );

    } else if ( Gdn_CanTp_DataSizeRemained[RxChannel] <= DataSize ) {   /* 最後のCF */
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
            Gdn_PduR_CanTpRxIndication( RxSduId, GDN_NTFRSLT_OK );

    } else {
        /* メッセージの残サイズ */
        Gdn_CanTp_DataSizeRemained[RxChannel] -= DataSize;  /* no wrap around */
        /* 現在のCFSN */
        CF_SN = Gdn_CanTp_CFSN[RxChannel];
        CF_SN++;    /* no wrap around */
        CF_SN &= GDN_CANTP_LoNibbleMask;    /* SN = (SN+1)%16 */
        Gdn_CanTp_CFSN[RxChannel] = CF_SN;

        TxBlockSize = N_AIInfo->BlockSize;
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        if ( Gdn_CanTp_BSValueChanged[N_AI] == GDN_TRUE ) {
            TxBlockSize = Gdn_CanTp_UserBSValue[N_AI];
        }
#endif
        FrameCnt = Gdn_CanTp_FrameCnt[RxChannel];
        FrameCnt++; /* no wrap around */

        if ( TxBlockSize == (Gdn_PduLengthType)0 ) {    /* ブロック不使用 */
            N_Cr = N_AIInfo->N_Cr;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Cr );

        } else if ( FrameCnt < TxBlockSize ) {  /* ブロック受信中 */
            Gdn_CanTp_FrameCnt[RxChannel] = FrameCnt;
            N_Cr = N_AIInfo->N_Cr;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Cr );

        } else if ( N_AIInfo->N_Br_min != (Gdn_TimeoutValueType)0 ) {
            /* 次のブロック受信、Br_min使用 */
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxDelayCTS;
            N_Br_min = N_AIInfo->N_Br_min;
            N_Br     = N_AIInfo->N_Br;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MinTimerIdx, N_Br_min );
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Br );

        } else {
            Gdn_CanTp_GetRxBuffer( RxChannel, N_AI );
        }
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_ReceiveFCCTS                                     */
/* Description   | FC.CTS受信処理                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxChannel : 受信チャネル                              */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_ReceiveFCCTS( Gdn_CanTp_ChannelType RxChannel )
{
    gdn_uint8               TxN_AI;
    Gdn_TimeoutValueType    N_Cs_min;

    TxN_AI = Gdn_CanTp_NAIidx[RxChannel];

    Gdn_CanTp_FrameCnt[RxChannel] = (Gdn_CanTp_BlockSizeType)0;

    N_Cs_min = gdn_cantp_TxNAIInformation[TxN_AI].N_Cs_min;
    Gdn_CanTp_GetTxBuffer( RxChannel, TxN_AI, N_Cs_min );
}

#if ( REPROG_CFG_SUBMICON_USE_SUB != STD_ON )
/******************************************************************************/
/* Function Name | Gdn_CanTp_SendFF                                           */
/* Description   | FF送信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxSduId     : 送信SduId                               */
/*               | (in) MessageSize : 送信メッセージサイズ                    */
/* Return Value  | 送信処理の結果                                             */
/*               |  GDN_E_OK     : FF送信要求を実施した                       */
/*               |  GDN_E_NOT_OK : 送信要求を実施できない                     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static Gdn_Std_ReturnType Gdn_CanTp_SendFF( Gdn_PduIdType     TxSduId,
                                            Gdn_PduLengthType MessageSize )
{
    Gdn_Std_ReturnType                t_Result;
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             TxChannel;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    gdn_uint8                         TxBuffer[GDN_CANTP_FD_DLCMaxSize];
#else
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
#endif
    Gdn_PduLengthType                 OffSet;
    Gdn_PduInfoType                   TxPdu;
    Gdn_PduLengthType                 DataSizeRemained;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_PduIdType                     PduId;
    Gdn_TimeoutValueType              N_As;

    t_Result  = GDN_E_NOT_OK;
    N_AIInfo  = &gdn_cantp_TxNAIInformation[TxSduId];
    TxChannel = N_AIInfo->Channel;

    OffSet = GDN_CANTP_NPCIOffSet_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)N_AIInfo->TargetAddress;   /* N_TA作成 */
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

    TxBuffer[OffSet] = GDN_CANTP_FF + (gdn_uint8)(MessageSize >> GDN_CANTP_Shift1Byte); /* N_PCI#1作成 */
    OffSet++;   /* no wrap around */
    TxBuffer[OffSet] = (gdn_uint8)MessageSize;  /* N_PCI#2作成 */
    OffSet++;   /* no wrap around */

    TxPdu.SduDataPtr = &TxBuffer[OffSet];
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    TxPdu.SduLength  = N_AIInfo->SendSize - OffSet;
#else
    TxPdu.SduLength  = GDN_CANTP_DLCMaxSize - OffSet;
#endif
    DataSizeRemained = (Gdn_PduLengthType)0;

    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxSendFF;
    /* N_Data作成 */
    GetBufferResult = Gdn_PduR_CanTpCopyTxData( TxSduId, &TxPdu, (Gdn_RetryInfoType*)GDN_NULL_PTR, &DataSizeRemained );

    if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&
         ( DataSizeRemained != (Gdn_PduLengthType)0 ) ) {

        TxPdu.SduDataPtr = &TxBuffer[0];
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        TxPdu.SduLength  = N_AIInfo->SendSize;
#else
        TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
#endif
        /* FFフレーム送信 */
        PduId = N_AIInfo->PduId;
        t_Result = Gdn_CanIf_Transmit( PduId, &TxPdu );

        if ( t_Result == GDN_E_OK ) {
            Gdn_CanTp_NAIidx[TxChannel]           = (gdn_uint8)TxSduId;
            Gdn_CanTp_CFSN[TxChannel]             = (gdn_uint8)0;
            Gdn_CanTp_DataSizeRemained[TxChannel] = DataSizeRemained;
            N_As = N_AIInfo->N_As;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_As );
        } else {    /* 送信失敗 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        }

    } else {    /* GDN_BUFREQ_E_NOT_OK */   /* GDN_BUFREQ_E_BUSY */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
    }

    return t_Result;
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SendSF                                           */
/* Description   | SF送信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxSduId     : 送信SduId                               */
/*               | (in) MessageSize : 送信メッセージサイズ                    */
/* Return Value  | 送信処理の結果                                             */
/*               |  GDN_E_OK     : SF送信要求を実施した                       */
/*               |  GDN_E_NOT_OK : 送信要求を実施できない                     */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static Gdn_Std_ReturnType Gdn_CanTp_SendSF( Gdn_PduIdType     TxSduId,
                                            Gdn_PduLengthType MessageSize )
{
    Gdn_Std_ReturnType                t_Result;
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             TxChannel;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    gdn_uint8                         TxBuffer[GDN_CANTP_FD_DLCMaxSize];
    Gdn_PduLengthType                 TxDataLength;
#else
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
#endif
    Gdn_PduLengthType                 OffSet;
    Gdn_PduInfoType                   TxPdu;
    Gdn_PduLengthType                 DataSizeRemained;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_PduIdType                     PduId;
    Gdn_TimeoutValueType              N_As;

    t_Result  = GDN_E_NOT_OK;
    N_AIInfo  = &gdn_cantp_TxNAIInformation[TxSduId];
    TxChannel = N_AIInfo->Channel;

    OffSet = GDN_CANTP_NPCIOffSet_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)N_AIInfo->TargetAddress;   /* N_TA作成 */
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    TxDataLength = MessageSize + OffSet + GDN_CANTP_NPCISizeSF;
    if ( TxDataLength <= GDN_CANTP_CAN_DL_8 ) {
        TxBuffer[OffSet] = (gdn_uint8)MessageSize;                  /* N_PCI作成:0byte目にSF_DLを設定 */
        OffSet++;   /* no wrap around */
    } else {
        TxDataLength = MessageSize + OffSet + GDN_CANTP_FD_NPCISizeSF;
        TxBuffer[OffSet] = GDN_CANTP_SF;                            /* N_PCI作成:0byte目に0x00を設定 */
        OffSet++;   /* no wrap around */
        TxBuffer[OffSet] = (gdn_uint8)MessageSize;                  /* N_PCI作成:1byte目にSF_DLを設定 */
        OffSet++;   /* no wrap around */
    }

#else
    TxBuffer[OffSet] = (gdn_uint8)MessageSize;  /* N_PCI作成 */
    OffSet++;   /* no wrap around */
#endif
    TxPdu.SduDataPtr = &TxBuffer[OffSet];
    TxPdu.SduLength  = MessageSize;
    DataSizeRemained = (Gdn_PduLengthType)0;

    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxSendSF;
    /* N_Data作成 */
    GetBufferResult = Gdn_PduR_CanTpCopyTxData( TxSduId, &TxPdu, (Gdn_RetryInfoType*)GDN_NULL_PTR, &DataSizeRemained );

    if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&
         ( DataSizeRemained == (Gdn_PduLengthType)0 ) ) {

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        for ( OffSet += MessageSize ; OffSet < (Gdn_PduLengthType)Gdn_CanTp_OptimizeSendLengthTbl[TxDataLength]; OffSet++ ) {   /* no wrap around */
            TxBuffer[OffSet] = N_AIInfo->PaddingValue;  /* パディング処理 */
        }

        TxPdu.SduDataPtr = &TxBuffer[0];
        TxPdu.SduLength  = (Gdn_PduLengthType)Gdn_CanTp_OptimizeSendLengthTbl[TxDataLength];
#else
        for ( OffSet += MessageSize ; OffSet < GDN_CANTP_DLCMaxSize; OffSet++ ) {   /* no wrap around */
            TxBuffer[OffSet] = N_AIInfo->PaddingValue;  /* パディング処理 */
        }

        TxPdu.SduDataPtr = &TxBuffer[0];
        TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
#endif
        PduId =  N_AIInfo->PduId;
        /* SFフレーム送信 */
        t_Result = Gdn_CanIf_Transmit(PduId, &TxPdu );

        if ( t_Result == GDN_E_OK ) {
            Gdn_CanTp_NAIidx[TxChannel] = (gdn_uint8)TxSduId;
            N_As = N_AIInfo->N_As;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_As );
        } else {    /* 送信失敗 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        }

    } else {    /* GDN_BUFREQ_E_NOT_OK */   /* GDN_BUFREQ_E_BUSY */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
    }

    return t_Result;
}
#endif

/******************************************************************************/
/* Function Name | Gdn_CanTp_SendCF                                           */
/* Description   | CF送信処理                                                 */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxN_AI : 送信N_AI                                     */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_SendCF( gdn_uint8 TxN_AI )
{
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_CanTp_ChannelType             TxChannel;
    Gdn_PduLengthType                 OffSet;
    Gdn_PduLengthType                 CF_DL;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    gdn_uint8                         TxBuffer[GDN_CANTP_FD_DLCMaxSize];
    Gdn_PduLengthType                 TxDataLength;
#else
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
#endif
    gdn_uint8                         CF_SN;
    Gdn_PduInfoType                   TxPdu;
    Gdn_PduLengthType                 DataSizeRemained;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_Std_ReturnType                SendResult;
    Gdn_PduIdType                     PduId;
    Gdn_TimeoutValueType              N_As;

    N_AIInfo  = &gdn_cantp_TxNAIInformation[TxN_AI];
    TxChannel = N_AIInfo->Channel;
    OffSet    = GDN_CANTP_NPCIOffSet_N;
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    CF_DL     = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( N_AIInfo->SendSize );
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)N_AIInfo->TargetAddress;   /* N_TA作成 */
        OffSet      = GDN_CANTP_NPCIOffSet_E;
        CF_DL       = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( N_AIInfo->SendSize );
    }
#else
    CF_DL     = GDN_CANTP_CFDLMaxSize_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)N_AIInfo->TargetAddress;   /* N_TA作成 */
        OffSet      = GDN_CANTP_NPCIOffSet_E;
        CF_DL       = GDN_CANTP_CFDLMaxSize_E;
    }
#endif

    CF_SN = Gdn_CanTp_CFSN[TxChannel];
    CF_SN++;    /* no wrap around */
    CF_SN &= GDN_CANTP_LoNibbleMask;    /* SN = (SN+1)%16 */
    TxBuffer[OffSet] = GDN_CANTP_CF + CF_SN;    /* N_PCI作成 */
    OffSet++;   /* no wrap around */
    TxPdu.SduDataPtr = &TxBuffer[OffSet];
    TxPdu.SduLength  = CF_DL;
    DataSizeRemained = Gdn_CanTp_DataSizeRemained[TxChannel];
    if ( CF_DL > DataSizeRemained ) {   /* メッセージ最後のCF送信 */
        TxPdu.SduLength  = DataSizeRemained;
    }

    /* N_Data作成 */
    GetBufferResult = Gdn_PduR_CanTpCopyTxData( (Gdn_PduIdType)TxN_AI, &TxPdu, (Gdn_RetryInfoType*)GDN_NULL_PTR, &DataSizeRemained );

    if ( GetBufferResult == GDN_BUFREQ_OK ) {
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
        TxDataLength = OffSet + TxPdu.SduLength;
        for ( OffSet += TxPdu.SduLength; OffSet < (Gdn_PduLengthType)Gdn_CanTp_OptimizeSendLengthTbl[TxDataLength]; OffSet++ ) {    /* no wrap around */
            TxBuffer[OffSet] = N_AIInfo->PaddingValue;  /* パディング処理 */
        }
        Gdn_CanTp_FrameCnt[TxChannel]++;    /* no wrap around */
        Gdn_CanTp_CFSN[TxChannel]             = CF_SN;
        Gdn_CanTp_DataSizeRemained[TxChannel] = DataSizeRemained;

        TxPdu.SduDataPtr = &TxBuffer[0];
        TxPdu.SduLength  = (Gdn_PduLengthType)Gdn_CanTp_OptimizeSendLengthTbl[TxDataLength];
#else
        for ( OffSet += TxPdu.SduLength; OffSet < GDN_CANTP_DLCMaxSize; OffSet++ ) {    /* no wrap around */
            TxBuffer[OffSet] = N_AIInfo->PaddingValue;  /* パディング処理 */
        }
        Gdn_CanTp_FrameCnt[TxChannel]++;    /* no wrap around */
        Gdn_CanTp_CFSN[TxChannel]             = CF_SN;
        Gdn_CanTp_DataSizeRemained[TxChannel] = DataSizeRemained;

        TxPdu.SduDataPtr = &TxBuffer[0];
        TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
#endif
        PduId = N_AIInfo->PduId;
        /* CFフレーム送信 */
        SendResult = Gdn_CanIf_Transmit( PduId, &TxPdu );

        if ( SendResult == GDN_E_OK ) {
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxSendCF;
            N_As = N_AIInfo->N_As;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_As );

        } else {    /* 送信失敗 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
            Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_NOT_OK );
        }

    } else {    /* 送信失敗 */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_NOT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SendFCOVFL                                       */
/* Description   | FC.OVFL送信処理                                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxN_AI : 受信N_AI                                     */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_SendFCOVFL( gdn_uint8 RxN_AI )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* RxN_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    gdn_uint8                         TxN_AI;
    GdnConst Gdn_CanTp_TxNAIInfoType* TxN_AIInfo;
    Gdn_PduLengthType                 OffSet;
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
    Gdn_PduInfoType                   TxPdu;
    Gdn_Std_ReturnType                SendResult;
    Gdn_PduIdType                     PduId;
    Gdn_TimeoutValueType              N_Ar;

    RxN_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];
    RxChannel  = RxN_AIInfo->Channel;
    TxN_AI     = RxN_AIInfo->TxN_AIidx;
    TxN_AIInfo = &gdn_cantp_TxNAIInformation[TxN_AI];

    OffSet = GDN_CANTP_NPCIOffSet_N;
    if ( TxN_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)TxN_AIInfo->TargetAddress; /* N_TA作成 */
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

    TxBuffer[OffSet] = GDN_CANTP_FCOVFL;    /* N_PCI作成 */
    OffSet++;   /* no wrap around */
    TxBuffer[OffSet] = RxN_AIInfo->BlockSize;   /* BS */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
    if ( Gdn_CanTp_BSValueChanged[RxN_AI] == GDN_TRUE ) {
        TxBuffer[OffSet] = Gdn_CanTp_UserBSValue[RxN_AI];
    }
#endif
    OffSet++;   /* no wrap around */
    TxBuffer[OffSet] = RxN_AIInfo->STmin;   /* STmin */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
    if ( Gdn_CanTp_STminValueChanged[RxN_AI] == GDN_TRUE ) {
        TxBuffer[OffSet] = Gdn_CanTp_UserSTminValue[RxN_AI];
    }
#endif

    for ( OffSet++; OffSet < GDN_CANTP_DLCMaxSize; OffSet++ ) { /* no wrap around */
        TxBuffer[OffSet] = TxN_AIInfo->PaddingValue;
    }

    TxPdu.SduDataPtr = &TxBuffer[0];
    TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
    PduId            = TxN_AIInfo->PduId;
    /* FC.OVFLフレーム送信 */
    SendResult = Gdn_CanIf_Transmit( PduId, &TxPdu );

    if ( SendResult == GDN_E_OK ) {
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxSendOVFL;
        N_Ar = RxN_AIInfo->N_Ar;
        Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Ar );

    } else {    /* 送信失敗 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SendFCCTS                                        */
/* Description   | FC.CTS送信処理                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxN_AI : 受信N_AI                                     */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_SendFCCTS( gdn_uint8 RxN_AI )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* RxN_AIInfo;
    Gdn_CanTp_ChannelType             RxChannel;
    gdn_uint8                         TxN_AI;
    GdnConst Gdn_CanTp_TxNAIInfoType* TxN_AIInfo;
    Gdn_PduLengthType                 OffSet;
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
    Gdn_PduInfoType                   TxPdu;
    Gdn_Std_ReturnType                SendResult;
    Gdn_PduIdType                     PduId;
    Gdn_PduIdType                     SduId;
    Gdn_TimeoutValueType              N_Ar;

    RxN_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];
    RxChannel  = RxN_AIInfo->Channel;
    TxN_AI     = RxN_AIInfo->TxN_AIidx;
    TxN_AIInfo = &gdn_cantp_TxNAIInformation[TxN_AI];

    OffSet = GDN_CANTP_NPCIOffSet_N;
    if ( TxN_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        TxBuffer[0] = (gdn_uint8)TxN_AIInfo->TargetAddress; /* N_TA作成 */
        OffSet = GDN_CANTP_NPCIOffSet_E;
    }

    TxBuffer[OffSet] = GDN_CANTP_FCCTS;  /* N_PCI作成 */
    OffSet++;   /* no wrap around */
    TxBuffer[OffSet] = RxN_AIInfo->BlockSize;   /* BS */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
    if ( Gdn_CanTp_BSValueChanged[RxN_AI] == GDN_TRUE ) {
        TxBuffer[OffSet] = Gdn_CanTp_UserBSValue[RxN_AI];
    }
#endif
    OffSet++;   /* no wrap around */
    TxBuffer[OffSet] = RxN_AIInfo->STmin;   /* STmin */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
    if ( Gdn_CanTp_STminValueChanged[RxN_AI] == GDN_TRUE ) {
        TxBuffer[OffSet] = Gdn_CanTp_UserSTminValue[RxN_AI];
    }
#endif

    for ( OffSet++; OffSet < GDN_CANTP_DLCMaxSize; OffSet++ ) { /* no wrap around */
        TxBuffer[OffSet] = TxN_AIInfo->PaddingValue;
    }

    TxPdu.SduDataPtr = &TxBuffer[0];
    TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
    PduId            = TxN_AIInfo->PduId;
    /* FC.CTSフレーム送信 */
    SendResult = Gdn_CanIf_Transmit( PduId, &TxPdu );

    if ( SendResult == GDN_E_OK ) {
        Gdn_CanTp_WaitCnt[RxChannel]       = (Gdn_CanTp_WFTMaxType)0;
        Gdn_CanTp_FrameCnt[RxChannel]      = GDN_CANTP_BSMinValue;
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxSendCTS;
        N_Ar = RxN_AIInfo->N_Ar;
        Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Ar );

    } else {    /* 送信失敗 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        SduId = RxN_AIInfo->SduId;
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_NOT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SendFCWT                                         */
/* Description   | FC.WAIT送信処理                                            */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxN_AI : 受信N_AI                                     */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_SendFCWT( gdn_uint8 RxN_AI )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* RxN_AIInfo;
    Gdn_CanTp_WFTMaxType              TxWFTMax;
    Gdn_CanTp_ChannelType             RxChannel;
    Gdn_CanTp_WFTMaxType              WaitCnt;
    gdn_uint8                         TxN_AI;
    GdnConst Gdn_CanTp_TxNAIInfoType* TxN_AIInfo;
    Gdn_PduLengthType                 OffSet;
    gdn_uint8                         TxBuffer[GDN_CANTP_DLCMaxSize];
    Gdn_PduInfoType                   TxPdu;
    Gdn_Std_ReturnType                SendResult;
    Gdn_PduIdType                     PduId;
    Gdn_PduIdType                     SduId;
    Gdn_TimeoutValueType              N_Ar;

    RxN_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];
    TxWFTMax   = RxN_AIInfo->WFTMax;
    RxChannel  = RxN_AIInfo->Channel;
    WaitCnt    = Gdn_CanTp_WaitCnt[RxChannel];
    TxN_AI     = RxN_AIInfo->TxN_AIidx;
    TxN_AIInfo = &gdn_cantp_TxNAIInformation[TxN_AI];

    if ( WaitCnt < TxWFTMax ) { /* FC.WT送信可 */
        OffSet = GDN_CANTP_NPCIOffSet_N;
        if ( TxN_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
            TxBuffer[0] = (gdn_uint8)TxN_AIInfo->TargetAddress; /* N_TA作成 */
            OffSet = GDN_CANTP_NPCIOffSet_E;
        }

        TxBuffer[OffSet] = GDN_CANTP_FCWT;  /* N_PCI作成 */
        OffSet++;   /* no wrap around */
        TxBuffer[OffSet] = RxN_AIInfo->BlockSize;   /* BS */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        if ( Gdn_CanTp_BSValueChanged[RxN_AI] == GDN_TRUE ) {
            TxBuffer[OffSet] = Gdn_CanTp_UserBSValue[RxN_AI];
        }
#endif
        OffSet++;   /* no wrap around */
        TxBuffer[OffSet] = RxN_AIInfo->STmin;   /* STmin */
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        if ( Gdn_CanTp_STminValueChanged[RxN_AI] == GDN_TRUE ) {
            TxBuffer[OffSet] = Gdn_CanTp_UserSTminValue[RxN_AI];
        }
#endif

        for ( OffSet++; OffSet < GDN_CANTP_DLCMaxSize; OffSet++ ) { /* no wrap around */
            TxBuffer[OffSet] = TxN_AIInfo->PaddingValue;
        }

        TxPdu.SduDataPtr = &TxBuffer[0];
        TxPdu.SduLength  = GDN_CANTP_DLCMaxSize;
        PduId            = TxN_AIInfo->PduId;
        /* FC.WTフレーム送信 */
        SendResult = Gdn_CanIf_Transmit( PduId, &TxPdu );

        if ( SendResult == GDN_E_OK ) {
            WaitCnt++;
            Gdn_CanTp_WaitCnt[RxChannel] = WaitCnt;

            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxSendWT;
            N_Ar = RxN_AIInfo->N_Ar;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Ar );

        } else {    /* 送信失敗 */
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
            SduId = RxN_AIInfo->SduId;
            Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_NOT_OK );
        }

    } else {
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        SduId = RxN_AIInfo->SduId;
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_WFT_OVRN );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_FCWTConfirmation                                 */
/* Description   | FC.WAIT送信完了処理                                        */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxChannel : FC.WAIT送信チャネル                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_FCWTConfirmation( Gdn_CanTp_ChannelType TxChannel )
{
    gdn_uint8                         RxN_AI;
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_TimeoutValueType              N_Br_min;
    Gdn_TimeoutValueType              N_Br;

    RxN_AI   = Gdn_CanTp_NAIidx[TxChannel];
    N_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];

    if ( N_AIInfo->N_Br_min != (Gdn_TimeoutValueType)0 ) {  /* Br_min使用 */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_RxDelayCTS;
        N_Br_min = N_AIInfo->N_Br_min;
        N_Br     = N_AIInfo->N_Br;
        Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MinTimerIdx, N_Br_min );
        Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_Br );

    } else {
        Gdn_CanTp_GetRxBuffer( TxChannel, RxN_AI );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_CFConfirmation                                   */
/* Description   | CF送信完了処理                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxChannel : CF送信チャネル                            */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_CFConfirmation( Gdn_CanTp_ChannelType TxChannel )
{
    gdn_uint8                         TxN_AI;
    Gdn_CanTp_BlockSizeType           TxBlockSize;
    Gdn_TimeoutValueType              N_Bs;

    TxN_AI   = Gdn_CanTp_NAIidx[TxChannel];

    if ( Gdn_CanTp_DataSizeRemained[TxChannel] != (Gdn_CanTp_BlockSizeType)0 ) {
        /* 送信途中のCF */
        TxBlockSize = Gdn_CanTp_BlockSize[TxChannel];

        if ( ( TxBlockSize != (Gdn_CanTp_BlockSizeType)0 ) &&
             ( Gdn_CanTp_FrameCnt[TxChannel] >= TxBlockSize ) ) {   /* ブロック内の最終CF */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxWaitFCx;
            N_Bs = gdn_cantp_TxNAIInformation[TxN_AI].N_Bs;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_Bs );

        } else {    /* 次のCFを送信する */
            Gdn_CanTp_GetTxBuffer( TxChannel, TxN_AI, (Gdn_TimeoutValueType)Gdn_CanTp_STmin[TxChannel] );
        }

    } else {    /* 最終CF */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_RxDataRetry                                      */
/* Description   | 受信バッファ取得のリトライ処理                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxChannel : CF受信チャネル                            */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_RxDataRetry( Gdn_CanTp_ChannelType RxChannel )
{
    gdn_uint8                         N_AI;
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_PduLengthType                 BufferRemained;
    Gdn_PduInfoType                   RxPdu;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_CanTp_BlockSizeType           TxBlockSize;
    Gdn_PduLengthType                 BlockDataSize;
    Gdn_PduLengthType                 CF_DL_Max;
    Gdn_PduIdType                     SduId;

    N_AI           = Gdn_CanTp_NAIidx[RxChannel];
    N_AIInfo       = &gdn_cantp_RxNAIInformation[N_AI];
    BufferRemained = (Gdn_PduLengthType)0;

    RxPdu.SduDataPtr = GDN_NULL_PTR;
    RxPdu.SduLength  = (Gdn_PduLengthType)0;
    SduId            = N_AIInfo->SduId;
    /* 受信バッファ有無確認 */
    GetBufferResult = Gdn_PduR_CanTpCopyRxData( SduId, &RxPdu, &BufferRemained );

    if ( GetBufferResult == GDN_BUFREQ_OK ) {
        TxBlockSize = N_AIInfo->BlockSize;
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        if ( Gdn_CanTp_BSValueChanged[N_AI] == GDN_TRUE ) {
            TxBlockSize = Gdn_CanTp_UserBSValue[N_AI];
        }
#endif
        /* 1ブロックの受信データ数を算出 */
        BlockDataSize = (Gdn_PduLengthType)0;
        if ( TxBlockSize != GDN_CANTP_BSMinValue ) {
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            CF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
            if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                CF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
            }
#else
            CF_DL_Max = GDN_CANTP_CFDLMaxSize_N;
            if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                CF_DL_Max = GDN_CANTP_CFDLMaxSize_E;
            }
#endif
            BlockDataSize = (Gdn_PduLengthType)( TxBlockSize * CF_DL_Max );
        }

        if ( ( BufferRemained >= Gdn_CanTp_DataSizeRemained[RxChannel] ) ||
             ( ( BlockDataSize != (Gdn_PduLengthType)0 ) &&
               ( BufferRemained >= BlockDataSize ) ) ) {    /* 次のブロック受信可 */
            Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx ); /* N_Br停止 */
            Gdn_CanTp_SendFCCTS( N_AI );

        } else {
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxBusy;
        }

    } else {    /* 受信データコピー失敗 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        Gdn_CanTp_ReleaseTimer( RxChannel, GDN_CANTP_MaxTimerIdx ); /* N_Br停止 */
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_NOT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_TxDataRetry                                      */
/* Description   | 送信データ取得のリトライ処理                               */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxChannel : CF送信チャネル                            */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_TxDataRetry( Gdn_CanTp_ChannelType TxChannel )
{
    gdn_uint8             TxN_AI;
    Gdn_PduLengthType     CF_DL;
    Gdn_PduInfoType       TxPdu;
    Gdn_PduLengthType     DataSizeRemained;
    Gdn_BufReq_ReturnType GetBufferResult;

    TxN_AI           = Gdn_CanTp_NAIidx[TxChannel];
    DataSizeRemained = (Gdn_PduLengthType)0;
    TxPdu.SduDataPtr = GDN_NULL_PTR;
    TxPdu.SduLength  = (Gdn_PduLengthType)0;

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    CF_DL = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( gdn_cantp_TxNAIInformation[TxN_AI].SendSize );
    if ( gdn_cantp_TxNAIInformation[TxN_AI].AddressFormat == GDN_CANTP_Extended ) {
        CF_DL = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( gdn_cantp_TxNAIInformation[TxN_AI].SendSize );
    }
#else
    CF_DL = GDN_CANTP_CFDLMaxSize_N;
    if ( gdn_cantp_TxNAIInformation[TxN_AI].AddressFormat == GDN_CANTP_Extended ) {
        CF_DL = GDN_CANTP_CFDLMaxSize_E;
    }
#endif
    if ( CF_DL > Gdn_CanTp_DataSizeRemained[TxChannel] ) {   /* メッセージ最後のCF送信 */
        CF_DL = Gdn_CanTp_DataSizeRemained[TxChannel];
    }

    /* 送信データ有無の確認 */
    GetBufferResult = Gdn_PduR_CanTpCopyTxData( (Gdn_PduIdType)TxN_AI, &TxPdu, (Gdn_RetryInfoType*)GDN_NULL_PTR, &DataSizeRemained );

    switch ( GetBufferResult ) {
        case GDN_BUFREQ_OK:
            if ( DataSizeRemained >= CF_DL ) {  /* 送信データあり */
                Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MaxTimerIdx );     /* N_Cs停止 */

                if ( Gdn_CanTp_ChannelStatus[TxChannel] == GDN_CANTP_TxGetDelay ) {
                    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxDelayCF;
                } else {    /* GDN_CANTP_TxGetNoDelay */
                    Gdn_CanTp_SendCF( TxN_AI );
                }
            }
            /* else リトライ継続 */
            break;

        case GDN_BUFREQ_E_BUSY:
            break;  /* リトライ継続 */

        default:    /* 異常 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
            Gdn_CanTp_ReleaseTimer( TxChannel, GDN_CANTP_MaxTimerIdx ); /* N_Cs停止 */
            Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_NOT_OK );
            break;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_GetRxBuffer                                      */
/* Description   | 受信バッファ有無の確認                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxChannel : 受信チャネル                              */
/* Parameters    | (in) RxN_AI    : 受信N_AI                                  */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_GetRxBuffer( Gdn_CanTp_ChannelType RxChannel,
                                   gdn_uint8 RxN_AI )
{
    GdnConst Gdn_CanTp_RxNAIInfoType* N_AIInfo;
    Gdn_PduLengthType                 BufferRemained;
    Gdn_PduInfoType                   RxPdu;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_CanTp_BlockSizeType           TxBlockSize;
    Gdn_PduLengthType                 BlockDataSize;
    Gdn_PduLengthType                 CF_DL_Max;
    Gdn_PduIdType                     SduId;
    Gdn_TimeoutValueType              N_Br;

    N_AIInfo = &gdn_cantp_RxNAIInformation[RxN_AI];

    BufferRemained   = (Gdn_PduLengthType)0;
    RxPdu.SduDataPtr = GDN_NULL_PTR;
    RxPdu.SduLength  = (Gdn_PduLengthType)0;
    SduId            = N_AIInfo->SduId;
    /* 受信バッファ有無確認 */
    GetBufferResult = Gdn_PduR_CanTpCopyRxData( SduId, &RxPdu, &BufferRemained );

    if ( GetBufferResult == GDN_BUFREQ_OK ) {
        TxBlockSize = N_AIInfo->BlockSize;
#if ( GDN_CANTP_ChangeParameterApi == GDN_ON )
        if ( Gdn_CanTp_BSValueChanged[RxN_AI] == GDN_TRUE ) {
            TxBlockSize = Gdn_CanTp_UserBSValue[RxN_AI];
        }
#endif
        /* 1ブロックの受信データ数を算出 */
        if ( TxBlockSize != GDN_CANTP_BSMinValue ) {
#if ( GDN_CANTP_CanFDSupport == GDN_ON )
            CF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
            if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                CF_DL_Max = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( Gdn_CanTp_ReceiveSize_FF[RxChannel] );
            }
#else
            CF_DL_Max = GDN_CANTP_CFDLMaxSize_N;
            if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
                CF_DL_Max = GDN_CANTP_CFDLMaxSize_E;
            }
#endif
            BlockDataSize = (Gdn_PduLengthType)( TxBlockSize * CF_DL_Max );
        }

        if ( ( BufferRemained >= Gdn_CanTp_DataSizeRemained[RxChannel] ) ||
             ( ( TxBlockSize != GDN_CANTP_BSMinValue ) &&
               ( BufferRemained >= BlockDataSize ) ) ) {    /* 次のブロック受信可 */
            /* FC.CTS送信 */
            Gdn_CanTp_SendFCCTS( RxN_AI );

        } else if ( N_AIInfo->N_Br == (Gdn_TimeoutValueType)0 ) {   /* リトライ不使用 */
            Gdn_CanTp_SendFCWT( RxN_AI );

        } else {
            Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_RxBusy;
            N_Br = N_AIInfo->N_Br;
            Gdn_CanTp_SetTimer( RxChannel, GDN_CANTP_MaxTimerIdx, N_Br );
        }

    } else {    /* 受信データコピー失敗 */
        Gdn_CanTp_ChannelStatus[RxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_NOT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_GetTxBuffer                                      */
/* Description   | 送信バッファ有無の確認                                     */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TxChannel : 送信チャネル                              */
/* Parameters    | (in) TxN_AI    : 送信N_AI                                  */
/*               | (in) MinTimer  : MinTimer(Cs_min or STmin)の値             */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_GetTxBuffer( Gdn_CanTp_ChannelType TxChannel,
                                   gdn_uint8 TxN_AI,
                                   Gdn_TimeoutValueType MinTimer )
{
    GdnConst Gdn_CanTp_TxNAIInfoType* N_AIInfo;
    Gdn_PduInfoType                   TxPdu;
    Gdn_PduLengthType                 DataSizeRemained;
    Gdn_PduLengthType                 CF_DL;
    Gdn_BufReq_ReturnType             GetBufferResult;
    Gdn_TimeoutValueType              N_Cs;

    N_AIInfo = &gdn_cantp_TxNAIInformation[TxN_AI];

    TxPdu.SduDataPtr = GDN_NULL_PTR;
    TxPdu.SduLength  = (Gdn_PduLengthType)0;
    DataSizeRemained = (Gdn_PduLengthType)0;

#if ( GDN_CANTP_CanFDSupport == GDN_ON )
    CF_DL = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_N( N_AIInfo->SendSize );
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        CF_DL = (Gdn_PduLengthType)GDN_CANTP_FD_CFDLMaxSize_E( N_AIInfo->SendSize );
    }
#else
    CF_DL = GDN_CANTP_CFDLMaxSize_N;
    if ( N_AIInfo->AddressFormat == GDN_CANTP_Extended ) {
        CF_DL = GDN_CANTP_CFDLMaxSize_E;
    }
#endif
    if ( CF_DL > Gdn_CanTp_DataSizeRemained[TxChannel] ) {   /* メッセージ最後のCF送信 */
        CF_DL = Gdn_CanTp_DataSizeRemained[TxChannel];
    }

    Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxGetNoDelay;
    /* 送信データ有無の確認 */
    GetBufferResult = Gdn_PduR_CanTpCopyTxData( (Gdn_PduIdType)TxN_AI, &TxPdu, (Gdn_RetryInfoType*)GDN_NULL_PTR, &DataSizeRemained );

    if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&
         ( DataSizeRemained >= CF_DL ) ) {  /* 送信データあり */

        if ( MinTimer != (Gdn_TimeoutValueType)0 ) {    /* Minタイマ使用 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxDelayCF;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MinTimerIdx, MinTimer );

        } else {
            Gdn_CanTp_SendCF( TxN_AI );
        }

    } else if ( ( GetBufferResult == GDN_BUFREQ_OK ) &&              /* 送信データなし */
                ( N_AIInfo->N_Cs != (Gdn_TimeoutValueType)0 ) ) {    /* 遅延可         */

        if ( MinTimer != (Gdn_TimeoutValueType)0 ) {    /* Minタイマ使用 */
            Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_TxGetDelay;
            Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MinTimerIdx, MinTimer );
        }

        N_Cs = N_AIInfo->N_Cs;
        Gdn_CanTp_SetTimer( TxChannel, GDN_CANTP_MaxTimerIdx, N_Cs );

    } else {    /* GDN_BUFREQ_E_NOT_OK */
        Gdn_CanTp_ChannelStatus[TxChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)TxN_AI, GDN_NTFRSLT_E_NOT_OK );
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_MinTimerTimeout                                  */
/* Description   | STmin/N_Cs_min/N_Br_minのタイムアウト処理                  */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TargetChannel : チャネル                              */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_MinTimerTimeout( Gdn_CanTp_ChannelType TargetChannel )
{
    switch ( Gdn_CanTp_ChannelStatus[TargetChannel] ) {
        case GDN_CANTP_RxDelayOVFL: /* FC.OVFLフレーム送信 */
            Gdn_CanTp_SendFCOVFL( Gdn_CanTp_NAIidx[TargetChannel] );
            break;

        case GDN_CANTP_RxDelayCTS:
            Gdn_CanTp_RxDataRetry( TargetChannel );
            break;

        case GDN_CANTP_TxDelayCF:   /* CFフレーム送信 */
            Gdn_CanTp_SendCF( Gdn_CanTp_NAIidx[TargetChannel] );
            break;

        case GDN_CANTP_TxGetDelay:
            Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_TxGetNoDelay;
            break;

        default:    /* 他の状態では、MINタイマの発火がない */
            break;
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_MaxTimerTimeout                                  */
/* Description   | N_As,Bs,Cs/N_Ar,Br,Crのタイムアウト処理                    */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) TargetChannel : チャネル                              */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_MaxTimerTimeout( Gdn_CanTp_ChannelType TargetChannel )
{
    gdn_uint8                         N_AI;
    gdn_uint8                         TxN_AI;
    Gdn_CanTp_StatusType              DetailStatus;
    GdnConst Gdn_CanTp_RxNAIInfoType* RxN_AIInfo;
    GdnConst Gdn_CanTp_TxNAIInfoType* TxN_AIInfo;
    Gdn_PduIdType                     SduId;
    Gdn_PduIdType                     PduId;

    N_AI         = Gdn_CanTp_NAIidx[TargetChannel];
    DetailStatus = Gdn_CanTp_ChannelStatus[TargetChannel];

    if ( ( DetailStatus == GDN_CANTP_RxSendOVFL ) ||
         ( DetailStatus == GDN_CANTP_RxSendWT   ) ||
         ( DetailStatus == GDN_CANTP_RxSendCTS  ) ) {           /* N_Ar */
        RxN_AIInfo = &gdn_cantp_RxNAIInformation[N_AI];
        TxN_AI     = RxN_AIInfo->TxN_AIidx;
        TxN_AIInfo = &gdn_cantp_TxNAIInformation[TxN_AI];
        PduId = TxN_AIInfo->PduId;
        (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
        Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_Idle;
        if ( DetailStatus != GDN_CANTP_RxSendOVFL ) {
            SduId = RxN_AIInfo->SduId;
            Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_TIMEOUT_A );
        }   /* FC.OVFL送信失敗は上位層に通知しない */

    } else if ( ( DetailStatus == GDN_CANTP_RxDelayCTS ) ||
                ( DetailStatus == GDN_CANTP_RxBusy     ) ) {    /* N_Br */
        Gdn_CanTp_SendFCWT( N_AI );

    } else if ( DetailStatus == GDN_CANTP_RxWaitCF ) {          /* N_Cr */
        Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_Idle;
        SduId = gdn_cantp_RxNAIInformation[N_AI].SduId;
        Gdn_PduR_CanTpRxIndication( SduId, GDN_NTFRSLT_E_TIMEOUT_CR );

    } else if ( ( DetailStatus == GDN_CANTP_TxSendSF ) ||
                ( DetailStatus == GDN_CANTP_TxSendFF ) ||
                ( DetailStatus == GDN_CANTP_TxSendCF ) ) {      /* N_As */
        PduId = gdn_cantp_TxNAIInformation[N_AI].PduId;
        (void)Gdn_CanIf_CancelTransmit( PduId );    /* No need to check return value */
        Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)N_AI, GDN_NTFRSLT_E_TIMEOUT_A );

    } else if ( ( DetailStatus == GDN_CANTP_TxWaitFC1 ) ||
                ( DetailStatus == GDN_CANTP_TxWaitFCx ) ) {     /* N_Bs */
        Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)N_AI, GDN_NTFRSLT_E_TIMEOUT_BS );

    } else if ( ( DetailStatus == GDN_CANTP_TxDelayCF    ) ||
                ( DetailStatus == GDN_CANTP_TxGetDelay   ) ||
                ( DetailStatus == GDN_CANTP_TxGetNoDelay ) ) {  /* N_Cs */
        Gdn_CanTp_ChannelStatus[TargetChannel] = GDN_CANTP_Idle;
        Gdn_PduR_CanTpTxConfirmation( (Gdn_PduIdType)N_AI, GDN_NTFRSLT_E_NOT_OK );

    } else {    /* GDN_CANTP_Idle / GDN_CANTP_RxDelayOVFL */
    }
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_SetTimer                                         */
/* Description   | タイマ設定処理                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) SetChannel   : チャネル                               */
/*               | (in) TimerIdx     : タイマIdx                              */
/*               | (in) TimeoutValue : タイムアウト閾値                       */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_SetTimer( Gdn_CanTp_ChannelType SetChannel,
                                gdn_uint8             TimerIdx,
                                Gdn_TimeoutValueType  TimeoutValue )
{
    gdn_uint8       LocalSynchronizer;
    gdn_uint16      GlobalSynchronizer;
    Gdn_TimerIdType TimerId;

    LocalSynchronizer = Gdn_CanTp_Synchronizer[SetChannel][TimerIdx];
    if ( LocalSynchronizer < GDN_CANTP_UINT8_MAX ) {
        LocalSynchronizer++;
    } else {
        LocalSynchronizer = 0U;
    }

    GlobalSynchronizer = ((uint16)SetChannel << GDN_CANTP_Shift1Byte) | ((gdn_uint16)LocalSynchronizer);

    Gdn_CanTp_Synchronizer[SetChannel][TimerIdx] = LocalSynchronizer;

    TimerId = gdn_cantp_TimerId[SetChannel][TimerIdx];
    Gdn_TmrSrv_SetTimer( TimerId, TimeoutValue, GlobalSynchronizer );
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_ReleaseTimer                                     */
/* Description   | タイマ解除処理                                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) SetChannel   : チャネル                               */
/*               | (in) TimerIdx     : タイマIdx                              */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_ReleaseTimer( Gdn_CanTp_ChannelType SetChannel,
                                    gdn_uint8             TimerIdx )
{
    Gdn_TimerIdType   TimerId;

    TimerId = gdn_cantp_TimerId[SetChannel][TimerIdx];
    Gdn_TmrSrv_ReleaseTimer( TimerId );
}

/******************************************************************************/
/* Function Name | Gdn_CanTp_UseNewParameter                                  */
/* Description   | FC.CTS受信時のBS,STmin設定処理                             */
/* Re-entrancy   | Non Reentrant                                              */
/* Parameters    | (in) RxChannel : 受信チャネル                              */
/*               | (in) TxBS      : FC.CTSの指定BS                            */
/*               | (in) TxSTmin   : FC.CTSの指定STmin                         */
/* Return Value  | なし                                                       */
/* Notes         | Pre-conditions / related modules / other concern           */
/******************************************************************************/
static void Gdn_CanTp_UseNewParameter( Gdn_CanTp_ChannelType   RxChannel,
                                       Gdn_CanTp_BlockSizeType TxBS,
                                       Gdn_CanTp_STminType     TxSTmin )
{
#if ( GDN_CANTP_ParameterPattern == GDN_CANTP_FixedPar )    /* 固定BS/STmin使用 */

    Gdn_CanTp_BlockSize[RxChannel] = (Gdn_CanTp_BlockSizeType)GDN_CANTP_BSFixedValue;
    Gdn_CanTp_STmin[RxChannel]     = (Gdn_CanTp_STminType)GDN_CANTP_STminFixedValue;

#else

  #if ( GDN_CANTP_ParameterPattern != GDN_CANTP_LatestPar ) /* 初回BS/STmin使用 */
    Gdn_CanTp_StatusType DetailStatus;
    DetailStatus = Gdn_CanTp_ChannelStatus[RxChannel];

    if ( DetailStatus == GDN_CANTP_TxWaitFC1 )  /* 初回FC.CTS受信 */
  #endif
    {
        Gdn_CanTp_BlockSize[RxChannel] = TxBS;

        if ( TxSTmin <= GDN_CANTP_STminMaxValue ) {             /* 0～127ms   */
            Gdn_CanTp_STmin[RxChannel] = TxSTmin;

  #if ( GDN_CANTP_STminFailPattern != GDN_CANTP_FailSafeMax )   /* 1msでF/S   */
        } else if ( ( TxSTmin >= GDN_CANTP_STminMicroMin ) &&
                    ( TxSTmin <= GDN_CANTP_STminMicroMax ) ) {  /* 0.1～0.9ms */
            Gdn_CanTp_STmin[RxChannel] = GDN_CANTP_STmin1ms;    /* 1ms        */
  #endif

        } else {                                                /* Reserved   */
            Gdn_CanTp_STmin[RxChannel] = GDN_CANTP_STminMaxValue;
        }
    }

#endif
}

#define GDN_CANTP_STOP_SEC_CODE
#include <Gdn_CanTp_MemMap.h>

/**** End of File *************************************************************/
