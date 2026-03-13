/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_C_MAJOR                            (2U)
#define OXCAN_C_MINOR                            (0U)
#define OXCAN_C_PATCH                            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_cfg_private.h"

/* #include "oxcan.h" */          /* BSW_CANIF_CFG_WAKEUPSRC_CTRLx is defined in CanIf_Cfg.h      */
                                  /* CanIf_Cfg.h is included in CS_Can_Cfg.h                      */
                                  /* CS_Can_Cfg.h is included in oxcan.h                          */

#include "bsw_canif_st.h"         /* bsw_canif_st_u1ControllerToCh[] is defined in bsw_canif_st.h */

#include "bsw_com_config.h"       /* BSW_COM_MSG_NUM is defined in bsw_com_config.h               */
                                  /* BSW_COM_TX_MSG_NUM is defined in bsw_com_config.h            */

#include "bsw_com_st.h"           /* bsw_com_u4SysStatTbl[][] is defined in bsw_com_st.h          */
#include "bsw_bswm_cs_status.h"   /* bsw_bswm_cs_st_u2CSStatus is defined in bsw_bswm_cs_status.h */

#include "oxcan_aubif.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_C_MAJOR != OXCAN_H_MAJOR) || \
     (OXCAN_C_MINOR != OXCAN_H_MINOR) || \
     (OXCAN_C_PATCH != OXCAN_H_PATCH))
#error "oxcan.c and oxcan.h : source and header files are inconsistent!"
#endif

#if ((OXCAN_C_MAJOR != OXCAN_CFG_H_MAJOR) || \
     (OXCAN_C_MINOR != OXCAN_CFG_H_MINOR) || \
     (OXCAN_C_PATCH != OXCAN_CFG_H_PATCH))
#error "oxcan.c and oxcan_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_BACK_EN                            (0x5aU)
#define OXCAN_BACK_DI                            (0xa5U)

#define OXCAN_BACK_NWORD                         ((BSWM_CAN_BACKUPDATASIZE + 3U) >> 2U)
                                                                            /* BSWM_CAN_BACKUPDATASIZE is defined in BswM_Can.h  */
                                                                            /* BswM_Can.h is included in CS_Can.h                */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (BSW_BSWM_CS_CFG_MSGDELIVER != BSW_BSWM_CS_MSGDELIVER_MIDDLE) 
#error "oxcan.c : BSW_BSWM_CS_CFG_MSGDELIVER shall be configured to BSW_BSWM_CS_MSGDELIVER_MIDDLE" 
#endif /* #if (BSW_BSWM_CS_CFG_MSGDELIVER != BSW_BSWM_CS_MSGDELIVER_MIDDLE)  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (BSW_CANNM_NM_TYPE_USE(Y) != BSW_USE)

#if (OXCAN_LIB_CFG_EN_NMC == 1U)
#error "oxcan.c : oxcan_nmc is enabled even though Aubist/CanNM is disabled." 
#endif /* #if (OXCAN_LIB_CFG_EN_NMC == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
#error "oxcan.c : oxcan_wrh is enabled even though Aubist/CanNM is disabled." 
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) != BSW_USE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_BACK_NWORD > 0U)
static U4               u4_sp_oxcan_back[OXCAN_BACK_NWORD]  __attribute__((section(".bss_BACK_BSW")));
static volatile U1      u1_s_oxcan_br_chk                   __attribute__((section(".bss_BACK_BSW")));
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

static U4               u4_s_oxcan_sys_act;

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
static U4               u4_s_oxcan_ecu_act;
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXCAN_BACK_NWORD > 0U)
static void    vd_s_oXCANAubCsInit(void);
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
static U4      u4_s_oXCANNetActvtd(U4 * u4_ap_ecu_act);
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */

static U2      u2_s_oXCANFatal(void);

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
    u4_s_oxcan_sys_act = (U4)0U;

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    u4_s_oxcan_ecu_act = (U4)0U;
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */

    vd_g_oXCANAubIfInit();

#if (OXCAN_LIB_CFG_EN_NMC == 1U)
    vd_g_oXCANNmcInit();
#endif /* #if (OXCAN_LIB_CFG_EN_NMC == 1U) */

#if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U))
    vd_g_oXCANRxdInit();
#endif /* #if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U)) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaInit();
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtInit();
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
    vd_g_oXCANWrhInit((U1)TRUE);    /* u1_a_RST_INIT = TRUE  */
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

#if (OXCAN_BACK_NWORD > 0U)
    u1_s_oxcan_br_chk = (U1)0U;
    vd_s_oXCANAubCsInit();
#else
    BswM_CS_Init();
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

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
    u4_s_oxcan_sys_act = (U4)0U;

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    u4_s_oxcan_ecu_act = (U4)0U;
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */

    vd_g_oXCANAubIfInit();

#if (OXCAN_LIB_CFG_EN_NMC == 1U)
    vd_g_oXCANNmcInit();
#endif /* #if (OXCAN_LIB_CFG_EN_NMC == 1U) */

#if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U))
    vd_g_oXCANRxdInit();
#endif /* #if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U)) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaInit();
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtInit();
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
    vd_g_oXCANWrhInit((U1)FALSE);    /* u1_a_RST_INIT = FALSE */
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

#if (OXCAN_BACK_NWORD > 0U)
    vd_s_oXCANAubCsInit();
#else
    BswM_CS_Init();
#endif /* #if (OXCAN_BACK_NWORD > 0U) */

    vd_g_oXCANCfgWkupInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANVomEvhk(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANVomEvhk(void)
{
    U4                  u4_t_lpcnt;

    U4                  u4_t_sys_last;
    U4                  u4_t_sys_next;
    U4                  u4_t_sys_chk;

    U4                  u4_t_last;
    U4                  u4_t_next;

    u4_t_sys_last      = u4_s_oxcan_sys_act;
    u4_t_sys_chk       = u4_g_oXCANCfgVomchk() & (U4)OXCAN_SYS_VOM;

#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    u4_t_last          = u4_t_sys_last & ((U4)U4_MAX ^ (U4)OXCAN_SYS_VOM);
    u4_t_sys_next      = u4_t_sys_chk | u4_t_last;

    u4_t_last          = u4_s_oxcan_ecu_act & ((U4)U4_MAX ^ (U4)OXCAN_SYS_VOM);
    u4_t_sys_chk       = u4_t_sys_chk | u4_t_last;
    u4_s_oxcan_ecu_act = u4_t_sys_chk;
#else
    u4_t_sys_next      = u4_t_sys_chk;
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */

    u4_s_oxcan_sys_act = u4_t_sys_next;

#if   (OXCAN_LIB_CFG_EN_RXD == 2U)
    vd_g_oXCANRxdSysEvhk(u4_t_sys_next, u4_t_sys_chk);
#elif (OXCAN_LIB_CFG_EN_RXD == 1U)
    vd_g_oXCANRxdSysEvhk(u4_t_sys_next, u4_t_sys_next);
#else
 /* do nothing */
#endif /* #if   (OXCAN_LIB_CFG_EN_RXD == 2U) */

    /* ----------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                           */
    /* ----------------------------------------------------------------------------------------------------- */
    /* BswM_CS_SetSystemStatus((U4)U4_MAX, u4_t_sys_next) is NOT invoked at here as designed.                */
    /* ----------------------------------------------------------------------------------------------------- */

    for(u4_t_lpcnt = (U4)BSW_COM_TX_MSG_NUM; u4_t_lpcnt < (U4)BSW_COM_MSG_NUM; u4_t_lpcnt++){

        u4_t_sys_chk = bsw_com_u4SysStatTbl[u4_t_lpcnt][0];
        u4_t_last    = u4_t_sys_last & u4_t_sys_chk;
        u4_t_next    = u4_t_sys_next & u4_t_sys_chk;
        if(((u4_t_last != (U4)0U) && (u4_t_next == (U4)0U)) ||
           ((u4_t_last == (U4)0U) && (u4_t_next != (U4)0U))){

            Com_InitIPDUStatus((PduIdType)u4_t_lpcnt, ((U1)COM_NO_RX | (U1)COM_TIMEOUT));
        }
    }

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaSysEvhk(u4_t_sys_next);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

    vd_g_oXCANCfgVomEvhk(u4_t_sys_last, u4_t_sys_next);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANMainPreTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
/*===================================================================================================================================*/
void    vd_g_oXCANMainPreTask(void)
{
    U4                  u4_t_vom_act;
    U4                  u4_t_sys_act;
    U4                  u4_t_ecu_1st;
    U4                  u4_t_ecu_2nd;

    u4_t_vom_act = u4_g_oXCANCfgVomchk() & (U4)OXCAN_SYS_VOM;
    u4_t_ecu_1st = u4_t_vom_act;
    u4_t_sys_act = u4_s_oXCANNetActvtd(&u4_t_ecu_1st) | u4_t_vom_act;

    u4_s_oxcan_sys_act = u4_t_sys_act;

#if   (OXCAN_LIB_CFG_EN_RXD == 2U)
    vd_g_oXCANRxdMainTask(u4_t_sys_act, u4_t_ecu_1st);
#elif (OXCAN_LIB_CFG_EN_RXD == 1U)
    vd_g_oXCANRxdMainTask(u4_t_sys_act, u4_t_sys_act);
#else
 /* do nothing */
#endif /* #if   (OXCAN_LIB_CFG_EN_RXD == 2U) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaTimElpsd(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtMainRx();
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
    vd_g_oXCANWrhMainTask(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

    /* ----------------------------------------------------------------------------------------------------- */
    BswM_CS_SetSystemStatus((U4)OXCAN_SYS_VOM, u4_t_sys_act);
    BswM_CS_MainFunctionMiddle();
    /* ----------------------------------------------------------------------------------------------------- */

    u4_t_ecu_2nd = u4_t_vom_act;
    u4_t_sys_act = u4_s_oXCANNetActvtd(&u4_t_ecu_2nd) | u4_t_vom_act;
    if(u4_t_sys_act != u4_s_oxcan_sys_act){

        u4_s_oxcan_sys_act = u4_t_sys_act;
        u4_s_oxcan_ecu_act = u4_t_ecu_2nd;

#if   (OXCAN_LIB_CFG_EN_RXD == 2U)
        vd_g_oXCANRxdSysEvhk(u4_t_sys_act, u4_t_ecu_2nd);
#elif (OXCAN_LIB_CFG_EN_RXD == 1U)
        vd_g_oXCANRxdSysEvhk(u4_t_sys_act, u4_t_sys_act);
#else
     /* do nothing */
#endif /* #if   (OXCAN_LIB_CFG_EN_RXD == 2U) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
        vd_g_oXCANSysEaSysEvhk(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */
    }
    else if(u4_t_ecu_1st != u4_t_ecu_2nd){

        u4_s_oxcan_ecu_act = u4_t_ecu_2nd;

#if (OXCAN_LIB_CFG_EN_RXD == 2U)
        vd_g_oXCANRxdSysEvhk(u4_t_sys_act, u4_t_ecu_2nd);
#endif /* #if (OXCAN_LIB_CFG_EN_RXD == 2U) */
    }
    else{
        /* do nothing */
    }

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtMainTx(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaEvAct((U1)OXCAN_SYSEA_EAGR_1ST);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

    vd_g_oXCANCfgPreTask(u4_t_sys_act);
}
/*===================================================================================================================================*/
#else /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */
/*===================================================================================================================================*/
void    vd_g_oXCANMainPreTask(void)
{
    U4                  u4_t_sys_act;

    u4_t_sys_act       = u4_g_oXCANCfgVomchk() & (U4)OXCAN_SYS_VOM;
    u4_s_oxcan_sys_act = u4_t_sys_act;

#if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U))
    vd_g_oXCANRxdMainTask(u4_t_sys_act, u4_t_sys_act);
#endif /* #if ((OXCAN_LIB_CFG_EN_RXD == 1U) || (OXCAN_LIB_CFG_EN_RXD == 2U)) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaTimElpsd(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtMainRx();
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
    vd_g_oXCANWrhMainTask(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */

    /* ----------------------------------------------------------------------------------------------------- */
    BswM_CS_SetSystemStatus((U4)OXCAN_SYS_VOM, u4_t_sys_act);
    BswM_CS_MainFunctionMiddle();
    /* ----------------------------------------------------------------------------------------------------- */

#if (OXCAN_LIB_CFG_EN_VCT == 1U)
    vd_g_oXCANvCtMainTx(u4_t_sys_act);
#endif /* #if (OXCAN_LIB_CFG_EN_VCT == 1U) */

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaEvAct((U1)OXCAN_SYSEA_EAGR_1ST);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

    vd_g_oXCANCfgPreTask(u4_t_sys_act);
}
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */
/*===================================================================================================================================*/
/*  void    vd_g_oXCANMainPosTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANMainPosTask(void)
{
    U2                  u2_t_fatal;

#if (OXCAN_LIB_CFG_EN_SEA == 1U)
    vd_g_oXCANSysEaEvAct((U1)OXCAN_SYSEA_EAGR_2ND);
#endif /* #if (OXCAN_LIB_CFG_EN_SEA == 1U) */

    u2_t_fatal = u2_s_oXCANFatal();

    vd_g_oXCANCfgPosTask(u4_s_oxcan_sys_act, u2_t_fatal);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXCANShtdwn(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXCANShtdwn(void)
{
#if (OXCAN_BACK_NWORD > 0U)
    U1                  u1_t_br_chk;

    vd_g_oXCANCfgShtdwn();
    BswM_CS_Sleep();

    u1_t_br_chk = u1_s_oxcan_br_chk;
    if(u1_t_br_chk != (U1)OXCAN_BACK_DI){

        BswM_Can_GetBackupData((U1 *)&u4_sp_oxcan_back[0]);
        u1_s_oxcan_br_chk = (U1)OXCAN_BACK_EN;
    }
#else
    vd_g_oXCANCfgDeInit();
    BswM_CS_Sleep();
#endif /* #if (OXCAN_BACK_NWORD > 0U) */
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXCANShtdwnOk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE : Shtdwn OK, else Not                                                                                       */
/*===================================================================================================================================*/
U1      u1_g_oXCANShtdwnOk(void)
{
    U1                  u1_t_sht_ok;
    U1                  u1_t_awk;

    u1_t_awk = BswM_CS_CheckAwake();
    if(u1_t_awk == (U1)BSWM_CS_AWAKE_EXIST){

        u1_t_sht_ok = (U1)FALSE;
    }
    else{

#if (OXCAN_LIB_CFG_EN_WRH == 1U)
        u1_t_sht_ok = u1_g_oXCANWrhShtdwnOk();
#else
        u1_t_sht_ok = (U1)TRUE;
#endif /* #if (OXCAN_LIB_CFG_EN_WRH == 1U) */
    }

    return(u1_t_sht_ok);
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANSysActvtd(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXCAN_SYS_XXX defined in oxcan_sys_def.h                                                                         */
/*===================================================================================================================================*/
U4      u4_g_oXCANSysActvtd(void)
{
    return(u4_s_oxcan_sys_act);
}
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANEcuActvtd(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXCAN_SYS_XXX defined in oxcan_sys_def.h                                                                         */
/*===================================================================================================================================*/
U4      u4_g_oXCANEcuActvtd(void)
{
#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)
    return(u4_s_oxcan_ecu_act);
#else
    return(u4_s_oxcan_sys_act);
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */
}
/*===================================================================================================================================*/

#if (OXCAN_BACK_NWORD > 0U)

/*===================================================================================================================================*/
/*  static void    vd_s_oXCANAubCsInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANAubCsInit(void)
{
    U4                  u4_t_lpcnt;
    U4                  u4_t_ctrl_num;
    U1                  u1_t_br_chk;

    u1_t_br_chk       = u1_s_oxcan_br_chk;
    u1_s_oxcan_br_chk = (U1)0U;
    if(u1_t_br_chk == (U1)OXCAN_BACK_EN){

        BswM_Can_SetBackupData((U1 *)&u4_sp_oxcan_back[0]);

        u4_t_ctrl_num = (U4)BSW_CANIF_CFG_MPU_CONTROLLERNUM;
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_t_ctrl_num; u4_t_lpcnt++){
            (void)CanIf_CheckWakeup(bsw_canif_st_u1ControllerToCh[u4_t_lpcnt]);
        }

        BswM_CS_Wakeup();

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)BSW_COM_MSG_NUM; u4_t_lpcnt++){
            (void)Com_InitIPDU((PduIdType)u4_t_lpcnt);
        }
    }
    else{

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)OXCAN_BACK_NWORD; u4_t_lpcnt++){
            u4_sp_oxcan_back[u4_t_lpcnt] = (U4)0U;
        }
        BswM_CS_Init();
    }
}
#endif /* #if (OXCAN_BACK_NWORD > 0U) */
/*===================================================================================================================================*/


#if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE)


/*===================================================================================================================================*/
/*  static U4      u4_s_oXCANNetActvtd(U4 * u4_ap_ecu_act)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_oXCANNetActvtd(U4 * u4_ap_ecu_act)
{
    U4                 u4_t_lpcnt;
    U4                 u4_t_sys_chk;
    U4                 u4_t_ecu_chk;
    U4                 u4_t_bit;
    U2                 u2_t_sts;
    U1                 u1_t_mod;
    U1                 u1_t_chk;

    u4_t_sys_chk = (U4)0U;
    u4_t_ecu_chk = (U4)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_NET_NUM_CH; u4_t_lpcnt++){

        /* #define NM_STATE_BUS_SLEEP              (BSW_NM_STATE_BUS_SLEEP)                      */
        /* #define NM_STATE_PREPARE_BUS_SLEEP      (BSW_NM_STATE_PREPARE_BUS_SLEEP)              */
        /* #define NM_STATE_READY_SLEEP            (BSW_NM_STATE_READY_SLEEP)                    */
        /* #define NM_STATE_NORMAL_OPERATION       (BSW_NM_STATE_NORMAL_OPERATION)               */
        /* #define NM_STATE_REPEAT_MESSAGE         (BSW_NM_STATE_REPEAT_MESSAGE)                 */
        /* #define NM_STATE_INVALID                (BSW_NM_STATE_INVALID)                        */
        /* #define BSW_NM_STATE_BUS_SLEEP          (0x01FEU)                                     */
        /* #define BSW_NM_STATE_PREPARE_BUS_SLEEP  (0x02FDU)                                     */
        /* #define BSW_NM_STATE_READY_SLEEP        (0x03FCU)                                     */
        /* #define BSW_NM_STATE_NORMAL_OPERATION   (0x04FBU)                                     */
        /* #define BSW_NM_STATE_REPEAT_MESSAGE     (0x05FAU)                                     */
        /* #define BSW_NM_STATE_INVALID            (0x00FFU)                                     */
        /*                                                                                       */
        /* Std_ReturnType Nm_GetState( NetworkHandleType nmNetworkHandle,                        */
        /*                             Nm_StateType* nmStatePtr,                                 */
        /*                             Nm_ModeType* nmModePtr             )                      */
        /*                                                                                       */
        /* comm/bsw_nm_public.h    71:typedef uint16              Bsw_Nm_StateType;              */
        /* NmStack_Types.h         61:#define Nm_StateType        Bsw_Nm_StateType               */
        /* comm/bsw_nm_public.h    71:typedef uint8               Bsw_Nm_ModeType;               */
        /* NmStack_Types.h         62:#define Nm_ModeType         Bsw_Nm_ModeType                */
        /* ComStack_Types.h        83:typedef uint8               NetworkHandleType;             */
        /*                                                                                       */
            
        u2_t_sts = (U2)NM_STATE_INVALID;
        (void)Nm_GetState((U1)st_gp_OXCAN_NET_BY_CH[u4_t_lpcnt].u2_cch, &u2_t_sts, &u1_t_mod);
        if((u2_t_sts == (U2)NM_STATE_REPEAT_MESSAGE  ) ||
           (u2_t_sts == (U2)NM_STATE_NORMAL_OPERATION)){
            u4_t_bit     = st_gp_OXCAN_NET_BY_CH[u4_t_lpcnt].u4_sysbit;
            u4_t_sys_chk |= u4_t_bit;
            u4_t_ecu_chk |= u4_t_bit;
        }
        else if(u2_t_sts == (U2)NM_STATE_READY_SLEEP){
            u4_t_sys_chk |= st_gp_OXCAN_NET_BY_CH[u4_t_lpcnt].u4_sysbit;
        }
        else{
            /* do nothing */
        }
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_g_OXCAN_NET_NUM_PN; u4_t_lpcnt++){

        /* #define COMM_PNC_REQUESTED                      (BSW_COMM_PNC_REQUESTED)              */
        /* #define COMM_PNC_READY_SLEEP                    (BSW_COMM_PNC_READY_SLEEP)            */
        /* #define COMM_PNC_PREPARE_SLEEP                  (BSW_COMM_PNC_PREPARE_SLEEP)          */
        /* #define COMM_PNC_NO_COMMUNICATION               (BSW_COMM_PNC_NO_COMMUNICATION)       */
        /* #define BSW_COMM_PNC_REQUESTED                      (0U)                              */
        /* #define BSW_COMM_PNC_READY_SLEEP                    (1U)                              */
        /* #define BSW_COMM_PNC_PREPARE_SLEEP                  (2U)                              */
        /* #define BSW_COMM_PNC_NO_COMMUNICATION               (3U)                              */
        /*                                                                                       */
        /* Std_ReturnType ComM_GetChPncMode( NetworkHandleType Channel, PNCHandleType PNC,       */
        /*                                                     ComM_PncModeType* RequestedMode ) */
        /*                                                                                       */
        /* ComStack_Types.h        55:typedef uint8                PNCHandleType;                */
        /* comm/bsw_comm_public.h 450:typedef uint8                Bsw_ComM_PncModeType;         */
        /* ComM.h                 376:#define ComM_PncModeType     Bsw_ComM_PncModeType          */
        /*                                                                                       */
        u1_t_chk = (U1)COMM_PNC_NO_COMMUNICATION;
        (void)ComM_GetChPncMode((U1)st_gp_OXCAN_NET_BY_PN[u4_t_lpcnt].u2_cch,
                                (U1)st_gp_OXCAN_NET_BY_PN[u4_t_lpcnt].u2_pnc,
                                &u1_t_chk);
        if(u1_t_chk == (U1)COMM_PNC_REQUESTED){
            u4_t_bit     = st_gp_OXCAN_NET_BY_PN[u4_t_lpcnt].u4_sysbit;
            u4_t_sys_chk |= u4_t_bit;
            u4_t_ecu_chk |= u4_t_bit;
        }
        else if(u1_t_chk == (U1)COMM_PNC_READY_SLEEP){
            u4_t_sys_chk |= st_gp_OXCAN_NET_BY_PN[u4_t_lpcnt].u4_sysbit;
        }
        else{
            /* do nothing */
        }
    }

    (*u4_ap_ecu_act) |= u4_t_ecu_chk;

    return(u4_t_sys_chk);
}
#endif /* #if (BSW_CANNM_NM_TYPE_USE(Y) == BSW_USE) */
/*===================================================================================================================================*/
/*  static U2      u2_s_oXCANFatal(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2      u2_s_oXCANFatal(void)
{
    U4                  u4_t_lpcnt;
    U2                  u2_t_can;
    U2                  u2_t_chk;
    U2                  u2_t_chbit;
    U2                  u2_t_fatal;

    if(bsw_bswm_cs_st_u2CSStatus != BSW_BSWM_CS_u2PVTST_RUN){

        u2_t_fatal = (U2)OXCAN_FATAL_AUB_COM;

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)BSW_COM_CFG_CHNUM; u4_t_lpcnt++){
            (void)u4_g_oXCANUsrhkWRQst(u1_gp_OXCAN_CTRLR_BY_CH[u4_t_lpcnt], (U1)TRUE);
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
                (void)u4_g_oXCANUsrhkWRQst(u1_gp_OXCAN_CTRLR_BY_CH[u4_t_lpcnt], (U1)TRUE);
                u2_t_fatal |= u2_t_chbit;
            }
            u2_t_chbit <<= 1U;
        }
    }

    return(u2_t_fatal);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0     2/20/2025  TN       oXCAN v1.4.0 -> oXCAN v2.0.0 was redesigned for Toyota BEVStep3.                                   */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
