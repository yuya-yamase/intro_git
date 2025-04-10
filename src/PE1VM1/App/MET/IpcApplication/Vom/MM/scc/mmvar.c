/* 19PFV3_1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  MM�o���G�[�V������񐧌�                                                                                                         */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MMVAR_C_MAJOR                      (1)
#define MMVAR_C_MINOR                      (0)
#define MMVAR_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mmvar_prm.h"
#include "hmimcst.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MMVAR_C_MAJOR != MMVAR_H_MAJOR) || \
     (MMVAR_C_MINOR != MMVAR_H_MINOR) || \
     (MMVAR_C_PATCH != MMVAR_H_PATCH))
#error "source and header files are inconsistent!"
#endif /* ((MMVAR_C_MAJOR != MMVAR_H_MAJOR) || ... */

#if ((MMVAR_C_MAJOR != MMVAR_PRM_MAJOR) || \
     (MMVAR_C_MINOR != MMVAR_PRM_MINOR) || \
     (MMVAR_C_PATCH != MMVAR_PRM_PATCH))
#error "source and parameter files are inconsistent!"
#endif /* ((MMVAR_C_MAJOR != MMVAR_PRM_MAJOR) || ... */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_mmvar_accon_pre;                                                /* Previous Acc                                       */
static U1 u1_s_mmvar_sta_chg_uname_pre;                                        /* Previous chg_uname_a                               */
static U1 u1_s_mmvar_req_uname;                                                /* Request uname_t_mode                               */
static U1 u1_s_mmvar_req_uname_flg;                                            /* Request uname_flg                                  */
static U2 u2_sp2_mmvar_textdata[MMVAR_UNAME_MAX][MMVAR_TEXT_LENGTH_AVNMS72];   /* Text Data                                          */
static U2 u2_sp_mmvar_sta_chg_uname[MMVAR_UNAME_MAX];                          /* chg_uname                                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_MMVarRamClear(void);
static void vd_s_MMVarRamClearExceptBkupRam(void);

static void vd_s_MMVarUnameProcess(void);
static void vd_s_MMVarAccOnTimerCtrl(void);
static void vd_s_MMVarUnameWriteCtrl(void);
static void vd_s_MMVarUpdateUnameData(const ST_MMTEXT_TXTDAT_AVNMS72* stp_a_txtdat);
static void vd_s_MMVarWriteUnameData(void);
static void vd_s_MMVarIntervalTimerCtrl(void);

/*===================================================================================================================================*/
/*  ����������                                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMVarInitial(void)
{
    /* Ram clear(Except for Backup Ram) */
    vd_s_MMVarRamClearExceptBkupRam();


    /* TimerStop */
    vd_s_MMVAR_STOPTIMER(MMVAR_TIMERID_UNAME_ACCON);
    vd_s_MMVAR_STOPTIMER(MMVAR_TIMERID_UNAME_INTERVAL);
}

/*===================================================================================================================================*/
/*  ����RAM�N���A����                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarRamClear(void)
{
    /* �e��RAM���N���A���� */

    u1_s_mmvar_accon_pre = (U1)FALSE;
    u1_s_mmvar_req_uname = (U1)MMVAR_UNAME_INT;
    u1_s_mmvar_sta_chg_uname_pre = (U1)MMVAR_CHG_UNAME_INT;
    u1_s_mmvar_req_uname_flg = (U1)MMVAR_REQ_UNAME_FLG_NO;

    vd_g_MMVAR_CLEAR_TEXT_UNAME(&u2_sp2_mmvar_textdata[0][0]);
    vd_g_MMVAR_CLEAR_CHG_UNAME(&u2_sp_mmvar_sta_chg_uname[0]);
}

/*===================================================================================================================================*/
/*  10ms������� ACC��Ԃ��m�F����                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMVarTask(void)
{
    U1 u1_t_is_accon;                                                           /* ACC���                                           */
    u1_t_is_accon = u1_MMVAR_ACCISON();

    if(u1_t_is_accon == (U1)FALSE)
    {
        /* Ram clear(Except for Backup Ram) */
        vd_s_MMVarRamClearExceptBkupRam();
    }
    else
    {
        /* Uname Process */
        vd_s_MMVarUnameProcess();
    }
    u1_s_mmvar_accon_pre = u1_t_is_accon;
}


/*===================================================================================================================================*/
/*  +BON����������                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMVarBonInitial(void)
{

    /* �e��RAM���N���A���� */
    vd_s_MMVarRamClear();


    /* TimerStop */
    vd_s_MMVAR_STOPTIMER(MMVAR_TIMERID_UNAME_ACCON);
    vd_s_MMVAR_STOPTIMER(MMVAR_TIMERID_UNAME_INTERVAL);

    return;
}

/*===================================================================================================================================*/
/*  Uname_AccOn                                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMVar_NotifyTimerEvent_Uname_AccOn(void)
{
    u1_s_mmvar_req_uname = (U1)MMVAR_UNAME1;
    vd_s_MMVAR_SENDREQUSERNAME(u1_s_mmvar_req_uname);
    u1_s_mmvar_req_uname_flg = (U1)MMVAR_FLG_ON;
}

/*===================================================================================================================================*/
/*  Uname_Interval                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_MMVar_NotifyTimerEvent_Uname_Interval(void)
{
    u1_s_mmvar_req_uname = u1_s_mmvar_req_uname + (U1)1;

    if(((U1)MMVAR_UNAME2 == u1_s_mmvar_req_uname)||((U1)MMVAR_UNAME3 == u1_s_mmvar_req_uname)){
        vd_s_MMVAR_SENDREQUSERNAME(u1_s_mmvar_req_uname);
        u1_s_mmvar_req_uname_flg = (U1)MMVAR_FLG_ON;
    }else{
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  Uname_Check                                                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_mmvar_mode                                                                                                  */
/*  Return:         u1_t_mmvar_ret                                                                                                   */
/*===================================================================================================================================*/
U1 u1_g_MMVar_CheckModeState(U1 u1_a_mmvar_mode)
{
    U1 u1_t_mmvar_ret;

    /* init */
    u1_t_mmvar_ret = (U1)FALSE;

    if (((U1)MMVAR_UNAME1 == u1_a_mmvar_mode) ||  /* user_1 */
        ((U1)MMVAR_UNAME2 == u1_a_mmvar_mode) ||  /* user_2 */
        ((U1)MMVAR_UNAME3 == u1_a_mmvar_mode))    /* user_3 */
    {
        u1_t_mmvar_ret = (U1)TRUE;
    }

    return(u1_t_mmvar_ret);
}

/*===================================================================================================================================*/
/*  Ram Clear(Except for Backup Ram)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarRamClearExceptBkupRam(void)
{

    u1_s_mmvar_accon_pre = (U1)FALSE;
    u1_s_mmvar_req_uname = (U1)MMVAR_UNAME_INT;
    u1_s_mmvar_sta_chg_uname_pre = (U1)MMVAR_CHG_UNAME_INT;
    u1_s_mmvar_req_uname_flg = (U1)MMVAR_REQ_UNAME_FLG_NO;
}

/*===================================================================================================================================*/
/*  Uname Process                                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarUnameProcess(void)
{
    vd_s_MMVarAccOnTimerCtrl();
    vd_s_MMVarUnameWriteCtrl();
}

/*===================================================================================================================================*/
/*  ACC-ON Timer Control                                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarAccOnTimerCtrl(void)
{
    if((U1)FALSE == u1_s_mmvar_accon_pre)
    {
        vd_s_MMVAR_STARTTIMERRESERVE(MMVAR_TIMERID_UNAME_ACCON);
    }
    else
    {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  Uname Write Control                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarUnameWriteCtrl(void)
{
    const ST_MMTEXT_TXTDAT_AVNMS72*  stp_t_txtdat_avnms72 = (ST_MMTEXT_TXTDAT_AVNMS72*)vdp_PTR_NA;
    U1 u1_t_mmvar_result;
    U1 u1_t_mmvar_rxsts;

    u1_t_mmvar_rxsts = u1_s_MMVAR_TEXTGETDATA_AVNMS72(&stp_t_txtdat_avnms72);

    if( ((U1)MMVAR_RET_OK == u1_t_mmvar_rxsts) &&
        ((ST_MMTEXT_TXTDAT_AVNMS72*)vdp_PTR_NA != stp_t_txtdat_avnms72) )
    {
        u1_t_mmvar_result = u1_g_MMVar_CheckModeState(stp_t_txtdat_avnms72->u1_UNAME_T_MODE);

        if( ((U1)TRUE == u1_t_mmvar_result) &&
            (u1_s_mmvar_sta_chg_uname_pre != stp_t_txtdat_avnms72->u1_STA_CHG_UNAME_A) )
        {
            vd_s_MMVarUpdateUnameData(stp_t_txtdat_avnms72);
            vd_s_MMVarWriteUnameData();

            if(stp_t_txtdat_avnms72->u1_UNAME_T_MODE == u1_s_mmvar_req_uname)
            {
                vd_s_MMVarIntervalTimerCtrl();
                u1_s_mmvar_req_uname_flg = (U1)MMVAR_FLG_OFF;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* Do Nothing */
        }
        u1_s_mmvar_sta_chg_uname_pre = stp_t_txtdat_avnms72->u1_STA_CHG_UNAME_A;
    }
    else
    {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*  Update Uname Data                                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   ST_MMTEXT_TXTDAT_AVNMS72* stp_a_txtdat : Text Data                                                                   */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarUpdateUnameData(const ST_MMTEXT_TXTDAT_AVNMS72* stp_a_txtdat)
{
    /* Update Text Data */
    vd_s_MMVAR_COPYU2(  &u2_sp2_mmvar_textdata[stp_a_txtdat->u1_UNAME_T_MODE - (U1)1][0]
                      , &stp_a_txtdat->u2_UNAME_TXT_DAT[0]
                      , MMVAR_TEXT_LENGTH_AVNMS72 );

    /* Update Change Number */
    if((U2)MMVAR_CHG_UNAME_VALID_MAX <= u2_sp_mmvar_sta_chg_uname[stp_a_txtdat->u1_UNAME_T_MODE - (U1)1])
    {
        u2_sp_mmvar_sta_chg_uname[stp_a_txtdat->u1_UNAME_T_MODE - (U1)1] = (U2)MMVAR_CHG_UNAME_VALID_MIN;
    }
    else
    {
        u2_sp_mmvar_sta_chg_uname[stp_a_txtdat->u1_UNAME_T_MODE - (U1)1] = u2_sp_mmvar_sta_chg_uname[stp_a_txtdat->u1_UNAME_T_MODE - (U1)1] + (U2)1;
    }

}

/*===================================================================================================================================*/
/*  Write Uname Data                                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarWriteUnameData(void)
{
    U1 u1_t_mmvar_cnt;
    U2 u2_tp_mmvar_usrdat[MMVAR_USRDAT_MAX];

    /* Always writing 3 users in order not to miss the new data */
    for(u1_t_mmvar_cnt = (U1)0; u1_t_mmvar_cnt < (U1)MMVAR_UNAME_MAX; u1_t_mmvar_cnt++)
    {
        u2_tp_mmvar_usrdat[0] = u2_sp_mmvar_sta_chg_uname[u1_t_mmvar_cnt];
        vd_s_MMVAR_COPYU2(&u2_tp_mmvar_usrdat[1], &u2_sp2_mmvar_textdata[u1_t_mmvar_cnt][0], MMVAR_TEXT_LENGTH_AVNMS72);

        vd_g_HmiMcstMMUserPut(&u2_tp_mmvar_usrdat[1], u2_tp_mmvar_usrdat[0], u1_t_mmvar_cnt + (U1)1U);
    }
}

/*===================================================================================================================================*/
/*  Interval Timer Control                                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_MMVarIntervalTimerCtrl(void)
{
    if( ((U1)MMVAR_FLG_ON == u1_s_mmvar_req_uname_flg) &&
        ( ((U1)MMVAR_UNAME1 == u1_s_mmvar_req_uname) ||
          ((U1)MMVAR_UNAME2 == u1_s_mmvar_req_uname) ) )
    {
        vd_s_MMVAR_STARTTIMERRESERVE(MMVAR_TIMERID_UNAME_INTERVAL);
    }
    else
    {
        /* Do Nothing */
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  19PFV3_1.0.0    2024.04.19  YK      Create New based on [P4.4.1]                                                                 */
/*                                                                                                                                   */
/*  YK = Yuki Koshimae, ISB                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
