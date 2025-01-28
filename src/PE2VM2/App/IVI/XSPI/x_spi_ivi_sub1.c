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
#define XSPI_IVI_SUB1_C_MAJOR                   (0)
#define XSPI_IVI_SUB1_C_MINOR                   (0)
#define XSPI_IVI_SUB1_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include    "x_spi_ivi_sub1_private.h"
#include    "x_spi_ivi_sub1_control.h"
#include    "x_spi_ivi_sub1_power.h"
#include    "x_spi_ivi_sub1_system.h"
#include    "x_spi_ivi_sub1_camera.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_IVI_SUB1_C_MAJOR != XSPI_IVI_SUB1_H_MAJOR) || \
     (XSPI_IVI_SUB1_C_MINOR != XSPI_IVI_SUB1_H_MINOR) || \
     (XSPI_IVI_SUB1_C_PATCH != XSPI_IVI_SUB1_H_PATCH))
#error "x_spi_ivi_sub1.c and x_spi_ivi_sub1.h : source and header files are inconsistent!"
#endif
#if ((XSPI_IVI_SUB1_C_MAJOR != XSPI_IVI_SUB1_PRIVATE_H_MAJOR) || \
     (XSPI_IVI_SUB1_C_MINOR != XSPI_IVI_SUB1_PRIVATE_H_MINOR) || \
     (XSPI_IVI_SUB1_C_PATCH != XSPI_IVI_SUB1_PRIVATE_H_PATCH))
#error "x_spi_ivi_sub1.c and x_spi_ivi_sub1_private.h : source and header files are inconsistent!"
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


#define XSPI_IVI_MISC_ID                    (0x4D495343U)
#define XSPI_IVI_MISC_CONTROL               (0x01U)
#define XSPI_IVI_MISC_POWER                 (0x21U)
#define XSPI_IVI_MISC_SYSTEM                (0x22U)
#define XSPI_IVI_MISC_DIAG                  (0x23U)
#define XSPI_IVI_MISC_VERSION               (0x24U)
#define XSPI_IVI_MISC_SECURITY              (0x25U)
#define XSPI_IVI_MISC_CAMERA                (0x34U)
#define XSPI_IVI_MISC_CLOCK                 (0x35U)
#define XSPI_IVI_MISC_DISPLAY               (0x36U)
#define XSPI_IVI_MISC_REPRO                 (0x38U)
#define XSPI_IVI_MISC_HDMI                  (0x39U)

#define XSPI_IVI_MISC_DATA_SIZE_MAX         (256U)
#define XSPI_IVI_MISC_DATA_SIZE_OFFSET      (1U)

#define XSPI_IVI_MISC_SIZE                  (XSPI_IVI_MISC_DATA_SIZE_MAX + XSPI_IVI_HEADER)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void          vd_s_XspiIviSub1SendCommandPeriCall(void);
static void          vd_s_XspiIviSub1MiscAna(const U1 * u1_ap_SUB1_ADD, const U2 u2_a_DTLEN);
static U1            u1_s_XspiIviSub1SendMISCData(U2 * u2_ap_data_len, U1 * u1_ap_xspi_add);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1Init(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    初期化処理                                                                                                        */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1Init(void)
{
    vd_g_XspiIviSub1PowerInit();
    vd_g_XspiIviSub1SystemInit();
    vd_g_XspiIviSub1CameraInit();
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1Ana(const U1 * u1_ap_XSPI_ADD)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_XSPI_ADD : SubFlame1 Start Buffer                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1Ana(const U1 * u1_ap_XSPI_ADD)
{
    //U2          u2_t_frame_counter;     /* Sub Frame Counter */
    //U2          u2_t_frame_num;         /* Sub Frame num */
    U2          u2_t_dt_len;            /* data length */
    //U1          u1_t_dt_type;           /* Transmit or Recieve */

    //u2_t_frame_counter  = (U2)((u1_ap_XSPI_ADD[0] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[1]);
    //u2_t_frame_num      = (U2)((u1_ap_XSPI_ADD[2] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[3]);
    u2_t_dt_len         = (U2)((u1_ap_XSPI_ADD[4] << XSPI_IVI_SFT_08) | u1_ap_XSPI_ADD[5]);
    //u1_t_dt_type        = u1_ap_XSPI_ADD[6];

    vd_s_XspiIviSub1MiscAna(&u1_ap_XSPI_ADD[8], u2_t_dt_len);

}

/*===================================================================================================================================*/
/*  static void            vd_s_XspiIviSub1MiscAna(const U1 * u1_ap_SUB1_ADD, const U2 u2_a_DTLEN)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC) Data Analysis                                                                                    */
/*  Arguments:      u1_ap_SUB1_ADD : SubFlame1 MISC Data Start pos                                                                   */
/*                  u2_a_DTLEN     : Data Length                                                                                     */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1MiscAna(const U1 * u1_ap_SUB1_ADD, const U2 u2_a_DTLEN)
{
    U4          u4_t_misc_id;
    U2          u2_t_datatype;   /*Command Data Type*/
    U2          u2_t_datasize;   /*Command Data Size*/
    U2          u2_t_data_id;    /*buffer id*/

    u2_t_data_id = (U2)0U;

    u4_t_misc_id = (U4)((u1_ap_SUB1_ADD[u2_t_data_id] << XSPI_IVI_SFT_24) | (u1_ap_SUB1_ADD[u2_t_data_id + 1U] << XSPI_IVI_SFT_16) | (u1_ap_SUB1_ADD[u2_t_data_id + 2U] << XSPI_IVI_SFT_08) | u1_ap_SUB1_ADD[u2_t_data_id + 3U]);

    while(u4_t_misc_id == (U4)XSPI_IVI_MISC_ID){
        u2_t_datatype = (U2)((u1_ap_SUB1_ADD[u2_t_data_id + 4U] << XSPI_IVI_SFT_08) | u1_ap_SUB1_ADD[u2_t_data_id + 5U]);
        u2_t_datasize = (U2)((u1_ap_SUB1_ADD[u2_t_data_id + 6U] << XSPI_IVI_SFT_08) | u1_ap_SUB1_ADD[u2_t_data_id + 7U]);
        /*各コマンド関数コールする箇所*/
        switch(u2_t_datatype){
            case XSPI_IVI_MISC_CONTROL:
                vd_g_XspiIviSub1ControlAna(&u1_ap_SUB1_ADD[u2_t_data_id + 8U],u2_t_datasize);
            break;
            case XSPI_IVI_MISC_POWER:
                vd_g_XspiIviSub1PowerAna(&u1_ap_SUB1_ADD[u2_t_data_id + 8U],u2_t_datasize);
            break;
            case XSPI_IVI_MISC_SYSTEM:
                vd_g_XspiIviSub1SystemAna(&u1_ap_SUB1_ADD[u2_t_data_id + 8U],u2_t_datasize);
            break;
            case XSPI_IVI_MISC_DIAG:
            /*シス検 skip*/
            break;
            case XSPI_IVI_MISC_VERSION:
            break;
            case XSPI_IVI_MISC_SECURITY:
            /*シス検 skip*/
            break;
            case XSPI_IVI_MISC_CAMERA:
                vd_g_XspiIviSub1CameraAna(&u1_ap_SUB1_ADD[u2_t_data_id + 8U],u2_t_datasize);
            break;
            case XSPI_IVI_MISC_CLOCK:
            /*シス検 skip*/
            break;
            case XSPI_IVI_MISC_DISPLAY:
            /*SOCで完結 skip*/
            break;
            case XSPI_IVI_MISC_REPRO:
            /*シス検 skip*/
            break;
            case XSPI_IVI_MISC_HDMI:
            /*シス検 skip*/
            break;
            default:
            break;
        }

        u2_t_data_id = u2_t_data_id + u2_t_datasize + (U2)XSPI_IVI_HEADER;
        /*識別子読み出し*/
        u4_t_misc_id = (U4)((u1_ap_SUB1_ADD[u2_t_data_id] << XSPI_IVI_SFT_24) | (u1_ap_SUB1_ADD[u2_t_data_id + 1U] << XSPI_IVI_SFT_16) | (u1_ap_SUB1_ADD[u2_t_data_id + 2U] << XSPI_IVI_SFT_08) | u1_ap_SUB1_ADD[u2_t_data_id + 3U]);
    }
}

/*===================================================================================================================================*/
/*  void            vd_g_XspiIviSub1Send(U1 * u1_ap_xspi_add)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC Data) Transmission data                                                                           */
/*  Arguments:      u1_ap_xspi_add : SubFlame2 start address                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1Send(U1 * u1_ap_xspi_add)
{
    U2          u2_t_data_size;
    U1          u1_t_data_num;

    u2_t_data_size = (U2)0U;

    /*定期送信用の関数呼び出し*/
    vd_s_XspiIviSub1SendCommandPeriCall();

    vd_g_MemfillU1(&u1_ap_xspi_add[0], (U1)0U, (U4)XSPI_IVI_MISC_SIZE);

    u1_t_data_num = u1_s_XspiIviSub1SendMISCData(&u2_t_data_size, u1_ap_xspi_add);
    u1_ap_xspi_add[0] = (U1)0x00U;
    u1_ap_xspi_add[1] = (U1)0x01U;
    u1_ap_xspi_add[2] = (U1)0x00U;
    u1_ap_xspi_add[3] = (U1)0x01U;
    u1_ap_xspi_add[4] = (U1)((u2_t_data_size & (U2)0xFF00U) >> XSPI_IVI_SFT_08);
    u1_ap_xspi_add[5] = (U1)(u2_t_data_size & (U2)0x00FFU);
    u1_ap_xspi_add[6] = (U1)0x8CU;
    u1_ap_xspi_add[7] = u1_t_data_num;
}

/*===================================================================================================================================*/
/*  void            vd_s_XspiIviSub1SendCommandPeriCall(void)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC Data) Transmission data                                                                           */
/*  Arguments:      u1_ap_xspi_add : SubFlame2 start address                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void            vd_s_XspiIviSub1SendCommandPeriCall(void)
{
    /*定期送信があるコマンドのMCU⇒SOC送信処理作成*/
    /*各コマンドの定期処理を呼び出し*/
    vd_g_XspiIviSub1PowerMainTask();
    vd_g_XspiIviSub1CameraMainTask();
    vd_g_XspiIviSub1SystemMainTask();

}

/*===================================================================================================================================*/
/*  U1            u1_s_XspiIviSub1SendMISCData(U2 * u2_ap_data_len, U1 * u1_ap_xspi_add)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC Data) Transmission data                                                                           */
/*  Arguments:      u1_ap_data_len : SubFlame1 Data Length                                                                           */
/*                  u1_ap_xspi_add : SubFlame1 MISC Data                                                                             */
/*  Return:         u1_t_data_num : SubFlame1 Data Num                                                                               */
/*===================================================================================================================================*/
static U1            u1_s_XspiIviSub1SendMISCData(U2 * u2_ap_data_len, U1 * u1_ap_xspi_add)
{
    U1          u1_t_data_size;
    U1          u1_t_data_size_ref;
    U1          u1_t_data_num;
    U1          u1_t_rslt;
    U4          u4_t_loop;

    u1_t_data_num = (U1)0U;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_IVI_MISC_DATA_SIZE_MAX; u4_t_loop++) {
        u1_t_data_size_ref = u1_g_XspiIviQueueGetMiscDataSizeRef();
        /*256byte-キューに入ってるデータサイズ-OFFSET(1)*/
        if(*u2_ap_data_len <= (U2)XSPI_IVI_MISC_DATA_SIZE_MAX - (U2)u1_t_data_size_ref - (U2)XSPI_IVI_MISC_DATA_SIZE_OFFSET) {
            u1_t_rslt = u1_g_XspiIviQueueGetMiscDataSize(&u1_t_data_size);
            if (u1_t_rslt == (U1)TRUE) {
                u1_t_data_num++;                                                                              /* MISC読み出し個数+1 */
                *u2_ap_data_len = *u2_ap_data_len + (U2)u1_t_data_size + (U2)XSPI_IVI_MISC_DATA_SIZE_OFFSET;        /* MISCサイズに読み出したMISCサイズ加算 */
            }
            else {
                /* MISCデータサイズ読み出し失敗でループ終了 */
                u4_t_loop = (U4)0xFFFFU;
            }
        }
        else {
            /* 読み出しサイズ上限のためループ終了 */
            u4_t_loop = (U4)0xFFFFU;
        }
    }
    /* MISCメッセージデータの読出しと格納 */
    vd_g_XspiIviQueueGetMiscdata(&u1_ap_xspi_add[8], *u2_ap_data_len);
	
    return (u1_t_data_num);

}

/*ヘッダー作る＋キューの関数を呼び出す関数を作成する(キューにデータを格納していく)*/
/*===================================================================================================================================*/
/*  void         vd_g_XspiIviSub1MISCStuckBuff(const U1 u1_a_TYPE, const U2 u2_a_SIZE,const U1 * u1_ap_SRC)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Description:    SubFlame1(MISC Data) Transmission data                                                                           */
/*  Arguments:      u2_a_TYPE : Command Data Type                                                                                    */
/*                  u2_a_SIZE : Command Data Length                                                                                  */
/*                  u1_ap_SRC : Command Data                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_XspiIviSub1MISCStuckBuff(const U1 u1_a_TYPE, const U2 u2_a_SIZE,const U1 * u1_ap_SRC)
{
    U1          u1_tp_misc_data[XSPI_IVI_MISC_DATA_SIZE_MAX];
    U2          u2_t_misc_data_size;
    U1          u1_t_jdg;

    
    u1_t_jdg = (U1)FALSE;
    vd_g_MemfillU1(&u1_tp_misc_data[0], (U1)0U, (U4)XSPI_IVI_MISC_DATA_SIZE_MAX);
    
    u2_t_misc_data_size = u2_a_SIZE + (U2)XSPI_IVI_HEADER;
    u1_t_jdg = u1_g_XspiIviQueueWriChkMISC(u2_t_misc_data_size);

    if(u1_t_jdg == (U1)TRUE)
    {
        /*キューに空き容量があるためデータ格納*/
        /*各コマンドのヘッダー情報作成*/
        /*識別値*/
        u1_tp_misc_data[0] = (U1)0x4DU;
        u1_tp_misc_data[1] = (U1)0x49U;
        u1_tp_misc_data[2] = (U1)0x53U;
        u1_tp_misc_data[3] = (U1)0x43U;
        /*データタイプ*/
        u1_tp_misc_data[4] = 0U;        /*データタイプがU1に収まるためByte4は0固定*/
        u1_tp_misc_data[5] = u1_a_TYPE;
        /*データサイズ*/
        u1_tp_misc_data[6] = (U1)((u2_a_SIZE & 0xFF00U) >> XSPI_IVI_SFT_08);
        u1_tp_misc_data[7] = (U1)u2_a_SIZE & 0x00FFU;

        vd_g_MemcpyU1(&u1_tp_misc_data[8], &u1_ap_SRC[0], (U4)u2_a_SIZE);

        /*MISCデータをキューに格納*/
        vd_g_XspiIviQueueWriMiscdata(u1_tp_misc_data,u2_t_misc_data_size);
        /*MISCデータサイズをキューに格納*/
        /*データサイズ最大256byteのためU1のバッファに収まるようOFFSET処理*/
        u2_t_misc_data_size = u2_t_misc_data_size - (U2)XSPI_IVI_MISC_DATA_SIZE_OFFSET;
        u1_g_XspiIviQueueWriMiscSize((U1)u2_t_misc_data_size);
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
/*  0.0.0    01/20/2025  KT       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
