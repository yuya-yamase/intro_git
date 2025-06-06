/* 19PFV3_1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  MMTextでカスタマイズするデータを定義する                                                                                         */
/*===================================================================================================================================*/

#ifndef MMTEXT_PRM
#define MMTEXT_PRM

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMTEXT_PRM_MAJOR                    (1)
#define MMTEXT_PRM_MINOR                    (0)
#define MMTEXT_PRM_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "memcpy_u1.h"
#include "memfill_u1.h"
#include "memfill_u2.h"

#include "MM_Appl.h"
#include "mmlib.h"
#include "mmtext.h"
#include "mmvar.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type definition                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* モード情報有効値判定関数型 */
typedef U1 (*FUNC_MMTEXT_CHECK_MODE)(U1 u1_a_mode);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#define MMTEXT_AVNMS72_MSG                 (MSG_AVNMS72_RXCH1)
#endif

/* テキスト種別 */
enum {
    MMTEXT_KIND_AVNMS72 = 0,
    MMTEXT_KIND_MAX
};

/* CCOM戻り値 */
#define MMTEXT_SPF_CCOM_OK                              (0U)                    /* 正常終了                                          */


/* モード情報抽出用マスク値定義 */
#define MMTEXT_UNAME_T_MODE_MASK                        (0xFFu)

/* モード情報抽出用ビットシフト量定義 */
#define MMTEXT_UNAME_T_MODE_SHIFT                       (0u)

/* 更新No.抽出用ビットシフト量定義 */
#define MMTEXT_CHG_SHIFT                                (4u)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* コピー、クリア */
#define vd_MMTEXT_COPYU1(u1_p_dst,u1_p_src,u4_num_byte) (vd_g_MemcpyU1(u1_p_dst,u1_p_src,u4_num_byte))
#define vd_MMTEXT_CLEARU1(u1_p_buff,u4_num_byte)        (vd_g_MemfillU1(u1_p_buff,(U1)0,u4_num_byte))
#define vd_MMTEXT_CLEARU2(u2_p_buff,u4_num_byte)        (vd_g_MemfillU2(u2_p_buff,(U2)0,(u4_num_byte)/sizeof(U2)))

/* CCOMからのメッセージ状態取得 */
#define u1_MMTEXT_GET_MSG_STS(u2_msg_label)             (u1_g_MMLibGetMsgStatus((u2_msg_label)))

/* CCOMからのメッセージ読み出し */
#define u1_MMTEXT_READ_MSG(u2_msg_label,u1_p_msg)       ((U1)Com_ReadIPDU(u2_msg_label,u1_p_msg))


/* CCOMへのデータ書き込み */
#if 0   /* BEV BSW provisionally */
#define vd_s_MMTEXT_WRITE_STA_CHG_UNAME_M(u1dat)        (vd_g_MMLibWriteTX1(STA_CHG_UNAME_M,&(u1dat)))
#define vd_s_MMTEXT_WRITE_UNAME_REQ(u1dat)              (vd_g_MMLibWriteTX1(UNAME_REQ,&(u1dat)))
#else
#define vd_s_MMTEXT_WRITE_STA_CHG_UNAME_M(u1dat)        (vdp_PTR_NA)
#define vd_s_MMTEXT_WRITE_UNAME_REQ(u1dat)              (vdp_PTR_NA)
#endif

/* CCOMへのデータ書き込み（無効値） */
#define vd_g_MMTextWriteImmTX1(DataName)                (vd_g_MMLibWriteImmTX1(DataName, (const void*)vdp_PTR_NA))
#define vd_g_MMTextWriteImmTX1SpfOnly(DataName)         (vd_g_MMLibWriteImmTX1SpfOnly(DataName, (const void*)vdp_PTR_NA))

#if 0   /* BEV BSW provisionally */
#define vd_MMTEXT_WRITE_INVALID_STA4_CHG_AUDIO_M()      (vd_g_MMTextWriteImmTX1(STA4_CHG_AUDIO_M))
#define vd_MMTEXT_WRITE_INVALID_LST_CHG_CMN_M()         (vd_g_MMTextWriteImmTX1(LST_CHG_CMN_M))
#define vd_MMTEXT_WRITE_INVALID_FAV_CHG_M()             (vd_g_MMTextWriteImmTX1(FAV_CHG_M))
#define vd_MMTEXT_WRITE_INVALID_HST_CHG_M()             (vd_g_MMTextWriteImmTX1(HST_CHG_M))
#define vd_MMTEXT_WRITE_INVALID_CD_CHG_M()              (vd_g_MMTextWriteImmTX1(CD_CHG_M))
#define vd_MMTEXT_WRITE_INVALID_CT_CHG_VR_M()           (vd_g_MMTextWriteImmTX1(CT_CHG_VR_M))
#define vd_MMTEXT_WRITE_INVALID_RT_CHG_VR_M()           (vd_g_MMTextWriteImmTX1(RT_CHG_VR_M))
#define vd_MMTEXT_WRITE_INVALID_GT_CHG_VR_M()           (vd_g_MMTextWriteImmTX1(GT_CHG_VR_M))
#else
#define vd_MMTEXT_WRITE_INVALID_STA4_CHG_AUDIO_M()      (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_LST_CHG_CMN_M()         (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_FAV_CHG_M()             (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_HST_CHG_M()             (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_CD_CHG_M()              (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_CT_CHG_VR_M()           (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_RT_CHG_VR_M()           (vdp_PTR_NA)
#define vd_MMTEXT_WRITE_INVALID_GT_CHG_VR_M()           (vdp_PTR_NA)
#endif

/* CCOMへの初期値書き込み */
#if 0   /* BEV BSW provisionally */
#define vd_g_MMTEXT_SET_INIT_MSG_METMS02()              (vd_g_MMLibSetInitMsg(METMS02))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS03()              (vd_g_MMLibSetInitMsg(METMS03))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS04()              (vd_g_MMLibSetInitMsg(METMS04))
#define vd_g_MMTEXT_STOP_TX_MSG_METMS05()               (vd_g_MMLibStopTxMsg(METMS05))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS06()              (vd_g_MMLibSetInitMsg(METMS06))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS10()              (vd_g_MMLibSetInitMsg(METMS10))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS11()              (vd_g_MMLibSetInitMsg(METMS11))
#define vd_g_MMTEXT_SET_INIT_MSG_METMS13()              (vd_g_MMLibSetInitMsg(METMS13))
#endif


#define u1_MMTEXT_CHECKMODESTATE(u1_mode)               (u1_g_MMVar_CheckModeState(u1_mode))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/* メッセージラベル情報テーブル */
#if 0   /* BEV BSW provisionally */
static const U2 u2_tbl_msg_label_info[MMTEXT_KIND_MAX] =
{
    (U2)MMTEXT_AVNMS72_MSG                 /* MMTEXT_KIND_AVNMS72 */
};
#endif

/* 外部関数情報テーブル */
static const struct
{
    FUNC_MMTEXT_CHECK_MODE fp_mode_valid_func;                                  /* モード情報有効値判定関数                          */
}
st_tbl_extfunc_info[MMTEXT_KIND_MAX] =
{
    {&u1_g_MMVar_CheckModeState}         /* MMTEXT_KIND_AVNMS72 */
};

#endif /* MMTEXT_PRM */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  mmtext.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
