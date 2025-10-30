/* 1.8.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  IO Hardware Abstraction Analog Digital Converter                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_CFG_C_MAJOR                     (1)
#define IOHW_ADC_CFG_C_MINOR                     (8)
#define IOHW_ADC_CFG_C_PATCH                     (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "iohw_adc_cfg_private.h"

#include "memfill_u4.h"
#include "Adc.h"
#include "Vcc.h"                      /* ehvm_vcc_transmit(...) */
#include "ehvm_cfg_pe0_vm0.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((IOHW_ADC_CFG_C_MAJOR != IOHW_ADC_CFG_H_MAJOR) || \
     (IOHW_ADC_CFG_C_MINOR != IOHW_ADC_CFG_H_MINOR) || \
     (IOHW_ADC_CFG_C_PATCH != IOHW_ADC_CFG_H_PATCH))
#error "iohw_adc_cfg.c and iohw_adc_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((IOHW_ADC_CFG_C_MAJOR != IOHW_ADC_CHANNEL_H_MAJOR) || \
     (IOHW_ADC_CFG_C_MINOR != IOHW_ADC_CHANNEL_H_MINOR) || \
     (IOHW_ADC_CFG_C_PATCH != IOHW_ADC_CHANNEL_H_PATCH))
#error "iohw_adc_cfg.c and iohw_adc_channel.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_MAIN_TICK                       (10U)   /* 10 milliseconds */
/* #define IOHW_ADC_CYCL_TICK                    (5U)        5 milliseconds */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef ADC_CFG_H

#define ADC_NUM_GR                               (ADC_CFG_GRP_SIZE)
#define ADC_GR_UN_0                              (ADC_GR_0)
#define ADC_GR_UN_1                              (ADC_GR_1)
#define ADC_GR_UN_2                              (ADC_GR_2)

#define ADC_NUM_CH                               (ADC_CFG_GRP00_CNV_CH_SIZE + ADC_CFG_GRP01_CNV_CH_SIZE + ADC_CFG_GRP02_CNV_CH_SIZE)
#define ADC_UN_0_NUM_CH                          (ADC_CFG_GRP00_CNV_CH_SIZE)
#define ADC_UN_1_NUM_CH                          (ADC_CFG_GRP01_CNV_CH_SIZE)
#define ADC_UN_2_NUM_CH                          (ADC_CFG_GRP02_CNV_CH_SIZE)

#endif /* #ifdef ADC_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define IOHW_ADC_LV_NUM_WORD                     ((ADC_NUM_CH >> 1U) + (ADC_NUM_CH & 0x01U))
static U4                u4_sp_iohw_adc_lv[IOHW_ADC_LV_NUM_WORD * IOHW_ADC_LV_NUM_BUF];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata=".IOHW_ADC_RODATA_CONST"

/* const U4                 u4_g_IOHW_ADC_IRQ_PLVL     = (U4)INT_HNDLR_IRQPL_OST_00; */

U4 * const               u4p_gp_IOHW_ADC_LV[IOHW_ADC_LV_NUM_BUF] = {
    &u4_sp_iohw_adc_lv[IOHW_ADC_LV_NUM_WORD * IOHW_ADC_LV_BUF_0],
    &u4_sp_iohw_adc_lv[IOHW_ADC_LV_NUM_WORD * IOHW_ADC_LV_BUF_1],
    &u4_sp_iohw_adc_lv[IOHW_ADC_LV_NUM_WORD * IOHW_ADC_LV_BUF_2]
};
const U2                 u2_g_IOHW_ADC_LV_MAX       = (U2)IOHW_ADC_LV_MAX;
const U1                 u1_g_IOHW_ADC_NUM_CH       = (U1)ADC_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                 u2_g_IOHW_ADC_SEQ_FIN_TOUT = (U2)100U / (U2)IOHW_ADC_MAIN_TICK; /* 100ms */

#define IOHW_ADC_NUM_CVST                        (1U)
const U1                 u1_g_IOHW_ADC_NUM_CVST     = (U1)IOHW_ADC_NUM_CVST;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* #if (__IOHW_ADC_CYCL_SEQ_ENA__ == 1)                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* const U2                 u2_g_IOHW_ADC_CYCL_TM_MAX  = (U2)10U / (U2)IOHW_ADC_CYCL_TICK;                                           */
/*                                                                                                                                   */
/* #define IOHW_ADC_NUM_CYCLTK                      (2U)                                                                             */
/*                                                                                                                                   */
/* DO NOT set "vdp_PTR_NA" to "fp_vd_TK"                                                                                             */
/* ST_IOHW_ADC_CYCLTK       st_gp_IOHW_ADC_CYCLTK[IOHW_ADC_NUM_CYCLTK] = {                                                           */
/*     {&vd_g_IoHwAdcCvstStart,       (U2)0U / (U2)IOHW_ADC_CYCL_TICK},                                                              */
/*     {&vd_g_IoHwAdcCvstFinish,      (U2)5U / (U2)IOHW_ADC_CYCL_TICK}                                                               */
/* };                                                                                                                                */
/* const U2                 u2_g_IOHW_ADC_NUM_CYCLTK   = (U2)IOHW_ADC_NUM_CYCLTK;                                                    */
/* #endif                                                                                                                            */

#pragma ghs section rodata=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".IOHW_ADC_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCfgInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCfgInit(void)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* u4_sp_iohw_adc_lv[] is initialized to IOHW_ADC_LV_U4_UNKNWN in vd_g_IoHwAdcInit.                */
    /* Thus, u4_sp_iohw_adc_lv[] doesn't need to be initialized at here.                               */
    /* ----------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCfgMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCfgMainTask(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCfgCvstInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCfgCvstInit(void)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* vd_g_IoHwAdcCfgCvstInit is invoked with u4_g_IoHwAdcCfg_DI if A/D conversion sequence is        */
    /* aborted or if u1_a_INIT is passed with TRUE in vd_g_IoHwAdcSeqAct or vd_g_IoHwAdcCyclSeqAct.    */
    /*                                                                                                 */
    /* The interrupts and timer expect to be disabled.                                                 */
    /* ----------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCfgCvstStart(const U1 u1_a_CVST, const U1 u1_a_LV_IDX)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCfgCvstStart(const U1 u1_a_CVST, const U1 u1_a_LV_IDX)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* u1_a_CVST is already tested if the value is less than u1_g_IOHW_ADC_NUM_CVST or not.            */
    /* vd_g_IoHwAdcCfgCvstStart is not called if u1_a_CVST is equal to or geater than                  */
    /* u1_g_IOHW_ADC_NUM_CVST. Thus, no need to test u1_a_CVST.                                        */
    /*                                                                                                 */
    /* u1_a_LV_IDX is already tested if the value is less than IOHW_ADC_LV_NUM_BUF or not.             */
    /* vd_g_IoHwAdcCfgCvstStart is not called if u1_a_LV_IDX is equal to or geater than                */
    /* IOHW_ADC_LV_NUM_BUF. Thus, no need to test u1_a_LV_IDX.                                         */
    /* ----------------------------------------------------------------------------------------------- */

    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* u4p_gp_IOHW_ADC_LV[u1_a_LV_IDX]([]) shall be initialized to IOHW_ADC_LV_UNKNWN(0xffff)          */
    /* before A/D conversion is started.                                                               */
    /*                                                                                                 */
    /* The buffer size to be initialized shall be designed to meet time performance requirement.       */
    /* ----------------------------------------------------------------------------------------------- */

    vd_g_MemfillU4(u4p_gp_IOHW_ADC_LV[u1_a_LV_IDX], (U4)IOHW_ADC_LV_U4_UNKNWN, (U4)IOHW_ADC_LV_NUM_WORD);

    /* FUNC(void, ADC_CODE) Adc_StartGroupConversion(VAR(Adc_GroupType, ADC_VAR_INIT) Group); */

    Adc_StartGroupConversion(ADC_GR_UN_0);
    Adc_StartGroupConversion(ADC_GR_UN_1);
    Adc_StartGroupConversion(ADC_GR_UN_2);
}
/*===================================================================================================================================*/
/*  void    vd_g_IoHwAdcCfgCvstFinish(const U1 u1_a_CVST, const U1 u1_a_LV_IDX)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IoHwAdcCfgCvstFinish(const U1 u1_a_CVST, const U1 u1_a_LV_IDX)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* u1_a_CVST is already tested if the value is less than u1_g_IOHW_ADC_NUM_CVST or not.            */
    /* vd_g_IoHwAdcCfgCvstFinish is not called if u1_a_CVST is equal to or geater than                 */
    /* u1_g_IOHW_ADC_NUM_CVST. Thus, no need to test u1_a_CVST.                                        */
    /*                                                                                                 */
    /* u1_a_LV_IDX is already tested if the value is less than IOHW_ADC_LV_NUM_BUF or not.             */
    /* vd_g_IoHwAdcCfgCvstFinish is not called if u1_a_LV_IDX is equal to or geater than               */
    /* IOHW_ADC_LV_NUM_BUF. Thus, no need to test u1_a_LV_IDX.                                         */
    /* ----------------------------------------------------------------------------------------------- */

    /* FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus(VAR(Adc_GroupType, ADC_VAR_INIT) Group); */
    /* typedef enum {                                                                             */
    /*     ADC_IDLE,                                                                              */
    /*     ADC_BUSY,                                                                              */
    /*     ADC_COMPLETED,                                                                         */
    /*     ADC_STREAM_COMPLETED                                                                   */
    /* } Adc_StatusType;                                                                          */
    /* FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup(VAR(Adc_GroupType, ADC_VAR_INIT) Group,       */
    /*                        P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_VAR_INIT) DataBufferPtr);  */
    /* typedef sint16   Adc_ValueGroupType;                                                       */

    U4 *                        u4_tp_vcc_tx;
    Adc_ValueGroupType *        u2_tp_lv_arch;
    Adc_StatusType              en_t_rslt;

    u4_tp_vcc_tx  = u4p_gp_IOHW_ADC_LV[u1_a_LV_IDX];
    u2_tp_lv_arch = (Adc_ValueGroupType *)u4_tp_vcc_tx;
    en_t_rslt     = Adc_GetGroupStatus(ADC_GR_UN_0);
    if(en_t_rslt == ADC_STREAM_COMPLETED){
        (void)Adc_ReadGroup( ADC_GR_UN_0, &u2_tp_lv_arch[0] );
    }

    en_t_rslt     = Adc_GetGroupStatus(ADC_GR_UN_1);
    if(en_t_rslt == ADC_STREAM_COMPLETED){
        (void)Adc_ReadGroup( ADC_GR_UN_1, &u2_tp_lv_arch[ADC_UN_0_NUM_CH] );
    }

    en_t_rslt     = Adc_GetGroupStatus(ADC_GR_UN_2);
    if(en_t_rslt == ADC_STREAM_COMPLETED){
        (void)Adc_ReadGroup( ADC_GR_UN_2, &u2_tp_lv_arch[ADC_UN_0_NUM_CH + ADC_UN_1_NUM_CH] );
    }

    (void)ehvm_vcc_transmit(EHVM_TX_VCCID_VCC_IOHWAD_DATA_TX_VM0,
                            u4_tp_vcc_tx, ((U4)IOHW_ADC_LV_NUM_WORD << 2U));
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
/*  1.0.0     3/26/2015  TN       New.                                                                                               */
/*  1.1.0     4/ 2/2015  TN       vd_g_IoHwAdcCfgPreTask was implemented.                                                            */
/*  1.1.1     6/24/2015  TN       iohw_adc.c v1.1.0 -> v1.1.1.                                                                       */
/*  1.2.0     6/25/2015  TN       iohw_adc.c v1.1.1 -> v1.2.0.                                                                       */
/*  1.3.0     7/30/2015  TN       iohw_adc.c v1.2.0 -> v1.3.0.                                                                       */
/*  1.4.0    10/28/2015  TN       iohw_adc.c v1.3.0 -> v1.4.0.                                                                       */
/*  1.5.0     1/15/2016  TN       iohw_adc.c v1.4.0 -> v1.5.0.                                                                       */
/*  1.6.0    10/ 3/2017  TN       iohw_adc.c v1.5.0 -> v1.6.0.                                                                       */
/*  1.7.0    10/13/2017  TN       iohw_adc.c v1.6.0 -> v1.7.0.                                                                       */
/*  1.8.0    12/15/2017  TN       iohw_adc.c v1.7.0 -> v1.8.0.                                                                       */
/*  1.8.1     9/ 7/2021  TN       iohw_adc.c v1.8.0 -> v1.8.1.                                                                       */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
