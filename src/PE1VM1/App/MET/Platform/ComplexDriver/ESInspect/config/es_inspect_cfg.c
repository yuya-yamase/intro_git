/* 1.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/* ECU Shipping Inspection                                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ES_INSPECT_CFG_C_MAJOR                   (1)
#define ES_INSPECT_CFG_C_MINOR                   (7)
#define ES_INSPECT_CFG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "es_inspect_cfg_private.h"
#if 0    /* BEV Diag provisionally */
#include "esi_memtest_cfg_private.h"
#include "esi_nvmr_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "esi_ramtest_d1x.h"
#include "esi_ssc.h"

#include "mem_section.h"
#include "lcom_spi_dsal.h"
#endif   /* BEV Diag provisionally */
#include "odo_km.h"
#include "nvmc_mgr.h"

#if 0    /* BEV Diag provisionally */
#include "dma_drv.h"
#endif   /* BEV Diag provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ES_INSPECT_CFG_C_MAJOR != ES_INSPECT_CFG_H_MAJOR) || \
     (ES_INSPECT_CFG_C_MINOR != ES_INSPECT_CFG_H_MINOR) || \
     (ES_INSPECT_CFG_C_PATCH != ES_INSPECT_CFG_H_PATCH))
#error "es_inspect_cfg.c and es_inspect_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define ESI_NUO_DI_KEYWORD                       (0x5aa5a55aU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                     u2_gp_ESI_TOUT_BY_MD[ES_INSPECT_NUM_MD] = {
    (U2)3000U  / (U2)ES_INSPECT_MAIN_TICK,      /* ES_INSPECT_MD_CHK (0U) */
    (U2)30000U / (U2)ES_INSPECT_MAIN_TICK,      /* ES_INSPECT_MD_RUN (1U) */
    (U2)100U   / (U2)ES_INSPECT_MAIN_TICK       /* ES_INSPECT_MD_FIN (2U) */
};

#if 0    /* BEV Diag provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_ESI_MEM_CRC  st_sp_ESI_MEM_CRC_D1L1[] = {
    {
        (const U4 *)0x00001FFC,         /* u4p_CRIT  */
        (const U1 *)0x00000000,         /* u1p_BLOCK */  /* RPRG1         */
        (U4)0x00001FFCU                 /* u4_nbyte  */  /* 8k - 4        */
    },
    {
        (const U4 *)0x001CFDFC,         /* u4p_CRIT  */
        (const U1 *)0x00006000,         /* u1p_BLOCK */  /* ECU1          */
        (U4)0x001C9DFCU                 /* u4_nbyte  */  /* 1864k - 4     */
    },
    {
        (const U4 *)0x001DFDFC,         /* u4p_CRIT  */
        (const U1 *)0x001D8000,         /* u1p_BLOCK */  /* ECU2          */
        (U4)0x00007DFCU                 /* u4_nbyte  */  /* 32k - 4       */
    },
    {
        (const U4 *)0x001FFADC,         /* u4p_CRIT  */
        (const U1 *)0x001E0000,         /* u1p_BLOCK */  /* RPRG2         */
        (U4)0x0001FADCU                 /* u4_nbyte  */  /* 128k - 4      */
    },
    {
        (const U4 *)0x001FFFFC,         /* u4p_CRIT  */
        (const U1 *)0x001FFAE0,         /* u1p_BLOCK */  /* KEY           */
        (U4)0x0000051CU                 /* u4_nbyte  */  /* 1k - 4        */
    },
    {
        (const U4 *)0x01007FFC,         /* u4p_CRIT  */
        (const U1 *)0x01000000,         /* u1p_BLOCK */  /* RPRG3         */
        (U4)0x00007FFCU                 /* u4_nbyte  */  /* 32k - 4       */
    }
};

static const ST_ESI_MEM_RWC  st_s_ESI_MEM_RWC_D1L1[] = {
    {
        &u1_g_ESIRamTestLocal,          /* fp_u1_RWC     */
        MEM_SEC_ADDR_STA_LOCAL_USD,     /* u4p_blo_begin */
        MEM_SEC_ADDR_END_LOCAL_USD,     /* u4p_blo_end   */
        ((U4)256U >> 2U)                /* u4_rwc_nword  */ /* 256 bytes, 30 microseconds @ 120MHz */
    },
    {
        &u1_g_ESIRamTestXcsys,          /* fp_u1_RWC     */
        MEM_SEC_ADDR_STA_BACK_USD,      /* u4p_blo_begin */
        MEM_SEC_ADDR_END_BACK_USD,      /* u4p_blo_end   */
        ((U4)64U >> 2U)                 /* u4_rwc_nword  */ /*  64 bytes, 20 microseconds @ 120MHz */
    }
};
const ST_ESI_MEM_SEQ         st_gp_ESI_MEM_TEST_SEQ[] = {
    {
        &st_sp_ESI_MEM_CRC_D1L1[0],     /* stp_CRC       */
        &st_s_ESI_MEM_RWC_D1L1[0],      /* stp_RWC       */
        (U2)6U,                         /* u2_crc_nblock */
        (U2)2U                          /* u2_rwc_nblock */
    }
};
const U1                     u1_g_ESI_MEM_TEST_NUM_SEQ  = (U1)ESI_MEM_TEST_NUM_SEQ;
const U4                     u4_g_ESI_MEM_RWC_PREP_TOUT = (U4)30000U * (U4)GPT_FRT_1US; /* 30 milliseconds */
#endif   /* BEV Diag provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_ESInspectCfgNuoDisabled(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_ESInspectCfgNuoDisabled(void)
{
    U4                 u4_t_km;
    U4                 u4_t_key;

    U1                 u1_t_nvm_chk;
    U1                 u1_t_nuo_di;

    /* ----------------------------------------------------------------------------------------- */
    /* WARNING :                                                                                 */
    /* ----------------------------------------------------------------------------------------- */
    /* If Odo is used to disable NvM update operation, DO NOT disable odo increment by           */
    /* u1_g_ESInspectNuoDisabled().                                                              */
    /*                                                                                           */
    /* Following implementation shall be used in MET-ECU. Other than MET-ECU, use other aging    */
    /* condition.                                                                                */
    /* ----------------------------------------------------------------------------------------- */
    u1_t_nuo_di = (U1)0U;
    u4_t_km     = (U4)U4_MAX;
    (void)u1_g_OdoKm(&u4_t_km);
    if(u4_t_km == (U4)0U){

        u4_t_key     = (U4)0U;
        u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_OXDC_BA_NUO_DI, &u4_t_key);
        if((u1_t_nvm_chk <  (U1)NVMC_STATUS_KIND_NG ) &&
           (u1_t_nvm_chk != (U1)NVMC_STATUS_ERRCOMP ) &&
           (u1_t_nvm_chk != (U1)NVMC_STATUS_CACHE_NG) &&
           (u4_t_key     == (U4)ESI_NUO_DI_KEYWORD  )){

            u1_t_nuo_di = (U1)ES_INSPECT_MDBF_NUO_DI;
        }
    }

    return(u1_t_nuo_di);
}
/*===================================================================================================================================*/
/*  void    vd_g_ESInspectCfgInit(const U1 u1_a_MD, const U1 u1_a_BON_INIT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ESInspectCfgInit(const U1 u1_a_MD, const U1 u1_a_BON_INIT)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* If u1_a_BON_INIT == TRUE, vd_g_ESInspectCfgInit is invoked at vd_g_ESInspectBonInit.            */
    /* If u1_a_BON_INIT != TRUE, vd_g_ESInspectCfgInit is invoked at vd_g_ESInspectRstwkInit.          */
    /* u1_a_MD is defined in es_inspect.h as #define ES_INSPECT_MD_XXX.                                */
    /* ----------------------------------------------------------------------------------------------- */
#if 0    /* BEV Diag provisionally */
    vd_g_ESIMemTestInit(u1_a_MD);
    vd_g_ESINvmrInit(u1_a_MD);
    vd_g_ESISscInit();
#endif   /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_ESInspectCfgDeInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ESInspectCfgDeInit(void)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* vd_g_ESInspectCfgDeInit is invoked at vd_g_ESInspectMainTask.                                   */
    /*                                                                                                 */
    /* Invocation order :                                                                              */
    /* 1. vd_g_ESInsepctCfgMainStart  if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /* 2. [es_inspect mode transition]                                                                 */
    /* 3. vd_g_ESInsepctCfgMainFinish if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /*    vd_g_ESInspectCfgDeInit     if the return of u1_g_ESInspectMdchk >= ES_INSPECT_NUM_MD        */
    /* ----------------------------------------------------------------------------------------------- */
#if 0    /* BEV Diag provisionally */
    vd_g_ESIMemTestDeInit();
    vd_g_ESINvmrDeInit();
#endif   /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_ESInsepctCfgMainStart(const U1 u1_a_MD, const U1 u1_a_NUO_DI, const U2 u2_a_ELPSD)                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ESInsepctCfgMainStart(const U1 u1_a_MD, const U1 u1_a_NUO_DI, const U2 u2_a_ELPSD)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* vd_g_ESInsepctCfgMainStart is invoked at vd_g_ESInspectMainTask.                                */
    /* u1_a_MD is defined in es_inspect.h as #define ES_INSPECT_MD_XXX.                                */
    /*                                                                                                 */
    /* Invocation order :                                                                              */
    /* 1. vd_g_ESInsepctCfgMainStart  if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /* 2. [es_inspect mode transition]                                                                 */
    /* 3. vd_g_ESInsepctCfgMainFinish if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /*    vd_g_ESInspectCfgDeInit     if the return of u1_g_ESInspectMdchk >= ES_INSPECT_NUM_MD        */
    /* ----------------------------------------------------------------------------------------------- */
#if 0    /* BEV Diag provisionally */
    vd_g_ESINvmrMainStart(u1_a_MD);
#endif   /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  void    vd_g_ESInsepctCfgMainFinish(const U1 u1_a_MD, const U2 u2_a_ELPSD)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ESInsepctCfgMainFinish(const U1 u1_a_MD, const U1 u1_a_NUO_DI, const U2 u2_a_ELPSD)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* vd_g_ESInsepctCfgMainFinish is invoked at vd_g_ESInspectMainTask.                               */
    /* u1_a_MD is defined in es_inspect.h as #define ES_INSPECT_MD_XXX.                                */
    /*                                                                                                 */
    /*                                                                                                 */
    /* Invocation order :                                                                              */
    /* 1. vd_g_ESInsepctCfgMainStart  if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /* 2. [es_inspect mode transition]                                                                 */
    /* 3. vd_g_ESInsepctCfgMainFinish if the return of u1_g_ESInspectMdchk <  ES_INSPECT_NUM_MD        */
    /*    vd_g_ESInspectCfgDeInit     if the return of u1_g_ESInspectMdchk >= ES_INSPECT_NUM_MD        */
    /* ----------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  vd_g_ESInsepctCfgDmaStop(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ESInsepctCfgDmaStop(void)
{
#if 0    /* BEV Diag provisionally */
    /* Lcom */
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_2_RX);
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_0_RX);
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_2_TX);
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_0_TX);
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_1_RX);
    vd_g_DmaDisCh((U1)DMA_CH_CSIG_1_TX);

    /* Sound */
    /* No processing required */
#endif   /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    10/31/2019  TN       New.                                                                                               */
/*  1.1.0    11/28/2019  TN       es_inspect.c v1.0.0 -> v1.1.0.                                                                     */
/*  1.2.0    12/ 3/2019  TN       es_inspect.c v1.1.0 -> v1.2.0.                                                                     */
/*  1.3.0     1/ 9/2020  TN       es_inspect.c v1.2.0 -> v1.3.0.                                                                     */
/*  1.4.0     3/20/2020  TN       es_inspect.c v1.3.0 -> v1.4.0.                                                                     */
/*  1.5.0     4/ 2/2020  TN       es_inspect.c v1.4.0 -> v1.5.0.                                                                     */
/*  1.6.0     4/22/2024  TK       es_inspect.c v1.5.0 -> v1.6.0.                                                                     */
/*  1.7.0     3/12/2026  SI       es_inspect.c v1.6.0 -> v1.7.0.                                                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B CVR                                                                            */
/*  19PFv3-1 12/26/2024  GM       Delete esi_adc module                                                                              */
/*  BEV-1     3/12/2026  SI       Configured for BEV E-CV                                                                            */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*  * TK   = Toru Kamishina,  DENSO-TECHNO                                                                                           */
/*  * GM   = Glen Monteposo, DENSO-TECHNO                                                                                            */
/*  * SI   = Shugo Ichinose, DENSO-TECHNO                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
