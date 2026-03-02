/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO TECHNO Corporation                                                                                               */
/*===================================================================================================================================*/
/*  Queue Operation for Sending CAN Message Field in Subframe 4 in XSPI Communication                                                */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_IVI_QUEUE_C_MAJOR                  (0)
#define XSPI_IVI_QUEUE_C_MINOR                  (0)
#define XSPI_IVI_QUEUE_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_queue_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_QUEUE_C_MAJOR != XSPI_IVI_QUEUE_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_QUEUE_C_MINOR != XSPI_IVI_QUEUE_PRIVATE_H_MINOR) || \
     (XSPI_IVI_QUEUE_C_PATCH != XSPI_IVI_QUEUE_PRIVATE_H_PATCH))
#error "x_spi_ivi_queue.c and x_spi_ivi_queue_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MAX_CMS_QUEUE_SIZE                      (338U)
#define MAX_CANDATA_QUEUE_SIZE                  (9984U)
#define MAX_MISCSIZE_QUEUE_SIZE                 (256U)
#define MAX_MISCDATA_QUEUE_SIZE                 (1604U)
#define MAX_DIAGCANDATA_QUEUE_SIZE              (8200U)
#define MAX_DIAGCAN_QUEUE_SIZE                  (7U)
#define MAX_DIAGCANSIZE_QUEUE_SIZE              (MAX_DIAGCAN_QUEUE_SIZE * 2U)
#define MAX_CANCOMMANDSIZE_QUEUE_SIZE           (128U)
#define MAX_CANCOMMANDDATA_QUEUE_SIZE           (512U)

#define XSPI_IVI_SFT_08                         ( 8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1 *    u1p_data;           /* データ格納バッファへのポインタ */
    U2      u2_front;           /* キューの最前部へのインデックス(取り出し用) */
    U2      u2_rear;            /* キューの最後尾へのインデックス(格納用) */
    U2      u2_size;            /* 現在のキューのサイズ */
    U2      u2_capacity;        /* 最大要素数 */
} ST_XSPI_IVI_QUEUE_CONTROL;


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_sp_xspi_ivi_queue_cmsdata[MAX_CMS_QUEUE_SIZE];                     /* CMS向け */
static  U1                                      u1_sp_xspi_ivi_queue_candata[MAX_CANDATA_QUEUE_SIZE];                 /* CANメッセージ向け */
static  U1                                      u1_sp_xspi_ivi_queue_cancommand[MAX_CANCOMMANDDATA_QUEUE_SIZE];       /* CANコマンド向け */
static  U1                                      u1_sp_xspi_ivi_queue_cancommandsize[MAX_CANCOMMANDSIZE_QUEUE_SIZE];   /* CANコマンドサイズ向け */
static  U1                                      u1_sp_xspi_ivi_queue_miscsize[MAX_MISCSIZE_QUEUE_SIZE];               /* MISCデータサイズ向け */
static  U1                                      u1_sp_xspi_ivi_queue_miscdata[MAX_MISCDATA_QUEUE_SIZE];               /* MISCデータ向け */
static  U1                                      u1_sp_xspi_ivi_queue_diagcandata[MAX_DIAGCANDATA_QUEUE_SIZE];         /* DiagCANデータ向け */
static  U1                                      u1_sp_xspi_ivi_queue_diagcandatasize[MAX_DIAGCANSIZE_QUEUE_SIZE];     /* DiagCANデータサイズ向け */
static  U1                                      u1_sp_xspi_ivi_queue_diagcansid[MAX_DIAGCAN_QUEUE_SIZE];              /* DiagCANSIDデータ向け */
static  U1                                      u1_sp_xspi_ivi_queue_diagcanid[MAX_DIAGCAN_QUEUE_SIZE];               /* DiagCANIDデータ向け */
static  U1                                      u1_sp_xspi_ivi_queue_diagcannum[MAX_DIAGCANSIZE_QUEUE_SIZE];          /* FlameNumデータ向け */

ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_CMS;                               /* CMS向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_CANDATA;                           /* CANメッセージ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_CANCOMMAND;                        /* CANコマンド向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE;                     /* CANコマンドサイズ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_MISCDATA;                          /* MISC向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_MISCDATASIZE;                      /* MISCデータサイズ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_DIAGCANDATA;                       /* DiagCAN向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE;                   /* DiagCANデータサイズ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_DIAGCANSID;                        /* DiagCANSIDデータ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_DIAGCANID;                       /* DiagCANIDデータ向け */
ST_XSPI_IVI_QUEUE_CONTROL                       st_sp_XSPI_IVI_QUEUE_DIAGCANNUM;                       /* DiagCANFlameNumデータ向け */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_XspiIviQueueBufferInit(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_data, const U2 u2_a_CAPACITY);
static U2       u2_s_XspiIviQueueFreeSpace(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue);
static U1       u1_s_XspiIviQueueEnqueue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, const U1 * u1_ap_VALUES, const U2 u2_a_NUM_VALUES);
static U1       u1_s_XspiIviQueueDequeue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_output, const U2 u2_a_NUM_VALUES);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化用IF                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueInit(void)
{
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_cmsdata[0], (U1)0U, (U4)MAX_CMS_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_candata[0], (U1)0U, (U4)MAX_CANDATA_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_miscsize[0], (U1)0U, (U4)MAX_MISCSIZE_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_miscdata[0], (U1)0U, (U4)MAX_MISCDATA_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_cancommand[0], (U1)0U, (U4)MAX_CANCOMMANDDATA_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_cancommandsize[0], (U1)0U, (U4)MAX_CANCOMMANDSIZE_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcandata[0], (U1)0U, (U4)MAX_DIAGCANDATA_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcandatasize[0], (U1)0U, (U4)MAX_DIAGCANSIZE_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcansid[0], (U1)0U, (U4)MAX_DIAGCAN_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcanid[0], (U1)0U, (U4)MAX_DIAGCAN_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcannum[0], (U1)0U, (U4)MAX_DIAGCANSIZE_QUEUE_SIZE);

    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_CMS, u1_sp_xspi_ivi_queue_cmsdata, (U2)MAX_CMS_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_CANDATA, u1_sp_xspi_ivi_queue_candata, (U2)MAX_CANDATA_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_MISCDATASIZE, u1_sp_xspi_ivi_queue_miscsize, (U2)MAX_MISCSIZE_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_MISCDATA, u1_sp_xspi_ivi_queue_miscdata, (U2)MAX_MISCDATA_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_CANCOMMAND, u1_sp_xspi_ivi_queue_cancommand, (U2)MAX_CANCOMMANDDATA_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE, u1_sp_xspi_ivi_queue_cancommandsize, (U2)MAX_CANCOMMANDSIZE_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATA, u1_sp_xspi_ivi_queue_diagcandata, (U2)MAX_DIAGCANDATA_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE, u1_sp_xspi_ivi_queue_diagcandatasize, (U2)MAX_DIAGCANSIZE_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANSID, u1_sp_xspi_ivi_queue_diagcansid, (U2)MAX_DIAGCAN_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANID, u1_sp_xspi_ivi_queue_diagcanid, (U2)MAX_DIAGCAN_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANNUM, u1_sp_xspi_ivi_queue_diagcannum, (U2)MAX_DIAGCANSIZE_QUEUE_SIZE);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueSoCResetInit(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SoCリセット初期化用IF                                                                                             */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueSoCResetInit(void)
{
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcandata[0], (U1)0U, (U4)MAX_DIAGCANDATA_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcandatasize[0], (U1)0U, (U4)MAX_DIAGCANSIZE_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcansid[0], (U1)0U, (U4)MAX_DIAGCAN_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcanid[0], (U1)0U, (U4)MAX_DIAGCAN_QUEUE_SIZE);
    vd_g_MemfillU1(&u1_sp_xspi_ivi_queue_diagcannum[0], (U1)0U, (U4)MAX_DIAGCANSIZE_QUEUE_SIZE);

    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATA, u1_sp_xspi_ivi_queue_diagcandata, (U2)MAX_DIAGCANDATA_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE, u1_sp_xspi_ivi_queue_diagcandatasize, (U2)MAX_DIAGCANSIZE_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANSID, u1_sp_xspi_ivi_queue_diagcansid, (U2)MAX_DIAGCAN_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANID, u1_sp_xspi_ivi_queue_diagcanid, (U2)MAX_DIAGCAN_QUEUE_SIZE);
    vd_s_XspiIviQueueBufferInit(&st_sp_XSPI_IVI_QUEUE_DIAGCANNUM, u1_sp_xspi_ivi_queue_diagcannum, (U2)MAX_DIAGCANSIZE_QUEUE_SIZE);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriCms(U1 * u1_ap_value)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CMS書込み処理                                                                                                     */
/*  Arguments:      u1_a_value  : 書込み対象のCMS                                                                                     */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriCms(U1 * u1_ap_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_CMS_NUM_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_CMS, u1_ap_value, u2_s_XSPI_IVI_QUEUE_CMS_NUM_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriCandata(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANデータ書込み処理                                                                                                */
/*  Arguments:      u1_a_value      : 書込み対象のCANデータ                                                                            */
/*                  u2_a_NUM_VALUES : 書込みサイズ                                                                                    */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriCandata(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_CANDATA, u1_ap_value, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriCanCommandSize(U1 * u1_ap_buf)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANコマンドサイズ書き込み処理                                                                                      */
/*  Arguments:      u1_ap_buf   : CANコマンドサイズ読み出し用のバッファ                                                                 */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriCanCommandSize(U1 * u1_ap_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_CANCOMMAND_SIZE_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE, u1_ap_value, u2_s_XSPI_IVI_QUEUE_CANCOMMAND_SIZE_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriCanCommandData(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANコマンド書き込み処理                                                                                           */
/*  Arguments:      u1_ap_buf       : CANコマンド読み出し用のバッファ                                                                  */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                  */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriCanCommandData(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_CANCOMMAND, u1_ap_value, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriMiscSize(U1 u1_ap_value)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISC Size書込み処理                                                                                               */
/*  Arguments:      u1_a_value  : 書込み対象のSize                                                                                    */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriMiscSize(U1 u1_a_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_MISC_NUM_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_MISCDATASIZE, &u1_a_value, u2_s_XSPI_IVI_QUEUE_MISC_NUM_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriMiscdata(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータ書込み処理                                                                                               */
/*  Arguments:      u1_a_value      : 書込み対象のMISCデータ                                                                           */
/*                  u2_a_NUM_VALUES : 書込みサイズ                                                                                    */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriMiscdata(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_MISCDATA, u1_ap_value, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriDiagCANdata(U1 * u1_ap_value, const U2 u2_a_NUM_VALUES)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ書込み処理                                                                                            */
/*  Arguments:      u1_a_value      : 書込み対象のDiagCANデータ                                                                        */
/*                  u2_a_NUM_VALUES : 書込みサイズ                                                                                    */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriDiagCANdata(const U1 * u1_ap_VALUE, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATA, u1_ap_VALUE, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriDiagCANdataSize(U2  u2_a_value)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ書込み処理                                                                                            */
/*  Arguments:      u1_a_value      : 書込み対象のDiagCANデータサイズ                                                                  */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriDiagCANdataSize(U2  u2_a_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_SIZE_NUM_VALUE   = (U2)2U;
    U1  u1_t_value[2];

    u1_t_value[0] = (U1)((u2_a_value & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
    u1_t_value[1] = (U1)(u2_a_value & (U2)0x00FFU);
    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE, &u1_t_value[0], u2_s_XSPI_IVI_QUEUE_DIAGCAN_SIZE_NUM_VALUE);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriDiagCANdataSID(U1  u1_a_value)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ書込み処理                                                                                            */
/*  Arguments:      u1_a_value      : 書込み対象のDiagCANSIDデータ                                                                     */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriDiagCANdataSID(U1  u1_a_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_SID_NUM_VALUE   = (U2)1U;

    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_DIAGCANSID, &u1_a_value, u2_s_XSPI_IVI_QUEUE_DIAGCAN_SID_NUM_VALUE);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriDiagCANdataID(U1  u1_a_value)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ書込み処理                                                                                            */
/*  Arguments:      u1_a_value      : 書込み対象のDiagCANIDデータ                                                                     */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriDiagCANdataID(U1  u1_a_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_ID_NUM_VALUE   = (U2)1U;

    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_DIAGCANID, &u1_a_value, u2_s_XSPI_IVI_QUEUE_DIAGCAN_ID_NUM_VALUE);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueWriDiagCANdataNum(U1  u1_a_value)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ書込み処理                                                                                            */
/*  Arguments:      u1_a_value      : 書込み対象のDiagCANFlameNumデータ                                                                */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueWriDiagCANdataNum(U2  u2_a_value)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_FLAMENUM_NUM_VALUE   = (U2)2U;
    
    U1  u1_t_value[2];

    u1_t_value[0] = (U1)((u2_a_value & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
    u1_t_value[1] = (U1)(u2_a_value & (U2)0x00FFU);

    (void)u1_s_XspiIviQueueEnqueue(&st_sp_XSPI_IVI_QUEUE_DIAGCANNUM, &u1_t_value[0], u2_s_XSPI_IVI_QUEUE_DIAGCAN_FLAMENUM_NUM_VALUE);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueGetCms(U1 * u1_ap_buf)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CMS読出し,格納処理                                                                                                */
/*  Arguments:      u1_ap_buf   : CMS読み出し用のバッファ                                                                              */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueGetCms(U1 * u1_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_CMS_NUM_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_CMS, u1_ap_buf, u2_s_XSPI_IVI_QUEUE_CMS_NUM_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueGetCandata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANデータ読出し,格納処理                                                                                           */
/*  Arguments:      u1_ap_buf       : CANデータ読み出し用のバッファ                                                                    */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                  */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueGetCandata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_CANDATA, u1_ap_buf, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueGetCanCommandSize(U1 * u1_ap_buf)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANコマンドサイズ読出し,格納処理                                                                                   */
/*  Arguments:      u1_ap_buf   : CANコマンドサイズ読み出し用のバッファ                                                                 */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueGetCanCommandSize(U1 * u1_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_CANCOMMAND_SIZE_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE, u1_ap_buf, u2_s_XSPI_IVI_QUEUE_CANCOMMAND_SIZE_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueGetCanCommandData(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANコマンド読出し,格納処理                                                                                         */
/*  Arguments:      u1_ap_buf       : CANコマンド読み出し用のバッファ                                                                  */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                  */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueGetCanCommandData(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_CANCOMMAND, u1_ap_buf, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* U1            u1_g_XspiIviQueueGetCanCommandSizeRef(void)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CANコマンドデータサイズ参照                                                                                        */
/*  Arguments:      -                                                                                                               */
/*  Return:         u1_t_return     : 次のCANコマンドサイズ                                                                           */
/*===================================================================================================================================*/
U1            u1_g_XspiIviQueueGetCanCommandSizeRef(void)
{
    return st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE.u1p_data[st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE.u2_front];
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueGetMiscDataSize(U1 * u1_ap_buf)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータサイズ読出し,格納処理                                                                                    */
/*  Arguments:      u1_ap_buf   : MISCデータサイズ読み出し用のバッファ                                                                  */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueGetMiscDataSize(U1 * u1_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_MISC_DATA_SIZE_VALUE   = (U2)1U;
    U1          u1_t_return;

    u1_t_return = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_MISCDATASIZE, u1_ap_buf, u2_s_XSPI_IVI_QUEUE_MISC_DATA_SIZE_VALUE);

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueGetMiscdata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータ読出し,格納処理                                                                                           */
/*  Arguments:      u1_ap_buf       : MISCデータ読み出し用のバッファ                                                                    */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                  */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueGetMiscdata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)
{
    (void)u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_MISCDATA, u1_ap_buf, u2_a_NUM_VALUES);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueGetDiagCANdata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ読出し,格納処理                                                                                       */
/*  Arguments:      u1_ap_buf       : DiagCANデータ読み出し用のバッファ                                                                 */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                   */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
U1            u1_g_XspiIviQueueGetDiagCANdata(U1 * u1_ap_buf, const U2 u2_a_NUM_VALUES)
{
    U1  u1_t_rslt;

    u1_t_rslt = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATA, u1_ap_buf, u2_a_NUM_VALUES);

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/* void            vd_g_XspiIviQueueGetDiagCANdataSize(U2 * u2_ap_buf)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータ読出し,格納処理                                                                                       */
/*  Arguments:      u2_ap_buf       : DiagCANデータ読み出し用のバッファ                                                                 */
/*                  u2_a_NUM_VALUES : 読み出しサイズ                                                                                   */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
void            vd_g_XspiIviQueueGetDiagCANdataSize(U2 * u2_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_DATA_SIZE_VALUE   = (U2)2U;
    U1  u1_t_value[2];
    U1  u1_t_rslt;

    u1_t_rslt = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE, &u1_t_value[0], u2_s_XSPI_IVI_QUEUE_DIAGCAN_DATA_SIZE_VALUE);

    if(u1_t_rslt == (U1)TRUE) {
        *u2_ap_buf = (U2)((u1_t_value[0] << XSPI_IVI_SFT_08) | u1_t_value[1]);
    }
}

/*===================================================================================================================================*/
/* U1                u1_g_XspiIviQueueGetDiagCANDataSID(U1 * u1_ap_buf)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータサイズ読出し,格納処理                                                                                    */
/*  Arguments:      u1_ap_buf   : MISCデータサイズ読み出し用のバッファ                                                                  */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueGetDiagCANDataSID(U1 * u1_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_SID_SIZE_VALUE   = (U2)1U;
    U1  u1_t_rslt;

    u1_t_rslt = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_DIAGCANSID, u1_ap_buf, u2_s_XSPI_IVI_QUEUE_DIAGCAN_SID_SIZE_VALUE);
    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueGetDiagCANDataID(U1 * u1_ap_buf)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータサイズ読出し,格納処理                                                                                    */
/*  Arguments:      u1_ap_buf   : MISCデータサイズ読み出し用のバッファ                                                                  */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
void              vd_g_XspiIviQueueGetDiagCANDataID(U1 * u1_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_ID_SIZE_VALUE   = (U2)1U;

    (void)u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_DIAGCANID, u1_ap_buf, u2_s_XSPI_IVI_QUEUE_DIAGCAN_ID_SIZE_VALUE);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueGetDiagCANDataNum(U1 * u1_ap_buf)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータサイズ読出し,格納処理                                                                                    */
/*  Arguments:      u1_ap_buf   : MISCデータサイズ読み出し用のバッファ                                                                  */
/*  Return:         u1_t_return : 成功(TRUE)/失敗(FALSE)                                                                              */
/*===================================================================================================================================*/
void              vd_g_XspiIviQueueGetDiagCANDataNum(U2 * u2_ap_buf)
{
    static const U2 u2_s_XSPI_IVI_QUEUE_DIAGCAN_FLAMENUM_SIZE_VALUE   = (U2)2U;
    U1  u1_t_value[2];
    U1  u1_t_rslt;

    u1_t_rslt = u1_s_XspiIviQueueDequeue(&st_sp_XSPI_IVI_QUEUE_DIAGCANNUM, &u1_t_value[0], u2_s_XSPI_IVI_QUEUE_DIAGCAN_FLAMENUM_SIZE_VALUE);

    if(u1_t_rslt == (U1)TRUE) {
        *u2_ap_buf = (U2)((u1_t_value[0] << XSPI_IVI_SFT_08) | u1_t_value[1]);
    }
}

/*===================================================================================================================================*/
/* U1            u1_g_XspiIviQueueGetMiscDataSizeRef(void)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータサイズ参照                                                                                              */
/*  Arguments:      -                                                                                                               */
/*  Return:         u1_t_return     : 次のMISCデータサイズ                                                                           */
/*===================================================================================================================================*/
U1            u1_g_XspiIviQueueGetMiscDataSizeRef(void)
{
    return st_sp_XSPI_IVI_QUEUE_MISCDATASIZE.u1p_data[st_sp_XSPI_IVI_QUEUE_MISCDATASIZE.u2_front];
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriChk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    CMS,CANデータバッファへの書き込み可否通知                                                                           */
/*  Arguments:      U1 u1_a_NUM    : 書き込みデータサイズ                                                                              */
/*  Return:         U1 u1_t_return : 可(TRUE)/否(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriChk(const U1 u1_a_NUM)
{
    U1          u1_t_return;
    U2          u2_t_cms_num;
    U2          u2_t_can_num;

    u1_t_return = (U1)FALSE;

    u2_t_cms_num = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_CMS);
    u2_t_can_num = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_CANDATA);

    /* CMSバッファに1つ以上空きがあり、かつCANデータバッファに書込みデータサイズより大きい空きがあるかチェック */
    if ((u2_t_cms_num > (U2)0U) && (u2_t_can_num > (U2)u1_a_NUM)) {
        u1_t_return = (U1)TRUE;
    }
    else {
        /* あき容量不足で書き込み不可 */
        /* do nothing */
    }

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriChkCanCommand(const U2 u2_a_NUM)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータバッファへの書き込み可否通知                                                                              */
/*  Arguments:      U1 u1_a_NUM    : 書き込みデータサイズ                                                                              */
/*  Return:         U1 u1_t_return : 可(TRUE)/否(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriChkCanCommand(const U1 u1_a_NUM)
{
    U1          u1_t_return;
    U2          u2_t_cancommand_num;
    U2          u2_t_cancommandsize_num;

    u1_t_return = (U1)FALSE;

    u2_t_cancommand_num     = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_CANCOMMAND);
    u2_t_cancommandsize_num = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_CANCOMMANDSIZE);

    /* CMSバッファに1つ以上空きがあり、かつCANデータバッファに書込みデータサイズより大きい空きがあるかチェック */
    if ((u2_t_cancommandsize_num > (U2)0U) && (u2_t_cancommand_num > (U2)u1_a_NUM)) {
        u1_t_return = (U1)TRUE;
    }
    else {
        /* あき容量不足で書き込み不可 */
        /* do nothing */
    }

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriChkMISC(const U2 u2_a_NUM)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    MISCデータバッファへの書き込み可否通知                                                                              */
/*  Arguments:      U1 u1_a_NUM    : 書き込みデータサイズ                                                                              */
/*  Return:         U1 u1_t_return : 可(TRUE)/否(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriChkMISC(const U2 u2_a_NUM)
{
    U1          u1_t_return;
    U2          u2_t_misc_num;
    U2          u2_t_miscsize_num;

    u1_t_return = (U1)FALSE;

    u2_t_misc_num     = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_MISCDATA);
    u2_t_miscsize_num = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_MISCDATASIZE);

    /* CMSバッファに1つ以上空きがあり、かつCANデータバッファに書込みデータサイズより大きい空きがあるかチェック */
    if ((u2_t_miscsize_num > (U2)0U) && (u2_t_misc_num > u2_a_NUM)) {
        u1_t_return = (U1)TRUE;
    }
    else {
        /* あき容量不足で書き込み不可 */
        /* do nothing */
    }

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* U1              u1_g_XspiIviQueueWriChkDiagCAN(const U2 u2_a_NUM)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    DiagCANデータバッファへの書き込み可否通知                                                                           */
/*  Arguments:      U1 u1_a_NUM    : 書き込みデータサイズ                                                                              */
/*  Return:         U1 u1_t_return : 可(TRUE)/否(FALSE)                                                                              */
/*===================================================================================================================================*/
U1              u1_g_XspiIviQueueWriChkDiagCAN(const U2 u2_a_NUM)
{
    U1          u1_t_return;
    U2          u2_t_data_num;
    U2          u2_t_size_num;
    U2          u2_t_sid_num;
    U2          u2_t_id_num;
    U2          u2_t_flamenum_num;

    u1_t_return = (U1)FALSE;

    u2_t_data_num     = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATA);
    u2_t_size_num     = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_DIAGCANDATASIZE);
    u2_t_sid_num      = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_DIAGCANSID);
    u2_t_id_num       = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_DIAGCANID);
    u2_t_flamenum_num = u2_s_XspiIviQueueFreeSpace(&st_sp_XSPI_IVI_QUEUE_DIAGCANNUM);

    /* CMSバッファに1つ以上空きがあり、かつCANデータバッファに書込みデータサイズより大きい空きがあるかチェック */
    if ((u2_t_size_num > (U2)0U) && 
        (u2_t_sid_num  > (U2)0U) &&  
        (u2_t_id_num   > (U2)0U) &&  
        (u2_t_flamenum_num  > (U2)0U) && 
        (u2_t_data_num > u2_a_NUM)) {
        u1_t_return = (U1)TRUE;
    }
    else {
        /* あき容量不足で書き込み不可 */
        /* do nothing */
    }

    return (u1_t_return);
}

/*===================================================================================================================================*/
/* static void   vd_s_XspiIviQueueBufferInit(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_data, const U2 u2_a_CAPACITY)       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    キュー初期化                                                                                                      */
/*  Arguments:      st_ap_queue   : 初期化対象の構造体へのポインタ                                                                      */
/*                  u1_ap_data    : キューへのポインタ                                                                                 */
/*                  u2_a_CAPACITY : 最大容量                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void   vd_s_XspiIviQueueBufferInit(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_data, const U2 u2_a_CAPACITY)
{
    st_ap_queue->u1p_data = u1_ap_data;
    st_ap_queue->u2_front = 0;
    st_ap_queue->u2_rear = 0;
    st_ap_queue->u2_size = 0;
    st_ap_queue->u2_capacity = u2_a_CAPACITY;
}
  
/*===================================================================================================================================*/
/* static U2              u2_s_XspiIviQueueFreeSpace(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    バッファの空き容量を返す                                                                                           */
/*  Arguments:      st_ap_queue : 確認対象のキューへのポインタ                                                                         */
/*  Return:         u2_t_return : 空き容量                                                                                           */
/*===================================================================================================================================*/
static U2              u2_s_XspiIviQueueFreeSpace(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue)
{  
    U2          u2_t_return;

    if (st_ap_queue->u2_capacity > st_ap_queue->u2_size) {
        u2_t_return =   st_ap_queue->u2_capacity - st_ap_queue->u2_size;
    }
    else {
        u2_t_return =   (U2)0U;
    }

    return (u2_t_return);  
} 

/*===================================================================================================================================*/
/* static U1    u1_s_XspiIviQueueEnqueue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, const U1 * u1_ap_VALUES, const U2 u2_a_NUM_VALUES) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    キューへのデータ追加処理                                                                                           */
/*  Arguments:      st_ap_queue     : データ追加対象の構造体へのポインタ                                                                */
/*                  u1_ap_VALUES    : 追加データ配列へのポインタ                                                                       */
/*                  u2_a_NUM_VALUES : データ数                                                                                        */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
static U1    u1_s_XspiIviQueueEnqueue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, const U1 * u1_ap_VALUES, const U2 u2_a_NUM_VALUES)
{
    U1          u1_t_return;
    U2          u2_t_wrinum;                /* データ格納数 */
    U2          u2_t_space_free;            /* キューの空き領域 */
    U2          u2_t_space_endpoint;        /* 格納位置からキュー終端までのバッファ数 */

    u2_t_space_free = u2_s_XspiIviQueueFreeSpace(st_ap_queue);

    if (u2_a_NUM_VALUES <= u2_t_space_free) {                                            /* 格納要求データ量 < 空きバッファ量 */
        u2_t_space_endpoint = st_ap_queue->u2_capacity - st_ap_queue->u2_rear;
        
        /* データがリングバッファの終点を跨がない場合 */
        if(u2_a_NUM_VALUES <= u2_t_space_endpoint) {
            u2_t_wrinum = u2_a_NUM_VALUES;
            vd_g_MemcpyU1(&st_ap_queue->u1p_data[st_ap_queue->u2_rear], u1_ap_VALUES, u2_t_wrinum);             /* データ格納 */
        }
        else {  /* 終点を跨ぐ場合 */
            u2_t_wrinum = u2_t_space_endpoint;
            vd_g_MemcpyU1(&st_ap_queue->u1p_data[st_ap_queue->u2_rear], u1_ap_VALUES, u2_t_wrinum);             /* データ格納 */
            u2_t_wrinum = u2_a_NUM_VALUES - u2_t_space_endpoint;
            vd_g_MemcpyU1(&st_ap_queue->u1p_data[0], &u1_ap_VALUES[u2_t_space_endpoint], u2_t_wrinum);          /* データ格納 */
        }

        st_ap_queue->u2_rear = (st_ap_queue->u2_rear + u2_a_NUM_VALUES) % st_ap_queue->u2_capacity;             /* 次格納先へとrearポインタ移動 */
        st_ap_queue->u2_size = st_ap_queue->u2_size + u2_a_NUM_VALUES;                                          /* バッファのサイズ更新 */
        u1_t_return = (U1)TRUE;
    }
    else {
        u1_t_return = (U1)FALSE;
    }

    return (u1_t_return);
}  
  
/*===================================================================================================================================*/
/* static U1        u1_s_XspiIviQueueDequeue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_output, const U2 u2_a_NUM_VALUES)   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    キューからのデータ取り出し処理                                                                                      */
/*  Arguments:      st_ap_queue     : データ取り出し対象の構造体へのポインタ                                                             */
/*                  u1_ap_output    : 取り出しデータ格納配列へのポインタ                                                                */
/*                  u2_a_NUM_VALUES : データ数                                                                                        */
/*  Return:         u1_t_return     : 成功(TRUE)/失敗(FALSE)                                                                          */
/*===================================================================================================================================*/
static U1        u1_s_XspiIviQueueDequeue(ST_XSPI_IVI_QUEUE_CONTROL * st_ap_queue, U1 * u1_ap_output, const U2 u2_a_NUM_VALUES)
{  
    U1          u1_t_return;
    U2          u2_t_reanum;                /* データ格納数 */
    U2          u2_t_space_endpoint;        /* 格納位置からキュー終端までのバッファ数 */

    if (st_ap_queue->u2_size >= u2_a_NUM_VALUES) {                                                       /* 保持データサイズ > 読み出し要求データ量 */
        u2_t_space_endpoint = st_ap_queue->u2_capacity - st_ap_queue->u2_front;
        
        /* データがリングバッファの終点を跨がない場合 */
        if(u2_a_NUM_VALUES <= u2_t_space_endpoint) {
            u2_t_reanum = u2_a_NUM_VALUES;
            vd_g_MemcpyU1(u1_ap_output, &st_ap_queue->u1p_data[st_ap_queue->u2_front], u2_t_reanum);            /* データ格納 */
        }
        else {  /* 終点を跨ぐ場合 */
            u2_t_reanum = u2_t_space_endpoint;
            vd_g_MemcpyU1(u1_ap_output, &st_ap_queue->u1p_data[st_ap_queue->u2_front], u2_t_reanum);            /* データ格納 */
            u2_t_reanum = u2_a_NUM_VALUES - u2_t_space_endpoint;
            vd_g_MemcpyU1(&u1_ap_output[u2_t_space_endpoint], &st_ap_queue->u1p_data[0], u2_t_reanum);            /* データ格納 */
        }

        st_ap_queue->u2_front = (st_ap_queue->u2_front + u2_a_NUM_VALUES) % st_ap_queue->u2_capacity;   /* 次取り出し先へとfrontポインタ移動 */
        st_ap_queue->u2_size = st_ap_queue->u2_size - u2_a_NUM_VALUES;                                  /* バッファのサイズ更新 */
        u1_t_return = (U1)TRUE;    /* 読み出し成功 */
    }
    else {
        u1_t_return = (U1)FALSE;    /* 読み出し失敗 */
    }

    return (u1_t_return);
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
