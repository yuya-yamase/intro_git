/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PictMuteCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PICTMUTE_TASK_TIME                   (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_pictmute_cycchk_timer;                       /* PictMute Cycle Check Poling Timer */

static U1 u1_s_pictmute_siperror_flag;                      /* Sip Error flag */
static U1 u1_s_pictmute_camaeramute_flag;                   /* Camera Process MUTE Request Flag */
static U1 u1_s_pictmute_pmpsailerrn_pre_sts;                /* Previous PORT-PM-PSAIL-ERR-N Status */
static U1 u1_s_pictmute_vicrst_pre_sts;                     /* Previous /V-IC-RST Status */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_PictMute_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_PictMute_Init(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_Init(void)
{
    u2_s_pictmute_cycchk_timer = (U2)0;
    u1_s_pictmute_siperror_flag = (U1)FALSE;
    u1_s_pictmute_camaeramute_flag = (U1)FALSE;
    u1_s_pictmute_pmpsailerrn_pre_sts = (U1)PICTMUTE_IO_STS_LOW;
    u1_s_pictmute_vicrst_pre_sts = (U1)PICTMUTE_IO_STS_LOW;
}

/*===================================================================================================================================*/
/*  void    vd_g_PictMute_Routine(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_Routine(void)
{
    static const U2 PICTMUTE_CYCCHK_POLING = (U2)(20U / PICTMUTE_TASK_TIME);    /* PictMUTE Poling Check Time : 20ms */

    U1  u1_t_read_pmvmute_sts;                                                  /* Read PM-V-MUTE Status */
    U1  u1_t_read_dispreqgpio0_sts;                                             /* Read DISP-REQ-GPIO0 Status */
    U1  u1_t_read_pmapshold_sts;                                                /* Read PMA-PS-HOLD Status */
    U1  u1_t_read_sailerr1_sts;                                                 /* Read SAIL-ERR1 Status */
    U1  u1_t_read_sailerr2_sts;                                                 /* Read SAIL-ERR2 Status */
    U1  u1_t_read_pmpsailerrn_sts;                                              /* Read PORT-PM-PSAIL-ERR-N Status */
    U1  u1_t_read_vicrst_sts;                                                   /* Read /V-IC-RST Status */
    U1  u1_t_cyc_time_chk_flg;

    u1_t_cyc_time_chk_flg = u1_s_PictMute_TimChk(u2_s_pictmute_cycchk_timer, PICTMUTE_CYCCHK_POLING);
    if(u1_t_cyc_time_chk_flg == (U1)TRUE){
        u2_s_pictmute_cycchk_timer = (U2)0;
        u1_t_read_pmvmute_sts = u1_PICTMUTE_GET_PM_V_MUTE();
        u1_t_read_dispreqgpio0_sts = u1_PICTMUTE_GET_DISP_REQ_GPIO0();
        u1_t_read_pmapshold_sts = u1_PICTMUTE_GET_PMA_PS_HOLD();
        u1_t_read_sailerr1_sts = u1_PICTMUTE_GET_SAIL_ERR1();
        u1_t_read_sailerr2_sts = u1_PICTMUTE_GET_SAIL_ERR2();
        u1_t_read_pmpsailerrn_sts = u1_PICTMUTE_GET_PORT_PM_PSAIL_ERR_N();
        u1_t_read_vicrst_sts = u1_PICTMUTE_GET_V_IC_RST();

        /* Sip Error Check */
        if(u1_t_read_dispreqgpio0_sts == (U1)PICTMUTE_IO_STS_LOW){
            /* MUTE ON Check */
            if((u1_t_read_pmapshold_sts == (U1)PICTMUTE_IO_STS_LOW)
            || ((u1_t_read_sailerr1_sts != (U1)PICTMUTE_IO_STS_HIGH) || (u1_t_read_sailerr2_sts != (U1)PICTMUTE_IO_STS_LOW))
            || ((u1_t_read_pmpsailerrn_sts == (U1)PICTMUTE_IO_STS_HIGH) && (u1_s_pictmute_pmpsailerrn_pre_sts == (U1)PICTMUTE_IO_STS_LOW))){
                u1_s_pictmute_siperror_flag = (U1)TRUE;
            }

            /* MUTE OFF Check */
            if(((u1_t_read_pmpsailerrn_sts == (U1)PICTMUTE_IO_STS_LOW) && (u1_s_pictmute_pmpsailerrn_pre_sts == (U1)PICTMUTE_IO_STS_HIGH))
            || ((u1_t_read_vicrst_sts == (U1)PICTMUTE_IO_STS_LOW) && (u1_s_pictmute_vicrst_pre_sts == (U1)PICTMUTE_IO_STS_HIGH))){
                u1_s_pictmute_siperror_flag = (U1)FALSE;
            }
        }
        else{
            u1_s_pictmute_siperror_flag = (U1)FALSE;
        }

        /* PM-V-MUTE Update */
        if((u1_s_pictmute_siperror_flag == (U1)TRUE)
        || (u1_s_pictmute_camaeramute_flag == (U1)TRUE)){
            if(u1_t_read_pmvmute_sts == (U1)PICTMUTE_IO_STS_LOW){
                u1_PICTMUTE_SET_PM_V_MUTE_H();
            }
        }
        else{                                                                   /* Sip Error Flag All OFF */
            if(u1_t_read_pmvmute_sts == (U1)PICTMUTE_IO_STS_HIGH){
                u1_PICTMUTE_SET_PM_V_MUTE_L();
            }
        }

        u1_s_pictmute_pmpsailerrn_pre_sts = u1_t_read_pmpsailerrn_sts;
        u1_s_pictmute_vicrst_pre_sts = u1_t_read_vicrst_sts;
    }
    else{
        u2_s_pictmute_cycchk_timer++;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_PictMute_TimChk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_PictMute_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void  vd_g_PictMute_CamMuteReq(const U1 u1_a_mute_sts)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      v  :  MUTE_OFF(FALSE) /  MUTE_ON(TRUE)                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_PictMute_CamMuteReq(const U1 u1_a_req_sts)
{
    u1_s_pictmute_camaeramute_flag = u1_a_req_sts;
}
