/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  MCU IVI I2C Read/Write                                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCU_IVI_I2C_CTRL_C_MAJOR                (0)
#define MCU_IVI_I2C_CTRL_C_MINOR                (0)
#define MCU_IVI_I2C_CTRL_C_PATCH                (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "gvif3tx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MCU_IVI_I2C_CTRL_C_MAJOR != MCU_IVI_I2C_CTRL_H_MAJOR) || \
     (MCU_IVI_I2C_CTRL_C_MINOR != MCU_IVI_I2C_CTRL_H_MINOR) || \
     (MCU_IVI_I2C_CTRL_C_PATCH != MCU_IVI_I2C_CTRL_H_PATCH))
#error "Mcu_I2c_Ctrl.c and Mcu_I2c_Ctrl.h : source and header files are inconsistent!"
#endif
#if ((MCU_IVI_I2C_CTRL_C_MAJOR != MCU_IVI_I2C_CTRL_PRIVATE_H_MAJOR) || \
     (MCU_IVI_I2C_CTRL_C_MINOR != MCU_IVI_I2C_CTRL_PRIVATE_H_MINOR) || \
     (MCU_IVI_I2C_CTRL_C_PATCH != MCU_IVI_I2C_CTRL_PRIVATE_H_PATCH))
#error "Mcu_I2c_Ctrl.c and Mcu_I2c_Ctrl_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* カウンタ最大値 */
#define MCU_SYS_COUNTTIME_FIN           (0xFFFFFFFFU)

#define MCU_WRINUM_I2C_READ             (2U)    /* レジスタ読出し処理 レジスタ書込み回数 */

/* I2C PDU TRx Ack Timeout時間：各タスク20周期分 */
/* ToDo：FTRで全スレーブデバイス固定のTimeout時間に変更 or タイムカウント用にメインタスクを作成する */
#define MCU_I2C_TRX_TIMEOUT             (20U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Ack管理 */
static uint8    Mcu_I2c_Ack_Eizoic;             /* Video-IC : W 0x72, R 0x73 */
static uint8    Mcu_I2c_Ack_Gvif_Rx;            /* GVIF-Rx  : W 0x46, R 0x47 */
static uint8    Mcu_I2c_Ack_Gvif_Tx;            /* GVIF-Tx  : W 0x48, R 0x49 */
static uint8    Mcu_I2c_Ack_Power;              /* P-IC     : W 0xDE, R 0xDF */
static uint8    Mcu_I2c_Ack_Rtc;                /* RTC-IC   : W 0x64, R 0x65 */
static uint8    Mcu_I2c_Ack_Gyro;               /* Gryo     : W 0xD2, R 0xD3 */
static uint8    Mcu_I2c_Ack_G_Moni;             /* Gmoni    : W 0x32, R 0x33 */

static uint8 *  Mcu_I2c_Ack[MCU_I2C_ACK_NUM] = {
    &Mcu_I2c_Ack_Eizoic,
    &Mcu_I2c_Ack_Gvif_Rx,
    &Mcu_I2c_Ack_Gvif_Tx,
    &Mcu_I2c_Ack_Power,
    &Mcu_I2c_Ack_Rtc,
    &Mcu_I2c_Ack_Gyro,
    &Mcu_I2c_Ack_G_Moni
};

static U2   u2_s_I2cCtrl_AckCnt_Eizoic;          /* Video-IC : W 0x72, R 0x73 */
static U2   u2_s_I2cCtrl_AckCnt_Gvif_Rx;         /* GVIF-Rx  : W 0x46, R 0x47 */
static U2   u2_s_I2cCtrl_AckCnt_Gvif_Tx;         /* GVIF-Tx  : W 0x48, R 0x49 */
static U2   u2_s_I2cCtrl_AckCnt_Power;           /* P-IC     : W 0xDE, R 0xDF */
static U2   u2_s_I2cCtrl_AckCnt_Rtc;             /* RTC-IC   : W 0x64, R 0x65 */
static U2   u2_s_I2cCtrl_AckCnt_Gyro;            /* Gryo     : W 0xD2, R 0xD3 */
static U2   u2_s_I2cCtrl_AckCnt_G_Moni;          /* Gmoni    : W 0x32, R 0x33 */

static U2 * u2_s_I2cCtrl_AckCnt[MCU_I2C_ACK_NUM] = {
    &u2_s_I2cCtrl_AckCnt_Eizoic,
    &u2_s_I2cCtrl_AckCnt_Gvif_Rx,
    &u2_s_I2cCtrl_AckCnt_Gvif_Tx,
    &u2_s_I2cCtrl_AckCnt_Power,
    &u2_s_I2cCtrl_AckCnt_Rtc,
    &u2_s_I2cCtrl_AckCnt_Gyro,
    &u2_s_I2cCtrl_AckCnt_G_Moni
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static uint8 Mcu_Dev_I2c_Ctrl_AckChk_Wri(uint8 mcu_ack, uint16 * mcu_regstep, const uint16 mcu_wri_max, 
                                        const uint8 mcu_i2c_sla, const ST_REG_WRI_REQ * I2C_WR_REGSET, const uint32 mcu_timeout_cnt,
                                        uint16 * mcu_btwmtime_cnt);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_VideoIc
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : 映像IC Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Init(void)
{
    Mcu_I2c_Ack_Eizoic          = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_Gvif_Rx         = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_Gvif_Tx         = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_Power           = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_Rtc             = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_Gyro            = (uint8)MCU_REGWRI_ACK_INI;
    Mcu_I2c_Ack_G_Moni          = (uint8)MCU_REGWRI_ACK_INI;

    u2_s_I2cCtrl_AckCnt_Eizoic  = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_Gvif_Rx = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_Gvif_Tx = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_Power   = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_Rtc     = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_Gyro    = (U2)0xFFFFU;
    u2_s_I2cCtrl_AckCnt_G_Moni  = (U2)0xFFFFU;
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_AckChk_Wri
  Description   : 
  param[in/out] : [i ]mcu_ack               : Ack管理RAM指定
                  [io]mcu_regstep           : レジスタ書込みデータ 現在書込みStepの配列No管理
                  [i ]mcu_wri_max           : レジスタ書込みデータの総Step数管理
                  [i ]mcu_i2c_sla           : レジスタ書込み時のスレーブアドレス指定
                  [i ]GVIFTX_INISET         : レジスタ書込みデータ位置と個数の管理
                  [i ]mcu_timeout_cnt       : Ackのタイムアウト管理
                  [io]mcu_btwmtime_cnt      : レジスタアクセス間Waitタイマ
  return        : MCU_REGWRI_RTRN_NONACT    : 書込み要求なし
                  MCU_REGWRI_RTRN_ACT       : 書込み要求あり
                  MCU_REGWRI_RTRN_FIN       : 書込みフロー完了通知
  Note          : I2C 書込み時Ack有無確認
*****************************************************************************/
static uint8 Mcu_Dev_I2c_Ctrl_AckChk_Wri(uint8 mcu_ack, uint16 * mcu_regstep, const uint16 mcu_wri_max, 
                                        const uint8 mcu_i2c_sla, const ST_REG_WRI_REQ * I2C_WR_REGSET, const uint32 mcu_timeout_cnt,
                                        uint16 * mcu_btwmtime_cnt)
{
    uint8   mcu_return;     /* 戻り値：書込みフラグ */
    uint16  mcu_i2c_queue;  /* I2C キューの空き状況 */
    uint16  mcu_nxt;        /* 次のレジスタ書込み位置 */

    mcu_return      = (uint8)MCU_REGWRI_RTRN_NONACT;

    /* 初回 */
    if((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_INI){
        /* 初回レジスタ書込み位置設定 */
        mcu_nxt = (uint16)0U;
        /* レジスタアクセス間waitタイマ 初期化(0xFFFF) */
        (*mcu_btwmtime_cnt) = (uint16)0xFFFFU;
    }
    /* Ackあり(正常 or レジスタアクセス間wait中) */
    else if(((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_RCV) || (((U2)0U < (*mcu_btwmtime_cnt) && ((*mcu_btwmtime_cnt) < (U2)0xFFFFU)))){
        /* Ackを正常に置換(Ack受信は単発でありwait中保持されていないため) */
        (*Mcu_I2c_Ack[mcu_ack]) = (U1)MCU_REGWRI_ACK_RCV;
        /* 次のレジスタ書込み位置取得 */
        mcu_nxt = (*mcu_regstep) + (uint16)1U;
        /* レジスタアクセス間waitタイマ インクリメント */
        (*mcu_btwmtime_cnt)++;
    }
    /* Ackなし,Ackあり(異常) */
    else{
        /* mcu_nxt未使用のため再送位置で初期化のみ実施 */
        mcu_nxt = (*mcu_regstep);
        /* レジスタアクセス間waitタイマ アクセス完了前なのでゼロクリア */
        (*mcu_btwmtime_cnt) = (uint16)0U;
    }

    /* Ack受信回数 < 書込み回数 */
    if((*u2_s_I2cCtrl_AckCnt[mcu_ack]) < I2C_WR_REGSET[(*mcu_regstep)].u2_num){
        /* 書込み回数分のAck待ち */
        /* レジスタアクセス間waitタイマ アクセス完了前なのでゼロクリア */
        (*mcu_btwmtime_cnt) = (uint16)0U;
    }
    /* [Ackあり(正常) or 初回] & [レジスタアクセス間のWait時間経過] */
    else if((((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_INI) || ((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_RCV)) &&
    // if((((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_INI) || ((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_RCV)) &&
       ((*mcu_btwmtime_cnt) >= I2C_WR_REGSET[(*mcu_regstep)].u2_wait)){
        /* レジスタアクセス間waitタイマのゼロクリア */
        (*mcu_btwmtime_cnt) = (uint16)0U;

        /* 規定の書込み回数分完了したか判定 */
        if(mcu_nxt >= mcu_wri_max){
            /* 初期設定フロー完了通知 */
            (*Mcu_I2c_Ack[mcu_ack]) = (uint8)MCU_REGWRI_ACK_INI;
            (*mcu_regstep)          = (uint8)0U;
            mcu_return              = (uint8)MCU_REGWRI_RTRN_FIN;
            /* Ack受信回数のクリア */
            (*u2_s_I2cCtrl_AckCnt[mcu_ack]) = (U2)0xFFFFU;
        }
        else{
            /* I2Cの書込みキューの空き状況確認 */
            mcu_i2c_queue   = u2_g_GpI2cMaRwcRembySla(mcu_i2c_sla, I2C_WR_REGSET[mcu_nxt].u2_num);

            /* 書込み予定データ以上の空き有り */
            if(mcu_i2c_queue >= I2C_WR_REGSET[mcu_nxt].u2_num){
                /* レジスタ書込み位置変更 */
                (*mcu_regstep) = mcu_nxt;
                /* 書込みデータ残存のため書込みフラグON */
                mcu_return = (uint8)MCU_REGWRI_RTRN_ACT;
                /* Ack取得RAMのクリア */
                (*Mcu_I2c_Ack[mcu_ack]) = (uint8)MCU_REGWRI_ACK_NON;
                /* Ack受信回数のクリア */
                (*u2_s_I2cCtrl_AckCnt[mcu_ack]) = (U2)0U;
            }
        }
    }
    /* Ackあり(異常) or Ackタイムアウト */
    else if(((*Mcu_I2c_Ack[mcu_ack]) == (uint8)MCU_REGWRI_ACK_ERR) || (mcu_timeout_cnt > (uint32)MCU_I2C_TRX_TIMEOUT)){
        /* 書込み要求を再送する */
        mcu_return = (uint8)MCU_REGWRI_RTRN_ACT;
        /* 再送のためAckをクリアする */
        (*Mcu_I2c_Ack[mcu_ack])      = (uint8)MCU_REGWRI_ACK_NON;
        /* Ack受信回数のクリア */
        (*u2_s_I2cCtrl_AckCnt[mcu_ack]) = (U2)0U;
    }
    else{
        /* Ackなし or レジスタアクセス間のWait時間経過前 */
        /* Ackタイムアウト前 */
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_RegSet
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack管理RAM指定
                  [io]mcu_regstep       : レジスタ書込みデータ 現在書込みStepの配列No管理
                  [i ]mcu_wri_max       : レジスタ書込みデータ 総Step数
                  [i ]mcu_i2c_sla       : レジスタ書込み時のスレーブアドレス指定
                  [i ]I2C_WR_REGSET     : レジスタ書込みデータ 開始位置と個数の管理テーブルへのアドレス
                  [io]mcu_timeout_cnt   : Ackのタイムアウト管理
                  [i ]mcu_setreg        : レジスタ書込みデータ 書込みデータ定義用配列へのアドレス
                  [io]mcu_btwmtime_cnt  : レジスタアクセス間Waitタイマ
  return        : FALSE                 : 書込み処理未完了
                  TRUE                  : 全データの書込み処理完了
  Note          : I2C レジスタ書込み処理
*****************************************************************************/
uint8 Mcu_Dev_I2c_Ctrl_RegSet(uint8 mcu_ack, uint16 * mcu_regstep, const uint16 mcu_wri_max,
                                const uint8 mcu_i2c_sla, const ST_REG_WRI_REQ * I2C_WR_REGSET, uint32 * mcu_timeout_cnt,
                                const ST_GP_I2C_MA_REQ * mcu_setreg, uint16 * mcu_btwmtime_cnt)
{
    uint8   mcu_wrichk;     /* 書込みフラグ */
    uint8   mcu_I2c_ret;    /* 戻り値：レジスタ書込み要求結果 */
    uint8   mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_wrichk      = (uint8)MCU_REGWRI_RTRN_NONACT;
    mcu_return      = (uint8)FALSE;

    /* Ack状況確認 */
    mcu_wrichk = Mcu_Dev_I2c_Ctrl_AckChk_Wri(mcu_ack, mcu_regstep, (uint16)mcu_wri_max, 
                                            (uint8)mcu_i2c_sla, I2C_WR_REGSET, (*mcu_timeout_cnt), mcu_btwmtime_cnt);

    if(mcu_wrichk == (uint8)MCU_REGWRI_RTRN_ACT){
        /* レジスタ書込み開始要求 */
        mcu_I2c_ret = u1_g_GpI2cMaReqTRx(&mcu_setreg[I2C_WR_REGSET[(*mcu_regstep)].u2_strt], I2C_WR_REGSET[(*mcu_regstep)].u2_num);
        /* Ackまでの時間計測開始 */
        (*mcu_timeout_cnt)  = (uint32)0U;

        if(mcu_I2c_ret == (uint8)FALSE){
            /* レジスタ書込み要求失敗のため、Ackタイムアウト扱いとし次回タスクで再送する */
            (*mcu_timeout_cnt)  = (uint32)MCU_SYS_COUNTTIME_FIN;
        }
    }
    else if(mcu_wrichk == (uint8)MCU_REGWRI_RTRN_FIN){
        mcu_return = (uint8)TRUE;
    }
    else{
        /* do nothing */
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_RegRead
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack管理RAM指定
                  [io]mcu_regstep       : レジスタ書込みデータ 現在書込みStepの配列No管理
                  [i ]mcu_i2c_sla       : レジスタ書込み時のスレーブアドレス指定
                  [io]mcu_timeout_cnt   : Ackのタイムアウト管理
                  [i ]mcu_setreg        : レジスタ書込みデータ 書込みデータ定義用配列へのアドレス
                  [io]mcu_btwmtime_cnt  : レジスタアクセス間Waitタイマ
                  [i ]mcu_mcu_b89_wait  : Bank8,9へのアクセス間Wait要否
  return        : FALSE                 : 読出し処理未完了
                  TRUE                  : 読出し処理完了
  Note          : I2C レジスタ読出し処理
*****************************************************************************/
uint8 Mcu_Dev_I2c_Ctrl_RegRead(uint8 mcu_ack, uint16 * mcu_regstep, const uint8 mcu_i2c_sla,
                                uint32 * mcu_timeout_cnt, const ST_GP_I2C_MA_REQ * mcu_setreg, uint16 * mcu_btwmtime_cnt, const uint8 mcu_waitmode)
{
    static const ST_REG_WRI_REQ I2C_READ[MCU_WRINUM_I2C_READ] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         1,         0}
    };
    /* GVIF送信向け Bank8,9アクセス時のWait時間 */
    static const ST_REG_WRI_REQ I2C_READ_B89[MCU_WRINUM_I2C_READ] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         7U/MCU_GVIFTX_TASK_TIME},
        {        1,         1,         7U/MCU_GVIFTX_TASK_TIME}
    };
    uint8           mcu_sts;        /* 書込み状況 */
    uint8           mcu_return;     /* 戻り値：フロー完了通知 */

    mcu_sts         = (uint8)FALSE;
    mcu_return      = (uint8)FALSE;

    if(mcu_waitmode == (uint8)MCU_I2C_WAIT_B89){
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet(mcu_ack, mcu_regstep, (uint16)MCU_WRINUM_I2C_READ,
                                                (uint8)mcu_i2c_sla, I2C_READ_B89, mcu_timeout_cnt,
                                                mcu_setreg, mcu_btwmtime_cnt);
    }
    else{
        /* レジスタ書込み処理 */
        mcu_sts = Mcu_Dev_I2c_Ctrl_RegSet(mcu_ack, mcu_regstep, (uint16)MCU_WRINUM_I2C_READ,
                                                (uint8)mcu_i2c_sla, I2C_READ, mcu_timeout_cnt,
                                                mcu_setreg, mcu_btwmtime_cnt);
    }

    if(mcu_sts == (uint8)TRUE){
        /* 全書込み完了 */
        mcu_return = (uint8)TRUE;
    }

    return(mcu_return);
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_VideoIc
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : 映像IC Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_VideoIc(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Eizoic      |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Eizoic < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Eizoic++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_GvifRx
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : GVIFRX Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_GvifRx(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Gvif_Rx     |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Gvif_Rx < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Gvif_Rx++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_GvifTx
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : GVIFTX Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_GvifTx(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Gvif_Tx     |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Gvif_Tx < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Gvif_Tx++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_Power
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : Power-IC Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_Power(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Power       |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Power < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Power++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_Rtc
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : RTC-IC Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_Rtc(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Rtc         |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Rtc < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Rtc++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_Gyro
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : ジャイロ Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_Gyro(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_Gyro        |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_Gyro < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_Gyro++;
    }
}

/*****************************************************************************
  Function      : Mcu_Dev_I2c_Ctrl_Ack_Gmoni
  Description   : 
  param[in/out] : [i ]mcu_ack           : Ack受信結果
  return        : -
  Note          : Gモニ Ack取得処理
*****************************************************************************/
void Mcu_Dev_I2c_Ctrl_Ack_Gmoni(const uint8 mcu_ack)
{
    Mcu_I2c_Ack_G_Moni      |=  mcu_ack;
    if(u2_s_I2cCtrl_AckCnt_G_Moni < (U2)U2_MAX){
        u2_s_I2cCtrl_AckCnt_G_Moni++;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/13/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
