/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HudDimmer Step                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMSTEP_C_MAJOR               (2)
#define HDIMSTEP_C_MINOR               (1)
#define HDIMSTEP_C_PATCH               (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hdimmgr_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HDIMSTEP_C_MAJOR != HDIMSTEP_H_MAJOR) || \
     (HDIMSTEP_C_MINOR != HDIMSTEP_H_MINOR) || \
     (HDIMSTEP_C_PATCH != HDIMSTEP_H_PATCH))
#error "hdimstep.c and hdimstep_cfg_private.h are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMSTEP_SWSGNL_UPDWON              (0x05)
#define HDIMSTEP_SWSGNL_UPON                (0x01)
#define HDIMSTEP_SWSGNL_DWON                (0x04)
#define HDIMSTEP_SWSGNL_NUM                 (16)

#define HDIMSTEP_SWEVT_NON                  (0)        
#define HDIMSTEP_SWEVT_UPDWON               (1)
#define HDIMSTEP_SWEVT_UPONEDGE             (2)
#define HDIMSTEP_SWEVT_DWONEDGE             (3)
#define HDIMSTEP_SWEVT_UPONCNTN             (4)
#define HDIMSTEP_SWEVT_DWONCNTN             (5)

#define HDIMSTEP_SWACTN_NON                 (0)             /* Don't change!!! */
#define HDIMSTEP_SWACTN_UP                  (1)
#define HDIMSTEP_SWACTN_DW                  (2)
#define HDIMSTEP_SWACTN_HOLD                (3)

#define HDIMSTEP_LONGON                     (500 / HDIMMGR_BASE_TASKTIM)
#define HDIMSTEP_LONGON_2ND                 (240 / HDIMMGR_BASE_TASKTIM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_hdimstep_upswoncnt;
static U2   u2_s_hdimstep_dwswoncnt;
static U1   u1_s_hdimstep_swsgnl;
static U1   u1_s_hdimstep_step;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1   u1_s_HdimstepDtctSwOpEvt(void);
static U1   u1_s_HdimstepSlctSwOpActn(const U1 u1_a_SWEVT);
static U1   u1_s_HdimstepExecSwOpActn(const U1 u1_a_SWACTN, const U1 u1_a_STEP);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Initialize at Poweron                                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimstepBon(void)
{
    U1      u1_t_step;

    u2_s_hdimstep_upswoncnt = (U2)U2_MAX;
    u2_s_hdimstep_dwswoncnt = (U2)U2_MAX;
    u1_s_hdimstep_swsgnl    = (U1)0;
    u1_g_hdimstep_hudill    = (U1)7U;   /* BEV Rebase provisionally */

    u1_s_hdimstep_step = (U1)HDIMSTEP_STEP_DEF;
    u1_t_step          = u1_g_HdimstepCfgReadStep();
    if(((U1)HDIMSTEP_STEP_MIN <= u1_t_step            ) &&
       (u1_t_step             <= (U1)HDIMSTEP_STEP_MAX)){
        u1_s_hdimstep_step = u1_t_step;
    }
}

/*===================================================================================================================================*/
/*  Initialize at Wakeup/Reset                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimstepWkup(void)
{
    U1      u1_t_step;

    u2_s_hdimstep_upswoncnt = (U2)U2_MAX;
    u2_s_hdimstep_dwswoncnt = (U2)U2_MAX;
    u1_s_hdimstep_swsgnl    = (U1)0;
    u1_g_hdimstep_hudill    = (U1)7U;   /* BEV Rebase provisionally */

    u1_s_hdimstep_step = (U1)HDIMSTEP_STEP_DEF;
    u1_t_step          = u1_g_HdimstepCfgReadStep();
    if(((U1)HDIMSTEP_STEP_MIN <= u1_t_step            ) &&
       (u1_t_step             <= (U1)HDIMSTEP_STEP_MAX)){
        u1_s_hdimstep_step = u1_t_step;
    }
}

/*===================================================================================================================================*/
/* HudDimmer Step Update                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void    vd_g_HdimstepUpdt(void)
{
    U1      u1_t_swevt;
    U1      u1_t_swactn;

    /* Update by switch operation */
    u1_t_swevt         = u1_s_HdimstepDtctSwOpEvt();
    u1_t_swactn        = u1_s_HdimstepSlctSwOpActn(u1_t_swevt);
    u1_s_hdimstep_step = u1_s_HdimstepExecSwOpActn(u1_t_swactn, u1_s_hdimstep_step);
}

/*===================================================================================================================================*/
/*  HudDimmer Step Data                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u4_a_step : Step Value                                                                                             */
/*  Return      u1_s_hdimstep_sts : Step Status                                                                                      */
/*===================================================================================================================================*/
U1  u1_g_HdimstepGetStepVal(U4 * u4_a_step)
{
    static const U1    u1_sp_HDIMSTEP_CNVRT_IN2IN[(U1)HDIMSTEP_STEP_MAX + (U1)1]={
        (U1)U1_MAX,  /* Don't change!!! */
        (U1)10, /* lvl 01 */                                                /* lvl 10 */
        (U1) 9, /* lvl 02 */                                                /* lvl 09 */
        (U1) 8, /* lvl 03 */                                                /* lvl 08 */
        (U1) 7, /* lvl 04 */                                                /* lvl 07 */
        (U1) 6, /* lvl 05 */                                                /* lvl 06 */
        (U1) 5, /* lvl 06 */                                                /* lvl 05 */
        (U1) 4, /* lvl 07 */                                                /* lvl 04 */
        (U1) 3, /* lvl 08 */                                                /* lvl 03 */
        (U1) 2, /* lvl 09 */                                                /* lvl 02 */
        (U1) 1, /* lvl 10 */                                                /* lvl 01 */
        (U1) 0  /* lvl 11 */                                                /* lvl 00 */
    };

    U1      u1_t_step;

    u1_t_step = u1_sp_HDIMSTEP_CNVRT_IN2IN[(U1)HDIMSTEP_STEP_DEF];
    if(((U1)HDIMSTEP_STEP_MIN <= u1_s_hdimstep_step   ) &&
       (u1_s_hdimstep_step    <= (U1)HDIMSTEP_STEP_MAX)){
        u1_t_step = u1_sp_HDIMSTEP_CNVRT_IN2IN[u1_s_hdimstep_step];
    }
    (*u4_a_step) = (U4)u1_t_step;

    return((U1)HDIMMGR_INSTS_NML);
}

/*===================================================================================================================================*/
/*  HudDimmer External Step Data                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_HdimstepGetExtrlStepVal(U4 * u4_a_step)
{
    (*u4_a_step) = (U4)u1_s_hdimstep_step;

    return((U1)HDIMMGR_INSTS_NML);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Function Definitions                                                                                                      */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* static U1   u1_s_HdimstepDtctSwOpEvt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static U1   u1_s_HdimstepDtctSwOpEvt(void)
{
    static const U1 u1_sp_HDIMSTEP_SWEVT[HDIMSTEP_SWSGNL_NUM]={
        /*                                 PreDw Dw    PreUp Up     */
        (U1)HDIMSTEP_SWEVT_NON,         /* OFF   OFF   OFF   OFF    */
        (U1)HDIMSTEP_SWEVT_UPONEDGE,    /* OFF   OFF   OFF   ON     */
        (U1)HDIMSTEP_SWEVT_NON,         /* OFF   OFF   ON    OFF    */
        (U1)HDIMSTEP_SWEVT_UPONCNTN,    /* OFF   OFF   ON    ON     */
        (U1)HDIMSTEP_SWEVT_DWONEDGE,    /* OFF   ON    OFF   OFF    */
        (U1)HDIMSTEP_SWEVT_UPDWON,      /* OFF   ON    OFF   ON     */
        (U1)HDIMSTEP_SWEVT_DWONEDGE,    /* OFF   ON    ON    OFF    */
        (U1)HDIMSTEP_SWEVT_UPDWON,      /* OFF   ON    ON    ON     */
        (U1)HDIMSTEP_SWEVT_NON,         /* ON    OFF   OFF   OFF    */
        (U1)HDIMSTEP_SWEVT_UPONEDGE,    /* ON    OFF   OFF   ON     */
        (U1)HDIMSTEP_SWEVT_NON,         /* ON    OFF   ON    OFF    */
        (U1)HDIMSTEP_SWEVT_UPONCNTN,    /* ON    OFF   ON    ON     */
        (U1)HDIMSTEP_SWEVT_DWONCNTN,    /* ON    ON    OFF   OFF    */
        (U1)HDIMSTEP_SWEVT_UPDWON,      /* ON    ON    OFF   ON     */
        (U1)HDIMSTEP_SWEVT_DWONCNTN,    /* ON    ON    ON    OFF    */
        (U1)HDIMSTEP_SWEVT_UPDWON       /* ON    ON    ON    ON     */
    };

    ST_HDIMSTEP_SWOP st_t_swop;
    U1               u1_t_swevt;
    U1               u1_t_sgnl;

    st_t_swop.u1_jdgenbl  = (U1)FALSE;
    st_t_swop.u1_isupswon = (U1)FALSE;
    st_t_swop.u1_isdwswon = (U1)FALSE;
    vd_g_HdimstepCfgSwOprtIn(&st_t_swop);

    if(st_t_swop.u1_jdgenbl == (U1)TRUE){
        u1_s_hdimstep_swsgnl  &= (U1)HDIMSTEP_SWSGNL_UPDWON;
        u1_s_hdimstep_swsgnl <<= 1;
        if(st_t_swop.u1_isupswon == (U1)TRUE){
            u1_s_hdimstep_swsgnl |= (U1)HDIMSTEP_SWSGNL_UPON;
        }
        if(st_t_swop.u1_isdwswon == (U1)TRUE){
            u1_s_hdimstep_swsgnl |= (U1)HDIMSTEP_SWSGNL_DWON;
        }
        u1_t_sgnl = u1_s_hdimstep_swsgnl;
    }
    else{
        u1_s_hdimstep_swsgnl = (U1)0; 
        u1_t_sgnl = (U1)U1_MAX;
    }

    u1_t_swevt = (U1)HDIMSTEP_SWEVT_NON;
    if(u1_t_sgnl < (U1)HDIMSTEP_SWSGNL_NUM){
        u1_t_swevt = u1_sp_HDIMSTEP_SWEVT[u1_t_sgnl];
    }
    return(u1_t_swevt);
}

/*===================================================================================================================================*/
/* static U1   u1_s_HdimstepSlctSwOpActn(const U1 u1_a_SWEVT)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static U1   u1_s_HdimstepSlctSwOpActn(const U1 u1_a_SWEVT)
{
    U1      u1_t_swactn;

    if(u2_s_hdimstep_upswoncnt < (U2)U2_MAX){
        u2_s_hdimstep_upswoncnt++;
    }
    if(u2_s_hdimstep_dwswoncnt < (U2)U2_MAX){
        u2_s_hdimstep_dwswoncnt++;
    }
    /*-----------------------------------------------------------------------*/
    switch (u1_a_SWEVT){
        case (U1)HDIMSTEP_SWEVT_UPDWON:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_HOLD;
            u2_s_hdimstep_upswoncnt = (U2)0;
            u2_s_hdimstep_dwswoncnt = (U2)0;
            break;
        case (U1)HDIMSTEP_SWEVT_UPONEDGE:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_UP;
            u2_s_hdimstep_upswoncnt = (U2)0;
            u2_s_hdimstep_dwswoncnt = (U2)0;
            break;
        case (U1)HDIMSTEP_SWEVT_DWONEDGE:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_DW;
            u2_s_hdimstep_upswoncnt = (U2)0;
            u2_s_hdimstep_dwswoncnt = (U2)0;
            break;
        case (U1)HDIMSTEP_SWEVT_UPONCNTN:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_HOLD;
            if(u2_s_hdimstep_upswoncnt >= (U2)HDIMSTEP_LONGON){
                u2_s_hdimstep_upswoncnt = ((U2)HDIMSTEP_LONGON - (U2)HDIMSTEP_LONGON_2ND);
                u1_t_swactn = (U1)HDIMSTEP_SWACTN_UP;
            }
            u2_s_hdimstep_dwswoncnt = (U2)0;
            break;
        case (U1)HDIMSTEP_SWEVT_DWONCNTN:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_HOLD;
            if(u2_s_hdimstep_dwswoncnt >= (U2)HDIMSTEP_LONGON){
                u2_s_hdimstep_dwswoncnt = ((U2)HDIMSTEP_LONGON - (U2)HDIMSTEP_LONGON_2ND);
                u1_t_swactn = (U1)HDIMSTEP_SWACTN_DW;
            }
            u2_s_hdimstep_upswoncnt = (U2)0;
            break;
     /* case (U1)HDIMSTEP_SWEVT_NON: */
        default:
            u1_t_swactn = (U1)HDIMSTEP_SWACTN_NON;
            u2_s_hdimstep_upswoncnt = (U2)U2_MAX;
            u2_s_hdimstep_dwswoncnt = (U2)U2_MAX;
            break;
    }
    return(u1_t_swactn);
}

/*===================================================================================================================================*/
/* static U1   u1_s_HdimstepExecSwOpActn(const U1 u1_a_SWACTN, const U1 u1_a_STEP)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static U1   u1_s_HdimstepExecSwOpActn(const U1 u1_a_SWACTN, const U1 u1_a_STEP)
{
    U1      u1_t_step;
    U1      u1_t_updtdstep;
    U1      u1_t_isok;

    u1_t_updtdstep = u1_a_STEP;
    u1_t_step      = u1_g_HdimstepCfgReadStep();
    if(((U1)HDIMSTEP_STEP_MIN <= u1_t_step            ) &&
       (u1_t_step             <= (U1)HDIMSTEP_STEP_MAX)){
        u1_t_updtdstep = u1_t_step;
    }
    u1_t_step = u1_t_updtdstep;

    /*-----------------------------------------------------------------------*/
    u1_t_isok = (U1)FALSE;

    switch(u1_a_SWACTN){
        case (U1)HDIMSTEP_SWACTN_UP:
            if(u1_t_updtdstep <= ((U1)HDIMSTEP_STEP_MAX - (U1)HDIMSTEP_STEP_LSB)){
                u1_t_updtdstep += (U1)HDIMSTEP_STEP_LSB;                                  /* PRQA S 3383 # over detection */
            }
            else{
                u1_t_updtdstep = (U1)HDIMSTEP_STEP_MAX;
            }
            if(u1_t_step != u1_t_updtdstep){
                u1_t_isok = u1_g_HdimstepCfgWriteStep(u1_t_updtdstep);
            }
            break;
        case (U1)HDIMSTEP_SWACTN_DW:
            if(u1_t_updtdstep >= ((U1)HDIMSTEP_STEP_MIN + (U1)HDIMSTEP_STEP_LSB)){
                u1_t_updtdstep -= (U1)HDIMSTEP_STEP_LSB;                                  /* PRQA S 3383 # over detection */
            }
            else{
                u1_t_updtdstep = (U1)HDIMSTEP_STEP_MIN;
            }
            if(u1_t_step != u1_t_updtdstep){
                u1_t_isok = u1_g_HdimstepCfgWriteStep(u1_t_updtdstep);
            }
            break;
        case (U1)HDIMSTEP_SWACTN_HOLD:
            break;
     /* case (U1)HDIMSTEP_SWACTN_NON: */
        default:
            /* no processing */
            break;
    }

    if(u1_t_isok == (U1)TRUE){
        u1_t_step = u1_t_updtdstep;
    }
    return(u1_t_step);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version          Date        Author  Change Description                                                                          */
/* ---------------   ----------  ------  --------------------------------------------------------------------------------------------*/
/*  2.0.0            2020.02.20  MaO     New                                                                                         */
/*  2.1.0            2024.02.14  HiS     HDIMSTEP_STEP_EXTRIN_SUP was revised. MM Dimmer was deleted.                                */
/*                                                                                                                                   */
/*  * MaO = Masayuki Okada, DENSO                                                                                                    */
/*  * HiS = Hidenobu Suzuki, ISB                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
