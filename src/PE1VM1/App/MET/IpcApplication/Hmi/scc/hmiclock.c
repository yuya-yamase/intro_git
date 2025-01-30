/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmiclock                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMICLOCK_C_MAJOR                         (2)
#define HMICLOCK_C_MINOR                         (0)
#define HMICLOCK_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmiclock.h"
#include "datesi_tim.h"

#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMICLOCK_C_MAJOR != HMICLOCK_H_MAJOR) || \
     (HMICLOCK_C_MINOR != HMICLOCK_H_MINOR) || \
     (HMICLOCK_C_PATCH != HMICLOCK_H_PATCH))
#error "hmiclock.c and hmiclock.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMI_CLOCK_BUFNUM             (1U)

#define HMI_CLOCK_BITMASK            (0x03U)
#define HMI_CLOCK_CUTMSTART_BITSFT   (10U)
#define HMI_CLOCK_CUTMEND_BITSFT     (12U)
#define HMI_CLOCK_HOURUP_BITSFT      (14U)
#define HMI_CLOCK_HOURDOWN_BITSFT    (16U)
#define HMI_CLOCK_MINUP_BITSFT       (18U)
#define HMI_CLOCK_MINDOWN_BITSFT     (20U)
#define HMI_CLOCK_ADJUST_BITSFT      (22U)

#define HMICLOCK_REQ                 (1U)

#define HMICLOCK_VAL                 (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_hmiclock_start_pre;
static U1   u1_s_hmiclock_end_pre;
static U1   u1_s_hmiclock_hourup_pre;
static U1   u1_s_hmiclock_hourdown_pre;
static U1   u1_s_hmiclock_minup_pre;
static U1   u1_s_hmiclock_mindown_pre;
static U1   u1_s_hmiclock_timzero_pre;
static U4   u4_s_hmiclock_cstmbuf[HMI_CLOCK_BUFNUM];

static U1   u1_s_hmiclock_cstmflag;
static U2   u2_s_hmiclock_to;
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
/*  void    vd_g_HmiClockInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiClockInit(void)
{
    U4 u4_t_loop;    /* loop counter */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_CLOCK_BUFNUM ; u4_t_loop++){
        u4_s_hmiclock_cstmbuf[u4_t_loop] = (U4)0U;
    }

    u1_s_hmiclock_start_pre    = (U1)0U;
    u1_s_hmiclock_end_pre      = (U1)0U;
    u1_s_hmiclock_hourup_pre   = (U1)0U;
    u1_s_hmiclock_hourdown_pre = (U1)0U;
    u1_s_hmiclock_minup_pre    = (U1)0U;
    u1_s_hmiclock_mindown_pre  = (U1)0U;
    u1_s_hmiclock_timzero_pre  = (U1)0U;

    u1_s_hmiclock_cstmflag     = (U1)FALSE;
    u2_s_hmiclock_to           = (U2)HMIPROXY_TOC_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiClockMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiClockMainTask(void)
{
    U1              u1_t_hmiclock_start;
    U1              u1_t_hmiclock_end;
    U1              u1_t_hmiclock_hourup;
    U1              u1_t_hmiclock_hourdown;
    U1              u1_t_hmiclock_minup;
    U1              u1_t_hmiclock_mindown;
    U1              u1_t_hmiclock_timzero;
    U2              u2_t_swcnt;
    U1              u1_t_kind;
    U1              u1_t_sts;

    static const U2 u2_s_HMICLOCK_ID_CLOCK = (U2)RIMID_U2_DS_22_10A7_MM_MET_TIMING;
    static const U2 u2_s_HMICLOCK_TO = (U2)1000U / (U2)20U;
    U1              u1_t_to;

    u1_t_hmiclock_start     = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_CUTMSTART_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_end       = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_CUTMEND_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_hourup    = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_HOURUP_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_hourdown  = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_HOURDOWN_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_minup     = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_MINUP_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_mindown   = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_MINDOWN_BITSFT) & (U4)HMI_CLOCK_BITMASK); 
    u1_t_hmiclock_timzero   = (U1)((u4_s_hmiclock_cstmbuf[0] >> HMI_CLOCK_ADJUST_BITSFT) & (U4)HMI_CLOCK_BITMASK); 

    u1_t_to = u1_g_HmiProxyToc(&u2_s_hmiclock_to, u2_s_HMICLOCK_TO);
    u2_t_swcnt = (U2)0U;

    if(u1_t_to == (U1)FALSE){

        if((u1_s_hmiclock_start_pre != u1_t_hmiclock_start) &&
           (u1_t_hmiclock_start     == (U1)HMICLOCK_REQ   ))   {
            vd_g_DateSITimAdjustStart();
            u1_s_hmiclock_cstmflag = (U1)TRUE;
        }

        if((u1_s_hmiclock_end_pre != u1_t_hmiclock_end  ) &&
           (u1_t_hmiclock_end     == (U1)HMICLOCK_REQ   ))   {
            vd_g_DateSITimAdjustEnd();
            u1_s_hmiclock_cstmflag = (U1)FALSE;
        }

        if((u1_s_hmiclock_timzero_pre != u1_t_hmiclock_timzero) &&
           (u1_t_hmiclock_timzero     == (U1)HMICLOCK_REQ     ))   {
            vd_g_DateSITimZeroRstReq();
            u1_t_sts  = u1_g_Rim_ReadU2withStatus(u2_s_HMICLOCK_ID_CLOCK , &u2_t_swcnt);
            u1_t_kind = u1_t_sts & (U1)RIM_RESULT_KIND_MASK;
            if ((u1_t_kind == (U1)RIM_RESULT_KIND_OK) &&
                (u2_t_swcnt < (U2)U2_MAX            ))  {
                u2_t_swcnt++;
                vd_g_Rim_WriteU2(u2_s_HMICLOCK_ID_CLOCK, u2_t_swcnt);
           }
        }

        if(u1_s_hmiclock_cstmflag == (U1)TRUE){

            if((u1_s_hmiclock_hourup_pre != (U1)u1_t_hmiclock_hourup) &&
               (u1_t_hmiclock_hourup     == (U1)HMICLOCK_REQ        ))   {
                vd_g_DateSITimAdjustReq((U1)DATESI_TIM_RNK_HUR, (U1)HMICLOCK_VAL, (U1)DATESI_TIM_ADJ_PLUS);
                vd_g_DateSITimAdjustUpdate();
            }else if((u1_s_hmiclock_hourdown_pre != u1_t_hmiclock_hourdown) &&
               (u1_t_hmiclock_hourdown     == (U1)HMICLOCK_REQ            ))   {
                vd_g_DateSITimAdjustReq((U1)DATESI_TIM_RNK_HUR, (U1)HMICLOCK_VAL, (U1)DATESI_TIM_ADJ_MINUS);
                vd_g_DateSITimAdjustUpdate();
            }else if((u1_s_hmiclock_minup_pre != u1_t_hmiclock_minup) &&
               (u1_t_hmiclock_minup     == (U1)HMICLOCK_REQ         ))   {
                vd_g_DateSITimAdjustReq((U1)DATESI_TIM_RNK_MIN, (U1)HMICLOCK_VAL, (U1)DATESI_TIM_ADJ_PLUS);
                vd_g_DateSITimAdjustUpdate();
            }else if((u1_s_hmiclock_mindown_pre != u1_t_hmiclock_mindown) &&
               (u1_t_hmiclock_mindown     == (U1)HMICLOCK_REQ           ))   {
                vd_g_DateSITimAdjustReq((U1)DATESI_TIM_RNK_MIN, (U1)HMICLOCK_VAL, (U1)DATESI_TIM_ADJ_MINUS);
                vd_g_DateSITimAdjustUpdate();
            }else{
                /* Do Nothing */
            }

        }

    }

    u1_s_hmiclock_start_pre    = u1_t_hmiclock_start;
    u1_s_hmiclock_end_pre      = u1_t_hmiclock_end;
    u1_s_hmiclock_hourup_pre   = u1_t_hmiclock_hourup;
    u1_s_hmiclock_hourdown_pre = u1_t_hmiclock_hourdown;
    u1_s_hmiclock_minup_pre    = u1_t_hmiclock_minup;
    u1_s_hmiclock_mindown_pre  = u1_t_hmiclock_mindown;
    u1_s_hmiclock_timzero_pre  = u1_t_hmiclock_timzero;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiClockPut(const U4 * u4_ap_REQ)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiClockPut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;    /* loop counter */

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_CLOCK_BUFNUM ; u4_t_loop++){
            u4_s_hmiclock_cstmbuf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
    u2_s_hmiclock_to   = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2019  TA       New.                                                                                               */
/*  1.1.0    09/02/2020  TA       See hmiproxy.c                                                                                     */
/*  2.0.0    06/22/2021  TH       Change for clock custmize by meter.                                                                */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
