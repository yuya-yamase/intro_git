/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines / Power-train System Rx for MilReq                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_PTS_RX_MILREQ_C_MAJOR                    (1)
#define VARDEF_PTS_RX_MILREQ_C_MINOR                    (0)
#define VARDEF_PTS_RX_MILREQ_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "vardef_ptsrx_milreq_cfg_private.h"
/* #include "vardef_ptsrx_milreq.h" */ /* vardef_ptsx_milreq.h is included in vardef_dbf.h */
#include "vardef.h"

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_PTS_RX_MILREQ_C_MAJOR != VARDEF_PTS_RX_MILREQ_H_MAJOR) || \
     (VARDEF_PTS_RX_MILREQ_C_MINOR != VARDEF_PTS_RX_MILREQ_H_MINOR) || \
     (VARDEF_PTS_RX_MILREQ_C_PATCH != VARDEF_PTS_RX_MILREQ_H_PATCH))
#error "vardef_ptsrx_milreq.c and vardef_ptsrx_milreq.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_PTS_RX_MILREQ_C_MAJOR != VARDEF_PTS_RX_MILREQ_CFG_H_MAJOR) || \
     (VARDEF_PTS_RX_MILREQ_C_MINOR != VARDEF_PTS_RX_MILREQ_CFG_H_MINOR) || \
     (VARDEF_PTS_RX_MILREQ_C_PATCH != VARDEF_PTS_RX_MILREQ_CFG_H_PATCH))
#error "vardef_ptsrx_milreq.c and vardef_ptsrx_milreq_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_PTS_RX_MILREQ_RXC_MAX                       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2           u2_s_vdf_pts_rx_milreq_elpsd;
static U1           u1_s_vdf_pts_rxc_milreq_sta;
static U1           u1_s_vdf_pts_rx_milreq_las;
static U1           u1_s_vdf_pts_rx_milreq_rim;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefPtsRxMilreqBonInit(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefPtsRxMilreqBonInit(void)
{
    u1_s_vdf_pts_rx_milreq_rim    = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    vd_g_Rim_WriteU1(u2_g_VDF_PTS_RX_MILREQ_RIM_U1, u1_s_vdf_pts_rx_milreq_rim);

    u2_s_vdf_pts_rx_milreq_elpsd  = (U2)U2_MAX;
    u1_s_vdf_pts_rxc_milreq_sta   = u1_g_VDF_PTS_RX_MILREQ_RXC_INT;
    u1_s_vdf_pts_rx_milreq_las    = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefPtsRxMilreqRstwkInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefPtsRxMilreqRstwkInit(void)
{
    U1          u1_t_rim_rx;
    U1          u1_t_rim_chk;

    u1_t_rim_rx  = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    u1_t_rim_chk = u1_g_Rim_ReadU1withStatus(u2_g_VDF_PTS_RX_MILREQ_RIM_U1, &u1_t_rim_rx) & (U1)RIM_RESULT_KIND_MASK;

    if((u1_t_rim_chk == (U1)RIM_RESULT_KIND_OK) &&
       (u1_t_rim_rx  <= (U1)VDF_PTS_RX_MILREQ_0F_UNK )){
        u1_s_vdf_pts_rx_milreq_rim = u1_t_rim_rx;
    }
    else{
        u1_s_vdf_pts_rx_milreq_rim = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
        vd_g_Rim_WriteU1(u2_g_VDF_PTS_RX_MILREQ_RIM_U1, u1_s_vdf_pts_rx_milreq_rim);
    }

    u2_s_vdf_pts_rx_milreq_elpsd  = (U2)U2_MAX;
    u1_s_vdf_pts_rxc_milreq_sta   = u1_g_VDF_PTS_RX_MILREQ_RXC_INT;
    u1_s_vdf_pts_rx_milreq_las    = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefPtsRxMilreqOpemdEvhk(const U2 u2_a_EOM)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefPtsRxMilreqOpemdEvhk(const U2 u2_a_EOM)
{
    U2                  u2_t_ign;

    u2_t_ign = u2_a_EOM & (U2)VDF_EOM_IGR_ON;
    if(u2_t_ign == (U2)0U){
        u1_s_vdf_pts_rxc_milreq_sta = u1_g_VDF_PTS_RX_MILREQ_RXC_INT;
        u1_s_vdf_pts_rx_milreq_las  = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefPtsRxMilreqMainTask(const U2 u2_a_EOM)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefPtsRxMilreqMainTask(const U2 u2_a_EOM)
{
    static const U2     u2_s_VDF_PTS_RX_MILREQ_PERI = ((U2)600U/ (U2)VDF_MAIN_TICK);

    U4                  u4_t_elpsd;

    U2                  u2_t_ign;
    U2                  u2_t_inc;

    U1                  u1_t_rx;
    U1                  u1_t_cnt;

    U2                  u2_t_rxcnt;
    U2                  u2_t_rxcnt_masked;

    u1_t_rx  = (U1)0U;
    u1_t_cnt = u1_g_VardefPtsRxMlrqCfgPtsyschk(&u1_t_rx);
    u2_t_ign = u2_a_EOM & (U2)VDF_EOM_IGR_ON;
    if(u2_t_ign == (U2)0U){
        u1_t_rx = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    }

    if((u1_t_rx                     > (U1)VDF_PTS_RX_MILREQ_0F_UNK  ) ||
       (u1_s_vdf_pts_rxc_milreq_sta > u1_g_VDF_PTS_RX_MILREQ_RXC_MAX) ||
       (u1_t_cnt                    > u1_g_VDF_PTS_RX_MILREQ_RXC_MAX)){
        u1_s_vdf_pts_rxc_milreq_sta = u1_t_cnt;
        u1_s_vdf_pts_rx_milreq_las  = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    }
    else if(u1_t_rx == u1_s_vdf_pts_rx_milreq_las){
        u2_t_rxcnt        = (U2)((U2)u1_t_cnt - (U2)u1_s_vdf_pts_rxc_milreq_sta);
        u2_t_rxcnt_masked = u2_t_rxcnt & (U2)u1_g_VDF_PTS_RX_MILREQ_RXC_MAX;
        u2_t_inc          = u2_t_rxcnt_masked + (U2)1U;
        if(u2_t_inc >= (U2)VDF_PTS_RX_MILREQ_RXC_MAX){
            if((u1_t_rx != (U1)VDF_PTS_RX_MILREQ_00_UNK)  &&
               ((u1_t_rx >= (U1)VDF_PTS_RX_MILREQ_01_GAS) &&
                (u1_t_rx <= (U1)VDF_PTS_RX_MILREQ_08_48V)))
            {
                u1_s_vdf_pts_rx_milreq_rim = u1_t_rx;
                vd_g_Rim_WriteU1(u2_g_VDF_PTS_RX_MILREQ_RIM_U1, u1_s_vdf_pts_rx_milreq_rim);
            }
        }
    }
    else if(u1_t_cnt != u1_s_vdf_pts_rxc_milreq_sta){
        u1_s_vdf_pts_rxc_milreq_sta = u1_t_cnt;
        u1_s_vdf_pts_rx_milreq_las  = u1_t_rx;
    }
    else{
        /* do nothing */
    }

    u4_t_elpsd = (U4)u2_s_vdf_pts_rx_milreq_elpsd + (U4)VDF_NUM_TSLOT;
    if(u4_t_elpsd >= (U4)u2_s_VDF_PTS_RX_MILREQ_PERI){
        u1_s_vdf_pts_rxc_milreq_sta = u1_t_cnt;
        u1_s_vdf_pts_rx_milreq_las  = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
        u4_t_elpsd           = (U4)0U;
    }
    u2_s_vdf_pts_rx_milreq_elpsd = (U2)u4_t_elpsd;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefPtsRxMilreqReset(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefPtsRxMilreqReset(void)
{
    u1_s_vdf_pts_rx_milreq_rim = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    vd_g_Rim_WriteU1(u2_g_VDF_PTS_RX_MILREQ_RIM_U1, u1_s_vdf_pts_rx_milreq_rim);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefPtsRxMilreq(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefPtsRxMilreq(void)
{
    U1    u1_t_ptsys_rx;

    u1_t_ptsys_rx = u1_s_vdf_pts_rx_milreq_rim;

    return(u1_t_ptsys_rx);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/18/2023  DR       New for 19PFv3 PTSYS for MILREQ warning                                                            */
/*                                                                                                                                   */
/*  * DR = Dyan Reyes, DTPH                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
