/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Dimmer Day Night                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_DAYNIGHT_C_MAJOR                     (1)
#define DIM_DAYNIGHT_C_MINOR                     (1)
#define DIM_DAYNIGHT_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dim_daynight_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DIM_DAYNIGHT_C_MAJOR != DIM_DAYNIGHT_H_MAJOR) || \
     (DIM_DAYNIGHT_C_MINOR != DIM_DAYNIGHT_H_MINOR) || \
     (DIM_DAYNIGHT_C_PATCH != DIM_DAYNIGHT_H_PATCH))
#error "dim_daynight.c and dim_daynight.h : source and header files are inconsistent!"
#endif

#if ((DIM_DAYNIGHT_C_MAJOR != DIM_DAYNIGHT_CFG_H_MAJOR) || \
     (DIM_DAYNIGHT_C_MINOR != DIM_DAYNIGHT_CFG_H_MINOR) || \
     (DIM_DAYNIGHT_C_PATCH != DIM_DAYNIGHT_CFG_H_PATCH))
#error "dim_daynight.c and dim_daynight_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DIM_ADIM_STS_CHK_RT_1ST                  (0x01U)
#define DIM_ADIM_STS_CHK_RT_2ND                  (0x02U)

#define DIM_ADIM_ACT_TO_INACT                    (0U)      
#define DIM_ADIM_ACT_TO_VALID                    (1U) 
#define DIM_ADIM_ACT_VALID                       (2U) 
#define DIM_ADIM_ACT_TO_RT_1ST                   (3U)
#define DIM_ADIM_ACT_TO_RT_2ND                   (4U)
#define DIM_ADIM_ACT_TO_INIT                     (5U)
#define DIM_ADIM_ACT_INIT                        (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2   u2_s_dim_adim_tocnt;
static U1   u1_s_dim_adim_rx_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_DimDaynightAdimUpdt(const U1 u1_a_ACT, const U1 u1_a_LAST, const U1 u1_a_LVL_NEXT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U2      u2_g_DimDaynightInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DimDaynightInit(void)
{
    u2_s_dim_adim_tocnt  = (U2)U2_MAX;
    u1_s_dim_adim_rx_chk = (U1)DIM_ADIM_RX_CHK_INACT;
}
/*===================================================================================================================================*/
/*  U1      u1_g_DimDaynightAdimchk(const U1 u1_a_LAST)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DimDaynightAdimchk(const U1 u1_a_LAST)
{
    static const U1         u1_sp_DIM_ADIM_ACT[] = {
        (U1)DIM_ADIM_ACT_VALID,     (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_RT_2ND,
        (U1)DIM_ADIM_ACT_INIT,      (U1)DIM_ADIM_ACT_TO_INIT,

        (U1)DIM_ADIM_ACT_VALID,     (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_RT_2ND,
        (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_INIT,

        (U1)DIM_ADIM_ACT_TO_RT_2ND, (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_RT_2ND,
        (U1)DIM_ADIM_ACT_INIT,      (U1)DIM_ADIM_ACT_TO_INIT,

        (U1)DIM_ADIM_ACT_TO_RT_2ND, (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_RT_2ND,
        (U1)DIM_ADIM_ACT_TO_RT_1ST, (U1)DIM_ADIM_ACT_TO_INIT
    };

    U1                      u1_t_rx_ena;
    U1                      u1_t_rx_evt;
    U1                      u1_t_lv_next;

    U1                      u1_t_daynight;
    U1                      u1_t_sts_chk;
    U1                      u1_t_act;

    if(u2_s_dim_adim_tocnt < (U2)U2_MAX){
        u2_s_dim_adim_tocnt++;
    }

    u1_t_lv_next = (U1)DIM_DAYNIGHT_LVL_UNKNWN;
    u1_t_rx_evt  = u1_g_DimDaynightCfgAdimRxEvt(&u1_t_lv_next);

    u1_t_rx_ena = u1_g_DimDaynightCfgRxEnabled();
    if((u1_t_rx_ena         != (U1)TRUE                ) ||
       (u1_s_dim_adim_rx_chk >= (U1)DIM_ADIM_NUM_RX_CHK)){
        u1_t_act = (U1)DIM_ADIM_ACT_TO_INACT;
    }
    else if(u1_t_rx_evt == (U1)TRUE){
        u1_t_act = (U1)DIM_ADIM_ACT_TO_VALID;
    }
    else{

        if(u2_s_dim_adim_tocnt >= u2_gp_DIM_ADIM_RX_TOUT[DIM_ADIM_RX_TOUT_2ND]){
            u1_t_sts_chk  = (U1)DIM_ADIM_STS_CHK_RT_2ND;
        }
        else{
            u1_t_sts_chk  = (U1)0U;
        }
        if(u2_s_dim_adim_tocnt >= u2_gp_DIM_ADIM_RX_TOUT[DIM_ADIM_RX_TOUT_1ST]){
            u1_t_sts_chk |= (U1)DIM_ADIM_STS_CHK_RT_1ST;
        }
        u1_t_act = (u1_t_sts_chk * (U1)DIM_ADIM_NUM_RX_CHK) + u1_s_dim_adim_rx_chk;
        u1_t_act = u1_sp_DIM_ADIM_ACT[u1_t_act];
    }

    u1_t_daynight = u1_s_DimDaynightAdimUpdt(u1_t_act, u1_a_LAST, u1_t_lv_next);

    vd_g_DimDaynightCfgAdimRxchk(u1_s_dim_adim_rx_chk, u1_t_daynight);

    return(u1_t_daynight);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_DimDaynightAdimUpdt(const U1 u1_a_ACT, const U1 u1_a_LAST, const U1 u1_a_LVL_NEXT)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_DimDaynightAdimUpdt(const U1 u1_a_ACT, const U1 u1_a_LAST, const U1 u1_a_LVL_NEXT)
{
    U1                      u1_t_daynight;

    u1_t_daynight = u1_a_LAST;
    switch(u1_a_ACT){
        case DIM_ADIM_ACT_TO_VALID:
            u2_s_dim_adim_tocnt   = (U2)0U;
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_VALID;
            u1_t_daynight         = u1_a_LVL_NEXT;
            break;
        case DIM_ADIM_ACT_VALID:
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_VALID;
            break;
        case DIM_ADIM_ACT_TO_RT_1ST:
            u2_s_dim_adim_tocnt   = (U2)U2_MAX;
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_RT_1ST;
            u1_t_daynight         = (U1)DIM_DAYNIGHT_LVL_DAY;
            break;
        case DIM_ADIM_ACT_TO_RT_2ND:
            u2_s_dim_adim_tocnt   = (U2)U2_MAX;
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_RT_2ND;
            break;
        case DIM_ADIM_ACT_TO_INIT:
            u2_s_dim_adim_tocnt   = (U2)0U;
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_INIT;
            break;
        case DIM_ADIM_ACT_INIT:
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_INIT;
            break;
     /* case DIM_ADIM_ACT_TO_INACT: */
        default:
            u2_s_dim_adim_tocnt   = (U2)U2_MAX;
            u1_s_dim_adim_rx_chk  = (U1)DIM_ADIM_RX_CHK_INACT;
            break;
    }

    return(u1_t_daynight);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/18/2018  TN       New.                                                                                               */
/*  1.1.0     2/22/2019  TN       vd_g_DimDaynightCfgDnInfTx was implemented.                                                        */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
