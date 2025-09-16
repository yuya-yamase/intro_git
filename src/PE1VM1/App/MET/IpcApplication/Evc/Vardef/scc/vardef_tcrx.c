/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines / tacho Rx                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_TC_RX_C_MAJOR                    (1)
#define VARDEF_TC_RX_C_MINOR                    (0)
#define VARDEF_TC_RX_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_tcrx_cfg_private.h"
#include "vardef_tcrx.h"
#include "vardef.h"

#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_TC_RX_C_MAJOR != VARDEF_TC_RX_H_MAJOR) || \
     (VARDEF_TC_RX_C_MINOR != VARDEF_TC_RX_H_MINOR) || \
     (VARDEF_TC_RX_C_PATCH != VARDEF_TC_RX_H_PATCH))
#error "vardef_tcrx.c and vardef_tcrx.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_TC_RX_C_MAJOR != VARDEF_TC_RX_CFG_H_MAJOR) || \
     (VARDEF_TC_RX_C_MINOR != VARDEF_TC_RX_CFG_H_MINOR) || \
     (VARDEF_TC_RX_C_PATCH != VARDEF_TC_RX_CFG_H_PATCH))
#error "vardef_tcrx.c and vardef_tcrx_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_TC_RX_RXC_MAX                       (2U)                            /* Receive count Max                                 */
#define VDF_TC_RX_HV_NE_SHFT                    (1U)                            /* HV_NE Shift Position                              */
#define VDF_TC_RX_RIM_DATA_MASK                 (0x01U)                         /* RIM Data Mask                                     */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1           u1_s_vdf_tc_rxc_nemet_sta;                                  /* NE_MET Receive count                              */
static U1           u1_s_vdf_tc_rxc_hvne_sta;                                   /* HV_NE Receive count                               */
static U1           u1_s_vdf_tc_rx_ne_met_las;                                  /* NE_MET Avairable                                  */
static U1           u1_s_vdf_tc_rx_rim;                                         /* RIM Parameter                                     */
static U2           u2_s_vdf_tc_rx_nemet_elpsd;                                 /* NE_MET time counter Reset                         */
static U2           u2_s_vdf_tc_rx_hvne_elpsd;                                  /* HV_NE  time counter Reset                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1        u1_s_VardefTcRx_NeMet(void);
static U1        u1_s_VardefTcRx_HvNe(void);
static void      vd_s_VardefTcRx_RimChk(const U1 u1_a_NE_MET, const U1 u1_a_HV_NE);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefTcRxBonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefTcRxBonInit(void)
{
    u1_s_vdf_tc_rx_rim         = (U1)VDF_TC_RX_ALL_INA;
    vd_g_Rim_WriteU1(u2_g_VDF_TC_RX_RIM_U1, u1_s_vdf_tc_rx_rim);

    u1_s_vdf_tc_rxc_nemet_sta  = u1_g_VDF_TC_RX_RXC_INT;
    u1_s_vdf_tc_rxc_hvne_sta   = u1_g_VDF_TC_RX_RXC_INT;
    u1_s_vdf_tc_rx_ne_met_las  = (U1)VDF_TC_RX_UNK;
    u2_s_vdf_tc_rx_nemet_elpsd = (U2)U2_MAX;
    u2_s_vdf_tc_rx_hvne_elpsd  = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefTcRxRstwkInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefTcRxRstwkInit(void)
{
    U1          u1_t_rim_rx;                                                    /* RIM Parameter                                     */
    U1          u1_t_rim_chk;                                                   /* RIM Status                                        */

    u1_t_rim_rx  = (U1)0U;
    u1_t_rim_chk = u1_g_Rim_ReadU1withStatus(u2_g_VDF_TC_RX_RIM_U1, &u1_t_rim_rx) & (U1)RIM_RESULT_KIND_MASK;
    if((u1_t_rim_chk == (U1)RIM_RESULT_KIND_OK) &&
       (u1_t_rim_rx  <= (U1)VDF_TC_RX_MAX     )){
        u1_s_vdf_tc_rx_rim = u1_t_rim_rx;
    }
    else{
        u1_s_vdf_tc_rx_rim = (U1)VDF_TC_RX_ALL_INA;
        vd_g_Rim_WriteU1(u2_g_VDF_TC_RX_RIM_U1, u1_s_vdf_tc_rx_rim);
    }

    u1_s_vdf_tc_rxc_nemet_sta  = u1_g_VDF_TC_RX_RXC_INT;
    u1_s_vdf_tc_rxc_hvne_sta   = u1_g_VDF_TC_RX_RXC_INT;
    u1_s_vdf_tc_rx_ne_met_las  = (U1)VDF_TC_RX_UNK;
    u2_s_vdf_tc_rx_nemet_elpsd = (U2)U2_MAX;
    u2_s_vdf_tc_rx_hvne_elpsd  = (U2)U2_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_VardefTcRxMainTask(const U2 u2_a_EOM)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefTcRxMainTask(const U2 u2_a_EOM)
{
    U1                  u1_t_rx_ne_met;                                         /* NE_MET Available Judgement                        */
    U1                  u1_t_rx_hv_ne;                                          /* HV_NE Available Judgement                         */
    U2                  u2_t_ign;                                               /* IGP                                               */

    u2_t_ign = u2_a_EOM & (U2)VDF_EOM_IGR_ON;
    if(u2_t_ign == (U2)VDF_EOM_IGR_ON){
        u1_t_rx_ne_met = u1_s_VardefTcRx_NeMet();
        u1_t_rx_hv_ne  = u1_s_VardefTcRx_HvNe();
        vd_s_VardefTcRx_RimChk(u1_t_rx_ne_met, u1_t_rx_hv_ne);
    }
    else{
        /* RAM Reset */
        u1_s_vdf_tc_rxc_nemet_sta  = u1_g_VDF_TC_RX_RXC_INT;
        u1_s_vdf_tc_rxc_hvne_sta   = u1_g_VDF_TC_RX_RXC_INT;
        u1_s_vdf_tc_rx_ne_met_las  = (U1)VDF_TC_RX_UNK;
        u2_s_vdf_tc_rx_nemet_elpsd = (U2)U2_MAX;
        u2_s_vdf_tc_rx_hvne_elpsd  = (U2)U2_MAX;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_VardefTcRxReset(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefTcRxReset(void)
{
    u2_s_vdf_tc_rx_nemet_elpsd = (U2)U2_MAX;
    u2_s_vdf_tc_rx_hvne_elpsd  = (U2)U2_MAX;
    u1_s_vdf_tc_rx_rim         = (U1)VDF_TC_RX_ALL_INA;
    vd_g_Rim_WriteU1(u2_g_VDF_TC_RX_RIM_U1, u1_s_vdf_tc_rx_rim);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefTcRxRim(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_vdf_tc_rx_rim                                                                                               */
/*===================================================================================================================================*/
U1      u1_g_VardefTcRxRim(void)
{
    return(u1_s_vdf_tc_rx_rim);
}

/*===================================================================================================================================*/
/*  static U1        u1_s_VardefTcRx_NeMet(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_ava_rx                                                                                                      */
/*===================================================================================================================================*/
static U1        u1_s_VardefTcRx_NeMet(void)
{
    static const U1     u1_s_VDF_TC_RX_NE_MET = ((U1)100U / (U1)VDF_MAIN_TICK); /* NE_MET Available Time                             */

    U1                  u1_t_cnt;                                               /* NE_MET Receive count                              */
    U1                  u1_t_ava_rx;                                            /* NE_MET Available Judgement                        */
    U1                  u1_t_rx;                                                /* NE_MET Receive                                    */
    U2                  u2_t_inc;                                               /* Continuous Receive Count                          */
    U4                  u4_t_elpsd;                                             /* NE_MET time counter                               */

    u1_t_ava_rx = u1_s_vdf_tc_rx_rim & (U1)VDF_TC_RX_NE_MET_MASK;            /* Initialized with previous NE_MET available judgement */
    u1_t_rx     = (U1)0U;
    u1_t_cnt    = u1_g_VardefTcRxCfgNeMetchk(&u1_t_rx);

    if((u1_s_vdf_tc_rxc_nemet_sta > u1_g_VDF_TC_RX_RXC_MAX) ||
       (u1_t_cnt                  > u1_g_VDF_TC_RX_RXC_MAX)){
        u1_s_vdf_tc_rxc_nemet_sta = u1_t_cnt;
        u1_s_vdf_tc_rx_ne_met_las = (U1)VDF_TC_RX_UNK;
    }
    else if(u1_t_rx == u1_s_vdf_tc_rx_ne_met_las){ 
        u2_t_inc = (((U2)u1_t_cnt - (U2)u1_s_vdf_tc_rxc_nemet_sta) & (U2)u1_g_VDF_TC_RX_RXC_MAX) + (U2)1U;
        if(u2_t_inc >= (U2)VDF_TC_RX_RXC_MAX){
            u1_t_ava_rx = u1_t_rx;
        }
    }
    else if(u1_t_cnt != u1_s_vdf_tc_rxc_nemet_sta){
        u1_s_vdf_tc_rxc_nemet_sta = u1_t_cnt;
        u1_s_vdf_tc_rx_ne_met_las = u1_t_rx;
    }
    else{
        /* do nothing */
    }

    /* timer count for 100ms */
    u4_t_elpsd = (U4)u2_s_vdf_tc_rx_nemet_elpsd + (U4)1U;
    if(u4_t_elpsd >= (U4)u1_s_VDF_TC_RX_NE_MET){
        u1_s_vdf_tc_rxc_nemet_sta = u1_t_cnt;
    	u1_s_vdf_tc_rx_ne_met_las = (U1)VDF_TC_RX_UNK;
        u4_t_elpsd                = (U4)0U;
    }
    u2_s_vdf_tc_rx_nemet_elpsd = (U2)u4_t_elpsd;

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  static U1        u1_s_VardefTcRx_HvNe(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_ava_rx                                                                                                      */
/*===================================================================================================================================*/
static U1        u1_s_VardefTcRx_HvNe(void)
{
    static const U1     u1_s_VDF_TC_RX_HV_NE = ((U1)100U / (U1)VDF_MAIN_TICK);  /* HV_NE Available Time                              */

    U1                  u1_t_cnt;                                               /* HV_NE Receive count                               */
    U1                  u1_t_ava_rx;                                            /* HV_NE Available Judgement                         */
    U2                  u2_t_inc;                                               /* Continuous Receive Count                          */
    U4                  u4_t_elpsd;                                             /* HV_NE time counter                                */

    u1_t_ava_rx = (u1_s_vdf_tc_rx_rim & (U1)VDF_TC_RX_HV_NE_MASK) >> VDF_TC_RX_HV_NE_SHFT; /* Initialized with previous HV_NE available judgement */
    u1_t_cnt    = u1_g_VardefTcRxCfgHvNechk();
    if(u1_t_ava_rx == (U1)VDF_TC_RX_INA){
        if((u1_s_vdf_tc_rxc_hvne_sta > u1_g_VDF_TC_RX_RXC_MAX) ||
           (u1_t_cnt                 > u1_g_VDF_TC_RX_RXC_MAX)){
            u1_s_vdf_tc_rxc_hvne_sta = u1_t_cnt;
        }
        else if(u1_t_cnt != u1_s_vdf_tc_rxc_hvne_sta){
            u2_t_inc = (((U2)u1_t_cnt - (U2)u1_s_vdf_tc_rxc_hvne_sta) & (U2)u1_g_VDF_TC_RX_RXC_MAX);
            if(u2_t_inc >= (U2)VDF_TC_RX_RXC_MAX){
                u1_t_ava_rx = (U1)VDF_TC_RX_ACT;
            }
        }
        else{
            /* do nothing */
        }

        /* timer count for 100ms */
        u4_t_elpsd = (U4)u2_s_vdf_tc_rx_hvne_elpsd + (U4)1U;
        if(u4_t_elpsd >= (U4)u1_s_VDF_TC_RX_HV_NE){
            u1_s_vdf_tc_rxc_hvne_sta = u1_t_cnt;
            u4_t_elpsd               = (U4)0U;
        }
        u2_s_vdf_tc_rx_hvne_elpsd = (U2)u4_t_elpsd;
    }
    else{
        u1_s_vdf_tc_rxc_hvne_sta  = u1_t_cnt;
        u2_s_vdf_tc_rx_hvne_elpsd = (U2)U2_MAX;
    }

    return(u1_t_ava_rx);
}

/*===================================================================================================================================*/
/*  static void      vd_s_VardefTcRx_RimChk(const U1 u1_a_NE_MET, const U1 u1_a_HV_NE)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_NE_MET                                                                                             */ 
/*                  const U1 u1_a_HV_NE                                                                                              */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void      vd_s_VardefTcRx_RimChk(const U1 u1_a_NE_MET, const U1 u1_a_HV_NE)
{
    U1                  u1_t_rim_chk;                                           /* NE_MET and HV_NE Available Judgement              */

    u1_t_rim_chk  = u1_a_NE_MET & (U1)VDF_TC_RX_RIM_DATA_MASK;
    u1_t_rim_chk |= (u1_a_HV_NE & (U1)VDF_TC_RX_RIM_DATA_MASK) << VDF_TC_RX_HV_NE_SHFT;
    if(u1_s_vdf_tc_rx_rim != u1_t_rim_chk){
        u1_s_vdf_tc_rx_rim = u1_t_rim_chk;
        vd_g_Rim_WriteU1(u2_g_VDF_TC_RX_RIM_U1, u1_s_vdf_tc_rx_rim);
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
/*  1.0.0    11/18/2024  SH       New.                                                                                               */
/*                                                                                                                                   */
/*  * SH  = Sae Hirose, DENSO TECHNO                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
