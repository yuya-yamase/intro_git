/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oil pressure                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILPRSS_C_MAJOR                          (1)
#define OILPRSS_C_MINOR                          (0)
#define OILPRSS_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oilpress_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OILPRSS_C_MAJOR != OILPRSS_H_MAJOR) || \
     (OILPRSS_C_MINOR != OILPRSS_H_MINOR) || \
     (OILPRSS_C_PATCH != OILPRSS_H_PATCH))
#error "oilpress.c and oilpress.h : source and header files are inconsistent!"
#endif

#if ((OILPRSS_C_MAJOR != OILPRSS_CFG_H_MAJOR) || \
     (OILPRSS_C_MINOR != OILPRSS_CFG_H_MINOR) || \
     (OILPRSS_C_PATCH != OILPRSS_CFG_H_PATCH))
#error "oilpress.c and oilpress_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OILPRSS_OFF                              (0U)
#define OILPRSS_INIT_OR_FAIL                     (1U)
#define OILPRSS_UPDT                             (2U)
#define OILPRSS_WRN                              (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1 u1_s_rcvd;
    U1 u1_dat_adr;
    U2 u2_dat[OILPRSS_BPOM_AVENUM];
    U1 u1_calsts;
    U2 u2_dspseg;
}ST_OILPRSS_VAR;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OILPRSS_VAR  st_s_oilprss;
static U1 u1_s_oilprss_sts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U2       u2_s_OilPrssCal(void);
static        void     vd_s_OilPrssClrInc(void);
static        void     vd_s_OilPrssBufIn(const ST_FSPOSNSR_INCARG* stp_a_incarg);
static        void     vd_s_OilPrssCalibReadPsi(U1* u1p_a_calib_psi_max, U1* u1p_a_calib_psi_min);
static        void     vd_s_OilPrssCalibReadBar(U1* u1p_a_calib_bar_max, U1* u1p_a_calib_bar_min);
static        void     vd_s_OilPrssCalibReadKpa(U1* u1p_a_calib_kpa_max, U1* u1p_a_calib_kpa_min);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OilPrssInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilPrssInit(void)
{
    vd_s_OilPrssClrInc();

    st_s_oilprss.u2_dspseg = (U2)OILPRSS_INIT_FAIL_VLE;
    st_s_oilprss.u1_calsts = (U1)OILPRSS_OFF;

    st_s_oilprss.u1_s_rcvd = (U1)FALSE;
    u1_s_oilprss_sts = (U1)OILPRSS_WRNOFF;
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilPrssClrInc(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilPrssClrInc(void)
{
    U1 u1_t_idx;

    st_s_oilprss.u1_dat_adr = (U1)0U;
    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILPRSS_BPOM_AVENUM; u1_t_idx++){
        st_s_oilprss.u2_dat[u1_t_idx] = (U2)0U;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilPrssInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilPrssInc(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    U2 u2_t_fail;

    u2_t_fail = stp_a_incarg->u2_sigfail & (U2)OILPRSS_FAILCHK;
    if(u2_t_fail == (U2)0U){
        if((stp_a_incarg->u1_rcvd & (U1)OILPRSS_ENG1G17RCVD) == (U1)OILPRSS_ENG1G17RCVD){
            vd_s_OilPrssBufIn(stp_a_incarg);
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilPrssBufIn(const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_incarg)                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OilPrssBufIn(const ST_FSPOSNSR_INCARG* stp_a_incarg)
{
    U1 u1_t_idx;

    if(st_s_oilprss.u1_s_rcvd == (U1)FALSE){
        for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILPRSS_BPOM_AVENUM; u1_t_idx++){
           st_s_oilprss.u2_dat[u1_t_idx] = stp_a_incarg->st_inc_eng1g17.u2_bpom;
        }
    }
    else{
        if(st_s_oilprss.u1_dat_adr >= (U1)OILPRSS_BPOM_AVENUM){
            st_s_oilprss.u1_dat_adr = (U1)0U;
        }
        st_s_oilprss.u2_dat[ st_s_oilprss.u1_dat_adr ] = stp_a_incarg->st_inc_eng1g17.u2_bpom;

        st_s_oilprss.u1_dat_adr = (st_s_oilprss.u1_dat_adr >= ((U1)OILPRSS_BPOM_AVENUM - (U1)1U )) ? (U1)0U : (st_s_oilprss.u1_dat_adr + (U1)1U);
    }

    st_s_oilprss.u1_s_rcvd = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  void    vd_g_OilPrssTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U2 u2_a_evtbit                                                                                                   */
/*                  U2 u2_a_sigfail                                                                                                  */
/*  Return:         -                                                                                                                */
/*  ATTENTION:      Priority (IG state > oil pressure warning > ENG1G17 communication failure > pressure unit state)                 */
/*===================================================================================================================================*/
void    vd_g_OilPrssTrnsit(U2 u2_a_evtbit, U2 u2_a_sigfail)
{
    U2 u2_t_igon;
    U2 u2_t_oilprswrn;
    U2 u2_t_fail;

    u2_t_igon      = u2_a_evtbit  & (U2)OILPRSS_IGON_EVT;
    u2_t_oilprswrn = u2_a_evtbit  & (U2)OILPRSS_OILWRN_EVT;
    u2_t_fail      = u2_a_sigfail & (U2)OILPRSS_FAILCHK;

    if(u2_t_igon != (U2)OILPRSS_IGON_EVT){
        st_s_oilprss.u1_calsts = (U1)OILPRSS_OFF;
        vd_s_OilPrssClrInc();
        st_s_oilprss.u1_s_rcvd = (U1)FALSE;
    }
    else if(u2_t_oilprswrn == (U2)OILPRSS_OILWRN_EVT){
        st_s_oilprss.u1_calsts = (U1)OILPRSS_WRN;
        if(u2_t_fail != (U2)0U){
            vd_s_OilPrssClrInc();
            st_s_oilprss.u1_s_rcvd = (U1)FALSE;
        }
    }
    else if(u2_t_fail != (U2)0U){
        st_s_oilprss.u1_calsts = (U1)OILPRSS_INIT_OR_FAIL;
        vd_s_OilPrssClrInc();
        st_s_oilprss.u1_s_rcvd = (U1)FALSE;
    }
    else{
        switch(st_s_oilprss.u1_calsts){
            case OILPRSS_OFF:
            case OILPRSS_WRN:
            case OILPRSS_INIT_OR_FAIL:
                if(st_s_oilprss.u1_s_rcvd == (U1)TRUE){
                    st_s_oilprss.u1_calsts = (U1)OILPRSS_UPDT;
                }
                else{
                    st_s_oilprss.u1_calsts = (U1)OILPRSS_INIT_OR_FAIL;
                }
                break;
            case OILPRSS_UPDT:
                if(st_s_oilprss.u1_s_rcvd != (U1)TRUE){
                    st_s_oilprss.u1_calsts = (U1)OILPRSS_INIT_OR_FAIL;
                    vd_s_OilPrssClrInc();
                    st_s_oilprss.u1_s_rcvd = (U1)FALSE;
                }
                break;
            default:
                st_s_oilprss.u1_calsts = (U1)OILPRSS_INIT_OR_FAIL;
                vd_s_OilPrssClrInc();
                st_s_oilprss.u1_s_rcvd = (U1)FALSE;
                break;
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_OilPrssUpdt(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OilPrssUpdt(void)
{
    switch(st_s_oilprss.u1_calsts){
        case OILPRSS_UPDT:
            st_s_oilprss.u2_dspseg = u2_s_OilPrssCal();
            u1_s_oilprss_sts = (U1)OILPRSS_WRNOFF;
            break;
        case OILPRSS_WRN:
            st_s_oilprss.u2_dspseg = u2_s_OilPrssCal();
            u1_s_oilprss_sts = (U1)OILPRSS_WRNON;
            break;
        case OILPRSS_OFF:
        case OILPRSS_INIT_OR_FAIL:
        default:
            st_s_oilprss.u2_dspseg = (U2)OILPRSS_INIT_FAIL_VLE;
            u1_s_oilprss_sts = (U1)OILPRSS_WRNOFF;
            break;
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_OilPrssCal(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U2 (U2)u4_t_val                                                                                                  */
/*===================================================================================================================================*/
static U2       u2_s_OilPrssCal(void)
{
    U4 u4_t_val;
    U1 u1_t_idx;
    U1 u1_t_unit;
    U1 u1_t_psi_min;
    U1 u1_t_psi_max;
    U1 u1_t_bar_min;
    U1 u1_t_bar_max;
    U1 u1_t_kpa_min;
    U1 u1_t_kpa_max;
    U4 u4_t_min;
    U4 u4_t_max;

    u4_t_val         = (U4)0U;
    u1_t_psi_min     = (U1)OILPRSS_PSI_MIN_DEF;
    u1_t_psi_max     = (U1)OILPRSS_PSI_MAX_DEF;
    u1_t_bar_min     = (U1)OILPRSS_BAR_MIN_DEF;
    u1_t_bar_max     = (U1)OILPRSS_BAR_MAX_DEF;
    u1_t_kpa_min     = (U1)OILPRSS_KPA_MIN_DEF;
    u1_t_kpa_max     = (U1)OILPRSS_KPA_MAX_DEF;

    vd_s_OilPrssCalibReadPsi(&u1_t_psi_max, &u1_t_psi_min);
    vd_s_OilPrssCalibReadBar(&u1_t_bar_max, &u1_t_bar_min);
    vd_s_OilPrssCalibReadKpa(&u1_t_kpa_max, &u1_t_kpa_min);

    for(u1_t_idx = (U1)0U; u1_t_idx < (U1)OILPRSS_BPOM_AVENUM; u1_t_idx++){
        if( st_s_oilprss.u2_dat[ u1_t_idx ] > (U2)OILPRSS_BPOMSIG_MAX ){
            u4_t_val += (U4)OILPRSS_BPOMSIG_MAX;
        }
        else{
            u4_t_val += (U4)st_s_oilprss.u2_dat[ u1_t_idx ];
        }
    }


    u1_t_unit = u1_OILPRSS_PRSSUNIT();
    if(u1_t_unit == (U1)OILPRSS_UNIT_PSI){
        u4_t_min  = u4_OILPRESS_CVT(u1_t_psi_min);
        u4_t_max  = u4_OILPRESS_CVT(u1_t_psi_max);
        u4_t_val  = ( u4_t_val * (U4)OILPRSS_PSI_MULU ) / (U4)OILPRSS_PSI_DIV;
        if(u4_t_val < u4_t_min){
            u4_t_val = u4_t_min;
        }
        if(u4_t_val > u4_t_max){
            u4_t_val = u4_t_max;
        }
    }
    else if(u1_t_unit == (U1)OILPRSS_UNIT_BAR){
        u4_t_min  = u4_OILPRESS_CVT(u1_t_bar_min);
        u4_t_max  = u4_OILPRESS_CVT(u1_t_bar_max);
        u4_t_val  = ( u4_t_val * (U4)OILPRSS_LSB_MULU ) / (U4)OILPRSS_LSB_DIV;
        if(u4_t_val < u4_t_min){
            u4_t_val = u4_t_min;
        }
        if(u4_t_val > u4_t_max){
            u4_t_val = u4_t_max;
        }
    }
    else{
        u4_t_min  = u4_OILPRESS_CVT(u1_t_kpa_min);
        u4_t_max  = u4_OILPRESS_CVT(u1_t_kpa_max);
        u4_t_val = (u4_t_val * (U4)OILPRSS_LSB_MULU) / (U4)OILPRSS_LSB_DIV;
        if(u4_t_val < u4_t_min){
            u4_t_val = u4_t_min;
        }
        if(u4_t_val > u4_t_max){
            u4_t_val = u4_t_max;
        }
    }

    return((U2)u4_t_val);
}

/*===================================================================================================================================*/
/*  U2      u2_g_OilPrssVal(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 st_s_oilprss.u2_dspseg                                                                                        */
/*===================================================================================================================================*/
U2      u2_g_OilPrssVal(void)
{
    return(st_s_oilprss.u2_dspseg);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OilPrssSts(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 st_s_oilprss_sts                                                                                              */
/*===================================================================================================================================*/
U1      u1_g_OilPrssSts(void)
{
    return(u1_s_oilprss_sts);
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilPrssCalibReadPsi(U1* u1p_a_calib_psi_max, U1* u1p_a_calib_psi_min)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1* u1p_a_calib_psi_max                                                                                          */
/*                  U1* u1p_a_calib_psi_min                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilPrssCalibReadPsi(U1* u1p_a_calib_psi_max, U1* u1p_a_calib_psi_min)
{
    U1 u1_t_psi_max;
    U1 u1_t_psi_min;

    u1_t_psi_max = u1_OILPRSS_CALIB_PSI_MAX;
    u1_t_psi_min = u1_OILPRSS_CALIB_PSI_MIN;

    if(u1_t_psi_min > u1_t_psi_max){
        u1_t_psi_max = (U1)OILPRSS_PSI_MAX_DEF;
        u1_t_psi_min = (U1)OILPRSS_PSI_MIN_DEF;
    }

    *u1p_a_calib_psi_max = u1_t_psi_max;
    *u1p_a_calib_psi_min = u1_t_psi_min;
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilPrssCalibReadBar(U1* u1p_a_calib_bar_max, U1* u1p_a_calib_bar_min)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1* u1p_a_calib_psi_max                                                                                          */
/*                  U1* u1p_a_calib_psi_min                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilPrssCalibReadBar(U1* u1p_a_calib_bar_max, U1* u1p_a_calib_bar_min)
{
    U1 u1_t_bar_max;
    U1 u1_t_bar_min;

    u1_t_bar_max = u1_OILPRSS_CALIB_BAR_MAX;
    u1_t_bar_min = u1_OILPRSS_CALIB_BAR_MIN;

    if(u1_t_bar_min > u1_t_bar_max){
        u1_t_bar_max = (U1)OILPRSS_BAR_MAX_DEF;
        u1_t_bar_min = (U1)OILPRSS_BAR_MIN_DEF;
    }

    *u1p_a_calib_bar_max = u1_t_bar_max;
    *u1p_a_calib_bar_min = u1_t_bar_min;
}

/*===================================================================================================================================*/
/*  static void     vd_s_OilPrssCalibReadKpa(U1* u1p_a_calib_kpa_max, U1* u1p_a_calib_kpa_min)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      U1* u1p_a_calib_psi_max                                                                                          */
/*                  U1* u1p_a_calib_psi_min                                                                                          */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_OilPrssCalibReadKpa(U1* u1p_a_calib_kpa_max, U1* u1p_a_calib_kpa_min)
{
    U1 u1_t_kpa_max;
    U1 u1_t_kpa_min;

    u1_t_kpa_max = u1_OILPRSS_CALIB_KPA_MAX;
    u1_t_kpa_min = u1_OILPRSS_CALIB_KPA_MIN;

    if(u1_t_kpa_min > u1_t_kpa_max){
        u1_t_kpa_max = (U1)OILPRSS_KPA_MAX_DEF;
        u1_t_kpa_min = (U1)OILPRSS_KPA_MIN_DEF;
    }

    *u1p_a_calib_kpa_max = u1_t_kpa_max;
    *u1p_a_calib_kpa_min = u1_t_kpa_min;
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
/*  0.0.2           05/20/2013  YK      Remove Unwanted Macros.                                                                      */
/*  0.0.3           05/22/2013  YK      Treatment improvement.                                                                       */
/*  0.1.0           12/14/2020  SK      Add OilPress Abnomal Sts Notice function                                                     */
/*                                      change First Accumulation process                                                            */
/*  1.0.0           12/13/2021  SK      Change notice value range of Oilpress.                                                       */
/*                                                                                                                                   */
/*  Revision        Date        Author   Change Description                                                                          */
/* ---------        ----------  -------  --------------------------------------------------------------------------------------------*/
/*  19PFv3-1        10/16/2023  SH       scc merge and change reading calibration                                                    */
/*  19PFv3-2        02/12/2024  SH       Add vd_s_OilPrssCalibReadPsi(), vd_s_OilPrssCalibReadBar() and vd_s_OilPrssCalibReadKpa()   */
/*  19PFv3-3        04/16/2024  SH       Add calibration guard                                                                       */
/*  19PFv3-4        05/22/2024  TN       Change for MET19PFV3-6133                                                                   */
/*  19PFv3-5        06/27/2024  TN       Delete Calibration Guard Process.                                                           */
/*  19PFv3-6        07/09/2024  KH       Remove logic for pressure unit fail event                                                   */
/*                                                                                                                                   */
/*  * YK = Yosuke Kawahara, NCOS                                                                                                     */
/*  * SK = Shintaro Kanou, Denso Techno                                                                                              */
/*  * SH = Sae Hirose, Denso Techno                                                                                                  */
/*  * TN = Tetsushi Nakano, Denso Techno                                                                                             */
/*  * KH = Kiko Huerte, DTPH                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
