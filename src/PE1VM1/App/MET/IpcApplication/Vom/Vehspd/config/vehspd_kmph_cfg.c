/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vehicle Speed                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_KMPH_CFG_C_MAJOR                  (2)
#define VEHSPD_KMPH_CFG_C_MINOR                  (1)
#define VEHSPD_KMPH_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vehspd_kmph_cfg_private.h"
#include "vehspd_can_sp1x_cfg_private.h"

#include "oxcan.h"
#include "odo_km.h"
#include "odo_vslmt.h"
#include "tripcom.h"
#include "tripsnsr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEHSPD_KMPH_CFG_C_MAJOR != VEHSPD_KMPH_CFG_H_MAJOR) || \
     (VEHSPD_KMPH_CFG_C_MINOR != VEHSPD_KMPH_CFG_H_MINOR) || \
     (VEHSPD_KMPH_CFG_C_PATCH != VEHSPD_KMPH_CFG_H_PATCH))
#error "vehspd_kmph_cfg.c and vehspd_kmph_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_MAIN_TICK                         (20U)  /* 20msec */
#define VEHSPD_IF_NUM_CFG                        (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VEHSPD_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (VEHSPD_STSBIT_INVALID != COM_TIMEOUT))
#error "VEHSPD_STSBIT_UNKNOWN shall be equal to COM_NO_RX and VEHSPD_STSBIT_INVALID shall be equal to COM_TIMEOUT."
#endif

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
const U2                   u2_g_VEHSPD_KMPH_OW_TOUT = (U2)5000U / (U2)VEHSPD_MAIN_TICK;  /* Overwrite timeout count (5000ms)         */

const ST_VEHSPD_IF         st_gp_VEHSPD_IF_CFG[VEHSPD_IF_NUM_CFG] = {                    /* Configuration of interfaces              */
    {
        &vd_g_VehspdCanSp1xInit,        /* fp_vd_INIT       */
        &u1_g_VehspdCanSp1xOpemdEvhk,   /* fp_u1_OPEMD_EVHK */
        &u1_g_VehspdCanSp1xKmph         /* fp_u1_KMPH       */
    }
};
const U1                   u1_g_VEHSPD_IF_NUM_CFG = (U1)VEHSPD_IF_NUM_CFG;               /* Number of interfaces configurations      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                   u2_g_VEHSPD_CAN_SP1X_1ST_TOUT = (U2)6600U / (U2)VEHSPD_MAIN_TICK;
                                                                                /* power-on mask 3.0 + sp1 timeout 3.6 = 6.6 seconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdCfgIFidx(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdCfgIFidx(void)
{
    return((U1)0U);
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCfgMedspdComTx(const U2 u2_a_KMPH)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdCfgMedspdComTx(const U2 u2_a_KMPH)
{
    U4                 u4_t_kmph;
    U1                 u1_t_metspd;

    u4_t_kmph = ((U4)u2_a_KMPH + ((U4)VEHSPD_1_KMPH >> 1)) / (U4)VEHSPD_1_KMPH; /* round half */
    if(u4_t_kmph >= (U4)U1_MAX){
        u1_t_metspd = (U1)U1_MAX;
    }
    else{
        u1_t_metspd = (U1)u4_t_kmph;
    }
#if 0   /* BEV Rebase provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MET_SPD, &u1_t_metspd);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCfgTolerXComTx(const ST_VEHSPD_BIAS_FACT * st_ap_FACT)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdCfgTolerXComTx(const ST_VEHSPD_BIAS_FACT * st_ap_FACT)
{
    static const U1    u1_s_VEHSPD_TOLER_A_UNK = (U1)VEHSPD_TOL_A_INITIAL_VALUE;
    static const S1    s1_s_VEHSPD_TOLER_B_UNK = (S1)VEHSPD_TOL_B_INITIAL_VALUE;

    if(st_ap_FACT != vdp_PTR_NA){
#if 0   /* BEV Rebase provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_TOLER_A, &(st_ap_FACT->u1_toler_a));
        (void)Com_SendSignal(ComConf_ComSignal_TOLER_B, &(st_ap_FACT->s1_toler_b));
#endif   /* BEV Rebase provisionally */
    }
    else{
#if 0   /* BEV Rebase provisionally */
        (void)Com_SendSignal(ComConf_ComSignal_TOLER_A, &u1_s_VEHSPD_TOLER_A_UNK);
        (void)Com_SendSignal(ComConf_ComSignal_TOLER_B, &s1_s_VEHSPD_TOLER_B_UNK);
#endif   /* BEV Rebase provisionally */
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCfgOdoInst(const U4 u4_a_ODO_INST, const U1 u1_a_STSBIT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdCfgOdoInst(const U4 u4_a_ODO_INST, const U1 u1_a_STSBIT)
{
    U1                 u1_t_status;
    U1                 u1_t_chk;

    if(u1_a_STSBIT == (U1)VEHSPD_STSBIT_VALID){
        vd_g_OdoVslmtOdoInst(u4_a_ODO_INST);
        vd_g_OdoInst(u4_a_ODO_INST);
    }
    u1_t_status = (U1)TRIPCOM_STSBIT_VALID;

    u1_t_chk = u1_a_STSBIT & ((U1)VEHSPD_STSBIT_UNKNOWN | (U1)VEHSPD_STSBIT_EMSTOP);
    if(u1_t_chk != (U1)0U){
        u1_t_status  = (U1)TRIPCOM_STSBIT_UNKNOWN;
    }
    u1_t_chk = u1_a_STSBIT & (U1)VEHSPD_STSBIT_INVALID;
    if(u1_t_chk != (U1)0U){
        u1_t_status |= (U1)TRIPCOM_STSBIT_INVALID;
    }
    vd_g_TripsnsrGetOdoInst(u4_a_ODO_INST, u1_t_status);
}
/*===================================================================================================================================*/
/*  void    vd_g_VehspdCanSp1xComRxInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VehspdCanSp1xComRxInit(void)
{
#if 0   /* BEV Rebase provisionally */
    Com_InitIPDUStatus((PduIdType)MSG_VSC1G13_RXCH0, ((U1)COM_NO_RX | (U1)COM_TIMEOUT));
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1      u1_g_VehspdCanSp1xComRx(U2 * u2_ap_sp1, U1 * u1_ap_sp1p)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VehspdCanSp1xComRx(U2 * u2_ap_sp1, U1 * u1_ap_sp1p)
{
    U2                 u2_t_sp1;

    u2_t_sp1 = (U2)0U;
#if 0   /* BEV Rebase provisionally */
    (void)Com_ReceiveSignal(ComConf_ComSignal_SP1,  &u2_t_sp1);
    (void)Com_ReceiveSignal(ComConf_ComSignal_SP1P, u1_ap_sp1p);
#endif   /* BEV Rebase provisionally */

    if(u2_t_sp1 >= (U2)VEHSPD_CAN_SP1_MIN){
        *u2_ap_sp1 = u2_t_sp1;
    }

#if 0   /* BEV Rebase provisionally */
    return((U1)Com_GetIPDUStatus((PduIdType)MSG_VSC1G13_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX));
#else   /* BEV Rebase provisionally */
    return((U1)COM_NO_RX);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/15/2017  TN       New.                                                                                               */
/*  1.1.0     3/ 9/2018  TN       vehspd_kmph.c v1.0.0 -> v1.1.0.                                                                    */
/*  1.2.0     3/21/2018  TN       vehspd_kmph.c v1.1.0 -> v1.2.0.                                                                    */
/*  1.3.0     7/ 6/2018  TN       vehspd_kmph.c v1.2.0 -> v1.3.0.                                                                    */
/*  1.4.0     2/28/2019  TN       vehspd_kmph.c v1.3.0 -> v1.4.0.                                                                    */
/*  1.5.0     5/28/2019  TN       vehspd_kmph.c v1.4.0 -> v1.5.0.                                                                    */
/*  1.6.0    10/17/2019  TN       vehspd_kmph.c v1.5.0 -> v1.6.0.                                                                    */
/*  1.7.0     7/ 7/2020  HY       vehspd_kmph.c v1.6.0 -> v1.7.0.                                                                    */
/*  2.0.1    10/18/2021  TA(M)    vehspd_kmph.c v1.7.0 -> v2.0.1                                                                     */
/*  2.1.0    06/06/2024  SM       Corrected the method of calculating the tolerance of the median tolerance to linear imputation.    */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  08/22/2023  SN       Delete Tolerance Information Table                                                                 */
/* 19PFv3-2  01/15/2024  TN(DT)   Change for MCUCONSTv010 Shipping Constant.                                                         */
/* 19PFv3-3  04/17/2024  TN(DT)   Change for 19PFv3 CV Provisional.                                                                  */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * HY   = Hiroshige Yanase, DensoTechno                                                                                           */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SN   = Shimon Nambu, DensoTechno                                                                                               */
/*  * TN(DT) = Tetsushi Nakano, Denso Techno                                                                                         */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
