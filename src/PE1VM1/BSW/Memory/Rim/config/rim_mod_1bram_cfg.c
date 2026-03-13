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
#define RIM_MOD_1BRAM_U1_ID_NUM                  (253U)
#define RIM_MOD_1BRAM_U2_ID_NUM                  (1U)
#define RIM_MOD_1BRAM_U4_ID_NUM                  (33U)
#define RIM_MOD_1BRAM_OTHER_ID_NUM               (222U)
/* END : ##TOOL_OUT#RIM_MOD_1B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_TBL_SIZE## */
#define RIM_MOD_1BRAM_OTHER_BUF_NUM              (1340U)
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
    {(U2)1U,        (U2)8U      },      /* 1    : RIMID_OTR_NVMC_DA_DTF_WRI_006 */
    {(U2)3U,        (U2)32U     },      /* 2    : RIMID_OTR_NVMC_DA_DTF_WRI_007 */
    {(U2)11U,       (U2)8U      },      /* 3    : RIMID_OTR_NVMC_DA_DTF_WRI_008 */
    {(U2)13U,       (U2)8U      },      /* 4    : RIMID_OTR_NVMC_DA_DTF_WRI_009 */
    {(U2)15U,       (U2)8U      },      /* 5    : RIMID_OTR_NVMC_DA_DTF_WRI_010 */
    {(U2)17U,       (U2)8U      },      /* 6    : RIMID_OTR_NVMC_DA_DTF_WRI_011 */
    {(U2)19U,       (U2)8U      },      /* 7    : RIMID_OTR_NVMC_DA_DTF_WRI_012 */
    {(U2)21U,       (U2)8U      },      /* 8    : RIMID_OTR_NVMC_DA_DTF_WRI_013 */
    {(U2)23U,       (U2)8U      },      /* 9    : RIMID_OTR_NVMC_DA_DTF_WRI_014 */
    {(U2)25U,       (U2)8U      },      /* 10   : RIMID_OTR_NVMC_DA_DTF_WRI_015 */
    {(U2)27U,       (U2)8U      },      /* 11   : RIMID_OTR_NVMC_DA_DTF_WRI_016 */
    {(U2)29U,       (U2)8U      },      /* 12   : RIMID_OTR_NVMC_DA_DTF_WRI_017 */
    {(U2)31U,       (U2)8U      },      /* 13   : RIMID_OTR_NVMC_DA_DTF_WRI_018 */
    {(U2)33U,       (U2)8U      },      /* 14   : RIMID_OTR_NVMC_DA_DTF_WRI_019 */
    {(U2)35U,       (U2)8U      },      /* 15   : RIMID_OTR_NVMC_DA_DTF_WRI_020 */
    {(U2)37U,       (U2)8U      },      /* 16   : RIMID_OTR_NVMC_DA_DTF_WRI_021 */
    {(U2)39U,       (U2)8U      },      /* 17   : RIMID_OTR_NVMC_DA_DTF_WRI_022 */
    {(U2)41U,       (U2)8U      },      /* 18   : RIMID_OTR_NVMC_DA_DTF_WRI_023 */
    {(U2)43U,       (U2)8U      },      /* 19   : RIMID_OTR_NVMC_DA_DTF_WRI_024 */
    {(U2)45U,       (U2)8U      },      /* 20   : RIMID_OTR_NVMC_DA_DTF_WRI_025 */
    {(U2)47U,       (U2)8U      },      /* 21   : RIMID_OTR_NVMC_DA_DTF_WRI_026 */
    {(U2)49U,       (U2)8U      },      /* 22   : RIMID_OTR_NVMC_DA_DTF_WRI_027 */
    {(U2)51U,       (U2)8U      },      /* 23   : RIMID_OTR_NVMC_DA_DTF_WRI_028 */
    {(U2)53U,       (U2)12U     },      /* 24   : RIMID_OTR_NVMC_DA_DTF_WRI_029 */
    {(U2)56U,       (U2)12U     },      /* 25   : RIMID_OTR_NVMC_DA_DTF_WRI_030 */
    {(U2)59U,       (U2)12U     },      /* 26   : RIMID_OTR_NVMC_DA_DTF_WRI_031 */
    {(U2)62U,       (U2)12U     },      /* 27   : RIMID_OTR_NVMC_DA_DTF_WRI_032 */
    {(U2)65U,       (U2)12U     },      /* 28   : RIMID_OTR_NVMC_DA_DTF_WRI_033 */
    {(U2)68U,       (U2)12U     },      /* 29   : RIMID_OTR_NVMC_DA_DTF_WRI_034 */
    {(U2)71U,       (U2)12U     },      /* 30   : RIMID_OTR_NVMC_DA_DTF_WRI_035 */
    {(U2)74U,       (U2)12U     },      /* 31   : RIMID_OTR_NVMC_DA_DTF_WRI_036 */
    {(U2)77U,       (U2)12U     },      /* 32   : RIMID_OTR_NVMC_DA_DTF_WRI_037 */
    {(U2)80U,       (U2)12U     },      /* 33   : RIMID_OTR_NVMC_DA_DTF_WRI_038 */
    {(U2)83U,       (U2)12U     },      /* 34   : RIMID_OTR_NVMC_DA_DTF_WRI_039 */
    {(U2)86U,       (U2)12U     },      /* 35   : RIMID_OTR_NVMC_DA_DTF_WRI_040 */
    {(U2)89U,       (U2)12U     },      /* 36   : RIMID_OTR_NVMC_DA_DTF_WRI_041 */
    {(U2)92U,       (U2)12U     },      /* 37   : RIMID_OTR_NVMC_DA_DTF_WRI_042 */
    {(U2)95U,       (U2)12U     },      /* 38   : RIMID_OTR_NVMC_DA_DTF_WRI_043 */
    {(U2)98U,       (U2)12U     },      /* 39   : RIMID_OTR_NVMC_DA_DTF_WRI_044 */
    {(U2)101U,      (U2)12U     },      /* 40   : RIMID_OTR_NVMC_DA_DTF_WRI_045 */
    {(U2)104U,      (U2)12U     },      /* 41   : RIMID_OTR_NVMC_DA_DTF_WRI_046 */
    {(U2)107U,      (U2)12U     },      /* 42   : RIMID_OTR_NVMC_DA_DTF_WRI_047 */
    {(U2)110U,      (U2)12U     },      /* 43   : RIMID_OTR_NVMC_DA_DTF_WRI_048 */
    {(U2)113U,      (U2)12U     },      /* 44   : RIMID_OTR_NVMC_DA_DTF_WRI_049 */
    {(U2)116U,      (U2)32U     },      /* 45   : RIMID_OTR_NVMC_DA_DTF_WRI_050 */
    {(U2)124U,      (U2)32U     },      /* 46   : RIMID_OTR_NVMC_DA_DTF_WRI_051 */
    {(U2)132U,      (U2)32U     },      /* 47   : RIMID_OTR_NVMC_DA_DTF_WRI_052 */
    {(U2)140U,      (U2)32U     },      /* 48   : RIMID_OTR_NVMC_DA_DTF_WRI_053 */
    {(U2)148U,      (U2)32U     },      /* 49   : RIMID_OTR_NVMC_DA_DTF_WRI_054 */
    {(U2)156U,      (U2)32U     },      /* 50   : RIMID_OTR_NVMC_DA_DTF_WRI_055 */
    {(U2)164U,      (U2)32U     },      /* 51   : RIMID_OTR_NVMC_DA_DTF_WRI_056 */
    {(U2)172U,      (U2)32U     },      /* 52   : RIMID_OTR_NVMC_DA_DTF_WRI_057 */
    {(U2)180U,      (U2)32U     },      /* 53   : RIMID_OTR_NVMC_DA_DTF_WRI_058 */
    {(U2)188U,      (U2)32U     },      /* 54   : RIMID_OTR_NVMC_DA_DTF_WRI_059 */
    {(U2)196U,      (U2)32U     },      /* 55   : RIMID_OTR_NVMC_DA_DTF_WRI_060 */
    {(U2)204U,      (U2)32U     },      /* 56   : RIMID_OTR_NVMC_DA_DTF_WRI_061 */
    {(U2)212U,      (U2)32U     },      /* 57   : RIMID_OTR_NVMC_DA_DTF_WRI_062 */
    {(U2)220U,      (U2)32U     },      /* 58   : RIMID_OTR_NVMC_DA_DTF_WRI_063 */
    {(U2)228U,      (U2)32U     },      /* 59   : RIMID_OTR_NVMC_DA_DTF_WRI_064 */
    {(U2)236U,      (U2)32U     },      /* 60   : RIMID_OTR_NVMC_DA_DTF_WRI_065 */
    {(U2)244U,      (U2)32U     },      /* 61   : RIMID_OTR_NVMC_DA_DTF_WRI_066 */
    {(U2)252U,      (U2)32U     },      /* 62   : RIMID_OTR_NVMC_DA_DTF_WRI_067 */
    {(U2)260U,      (U2)32U     },      /* 63   : RIMID_OTR_NVMC_DA_DTF_WRI_068 */
    {(U2)268U,      (U2)32U     },      /* 64   : RIMID_OTR_NVMC_DA_DTF_WRI_069 */
    {(U2)276U,      (U2)32U     },      /* 65   : RIMID_OTR_NVMC_DA_DTF_WRI_070 */
    {(U2)284U,      (U2)8U      },      /* 66   : RIMID_OTR_NVMC_DA_DTF_WRI_071 */
    {(U2)286U,      (U2)8U      },      /* 67   : RIMID_OTR_NVMC_DA_DTF_WRI_079 */
    {(U2)288U,      (U2)8U      },      /* 68   : RIMID_OTR_NVMC_DA_DTF_WRI_080 */
    {(U2)290U,      (U2)8U      },      /* 69   : RIMID_OTR_NVMC_DA_DTF_WRI_081 */
    {(U2)292U,      (U2)8U      },      /* 70   : RIMID_OTR_NVMC_DA_DTF_WRI_082 */
    {(U2)294U,      (U2)8U      },      /* 71   : RIMID_OTR_NVMC_DA_DTF_WRI_083 */
    {(U2)296U,      (U2)8U      },      /* 72   : RIMID_OTR_NVMC_DA_DTF_WRI_084 */
    {(U2)298U,      (U2)32U     },      /* 73   : RIMID_OTR_NVMC_DA_DTF_WRI_085 */
    {(U2)306U,      (U2)32U     },      /* 74   : RIMID_OTR_NVMC_DA_DTF_WRI_086 */
    {(U2)314U,      (U2)32U     },      /* 75   : RIMID_OTR_NVMC_DA_DTF_WRI_087 */
    {(U2)322U,      (U2)32U     },      /* 76   : RIMID_OTR_NVMC_DA_DTF_WRI_088 */
    {(U2)330U,      (U2)32U     },      /* 77   : RIMID_OTR_NVMC_DA_DTF_WRI_089 */
    {(U2)338U,      (U2)32U     },      /* 78   : RIMID_OTR_NVMC_DA_DTF_WRI_090 */
    {(U2)346U,      (U2)32U     },      /* 79   : RIMID_OTR_NVMC_DA_DTF_WRI_091 */
    {(U2)354U,      (U2)32U     },      /* 80   : RIMID_OTR_NVMC_DA_DTF_WRI_092 */
    {(U2)362U,      (U2)32U     },      /* 81   : RIMID_OTR_NVMC_DA_DTF_WRI_093 */
    {(U2)370U,      (U2)32U     },      /* 82   : RIMID_OTR_NVMC_DA_DTF_WRI_094 */
    {(U2)378U,      (U2)32U     },      /* 83   : RIMID_OTR_NVMC_DA_DTF_WRI_095 */
    {(U2)386U,      (U2)32U     },      /* 84   : RIMID_OTR_NVMC_DA_DTF_WRI_096 */
    {(U2)394U,      (U2)32U     },      /* 85   : RIMID_OTR_NVMC_DA_DTF_WRI_097 */
    {(U2)402U,      (U2)32U     },      /* 86   : RIMID_OTR_NVMC_DA_DTF_WRI_098 */
    {(U2)410U,      (U2)32U     },      /* 87   : RIMID_OTR_NVMC_DA_DTF_WRI_099 */
    {(U2)418U,      (U2)32U     },      /* 88   : RIMID_OTR_NVMC_DA_DTF_WRI_100 */
    {(U2)426U,      (U2)32U     },      /* 89   : RIMID_OTR_NVMC_DA_DTF_WRI_101 */
    {(U2)434U,      (U2)32U     },      /* 90   : RIMID_OTR_NVMC_DA_DTF_WRI_102 */
    {(U2)442U,      (U2)32U     },      /* 91   : RIMID_OTR_NVMC_DA_DTF_WRI_103 */
    {(U2)450U,      (U2)32U     },      /* 92   : RIMID_OTR_NVMC_DA_DTF_WRI_104 */
    {(U2)458U,      (U2)32U     },      /* 93   : RIMID_OTR_NVMC_DA_DTF_WRI_105 */
    {(U2)466U,      (U2)32U     },      /* 94   : RIMID_OTR_NVMC_DA_DTF_WRI_106 */
    {(U2)474U,      (U2)32U     },      /* 95   : RIMID_OTR_NVMC_DA_DTF_WRI_107 */
    {(U2)482U,      (U2)32U     },      /* 96   : RIMID_OTR_NVMC_DA_DTF_WRI_108 */
    {(U2)490U,      (U2)32U     },      /* 97   : RIMID_OTR_NVMC_DA_DTF_WRI_109 */
    {(U2)498U,      (U2)32U     },      /* 98   : RIMID_OTR_NVMC_DA_DTF_WRI_110 */
    {(U2)506U,      (U2)32U     },      /* 99   : RIMID_OTR_NVMC_DA_DTF_WRI_111 */
    {(U2)514U,      (U2)32U     },      /* 100  : RIMID_OTR_NVMC_DA_DTF_WRI_112 */
    {(U2)522U,      (U2)32U     },      /* 101  : RIMID_OTR_NVMC_DA_DTF_WRI_113 */
    {(U2)530U,      (U2)32U     },      /* 102  : RIMID_OTR_NVMC_DA_DTF_WRI_114 */
    {(U2)538U,      (U2)32U     },      /* 103  : RIMID_OTR_NVMC_DA_DTF_WRI_115 */
    {(U2)546U,      (U2)32U     },      /* 104  : RIMID_OTR_NVMC_DA_DTF_WRI_116 */
    {(U2)554U,      (U2)32U     },      /* 105  : RIMID_OTR_NVMC_DA_DTF_WRI_117 */
    {(U2)562U,      (U2)32U     },      /* 106  : RIMID_OTR_NVMC_DA_DTF_WRI_118 */
    {(U2)570U,      (U2)32U     },      /* 107  : RIMID_OTR_NVMC_DA_DTF_WRI_119 */
    {(U2)578U,      (U2)32U     },      /* 108  : RIMID_OTR_NVMC_DA_DTF_WRI_120 */
    {(U2)586U,      (U2)32U     },      /* 109  : RIMID_OTR_NVMC_DA_DTF_WRI_121 */
    {(U2)594U,      (U2)32U     },      /* 110  : RIMID_OTR_NVMC_DA_DTF_WRI_122 */
    {(U2)602U,      (U2)32U     },      /* 111  : RIMID_OTR_NVMC_DA_DTF_WRI_123 */
    {(U2)610U,      (U2)32U     },      /* 112  : RIMID_OTR_NVMC_DA_DTF_WRI_124 */
    {(U2)618U,      (U2)32U     },      /* 113  : RIMID_OTR_NVMC_DA_DTF_WRI_125 */
    {(U2)626U,      (U2)32U     },      /* 114  : RIMID_OTR_NVMC_DA_DTF_WRI_126 */
    {(U2)634U,      (U2)32U     },      /* 115  : RIMID_OTR_NVMC_DA_DTF_WRI_127 */
    {(U2)642U,      (U2)32U     },      /* 116  : RIMID_OTR_NVMC_DA_DTF_WRI_128 */
    {(U2)650U,      (U2)32U     },      /* 117  : RIMID_OTR_NVMC_DA_DTF_WRI_129 */
    {(U2)658U,      (U2)32U     },      /* 118  : RIMID_OTR_NVMC_DA_DTF_WRI_130 */
    {(U2)666U,      (U2)32U     },      /* 119  : RIMID_OTR_NVMC_DA_DTF_WRI_131 */
    {(U2)674U,      (U2)32U     },      /* 120  : RIMID_OTR_NVMC_DA_DTF_WRI_132 */
    {(U2)682U,      (U2)32U     },      /* 121  : RIMID_OTR_NVMC_DA_DTF_WRI_133 */
    {(U2)690U,      (U2)32U     },      /* 122  : RIMID_OTR_NVMC_DA_DTF_WRI_134 */
    {(U2)698U,      (U2)32U     },      /* 123  : RIMID_OTR_NVMC_DA_DTF_WRI_135 */
    {(U2)706U,      (U2)32U     },      /* 124  : RIMID_OTR_NVMC_DA_DTF_WRI_136 */
    {(U2)714U,      (U2)32U     },      /* 125  : RIMID_OTR_NVMC_DA_DTF_WRI_137 */
    {(U2)722U,      (U2)32U     },      /* 126  : RIMID_OTR_NVMC_DA_DTF_WRI_138 */
    {(U2)730U,      (U2)8U      },      /* 127  : RIMID_OTR_NVMC_DA_DTF_WRI_141 */
    {(U2)732U,      (U2)8U      },      /* 128  : RIMID_OTR_NVMC_DA_DTF_WRI_142 */
    {(U2)734U,      (U2)32U     },      /* 129  : RIMID_OTR_NVMC_DA_DTF_WRI_143 */
    {(U2)742U,      (U2)32U     },      /* 130  : RIMID_OTR_NVMC_DA_DTF_WRI_144 */
    {(U2)750U,      (U2)8U      },      /* 131  : RIMID_OTR_NVMC_DA_DTF_WRI_147 */
    {(U2)752U,      (U2)8U      },      /* 132  : RIMID_OTR_NVMC_DA_DTF_WRI_148 */
    {(U2)754U,      (U2)32U     },      /* 133  : RIMID_OTR_NVMC_DA_DTF_WRI_149 */
    {(U2)762U,      (U2)32U     },      /* 134  : RIMID_OTR_NVMC_DA_DTF_WRI_150 */
    {(U2)770U,      (U2)32U     },      /* 135  : RIMID_OTR_NVMC_DA_DTF_WRI_151 */
    {(U2)778U,      (U2)32U     },      /* 136  : RIMID_OTR_NVMC_DA_DTF_WRI_152 */
    {(U2)786U,      (U2)8U      },      /* 137  : RIMID_OTR_NVMC_DA_DTF_WRI_173 */
    {(U2)788U,      (U2)8U      },      /* 138  : RIMID_OTR_NVMC_DA_DTF_WRI_174 */
    {(U2)790U,      (U2)8U      },      /* 139  : RIMID_OTR_NVMC_DA_DTF_WRI_175 */
    {(U2)792U,      (U2)8U      },      /* 140  : RIMID_OTR_NVMC_DA_DTF_WRI_176 */
    {(U2)794U,      (U2)8U      },      /* 141  : RIMID_OTR_NVMC_DA_DTF_WRI_177 */
    {(U2)796U,      (U2)8U      },      /* 142  : RIMID_OTR_NVMC_DA_DTF_WRI_178 */
    {(U2)798U,      (U2)8U      },      /* 143  : RIMID_OTR_NVMC_DA_DTF_WRI_179 */
    {(U2)800U,      (U2)8U      },      /* 144  : RIMID_OTR_NVMC_DA_DTF_WRI_180 */
    {(U2)802U,      (U2)8U      },      /* 145  : RIMID_OTR_NVMC_DA_DTF_WRI_181 */
    {(U2)804U,      (U2)8U      },      /* 146  : RIMID_OTR_NVMC_DA_DTF_WRI_182 */
    {(U2)806U,      (U2)8U      },      /* 147  : RIMID_OTR_NVMC_DA_DTF_WRI_183 */
    {(U2)808U,      (U2)8U      },      /* 148  : RIMID_OTR_NVMC_DA_DTF_WRI_184 */
    {(U2)810U,      (U2)8U      },      /* 149  : RIMID_OTR_NVMC_DA_DTF_WRI_185 */
    {(U2)812U,      (U2)8U      },      /* 150  : RIMID_OTR_NVMC_DA_DTF_WRI_186 */
    {(U2)814U,      (U2)8U      },      /* 151  : RIMID_OTR_NVMC_DA_DTF_WRI_187 */
    {(U2)816U,      (U2)8U      },      /* 152  : RIMID_OTR_NVMC_DA_DTF_WRI_188 */
    {(U2)818U,      (U2)8U      },      /* 153  : RIMID_OTR_NVMC_DA_DTF_WRI_189 */
    {(U2)820U,      (U2)8U      },      /* 154  : RIMID_OTR_NVMC_DA_DTF_WRI_190 */
    {(U2)822U,      (U2)8U      },      /* 155  : RIMID_OTR_NVMC_DA_DTF_WRI_191 */
    {(U2)824U,      (U2)8U      },      /* 156  : RIMID_OTR_NVMC_DA_DTF_WRI_192 */
    {(U2)826U,      (U2)32U     },      /* 157  : RIMID_OTR_NVMC_DA_DTF_WRI_193 */
    {(U2)834U,      (U2)32U     },      /* 158  : RIMID_OTR_NVMC_DA_DTF_WRI_194 */
    {(U2)842U,      (U2)32U     },      /* 159  : RIMID_OTR_NVMC_DA_DTF_WRI_195 */
    {(U2)850U,      (U2)32U     },      /* 160  : RIMID_OTR_NVMC_DA_DTF_WRI_196 */
    {(U2)858U,      (U2)32U     },      /* 161  : RIMID_OTR_NVMC_DA_DTF_WRI_197 */
    {(U2)866U,      (U2)32U     },      /* 162  : RIMID_OTR_NVMC_DA_DTF_WRI_198 */
    {(U2)874U,      (U2)32U     },      /* 163  : RIMID_OTR_NVMC_DA_DTF_WRI_199 */
    {(U2)882U,      (U2)32U     },      /* 164  : RIMID_OTR_NVMC_DA_DTF_WRI_200 */
    {(U2)890U,      (U2)32U     },      /* 165  : RIMID_OTR_NVMC_DA_DTF_WRI_201 */
    {(U2)898U,      (U2)32U     },      /* 166  : RIMID_OTR_NVMC_DA_DTF_WRI_202 */
    {(U2)906U,      (U2)32U     },      /* 167  : RIMID_OTR_NVMC_DA_DTF_WRI_203 */
    {(U2)914U,      (U2)32U     },      /* 168  : RIMID_OTR_NVMC_DA_DTF_WRI_204 */
    {(U2)922U,      (U2)32U     },      /* 169  : RIMID_OTR_NVMC_DA_DTF_WRI_205 */
    {(U2)930U,      (U2)32U     },      /* 170  : RIMID_OTR_NVMC_DA_DTF_WRI_206 */
    {(U2)938U,      (U2)32U     },      /* 171  : RIMID_OTR_NVMC_DA_DTF_WRI_207 */
    {(U2)946U,      (U2)32U     },      /* 172  : RIMID_OTR_NVMC_DA_DTF_WRI_208 */
    {(U2)954U,      (U2)32U     },      /* 173  : RIMID_OTR_NVMC_DA_DTF_WRI_209 */
    {(U2)962U,      (U2)32U     },      /* 174  : RIMID_OTR_NVMC_DA_DTF_WRI_210 */
    {(U2)970U,      (U2)32U     },      /* 175  : RIMID_OTR_NVMC_DA_DTF_WRI_211 */
    {(U2)978U,      (U2)32U     },      /* 176  : RIMID_OTR_NVMC_DA_DTF_WRI_212 */
    {(U2)986U,      (U2)32U     },      /* 177  : RIMID_OTR_NVMC_DA_DTF_WRI_213 */
    {(U2)994U,      (U2)32U     },      /* 178  : RIMID_OTR_NVMC_DA_DTF_WRI_214 */
    {(U2)1002U,     (U2)32U     },      /* 179  : RIMID_OTR_NVMC_DA_DTF_WRI_215 */
    {(U2)1010U,     (U2)32U     },      /* 180  : RIMID_OTR_NVMC_DA_DTF_WRI_216 */
    {(U2)1018U,     (U2)32U     },      /* 181  : RIMID_OTR_NVMC_DA_DTF_WRI_217 */
    {(U2)1026U,     (U2)32U     },      /* 182  : RIMID_OTR_NVMC_DA_DTF_WRI_218 */
    {(U2)1034U,     (U2)32U     },      /* 183  : RIMID_OTR_NVMC_DA_DTF_WRI_219 */
    {(U2)1042U,     (U2)32U     },      /* 184  : RIMID_OTR_NVMC_DA_DTF_WRI_220 */
    {(U2)1050U,     (U2)32U     },      /* 185  : RIMID_OTR_NVMC_DA_DTF_WRI_221 */
    {(U2)1058U,     (U2)32U     },      /* 186  : RIMID_OTR_NVMC_DA_DTF_WRI_222 */
    {(U2)1066U,     (U2)32U     },      /* 187  : RIMID_OTR_NVMC_DA_DTF_WRI_223 */
    {(U2)1074U,     (U2)32U     },      /* 188  : RIMID_OTR_NVMC_DA_DTF_WRI_224 */
    {(U2)1082U,     (U2)32U     },      /* 189  : RIMID_OTR_NVMC_DA_DTF_WRI_225 */
    {(U2)1090U,     (U2)32U     },      /* 190  : RIMID_OTR_NVMC_DA_DTF_WRI_226 */
    {(U2)1098U,     (U2)32U     },      /* 191  : RIMID_OTR_NVMC_DA_DTF_WRI_227 */
    {(U2)1106U,     (U2)32U     },      /* 192  : RIMID_OTR_NVMC_DA_DTF_WRI_228 */
    {(U2)1114U,     (U2)32U     },      /* 193  : RIMID_OTR_NVMC_DA_DTF_WRI_229 */
    {(U2)1122U,     (U2)32U     },      /* 194  : RIMID_OTR_NVMC_DA_DTF_WRI_230 */
    {(U2)1130U,     (U2)32U     },      /* 195  : RIMID_OTR_NVMC_DA_DTF_WRI_231 */
    {(U2)1138U,     (U2)32U     },      /* 196  : RIMID_OTR_NVMC_DA_DTF_WRI_232 */
    {(U2)1146U,     (U2)32U     },      /* 197  : RIMID_OTR_NVMC_DA_DTF_WRI_233 */
    {(U2)1154U,     (U2)32U     },      /* 198  : RIMID_OTR_NVMC_DA_DTF_WRI_234 */
    {(U2)1162U,     (U2)32U     },      /* 199  : RIMID_OTR_NVMC_DA_DTF_WRI_235 */
    {(U2)1170U,     (U2)32U     },      /* 200  : RIMID_OTR_NVMC_DA_DTF_WRI_236 */
    {(U2)1178U,     (U2)32U     },      /* 201  : RIMID_OTR_NVMC_DA_DTF_WRI_237 */
    {(U2)1186U,     (U2)32U     },      /* 202  : RIMID_OTR_NVMC_DA_DTF_WRI_238 */
    {(U2)1194U,     (U2)32U     },      /* 203  : RIMID_OTR_NVMC_DA_DTF_WRI_239 */
    {(U2)1202U,     (U2)32U     },      /* 204  : RIMID_OTR_NVMC_DA_DTF_WRI_240 */
    {(U2)1210U,     (U2)32U     },      /* 205  : RIMID_OTR_NVMC_DA_DTF_WRI_241 */
    {(U2)1218U,     (U2)32U     },      /* 206  : RIMID_OTR_NVMC_DA_DTF_WRI_242 */
    {(U2)1226U,     (U2)32U     },      /* 207  : RIMID_OTR_NVMC_DA_DTF_WRI_243 */
    {(U2)1234U,     (U2)32U     },      /* 208  : RIMID_OTR_NVMC_DA_DTF_WRI_244 */
    {(U2)1242U,     (U2)32U     },      /* 209  : RIMID_OTR_NVMC_DA_DTF_WRI_245 */
    {(U2)1250U,     (U2)32U     },      /* 210  : RIMID_OTR_NVMC_DA_DTF_WRI_246 */
    {(U2)1258U,     (U2)32U     },      /* 211  : RIMID_OTR_NVMC_DA_DTF_WRI_247 */
    {(U2)1266U,     (U2)32U     },      /* 212  : RIMID_OTR_NVMC_DA_DTF_WRI_248 */
    {(U2)1274U,     (U2)32U     },      /* 213  : RIMID_OTR_NVMC_DA_DTF_WRI_249 */
    {(U2)1282U,     (U2)32U     },      /* 214  : RIMID_OTR_NVMC_DA_DTF_WRI_250 */
    {(U2)1290U,     (U2)32U     },      /* 215  : RIMID_OTR_NVMC_DA_DTF_WRI_251 */
    {(U2)1298U,     (U2)32U     },      /* 216  : RIMID_OTR_NVMC_DA_DTF_WRI_252 */
    {(U2)1306U,     (U2)32U     },      /* 217  : RIMID_OTR_NVMC_DA_DTF_WRI_253 */
    {(U2)1314U,     (U2)32U     },      /* 218  : RIMID_OTR_NVMC_DA_DTF_WRI_254 */
    {(U2)1322U,     (U2)32U     },      /* 219  : RIMID_OTR_NVMC_DA_DTF_WRI_255 */
    {(U2)1330U,     (U2)8U      },      /* 220  : RIMID_OTR_NVMC_DA_DTF_WRI_257 */
    {(U2)1332U,     (U2)32U     }       /* 221  : RIMID_OTR_NVMC_DA_DTF_WRI_258 */
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
