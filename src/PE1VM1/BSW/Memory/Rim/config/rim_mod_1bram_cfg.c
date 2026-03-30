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
#define RIM_MOD_1BRAM_U1_ID_NUM                  (252U)
#define RIM_MOD_1BRAM_U2_ID_NUM                  (0U)
#define RIM_MOD_1BRAM_U4_ID_NUM                  (32U)
#define RIM_MOD_1BRAM_OTHER_ID_NUM               (221U)
/* END : ##TOOL_OUT#RIM_MOD_1B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_TBL_SIZE## */
#define RIM_MOD_1BRAM_OTHER_BUF_NUM              (1339U)
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
    {(U2)0U,        (U2)8U      },      /* 0    : RIMID_OTR_NVMC_DA_DTF_WRI_001 */
    {(U2)2U,        (U2)32U     },      /* 1    : RIMID_OTR_NVMC_DA_DTF_WRI_002 */
    {(U2)10U,       (U2)8U      },      /* 2    : RIMID_OTR_NVMC_DA_DTF_WRI_003 */
    {(U2)12U,       (U2)8U      },      /* 3    : RIMID_OTR_NVMC_DA_DTF_WRI_004 */
    {(U2)14U,       (U2)8U      },      /* 4    : RIMID_OTR_NVMC_DA_DTF_WRI_005 */
    {(U2)16U,       (U2)8U      },      /* 5    : RIMID_OTR_NVMC_DA_DTF_WRI_006 */
    {(U2)18U,       (U2)8U      },      /* 6    : RIMID_OTR_NVMC_DA_DTF_WRI_007 */
    {(U2)20U,       (U2)8U      },      /* 7    : RIMID_OTR_NVMC_DA_DTF_WRI_008 */
    {(U2)22U,       (U2)8U      },      /* 8    : RIMID_OTR_NVMC_DA_DTF_WRI_009 */
    {(U2)24U,       (U2)8U      },      /* 9    : RIMID_OTR_NVMC_DA_DTF_WRI_010 */
    {(U2)26U,       (U2)8U      },      /* 10   : RIMID_OTR_NVMC_DA_DTF_WRI_011 */
    {(U2)28U,       (U2)8U      },      /* 11   : RIMID_OTR_NVMC_DA_DTF_WRI_012 */
    {(U2)30U,       (U2)8U      },      /* 12   : RIMID_OTR_NVMC_DA_DTF_WRI_013 */
    {(U2)32U,       (U2)8U      },      /* 13   : RIMID_OTR_NVMC_DA_DTF_WRI_014 */
    {(U2)34U,       (U2)8U      },      /* 14   : RIMID_OTR_NVMC_DA_DTF_WRI_015 */
    {(U2)36U,       (U2)8U      },      /* 15   : RIMID_OTR_NVMC_DA_DTF_WRI_016 */
    {(U2)38U,       (U2)8U      },      /* 16   : RIMID_OTR_NVMC_DA_DTF_WRI_017 */
    {(U2)40U,       (U2)8U      },      /* 17   : RIMID_OTR_NVMC_DA_DTF_WRI_018 */
    {(U2)42U,       (U2)8U      },      /* 18   : RIMID_OTR_NVMC_DA_DTF_WRI_019 */
    {(U2)44U,       (U2)8U      },      /* 19   : RIMID_OTR_NVMC_DA_DTF_WRI_020 */
    {(U2)46U,       (U2)8U      },      /* 20   : RIMID_OTR_NVMC_DA_DTF_WRI_021 */
    {(U2)48U,       (U2)8U      },      /* 21   : RIMID_OTR_NVMC_DA_DTF_WRI_022 */
    {(U2)50U,       (U2)8U      },      /* 22   : RIMID_OTR_NVMC_DA_DTF_WRI_023 */
    {(U2)52U,       (U2)12U     },      /* 23   : RIMID_OTR_NVMC_DA_DTF_WRI_024 */
    {(U2)55U,       (U2)12U     },      /* 24   : RIMID_OTR_NVMC_DA_DTF_WRI_025 */
    {(U2)58U,       (U2)12U     },      /* 25   : RIMID_OTR_NVMC_DA_DTF_WRI_026 */
    {(U2)61U,       (U2)12U     },      /* 26   : RIMID_OTR_NVMC_DA_DTF_WRI_027 */
    {(U2)64U,       (U2)12U     },      /* 27   : RIMID_OTR_NVMC_DA_DTF_WRI_028 */
    {(U2)67U,       (U2)12U     },      /* 28   : RIMID_OTR_NVMC_DA_DTF_WRI_029 */
    {(U2)70U,       (U2)12U     },      /* 29   : RIMID_OTR_NVMC_DA_DTF_WRI_030 */
    {(U2)73U,       (U2)12U     },      /* 30   : RIMID_OTR_NVMC_DA_DTF_WRI_031 */
    {(U2)76U,       (U2)12U     },      /* 31   : RIMID_OTR_NVMC_DA_DTF_WRI_032 */
    {(U2)79U,       (U2)12U     },      /* 32   : RIMID_OTR_NVMC_DA_DTF_WRI_033 */
    {(U2)82U,       (U2)12U     },      /* 33   : RIMID_OTR_NVMC_DA_DTF_WRI_034 */
    {(U2)85U,       (U2)12U     },      /* 34   : RIMID_OTR_NVMC_DA_DTF_WRI_035 */
    {(U2)88U,       (U2)12U     },      /* 35   : RIMID_OTR_NVMC_DA_DTF_WRI_036 */
    {(U2)91U,       (U2)12U     },      /* 36   : RIMID_OTR_NVMC_DA_DTF_WRI_037 */
    {(U2)94U,       (U2)12U     },      /* 37   : RIMID_OTR_NVMC_DA_DTF_WRI_038 */
    {(U2)97U,       (U2)12U     },      /* 38   : RIMID_OTR_NVMC_DA_DTF_WRI_039 */
    {(U2)100U,      (U2)12U     },      /* 39   : RIMID_OTR_NVMC_DA_DTF_WRI_040 */
    {(U2)103U,      (U2)12U     },      /* 40   : RIMID_OTR_NVMC_DA_DTF_WRI_041 */
    {(U2)106U,      (U2)12U     },      /* 41   : RIMID_OTR_NVMC_DA_DTF_WRI_042 */
    {(U2)109U,      (U2)12U     },      /* 42   : RIMID_OTR_NVMC_DA_DTF_WRI_043 */
    {(U2)112U,      (U2)12U     },      /* 43   : RIMID_OTR_NVMC_DA_DTF_WRI_044 */
    {(U2)115U,      (U2)32U     },      /* 44   : RIMID_OTR_NVMC_DA_DTF_WRI_045 */
    {(U2)123U,      (U2)32U     },      /* 45   : RIMID_OTR_NVMC_DA_DTF_WRI_046 */
    {(U2)131U,      (U2)32U     },      /* 46   : RIMID_OTR_NVMC_DA_DTF_WRI_047 */
    {(U2)139U,      (U2)32U     },      /* 47   : RIMID_OTR_NVMC_DA_DTF_WRI_048 */
    {(U2)147U,      (U2)32U     },      /* 48   : RIMID_OTR_NVMC_DA_DTF_WRI_049 */
    {(U2)155U,      (U2)32U     },      /* 49   : RIMID_OTR_NVMC_DA_DTF_WRI_050 */
    {(U2)163U,      (U2)32U     },      /* 50   : RIMID_OTR_NVMC_DA_DTF_WRI_051 */
    {(U2)171U,      (U2)32U     },      /* 51   : RIMID_OTR_NVMC_DA_DTF_WRI_052 */
    {(U2)179U,      (U2)32U     },      /* 52   : RIMID_OTR_NVMC_DA_DTF_WRI_053 */
    {(U2)187U,      (U2)32U     },      /* 53   : RIMID_OTR_NVMC_DA_DTF_WRI_054 */
    {(U2)195U,      (U2)32U     },      /* 54   : RIMID_OTR_NVMC_DA_DTF_WRI_055 */
    {(U2)203U,      (U2)32U     },      /* 55   : RIMID_OTR_NVMC_DA_DTF_WRI_056 */
    {(U2)211U,      (U2)32U     },      /* 56   : RIMID_OTR_NVMC_DA_DTF_WRI_057 */
    {(U2)219U,      (U2)32U     },      /* 57   : RIMID_OTR_NVMC_DA_DTF_WRI_058 */
    {(U2)227U,      (U2)32U     },      /* 58   : RIMID_OTR_NVMC_DA_DTF_WRI_059 */
    {(U2)235U,      (U2)32U     },      /* 59   : RIMID_OTR_NVMC_DA_DTF_WRI_060 */
    {(U2)243U,      (U2)32U     },      /* 60   : RIMID_OTR_NVMC_DA_DTF_WRI_061 */
    {(U2)251U,      (U2)32U     },      /* 61   : RIMID_OTR_NVMC_DA_DTF_WRI_062 */
    {(U2)259U,      (U2)32U     },      /* 62   : RIMID_OTR_NVMC_DA_DTF_WRI_063 */
    {(U2)267U,      (U2)32U     },      /* 63   : RIMID_OTR_NVMC_DA_DTF_WRI_064 */
    {(U2)275U,      (U2)32U     },      /* 64   : RIMID_OTR_NVMC_DA_DTF_WRI_065 */
    {(U2)283U,      (U2)8U      },      /* 65   : RIMID_OTR_NVMC_DA_DTF_WRI_066 */
    {(U2)285U,      (U2)8U      },      /* 66   : RIMID_OTR_NVMC_DA_DTF_WRI_074 */
    {(U2)287U,      (U2)8U      },      /* 67   : RIMID_OTR_NVMC_DA_DTF_WRI_075 */
    {(U2)289U,      (U2)8U      },      /* 68   : RIMID_OTR_NVMC_DA_DTF_WRI_076 */
    {(U2)291U,      (U2)8U      },      /* 69   : RIMID_OTR_NVMC_DA_DTF_WRI_077 */
    {(U2)293U,      (U2)8U      },      /* 70   : RIMID_OTR_NVMC_DA_DTF_WRI_078 */
    {(U2)295U,      (U2)8U      },      /* 71   : RIMID_OTR_NVMC_DA_DTF_WRI_079 */
    {(U2)297U,      (U2)32U     },      /* 72   : RIMID_OTR_NVMC_DA_DTF_WRI_080 */
    {(U2)305U,      (U2)32U     },      /* 73   : RIMID_OTR_NVMC_DA_DTF_WRI_081 */
    {(U2)313U,      (U2)32U     },      /* 74   : RIMID_OTR_NVMC_DA_DTF_WRI_082 */
    {(U2)321U,      (U2)32U     },      /* 75   : RIMID_OTR_NVMC_DA_DTF_WRI_083 */
    {(U2)329U,      (U2)32U     },      /* 76   : RIMID_OTR_NVMC_DA_DTF_WRI_084 */
    {(U2)337U,      (U2)32U     },      /* 77   : RIMID_OTR_NVMC_DA_DTF_WRI_085 */
    {(U2)345U,      (U2)32U     },      /* 78   : RIMID_OTR_NVMC_DA_DTF_WRI_086 */
    {(U2)353U,      (U2)32U     },      /* 79   : RIMID_OTR_NVMC_DA_DTF_WRI_087 */
    {(U2)361U,      (U2)32U     },      /* 80   : RIMID_OTR_NVMC_DA_DTF_WRI_088 */
    {(U2)369U,      (U2)32U     },      /* 81   : RIMID_OTR_NVMC_DA_DTF_WRI_089 */
    {(U2)377U,      (U2)32U     },      /* 82   : RIMID_OTR_NVMC_DA_DTF_WRI_090 */
    {(U2)385U,      (U2)32U     },      /* 83   : RIMID_OTR_NVMC_DA_DTF_WRI_091 */
    {(U2)393U,      (U2)32U     },      /* 84   : RIMID_OTR_NVMC_DA_DTF_WRI_092 */
    {(U2)401U,      (U2)32U     },      /* 85   : RIMID_OTR_NVMC_DA_DTF_WRI_093 */
    {(U2)409U,      (U2)32U     },      /* 86   : RIMID_OTR_NVMC_DA_DTF_WRI_094 */
    {(U2)417U,      (U2)32U     },      /* 87   : RIMID_OTR_NVMC_DA_DTF_WRI_095 */
    {(U2)425U,      (U2)32U     },      /* 88   : RIMID_OTR_NVMC_DA_DTF_WRI_096 */
    {(U2)433U,      (U2)32U     },      /* 89   : RIMID_OTR_NVMC_DA_DTF_WRI_097 */
    {(U2)441U,      (U2)32U     },      /* 90   : RIMID_OTR_NVMC_DA_DTF_WRI_098 */
    {(U2)449U,      (U2)32U     },      /* 91   : RIMID_OTR_NVMC_DA_DTF_WRI_099 */
    {(U2)457U,      (U2)32U     },      /* 92   : RIMID_OTR_NVMC_DA_DTF_WRI_100 */
    {(U2)465U,      (U2)32U     },      /* 93   : RIMID_OTR_NVMC_DA_DTF_WRI_101 */
    {(U2)473U,      (U2)32U     },      /* 94   : RIMID_OTR_NVMC_DA_DTF_WRI_102 */
    {(U2)481U,      (U2)32U     },      /* 95   : RIMID_OTR_NVMC_DA_DTF_WRI_103 */
    {(U2)489U,      (U2)32U     },      /* 96   : RIMID_OTR_NVMC_DA_DTF_WRI_104 */
    {(U2)497U,      (U2)32U     },      /* 97   : RIMID_OTR_NVMC_DA_DTF_WRI_105 */
    {(U2)505U,      (U2)32U     },      /* 98   : RIMID_OTR_NVMC_DA_DTF_WRI_106 */
    {(U2)513U,      (U2)32U     },      /* 99   : RIMID_OTR_NVMC_DA_DTF_WRI_107 */
    {(U2)521U,      (U2)32U     },      /* 100  : RIMID_OTR_NVMC_DA_DTF_WRI_108 */
    {(U2)529U,      (U2)32U     },      /* 101  : RIMID_OTR_NVMC_DA_DTF_WRI_109 */
    {(U2)537U,      (U2)32U     },      /* 102  : RIMID_OTR_NVMC_DA_DTF_WRI_110 */
    {(U2)545U,      (U2)32U     },      /* 103  : RIMID_OTR_NVMC_DA_DTF_WRI_111 */
    {(U2)553U,      (U2)32U     },      /* 104  : RIMID_OTR_NVMC_DA_DTF_WRI_112 */
    {(U2)561U,      (U2)32U     },      /* 105  : RIMID_OTR_NVMC_DA_DTF_WRI_113 */
    {(U2)569U,      (U2)32U     },      /* 106  : RIMID_OTR_NVMC_DA_DTF_WRI_114 */
    {(U2)577U,      (U2)32U     },      /* 107  : RIMID_OTR_NVMC_DA_DTF_WRI_115 */
    {(U2)585U,      (U2)32U     },      /* 108  : RIMID_OTR_NVMC_DA_DTF_WRI_116 */
    {(U2)593U,      (U2)32U     },      /* 109  : RIMID_OTR_NVMC_DA_DTF_WRI_117 */
    {(U2)601U,      (U2)32U     },      /* 110  : RIMID_OTR_NVMC_DA_DTF_WRI_118 */
    {(U2)609U,      (U2)32U     },      /* 111  : RIMID_OTR_NVMC_DA_DTF_WRI_119 */
    {(U2)617U,      (U2)32U     },      /* 112  : RIMID_OTR_NVMC_DA_DTF_WRI_120 */
    {(U2)625U,      (U2)32U     },      /* 113  : RIMID_OTR_NVMC_DA_DTF_WRI_121 */
    {(U2)633U,      (U2)32U     },      /* 114  : RIMID_OTR_NVMC_DA_DTF_WRI_122 */
    {(U2)641U,      (U2)32U     },      /* 115  : RIMID_OTR_NVMC_DA_DTF_WRI_123 */
    {(U2)649U,      (U2)32U     },      /* 116  : RIMID_OTR_NVMC_DA_DTF_WRI_124 */
    {(U2)657U,      (U2)32U     },      /* 117  : RIMID_OTR_NVMC_DA_DTF_WRI_125 */
    {(U2)665U,      (U2)32U     },      /* 118  : RIMID_OTR_NVMC_DA_DTF_WRI_126 */
    {(U2)673U,      (U2)32U     },      /* 119  : RIMID_OTR_NVMC_DA_DTF_WRI_127 */
    {(U2)681U,      (U2)32U     },      /* 120  : RIMID_OTR_NVMC_DA_DTF_WRI_128 */
    {(U2)689U,      (U2)32U     },      /* 121  : RIMID_OTR_NVMC_DA_DTF_WRI_129 */
    {(U2)697U,      (U2)32U     },      /* 122  : RIMID_OTR_NVMC_DA_DTF_WRI_130 */
    {(U2)705U,      (U2)32U     },      /* 123  : RIMID_OTR_NVMC_DA_DTF_WRI_131 */
    {(U2)713U,      (U2)32U     },      /* 124  : RIMID_OTR_NVMC_DA_DTF_WRI_132 */
    {(U2)721U,      (U2)32U     },      /* 125  : RIMID_OTR_NVMC_DA_DTF_WRI_133 */
    {(U2)729U,      (U2)8U      },      /* 126  : RIMID_OTR_NVMC_DA_DTF_WRI_136 */
    {(U2)731U,      (U2)8U      },      /* 127  : RIMID_OTR_NVMC_DA_DTF_WRI_137 */
    {(U2)733U,      (U2)32U     },      /* 128  : RIMID_OTR_NVMC_DA_DTF_WRI_138 */
    {(U2)741U,      (U2)32U     },      /* 129  : RIMID_OTR_NVMC_DA_DTF_WRI_139 */
    {(U2)749U,      (U2)8U      },      /* 130  : RIMID_OTR_NVMC_DA_DTF_WRI_142 */
    {(U2)751U,      (U2)8U      },      /* 131  : RIMID_OTR_NVMC_DA_DTF_WRI_143 */
    {(U2)753U,      (U2)32U     },      /* 132  : RIMID_OTR_NVMC_DA_DTF_WRI_144 */
    {(U2)761U,      (U2)32U     },      /* 133  : RIMID_OTR_NVMC_DA_DTF_WRI_145 */
    {(U2)769U,      (U2)32U     },      /* 134  : RIMID_OTR_NVMC_DA_DTF_WRI_146 */
    {(U2)777U,      (U2)32U     },      /* 135  : RIMID_OTR_NVMC_DA_DTF_WRI_147 */
    {(U2)785U,      (U2)8U      },      /* 136  : RIMID_OTR_NVMC_DA_DTF_WRI_168 */
    {(U2)787U,      (U2)8U      },      /* 137  : RIMID_OTR_NVMC_DA_DTF_WRI_169 */
    {(U2)789U,      (U2)8U      },      /* 138  : RIMID_OTR_NVMC_DA_DTF_WRI_170 */
    {(U2)791U,      (U2)8U      },      /* 139  : RIMID_OTR_NVMC_DA_DTF_WRI_171 */
    {(U2)793U,      (U2)8U      },      /* 140  : RIMID_OTR_NVMC_DA_DTF_WRI_172 */
    {(U2)795U,      (U2)8U      },      /* 141  : RIMID_OTR_NVMC_DA_DTF_WRI_173 */
    {(U2)797U,      (U2)8U      },      /* 142  : RIMID_OTR_NVMC_DA_DTF_WRI_174 */
    {(U2)799U,      (U2)8U      },      /* 143  : RIMID_OTR_NVMC_DA_DTF_WRI_175 */
    {(U2)801U,      (U2)8U      },      /* 144  : RIMID_OTR_NVMC_DA_DTF_WRI_176 */
    {(U2)803U,      (U2)8U      },      /* 145  : RIMID_OTR_NVMC_DA_DTF_WRI_177 */
    {(U2)805U,      (U2)8U      },      /* 146  : RIMID_OTR_NVMC_DA_DTF_WRI_178 */
    {(U2)807U,      (U2)8U      },      /* 147  : RIMID_OTR_NVMC_DA_DTF_WRI_179 */
    {(U2)809U,      (U2)8U      },      /* 148  : RIMID_OTR_NVMC_DA_DTF_WRI_180 */
    {(U2)811U,      (U2)8U      },      /* 149  : RIMID_OTR_NVMC_DA_DTF_WRI_181 */
    {(U2)813U,      (U2)8U      },      /* 150  : RIMID_OTR_NVMC_DA_DTF_WRI_182 */
    {(U2)815U,      (U2)8U      },      /* 151  : RIMID_OTR_NVMC_DA_DTF_WRI_183 */
    {(U2)817U,      (U2)8U      },      /* 152  : RIMID_OTR_NVMC_DA_DTF_WRI_184 */
    {(U2)819U,      (U2)8U      },      /* 153  : RIMID_OTR_NVMC_DA_DTF_WRI_185 */
    {(U2)821U,      (U2)8U      },      /* 154  : RIMID_OTR_NVMC_DA_DTF_WRI_186 */
    {(U2)823U,      (U2)8U      },      /* 155  : RIMID_OTR_NVMC_DA_DTF_WRI_187 */
    {(U2)825U,      (U2)32U     },      /* 156  : RIMID_OTR_NVMC_DA_DTF_WRI_188 */
    {(U2)833U,      (U2)32U     },      /* 157  : RIMID_OTR_NVMC_DA_DTF_WRI_189 */
    {(U2)841U,      (U2)32U     },      /* 158  : RIMID_OTR_NVMC_DA_DTF_WRI_190 */
    {(U2)849U,      (U2)32U     },      /* 159  : RIMID_OTR_NVMC_DA_DTF_WRI_191 */
    {(U2)857U,      (U2)32U     },      /* 160  : RIMID_OTR_NVMC_DA_DTF_WRI_192 */
    {(U2)865U,      (U2)32U     },      /* 161  : RIMID_OTR_NVMC_DA_DTF_WRI_193 */
    {(U2)873U,      (U2)32U     },      /* 162  : RIMID_OTR_NVMC_DA_DTF_WRI_194 */
    {(U2)881U,      (U2)32U     },      /* 163  : RIMID_OTR_NVMC_DA_DTF_WRI_195 */
    {(U2)889U,      (U2)32U     },      /* 164  : RIMID_OTR_NVMC_DA_DTF_WRI_196 */
    {(U2)897U,      (U2)32U     },      /* 165  : RIMID_OTR_NVMC_DA_DTF_WRI_197 */
    {(U2)905U,      (U2)32U     },      /* 166  : RIMID_OTR_NVMC_DA_DTF_WRI_198 */
    {(U2)913U,      (U2)32U     },      /* 167  : RIMID_OTR_NVMC_DA_DTF_WRI_199 */
    {(U2)921U,      (U2)32U     },      /* 168  : RIMID_OTR_NVMC_DA_DTF_WRI_200 */
    {(U2)929U,      (U2)32U     },      /* 169  : RIMID_OTR_NVMC_DA_DTF_WRI_201 */
    {(U2)937U,      (U2)32U     },      /* 170  : RIMID_OTR_NVMC_DA_DTF_WRI_202 */
    {(U2)945U,      (U2)32U     },      /* 171  : RIMID_OTR_NVMC_DA_DTF_WRI_203 */
    {(U2)953U,      (U2)32U     },      /* 172  : RIMID_OTR_NVMC_DA_DTF_WRI_204 */
    {(U2)961U,      (U2)32U     },      /* 173  : RIMID_OTR_NVMC_DA_DTF_WRI_205 */
    {(U2)969U,      (U2)32U     },      /* 174  : RIMID_OTR_NVMC_DA_DTF_WRI_206 */
    {(U2)977U,      (U2)32U     },      /* 175  : RIMID_OTR_NVMC_DA_DTF_WRI_207 */
    {(U2)985U,      (U2)32U     },      /* 176  : RIMID_OTR_NVMC_DA_DTF_WRI_208 */
    {(U2)993U,      (U2)32U     },      /* 177  : RIMID_OTR_NVMC_DA_DTF_WRI_209 */
    {(U2)1001U,     (U2)32U     },      /* 178  : RIMID_OTR_NVMC_DA_DTF_WRI_210 */
    {(U2)1009U,     (U2)32U     },      /* 179  : RIMID_OTR_NVMC_DA_DTF_WRI_211 */
    {(U2)1017U,     (U2)32U     },      /* 180  : RIMID_OTR_NVMC_DA_DTF_WRI_212 */
    {(U2)1025U,     (U2)32U     },      /* 181  : RIMID_OTR_NVMC_DA_DTF_WRI_213 */
    {(U2)1033U,     (U2)32U     },      /* 182  : RIMID_OTR_NVMC_DA_DTF_WRI_214 */
    {(U2)1041U,     (U2)32U     },      /* 183  : RIMID_OTR_NVMC_DA_DTF_WRI_215 */
    {(U2)1049U,     (U2)32U     },      /* 184  : RIMID_OTR_NVMC_DA_DTF_WRI_216 */
    {(U2)1057U,     (U2)32U     },      /* 185  : RIMID_OTR_NVMC_DA_DTF_WRI_217 */
    {(U2)1065U,     (U2)32U     },      /* 186  : RIMID_OTR_NVMC_DA_DTF_WRI_218 */
    {(U2)1073U,     (U2)32U     },      /* 187  : RIMID_OTR_NVMC_DA_DTF_WRI_219 */
    {(U2)1081U,     (U2)32U     },      /* 188  : RIMID_OTR_NVMC_DA_DTF_WRI_220 */
    {(U2)1089U,     (U2)32U     },      /* 189  : RIMID_OTR_NVMC_DA_DTF_WRI_221 */
    {(U2)1097U,     (U2)32U     },      /* 190  : RIMID_OTR_NVMC_DA_DTF_WRI_222 */
    {(U2)1105U,     (U2)32U     },      /* 191  : RIMID_OTR_NVMC_DA_DTF_WRI_223 */
    {(U2)1113U,     (U2)32U     },      /* 192  : RIMID_OTR_NVMC_DA_DTF_WRI_224 */
    {(U2)1121U,     (U2)32U     },      /* 193  : RIMID_OTR_NVMC_DA_DTF_WRI_225 */
    {(U2)1129U,     (U2)32U     },      /* 194  : RIMID_OTR_NVMC_DA_DTF_WRI_226 */
    {(U2)1137U,     (U2)32U     },      /* 195  : RIMID_OTR_NVMC_DA_DTF_WRI_227 */
    {(U2)1145U,     (U2)32U     },      /* 196  : RIMID_OTR_NVMC_DA_DTF_WRI_228 */
    {(U2)1153U,     (U2)32U     },      /* 197  : RIMID_OTR_NVMC_DA_DTF_WRI_229 */
    {(U2)1161U,     (U2)32U     },      /* 198  : RIMID_OTR_NVMC_DA_DTF_WRI_230 */
    {(U2)1169U,     (U2)32U     },      /* 199  : RIMID_OTR_NVMC_DA_DTF_WRI_231 */
    {(U2)1177U,     (U2)32U     },      /* 200  : RIMID_OTR_NVMC_DA_DTF_WRI_232 */
    {(U2)1185U,     (U2)32U     },      /* 201  : RIMID_OTR_NVMC_DA_DTF_WRI_233 */
    {(U2)1193U,     (U2)32U     },      /* 202  : RIMID_OTR_NVMC_DA_DTF_WRI_234 */
    {(U2)1201U,     (U2)32U     },      /* 203  : RIMID_OTR_NVMC_DA_DTF_WRI_235 */
    {(U2)1209U,     (U2)32U     },      /* 204  : RIMID_OTR_NVMC_DA_DTF_WRI_236 */
    {(U2)1217U,     (U2)32U     },      /* 205  : RIMID_OTR_NVMC_DA_DTF_WRI_237 */
    {(U2)1225U,     (U2)32U     },      /* 206  : RIMID_OTR_NVMC_DA_DTF_WRI_238 */
    {(U2)1233U,     (U2)32U     },      /* 207  : RIMID_OTR_NVMC_DA_DTF_WRI_239 */
    {(U2)1241U,     (U2)32U     },      /* 208  : RIMID_OTR_NVMC_DA_DTF_WRI_240 */
    {(U2)1249U,     (U2)32U     },      /* 209  : RIMID_OTR_NVMC_DA_DTF_WRI_241 */
    {(U2)1257U,     (U2)32U     },      /* 210  : RIMID_OTR_NVMC_DA_DTF_WRI_242 */
    {(U2)1265U,     (U2)32U     },      /* 211  : RIMID_OTR_NVMC_DA_DTF_WRI_243 */
    {(U2)1273U,     (U2)32U     },      /* 212  : RIMID_OTR_NVMC_DA_DTF_WRI_244 */
    {(U2)1281U,     (U2)32U     },      /* 213  : RIMID_OTR_NVMC_DA_DTF_WRI_245 */
    {(U2)1289U,     (U2)32U     },      /* 214  : RIMID_OTR_NVMC_DA_DTF_WRI_246 */
    {(U2)1297U,     (U2)32U     },      /* 215  : RIMID_OTR_NVMC_DA_DTF_WRI_247 */
    {(U2)1305U,     (U2)32U     },      /* 216  : RIMID_OTR_NVMC_DA_DTF_WRI_248 */
    {(U2)1313U,     (U2)32U     },      /* 217  : RIMID_OTR_NVMC_DA_DTF_WRI_249 */
    {(U2)1321U,     (U2)32U     },      /* 218  : RIMID_OTR_NVMC_DA_DTF_WRI_250 */
    {(U2)1329U,     (U2)8U      },      /* 219  : RIMID_OTR_NVMC_DA_DTF_WRI_252 */
    {(U2)1331U,     (U2)32U     }       /* 220  : RIMID_OTR_NVMC_DA_DTF_WRI_253 */
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
