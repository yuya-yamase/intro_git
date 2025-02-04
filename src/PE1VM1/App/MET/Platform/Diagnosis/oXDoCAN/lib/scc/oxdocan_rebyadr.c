/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  SID 0x23 Read by Address                                                                                                         */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_REBYADR_C_MAJOR                  (1U)
#define OXDOCAN_REBYADR_C_MINOR                  (0U)
#define OXDOCAN_REBYADR_C_PATCH                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_rebyadr_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDOCAN_REBYADR_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "oxdocan_rebyadr.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((OXDOCAN_REBYADR_C_MAJOR != OXDOCAN_REBYADR_CFG_H_MAJOR) || \
     (OXDOCAN_REBYADR_C_MINOR != OXDOCAN_REBYADR_CFG_H_MINOR) || \
     (OXDOCAN_REBYADR_C_PATCH != OXDOCAN_REBYADR_CFG_H_PATCH))
#error "oxdocan_rebyadr.c and oxdocan_rebyadr_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                    u4_s_oxdc_rebyadr_src_begin;
static U4                    u4_s_oxdc_rebyadr_src_nbyte;
static U4                    u4_s_oxdc_rebyadr_src_rbcnt;
static U1                    u1_s_oxdc_rebyadr_mid;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXdcRebyAdrReqchk(const ST_OXDC_REQ * st_ap_REQ, const ST_OXDC_ANS * st_ap_ANS);

static void    vd_s_oXdcRebyAdrProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRebyAdrInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRebyAdrInit(void)
{
    u4_s_oxdc_rebyadr_src_begin = (U4)U4_MAX;
    u4_s_oxdc_rebyadr_src_nbyte = (U4)0U;
    u4_s_oxdc_rebyadr_src_rbcnt = (U4)U4_MAX;
    u1_s_oxdc_rebyadr_mid       = (U1)U1_MAX;
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRebyAdrMainTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRebyAdrMainTask(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    if(st_ap_REQ->u1_sid == (U1)OXDC_SID_23){

        if(st_ap_REQ->u2_tim_elpsd == (U2)0U){
            vd_s_oXdcRebyAdrReqchk(st_ap_REQ, st_ap_ans);
        }

        if(u1_s_oxdc_rebyadr_mid < u1_g_OXDC_RBA_MEM_NUM_CFG){
            vd_s_oXdcRebyAdrProcRun(st_ap_REQ, st_ap_ans);
        }
        else if(st_ap_REQ->u2_tim_elpsd > (U2)0U){
            vd_g_oXDoCANAnsTx((U1)OXDC_SAL_PROC_NR_22, vdp_PTR_NA);
        }
        else{
            /* Do Nothing */
        }
    }
    else{
        vd_g_oXDoCANRebyAdrInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRebyAdrStartRamSet(const U1 u1_a_MEM, const U4 u4_a_BEGIN, const U4 u4_a_NBYTE)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRebyAdrStartRamSet(const U1 u1_a_MEM, const U4 u4_a_BEGIN, const U4 u4_a_NBYTE)
{
    u1_s_oxdc_rebyadr_mid       = u1_a_MEM;
    u4_s_oxdc_rebyadr_src_begin = u4_a_BEGIN;
    u4_s_oxdc_rebyadr_src_nbyte = u4_a_NBYTE;
    u4_s_oxdc_rebyadr_src_rbcnt = (U4)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRebyAdrReqchk(const ST_OXDC_REQ * st_ap_REQ, const ST_OXDC_ANS * st_ap_ANS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcRebyAdrReqchk(const ST_OXDC_REQ * st_ap_REQ, const ST_OXDC_ANS * st_ap_ANS)
{
    U1                       u1_t_proc;

    u1_t_proc = u1_g_oXDoCANCfgRbaReqchk(st_ap_REQ, st_ap_ANS);

    if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        vd_g_oXDoCANRebyAdrInit();
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcRebyAdrProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
static void    vd_s_oXdcRebyAdrProcRun(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans)
{
    const U1 *               u1_tp_SRC;

    U4                       u4_t_res_nbyte;
    U4                       u4_t_rb_max;
    U4                       u4_t_lpcnt;
    U4                       u4_t_lpend;

    U1                       u1_t_proc;

    u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;

    if((st_ap_REQ->u1p_RX   != vdp_PTR_NA                ) &&
       (st_ap_REQ->u4_nbyte == (U4)OXDC_REBYADR_REQ_NBYTE) &&
       (st_ap_ans->u1p_tx   != vdp_PTR_NA                ) &&
       (st_ap_ans->u4_nbyte >= (U4)u4_s_oxdc_rebyadr_src_nbyte   )){

        if(u4_s_oxdc_rebyadr_src_nbyte > u4_s_oxdc_rebyadr_src_rbcnt){
            u4_t_res_nbyte = u4_s_oxdc_rebyadr_src_nbyte - u4_s_oxdc_rebyadr_src_rbcnt;
        }
        else{
            u4_t_res_nbyte = (U4)0U;
        }

        u4_t_rb_max = (U4)st_gp_OXDC_RBA_MEM_CFG[u1_s_oxdc_rebyadr_mid].u2_rb_max;
        if((u4_t_res_nbyte == (U4)0U) ||
           (u4_t_rb_max    == (U4)0U)){
            u4_t_lpcnt = (U4)U4_MAX;
            u4_t_lpend = (U4)0U;
        }
        else if(u4_t_res_nbyte <= u4_t_rb_max){
            u4_t_lpcnt = u4_s_oxdc_rebyadr_src_rbcnt;
            u4_t_lpend = u4_s_oxdc_rebyadr_src_nbyte;
            u1_t_proc  = (U1)OXDC_SAL_PROC_FIN;
        }
        else{
            u4_t_lpcnt = u4_s_oxdc_rebyadr_src_rbcnt;
            u4_t_lpend = u4_s_oxdc_rebyadr_src_rbcnt + u4_t_rb_max;
            u1_t_proc  = (U1)OXDC_SAL_PROC_RUN;
        }

        /* ---------------------------------------------------------------------------- */
        /* WARNING :                                                                    */
        /* ---------------------------------------------------------------------------- */
        /* The data consistency is intentionally ignored.                               */
        /* If data consistency is required, USE SID 0x22 AND ASIGN DATA IDENTIFIER.     */
        /* ---------------------------------------------------------------------------- */
        u1_tp_SRC = (const U1 *)u4_s_oxdc_rebyadr_src_begin;
        while(u4_t_lpcnt < u4_t_lpend){
            st_ap_ans->u1p_tx[u4_t_lpcnt] = u1_tp_SRC[u4_t_lpcnt];
            u4_t_lpcnt++;
        }

        u4_s_oxdc_rebyadr_src_rbcnt = u4_t_lpend;
    }

    if(u1_t_proc == (U1)OXDC_SAL_PROC_FIN){
        st_ap_ans->u4_nbyte = u4_s_oxdc_rebyadr_src_nbyte;
        vd_g_oXDoCANRebyAdrInit();
        vd_g_oXDoCANAnsTx(u1_t_proc, st_ap_ans);
    }
    else if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
        vd_g_oXDoCANRebyAdrInit();
        vd_g_oXDoCANAnsTx(u1_t_proc, vdp_PTR_NA);
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tydocan_rebyadr ->           */
/*                                oxdocan_rebyadr.                                                                                   */
/*  1.0.1     7/ 7/2023  ST       Update for OEM standardization.                                                                    */
/*  1.0.2     8/21/2023  TI       Update for OEM standardization.                                                                    */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Takehisa Inoue, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
