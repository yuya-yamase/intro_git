/* 1.1.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Nvmc : Mgr EEPROM                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_EEP_C_MAJOR                         (1U)
#define NVMC_EEP_C_MINOR                         (1U)
#define NVMC_EEP_C_PATCH                         (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "memcpy_u1.h"

#include "ms_nvm_eep.h"

#include "nvmc_mgr.h"
#include "nvmc_mgr_private.h"

#include "nvmc_eep_private.h"
#include "nvmc_eep_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NVMC_EEP_C_MAJOR != NVMC_EEP_PRIVATE_H_MAJOR) || \
     (NVMC_EEP_C_MINOR != NVMC_EEP_PRIVATE_H_MINOR) || \
     (NVMC_EEP_C_PATCH != NVMC_EEP_PRIVATE_H_PATCH))
#error "nvmc_eep.c and nvmc_eep_private.h : source and header files are inconsistent!"
#endif

#if ((NVMC_EEP_C_MAJOR != NVMC_EEP_CFG_PRIVATE_H_MAJOR) || \
     (NVMC_EEP_C_MINOR != NVMC_EEP_CFG_PRIVATE_H_MINOR) || \
     (NVMC_EEP_C_PATCH != NVMC_EEP_CFG_PRIVATE_H_PATCH))
#error "nvmc_eep.c and nvmc_eep_cfg_private.h : source and config files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_REQUEST_TYPE_INVALID                (NVMC_REQUEST_TYPE_NUM)
#define NVMC_EEP_BLOCKSIZE                       (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NVMC_EEP_ID_INVALID                      (0xFFFFU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U2  u2_s_nvmc_eep_execid;
static  U2  u2_s_nvmc_eep_timer;
static  U1  u1_s_nvmc_eep_execsrvtype;

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
/* void    vd_d_Nvmc_EEP_Init(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_EEP_Init(void)
{
    vd_g_Nvm_Eep_Init();
    u2_s_nvmc_eep_execid = (U2)NVMC_EEP_ID_INVALID;
    u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_INVALID;
    u2_s_nvmc_eep_timer = u2_d_NVMC_EEP_CTL_DEVICE_TIMEOUT;
}

/*===================================================================================================================================*/
/*  void    vd_d_Nvmc_MainFunc_EEP(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_d_Nvmc_MainFunc_EEP(void)
{
    U1  u1_t_data;
    U1  u1_t_is_idle;
    U1  u1_t_type;
    U2  u2_t_id;

    u1_t_data = (U1)0U;
    if(u1_s_nvmc_eep_execsrvtype < (U1)NVMC_REQUEST_TYPE_NUM){
        u1_t_is_idle = u1_g_Nvm_Eep_IsPortIdle();
        if(u1_t_is_idle == (U1)TRUE){
            (void)u1_g_Nvm_Eep_NonWrite();

            u2_t_id = u2_s_nvmc_eep_execid;
            u1_t_type = u1_s_nvmc_eep_execsrvtype;

            u2_s_nvmc_eep_execid = (U2)NVMC_EEP_ID_INVALID;
            u2_s_nvmc_eep_timer = u2_d_NVMC_EEP_CTL_DEVICE_TIMEOUT;
            u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_INVALID;

            vd_g_Nvmc_JobFinishHook(u1_d_NVMC_EEP_DEVICE_TYPE, u2_t_id, u1_t_type, (U1)NVMC_RESULT_OK, &u1_t_data, (U2)0U);
        }
        else{
            if(u2_s_nvmc_eep_timer < u2_d_NVMC_EEP_CTL_DEVICE_TIMEOUT){
                u2_s_nvmc_eep_timer++;
            }
            else{
                u2_t_id = u2_s_nvmc_eep_execid;
                u1_t_type = u1_s_nvmc_eep_execsrvtype;

                u2_s_nvmc_eep_execid = (U2)NVMC_EEP_ID_INVALID;
                u2_s_nvmc_eep_timer = u2_d_NVMC_EEP_CTL_DEVICE_TIMEOUT;
                u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_INVALID;

                vd_d_Nvmc_EEP_DriverErrorHook(u2_t_id, u1_t_type);
                vd_g_Nvmc_JobFinishHook(u1_d_NVMC_EEP_DEVICE_TYPE, u2_t_id, u1_t_type, (U1)NVMC_RESULT_NG, &u1_t_data, (U2)0U);
            }
        }
    }
    else{
        u2_s_nvmc_eep_execid = (U2)NVMC_EEP_ID_INVALID;
        u2_s_nvmc_eep_timer = u2_d_NVMC_EEP_CTL_DEVICE_TIMEOUT;
        u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_INVALID;
    }
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_ReadBlock_EEP(const U2 u2_a_BLOCKID)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_ReadBlock_EEP(const U2 u2_a_BLOCKID)
{
    U4      u4_t_read_data;
    U2      u2_t_data;
    U1      u1_t_ret;
    U1      u1_t_drv_sts;
    U1      u1_t_cnt;

    u1_t_ret       = (U1)FALSE;

    u4_t_read_data = (U4)0U;
    u1_t_cnt       = (U1)0U;
    do{
        u1_t_drv_sts = u1_g_Nvm_Eep_Read(u2_a_BLOCKID, &u4_t_read_data);
        if(u1_t_drv_sts == (U1)TRUE){
            u2_t_data = (U2)u4_t_read_data;
            vd_g_Nvmc_JobFinishHook(u1_d_NVMC_EEP_DEVICE_TYPE, u2_a_BLOCKID, (U1)NVMC_REQUEST_TYPE_READ, (U1)NVMC_RESULT_OK, (U1 *)&u2_t_data, (U2)NVMC_EEP_BLOCKSIZE);
            u1_t_ret = (U1)TRUE;
            break;
        }
        u1_t_cnt++;
    }while(u1_t_cnt <= u1_d_NVMC_EEP_CTL_READ_RETRY);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_WriteBlock_EEP(const U2 u2_a_BLOCKID, const U4 * consr u1_ap_DATA, const U2 u2_a_SIZE)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*                  --> *u1_ap_DATA  : Write Data                                                                                    */
/*                  --> u2_a_SIZE    : Data Size                                                                                     */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_WriteBlock_EEP(const U2 u2_a_BLOCKID, const U1 * const u1_ap_DATA, const U2 u2_a_SIZE)
{
    U2  u2_t_data;
    U1  u1_t_ret;
    U1  u1_t_drv_sts;
    U1  u1_t_cnt;

    u1_t_ret = (U1)FALSE;

    u1_t_cnt = (U1)0U;

    if(u2_a_SIZE == (U2)NVMC_EEP_BLOCKSIZE){
        vd_g_MemcpyU1((U1 *)&u2_t_data, u1_ap_DATA, (U4)u2_a_SIZE);
        do{
            u1_t_drv_sts = u1_g_Nvm_Eep_Write(u2_a_BLOCKID, (U4)u2_t_data);
            if(u1_t_drv_sts == (U1)TRUE){
                u2_s_nvmc_eep_execid = u2_a_BLOCKID;
                u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_WRITE;
                u2_s_nvmc_eep_timer = (U2)0U;

                u1_t_ret = (U1)TRUE;
                break;
            }
            u1_t_cnt++;
        }while(u1_t_cnt <= u1_d_NVMC_EEP_CTL_WRITE_RETRY);
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_EraseBlock_EEP(const U2 u2_a_BLOCKID)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_BLOCKID : BlockId                                                                                       */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_EraseBlock_EEP(const U2 u2_a_BLOCKID)
{
    U1  u1_t_ret;
    U1  u1_t_drv_sts;
    U1  u1_t_cnt;

    u1_t_ret = (U1)FALSE;

    u1_t_cnt = (U1)0U;
    do{
        u1_t_drv_sts = u1_g_Nvm_Eep_Erase(u2_a_BLOCKID);
        if(u1_t_drv_sts == (U1)TRUE){
            u2_s_nvmc_eep_execid = u2_a_BLOCKID;
            u1_s_nvmc_eep_execsrvtype = (U1)NVMC_REQUEST_TYPE_ERASE;
            u2_s_nvmc_eep_timer = (U2)0U;

            u1_t_ret = (U1)TRUE;
            break;
        }
        u1_t_cnt++;
    }while(u1_t_cnt <= u1_d_NVMC_EEP_CTL_ERASE_RETRY);
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1      u1_d_Nvmc_IsDeviceIdle_EEP(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_ret : Result                                                                                             */
/*===================================================================================================================================*/
U1      u1_d_Nvmc_IsDeviceIdle_EEP(void)
{
    U1 u1_t_ret;
    
    u1_t_ret = (U1)FALSE;
    if(u1_s_nvmc_eep_execsrvtype == (U1)NVMC_REQUEST_TYPE_INVALID){
        u1_t_ret = (U1)TRUE;
    }
    return(u1_t_ret);
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
/*  1.0.0            8/27/2015  KM      New.                                                                                         */
/*  1.0.1            9/29/2015  KM      Updated.                                                                                     */
/*  1.0.2           10/16/2015  KS      Revision Updated.                                                                            */
/*  1.0.3           10/22/2015  KM      Add vd_g_Nvm_Eep_Init function Call.                                                         */
/*  1.0.4           11/ 6/2015  KS      Revision Updated.                                                                            */
/*  1.0.5           11/11/2015  KM      Bug fix.                                                                                     */
/*  1.0.6            2/29/2016  KM      Fixed Version Check.                                                                         */
/*  1.0.7            3/25/2016  KM      Fixed Unit Test issue.                                                                       */
/*  1.0.8           04/11/2016  HK      Fixed function comments.                                                                     */
/*  1.0.9            4/12/2016  KM      Deleted unnecessary include.                                                                 */
/*  1.0.10           4/15/2016  KM      Revision Updated.                                                                            */
/*  1.0.11           4/18/2016  KM      Fixed initial value of u2_s_nvmc_eep_timer.                                                  */
/*  1.0.12           5/16/2016  HK      Fixed PCS3-2 issue.                                                                          */
/*  1.1.0           10/28/2016  HK      Changed with the small sector correspondence.                                                */
/*  1.1.1            8/28/2017  HK      Fixed AIP3GBSW-146 issue.                                                                    */
/*  1.1.2            3/20/2018  HK      Fixed AIP3GBSW-266 issue.                                                                    */
/*  1.1.3           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * KS      = Kenichi Sakai, Denso Create                                                                                          */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
