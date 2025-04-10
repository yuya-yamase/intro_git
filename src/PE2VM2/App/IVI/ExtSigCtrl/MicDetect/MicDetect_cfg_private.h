/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Mic Power Control & Detection Specification (26CDC)                                                                              */
/*===================================================================================================================================*/

#ifndef MIC_DETECT_PRIVATE_H
#define MIC_DETECT_PRIVATE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MIC_DETECT_CFG_PRIVATE_H_MAJOR          (0)
#define MIC_DETECT_CFG_PRIVATE_H_MINOR          (0)
#define MIC_DETECT_CFG_PRIVATE_H_PATCH          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "MicDetect.h"

#include "Dio.h"
#include "iohw_adc_channel.h"

#include "x_spi_ivi_sub1_system.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 通知関数 */
#define u1_MICDETECT_XSPISEND_MIC(x)            (vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_MIC, (x)))
#define u1_MICDETECT_XSPISEND_MIC2(x)           (vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_MIC2, (x)))
#define u1_MICDETECT_XSPISEND_MIC3(x)           (vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_MIC3, (x)))
#define u1_MICDETECT_XSPISEND_MIC4(x)           (vd_g_XspiIviSub1ExtSgnlPut((U1)XSPI_IVI_EXTSIG_MIC4, (x)))

/* Port */
/* MIC-ON端子 */
#define MICDETECT_PORT_MIC_ON                   (DIO_ID_PORT11_CH13)
#define MICDETECT_PORT_MIC_DET                  (ADC_CH_MIC)
#define MICDETECT_PORT_MIC2_DET                 (ADC_CH_MIC2)
#define MICDETECT_PORT_MIC3_DET                 (ADC_CH_MIC3)
#define MICDETECT_PORT_MIC4_DET                 (ADC_CH_MIC4)

/* 車両信号制御トリガbit定義 */
#define MICDETECT_TRG_INIT                      (0x00U)     /* 初期状態 */
#define MICDETECT_TRG_MIC_ON_BIT                (0x01U)     /* 0bit:MIC-ON関連トリガbit */
#define MICDETECT_END_TRG_NON                   (0xFFU)     /* 終了トリガ無し(システムOFFでのみ終了) */

/* 車両信号トリガID定義 */
#define MICDETECT_TRG_NUM                       (1U)        /* トリガ総数 */
#define MICDETECT_TRG_MIC_ON                    (0U)        /* DIO端子：MIC-ON */

/* マイク入力AD閾値 */
#define MICDETECT_AD_PWRFAULT                   (0x0A21U)    /* AD天絡判定閾値   */
#define MICDETECT_AD_BORDER                     (0x0054U)    /* AD接続判定閾値   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* 車両信号ステータステーブル */
typedef struct  {
    const   U1                          u1_STRTIM;                                              /* 開始待ち時間 */
    void    (* const                    fp_vd_STADR)(const U1 u1_a_KIND);                       /* 開始処理関数アドレス */
    const   U1                          u1_CYCTIM;                                              /* 定周期時間 */
    void    (* const                    fp_vd_CYCADR)(const U1 u1_a_KIND);                      /* 定周期処理関数アドレス */
    void    (* const                    fp_vd_EDADR)(const U1 u1_a_KIND);                       /* 終了処理関数アドレス */
    const   U1                          u1_SAME_CNT_NUM;                                        /* 同一論理判定確定回数 */
    const   U1                          u1_STRTRG;                                              /* 制御開始トリガ */
    const   U1                          u1_ENDTRG;                                              /* 制御終了トリガ */
    void    (* const                    fp_vd_SNDADR)(const U1 u1_a_ID, const U1 u1_a_DATA);    /* データ送信関数アドレス */
    void    (* const                    fp_vd_CTLTMNLADR)(void);                                /* 端子制御関数アドレス */
} ST_MICDETECT_STS;

/* トリガカウント値テーブル */
typedef struct {
    U1                                  u1_trmnl_no;                                            /* トリガ処理対象端子 */
    U1                                  u1_timcnt;                                              /* トリガタイマ値 */
} ST_MICDETECT_TRG_CNT_STS;

/* トリガテーブル */
typedef struct {
    const ST_MICDETECT_TRG_CNT_STS *    stp_MSGTBL;                                             /* トリガカウントテーブル */
    U1                                  u1_trgbit;                                              /* トリガビット */
    U1                                  u1_trgtbl_max;                                          /* トリガカウントテーブルサイズ */
} ST_MICDETECT_TRG_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_MicDetect_MicStr(const U1 u1_a_kind);
void            vd_g_MicDetect_Cyc(const U1 u1_a_KIND);
void            vd_g_MicDetect_MicEnd(const U1 u1_a_kind);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_MICDETECT_STS           st_gp_MICDETECT_STS[MICDETECT_KIND_NUM];
extern const U1                         u1_t_MICDETECT_CNVRT_ID[MICDETECT_KIND_NUM];

#endif /* MIC_DETECT_PRIVATE_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  MicDetect_cfg.c                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
