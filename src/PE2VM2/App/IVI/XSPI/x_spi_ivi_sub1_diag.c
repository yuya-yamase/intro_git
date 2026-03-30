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
#define XSPI_IVI_SUB1_DIAG_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_DIAG_C_MINOR                   (0)
#define XSPI_IVI_SUB1_DIAG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_diag.h"
#include    "SysEcDrc.h"
#include    "PictCtl.h"
#include    "DtcCtl.h"
#include    "RobCtl.h"
#include    "WhlIni.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_DIAG_C_MAJOR != XSPI_IVI_SUB1_DIAG_H_MAJOR) || \
     (XSPI_IVI_SUB1_DIAG_C_MINOR != XSPI_IVI_SUB1_DIAG_H_MINOR) || \
     (XSPI_IVI_SUB1_DIAG_C_PATCH != XSPI_IVI_SUB1_DIAG_H_PATCH))
#error "x_spi_ivi_sub1_diag.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_DIAG_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_DIAG_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_DIAG_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_diag.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_DIAG_ID                 (0x23U)
#define    XSPI_IVI_DIAG_SIZE_RQST          (0x10U)
#define    XSPI_IVI_DIAG_SIZE_RES           (0x11U)
#define    XSPI_IVI_DIAG_DATA_RQST          (0x12U)
#define    XSPI_IVI_DIAG_DATA_RES           (0x13U)
#define    XSPI_IVI_DIAG_REC_NOTIFY         (0x14U)
#define    XSPI_IVI_DIAG_MODE               (0x30U)
#define    XSPI_IVI_DIAG_WHLINI_RQST        (0x31U)
#define    XSPI_IVI_DIAG_WHLINI_RES         (0x32U)
#define    XSPI_IVI_DIAG_PINFOINI_START_RES (0x33U)
#define    XSPI_IVI_DIAG_PINFOINI_FIN_RES   (0x34U)
#define    XSPI_IVI_DIAG_PINFOINI_RQST      (0x36U)
#define    XSPI_IVI_DIAG_DTCREC_SEND        (0x41U)
#define    XSPI_IVI_DIAG_DTCREC_RECV        (0x42U)
#define    XSPI_IVI_DIAG_ROBREC_SEND        (0x43U)
#define    XSPI_IVI_DIAG_ROBREC_RECV        (0x44U)

#define    XSPI_IVI_DIAG_SIZE               (248U)
#define    XSPI_IVI_DIAG_LOG_SIZE           (5U)
#define    XSPI_IVI_DIAG_LOGDATA_SIZE       (243U)
#define    XSPI_IVI_DIAG_READ_REQ_START     (0U)
#define    XSPI_IVI_DIAG_READ_REQ_CANCEL    (1U)
#define    XSPI_IVI_DIAG_READ_RECNOTIF_VALI (0U)
#define    XSPI_IVI_DIAG_READ_RECNOTIF_FAIL (0xFFU)

#define    XSPI_IVI_DIAG_DTCREC_SEND_SIZE   (4U)
#define    XSPI_IVI_DIAG_ROBREC_SEND_SIZE   (3U)
#define    XSPI_IVI_DIAG_WHLINI_RES_SIZE    (3U)
#define    XSPI_IVI_PINFOINI_START_SIZE     (2U)
#define    XSPI_IVI_PINFOINI_FIN_SIZE       (3U)
#define    XSPI_IVI_DIAG_LOGDATA_MAXSIZE    (1080U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4              u4_s_xspi_ivi_diagdatasize;     /*ダイレコログサイズ格納用*/
static U2              u2_s_xspi_ivi_diagdatanum;      /*ダイレコログ分割数*/
static U1              u1_sp_xspi_ivi_diagdata[XSPI_IVI_DIAG_LOGDATA_MAXSIZE];
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1_DiagSizeReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_DiagSizeRespons(void);
static void            vd_s_XspiIviSub1_DiagLogReadReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_DiagLogRecieveNotify(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_DiagPinfoIniReq(void);
static void            vd_s_XspiIviSub1_DiagPinfoIniStartRespons(void);
static void            vd_s_XspiIviSub1_DiagPinfoIniFinRespons(void);
static void            vd_s_XspiIviSub1_DiagLogDataRespons(U2 u2_a_OFFSET_DATA);
static void            vd_s_XspiIviSub1_DiagDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DiagInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DiagInit(void)
{
    u4_s_xspi_ivi_diagdatasize = (U4)0U;
    u2_s_xspi_ivi_diagdatanum = (U2)0U;
    vd_g_MemfillU1(&u1_sp_xspi_ivi_diagdata[0], (U1)0U, (U4)XSPI_IVI_DIAG_LOGDATA_MAXSIZE); /*暫定サイズ*/
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DiagMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DiagMainTask(void)
{
    /*定期送信などのデータ作成をここで行う*/
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1DiagAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1DiagAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_DIAG_SIZE_RQST:
        vd_s_XspiIviSub1_DiagSizeReq(u1_ap_XSPI_ADD,u2_a_DATA_SIZE);
        break;
    case XSPI_IVI_DIAG_DATA_RQST:
        vd_s_XspiIviSub1_DiagLogReadReq(u1_ap_XSPI_ADD,u2_a_DATA_SIZE);
        break;
    case XSPI_IVI_DIAG_REC_NOTIFY:
        vd_s_XspiIviSub1_DiagLogRecieveNotify(u1_ap_XSPI_ADD,u2_a_DATA_SIZE);
        break;
    case XSPI_IVI_DIAG_MODE:
        vd_g_PictCtl_RcvDiagModInd(u1_ap_XSPI_ADD[1]);
        break;
    case XSPI_IVI_DIAG_WHLINI_RQST:
        vd_g_WhlIni_SoCReq(u1_ap_XSPI_ADD[1]);
        break;
    case XSPI_IVI_DIAG_PINFOINI_RQST:
        vd_s_XspiIviSub1_DiagPinfoIniReq();
        break;
    case XSPI_IVI_DIAG_DTCREC_RECV:
        vd_g_DtcCtl_RecDtc(u1_ap_XSPI_ADD[1],u1_ap_XSPI_ADD[2],u1_ap_XSPI_ADD[3]);
        break;
    case XSPI_IVI_DIAG_ROBREC_RECV:
        vd_g_RobCtl_RecRob(u1_ap_XSPI_ADD[1],u1_ap_XSPI_ADD[2]);
        break;
    
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagSizeReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagSizeReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    vd_s_XspiIviSub1_DiagSizeRespons();
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagSizeRespons(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagSizeRespons(void)
{
    U1     u1_s_LOGSIZE = (U1)XSPI_IVI_DIAG_LOG_SIZE;
    U1     u1_tp_data[XSPI_IVI_DIAG_LOG_SIZE];

    /* ダイレコログサイズを取得 */
    vd_g_SysEcDrc_SendDateSet(&u4_s_xspi_ivi_diagdatasize, &u1_sp_xspi_ivi_diagdata[0], (U4)XSPI_IVI_DIAG_LOGDATA_MAXSIZE);

    u2_s_xspi_ivi_diagdatanum = (U2)((u4_s_xspi_ivi_diagdatasize + (U4)242U) / (U4)XSPI_IVI_DIAG_LOGDATA_SIZE);

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_SIZE_RES;
    u1_tp_data[1] = (U1)((u4_s_xspi_ivi_diagdatasize & 0xFF000000U) >> XSPI_IVI_SFT_24);
    u1_tp_data[2] = (U1)((u4_s_xspi_ivi_diagdatasize & 0x00FF0000U) >> XSPI_IVI_SFT_16);
    u1_tp_data[3] = (U1)((u4_s_xspi_ivi_diagdatasize & 0x0000FF00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[4] = (U1)(u4_s_xspi_ivi_diagdatasize & 0x000000FFU);

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_LOGSIZE);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagLogReadReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagLogReadReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1   u1_t_type;
    U2   u2_t_offset;

    u1_t_type = u1_ap_XSPI_ADD[1];
    u2_t_offset = (U2)0U;
    switch (u1_t_type)
    {
    case XSPI_IVI_DIAG_READ_REQ_START:
        /* データ通知開始 */
        if(u2_s_xspi_ivi_diagdatanum != (U2)0U) {
            u2_t_offset = (U2)1U;
        }
        vd_s_XspiIviSub1_DiagLogDataRespons(u2_t_offset);
        break;
    case XSPI_IVI_DIAG_READ_REQ_CANCEL:
        /* データ通知終了 */
        u4_s_xspi_ivi_diagdatasize = (U4)0U;
        u2_s_xspi_ivi_diagdatanum = (U2)0U;
        vd_s_XspiIviSub1_DiagLogDataRespons(u2_t_offset);
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagLogRecieveNotify(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagLogRecieveNotify(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE)
{
    U1   u1_t_type;
    U2   u2_t_offset;

    u1_t_type = u1_ap_XSPI_ADD[1];
    u2_t_offset = (U2)((u1_ap_XSPI_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[3]);
    switch (u1_t_type)
    {
    case XSPI_IVI_DIAG_READ_RECNOTIF_VALI:
        /* 次データ送信 */
        if(u2_t_offset < u2_s_xspi_ivi_diagdatanum) {
            u2_t_offset = u2_t_offset + (U2)1U;
            vd_s_XspiIviSub1_DiagLogDataRespons(u2_t_offset);
        }
        break;
    case XSPI_IVI_DIAG_READ_RECNOTIF_FAIL:
        /* データ再送信 */
        vd_s_XspiIviSub1_DiagLogDataRespons(u2_t_offset);
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagLogDataRespons(U2 u2_a_OFFSET_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagLogDataRespons(U2 u2_a_OFFSET_DATA)
{
    U1     u1_tp_data[XSPI_IVI_DIAG_SIZE];
    U4     u4_t_data_buf;   /*データ読み出し開始位置*/
    U1     u1_t_data_size;

    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)XSPI_IVI_DIAG_SIZE);

    if(u2_a_OFFSET_DATA >= (U2)2U){
        u4_t_data_buf = (U4)((u2_a_OFFSET_DATA - (U2)1U) * (U2)XSPI_IVI_DIAG_LOGDATA_SIZE);
    } else {
        u4_t_data_buf = (U4)0U;
    }

    if(u2_s_xspi_ivi_diagdatanum == u2_a_OFFSET_DATA) {
        u1_t_data_size = (U1)(u4_s_xspi_ivi_diagdatasize % (U4)XSPI_IVI_DIAG_LOGDATA_SIZE);
    } else {
        u1_t_data_size = (U1)XSPI_IVI_DIAG_LOGDATA_SIZE;
    }

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_DATA_RES;
    u1_tp_data[1] = (U1)((u2_s_xspi_ivi_diagdatanum & 0xFF00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[2] = (U1)(u2_s_xspi_ivi_diagdatanum & 0x00FFU);
    u1_tp_data[3] = (U1)((u2_a_OFFSET_DATA & 0xFF00U) >> XSPI_IVI_SFT_08);
    u1_tp_data[4] = (U1)(u2_a_OFFSET_DATA & 0x00FFU);

    vd_g_MemcpyU1(&u1_tp_data[5], &u1_sp_xspi_ivi_diagdata[u4_t_data_buf], (U4)u1_t_data_size);

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],(U1)XSPI_IVI_DIAG_SIZE);
}
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_DiagWhliniRespons(const U1 u1_a_KIND, const U1 u1_a_RESULT)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_KIND       :  種別                                                                                          */
/*                  u1_a_RESULT     :  結果                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1_DiagWhliniRespons(const U1 u1_a_KIND, const U1 u1_a_RESULT)
{
    U1     u1_s_DTCSIZE = (U1)XSPI_IVI_DIAG_WHLINI_RES_SIZE;
    U1     u1_tp_data[XSPI_IVI_DIAG_WHLINI_RES_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_WHLINI_RES;
    u1_tp_data[1] = u1_a_KIND;
    u1_tp_data[2] = u1_a_RESULT;

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_DTCSIZE);
}
/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagPinfoIniReq(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagPinfoIniReq(void)
{
    vd_s_XspiIviSub1_DiagPinfoIniStartRespons();
    vd_s_XspiIviSub1_DiagPinfoIniFinRespons();
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagPinfoIniStartRespons(void)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagPinfoIniStartRespons(void)
{
    U1     u1_s_PISSIZE = (U1)XSPI_IVI_PINFOINI_START_SIZE;
    U1     u1_tp_data[XSPI_IVI_PINFOINI_START_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_PINFOINI_START_RES;
    u1_tp_data[1] = (U1)0x00;                             /* 0x00 MCU */

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_PISSIZE);
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1_DiagPinfoIniFinRespons(void)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagPinfoIniFinRespons(void)
{
    U1     u1_s_PIFSIZE = (U1)XSPI_IVI_PINFOINI_FIN_SIZE;
    U1     u1_tp_data[XSPI_IVI_PINFOINI_FIN_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_PINFOINI_FIN_RES;
    u1_tp_data[1] = (U1)0x00;                             /* 0x00 MCU */
    u1_tp_data[2] = (U1)0x00;                             /* 0x00 初期化成功(初期化対象が無いため) */

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_PIFSIZE);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_DiagDtcrecSend(const U1 u1_a_CODE, const U1 u1_a_DIAGCODE, const U1 u1_a_STS)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_CODE       :  区分コード                                                                                     */
/*                  u1_a_DIAGCODE   :  開発ダイアグコード                                                                              */
/*                  u1_a_STS        :  ステータス                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1_DiagDtcrecSend(const U1 u1_a_CODE, const U1 u1_a_DIAGCODE, const U1 u1_a_STS)
{
    U1     u1_s_DTCSIZE = (U1)XSPI_IVI_DIAG_DTCREC_SEND_SIZE;
    U1     u1_tp_data[XSPI_IVI_DIAG_DTCREC_SEND_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_DTCREC_SEND;
    u1_tp_data[1] = u1_a_CODE;
    u1_tp_data[2] = u1_a_DIAGCODE;
    u1_tp_data[3] = u1_a_STS;

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_DTCSIZE);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1_DiagRobrecSend(const U1 u1_a_CODE, const U1 u1_a_DIAGCODE)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_a_CODE       :  区分コード                                                                                     */
/*                  u1_a_DIAGCODE   :  開発ダイアグコード                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1_DiagRobrecSend(const U1 u1_a_CODE, const U1 u1_a_DIAGCODE)
{
    U1     u1_s_ROBSIZE = (U1)XSPI_IVI_DIAG_ROBREC_SEND_SIZE;
    U1     u1_tp_data[XSPI_IVI_DIAG_ROBREC_SEND_SIZE];

    u1_tp_data[0] = (U1)XSPI_IVI_DIAG_ROBREC_SEND;
    u1_tp_data[1] = u1_a_CODE;
    u1_tp_data[2] = u1_a_DIAGCODE;

    vd_s_XspiIviSub1_DiagDataToQueue(&u1_tp_data[0],u1_s_ROBSIZE);
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub1_DiagDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1_DiagDataToQueue(const U1* u1_ap_XSPI_ADD, const U1 u1_a_SIZE)
{
    U1     u1_tp_data[XSPI_IVI_DIAG_SIZE];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_DIAG_ID;
    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)XSPI_IVI_DIAG_SIZE);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u1_a_SIZE);

    /*キューの関数呼び出し*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,(U2)u1_a_SIZE,u1_tp_data);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    02/10/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
