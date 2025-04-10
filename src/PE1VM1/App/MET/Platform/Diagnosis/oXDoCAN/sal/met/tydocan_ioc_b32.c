/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN I/O Control / Request Message Bitfield Max 32 Bits                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_IOC_B32_C_MAJOR                  (2)
#define TYDOCAN_IOC_B32_C_MINOR                  (0)
#define TYDOCAN_IOC_B32_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_ioc_b32_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_IOC_B32_C_MAJOR != TYDOCAN_IOC_B32_H_MAJOR) || \
     (TYDOCAN_IOC_B32_C_MINOR != TYDOCAN_IOC_B32_H_MINOR) || \
     (TYDOCAN_IOC_B32_C_PATCH != TYDOCAN_IOC_B32_H_PATCH))
#error "tydocan_ioc_b32.c and tydocan_ioc_b32.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_IOC_B32_C_MAJOR != TYDOCAN_IOC_B32_CFG_H_MAJOR) || \
     (TYDOCAN_IOC_B32_C_MINOR != TYDOCAN_IOC_B32_CFG_H_MINOR) || \
     (TYDOCAN_IOC_B32_C_PATCH != TYDOCAN_IOC_B32_CFG_H_PATCH))
#error "tydocan_ioc_b32.c and tydocan_ioc_b32_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_IOC_B8_BO_NEXT                      (2U)
#define TYDC_IOC_B8_LB_NEXT                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    const U1 *                  u1p_REQ;

    U4                          u4_sup;
    U4                          u4_cst;

    U2                          u2_nbyte;
    U1                          u1_prm;
    U1                          u1_sb_chk;
}ST_TYDC_IOR32;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_TydcIoR32(ST_TYDC_IOR32 * st_ap_ior32);
static U1      u1_s_TydcIoR32_Sta(ST_TYDC_IOR32 * st_ap_ior32);   /* Short Term Adjustment      */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANIocB32Init(void)
{
    U4                            u4_t_lpcnt;
    U4                            u4_t_num_r32;

    u4_t_num_r32 = (U4)TYDC_IOC_R32_NWORD * (U4)u2_g_TYDC_IOC_B32_NUM_DID;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_num_r32; u4_t_lpcnt++){
        u4_gp_tydc_ioc_r32[u4_t_lpcnt] = (U4)0U;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDidSup_IocB32(const U2 u2_a_DID, U4 * u4_ap_s32)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDidSup_IocB32(const U2 u2_a_DID, U4 * u4_ap_s32)
{
    const ST_TYDC_IOC_B32_IF *    st_tp_IF;
    U4                            u4_t_b32;
    U1                            u1_t_nbyte;
    U1                            u1_t_sup;

    u1_t_sup = (U1)OXDC_XID_SUP_NOT;
    if(u2_a_DID < u2_g_TYDC_IOC_B32_NUM_DID){

        st_tp_IF   = st_gp_TYDC_IOC_B32[u2_a_DID].stp_IF;
        u1_t_nbyte = st_gp_TYDC_IOC_B32[u2_a_DID].u1_nbyte;
        if((st_tp_IF            != vdp_PTR_NA           ) &&
           (u1_t_nbyte          >  (U1)0U               ) &&
           (u1_t_nbyte          <= (U1)TYDC_IOR32_NB_MAX) &&
           (st_tp_IF->fp_u4_SUP != vdp_PTR_NA           ) &&
           (st_tp_IF->fp_vd_ACT != vdp_PTR_NA           ) &&
           (st_tp_IF->fp_vd_DEA != vdp_PTR_NA           )){

            if((st_tp_IF->fp_u4_LAS                    == vdp_PTR_NA) &&
               (st_gp_TYDC_IOC_B32[u2_a_DID].u1_sb_chk != (U1)TRUE  )){

             /* u1_t_sup = (U1)OXDC_XID_SUP_NOT; */
            }
            else{

                u4_t_b32 = (*st_tp_IF->fp_u4_SUP)(st_gp_TYDC_IOC_B32[u2_a_DID].u2_gr);
                if(u4_t_b32 != (U4)0U){
                    u1_t_sup = (U1)OXDC_XID_SUP_PUB;
                }

                if(u4_ap_s32 != vdp_PTR_NA){
                    (*u4_ap_s32) = u4_t_b32;
                }
            }
        }
    }

    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_IocB32(U1 * u1_ap_ans, const U2 u2_a_DID)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_IocB32(U1 * u1_ap_ans, const U2 u2_a_DID)
{
    const ST_TYDC_IOC_B32_IF *    st_tp_IF;

    U4 *                          u4_tp_r32;

    U4                            u4_tp_b32[TYDC_B32_NWORD];

    U2                            u2_t_gr;

    U1                            u1_t_nbyte;
    U1                            u1_t_proc;

    u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    if(u2_a_DID < u2_g_TYDC_IOC_B32_NUM_DID){

        st_tp_IF   = st_gp_TYDC_IOC_B32[u2_a_DID].stp_IF;
        u1_t_nbyte = st_gp_TYDC_IOC_B32[u2_a_DID].u1_nbyte;
        if((st_tp_IF            != vdp_PTR_NA           ) &&
           (u1_t_nbyte          >  (U1)0U               ) &&
           (u1_t_nbyte          <= (U1)TYDC_IOR32_NB_MAX) &&
           (st_tp_IF->fp_u4_SUP != vdp_PTR_NA           )){

            u2_t_gr = st_gp_TYDC_IOC_B32[u2_a_DID].u2_gr;
            u4_tp_b32[TYDC_B32_WO_SU] = (*st_tp_IF->fp_u4_SUP)(u2_t_gr);

            if(st_tp_IF->fp_u4_LAS != vdp_PTR_NA){

                u1_t_proc                 = (U1)OXDC_SAL_PROC_FIN;

                u4_tp_b32[TYDC_B32_WO_LA] = (*st_tp_IF->fp_u4_LAS)(u2_t_gr) & u4_tp_b32[TYDC_B32_WO_SU];
            }
            else if(st_gp_TYDC_IOC_B32[u2_a_DID].u1_sb_chk == (U1)TRUE){

                u1_t_proc                 = (U1)OXDC_SAL_PROC_FIN;

                u4_tp_r32 = &u4_gp_tydc_ioc_r32[u2_a_DID];
                u4_tp_b32[TYDC_B32_WO_LA] = (U4)0x00000001U << u4_tp_r32[TYDC_IOC_R32_CST];
            }
            else{
             /* u1_t_proc = (U1)OXDC_SAL_PROC_NR_31; */
            }

            if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){
                (void)u1_g_TyDoCANBi32Tx(u1_ap_ans, &u4_tp_b32[0], (U2)u1_t_nbyte);
            }
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANIocCsmchk_B32(const U1 u1_a_PRM, const U1 * u1_ap_CSM, const U2 u2_a_DID)                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANIocCsmchk_B32(const U1 u1_a_PRM, const U1 * u1_ap_CSM, const U2 u2_a_DID)
{
    const ST_TYDC_IOC_B32_IF *    st_tp_IF;

    U4 *                          u4_tp_r32;

    ST_TYDC_IOR32                 st_t_ior32;
    U1                            u1_t_nbyte;
    U1                            u1_t_proc;

    u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    if(u2_a_DID < u2_g_TYDC_IOC_B32_NUM_DID){

        u4_tp_r32  = &u4_gp_tydc_ioc_r32[u2_a_DID];

        st_tp_IF   = st_gp_TYDC_IOC_B32[u2_a_DID].stp_IF;
        u1_t_nbyte = st_gp_TYDC_IOC_B32[u2_a_DID].u1_nbyte;
        if((st_tp_IF            != vdp_PTR_NA           ) &&
           (u1_t_nbyte          >  (U1)0U               ) &&
           (u1_t_nbyte          <= (U1)TYDC_IOR32_NB_MAX) &&
           (st_tp_IF->fp_u4_SUP != vdp_PTR_NA           )){

            st_t_ior32.u1p_REQ   = u1_ap_CSM;
            st_t_ior32.u4_sup    = (*st_tp_IF->fp_u4_SUP)(st_gp_TYDC_IOC_B32[u2_a_DID].u2_gr);
            st_t_ior32.u4_cst    = (U4)0U;
            st_t_ior32.u2_nbyte  = (U2)u1_t_nbyte;
            st_t_ior32.u1_prm    = u1_a_PRM;
            st_t_ior32.u1_sb_chk = st_gp_TYDC_IOC_B32[u2_a_DID].u1_sb_chk;

            u1_t_proc            = u1_s_TydcIoR32(&st_t_ior32);

            if(u1_t_proc == (U1)OXDC_SAL_PROC_RUN){
                u4_tp_r32[TYDC_IOC_R32_CST] = st_t_ior32.u4_cst;
            }
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANIocAct_B32(const U2 u2_a_DID)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANIocAct_B32(const U2 u2_a_DID)
{
    const ST_TYDC_IOC_B32_IF *    st_tp_IF;

    U2                            u2_t_gr;

    if(u2_a_DID < u2_g_TYDC_IOC_B32_NUM_DID){

        st_tp_IF = st_gp_TYDC_IOC_B32[u2_a_DID].stp_IF;
        if((st_tp_IF            != vdp_PTR_NA                      ) &&
           (st_tp_IF->fp_vd_ACT != vdp_PTR_NA                      )){

            u2_t_gr  = st_gp_TYDC_IOC_B32[u2_a_DID].u2_gr;

            (*st_tp_IF->fp_vd_ACT)(u2_t_gr, &u4_gp_tydc_ioc_r32[u2_a_DID]);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANIocDeAct_B32(const U2 u2_a_DID)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANIocDeAct_B32(const U2 u2_a_DID)
{
    const ST_TYDC_IOC_B32_IF *    st_tp_IF;

    if(u2_a_DID < u2_g_TYDC_IOC_B32_NUM_DID){

        st_tp_IF = st_gp_TYDC_IOC_B32[u2_a_DID].stp_IF;
        if((st_tp_IF            != vdp_PTR_NA) &&
           (st_tp_IF->fp_vd_DEA != vdp_PTR_NA)){

            (*st_tp_IF->fp_vd_DEA)(st_gp_TYDC_IOC_B32[u2_a_DID].u2_gr);
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcIoR32(ST_TYDC_IOR32 * st_ap_ior32)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcIoR32(ST_TYDC_IOR32 * st_ap_ior32)
{
    U1                       u1_t_proc;

    if(st_ap_ior32 == vdp_PTR_NA){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else if(st_ap_ior32->u2_nbyte > (U2)TYDC_IOR32_NB_MAX){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else if(st_ap_ior32->u1p_REQ == vdp_PTR_NA){

        if(st_ap_ior32->u1_prm == (U1)OXDC_IOC_PRM_CTE){

            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;

            st_ap_ior32->u4_cst = (U4)0U;
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }
    else if(st_ap_ior32->u1_prm == (U1)OXDC_IOC_PRM_STA){
        u1_t_proc = u1_s_TydcIoR32_Sta(st_ap_ior32);
    }
    else if(st_ap_ior32->u1_prm == (U1)OXDC_IOC_PRM_CTE){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_TydcIoR32_Sta(ST_TYDC_IOR32 * st_ap_ior32)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_TydcIoR32_Sta(ST_TYDC_IOR32 * st_ap_ior32)
{
    const U1 *               u1_tp_S8;

    U4                       u4_t_lpcnt;
    U4                       u4_t_ior_nbyte;

    U4                       u4_t_lsb;
    U4                       u4_t_cst;

    U4                       u4_t_und;   /* undefined bit */
    U4                       u4_t_inv;   /* invalid bit   */

    U1                       u1_t_bic;
    U1                       u1_t_proc;

    u4_t_ior_nbyte = (U4)st_ap_ior32->u2_nbyte;
    u1_tp_S8       = st_ap_ior32->u1p_REQ;

    u4_t_lsb       = (U4)0U;
    u4_t_cst       = (U4)0U;
    for(u4_t_lpcnt = (U4)1U; u4_t_lpcnt < u4_t_ior_nbyte; u4_t_lpcnt += (U2)TYDC_IOC_B8_BO_NEXT){
        u4_t_cst |= (U4)((U4)u1_tp_S8[u4_t_lpcnt] << u4_t_lsb);
        u4_t_lsb += (U4)TYDC_IOC_B8_LB_NEXT;
    }

    u4_t_und  = (U4)U4_MAX ^ st_ap_ior32->u4_sup;

    u4_t_inv  = u4_t_cst & u4_t_und;

    if(u4_t_inv != (U4)0U){

        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else if(st_ap_ior32->u1_sb_chk != (U1)TRUE){

        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;

        st_ap_ior32->u4_cst = u4_t_cst;
    }
    else{

        u1_t_bic = u1_g_BitCnt(u4_t_cst);
        if(u1_t_bic == (U1)1U){

            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;

            st_ap_ior32->u4_cst = (U4)u1_g_LsbSrch(u4_t_cst);
        }
        else{
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/20/2020  TN       New.                                                                                               */
/*  2.0.0     6/20/2024  TK       Abolition ControlEnableMask for 19PFv3 Phase6Diag                                                  */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * TK = Toru Kamishina, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
