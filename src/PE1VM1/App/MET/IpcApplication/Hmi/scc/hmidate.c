/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmidate                                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIDATE_C_MAJOR                         (1)
#define HMIDATE_C_MINOR                         (0)
#define HMIDATE_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiproxy_cfg_private.h"
#include "hmidate.h"
#include "datesi_cal.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIDATE_C_MAJOR != HMIDATE_H_MAJOR) || \
     (HMIDATE_C_MINOR != HMIDATE_H_MINOR) || \
     (HMIDATE_C_PATCH != HMIDATE_H_PATCH))
#error "hmidate.c and hmidate.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMI_DATE_BUFNUM             (1U)

#define HMI_DATE_BITMASK            (0x03U)
#define HMI_DATE_CUTMSTART_BITSFT   (18U)
#define HMI_DATE_CUTMEND_BITSFT     (20U)
#define HMI_DATE_YEARUP_BITSFT      (6U)
#define HMI_DATE_YEARDOWN_BITSFT    (8U)
#define HMI_DATE_MONTHUP_BITSFT     (10U)
#define HMI_DATE_MONTHDOWN_BITSFT   (12U)
#define HMI_DATE_DAYUP_BITSFT       (14U)
#define HMI_DATE_DAYDOWN_BITSFT     (16U)
#define HMI_DATE_UPDATE_BITSFT      (22U)

#define HMIDATE_NONREQ              (0U)
#define HMIDATE_REQ                 (1U)

#define HMIDATE_VAL                 (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_hmidate_start_pre;
static U1   u1_s_hmidate_end_pre;
static U1   u1_s_hmidate_yearup_pre;
static U1   u1_s_hmidate_yeardown_pre;
static U1   u1_s_hmidate_monthup_pre;
static U1   u1_s_hmidate_monthdown_pre;
static U1   u1_s_hmidate_dayup_pre;
static U1   u1_s_hmidate_daydown_pre;
static U4   u4_s_hmidate_cstmbuf[HMI_DATE_BUFNUM];
static U1   u1_s_hmidate_update_pre;

static U2   u2_s_hmidate_to;
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
/*  void    vd_g_HmiDateInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiDateInit(void)
{
    U4 u4_t_loop;    /* loop counter */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_DATE_BUFNUM ; u4_t_loop++){
        u4_s_hmidate_cstmbuf[u4_t_loop] = (U4)0U;
    }

    u1_s_hmidate_start_pre      = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_end_pre        = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_yearup_pre     = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_yeardown_pre   = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_monthup_pre    = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_monthdown_pre  = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_dayup_pre      = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_daydown_pre    = (U1)HMIDATE_NONREQ;
    u1_s_hmidate_update_pre     = (U1)HMIDATE_NONREQ;

    u2_s_hmidate_to             = (U2)HMIPROXY_TOC_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiDateMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiDateMainTask(void)
{
    static const U2 u2_s_HMIDATE_TO = (U2)50U;                                       /* Timeout is 1000ms/20ms;                      */

    U1              u1_t_hmidate_start;
    U1              u1_t_hmidate_end;
    U1              u1_t_hmidate_yearup;
    U1              u1_t_hmidate_yeardown;
    U1              u1_t_hmidate_monthup;
    U1              u1_t_hmidate_monthdown;
    U1              u1_t_hmidate_dayup;
    U1              u1_t_hmidate_daydown;
    U1              u1_t_himidate_update;
    U1              u1_t_to;

    u1_t_hmidate_start     = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_CUTMSTART_BITSFT) & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_end       = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_CUTMEND_BITSFT)   & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_yearup    = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_YEARUP_BITSFT)    & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_yeardown  = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_YEARDOWN_BITSFT)  & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_monthup   = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_MONTHUP_BITSFT)   & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_monthdown = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_MONTHDOWN_BITSFT) & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_dayup     = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_DAYUP_BITSFT)     & (U4)HMI_DATE_BITMASK);
    u1_t_hmidate_daydown   = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_DAYDOWN_BITSFT)   & (U4)HMI_DATE_BITMASK);
    u1_t_himidate_update   = (U1)((u4_s_hmidate_cstmbuf[0] >> HMI_DATE_UPDATE_BITSFT)    & (U4)HMI_DATE_BITMASK);

    u1_t_to                = u1_g_HmiProxyToc(&u2_s_hmidate_to, u2_s_HMIDATE_TO);

    if(u1_t_to == (U1)FALSE){

        if((u1_s_hmidate_start_pre     != u1_t_hmidate_start)     &&
           (u1_t_hmidate_start         == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustStart();
        }

        if((u1_s_hmidate_update_pre    != u1_t_himidate_update)   &&
           (u1_t_himidate_update       == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustUpdate();
        }

        if((u1_s_hmidate_end_pre       != u1_t_hmidate_end)       &&
           (u1_t_hmidate_end           == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustEnd();
        }

        if((u1_s_hmidate_yearup_pre    != u1_t_hmidate_yearup)    &&
           (u1_t_hmidate_yearup        == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_YEAE, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_PLUS);
        }

        if((u1_s_hmidate_yeardown_pre  != u1_t_hmidate_yeardown)  &&
           (u1_t_hmidate_yeardown      == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_YEAE, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_MINUS);
        }

        if((u1_s_hmidate_monthup_pre   != u1_t_hmidate_monthup)   &&
           (u1_t_hmidate_monthup       == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_MONTH, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_PLUS);
        }

        if((u1_s_hmidate_monthdown_pre != u1_t_hmidate_monthdown) &&
           (u1_t_hmidate_monthdown     == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_MONTH, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_MINUS);
        }

        if((u1_s_hmidate_dayup_pre     != u1_t_hmidate_dayup)     &&
           (u1_t_hmidate_dayup         == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_DAY, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_PLUS);
        }

        if((u1_s_hmidate_daydown_pre   != u1_t_hmidate_daydown)   &&
           (u1_t_hmidate_daydown       == (U1)HMIDATE_REQ     )) {
            vd_g_DateSICalAdjustReq((U1)DATESI_CAL_RNK_DAY, (U1)HMIDATE_VAL,(U1)DATESI_CAL_ADJ_MINUS);
        }

    }

    u1_s_hmidate_start_pre      = u1_t_hmidate_start;
    u1_s_hmidate_end_pre        = u1_t_hmidate_end;
    u1_s_hmidate_yearup_pre     = u1_t_hmidate_yearup;
    u1_s_hmidate_yeardown_pre   = u1_t_hmidate_yeardown;
    u1_s_hmidate_monthup_pre    = u1_t_hmidate_monthup;
    u1_s_hmidate_monthdown_pre  = u1_t_hmidate_monthdown;
    u1_s_hmidate_dayup_pre      = u1_t_hmidate_dayup;
    u1_s_hmidate_daydown_pre    = u1_t_hmidate_daydown;
    u1_s_hmidate_update_pre     = u1_t_himidate_update;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiDatePut(const U4 * u4_ap_REQ)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiDatePut(const U4 * u4_ap_REQ)
{
    U4 u4_t_loop;                                                                    /* loop counter                                 */

    if(u4_ap_REQ != vdp_PTR_NA) {
        for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)HMI_DATE_BUFNUM ; u4_t_loop++){
            u4_s_hmidate_cstmbuf[u4_t_loop] = u4_ap_REQ[u4_t_loop];
        }
    }
    u2_s_hmidate_to   = (U2)HMIPROXY_TOC_INI;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/01/2022  ToK      New.                                                                                               */
/*                                                                                                                                   */
/*  * ToK  = Toru Kamishina, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
