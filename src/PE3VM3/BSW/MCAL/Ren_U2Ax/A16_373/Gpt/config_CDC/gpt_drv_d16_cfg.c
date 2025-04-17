/* 1.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/F1KM : Timer Array Unit D                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_DRV_D16_CFG_C_MAJOR                  (1)
#define GPT_DRV_D16_CFG_C_MINOR                  (0)
#define GPT_DRV_D16_CFG_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gpt_drv_d16_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GPT_DRV_D16_CFG_C_MAJOR != GPT_DRV_D16_CFG_H_MAJOR) || \
     (GPT_DRV_D16_CFG_C_MINOR != GPT_DRV_D16_CFG_H_MINOR) || \
     (GPT_DRV_D16_CFG_C_PATCH != GPT_DRV_D16_CFG_H_PATCH))
#error "gpt_drv_d16_cfg.c and gpt_drv_d16_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GPT_D16_MDCTRL_RLT_REPT                  (0x0000U)

#define GPT_D16_MDCTRL_PWM_PERI                  (0x0801U)      /* 33.15.1.4 Register Settings for the Master Channel   */
#define GPT_D16_MDCTRL_PWM_DUTY                  (0x0409U)      /* 33.15.1.5 Register Settings for Slave Channels       */

#define GPT_D16_MDCTRL_FRT_CAPT                  (0x0156U)      /* 33.12.9 TAUDnTTINm Input Position Detection Function */

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
#pragma ghs section rodata=".GPT_RODATA_CONST"

const ST_GPT_D16_UNIT    st_gp_GPT_D16_UNIT_CFG[GPT_D16_NUM_UNIT] = {
    /*---------------------------- GPT_D16_UNIT_00 -------------------------------------------------------------------------*/
    {
        (volatile U2 *)0xffbf4000U,                                                                       /* u2p_base       */
        {
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[0]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[1]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[2]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[3]  */
            (U2)GPT_D16_MDCTRL_PWM_PERI | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[4]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[5]  */
            (U2)GPT_D16_MDCTRL_PWM_DUTY | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[6]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[7]  */
            (U2)GPT_D16_MDCTRL_PWM_DUTY | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[8]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[9]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[10] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[11] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[12] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[13] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[14] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0                                     /* u2p_mdctrl[15] */
        },
        {
            (U2)10U,                                                                                      /* u2p_irq_ch[0]  */
            (U2)376U,                                                                                     /* u2p_irq_ch[1]  */
            (U2)11U,                                                                                      /* u2p_irq_ch[2]  */
            (U2)377U,                                                                                     /* u2p_irq_ch[3]  */
            (U2)12U,                                                                                      /* u2p_irq_ch[4]  */
            (U2)378U,                                                                                     /* u2p_irq_ch[5]  */
            (U2)13U,                                                                                      /* u2p_irq_ch[6]  */
            (U2)379U,                                                                                     /* u2p_irq_ch[7]  */
            (U2)23U,                                                                                      /* u2p_irq_ch[8]  */
            (U2)380U,                                                                                     /* u2p_irq_ch[9]  */
            (U2)24U,                                                                                      /* u2p_irq_ch[10] */
            (U2)381U,                                                                                     /* u2p_irq_ch[11] */
            (U2)25U,                                                                                      /* u2p_irq_ch[12] */
            (U2)382U,                                                                                     /* u2p_irq_ch[13] */
            (U2)26U,                                                                                      /* u2p_irq_ch[14] */
            (U2)383U                                                                                      /* u2p_irq_ch[15] */
        },

        (U2)0x0000U,                                                                                      /* u2_tps         */
        (U2)0x0000U,                                                                                      /* u2_brs         */

        (U2)0x0140U,                                                                                      /* u2_out_en      */
        (U2)0x0140U,                                                                                      /* u2_out_md      */
        (U2)0x0000U,                                                                                      /* u2_out_cf      */
        (U2)0x0100U,                                                                                      /* u2_out_lv      */

        (U2)0x0000U,                                                                                      /* u2_dto_en      */
        (U2)0x0000U,                                                                                      /* u2_dto_md      */
        (U2)0x0000U,                                                                                      /* u2_dto_lv      */

        (U2)0x0000U,                                                                                      /* u2_rto_en      */
        (U2)0x0000U,                                                                                      /* u2_rto_ct      */
        (U2)0x0000U,                                                                                      /* u2_rto_lv      */
        (U2)0x0000U,                                                                                      /* u2_rto_mo      */

        (U2)0x0000U,                                                                                      /* u2_rld_en      */
        (U2)0x0000U,                                                                                      /* u2_rld_md      */
        (U2)0x0000U,                                                                                      /* u2_rld_se      */
        (U2)0x0000U                                                                                       /* u2_rld_ct      */
    },
    /*---------------------------- GPT_D16_UNIT_01 -------------------------------------------------------------------------*/
    {
        (volatile U2 *)0xffbf5000U,                                                                       /* u2p_base       */
        {
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[0]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[1]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[2]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[3]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[4]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[5]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[6]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[7]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[8]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[9]  */
            (U2)GPT_D16_MDCTRL_PWM_PERI | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[10] */
            (U2)GPT_D16_MDCTRL_PWM_DUTY | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[11] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[12] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[13] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[14] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0                                     /* u2p_mdctrl[15] */
        },
        {
            (U2)384U,                                                                                     /* u2p_irq_ch[0]  */
            (U2)385U,                                                                                     /* u2p_irq_ch[1]  */
            (U2)386U,                                                                                     /* u2p_irq_ch[2]  */
            (U2)387U,                                                                                     /* u2p_irq_ch[3]  */
            (U2)388U,                                                                                     /* u2p_irq_ch[4]  */
            (U2)389U,                                                                                     /* u2p_irq_ch[5]  */
            (U2)390U,                                                                                     /* u2p_irq_ch[6]  */
            (U2)391U,                                                                                     /* u2p_irq_ch[7]  */
            (U2)392U,                                                                                     /* u2p_irq_ch[8]  */
            (U2)393U,                                                                                     /* u2p_irq_ch[9]  */
            (U2)394U,                                                                                     /* u2p_irq_ch[10] */
            (U2)395U,                                                                                     /* u2p_irq_ch[11] */
            (U2)396U,                                                                                     /* u2p_irq_ch[12] */
            (U2)397U,                                                                                     /* u2p_irq_ch[13] */
            (U2)398U,                                                                                     /* u2p_irq_ch[14] */
            (U2)399U                                                                                      /* u2p_irq_ch[15] */
        },

        (U2)0x0000U,                                                                                      /* u2_tps         */
        (U2)0x0000U,                                                                                      /* u2_brs         */

        (U2)0x0800U,                                                                                      /* u2_out_en      */
        (U2)0x0800U,                                                                                      /* u2_out_md      */
        (U2)0x0000U,                                                                                      /* u2_out_cf      */
        (U2)0x0000U,                                                                                      /* u2_out_lv      */

        (U2)0x0000U,                                                                                      /* u2_dto_en      */
        (U2)0x0000U,                                                                                      /* u2_dto_md      */
        (U2)0x0000U,                                                                                      /* u2_dto_lv      */

        (U2)0x0000U,                                                                                      /* u2_rto_en      */
        (U2)0x0000U,                                                                                      /* u2_rto_ct      */
        (U2)0x0000U,                                                                                      /* u2_rto_lv      */
        (U2)0x0000U,                                                                                      /* u2_rto_mo      */

        (U2)0x0000U,                                                                                      /* u2_rld_en      */
        (U2)0x0000U,                                                                                      /* u2_rld_md      */
        (U2)0x0000U,                                                                                      /* u2_rld_se      */
        (U2)0x0000U                                                                                       /* u2_rld_ct      */
    },
    /*---------------------------- GPT_D16_UNIT_02 -------------------------------------------------------------------------*/
    {
        (volatile U2 *)0xffbf6000U,                                                                       /* u2p_base       */
        {
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[0]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[1]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[2]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[3]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[4]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[5]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[6]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[7]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[8]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[9]  */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[10] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[11] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[12] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[13] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0,                                    /* u2p_mdctrl[14] */
            (U2)GPT_D16_MDCTRL_RLT_REPT | (U2)GPT_D16_MDCTRL_CLKSRC_0                                     /* u2p_mdctrl[15] */
        },
        {
            (U2)400U,                                                                                     /* u2p_irq_ch[0]  */
            (U2)401U,                                                                                     /* u2p_irq_ch[1]  */
            (U2)402U,                                                                                     /* u2p_irq_ch[2]  */
            (U2)403U,                                                                                     /* u2p_irq_ch[3]  */
            (U2)404U,                                                                                     /* u2p_irq_ch[4]  */
            (U2)405U,                                                                                     /* u2p_irq_ch[5]  */
            (U2)406U,                                                                                     /* u2p_irq_ch[6]  */
            (U2)407U,                                                                                     /* u2p_irq_ch[7]  */
            (U2)408U,                                                                                     /* u2p_irq_ch[8]  */
            (U2)409U,                                                                                     /* u2p_irq_ch[9]  */
            (U2)410U,                                                                                     /* u2p_irq_ch[10] */
            (U2)411U,                                                                                     /* u2p_irq_ch[11] */
            (U2)412U,                                                                                     /* u2p_irq_ch[12] */
            (U2)413U,                                                                                     /* u2p_irq_ch[13] */
            (U2)414U,                                                                                     /* u2p_irq_ch[14] */
            (U2)415U                                                                                      /* u2p_irq_ch[15] */
        },

        (U2)0x0000U,                                                                                      /* u2_tps         */
        (U2)0x0000U,                                                                                      /* u2_brs         */

        (U2)0x0000U,                                                                                      /* u2_out_en      */
        (U2)0x0000U,                                                                                      /* u2_out_md      */
        (U2)0x0000U,                                                                                      /* u2_out_cf      */
        (U2)0x0000U,                                                                                      /* u2_out_lv      */

        (U2)0x0000U,                                                                                      /* u2_dto_en      */
        (U2)0x0000U,                                                                                      /* u2_dto_md      */
        (U2)0x0000U,                                                                                      /* u2_dto_lv      */

        (U2)0x0000U,                                                                                      /* u2_rto_en      */
        (U2)0x0000U,                                                                                      /* u2_rto_ct      */
        (U2)0x0000U,                                                                                      /* u2_rto_lv      */
        (U2)0x0000U,                                                                                      /* u2_rto_mo      */

        (U2)0x0000U,                                                                                      /* u2_rld_en      */
        (U2)0x0000U,                                                                                      /* u2_rld_md      */
        (U2)0x0000U,                                                                                      /* u2_rld_se      */
        (U2)0x0000U                                                                                       /* u2_rld_ct      */
    }
};
const U1                 u1_g_GPT_D16_NUM_UNIT = (U1)GPT_D16_NUM_UNIT;

#pragma ghs section rodata=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/23/2021  TN       New.                                                                                               */
/*  1.0.1     1/10/2023  TI       gpt_drv_d16.c v1.0.0 -> v1.0.1.                                                                    */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TI   = Takehisa Inoue, Denso                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
