/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Variation Defines Configuration                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_CFG_C_MAJOR                       (2)
#define VARDEF_CFG_C_MINOR                       (3)
#define VARDEF_CFG_C_PATCH                       (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_cfg_private.h"
#include "vardef_dest_cfg_private.h"
#include "vardef_ptsrx_cfg_private.h"
#include "vardef_hcs_cfg_private.h"

#include "oxcan.h"

#include "rim_ctl.h"

#include "vardef_esopt.h"
#include "veh_opemd.h"
#if 0   /* BEV Rebase provisionally */
#include "es_inspect.h"
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_CFG_C_MAJOR != VARDEF_H_MAJOR) || \
     (VARDEF_CFG_C_MINOR != VARDEF_H_MINOR) || \
     (VARDEF_CFG_C_PATCH != VARDEF_H_PATCH))
#error "vardef_cfg.c and vardef.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_CFG_C_MAJOR != VARDEF_CFG_H_MAJOR) || \
     (VARDEF_CFG_C_MINOR != VARDEF_CFG_H_MINOR) || \
     (VARDEF_CFG_C_PATCH != VARDEF_CFG_H_PATCH))
#error "vardef_cfg.c and vardef_cfg_private.h : source and header files are inconsistent!"
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1         u1_s_VardefCfgPowerChk(void);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef VARDEF_PTS_RX_H
#if 0   /* BEV Rebase provisionally */
const U2                u2_g_VDF_PTS_RX_RIM_U1       = (U2)RIMID_U1_VDF_PTSYS;
#else   /* BEV Rebase provisionally */
const U2                u2_g_VDF_PTS_RX_RIM_U1       = U2_MAX;
#endif   /* BEV Rebase provisionally */

const U1                u1_g_VDF_PTS_RX_RXC_INT  = (U1)OXCAN_RXD_EVC_UNK;
const U1                u1_g_VDF_PTS_RX_RXC_MAX  = (U1)OXCAN_RXD_EVC_MAX;
#endif /* #ifdef VARDEF_PTS_RX_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef VARDEF_HCS_H
const U2               u2_g_VDF_HCS_ASCEXT_RIM_U1  = (U2)RIMID_U1_VDF_HCS_ASCEXT;

const U1               u1_g_VDF_HCS_ASCEXT_RXC_INT = (U1)OXCAN_RXD_EVC_UNK;
const U1               u1_g_VDF_HCS_ASCEXT_RXC_MAX = (U1)OXCAN_RXD_EVC_MAX;
#endif /* #ifdef VARDEF_HCS_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                u2_g_VDF_MT_CH                  = (U2)VDF_ESO_CH_MT;
const U2                u2_g_VDF_AT_CH                  = (U2)VDF_ESO_CH_AT;
const U2                u2_g_VDF_MMT_SMT_CH             = (U2)VDF_ESO_CH_MMT_SMT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefCfgBonInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefCfgBonInit(void)
{
    vd_g_VardefEsOptBonInit();
    vd_g_VardefDestBonInit();

    vd_g_VardefPtsRxBonInit();
    vd_g_VardefHcsBonInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefCfgRstwkInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefCfgRstwkInit(void)
{
    vd_g_VardefEsOptRstwkInit();
    vd_g_VardefDestRstwkInit();

    vd_g_VardefPtsRxRstwkInit();
    vd_g_VardefHcsRstwkInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefCfgOpemdEvhk(const U2 u2_a_EOM)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefCfgOpemdEvhk(const U2 u2_a_EOM)
{
    vd_g_VardefEsOptOpemdEvhk(u2_a_EOM);
    vd_g_VardefPtsRxOpemdEvhk(u2_a_EOM);
    vd_g_VardefHcsOpemdEvhk(u2_a_EOM);
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefCfgMainTask(const U2 u2_a_EOM, const U1 u1_a_TSLOT)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefCfgMainTask(const U2 u2_a_EOM, const U1 u1_a_TSLOT)
{
    vd_g_VardefEsOptMainTask(u2_a_EOM, u1_a_TSLOT);

    if(u1_a_TSLOT == (U1)VDF_TSLOT_2){
        vd_g_VardefDestMainTask();                    /* vd_g_VardefDestMainTask shall be invoked every 100 milliseconds        */
        vd_g_VardefPtsRxMainTask(u2_a_EOM);           /* vd_g_VardefPtsRxMainTask shall be invoked every 100 milliseconds       */
        vd_g_VardefHcsMainTask(u2_a_EOM);
    }
    else{
        /* do nothing */
    }
}
/*===================================================================================================================================*/
/*  U2      u2_g_VardefCfgEomchk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_VardefCfgEomchk(void)
{
#if 0   /* BEV Rebase provisionally */
#if ((ES_INSPECT_MDBF_NUO_DI != (VDF_EOM_NUO_DI >> 8U)) ||  \
     (ES_INSPECT_MDBF_SI_ACT != (VDF_EOM_SI_ACT >> 8U)))
#error "vardef_fg.c : VDF_EOM_XXX shall be equal to ES_INSPECT_MDBF_XXXX."
#endif
#endif   /* BEV Rebase provisionally */

    U2          u2_t_eom;

    u2_t_eom = (U2)u1_s_VardefCfgPowerChk();
#if 0   /* BEV Rebase provisionally */
    u2_t_eom |= ((U2)u1_g_ESInspectMdBfield() << 8U);
#endif   /* BEV Rebase provisionally */

    return(u2_t_eom);
}

#ifdef VARDEF_PTS_RX_H


/*===================================================================================================================================*/
/*  U1      u1_g_VardefPtsRxCfgPtsyschk(U1 * u1_ap_ptsys_rx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefPtsRxCfgPtsyschk(U1 * u1_ap_ptsys_rx)
{
#if 0   /* BEV Rebase provisionally */
#ifdef ComConf_ComSignal_PTSYS
    (void)Com_ReceiveSignal(ComConf_ComSignal_PTSYS, u1_ap_ptsys_rx);
    return(u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_ENG1G13));
#else
    (*u1_ap_ptsys_rx) = (U1)VDF_PTS_RX_1F_NRX;
    return((U1)OXCAN_RXD_EVC_UNK);
#endif
#else   /* BEV Rebase provisionally */
    (*u1_ap_ptsys_rx) = (U1)VDF_PTS_RX_1F_NRX;
    return((U1)OXCAN_RXD_EVC_UNK);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/


#endif /* #ifdef VARDEF_PTS_RX_H */


/*===================================================================================================================================*/
/*  U1      u1_g_VardefHcsCfgAscextchk(U1* u1_ap_ascext_rx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefHcsCfgAscextchk(U1* u1_ap_ascext_rx)
{
    (void)Com_ReceiveSignal(ComConf_ComSignal_ASCEXT, u1_ap_ascext_rx);
#if 0   /* BEV Rebase provisionally */
    return(u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_ASC1S90));
#else   /* BEV Rebase provisionally */
    return((U1)OXCAN_RXD_EVC_UNK);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  U1      u1_s_VardefCfgPowerChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_s_VardefCfgPowerChk(void)
{
    U1          u1_t_ret;
    U1          u1_t_power_on;

    u1_t_ret = (U1)VDF_EOM_PB_ON;

    u1_t_power_on = u1_g_VehopemdBaOn();
    if (u1_t_power_on == (U1)TRUE) {
        u1_t_ret |= (U1)VDF_EOM_PBA_ON;
    }

    u1_t_power_on = u1_g_VehopemdAccOn();
    if (u1_t_power_on == (U1)TRUE) {
        u1_t_ret |= (U1)VDF_EOM_ACC_ON;
    }

    u1_t_power_on = u1_g_VehopemdIgnOn();
    if (u1_t_power_on == (U1)TRUE) {
        u1_t_ret |= (U1)VDF_EOM_IGR_ON;
    }


    u1_t_power_on = u1_g_VehopemdIgnpOn();
    if (u1_t_power_on == (U1)TRUE) {
        u1_t_ret |= (U1)VDF_EOM_IGP_ON;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     3/26/2020  TN       New.                                                                                               */
/*  2.1.0     9/28/2020  SF       vardef.c v2.0.0 -> v2.1.0                                                                          */
/*  2.2.0     1/25/2021  SF       vardef.c v2.1.0 -> v2.2.0                                                                          */
/*  2.3.0     5/02/2024  GM       vardef.c v2.2.0 -> v2.3.0                                                                          */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1    9/28/2020  SF       Change config for 800B CV-R                                                                        */
/*  800B-2    1/25/2021  SF       Change config for 800B 1A                                                                          */
/*  840B-1    4/14/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1    6/14/2021  RO       Change config for 893B CV                                                                          */
/*  178D-1    8/04/2021  RO       Change config for 178D CV                                                                          */
/*  300D-1    9/06/2021  RO       Change config for 300D CV                                                                          */
/*  460B-1    9/27/2021  RO       Change config for 460B CV                                                                          */
/*  893B-2   11/23/2021  RO       Change config for 893B 1A                                                                          */
/*  840B-2   12/20/2021  RO       Change config for 840B 1A                                                                          */
/*  840B-3    1/24/2022  RO       Change config for 840B MPT                                                                         */
/*  840B-4    2/14/2022  RO       Change config for 840B MPT                                                                         */
/*  178D-2    3/04/2022  RO       Change config for 178D 1A                                                                          */
/*  175D-1    4/06/2022  HA       Change config for 175D 1A                                                                          */
/*  177D227D-1 4/06/2022 SK/HA    Change config for 177D227D 1A                                                                      */
/*  178D-3    4/04/2022  RO       Change config for 178D MPT                                                                         */
/*  178D-4    4/15/2022  RO       Change config for 178D MPT                                                                         */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  200D-1    6/08/2022  RO       Change config for 200D Certified Car                                                               */
/*  200D-2    7/01/2022  RO       Change config for 200D970B Pre1A                                                                   */
/*  220D-1    7/21/2022  RO       Change config for 220D Pre1A                                                                       */
/*  115D117D-1 8/24/2022 RO       Change config for 115D117D 1A                                                                      */
/*  970B-1    8/25/2022  YK       Change config for 970B 1A                                                                          */
/*  115D117D-2 8/31/2022 RO       Change config for 115D117D 1A                                                                      */
/*  296D-1    9/02/2022  HA       Change config for 296D CV                                                                          */
/*  960B-1     9/13/2022 SK       Change config for 960B Pre1A                                                                       */
/*  115D117D-3 9/26/2022 RO       Change config for 115D117D 1A                                                                      */
/*  920B-2    10/07/2022 HA       Change config for 920B CV-R                                                                        */
/*  115D117D-4 10/31/2022 RO      Change config for 115D117D MPT                                                                     */
/*  296D-2    11/03/2022 HA       Change config for 296D Certified Car                                                               */
/*  115D117D-5 11/08/2022 MG      Change config for 115D117D MPT                                                                     */
/*  200D-3    12/02/2022 RO       Change config for 200D MPT                                                                         */
/*  448D-1    12/05/2022 SK       Change config for 448D CV                                                                          */
/*  458D-1     2/01/2023 HA       Change config for 458D Certified Car                                                               */
/*  539D-1    2/16/2023  HA       Change config for 539D CV-R                                                                        */
/*  396D-1    2/21/2023  HA       Change config for 396D Certified Car                                                               */
/*  234D-1    3/14/2023  HA       Change config for 234D239D Certified Car                                                           */
/*  458D-2    4/18/2023  RO       Change config for 448D539D396D234D239D458D 1A                                                      */
/*  960B-2    5/08/2023  RO       Change config for 960B 1A                                                                          */
/*  234D-1    5/22/2023  RO       Change config for 234D239D458D 1A                                                                  */
/*  587D588D-1 6/01/2023 HA       Change config for 587D588D CV                                                                      */
/*  19pfv3-1  10/27/2023 DR       Added steer PTSYS for 19pfv3                                                                       */
/*  19pfv3-2   1/10/2024 HF       Delete u1_g_VardefCfgSpdMax for 19pfv3                                                             */
/*  19pfv3-3   4/03/2024 DR       Delete engine type functions (vareng)3                                                             */
/*  19pfv3-4   4/22/2023 JMH      Deleted steer PTSYS for 19pfv3                                                                     */
/*  19pfv3-5   5/02/2024 GM       Delete Database Field by PID items for 19pfv3                                                      */
/*  19pfv3-6   5/28/2024 TN(DT)   Delete Grade module for 19pfv3                                                                     */
/*  19PFv3-7   7/10/2024 YR       Added HCS for 19pfv3                                                                               */
/*  19PFv3-8  11/ 7/2024 PG       Added vardef_sgauge for 19PFv3 R2.2                                                                */
/*  19PFv3-9  11/18/2024 SH       Added NE_MET and HV_NE for 19pfv3                                                                  */
/*  BEV-1     10/15/2025 SN       Configured for BEVstep3_Rebase                                                                     */
/*                                                                                                                                   */
/*  * TN     = Takashi Nagai, Denso                                                                                                  */
/*  * SF     = Seiya Fukutome, Denso Techno                                                                                          */
/*  * AT     = Ayano Tomimoto, KSE                                                                                                   */
/*  * RO     = Reiya Okuda, KSE                                                                                                      */
/*  * HA     = Hiroki Asano, PRD                                                                                                     */
/*  * SK     = Shotaro Kitayama, PRD                                                                                                 */
/*  * YK     = Yohei Kubota, MSE                                                                                                     */
/*  * MG     = Mei Godo, KSE                                                                                                         */
/*  * DR     = Dyan Reyes, DTPH                                                                                                      */
/*  * HF     = Hinari Fukamachi, KSE                                                                                                 */
/*  * JMH    = James Michael D. Hilarion, DTPH                                                                                       */
/*  * GM     = Glen Monteposo, DTPH                                                                                                  */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * YR     = Yhana Regalario, DTPH                                                                                                 */
/*  * PG     = Patrick Garcia, DTPH                                                                                                  */
/*  * SH     = Sae Hirose, Denso Techno                                                                                              */
/*  * SN     = Shimon Nambu, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
