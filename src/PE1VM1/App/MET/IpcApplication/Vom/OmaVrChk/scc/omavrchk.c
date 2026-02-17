/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  On-Board MAC Authentication Verification Result Check                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OMAVRCHK_C_MAJOR                   (1)
#define OMAVRCHK_C_MINOR                   (0)
#define OMAVRCHK_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "omavrchk.h"
#include "oxcan_acex_def.h"
#include "rim_ctl.h"

#include "aip_common.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OMAVRCHK_C_MAJOR != OMAVRCHK_H_MAJOR) || \
     (OMAVRCHK_C_MINOR != OMAVRCHK_H_MINOR) || \
     (OMAVRCHK_C_PATCH != OMAVRCHK_H_PATCH))
#error "omavrchk.c and omavrchk.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OMAVRCHK_RIM_NUM                                                (2U)
#define OMAVRCHK_RIM_RESULT_NUM                                         (16U)
#define OMAVRCHK_RIM_INIT                                               (0xAAAAAAAAU)

#define OMA_KEY_VALUE_VERIFY_ATTEMPT                                    (3U)
#define OMA_KEY_VALUE_VERIFY_SUCCESS                                    (2U)

#define OMAVRCHK_RESULT_MASK                                            (3U)
#define OMAVRCHK_RESULT_SHIFT_BIT                                       (2U)

#define SECOC_VERIF_SUCCESS                                             (0x00U)
#define SECOC_VERIF_FAIL                                                (0x01U)
#define SECOC_FRESHNESS_FAIL                                            (0x02U)
#define SECOC_AUTH_BUILD_FAIL                                           (0x03U)
#define SECOC_NO_VERIF                                                  (0x04U)
#define SECOC_VERIF_FAIL_OVERWRITE                                      (0x05U)
#define SECOC_NO_VERIF_START_FAIL                                       (0x40U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1      u1_receive_cnt;                    /* Message auth result receive count */
    U1      u1_ok_cnt;                         /* Message auth OK result count */
}ST_OMAVRCHK_CNT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_OMAVRCHK_CNT  st_sp_omavrchk_cnt[OXCAN_OMA_NUM_REC];
static U1               u1_s_omavrchk_odo_rx_cnt;
static U1               u1_s_omavrchk_odo_auth_rslt;
static U1               u1_s_omavrchk_firstnrx_rslt;
static U1               u1_s_omavrchk_odo_firstnrx_rslt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_OmaVrChkUpdateResult(U4 * u4_ap_oma_cnt, const U1 u1_a_result);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const   U2      u2_sp_OMAVRCHK_RIMID_RESULT[OMAVRCHK_RIM_NUM] = {
    (U2)RIMID_U4_OMAVRCHK_RESULT_01,
    (U2)RIMID_U4_OMAVRCHK_RESULT_02
};

/*===================================================================================================================================*/
/*  void    vd_g_OmaVrChkInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OmaVrChkInit(void)
{
    U4                  u4_t_loop;

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)OXCAN_OMA_NUM_REC; u4_t_loop++){
        st_sp_omavrchk_cnt[u4_t_loop].u1_receive_cnt = (U1)0U;
        st_sp_omavrchk_cnt[u4_t_loop].u1_ok_cnt      = (U1)0U;
    }
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)OMAVRCHK_RIM_NUM; u4_t_loop++){
        vd_g_Rim_WriteU4((U2)u2_sp_OMAVRCHK_RIMID_RESULT[u4_t_loop], (U4)OMAVRCHK_RIM_INIT);
    }
    u1_s_omavrchk_odo_rx_cnt             = (U1)0U;
    u1_s_omavrchk_odo_auth_rslt          = (U1)OMAVRCHK_RESULT_UNKNOWN;
    u1_s_omavrchk_firstnrx_rslt          = (U1)OMAVRCHK_RESULT_OK;
    u1_s_omavrchk_odo_firstnrx_rslt      = (U1)OMAVRCHK_RESULT_UNKNOWN;
}
/*===================================================================================================================================*/
/*  void    vd_g_OmaVrChkInitIgOnEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OmaVrChkInitIgOnEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)
{
    vd_g_OmaVrChkInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_OmaVrChkRxHook(const U2 u2_a_OMA_RX, const U1 u1_a_OMA_VR)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OmaVrChkRxHook(const U2 u2_a_OMA_RX, const U1 u1_a_OMA_VR)
{
    if((u2_a_OMA_RX < (U2)OXCAN_OMA_NUM_REC) &&
       (st_sp_omavrchk_cnt[u2_a_OMA_RX].u1_receive_cnt < (U1)OMA_KEY_VALUE_VERIFY_ATTEMPT)){
        if((u1_a_OMA_VR == (U1)SECOC_VERIF_SUCCESS) &&
           (st_sp_omavrchk_cnt[u2_a_OMA_RX].u1_ok_cnt < (U1)OMA_KEY_VALUE_VERIFY_ATTEMPT)){
            st_sp_omavrchk_cnt[u2_a_OMA_RX].u1_ok_cnt++;
            st_sp_omavrchk_cnt[u2_a_OMA_RX].u1_receive_cnt++;
        }
        else if((u1_a_OMA_VR == (U1)SECOC_VERIF_FAIL)     ||
                (u1_a_OMA_VR == (U1)SECOC_FRESHNESS_FAIL) ||
                (u1_a_OMA_VR == (U1)SECOC_VERIF_FAIL_OVERWRITE)){
            st_sp_omavrchk_cnt[u2_a_OMA_RX].u1_receive_cnt++;         
        }
        else{
            /* do nothing */
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_OmaVrChkRxHookByOdo(const U1 u1_a_OMA_VR)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OmaVrChkRxHookByOdo(const U1 u1_a_OMA_VR)
{
    if(u1_a_OMA_VR == (U1)SECOC_VERIF_SUCCESS){
        u1_s_omavrchk_odo_auth_rslt = (U1)OMAVRCHK_RESULT_OK;
    }
    else if((u1_a_OMA_VR == (U1)SECOC_VERIF_FAIL)     ||
            (u1_a_OMA_VR == (U1)SECOC_FRESHNESS_FAIL) ||
            (u1_a_OMA_VR == (U1)SECOC_VERIF_FAIL_OVERWRITE)){
        u1_s_omavrchk_odo_auth_rslt = (U1)OMAVRCHK_RESULT_NG;
    }
    else{
        u1_s_omavrchk_odo_auth_rslt = (U1)OMAVRCHK_RESULT_UNKNOWN;
    }
    
    if(u1_s_omavrchk_odo_rx_cnt < (U1)U1_MAX){
        u1_s_omavrchk_odo_rx_cnt++;
    }
    else{
        u1_s_omavrchk_odo_rx_cnt = (U1)0U;
    }
}
/*===================================================================================================================================*/
/*  static U1    u1_s_OmaVrChkUpdateResult(const U4 u4_a_oma_cnt, const U1 u1_a_result)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_OmaVrChkUpdateResult(U4 * u4_ap_oma_idcnt, const U1 u1_a_rim_result)
{
    U1               u1_t_result;
    U4               u4_t_oma_idcnt;

    u1_t_result    = u1_a_rim_result;
    u4_t_oma_idcnt = (*u4_ap_oma_idcnt);
    if(u4_t_oma_idcnt < (U4)OXCAN_OMA_NUM_REC){
        if((st_sp_omavrchk_cnt[u4_t_oma_idcnt].u1_receive_cnt >= (U1)OMA_KEY_VALUE_VERIFY_ATTEMPT) &&
           (u1_t_result == (U1)OMAVRCHK_RESULT_UNKNOWN)){
            if(st_sp_omavrchk_cnt[u4_t_oma_idcnt].u1_ok_cnt < (U1)OMA_KEY_VALUE_VERIFY_SUCCESS){
                u1_t_result = (U1)OMAVRCHK_RESULT_NG;
            }
            else{
                u1_t_result = (U1)OMAVRCHK_RESULT_OK;
            }
        }
        if(u4_t_oma_idcnt == (U4)OXCAN_OMA_RX_BDC1S13){
            u1_s_omavrchk_odo_firstnrx_rslt = u1_t_result;
        }
        (*u4_ap_oma_idcnt) = u4_t_oma_idcnt + (U4)1U;
    }

    return(u1_t_result);
}
/*===================================================================================================================================*/
/*  void    vd_g_OmaVrChkMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OmaVrChkMainTask(void)
{
    U4                  u4_t_rim_num;
    U4                  u4_t_loop;
    U4                  u4_t_oma_idcnt;
    U4                  u4_t_data;
    U4                  u4_t_write;
    U1                  u1_t_sts;
    U1                  u1_t_rim_result;
    U1                  u1_t_updated_result;

    u4_t_oma_idcnt              = (U4)0U;
    u1_s_omavrchk_firstnrx_rslt = (U1)OMAVRCHK_RESULT_OK;

    for(u4_t_rim_num = (U4)0U; u4_t_rim_num < (U4)OMAVRCHK_RIM_NUM; u4_t_rim_num++){
        u4_t_data    = (U4)0U;
        u1_t_sts     = u1_g_Rim_ReadU4withStatus(u2_sp_OMAVRCHK_RIMID_RESULT[u4_t_rim_num], &u4_t_data);
        if((u1_t_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
            u4_t_write = (U4)0U;
            for(u4_t_loop = (U4)0U; u4_t_loop < (U4)OMAVRCHK_RIM_RESULT_NUM; u4_t_loop++){
                u1_t_rim_result     = (U1)((u4_t_data >> (u4_t_loop * (U4)OMAVRCHK_RESULT_SHIFT_BIT)) & (U4)OMAVRCHK_RESULT_MASK);
                u1_t_updated_result = u1_s_OmaVrChkUpdateResult(&u4_t_oma_idcnt, u1_t_rim_result);
                if(u1_t_updated_result == (U1)OMAVRCHK_RESULT_NG){
                    u1_s_omavrchk_firstnrx_rslt = (U1)OMAVRCHK_RESULT_NG;
                }
                u4_t_write |= ((U4)u1_t_updated_result << (u4_t_loop * (U4)OMAVRCHK_RESULT_SHIFT_BIT));
            }
            vd_g_Rim_WriteU4(u2_sp_OMAVRCHK_RIMID_RESULT[u4_t_rim_num], u4_t_write);
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_OmaVrChkResult(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OmaVrChkResult(void)
{
    return(u1_s_omavrchk_firstnrx_rslt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_OmaVrChkResultFirstNRx(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OmaVrChkResultFirstNRx(void)
{
    return(u1_s_omavrchk_odo_firstnrx_rslt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_OmaVrChkResultEachRx(U1 * u1_ap_cnt)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OmaVrChkResultEachRx(U1 * u1_ap_cnt)
{
    (*u1_ap_cnt)   = (U1)u1_s_omavrchk_odo_rx_cnt;
    return(u1_s_omavrchk_odo_auth_rslt);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/09/2026  KO       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KO     = Kazuto Oishi,  Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
