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
#define XSPI_IVI_SUB1_POWER_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_POWER_C_MINOR                   (0)
#define XSPI_IVI_SUB1_POWER_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_power.h"
#include    "Dio.h"
#include    "Dio_Symbols.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_POWER_C_MAJOR != XSPI_IVI_SUB1_POWER_H_MAJOR) || \
     (XSPI_IVI_SUB1_POWER_C_MINOR != XSPI_IVI_SUB1_POWER_H_MINOR) || \
     (XSPI_IVI_SUB1_POWER_C_PATCH != XSPI_IVI_SUB1_POWER_H_PATCH))
#error "x_spi_ivi_sub1_power.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_POWER_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_POWER_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_POWER_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_power.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_POWER_ID                    (0x21U)
#define    XSPI_IVI_POWER_STATE_SEND            (0x01U)
#define    XSPI_IVI_POWER_STATE_REC             (0x02U)
#define    XSPI_IVI_POWER_STATE_TRANS_REC       (0x03U)
#define    XSPI_IVI_POWER_STATE_TRANS_SEND      (0x04U)


#define    XSPI_IVI_POWER_TASK           (2000U / 5U)
#define    XSPI_IVI_POWER_STATE_SIZE      (5U)
#define    XSPI_IVI_POWER_TRANS_SIZE      (6U)

#define    XSPI_IVI_POWER_STATE_NUM             (7U)    /* 状態総数 */
#define    XSPI_IVI_POWER_STATE_OFF             (0U)    /* OFF */
#define    XSPI_IVI_POWER_STATE_PARK            (1U)    /* 駐車中 */
#define    XSPI_IVI_POWER_STATE_RIDEON          (2U)    /* 乗車中 */
#define    XSPI_IVI_POWER_STATE_POWERON         (3U)    /* PowerON通常  */
#define    XSPI_IVI_POWER_STATE_POWERON_STOP    (4U)    /* PowerON緊急停止 */
#define    XSPI_IVI_POWER_STATE_PARK_HI_PRE     (5U)    /* 駐車中高圧起動  */
#define    XSPI_IVI_POWER_STATE_PARK_TEMP_CON   (6U)    /* 駐車中高圧・温調起動  */
#define    XSPI_IVI_POWER_STATE_UNKNOWN         (0xFFU) /* 未確定  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*電源ステータス用*/
typedef struct{
    U1                          u1_basic_state;
    U1                          u1_special_state;
    U1                          u1_ota_state;
    U1                          u1_appearance_state;
}ST_XSPI_IVI_POWER_STATE;

/*状態移行指示用*/
typedef struct{
    U1                          u1_count;
    U1                          u1_basic_state;
    U1                          u1_special_state;
    U1                          u1_ota_state;
    U1                          u1_appearance_state;
}ST_XSPI_IVI_POWER_STATE_TRANS;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*電源ステータス格納*/
static U1 u1_s_xspi_ivi_power_state[4];
static U1 u1_s_xspi_ivi_power_state_pre[4];
/*状態移行格納*/
static ST_XSPI_IVI_POWER_STATE_TRANS st_s_xspi_ivi_state_trans; 

static U4 u4_s_xspi_ivi_task_cnt_subframe1_power_pre;

/*SPI通信許可状態*/
static U1 u1_s_xspi_ivi_power_start_flg;
/*状態移行指示有無*/
static U1 u1_s_xspi_ivi_power_state_trans_flg;
/*デバイス初期化状態*/
static U1 u1_s_xspi_ivi_power_device_init_fin_flg;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size);
static U1              u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE);
static void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD);
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1POWERInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerInit(void)
{
    u1_s_xspi_ivi_power_start_flg = (U1)FALSE;
    u1_s_xspi_ivi_power_state_trans_flg = (U1)FALSE;
    u1_s_xspi_ivi_power_device_init_fin_flg = (U1)FALSE;

    vd_g_MemfillU1(&u1_s_xspi_ivi_power_state[0], (U1)U1_MAX, (U4)4U);
    vd_g_MemfillU1(&u1_s_xspi_ivi_power_state_pre[0], (U1)U1_MAX, (U4)4U);

    st_s_xspi_ivi_state_trans.u1_count = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_basic_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_special_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_ota_state = (U1)U1_MAX;
    st_s_xspi_ivi_state_trans.u1_appearance_state = (U1)U1_MAX;

    u4_s_xspi_ivi_task_cnt_subframe1_power_pre = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1POWERMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerMainTask(void)
{
    /*定期送信などのデータ作成をここで行う*/
    U1 u1_tp_data[6];
    U4 u4_t_power_task;
    U1 u1_t_power_ivent_jdg;

    /*CAN受信用*/
    U1 u1_t_VPSINFO1;
    U1 u1_t_VPSINFO2;
    U1 u1_t_VPSINFO3;
    U1 u1_t_VPSINFO4;
    U1 u1_t_VPSINFO5;
    U1 u1_t_VPSINFO6;
    U1 u1_t_VPSINFO7;
    U1 u1_t_VPSINFOS; /*特殊ステート*/
    U1 u1_t_VPSISOTA; /*OTAステート*/
    U1 u1_t_APOFRQ;   /*見た目ON/OFF*/

    /*Boot起動用*/
    U1 u1_t_boot;

    /*前回電源ステート更新*/
    vd_g_MemcpyU1(&u1_s_xspi_ivi_power_state_pre[0],&u1_s_xspi_ivi_power_state[0],(U1)4U);

    /*電源ステートをCANから受信（シス検暫定）*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &u1_t_VPSINFO1 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_VPSINFO2 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_VPSINFO3 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_VPSINFO4 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_VPSINFO5 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO6, &u1_t_VPSINFO6 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO7, &u1_t_VPSINFO7 );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFOS, &u1_t_VPSINFOS );
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSISOTA, &u1_t_VPSISOTA );
    (void)Com_ReceiveSignal(ComConf_ComSignal_APOFRQ  , &u1_t_APOFRQ    );
    
    if(u1_t_VPSINFO1 == (U1)TRUE) {
        u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_OFF;
    } else if(u1_t_VPSINFO4 == (U1)TRUE){
        u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_POWERON;
    } else if(u1_t_VPSINFO5 == (U1)TRUE) {
        u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_POWERON_STOP;
    } else if(u1_t_VPSINFO3 == (U1)TRUE) {
        u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_RIDEON;
    } else if(u1_t_VPSINFO2 == (U1)TRUE) {
        if(u1_t_VPSINFO7 == (U1)TRUE) {
            u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_PARK_TEMP_CON;
        } else if(u1_t_VPSINFO6 == (U1)TRUE) {
            u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_PARK_HI_PRE;
        } else {
            u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_PARK;
        }
    } else {
        
    }

    u1_s_xspi_ivi_power_state[1] = u1_t_VPSINFOS; /*特殊ステートのCAN信号値*/
    u1_s_xspi_ivi_power_state[2] = u1_t_VPSISOTA; /*OTAステートのCAN信号値*/
    u1_s_xspi_ivi_power_state[3] = u1_t_APOFRQ; /*見た目ON/OFFのCAN信号値*/
    
    /* シス検暫定対応*/
    /* BOOT入力値取得処理 */
    u1_t_boot = Dio_ReadChannel(DIO_ID_PORT0_CH2);
    if(u1_t_boot == STD_HIGH){   /* BOOT=Hiを検知した場合、どの状態でも下記状態に上書き */
        u1_s_xspi_ivi_power_state[0] = (U1)XSPI_IVI_POWER_STATE_POWERON;   /* 基本ステート：POWERON通常 */
        u1_s_xspi_ivi_power_state[1] = (U1)XSPI_IVI_POWER_STATE_OFF;       /*特殊ステート：未設定*/
        u1_s_xspi_ivi_power_state[3] = (U1)0U;                             /*見た目ON/OFF：ON*/
    }
    /* シス検暫定ここまで */

    u4_t_power_task = u4_s_xspi_ivi_task_cnt - u4_s_xspi_ivi_task_cnt_subframe1_power_pre;
    u1_t_power_ivent_jdg = (U1)FALSE;
    u1_t_power_ivent_jdg = u1_s_XspiIviSub1PowerDataEventJdg(&u1_s_xspi_ivi_power_state[0],&u1_s_xspi_ivi_power_state_pre[0],(U1)4U);

    /*SPI通信許可OKかどうか*/
    if(u1_s_xspi_ivi_power_start_flg == (U1)TRUE){
        if((u4_t_power_task >= (U4)XSPI_IVI_POWER_TASK) ||
           (u1_t_power_ivent_jdg == (U1)TRUE)){
            /*2s定期 or 値変化でXSPI通信*/
            u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_SEND;
            vd_g_MemcpyU1(&u1_tp_data[1],&u1_s_xspi_ivi_power_state[0],(U1)4U);
            vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_STATE_SIZE,u1_tp_data);
            u4_s_xspi_ivi_task_cnt_subframe1_power_pre = u4_s_xspi_ivi_task_cnt;
        }else{
            /*Do Nothing*/
        }

        if((u1_s_xspi_ivi_power_device_init_fin_flg == (U1)TRUE) &&
           (u1_s_xspi_ivi_power_state_trans_flg == (U1)TRUE)){/*デバイス初期化済かつ指示あり*/
            /*状態移行確認*/
            u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_TRANS_SEND;
            u1_tp_data[1] = st_s_xspi_ivi_state_trans.u1_count;
            u1_tp_data[2] = st_s_xspi_ivi_state_trans.u1_basic_state;
            u1_tp_data[3] = st_s_xspi_ivi_state_trans.u1_special_state;
            u1_tp_data[4] = st_s_xspi_ivi_state_trans.u1_ota_state;
            u1_tp_data[5] = st_s_xspi_ivi_state_trans.u1_appearance_state;
            vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_TRANS_SIZE,u1_tp_data);
            /*指示フラグをFALSEに落とす*/
            u1_s_xspi_ivi_power_state_trans_flg = (U1)FALSE;
        }
    }
}


/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_PowerState1stSend(void)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1_PowerState1stSend(void)
{
    /*起動時電源ステート送信処理*/    
    U1 u1_tp_data[5];

    u1_tp_data[0] = (U1)XSPI_IVI_POWER_STATE_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_s_xspi_ivi_power_state[0],(U1)4U);
    vd_s_XspiIviSub1PowerDataToQueue((U2)XSPI_IVI_POWER_STATE_SIZE,u1_tp_data);
    u1_s_xspi_ivi_power_start_flg = (U1)TRUE;
    u4_s_xspi_ivi_task_cnt_subframe1_power_pre = u4_s_xspi_ivi_task_cnt;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_POWER_Ana(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1PowerAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_POWER_STATE_REC:
        /*シス検では受信のみ 今後フェール用で使用*/
        break;
    case XSPI_IVI_POWER_STATE_TRANS_REC:
        vd_s_XspiIviSub1_PowerStateTransRec(&u1_ap_XSPI_ADD[0],u2_a_data_size);
        break;    
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_PowerStateTransRec(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)
{
    /*状態移行指示あり シス検では1回のみ*/
    if(u1_ap_XSPI_ADD[1] != (U1)0U){
        u1_s_xspi_ivi_power_state_trans_flg = (U1)TRUE;
    }
    st_s_xspi_ivi_state_trans.u1_count = u1_ap_XSPI_ADD[1];
    st_s_xspi_ivi_state_trans.u1_basic_state = u1_ap_XSPI_ADD[2];
    st_s_xspi_ivi_state_trans.u1_special_state = u1_ap_XSPI_ADD[3];
    st_s_xspi_ivi_state_trans.u1_ota_state = u1_ap_XSPI_ADD[4];
    st_s_xspi_ivi_state_trans.u1_appearance_state = u1_ap_XSPI_ADD[5];
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DevInitFinish(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DevInitFinish(void)
{
    u1_s_xspi_ivi_power_device_init_fin_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1 u1_a_XSPI_ADD)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1PowerDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD)
{
    U1     u1_tp_data[6];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_POWER_ID;

    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)6U);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u2_a_size);

    /*キューの関数呼び出し（そっちでヘッダーとかは入れてく）*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_a_size,u1_tp_data);
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1PowerDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)
{
    U1     u1_t_judge;
    U4     u4_t_loop;

    u1_t_judge = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++){
        if(u1_ap_DATA[u4_t_loop] != u1_ap_DATA_PRE[u4_t_loop]){
            u1_t_judge = (U1)TRUE;
        }
    }

    return(u1_t_judge);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/20/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
