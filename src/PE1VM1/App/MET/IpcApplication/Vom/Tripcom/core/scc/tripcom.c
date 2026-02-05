/* 2.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_C_MAJOR                         (2)
#define TRIPCOM_C_MINOR                         (5)
#define TRIPCOM_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"

#include "tripcom_private.h"
#include "tripcom_ms.h"
#include "tripcom_nvmif.h"
#include "tripcom_nvmif_grph.h"
#include "tripcom_calc.h"
#include "fpcall_vd_fvd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_C_MAJOR != TRIPCOM_H_MAJOR) || \
     (TRIPCOM_C_MINOR != TRIPCOM_H_MINOR) || \
     (TRIPCOM_C_PATCH != TRIPCOM_H_PATCH))
#error "tripcom.c and tripcom.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_C_MAJOR != TRIPCOM_PRIVATE_H_MAJOR) || \
     (TRIPCOM_C_MINOR != TRIPCOM_PRIVATE_H_MINOR) || \
     (TRIPCOM_C_PATCH != TRIPCOM_PRIVATE_H_PATCH))
#error "tripcom.c and tripcom_private.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_C_MAJOR != TRIPCOM_CFG_H_MAJOR) || \
     (TRIPCOM_C_MINOR != TRIPCOM_CFG_H_MINOR) || \
     (TRIPCOM_C_PATCH != TRIPCOM_CFG_H_PATCH))
#error "tripcom.c and tripcom_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_RSTRQ_ACT                       (0x01U)
#define TRIPCOM_RSTRQ_DEACT                     (0x02U)
#define TRIPCOM_RSTRQ_MSK                       (0x03U)

#define TRIPCOM_MANRSTRQ_RSTRQ_NUM              (5U)
#define TRIPCOM_MANRSTRQ_TOFCRST                (0U)
#define TRIPCOM_MANRSTRQ_TOFCRT2                (1U)
#define TRIPCOM_MANRSTRQ_M1FCRST                (2U)
#define TRIPCOM_MANRSTRQ_TOECRST                (3U)
#define TRIPCOM_MANRSTRQ_M1ECRST                (4U)

#define TRIPCOM_AUTRSTRQ_REFUEL_NUM             (3U)
#define TRIPCOM_AUTRSTRQ_REFUEL_FE              (0U)
#define TRIPCOM_AUTRSTRQ_REFUEL_DTE             (1U)
#define TRIPCOM_AUTRSTRQ_FRCREFUEL              (2U)

#define TRIPCOM_RSTRQ_DTE_SFT                   (1U)
#define TRIPCOM_PREVSTS_SFT                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1      ( * const   fp_u1_GETSIGNAL)(U1 * u1p_a_rst);
    U2                  u2_rstrqbit;
} ST_TRIPCOM_MANRSTRQ;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2                                      u2_s_tripcom_prvvehsyssts;
static  U2                                      u2_s_tripcom_dmreset;
static  U2                                      u2_s_tripcom_immw_dmreset;
static  U2                                      u2_s_tripcom_grphreset;
static  U2                                      u2_s_tripcom_grphresetbk;
static  U1                                      u1_sp_tripcom_manrstrq[TRIPCOM_MANRSTRQ_RSTRQ_NUM];
static  U1                                      u1_sp_tripcom_autrstrq[TRIPCOM_AUTRSTRQ_REFUEL_NUM];
static  U1                                      u1_s_tripcom_refuel_actbit;
static  U1                                      u1_s_tripcom_frcrefuel_actbit;
static  U1                                      u1_s_tripcom_immr_frcrefuel_actbit;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_TripcomInit(void);
static  void    vd_s_TripcomCalcTask(const U2 u2_a_VEHSYSSTS, const U2 u2_a_VARBIT);
static  void    vd_s_TripcomCnttsTask(const U2 u2_a_VARBIT, const U4 * u4_ap_DELTA, const U2 * u2_ap_STSFIELD);
static  U2      u2_s_TripcomManRstRqbitChk(void);
static  U2      u2_s_TripcomAutRstRqbitChk(const U2 u2_a_VEHSYSSTS);
static  U2      u2_s_TripcomOtherRqbitChk(void);
static  U2      u2_s_TripcomAutImmwRstRqbitChk(const U2 u2_a_STSFIELD);
static  U2      u2_s_TripcomManImmwRstRqbitChk(void);
static  void    vd_s_TripcomCanTx(const U2 u2_a_VARBIT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripcomBonInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomBonInit(void)
{
    U2          u2_t_varbit;

    vd_g_TripcomMsBonInit();
    vd_g_TripcomMsInit();
    vd_g_TripcomNvmIfInit((U1)TRUE);
    vd_g_TripcomNvmIfGrphInit((U1)TRUE);
    vd_s_TripcomInit();

    u2_t_varbit = u2_g_TripcomCfgGetVariation();
    vd_s_TripcomCanTx(u2_t_varbit);

    /* ----------------------------------------------------------- */
    /* CAUTION                                                     */
    /* ----------------------------------------------------------- */
    /* Call vd_g_TripcomCfgTxBonInit() after vd_s_TripcomCanTx().  */
    /* CAN TX initial value is set at vd_s_TripcomCanTx().         */
    /* ----------------------------------------------------------- */
    vd_g_TripcomCfgTxBonInit();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomWkupInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomWkupInit(void)
{
    U2          u2_t_varbit;

    vd_g_TripcomMsInit();
    vd_g_TripcomNvmIfInit((U1)FALSE);
    vd_g_TripcomNvmIfGrphInit((U1)FALSE);
    vd_s_TripcomInit();

    u2_t_varbit = u2_g_TripcomCfgGetVariation();
    vd_s_TripcomCanTx(u2_t_varbit);

    /* ----------------------------------------------------------- */
    /* CAUTION                                                     */
    /* ----------------------------------------------------------- */
    /* Call vd_g_TripcomCfgTxWkupInit() after vd_s_TripcomCanTx(). */
    /* CAN TX initial value is set at vd_s_TripcomCanTx().         */
    /* ----------------------------------------------------------- */
    vd_g_TripcomCfgTxWkupInit();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMainTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMainTask(void)
{
    U1          u1_t_jdg;
    U2          u2_t_vehmode;
    U2          u2_t_varbit;


    u2_t_vehmode = u2_g_TripsnsrVehstsChk();
    u2_t_varbit  = u2_g_TripcomCfgGetVariation();

    vd_s_TripcomCalcTask(u2_t_vehmode, u2_t_varbit);
    vd_s_TripcomCanTx(u2_t_varbit);

    u1_t_jdg = u1_g_TripcomCfgJdgRefuelEnd();
    if (u1_t_jdg == (U1)TRUE) {
        u1_s_tripcom_refuel_actbit = (U1)0U;
    }
    u1_s_tripcom_frcrefuel_actbit = (U1)0U;
    u2_s_tripcom_prvvehsyssts = u2_t_vehmode;

    vd_g_TripcomMsMainTask();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomSmoothingTask(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomSmoothingTask(void)
{
    vd_g_TripcomCfgSmoothingTask();
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomOvrfChk(const U4 u4_a_AUGEND, const U4 u4_a_ADDEND, const U4 u4_a_MAX)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomOvrfChk(const U4 u4_a_AUGEND, const U4 u4_a_ADDEND, const U4 u4_a_MAX)
{
    U1          u1_t_result;
    U4          u4_t_margin;


    u4_t_margin = u4_g_TripcomCalcSubU4U4(u4_a_MAX, u4_a_AUGEND);
    if (u4_a_ADDEND > u4_t_margin) {
        u1_t_result = (U1)TRUE;
    }
    else {
        u1_t_result = (U1)FALSE;
    }

    return (u1_t_result);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomGetPIEVSTS(U1 * u1p_a_pievsts)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomGetPIEVSTS(U1 * u1p_a_pievsts)
{
    U1          u1_t_sts;

    u1_t_sts = u1_g_TripcomCfgGetPIEVSTS(u1p_a_pievsts);

    return (u1_t_sts);
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomActRefuelEvHk(const U2 u2_a_DELTA, const U1 u1_a_VTM)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomActRefuelEvHk(const U2 u2_a_DELTA, const U1 u1_a_VTM)
{
    u1_s_tripcom_refuel_actbit |= (U1)TRIPCOM_RSTRQ_ACT;
    u1_s_tripcom_refuel_actbit |= (U1)((U4)TRIPCOM_RSTRQ_ACT << TRIPCOM_RSTRQ_DTE_SFT);
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomFrcRefuelEvHk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomFrcRefuelEvHk(void)
{
    u1_s_tripcom_frcrefuel_actbit = (U1)TRIPCOM_RSTRQ_ACT;
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomFrcRefuelEvImmWr(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomFrcRefuelEvImmWr(void)
{
    u1_s_tripcom_frcrefuel_actbit      = (U1)TRIPCOM_RSTRQ_ACT;
    u1_s_tripcom_immr_frcrefuel_actbit = (U1)TRIPCOM_RSTRQ_ACT;
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomRstRq(const U2 u2_a_RSTRQBIT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomRstRq(const U2 u2_a_RSTRQBIT)
{
    u2_s_tripcom_dmreset |= u2_a_RSTRQBIT;
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomRstRqImmWr(const U2 u2_a_RSTRQBIT)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomRstRqImmWr(const U2 u2_a_RSTRQBIT)
{
    u2_s_tripcom_dmreset      |= u2_a_RSTRQBIT;
    u2_s_tripcom_immw_dmreset |= u2_a_RSTRQBIT;
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomGrphRstRq(const U2 u2_a_RSTRQBIT)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomGrphRstRq(const U2 u2_a_RSTRQBIT)
{
    u2_s_tripcom_grphreset |= (u2_a_RSTRQBIT ^ u2_s_tripcom_grphresetbk) & u2_a_RSTRQBIT;
    if((((u2_a_RSTRQBIT            & u2_gp_TRIPCOM_GRPH_RSTBIT[AVGGRPH_CNTT_1MFE]) != (U2)0U)
     && ((u2_s_tripcom_grphresetbk & u2_gp_TRIPCOM_GRPH_RSTBIT[AVGGRPH_CNTT_1MFE]) == (U2)0U))
    || (((u2_a_RSTRQBIT            & u2_gp_TRIPCOM_GRPH_RSTBIT[AVGGRPH_CNTT_1MEE]) != (U2)0U)
     && ((u2_s_tripcom_grphresetbk & u2_gp_TRIPCOM_GRPH_RSTBIT[AVGGRPH_CNTT_1MEE]) == (U2)0U))){
        vd_g_TripcomMsClrRimRslt();
    }
    u2_s_tripcom_grphresetbk = u2_a_RSTRQBIT;
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomInit(void)
{
    U1                  u1_t_rst_cnt;

    u2_s_tripcom_prvvehsyssts           = (U2)0U;
    u1_s_tripcom_refuel_actbit          = (U1)0U;
    u1_s_tripcom_frcrefuel_actbit       = (U1)0U;
    u1_s_tripcom_immr_frcrefuel_actbit  = (U1)0U;
    u2_s_tripcom_dmreset                = (U2)0U;
    u2_s_tripcom_immw_dmreset           = (U2)0U;
    u2_s_tripcom_grphreset              = (U2)0U;
    u2_s_tripcom_grphresetbk            = (U2)0U;

    for (u1_t_rst_cnt = (U1)0U; u1_t_rst_cnt < (U1)TRIPCOM_MANRSTRQ_RSTRQ_NUM; u1_t_rst_cnt++) {
        u1_sp_tripcom_manrstrq[u1_t_rst_cnt] = (U1)0U;
    }

    for (u1_t_rst_cnt = (U1)0U; u1_t_rst_cnt < (U1)TRIPCOM_AUTRSTRQ_REFUEL_NUM; u1_t_rst_cnt++) {
        u1_sp_tripcom_autrstrq[u1_t_rst_cnt] = (U1)0U;
    }

    vd_g_TripcomCfgApplInit();

}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCalcTask(const U2 u2_a_VEHSYSSTS, const U2 u2_a_VARBIT)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCalcTask(const U2 u2_a_VEHSYSSTS, const U2 u2_a_VARBIT)
{
    U4                                          u4_t_loop;
    U4                                          u4_tp_delta[TRIPCOM_NUM_DELTA];
    U2                                          u2_tp_stsfield[TRIPCOM_NUM_STSFIELD];

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_DELTA; u4_t_loop++) {
        u4_tp_delta[u4_t_loop] = (U4)0U;
    }
    u2_tp_stsfield[TRIPCOM_STSFIELD_VSTS]         = u2_a_VEHSYSSTS;
    u2_tp_stsfield[TRIPCOM_STSFIELD_SNSR]         = u2_g_TripsnsrDeltaChk(&u4_tp_delta[0]);
    u2_tp_stsfield[TRIPCOM_STSFIELD_AUTO_RSTRQ]   = u2_s_TripcomAutRstRqbitChk(u2_a_VEHSYSSTS);
    u2_tp_stsfield[TRIPCOM_STSFIELD_MANUAL_RSTRQ] = u2_s_TripcomManRstRqbitChk();
    u2_tp_stsfield[TRIPCOM_STSFIELD_OTHRQ]        = u2_s_TripcomOtherRqbitChk();
    u2_tp_stsfield[TRIPCOM_STSFIELD_AURST_IMMW]   = u2_s_TripcomAutImmwRstRqbitChk(u2_tp_stsfield[TRIPCOM_STSFIELD_AUTO_RSTRQ]);
    u2_tp_stsfield[TRIPCOM_STSFIELD_MARST_IMMW]   = u2_s_TripcomManImmwRstRqbitChk();

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_g_TRIPCOM_NUM_CALC_APPL_TASK ; u4_t_loop++){
        fp_gp_TRIPCOM_CALC_APPL_TASK[u4_t_loop](&u2_tp_stsfield[0]);
    }

    vd_s_TripcomCnttsTask(u2_a_VARBIT, &u4_tp_delta[0], &u2_tp_stsfield[0]);
    vd_s_TripomCfgPostAppTask();

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_NUM_CNTT; u4_t_loop++) {
        if((u2_s_tripcom_grphreset & u2_gp_TRIPCOM_GRPH_RSTBIT[u4_t_loop]) != (U2)0U){
            vd_g_AvgGrphReset((U1)u4_t_loop);
        }
    }
    u2_s_tripcom_grphreset = (U2)0U;
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCnttsTask(const U2 u2_a_VARBIT, const U4 * u4_ap_DELTA, const U2 * u2_ap_STSFIELD)                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCnttsTask(const U2 u2_a_VARBIT, const U4 * u4_ap_DELTA, const U2 * u2_ap_STSFIELD)
{
    const   ST_TRIPCOM_CNTT *                   stp_t_APPL;
    const   ST_TRIPCOM_IF *                     stp_t_APPLIF;

    U4                                          u4_t_loop;
    U1                                          u1_t_applid;
    U1                                          u1_t_cnttid;
    U1                                          u1_t_update;
    U1                                          u1_t_actv;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_CNTTS; u4_t_loop++) {
        stp_t_APPL  = &st_gp_TRIPCOM_CNTTS_CFG[u4_t_loop];
        u1_t_applid = stp_t_APPL->u1_applid;
        u1_t_cnttid = stp_t_APPL->u1_cnttid;

        if (u1_t_applid < (U1)TRIPCOM_NUM_APPL) {
            stp_t_APPLIF = &st_gp_TRIPCOM_IF_CFG[u1_t_applid];
            u1_t_actv    = (U1)FALSE;

            if ((stp_t_APPL->u2_varbit & u2_a_VARBIT) != (U2)0U) {
                if (stp_t_APPLIF->fp_vd_CONDCHK   != vdp_PTR_NA) {
                    (stp_t_APPLIF->fp_vd_CONDCHK)(u1_t_cnttid, &u2_ap_STSFIELD[0]);
                }
                u1_t_update = (U1)FALSE;
                if (stp_t_APPLIF->fp_u1_CALCTRNST != vdp_PTR_NA) {
                    u1_t_update = (stp_t_APPLIF->fp_u1_CALCTRNST)(u1_t_cnttid, &u2_ap_STSFIELD[0]);
                }
                if (stp_t_APPLIF->fp_vd_ACCMLT    != vdp_PTR_NA) {
                    (stp_t_APPLIF->fp_vd_ACCMLT)(u1_t_cnttid, &u2_ap_STSFIELD[0], &u4_ap_DELTA[0]);
                }
                if ((stp_t_APPLIF->fp_vd_UPDT     != vdp_PTR_NA) && (u1_t_update == (U1)TRUE)) {
                    (stp_t_APPLIF->fp_vd_UPDT)(u1_t_cnttid);
                }
                if ((stp_t_APPLIF->fp_vd_GRPHUPDT != vdp_PTR_NA) && (u1_t_update == (U1)TRUE)) {
                    (stp_t_APPLIF->fp_vd_GRPHUPDT)(u1_t_cnttid);
                }
                u1_t_actv = (U1)TRUE;
            }

            if((stp_t_APPL->u2_varbit       != (U2)0U    ) &&
               (stp_t_APPLIF->fp_vd_RSTIMMW != vdp_PTR_NA)) {
                stp_t_APPLIF->fp_vd_RSTIMMW(u1_t_actv, u1_t_cnttid, &u2_ap_STSFIELD[0]);
            }
        }
    }
}
/*===================================================================================================================================*/
/* static  U2      u2_s_TripcomManRstRqbitChk(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripcomManRstRqbitChk(void)
{
    static  const   ST_TRIPCOM_MANRSTRQ         st_sp_TRIPCOM_MANRSTRQ[TRIPCOM_MANRSTRQ_RSTRQ_NUM]       = {
        /*  fp_u1_GETSIGNAL,                    u2_rstrqbit                         */
        {   &u1_g_TripcomCfgGetTOFCRST,         (U2)(TRIPCOM_RSTRQBIT_M_AVGFEHE_TA  | TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA | TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC) },
        {   &u1_g_TripcomCfgGetTOFCRT2,         (U2)(TRIPCOM_RSTRQBIT_M_AVGFEHE_TA  | TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA | TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC) },
        {   &u1_g_TripcomCfgGetM1FCRST,         (U2)TRIPCOM_RSTRQBIT_M_AVGFEHE_ONEM                                                                     },
        {   &u1_g_TripcomCfgGetTOECRST,         (U2)(TRIPCOM_RSTRQBIT_M_AVGEE_TA    | TRIPCOM_RSTRQBIT_M_AVGVEHSPD_TA | TRIPCOM_RSTRQBIT_M_PTSRUNTM_LC) },
        {   &u1_g_TripcomCfgGetM1ECRST,         (U2)TRIPCOM_RSTRQBIT_M_AVGEE_ONEM                                                                       }
    };

    U2                                          u2_t_rstrqbit;
    U1                                          u1_t_val;
    U1                                          u1_t_sts;
    U1                                          u1_t_rst_cnt;

    u2_t_rstrqbit = (U2)0U;

    for (u1_t_rst_cnt = (U1)0U; u1_t_rst_cnt < (U1)TRIPCOM_MANRSTRQ_RSTRQ_NUM; u1_t_rst_cnt++) {
        u1_t_val = (U1)0U;
        u1_t_sts = st_sp_TRIPCOM_MANRSTRQ[u1_t_rst_cnt].fp_u1_GETSIGNAL(&u1_t_val);
        if (u1_t_sts == (U1)TRIPCOM_STSBIT_VALID) {
            u1_sp_tripcom_manrstrq[u1_t_rst_cnt] |= (u1_t_val & (U1)TRIPCOM_RSTRQ_ACT);
            if (u1_sp_tripcom_manrstrq[u1_t_rst_cnt] == (U1)TRIPCOM_RSTRQ_ACT) {
                u2_t_rstrqbit |= st_sp_TRIPCOM_MANRSTRQ[u1_t_rst_cnt].u2_rstrqbit;
            }
            u1_sp_tripcom_manrstrq[u1_t_rst_cnt] = (U1)(u1_sp_tripcom_manrstrq[u1_t_rst_cnt] << TRIPCOM_PREVSTS_SFT) & (U1)TRIPCOM_RSTRQ_MSK;
        }
    }

    u2_t_rstrqbit        |= u2_s_tripcom_dmreset;
    u2_s_tripcom_dmreset  = (U2)0U;
    return (u2_t_rstrqbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_TripcomAutRstRqbitChk(const U2 u2_a_VEHSYSSTS)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripcomAutRstRqbitChk(const U2 u2_a_VEHSYSSTS)
{
    static  const   U2                          u2_s_ECOCHK = (U2)(TRIPCOM_VEHSTS_ECORUNUNK | TRIPCOM_VEHSTS_ECORUNINV | TRIPCOM_VEHSTS_ECOSTP);
    static  const   U2                          u2_sp_AUTREQBIT[TRIPCOM_AUTRSTRQ_REFUEL_NUM] = {
        (U2)TRIPCOM_RSTRQBIT_A_FE_RECHRG,
        (U2)TRIPCOM_RSTRQBIT_A_DTE_RECHRG,
        (U2)TRIPCOM_RSTRQBIT_A_FRCRECHRG
    };

    U2                                          u2_t_rstrqbit;
    U1                                          u1_t_rxrst;
    U1                                          u1_t_rst_cnt;

    u2_t_rstrqbit = (U2)0U;

    /* Reset triggered by Driving cycle */
    if (((u2_s_tripcom_prvvehsyssts & (U2)TRIPCOM_VEHSTS_DRVCYC) == (U2)0U) &&
        ((u2_a_VEHSYSSTS            & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U)) {

        u2_t_rstrqbit |= (U2)TRIPCOM_RSTRQBIT_A_DRVCYC;
    }

    /* Reset triggered by Driving cycle OFF */
    if (((u2_s_tripcom_prvvehsyssts & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U) &&
        ((u2_a_VEHSYSSTS            & (U2)TRIPCOM_VEHSTS_DRVCYC) == (U2)0U)) {

        u2_t_rstrqbit |= (U2)TRIPCOM_RSTRQBIT_A_DRVCYC_OFF;
    }

    /* Reset triggered by Eco idling stop */
    if ((( u2_a_VEHSYSSTS            & (U2)TRIPCOM_VEHSTS_DRVCYC) == (U2)0U                   )  ||
        (((u2_a_VEHSYSSTS            & (U2)TRIPCOM_VEHSTS_DRVCYC) != (U2)0U                   )  &&
         ((u2_s_tripcom_prvvehsyssts & u2_s_ECOCHK              ) == (U2)0U                   )  &&
         ((u2_a_VEHSYSSTS            & u2_s_ECOCHK              ) == (U2)TRIPCOM_VEHSTS_ECOSTP))) {

        u2_t_rstrqbit |= (U2)TRIPCOM_RSTRQBIT_A_ECOSTP;
    }

    u1_sp_tripcom_autrstrq[TRIPCOM_AUTRSTRQ_REFUEL_FE]  |= (u1_s_tripcom_refuel_actbit & (U1)TRIPCOM_RSTRQ_ACT);
    u1_sp_tripcom_autrstrq[TRIPCOM_AUTRSTRQ_REFUEL_DTE] |= ((U1)(u1_s_tripcom_refuel_actbit >> TRIPCOM_RSTRQ_DTE_SFT) & (U1)TRIPCOM_RSTRQ_ACT);
    u1_sp_tripcom_autrstrq[TRIPCOM_AUTRSTRQ_FRCREFUEL]  |= u1_s_tripcom_frcrefuel_actbit;

    for (u1_t_rst_cnt = (U1)0U; u1_t_rst_cnt < (U1)TRIPCOM_AUTRSTRQ_REFUEL_NUM; u1_t_rst_cnt++) {
        if (u1_sp_tripcom_autrstrq[u1_t_rst_cnt] == (U1)TRIPCOM_RSTRQ_DEACT) {
            u2_t_rstrqbit |= u2_sp_AUTREQBIT[u1_t_rst_cnt];
        }
        u1_sp_tripcom_autrstrq[u1_t_rst_cnt] = (U1)(u1_sp_tripcom_autrstrq[u1_t_rst_cnt] << TRIPCOM_PREVSTS_SFT) & (U1)TRIPCOM_RSTRQ_MSK;
    }

    /* Reset triggered by Rx fuel/hydrogen/electric-power signal */
    u1_t_rxrst = u1_g_TripsnsrResetChk();
    if ((u1_t_rxrst & (U1)TRIPCOM_INSTFEHE_UPD) != (U1)0U) {
        u2_t_rstrqbit |= (U2)TRIPCOM_RSTRQBIT_A_UPDTFEHUSD;
    }
    
    if ((u1_t_rxrst & (U1)TRIPCOM_INSTEE_UPD) != (U1)0U) {
        u2_t_rstrqbit |= (U2)TRIPCOM_RSTRQBIT_A_UPDTEEUSD;
    }


    return (u2_t_rstrqbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_TripcomOtherRqbitChk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripcomOtherRqbitChk(void)
{
    U2          u2_t_othrqbit;
    U1          u1_t_checkmsk;
    U1          u1_t_jdg;

    u2_t_othrqbit = (U2)0U;

    /* Pause triggered by Refuel for FE */
    u1_t_checkmsk = (U1)TRIPCOM_RSTRQ_ACT;
    if ((u1_s_tripcom_refuel_actbit & u1_t_checkmsk) != (U1)0U) {
        u2_t_othrqbit = (U2)TRIPCOM_PSRQBIT_A_FE_RECHRG;
    }

    /* Pause triggered by Refuel for DTE */
    u1_t_checkmsk <<= TRIPCOM_RSTRQ_DTE_SFT;
    if ((u1_s_tripcom_refuel_actbit & u1_t_checkmsk) != (U1)0U) {
        u2_t_othrqbit |= (U2)TRIPCOM_PSRQBIT_A_DTE_RECHRG;
    }

    /* Pause triggered by Force Refuel */
    if (u1_s_tripcom_frcrefuel_actbit == (U1)TRIPCOM_RSTRQ_ACT) {
        u2_t_othrqbit |= (U2)TRIPCOM_PSRQBIT_A_FRCRECHRG;
    }

     /* Pause triggered by EV Run Mode  */
    u1_t_jdg = u1_g_TripcomCfgGetEVRunSts();
    if (u1_t_jdg == (U1)TRUE) {
        u2_t_othrqbit |= (U2)TRIPCOM_PSRQBIT_A_EVRUN;
    }

    return (u2_t_othrqbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_TripcomAutImmwRstRqbitChk(const U2 u2_a_STSFIELD)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripcomAutImmwRstRqbitChk(const U2 u2_a_STSFIELD)
{
    U2                                          u2_t_rstrqbit;

    u2_t_rstrqbit = (U2)0U;
    if (u1_s_tripcom_immr_frcrefuel_actbit == (U1)TRIPCOM_RSTRQ_DEACT) {
        u2_t_rstrqbit  = (U2)TRIPCOM_RSTRQBIT_A_FRCRECHRG;
        u2_t_rstrqbit &= u2_a_STSFIELD;
    }
    u1_s_tripcom_immr_frcrefuel_actbit = (U1)(u1_s_tripcom_immr_frcrefuel_actbit << TRIPCOM_PREVSTS_SFT) & (U1)TRIPCOM_RSTRQ_MSK;
    return(u2_t_rstrqbit);
}

/*===================================================================================================================================*/
/* static  U2      u2_s_TripcomManImmwRstRqbitChk(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U2      u2_s_TripcomManImmwRstRqbitChk(void)
{
    U2                                          u2_t_rstrqbit;

    u2_t_rstrqbit             = u2_s_tripcom_immw_dmreset;
    u2_s_tripcom_immw_dmreset = (U2)0U;
    return(u2_t_rstrqbit);
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCanTx(const U2 u2_a_VARBIT)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCanTx(const U2 u2_a_VARBIT)
{
    const   ST_TRIPCOM_CNTT *                   stp_t_APPL;
    const   ST_TRIPCOM_CALCTX *                 stp_t_APPTX;

    U4                                          u4_t_loop;
    U1                                          u1_tp_unittype[TRIPCOM_NUM_CANTXUNIT];
    U1                                          u1_t_unit;
    U2                                          u2_t_txval;


    vd_g_TripcomCfgGetUnit(&u1_tp_unittype[0]);

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_CNTTS; u4_t_loop++) {
        stp_t_APPL  = &st_gp_TRIPCOM_CNTTS_CFG[u4_t_loop];

        u2_t_txval  = (U2)TRIPCOM_CANTX_UNKNOWN;
        if (((stp_t_APPL->u2_varbit & u2_a_VARBIT)  != (U2)0U              ) &&
            ( stp_t_APPL->u1_applid                 <  (U1)TRIPCOM_NUM_APPL)) {

            stp_t_APPTX = &st_gp_TRIPCOM_CALCTX_CFG[stp_t_APPL->u1_applid];
            u1_t_unit   = (U1)0U;
            if (stp_t_APPTX->u1_unittype < (U1)TRIPCOM_NUM_CANTXUNIT) {
                u1_t_unit  = u1_tp_unittype[stp_t_APPTX->u1_unittype];
            }
            if (stp_t_APPTX->fp_u2_CALCTXVAL != vdp_PTR_NA) {
                u2_t_txval = (stp_t_APPTX->fp_u2_CALCTXVAL)(stp_t_APPL->u1_cnttid, u1_t_unit);
            }
        }
        vd_g_TripcomCfgSetTxValHk((U1)u4_t_loop, u2_t_txval);
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
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.1.0    03/30/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/28/2020  YA       Initial value transmission change                                                                  */
/*  1.2.0    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    Supports TripA and TripB.                                                                          */
/*  2.0.3    10/27/2021  TK       QAC supported.                                                                                     */
/*  2.2.0    02/25/2022  TA(M)    See triocom_nvmif v2.1.0                                                                           */
/*  2.2.1    04/14/2022  TA(M)    See dte_ed v2.2.0                                                                                  */
/*  2.2.2    07/28/2022  YI       Add u1_g_TripcomCfgGetTOFCRT2.                                                                     */
/*  2.2.3    08/08/2022  YI       Add u1_g_EvDtePct.                                                                                 */
/*  2.3.0    01/10/2024  TH       Add vd_g_TripcomNvmIfGrphInit.                                                                     */
/*  2.3.1    10/22/2024  TH       Delete Refuel Threshold                                                                            */
/*  2.4.0    02/18/2025  MaO(M)   Add write process immediately                                                                      */
/*  2.4.1    04/22/2025  KM       Add posttask for tripcom application                                                               */
/*  2.5.0    06/23/2025  RS       tripcom_comtx.c v2.4.1 -> v2.5.0.(Change for BEV System_Consideration_2)                           */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 04/03/2024  DR       Deleted engine type and info functions                                                             */
/*  BEV-01   01/20/2026  DR       Added send data cntt ID for AS_EVDT and AS_TOEC for FF2                                            */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * KM   = Kazuma Miyazawa, Denso Techno                                                                                           */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
