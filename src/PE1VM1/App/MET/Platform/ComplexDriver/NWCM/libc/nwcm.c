/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  NVM Write Count Manager                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NWCM_C_MAJOR                            (1U)
#define NWCM_C_MINOR                            (0U)
#define NWCM_C_PATCH                            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "nwcm_cfg_private.h"

#include "crc32.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((NWCM_C_MAJOR != NWCM_CFG_PRIVATE_H_MAJOR) || \
     (NWCM_C_MINOR != NWCM_CFG_PRIVATE_H_MINOR) || \
     (NWCM_C_PATCH != NWCM_CFG_PRIVATE_H_PATCH))
#error "nwcm.c and nwcm_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define NWCM_DATA_SIZE_MAX                      (7U)
#define NWCM_NVM_DATA_SIZE                      (28U)

#define NWCM_NVM_ID_CRC                         (0U)
#define NWCM_NVM_ID_CNT                         (1U)
#define NWCM_NVM_ID_DATA                        (2U)

#define NWCM_NVM_WRITE_INIT                     (0x0000U)
#define NWCM_NVM_WRITE_START                    (0x0100U)
#define NWCM_NVM_WRITE_BRAMCOMP                 (0x0200U)
#define NWCM_NVM_WRITE_NVMCOMP                  (0x0300U)
#define NWCM_NVM_WRITE_STATE_MASK               (0x00FFU)
#define NWCM_NVM_WRITE_ID_MASK                  (0xFF00U)

#if (NWCM_INIT_FUNC_EN == 1U)
#define NWCM_NVM_WRITE_ENABLE                   (0U)
#define NWCM_NVM_WRITE_DISABLE                  (1U)
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1               u1_s_nwcm_chk_mng_id;
static U1               u1_s_nwcm_chk_data_id;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_NWCMCheckCRCMgr(void);
static void     vd_s_NWCMCheckCRC(void);
static U1       u1_s_NWCMLatestID(const U1 u1_a_MNG_ID, U1 *u1_ap_DATA_ID, U1 *u1_ap_DATA);
#if (NWCM_INIT_FUNC_EN == 1U)
static void     vd_s_NWCMCheckInitNVM(void);
static U1       u1_s_NWCMMemcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size);
static U1       u1_s_NWCMCheckWriteInitCond(const U1 u1_a_ID);
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_NWCMBonInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NWCMBonInit(void)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_nvmcdata[NWCM_DATA_SIZE_MAX];
    U1                          u1_t_mng_id;
    U1                          u1_t_data_id;

    for(u1_t_mng_id = (U1)0U; u1_t_mng_id < u1_g_NWCM_NUM_MNG_ID; u1_t_mng_id++){
        st_tp_ID = &st_gp_NWCM_CFG[u1_t_mng_id];
        for(u1_t_data_id = (U1)0U; u1_t_data_id < st_tp_ID->u1_nvmcid_num; u1_t_data_id++){
            (void)u1_g_Nvmc_ReadOthrwithSts(st_tp_ID->u2p_NVMCID[u1_t_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_nvmcdata[0]);
            vd_g_Rim_WriteOther(st_tp_ID->u2p_RIMID[u1_t_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_nvmcdata[0]);
        }
        vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)NWCM_NVM_WRITE_INIT);
#if (NWCM_INIT_FUNC_EN == 1U)
        vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_t_mng_id], (U1)NWCM_NVM_INIT_NOTREQ);
        vd_g_Rim_WriteU1(u2_gp_NWCM_WRITE_CTRL_RIMID[u1_t_mng_id], (U1)NWCM_NVM_WRITE_ENABLE);
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
    }
    u1_s_nwcm_chk_mng_id = (U1)0U;
    u1_s_nwcm_chk_data_id = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_NWCMWkupInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NWCMWkupInit(void)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_nvmcdata[NWCM_DATA_SIZE_MAX];
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U1                          u1_t_mng_id;
    U1                          u1_t_data_id;
    U2                          u2_t_write_state_id;
    U2                          u2_t_write_state;
    U2                          u2_t_write_id;

    for(u1_t_mng_id = (U1)0U; u1_t_mng_id < u1_g_NWCM_NUM_MNG_ID; u1_t_mng_id++){
        st_tp_ID = &st_gp_NWCM_CFG[u1_t_mng_id];
        (void)u1_g_Rim_ReadU2withStatus(st_tp_ID->u2_write_state_id, &u2_t_write_state_id);
        u2_t_write_state = u2_t_write_state_id & (U2)NWCM_NVM_WRITE_ID_MASK;
        u2_t_write_id    = u2_t_write_state_id & (U2)NWCM_NVM_WRITE_STATE_MASK;
        for(u1_t_data_id = (U1)0U; u1_t_data_id < st_tp_ID->u1_nvmcid_num; u1_t_data_id++){
            if((u2_t_write_state == (U2)NWCM_NVM_WRITE_START) && (u2_t_write_id == (U2)u1_t_data_id)){
                (void)u1_g_Nvmc_ReadOthrwithSts(st_tp_ID->u2p_NVMCID[u1_t_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_nvmcdata[0]);
                vd_g_Rim_WriteOther(st_tp_ID->u2p_RIMID[u1_t_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_nvmcdata[0]);
            }
            else if((u2_t_write_state == (U2)NWCM_NVM_WRITE_BRAMCOMP) && (u2_t_write_id == (U2)u1_t_data_id)){
                (void)u1_g_Rim_ReadOtherwithStatus(st_tp_ID->u2p_RIMID[u1_t_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_rimdata[0]);
                vd_g_Nvmc_WriteOthr(st_tp_ID->u2p_NVMCID[u1_t_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_rimdata[0]);
            }
            else{
                /* Do Nothing */
            }
        }
        vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)NWCM_NVM_WRITE_INIT);
    }
    u1_s_nwcm_chk_mng_id = (U1)0U;
    u1_s_nwcm_chk_data_id = (U1)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_NWCMMainTask(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NWCMMainTask(void)
{
    vd_s_NWCMCheckCRCMgr();
#if (NWCM_INIT_FUNC_EN == 1U)
    vd_s_NWCMCheckInitNVM();
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
}
/*===================================================================================================================================*/
/*  U1      u1_g_NWCMReadData(const U1 u1_a_ID, U1 *u1_ap_data, const U1 u1_a_size)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_NWCMReadData(const U1 u1_a_ID, U1 *u1_ap_data, const U1 u1_a_size)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U1                          u1_t_latest_data_id;
    U1                          u1_t_ret;
    U1                          u1_t_data_size;

    u1_t_ret                    = (U1)0U;
    u1_t_latest_data_id         = (U1)0U;

    for(u1_t_data_size = (U1)0U; u1_t_data_size < (U1)NWCM_DATA_SIZE_MAX; u1_t_data_size++){
        u4_tp_rimdata[u1_t_data_size] = (U4)0;
    }

    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
        st_tp_ID = &st_gp_NWCM_CFG[u1_a_ID];
        if(u1_a_size != st_tp_ID->u1_nvm_datasize){
            u1_t_ret = (U1)NWCM_RESULT_NG_SIZE;
        }
    }
    else{
        u1_t_ret = (U1)NWCM_RESULT_NG_ID;
    }

    if(u1_t_ret == (U1)0U){
        u1_t_ret = u1_s_NWCMLatestID(u1_a_ID, &u1_t_latest_data_id, (U1 *)&u4_tp_rimdata[0]);
        if(u1_t_ret < (U1)NWCM_RESULT_NG_NO_READABLE_DATA){
            vd_g_MemcpyU1(u1_ap_data, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_DATA], (U4)u1_a_size);
        }
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_NWCMWriteData(const U1 u1_a_ID, const U1 *u1_ap_data, const U1 u1_a_size)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_NWCMWriteData(const U1 u1_a_ID, const U1 *u1_ap_data, const U1 u1_a_size)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U1                          u1_t_latest_data_id;
    U1                          u1_t_write_data_id;
    U1                          u1_t_ret;
    U4                          u4_t_crc32;
    U1                          u1_t_data_size;

    u1_t_ret                    = (U1)0U;
    u1_t_latest_data_id         = (U1)0U;

    for(u1_t_data_size = (U1)0U; u1_t_data_size < (U1)NWCM_DATA_SIZE_MAX; u1_t_data_size++){
        u4_tp_rimdata[u1_t_data_size] = (U4)0;
    }

    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
#if (NWCM_INIT_FUNC_EN == 1U)
        u1_t_ret = u1_s_NWCMCheckWriteInitCond(u1_a_ID);
        if(u1_t_ret == (U1)0U){
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
            st_tp_ID = &st_gp_NWCM_CFG[u1_a_ID];
            if(u1_a_size != st_tp_ID->u1_nvm_datasize){
                u1_t_ret = (U1)NWCM_RESULT_NG_SIZE;
            }
#if (NWCM_INIT_FUNC_EN == 1U)
        }
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
    }
    else{
        u1_t_ret = (U1)NWCM_RESULT_NG_ID;
    }

    if(u1_t_ret == (U1)0U){
        (void)u1_s_NWCMLatestID(u1_a_ID, &u1_t_latest_data_id, (U1 *)&u4_tp_rimdata[0]);
        if(u1_t_latest_data_id < (st_tp_ID->u1_nvmcid_num - (U1)1U)){
            u1_t_write_data_id = u1_t_latest_data_id + (U1)1U;
        }
        else
        {
            u1_t_write_data_id = (U1)0U;
        }

        vd_g_MemcpyU1((U1 *)&u4_tp_rimdata[NWCM_NVM_ID_DATA], u1_ap_data, (U4)u1_a_size);
        if(u4_tp_rimdata[NWCM_NVM_ID_CNT] != (U4)U4_MAX){
            u4_tp_rimdata[NWCM_NVM_ID_CNT]++;
        }
        u4_t_crc32 = u4_g_Crc32((U4)U4_MAX, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_CNT], (U4)st_tp_ID->u1_nvm_datasize + (U4)4U, (U1)FALSE);
        u4_tp_rimdata[NWCM_NVM_ID_CRC] = u4_t_crc32;

        vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)(NWCM_NVM_WRITE_START | u1_t_write_data_id));
        vd_g_Rim_WriteOther(st_tp_ID->u2p_RIMID[u1_t_write_data_id], (U2)u1_a_size + (U2)8U, (U1 *)&u4_tp_rimdata[0]);
        vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)(NWCM_NVM_WRITE_BRAMCOMP | u1_t_write_data_id));
        vd_g_Nvmc_WriteOthr(st_tp_ID->u2p_NVMCID[u1_t_write_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_rimdata[0]);
        vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)NWCM_NVM_WRITE_NVMCOMP);

#if (NWCM_INIT_FUNC_EN == 1U)
        vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], (U1)NWCM_NVM_INIT_NOTREQ);
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
    }
    return(u1_t_ret);
}
#if (NWCM_INIT_FUNC_EN == 1U)
/*===================================================================================================================================*/
/*  U1      u1_g_NWCMInitData(const U1 u1_a_ID, const U1 *u1_ap_data, const U1 u1_a_size)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_NWCMInitData(const U1 u1_a_ID, const U1 *u1_ap_data, const U1 u1_a_size)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_nvmcdata[NWCM_DATA_SIZE_MAX];
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U1                          u1_t_data_id;
    U1                          u1_t_rimresult;
    U1                          u1_t_ret;
    U4                          u4_t_crc32;
    U1                          u1_t_init_state;
    U1                          u1_t_nvmc_read;
    U1                          u1_t_memcmp_chk;

    u1_t_ret                    = (U1)0U;
    u1_t_init_state             = (U1)NWCM_NVM_INIT_NOTREQ;

    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
        u1_t_rimresult = u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], &u1_t_init_state);
        if(u1_t_rimresult != (U1)RIM_RESULT_OK){
            u1_t_init_state = (U1)NWCM_NVM_INIT_NOTREQ;
            vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], (U1)NWCM_NVM_INIT_NOTREQ);
        }
        if(u1_t_init_state != (U1)NWCM_NVM_INIT_START){
            st_tp_ID = &st_gp_NWCM_CFG[u1_a_ID];
            if(u1_a_size != st_tp_ID->u1_nvm_datasize){
                u1_t_ret = (U1)NWCM_RESULT_NG_SIZE;
            }
        }
        else{
            u1_t_ret = (U1)NWCM_RESULT_NG_INIT;
        }
    }
    else{
        u1_t_ret = (U1)NWCM_RESULT_NG_ID;
    }

    if(u1_t_ret == (U1)0U){
        vd_g_MemcpyU1((U1 *)&u4_tp_rimdata[NWCM_NVM_ID_DATA], u1_ap_data, (U4)u1_a_size);
        u4_tp_rimdata[NWCM_NVM_ID_CNT] = (U4)0U;
        u4_t_crc32 = u4_g_Crc32((U4)U4_MAX, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_CNT], (U4)st_tp_ID->u1_nvm_datasize + (U4)4U, (U1)FALSE);
        u4_tp_rimdata[NWCM_NVM_ID_CRC] = u4_t_crc32;

        for(u1_t_data_id = (U1)0U; u1_t_data_id < st_tp_ID->u1_nvmcid_num; u1_t_data_id++){
            u1_t_nvmc_read = u1_g_Nvmc_ReadOthrwithSts(st_tp_ID->u2p_NVMCID[u1_t_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_nvmcdata[0]);
            if(u1_t_nvmc_read == (U1)NVMC_STATUS_COMP){
                u1_t_memcmp_chk = u1_s_NWCMMemcmp((U1 *)&u4_tp_rimdata[0], (U1 *)&u4_tp_nvmcdata[0], st_tp_ID->u1_nvm_datasize);
            }
            if((u1_t_nvmc_read != (U1)NVMC_STATUS_COMP)||(u1_t_memcmp_chk != (U1)TRUE)){
                vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)(NWCM_NVM_WRITE_START | u1_t_data_id));
                vd_g_Rim_WriteOther(st_tp_ID->u2p_RIMID[u1_t_data_id], (U2)u1_a_size + (U2)8U, (U1 *)&u4_tp_rimdata[0]);
                vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)(NWCM_NVM_WRITE_BRAMCOMP | u1_t_data_id));
                vd_g_Nvmc_WriteOthr(st_tp_ID->u2p_NVMCID[u1_t_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_rimdata[0]);
                vd_g_Rim_WriteU2(st_tp_ID->u2_write_state_id, (U2)NWCM_NVM_WRITE_NVMCOMP);
            }
        }
        vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], (U1)NWCM_NVM_INIT_START);
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1      u1_g_NWCMGetInitState(const U1 u1_a_ID)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_NWCMGetInitState(const U1 u1_a_ID)
{
    U1                          u1_t_init_state;

    u1_t_init_state             = (U1)NWCM_NVM_INIT_NOTREQ;

    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
        (void)u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], &u1_t_init_state);
    }
    return(u1_t_init_state);
}
/*===================================================================================================================================*/
/*  void    vd_g_NWCMWriteDisable(const U1 u1_a_ID)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NWCMWriteDisable(const U1 u1_a_ID)
{
    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
        vd_g_Rim_WriteU1(u2_gp_NWCM_WRITE_CTRL_RIMID[u1_a_ID], (U1)NWCM_NVM_WRITE_DISABLE);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_NWCMWriteEnable(const U1 u1_a_ID)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_NWCMWriteEnable(const U1 u1_a_ID)
{
    if(u1_a_ID < u1_g_NWCM_NUM_MNG_ID){
        vd_g_Rim_WriteU1(u2_gp_NWCM_WRITE_CTRL_RIMID[u1_a_ID], (U1)NWCM_NVM_WRITE_ENABLE);
    }
}
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
/*===================================================================================================================================*/
/*  static void    vd_s_NWCMCheckCRC(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_NWCMCheckCRCMgr(void)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U1                          u1_t_ret;
#if (NWCM_INIT_FUNC_EN == 1U)
    U1                          u1_t_init_state;

    u1_t_init_state             = (U1)NWCM_NVM_INIT_NOTREQ;
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */

    if(u1_s_nwcm_chk_mng_id >= u1_g_NWCM_NUM_MNG_ID){
        u1_s_nwcm_chk_mng_id = (U1)0U;
    }
    st_tp_ID = &st_gp_NWCM_CFG[u1_s_nwcm_chk_mng_id];
    if(u1_s_nwcm_chk_data_id >= st_tp_ID->u1_nvmcid_num){
        u1_s_nwcm_chk_data_id = (U1)0U;
    }
#if (NWCM_INIT_FUNC_EN == 1U)
    u1_t_ret = u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_INIT_STAT_RIMID[u1_s_nwcm_chk_mng_id], &u1_t_init_state);
    if(u1_t_ret != (U1)RIM_RESULT_OK){
        u1_t_init_state = (U1)NWCM_NVM_INIT_NOTREQ;
        vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_s_nwcm_chk_mng_id], (U1)NWCM_NVM_INIT_NOTREQ);
    }
    if(u1_t_init_state != (U1)NWCM_NVM_INIT_START){
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
        u1_t_ret = u1_g_Nvmc_GetDataSts(st_tp_ID->u2p_NVMCID[u1_s_nwcm_chk_data_id]);
        if(u1_t_ret != (U1)NVMC_STATUS_READING){
            vd_s_NWCMCheckCRC();
        }
#if (NWCM_INIT_FUNC_EN == 1U)
    }
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
}
/*===================================================================================================================================*/
/*  static void    vd_s_NWCMCheckCRC(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_NWCMCheckCRC(void)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_nvmcdata[NWCM_DATA_SIZE_MAX];
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U4                          u4_t_crc32;
    U1                          u1_t_ret;
    U1                          u1_t_nvmc_state;
    U1                          u1_t_rim_state;

    st_tp_ID = &st_gp_NWCM_CFG[u1_s_nwcm_chk_mng_id];
    u1_t_nvmc_state = (U1)FALSE;
    u1_t_rim_state = (U1)FALSE;

    u1_t_ret = u1_g_Nvmc_ReadOthrwithSts(st_tp_ID->u2p_NVMCID[u1_s_nwcm_chk_data_id], (U2)NWCM_NVM_DATA_SIZE, (U1 *)&u4_tp_nvmcdata[0]);
    if(u1_t_ret == (U1)NVMC_STATUS_COMP){
        u4_t_crc32 = u4_g_Crc32((U4)U4_MAX, (U1 *)&u4_tp_nvmcdata[NWCM_NVM_ID_CNT], (U4)st_tp_ID->u1_nvm_datasize + (U4)4U, (U1)FALSE);
        if(u4_t_crc32 == u4_tp_nvmcdata[NWCM_NVM_ID_CRC]){
            u1_t_nvmc_state = (U1)TRUE;
        }
    }
    u1_t_ret = u1_g_Rim_ReadOtherwithStatus(st_tp_ID->u2p_RIMID[u1_s_nwcm_chk_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_rimdata[0]);
    if(u1_t_ret == (U1)RIM_RESULT_OK){
        u4_t_crc32 = u4_g_Crc32((U4)U4_MAX, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_CNT], (U4)st_tp_ID->u1_nvm_datasize + (U4)4U, (U1)FALSE);
        if(u4_t_crc32 == u4_tp_rimdata[NWCM_NVM_ID_CRC]){
            u1_t_rim_state = (U1)TRUE;
        }
    }
    if((u1_t_nvmc_state != (U1)FALSE)&&(u1_t_rim_state != (U1)TRUE)){
        vd_g_Rim_WriteOther(st_tp_ID->u2p_RIMID[u1_s_nwcm_chk_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_nvmcdata[0]);
    }

    u1_s_nwcm_chk_data_id++;
    if(u1_s_nwcm_chk_data_id >= st_tp_ID->u1_nvmcid_num){
        u1_s_nwcm_chk_data_id = (U1)0U;
        u1_s_nwcm_chk_mng_id++;
        if(u1_s_nwcm_chk_mng_id >= u1_g_NWCM_NUM_MNG_ID){
            u1_s_nwcm_chk_mng_id = (U1)0U;
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_NWCMLatestID(const U1 u1_a_MNG_ID, U1 *u1_ap_DATA_ID, U1 *u1_ap_DATA)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_NWCMLatestID(const U1 u1_a_MNG_ID, U1 *u1_ap_DATA_ID, U1 *u1_ap_DATA)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U4                          u4_tp_rimdata[NWCM_DATA_SIZE_MAX];
    U4                          u4_t_hold_write_cnt;
    U1                          u1_t_data_id;
    U1                          u1_t_rimresult;
    U1                          u1_t_ret;
    U4                          u4_t_crc32;

    u1_t_ret = (U1)NWCM_RESULT_NG_NO_READABLE_DATA;
    u4_t_hold_write_cnt = (U4)0U;
    st_tp_ID = &st_gp_NWCM_CFG[u1_a_MNG_ID];

    for(u1_t_data_id = (U1)0U; u1_t_data_id < st_tp_ID->u1_nvmcid_num; u1_t_data_id++){
        u1_t_rimresult = u1_g_Rim_ReadOtherwithStatus(st_tp_ID->u2p_RIMID[u1_t_data_id], (U2)st_tp_ID->u1_nvm_datasize + (U2)8U, (U1 *)&u4_tp_rimdata[0]);
        if(u1_t_rimresult != (U1)RIM_RESULT_OK){
            u1_t_ret |= (U1)NWCM_RESULT_NG_BRAM;
        }
        else{
            u4_t_crc32 = u4_g_Crc32((U4)U4_MAX, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_CNT], (U4)st_tp_ID->u1_nvm_datasize + (U4)4U, (U1)FALSE);
            if(u4_t_crc32 != u4_tp_rimdata[NWCM_NVM_ID_CRC]){
                u1_t_ret |= (U1)NWCM_RESULT_NG_CRC;
            }
            else{
                u1_t_ret &= ~(U1)NWCM_RESULT_NG_NO_READABLE_DATA;
                if(u4_t_hold_write_cnt <= u4_tp_rimdata[NWCM_NVM_ID_CNT]){
                    *u1_ap_DATA_ID = u1_t_data_id;
                    vd_g_MemcpyU1(u1_ap_DATA, (U1 *)&u4_tp_rimdata[NWCM_NVM_ID_CRC], (U4)st_tp_ID->u1_nvm_datasize + (U4)8U);
                    u4_t_hold_write_cnt = u4_tp_rimdata[NWCM_NVM_ID_CNT];
                }
            }
        }
    }
    return(u1_t_ret);
}
#if (NWCM_INIT_FUNC_EN == 1U)
/*===================================================================================================================================*/
/*  static void    vd_s_NWCMCheckInitNVM(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_NWCMCheckInitNVM(void)
{
    const ST_NWCM_CFG *         st_tp_ID;
    U1                          u1_t_mng_id;
    U1                          u1_t_data_id;
    U1                          u1_t_ret;
    U1                          u1_t_init_state;
    U1                          u1_t_nvmc_error;

    u1_t_init_state             = (U1)NWCM_NVM_INIT_NOTREQ;

    for(u1_t_mng_id = (U1)0U; u1_t_mng_id < u1_g_NWCM_NUM_MNG_ID; u1_t_mng_id++){
        (void)u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_INIT_STAT_RIMID[u1_t_mng_id], &u1_t_init_state);
        if(u1_t_init_state == (U1)NWCM_NVM_INIT_START){
            st_tp_ID = &st_gp_NWCM_CFG[u1_t_mng_id];
            u1_t_nvmc_error = (U1)FALSE;
            for(u1_t_data_id = (U1)0U; u1_t_data_id < st_tp_ID->u1_nvmcid_num; u1_t_data_id++){
                u1_t_ret = u1_g_Nvmc_GetDataSts(st_tp_ID->u2p_NVMCID[u1_t_data_id]);
                if(u1_t_ret == (U1)NVMC_STATUS_ERRCOMP){
                    u1_t_nvmc_error = (U1)TRUE;
                }
                if(u1_t_ret == (U1)NVMC_STATUS_WRITING){
                    break;
                }
            }
            if(u1_t_data_id == st_tp_ID->u1_nvmcid_num){
                if(u1_t_nvmc_error != (U1)FALSE){
                    vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_t_mng_id], (U1)NWCM_NVM_INIT_ERROR);
                }
                else{
                    vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_t_mng_id], (U1)NWCM_NVM_INIT_COMP);
                }
            }
        }
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_NWCMMemcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_NWCMMemcmp(const U1 *u1_ap_data1, const U1 *u1_ap_data2, const U1 u1_a_size)
{
    U1                          u1_t_data_size;
    U1                          u1_t_ret;

    u1_t_ret = (U1)TRUE;

    for(u1_t_data_size = (U1)0U; u1_t_data_size < u1_a_size; u1_t_data_size++){
        if(u1_ap_data1[u1_t_data_size] != u1_ap_data2[u1_t_data_size]){
            u1_t_ret = (U1)FALSE;
            break;
        }
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_NWCMCheckWriteInitCond(const U1 u1_a_ID)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_NWCMCheckWriteInitCond(const U1 u1_a_ID)
{
    U1                          u1_t_rimresult;
    U1                          u1_t_ret;
    U1                          u1_t_write_disable;
    U1                          u1_t_init_state;

    u1_t_ret                    = (U1)0U;
    u1_t_init_state             = (U1)NWCM_NVM_INIT_NOTREQ;

    u1_t_rimresult = u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_WRITE_CTRL_RIMID[u1_a_ID], &u1_t_write_disable);
    if(u1_t_rimresult != (U1)RIM_RESULT_OK){
        u1_t_write_disable = (U1)NWCM_NVM_WRITE_ENABLE;
        vd_g_Rim_WriteU1(u2_gp_NWCM_WRITE_CTRL_RIMID[u1_a_ID], (U1)NWCM_NVM_WRITE_ENABLE);
    }
    if(u1_t_write_disable != (U1)NWCM_NVM_WRITE_DISABLE){
        u1_t_rimresult = u1_g_Rim_ReadU1withStatus(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], &u1_t_init_state);
        if(u1_t_rimresult != (U1)RIM_RESULT_OK){
            u1_t_init_state = (U1)NWCM_NVM_INIT_NOTREQ;
            vd_g_Rim_WriteU1(u2_gp_NWCM_INIT_STAT_RIMID[u1_a_ID], (U1)NWCM_NVM_INIT_NOTREQ);
        }
        if(u1_t_init_state == (U1)NWCM_NVM_INIT_START){
            u1_t_ret = (U1)NWCM_RESULT_NG_INIT;
        }
    }
    else{
        u1_t_ret = (U1)NWCM_RESULT_NG_DISABLE;
    }
    return(u1_t_ret);
}
#endif /* #if (NWCM_INIT_FUNC_EN == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     4/24/2023  TM       New.                                                                                               */
/*                                                                                                                                   */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
