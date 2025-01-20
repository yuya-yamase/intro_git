/* 1.4.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr DataFlash                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_DTF_C_MAJOR                         (1U)
#define NVMC_DTF_C_MINOR                         (4U)
#define NVMC_DTF_C_PATCH                         (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "wdg_drv.h"

#include "int_drv.h"
#include "memfill_u1.h"
#include "memcpy_u1.h"

#include "NvM.h"
#include "NvM_Ext.h"
#include "SchM_NvM.h"
#include "Mscd.h"
#include "Fee.h"
#include "Fls.h"

#include "nvmc_mgr.h"
#include "nvmc_mgr_private.h"
#include "nvmc_mgr_acstask_private.h"

#include "nvmc_dtf.h"
#include "nvmc_dtf_private.h"
#include "nvmc_dtf_cfg.h"
#include "nvmc_dtf_cfg_private.h"
#include "nvmc_dtf_adapt_private.h"

#include <stdint.h>
#include <Std_Types.h>
#include <SS.h>
#include <Ecu_Memmap.h>

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_DTF_C_MAJOR != NVMC_DTF_H_MAJOR) || \
     (NVMC_DTF_C_MINOR != NVMC_DTF_H_MINOR) || \
     (NVMC_DTF_C_PATCH != NVMC_DTF_H_PATCH))
#error "nvmc_dtf.c and nvmc_dtf.h : source and header files are inconsistent!"
#endif

#if ((NVMC_DTF_C_MAJOR != NVMC_DTF_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_C_MINOR != NVMC_DTF_PRIVATE_H_MINOR) || \
     (NVMC_DTF_C_PATCH != NVMC_DTF_PRIVATE_H_PATCH))
#error "nvmc_dtf.c and nvmc_dtf_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_DTF_C_MAJOR != NVMC_DTF_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_DTF_C_MINOR != NVMC_DTF_CFG_PRIVATE_H_MINOR) || \
     (NVMC_DTF_C_PATCH != NVMC_DTF_CFG_PRIVATE_H_PATCH))
#error "nvmc_dtf.c and nvmc_dtf_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #define NVMC_RECOVERY_ID_NUM_DTF                 (5U) */

/* #define NVMC_WFCFG_WARBR                         (0x00000000U) */
/* #define NVMC_WSWP_CFG                            (0x00003FFFU) */
/* #define NVMC_WFCFG_BERR_DED                      (0x00000001U) */
/* #define NVMC_WFCFG_BERRCLR_DED                   (0x00000001U) */

/* #define NVMC_ECC_ERR_OFF                         (0U) */
/* #define NVMC_ECC_ERR_ON                          (1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_sp_nvmc_dtf_read_ramblk[NVMC_DTF_DATA_MAX_SIZE]           __attribute__((section(".bss_nvmc_ramblk")));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Nvmc_RAMBlockInit(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_BonInit_DTF(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_BonInit_DTF(void)
{
    volatile U4             u4_t_mode_bak;

    vd_s_Nvmc_RAMBlockInit();
    u4_t_mode_bak = u4_g_CPUM_PRIV();
    Fls_Init(vdp_PTR_NA);
    NvM_PreInit();
    Mscd_Init();
    NvM_Init(vdp_PTR_NA);
    Fee_Init(vdp_PTR_NA);

    vd_g_CPUM_RSTR(u4_t_mode_bak);
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_WkupInit_DTF(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_WkupInit_DTF(void)
{
    volatile U4             u4_t_mode_bak;

    vd_s_Nvmc_RAMBlockInit();
    u4_t_mode_bak = u4_g_CPUM_PRIV();
    Fls_Init(vdp_PTR_NA);
    NvM_PreInit();
    Mscd_Init();
    NvM_Init(vdp_PTR_NA);
    Fee_Init(vdp_PTR_NA);
    
    vd_g_CPUM_RSTR(u4_t_mode_bak);
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_Execution_DTF(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_DTF_ExecDriver(void)
{
#if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U))
#else
    volatile U4             u4_t_mode_bak;

    u4_t_mode_bak = u4_g_CPUM_PRIV();
    Mscd_SpeedUp_MainFunction();
    vd_g_CPUM_RSTR(u4_t_mode_bak);
#endif /* #if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U)) */
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_ReadBlock_DTF(const U2 u2_a_BLOCKID)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_ReadBlock_DTF(const U2 u2_a_BLOCKID)
{
    volatile    U4      u4_t_mode_bak;
                U1      u1_t_is_idle;
                U1      u1_t_rslt;
                U1      u1_t_ret;

    u1_t_ret = (U1)FALSE;
    u1_t_is_idle = u1_d_Nvmc_IsDeviceIdle_DTF();
    if(u1_t_is_idle == (U1)TRUE){
        vd_g_MemfillU1(u1_sp_nvmc_dtf_read_ramblk, (U1)0U, (U4)NVMC_DTF_DATA_MAX_SIZE);
        u4_t_mode_bak = u4_g_CPUM_PRIV();
        u1_t_rslt = NvM_ReadBlock(u2_a_BLOCKID, &u1_sp_nvmc_dtf_read_ramblk[0]);             /* No need to cast because Std_ReturnType(uint8) to U1 */
        vd_g_CPUM_RSTR(u4_t_mode_bak);
        if(u1_t_rslt == (U1)E_OK){
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_WriteBlock_DTF(const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*                  --> *u1_ap_DATA  : Write Data                                                                                    */
/*                  --> u2_a_SIZE    : Data Size                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_WriteBlock_DTF(const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)
{
    volatile    U4      u4_t_mode_bak;
                U1      u1_t_is_idle;
                U2      u2_t_length;
                U1  *   u1_tp_block;
                U1      u1_t_ret;
                U1      u1_t_rslt;

    u1_t_ret = (U1)FALSE;
    u1_t_is_idle = u1_d_Nvmc_IsDeviceIdle_DTF();
    if(u1_t_is_idle == (U1)TRUE){
        u2_t_length = u2_d_Nvmc_DTF_get_RAM_Block_Size(u2_a_BLOCKID);
        if(u2_a_SIZE == u2_t_length){
            u1_tp_block = u1_dp_Nvmc_DTF_get_RAM_Block_Addr(u2_a_BLOCKID);
            if(u1_tp_block != NULL_PTR){
                vd_g_MemcpyU1(&u1_tp_block[0], &u1_ap_DATA[0], (U4)u2_t_length);
                u4_t_mode_bak = u4_g_CPUM_PRIV();
                u1_t_rslt = NvM_WriteBlock(u2_a_BLOCKID, NULL_PTR);        /* No need to cast because Std_ReturnType(uint8) to U1 */
                vd_g_CPUM_RSTR(u4_t_mode_bak);
                if(u1_t_rslt == (U1)E_OK){
                    u1_t_ret = (U1)TRUE;
                }
            }
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_IsDeviceIdle_DTF(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_IsDeviceIdle_DTF(void)
{
#if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U))
    return((U1)TRUE);
#else
                U1  u1_t_ret;
                U1  u1_t_rslt;
    volatile    U4  u4_t_mode_bak;
                Mscd_MsStatusType      st_tp_sts;

    u4_t_mode_bak = u4_g_CPUM_PRIV();
    u1_t_rslt = Mscd_Msif_GetStatus(&st_tp_sts);                            /* No need to cast because Std_ReturnType(uint8) to U1 */
    vd_g_CPUM_RSTR(u4_t_mode_bak);
    u1_t_ret = (U1)FALSE;
    if(u1_t_rslt == (U1)E_OK){
        if(st_tp_sts == MSCD_MS_STATE_IDLE){
            u1_t_ret = (U1)TRUE;
        }
        else if(st_tp_sts == MSCD_MS_STATE_ERROR){
            vd_g_Nvmc_DTF_StateErrorHook();
        }
        else{
            /* u1_t_ret = (U1)FALSE; */
        }
    }
    else{
        vd_g_Nvmc_DTF_StateErrorHook();
    }
    return(u1_t_ret);
#endif /* #if ((defined(__AIP_DEBUG_SIM__)) && (__AIP_DEBUG_SIM__==1U)) */
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_Recovery_DTF(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_Recovery_DTF(void)
{
    vd_d_Nvmc_Recovery(u1_d_NVMC_DTF_DEVICE_TYPE);
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_MainFunc_DTF_Req(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_MainFunc_DTF_Req(void)
{
    volatile U4             u4_t_mode_bak;

    u4_t_mode_bak = u4_g_CPUM_PRIV();
    NvM_MainFunction();
    vd_g_CPUM_RSTR(u4_t_mode_bak);
}

/*===================================================================================================================================*/
/*  U1      u1_g_Nvmc_DTF_ChkDTF_ECCErr(const U4 u4_a_DAB_DFAR)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u4_a_DAB_DFAR : DAB_DFAR                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_g_Nvmc_DTF_ChkDTF_ECCErr(const U4 u4_a_DAB_DFAR)
{
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/*  Std_ReturnType   u1_g_Nvmc_DTF_Hook(const U1 u1_a_BLOCKREQ, const U2 u2_a_BLOCKID, const U1 u1_a_JOBRESULT)                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u1_a_BLOCKREQ  : Block Request Type                                                                          */
/*                      u2_a_BLOCKID   : Block ID                                                                                    */
/*                      u1_a_JOBRESULT : Result of job                                                                               */
/*  Return:         --> (U1)E_OK       : Call back result                                                                            */
/*===================================================================================================================================*/
Std_ReturnType   u1_g_Nvmc_DTF_Hook(const U1 u1_a_BLOCKREQ, const U2 u2_a_BLOCKID, const U1 u1_a_JOBRESULT)
{
    Mscd_ErrorInfo_ErrorResultInfoType    st_t_error;
    volatile                        U4    u4_t_mode_bak;
                                    U1    u1_t_is_direct;
                                    U1 *  u1_tp_block;
                                    U2    u2_t_length;
                                    U1    u1_t_result;
                                    U1    u1_t_joberr;

    st_t_error.u4ErrorResult = (uint32)MSCD_ERRINFO_RESULT_NO_ERROR;

    u4_t_mode_bak = u4_g_CPUM_PRIV();
    u1_t_joberr = Mscd_ErrorInfo_GetSingleBlockJobErrorResult(u1_a_BLOCKREQ, &st_t_error);
    vd_g_CPUM_RSTR(u4_t_mode_bak);

    if(u1_t_joberr == (U1)E_OK){

        u2_t_length = u2_d_Nvmc_DTF_get_RAM_Block_Size(u2_a_BLOCKID);
        u1_t_result = (U1)NVMC_RESULT_NG;
        switch(u1_a_BLOCKREQ){
            case NVM_READ_BLOCK:
                if(u1_a_JOBRESULT == (U1)NVM_REQ_OK){
                    u1_t_result = (U1)NVMC_RESULT_OK;
                }
                else{
                    if((st_t_error.u4ErrorResult & (uint32)MSCD_ERRINFO_RESULT_NODATA) != (uint32)0U){
                        u1_t_result = (U1)NVMC_RESULT_NODATA;
                    }
                }
                u1_t_is_direct = u1_g_Nvmc_DTF_Adapt_IsDirectRead();
                if(u1_t_is_direct != (U1)TRUE){
                    vd_g_Nvmc_JobFinishHook((U1)NVMC_DEVICE_TYPE_DTF,
                                            u2_a_BLOCKID,
                                            (U1)NVMC_REQUEST_TYPE_READ,
                                            u1_t_result,
                                            u1_sp_nvmc_dtf_read_ramblk,
                                            u2_t_length);
                }
                else{
                    vd_d_Nvmc_DTF_Adapt_SetResult(u1_t_result);
                }
                break;
            case NVM_WRITE_BLOCK:
                u1_tp_block = u1_dp_Nvmc_DTF_get_RAM_Block_Addr(u2_a_BLOCKID);
                if(u1_a_JOBRESULT == (U1)NVM_REQ_OK){
                    u1_t_result = (U1)NVMC_RESULT_OK;
                }
                if(u1_tp_block != NULL_PTR){
                    vd_g_Nvmc_JobFinishHook((U1)NVMC_DEVICE_TYPE_DTF,
                                            u2_a_BLOCKID,
                                            (U1)NVMC_REQUEST_TYPE_WRITE,
                                            u1_t_result,
                                            u1_tp_block,
                                            u2_t_length);
                }
                break;
            default:
                /* do nothing */
                break;
        }
    }
    return(E_OK);
}

/*===================================================================================================================================*/
/*  Std_ReturnType   u1_g_Nvmc_DTF_CommonReadCallBack(const U2 u2_a_BLOCKID, const void * vd_ap_NVMBUFFER)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID     : Block ID                                                                                  */
/*                      * vd_ap_NVMBUFFER : Read Data Pointer                                                                         */
/*  Return:         --> (U1)E_OK   : Call back result                                                                                */
/*===================================================================================================================================*/
Std_ReturnType   u1_g_Nvmc_DTF_CommonReadCallBack(const U2 u2_a_BLOCKID, const void * vd_ap_NVMBUFFER)
{
    return (E_OK);
}

/*===================================================================================================================================*/
/*  Std_ReturnType   u1_g_Nvmc_DTF_CommonWriteCallBack(const U2 u2_a_BLOCKID, void * vd_ap_NvMBuffer)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID      : Block ID                                                                                 */
/*                      * vd_ap_NvMBuffer : Write Data Pointer                                                                       */
/*  Return:         --> (U1)E_OK   : Call back result                                                                                */
/*===================================================================================================================================*/
Std_ReturnType   u1_g_Nvmc_DTF_CommonWriteCallBack(const U2 u2_a_BLOCKID, void * vd_ap_NvMBuffer)
{
    return (E_OK);
}

/*===================================================================================================================================*/
/* U1 * u1_dp_Nvmc_DTF_get_RAM_Block_Addr(const U2 u2_a_ID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID         : NVM ID                                                                                     */
/*  Return:         --> u1_tp_ram_block : RAM block pointer                                                                          */
/*===================================================================================================================================*/
U1 * u1_dp_Nvmc_DTF_get_RAM_Block_Addr(const U2 u2_a_ID)
{
    U1  *   u1_tp_ram_block;

    u1_tp_ram_block = NULL_PTR;
    if(u2_a_ID < u2_d_NVMC_NUM_OF_NVRAMBLOCKS){
        u1_tp_ram_block = NvMBlockDescriptors[u2_a_ID].NvMRamBlockDataAddress;  /* No need to cast because (uint8 *) to (U1 *) */
    }

    return(u1_tp_ram_block);
}

/*===================================================================================================================================*/
/*  U2 u2_d_Nvmc_DTF_get_RAM_Block_Size(const U2 u2_a_ID)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_ID         : NVM ID                                                                                     */
/*  Return:         --> u2_t_size       : RAM block size                                                                             */
/*===================================================================================================================================*/
U2 u2_d_Nvmc_DTF_get_RAM_Block_Size(const U2 u2_a_ID)
{
    U2 u2_t_size;

    u2_t_size = (U2)0U;
    if(u2_a_ID < u2_d_NVMC_NUM_OF_NVRAMBLOCKS){
        u2_t_size = NvMBlockDescriptors[u2_a_ID].NvMNvBlockLength;              /* No need to cast because uint16 to U2 */
    }

    return(u2_t_size);
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
/*  static void    vd_d_Nvmc_RAM_Block_Init(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Nvmc_RAMBlockInit(void)
{
    (void)SS_Memory_set(__ghsbegin_MEM_SEC_ADDR_STA_BSS_MS, 0UL, (uintptr_t)NVMC_RAM_SIZE);
    vd_g_Wdg_SetTriggerCondition((U2)0U);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0            9/ 2/2015  KM      New.                                                                                         */
/*  1.0.1            9/29/2015  KM      Updated.                                                                                     */
/*  1.1.0           10/ 6/2015  KM      Updated & Bug fix.                                                                           */
/*  1.1.1           10/21/2015  MH      Fixed QAC issue.                                                                             */
/*  1.1.2           10/29/2015  KS      File revision updated                                                                        */
/*                  10/30/2015  KM      Bug fix.                                                                                     */
/*  1.1.3                               u1_g_Nvmc_DTF_ReadMemory was deleted because not used                                        */
/*  1.1.4           11/18/2015  KS      The unnecessary function prottypes were deleted.                                             */
/*  1.1.5           12/10/2015  KS      Fixed DTF CS issue.                                                                          */
/*  1.1.6            1/ 6/2016  KM      include "nvmc_mgr_acstask_private.h".                                                        */
/*  1.1.7            1/ 8/2016  KM      Fixed DTF CS issue.                                                                          */
/*  1.1.8            1/11/2016  KM      File revision updated                                                                        */
/*  1.1.9            2/26/2016  KM      Version updated.                                                                             */
/*  1.1.10           4/ 4/2016  KM      Fixed PCS3-2 issue.                                                                          */
/*  1.1.11           4/11/2016  HK      Fixed function comments.                                                                     */
/*  1.1.12           4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.1.13           4/15/2016  KM      Version updated.                                                                             */
/*  1.1.14           5/30/2016  KM      Fixed u1_g_Nvmc_DTF_ChkDTF_ECCErr.                                                           */
/*  1.1.15          10/24/2016  HK      Changed that user can disable DTF configuration.                                             */
/*                                      Fixed DTF issue : Second argment of bswd_ms_NvM_ReadBlock changed NULL to BSWD_NULL          */
/*  1.2.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.3.0           03/31/2017  HK      Changed from 15BSW DTF to 19BSW DTF.                                                         */
/*  1.3.1           06/09/2017  HK      Add Common Read/Write Callback api of DTF Mirror config.                                     */
/*                                      Changed u1_g_Nvmc_DTF_Hook by DTFDriver update.                                              */
/*  1.3.2           07/05/2017  MH      Remove unnecessary "#include" file.                                                          */
/*  1.3.3           08/22/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.3.4           09/21/2017  HK      Fixed AIP3GBSW-167 issue.                                                                    */
/*  1.3.5           11/21/2017  HK      Fixed AIP3GBSW-203 issue.                                                                    */
/*                                      Fixed AIP3GBSW-204 issue.                                                                    */
/*  1.3.6           01/19/2018  HK      Fixed AIP3GBSW-241 issue.                                                                    */
/*  1.3.7           03/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.4.0           10/ 4/2021  TN      QAC warning#2987 were fixed.                                                                 */
/*                                      vd_d_Nvmc_DeInit_DTF, vd_d_Nvmc_DTF_Refresh and vd_d_Nvmc_MainFunc_DTF_Conf were deleted.    */
/*  1.4.1           29/ 7/2022  ST      Upadated to match AUBSIT-MS updates.                                                         */
/*  1.4.2           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 and Waning CERT-PRE31 was fixed.                       */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * KS      = Kenichi Sakai,   Denso Create                                                                                        */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * ST      = Shohei Takada, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
