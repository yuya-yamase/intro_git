/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  SysEcDrc                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "SysEcDrc.h"
#include "memfill_u1.h"
#include "gpt_drv_frt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define SYSECDRC_DRCCNT_NUM (135U)
#define SYSECDRC_DRCCNT_MAX (SYSECDRC_DRCCNT_NUM - 1U)

#define SYSECDRC_TIMSIZ     (4U)
#define SYSECDRC_TRCSIZ     (4U)
#define SYSECDRC_DRCSIZE    (SYSECDRC_TIMSIZ + SYSECDRC_TRCSIZ)
#define SYSECDRC_DRCMAXSIZE (SYSECDRC_DRCCNT_NUM * SYSECDRC_DRCSIZE)

#define SYSECDRC_MASK_1BYTE (0x000000FFU)
#define SYSECDRC_MASK_2BYTE (0x0000FF00U)
#define SYSECDRC_MASK_3BYTE (0x00FF0000U)
#define SYSECDRC_MASK_4BYTE (0xFF000000U)

#define SYSECDRC_SHIF_1BYTE (8U)
#define SYSECDRC_SHIF_2BYTE (16U)
#define SYSECDRC_SHIF_3BYTE (24U)

#define SYSECDRC_BUFF0      (0U)
#define SYSECDRC_BUFF1      (1U)
#define SYSECDRC_BUFF2      (2U)
#define SYSECDRC_BUFF3      (3U)
#define SYSECDRC_BUFF4      (4U)
#define SYSECDRC_BUFF5      (5U)
#define SYSECDRC_BUFF6      (6U)
#define SYSECDRC_BUFF7      (7U)

#define SYSECDRC_TIMCNT50MS (5U)

#define SYSECDRC_FRT_1MS    (1000U * GPT_FRT_1US)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2  u2_wp;
    U2  u2_wcnt;
} ST_TRC_MNG;

typedef struct {
    U1 u1_systime[SYSECDRC_TIMSIZ];
    U1 u1_drec[SYSECDRC_TRCSIZ];
} ST_DRC_SYSREC;

typedef struct {
    ST_TRC_MNG st_trcmng;
    ST_DRC_SYSREC st_drcrec[SYSECDRC_DRCCNT_NUM];
} ST_DRC_SYS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_sysecdrc_timecnt_10ms;
ST_DRC_SYS   st_s_drc_sys;
static U4    u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_NUM_PARAM];
static U4    u4_s_sysecdrc_systime_1ms;
static U4    u4_s_sysecdrc_frtsum_1ms;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_SysEcDrc_DrcClear(void);
static void    vd_s_SysEcDrc_UpdateSystime(void);
static void    vd_s_SysEcDrc_GetTim1ms_4(U1* u1p_a_tim1, U1* u1p_a_tim2, U1* u1p_a_tim3, U1* u1p_a_tim4);
static void    vd_s_SysEcDrc_Memcpy(U1 * u1p_a_dst, const ST_DRC_SYSREC * stp_a_src);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_SysEcDrc_Init(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SysEcDrc_Init(void)
{
    vd_s_SysEcDrc_DrcClear();
    u1_s_sysecdrc_timecnt_10ms = (U1)0U;
    u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_BASE]  = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_CRRNT] = (U4)0U;
    u4_s_sysecdrc_systime_1ms = u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_BASE] / (U4)SYSECDRC_FRT_1MS;
    u4_s_sysecdrc_frtsum_1ms = u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_BASE] % (U4)SYSECDRC_FRT_1MS;
}

/*===================================================================================================================================*/
/*  static void    vd_s_SysEcDrc_DrcClear(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SysEcDrc_DrcClear(void)
{
    U1 u1_t_cnt;
    
    st_s_drc_sys.st_trcmng.u2_wp = (U2)0;
    st_s_drc_sys.st_trcmng.u2_wcnt = (U2)0;
    
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)SYSECDRC_DRCCNT_NUM; u1_t_cnt++){
        vd_g_MemfillU1(&st_s_drc_sys.st_drcrec[u1_t_cnt].u1_systime[SYSECDRC_BUFF0], (U1)0x00U, (U4)SYSECDRC_TIMSIZ);
        vd_g_MemfillU1(&st_s_drc_sys.st_drcrec[u1_t_cnt].u1_drec[SYSECDRC_BUFF0], (U1)0x00U, (U4)SYSECDRC_TRCSIZ);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_SysEcDrc_MainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_SysEcDrc_MainTask(void)
{
    if(u1_s_sysecdrc_timecnt_10ms >= (U1)SYSECDRC_TIMCNT50MS){
        vd_s_SysEcDrc_UpdateSystime();
        u1_s_sysecdrc_timecnt_10ms = (U1)0U;
    }
    u1_s_sysecdrc_timecnt_10ms++;
}

/*===================================================================================================================================*/
/*  static void    vd_s_SysEcDrc_UpdateSystime(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_SysEcDrc_UpdateSystime(void)
{
    U4 u4_t_frt_elpsd;
    U4 u4_t_frt_next;
    U4 u4_t_max;

    u4_t_frt_elpsd = u4_g_Gpt_FrtGetUsElapsed(&u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_BASE]);
    u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_BASE] = u4_sp_sysecdrc_elpsd_frt[GPT_FRT_USELPSD_CRRNT];

    u4_s_sysecdrc_frtsum_1ms = u4_s_sysecdrc_frtsum_1ms + u4_t_frt_elpsd;
    u4_t_frt_next = u4_s_sysecdrc_frtsum_1ms / (U4)SYSECDRC_FRT_1MS;
    u4_s_sysecdrc_frtsum_1ms = u4_s_sysecdrc_frtsum_1ms % (U4)SYSECDRC_FRT_1MS;

    u4_t_max = (U4)U4_MAX - u4_t_frt_next;
    if(u4_t_max >= u4_s_sysecdrc_systime_1ms){
        u4_s_sysecdrc_systime_1ms  = u4_s_sysecdrc_systime_1ms + u4_t_frt_next;
    }
    else{
        u4_s_sysecdrc_systime_1ms = u4_t_frt_next - ((U4)U4_MAX - u4_s_sysecdrc_systime_1ms);
    }
}

/*===================================================================================================================================*/
/*  U4      u4_g_SysEcDrc_GetSystime(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4    u4_g_SysEcDrc_GetSystime(void)
{
    return(u4_s_sysecdrc_systime_1ms);
}

/*===================================================================================================================================*/
/*  void vd_g_SysEcDrc_Drec(const U1 u1_a_ARGTRCKIND, const U1 u1_a_DREC1, const U1 u1_a_DREC2, const U1 u1_a_DREC3)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SysEcDrc_Drec(const U1 u1_a_ARGTRCKIND, const U1 u1_a_DREC1, const U1 u1_a_DREC2, const U1 u1_a_DREC3)
{
    ST_TRC_MNG* st_tp_trcmng;
    
    st_tp_trcmng = (ST_TRC_MNG*)&st_s_drc_sys.st_trcmng;    /* ダイレコ領域データアドレス取得 */

    if(st_tp_trcmng != NULL_PTR){
        if (st_tp_trcmng->u2_wp >= SYSECDRC_DRCCNT_NUM) {
            st_tp_trcmng->u2_wp = (U2)0U;
        }

        vd_s_SysEcDrc_UpdateSystime();
        vd_s_SysEcDrc_GetTim1ms_4(&st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_systime[SYSECDRC_BUFF0],
                                  &st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_systime[SYSECDRC_BUFF1],
                                  &st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_systime[SYSECDRC_BUFF2],
                                  &st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_systime[SYSECDRC_BUFF3]);

        st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_drec[SYSECDRC_BUFF3] = u1_a_ARGTRCKIND;
        st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_drec[SYSECDRC_BUFF2] = u1_a_DREC1;
        st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_drec[SYSECDRC_BUFF1] = u1_a_DREC2;
        st_s_drc_sys.st_drcrec[st_tp_trcmng->u2_wp].u1_drec[SYSECDRC_BUFF0] = u1_a_DREC3;

        if(st_tp_trcmng->u2_wp < (U2)SYSECDRC_DRCCNT_MAX) {
            st_tp_trcmng->u2_wp++;
        }
        else{
            st_tp_trcmng->u2_wp = (U2)0U;
        }
        
        if(st_tp_trcmng->u2_wcnt < (U2)U2_MAX) {
            st_tp_trcmng->u2_wcnt++;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_SysEcDrc_GetTim1ms_4(U1* u1p_a_tim1, U1* u1p_a_tim2, U1* u1p_a_tim3, U1* u1p_a_tim4)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_SysEcDrc_GetTim1ms_4(U1* u1p_a_tim1, U1* u1p_a_tim2, U1* u1p_a_tim3, U1* u1p_a_tim4)
{
    U1 u1_time[SYSECDRC_TIMSIZ];
    
    u1_time[SYSECDRC_BUFF0] = (U1)(u4_s_sysecdrc_systime_1ms & (U4)SYSECDRC_MASK_1BYTE);
    u1_time[SYSECDRC_BUFF1] = (U1)((u4_s_sysecdrc_systime_1ms & (U4)SYSECDRC_MASK_2BYTE) >> SYSECDRC_SHIF_1BYTE);
    u1_time[SYSECDRC_BUFF2] = (U1)((u4_s_sysecdrc_systime_1ms & (U4)SYSECDRC_MASK_3BYTE) >> SYSECDRC_SHIF_2BYTE);
    u1_time[SYSECDRC_BUFF3] = (U1)((u4_s_sysecdrc_systime_1ms & (U4)SYSECDRC_MASK_4BYTE) >> SYSECDRC_SHIF_3BYTE);
    
    if((((u1p_a_tim1 != NULL_PTR)  &&
         (u1p_a_tim2 != NULL_PTR)) &&
         (u1p_a_tim3 != NULL_PTR)) &&
         (u1p_a_tim4 != NULL_PTR)){
        *u1p_a_tim1 = u1_time[SYSECDRC_BUFF0];
        *u1p_a_tim2 = u1_time[SYSECDRC_BUFF1];
        *u1p_a_tim3 = u1_time[SYSECDRC_BUFF2];
        *u1p_a_tim4 = u1_time[SYSECDRC_BUFF3];
    }
}

/*===================================================================================================================================*/
/*  void vd_g_SysEcDrc_SendDateSet(U4* u4p_a_size, U1* u1p_a_buff, const U4 u4_a_BUFF_MAX)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_SysEcDrc_SendDateSet(U4* u4p_a_size, U1* u1p_a_buff, const U4 u4_a_BUFF_MAX)
{
    ST_TRC_MNG* st_tp_trcmng;
    U4 u4_t_wp;
    U4 u4_t_cnt;
    U4 u4_t_cntmax;
    U4 u4_t_buffmaxcnt;
    
    st_tp_trcmng = (ST_TRC_MNG*)&st_s_drc_sys.st_trcmng;    /* ダイレコ領域データアドレス取得 */
    
    if(st_tp_trcmng->u2_wcnt < (U2)SYSECDRC_DRCCNT_NUM){
        *u4p_a_size = (U4)st_tp_trcmng->u2_wcnt * (U4)SYSECDRC_DRCSIZE;
        u4_t_cntmax = (U4)st_tp_trcmng->u2_wcnt;
    }
    else{
        *u4p_a_size = (U4)SYSECDRC_DRCMAXSIZE;
        u4_t_cntmax = (U4)SYSECDRC_DRCCNT_NUM;
    }
    
    u4_t_buffmaxcnt = u4_a_BUFF_MAX / (U4)SYSECDRC_DRCSIZE;
    if(u4_t_cntmax > u4_t_buffmaxcnt){
        u4_t_cntmax = u4_t_buffmaxcnt;
    }
    
    for(u4_t_cnt = (U4)0U; u4_t_cnt < u4_t_cntmax; u4_t_cnt++){
        u4_t_wp = u4_t_cnt * (U4)SYSECDRC_DRCSIZE;
        vd_s_SysEcDrc_Memcpy(&u1p_a_buff[u4_t_wp], &st_s_drc_sys.st_drcrec[u4_t_cnt]);
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_SysEcDrc_Memcpy(U1 * u1p_a_dst, const ST_DRC_SYSREC * stp_a_src)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_SysEcDrc_Memcpy(U1 * u1p_a_dst, const ST_DRC_SYSREC * stp_a_src)
{
    u1p_a_dst[SYSECDRC_BUFF0] = stp_a_src->u1_systime[SYSECDRC_BUFF3];
    u1p_a_dst[SYSECDRC_BUFF1] = stp_a_src->u1_systime[SYSECDRC_BUFF2];
    u1p_a_dst[SYSECDRC_BUFF2] = stp_a_src->u1_systime[SYSECDRC_BUFF1];
    u1p_a_dst[SYSECDRC_BUFF3] = stp_a_src->u1_systime[SYSECDRC_BUFF0];
    u1p_a_dst[SYSECDRC_BUFF4] = stp_a_src->u1_drec[SYSECDRC_BUFF3];
    u1p_a_dst[SYSECDRC_BUFF5] = stp_a_src->u1_drec[SYSECDRC_BUFF2];
    u1p_a_dst[SYSECDRC_BUFF6] = stp_a_src->u1_drec[SYSECDRC_BUFF1];
    u1p_a_dst[SYSECDRC_BUFF7] = stp_a_src->u1_drec[SYSECDRC_BUFF0];

}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    05/20/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
