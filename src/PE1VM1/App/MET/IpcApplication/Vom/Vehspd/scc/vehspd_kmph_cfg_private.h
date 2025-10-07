/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vehicle Speed                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VEHSPD_KMPH_CFG_H
#define VEHSPD_KMPH_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_KMPH_CFG_H_MAJOR                  (2)
#define VEHSPD_KMPH_CFG_H_MINOR                  (1)
#define VEHSPD_KMPH_CFG_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#if 0   /* BEV Rebase provisionally */
#include "veh_opemd.h"
#endif   /* BEV Rebase provisionally */
#include "vehspd_kmph.h"
#include "calibration.h"
#include "vardef.h"
#include "memcpy_u2.h"
#include "memfill_u2.h"
#include "lerp_u2.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_OW_TOC_MAX                        (0xfffeU) /* Overwrite Timeout Counter Max.                                         */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_TOL_A_INITIAL_VALUE               (0x3FU)   /* 0x3f is defined in CAN bitassign as default tx value                   */
#define VEHSPD_TOL_B_INITIAL_VALUE               (0)       /* 0x00 is defined in CAN bitassign as default tx value                   */
                                                           /* Since TOLER_B is a signed type variable, The suffix "U" is not added.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_SPDTLRNC_USA_CAN                  (VDF_SPDTLRNC_USA_CAN)
#define VEHSPD_SPDTLRNC_UNR_AUS                  (VDF_SPDTLRNC_UNR_AUS)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEHSPD_CALIB_CORPT                       (CALIB_SP_TOLER_CORPT_NUM)
#define VEHSPD_CORPT                             (VEHSPD_CALIB_CORPT + 1U)      /* Linear completion points used in tolerances.      */
#define VEHSPD_CORPT_NUM                         ((VEHSPD_CORPT * 2U) + 1U)     /* Number of elements in a linear complement array.  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_VEHSPD_CALIB_TOLER_A_USA_CAN          (u1_CALIB_MCUID0256_TOLA_USA_CAN)
#define s1_VEHSPD_CALIB_TOLER_B_USA_CAN          (s1_CALIB_MCUID0257_TOLB_USA_CAN)
#define u1_VEHSPD_CALIB_TOLER_A_UNR_AUS          (u1_CALIB_MCUID0260_TOLA_UNR_AUS)
#define s1_VEHSPD_CALIB_TOLER_B_UNR_AUS          (s1_CALIB_MCUID0261_TOLB_UNR_AUS)
#define u2p_VEHSPD_CALIB_BIAS_USA_CAN            (&u2_CALIB_MCUID0757_SP_USA_CAN[0])
#define u2p_VEHSPD_CALIB_BIAS_UNR_AUS            (&u2_CALIB_MCUID0777_SP_UNR_AUS[0])

#define u1_g_VehspdSpdTlrnc()                    (u1_g_VardefSpdTlrncByPid())

#define vd_g_VehspdMemcpyU2(cpydst, CPYSRC, NUM) (vd_g_MemcpyU2((cpydst), (CPYSRC), (NUM)))
#define vd_g_VehspdMemfillU2(buff, FILL, NUM)    (vd_g_MemfillU2((buff), (FILL), (NUM)))
#define u2_g_VehspdLerpU2(X, MAP)                (u2_g_LerpU2((X),(MAP)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    void  (* const fp_vd_INIT)(void);                                            /* Initialization function                          */
    U1    (* const fp_u1_OPEMD_EVHK)(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT); /* Return : TRUE = initialization, FALSE = Not      */
    U1    (* const fp_u1_KMPH)(U2 * u2_ap_kmph, U4 * u4_ap_odocnt);              /* Return : VEHSPD_STSBIT_XXX                       */
}ST_VEHSPD_IF;

typedef struct{
    U1             u1_toler_a;                                                   /* res. = 0.002 [unitless], offset = 0.940          */
    S1             s1_toler_b;                                                   /* res. = 0.2   [km/h]                              */
    U2             u2p_bias_map[VEHSPD_CORPT_NUM];                               /* A linear complement array used in tolerances     */
}ST_VEHSPD_BIAS_FACT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_VehspdCfgIFidx(void);

void    vd_g_VehspdCfgMedspdComTx(const U2 u2_a_KMPH);
void    vd_g_VehspdCfgTolerXComTx(const ST_VEHSPD_BIAS_FACT * st_ap_FACT);

void    vd_g_VehspdCfgOdoInst(const U4 u4_a_ODO_INST, const U1 u1_a_STSBIT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2                   u2_g_VEHSPD_KMPH_OW_TOUT;

extern const ST_VEHSPD_IF         st_gp_VEHSPD_IF_CFG[];
extern const U1                   u1_g_VEHSPD_IF_NUM_CFG;

#endif      /* VEHSPD_KMPH_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vehspd_kmph.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
