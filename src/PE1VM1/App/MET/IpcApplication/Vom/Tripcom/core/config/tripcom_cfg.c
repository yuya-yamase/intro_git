/* 2.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Trip Computer                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_CFG_C_MAJOR                     (2)
#define TRIPCOM_CFG_C_MINOR                     (6)
#define TRIPCOM_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"
#include "tripsnsr_cfg_private.h"

#include "avgee_kmpkwh.h"
#include "avggrph.h"
#include "instee_kmpkwh.h"
#include "evdte_km.h"
#include "avgvehspd_kmph.h"
#include "ptsruntm_hrs.h"
#include "ptsrundist_km.h"

#include "oxcan.h"

#include "alert.h"
#include "alert_mtrx.h"

#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_CFG_C_MAJOR != TRIPCOM_H_MAJOR) || \
     (TRIPCOM_CFG_C_MINOR != TRIPCOM_H_MINOR) || \
     (TRIPCOM_CFG_C_PATCH != TRIPCOM_H_PATCH))
#error "tripcom_cfg.c and tripcom.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_CFG_C_MAJOR != TRIPCOM_CFG_H_MAJOR) || \
     (TRIPCOM_CFG_C_MINOR != TRIPCOM_CFG_H_MINOR) || \
     (TRIPCOM_CFG_C_PATCH != TRIPCOM_CFG_H_PATCH))
#error "tripcom_cfg.c and tripcom_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (TRIPCOM_STSBIT_INVALID != COM_TIMEOUT))
#error "tripcom status bit and com status bit are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_NUM_PTSYS                       (16U)

#define TRIPCOM_EHV1S94_FAILTIM                 (5000U/OXCAN_MAIN_TICK)

#define TRIPCOM_CFG_EVDTE_VAL100                (100U)

#define TRIPCOM_CFG_EVDTE_RXLSB                 (100U)

/* refer to tripcom.h */
/* Bit[0-1] : Common Bit Definition             */
/* #define TRIPCOM_STSBIT_VALID                 (0x00U)            *//*  Valid                                                    */
/* #define TRIPCOM_STSBIT_UNKNOWN               (0x01U)            *//*  Unknown                                                  */
/* #define TRIPCOM_STSBIT_INVALID               (0x02U)            *//*  Invalid                                                  */
#define TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_UNK    (TRIPCOM_STSBIT_UNKNOWN)
#define TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_INV    (TRIPCOM_STSBIT_INVALID)

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
static U1       u1_s_TripcomCfgJdgEvDteSts(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void                (* const                    fp_gp_TRIPCOM_CALC_APPL_TASK[])(const U2 * u2_ap_STSFIELD)  = {
    &vd_g_AvgEeApplTask,
    &vd_g_EvDteApplTask,
    &vd_g_AvgVehspdApplTask,
    &vd_g_PtsRunDistApplTask
};
const U1     u1_g_TRIPCOM_NUM_CALC_APPL_TASK = sizeof(fp_gp_TRIPCOM_CALC_APPL_TASK) / sizeof(fp_gp_TRIPCOM_CALC_APPL_TASK[0]);
const           ST_TRIPCOM_IF                   st_gp_TRIPCOM_IF_CFG[TRIPCOM_NUM_APPL]                      = {
    {   vdp_PTR_NA,              &u1_g_AvgEeCalcTrnst,      &vd_g_AvgEeAccmlt,      &vd_g_AvgEeUpdt,        &vd_g_AvgEeGrphUpdt,  &vd_g_AvgEeRstImmw     }, /* 00 Average Electric Economy             */
    {   vdp_PTR_NA,              &u1_g_InstEeCalcTrnst,     &vd_g_InstEeAccmlt,     &vd_g_InstEeUpdt,       vdp_PTR_NA,           vdp_PTR_NA             }, /* 01 Inst. Electric Economy               */
    {   vdp_PTR_NA,              &u1_g_EvDteCalcTrnst,      vdp_PTR_NA,             &vd_g_EvDteUpdt,        vdp_PTR_NA,           vdp_PTR_NA             }, /* 02 EV Distance To Empty                 */
    {   vdp_PTR_NA,              &u1_g_AvgVehspdCalcTrnst,  &vd_g_AvgVehspdAccmlt,  &vd_g_AvgVehspdUpdt,    vdp_PTR_NA,           &vd_g_AvgVehspdRstImmw }, /* 03 Average Vehicle Speed                */
    {   &vd_g_PtsRunTmCondChk,   &u1_g_PtsRunTmCalcTrnst,   &vd_g_PtsRunTmAccmlt,   vdp_PTR_NA,             vdp_PTR_NA,           &vd_g_PtsRunTmRstImmw  }, /* 04 Powertrain System Run Time           */
    {   vdp_PTR_NA,              &u1_g_PtsRunDistCalcTrnst, &vd_g_PtsRunDistAccmlt, vdp_PTR_NA,             vdp_PTR_NA,           vdp_PTR_NA             }, /* 05 Powertrain System Run Distance       */
    {   vdp_PTR_NA,              vdp_PTR_NA,                vdp_PTR_NA,             vdp_PTR_NA,             vdp_PTR_NA,           vdp_PTR_NA             }  /* 06 Distance To Empty for ED             */
};
const           ST_TRIPCOM_CALCTX               st_gp_TRIPCOM_CALCTX_CFG[TRIPCOM_NUM_APPL]                  = {
    {   &u2_g_AvgEeCalcTx,              (U1)TRIPCOM_CANTXUNIT_EECON             },  /*  00 Average Electric Economy                  */
    {   &u2_g_InstEeCalcTx,             (U1)TRIPCOM_CANTXUNIT_EECON             },  /*  01 Inst. Electric Economy                    */
    {   &u2_g_EvDteCalcTx,              (U1)TRIPCOM_CANTXUNIT_DIST              },  /*  02 EV Distance To Empty                      */
    {   &u2_g_AvgVehspdCalcTx,          (U1)TRIPCOM_CANTXUNIT_SPEED             },  /*  03 Average Vehicle Speed                     */
    {   &u2_g_PtsRunTmCalcTx,           (U1)U1_MAX                              },  /*  04 Powertrain System Run Time                */
    {   &u2_g_PtsRunDistCalcTx,         (U1)TRIPCOM_CANTXUNIT_DIST              },  /*  05 Powertrain System Run Distance            */
    {   vdp_PTR_NA,                     (U1)U1_MAX                              }   /*  06 Distance To Empty for ED                  */
};
const           ST_TRIPCOM_CNTT                 st_gp_TRIPCOM_CNTTS_CFG[TRIPCOM_NUM_CNTTS]                  = {
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_TA,         (U2)0x0100U     },  /*  Total Average                                */
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_DC,         (U2)0x0100U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_ONEM,       (U2)0x0100U     },  /*  One min Cycle                                */
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_FIVEM,      (U2)0x0000U     },  /*  Five mins Cycle                              */
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_DC_DT,      (U2)0x0100U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_AVGEE,         (U1)AVGEE_CNTT_DC_EC,      (U2)0x0100U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_INSTEE,        (U1)INSTEE_CNTT_RX,        (U2)0x0200U     },  /*  Rx Signal Cycle                              */
    {   (U1)TRIPCOM_APPL_EVDTE,         (U1)EVDTE_CNTT_EP,         (U2)0x0400U     },  /*  Electric Power                               */
    {   (U1)TRIPCOM_APPL_AVGVEHSPD,     (U1)AVGVEHSPD_CNTT_TA,     (U2)0x8000U     },  /*  Total Average                                */
    {   (U1)TRIPCOM_APPL_AVGVEHSPD,     (U1)AVGVEHSPD_CNTT_DC,     (U2)0x8000U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_AVGVEHSPD,     (U1)AVGVEHSPD_CNTT_TR_A,   (U2)0x8000U     },  /*  Trip A                                       */
    {   (U1)TRIPCOM_APPL_AVGVEHSPD,     (U1)AVGVEHSPD_CNTT_TR_B,   (U2)0x8000U     },  /*  Trip B                                       */
    {   (U1)TRIPCOM_APPL_PTSRUNTM,      (U1)PTSRUNTM_CNTT_LC,      (U2)0x8000U     },  /*  Life Cycle                                   */
    {   (U1)TRIPCOM_APPL_PTSRUNTM,      (U1)PTSRUNTM_CNTT_DC,      (U2)0x8000U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_PTSRUNTM,      (U1)PTSRUNTM_CNTT_TR_A,    (U2)0x8000U     },  /*  Trip A                                       */
    {   (U1)TRIPCOM_APPL_PTSRUNTM,      (U1)PTSRUNTM_CNTT_TR_B,    (U2)0x8000U     },  /*  Trip B                                       */
    {   (U1)TRIPCOM_APPL_PTSRUNDIST,    (U1)PTSRUNDIST_CNTT_LC,    (U2)0x8000U     },  /*  Life Cycle                                   */
    {   (U1)TRIPCOM_APPL_PTSRUNDIST,    (U1)PTSRUNDIST_CNTT_DC,    (U2)0x8000U     },  /*  Driving Cycle                                */
    {   (U1)TRIPCOM_APPL_PTSRUNDIST,    (U1)PTSRUNDIST_CNTT_TR_A,  (U2)0x8000U     },  /*  Trip A                                       */
    {   (U1)TRIPCOM_APPL_PTSRUNDIST,    (U1)PTSRUNDIST_CNTT_TR_B,  (U2)0x8000U     },  /*  Trip B                                       */
    {   (U1)TRIPCOM_APPL_DTE_ED,        (U1)DTE_ED_CNTT_FU,        (U2)0x0000U     }   /*  Fuel                                         */
};
const           U2                              u2_gp_TRIPCOM_GRPH_RSTBIT[AVGGRPH_NUM_CNTT]                 = {
    (U2)TRIPCOM_RSTRQBIT_M_AVGEE_TA,
    (U2)TRIPCOM_RSTRQBIT_M_AVGEE_ONEM
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgApplInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgApplInit(void) 
{
    static const   FP_VD_FVD                               fp_sp_TRIPCOM_CALC_APPL_INIT[]                              = {
        &vd_g_AvgEeInit,
        &vd_g_AvgGrphInit,
        &vd_g_InstEeInit,
        &vd_g_EvDteInit,
        &vd_g_AvgVehspdInit,
        &vd_g_PtsRunTmInit,
        &vd_g_PtsRunDistInit
    };

    vd_g_Fpcall_vd_Fvd(&fp_sp_TRIPCOM_CALC_APPL_INIT[0], u2_NC_VD_FVD(fp_sp_TRIPCOM_CALC_APPL_INIT));

}

/*===================================================================================================================================*/
/* U2              u2_g_TripcomCfgGetVariation(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2              u2_g_TripcomCfgGetVariation(void)
{
    static  const   U2   u2_s_TRIPCOM_VAR = (U2)0x8700U;
    return (u2_s_TRIPCOM_VAR);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomCfgGetPIEVSTS(U1 * u1p_a_pievsts)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomCfgGetPIEVSTS(U1 * u1p_a_pievsts)
{
    U1          u1_t_msgsts;

    (*u1p_a_pievsts) = (U1)0U;
    u1_t_msgsts      = (U1)TRIPCOM_STSBIT_VALID;
    u1_t_msgsts      = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_EHV1S94_CH0,
                                        (U4)OXCAN_SYS_IGP,
                                        (U2)TRIPCOM_EHV1S94_FAILTIM) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PIEVSTS, u1p_a_pievsts);

    return (u1_t_msgsts);
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgSmoothingTask(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgSmoothingTask(void)
{
    static const FP_VD_FVD             fp_sp_TRIPCOM_SMOOTH_TASK[] = {
        &vd_g_InstEeSmooth
    };

    vd_g_Fpcall_vd_Fvd(&fp_sp_TRIPCOM_SMOOTH_TASK[0], u2_NC_VD_FVD(fp_sp_TRIPCOM_SMOOTH_TASK));
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomNvmIfSyncCmplt(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfSyncCmplt(void)
{
    vd_g_AvgEeUpdt((U1)AVGEE_CNTT_TA);
    vd_g_AvgVehspdUpdt((U1)AVGVEHSPD_CNTT_TA);
    vd_g_AvgVehspdUpdt((U1)AVGVEHSPD_CNTT_TR_A);
    vd_g_AvgVehspdUpdt((U1)AVGVEHSPD_CNTT_TR_B);
    vd_g_AvgGrphDataSync();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomNvmIfGrphSyncCmplt(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfGrphSyncCmplt(void)
{
    vd_g_AvgGrphDataSync();
}
/*===================================================================================================================================*/
/* U1              u1_g_TripcomEvDteKmIgOffAcOn(U4 * u4p_a_km)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomEvDteKmIgOffAcOn(U4 * u4p_a_km)
{
    U4 u4_t_evrngkm;
    U4 u4_t_mul;
    U4 u4_t_div;
    U2 u2_t_pievd06;
    U1 u1_t_pievdsr;
    U1 u1_t_evdte_appsts;
    U1 u1_t_sts;

    u1_t_evdte_appsts = u1_s_TripcomCfgJdgEvDteSts();

    if ((u1_t_evdte_appsts & (U1)(TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_INV | TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_UNK)) == (U1)0U) {
        vd_g_TripsnsrCfgEvDteDist(&u2_t_pievd06);
        vd_g_TripsnsrCfgEvDteSubRate(&u1_t_pievdsr);

        if (u1_t_pievdsr >= (U1)TRIPCOM_CFG_EVDTE_VAL100) {
            u1_t_pievdsr = (U1)TRIPCOM_CFG_EVDTE_VAL100;
        }

        if (u2_t_pievd06 == (U2)0U) {
            u1_t_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_RCVZERO;
            u4_t_evrngkm       = (U4)0U;
        }
        else {
            u4_t_div = (U4)TRIPCOM_CFG_EVDTE_VAL100 - (U4)u1_t_pievdsr;
            /* The maximum value of u1_t_pievdsr is 100, so it is not less than 0.                                               */
            u4_t_mul = (U4)u2_t_pievd06 * u4_t_div;
            /* The maximum value of u2_t_pievd06 is 65535. The maximum value of u4_t_div is 100.                                 */
            /* so ((U4)u2_t_pievd06 * u4_t_div) is always less than U4_MAX.                                                      */
            u4_t_mul = u4_t_mul * (U4)TRIPCOM_CFG_EVDTE_RXLSB;
            /* The maximum value of u4_t_mul is 65535 * 100. The value of EVDTE_RXLSB is 100.                                    */
            /* so (u4_t_mul * (U4)EVDTE_RXLSB) is always less than U4_MAX.                                                       */
            u4_t_evrngkm = u4_t_mul / (U4)TRIPCOM_CFG_EVDTE_VAL100;
        }
    }
    else {
        u4_t_evrngkm = (U4)0U;
    }

    if (u4p_a_km != vdp_PTR_NA) {
        (*u4p_a_km) = u4_t_evrngkm;
    }

    u1_t_sts  = u1_t_evdte_appsts & (U1)(TRIPCOM_STSBIT_UNKNOWN | TRIPCOM_STSBIT_INVALID | TRIPCOM_STSBIT_EVDTE_RCVZERO);

    return (u1_t_sts);
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomEvDteKmIgOffAcOff(U4 * u4p_a_km)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomEvDteKmIgOffAcOff(U4 * u4p_a_km)
{
    U4 u4_t_evrngkm;
    U2 u2_t_pievd06;
    U1 u1_t_evdte_appsts;
    U1 u1_t_sts;

    u1_t_evdte_appsts = u1_s_TripcomCfgJdgEvDteSts();

    if ((u1_t_evdte_appsts & (U1)(TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_INV | TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_UNK)) == (U1)0U) {
        vd_g_TripsnsrCfgEvDteDist(&u2_t_pievd06);

        if (u2_t_pievd06 == (U2)0U) {
            u1_t_evdte_appsts |= (U1)TRIPCOM_STSBIT_EVDTE_RCVZERO;
            u4_t_evrngkm       = (U4)0U;
        }
        else {
            u4_t_evrngkm = (U4)u2_t_pievd06 * (U4)TRIPCOM_CFG_EVDTE_RXLSB;
            /* The maximum value of u2_t_pievd06 is 65535. The value of EVDTE_RXLSB is 100.                                      */
            /* so ((U4)u2_t_pievd06 * (U4)EVDTE_RXLSB) is always less than U4_MAX.                                               */
        }
    }
    else {
        u4_t_evrngkm = (U4)0U;
    }

    if (u4p_a_km != vdp_PTR_NA) {
        (*u4p_a_km) = u4_t_evrngkm;
    }

    u1_t_sts  = u1_t_evdte_appsts & (U1)(TRIPCOM_STSBIT_UNKNOWN | TRIPCOM_STSBIT_INVALID | TRIPCOM_STSBIT_EVDTE_RCVZERO);

    return (u1_t_sts);
}

/*===================================================================================================================================*/
/* static void     u1_s_TripcomCfgJdgEvDteSts(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_TripcomCfgJdgEvDteSts(void)
{
    U1 u1_t_sts;
    U1 u1_t_evdte_appsts;

    u1_t_evdte_appsts = (U1)0U;

    u1_t_sts          = u1_g_TripsnsrCfgEvDteBatSts();
    if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_INVALID) != (U1)0U) {
        u1_t_evdte_appsts  = (U1)TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_INV;
    }
    if ((u1_t_sts & (U1)TRIPSNSR_EVDTE_UNKNOWN) != (U1)0U) {
        u1_t_evdte_appsts |= (U1)TRIPCOM_CFG_STSBIT_EVDTE_PIEVDXX_UNK;
    }

    return (u1_t_evdte_appsts);
}

/*===================================================================================================================================*/
/* void             vd_s_TripomCfgPostAppTask(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void             vd_s_TripomCfgPostAppTask(void)
{
    vd_g_AvgEePostTask();
    vd_g_AvgGrphTimeCnt();
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version   Date        Author   Change Description                                                                                */
/* ---------- ----------  -------  ------------------------------------------------------------------------------------------------- */
/*  1.0.0     11/07/2018  HY       New.                                                                                              */
/*  1.1.0     03/17/2020  YA       Change for 800B CV                                                                                */
/*  1.1.1     07/28/2020  YA       Initial value transmission change                                                                 */
/*  1.2.0     10/07/2020  YA       Change for 800B CV-R.                                                                             */
/*  2.0.1     10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                    */
/*  2.0.2     10/25/2021  TA(M)    tripcom.c v2.0.1 -> v2.0.2.                                                                       */
/*  2.0.3     10/25/2021  TK       tripcom.c v2.0.2 -> v2.0.3.                                                                       */
/*  2.2.0     02/25/20232 TA(M)    tripcom.c v2.0.3 -> v2.2.0.                                                                       */
/*  2.2.1     04/14/2022  TA(M)    tripcom.c v2.2.0 -> v2.2.1.                                                                       */
/*  2.2.2     07/28/2022  YI       tripcom.c v2.2.1 -> v2.2.2.                                                                       */
/*  2.2.3     08/08/2022  YI       tripcom.c v2.2.2 -> v2.2.3.                                                                       */
/*  2.3.0     01/10/2024  TH       tripcom.c v2.2.3 -> v2.3.0.                                                                       */
/*  2.3.1     10/22/2024  TH       tripcom.c v2.3.0 -> v2.3.1.                                                                       */
/*  2.4.0     02/18/2025  MaO(M)   tripcom.c v2.3.1 -> v2.4.0.                                                                       */
/*  2.4.1     04/22/2025  KM       tripcom.c v2.4.0 -> v2.4.1.                                                                       */
/*  2.5.0     06/23/2025  RS       tripcom_comtx.c v2.4.1 -> v2.5.0.(Change for BEV System_Consideration_2)                          */
/*  2.6.0     02/11/2026  DT       tripcom_comtx.c v2.5.0 -> v2.6.0.(Change for BEV FF2)                                             */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision  Date        Author   Change Description                                                                                */
/* ---------- ----------  -------  ------------------------------------------------------------------------------------------------- */
/*  178D-1    11/22/2021  YA       Changed for 178D 1A                                                                               */
/*  178D-2    02/04/2022  YS       Changed for MET-M_DM-CSTD-1-02-C-C2-178D-F                                                        */
/*  200D      09/04/2022  SK       Changed for 200D 1A                                                                               */
/*  200D      12/01/2022  HH       Changed for 200D MPT                                                                              */
/*  330D      01/10/2023  KK       Changed for 330D CV-R                                                                             */
/*  330D      02/07/2023  HH       Changed for 330D CV-R                                                                             */
/*  19PFv3-1  11/06/2023  SH       Changed to read calibration parameter                                                             */
/*  19PFv3-2  02/07/2024  PG       Changed for MET-M_DMTOEC-CSTD-1-01-E-C0                                                           */
/*  19PFv3-3  02/12/2024  PG       Changed for MET-M_DMEVRNGE-CSTD-1-07-A-C1                                                         */
/*  19PFv3-4  02/26/2024  PG       Changed for MET-M_DMM1EC-CSTD-0-02-B-C0                                                           */
/*  19PFv3-5  03/19/2024  PG       Changed for MET-M_DMINEC-CSTD-1-01-D-C2                                                           */
/*  19PFv3-6  03/20/2024  DR       Changed variation for EV Ratio                                                                    */
/*  19PFv3-7  04/03/2024  DR       Changed for deletion of MET-M_ENG-CSTD-0-02-A-C2                                                  */
/*  19PFv3-8  04/12/2024  SH       Add calibration guard                                                                             */
/*  19PFv3-9  05/16/2024  SH       Delete  MCUID0432 default process                                                                 */
/*  19PFv3-10 06/10/2024  PG       Changed for MET-M_DMAFFC-CSTD-1-02-A-C0                                                           */
/*  19PFv3-11 06/24/2024  SM       Removed vd_g_DteEdInit function call in vd_g_TripcomNvmIfSyncCmplt to fix bug MET19PFV3-16362     */
/*  19PFv3-12 06/27/2024  TN       Delete Calibration Guard Process.                                                                 */
/*  19PFv3-13 11/19/2024  KH       Delete Compile switch                                                                             */
/*  19PFv3-14 01/14/2025  AA       Unapply Distance to Empty                                                                         */
/*  19PFv3-15 04/21/2025  SN       Changed u1_g_TripcomCfgGetEVRunSts                                                                */
/*  BEV-01    01/13/2026  PG       Delete Compile switch for u1_g_TripcomCfgGetTOECRST                                               */
/*  BEV-02    01/22/2026  DR       Added CNTTID for AS_EVDT and AS_TOEC                                                              */
/*  BEV-03    02/12/2026  DT       Deleted unapplied parameter for BEV FF2                                                           */
/*  BEV-04    02/12/2026  EA       Deleted/Deactivated other than BEV Powertrain processes                                           */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * YS   = Yosuke Sugimoto, Denso Techno                                                                                           */
/*  * SK   = Shintaro Kano, Denso Techno                                                                                             */
/*  * HH   = Hiroki Hara, Denso Techno                                                                                               */
/*  * KK   = Kohei Kato, Denso Techno                                                                                                */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * AA   = Anna Asuncion, DTPH                                                                                                     */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * KM   = Kazuma Miyazawa, Denso Techno                                                                                           */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*  * DT   = Dj Tutanes, DTPH                                                                                                        */
/*  * EA   = Eunice Avelin, DTPH                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
