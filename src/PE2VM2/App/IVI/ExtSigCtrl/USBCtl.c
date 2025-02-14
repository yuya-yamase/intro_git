/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "USBCtl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define USB_TASK_TIME                   (1U)

#define USB_DETECT_STS_SAMPLING_CNT     (6U)
#define USB_DETECT_ADVAL_CONECT         (0x0C8D)
#define USB_DETECT_ADVAL_DISCONECT      (0x0444)

#define USB_PD_MOVEAVE_STEP0            (0U)
#define USB_PD_MOVEAVE_STEP1            (1U)

#define USB_PD_BUF_NUM                  (10U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_usb_detect_cycchk_timer;                     /* USB Detect Cycle Check Poling Timer */
static U2 u2_s_usb_pd_cycchk_timer;                         /* USB Power Delivery Cycle Check Poling Timer */

static U1 u1_s_usb_detect_pre_sts;                          /* Previous USB-ADP-DET Status */
static U1 u1_s_usb_detect_sts_cnt;                          /* USB-ADP-DET Status Sampling Counter */
static U1 u1_s_usb_pd_moveave_sts;                          /* USB-CURRENT-DET Moving Average Status */
static U2 u2_s_usb_pd_det_val_buf[USB_PD_BUF_NUM];          /* USB-CURRENT-DET Status Sampling Buffer */
static U1 u1_s_usb_pd_sts_cnt;                              /* USB-CURRENT-DET Status Sampling Counter */
static U4 u4_s_usb_pd_val_sum;                              /* USB-CURRENT-DET Value Sum */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_Usb_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_Usb_Pd_MoveAve(U2 u2_a_cur_det_val);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_Usb_Init(void)                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Usb_Init(void)
{
    U1 u1_t_cnt;

    u2_s_usb_detect_cycchk_timer = (U2)0;
    u2_s_usb_pd_cycchk_timer = (U2)0;
    u1_s_usb_detect_pre_sts = (U1)USB_DETECT_STS_UNDET;
    u1_s_usb_detect_sts_cnt = (U1)0;
    u1_s_usb_pd_moveave_sts = (U1)USB_PD_MOVEAVE_STEP0;
    for(u1_t_cnt =0; u1_t_cnt < (U1)USB_PD_BUF_NUM; u1_t_cnt++){
        u2_s_usb_pd_det_val_buf[u1_t_cnt] = (U2)0;
    }
    u1_s_usb_pd_sts_cnt = (U1)0;
    u4_s_usb_pd_val_sum = (U4)0;
}

/*===================================================================================================================================*/
/*  void    vd_g_Usb_Routine(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Usb_Routine(void)
{
    static const U2 USB_DETECT_CYCCHK_POLING = (U2)(50U / USB_TASK_TIME);       /* USB-ADP-DET Poling Check Time t3 : 50ms */
    static const U2 USB_PD_CYCCHK_POLING = (U2)(50U / USB_TASK_TIME);           /* USB-CURRENT-DET Poling Check Time t3 : 50ms */

    U1  u1_t_read_adc_sts;                                                      /* Read A/D Change Status */
    U1  u1_t_adp_det_sts;                                                       /* USB-ADP-DET Status */
    U2  u2_t_adp_det_val;                                                       /* USB-ADP-DET A/D Value */
    U1  u1_t_v33_peri_on_sts;                                                   /* V33-Peri-On Port Status */
    U2  u2_t_cur_det_val;                                                       /* USB-CURRENT-DET A/D Value */
    U1  u1_t_cyc_time_chk_flg;

    u1_t_cyc_time_chk_flg = u1_s_Usb_TimChk(u2_s_usb_detect_cycchk_timer, USB_DETECT_CYCCHK_POLING);
    if(u1_t_cyc_time_chk_flg == (U1)TRUE){
        u2_s_usb_detect_cycchk_timer = (U2)0;
        u1_t_read_adc_sts = u1_USB_GET_ADP_DET(&u2_t_adp_det_val); 
        if(u1_t_read_adc_sts == (U1)TRUE){
            if(u2_t_adp_det_val >= (U2)USB_DETECT_ADVAL_CONECT){
                u1_t_adp_det_sts = (U1)USB_DETECT_STS_CONECT;
            }
            else if(u2_t_adp_det_val >= (U2)USB_DETECT_ADVAL_DISCONECT){
                u1_t_adp_det_sts = (U1)USB_DETECT_STS_DISCONECT;
            }
            else{
                u1_t_adp_det_sts = (U1)USB_DETECT_STS_SHORT;
            }

            if(u1_t_adp_det_sts != u1_s_usb_detect_pre_sts){
                u1_s_usb_detect_sts_cnt = (U1)1;
            }
            else{
                if(u1_s_usb_detect_sts_cnt < (U1)U1_MAX){
                     u1_s_usb_detect_sts_cnt++;
                }
            }
            u1_s_usb_detect_pre_sts = u1_t_adp_det_sts;

            if(u1_s_usb_detect_sts_cnt >= (U2)USB_DETECT_STS_SAMPLING_CNT){
                u1_USB_OSCMD_EXTSIG_USB(u1_t_adp_det_sts);
            }
        }
    }
    else{
        u2_s_usb_detect_cycchk_timer++;
    }

    u1_t_v33_peri_on_sts = u1_USB_GET_V33_PERI_ON();
    if(u1_t_v33_peri_on_sts == (U1)TRUE){
        u1_t_cyc_time_chk_flg = u1_s_Usb_TimChk(u2_s_usb_pd_cycchk_timer, USB_PD_CYCCHK_POLING);
        if(u1_t_cyc_time_chk_flg == (U1)TRUE){
            u2_s_usb_pd_cycchk_timer = (U2)0;
            u1_t_read_adc_sts = u1_USB_GET_CUR_DET(&u2_t_cur_det_val); 
            if(u1_t_read_adc_sts == (U1)TRUE){
                vd_s_Usb_Pd_MoveAve(u2_t_cur_det_val);
            }
        }
        else{
            u2_s_usb_pd_cycchk_timer++;
        }
    }
    else{
        u2_s_usb_pd_cycchk_timer = (U2)0;
        u1_s_usb_pd_sts_cnt = (U1)0;
        u4_s_usb_pd_val_sum = (U4)0;
        /* Process Reset */
        u1_s_usb_pd_moveave_sts = (U1)USB_PD_MOVEAVE_STEP0;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_Usb_TimChk(void)                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Usb_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_Usb_Pd_MoveAve(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_cur_det_val  :  USB-CURRENT-DET A/D Value                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Usb_Pd_MoveAve(U2 u2_a_cur_det_val)
{
    switch (u1_s_usb_pd_moveave_sts){
        case USB_PD_MOVEAVE_STEP0:                                                  /* STEP0 */
            if(u1_s_usb_pd_sts_cnt < (U1)USB_PD_BUF_NUM){
                /* Input Value Sum */
                u4_s_usb_pd_val_sum += (U4)u2_a_cur_det_val;
                /* Input Buffer */
                u2_s_usb_pd_det_val_buf[u1_s_usb_pd_sts_cnt] = u2_a_cur_det_val;
            }
            else{                                                                   /* Counter Fail */
                u1_s_usb_pd_sts_cnt = (U1)0;
                u4_s_usb_pd_val_sum = (U4)0;
            }

            if(u1_s_usb_pd_sts_cnt == (U1)((U1)USB_PD_BUF_NUM - (U1)1U)){
                u1_USB_OSCMD_USB_PD((U4)(u4_s_usb_pd_val_sum / (U4)USB_PD_BUF_NUM));
                /* Next Process */
                u1_s_usb_pd_moveave_sts = (U1)USB_PD_MOVEAVE_STEP1;
            }
            else{
                u1_s_usb_pd_sts_cnt++;
            }
            break;
        case USB_PD_MOVEAVE_STEP1:                                                  /* STEP1 */
            if(u1_s_usb_pd_sts_cnt < (U1)USB_PD_BUF_NUM){
                if(u1_s_usb_pd_sts_cnt == (U1)((U1)USB_PD_BUF_NUM - (U1)1U)){
                    u1_s_usb_pd_sts_cnt = (U1)0;
                    u4_s_usb_pd_val_sum -= (U4)u2_s_usb_pd_det_val_buf[u1_s_usb_pd_sts_cnt];
                    u4_s_usb_pd_val_sum += (U4)u2_a_cur_det_val;
                    u2_s_usb_pd_det_val_buf[u1_s_usb_pd_sts_cnt] = u2_a_cur_det_val;

                    u1_USB_OSCMD_USB_PD((U4)(u4_s_usb_pd_val_sum / (U4)USB_PD_BUF_NUM));
                }
                else{
                    u1_s_usb_pd_sts_cnt++;
                    u4_s_usb_pd_val_sum -= (U4)u2_s_usb_pd_det_val_buf[u1_s_usb_pd_sts_cnt];
                    u4_s_usb_pd_val_sum += (U4)u2_a_cur_det_val;
                    u2_s_usb_pd_det_val_buf[u1_s_usb_pd_sts_cnt] = u2_a_cur_det_val;

                    u1_USB_OSCMD_USB_PD((U4)(u4_s_usb_pd_val_sum / (U4)USB_PD_BUF_NUM));
                }
            }
            else{                                                                   /* Counter Fail */
                u1_s_usb_pd_sts_cnt = (U1)0;
                u4_s_usb_pd_val_sum = (U4)0;
                /* Process Reset */
                u1_s_usb_pd_moveave_sts = (U1)USB_PD_MOVEAVE_STEP0;
            }
            break;
        default:                                                                    /* FAIL */
            u1_s_usb_pd_sts_cnt = (U1)0;
            u4_s_usb_pd_val_sum = (U4)0;
            /* Process Reset */
            u1_s_usb_pd_moveave_sts = (U1)USB_PD_MOVEAVE_STEP0;
            break;
    }
}
