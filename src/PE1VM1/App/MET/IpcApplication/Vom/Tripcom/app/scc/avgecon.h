/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Average XXXX Economy application core                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef AVGECON_H
#define AVGECON_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_H_MAJOR                         (2)
#define AVGECON_H_MINOR                         (1)
#define AVGECON_H_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AVGECON_NUM_ENGYTYPE                    (3U)
#define AVGECON_ENGYTYPE_FUEL                   (0U)
#define AVGECON_ENGYTYPE_HYDR                   (1U)
#define AVGECON_ENGYTYPE_ELPW                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2                                          u2_calctm;
    U1                                          u1_calcstsbit;
    U1                                          u1_initupdt;
    U1                                          u1_rstterm;
    U1                                          u1_rstimmw;
} ST_AVGECON_VAR;

typedef struct {
    U2                                          u2_autoreset;           /* see tripcom.h                                             */
    U2                                          u2_manualreset;         /* see tripcom.h                                             */
    U2                                          u2_pause;               /* see tripcom.h                                             */
    U2                                          u2_calc_intrvl;         /* Caution : 0 is special value for this configuration       */
                                                                        /* when u2_calcintvl = 0, periodic updt will not be          */
                                                                        /* called.                                                   */
    U1                                          u1_ms_economy_id;       /* see tripcom_ms.h                                          */
    U1                                          u1_ms_used_id;          /* see tripcom_ms.h                                          */
    U1                                          u1_ms_odocnt_id;        /* see tripcom_ms.h                                          */
    U1                                          u1_init_after_updt;     /* Init accumulated value after update                       */

    U1                                          u1_cantx_aprx;          /* Use approximate val to avoid 0 div only when L(Kg)/100Km  */
                                                                        /* If set FALSE, tx-value becomes 0                          */
    U2                                          u2_cantx_max;           /* Range max property for cantx value                        */
    U2                                          u2_cantx_fail;          /* Communiation failed                                       */
    U2                                          u2_cantx_unknown;       /* Unit is not defined                                       */
    U2                                          u2_cantx_rstinit;       /* Initial value for after reset                             */
    U2                                          u2_cantx_resconv;       /* Multiplier to convert resolution                          */
} ST_AVGECON_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void            vd_g_AvgEconInit(U1 * u1p_a_sts, ST_AVGECON_VAR * st_ap_var, const U4 u4_a_NUM_CNTTS);
U1              u1_g_AvgEconCalcTrnst(const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD);
void            vd_g_AvgEconAccmlt(const ST_AVGECON_CNTT * stp_a_CNTT,
                                    const U1 u1_a_ISINIT, const U2 u2_a_STSJDG, const U4 u4_a_USD, const U4 u4_a_ODO);
void            vd_g_AvgEconUpdt(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_TYPE);
void            vd_g_AvgEconRstImmw(const U1 u1_a_ACTV, const ST_AVGECON_CNTT * stp_a_CNTT, ST_AVGECON_VAR * stp_a_var, const U2 * u2_ap_STSFIELD);
U2              u2_g_AvgEconCalcTx(const ST_AVGECON_CNTT * stp_a_CNTT, const U1 u1_a_RSTTRM, const U1 u1_a_UNIT, const U1 u1_a_TYPE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* AVGECON_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  avgecon.c                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
