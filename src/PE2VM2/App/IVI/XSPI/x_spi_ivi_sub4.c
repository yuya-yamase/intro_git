/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB4_C_MAJOR                   (0)
#define XSPI_IVI_SUB4_C_MINOR                   (0)
#define XSPI_IVI_SUB4_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub4_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB4_C_MAJOR != XSPI_IVI_SUB4_H_MAJOR) || \
     (XSPI_IVI_SUB4_C_MINOR != XSPI_IVI_SUB4_H_MINOR) || \
     (XSPI_IVI_SUB4_C_PATCH != XSPI_IVI_SUB4_H_PATCH))
#error "x_spi_ivi_sub4.c and x_spi_ivi_sub4.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB4_C_MAJOR != XSPI_IVI_SUB4_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB4_C_MINOR != XSPI_IVI_SUB4_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB4_C_PATCH != XSPI_IVI_SUB4_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub4.c and x_spi_ivi_sub4_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SFT_08                     ( 8U)
#define XSPI_IVI_SFT_16                     (16U)
#define XSPI_IVI_SFT_24                     (24U)

#define XSPI_IVI_CAN_NUM_DLC                (3U)
#define XSPI_IVI_CAN_DLC_08                 (0U)
#define XSPI_IVI_CAN_DLC_32                 (1U)
#define XSPI_IVI_CAN_DLC_64                 (2U)

#define XSPI_IVI_CAN_64                     (64U)

#define XSPI_IVI_CMS_1                      (   1U)
#define XSPI_IVI_CMS_128                    ( 128U)

#define XSPI_IVI_CAN_DATA_80                (  80U)
#define XSPI_IVI_CAN_DATA_MAX               (3356U)     /* サブフレーム4領域(3500byte) - コマンド,メッセージヘッダ(8+8byte) - CMS領域(128byte) */

#define XSPI_IVI_CANCOMMAND_ID              (0x434E4454U)
#define XSPI_IVI_CANCOMMAND_BUS_REQ         (0x03U)
#define XSPI_IVI_CANCOMMAND_SEND            (0x04U)

#define XSPI_IVI_CAN_COMMNDDATA_SIZE        (24U)
#define XSPI_IVI_CAN_BUSSTS_SIZE            (9U)
#define XSPI_IVI_CAN_COMMAND_BUF_MAX        (128U)
#define XSPI_IVI_CAN_COMMAND_SIZE_MAX       (256U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_act;
    U1                          u1_dlc;
	U4                          u4_flame_id;
}ST_XSPI_IVI_MSG2POSLEN;

/* CANIDと対応するAubist定義のペア */
typedef struct {
    U4                          u4_canid;
    U4                          u4_aubist;
} ST_XSPI_IVI_CANID_PAIR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_sp_Xspi_Ivi_CanBusSts2M[4];
static U1       u1_sp_Xspi_Ivi_CanBusSts5M[4];
static U1       u1_sp_Xspi_Ivi_CanBusSts2M_pre[4];
static U1       u1_sp_Xspi_Ivi_CanBusSts5M_pre[4];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviSub4CanAna(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN);
static U2       u2_s_XspiIviSub4SendCanCmd(U1 * u1_ap_buf);
static U2       u2_s_XspiIviSub4SendCanMsg(U1 * u1_ap_buf, const U2 u2_a_COM_LEN);
static void     vd_s_XspiIviCANGWStuckBuff(const U4 u4_a_TIME, const U4 u4_a_MSG, const U1 u1_a_DLC, const U1 * u1_a_SRC);
static U4       u4_s_XspiIviBinarySearch(U4 canid);
static void     vd_s_XspiIviCANCommandStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub4Init(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub4Init(void)
{
    /*CANBusステータスを取得するIF不明のため暫定で正常動作固定とする*/
    /*初期化状態で初期値セットの必要あり*/
    /*2MBusSts*/
    u1_sp_Xspi_Ivi_CanBusSts2M[0] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M[1] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M[2] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M[3] = (U1)3U;   /*通常動作状態*/
    u1_sp_Xspi_Ivi_CanBusSts2M_pre[0] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M_pre[1] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M_pre[2] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts2M_pre[3] = (U1)3U;   /*通常動作状態*/

    /*5MBusSts*/
    u1_sp_Xspi_Ivi_CanBusSts5M[0] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M[1] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M[2] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M[3] = (U1)3U;   /*通常動作状態*/
    u1_sp_Xspi_Ivi_CanBusSts5M_pre[0] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M_pre[1] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M_pre[2] = (U1)0U;   /*正常*/
    u1_sp_Xspi_Ivi_CanBusSts5M_pre[3] = (U1)3U;   /*通常動作状態*/
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub4Ana(const U1 * u1_ap_XSPI_ADD)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    サブフレーム4(CAN Data/Repro/LCAN Data)データ解析処理                                                              */
/*  Arguments:      u1_ap_XSPI_ADD : XSPI受信データ サブフレーム4開始位置ポインタ                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub4Ana(const U1 * u1_ap_XSPI_ADD)
{
    static const U1 u1_s_ID_CAN_DARA_SOC2MCU        = (U1)0x02U;
    static const U1 u1_s_ID_REPRO_DARA_SOC2MCU      = (U1)0x03U;
    static const U1 u1_s_ID_LCAN_DARA_SOC2MCU       = (U1)0x05U;

    //U2          u2_t_frame_counter;     /* Sub Frame Counter 未使用のためコメントアウト */
    //U2          u2_t_frame_num;         /* Sub Frame 個数 未使用のためコメントアウト */
    U2          u2_t_dt_len;            /* 有効データ長 */
    U1          u1_t_dt_type;           /* データ種別 */

    /* サブフレームヘッダ解析処理 */
    //u2_t_frame_counter  = (U2)((u1_ap_XSPI_ADD[0] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[1]);
    //u2_t_frame_num      = (U2)((u1_ap_XSPI_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[3]);
    u2_t_dt_len         = (U2)((u1_ap_XSPI_ADD[4] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[5]);
    u1_t_dt_type        = u1_ap_XSPI_ADD[6];

    if (u1_t_dt_type == u1_s_ID_CAN_DARA_SOC2MCU) {
        /* CAN Data解析処理 */
        vd_s_XspiIviSub4CanAna(&u1_ap_XSPI_ADD[8], u2_t_dt_len);
    }
    else if (u1_t_dt_type == u1_s_ID_REPRO_DARA_SOC2MCU) {
        /* Repro Data解析処理 */
        /* skip */
    }
    else if (u1_t_dt_type == u1_s_ID_LCAN_DARA_SOC2MCU) {
        /* LCAN Data解析処理 */
        /* skip */
    }
    else {
        /* データ種別異常 */
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub4CanAna(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    サブフレーム4 CAN Data 解析処理                                                                                    */
/*  Arguments:      u1_ap_SUB4_ADD : サブフレーム4 CAN Data開始位置                                                                    */
/*                  u2_a_DTLEN     : 有効データ長                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub4CanAna(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN)
{
    const U1 *  u1_tp_CNDT;                             /* CAN Command Data Field 先頭位置 */
    const U1 *  u1_tp_CNMS_HDR;                         /* CAN Message Header Field 先頭位置 */
    const U1 *  u1_tp_CNMS_CMS;                         /* CAN Message Field CMS先頭位置 */
    const U1 *  u1_tp_CNMS_MSG;                         /* CAN Message Field CANデータ先頭位置 */
    U4          u4_t_com_ID;                            /* CAN Command 識別値 未使用のためコメントアウト */
    //U2          u2_t_com_num;                           /* CAN Command コマンド数 未使用のためコメントアウト */
    U2          u2_t_com_len;                           /* CAN Command データ長 */
    //U4          u4_t_msg_ID;                            /* CAN Message 識別値 未使用のためコメントアウト */
    U2          u2_t_msg_num;                           /* CAN Message メッセージ数 */
    //U2          u2_t_msg_len;                           /* CAN Message データ長 未使用のためコメントアウト */
    U4          u4_t_msg_canid;                         /* CAN Message CAN ID */
    U1          u1_t_msg_dlc;                           /* CAN Message DLC  */
    U1          u1_tp_can_data[XSPI_IVI_CAN_DATA_80];   /* CAN Message CANデータ */
    U4          u4_t_loop;
    U4          u4_t_msg_aubistid;
    U2          u2_t_datatype;                          /* CAN Command データタイプ*/
    U2          u2_t_cancommandbuf;                     /* CAN Command データバッファ*/
    U2          u2_t_cancommandsize;                    /* CAN Command データサイズ*/

    /* CAN Command Header Field 解析処理 */
    //u4_t_com_ID     = (U4)((u1_ap_SUB4_ADD[0] << XSPI_IVI_SFT_24) | (u1_ap_SUB4_ADD[1] << XSPI_IVI_SFT_16) | (u1_ap_SUB4_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_SUB4_ADD[3]);
    //u2_t_com_num    = (U2)((u1_ap_SUB4_ADD[4] << XSPI_IVI_SFT_08) | u1_ap_SUB4_ADD[5]);
    u2_t_com_len    = (U2)((u1_ap_SUB4_ADD[6] << XSPI_IVI_SFT_08) | u1_ap_SUB4_ADD[7]);
    u2_t_cancommandbuf = (U2)0U;

    /* CAN Command Data Field 解析処理 */
    u1_tp_CNDT = &u1_ap_SUB4_ADD[XSPI_IVI_HEADER];
    u4_t_com_ID     = (U4)((u1_tp_CNDT[0] << XSPI_IVI_SFT_24) | (u1_tp_CNDT[1] << XSPI_IVI_SFT_16) | (u1_tp_CNDT[2] << XSPI_IVI_SFT_08) | u1_tp_CNDT[3]);

    while(u4_t_com_ID == (U4)XSPI_IVI_CANCOMMAND_ID){
        u2_t_datatype = u1_tp_CNDT[u2_t_cancommandbuf + 6U];
        u2_t_cancommandsize = (U2)((u1_tp_CNDT[u2_t_cancommandbuf + 4U] << XSPI_IVI_SFT_08) | u1_tp_CNDT[u2_t_cancommandbuf + 5U]);
        switch (u2_t_datatype)
        {
        case XSPI_IVI_CANCOMMAND_BUS_REQ:
            /* BUSステータス要求に対する応答 */
            vd_g_XspiIviCANBusSend();
            break;
        default:
            break;
        }
        u2_t_cancommandbuf = u2_t_cancommandbuf + u2_t_cancommandsize + (U2)XSPI_IVI_HEADER;
        u4_t_com_ID     = (U4)((u1_tp_CNDT[u2_t_cancommandbuf] << XSPI_IVI_SFT_24) | (u1_tp_CNDT[u2_t_cancommandbuf + 1U] << XSPI_IVI_SFT_16) | (u1_tp_CNDT[u2_t_cancommandbuf + 2U] << XSPI_IVI_SFT_08) | u1_tp_CNDT[u2_t_cancommandbuf + 3U]);
    }

    /* CAN Message Header Field 解析処理 */
    u1_tp_CNMS_HDR = &u1_tp_CNDT[u2_t_com_len];

    //u4_t_msg_ID     = (U4)((u1_tp_CNMS_HDR[0] << XSPI_IVI_SFT_24) | (u1_tp_CNMS_HDR[1] << XSPI_IVI_SFT_16) | (u1_tp_CNMS_HDR[2] << XSPI_IVI_SFT_08) | u1_tp_CNMS_HDR[3]);
    u2_t_msg_num    = (U2)((u1_tp_CNMS_HDR[4] << XSPI_IVI_SFT_08) | u1_tp_CNMS_HDR[5]);
    //u2_t_msg_len    = (U2)((u1_tp_CNMS_HDR[6] << XSPI_IVI_SFT_08) | u1_tp_CNMS_HDR[7]);

    /* CAN Message Data Field 解析処理 */
    /* CMS,CANデータの先頭位置にポインタセット */
    u1_tp_CNMS_CMS  = &u1_tp_CNMS_HDR[XSPI_IVI_HEADER];
    u1_tp_CNMS_MSG  = &u1_tp_CNMS_CMS[XSPI_IVI_CMS_128];

    /* CAN受信用バッファのクリア */
    vd_g_MemfillU1(&u1_tp_can_data[0], (U1)0U, (U4)XSPI_IVI_CAN_DATA_80);

    for (u4_t_loop = 0; u4_t_loop < u2_t_msg_num; u4_t_loop++) {
        /* CAN ID,DLCの読出し */
        u4_t_msg_canid  = (U4)(((u1_tp_CNMS_MSG[4] << XSPI_IVI_SFT_24) | (u1_tp_CNMS_MSG[5] << XSPI_IVI_SFT_16) | (u1_tp_CNMS_MSG[6] << XSPI_IVI_SFT_08) | u1_tp_CNMS_MSG[7]) & 0x7FFFFFFFU);
        if((u1_tp_CNMS_MSG[4] & (U1)0x80U) == (U4)0x00){
            u4_t_msg_canid = u4_t_msg_canid >> 20U;
        }
        u1_t_msg_dlc    = (U1)(u1_tp_CNMS_MSG[8]);
        /* DLCぶんCANデータを読出し */
        vd_g_MemcpyU1(&u1_tp_can_data[0], &u1_tp_CNMS_MSG[9], (U4)u1_t_msg_dlc);

        /* CANID → AubistIDに変換する */
        u4_t_msg_aubistid = u4_s_XspiIviBinarySearch(u4_t_msg_canid);
        
        if(u4_t_msg_aubistid != (U4)0xFFFFFFFFU){
        /* フレーム送信処理 */
            (void)Com_SendIPDU((PduIdType)u4_t_msg_aubistid, &u1_tp_can_data[0] );
        }

        /* 読み出したデータ分ポインタを移動する */
        u1_tp_CNMS_MSG  = &u1_tp_CNMS_MSG[u1_tp_CNMS_CMS[0]];
        u1_tp_CNMS_CMS  = &u1_tp_CNMS_CMS[1];
    }
}

/*===================================================================================================================================*/
/*  static U4              u4_s_XspiIviBinarySearch(U4 canid)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANID変換処理(受信ID⇒Aubist定義ID)                                                                                */
/*  Arguments:      u4_a_CANID   : CANID                                                                                             */
/*  Return:         u4_t_ret     : Aubist定義のCANID(MSG_*******_TXCH*)                                                               */
/*===================================================================================================================================*/
static U4              u4_s_XspiIviBinarySearch(U4 u4_a_CANID) {
    // ソート済みのCANIDとAubist定義のマッピング
    static const ST_XSPI_IVI_CANID_PAIR canid_aubist_map[] = {
        {0x00000121,    MSG_AVN1S38_TXCH0},
        {0x00000126,    MSG_AVN1S34_TXCH0},
        {0x00000141,    MSG_AVN1SG7_TXCH0},
        {0x0000014C,    MSG_AVN1S71_TXCH0},
        {0x0000017F,    MSG_AVN1S32_TXCH0},
        {0x00000185,    MSG_AVN1SD4_TXCH0},
        {0x000001A1,    MSG_AVN1SD6_TXCH0},
        {0x000001A2,    MSG_AVN1SD7_TXCH0},
        {0x000001A3,    MSG_AVN1SF6_TXCH0},
        {0x000001A5,    MSG_AVN1SF4_TXCH0},
        {0x000001A7,    MSG_AVN1SF5_TXCH0},
        {0x000001A8,    MSG_AVN1SE9_TXCH0},
        {0x000001A9,    MSG_AVN1SF1_TXCH0},
        {0x000001AB,    MSG_AVN1SF2_TXCH0},
        {0x000001AC,    MSG_AVN1SF3_TXCH0},
        {0x000001AD,    MSG_AVN1SE3_TXCH0},
        {0x000001AE,    MSG_AVN1SE8_TXCH0},
        {0x000001AF,    MSG_AVN1SE4_TXCH0},
        {0x000001B0,    MSG_AVN1SE5_TXCH0},
        {0x000001B3,    MSG_AVN1SE6_TXCH0},
        {0x000001B4,    MSG_AVN1SE7_TXCH0},
        {0x000001B5,    MSG_AVN1SE2_TXCH0},
        {0x000001B7,    MSG_AVN1SE1_TXCH0},
        {0x000001B8,    MSG_AVN1SD8_TXCH0},
        {0x000001B9,    MSG_AVN1SD9_TXCH0},
        {0x000001BD,    MSG_AVN1S52_TXCH0},
        {0x000001EC,    MSG_AVN1SA6_TXCH0},
        {0x000001F2,    MSG_AVN1SB9_TXCH0},
        {0x000001FC,    MSG_AVN1S40_TXCH0},
        {0x000001FD,    MSG_AVN1S41_TXCH0},
        {0x000001FE,    MSG_AVN1S42_TXCH0},
        {0x000001FF,    MSG_AVN1S43_TXCH0},
        {0x000002AA,    MSG_AVN1S73_TXCH0},
        {0x000002D2,    MSG_AVN1SB7_TXCH0},
        {0x000002D3,    MSG_AVN1SB8_TXCH0},
        {0x000002D4,    MSG_AVN1SC1_TXCH0},
        {0x000002D5,    MSG_AVN1SC2_TXCH0},
        {0x000002D6,    MSG_AVN1SC3_TXCH0},
        {0x000002D7,    MSG_AVN1SC4_TXCH0},
        {0x000002DF,    MSG_AVN1SC5_TXCH0},
        {0x000002E0,    MSG_AVN1SC6_TXCH0},
        {0x000002E1,    MSG_AVN1SC7_TXCH0},
        {0x000002E2,    MSG_AVN1SC8_TXCH0},
        {0x000002E3,    MSG_AVN1SH1_TXCH0},
        {0x000002E7,    MSG_AVN1SG8_TXCH0},
        {0x000002E8,    MSG_AVN1SG9_TXCH0},
        {0x000002EF,    MSG_AVN1SC9_TXCH0},
        {0x000002F0,    MSG_AVN1SD1_TXCH0},
        {0x000002F2,    MSG_AVN1SD2_TXCH0},
        {0x000002F5,    MSG_AVN1SD3_TXCH0},
        {0x000002F6,    MSG_AVN1SD5_TXCH0},
        {0x000002F7,    MSG_AVN1SF7_TXCH0},
        {0x000002F8,    MSG_AVN1SF8_TXCH0},
        {0x000002FA,    MSG_AVN1SF9_TXCH0},
        {0x000002FB,    MSG_AVN1SG1_TXCH0},
        {0x0000030E,    MSG_AVN1S67_TXCH0},
        {0x0000030F,    MSG_AVN1S68_TXCH0},
        {0x00000313,    MSG_AVN1SB2_TXCH0},
        {0x0000031A,    MSG_AVN1S30_TXCH0},
        {0x0000031D,    MSG_AVN1SA1_TXCH0},
        {0x00000322,    MSG_AVN1SG4_TXCH0},
        {0x0000033A,    MSG_AVN1SG3_TXCH0},
        {0x00000345,    MSG_AVN1S94_TXCH0},
        {0x00000346,    MSG_AVN1S95_TXCH0},
        {0x0000034E,    MSG_AVN1S61_TXCH0},
        {0x00000351,    MSG_CDC1S04_TXCH0},
        {0x0000035A,    MSG_AVN1SA7_TXCH0},
        {0x0000035B,    MSG_AVN1S62_TXCH0},
        {0x00000384,    MSG_AVN1S01_TXCH0},
        {0x00000386,    MSG_AVN1S03_TXCH0},
        {0x00000387,    MSG_AVN1S05_TXCH0},
        {0x00000388,    MSG_AVN1S06_TXCH0},
        {0x00000389,    MSG_AVN1S08_TXCH0},
        {0x0000038E,    MSG_AVN1S04_TXCH0},
        {0x0000038F,    MSG_AVN1S07_TXCH0},
        {0x000003A6,    MSG_AVN1S46_TXCH0},
        {0x000003A7,    MSG_AVN1S47_TXCH0},
        {0x000003A8,    MSG_AVN1S70_TXCH0},
        {0x000003C0,    MSG_AVN1S99_TXCH0},
        {0x000003C2,    MSG_AVN1SA9_TXCH0},
        {0x000003C4,    MSG_AVN1S78_TXCH0},
        {0x000003C9,    MSG_AVN1S63_TXCH0},
        {0x000003D0,    MSG_AVN1S76_TXCH0},
        {0x000003D9,    MSG_AVN1S97_TXCH0},
        {0x000003E4,    MSG_AVN1S98_TXCH0},
        {0x000003E6,    MSG_AVN1S11_TXCH0},
        {0x000003F1,    MSG_AVN1SA8_TXCH0},
        {0x000003F2,    MSG_AVN1SB6_TXCH0},
        {0x000003FD,    MSG_AVN1S77_TXCH0},
        {0x0000040E,    MSG_AVN1SB1_TXCH0},
        {0x0000042E,    MSG_AVN1S33_TXCH0},
        {0x00000434,    MSG_AVN1S20_TXCH0},
        {0x00000435,    MSG_AVN1S21_TXCH0},
        {0x00000436,    MSG_AVN1S22_TXCH0},
        {0x00000437,    MSG_AVN1S23_TXCH0},
        {0x0000043E,    MSG_AVN1SG5_TXCH0},
        {0x00000490,    MSG_AVN1S64_TXCH0},
        {0x00000515,    MSG_AVN1SB3_TXCH0},
        {0x0000051A,    MSG_AVN1SB4_TXCH0},
        {0x0000051B,    MSG_AVN1SB5_TXCH0},
        {0x0000051D,    MSG_AVN1S44_TXCH0},
        {0x0000051F,    MSG_AVN1S65_TXCH0},
        {0x00000521,    MSG_AVN1S69_TXCH0},
        {0x0000052A,    MSG_AVN1S66_TXCH0},
        {0x0000058A,    MSG_AVN1S39_TXCH0},
        {0x0000060C,    MSG_AVN1SG6_TXCH0}
    };
    static const U4 u4_s_XSPI_IVI_BS_HALF   = (U4)2U;
    static const U4 u4_s_XSPI_IVI_BS_SFT_1  = (U4)1U;

    U4  u4_t_ret;
    U4  u4_t_size;
    U4  u4_t_left;
    U4  u4_t_right;
    U4  u4_t_mid;

    u4_t_ret = (U4)0xFFFFFFFFU;
    u4_t_size = sizeof(canid_aubist_map) / sizeof(ST_XSPI_IVI_CANID_PAIR);
    u4_t_left = (U4)0U;
    u4_t_right = u4_t_size - u4_s_XSPI_IVI_BS_SFT_1;

    while (u4_t_left <= u4_t_right) {
        u4_t_mid = u4_t_left + (u4_t_right - u4_t_left) / u4_s_XSPI_IVI_BS_HALF;

        /* CANIDが中央の要素と一致する場合 */
        if (canid_aubist_map[u4_t_mid].u4_canid == u4_a_CANID) {
            u4_t_ret = canid_aubist_map[u4_t_mid].u4_aubist;
            break;
        }

        /* CANIDが中央の要素より小さい場合 */
        if (canid_aubist_map[u4_t_mid].u4_canid > u4_a_CANID) {
            u4_t_right = u4_t_mid - u4_s_XSPI_IVI_BS_SFT_1;
        } else {
            u4_t_left = u4_t_mid + u4_s_XSPI_IVI_BS_SFT_1;
        }
    }
 
    return (u4_t_ret);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub4Send(U1 * u1_ap_xspi_add)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    サブフレーム4(CAN Data/Repro/LCAN Data)用送信データ作成処理                                                         */
/*  Arguments:      u1_ap_xspi_add : サブフレーム4データ書き込み位置へのポインタ                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub4Send(U1 * u1_ap_xspi_add)
{
    U2          u2_t_com_len;                           /* CAN Command Field有効データ長 最大256byte */
    U2          u2_t_msg_len;                           /* CAN Message Field有効データ長 最大3500Byte - CANCommandFieldで使用するサイズ */
    U1          u1_tp_sub4_header[XSPI_IVI_HEADER];     /* SubFrameHeader */

    /* CAN Data/Repro/LCAN Dataを何かしらの優先度に従って分岐させる必要があるが、本ソフトではCANのみ対応のためSkipする */
    
    /* CAN Data向け処理 */
    /* CAN Command Field処理 */
    u2_t_com_len = u2_s_XspiIviSub4SendCanCmd(&u1_ap_xspi_add[XSPI_IVI_HEADER]);
    /* CAN Message Field処理 */
    u2_t_msg_len = u2_s_XspiIviSub4SendCanMsg(&u1_ap_xspi_add[XSPI_IVI_HEADER + u2_t_com_len], u2_t_com_len);
    /* CAN DataのSubFrameHeaderの付与 */
    u1_tp_sub4_header[0] = (U1)0x00U;
    u1_tp_sub4_header[1] = (U1)0x01U;
    u1_tp_sub4_header[2] = (U1)0x00U;
    u1_tp_sub4_header[3] = (U1)0x01U;
    u1_tp_sub4_header[4] = (U1)(((u2_t_com_len + u2_t_msg_len) & 0xFF00U)       >> XSPI_IVI_SFT_08);
    u1_tp_sub4_header[5] = (U1)(((u2_t_com_len + u2_t_msg_len) & 0x00FFU));/*   >> 0) */
    u1_tp_sub4_header[6] = (U1)0x01;    /* 01h：CAN Data受信(MCU→SoC) */
    u1_tp_sub4_header[7] = (U1)0x01;

    vd_g_MemcpyU1(&u1_ap_xspi_add[0], &u1_tp_sub4_header[0], (U4)XSPI_IVI_HEADER);

    /* Repro向け処理 */
    /* skip */

    /* LCAN Data向け処理 */
    /* skip */
}

/*===================================================================================================================================*/
/*  static U2              u2_s_XspiIviSub4SendCanCmd(U1 * u1_ap_buf)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CAN Command Field 向けデータ作成処理                                                                               */
/*  Arguments:      u1_ap_buf    : CAN Command Field データ格納開始位置                                                                */
/*  Return:         u2_t_com_len : CAN Command Field データ長                                                                         */
/*===================================================================================================================================*/
static U2              u2_s_XspiIviSub4SendCanCmd(U1 * u1_ap_buf)
{
    U1          u1_tp_can_com_header[XSPI_IVI_HEADER];      /* CAN Command Header Field */
    U2          u2_t_com_num;                               /* コマンド数 */
    U2          u2_t_com_len;                               /* データ長 Max(256-8)byte */
    U4          u4_t_loop;
    U1          u1_t_data_size_ref;
    U1          u1_t_data_size;
    U1          u1_t_rslt;

    u2_t_com_num = (U2)0x0000U;
    u2_t_com_len = (U2)0x0000U;
    u1_t_data_size = (U2)0U;

    /* CAN Commandデータ格納処理 */
    /* skip */
    /* キューから抜き出す処理*/
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_IVI_CAN_COMMAND_BUF_MAX; u4_t_loop++) {
        u1_t_data_size_ref = u1_g_XspiIviQueueGetCanCommandSizeRef();
        /*256byte-キューに入ってるデータサイズ-CAN CommandHeaderサイズ*/
        if(u2_t_com_len <= (U2)XSPI_IVI_CAN_COMMAND_SIZE_MAX - (U2)u1_t_data_size_ref - (U2)XSPI_IVI_HEADER) {
            u1_t_rslt = u1_g_XspiIviQueueGetCanCommandSize(&u1_t_data_size);
            if (u1_t_rslt == (U1)TRUE) {
                u2_t_com_num++;                                                      /* CANコマンド読み出し個数+1 */
                u2_t_com_len = u2_t_com_len + (U2)u1_t_data_size;        /* CANコマンドサイズに読み出したCANコマンドサイズ加算 */
            }
            else {
                /* CANコマンドデータサイズ読み出し失敗でループ終了 */
                u4_t_loop = (U4)0xFFFFU;
            }
        }
        else {
            /* 読み出しサイズ上限のためループ終了 */
            u4_t_loop = (U4)0xFFFFU;
        }
    }

    /* CAN Command Header Fieldの付与 */
    u1_tp_can_com_header[0] = (U1)0x43U;
    u1_tp_can_com_header[1] = (U1)0x4eU;
    u1_tp_can_com_header[2] = (U1)0x43U;
    u1_tp_can_com_header[3] = (U1)0x4dU;
    u1_tp_can_com_header[4] = (U1)((u2_t_com_num & 0xFF00U)     >> XSPI_IVI_SFT_08);
    u1_tp_can_com_header[5] = (U1)((u2_t_com_num & 0x00FFU));/* >> 0 */
    u1_tp_can_com_header[6] = (U1)((u2_t_com_len & 0xFF00U)     >> XSPI_IVI_SFT_08);
    u1_tp_can_com_header[7] = (U1)((u2_t_com_len & 0x00FFU));/* >> 0 */

    vd_g_MemcpyU1(&u1_ap_buf[0], &u1_tp_can_com_header[0], (U4)XSPI_IVI_HEADER);
    vd_g_XspiIviQueueGetCanCommandData(&u1_ap_buf[8], u2_t_com_len);

    u2_t_com_len = u2_t_com_len + (U2)XSPI_IVI_HEADER;

    return (u2_t_com_len);
}

/*===================================================================================================================================*/
/*  static U2              u2_s_XspiIviSub4SendCanMsg(U1 * u1_ap_buf, const U2 u2_a_COM_LEN)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CAN Message Field 向けデータ作成処理                                                                              */
/*  Arguments:      u1_ap_buf       : CAN Message Field データ格納開始位置                                                            */
/*                  u2_a_COM_LEN    : CAN Command Field データ長                                                                     */
/*  Return:         u2_t_candt_size : CAN Message Field データ長                                                                     */
/*===================================================================================================================================*/
static U2              u2_s_XspiIviSub4SendCanMsg(U1 * u1_ap_buf, const U2 u2_a_COM_LEN)
{
    U1 *        u1_tp_cms;                                  /* CMS領域開始位置 */
    U1 *        u1_tp_candt;                                /* CAN Data領域開始位置 */

    U1          u1_t_rslt;                                  /* CMS読み出し結果 */
    U4          u4_t_loop;
    U1          u1_t_cms_num;                               /* CMS読み出し個数 */
    U2          u2_t_candt_size;                            /* CANメッセージデータサイズ */
    U1          u1_tp_can_msg_header[XSPI_IVI_HEADER];      /* CAN Message Header Field */

    u1_tp_cms               = &u1_ap_buf[XSPI_IVI_HEADER];  /* Header 0-7byte, CMS 8-135byte, CANデータ 136-*byte */
    u1_tp_candt             = &u1_ap_buf[XSPI_IVI_HEADER + XSPI_IVI_CMS_128];
    u1_t_cms_num            = (U1)0U;
    u2_t_candt_size         = (U2)0U;

    for (u4_t_loop = 0; u4_t_loop < (U4)XSPI_IVI_CMS_128; u4_t_loop++){
        /* CMS合計 <= 3356byte - CANコマンドフィールドのデータ長 - CANデータ最大サイズ だったら読出し実施 */
        if (u2_t_candt_size <= ((U2)XSPI_IVI_CAN_DATA_MAX - u2_a_COM_LEN - (U2)XSPI_IVI_CAN_DATA_80)) {
            u1_t_rslt = u1_g_XspiIviQueueGetCms(&u1_tp_cms[u4_t_loop]);

            if (u1_t_rslt == (U1)TRUE) {
                u1_t_cms_num++;                                             /* CMS読み出し個数+1 */
                u2_t_candt_size = u2_t_candt_size + u1_tp_cms[u4_t_loop];   /* CANデータサイズに読み出したCMS加算 */
            }
            else {
                /* CMS読み出し失敗でループ終了 */
                u4_t_loop = (U4)0xFFFFU;
            }
        }
        else {
            /* 読み出しサイズ上限のためループ終了 */
            u4_t_loop = (U4)0xFFFFU;
        }
    }
    /* CAMメッセージデータの読出しと格納 */
    vd_g_XspiIviQueueGetCandata(&u1_tp_candt[0], u2_t_candt_size);

    u2_t_candt_size = u2_t_candt_size + (U2)128U;
    /* CAM Command Header Field の付与 */
    u1_tp_can_msg_header[0] = (U1)0x43U;
    u1_tp_can_msg_header[1] = (U1)0x4eU;
    u1_tp_can_msg_header[2] = (U1)0x4dU;
    u1_tp_can_msg_header[3] = (U1)0x53U;
    u1_tp_can_msg_header[4] = (U1)0x00;    /* CANメッセージ数は最大128であり、[5]に収まるので固定で0を格納 */
    u1_tp_can_msg_header[5] = (U1)u1_t_cms_num;
    u1_tp_can_msg_header[6] = (U1)((u2_t_candt_size & 0xFF00U)     >> XSPI_IVI_SFT_08);
    u1_tp_can_msg_header[7] = (U1)((u2_t_candt_size & 0x00FFU));/* >> 0 */

    vd_g_MemcpyU1(&u1_ap_buf[0], &u1_tp_can_msg_header[0], (U4)XSPI_IVI_HEADER);

	u2_t_candt_size = u2_t_candt_size +XSPI_IVI_HEADER;
	
    return (u2_t_candt_size);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviCANGWPushPDU(const U2 u2_a_MSG)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CAN受信によるユーザフック処理                                                                                      */
/*  Arguments:      u2_a_MSG : 受信したCANフレーム                                                                                    */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviCANGWPushPDU(const U2 u2_a_MSG)
{
    static const U2 u2_s_XSPI_IVI_CANGW_MIN      = (U2)MSG_ABG1D50_RXCH0;
    static const U2 u2_s_XSPI_IVI_CANGW_MAX      = (U2)MSG_ZN21S72_RXCH0;

    static const ST_XSPI_IVI_MSG2POSLEN st_sp_LCOM_SPI_MSG2POSLEN[] = {
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4AC00000},       /*      0:MSG_ABG1D50_RXCH0    (106U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4BC00000},       /*      1:MSG_ABG1D51_RXCH0    (107U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3B100000},       /*      2:MSG_ABG1S01_RXCH0    (108U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1D800000},       /*      3:MSG_ABG1S04_RXCH0    (109U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1D600000},       /*      4:MSG_ABG1S09_RXCH0    (110U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4B800000},       /*      5:MSG_ACN1D50_RXCH0    (111U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3A100000},       /*      6:MSG_ACN1S03_RXCH0    (112U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x38100000},       /*      7:MSG_ACN1S04_RXCH0    (113U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38200000},       /*      8:MSG_ACN1S05_RXCH0    (114U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3B000000},       /*      9:MSG_ACN1S07_RXCH0    (115U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40700000},       /*     10:MSG_ACN1S15_RXCH0    (116U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40800000},       /*     11:MSG_ACN1S16_RXCH0    (117U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35400000},       /*     12:MSG_ACN1S22_RXCH0    (118U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x25500000},       /*     13:MSG_ACN1S25_RXCH0    (119U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x50600000},       /*     14:MSG_ACN1S29_RXCH0    (120U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x59400000},       /*     15:MSG_ADC1S06_RXCH0    (121U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20700000},       /*     16:MSG_ADC1S13_RXCH0    (122U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20800000},       /*     17:MSG_ADC1S14_RXCH0    (123U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20A00000},       /*     18:MSG_ADC1S17_RXCH0    (124U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x61300000},       /*     19:MSG_ADC1S19_RXCH0    (125U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x1C700000},       /*     20:MSG_ADC1S20_RXCH0    (126U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20B00000},       /*     21:MSG_ADC1S23_RXCH0    (127U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x14400000},       /*     22:MSG_ADC1S27_RXCH0    (128U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34900000},       /*     23:MSG_ADC1S30_RXCH0    (129U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1C000000},       /*     24:MSG_ADC1S31_RXCH0    (130U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x24700000},       /*     25:MSG_ADU1S02_RXCH0    (131U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1F500000},       /*     26:MSG_ADU1S03_RXCH0    (132U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1F000000},       /*     27:MSG_ADU1S05_RXCH0    (133U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x22E00000},       /*     28:MSG_ADU1S06_RXCH0    (134U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20E00000},       /*     29:MSG_ADU1S07_RXCH0    (135U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16100000},       /*     30:MSG_ADU1S18_RXCH0    (136U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16200000},       /*     31:MSG_ADU1S19_RXCH0    (137U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16300000},       /*     32:MSG_ADU1S20_RXCH0    (138U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16600000},       /*     33:MSG_ADU1S21_RXCH0    (139U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16700000},       /*     34:MSG_ADU1S22_RXCH0    (140U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16800000},       /*     35:MSG_ADU1S23_RXCH0    (141U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16900000},       /*     36:MSG_ADU1S24_RXCH0    (142U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16A00000},       /*     37:MSG_ADU1S25_RXCH0    (143U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16B00000},       /*     38:MSG_ADU1S26_RXCH0    (144U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16C00000},       /*     39:MSG_ADU1S27_RXCH0    (145U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16D00000},       /*     40:MSG_ADU1S28_RXCH0    (146U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x07200000},       /*     41:MSG_ARS1S01_RXCH0    (147U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1DD00000},       /*     42:MSG_ARS1S90_RXCH0    (148U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x21400000},       /*     43:MSG_BAT1E41_RXCH0    (149U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x16E00000},       /*     44:MSG_BAT1E45_RXCH0    (150U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x26E00000},       /*     45:MSG_BAT1ED1_RXCH0    (151U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x0F300000},       /*     46:MSG_BAT1ED4_RXCH0    (152U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1BA00000},       /*     47:MSG_BAT1ED5_RXCH0    (153U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1EF00000},       /*     48:MSG_BAT1EDA_RXCH0    (154U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x27200000},       /*     49:MSG_BAT1EDB_RXCH0    (155U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3E500000},       /*     50:MSG_BAT1S01_RXCH0    (156U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x12400000},       /*     51:MSG_BAT1S08_RXCH0    (157U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x15500000},       /*     52:MSG_BAT1S11_RXCH0    (158U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27900000},       /*     53:MSG_BAT2ED2_RXCH0    (159U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x37900000},       /*     54:MSG_BCC1S05_RXCH0    (160U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3F300000},       /*     55:MSG_BCC1S06_RXCH0    (161U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38B00000},       /*     56:MSG_BDB1F01_RXCH0    (162U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38D00000},       /*     57:MSG_BDB1F02_RXCH0    (163U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1F400000},       /*     58:MSG_BDB1F03_RXCH0    (164U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1CF00000},       /*     59:MSG_BDB1S01_RXCH0    (165U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62100000},       /*     60:MSG_BDB1S02_RXCH0    (166U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62200000},       /*     61:MSG_BDB1S03_RXCH0    (167U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62300000},       /*     62:MSG_BDB1S04_RXCH0    (168U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38000000},       /*     63:MSG_BDB1S05_RXCH0    (169U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62400000},       /*     64:MSG_BDB1S08_RXCH0    (170U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62600000},       /*     65:MSG_BDB1S10_RXCH0    (171U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62C00000},       /*     66:MSG_BDB1S13_RXCH0    (172U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3FC00000},       /*     67:MSG_BDB1S19_RXCH0    (173U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x30600000},       /*     68:MSG_BDB1S25_RXCH0    (174U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x30500000},       /*     69:MSG_BDB1S26_RXCH0    (175U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62900000},       /*     70:MSG_BDB1S27_RXCH0    (176U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x62A00000},       /*     71:MSG_BDB1S28_RXCH0    (177U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x39700000},       /*     72:MSG_BDB1S29_RXCH0    (178U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3B500000},       /*     73:MSG_BDB1S35_RXCH0    (179U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3B800000},       /*     74:MSG_BDB1S36_RXCH0    (180U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x31200000},       /*     75:MSG_BDC1S13_RXCH0    (181U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x32000000},       /*     76:MSG_BDC1S14_RXCH0    (182U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x32A00000},       /*     77:MSG_BDC1S16_RXCH0    (183U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x18600000},       /*     78:MSG_BDC1S30_RXCH0    (184U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1D200000},       /*     79:MSG_BDC1S33_RXCH0    (185U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x14800000},       /*     80:MSG_BDC1S41_RXCH0    (186U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1D300000},       /*     81:MSG_BDC1S46_RXCH0    (187U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x33700000},       /*     82:MSG_BDC1S48_RXCH0    (188U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x01300000},       /*     83:MSG_BDC1S52_RXCH0    (189U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x01B00000},       /*     84:MSG_BDC1S60_RXCH0    (190U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1E300000},       /*     85:MSG_BDC1S81_RXCH0    (191U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x15000000},       /*     86:MSG_BDC1S82_RXCH0    (192U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x36700000},       /*     87:MSG_BDC1S83_RXCH0    (193U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35500000},       /*     88:MSG_BDC1S97_RXCH0    (194U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35800000},       /*     89:MSG_BDC1S98_RXCH0    (195U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35D00000},       /*     90:MSG_BDC1S99_RXCH0    (196U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1A400000},       /*     91:MSG_BDC1SA0_RXCH0    (197U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35F00000},       /*     92:MSG_BDC1SA1_RXCH0    (198U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x39300000},       /*     93:MSG_BDC1SC1_RXCH0    (199U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39500000},       /*     94:MSG_BDC1SC2_RXCH0    (200U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39600000},       /*     95:MSG_BDC1SC3_RXCH0    (201U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39A00000},       /*     96:MSG_BDC1SC4_RXCH0    (202U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39B00000},       /*     97:MSG_BDC1SC5_RXCH0    (203U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39D00000},       /*     98:MSG_BDC1SC6_RXCH0    (204U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39E00000},       /*     99:MSG_BDC1SC7_RXCH0    (205U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x39F00000},       /*    100:MSG_BDC1SC8_RXCH0    (206U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3A500000},       /*    101:MSG_BDC1SC9_RXCH0    (207U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3AC00000},       /*    102:MSG_BDC1SD1_RXCH0    (208U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3AE00000},       /*    103:MSG_BDC1SD2_RXCH0    (209U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3B200000},       /*    104:MSG_BDC1SD3_RXCH0    (210U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3B300000},       /*    105:MSG_BDC1SD4_RXCH0    (211U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3B900000},       /*    106:MSG_BDC1SD5_RXCH0    (212U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3BC00000},       /*    107:MSG_BDC1SD6_RXCH0    (213U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3C600000},       /*    108:MSG_BDC1SD7_RXCH0    (214U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3C700000},       /*    109:MSG_BDC1SD8_RXCH0    (215U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3CD00000},       /*    110:MSG_BDC1SD9_RXCH0    (216U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3D300000},       /*    111:MSG_BDC1SE1_RXCH0    (217U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3D600000},       /*    112:MSG_BDC1SE2_RXCH0    (218U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3DD00000},       /*    113:MSG_BDC1SE3_RXCH0    (219U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3E100000},       /*    114:MSG_BDC1SE4_RXCH0    (220U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3EB00000},       /*    115:MSG_BDC1SE5_RXCH0    (221U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3EF00000},       /*    116:MSG_BDC1SE6_RXCH0    (222U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x3F500000},       /*    117:MSG_BDC1SE7_RXCH0    (223U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x42300000},       /*    118:MSG_BDC1SE8_RXCH0    (224U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x42900000},       /*    119:MSG_BDC1SE9_RXCH0    (225U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x43000000},       /*    120:MSG_BDC1SF1_RXCH0    (226U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x48000000},       /*    121:MSG_BDC1SF2_RXCH0    (227U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x48400000},       /*    122:MSG_BDC1SF3_RXCH0    (228U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x49100000},       /*    123:MSG_BDC1SF4_RXCH0    (229U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x49700000},       /*    124:MSG_BDC1SF6_RXCH0    (230U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x52600000},       /*    125:MSG_BDC1SG4_RXCH0    (231U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x52B00000},       /*    126:MSG_BDC1SG6_RXCH0    (232U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x52C00000},       /*    127:MSG_BDC1SG7_RXCH0    (233U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53000000},       /*    128:MSG_BDC1SG8_RXCH0    (234U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53100000},       /*    129:MSG_BDC1SG9_RXCH0    (235U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53400000},       /*    130:MSG_BDC1SH3_RXCH0    (236U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53500000},       /*    131:MSG_BDC1SH4_RXCH0    (237U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53700000},       /*    132:MSG_BDC1SH5_RXCH0    (238U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x53800000},       /*    133:MSG_BDC1SH6_RXCH0    (239U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2B300000},       /*    134:MSG_BDC1SH8_RXCH0    (240U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x61000000},       /*    135:MSG_BDC1SV1_RXCH0    (241U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x60200000},       /*    136:MSG_BDC1SV2_RXCH0    (242U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x59600000},       /*    137:MSG_BDC1SV3_RXCH0    (243U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x37B00000},       /*    138:MSG_BDF3S01_RXCH0    (244U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x18D00000},       /*    139:MSG_BDF3S02_RXCH0    (245U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x19A00000},       /*    140:MSG_BDR3S02_RXCH0    (246U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3CB00000},       /*    141:MSG_BKD1S01_RXCH0    (247U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3AB00000},       /*    142:MSG_BKD1S02_RXCH0    (248U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3F600000},       /*    143:MSG_BSR1S01_RXCH0    (249U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x23500000},       /*    144:MSG_BSR1S02_RXCH0    (250U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2AF00000},       /*    145:MSG_BSR1S03_RXCH0    (251U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x33300000},       /*    146:MSG_CDC1S01_RXCH0    (252U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1D900000},       /*    147:MSG_CMB1S03_RXCH0    (253U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2F300000},       /*    148:MSG_CMB1S04_RXCH0    (254U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x0A900000},       /*    149:MSG_CSR1G10_RXCH0    (255U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x43A00000},       /*    150:MSG_CSR1S04_RXCH0    (256U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3DB00000},       /*    151:MSG_CSR1S07_RXCH0    (257U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3DC00000},       /*    152:MSG_CSR1S08_RXCH0    (258U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x43800000},       /*    153:MSG_DCM1S01_RXCH0    (259U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34F00000},       /*    154:MSG_DCM1S03_RXCH0    (260U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x36300000},       /*    155:MSG_DCM1S04_RXCH0    (261U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34800000},       /*    156:MSG_DCM1S08_RXCH0    (262U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27D00000},       /*    157:MSG_DDM1S00_RXCH0    (263U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x12B00000},       /*    158:MSG_DDM1S09_RXCH0    (264U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x0B800000},       /*    159:MSG_DDM1S12_RXCH0    (265U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2EE00000},       /*    160:MSG_DDM1S16_RXCH0    (266U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1D700000},       /*    161:MSG_DDM1S17_RXCH0    (267U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2DA00000},       /*    162:MSG_DDM1S20_RXCH0    (268U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x21900000},       /*    163:MSG_DDM1S32_RXCH0    (269U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2E500000},       /*    164:MSG_DDM1S35_RXCH0    (270U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x28100000},       /*    165:MSG_DDM1SFG_RXCH0    (271U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x28200000},       /*    166:MSG_DDM1SFH_RXCH0    (272U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x52800000},       /*    167:MSG_DKY1S26_RXCH0    (273U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3BE00000},       /*    168:MSG_DRL1S03_RXCH0    (274U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3AF00000},       /*    169:MSG_DRR1S03_RXCH0    (275U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x28500000},       /*    170:MSG_DS11S27_RXCH0    (276U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x31700000},       /*    171:MSG_DS11S37_RXCH0    (277U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x60800000},       /*    172:MSG_DS11S40_RXCH0    (278U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x41100000},       /*    173:MSG_DS12F02_RXCH0    (279U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x41200000},       /*    174:MSG_DS12F03_RXCH0    (280U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3F000000},       /*    175:MSG_DST1S02_RXCH0    (281U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x4A000000},       /*    176:MSG_EBU1D01_RXCH0    (282U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3BF00000},       /*    177:MSG_ECT1G01_RXCH0    (283U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2A100000},       /*    178:MSG_ECT1G92_RXCH0    (284U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40100000},       /*    179:MSG_ECT1S93_RXCH0    (285U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1BC00000},       /*    180:MSG_EHV1E96_RXCH0    (286U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x07E00000},       /*    181:MSG_EHV1F02_RXCH0    (287U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x0A500000},       /*    182:MSG_EHV1F04_RXCH0    (288U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x12800000},       /*    183:MSG_EHV1G30_RXCH0    (289U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2A700000},       /*    184:MSG_EHV1G70_RXCH0    (290U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2A800000},       /*    185:MSG_EHV1G71_RXCH0    (291U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1D000000},       /*    186:MSG_EHV1S23_RXCH0    (292U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42F00000},       /*    187:MSG_EHV1S26_RXCH0    (293U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x32500000},       /*    188:MSG_EHV1S31_RXCH0    (294U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3B600000},       /*    189:MSG_EHV1S90_RXCH0    (295U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42100000},       /*    190:MSG_EHV1S94_RXCH0    (296U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40B00000},       /*    191:MSG_EHV1S95_RXCH0    (297U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1FA00000},       /*    192:MSG_EHV1S96_RXCH0    (298U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42B00000},       /*    193:MSG_EHV1S97_RXCH0    (299U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2DE00000},       /*    194:MSG_EHV1S99_RXCH0    (300U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2EB00000},       /*    195:MSG_EHV1SL2_RXCH0    (301U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x0A600000},       /*    196:MSG_EHV2G02_RXCH0    (302U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x07500000},       /*    197:MSG_EHV2G10_RXCH0    (303U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x0A100000},       /*    198:MSG_EHV2G20_RXCH0    (304U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x33500000},       /*    199:MSG_EIM1S01_RXCH0    (305U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x5F300000},       /*    200:MSG_ENG1C01_RXCH0    (306U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x5F400000},       /*    201:MSG_ENG1C02_RXCH0    (307U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49900000},       /*    202:MSG_ENG1D51_RXCH0    (308U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49A00000},       /*    203:MSG_ENG1D52_RXCH0    (309U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49B00000},       /*    204:MSG_ENG1D53_RXCH0    (310U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49D00000},       /*    205:MSG_ENG1D55_RXCH0    (311U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4A800000},       /*    206:MSG_ENG1D56_RXCH0    (312U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4AE00000},       /*    207:MSG_ENG1D59_RXCH0    (313U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4AF00000},       /*    208:MSG_ENG1D60_RXCH0    (314U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x0A400000},       /*    209:MSG_ENG1G03_RXCH0    (315U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1C500000},       /*    210:MSG_ENG1G13_RXCH0    (316U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x51E00000},       /*    211:MSG_ENG1G90_RXCH0    (317U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x0FC00000},       /*    212:MSG_ENG1G92_RXCH0    (318U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x59200000},       /*    213:MSG_ENG1S51_RXCH0    (319U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x58900000},       /*    214:MSG_ENG1S60_RXCH0    (320U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x58300000},       /*    215:MSG_ENG1S99_RXCH0    (321U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x4A300000},       /*    216:MSG_EPS1D50_RXCH0    (322U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x06200000},       /*    217:MSG_EPS1S11_RXCH0    (323U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1CA00000},       /*    218:MSG_EPS1S90_RXCH0    (324U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x5F600000},       /*    219:MSG_FCM1C01_RXCH0    (325U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x5F100000},       /*    220:MSG_FCM1C03_RXCH0    (326U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x48900000},       /*    221:MSG_FCM1S10_RXCH0    (327U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x48B00000},       /*    222:MSG_FCM1S12_RXCH0    (328U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x25100000},       /*    223:MSG_FCM1S39_RXCH0    (329U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x25200000},       /*    224:MSG_FCM1S40_RXCH0    (330U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x26100000},       /*    225:MSG_FCM1S41_RXCH0    (331U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x27400000},       /*    226:MSG_FCM1S49_RXCH0    (332U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x27500000},       /*    227:MSG_FCM1S51_RXCH0    (333U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27600000},       /*    228:MSG_FCM1S52_RXCH0    (334U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27C00000},       /*    229:MSG_FCM1S58_RXCH0    (335U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x28A00000},       /*    230:MSG_FCM1S66_RXCH0    (336U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x25A00000},       /*    231:MSG_FCM1S70_RXCH0    (337U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x15900000},       /*    232:MSG_FCM1S76_RXCH0    (338U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x15A00000},       /*    233:MSG_FCM1S78_RXCH0    (339U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x10000000},       /*    234:MSG_FCM1S79_RXCH0    (340U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x20F00000},       /*    235:MSG_FCM1S88_RXCH0    (341U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1B200000},       /*    236:MSG_FCM1S90_RXCH0    (342U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x25900000},       /*    237:MSG_FCM1S92_RXCH0    (343U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    0x0A800000},       /*    238:MSG_FCM1S95_RXCH0    (344U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x11500000},       /*    239:MSG_FWD1S10_RXCH0    (345U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x63300000},       /*    240:MSG_IDT1S02_RXCH0    (346U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3FB00000},       /*    241:MSG_IDT1S07_RXCH0    (347U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x14B00000},       /*    242:MSG_IDT1S08_RXCH0    (348U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x53200000},       /*    243:MSG_IDT1S15_RXCH0    (349U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x43B00000},       /*    244:MSG_IPA1S05_RXCH0    (350U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x36B00000},       /*    245:MSG_ITS1S01_RXCH0    (351U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3DE00000},       /*    246:MSG_ITS1S04_RXCH0    (352U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x31400000},       /*    247:MSG_ITS1S05_RXCH0    (353U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27B00000},       /*    248:MSG_ITS1S08_RXCH0    (354U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49400000},       /*    249:MSG_LVN1S01_RXCH0    (355U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x61100000},       /*    250:MSG_MET1S02_RXCH0    (356U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x31500000},       /*    251:MSG_MET1S33_RXCH0    (357U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x52400000},       /*    252:MSG_MET1S38_RXCH0    (358U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1DC00000},       /*    253:MSG_MET1S47_RXCH0    (359U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1F700000},       /*    254:MSG_MET1S55_RXCH0    (360U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x04900000},       /*    255:MSG_MGC1F13_RXCH0    (361U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3BD00000},       /*    256:MSG_PCN1S01_RXCH0    (362U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1CC00000},       /*    257:MSG_PDC1G01_RXCH0    (363U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x50700000},       /*    258:MSG_PDC1G02_RXCH0    (364U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2F400000},       /*    259:MSG_PDS1S01_RXCH0    (365U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x29500000},       /*    260:MSG_PLG1G15_RXCH0    (366U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x29600000},       /*    261:MSG_PLG1G16_RXCH0    (367U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42200000},       /*    262:MSG_PLG1S01_RXCH0    (368U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x43200000},       /*    263:MSG_PLG1S06_RXCH0    (369U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2A600000},       /*    264:MSG_PLG1S20_RXCH0    (370U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x20400000},       /*    265:MSG_PLG1S21_RXCH0    (371U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1D100000},       /*    266:MSG_PMN1G03_RXCH0    (372U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40300000},       /*    267:MSG_PST1S01_RXCH0    (373U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40500000},       /*    268:MSG_PST1S02_RXCH0    (374U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2B200000},       /*    269:MSG_PWC1S41_RXCH0    (375U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x14D00000},       /*    270:MSG_RCP1S01_RXCH0    (376U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x23000000},       /*    271:MSG_RCP1S02_RXCH0    (377U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x14F00000},       /*    272:MSG_RCP1S03_RXCH0    (378U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3CA00000},       /*    273:MSG_RSE1G20_RXCH0    (379U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x32F00000},       /*    274:MSG_RSE1G24_RXCH0    (380U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x33600000},       /*    275:MSG_RSE1G25_RXCH0    (381U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34D00000},       /*    276:MSG_RSE1G26_RXCH0    (382U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38500000},       /*    277:MSG_RSE1G29_RXCH0    (383U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x3C800000},       /*    278:MSG_RSE1S02_RXCH0    (384U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x32800000},       /*    279:MSG_RST1S03_RXCH0    (385U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1DB00000},       /*    280:MSG_SBW1G02_RXCH0    (386U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x43900000},       /*    281:MSG_SCN1S01_RXCH0    (387U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x37500000},       /*    282:MSG_SCN1S02_RXCH0    (388U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x10B00000},       /*    283:MSG_SCS1S10_RXCH0    (389U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2FD00000},       /*    284:MSG_SCS1S11_RXCH0    (390U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x2FE00000},       /*    285:MSG_SCS1S14_RXCH0    (391U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40C00000},       /*    286:MSG_SOL1S02_RXCH0    (392U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x40D00000},       /*    287:MSG_SOL1S03_RXCH0    (393U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1EB00000},       /*    288:MSG_SOL1S04_RXCH0    (394U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1EA00000},       /*    289:MSG_SOL1S05_RXCH0    (395U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1BB00000},       /*    290:MSG_SOL1S06_RXCH0    (396U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49500000},       /*    291:MSG_TPM1S02_RXCH0    (397U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x49600000},       /*    292:MSG_TPM1S03_RXCH0    (398U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34700000},       /*    293:MSG_TPM1S04_RXCH0    (399U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x34C00000},       /*    294:MSG_TPM1S05_RXCH0    (400U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x41700000},       /*    295:MSG_TPM1S06_RXCH0    (401U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x36F00000},       /*    296:MSG_TPM1S07_RXCH0    (402U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x41800000},       /*    297:MSG_TPM1S08_RXCH0    (403U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42600000},       /*    298:MSG_TPM1S09_RXCH0    (404U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42800000},       /*    299:MSG_TPM1S10_RXCH0    (405U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42A00000},       /*    300:MSG_TPM1S11_RXCH0    (406U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x42C00000},       /*    301:MSG_TPM1S12_RXCH0    (407U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2A000000},       /*    302:MSG_TRA1S01_RXCH0    (408U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x0A000000},       /*    303:MSG_TRA1S02_RXCH0    (409U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3E700000},       /*    304:MSG_UCB1S01_RXCH0    (410U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x31800000},       /*    305:MSG_VAS1S01_RXCH0    (411U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x4A400000},       /*    306:MSG_VGR1D50_RXCH0    (412U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x4A100000},       /*    307:MSG_VSC1D51_RXCH0    (413U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x06A00000},       /*    308:MSG_VSC1F01_RXCH0    (414U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x06900000},       /*    309:MSG_VSC1G12_RXCH0    (415U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x09E00000},       /*    310:MSG_VSC1G13_RXCH0    (416U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x0B700000},       /*    311:MSG_VSC1G14_RXCH0    (417U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x26200000},       /*    312:MSG_VSC1G96_RXCH0    (418U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x60100000},       /*    313:MSG_VUM1S01_RXCH0    (419U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x2F900000},       /*    314:MSG_WIP1S01_RXCH0    (420U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x27E00000},       /*    315:MSG_YGW1S01_RXCH0    (421U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x37F00000},       /*    316:MSG_ZN11S02_RXCH0    (422U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x38A00000},       /*    317:MSG_ZN11S03_RXCH0    (423U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x08600000},       /*    318:MSG_ZN11S08_RXCH0    (424U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x1DE00000},       /*    319:MSG_ZN11S14_RXCH0    (425U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1DF00000},       /*    320:MSG_ZN11S17_RXCH0    (426U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x36800000},       /*    321:MSG_ZN11S19_RXCH0    (427U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x39800000},       /*    322:MSG_ZN11S25_RXCH0    (428U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x36A00000},       /*    323:MSG_ZN11S26_RXCH0    (429U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x39C00000},       /*    324:MSG_ZN11S32_RXCH0    (430U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x50000000},       /*    325:MSG_ZN11S38_RXCH0    (431U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x36E00000},       /*    326:MSG_ZN11S60_RXCH0    (432U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x33F00000},       /*    327:MSG_ZN11S63_RXCH0    (433U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3D200000},       /*    328:MSG_ZN11S64_RXCH0    (434U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3F900000},       /*    329:MSG_ZN11S65_RXCH0    (435U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x40000000},       /*    330:MSG_ZN11S66_RXCH0    (436U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x40400000},       /*    331:MSG_ZN11S67_RXCH0    (437U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35000000},       /*    332:MSG_ZN11SF6_RXCH0    (438U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35200000},       /*    333:MSG_ZN11SF7_RXCH0    (439U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x35300000},       /*    334:MSG_ZN11SF8_RXCH0    (440U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3BB00000},       /*    335:MSG_ZN11SF9_RXCH0    (441U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1E100000},       /*    336:MSG_ZN21S05_RXCH0    (442U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    0x39000000},       /*    337:MSG_ZN21S13_RXCH0    (443U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x1BE00000},       /*    338:MSG_ZN21S28_RXCH0    (444U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    0x3A900000}        /*    339:MSG_ZN21S72_RXCH0    (445U) */
    };

    U1  u1_t_act;
    U2  u2_t_idx;
    U1  u1_t_dlc;
    U4  u4_t_time;
    U1  u1_tp_sgnl[XSPI_IVI_CAN_64];

    if ((u2_a_MSG >= u2_s_XSPI_IVI_CANGW_MIN) &&
       (u2_a_MSG <= u2_s_XSPI_IVI_CANGW_MAX)    ) {
        u2_t_idx = u2_a_MSG - u2_s_XSPI_IVI_CANGW_MIN;
        u1_t_act = st_sp_LCOM_SPI_MSG2POSLEN[u2_t_idx].u1_act;
        if (u1_t_act != (U1)FALSE) {
            /* CANデータ受信 */
            u1_t_dlc = st_sp_LCOM_SPI_MSG2POSLEN[u2_t_idx].u1_dlc;
            vd_g_MemfillU1(&u1_tp_sgnl[0], (U1)0U, (U4)XSPI_IVI_CAN_64);
            (void)Com_ReadIPDU((PduIdType)u2_a_MSG, &u1_tp_sgnl[0] );

            /* タイムスタンプ取得処理 */
            u4_t_time = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
            u4_t_time = (U4)(u4_t_time / MCU_FRT_1MS);

            vd_s_XspiIviCANGWStuckBuff(u4_t_time, st_sp_LCOM_SPI_MSG2POSLEN[u2_t_idx].u4_flame_id, u1_t_dlc, &u1_tp_sgnl[0]);
        }
    }
}

/*===================================================================================================================================*/
/*  static void         vd_s_XspiIviCANGWStuckBuff(const U4 u4_a_TIME, const U4 u4_a_MSG, const U1 u1_a_DLC, const U1 * u1_ap_SRC)   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CAN受信によるユーザフック処理                                                                                      */
/*  Arguments:      u4_a_TIME : CAN受信時のタイムスタンプ                                                                              */
/*                  u4_a_MSG  : CAN ID                                                                                               */
/*                  u1_a_DLC  : 受信CANフレームのDLC                                                                                  */
/*                  u1_ap_SRC : CAN DATA                                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviCANGWStuckBuff(const U4 u4_a_TIME, const U4 u4_a_MSG, const U1 u1_a_DLC, const U1 * u1_ap_SRC)
{
    static const U1     u1_sp_XSPI_DLC[3] = {
        (U1)8U,     /* 8byte    */
        (U1)32U,    /* 32byte   */
        (U1)64U     /* 64byte   */
    };

    U1          u1_t_cms;
    U1          u1_t_jdg;
    U1          u1_tp_cms[XSPI_IVI_CMS_1];
    U1          u1_tp_can_data[XSPI_IVI_CAN_DATA_80];

    u1_t_jdg = (U1)FALSE;
    
    if (u1_a_DLC < (U1)XSPI_IVI_CAN_NUM_DLC) {
        u1_t_cms = (U1)4U + (U1)4U + (U1)1U + u1_sp_XSPI_DLC[u1_a_DLC] + (U1)7U;     /* time,CANID,DLC,CANData,未使用のbyteを加算してCMSを作成 */
        u1_t_jdg = u1_g_XspiIviQueueWriChk(u1_t_cms);
    }
    else {
        /* 引数の値域外のため異常と判断し読み捨てとする */
        /* do nothing */
    }
    
    if (u1_t_jdg == (U1)TRUE) {
        /* バッファに空きがあるためデータ保持 */
        vd_g_MemfillU1(&u1_tp_can_data[0], (U1)0U, (U4)XSPI_IVI_CAN_DATA_80);
        /* CMS */
        u1_tp_cms[0] = u1_t_cms;
        /* time */
        u1_tp_can_data[0] = (u4_a_TIME  & (U4)0xFF000000U) >>   24; /* 1バイトを抽出してシフト */
        u1_tp_can_data[1] = (u4_a_TIME  & (U4)0x00FF0000U) >>   16; /* 1バイトを抽出してシフト */
        u1_tp_can_data[2] = (u4_a_TIME  & (U4)0x0000FF00U) >>    8; /* 1バイトを抽出してシフト */
        u1_tp_can_data[3] = (u4_a_TIME  & (U4)0x000000FFU);         /* 1バイトを抽出 */
        /* CAN ID */
        u1_tp_can_data[4] = (u4_a_MSG   & (U4)0xFF000000U) >>   24; /* 1バイトを抽出 */
        u1_tp_can_data[5] = (u4_a_MSG   & (U4)0x00FF0000U) >>   16; /* 1バイトを抽出してシフト */
        u1_tp_can_data[6] = (u4_a_MSG   & (U4)0x0000FF00U) >>    8; /* 1バイトを抽出してシフト */
        u1_tp_can_data[7] = (u4_a_MSG   & (U4)0x000000FFU);         /* 1バイトを抽出してシフト */
        /* DLC */
        u1_tp_can_data[8] = u1_sp_XSPI_DLC[u1_a_DLC];
        /* CANData */
        vd_g_MemcpyU1(&u1_tp_can_data[9], &u1_ap_SRC[0], (U4)u1_sp_XSPI_DLC[u1_a_DLC]);

        /* ToDo：キュー操作なので割禁が必要か検討する */
        u1_g_XspiIviQueueWriCms(u1_tp_cms);
        vd_g_XspiIviQueueWriCandata(u1_tp_can_data, (U2)u1_t_cms);
        /* ToDo：キュー操作なので割禁が必要か検討する */
    }
    else {
        /* バッファに空きがないため受信した信号は保持せず読み捨てる */
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  void         vd_g_XspiIviCANBusGet2M(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANBusステータス受信によるユーザフック処理                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviCANBusGet2M(void){
    /*暫定 CANBusステータスの取得IF不明のため側だけ用意しておく*/
    /*RAMに状態を格納*/
    /*状態変化時スタックしていく*/
}

/*===================================================================================================================================*/
/*  void         vd_g_XspiIviCANBusGet5M(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANBusステータス受信によるユーザフック処理                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviCANBusGet5M(void){
    /*暫定 CANBusステータスの取得IF不明のため側だけ用意しておく*/
    /*RAMに状態を格納*/
    /*状態変化時スタックしていく*/
}

/*===================================================================================================================================*/
/*  void         vd_g_XspiIviCANBusSend(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANBusステータス受信によるユーザフック処理                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void         vd_g_XspiIviCANBusSend(void){
    /*CANBusStsの送信用：起動時、ステータス変化時、SoCからの要求有時にコール*/
    vd_s_XspiIviCANCommandStuckBuff((U1)XSPI_IVI_CANCOMMAND_SEND,(U2)XSPI_IVI_CAN_BUSSTS_SIZE);
}



/*===================================================================================================================================*/
/*  void         vd_s_XspiIviCANCommandStuckBuff(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    BUSステータスをバッファにスタックしていく処理                                                                        */
/*  Arguments:      u2_a_TYPE : Command Data Type                                                                                    */
/*                  u2_a_SIZE : Command Data Length                                                                                  */
/*                  u1_ap_SRC : Command Data                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviCANCommandStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE)
{
    U1          u1_tp_cancomamand_data[XSPI_IVI_CAN_COMMNDDATA_SIZE];
    U1          u1_t_cancommand_data_size;
    U1          u1_t_jdg;

    
    u1_t_jdg = (U1)FALSE;
    vd_g_MemfillU1(&u1_tp_cancomamand_data[0], (U1)0U, (U4)XSPI_IVI_CAN_COMMNDDATA_SIZE);
    

    /*8byteアライメント*/
    if((u2_a_SIZE > (U2)8U) && (u2_a_SIZE <= (U2)16U)) {
        u1_t_cancommand_data_size = (U1)XSPI_IVI_HEADER + (U1)16U;
    } else if(u2_a_SIZE <= (U2)8U){
        u1_t_cancommand_data_size = (U1)XSPI_IVI_HEADER + (U1)8U;
    } else {

    }
    u1_t_jdg = u1_g_XspiIviQueueWriChkCanCommand(u1_t_cancommand_data_size);

    if(u1_t_jdg == (U1)TRUE)
    {
        /*キューに空き容量があるためデータ格納*/
        /*各コマンドのヘッダー情報作成*/
        /*識別値*/
        u1_tp_cancomamand_data[0] = (U1)0x43U;
        u1_tp_cancomamand_data[1] = (U1)0x4EU;
        u1_tp_cancomamand_data[2] = (U1)0x44U;
        u1_tp_cancomamand_data[3] = (U1)0x54U;
        /*データ長*/
        u1_tp_cancomamand_data[4] = 0U;        /*データタイプがU1に収まるためByte4は0固定*/
        u1_tp_cancomamand_data[5] = (U1)u1_t_cancommand_data_size - (U2)XSPI_IVI_HEADER;
        /*データサイズ*/
        u1_tp_cancomamand_data[6] = (U1)u1_a_ID;
        u1_tp_cancomamand_data[7] = (U1)0U;
        u1_tp_cancomamand_data[8] = (U1)u1_a_ID;

        vd_g_MemcpyU1(&u1_tp_cancomamand_data[9], &u1_sp_Xspi_Ivi_CanBusSts2M[0], (U4)4U);
        vd_g_MemcpyU1(&u1_tp_cancomamand_data[13], &u1_sp_Xspi_Ivi_CanBusSts5M[0], (U4)4U);


        /*CANコマンドデータをキューに格納*/
        vd_g_XspiIviQueueWriCanCommandData(u1_tp_cancomamand_data,(U2)u1_t_cancommand_data_size);
        /*CANコマンドデータサイズをキューに格納*/
        u1_g_XspiIviQueueWriCanCommandSize(&u1_t_cancommand_data_size);
    }
    else{
        /*キューに空き容量がないため読み飛ばし*/
        /* do nothing */
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
/*  0.0.0    11/11/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
