/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_VPTRAN_C_MAJOR                     (0)
#define XSPI_VPTRAN_C_MINOR                     (0)
#define XSPI_VPTRAN_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met_vptran.h"
#include "vptran_sel.h"
#include "vptran_sel_typ.h"
#include "vardef.h"
#include "bitcnt.h"
#include "lsbsrch.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_VPTRAN_C_MAJOR != XSPI_VPTRAN_H_MAJOR) || \
     (XSPI_VPTRAN_C_MINOR != XSPI_VPTRAN_H_MINOR) || \
     (XSPI_VPTRAN_C_PATCH != XSPI_VPTRAN_H_PATCH))
#error "xspi_cfg.c and xspi_cfg_vptran.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_VPTRAN_SFTRNG_NUM              (11U)
#define XSPI_VPTRAN_SFTRNG_BUF_NUM          (XSPI_VPTRAN_SFTRNG_NUM * 2U)

#define XSPI_VPTRAN_SFT_CURGEAR_MAX         (15U)

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
static  U1      u1_s_XSpiCfgCvtVptranSftRng(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG_STS, const U2 u2_a_RNG, const U1 u1_a_GEAR);
static  U1      u1_s_XSpiCfgCvtVptranSftOut(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG, const U1 u1_a_GEAR);
static  U1      u1_s_XSpiCfgCvtVptranShiftPos(const U2 u2_a_RNG, const U1 u1_a_XSPI_RNG);
static  U1      u1_s_XSpiCfgVptranHideDispJdg(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiCfgCvtVptranGear(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_XSpiCfgCvtVptranGear(void)
{
    U2      u2_t_gear;
    U1      u1_t_ger_sts;
    U1      u1_t_hide_disp_jdg;

    u2_t_gear          = (U2)0U;
    u1_t_ger_sts       = (U1)VPTRAN_UNKNOWN;

    u1_t_ger_sts       = u1_g_VptranGearSelected(&u2_t_gear);
    u1_t_hide_disp_jdg = u1_s_XSpiCfgVptranHideDispJdg();

    /* Turn-Off the Gear if a shift range is not shown OR shift range is P, R or N. */
    if (u1_t_hide_disp_jdg == (U1)TRUE){
        u2_t_gear = (U2)0U;
    }

    if (((u1_t_ger_sts & (U1)(VPTRAN_INVALID | VPTRAN_UNKNOWN)) != (U1)0U) ||
        (u2_t_gear > (U2)XSPI_VPTRAN_SFT_CURGEAR_MAX)) {
        u2_t_gear = (U2)0U;
    }

    return((U1)u2_t_gear);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiCfgCvtVptranShift(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void  vd_g_XSpiCfgCvtVptranShift(U1* u1p_a_blnk, U1* u1p_a_pos)
{
    U2      u2_t_rng;
    U2      u2_t_gear;
    U1      u1_t_sft_sbw;
    U1      u1_t_rng_sts;
    U1      u1_t_ger_sts;
    U1      u1_t_xspi_rng;

    u2_t_rng  = (U2)0U;
    u2_t_gear = (U2)0U;
    u1_t_rng_sts = u1_g_VptranRangeSelected(&u2_t_rng);
    u1_t_ger_sts = u1_g_VptranGearSelected(&u2_t_gear);
    u1_t_sft_sbw = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_SBW);

    if ((u1_t_ger_sts & (U1)(VPTRAN_INVALID | VPTRAN_UNKNOWN)) != (U1)0U) {
        u2_t_gear = (U2)0U;
    }

    u1_t_xspi_rng = u1_s_XSpiCfgCvtVptranSftRng(u1_t_sft_sbw, u1_t_rng_sts, u2_t_rng, (U1)u2_t_gear);

    if ((u1p_a_blnk != vdp_PTR_NA) && (u1p_a_pos != vdp_PTR_NA)) {
        if (u1_t_xspi_rng != (U1)XSPI_VPTRAN_SFT_OFF) {
            (*u1p_a_pos)  = u1_t_xspi_rng;
            (*u1p_a_blnk) = u1_s_XSpiCfgCvtVptranShiftPos(u2_t_rng, u1_t_xspi_rng);
        }
        else {
            (*u1p_a_pos)  = (U1)XSPI_VPTRAN_SFT_OFF;
            (*u1p_a_blnk) = (U1)XSPI_VPTRAN_SFT_POS_OFF;
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiCfgCvtVptranGsi(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiCfgCvtVptranGsi(void)
{
    static const U2     u2_s_GSI_MSK = (U2)0x0003U;
    U2                  u2_t_gsi;
    U1                  u1_t_sts;
    U1                  u1_t_hide_disp_jdg;

    u2_t_gsi          = (U2)0x0000U;
    u1_t_sts          = u1_g_VptranGearShiftIndicator(&u2_t_gsi);
    u1_t_hide_disp_jdg = u1_s_XSpiCfgVptranHideDispJdg();

    /* Turn-Off the GSI if a shift range is not shown OR shift range is P, R or N. */
    if (u1_t_hide_disp_jdg == (U1)TRUE){
        u2_t_gsi = (U2)0x0000U;
    }
    if ((u1_t_sts & (U1)(VPTRAN_INVALID | VPTRAN_UNKNOWN)) != (U1)0U) {
        u2_t_gsi = (U2)0x0000U;
    }

    u2_t_gsi &= u2_s_GSI_MSK;

    return((U1)u2_t_gsi);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_XSpiCfgGetSftRng(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG_STS, const U1 u1_a_RNG, const U1 u1_a_GEAR)        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_SFT_TYP        : Shift Type (Use return value of u1_g_VptranShiftTypeCfg)                                   */
/*                  u1_a_RNG_STS        : Status bits of Range info (Use return value of u1_g_VptranRangeSelected)                   */
/*                  u1_a_RNG            : Selected Range (u1_g_VptranRangeSelected)                                                  */
/*                  u1_a_GEAR           : Selected Gear (u1_g_VptranGearSelected)                                                    */
/*  Return:         A range value to store the Xspi buffer                                                                           */
/*===================================================================================================================================*/
static  U1      u1_s_XSpiCfgCvtVptranSftRng(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG_STS, const U2 u2_a_RNG, const U1 u1_a_GEAR)
{
    static const    U1      u1_s_VALID_SEL_RNG = (U1)1U;
    U2                      u2_t_rng;
    U1                      u1_t_rng_bitcnt;
    U1                      u1_t_rng_num;
    U1                      u1_t_rng_out;

    u2_t_rng = u2_a_RNG & (U2)VPTRAN_RNG_MSK;

    u1_t_rng_bitcnt = u1_g_BitCnt((U4)u2_t_rng);
    u1_t_rng_num = u1_g_LsbSrch((U4)u2_t_rng);
    if ((u1_t_rng_bitcnt == u1_s_VALID_SEL_RNG) && (u1_t_rng_num < (U1)XSPI_VPTRAN_SFTRNG_NUM) && (u1_a_RNG_STS == (U1)0U)) {
        u1_t_rng_out = u1_s_XSpiCfgCvtVptranSftOut(u1_a_SFT_SBW, u1_t_rng_num, u1_a_GEAR);
    } else {
        u1_t_rng_out = (U1)XSPI_VPTRAN_SFT_OFF;
    }
    return (u1_t_rng_out);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_XSpiCfgCvtVptranSftOut(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG, const U1 u1_a_GEAR)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_XSpiCfgCvtVptranSftOut(const U1 u1_a_SFT_SBW, const U1 u1_a_RNG, const U1 u1_a_GEAR)
{
    static const    U1  u1_sp_SFTRNG_SBW_TBL[XSPI_VPTRAN_SFTRNG_BUF_NUM] = {
        /* GEAR Inactive */                  /* GEAR Active */
        (U1)XSPI_VPTRAN_SFT_P   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_P_ON  */
        (U1)XSPI_VPTRAN_SFT_R   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_R_ON  */
        (U1)XSPI_VPTRAN_SFT_N   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_N_ON  */
        (U1)XSPI_VPTRAN_SFT_D   ,        (U1)XSPI_VPTRAN_SFT_DM  ,      /* VPTRAN_RNG_D_ON  */
        (U1)XSPI_VPTRAN_SFT_B   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_B_ON  */
        (U1)XSPI_VPTRAN_SFT_S   ,        (U1)XSPI_VPTRAN_SFT_SM  ,      /* VPTRAN_RNG_S_ON  */
        (U1)XSPI_VPTRAN_SFT_DM  ,        (U1)XSPI_VPTRAN_SFT_DM  ,      /* VPTRAN_RNG_DM_ON */
        (U1)XSPI_VPTRAN_SFT_SM  ,        (U1)XSPI_VPTRAN_SFT_SM  ,      /* VPTRAN_RNG_SM_ON */
        (U1)XSPI_VPTRAN_SFT_MM  ,        (U1)XSPI_VPTRAN_SFT_MM  ,      /* VPTRAN_RNG_MM_ON */
        (U1)XSPI_VPTRAN_SFT_M   ,        (U1)XSPI_VPTRAN_SFT_MM  ,      /* VPTRAN_RNG_M_ON  */
        (U1)XSPI_VPTRAN_SFT_SD  ,        (U1)XSPI_VPTRAN_SFT_OFF        /* VPTRAN_RNG_SD_ON */
    };
    static const    U1  u1_sp_SFTRNG_CVT_TBL[XSPI_VPTRAN_SFTRNG_BUF_NUM] = {
        /* GEAR Inactive */                  /* GEAR Active */
        (U1)XSPI_VPTRAN_SFT_P   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_P_ON  */
        (U1)XSPI_VPTRAN_SFT_R   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_R_ON  */
        (U1)XSPI_VPTRAN_SFT_N   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_N_ON  */
        (U1)XSPI_VPTRAN_SFT_D   ,        (U1)XSPI_VPTRAN_SFT_DM  ,      /* VPTRAN_RNG_D_ON  */
        (U1)XSPI_VPTRAN_SFT_B   ,        (U1)XSPI_VPTRAN_SFT_OFF ,      /* VPTRAN_RNG_B_ON  */
        (U1)XSPI_VPTRAN_SFT_S   ,        (U1)XSPI_VPTRAN_SFT_SM  ,      /* VPTRAN_RNG_S_ON  */
        (U1)XSPI_VPTRAN_SFT_DM  ,        (U1)XSPI_VPTRAN_SFT_DM  ,      /* VPTRAN_RNG_DM_ON */
        (U1)XSPI_VPTRAN_SFT_SM  ,        (U1)XSPI_VPTRAN_SFT_SM  ,      /* VPTRAN_RNG_SM_ON */
        (U1)XSPI_VPTRAN_SFT_MM  ,        (U1)XSPI_VPTRAN_SFT_MM  ,      /* VPTRAN_RNG_MM_ON */
        (U1)XSPI_VPTRAN_SFT_M   ,        (U1)XSPI_VPTRAN_SFT_MM  ,      /* VPTRAN_RNG_M_ON  */
        (U1)XSPI_VPTRAN_SFT_SD  ,        (U1)XSPI_VPTRAN_SFT_OFF        /* VPTRAN_RNG_SD_ON */
    };

    static const    U1  u1_s_RNG_SFT        = (U1)1U;
    static const    U1  u1_s_GEAR_OFST      = (U1)1U;
    
    U1                  u1_t_pos;
    U1                  u1_t_rng_out;

    u1_t_pos = (U1)(u1_a_RNG << u1_s_RNG_SFT);
    if (u1_a_GEAR > (U1)0U) {
        u1_t_pos += u1_s_GEAR_OFST;
    }

    u1_t_rng_out = (U1)XSPI_VPTRAN_SFT_OFF;
    if (u1_a_SFT_SBW == (U1)TRUE) {
            u1_t_rng_out = u1_sp_SFTRNG_SBW_TBL[u1_t_pos];
    } else {
            u1_t_rng_out = u1_sp_SFTRNG_CVT_TBL[u1_t_pos];
    }

    return (u1_t_rng_out);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_XSpiCfgCvtVptranShiftPos(const U2 u2_a_RNG)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_XSpiCfgCvtVptranShiftPos(const U2 u2_a_RNG, const U1 u1_a_XSPI_RNG)
{
    U1      u1_t_pos;

    if ((u1_a_XSPI_RNG == (U1)XSPI_VPTRAN_SFT_N) &&
        ((u2_a_RNG & (U2)VPTRAN_STS_DBL_PARK) != (U2)0U)) {
        u1_t_pos = (U1)XSPI_VPTRAN_SFT_POS_BLNK_1;
    }
    else if ((u2_a_RNG & (U2)VPTRAN_STS_OILWRN) != (U2)0U) {
        u1_t_pos = (U1)XSPI_VPTRAN_SFT_POS_BLNK_1;
    }
    else if ((u2_a_RNG & (U2)VPTRAN_STS_CLATCHENGAGE) != (U2)0U) {
        u1_t_pos = (U1)XSPI_VPTRAN_SFT_POS_BLNK_2;
    }
    else if ((u2_a_RNG & (U2)VPTRAN_STS_SPTMDENABLE) != (U2)0U) {
        u1_t_pos = (U1)XSPI_VPTRAN_SFT_POS_BLNK_3;
    }
    else {
        u1_t_pos = (U1)XSPI_VPTRAN_SFT_POS_ON;
    }
    return (u1_t_pos);
}

/*===================================================================================================================================*/
/* static  U1      u1_s_XSpiCfgVptranHideDispJdg(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_XSpiCfgVptranHideDispJdg(void)
{
    static const U2     u2_s_GERHIDE_RNG = (U2)(VPTRAN_RNG_P_ON | VPTRAN_RNG_R_ON | VPTRAN_RNG_N_ON | VPTRAN_RNG_B_ON | VPTRAN_RNG_SD_ON);
    U2                  u2_t_rng;
    U1                  u1_t_xspi_blnk;
    U1                  u1_t_xspi_rng;
    U2                  u2_t_gear;
    U1                  u1_t_ret;

    u2_t_rng       = (U2)0U;
    u1_t_xspi_blnk = (U1)XSPI_VPTRAN_SFT_POS_OFF;
    u1_t_xspi_rng  = (U1)XSPI_VPTRAN_SFT_OFF;
    u2_t_gear      = (U2)0U;
    u1_t_ret = (U1)FALSE;

    (void)u1_g_VptranRangeSelected(&u2_t_rng);
    vd_g_XSpiCfgCvtVptranShift(&u1_t_xspi_blnk, &u1_t_xspi_rng);
    (void)u1_g_VptranGearSelected(&u2_t_gear);

    if ((u1_t_xspi_rng == (U1)XSPI_VPTRAN_SFT_OFF) ||
        ((u2_t_rng & u2_s_GERHIDE_RNG) != (U2)0U)) {
        if (u2_t_gear != (U2)0U) {
            u1_t_ret = (U1)TRUE;
        }
        else {
            u1_t_ret = (U1)FALSE;
        }
    }

    return (u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/07/2020  KM       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/09/2020  KK       Configured for 800B                                                                                */
/*  1.1.0     8/10/2020  KK       Priority Change (B_x_SBW / B_GEAR_S)                                                               */
/*  1.1.1     3/10/2021  KK       Fix a bug (Disable GSI when SFTAREA = 0b)                                                          */
/*  1.2.0     6/17/2021  TN       Add Normal Shift (MET-D_ATSPT-CSTD-)                                                               */
/*  1.3.0     7/02/2021  TN       Add Deceleration level and Recommended gear (MET-H_DCLDSP-CSTD-0,MET-D_GSI-CSTD-1)                 */
/*  1.4.0     9/20/2021  TN       Add Notification Processing Of Shift Blinking State                                                */
/*  1.5.0     1/16/2024  GM       19PFv3 Update                                                                                      */
/*  1.6.0     4/12/2024  GM       Fix a bug (Send Shift Pos Blink Pattern 1 when N Range and Double parking mode)                    */
/*                                                                                                                                   */
/*  * KM   = Keisuke Mashita, Denso Techno                                                                                           */
/*  * KK   = Kohei Kato,      Denso Techno                                                                                           */
/*  * TN   = Tetsu Naruse,    Denso Techno                                                                                           */
/*  * GM   = Glen Monteposo,  DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
