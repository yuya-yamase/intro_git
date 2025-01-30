/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Ambient Temprature Celsius/Fahrenheit                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AMBTMP_C_MAJOR                         (2)
#define AMBTMP_C_MINOR                         (2)
#define AMBTMP_C_PATCH                         (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ambtmp_cfg_private.h"
#include "ambtmp_ad.h"
#include "ambtmp_can.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AMBTMP_C_MAJOR != AMBTMP_H_MAJOR) || \
     (AMBTMP_C_MINOR != AMBTMP_H_MINOR) || \
     (AMBTMP_C_PATCH != AMBTMP_H_PATCH))
#error "ambtmp.c and ambtmp.h : source and header files are inconsistent!"
#endif

#if ((AMBTMP_C_MAJOR != AMBTMP_CFG_H_MAJOR) || \
     (AMBTMP_C_MINOR != AMBTMP_CFG_H_MINOR) || \
     (AMBTMP_C_PATCH != AMBTMP_CFG_H_PATCH))
#error "ambtmp.c and ambtmp_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AMBTMP_NUM_SNSRIF           (2U)

#define AMBTMP_NUM_DEGREE           (2U)
#define AMBTMP_DEG_CELSIUS          (0U)
#define AMBTMP_DEG_FAHRENHEIT       (1U)

#define AMBTMP_DEG_0P49             (49U)
#define AMBTMP_DEG_0P50             (50U)
#define AMBTMP_DEG_RES              (100U)
#define AMBTMP_OFFSET               (4000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                          u2_deg;
    U2                          u2_dsp;
    U1                          u1_icew;
    U1                          u1_icyraw;
}ST_AMBTMP_DEG;

typedef struct{
    U2                          u2_hi;
    U2                          u2_lo;
}ST_AMBTMP_ICEW;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1               u1_s_ambtmp_sts;
static U1               u1_s_ambtmp_trvl_flg;                   /* Travelling Flag      */
static ST_AMBTMP_DEG    st_sp_ambtmp[AMBTMP_NUM_DEGREE];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_AmbtmpDspCel(const U2 u2_a_CEL_0P01, const U1 u1_a_IFIDX);
static U2   u2_s_AmbtmpDspFah(const U2 u2_a_FAH_0P01);
static void vd_s_AmbtmpIceWrnChk(void);
static void vd_s_AmbtmpTrvlFlgChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AmbtmpInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AmbtmpBonInit(void)
{

    u1_s_ambtmp_sts                               = (U1)AMBTMP_STS_UNKNOWN;
    u1_s_ambtmp_trvl_flg                          = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_dsp    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u1_icew   = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u1_icyraw = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_dsp    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icew   = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icyraw = (U1)FALSE;

    vd_g_AmbtmpAdBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_AmbtmpRstWkInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AmbtmpRstWkInit(void)
{

    u1_s_ambtmp_sts                               = (U1)AMBTMP_STS_UNKNOWN;
    u1_s_ambtmp_trvl_flg                          = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_dsp    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u1_icew   = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u1_icyraw = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_dsp    = (U2)AMBTMP_DEG_UNK;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icew   = (U1)FALSE;
    st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icyraw = (U1)FALSE;

    vd_g_AmbtmpAdRstWkInit();

}
/*===================================================================================================================================*/
/*  void    vd_g_AmbtmpOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AmbtmpOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U1  u1_t_comp;

    u1_t_comp = u1_g_AmbtmpAdInitComp();
    if(u1_t_comp == (U1)TRUE){
        vd_g_AmbtmpCfgOpemdEvhk(u4_a_MDBIT, u4_a_EVTBIT);
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_AmbtmpMainTask(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AmbtmpMainTask(void)
{
    static U1      (* const fp_sp_u1_AMBTMP_IF[AMBTMP_NUM_SNSRIF])(U2 * u2p_a_cel) ={
        &u1_g_AmbtmpCAN,
        &u1_g_AmbtmpAd
    };

    U1  u1_t_ifidx;
    U4  u4_t_fah;

    vd_g_AmbtmpCfgMainStart();

    u1_t_ifidx   = u1_g_AmbtmpCfgIFIdx();

    if((u1_t_ifidx < (U1)AMBTMP_NUM_SNSRIF) && (fp_sp_u1_AMBTMP_IF[u1_t_ifidx] != vdp_PTR_NA)){
        u1_s_ambtmp_sts = (fp_sp_u1_AMBTMP_IF[u1_t_ifidx])(&st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg);
        if(st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg >= (U2)AMBTMP_DEG_UNK){
            st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg = (U2)AMBTMP_DEG_UNK;
        }
        else{
            u4_t_fah  = ((U4)st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg * (U4)AMBTMP_CEL2FAH_COEF);
            /* The maximum value of u2_deg is 65534, value of AMBTMP_CEL2FAH_COEF is 18.                           */
            /* so (u2_deg * AMBTMP_CEL2FAH_COEF) is always less than U4_MAX.                                       */
            u4_t_fah /= (U4)AMBTMP_CEL2FAH_DIV;
            if(u4_t_fah >= (U4)AMBTMP_DEG_UNK) {
                st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg = (U2)AMBTMP_DEG_UNK;
            }else{
                st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg = (U2)u4_t_fah;
            }
        }
        st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_dsp = u2_s_AmbtmpDspCel(st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg, u1_t_ifidx);
        st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_dsp = u2_s_AmbtmpDspFah(st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg);
        vd_s_AmbtmpTrvlFlgChk();
        vd_s_AmbtmpIceWrnChk();
    }
    else{
        vd_g_AmbtmpAdBonInit(); 
    }
    vd_g_AmbtmpCfgMainFinish(u1_s_ambtmp_sts, st_sp_ambtmp[AMBTMP_DEG_CELSIUS].u2_deg, st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpCel(U2 * u2p_a_cel)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpCel(U2 * u2p_a_cel)
{
    if(u2p_a_cel != vdp_PTR_NA){
        *u2p_a_cel = st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_dsp;
    }
    return(u1_s_ambtmp_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpCelInst(U2 * u2p_a_cel)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpCelInst(U2 * u2p_a_cel)
{
    if(u2p_a_cel != vdp_PTR_NA){
        *u2p_a_cel = st_sp_ambtmp[AMBTMP_DEG_CELSIUS   ].u2_deg;
    }
    return(u1_s_ambtmp_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpFah(U2 * u2p_a_fah)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpFah(U2 * u2p_a_fah)
{
    if(u2p_a_fah != vdp_PTR_NA){
        *u2p_a_fah = st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_dsp;
    }
    return(u1_s_ambtmp_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpFahInst(U2 * u2p_a_fah)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpFahInst(U2 * u2p_a_fah)
{
    if(u2p_a_fah != vdp_PTR_NA){
        *u2p_a_fah = st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u2_deg;
    }
    return(u1_s_ambtmp_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIceWrnActCel(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIceWrnAct(void)
{
    U1  u1_t_icew;
    U1  u1_t_unit;

    u1_t_unit = u1_g_AmbtmpCfgUnit();
    if(u1_t_unit == (U1)AMBTMP_UNIT_CEL){
        u1_t_icew = st_sp_ambtmp[AMBTMP_DEG_CELSIUS].u1_icew;
    }
    else{
        u1_t_icew = st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icew;
    }
    return(u1_t_icew);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIcyraWrnAct(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIcyraWrnAct(void)
{
    U1  u1_t_icyraw;
    U1  u1_t_unit;

    u1_t_unit = u1_g_AmbtmpCfgUnit();
    if(u1_t_unit == (U1)AMBTMP_UNIT_CEL){
        u1_t_icyraw = st_sp_ambtmp[AMBTMP_DEG_CELSIUS].u1_icyraw;
    }
    else{
        u1_t_icyraw = st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icyraw;
    }
    return(u1_t_icyraw);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIceWrnActCel(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIceWrnActCel(void)
{
    return(st_sp_ambtmp[AMBTMP_DEG_CELSIUS].u1_icew);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIcyraWrnActCel(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIcyraWrnActCel(void)
{
    return(st_sp_ambtmp[AMBTMP_DEG_CELSIUS].u1_icyraw);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIceWrnActCel(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIceWrnActFah(void)
{
    return(st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icew);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpIcyraWrnActCel(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpIcyraWrnActFah(void)
{
    return(st_sp_ambtmp[AMBTMP_DEG_FAHRENHEIT].u1_icyraw);
}

/*===================================================================================================================================*/
/*  static U2   u2_s_AmbtmpDspCel(const U2 u2_a_CEL_0P01, const U1 u1_a_IFIDX)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_AmbtmpDspCel(const U2 u2_a_CEL_0P01, const U1 u1_a_IFIDX)
{
    U2  u2_t_quo_1cel;
    U2  u2_t_dsp_0p01cel;

    if(u2_a_CEL_0P01 >= (U2)AMBTMP_DEG_UNK){
        u2_t_dsp_0p01cel = (U2)AMBTMP_DEG_UNK;
    }
    else{
        if(u1_a_IFIDX == (U1)AMBTMP_IF_CAN){
            u2_t_quo_1cel = u2_a_CEL_0P01 / (U2)AMBTMP_DEG_RES;
        }
        else{
            if(u2_a_CEL_0P01 < (U2)AMBTMP_OFFSET) {
                u2_t_quo_1cel = u2_a_CEL_0P01 + (U2)AMBTMP_DEG_0P49;
            }
            else{
                if(((U2)U2_MAX - (U2)AMBTMP_DEG_0P50) > u2_a_CEL_0P01 ){
                    u2_t_quo_1cel = u2_a_CEL_0P01 + (U2)AMBTMP_DEG_0P50;
                }
                else{
                    u2_t_quo_1cel = (U2)U2_MAX;
                }
            }
            u2_t_quo_1cel /= (U2)AMBTMP_DEG_RES;
        }
        u2_t_dsp_0p01cel = (u2_t_quo_1cel * (U2)AMBTMP_DEG_RES);
    }
    return(u2_t_dsp_0p01cel);
}

/*===================================================================================================================================*/
/*  static U2   u2_s_AmbtmpDspFah(const U2 u2_a_FAH_0P01)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2   u2_s_AmbtmpDspFah(const U2 u2_a_FAH_0P01)
{
    U2  u2_t_quo_1fah;
    U2  u2_t_dsp_0p01fah;

    if(u2_a_FAH_0P01 >= (U2)AMBTMP_DEG_UNK){
        u2_t_dsp_0p01fah = (U2)AMBTMP_DEG_UNK;
    }
    else{
        if(u2_a_FAH_0P01 < (U2)AMBTMP_OFFSET) {
                u2_t_quo_1fah = u2_a_FAH_0P01 + (U2)AMBTMP_DEG_0P49;
        }
        else{
            if(((U2)U2_MAX - (U2)AMBTMP_DEG_0P50) > u2_a_FAH_0P01 ){
                u2_t_quo_1fah = u2_a_FAH_0P01 + (U2)AMBTMP_DEG_0P50;
            }
            else{
                u2_t_quo_1fah = (U2)U2_MAX;
            }
        }
        u2_t_quo_1fah    /= (U2)AMBTMP_DEG_RES;
        u2_t_dsp_0p01fah  = (u2_t_quo_1fah * (U2)AMBTMP_DEG_RES);
    }
    return(u2_t_dsp_0p01fah);
}

/*===================================================================================================================================*/
/*  static void vd_s_AmbtmpIceWrnChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_AmbtmpIceWrnChk(void)
{
    static const ST_AMBTMP_ICEW st_sp_AMBTMP_ICEW[AMBTMP_NUM_DEGREE] = {
        {(U2)4500U, (U2)4300U},     /* 5.0 degree celsius: 4000 + 5.0 * 100, 3.0 degree celsius: 4000 + 3.0 * 100                    */
        {(U2)8100U, (U2)7700U},     /* 41.0 degree Fahrenheit: 4000 + 41.0 * 100, 37.0 degree Fahrenheit: 4000 + 37.0 * 100          */
    };
    U1 u1_t_trvl_dst_flg;               /* Travelling Distance Flag         */
    U4 u4_t_loop;

    u1_t_trvl_dst_flg = u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_OFF);

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)AMBTMP_NUM_DEGREE ; u4_t_loop++){
        if(u1_s_ambtmp_sts != (U1)AMBTMP_STS_VALID){
            st_sp_ambtmp[u4_t_loop].u1_icew = (U1)FALSE;
        }
        else{
            if(st_sp_ambtmp[u4_t_loop].u2_dsp >= st_sp_AMBTMP_ICEW[u4_t_loop].u2_hi){
                st_sp_ambtmp[u4_t_loop].u1_icew = (U1)FALSE;
            }
            else if(st_sp_ambtmp[u4_t_loop].u2_dsp <= st_sp_AMBTMP_ICEW[u4_t_loop].u2_lo){
                st_sp_ambtmp[u4_t_loop].u1_icew = (U1)TRUE;
            }
            else{
                /* keep st_sp_ambtmp[u4_t_loop].u1_icew */
            }
        }
        if((u1_t_trvl_dst_flg               == (U1)TRUE) &&
           (u1_s_ambtmp_trvl_flg            == (U1)TRUE) &&
           (st_sp_ambtmp[u4_t_loop].u1_icew == (U1)TRUE)) {
            st_sp_ambtmp[u4_t_loop].u1_icyraw = (U1)TRUE;
        }
        else{
            st_sp_ambtmp[u4_t_loop].u1_icyraw = (U1)FALSE;
        }
    }
}

/*===================================================================================================================================*/
/*  static void vd_s_AmbtmpTrvlFlgChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_AmbtmpTrvlFlgChk(void)
{
    static const U2         u2_s_AMBTMP_TRVLFLG_5KMH    = (U2)500U;     /* 5km/h Threshold (LSB0.01km/h)    */
    static const U2         u2_s_AMBTMP_TRVLFLG_4KMH    = (U2)400U;     /* 4km/h Threshold (LSB0.01km/h)    */

    U1 u1_t_spdsts;                                                     /* Vehicle Speed Status             */
    U2 u2_t_vehspd;                                                     /* Vehicle Speed(LSB0.01km/h)       */

    u2_t_vehspd = (U2)0U;
    u1_t_spdsts = u1_g_VehspdKmphInst(&u2_t_vehspd, (U1)TRUE);

    if(u1_t_spdsts != (U1)AMBTMP_STS_VALID){
        u1_s_ambtmp_trvl_flg = (U1)FALSE;
    }
    else{
        if(u2_t_vehspd >= u2_s_AMBTMP_TRVLFLG_5KMH){
            u1_s_ambtmp_trvl_flg = (U1)TRUE;
        }
        else if(u2_t_vehspd <= u2_s_AMBTMP_TRVLFLG_4KMH){
            u1_s_ambtmp_trvl_flg = (U1)FALSE;
        }
        else{
            /* keep u1_s_ambtmp_trvl_flg */
        }
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
/*  1.0.0    10/08/2018  TA       New.                                                                                               */
/*  1.1.0    03/10/2020  YN       Road surface freeze indication judgment added                                                      */
/*  1.1.1    05/14/2020  YN       Added void pointer to NULL                                                                         */
/*  1.2.1    06/15/2020  YN       Disable Warning IF as a temporary measure                                                          */
/*  1.2.2    07/21/2020  YN       Fix casting & remove extra commas                                                                  */
/*  1.3.2    07/27/2020  YN       Set the threshold of the freeze icon for each temperature unit.                                    */
/*  2.0.0    04/30/2021  TA       Delete u1_g_AmbtmpCelFahByUnit                                                                     */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    11/25/2021  TA(M)    Change judge ice warning in Celsius and Fahrenheit respectively                                    */
/*  2.2.0    03/07/2022  TA(M)    Change the processing when unknows of ambtmp_ad                                                    */
/*  2.2.1    06/28/2022  TA(M)    Change rounding logic of u2_s_AmbtmpDspCel/u2_s_AmbtmpDspFah                                       */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
