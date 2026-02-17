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
#define TRIPCOM_COMTX_C_MAJOR                     (2)
#define TRIPCOM_COMTX_C_MINOR                     (6)
#define TRIPCOM_COMTX_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_cfg_private.h"
#include "tripcom_comtx.h"
#include "oxcan.h"
#include "vardef.h"
#include "veh_opemd.h"
#include "locale.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_COMTX_C_MAJOR != TRIPCOM_H_MAJOR) || \
     (TRIPCOM_COMTX_C_MINOR != TRIPCOM_H_MINOR) || \
     (TRIPCOM_COMTX_C_PATCH != TRIPCOM_H_PATCH))
#error "tripcom_comtx.c and tripcom.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_COMTX_C_MAJOR != TRIPCOM_COMTX_H_MAJOR) || \
     (TRIPCOM_COMTX_C_MINOR != TRIPCOM_COMTX_H_MINOR) || \
     (TRIPCOM_COMTX_C_PATCH != TRIPCOM_COMTX_H_PATCH))
#error "tripcom_comtx.c and tripcom_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_COMTX_TICK                      (10U)

#define TRIPCOM_COMTX_PTSON_250MS               (250U / TRIPCOM_COMTX_TICK)
#define TRIPCOM_COMTX_DRVCYC_MSK                (0x03U)
#define TRIPCOM_COMTX_NUM_UNITSIG               (1U)
#define TRIPCOM_COMTX_TXHLD_2SEC                (2000U / TRIPCOM_COMTX_TICK)

#define TRIPCOM_COMTX_EC_SCL_000_UNDEF          (0U)

#define TRIPCOM_COMTX_NFCS_TYPE_A               (2U)

#define TRIPCOM_COMTX_PREVSTS_SFT               (1U)

/* UNIT_6 unit conversion (mile/kWh US or UK  */
#define TRIPCOM_UNIT_VAL_ELECO_MPKWH            (3U)
#define TRIPCOM_UNIT_VAL_ELECO_MPKWH_UK         (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    void    (* const                            fp_vd_UNITTX)(const U1 u1_a_UNIT);
    U1                                          u1_unittype;
} ST_TRIPCOM_COMUNITTX;

typedef struct {
    U1                                          u1_ch;
    U1                                          u1_unit_num;
    const U1 *                                  u1p_table;
} ST_TRIPCOM_LOCALE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_tripcom_tx_ptson_elpsd;
static  U1                                      u1_s_tripcom_tx_drvcyc;
static  U1                                      u1_sp_tripcom_tx_unit[TRIPCOM_NUM_CANTXUNIT];
static  U2                                      u2_sp_tripcom_tx_value[TRIPCOM_NUM_CNTTS];
static  U1                                      u1_s_tripcom_tx_m1ec_timer;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_TripcomCfgCanTxInit(void);

static  void    vd_s_TripcomCfgCanTxPtsOn250ms(void);

static  void    vd_s_TripcomCfgCanTxUNIT6(const U1 u1_a_UNIT);

static  void    vd_s_TripcomCfgCanTxTOEC(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxM1EC1(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxASEC(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxASEVDT(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxASTOEC(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxINEC(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxRANGE(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxEVRANGE(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxASSP(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxASTM(const U2 u2_a_VALUE);
static  void    vd_s_TripcomCfgCanTxEC_SCL(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  const   U1                              u1_sp_TRIPCOM_TX_SPEED_UNTCNV[UNIT_NUM_VAL_SPEED]        = {
    (U1)1U,                                     /* 00 UNIT_VAL_SPEED_KMPH       */
    (U1)2U                                      /* 01 UNIT_VAL_SPEED_MPH        */
};
static  const   U1                              u1_sp_TRIPCOM_TX_DIST_UNTCNV[UNIT_NUM_VAL_DIST]          = {
    (U1)1U,                                     /* 00 UNIT_VAL_DIST_KM          */
    (U1)2U                                      /* 01 UNIT_VAL_DIST_MILE        */
};
static  const   U1                              u1_sp_TRIPCOM_TX_EECON_UNTCNV[UNIT_NUM_VAL_ELECO]        = {
    (U1)0U,                                     /* 00 UNIT_VAL_ELECO_WHPKM      */
    (U1)0U,                                     /* 01 UNIT_VAL_ELECO_KWHPKM     */
    (U1)0U,                                     /* 02 UNIT_VAL_ELECO_WHPMILE    */
    (U1)0U,                                     /* 03 UNIT_VAL_ELECO_KWHPMILE   */
    (U1)1U,                                     /* 04 UNIT_VAL_ELECO_KMPKWH     */
    (U1)2U,                                     /* 05 UNIT_VAL_ELECO_KWHP100KM  */
    (U1)3U                                      /* 06 UNIT_VAL_ELECO_MILEPKWH   */
};
static  const   ST_TRIPCOM_LOCALE               st_sp_TRIPCOM_TX_LOCALE_INF[TRIPCOM_NUM_CANTXUNIT]       = {
    {   (U1)UNIT_IDX_SPEED,      (U1)UNIT_NUM_VAL_SPEED,      &u1_sp_TRIPCOM_TX_SPEED_UNTCNV[0]   },
    {   (U1)UNIT_IDX_DIST,       (U1)UNIT_NUM_VAL_DIST,       &u1_sp_TRIPCOM_TX_DIST_UNTCNV[0]    },
    {   (U1)UNIT_IDX_ELECO,      (U1)UNIT_NUM_VAL_ELECO,      &u1_sp_TRIPCOM_TX_EECON_UNTCNV[0]   }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgTxBonInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgTxBonInit(void)
{
    vd_s_TripcomCfgCanTxInit();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgTxWkupInit(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgTxWkupInit(void)
{
    vd_s_TripcomCfgCanTxInit();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomComTxTask(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomComTxTask(void)
{
    static  void    (* const                    fp_sp_vd_TXVAL[TRIPCOM_NUM_CNTTS])(const U2 u2_a_VALUE) = {
        &vd_s_TripcomCfgCanTxTOEC,              /*  00 AVGEE_CNTT_TA            */
        &vd_s_TripcomCfgCanTxASEC,              /*  01 AVGEE_CNTT_DC            */
        &vd_s_TripcomCfgCanTxM1EC1,             /*  02 AVGEE_CNTT_ONEM          */
        vdp_PTR_NA,                             /*  03 AVGEE_CNTT_FIVEM         */
        &vd_s_TripcomCfgCanTxASEVDT,            /*  04 AVGEE_CNTT_DC_DT         */
        &vd_s_TripcomCfgCanTxASTOEC,            /*  05 AVGEE_CNTT_DC_EC         */
        &vd_s_TripcomCfgCanTxINEC,              /*  06 INSTEE_CNTT_RX           */
        &vd_s_TripcomCfgCanTxEVRANGE,           /*  07 EVDTE_CNTT_EP            */
        vdp_PTR_NA,                             /*  08 AVGVEHSPD_CNTT_TA        */
        &vd_s_TripcomCfgCanTxASSP,              /*  09 AVGVEHSPD_CNTT_DC        */
        vdp_PTR_NA,                             /*  10 AVGVEHSPD_CNTT_TR_A      */
        vdp_PTR_NA,                             /*  11 AVGVEHSPD_CNTT_TR_B      */
        vdp_PTR_NA,                             /*  12 PTSRUNTM_CNTT_LC         */
        &vd_s_TripcomCfgCanTxASTM,              /*  13 PTSRUNTM_CNTT_DC         */
        vdp_PTR_NA,                             /*  14 PTSRUNTM_CNTT_TR_A       */
        vdp_PTR_NA,                             /*  15 PTSRUNTM_CNTT_TR_B       */
        vdp_PTR_NA,                             /*  16 PTSRUNDIST_CNTT_LC       */
        vdp_PTR_NA,                             /*  17 PTSRUNDIST_CNTT_DC       */
        vdp_PTR_NA,                             /*  18 PTSRUNDIST_CNTT_TR_A     */
        vdp_PTR_NA,                             /*  19 PTSRUNDIST_CNTT_TR_B     */
        &vd_s_TripcomCfgCanTxRANGE              /*  20 DTE_ED_CNTT_FU           */
    };
    static  const   ST_TRIPCOM_COMUNITTX        st_sp_TRIPCOM_TX_UNIT[TRIPCOM_COMTX_NUM_UNITSIG]        = {
        {   &vd_s_TripcomCfgCanTxUNIT6,         (U1)TRIPCOM_CANTXUNIT_EECON     }
    };
    const   ST_TRIPCOM_COMUNITTX *              stp_t_UNIT;
    U4                                          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_CNTTS; u4_t_loop++) {
        if (fp_sp_vd_TXVAL[u4_t_loop] != vdp_PTR_NA) {
            (fp_sp_vd_TXVAL[u4_t_loop])(u2_sp_tripcom_tx_value[u4_t_loop]);
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_COMTX_NUM_UNITSIG; u4_t_loop++) {
        stp_t_UNIT = &st_sp_TRIPCOM_TX_UNIT[u4_t_loop];

        if ((stp_t_UNIT->u1_unittype < (U1)TRIPCOM_NUM_CANTXUNIT    ) &&
            (u1_sp_tripcom_tx_unit[stp_t_UNIT->u1_unittype] != (U1)0U)) {

            (stp_t_UNIT->fp_vd_UNITTX)(u1_sp_tripcom_tx_unit[stp_t_UNIT->u1_unittype]);
        }
    }

    vd_s_TripcomCfgCanTxEC_SCL();
    vd_s_TripcomCfgCanTxPtsOn250ms();

}

/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgSetTxValHk(const U1 u1_a_CNTTID, const U2 u2_a_TXVAL)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgSetTxValHk(const U1 u1_a_CNTTID, const U2 u2_a_TXVAL)
{
    u2_sp_tripcom_tx_value[u1_a_CNTTID] = u2_a_TXVAL;
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomCfgGetUnit(U1 * u1_ap_unittype)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomCfgGetUnit(U1 * u1_ap_unittype)
{
    U4                                          u4_t_loop;
    U1                                          u1_t_unit;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_CANTXUNIT; u4_t_loop++) {
        u1_ap_unittype[u4_t_loop] = (U1)0U;
        u1_t_unit = u1_g_Unit(st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1_ch);
        if (u1_t_unit < st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1_unit_num) {
            u1_ap_unittype[u4_t_loop] = st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1p_table[u1_t_unit];
        }
        u1_sp_tripcom_tx_unit[u4_t_loop] = u1_ap_unittype[u4_t_loop];
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxInit(void)
{
    U4                                          u4_t_loop;
    U1                                          u1_t_unit;
    U1                                          u1_t_sndval;
    U1                                          u1_t_unitsndval;
    U2                                          u2_t_range_sndval;


    u1_s_tripcom_tx_ptson_elpsd = (U1)U1_MAX;
    u1_s_tripcom_tx_drvcyc      = (U1)FALSE;
    u2_t_range_sndval           = (U2)TRIPCOM_CANTX_UNKNOWN;

    u1_s_tripcom_tx_m1ec_timer  = (U1)U1_MAX;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NUM_CANTXUNIT; u4_t_loop++) {
        u1_sp_tripcom_tx_unit[u4_t_loop] = (U1)0U;
        u1_t_unit = u1_g_Unit(st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1_ch);
        if (u1_t_unit < st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1_unit_num) {
            u1_sp_tripcom_tx_unit[u4_t_loop] = st_sp_TRIPCOM_TX_LOCALE_INF[u4_t_loop].u1p_table[u1_t_unit];
        }
    }

    /* to avoid event-tx when initial value of bit-assignment table is inconsistent with tripcom spec */
    /* only for +B-on message                                                                         */

    (void)Com_SendSignal(ComConf_ComSignal_TO_EC,    &u2_sp_tripcom_tx_value[0]);

    (void)Com_SendSignal(ComConf_ComSignal_M1_EC1,   &u2_sp_tripcom_tx_value[2]);

    (void)Com_SendSignal(ComConf_ComSignal_AS_EC,   &u2_sp_tripcom_tx_value[1]);

    (void)Com_SendSignal(ComConf_ComSignal_AS_EVDT,   &u2_sp_tripcom_tx_value[4]);

    (void)Com_SendSignal(ComConf_ComSignal_AS_TOEC,   &u2_sp_tripcom_tx_value[5]);

    (void)Com_SendSignal(ComConf_ComSignal_IN_EC,    &u2_sp_tripcom_tx_value[6]);

    (void)Com_SendSignal(ComConf_ComSignal_RANGE,   &u2_t_range_sndval);

    (void)Com_SendSignal(ComConf_ComSignal_EV_RANGE, &u2_sp_tripcom_tx_value[7]);

    (void)Com_SendSignal(ComConf_ComSignal_AS_SP,   &u2_sp_tripcom_tx_value[9]);

    (void)Com_SendSignal(ComConf_ComSignal_AS_TM,   &u2_sp_tripcom_tx_value[13]);

    (void)Com_SendSignal(ComConf_ComSignal_UNIT_6,  &u1_sp_tripcom_tx_unit[TRIPCOM_CANTXUNIT_EECON]);

    u1_t_sndval = (U1)0U;
    (void)Com_SendSignal(ComConf_ComSignal_M1_EC_R, &u1_t_sndval);

    u1_t_sndval = (U1)TRIPCOM_COMTX_EC_SCL_000_UNDEF;
    (void)Com_SendSignal(ComConf_ComSignal_EC_SCL, &u1_t_sndval);

    u1_t_sndval = (U1)TRIPCOM_COMTX_NFCS_TYPE_A;
    (void)Com_SendSignal(ComConf_ComSignal_NFCS, &u1_t_sndval);

}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxPtsOn250ms(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxPtsOn250ms(void)
{
    U1                                          u1_t_igsts;
    U1                                          u1_t_ptssts;
    U1                                          u1_t_drvcyc;


    if (u1_s_tripcom_tx_ptson_elpsd < (U1)U1_MAX) {
        u1_s_tripcom_tx_ptson_elpsd++;
    }
    if (u1_s_tripcom_tx_ptson_elpsd == (U1)TRIPCOM_COMTX_PTSON_250MS) {
        (void)Com_TriggerIPDUSend(MSG_MET1S38_TXCH0);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
    u1_t_igsts = u1_g_VehopemdIgnOn();
    if (u1_t_igsts == (U1)TRUE) {
        u1_t_ptssts = u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_OFF);
        if (u1_t_ptssts == (U1)TRUE) {
            u1_s_tripcom_tx_drvcyc <<= TRIPCOM_COMTX_PREVSTS_SFT;
            u1_s_tripcom_tx_drvcyc |= (U1)TRUE;
        }
        else {
            u1_t_drvcyc = u1_s_tripcom_tx_drvcyc & (U1)TRUE;
            u1_s_tripcom_tx_drvcyc = (U1)(u1_s_tripcom_tx_drvcyc << TRIPCOM_COMTX_PREVSTS_SFT) | u1_t_drvcyc;
        }
    }
    else {
        u1_s_tripcom_tx_drvcyc <<= TRIPCOM_COMTX_PREVSTS_SFT;
    }
    u1_s_tripcom_tx_drvcyc &= (U1)TRIPCOM_COMTX_DRVCYC_MSK;
    if (u1_s_tripcom_tx_drvcyc == (U1)TRUE) {
        u1_s_tripcom_tx_ptson_elpsd = (U1)0U;
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxUNIT6(const U1 u1_a_UNIT)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxUNIT6(const U1 u1_a_UNIT)
{
    U1          u1_t_preunit;
    U1          u1_t_unitsndval;
    U1          u1_t_unitdest;

    u1_t_preunit = (U1)0U;
    u1_t_unitsndval  = u1_a_UNIT;
    u1_t_unitdest = u1_g_VardefUnitSlctDstByPid();
    
    (void)Com_ReceiveSignal(ComConf_ComSignal_UNIT_6, &u1_t_preunit);
    if ((u1_t_unitdest == (U1)VDF_UNIT_TYPE_UK) && 
        (u1_a_UNIT     == (U1)TRIPCOM_UNIT_VAL_ELECO_MPKWH)) {
         u1_t_unitsndval = (U1)TRIPCOM_UNIT_VAL_ELECO_MPKWH_UK;
    }

    if (u1_t_preunit != u1_t_unitsndval) {
        (void)Com_SendSignal(ComConf_ComSignal_UNIT_6, &u1_t_unitsndval);
        (void)Com_TriggerIPDUSend(MSG_MET1S38_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxTOEC(const U2 u2_a_VALUE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxTOEC(const U2 u2_a_VALUE)
{

    U2          u2_t_presndval;


    u2_t_presndval = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TO_EC, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_TO_EC, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxM1EC1(const U2 u2_a_VALUE)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxM1EC1(const U2 u2_a_VALUE)
{

    U2          u2_t_prem1ec1;
    U1          u1_t_m1ecr;
    U1          u1_t_sndflg;
    U1          u1_t_prem1ecr;
    U1          u1_t_m1ec_req;


    u1_t_prem1ecr = (U1)FALSE;
    u1_t_sndflg   = (U1)FALSE;
    u1_t_m1ec_req = (U1)FALSE;
    u2_t_prem1ec1 = (U2)0U;
    
    (void)Com_ReceiveSignal(ComConf_ComSignal_M1_EC1,  &u2_t_prem1ec1);
    (void)Com_ReceiveSignal(ComConf_ComSignal_M1_EC_R, &u1_t_prem1ecr);
    
    
    if (u2_t_prem1ec1 != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_M1_EC1, &u2_a_VALUE);
        u1_t_sndflg   = (U1)TRUE;
        u1_t_m1ec_req = (U1)TRUE;
    }
    
    if (u1_s_tripcom_tx_m1ec_timer < (U1)U1_MAX) {
        u1_s_tripcom_tx_m1ec_timer++;
    }
    
    if (u1_s_tripcom_tx_m1ec_timer >= (U1)TRIPCOM_COMTX_TXHLD_2SEC) {
        if (u1_t_prem1ecr != (U1)FALSE) {
            u1_t_m1ecr = (U1)FALSE;
            (void)Com_SendSignal(ComConf_ComSignal_M1_EC_R, &u1_t_m1ecr);
            u1_t_sndflg = (U1)TRUE;
        }
        else if (u1_t_m1ec_req == (U1)TRUE) {
            u1_t_m1ecr = (U1)TRUE;
            (void)Com_SendSignal(ComConf_ComSignal_M1_EC_R, &u1_t_m1ecr);
            u1_t_sndflg = (U1)TRUE;
            u1_s_tripcom_tx_m1ec_timer = (U1)0U;
        }
        else {
            /* Do Nothing */
        }
    }

    if (u1_t_sndflg == (U1)TRUE) {
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }


}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxASEC(const U2 u2_a_VALUE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxASEC(const U2 u2_a_VALUE)
{
    U2          u2_t_presndval;

    u2_t_presndval = (U2)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_AS_EC, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_AS_EC, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxASEVDT(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxASEVDT(const U2 u2_a_VALUE)
{
    U2          u2_t_presndval;

    u2_t_presndval = (U2)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_AS_EVDT, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_AS_EVDT, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxASTOEC(const U2 u2_a_VALUE)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxASTOEC(const U2 u2_a_VALUE)
{
    U2          u2_t_presndval;

    u2_t_presndval = (U2)0U;

    (void)Com_ReceiveSignal(ComConf_ComSignal_AS_TOEC, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_AS_TOEC, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxINEC(const U2 u2_a_VALUE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxINEC(const U2 u2_a_VALUE)
{

    static  const   U2                          u2_s_IN_EC_HIS          = (U2)1U;
    static  const   U2                          u2_s_TXMAX              = (U2)0xFFFCU;
    U2                                          u2_t_presndval;
    U2                                          u2_t_diff;

    u2_t_presndval = (U2)0U;
    (void)Com_ReceiveSignal( ComConf_ComSignal_IN_EC, &u2_t_presndval);

    if ((u2_a_VALUE     <= u2_s_TXMAX) &&
        (u2_t_presndval <= u2_s_TXMAX)) {
        if (u2_t_presndval > u2_a_VALUE) {
            u2_t_diff = u2_t_presndval - u2_a_VALUE;
        }
        else {
            u2_t_diff = u2_a_VALUE - u2_t_presndval;
        }

        if ((u2_t_diff    > u2_s_IN_EC_HIS) ||
            ((u2_a_VALUE == (U2)0U       )  &&
             (u2_t_diff  != (U2)0U       ))) {
            (void)Com_SendSignal(ComConf_ComSignal_IN_EC, &u2_a_VALUE);
            (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
        }
    }
    else {
        if (u2_a_VALUE != u2_t_presndval) {
            (void)Com_SendSignal(ComConf_ComSignal_IN_EC, &u2_a_VALUE);
            (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
        }
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxRANGE(const U2 u2_a_VALUE)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxRANGE(const U2 u2_a_VALUE)
{

    U2          u2_t_sndval;


    u2_t_sndval = (U2)TRIPCOM_CANTX_UNKNOWN;
    (void)Com_SendSignal(ComConf_ComSignal_RANGE, &u2_t_sndval);
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxEVRANGE(const U2 u2_a_VALUE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxEVRANGE(const U2 u2_a_VALUE)
{

    U2          u2_t_presndval;

    u2_t_presndval = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_EV_RANGE, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_EV_RANGE, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S55_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxASSP(const U2 u2_a_VALUE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxASSP(const U2 u2_a_VALUE)
{

    U2          u2_t_presndval;


    u2_t_presndval = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_AS_SP, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_AS_SP, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S38_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxASTM(const U2 u2_a_VALUE)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxASTM(const U2 u2_a_VALUE)
{

    U2          u2_t_presndval;


    u2_t_presndval = (U2)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_AS_TM, &u2_t_presndval);
    if (u2_t_presndval != u2_a_VALUE) {
        (void)Com_SendSignal(ComConf_ComSignal_AS_TM, &u2_a_VALUE);
        (void)Com_TriggerIPDUSend(MSG_MET1S38_TXCH0);
    }
}

/*===================================================================================================================================*/
/* static  void    vd_s_TripcomCfgCanTxEC_SCL(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  void    vd_s_TripcomCfgCanTxEC_SCL(void)
{
    U1          u1_t_sndval;

    u1_t_sndval = u1_CALIB_MCUID0255_PE_EV;
    (void)Com_SendSignal(ComConf_ComSignal_EC_SCL, &u1_t_sndval);
    (void)Com_TriggerIPDUSend(MSG_MET1S38_TXCH0);
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
/*  1.1.0    03/17/2020  YA       Change for 800B CV                                                                                 */
/*  1.1.1    07/28/2020  YA       Initial value transmission change                                                                  */
/*  1.2.0    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    tripcom.c v2.0.1 -> v2.0.2.                                                                        */
/*  2.0.3    10/25/2021  TK       tripcom.c v2.0.2 -> v2.0.3.                                                                        */
/*  2.1.0    01/24/2022  TA(M)    tripcom.c v2.0.3 -> v2.1.0.                                                                        */
/*  2.2.0    02/25/2022  TA(M)    tripcom.c v2.1.0 -> v2.2.0.                                                                        */
/*  2.2.1    04/14/2022  TA(M)    tripcom.c v2.2.0 -> v2.2.1.                                                                        */
/*  2.2.2    07/28/2022  YI       tripcom.c v2.2.1 -> v2.2.2.                                                                        */
/*  2.2.3    08/08/2022  YI       tripcom.c v2.2.2 -> v2.2.3.                                                                        */
/*  2.3.0    01/11/2024  TH       tripcom.c v2.2.3 -> v2.3.0.                                                                        */
/*  2.3.1    10/22/2024  TH       tripcom.c v2.3.0 -> v2.3.1.                                                                        */
/*  2.4.0    02/18/2025  MaO(M)   tripcom.c v2.3.1 -> v2.4.0.                                                                        */
/*  2.4.1    04/22/2025  KM       tripcom.c v2.4.0 -> v2.4.1.                                                                        */
/*  2.5.0    06/23/2025  RS       Change for BEV System_Consideration_2.                                                             */
/*  2.6.0    02/11/2026  DT       Change for BEV FF2.                                                                                */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  178D-1   11/08/2021  YA       Changed for 178D 1A                                                                                */
/*  178D-2   02/17/2022  YS       Changed for MET-M_DM-CSTD-1-02-C-C2-178D-F                                                         */
/*  200D     09/04/2022  SK       Changed for 200D 1A                                                                                */
/*  200D     12/01/2022  HH       Changed for 200D MPT                                                                               */
/*  330D     05/15/2023  HH       Changed for 330D MPT                                                                               */
/*  19PFv3-1 11/06/2023  SH       Changed to read calibration parameter                                                              */
/*  19PFv3-2 02/05/2024  PG       Changed for MET-M_DMEVRNGE-CSTD-1-07-A-C1                                                          */
/*  19PFv3-3 02/07/2024  PG       Changed for MET-M_DMTOEC-CSTD-1-01-E-C0                                                            */
/*  19PFv3-4 02/26/2024  PG       Changed for MET-M_DMM1EC-CSTD-0-02-B-C0                                                            */
/*  19PFv3-5 02/29/2024  PG       Changed for MET-M_DMASFC-CSTD-2-00-A-C0                                                            */
/*  19PFv3-6 03/15/2024  PG       Added vd_s_TripcomCfgCanTxEC_SCL                                                                   */
/*                                Added u1_s_TripcomCfgGetCalibRngeChk                                                               */
/*                                Changed logic in vd_s_TripcomCfgCanTxFC_SCL                                                        */
/*  19PFv3-7 03/19/2024  PG       Changed for MET-M_DMINEC-CSTD-1-01-D-C2                                                            */
/*  19Pfv3-8 04/24/2024  PG       Changed function name u1_s_TripcomCfgGetCalibRngeChk to u1_s_TripcomCfgCalibU1MinMaxChk            */
/*  19PFv3-9 06/27/2024  TN       Delete Calibration Guard Process.                                                                  */
/*  19PFv3-10 04/24/2025 PG       Added vd_s_TripcomCfgCanTxEMGF250ms                                                                */
/*  19PFv3-11 07/17/2025 SK       Added Convert Function of UNIT_6 for 410D MPT                                                      */
/*  BEV3-01   01/20/2026 DR       Added AS_EVDT and AS_TOEC for BEV FF2                                                              */
/*  BEV3-02   02/11/2026 DT       Update TX can frame for BEV FF2 and delete not applied drive moni appli                            */
/*  BEV3-03   02/12/2026 EA       Deleted/Deactivated other than BEV Powertrain processes                                            */
/*  BEV3-04   01/30/2026 YN       Configured for BEVstep3_FF2.(MET-M_DESTVARI-CSTD-0-01)                                             */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * TK   = Takanori Kuno, Denso Techno                                                                                             */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * YS   = Yosuke Sugimoto, Denso Techno                                                                                           */
/*  * SK   = Shintaro Kano, Denso Techno                                                                                             */
/*  * HH   = Hiroki Hara, Denso Techno                                                                                               */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * KM   = Kazuma Miyazawa, Denso Techno                                                                                           */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * DT   = Dj Tutanes, DTPH                                                                                                        */
/*  * EA   = Eunice Avelin, DTPH                                                                                                     */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
