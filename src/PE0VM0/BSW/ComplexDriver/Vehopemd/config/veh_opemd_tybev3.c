/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode for Toyota                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TYCAN_C_MAJOR                  (2)
#define VEH_OPEMD_TYCAN_C_MINOR                  (0)
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
#error "veh_opemd_tybev3.c and veh_opemd_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VEH_OPEMD_TYCAN_C_MAJOR != VEH_OPEMD_XMODE_H_MAJOR) || \
     (VEH_OPEMD_TYCAN_C_MINOR != VEH_OPEMD_XMODE_H_MINOR) || \
     (VEH_OPEMD_TYCAN_C_PATCH != VEH_OPEMD_XMODE_H_PATCH))
#error "veh_opemd_tybev3.c and veh_opemd_xmode.h : source and header files are inconsistent!"
#endif

#if ((!defined(__VEH_OPEMD_OEM__)             ) || \
     (__VEH_OPEMD_OEM__ != VEH_OPEMD_OEM_TYCAN))
#error "veh_opemd_tybev3.c and veh_opemd_xmode.h : source and header files are inconsistent!"
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

typedef struct{
    U4   u4_powsts_bit;
    U2   u2_jdg_signal;
}ST_VEH_OPEMD_SP_STS;

typedef struct{
    U4   u4_powsts_bit;
    U1   u1_jdg_signal;
}ST_VEH_OPEMD_BASIC_STS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TM_MAX                         (0xfffeU)
#define VEH_OPEMD_TM_STOP                        (0xffffU)

#define VEH_OPEMD_NUM_TM_ELPSD                   (2U)

#define VEH_OPEMD_POWSTS_MSG                     (MSG_BDC1S81_RXCH0)
#define VEH_OPEMD_POWSTS_MSG_DLC                 (32U)
#define VEH_OPEMD_SPPOWSTS_NUM                   (8U)
#define VEH_OPEMD_BCPOWSTS_NUM                   (7U)
#define VEH_OPEMD_VPSINF_MASK                    (0x7FU)

#define VEH_OPEMD_POWSTS_MASK                    (0xFFFFFFFEU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_VEH_OPEMD_TYCAN_IDLST()               ((U1)FALSE)
#define VEH_OPEMD_TYCAN_IDLST_ENA                (TRUE)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

U4                              u4_g_vehopemd_sysbit                    __attribute__((section(".bss_SHARE_COMPLEX_VEHOPEMD_SYSSTS")));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

static const ST_VEH_OPEMD_SP_STS   st_gp_VEOPE_SP_STS_INFO[VEH_OPEMD_SPPOWSTS_NUM] = {
    /* u4_powsts_bit                              u2_jdg_signal                                */
    /*                                            (BDC1S81 RcvSignal byte6|byte4)              */
    {(U4)VEH_OPEMD_MDBIT_PDM,                     (U2)0x0001U},
    {(U4)VEH_OPEMD_MDBIT_OTA1,                    (U2)0x0102U},
    {(U4)VEH_OPEMD_MDBIT_OTA2,                    (U2)0x0202U},
    {(U4)VEH_OPEMD_MDBIT_OTA3,                    (U2)0x0302U},
    {(U4)VEH_OPEMD_MDBIT_OTA4,                    (U2)0x0402U},
    {(U4)VEH_OPEMD_MDBIT_WRP,                     (U2)0x0003U},
    {(U4)VEH_OPEMD_MDBIT_EDS,                     (U2)0x0004U},
    {(U4)VEH_OPEMD_MDBIT_PAO,                     (U2)0x0005U}
};

static const ST_VEH_OPEMD_BASIC_STS   st_gp_VEOPE_BC_STS_INFO[VEH_OPEMD_BCPOWSTS_NUM] = {
    /* u4_powsts_bit                              u1_jdg_signal                                */
    /*                                            (BDC1S81 RcvSignal byte3)                    */
    {(U4)VEH_OPEMD_MDBIT_PAR_HVHC,                (U1)0x62U},
    {(U4)VEH_OPEMD_MDBIT_PAR_HV,                  (U1)0x22U},
    {(U4)VEH_OPEMD_MDBIT_POE,                     (U1)0x76U},
    {(U4)VEH_OPEMD_MDBIT_PON,                     (U1)0x7EU},
    {(U4)VEH_OPEMD_MDBIT_RID,                     (U1)0x66U},
    {(U4)VEH_OPEMD_MDBIT_PAR,                     (U1)0x02U},
    {(U4)VEH_OPEMD_MDBIT_CHK,                     (U1)0x01U}
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
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
    u4_g_vehopemd_sysbit = (U4)VEH_OPEMD_MDBIT_CHK;
}
/*===================================================================================================================================*/
/*  void    vd_g_VehopemdCfgWkupInit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehopemdCfgWkupInit(void)
{
    u4_g_vehopemd_sysbit = (U4)VEH_OPEMD_MDBIT_CHK;
}
/*===================================================================================================================================*/
/*  U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evtbit)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VehopemdCfgMdupdt(const U4 u4_a_MDBIT, U4 * u4_ap_evtbit)
{

    U4                             u4_t_mdbit;
    U4                             u4_t_bit;
    U4                             u4_t_evt;
    U4                             u4_t_loop_cnt;
    U2                             u2_t_powsts_rcv_data;
    U1                             u1_t_msgtout;
    U1                             u1_tp_powsts_data[VEH_OPEMD_POWSTS_MSG_DLC];


    u2_t_powsts_rcv_data = (U2)0U;
    u4_t_mdbit = (U4)0U;

    u1_t_msgtout = (U1)Com_GetIPDUStatus(VEH_OPEMD_POWSTS_MSG);
    
    if((U1)(u1_t_msgtout & (U1)COM_TIMEOUT) != (U1)0U){
        u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_PAR;
    } else if((U1)(u1_t_msgtout & (U1)COM_NO_RX) != (U1)0U){
        u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_CHK;
    } else {
        (void)Com_ReadIPDU((U2)VEH_OPEMD_POWSTS_MSG,&u1_tp_powsts_data[0]);
        
        /*---------------------------------------------------------------------------------*/
        /* Extracting received values ecessary to determine the vehicle power state        */
        /* The data sequence is as follows                                                 */
        /*  (U2)byte6 | byte4                                                              */
        /*---------------------------------------------------------------------------------*/
        u2_t_powsts_rcv_data = (U2)((U2)u1_tp_powsts_data[6] << 8U);
        u2_t_powsts_rcv_data |= (U2)u1_tp_powsts_data[4];
    
        for(u4_t_loop_cnt = (U4)0U;u4_t_loop_cnt < (U4)VEH_OPEMD_SPPOWSTS_NUM;u4_t_loop_cnt++){
            if(u2_t_powsts_rcv_data  == st_gp_VEOPE_SP_STS_INFO[u4_t_loop_cnt].u2_jdg_signal){
                u4_t_mdbit |= st_gp_VEOPE_SP_STS_INFO[u4_t_loop_cnt].u4_powsts_bit;
                break;
            }
        }
        
        for(u4_t_loop_cnt = (U4)0U;u4_t_loop_cnt < (U4)VEH_OPEMD_BCPOWSTS_NUM;u4_t_loop_cnt++){
            if((u1_tp_powsts_data[3] & (U1)VEH_OPEMD_VPSINF_MASK)  == st_gp_VEOPE_BC_STS_INFO[u4_t_loop_cnt].u1_jdg_signal){
                u4_t_mdbit |= st_gp_VEOPE_BC_STS_INFO[u4_t_loop_cnt].u4_powsts_bit;
                break;
            }
        }
        
        /* If the value is outside the specification, the value being Checking is set.*/
        if(u4_t_mdbit == (U4)0U){
            u4_t_mdbit = (U4)VEH_OPEMD_MDBIT_CHK;
        }
    }

    /*-------------------------------*/
    /* u4_t_evt                      */
    /* ON->OFF event :bit31-bit16    */
    /* OFF->ON event :bit15-bit0     */
    /*-------------------------------*/
    u4_t_bit = u4_a_MDBIT ^ u4_t_mdbit;
    u4_t_evt  =  ((u4_t_bit & u4_a_MDBIT) & (U4)VEH_OPEMD_MDBIT_FIELDS) << 16U;
    u4_t_evt |= ((u4_t_bit & u4_t_mdbit) & (U4)VEH_OPEMD_MDBIT_FIELDS);

    (*u4_ap_evtbit) = u4_t_evt;

    /*-------------------------------------------------------------------*/
    /* Access to 4byte RAM is completed with one instruction.            */
    /* There is no interrupt during access, SPINLOCK is not required.    */
    /*-------------------------------------------------------------------*/
    u4_g_vehopemd_sysbit = u4_t_mdbit;
    /*-------------------------------------------------------------------*/

    return(u4_t_mdbit);
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
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HU   = Hayato Usui, Denso Create                                                                                               */
/*  * ST   = Satoshi Tanaka, Denso Create                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
