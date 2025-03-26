/* 19PFV3_1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  MMText                                                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMTEXT_C_MAJOR                      (1)
#define MMTEXT_C_MINOR                      (0)
#define MMTEXT_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mmtext_prm.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MMTEXT_C_MAJOR != MMTEXT_H_MAJOR) || \
     (MMTEXT_C_MINOR != MMTEXT_H_MINOR) || \
     (MMTEXT_C_PATCH != MMTEXT_H_PATCH))
#error "source and header files are inconsistent!"
#endif /* ((MMTEXT_C_MAJOR != MMTEXT_H_MAJOR) || ... */

#if ((MMTEXT_C_MAJOR != MMTEXT_PRM_MAJOR) || \
     (MMTEXT_C_MINOR != MMTEXT_PRM_MINOR) || \
     (MMTEXT_C_PATCH != MMTEXT_PRM_PATCH))
#error "source and parameter files are inconsistent!"
#endif /* ((MMTEXT_C_MAJOR != MMTEXT_PRM_MAJOR) || ... */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMTEXT_FRAME_LENGTH                 (8)                                 /* フレーム長                                        */
#define MMTEXT_NUMOFTEXT_FRAME              (3)                                 /* 1フレームあたりの最大文字数                       */
#define MMTEXT_SFTSIZ_ONEBYTE               (8)                                 /* For 1Byte shift                                   */
#define MMTEXT_MSK_HIGHBYTE                 (0xFF00)                            /* Mask for extracting the higher 1Byte of 2Byte     */
#define MMTEXT_MSK_LOWBYTE                  (0x00FF)                            /* Mask for extracting the lower 1Byte of 2Byte      */

#define MMTEXT_FRAME_MAX_AVNMS72            (1 + ((MMTEXT_TEXT_LENGTH_AVNMS72 + (MMTEXT_NUMOFTEXT_FRAME - 1)) / MMTEXT_NUMOFTEXT_FRAME))

#define MMTEXT_KIND_INVALID                 (MMTEXT_KIND_MAX)                   /* テキスト種別無効値                                */

#define MMTEXT_RCV_OK                       (0x00)                              /* 正常受信                                          */
#define MMTEXT_RCV_NG                       (0xFF)                              /* 異常受信                                          */
#define MMTEXT_RCV_INVALID                  (0x01)                              /* 対象外                                            */

#define MMTEXT_FRAMETYPE_HEAD               (0x01)                              /* 先頭フレーム                                      */
#define MMTEXT_FRAMETYPE_TEXT               (0x02)                              /* テキストフレーム                                  */

#define MMTEXT_FRAMECOUNT_END               (0xFF)                              /* Endフレーム                                       */

#define MMTEXT_UPDNUM_VALID_MIN             (0x01)                              /* 更新No.有効値下限                                 */
#define MMTEXT_UPDNUM_VALID_MAX             (0x0E)                              /* 更新No.有効値上限                                 */
#define MMTEXT_UPDNUM_INITIAL               (0x0F)                              /* 更新No.初期値                                     */

#define MMTEXT_UNAME_REQ_INITIAL            (0x0FU)                             /* Initial UNAME_REQ                                 */

#define MMTEXT_MSGPOS_TXT_COUNT             (0)                                 /* 表示用カウンタ情報位置                            */

#define MMTEXT_MSGPOS_TXT_OFS_LOW           (0)                                 /* Text data Lower 1Byte (table position)            */
#define MMTEXT_MSGPOS_TXT_OFS_HIGH          (1)                                 /* Text data Higher 1Byte (table position)           */

#define MMTEXT_MSGPOS_TXT_DAT_A_LOW         (2)                                 /* Text data(1st of 3 characters) Lower 1Byte        */
#define MMTEXT_MSGPOS_TXT_DAT_A_HIGH        (3)                                 /* Text data(1st of 3 characters) Higher 1Byte       */
#define MMTEXT_MSGPOS_TXT_DAT_B_LOW         (4)                                 /* Text data(2nd of 3 characters) Lower 1Byte        */
#define MMTEXT_MSGPOS_TXT_DAT_B_HIGH        (5)                                 /* Text data(2nd of 3 characters) Higher 1Byte       */
#define MMTEXT_MSGPOS_TXT_DAT_C_LOW         (6)                                 /* Text data(3rd of 3 characters) Lower 1Byte        */
#define MMTEXT_MSGPOS_TXT_DAT_C_HIGH        (7)                                 /* Text data(3rd of 3 characters) Higher 1Byte       */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef union
{
    struct
    {
        U1 u1_avnms72[MMTEXT_FRAME_MAX_AVNMS72][MMTEXT_FRAME_LENGTH];
    } st_buf;                                                                   /* 受信バッファ本体                                  */
    U2 u2_dummy;                                                                /* アライメントを2byteにするためのダミー領域         */
}
UN_MMTEXT_RCVBUF;

/* テキストデータ構築関数型 */
typedef void (*FUNC_MMTEXT_CONSTRUCT)(U1* u1_ap_rcvbuf);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_MMTEXT_TXTDAT_AVNMS72 st_s_mmtext_txtdat_avnms72;                      /* User name text data                               */
static UN_MMTEXT_RCVBUF         un_s_rcvbuf;                                    /* 受信バッファ                                      */
static U1                       u1_s_frame_count[MMTEXT_KIND_MAX];              /* 受信済みフレームカウンタ最大値                    */
static U1                       u1_s_mmtext_uname_req;                          /* Set data for UNAME_REQ in METMS13                 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_MMText_CheckMessage(U1 u1_a_kind, const U1* u1_ap_msg);          /* 正常受信判定                                      */
static U1 u1_s_MMText_Check1stFrame(U1 u1_a_kind, const U1* u1_ap_msg);         /* 1フレーム目の判定                                 */
static U1 u1_s_MMText_Check2ndFrame(U1 u1_a_kind, const U1* u1_ap_msg);         /* 2フレーム目以降の判定                             */
static void vd_s_MMText_StoreMessage(U1 u1_a_kind, const U1* u1_ap_msg);        /* 受信バッファ格納                                  */
static void vd_s_MMText_ConstructTextData(U1 u1_a_kind, U1* u1_ap_rcvbuf);      /* テキストデータ構築                                */
static void vd_s_MMText_SendTxtRcvSts(U1 u1_a_kind, U1 u1_a_update_num);        /* テキスト受信ステータス送信                        */
static void vd_s_MMText_ClearAllData(void);                                     /* 全データクリア                                    */
static void vd_s_MMText_InitTextData(U1 u1_a_kind);                             /* テキストデータ初期化                              */
static void vd_s_MMText_InitSendMessage(void);                                  /* 送信メッセージ初期化                              */
static void vd_s_MMText_InitSetMessage(void);                                   /* Set Initial Tx Message                            */
static void vd_s_MMText_InvalidSetSignal(void);                                 /* Set Invalid Tx Signal                             */
static U1 u1_s_MMText_GetKind(U2 u2_a_msg_label);                               /* テキスト種別取得                                  */
static void vd_s_MMText_ClearRcvBuf(U1 u1_a_kind);                              /* 受信バッファクリア                                */
static U1 u1_s_MMText_CheckModeValid(U1 u1_a_kind, U1 u1_a_mode);               /* モード情報有効値確認                              */
static U1 u1_s_MMText_CheckUpdateNumValid(U1 u1_a_update_num);                  /* 更新No.有効値確認                                 */
static U1 u1_s_MMText_CheckReceived(U1 u1_a_kind, U1 u1_a_count);               /* 受信済み確認                                      */
static U1 u1_s_MMText_CheckFrameType(U1 u1_a_kind, U1 u1_a_count);              /* フレームタイプ確認                                */
static U1 u1_s_MMText_CombineText(U2* u2_ap_dest, U1* u1_ap_rcvbuf, U1 u1_a_count); /* テキスト結合                                      */
static void vd_s_MMText_ConstructTextData_AVNMS72(U1* u1p_a_mmtext_rcvbuf);     /* Create Text Data(AVNMS72)                         */

static U1 u1_s_MMText_GetMsgStsJdg(U1 u1_a_kind);                               /* テキスト種別メッセージ受信状態判定                */
static void vd_s_MMText_WriteUserNameData(U1 u1_a_mmtext_chg_num);              /* Write User Name Data                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* テキストデータ情報テーブル */
static const struct
{
    void* vp_txtdat;                                                            /* データバッファアドレス                            */
    U4 u4_size;                                                                 /* データバッファサイズ                              */
    U1* u1p_update_num;                                                         /* 更新No.格納アドレス                               */
    FUNC_MMTEXT_CONSTRUCT fp_construct_func;                                    /* テキストデータ構築関数                            */
}
st_tbl_txtdat_info[MMTEXT_KIND_MAX] =
{
    {(void*)&st_s_mmtext_txtdat_avnms72,   sizeof(st_s_mmtext_txtdat_avnms72),    &st_s_mmtext_txtdat_avnms72.u1_STA_CHG_UNAME_A,
        &vd_s_MMText_ConstructTextData_AVNMS72}  /* MMTEXT_KIND_AVNMS72 */
};

/* 受信バッファ情報テーブル */
static const struct
{
    U1* u1p_rcvbuf;                                                             /* 受信バッファアドレス                              */
    U4 u4_size;                                                                 /* 受信バッファサイズ                                */
}
st_tbl_rcvbuf_info[MMTEXT_KIND_MAX] =
{
    {(U1*)un_s_rcvbuf.st_buf.u1_avnms72,   sizeof(un_s_rcvbuf.st_buf.u1_avnms72)}     /* MMTEXT_KIND_AVNMS72 */
};

/* フレーム情報テーブル */
static const struct
{
    U1 u1_max;                                                                  /* 最大フレーム数                                    */
    U1 u1_frame_per_line;                                                       /* 1行あたりのフレーム数                             */
    U1 u1_mode_mask;                                                            /* モード情報マスク                                  */
    U1 u1_mode_offset;                                                          /* モード情報オフセット                              */
}
st_tbl_frame_info[MMTEXT_KIND_MAX] =
{
    {(U1)MMTEXT_FRAME_MAX_AVNMS72,  (U1)MMTEXT_FRAME_MAX_AVNMS72,                                 MMTEXT_UNAME_T_MODE_MASK,     MMTEXT_UNAME_T_MODE_SHIFT     }  /* MMTEXT_KIND_AVNMS72 */
};

/* In-frame character position table */
static const U1 u1_s_mmtext_chrofs[MMTEXT_NUMOFTEXT_FRAME][sizeof(U2)] = {
    {
        (U1)MMTEXT_MSGPOS_TXT_DAT_A_LOW,    (U1)MMTEXT_MSGPOS_TXT_DAT_A_HIGH
    },
    {
        (U1)MMTEXT_MSGPOS_TXT_DAT_B_LOW,    (U1)MMTEXT_MSGPOS_TXT_DAT_B_HIGH
    },
    {
        (U1)MMTEXT_MSGPOS_TXT_DAT_C_LOW,    (U1)MMTEXT_MSGPOS_TXT_DAT_C_HIGH
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* メッセージからフレームカウンタ取得 */
#define u1_MMTEXT_GET_TXT_COUNT(u1p_msg)    (((const U1*)(u1p_msg))[0])

/* メッセージからモード情報取得 */
#define u1_MMTEXT_GET_MODE(u1_kind,u1p_msg) (((((const U1*)(u1p_msg))[1])&(st_tbl_frame_info[(u1_kind)].u1_mode_mask))>>(st_tbl_frame_info[(u1_kind)].u1_mode_offset))

/* メッセージから更新No.取得 */
#define u1_MMTEXT_GET_CHG(u1p_msg)          ((((const U1*)(u1p_msg))[2])>>MMTEXT_CHG_SHIFT)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  起動通知時処理                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMText_StartNotification(void)
{
    /* 全データクリア */
    vd_s_MMText_ClearAllData();

    /* 送信メッセージ初期化 */
    vd_s_MMText_InitSendMessage();
}

/*===================================================================================================================================*/
/*  終了通知時処理                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMText_EndNotification(void)
{
    /* 何もしない */
}

/*===================================================================================================================================*/
/*  ACC-ONエッジ通知時処理                                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMText_AccOnEdgeNotification(void)
{
    /* 全データクリア */
    vd_s_MMText_ClearAllData();

    /* 送信メッセージ初期化 */
    vd_s_MMText_InitSendMessage();
}

/*===================================================================================================================================*/
/*  メッセージ処理                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U2 u2_a_msg_label   メッセージラベル                                                                                 */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMText_ProcessMessage(U2 u2_a_msg_label)
{
    U1 u1_t_kind;                                                               /* テキスト種別                                      */
    U1 u1_tp_msg[8];                                                            /* 受信メッセージ                                    */
    U1 u1_t_ccom_ret;
    U1 u1_t_result;
    U1 u1_t_count;
    U1 u1_t_update_num_new;

    vd_MMTEXT_CLEARU1((U1*)u1_tp_msg, (U4)sizeof(u1_tp_msg));

    /* テキスト種別取得 */
    u1_t_kind = u1_s_MMText_GetKind(u2_a_msg_label);

    /* 「テキスト種別無効値」なら処理終了 */
    if((U1)MMTEXT_KIND_INVALID == u1_t_kind)
    {
        return;
    }

    /* メッセージ読み出し */
    u1_t_ccom_ret = u1_MMTEXT_READ_MSG(u2_a_msg_label, (U1*)u1_tp_msg);

    /* メッセージ読み出しに失敗したら処理終了 */
    if((U1)MMTEXT_SPF_CCOM_OK != u1_t_ccom_ret)
    {
        /* メッセージ受信通知内で処理するため、あり得ない */
        return;
    }

    /* 正常受信判定 */
    u1_t_result = u1_s_MMText_CheckMessage(u1_t_kind, (const U1*)u1_tp_msg);

    /* 正常受信時はメッセージの保持や構築を行う */
    if((U1)MMTEXT_RCV_OK == u1_t_result)
    {
        /* 受信バッファに格納 */
        vd_s_MMText_StoreMessage(u1_t_kind, (U1*)u1_tp_msg);

        /* フレームカウンタ取得 */
        u1_t_count = u1_MMTEXT_GET_TXT_COUNT((U1*)u1_tp_msg);

        /* Endフレームの場合はテキストデータ構築 */
        if((U1)MMTEXT_FRAMECOUNT_END == u1_t_count)
        {
            /* 更新No.取得 */
            u1_t_update_num_new = u1_MMTEXT_GET_CHG(st_tbl_rcvbuf_info[u1_t_kind].u1p_rcvbuf);

            /* 更新No.が変化する場合、テキスト受信ステータス送信 */
            if(*st_tbl_txtdat_info[u1_t_kind].u1p_update_num != u1_t_update_num_new)
            {
                /* テキスト受信ステータス送信 */
                vd_s_MMText_SendTxtRcvSts(u1_t_kind, u1_t_update_num_new);
            }

            /* テキストデータ構築 */
            vd_s_MMText_ConstructTextData(u1_t_kind, st_tbl_rcvbuf_info[u1_t_kind].u1p_rcvbuf);

            /* テキストデータ構築完了したので受信バッファをクリア */
            vd_s_MMText_ClearRcvBuf(u1_t_kind);
        }
    }
    else if((U1)MMTEXT_RCV_NG == u1_t_result)
    {
        /* 異常受信時は受信バッファクリア */
        vd_s_MMText_ClearRcvBuf(u1_t_kind);
    }
    else
    {
        /* 対象外に該当する場合は、何も処理しない */
    }
}


/*===================================================================================================================================*/
/*  テキストデータ取得：AVNMS72                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   const ST_MMTEXT_TXTDAT_AVNMS72** stpp_a_textdata  テキストデータ格納先    <出力パラメータ>                           */
/*  Return      テキストデータ取得結果(正常/異常/未確定)                                                                             */
/*===================================================================================================================================*/
U1 u1_g_MMText_GetTextData_AVNMS72(const ST_MMTEXT_TXTDAT_AVNMS72** stpp_a_textdata)
{
    U1 u1_t_result = (U1)MMTEXT_RET_NG;

    /* パラメータチェック */
    if((const ST_MMTEXT_TXTDAT_AVNMS72**)vdp_PTR_NA != stpp_a_textdata)
    {
        /* 更新No.が初期値なら「未確定」、そうでなければ「正常」*/
        if((U1)MMTEXT_UPDNUM_INITIAL == *st_tbl_txtdat_info[MMTEXT_KIND_AVNMS72].u1p_update_num)
        {
            u1_t_result = (U1)MMTEXT_RET_UNSETTLED;
        }
        else
        {
            /* テキストデータ格納領域のアドレスを格納 */
            *stpp_a_textdata = &st_s_mmtext_txtdat_avnms72;
            u1_t_result = (U1)MMTEXT_RET_OK;
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  Send Request UNAME                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_mmtext_uname                                                                                                 */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMText_SendReqUserName(U1 u1_a_mmtext_uname)
{
    U1 u1_t_mmtext_result;
    
    u1_t_mmtext_result = u1_MMTEXT_CHECKMODESTATE(u1_a_mmtext_uname);
    if((U1)TRUE == u1_t_mmtext_result){
        u1_s_mmtext_uname_req = u1_a_mmtext_uname;
        vd_s_MMTEXT_WRITE_UNAME_REQ(u1_s_mmtext_uname_req);
    }
    else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  正常受信判定                                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1* u1_ap_msg   メッセージ                                                                                           */
/*  Return      判定結果(正常受信/異常受信/対象外)                                                                                   */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CheckMessage(U1 u1_a_kind, const U1* u1_ap_msg)
{
    U1 u1_t_result;
    U1 u1_t_count;
    U1 u1_t_chkmsg;

    /* フレームカウンタ取得 */
    u1_t_count = u1_MMTEXT_GET_TXT_COUNT(u1_ap_msg);

    /* フレームカウンタ別に判定する */
    if((U1)0x01 == u1_t_count)
    {
        /* テキスト種別に応じたメッセージを正常受信できている場合に処理を行う */
        u1_t_chkmsg = u1_s_MMText_GetMsgStsJdg(u1_a_kind);
        if((U1)FALSE != u1_t_chkmsg)
        {
            /* 1フレーム目の判定 */
            u1_t_result = u1_s_MMText_Check1stFrame(u1_a_kind, u1_ap_msg);
        }
        else
        {
            u1_t_result = (U1)MMTEXT_RCV_NG;
        }
    }
    else if((U1)0x01 < u1_t_count)
    {
        /* フレームカウンタが最終フレームか、最大フレーム数未満なら判定処理実施 */
        if(((U1)MMTEXT_FRAMECOUNT_END == u1_t_count) || (st_tbl_frame_info[u1_a_kind].u1_max > u1_t_count))
        {
            /* 2フレーム目以降の判定 */
            u1_t_result = u1_s_MMText_Check2ndFrame(u1_a_kind, u1_ap_msg);
        }
        else
        {
            /* フレームカウンタが異常値のため対象外とする */
            /* 最終フレームでない、最大フレーム数以上のフレームカウンタはあり得ない */
            u1_t_result = (U1)MMTEXT_RCV_INVALID;
        }
    }
    else
    {
        /* フレームカウンタが値域外（0x00）のため対象外とする */
        u1_t_result = (U1)MMTEXT_RCV_INVALID;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  1フレーム目の判定                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1* u1_ap_msg   メッセージ                                                                                           */
/*  Return      判定結果(正常受信/異常受信)                                                                                          */
/*===================================================================================================================================*/
static U1 u1_s_MMText_Check1stFrame(U1 u1_a_kind, const U1* u1_ap_msg)
{
    U1 u1_t_result;
    U1 u1_t_mode;
    U1 u1_t_valid;
    U1 u1_t_valid_update_num;
    U1 u1_t_update_num;

    u1_t_result = (U1)MMTEXT_RCV_NG;
    /* モード情報の有効値確認 */
    u1_t_mode = u1_MMTEXT_GET_MODE(u1_a_kind, u1_ap_msg);
    u1_t_valid = u1_s_MMText_CheckModeValid(u1_a_kind, u1_t_mode);

    /* モード情報が有効値の場合に、さらに確認を行う */
    if((U1)TRUE == u1_t_valid)
    {
            u1_t_update_num = u1_MMTEXT_GET_CHG(u1_ap_msg);
            u1_t_valid_update_num = u1_s_MMText_CheckUpdateNumValid(u1_t_update_num);

            /* 更新No.が有効値ならステータス通知との確認 */
            if((U1)TRUE == u1_t_valid_update_num)
            {
                    u1_t_result = (U1)MMTEXT_RCV_OK;
            }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  2フレーム目以降の判定                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1* u1_ap_msg   メッセージ                                                                                           */
/*  Return      判定結果(正常受信/異常受信)                                                                                          */
/*===================================================================================================================================*/
static U1 u1_s_MMText_Check2ndFrame(U1 u1_a_kind, const U1* u1_ap_msg)
{
    U1 u1_t_result;
    U1 u1_t_count;
    U1 u1_t_count_rcvbuf;
    U1 u1_t_received_1st;
    U1 u1_t_received;
    U1 u1_t_mode;
    U1 u1_t_mode_rcvbuf;
    U1 u1_t_update_num;
    U1 u1_t_update_num_rcvbuf;

    u1_t_result = (U1)MMTEXT_RCV_NG;
    /* フレームカウンタ取得 */
    u1_t_count = u1_MMTEXT_GET_TXT_COUNT(u1_ap_msg);

    /* 1フレーム目受信済み確認 */
    u1_t_received_1st = u1_s_MMText_CheckReceived(u1_a_kind, 0x01u);

    /* 処理中フレーム受信済み確認 */
    u1_t_received = u1_s_MMText_CheckReceived(u1_a_kind, u1_t_count);

    /* 1フレーム目受信済み、かつ処理中フレーム未受信なら、モード情報の確認 */
    if(((U1)TRUE == u1_t_received_1st) && ((U1)FALSE == u1_t_received))
    {
        /* モード情報取得 */
        u1_t_mode = u1_MMTEXT_GET_MODE(u1_a_kind, u1_ap_msg);
        u1_t_mode_rcvbuf = u1_MMTEXT_GET_MODE(u1_a_kind, st_tbl_rcvbuf_info[u1_a_kind].u1p_rcvbuf);

        /* メッセージと受信バッファでモード情報が一致したら正常受信とする */
        if(u1_t_mode == u1_t_mode_rcvbuf)
        {
            /* 行の先頭フレームの場合は更新No.も確認する */
            u1_t_count_rcvbuf = u1_s_MMText_CheckFrameType(u1_a_kind, u1_t_count);
            if((U1)MMTEXT_FRAMETYPE_HEAD == u1_t_count_rcvbuf)
            {
                /* 更新No.取得 */
                u1_t_update_num = u1_MMTEXT_GET_CHG(u1_ap_msg);
                u1_t_update_num_rcvbuf = u1_MMTEXT_GET_CHG(st_tbl_rcvbuf_info[u1_a_kind].u1p_rcvbuf);

                /* メッセージと受信バッファで更新No.が一致したら正常受信とする */
                if(u1_t_update_num == u1_t_update_num_rcvbuf)
                {
                    u1_t_result = (U1)MMTEXT_RCV_OK;
                }
            }
            else
            {
                /* 行の先頭フレームでない場合はここで正常受信とする */
                u1_t_result = (U1)MMTEXT_RCV_OK;
            }
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  受信バッファ格納                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1* u1_ap_msg   メッセージ                                                                                           */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_StoreMessage(U1 u1_a_kind, const U1* u1_ap_msg)
{
    U1 u1_t_count;
    U1 u1_t_received;
    U4 u4_t_index;
    U4 u4_t_count_calculation;
    U4 u4_t_index_calculation;

    /* フレームカウンタ取得 */
    u1_t_count = u1_MMTEXT_GET_TXT_COUNT(u1_ap_msg);

    /* 1フレーム目で、既に受信済みの場合は受信バッファをクリア */
    if((U1)0x01 == u1_t_count)
    {
        /* 受信済み確認 */
        u1_t_received = u1_s_MMText_CheckReceived(u1_a_kind, u1_t_count);
        if((U1)TRUE == u1_t_received)
        {
            vd_s_MMText_ClearRcvBuf(u1_a_kind);
        }
    }

    /* 格納先インデックスを決定 */
    if((U1)MMTEXT_FRAMECOUNT_END == u1_t_count)
    {
        u4_t_index_calculation = (U4)u1_s_frame_count[u1_a_kind];

        if(((U4)U4_MAX/(U4)MMTEXT_FRAME_LENGTH) >= u4_t_index_calculation)
        {
            /* Endフレームは受信済み最大カウンタ値からインデックスを算出 */
            u4_t_index = (U4)(u4_t_index_calculation * (U4)MMTEXT_FRAME_LENGTH);
        }
        else
        {
            u4_t_index = U4_MAX;
        }
    }
    else
    {
        if((U4)U4_MIN < (U4)u1_t_count)
        {
            u4_t_count_calculation = (U4)((U4)u1_t_count - (U4)1);

            if(((U4)U4_MAX/(U4)MMTEXT_FRAME_LENGTH) >= u4_t_count_calculation)
            {
                /* Endフレーム以外はフレームカウンタからインデックスを算出 */
                u4_t_index = (U4)(u4_t_count_calculation * (U4)MMTEXT_FRAME_LENGTH);

                /* 受信済み最大カウンタ値を更新 */
                if(u1_t_count > u1_s_frame_count[u1_a_kind])
                {
                    u1_s_frame_count[u1_a_kind] = u1_t_count;
                }
            }
            else
            {
                u4_t_index = U4_MAX;
            }
        }
        else
        {
            u4_t_index = U4_MAX;
        }
    }

    if (st_tbl_rcvbuf_info[u1_a_kind].u4_size > u4_t_index) {
        /* 格納先にメッセージをコピー */
        vd_MMTEXT_COPYU1(&st_tbl_rcvbuf_info[u1_a_kind].u1p_rcvbuf[u4_t_index], u1_ap_msg, (U4)MMTEXT_FRAME_LENGTH);
    }else {
        /* DO NOTHING */
    }
    
}

/*===================================================================================================================================*/
/*  テキストデータ構築                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1* u1_ap_msg   受信バッファ                                                                                         */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_ConstructTextData(U1 u1_a_kind, U1* u1_ap_rcvbuf)
{
    /* 格納前にテキストデータ初期化 */
    vd_s_MMText_InitTextData(u1_a_kind);

    /* テキスト種別ごとのテキストデータ構築処理呼び出し */
    st_tbl_txtdat_info[u1_a_kind].fp_construct_func(u1_ap_rcvbuf);
}

/*===================================================================================================================================*/
/*  テキスト受信ステータス送信                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind        テキスト種別                                                                                     */
/*              U1 u1_a_update_num  更新No.                                                                                          */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_SendTxtRcvSts(U1 u1_a_kind, U1 u1_a_update_num)
{
    /* テキスト種別ごとに送信データ書き込み */
    switch(u1_a_kind)
    {

        case (U1)MMTEXT_KIND_AVNMS72:
            vd_s_MMText_WriteUserNameData(u1_a_update_num);
            break;

        default:
            /* DO NOTHING */
            break;
    }
}

/*===================================================================================================================================*/
/*  全データクリア                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_ClearAllData(void)
{
    U1 u1_t_kind;

    /* 受信バッファと受信済みフレームカウンタ最大値をクリア */
    vd_MMTEXT_CLEARU1((U1*)&un_s_rcvbuf, (U4)sizeof(un_s_rcvbuf));
    vd_MMTEXT_CLEARU1((U1*)u1_s_frame_count, (U4)sizeof(u1_s_frame_count));

    /* データバッファクリア */
    for(u1_t_kind = (U1)0; (U1)MMTEXT_KIND_MAX > u1_t_kind; u1_t_kind++)
    {
        vd_s_MMText_InitTextData(u1_t_kind);
    }

    u1_s_mmtext_uname_req = (U1)MMTEXT_UNAME_REQ_INITIAL;
}

/*===================================================================================================================================*/
/*  テキストデータ初期化                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_InitTextData(U1 u1_a_kind)
{
    /* テキストデータ格納領域をクリア */
    vd_MMTEXT_CLEARU2((U2*)st_tbl_txtdat_info[u1_a_kind].vp_txtdat, st_tbl_txtdat_info[u1_a_kind].u4_size);

    /* データバッファに更新No.初期値を設定 */
    *st_tbl_txtdat_info[u1_a_kind].u1p_update_num = (U1)MMTEXT_UPDNUM_INITIAL;
}

/*===================================================================================================================================*/
/*  送信メッセージ初期化                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_InitSendMessage(void)
{
    vd_s_MMText_InitSetMessage();

    vd_s_MMText_InvalidSetSignal();

}

/*===================================================================================================================================*/
/*  Set Initial Tx Message                                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_InitSetMessage(void)
{
#if 0   /* BEV BSW provisionally */
    /* 送信メッセージの初期値書き込み */
    vd_g_MMTEXT_SET_INIT_MSG_METMS02();
    vd_g_MMTEXT_SET_INIT_MSG_METMS03();
    vd_g_MMTEXT_SET_INIT_MSG_METMS04();
    /* 対象外となるメッセージの送信停止 */
    vd_g_MMTEXT_STOP_TX_MSG_METMS05();

    vd_g_MMTEXT_SET_INIT_MSG_METMS06();
    vd_g_MMTEXT_SET_INIT_MSG_METMS10();
    vd_g_MMTEXT_SET_INIT_MSG_METMS11();
    vd_g_MMTEXT_SET_INIT_MSG_METMS13();
#endif
}

/*===================================================================================================================================*/
/*  Set Invalid Tx Signal                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_InvalidSetSignal(void)
{
    /* 対象外テキストの更新No.に無効値を設定 */
    vd_MMTEXT_WRITE_INVALID_STA4_CHG_AUDIO_M();

    /* Set invalid value for the update number */
    vd_MMTEXT_WRITE_INVALID_LST_CHG_CMN_M();
    vd_MMTEXT_WRITE_INVALID_FAV_CHG_M();
    vd_MMTEXT_WRITE_INVALID_HST_CHG_M();
    vd_MMTEXT_WRITE_INVALID_CD_CHG_M();
    vd_MMTEXT_WRITE_INVALID_CT_CHG_VR_M();
    vd_MMTEXT_WRITE_INVALID_RT_CHG_VR_M();
    vd_MMTEXT_WRITE_INVALID_GT_CHG_VR_M();
}

/*===================================================================================================================================*/
/*  テキスト種別取得                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U2 u2_a_msg_label   メッセージラベル                                                                                 */
/*  Return      テキスト種別(対象外のメッセージラベル指定時は無効値)                                                                 */
/*===================================================================================================================================*/
static U1 u1_s_MMText_GetKind(U2 u2_a_msg_label)
{
    U1 u1_t_kind;
    U1 u1_t_index;

    /* テキスト種別を無効値で初期化 */
    u1_t_kind = (U1)MMTEXT_KIND_INVALID;

    /* メッセージラベル情報テーブルからテキスト種別を取得 */
    for(u1_t_index = (U1)0; (U1)MMTEXT_KIND_MAX > u1_t_index; u1_t_index++)
    {
#if 0   /* BEV BSW provisionally */
        if(u2_tbl_msg_label_info[u1_t_index] == u2_a_msg_label)
        {
            u1_t_kind = u1_t_index;
            break;
        }
#endif
    }

    return(u1_t_kind);
}

/*===================================================================================================================================*/
/*  受信バッファクリア                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_ClearRcvBuf(U1 u1_a_kind)
{
    /* 受信バッファと受信済みフレームカウンタ最大値をクリア */
    vd_MMTEXT_CLEARU1((U1*)st_tbl_rcvbuf_info[u1_a_kind].u1p_rcvbuf, st_tbl_rcvbuf_info[u1_a_kind].u4_size);
    vd_MMTEXT_CLEARU1((U1*)&u1_s_frame_count[u1_a_kind], (U4)sizeof(u1_s_frame_count[u1_a_kind]));
}

/*===================================================================================================================================*/
/*  モード情報有効値確認                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1 u1_a_mode    モード情報                                                                                           */
/*  Return      確認結果(有効値/無効値)                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CheckModeValid(U1 u1_a_kind, U1 u1_a_mode)
{
    U1 u1_t_valid;
    U1 u1_t_result;

    /* テキスト種別に対応した判定関数を呼び出す */
    u1_t_result = st_tbl_extfunc_info[u1_a_kind].fp_mode_valid_func(u1_a_mode);

    /* 判定結果が有効値の場合、戻り値を有効値とする */
    if((U1)TRUE == u1_t_result)
    {
        u1_t_valid = (U1)TRUE;
    }
    else
    {
        u1_t_valid = (U1)FALSE;
    }

    return(u1_t_valid);
}

/*===================================================================================================================================*/
/*  更新No.有効値確認                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_update_num  更新No.                                                                                          */
/*  Return      確認結果(有効値/無効値)                                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CheckUpdateNumValid(U1 u1_a_update_num)
{
    U1 u1_t_valid;

    /* 更新No.が有効値域内かどうかを確認 */
    if(((U1)MMTEXT_UPDNUM_VALID_MIN <= u1_a_update_num) &&
        ((U1)MMTEXT_UPDNUM_VALID_MAX >= u1_a_update_num))
    {
        u1_t_valid = (U1)TRUE;
    }
    else
    {
        u1_t_valid = (U1)FALSE;
    }

    return(u1_t_valid);
}


/*===================================================================================================================================*/
/*  受信済み確認                                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1 u1_a_count   対象フレームカウンタ                                                                                 */
/*  Return      確認結果(受信済み/未受信)                                                                                            */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CheckReceived(U1 u1_a_kind, U1 u1_a_count)
{
    U1 u1_t_result;
    U1 u1_t_count_rcvbuf;
    U4 u4_t_index;
    U4 u4_t_index_calculaion;

    /* Init */
    u1_t_result = (U1)FALSE;

    /* 対象フレームカウンタが最大フレーム数より大きい場合は未受信とする */
    if(u1_a_count > st_tbl_frame_info[u1_a_kind].u1_max)
    {
        return (U1)FALSE;
    }

    if((U1)U1_MIN < u1_a_count)
    {
        u4_t_index_calculaion = (U4)((U4)u1_a_count - (U4)1);

        if(((U4)U4_MAX/(U4)MMTEXT_FRAME_LENGTH) >= u4_t_index_calculaion)
        {
            /* 受信バッファのフレームカウンタが0x00であれば未受信とする */
            u4_t_index = (U4)(u4_t_index_calculaion * (U4)MMTEXT_FRAME_LENGTH);
            u1_t_count_rcvbuf = u1_MMTEXT_GET_TXT_COUNT(&st_tbl_rcvbuf_info[u1_a_kind].u1p_rcvbuf[u4_t_index]);

            if((U1)0x00 == u1_t_count_rcvbuf)
            {
                u1_t_result = (U1)FALSE;
            }
            else
            {
                u1_t_result = (U1)TRUE;
            }
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  フレームタイプ確認                                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1 u1_a_kind    テキスト種別                                                                                         */
/*              U1 u1_a_count   フレームカウンタ                                                                                     */
/*  Return      フレームタイプ(先頭フレーム/テキストフレーム)                                                                        */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CheckFrameType(U1 u1_a_kind, U1 u1_a_count)
{
    U1 u1_t_type;

    u1_t_type = (U1)MMTEXT_FRAMETYPE_TEXT;
    /* フレームカウンタと1行あたりのフレーム数の剰余が1なら先頭フレーム */
    if((U1)0 != st_tbl_frame_info[u1_a_kind].u1_frame_per_line)
    {
        if((U1)1 == (u1_a_count % st_tbl_frame_info[u1_a_kind].u1_frame_per_line))
        {
            u1_t_type =(U1) MMTEXT_FRAMETYPE_HEAD;
        }
    }

    return(u1_t_type);
}

/*===================================================================================================================================*/
/*  テキスト結合                                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1* u2_ap_dest      テキスト格納先                                                                                   */
/*              U1* u1_ap_rcvbuf    受信バッファ                                                                                     */
/*              U1 u1_a_count       指定フレーム数                                                                                   */
/*  Return      処理結果(結合完了/Endフレーム検出)                                                                                   */
/*===================================================================================================================================*/
static U1 u1_s_MMText_CombineText(U2* u2_ap_dest, U1* u1_ap_rcvbuf, U1 u1_a_count)
{
    U1                  u1_t_result;
    U1                  u1_t_index;
    U1*                 u1p_t_msg_text;
    U1                  u1_t_loop;
    U1                  u1_t_txtcnt;
    U2                  u2_t_txtdat_high;
    U2                  u2_t_txtdat_low;

    u1_t_result = (U1)TRUE;

    /* 格納先インデックスを初期化 */
    u1_t_index = (U1)0;

    /* 指定フレーム数分繰り返す */
    for(u1_t_loop = (U1)0; u1_t_loop < u1_a_count; u1_t_loop++)
    {
        /* 対象フレームを取得 */
        u1p_t_msg_text = &u1_ap_rcvbuf[u1_t_loop * (U1)MMTEXT_FRAME_LENGTH];

        /* 対象フレームが受信済みならテキストデータを結合 */
        if((U1)0x00 != u1p_t_msg_text[MMTEXT_MSGPOS_TXT_COUNT])
        {
            for(u1_t_txtcnt = 0; (U1)MMTEXT_NUMOFTEXT_FRAME > u1_t_txtcnt; u1_t_txtcnt++)
            {
                if(((U1)MMTEXT_NUMOFTEXT_FRAME * u1_a_count) > u1_t_index)
                {
                    /* 格納先領域にコピーしてインデックスを進める */
                    u2_t_txtdat_high = (U2)(((U2)u1p_t_msg_text[ u1_s_mmtext_chrofs[u1_t_txtcnt][MMTEXT_MSGPOS_TXT_OFS_HIGH] ]) << (U1)MMTEXT_SFTSIZ_ONEBYTE);
                    u2_t_txtdat_low  = (U2)u1p_t_msg_text[u1_s_mmtext_chrofs[u1_t_txtcnt][MMTEXT_MSGPOS_TXT_OFS_LOW]];
                    u2_ap_dest[u1_t_index] = ((u2_t_txtdat_high & (U2)MMTEXT_MSK_HIGHBYTE) | (u2_t_txtdat_low & (U2)MMTEXT_MSK_LOWBYTE));
                    u1_t_index++;
                }
                else{
                    u1_t_result = (U1)FALSE;
                    break;
                }
            }
            
            /* Endフレームを検出したら途中終了 */
            if((U1)MMTEXT_FRAMECOUNT_END == u1p_t_msg_text[MMTEXT_MSGPOS_TXT_COUNT])
            {
                u1_t_result = (U1)FALSE;
                break;
            }
            
            if(((U1)MMTEXT_NUMOFTEXT_FRAME * u1_a_count) <= u1_t_index)
            {
                break;
            }
        }
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  Create Text Data(AVNMS72)                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1* u1p_a_mmtext_rcvbuf                                                                                              */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_ConstructTextData_AVNMS72(U1* u1p_a_mmtext_rcvbuf)
{
    /* 1st Frame Data */
    st_s_mmtext_txtdat_avnms72.u1_UNAME_T_MODE = u1p_a_mmtext_rcvbuf[1];
    st_s_mmtext_txtdat_avnms72.u1_STA_CHG_UNAME_A = u1_MMTEXT_GET_CHG(u1p_a_mmtext_rcvbuf);

    /* Text Data */
    (void)u1_s_MMText_CombineText(
        (U2*)st_s_mmtext_txtdat_avnms72.u2_UNAME_TXT_DAT,
        &u1p_a_mmtext_rcvbuf[MMTEXT_FRAME_LENGTH],
        (U1)(MMTEXT_FRAME_MAX_AVNMS72 - 1));
}

/*===================================================================================================================================*/
/*  テキスト種別メッセージ受信状態判定                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1  u1_a_kind    テキスト種別                                                                                        */
/*  Return      TRUE ：「対象テキスト」 かつ 「正常受信」 かつ 「ACC-ON」                                                            */
/*              FALSE：「対象外テキスト」 または 「未受信」 または 「途絶」 または 「ACC-OFF」                                       */
/*===================================================================================================================================*/
static U1 u1_s_MMText_GetMsgStsJdg(U1 u1_a_kind)
{
    U1 u1_t_result;

    switch(u1_a_kind)
    {

        /* Always TRUE because nothing Mode notice and Status notice */
        case (U1)MMTEXT_KIND_AVNMS72:
            u1_t_result = (U1)TRUE;
            break;

        default:
            /* テキスト種別が対象外の場合は判定処理させない */
            u1_t_result = (U1)FALSE;
            break;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  Write User Name Data                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   U1  u1_a_mmtext_chg_num                                                                                              */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMText_WriteUserNameData(U1 u1_a_mmtext_chg_num)
{
    U1 u1_t_mmtext_uname_t_mode;

    u1_t_mmtext_uname_t_mode = u1_MMTEXT_GET_MODE((U1)MMTEXT_KIND_AVNMS72, st_tbl_rcvbuf_info[(U1)MMTEXT_KIND_AVNMS72].u1p_rcvbuf);
    if(u1_t_mmtext_uname_t_mode == u1_s_mmtext_uname_req){
        u1_s_mmtext_uname_req = (U1)MMTEXT_UNAME_REQ_INITIAL;
    }
    else{
        /* Do Nothing */
    }

    vd_s_MMTEXT_WRITE_STA_CHG_UNAME_M(u1_a_mmtext_chg_num);
    vd_s_MMTEXT_WRITE_UNAME_REQ(u1_s_mmtext_uname_req);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  19PFV3_1.0.0    2024.04.19  YK      Create New based on [P4.3.0]                                                                 */
/*  19PFV3_1.0.1    2024.05.15  YK      Add Invalid change No. (MET24GL3-2601)                                                       */
/*                                                                                                                                   */
/*  YK = Yuki Koshimae, ISB                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
