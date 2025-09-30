/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  EV Distance To Empty for Trip Computer                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVDTE_KM_C_MAJOR                      (2)
#define EVDTE_KM_C_MINOR                      (3)
#define EVDTE_KM_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "evdte_km_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVDTE_KM_C_MAJOR != EVDTE_KM_H_MAJOR) || \
     (EVDTE_KM_C_MINOR != EVDTE_KM_H_MINOR) || \
     (EVDTE_KM_C_PATCH != EVDTE_KM_H_PATCH))
#error "evdte_km.c and evdte_km.h : source and header files are inconsistent!"
#endif

#if ((EVDTE_KM_C_MAJOR != EVDTE_KM_CFG_H_MAJOR) || \
     (EVDTE_KM_C_MINOR != EVDTE_KM_CFG_H_MINOR) || \
     (EVDTE_KM_C_PATCH != EVDTE_KM_CFG_H_PATCH))
#error "evdte_km.c and evdte_km_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVDTE_ACOFF          (0U)
#define EVDTE_ACON           (1U)

#define EVDTE_CANTX_MAX      (0xFFFCU)
#define EVDTE_CANTX_RESCNV   (1000U)
#define EVDTE_CANTX_RNDUP    (EVDTE_CANTX_RESCNV - 1U)


#define EVDTE_VAL100         (100U)
#define EVDTE_IGON_FAIL_TIM  (10000U / TRIPCOM_TICK)

#define EVDTE_RXLSB          (100U)

/* refer to tripcom.h */
/* Bit[0-1] : Common Bit Definition             */
/* #define TRIPCOM_STSBIT_VALID                    (0x00U)            *//*  Valid                                                    */
/* #define TRIPCOM_STSBIT_UNKNOWN                  (0x01U)            *//*  Unknown                                                  */
/* #define TRIPCOM_STSBIT_INVALID                  (0x02U)            *//*  Invalid                                                  */
#define TRIPCOM_STSBIT_EVDTE_PIEVDXX_UNK           (TRIPCOM_STSBIT_UNKNOWN)
#define TRIPCOM_STSBIT_EVDTE_PIEVDXX_INV           (TRIPCOM_STSBIT_INVALID)

/* Bit[2-7] : Extra Bit Definition              */
/* 07 EV Distance To Empty                      */
/* #define TRIPCOM_STSBIT_EVDTE_RCVZERO            (0x04U)            *//*  Receive Pievd06 = 0                                      */
#define TRIPCOM_STSBIT_EVDTE_CNGPIEVD_UNK          (TRIPCOM_STSBIT_UNKNOWN << 4)
#define TRIPCOM_STSBIT_EVDTE_CNGPIEVD_INV          (TRIPCOM_STSBIT_INVALID << 4)
#define TRIPCOM_STSBIT_EVDTE_IGON                  (0x80U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1  u1_s_evdte_chginfo;
static U1  u1_s_evdte_appsts;
static U2  u2_s_evdte_rngdiff;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_EvDteUpdtCNGPIEVD(const U1 u1_a_CNGPIEVD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_EvDteInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvDteInit(void)
{
    u1_s_evdte_chginfo = (U1)EVDTE_ACOFF;
    u1_s_evdte_appsts  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    u2_s_evdte_rngdiff = (U2)0U;
}

/*===================================================================================================================================*/
/* void            vd_g_EvDteApplTask(const U2 * u2_ap_STSFIELD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvDteApplTask(const U2 * u2_ap_STSFIELD)
{
    U1    u1_t_sts;
    U1    u1_t_cngpievd;

    u1_s_evdte_appsts = (U1)0U;

    u1_t_sts          = u1_g_TripsnsrCfgEvDteSts();
    if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_INVALID) != (U1)0U) {
        u1_s_evdte_appsts  = (U1)TRIPCOM_STSBIT_EVDTE_PIEVDXX_INV;
    }
    if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_UNKNOWN) != (U1)0U) {
        u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_PIEVDXX_UNK;
    }

    if ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_IGON) != (U2)0U) {
        u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_IGON;

        u1_t_cngpievd = (U1)0U;
        u1_t_sts      = u1_g_TripsnsrCfgEvDteCNGPIEVD(&u1_t_cngpievd);
        if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_INVALID) != (U1)0U) {
            u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_CNGPIEVD_INV;
        }
        if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_UNKNOWN) != (U1)0U) {
            u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_CNGPIEVD_UNK;
        }
    }
    else {
        u1_t_cngpievd      = (U1)0U;
        u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_CNGPIEVD_UNK;
    }
    vd_s_EvDteUpdtCNGPIEVD(u1_t_cngpievd);
}

/*===================================================================================================================================*/
/* U1              u1_g_EvDteCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_EvDteCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    return ((U1)TRUE); 
}

/*===================================================================================================================================*/
/* void            vd_g_EvDteUpdt(const U1 u1_a_CNTTID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void          vd_g_EvDteUpdt(const U1 u1_a_CNTTID)
{
    U4 u4_t_evrngkm;
    U4 u4_t_mul;
    U4 u4_t_div;
    U2 u2_t_pievd06;
    U1 u1_t_pievdsr;
    U1 u1_t_pieve06;

    if ((u1_s_evdte_appsts & (U1)(TRIPCOM_STSBIT_EVDTE_PIEVDXX_INV | TRIPCOM_STSBIT_EVDTE_PIEVDXX_UNK)) == (U1)0U) {
        vd_g_TripsnsrCfgEvDteDist(&u2_t_pievd06);
        vd_g_TripsnsrCfgEvDteSubRate(&u1_t_pievdsr);
        vd_g_TripsnsrCfgEvDtePIEVE06(&u1_t_pieve06);

        if (u1_t_pieve06 >= (U1)EVDTE_VAL100) {
            u1_t_pieve06 = (U1)EVDTE_VAL100;
        }

        if (u1_t_pievdsr >= (U1)EVDTE_VAL100) {
            u1_t_pievdsr = (U1)EVDTE_VAL100;
        }

        if(u2_t_pievd06 == (U2)0U){
            u1_s_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_RCVZERO;
            u4_t_evrngkm       = (U4)0U;
            u2_s_evdte_rngdiff   = (U2)0U;
        }
        else{
            if (u1_s_evdte_chginfo == (U1)EVDTE_ACON) {
                u4_t_div = (U4)EVDTE_VAL100 - (U4)u1_t_pievdsr;
                /* The maximum value of u1_t_pievdsr is 100, so it is not less than 0.                                               */
                u4_t_mul = (U4)u2_t_pievd06 * u4_t_div;
                /* The maximum value of u2_t_pievd06 is 65535. The maximum value of u4_t_div is 100.                                 */
                /* so ((U4)u2_t_pievd06 * u4_t_div) is always less than U4_MAX.                                                      */
                u4_t_mul = u4_t_mul * (U4)EVDTE_RXLSB;
                /* The maximum value of u4_t_mul is 65535 * 100. The value of EVDTE_RXLSB is 100.                                    */
                /* so (u4_t_mul * (U4)EVDTE_RXLSB) is always less than U4_MAX.                                                       */
                u4_t_evrngkm = u4_t_mul / (U4)EVDTE_VAL100;
            }
            else {
                u4_t_evrngkm = (U4)u2_t_pievd06 * (U4)EVDTE_RXLSB;
                /* The maximum value of u2_t_pievd06 is 65535. The value of EVDTE_RXLSB is 100.                                      */
                /* so ((U4)u2_t_pievd06 * (U4)EVDTE_RXLSB) is always less than U4_MAX.                                               */
            }
            u4_t_mul = (U4)u2_t_pievd06 * (U4)u1_t_pievdsr;
            /* The maximum value of u2_t_pievd06 is 65535. The maximum value of u1_t_pievdsr is 100.                             */
            /* so ((U4)u2_t_pievd06 * (U4)u1_t_pievdsr) is always less than U4_MAX.                                              */
            u4_t_div = u4_t_mul / (U4)EVDTE_VAL100;
            u2_s_evdte_rngdiff = (U2)u4_t_div;
            /* The maximum value of u4_t_div is 65535.                                                                           */
            /* so u4_t_div is always less than U2_MAX.                                                                           */
        }
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVDTE_OC, u4_t_evrngkm);
        vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_EVDTE_PCT, (U4)u1_t_pieve06);
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_EvDteKm(U4 * u4p_a_km, U1 * u1p_a_acsts)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_EvDteKm(U4 * u4p_a_km, U1 * u1p_a_acsts)
{
    U1  u1_t_sts;

    if ((u4p_a_km    != vdp_PTR_NA) &&
        (u1p_a_acsts != vdp_PTR_NA)) {
        (*u4p_a_km)    = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVDTE_OC);
        (*u1p_a_acsts) = u1_s_evdte_chginfo;
    }
    
    u1_t_sts  = u1_s_evdte_appsts & (U1)(TRIPCOM_STSBIT_UNKNOWN | TRIPCOM_STSBIT_INVALID | TRIPCOM_STSBIT_EVDTE_RCVZERO);
    
    return (u1_t_sts);
}

/*===================================================================================================================================*/
/* U1              u1_g_EvDtePct(U1 * u1p_a_pct)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1            u1_g_EvDtePct(U1 * u1p_a_pct)
{
    U1  u1_t_sts;

    if (u1p_a_pct != vdp_PTR_NA) {
        (*u1p_a_pct) = (U1)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVDTE_PCT);
    }
    
    u1_t_sts = u1_s_evdte_appsts & (U1)(TRIPCOM_STSBIT_UNKNOWN | TRIPCOM_STSBIT_INVALID);
    
    return (u1_t_sts);
}

/*===================================================================================================================================*/
/* U2              u2_g_EvDteCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2           u2_g_EvDteCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    U4          u4_t_dist;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if ((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
        u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
    }
    else if ((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_UNKNOWN      ) != (U1)0U){
        /* u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN; */
    }
    else if ((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_EVDTE_RCVZERO) != (U1)0U){
        u2_t_txval = (U2)0U;
    }
    else {
        u4_t_dist   = u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_EVDTE_OC);
        u1_t_cnvsts = u1_g_TripcomCalcTxCnvtEvDte(&u4_t_dist, u1_a_UNIT);
        if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
            u4_t_dist   = u4_g_TripcomCalcAddU4U4(u4_t_dist, (U4)EVDTE_CANTX_RNDUP);
            u4_t_dist  /= (U4)EVDTE_CANTX_RESCNV;
            u2_t_txval  = (U2)EVDTE_CANTX_MAX;
            if (u4_t_dist  < (U4)u2_t_txval) {
                u2_t_txval = (U2)u4_t_dist;
            }
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/* static void     vd_s_EvDteUpdtCNGPIEVD(const U1 u1_a_CNGPIEVD)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_EvDteUpdtCNGPIEVD(const U1 u1_a_CNGPIEVD)
{
    if((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_EVDTE_IGON) == (U1)0U){
        u1_s_evdte_chginfo = (U1)EVDTE_ACOFF;
    }
    else{
        if((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_EVDTE_CNGPIEVD_INV) != (U1)0U){
            /* u1_s_evdte_chginfo is not updated */
        }
        else if((u1_s_evdte_appsts & (U1)TRIPCOM_STSBIT_EVDTE_CNGPIEVD_UNK) != (U1)0U){
            u1_s_evdte_chginfo = (U1)EVDTE_ACOFF;
        }
        else{
            u1_s_evdte_chginfo = u1_a_CNGPIEVD;
        }
    }
}

/*===================================================================================================================================*/
/* U2              u2_g_EvDteKmDiff(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2            u2_g_EvDteKmDiff(void)
{
    return (u2_s_evdte_rngdiff);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    03/19/2020  YA       New.                                                                                               */
/*  1.0.1    07/13/2020  YA       Operation sequence modification                                                                    */
/*                                Change evrng to hold for +B-ON                                                                     */
/*  1.0.2    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  1.1.0    05/17/2021  YS       implement round-up for EVDTE unit conversion (MET-M_DMEVRNGE-CSTD-1-02-A-C0)                       */
/*  2.0.0    06/09/2021  TA       Change u1_g_EvDteKm                                                                                */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.1.0    06/20/2022  TA(M)    Change to update the EvDte value even when IG-ON and Ready OFF                                     */
/*  2.2.0    08/08/2022  YI       Add u1_g_EvDtePct.                                                                                 */
/*  2.3.0    12/12/2023  HF       Add u2_g_EvDteKmDiff.                                                                              */
/*                                                                                                                                   */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * YS   = Yosuke Sugimoto, DensoTechno                                                                                            */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
