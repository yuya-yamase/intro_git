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
#define PICTMUTE_MUTEHI_VEHPOW               (0x01U)
#define PICTMUTE_MUTEHI_SIPERR               (0x02U)
#define PICTMUTE_MUTEHI_CAMERA               (0x04U)
#define PICTMUTE_MUTEHI_OTARST               (0x08U)
#define PICTMUTE_MUTEHI_VMRST                (0x10U)
#define PICTMUTE_MUTELO_VICRST               (~(PICTMUTE_MUTEHI_VEHPOW | PICTMUTE_MUTEHI_SIPERR | PICTMUTE_MUTEHI_CAMERA | PICTMUTE_MUTEHI_OTARST))
#define PICTMUTE_MUTELO_PMAPSHOLD            (~PICTMUTE_MUTEHI_SIPERR)
#define PICTMUTE_MUTELO_CAMERA               (~PICTMUTE_MUTEHI_CAMERA)
#define PICTMUTE_MUTELO_VMRST                (~PICTMUTE_MUTEHI_VMRST)
#define PICTMUTE_MUTESET_MASK                (PICTMUTE_MUTEHI_VEHPOW | PICTMUTE_MUTEHI_SIPERR | PICTMUTE_MUTEHI_CAMERA | PICTMUTE_MUTEHI_OTARST | PICTMUTE_MUTEHI_VMRST)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PICTMUTE_TASK_TIME                   (1U)
#define PICTMUTE_OSCMD_SOC_BOOT_COMPLETE     (0x04U) /* SoC boot completed */
#define PICTMUTE_OSCMD_SOC_VM_RESET          (0x05U) /* SoC VM resetting */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_pictmute_cycchk_timer;                       /* PictMute Cycle Check Poling Timer */

static U1 u1_s_pictmute_mute_signal;                        /* MUTE ON/OFF Setting Signal */
static U1 u1_s_pictmute_pmapshold_pre_sts;                  /* Previous PMA_PS_HOLD Status */
static U1 u1_s_pictmute_pre_soc_ope_sts;                    /* Previous SoC Operation Reqest Status */

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
    u2_s_pictmute_cycchk_timer = (U2)0U;
    u1_s_pictmute_mute_signal = (U1)0x00U;
    u1_s_pictmute_pmapshold_pre_sts = (U1)PICTMUTE_IO_STS_LOW;
    u1_s_pictmute_pre_soc_ope_sts = (U1)0x00U;
}

/*===================================================================================================================================*/
/*  void    vd_g_PictMute_Routine(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_Routine(void)
{
    static const U2 PICTMUTE_CYCCHK_POLING = (U2)(1U / PICTMUTE_TASK_TIME);    /* PictMUTE Poling Check Time : 1ms */

    U1  u1_t_read_vehpowstt_sts;                                                /* Read Vehicle Power State Status */
    U1  u1_t_read_pmapshold_sts;                                                /* Read PMA-PS-HOLD Status */
    U1  u1_t_read_vicrst_sts;                                                   /* Read /V-IC-RST Status */
    U1  u1_t_cyc_time_chk_flg;

    u1_t_cyc_time_chk_flg = u1_s_PictMute_TimChk(u2_s_pictmute_cycchk_timer, PICTMUTE_CYCCHK_POLING);
    if(u1_t_cyc_time_chk_flg == (U1)TRUE){
        u2_s_pictmute_cycchk_timer = (U2)0U;
        u1_t_read_vehpowstt_sts = u1_PICTMUTE_GET_VEHPOWSTT();
        u1_t_read_pmapshold_sts = u1_PICTMUTE_GET_PMA_PS_HOLD();
        u1_t_read_vicrst_sts = u1_PICTMUTE_GET_V_IC_RST();

        /* MUTE ON Check */
        if((u1_t_read_vehpowstt_sts == (U1)PICTMUTE_VEHPOWSTT_PARKING)
        || (u1_t_read_vehpowstt_sts == (U1)PICTMUTE_VEHPOWSTT_EDS)){
            u1_s_pictmute_mute_signal |= (U1)PICTMUTE_MUTEHI_VEHPOW;
        }

        /* MUTE OFF Check */
        if((u1_t_read_pmapshold_sts == (U1)PICTMUTE_IO_STS_HIGH)
        && (u1_s_pictmute_pmapshold_pre_sts == (U1)PICTMUTE_IO_STS_LOW)){
            u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTELO_PMAPSHOLD;
        }
#if 0   /* temporary */
        if(u1_t_read_vicrst_sts == (U1)PICTMUTE_IO_STS_LOW){
            u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTELO_VICRST;
        }
#else
        if((u1_t_read_vehpowstt_sts != (U1)POWER_MODE_STATE_PARK) &&
           (u1_t_read_vehpowstt_sts != (U1)POWER_MODE_STATE_EDS)){
            u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTELO_VICRST;
        }
#endif  /* temporary */

        /* PM-V-MUTE Update */
        u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTESET_MASK;
        if(u1_s_pictmute_mute_signal != (U1)0x00U){
            vd_PICTMUTE_SET_PM_V_MUTE_H();
        }
        else{
            vd_PICTMUTE_SET_PM_V_MUTE_L();
        }
        u1_s_pictmute_pmapshold_pre_sts = u1_t_read_pmapshold_sts;
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
/*  void    vd_g_PictMute_CamMuteReq(const U1 u1_a_req_sts)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  MUTE_OFF(FALSE) /  MUTE_ON(TRUE)                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_CamMuteReq(const U1 u1_a_req_sts)
{
    if(u1_a_req_sts == (U1)TRUE){
        u1_s_pictmute_mute_signal |= (U1)PICTMUTE_MUTEHI_CAMERA;
    }
    else{
        u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTELO_CAMERA;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_PictMute_SipResetReq(const U1 u1_a_req_sts)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  MUTE_OFF(FALSE) /  MUTE_ON(TRUE)                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_SipResetReq(const U1 u1_a_req_sts)
{
    if(u1_a_req_sts == (U1)TRUE){
        u1_s_pictmute_mute_signal |= (U1)PICTMUTE_MUTEHI_SIPERR;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_PictMute_CdcResetReq(const U1 u1_a_req_sts)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  MUTE_OFF(FALSE) /  MUTE_ON(TRUE)                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_CdcResetReq(const U1 u1_a_req_sts)
{
    if(u1_a_req_sts == (U1)TRUE){
        u1_s_pictmute_mute_signal |= (U1)PICTMUTE_MUTEHI_OTARST;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_PictMute_VmResetReq(const U1 u1_a_req_sts)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  MUTE_OFF(FALSE) /  MUTE_ON(TRUE)                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_VmResetReq(const U1 u1_a_req_sts)
{
    if(u1_a_req_sts == (U1)TRUE){
        u1_s_pictmute_mute_signal |= (U1)PICTMUTE_MUTEHI_VMRST;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_PictMute_SoCResetReq    ( U1 u1_a_req_sts)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_socreq  :                                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PictMute_SoCResetReq(U1 u1_a_socreq)
{
    /* Trigger only on transition: "SoC VM resetting" -> "SoC boot completed" */
    if ((u1_s_pictmute_pre_soc_ope_sts == PICTMUTE_OSCMD_SOC_VM_RESET) &&
        (u1_a_socreq                   == PICTMUTE_OSCMD_SOC_BOOT_COMPLETE))
    {
        u1_s_pictmute_mute_signal &= (U1)PICTMUTE_MUTELO_VMRST;
    }
    /* Update previous state for edge detection */
    u1_s_pictmute_pre_soc_ope_sts = u1_a_socreq;
}
