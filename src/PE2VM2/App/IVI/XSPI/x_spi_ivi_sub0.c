/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Transmission and reception processing of subframe 0 in XSPI communication.                                                       */
/*  Handled data: DiagCAN Data                                                                                                       */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SUB0_C_MAJOR                   (0)
#define XSPI_IVI_SUB0_C_MINOR                   (0)
#define XSPI_IVI_SUB0_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub0_private.h"
#include    "x_spi_ivi_sub0_SID14.h"
#include    "x_spi_ivi_sub0_SID19.h"
#include    "x_spi_ivi_sub0_SID22.h"
#include    "x_spi_ivi_sub0_SID2E.h"
#include    "x_spi_ivi_sub0_SID31.h"
#include    "x_spi_ivi_sub1_power.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB0_C_MAJOR != XSPI_IVI_SUB0_H_MAJOR) || \
     (XSPI_IVI_SUB0_C_MINOR != XSPI_IVI_SUB0_H_MINOR) || \
     (XSPI_IVI_SUB0_C_PATCH != XSPI_IVI_SUB0_H_PATCH))
#error "x_spi_ivi_sub0.c and x_spi_ivi_sub0.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB0_C_MAJOR != XSPI_IVI_SUB0_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB0_C_MINOR != XSPI_IVI_SUB0_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB0_C_PATCH != XSPI_IVI_SUB0_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub0.c and x_spi_ivi_sub0_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_DIAG_SIZE              (264U)
#define XSPI_IVI_DIAG_OSCOM_DATA_SIZE   (256U)

#define XSPI_IVI_DIAG_TX_MCU_TO_SOC     (1U)
#define XSPI_IVI_DIAG_TX_SOC_TO_MCU     (2U)

#define XSPI_IVI_DIAG_RES_COMP          (0U)
#define XSPI_IVI_DIAG_RES_WAIT          (1U)

#define XSPI_IVI_DIAG_RES_NODEL         (0U)
#define XSPI_IVI_DIAG_RES_DELETE        (1U)
#define XSPI_IVI_DIAG_RES_DELETE_RDY    (2U)

#define XSPI_IVI_DIAG_TOUT              (30000U / XSPI_IVI_TASK_TIME)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                          u2_data_len;
    U1                          u1_canid;
    U2                          u2_frame_cnt;
    U2                          u2_frame_num;
    U1                          u1_sid;
    U1                          u1_data[XSPI_IVI_DIAG_MAX_SIZE];
}ST_XSPI_IVI_DIAGCAN_DATA;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1          u1_sp_XspiIviSub0DiagResponse_buf[XSPI_IVI_DIAG_MAX_SIZE];      /*応答用のRAM*/
static  U2          u2_s_XspiIviSub0DiagResSize;                                    /*応答用のデータサイズRAM*/
static  ST_XSPI_IVI_DIAGCAN_DATA    st_s_XspiIviSub0DiagCanData;                    /*送信データ*/

static  U1          u1_s_XspiIviSub0OsComBridgeChk;
static  U1          u1_s_XspiIviSub0SendFlg;
static  U1          u1_s_XspiIviSub0ResponseFlg;
static  U1          u1_s_XspiIviSub0ResponseDeleteFlg;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void         vd_s_XspiIviSub0DataInit(void);
static void         vd_s_XspiIviSub0ResetInit(void);
static void         vd_s_XspiIviSub0SoCResetNrcResponse(void);
static void         vd_s_XspiIviSub0DiagCANAna(const U1 * u1_ap_SUB1_ADD, const U2 u2_a_DTLEN);
static void         vd_s_XspiIviSub0SendDiagCANData(U2 * u2_ap_datalen, U1 *u1_ap_canid, U1 * u1_ap_xspi_add);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0Init(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0Init(void)
{
    u2_s_XspiIviSub0DiagResSize = (U2)0U;
    u1_s_XspiIviSub0OsComBridgeChk = (U1)FALSE;
    u1_s_XspiIviSub0SendFlg = (U1)FALSE;
    u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_COMP;
    u1_s_XspiIviSub0ResponseDeleteFlg = (U1)XSPI_IVI_DIAG_RES_NODEL;

    vd_g_MemfillU1(&u1_sp_XspiIviSub0DiagResponse_buf[0], (U1)0U, (U4)XSPI_IVI_DIAG_MAX_SIZE);

    vd_s_XspiIviSub0DataInit();
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0DataInit(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0DataInit(void)
{
    vd_g_MemfillU1(&st_s_XspiIviSub0DiagCanData.u1_data[0], (U1)0U, (U4)XSPI_IVI_DIAG_MAX_SIZE);
    
    st_s_XspiIviSub0DiagCanData.u2_frame_num = (U2)0U;
    st_s_XspiIviSub0DiagCanData.u2_frame_cnt = (U2)0U;
    st_s_XspiIviSub0DiagCanData.u2_data_len = (U2)0U;
    st_s_XspiIviSub0DiagCanData.u1_canid = (U2)DIAGAPP_REQUESTID_UNKNOWN;
    st_s_XspiIviSub0DiagCanData.u1_sid = (U1)0U;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0VMResetInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0VMResetInit(void)
{
    vd_s_XspiIviSub0ResetInit();
    vd_g_XspiIviSub1PowerVMResetComp((U1)XSPI_IVI_POWER_RESET_COMP_DIAGCAN);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0SoCResetInit(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0SoCResetInit(void)
{
    vd_s_XspiIviSub0ResetInit();
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0CDCResetInit(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0CDCResetInit(void)
{
    vd_s_XspiIviSub0SoCResetNrcResponse();
    vd_g_XspiIviSub1PowerCDCResetComp((U1)XSPI_IVI_POWER_RESET_COMP_DIAGCAN);
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0ResetInit(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub0ResetInit(void)
{
    vd_s_XspiIviSub0SoCResetNrcResponse();
    vd_g_XspiIviQueueSoCResetInit();
    vd_g_DiagAppSID10SoCResetInit();

    u2_s_XspiIviSub0DiagResSize = (U2)0U;
    u1_s_XspiIviSub0OsComBridgeChk = (U1)FALSE;
    u1_s_XspiIviSub0SendFlg = (U1)FALSE;
    u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_COMP;
    u1_s_XspiIviSub0ResponseDeleteFlg = (U1)XSPI_IVI_DIAG_RES_NODEL;
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0SoCResetNrcResponse(void)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SoCリセット時の否定応答処理                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0SoCResetNrcResponse(void)
{
    U1  u1_t_result;
    U1  u1_t_sid;
    U1  u1_t_sid_tmp;
    U1  u1_t_response_flg;

    u1_t_result = (U1)TRUE;
    u1_t_sid = (U1)0U;
    u1_t_response_flg = (U1)FALSE;
    if(u1_s_XspiIviSub0ResponseFlg == (U1)XSPI_IVI_DIAG_RES_WAIT) {
        u1_t_sid = st_s_XspiIviSub0DiagCanData.u1_sid;
        u1_t_response_flg = (U1)TRUE;
    }

    while(u1_t_result == (U1)TRUE) {
        u1_t_result = u1_g_XspiIviQueueGetDiagCANDataSID(&u1_t_sid_tmp);
        if((u1_t_sid_tmp == (U1)XSPI_IVI_SID14) ||
           (u1_t_sid_tmp == (U1)XSPI_IVI_SID19) ||
           (u1_t_sid_tmp == (U1)XSPI_IVI_SID22) ||
           (u1_t_sid_tmp == (U1)XSPI_IVI_SID2E) ||
           (u1_t_sid_tmp == (U1)XSPI_IVI_SID31)) {
            u1_t_sid = u1_t_sid_tmp;
            u1_t_response_flg = (U1)TRUE;
        }
    }

    if(u1_t_response_flg == (U1)TRUE) {
        switch(u1_t_sid) {
            case XSPI_IVI_SID14:
            case XSPI_IVI_SID22:
            case XSPI_IVI_SID2E:
            case XSPI_IVI_SID31:
                vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_22);
                break;
            case XSPI_IVI_SID19:
                vd_g_DiagAppAnsTxNRC((U1)OXDC_SAL_PROC_NR_31);
                break;
            default:
                break;
        }
    }

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0Ana(const U1 * u1_ap_XSPI_ADD)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN) Data Analysis                                                                                 */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame0 Start Buffer                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void                vd_g_XspiIviSub0Ana(const U1 * u1_ap_XSPI_ADD)
{
    U2          u2_t_frame_counter;     /* Sub Frame Counter */
    U2          u2_t_frame_num;         /* Sub Frame num */
    U2          u2_t_dt_len;            /* data length */
    /*U1          u1_t_dt_type;*/           /* Transmit or Recieve */

    U2          u2_t_buf_pos;           /* data set buffer position*/

    u2_t_frame_counter  = (U2)((u1_ap_XSPI_ADD[0] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[1]);
    u2_t_frame_num      = (U2)((u1_ap_XSPI_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[3]);
    u2_t_dt_len         = (U2)((u1_ap_XSPI_ADD[4] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[5]);
    /*u1_t_dt_type        = u1_ap_XSPI_ADD[6];*/

    u2_t_buf_pos = (u2_t_frame_counter - (U2)1U) * (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE;

    if(u2_t_frame_num != (U2)0U) {
        if(u2_t_frame_counter == u2_t_frame_num) {
            /*応答用のデータサイズRAMにデータサイズ＋する*/
            vd_g_MemcpyU1(&u1_sp_XspiIviSub0DiagResponse_buf[u2_t_buf_pos], &u1_ap_XSPI_ADD[8], (U4)u2_t_dt_len);
            u2_s_XspiIviSub0DiagResSize += u2_t_dt_len;

            vd_s_XspiIviSub0DiagCANAna(&u1_sp_XspiIviSub0DiagResponse_buf[0], u2_s_XspiIviSub0DiagResSize);

            vd_g_MemfillU1(&u1_sp_XspiIviSub0DiagResponse_buf[0], (U1)0U, (U4)u2_s_XspiIviSub0DiagResSize);
            u2_s_XspiIviSub0DiagResSize = (U2)0U;
        } else {
            /*応答用のRAMに値を詰めていく＋データサイズもカウントしていく*/
            vd_g_MemcpyU1(&u1_sp_XspiIviSub0DiagResponse_buf[u2_t_buf_pos], &u1_ap_XSPI_ADD[8], (U4)u2_t_dt_len);
            u2_s_XspiIviSub0DiagResSize += u2_t_dt_len;
        }
    } else {
        /*Do Nothing*/
    }

    if((u1_s_XspiIviSub0ResponseFlg != (U1)XSPI_IVI_DIAG_RES_COMP) &&
       (u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_DIAG_TOUT] > (U4)XSPI_IVI_DIAG_TOUT)) {
        u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_COMP;
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub0DiagCANAna(const U1 * u1_ap_SUB1_ADD, const U2 u2_a_DTLEN)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN) Data Analysis                                                                                 */
/*  Arguments:      u1_ap_SUB0_ADD : SubFlame0 DiagCAN Data Start pos                                                                */
/*                  u2_a_DTLEN     : Data Length                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub0DiagCANAna(const U1 * u1_ap_SUB0_ADD, const U2 u2_a_DTLEN)
{
    U1          u1_t_SID;

    u1_t_SID = u1_ap_SUB0_ADD[0];

    if(u1_t_SID == (U1)XSPI_IVI_SID10) {
        vd_g_DiagAppSID10Respons(&u1_ap_SUB0_ADD[0]);
    } else {
        if(u1_s_XspiIviSub0ResponseDeleteFlg != (U1)XSPI_IVI_DIAG_RES_DELETE) {
            switch(u1_t_SID) {
                case XSPI_IVI_SID14:
                    vd_g_XspiIviSub0Response_SID14(&u1_ap_SUB0_ADD[0]);
                    break;
                case XSPI_IVI_SID19:
                    vd_g_XspiIviSub0Response_SID19(&u1_ap_SUB0_ADD[0]);
                    break;
                case XSPI_IVI_SID22:
                    vd_g_XspiIviSub0Response_SID22(&u1_ap_SUB0_ADD[0], u2_a_DTLEN);
                    break;
                case XSPI_IVI_SID2E:
                    vd_g_XspiIviSub0Response_SID2E(&u1_ap_SUB0_ADD[0]);
                    break;
                case XSPI_IVI_SID31:
                    vd_g_XspiIviSub0Response_SID31(&u1_ap_SUB0_ADD[0]);
                    break;
                default :
                    break;
            }
        } else {
        }
        u1_s_XspiIviSub0ResponseDeleteFlg = (U1)XSPI_IVI_DIAG_RES_NODEL;
        u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_COMP;
    }

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0Send(U1 * u1_ap_xspi_add)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u1_ap_xspi_add : SubFlame0 start address                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0Send(U1 * u1_ap_xspi_add)
{
    U2          u2_t_data_size;
    U1          u1_t_canid;
    U1          u1_t_rslt;

    u2_t_data_size = (U2)0U;
    u1_t_canid     = (U1)0U;
    u1_t_rslt      = (U1)FALSE;

    vd_g_MemfillU1(&u1_ap_xspi_add[0], (U1)0U, (U4)XSPI_IVI_DIAG_SIZE);

    if(u1_s_XspiIviSub0SendFlg == (U1)FALSE){
        /*リングバッファからデータ取り出し*/
        vd_g_XspiIviQueueGetDiagCANdataSize(&st_s_XspiIviSub0DiagCanData.u2_data_len);
        (void)u1_g_XspiIviQueueGetDiagCANDataSID(&st_s_XspiIviSub0DiagCanData.u1_sid);
        vd_g_XspiIviQueueGetDiagCANDataID(&st_s_XspiIviSub0DiagCanData.u1_canid);
        vd_g_XspiIviQueueGetDiagCANDataNum(&st_s_XspiIviSub0DiagCanData.u2_frame_num);
        if((st_s_XspiIviSub0DiagCanData.u2_data_len >  (U2)0U) &&
           (st_s_XspiIviSub0DiagCanData.u2_data_len <= (U2)XSPI_IVI_DIAG_MAX_SIZE)) {
            u1_t_rslt = u1_g_XspiIviQueueGetDiagCANdata(&st_s_XspiIviSub0DiagCanData.u1_data[0],st_s_XspiIviSub0DiagCanData.u2_data_len);
            if(u1_t_rslt == (U1)TRUE) {
                u1_s_XspiIviSub0SendFlg = (U1)TRUE;
            }
        }
    }

    if(u1_s_XspiIviSub0SendFlg == (U1)TRUE) {
        if(u1_s_XspiIviSub0ResponseFlg == (U1)XSPI_IVI_DIAG_RES_COMP) {
            vd_s_XspiIviSub0SendDiagCANData(&u2_t_data_size,&u1_t_canid, &u1_ap_xspi_add[8]);
            u1_ap_xspi_add[0] = (U1)((st_s_XspiIviSub0DiagCanData.u2_frame_cnt & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
            u1_ap_xspi_add[1] = (U1)(st_s_XspiIviSub0DiagCanData.u2_frame_cnt & (U2)0x00FFU);
            u1_ap_xspi_add[2] = (U1)((st_s_XspiIviSub0DiagCanData.u2_frame_num & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
            u1_ap_xspi_add[3] = (U1)(st_s_XspiIviSub0DiagCanData.u2_frame_num & (U2)0x00FFU);
            u1_ap_xspi_add[4] = (U1)((u2_t_data_size & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
            u1_ap_xspi_add[5] = (U1)(u2_t_data_size & (U2)0x00FFU);
            u1_ap_xspi_add[6] = (U1)XSPI_IVI_DIAG_TX_MCU_TO_SOC;
            u1_ap_xspi_add[7] = u1_t_canid;

            if(st_s_XspiIviSub0DiagCanData.u2_frame_num == st_s_XspiIviSub0DiagCanData.u2_frame_cnt) {
                u1_s_XspiIviSub0SendFlg = (U1)FALSE;
                st_s_XspiIviSub0DiagCanData.u2_frame_cnt = (U2)0U;
                if((st_s_XspiIviSub0DiagCanData.u1_sid == (U1)XSPI_IVI_SID10) ||
                   (st_s_XspiIviSub0DiagCanData.u1_sid == (U1)XSPI_IVI_SID28)) {
                    u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_COMP;
                } else {
                    u1_s_XspiIviSub0ResponseFlg = (U1)XSPI_IVI_DIAG_RES_WAIT;
                    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_DIAG_TOUT] = (U4)0U;
                }
            }
        }
    } else {
        /*Do Nothing*/
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub0SendDiagCANData(U2 * u2_ap_DATALEN, U1 *u1_ap_CANID, U1 * u1_ap_XSPI_ADD)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u2_ap_DATALEN : SubFlame0 Data Length                                                                            */
/*                  u1_ap_XSPI_ADD : SubFlame0 Diag Data                                                                             */
/*  Return:         u1_t_canid : SubFlame0 CANID                                                                                     */
/*===================================================================================================================================*/
static void         vd_s_XspiIviSub0SendDiagCANData(U2 * u2_ap_datalen, U1 *u1_ap_canid, U1 * u1_ap_xspi_add)
{
    U2  u2_t_size;
    U2  u2_t_buf_pos;

    if(st_s_XspiIviSub0DiagCanData.u2_data_len > (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE) {
        u2_t_buf_pos = st_s_XspiIviSub0DiagCanData.u2_frame_cnt * (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE;
        u2_t_size = st_s_XspiIviSub0DiagCanData.u2_data_len - (st_s_XspiIviSub0DiagCanData.u2_frame_cnt * (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE);
        if(u2_t_size > (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE) {
            *u2_ap_datalen = (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE;
        } else {
            *u2_ap_datalen = u2_t_size;
        }
    } else {
        u2_t_buf_pos = (U2)0U;
        *u2_ap_datalen = st_s_XspiIviSub0DiagCanData.u2_data_len;
    }
    /*受けとったダイアグデータをxspiバッファに格納*/
    /*256以上の場合は分割する＋サブフレームカウンタのRAMをカウントアップ*/
    vd_g_MemcpyU1(&u1_ap_xspi_add[0], &st_s_XspiIviSub0DiagCanData.u1_data[u2_t_buf_pos], (U4)*u2_ap_datalen);
    if(st_s_XspiIviSub0DiagCanData.u2_frame_num != (U2)0U) {
        st_s_XspiIviSub0DiagCanData.u2_frame_cnt++;
    }
    *u1_ap_canid = st_s_XspiIviSub0DiagCanData.u1_canid;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0Request(const U2 u2_a_DATALEN, const U1 u1_a_CANID, const U1 * u1_ap_XSPI_ADD, const U1 u1_a_SID)*/
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame0(DiagCAN Data) Transmission data                                                                        */
/*  Arguments:      u2_ap_DATALEN : SubFlame0 Data Length                                                                            */
/*                  u1_ap_XSPI_ADD : SubFlame0 Diag Data                                                                             */
/*  Return:         u1_t_canid : SubFlame0 CANID                                                                                     */
/*===================================================================================================================================*/
void         vd_g_XspiIviSub0Request(const U2 u2_a_DATALEN, const U1 u1_a_CANID, const U1 * u1_ap_XSPI_ADD, const U1 u1_a_SID)
{
    U1  u1_t_jdg;
    U2  u2_t_num;

    u1_t_jdg = u1_g_XspiIviQueueWriChkDiagCAN(u2_a_DATALEN);

    if(u1_t_jdg == (U1)TRUE) {
        u2_t_num = (u2_a_DATALEN + (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE - (U2)1U) / (U2)XSPI_IVI_DIAG_OSCOM_DATA_SIZE;
        vd_g_XspiIviQueueWriDiagCANdata(u1_ap_XSPI_ADD,u2_a_DATALEN);
        vd_g_XspiIviQueueWriDiagCANdataSize(u2_a_DATALEN);
        vd_g_XspiIviQueueWriDiagCANdataSID(u1_a_SID);
        vd_g_XspiIviQueueWriDiagCANdataID(u1_a_CANID);
        vd_g_XspiIviQueueWriDiagCANdataNum(u2_t_num);
    }

    if((u1_a_SID == (U1)XSPI_IVI_SID10) ||
       (u1_a_SID == (U1)XSPI_IVI_SID28)){
        /*Do Nothing*/
    } else {
        if(u1_s_XspiIviSub0ResponseDeleteFlg == (U1)XSPI_IVI_DIAG_RES_DELETE_RDY) {
            u1_s_XspiIviSub0ResponseDeleteFlg = (U1)XSPI_IVI_DIAG_RES_DELETE;
        } else if(u1_s_XspiIviSub0ResponseDeleteFlg == (U1)XSPI_IVI_DIAG_RES_NODEL){
            u1_s_XspiIviSub0ResponseDeleteFlg = (U1)XSPI_IVI_DIAG_RES_DELETE_RDY;
        } else {
            /*Do Nothing*/
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub0OSComChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    OS Communication bridge check                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub0OSComChk(void)
{
    u1_s_XspiIviSub0OsComBridgeChk = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  U1            u1_g_XspiIviSub0OSComBridge(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    OS Communication bridge check                                                                                    */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_XspiIviSub0OSComBridge(void)
{
    return(u1_s_XspiIviSub0OsComBridgeChk);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    07/17/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
