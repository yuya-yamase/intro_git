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
#define XSPI_IVI_SUB2_C_MAJOR                   (0)
#define XSPI_IVI_SUB2_C_MINOR                   (0)
#define XSPI_IVI_SUB2_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub2_private.h"
#include    "x_spi_ivi_private.h"
#include    "GyroDevCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB2_C_MAJOR != XSPI_IVI_SUB2_H_MAJOR) || \
     (XSPI_IVI_SUB2_C_MINOR != XSPI_IVI_SUB2_H_MINOR) || \
     (XSPI_IVI_SUB2_C_PATCH != XSPI_IVI_SUB2_H_PATCH))
#error "x_spi_ivi_sub2.c and x_spi_ivi_sub2.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB2_C_MAJOR != XSPI_IVI_SUB2_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB2_C_MINOR != XSPI_IVI_SUB2_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB2_C_PATCH != XSPI_IVI_SUB2_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub2.c and x_spi_ivi_sub2_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_SFT_01                     ( 1U)
#define XSPI_IVI_SFT_02                     ( 2U)
#define XSPI_IVI_SFT_04                     ( 4U)
#define XSPI_IVI_SFT_08                     ( 8U)
#define XSPI_IVI_SFT_16                     (16U)
#define XSPI_IVI_SFT_24                     (24U)

#define XSPI_IVI_SUBFRAME2_TOTAL_LENGTH    (1032U)
#define XSPI_IVI_SUBFRAME2_DATA_LENGTH     (1024U)
#define XSPI_IVI_SUBFRAME2_VARDT_LENGTH    (1016U)


#define XSPI_IVI_INIT_DATA_LENGTH         (9748U)
#define XSPI_IVI_INIT_DATA_SEND_LENG      (1016U)
#define XSPI_IVI_INIT_DATA_SEND_LAST_LENG  (604U)
#define XSPI_IVI_DATA_LENGTH               (270U)
#define XSPI_IVI_COM_START_RES_LENGTH        (4U)
#define XSPI_IVI_TMPDATA                    (10U)
#define XSPI_IVI_PULSE_TMPDATA              (32U)

#define XSPI_IVI_INIT_DATA_LAST_BUF          (9U)

/*定期送信バッファ位置*/
/*Gyro*/
#define XSPI_IVI_GYRO_X_BUF_POS             (40U)
#define XSPI_IVI_GYRO_Y_BUF_POS             (60U)
#define XSPI_IVI_GYRO_Z_BUF_POS             (80U)
#define XSPI_IVI_GYRO_TEMP_BUF_POS         (100U)
#define XSPI_IVI_GYRO_STS_BUF_POS          (266U)
/*Accel*/
#define XSPI_IVI_ACCL_X_BUF_POS            (104U)
#define XSPI_IVI_ACCL_Y_BUF_POS            (124U)
#define XSPI_IVI_ACCL_Z_BUF_POS            (144U)
#define XSPI_IVI_ACCL_TEMP_BUF_POS         (164U)
#define XSPI_IVI_ACCL_STS_BUF_POS          (267U)
/*Pulse Num*/
#define XSPI_IVI_PULSE_REV_BUF_POS          (16U)
#define XSPI_IVI_PULSE_NUM_BUF_POS          (20U)
/*Pulse Width*/
#define XSPI_IVI_CLKFREQ_BUF_POS           (168U)
#define XSPI_IVI_PULSE_COUNT_BUF_POS       (169U)
#define XSPI_IVI_PULSE_WIDTH_BUF_POS       (170U)

/*初回送信バッファ位置*/
/*Gyro*/
#define XSPI_IVI_GYRO_X_INIT_BUF_POS      (1552U)
#define XSPI_IVI_GYRO_Y_INIT_BUF_POS      (1572U)
#define XSPI_IVI_GYRO_Z_INIT_BUF_POS      (1592U)
#define XSPI_IVI_GYRO_TEMP_INIT_BUF_POS   (1612U)
#define XSPI_IVI_GYRO_STS_INIT_BUF_POS    (9744U)
/*Accel*/
#define XSPI_IVI_ACCL_X_INIT_BUF_POS      (5648U)
#define XSPI_IVI_ACCL_Y_INIT_BUF_POS      (5668U)
#define XSPI_IVI_ACCL_Z_INIT_BUF_POS      (5688U)
#define XSPI_IVI_ACCL_TEMP_INIT_BUF_POS   (5708U)
#define XSPI_IVI_ACCL_STS_INIT_BUF_POS    (9745U)
/*Pulse Num*/
#define XSPI_IVI_PULSE_REV_INIT_BUF_POS     (16U)
#define XSPI_IVI_PULSE_NUM_INIT_BUF_POS     (20U)

/*分解能*/
/*Gyro*/
#define XSPI_IVI_GYRO_AXS_RES            (0x6666)
#define XSPI_IVI_GYRO_TEMP_RES           (0x01F4)
/*Accel*/
#define XSPI_IVI_ACCL_AXS_RES            (0x4000)
#define XSPI_IVI_ACCL_TEMP_RES           (0x007D)

/*中央値*/
/*Gyro*/
#define XSPI_IVI_GYRO_AXS_CEN            (0x0000)
#define XSPI_IVI_GYRO_TEMP_CEN           (0x0018)
/*Accel*/
#define XSPI_IVI_ACCL_AXS_CEN            (0x0000)
#define XSPI_IVI_ACCL_TEMP_CEN           (0x0017)

/*GセンサINT*/
#define XSPI_IVI_GYRO_INT_SET_REQ        (0x11U)
#define XSPI_IVI_GYRO_INT_GET_REQ        (0x13U)
#define XSPI_IVI_GYRO_INT_OUT_REQ        (0x15U)
#define XSPI_IVI_GYRO_INT_SET_RES        (0x12U)
#define XSPI_IVI_GYRO_INT_GET_RES        (0x14U)
#define XSPI_IVI_GYRO_INT_OUT_RES        (0x16U)

#define XSPI_IVI_DATA_INT_SET_LENGTH     (8U)
#define XSPI_IVI_DATA_INT_GET_LENGTH     (16U)
#define XSPI_IVI_DATA_INT_OUT_LENGTH     (8U)

#define XSPI_IVI_GYRO_INT_GET_DATA_SIZE  (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_xspi_ivi_com_start_flg;  /*Communication Start Request*/
static U1 u1_s_xspi_ivi_ini_send_flg;   /*Initial Send Data Request*/
static U1 u1_s_xspi_ivi_comp_com_start; /*Communication Start Complete*/
static U1 u1_s_xspi_ivi_comp_ini_send;  /*Initial Send Data Complete*/

static U1 u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_INIT_DATA_LENGTH];    /*Init Transmission Gyro Data*/
static U1 u1_sp_xspi_ivi_gyro_data[XSPI_IVI_DATA_LENGTH];              /*Regular Transmission Gyro Data*/
/*分解能/中央値格納RAM*/
static U2 u2_s_xspi_ivi_gyro_xyz_reso;
static U2 u2_s_xspi_ivi_gyro_temp_reso;
static U2 u2_s_xspi_ivi_acc_xyz_reso;
static U2 u2_s_xspi_ivi_acc_temp_reso;
static U1 u1_s_xspi_ivi_gyro_xyz_center;
static U1 u1_s_xspi_ivi_gyro_temp_center;
static U1 u1_s_xspi_ivi_acc_xyz_center;
static U1 u1_s_xspi_ivi_acc_temp_center;
/*センサデータ格納RAM*/
static U1 u1_sp_xspi_ivi_gyro_x_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_x_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_y_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_y_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_z_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_z_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_temp_data[XSPI_IVI_TMPDATA];
static U1 u1_s_xspi_ivi_gyro_x_valid_data;
static U1 u1_s_xspi_ivi_gyro_y_valid_data;
static U1 u1_s_xspi_ivi_gyro_z_valid_data;
static U1 u1_s_xspi_ivi_gyro_temp_valid_data;
static U1 u1_sp_xspi_ivi_acc_x_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_x_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_y_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_y_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_z_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_z_data_up[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_temp_data_down[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_temp_data_up[XSPI_IVI_TMPDATA];
static U1 u1_s_xspi_ivi_acc_x_valid_data;
static U1 u1_s_xspi_ivi_acc_y_valid_data;
static U1 u1_s_xspi_ivi_acc_z_valid_data;
static U1 u1_s_xspi_ivi_acc_temp_valid_data;
static U2 u2_sp_xspi_ivi_pulse_num[XSPI_IVI_TMPDATA];
/*100msデータ作成までの退避RAM*/
static U1 u1_sp_xspi_ivi_gyro_x_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_x_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_y_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_y_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_z_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_gyro_z_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_s_xspi_ivi_gyro_temp_data_tmp;
static U1 u1_s_xspi_ivi_gyro_x_valid_data_tmp;
static U1 u1_s_xspi_ivi_gyro_y_valid_data_tmp;
static U1 u1_s_xspi_ivi_gyro_z_valid_data_tmp;
static U1 u1_s_xspi_ivi_gyro_temp_valid_data_tmp;
static U1 u1_sp_xspi_ivi_acc_x_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_x_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_y_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_y_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_z_data_down_tmp[XSPI_IVI_TMPDATA];
static U1 u1_sp_xspi_ivi_acc_z_data_up_tmp[XSPI_IVI_TMPDATA];
static U1 u1_s_xspi_ivi_acc_temp_data_down_tmp;
static U1 u1_s_xspi_ivi_acc_temp_data_up_tmp;
static U1 u1_s_xspi_ivi_acc_x_valid_data_tmp;
static U1 u1_s_xspi_ivi_acc_y_valid_data_tmp;
static U1 u1_s_xspi_ivi_acc_z_valid_data_tmp;
static U1 u1_s_xspi_ivi_acc_temp_valid_data_tmp;
static U2 u2_sp_xspi_ivi_pulse_num_tmp[XSPI_IVI_TMPDATA];
static U4 u4_sp_xspi_ivi_pulse_width_tmp[XSPI_IVI_PULSE_TMPDATA];
static U1 u1_s_xspi_ivi_clock_freq_tmp;
static U4 u4_s_xspi_ivi_pulse_count_tmp;

static U2 u2_s_xspi_ivi_total_pulse_num;

static U1 u2_s_xspi_ivi_ini_buf_cnt;                          /*SubFrame Num*/
static U1 u1_s_xspi_ivi_tmp_gyro_ini_cnt;                     /*tmp_gyro ini buf num*/
static U1 u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf;                     /*tmp_gyro ini buf num*/
static U1 u1_s_xspi_ivi_gyro_buf_cnt;
static U1 u1_s_xspi_ivi_pulse_buf_cnt;

static U1 u1_s_xspi_ivi_gyro_receive_finish_flg;
static U1 u1_s_xspi_ivi_pulsenum_receive_finish_flg;
static U1 u1_s_xspi_ivi_pulsewid_receive_finish_flg;

static U1 u1_sp_xspi_ivi_gyro_int_setting_result;
static U1 u1_sp_xspi_ivi_gyro_int_get_data[XSPI_IVI_GYRO_INT_GET_DATA_SIZE];
static U1 u1_sp_xspi_ivi_gyro_int_output_result;
static U1 u1_s_xspi_ivi_gyroint_set_response_flg;
static U1 u1_s_xspi_ivi_gyroint_get_response_flg;
static U1 u1_s_xspi_ivi_gyroint_output_response_flg;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviSub2GyroAna(const U1 * u1_ap_SUB2_ADD, const U2 u2_a_DTLEN);
static void     vd_s_XspiIviSub2FrameHeader(U1 * u1_ap_buf,const U2 u2_a_DTLEN,const U2 u2_a_CNT);
static void     vd_s_XspiIviSub2SenSensorData(U1 * u1_ap_xspi_add);
static void     vd_s_XspiIviSub2PeriBufSet(void);
static void     vd_s_XspiIviSub21stBufSet(void);

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
void            vd_g_XspiIviSub2Init(void)
{
    /*送信用バッファ初期化*/
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_init_data[0], (U1)0U, (U4)XSPI_IVI_INIT_DATA_LENGTH);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_data[0], (U1)0U, (U4)XSPI_IVI_DATA_LENGTH);

    /*分解能・中央値初期化*/
    u2_s_xspi_ivi_gyro_xyz_reso = (U2)0U;
    u2_s_xspi_ivi_gyro_temp_reso = (U2)0U;
    u2_s_xspi_ivi_acc_xyz_reso = (U2)0U;
    u2_s_xspi_ivi_acc_temp_reso = (U2)0U;
    u1_s_xspi_ivi_gyro_xyz_center = (U1)0U;
    u1_s_xspi_ivi_gyro_temp_center = (U1)0U;
    u1_s_xspi_ivi_acc_xyz_center = (U1)0U;
    u1_s_xspi_ivi_acc_temp_center = (U1)0U;
    /*センサデータ格納バッファ初期化*/
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_x_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_x_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_y_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_y_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_z_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_z_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_temp_data[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    u1_s_xspi_ivi_gyro_x_valid_data = (U1)0U;
    u1_s_xspi_ivi_gyro_y_valid_data = (U1)0U;
    u1_s_xspi_ivi_gyro_z_valid_data = (U1)0U;
    u1_s_xspi_ivi_gyro_temp_valid_data = (U1)0U;
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_x_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_x_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_y_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_y_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_z_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_z_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_temp_data_down[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_temp_data_up[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    u1_s_xspi_ivi_acc_x_valid_data = (U1)0U;
    u1_s_xspi_ivi_acc_y_valid_data = (U1)0U;
    u1_s_xspi_ivi_acc_z_valid_data = (U1)0U;
    u1_s_xspi_ivi_acc_temp_valid_data = (U1)0U;
    vd_g_MemfillU2(&u2_sp_xspi_ivi_pulse_num[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    /*送信バッファに格納する前の退避バッファの初期化*/
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_x_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_x_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_y_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_y_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_z_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_z_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    u1_s_xspi_ivi_gyro_temp_data_tmp = (U1)0U;
    u1_s_xspi_ivi_gyro_x_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_gyro_y_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_gyro_z_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_gyro_temp_valid_data_tmp = (U1)0U;
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_x_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_x_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_y_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_y_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_z_data_down_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_acc_z_data_up_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    u1_s_xspi_ivi_acc_temp_data_down_tmp = (U1)0U;
    u1_s_xspi_ivi_acc_temp_data_up_tmp = (U1)0U;
    u1_s_xspi_ivi_acc_x_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_acc_y_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_acc_z_valid_data_tmp = (U1)0U;
    u1_s_xspi_ivi_acc_temp_valid_data_tmp = (U1)0U;
    vd_g_MemfillU2(&u2_sp_xspi_ivi_pulse_num_tmp[0], (U1)0U, (U4)XSPI_IVI_TMPDATA);
    vd_g_MemfillU4(&u4_sp_xspi_ivi_pulse_width_tmp[0], (U1)0U, (U4)XSPI_IVI_PULSE_TMPDATA);
    u1_s_xspi_ivi_clock_freq_tmp = (U1)0U;
    u4_s_xspi_ivi_pulse_count_tmp = (U4)0U;

	u1_s_xspi_ivi_com_start_flg  = (U1)FALSE;                   /*通信開始フラグ初期化*/
    u1_s_xspi_ivi_ini_send_flg   = (U1)FALSE;                   /*初回送信開始フラグ初期化*/
    u1_s_xspi_ivi_comp_com_start = (U1)FALSE;                   /*通信開始応答完了フラグ初期化*/
    u1_s_xspi_ivi_comp_ini_send  = (U1)FALSE;                   /*初回送信完了フラグ初期化*/
    u2_s_xspi_ivi_ini_buf_cnt = (U2)0U;                         /*分割送信フレーム番号初期化*/
    u1_s_xspi_ivi_tmp_gyro_ini_cnt = (U1)0U;                    /*初回送信データ数初期化*/
    u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf = (U1)0U;                /*初回送信データのリングバッファ格納箇所初期化*/
    u1_s_xspi_ivi_gyro_buf_cnt = (U1)0U;                        /*ジャイロセンサ受信回数初期化*/
    u1_s_xspi_ivi_pulse_buf_cnt = (U1)0U;                       /*パルス受信回数初期化*/

    u2_s_xspi_ivi_total_pulse_num = (U2)0U;                     /*生涯スピードパルス数*/

    u1_s_xspi_ivi_gyro_receive_finish_flg = (U1)FALSE;
    u1_s_xspi_ivi_pulsenum_receive_finish_flg = (U1)FALSE;
    u1_s_xspi_ivi_pulsewid_receive_finish_flg = (U1)FALSE;

    u1_sp_xspi_ivi_gyro_int_setting_result = (U1)0U;
    u1_sp_xspi_ivi_gyro_int_output_result = (U1)0U;
    vd_g_MemfillU1(&u1_sp_xspi_ivi_gyro_int_get_data[0], (U1)0U, (U4)XSPI_IVI_GYRO_INT_GET_DATA_SIZE);
    u1_s_xspi_ivi_gyroint_set_response_flg = (U1)FALSE;
    u1_s_xspi_ivi_gyroint_get_response_flg = (U1)FALSE;
    u1_s_xspi_ivi_gyroint_output_response_flg = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2Ana(const U1 * u1_ap_XSPI_ADD)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(GYRO) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame2 Start Buffer                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2Ana(const U1 * u1_ap_XSPI_ADD)
{
    //U2          u2_t_frame_counter;     /* Sub Frame Counter */
    //U2          u2_t_frame_num;         /* Sub Frame num */
    U2          u2_t_dt_len;            /* data length */
    //U1          u1_t_dt_type;           /* Transmit or Recieve */

    //u2_t_frame_counter  = (U2)((u1_ap_XSPI_ADD[0] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[1]);
    //u2_t_frame_num      = (U2)((u1_ap_XSPI_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[3]);
    u2_t_dt_len         = (U2)((u1_ap_XSPI_ADD[4] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[5]);
    //u1_t_dt_type        = u1_ap_XSPI_ADD[6];

    vd_s_XspiIviSub2GyroAna(&u1_ap_XSPI_ADD[8], u2_t_dt_len);

}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub2GyroAna(const U1 * u1_ap_SUB2_ADD, const U2 u2_a_DTLEN)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(GYRO) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_SUB2_ADD : SubFlame2 GYRO Data Start pos                                                                   */
/*                  u2_a_DTLEN     : Data Length                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub2GyroAna(const U1 * u1_ap_SUB2_ADD, const U2 u2_a_DTLEN)
{
    static const U1 u1_s_GYRO_SUBTYPE_COM_START_REQ = (U1)0x01U;
    static const U1 u1_s_GYRO_SUBTYPE_INIT_DATA_REQ = (U1)0x03U;

    U1          u1_t_subtype;   /*SubFlame Subtype*/
    ST_GYRODEV_NOTIFCOND_SETDATA  st_t_setdata;
    ST_GYRODEV_CTRLOUT_SETDATA    st_t_outputdata;

    u1_t_subtype = u1_ap_SUB2_ADD[0];

    if((u1_t_subtype == (U1)u1_s_GYRO_SUBTYPE_COM_START_REQ) && (u1_s_xspi_ivi_com_start_flg == (U1)FALSE)) {
        u1_s_xspi_ivi_com_start_flg = (U1)TRUE;
    }else if((u1_t_subtype == (U1)u1_s_GYRO_SUBTYPE_INIT_DATA_REQ) &&  (u1_s_xspi_ivi_ini_send_flg == (U1)FALSE)){
        u1_s_xspi_ivi_ini_send_flg = (U1)TRUE;
    }else{
        /* Do Nothing */
    }

    switch (u1_t_subtype)
    {
    case XSPI_IVI_GYRO_INT_SET_REQ:
        st_t_setdata.u1_threshold = u1_ap_SUB2_ADD[4];
        st_t_setdata.u1_axis_x = u1_ap_SUB2_ADD[5];
        st_t_setdata.u1_axis_y = u1_ap_SUB2_ADD[6];
        st_t_setdata.u1_axis_z = u1_ap_SUB2_ADD[7];
        st_t_setdata.u1_active = u1_ap_SUB2_ADD[8];
        vd_g_GyroDev_NotifCond_SetReq(st_t_setdata);
        break;
    case XSPI_IVI_GYRO_INT_GET_REQ:
        vd_g_GyroDev_NotifCond_ReadReq();
        break;
    case XSPI_IVI_GYRO_INT_OUT_REQ:
        st_t_outputdata.u1_type         = u1_ap_SUB2_ADD[4];
        st_t_outputdata.u1_type_standby = u1_ap_SUB2_ADD[5];
        vd_g_GyroDev_OutCtl_SetReq(st_t_outputdata);
        break;
    
    default:
        break;
    }

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2Send(U1 * u1_ap_xspi_add)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u1_ap_xspi_add : SubFlame2 start address                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2Send(U1 * u1_ap_xspi_add)
{
    /*ジャイロ・パルス数・パルス幅全部100ms取得済の場合、送信バッファにデータ格納*/
    /*データ格納したら受信完了フラグをOFFにする*/
    if((u1_s_xspi_ivi_gyro_receive_finish_flg == (U1)TRUE) &&
       (u1_s_xspi_ivi_pulsenum_receive_finish_flg == (U1)TRUE) &&
       (u1_s_xspi_ivi_pulsewid_receive_finish_flg == (U1)TRUE))
    {
        /*通信開始応答を返答したか判定*/
        if(u1_s_xspi_ivi_com_start_flg == (U1)TRUE) {
            /*定期送信バッファに格納*/
            vd_s_XspiIviSub2PeriBufSet();
        } else {
            /*初回送信バッファに格納*/
            vd_s_XspiIviSub21stBufSet();
        }
        u1_s_xspi_ivi_gyro_receive_finish_flg = (U1)FALSE;
        u1_s_xspi_ivi_pulsenum_receive_finish_flg = (U1)FALSE;
        u1_s_xspi_ivi_pulsewid_receive_finish_flg = (U1)FALSE;
    }

    vd_g_MemfillU1(&u1_ap_xspi_add[0],(U1)0U,(U4)XSPI_IVI_SUBFRAME2_TOTAL_LENGTH);

    /*通信開始応答かそうじゃないか*/
    if((u1_s_xspi_ivi_com_start_flg == (U1)TRUE) && (u1_s_xspi_ivi_comp_com_start == (U1)FALSE)) {
        /* 通信開始応答 */
        vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_COM_START_RES_LENGTH,(U2)0U);
        u1_ap_xspi_add[8] = (U1)0x02;
        u1_ap_xspi_add[9] = (U1)0x00;
        u1_ap_xspi_add[10] = (U1)0x00;
        u1_ap_xspi_add[11] = (U1)0x00;

        u1_s_xspi_ivi_comp_com_start = (U1)TRUE;
        u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_GYRO] = (U4)0U;
    }else if((u1_s_xspi_ivi_com_start_flg == (U1)TRUE) && (u1_s_xspi_ivi_comp_com_start == (U1)TRUE)){
        /*Gyroセンサデータ取得処理*/
        vd_s_XspiIviSub2SenSensorData(u1_ap_xspi_add);
    }else{
        /*Do Nothing*/
    }
}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub2SenSensorData(U1 * u1_ap_xspi_add)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u1_ap_xspi_add : SubFlame2 start address                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub2SenSensorData(U1 * u1_ap_xspi_add)
{
    U4 u4_s_XSPI_IVI_TASK_SEND_CNT = (U4)100U / (U4)XSPI_IVI_TASK_TIME;
    U4 u4_s_XSPI_IVI_TASK_INIT_SEND_CNT = (U4)20U / (U4)XSPI_IVI_TASK_TIME;


    U2 u2_t_buf_cnt;
    U2 u2_t_dt_size;

    u2_t_buf_cnt = (U2)0U;
    u2_t_dt_size = (U2)0U;

    /*定期送信処理と初回送信処理の切り分け*/
    if(u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_GYRO] >= u4_s_XSPI_IVI_TASK_SEND_CNT){
        /*定期送信処理*/
        vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_DATA_LENGTH,(U2)0U);
        vd_g_MemcpyU1(&u1_ap_xspi_add[8], &u1_sp_xspi_ivi_gyro_data[0], (U4)XSPI_IVI_DATA_LENGTH);
        u1_ap_xspi_add[8]  = (U1)0x05; /*SubType*/
        u1_ap_xspi_add[9]  = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[10] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[11] = (U1)0x00; /*Reserve*/
        u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_GYRO] = (U4)0U;

    }else if((u1_s_xspi_ivi_ini_send_flg == (U1)TRUE) && (u1_s_xspi_ivi_comp_ini_send == (U1)FALSE)) {
        /*20msごとに*/
        if(u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_GYRO_INI] >= u4_s_XSPI_IVI_TASK_INIT_SEND_CNT) {
            /*初回送信*/
            u2_t_buf_cnt = u2_s_xspi_ivi_ini_buf_cnt * (U2)1016U;

            vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_INIT_DATA_LENGTH,u2_s_xspi_ivi_ini_buf_cnt);

            /*初回送信の0-7byteフィールド*/
            u1_ap_xspi_add[8]  = (U1)0x04; /*SubType*/
            u1_ap_xspi_add[9]  = (U1)0x00; /*Reserve*/
            u1_ap_xspi_add[10] = (U1)0x00; /*Reserve*/
            u1_ap_xspi_add[11] = (U1)0x00; /*Reserve*/
            u1_ap_xspi_add[12] = (U1)(((U2)XSPI_IVI_INIT_DATA_LENGTH / (U2)XSPI_IVI_INIT_DATA_SEND_LENG)+(U2)1U);  /*Total Div Frame */
            u1_ap_xspi_add[13] = (U1)(u2_s_xspi_ivi_ini_buf_cnt + (U2)1U);  /*Frame Number*/

            if(u2_s_xspi_ivi_ini_buf_cnt >= (U2)XSPI_IVI_INIT_DATA_LAST_BUF) {
                u2_t_dt_size = (U2)XSPI_IVI_INIT_DATA_SEND_LAST_LENG;
                u1_ap_xspi_add[14] = (U1)(u2_t_dt_size & 0x00FFU);  /*Frame Data Num(Lo)*/
                u1_ap_xspi_add[15] = (U1)((u2_t_dt_size & 0xFF00U)>>XSPI_IVI_SFT_08);  /*Frame Data Num(Hi)*/

                /*初回送信完了*/
                vd_g_MemcpyU1(&u1_ap_xspi_add[16], &u1_sp_xspi_ivi_gyro_init_data[u2_t_buf_cnt], (U4)XSPI_IVI_INIT_DATA_SEND_LAST_LENG);
                u1_s_xspi_ivi_comp_ini_send = (U1)TRUE;
            } else{
                u2_t_dt_size = (U2)XSPI_IVI_INIT_DATA_SEND_LENG;
                u1_ap_xspi_add[14] = (U1)(u2_t_dt_size & 0x00FFU);  /*Frame Data Num(Lo)*/
                u1_ap_xspi_add[15] = (U1)((u2_t_dt_size & 0xFF00U)>>XSPI_IVI_SFT_08);  /*Frame Data Num(Hi)*/

                vd_g_MemcpyU1(&u1_ap_xspi_add[16], &u1_sp_xspi_ivi_gyro_init_data[u2_t_buf_cnt], (U4)XSPI_IVI_INIT_DATA_SEND_LENG);
            }

            u2_s_xspi_ivi_ini_buf_cnt++;
            u4_s_xspi_ivi_task_cnt[XSPI_TASK_CNT_GYRO_INI] = (U4)0U;
        }
        /*Gyroセンサデータ取得処理*/
    }else if(u1_s_xspi_ivi_gyroint_set_response_flg == (U1)TRUE){
        vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_DATA_INT_SET_LENGTH,(U2)0U);
        u1_ap_xspi_add[8]  = (U1)XSPI_IVI_GYRO_INT_SET_RES; /*SubType*/
        u1_ap_xspi_add[9]  = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[10] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[11] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[12] = u1_sp_xspi_ivi_gyro_int_setting_result;
        u1_s_xspi_ivi_gyroint_set_response_flg = (U1)FALSE;

    }else if(u1_s_xspi_ivi_gyroint_get_response_flg == (U1)TRUE){
        vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_DATA_INT_GET_LENGTH,(U2)0U);
        u1_ap_xspi_add[8]  = (U1)XSPI_IVI_GYRO_INT_GET_RES; /*SubType*/
        u1_ap_xspi_add[9]  = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[10] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[11] = (U1)0x00; /*Reserve*/
        vd_g_MemcpyU1(&u1_ap_xspi_add[12], &u1_sp_xspi_ivi_gyro_int_get_data[0], (U4)XSPI_IVI_GYRO_INT_GET_DATA_SIZE);
        u1_s_xspi_ivi_gyroint_get_response_flg = (U1)FALSE;

    }else if(u1_s_xspi_ivi_gyroint_output_response_flg == (U1)TRUE){
        vd_s_XspiIviSub2FrameHeader(u1_ap_xspi_add,(U2)XSPI_IVI_DATA_INT_OUT_LENGTH,(U2)0U);
        u1_ap_xspi_add[8]  = (U1)XSPI_IVI_GYRO_INT_OUT_RES; /*SubType*/
        u1_ap_xspi_add[9]  = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[10] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[11] = (U1)0x00; /*Reserve*/
        u1_ap_xspi_add[12] = u1_sp_xspi_ivi_gyro_int_output_result;
        u1_s_xspi_ivi_gyroint_output_response_flg = (U1)FALSE;

    }else{
        /*Do Nothing*/
    }
}

/*===================================================================================================================================*/
/*  static void              vd_s_XspiIviSub2FrameHeader(U1 * u1_ap_buf,const U2 u2_a_DTLEN,const U2 u2_a_CNT)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFrame2 Header Set                                                                                             */
/*  Arguments:      u1_ap_buf    : Header Set Start Pos                                                                              */
/*                  u2_a_DTLEN : Data Length                                                                                         */
/*===================================================================================================================================*/
static void              vd_s_XspiIviSub2FrameHeader(U1 * u1_ap_buf,const U2 u2_a_DTLEN,const U2 u2_a_CNT)
{
    U1          u1_tp_subframe2_header[XSPI_IVI_HEADER];    /* Sub Frame2 Header Field */
    U2          u2_t_subframe2_dtlen;

    if(u2_a_DTLEN > (U2)XSPI_IVI_SUBFRAME2_DATA_LENGTH) {
        u2_t_subframe2_dtlen = (u2_a_DTLEN - (u2_a_CNT * ((U2)XSPI_IVI_SUBFRAME2_DATA_LENGTH - (U2)XSPI_IVI_HEADER)));
        if(u2_t_subframe2_dtlen > (U2)XSPI_IVI_SUBFRAME2_VARDT_LENGTH){
            u2_t_subframe2_dtlen = (U2)XSPI_IVI_SUBFRAME2_DATA_LENGTH;
        } else {
            u2_t_subframe2_dtlen = u2_t_subframe2_dtlen + (U2)XSPI_IVI_HEADER;
        }
    } else {
        u2_t_subframe2_dtlen = u2_a_DTLEN;
    }

    if(u2_t_subframe2_dtlen > (U2)XSPI_IVI_SUBFRAME2_DATA_LENGTH) {
        u2_t_subframe2_dtlen = (U2)XSPI_IVI_SUBFRAME2_DATA_LENGTH;
    }

    /* SubFrame2 Header Field */
    u1_tp_subframe2_header[0] = (U1)0x00U;
    u1_tp_subframe2_header[1] = (U1)0x01U;
    u1_tp_subframe2_header[2] = (U1)0x00U;
    u1_tp_subframe2_header[3] = (U1)0x01U;
    u1_tp_subframe2_header[4] = (U1)((u2_t_subframe2_dtlen & 0xFF00U) >> XSPI_IVI_SFT_08);
    u1_tp_subframe2_header[5] = (U1)(u2_t_subframe2_dtlen & 0x00FFU);
    u1_tp_subframe2_header[6] = (U1)0x04;
    u1_tp_subframe2_header[7] = (U1)0x00;

    vd_g_MemcpyU1(&u1_ap_buf[0], &u1_tp_subframe2_header[0], (U4)XSPI_IVI_HEADER);

}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2GyroDataPut(const ST_XSPI_IVI_GYRO_SENSOR_DATA st_a_GYRO_DATA)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      st_a_GYRO_DATA : Gyro Sensor Data                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2GyroDataPut(const ST_XSPI_IVI_GYRO_SENSOR_DATA st_a_GYRO_DATA)
{
    u2_s_xspi_ivi_gyro_xyz_reso = st_a_GYRO_DATA.st_gyro_reso.u2_gyro_xyz_reso;
    u2_s_xspi_ivi_gyro_temp_reso = st_a_GYRO_DATA.st_gyro_reso.u2_gyro_temp_reso;
    u2_s_xspi_ivi_acc_xyz_reso = st_a_GYRO_DATA.st_gyro_reso.u2_accel_xyz_reso;
    u2_s_xspi_ivi_acc_temp_reso = st_a_GYRO_DATA.st_gyro_reso.u2_accel_temp_reso;
    u1_s_xspi_ivi_gyro_xyz_center = st_a_GYRO_DATA.st_gyro_reso.u1_gyro_xyz_center;
    u1_s_xspi_ivi_gyro_temp_center = st_a_GYRO_DATA.st_gyro_reso.u1_gyro_temp_center;
    u1_s_xspi_ivi_acc_xyz_center = st_a_GYRO_DATA.st_gyro_reso.u1_accel_xyz_center;
    u1_s_xspi_ivi_acc_temp_center = st_a_GYRO_DATA.st_gyro_reso.u1_accel_temp_center;
    u1_sp_xspi_ivi_gyro_x_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_x_data_down;
    u1_sp_xspi_ivi_gyro_x_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_x_data_up;
    u1_sp_xspi_ivi_gyro_y_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_y_data_down;
    u1_sp_xspi_ivi_gyro_y_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_y_data_up;
    u1_sp_xspi_ivi_gyro_z_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_z_data_down;
    u1_sp_xspi_ivi_gyro_z_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_z_data_up;
    u1_sp_xspi_ivi_gyro_temp_data[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_gyro_temp_data;
    u1_s_xspi_ivi_gyro_x_valid_data |= st_a_GYRO_DATA.u1_gyro_x_data_sts;
    u1_s_xspi_ivi_gyro_y_valid_data |= st_a_GYRO_DATA.u1_gyro_y_data_sts;
    u1_s_xspi_ivi_gyro_z_valid_data |= st_a_GYRO_DATA.u1_gyro_z_data_sts;
    u1_s_xspi_ivi_gyro_temp_valid_data |= st_a_GYRO_DATA.u1_gyro_temp_data_sts;
    u1_sp_xspi_ivi_acc_x_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_x_data_down;
    u1_sp_xspi_ivi_acc_x_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_x_data_up;
    u1_sp_xspi_ivi_acc_y_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_y_data_down;
    u1_sp_xspi_ivi_acc_y_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_y_data_up;
    u1_sp_xspi_ivi_acc_z_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_z_data_down;
    u1_sp_xspi_ivi_acc_z_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_z_data_up;
    u1_sp_xspi_ivi_acc_temp_data_down[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_temp_data_down;
    u1_sp_xspi_ivi_acc_temp_data_up[u1_s_xspi_ivi_gyro_buf_cnt] = st_a_GYRO_DATA.u1_accl_temp_data_up;
    u1_s_xspi_ivi_acc_x_valid_data |= st_a_GYRO_DATA.u1_accl_x_data_sts;
    u1_s_xspi_ivi_acc_y_valid_data |= st_a_GYRO_DATA.u1_accl_y_data_sts;
    u1_s_xspi_ivi_acc_z_valid_data |= st_a_GYRO_DATA.u1_accl_z_data_sts;
    u1_s_xspi_ivi_acc_temp_valid_data |= st_a_GYRO_DATA.u1_accl_temp_data_sts;

    u1_s_xspi_ivi_gyro_buf_cnt++;
    if(u1_s_xspi_ivi_gyro_buf_cnt >= (U1)XSPI_IVI_TMPDATA){
        /*退避用バッファに移動*/
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_x_data_down_tmp[0], &u1_sp_xspi_ivi_gyro_x_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_x_data_up_tmp[0], &u1_sp_xspi_ivi_gyro_x_data_up[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_y_data_down_tmp[0], &u1_sp_xspi_ivi_gyro_y_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_y_data_up_tmp[0], &u1_sp_xspi_ivi_gyro_y_data_up[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_z_data_down_tmp[0], &u1_sp_xspi_ivi_gyro_z_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_gyro_z_data_up_tmp[0], &u1_sp_xspi_ivi_gyro_z_data_up[0], (U4)XSPI_IVI_TMPDATA);
        u1_s_xspi_ivi_gyro_temp_data_tmp = u1_sp_xspi_ivi_gyro_temp_data[9];
        u1_s_xspi_ivi_gyro_x_valid_data_tmp = u1_s_xspi_ivi_gyro_x_valid_data;
        u1_s_xspi_ivi_gyro_y_valid_data_tmp = u1_s_xspi_ivi_gyro_y_valid_data;
        u1_s_xspi_ivi_gyro_z_valid_data_tmp = u1_s_xspi_ivi_gyro_z_valid_data;
        u1_s_xspi_ivi_gyro_temp_valid_data_tmp = u1_s_xspi_ivi_gyro_temp_valid_data;
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_x_data_down_tmp[0], &u1_sp_xspi_ivi_acc_x_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_x_data_up_tmp[0], &u1_sp_xspi_ivi_acc_x_data_up[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_y_data_down_tmp[0], &u1_sp_xspi_ivi_acc_y_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_y_data_up_tmp[0], &u1_sp_xspi_ivi_acc_y_data_up[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_z_data_down_tmp[0], &u1_sp_xspi_ivi_acc_z_data_down[0], (U4)XSPI_IVI_TMPDATA);
        vd_g_MemcpyU1(&u1_sp_xspi_ivi_acc_z_data_up_tmp[0], &u1_sp_xspi_ivi_acc_z_data_up[0], (U4)XSPI_IVI_TMPDATA);
        u1_s_xspi_ivi_acc_temp_data_down_tmp = u1_sp_xspi_ivi_acc_temp_data_down[9];
        u1_s_xspi_ivi_acc_temp_data_up_tmp = u1_sp_xspi_ivi_acc_temp_data_up[9];
        u1_s_xspi_ivi_acc_x_valid_data_tmp = u1_s_xspi_ivi_acc_x_valid_data;
        u1_s_xspi_ivi_acc_y_valid_data_tmp = u1_s_xspi_ivi_acc_y_valid_data;
        u1_s_xspi_ivi_acc_z_valid_data_tmp = u1_s_xspi_ivi_acc_z_valid_data;
        u1_s_xspi_ivi_acc_temp_valid_data_tmp = u1_s_xspi_ivi_acc_temp_valid_data;
        /*カウント0クリア*/
        u1_s_xspi_ivi_gyro_buf_cnt = (U1)0U;
        /*有効情報0クリア*/
        u1_s_xspi_ivi_gyro_x_valid_data = (U1)0U;
        u1_s_xspi_ivi_gyro_y_valid_data = (U1)0U;
        u1_s_xspi_ivi_gyro_z_valid_data = (U1)0U;
        u1_s_xspi_ivi_gyro_temp_valid_data = (U1)0U;
        u1_s_xspi_ivi_acc_x_valid_data = (U1)0U;
        u1_s_xspi_ivi_acc_y_valid_data = (U1)0U;
        u1_s_xspi_ivi_acc_z_valid_data = (U1)0U;
        u1_s_xspi_ivi_acc_temp_valid_data = (U1)0U;

        u1_s_xspi_ivi_gyro_receive_finish_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2PulseNumDataPut(const U2 u2_a_PULSE_NUM)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u2_a_PULSE_NUM : PULSE NUM Data                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2PulseNumDataPut(const U2 u2_a_PULSE_NUM)
{

    u2_s_xspi_ivi_total_pulse_num = u2_s_xspi_ivi_total_pulse_num + u2_a_PULSE_NUM;
    u2_sp_xspi_ivi_pulse_num[u1_s_xspi_ivi_pulse_buf_cnt] = u2_s_xspi_ivi_total_pulse_num;

    u1_s_xspi_ivi_pulse_buf_cnt++;
    if(u1_s_xspi_ivi_pulse_buf_cnt >= (U1)XSPI_IVI_TMPDATA){
        /*退避用バッファに移動*/
        vd_g_MemcpyU2(&u2_sp_xspi_ivi_pulse_num_tmp[0], &u2_sp_xspi_ivi_pulse_num[0], (U4)XSPI_IVI_TMPDATA);
        /*カウント0クリア*/
        u1_s_xspi_ivi_pulse_buf_cnt = (U1)0U;

        u1_s_xspi_ivi_pulsenum_receive_finish_flg = (U1)TRUE;
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2PulseWidDataPut(const ST_XSPI_IVI_PULSE_WID_DATA st_a_PULSE_WID)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      st_a_PULSE_WID : PULSE WIDTH Data                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2PulseWidDataPut(const ST_XSPI_IVI_PULSE_WID_DATA st_a_PULSE_WID)
{
    vd_g_MemcpyU4(&u4_sp_xspi_ivi_pulse_width_tmp[0],&st_a_PULSE_WID.u4_pulse_width[0],(U4)XSPI_IVI_PULSE_TMPDATA);
    u1_s_xspi_ivi_clock_freq_tmp = st_a_PULSE_WID.u1_clock_freq;
    u4_s_xspi_ivi_pulse_count_tmp = st_a_PULSE_WID.u4_pulse_count;

    u1_s_xspi_ivi_pulsewid_receive_finish_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2GyroIntSetSend(const U1 u1_a_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u1_a_DATA : Setting Result                                                                                       */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2GyroIntSetSend(const U1 u1_a_DATA)
{
    u1_sp_xspi_ivi_gyro_int_setting_result = u1_a_DATA;
    u1_s_xspi_ivi_gyroint_set_response_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2GyroIntGetSend(const ST_XSPI_IVI_GYRO_INT_DATA st_a_DATA)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u1_a_DATA : INT Data                                                                                             */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2GyroIntGetSend(const ST_XSPI_IVI_GYRO_INT_DATA st_a_DATA)
{
    u1_sp_xspi_ivi_gyro_int_get_data[0] = st_a_DATA.u1_result;
    u1_sp_xspi_ivi_gyro_int_get_data[1] = (U1)0x00U;/*Reserve*/
    u1_sp_xspi_ivi_gyro_int_get_data[2] = (U1)0x00U;/*Reserve*/
    u1_sp_xspi_ivi_gyro_int_get_data[3] = (U1)0x00U;/*Reserve*/
    u1_sp_xspi_ivi_gyro_int_get_data[4] = st_a_DATA.u1_threshold;
    u1_sp_xspi_ivi_gyro_int_get_data[5] = st_a_DATA.u1_gyro_int_x;
    u1_sp_xspi_ivi_gyro_int_get_data[6] = st_a_DATA.u1_gyro_int_y;
    u1_sp_xspi_ivi_gyro_int_get_data[7] = st_a_DATA.u1_gyro_int_z;
    u1_sp_xspi_ivi_gyro_int_get_data[8] = st_a_DATA.u1_gyro_int_active;
    u1_s_xspi_ivi_gyroint_get_response_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub2GyroIntOutSend(const U1 u1_a_DATA)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data                                                                           */
/*  Arguments:      u1_a_DATA : Output Result                                                                                        */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub2GyroIntOutSend(const U1 u1_a_DATA)
{
    u1_sp_xspi_ivi_gyro_int_output_result = u1_a_DATA;
    u1_s_xspi_ivi_gyroint_output_response_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub2PeriBufSet(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data to periodic buff                                                          */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub2PeriBufSet(void)
{
    U4 u4_t_lpcnt;
    U4 u4_t_bufpos;

    /*定期送信*/
    /*SubType*/
    u1_sp_xspi_ivi_gyro_data[0] = (U1)0x05;
    u1_sp_xspi_ivi_gyro_data[1] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[2] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[3] = (U1)0x00; /*Reserve*/
    /*分解能*/
    u1_sp_xspi_ivi_gyro_data[4] = (U1)(u2_s_xspi_ivi_gyro_xyz_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[5] = (U1)((u2_s_xspi_ivi_gyro_xyz_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_data[6] = (U1)(u2_s_xspi_ivi_gyro_temp_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[7] = (U1)((u2_s_xspi_ivi_gyro_temp_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_data[8] = (U1)(u2_s_xspi_ivi_acc_xyz_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[9] = (U1)((u2_s_xspi_ivi_acc_xyz_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_data[10] = (U1)(u2_s_xspi_ivi_acc_temp_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[11] = (U1)((u2_s_xspi_ivi_acc_temp_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    /*中央値*/
    u1_sp_xspi_ivi_gyro_data[12] = (U1)(u1_s_xspi_ivi_gyro_xyz_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[13] = (U1)(u1_s_xspi_ivi_gyro_temp_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[14] = (U1)(u1_s_xspi_ivi_acc_xyz_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_data[15] = (U1)(u1_s_xspi_ivi_acc_temp_center & 0x00FF);
    /*Pulse Rev Data*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_PULSE_REV_BUF_POS] = (U1)0xFFU; /*固定値*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_PULSE_REV_BUF_POS + 1] = (U1)0x00U; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_PULSE_REV_BUF_POS + 2] = (U1)0x00U; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_PULSE_REV_BUF_POS + 3] = (U1)0x00U; /*Reserve*/
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_IVI_TMPDATA; u4_t_lpcnt++) {
        /*ジャイロXYZ軸データ格納*/
        u4_t_bufpos = (U4)XSPI_IVI_GYRO_X_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_x_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_x_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_GYRO_Y_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_y_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_y_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_GYRO_Z_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_z_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_z_data_up_tmp[u4_t_lpcnt];

        /*加速度XYZ軸データ格納*/
        u4_t_bufpos = (U4)XSPI_IVI_ACCL_X_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_x_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_x_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_ACCL_Y_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_y_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_y_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_ACCL_Z_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_z_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_z_data_up_tmp[u4_t_lpcnt];

        /*生涯スピードパルス数格納*/
        u4_t_bufpos = (U4)XSPI_IVI_PULSE_NUM_BUF_POS + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = (U1)(u2_sp_xspi_ivi_pulse_num_tmp[u4_t_lpcnt] & 0x00FF);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = (U1)((u2_sp_xspi_ivi_pulse_num_tmp[u4_t_lpcnt] & 0xFF00)>>XSPI_IVI_SFT_08);
    }
    /*ジャイロ温度データ格納*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_TEMP_BUF_POS] = (U1)u1_s_xspi_ivi_gyro_temp_data_tmp;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_TEMP_BUF_POS + 1U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_TEMP_BUF_POS + 2U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_TEMP_BUF_POS + 3U] = (U1)0x00; /*Reserve*/
    /*加速度温度データ格納*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_TEMP_BUF_POS] = u1_s_xspi_ivi_acc_temp_data_down_tmp;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_TEMP_BUF_POS + 1U] = u1_s_xspi_ivi_acc_temp_data_up_tmp;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_TEMP_BUF_POS + 2U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_TEMP_BUF_POS + 3U] = (U1)0x00; /*Reserve*/
    /*ジャイロセンサ有効情報格納*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_STS_BUF_POS] = u1_s_xspi_ivi_gyro_x_valid_data_tmp & 0x01;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_y_valid_data_tmp & 0x01) << XSPI_IVI_SFT_01);
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_z_valid_data_tmp & 0x01) << XSPI_IVI_SFT_02);
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_GYRO_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_temp_valid_data_tmp & 0x01) << XSPI_IVI_SFT_04);
    /*加速度センサ有効情報格納*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_STS_BUF_POS] = u1_s_xspi_ivi_acc_x_valid_data_tmp & 0x01;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_y_valid_data_tmp & 0x01) << XSPI_IVI_SFT_01);
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_z_valid_data_tmp & 0x01) << XSPI_IVI_SFT_02);
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_ACCL_STS_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_temp_valid_data_tmp & 0x01) << XSPI_IVI_SFT_04);

    /*パルス幅データ格納*/
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_CLKFREQ_BUF_POS] = u1_s_xspi_ivi_clock_freq_tmp;
    u1_sp_xspi_ivi_gyro_data[XSPI_IVI_PULSE_COUNT_BUF_POS] = (U1)u4_s_xspi_ivi_pulse_count_tmp;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_IVI_PULSE_TMPDATA; u4_t_lpcnt++) {
        u4_t_bufpos = XSPI_IVI_PULSE_WIDTH_BUF_POS + (u4_t_lpcnt * (U4)3U);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos]  = (U1)(u4_sp_xspi_ivi_pulse_width_tmp[u4_t_lpcnt] & 0x000000FF);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 1]  = (U1)((u4_sp_xspi_ivi_pulse_width_tmp[u4_t_lpcnt] & 0x0000FF00)>>XSPI_IVI_SFT_08);
        u1_sp_xspi_ivi_gyro_data[u4_t_bufpos + 2]  = (U1)((u4_sp_xspi_ivi_pulse_width_tmp[u4_t_lpcnt] & 0x00FF0000)>>XSPI_IVI_SFT_16);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_XspiIviSub21stBufSet(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame2(Gyro Data) Transmission data to 1st buff                                                               */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_XspiIviSub21stBufSet(void)
{
    U4 u4_t_lpcnt;
    U4 u4_t_bufpos;
    U1 u1_t_rec_sta;
    U1 u1_t_wri_sta;

    u1_s_xspi_ivi_tmp_gyro_ini_cnt++;
    if(u1_s_xspi_ivi_tmp_gyro_ini_cnt < (U1)65U){
        u1_t_rec_sta = (U1)0U;
        u1_t_wri_sta = (U1)u1_s_xspi_ivi_tmp_gyro_ini_cnt;
    } else {
        u1_t_rec_sta = u1_s_xspi_ivi_tmp_gyro_ini_cnt % (U1)64U;
        u1_t_wri_sta = u1_s_xspi_ivi_tmp_gyro_ini_cnt % (U1)64U;
    }

    /*初回送信バッファに格納*/
    /*保持データ数・読み出し/書き込み位置格納*/
    u1_sp_xspi_ivi_gyro_init_data[0] = u1_t_rec_sta;
    u1_sp_xspi_ivi_gyro_init_data[1] = u1_t_wri_sta;
    u1_sp_xspi_ivi_gyro_init_data[2] = u1_s_xspi_ivi_tmp_gyro_ini_cnt;
    u1_sp_xspi_ivi_gyro_init_data[3] = (U1)0x00; /*Reserve*/
    /*分解能*/
    u1_sp_xspi_ivi_gyro_init_data[4] = (U1)(u2_s_xspi_ivi_gyro_xyz_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[5] = (U1)((u2_s_xspi_ivi_gyro_xyz_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_init_data[6] = (U1)(u2_s_xspi_ivi_gyro_temp_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[7] = (U1)((u2_s_xspi_ivi_gyro_temp_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_init_data[8] = (U1)(u2_s_xspi_ivi_acc_xyz_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[9] = (U1)((u2_s_xspi_ivi_acc_xyz_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    u1_sp_xspi_ivi_gyro_init_data[10] = (U1)(u2_s_xspi_ivi_acc_temp_reso & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[11] = (U1)((u2_s_xspi_ivi_acc_temp_reso & 0xFF00)>>XSPI_IVI_SFT_08);
    /*中央値*/
    u1_sp_xspi_ivi_gyro_init_data[12] = (U1)(u1_s_xspi_ivi_gyro_xyz_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[13] = (U1)(u1_s_xspi_ivi_gyro_temp_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[14] = (U1)(u1_s_xspi_ivi_acc_xyz_center & 0x00FF);
    u1_sp_xspi_ivi_gyro_init_data[15] = (U1)(u1_s_xspi_ivi_acc_temp_center & 0x00FF);
    /*Pulse Rev Data*/
    u4_t_bufpos = (U4)XSPI_IVI_PULSE_REV_INIT_BUF_POS + (U4)(u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U1)24U);
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos] = (U1)0xFFU; /*固定値*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1] = (U1)0x00U; /*Reserve*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 2] = (U1)0x00U; /*Reserve*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 3] = (U1)0x00U; /*Reserve*/
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_IVI_TMPDATA; u4_t_lpcnt++) {
        /*ジャイロXYZ軸データ格納*/
        u4_t_bufpos = (U4)XSPI_IVI_GYRO_X_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_x_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_x_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_GYRO_Y_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_y_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_y_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_GYRO_Z_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_gyro_z_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_gyro_z_data_up_tmp[u4_t_lpcnt];

        /*加速度XYZ軸データ格納*/
        u4_t_bufpos = (U4)XSPI_IVI_ACCL_X_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_x_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_x_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_ACCL_Y_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_y_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_y_data_up_tmp[u4_t_lpcnt];

        u4_t_bufpos = (U4)XSPI_IVI_ACCL_Z_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = u1_sp_xspi_ivi_acc_z_data_down_tmp[u4_t_lpcnt];
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = u1_sp_xspi_ivi_acc_z_data_up_tmp[u4_t_lpcnt];

        /*生涯スピードパルス数格納*/
        u4_t_bufpos = (U4)XSPI_IVI_PULSE_NUM_INIT_BUF_POS + (U4)(u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U1)24U) + (u4_t_lpcnt * (U4)2);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos]  = (U1)(u2_sp_xspi_ivi_pulse_num_tmp[u4_t_lpcnt] & 0x00FF);
        u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1]  = (U1)((u2_sp_xspi_ivi_pulse_num_tmp[u4_t_lpcnt] & 0xFF00)>>XSPI_IVI_SFT_08);
    }
    /*ジャイロ温度データ格納*/
    u4_t_bufpos = (U4)XSPI_IVI_GYRO_TEMP_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U);
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos] = (U1)u1_s_xspi_ivi_gyro_temp_data_tmp;
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 2U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 3U] = (U1)0x00; /*Reserve*/
    /*加速度温度データ格納*/
    u4_t_bufpos = (U4)XSPI_IVI_ACCL_TEMP_INIT_BUF_POS + ((U4)u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf * (U2)64U);
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos] = u1_s_xspi_ivi_acc_temp_data_down_tmp;
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 1U] = u1_s_xspi_ivi_acc_temp_data_up_tmp;
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 2U] = (U1)0x00; /*Reserve*/
    u1_sp_xspi_ivi_gyro_init_data[u4_t_bufpos + 3U] = (U1)0x00; /*Reserve*/
    /*ジャイロセンサ有効情報格納*/
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_GYRO_STS_INIT_BUF_POS] = u1_s_xspi_ivi_gyro_x_valid_data_tmp & 0x01;
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_GYRO_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_y_valid_data_tmp & 0x01) << XSPI_IVI_SFT_01);
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_GYRO_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_z_valid_data_tmp & 0x01) << XSPI_IVI_SFT_02);
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_GYRO_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_gyro_temp_valid_data_tmp & 0x01) << XSPI_IVI_SFT_04);
    /*加速度センサ有効情報格納*/
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_ACCL_STS_INIT_BUF_POS] = u1_s_xspi_ivi_acc_x_valid_data_tmp & 0x01;
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_ACCL_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_y_valid_data_tmp & 0x01) << XSPI_IVI_SFT_01);
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_ACCL_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_z_valid_data_tmp & 0x01) << XSPI_IVI_SFT_02);
    u1_sp_xspi_ivi_gyro_init_data[XSPI_IVI_ACCL_STS_INIT_BUF_POS] |= (U1)((u1_s_xspi_ivi_acc_temp_valid_data_tmp & 0x01) << XSPI_IVI_SFT_04);

    u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf++;
    if(u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf > (U1)63U) {
        u1_s_xspi_ivi_tmp_gyro_ini_cnt_buf = (U1)0U;
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
/*  0.0.0    01/27/2024  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
