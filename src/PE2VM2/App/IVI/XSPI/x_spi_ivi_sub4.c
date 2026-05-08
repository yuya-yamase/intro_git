/* 1.12.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 4 in XSPI communication.                                                       */
/*  Handled data: CAN Data/Repro/LCAN Data                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB4_C_MAJOR                   (1)
#define XSPI_IVI_SUB4_C_MINOR                   (12)
#define XSPI_IVI_SUB4_C_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub4_private.h"
#include    "x_spi_ivi_sub1_power.h"

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
#define XSPI_IVI_SFT_04                     ( 4U)
#define XSPI_IVI_SFT_08                     ( 8U)
#define XSPI_IVI_SFT_16                     (16U)
#define XSPI_IVI_SFT_24                     (24U)

#define XSPI_IVI_CAN_DLC_08                 ( 8U)
#define XSPI_IVI_CAN_DLC_32                 (32U)
#define XSPI_IVI_CAN_DLC_64                 (64U)

#define XSPI_IVI_CAN_64                     (64U)

#define XSPI_IVI_CMS_1                      (   1U)
#define XSPI_IVI_CMS_128                    ( 128U)

#define XSPI_IVI_CAN_DATA_80                (  80U)
#define XSPI_IVI_CAN_DATA_MAX               (3356U)     /* サブフレーム4領域(3500byte) - コマンド,メッセージヘッダ(8+8byte) - CMS領域(128byte) */

#define XSPI_IVI_BS_ERR                     (0xFFFFFFFFU)

#define XSPI_IVI_CANCOMMAND_ID              (0x434E4454U)
#define XSPI_IVI_CANCOMMAND_BUS_REQ         (0x03U)
#define XSPI_IVI_CANCOMMAND_SEND            (0x04U)
#define XSPI_IVI_CANCOMMAND_PARNMSEND_REQ   (0x10U)
#define XSPI_IVI_CANCOMMAND_PARNM_STS       (0x11U)
#define XSPI_IVI_CANCOMMAND_UTC_SEND        (0x21U)

#define XSPI_IVI_CAN_COMMNDDATA_SIZE        (24U)
#define XSPI_IVI_CAN_BUSSTS_SIZE            (9U)
#define XSPI_IVI_CAN_COMMAND_BUF_MAX        (128U)
#define XSPI_IVI_CAN_COMMAND_SIZE_MAX       (256U)

#define XSPI_IVI_UPPER_NIBBLE_MASK          (0xF0U)
#define XSPI_IVI_LOWER_NIBBLE_MASK          (0x0FU)

#define XSPI_IVI_CAN_BUF_0                  (0U)
#define XSPI_IVI_CAN_BUF_1                  (1U)
#define XSPI_IVI_CAN_BUF_2                  (2U)
#define XSPI_IVI_CAN_BUF_3                  (3U)
#define XSPI_IVI_CAN_BUF_4                  (4U)
#define XSPI_IVI_CAN_BUF_5                  (5U)
#define XSPI_IVI_CAN_BUF_6                  (6U)
#define XSPI_IVI_CAN_BUF_7                  (7U)
#define XSPI_IVI_CAN_BUF_8                  (8U)

/* CANバスステータス通知 バッファ位置 */
#define XSPI_IVI_CANBUS_POS_TOTAL           (4U)
#define XSPI_IVI_CANBUS_POS_REGSTUCK        (0U)
#define XSPI_IVI_CANBUS_POS_BUSOFF          (1U)
#define XSPI_IVI_CANBUS_POS_NOCONNECT       (2U)
#define XSPI_IVI_CANBUS_POS_STATUS          (3U)

/* CANバスステータス通知 VM通信受信値 */
#define XSPI_IVI_CANBUS_RSV_ACTIVE          (0x00U)
#define XSPI_IVI_CANBUS_RSV_REGSTUCK        (0x01U)
#define XSPI_IVI_CANBUS_RSV_BUSOFF          (0x02U)
#define XSPI_IVI_CANBUS_RSV_NOCONNECT       (0x04U)

/*UTC*/
#define XSPI_IVI_CLOCKUTC_SEND_TASK         (1000U / XSPI_IVI_TASK_TIME)
#define XSPI_IVI_CLOCKUTC_COMMAND_SIZE      (14U)
#define XSPI_IVI_CLOCKUTC_DATA_SIZE         (9U)
#define XSPI_IVI_WEEK_SUNDAY_RTC            (7U)
#define XSPI_IVI_WEEK_SUNDAY_UTC            (0U)
#define XSPI_IVI_YEAR_OFFSET                (100U)
#define XSPI_IVI_UTC_STATUS_VARID           (1U)
#define XSPI_IVI_BCD_HUNDREDS               (100U)
#define XSPI_IVI_BCD_TENS                   (10U)

/*PartialNM*/
#define XSPI_IVI_PARTIALNM_DATASIZE         (7U)

#define XSPI_IVI_IVDSH_DREC_NWORD           (2U)
#define XSPI_IVI_DATANM2_MASK               (0xC0U)
#define XSPI_IVI_MET1D51_CANID              (0x4B600000U)
#define XSPI_IVI_MET1D51_DLC                (8U)

/* Provisional (CANSignal To VM1) */
#define XSPI_IVI_IVDSH_NWORD                (1U)
/* Provisional (CANSignal To VM1) */

/*Reset Signal Mask Value*/
#define XSPI_IVI_CAN_CDSIZE_MASK            (0x0FU)
#define XSPI_IVI_CAN_MMRESET_MASK           (0x01U)
#define XSPI_IVI_CAN_HFDISP_MASK            (0x03U)
#define XSPI_IVI_CAN_PVMREQ_MASK            (0x03U)
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
static U1       u1_s_flg_canstuck;
static U1       u1_sp_Xspi_Ivi_CanBusSts2M[XSPI_IVI_CANBUS_POS_TOTAL];
static U1       u1_sp_Xspi_Ivi_CanBusSts5M[XSPI_IVI_CANBUS_POS_TOTAL];
static U1       u1_sp_Xspi_Ivi_CanBusSts2M_pre[XSPI_IVI_CANBUS_POS_TOTAL];
static U1       u1_sp_Xspi_Ivi_CanBusSts5M_pre[XSPI_IVI_CANBUS_POS_TOTAL];

static U1       u1_s_Xspi_Ivi_ClockUtc_recflg;
static U1       u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CLOCKUTC_DATA_SIZE];
static U1       u1_sp_Xspi_Ivi_ClockUtcdata_pre[XSPI_IVI_CLOCKUTC_DATA_SIZE];

static U1       u1_s_Xspi_Ivi_DataNm2_Sgnl_pre;

/* Provisional (CANSignal To VM1) */
static U1       u1_sp_Xspi_Ivi_DMS1S02_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S27_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S28_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S29_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S30_Data[XSPI_IVI_CAN_DLC_32];
static U1       u1_sp_Xspi_Ivi_MET1S43_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S62_Data[XSPI_IVI_CAN_DLC_08];
static U1       u1_sp_Xspi_Ivi_MET1S70_Data[XSPI_IVI_CAN_DLC_32];
/* Provisional (CANSignal To VM1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviSub4CanAna(const U1 * u1_ap_SUB4_ADD, const U2 u2_a_DTLEN);
static U2       u2_s_XspiIviSub4SendCanCmd(U1 * u1_ap_buf);
static U2       u2_s_XspiIviSub4SendCanMsg(U1 * u1_ap_buf, const U2 u2_a_COM_LEN);
static void     vd_s_XspiIviCANGWStuckBuff(const U4 u4_a_TIME, const U4 u4_a_MSG, const U1 u1_a_DLC, const U1 * u1_a_SRC);
static U4       u4_s_XspiIviBinarySearch(const U4 u4_a_CANID);
static void     vd_s_XspiIviCANCommandStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE);
static U1       u1_s_XspiIviClockUTCDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE);
static void     vd_s_XspiIviClockUTCStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE);
static void     vd_s_XspiIviSub4ResetInit(void);

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
    u1_s_flg_canstuck   = (U1)FALSE;

    /*2MBusSts*/
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_CanBusSts2M[0], (U1)0x00U, sizeof(u1_sp_Xspi_Ivi_CanBusSts2M));
    u1_sp_Xspi_Ivi_CanBusSts2M[XSPI_IVI_CANBUS_POS_STATUS]  = (U1)0x01U;    /* INIT：初期化状態（送受信不可状態） */

    vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_CanBusSts2M_pre[0], &u1_sp_Xspi_Ivi_CanBusSts2M[0], sizeof(u1_sp_Xspi_Ivi_CanBusSts2M_pre));

    /*5MBusSts*/
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_CanBusSts5M[0], (U1)0x00U, sizeof(u1_sp_Xspi_Ivi_CanBusSts5M));
    u1_sp_Xspi_Ivi_CanBusSts5M[XSPI_IVI_CANBUS_POS_STATUS]  = (U1)0x01U;    /* INIT：初期化状態（送受信不可状態） */

    vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_CanBusSts5M_pre[0], &u1_sp_Xspi_Ivi_CanBusSts5M[0], sizeof(u1_sp_Xspi_Ivi_CanBusSts5M_pre));

    u1_s_Xspi_Ivi_ClockUtc_recflg = (U1)FALSE;
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_ClockUtcdata[0], (U1)0U, (U4)XSPI_IVI_CLOCKUTC_DATA_SIZE);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_ClockUtcdata_pre[0], (U1)0U, (U4)XSPI_IVI_CLOCKUTC_DATA_SIZE);

    /* Provisional (CANSignal To VM1) */
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_DMS1S02_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S27_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S28_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S29_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S30_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_32);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S43_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S62_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_sp_Xspi_Ivi_MET1S70_Data[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_32);
    /* Provisional (CANSignal To VM1) */

    u1_s_Xspi_Ivi_DataNm2_Sgnl_pre = (U1)U1_MAX;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub4VMResetInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    VMリセット時の初期化処理                                                                                           */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub4VMResetInit(void)
{
    vd_s_XspiIviSub4ResetInit();
    vd_g_XspiIviSub1PowerVMResetComp((U1)XSPI_IVI_POWER_RESET_COMP_CAN);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub4SoCResetInit(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SoCリセット時の初期化処理                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub4SoCResetInit(void)
{
    vd_s_XspiIviSub4ResetInit();
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub4ResetInit(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    リセット時の初期化処理                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub4ResetInit(void)
{
    U1  u1_t_sgnl_cdsize;
    U1  u1_t_sgnl_mmreset;
    U1  u1_t_sgnl_hfdisp;
    U1  u1_t_sgnl_pvmreq;
    U1  u1_tp_candata_AVN1S73[8];
    U1  u1_tp_candata_AVN1SF7[32];
    U4  u4_t_lpcnt;

    vd_g_MemfillU1(&u1_tp_candata_AVN1S73[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_08);
    vd_g_MemfillU1(&u1_tp_candata_AVN1SF7[0], (U1)0U, (U4)XSPI_IVI_CAN_DLC_32);

    (void)Com_ReceiveSignal(ComConf_ComSignal_CD_SIZE, &u1_t_sgnl_cdsize);
    (void)Com_ReceiveSignal(ComConf_ComSignal_MM_RESET, &u1_t_sgnl_mmreset);
    (void)Com_ReceiveSignal(ComConf_ComSignal_HF_DISP, &u1_t_sgnl_hfdisp);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PVM_REQ, &u1_t_sgnl_pvmreq);


    for(u4_t_lpcnt = (U4)MSG_AVN1S01_TXCH0; u4_t_lpcnt <= (U4)MSG_MET1S33_TXCH0; u4_t_lpcnt++){
        if(u4_t_lpcnt == (U4)MSG_AVN1S73_TXCH0) {
            u1_tp_candata_AVN1S73[0] |= (u1_t_sgnl_mmreset & (U1)XSPI_IVI_CAN_MMRESET_MASK) << (U1)XSPI_IVI_SFT_02;
            u1_tp_candata_AVN1S73[6] |= (u1_t_sgnl_cdsize & (U1)XSPI_IVI_CAN_CDSIZE_MASK) << (U1)XSPI_IVI_SFT_04;
            u1_tp_candata_AVN1S73[6] |= (u1_t_sgnl_hfdisp & (U1)XSPI_IVI_CAN_HFDISP_MASK) << (U1)XSPI_IVI_SFT_02;
            (void)Com_SendIPDU((PduIdType)MSG_AVN1S73_TXCH0, &u1_tp_candata_AVN1S73[0] );
        } else if(u4_t_lpcnt == (U4)MSG_AVN1SF7_TXCH0) {
            u1_tp_candata_AVN1SF7[27] |= u1_t_sgnl_pvmreq & (U1)XSPI_IVI_CAN_PVMREQ_MASK;
            (void)Com_SendIPDU((PduIdType)MSG_AVN1SF7_TXCH0, &u1_tp_candata_AVN1SF7[0] );
        } else if(u4_t_lpcnt == (U4)MSG_MET1S33_TXCH0) {
            /*Do Nothing*/
        } else {
            (void)Com_InitIPDU((PduIdType)u4_t_lpcnt);
        }
    }
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

    /* Provisional (CANSignal To VM1) */
    U4 u4_t_dms1s02_adr;
    U4 u4_t_met1s27_adr;
    U4 u4_t_met1s28_adr;
    U4 u4_t_met1s29_adr;
    U4 u4_t_met1s30_adr;
    U4 u4_t_met1s43_adr;
    U4 u4_t_met1s62_adr;
    U4 u4_t_met1s70_adr;

    u4_t_dms1s02_adr = &u1_sp_Xspi_Ivi_DMS1S02_Data[0];
    u4_t_met1s27_adr = &u1_sp_Xspi_Ivi_MET1S27_Data[0];
    u4_t_met1s28_adr = &u1_sp_Xspi_Ivi_MET1S28_Data[0];
    u4_t_met1s29_adr = &u1_sp_Xspi_Ivi_MET1S29_Data[0];
    u4_t_met1s30_adr = &u1_sp_Xspi_Ivi_MET1S30_Data[0];
    u4_t_met1s43_adr = &u1_sp_Xspi_Ivi_MET1S43_Data[0];
    u4_t_met1s62_adr = &u1_sp_Xspi_Ivi_MET1S62_Data[0];
    u4_t_met1s70_adr = &u1_sp_Xspi_Ivi_MET1S70_Data[0];

    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_DMS1S02, &u4_t_dms1s02_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S27, &u4_t_met1s27_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S28, &u4_t_met1s28_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S29, &u4_t_met1s29_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S30, &u4_t_met1s30_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S43, &u4_t_met1s43_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S62, &u4_t_met1s62_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_MET1S70, &u4_t_met1s70_adr, (U2)XSPI_IVI_IVDSH_NWORD);
    /* Provisional (CANSignal To VM1) */

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
        vd_g_FwupxPutReqData(&u1_ap_XSPI_ADD[8], u2_t_dt_len);
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
    U1          u1_t_cd_size;

    U1          u1_t_parnm_sts;                         /* PartialNM用ステータスデータ格納用*/
    U1          u1_tp_parnm_data[XSPI_IVI_PARTIALNM_DATASIZE];                     /* PartialNM用PNCIDデータ格納用*/

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
        case XSPI_IVI_CANCOMMAND_PARNMSEND_REQ:
            vd_g_MemcpyU1(&u1_tp_parnm_data[0], &u1_tp_CNDT[u2_t_cancommandbuf + 9U], (U4)XSPI_IVI_PARTIALNM_DATASIZE);
            vd_g_PncReqctl_PartialNMSendReq(&u1_tp_parnm_data[0]);
            break;
        case XSPI_IVI_CANCOMMAND_PARNM_STS:
            u1_t_parnm_sts = u1_tp_CNDT[u2_t_cancommandbuf + 9U];
            vd_g_PncReqctl_PartialNMGetSts(u1_t_parnm_sts);
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
        u4_t_msg_canid  = (U4)(((u1_tp_CNMS_MSG[4] << XSPI_IVI_SFT_24) | (u1_tp_CNMS_MSG[5] << XSPI_IVI_SFT_16)) & 0x7FF00000U);
        if((u1_tp_CNMS_MSG[4] & (U1)0x80U) == (U4)0x00){
            /* 標準フォーマット */
            u4_t_msg_canid = u4_t_msg_canid >> 20U;
        }
        else {
            /* 拡張フォーマット 予備設計 */
            u4_t_msg_canid = u4_t_msg_canid >> 2U;
            u4_t_msg_canid |= (U4)(((u1_tp_CNMS_MSG[5] << XSPI_IVI_SFT_16) | (u1_tp_CNMS_MSG[6] << XSPI_IVI_SFT_08) | u1_tp_CNMS_MSG[7]) & 0x0003FFFFU);
        }
        u1_t_msg_dlc    = (U1)(u1_tp_CNMS_MSG[8]);
        /* DLCぶんCANデータを読出し */
        vd_g_MemcpyU1(&u1_tp_can_data[0], &u1_tp_CNMS_MSG[9], (U4)u1_t_msg_dlc);

        /* CANID → AubistIDに変換する */
        u4_t_msg_aubistid = u4_s_XspiIviBinarySearch(u4_t_msg_canid);
        
        if(u4_t_msg_aubistid != (U4)XSPI_IVI_BS_ERR){
        /* フレーム送信処理 */
            vd_g_CanCtlTx_SendHk(u4_t_msg_aubistid, &u1_tp_can_data[0]);
            (void)Com_SendIPDU((PduIdType)u4_t_msg_aubistid, &u1_tp_can_data[0] );
        }

        /* Provisional (CANSignal To VM1) */
        switch(u4_t_msg_canid) {
            case 0x00000427U:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_DMS1S02_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x000003EAU:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S27_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x0000037EU:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S28_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x000003ECU:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S29_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x000003EEU:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S30_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_32);
                break;
            case 0x00000529U:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S43_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x0000041AU:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S62_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_08);
                break;
            case 0x00000357U:
                vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_MET1S70_Data[0], &u1_tp_can_data[0], (U4)XSPI_IVI_CAN_DLC_32);
                break;
            default:
                break;
        }
        /* Provisional (CANSignal To VM1) */

        /* 読み出したデータ分ポインタを移動する */
        u1_tp_CNMS_MSG  = &u1_tp_CNMS_MSG[u1_tp_CNMS_CMS[0]];
        u1_tp_CNMS_CMS  = &u1_tp_CNMS_CMS[1];
    }
}

/*===================================================================================================================================*/
/*  static U4              u4_s_XspiIviBinarySearch(const U4 u4_a_CANID)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANID Conversion Process (Received ID → Aubist-defined ID)                                                       */
/*  Arguments:      u4_a_CANID   : CANID                                                                                             */
/*  Return:         u4_t_ret     : Aubist CANID(MSG_*******_TXCH*)                                                                   */
/*===================================================================================================================================*/
static U4              u4_s_XspiIviBinarySearch(const U4 u4_a_CANID) {
    /* ソート済みのCANIDとAubist定義のマッピング */
    static const ST_XSPI_IVI_CANID_PAIR st_sp_XSPISUB4_BSTBL[] = {
        {(U4)0x00000121U,    (U4)MSG_AVN1S38_TXCH0},
        {(U4)0x00000126U,    (U4)MSG_AVN1S34_TXCH0},
        {(U4)0x00000141U,    (U4)MSG_AVN1SG7_TXCH0},
        {(U4)0x0000014CU,    (U4)MSG_AVN1S71_TXCH0},
        {(U4)0x0000017FU,    (U4)MSG_AVN1S32_TXCH0},
        {(U4)0x00000185U,    (U4)MSG_AVN1SD4_TXCH0},
        {(U4)0x000001A1U,    (U4)MSG_AVN1SD6_TXCH0},
        {(U4)0x000001A2U,    (U4)MSG_AVN1SD7_TXCH0},
        {(U4)0x000001A3U,    (U4)MSG_AVN1SF6_TXCH0},
        {(U4)0x000001A5U,    (U4)MSG_AVN1SD8_TXCH0},
        {(U4)0x000001A7U,    (U4)MSG_AVN1SD9_TXCH0},
        {(U4)0x000001A8U,    (U4)MSG_AVN1SE9_TXCH0},
        {(U4)0x000001A9U,    (U4)MSG_AVN1SF1_TXCH0},
        {(U4)0x000001ABU,    (U4)MSG_AVN1SF2_TXCH0},
        {(U4)0x000001ACU,    (U4)MSG_AVN1SF3_TXCH0},
        {(U4)0x000001ADU,    (U4)MSG_AVN1SE3_TXCH0},
        {(U4)0x000001AEU,    (U4)MSG_AVN1SE8_TXCH0},
        {(U4)0x000001AFU,    (U4)MSG_AVN1SE4_TXCH0},
        {(U4)0x000001B0U,    (U4)MSG_AVN1SE5_TXCH0},
        {(U4)0x000001B3U,    (U4)MSG_AVN1SE6_TXCH0},
        {(U4)0x000001B4U,    (U4)MSG_AVN1SE7_TXCH0},
        {(U4)0x000001B5U,    (U4)MSG_AVN1SE2_TXCH0},
        {(U4)0x000001B7U,    (U4)MSG_AVN1SE1_TXCH0},
        {(U4)0x000001B8U,    (U4)MSG_AVN1SF4_TXCH0},
        {(U4)0x000001B9U,    (U4)MSG_AVN1SF5_TXCH0},
        {(U4)0x000001BDU,    (U4)MSG_AVN1S52_TXCH0},
        {(U4)0x000001ECU,    (U4)MSG_AVN1SA6_TXCH0},
        {(U4)0x000001F2U,    (U4)MSG_AVN1SB9_TXCH0},
        {(U4)0x000001FCU,    (U4)MSG_AVN1S40_TXCH0},
        {(U4)0x000001FDU,    (U4)MSG_AVN1S41_TXCH0},
        {(U4)0x000001FEU,    (U4)MSG_AVN1S42_TXCH0},
        {(U4)0x000001FFU,    (U4)MSG_AVN1S43_TXCH0},
        {(U4)0x000002AAU,    (U4)MSG_AVN1S73_TXCH0},
        {(U4)0x000002D2U,    (U4)MSG_AVN1SB7_TXCH0},
        {(U4)0x000002D3U,    (U4)MSG_AVN1SB8_TXCH0},
        {(U4)0x000002D4U,    (U4)MSG_AVN1SC1_TXCH0},
        {(U4)0x000002D5U,    (U4)MSG_AVN1SC2_TXCH0},
        {(U4)0x000002D6U,    (U4)MSG_AVN1SC3_TXCH0},
        {(U4)0x000002D7U,    (U4)MSG_AVN1SC4_TXCH0},
        {(U4)0x000002DFU,    (U4)MSG_AVN1SC5_TXCH0},
        {(U4)0x000002E0U,    (U4)MSG_AVN1SC6_TXCH0},
        {(U4)0x000002E1U,    (U4)MSG_AVN1SC7_TXCH0},
        {(U4)0x000002E2U,    (U4)MSG_AVN1SC8_TXCH0},
        {(U4)0x000002E3U,    (U4)MSG_AVN1SH1_TXCH0},
        {(U4)0x000002EFU,    (U4)MSG_AVN1SC9_TXCH0},
        {(U4)0x000002F0U,    (U4)MSG_AVN1SD1_TXCH0},
        {(U4)0x000002F2U,    (U4)MSG_AVN1SD2_TXCH0},
        {(U4)0x000002F5U,    (U4)MSG_AVN1SD3_TXCH0},
        {(U4)0x000002F6U,    (U4)MSG_AVN1SD5_TXCH0},
        {(U4)0x000002F7U,    (U4)MSG_AVN1SF7_TXCH0},
        {(U4)0x000002F8U,    (U4)MSG_AVN1SF8_TXCH0},
        {(U4)0x000002FAU,    (U4)MSG_AVN1SF9_TXCH0},
        {(U4)0x0000030EU,    (U4)MSG_AVN1S67_TXCH0},
        {(U4)0x0000030FU,    (U4)MSG_AVN1S68_TXCH0},
        {(U4)0x00000313U,    (U4)MSG_AVN1SB2_TXCH0},
        {(U4)0x00000315U,    (U4)MSG_MET1S33_TXCH0},
        {(U4)0x0000031AU,    (U4)MSG_AVN1S30_TXCH0},
        {(U4)0x0000031DU,    (U4)MSG_AVN1SA1_TXCH0},
        {(U4)0x00000322U,    (U4)MSG_AVN1SG4_TXCH0},
        {(U4)0x0000033AU,    (U4)MSG_AVN1SG3_TXCH0},
        {(U4)0x00000345U,    (U4)MSG_AVN1S94_TXCH0},
        {(U4)0x00000346U,    (U4)MSG_AVN1S95_TXCH0},
        {(U4)0x00000351U,    (U4)MSG_CDC1S04_TXCH0},
        {(U4)0x0000035AU,    (U4)MSG_AVN1SA7_TXCH0},
        {(U4)0x0000035BU,    (U4)MSG_AVN1S62_TXCH0},
        {(U4)0x00000384U,    (U4)MSG_AVN1S01_TXCH0},
        {(U4)0x00000386U,    (U4)MSG_AVN1S03_TXCH0},
        {(U4)0x00000387U,    (U4)MSG_AVN1S05_TXCH0},
        {(U4)0x00000388U,    (U4)MSG_AVN1S06_TXCH0},
        {(U4)0x00000389U,    (U4)MSG_AVN1S08_TXCH0},
        {(U4)0x0000038EU,    (U4)MSG_AVN1S04_TXCH0},
        {(U4)0x0000038FU,    (U4)MSG_AVN1S07_TXCH0},
        {(U4)0x000003A6U,    (U4)MSG_AVN1S46_TXCH0},
        {(U4)0x000003A7U,    (U4)MSG_AVN1S47_TXCH0},
        {(U4)0x000003A8U,    (U4)MSG_AVN1S70_TXCH0},
        {(U4)0x000003C0U,    (U4)MSG_AVN1S99_TXCH0},
        {(U4)0x000003C2U,    (U4)MSG_AVN1SA9_TXCH0},
        {(U4)0x000003C4U,    (U4)MSG_AVN1S78_TXCH0},
        {(U4)0x000003C9U,    (U4)MSG_AVN1S63_TXCH0},
        {(U4)0x000003D0U,    (U4)MSG_AVN1S76_TXCH0},
        {(U4)0x000003D9U,    (U4)MSG_AVN1S97_TXCH0},
        {(U4)0x000003E4U,    (U4)MSG_AVN1S98_TXCH0},
        {(U4)0x000003E6U,    (U4)MSG_AVN1S11_TXCH0},
        {(U4)0x000003F1U,    (U4)MSG_AVN1SA8_TXCH0},
        {(U4)0x000003FDU,    (U4)MSG_AVN1S77_TXCH0},
        {(U4)0x0000042EU,    (U4)MSG_AVN1S33_TXCH0},
        {(U4)0x00000434U,    (U4)MSG_AVN1S20_TXCH0},
        {(U4)0x00000435U,    (U4)MSG_AVN1S21_TXCH0},
        {(U4)0x00000436U,    (U4)MSG_AVN1S22_TXCH0},
        {(U4)0x00000437U,    (U4)MSG_AVN1S23_TXCH0},
        {(U4)0x0000043EU,    (U4)MSG_AVN1SG5_TXCH0},
        {(U4)0x00000490U,    (U4)MSG_AVN1S64_TXCH0},
        {(U4)0x00000515U,    (U4)MSG_AVN1SB3_TXCH0},
        {(U4)0x0000051AU,    (U4)MSG_AVN1SB4_TXCH0},
        {(U4)0x0000051BU,    (U4)MSG_AVN1SB5_TXCH0},
        {(U4)0x0000051DU,    (U4)MSG_AVN1S44_TXCH0},
        {(U4)0x0000051FU,    (U4)MSG_AVN1S65_TXCH0},
        {(U4)0x00000521U,    (U4)MSG_AVN1S69_TXCH0},
        {(U4)0x0000052AU,    (U4)MSG_AVN1S66_TXCH0},
        {(U4)0x0000058AU,    (U4)MSG_AVN1S39_TXCH0},
        {(U4)0x000005D1U,    (U4)MSG_AVN1SH2_TXCH0},
        {(U4)0x0000060CU,    (U4)MSG_AVN1SG6_TXCH0}
    };
    static const U4 u4_s_XSPI_IVI_BS_HALF   = (U4)2U;
    static const U4 u4_s_XSPI_IVI_BS_SFT_1  = (U4)1U;

    U4  u4_t_ret;
    U4  u4_t_size;
    U4  u4_t_left;
    U4  u4_t_right;
    U4  u4_t_mid;

    u4_t_ret    = (U4)XSPI_IVI_BS_ERR;
    u4_t_size   = (U4)(sizeof(st_sp_XSPISUB4_BSTBL) / sizeof(ST_XSPI_IVI_CANID_PAIR));
    u4_t_left   = (U4)0U;
    u4_t_right  = u4_t_size;

    while (u4_t_left < u4_t_right) {
        u4_t_mid = u4_t_left + (u4_t_right - u4_t_left) / u4_s_XSPI_IVI_BS_HALF;

        /* CANIDが中央の要素と一致する場合 */
        if (st_sp_XSPISUB4_BSTBL[u4_t_mid].u4_canid == u4_a_CANID) {
            u4_t_ret = st_sp_XSPISUB4_BSTBL[u4_t_mid].u4_aubist;
            break;
        }

        /* CANIDが中央の要素より小さい場合 */
        if (st_sp_XSPISUB4_BSTBL[u4_t_mid].u4_canid > u4_a_CANID) {
            u4_t_right = u4_t_mid;
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
    U1          u1_t_clock_event_jdg;

    u2_t_com_num = (U2)0x0000U;
    u2_t_com_len = (U2)0x0000U;
    u1_t_data_size = (U2)0U;

    if(u1_s_Xspi_Ivi_ClockUtc_recflg == (U1)FALSE) {
        if(u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CLOCK_UTC] >= (U4)XSPI_IVI_CLOCKUTC_SEND_TASK) {
            /*時計情報取得前*/
            vd_s_XspiIviClockUTCStuckBuff((U1)XSPI_IVI_CANCOMMAND_UTC_SEND,(U2)XSPI_IVI_CLOCKUTC_COMMAND_SIZE);
            u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CLOCK_UTC] = (U4)0U;
        }
    } else {
        /*時計情報変化時*/
        u1_t_clock_event_jdg = u1_s_XspiIviClockUTCDataEventJdg(&u1_sp_Xspi_Ivi_ClockUtcdata[0],&u1_sp_Xspi_Ivi_ClockUtcdata_pre[0],(U1)XSPI_IVI_CLOCKUTC_DATA_SIZE);
        if(u1_t_clock_event_jdg == (U1)TRUE) {
            vd_s_XspiIviClockUTCStuckBuff((U1)XSPI_IVI_CANCOMMAND_UTC_SEND,(U2)XSPI_IVI_CLOCKUTC_COMMAND_SIZE);
            u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CLOCK_UTC] = (U4)0U;
        }
        vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_ClockUtcdata_pre[0], &u1_sp_Xspi_Ivi_ClockUtcdata[0], (U4)XSPI_IVI_CLOCKUTC_DATA_SIZE);
    }

    /* CAN Commandデータ格納処理 */
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
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4AC00000U},   /*      0:MSG_ABG1D50_RXCH0    (103U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4BC00000U},   /*      1:MSG_ABG1D51_RXCH0    (104U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3B100000U},   /*      2:MSG_ABG1S01_RXCH0    (105U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1D800000U},   /*      3:MSG_ABG1S04_RXCH0    (106U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1D600000U},   /*      4:MSG_ABG1S09_RXCH0    (107U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4B800000U},   /*      5:MSG_ACN1D50_RXCH0    (108U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3A100000U},   /*      6:MSG_ACN1S03_RXCH0    (109U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x38100000U},   /*      7:MSG_ACN1S04_RXCH0    (110U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38200000U},   /*      8:MSG_ACN1S05_RXCH0    (111U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3B000000U},   /*      9:MSG_ACN1S07_RXCH0    (112U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40700000U},   /*     10:MSG_ACN1S15_RXCH0    (113U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40800000U},   /*     11:MSG_ACN1S16_RXCH0    (114U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35400000U},   /*     12:MSG_ACN1S22_RXCH0    (115U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x25500000U},   /*     13:MSG_ACN1S25_RXCH0    (116U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x50600000U},   /*     14:MSG_ACN1S29_RXCH0    (117U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x59400000U},   /*     15:MSG_ADC1S06_RXCH0    (118U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20700000U},   /*     16:MSG_ADC1S13_RXCH0    (119U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20800000U},   /*     17:MSG_ADC1S14_RXCH0    (120U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20900000U},   /*     18:MSG_ADC1S15_RXCH0    (121U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20A00000U},   /*     19:MSG_ADC1S17_RXCH0    (122U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x61300000U},   /*     20:MSG_ADC1S19_RXCH0    (123U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20B00000U},   /*     21:MSG_ADC1S23_RXCH0    (124U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34900000U},   /*     22:MSG_ADC1S30_RXCH0    (125U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x5D000000U},   /*     23:MSG_ADC1S33_RXCH0    (126U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x24700000U},   /*     24:MSG_ADU1S02_RXCH0    (127U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1F500000U},   /*     25:MSG_ADU1S03_RXCH0    (128U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1F000000U},   /*     26:MSG_ADU1S05_RXCH0    (129U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x22E00000U},   /*     27:MSG_ADU1S06_RXCH0    (130U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20E00000U},   /*     28:MSG_ADU1S07_RXCH0    (131U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x07200000U},   /*     29:MSG_ARS1S01_RXCH0    (132U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x21400000U},   /*     30:MSG_BAT1E41_RXCH0    (133U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x16E00000U},   /*     31:MSG_BAT1E45_RXCH0    (134U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3E500000U},   /*     32:MSG_BAT1S01_RXCH0    (135U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x12400000U},   /*     33:MSG_BAT1S08_RXCH0    (136U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1C100000U},   /*     34:MSG_BAT1S12_RXCH0    (137U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x27900000U},   /*     35:MSG_BAT2ED2_RXCH0    (138U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x37900000U},   /*     36:MSG_BCC1S05_RXCH0    (139U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3F300000U},   /*     37:MSG_BCC1S06_RXCH0    (140U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4A500000U},   /*     38:MSG_BDB1D50_RXCH0    (141U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38B00000U},   /*     39:MSG_BDB1F01_RXCH0    (142U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1F400000U},   /*     40:MSG_BDB1F03_RXCH0    (143U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1CF00000U},   /*     41:MSG_BDB1S01_RXCH0    (144U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x62200000U},   /*     42:MSG_BDB1S03_RXCH0    (145U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x62300000U},   /*     43:MSG_BDB1S04_RXCH0    (146U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38000000U},   /*     44:MSG_BDB1S05_RXCH0    (147U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x62400000U},   /*     45:MSG_BDB1S08_RXCH0    (148U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3FC00000U},   /*     46:MSG_BDB1S19_RXCH0    (149U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x30600000U},   /*     47:MSG_BDB1S25_RXCH0    (150U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x30500000U},   /*     48:MSG_BDB1S26_RXCH0    (151U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x62900000U},   /*     49:MSG_BDB1S27_RXCH0    (152U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x62A00000U},   /*     50:MSG_BDB1S28_RXCH0    (153U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x39700000U},   /*     51:MSG_BDB1S29_RXCH0    (154U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3B500000U},   /*     52:MSG_BDB1S35_RXCH0    (155U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3B800000U},   /*     53:MSG_BDB1S36_RXCH0    (156U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4B900000U},   /*     54:MSG_BDC1D00_RXCH0    (157U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4BA00000U},   /*     55:MSG_BDC1D01_RXCH0    (158U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x31200000U},   /*     56:MSG_BDC1S13_RXCH0    (159U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x32000000U},   /*     57:MSG_BDC1S14_RXCH0    (160U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x32A00000U},   /*     58:MSG_BDC1S16_RXCH0    (161U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x37300000U},   /*     59:MSG_BDC1S20_RXCH0    (162U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x18600000U},   /*     60:MSG_BDC1S30_RXCH0    (163U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1D200000U},   /*     61:MSG_BDC1S33_RXCH0    (164U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x09C00000U},   /*     62:MSG_BDC1S40_RXCH0    (165U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x14800000U},   /*     63:MSG_BDC1S41_RXCH0    (166U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x36400000U},   /*     64:MSG_BDC1S45_RXCH0    (167U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1D300000U},   /*     65:MSG_BDC1S46_RXCH0    (168U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x33700000U},   /*     66:MSG_BDC1S48_RXCH0    (169U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x01B00000U},   /*     67:MSG_BDC1S60_RXCH0    (170U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34100000U},   /*     68:MSG_BDC1S74_RXCH0    (171U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1E300000U},   /*     69:MSG_BDC1S81_RXCH0    (172U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x15000000U},   /*     70:MSG_BDC1S82_RXCH0    (173U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x36700000U},   /*     71:MSG_BDC1S83_RXCH0    (174U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1E400000U},   /*     72:MSG_BDC1S91_RXCH0    (175U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35500000U},   /*     73:MSG_BDC1S97_RXCH0    (176U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35800000U},   /*     74:MSG_BDC1S98_RXCH0    (177U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35D00000U},   /*     75:MSG_BDC1S99_RXCH0    (178U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A400000U},   /*     76:MSG_BDC1SA0_RXCH0    (179U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35F00000U},   /*     77:MSG_BDC1SA1_RXCH0    (180U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39300000U},   /*     78:MSG_BDC1SC1_RXCH0    (181U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39500000U},   /*     79:MSG_BDC1SC2_RXCH0    (182U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39600000U},   /*     80:MSG_BDC1SC3_RXCH0    (183U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39A00000U},   /*     81:MSG_BDC1SC4_RXCH0    (184U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39B00000U},   /*     82:MSG_BDC1SC5_RXCH0    (185U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39D00000U},   /*     83:MSG_BDC1SC6_RXCH0    (186U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39E00000U},   /*     84:MSG_BDC1SC7_RXCH0    (187U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x39F00000U},   /*     85:MSG_BDC1SC8_RXCH0    (188U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3A500000U},   /*     86:MSG_BDC1SC9_RXCH0    (189U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3AC00000U},   /*     87:MSG_BDC1SD1_RXCH0    (190U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3AE00000U},   /*     88:MSG_BDC1SD2_RXCH0    (191U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3B200000U},   /*     89:MSG_BDC1SD3_RXCH0    (192U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3B300000U},   /*     90:MSG_BDC1SD4_RXCH0    (193U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3B900000U},   /*     91:MSG_BDC1SD5_RXCH0    (194U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3BC00000U},   /*     92:MSG_BDC1SD6_RXCH0    (195U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3C600000U},   /*     93:MSG_BDC1SD7_RXCH0    (196U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3C700000U},   /*     94:MSG_BDC1SD8_RXCH0    (197U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3CD00000U},   /*     95:MSG_BDC1SD9_RXCH0    (198U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3D300000U},   /*     96:MSG_BDC1SE1_RXCH0    (199U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3D600000U},   /*     97:MSG_BDC1SE2_RXCH0    (200U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3DD00000U},   /*     98:MSG_BDC1SE3_RXCH0    (201U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3E100000U},   /*     99:MSG_BDC1SE4_RXCH0    (202U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3EB00000U},   /*    100:MSG_BDC1SE5_RXCH0    (203U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3EF00000U},   /*    101:MSG_BDC1SE6_RXCH0    (204U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3F500000U},   /*    102:MSG_BDC1SE7_RXCH0    (205U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x42300000U},   /*    103:MSG_BDC1SE8_RXCH0    (206U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x42900000U},   /*    104:MSG_BDC1SE9_RXCH0    (207U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x43000000U},   /*    105:MSG_BDC1SF1_RXCH0    (208U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x48000000U},   /*    106:MSG_BDC1SF2_RXCH0    (209U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x48400000U},   /*    107:MSG_BDC1SF3_RXCH0    (210U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x49100000U},   /*    108:MSG_BDC1SF4_RXCH0    (211U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x34E00000U},   /*    109:MSG_BDC1SF5_RXCH0    (212U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x49700000U},   /*    110:MSG_BDC1SF6_RXCH0    (213U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x52600000U},   /*    111:MSG_BDC1SG4_RXCH0    (214U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x52B00000U},   /*    112:MSG_BDC1SG6_RXCH0    (215U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x52C00000U},   /*    113:MSG_BDC1SG7_RXCH0    (216U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53000000U},   /*    114:MSG_BDC1SG8_RXCH0    (217U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53100000U},   /*    115:MSG_BDC1SG9_RXCH0    (218U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53400000U},   /*    116:MSG_BDC1SH3_RXCH0    (219U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53500000U},   /*    117:MSG_BDC1SH4_RXCH0    (220U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53700000U},   /*    118:MSG_BDC1SH5_RXCH0    (221U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53800000U},   /*    119:MSG_BDC1SH6_RXCH0    (222U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2B300000U},   /*    120:MSG_BDC1SH8_RXCH0    (223U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3CE00000U},   /*    121:MSG_BDC1SI0_RXCH0    (224U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3E800000U},   /*    122:MSG_BDC1SI1_RXCH0    (225U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3E900000U},   /*    123:MSG_BDC1SI2_RXCH0    (226U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3F400000U},   /*    124:MSG_BDC1SI3_RXCH0    (227U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x31E00000U},   /*    125:MSG_BDC1SI4_RXCH0    (228U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x31F00000U},   /*    126:MSG_BDC1SI5_RXCH0    (229U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x32100000U},   /*    127:MSG_BDC1SI6_RXCH0    (230U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x50800000U},   /*    128:MSG_BDC1SI7_RXCH0    (231U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x50B00000U},   /*    129:MSG_BDC1SI8_RXCH0    (232U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x50C00000U},   /*    130:MSG_BDC1SI9_RXCH0    (233U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x50E00000U},   /*    131:MSG_BDC1SJ0_RXCH0    (234U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x48500000U},   /*    132:MSG_BDC1SJ1_RXCH0    (235U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x50D00000U},   /*    133:MSG_BDC1SJ2_RXCH0    (236U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x53600000U},   /*    134:MSG_BDC1SJ3_RXCH0    (237U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x36100000U},   /*    135:MSG_BDC1SJ4_RXCH0    (238U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x37800000U},   /*    136:MSG_BDC1SJ5_RXCH0    (239U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3C300000U},   /*    137:MSG_BDC1SJ6_RXCH0    (240U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3F200000U},   /*    138:MSG_BDC1SJ7_RXCH0    (241U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x43C00000U},   /*    139:MSG_BDC1SJ8_RXCH0    (242U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x61000000U},   /*    140:MSG_BDC1SV1_RXCH0    (243U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x60200000U},   /*    141:MSG_BDC1SV2_RXCH0    (244U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x37B00000U},   /*    142:MSG_BDF3S01_RXCH0    (245U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x18D00000U},   /*    143:MSG_BDF3S02_RXCH0    (246U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x19A00000U},   /*    144:MSG_BDR3S02_RXCH0    (247U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3F600000U},   /*    145:MSG_BSR1S01_RXCH0    (248U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x23500000U},   /*    146:MSG_BSR1S02_RXCH0    (249U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2AF00000U},   /*    147:MSG_BSR1S03_RXCH0    (250U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x33300000U},   /*    148:MSG_CDC1S01_RXCH0    (251U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1D900000U},   /*    149:MSG_CMB1S03_RXCH0    (252U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2F300000U},   /*    150:MSG_CMB1S04_RXCH0    (253U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x0A900000U},   /*    151:MSG_CSR1G10_RXCH0    (254U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43A00000U},   /*    152:MSG_CSR1S04_RXCH0    (255U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3DB00000U},   /*    153:MSG_CSR1S07_RXCH0    (256U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43800000U},   /*    154:MSG_DCM1S01_RXCH0    (257U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34F00000U},   /*    155:MSG_DCM1S03_RXCH0    (258U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x36300000U},   /*    156:MSG_DCM1S04_RXCH0    (259U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34800000U},   /*    157:MSG_DCM1S08_RXCH0    (260U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x27D00000U},   /*    158:MSG_DDM1S00_RXCH0    (261U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x12B00000U},   /*    159:MSG_DDM1S09_RXCH0    (262U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x0B800000U},   /*    160:MSG_DDM1S12_RXCH0    (263U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2EE00000U},   /*    161:MSG_DDM1S16_RXCH0    (264U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1D700000U},   /*    162:MSG_DDM1S17_RXCH0    (265U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2DA00000U},   /*    163:MSG_DDM1S20_RXCH0    (266U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x21900000U},   /*    164:MSG_DDM1S32_RXCH0    (267U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2E500000U},   /*    165:MSG_DDM1S35_RXCH0    (268U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x28200000U},   /*    166:MSG_DDM1SFH_RXCH0    (269U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x52800000U},   /*    167:MSG_DKY1S26_RXCH0    (270U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x28500000U},   /*    168:MSG_DS11S27_RXCH0    (271U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x31700000U},   /*    169:MSG_DS11S37_RXCH0    (272U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x60800000U},   /*    170:MSG_DS11S40_RXCH0    (273U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x41100000U},   /*    171:MSG_DS12F02_RXCH0    (274U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x41200000U},   /*    172:MSG_DS12F03_RXCH0    (275U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3F000000U},   /*    173:MSG_DST1S02_RXCH0    (276U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4A000000U},   /*    174:MSG_EBU1D01_RXCH0    (277U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3BF00000U},   /*    175:MSG_ECT1G01_RXCH0    (278U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2A100000U},   /*    176:MSG_ECT1G92_RXCH0    (279U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40100000U},   /*    177:MSG_ECT1S93_RXCH0    (280U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1BC00000U},   /*    178:MSG_EHV1E96_RXCH0    (281U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x07E00000U},   /*    179:MSG_EHV1F02_RXCH0    (282U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x0A500000U},   /*    180:MSG_EHV1F04_RXCH0    (283U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2A700000U},   /*    181:MSG_EHV1G70_RXCH0    (284U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2A800000U},   /*    182:MSG_EHV1G71_RXCH0    (285U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1D000000U},   /*    183:MSG_EHV1S23_RXCH0    (286U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x32500000U},   /*    184:MSG_EHV1S31_RXCH0    (287U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40B00000U},   /*    185:MSG_EHV1S95_RXCH0    (288U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1FA00000U},   /*    186:MSG_EHV1S96_RXCH0    (289U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42B00000U},   /*    187:MSG_EHV1S97_RXCH0    (290U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2DE00000U},   /*    188:MSG_EHV1S99_RXCH0    (291U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2EB00000U},   /*    189:MSG_EHV1SL2_RXCH0    (292U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x0A600000U},   /*    190:MSG_EHV2G02_RXCH0    (293U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x0A100000U},   /*    191:MSG_EHV2G20_RXCH0    (294U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20200000U},   /*    192:MSG_EHV2G70_RXCH0    (295U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x5F300000U},   /*    193:MSG_ENG1C01_RXCH0    (296U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x5F400000U},   /*    194:MSG_ENG1C02_RXCH0    (297U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49900000U},   /*    195:MSG_ENG1D51_RXCH0    (298U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49A00000U},   /*    196:MSG_ENG1D52_RXCH0    (299U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49B00000U},   /*    197:MSG_ENG1D53_RXCH0    (300U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49D00000U},   /*    198:MSG_ENG1D55_RXCH0    (301U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4A800000U},   /*    199:MSG_ENG1D56_RXCH0    (302U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4AE00000U},   /*    200:MSG_ENG1D59_RXCH0    (303U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4AF00000U},   /*    201:MSG_ENG1D60_RXCH0    (304U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x0A400000U},   /*    202:MSG_ENG1G03_RXCH0    (305U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x51E00000U},   /*    203:MSG_ENG1G90_RXCH0    (306U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x0FC00000U},   /*    204:MSG_ENG1G92_RXCH0    (307U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x59200000U},   /*    205:MSG_ENG1S51_RXCH0    (308U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x58900000U},   /*    206:MSG_ENG1S60_RXCH0    (309U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x4A300000U},   /*    207:MSG_EPS1D50_RXCH0    (310U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x06200000U},   /*    208:MSG_EPS1S11_RXCH0    (311U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x5F600000U},   /*    209:MSG_FCM1C01_RXCH0    (312U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x5F100000U},   /*    210:MSG_FCM1C03_RXCH0    (313U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x48900000U},   /*    211:MSG_FCM1S10_RXCH0    (314U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x48B00000U},   /*    212:MSG_FCM1S12_RXCH0    (315U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x25100000U},   /*    213:MSG_FCM1S39_RXCH0    (316U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x26100000U},   /*    214:MSG_FCM1S41_RXCH0    (317U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x27400000U},   /*    215:MSG_FCM1S49_RXCH0    (318U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x27500000U},   /*    216:MSG_FCM1S51_RXCH0    (319U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x27600000U},   /*    217:MSG_FCM1S52_RXCH0    (320U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x28A00000U},   /*    218:MSG_FCM1S66_RXCH0    (321U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x25A00000U},   /*    219:MSG_FCM1S70_RXCH0    (322U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x10000000U},   /*    220:MSG_FCM1S79_RXCH0    (323U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x20F00000U},   /*    221:MSG_FCM1S88_RXCH0    (324U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B200000U},   /*    222:MSG_FCM1S90_RXCH0    (325U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x0A800000U},   /*    223:MSG_FCM1S95_RXCH0    (326U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3FB00000U},   /*    224:MSG_IDT1S07_RXCH0    (327U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x14B00000U},   /*    225:MSG_IDT1S08_RXCH0    (328U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x53200000U},   /*    226:MSG_IDT1S15_RXCH0    (329U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43B00000U},   /*    227:MSG_IPA1S05_RXCH0    (330U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x36B00000U},   /*    228:MSG_ITS1S01_RXCH0    (331U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3DE00000U},   /*    229:MSG_ITS1S04_RXCH0    (332U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x27B00000U},   /*    230:MSG_ITS1S08_RXCH0    (333U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49400000U},   /*    231:MSG_LVN1S01_RXCH0    (334U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x61100000U},   /*    232:MSG_MET1S02_RXCH0    (335U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x61500000U},   /*    233:MSG_MET1S11_RXCH0    (336U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x52400000U},   /*    234:MSG_MET1S38_RXCH0    (337U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1DC00000U},   /*    235:MSG_MET1S47_RXCH0    (338U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1F700000U},   /*    236:MSG_MET1S55_RXCH0    (339U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x04900000U},   /*    237:MSG_MGC1F13_RXCH0    (340U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3BD00000U},   /*    238:MSG_PCN1S01_RXCH0    (341U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1CC00000U},   /*    239:MSG_PDC1G01_RXCH0    (342U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x50700000U},   /*    240:MSG_PDC1G02_RXCH0    (343U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x29500000U},   /*    241:MSG_PLG1G15_RXCH0    (344U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x29600000U},   /*    242:MSG_PLG1G16_RXCH0    (345U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42200000U},   /*    243:MSG_PLG1S01_RXCH0    (346U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43200000U},   /*    244:MSG_PLG1S06_RXCH0    (347U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2A600000U},   /*    245:MSG_PLG1S20_RXCH0    (348U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x20400000U},   /*    246:MSG_PLG1S21_RXCH0    (349U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1D100000U},   /*    247:MSG_PMN1G03_RXCH0    (350U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40300000U},   /*    248:MSG_PST1S01_RXCH0    (351U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40500000U},   /*    249:MSG_PST1S02_RXCH0    (352U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x14D00000U},   /*    250:MSG_RCP1S01_RXCH0    (353U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x23000000U},   /*    251:MSG_RCP1S02_RXCH0    (354U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x14F00000U},   /*    252:MSG_RCP1S03_RXCH0    (355U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2C600000U},   /*    253:MSG_RCP1S04_RXCH0    (356U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2C700000U},   /*    254:MSG_RCP1S05_RXCH0    (357U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2C800000U},   /*    255:MSG_RCP1S06_RXCH0    (358U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3CA00000U},   /*    256:MSG_RSE1G20_RXCH0    (359U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x32F00000U},   /*    257:MSG_RSE1G24_RXCH0    (360U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x33600000U},   /*    258:MSG_RSE1G25_RXCH0    (361U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34D00000U},   /*    259:MSG_RSE1G26_RXCH0    (362U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x32800000U},   /*    260:MSG_RST1S03_RXCH0    (363U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43900000U},   /*    261:MSG_SCN1S01_RXCH0    (364U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x37500000U},   /*    262:MSG_SCN1S02_RXCH0    (365U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4A900000U},   /*    263:MSG_SCS1D50_RXCH0    (366U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x10B00000U},   /*    264:MSG_SCS1S10_RXCH0    (367U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2FD00000U},   /*    265:MSG_SCS1S11_RXCH0    (368U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2FE00000U},   /*    266:MSG_SCS1S14_RXCH0    (369U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40C00000U},   /*    267:MSG_SOL1S02_RXCH0    (370U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x40D00000U},   /*    268:MSG_SOL1S03_RXCH0    (371U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1EB00000U},   /*    269:MSG_SOL1S04_RXCH0    (372U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1EA00000U},   /*    270:MSG_SOL1S05_RXCH0    (373U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1BB00000U},   /*    271:MSG_SOL1S06_RXCH0    (374U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49500000U},   /*    272:MSG_TPM1S02_RXCH0    (375U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49600000U},   /*    273:MSG_TPM1S03_RXCH0    (376U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34700000U},   /*    274:MSG_TPM1S04_RXCH0    (377U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34C00000U},   /*    275:MSG_TPM1S05_RXCH0    (378U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x41700000U},   /*    276:MSG_TPM1S06_RXCH0    (379U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x36F00000U},   /*    277:MSG_TPM1S07_RXCH0    (380U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x41800000U},   /*    278:MSG_TPM1S08_RXCH0    (381U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42600000U},   /*    279:MSG_TPM1S09_RXCH0    (382U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42800000U},   /*    280:MSG_TPM1S10_RXCH0    (383U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42A00000U},   /*    281:MSG_TPM1S11_RXCH0    (384U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42C00000U},   /*    282:MSG_TPM1S12_RXCH0    (385U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2A000000U},   /*    283:MSG_TRA1S01_RXCH0    (386U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x0A000000U},   /*    284:MSG_TRA1S02_RXCH0    (387U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3E700000U},   /*    285:MSG_UCB1S01_RXCH0    (388U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4A400000U},   /*    286:MSG_VGR1D50_RXCH0    (389U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x4A100000U},   /*    287:MSG_VSC1D51_RXCH0    (390U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x06A00000U},   /*    288:MSG_VSC1F01_RXCH0    (391U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x06900000U},   /*    289:MSG_VSC1G12_RXCH0    (392U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x09E00000U},   /*    290:MSG_VSC1G13_RXCH0    (393U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x0B700000U},   /*    291:MSG_VSC1G14_RXCH0    (394U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x26200000U},   /*    292:MSG_VSC1G96_RXCH0    (395U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x60100000U},   /*    293:MSG_VUM1S01_RXCH0    (396U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2F900000U},   /*    294:MSG_WIP1S01_RXCH0    (397U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x37F00000U},   /*    295:MSG_ZN11S02_RXCH0    (398U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38A00000U},   /*    296:MSG_ZN11S03_RXCH0    (399U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x08600000U},   /*    297:MSG_ZN11S08_RXCH0    (400U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1DE00000U},   /*    298:MSG_ZN11S14_RXCH0    (401U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1DF00000U},   /*    299:MSG_ZN11S17_RXCH0    (402U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x36800000U},   /*    300:MSG_ZN11S19_RXCH0    (403U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x39800000U},   /*    301:MSG_ZN11S25_RXCH0    (404U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x36A00000U},   /*    302:MSG_ZN11S26_RXCH0    (405U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x50000000U},   /*    303:MSG_ZN11S38_RXCH0    (406U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x36E00000U},   /*    304:MSG_ZN11S60_RXCH0    (407U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x33F00000U},   /*    305:MSG_ZN11S63_RXCH0    (408U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3D200000U},   /*    306:MSG_ZN11S64_RXCH0    (409U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3F900000U},   /*    307:MSG_ZN11S65_RXCH0    (410U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x40000000U},   /*    308:MSG_ZN11S66_RXCH0    (411U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x40400000U},   /*    309:MSG_ZN11S67_RXCH0    (412U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35300000U},   /*    310:MSG_ZN11SF8_RXCH0    (413U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3BB00000U},   /*    311:MSG_ZN11SF9_RXCH0    (414U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1E100000U},   /*    312:MSG_ZN21S05_RXCH0    (415U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x39000000U},   /*    313:MSG_ZN21S13_RXCH0    (416U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1BE00000U},   /*    314:MSG_ZN21S28_RXCH0    (417U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1CE00000U},   /*    315:MSG_ZN21S52_RXCH0    (418U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3A900000U}    /*    316:MSG_ZN21S72_RXCH0    (419U) */
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
/*  void            vd_g_XspiIviCANSendFrmGWPushPDU(const U2 u2_a_MSG)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    User Hook IF(Send CAN Frame)                                                                                     */
/*  Arguments:      u2_a_MSG : Send CAN Frame                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviCANSendFrmGWPushPDU(const U2 u2_a_MSG)
{
    static const U2 u2_s_XSPI_IVI_SENDCANGW_MIN      = (U2)MSG_AVN1S01_TXCH0;
    static const U2 u2_s_XSPI_IVI_SENDCANGW_MAX      = (U2)MSG_MET1S33_TXCH0;

    static const ST_XSPI_IVI_MSG2POSLEN st_sp_XSPI_SNDMSG2POSLEN[] = {
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x38400000U},   /*      0:MSG_AVN1S01_TXCH0    (  0U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x38600000U},   /*      1:MSG_AVN1S03_TXCH0    (  1U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38E00000U},   /*      2:MSG_AVN1S04_TXCH0    (  2U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38700000U},   /*      3:MSG_AVN1S05_TXCH0    (  3U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38800000U},   /*      4:MSG_AVN1S06_TXCH0    (  4U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38F00000U},   /*      5:MSG_AVN1S07_TXCH0    (  5U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x38900000U},   /*      6:MSG_AVN1S08_TXCH0    (  6U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3E600000U},   /*      7:MSG_AVN1S11_TXCH0    (  7U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43400000U},   /*      8:MSG_AVN1S20_TXCH0    (  8U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43500000U},   /*      9:MSG_AVN1S21_TXCH0    (  9U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43600000U},   /*     10:MSG_AVN1S22_TXCH0    ( 10U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x43700000U},   /*     11:MSG_AVN1S23_TXCH0    ( 11U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x31A00000U},   /*     12:MSG_AVN1S30_TXCH0    ( 12U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x17F00000U},   /*     13:MSG_AVN1S32_TXCH0    ( 13U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x42E00000U},   /*     14:MSG_AVN1S33_TXCH0    ( 14U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x12600000U},   /*     15:MSG_AVN1S34_TXCH0    ( 15U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x12100000U},   /*     16:MSG_AVN1S38_TXCH0    ( 16U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x58A00000U},   /*     17:MSG_AVN1S39_TXCH0    ( 17U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1FC00000U},   /*     18:MSG_AVN1S40_TXCH0    ( 18U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1FD00000U},   /*     19:MSG_AVN1S41_TXCH0    ( 19U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1FE00000U},   /*     20:MSG_AVN1S42_TXCH0    ( 20U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1FF00000U},   /*     21:MSG_AVN1S43_TXCH0    ( 21U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x51D00000U},   /*     22:MSG_AVN1S44_TXCH0    ( 22U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3A600000U},   /*     23:MSG_AVN1S46_TXCH0    ( 23U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3A700000U},   /*     24:MSG_AVN1S47_TXCH0    ( 24U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1BD00000U},   /*     25:MSG_AVN1S52_TXCH0    ( 25U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x35B00000U},   /*     26:MSG_AVN1S62_TXCH0    ( 26U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3C900000U},   /*     27:MSG_AVN1S63_TXCH0    ( 27U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x49000000U},   /*     28:MSG_AVN1S64_TXCH0    ( 28U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x51F00000U},   /*     29:MSG_AVN1S65_TXCH0    ( 29U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x52A00000U},   /*     30:MSG_AVN1S66_TXCH0    ( 30U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x30E00000U},   /*     31:MSG_AVN1S67_TXCH0    ( 31U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x30F00000U},   /*     32:MSG_AVN1S68_TXCH0    ( 32U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x52100000U},   /*     33:MSG_AVN1S69_TXCH0    ( 33U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3A800000U},   /*     34:MSG_AVN1S70_TXCH0    ( 34U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x14C00000U},   /*     35:MSG_AVN1S71_TXCH0    ( 35U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2AA00000U},   /*     36:MSG_AVN1S73_TXCH0    ( 36U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3D000000U},   /*     37:MSG_AVN1S76_TXCH0    ( 37U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3FD00000U},   /*     38:MSG_AVN1S77_TXCH0    ( 38U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3C400000U},   /*     39:MSG_AVN1S78_TXCH0    ( 39U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34500000U},   /*     40:MSG_AVN1S94_TXCH0    ( 40U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x34600000U},   /*     41:MSG_AVN1S95_TXCH0    ( 41U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3D900000U},   /*     42:MSG_AVN1S97_TXCH0    ( 42U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3E400000U},   /*     43:MSG_AVN1S98_TXCH0    ( 43U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x3C000000U},   /*     44:MSG_AVN1S99_TXCH0    ( 44U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x31D00000U},   /*     45:MSG_AVN1SA1_TXCH0    ( 45U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1EC00000U},   /*     46:MSG_AVN1SA6_TXCH0    ( 46U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x35A00000U},   /*     47:MSG_AVN1SA7_TXCH0    ( 47U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x3F100000U},   /*     48:MSG_AVN1SA8_TXCH0    ( 48U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x3C200000U},   /*     49:MSG_AVN1SA9_TXCH0    ( 49U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x31300000U},   /*     50:MSG_AVN1SB2_TXCH0    ( 50U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x51500000U},   /*     51:MSG_AVN1SB3_TXCH0    ( 51U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x51A00000U},   /*     52:MSG_AVN1SB4_TXCH0    ( 52U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x51B00000U},   /*     53:MSG_AVN1SB5_TXCH0    ( 53U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2D200000U},   /*     54:MSG_AVN1SB7_TXCH0    ( 54U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2D300000U},   /*     55:MSG_AVN1SB8_TXCH0    ( 55U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1F200000U},   /*     56:MSG_AVN1SB9_TXCH0    ( 56U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2D400000U},   /*     57:MSG_AVN1SC1_TXCH0    ( 57U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2D500000U},   /*     58:MSG_AVN1SC2_TXCH0    ( 58U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2D600000U},   /*     59:MSG_AVN1SC3_TXCH0    ( 59U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2D700000U},   /*     60:MSG_AVN1SC4_TXCH0    ( 60U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2DF00000U},   /*     61:MSG_AVN1SC5_TXCH0    ( 61U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2E000000U},   /*     62:MSG_AVN1SC6_TXCH0    ( 62U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2E100000U},   /*     63:MSG_AVN1SC7_TXCH0    ( 63U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2E200000U},   /*     64:MSG_AVN1SC8_TXCH0    ( 64U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2EF00000U},   /*     65:MSG_AVN1SC9_TXCH0    ( 65U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2F000000U},   /*     66:MSG_AVN1SD1_TXCH0    ( 66U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2F200000U},   /*     67:MSG_AVN1SD2_TXCH0    ( 67U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_64,    (U4)0x2F500000U},   /*     68:MSG_AVN1SD3_TXCH0    ( 68U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x18500000U},   /*     69:MSG_AVN1SD4_TXCH0    ( 69U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x2F600000U},   /*     70:MSG_AVN1SD5_TXCH0    ( 70U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A100000U},   /*     71:MSG_AVN1SD6_TXCH0    ( 71U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A200000U},   /*     72:MSG_AVN1SD7_TXCH0    ( 72U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A500000U},   /*     73:MSG_AVN1SD8_TXCH0    ( 73U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A700000U},   /*     74:MSG_AVN1SD9_TXCH0    ( 74U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B700000U},   /*     75:MSG_AVN1SE1_TXCH0    ( 75U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B500000U},   /*     76:MSG_AVN1SE2_TXCH0    ( 76U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1AD00000U},   /*     77:MSG_AVN1SE3_TXCH0    ( 77U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1AF00000U},   /*     78:MSG_AVN1SE4_TXCH0    ( 78U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B000000U},   /*     79:MSG_AVN1SE5_TXCH0    ( 79U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B300000U},   /*     80:MSG_AVN1SE6_TXCH0    ( 80U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B400000U},   /*     81:MSG_AVN1SE7_TXCH0    ( 81U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1AE00000U},   /*     82:MSG_AVN1SE8_TXCH0    ( 82U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A800000U},   /*     83:MSG_AVN1SE9_TXCH0    ( 83U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1A900000U},   /*     84:MSG_AVN1SF1_TXCH0    ( 84U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1AB00000U},   /*     85:MSG_AVN1SF2_TXCH0    ( 85U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1AC00000U},   /*     86:MSG_AVN1SF3_TXCH0    ( 86U) */
        {   (U1)TRUE,   (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B800000U},   /*     87:MSG_AVN1SF4_TXCH0    ( 87U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x1B900000U},   /*     88:MSG_AVN1SF5_TXCH0    ( 88U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x1A300000U},   /*     89:MSG_AVN1SF6_TXCH0    ( 89U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2F700000U},   /*     90:MSG_AVN1SF7_TXCH0    ( 90U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2F800000U},   /*     91:MSG_AVN1SF8_TXCH0    ( 91U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2FA00000U},   /*     92:MSG_AVN1SF9_TXCH0    ( 92U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x33A00000U},   /*     93:MSG_AVN1SG3_TXCH0    ( 93U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x32200000U},   /*     94:MSG_AVN1SG4_TXCH0    ( 94U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x43E00000U},   /*     95:MSG_AVN1SG5_TXCH0    ( 95U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x60C00000U},   /*     96:MSG_AVN1SG6_TXCH0    ( 96U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x14100000U},   /*     97:MSG_AVN1SG7_TXCH0    ( 97U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x2E300000U},   /*     98:MSG_AVN1SH1_TXCH0    ( 98U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_32,    (U4)0x5D100000U},   /*     99:MSG_AVN1SH2_TXCH0    ( 99U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x35100000U},   /*    100:MSG_CDC1S04_TXCH0    (100U) */
        {   (U1)FALSE,  (U1)XSPI_IVI_CAN_DLC_08,    (U4)0x31500000U}    /*    101:MSG_MET1S33_TXCH0    (101U) */
    };

    U1  u1_t_act;
    U2  u2_t_idx;
    U1  u1_t_dlc;
    U4  u4_t_time;
    U1  u1_tp_sgnl[XSPI_IVI_CAN_64];

    if ((u2_a_MSG >= u2_s_XSPI_IVI_SENDCANGW_MIN) &&
       (u2_a_MSG <= u2_s_XSPI_IVI_SENDCANGW_MAX)    ) {
        u2_t_idx = (U2)(u2_a_MSG - u2_s_XSPI_IVI_SENDCANGW_MIN);
        u1_t_act = st_sp_XSPI_SNDMSG2POSLEN[u2_t_idx].u1_act;
        if (u1_t_act != (U1)FALSE) {
            /* Send CAN Frame */
            u1_t_dlc = st_sp_XSPI_SNDMSG2POSLEN[u2_t_idx].u1_dlc;
            vd_g_MemfillU1(&u1_tp_sgnl[0], (U1)0U, (U4)XSPI_IVI_CAN_64);
            (void)Com_ReadIPDU((PduIdType)u2_a_MSG, &u1_tp_sgnl[0] );

            /* TimeStamp */
            u4_t_time = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
            u4_t_time = (U4)(u4_t_time / MCU_FRT_1MS);

            vd_s_XspiIviCANGWStuckBuff(u4_t_time, st_sp_XSPI_SNDMSG2POSLEN[u2_t_idx].u4_flame_id, u1_t_dlc, &u1_tp_sgnl[0]);
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviCANGWPushPDU(const U4 * const u4_ap_QSEV_RX)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    QSEv受信によるユーザフック処理                                                                                     */
/*  Arguments:      u4_ap_QSEV_RX : 受信したQSEv情報                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviQSEvGWPushPDU(const U4 * const u4_ap_QSEV_RX)
{
    static const U1 u1_s_POS_HEAD   = (U1)0U;
    static const U1 u1_s_POS_CANID  = (U1)1U;
    static const U1 u1_s_POS_DATA   = (U1)2U;
    static const U1 u1_s_SFT_BASEID = (U1)2U;
    static const U4 u4_s_MSK_DL     = (U4)0x000000FFU;  /* Data Length Mask for HEAD */
    static const U4 u4_s_MSK_BASEID = (U4)0x1FFC0000U;  /* Bsse CAN ID Mask for CAN-ID */
    static const U4 u4_s_MSK_EXTID  = (U4)0x0003FFFFU;  /* Extended CAN ID Mask for CAN-ID */
    static const U4 u4_s_FLG_EXT    = (U4)0x80000000U;  /* Extended CAN ID Flag */

    U4      u4_t_time;
    U4      u4_t_canid;
    U2      u2_t_dlc;

    /* タイムスタンプ取得 */
    u4_t_time   = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    u4_t_time   = (U4)(u4_t_time / MCU_FRT_1MS);

    /* CANID取得,通知用IDに変換 */
    u4_t_canid  = u4_s_FLG_EXT;
    u4_t_canid  |= ((u4_ap_QSEV_RX[u1_s_POS_CANID] & u4_s_MSK_BASEID) << u1_s_SFT_BASEID);
    u4_t_canid  |= (u4_ap_QSEV_RX[u1_s_POS_CANID] & u4_s_MSK_EXTID);

    /* DLC取得 */
    u2_t_dlc    = (U2)(u4_ap_QSEV_RX[u1_s_POS_HEAD]  & u4_s_MSK_DL);

    vd_s_XspiIviCANGWStuckBuff(u4_t_time, u4_t_canid, (U1)u2_t_dlc, (const U1 *)&u4_ap_QSEV_RX[u1_s_POS_DATA]);
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
    static const U1 u1_s_FIXLEN_CMS = (U1)9U;       /* time(4byte) + CANID(4byte) + DLC(1byte) */
    static const U1 u1_s_MSK_ALIGN8 = (U1)0x07U;    /* Mask for 8-byte alignment */

    U1          u1_t_cms;
    U1          u1_t_jdg;
    U1          u1_tp_cms[XSPI_IVI_CMS_1];
    U1          u1_tp_can_data[XSPI_IVI_CAN_DATA_80];

    if(u1_s_flg_canstuck    == (U1)FALSE){
        u1_s_flg_canstuck   = (U1)TRUE;
        u1_t_jdg            = (U1)FALSE;

        if (u1_a_DLC <= (U1)XSPI_IVI_CAN_DLC_64) {
            /* CMS : time(4byte) + CANID(4byte) + DLC(1byte) + CANData([DLC]byte) + 8byte alignment */
            u1_t_cms = (u1_s_FIXLEN_CMS + u1_a_DLC + u1_s_MSK_ALIGN8) & ~(u1_s_MSK_ALIGN8);
            u1_t_jdg = u1_g_XspiIviQueueWriChk(u1_t_cms);
        }
        else {
            /* DLC値域外のため異常と判断し読み捨てとする */
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
            u1_tp_can_data[4] = (u4_a_MSG   & (U4)0xFF000000U) >>   24; /* 1バイトを抽出してシフト */
            u1_tp_can_data[5] = (u4_a_MSG   & (U4)0x00FF0000U) >>   16; /* 1バイトを抽出してシフト */
            u1_tp_can_data[6] = (u4_a_MSG   & (U4)0x0000FF00U) >>    8; /* 1バイトを抽出してシフト */
            u1_tp_can_data[7] = (u4_a_MSG   & (U4)0x000000FFU);         /* 1バイトを抽出 */
            /* DLC */
            u1_tp_can_data[8] = u1_a_DLC;
            /* CANData */
            vd_g_MemcpyU1(&u1_tp_can_data[9], &u1_ap_SRC[0], (U4)u1_a_DLC);

            /* キューへの格納 */
            u1_g_XspiIviQueueWriCms(u1_tp_cms);
            vd_g_XspiIviQueueWriCandata(u1_tp_can_data, (U2)u1_t_cms);
        }
        else {
            /* バッファに空きがないため受信した信号は保持せず読み捨てる */
            /* do nothing */
        }
        u1_s_flg_canstuck   = (U1)FALSE;
    }
    else{
        /* 別処理でCANキューへの格納中のため読み捨て */
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviCANBusGet2M(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    2M CANBusステータス更新処理                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviCANBusGet2M(void)
{
    static const U2 u2_s_NWORD  = (U2)1U;

    U1      u1_t_sts;
    U4      u4_t_data;

    u4_t_data   = (U4)0U;

    /* 2M-1 */
    u1_t_sts    = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_CANBUS_STS_2M1, &u4_t_data, u2_s_NWORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_sp_Xspi_Ivi_CanBusSts2M[0]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts2M[1]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts2M[2]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts2M[3]   = (U1)0x03U;    /* 初期化 : 通常動作状態 */

        if(u4_t_data    != (U4)XSPI_IVI_CANBUS_RSV_ACTIVE){
            u1_sp_Xspi_Ivi_CanBusSts2M[3]   = (U1)0x04U;        /* 通信不能状態 */

            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_REGSTUCK)    != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts2M[0]   = (U1)0x01U;    /* 通信不能状態要因 メッセージレジスタ固着 */
            }
            else{
                 /* do nothing */
            }
            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_BUSOFF)      != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts2M[1]   = (U1)0x01U;    /* 通信不能状態要因 バス OFF */
            }
            else{
                 /* do nothing */
            }
            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_NOCONNECT)   != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts2M[2]   = (U1)0x01U;    /* 通信不能状態要因 CANバス未接続（5sec間送信割未検出） */
            }
            else{
                 /* do nothing */
            }
        }
        else{
            /* do nothing */
        }
    }
    else{
        /* do nothing */
    }

    /* 2M-2 */
    /* T.B.D */
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviCANBusGet5M(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    5M CANBusステータス更新処理                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviCANBusGet5M(void)
{
    static const U2 u2_s_NWORD  = (U2)1U;

    U1      u1_t_sts;
    U4      u4_t_data;

    u4_t_data   = (U4)0U;

    /* 5M */
    u1_t_sts    = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_CANBUS_STS_5M, &u4_t_data, u2_s_NWORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        u1_sp_Xspi_Ivi_CanBusSts5M[0]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts5M[1]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts5M[2]   = (U1)0x00U;    /* 初期化 : 正常 */
        u1_sp_Xspi_Ivi_CanBusSts5M[3]   = (U1)0x03U;    /* 初期化 : 通常動作状態 */

        if(u4_t_data    != (U4)XSPI_IVI_CANBUS_RSV_ACTIVE){
            u1_sp_Xspi_Ivi_CanBusSts5M[3]   = (U1)0x04U;        /* 通信不能状態 */

            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_REGSTUCK)    != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts5M[0]   = (U1)0x01U;    /* 通信不能状態要因 メッセージレジスタ固着 */
            }
            else{
                 /* do nothing */
            }
            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_BUSOFF)      != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts5M[1]   = (U1)0x01U;    /* 通信不能状態要因 バス OFF */
            }
            else{
                 /* do nothing */
            }
            if((u4_t_data    & (U4)XSPI_IVI_CANBUS_RSV_NOCONNECT)   != (U4)0U){
                u1_sp_Xspi_Ivi_CanBusSts5M[2]   = (U1)0x01U;    /* 通信不能状態要因 CANバス未接続（5sec間送信割未検出） */
            }
            else{
                 /* do nothing */
            }
        }
        else{
            /* do nothing */
        }
    }
    else{
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviDrecSgnlGet(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MET送信信号取得処理(ドラレコ系信号)                                                                                 */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviDrecSgnlGet(void)
{
    U1      u1_t_sts;
    U4      u4_t_ivdsh_data[XSPI_IVI_IVDSH_DREC_NWORD];
    U1      u1_t_data[XSPI_IVI_CAN_DLC_08];
    U1      u1_t_datanm2_sgnl;
    U4      u4_t_lpcnt;
    U4      u4_t_time;

    u1_t_sts    = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_MET1D51, &u4_t_ivdsh_data[0], (U2)XSPI_IVI_IVDSH_DREC_NWORD);
    if(u1_t_sts != (U1)IVDSH_NO_REA){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_IVI_IVDSH_DREC_NWORD; u4_t_lpcnt++){
            u1_t_data[u4_t_lpcnt * 4]     = (U1)(u4_t_ivdsh_data[u4_t_lpcnt]  & (U4)0x000000FFU);
            u1_t_data[(u4_t_lpcnt * 4)+1] = (U1)((u4_t_ivdsh_data[u4_t_lpcnt] & (U4)0x0000FF00U) >> 8U);
            u1_t_data[(u4_t_lpcnt * 4)+2] = (U1)((u4_t_ivdsh_data[u4_t_lpcnt] & (U4)0x00FF0000U) >> 16U);
            u1_t_data[(u4_t_lpcnt * 4)+3] = (U1)((u4_t_ivdsh_data[u4_t_lpcnt] & (U4)0xFF000000U) >> 24U);
        }
        u1_t_datanm2_sgnl = u1_t_data[0] & (U1)XSPI_IVI_DATANM2_MASK;

        if(u1_t_datanm2_sgnl != u1_s_Xspi_Ivi_DataNm2_Sgnl_pre) {
            /* タイムスタンプ取得処理 */
            u4_t_time = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
            u4_t_time = (U4)(u4_t_time / MCU_FRT_1MS);
            vd_s_XspiIviCANGWStuckBuff(u4_t_time, (U4)XSPI_IVI_MET1D51_CANID, (U1)XSPI_IVI_MET1D51_DLC, &u1_t_data[0]);
        }
        u1_s_Xspi_Ivi_DataNm2_Sgnl_pre = u1_t_datanm2_sgnl;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviCANBusEventJdg(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANBusステータス イベント送信判定                                                                                  */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviCANBusEventJdg(void)
{
    U1      u1_t_jdg;
    U4      u4_t_loop;

    u1_t_jdg    = (U1)FALSE;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_IVI_CANBUS_POS_TOTAL; u4_t_loop++){
        /* 2M */
        if(u1_sp_Xspi_Ivi_CanBusSts2M[u4_t_loop] != u1_sp_Xspi_Ivi_CanBusSts2M_pre[u4_t_loop]){
            u1_t_jdg    = (U1)TRUE;
            vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_CanBusSts2M_pre[0], &u1_sp_Xspi_Ivi_CanBusSts2M[0], sizeof(u1_sp_Xspi_Ivi_CanBusSts2M_pre));
        }
        /* 5M */
        if(u1_sp_Xspi_Ivi_CanBusSts5M[u4_t_loop] != u1_sp_Xspi_Ivi_CanBusSts5M_pre[u4_t_loop]){
            u1_t_jdg    = (U1)TRUE;
            vd_g_MemcpyU1(&u1_sp_Xspi_Ivi_CanBusSts5M_pre[0], &u1_sp_Xspi_Ivi_CanBusSts5M[0], sizeof(u1_sp_Xspi_Ivi_CanBusSts5M_pre));
        }
    }

    if(u1_t_jdg == (U1)TRUE){
        /* CANBusステータスイベント送信 */
        vd_g_XspiIviCANBusSend();
    }
    else{
        /* do nothing */
    }
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
/*  static void            vd_s_XspiIviCANCommandStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    BUSステータスをバッファにスタックしていく処理                                                                        */
/*  Arguments:      u1_a_ID   : Command ID                                                                                           */
/*                  u2_a_SIZE : Command Data Length                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviCANCommandStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE)
{
    U1          u1_tp_cancomamand_data[XSPI_IVI_CAN_COMMNDDATA_SIZE];
    U1          u1_t_cancommand_data_size;
    U1          u1_t_jdg;

    u1_t_jdg = (U1)FALSE;
    vd_g_MemfillU1(&u1_tp_cancomamand_data[0], (U1)0U, (U4)XSPI_IVI_CAN_COMMNDDATA_SIZE);
    
    /* 8byteアライメント確保とキュー空き判定 */
    if((u2_a_SIZE > (U2)8U) && (u2_a_SIZE <= (U2)16U)) {
        u1_t_cancommand_data_size = (U1)XSPI_IVI_HEADER + (U1)16U;
        u1_t_jdg    = u1_g_XspiIviQueueWriChkCanCommand(u1_t_cancommand_data_size);
    } else if(u2_a_SIZE <= (U2)8U){
        u1_t_cancommand_data_size = (U1)XSPI_IVI_HEADER + (U1)8U;
        u1_t_jdg    = u1_g_XspiIviQueueWriChkCanCommand(u1_t_cancommand_data_size);
    } else {
        /* コマンドサイズ異常 */
        u1_t_jdg    = (U1)FALSE;
    }

    if(u1_t_jdg == (U1)TRUE)
    {
        /* キューに空き容量があるためデータ格納 */
        /* 各コマンドのヘッダー情報作成 */
        /* 識別値 */
        u1_tp_cancomamand_data[0] = (U1)0x43U;
        u1_tp_cancomamand_data[1] = (U1)0x4EU;
        u1_tp_cancomamand_data[2] = (U1)0x44U;
        u1_tp_cancomamand_data[3] = (U1)0x54U;
        /* データ長 */
        u1_tp_cancomamand_data[4] = (U1)0U;         /* データタイプがU1に収まるためByte4は0固定 */
        u1_tp_cancomamand_data[5] = (U1)u1_t_cancommand_data_size - (U1)XSPI_IVI_HEADER;
        /* データサイズ */
        u1_tp_cancomamand_data[6] = (U1)u1_a_ID;
        u1_tp_cancomamand_data[7] = (U1)0U;

        /* Byte1 SubType */
        u1_tp_cancomamand_data[8] = (U1)u1_a_ID;

        switch (u1_a_ID)
        {
        case XSPI_IVI_CANCOMMAND_SEND:
            /* 200.102_04h：CANバスステータス通知 */
            /* Byte2-5 CANBusStatus 2M */
            vd_g_MemcpyU1(&u1_tp_cancomamand_data[9], &u1_sp_Xspi_Ivi_CanBusSts2M[0], (U4)XSPI_IVI_CANBUS_POS_TOTAL);
            /* Byte6-9 CANBusStatus 5M */
            vd_g_MemcpyU1(&u1_tp_cancomamand_data[13], &u1_sp_Xspi_Ivi_CanBusSts5M[0], (U4)XSPI_IVI_CANBUS_POS_TOTAL);
            break;
        
        default:
            /* do nothing */
            break;
        }

        /* CANコマンドデータをキューに格納 */
        vd_g_XspiIviQueueWriCanCommandData(u1_tp_cancomamand_data,(U2)u1_t_cancommand_data_size);
        /* CANコマンドデータサイズをキューに格納 */
        u1_g_XspiIviQueueWriCanCommandSize(&u1_t_cancommand_data_size);
    }
    else{
        /* ID不正orキューに空き容量がないため読み飛ばし */
        /* do nothing */
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub4ClockUTCPut(const U1* u1_ap_DATA)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    UTC時刻情報取得                                                                                                   */
/*  Arguments:      u1_ap_DATA : UTC時刻情報                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviClockUTCPut(const U1* u1_ap_DATA)
{
    U2 u2_t_year_hi;
    U2 u2_t_year_lo;
    U1 u1_t_week;
    U2 u2_t_year;

    /*BCDデータで格納*/
    /*second*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_0] = (u1_ap_DATA[XSPI_IVI_CAN_BUF_5] % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_0] |= ((u1_ap_DATA[XSPI_IVI_CAN_BUF_5] / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*minute*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_1] = (u1_ap_DATA[XSPI_IVI_CAN_BUF_4] % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_1] |= ((u1_ap_DATA[XSPI_IVI_CAN_BUF_4] / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*hour*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_2] = (u1_ap_DATA[XSPI_IVI_CAN_BUF_3] % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_2] |= ((u1_ap_DATA[XSPI_IVI_CAN_BUF_3] / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*day*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_3] = (u1_ap_DATA[XSPI_IVI_CAN_BUF_2] % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_3] |= ((u1_ap_DATA[XSPI_IVI_CAN_BUF_2] / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*month*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_4] = (u1_ap_DATA[XSPI_IVI_CAN_BUF_1] % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_4] |= ((u1_ap_DATA[XSPI_IVI_CAN_BUF_1] / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*year*/
    u2_t_year = (U2)(u1_ap_DATA[XSPI_IVI_CAN_BUF_0] + (U1)XSPI_IVI_YEAR_OFFSET);
    u2_t_year_hi = u2_t_year / (U2)XSPI_IVI_BCD_HUNDREDS;
    u2_t_year_lo = u2_t_year % (U2)XSPI_IVI_BCD_HUNDREDS;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_5] =  (U1)((u2_t_year_hi % (U2)XSPI_IVI_BCD_TENS) & (U2)XSPI_IVI_LOWER_NIBBLE_MASK);
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_5] |= (U1)(((u2_t_year_hi / (U2)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U2)XSPI_IVI_UPPER_NIBBLE_MASK);
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_6] =  (U1)((u2_t_year_lo % (U2)XSPI_IVI_BCD_TENS) & (U2)XSPI_IVI_LOWER_NIBBLE_MASK);
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_6] |= (U1)(((u2_t_year_lo / (U2)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U2)XSPI_IVI_UPPER_NIBBLE_MASK);
    /*week*/
    u1_t_week = u1_ap_DATA[XSPI_IVI_CAN_BUF_6];
    if(u1_t_week == (U1)XSPI_IVI_WEEK_SUNDAY_RTC) {
        u1_t_week = (U1)XSPI_IVI_WEEK_SUNDAY_UTC;
    }
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_7] = (u1_t_week % (U1)XSPI_IVI_BCD_TENS) & (U1)XSPI_IVI_LOWER_NIBBLE_MASK;
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_7] |= ((u1_t_week / (U1)XSPI_IVI_BCD_TENS) << XSPI_IVI_SFT_04) & (U1)XSPI_IVI_UPPER_NIBBLE_MASK;
    /*sts*/
    u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_8] = u1_ap_DATA[XSPI_IVI_CAN_BUF_7];

    if(u1_sp_Xspi_Ivi_ClockUtcdata[XSPI_IVI_CAN_BUF_8] == (U1)XSPI_IVI_UTC_STATUS_VARID) {
        u1_s_Xspi_Ivi_ClockUtc_recflg = (U1)TRUE;
    } else {
        u1_s_Xspi_Ivi_ClockUtc_recflg = (U1)FALSE;
    }
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviClockUTCDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    時刻情報のイベント判定                                                                                             */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviClockUTCDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_SIZE)
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
/*  void         vd_s_XspiIviClockUTCStuckBuff(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    UTC時計情報をバッファにスタックしていく処理                                                                          */
/*  Arguments:      u2_a_TYPE : Command Data Type                                                                                    */
/*                  u2_a_SIZE : Command Data Length                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviClockUTCStuckBuff(const U1 u1_a_ID,const U2 u2_a_SIZE)
{
    U1          u1_tp_utc_data[XSPI_IVI_CAN_COMMNDDATA_SIZE];
    U1          u1_t_utc_data_size;
    U1          u1_t_jdg;
    U4          u4_t_time;

    u1_t_jdg = (U1)FALSE;
    vd_g_MemfillU1(&u1_tp_utc_data[0], (U1)0U, (U4)XSPI_IVI_CAN_COMMNDDATA_SIZE);

    /*8byteアライメント*/
    if((u2_a_SIZE > (U2)8U) && (u2_a_SIZE <= (U2)16U)) {
        u1_t_utc_data_size = (U1)XSPI_IVI_HEADER + (U1)16U;
        u1_t_jdg = u1_g_XspiIviQueueWriChkCanCommand(u1_t_utc_data_size);
    } else if(u2_a_SIZE <= (U2)8U){
        u1_t_utc_data_size = (U1)XSPI_IVI_HEADER + (U1)8U;
        u1_t_jdg = u1_g_XspiIviQueueWriChkCanCommand(u1_t_utc_data_size);
    } else {
        u1_t_jdg = (U1)FALSE;
    }

    if(u1_t_jdg == (U1)TRUE)
    {
        /*FRT*/
        u4_t_time = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
        u4_t_time = (U4)(u4_t_time / MCU_FRT_1MS);

        /*キューに空き容量があるためデータ格納*/
        /*識別値*/
        u1_tp_utc_data[0] = (U1)0x43U;
        u1_tp_utc_data[1] = (U1)0x4EU;
        u1_tp_utc_data[2] = (U1)0x44U;
        u1_tp_utc_data[3] = (U1)0x54U;
        /*データ長*/
        u1_tp_utc_data[4] = (U1)((u2_a_SIZE >> XSPI_IVI_SFT_08) & (U2)0x00FFU);
        u1_tp_utc_data[5] = (U1)(u2_a_SIZE & (U2)0x00FFU);
        /*データサイズ*/
        u1_tp_utc_data[6] = (U1)u1_a_ID;
        u1_tp_utc_data[7] = (U1)0U;
        u1_tp_utc_data[8] = (U1)u1_a_ID;

        /*tickTime*/
        u1_tp_utc_data[9] = (U1)((u4_t_time >> XSPI_IVI_SFT_24) & (U4)0x000000FFU);
        u1_tp_utc_data[10] = (U1)((u4_t_time >> XSPI_IVI_SFT_16) & (U4)0x000000FFU);
        u1_tp_utc_data[11] = (U1)((u4_t_time >> XSPI_IVI_SFT_08) & (U4)0x000000FFU);
        u1_tp_utc_data[12] = (U1)(u4_t_time & (U4)0x000000FFU);
        /*UTC data*/
        vd_g_MemcpyU1(&u1_tp_utc_data[13], &u1_sp_Xspi_Ivi_ClockUtcdata[0], (U4)XSPI_IVI_CLOCKUTC_DATA_SIZE);

        /*CANコマンドデータをキューに格納*/
        vd_g_XspiIviQueueWriCanCommandData(u1_tp_utc_data,(U2)u1_t_utc_data_size);
        /*CANコマンドデータサイズをキューに格納*/
        u1_g_XspiIviQueueWriCanCommandSize(&u1_t_utc_data_size);
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
/*  1.0.0    11/11/2024  TN       New.                                                                                               */
/*  1.0.1    01/30/2025  TN       Updated to follow BSW macro changes.                                                               */
/*  1.1.0    05/12/2025  TN       Updated for communication specification v6.50.                                                     */
/*  1.2.0    05/26/2025  TN       Added support for UTC clock information command.                                                   */
/*  1.3.0    05/26/2025  TaN      Added processing to set CD_SIZE signal value.                                                      */
/*  1.4.0    06/30/2025  TN       Updated for communication specification v7.30.                                                     */
/*  1.5.0    07/07/2025  TaN      Added support for Partial Network Management (PartialNM).                                          */
/*  1.6.0    07/07/2025  TN       Added CAN bus status processing.                                                                   */
/*  1.7.0    07/14/2025  TaN      Added CAN transmission processing for FLYNOP signal notified via inter-VM communication.           */
/*  1.7.1    07/21/2025  TN       Fixed CAN bus notification.                                                                        */
/*  1.8.0    07/21/2025  TN       Added GW processing for signals excluded in Comm. Spec. V7.30.                                     */
/*  1.9.0    08/19/2025  TN       Added gateway for QSEv.                                                                            */
/*  1.10.0   10/06/2025  TN       Update Gateway Process: BEVstep3-Cockpit_CanVmRouting_v7.30.xlsx Revision 12104                    */
/*  1.11.0   02/02/2025  KT       Fixed Gateway Process: BEVstep3-Cockpit_CanVmRouting_v7.30.xlsx BEVS3CDC-26407                     */
/*  1.12.0   03/17/2025  KT       Update Gateway Process: BEVstep3-Cockpit_CanVmRouting_v26.02.13.0                                  */
/*  1.12.1   03/31/2025  TN       Prevented underflow when a CANID smaller than the table minimum is specified.                      */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * TN   = Tetsu Naruse, Denso Techno                                                                                              */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * TaN  = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
