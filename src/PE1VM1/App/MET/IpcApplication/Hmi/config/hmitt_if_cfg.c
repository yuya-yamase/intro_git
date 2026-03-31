/* 1.11.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmitt                                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITT_IF_CFG_C_MAJOR                  (1)
#define HMITT_IF_CFG_C_MINOR                  (11)
#define HMITT_IF_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmitt_cfg_private.h"
#include "hmitt_if_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMITT_IF_CFG_C_MAJOR != HMITT_H_MAJOR) || \
     (HMITT_IF_CFG_C_MINOR != HMITT_H_MINOR) || \
     (HMITT_IF_CFG_C_PATCH != HMITT_H_PATCH))
#error "hmitt_if_cfg.c and hmitt_if_cfg.h : source and header files are inconsistent!"
#endif

#if ((HMITT_IF_CFG_C_MAJOR != HMITT_IF_CFG_H_MAJOR) || \
     (HMITT_IF_CFG_C_MINOR != HMITT_IF_CFG_H_MINOR) || \
     (HMITT_IF_CFG_C_PATCH != HMITT_IF_CFG_H_PATCH))
#error "hmitt_if_cfg.c and hmitt__if_cfg.h : source and header files are inconsistent!"
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_REQBIT   st_gp_HMITTASILREQBIT[HMITTCFG_IF_ASIL_NUM] = {
    /*  u2_src_ch                     u1_src_act                           u1_dst_idx  u4_dst_bit                                                      */
    {  (U2)ALERT_CH_C_ECB_TT,         (U1)ALERT_REQ_C_ECB_TT_MALFUNC,           (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB_TT,         (U1)ALERT_REQ_C_ECB_TT_UNAVAILABLE,       (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB_TT,         (U1)ALERT_REQ_C_ECB_TT_LEARNING1,         (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB_TT,         (U1)ALERT_REQ_C_ECB_TT_TESTMODE,          (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB_TT,         (U1)ALERT_REQ_C_ECB_TT_LEARNING2,         (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_MALFUNC,             (U1)0U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_OPERATING,           (U1)0U,    u4_HMITT_HB1(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_TESTMODE,            (U1)0U,    u4_HMITT_HB1(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,         (U1)0U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_PRIMARYCHK,        (U1)0U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_PUHDVCACT,         (U1)0U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_AIRBAG,         (U1)ALERT_REQ_B_AIRBAG_MALFUNC,           (U1)0U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_AIRBAG,         (U1)ALERT_REQ_B_AIRBAG_PRMRYCHK,          (U1)0U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_AIRBAG)             },
    {  (U2)ALERT_CH_C_VSCOFF,         (U1)ALERT_REQ_C_VSCOFF_UNAVAILABLE,       (U1)0U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_TT_ON,         (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_1HZ,     (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_2HZ,     (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_2P00HZ__50P_EPB)                },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_4HZ,     (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_4P00HZ__50P_EPB)                },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_ON,                (U1)0U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_FLASH_1HZ,         (U1)0U,    u4_HMITT_HB6(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_FLASH_4HZ,         (U1)0U,    u4_HMITT_HB6(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_BRLV_2_WRN,     (U1)ALERT_REQ_C_BRLV_2_WRN_MALFUNC,       (U1)0U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_2_TT,       (U1)ALERT_REQ_C_BRK_2_TT_ON,              (U1)0U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRPADW ,        (U1)ALERT_REQ_C_BRPADW_MALFUNC,           (U1)0U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_TMTT,           (U1)ALERT_REQ_S_TMTT_ON,                  (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_ON_R,            (U1)1U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_FLASH_4HZ,       (U1)1U,    u4_HMITT_HB1(HMITT_BLINK_CO_4P00HZ__50P_STEER)              },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_ON_A,            (U1)1U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_HLD,     (U1)ALERT_REQ_C_BRKHLD_HLD_ON,            (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_HLD,     (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,         (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_2P00HZ__50P)                    }
};
const ST_ALERT_REQBIT   st_gp_HMITTREQBIT[HMITTCFG_IF_NUM] = {
    /*  u2_src_ch                     u1_src_act                           u1_dst_idx  u4_dst_bit                                                      */
    {  (U2)ALERT_CH_B_TTAIL,          (U1)ALERT_REQ_B_TTAIL_ON,                 (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TRFOG,          (U1)ALERT_REQ_B_TRFOG_ON,                 (U1)0U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TFFOG,          (U1)ALERT_REQ_B_TFFOG_ON,                 (U1)0U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TBEAM12,        (U1)ALERT_REQ_B_TBEAM12_ON,               (U1)0U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_TRCOFF,         (U1)ALERT_REQ_C_TRCOFF_MALFUNC,           (U1)0U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_STBY,    (U1)ALERT_REQ_C_BRKHLD_STBY_ON,           (U1)3U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_REASYS_TT,      (U1)ALERT_REQ_H_REASYS_TT_ON,             (U1)8U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_REASYS_TT,      (U1)ALERT_REQ_H_REASYS_TT_FLASH,          (U1)8U,    u4_HMITT_HB4(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_B_THEAD,          (U1)ALERT_REQ_B_THEAD_ON,                 (U1)12U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_GRN_ON,            (U1)22U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_GRN_FLASH,         (U1)22U,   u4_HMITT_HB4(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_AMBER_ON,          (U1)22U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_HCS_TTB,        (U1)ALERT_REQ_C_HCS_TTB_ACCESS_MODE,      (U1)24U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    }
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  U2    u2_g_HmittSizeAsilReqbit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_t_ret : array element number                                                                                  */
/*===================================================================================================================================*/
U2 u2_g_HmittSizeAsilReqbit(void){

    U2 u2_t_ret;

    u2_t_ret = (U2)(sizeof(st_gp_HMITTASILREQBIT) / sizeof(st_gp_HMITTASILREQBIT[0]));

    return (u2_t_ret);
}

/*===================================================================================================================================*/
/*  U2    u2_g_HmittSizeReqbit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_t_ret : array element number                                                                                  */
/*===================================================================================================================================*/
U2 u2_g_HmittSizeReqbit(void){

    U2 u2_t_ret;

    u2_t_ret = (U2)(sizeof(st_gp_HMITTREQBIT) / sizeof(st_gp_HMITTREQBIT[0]));

    return (u2_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2017  TA       New.                                                                                               */
/*  1.1.0    04/18/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    09/07/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Setting for 800B 1A.                                                                               */
/*  1.4.0    06/02/2021  TH       Setting for 22-24FGM CV.                                                                           */
/*  1.6.0    02/02/2024  DR       Setting for 19PFv3                                                                                 */
/*  1.8.0    10/15/2024  KO       Setting for BEV System_Consideration_1.                                                            */
/*  1.9.0    06/23/2025  HY       Setting for BEV System_Consideration_2.                                                            */
/*  1.10.0   11/27/2025  PG       Setting for BEV System_Consideration_ADAS                                                          */
/*  1.11.0   01/20/2026  KI       hmitt.c,hmitt.h,hmitt_if_cfg.c,hmitt_if_cfg.h,hmitt_cfg.c,                                         */
/*                                hmitt_cfg_private.h v1.10.0 -> v1.11.0. (Change for BEV FF2.)                                      */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2 07/10/2024  YR       Added config for HCS                                                                               */
/*  19PFv3-3 09/04/2024  TR       Deleted config for H_XMGRIP (XMGRIP Level)                                                         */
/*  19PFv3-4 09/20/2024  TR       Updated config for P_COOTEM Blinking State                                                         */
/*  19Pfv3-5 11/25/2024  YR       Change CH name and request ID name for TRCOFF                                                      */
/*  19PFv3-5 12/10/2024  PG       Added config for S_DMC                                                                             */
/*  BEV-1    10/15/2024  KO       Change for BEV System_Consideration_1.(MET-C_STEER-CSTD-0-00-A-C0)                                 */
/*  BEV-2    11/12/2024  KO       Change for BEV System_Consideration_1.(MET-C_BRLV-CSTD-2-00-A-C0)                                  */
/*  BEV-3    11/25/2024  KO       Change for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-00-A-C0 / MET-C_EPB-CSTD-1-00-A-C0)        */
/*  BEV-4    12/23/2024  KO       Change for BEV System_Consideration_1.(MET-H_ZMILREQ-CSTD-1-00-A-C0                       )        */
/*  BEV-5     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-C_BRK-CSTD-2-00-A-C0)                                   */
/*  BEV-6    06/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0 / MET-S_ADTT-CSTD-0-02-A-C0)     */
/*  BEV-7     7/07/2025  KT       Delete for BEV System_Consideration_2.(MET-C_DAC-CSTD-2-00-B-C1 etc.)                              */
/*  BEV-8     1/15/2026  HT       Change for Full_function2 (MET-M_REMWAR-CSTD-2-04-A-C0)                                            */
/*                                Removed "ALERT_REQ" in order to transfer signal transmission control from the MCU to the SoC       */
/*  BEV-9     3/16/2026  NI       Change config for BEV Full_Function_2.                                                             */
/*                                MET-C_BRK-CSTD-2-00-C-C0,MET-C_ECB-CSTD-1-00-C-C0                                                  */
/*                                Changed split TT and PD, and rename/delete the definitions accordingly.                            */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * HF   = Hinari Fukamachi,KSE                                                                                                    */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * KT   = Kenta Takaji,    Denso Techno                                                                                           */
/*  * KI   = Kanji Ito,  Denso Techno                                                                                                */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * NI   = Naoki Inagaki, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
