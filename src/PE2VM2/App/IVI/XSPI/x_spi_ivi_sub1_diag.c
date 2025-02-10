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

#define    XSPI_IVI_DIAG_SIZE               (248U)
#define    XSPI_IVI_DIAG_LOG_SIZE           (5U)
#define    XSPI_IVI_DIAG_LOGDATA_SIZE       (243U)
#define    XSPI_IVI_DIAG_READ_REQ_START     (0U)
#define    XSPI_IVI_DIAG_READ_REQ_CANCEL    (1U)
#define    XSPI_IVI_DIAG_READ_RECNOTIF_VALI (0U)
#define    XSPI_IVI_DIAG_READ_RECNOTIF_FAIL (0xFFU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4              u4_s_xspi_ivi_diagdatasize;     /*ダイレコログサイズ格納用*/
static U2              u2_s_xspi_ivi_diagdatanum;      /*ダイレコログ分割数*/
static U1              u1_sp_xspi_ivi_diagdata[1000];   /*暫定で1000byte分のダイレコログデータ格納できるように準備*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1_DiagSizeReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_DiagSizeRespons(void);
static void            vd_s_XspiIviSub1_DiagLogReadReq(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
static void            vd_s_XspiIviSub1_DiagLogRecieveNotify(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_DATA_SIZE);
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
    vd_g_MemfillU1(&u1_sp_xspi_ivi_diagdata[0], (U1)0U, (U4)1000U); /*暫定サイズ*/
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

    /*ダイレコログサイズを取得*/
    /*サイズ取得のタイミングでダイレコログデータも取得*/
    /*シス検は0固定のためskip*/

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
