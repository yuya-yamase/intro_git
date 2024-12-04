/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_1B2CRAM                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_1B2CRAM_CFG_C_MAJOR              (1U)
#define RIM_MOD_1B2CRAM_CFG_C_MINOR              (3U)
#define RIM_MOD_1B2CRAM_CFG_C_PATCH              (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"

#include "rim_mod_1b2cram_private.h"
#include "rim_mod_1b2cram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_1B2CRAM_CFG_C_MAJOR != RIM_MOD_1B2CRAM_H_MAJOR) || \
     (RIM_MOD_1B2CRAM_CFG_C_MINOR != RIM_MOD_1B2CRAM_H_MINOR) || \
     (RIM_MOD_1B2CRAM_CFG_C_PATCH != RIM_MOD_1B2CRAM_H_PATCH))
#error "rim_mod_1b2cram_cfg.c and rim_mod_1b2cram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_1B2CRAM_CFG_C_MAJOR != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_1B2CRAM_CFG_C_MINOR != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_1B2CRAM_CFG_C_PATCH != RIM_MOD_1B2CRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_1b2cram_cfg.c and rim_mod_1b2cram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#RIM_MOD_1B2C_SIZE## */
#define RIM_MOD_1B2CRAM_U1_ID_NUM                (1U)
#define RIM_MOD_1B2CRAM_U2_ID_NUM                (1U)
#define RIM_MOD_1B2CRAM_U4_ID_NUM                (1U)
/* END : ##TOOL_OUT#RIM_MOD_1B2C_SIZE## */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
U1  u1_dp_rimmod_1b2c_byte_main[RIM_MOD_1B2CRAM_U1_ID_NUM]   __attribute__((section(".bss_BACK_RIM1")));
U1  u1_dp_rimmod_1b2c_byte_mirr1[RIM_MOD_1B2CRAM_U1_ID_NUM]  __attribute__((section(".bss_RIM1")));
U1  u1_dp_rimmod_1b2c_byte_mirr2[RIM_MOD_1B2CRAM_U1_ID_NUM]  __attribute__((section(".bss_RIM2")));
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
U2  u2_dp_rimmod_1b2c_half_main[RIM_MOD_1B2CRAM_U2_ID_NUM]   __attribute__((section(".bss_BACK_RIM1")));
U2  u2_dp_rimmod_1b2c_half_mirr1[RIM_MOD_1B2CRAM_U2_ID_NUM]  __attribute__((section(".bss_RIM1")));
U2  u2_dp_rimmod_1b2c_half_mirr2[RIM_MOD_1B2CRAM_U2_ID_NUM]  __attribute__((section(".bss_RIM2")));
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
U4  u4_dp_rimmod_1b2c_word_main[RIM_MOD_1B2CRAM_U4_ID_NUM]   __attribute__((section(".bss_BACK_RIM1")));
U4  u4_dp_rimmod_1b2c_word_mirr1[RIM_MOD_1B2CRAM_U4_ID_NUM]  __attribute__((section(".bss_RIM1")));
U4  u4_dp_rimmod_1b2c_word_mirr2[RIM_MOD_1B2CRAM_U4_ID_NUM]  __attribute__((section(".bss_RIM2")));
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_d_RIM_MOD_1B2CRAM_MODULE_ID = (U2)RIM_MOD_ID_2;
const U2 u2_d_RIM_MOD_1B2CRAM_DATA_ID_MASK = (U2)0x01FFU;

#if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1B2CRAM_U1_ID_NUM = (U2)RIM_MOD_1B2CRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_1B2CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1B2CRAM_U2_ID_NUM = (U2)RIM_MOD_1B2CRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_1B2CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1B2CRAM_U4_ID_NUM = (U2)RIM_MOD_1B2CRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_1B2CRAM_U4_USE__ == TRUE) */

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
/*  1.0.0           11/17/2014  KM      New.                                                                                         */
/*  1.1.0           03/30/2015  MH      Update version check                                                                         */
/*  1.1.1           07/14/2015  HK      Comment correction                                                                           */
/*  1.2.0           09/07/2015  HK      Revision up by "rim_mod_1b2cram.c" correction                                                */
/*  1.2.1           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.2.2           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.2.3           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.2.4            9/30/2021  TN      rim_mod_1b2cram.c v1.2.3 -> v1.2.4.                                                          */
/*  1.3.0           19/ 5/2021  TN      rim_mod_1b2cram.c v1.2.4 -> v1.3.0.                                                          */
/*  1.3.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
