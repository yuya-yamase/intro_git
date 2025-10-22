/* 2.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Throughput Measure                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
#if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1))
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_C_MAJOR                       (2)
#define THROUGHPUT_C_MINOR                       (5)
#define THROUGHPUT_C_PATCH                       (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "throughput_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((THROUGHPUT_C_MAJOR != THROUGHPUT_H_MAJOR) || \
     (THROUGHPUT_C_MINOR != THROUGHPUT_H_MINOR) || \
     (THROUGHPUT_C_PATCH != THROUGHPUT_H_PATCH))
#error "throughput.c and throughput.h : source and header files are inconsistent!"
#endif

#if ((THROUGHPUT_C_MAJOR != THROUGHPUT_CFG_H_MAJOR) || \
     (THROUGHPUT_C_MINOR != THROUGHPUT_CFG_H_MINOR) || \
     (THROUGHPUT_C_PATCH != THROUGHPUT_CFG_H_PATCH))
#error "throughput.c and throughput_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4        u4_meas_start;
    U4        u4_ovrhd_frt;
    U4        u4_ovrhd_cnt;
    U4        u4_task_start;
}ST_THROUGHPUT_MEAS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_THROUGHPUT_MEAS               st_sp_throughput_meas[THROUGHPUT_INTRPT_DEPTH];
static volatile U4                      u4_s_throughput_idepth;
static U4                               u4_s_throughput_meas_ovrhd;
static U4                               u4_s_throughput_irq_ovrhd;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputInit(void)
{
    U4                 u4_t_cnt;

    vd_g_ThroughputCfgInit();

    for(u4_t_cnt = (U4)0U; u4_t_cnt < (U4)THROUGHPUT_INTRPT_DEPTH; u4_t_cnt++){
        st_sp_throughput_meas[u4_t_cnt].u4_meas_start = (U4)0U;
        st_sp_throughput_meas[u4_t_cnt].u4_ovrhd_frt  = (U4)0U;
        st_sp_throughput_meas[u4_t_cnt].u4_ovrhd_cnt  = (U4)0U;
        st_sp_throughput_meas[u4_t_cnt].u4_task_start = (U4)0U;
    }

    u4_s_throughput_idepth = (U4)0U;

    u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT]    = (U4)0U;
    u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] = (U4)0U;

    u4_s_throughput_meas_ovrhd = (U4)u2_g_ThroughputCfgMeasOvrhd();
    u4_s_throughput_irq_ovrhd  = (U4)u2_g_ThroughputCfgIrqOvrhd();
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputIntrptStart(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputIntrptStart(void)
{
/* --------------------------------------------------------------------------------------------------------------------------------- */
#if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0)
/* --------------------------------------------------------------------------------------------------------------------------------- */
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    U4                 u4_t_idepth;

    u4_t_gli = u4_g_ThroughputCfg_DI();

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth + (U4)1;
    if(u4_t_idepth < (U4)THROUGHPUT_INTRPT_DEPTH){

        u4_s_throughput_idepth = u4_t_idepth;

        st_sp_throughput_meas[u4_t_idepth].u4_meas_start = u4_t_frt;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt  = (U4)0U;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt  = (U4)1U;
        st_sp_throughput_meas[u4_t_idepth].u4_task_start = u4_g_ThroughputCfgFrt();
    }
    else{
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }

    vd_g_ThroughputCfg_EI(u4_t_gli);
/* --------------------------------------------------------------------------------------------------------------------------------- */
#else /* #if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
    volatile U4        u4_t_frt;
    U4                 u4_t_idepth;

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth + (U4)1U;
    if(u4_t_idepth < (U4)THROUGHPUT_INTRPT_DEPTH){

        u4_s_throughput_idepth = u4_t_idepth;

        st_sp_throughput_meas[u4_t_idepth].u4_meas_start = u4_t_frt;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt  = (U4)0U;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt  = (U4)0U;
        st_sp_throughput_meas[u4_t_idepth].u4_task_start = u4_g_ThroughputCfgFrt();
    }
    else{
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }
/* --------------------------------------------------------------------------------------------------------------------------------- */
#endif /* #if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputIntrptFinish(const U2 u2_a_IRQ_CH)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputIntrptFinish(const U2 u2_a_IRQ_CH)
{
/* --------------------------------------------------------------------------------------------------------------------------------- */
#if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0)
/* --------------------------------------------------------------------------------------------------------------------------------- */
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    volatile U4        u4_t_meas_start;
    U4                 u4_t_idepth;
    U4                 u4_t_throughput;
    U4                 u4_t_ovrhd;
    U4                 u4_t_diff;

    u4_t_gli = u4_g_ThroughputCfg_DI();

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth;
    if(u4_t_idepth >= (U4)THROUGHPUT_INTRPT_DEPTH){
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }
    else if(u4_t_idepth > (U4)0U){

        u4_t_throughput  = u4_t_frt - st_sp_throughput_meas[u4_t_idepth].u4_task_start;
        u4_t_throughput += u4_s_throughput_irq_ovrhd;

        u4_t_ovrhd       = st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt * u4_s_throughput_meas_ovrhd;
        u4_t_ovrhd     >>= THROUGHPUT_RSHFT_OVRHD_CAL;
        u4_t_ovrhd      += st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt;

        if(u4_t_throughput >= u4_t_ovrhd){
            u4_t_throughput -= u4_t_ovrhd;
            vd_g_ThroughputCfgIsrCapt(u2_a_IRQ_CH, u4_t_throughput);
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_LT_OVRHD;
            u4_t_diff = u4_t_ovrhd - u4_t_throughput;
            if(u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] < u4_t_diff){
                u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] = u4_t_diff;
            }
        }

        u4_t_meas_start = st_sp_throughput_meas[u4_t_idepth].u4_meas_start;
        u4_t_idepth--;
        u4_s_throughput_idepth = u4_t_idepth;
        if(st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt < (U4)U2_MAX){
            st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt++;
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_OVRHD_CNT_OVF;
        }

        /* over head for lower task */
        u4_t_frt = (u4_g_ThroughputCfgFrt() - u4_t_meas_start) + u4_s_throughput_irq_ovrhd;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt += u4_t_frt; 
    }
    else{   
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_UDF;
    }

    vd_g_ThroughputCfg_EI(u4_t_gli);
/* --------------------------------------------------------------------------------------------------------------------------------- */
#else /* #if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
    volatile U4        u4_t_frt;
    volatile U4        u4_t_meas_start;
    U4                 u4_t_idepth;
    U4                 u4_t_throughput;
    U4                 u4_t_ovrhd;
    U4                 u4_t_diff;

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth;
    if(u4_t_idepth >= (U4)THROUGHPUT_INTRPT_DEPTH){
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }
    else if(u4_t_idepth > (U4)0U){

        u4_t_throughput  = u4_t_frt - st_sp_throughput_meas[u4_t_idepth].u4_task_start;
        u4_t_throughput += u4_s_throughput_irq_ovrhd;

        u4_t_ovrhd       = st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt * u4_s_throughput_meas_ovrhd;
        u4_t_ovrhd     >>= THROUGHPUT_RSHFT_OVRHD_CAL;
        u4_t_ovrhd      += st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt;

        if(u4_t_throughput >= u4_t_ovrhd){
            u4_t_throughput -= u4_t_ovrhd;
            vd_g_ThroughputCfgIsrCapt(u2_a_IRQ_CH, u4_t_throughput);
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_LT_OVRHD;
            u4_t_diff = u4_t_ovrhd - u4_t_throughput;
            if(u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] < u4_t_diff){
                u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] = u4_t_diff;
            }
        }

        u4_t_meas_start = st_sp_throughput_meas[u4_t_idepth].u4_meas_start;
        u4_t_idepth--;
        u4_s_throughput_idepth = u4_t_idepth;
    /*  if(st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt < (U4)U2_MAX){               */
    /*      st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt++;                          */
    /*  }                                                                                          */
    /*  else{                                                                                      */
    /*      u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_OVRHD_CNT_OVF; */
    /*  }                                                                                          */

        /* over head for lower task */
        u4_t_frt = (u4_g_ThroughputCfgFrt() - u4_t_meas_start) + u4_s_throughput_irq_ovrhd;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt += u4_t_frt; 
    }
    else{   
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_UDF;
    }
/* --------------------------------------------------------------------------------------------------------------------------------- */
#endif /* #if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 0) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputMainStart(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputMainStart(void)
{
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    U4                 u4_t_idepth;

    u4_t_gli = u4_g_ThroughputCfg_DI();

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth + (U4)1U;
    if(u4_t_idepth < (U4)THROUGHPUT_INTRPT_DEPTH){

        u4_s_throughput_idepth = u4_t_idepth;

        st_sp_throughput_meas[u4_t_idepth].u4_meas_start = u4_t_frt;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt  = (U4)0U;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt  = (U4)1U;
        st_sp_throughput_meas[u4_t_idepth].u4_task_start = u4_g_ThroughputCfgFrt();
    }
    else{
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }

    vd_g_ThroughputCfg_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputMainFinish(const U2 u2_a_TASK_ID)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputMainFinish(const U2 u2_a_TASK_ID)
{
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    volatile U4        u4_t_meas_start;
    U4                 u4_t_idepth;
    U4                 u4_t_throughput;
    U4                 u4_t_ovrhd;
    U4                 u4_t_diff;

    u4_t_gli = u4_g_ThroughputCfg_DI();

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth;
    if(u4_t_idepth >= (U4)THROUGHPUT_INTRPT_DEPTH){
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }
    else if(u4_t_idepth > (U4)0U){

        u4_t_throughput  = u4_t_frt - st_sp_throughput_meas[u4_t_idepth].u4_task_start;
        u4_t_ovrhd       = st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt * u4_s_throughput_meas_ovrhd;
        u4_t_ovrhd     >>= THROUGHPUT_RSHFT_OVRHD_CAL;
        u4_t_ovrhd      += st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt;

        if(u4_t_throughput >= u4_t_ovrhd){
            u4_t_throughput -= u4_t_ovrhd;
            vd_g_ThroughputCfgTaskCapt(u2_a_TASK_ID, u4_t_throughput);
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_LT_OVRHD;
            u4_t_diff = u4_t_ovrhd - u4_t_throughput;
            if(u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] < u4_t_diff){
                u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] = u4_t_diff;
            }
        }

        u4_t_meas_start = st_sp_throughput_meas[u4_t_idepth].u4_meas_start;
        u4_t_idepth--;
        u4_s_throughput_idepth = u4_t_idepth;
        if(st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt < (U4)U2_MAX){
            st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt++;
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_OVRHD_CNT_OVF;
        }

        /* over head for lower task */
        u4_t_frt = u4_g_ThroughputCfgFrt() - u4_t_meas_start;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt += (u4_t_frt - u4_t_throughput); 
    }
    else{   
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_UDF;
    }

    vd_g_ThroughputCfg_EI(u4_t_gli);
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputIdleStart(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputIdleStart(void)
{
    volatile U4        u4_t_gli;

    u4_t_gli = u4_g_ThroughputCfg_DI();                                   /* Disable Interrupt */

    u4_s_throughput_idepth                 = (U4)0U;
    st_sp_throughput_meas[0].u4_ovrhd_frt  = (U4)0U;
    st_sp_throughput_meas[0].u4_ovrhd_cnt  = (U4)1U;
    st_sp_throughput_meas[0].u4_task_start = u4_g_ThroughputCfgFrt();

    vd_g_ThroughputCfg_EI(u4_t_gli);                                      /* Enable Interrupt  */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputIdleFinish(const U2 u2_a_TASK_ID)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputIdleFinish(const U2 u2_a_TASK_ID)
{
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    U4                 u4_t_throughput;
    U4                 u4_t_ovrhd;
    U4                 u4_t_diff;

    u4_t_gli = u4_g_ThroughputCfg_DI();                                   /* Disable Interrupt */

    u4_t_frt = u4_g_ThroughputCfgFrt();

    if(u4_s_throughput_idepth == (U4)0U){

        u4_t_throughput  = u4_t_frt - st_sp_throughput_meas[0].u4_task_start;
        u4_t_ovrhd       = st_sp_throughput_meas[0].u4_ovrhd_cnt * u4_s_throughput_meas_ovrhd;
        u4_t_ovrhd     >>= THROUGHPUT_RSHFT_OVRHD_CAL;
        u4_t_ovrhd      += st_sp_throughput_meas[0].u4_ovrhd_frt;

        if(u4_t_throughput >= u4_t_ovrhd){
            u4_t_throughput -= u4_t_ovrhd;
            vd_g_ThroughputCfgTaskCapt(u2_a_TASK_ID, u4_t_throughput);
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_LT_OVRHD;
            u4_t_diff = u4_t_ovrhd - u4_t_throughput;
            if(u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] < u4_t_diff){
                u4_gp_throughput_errlog[THROUGHPUT_ERR_OVRHD_MAX] = u4_t_diff;
            }
        }
    }
    else{
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_UNKNWN;
    }

    vd_g_ThroughputCfg_EI(u4_t_gli);                                      /* Enable Interrupt  */
}
/*===================================================================================================================================*/
/*  U4      u4_g_Throughput_DI(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_Throughput_DI(void)
{
    volatile U4        u4_t_gli;
    volatile U4        u4_t_frt;
    U4                 u4_t_idepth;

    u4_t_gli = u4_g_ThroughputCfg_DI();

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth + (U4)1U;
    if(u4_t_idepth < (U4)THROUGHPUT_INTRPT_DEPTH){

        u4_s_throughput_idepth = u4_t_idepth;

        st_sp_throughput_meas[u4_t_idepth].u4_meas_start = u4_t_frt;
        st_sp_throughput_meas[u4_t_idepth].u4_task_start = u4_g_ThroughputCfgFrt();
    }
    else{
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }

    return(u4_t_gli);
}
/*===================================================================================================================================*/
/*  void    vd_g_Throughput_EI(const U4 u4_a_GLI, const U2 u2_a_CSC_ID)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Throughput_EI(const U4 u4_a_GLI, const U2 u2_a_CSC_ID)
{
    volatile U4        u4_t_frt;
    volatile U4        u4_t_meas_start;
    U4                 u4_t_throughput;
    U4                 u4_t_idepth;

    u4_t_frt = u4_g_ThroughputCfgFrt();

    u4_t_idepth = u4_s_throughput_idepth;
    if(u4_t_idepth >= (U4)THROUGHPUT_INTRPT_DEPTH){
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_OVF;
    }
    else if(u4_t_idepth > (U4)0U){

        u4_t_throughput = u4_t_frt - st_sp_throughput_meas[u4_t_idepth].u4_task_start;
        vd_g_ThroughputCfgCscCapt(u2_a_CSC_ID, u4_t_throughput);

        u4_t_meas_start = st_sp_throughput_meas[u4_t_idepth].u4_meas_start;
        u4_t_idepth--;
        u4_s_throughput_idepth = u4_t_idepth;
        if(st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt < (U4)U2_MAX){
            st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_cnt++;
        }
        else{
            u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_OVRHD_CNT_OVF;
        }

        /* over head for lower task */
        u4_t_frt = (u4_g_ThroughputCfgFrt() - u4_t_meas_start) - u4_t_throughput;
        st_sp_throughput_meas[u4_t_idepth].u4_ovrhd_frt += u4_t_frt; 
    }
    else{   
        u4_gp_throughput_errlog[THROUGHPUT_ERR_STSBIT] |= (U4)THROUGHPUT_ERRBIT_IDEPTH_UDF;
    }

    vd_g_ThroughputCfg_EI(u4_a_GLI);
}
/*===================================================================================================================================*/
/*  void    vd_g_Throughput_vd_Fvd(void (* const * fp_ap_vd_Fvd)(void), const U2 u2_a_NC, const U2 u2_a_vd_FVD_ID)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Throughput_vd_Fvd(void (* const * fp_ap_vd_Fvd)(void), const U2 u2_a_NC, const U2 u2_a_vd_FVD_ID)
{
    volatile U4        u4_t_gli;

    U4                 u4_t_frt;
    U4                 u4_t_throughput;
    U2                 u2_t_lpcnt;

    vd_g_ThroughputCfg_vd_Fvd_Start(u2_a_vd_FVD_ID);

    for(u2_t_lpcnt = (U2)0U; u2_t_lpcnt < u2_a_NC; u2_t_lpcnt++){

        u4_t_gli = u4_g_ThroughputCfg_DI();                                   /* Disable Interrupt */
        u4_t_frt = u4_g_ThroughputCfgFrt();

        (*fp_ap_vd_Fvd[u2_t_lpcnt])();

        u4_t_throughput = u4_g_ThroughputCfgFrt() - u4_t_frt;
        vd_g_ThroughputCfg_EI(u4_t_gli);                                      /* Enable Interrupt  */

        vd_g_ThroughputCfg_vd_Fvd_Capt(u2_t_lpcnt, u4_t_throughput);
    }

    vd_g_ThroughputCfg_vd_Fvd_Finish(u2_a_vd_FVD_ID);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
#endif /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/29/2015  TN       New.                                                                                               */
/*  1.1.0     6/12/2015  TN       u2_g_ThroughputCfgCalcOvrhd() -> u2_g_ThroughputCfgMeasOvrhd()                                     */
/*                                u2_g_ThroughputCfgIrqOvrhd() was implemented instead of u4_g_THROUGHPUT_OVRHD_FRT_INTRPT.          */
/*  1.2.0     6/25/2015  TN       Volatile variables handling was optimized in order to prevent that compiler generates redundant    */
/*                                read/write instuctions.                                                                            */
/*  2.0.0    10/12/2015  TN       vd_g_ThroughputMainStart -> vd_g_ThroughputIdleStart.                                              */
/*                                vd_g_ThroughputMainFinish -> vd_g_ThroughputIdleFinish.                                            */
/*                                vd_g_ThroughputMainStart was modified in order to support scheduler v2.0.0.                        */
/*                                vd_g_ThroughputMainFinish was modified in order to support scheduler v2.0.0.                       */
/*  2.1.0     1/18/2016  TN       vd_g_Throughput_vd_Fvd, vd_g_ThroughputEcuToRun and vd_g_ThroughputEcuToShtdwn were implemented.   */
/*                                u4_THROUGHPUT_DI      -> u4_g_ThroughputCfg_DI                                                     */
/*                                vd_THROUGHPUT_EI      -> vd_g_ThroughputCfg_EI.                                                    */
/*                                u4_THROUGHPUT_GET_FRT -> u4_g_ThroughputCfgFrt                                                     */
/*  2.2.0     1/20/2016  TN       vd_g_ThroughputCrtclStart  -> u4_g_Throughput_DI                                                   */
/*                                vd_g_ThroughputCrtclFinish -> vd_g_Throughput_EI                                                   */
/*                                vd_g_ThroughputCfgIsrUpdt  -> vd_g_ThroughputCfgIsrCapt                                            */
/*                                vd_g_ThroughputCfgTaskUpdt -> vd_g_ThroughputCfgTaskCapt                                           */
/*                                vd_g_Throughput_vd_Fvd was redesigned and optimized.                                               */
/*  2.3.0     2/ 4/2016  TN       vd_g_ThroughputMainTask was implemented.                                                           */
/*  2.4.0     2/19/2016  TN       Bug Fix : u4_s_throughput_irq_ovrhd was added in throughput result for MainTask in                 */
/*                                vd_g_ThroughputMainFinish.                                                                         */
/*  2.4.1     9/ 7/2021  TN       "U" suffix were added into litterals because of MC3 Rule-7.2 compliance.                           */
/*                                NULL->vdp_PTR_NA.                                                                                  */
/*  2.5.0     9/15/2021  TN       u2_a_NC was defined in vd_g_Throughput_vd_Fvd because of MISAR-C Rule 18.1.                        */
/*  2.5.1    11/22/2023  KM       u4_g_ThroughputCfgFrt was moved to throughput_usrcfg.h.                                            */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KM   = Kazuyuki Makino, DENSO.                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
