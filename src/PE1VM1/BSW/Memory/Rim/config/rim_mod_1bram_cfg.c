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
#define RIM_MOD_1BRAM_U1_ID_NUM                  (409U)
#define RIM_MOD_1BRAM_U2_ID_NUM                  (0U)
#define RIM_MOD_1BRAM_U4_ID_NUM                  (65U)
#define RIM_MOD_1BRAM_OTHER_ID_NUM               (341U)
/* END : ##TOOL_OUT#RIM_MOD_1B_SIZE## */
/* START : ##TOOL_OUT#RIM_MOD_1B_OTR_TBL_SIZE## */
#define RIM_MOD_1BRAM_OTHER_BUF_NUM              (1509U)
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
    {(U2)0U,        (U2)24U     },      /* 0    : RIMID_OTR_NVMC_DA_DTF_WRI_014 */
    {(U2)6U,        (U2)12U     },      /* 1    : RIMID_OTR_NVMC_DA_DTF_WRI_015 */
    {(U2)9U,        (U2)16U     },      /* 2    : RIMID_OTR_NVMC_DA_DTF_WRI_016 */
    {(U2)13U,       (U2)16U     },      /* 3    : RIMID_OTR_NVMC_DA_DTF_WRI_017 */
    {(U2)17U,       (U2)16U     },      /* 4    : RIMID_OTR_NVMC_DA_DTF_WRI_018 */
    {(U2)21U,       (U2)16U     },      /* 5    : RIMID_OTR_NVMC_DA_DTF_WRI_019 */
    {(U2)25U,       (U2)16U     },      /* 6    : RIMID_OTR_NVMC_DA_DTF_WRI_020 */
    {(U2)29U,       (U2)16U     },      /* 7    : RIMID_OTR_NVMC_DA_DTF_WRI_021 */
    {(U2)33U,       (U2)16U     },      /* 8    : RIMID_OTR_NVMC_DA_DTF_WRI_022 */
    {(U2)37U,       (U2)16U     },      /* 9    : RIMID_OTR_NVMC_DA_DTF_WRI_023 */
    {(U2)41U,       (U2)24U     },      /* 10   : RIMID_OTR_NVMC_DA_DTF_WRI_047 */
    {(U2)47U,       (U2)24U     },      /* 11   : RIMID_OTR_NVMC_DA_DTF_WRI_048 */
    {(U2)53U,       (U2)8U      },      /* 12   : RIMID_OTR_NVMC_DA_DTF_WRI_050 */
    {(U2)55U,       (U2)8U      },      /* 13   : RIMID_OTR_NVMC_DA_DTF_WRI_052 */
    {(U2)57U,       (U2)8U      },      /* 14   : RIMID_OTR_NVMC_DA_DTF_WRI_053 */
    {(U2)59U,       (U2)8U      },      /* 15   : RIMID_OTR_NVMC_DA_DTF_WRI_054 */
    {(U2)61U,       (U2)8U      },      /* 16   : RIMID_OTR_NVMC_DA_DTF_WRI_055 */
    {(U2)63U,       (U2)8U      },      /* 17   : RIMID_OTR_NVMC_DA_DTF_WRI_056 */
    {(U2)65U,       (U2)8U      },      /* 18   : RIMID_OTR_NVMC_DA_DTF_WRI_057 */
    {(U2)67U,       (U2)8U      },      /* 19   : RIMID_OTR_NVMC_DA_DTF_WRI_058 */
    {(U2)69U,       (U2)8U      },      /* 20   : RIMID_OTR_NVMC_DA_DTF_WRI_059 */
    {(U2)71U,       (U2)8U      },      /* 21   : RIMID_OTR_NVMC_DA_DTF_WRI_060 */
    {(U2)73U,       (U2)8U      },      /* 22   : RIMID_OTR_NVMC_DA_DTF_WRI_061 */
    {(U2)75U,       (U2)8U      },      /* 23   : RIMID_OTR_NVMC_DA_DTF_WRI_062 */
    {(U2)77U,       (U2)8U      },      /* 24   : RIMID_OTR_NVMC_DA_DTF_WRI_063 */
    {(U2)79U,       (U2)8U      },      /* 25   : RIMID_OTR_NVMC_DA_DTF_WRI_064 */
    {(U2)81U,       (U2)8U      },      /* 26   : RIMID_OTR_NVMC_DA_DTF_WRI_065 */
    {(U2)83U,       (U2)8U      },      /* 27   : RIMID_OTR_NVMC_DA_DTF_WRI_066 */
    {(U2)85U,       (U2)8U      },      /* 28   : RIMID_OTR_NVMC_DA_DTF_WRI_067 */
    {(U2)87U,       (U2)8U      },      /* 29   : RIMID_OTR_NVMC_DA_DTF_WRI_068 */
    {(U2)89U,       (U2)8U      },      /* 30   : RIMID_OTR_NVMC_DA_DTF_WRI_069 */
    {(U2)91U,       (U2)8U      },      /* 31   : RIMID_OTR_NVMC_DA_DTF_WRI_070 */
    {(U2)93U,       (U2)8U      },      /* 32   : RIMID_OTR_NVMC_DA_DTF_WRI_071 */
    {(U2)95U,       (U2)8U      },      /* 33   : RIMID_OTR_NVMC_DA_DTF_WRI_072 */
    {(U2)97U,       (U2)12U     },      /* 34   : RIMID_OTR_NVMC_DA_DTF_WRI_073 */
    {(U2)100U,      (U2)12U     },      /* 35   : RIMID_OTR_NVMC_DA_DTF_WRI_074 */
    {(U2)103U,      (U2)12U     },      /* 36   : RIMID_OTR_NVMC_DA_DTF_WRI_075 */
    {(U2)106U,      (U2)12U     },      /* 37   : RIMID_OTR_NVMC_DA_DTF_WRI_076 */
    {(U2)109U,      (U2)12U     },      /* 38   : RIMID_OTR_NVMC_DA_DTF_WRI_077 */
    {(U2)112U,      (U2)12U     },      /* 39   : RIMID_OTR_NVMC_DA_DTF_WRI_078 */
    {(U2)115U,      (U2)12U     },      /* 40   : RIMID_OTR_NVMC_DA_DTF_WRI_079 */
    {(U2)118U,      (U2)12U     },      /* 41   : RIMID_OTR_NVMC_DA_DTF_WRI_080 */
    {(U2)121U,      (U2)12U     },      /* 42   : RIMID_OTR_NVMC_DA_DTF_WRI_081 */
    {(U2)124U,      (U2)12U     },      /* 43   : RIMID_OTR_NVMC_DA_DTF_WRI_082 */
    {(U2)127U,      (U2)12U     },      /* 44   : RIMID_OTR_NVMC_DA_DTF_WRI_083 */
    {(U2)130U,      (U2)12U     },      /* 45   : RIMID_OTR_NVMC_DA_DTF_WRI_084 */
    {(U2)133U,      (U2)12U     },      /* 46   : RIMID_OTR_NVMC_DA_DTF_WRI_085 */
    {(U2)136U,      (U2)12U     },      /* 47   : RIMID_OTR_NVMC_DA_DTF_WRI_086 */
    {(U2)139U,      (U2)12U     },      /* 48   : RIMID_OTR_NVMC_DA_DTF_WRI_087 */
    {(U2)142U,      (U2)12U     },      /* 49   : RIMID_OTR_NVMC_DA_DTF_WRI_088 */
    {(U2)145U,      (U2)12U     },      /* 50   : RIMID_OTR_NVMC_DA_DTF_WRI_089 */
    {(U2)148U,      (U2)12U     },      /* 51   : RIMID_OTR_NVMC_DA_DTF_WRI_090 */
    {(U2)151U,      (U2)12U     },      /* 52   : RIMID_OTR_NVMC_DA_DTF_WRI_091 */
    {(U2)154U,      (U2)12U     },      /* 53   : RIMID_OTR_NVMC_DA_DTF_WRI_092 */
    {(U2)157U,      (U2)12U     },      /* 54   : RIMID_OTR_NVMC_DA_DTF_WRI_093 */
    {(U2)160U,      (U2)32U     },      /* 55   : RIMID_OTR_NVMC_DA_DTF_WRI_094 */
    {(U2)168U,      (U2)32U     },      /* 56   : RIMID_OTR_NVMC_DA_DTF_WRI_095 */
    {(U2)176U,      (U2)32U     },      /* 57   : RIMID_OTR_NVMC_DA_DTF_WRI_096 */
    {(U2)184U,      (U2)32U     },      /* 58   : RIMID_OTR_NVMC_DA_DTF_WRI_097 */
    {(U2)192U,      (U2)32U     },      /* 59   : RIMID_OTR_NVMC_DA_DTF_WRI_098 */
    {(U2)200U,      (U2)32U     },      /* 60   : RIMID_OTR_NVMC_DA_DTF_WRI_099 */
    {(U2)208U,      (U2)32U     },      /* 61   : RIMID_OTR_NVMC_DA_DTF_WRI_100 */
    {(U2)216U,      (U2)32U     },      /* 62   : RIMID_OTR_NVMC_DA_DTF_WRI_101 */
    {(U2)224U,      (U2)32U     },      /* 63   : RIMID_OTR_NVMC_DA_DTF_WRI_102 */
    {(U2)232U,      (U2)32U     },      /* 64   : RIMID_OTR_NVMC_DA_DTF_WRI_103 */
    {(U2)240U,      (U2)32U     },      /* 65   : RIMID_OTR_NVMC_DA_DTF_WRI_104 */
    {(U2)248U,      (U2)32U     },      /* 66   : RIMID_OTR_NVMC_DA_DTF_WRI_105 */
    {(U2)256U,      (U2)32U     },      /* 67   : RIMID_OTR_NVMC_DA_DTF_WRI_106 */
    {(U2)264U,      (U2)32U     },      /* 68   : RIMID_OTR_NVMC_DA_DTF_WRI_107 */
    {(U2)272U,      (U2)32U     },      /* 69   : RIMID_OTR_NVMC_DA_DTF_WRI_108 */
    {(U2)280U,      (U2)32U     },      /* 70   : RIMID_OTR_NVMC_DA_DTF_WRI_109 */
    {(U2)288U,      (U2)32U     },      /* 71   : RIMID_OTR_NVMC_DA_DTF_WRI_110 */
    {(U2)296U,      (U2)32U     },      /* 72   : RIMID_OTR_NVMC_DA_DTF_WRI_111 */
    {(U2)304U,      (U2)32U     },      /* 73   : RIMID_OTR_NVMC_DA_DTF_WRI_112 */
    {(U2)312U,      (U2)32U     },      /* 74   : RIMID_OTR_NVMC_DA_DTF_WRI_113 */
    {(U2)320U,      (U2)32U     },      /* 75   : RIMID_OTR_NVMC_DA_DTF_WRI_114 */
    {(U2)328U,      (U2)8U      },      /* 76   : RIMID_OTR_NVMC_DA_DTF_WRI_115 */
    {(U2)330U,      (U2)8U      },      /* 77   : RIMID_OTR_NVMC_DA_DTF_WRI_127 */
    {(U2)332U,      (U2)8U      },      /* 78   : RIMID_OTR_NVMC_DA_DTF_WRI_128 */
    {(U2)334U,      (U2)8U      },      /* 79   : RIMID_OTR_NVMC_DA_DTF_WRI_129 */
    {(U2)336U,      (U2)8U      },      /* 80   : RIMID_OTR_NVMC_DA_DTF_WRI_130 */
    {(U2)338U,      (U2)8U      },      /* 81   : RIMID_OTR_NVMC_DA_DTF_WRI_131 */
    {(U2)340U,      (U2)8U      },      /* 82   : RIMID_OTR_NVMC_DA_DTF_WRI_132 */
    {(U2)342U,      (U2)8U      },      /* 83   : RIMID_OTR_NVMC_DA_DTF_WRI_133 */
    {(U2)344U,      (U2)8U      },      /* 84   : RIMID_OTR_NVMC_DA_DTF_WRI_134 */
    {(U2)346U,      (U2)8U      },      /* 85   : RIMID_OTR_NVMC_DA_DTF_WRI_135 */
    {(U2)348U,      (U2)8U      },      /* 86   : RIMID_OTR_NVMC_DA_DTF_WRI_136 */
    {(U2)350U,      (U2)8U      },      /* 87   : RIMID_OTR_NVMC_DA_DTF_WRI_137 */
    {(U2)352U,      (U2)32U     },      /* 88   : RIMID_OTR_NVMC_DA_DTF_WRI_138 */
    {(U2)360U,      (U2)32U     },      /* 89   : RIMID_OTR_NVMC_DA_DTF_WRI_139 */
    {(U2)368U,      (U2)32U     },      /* 90   : RIMID_OTR_NVMC_DA_DTF_WRI_140 */
    {(U2)376U,      (U2)32U     },      /* 91   : RIMID_OTR_NVMC_DA_DTF_WRI_141 */
    {(U2)384U,      (U2)32U     },      /* 92   : RIMID_OTR_NVMC_DA_DTF_WRI_142 */
    {(U2)392U,      (U2)32U     },      /* 93   : RIMID_OTR_NVMC_DA_DTF_WRI_143 */
    {(U2)400U,      (U2)32U     },      /* 94   : RIMID_OTR_NVMC_DA_DTF_WRI_144 */
    {(U2)408U,      (U2)32U     },      /* 95   : RIMID_OTR_NVMC_DA_DTF_WRI_145 */
    {(U2)416U,      (U2)32U     },      /* 96   : RIMID_OTR_NVMC_DA_DTF_WRI_146 */
    {(U2)424U,      (U2)32U     },      /* 97   : RIMID_OTR_NVMC_DA_DTF_WRI_147 */
    {(U2)432U,      (U2)32U     },      /* 98   : RIMID_OTR_NVMC_DA_DTF_WRI_148 */
    {(U2)440U,      (U2)32U     },      /* 99   : RIMID_OTR_NVMC_DA_DTF_WRI_149 */
    {(U2)448U,      (U2)32U     },      /* 100  : RIMID_OTR_NVMC_DA_DTF_WRI_150 */
    {(U2)456U,      (U2)32U     },      /* 101  : RIMID_OTR_NVMC_DA_DTF_WRI_151 */
    {(U2)464U,      (U2)32U     },      /* 102  : RIMID_OTR_NVMC_DA_DTF_WRI_152 */
    {(U2)472U,      (U2)32U     },      /* 103  : RIMID_OTR_NVMC_DA_DTF_WRI_153 */
    {(U2)480U,      (U2)32U     },      /* 104  : RIMID_OTR_NVMC_DA_DTF_WRI_154 */
    {(U2)488U,      (U2)32U     },      /* 105  : RIMID_OTR_NVMC_DA_DTF_WRI_155 */
    {(U2)496U,      (U2)32U     },      /* 106  : RIMID_OTR_NVMC_DA_DTF_WRI_156 */
    {(U2)504U,      (U2)32U     },      /* 107  : RIMID_OTR_NVMC_DA_DTF_WRI_157 */
    {(U2)512U,      (U2)32U     },      /* 108  : RIMID_OTR_NVMC_DA_DTF_WRI_158 */
    {(U2)520U,      (U2)32U     },      /* 109  : RIMID_OTR_NVMC_DA_DTF_WRI_159 */
    {(U2)528U,      (U2)32U     },      /* 110  : RIMID_OTR_NVMC_DA_DTF_WRI_160 */
    {(U2)536U,      (U2)32U     },      /* 111  : RIMID_OTR_NVMC_DA_DTF_WRI_161 */
    {(U2)544U,      (U2)32U     },      /* 112  : RIMID_OTR_NVMC_DA_DTF_WRI_162 */
    {(U2)552U,      (U2)32U     },      /* 113  : RIMID_OTR_NVMC_DA_DTF_WRI_163 */
    {(U2)560U,      (U2)32U     },      /* 114  : RIMID_OTR_NVMC_DA_DTF_WRI_164 */
    {(U2)568U,      (U2)32U     },      /* 115  : RIMID_OTR_NVMC_DA_DTF_WRI_165 */
    {(U2)576U,      (U2)32U     },      /* 116  : RIMID_OTR_NVMC_DA_DTF_WRI_166 */
    {(U2)584U,      (U2)32U     },      /* 117  : RIMID_OTR_NVMC_DA_DTF_WRI_167 */
    {(U2)592U,      (U2)32U     },      /* 118  : RIMID_OTR_NVMC_DA_DTF_WRI_168 */
    {(U2)600U,      (U2)32U     },      /* 119  : RIMID_OTR_NVMC_DA_DTF_WRI_169 */
    {(U2)608U,      (U2)32U     },      /* 120  : RIMID_OTR_NVMC_DA_DTF_WRI_170 */
    {(U2)616U,      (U2)32U     },      /* 121  : RIMID_OTR_NVMC_DA_DTF_WRI_171 */
    {(U2)624U,      (U2)32U     },      /* 122  : RIMID_OTR_NVMC_DA_DTF_WRI_172 */
    {(U2)632U,      (U2)32U     },      /* 123  : RIMID_OTR_NVMC_DA_DTF_WRI_173 */
    {(U2)640U,      (U2)32U     },      /* 124  : RIMID_OTR_NVMC_DA_DTF_WRI_174 */
    {(U2)648U,      (U2)32U     },      /* 125  : RIMID_OTR_NVMC_DA_DTF_WRI_175 */
    {(U2)656U,      (U2)32U     },      /* 126  : RIMID_OTR_NVMC_DA_DTF_WRI_176 */
    {(U2)664U,      (U2)32U     },      /* 127  : RIMID_OTR_NVMC_DA_DTF_WRI_177 */
    {(U2)672U,      (U2)32U     },      /* 128  : RIMID_OTR_NVMC_DA_DTF_WRI_178 */
    {(U2)680U,      (U2)32U     },      /* 129  : RIMID_OTR_NVMC_DA_DTF_WRI_179 */
    {(U2)688U,      (U2)32U     },      /* 130  : RIMID_OTR_NVMC_DA_DTF_WRI_180 */
    {(U2)696U,      (U2)32U     },      /* 131  : RIMID_OTR_NVMC_DA_DTF_WRI_181 */
    {(U2)704U,      (U2)32U     },      /* 132  : RIMID_OTR_NVMC_DA_DTF_WRI_182 */
    {(U2)712U,      (U2)32U     },      /* 133  : RIMID_OTR_NVMC_DA_DTF_WRI_183 */
    {(U2)720U,      (U2)32U     },      /* 134  : RIMID_OTR_NVMC_DA_DTF_WRI_184 */
    {(U2)728U,      (U2)32U     },      /* 135  : RIMID_OTR_NVMC_DA_DTF_WRI_185 */
    {(U2)736U,      (U2)32U     },      /* 136  : RIMID_OTR_NVMC_DA_DTF_WRI_186 */
    {(U2)744U,      (U2)32U     },      /* 137  : RIMID_OTR_NVMC_DA_DTF_WRI_187 */
    {(U2)752U,      (U2)32U     },      /* 138  : RIMID_OTR_NVMC_DA_DTF_WRI_188 */
    {(U2)760U,      (U2)32U     },      /* 139  : RIMID_OTR_NVMC_DA_DTF_WRI_189 */
    {(U2)768U,      (U2)32U     },      /* 140  : RIMID_OTR_NVMC_DA_DTF_WRI_190 */
    {(U2)776U,      (U2)32U     },      /* 141  : RIMID_OTR_NVMC_DA_DTF_WRI_191 */
    {(U2)784U,      (U2)32U     },      /* 142  : RIMID_OTR_NVMC_DA_DTF_WRI_192 */
    {(U2)792U,      (U2)32U     },      /* 143  : RIMID_OTR_NVMC_DA_DTF_WRI_193 */
    {(U2)800U,      (U2)32U     },      /* 144  : RIMID_OTR_NVMC_DA_DTF_WRI_194 */
    {(U2)808U,      (U2)32U     },      /* 145  : RIMID_OTR_NVMC_DA_DTF_WRI_195 */
    {(U2)816U,      (U2)32U     },      /* 146  : RIMID_OTR_NVMC_DA_DTF_WRI_196 */
    {(U2)824U,      (U2)32U     },      /* 147  : RIMID_OTR_NVMC_DA_DTF_WRI_197 */
    {(U2)832U,      (U2)32U     },      /* 148  : RIMID_OTR_NVMC_DA_DTF_WRI_198 */
    {(U2)840U,      (U2)32U     },      /* 149  : RIMID_OTR_NVMC_DA_DTF_WRI_199 */
    {(U2)848U,      (U2)24U     },      /* 150  : RIMID_OTR_NVMC_DA_DTF_WRI_200 */
    {(U2)854U,      (U2)24U     },      /* 151  : RIMID_OTR_NVMC_DA_DTF_WRI_201 */
    {(U2)860U,      (U2)24U     },      /* 152  : RIMID_OTR_NVMC_DA_DTF_WRI_202 */
    {(U2)866U,      (U2)32U     },      /* 153  : RIMID_OTR_NVMC_DA_DTF_WRI_203 */
    {(U2)874U,      (U2)32U     },      /* 154  : RIMID_OTR_NVMC_DA_DTF_WRI_204 */
    {(U2)882U,      (U2)32U     },      /* 155  : RIMID_OTR_NVMC_DA_DTF_WRI_205 */
    {(U2)890U,      (U2)24U     },      /* 156  : RIMID_OTR_NVMC_DA_DTF_WRI_206 */
    {(U2)896U,      (U2)24U     },      /* 157  : RIMID_OTR_NVMC_DA_DTF_WRI_207 */
    {(U2)902U,      (U2)24U     },      /* 158  : RIMID_OTR_NVMC_DA_DTF_WRI_208 */
    {(U2)908U,      (U2)24U     },      /* 159  : RIMID_OTR_NVMC_DA_DTF_WRI_209 */
    {(U2)914U,      (U2)24U     },      /* 160  : RIMID_OTR_NVMC_DA_DTF_WRI_210 */
    {(U2)920U,      (U2)24U     },      /* 161  : RIMID_OTR_NVMC_DA_DTF_WRI_211 */
    {(U2)926U,      (U2)32U     },      /* 162  : RIMID_OTR_NVMC_DA_DTF_WRI_212 */
    {(U2)934U,      (U2)32U     },      /* 163  : RIMID_OTR_NVMC_DA_DTF_WRI_213 */
    {(U2)942U,      (U2)32U     },      /* 164  : RIMID_OTR_NVMC_DA_DTF_WRI_214 */
    {(U2)950U,      (U2)32U     },      /* 165  : RIMID_OTR_NVMC_DA_DTF_WRI_219 */
    {(U2)958U,      (U2)32U     },      /* 166  : RIMID_OTR_NVMC_DA_DTF_WRI_220 */
    {(U2)966U,      (U2)32U     },      /* 167  : RIMID_OTR_NVMC_DA_DTF_WRI_221 */
    {(U2)974U,      (U2)32U     },      /* 168  : RIMID_OTR_NVMC_DA_DTF_WRI_222 */
    {(U2)982U,      (U2)32U     },      /* 169  : RIMID_OTR_NVMC_DA_DTF_WRI_223 */
    {(U2)990U,      (U2)32U     },      /* 170  : RIMID_OTR_NVMC_DA_DTF_WRI_224 */
    {(U2)998U,      (U2)32U     },      /* 171  : RIMID_OTR_NVMC_DA_DTF_WRI_225 */
    {(U2)1006U,     (U2)32U     },      /* 172  : RIMID_OTR_NVMC_DA_DTF_WRI_226 */
    {(U2)1014U,     (U2)32U     },      /* 173  : RIMID_OTR_NVMC_DA_DTF_WRI_227 */
    {(U2)1022U,     (U2)32U     },      /* 174  : RIMID_OTR_NVMC_DA_DTF_WRI_228 */
    {(U2)1030U,     (U2)32U     },      /* 175  : RIMID_OTR_NVMC_DA_DTF_WRI_229 */
    {(U2)1038U,     (U2)32U     },      /* 176  : RIMID_OTR_NVMC_DA_DTF_WRI_230 */
    {(U2)1046U,     (U2)32U     },      /* 177  : RIMID_OTR_NVMC_DA_DTF_WRI_231 */
    {(U2)1054U,     (U2)32U     },      /* 178  : RIMID_OTR_NVMC_DA_DTF_WRI_232 */
    {(U2)1062U,     (U2)32U     },      /* 179  : RIMID_OTR_NVMC_DA_DTF_WRI_233 */
    {(U2)1070U,     (U2)32U     },      /* 180  : RIMID_OTR_NVMC_DA_DTF_WRI_234 */
    {(U2)1078U,     (U2)32U     },      /* 181  : RIMID_OTR_NVMC_DA_DTF_WRI_235 */
    {(U2)1086U,     (U2)32U     },      /* 182  : RIMID_OTR_NVMC_DA_DTF_WRI_236 */
    {(U2)1094U,     (U2)32U     },      /* 183  : RIMID_OTR_NVMC_DA_DTF_WRI_237 */
    {(U2)1102U,     (U2)32U     },      /* 184  : RIMID_OTR_NVMC_DA_DTF_WRI_238 */
    {(U2)1110U,     (U2)28U     },      /* 185  : RIMID_OTR_NVMC_DA_DTF_WRI_239 */
    {(U2)1117U,     (U2)28U     },      /* 186  : RIMID_OTR_NVMC_DA_DTF_WRI_240 */
    {(U2)1124U,     (U2)28U     },      /* 187  : RIMID_OTR_NVMC_DA_DTF_WRI_241 */
    {(U2)1131U,     (U2)28U     },      /* 188  : RIMID_OTR_NVMC_DA_DTF_WRI_242 */
    {(U2)1138U,     (U2)28U     },      /* 189  : RIMID_OTR_NVMC_DA_DTF_WRI_243 */
    {(U2)1145U,     (U2)24U     },      /* 190  : RIMID_OTR_NVMC_DA_DTF_WRI_244 */
    {(U2)1151U,     (U2)24U     },      /* 191  : RIMID_OTR_NVMC_DA_DTF_WRI_245 */
    {(U2)1157U,     (U2)24U     },      /* 192  : RIMID_OTR_NVMC_DA_DTF_WRI_246 */
    {(U2)1163U,     (U2)24U     },      /* 193  : RIMID_OTR_NVMC_DA_DTF_WRI_247 */
    {(U2)1169U,     (U2)24U     },      /* 194  : RIMID_OTR_NVMC_DA_DTF_WRI_248 */
    {(U2)1175U,     (U2)24U     },      /* 195  : RIMID_OTR_NVMC_DA_DTF_WRI_257 */
    {(U2)1181U,     (U2)24U     },      /* 196  : RIMID_OTR_NVMC_DA_DTF_WRI_258 */
    {(U2)1187U,     (U2)24U     },      /* 197  : RIMID_OTR_NVMC_DA_DTF_WRI_280 */
    {(U2)1193U,     (U2)24U     },      /* 198  : RIMID_OTR_NVMC_DA_DTF_WRI_281 */
    {(U2)1199U,     (U2)16U     },      /* 199  : RIMID_OTR_NVMC_DA_DTF_WRI_286 */
    {(U2)1203U,     (U2)24U     },      /* 200  : RIMID_OTR_NVMC_DA_DTF_WRI_295 */
    {(U2)1209U,     (U2)24U     },      /* 201  : RIMID_OTR_NVMC_DA_DTF_WRI_296 */
    {(U2)1215U,     (U2)24U     },      /* 202  : RIMID_OTR_NVMC_DA_DTF_WRI_305 */
    {(U2)1221U,     (U2)24U     },      /* 203  : RIMID_OTR_NVMC_DA_DTF_WRI_306 */
    {(U2)1227U,     (U2)8U      },      /* 204  : RIMID_OTR_NVMC_DA_DTF_WRI_315 */
    {(U2)1229U,     (U2)8U      },      /* 205  : RIMID_OTR_NVMC_DA_DTF_WRI_316 */
    {(U2)1231U,     (U2)8U      },      /* 206  : RIMID_OTR_NVMC_DA_DTF_WRI_317 */
    {(U2)1233U,     (U2)8U      },      /* 207  : RIMID_OTR_NVMC_DA_DTF_WRI_318 */
    {(U2)1235U,     (U2)8U      },      /* 208  : RIMID_OTR_NVMC_DA_DTF_WRI_319 */
    {(U2)1237U,     (U2)8U      },      /* 209  : RIMID_OTR_NVMC_DA_DTF_WRI_320 */
    {(U2)1239U,     (U2)8U      },      /* 210  : RIMID_OTR_NVMC_DA_DTF_WRI_321 */
    {(U2)1241U,     (U2)8U      },      /* 211  : RIMID_OTR_NVMC_DA_DTF_WRI_322 */
    {(U2)1243U,     (U2)8U      },      /* 212  : RIMID_OTR_NVMC_DA_DTF_WRI_323 */
    {(U2)1245U,     (U2)8U      },      /* 213  : RIMID_OTR_NVMC_DA_DTF_WRI_324 */
    {(U2)1247U,     (U2)8U      },      /* 214  : RIMID_OTR_NVMC_DA_DTF_WRI_325 */
    {(U2)1249U,     (U2)8U      },      /* 215  : RIMID_OTR_NVMC_DA_DTF_WRI_326 */
    {(U2)1251U,     (U2)8U      },      /* 216  : RIMID_OTR_NVMC_DA_DTF_WRI_327 */
    {(U2)1253U,     (U2)8U      },      /* 217  : RIMID_OTR_NVMC_DA_DTF_WRI_328 */
    {(U2)1255U,     (U2)8U      },      /* 218  : RIMID_OTR_NVMC_DA_DTF_WRI_329 */
    {(U2)1257U,     (U2)8U      },      /* 219  : RIMID_OTR_NVMC_DA_DTF_WRI_330 */
    {(U2)1259U,     (U2)8U      },      /* 220  : RIMID_OTR_NVMC_DA_DTF_WRI_331 */
    {(U2)1261U,     (U2)8U      },      /* 221  : RIMID_OTR_NVMC_DA_DTF_WRI_332 */
    {(U2)1263U,     (U2)8U      },      /* 222  : RIMID_OTR_NVMC_DA_DTF_WRI_333 */
    {(U2)1265U,     (U2)8U      },      /* 223  : RIMID_OTR_NVMC_DA_DTF_WRI_334 */
    {(U2)1267U,     (U2)8U      },      /* 224  : RIMID_OTR_NVMC_DA_DTF_WRI_335 */
    {(U2)1269U,     (U2)8U      },      /* 225  : RIMID_OTR_NVMC_DA_DTF_WRI_336 */
    {(U2)1271U,     (U2)8U      },      /* 226  : RIMID_OTR_NVMC_DA_DTF_WRI_337 */
    {(U2)1273U,     (U2)8U      },      /* 227  : RIMID_OTR_NVMC_DA_DTF_WRI_338 */
    {(U2)1275U,     (U2)8U      },      /* 228  : RIMID_OTR_NVMC_DA_DTF_WRI_339 */
    {(U2)1277U,     (U2)8U      },      /* 229  : RIMID_OTR_NVMC_DA_DTF_WRI_340 */
    {(U2)1279U,     (U2)8U      },      /* 230  : RIMID_OTR_NVMC_DA_DTF_WRI_341 */
    {(U2)1281U,     (U2)8U      },      /* 231  : RIMID_OTR_NVMC_DA_DTF_WRI_342 */
    {(U2)1283U,     (U2)8U      },      /* 232  : RIMID_OTR_NVMC_DA_DTF_WRI_343 */
    {(U2)1285U,     (U2)8U      },      /* 233  : RIMID_OTR_NVMC_DA_DTF_WRI_344 */
    {(U2)1287U,     (U2)8U      },      /* 234  : RIMID_OTR_NVMC_DA_DTF_WRI_345 */
    {(U2)1289U,     (U2)8U      },      /* 235  : RIMID_OTR_NVMC_DA_DTF_WRI_346 */
    {(U2)1291U,     (U2)8U      },      /* 236  : RIMID_OTR_NVMC_DA_DTF_WRI_347 */
    {(U2)1293U,     (U2)8U      },      /* 237  : RIMID_OTR_NVMC_DA_DTF_WRI_348 */
    {(U2)1295U,     (U2)8U      },      /* 238  : RIMID_OTR_NVMC_DA_DTF_WRI_349 */
    {(U2)1297U,     (U2)8U      },      /* 239  : RIMID_OTR_NVMC_DA_DTF_WRI_350 */
    {(U2)1299U,     (U2)8U      },      /* 240  : RIMID_OTR_NVMC_DA_DTF_WRI_351 */
    {(U2)1301U,     (U2)8U      },      /* 241  : RIMID_OTR_NVMC_DA_DTF_WRI_352 */
    {(U2)1303U,     (U2)8U      },      /* 242  : RIMID_OTR_NVMC_DA_DTF_WRI_353 */
    {(U2)1305U,     (U2)8U      },      /* 243  : RIMID_OTR_NVMC_DA_DTF_WRI_354 */
    {(U2)1307U,     (U2)8U      },      /* 244  : RIMID_OTR_NVMC_DA_DTF_WRI_355 */
    {(U2)1309U,     (U2)8U      },      /* 245  : RIMID_OTR_NVMC_DA_DTF_WRI_356 */
    {(U2)1311U,     (U2)8U      },      /* 246  : RIMID_OTR_NVMC_DA_DTF_WRI_357 */
    {(U2)1313U,     (U2)8U      },      /* 247  : RIMID_OTR_NVMC_DA_DTF_WRI_358 */
    {(U2)1315U,     (U2)8U      },      /* 248  : RIMID_OTR_NVMC_DA_DTF_WRI_359 */
    {(U2)1317U,     (U2)8U      },      /* 249  : RIMID_OTR_NVMC_DA_DTF_WRI_360 */
    {(U2)1319U,     (U2)8U      },      /* 250  : RIMID_OTR_NVMC_DA_DTF_WRI_361 */
    {(U2)1321U,     (U2)8U      },      /* 251  : RIMID_OTR_NVMC_DA_DTF_WRI_362 */
    {(U2)1323U,     (U2)8U      },      /* 252  : RIMID_OTR_NVMC_DA_DTF_WRI_363 */
    {(U2)1325U,     (U2)8U      },      /* 253  : RIMID_OTR_NVMC_DA_DTF_WRI_364 */
    {(U2)1327U,     (U2)8U      },      /* 254  : RIMID_OTR_NVMC_DA_DTF_WRI_365 */
    {(U2)1329U,     (U2)8U      },      /* 255  : RIMID_OTR_NVMC_DA_DTF_WRI_366 */
    {(U2)1331U,     (U2)8U      },      /* 256  : RIMID_OTR_NVMC_DA_DTF_WRI_367 */
    {(U2)1333U,     (U2)8U      },      /* 257  : RIMID_OTR_NVMC_DA_DTF_WRI_368 */
    {(U2)1335U,     (U2)8U      },      /* 258  : RIMID_OTR_NVMC_DA_DTF_WRI_369 */
    {(U2)1337U,     (U2)8U      },      /* 259  : RIMID_OTR_NVMC_DA_DTF_WRI_370 */
    {(U2)1339U,     (U2)8U      },      /* 260  : RIMID_OTR_NVMC_DA_DTF_WRI_371 */
    {(U2)1341U,     (U2)8U      },      /* 261  : RIMID_OTR_NVMC_DA_DTF_WRI_372 */
    {(U2)1343U,     (U2)8U      },      /* 262  : RIMID_OTR_NVMC_DA_DTF_WRI_373 */
    {(U2)1345U,     (U2)8U      },      /* 263  : RIMID_OTR_NVMC_DA_DTF_WRI_374 */
    {(U2)1347U,     (U2)8U      },      /* 264  : RIMID_OTR_NVMC_DA_DTF_WRI_375 */
    {(U2)1349U,     (U2)8U      },      /* 265  : RIMID_OTR_NVMC_DA_DTF_WRI_376 */
    {(U2)1351U,     (U2)8U      },      /* 266  : RIMID_OTR_NVMC_DA_DTF_WRI_377 */
    {(U2)1353U,     (U2)8U      },      /* 267  : RIMID_OTR_NVMC_DA_DTF_WRI_378 */
    {(U2)1355U,     (U2)8U      },      /* 268  : RIMID_OTR_NVMC_DA_DTF_WRI_379 */
    {(U2)1357U,     (U2)8U      },      /* 269  : RIMID_OTR_NVMC_DA_DTF_WRI_380 */
    {(U2)1359U,     (U2)8U      },      /* 270  : RIMID_OTR_NVMC_DA_DTF_WRI_381 */
    {(U2)1361U,     (U2)8U      },      /* 271  : RIMID_OTR_NVMC_DA_DTF_WRI_382 */
    {(U2)1363U,     (U2)8U      },      /* 272  : RIMID_OTR_NVMC_DA_DTF_WRI_383 */
    {(U2)1365U,     (U2)8U      },      /* 273  : RIMID_OTR_NVMC_DA_DTF_WRI_384 */
    {(U2)1367U,     (U2)8U      },      /* 274  : RIMID_OTR_NVMC_DA_DTF_WRI_385 */
    {(U2)1369U,     (U2)8U      },      /* 275  : RIMID_OTR_NVMC_DA_DTF_WRI_386 */
    {(U2)1371U,     (U2)8U      },      /* 276  : RIMID_OTR_NVMC_DA_DTF_WRI_387 */
    {(U2)1373U,     (U2)8U      },      /* 277  : RIMID_OTR_NVMC_DA_DTF_WRI_388 */
    {(U2)1375U,     (U2)8U      },      /* 278  : RIMID_OTR_NVMC_DA_DTF_WRI_389 */
    {(U2)1377U,     (U2)8U      },      /* 279  : RIMID_OTR_NVMC_DA_DTF_WRI_390 */
    {(U2)1379U,     (U2)8U      },      /* 280  : RIMID_OTR_NVMC_DA_DTF_WRI_391 */
    {(U2)1381U,     (U2)8U      },      /* 281  : RIMID_OTR_NVMC_DA_DTF_WRI_392 */
    {(U2)1383U,     (U2)8U      },      /* 282  : RIMID_OTR_NVMC_DA_DTF_WRI_393 */
    {(U2)1385U,     (U2)8U      },      /* 283  : RIMID_OTR_NVMC_DA_DTF_WRI_394 */
    {(U2)1387U,     (U2)8U      },      /* 284  : RIMID_OTR_NVMC_DA_DTF_WRI_395 */
    {(U2)1389U,     (U2)8U      },      /* 285  : RIMID_OTR_NVMC_DA_DTF_WRI_396 */
    {(U2)1391U,     (U2)8U      },      /* 286  : RIMID_OTR_NVMC_DA_DTF_WRI_397 */
    {(U2)1393U,     (U2)8U      },      /* 287  : RIMID_OTR_NVMC_DA_DTF_WRI_398 */
    {(U2)1395U,     (U2)8U      },      /* 288  : RIMID_OTR_NVMC_DA_DTF_WRI_399 */
    {(U2)1397U,     (U2)8U      },      /* 289  : RIMID_OTR_NVMC_DA_DTF_WRI_400 */
    {(U2)1399U,     (U2)8U      },      /* 290  : RIMID_OTR_NVMC_DA_DTF_WRI_401 */
    {(U2)1401U,     (U2)8U      },      /* 291  : RIMID_OTR_NVMC_DA_DTF_WRI_402 */
    {(U2)1403U,     (U2)8U      },      /* 292  : RIMID_OTR_NVMC_DA_DTF_WRI_403 */
    {(U2)1405U,     (U2)8U      },      /* 293  : RIMID_OTR_NVMC_DA_DTF_WRI_404 */
    {(U2)1407U,     (U2)8U      },      /* 294  : RIMID_OTR_NVMC_DA_DTF_WRI_405 */
    {(U2)1409U,     (U2)8U      },      /* 295  : RIMID_OTR_NVMC_DA_DTF_WRI_406 */
    {(U2)1411U,     (U2)8U      },      /* 296  : RIMID_OTR_NVMC_DA_DTF_WRI_407 */
    {(U2)1413U,     (U2)8U      },      /* 297  : RIMID_OTR_NVMC_DA_DTF_WRI_408 */
    {(U2)1415U,     (U2)8U      },      /* 298  : RIMID_OTR_NVMC_DA_DTF_WRI_409 */
    {(U2)1417U,     (U2)8U      },      /* 299  : RIMID_OTR_NVMC_DA_DTF_WRI_410 */
    {(U2)1419U,     (U2)8U      },      /* 300  : RIMID_OTR_NVMC_DA_DTF_WRI_411 */
    {(U2)1421U,     (U2)8U      },      /* 301  : RIMID_OTR_NVMC_DA_DTF_WRI_412 */
    {(U2)1423U,     (U2)8U      },      /* 302  : RIMID_OTR_NVMC_DA_DTF_WRI_413 */
    {(U2)1425U,     (U2)8U      },      /* 303  : RIMID_OTR_NVMC_DA_DTF_WRI_414 */
    {(U2)1427U,     (U2)8U      },      /* 304  : RIMID_OTR_NVMC_DA_DTF_WRI_415 */
    {(U2)1429U,     (U2)8U      },      /* 305  : RIMID_OTR_NVMC_DA_DTF_WRI_416 */
    {(U2)1431U,     (U2)8U      },      /* 306  : RIMID_OTR_NVMC_DA_DTF_WRI_417 */
    {(U2)1433U,     (U2)8U      },      /* 307  : RIMID_OTR_NVMC_DA_DTF_WRI_418 */
    {(U2)1435U,     (U2)8U      },      /* 308  : RIMID_OTR_NVMC_DA_DTF_WRI_419 */
    {(U2)1437U,     (U2)8U      },      /* 309  : RIMID_OTR_NVMC_DA_DTF_WRI_420 */
    {(U2)1439U,     (U2)8U      },      /* 310  : RIMID_OTR_NVMC_DA_DTF_WRI_421 */
    {(U2)1441U,     (U2)8U      },      /* 311  : RIMID_OTR_NVMC_DA_DTF_WRI_422 */
    {(U2)1443U,     (U2)8U      },      /* 312  : RIMID_OTR_NVMC_DA_DTF_WRI_423 */
    {(U2)1445U,     (U2)8U      },      /* 313  : RIMID_OTR_NVMC_DA_DTF_WRI_424 */
    {(U2)1447U,     (U2)8U      },      /* 314  : RIMID_OTR_NVMC_DA_DTF_WRI_425 */
    {(U2)1449U,     (U2)8U      },      /* 315  : RIMID_OTR_NVMC_DA_DTF_WRI_426 */
    {(U2)1451U,     (U2)8U      },      /* 316  : RIMID_OTR_NVMC_DA_DTF_WRI_427 */
    {(U2)1453U,     (U2)8U      },      /* 317  : RIMID_OTR_NVMC_DA_DTF_WRI_428 */
    {(U2)1455U,     (U2)8U      },      /* 318  : RIMID_OTR_NVMC_DA_DTF_WRI_429 */
    {(U2)1457U,     (U2)8U      },      /* 319  : RIMID_OTR_NVMC_DA_DTF_WRI_430 */
    {(U2)1459U,     (U2)8U      },      /* 320  : RIMID_OTR_NVMC_DA_DTF_WRI_431 */
    {(U2)1461U,     (U2)8U      },      /* 321  : RIMID_OTR_NVMC_DA_DTF_WRI_432 */
    {(U2)1463U,     (U2)8U      },      /* 322  : RIMID_OTR_NVMC_DA_DTF_WRI_433 */
    {(U2)1465U,     (U2)8U      },      /* 323  : RIMID_OTR_NVMC_DA_DTF_WRI_434 */
    {(U2)1467U,     (U2)8U      },      /* 324  : RIMID_OTR_NVMC_DA_DTF_WRI_435 */
    {(U2)1469U,     (U2)8U      },      /* 325  : RIMID_OTR_NVMC_DA_DTF_WRI_436 */
    {(U2)1471U,     (U2)8U      },      /* 326  : RIMID_OTR_NVMC_DA_DTF_WRI_437 */
    {(U2)1473U,     (U2)8U      },      /* 327  : RIMID_OTR_NVMC_DA_DTF_WRI_438 */
    {(U2)1475U,     (U2)8U      },      /* 328  : RIMID_OTR_NVMC_DA_DTF_WRI_439 */
    {(U2)1477U,     (U2)8U      },      /* 329  : RIMID_OTR_NVMC_DA_DTF_WRI_440 */
    {(U2)1479U,     (U2)8U      },      /* 330  : RIMID_OTR_NVMC_DA_DTF_WRI_441 */
    {(U2)1481U,     (U2)8U      },      /* 331  : RIMID_OTR_NVMC_DA_DTF_WRI_442 */
    {(U2)1483U,     (U2)8U      },      /* 332  : RIMID_OTR_NVMC_DA_DTF_WRI_443 */
    {(U2)1485U,     (U2)8U      },      /* 333  : RIMID_OTR_NVMC_DA_DTF_WRI_444 */
    {(U2)1487U,     (U2)8U      },      /* 334  : RIMID_OTR_NVMC_DA_DTF_WRI_445 */
    {(U2)1489U,     (U2)8U      },      /* 335  : RIMID_OTR_NVMC_DA_DTF_WRI_446 */
    {(U2)1491U,     (U2)8U      },      /* 336  : RIMID_OTR_NVMC_DA_DTF_WRI_447 */
    {(U2)1493U,     (U2)8U      },      /* 337  : RIMID_OTR_NVMC_DA_DTF_WRI_448 */
    {(U2)1495U,     (U2)8U      },      /* 338  : RIMID_OTR_NVMC_DA_DTF_WRI_449 */
    {(U2)1497U,     (U2)24U     },      /* 339  : RIMID_OTR_NVMC_DA_DTF_WRI_458 */
    {(U2)1503U,     (U2)24U     }       /* 340  : RIMID_OTR_NVMC_DA_DTF_WRI_459 */
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
