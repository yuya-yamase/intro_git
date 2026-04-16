/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  ASIL Telltale Drawing Monitoring Check                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ASILCHK_C_MAJOR                         (1)
#define ASILCHK_C_MINOR                         (0)
#define ASILCHK_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "asilchk_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ASILCHK_C_MAJOR != ASILCHK_H_MAJOR) || \
     (ASILCHK_C_MINOR != ASILCHK_H_MINOR) || \
     (ASILCHK_C_PATCH != ASILCHK_H_PATCH))
#error "asilchk.c and asilchk.h : source and header files are inconsistent!"
#endif

#if ((ASILCHK_C_MAJOR != ASILCHK_CFG_H_MAJOR) || \
     (ASILCHK_C_MINOR != ASILCHK_CFG_H_MINOR) || \
     (ASILCHK_C_PATCH != ASILCHK_CFG_H_PATCH))
#error "asilchk.c and asilchk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Blink CRC compare state [OnDuty_flag | OffDuty_flag] */
#define ASILCHK_BLINKCHK_STS_OK      (0U)   /* [00b] OnDuty/OffDuty compare OK or not needed */
#define ASILCHK_BLINKCHK_STS_OFF_NG  (1U)   /* [01b] OnDuty compare OK, OffDuty waiting      */
#define ASILCHK_BLINKCHK_STS_ON_NG   (2U)   /* [10b] OnDuty waiting, OffDuty compare OK      */
#define ASILCHK_BLINKCHK_STS_BOTH_NG (3U)   /* [11b] OnDuty/OffDuty compare NG               */

/* CRC Compare result */
#define ASILCHK_CRCCOMP_NORMAL       (0U)   /* CRC compare normal */
#define ASILCHK_CRCCOMP_UNMATCH      (1U)   /* CRC compare fail */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_asilchk_startmaskcnt;

static U4   u4_s_asilchk_alivecnt_pre;
static U4   u4_s_asilchk_alivecnt_cur;
static U2   u2_s_asilchk_alivecnt_abjdgcnt;

static U4   u4_sp_asilchk_crc_val[ASILCHK_TT_NUM];
static U1   u1_sp_asilchk_crc_cyclechkcnt[ASILCHK_TT_NUM];
static U1   u1_sp_asilchk_crc_blink_sts[ASILCHK_TT_NUM];
static U2   u2_sp_asilchk_crc_abjdgcnt[ASILCHK_TT_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_AsilChkInit(void);
static void vd_s_AsilChkAliveCntFailChk(void);
static void vd_s_AsilChkCrcCompFailChk(void);
static U2   u2_s_AsilChkCrcFailCount(const U2 u2_a_ABJDGCNT_PRE, const U4   u4_a_CRCCOMP_RSLT);
static U1   u2_s_AsilChkCrcLightCompChk(const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL);
static U1   u2_s_AsilChkCrcBlinkCompChk(U1* const u1_ap_BLINK_STS, const U1 u1_a_CYCTIME,
                                        U1* const u1_ap_CYCLECHKCNT, const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL);
static void vd_s_AsilChkCrcBlinkCompClear(U1* const u1_ap_BLINK_STS, U1* const u1_ap_CYCLECHKCNT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AsilChkBonRstWkInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkBonRstWkInit(void)
{
    U4    u4_t_loop;
    
    vd_s_AsilChkInit();

    u2_s_asilchk_startmaskcnt = (U2)0U;
    u4_s_asilchk_alivecnt_cur = (U4)U4_MAX;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ASILCHK_TT_NUM; u4_t_loop++){
        u4_sp_asilchk_crc_val[u4_t_loop] = (U4)U4_MAX;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_AsilChkInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AsilChkInit(void)
{
    U4    u4_t_loop;

    vd_g_AsilChkCfgInit();

    u4_s_asilchk_alivecnt_pre       = (U4)U4_MAX;
    u2_s_asilchk_alivecnt_abjdgcnt  = (U2)ASILCHK_ALIVECNT_NGJDGTIM;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ASILCHK_TT_NUM; u4_t_loop++){
        u4_sp_asilchk_crc_val[u4_t_loop]          = (U4)U4_MAX;
        u1_sp_asilchk_crc_cyclechkcnt[u4_t_loop]  = (U1)0U;
        u1_sp_asilchk_crc_blink_sts[u4_t_loop]    = (U1)ASILCHK_BLINKCHK_STS_OK;
        u2_sp_asilchk_crc_abjdgcnt[u4_t_loop]     = (U2)ASILCHK_CRCCOMP_NGJDGTIM;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_AsilChkMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AsilChkMainTask(void)
{
    U1    u1_t_startmaskchk;

    u1_t_startmaskchk = u1_g_AsilChkCfgGetPowSts();
    if(u1_t_startmaskchk == (U1)FALSE) {
        /* SOC startup: Reset data */
        vd_s_AsilChkInit();
        /* SOC startup: Reset power-on mask counter */
        u2_s_asilchk_startmaskcnt = (U2)0U;
    }
    else if(u2_s_asilchk_startmaskcnt < (U2)ASILCHK_MASK_TIM) {
        /* Before power-on mask time elapsed: Reset data */
        vd_s_AsilChkInit();
        /* Before power-on mask time elapsed: Count power-on mask counter */
        if(u2_s_asilchk_startmaskcnt < (U2)U2_MAX) {
            u2_s_asilchk_startmaskcnt++;
        }
    }
    else {
        /* Alive Counter Fail Check */
        vd_s_AsilChkAliveCntFailChk();
        /* CRC Compare Fail Check */
        vd_s_AsilChkCrcCompFailChk();
        /* Update power-on mask counter */
        u2_s_asilchk_startmaskcnt = (U2)ASILCHK_MASK_TIM;
    }
}

/*===================================================================================================================================*/
/*  void   vd_g_AsilChkGetAliveCnt(const U4 u4_a_CNT)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 u4_a_CNT: alive counter                                                                                 */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_AsilChkGetAliveCnt(const U4 u4_a_CNT)
{
    u4_s_asilchk_alivecnt_cur = u4_a_CNT;
}

/*===================================================================================================================================*/
/*  void vd_g_AsilChkGetCrcVal(const U4 * u4_ap_CRCDATA, const U1 u1_a_BUFSIZE)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U4 * u4_ap_CRCDATA : crc status/value of each telltale                                                     */
/*                  const U1 u1_a_BUFSIZE    : buffer size of first argument                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_AsilChkGetCrcVal(const U4 * u4_ap_CRCDATA, const U1 u1_a_BUFSIZE)
{
    static const U4 u4_s_ASILCHK_VAL_OFFSET = (U4)1U;
    static const U4 u4_s_ASILCHK_PACK_DATA  = (U4)2U;
    U4              u4_t_loop;
    U4              u4_t_crcval_idx;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ASILCHK_TT_NUM; u4_t_loop++) {
        u4_t_crcval_idx = (u4_t_loop * u4_s_ASILCHK_PACK_DATA) + u4_s_ASILCHK_VAL_OFFSET;

        if(u4_t_crcval_idx < (U4)u1_a_BUFSIZE) {
            u4_sp_asilchk_crc_val[u4_t_loop] = u4_ap_CRCDATA[u4_t_crcval_idx];
        }
    }
}

/*===================================================================================================================================*/
/*  static void   vd_s_AsilChkAliveCntFailChk(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_AsilChkAliveCntFailChk(void)
{
    if(u4_s_asilchk_alivecnt_pre != u4_s_asilchk_alivecnt_cur) {
        u2_s_asilchk_alivecnt_abjdgcnt = (U2)ASILCHK_ALIVECNT_NGJDGTIM;
    }
    else if(u2_s_asilchk_alivecnt_abjdgcnt > (U2)ASILCHK_ALIVECNT_NGJDGTIM) {
        u2_s_asilchk_alivecnt_abjdgcnt = (U2)ASILCHK_ALIVECNT_NGJDGTIM - (U2)1U;
    }
    else if(u2_s_asilchk_alivecnt_abjdgcnt > (U2)ASILCHK_ALIVECNT_TIM_EXPIRED) {
        u2_s_asilchk_alivecnt_abjdgcnt--;
    }
    else {
        u2_s_asilchk_alivecnt_abjdgcnt = (U2)ASILCHK_ALIVECNT_TIM_EXPIRED;
    }
    u4_s_asilchk_alivecnt_pre = u4_s_asilchk_alivecnt_cur;

    if(u2_s_asilchk_alivecnt_abjdgcnt == (U2)ASILCHK_ALIVECNT_TIM_EXPIRED) {
        vd_g_AsilChkCfgAliveCntFailAct();
    }
}

/*===================================================================================================================================*/
/*  static void   vd_s_AsilChkCrcCompFailChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_AsilChkCrcCompFailChk(void)
{
    U4    u4_t_loop;
    U1    u1_t_req;
    U4    u4_t_oncrc;
    U1    u1_t_cyctime;
    U1    u1_t_crccomp_rslt;
    U1    u1_t_crcfail;

    /* Get telltale status */
    vd_g_AsilChkCfgGetTtSts();

    u1_t_crcfail = (U1)FALSE;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)ASILCHK_TT_NUM; u4_t_loop++) {

        u1_t_req = (U1)ASILCHK_REQ_OFF;
        if(st_gp_ASILCHK_TT_TABLE[u4_t_loop].fp_u1_req != vdp_PTR_NA) {
            u1_t_req = st_gp_ASILCHK_TT_TABLE[u4_t_loop].fp_u1_req();
        }

        if(u1_t_req == (U1)ASILCHK_REQ_ASIL_LIGHT) {
            u4_t_oncrc = st_gp_ASILCHK_TT_TABLE[u4_t_loop].fp_u4_oncrc();
            /* CRC Light Comp Check */
            u1_t_crccomp_rslt = u2_s_AsilChkCrcLightCompChk(u4_t_oncrc, u4_sp_asilchk_crc_val[u4_t_loop]);
            /* Reset blink data */
            vd_s_AsilChkCrcBlinkCompClear(&u1_sp_asilchk_crc_blink_sts[u4_t_loop],&u1_sp_asilchk_crc_cyclechkcnt[u4_t_loop]);
        }
        else if(u1_t_req == (U1)ASILCHK_REQ_ASIL_BLINK) {
            u4_t_oncrc   = st_gp_ASILCHK_TT_TABLE[u4_t_loop].fp_u4_oncrc();
            u1_t_cyctime = st_gp_ASILCHK_TT_TABLE[u4_t_loop].fp_u1_cyctime();
            /* CRC Blink Comp Check */
            u1_t_crccomp_rslt = u2_s_AsilChkCrcBlinkCompChk(&u1_sp_asilchk_crc_blink_sts[u4_t_loop],
                                                            u1_t_cyctime,
                                                            &u1_sp_asilchk_crc_cyclechkcnt[u4_t_loop],
                                                            u4_t_oncrc,
                                                            u4_sp_asilchk_crc_val[u4_t_loop]);
        }
        else {
            /* No need CRC check */
            u1_t_crccomp_rslt = (U1)ASILCHK_CRCCOMP_NORMAL;
            /* Reset blink data */
            vd_s_AsilChkCrcBlinkCompClear(&u1_sp_asilchk_crc_blink_sts[u4_t_loop],&u1_sp_asilchk_crc_cyclechkcnt[u4_t_loop]);
        }

        u2_sp_asilchk_crc_abjdgcnt[u4_t_loop] = u2_s_AsilChkCrcFailCount(u2_sp_asilchk_crc_abjdgcnt[u4_t_loop], u1_t_crccomp_rslt);
        if(u2_sp_asilchk_crc_abjdgcnt[u4_t_loop] == (U2)ASILCHK_CRCCOMP_TIM_EXPIRED) {
            u1_t_crcfail = (U1)TRUE;
        }
    }

    if(u1_t_crcfail == (U1)TRUE) {
        vd_g_AsilChkCfgCrcFailAct();
    }
}

/*===================================================================================================================================*/
/*  static U2   u2_s_AsilChkCrcFailCount(const U2 u2_a_ABJDGCNT_PRE, const U4 u4_a_CRCCOMP_RSLT)                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2 u2_s_AsilChkCrcFailCount(const U2 u2_a_ABJDGCNT_PRE, const U4 u4_a_CRCCOMP_RSLT)
{
    U2    u2_t_abjdgcnt_next;

    if (u4_a_CRCCOMP_RSLT == (U1)ASILCHK_CRCCOMP_NORMAL) {
        u2_t_abjdgcnt_next = (U2)ASILCHK_CRCCOMP_NGJDGTIM;
    }
    else if(u2_a_ABJDGCNT_PRE > (U2)ASILCHK_CRCCOMP_NGJDGTIM) {
        u2_t_abjdgcnt_next = (U2)ASILCHK_CRCCOMP_NGJDGTIM - (U2)1U;
    }
    else if(u2_a_ABJDGCNT_PRE > (U2)ASILCHK_CRCCOMP_TIM_EXPIRED) {
        u2_t_abjdgcnt_next = (U2)u2_a_ABJDGCNT_PRE - (U2)1U;
    }
    else {
        u2_t_abjdgcnt_next = (U2)ASILCHK_CRCCOMP_TIM_EXPIRED;
    }

    return(u2_t_abjdgcnt_next);
}

/*===================================================================================================================================*/
/*  static U1   u2_s_AsilChkCrcLightCompChk(const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u2_s_AsilChkCrcLightCompChk(const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL)
{
    U1    u1_t_comprslt;

    if(u4_a_CRCVAL == u4_a_ONCRC) {
        u1_t_comprslt = (U1)ASILCHK_CRCCOMP_NORMAL;
    } else {
        u1_t_comprslt = (U1)ASILCHK_CRCCOMP_UNMATCH;
    }

    return(u1_t_comprslt);
}

/*===================================================================================================================================*/
/*  static U1   u2_s_AsilChkCrcBlinkCompChk(U1* const u1_ap_BLINK_STS, const U1 u1_a_CYCTIME,                                        */
/*                                           U1* const u1_ap_CYCLECHKCNT, const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u2_s_AsilChkCrcBlinkCompChk(U1* const u1_ap_BLINK_STS, const U1 u1_a_CYCTIME,
                                        U1* const u1_ap_CYCLECHKCNT, const U4 u4_a_ONCRC, const U4 u4_a_CRCVAL)
{
    U1    u1_t_comprslt;
    U4    u4_t_exp_crc;
    U1    u1_t_halfcyc;

    /* Calculate expected CRC value (set according to ON/OFF duty) */
    u1_t_halfcyc = u1_a_CYCTIME / (U1)2U;
    if(*u1_ap_CYCLECHKCNT < u1_t_halfcyc) {
        u4_t_exp_crc = u4_a_ONCRC;  /* ON Duty */
    } else {
        u4_t_exp_crc = (U4)0U;      /* OFF Duty */
    }

    /* Blink CRC compare state transition */
    switch(*u1_ap_BLINK_STS) {
        case ASILCHK_BLINKCHK_STS_OK:               /* [00b] Both OK / initial state */
            if(u4_a_CRCVAL != u4_t_exp_crc) {
                *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_BOTH_NG;
            }
            break;
        case ASILCHK_BLINKCHK_STS_OFF_NG:           /* [01b] ON_DUTY compare OK, OFF_DUTY waiting */
            if((u4_t_exp_crc == (U4)0U) && (u4_a_CRCVAL == u4_t_exp_crc)) {       /* OFF_DUTY match */
                *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_OK;
            }
            break;
        case ASILCHK_BLINKCHK_STS_ON_NG:            /* [10b] OFF_DUTY compare OK, ON_DUTY waiting */
            if((u4_t_exp_crc == u4_a_ONCRC) && (u4_a_CRCVAL == u4_t_exp_crc)) {   /* ON_DUTY match */
                *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_OK;
            }
            break;
        case ASILCHK_BLINKCHK_STS_BOTH_NG:               /* [11b] Both NG */
            if(u4_a_CRCVAL == u4_t_exp_crc) {
                if(u4_t_exp_crc == (U4)0U) {                                      /* OFF_DUTY match */                
                    *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_ON_NG;
                } else {                                                          /* ON_DUTY match */
                    *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_OFF_NG;
                }
            }
            break;
        default:
            *u1_ap_BLINK_STS = (U1)ASILCHK_BLINKCHK_STS_BOTH_NG;
            break;
    }

    u1_t_comprslt     = (U1)ASILCHK_CRCCOMP_UNMATCH;
    if(*u1_ap_BLINK_STS == (U1)ASILCHK_BLINKCHK_STS_OK) {
        u1_t_comprslt = (U1)ASILCHK_CRCCOMP_NORMAL;
    }

    /* Update cycle counter */
    if(*u1_ap_CYCLECHKCNT >= (u1_a_CYCTIME - (U1)1U)) {
        *u1_ap_CYCLECHKCNT = (U1)0U;
    } else {
        (*u1_ap_CYCLECHKCNT)++;
    }

    return(u1_t_comprslt);
}

/*===================================================================================================================================*/
/*  static void   vd_s_AsilChkCrcBlinkCompClear(U1* const u1_ap_BLINK_STS, U1* const u1_ap_CYCLECHKCNT)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1* const u1_ap_BLINK_STS    : blink check status                                                                */
/*                  U1* const u1_ap_CYCLECHKCNT  : cycle check counter                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_AsilChkCrcBlinkCompClear(U1* const u1_ap_BLINK_STS, U1* const u1_ap_CYCLECHKCNT)
{
    *u1_ap_BLINK_STS   = (U1)ASILCHK_BLINKCHK_STS_OK;
    *u1_ap_CYCLECHKCNT = (U1)0U;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/09/2026  KO       New.                                                                                               */
/*                                                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
