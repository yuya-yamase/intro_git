/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Power-train System Coolant Temperature                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_CEL_C_MAJOR                      (2)
#define PTSCTMP_CEL_C_MINOR                      (1)
#define PTSCTMP_CEL_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ptsctmp_cel_cfg_private.h"
#include "ptsctmp_wtssr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((PTSCTMP_CEL_C_MAJOR != PTSCTMP_CEL_H_MAJOR) || \
     (PTSCTMP_CEL_C_MINOR != PTSCTMP_CEL_H_MINOR) || \
     (PTSCTMP_CEL_C_PATCH != PTSCTMP_CEL_H_PATCH))
#error "ptsctmp_cel.c and ptsctmp_cel.h : source and header files are inconsistent!"
#endif

#if ((PTSCTMP_CEL_C_MAJOR != PTSCTMP_CEL_CFG_H_MAJOR) || \
     (PTSCTMP_CEL_C_MINOR != PTSCTMP_CEL_CFG_H_MINOR) || \
     (PTSCTMP_CEL_C_PATCH != PTSCTMP_CEL_CFG_H_PATCH))
#error "ptsctmpl_cel.c and ptsctmp_cel_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PTSCTMP_MAINTICK                         (100U)

#define PTSCTMP_ACT_NUM                          (16U)
#define PTSCTMP_FLTR_TO_INACT                    (0U)
#define PTSCTMP_FLTR_TO_INIT                     (1U)
#define PTSCTMP_FLTR_TO_INIT_OVH                 (2U)
#define PTSCTMP_FLTR_ACT                         (3U)
#define PTSCTMP_FLTR_TO_ACT                      (4U)
#define PTSCTMP_FLTR_TO_ACT_OVH                  (5U)
#define PTSCTMP_FLTR_TO_LAST                     (6U)
#define PTSCTMP_FLTR_TO_LAST_OVH                 (7U)
#define PTSCTMP_FLTR_TO_NOS                      (8U)
#define PTSCTMP_FLTR_TO_NOS_OVH                  (9U)

#define PTSCTMP_FLTR_NUM_STS                     (2U)
#define PTSCTMP_FLTR_STS_INACT                   (0U)
#define PTSCTMP_FLTR_STS_ACT                     (1U)

#define PTSCTMP_FLTR_MVAVG_TMS_MAX               (4U)

#define PTSCTMP_TIMES_TMELPSD                    (1000U/PTSCTMP_MAINTICK)

#define PTSCTMP_STSBIT_SMP_ELPSD                 (0x08U)

#define PTSCTMP_CEL_WT_OVH                       (12500U + PTSCTMP_CEL_OFFSET) /* 125[cel] */
#define PTSCTMP_CEL_ZERO                         (PTSCTMP_CEL_OFFSET)          /*   0[cel] */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_ptsctmp_stsbit;     /* Status of Power-train System Coolant Temperature                                     */
static U2       u2_s_ptsctmp_cel_inst;   /* Power-train System Coolant Temperature (instant)   LSB:0.01[cel] Offset:-273.15[cel] */
static U2       u2_s_ptsctmp_cel_fltrd;  /* Power-train System Coolant Temperature (filtered)  LSB:0.01[cel] Offset:-273.15[cel] */

static U1       u1_s_ptsctmp_fltr_ctl;                                 /* Filtering control status                               */
static U2       u2_sp_ptsctmp_fltr_smpl[PTSCTMP_FLTR_MVAVG_TMS_MAX];   /* The coolant temperature samples for filtering          */
static U1       u1_s_ptsctmp_fltr_pos_oldest;                          /* The oldest index of the coolant temperature samples    */
static U2       u2_s_ptsctmp_fltr_tmelpsd;                             /* Elapsed time after filtering control                   */
static U4       u4_s_ptsctmp_fltr_sum;                                 /* Sum of the coolant temperature samples                 */
static U2       u2_s_ptsctmp_dtc_to;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_PtsctmpFltrCel(const U1 u1_a_STSBIT, const U2 u2_a_0P01CEL);
static U1       u1_s_PtsctmpSmpltmchk(void);
static void     vd_s_PtsctmpFltrAct(const U1 u1_a_ACT, const U1 u1_a_STSBIT, const U2 u2_a_CEL);
static void     vd_s_PtsctmpMvAvgInit(const U2  u2_a_CEL);
static U2       u2_s_PtsctmpMvAvgUpdt(const U2  u2_a_CEL);
static void     vs_s_PtsctmpDtcchk(const U1 u1_a_STSBIT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PtsctmpInit(void)
{
    U4                  u4_t_lpcnt;

    u1_s_ptsctmp_stsbit     = (U1)PTSCTMP_STSBIT_UNKNOWN;
    u2_s_ptsctmp_cel_inst   = (U2)PTSCTMP_CEL_ZERO;
    u2_s_ptsctmp_cel_fltrd  = (U2)PTSCTMP_CEL_ZERO;
    u1_s_ptsctmp_fltr_ctl   = (U1)PTSCTMP_FLTR_STS_INACT;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
        u2_sp_ptsctmp_fltr_smpl[u4_t_lpcnt] = (U2)0U;
    }
    u1_s_ptsctmp_fltr_pos_oldest = (U1)U1_MAX;
    u2_s_ptsctmp_fltr_tmelpsd    = (U2)0U;
    u4_s_ptsctmp_fltr_sum        = (U4)0U;
    u2_s_ptsctmp_dtc_to          = (U2)0U;

    vd_g_PtsctmpWtssrInit();
}

/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PtsctmpOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    U4                  u4_t_evtchk;
#if 0   /* BEV BSW provisionally */
    u4_t_evtchk = u4_a_EVTBIT & ((U4)VEH_OPEMD_EVTBIT_IGN_TO_ON |(U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF);
#else
    u4_t_evtchk = u4_a_EVTBIT & ((U4)0x00000020U |(U4)0x00002000U);
#endif
    if(u4_t_evtchk != (U4)0U){
        u1_s_ptsctmp_stsbit    = (U1)PTSCTMP_STSBIT_UNKNOWN;
        u2_s_ptsctmp_cel_inst  = (U2)PTSCTMP_CEL_ZERO;
        u2_s_ptsctmp_cel_fltrd = (U2)PTSCTMP_CEL_ZERO;
        u1_s_ptsctmp_fltr_ctl  = (U1)PTSCTMP_FLTR_STS_INACT;
        u2_s_ptsctmp_dtc_to    = (U2)0U;
    }
    vd_g_PtsctmpWtssrOpemdEvhk(u4_a_MDBIT, u4_a_EVTBIT);
}

/*===================================================================================================================================*/
/*  void    vd_g_PtsctmpMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_PtsctmpMainTask(void)
{
    U1                  u1_t_stsbit;
    U1                  u1_t_wtsel;
    U1                  u1_t_wtssr;
    U2                  u2_t_0p01cel;

    u2_t_0p01cel = (U2)PTSCTMP_CEL_ZERO;
    u1_t_stsbit  = u1_g_PtsctmpCfgCelInst(&u2_t_0p01cel) & ((U1)PTSCTMP_STSBIT_UNKNOWN |
                                                            (U1)PTSCTMP_STSBIT_INVALID |
                                                            (U1)PTSCTMP_STSBIT_WTSW_HI |
                                                            (U1)PTSCTMP_STSBIT_WTSW_OP);
    u1_t_wtsel = u1_g_PtsctmpCfgWtSel();
    if(u1_t_wtsel == (U1)PTSCTMP_WTSEL_SSR){
        u1_t_stsbit &= ((U1)U1_MAX ^ (U1)PTSCTMP_STSBIT_WTSW_HI);
        u1_t_wtssr   = u1_g_PtsctmpWtssrMainTask();
        if(u1_t_wtssr == (U1)TRUE){
            u1_t_stsbit |= (U1)PTSCTMP_STSBIT_WTSW_HI;
        }
    }

    vd_s_PtsctmpFltrCel(u1_t_stsbit, u2_t_0p01cel);
    vs_s_PtsctmpDtcchk(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_PtsctmpCelInst(U2 * u2p_a_0p01cel)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PtsctmpCelInst(U2 * u2p_a_0p01cel)
{
    U1                  u1_t_unk;


    u1_t_unk = u1_s_ptsctmp_stsbit & ((U1)PTSCTMP_STSBIT_UNKNOWN | (U1)PTSCTMP_STSBIT_WTSW_HI);
    if((u1_s_ptsctmp_stsbit & (U1)PTSCTMP_STSBIT_WTSW_OP) == (U1)0U){
        u1_t_unk &= ((U1)U1_MAX ^ (U1)PTSCTMP_STSBIT_WTSW_HI);
    }
    if((u1_t_unk      != (U1)PTSCTMP_STSBIT_UNKNOWN) &&
       (u2p_a_0p01cel != vdp_PTR_NA                )){
        (*u2p_a_0p01cel) = u2_s_ptsctmp_cel_inst;
    }

    return(u1_s_ptsctmp_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_PtsctmpCelFltrd(U2 * u2p_a_0p01cel)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_PtsctmpCelFltrd(U2 * u2p_a_0p01cel)
{
    U1                  u1_t_unk;

    u1_t_unk = u1_s_ptsctmp_stsbit & ((U1)PTSCTMP_STSBIT_UNKNOWN | (U1)PTSCTMP_STSBIT_WTSW_HI);
    if((u1_s_ptsctmp_stsbit & (U1)PTSCTMP_STSBIT_WTSW_OP) == (U1)0U){
        u1_t_unk &= ((U1)U1_MAX ^ (U1)PTSCTMP_STSBIT_WTSW_HI);
    }
    if((u1_t_unk      != (U1)PTSCTMP_STSBIT_UNKNOWN) &&
       (u2p_a_0p01cel != vdp_PTR_NA                )){
        (*u2p_a_0p01cel) = u2_s_ptsctmp_cel_fltrd;
    }
    return(u1_s_ptsctmp_stsbit);
}

/*===================================================================================================================================*/
/*  static void     vd_s_PtsctmpFltrCel(const U1 u1_a_STSBIT, const U2 u2_a_0P01CEL)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PtsctmpFltrCel(const U1 u1_a_STSBIT, const U2 u2_a_0P01CEL)
{
    static const U1 u1_sp_PTSCTMP_FLTR_CTRL_STM[PTSCTMP_ACT_NUM][PTSCTMP_FLTR_NUM_STS] = {   /* Filtering-action decision table */
        {(U1)PTSCTMP_FLTR_TO_INIT,      (U1)PTSCTMP_FLTR_ACT        },
        {(U1)PTSCTMP_FLTR_TO_NOS,       (U1)PTSCTMP_FLTR_TO_NOS     },
        {(U1)PTSCTMP_FLTR_TO_LAST,      (U1)PTSCTMP_FLTR_TO_LAST    },
        {(U1)PTSCTMP_FLTR_TO_NOS,       (U1)PTSCTMP_FLTR_TO_NOS     },
        {(U1)PTSCTMP_FLTR_TO_INIT_OVH,  (U1)PTSCTMP_FLTR_ACT        },
        {(U1)PTSCTMP_FLTR_TO_NOS_OVH,   (U1)PTSCTMP_FLTR_TO_NOS_OVH },
        {(U1)PTSCTMP_FLTR_TO_LAST_OVH,  (U1)PTSCTMP_FLTR_TO_LAST_OVH},
        {(U1)PTSCTMP_FLTR_TO_NOS_OVH,   (U1)PTSCTMP_FLTR_TO_NOS_OVH },
        {(U1)PTSCTMP_FLTR_TO_INIT,      (U1)PTSCTMP_FLTR_TO_ACT     },
        {(U1)PTSCTMP_FLTR_TO_NOS,       (U1)PTSCTMP_FLTR_TO_NOS     },
        {(U1)PTSCTMP_FLTR_TO_LAST,      (U1)PTSCTMP_FLTR_TO_LAST    },
        {(U1)PTSCTMP_FLTR_TO_NOS,       (U1)PTSCTMP_FLTR_TO_NOS     },
        {(U1)PTSCTMP_FLTR_TO_INIT_OVH,  (U1)PTSCTMP_FLTR_TO_ACT_OVH },
        {(U1)PTSCTMP_FLTR_TO_NOS_OVH,   (U1)PTSCTMP_FLTR_TO_NOS_OVH },
        {(U1)PTSCTMP_FLTR_TO_LAST_OVH,  (U1)PTSCTMP_FLTR_TO_LAST_OVH},
        {(U1)PTSCTMP_FLTR_TO_NOS_OVH,   (U1)PTSCTMP_FLTR_TO_NOS_OVH }
    };

    U1                  u1_t_igon;
    U1                  u1_t_stsbit;
    U1                  u1_t_act;

    u1_t_igon    = u1_g_PtsctmpCfgIgOn();
    u1_t_stsbit  = u1_a_STSBIT;
    if((u1_a_STSBIT & (U1)PTSCTMP_STSBIT_WTSW_OP) == (U1)0U){
        u1_t_stsbit &= ((U1)U1_MAX ^ (U1)PTSCTMP_STSBIT_WTSW_HI);
    }
    u1_t_stsbit &= ((U1)U1_MAX ^ (U1)PTSCTMP_STSBIT_WTSW_OP);
    u1_t_stsbit  = u1_t_stsbit | u1_s_PtsctmpSmpltmchk();
    u1_t_act     = (U1)PTSCTMP_FLTR_TO_INACT;
    if((u1_t_igon             == (U1)TRUE                ) &&
       (u1_t_stsbit           <  (U1)PTSCTMP_ACT_NUM     ) &&
       (u1_s_ptsctmp_fltr_ctl <  (U1)PTSCTMP_FLTR_NUM_STS)){
        u1_t_act = u1_sp_PTSCTMP_FLTR_CTRL_STM[u1_t_stsbit][u1_s_ptsctmp_fltr_ctl];
    }
    vd_s_PtsctmpFltrAct(u1_t_act, u1_a_STSBIT, u2_a_0P01CEL);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_PtsctmpSmpltmchk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_PtsctmpSmpltmchk(void)
{
    U1                  u1_t_stsbit;

    u1_t_stsbit = (U1)0U;
    if(u2_s_ptsctmp_fltr_tmelpsd < (U2)U2_MAX){
        u2_s_ptsctmp_fltr_tmelpsd++;
    }
    if(u2_s_ptsctmp_fltr_tmelpsd >= (U2)PTSCTMP_TIMES_TMELPSD){
        u1_t_stsbit = (U1)PTSCTMP_STSBIT_SMP_ELPSD;
    }
    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  static void     vd_s_PtsctmpFltrAct(const U1 u1_a_ACT, const U1 u1_a_STSBIT, const U2 u2_a_CEL)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PtsctmpFltrAct(const U1 u1_a_ACT, const U1 u1_a_STSBIT, const U2 u2_a_CEL)
{
    U2                  u2_t_avg_cel;

    switch(u1_a_ACT){
        case PTSCTMP_FLTR_TO_INIT:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_ACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            vd_s_PtsctmpMvAvgInit(u2_a_CEL);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = u2_a_CEL;
            u2_s_ptsctmp_cel_inst     = u2_a_CEL;
            break;
        case PTSCTMP_FLTR_TO_INIT_OVH:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_ACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            vd_s_PtsctmpMvAvgInit((U2)PTSCTMP_CEL_WT_OVH);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = (U2)PTSCTMP_CEL_WT_OVH;
            u2_s_ptsctmp_cel_inst     = u2_a_CEL;
            break;
        case PTSCTMP_FLTR_ACT:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_ACT;
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_inst     = u2_a_CEL;
            break;
        case PTSCTMP_FLTR_TO_ACT:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_ACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            u2_t_avg_cel              = u2_s_PtsctmpMvAvgUpdt(u2_a_CEL);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = u2_t_avg_cel;
            u2_s_ptsctmp_cel_inst     = u2_a_CEL;
            break;
        case PTSCTMP_FLTR_TO_ACT_OVH:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_ACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            u2_t_avg_cel              = u2_s_PtsctmpMvAvgUpdt((U2)PTSCTMP_CEL_WT_OVH);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = u2_t_avg_cel;
            u2_s_ptsctmp_cel_inst     = u2_a_CEL;
            break;
        case PTSCTMP_FLTR_TO_LAST:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_INACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            break;
        case PTSCTMP_FLTR_TO_LAST_OVH:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_INACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = (U2)PTSCTMP_CEL_WT_OVH;
            break;
        case PTSCTMP_FLTR_TO_NOS:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_INACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            vd_s_PtsctmpMvAvgInit((U2)PTSCTMP_CEL_ZERO);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = (U2)PTSCTMP_CEL_ZERO;
            u2_s_ptsctmp_cel_inst     = (U2)PTSCTMP_CEL_ZERO;
            break;
        case PTSCTMP_FLTR_TO_NOS_OVH:
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_INACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            vd_s_PtsctmpMvAvgInit((U2)PTSCTMP_CEL_WT_OVH);
            u1_s_ptsctmp_stsbit       = u1_a_STSBIT;
            u2_s_ptsctmp_cel_fltrd    = (U2)PTSCTMP_CEL_WT_OVH;
            u2_s_ptsctmp_cel_inst     = (U2)PTSCTMP_CEL_ZERO;
            break;
        default:/*  PTSCTMP_FLTR_TO_INACT   */
            u1_s_ptsctmp_fltr_ctl     = (U1)PTSCTMP_FLTR_STS_INACT;
            u2_s_ptsctmp_fltr_tmelpsd = (U2)0U;
            vd_s_PtsctmpMvAvgInit((U2)PTSCTMP_CEL_ZERO);
            u1_s_ptsctmp_stsbit       = (U1)PTSCTMP_STSBIT_UNKNOWN;
            u2_s_ptsctmp_cel_fltrd    = (U2)PTSCTMP_CEL_ZERO;
            u2_s_ptsctmp_cel_inst     = (U2)PTSCTMP_CEL_ZERO;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_PtsctmpMvAvgInit(const U2  u2_a_CEL)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_PtsctmpMvAvgInit(const U2  u2_a_CEL)
{
    U4                  u4_t_lpcnt;

    u1_s_ptsctmp_fltr_pos_oldest = (U1)U1_MAX;
    if(((U4)U4_MAX / (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX) >= (U4)u2_a_CEL){
        u4_s_ptsctmp_fltr_sum = (U4)u2_a_CEL * (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX;
    }
    else{
        u4_s_ptsctmp_fltr_sum = (U4)U4_MAX;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
        u2_sp_ptsctmp_fltr_smpl[u4_t_lpcnt] = u2_a_CEL;
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_PtsctmpMvAvgUpdt(const U2  u2_a_CEL)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_PtsctmpMvAvgUpdt(const U2  u2_a_CEL)
{
    U2                  u2_t_cel_oldest;
    U4                  u4_t_avg_cel;
    U4                  u4_t_lpcnt;

    if(u1_s_ptsctmp_fltr_pos_oldest < ((U1)PTSCTMP_FLTR_MVAVG_TMS_MAX - (U1)1U)){
        u1_s_ptsctmp_fltr_pos_oldest++;
    }
    else{
        u1_s_ptsctmp_fltr_pos_oldest = (U1)0U;
    }

    u2_t_cel_oldest                                       = u2_sp_ptsctmp_fltr_smpl[u1_s_ptsctmp_fltr_pos_oldest];
    u2_sp_ptsctmp_fltr_smpl[u1_s_ptsctmp_fltr_pos_oldest] = u2_a_CEL;

    if((u4_s_ptsctmp_fltr_sum >= (U4)u2_t_cel_oldest                          )&&
       (u4_s_ptsctmp_fltr_sum <= ((U4)U2_MAX * (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX))){

        u4_s_ptsctmp_fltr_sum -= (U4)u2_t_cel_oldest;
        if(((U4)U4_MAX - (U4)u2_a_CEL) >= u4_s_ptsctmp_fltr_sum){
            u4_s_ptsctmp_fltr_sum += (U4)u2_a_CEL;
        }
        else{
            u4_s_ptsctmp_fltr_sum = (U4)U4_MAX;
        }
    }
    else{

        u4_s_ptsctmp_fltr_sum = (U4)0U;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX; u4_t_lpcnt++){
            if(((U4)U4_MAX - (U4)u2_sp_ptsctmp_fltr_smpl[u4_t_lpcnt]) >= u4_s_ptsctmp_fltr_sum){
                u4_s_ptsctmp_fltr_sum += u2_sp_ptsctmp_fltr_smpl[u4_t_lpcnt];
            }
            else{
                u4_s_ptsctmp_fltr_sum = (U4)U4_MAX;
            }
        }
    }
    u4_t_avg_cel = u4_s_ptsctmp_fltr_sum / (U4)PTSCTMP_FLTR_MVAVG_TMS_MAX;

    if(u4_t_avg_cel > (U4)U2_MAX){
        u4_t_avg_cel = (U4)U2_MAX;
    }
    return((U2)u4_t_avg_cel);
}

/*===================================================================================================================================*/
/*  static void     vs_s_PtsctmpDtcchk(const U1 u1_a_STSBIT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vs_s_PtsctmpDtcchk(const U1 u1_a_STSBIT)
{
    static const U2 u2_s_PTSCTMP_DTC_TO = (U2)3000U / (U2)PTSCTMP_MAINTICK;
    static const U1 u1_s_PTSCTMP_DTCCHK = (U1)PTSCTMP_STSBIT_WTSW_OP | (U1)PTSCTMP_STSBIT_WTSW_HI;
    U1  u1_t_igon;
    U1  u1_t_dtcchk;

    if(u2_s_ptsctmp_dtc_to < (U2)U2_MAX){
        u2_s_ptsctmp_dtc_to++;
    }

    u1_t_igon   = u1_g_PtsctmpCfgIgOn();
    u1_t_dtcchk = u1_a_STSBIT & u1_s_PTSCTMP_DTCCHK;
    if((u1_t_igon   == (U1)FALSE          ) ||
       (u1_t_dtcchk != u1_s_PTSCTMP_DTCCHK)){
        u2_s_ptsctmp_dtc_to = (U2)0U;
    }

    if(u2_s_ptsctmp_dtc_to > u2_s_PTSCTMP_DTC_TO){
        u1_s_ptsctmp_stsbit |= (U1)PTSCTMP_STSBIT_WTSW_DTCACT;
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
/*  1.0.0     7/25/2018  AK       NEW!                                                                                               */
/*  1.1.0     2/28/2019  TN       Improvement : The status "UNKNOWN" check was implemented into u1_g_PtsctmpCelInst and              */
/*                                u1_g_PtsctmpCelFltrd.                                                                              */
/*  1.2.0     6/17/2019  TN       Improvement : u1_g_PTSCTMP_IF_CEL_NUM -> u1_g_PTSCTMP_IF_NUM_CEL                                   */
/*  1.3.0     3/11/2020  HK       Modify : The temperature offset of u1_g_PtsctmpCelInst and u1_g_PtsctmpCelFltrd was changed        */
/*                                to -273.15 [cel].                                                                                  */
/*  1.4.0     7/ 7/2020  HY       Apply the improvement of 775B-v131-r015 version.                                                   */
/*  2.0.0     4/15/2021  TA       Add PTSCTMP_STSBIT_WTSW_OP/PTSCTMP_STSBIT_WTSW_DTCACT                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.1.0    12/15/2021  TA(M)    Add u1_g_PtsctmpCfgWtSel                                                                           */
/*                                                                                                                                   */
/*  * AK   = Aiko Kishino, Denso                                                                                                     */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * HK   = Hidehiro Kuoda, Denso Techno                                                                                            */
/*  * HY   = Hiroshige Yanase, Denso Techno                                                                                          */
/*  * TA   = Teruyuki Anjima, DENSO                                                                                                  */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
