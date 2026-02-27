/* 1.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_1BRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_1BRAM_CFG_C_MAJOR                (1U)
#define RIM_MOD_1BRAM_CFG_C_MINOR                (2U)
#define RIM_MOD_1BRAM_CFG_C_PATCH                (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "rim_ctl.h"

#include "rim_mod_1bram_private.h"
#include "rim_mod_1bram_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((RIM_MOD_1BRAM_CFG_C_MAJOR != RIM_MOD_1BRAM_H_MAJOR) || \
     (RIM_MOD_1BRAM_CFG_C_MINOR != RIM_MOD_1BRAM_H_MINOR) || \
     (RIM_MOD_1BRAM_CFG_C_PATCH != RIM_MOD_1BRAM_H_PATCH))
#error "rim_mod_1bram_cfg.c and rim_mod_1bram_private.h : source and header files are inconsistent!"
#endif

#if ((RIM_MOD_1BRAM_CFG_C_MAJOR != RIM_MOD_1BRAM_CFG_PRIVATE_H_MAJOR) || \
     (RIM_MOD_1BRAM_CFG_C_MINOR != RIM_MOD_1BRAM_CFG_PRIVATE_H_MINOR) || \
     (RIM_MOD_1BRAM_CFG_C_PATCH != RIM_MOD_1BRAM_CFG_PRIVATE_H_PATCH))
#error "rim_mod_1bram_cfg.c and rim_mod_1bram_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* START : ##TOOL_OUT#RIM_MOD_1B_SIZE## */
#define RIM_MOD_1BRAM_U1_ID_NUM                  (67U)
#define RIM_MOD_1BRAM_U2_ID_NUM                  (1U)
#define RIM_MOD_1BRAM_U4_ID_NUM                  (2U)
#define RIM_MOD_1BRAM_OTHER_ID_NUM               (67U)
/* END : ##TOOL_OUT#RIM_MOD_1B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_TBL_SIZE## */
#define RIM_MOD_1BRAM_OTHER_BUF_NUM              (291U)
/* END : ##TOOL_OUT#RIM_MOD_1B_OTR_TBL_SIZE## */

/* Set st_d_RIM_MOD_1BRAM_OTR_SZ_CFG's max size */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_SIZE_MAX## */
#define RIM_MOD_1BRAM_OTHER_ID_CFGMAX            (32U)
/* END : ##TOOL_OUT#RIM_MOD_1B_OTR_SIZE_MAX## */

#if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE)
#if (RIM_MOD_1BRAM_OTHER_ID_CFGMAX > RIM_MOD_1BRAM_OTHER_ID_MAXBYTE)
#error "This buffer number isn't supported.Please contact BSW team."
#endif  /* #if (RIM_MOD_1BRAM_OTHER_ID_CFGMAX > RIM_MOD_1BRAM_OTHER_ID_MAXBYTE) */
#endif  /* #if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_1BRAM_U1_USE__ == TRUE)
U1  u1_dp_rimmod_1bram_u1buf_main[RIM_MOD_1BRAM_U1_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
#endif  /* #if (__RIM_MOD_1BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_U2_USE__ == TRUE)
U2  u2_dp_rimmod_1bram_u2buf_main[RIM_MOD_1BRAM_U2_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
#endif  /* #if (__RIM_MOD_1BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_U4_USE__ == TRUE)
U4  u4_dp_rimmod_1bram_u4buf_main[RIM_MOD_1BRAM_U4_ID_NUM]           __attribute__((section(".bss_BACK_RIM1")));
#endif  /* #if (__RIM_MOD_1BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE)
U4  u4_dp_rimmod_1bram_otrbuf_main[RIM_MOD_1BRAM_OTHER_BUF_NUM]      __attribute__((section(".bss_BACK_RIM1")));
#endif  /* #if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2 u2_d_RIM_MOD_1BRAM_DATA_ID_MASK = (U2)0x01FFU;

#if (__RIM_MOD_1BRAM_U1_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1BRAM_U1_ID_NUM    = (U2)RIM_MOD_1BRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_1BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_U2_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1BRAM_U2_ID_NUM    = (U2)RIM_MOD_1BRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_1BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_U4_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1BRAM_U4_ID_NUM    = (U2)RIM_MOD_1BRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_1BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE)
const U2 u2_d_RIM_MOD_1BRAM_OTHER_ID_NUM = (U2)RIM_MOD_1BRAM_OTHER_ID_NUM;

const ST_RIM_MOD_1BRAM_SIZE st_d_RIM_MOD_1BRAM_OTR_SZ_CFG[RIM_MOD_1BRAM_OTHER_ID_NUM] = {
/*  index           size    */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_TABLE## */
    {(U2)0U,        (U2)4U      },      /* 0    : RIMID_OTR_SAMPLE_B_OTH */
    {(U2)1U,        (U2)28U     },      /* 1    : RIMID_OTR_NVMC_DA_DTF_WRI_006 */
    {(U2)8U,        (U2)32U     },      /* 2    : RIMID_OTR_NVMC_DA_DTF_WRI_007 */
    {(U2)16U,       (U2)8U      },      /* 3    : RIMID_OTR_NVMC_DA_DTF_WRI_008 */
    {(U2)18U,       (U2)8U      },      /* 4    : RIMID_OTR_NVMC_DA_DTF_WRI_009 */
    {(U2)20U,       (U2)8U      },      /* 5    : RIMID_OTR_NVMC_DA_DTF_WRI_010 */
    {(U2)22U,       (U2)8U      },      /* 6    : RIMID_OTR_NVMC_DA_DTF_WRI_011 */
    {(U2)24U,       (U2)8U      },      /* 7    : RIMID_OTR_NVMC_DA_DTF_WRI_012 */
    {(U2)26U,       (U2)8U      },      /* 8    : RIMID_OTR_NVMC_DA_DTF_WRI_013 */
    {(U2)28U,       (U2)8U      },      /* 9    : RIMID_OTR_NVMC_DA_DTF_WRI_014 */
    {(U2)30U,       (U2)8U      },      /* 10   : RIMID_OTR_NVMC_DA_DTF_WRI_015 */
    {(U2)32U,       (U2)8U      },      /* 11   : RIMID_OTR_NVMC_DA_DTF_WRI_016 */
    {(U2)34U,       (U2)8U      },      /* 12   : RIMID_OTR_NVMC_DA_DTF_WRI_017 */
    {(U2)36U,       (U2)8U      },      /* 13   : RIMID_OTR_NVMC_DA_DTF_WRI_018 */
    {(U2)38U,       (U2)8U      },      /* 14   : RIMID_OTR_NVMC_DA_DTF_WRI_019 */
    {(U2)40U,       (U2)8U      },      /* 15   : RIMID_OTR_NVMC_DA_DTF_WRI_020 */
    {(U2)42U,       (U2)8U      },      /* 16   : RIMID_OTR_NVMC_DA_DTF_WRI_021 */
    {(U2)44U,       (U2)8U      },      /* 17   : RIMID_OTR_NVMC_DA_DTF_WRI_022 */
    {(U2)46U,       (U2)8U      },      /* 18   : RIMID_OTR_NVMC_DA_DTF_WRI_023 */
    {(U2)48U,       (U2)8U      },      /* 19   : RIMID_OTR_NVMC_DA_DTF_WRI_024 */
    {(U2)50U,       (U2)8U      },      /* 20   : RIMID_OTR_NVMC_DA_DTF_WRI_025 */
    {(U2)52U,       (U2)8U      },      /* 21   : RIMID_OTR_NVMC_DA_DTF_WRI_026 */
    {(U2)54U,       (U2)8U      },      /* 22   : RIMID_OTR_NVMC_DA_DTF_WRI_027 */
    {(U2)56U,       (U2)8U      },      /* 23   : RIMID_OTR_NVMC_DA_DTF_WRI_028 */
    {(U2)58U,       (U2)12U     },      /* 24   : RIMID_OTR_NVMC_DA_DTF_WRI_029 */
    {(U2)61U,       (U2)12U     },      /* 25   : RIMID_OTR_NVMC_DA_DTF_WRI_030 */
    {(U2)64U,       (U2)12U     },      /* 26   : RIMID_OTR_NVMC_DA_DTF_WRI_031 */
    {(U2)67U,       (U2)12U     },      /* 27   : RIMID_OTR_NVMC_DA_DTF_WRI_032 */
    {(U2)70U,       (U2)12U     },      /* 28   : RIMID_OTR_NVMC_DA_DTF_WRI_033 */
    {(U2)73U,       (U2)12U     },      /* 29   : RIMID_OTR_NVMC_DA_DTF_WRI_034 */
    {(U2)76U,       (U2)12U     },      /* 30   : RIMID_OTR_NVMC_DA_DTF_WRI_035 */
    {(U2)79U,       (U2)12U     },      /* 31   : RIMID_OTR_NVMC_DA_DTF_WRI_036 */
    {(U2)82U,       (U2)12U     },      /* 32   : RIMID_OTR_NVMC_DA_DTF_WRI_037 */
    {(U2)85U,       (U2)12U     },      /* 33   : RIMID_OTR_NVMC_DA_DTF_WRI_038 */
    {(U2)88U,       (U2)12U     },      /* 34   : RIMID_OTR_NVMC_DA_DTF_WRI_039 */
    {(U2)91U,       (U2)12U     },      /* 35   : RIMID_OTR_NVMC_DA_DTF_WRI_040 */
    {(U2)94U,       (U2)12U     },      /* 36   : RIMID_OTR_NVMC_DA_DTF_WRI_041 */
    {(U2)97U,       (U2)12U     },      /* 37   : RIMID_OTR_NVMC_DA_DTF_WRI_042 */
    {(U2)100U,      (U2)12U     },      /* 38   : RIMID_OTR_NVMC_DA_DTF_WRI_043 */
    {(U2)103U,      (U2)12U     },      /* 39   : RIMID_OTR_NVMC_DA_DTF_WRI_044 */
    {(U2)106U,      (U2)12U     },      /* 40   : RIMID_OTR_NVMC_DA_DTF_WRI_045 */
    {(U2)109U,      (U2)12U     },      /* 41   : RIMID_OTR_NVMC_DA_DTF_WRI_046 */
    {(U2)112U,      (U2)12U     },      /* 42   : RIMID_OTR_NVMC_DA_DTF_WRI_047 */
    {(U2)115U,      (U2)12U     },      /* 43   : RIMID_OTR_NVMC_DA_DTF_WRI_048 */
    {(U2)118U,      (U2)12U     },      /* 44   : RIMID_OTR_NVMC_DA_DTF_WRI_049 */
    {(U2)121U,      (U2)32U     },      /* 45   : RIMID_OTR_NVMC_DA_DTF_WRI_050 */
    {(U2)129U,      (U2)32U     },      /* 46   : RIMID_OTR_NVMC_DA_DTF_WRI_051 */
    {(U2)137U,      (U2)32U     },      /* 47   : RIMID_OTR_NVMC_DA_DTF_WRI_052 */
    {(U2)145U,      (U2)32U     },      /* 48   : RIMID_OTR_NVMC_DA_DTF_WRI_053 */
    {(U2)153U,      (U2)32U     },      /* 49   : RIMID_OTR_NVMC_DA_DTF_WRI_054 */
    {(U2)161U,      (U2)32U     },      /* 50   : RIMID_OTR_NVMC_DA_DTF_WRI_055 */
    {(U2)169U,      (U2)32U     },      /* 51   : RIMID_OTR_NVMC_DA_DTF_WRI_056 */
    {(U2)177U,      (U2)32U     },      /* 52   : RIMID_OTR_NVMC_DA_DTF_WRI_057 */
    {(U2)185U,      (U2)32U     },      /* 53   : RIMID_OTR_NVMC_DA_DTF_WRI_058 */
    {(U2)193U,      (U2)32U     },      /* 54   : RIMID_OTR_NVMC_DA_DTF_WRI_059 */
    {(U2)201U,      (U2)32U     },      /* 55   : RIMID_OTR_NVMC_DA_DTF_WRI_060 */
    {(U2)209U,      (U2)32U     },      /* 56   : RIMID_OTR_NVMC_DA_DTF_WRI_061 */
    {(U2)217U,      (U2)32U     },      /* 57   : RIMID_OTR_NVMC_DA_DTF_WRI_062 */
    {(U2)225U,      (U2)32U     },      /* 58   : RIMID_OTR_NVMC_DA_DTF_WRI_063 */
    {(U2)233U,      (U2)32U     },      /* 59   : RIMID_OTR_NVMC_DA_DTF_WRI_064 */
    {(U2)241U,      (U2)32U     },      /* 60   : RIMID_OTR_NVMC_DA_DTF_WRI_065 */
    {(U2)249U,      (U2)32U     },      /* 61   : RIMID_OTR_NVMC_DA_DTF_WRI_066 */
    {(U2)257U,      (U2)32U     },      /* 62   : RIMID_OTR_NVMC_DA_DTF_WRI_067 */
    {(U2)265U,      (U2)32U     },      /* 63   : RIMID_OTR_NVMC_DA_DTF_WRI_068 */
    {(U2)273U,      (U2)32U     },      /* 64   : RIMID_OTR_NVMC_DA_DTF_WRI_069 */
    {(U2)281U,      (U2)32U     },      /* 65   : RIMID_OTR_NVMC_DA_DTF_WRI_070 */
    {(U2)289U,      (U2)8U      }       /* 66   : RIMID_OTR_NVMC_DA_DTF_WRI_071 */
/* END : ##TOOL_OUT#RIM_MOD_1B_OTR_TABLE## */
};

#endif  /* #if (__RIM_MOD_1BRAM_OTHER_USE__ == TRUE) */

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
/*                                      Revision up by "rim_mod_1bram.c" correction                                                  */
/*  1.1.3           10/07/2015  HK      Expand DataID to 9bit                                                                        */
/*  1.1.4           10/22/2015  HK      Correction of the use macro name                                                             */
/*  1.1.5           02/29/2016  HK      Correspond non-library                                                                       */
/*  1.1.6           12/07/2016  HK      Fixed AIP3GBSW-25 issue.                                                                     */
/*  1.1.7            8/22/2017  HK      Fixed QAC warning.                                                                           */
/*  1.1.8           10/ 9/2021  TN      rim_mod_1bram.c v1.1.7 -> v1.1.8.                                                            */
/*  1.2.0           11/ 1/2021  TN      rim_mod_1bram.c v1.1.8 -> v1.2.0.                                                            */
/*  1.2.1           11/ 8/2023  KN      Improvement : Warning MISRA-C-Rule7.2 was fixed.                                             */
/*                                                                                                                                   */
/*  * KM      = Kazuyuki Makino, Denso Create                                                                                        */
/*  * MH      = Masayuki Hattori, Denso                                                                                              */
/*  * HK      = Hayato Kanamori, Denso Create                                                                                        */
/*  * TN      = Takashi Nagai, DENSO                                                                                                 */
/*  * KN      = Keigo Nomura   , Denso Create                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
