/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode for Toyota                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TYBEV3_C_MAJOR                 (2)
#define VEH_OPEMD_TYBEV3_C_MINOR                 (1)
#define VEH_OPEMD_TYBEV3_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "veh_opemd_cfg_private.h"
#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEH_OPEMD_TYBEV3_C_MAJOR != VEH_OPEMD_TYBEV3_H_MAJOR) || \
     (VEH_OPEMD_TYBEV3_C_MINOR != VEH_OPEMD_TYBEV3_H_MINOR) || \
     (VEH_OPEMD_TYBEV3_C_PATCH != VEH_OPEMD_TYBEV3_H_PATCH))
#error "veh_opemd_tybev3.c and veh_opemd_xmode.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_VPS_NUM_CHK                    (6U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_MDLSB_NM_0                     (31U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2              u2_crit;
    U2              u2_mdbit;
}ST_VEH_OPEMD_VPS_CHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_s_veh_opemd_unk_tocnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline U2      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgRstInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgRstInit(void)
{
    u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgWkupInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgWkupInit(void)
{
    u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
}
/*===================================================================================================================================*/
/*  U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evbit)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evbit)
{
    static const ST_VEH_OPEMD_VPS_CHK    st_sp_VEH_OPEMD_VPS_CHK[VEH_OPEMD_VPS_NUM_CHK] = {
        {(U2)0x0062U, (U2)0x0068U},   /*              PBA        | IGCT | IGBD */
        {(U2)0x0022U, (U2)0x0028U},   /*              PBA        | IGCT        */
        {(U2)0x0076U, (U2)0x007aU},   /* ACC |        PBA | IG_R | IGCT | IGBD */
        {(U2)0x007eU, (U2)0x007eU},   /* ACC | IG_P | PBA | IG_R | IGCT | IGBD */
        {(U2)0x0066U, (U2)0x006aU},   /* ACC |        PBA        | IGCT | IGBD */
        {(U2)0x0002U, (U2)0x0008U}    /*              PBA                      */
    };

    static const U2                      u2_s_VEH_OPEMD_UNK_TOUT = (U2)3000U / (U2)10U;

    U4                                   u4_t_mdbit;
    U4                                   u4_t_evbit;
    U4                                   u4_t_ev_off;
    U4                                   u4_t_ev_on;

    U2                                   u2_t_vps_chk;
    U1                                   u1_t_vps_rx;
    U1                                   u1_t_ipdu_st;

    u4_t_mdbit   = u4_a_MDBIT & (U4)VEH_OPEMD_MDBIT_FIELDS;
    u1_t_ipdu_st = (U1)Com_GetIPDUStatus((U2)MSG_BDC1S81_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_ipdu_st == (U1)0U){ 

        u1_t_vps_rx   = (U1)0U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO1, &u1_t_vps_rx);
        u2_t_vps_chk  = (U2)u1_t_vps_rx;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 1U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 2U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 3U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 4U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO6, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 5U;
        Com_ReceiveSignal(ComConf_ComSignal_VPSINFO7, &u1_t_vps_rx);
        u2_t_vps_chk |= (U2)u1_t_vps_rx << 6U;

        u2_t_vps_chk = u2_s_VehopemdVpschk(u2_t_vps_chk, &st_sp_VEH_OPEMD_VPS_CHK[0U], (U2)VEH_OPEMD_VPS_NUM_CHK);

        if(u2_t_vps_chk != (U2)VEH_OPEMD_MDBIT_UNK){
            u4_t_mdbit = (U4)u2_t_vps_chk;
            u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
        }
        else if(u2_s_veh_opemd_unk_tocnt >= (U2)U2_MAX){
            u2_s_veh_opemd_unk_tocnt = (U2)0U;
        }
        else if(u2_s_veh_opemd_unk_tocnt >= u2_s_VEH_OPEMD_UNK_TOUT){
         /* u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_UNK; */
        }
        else{
            u2_s_veh_opemd_unk_tocnt++;
        }
    }
    else if(u1_t_ipdu_st == (U1)COM_NO_RX){
        u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    }
    else{
     /* u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_UNK; */
        u2_s_veh_opemd_unk_tocnt = (U2)U2_MAX;
    }

    u4_t_evbit  = u4_a_MDBIT ^ u4_t_mdbit;
    u4_t_ev_off = ((u4_t_evbit & u4_a_MDBIT) & (U4)VEH_OPEMD_MDBIT_FIELDS) << 16U;
    u4_t_ev_on  = ((u4_t_evbit & u4_t_mdbit) & (U4)VEH_OPEMD_MDBIT_FIELDS);

    (*u4_ap_evbit) = u4_t_ev_off | u4_t_ev_on;

    return(u4_t_mdbit);
}
/*===================================================================================================================================*/
/*  static inline U4      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK)       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U2      u2_s_VehopemdVpschk(const U2 u2_a_RX, const ST_VEH_OPEMD_VPS_CHK * st_ap_CHK, const U2 u2_a_NUM_CHK)
{
    U4                             u4_t_lpcnt;
    U2                             u2_t_chk;

    u2_t_chk = (U2)VEH_OPEMD_MDBIT_UNK;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u2_a_NUM_CHK; u4_t_lpcnt++){
        if(u2_a_RX == st_ap_CHK[u4_t_lpcnt].u2_crit){
            u2_t_chk = st_ap_CHK[u4_t_lpcnt].u2_mdbit;
            break;
        }
    }

    return(u2_t_chk);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 3/2015  TN       New.                                                                                               */
/*  1.1.0     3/23/2015  TN       Timer Function was implemented                                                                     */
/*  1.2.0    11/ 2/2017  TN       Design Change : vd_s_VehopemdTmUpdt was moved from veh_opemd.c to veh_opemd_tycan.c.               */
/*  1.2.1     6/23/2020  HU       QAC warnings were fixed.                                                                           */
/*  1.3.0    12/ 7/2020  ST       AUBIST/CAN, COM v1.0.6 -> v1.1.5                                                                   */
/*  2.0.0     2/ 3/2025  ST       Supported vehicle power state.                                                                     */
/*  2.1.0     2/ 7/2025  TN       BEVStep3 Vehicle Power State requirement was implemented.                                          */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HU   = Hayato Usui, Denso Create                                                                                               */
/*  * ST   = Satoshi Tanaka, Denso Create                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
