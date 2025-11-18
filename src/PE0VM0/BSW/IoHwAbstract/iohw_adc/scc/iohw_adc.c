/* 1.8.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Analog Digital Converter                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_C_MAJOR                         (1)
#define IOHW_ADC_C_MINOR                         (8)
#define IOHW_ADC_C_PATCH                         (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "iohw_adc_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IOHW_ADC_C_MAJOR != IOHW_ADC_H_MAJOR) || \
     (IOHW_ADC_C_MINOR != IOHW_ADC_H_MINOR) || \
     (IOHW_ADC_C_PATCH != IOHW_ADC_H_PATCH))
#error "iohw_adc.c and iohw_adc.h : source and header files are inconsistent!"
#endif

#if ((IOHW_ADC_C_MAJOR != IOHW_ADC_CFG_H_MAJOR) || \
     (IOHW_ADC_C_MINOR != IOHW_ADC_CFG_H_MINOR) || \
     (IOHW_ADC_C_PATCH != IOHW_ADC_CFG_H_PATCH))
#error "iohw_adc.c and iohw_adc_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_CVIDX_BIT_STA                   (0x0000ffffU)
#define IOHW_ADC_CVIDX_BIT_FIN                   (0xffff0000U)
#define IOHW_ADC_CVIDX_LSB_STA                   (0U)
#define IOHW_ADC_CVIDX_LSB_FIN                   (16U)

#define IOHW_ADC_CVIDX_INC_STA                   (0x00000001U)
#define IOHW_ADC_CVIDX_INC_FIN                   (0x00010000U)

#define IOHW_ADC_CYCL_SEQ_INIT                   (0x00U)
#define IOHW_ADC_CYCL_SEQ_ACT                    (0x01U)
#define IOHW_ADC_CYCL_SEQ_INACT                  (0x02U)

#define IOHW_ADC_LV_BIT_IDX                      (0x7fU)
#define IOHW_ADC_LV_BIT_UNK                      (0x80U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section bss=".IOHW_ADC_BSS_VAR_NO_INIT"

static volatile U4           u4_s_iohw_adc_cvidx;
static U2                    u2_s_iohw_adc_seq_tocnt;

#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
static U2                    u2_s_iohw_adc_cycltmcnt;
static U2                    u2_s_iohw_adc_cycltk;
static volatile U1           u1_s_iohw_adc_cyclact;
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */

static volatile U1           u1_s_iohw_adc_lv_wr_act;
static volatile U1           u1_s_iohw_adc_lv_wr_fin;
static volatile U1           u1_s_iohw_adc_lv_rd;

#pragma ghs section bss=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".IOHW_ADC_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcInit(void)
{
    U4 *                       u4_tp_lv_0;
    U4 *                       u4_tp_lv_1;
    U4 *                       u4_tp_lv_2;
    U4                         u4_t_lpcnt;
    U4                         u4_t_num_word;

    u4_s_iohw_adc_cvidx     = (U4)U4_MAX;
    u2_s_iohw_adc_seq_tocnt = (U2)0U;

#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
    u2_s_iohw_adc_cycltmcnt = (U2)U2_MAX;
    u2_s_iohw_adc_cycltk    = (U2)U2_MAX;
    u1_s_iohw_adc_cyclact   = (U1)IOHW_ADC_CYCL_SEQ_INACT;
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */

    u1_s_iohw_adc_lv_wr_act = (U1)IOHW_ADC_LV_BUF_0;
    u1_s_iohw_adc_lv_wr_fin = (U1)IOHW_ADC_LV_BUF_1 | (U1)IOHW_ADC_LV_BIT_UNK;
    u1_s_iohw_adc_lv_rd     = (U1)IOHW_ADC_LV_BUF_2 | (U1)IOHW_ADC_LV_BIT_UNK;

    u4_t_num_word = ((U4)u1_g_IOHW_ADC_NUM_CH >> 1) + ((U4)u1_g_IOHW_ADC_NUM_CH & (U4)0x00000001U);

    u4_tp_lv_0 = u4p_gp_IOHW_ADC_LV[IOHW_ADC_LV_BUF_0];
    u4_tp_lv_1 = u4p_gp_IOHW_ADC_LV[IOHW_ADC_LV_BUF_1];
    u4_tp_lv_2 = u4p_gp_IOHW_ADC_LV[IOHW_ADC_LV_BUF_2];
    for(u4_t_lpcnt = (U4)0; u4_t_lpcnt < u4_t_num_word; u4_t_lpcnt++){
        u4_tp_lv_0[u4_t_lpcnt] = (U4)IOHW_ADC_LV_U4_UNKNWN;
        u4_tp_lv_1[u4_t_lpcnt] = (U4)IOHW_ADC_LV_U4_UNKNWN;
        u4_tp_lv_2[u4_t_lpcnt] = (U4)IOHW_ADC_LV_U4_UNKNWN;
    }

    vd_g_IoHwAdcCfgInit();
    vd_g_IoHwAdcCfgCvstInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcMainTask(void)
{
    volatile U4                u4_t_gli;

    U1                         u1_t_tout;
    U1                         u1_t_wr_act;
    U1                         u1_t_wr_fin;
    U1                         u1_t_wr_inact;
    U1                         u1_t_rd;

    vd_g_IoHwAdcCfgMainTask();

    if(u2_s_iohw_adc_seq_tocnt < (U2)U2_MAX){
        u2_s_iohw_adc_seq_tocnt++;
    }

    if((u2_g_IOHW_ADC_SEQ_FIN_TOUT >  (U2)0U                    ) &&
       (u2_s_iohw_adc_seq_tocnt    >= u2_g_IOHW_ADC_SEQ_FIN_TOUT)){
        u1_t_tout = (U1)TRUE;
    }
    else{
        u1_t_tout = (U1)FALSE;
    }

    u4_t_gli = u4_g_IoHwAdcCfg_DI();

    u1_t_wr_act   = u1_s_iohw_adc_lv_wr_act;
    u1_t_wr_fin   = u1_s_iohw_adc_lv_wr_fin;
    u1_t_wr_inact = u1_t_wr_fin & (U1)IOHW_ADC_LV_BIT_IDX;
    u1_t_rd       = u1_s_iohw_adc_lv_rd & (U1)IOHW_ADC_LV_BIT_IDX;

    if((u1_t_wr_act   >= (U1)IOHW_ADC_LV_NUM_BUF) ||
       (u1_t_wr_inact >= (U1)IOHW_ADC_LV_NUM_BUF) ||
       (u1_t_rd       >= (U1)IOHW_ADC_LV_NUM_BUF) ||
       (u1_t_wr_act   == u1_t_wr_inact          ) ||
       (u1_t_wr_act   == u1_t_rd                ) ||
       (u1_t_wr_inact == u1_t_rd                ) ||
       (u1_t_tout     == (U1)TRUE               )){

        u4_s_iohw_adc_cvidx     = (U4)U4_MAX;
        vd_g_IoHwAdcCfgCvstInit();

        u1_s_iohw_adc_lv_wr_act = (U1)IOHW_ADC_LV_BUF_0;
        u1_s_iohw_adc_lv_wr_fin = (U1)IOHW_ADC_LV_BUF_1 | (U1)IOHW_ADC_LV_BIT_UNK;
        u1_s_iohw_adc_lv_rd     = (U1)IOHW_ADC_LV_BUF_2 | (U1)IOHW_ADC_LV_BIT_UNK;

        u2_s_iohw_adc_seq_tocnt = (U2)0U;

#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
        u1_s_iohw_adc_cyclact   = (U1)IOHW_ADC_CYCL_SEQ_INACT;
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */
    }
    else if(u1_t_wr_fin < (U1)IOHW_ADC_LV_NUM_BUF){

        u1_s_iohw_adc_lv_wr_fin = u1_t_rd | (U1)IOHW_ADC_LV_BIT_UNK;
        u1_s_iohw_adc_lv_rd     = u1_t_wr_fin;

        u2_s_iohw_adc_seq_tocnt = (U2)0U;
    }
    else{
        /* do nothing */
    }

    vd_g_IoHwAdcCfg_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcSeqAct(const U1 u1_a_INIT)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcSeqAct(const U1 u1_a_INIT)
{
    volatile U4                u4_t_gli;
    U4                         u4_t_cvidx;

    u4_t_gli = u4_g_IoHwAdcCfg_DI();

    u4_t_cvidx = u4_s_iohw_adc_cvidx;
    if(u1_a_INIT == (U1)TRUE){
        vd_g_IoHwAdcCfgCvstInit();
        u4_s_iohw_adc_cvidx = (U4)0U;
    }
    else if(u4_t_cvidx >= (U4)U4_MAX){
        u4_s_iohw_adc_cvidx = (U4)0U;
    }
    else{
        /* do nothing */
    }

    vd_g_IoHwAdcCfg_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcSeqDeAct(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcSeqDeAct(void)
{
    volatile U4                u4_t_gli;
    U4                         u4_t_cvidx;

    u4_t_gli = u4_g_IoHwAdcCfg_DI();

    u4_t_cvidx = u4_s_iohw_adc_cvidx;
    if(u4_t_cvidx < (U4)U4_MAX){
        vd_g_IoHwAdcCfgCvstInit();
    }
    u4_s_iohw_adc_cvidx = (U4)U4_MAX;

    vd_g_IoHwAdcCfg_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwAdcSeqActvtd(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IoHwAdcSeqActvtd(void)
{
    U4                         u4_t_cvidx;
    U1                         u1_t_act;

    u4_t_cvidx = u4_s_iohw_adc_cvidx;
    if(u4_t_cvidx < (U4)U4_MAX){
        u1_t_act = (U1)TRUE;
    }
    else{
        u1_t_act = (U1)FALSE;
    }

    return(u1_t_act);
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCvstStart(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCvstStart(void)
{
    U4                         u4_t_cvidx;
    U4                         u4_t_cvidx_sta;
    U4                         u4_t_cvidx_fin;

    U1                         u1_t_lv_wr_act;

    u4_t_cvidx     = u4_s_iohw_adc_cvidx;
    u4_t_cvidx_sta = u4_t_cvidx & (U4)IOHW_ADC_CVIDX_BIT_STA;
    u4_t_cvidx_fin = u4_t_cvidx >> IOHW_ADC_CVIDX_LSB_FIN;

    u1_t_lv_wr_act = u1_s_iohw_adc_lv_wr_act;
    if((u1_t_lv_wr_act <  (U1)IOHW_ADC_LV_NUM_BUF   ) &&
       (u4_t_cvidx_sta <  (U4)u1_g_IOHW_ADC_NUM_CVST) &&
       (u4_t_cvidx_sta == u4_t_cvidx_fin            )){

        u4_s_iohw_adc_cvidx = u4_t_cvidx + (U4)IOHW_ADC_CVIDX_INC_STA;
        vd_g_IoHwAdcCfgCvstStart((U1)u4_t_cvidx_sta, u1_t_lv_wr_act);
    }
    else{

        vd_g_IoHwAdcSeqDeAct();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCvstFinish(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCvstFinish(void)
{
    U4                         u4_t_cvidx;
    U4                         u4_t_cvidx_sta;
    U4                         u4_t_cvidx_fin;
    U4                         u4_t_cvidx_next;

    U1                         u1_t_lv_wr_act;

    u4_t_cvidx      = u4_s_iohw_adc_cvidx;
    u4_t_cvidx_sta  = u4_t_cvidx & (U4)IOHW_ADC_CVIDX_BIT_STA;
    u4_t_cvidx_fin  = u4_t_cvidx >> IOHW_ADC_CVIDX_LSB_FIN;
    u4_t_cvidx_next = u4_t_cvidx_fin + (U4)1U;

    u1_t_lv_wr_act  = u1_s_iohw_adc_lv_wr_act;
    if((u1_t_lv_wr_act <  (U1)IOHW_ADC_LV_NUM_BUF   ) &&
       (u4_t_cvidx_fin <  (U4)u1_g_IOHW_ADC_NUM_CVST) &&
       (u4_t_cvidx_sta == u4_t_cvidx_next           )){

        vd_g_IoHwAdcCfgCvstFinish((U1)u4_t_cvidx_fin, u1_t_lv_wr_act);

        if(u4_t_cvidx_next >= (U4)u1_g_IOHW_ADC_NUM_CVST){

            u1_s_iohw_adc_lv_wr_act = u1_s_iohw_adc_lv_wr_fin & (U1)IOHW_ADC_LV_BIT_IDX; /* lv_wr_act <-> lv_wr_fin */
            u1_s_iohw_adc_lv_wr_fin = u1_t_lv_wr_act;

            u4_s_iohw_adc_cvidx     = (U4)U4_MAX;
        }
        else{

            u4_s_iohw_adc_cvidx     = u4_t_cvidx + (U4)IOHW_ADC_CVIDX_INC_FIN;
        }
    }
    else{

        vd_g_IoHwAdcSeqDeAct();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCyclSeqTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCyclSeqTask(void)
{
#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
    U1                         u1_t_cycl_act;
    U1                         u1_t_lv_wr_act;

    u1_t_cycl_act  = u1_s_iohw_adc_cyclact;
    u1_t_lv_wr_act = u1_s_iohw_adc_lv_wr_act;
    if((u1_t_lv_wr_act >= (U1)IOHW_ADC_LV_NUM_BUF    ) ||
       (u1_t_cycl_act  >= (U1)IOHW_ADC_CYCL_SEQ_INACT)){

        u1_t_cycl_act           = (U1)IOHW_ADC_CYCL_SEQ_INACT;
        u2_s_iohw_adc_cycltmcnt = (U2)U2_MAX;

        vd_g_IoHwAdcSeqDeAct();
    }
    else if(u1_t_cycl_act == (U1)IOHW_ADC_CYCL_SEQ_INIT){

        u1_t_cycl_act           = (U1)IOHW_ADC_CYCL_SEQ_ACT;
        u2_s_iohw_adc_cycltmcnt = (U2)U2_MAX;

        vd_g_IoHwAdcSeqDeAct();
    }
    else{
        u1_t_cycl_act           = (U1)IOHW_ADC_CYCL_SEQ_ACT;
    }

    u1_s_iohw_adc_cyclact = u1_t_cycl_act;

    if(u1_t_cycl_act == (U1)IOHW_ADC_CYCL_SEQ_ACT){

        if(u2_s_iohw_adc_cycltmcnt >= u2_g_IOHW_ADC_CYCL_TM_MAX){

            u2_s_iohw_adc_cycltmcnt = (U2)0U;
            u2_s_iohw_adc_cycltk    = (U2)0U;
            u4_s_iohw_adc_cvidx     = (U4)0U;
        }

        while((u2_s_iohw_adc_cycltk                                  <  u2_g_IOHW_ADC_NUM_CYCLTK) &&
              (st_gp_IOHW_ADC_CYCLTK[u2_s_iohw_adc_cycltk].u2_cycltm == u2_s_iohw_adc_cycltmcnt )){

            (st_gp_IOHW_ADC_CYCLTK[u2_s_iohw_adc_cycltk].fp_vd_TK)();
            u2_s_iohw_adc_cycltk++;
        }

        u2_s_iohw_adc_cycltmcnt++;
    }
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCyclSeqAct(const U1 u1_a_INIT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCyclSeqAct(const U1 u1_a_INIT)
{
#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
    if((u1_a_INIT             == (U1)TRUE                   ) ||
       (u1_s_iohw_adc_cyclact >= (U1)IOHW_ADC_CYCL_SEQ_INACT)){

        u1_s_iohw_adc_cyclact = (U1)IOHW_ADC_CYCL_SEQ_INIT;
    }
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCyclSeqDeAct(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCyclSeqDeAct(void)
{
#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
    u1_s_iohw_adc_cyclact = (U1)IOHW_ADC_CYCL_SEQ_INACT;
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwAdcCyclSeqActvtd(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IoHwAdcCyclSeqActvtd(void)
{
#if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)
    U1                         u1_t_act;

    if(u1_s_iohw_adc_cyclact == (U1)IOHW_ADC_CYCL_SEQ_ACT){
        u1_t_act = (U1)TRUE;
    }
    else{
        u1_t_act = (U1)FALSE;
    }

    return(u1_t_act);
#else
    return((U1)FALSE);
#endif /* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1) */
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwAdcRead(const U1 u1_a_ADC_CH, U2 *u2_ap_lv)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_IoHwAdcRead(const U1 u1_a_ADC_CH, U2 *u2_ap_lv)
{
    U2 *                       u2_tp_lv_rd;
    U2                         u2_t_lv;
    U1                         u1_t_valid;
    U1                         u1_t_rd;

    u1_t_valid = (U1)FALSE;

    u1_t_rd    = u1_s_iohw_adc_lv_rd;
    if((u1_a_ADC_CH < u1_g_IOHW_ADC_NUM_CH   ) &&
       (u1_t_rd     < (U1)IOHW_ADC_LV_NUM_BUF)){

        u2_tp_lv_rd = (U2 *)u4p_gp_IOHW_ADC_LV[u1_t_rd];
        u2_t_lv     = u2_tp_lv_rd[u1_a_ADC_CH];
        if(u2_t_lv <= u2_g_IOHW_ADC_LV_MAX){

            if(u2_ap_lv != vdp_PTR_NA){
                (*u2_ap_lv) = u2_t_lv;
            }
            u1_t_valid = (U1)TRUE;
        }
    }

    return(u1_t_valid);
}
/*===================================================================================================================================*/
/*  U2      u2_g_IoHwAdcLv(const U1 u1_a_ADC_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_IoHwAdcLv(const U1 u1_a_ADC_CH)
{
    U2 *                       u2_tp_lv_rd;
    U2                         u2_t_lv;
    U1                         u1_t_rd;

    u2_t_lv = (U2)IOHW_ADC_LV_UNKNWN;

    u1_t_rd = u1_s_iohw_adc_lv_rd;
    if((u1_a_ADC_CH < u1_g_IOHW_ADC_NUM_CH   ) &&
       (u1_t_rd     < (U1)IOHW_ADC_LV_NUM_BUF)){

        u2_tp_lv_rd = (U2 *)u4p_gp_IOHW_ADC_LV[u1_t_rd];
        u2_t_lv     = u2_tp_lv_rd[u1_a_ADC_CH];
    }

    return(u2_t_lv);
}

#pragma ghs section text=default

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/26/2015  TN       New.                                                                                               */
/*  1.1.0     4/ 2/2015  TN       vd_g_IoHwAdcCfgPreTask was implemented.                                                            */
/*  1.1.1     6/24/2015  TN       Bug Fix : If interrrupt priority level for vd_g_IoHwAdcCvStart and vd_g_IoHwAdcCvFinish was        */
/*                                changed to higher, RAM sharing issue was caused.                                                   */
/*  1.2.0     6/25/2015  TN       Volatile variables handling was optimized in order to prevent that compiler generates redundant    */
/*                                read/write instuctions.                                                                            */
/*  1.3.0     7/30/2015  TN       Improvement : The use case of conversion cycle was re-designed considering failsafe.               */
/*                                First parameter for vd_g_IoHwAdcCfgCvStart and vd_g_IoHwAdcCfgCvFinish was changed to CVTK index.  */
/*  1.4.0    10/28/2015  TN       Improvement : Cyclic sequence was redesigned and optimized. __IOHW_ADC_DET__ was implemented.      */
/*  1.5.0     1/15/2016  TN       Improvement : Redundant function name redirections were deleted.                                   */
/*  1.6.0    10/ 3/2017  TN       Re-designed and simplified.                                                                        */
/*  1.7.0    10/13/2017  TN       IOHW_ADC_LV_BIT_FIN -> IOHW_ADC_LV_BIT_UNK.                                                        */
/*  1.8.0    12/15/2017  TN       u4p_gp_IOHW_ADC_LV[u1_t_rd] initalization was re-implemented into vd_g_IoHwAdcInit.                */
/*  1.8.1     9/ 7/2021  TN       NULL->vdp_PTR_NA.                                                                                  */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
