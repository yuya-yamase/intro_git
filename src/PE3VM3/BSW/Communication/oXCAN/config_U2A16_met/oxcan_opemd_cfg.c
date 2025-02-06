/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXtention of CAN Operational Mode                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_OPEMD_CFG_C_MAJOR                  (1U)
#define OXCAN_OPEMD_CFG_C_MINOR                  (0U)
#define OXCAN_OPEMD_CFG_C_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxcan_opemd_cfg_private.h"

#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXCAN_OPEMD_CFG_C_MAJOR != OXCAN_OPEMD_CFG_H_MAJOR) || \
     (OXCAN_OPEMD_CFG_C_MINOR != OXCAN_OPEMD_CFG_H_MINOR) || \
     (OXCAN_OPEMD_CFG_C_PATCH != OXCAN_OPEMD_CFG_H_PATCH))
#error "oxcan_opemd_cfg.c and oxcan_opemd_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXCAN_OPEMD_BIT0_MASK      (0xFFFFFFFEU)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXCANOpemdEvTxRidngOn250ms(void);
static void    vd_s_oXCANOpemdEvTxRidngOn2p5s(void);
static void    vd_s_oXCANOpemdEvTxPonEmgOn250ms(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXCAN_OPEMD_CHK           st_gp_OXCAN_OPEMD_CHK[OXCAN_OPEMD_NUM_CHK] = {
    /* OXCAN_OPEMD_CHK_NM_AWK  (0U)      */
    {
        (U4)VEH_OPEMD_MDBIT_POE,                              /* u4_vom_chk */
        (U4)0x0000U,                                          /* u4_tim_run */
        (U4)0x0000U                                           /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PAR  (1U)           */
    {
        (U4)VEH_OPEMD_MDBIT_PAR,                             /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PAR,                             /* u4_tim_run */
        (U4)OXCAN_SYS_PAR                                    /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_RID_ON  (2U)        */
    {
        (U4)VEH_OPEMD_MDBIT_RID,                             /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_RID,                             /* u4_tim_run */
        (U4)OXCAN_SYS_RID                                    /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PON_ON  (3U)        */
    {
        (U4)VEH_OPEMD_MDBIT_PON,                              /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PON,                              /* u4_tim_run */
        (U4)OXCAN_SYS_PON                                    /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_POE_ON  (4U)        */
    {
        (U4)VEH_OPEMD_MDBIT_POE,                             /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_POE,                             /* u4_tim_run */
        (U4)OXCAN_SYS_POE                                    /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PARK_PAR_HV (5U)    */
    {
        (U4)VEH_OPEMD_MDBIT_PAR_HV,                          /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PAR_HV,                          /* u4_tim_run */
        (U4)OXCAN_SYS_PAR_HV                                 /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PAR_HVHC (6U)       */
    {
        (U4)VEH_OPEMD_MDBIT_PAR_HVHC,                        /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PAR_HVHC,                        /* u4_tim_run */
        (U4)OXCAN_SYS_PAR_HVHC                               /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_CHK (7U)            */
    {
        (U4)VEH_OPEMD_MDBIT_CHK,                             /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_CHK,                             /* u4_tim_run */
        (U4)OXCAN_SYS_CHK                                    /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PDM (8U)            */
    {
        (U4)VEH_OPEMD_MDBIT_PDM,                            /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PDM,                            /* u4_tim_run */
        (U4)OXCAN_SYS_PDM                                   /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_OTA1 (9U)           */
    {
        (U4)VEH_OPEMD_MDBIT_OTA1,                           /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_OTA1,                           /* u4_tim_run */
        (U4)OXCAN_SYS_OTA1                                  /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_OTA2 (10U)          */
    {
        (U4)VEH_OPEMD_MDBIT_OTA2,                           /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_OTA2,                           /* u4_tim_run */
        (U4)OXCAN_SYS_OTA2                                  /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_OTA3 (11U)          */
    {
        (U4)VEH_OPEMD_MDBIT_OTA3,                           /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_OTA3,                           /* u4_tim_run */
        (U4)OXCAN_SYS_OTA3                                  /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_OTA4 (12U)          */
    {
        (U4)VEH_OPEMD_MDBIT_OTA4,                           /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_OTA4,                           /* u4_tim_run */
        (U4)OXCAN_SYS_OTA4                                  /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_WRP(13U)            */
    {
        (U4)VEH_OPEMD_MDBIT_WRP,                            /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_WRP,                            /* u4_tim_run */
        (U4)OXCAN_SYS_WRP                                   /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_EDS (14U)           */
    {
        (U4)VEH_OPEMD_MDBIT_EDS,                            /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_EDS,                            /* u4_tim_run */
        (U4)OXCAN_SYS_EDS                                   /* u4_sys_act */
    },
    /* OXCAN_OPEMD_CHK_PAO (15U)           */
    {
        (U4)VEH_OPEMD_MDBIT_PAO,                            /* u4_vom_chk */
        (U4)VEH_OPEMD_MDBIT_PAO,                            /* u4_tim_run */
        (U4)OXCAN_SYS_PAO                                   /* u4_sys_act */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_OXCAN_OPEMD_EVTX          st_gp_OXCAN_OPEMD_EVTX[] = {
    {
        &vd_s_oXCANOpemdEvTxRidngOn250ms,  /* fp_vd_EVTX */
        (U2)OXCAN_OPEMD_CHK_RID_ON,        /* u2_tim_idx */
        (U2)250U / (U2)OXCAN_MAIN_TICK     /* u2_tim_evt */
    },
    {
        &vd_s_oXCANOpemdEvTxRidngOn2p5s,   /* fp_vd_EVTX */
        (U2)OXCAN_OPEMD_CHK_RID_ON,        /* u2_tim_idx */
        (U2)2500U / (U2)OXCAN_MAIN_TICK    /* u2_tim_evt */
    },
    {
        &vd_s_oXCANOpemdEvTxPonEmgOn250ms, /* fp_vd_EVTX */
        (U2)OXCAN_OPEMD_CHK_POE_ON,        /* u2_tim_idx */
        (U2)250U / (U2)OXCAN_MAIN_TICK     /* u2_tim_evt */
    }
};
const U1                           u1_g_OXCAN_OPEMD_NUM_EVTX = (U1)3U;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U4      u4_g_oXCANOpemdCfgMdfield(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_oXCANOpemdCfgMdfield(void)
{
    U4    u4_t_veopemd;
    
    u4_t_veopemd = u4_g_VehopemdMdfield();
    /*-------------------------------------------------------------------*/
    /* Access to 4byte RAM is completed with one instruction.            */
    /* There is no interrupt during access, SPINLOCK is not required.    */
    /*-------------------------------------------------------------------*/
    u4_t_veopemd = (U4)((u4_t_veopemd & (U4)OXCAN_OPEMD_BIT0_MASK) | *u4_g_oxcan_nmsts);

    return(u4_t_veopemd);
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANOpemdEvTxRidngOn250ms(void)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANOpemdEvTxRidngOn250ms(void)
{
    /* Users Configration */

    /* Sample Code */
/*  Com_TriggerIPDUSend(MSG_MET1H01_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H02_H_FD); */
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANOpemdEvTxRidngOn2p5s(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANOpemdEvTxRidngOn2p5s(void)
{
    /* Sample Code */
/*  Com_TriggerIPDUSend(MSG_MET1H01_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H11_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H18_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H04_H_FD); */
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXCANOpemdEvTxPonEmgOn250ms(void)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCANOpemdEvTxPonEmgOn250ms(void)
{
    /* Sample Code */
/*  Com_TriggerIPDUSend(MSG_MET1H01_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H02_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H10_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H11_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H18_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H04_H_FD); */
/*  Com_TriggerIPDUSend(MSG_MET1H24_H_FD); */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/22/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000.                                            */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HU   = Hayato Usui, DENSO                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
