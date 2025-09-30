/* 2.1.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Memory Service for Trip Computer                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_MS_C_MAJOR                      (2)
#define TRIPCOM_MS_C_MINOR                      (1)
#define TRIPCOM_MS_C_PATCH                      (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_ms_cfg_private.h"
#include "tripcom_ms.h"
#include "tripcom_private.h"
#include "tripcom_nvmif.h"
#include "tripcom_nvmif_grph.h"
#include "avggrph.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TRIPCOM_MS_C_MAJOR != TRIPCOM_MS_H_MAJOR) || \
     (TRIPCOM_MS_C_MINOR != TRIPCOM_MS_H_MINOR) || \
     (TRIPCOM_MS_C_PATCH != TRIPCOM_MS_H_PATCH))
#error "tripcom_ms.c and tripcom_ms.h : source and header files are inconsistent!"
#endif

#if ((TRIPCOM_MS_C_MAJOR != TRIPCOM_MS_CFG_H_MAJOR) || \
     (TRIPCOM_MS_C_MINOR != TRIPCOM_MS_CFG_H_MINOR) || \
     (TRIPCOM_MS_C_PATCH != TRIPCOM_MS_CFG_H_PATCH))
#error "tripcom_ms.c and tripcom_ms_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPCOM_MS_NVMR_CTRL_RUN_C              (0x00U)
#define TRIPCOM_MS_NVMR_CTRL_RUN_R              (0x01U)
#define TRIPCOM_MS_NVMR_CTRL_FIN                (0x02U)
#define TRIPCOM_MS_NVMR_CTRL_INA                (0x04U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_tripcom_ms_igsts;
static  U4                                      u4_sp_tripcom_ms_value[TRIPCOM_MS_NUM_ID];
static  U1                                      u1_sp_tripcom_ms_nvmsts[TRIPCOM_NVMIF_CH_NUM];
static  U1                                      u1_sp_tripcom_ms_nvmgrphsts[TRIPCOM_NVMIF_GRPH_CH_NUM];
static  U1                                      u1_sp_tripcom_ms_rimsts[TRIPCOM_MS_NUM_ID];
static  U1                                      u1_s_tripcom_ms_diag_ctrl;
static  U1                                      u1_s_tripcom_ms_diag_rsltok;
static  U1                                      u1_s_tripcom_ms_grph_diag_ctrl;
static  U1                                      u1_s_tripcom_ms_grph_diag_rsltok;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/* void            vd_g_TripcomMsBonInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsBonInit(void)
{
    const ST_TRIPCOM_MS_MEM *                   stp_t_MEM;
    U4                                          u4_t_loop;


    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u4_t_loop];

        if ((stp_t_MEM->u1_devtype                        >= (U1)TRIPCOM_MS_DEV_NVM) ||
            (stp_t_MEM->u2_memoryid                       == (U2)U2_MAX            ) ||
            (fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype] == vdp_PTR_NA            )) {
            /* Do Nothing */
        }
        else if (stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_BR_Z) {
            (*fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype])(stp_t_MEM->u2_memoryid, (U4)0U);
        }
        else { /* if(stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_BR_M) */
            (*fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype])(stp_t_MEM->u2_memoryid, (U4)U4_MAX);
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsInit(void)
{
    const ST_TRIPCOM_MS_MEM *                   stp_t_MEM;
    U4                                          u4_t_loop;
    U4                                          u4_t_value;
    U1                                          u1_t_memsts;
    U1                                          u1_t_readsts;


    u1_s_tripcom_ms_igsts       = (U1)FALSE;
    u1_s_tripcom_ms_diag_ctrl   = (U1)TRIPCOM_MS_NVMR_CTRL_INA;
    u1_s_tripcom_ms_diag_rsltok = (U1)FALSE;
    u1_s_tripcom_ms_grph_diag_ctrl   = (U1)TRIPCOM_MS_NVMR_CTRL_INA;
    u1_s_tripcom_ms_grph_diag_rsltok = (U1)FALSE;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {

        stp_t_MEM    = &st_gp_TRIPCOM_MS_MEM_CFG[u4_t_loop];
        u4_t_value   = (U4)0U;
        u1_t_readsts = (U1)TRIPCOM_STSBIT_VALID;

        if (stp_t_MEM->u1_devtype < (U1)TRIPCOM_MS_NUM_DEV) {
            if ((stp_t_MEM->u2_memoryid                                  != (U2)U2_MAX) &&
                (st_gp_TRIPCOM_MS_RDIF[stp_t_MEM->u1_devtype].fp_u1_RDIF != vdp_PTR_NA)) {

                u1_t_memsts = st_gp_TRIPCOM_MS_RDIF[stp_t_MEM->u1_devtype].fp_u1_RDIF(stp_t_MEM->u2_memoryid, &u4_t_value);
                if (u1_t_memsts != (U1)0U) {
                    u1_t_readsts = (U1)TRIPCOM_STSBIT_INVALID;
                }
            }
            else {
                u1_t_readsts = (U1)TRIPCOM_STSBIT_INVALID;
            }
        }
        if (u1_t_readsts == (U1)TRIPCOM_STSBIT_VALID) {
            u4_sp_tripcom_ms_value[u4_t_loop] = u4_t_value;
        }
        else {
            if(stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_BR_M){
                u4_sp_tripcom_ms_value[u4_t_loop] = (U4)U4_MAX;
            }
            else{
                u4_sp_tripcom_ms_value[u4_t_loop] = (U4)0U;
            }
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_CH_NUM; u4_t_loop++) {
        u1_sp_tripcom_ms_nvmsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_NON;
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++) {
        u1_sp_tripcom_ms_nvmgrphsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_NON;
    }
    vd_g_TripcomMsClrRimRslt();

}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsMainTask(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsMainTask(void)
{
    const ST_TRIPCOM_MS_MEM *                   stp_t_MEM;
    U4                                          u4_t_loop;
    U1                                          u1_t_igsts;
    U1                                          u1_t_esi_chk;
    U1                                          u1_t_id;

    u1_t_igsts   = u1_g_TripcomMsIgnOn();
    u1_t_esi_chk = u1_g_TripcomMsEsichk();

    if ((u1_t_esi_chk           == (U1)0U   ) &&
        (u1_t_igsts             == (U1)FALSE) &&
        (u1_s_tripcom_ms_igsts  == (U1)TRUE )) {

        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
            stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u4_t_loop];

            if ((stp_t_MEM->u1_devtype                         < (U1)TRIPCOM_MS_NUM_DEV) &&
                (stp_t_MEM->u2_memoryid                       != (U2)U2_MAX            ) &&
                (fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype] != vdp_PTR_NA            )) {

                fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype](stp_t_MEM->u2_memoryid, u4_sp_tripcom_ms_value[u4_t_loop]);
            }
        }

        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_CH_NUM; u4_t_loop++) {
            u1_t_id = u1_gp_TRIPCOM_MS_CH2ID[u4_t_loop];
            (void)u1_g_TripcomNvmIfRWRqst((U1)u4_t_loop, &u4_sp_tripcom_ms_value[u1_t_id]);
        }
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++) {
            u1_t_id = u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop];
            (void)u1_g_TripcomNvmIfGrphRWRqst((U1)u4_t_loop, &u4_sp_tripcom_ms_value[u1_t_id]);
        }

    }
    u1_s_tripcom_ms_igsts = u1_t_igsts;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_CH_NUM; u4_t_loop++) {
        u1_t_id = u1_gp_TRIPCOM_MS_CH2ID[u4_t_loop];
        if(u1_sp_tripcom_ms_nvmsts[u4_t_loop] == (U1)TRIPCOM_MS_NVMSTS_REQ){
            (void)u1_g_TripcomNvmIfRWRqst((U1)u4_t_loop, &u4_sp_tripcom_ms_value[u1_t_id]);
            u1_sp_tripcom_ms_nvmsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_WAIT;
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++) {
        u1_t_id = u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop];
        if(u1_sp_tripcom_ms_nvmgrphsts[u4_t_loop] == (U1)TRIPCOM_MS_NVMSTS_REQ){
            (void)u1_g_TripcomNvmIfGrphRWRqst((U1)u4_t_loop, &u4_sp_tripcom_ms_value[u1_t_id]);
            u1_sp_tripcom_ms_nvmgrphsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_WAIT;
        }
    }
}

/*===================================================================================================================================*/
/* U4              u4_g_TripcomMsGetAccmltVal(const U1 u1_a_ID)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4              u4_g_TripcomMsGetAccmltVal(const U1 u1_a_ID)
{
    U4          u4_t_value;


    if (u1_a_ID < (U1)TRIPCOM_MS_NUM_ID) {
        u4_t_value = u4_sp_tripcom_ms_value[u1_a_ID];
    }
    else {
        u4_t_value = (U4)0U;
    }
    return (u4_t_value);
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsSetAccmltVal(const U1 u1_a_ID, const U4 u4_a_VAL)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSetAccmltVal(const U1 u1_a_ID, const U4 u4_a_VAL)
{
    if (u1_a_ID < (U1)TRIPCOM_MS_NUM_ID) {
        u4_sp_tripcom_ms_value[u1_a_ID] = u4_a_VAL;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsSetNvmRqst(const U1 u1_a_ID)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSetNvmRqst(const U1 u1_a_ID)
{
    const ST_TRIPCOM_MS_MEM *   stp_t_MEM;
    U4                          u4_t_loop;
    U1                          u1_t_memsts;
    U4                          u4_t_value;

    if(u1_a_ID < (U1)TRIPCOM_MS_NUM_ID){
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u1_a_ID];

        if((stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_BR_Z) ||        /* +B Backup Memory */
           (stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_BR_M)){
            if((stp_t_MEM->u2_memoryid                                  != (U2)U2_MAX) &&
               (fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype]            != vdp_PTR_NA) &&
               (st_gp_TRIPCOM_MS_RDIF[stp_t_MEM->u1_devtype].fp_u1_RDIF != vdp_PTR_NA)) {

                fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype](stp_t_MEM->u2_memoryid, u4_sp_tripcom_ms_value[u1_a_ID]);
                u1_t_memsts = st_gp_TRIPCOM_MS_RDIF[stp_t_MEM->u1_devtype].fp_u1_RDIF(stp_t_MEM->u2_memoryid, &u4_t_value);
                if(((u1_t_memsts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK         )
                && (u4_t_value                               == u4_sp_tripcom_ms_value[u1_a_ID])){
                    u1_sp_tripcom_ms_rimsts[u1_a_ID] = (U1)TRIPCOM_MS_NVMSTS_SUC;
                }
                else{
                    u1_sp_tripcom_ms_rimsts[u1_a_ID] = (U1)TRIPCOM_MS_NVMSTS_FAIL;
                }
            }
        }
        else if(stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM){       /* Non Volatile Memory */
            if(stp_t_MEM->u1_nvmifch < (U1)TRIPCOM_NVMIF_CH_NUM){
                u1_sp_tripcom_ms_nvmsts[stp_t_MEM->u1_nvmifch] = (U1)TRIPCOM_MS_NVMSTS_REQ;
            }
            for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++) {
                if((u1_a_ID >= u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop])
                && (u1_a_ID <  (u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop] + (U1)TRIPCOM_NVMIF_GRPH_GRP_SIZE))){
                    u1_sp_tripcom_ms_nvmgrphsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_REQ;
                }
            }
        }
        else{                                                           /* Volatile Memory */
            /* nothing */
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsSetNvmRslt(const U1 u1_a_ID, const U1 u1_a_rslt)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSetNvmRslt(const U1 u1_a_ID, const U1 u1_a_rslt)
{
    if (u1_a_ID < (U1)TRIPCOM_NVMIF_CH_NUM) {
        if(u1_sp_tripcom_ms_nvmsts[u1_a_ID] == (U1)TRIPCOM_MS_NVMSTS_WAIT){
            u1_sp_tripcom_ms_nvmsts[u1_a_ID] = u1_a_rslt;
        }
    }
    vd_g_AvgGrphUpdtRslt();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsSetNvmGrphRslt(const U1 u1_a_ID, const U1 u1_a_rslt)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSetNvmGrphRslt(const U1 u1_a_ID, const U1 u1_a_rslt)
{
    if (u1_a_ID < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM) {
        if(u1_sp_tripcom_ms_nvmgrphsts[u1_a_ID] == (U1)TRIPCOM_MS_NVMSTS_WAIT){
            u1_sp_tripcom_ms_nvmgrphsts[u1_a_ID] = u1_a_rslt;
        }
    }
    vd_g_AvgGrphUpdtRslt();
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsClrRimRslt(const U1 u1_a_ID, const U1 u1_a_rslt)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsClrRimRslt(void)
{
    U4                          u4_t_loop;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
        u1_sp_tripcom_ms_rimsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_NON;
    }
    vd_g_AvgGrphUpdtRslt();
}

/*===================================================================================================================================*/
/* U1              u1_g_TripcomMsGetNvmRslt(const U1 u1_a_ID)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_TripcomMsGetNvmRslt(const U1 u1_a_ID)
{
    const ST_TRIPCOM_MS_MEM *   stp_t_MEM;
    U4                          u4_t_loop;
    U1                          u1_t_rslt;

    u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_NON;
    if (u1_a_ID < (U1)TRIPCOM_MS_NUM_ID) {
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u1_a_ID];

        if((stp_t_MEM->u1_devtype  == (U1)TRIPCOM_MS_DEV_BR_Z) ||       /* +B Backup Memory */
           (stp_t_MEM->u1_devtype  == (U1)TRIPCOM_MS_DEV_BR_M)){
            if(stp_t_MEM->u2_memoryid != (U2)U2_MAX){
                u1_t_rslt = u1_sp_tripcom_ms_rimsts[u1_a_ID];
            }
        }
        else if(stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM){       /* Non Volatile Memory */
            if(stp_t_MEM->u1_nvmifch < (U1)TRIPCOM_NVMIF_CH_NUM){
                u1_t_rslt = u1_sp_tripcom_ms_nvmsts[stp_t_MEM->u1_nvmifch];
            }
            for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_CH_NUM; u4_t_loop++) {
                if((u1_a_ID >= u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop])
                && (u1_a_ID <  (u1_gp_TRIPCOM_MS_GRPH_CH2ID[u4_t_loop] + (U1)TRIPCOM_NVMIF_GRPH_GRP_SIZE))){
                    u1_t_rslt = u1_sp_tripcom_ms_nvmgrphsts[u4_t_loop];
                }
            }
        }
        else{ /* if(stp_t_MEM->u1_devtype >= (U1)TRIPCOM_MS_NUM_DEV) */  /* Volatile Memory */
            u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_SUC;
        }
    }
    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfCbkData(const U1 u1_a_CH, const U4 u4_a_DATA_NVM)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfCbkData(const U1 u1_a_CH, const U4 u4_a_DATA_NVM)
{
    U1          u1_t_id;

    if (u1_a_CH < (U1)TRIPCOM_NVMIF_CH_NUM) {
        u1_t_id = u1_gp_TRIPCOM_MS_CH2ID[u1_a_CH];
        u4_sp_tripcom_ms_value[u1_t_id] = u4_a_DATA_NVM;

        vd_g_TripcomMsSyncUpdtImm(u1_a_CH);
    }

}

/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphCbkData(const U1 u1_a_CH, const U4 u4_a_DATA_NVM)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfGrphCbkData(const U1 u1_a_CH, const ST_TRIPCOM_GRPH_NVMDATA * const st_ap_DATANVM)
{
    U1          u1_t_id;
    U4          u4_t_loop;

    if (u1_a_CH < (U1)TRIPCOM_NVMIF_GRPH_CH_NUM) {
        u1_t_id = u1_gp_TRIPCOM_MS_GRPH_CH2ID[u1_a_CH];

        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_NVMIF_GRPH_GRP_SIZE; u4_t_loop++) {
            if(st_ap_DATANVM != vdp_PTR_NA){
                u4_sp_tripcom_ms_value[u1_t_id + u4_t_loop] = st_ap_DATANVM->u4_value[u4_t_loop];
            }
            else{
                u4_sp_tripcom_ms_value[u1_t_id + u4_t_loop] = (U4)0xFFFFFFFFU;
            }
        }
    }

}

/*===================================================================================================================================*/
/*  void    u1_g_TripcomNvmClear(const U1 u1_a_REQ, const U1 u1_a_RUN)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_TripcomNvmClear(const U1 u1_a_REQ, const U1 u1_a_RUN)
{
    U1          u1_t_ctrl;
    U1          u1_t_grphctrl;
    U1          u1_t_req;
    U1          u1_t_grphreq;
    U1          u1_t_rslt;

    u1_t_ctrl = u1_s_tripcom_ms_diag_ctrl;
    u1_t_grphctrl = u1_s_tripcom_ms_grph_diag_ctrl;
    if(u1_a_REQ > (U1)TRIPCOM_NVMIF_DIAG_REQ_WRI){

        u1_t_rslt = (U1)TRIPCOM_NVMR_RES_UNK;
    }
    else if ((u1_t_ctrl     >= (U1)TRIPCOM_MS_NVMR_CTRL_FIN)
          && (u1_t_grphctrl >= (U1)TRIPCOM_MS_NVMR_CTRL_FIN)) {
        u1_t_req = u1_t_ctrl & (U1)TRIPCOM_NVMIF_DIAG_REQ_WRI;
        u1_t_grphreq = u1_t_grphctrl & (U1)TRIPCOM_NVMIF_GRPH_DIAG_REQ_WRI;
        if (u1_a_RUN == (U1)TRUE) {

            u1_s_tripcom_ms_diag_ctrl   = u1_a_REQ;
            u1_s_tripcom_ms_diag_rsltok = (U1)FALSE;

            vd_g_TripcomNvmIfDiagStart(u1_a_REQ);

            u1_s_tripcom_ms_grph_diag_ctrl   = u1_a_REQ;
            u1_s_tripcom_ms_grph_diag_rsltok = (U1)FALSE;

            vd_g_TripcomNvmIfGrphDiagStart(u1_a_REQ);

            u1_t_rslt = (U1)TRIPCOM_NVMR_RES_RUN;
        }
        else if ((u1_t_req != u1_a_REQ) || (u1_t_grphreq != u1_a_REQ)) {
            u1_t_rslt = (U1)TRIPCOM_NVMR_RES_UNK;
        }
        else if ((u1_s_tripcom_ms_diag_rsltok == (U1)TRUE) && (u1_s_tripcom_ms_grph_diag_rsltok == (U1)TRUE)) {
            u1_t_rslt = (U1)TRIPCOM_NVMR_RES_SUC;
        }
        else {
            u1_t_rslt = (U1)TRIPCOM_NVMR_RES_FAI;
        }
    }
    else if ((u1_t_ctrl == u1_a_REQ) || (u1_t_grphctrl ==  u1_a_REQ)) {
        u1_t_rslt = (U1)TRIPCOM_NVMR_RES_RUN;
    }
    else {
        u1_t_rslt = (U1)TRIPCOM_NVMR_RES_UNK;
    }

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfDiagFinish(const U1 u1_a_RSLT)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfDiagFinish(const U1 u1_a_RSLT)
{
    u1_s_tripcom_ms_diag_rsltok  = u1_a_RSLT;
    u1_s_tripcom_ms_diag_ctrl   |= (U1)TRIPCOM_MS_NVMR_CTRL_FIN;
}
/*===================================================================================================================================*/
/*  void    vd_g_TripcomNvmIfGrphDiagFinish(const U1 u1_a_RSLT)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomNvmIfGrphDiagFinish(const U1 u1_a_RSLT)
{
    u1_s_tripcom_ms_grph_diag_rsltok  = u1_a_RSLT;
    u1_s_tripcom_ms_grph_diag_ctrl   |= (U1)TRIPCOM_MS_NVMR_CTRL_FIN;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/07/2018  HY       New.                                                                                               */
/*  1.0.1    03/11/2020  YA       Change for 800B CV                                                                                 */
/*  1.0.2    07/13/2020  YA       Delete F/H Economy Display Value Definition                                                        */
/*                                Add u1_g_TripcomMsEsichk for support ESInspect                                                     */
/*                                Add Initial Value Selection                                                                        */
/*  1.0.3    10/07/2020  YA       Change for 800B CV-R.                                                                              */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*  2.0.2    10/25/2021  TA(M)    Supports TripA and TripB.                                                                          */
/*  2.0.3    08/08/2022  YI       Add TRIPCOM_MS_ID_EVDTE_PCT.                                                                       */
/*  2.1.0    01/10/2024  TH       Add TRIPCOM_MS_ID_AVGGRPH  .                                                                       */
/*  2.1.1    06/24/2024  SM       Added vd_g_TripcomMsSyncUpdtImm to fix bug MET19PFV3-16362                                         */
/*  2.1.2    02/17/2025  MaO(M)   Improving processing load(vd_g_TripcomMsSetNvmRqst, u1_g_TripcomMsGetNvmRslt)                      */
/*  2.1.3    04/18/2025  TH       Fix: Update Result when Clear Rim Result                                                           */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
