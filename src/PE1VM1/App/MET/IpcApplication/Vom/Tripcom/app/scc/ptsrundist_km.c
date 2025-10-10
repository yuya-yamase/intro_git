/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Powertrain Run Distance for Trip Computer                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSRUNDIST_KM_C_MAJOR                   (2)
#define PTSRUNDIST_KM_C_MINOR                   (0)
#define PTSRUNDIST_KM_C_PATCH                   (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ptsrundist_km_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSRUNDIST_KM_C_MAJOR != PTSRUNDIST_KM_H_MAJOR) || \
     (PTSRUNDIST_KM_C_MINOR != PTSRUNDIST_KM_H_MINOR) || \
     (PTSRUNDIST_KM_C_PATCH != PTSRUNDIST_KM_H_PATCH))
#error "ptsrundist_km.c and ptsrundist_km.h : source and header files are inconsistent!"
#endif

#if ((PTSRUNDIST_KM_C_MAJOR != PTSRUNDIST_KM_CFG_H_MAJOR) || \
     (PTSRUNDIST_KM_C_MINOR != PTSRUNDIST_KM_CFG_H_MINOR) || \
     (PTSRUNDIST_KM_C_PATCH != PTSRUNDIST_KM_CFG_H_PATCH))
#error "ptsrundist_km.c and ptsrundist_km_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1                                          u1_initupdt;
    U1                                          u1_status;
} ST_PTSRUNDIST_APPVAR;

typedef struct {
    U2                                          u2_manualreset;         /* see tripcom.h                                             */
    U2                                          u2_autoreset;           /* see tripcom.h                                             */
    U1                                          u1_ms_odocnt_id;        /* see tripcom_ms.h                                          */

    U1                                          u1_cantx_resconv;       /* Multiplier to convert resolution                          */
    U2                                          u2_cantx_max;           /* Range max property for cantx value                        */
} ST_PTSRUNDIST_CNTT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  ST_PTSRUNDIST_APPVAR                    st_sp_ptsrundist_var[PTSRUNDIST_NUM_CNTTS];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_PTSRUNDIST_CNTT                 st_sp_PTSRUNDIST_CNTTS_CFG[PTSRUNDIST_NUM_CNTTS] = {
    {
        /*  #define PTSRUNDIST_CNTT_LC                      (0)         */
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_LC,
        (U2)0U,

        (U1)TRIPCOM_MS_ID_PTSRUNDIST_LC_OC,

        (U1)100U,
        (U2)0xFFFDU
    },
    {
        /*  #define PTSRUNDIST_CNTT_DC                      (1)         */
        (U2)0U,
        (U2)TRIPCOM_RSTRQBIT_A_DRVCYC,

        (U1)TRIPCOM_MS_ID_PTSRUNDIST_DC_OC,

        (U1)100U,
        (U2)0xFFFDU
    },
    {
        /*  #define PTSRUNDIST_CNTT_TR_A                    (2U)        */
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_A,
        (U2)0U,

        (U1)TRIPCOM_MS_ID_PTSRUNDIST_TR_A_OC,

        (U1)100U,
        (U2)0xFFFDU
    },
    {
        /*  #define PTSRUNDIST_CNTT_TR_B                    (3U)        */
        (U2)TRIPCOM_RSTRQBIT_M_PTSRUNDIST_TR_B,
        (U2)0U,

        (U1)TRIPCOM_MS_ID_PTSRUNDIST_TR_B_OC,

        (U1)100U,
        (U2)0xFFFDU
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_PtsRunDistInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunDistInit(void)
{
    U4          u4_t_loop;


    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)PTSRUNDIST_NUM_CNTTS ; u4_t_loop++){
        st_sp_ptsrundist_var[u4_t_loop].u1_initupdt = (U1)FALSE;
        st_sp_ptsrundist_var[u4_t_loop].u1_status   = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_PtsRunDistApplTask(const U2 * u2_ap_STSFIELD)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunDistApplTask(const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;
    U4          u4_t_loop;


    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)PTSRUNDIST_NUM_CNTTS ; u4_t_loop++){
        st_sp_ptsrundist_var[u4_t_loop].u1_status = (U1)TRIPCOM_STSBIT_VALID;
        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN;
        if (u2_t_jdgbit != (U2)0U) {
            st_sp_ptsrundist_var[u4_t_loop].u1_status  = (U1)TRIPCOM_STSBIT_UNKNOWN;
        }
        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID;
        if (u2_t_jdgbit != (U2)0U) {
            st_sp_ptsrundist_var[u4_t_loop].u1_status |= (U1)TRIPCOM_STSBIT_INVALID;
        }
    }

}

/*===================================================================================================================================*/
/* U1              u1_g_PtsRunDistCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_PtsRunDistCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    U2          u2_t_jdgbit;


    if (u1_a_CNTTID < (U1)PTSRUNDIST_NUM_CNTTS) {
        st_sp_ptsrundist_var[u1_a_CNTTID].u1_initupdt = (U1)FALSE;
        u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_AUTO_RSTRQ] & st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u2_autoreset;
    	u2_t_jdgbit |= (u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u2_manualreset);
        
        if (u2_t_jdgbit != (U2)0U) {
            st_sp_ptsrundist_var[u1_a_CNTTID].u1_initupdt = (U1)TRUE;
        }
    }

    return ((U1)FALSE);
}

/*===================================================================================================================================*/
/* void            vd_g_PtsRunDistAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_PtsRunDistAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    U4          u4_t_odocnt;
    U1          u1_t_ovf;


    if (u1_a_CNTTID < (U1)PTSRUNDIST_NUM_CNTTS) {
        if (st_sp_ptsrundist_var[u1_a_CNTTID].u1_initupdt == (U1)TRUE) {
            vd_g_TripcomMsSetAccmltVal(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u1_ms_odocnt_id, (U4)0U);
        }
        else if (st_sp_ptsrundist_var[u1_a_CNTTID].u1_status == (U1)TRIPCOM_STSBIT_VALID) {
            u4_t_odocnt = u4_g_TripcomMsGetAccmltVal(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u1_ms_odocnt_id);

            u1_t_ovf = u1_g_TripcomOvrfChk(u4_t_odocnt, u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_KM], (U4)U4_MAX);
            if (u1_t_ovf == (U1)TRUE) {
                u4_t_odocnt = (U4)U4_MAX;
            }
            else {
                u4_t_odocnt += u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_KM];
                /* u1_g_TripcomOvrfChk() verified not to exceed U4_MAX.         */
            }

            vd_g_TripcomMsSetAccmltVal(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u1_ms_odocnt_id, u4_t_odocnt);
        }
        else {
            /* Do Nothing */
        }
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_PtsRunDistKm(U4 * u4p_a_km)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_PtsRunDistKm(const U1 u1_a_PTSRUN_DIST_CH, U4 * u4p_a_km)
{
    U1          u1_t_status;


    u1_t_status = (U1)TRIPCOM_STSBIT_INVALID;
    if (u1_a_PTSRUN_DIST_CH < (U1)PTSRUNDIST_NUM_CNTTS) {
        if (u4p_a_km != vdp_PTR_NA) {
            (*u4p_a_km) = u4_g_TripcomMsGetAccmltVal(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_PTSRUN_DIST_CH].u1_ms_odocnt_id);
        }
        u1_t_status = st_sp_ptsrundist_var[u1_a_PTSRUN_DIST_CH].u1_status;
    }
    return (u1_t_status);
}

/*===================================================================================================================================*/
/* U2              u2_g_PtsRunDistCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_PtsRunDistCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    U4          u4_t_dist;
    U2          u2_t_txval;
    U1          u1_t_cnvsts;


    u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;

    if (u1_a_CNTTID < (U1)PTSRUNDIST_NUM_CNTTS) {
        if ((st_sp_ptsrundist_var[u1_a_CNTTID].u1_status & (U1)TRIPCOM_STSBIT_INVALID) != (U1)0U) {
            u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
        }
        else {
            u4_t_dist   = u4_g_TripcomMsGetAccmltVal(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u1_ms_odocnt_id);
            u1_t_cnvsts = u1_g_TripcomCalcTxCnvtDist(&u4_t_dist, u1_a_UNIT);
            if (u1_t_cnvsts == (U1)TRIPCOM_STSBIT_VALID) {
                u4_t_dist  /= (U4)(st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u1_cantx_resconv);
                u2_t_txval  = st_sp_PTSRUNDIST_CNTTS_CFG[u1_a_CNTTID].u2_cantx_max;
                if (u4_t_dist  < (U4)u2_t_txval) {
                    u2_t_txval = (U2)u4_t_dist;
                }
            }
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    09/24/2019  TA       Add LC                                                                                             */
/*  1.1.1    03/19/2020  YA       Change for 800B CV                                                                                 */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    Supports TripA and TripB.                                                                          */
/*  2.0.3    10/27/2021  TK       QAC supported.                                                                                     */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
