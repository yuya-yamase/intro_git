/* 1.2.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date Library                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATE_C_MAJOR                             (1U)
#define DATE_C_MINOR                             (2U)
#define DATE_C_PATCH                             (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "date.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATE_C_MAJOR != DATE_H_MAJOR) || \
     (DATE_C_MINOR != DATE_H_MINOR) || \
     (DATE_C_PATCH != DATE_H_PATCH))
#error "date.c and date.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define YYMMDDWK_BIT_LT_4YR                      (0x00000003U)
#define YYMMDDWK_LSB_NUM_4YR                     (2U)

#define YYMMDDWK___1YR                           (1U)
#define YYMMDDWK___4YR                           (4U)
#define YYMMDDWK_100YR                           (100U)
#define YYMMDDWK_400YR                           (400U)

#define YYMMDDWK___1YR_TO_DAY                    (365U)    /* days */
#define YYMMDDWK___4YR_TO_DAY                    (1461U)   /* days */
#define YYMMDDWK_100YR_TO_DAY                    (36524U)  /* days */
#define YYMMDDWK_400YR_TO_DAY                    (146097U) /* days */

#define YYMMDDWK_MO_DAY_MAX_LPYR_OFST            (13U)
#define YYMMDDWK_MO_DAYCNT_LPYR_OFST             (16U)

#define YYMMDDWK_WK_00_JAN_1ST                   (YYMMDDWK_WK_SAT)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_DateLpyrchk(const U4 u4_a_YR);
static U1      u1_s_YymmDayMax(const U4 u4_a_MO, const U1 u1_a_LPYR);
static U1      u1_s_DateFrmtOk(const U4 * u4_ap_DATE, U1 * u1_ap_lpyr);
static U4      u4_s_DaycntToYr(U4 * u4_ap_daycnt);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2    u2_sp_YYMMDDWK_MO_DAYCNT[] = {
    (U2)0U,        /* 00 : -   */
    (U2)0U,        /* 01 : Jan */
    (U2)31U,       /* 02 : Feb */
    (U2)59U,       /* 03 : Mar */
    (U2)90U,       /* 04 : Apr */
    (U2)120U,      /* 05 : May */
    (U2)151U,      /* 06 : Jun */
    (U2)181U,      /* 07 : Jul */
    (U2)212U,      /* 08 : Aug */
    (U2)243U,      /* 09 : Sep */
    (U2)273U,      /* 10 : Oct */
    (U2)304U,      /* 11 : Nov */
    (U2)334U,      /* 12 : Dec */
    (U2)365U,      /* 13       */
    (U2)365U,      /* 14       */
    (U2)365U,      /* 15       */

    (U2)0U,        /* 00 : -   */
    (U2)0U,        /* 01 : Jan */
    (U2)31U,       /* 02 : Feb */
    (U2)60U,       /* 03 : Mar */
    (U2)91U,       /* 04 : Apr */
    (U2)121U,      /* 05 : May */
    (U2)152U,      /* 06 : Jun */
    (U2)182U,      /* 07 : Jul */
    (U2)213U,      /* 08 : Aug */
    (U2)244U,      /* 09 : Sep */
    (U2)274U,      /* 10 : Oct */
    (U2)305U,      /* 11 : Nov */
    (U2)335U,      /* 12 : Dec */
    (U2)366U,      /* 13       */
    (U2)366U,      /* 14       */
    (U2)366U       /* 15       */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_YymmddFrmtOk(const U4 u4_a_YYMMDD, U2 * u2_ap_date)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_YymmddFrmtOk(const U4 u4_a_YYMMDD, U2 * u2_ap_date)
{
    U4                 u4_tp_work[YYMMDD_DATE_SIZE];
    U1                 u1_t_frmt;
    U1                 u1_t_lpyr;

    u4_tp_work[YYMMDD_DATE_YR] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR;
    u4_tp_work[YYMMDD_DATE_MO] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO;
    u4_tp_work[YYMMDD_DATE_DA] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA;
    u1_t_lpyr                  = (U1)FALSE;

    u1_t_frmt = u1_s_DateFrmtOk(&u4_tp_work[0], &u1_t_lpyr);
    if((u1_t_frmt  == (U1)TRUE  ) &&
       (u2_ap_date != vdp_PTR_NA)){

        u2_ap_date[YYMMDD_DATE_YR] = (U2)u4_tp_work[YYMMDD_DATE_YR];
        u2_ap_date[YYMMDD_DATE_MO] = (U2)u4_tp_work[YYMMDD_DATE_MO];
        u2_ap_date[YYMMDD_DATE_DA] = (U2)u4_tp_work[YYMMDD_DATE_DA];
    }

    return(u1_t_frmt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DayMaxofMonth(const U4 u4_a_YR, const U4 u4_a_MO)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DayMaxofMonth(const U4 u4_a_YR, const U4 u4_a_MO)
{
    U1                 u1_t_da_max;
    U1                 u1_t_lpyr;

    u1_t_lpyr   = u1_s_DateLpyrchk(u4_a_YR);
    u1_t_da_max = u1_s_YymmDayMax(u4_a_MO, u1_t_lpyr);

    return(u1_t_da_max);
}
/*===================================================================================================================================*/
/*  U4      u4_g_YymmddToDaycnt(const U4 u4_a_YYMMDD)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_YymmddToDaycnt(const U4 u4_a_YYMMDD)
{
    U4                 u4_t_yr_elpsd;
    U4                 u4_t_x100y;
    U4                 u4_t_num_lpyr;
    U4                 u4_t_mo;
    U4                 u4_t_daycnt;

    U4                 u4_tp_date[YYMMDD_DATE_SIZE];
    
    U1                 u1_t_frmt;
    U1                 u1_t_lpyr;

    u4_tp_date[YYMMDD_DATE_YR] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_YR) >> YYMMDDWK_LSB_YR;
    u4_tp_date[YYMMDD_DATE_MO] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_MO) >> YYMMDDWK_LSB_MO;
    u4_tp_date[YYMMDD_DATE_DA] = (u4_a_YYMMDD & (U4)YYMMDDWK_BIT_DA) >> YYMMDDWK_LSB_DA;
    u1_t_lpyr                    = (U1)FALSE;

    u1_t_frmt = u1_s_DateFrmtOk(&u4_tp_date[0], &u1_t_lpyr);
    if(u1_t_frmt == (U1)TRUE){

        if(u4_tp_date[YYMMDD_DATE_YR] > (U4)0U){

            u4_t_yr_elpsd = u4_tp_date[YYMMDD_DATE_YR] - (U4)1;
            u4_t_x100y    = u4_t_yr_elpsd / (U4)YYMMDDWK_100YR;
            u4_t_num_lpyr = ((u4_t_yr_elpsd >> YYMMDDWK_LSB_NUM_4YR) - u4_t_x100y) + (u4_t_x100y >> YYMMDDWK_LSB_NUM_4YR);

            u4_t_daycnt   = (u4_tp_date[YYMMDD_DATE_YR] * (U4)YYMMDDWK___1YR_TO_DAY) + u4_t_num_lpyr;
            u4_t_daycnt  += u4_tp_date[YYMMDD_DATE_DA];
        }
        else{
            u4_t_daycnt   = u4_tp_date[YYMMDD_DATE_DA] - (U4)1U;
        }

        if(u1_t_lpyr == (U1)TRUE){
            u4_t_mo = u4_tp_date[YYMMDD_DATE_MO] + (U4)YYMMDDWK_MO_DAYCNT_LPYR_OFST;
        }
        else{
            u4_t_mo = u4_tp_date[YYMMDD_DATE_MO];
        }
        u4_t_daycnt += (U4)u2_sp_YYMMDDWK_MO_DAYCNT[u4_t_mo];
    }
    else{
        u4_t_daycnt = (U4)YYMMDDWK_DAYCNT_UNKNWN;
    }

    return(u4_t_daycnt);
}
/*===================================================================================================================================*/
/*  U4      u4_g_DaycntToYymmddwk(const U4 u4_a_DAYCNT)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_DaycntToYymmddwk(const U4 u4_a_DAYCNT)
{
    const U2 *         u2_tp_MO_DAYCNT;
    U4                 u4_t_yymmddwk;
    U4                 u4_t_yr;
    U4                 u4_t_wk;

    U4                 u4_t_daycnt;

    U1                 u1_t_lpyr;
    U1                 u1_t_begin;
    U1                 u1_t_end;
    U1                 u1_t_mo;

    if(u4_a_DAYCNT <= (U4)YYMMDDWK_DAYCNT_MAX){

        u4_t_daycnt   = u4_a_DAYCNT;

        u4_t_yr       = u4_s_DaycntToYr(&u4_t_daycnt);
        u4_t_yymmddwk = u4_t_yr << YYMMDDWK_LSB_YR;

        u1_t_lpyr = u1_s_DateLpyrchk(u4_t_yr);
        if(u1_t_lpyr == (U1)TRUE){
            u2_tp_MO_DAYCNT = &u2_sp_YYMMDDWK_MO_DAYCNT[YYMMDDWK_MO_DAYCNT_LPYR_OFST];
        }
        else{
            u2_tp_MO_DAYCNT = &u2_sp_YYMMDDWK_MO_DAYCNT[0];
        }

        u1_t_begin = (U1)YYMMDDWK_MO_JAN;
        u1_t_end   = (U1)YYMMDDWK_MO_DEC;
        u1_t_mo    = (U1)YYMMDDWK_MO_JUL;
        while(u1_t_begin < u1_t_end){

            if(u4_t_daycnt >= (U4)u2_tp_MO_DAYCNT[u1_t_mo]){
                u1_t_begin = u1_t_mo;
            }
            else{
                u1_t_end = u1_t_mo - (U1)1U;
            }
            u1_t_mo = ((u1_t_begin + u1_t_end) + (U1)1U) >> 1U;
        }
        u4_t_yymmddwk |= ((U4)u1_t_mo << YYMMDDWK_LSB_MO);

        u4_t_daycnt    = (u4_t_daycnt + (U4)1U) - (U4)u2_tp_MO_DAYCNT[u1_t_mo];
        u4_t_yymmddwk |= (u4_t_daycnt << YYMMDDWK_LSB_DA);

        u4_t_daycnt    = u4_a_DAYCNT + (U4)YYMMDDWK_WK_00_JAN_1ST;
        u4_t_wk        = u4_t_daycnt % (U4)YYMMDDWK_NUM_WK;
     /* u4_t_yymmddwk |= (u4_t_wk << YYMMDDWK_LSB_WK); QAC warning#2985 */
        u4_t_yymmddwk |= u4_t_wk;
    }
    else{
        u4_t_yymmddwk  = (U4)YYMMDDWK_UNKNWN;
    }

    return(u4_t_yymmddwk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DayOfWeek(const U4 u4_a_DAYCNT)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DayOfWeek(const U4 u4_a_DAYCNT)
{
    U4                 u4_t_daycnt;
    U4                 u4_t_wk;

    u4_t_wk = (U4)YYMMDDWK_WK_UNKNWN;
    if(u4_a_DAYCNT <= (U4)YYMMDDWK_DAYCNT_MAX){
        u4_t_daycnt = u4_a_DAYCNT + (U4)YYMMDDWK_WK_00_JAN_1ST;
        u4_t_wk     = u4_t_daycnt % (U4)YYMMDDWK_NUM_WK;
    }

    return((U1)u4_t_wk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DateLpyrchk(const U4 u4_a_YR)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DateLpyrchk(const U4 u4_a_YR)
{
    U4                 u4_t_x4yr;
    U4                 u4_t_x100yr;
    U4                 u4_t_x400yr;
    U1                 u1_t_ans;

    u4_t_x4yr   = u4_a_YR & (U4)YYMMDDWK_BIT_LT_4YR;
    u4_t_x100yr = u4_a_YR % (U4)YYMMDDWK_100YR;
    u4_t_x400yr = u4_a_YR % (U4)YYMMDDWK_400YR;

    if(u4_t_x400yr == (U4)0U){
        u1_t_ans = (U1)TRUE;
    }
    else if(u4_t_x100yr == (U4)0U){
        u1_t_ans = (U1)FALSE;
    }
    else if(u4_t_x4yr == (U4)0U){
        u1_t_ans = (U1)TRUE;
    }
    else{
        u1_t_ans = (U1)FALSE;
    }

    return(u1_t_ans);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_YymmDayMax(const U4 u4_a_MO, const U1 u1_a_LPYR)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_YymmDayMax(const U4 u4_a_MO, const U1 u1_a_LPYR)
{
    static const U1    u1_sp_YYMMDDWK_MO_DAY_MAX[] = {
        (U1)0U,
        (U1)31U,  /* Jan */
        (U1)28U,  /* Feb */
        (U1)31U,  /* Mar */
        (U1)30U,  /* Apr */
        (U1)31U,  /* May */
        (U1)30U,  /* Jun */
        (U1)31U,  /* Jul */
        (U1)31U,  /* Aug */
        (U1)30U,  /* Sep */
        (U1)31U,  /* Oct */
        (U1)30U,  /* Nov */
        (U1)31U,  /* Dec */

        (U1)0U,
        (U1)31U,  /* Jan */
        (U1)29U,  /* Feb */
        (U1)31U,  /* Mar */
        (U1)30U,  /* Apr */
        (U1)31U,  /* May */
        (U1)30U,  /* Jun */
        (U1)31U,  /* Jul */
        (U1)31U,  /* Aug */
        (U1)30U,  /* Sep */
        (U1)31U,  /* Oct */
        (U1)30U,  /* Nov */
        (U1)31U   /* Dec */
    };

    U1                 u1_t_da_max;

    if((u4_a_MO < (U4)YYMMDDWK_MO_MIN) ||
       (u4_a_MO > (U4)YYMMDDWK_MO_MAX)){
        u1_t_da_max = (U1)YYMMDDWK_DA_UNKNWN;
    }
    else if(u1_a_LPYR == (U1)TRUE){
        u1_t_da_max = u1_sp_YYMMDDWK_MO_DAY_MAX[u4_a_MO + (U4)YYMMDDWK_MO_DAY_MAX_LPYR_OFST];
    }
    else{
        u1_t_da_max = u1_sp_YYMMDDWK_MO_DAY_MAX[u4_a_MO];
    }

    return(u1_t_da_max);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DateFrmtOk(const U4 * u4_ap_DATE, U1 * u1_ap_lpyr)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DateFrmtOk(const U4 * u4_ap_DATE, U1 * u1_ap_lpyr)
{
    U1                 u1_t_lpyr;
    U1                 u1_t_da_max;
    U1                 u1_t_ans;

    u1_t_ans = (U1)FALSE;
    if(u4_ap_DATE[YYMMDD_DATE_YR] <= (U4)YYMMDDWK_YR_MAX){

        u1_t_lpyr   = u1_s_DateLpyrchk(u4_ap_DATE[YYMMDD_DATE_YR]);
        u1_t_da_max = u1_s_YymmDayMax(u4_ap_DATE[YYMMDD_DATE_MO], u1_t_lpyr);

        if((u4_ap_DATE[YYMMDD_DATE_DA] >= (U4)YYMMDDWK_DA_MIN) &&
           (u4_ap_DATE[YYMMDD_DATE_DA] <= (U4)u1_t_da_max  )){

            (*u1_ap_lpyr) = u1_t_lpyr;
            u1_t_ans      = (U1)TRUE;
        }
    }

    return(u1_t_ans);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_DaycntToYr(U4 * u4_ap_daycnt)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_DaycntToYr(U4 * u4_ap_daycnt)
{
    U4                 u4_t_daycnt;
    U4                 u4_t_yr;

    u4_t_daycnt = (*u4_ap_daycnt);

    u4_t_yr = (U4)0U;
    if(u4_t_daycnt >= (U4)YYMMDDWK_400YR_TO_DAY){
        u4_t_yr      = (u4_t_daycnt / (U4)YYMMDDWK_400YR_TO_DAY) * (U4)YYMMDDWK_400YR;
        u4_t_daycnt  =  u4_t_daycnt % (U4)YYMMDDWK_400YR_TO_DAY;
    }
    if(u4_t_daycnt >= ((U4)YYMMDDWK_100YR_TO_DAY + (U4)1U)){
        u4_t_yr     += (((u4_t_daycnt - (U4)1) / (U4)YYMMDDWK_100YR_TO_DAY) * (U4)YYMMDDWK_100YR);
        u4_t_daycnt  =   (u4_t_daycnt - (U4)1) % (U4)YYMMDDWK_100YR_TO_DAY;

        if(u4_t_daycnt >= ((U4)YYMMDDWK___4YR * (U4)YYMMDDWK___1YR_TO_DAY)){
            u4_t_yr     += (U4)YYMMDDWK___4YR;
            u4_t_daycnt -= ((U4)YYMMDDWK___4YR * (U4)YYMMDDWK___1YR_TO_DAY);
        }
        else{
            u4_t_yr     += (u4_t_daycnt / (U4)YYMMDDWK___1YR_TO_DAY);
            u4_t_daycnt  =  u4_t_daycnt % (U4)YYMMDDWK___1YR_TO_DAY;
        }
    }
    if(u4_t_daycnt >= (U4)YYMMDDWK___4YR_TO_DAY){
        u4_t_yr     += ((u4_t_daycnt / (U4)YYMMDDWK___4YR_TO_DAY) * (U4)YYMMDDWK___4YR);
        u4_t_daycnt  =   u4_t_daycnt % (U4)YYMMDDWK___4YR_TO_DAY;
    }
    if(u4_t_daycnt >= ((U4)YYMMDDWK___1YR_TO_DAY + (U4)1U)){
        u4_t_yr     += ((u4_t_daycnt - (U4)1) / (U4)YYMMDDWK___1YR_TO_DAY);
        u4_t_daycnt  =  (u4_t_daycnt - (U4)1) % (U4)YYMMDDWK___1YR_TO_DAY;
    }

    (*u4_ap_daycnt) = u4_t_daycnt;

    return(u4_t_yr);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/ 2/2015  TN       New.                                                                                               */
/*  1.1.0     9/14/2015  TN       Bug Fix : yymmdd could be computed because of u4_s_DaycntToYr.                                     */
/*  1.2.0     9/15/2015  TN       Bug Fix : uninitialized variables in u4_g_YymmddToDaycnt.                                          */
/*  1.2.1     4/ 7/2017  TN       Improvement : Literal suffix "U" was added in order to prevent QAC warnings.                       */
/*  1.2.2     9/ 7/2021  TN       "U" suffix were added into litterals because of MC3 Rule-7.2 compliance.                           */
/*                                NULL->vdp_PTR_NA.                                                                                  */
/*           10/ 1/2021  TN       QAC warning was fixed.                                                                             */
/*  1.2.3    11/ 9/2023  KN       Improvement : Warning MISRA-C-Rule7.2 was fixed.                                                   */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KN   = Keigo Nomura , Denso Create                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
