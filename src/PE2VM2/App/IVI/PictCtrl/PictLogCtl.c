/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  PictLogCtl                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PictLogCtl.h"
#include "SysEcDrc.h"
#include "x_spi_ivi_sub1_camera.h"
#include "memfill_u1.h"
#include "memfill_u4.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PICTLOGCTL_FLG_NON                      (0x00U)
#define PICTLOGCTL_FLG_GPIO0_HI                 (0x01U)
#define PICTLOGCTL_FLG_GPIO0_LO                 (0x02U)
#define PICTLOGCTL_FLG_BPASS                    (0x04U)
#define PICTLOGCTL_FLG_NORMAL                   (0x08U)
#define PICTLOGCTL_FLG_MUTE_ON                  (0x10U)
#define PICTLOGCTL_FLG_MUTE_OFF                 (0x20U)
#define PICTLOGCTL_FLG_CD_SIZE                  (0x40U)
#define PICTLOGCTL_FLG_POWER_ON                 (0x80U)

#define PICTLOGCTL_BUFF_NUM                     (35U)
#define PICTLOGCTL_BUFF_ENABLESTS               (0U)
#define PICTLOGCTL_BUFF_TXFLG                   (1U)
#define PICTLOGCTL_BUFF_UNDEFINE                (2U)
#define PICTLOGCTL_BUFF_GPIO0_HI                (3U)
#define PICTLOGCTL_BUFF_GPIO0_LO                (7U)
#define PICTLOGCTL_BUFF_BPASS                   (11U)
#define PICTLOGCTL_BUFF_NORMAL                  (15U)
#define PICTLOGCTL_BUFF_MUTE_ON                 (19U)
#define PICTLOGCTL_BUFF_MUTE_OFF                (23U)
#define PICTLOGCTL_BUFF_CD_SIZE                 (27U)
#define PICTLOGCTL_BUFF_POWER_ON                (31U)

#define PICTLOGCTL_TIMSIZ                       (4U)
#define PICTLOGCTL_TIMBUFF0                     (0U)
#define PICTLOGCTL_TIMBUFF1                     (1U)
#define PICTLOGCTL_TIMBUFF2                     (2U)
#define PICTLOGCTL_TIMBUFF3                     (3U)

#define PICTLOGCTL_MASK_1BYTE                   (0x000000FFU)
#define PICTLOGCTL_MASK_2BYTE                   (0x0000FF00U)
#define PICTLOGCTL_MASK_3BYTE                   (0x00FF0000U)
#define PICTLOGCTL_MASK_4BYTE                   (0xFF000000U)

#define PICTLOGCTL_SHIF_1BYTE                   (8U)
#define PICTLOGCTL_SHIF_2BYTE                   (16U)
#define PICTLOGCTL_SHIF_3BYTE                   (24U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4    u4_sp_pictlogctl_time[PICTLOGCTL_POINT_NUM];
static U1    u1_s_pictlogctl_enblests;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_PictLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1 u1_sp_PICTLOGCTL_FLG_TBL[PICTLOGCTL_POINT_NUM] =
{
    (U1)PICTLOGCTL_FLG_GPIO0_HI,
    (U1)PICTLOGCTL_FLG_GPIO0_LO,
    (U1)PICTLOGCTL_FLG_BPASS,
    (U1)PICTLOGCTL_FLG_NORMAL,
    (U1)PICTLOGCTL_FLG_MUTE_ON,
    (U1)PICTLOGCTL_FLG_MUTE_OFF,
    (U1)PICTLOGCTL_FLG_CD_SIZE,
    (U1)PICTLOGCTL_FLG_POWER_ON
};

static const U1 u1_sp_PICTLOGCTL_TXINDEX_TBL[PICTLOGCTL_POINT_NUM] =
{
    (U1)PICTLOGCTL_BUFF_GPIO0_HI,
    (U1)PICTLOGCTL_BUFF_GPIO0_LO,
    (U1)PICTLOGCTL_BUFF_BPASS,
    (U1)PICTLOGCTL_BUFF_NORMAL,
    (U1)PICTLOGCTL_BUFF_MUTE_ON,
    (U1)PICTLOGCTL_BUFF_MUTE_OFF,
    (U1)PICTLOGCTL_BUFF_CD_SIZE,
    (U1)PICTLOGCTL_BUFF_POWER_ON
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_PictLogCtl_Init(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictLogCtl_Init(void)
{
    vd_g_MemfillU4(&u4_sp_pictlogctl_time[0], (U4)0U, (U4)PICTLOGCTL_POINT_NUM);
    u1_s_pictlogctl_enblests = (U1)PICTLOGCTL_FLG_NON;
}

/*===================================================================================================================================*/
/*  void    vd_s_PictLogCtl_LogReq(const U1 u1_a_POINT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void     vd_g_PictLogCtl_LogReq(const U1 u1_a_POINT)
{
    U1 u1_t_cnt;
    U1 u1_t_sts;
    U1 u1_t_txflg;
    U1 u1_t_buff_index;
    U4 u4_t_elpsd_time;
    U1 u1_t_buff[PICTLOGCTL_BUFF_NUM];
    
    u1_t_sts = (U1)0U;
    u1_t_txflg = u1_sp_PICTLOGCTL_FLG_TBL[u1_a_POINT];
    u1_t_buff_index = (U1)0U;
    u4_t_elpsd_time = (U4)0U;
    vd_g_MemfillU1(&u1_t_buff[0], (U1)0x00U, (U4)PICTLOGCTL_BUFF_NUM);
    
    u4_sp_pictlogctl_time[u1_a_POINT] = u4_g_SysEcDrc_GetSystime();
    
    u1_t_buff[PICTLOGCTL_BUFF_TXFLG] = u1_t_txflg;
    
    u1_s_pictlogctl_enblests |= u1_t_txflg;
    u1_t_buff[PICTLOGCTL_BUFF_ENABLESTS] = u1_s_pictlogctl_enblests;
    
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)PICTLOGCTL_POINT_NUM; u1_t_cnt++){
        u1_t_sts = u1_s_pictlogctl_enblests & u1_sp_PICTLOGCTL_FLG_TBL[u1_t_cnt];
        if(u1_t_sts != (U1)PICTLOGCTL_FLG_NON){
            u4_t_elpsd_time = u4_sp_pictlogctl_time[u1_t_cnt];
            u1_t_buff_index = u1_sp_PICTLOGCTL_TXINDEX_TBL[u1_t_cnt];
            vd_s_PictLogCtl_SetTim_4(u4_t_elpsd_time, &u1_t_buff[u1_t_buff_index]);
        }
    }
    
    vd_g_XspiIviSub1CameraLogDataSend(&u1_t_buff[0]);
}

/*===================================================================================================================================*/
/*  static void vd_s_PictLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PictLogCtl_SetTim_4(U4 u4_a_time, U1* u1p_a_buff)
{
    U1 u1_t_time[PICTLOGCTL_TIMSIZ];
    
    u1_t_time[PICTLOGCTL_TIMBUFF3] = (U1)(u4_a_time & (U4)PICTLOGCTL_MASK_1BYTE);
    u1_t_time[PICTLOGCTL_TIMBUFF2] = (U1)((u4_a_time & (U4)PICTLOGCTL_MASK_2BYTE) >> PICTLOGCTL_SHIF_1BYTE);
    u1_t_time[PICTLOGCTL_TIMBUFF1] = (U1)((u4_a_time & (U4)PICTLOGCTL_MASK_3BYTE) >> PICTLOGCTL_SHIF_2BYTE);
    u1_t_time[PICTLOGCTL_TIMBUFF0] = (U1)((u4_a_time & (U4)PICTLOGCTL_MASK_4BYTE) >> PICTLOGCTL_SHIF_3BYTE);
    
    if(u1p_a_buff != NULL_PTR){
        vd_g_MemcpyU1(&u1p_a_buff[0], &u1_t_time[0], (U4)PICTLOGCTL_TIMSIZ);
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
/*  0.0.0    02/02/2026  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
