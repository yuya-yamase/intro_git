/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oil temperature                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILTMP_C_MAJOR                    (1)
#define OILTMP_C_MINOR                    (0)
#define OILTMP_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oiltemp_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OILTMP_C_MAJOR != OILTMP_H_MAJOR) || \
     (OILTMP_C_MINOR != OILTMP_H_MINOR) || \
     (OILTMP_C_PATCH != OILTMP_H_PATCH))
#error "oiltemp.c and oiltemp.h : source and header files are inconsistent!"
#endif

#if ((OILTMP_C_MAJOR != OILTMP_CFG_H_MAJOR) || \
     (OILTMP_C_MINOR != OILTMP_CFG_H_MINOR) || \
     (OILTMP_C_PATCH != OILTMP_CFG_H_PATCH))
#error "oiltemp.c and oiltemp_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILTMP_OFF                        (0U)
#define OILTMP_INIT_OR_FAIL               (1U)
#define OILTMP_UPDT                       (2U)

#define OILTMP_INVALID_VAL                (0xFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1 u1_s_rcvd;
    U1 u1_dat_adr;
    U2 u2_dat[OILTMP_BTHOE_AVENUM];
    U1 u1_calsts;
    U1 u1_unit;
    U2 u2_dspseg;
    U1 u1_overheat;
}ST_OILTMP_VAR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OILTMP_VAR  st_s_oiltmp;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U1       u1_s_OilTmpUnitJdg(void);
static        U2       u2_s_OilTmpCal(U1 u1_a_unit);
static        void     vd_s_OilTmpClrInc(void);
static        U1       u1_s_OilTmpOverHeatJdg(U2 u2_a_dspval, U1 u1_a_unit, U1 u1_a_overheat);
static        void     vd_s_OilTmpCalibReadTmpCel(U2* u2p_a_calib_tmpc_max, U2* u2p_a_calib_tmpc_min);
static        void     vd_s_OilTmpCalibReadTmpFah(U2* u2p_a_calib_tmpf_max, U2* u2p_a_calib_tmpf_min);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OilTmpInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilTmpInit(void)
{
    vd_s_OilTmpClrInc();

    st_s_oiltmp.u1_calsts   = (U1)OILTMP_OFF;
    st_s_oiltmp.u1_s_rcvd   = (U1)FALSE;
    st_s_oiltmp.u1_unit     = (U1)OILTMP_UNIT_DEF;
    st_s_oiltmp.u2_dspseg   = (U2)OILTMP_INVALID_VAL;
    st_s_oiltmp.u1_overheat = (U1)OILTMP_OVERHEAT_OFF;
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilTmpClrInc(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilTmpClrInc(void)
{
    U1 u1_t_idx;

    st_s_oiltmp.u1_dat_adr = (U1)0U;
    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILTMP_BTHOE_AVENUM; u1_t_idx++){
        st_s_oiltmp.u2_dat[u1_t_idx] = (U2)0U;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilTmpInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                   */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:信号入力取得（通信途絶、バリエーションエラー）                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilTmpInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    U2 u2_t_fail;
    U1 u1_t_idx;

    u2_t_fail = stp_a_incarg->u2_sigfail & (U2)OILTMP_FAILCHK;
    if(u2_t_fail == (U2)0U){
        if((stp_a_incarg->u1_rcvd & (U1)OILTMP_ENG1G17RCVD) == (U1)OILTMP_ENG1G17RCVD){
            if(st_s_oiltmp.u1_s_rcvd == (U1)FALSE){
                for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILTMP_BTHOE_AVENUM; u1_t_idx++){
                   st_s_oiltmp.u2_dat[u1_t_idx] = stp_a_incarg->st_inc_eng1g17.u2_bthoe;
                }
                st_s_oiltmp.u1_dat_adr = (U1)0U;
            }
            else{
                 if(st_s_oiltmp.u1_dat_adr >= (U1)OILTMP_BTHOE_AVENUM){
                     st_s_oiltmp.u1_dat_adr  = (U1)0U;
                 }

                 st_s_oiltmp.u2_dat[st_s_oiltmp.u1_dat_adr] = stp_a_incarg->st_inc_eng1g17.u2_bthoe;

                 st_s_oiltmp.u1_dat_adr = (st_s_oiltmp.u1_dat_adr >= ((U1)OILTMP_BTHOE_AVENUM - (U1)1U)) ? (U1)0U : (st_s_oiltmp.u1_dat_adr + (U1)1U);
            }
            st_s_oiltmp.u1_s_rcvd  = (U1)TRUE;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilTmpTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_evtbit                                                                                                   */
/*                  U2 u2_a_sigfail                                                                                                  */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilTmpTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)
{
    U2 u2_t_fail;
    U2 u2_t_igon;

    u2_t_igon = u2_a_evtbit  & (U2)OILTMP_IGON_EVT;
    u2_t_fail = u2_a_sigfail & (U2)OILTMP_FAILCHK;

    if(u2_t_igon != (U2)OILTMP_IGON_EVT){
        st_s_oiltmp.u1_calsts  = (U1)OILTMP_OFF;
        vd_s_OilTmpClrInc();
        st_s_oiltmp.u1_s_rcvd  = (U1)FALSE;
    }
    else if(u2_t_fail != (U2)0U){
        st_s_oiltmp.u1_calsts = (U1)OILTMP_INIT_OR_FAIL;
        vd_s_OilTmpClrInc();
        st_s_oiltmp.u1_s_rcvd = (U1)FALSE;
    }
    else{
        switch(st_s_oiltmp.u1_calsts){
            case OILTMP_OFF:
            case OILTMP_INIT_OR_FAIL:
                if(st_s_oiltmp.u1_s_rcvd == (U1)TRUE){
                    st_s_oiltmp.u1_calsts = (U1)OILTMP_UPDT;
                }
                else{
                    st_s_oiltmp.u1_calsts = (U1)OILTMP_INIT_OR_FAIL;
                }
                break;
            case OILTMP_UPDT:
                if(st_s_oiltmp.u1_s_rcvd != (U1)TRUE){
                    st_s_oiltmp.u1_calsts  = (U1)OILTMP_INIT_OR_FAIL;
                    vd_s_OilTmpClrInc();
                    st_s_oiltmp.u1_s_rcvd  = (U1)FALSE;
                }
                break;
            default:
                st_s_oiltmp.u1_calsts  = (U1)OILTMP_INIT_OR_FAIL;
                vd_s_OilTmpClrInc();
                st_s_oiltmp.u1_s_rcvd  = (U1)FALSE;
                break;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilTmpUpdt(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilTmpUpdt(void)
{
    switch(st_s_oiltmp.u1_calsts){
        case OILTMP_UPDT:
            st_s_oiltmp.u1_unit     = u1_s_OilTmpUnitJdg();
            st_s_oiltmp.u2_dspseg   = u2_s_OilTmpCal(st_s_oiltmp.u1_unit);
            st_s_oiltmp.u1_overheat = u1_s_OilTmpOverHeatJdg(st_s_oiltmp.u2_dspseg,
                                                             st_s_oiltmp.u1_unit,
                                                             st_s_oiltmp.u1_overheat);
            break;
        case OILTMP_OFF:
        case OILTMP_INIT_OR_FAIL:
        default:
            st_s_oiltmp.u2_dspseg   = (U2)OILTMP_INVALID_VAL;
            st_s_oiltmp.u1_unit     = (U1)OILTMP_UNIT_DEF;
            st_s_oiltmp.u1_overheat = (U1)OILTMP_OVERHEAT_OFF;
            break;
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_OilTmpUnitJdg(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_region                                                                                                   */
/*  Attention:      If the unit information is an abnormal value, control is performed using the initial value (Celsius).            */
/*===================================================================================================================================*/
static U1       u1_s_OilTmpUnitJdg(void)
{
    U1 u1_t_tmp_unit;

    u1_t_tmp_unit = u1_OILTMP_TEMP_UNIT();
    if(u1_t_tmp_unit == (U1)OILTMP_TEMP_JDG){
        u1_t_tmp_unit = (U1)OILTMP_TEMPF;
    }
    else{
        u1_t_tmp_unit = (U1)OILTMP_TEMPC;
    }

    return(u1_t_tmp_unit);
}

/*===================================================================================================================================*/
/*  static U2       u2_s_OilTmpCal(U1 u1_a_unit)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U2 u2_t_pixel                                                                                                    */
/*===================================================================================================================================*/
static U2       u2_s_OilTmpCal(U1 u1_a_unit)
{
    U4 u4_t_val;
    U1 u1_t_idx;
    S4 s4_t_val;
    U2 u2_t_dspval;
    U2 u2_t_max;
    U2 u2_t_min;
    U2 u2_t_tmpc_max;
    U2 u2_t_tmpf_max;
    U2 u2_t_tmpc_min;
    U2 u2_t_tmpf_min;

    u4_t_val          = (U4)0U;
    u2_t_tmpc_max     = (U2)OILTMP_TMPC_MAX_DEF;
    u2_t_tmpc_min     = (U2)OILTMP_TMPC_MIN_DEF;
    u2_t_tmpf_max     = (U2)OILTMP_TMPF_MAX_DEF;
    u2_t_tmpf_min     = (U2)OILTMP_TMPF_MIN_DEF;

    vd_s_OilTmpCalibReadTmpCel(&u2_t_tmpc_max, &u2_t_tmpc_min);
    vd_s_OilTmpCalibReadTmpFah(&u2_t_tmpf_max, &u2_t_tmpf_min);

    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILTMP_BTHOE_AVENUM; u1_t_idx++){
        if(st_s_oiltmp.u2_dat[u1_t_idx] > (U2)OILTMP_BTHOE_TEMPCSIG_MAX){
            u4_t_val += (U4)OILTMP_BTHOE_TEMPCSIG_MAX;
        }
        else{
            u4_t_val += (U4)st_s_oiltmp.u2_dat[u1_t_idx];
        }
    }

    u2_t_min = u2_OILTMP_CNV_TMP(u2_t_tmpc_min);
    u2_t_max = u2_OILTMP_CNV_TMP(u2_t_tmpc_max);

    s4_t_val = (S4)u4_t_val * (S4)OILTMP_TMPC_LSBMULU; 
    s4_t_val = s4_t_val / (S4)OILTMP_TMPC_LSBDIV;
    s4_t_val = s4_t_val + (S4)OILTMP_TMPC_OFST;

    if((u1_a_unit & (U1)OILTMP_UNIT_MSK) == (U1)OILTMP_TEMPF){
        s4_t_val = ((s4_t_val * (S4)OILTMP_CHGF_DAT9) / (S4)OILTMP_CHGF_DAT5) + (S4)OILTMP_CHGF_DAT32;
        u2_t_min = u2_OILTMP_CNV_TMP(u2_t_tmpf_min);
        u2_t_max = u2_OILTMP_CNV_TMP(u2_t_tmpf_max);
    }
    s4_t_val = s4_t_val / (S4)OILTMP_BTHOE_LSB;
    s4_t_val = s4_t_val + (S4)OILTMP_COM_OFST;

    if(s4_t_val < (S4)(U4)u2_t_min){
        u2_t_dspval = u2_t_min;
    }
    else if(s4_t_val > (S4)(U4)u2_t_max){
        u2_t_dspval = u2_t_max;
    }
    else {
        u2_t_dspval = (U2)(U4)s4_t_val;
    }

    return(u2_t_dspval);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_OilTmpOverHeatJdg(U2 u2_a_dspval, U1 u1_a_unit,U1 u1_a_overheat)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_dspval                                                                                                   */
/*                  U1 u1_a_unit                                                                                                     */
/*                  U1 u1_a_overheat                                                                                                 */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_OilTmpOverHeatJdg(U2 u2_a_dspval, U1 u1_a_unit, U1 u1_a_overheat)
{
    U1  u1_t_ret;
    U1  u1_t_ovht;
    U1  u1_t_hys;
    U1  u1_t_chk;
    ST_OILTMP_OVERHEAT_HYS st_tp_oiltmp_overheat_hystbl[OILTMP_UNIT_TYP_MAX];

    u1_t_ovht = (U1)OILTMP_OVERHEAT_TMP;
    u1_t_hys  = u1_OILTMP_HYSTERESIS;

    if(u1_t_ovht > u1_t_hys){
        u1_t_chk = u1_t_ovht - u1_t_hys;
    }
    else{
        u1_t_chk = (U1)0U;
    }

    st_tp_oiltmp_overheat_hystbl[OILTMP_UNIT_TYP_FMAP].u2_oh_off = u2_OILTMP_FMAP_OVERHEAT_HYS(u1_t_chk);
    st_tp_oiltmp_overheat_hystbl[OILTMP_UNIT_TYP_FMAP].u2_oh_on  = u2_OILTMP_FMAP_OVERHEAT_HYS(u1_t_ovht);
    st_tp_oiltmp_overheat_hystbl[OILTMP_UNIT_TYP_CMAP].u2_oh_off = u2_OILTMP_CMAP_OVERHEAT_HYS(u1_t_chk);
    st_tp_oiltmp_overheat_hystbl[OILTMP_UNIT_TYP_CMAP].u2_oh_on  = u2_OILTMP_CMAP_OVERHEAT_HYS(u1_t_ovht);

    if(u1_a_overheat > (U1)OILTMP_OVERHEAT_ON){
        u1_a_overheat = (U1)OILTMP_OVERHEAT_OFF;
    }

    if(u1_a_unit < (U1)OILTMP_UNIT_TYP_MAX){
        if(u2_a_dspval <= st_tp_oiltmp_overheat_hystbl[u1_a_unit].u2_oh_off){
            u1_t_ret = (U1)OILTMP_OVERHEAT_OFF;
        }
        else if(u2_a_dspval >= st_tp_oiltmp_overheat_hystbl[u1_a_unit].u2_oh_on){
            u1_t_ret = (U1)OILTMP_OVERHEAT_ON;
        }
        else{
            u1_t_ret = u1_a_overheat;
        }
    }
    else{
        u1_t_ret = u1_a_overheat;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U2      u2_g_OilTmpVal(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         ST_OILTMP_VAR st_s_oiltmp.u2_dspseg                                                                              */
/*===================================================================================================================================*/
U2      u2_g_OilTmpVal(void)
{
    return(st_s_oiltmp.u2_dspseg);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilTmpOverheatsts(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 st_s_oiltmp.u1_overheat                                                                                       */
/*===================================================================================================================================*/
U1      u1_g_OilTmpOverheatsts(void)
{
    return(st_s_oiltmp.u1_overheat);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilTmpUnit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
U1      u1_g_OilTmpUnit(void)
{
    U1 u1_t_unit;
    U1 u1_t_ret;

    u1_t_unit = st_s_oiltmp.u1_unit & (U1)OILTMP_TEMPC;

    if(u1_t_unit == (U1)OILTMP_TEMPF){
        u1_t_ret = (U1)OILTMP_TEMPF;
    }
    else{
        u1_t_ret = (U1)OILTMP_TEMPC;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilTmpCalibReadTmpCel(U2* u2p_a_calib_tmpc_max, U2* u2p_a_calib_tmpc_min)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2* u2p_a_calib_tmpc_max                                                                                         */
/*                  U2* u2p_a_calib_tmpc_min                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilTmpCalibReadTmpCel(U2* u2p_a_calib_tmpc_max, U2* u2p_a_calib_tmpc_min)
{
    U2 u2_t_tmpc_max;
    U2 u2_t_tmpc_min;

    u2_t_tmpc_max = u2_OILTMP_CALIB_OLTMAXC;
    u2_t_tmpc_min = u2_OILTMP_CALIB_OLTMINC;

    if(u2_t_tmpc_min > u2_t_tmpc_max){
        u2_t_tmpc_max = (U2)OILTMP_TMPC_MAX_DEF;
        u2_t_tmpc_min = (U2)OILTMP_TMPC_MIN_DEF;
    }

    *u2p_a_calib_tmpc_max = u2_t_tmpc_max;
    *u2p_a_calib_tmpc_min = u2_t_tmpc_min;
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilTmpCalibReadTmpFah(U2* u2p_a_calib_tmpf_max, U2* u2p_a_calib_tmpf_min)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2* u2p_a_calib_tmpf_max                                                                                         */
/*                  U2* u2p_a_calib_tmpf_min                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilTmpCalibReadTmpFah(U2* u2p_a_calib_tmpf_max, U2* u2p_a_calib_tmpf_min)
{
    U2 u2_t_tmpf_max;
    U2 u2_t_tmpf_min;

    u2_t_tmpf_max = u2_OILTMP_CALIB_OLTMAXF;
    u2_t_tmpf_min = u2_OILTMP_CALIB_OLTMINF;

    if(u2_t_tmpf_min > u2_t_tmpf_max){
        u2_t_tmpf_max = (U2)OILTMP_TMPF_MAX_DEF;
        u2_t_tmpf_min = (U2)OILTMP_TMPF_MIN_DEF;
    }

    *u2p_a_calib_tmpf_max = u2_t_tmpf_max;
    *u2p_a_calib_tmpf_min = u2_t_tmpf_min;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  0.0.0           04/15/2013  YK      New.                                                                                         */
/*  0.0.1           05/08/2013  YK      Support for sample software.                                                                 */
/*  0.0.2           05/17/2013  YK      Overheat judgment statement correction.                                                      */
/*  0.0.3           05/20/2013  YK      Remove Unwanted Macros.                                                                      */
/*  0.0.4           05/22/2013  YK      Treatment improvement.                                                                       */
/*  0.0.5           11/22/20132 YK      Addition of oil temperature abnormal value judgment processing.                              */
/*                                      Review of temperature and Middle East information acquisition process.                       */
/*  0.1.0           12/21/2020  SK      Addition of temperature and Middle East information acquisition process                      */
/*                                      Change judg of unit info                                                                     */
/*  1.0.0           12/13/2021  SK      Chabge notice value range of oiltemp                                                         */
/*                                                                                                                                   */
/*  Revision        Date        Author   Change Description                                                                          */
/* ---------        ----------  -------  --------------------------------------------------------------------------------------------*/
/*  19PFv3-1        10/16/2023  SH       scc merge and change reading calibration                                                    */
/*  19PFv3-2        02/12/2024  SH       Add vd_s_OilTmpCalibReadTmpCel() and vd_s_OilTmpCalibReadTmpFah                             */
/*  19PFv3-3        04/16/2024  SH       Add calibration guard                                                                       */
/*  19PFv3-4        05/22/2024  TN       Change for MET19PFV3-4469                                                                   */
/*  19PFv3-5        06/27/2024  TN       Delete Calibration Guard Process.                                                           */
/*  19PFv3-6        07/02/2024  KH       Change for 19PFv3 R1.2                                                                      */
/*                                                                                                                                   */
/*  * YK = Yosuke Kawahara, NCOS                                                                                                     */
/*  * SK = Shintaro Kanou, Densotechno                                                                                               */
/*  * SH = Sae Hirose, Denso Techno                                                                                                  */
/*  * TN = Tetsushi Nakano, Denso Techno                                                                                             */
/*  * KH = Kiko Huerte, DTPH                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
