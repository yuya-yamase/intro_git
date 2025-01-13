/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CAN Network Management Wake-up Request Monitor                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_NMWK_C_MAJOR                       (1U)
#define OXCAN_NMWK_C_MINOR                       (0U)
#define OXCAN_NMWK_C_PATCH                       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_nmwk_cfg_private.h"

#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))
#include "Dcm.h"
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_NMWK_C_MAJOR != OXCAN_NMWK_CFG_H_MAJOR) || \
     (OXCAN_NMWK_C_MINOR != OXCAN_NMWK_CFG_H_MINOR) || \
     (OXCAN_NMWK_C_PATCH != OXCAN_NMWK_CFG_H_PATCH))
#error "oxcan_nmwk.c and oxcan_nmwk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_NMWK_NUM_AEVT                      (32U)
#define OXCAN_NMWK_AEVTBIT_TO_RQWK               (0x01U)
#define OXCAN_NMWK_AEVTBIT_TO_AWAK               (0x02U)
#define OXCAN_NMWK_AEVTBIT_RQST                  (0x04U)
#define OXCAN_NMWK_AEVTBIT_RQRI                  (0x08U)
#define OXCAN_NMWK_AEVTBIT_NM_AWAK               (0x10U)

#define OXCAN_NMWK_NUM_ARQSTS                    (4U)
#define OXCAN_NMWK_ARQSTS_WAI_EVT                (0U)
#define OXCAN_NMWK_ARQSTS_TRG_WK                 (1U)
#define OXCAN_NMWK_ARQSTS_SLP_OK                 (2U)
#define OXCAN_NMWK_ARQSTS_SLP_NG                 (3U)

#define OXCAN_NMWK_NUM_ARQACT                    (8U)
#define OXCAN_NMWK_ARQACT_TO_WAI_EVT             (0U)
#define OXCAN_NMWK_ARQACT_TO_WAI_WKF             (1U)
#define OXCAN_NMWK_ARQACT_TO_TRG_WK              (2U)
#define OXCAN_NMWK_ARQACT_TRG_WK                 (3U)
#define OXCAN_NMWK_ARQACT_TO_SLP_OK              (4U)
#define OXCAN_NMWK_ARQACT_SLP_OK                 (5U)
#define OXCAN_NMWK_ARQACT_TO_SLP_NG              (6U)
#define OXCAN_NMWK_ARQACT_SLP_NG                 (7U)

#define OXCAN_NMWK_ARQACT_OPT_TM_INIT            (0x01U)
#define OXCAN_NMWK_ARQACT_OPT_XRQST              (0x02U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2                       u2_s_oxcan_nmwk_xrqst;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_oXCANNmwkApplRqchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk);
static U1      u1_s_oXCANNmwkApplEvtchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk);

#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))
static U2      u2_s_oXCANNmwkDcmAct(void);
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmwkInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmwkInit(void)
{
    U4                 u4_t_subnet;

    u2_s_oxcan_nmwk_xrqst = (U2)0U;

    for(u4_t_subnet = (U4)0U; u4_t_subnet < (U4)u1_g_OXCAN_NMWK_NUM_CH; u4_t_subnet++){

        st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_evtx   = (U2)U2_MAX;
        st_gp_oxcan_nmwk[u4_t_subnet].u1_evtx      = (U1)FALSE;

        st_gp_oxcan_nmwk[u4_t_subnet].u1_applrqsts = (U1)OXCAN_NMWK_ARQSTS_WAI_EVT;
        st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_appl   = (U2)0U;
        st_gp_oxcan_nmwk[u4_t_subnet].u2_applrqbit = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmwkMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmwkMainTask(void)
{
    U4                 u4_t_subnet;
    U2                 u2_t_xrqbit_sys;
    U2                 u2_t_xrqbit_evtx;
    U2                 u2_t_xrqbit_appl;
    U2                 u2_t_xrq_chk;
    U1                 u1_t_nm_awk;

    u2_t_xrqbit_sys = (U2)0U;
    u1_t_nm_awk     = u1_g_oXCANOpemdNmAwkTout(u2_g_OXCAN_NMWK_TIMOUT_OPEMD);
    if(u1_t_nm_awk != (U1)TRUE){
        u2_t_xrqbit_sys = (U2)OXCAN_NMWK_XRQBIT_SYS_IN_RUN;
    }

    u2_t_xrqbit_evtx = (U2)0U;
    u2_t_xrqbit_appl = (U2)0U;
    for(u4_t_subnet = (U4)0U; u4_t_subnet < (U4)u1_g_OXCAN_NMWK_NUM_CH; u4_t_subnet++){

        if(st_gp_oxcan_nmwk[u4_t_subnet].u1_evtx == (U1)TRUE){

            /* ------------------------------------------------------------------------------ */
            /* Attention :                                                                    */
            /* ------------------------------------------------------------------------------ */
            /* Although vd_g_oXCANNmwkMainTask is designed that it's executed prior to        */
            /* applications, st_gp_oxcan_nmwk[x].u2_tm_evtx shall be started at "0" in order  */
            /* to guarantee that duration is always greater than timeout threshold.           */
            /* ------------------------------------------------------------------------------ */
            st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_evtx = (U2)0U;
            st_gp_oxcan_nmwk[u4_t_subnet].u1_evtx = (U1)FALSE;
        }
        else if(st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_evtx < (U2)U2_MAX){
            st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_evtx++;
        }
        else{
            /* no processing */
        }

        if(st_gp_oxcan_nmwk[u4_t_subnet].u2_tm_evtx < st_gp_OXCAN_NMWK_CHK[u4_t_subnet].u2_tout_evtx){
            u2_t_xrqbit_evtx |= st_gp_OXCAN_NMWK_CHK[u4_t_subnet].u2_xrqbit;
        }
        u2_t_xrqbit_appl |= u2_s_oXCANNmwkApplRqchk(&st_gp_OXCAN_NMWK_CHK[u4_t_subnet], &st_gp_oxcan_nmwk[u4_t_subnet]);
    }

    u2_s_oxcan_nmwk_xrqst  = (u2_t_xrqbit_evtx | u2_t_xrqbit_appl) | u2_t_xrqbit_sys;

#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))
    u2_s_oxcan_nmwk_xrqst |= u2_s_oXCANNmwkDcmAct();
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE)) */
    
    for(u4_t_subnet = (U4)0U; u4_t_subnet < (U4)u1_g_OXCAN_NMWK_NUM_CH; u4_t_subnet++){
        u2_t_xrq_chk = u2_s_oxcan_nmwk_xrqst & st_gp_OXCAN_NMWK_CHK[u4_t_subnet].u2_xrq_chk;
        if(u2_t_xrq_chk != (U2)0U){
            (void)ComM_RequestComMode((U1)st_gp_OXCAN_NMWK_CHK[u4_t_subnet].u2_com_awk, (U1)COMM_FULL_COMMUNICATION);
        }
        else{
            (void)ComM_RequestComMode((U1)st_gp_OXCAN_NMWK_CHK[u4_t_subnet].u2_com_awk, (U1)COMM_NO_COMMUNICATION);
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANNmwkEcuShtdwnOk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANNmwkEcuShtdwnOk(void)
{
    U1                 u1_t_ok;

    if(u2_s_oxcan_nmwk_xrqst == (U2)0U){
        u1_t_ok = (U1)TRUE;
    }
    else{
        u1_t_ok = (U1)FALSE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANNmwkRxeByCh(const U1 u1_a_CH)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANNmwkRxeByCh(const U1 u1_a_CH)
{
    U2                 u2_t_bus;
    U1                 u1_t_mod;
    U1                 u1_t_chk;

    U1                 u1_t_rxe;

    u1_t_rxe = (U1)FALSE;
    u1_t_chk = Nm_GetState(u1_a_CH, &u2_t_bus, &u1_t_mod);
    if(u1_t_chk == (U1)E_OK){

        if((u2_t_bus == (U2)NM_STATE_READY_SLEEP     ) ||
           (u2_t_bus == (U2)NM_STATE_NORMAL_OPERATION) ||
           (u2_t_bus == (U2)NM_STATE_REPEAT_MESSAGE  )){

            u1_t_rxe = (U1)TRUE;
        }
    }

    return(u1_t_rxe);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmwkEvtxByCh(const U1 u1_a_CH)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmwkEvtxByCh(const U1 u1_a_CH)
{
    /* ------------------------------------------------------------------------------ */
    /* Attention :                                                                    */
    /* ------------------------------------------------------------------------------ */
    /* vd_g_oXCANNmwkEvtxByCh is being called with Global DI and from,                */
    /* Com_TriggerIPDUSend and Com_SendIPDU.                                          */
    /* ------------------------------------------------------------------------------ */

    U1                 u1_t_nm_subnet;

    if(u1_a_CH < (U1)BSW_COM_CFG_CHNUM){
        u1_t_nm_subnet = u1_gp_OXCAN_NMWK_CH_COM_TO_NM[u1_a_CH];
        if(u1_t_nm_subnet < u1_g_OXCAN_NMWK_NUM_CH){
            st_gp_oxcan_nmwk[u1_t_nm_subnet].u1_evtx = (U1)TRUE;
        }
    }
}
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANNmwkApplRqchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_oXCANNmwkApplRqchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk)
{
    static const U1    u1_sp_OXCAN_NMWK_ARQ_STM[OXCAN_NMWK_NUM_AEVT][OXCAN_NMWK_NUM_ARQSTS] = {
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TRG_WK,     (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_WKF, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TRG_WK,     (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_WKF, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT, (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT},
        {(U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TRG_WK,     (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK },
        {(U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_WAI_WKF, (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK },
        {(U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TRG_WK,     (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK },
        {(U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_WAI_WKF, (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK,  (U1)OXCAN_NMWK_ARQACT_TO_TRG_WK },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_NG    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_NG    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_OK,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_NG,     (U1)OXCAN_NMWK_ARQACT_SLP_NG    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_NG,     (U1)OXCAN_NMWK_ARQACT_SLP_NG    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    },
        {(U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_TO_SLP_NG,  (U1)OXCAN_NMWK_ARQACT_SLP_OK,     (U1)OXCAN_NMWK_ARQACT_SLP_OK    }
    };

    static const U1    u1_sp_OXCAN_NMWK_ARQACT_NEXT[OXCAN_NMWK_NUM_ARQACT] = {
        (U1)OXCAN_NMWK_ARQSTS_WAI_EVT, /* OXCAN_NMWK_ARQACT_TO_WAI_EVT */
        (U1)OXCAN_NMWK_ARQSTS_WAI_EVT, /* OXCAN_NMWK_ARQACT_TO_WAI_WKF */
        (U1)OXCAN_NMWK_ARQSTS_TRG_WK,  /* OXCAN_NMWK_ARQACT_TO_TRG_WK  */
        (U1)OXCAN_NMWK_ARQSTS_TRG_WK,  /* OXCAN_NMWK_ARQACT_TRG_WK     */
        (U1)OXCAN_NMWK_ARQSTS_SLP_OK,  /* OXCAN_NMWK_ARQACT_TO_SLP_OK  */
        (U1)OXCAN_NMWK_ARQSTS_SLP_OK,  /* OXCAN_NMWK_ARQACT_SLP_OK     */
        (U1)OXCAN_NMWK_ARQSTS_SLP_NG,  /* OXCAN_NMWK_ARQACT_TO_SLP_NG  */
        (U1)OXCAN_NMWK_ARQSTS_SLP_NG   /* OXCAN_NMWK_ARQACT_SLP_NG     */
    };

    static const U1    u1_sp_OXCAN_NMWK_ARQACT_OPTBIT[OXCAN_NMWK_NUM_ARQACT] = {
        (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT,                                   /* OXCAN_NMWK_ARQACT_TO_WAI_EVT */
        (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT,                                   /* OXCAN_NMWK_ARQACT_TO_WAI_WKF */
        (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT | (U1)OXCAN_NMWK_ARQACT_OPT_XRQST, /* OXCAN_NMWK_ARQACT_TO_TRG_WK  */
                                            (U1)OXCAN_NMWK_ARQACT_OPT_XRQST, /* OXCAN_NMWK_ARQACT_TRG_WK     */
        (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT,                                   /* OXCAN_NMWK_ARQACT_TO_SLP_OK  */
        (U1)0x00U,                                                           /* OXCAN_NMWK_ARQACT_SLP_OK     */
        (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT | (U1)OXCAN_NMWK_ARQACT_OPT_XRQST, /* OXCAN_NMWK_ARQACT_TO_SLP_NG  */
                                            (U1)OXCAN_NMWK_ARQACT_OPT_XRQST  /* OXCAN_NMWK_ARQACT_SLP_NG     */
    };

    U2                 u2_t_xrqbit;
    U1                 u1_t_evtbit;
    U1                 u1_t_act;
    U1                 u1_t_optbit;

    u1_t_evtbit = u1_s_oXCANNmwkApplEvtchk(st_ap_CHK, st_ap_nmwk);

    u1_t_act = (U1)OXCAN_NMWK_ARQACT_TO_WAI_EVT;
    if(st_ap_nmwk->u1_applrqsts < (U1)OXCAN_NMWK_NUM_ARQSTS){
        u1_t_act = u1_sp_OXCAN_NMWK_ARQ_STM[u1_t_evtbit][st_ap_nmwk->u1_applrqsts];
    }

    if((u1_t_act               == (U1)OXCAN_NMWK_ARQACT_TO_WAI_WKF) &&
       (st_ap_CHK->fp_vd_WKRTO != vdp_PTR_NA                      )){
        (st_ap_CHK->fp_vd_WKRTO)();
    }

    st_ap_nmwk->u1_applrqsts = u1_sp_OXCAN_NMWK_ARQACT_NEXT[u1_t_act];
    u1_t_optbit = u1_sp_OXCAN_NMWK_ARQACT_OPTBIT[u1_t_act] & (U1)OXCAN_NMWK_ARQACT_OPT_TM_INIT;
    if(u1_t_optbit != (U1)0U){
        st_ap_nmwk->u2_tm_appl = (U2)0U;
    }

    u2_t_xrqbit = (U2)0U;
    u1_t_optbit = u1_sp_OXCAN_NMWK_ARQACT_OPTBIT[u1_t_act] & (U1)OXCAN_NMWK_ARQACT_OPT_XRQST;
    if(u1_t_optbit != (U1)0U){
        u2_t_xrqbit = st_ap_CHK->u2_xrqbit;
    }

    return(u2_t_xrqbit);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXCANNmwkApplEvtchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         AppAwake Event Pattern                                                                                           */
/*===================================================================================================================================*/
static U1      u1_s_oXCANNmwkApplEvtchk(const ST_OXCAN_NMWK_CHK * st_ap_CHK, ST_OXCAN_NMWK * st_ap_nmwk)
{
    U2                 u2_t_buswake_sts;
    U2                 u2_t_applrqst;
    U2                 u2_t_rqstevt;

    U1                 u1_t_evtbit;
    U1                 u1_t_nm_mod;
    U1                 u1_t_nm_chk;

    if(st_ap_nmwk->u2_tm_appl < (U2)U2_MAX){
        st_ap_nmwk->u2_tm_appl++;
    }

    u1_t_evtbit = (U1)0U;
    if(st_ap_nmwk->u2_tm_appl >= u2_g_OXCAN_NMWK_TIMOUT_ARQWK){
        u1_t_evtbit |= (U1)OXCAN_NMWK_AEVTBIT_TO_RQWK;
    }

#if (OXCAN_APP_SLPNG_TOE == 1U)
    if(st_ap_nmwk->u2_tm_appl >= st_ap_CHK->u2_tout_awak){
        u1_t_evtbit |= (U1)OXCAN_NMWK_AEVTBIT_TO_AWAK;
    }
#endif /* #if (OXCAN_APP_SLPNG_TOE == 1U) */

    if(st_ap_CHK->fp_u2_ARQST != vdp_PTR_NA){
        u2_t_applrqst = (st_ap_CHK->fp_u2_ARQST)();
        if(u2_t_applrqst != (U2)0U){
            u1_t_evtbit |= (U1)OXCAN_NMWK_AEVTBIT_RQST;
        }
        u2_t_rqstevt = (u2_t_applrqst ^ st_ap_nmwk->u2_applrqbit) & u2_t_applrqst;
        if(u2_t_rqstevt != (U2)0U){
            u1_t_evtbit |= (U1)OXCAN_NMWK_AEVTBIT_RQRI;
        }
    }
    else{
        u2_t_applrqst = (U2)0U;
    }
    st_ap_nmwk->u2_applrqbit = u2_t_applrqst;

    u1_t_nm_chk = Nm_GetState((U1)st_ap_CHK->u2_nm_netid, &u2_t_buswake_sts, &u1_t_nm_mod);
    if(u1_t_nm_chk == (U1)E_OK){

        if((u2_t_buswake_sts == (U2)NM_STATE_READY_SLEEP     ) ||
           (u2_t_buswake_sts == (U2)NM_STATE_NORMAL_OPERATION) ||
           (u2_t_buswake_sts == (U2)NM_STATE_REPEAT_MESSAGE  )){
            u1_t_evtbit |= (U1)OXCAN_NMWK_AEVTBIT_NM_AWAK;
        }
    }

    return(u1_t_evtbit);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */



#if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE))



/* --------------------------------------------------------------------------------------------------------------------------------- */
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANNmwkDcmAct(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         AppAwake Event Pattern                                                                                           */
/*===================================================================================================================================*/
static U2      u2_s_oXCANNmwkDcmAct(void)
{
    U2                 u2_t_xrqbit;
    U1                 u1_t_act;

    u1_t_act = Dcm_GetBusSleepPermission((U1)TRUE);
    if(u1_t_act == (U1)FALSE){
        u2_t_xrqbit = u2_g_OXCAN_NMWK_XRQST_BY_DCM;
    }
    else{
        u2_t_xrqbit = (U2)0U;
    }

    return(u2_t_xrqbit);
}
/* --------------------------------------------------------------------------------------------------------------------------------- */



#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_DCM)) && (BSW_BSWM_CS_CFG_FUNC_DCM == BSW_USE)) */



/* --------------------------------------------------------------------------------------------------------------------------------- */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tycan_nmwk -> oxcan_nmwk.    */
/*  1.0.1     9/27/2022  TM       Fixed QAC issue.                                                                                   */
/*  1.0.2     1/25/2023  TM       Changed to be able to select apply sleep NG timeout enable or not.                                 */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/


