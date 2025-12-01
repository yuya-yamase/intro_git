/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : Timer Array Unit J                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_DRV_J32_C_MAJOR                      (1)
#define GPT_DRV_J32_C_MINOR                      (0)
#define GPT_DRV_J32_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_j32_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GPT_DRV_J32_C_MAJOR != GPT_DRV_J32_H_MAJOR) || \
     (GPT_DRV_J32_C_MINOR != GPT_DRV_J32_H_MINOR) || \
     (GPT_DRV_J32_C_PATCH != GPT_DRV_J32_H_PATCH))
#error "gpt_drv_j32.c and gpt_drv_j32.h : source and header files are inconsistent!"
#endif

#if ((GPT_DRV_J32_C_MAJOR != GPT_DRV_J32_CFG_H_MAJOR) || \
     (GPT_DRV_J32_C_MINOR != GPT_DRV_J32_CFG_H_MINOR) || \
     (GPT_DRV_J32_C_PATCH != GPT_DRV_J32_CFG_H_PATCH))
#error "gpt_drv_j32.c and gpt_drv_j32_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TRUE != 1) || (FALSE != 0))
#error "gpt_drv_j32.c : TRUE shall be "1" and FALSE shall be "0"."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_J32_RA_HALF_TPS                      (0x0090U >> 1)
#define GPT_J32_RA_BYTE_BRS                      (0x0094U)

/* #define GPT_J32_RA_WORD_CDR_CH_0                 (0x0000U >> 2) */
#define GPT_J32_RA_WORD_CNT_CH_0                 (0x0010U >> 2)
#define GPT_J32_RA_HALF_CMOR_CH_0                (0x0080U >> 1)
#define GPT_J32_RA_BYTE_CMUR_CH_0                (0x0020U)
#define GPT_J32_RA_BYTE_CSR_CH_0                 (0x0030U)
#define GPT_J32_RA_BYTE_CSC_CH_0                 (0x0040U)

#define GPT_J32_RA_BYTE_TS                       (0x0054U)
#define GPT_J32_RA_BYTE_TE                       (0x0050U)
#define GPT_J32_RA_BYTE_TT                       (0x0058U)

#define GPT_J32_RA_BYTE_TOE                      (0x0060U)
#define GPT_J32_RA_BYTE_TO                       (0x005cU)
#define GPT_J32_RA_BYTE_TOM                      (0x0098U)
#define GPT_J32_RA_BYTE_TOC                      (0x009cU)
#define GPT_J32_RA_BYTE_TOL                      (0x0064U)

#define GPT_J32_RA_BYTE_RDE                      (0x00a0U)
#define GPT_J32_RA_BYTE_RDM                      (0x00a4U)
#define GPT_J32_RA_BYTE_RDT                      (0x0068U)
#define GPT_J32_RA_BYTE_RSF                      (0x006cU)

#define GPT_J32_CHBIT_BY_UNIT                    (0x0fU)

#define GPT_J32_MDCTRL_BIT_CONST                 (0xcfdfU)

#define GPT_J32_CSR_BIT_OVF                      (0x01U)
#define GPT_J32_CSC_BIT_CLOV                     (0x01U)

#define GPT_J32_CH_TO_UNIT                       (2U)
#define GPT_J32_CH_TO_CH_BY_UNIT                 (0x00000003U)

#define GPT_J32_START_NUM_CHK                    (4U)
#define GPT_J32_START_CHK_TOC                    (0U)
#define GPT_J32_START_CHK_TOM                    (1U)
#define GPT_J32_START_CHK_RDE                    (2U)
#define GPT_J32_START_CHK_RDM                    (3U)

#define GPT_J32_RO_HALF_LSR_CH                   (1U)
#define GPT_J32_RO_BYTE_LSR_CH                   (2U)

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
#define RH850_G4MH_SYNCP       /* static inline void  vd_s_SYNCP(void)                                   */
#define RH850_G4MH_SYNCP_BYTE  /* static inline void  vd_s_SYNCP_B(const volatile U1 * const u1_ap_RDBK) */
#define RH850_G4MH_RDBK_BYTE   /* static inline void  vd_s_RDBK_B(const volatile U1 * const u1_ap_RDBK)  */
#include "rh850_g4mh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".GPT_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32Init(void)
{
    volatile U2 *       u2_tp_half;
    volatile U1 *       u1_tp_byte;

    const U2 *          u2_tp_MDCTRL;

    volatile U4         u4_t_gli;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U4                  u4_t_irq_sta;
    U4                  u4_t_irq_end;

    U4                  u4_t_offset;
    U4                  u4_t_cfg;

    for(u4_t_unit = (U4)0U; u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT; u4_t_unit++){

        u2_tp_half = (volatile U2 *)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        u1_tp_byte = (volatile U1 *)u2_tp_half;

        u4_t_irq_sta = (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        u4_t_irq_end = u4_t_irq_sta + (U4)GPT_J32_NUM_CH_BY_UNIT;

        u4_t_gli = u4_g_IRQ_DI();

        do{
            vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_sta, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            u4_t_irq_sta++;
        }
        while(u4_t_irq_sta < u4_t_irq_end);

        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TT], (U1)GPT_J32_CHBIT_BY_UNIT);
        vd_s_RDBK_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);

        vd_g_IRQ_EI(u4_t_gli);

        u4_t_cfg = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4_srcclk;
     /* vd_REG_U2_WRITE(u2_tp_half[GPT_J32_RA_HALF_TPS],  (U2)(u4_t_cfg >> GPT_J32_SRCCLK_LSB_TPS)); QAC Warning#2985 */
        vd_REG_U2_WRITE(u2_tp_half[GPT_J32_RA_HALF_TPS],  (U2)u4_t_cfg                            );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_BRS],  (U1)(u4_t_cfg >> GPT_J32_SRCCLK_LSB_BRS));

        u4_t_cfg = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4_output;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TO],   (U1)0x00U                               );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOE],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOE));
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOC],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOC));
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOM],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOM));
     /* vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOL],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOL)); QAC Waring#2985 */
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOL],  (U1)u4_t_cfg                            );

        u4_t_cfg = (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_reload;
     /* vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDE],  (U1)(u4_t_cfg >> GPT_J32_RELOAD_LSB_RDE)); QAC Waring#2985 */
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDE],  (U1)u4_t_cfg                            );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDM],  (U1)(u4_t_cfg >> GPT_J32_RELOAD_LSB_RDM));

        u2_tp_MDCTRL = &(st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2p_mdctrl[0]);
        for(u4_t_ch = (U4)0U; u4_t_ch < (U4)GPT_J32_NUM_CH_BY_UNIT; u4_t_ch++){

            u4_t_offset = (U4)GPT_J32_RA_HALF_CMOR_CH_0 + (u4_t_ch << GPT_J32_RO_HALF_LSR_CH);
            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],  u2_tp_MDCTRL[u4_t_ch]);

            u4_t_offset = (U4)GPT_J32_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_J32_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],  (U1)0x00U            );
        }

        vd_s_RDBK_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);
    }
    vd_s_SYNCP();
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32DeInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32DeInit(void)
{
    volatile U1 *       u1_tp_byte;

    volatile U4         u4_t_gli;

    U4                  u4_t_unit;

    U4                  u4_t_irq_sta;
    U4                  u4_t_irq_end;

    for(u4_t_unit = (U4)0U; u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT; u4_t_unit++){

        u1_tp_byte = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;

        u4_t_irq_sta = (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        u4_t_irq_end = u4_t_irq_sta + (U4)GPT_J32_NUM_CH_BY_UNIT;

        u4_t_gli = u4_g_IRQ_DI();

        do{
            vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_sta, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            u4_t_irq_sta++;
        }
        while(u4_t_irq_sta < u4_t_irq_end);

        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TT],  (U1)GPT_J32_CHBIT_BY_UNIT);

        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOE], (U1)0x00U);
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TO],  (U1)0x00U);
        vd_s_RDBK_B(&u1_tp_byte[GPT_J32_RA_BYTE_TO]);

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  U4      u4_g_Gpt_J32GetTimeElapsed(const U1 u1_a_J32_CH, U4 * u4_ap_j32stamp)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_Gpt_J32GetTimeElapsed(const U1 u1_a_J32_CH, U4 * u4_ap_j32stamp)
{
    volatile U4 *       u4_tp_word;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U4                  u4_t_elapsed;

    u4_t_elapsed = (U4)U4_MAX;
    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){

        u4_t_ch = ((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT) + (U4)GPT_J32_RA_WORD_CNT_CH_0;

        u4_tp_word   = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        u4_t_elapsed = u4_REG_READ(u4_tp_word[u4_t_ch]);

        if(u4_ap_j32stamp != vdp_PTR_NA){
            u4_ap_j32stamp[GPT_J32_TMELPSD_CRRNT] = u4_t_elapsed;
            u4_t_elapsed -= u4_ap_j32stamp[GPT_J32_TMELPSD_BASE];
        }
    }

    return(u4_t_elapsed);
}
/*===================================================================================================================================*/
/*  U4      u4_g_Gpt_J32GetTimeCaptured(const U1 u1_a_J32_CH, U4 * u4_ap_j32stamp)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_Gpt_J32GetTimeCaptured(const U1 u1_a_J32_CH, U4 * u4_ap_j32stamp)
{
    volatile U4 *       u4_tp_word;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U4                  u4_t_elapsed;

    u4_t_elapsed = (U4)U4_MAX;
    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){

     /* u4_t_ch = ((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT) + (U4)GPT_J32_RA_WORD_CDR_CH_0; QAC Warning#2985 */
        u4_t_ch = (U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT;

        u4_tp_word   = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        u4_t_elapsed = u4_REG_READ(u4_tp_word[u4_t_ch]);

         if(u4_ap_j32stamp != vdp_PTR_NA){
            u4_ap_j32stamp[GPT_J32_TMELPSD_CRRNT] = u4_t_elapsed;
            u4_t_elapsed -= u4_ap_j32stamp[GPT_J32_TMELPSD_BASE];
        }
    }

    return(u4_t_elapsed);
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32Start(const U1 u1_a_J32_CH, const U4 * u4_ap_START)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32Start(const U1 u1_a_J32_CH, const U4 * u4_ap_START)
{
    volatile U4 *       u4_tp_word;
    volatile U2 *       u2_tp_half;
    volatile U1 *       u1_tp_byte;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U4                  u4_t_irq_ch;
    U4                  u4_t_cfg;
    U4                  u4_t_offset;
    U4                  u4_t_bit;
    U4                  u4_t_period;

    U2                  u2_t_chbit;
    U2                  u2_tp_chk[GPT_J32_START_NUM_CHK];
    U2                  u2_t_mdctrl;
    U2                  u2_t_stbit;
    U2                  u2_t_start;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){

        u4_t_ch      = (U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT;
        u2_t_chbit   = (U2)0x0001U << u4_t_ch;

        u4_t_irq_ch  = (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch + u4_t_ch;

        u4_tp_word   = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        u2_tp_half   = (volatile U2 *)u4_tp_word;
        u1_tp_byte   = (volatile U1 *)u4_tp_word;

        u4_t_cfg     = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4_srcclk;
     /* vd_REG_U2_WRITE(u2_tp_half[GPT_J32_RA_HALF_TPS],  (U2)(u4_t_cfg >> GPT_J32_SRCCLK_LSB_TPS)); QAC Warning#2985 */
        vd_REG_U2_WRITE(u2_tp_half[GPT_J32_RA_HALF_TPS],  (U2)u4_t_cfg                            );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_BRS],  (U1)(u4_t_cfg >> GPT_J32_SRCCLK_LSB_BRS));

        u4_t_cfg     = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4_output;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOE],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOE));
     /* vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOL],  (U1)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOL)); QAC Warning#2985 */
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOL],  (U1)u4_t_cfg                            );

        u2_tp_chk[GPT_J32_START_CHK_TOC] = (U2)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOC);
        u2_tp_chk[GPT_J32_START_CHK_TOM] = (U2)(u4_t_cfg >> GPT_J32_OUTPUT_LSB_TOM);

        u4_t_cfg     = (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_reload;
     /* u2_tp_chk[GPT_J32_START_CHK_RDE] = (U2)(u4_t_cfg >> GPT_J32_RELOAD_LSB_RDE);  QAC Warning#2985 */
        u2_tp_chk[GPT_J32_START_CHK_RDE] = (U2)u4_t_cfg;
        u2_tp_chk[GPT_J32_START_CHK_RDM] = (U2)(u4_t_cfg >> GPT_J32_RELOAD_LSB_RDM);

        u2_t_start   = (U2)u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_TE]) ^ u2_t_chbit;
        u2_t_start  |= ((U2)u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_TOC]) ^ u2_tp_chk[GPT_J32_START_CHK_TOC]);
        u2_t_start  |= ((U2)u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_TOM]) ^ u2_tp_chk[GPT_J32_START_CHK_TOM]);
        u2_t_start  |= ((U2)u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_RDE]) ^ u2_tp_chk[GPT_J32_START_CHK_RDE]);
        u2_t_start  |= ((U2)u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_RDM]) ^ u2_tp_chk[GPT_J32_START_CHK_RDM]);
        u2_t_start  &= u2_t_chbit;

        u4_t_offset  = (U4)GPT_J32_RA_HALF_CMOR_CH_0 + (u4_t_ch << GPT_J32_RO_HALF_LSR_CH);
        u2_t_mdctrl  = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2p_mdctrl[u4_t_ch] & (U2)GPT_J32_MDCTRL_BIT_CONST;
        u2_t_start  |= ((u2_REG_READ(u2_tp_half[u4_t_offset]) ^ u2_t_mdctrl) & (U2)GPT_J32_MDCTRL_BIT_CONST);

        u4_t_bit     = u4_ap_START[GPT_J32_START_CTRL] & (U4)GPT_J32_START_CTRL_BIT_TRG_ST;
        if(u4_t_bit != (U4)0U){
            u2_t_stbit = u2_t_chbit;
        }
        else{
            u2_t_stbit = (U2)0U;
        }

        if(u2_t_start != (U2)0U){

            vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TT],  (U1)u2_t_chbit);
            vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);

            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOC],  (U1)u2_tp_chk[GPT_J32_START_CHK_TOC]);
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TOM],  (U1)u2_tp_chk[GPT_J32_START_CHK_TOM]);
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDE],  (U1)u2_tp_chk[GPT_J32_START_CHK_RDE]);
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDM],  (U1)u2_tp_chk[GPT_J32_START_CHK_RDM]);

            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],         u2_t_mdctrl   );

            u4_t_bit = u4_ap_START[GPT_J32_START_CTRL] & (U4)GPT_J32_START_CTRL_BIT_ELVL;
            u4_t_offset = (U4)GPT_J32_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_J32_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],         (U1)u4_t_bit  );

            u4_t_period = u4_ap_START[GPT_J32_START_PERI] - (U4)1U;
            vd_REG_U4_WRITE(u4_tp_word[u4_t_ch],             u4_t_period   );

            u4_t_offset = (U4)GPT_J32_RA_BYTE_CSC_CH_0 + (u4_t_ch << GPT_J32_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],         (U1)TRUE      );

            u4_t_bit = u4_ap_START[GPT_J32_START_CTRL] & (U4)GPT_J32_START_CTRL_BIT_IRQ_EN;
            if(u4_t_bit != (U4)0){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }

            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TS],  (U1)u2_t_stbit);
            vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);
        }
        else{

            u4_t_bit = u4_ap_START[GPT_J32_START_CTRL] & (U4)GPT_J32_START_CTRL_BIT_ELVL;
            u4_t_offset = (U4)GPT_J32_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_J32_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],         (U1)u4_t_bit  );

            u2_t_stbit  = st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_reload & u2_t_stbit;
            u4_t_period = u4_ap_START[GPT_J32_START_PERI] - (U4)1U;
            vd_REG_U4_WRITE(u4_tp_word[u4_t_ch],             u4_t_period   );
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDT], (U1)u2_t_stbit);
            vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_RSF]);

            u4_t_bit = u4_ap_START[GPT_J32_START_CTRL] & ((U4)GPT_J32_START_CTRL_BIT_IRQ_EN | (U4)GPT_J32_START_CTRL_BIT_IRQ_CL);
            if(u4_t_bit == ((U4)GPT_J32_START_CTRL_BIT_IRQ_EN | (U4)GPT_J32_START_CTRL_BIT_IRQ_CL)){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else if(u4_t_bit == (U4)GPT_J32_START_CTRL_BIT_IRQ_EN){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32Stop(const U1 u1_a_J32_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32Stop(const U1 u1_a_J32_CH)
{
    volatile U1 *       u1_tp_byte;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U1                  u1_t_chbit;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){

        u4_t_ch     = (U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT;
        u1_t_chbit  = (U1)0x01 << u4_t_ch;

        u4_t_ch    += (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;

        vd_g_IntHndlrIRQCtrlCh((U2)u4_t_ch, (U1)0x00U);

        u1_tp_byte = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TT],   u1_t_chbit);
        vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32SyncStart(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32SyncStart(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)
{
    volatile U1 *       u1_tp_byte;

    U1                  u1_t_run;

    if(u1_a_J32_UNIT < u1_g_GPT_J32_NUM_UNIT){

        u1_tp_byte   = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u1_a_J32_UNIT].u4p_base;

        u1_t_run   = u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_TE]) & u1_a_J32_CHBIT;
        if(u1_t_run != u1_a_J32_CHBIT){
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TS],   u1_a_J32_CHBIT);
            vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);
        }
        else{
            vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_RDT],  u1_a_J32_CHBIT);
            vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_RSF]);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32SyncStop(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32SyncStop(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)
{
    volatile U1 *       u1_tp_byte;

    volatile U4         u4_t_gli;

    U2                  u2_t_lpcnt;
    U2                  u2_t_irq_ch;

    U1                  u1_t_chbit;
    U1                  u1_t_bit;

    if(u1_a_J32_UNIT < u1_g_GPT_J32_NUM_UNIT){

        u1_tp_byte   = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u1_a_J32_UNIT].u4p_base;
        u1_t_chbit   = u1_a_J32_CHBIT;
        u2_t_irq_ch  = st_gp_GPT_J32_UNIT_CFG[u1_a_J32_UNIT].u2_irq_ch;
         
        u4_t_gli = u4_g_IRQ_DI();

        u2_t_lpcnt = (U2)0U;
        while(u1_t_chbit != (U1)0U){

            u1_t_bit = u1_t_chbit & (U1)0x01;
            if(u1_t_bit != (U1)0U){
                vd_g_IntHndlrIRQCtrlCh(u2_t_irq_ch + u2_t_lpcnt, (U1)0x00U);
            }
            u1_t_chbit >>= 1;
            u2_t_lpcnt++;
        }

        vd_REG_U1_WRITE(u1_tp_byte[GPT_J32_RA_BYTE_TT],   u1_a_J32_CHBIT);
        vd_s_SYNCP_B(&u1_tp_byte[GPT_J32_RA_BYTE_TE]);

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_J32SyncReload(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_J32SyncReload(const U1 u1_a_J32_UNIT, const U1 u1_a_J32_CHBIT)
{
    volatile U1 *       u1_tp_byte;

    U1                  u1_t_chbit;
    U1                  u1_t_bit;
    U1                  u1_t_reload;

    u1_t_reload = (U1)FALSE;
    if(u1_a_J32_UNIT < u1_g_GPT_J32_NUM_UNIT){

        u1_tp_byte   = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u1_a_J32_UNIT].u4p_base;
        u1_t_chbit = (U1)st_gp_GPT_J32_UNIT_CFG[u1_a_J32_UNIT].u2_reload & u1_a_J32_CHBIT;
        u1_t_bit   = (u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_RSF]) ^ u1_t_chbit) & u1_t_chbit;
        if(u1_t_bit == u1_a_J32_CHBIT){
            u1_t_reload = (U1)TRUE;
        }
    }

    return(u1_t_reload);
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32EI(const U1 u1_a_J32_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32EI(const U1 u1_a_J32_CH)
{
    U4                  u4_t_unit;
    U4                  u4_t_irq_ch;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){
        u4_t_irq_ch = ((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT) + (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_J32DI(const U1 u1_a_J32_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_J32DI(const U1 u1_a_J32_CH)
{
    U4                  u4_t_unit;
    U4                  u4_t_irq_ch;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){
        u4_t_irq_ch = ((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT) + (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)0x00U);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_J32IRQst(const U1 u1_a_J32_CH, const U1 u1_a_W_CLR)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_J32IRQst(const U1 u1_a_J32_CH, const U1 u1_a_W_CLR)
{
    volatile U1 *       u1_tp_byte;

    U4                  u4_t_unit;
    U4                  u4_t_ch;
    U4                  u4_t_irq_ch;
    U1                  u1_t_ovf;

    U4                  u4_t_offset;
    U1                  u1_t_irqst;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){
        u4_t_irq_ch = ((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT) + (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        u1_t_irqst  = u1_g_IntHndlrIRQst((U2)u4_t_irq_ch, (U1)(u1_a_W_CLR & GPT_J32_IRQST_BIT_IRQ));

        u1_tp_byte  = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;

        u4_t_ch      = (U4)(((U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT ) << GPT_J32_RO_BYTE_LSR_CH);
        u4_t_offset = (U4)GPT_J32_RA_BYTE_CSR_CH_0 + u4_t_ch;
        u1_t_ovf = u1_REG_READ(u1_tp_byte[u4_t_offset]) & GPT_J32_CSR_BIT_OVF;

        if((u1_a_W_CLR & (U1)GPT_J32_IRQST_BIT_OVF) != 0){
            u4_t_offset = (U4)GPT_J32_RA_BYTE_CSC_CH_0 + u4_t_ch;
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],   (U1)GPT_J32_CSC_BIT_CLOV);
        }
        
        if(u1_t_ovf != (U1)0U){
            u1_t_irqst |= (U1)GPT_J32_IRQST_BIT_OVF;
        }
    }
    else{
        u1_t_irqst = (U1)0;
    }

    return(u1_t_irqst);
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_J32IRQenabled(const U1 u1_a_J32_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_J32IRQenabled(const U1 u1_a_J32_CH)
{
    volatile U1 *       u1_tp_byte;
    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U1                  u1_t_chbit;
    U1                  u1_t_irqen;
    U1                  u1_t_run;

    u4_t_unit = (U4)u1_a_J32_CH >> GPT_J32_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_J32_NUM_UNIT){

        u4_t_ch     = (U4)u1_a_J32_CH & (U4)GPT_J32_CH_TO_CH_BY_UNIT;
        u1_t_chbit  = (U1)0x01 << u4_t_ch;

        u4_t_ch    += (U4)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u2_irq_ch;
        u1_t_irqen  = u1_g_IntHndlrIRQenabled((U2)u4_t_ch);

        u1_tp_byte = (volatile U1 *)st_gp_GPT_J32_UNIT_CFG[u4_t_unit].u4p_base;
        u1_t_run   = u1_REG_READ(u1_tp_byte[GPT_J32_RA_BYTE_TE]) & u1_t_chbit;
        if(u1_t_run != (U1)0U){
            u1_t_irqen |= (U1)GPT_J32_IRQEN_BIT_CNTE;
        }
    }
    else{
        u1_t_irqen = (U1)0x00U;
    }

    return(u1_t_irqen);
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
/*  1.0.0    12/20/2021  TN       New.                                                                                               */
/*  1.0.1     5/26/2023  KM       Bug Fix : Changed the value of GPT_J32_MDCTRL_BIT_CONST.                                           */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KM   = Kazuyuki Makino, Denso                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
