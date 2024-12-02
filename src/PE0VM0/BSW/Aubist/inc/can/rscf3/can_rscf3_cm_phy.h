/* can_rscf3_cm_phy_h_m10700_v2-2-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3/CM/PHYSICAL/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CAN_RSCF3_CM_PHY_H
#define CAN_RSCF3_CM_PHY_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define CAN_u4BIT_NONE                  (0x00000000UL)      /* bit なし(uint32)                         */
#define CAN_u4BIT0                      (0x00000001UL)      /* bit 0(uint32)                            */
#define CAN_u4BIT31                     (0x80000000UL)      /* bit 31                                   */

#define CAN_SFT_0                       (0U)                /* シフト値 0                               */
#define CAN_SFT_1                       (1U)                /* シフト値 1                               */
#define CAN_SFT_2                       (2U)                /* シフト値 2                               */
#define CAN_SFT_3                       (3U)                /* シフト値 3                               */
#define CAN_SFT_4                       (4U)                /* シフト値 4                               */
#define CAN_SFT_5                       (5U)                /* シフト値 5                               */
#define CAN_SFT_6                       (6U)                /* シフト値 6                               */
#define CAN_SFT_7                       (7U)                /* シフト値 7                               */
#define CAN_SFT_8                       (8U)                /* シフト値 8                               */
#define CAN_SFT_9                       (9U)                /* シフト値 9                               */
#define CAN_SFT_10                      (10U)               /* シフト値 10                              */
#define CAN_SFT_11                      (11U)               /* シフト値 11                              */
#define CAN_SFT_12                      (12U)               /* シフト値 12                              */
#define CAN_SFT_13                      (13U)               /* シフト値 13                              */
#define CAN_SFT_14                      (14U)               /* シフト値 14                              */
#define CAN_SFT_15                      (15U)               /* シフト値 15                              */
#define CAN_SFT_16                      (16U)               /* シフト値 16                              */
#define CAN_SFT_17                      (17U)               /* シフト値 17                              */
#define CAN_SFT_18                      (18U)               /* シフト値 18                              */
#define CAN_SFT_19                      (19U)               /* シフト値 19                              */
#define CAN_SFT_20                      (20U)               /* シフト値 20                              */
#define CAN_SFT_21                      (21U)               /* シフト値 21                              */
#define CAN_SFT_22                      (22U)               /* シフト値 22                              */
#define CAN_SFT_23                      (23U)               /* シフト値 23                              */
#define CAN_SFT_24                      (24U)               /* シフト値 24                              */
#define CAN_SFT_25                      (25U)               /* シフト値 25                              */
#define CAN_SFT_26                      (26U)               /* シフト値 26                              */
#define CAN_SFT_27                      (27U)               /* シフト値 27                              */
#define CAN_SFT_28                      (28U)               /* シフト値 28                              */
#define CAN_SFT_29                      (29U)               /* シフト値 29                              */
#define CAN_SFT_30                      (30U)               /* シフト値 30                              */
#define CAN_SFT_31                      (31U)               /* シフト値 31                              */

#define CAN_MBSFT_MSK                   (0x1FU)             /* MBOX番号に対応した32Bit列ビット位置変換用マスク */

#define CAN_CLK_CLKC                    (0U)                /* クロックソース：clkc                     */
#define CAN_CLK_XINCAN                  (1U)                /* クロックソース：clk_xincan               */

#define CAN_PAYLOAD_OVERFLOW_STORED     (0U)                /* ペイロードオーバフローモード：バッファサイズを超える分のペイロードは切り捨てて格納する */
#define CAN_PAYLOAD_OVERFLOW_NOTSTORED  (1U)                /* ペイロードオーバフローモード：格納せず破棄する                                         */

#define CAN_NUM_FIFO_RCV                (8U)                /* 受信FIFO数                               */
#define CAN_NUM_BUF_SND_PER_CH          (32U)               /* 送信バッファ数/1チャネル                 */

#define CAN_NUM_RULETABLE_PAGE_CH       (8U)                /* 受信ルールページ数/1チャネル             */
#define CAN_NUM_RULETABLE_PER_PAGE      (16U)               /* 受信ルール数/1ページ                     */
#define CAN_NUM_RULETABLE_PER_PAGE_MSK  (0x0FU)             /* 受信ルール数用マスク値                   */
#define CAN_NUM_RULETABLE_PER_PAGE_SFT  (0x4U)              /* 受信ルール数用シフト値                   */

#define CAN_TRX_FIFO_0                  (0U)                /* 送受信FIFO0                              */
#define CAN_TRX_FIFO_1                  (1U)                /* 送受信FIFO1                              */
#define CAN_TRX_FIFO_2                  (2U)                /* 送受信FIFO2                              */
#define CAN_TRX_FIFO_FOR_RX             (2U)                /* 受信で使用する送受信FIFO数               */

#define CAN_CFTYPE_RX_INT               (CAN_TRX_FIFO_0)    /* 割り込み受信で使用する送受信FIFOのNo     */
#define CAN_CFTYPE_RX_POLL              (CAN_TRX_FIFO_1)    /* ポーリング受信で使用する送受信FIFOのNo   */

#define CAN_GMODE_RST2STP_CYCLE         (3U)                /* GlobalResetModeからGlobalStopModeへの最大遷移時間(pclk)           */
#define CAN_GMODE_RST2TST_CYCLE         (10U)               /* GlobalResetModeからGlobalTestModeへの最大遷移時間(pclk)           */
#define CAN_GMODE_RST2COM_CYCLE         (10U)               /* GlobalResetModeからGlobalOperatingModeへの最大遷移時間(pclk)      */
#define CAN_CMODE_RST2STP_CYCLE         (3U)                /* ChannelRestModeからChannelStopModeへの最大遷移時間(pclk)          */

#define CAN_GMODE_ANY2RST_BITTIME       (2U)                /* GlobalRestModeへの最大遷移時間(bit time)                          */
#define CAN_CMODE_RST2COM_BITTIME       (4U)                /* ChannelRestModeからChannelOperatingModeへの最大遷移時間(bit time) */
#define CAN_CMODE_ANY2RST_BITTIME       (2U)                /* ChannelRestModeへの最大遷移時間(bit time)                         */

#define CAN_RAMCHK_MASK_LOWERHALFBYTE   (0x0FU)             /* 1byteRAMチェック用マスク値               */
#define CAN_RAMCHK_VALUE_LOWERHALFBYTE  (0x0FU)             /* 1byteRAMチェック用期待値                 */

#define CAN_USER_BAUDRATE               (CAN_TB_USER_BAUDRATE )        /* ボーレート：ユーザボーレート              */
#define CAN_125KBPS_2M_PTN1             (CAN_TB_125K_2M_PTN1  )        /* ボーレート：125kbps_2M  ：パターン1       */
#define CAN_125KBPS_2P5M_PTN1           (CAN_TB_125K_2P5M_PTN1)        /* ボーレート：125kbps_2.5M：パターン1       */
#define CAN_250KBPS_4M_PTN1             (CAN_TB_250K_4M_PTN1  )        /* ボーレート：250kbps_4M  ：パターン1       */
#define CAN_250KBPS_4M_PTN2             (CAN_TB_250K_4M_PTN2  )        /* ボーレート：250kbps_4M  ：パターン2       */
#define CAN_250KBPS_5M_PTN1             (CAN_TB_250K_5M_PTN1  )        /* ボーレート：250kbps_5M  ：パターン1       */
#define CAN_250KBPS_5M_PTN2             (CAN_TB_250K_5M_PTN2  )        /* ボーレート：250kbps_5M  ：パターン2       */
#define CAN_500KBPS_8M_PTN1             (CAN_TB_500K_8M_PTN1  )        /* ボーレート：500kbps_8M  ：パターン1       */
#define CAN_500KBPS_8M_PTN2             (CAN_TB_500K_8M_PTN2  )        /* ボーレート：500kbps_8M  ：パターン2       */
#define CAN_500KBPS_8M_PTN3             (CAN_TB_500K_8M_PTN3  )        /* ボーレート：500kbps_8M  ：パターン3       */
#define CAN_500KBPS_8M_PTN4             (CAN_TB_500K_8M_PTN4  )        /* ボーレート：500kbps_8M  ：パターン4       */
#define CAN_500KBPS_8M_PTN5             (CAN_TB_500K_8M_PTN5  )        /* ボーレート：500kbps_8M  ：パターン5       */
#define CAN_500KBPS_10M_PTN1            (CAN_TB_500K_10M_PTN1 )        /* ボーレート：500kbps_10M ：パターン1       */
#define CAN_500KBPS_10M_PTN2            (CAN_TB_500K_10M_PTN2 )        /* ボーレート：500kbps_10M ：パターン2       */
#define CAN_500KBPS_10M_PTN3            (CAN_TB_500K_10M_PTN3 )        /* ボーレート：500kbps_10M ：パターン3       */
#define CAN_500KBPS_10M_PTN4            (CAN_TB_500K_10M_PTN4 )        /* ボーレート：500kbps_10M ：パターン4       */
#define CAN_500KBPS_10M_PTN5            (CAN_TB_500K_10M_PTN5 )        /* ボーレート：500kbps_10M ：パターン5       */
#define CAN_500KBPS_20M_PTN1            (CAN_TB_500K_20M_PTN1 )        /* ボーレート：500kbps_20M ：パターン1       */
#define CAN_500KBPS_32M_PTN1            (CAN_TB_500K_32M_PTN1 )        /* ボーレート：500kbps_32M ：パターン1       */
#define CAN_500KBPS_40M_PTN1            (CAN_TB_500K_40M_PTN1 )        /* ボーレート：500kbps_40M ：パターン1       */
#define CAN_500KBPS_40M_PTN2            (CAN_TB_500K_40M_PTN2 )        /* ボーレート：500kbps_40M ：パターン2       */
#define CAN_500KBPS_80M_PTN1            (CAN_TB_500K_80M_PTN1 )        /* ボーレート：500kbps_80M ：パターン1       */

#define CAN_USER_DATABAUDRATE           (CAN_TB_USER_DATABAUDRATE)     /* データボーレート：ユーザボーレート        */
#define CAN_DB_125KBPS_2M_PTN1          (CAN_TB_DB_125K_2M_PTN1  )     /* データボーレート：125kbps_2M  ：パターン1 */
#define CAN_DB_125KBPS_2P5M_PTN1        (CAN_TB_DB_125K_2P5M_PTN1)     /* データボーレート：125kbps_2.5M：パターン1 */
#define CAN_DB_250KBPS_4M_PTN1          (CAN_TB_DB_250K_4M_PTN1  )     /* データボーレート：250kbps_4M  ：パターン1 */
#define CAN_DB_250KBPS_4M_PTN2          (CAN_TB_DB_250K_4M_PTN2  )     /* データボーレート：250kbps_4M  ：パターン2 */
#define CAN_DB_250KBPS_5M_PTN1          (CAN_TB_DB_250K_5M_PTN1  )     /* データボーレート：250kbps_5M  ：パターン1 */
#define CAN_DB_250KBPS_5M_PTN2          (CAN_TB_DB_250K_5M_PTN2  )     /* データボーレート：250kbps_5M  ：パターン2 */
#define CAN_DB_500KBPS_8M_PTN1          (CAN_TB_DB_500K_8M_PTN1  )     /* データボーレート：500kbps_8M  ：パターン1 */
#define CAN_DB_500KBPS_8M_PTN2          (CAN_TB_DB_500K_8M_PTN2  )     /* データボーレート：500kbps_8M  ：パターン2 */
#define CAN_DB_500KBPS_8M_PTN3          (CAN_TB_DB_500K_8M_PTN3  )     /* データボーレート：500kbps_8M  ：パターン3 */
#define CAN_DB_500KBPS_8M_PTN4          (CAN_TB_DB_500K_8M_PTN4  )     /* データボーレート：500kbps_8M  ：パターン4 */
#define CAN_DB_500KBPS_8M_PTN5          (CAN_TB_DB_500K_8M_PTN5  )     /* データボーレート：500kbps_8M  ：パターン5 */
#define CAN_DB_500KBPS_10M_PTN1         (CAN_TB_DB_500K_10M_PTN1 )     /* データボーレート：500kbps_10M ：パターン1 */
#define CAN_DB_500KBPS_10M_PTN2         (CAN_TB_DB_500K_10M_PTN2 )     /* データボーレート：500kbps_10M ：パターン2 */
#define CAN_DB_500KBPS_10M_PTN3         (CAN_TB_DB_500K_10M_PTN3 )     /* データボーレート：500kbps_10M ：パターン3 */
#define CAN_DB_500KBPS_10M_PTN4         (CAN_TB_DB_500K_10M_PTN4 )     /* データボーレート：500kbps_10M ：パターン4 */
#define CAN_DB_500KBPS_10M_PTN5         (CAN_TB_DB_500K_10M_PTN5 )     /* データボーレート：500kbps_10M ：パターン5 */
#define CAN_DB_500KBPS_20M_PTN1         (CAN_TB_DB_500K_20M_PTN1 )     /* データボーレート：500kbps_20M ：パターン1 */
#define CAN_DB_500KBPS_32M_PTN1         (CAN_TB_DB_500K_32M_PTN1 )     /* データボーレート：500kbps_32M ：パターン1 */
#define CAN_DB_500KBPS_40M_PTN1         (CAN_TB_DB_500K_40M_PTN1 )     /* データボーレート：500kbps_40M ：パターン1 */
#define CAN_DB_500KBPS_40M_PTN2         (CAN_TB_DB_500K_40M_PTN2 )     /* データボーレート：500kbps_40M ：パターン2 */
#define CAN_DB_500KBPS_80M_PTN1         (CAN_TB_DB_500K_80M_PTN1 )     /* データボーレート：500kbps_80M ：パターン1 */
#define CAN_DB_2MBPS_20M_PTN1           (CAN_TB_DB_2M_20M_PTN1   )     /* データボーレート：2Mbps_20M   ：パターン1 */
#define CAN_DB_2MBPS_32M_PTN1           (CAN_TB_DB_2M_32M_PTN1   )     /* データボーレート：2Mbps_32M   ：パターン1 */
#define CAN_DB_2MBPS_40M_PTN1           (CAN_TB_DB_2M_40M_PTN1   )     /* データボーレート：2Mbps_40M   ：パターン1 */
#define CAN_DB_2MBPS_40M_PTN2           (CAN_TB_DB_2M_40M_PTN2   )     /* データボーレート：2Mbps_40M   ：パターン2 */
#define CAN_DB_2MBPS_80M_PTN1           (CAN_TB_DB_2M_80M_PTN1   )     /* データボーレート：2Mbps_80M   ：パターン1 */

#define CAN_BAUDRATEINFO_1_1            (CAN_TB_SSPOFFSET_NOUSE      ) /* SSPオフセット値：使用しない               */
#define CAN_BAUDRATEINFO_1_2            (CAN_TB_SSPOFFSET_2M_20M_PTN1) /* SSPオフセット値：2Mbps_20M：パターン1     */
#define CAN_BAUDRATEINFO_1_3            (CAN_TB_SSPOFFSET_2M_32M_PTN1) /* SSPオフセット値：2Mbps_32M：パターン1     */
#define CAN_BAUDRATEINFO_1_4            (CAN_TB_SSPOFFSET_2M_40M_PTN1) /* SSPオフセット値：2Mbps_40M：パターン1     */
#define CAN_BAUDRATEINFO_1_5            (CAN_TB_SSPOFFSET_2M_40M_PTN2) /* SSPオフセット値：2Mbps_40M：パターン2     */
#define CAN_BAUDRATEINFO_1_6            (CAN_TB_SSPOFFSET_2M_80M_PTN1) /* SSPオフセット値：2Mbps_80M：パターン1     */

#define CAN_BAUDRATEINFO_2_1            (CAN_NOUSE)         /* データボーレートスイッチ：使用しない     */
#define CAN_BAUDRATEINFO_2_2            (CAN_USE  )         /* データボーレートスイッチ：使用する       */

#define CAN_BAUDRATEINFO_3_1            (0x00000000UL)      /* ボーレート情報3：未使用                  */


/*======================================*/
/* レジスタ初期値マクロ                 */
/*======================================*/
#define CAN_u4CMNCFG_INIT               (0x00000000UL)      /* 初期値 CmNCFG                            */
#define CAN_u4CMCTR_INIT                (0x00000001UL)      /* 初期値 CmCTR                             */
#define CAN_u4GCFG_INIT                 (0x00000000UL)      /* 初期値 GCFG                              */
#define CAN_u4GCTR_INIT                 (0x00000000UL)      /* 初期値 GCTR                              */
#define CAN_u4GFDCFG_INIT               (0x00000000UL)      /* 初期値 GFDCFG                            */
#define CAN_u4GAFLCFG0_INIT             (0x00000000UL)      /* 初期値 GAFLCFG0                          */
#define CAN_u4GAFLCFG1_INIT             (0x00000000UL)      /* 初期値 GAFLCFG1                          */
#define CAN_u4GAFLIDJ_INIT              (0xFFFFFFFFUL)      /* 初期値 GAFLIDj                           */
#define CAN_u4GAFLMJ_INIT               (0xDFFFFFFFUL)      /* 初期値 GAFLMj                            */
#define CAN_u4GAFLP0J_INIT              (0x00000000UL)      /* 初期値 GAFLP0_j                          */
#define CAN_u4GAFLP1J_INIT              (0x00000000UL)      /* 初期値 GAFLP1_j                          */
#define CAN_u4RMNB_INIT                 (0x00000000UL)      /* 初期値 RMNB                              */
#define CAN_u4RFCCX_INIT                (0x00000000UL)      /* 初期値 RFCCx                             */
#define CAN_u4CFCCK_INIT                (0x00000000UL)      /* 初期値 CFCCk                             */
#define CAN_u4TMIDP_INIT                (0x9FFFFFFFUL)      /* 初期値 TMIDp                             */
#define CAN_u4TMIECM_INIT               (0x00000000UL)      /* 初期値 TMIECm                            */
#define CAN_u4TXQCCM_INIT               (0x00000000UL)      /* 初期値 TXQCCm                            */
#define CAN_u4THLCCM_INIT               (0x00000000UL)      /* 初期値 THLCCm                            */
#define CAN_u4CDTCT_INIT                (0x00000000UL)      /* 初期値 CDTCT                             */
#define CAN_u4CMDCFG_INIT               (0x00000000UL)      /* 初期値 CmDCFG                            */
#define CAN_u4CMFDCFG_INIT              (0x00000000UL)      /* 初期値 CmFDCFG                           */


/*======================================*/
/* レジスタ操作用マクロ                 */
/*======================================*/
#define CAN_u4CMCTR_CHMDC_COMM_SET      (0x00000000UL)      /* チャネル通信モード設定                   */
#define CAN_u4CMCTR_CHMDC_RESET_SET     (0x00000001UL)      /* チャネルリセットモード設定               */
#define CAN_u4CMCTR_CSLPR_STOP_SET      (0x00000004UL)      /* チャネルストップモード設定               */

#define CAN_u4CMSTS_CMODE_COMM          (0x00000000UL)      /* チャネル通信モード                       */
#define CAN_u4CMSTS_CMODE_RESET         (0x00000001UL)      /* チャネルリセットモード                   */
#define CAN_u4CMSTS_CMODE_STOP          (0x00000004UL)      /* チャネルストップモード                   */

#define CAN_u4CMERFL_CLEARALL           (0x00000000UL)      /* CmERFLレジスタクリア                     */
#define CAN_u4CMERFL_BOEF_BUSOFF        (0x00000008UL)      /* バスオフ検出                             */
#define CAN_u4CMERFL_BOEF_CLR           (0x00007FF7UL)      /* バスオフ開始フラグクリア                 */

#define CAN_u4CMFDCFG_TDCE_SET          (0x00000200UL)      /* 送信遅延補正許可ビット設定               */
#define CAN_u4CMFDCFG_TDCE_CLR          (0xFFFFFDFFUL)      /* 送信遅延補正許可ビットクリア             */

#define CAN_u4CMFDSTS_CLEARALL          (0x00000000UL)      /* CmFDSTSレジスタクリア                    */

#define CAN_u4GCTR_TSRST_RESET          (0x00010000UL)      /* タイムスタンプカウンタリセット           */
#define CAN_u4GCTR_GMDC_COMM_SET        (0x00000000UL)      /* グローバル動作モード設定                 */
#define CAN_u4GCTR_GMDC_RESET_SET       (0x00000001UL)      /* グローバルリセットモード設定             */
#define CAN_u4GCTR_GMDC_TEST_SET        (0x00000002UL)      /* グローバルテストモード設定               */
#define CAN_u4GCTR_GSLPR_STOP_SET       (0x00000004UL)      /* グローバルストップモード設定             */

#define CAN_u4GSTS_GMODE_COMM           (0x00000000UL)      /* グローバル動作モード                     */
#define CAN_u4GSTS_GMODE_RESET          (0x00000001UL)      /* グローバルリセットモード                 */
#define CAN_u4GSTS_GMODE_TEST           (0x00000002UL)      /* グローバルテストモード                   */
#define CAN_u4GSTS_GMODE_STOP           (0x00000005UL)      /* グローバルストップモード                 */
#define CAN_u4GSTS_GRAMINIT             (0x00000008UL)      /* CAN用RAMクリア中                         */

#define CAN_u4GERFL_CLEARALL            (0x00000000UL)      /* GERFLレジスタクリア                      */

#define CAN_u4GAFLECTR_AFLDAE_ENA       (0x00000100UL)      /* 受信ルールテーブル書き込み許可設定       */
#define CAN_u4GAFLECTR_AFLDAE_DIS       (0x00000000UL)      /* 受信ルールテーブル書き込み禁止設定       */

#define CAN_u4GAFLMJ_STDIDMSK_NOUSE     (0xC00007FFUL)      /* 標準ID,IDE,RTRビットを比較対象に設定     */
#define CAN_u4GAFLMJ_EXTIDMSK_NOUSE     (0xDFFFFFFFUL)      /* 拡張ID,IDE,RTRビットを比較対象に設定     */
#define CAN_u4GAFLMJ_GAFLIDEM_SET       (0x80000000UL)      /* IDEビットを比較対象に設定                */
#define CAN_u4GAFLMJ_GAFLRTRM_SET       (0x40000000UL)      /* RTRビットを比較対象に設定                */
#define CAN_u4RMNB_CLEARALL             (0x00000000UL)      /* RMNBレジスタクリア                       */

#define CAN_u4RFSTSX_CLEARALL           (0x00000001UL)      /* RFSTSxレジスタクリア                     */

#define CAN_u4CFCCK_CFRXIE_DIS          (0xFFFFFFFDUL)      /* 送受信FIFO受信割り込み禁止               */
#define CAN_u4CFCCK_CFE_NOUSE           (0xFFFFFFFEUL)      /* 送受信FIFO未使用                         */

#define CAN_u4CFSTSK_CLEARALL           (0x00000001UL)      /* CFSTSkレジスタクリア                     */
#define CAN_u4CFSTSK_CFTXIF_CLR         (0x0000000DUL)      /* 送受信FIFO送信割り込み要求フラグクリア   */
#define CAN_u4CFSTSK_CFRXIF_CLR         (0x00000015UL)      /* 送受信FIFO受信割り込み要求フラグクリア   */
#define CAN_u4CFSTSK_CFMLT_CLR          (0x00000019UL)      /* 送受信FIFOメッセージロストフラグクリア   */

#define CAN_u4CFFDCSTSK_CFFDF_CANFD     (0x00000004UL)      /* CAN FDフレーム設定                       */

#define CAN_u4CFPCTRK_CFPC_SET          (0x000000FFUL)      /* 送受信FIFOのリードポインタ移動           */

#define CAN_u1TMCP_TMTR_SET             ((uint8)0x01U)      /* 送信要求                                 */
#define CAN_u1TMCP_TMTAR_SET            ((uint8)0x02U)      /* 送信アボート要求                         */

#define CAN_u1TMSTSP_TXFREE             ((uint8)0x00U)      /* 送信可能状態                             */
#define CAN_u1TMSTSP_ABORTED            ((uint8)0x02U)      /* 送信アボート完了                         */
#define CAN_u1TMSTSP_TMTRF_CLR          ((uint8)0x00U)      /* 送信結果フラグクリア                     */

#define CAN_u4TMPTRP_CLEARALL           (0x00000000UL)      /* TMPTRpレジスタクリア                     */

#define CAN_u4TMFDCTRP_CLEARALL         (0x00000000UL)      /* TMFDCTRpレジスタクリア                   */
#define CAN_u4TMFDCTRP_FDF_CAN          (0x00000000UL)      /* クラシカルCANフレーム設定                */
#define CAN_u4TMFDCTRP_FDF_CANFD        (0x00000004UL)      /* CAN FDフレーム設定                       */
#define CAN_u4TMFDCTRP_BRS_OFF          (0x00000000UL)      /* データ領域のビットレートは変わらない     */
#define CAN_u4TMFDCTRP_BRS_ON           (0x00000002UL)      /* データ領域のビットレートは変わる         */
#define CAN_u4TMFDCTRP_ESI_E_ACT        (0x00000000UL)      /* ESIビットをエラーアクティブノード        */
#define CAN_u4TMFDCTRP_ESI_E_PCV        (0x00000001UL)      /* ESIビットをエラーパッシブノード          */

#define CAN_u4TMDFBP_CLEARALL           (0x00000000UL)      /* TMDFb_pレジスタクリア                    */

#define CAN_u4TXQSTSM_CLEARALL          (0x00000001UL)      /* TXQSTSmレジスタクリア                    */

#define CAN_u4THLSTSM_CLEARALL          (0x00000001UL)      /* THLSTSmレジスタクリア                    */

#define CAN_u4GTSTCFG_ICBCE_DIS         (0x00000000UL)      /* チャネル間通信テスト禁止                 */

#define CAN_u4GTSTCTR_RTME_ENA          (0x00000004UL)      /* RAMテスト許可                            */
#define CAN_u4GTSTCTR_RTME_DIS          (0x00000000UL)      /* RAMテスト禁止                            */
#define CAN_u4GTSTCTR_ICBCTME_DIS       (0x00000000UL)      /* チャネル間通信テスト禁止                 */

#define CAN_u4GLOCKK_LOCK_RELKEY1       (0x00007575UL)      /* テストモードのプロテクト解除データ1      */
#define CAN_u4GLOCKK_LOCK_RELKEY2       (0x00008A8AUL)      /* テストモードのプロテクト解除データ2      */


/*======================================*/
/* レジスタマスク用マクロ               */
/*======================================*/
#define CAN_u4CMSTS_MODEALL_MSK         (0x00000007UL)      /* CmSTSレジスタ    CSLPSTS,CHLTSTS,CRSTSTSマスク          */
#define CAN_u4CMERFL_BOEF_MSK           (0x00000008UL)      /* CmERFLレジスタ   BOEFマスク                             */
#define CAN_u4CMFDCFG_TDCO_MSK          (0x007F0000UL)      /* CmFDCFGレジスタ  TDCOビットマスク                       */
#define CAN_u4GSTS_GRAMINIT_MSK         (0x00000008UL)      /* GSTSレジスタ     GRAMINITマスク                         */
#define CAN_u4GSTS_MODEALL_MSK          (0x0000000FUL)      /* GSTSレジスタ     GRAMINIT,GSLPSTS,GHLTSTS,GRSTSTSマスク */
#define CAN_u4GAFLECTR_USEDBIT_MSK      (0x00000100UL)      /* GAFLECTRレジスタ 使用ビットマスク                       */
#define CAN_u4GAFLECTR_AFLPN_MSK        (0x0000003FUL)      /* GAFLECTRレジスタ AFLPNマスク                            */
#define CAN_u4GAFLMJ_GAFLIDM_STD_MSK    (0x000007FFUL)      /* GAFLMjレジスタ   GAFLIDMマスク(標準ID用)                */
#define CAN_u4GAFLMJ_GAFLIDM_EXT_MSK    (0x1FFFFFFFUL)      /* GAFLMjレジスタ   GAFLIDMマスク(拡張ID用)                */
#define CAN_u4CFSTSK_CFMC_MSK           (0x0000FF00UL)      /* CFSTSkレジスタ   CFMCマスク                             */
#define CAN_u4CFIDK_EID_MSK             (0x9FFFFFFFUL)      /* CFIDkレジスタ    CFIDE,CFIDマスク(拡張ID用)             */
#define CAN_u4CFPTRK_CFDLC_MSK          (0xF0000000UL)      /* CFPTRkレジスタ   CFDLCマスク                            */
#define CAN_u4CFFDCSTSK_CFPTR_MSK       (0xFFFF0000UL)      /* CFFDCSTSkレジスタCFPTRマスク                            */
#define CAN_u4CDTCT_USEDBIT_MSK         (0x0000FFFFUL)      /* CDTCTレジスタ    使用ビットマスク                       */
#define CAN_u1TMSTSP_REQ_RES_MSK        ((uint8)0x1EU)      /* TMSTSpレジスタ   TMTARM,TMTRM,TMTRFマスク               */
#define CAN_u4TMIDP_SID_MSK             (0x000007FFUL)      /* TMIDpレジスタ    TMIDマスク(標準ID用)                   */
#define CAN_u4TMIDP_EID_MSK             (0x9FFFFFFFUL)      /* TMIDpレジスタ    TMID,TMIDEマスク(拡張ID用)             */
#define CAN_u4TXQCCM_USEDBIT_MSK        (0x00001FA1UL)      /* TXQCCmレジスタ   使用ビットマスク                       */
#define CAN_u4THLCCM_USEDBIT_MSK        (0x00000701UL)      /* THLCCmレジスタ   使用ビットマスク                       */
#define CAN_u4GTSTCFG_USEDBIT_MSK       (0x000000FFUL)      /* GTSTCFGレジスタ  使用ビットマスク                       */
#define CAN_u4GTSTCFG_RTMPS_MSK         (0x01FF0000UL)      /* GTSTCFGレジスタ  RTMPSマスク                            */
#define CAN_u4GTSTCTR_USEDBIT_MSK       (0x00000005UL)      /* GTSTCTRレジスタ  使用ビットマスク                       */
#define CAN_u4GTSTCTR_RTME_MSK          (0x00000004UL)      /* GTSTCTRレジスタ  RTMEマスク                             */
#define CAN_u4RMNB_USEDBIT_MSK          (0x000007FFUL)      /* RMNBレジスタ     使用ビットマスク                       */
#define CAN_u4CFCCK_USEDBIT_MSK         (0xFFFFFF77UL)      /* CFCCkレジスタ    使用ビットマスク                       */
#define CAN_u4CFCCK_GCHKBIT_MSK         (0x00FFF370UL)      /* CFCCkレジスタ    グローバルレジスタチェック用マスク     */
#define CAN_u4CFFDCSTSK_CFFDF_MSK       (0x00000004UL)      /* CFFDCSTSレジスタ CFFDFマスク                            */
#define CAN_u4CMCTR_USEDBIT_MSK         (0xC7EFFF0FUL)      /* CmCTRレジスタ    使用ビットマスク                       */
#define CAN_u4CMCTR_MODEALL_MSK         (0x00000007UL)      /* CmCTRレジスタ    CSLPR,CHMDCマスク                      */
#define CAN_u4GCFG_USEDBIT_MSK          (0x0000003FUL)      /* GCFGレジスタ     使用ビットマスク                       */
#define CAN_u4GCFG_DCS_MSK              (0x00000010UL)      /* GCFGレジスタ     DCSマスク                              */
#define CAN_u4GCTR_USEDBIT_MSK          (0x00000F07UL)      /* GCTRレジスタ     使用ビットマスク                       */
#define CAN_u4GFDCFG_USEDBIT_MSK        (0x00000001UL)      /* GFDCFGレジスタ   使用ビットマスク                       */


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


#endif  /* CAN_RSCF3_CM_PHY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-1-1         :2019/08/07                                              */
/*  v2-1-2         :2019/10/10                                              */
/*  v2-2-0         :2020/02/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
