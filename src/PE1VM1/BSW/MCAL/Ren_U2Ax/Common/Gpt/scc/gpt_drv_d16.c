/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : Timer Array Unit D                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_DRV_D16_C_MAJOR                      (1)
#define GPT_DRV_D16_C_MINOR                      (0)
#define GPT_DRV_D16_C_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_d16_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GPT_DRV_D16_C_MAJOR != GPT_DRV_D16_H_MAJOR) || \
     (GPT_DRV_D16_C_MINOR != GPT_DRV_D16_H_MINOR) || \
     (GPT_DRV_D16_C_PATCH != GPT_DRV_D16_H_PATCH))
#error "gpt_drv_d16.c and gpt_drv_d16.h : source and header files are inconsistent!"
#endif

#if ((GPT_DRV_D16_C_MAJOR != GPT_DRV_D16_CFG_H_MAJOR) || \
     (GPT_DRV_D16_C_MINOR != GPT_DRV_D16_CFG_H_MINOR) || \
     (GPT_DRV_D16_C_PATCH != GPT_DRV_D16_CFG_H_PATCH))
#error "gpt_drv_d16.c and gpt_drv_d16_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TRUE != 1) || (FALSE != 0))
#error "gpt_drv_d16.c : TRUE shall be "1" and FALSE shall be "0"."
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_RA_HALF_TPS                      (0x0240U >> 1)
#define GPT_D16_RA_BYTE_BRS                      (0x0244U)

/* #define GPT_D16_RA_HALF_CDR_CH_0                 (0x0000U >> 1) */
#define GPT_D16_RA_HALF_CNT_CH_0                 (0x0080U >> 1)
#define GPT_D16_RA_HALF_CMOR_CH_0                (0x0200U >> 1)
#define GPT_D16_RA_BYTE_CMUR_CH_0                (0x00c0U)
#define GPT_D16_RA_BYTE_CSR_CH_0                 (0x0140U)
#define GPT_D16_RA_BYTE_CSC_CH_0                 (0x0180U)

#define GPT_D16_RA_HALF_TS                       (0x01c4U >> 1)
#define GPT_D16_RA_HALF_TE                       (0x01c0U >> 1)
#define GPT_D16_RA_HALF_TT                       (0x01c8U >> 1)

#define GPT_D16_RA_HALF_TOE                      (0x005cU >> 1)
#define GPT_D16_RA_HALF_TO                       (0x0058U >> 1)
#define GPT_D16_RA_HALF_TOM                      (0x0248U >> 1)
#define GPT_D16_RA_HALF_TOC                      (0x024cU >> 1)
#define GPT_D16_RA_HALF_TOL                      (0x0040U >> 1)

#define GPT_D16_RA_HALF_TDE                      (0x0250U >> 1)
#define GPT_D16_RA_HALF_TDM                      (0x0254U >> 1)
#define GPT_D16_RA_HALF_TDL                      (0x0054U >> 1)

#define GPT_D16_RA_HALF_TRO                      (0x004cU >> 1)
#define GPT_D16_RA_HALF_TRE                      (0x0258U >> 1)
#define GPT_D16_RA_HALF_TRC                      (0x025cU >> 1)
#define GPT_D16_RA_HALF_TME                      (0x0050U >> 1)

#define GPT_D16_RA_HALF_RDE                      (0x0260U >> 1)
#define GPT_D16_RA_HALF_RDM                      (0x0264U >> 1)
#define GPT_D16_RA_HALF_RDS                      (0x0268U >> 1)
#define GPT_D16_RA_HALF_RDC                      (0x026cU >> 1)
#define GPT_D16_RA_HALF_RDT                      (0x0044U >> 1)
#define GPT_D16_RA_HALF_RSF                      (0x0048U >> 1)

#define GPT_D16_MDCTRL_BIT_CONST                 (0xffdfU)

#define GPT_D16_CSR_BIT_OVF                      (0x01U)
#define GPT_D16_CSC_BIT_CLOV                     (0x01U)

#define GPT_D16_CH_TO_UNIT                       (4U)
#define GPT_D16_CH_TO_CH_BY_UNIT                 (0x0000000fU)

#define GPT_D16_RO_HALF_LSR_CH                   (1U)
#define GPT_D16_RO_BYTE_LSR_CH                   (2U)

#define GPT_D16_PIC1_TAUD0                       (GPT_D16_UNIT_0)
#define GPT_D16_PIC1_TAUD1                       (GPT_D16_UNIT_1 << 4)
#define GPT_D16_PIC1_TAUD2                       (GPT_D16_UNIT_2 << 4)

#define GPT_D16_PIC1_BASE                        ((volatile U4 *)0xFFBFAF00U)
#define GPT_D16_PIC1_TAUD2SEL_BASE               ((volatile U2 *)0xFFBF6800U)

#define GPT_D16_PIC1_RA_WORD_TAUD0S              (0x0078U >> 2)
#define GPT_D16_PIC1_RA_WORD_TAUD1S              (0x007cU >> 2) 
#define GPT_D16_PIC1_RA_HALF_TAUD2               (0x0000U)


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
#define RH850_G4MH_SYNCP_HALF  /* static inline void  vd_s_SYNCP_H(const volatile U2 * const u2_ap_RDBK) */
#define RH850_G4MH_RDBK_HALF   /* static inline void  vd_s_RDBK_H(const volatile U2 * const u2_ap_RDBK)  */
#include "rh850_g4mh.h"

static void    vd_s_Gpt_D16PICInit(void);
static void    vd_s_Gpt_D16PICDeInit(void);
static U1      u1_s_Gpt_D16PICSetup(const U1 u1_a_D16_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section text=".GPT_TEXT_CODE"

/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16Init(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16Init(void)
{
    volatile U2 *       u2_tp_half;
    volatile U1 *       u1_tp_byte;

    const U2 *          u2_tp_MDCTRL;
    const U2 *          u2_tp_IRQ_CH;

    volatile U4         u4_t_gli;

    U4                  u4_t_unit;
    U4                  u4_t_ch;
    U4                  u4_t_lpcnt;
    U4                  u4_t_offset;

    vd_s_Gpt_D16PICInit();

    for(u4_t_unit = (U4)0U; u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT; u4_t_unit++){

        u2_tp_half = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        u1_tp_byte = (volatile U1 *)u2_tp_half;

        u2_tp_IRQ_CH = &(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[0]);

        u4_t_gli = u4_g_IRQ_DI();

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GPT_D16_NUM_CH_BY_UNIT; u4_t_lpcnt++){
            vd_g_IntHndlrIRQCtrlCh(u2_tp_IRQ_CH[u4_t_lpcnt], (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        }

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TT], (U2)U2_MAX);
        vd_s_RDBK_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);

        vd_g_IRQ_EI(u4_t_gli);

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TPS],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_tps    );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_D16_RA_BYTE_BRS],  (U1)st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_brs);

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TO],   (U2)0x0000U                                 );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_en );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_cf );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_md );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOL],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_lv );

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_en );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_md );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDL],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_lv );

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_en );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_ct );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRO],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_lv );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TME],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_mo );

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_en );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_md );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDS],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_se );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_ct );

        u2_tp_MDCTRL = &(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_mdctrl[0]);
        for(u4_t_ch = (U4)0U; u4_t_ch < (U4)GPT_D16_NUM_CH_BY_UNIT; u4_t_ch++){

            u4_t_offset = (U4)GPT_D16_RA_HALF_CMOR_CH_0 + (u4_t_ch << GPT_D16_RO_HALF_LSR_CH);
            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],  u2_tp_MDCTRL[u4_t_ch]);

            u4_t_offset = (U4)GPT_D16_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_D16_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],  (U1)0x00U            );
        }

        vd_s_RDBK_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);
    }
    vd_s_SYNCP();
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16DeInit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16DeInit(void)
{
    volatile U2 *       u2_tp_half;
    const U2 *          u2_tp_IRQ_CH;

    volatile U4         u4_t_gli;
    U4                  u4_t_unit;

    U4                  u4_t_lpcnt;

    for(u4_t_unit = (U4)0U; u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT; u4_t_unit++){

        u2_tp_half   = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;

        u2_tp_IRQ_CH = &(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[0]);

        u4_t_gli = u4_g_IRQ_DI();

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)GPT_D16_NUM_CH_BY_UNIT; u4_t_lpcnt++){
            vd_g_IntHndlrIRQCtrlCh(u2_tp_IRQ_CH[u4_t_lpcnt], (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
        }

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TT],  (U2)U2_MAX);

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOE], (U2)0x0000U);
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TO],  (U2)0x0000U);
        vd_s_RDBK_H(&u2_tp_half[GPT_D16_RA_HALF_TO]);

        vd_g_IRQ_EI(u4_t_gli);
    }
    vd_s_Gpt_D16PICDeInit();
}
/*===================================================================================================================================*/
/*  U2      u2_g_Gpt_D16GetTimeElapsed(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_Gpt_D16GetTimeElapsed(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)
{
    volatile U2 *       u2_tp_half;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U2                  u2_t_elapsed;

    u2_t_elapsed = (U2)U2_MAX;
    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch = (((U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT) << 1) + (U4)GPT_D16_RA_HALF_CNT_CH_0;

        u2_tp_half   = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        u2_t_elapsed = u2_REG_READ(u2_tp_half[u4_t_ch]);

        if(u2_ap_d16stamp != vdp_PTR_NA){
            u2_ap_d16stamp[GPT_D16_TMELPSD_CRRNT] = u2_t_elapsed;
            u2_t_elapsed -= u2_ap_d16stamp[GPT_D16_TMELPSD_BASE];
        }
    }

    return(u2_t_elapsed);
}
/*===================================================================================================================================*/
/*  U2      u2_g_Gpt_D16GetTimeCaptured(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_Gpt_D16GetTimeCaptured(const U1 u1_a_D16_CH, U2 * u2_ap_d16stamp)
{
    volatile U2 *       u2_tp_half;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U2                  u2_t_elapsed;

    u2_t_elapsed = (U2)U2_MAX;
    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

     /* u4_t_ch = (((U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT) << 1U) + (U4)GPT_D16_RA_HALF_CDR_CH_0; QAC Warning#2985 */
        u4_t_ch = ((U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT) << 1U;

        u2_tp_half   = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        u2_t_elapsed = u2_REG_READ(u2_tp_half[u4_t_ch]);

        if(u2_ap_d16stamp != vdp_PTR_NA){
            u2_ap_d16stamp[GPT_D16_TMELPSD_CRRNT] = u2_t_elapsed;
            u2_t_elapsed -= u2_ap_d16stamp[GPT_D16_TMELPSD_BASE];
        }
    }

    return(u2_t_elapsed);
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16Start(const U1 u1_a_D16_CH, const U2 * u2_ap_START)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16Start(const U1 u1_a_D16_CH, const U2 * u2_ap_START)
{
    volatile U2 *       u2_tp_half;
    volatile U1 *       u1_tp_byte;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U4                  u4_t_irq_ch;
    U4                  u4_t_offset;

    U2                  u2_t_bit;
    U2                  u2_t_period;
    U2                  u2_t_start;
    U2                  u2_t_mdctrl;
    U2                  u2_t_chbit;
    U2                  u2_t_stbit;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch     = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        u2_t_chbit  = (U2)0x0001 << u4_t_ch;

        u4_t_irq_ch = (U4)st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch];

        u2_tp_half  = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        u1_tp_byte  = (volatile U1 *)u2_tp_half;

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TPS],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_tps    );
        vd_REG_U1_WRITE(u1_tp_byte[GPT_D16_RA_BYTE_BRS],  (U1)st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_brs);

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_en );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOL],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_lv );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDL],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_lv );

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRO],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_lv );
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TME],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_mo );

        u2_t_start  = u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TE]) ^ u2_t_chbit;
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TOC]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_cf);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TOM]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_md);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TDE]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_en);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TDM]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_md);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TRE]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_en);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TRC]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_ct);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_RDE]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_en);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_RDM]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_md);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_RDS]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_se);
        u2_t_start |= (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_RDC]) ^ st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_ct);
        u2_t_start &= u2_t_chbit;

        u4_t_offset = (U4)GPT_D16_RA_HALF_CMOR_CH_0 + (u4_t_ch << GPT_D16_RO_HALF_LSR_CH);
        u2_t_mdctrl = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_mdctrl[u4_t_ch] & (U2)GPT_D16_MDCTRL_BIT_CONST;
        u2_t_start |= ((u2_REG_READ(u2_tp_half[u4_t_offset]) ^ u2_t_mdctrl) & (U2)GPT_D16_MDCTRL_BIT_CONST);

        u2_t_bit    = u2_ap_START[GPT_D16_START_CTRL] & (U2)GPT_D16_START_CTRL_BIT_TRG_ST;
        if(u2_t_bit != (U2)0U){
            u2_t_stbit = u2_t_chbit;
        }
        else{
            u2_t_stbit = (U2)0U;
        }

        if(u2_t_start != (U2)0U){

            vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);

            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TT],   u2_t_chbit  );
            vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);

            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_cf);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TOM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_out_md);

            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_en);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TDM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_dto_md);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_en);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TRC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rto_ct);

            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDE],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_en);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDM],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_md);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDS],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_se);
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDC],  st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_ct);

            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],          u2_t_mdctrl );

            u2_t_bit     = u2_ap_START[GPT_D16_START_CTRL] & (U2)GPT_D16_START_CTRL_BIT_ELVL;
            u4_t_offset = (U4)GPT_D16_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_D16_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],          (U1)u2_t_bit);

         /* u4_t_offset = (U4)GPT_D16_RA_HALF_CDR_CH_0 + (u4_t_ch << GPT_D16_RO_HALF_LSR_CH);  QAC Warning#2986 */
            u4_t_offset = u4_t_ch << GPT_D16_RO_HALF_LSR_CH;
            u2_t_period = u2_ap_START[GPT_D16_START_PERI] - (U2)1U;
            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],          u2_t_period );

            u4_t_offset = (U4)GPT_D16_RA_BYTE_CSC_CH_0 + (u4_t_ch << GPT_D16_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],          (U1)TRUE    );

            u2_t_bit = u2_ap_START[GPT_D16_START_CTRL] & (U2)GPT_D16_START_CTRL_BIT_IRQ_EN;
            if(u2_t_bit != (U2)0){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }

            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TS],   u2_t_stbit  );
            vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);
        }
        else{

            u2_t_bit    = u2_ap_START[GPT_D16_START_CTRL] & (U2)GPT_D16_START_CTRL_BIT_ELVL;
            u4_t_offset = (U4)GPT_D16_RA_BYTE_CMUR_CH_0 + (u4_t_ch << GPT_D16_RO_BYTE_LSR_CH);
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],          (U1)u2_t_bit);

            u2_t_stbit  = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2_rld_en & u2_t_stbit;
            u2_t_period = u2_ap_START[GPT_D16_START_PERI] - (U2)1U;
         /* u4_t_offset = (U4)GPT_D16_RA_HALF_CDR_CH_0 + (u4_t_ch << GPT_D16_RO_HALF_LSR_CH); QAC Warning#2986 */
            u4_t_offset = u4_t_ch << GPT_D16_RO_HALF_LSR_CH;
            vd_REG_U2_WRITE(u2_tp_half[u4_t_offset],          u2_t_period );
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDT],  u2_t_stbit  );
            vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_RSF]);

            u2_t_bit = u2_ap_START[GPT_D16_START_CTRL] & ((U2)GPT_D16_START_CTRL_BIT_IRQ_EN | (U2)GPT_D16_START_CTRL_BIT_IRQ_CL);
            if(u2_t_bit == ((U2)GPT_D16_START_CTRL_BIT_IRQ_EN | (U2)GPT_D16_START_CTRL_BIT_IRQ_CL)){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR | (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else if(u2_t_bit == (U2)GPT_D16_START_CTRL_BIT_IRQ_EN){
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
            }
            else{
                vd_g_IntHndlrIRQCtrlCh((U2)u4_t_irq_ch, (U1)INT_HNDLR_IRQ_CTRL_RQ_CLR);
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16Stop(const U1 u1_a_D16_CH)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16Stop(const U1 u1_a_D16_CH)
{
    volatile U2 *       u2_tp_half;

    U4                  u4_t_unit;
    U4                  u4_t_ch;

    U2                  u2_t_chbit;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch    = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        u2_t_chbit = (U2)0x0001 << u4_t_ch;

        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch], (U1)0x00U);

        u2_tp_half = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TT],  u2_t_chbit);
        vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16SyncStart(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16SyncStart(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)
{
    volatile U2 *       u2_tp_half;
    U2                  u2_t_run;

    if(u1_a_D16_UNIT < u1_g_GPT_D16_NUM_UNIT){

        u2_tp_half = st_gp_GPT_D16_UNIT_CFG[u1_a_D16_UNIT].u2p_base;

        u2_t_run   = u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TE]) & u2_a_D16_CHBIT;
        if(u2_t_run != u2_a_D16_CHBIT){
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TS],   u2_a_D16_CHBIT);
            vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);
        }
        else{
            vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_RDT],  u2_a_D16_CHBIT);
            vd_s_SYNCP_H(&u2_tp_half[GPT_D16_RA_HALF_RSF]);
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16SyncStop(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16SyncStop(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)
{
    volatile U2 *       u2_tp_half;
    const U2 *          u2_tp_IRQ_CH;

    volatile U4         u4_t_gli;
    U4                  u4_t_lpcnt;

    U2                  u2_t_chbit;
    U2                  u2_t_bit;

    if(u1_a_D16_UNIT < u1_g_GPT_D16_NUM_UNIT){

        u2_tp_half   = st_gp_GPT_D16_UNIT_CFG[u1_a_D16_UNIT].u2p_base;

        u2_t_chbit   = u2_a_D16_CHBIT;
        u2_tp_IRQ_CH = &(st_gp_GPT_D16_UNIT_CFG[u1_a_D16_UNIT].u2p_irq_ch[0]);

        u4_t_gli = u4_g_IRQ_DI();

        u4_t_lpcnt = (U4)0U;
        while(u2_t_chbit != (U2)0U){

            u2_t_bit = u2_t_chbit & (U2)0x0001U;
            if(u2_t_bit != (U2)0U){
                vd_g_IntHndlrIRQCtrlCh(u2_tp_IRQ_CH[u4_t_lpcnt], (U1)0x00U);
            }
            u2_t_chbit >>= 1;
            u4_t_lpcnt++;
        }

        vd_REG_U2_WRITE(u2_tp_half[GPT_D16_RA_HALF_TT],  u2_a_D16_CHBIT);
        vd_s_RDBK_H(&u2_tp_half[GPT_D16_RA_HALF_TE]);

        vd_g_IRQ_EI(u4_t_gli);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_D16SyncReload(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_D16SyncReload(const U1 u1_a_D16_UNIT, const U2 u2_a_D16_CHBIT)
{
    volatile U2 *       u2_tp_half;
    U2                  u2_t_chbit;
    U2                  u2_t_bit;
    U1                  u1_t_reload;

    u1_t_reload = (U1)FALSE;
    if(u1_a_D16_UNIT < u1_g_GPT_D16_NUM_UNIT){

        u2_tp_half = st_gp_GPT_D16_UNIT_CFG[u1_a_D16_UNIT].u2p_base;
        u2_t_chbit = st_gp_GPT_D16_UNIT_CFG[u1_a_D16_UNIT].u2_rld_en & u2_a_D16_CHBIT;
        u2_t_bit   = (u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_RSF]) ^ u2_t_chbit) & u2_t_chbit;
        if(u2_t_bit == u2_a_D16_CHBIT){
            u1_t_reload = (U1)TRUE;
        }
    }

    return(u1_t_reload);
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16EI(const U1 u1_a_D16_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16EI(const U1 u1_a_D16_CH)
{
    U4                  u4_t_unit;
    U4                  u4_t_ch;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch], (U1)INT_HNDLR_IRQ_CTRL_CH_ENA);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_Gpt_D16DI(const U1 u1_a_D16_CH)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gpt_D16DI(const U1 u1_a_D16_CH)
{
    U4                  u4_t_unit;
    U4                  u4_t_ch;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        vd_g_IntHndlrIRQCtrlCh(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch], (U1)0x00);
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_D16IRQst(const U1 u1_a_D16_CH, const U1 u1_a_W_CLR)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_D16IRQst(const U1 u1_a_D16_CH, const U1 u1_a_W_CLR)
{
    volatile U1 *       u1_tp_byte;

    U4                  u4_t_unit;
    U4                  u4_t_ch;
    U1                  u1_t_ovf;

    U4                  u4_t_offset;
    U1                  u1_t_irqst;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        u1_t_irqst = u1_g_IntHndlrIRQst(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch], (U1)(u1_a_W_CLR & GPT_D16_IRQST_BIT_IRQ));

        u1_tp_byte  = (volatile U1 *)st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;

        u4_t_ch = u4_t_ch << GPT_D16_RO_BYTE_LSR_CH;
        u4_t_offset = (U4)GPT_D16_RA_BYTE_CSR_CH_0 + u4_t_ch;
        u1_t_ovf = u1_REG_READ(u1_tp_byte[u4_t_offset]) & GPT_D16_CSR_BIT_OVF;

        if((u1_a_W_CLR & (U1)GPT_D16_IRQST_BIT_OVF) != 0){
            u4_t_offset = (U4)GPT_D16_RA_BYTE_CSC_CH_0 + u4_t_ch;
            vd_REG_U1_WRITE(u1_tp_byte[u4_t_offset],   (U1)GPT_D16_CSC_BIT_CLOV);
        }
        
        if(u1_t_ovf != (U1)0U){
            u1_t_irqst |= (U1)GPT_D16_IRQST_BIT_OVF;
        }
    }
    else{
        u1_t_irqst = (U1)0;
    }

    return(u1_t_irqst);
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_D16IRQenabled(const U1 u1_a_D16_CH)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_D16IRQenabled(const U1 u1_a_D16_CH)
{
    volatile U2 *       u2_tp_half;

    U4                  u4_t_unit;
    U4                  u4_t_ch;
    U2                  u2_t_chbit;
    U2                  u2_t_run;

    U1                  u1_t_irqen;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    if(u4_t_unit < (U4)u1_g_GPT_D16_NUM_UNIT){

        u4_t_ch    = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
        u2_t_chbit = (U2)0x0001 << u4_t_ch;

        u1_t_irqen = u1_g_IntHndlrIRQenabled(st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_irq_ch[u4_t_ch]);

        u2_tp_half = st_gp_GPT_D16_UNIT_CFG[u4_t_unit].u2p_base;
        u2_t_run   = u2_REG_READ(u2_tp_half[GPT_D16_RA_HALF_TE]) & u2_t_chbit;
        if(u2_t_run != (U2)0U){
            u1_t_irqen |= (U1)GPT_D16_IRQEN_BIT_CNTE;
        }
    }
    else{
        u1_t_irqen = (U1)0x00U;
    }

    return(u1_t_irqen);
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_D16PICRegChk(const U1 u1_a_D16_CH)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_D16PICRegChk(const U1 u1_a_D16_CH)
{
    U4                  u4_t_unit;
    U4                  u4_t_ch;
    U4                  u4_t_ch_msk;
    U4                  u4_t_ch_bit;
    U1                  u1_t_rslt;

    u1_t_rslt   = (U1)TRUE;
    u4_t_ch     = (U4)u1_a_D16_CH & (U4)GPT_D16_CH_TO_CH_BY_UNIT;
    u4_t_unit   = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;
    u4_t_ch_msk = (U4)0x03U << (u4_t_ch * 2U);

    switch(u4_t_unit){
        case GPT_D16_UNIT_0:
            u4_t_ch_bit = u4_REG_READ(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD0S]) & u4_t_ch_msk;
            if(u4_t_ch_bit != (U4)(u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_0] & u4_t_ch_msk)){
                u1_t_rslt = (U1)FALSE;
            }
            break;

        case GPT_D16_UNIT_1:
            u4_t_ch_bit = u4_REG_READ(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD1S]) & u4_t_ch_msk;
            if(u4_t_ch_bit != (U4)(u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_1] & u4_t_ch_msk)){
                u1_t_rslt = (U1)FALSE;
            }
            break;

        case GPT_D16_UNIT_2:
            u4_t_ch_msk = (U4)1U << u4_t_ch; /* Because TAUD2 has a different register layout, reset the mask value. */
            u4_t_ch_bit = (U4)u2_REG_READ(GPT_D16_PIC1_TAUD2SEL_BASE[GPT_D16_PIC1_RA_HALF_TAUD2]) & u4_t_ch_msk;
            if((U2)u4_t_ch_bit != (U2)(u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_2] & u4_t_ch_msk)){
                u1_t_rslt = (U1)FALSE;
            }
            break;
        default:
            u1_t_rslt = (U1)FALSE;
            break;
    }

    return u1_t_rslt;
}
/*===================================================================================================================================*/
/*  U1      u1_g_Gpt_D16PICRegRefresh(const U1 u1_a_D16_CH)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_Gpt_D16PICRegRefresh(const U1 u1_a_D16_CH)
{
    U1                  u1_t_rslt;

    u1_t_rslt = u1_s_Gpt_D16PICSetup(u1_a_D16_CH);

    return u1_t_rslt;
}
/*===================================================================================================================================*/
/*  static void    vd_s_Gpt_D16PICInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gpt_D16PICInit(void)
{
    (void)u1_s_Gpt_D16PICSetup(GPT_D16_PIC1_TAUD0);
    (void)u1_s_Gpt_D16PICSetup(GPT_D16_PIC1_TAUD1);
    (void)u1_s_Gpt_D16PICSetup(GPT_D16_PIC1_TAUD2);
}
/*===================================================================================================================================*/
/*  static void    vd_s_Gpt_D16PICDeInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gpt_D16PICDeInit(void)
{
    vd_REG_U4_WRITE(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD0S], (U4)0x00000000U);
    vd_REG_U4_WRITE(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD1S], (U4)0x00000000U);
    vd_REG_U2_WRITE(GPT_D16_PIC1_TAUD2SEL_BASE[GPT_D16_PIC1_RA_HALF_TAUD2], (U2)0x0000U);
}
/*===================================================================================================================================*/
/*  U1      u1_s_Gpt_D16PICSetup(const U1 u1_a_D16_CH)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Gpt_D16PICSetup(const U1 u1_a_D16_CH)
{
    U1                  u1_t_rslt;
    U4                  u4_t_unit;

    u4_t_unit = (U4)u1_a_D16_CH >> GPT_D16_CH_TO_UNIT;

    switch(u4_t_unit){
        case GPT_D16_UNIT_0:
            vd_REG_U4_WRITE(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD0S], (U4)u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_0]);
            break;

        case GPT_D16_UNIT_1:
            vd_REG_U4_WRITE(GPT_D16_PIC1_BASE[GPT_D16_PIC1_RA_WORD_TAUD1S], (U4)u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_1]);
            break;

        case GPT_D16_UNIT_2:
            vd_REG_U2_WRITE(GPT_D16_PIC1_TAUD2SEL_BASE[GPT_D16_PIC1_RA_HALF_TAUD2], (U2)u4_g_GPT_CFG_PIC1_TAUDSEL[GPT_D16_UNIT_2]);
            break;

        default:
            /* do nothing */
            break;
    }

    u1_t_rslt = u1_g_Gpt_D16PICRegChk(u1_a_D16_CH);

    return u1_t_rslt;
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
/*  1.0.0    12/23/2021  TN       New.                                                                                               */
/*  1.0.1     1/10/2023  TI       Bug Fix : Changed the value of GPT_D16_MDCTRL_BIT_CONST.                                           */
/*                                          Modified TAUDnTDM and TAUDnTRC to write while timer is stopped.                          */
/*                                Improvement : Changed argument name.                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TI   = Takehisa Inoue, Denso                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
