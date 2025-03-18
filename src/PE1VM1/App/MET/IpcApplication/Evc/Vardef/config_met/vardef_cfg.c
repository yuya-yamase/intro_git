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
#include "vardef_ptsrx_milreq_cfg_private.h"
#include "vardef_ds2e.h"
#include "vardef_mmmthd_cfg_private.h"
#include "vardef_navspdlmt_cfg_private.h"
#include "vardef_hcs_cfg_private.h"

#include "locale.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

#include "nvmc_mgr.h"
#if 0   /* BEV BSW provisionally */
#else
#include "nvmc_mgr_cfg_STUB.h"
#endif
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

#include "vardef_esopt.h"
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#else
#include "es_inspect_STUB.h"
#endif

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef VARDEF_PTS_RX_MILREQ_H
const U2                u2_g_VDF_PTS_RX_MILREQ_RIM_U1 = (U2)RIMID_U1_VDF_PTSYS_MILREQ;

const U1                u1_g_VDF_PTS_RX_MILREQ_RXC_INT = (U1)OXCAN_RX_RXEV_CNT_UNK;
const U1                u1_g_VDF_PTS_RX_MILREQ_RXC_MAX = (U1)OXCAN_RX_RXEV_CNT_MAX;
#endif /* #ifdef VARDEF_PTS_RX_MILREQ_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef VARDEF_HCS_H
const U2               u2_g_VDF_HCS_ASCEXT_RIM_U1  = (U2)RIMID_U1_VDF_HCS_ASCEXT;

const U1               u1_g_VDF_HCS_ASCEXT_RXC_INT = (U1)OXCAN_RX_RXEV_CNT_UNK;
const U1               u1_g_VDF_HCS_ASCEXT_RXC_MAX = (U1)OXCAN_RX_RXEV_CNT_MAX;
#endif /* #ifdef VARDEF_HCS_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/

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

    vd_g_VardefPtsRxMilreqBonInit();
    vd_g_VardefDs2EInit();
    vd_g_VardefMmMthdBonInit();
    vd_g_VardefNavSpdLmtBonInit();
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

    vd_g_VardefPtsRxMilreqRstwkInit();
    vd_g_VardefDs2EInit();
    vd_g_VardefMmMthdRstwkInit();
    vd_g_VardefNavSpdLmtRstwkInit();
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
    vd_g_VardefPtsRxMilreqOpemdEvhk(u2_a_EOM);
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
        vd_g_VardefPtsRxMilreqMainTask(u2_a_EOM);     /* vd_g_VardefPtsRxMilreqMainTask shall be invoked every 100 milliseconds */
        vd_g_VardefNavSpdLmtMainTask(u2_a_EOM);       /* vd_g_VardefNavSpdLmtMainTask shall be invoked every 100 milliseconds   */
        vd_g_VardefHcsMainTask(u2_a_EOM);
    }
    else if(u1_a_TSLOT == (U1)VDF_TSLOT_4){
        vd_g_VardefMmMthdMainTask(u2_a_EOM);         /* vd_g_VardefMmMthdMainTask shall be invoked every 100 milliseconds    */
    }
    else{
        /* do nothing */
    }

    vd_g_VardefDs2EMainTask();
}
/*===================================================================================================================================*/
/*  U2      u2_g_VardefCfgEomchk(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_VardefCfgEomchk(void)
{
#if 0   /* BEV BSW provisionally */
#if ((VDF_EOM_ACC_ON != VEH_OPEMD_MDBIT_ACC) || \
     (VDF_EOM_IGR_ON != VEH_OPEMD_MDBIT_IGN))
#error "vardef_fg.c : VDF_EOM_XXX shall be equal to VEH_OPEMD_MDBIT_XXX."
#endif
#else
#if ((VDF_EOM_ACC_ON != VEH_OPEMD_MDBIT_STUB_ACC) || \
     (VDF_EOM_IGR_ON != VEH_OPEMD_MDBIT_IGN))
#error "vardef_fg.c : VDF_EOM_XXX shall be equal to VEH_OPEMD_MDBIT_XXX."
#endif
#endif

#if ((ES_INSPECT_MDBF_NUO_DI != (VDF_EOM_NUO_DI >> 8U)) ||  \
     (ES_INSPECT_MDBF_SI_ACT != (VDF_EOM_SI_ACT >> 8U)))
#error "vardef_fg.c : VDF_EOM_XXX shall be equal to ES_INSPECT_MDBF_XXXX."
#endif

    U2          u2_t_eom;

    u2_t_eom  = (U2)VDF_EOM_PB_ON;
#if 0   /* BEV BSW provisionally */
    u2_t_eom |= (U2)u4_g_VehopemdMdfield() & ((U2)VDF_EOM_ACC_ON | (U2)VDF_EOM_IGR_ON | (U2)VDF_EOM_PBA_ON | (U2)VDF_EOM_IGP_ON);
#else
    u2_t_eom |= (U2)u4_g_VehopemdConvertMdfield() & ((U2)VDF_EOM_ACC_ON | (U2)VDF_EOM_IGR_ON | (U2)VDF_EOM_PBA_ON | (U2)VDF_EOM_IGP_ON);
#endif
#if 0   /* BEV BSW provisionally */
    u2_t_eom |= ((U2)u1_g_ESInspectMdBfield() << 8U);
#endif

    return(u2_t_eom);
}

#ifdef VARDEF_PTS_RX_MILREQ_H

/*===================================================================================================================================*/
/*  U1      u1_g_VardefPtsRxMlrqCfgPtsyschk(U1 * u1_ap_ptsys_rx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefPtsRxMlrqCfgPtsyschk(U1* u1_ap_ptsys_rx)
{
#ifdef ComConf_ComSignal_PTSYS
    (void)Com_ReceiveSignal(ComConf_ComSignal_PTSYS, u1_ap_ptsys_rx);
    return(u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_ENG1G13_RXCH0));
#else
    (*u1_ap_ptsys_rx) = (U1)VDF_PTS_RX_MILREQ_1F_NRX;
    return((U1)OXCAN_RX_RXEV_CNT_UNK);
#endif
}
/*===================================================================================================================================*/

#endif /* #ifdef VARDEF_PTS_RX_MILREQ_H */
/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgMmcProt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgMmcProt(void)
{
    U1  u1_t_mmprt;
    U1  u1_t_sts;

    u1_t_mmprt = (U1)VDF_MMPROT_AUTO;
    
    if(u1_t_mmprt == (U1)VDF_MMPROT_AUTO){
        u1_t_sts = u1_g_VardefMmMthdSts();
        if(u1_t_sts == (U1)VDF_MM_MTHD_MMSUBBUS){
            u1_t_mmprt = (U1)VDF_MMPROT_17CY_MM_SUB_BUS;
        }
        else{
            u1_t_mmprt = (U1)VDF_MMPROT_21CY_ETH_WO_AR;
        }
    }

    return(u1_t_mmprt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgMmMthd(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgMmMthd(void)
{
    U1  u1_t_mmprt;
    U1  u1_t_sts;

    u1_t_mmprt = (U1)VDF_MMPROT_AUTO;
    
    if(u1_t_mmprt == (U1)VDF_MMPROT_AUTO){
        u1_t_sts = u1_g_VardefMmMthdSts();
    }
    else if(u1_t_mmprt == (U1)VDF_MMPROT_21CY_ETH_WO_AR){
        u1_t_sts = (U1)VDF_MM_MTHD_ETHER;
    }
    else{
        u1_t_sts = (U1)VDF_MM_MTHD_MMSUBBUS;
    }
    return(u1_t_sts);
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefCfgSendMmcProt(const U1 u1_a_SIG)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefCfgSendMmcProt(const U1 u1_a_SIG)
{
    U1  u1_t_sig;

    u1_t_sig = u1_a_SIG;
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MMC_PROT, &u1_t_sig);    /* COM Tx STUB delete */
#endif
}


/*===================================================================================================================================*/
/*  U1      u1_g_VardefHcsCfgAscextchk(U1* u1_ap_ascext_rx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefHcsCfgAscextchk(U1* u1_ap_ascext_rx)
{
    (void)Com_ReceiveSignal(ComConf_ComSignal_ASCEXT, u1_ap_ascext_rx);
#if 0   /* BEV BSW provisionally */
    return(u1_g_oXCANRxEvcnt((U2)OXCAN_PDU_RX_CAN_ASC1S90));
#else
    return((U1)OXCAN_RX_RXEV_CNT_UNK);
#endif
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
/*  BEV-1      2/06/2025 SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
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
/*  * SF     = Shiro Furui, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
