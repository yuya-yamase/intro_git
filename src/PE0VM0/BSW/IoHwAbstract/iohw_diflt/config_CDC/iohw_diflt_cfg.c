/* 1.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Digital Input Filter                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_CFG_C_MAJOR                   (1)
#define IOHW_DIFLT_CFG_C_MINOR                   (4)
#define IOHW_DIFLT_CFG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "iohw_diflt_cfg_private.h"
/* #include "rngcmpr_u2.h" */

#include "iohw_adc.h"
#include "Dio.h"
/* #include "veh_opemd.h" */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IOHW_DIFLT_CFG_C_MAJOR != IOHW_DIFLT_CFG_H_MAJOR) || \
     (IOHW_DIFLT_CFG_C_MINOR != IOHW_DIFLT_CFG_H_MINOR) || \
     (IOHW_DIFLT_CFG_C_PATCH != IOHW_DIFLT_CFG_H_PATCH))
#error "iohw_diflt_cfg.c and iohw_diflt_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((IOHW_DIFLT_CFG_C_MAJOR != IOHW_DIFLT_SGNL_H_MAJOR) || \
     (IOHW_DIFLT_CFG_C_MINOR != IOHW_DIFLT_SGNL_H_MINOR) || \
     (IOHW_DIFLT_CFG_C_PATCH != IOHW_DIFLT_SGNL_H_PATCH))
#error "iohw_diflt_cfg.c and iohw_diflt_sgnl.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_SMPLG_TICK                    (10U)  /* 10ms */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_SMPLGCHK_PW3V_ACT             (0x0001U)
#define IOHW_DIFLT_SMPLGCHK_PW5V_ACT             (0x0002U)

#ifdef VEH_OPEMD_H
#define IOHW_DIFLT_SMPLGCHK_ACC_ON               (VEH_OPEMD_MDBIT_ACC) /* 0x00000010U */
#define IOHW_DIFLT_SMPLGCHK_STA_ON               (VEH_OPEMD_MDBIT_STA) /* 0x00000020U */
#define IOHW_DIFLT_SMPLGCHK_IGN_ON               (VEH_OPEMD_MDBIT_IGN) /* 0x00000040U */
#else
#define IOHW_DIFLT_SMPLGCHK_ACC_ON               (0x00000010U)
#define IOHW_DIFLT_SMPLGCHK_STA_ON               (0x00000020U) /* 0x00000020U */
#define IOHW_DIFLT_SMPLGCHK_IGN_ON               (0x00000040U) /* 0x00000040U */
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_DIFLT_NUM_DIPORT                    (1U)
#define IOHW_DIFLT_DIPORT_00                     (0U)
#define IOHW_DIFLT_DIPORT_01                     (1U)
#define IOHW_DIFLT_DIPORT_02                     (2U)
#define IOHW_DIFLT_DIPORT_03                     (3U)

#if (IOHW_DIFLT_NUM_DIPORT > IOHW_DIFLT_DIPORT_NUM_INST)
#error "IOHW_DIFLT_NUM_DIPORT shall be less than IOHW_DIFLT_DIPORT_NUM_INST. Otherwise, iohw_diflt shall be rebuilt from *.c."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section bss=".IOHW_DIFLT_BSS_VAR_NO_INIT"

U4                          u4_gp_iohw_diflt_fltrd[IOHW_DIFLT_NUM_DIPORT]          __attribute__((section(".bss_SHARE_IOHW_DIFLT_FLTRD")));
U2                          u2_gp_iohw_diflt_smpld[IOHW_DIFLT_NUM_DIPORT];

ST_IOHW_DICTRL              st_gp_iohw_diflt_ctrl[IOHW_DIFLT_NUM_DISGNL];

#pragma ghs section bss=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------------- */
/* Attention :                                                                                  */
/* If sampling conditions are determined after executing vd_g_IoHwDifltMainTask, the conditions */
/* expect to be set to u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT in order to synchronize between          */
/* sampling conditions and di-signals in vd_g_IoHwDifltSgnlInit.                                */
/*                                                                                              */
/* Example)                                                                                     */
/* In Toyota-MET/HUD, vehicle operational mode, especially Ignition, are detemined after        */
/* executing vd_g_IoHwDifltMainTask.                                                            */
/* -------------------------------------------------------------------------------------------- */
#pragma ghs section rodata=".IOHW_DIFLT_RODATA_CONST"

const U2                    u2_g_IOHW_DIFLT_SMPLGCHK_AT_EVT = ((U2)IOHW_DIFLT_SMPLGCHK_ACC_ON |
                                                               (U2)IOHW_DIFLT_SMPLGCHK_STA_ON |
                                                               (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                    u2_g_IOHW_DIFLT_NUM_DIPORT = (U2)IOHW_DIFLT_NUM_DIPORT;

#define IOHW_DIFLT_NUM_FLTR                      (3U)
#define IOHW_DIFLT_FLTR_ALWAYS                   (0U)
#define IOHW_DIFLT_FLTR_IGN_ON                   (1U)
#define IOHW_DIFLT_FLTR_PW3V_IGN_ON              (2U)
const ST_IOHW_DIFLTR        st_gp_IOHW_DIFLT_FLTR[IOHW_DIFLT_NUM_FLTR] = {
    {
        (U2)0x0000U,                                                          /* u2_smplgchk   */
        (U2)0x0000U,                                                          /* u2_smplgena   */
        /* ----------------------------------------------------------------------------------- */
        /* Attention :                                                                         */
        /* ----------------------------------------------------------------------------------- */
        /* if u2_dlymask > 0, IOHW_DILFT_CTRLOPT_DLYMSK_ENA shall be set to u2_ctrlopt.        */
        /* if u1_valid_init >= 2, IOHW_DILFT_CTRLOPT_INIT_ENA shall be set to u2_ctrlopt.      */
        /* ----------------------------------------------------------------------------------- */
        (U2)IOHW_DILFT_CTRLOPT_INIT_ENA,                                      /* u2_ctrlopt    */
        (U2)0U,                                                               /* u2_dlymask    */
        (U2)10U / (U2)IOHW_DIFLT_SMPLG_TICK,                                  /* u2_cycle      */
        (U1)6U,                                                               /* u1_valid_init */
        (U1)6U                                                                /* u1_valid_nrml */
    },
    {
        (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON | (U2)IOHW_DIFLT_SMPLGCHK_STA_ON,      /* u2_smplgchk   */
        (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON,                                       /* u2_smplgena   */
        /* ----------------------------------------------------------------------------------- */
        /* Attention :                                                                         */
        /* ----------------------------------------------------------------------------------- */
        /* if u2_dlymask > 0, IOHW_DILFT_CTRLOPT_DLYMSK_ENA shall be set to u2_ctrlopt.        */
        /* if u1_valid_init >= 2, IOHW_DILFT_CTRLOPT_INIT_ENA shall be set to u2_ctrlopt.      */
        /* ----------------------------------------------------------------------------------- */
        (U2)IOHW_DILFT_CTRLOPT_INIT_ENA,                                      /* u2_ctrlopt    */
        (U2)0U,                                                               /* u2_dlymask    */
        (U2)10U / (U2)IOHW_DIFLT_SMPLG_TICK,                                  /* u2_cycle      */
        (U1)3U,                                                               /* u1_valid_init */
        (U1)6U                                                                /* u1_valid_nrml */
    },
    {
        (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON | (U2)IOHW_DIFLT_SMPLGCHK_PW3V_ACT,    /* u2_smplgchk   */
        (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON | (U2)IOHW_DIFLT_SMPLGCHK_PW3V_ACT,    /* u2_smplgena   */
        /* ----------------------------------------------------------------------------------- */
        /* Attention :                                                                         */
        /* ----------------------------------------------------------------------------------- */
        /* if u2_dlymask > 0, IOHW_DILFT_CTRLOPT_DLYMSK_ENA shall be set to u2_ctrlopt.        */
        /* if u1_valid_init >= 2, IOHW_DILFT_CTRLOPT_INIT_ENA shall be set to u2_ctrlopt.      */
        /* ----------------------------------------------------------------------------------- */
        (U2)IOHW_DILFT_CTRLOPT_DLYMSK_ENA | (U2)IOHW_DILFT_CTRLOPT_INIT_ENA,  /* u2_ctrlopt    */
        (U2)100U / (U2)IOHW_DIFLT_SMPLG_TICK,                                 /* u2_dlymask    */
        (U2)10U  / (U2)IOHW_DIFLT_SMPLG_TICK,                                 /* u2_cycle      */
        (U1)3U,                                                               /* u1_valid_init */
        (U1)6U                                                                /* u1_valid_nrml */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_IOHW_DISGNL        st_gp_IOHW_DIFLT_DISGNL[IOHW_DIFLT_NUM_DISGNL] = {
    {(U2)0x0001U, (U2)0x0001U, (U2)IOHW_DIFLT_DIPORT_00, (U2)IOHW_DIFLT_FLTR_ALWAYS},    /* 00 : IOHW_DISGNL_IGN     */
    {(U2)0x0010U, (U2)0x0010U, (U2)IOHW_DIFLT_DIPORT_00, (U2)IOHW_DIFLT_FLTR_ALWAYS}   /* 01 : IOHW_DISGNL_SAMPLEPIN  */
};
const U2                    u2_g_IOHW_DIFLT_NUM_DISGNL = (U2)IOHW_DIFLT_NUM_DISGNL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_IOHW_DIGR          st_gp_IOHW_DIFLT_DIGR[IOHW_DIFLT_NUM_DIGR] = {
    {(U2)0x0011U, (U2)IOHW_DIFLT_DIPORT_00}
};
const U2                    u2_g_IOHW_DIFLT_NUM_DIGR = (U2)IOHW_DIFLT_NUM_DIGR;

#pragma ghs section rodata=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".IOHW_DIFLT_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_IoHwDifltCfgInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_IoHwDifltCfgInit(void)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* u4_gp_iohw_diflt_fltrd[], u2_gp_iohw_diflt_smpld[] and st_gp_iohw_diflt_ctrl[] are initialized  */
    /* in vd_g_IoHwDifltInit.                                                                          */
    /* Thus, those variables don't need to be initialized at here.                                     */
    /* ----------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  U2      u2_g_IoHwDifltCfgSmplgchk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U2      u2_g_IoHwDifltCfgSmplgchk(void)
{
#ifdef VEH_OPEMD_H
    static const U2                u2_s_IOHW_DIFLT_SMPLGCHK_OPE_FIELDS = ((U2)IOHW_DIFLT_SMPLGCHK_ACC_ON |
                                                                          (U2)IOHW_DIFLT_SMPLGCHK_STA_ON |
                                                                          (U2)IOHW_DIFLT_SMPLGCHK_IGN_ON);

    U2                             u2_t_smplgchk;

    u2_t_smplgchk = (U2)u4_g_VehopemdMdfield() & u2_s_IOHW_DIFLT_SMPLGCHK_OPE_FIELDS;

    return(u2_t_smplgchk);
#else
    return((U2)IOHW_DIFLT_SMPLGCHK_IGN_ON);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwDifltCfgRead(U2 * u2_ap_di_inst)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_IoHwDifltCfgRead(U2 * u2_ap_di_inst)
{
    static const U2                u2_s_IOHW_DIFLT_IG_LV_MAX = (U2)IOHW_ADC_LV_MAX;
    static const U2                u2_s_IOHW_DIFLT_IG_LV_MIN = (U2)512U;

    U2                             u2_t_lv;

    u2_ap_di_inst[IOHW_DIFLT_DIPORT_00] = (U2)0U;

    u2_t_lv = u2_g_IoHwAdcLv((U1)ADC_CH_IG_MON);
    if((u2_t_lv <= u2_s_IOHW_DIFLT_IG_LV_MAX) &&
       (u2_t_lv >= u2_s_IOHW_DIFLT_IG_LV_MIN)){
        u2_ap_di_inst[IOHW_DIFLT_DIPORT_00] |= (U2)0x0001U;
    }

    u2_ap_di_inst[IOHW_DIFLT_DIPORT_00] |= ((U2)Dio_ReadChannel(DIO_ID_PORT0_CH0)) << 4;

}

#pragma ghs section text=default

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/02/2015  TN       New.                                                                                               */
/*  1.1.0     4/22/2015  TN       iohw_diflt.c v1.0.0 -> v1.1.0.                                                                     */
/*  1.2.0     7/ 9/2015  TN       iohw_diflt.c v1.1.0 -> v1.2.0.                                                                     */
/*  1.3.0    10/28/2015  TN       iohw_diflt.c v1.2.0 -> v1.3.0.                                                                     */
/*  1.3.1    11/27/2015  TN       iohw_diflt.c v1.3.0 -> v1.3.1.                                                                     */
/*  1.3.2     9/ 7/2021  TN       iohw_diflt.c v1.3.1 -> v1.3.2.                                                                     */
/*  1.4.0    10/ 4/2021  TN       iohw_diflt.c v1.3.2 -> v1.4.0.                                                                     */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
