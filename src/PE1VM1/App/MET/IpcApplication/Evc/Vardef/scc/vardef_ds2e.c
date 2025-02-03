/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Diag Service 0x2E                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DS_2E_C_MAJOR                     (2)
#define VARDEF_DS_2E_C_MINOR                     (3)
#define VARDEF_DS_2E_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_ds2e_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_DS_2E_C_MAJOR != VARDEF_DS_2E_H_MAJOR) || \
     (VARDEF_DS_2E_C_MINOR != VARDEF_DS_2E_H_MINOR) || \
     (VARDEF_DS_2E_C_PATCH != VARDEF_DS_2E_H_PATCH))
#error "vardef_ds2e.c and vardef_ds2e.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_DS_2E_C_MAJOR != VARDEF_DS_2E_CFG_H_MAJOR) || \
     (VARDEF_DS_2E_C_MINOR != VARDEF_DS_2E_CFG_H_MINOR) || \
     (VARDEF_DS_2E_C_PATCH != VARDEF_DS_2E_CFG_H_PATCH))
#error "vardef_ds2e.c and vardef_ds2e_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DS_2E_DST_BI                         (0U)   /* Data Structure Type = Bit               */
#define VDF_DS_2E_DST_NU                         (1U)   /* Date Structure Type = Numeric           */
#define VDF_DS_2E_DST_CMP_NU                     (2U)   /* Date Structure Type = Composite Numeric */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Composite Numeric  */
#define VDF_DS_2E_CMP_NU_NUM                     (1U)
#define VDF_DS_2E_CMP_NU_2209                    (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Composite Numeric DID 0x2209 */
#define VDF_DS_2E_2209_NUM                       (2U)
#define VDF_DS_2E_2209_TDSS                      (0U)   /*  Touch display start sensitivity        */
#define VDF_DS_2E_2209_TO                        (1U)   /*  Time out                               */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                  u1_dst;
    U1                  u1_cmp_nu_did;
}ST_VDF_DS_2E_DST;

typedef struct{
    U1                  u1_num;
    const U4 *          u4_msk;
}ST_VDF_DS_2E_CMP_NU;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4          u4_sp_vdf_ds2e_las_b32[VDF_DS_2E_NUM_DID];
static U1          u1_s_vdf_ds2e_syn_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_VdfDs2ELaschk(const ST_VDF_DS_2E * st_ap_DID , const ST_VDF_DS_2E_DST * st_ap_DST);
static U4      u4_s_VdfDs2ECmpNuLaschk(const U1 u1_a_DID ,const U4 u4_a_B32 ,const U4 u4_a_MAX ,
                                       U4 ( * const fp_u4_a_DEF)(const U1 u1_a_NVM_UNK),const U1 u1_a_NVM_STS);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_VDF_DS_2E_DST    st_sp_VDF_DS_2E_DST[VDF_DS_2E_NUM_DID] = {
    /*  VDF_DS_2E_2002 (0U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2003 (1U)     */
    {
        (U1)VDF_DS_2E_DST_BI,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2004 (2U)     */
    {
        (U1)VDF_DS_2E_DST_BI,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2021 (3U)     */
    {
        (U1)VDF_DS_2E_DST_BI,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2041 (4U)     */
    {
        (U1)VDF_DS_2E_DST_BI,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2042 (5U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2043 (6U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2045 (7U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_20C1 (8U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_20C2 (9U)     */
    {
        (U1)VDF_DS_2E_DST_NU,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2204 (10U)     */
    {
        (U1)VDF_DS_2E_DST_BI,
        (U1)U1_MAX
    },
    /*  VDF_DS_2E_2209 (11U)    */
    {
        (U1)VDF_DS_2E_DST_CMP_NU,
        (U1)VDF_DS_2E_CMP_NU_2209
    }
};

static const U4    u4_sp_VDF_DS_2E_2209_MSK[VDF_DS_2E_2209_NUM] = {
    (U4)VDF_DS_2E_TDSS_MSK,              /*  VDF_DS_2E_2209_TDSS     */
    (U4)VDF_DS_2E_TO_MSK                 /*  VDF_DS_2E_2209_TO       */
};

static const ST_VDF_DS_2E_CMP_NU    st_sp_VDF_DS_2E_CMP_NU[VDF_DS_2E_CMP_NU_NUM] = {
    {
        (U1)VDF_DS_2E_2209_NUM,
        &u4_sp_VDF_DS_2E_2209_MSK[0]
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VardefDs2EInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDs2EInit(void)
{
    U4                   u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)VDF_DS_2E_NUM_DID; u4_t_lpcnt++){
        u4_sp_vdf_ds2e_las_b32[u4_t_lpcnt] = u4_s_VdfDs2ELaschk(&st_gp_VDF_DS_2E[u4_t_lpcnt], &st_sp_VDF_DS_2E_DST[u4_t_lpcnt]);
    }

    u1_s_vdf_ds2e_syn_cnt = (U1)VDF_DS_2E_NUM_DID;
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefDs2EMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDs2EMainTask(void)
{
    if(u1_s_vdf_ds2e_syn_cnt >= (U1)VDF_DS_2E_NUM_DID){
        u1_s_vdf_ds2e_syn_cnt = (U1)0U;
    }

    u4_sp_vdf_ds2e_las_b32[u1_s_vdf_ds2e_syn_cnt] = u4_s_VdfDs2ELaschk(&st_gp_VDF_DS_2E[u1_s_vdf_ds2e_syn_cnt], &st_sp_VDF_DS_2E_DST[u1_s_vdf_ds2e_syn_cnt]);

    u1_s_vdf_ds2e_syn_cnt++;
}
/*===================================================================================================================================*/
/*  U4      u4_g_VardefDs2E_Las32(const U2 u2_a_DID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VardefDs2E_Las32(const U2 u2_a_DID)
{
    U4                   u4_t_las_b32;

    if(u2_a_DID < (U2)VDF_DS_2E_NUM_DID){
        u4_t_las_b32 = u4_sp_vdf_ds2e_las_b32[u2_a_DID];
    }
    else{
        u4_t_las_b32 = (U4)VDF_DS_2E_UNK;
    }

    return(u4_t_las_b32);
}
/*===================================================================================================================================*/
/*  U4      u4_g_VardefDs2E_Max32(const U2 u2_a_DID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_VardefDs2E_Max32(const U2 u2_a_DID)
{
    U4                   u4_t_max;

    if(u2_a_DID >= (U2)VDF_DS_2E_NUM_DID){
        u4_t_max = (U4)VDF_DS_2E_UNK;
    }
    else if(st_gp_VDF_DS_2E[u2_a_DID].fp_u4_MAX != vdp_PTR_NA){
        u4_t_max = (*st_gp_VDF_DS_2E[u2_a_DID].fp_u4_MAX)() & (U4)VDF_DS_2E_MAX;
    }
    else{
        u4_t_max = st_gp_VDF_DS_2E[u2_a_DID].u4_max & (U4)VDF_DS_2E_MAX;
    }

    return(u4_t_max);
}
/*===================================================================================================================================*/
/*  void    vd_g_VardefDs2E_Syn32(const U2 u2_a_DID)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VardefDs2E_Syn32(const U2 u2_a_DID)
{
    if(u2_a_DID < (U2)VDF_DS_2E_NUM_DID){
        u4_sp_vdf_ds2e_las_b32[u2_a_DID] = u4_s_VdfDs2ELaschk(&st_gp_VDF_DS_2E[u2_a_DID], &st_sp_VDF_DS_2E_DST[u2_a_DID]);
    }
}
/*===================================================================================================================================*/
/*  static U4      u4_s_VdfDs2ELaschk(const ST_VDF_DS_2E * st_ap_DID , const ST_VDF_DS_2E_DST * st_ap_DST)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_VdfDs2ELaschk(const ST_VDF_DS_2E * st_ap_DID , const ST_VDF_DS_2E_DST * st_ap_DST)
{
    U4                   u4_t_las_b32;
    U4                   u4_t_max;
    U4                   u4_t_nvm_b32;

    U1                   u1_t_nvm_chk;
    U1                   u1_t_nvm_unk;

    u4_t_nvm_b32 = (U4)0U;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts(st_ap_DID->u2_nid, &u4_t_nvm_b32);
    u1_t_nvm_unk = (U1)FALSE;
    if((u1_t_nvm_chk >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG)){

        u4_t_nvm_b32 = (U4)U4_MAX;
        u1_t_nvm_unk = (U1)TRUE;
    }

    if(st_ap_DID->fp_u4_MAX != vdp_PTR_NA){
        u4_t_max = (*st_ap_DID->fp_u4_MAX)();
    }
    else{
        u4_t_max = st_ap_DID->u4_max;
    }
    u4_t_max &= (U4)VDF_DS_2E_MAX;

    if(st_ap_DST->u1_dst == (U1)VDF_DS_2E_DST_CMP_NU){
        u4_t_las_b32 = u4_s_VdfDs2ECmpNuLaschk(st_ap_DST->u1_cmp_nu_did ,u4_t_nvm_b32 ,u4_t_max ,st_ap_DID->fp_u4_DEF,u1_t_nvm_unk);
    }
    else{
        if(u4_t_nvm_b32 > u4_t_max){
            if(st_ap_DID->fp_u4_DEF != vdp_PTR_NA){
                u4_t_las_b32 = (*st_ap_DID->fp_u4_DEF)(u1_t_nvm_unk) & (U4)VDF_DS_2E_MAX;
            }
            else{
                u4_t_las_b32 = (U4)VDF_DS_2E_UNK;
            }
        }
        else if(st_ap_DST->u1_dst == (U1)VDF_DS_2E_DST_BI){
            u4_t_las_b32 = u4_t_nvm_b32 & u4_t_max;
        }
        else{
            u4_t_las_b32 = u4_t_nvm_b32;
        }
    }

    return(u4_t_las_b32);
}
/*===================================================================================================================================*/
/*  static U4  u4_s_VdfDs2ECmpNuLaschk(const U1 u1_a_DID ,const U4 u4_a_B32 ,const U4 u4_a_MAX ,                                     */
/*                                     U4 ( * const fp_u4_a_DEF)(const U1 u1_a_NVM_UNK),const U1 u1_a_NVM_STS)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4  u4_s_VdfDs2ECmpNuLaschk(const U1 u1_a_DID ,const U4 u4_a_B32 ,const U4 u4_a_MAX ,
                                   U4 ( * const fp_u4_a_DEF)(const U1 u1_a_NVM_UNK),const U1 u1_a_NVM_STS)
{
    U4    u4_t_las_b32;
    U4    u4_t_max_byte;
    U4    u4_t_b32_byte;
    U1    u1_t_loop;

    u4_t_las_b32 = (U4)VDF_DS_2E_UNK;

    if(u1_a_DID < (U1)VDF_DS_2E_CMP_NU_NUM){
        for(u1_t_loop = (U1)0U; u1_t_loop < st_sp_VDF_DS_2E_CMP_NU[u1_a_DID].u1_num; u1_t_loop++){
            u4_t_max_byte = u4_a_MAX & st_sp_VDF_DS_2E_CMP_NU[u1_a_DID].u4_msk[u1_t_loop];
            u4_t_b32_byte = u4_a_B32 & st_sp_VDF_DS_2E_CMP_NU[u1_a_DID].u4_msk[u1_t_loop];
            if(u4_t_b32_byte > u4_t_max_byte){
                if(fp_u4_a_DEF != vdp_PTR_NA){
                    u4_t_las_b32 |= (*fp_u4_a_DEF)(u1_a_NVM_STS) & st_sp_VDF_DS_2E_CMP_NU[u1_a_DID].u4_msk[u1_t_loop];
                }
            }
            else{
                u4_t_las_b32 |= u4_t_b32_byte;
            }
        }
    }

    return(u4_t_las_b32);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     3/24/2020  TN       New.                                                                                               */
/*  2.1.0     9/28/2020  SF       Add Date Structure Type : Composite Numeric.                                                       */
/*  2.2.0     1/25/2021  SF       Changed to notify the read status of non-volatile memory to the default value judgment.            */
/*  2.3.0     9/12/2022  RO       Add SID 0x2004, 0x2045                                                                             */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * SF = Seiya Fukutome, DENSO TECHNO                                                                                              */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
