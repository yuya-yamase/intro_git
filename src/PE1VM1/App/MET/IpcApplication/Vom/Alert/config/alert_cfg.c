/* 5.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert                                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_CFG_C_MAJOR                        (5)
#define ALERT_CFG_C_MINOR                        (5)
#define ALERT_CFG_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_bcm.h"

#include "vardef.h"
#include "vardef_dest.h"
#include "odo_km.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ALERT_CFG_C_MAJOR != ALERT_H_MAJOR) || \
     (ALERT_CFG_C_MINOR != ALERT_H_MINOR) || \
     (ALERT_CFG_C_PATCH != ALERT_H_PATCH))
#error "alert_cfg.c and alert.h : source and header files are inconsistent!"
#endif

#if ((ALERT_CFG_C_MAJOR != ALERT_CFG_H_MAJOR) || \
     (ALERT_CFG_C_MINOR != ALERT_CFG_H_MINOR) || \
     (ALERT_CFG_C_PATCH != ALERT_CFG_H_PATCH))
#error "alert_cfg.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Project Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#if (__PRJ_LIB_ALERT_D1L1_330D_HEV__ != 1)
#error "alert_cfg.c : Target project is inactive!"
#endif
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_ECOMODE3_JUDG_TBL_NUM              (16U)
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
static inline U1      u1_s_AlertCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_g_ALERT_IGN_OFF_TOUT    = (U4)150000U; /* 25 minutes */
const U1                    u1_g_ALERT_BUS_CH          = (U1)OXCAN_CH_0_CAN;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertCfgInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertCfgInit(void)
{
    vd_g_AlertBcmInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertCfgMainStart(const U1 u1_a_VOM)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertCfgMainStart(const U1 u1_a_VOM)
{
    vd_g_AlertBcmTask(u1_a_VOM);
}
/*===================================================================================================================================*/
/*  void    vd_g_AlertCfgMainFinish(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertCfgMainFinish(void)
{
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgOilrpm(U2 * u2p_a_Rpm)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_AlertCfgOilrpm(U2 * u2p_a_Rpm)
{
    U1 u1_t_ret;

    *u2p_a_Rpm = (U2)0U;
    u1_t_ret    = (U1)ALERT_ENGTYPE_CAN_VALID;

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgPtsctmpCelFltrd(U2 * u2p_a_0p01cel)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgPtsctmpCelFltrd(U2 * u2p_a_0p01cel)
{
    static const U2 u2_s_ALERT_FLTRD_0P01_CNVRT = (U2)1U;     /* Cel LSB 0P01 Convert */
    U2              u2_t_0p01cel;
    U1              u1_t_tmpret;

    u2_t_0p01cel = (U2)0U;
    u1_t_tmpret  = u1_g_PtsctmpCelFltrd(&u2_t_0p01cel);

    if(u2_t_0p01cel >= (U2)ALERT_PTSCTMP_CEL_OFFSET){
        *u2p_a_0p01cel = ((u2_t_0p01cel - (U2)ALERT_PTSCTMP_CEL_OFFSET) * u2_s_ALERT_FLTRD_0P01_CNVRT);
    }
    else{
        *u2p_a_0p01cel = (U2)0U;
    }

    return(u1_t_tmpret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgPtsctmpCelInst(U2 * u2p_a_0p01cel)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgPtsctmpCelInst(U2 * u2p_a_0p01cel)
{
    static const U2 u2_s_ALERT_INST_0P01_CNVRT = (U2)1U;     /* Cel LSB 0P01 Convert */
    U2              u2_t_0p01cel;
    U1              u1_t_tmpret;

    u2_t_0p01cel = (U2)0U;
    u1_t_tmpret  = u1_g_PtsctmpCelInst(&u2_t_0p01cel);

    if(u2_t_0p01cel >= (U2)ALERT_PTSCTMP_CEL_OFFSET){
        *u2p_a_0p01cel = ((u2_t_0p01cel - (U2)ALERT_PTSCTMP_CEL_OFFSET) * u2_s_ALERT_INST_0P01_CNVRT);
    }
    else{
        *u2p_a_0p01cel = (U2)0U;
    }

    return(u1_t_tmpret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgS_cvrsAdds(U1 * u1p_a_rprt, U1 * u1p_a_sfty)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgS_cvrsAdds(U1 * u1p_a_rprt, U1 * u1p_a_sfty)
{
#if defined(OXCAN_PDU_RX_CAN_AVNMS73) && (defined(ComConf_ComSignal_L_ADDSTRI1_REPORT) || defined(ComConf_ComSignal_L_ADDSTRI1_SAFETY_CON))
    static const U2 u2_s_ALERT_S_CVRS_TO_THRSH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_AVNMS73,
                                   (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                   u2_s_ALERT_S_CVRS_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl   = (U1)0U;
#if defined(ComConf_ComSignal_L_ADDSTRI1_REPORT)
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_ADDSTRI1_REPORT, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_L_ADDSTRI1_REPORT) */
    *u1p_a_rprt = u1_t_sgnl;

    u1_t_sgnl   = (U1)0U;
#if defined(ComConf_ComSignal_L_ADDSTRI1_SAFETY_CON)
    (void)Com_ReceiveSignal(ComConf_ComSignal_L_ADDSTRI1_SAFETY_CON, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_L_ADDSTRI1_SAFETY_CON) */
    *u1p_a_sfty = u1_t_sgnl;

    return(u1_t_msgsts);
#else
    return((U1)COM_NO_RX);
#endif /* defined(OXCAN_PDU_RX_CAN_AVNMS73) && (defined(ComConf_ComSignal_L_ADDSTRI1_REPORT) || defined(ComConf_ComSignal_L_ADDSTRI1_SAFETY_CON)) */
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgC_brk_0IsTmode(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgC_brk_0IsTmode(void)
{
    static const U2 u2_s_ALERT_CFG_BIT_TEST_MODE = (U2)0x8000U;
    U1              u1_t_rim_sts;
    U2              u2_t_rim_mode;
    U1              u1_t_tmode;

    u1_t_tmode    = (U1)FALSE;
    u2_t_rim_mode = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_TYDC_WRBYID_AA00, &u2_t_rim_mode) & (U1)RIM_RESULT_KIND_MASK;
    if((u1_t_rim_sts                                  == (U1)RIM_RESULT_KIND_OK)&&
      ((u2_t_rim_mode & u2_s_ALERT_CFG_BIT_TEST_MODE) != (U2)0U               )){
        u1_t_tmode = (U1)TRUE;
    }

    return(u1_t_tmode);
}
/*===================================================================================================================================*/
/*  U2    u2_g_AlertCfgC_brk_0EngineRPMVal(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2 u2_g_AlertCfgC_brk_0EngineRPMVal(void)
{
    static const U2 u2_s_ALERT_C_BRK_TO_THRSH     = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U4 u4_s_ALERT_C_BRK_400RPM       = (U4)400U;
    static const U4 u4_s_ALERT_C_BRK_NE_RXCFNT    = (U4)50U;                 /* 12800/256                                            */
    static const U4 u4_s_ALERT_C_BRK_NE_ROUND     = (U4)32U;                 /* 64 * 0.5 (For rounding off when divided by 64)       */
    static const U4 u4_s_ALERT_C_BRK_NE_LSR_CFCNT = (U4)6U;                  /* /64  (For right shft operation, instead of division) */
                                                                             /* LSB:(12800/256/64)rpm -> 1rpm                        */

    S2 s2_t_ne;
    U4 u4_t_egrt_val;
    U2 u2_t_ret;
    U1 u1_t_stsbit;

    s2_t_ne       = (S2)0;
    u4_t_egrt_val = (U4)0U;
    u2_t_ret      = (U2)0U;

    u1_t_stsbit   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G02,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_C_BRK_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    (void)Com_ReceiveSignal(ComConf_ComSignal_NE1, &s2_t_ne);

    if(u1_t_stsbit == (U1)COM_NO_RX){
        u4_t_egrt_val = (U4)0U;
    }
    else if((u1_t_stsbit == (U1)COM_TIMEOUT                  )||
            (u1_t_stsbit == ((U1)COM_TIMEOUT | (U1)COM_NO_RX))){
        u4_t_egrt_val = u4_s_ALERT_C_BRK_400RPM;
    }
    else{
        if(s2_t_ne > (S2)0)
        {
            u4_t_egrt_val = (U4)((U2)s2_t_ne);

            u4_t_egrt_val = u4_t_egrt_val * u4_s_ALERT_C_BRK_NE_RXCFNT;
            u4_t_egrt_val = (u4_t_egrt_val + u4_s_ALERT_C_BRK_NE_ROUND) >> u4_s_ALERT_C_BRK_NE_LSR_CFCNT;
        }
    }

    if(u4_t_egrt_val > (U4)U2_MAX){
        u2_t_ret = (U2)U2_MAX;
    }
    else{
        u2_t_ret = (U2)u4_t_egrt_val;
    }

    return(u2_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgP_mflid_FlidCalibJdg(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgP_mflid_FlidCalibJdg(void)
{
    static const U1 u1_s_OPEN_MSG_UNKNOWN = (U1)3U;
    U1              u1_t_open_msg_rqst;
    U1              u1_t_calib_jdg;

    u1_t_calib_jdg     = u1_CALIB_MCUID0432_LIDINFO;

    if(u1_t_calib_jdg == (U1)CALIB_MCUID0432_LSTM){
        u1_t_open_msg_rqst = u1_g_AlertFLidopenMsgRqst();
    }
    else{
        u1_t_open_msg_rqst = u1_s_OPEN_MSG_UNKNOWN;
    }

    return(u1_t_open_msg_rqst);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgH_tevrnIsEnable(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgH_tevrnIsEnable(void)
{
    U1              u1_t_ret;
    U1              u1_t_calib;
    U1              u1_t_ptsys;

    u1_t_calib     = u1_s_AlertCfgCalibU1NumChk(u1_CALIB_MCUID0025_SPORTS, (U1)CALIB_MCUID0025_NUM, (U1)CALIB_MCUID0025_DEF);

    u1_t_ptsys     = u1_g_AlertPtsys();
    if(u1_t_ptsys > (U1)ALERT_PTSYS_1F_NRX){
        u1_t_ptsys = (U1)ALERT_PTSYS_0F_UNK;
    }

    if((u1_t_calib  != (U1)CALIB_MCUID0025_070D)   &&
       ((u1_t_ptsys == (U1)VDF_PTS_RX_03_HYB)      ||
        (u1_t_ptsys == (U1)VDF_PTS_RX_04_HYB_PLU)  ||
        (u1_t_ptsys == (U1)VDF_PTS_RX_06_HYB_MOT))){

        u1_t_ret = (U1)TRUE;
    }
    else{
        u1_t_ret = (U1)FALSE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static inline U1    u1_s_AlertCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_NUM                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         u1_t_ret                                                                                                         */
/*===================================================================================================================================*/
static inline U1      u1_s_AlertCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)
{
    U1              u1_t_ret;

    u1_t_ret = u1_a_CALIBID;

    if(u1_t_ret >= u1_a_NUM){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgIdlstp(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_idlstp                                                                                                      */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgIdlstp(void)
{
    U1              u1_t_idlstp;
    U1              u1_t_pwrtrn;

    u1_t_pwrtrn = u1_g_VardefPtsRx();
    u1_t_idlstp = (U1)FALSE;
    if(u1_t_pwrtrn == (U1)VDF_PTS_RX_02_GAS_ISS){
        u1_t_idlstp = (U1)TRUE;
    }

    return(u1_t_idlstp);
}

/*===================================================================================================================================*/
/*  U1    u1_g_AlertCfgEcomodeOn(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_pts_on                                                                                                      */
/*===================================================================================================================================*/
U1    u1_g_AlertCfgEcomodeOn(void)
{
    static const U2 u2_s_ALERT_ECOMODE3_TO_THRESH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ECOMODE3_SGNL_MSK  = (U1)0x0FU;
    static const U1 u1_s_ALERT_ECOMODE3_JUDG_TBL[ALERT_ECOMODE3_JUDG_TBL_NUM] = {
        (U1)FALSE, (U1)TRUE,  (U1)TRUE,  (U1)TRUE,  (U1)TRUE,  (U1)FALSE, (U1)FALSE, (U1)FALSE,
        (U1)FALSE, (U1)FALSE, (U1)FALSE, (U1)FALSE, (U1)FALSE, (U1)FALSE, (U1)FALSE, (U1)FALSE
    };
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_pts_on;

    u1_t_pts_on = (U1)FALSE;
    u1_t_msgsts = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                   (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                   u2_s_ALERT_ECOMODE3_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    if(u1_t_msgsts == (U1)0U){
        u1_t_sgnl   = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_ECOMODE3, &u1_t_sgnl);
        u1_t_sgnl  &= u1_s_ALERT_ECOMODE3_SGNL_MSK;
        u1_t_pts_on = u1_s_ALERT_ECOMODE3_JUDG_TBL[u1_t_sgnl];
    }

    return(u1_t_pts_on);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     1/17/2019  TN       New.                                                                                               */
/*  5.1.0     3/26/2019  TN       alert v5.0.0 -> v5.1.0.                                                                            */
/*  5.2.0     4/17/2019  YI       alert v5.1.0 -> v5.2.0.                                                                            */
/*  5.3.0     5/10/2019  YI       alert v5.2.0 -> v5.3.0.                                                                            */
/*  5.4.0     9/20/2019  YI       alert v5.3.0 -> v5.4.0.                                                                            */
/*  5.5.0    10/31/2019  DS       alert v5.4.0 -> v5.5.0.                                                                            */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  001      12/12/2019  DS       Add Enable IF for TATOL.                                                                           */
/*  19PFv3-1 11/14/2023  TH       Update for 19PFv3 CV                                                                               */
/*  19PFv3-2 02/13/2024  AA       Added config for P_MFLID                                                                           */
/*  19PFv3-3 03/20/2024  KH       Added config for H_TEVRN                                                                           */
/*  19PFv3-4 04/03/2024  DR       Deleted engine type                                                                                */
/*  19PFv3-5 05/06/2024  YR       Added config for ECOMODE3                                                                          */
/*  19PFv3-6 06/27/2024  TN(DT)   Delete Calibration Guard Process.                                                                  */
/*  19PFv3-7 07/12/2024  TN(DT)   Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, Denso                                                                                                  */
/*  * YI     = Yoshiki Iwata, Denso                                                                                                  */
/*  * DS     = Daisuke Suzuki, NTTD MSE                                                                                              */
/*  * TH     = Taisuke, Hirakawa, KSE                                                                                                */
/*  * AA     = Anna Asuncion, DT                                                                                                     */
/*  * KH     = Kiko Huerte, DTPH                                                                                                     */
/*  * DR     = Dyan Reyes, DTPH                                                                                                      */
/*  * YR     = Yhana Regalario, DTPH                                                                                                 */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
