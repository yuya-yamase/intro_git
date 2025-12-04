/* 3.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Turn & Hazard Make/Manage Flash Cycle                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THBLNKR_C_MAJOR                          (3)
#define THBLNKR_C_MINOR                          (5)
#define THBLNKR_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "thblnkr_cfg_private.h"
#include "alert.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((THBLNKR_C_MAJOR != THBLNKR_H_MAJOR) || \
     (THBLNKR_C_MINOR != THBLNKR_H_MINOR) || \
     (THBLNKR_C_PATCH != THBLNKR_H_PATCH))
#error "thblnkr.c and thblnkr.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define     THBLNKR_1BIT_SHIFT        (1U)
#define     THBLNKR_TURHAZ_REQ_NUM    (2U)
#define     THBLNKR_CHK_TURN_L_ON     (0x00000001U)
#define     THBLNKR_CHK_TURN_R_ON     (0x00000002U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_thblnkr_tictoc_req;
static U1                   u1_s_thblnkr_tictoc_hld;
static U2                   u2_s_thblnkr_spdmd;
static U1                   u1_s_thblnkr_ind_act;
static U2                   u2_s_thblnkr_act_tim_mtnls_l;
static U2                   u2_s_thblnkr_act_tim_mtnls_r;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_ThblnkrInit(void);
static U1       u1_s_ThblnkrGetInput(void);
static void     vd_s_ThblnkrTicTac(const U1 u1_a_PRE_INDACT, const U1 u1_a_CUR_INDACT);
static void     vd_s_ThblnkrSpdMd(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_ThblnkrBonInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThblnkrBonInit(void)
{
    vd_s_ThblnkrInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_ThblnkrRstWkInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThblnkrRstWkInit(void)
{
    vd_s_ThblnkrInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_ThblnkrMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThblnkrMainTask(void)
{
    U1                                  u1_t_ind_act_next;

    u1_t_ind_act_next = u1_s_ThblnkrGetInput();
    vd_s_ThblnkrTicTac(u1_s_thblnkr_ind_act, u1_t_ind_act_next);
    vd_s_ThblnkrSpdMd();

    u1_s_thblnkr_ind_act = u1_t_ind_act_next;
}

/*===================================================================================================================================*/
/*  U1      u1_g_ThblnkrTicTocReq(U1 * u1p_a_spdmd)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_ThblnkrTicTocReq(U1 * u1p_a_spdmd)
{
    if (u1p_a_spdmd != vdp_PTR_NA) {
        *u1p_a_spdmd = (U1)u2_s_thblnkr_spdmd;
    }

    return(u1_s_thblnkr_tictoc_req);
}

/*===================================================================================================================================*/
/*  U1  u1_g_ThblnkrIndAct(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1  u1_g_ThblnkrIndAct(void)
{
    return(u1_s_thblnkr_ind_act);
}

/*===================================================================================================================================*/
/*  static void     vd_s_ThblnkrInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_ThblnkrInit(void)
{
    u1_s_thblnkr_tictoc_req         = (U1)THBLNKR_NON;
    u1_s_thblnkr_tictoc_hld         = (U1)U1_MAX;
    u2_s_thblnkr_spdmd              = (U2)THBLNKR_SPDMD_LO;
    u1_s_thblnkr_ind_act            = (U1)0U;
    u2_s_thblnkr_act_tim_mtnls_l    = (U2)0U;
    u2_s_thblnkr_act_tim_mtnls_r    = (U2)0U;
}

/*===================================================================================================================================*/
/*  static U1   u1_s_ThblnkrGetInput(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_ThblnkrGetInput(void)
{
    static const ST_ALERT_REQBIT   st_sp_THBLNKR_L_REQBIT[THBLNKR_TURHAZ_REQ_NUM] = {
        /*  u2_src_ch                       u1_src_act                          u1_dst_idx  u4_dst_bit                */
        {  (U2)ALERT_CH_B_TURHAZ_L,         (U1)ALERT_REQ_B_TURHAZ_L_ON,        (U1)0U,     (U4)THBLNKR_CHK_TURN_L_ON  },
        {  (U2)ALERT_CH_B_TURHAZ_R,         (U1)ALERT_REQ_B_TURHAZ_R_ON,        (U1)0U,     (U4)THBLNKR_CHK_TURN_R_ON  }
    };

    static const U1 u1_s_MTNR_LSB_VAL  = (U1)1U;
    static const U2 u2_s_THBNLKR_INACT = ((U2)5000U / (U2)THBLNKR_MAINTICK);
    U1 u1_t_thblnkr_req;
    U1 u1_t_mtnl_sgnl;
    U1 u1_t_mtnr_sgnl;
    U4 u4_t_req;

    u1_t_mtnl_sgnl = (U1)FALSE;
    u1_t_mtnr_sgnl = (U1)FALSE;
    u4_t_req       = (U4)0U;

    vd_g_AlertReqToBit(st_sp_THBLNKR_L_REQBIT, (U2)THBLNKR_TURHAZ_REQ_NUM, &u4_t_req, (U1)1U);

    if((u4_t_req & (U4)THBLNKR_CHK_TURN_L_ON) != (U4)0U){
        u1_t_mtnl_sgnl = (U1)(u4_t_req & (U4)THBLNKR_CHK_TURN_L_ON);
    }

    if (u1_t_mtnl_sgnl == (U1)TRUE) {
        if (u2_s_thblnkr_act_tim_mtnls_l < (U2)U2_MAX) {
            u2_s_thblnkr_act_tim_mtnls_l++;
        }
    }
    else {
        u2_s_thblnkr_act_tim_mtnls_l = (U2)0U;
    }
    if (u2_s_thblnkr_act_tim_mtnls_l > u2_s_THBNLKR_INACT) {
        u1_t_mtnl_sgnl = (U1)FALSE;
    }
    u1_t_thblnkr_req = u1_t_mtnl_sgnl;


    if((u4_t_req & (U4)THBLNKR_CHK_TURN_R_ON) != (U4)0U){
        u1_t_mtnr_sgnl = (U1)((u4_t_req & (U4)THBLNKR_CHK_TURN_R_ON) >> THBLNKR_1BIT_SHIFT);
    }

    if (u1_t_mtnr_sgnl == (U1)TRUE) {
        if (u2_s_thblnkr_act_tim_mtnls_r < (U2)U2_MAX) {
            u2_s_thblnkr_act_tim_mtnls_r++;
        }
    }
    else {
        u2_s_thblnkr_act_tim_mtnls_r = (U2)0U;
    }
    if (u2_s_thblnkr_act_tim_mtnls_r > u2_s_THBNLKR_INACT) {
        u1_t_mtnr_sgnl = (U1)FALSE;
    }
    u1_t_thblnkr_req |= (u1_t_mtnr_sgnl << u1_s_MTNR_LSB_VAL);

    return(u1_t_thblnkr_req);
}

/*===================================================================================================================================*/
/*  static void    vd_s_ThblnkrTicTac(const U1 u1_a_PRE_INDACT, const U1 u1_a_CUR_INDACT)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_ThblnkrTicTac(const U1 u1_a_PRE_INDACT, const U1 u1_a_CUR_INDACT)
{
    static const U1                      u1_s_THBLNKR_HOLDTIM = (U1)2U;
    U1                                   u1_t_edge_exist;
    U1                                   u1_t_onedge;
    U1                                   u1_t_offedge;

    u1_t_onedge = (U1)FALSE;
    u1_t_offedge = (U1)FALSE;

    u1_t_edge_exist = u1_a_PRE_INDACT ^ u1_a_CUR_INDACT;
    if (u1_t_edge_exist != (U1)0U) {
        if ((u1_t_edge_exist & u1_a_CUR_INDACT) != (U1)0U) {
            u1_t_onedge = (U1)TRUE;
        }
        else {
            u1_t_offedge = (U1)TRUE;
        }
    }

    if (u1_s_thblnkr_tictoc_hld < (U1)U1_MAX) {
        u1_s_thblnkr_tictoc_hld++;
    }

    if (u1_t_onedge == (U1)TRUE) {
        u1_s_thblnkr_tictoc_req = (U1)THBLNKR_TIC;
        u1_s_thblnkr_tictoc_hld = (U1)0U;
    }
    else if (u1_t_offedge == (U1)TRUE) {
        u1_s_thblnkr_tictoc_req = (U1)THBLNKR_TOC;
        u1_s_thblnkr_tictoc_hld = (U1)0U;
    }
    else {
        if (u1_s_thblnkr_tictoc_hld >= u1_s_THBLNKR_HOLDTIM) {
            u1_s_thblnkr_tictoc_req = (U1)THBLNKR_NON;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_ThblnkrSpdMd(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_ThblnkrSpdMd(void)
{

    static const U2                   u2_sp_THBLNKR_SPDMD_RNG[] = {
        (U2)0U,    (U2)2701U, (U2)7701U,
        (U2)2999U, (U2)7999U, (U2)U2_MAX
    };
    static const ST_RNG_CMPR_U2       st_s_THBLNKR_SPDMD_CHK = {
        &u2_sp_THBLNKR_SPDMD_RNG[0],
        (U2)0U,
        (U2)3U
    };
    U2  u2_t_kmph;

    u2_t_kmph          = u2_g_ThblnkrVehSpdDsplyd();
    u2_s_thblnkr_spdmd = u2_g_ThblnkrRngCmprU2(u2_s_thblnkr_spdmd, u2_t_kmph, &st_s_THBLNKR_SPDMD_CHK);
    if(u2_s_thblnkr_spdmd >= (U2)THBLNKR_NUM_SPDMD){
        u2_s_thblnkr_spdmd = (U2)THBLNKR_SPDMD_HI;
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
/*  1.0.0    12/03/2018  TA       New.                                                                                               */
/*  1.1.0    12/10/2019  TA       Add Esi mode and optimisation                                                                      */
/*  1.2.0    02/12/2020  TA       Refactoring                                                                                        */
/*  1.3.0    10/08/2020  KK       A/D corrction feature (AD_K) was added. Diag customize for Tic-Toc pres. was added.                */
/*           08/24/2020  TA       Delete Over Write IF for Diagnosis                                                                 */
/*           09/29/2020  TA       Change sampling mask time(u2_g_THBLNKR_SMPL_MSK_TIM) to configuration data                         */
/*           10/08/2020  TA       Change DTC status to B backup retention memory using RIM                                           */
/*  1.3.1    03/15/2021  KK       Fix Short jugdement bugs                                                                           */
/*  1.4.0    05/12/2021  SK       Add Rcd Req type. Make Reqval into an array                                                        */
/*           07/26/2021  TA       Changed the conditions for disconnection judgment and short-circuit judgment                       */
/*                                from u1_s_thblnkr_pri_onoff to u1_s_thblnkr_pub_onoffChange                                        */
/*  2.0.0    09/06/2021  YI       MET-B_MMTURHAZ-CSTD-0-09-A-C7                                                                      */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    11/04/2021  TA(M)    Changed to read AD_I from non-volatile memory                                                      */
/*  2.2.0    06/27/2022  TA(M)    Add Advanced Park WinkerON request (MET-B_MMTURHAZ-CSTD-0-13-A-C7)                                 */
/*  2.3.0    04/18/2022  ZS       MET-B_STOPTURN-CORG-0-01-A-C0                                                                      */
/*  2.4.0    08/25/2022  TA(M)    Add B_ST signal tp open judgment condition(MET-B_MMTURHAZ-CSTD-0-13-A-C7)                          */
/*  2.5.0    09/24/2022  TA(M)    Add THBLNKR_TLCHK_OTHER_REQ (return value of u1_g_ThblnkrTlchkSts)                                 */
/*  2.5.1    10/20/2022  YI       Fix QAC warning.                                                                                   */
/*  3.0.0    12/13/2023  KH       Change according to MET-B_TURHAZ-CSTD-A0-xx-x-xx specification                                     */
/*  3.1.0    07/03/2024  AA       Change for WKPSLP update                                                                           */
/*  3.2.0    09/16/2024  YR       Removed the processing for sound pressure                                                          */
/*  3.3.0    09/16/2024  KH       Change logic of Awake condition                                                                    */
/*           09/19/2024  YR       Change comment for u1_g_ThblnkrTicTocReq function                                                  */
/*  3.4.0    10/23/2024  RS       Change for BEV System_Consideration_1                                                              */
/*  3.5.0    12/04/2025  SH       Change for BEV System_Consideration_ADAS                                                           */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima , Denso                                                                                                 */
/*  * KK   = Kohei Kato,       Denso Techno                                                                                          */
/*  * SK   = Shintaro Kanou,   Denso Techno                                                                                          */
/*  * YI   = Yoshiki Iwata,    NTT Data MSE                                                                                          */
/*  * TA(M)= Teruyuki Anjima,  NTT Data MSE                                                                                          */
/*  * ZS   = Zenjiro Shamoto,  NTT Data MSE                                                                                          */
/*  * KH   = Kiko Huerte,      DTPH                                                                                                  */
/*  * AA   = Anna Asuncion,    Denso Techno                                                                                          */
/*  * YR   = Yhana Regalario.  DTPH                                                                                                  */
/*  * RS   = Ryuki Sako,       Denso Techno                                                                                          */
/*  * SH   = Sae Hirose,       Denso Techno                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
