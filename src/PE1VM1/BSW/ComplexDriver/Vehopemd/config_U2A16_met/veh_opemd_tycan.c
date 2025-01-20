/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode for Toyota                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TYCAN_C_MAJOR                  (1)
#define VEH_OPEMD_TYCAN_C_MINOR                  (3)
#define VEH_OPEMD_TYCAN_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "veh_opemd_cfg_private.h"

#include "iohw_diflt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEH_OPEMD_TYCAN_C_MAJOR != VEH_OPEMD_CFG_H_MAJOR) || \
     (VEH_OPEMD_TYCAN_C_MINOR != VEH_OPEMD_CFG_H_MINOR) || \
     (VEH_OPEMD_TYCAN_C_PATCH != VEH_OPEMD_CFG_H_PATCH))
#error "veh_opemd_tycan.c and veh_opemd_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VEH_OPEMD_TYCAN_C_MAJOR != VEH_OPEMD_XMODE_H_MAJOR) || \
     (VEH_OPEMD_TYCAN_C_MINOR != VEH_OPEMD_XMODE_H_MINOR) || \
     (VEH_OPEMD_TYCAN_C_PATCH != VEH_OPEMD_XMODE_H_PATCH))
#error "veh_opemd_tycan.c and veh_opemd_xmode.h : source and header files are inconsistent!"
#endif

#if ((!defined(__VEH_OPEMD_OEM__)             ) || \
     (__VEH_OPEMD_OEM__ != VEH_OPEMD_OEM_TYCAN))
#error "veh_opemd_tycan.c and veh_opemd_xmode.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4   u4_mdbit_chk;
    U4   u4_mdbit_act;
    U4   u4_evtbit_start;
    U2   u2_tm_rst;
    U2   u2_tm_wk;
}ST_VEH_OPEMD_TM;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TM_MAX                         (0xfffeU)
#define VEH_OPEMD_TM_STOP                        (0xffffU)

#define VEH_OPEMD_NUM_TM_ELPSD                   (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_VEH_OPEMD_TYCAN_IDLST()               ((U1)FALSE)
#define VEH_OPEMD_TYCAN_IDLST_ENA                (TRUE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2                       u2_sp_veh_opemd_tmelpsd[VEH_OPEMD_NUM_TM_ELPSD];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_VehopemdCfgAccchk(const U4 u4_a_MDBIT);
static U4      u4_s_VehopemdCfgStachk(const U4 u4_a_MDBIT, const U1 u1_a_IGON);
static U4      u4_s_VehopemdCfgRdychk(const U4 u4_a_MDBIT, const U1 u1_a_IGON);

static U4      u4_s_VehopemdCfgIgpchk(const U4 u4_a_MDBIT);
static U4      u4_s_VehopemdCfgPbachk(const U4 u4_a_MDBIT);
static void    vd_s_VehopemdTmUpdt(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT);

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
    U4                             u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0; u4_t_lpcnt < (U4)VEH_OPEMD_NUM_TM_ELPSD; u4_t_lpcnt++){
        u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] = (U2)VEH_OPEMD_TM_STOP;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgWkupInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgWkupInit(void)
{
    U4                             u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0; u4_t_lpcnt < (U4)VEH_OPEMD_NUM_TM_ELPSD; u4_t_lpcnt++){
        u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] = (U2)VEH_OPEMD_TM_STOP;
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evtbit)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evtbit)
{
    static const U1                u1_s_VEH_OPEMD_LSR_TO_OFF = (U1)VEH_OPEMD_EVTLSB_TO_OFF - (U1)VEH_OPEMD_MDLSB_FIELDS;
    static const U1                u1_s_VEH_OPEMD_LSR_TO_ON  = (U1)VEH_OPEMD_EVTLSB_TO_ON  - (U1)VEH_OPEMD_MDLSB_FIELDS;

    U4                             u4_t_mdbit;
    U4                             u4_t_bit;
    U4                             u4_t_evt;
    U1                             u1_t_igon;
    U1                             u1_t_msgtout;
    U1                             u1_t_sgnl;

    u4_t_mdbit = (U4)0U;
    u1_t_igon  = (U1)FALSE;
    /*------------------------------------------------------------*/
    u1_t_msgtout = (U1)Com_GetIPDUStatus(MSG_BDC1S81_RXCH0);
    u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_msgtout == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO5, &u1_t_sgnl);
        if(u1_t_sgnl    == (U1)TRUE){
            u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_IGN;
            u1_t_igon  = (U1)TRUE;
        }
    }
    /*------------------------------------------------------------*/

    u4_t_mdbit |= u4_s_VehopemdCfgStachk(u4_a_MDBIT, u1_t_igon);
    u4_t_mdbit |= u4_s_VehopemdCfgAccchk(u4_a_MDBIT);
    u4_t_mdbit |= u4_s_VehopemdCfgIgpchk(u4_a_MDBIT);
    u4_t_mdbit |= u4_s_VehopemdCfgRdychk(u4_a_MDBIT, u1_t_igon);
    u4_t_mdbit |= u4_s_VehopemdCfgPbachk(u4_a_MDBIT);

    u4_t_bit = u4_t_mdbit & ((U4)VEH_OPEMD_MDBIT_IGN | (U4)VEH_OPEMD_MDBIT_STA);
    if(u4_t_bit == (U4)VEH_OPEMD_MDBIT_IGN){      /* sta = off, ign = on         */
        u4_t_mdbit |= (U4)VEH_OPEMD_MDBIT_NRML;
    }
    else if(u4_t_bit != (U4)0U){                   /* sta = on,  ign = don't care */
        u4_t_mdbit |= (U4)VEH_OPEMD_MDBIT_CRNK;
    }
    else{
        /* no processing */
    }

    u4_t_bit = u4_a_MDBIT ^ u4_t_mdbit;
    u4_t_evt  =  ((u4_t_bit & u4_a_MDBIT) & (U4)VEH_OPEMD_MDBIT_FIELDS) << u1_s_VEH_OPEMD_LSR_TO_OFF;
    u4_t_evt |= (((u4_t_bit & u4_t_mdbit) & (U4)VEH_OPEMD_MDBIT_FIELDS) << u1_s_VEH_OPEMD_LSR_TO_ON );

    vd_s_VehopemdTmUpdt(u4_t_mdbit, u4_t_evt);

    (*u4_ap_evtbit) = u4_t_evt;

    return(u4_t_mdbit);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehopemdTmElapsed(const U1 u1_a_TM, const U2 u2_a_THRSHLD)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehopemdTmElapsed(const U1 u1_a_TM, const U2 u2_a_THRSHLD)
{
    U1                             u1_t_elapsed;

    u1_t_elapsed = (U1)FALSE;
    if(u1_a_TM < (U1)VEH_OPEMD_NUM_TM_ELPSD){
        if((u2_sp_veh_opemd_tmelpsd[u1_a_TM] < (U2)VEH_OPEMD_TM_STOP) &&
           (u2_sp_veh_opemd_tmelpsd[u1_a_TM] >= u2_a_THRSHLD        )){
            u1_t_elapsed = (U1)TRUE;
        }
    }

    return(u1_t_elapsed);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_VehopemdCfgAccchk(const U4 u4_a_MDBIT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VehopemdCfgAccchk(const U4 u4_a_MDBIT)
{
#if (defined(MSG_BDC1S81_RXCH0) && defined(ComConf_ComSignal_VPSINFO3))
    U4                             u4_t_mdbit;
    U1                             u1_t_msgtout;
    U1                             u1_t_sgnl;

    u4_t_mdbit = (U4)0U;
    u1_t_msgtout = (U1)Com_GetIPDUStatus(MSG_BDC1S81_RXCH0);
    u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_msgtout == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO3, &u1_t_sgnl);
        if(u1_t_sgnl    == (U1)TRUE){
            u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_ACC;
        }
    }

    return(u4_t_mdbit);
#else
    return((U4)0U);
#endif
}
/*===================================================================================================================================*/
/*  static U4      u4_s_VehopemdCfgStachk(const U4 u4_a_MDBIT, const U1 u1_a_IGON)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VehopemdCfgStachk(const U4 u4_a_MDBIT, const U1 u1_a_IGON)
{
#if ((defined(MSG_ENG1G92_RXCH0) && (defined(ComConf_ComSignal_B_ST) || defined(ComConf_ComSignal_B_TC))) || \
     (defined(MSG_ECO1S90_RxCH0) && defined(ComConf_ComSignal_MSTART)))
    U4                             u4_t_mdbit;
    U1                             u1_t_msgtout;
/*    U1                             u1_t_sgnl; */
/*    U1                             u1_t_idlest; */

    u4_t_mdbit = (U4)0U;
    if(u1_a_IGON == (U1)TRUE){
/*        u1_t_idlest = u1_VEH_OPEMD_TYCAN_IDLST(); */

#if (defined(MSG_ENG1G92_RXCH0) && (defined(ComConf_ComSignal_B_ST) || defined(ComConf_ComSignal_B_TC)))
        u1_t_msgtout = (U1)Com_GetIPDUStatus(MSG_ENG1G92_RXCH0);
        u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgtout == (U1)0U){
#ifdef ComConf_ComSignal_B_ST
/*            (void)Com_ReceiveSignal(ComConf_ComSignal_B_ST, &u1_t_sgnl); */
/*            if((u1_t_sgnl   == (U1)TRUE                     ) &&         */
/*               (u1_t_idlest != (U1)VEH_OPEMD_TYCAN_IDLST_ENA)){          */
/*                u4_t_mdbit |= (U4)VEH_OPEMD_MDBIT_STA;                   */
/*            }                                                            */
#endif /* #ifdef ComConf_ComSignal_B_ST */
#ifdef ComConf_ComSignal_B_TC
            (void)Com_ReceiveSignal(ComConf_ComSignal_B_TC, &u1_t_sgnl);
            if(u1_t_sgnl == (U1)TRUE){
                u4_t_mdbit |= (U4)VEH_OPEMD_MDBIT_TST;
            }
#endif /* #ifdef ComConf_ComSignal_B_TC */
        }
#endif

#if (defined(MSG_ECO1S90_RxCH0) && defined(ComConf_ComSignal_MSTART))
/*        u1_t_msgtout = (U1)Com_GetIPDUStatus(MSG_ECO1S90_RxCH0);      */
/*        u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);             */
/*        (void)Com_ReceiveSignal(ComConf_ComSignal_MSTART, &u1_t_sgnl); */
/*        if((u1_t_msgtout == (U1)0U                       ) &&          */
/*           (u1_t_sgnl    == (U1)TRUE                     ) &&          */
/*           (u1_t_idlest  == (U1)VEH_OPEMD_TYCAN_IDLST_ENA)){           */
/*            u4_t_mdbit |= (U4)VEH_OPEMD_MDBIT_STA;                     */
/*        }                                                              */
#endif
    }

    return(u4_t_mdbit);
#else
    return((U4)0U);
#endif
}
/*===================================================================================================================================*/
/*  static U4      u4_s_VehopemdCfgRdychk(const U4 u4_a_MDBIT, const U1 u1_a_IGON)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VehopemdCfgRdychk(const U4 u4_a_MDBIT, const U1 u1_a_IGON)
{
#if (defined(MSG_EHV1S90_Rx_CH0) && defined(ComConf_ComSignal_RDYIND))
    U4                             u4_t_mdbit;
    U1                             u1_t_msgtout;
    U1                             u1_t_sgnl;

    u4_t_mdbit = (U4)0U;
    if(u1_a_IGON == (U1)TRUE){
        u1_t_msgtout = (U1)Com_GetIPDUStatus(MSG_EHV1S90_Rx_CH0);
        u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        (void)Com_ReceiveSignal(ComConf_ComSignal_RDYIND, &u1_t_sgnl);
        if((u1_t_msgtout == (U1)0U  ) &&
           (u1_t_sgnl    == (U1)TRUE)){
            u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_RDY;
        }
    }

    return(u4_t_mdbit);
#else
    return((U4)0U);
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_VehopemdTmUpdt(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VehopemdTmUpdt(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
    static const ST_VEH_OPEMD_TM   st_sp_VEH_OPEMD_TM_ELPSD[VEH_OPEMD_NUM_TM_ELPSD] = {
        /* Vehicle Operaional Mode = Normal */
        {
            (U4)VEH_OPEMD_MDBIT_IGN | (U4)VEH_OPEMD_MDBIT_STA,                  /* u4_mdbit_chk    */
            (U4)VEH_OPEMD_MDBIT_IGN,                                            /* u4_mdbit_act    */
            (U4)VEH_OPEMD_EVTBIT_IGN_TO_ON | (U4)VEH_OPEMD_EVTBIT_STA_TO_OFF,   /* u4_evtbit_start */
            (U2)VEH_OPEMD_TM_STOP,                                              /* u2_tm_rst       */
            (U2)VEH_OPEMD_TM_STOP                                               /* u2_tm_wk        */
        },
        /* Ignition-Off                     */
        {
            (U4)VEH_OPEMD_MDBIT_IGN,                                            /* u4_mdbit_chk    */
            (U4)0x00000000U,                                                    /* u4_mdbit_act    */
            (U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF,                                    /* u4_evtbit_start */
            (U2)VEH_OPEMD_TM_MAX,                                               /* u2_tm_rst       */
            (U2)VEH_OPEMD_TM_MAX                                                /* u2_tm_wk        */
        }
    };

    U4                             u4_t_chkbit;
    U4                             u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0; u4_t_lpcnt < (U4)VEH_OPEMD_NUM_TM_ELPSD; u4_t_lpcnt++){

        u4_t_chkbit = u4_a_MDBIT & st_sp_VEH_OPEMD_TM_ELPSD[u4_t_lpcnt].u4_mdbit_chk;
        if(u4_t_chkbit == st_sp_VEH_OPEMD_TM_ELPSD[u4_t_lpcnt].u4_mdbit_act){

            u4_t_chkbit = u4_a_EVTBIT & st_sp_VEH_OPEMD_TM_ELPSD[u4_t_lpcnt].u4_evtbit_start;
            if((u4_t_chkbit                         != (U4)0U               ) ||
               (u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] >= (U2)VEH_OPEMD_TM_STOP)){
                u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] = (U2)0U;
            }
            else if(u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] < (U2)VEH_OPEMD_TM_MAX){
                u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt]++;
            }
            else{
                /* no processing */
            }
        }
        else{
            u2_sp_veh_opemd_tmelpsd[u4_t_lpcnt] = (U2)VEH_OPEMD_TM_STOP;
        }
    }
}
/*===================================================================================================================================*/

#if (defined(MSG_BDC1S81_RXCH0) && defined(ComConf_ComSignal_VPSINFO4))

/*===================================================================================================================================*/
/*  static U4      u4_s_VehopemdCfgIgpchk(const U4 u4_a_MDBIT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VehopemdCfgIgpchk(const U4 u4_a_MDBIT)
{
    U4                             u4_t_mdbit;
    U1                             u1_t_msgtout;
    U1                             u1_t_sgnl;

    u4_t_mdbit    = (U4)0U;
    u1_t_msgtout  = (U1)Com_GetIPDUStatus(MSG_BDC1S81_RXCH0);
    u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO4, &u1_t_sgnl);
    if((u1_t_msgtout == (U1)0U  ) &&
       (u1_t_sgnl    == (U1)TRUE)){
        u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_IGNP;
    }
    return(u4_t_mdbit);
}
#endif

#if (defined(MSG_BDC1S81_RXCH0) && defined(ComConf_ComSignal_VPSINFO2))

/*===================================================================================================================================*/
/*  static U4      u4_s_VehopemdCfgPbachk(const U4 u4_a_MDBIT)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VehopemdCfgPbachk(const U4 u4_a_MDBIT)
{
    U4                             u4_t_mdbit;
    U1                             u1_t_msgtout;
    U1                             u1_t_sgnl_02;

    u4_t_mdbit    = (U4)0U;
    u1_t_msgtout  = (U1)Com_GetIPDUStatus(MSG_BDC1S81_RXCH0);
    u1_t_msgtout &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl_02     = (U1)0U;

    if(u1_t_msgtout == (U1)0U  ){
        (void)Com_ReceiveSignal(ComConf_ComSignal_VPSINFO2, &u1_t_sgnl_02);
        if(u1_t_sgnl_02    == (U1)TRUE){
            u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_PBA;
        }
    }
    return(u4_t_mdbit);
}
#endif

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
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HU   = Hayato Usui, Denso Create                                                                                               */
/*  * ST   = Satoshi Tanaka, Denso Create                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
