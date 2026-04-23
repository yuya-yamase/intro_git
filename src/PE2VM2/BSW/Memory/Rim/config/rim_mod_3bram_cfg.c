/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3BRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_CFG_C_MAJOR                (1U)
#define RIM_MOD_3BRAM_CFG_C_MINOR                (3U)
#define RIM_MOD_3BRAM_CFG_C_PATCH                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"

#include "rim_mod_3bram_private.h"
#include "rim_mod_3bram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_3BRAM_CFG_C_MAJOR != RIM_MOD_3BRAM_H_MAJOR) || \
     (RIM_MOD_3BRAM_CFG_C_MINOR != RIM_MOD_3BRAM_H_MINOR) || \
     (RIM_MOD_3BRAM_CFG_C_PATCH != RIM_MOD_3BRAM_H_PATCH))
#error "rim_mod_3bram_cfg.c and rim_mod_3bram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_3BRAM_CFG_C_MAJOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_3BRAM_CFG_C_MINOR != RIM_MOD_3BRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_3BRAM_CFG_C_PATCH != RIM_MOD_3BRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_3bram_cfg.c and rim_mod_3bram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#RIM_MOD_3B_SIZE## */
#define RIM_MOD_3BRAM_U1_ID_NUM                  (8U)
#define RIM_MOD_3BRAM_U2_ID_NUM                  (5U)
#define RIM_MOD_3BRAM_U4_ID_NUM                  (7U)
#define RIM_MOD_3BRAM_OTHER_ID_NUM               (1U)
/* END : ##TOOL_OUT#RIM_MOD_3B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_TBL_SIZE## */
#define RIM_MOD_3BRAM_OTHER_BUF_NUM              (1U)
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_TBL_SIZE## */

/* Set st_d_RIM_MOD_3BRAM_OTR_SZ_CFG's max size */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_SIZE_MAX## */
#define RIM_MOD_3BRAM_OTHER_ID_CFGMAX            (4U)
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_SIZE_MAX## */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
#if (RIM_MOD_3BRAM_OTHER_ID_CFGMAX > RIM_MOD_3BRAM_OTHER_ID_MAXBYTE)
#error "This buffer number isn't supported.Please contact BSW team."
#endif  /* #if (RIM_MOD_3BRAM_OTHER_ID_CFGMAX > RIM_MOD_3BRAM_OTHER_ID_MAXBYTE) */
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
U1  u1_dp_rimmod_3b_byte_main[RIM_MOD_3BRAM_U1_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U1  u1_dp_rimmod_3b_byte_mirr1[RIM_MOD_3BRAM_U1_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U1  u1_dp_rimmod_3b_byte_mirr2[RIM_MOD_3BRAM_U1_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
U2  u2_dp_rimmod_3b_half_main[RIM_MOD_3BRAM_U2_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U2  u2_dp_rimmod_3b_half_mirr1[RIM_MOD_3BRAM_U2_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U2  u2_dp_rimmod_3b_half_mirr2[RIM_MOD_3BRAM_U2_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
U4  u4_dp_rimmod_3b_word_main[RIM_MOD_3BRAM_U4_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_word_mirr1[RIM_MOD_3BRAM_U4_ID_NUM]          __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_word_mirr2[RIM_MOD_3BRAM_U4_ID_NUM]          __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
U4  u4_dp_rimmod_3b_oth_main[RIM_MOD_3BRAM_OTHER_BUF_NUM]        __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_oth_mirr1[RIM_MOD_3BRAM_OTHER_BUF_NUM]       __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_oth_mirr2[RIM_MOD_3BRAM_OTHER_BUF_NUM]       __attribute__((section(".bss_BACK_RIM3")));

U4  u4_dp_rimmod_3b_oth_cs_main[RIM_MOD_3BRAM_OTHER_ID_NUM]      __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_3b_oth_cs_mirr1[RIM_MOD_3BRAM_OTHER_ID_NUM]     __attribute__((section(".bss_BACK_RIM2")));
U4  u4_dp_rimmod_3b_oth_cs_mirr2[RIM_MOD_3BRAM_OTHER_ID_NUM]     __attribute__((section(".bss_BACK_RIM3")));
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_d_RIM_MOD_3BRAM_MODULE_ID = (U2)RIM_MOD_ID_0;
const U2 u2_d_RIM_MOD_3BRAM_DATA_ID_MASK = (U2)0x01FFU;

#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U1_ID_NUM = (U2)RIM_MOD_3BRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U2_ID_NUM = (U2)RIM_MOD_3BRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_U4_ID_NUM = (U2)RIM_MOD_3BRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3BRAM_OTR_ID_NUM = (U2)RIM_MOD_3BRAM_OTHER_ID_NUM;

const ST_RIM_MOD_3BRAM_SIZE st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[RIM_MOD_3BRAM_OTHER_ID_NUM] = {
/*  index           size    */
/* START : ##TOOL_OUT#RIM_MOD_3B_OTR_TABLE## */
    {(U2)0U,        (U2)4U      }       /* 0    : RIMID_OTR_SAMPLE_BBB_OTH */
/* END : ##TOOL_OUT#RIM_MOD_3B_OTR_TABLE## */
};

#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  1.0.0           11/18/2014  KM      New.                                                                                         */
/*  1.1.0           03/30/2015  MH      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*  1.2.0           09/07/2015  HK      Correction of the error message                                                              */
/*                                      Condition judgment addition with the preprocessor                                            */
/*                                      Revision up by "rim_mod_3bram.c" correction                                                  */
/*  1.2.1           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.2           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.2.3           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.4            9/14/2021  TN      rim_mod_3bram.c v1.2.3 -> v1.2.4.                                                            */
/*  1.3.0            9/16/2021  TN      rim_mod_3bram.c v1.2.4 -> v1.3.0.                                                            */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, Denso                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
