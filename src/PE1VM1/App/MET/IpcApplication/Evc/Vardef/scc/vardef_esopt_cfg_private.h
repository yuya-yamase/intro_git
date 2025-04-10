/* 2.5.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Vardef Electrical System Option.                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VARDEF_ESOPT_CFG_H
#define VARDEF_ESOPT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_ESOPT_CFG_H_MAJOR                 (2)
#define VARDEF_ESOPT_CFG_H_MINOR                 (5)
#define VARDEF_ESOPT_CFG_H_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "vardef.h"
/* #include "vardef_esopt.h" */ /* vardef_esopt.h is included in vardef_dbf.h" */

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_ESO_AVA_RX_INA                       (0U)                /* Unavailable / u4_gp_vdf_eso_ava : channel bit is reset to 0b */
#define VDF_ESO_AVA_RX_ACT                       (1U)                /* Available   / u4_gp_vdf_eso_ava : channel bit is set to 1b   */
#define VDF_ESO_AVA_RX_UNK                       (2U)                /* Unknown     / u4_gp_vdf_eso_ava : channel bit is kept last   */

#define VDF_ESO_RXC_NUM_MIN                      (2U)
#define VDF_ESO_RXC_MIN_INA                      (VDF_ESO_AVA_RX_INA)
#define VDF_ESO_RXC_MIN_ACT                      (VDF_ESO_AVA_RX_ACT)

#define VDF_ESO_INPUT_TYPE_CAN                   (0U)
#define VDF_ESO_INPUT_TYPE_CXPI                  (1U)
#define VDF_ESO_INPUT_TYPE_ETH                   (2U)
#define VDF_ESO_INPUT_TYPE_OTHER                 (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                 u2_tim_elpsd;
    U1                 u1_rxc_start;
    U1                 u1_ava_rx;
}ST_VDF_ESO_RX;

typedef struct{
    U1 ( * const       fp_u1_AVA_RX)(void);                          /* Return VDF_ESO_AVA_RX_XXX                                    */

    U2                 u2_eso_ch;
    U1                 u1_input_type;
    U2                 u2_msg_rx;                                    /* Com/Message Idx                                              */
    U2                 u2_vom_act;                                   /* Vehicle Operation Mode                                       */
    U2                 u2_rxc_peri;                                  /* Rx Counting Period  Max.= VDF_ESO_RXC_TOC_MAX                */

    U2                 u2_rxc_min[VDF_ESO_RXC_NUM_MIN]; 
}ST_VDF_ESO_CH;

typedef struct{
    U4                 u4_ini;                                       /* channel bits to be set as initial via Diag SID 0x31          */
    U4                 u4_nvm;                                       /* channel bits to be retained on NvM                           */
    U4                 u4_unk;                                       /* channel bits to be set if NvM is unknown                     */
    U4                 u4_rx;                                        /* channel bits to be rxed                                      */
    U2                 u2_nid;                                       /* NvMC ID                                                      */
    U2                 u2_bid;                                       /* RIM ID                                                       */
}ST_VDF_ESO_AVA;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern ST_VDF_ESO_RX          st_gp_vdf_eso_rx[];                    /* The size is equal to u2_g_VDF_ESO_NUM_RX                     */
extern U4                     u4_gp_vdf_eso_ava[];                   /* The size is equal to u1_g_VDF_ESO_NOW_AVA                    */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_VardefEsOptCfgInit(void);

U1      u1_g_VardefEsOptCfgCanRxEvcnt(const U2 u2_a_MSG_ID);
U1      u1_g_VardefEsOptCfgEthRxEvcnt(const U2 u2_a_MSG_ID);

U1      u1_g_VardefEsOptCfgAvaByAVN(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_VDF_ESO_CH    st_gp_VDF_ESO_CH[];                    /* The size is equal to u2_g_VDF_ESO_NUM_RX                     */
extern const U2               u2_g_VDF_ESO_NUM_RX;
extern const U2               u2_g_VDF_ESO_NUM_RX_BY_RUN;

extern const ST_VDF_ESO_AVA   st_gp_VDF_ESO_AVA[];                   /* The size is equal to u1_g_VDF_ESO_NOW_AVA                    */
extern const U1               u1_g_VDF_ESO_NOW_AVA;

extern const U2               u2_g_VDF_ESO_RES_TOUT;

extern const U1               u1_g_VDF_ESO_RXC_INT;
extern const U1               u1_g_VDF_ESO_RXC_MAX;

#endif      /* VARDEF_ESOPT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  vardef_esopt.c                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
