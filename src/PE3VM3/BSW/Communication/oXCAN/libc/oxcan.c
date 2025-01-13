/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_C_MAJOR                            (1U)
#define OXCAN_C_MINOR                            (4U)
#define OXCAN_C_PATCH                            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_cfg_private.h"

/* #include "oxcan.h" */          /* BSW_BSWM_CS_CFG_FUNC_CS is defined in BswM_CS_Cfg.h          */
                                  /* BSW_BSWM_CS_CFG_FUNC_SECOC is defined in BswM_CS_Cfg.h       */
                                  /* BswM_CS_Cfg.h is included in CS_Can_Cfg.h                    */
                                  /* CS_Can_Cfg.h is included in oxcan.h                          */

#include "bsw_com_config.h"       /* BSW_COM_MSG_NUM is defined in bsw_com_config.h               */
                                  /* BSW_COM_TX_MSG_NUM is defined in bsw_com_config.h            */

#include "bsw_com_st.h"           /* bsw_com_u4SysStatTbl[][] is defined in bsw_com_st.h          */

#include "bsw_cannm_ch_config.h"  /* BSW_CANNM_NM_TYPE_USE(x) is defined in bsw_cannm_ch_config.h */
#include "bsw_bswm_cs_status.h"   /* bsw_bswm_cs_st_u2CSStatus is defined in bsw_bswm_cs_status.h */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if OXCAN_AUB_CSM_SUP
#include "Csm.h"
#include "CryIf.h"
#include "Crypto_83_icus.h"
#include "SchM_Csm.h"
#include "SchM_Crypto_83_icus.h"
#if OXCAN_AUB_CRPT_SW_SUP
#include "Crypto_83_sw.h"
#include "SchM_Crypto_83_sw.h"
#endif /* OXCAN_AUB_CRPT_SW_SUP */
#endif /* OXCAN_AUB_CSM_SUP */
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
#include "SecOC.h"
#include "IdsM.h"
#include "SchM_IdsM.h"
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && .. */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_aubif.h"
/*#include "ox25epf_can.h"*/

#include "int_drv.h"

#if (OXCAN_AUB_E2E_SUP == 1U)
#include "E2E.h"
#endif /* #if (OXCAN_AUB_E2E_SUP == 1U) */

#if (OXCAN_IC_TJA1145_USE == 1U)
#include "Cdd_Canic.h"
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_C_MAJOR != OXCAN_CFG_H_MAJOR) || \
     (OXCAN_C_MINOR != OXCAN_CFG_H_MINOR) || \
     (OXCAN_C_PATCH != OXCAN_CFG_H_PATCH))
#error "oxcan.c and oxcan_cfg_private.h : source and header files are inconsistent!"
#endif

#if 0
#if (OXCAN_C_MAJOR != OX25EPF_CAN_VER_MAJOR)
#error "oxcan.c and ox25epf_can.h : source and header files are inconsistent!"
#endif
#endif
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_BACK_EN                     (0x5aU)
#define OXCAN_BACK_DI                     (0xa5U)

#define OXCAN_BACK_NWORD                  ((BSWM_CAN_BACKUPDATASIZE + 3U) >> 2U)
                                                                            /* BSWM_CAN_BACKUPDATASIZE is defined in BswM_Can.h  */
                                                                            /* BswM_Can.h is included in CS_Can.h                */

#if (OXCAN_NM_TX_STOP_EN == 1U)
#define OXCAN_NMMSG_RESUME                (0x00U)
#define OXCAN_NMMSG_STOP                  (0x01U)
#endif /* #if (OXCAN_NM_TX_STOP_EN == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_AUB_E2E_SUP == 1U)
#define OXCAN_E2E_OFFSET                         (0U)
#define OXCAN_E2E_MAXDELTACNT                    (3U)
#endif /* #if (OXCAN_AUB_E2E_SUP == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_BACK_NWORD > 0U)
static U4               u4_sp_oxcan_back[OXCAN_BACK_NWORD]  __attribute__((section(".bss_BACK_BSW")));
static volatile U1      u1_s_oxcan_br_chk                          __attribute__((section(".bss_BACK_BSW")));
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

static U4               u4_s_oxcan_sysbit;

#if OXCAN_AUB_CSM_SUP
static U1               u1_s_oxcan_sht_ma;
#endif /* #if OXCAN_AUB_CSM_SUP */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U))
static E2E_P05CheckStateType        st_s_oxcan_aubif_e2e_chkstat[OXCAN_E2E_NUM_CHECK_MSG];
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U)) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U))
static E2E_P05ProtectStateType      st_s_oxcan_aubif_e2e_protstat[OXCAN_E2E_NUM_PROTECT_MSG];
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXCANInit(const U1 u1_a_WKU_INIT);
static U2      u2_s_oXCANCanFatal(void);

#if OXCAN_AUB_CSM_SUP
static void    vd_s_oXCANSecurityInit(void);
static U2      u2_s_oXCANSecurityFatal(void);
static void    vd_s_oXCANSecurityDeInit(void);
#endif /* #if OXCAN_AUB_CSM_SUP */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXCANRstInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANRstInit(void)
{
    vd_s_oXCANInit((U1)FALSE);   /* u1_a_WKU_INIT = FALSE */
    vd_g_oXCANCfgRstInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANWkupInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANWkupInit(void)
{
    vd_s_oXCANInit((U1)TRUE);    /* u1_a_WKU_INIT = TRUE  */
    vd_g_oXCANCfgWkupInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANOpemdEvhk(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANOpemdEvhk(void)
{
/*    U4                  u4_t_cpu_md;*/

    U4                  u4_t_lpcnt;
    U4                  u4_t_sysbit_next;
    U4                  u4_t_sysbit_prev;
    U4                  u4_t_prev;
    U4                  u4_t_next;

/*    u4_t_cpu_md = u4_g_CPUM_PRIV();  *//* CPU mode = privilege   */

    u4_t_sysbit_prev = u4_s_oxcan_sysbit;

    u4_t_sysbit_next = u4_g_oXCANOpemdSyschk((U1)FALSE); /* Timer Increment Disabled */
    BswM_CS_SetSystemStatus(u4_g_OXCAN_SYS_POWER, u4_s_oxcan_sysbit);

    /* ----------------------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                             */
    /* ----------------------------------------------------------------------------------------------------- */
    /* u1_g_oXCANMsgOnline is called from BswM_CS_MainFunctionMiddle or BswM_CS_MainFunctionHigh depending   */
    /* on following configuration :                                                                          */
    /*                                                                                                       */
    /* BswM_CS_Cfg.h                                                                                         */
    /* #define BSW_BSWM_CS_CFG_MSGDELIVER                                                                    */
    /*                                                                                                       */
    /* If BSW_BSWM_CS_CFG_MSGDELIVER is configured with BSW_BSWM_CS_MSGDELIVER_HIGH, u1_g_oXCANMsgOnline     */
    /* could be called from interrupts service routine. Therefore, u4_s_oxcan_sysbit shall be updated        */
    /* by latest operational mode before executing Rx messages initialization.                               */
    /* ----------------------------------------------------------------------------------------------------- */
    u4_s_oxcan_sysbit = u4_t_sysbit_next;

    for(u4_t_lpcnt = (U4)BSW_COM_TX_MSG_NUM; u4_t_lpcnt < (U4)BSW_COM_MSG_NUM; u4_t_lpcnt++){

        u4_t_prev = u4_t_sysbit_prev & bsw_com_u4SysStatTbl[u4_t_lpcnt][0];
        u4_t_next = u4_t_sysbit_next & bsw_com_u4SysStatTbl[u4_t_lpcnt][0];
        if(((u4_t_prev != (U4)0U) && (u4_t_next == (U4)0U)) ||
           ((u4_t_prev == (U4)0U) && (u4_t_next != (U4)0U))){

            Com_InitIPDUStatus((PduIdType)u4_t_lpcnt, ((U1)COM_NO_RX | (U1)COM_TIMEOUT));
        }
    }

    vd_g_oXCANRxOpemdEvthk(u4_t_sysbit_next);

    vd_g_oXCANCfgOpemdEvthk(u4_t_sysbit_prev, u4_t_sysbit_next);

/*    vd_g_CPUM_RSTR(u4_t_cpu_md);   */  /* CPU mode = u4_t_cpu_md */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANMainPreTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANMainPreTask(void)
{
/*    U4                  u4_t_cpu_md;*/

/*    u4_t_cpu_md = u4_g_CPUM_PRIV();  *//* CPU mode = privilege   */

    u4_s_oxcan_sysbit = u4_g_oXCANOpemdSyschk((U1)TRUE);  /* Timer Increment Enabled */

    BswM_CS_SetSystemStatus(u4_g_OXCAN_SYS_POWER, u4_s_oxcan_sysbit);

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    vd_g_oXCANNmwkMainTask();
#endif

    BswM_CS_MainFunctionMiddle();

#ifdef CXPICDD_H
    CxpiCdd_MainFunction_In();
#endif /* #ifdef CXPICDD_H */

    vd_g_oXCANRxMainTask(u4_s_oxcan_sysbit);
    vd_g_oXCANCfgPreTask(u4_s_oxcan_sysbit);

/*    vd_g_CPUM_RSTR(u4_t_cpu_md);    */ /* CPU mode = u4_t_cpu_md */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANMainPostTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANMainPostTask(void)
{
/*    U4                  u4_t_cpu_md;*/
    U2                  u2_t_fatal;
#if (OXCAN_RX_STOP_EN == 1U)
    U4                  u4_t_ch;
#endif /* #if (OXCAN_RX_STOP_EN == 1U) */

/*    u4_t_cpu_md = u4_g_CPUM_PRIV();  *//* CPU mode = privilege   */

    vd_g_oXCANOpemdEvTx();

#if (OXCAN_RX_STOP_EN == 1U)
    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_OXCAN_TXRX_NUM_CH; u4_t_ch++){
        if(u1_g_oXCANPdumsgStat((U1)u4_t_ch) == (U1)OXCAN_PDUMSG_STOP){
            vd_g_oXCANRxTimerInit((U1)u4_t_ch);
        }
    }
#endif /* #if (OXCAN_RX_STOP_EN == 1U) */

#ifdef CXPICDD_H
    vd_g_TyCANCxptxMainTask(u4_s_oxcan_sysbit);
#endif /* #ifdef CXPICDD_H */

#if (OXCAN_FATAL_AUB_GIC != TRUE)
#error "oxcan.c : OXCAN_FATAL_AUB_GIC be equal to TRUE."
#endif /* #if (OXCAN_FATAL_AUB_GIC != TRUE) */
    u2_t_fatal  = (U2)u1_g_oXCANAubIfGicUnk();
    u2_t_fatal |= u2_s_oXCANCanFatal();

#if OXCAN_AUB_CSM_SUP

    u2_t_fatal |= u2_s_oXCANSecurityFatal();
#endif /* #if OXCAN_AUB_CSM_SUP */

    vd_g_oXCANCfgPostTask(u4_s_oxcan_sysbit, u2_t_fatal);

/*    vd_g_CPUM_RSTR(u4_t_cpu_md);    */ /* CPU mode = u4_t_cpu_md */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANShutdown(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANShutdown(void)
{
#if (OXCAN_BACK_NWORD > 0U)
    U1                  u1_t_br_chk;
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

    vd_g_oXCANCfgShutdown();

#ifdef CXPICDD_H
    vd_g_oXCANCxptxDeInit();
/* ------------------------------------------------------------------------------------------------- */
/* NOTE :                                                                                            */
/* This process is unnecessary because BSW software does not cancel sleep. Also, it is unnecessary   */
/* because the required processing is not executed in CxpiCdd_SsCheckSlpCancel().                    */
/* ------------------------------------------------------------------------------------------------- */
/*#if (CXPICDD_SLP_CANCEL_USE == CXPICDD_ON)*/
    /* Do not check the return value, because it doesn't sleep cancel. */
    /*(void)CxpiCdd_SsCheckSlpCancel();*/
/*#endif*/
#endif /* #ifdef CXPICDD_H */

#if (OXCAN_IC_TJA1145_USE == 1U)
    Cdd_Canic_Shutdown();
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */

    BswM_CS_Sleep();

#if (OXCAN_BACK_NWORD > 0U)
    u1_t_br_chk = u1_s_oxcan_br_chk;
    if(u1_t_br_chk != (U1)OXCAN_BACK_DI){

        u1_s_oxcan_br_chk = (U1)0U;

        BswM_Can_GetBackupData((U1 *)&u4_sp_oxcan_back[0]);

        u1_s_oxcan_br_chk = (U1)OXCAN_BACK_EN;
    }
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
     (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))

    SecOC_DeInit();
#endif

}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANEcuShtdwnOk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Can Sleep Check Result                                                                                           */
/*===================================================================================================================================*/
U1      u1_g_oXCANEcuShtdwnOk(void)
{
    U4                  u4_t_cpu_md;
    U1                  u1_t_sht_ok;
    U1                  u1_t_awk;

    u4_t_cpu_md = u4_g_CPUM_PRIV();  /* CPU mode = privilege   */

    u1_t_awk = BswM_CS_CheckAwake();
    if(u1_t_awk == (U1)BSWM_CS_AWAKE_EXIST){

        u1_t_sht_ok = (U1)FALSE;
    }
    else{

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
        u1_t_sht_ok = u1_g_oXCANNmwkEcuShtdwnOk();
#else
        u1_t_sht_ok = (U1)TRUE;
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */
    }

#if OXCAN_AUB_CSM_SUP

    u1_t_sht_ok &= u1_s_oxcan_sht_ma;
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \ ... */

    vd_g_CPUM_RSTR(u4_t_cpu_md);     /* CPU mode = u4_t_cpu_md */

    return(u1_t_sht_ok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANMsgOnline(const U2 u2_a_MSG)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANMsgOnline(const U2 u2_a_MSG)
{
    U1                  u1_t_online;
    U4                  u4_t_sysbit;

    u1_t_online = (U1)FALSE;
    if(u2_a_MSG < (U2)BSW_COM_MSG_NUM){
#if (OXCAN_RX_STOP_EN == 1U)
        if(u1_g_oXCANPdumsgStat(bsw_com_stMsgInfoTbl[u2_a_MSG].u1Network) != (U1)OXCAN_PDUMSG_STOP){
            u4_t_sysbit = u4_s_oxcan_sysbit & bsw_com_u4SysStatTbl[u2_a_MSG][0];
            if(u4_t_sysbit != (U4)0U){
                u1_t_online = (U1)TRUE;
            }
        }
#else
        u4_t_sysbit = u4_s_oxcan_sysbit & bsw_com_u4SysStatTbl[u2_a_MSG][0];
        if(u4_t_sysbit != (U4)0U){
            u1_t_online = (U1)TRUE;
        }
#endif /* #if (OXCAN_RX_STOP_EN == 1U) */
    }

    return (u1_t_online);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANPdumsgStop(const U1 u1_a_CH, const U1 u1_a_ID)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANPdumsgStop(const U1 u1_a_CH, const U1 u1_a_ID)
{
#if 0
    if((u1_a_CH < u1_g_OXCAN_TXRX_NUM_CH) && (u1_a_ID < u1_g_OXCAN_TXRX_NUM_ID)){
        vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[u1_a_CH][u1_a_ID], (U1)OXCAN_PDUMSG_STOP);
        vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[u1_a_CH], (U1)OXCAN_PDUMSG_STOP);

        (void)BswM_CS_StopTxPdu((NetworkHandleType)u1_a_CH);
    }
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANPdumsgResume(const U1 u1_a_CH, const U1 u1_a_ID)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANPdumsgResume(const U1 u1_a_CH, const U1 u1_a_ID)
{
#if 0
    U4                  u4_t_lpcnt;
    U1                  u1_t_rim_ret;
    U1                  u1_t_id_req;
    U1                  u1_t_ch_req;

    if((u1_a_CH < u1_g_OXCAN_TXRX_NUM_CH) && (u1_a_ID < u1_g_OXCAN_TXRX_NUM_ID)){
        u1_t_ch_req = (U1)OXCAN_PDUMSG_RESUME;
        vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[u1_a_CH][u1_a_ID], (U1)OXCAN_PDUMSG_RESUME);
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_TXRX_NUM_ID; u4_t_lpcnt++){
            u1_t_rim_ret = u1_g_Rim_ReadU1withStatus(u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[u1_a_CH][u4_t_lpcnt], &u1_t_id_req);
            if((u1_t_rim_ret != (U1)RIM_RESULT_OK) && (u1_t_rim_ret != (U1)RIM_RESULT_OK_REPAIRED)){
                u1_t_id_req = (U1)OXCAN_PDUMSG_RESUME;
                vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[u1_a_CH][u4_t_lpcnt], u1_t_id_req);
            }
            u1_t_ch_req |= u1_t_id_req;
        }

        if(u1_t_ch_req == (U1)OXCAN_PDUMSG_RESUME){
            vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[u1_a_CH], (U1)OXCAN_PDUMSG_RESUME);

            (void)BswM_CS_ResumeTxPdu((NetworkHandleType)u1_a_CH);
        }
    }
#endif
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANPdumsgStat(const U1 u1_a_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANPdumsgStat(const U1 u1_a_CH)
{
#if 0
    U1                  u1_t_rim_ret;
    U1                  u1_t_pdusts;

    u1_t_pdusts = (U1)OXCAN_PDUMSG_RESUME;

    if(u1_a_CH < u1_g_OXCAN_TXRX_NUM_CH){
        u1_t_rim_ret = u1_g_Rim_ReadU1withStatus(u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[u1_a_CH], &u1_t_pdusts);
        if((u1_t_rim_ret != (U1)RIM_RESULT_OK) && (u1_t_rim_ret != (U1)RIM_RESULT_OK_REPAIRED)){
            u1_t_pdusts = (U1)OXCAN_PDUMSG_RESUME;
            vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[u1_a_CH], u1_t_pdusts);
        }
    }

    return(u1_t_pdusts);
#else
    return((U1)OXCAN_PDUMSG_RESUME);
#endif
}

#if (OXCAN_NM_TX_STOP_EN == 1U)
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmmsgStop(const U1 u1_a_CH, const U1 u1_a_ID)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmmsgStop(const U1 u1_a_CH, const U1 u1_a_ID)
{
#if 0
    if((u1_a_CH < u1_g_OXCAN_TXRX_NUM_CH) && (u1_a_ID < u1_g_OXCAN_TXRX_NUM_ID)){
        vd_g_Rim_WriteU1(u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[u1_a_CH][u1_a_ID], (U1)OXCAN_NMMSG_STOP);
        (void)Nm_DisableCommunication((NetworkHandleType)u1_a_CH);
    }
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANNmmsgResume(const U1 u1_a_CH, const U1 u1_a_ID)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANNmmsgResume(const U1 u1_a_CH, const U1 u1_a_ID)
{
#if 0
    U4                  u4_t_lpcnt;
    U1                  u1_t_rim_ret;
    U1                  u1_t_id_req;
    U1                  u1_t_ch_req;

    if((u1_a_CH < u1_g_OXCAN_TXRX_NUM_CH) && (u1_a_ID < u1_g_OXCAN_TXRX_NUM_ID)){
        u1_t_ch_req = (U1)OXCAN_NMMSG_RESUME;
        vd_g_Rim_WriteU1(u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[u1_a_CH][u1_a_ID], (U1)OXCAN_NMMSG_RESUME);
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_TXRX_NUM_ID; u4_t_lpcnt++){
            u1_t_rim_ret = u1_g_Rim_ReadU1withStatus(u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[u1_a_CH][u4_t_lpcnt], &u1_t_id_req);
            if((u1_t_rim_ret != (U1)RIM_RESULT_OK) && (u1_t_rim_ret != (U1)RIM_RESULT_OK_REPAIRED)){
                u1_t_id_req = (U1)OXCAN_NMMSG_RESUME;
                vd_g_Rim_WriteU1(u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[u1_a_CH][u4_t_lpcnt], u1_t_id_req);
            }
            u1_t_ch_req |= u1_t_id_req;
        }
        if(u1_t_ch_req == (U1)OXCAN_NMMSG_RESUME){
            (void)Nm_EnableCommunication((NetworkHandleType)u1_a_CH);
        }
    }
#endif
}
#endif /* #if (OXCAN_NM_TX_STOP_EN == 1U) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U))
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANE2ECheckData(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXCANE2ECheckData(PduIdType PduId, BswConstR PduInfoType* PduInfoPtr)
{
    E2E_P05ConfigType   st_t_oxcan_aubif_e2e_data;
    U4                  u4_t_lpcnt;
    U2                  u2_t_length;
    U2                  u2_t_msg_num;
    U1                  u1_t_e2e;
    U1                  u1_t_permission;
    U1                  u1_t_ret_e2e;

    u1_t_permission = (U1)FALSE;
    u1_t_e2e = (U1)FALSE;
    u2_t_msg_num = (U2)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u4_g_OXCAN_E2E_NUM_CHECK_MSG; u4_t_lpcnt++){
        if(PduId == u2_gp_OXCAN_E2E_CHECK_MSG[u4_t_lpcnt]){
            u1_t_e2e = (U1)TRUE;
            u2_t_msg_num = (U2)u4_t_lpcnt;
            break;
        }
    }

    if(u1_t_e2e == (U1)TRUE){
        u2_t_length = PduInfoPtr->SduLength;
        st_t_oxcan_aubif_e2e_data.Offset          = (U2)OXCAN_E2E_OFFSET;
        st_t_oxcan_aubif_e2e_data.DataLength      = u2_t_length * (U2)8U;
        st_t_oxcan_aubif_e2e_data.DataID          = (U2)Com_GetFrameID(PduId);
        st_t_oxcan_aubif_e2e_data.MaxDeltaCounter = (U1)OXCAN_E2E_MAXDELTACNT;
        u1_t_ret_e2e = E2E_P05Check(&st_t_oxcan_aubif_e2e_data, &st_s_oxcan_aubif_e2e_chkstat[u2_t_msg_num], PduInfoPtr->SduDataPtr, u2_t_length);
        if(u1_t_ret_e2e == E2E_E_OK){
            if((st_s_oxcan_aubif_e2e_chkstat[u2_t_msg_num].Status == E2E_P05STATUS_OK) || (st_s_oxcan_aubif_e2e_chkstat[u2_t_msg_num].Status == E2E_P05STATUS_OKSOMELOST)){
                u1_t_permission = (U1)TRUE;
            }
        }
    } else {
        u1_t_permission = (U1)TRUE;
    }
    
    return (u1_t_permission);
}
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U)) */
#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U))
/*===================================================================================================================================*/
/*  void      vd_g_oXCANE2EProtectData(PduIdType PduId, PduInfoType* PduInfoPtr)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_oXCANE2EProtectData(PduIdType PduId, PduInfoType* PduInfoPtr)
{
    E2E_P05ConfigType   st_t_oxcan_aubif_e2e_data;
    U4                  u4_t_lpcnt;
    U2                  u2_t_length;
    U2                  u2_t_msg_num;
    U1                  u1_t_e2e;

    u1_t_e2e = (U1)FALSE;
    u2_t_msg_num = (U2)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u4_g_OXCAN_E2E_NUM_PROTECT_MSG; u4_t_lpcnt++){
        if(PduId == u2_gp_OXCAN_E2E_PROTECT_MSG[u4_t_lpcnt]){
            u1_t_e2e = (U1)TRUE;
            u2_t_msg_num = (U2)u4_t_lpcnt;
            break;
        }
    }
 
    if(u1_t_e2e == (U1)TRUE){
        u2_t_length = PduInfoPtr->SduLength;
        st_t_oxcan_aubif_e2e_data.Offset          = (U2)OXCAN_E2E_OFFSET;
        st_t_oxcan_aubif_e2e_data.DataLength      = u2_t_length * (U2)8U;
        st_t_oxcan_aubif_e2e_data.DataID          = (U2)Com_GetFrameID(PduId);
        st_t_oxcan_aubif_e2e_data.MaxDeltaCounter = (U1)OXCAN_E2E_MAXDELTACNT;
        (void)E2E_P05Protect(&st_t_oxcan_aubif_e2e_data, &st_s_oxcan_aubif_e2e_protstat[u2_t_msg_num], PduInfoPtr->SduDataPtr, u2_t_length);
    }

}
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U)) */

/*===================================================================================================================================*/
/*  static void    vd_s_oXCANInit(const U1 u1_a_WKU_INIT)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANInit(const U1 u1_a_WKU_INIT)
{
#if 0
    U4                  u4_t_ch;
    U4                  u4_t_id;
#endif
#if (OXCAN_AUB_E2E_SUP == 1U)
    U4                  u4_t_msg_cnt;
#endif /* #if (OXCAN_AUB_E2E_SUP == 1U) */
#if (OXCAN_BACK_NWORD > 0U)
    U4                  u4_t_lpcnt;
    U1                  u1_t_br_chk;
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

    u4_s_oxcan_sysbit = (U4)OXCAN_SYS_BAT;

    vd_g_oXCANAubIfInit();

#if OXCAN_AUB_CSM_SUP
    u1_s_oxcan_sht_ma = (U1)TRUE;
    vd_s_oXCANSecurityInit();
#endif /* #if OXCAN_AUB_CSM_SUP */
#if (OXCAN_IC_TJA1145_USE == 1U)
    Cdd_Canic_Init();
#endif /* #if (OXCAN_IC_TJA1145_USE == 1U) */
#if (OXCAN_BACK_NWORD > 0U)
    u1_t_br_chk = u1_s_oxcan_br_chk;
    if((u1_a_WKU_INIT == (U1)TRUE                ) &&
       (u1_t_br_chk   == (U1)OXCAN_BACK_EN)){

        BswM_Can_SetBackupData((U1 *)&u4_sp_oxcan_back[0]);
        (void)CanIf_CheckWakeup(u4_g_OXCAN_WKSRC_CHK);
        BswM_CS_Wakeup();

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)BSW_COM_MSG_NUM; u4_t_lpcnt++){
            (void)Com_InitIPDU((PduIdType)u4_t_lpcnt);
        }
    }
    else{

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_BACK_NWORD; u4_t_lpcnt++){
            u4_sp_oxcan_back[u4_t_lpcnt] = (U4)0U;
        }
        u1_s_oxcan_br_chk = (U1)0U;
        BswM_CS_Init();
    }
#else
    BswM_CS_Init();
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U))
    for(u4_t_msg_cnt = (U4)0U;u4_t_msg_cnt < (U4)OXCAN_E2E_NUM_CHECK_MSG;u4_t_msg_cnt++){
        (void)E2E_P05CheckInit(&st_s_oxcan_aubif_e2e_chkstat[u4_t_msg_cnt]);
    }
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_CHECK_MSG != 0U)) */

#if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U))
    for(u4_t_msg_cnt = (U4)0U;u4_t_msg_cnt < (U4)OXCAN_E2E_NUM_PROTECT_MSG;u4_t_msg_cnt++){
        (void)E2E_P05ProtectInit(&st_s_oxcan_aubif_e2e_protstat[u4_t_msg_cnt]);
    }
#endif /* #if ((OXCAN_AUB_E2E_SUP == 1U) && (OXCAN_E2E_NUM_PROTECT_MSG != 0U)) */

#ifdef CXPICDD_H
    vd_g_TyCANCxptxInit(u1_a_WKU_INIT);
#endif /* #ifdef CXPICDD_H */

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    vd_g_oXCANNmwkInit();
#endif

    vd_g_oXCANOpemdInit();
    vd_g_oXCANRxInit();
#if 0
    for(u4_t_ch = (U4)0U; u4_t_ch < (U4)u1_g_OXCAN_TXRX_NUM_CH; u4_t_ch++){
        vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_STAT_BY_CH_RIMID[u4_t_ch], (U1)OXCAN_PDUMSG_RESUME);
        for(u4_t_id = (U4)0U; u4_t_id < (U4)u1_g_OXCAN_TXRX_NUM_ID; u4_t_id++){
            vd_g_Rim_WriteU1(u2_gp_OXCAN_PDU_REQ_BY_ID_RIMID[u4_t_ch][u4_t_id], (U1)OXCAN_PDUMSG_RESUME);
#if (OXCAN_NM_TX_STOP_EN == 1U)
            vd_g_Rim_WriteU1(u2_gp_OXCAN_NM_REQ_BY_ID_RIMID[u4_t_ch][u4_t_id], (U1)OXCAN_NMMSG_RESUME);
#endif /* #if (OXCAN_NM_TX_STOP_EN == 1U) */
        }
    }
#endif
}
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANCanFatal(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_oXCANCanFatal(void)
{
    U4                  u4_t_lpcnt;
    U2                  u2_t_can;
    U2                  u2_t_chk;
    U2                  u2_t_chbit;
    U2                  u2_t_fatal;

    if(bsw_bswm_cs_st_u2CSStatus != BSW_BSWM_CS_u2PVTST_RUN){

        u2_t_fatal = (U2)OXCAN_FATAL_AUB_COM;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)BSW_COM_CFG_CHNUM; u4_t_lpcnt++){
            vd_g_oXCANUsrhkExirClrIRQst(u1_gp_OXCAN_CTRLR_BY_CH[u4_t_lpcnt]);
        }

#if (OXCAN_BACK_NWORD > 0U)
        u1_s_oxcan_br_chk = (U1)OXCAN_BACK_DI;
#endif /* #if (OXCAN_BACK_NWORD > 0U) */
    }
    else{

        u2_t_fatal = (U2)0U;
        u2_t_chbit = (U2)OXCAN_FATAL_AUB_CAN_0;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)BSW_COM_CFG_CHNUM; u4_t_lpcnt++){

            /* ----------------------------------------------------------------------------------------------------- */
            /* Attention :                                                                                           */
            /* ----------------------------------------------------------------------------------------------------- */
            /* The return of BswM_Can_GetChFailStatus is intentionally discarded because the API returns E_NOT_OK    */
            /* only if the 1st parameter "NetworkHandleType network" is greater than or equal to BSW_COM_CFG_CHNUM.  */
            /* ----------------------------------------------------------------------------------------------------- */
            (void)BswM_Can_GetChFailStatus((U1)u4_t_lpcnt, &u2_t_can);

            u2_t_chk = u2_t_can & ((U2)BSWM_CAN_CHFAILST_REGCHECK | (U2)BSWM_CAN_CHFAILST_INITNG);
            if(u2_t_chk != (U2)0U){
                vd_g_oXCANUsrhkExirClrIRQst(u1_gp_OXCAN_CTRLR_BY_CH[u4_t_lpcnt]);
                u2_t_fatal |= u2_t_chbit;
            }
            u2_t_chbit <<= 1U;
        }
    }

    return(u2_t_fatal);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



#if OXCAN_AUB_CSM_SUP



/*===================================================================================================================================*/
/*  static void    vd_s_oXCANSecurityInit(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANSecurityInit(void)
{
    Crypto_83_icus_Init(NULL_PTR);
#if OXCAN_AUB_CRPT_SW_SUP
    Crypto_83_sw_Init(NULL_PTR);
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
    CryIf_Init(NULL_PTR);
    Csm_Init(NULL_PTR);
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
    SecOC_Init(NULL_PTR);         /* ./inc/Compiler.h:52:#define NULL_PTR            ((void *)0).. */
    IdsM_Init(NULL_PTR);
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANSecurityFatal(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_oXCANSecurityFatal(void)
{
    U2                  u2_t_fatal;
    U2                  u2_t_icus_er;    /* ./inc/Crypto_83_icus.h:61:typedef uint16 Crypto_83_icus_Ab_ErrorStatusType; */
#if OXCAN_AUB_CRPT_SW_SUP
    U2                  u2_t_crpt_sw_er; /* ./inc/Crypto_83_sw.h:57:typedef uint16 Crypto_83_sw_Ab_ErrorStatusType;     */
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
    U2                  u2_t_csm_er;     /* ./inc/Csm.h:51:typedef uint16 Csm_Ab_ErrorStatusType;                       */
    U1                  u1_t_csm_md;     /* ./inc/Csm_Types.h:568:typedef uint8 Csm_ModeType;                           */
    U1                  u1_t_sht_ma;
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
    (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
    (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
    (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))
    U1                  u1_t_sec_md;  /* ./inc/SecOC_Types.h:34:typedef uint8 SecOC_ModeType;                        */
#endif  /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* The return of Csm_Ab_GetErrorStatus is intentionally discarded because the API returns E_NOT_OK       */
    /* only if the parameter "ptErrorStatus" is equal to NULL_PTR((void *)0)                                 */
    /*                                                                                                       */
    /* The return of Csm_GetMode is intentionally discarded because the API returns E_NOT_OK                 */
    /* only if the parameter "ud_Mode" is equal to NULL_PTR((void *)0)                                       */
    /*                                                                                                       */
    /* The return of SecOC_GetMode is intentionally discarded because the API returns E_NOT_OK               */
    /* only if the parameter "ptMode" is equal to NULL_PTR((void *)0)                                        */
    /* ----------------------------------------------------------------------------------------------------- */

    Crypto_83_icus_Ab_MainFunctionOut();
#if OXCAN_AUB_CRPT_SW_SUP
    Crypto_83_sw_Ab_MainFunctionOut();
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
    Csm_MainFunction();
    Crypto_83_icus_Ab_MainFunctionIn();
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
     (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))
    IdsM_MainFunction();
#endif  /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */
#if OXCAN_AUB_CRPT_SW_SUP
    Crypto_83_sw_Ab_MainFunctionIn();
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */

    u2_t_icus_er = CRYPTO_83_ICUS_AB_E_RAM_CHECK_FAIL;
    (void)Crypto_83_icus_Ab_GetErrorStatus(&u2_t_icus_er);

#if OXCAN_AUB_CRPT_SW_SUP
    u2_t_crpt_sw_er = CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL;
    (void)Crypto_83_sw_Ab_GetErrorStatus(&u2_t_crpt_sw_er);
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */

    u2_t_csm_er = CSM_AB_E_RAM_CHECK_FAIL;
    (void)Csm_Ab_GetErrorStatus(&u2_t_csm_er);

    u1_t_csm_md = CSM_AB_M_ABNORMAL;
    (void)Csm_Ab_GetMode(&u1_t_csm_md);

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
     (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))
    u1_t_sec_md = SECOC_M_ABNORMAL;
    (void)SecOC_Ab_GetMode(&u1_t_sec_md);
#endif  /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */

    u2_t_fatal  = (U2)0U;
    u1_t_sht_ma = (U1)TRUE;

    if((u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_HSM_FAULT      ) ||
       (u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_NOT_INITIALIZED) ||
       (u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_RAM_CHECK_FAIL ) ||
       (u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_NVM_LOCK       ) ||
       (u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_CRYPTO_LOCK    ) ||
       (u2_t_icus_er    == CRYPTO_83_ICUS_AB_E_ICUS_LOCK      ) ||
#if OXCAN_AUB_CRPT_SW_SUP
       (u2_t_crpt_sw_er == CRYPTO_83_SW_AB_E_NOT_INITIALIZED  ) ||
       (u2_t_crpt_sw_er == CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL   ) ||
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
       (u2_t_csm_er     == CSM_AB_E_NOT_INITIALIZED           ) ||
       (u2_t_csm_er     == CSM_AB_E_RAM_CHECK_FAIL            )){

        u2_t_fatal  = (U2)OXCAN_FATAL_AUB_SEC;
     /* u1_t_sht_ma = (U1)TRUE; */
    }

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
     (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))

    else if((u2_t_icus_er                   != CRYPTO_83_ICUS_AB_E_NONE     ) ||
#if OXCAN_AUB_CRPT_SW_SUP
            (u2_t_crpt_sw_er                != CRYPTO_83_SW_AB_E_NONE       ) ||
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
            ((u1_t_csm_md != CSM_AB_M_IDLE) && (u1_t_csm_md != CSM_AB_M_RUN)) ||
            ((u1_t_sec_md != SECOC_M_IDLE ) && (u1_t_sec_md != SECOC_M_RUN ))){

        vd_s_oXCANSecurityDeInit();

     /* u2_t_fatal  = (U2)0U;   */
     /* u1_t_sht_ma = (U1)TRUE; */
    }
    else if((u1_t_csm_md == CSM_AB_M_RUN) ||
            (u1_t_sec_md == SECOC_M_RUN )){
#else
    else if((u2_t_icus_er                   != CRYPTO_83_ICUS_AB_E_NONE     ) ||
#if OXCAN_AUB_CRPT_SW_SUP
            (u2_t_crpt_sw_er                != CRYPTO_83_SW_AB_E_NONE       ) ||
#endif /* #if OXCAN_AUB_CRPT_SW_SUP */
            ((u1_t_csm_md != CSM_AB_M_IDLE) && (u1_t_csm_md != CSM_AB_M_RUN))){

        vd_s_oXCANSecurityDeInit();

     /* u2_t_fatal  = (U2)0U;   */
     /* u1_t_sht_ma = (U1)TRUE; */
    }
    else if(u1_t_csm_md == CSM_AB_M_RUN){
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */

     /* u2_t_fatal  = (U2)0U;   */
        u1_t_sht_ma = (U1)FALSE;
    }
    else{

     /* u2_t_fatal  = (U2)0U;   */
     /* u1_t_sht_ma = (U1)TRUE; */
    }

    u1_s_oxcan_sht_ma = u1_t_sht_ma;

    return(u2_t_fatal);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANSecurityDeInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANSecurityDeInit(void)
{
    U4                  u4_t_gli;

    u4_t_gli = bsw_cs_system_DI();

#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS   )) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)) && \
     (BSW_BSWM_CS_CFG_FUNC_CS   ==BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC==BSW_USE))
    SecOC_DeInit();
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && ... */
    vd_s_oXCANSecurityInit();

    bsw_cs_system_EI(u4_t_gli);
}


#endif /* #if OXCAN_AUB_CSM_SUP */



/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000, Function Name tycan_bodycom -> oxcan.      */
/*  1.0.1     9/27/2022  TM       Support E2E.                                                                                       */
/*  1.0.2    10/14/2022  HU       u1_g_oXCANTxStat was implemented.                                                                  */
/*  1.0.3    10/20/2022  HU       vd_g_oXCANTxResume was improved.                                                                   */
/*  1.0.4    10/26/2022  HU       Improvement :  The "bsw_cannm_ch_config.h" include was optimzied.                                  */
/*  1.1.0    11/29/2022  SY       Aubist/CXPI(forTMC) Gen1 -> Gen2.                                                                  */
/*  1.1.1    12/13/2022  TM       Aubist/SEC Gen1 -> Gen2.                                                                           */
/*  1.1.2     1/25/2023  TM       Changed to be able to select receiving stops when sending stops. Not stop sending NM messages.     */
/*  1.1.3     5/10/2023  SY       Fix for CXPI. Fixed so that cxpicdd_sscheckslpcancel is not called.                                */
/*                       HU       vd_g_oXCANNmmsgStop and vd_g_oXCANNmmsgResume were implemented.                                    */
/*  1.1.4     6/08/2023  MI       Aubist/SEC was updated.                                                                            */
/*  1.2.0    12/20/2023  TM       QAC warnigs were fixed.                                                                            */
/*                       HU       CXPI was deleted from SleepNG condition of MET.                                                    */
/*  1.2.1     1/31/2024  TI       Changed oxcan_usrhk.h include order.                                                               */
/*  1.3.0     2/22/2024  MI       Support GetErrorStatus for Aubist/SEC(Icus/Csm/Crypto-sw).                                         */
/*  1.4.0     5/23/2024  HU       Bug Fix : CXPI Tranciever IC was stopped in vd_g_oXCANShutdown if CXPI was supported.              */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*  * TM   = Takanori Maruyama, DENSO                                                                                                */
/*  * SY   = Satoshi Yamada, DENSO                                                                                                   */
/*  * TI   = Tomoko Inuzuka, DENSO                                                                                                   */
/*  * MI   = Masahiko Izumi, DENSO                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
