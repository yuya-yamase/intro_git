/* 2.2.0 */
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
#define TRIPCOM_MS_C_MINOR                      (2)
#define TRIPCOM_MS_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tripcom_ms_cfg_private.h"
#include "tripcom_ms.h"
#include "tripcom_private.h"
#include "avggrph.h"
#include "memfill_u2.h"
#include "memfill_u4.h"

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
#define TRIPCOM_MS_GRAPH_ECON_NUM               (AVGGRPH_SIZE_TA + 1U)
#define TRIPCOM_MS_GRAPH_ECON_1ST_LAST          (0U)                           /* AVGGRPH_TAECON_HIST_1ST_LAST      */
#define TRIPCOM_MS_GRAPH_ECON_2ND_LAST          (1U)                           /* AVGGRPH_TAECON_HIST_2ND_LAST      */
#define TRIPCOM_MS_GRAPH_ECON_3RD_LAST          (2U)                           /* AVGGRPH_TAECON_HIST_3RD_LAST      */
#define TRIPCOM_MS_GRAPH_ECON_4TH_LAST          (3U)                           /* AVGGRPH_TAECON_HIST_4TH_LAST      */
#define TRIPCOM_MS_GRAPH_ECON_5TH_LAST          (4U)                           /* AVGGRPH_TAECON_HIST_5TH_LAST      */
#define TRIPCOM_MS_GRAPH_ECON_MAX               (5U)                           /* avggrph_taee_max                  */

#define TRIPCOM_MS_GRAPH_DATE_NUM               (AVGGRPH_SIZE_TA_DATE)

#define TRIPCOM_MS_GRAPH_ECON_BYTESIZE          (24U)                          /* TRIPCOM_MS_GRAPH_ECON_NUM * 4byte */
#define TRIPCOM_MS_GRAPH_DATE_BYTESIZE          (12U)                          /* TRIPCOM_MS_GRAPH_DATE_NUM * 2byte */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_tripcom_ms_igsts;
static  U4                                      u4_sp_tripcom_ms_value[TRIPCOM_MS_NUM_ID];
static  U4                                      u4_sp_tripcom_graph_econ_val[TRIPCOM_MS_GRAPH_ECON_NUM];
static  U2                                      u2_sp_tripcom_graph_date_val[TRIPCOM_MS_GRAPH_DATE_NUM];
static  U1                                      u1_sp_tripcom_ms_rimsts[TRIPCOM_MS_NUM_ID];
static  U1                                      u1_sp_tripcom_ms_nvmsts[TRIPCOM_MS_NUM_ID];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_TripcomMsNvmWrite(U1 u1_a_ID);
static U1       u1_s_TripcomMsNvmJdgSts(U1 u1_a_ID);

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

                if (stp_t_MEM->u2_memoryid == (U2)NVMCID_OTR_GRPH_TAEE_ECON) {
                    u1_t_memsts = u1_g_Nvmc_ReadOthrwithSts(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_ECON_BYTESIZE, (U1*)&u4_sp_tripcom_graph_econ_val[0]);
                    if (u1_t_memsts != (U1)NVMC_STATUS_KIND_OK) {
                        vd_g_MemfillU4(&u4_sp_tripcom_graph_econ_val[0], (U4)U4_MAX, (U4)TRIPCOM_MS_GRAPH_ECON_NUM);
                    }
                }
                else if (stp_t_MEM->u2_memoryid == (U2)NVMCID_OTR_GRPH_TAEE_DATE) {
                    u1_t_memsts = u1_g_Nvmc_ReadOthrwithSts(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_DATE_BYTESIZE, (U1*)&u2_sp_tripcom_graph_date_val[0]);
                    if (u1_t_memsts != (U1)NVMC_STATUS_KIND_OK) {
                        vd_g_MemfillU2(&u2_sp_tripcom_graph_date_val[0], (U2)U2_MAX, (U4)TRIPCOM_MS_GRAPH_DATE_NUM);
                    }
                }
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
    vd_g_TripcomMsClrRimRslt();
    vd_g_TripcomMsClrNvmRslt();
    vd_g_AvgGrphUpdtOneEconRslt((U1)AVGGRPH_CNTT_1MEE);
    vd_g_AvgGrphUpdtTaEconRslt((U1)AVGGRPH_CNTT_TAEE);
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

    u1_t_igsts   = u1_g_TripcomMsIgnOn();
    u1_t_esi_chk = u1_g_TripcomMsEsichk();

    if ((u1_t_esi_chk           == (U1)0U   ) &&
        (u1_t_igsts             == (U1)FALSE) &&
        (u1_s_tripcom_ms_igsts  == (U1)TRUE )) {

        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
            stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u4_t_loop];

            if ((stp_t_MEM->u1_devtype < (U1)TRIPCOM_MS_NUM_DEV) &&
                (stp_t_MEM->u2_memoryid != (U2)U2_MAX)) {

                if (fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype] != vdp_PTR_NA) {

                    fp_gp_TRIPCOM_MS_WRIF[stp_t_MEM->u1_devtype](stp_t_MEM->u2_memoryid, u4_sp_tripcom_ms_value[u4_t_loop]);
                }
                else if (stp_t_MEM->u2_memoryid == (U2)NVMCID_OTR_GRPH_TAEE_ECON) {

                    vd_g_Nvmc_WriteOthr(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_ECON_BYTESIZE, (U1*)&u4_sp_tripcom_graph_econ_val[0]);
                }
                else if (stp_t_MEM->u2_memoryid == (U2)NVMCID_OTR_GRPH_TAEE_DATE) {

                    vd_g_Nvmc_WriteOthr(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_DATE_BYTESIZE, (U1*)&u2_sp_tripcom_graph_date_val[0]);
                }
                else {
                    /* do nothing */
                }
            }
        }
    }
    u1_s_tripcom_ms_igsts = u1_t_igsts;

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u4_t_loop];
        if ((stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM) ||
            (stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM_O)) {

            if (u1_sp_tripcom_ms_nvmsts[u4_t_loop] == (U1)TRIPCOM_MS_NVMSTS_REQ) {
                vd_s_TripcomMsNvmWrite((U1)u4_t_loop);
                u1_sp_tripcom_ms_nvmsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_WAIT;
            }
            else if (u1_sp_tripcom_ms_nvmsts[u4_t_loop] == (U1)TRIPCOM_MS_NVMSTS_WAIT) {
                u1_sp_tripcom_ms_nvmsts[u4_t_loop] = u1_s_TripcomMsNvmJdgSts((U1)u4_t_loop);

                if ((u1_sp_tripcom_ms_nvmsts[u4_t_loop] != (U1)TRIPCOM_MS_NVMSTS_WAIT          ) &&
                    ((u4_t_loop                         == (U4)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON)  ||
                     (u4_t_loop                         == (U4)TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE))) {

                    vd_g_AvgGrphUpdtTaEconRslt((U1)AVGGRPH_CNTT_TAEE);
                }
            }
            else {
                /* do nothing */
            }
        }
    }
}

/*===================================================================================================================================*/
/* static void     vd_s_TripcomMsNvmWrite(U1 u1_a_ID)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_TripcomMsNvmWrite(U1 u1_a_ID)
{
    const ST_TRIPCOM_MS_MEM *                   stp_t_MEM;

    if(u1_a_ID < (U1)TRIPCOM_MS_NUM_ID) {
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u1_a_ID];
        if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
            vd_g_Nvmc_WriteOthr(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_ECON_BYTESIZE, (U1*)&u4_sp_tripcom_graph_econ_val[0]);
        }
        else if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE) {
            vd_g_Nvmc_WriteOthr(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_DATE_BYTESIZE, (U1*)&u2_sp_tripcom_graph_date_val[0]);
        }
        else {
            if ((stp_t_MEM->u2_memoryid                    != (U2)U2_MAX) &&
                (fp_gp_TRIPCOM_MS_WRIF[TRIPCOM_MS_DEV_NVM] != vdp_PTR_NA)) {
                fp_gp_TRIPCOM_MS_WRIF[TRIPCOM_MS_DEV_NVM](stp_t_MEM->u2_memoryid, u4_sp_tripcom_ms_value[u1_a_ID]);
            }
        }
    }
}

/*===================================================================================================================================*/
/* static U1       u1_s_TripcomMsNvmJdgSts(U1 u1_a_ID)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_TripcomMsNvmJdgSts(U1 u1_a_ID)
{
    const ST_TRIPCOM_MS_MEM *                   stp_t_MEM;
    U4                                          u4_t_value;
    U4                                          u4_t_graph_econ_val[TRIPCOM_MS_GRAPH_ECON_NUM];
    U2                                          u2_t_graph_date_val[TRIPCOM_MS_GRAPH_DATE_NUM];
    U1                                          u1_t_sts;
    U1                                          u1_t_rslt;

    u1_t_sts = (U1)NVMC_STATUS_NG;
    if (u1_a_ID < (U1)TRIPCOM_MS_NUM_ID) {
        stp_t_MEM = &st_gp_TRIPCOM_MS_MEM_CFG[u1_a_ID];
        if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
            u1_t_sts = u1_g_Nvmc_ReadOthrwithSts(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_ECON_BYTESIZE, (U1*)&u4_t_graph_econ_val[0]);
        }
        else if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE) {
            u1_t_sts = u1_g_Nvmc_ReadOthrwithSts(stp_t_MEM->u2_memoryid, (U2)TRIPCOM_MS_GRAPH_DATE_BYTESIZE, (U1*)&u2_t_graph_date_val[0]);
        }
        else {
            if (stp_t_MEM->u2_memoryid != (U2)U2_MAX) {
                u1_t_sts = u1_g_Nvmc_ReadU4withSts(stp_t_MEM->u2_memoryid, &u4_t_value);
            }
        }
    }

    if (u1_t_sts == (U1)NVMC_STATUS_WRITING) {
        u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_WAIT;
    }
    else if ((u1_t_sts >= (U1)NVMC_STATUS_KIND_NG) ||
             (u1_t_sts == (U1)NVMC_STATUS_ERRCOMP) ||
             (u1_t_sts == (U1)NVMC_STATUS_CACHE_NG)) {
        u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_FAIL;
    }
    else {
        u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_SUC;
    }
    return(u1_t_rslt);
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
/* void           vd_g_TripcomMsGetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripcomMsGetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE)
{
    U4          u4_t_loop;

    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++) {
            u4_ap_econ[u4_t_loop] = u4_sp_tripcom_graph_econ_val[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsSetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsSetGrphEconVal(const U1 u1_a_ID, U4* u4_ap_econ, const U1 u1_a_SIZE)
{
    U4          u4_t_loop;

    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++) {
            u4_sp_tripcom_graph_econ_val[u4_t_loop] = u4_ap_econ[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/* void           vd_g_TripcomMsGetGrphMaxVal(const U1 u1_a_ID, U4* u4_ap_max)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripcomMsGetGrphMaxVal(const U1 u1_a_ID, U4* u4_ap_max)
{
    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
        *u4_ap_max = u4_sp_tripcom_graph_econ_val[TRIPCOM_MS_GRAPH_ECON_MAX];
    }
}

/*===================================================================================================================================*/
/* void           vd_g_TripcomMsSetGrphMaxVal(const U1 u1_a_ID, const U4 u4_a_MAX)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripcomMsSetGrphMaxVal(const U1 u1_a_ID, const U4 u4_a_MAX)
{
    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_ECON) {
        u4_sp_tripcom_graph_econ_val[TRIPCOM_MS_GRAPH_ECON_MAX] = u4_a_MAX;
    }
}

/*===================================================================================================================================*/
/* void           vd_g_TripcomMsGetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripcomMsGetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE)
{
    U4          u4_t_loop;

    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE) {
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++) {
            u2_ap_date[u4_t_loop] = u2_sp_tripcom_graph_date_val[u4_t_loop];
        }
    }
}

/*===================================================================================================================================*/
/* void           vd_g_TripcomMsSetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void              vd_g_TripcomMsSetGrphDateVal(const U1 u1_a_ID, U2* u2_ap_date, const U1 u1_a_SIZE)
{
    U4          u4_t_loop;

    if (u1_a_ID == (U1)TRIPCOM_MS_ID_AVGGRPH_TAEE_DATE) {
        for (u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_a_SIZE; u4_t_loop++) {
            u2_sp_tripcom_graph_date_val[u4_t_loop] = u2_ap_date[u4_t_loop];
        }
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
        else if ((stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM  ) ||
                 (stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM_O)) { /* Non Volatile Memory */
            u1_sp_tripcom_ms_nvmsts[u1_a_ID] = (U1)TRIPCOM_MS_NVMSTS_REQ;
        }
        else{                                                           /* Volatile Memory */
            /* nothing */
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsClrRimRslt(void)                                                                                    */
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
}

/*===================================================================================================================================*/
/* void            vd_g_TripcomMsClrNvmRslt(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_TripcomMsClrNvmRslt(void)
{
    U4                          u4_t_loop;
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)TRIPCOM_MS_NUM_ID; u4_t_loop++) {
        u1_sp_tripcom_ms_nvmsts[u4_t_loop] = (U1)TRIPCOM_MS_NVMSTS_NON;
    }
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
        else if((stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM  ) ||  /* Non Volatile Memory */
                (stp_t_MEM->u1_devtype == (U1)TRIPCOM_MS_DEV_NVM_O)) {
            u1_t_rslt = u1_sp_tripcom_ms_nvmsts[u1_a_ID];
        }
        else{ /* if(stp_t_MEM->u1_devtype >= (U1)TRIPCOM_MS_NUM_DEV) */  /* Volatile Memory */
            u1_t_rslt = (U1)TRIPCOM_MS_NVMSTS_SUC;
        }
    }
    return(u1_t_rslt);
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
/*  2.2.0    02/19/2026  PG       Change for BEV M_DM (change to nvm access from special app access)                                 */
/*                                                                                                                                   */
/*  * HY   = Hidefumi Yoshida, Denso                                                                                                 */
/*  * YA   = Yuhei Aoyama, DensoTechno                                                                                               */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * YI   = Yoshiki Iwata, NTT Data MSE                                                                                             */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                          */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
