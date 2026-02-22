/* 1.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3CRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3CRAM_CFG_C_MAJOR                (1U)
#define RIM_MOD_3CRAM_CFG_C_MINOR                (2U)
#define RIM_MOD_3CRAM_CFG_C_PATCH                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"

#include "rim_mod_3cram_private.h"
#include "rim_mod_3cram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_3CRAM_CFG_C_MAJOR != RIM_MOD_3CRAM_H_MAJOR) || \
     (RIM_MOD_3CRAM_CFG_C_MINOR != RIM_MOD_3CRAM_H_MINOR) || \
     (RIM_MOD_3CRAM_CFG_C_PATCH != RIM_MOD_3CRAM_H_PATCH))
#error "rim_mod_3cram_cfg.c and rim_mod_3cram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_3CRAM_CFG_C_MAJOR != RIM_MOD_3CRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_3CRAM_CFG_C_MINOR != RIM_MOD_3CRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_3CRAM_CFG_C_PATCH != RIM_MOD_3CRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_3cram_cfg.c and rim_mod_3cram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#RIM_MOD_3C_SIZE## */
#define RIM_MOD_3CRAM_U1_ID_NUM                  (1U)
#define RIM_MOD_3CRAM_U2_ID_NUM                  (2U)
#define RIM_MOD_3CRAM_U4_ID_NUM                  (2U)
#define RIM_MOD_3CRAM_OTHER_ID_NUM               (0U)
/* END : ##TOOL_OUT#RIM_MOD_3C_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_3C_OTR_TBL_SIZE## */
#define RIM_MOD_3CRAM_OTHER_BUF_NUM              (0U)
/* END : ##TOOL_OUT#RIM_MOD_3C_OTR_TBL_SIZE## */

/* Set st_d_RIM_MOD_3CRAM_OTR_SZ_CFG's max size */
/* START : ##TOOL_OUT#RIM_MOD_3C_OTR_SIZE_MAX## */
#define RIM_MOD_3CRAM_OTHER_ID_CFGMAX            (0U)
/* END : ##TOOL_OUT#RIM_MOD_3C_OTR_SIZE_MAX## */

#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
#if (RIM_MOD_3CRAM_OTHER_ID_CFGMAX > RIM_MOD_3CRAM_OTHER_ID_MAXBYTE)
#error "This buffer number isn't supported.Please contact BSW team."
#endif  /* #if (RIM_MOD_3CRAM_OTHER_ID_CFGMAX > RIM_MOD_3CRAM_OTHER_ID_MAXBYTE) */
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
U1  u1_dp_rimmod_3cram_u1buf_main[RIM_MOD_3CRAM_U1_ID_NUM]           __attribute__((section(".bss_RIM1")));
U1  u1_dp_rimmod_3cram_u1buf_mirr1[RIM_MOD_3CRAM_U1_ID_NUM]          __attribute__((section(".bss_RIM2")));
U1  u1_dp_rimmod_3cram_u1buf_mirr2[RIM_MOD_3CRAM_U1_ID_NUM]          __attribute__((section(".bss_RIM3")));
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
U2  u2_dp_rimmod_3cram_u2buf_main[RIM_MOD_3CRAM_U2_ID_NUM]           __attribute__((section(".bss_RIM1")));
U2  u2_dp_rimmod_3cram_u2buf_mirr1[RIM_MOD_3CRAM_U2_ID_NUM]          __attribute__((section(".bss_RIM2")));
U2  u2_dp_rimmod_3cram_u2buf_mirr2[RIM_MOD_3CRAM_U2_ID_NUM]          __attribute__((section(".bss_RIM3")));
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
U4  u4_dp_rimmod_3cram_u4buf_main[RIM_MOD_3CRAM_U4_ID_NUM]           __attribute__((section(".bss_RIM1")));
U4  u4_dp_rimmod_3cram_u4buf_mirr1[RIM_MOD_3CRAM_U4_ID_NUM]          __attribute__((section(".bss_RIM2")));
U4  u4_dp_rimmod_3cram_u4buf_mirr2[RIM_MOD_3CRAM_U4_ID_NUM]          __attribute__((section(".bss_RIM3")));
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
U4  u4_dp_rimmod_3cram_otrbuf_main[RIM_MOD_3CRAM_OTHER_BUF_NUM]      __attribute__((section(".bss_RIM1")));
U4  u4_dp_rimmod_3cram_otrbuf_mirr1[RIM_MOD_3CRAM_OTHER_BUF_NUM]     __attribute__((section(".bss_RIM2")));
U4  u4_dp_rimmod_3cram_otrbuf_mirr2[RIM_MOD_3CRAM_OTHER_BUF_NUM]     __attribute__((section(".bss_RIM3")));
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_d_RIM_MOD_3CRAM_DATA_ID_MASK = (U2)0x01FFU;

#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3CRAM_U1_ID_NUM = (U2)RIM_MOD_3CRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3CRAM_U2_ID_NUM = (U2)RIM_MOD_3CRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3CRAM_U4_ID_NUM = (U2)RIM_MOD_3CRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
const U2 u2_d_RIM_MOD_3CRAM_OTR_ID_NUM = (U2)RIM_MOD_3CRAM_OTHER_ID_NUM;

const ST_RIM_MOD_3CRAM_SIZE st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[RIM_MOD_3CRAM_OTHER_ID_NUM] = {
/*  index           size    */
/* START : ##TOOL_OUT#RIM_MOD_3C_OTR_TABLE## */
/* END : ##TOOL_OUT#RIM_MOD_3C_OTR_TABLE## */
};

#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */

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
/*  1.1.2           09/07/2015  HK      Correction of the error message                                                              */
/*                                      Condition judgment addition with the preprocessor                                            */
/*                                      Revision up by "rim_mod_3cram.c" correction                                                  */
/*  1.1.3           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.1.4           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.1.5           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.1.6            8/22/2017  HK      Fixed QAC warning.                                                                           */
/*  1.1.7           10/ 9/2021  TN      rim_mod_3cram.c v1.1.6 -> v1.1.7.                                                            */
/*  1.2.0           11/ 1/2021  TN      rim_mod_3cram.c v1.1.7 -> v1.2.0.                                                            */
/*  1.2.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
