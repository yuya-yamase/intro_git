/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Digital Input Filter                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_C_MAJOR                       (1)
#define IOHW_DIFLT_C_MINOR                       (4)
#define IOHW_DIFLT_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "iohw_diflt_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IOHW_DIFLT_C_MAJOR != IOHW_DIFLT_H_MAJOR) || \
     (IOHW_DIFLT_C_MINOR != IOHW_DIFLT_H_MINOR) || \
     (IOHW_DIFLT_C_PATCH != IOHW_DIFLT_H_PATCH))
#error "iohw_diflt.c and iohw_diflt.h : source and header files are inconsistent!"
#endif

#if ((IOHW_DIFLT_C_MAJOR != IOHW_DIFLT_CFG_H_MAJOR) || \
     (IOHW_DIFLT_C_MINOR != IOHW_DIFLT_CFG_H_MINOR) || \
     (IOHW_DIFLT_C_PATCH != IOHW_DIFLT_CFG_H_PATCH))
#error "iohw_diflt.c and iohw_diflt_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_NUM_FLTR_STS                  (4U)
#define IOHW_DIFLT_STS_UNKNWN                    (0U)
#define IOHW_DIFLT_STS_DLYMSK                    (1U)
#define IOHW_DIFLT_STS_INIT                      (2U)
#define IOHW_DIFLT_STS_NRML                      (3U)

#define IOHW_DIFLT_NUM_STSBIT                    (32U)
#define IOHW_DIFLT_STSBIT_DLYMSK_ENA             (0x10U) /* equal to IOHW_DILFT_CTRLOPT_DLYMSK_ENA */
#define IOHW_DIFLT_STSBIT_INIT_ENA               (0x08U) /* equal to IOHW_DILFT_CTRLOPT_INIT_ENA   */
#define IOHW_DIFLT_STSBIT_DLYMSK_CMPLT           (0x04U)
#define IOHW_DIFLT_STSBIT_SMPLG_CYCLD            (0x02U)
#define IOHW_DIFLT_STSBIT_VALID_FULL             (0x01U)

#define IOHW_DIFLT_STSBIT_CTRLOPT                (0x18U)

#if ((IOHW_DIFLT_STSBIT_DLYMSK_ENA != IOHW_DILFT_CTRLOPT_DLYMSK_ENA) || \
     (IOHW_DIFLT_STSBIT_INIT_ENA   != IOHW_DILFT_CTRLOPT_INIT_ENA  ))
#error "iohw_diflt.c and iohw_diflt_cfg_private.h : IOHW_DILFT_CTRLOPT_XXX prohibit to be modified!"
#endif

#define IOHW_DIFLT_NUM_ACT                       (12U)
#define IOHW_DIFLT_ACT_TO_UNKNWN                 (0U)
#define IOHW_DIFLT_ACT_TO_DLYMSK                 (1U)
#define IOHW_DIFLT_ACT_DLYMSK_CYCL               (2U)
#define IOHW_DIFLT_ACT_DLYMSK                    (3U)
#define IOHW_DIFLT_ACT_TO_INIT                   (4U)
#define IOHW_DIFLT_ACT_INIT_CYCL                 (5U)
#define IOHW_DIFLT_ACT_INIT_DLYD                 (6U)
#define IOHW_DIFLT_ACT_INIT                      (7U)
#define IOHW_DIFLT_ACT_TO_NRML_INST              (8U)
#define IOHW_DIFLT_ACT_TO_NRML                   (9U)
#define IOHW_DIFLT_ACT_NRML_CYCL                 (10U)
#define IOHW_DIFLT_ACT_NRML                      (11U)

#define IOHW_DIFLT_ACTBIT_TIMER_UPDT             (0x18U)
#define IOHW_DIFLT_ACTBIT_TIMER_DLYD             (0x10U)
#define IOHW_DIFLT_ACTBIT_TIMER_RSTA             (0x08U)
#define IOHW_DIFLT_ACTBIT_SMPLD_UPDT             (0x04U)
#define IOHW_DIFLT_ACTBIT_FLTRD_UPDT             (0x02U)
#define IOHW_DIFLT_ACTBIT_SMPLG_RSTA             (0x01U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_FLTRD_LSB_VALID               (16U)
#define IOHW_DIFLT_SMPLG_CYCL_MIN                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2      u2_act;
    U2      u2_sgnlbit;
    U2      u2_port;
    U2      u2_inst;
    U2      u2_cycle;
}ST_IOHW_DIACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_IoHwDifltSgnlUpdt(const U2 * u2_ap_DI_INST, const U2 u2_a_SMPLGCHK, U4 * u4_ap_fltrd);
static U2      u2_s_IoHwDifltTimelpsdchk(const ST_IOHW_DIFLTR * st_ap_FLTR, ST_IOHW_DICTRL * st_ap_ctrl);
static void    vd_s_IoHwDifltCtrlAct(const ST_IOHW_DIACT * st_ap_ACT, ST_IOHW_DICTRL * st_ap_ctrl, U4 * u4_ap_fltrd);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_IoHwDifltInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwDifltInit(void)
{
    U2                         u2_t_lpcnt;

    for(u2_t_lpcnt = (U2)0U; u2_t_lpcnt < u2_g_IOHW_DIFLT_NUM_DIPORT; u2_t_lpcnt++){
        u4_gp_iohw_diflt_fltrd[u2_t_lpcnt] = (U4)0x00000000U;  /* array size = # of digital port */
        u2_gp_iohw_diflt_smpld[u2_t_lpcnt] = (U2)0x0000U;      /* array size = # of digital port */
    }

    for(u2_t_lpcnt = (U2)0U; u2_t_lpcnt < u2_g_IOHW_DIFLT_NUM_DISGNL; u2_t_lpcnt++){
        st_gp_iohw_diflt_ctrl[u2_t_lpcnt].u2_tmelpsd  = (U2)0U;
        st_gp_iohw_diflt_ctrl[u2_t_lpcnt].u1_validcnt = (U1)0U;
        st_gp_iohw_diflt_ctrl[u2_t_lpcnt].u1_fltrsts  = (U1)IOHW_DIFLT_STS_UNKNWN;
    }

    vd_g_IoHwDifltCfgInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwDifltSgnlInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwDifltSgnlInit(void)
{
    const ST_IOHW_DIFLTR *     st_tp_FLTR;

    U4                         u4_tp_di_fltrd[IOHW_DIFLT_DIPORT_NUM_INST];
    U4                         u4_t_fltrd;

    U2                         u2_tp_di_inst[IOHW_DIFLT_DIPORT_NUM_INST];

    U2                         u2_t_sgnlcnt;
    U2                         u2_t_evtchk;
    U2                         u2_t_smplgchk;
    U2                         u2_t_sgnlbit;
    U2                         u2_t_fltr;
    U2                         u2_t_port;
    U2                         u2_t_inst;
    U2                         u2_t_ctrlopt;

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* In order to keep coherency between filtered signal and filter status (valid/invalid,  */
    /* the copy of u4_gp_iohw_diflt_fltrd[], "u4_tp_di_fltrd[]", are used to update filterd  */
    /* because the data structure of u4_gp_iohw_diflt_fltrd[] is bitfield and the variable   */
    /* is read/modified/written to update the value.                                         */
    /* ------------------------------------------------------------------------------------- */
    vd_g_MemcpyU4(&u4_tp_di_fltrd[0], &u4_gp_iohw_diflt_fltrd[0], (U4)u2_g_IOHW_DIFLT_NUM_DIPORT);

    vd_g_IoHwDifltCfgRead(&u2_tp_di_inst[0]);

    u2_t_smplgchk = u2_g_IoHwDifltCfgSmplgchk();

    for(u2_t_sgnlcnt = (U2)0; u2_t_sgnlcnt < u2_g_IOHW_DIFLT_NUM_DISGNL; u2_t_sgnlcnt++){

        u2_t_fltr    = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_fltr;
        st_tp_FLTR   = &st_gp_IOHW_DIFLT_FLTR[u2_t_fltr];

        u2_t_evtchk = st_tp_FLTR->u2_smplgchk & u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT;
        if(u2_t_evtchk != (U2)0U){

            u2_t_evtchk = u2_t_smplgchk & st_tp_FLTR->u2_smplgchk;
            if(u2_t_evtchk != st_tp_FLTR->u2_smplgena){

                st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u2_tmelpsd  = (U2)0U;
                st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt = (U1)0U;
                st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts  = (U1)IOHW_DIFLT_STS_UNKNWN;

                u2_t_port    = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_port;
                u4_t_fltrd   = (U4)st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_sgnlbit << IOHW_DIFLT_FLTRD_LSB_VALID;
                u4_tp_di_fltrd[u2_t_port] &= ((U4)U4_MAX ^ u4_t_fltrd); /* invalid */
            }
            else if(st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts == (U1)IOHW_DIFLT_STS_UNKNWN){

                u2_t_sgnlbit = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_sgnlbit;
                u2_t_port    = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_port;

                u2_t_inst = u2_tp_di_inst[u2_t_port] & u2_t_sgnlbit;
                u2_gp_iohw_diflt_smpld[u2_t_port] &= ((U2)U2_MAX ^ u2_t_sgnlbit);
                u2_gp_iohw_diflt_smpld[u2_t_port] |= u2_t_inst;

                st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u2_tmelpsd = (U2)0U;
                u2_t_ctrlopt = st_tp_FLTR->u2_ctrlopt & (U2)IOHW_DIFLT_STSBIT_CTRLOPT;
                if(u2_t_ctrlopt == (U2)0U){ /* To Normal */

                    u4_t_fltrd                 = (U4)u2_t_sgnlbit << IOHW_DIFLT_FLTRD_LSB_VALID;
                    u4_tp_di_fltrd[u2_t_port] &= ((U4)U4_MAX ^ (u4_t_fltrd | (U4)u2_t_sgnlbit));
                    u4_t_fltrd                |= (U4)u2_t_inst;
                    u4_tp_di_fltrd[u2_t_port] |= u4_t_fltrd;

                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt = (U1)1U;
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts  = (U1)IOHW_DIFLT_STS_NRML;
                }
                else if(u2_t_ctrlopt == (U2)IOHW_DILFT_CTRLOPT_INIT_ENA){

                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt = (U1)1U;
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts  = (U1)IOHW_DIFLT_STS_INIT;
                }
                else{
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt = (U1)1U;
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts  = (U1)IOHW_DIFLT_STS_DLYMSK;
                }
            }
            else{
                /* do nothing */
            }
        } /* st_tp_FLTR->u2_smplgchk & u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT != (U2)                 */
    } /* for(u2_t_sgnlcnt = (U2)0; u2_t_sgnlcnt < u2_g_IOHW_DIFLT_NUM_DISGNL; u2_t_sgnlcnt++){ */

    vd_g_MemcpyU4(&u4_gp_iohw_diflt_fltrd[0], &u4_tp_di_fltrd[0], (U4)u2_g_IOHW_DIFLT_NUM_DIPORT);
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwDifltMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwDifltMainTask(void)
{
    U4                         u4_tp_di_fltrd[IOHW_DIFLT_DIPORT_NUM_INST];
    U2                         u2_tp_di_inst[IOHW_DIFLT_DIPORT_NUM_INST];
    U2                         u2_t_smplgchk;

    /* ------------------------------------------------------------------------------------- */
    /* Attention :                                                                           */
    /* In order to keep coherency between filtered signal and filter status (valid/invalid,  */
    /* the copy of u4_gp_iohw_diflt_fltrd[], "u4_tp_di_fltrd[]", are used to update filterd  */
    /* because the data structure of u4_gp_iohw_diflt_fltrd[] is bitfield and the variable   */
    /* is read/modified/written to update the value.                                         */
    /* ------------------------------------------------------------------------------------- */
    vd_g_MemcpyU4(&u4_tp_di_fltrd[0], &u4_gp_iohw_diflt_fltrd[0], (U4)u2_g_IOHW_DIFLT_NUM_DIPORT);

    u2_t_smplgchk = u2_g_IoHwDifltCfgSmplgchk();
    vd_g_IoHwDifltCfgRead(&u2_tp_di_inst[0]);

    vd_s_IoHwDifltSgnlUpdt(&u2_tp_di_inst[0], u2_t_smplgchk, &u4_tp_di_fltrd[0]);

    vd_g_MemcpyU4(&u4_gp_iohw_diflt_fltrd[0], &u4_tp_di_fltrd[0], (U4)u2_g_IOHW_DIFLT_NUM_DIPORT);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IoHwDifltSgnlUpdt(const U2 * u2_ap_DI_INST, const U2 u2_a_SMPLGCHK, U4 * u4_ap_fltrd)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_IoHwDifltSgnlUpdt(const U2 * u2_ap_DI_INST, const U2 u2_a_SMPLGCHK, U4 * u4_ap_fltrd)
{
    static const U1            u1_sp_IOHW_DIFLT_STM[IOHW_DIFLT_NUM_STSBIT][IOHW_DIFLT_NUM_FLTR_STS] = {
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_INIT,      (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_INIT_DLYD,    (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_INIT_DLYD,    (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML_INST, (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK,       (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK_CYCL,  (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_DLYMSK_CYCL,  (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML  },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_INIT_DLYD,    (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_INIT_DLYD,    (U1)IOHW_DIFLT_ACT_INIT,         (U1)IOHW_DIFLT_ACT_NRML     },
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_INIT_CYCL,    (U1)IOHW_DIFLT_ACT_NRML_CYCL},
        {(U1)IOHW_DIFLT_ACT_TO_DLYMSK,    (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML,      (U1)IOHW_DIFLT_ACT_TO_NRML  }
    };

    const ST_IOHW_DIFLTR *     st_tp_FLTR;
    ST_IOHW_DIACT              st_t_di_act;

    U2                         u2_t_sgnlcnt;

    U2                         u2_t_fltr;
    U2                         u2_t_stsbit;
    U2                         u2_t_jdgbit;
    U2                         u2_t_smpld;

    U1                         u1_t_valid_thrsld;
    U1                         u1_t_fltrsts;

    for(u2_t_sgnlcnt = (U2)0U; u2_t_sgnlcnt < u2_g_IOHW_DIFLT_NUM_DISGNL; u2_t_sgnlcnt++){

        st_t_di_act.u2_act     = (U2)IOHW_DIFLT_ACT_TO_UNKNWN;
        st_t_di_act.u2_sgnlbit = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_sgnlbit;
        st_t_di_act.u2_port    = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_port;
        u2_t_fltr              = st_gp_IOHW_DIFLT_DISGNL[u2_t_sgnlcnt].u2_fltr;
        st_tp_FLTR             = &st_gp_IOHW_DIFLT_FLTR[u2_t_fltr];
        st_t_di_act.u2_inst    = u2_ap_DI_INST[st_t_di_act.u2_port] & st_t_di_act.u2_sgnlbit;
        st_t_di_act.u2_cycle   = st_tp_FLTR->u2_cycle;

        /* Sampling Condition Check */
        u2_t_jdgbit  = u2_a_SMPLGCHK & st_tp_FLTR->u2_smplgchk;
        u1_t_fltrsts = st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_fltrsts;
        if((u2_t_jdgbit  == st_tp_FLTR->u2_smplgena    ) &&
           (u1_t_fltrsts  < (U1)IOHW_DIFLT_NUM_FLTR_STS)){

            u2_t_stsbit  = st_tp_FLTR->u2_ctrlopt & (U2)IOHW_DIFLT_STSBIT_CTRLOPT;
            u2_t_stsbit |= u2_s_IoHwDifltTimelpsdchk(st_tp_FLTR, &st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt]);
            u2_t_jdgbit  = u2_t_stsbit & (U2)IOHW_DIFLT_STSBIT_SMPLG_CYCLD;
            if(u2_t_jdgbit != (U2)0U){

                u2_t_smpld = u2_gp_iohw_diflt_smpld[st_t_di_act.u2_port] & st_t_di_act.u2_sgnlbit;
                if(st_t_di_act.u2_inst != u2_t_smpld){
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt = (U1)1U;
                }
                else if(st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt < (U1)U1_MAX){
                    st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt++;
                }
                else{
                    /* do nothing */
                }

                if(u1_t_fltrsts == (U1)IOHW_DIFLT_STS_NRML){
                    u1_t_valid_thrsld = st_tp_FLTR->u1_valid_nrml;
                }
                else{
                    u1_t_valid_thrsld = st_tp_FLTR->u1_valid_init;
                }
                if(st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt].u1_validcnt >= u1_t_valid_thrsld){
                    u2_t_stsbit |= (U2)IOHW_DIFLT_STSBIT_VALID_FULL;
                }
            }
            st_t_di_act.u2_act = (U2)u1_sp_IOHW_DIFLT_STM[u2_t_stsbit][u1_t_fltrsts];
        }
        vd_s_IoHwDifltCtrlAct(&st_t_di_act, &st_gp_iohw_diflt_ctrl[u2_t_sgnlcnt], u4_ap_fltrd);
    }
}
/*===================================================================================================================================*/
/*  static U2      u2_s_IoHwDifltTimelpsdchk(const ST_IOHW_DIFLTR * st_ap_FLTR, ST_IOHW_DICTRL * st_ap_ctrl)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static U2      u2_s_IoHwDifltTimelpsdchk(const ST_IOHW_DIFLTR * st_ap_FLTR, ST_IOHW_DICTRL * st_ap_ctrl)
{
    U2                         u2_t_stsbit;
    U2                         u2_t_cycled;

    u2_t_stsbit = (U2)0U;
    if(st_ap_ctrl->u2_tmelpsd < (U2)U2_MAX){
        st_ap_ctrl->u2_tmelpsd++;
    }

    if(st_ap_ctrl->u2_tmelpsd >= st_ap_FLTR->u2_dlymask){
        u2_t_stsbit |= (U2)IOHW_DIFLT_STSBIT_DLYMSK_CMPLT;
    }

    if(st_ap_FLTR->u2_cycle <= (U2)IOHW_DIFLT_SMPLG_CYCL_MIN){   /* div by zero protection */
        u2_t_stsbit |= (U2)IOHW_DIFLT_STSBIT_SMPLG_CYCLD;
    }
    else{ 
        u2_t_cycled = st_ap_ctrl->u2_tmelpsd % st_ap_FLTR->u2_cycle;
        if(u2_t_cycled == (U2)0U){
            u2_t_stsbit |= (U2)IOHW_DIFLT_STSBIT_SMPLG_CYCLD;
        }
    }

    return(u2_t_stsbit);
}
/*===================================================================================================================================*/
/*  static void    vd_s_IoHwDifltCtrlAct(const ST_IOHW_DIACT * st_ap_ACT, ST_IOHW_DICTRL * st_ap_ctrl, U4 * u4_ap_fltrd)             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_IoHwDifltCtrlAct(const ST_IOHW_DIACT * st_ap_ACT, ST_IOHW_DICTRL * st_ap_ctrl, U4 * u4_ap_fltrd)
{
    static const U1            u1_sp_IOHW_DIFLT_NEXT[IOHW_DIFLT_NUM_ACT] = {
        (U1)IOHW_DIFLT_STS_UNKNWN,  /* IOHW_DIFLT_ACT_TO_UNKNWN    (0)  */
        (U1)IOHW_DIFLT_STS_DLYMSK,  /* IOHW_DIFLT_ACT_TO_DLYMSK    (1)  */
        (U1)IOHW_DIFLT_STS_DLYMSK,  /* IOHW_DIFLT_ACT_DLYMSK_CYCL  (2)  */
        (U1)IOHW_DIFLT_STS_DLYMSK,  /* IOHW_DIFLT_ACT_DLYMSK       (3)  */
        (U1)IOHW_DIFLT_STS_INIT,    /* IOHW_DIFLT_ACT_TO_INIT      (4)  */
        (U1)IOHW_DIFLT_STS_INIT,    /* IOHW_DIFLT_ACT_INIT_CYCL    (5)  */
        (U1)IOHW_DIFLT_STS_INIT,    /* IOHW_DIFLT_ACT_INIT_DLYD    (6)  */
        (U1)IOHW_DIFLT_STS_INIT,    /* IOHW_DIFLT_ACT_INIT         (7)  */
        (U1)IOHW_DIFLT_STS_NRML,    /* IOHW_DIFLT_ACT_TO_NRML_INST (8)  */
        (U1)IOHW_DIFLT_STS_NRML,    /* IOHW_DIFLT_ACT_TO_NRML      (9)  */
        (U1)IOHW_DIFLT_STS_NRML,    /* IOHW_DIFLT_ACT_NRML_CYCL    (10) */
        (U1)IOHW_DIFLT_STS_NRML     /* IOHW_DIFLT_ACT_NRML         (11) */
    };

    static const U1            u1_sp_IOHW_DIFLT_ACTBIT[IOHW_DIFLT_NUM_ACT] = {
        (U1)0x00U,                  /* IOHW_DIFLT_ACT_TO_UNKNWN    (0)  */
        (U1)0x0DU,                  /* IOHW_DIFLT_ACT_TO_DLYMSK    (1)  */
        (U1)0x04U,                  /* IOHW_DIFLT_ACT_DLYMSK_CYCL  (2)  */
        (U1)0x00U,                  /* IOHW_DIFLT_ACT_DLYMSK       (3)  */
        (U1)0x0DU,                  /* IOHW_DIFLT_ACT_TO_INIT      (4)  */
        (U1)0x0CU,                  /* IOHW_DIFLT_ACT_INIT_CYCL    (5)  */
        (U1)0x10U,                  /* IOHW_DIFLT_ACT_INIT_DLYD    (6)  */
        (U1)0x00U,                  /* IOHW_DIFLT_ACT_INIT         (7)  */
        (U1)0x0FU,                  /* IOHW_DIFLT_ACT_TO_NRML_INST (8)  */
        (U1)0x0EU,                  /* IOHW_DIFLT_ACT_TO_NRML      (9)  */
        (U1)0x0CU,                  /* IOHW_DIFLT_ACT_NRML_CYCL    (10) */
        (U1)0x00U                   /* IOHW_DIFLT_ACT_NRML         (11) */
    };

    U4                         u4_t_fltrd;

    U1                         u1_t_next;
    U1                         u1_t_actbit;
    U1                         u1_t_jdgbit;

    u1_t_next   = u1_sp_IOHW_DIFLT_NEXT[st_ap_ACT->u2_act];
    u1_t_actbit = u1_sp_IOHW_DIFLT_ACTBIT[st_ap_ACT->u2_act];

    u1_t_jdgbit = u1_t_actbit & (U1)IOHW_DIFLT_ACTBIT_TIMER_UPDT;
    if(u1_t_jdgbit == (U1)IOHW_DIFLT_ACTBIT_TIMER_RSTA){
        st_ap_ctrl->u2_tmelpsd  = (U2)0U;
    }
    else if(u1_t_jdgbit == (U1)IOHW_DIFLT_ACTBIT_TIMER_DLYD){

        if(st_ap_ACT->u2_cycle <= (U2)IOHW_DIFLT_SMPLG_CYCL_MIN){ /* div by zero protection */
            st_ap_ctrl->u2_tmelpsd = (U2)0U;
        }
        else{
            st_ap_ctrl->u2_tmelpsd = st_ap_ctrl->u2_tmelpsd % st_ap_ACT->u2_cycle;
        }
    }
    else{
        /* do nothing */
    }

    u1_t_jdgbit = u1_t_actbit & (U1)IOHW_DIFLT_ACTBIT_SMPLD_UPDT;
    if(u1_t_jdgbit != (U1)0U){
        u2_gp_iohw_diflt_smpld[st_ap_ACT->u2_port] &= ((U2)U2_MAX ^ st_ap_ACT->u2_sgnlbit);
        u2_gp_iohw_diflt_smpld[st_ap_ACT->u2_port] |= st_ap_ACT->u2_inst;
    }
    
    u1_t_jdgbit = u1_t_actbit & (U1)IOHW_DIFLT_ACTBIT_FLTRD_UPDT;
    if(u1_t_next != (U1)IOHW_DIFLT_STS_NRML){
        u4_t_fltrd = (U4)st_ap_ACT->u2_sgnlbit << IOHW_DIFLT_FLTRD_LSB_VALID;
        u4_ap_fltrd[st_ap_ACT->u2_port] &= ((U4)U4_MAX ^ u4_t_fltrd);
    }
    else if(u1_t_jdgbit != (U1)0U){
        u4_t_fltrd = (U4)st_ap_ACT->u2_sgnlbit << IOHW_DIFLT_FLTRD_LSB_VALID;
        u4_ap_fltrd[st_ap_ACT->u2_port] &= ((U4)U4_MAX ^ (u4_t_fltrd | (U4)st_ap_ACT->u2_sgnlbit));
        u4_ap_fltrd[st_ap_ACT->u2_port] |= (u4_t_fltrd | (U4)st_ap_ACT->u2_inst);
    }
    else{
        /* do nothing */
    }
    st_ap_ctrl->u1_fltrsts = u1_t_next;

    u1_t_jdgbit = u1_t_actbit & (U1)IOHW_DIFLT_ACTBIT_SMPLG_RSTA;
    if(u1_t_jdgbit != (U1)0U){
        st_ap_ctrl->u1_validcnt = (U1)1U;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwDifltSgnl(const U2 u2_a_DISGNL, U2 * u2_ap_sgnl)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_IoHwDifltSgnl(const U2 u2_a_DISGNL, U2 * u2_ap_sgnl)
{
    U4                         u4_t_fltrd;

    U2                         u2_t_sgnlbit;
    U2                         u2_t_port;
    U2                         u2_t_validchk;

    U1                         u1_t_valid;

    u1_t_valid = (U1)FALSE;
    if(u2_a_DISGNL < u2_g_IOHW_DIFLT_NUM_DISGNL){

        u2_t_sgnlbit  = st_gp_IOHW_DIFLT_DISGNL[u2_a_DISGNL].u2_sgnlbit;
        u2_t_port     = st_gp_IOHW_DIFLT_DISGNL[u2_a_DISGNL].u2_port;
        u4_t_fltrd    = u4_gp_iohw_diflt_fltrd[u2_t_port];
        u2_t_validchk = (U2)(u4_t_fltrd >> IOHW_DIFLT_FLTRD_LSB_VALID) & u2_t_sgnlbit;
        if(u2_t_validchk == u2_t_sgnlbit){
            if(u2_ap_sgnl != vdp_PTR_NA){
                (*u2_ap_sgnl) = (U2)u4_t_fltrd & u2_t_sgnlbit;
            }
            u1_t_valid = (U1)TRUE;
        }
    }

    return(u1_t_valid);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwDifltSwitch(const U2 u2_a_DISGNL)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_IoHwDifltSwitch(const U2 u2_a_DISGNL)
{
    U4                         u4_t_fltrd;

    U2                         u2_t_sgnlbit;
    U2                         u2_t_sgnlact;
    U2                         u2_t_port;
    U2                         u2_t_validchk;

    U1                         u1_t_switch;

    u1_t_switch = (U1)IOHW_DIFLT_SWITCH_UNKNWN;
    if(u2_a_DISGNL < u2_g_IOHW_DIFLT_NUM_DISGNL){

        u2_t_sgnlbit   = st_gp_IOHW_DIFLT_DISGNL[u2_a_DISGNL].u2_sgnlbit;
        u2_t_sgnlact   = st_gp_IOHW_DIFLT_DISGNL[u2_a_DISGNL].u2_sgnlact;
        u2_t_port      = st_gp_IOHW_DIFLT_DISGNL[u2_a_DISGNL].u2_port;
        u4_t_fltrd     = u4_gp_iohw_diflt_fltrd[u2_t_port];
        u2_t_validchk  = (U2)(u4_t_fltrd >> IOHW_DIFLT_FLTRD_LSB_VALID) & u2_t_sgnlbit;
        u4_t_fltrd    &= (U4)u2_t_sgnlbit;
        if(u2_t_validchk != u2_t_sgnlbit){
         /* u1_t_switch = (U1)IOHW_DIFLT_SWITCH_UNKNWN; */
        }
        else if(u4_t_fltrd == (U4)u2_t_sgnlact){
            u1_t_switch = (U1)IOHW_DIFLT_SWITCH_ACT;
        }
        else{
            u1_t_switch = (U1)IOHW_DIFLT_SWITCH_INACT;
        }
    }
    
    return(u1_t_switch);
}
/*===================================================================================================================================*/
/*  U1      u1_g_IoHwDifltGroup(const U2 u2_a_DIGR, U2 * u2_ap_gr)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_IoHwDifltGroup(const U2 u2_a_DIGR, U2 * u2_ap_gr)
{
    U4                         u4_t_fltrd;

    U2                         u2_t_sgnlbit;
    U2                         u2_t_port;
    U2                         u2_t_validchk;

    U1                         u1_t_valid;

    u1_t_valid = (U1)FALSE;
    if(u2_a_DIGR < u2_g_IOHW_DIFLT_NUM_DIGR){

        u2_t_sgnlbit  = st_gp_IOHW_DIFLT_DIGR[u2_a_DIGR].u2_sgnlbit;
        u2_t_port     = st_gp_IOHW_DIFLT_DIGR[u2_a_DIGR].u2_port;
        u4_t_fltrd    = u4_gp_iohw_diflt_fltrd[u2_t_port];
        u2_t_validchk = (U2)(u4_t_fltrd >> IOHW_DIFLT_FLTRD_LSB_VALID) & u2_t_sgnlbit;
        if(u2_ap_gr != vdp_PTR_NA){

            /* ------------------------------------------------------------------------------------------ */
            /* Attention :                                                                                */
            /* The signals, which are valid, are copied to return buffer "u2_ap_gr[IOHW_DIFLT_GRP_SGNL]". */
            /* It's because user can use own default value which are set before call u1_g_IoHwDifltGroup. */
            /* ------------------------------------------------------------------------------------------ */
            u2_ap_gr[IOHW_DIFLT_GRP_SGNL] &= ((U2)U2_MAX ^ u2_t_validchk);
            u2_ap_gr[IOHW_DIFLT_GRP_SGNL] |= ((U2)u4_t_fltrd & u2_t_validchk);
            u2_ap_gr[IOHW_DIFLT_GRP_STAT]  = u2_t_validchk;
        }
        if(u2_t_validchk == u2_t_sgnlbit){
            u1_t_valid = (U1)TRUE;
        }
    }

    return(u1_t_valid);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/02/2015  TN       New.                                                                                               */
/*  1.1.0     4/22/2015  TN       u1_g_IoHwDifltGroup was implemented.                                                               */
/*  1.2.0     7/ 9/2015  TN       Group valid checker was implemented.                                                               */
/*  1.3.0    10/28/2015  TN       The design of state machine for filter was optimized.                                              */
/*  1.3.1    11/27/2015  TN       Mis-typecast was fixed. st_t_di_act.u2_act = u1_sp_IOHW_DIFLT_STM[u2_t_stsbit][u1_t_fltrsts];      */
/*                                                     -> st_t_di_act.u2_act = (U2)u1_sp_IOHW_DIFLT_STM[u2_t_stsbit][u1_t_fltrsts];  */
/*  1.3.2     9/ 7/2021  TN       "U" suffix were added into litterals because of MC3 Rule-7.2 compliance.                           */
/*                                NULL->vdp_PTR_NA.                                                                                  */
/*  1.4.0    10/ 4/2021  TN       QAC warnnings were fixed.                                                                          */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
