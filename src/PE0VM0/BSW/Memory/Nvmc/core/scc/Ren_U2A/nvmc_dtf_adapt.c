/* 1.2.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Adapt                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DTF_ADAPT_C_MAJOR                   (1U)
#define NVMC_DTF_ADAPT_C_MINOR                   (2U)
#define NVMC_DTF_ADAPT_C_PATCH                   (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "int_drv.h"
#include "memfill_u1.h"
#include "memcpy_u1.h"

#include "NvM.h"
#include "NvM_Ext.h"
#include "Mscd.h"
#include "Fee.h"

#include "nvmc_mgr.h"
#include "nvmc_mgr_private.h"
#include "nvmc_dtf_private.h"

#include "nvmc_dtf_adapt_private.h"
#include "nvmc_dtf_adapt_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_DTF_ADAPT_C_MAJOR != NVMC_DTF_ADAPT_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_ADAPT_C_MINOR != NVMC_DTF_ADAPT_PRIVATE_H_MINOR) || \
     (NVMC_DTF_ADAPT_C_PATCH != NVMC_DTF_ADAPT_PRIVATE_H_PATCH))
#error "nvmc_dtf_adapt.c and nvmc_dtf_adapt_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_DTF_ADAPT_C_MAJOR != NVMC_DTF_ADAPT_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_ADAPT_C_MINOR != NVMC_DTF_ADAPT_CFG_PRIVATE_H_MINOR) || \
     (NVMC_DTF_ADAPT_C_PATCH != NVMC_DTF_ADAPT_CFG_PRIVATE_H_PATCH))
#error "nvmc_dtf_adapt.c and nvmc_dtf_adapt_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1                   u1_dp_nvmc_dtf_adapt_read_buf[NVMC_DTF_ADAPT_BUF_ARRAY_SIZE];
static          U1   u1_s_nvmc_dtf_adapt_call_sts;
static          U1   u1_s_nvmc_dtf_adapt_rslt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_Dtf_Adapt_Init(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_Dtf_Adapt_Init(void)
{
    vd_g_MemfillU1(u1_dp_nvmc_dtf_adapt_read_buf, (U1)0U, (U4)NVMC_DTF_ADAPT_BUF_ARRAY_SIZE);
    u1_s_nvmc_dtf_adapt_call_sts = (U1)FALSE;
    u1_s_nvmc_dtf_adapt_rslt = (U1)NVMC_RESULT_NG;
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_Dtf_Adapt_ReadDrctBlock(const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*                  --> *u1_ap_data  : Read Data Pointer                                                                             */
/*                  --> *u2_a_SIZE   : Data Size                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_Dtf_Adapt_ReadDrctBlock(const U2 u2_a_BLOCKID, U1 * u1_ap_data, const U2 u2_a_SIZE)
{
    volatile  U4  u4_t_mode_bak;
              U2  u2_t_length;
              U2  u2_t_cnt;
              U1  u1_t_ret;
              U1  u1_t_id_sts;
              U1  u1_t_is_idle;
              U1  u1_t_req_rslt;

    u1_t_ret = (U1)NVMC_RESULT_NG;
    if(u1_ap_data != vdp_PTR_NA){
        u1_t_is_idle = u1_d_Nvmc_IsDeviceIdle_DTF();
        if(u1_t_is_idle == (U1)TRUE){
            /* Setting request for hook */
            u2_t_length = u2_d_Nvmc_DTF_get_RAM_Block_Size(u2_a_BLOCKID);
            if(u2_a_SIZE == u2_t_length){
                vd_g_MemfillU1(u1_dp_nvmc_dtf_adapt_read_buf, (U1)0U, (U4)NVMC_DTF_ADAPT_BUF_ARRAY_SIZE);
                u4_t_mode_bak = u4_g_CPUM_PRIV();
                u1_t_req_rslt = NvM_ReadBlock(u2_a_BLOCKID, &u1_dp_nvmc_dtf_adapt_read_buf[0]);  /* No need to cast because Std_ReturnType(uint8) to U1 */
                vd_g_CPUM_RSTR(u4_t_mode_bak);
                u1_s_nvmc_dtf_adapt_rslt = (U1)NVMC_RESULT_NG;
                u1_s_nvmc_dtf_adapt_call_sts = (U1)TRUE;
                if(u1_t_req_rslt == (U1)E_OK){
                    u2_t_cnt = (U2)0U;
                    u1_t_id_sts = (U1)NVM_REQ_PENDING;
                    do{
                        u2_t_cnt++;
                        if(u2_t_cnt > u2_d_NVMC_DTF_ADAPT_TIMEOUT){
                            break;
                        }
                        u4_t_mode_bak = u4_g_CPUM_PRIV();
                        Mscd_SpeedUp_MainFunction();
                        u1_t_req_rslt = NvM_GetErrorStatus(u2_a_BLOCKID, &u1_t_id_sts); /* No need to cast because Std_ReturnType(uint8) to U1 */
                        vd_g_CPUM_RSTR(u4_t_mode_bak);
                        if(u1_t_req_rslt != (U1)E_OK){
                            u1_t_id_sts = (U1)NVM_REQ_PENDING;
                        }
                    }while(u1_t_id_sts == (U1)NVM_REQ_PENDING);
                    u1_t_ret = u1_s_nvmc_dtf_adapt_rslt;
                    if(u1_t_ret == (U1)NVMC_RESULT_OK){
                        vd_g_MemcpyU1(u1_ap_data, u1_dp_nvmc_dtf_adapt_read_buf, (U4)u2_a_SIZE);
                    }
                }
            }
            /* Clear request for hook */
            u1_s_nvmc_dtf_adapt_call_sts = (U1)FALSE;
            u1_s_nvmc_dtf_adapt_rslt = (U1)NVMC_RESULT_NG; /* It is careful in sequence */
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Nvmc_DTF_Adapt_IsDirectRead(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1    u1_g_Nvmc_DTF_Adapt_IsDirectRead(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u1_s_nvmc_dtf_adapt_call_sts == (U1)TRUE){
        u1_t_ret = (U1)TRUE;
        u1_s_nvmc_dtf_adapt_call_sts = (U1)FALSE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void vd_d_Nvmc_DTF_Adapt_SetResult(const U1 u1_a_RESULT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_RESULT : Error Result                                                                                   */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_d_Nvmc_DTF_Adapt_SetResult(const U1 u1_a_RESULT)
{
    u1_s_nvmc_dtf_adapt_rslt = u1_a_RESULT;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Static Functions                                                                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            8/24/2015  KM      New.                                                                                         */
/*  1.0.1            9/29/2015  KM      Updated.                                                                                     */
/*  1.0.2           10/09/2015  MH      Removed DMB instruction.                                                                     */
/*                                      Fixed the issued that DTF status does not change IDLE state.                                 */
/*  1.0.3            2/ 1/2016  KM      Fixed u1_s_nvmc_dtf_adapt_read_sts value before reading.                                     */
/*  1.0.4            4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.0.5            4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.0.6            4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.0.7            4/18/2016  KM      Added BlockId Invalid check to vd_g_Nvmc_DTF_Adapt_FinishHook.                               */
/*  1.0.8           10/24/2016  HK      Changed that user can disable DTF configuration.                                             */
/*                                      Fixed DTF issue : Second argment of bswd_ms_NvM_ReadBlock changed NULL to BSWD_NULL          */
/*  1.1.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.1.1           11/25/2016  HK      Added DTF max size check.                                                                    */
/*  1.2.0           03/31/2017  HK      Changed from 15BSW DTF to 19BSW DTF.                                                         */
/*  1.2.1           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.2.2           12/01/2017  HK      Fixed AIP3GBSW-174 issue.                                                                    */
/*  1.2.3            9/14/2021  TN      NULL -> vdp_PTR_NA.                                                                          */
/*  1.2.4           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
