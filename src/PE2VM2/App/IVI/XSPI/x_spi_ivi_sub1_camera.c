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
#define XSPI_IVI_SUB1_CAMERA_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_CAMERA_C_MINOR                   (0)
#define XSPI_IVI_SUB1_CAMERA_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_camera.h"
#include    "PictCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_CAMERA_C_MAJOR != XSPI_IVI_SUB1_CAMERA_H_MAJOR) || \
     (XSPI_IVI_SUB1_CAMERA_C_MINOR != XSPI_IVI_SUB1_CAMERA_H_MINOR) || \
     (XSPI_IVI_SUB1_CAMERA_C_PATCH != XSPI_IVI_SUB1_CAMERA_H_PATCH))
#error "x_spi_ivi_sub1_camera.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_CAMERA_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_CAMERA_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_CAMERA_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1_camera.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define    XSPI_IVI_CAMERA_TYPE_ID        (0x34U)
#define    XSPI_IVI_CAMERA_TYPE_REC       (0x01U)
#define    XSPI_IVI_CAMERA_TYPE_SEND      (0x02U)
#define    XSPI_IVI_CAMERA_SYNC_SEND      (0x03U)
#define    XSPI_IVI_CAMERA_MODE_REC       (0x04U)
#define    XSPI_IVI_CAMERA_LOG_SEND       (0x05U)

#define    XSPI_IVI_CAMERA_TASK           (3000U / XSPI_IVI_TASK_TIME)
#define    XSPI_IVI_CAMERA_DATA_SIZE      (6U)

#define    XSPI_IVI_CAMERALOG_DATA_SIZE   (36U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_sp_xspi_ivi_camera_data[5];
U1      u1_sp_xspi_ivi_camera_data_pre[5];
U1      u1_sp_xspi_ivi_camera_sync_pass_data[5];
U1      u1_sp_xspi_ivi_camera_sync_pass_data_pre[5];

U1      u1_s_xspi_ivi_camera_data_1stsend_flg;
U1      u1_s_xspi_ivi_camera_sync_1stsend_flg;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void            vd_s_XspiIviSub1CameraData(void);
static void            vd_s_XspiIviSub1CameraSyncPassData(void);
static void            vd_s_XspiIviSub1CameraDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD);
static U1              u1_s_XspiIviSub1CameraDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraInit(void)
{
    /*構造体初期化*/
    u1_s_xspi_ivi_camera_data_1stsend_flg = (U1)FALSE;
    u1_s_xspi_ivi_camera_sync_1stsend_flg = (U1)FALSE;

    vd_g_MemfillU1(&u1_sp_xspi_ivi_camera_data[0], (U1)0U, (U4)XSPI_IVI_CAMERA_DATA_SIZE - (U4)1U);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_camera_data_pre[0], (U1)0U, (U4)XSPI_IVI_CAMERA_DATA_SIZE - (U4)1U);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_camera_sync_pass_data[0], (U1)0U, (U4)XSPI_IVI_CAMERA_DATA_SIZE - (U4)1U);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_camera_sync_pass_data_pre[0], (U1)0U, (U4)XSPI_IVI_CAMERA_DATA_SIZE - (U4)1U);

    u1_sp_xspi_ivi_camera_sync_pass_data[0] = (U1)U1_MAX;
    u1_sp_xspi_ivi_camera_sync_pass_data_pre[0] = (U1)U1_MAX;

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraMainTask(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    定期処理                                                                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraMainTask(void)
{
    U4 u4_t_cameara_task;
    U4 u4_t_camera_sync_task;
    U1 u1_t_camera_ivent_jdg;

    u4_t_cameara_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CAMERA];
    u4_t_camera_sync_task = u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CAMERA_SYNC];

    u1_t_camera_ivent_jdg = (U1)FALSE;
    u1_t_camera_ivent_jdg = u1_s_XspiIviSub1CameraDataEventJdg(&u1_sp_xspi_ivi_camera_data[0],&u1_sp_xspi_ivi_camera_data_pre[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);

    /*定期送信などのデータ作成をここで行う*/
    if(u1_s_xspi_ivi_camera_data_1stsend_flg == (U1)TRUE){/*カメラ種別の初回送信完了済の場合*/
        /*カメラ種別*/
        if((u4_t_cameara_task >= (U4)XSPI_IVI_CAMERA_TASK) || 
           (u1_t_camera_ivent_jdg == (U1)TRUE)){
            /*定期 or イベント送信*/
            vd_s_XspiIviSub1CameraData();
        }else{

        }
    }

    u1_t_camera_ivent_jdg = u1_s_XspiIviSub1CameraDataEventJdg(&u1_sp_xspi_ivi_camera_sync_pass_data[0],&u1_sp_xspi_ivi_camera_sync_pass_data_pre[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);

    /*同期検知*/
    if(u1_s_xspi_ivi_camera_sync_1stsend_flg == (U1)TRUE){/*初回送信完了済の場合*/
        if((u4_t_camera_sync_task >= (U4)XSPI_IVI_CAMERA_TASK) || 
           (u1_t_camera_ivent_jdg == (U1)TRUE)){
            /*定期 or イベント送信*/
            vd_s_XspiIviSub1CameraSyncPassData();
        }else{
        
        }
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraAna(const U1 * u1_ap_XSPI_ADD, const U2 u2_a_data_size)
{
    U1 u1_t_subtype;

    u1_t_subtype = u1_ap_XSPI_ADD[0];

    switch (u1_t_subtype)
    {
    case XSPI_IVI_CAMERA_TYPE_REC:
        vd_s_XspiIviSub1CameraData();
        u1_s_xspi_ivi_camera_data_1stsend_flg = (U1)TRUE;
        break;
    case XSPI_IVI_CAMERA_MODE_REC:
        vd_g_PictCtl_DispQualPraChk(u1_ap_XSPI_ADD[1]);
        break;
    default:
        break;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraDataSend(const ST_XSPI_IVI_MISC_CAMERA_DATA st_a_DATA)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : カメラデータ                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraDataSend(const ST_XSPI_IVI_MISC_CAMERA_DATA st_a_DATA)
{
    u1_sp_xspi_ivi_camera_data[0] = st_a_DATA.u1_camera_type;
    u1_sp_xspi_ivi_camera_data[1] = st_a_DATA.u1_center_camera_size;
    u1_sp_xspi_ivi_camera_data[2] = st_a_DATA.u1_met_camera_size;
    u1_sp_xspi_ivi_camera_data[3] = st_a_DATA.u1_disp_gpio0;
    u1_sp_xspi_ivi_camera_data[4] = st_a_DATA.u1_met_gpio1;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraSyncPassDataSend(const ST_XSPI_IVI_MISC_CAMERA_SYNC_PASS_DATA st_a_DATA)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : 同期検知・経路情報データ                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraSyncPassDataSend(const ST_XSPI_IVI_MISC_CAMERA_SYNC_PASS_DATA st_a_DATA)
{
    u1_sp_xspi_ivi_camera_sync_pass_data[0] = st_a_DATA.u1_camera_sync;
    u1_sp_xspi_ivi_camera_sync_pass_data[1] = st_a_DATA.u1_camera_mipi_display;
    u1_sp_xspi_ivi_camera_sync_pass_data[2] = st_a_DATA.u1_camera_pass;
    u1_sp_xspi_ivi_camera_sync_pass_data[3] = st_a_DATA.u1_camera_mipi_rec;
    u1_sp_xspi_ivi_camera_sync_pass_data[4] = st_a_DATA.u1_camera_vic_sts;

    if(u1_s_xspi_ivi_camera_sync_1stsend_flg == (U1)FALSE){
        vd_s_XspiIviSub1CameraSyncPassData();
        u1_s_xspi_ivi_camera_sync_1stsend_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1CameraData(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : カメラ種別判別データ                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1CameraData(void)
{
    U1 u1_tp_data[6];

    u1_tp_data[0] = (U1)XSPI_IVI_CAMERA_TYPE_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_sp_xspi_ivi_camera_data[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);
    vd_s_XspiIviSub1CameraDataToQueue((U2)XSPI_IVI_CAMERA_DATA_SIZE,u1_tp_data);

    vd_g_MemcpyU1(&u1_sp_xspi_ivi_camera_data_pre[0],&u1_sp_xspi_ivi_camera_data[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CAMERA] = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1CameraSyncPassData(void)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      st_a_DATA : 同期検知・経路情報データ                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1CameraSyncPassData(void)
{
    U1 u1_tp_data[6];

    u1_tp_data[0] = (U1)XSPI_IVI_CAMERA_SYNC_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_sp_xspi_ivi_camera_sync_pass_data[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);
    vd_s_XspiIviSub1CameraDataToQueue((U2)XSPI_IVI_CAMERA_DATA_SIZE,u1_tp_data);

    vd_g_MemcpyU1(&u1_sp_xspi_ivi_camera_sync_pass_data_pre[0],&u1_sp_xspi_ivi_camera_sync_pass_data[0],(U1)XSPI_IVI_CAMERA_DATA_SIZE - (U1)1U);
    u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_CAMERA_SYNC] = (U4)0U;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1CameraDataToQueue(const U2 u2_a_size,const U1 u1_a_XSPI_ADD)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1CameraDataToQueue(const U2 u2_a_size,const U1* u1_ap_XSPI_ADD)
{
    U1     u1_tp_data[256];
    U1     u1_t_id;

    u1_t_id = (U1)XSPI_IVI_CAMERA_TYPE_ID;

    vd_g_MemfillU1(&u1_tp_data[0], (U1)0U, (U4)256U);
    vd_g_MemcpyU1(&u1_tp_data[0], &u1_ap_XSPI_ADD[0], (U4)u2_a_size);

    /*キューの関数呼び出し（そっちでヘッダーとかは入れてく）*/
    vd_g_XspiIviSub1MISCStuckBuff(u1_t_id,u2_a_size,u1_tp_data);
}

/*===================================================================================================================================*/
/*  U1          u1_s_XspiIviSub1CameraDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*                  u2_a_data_size : Data Size                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1CameraDataEventJdg(const U1* u1_ap_DATA,const U1* u1_ap_DATA_PRE,const U1 u1_a_size)
{
    U1     u1_t_judge;
    U4     u4_t_loop;

    u1_t_judge = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_size; u4_t_loop++){
        if(u1_ap_DATA[u4_t_loop] != u1_ap_DATA_PRE[u4_t_loop]){
            u1_t_judge = (U1)TRUE;
        }
    }

    return(u1_t_judge);
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1CameraLogDataSend(const U1 * u1_ap_DATA)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_DATA : Camera Log Data                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1CameraLogDataSend(const U1 * u1_ap_DATA)
{
    U1  u1_tp_data[XSPI_IVI_CAMERALOG_DATA_SIZE];
    U1  u1_t_size;

    u1_t_size = (U1)XSPI_IVI_CAMERALOG_DATA_SIZE - (U1)1U;
    u1_tp_data[0] = (U1)XSPI_IVI_CAMERA_LOG_SEND;
    vd_g_MemcpyU1(&u1_tp_data[1],&u1_ap_DATA[0],u1_t_size);
    vd_s_XspiIviSub1CameraDataToQueue((U2)XSPI_IVI_CAMERALOG_DATA_SIZE,u1_tp_data);
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
