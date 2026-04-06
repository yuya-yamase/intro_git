/* can_rscf4_pbcfg_c_m10700_v3-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF4/PBCFG/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <can/common/can_cm_log.h>
#include <can/common/can_syscfg_ext.h>

#include <Can.h>
#include "../../cfg/common/can_cv_cfg.h"
#include "../../cfg/rscf4/can_rscf4_cfg_ext.h"
#include "../../cfg/rscf4/can_rscf4_cfg.h"

#include <can/common/can_cv_can.h>
#include <can/common/can_memmap.h>
#include <can/rscf4/can_rscf4.h>
#include <can/rscf4/can_rscf4_cm_phy.h>

#if (CAN_CFG_CAN == CAN_USE)
#include <can/rscf4/can_rscf4_tb_log.h>
#include <can/rscf4/can_rscf4_tb_phy.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*==================================================================*/
/* HOH Configuration Table                                          */
/*==================================================================*/
/* param1 : HOH Number                                              */
/* value  : HOH Configuration                                       */
/*   - u1ControllerID CAN Controller ID associated to HOH           */
/*   - u1MboxNo       MBOX Number associated to HOH                 */
/*------------------------------------------------------------------*/
#if (CAN_CFG_TRANSMIT == CAN_USE)
CanConst CanHohCfgType Can_stHohCfgTbl[ CAN_TB_HOHNUM ] =
{
  /*   u1ControllerID         , u1MboxNo          */
  /*========== User define Area [Start] ==========*/
  /*--- Reception --------------------------------*/
#warning "BEVCDCFD-2652"
#if 0 /* BEVCDCFD-2652 */
     { (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB001 }   /* [0] HOH000 */
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB002 }   /* [1] HOH001 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB009 }   /* [2] HOH002 */
#else /* BEVCDCFD-2652 */
     { (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB002 }   /* [0] HOH000 */
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB003 }   /* [1] HOH001 */
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB004 }   /* [2] HOH002 */
#endif /* BEVCDCFD-2652 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB010 }   /* [3] HOH003 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB011 }   /* [4] HOH004 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB012 }   /* [5] HOH005 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB013 }   /* [6] HOH006 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB014 }   /* [7] HOH007 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB015 }   /* [8] HOH008 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB016 }   /* [9] HOH009 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB017 }   /* [10] HOH010 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB018 }   /* [11] HOH011 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB019 }   /* [12] HOH012 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB020 }   /* [13] HOH013 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB021 }   /* [14] HOH014 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB022 }   /* [15] HOH015 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB023 }   /* [16] HOH016 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB024 }   /* [17] HOH017 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB025 }   /* [18] HOH018 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB026 }   /* [19] HOH019 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB027 }   /* [20] HOH020 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB028 }   /* [21] HOH021 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB029 }   /* [22] HOH022 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB030 }   /* [23] HOH023 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB031 }   /* [24] HOH024 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB032 }   /* [25] HOH025 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB033 }   /* [26] HOH026 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB034 }   /* [27] HOH027 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB035 }   /* [28] HOH028 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB036 }   /* [29] HOH029 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB037 }   /* [30] HOH030 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB038 }   /* [31] HOH031 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB039 }   /* [32] HOH032 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB040 }   /* [33] HOH033 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB041 }   /* [34] HOH034 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB042 }   /* [35] HOH035 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB043 }   /* [36] HOH036 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB044 }   /* [37] HOH037 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB045 }   /* [38] HOH038 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB046 }   /* [39] HOH039 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB047 }   /* [40] HOH040 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB048 }   /* [41] HOH041 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB049 }   /* [42] HOH042 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB050 }   /* [43] HOH043 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB051 }   /* [44] HOH044 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB052 }   /* [45] HOH045 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB053 }   /* [46] HOH046 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB054 }   /* [47] HOH047 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB055 }   /* [48] HOH048 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB056 }   /* [49] HOH049 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB057 }   /* [50] HOH050 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB058 }   /* [51] HOH051 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB059 }   /* [52] HOH052 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB060 }   /* [53] HOH053 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB061 }   /* [54] HOH054 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB062 }   /* [55] HOH055 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB063 }   /* [56] HOH056 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB064 }   /* [57] HOH057 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB065 }   /* [58] HOH058 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB066 }   /* [59] HOH059 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB067 }   /* [60] HOH060 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB068 }   /* [61] HOH061 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB069 }   /* [62] HOH062 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB070 }   /* [63] HOH063 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB071 }   /* [64] HOH064 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB072 }   /* [65] HOH065 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB073 }   /* [66] HOH066 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB074 }   /* [67] HOH067 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB075 }   /* [68] HOH068 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB076 }   /* [69] HOH069 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB077 }   /* [70] HOH070 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB078 }   /* [71] HOH071 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB079 }   /* [72] HOH072 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB080 }   /* [73] HOH073 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB081 }   /* [74] HOH074 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB082 }   /* [75] HOH075 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB083 }   /* [76] HOH076 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB084 }   /* [77] HOH077 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB085 }   /* [78] HOH078 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB086 }   /* [79] HOH079 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB087 }   /* [80] HOH080 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB088 }   /* [81] HOH081 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB089 }   /* [82] HOH082 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB090 }   /* [83] HOH083 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB091 }   /* [84] HOH084 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB092 }   /* [85] HOH085 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB093 }   /* [86] HOH086 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB094 }   /* [87] HOH087 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB095 }   /* [88] HOH088 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB096 }   /* [89] HOH089 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB097 }   /* [90] HOH090 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB098 }   /* [91] HOH091 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB099 }   /* [92] HOH092 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB100 }   /* [93] HOH093 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB101 }   /* [94] HOH094 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB102 }   /* [95] HOH095 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB103 }   /* [96] HOH096 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB104 }   /* [97] HOH097 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB105 }   /* [98] HOH098 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB106 }   /* [99] HOH099 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB107 }   /* [100] HOH100 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB108 }   /* [101] HOH101 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB109 }   /* [102] HOH102 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB110 }   /* [103] HOH103 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB111 }   /* [104] HOH104 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB112 }   /* [105] HOH105 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB113 }   /* [106] HOH106 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB114 }   /* [107] HOH107 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB115 }   /* [108] HOH108 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB116 }   /* [109] HOH109 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB117 }   /* [110] HOH110 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB118 }   /* [111] HOH111 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB119 }   /* [112] HOH112 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB120 }   /* [113] HOH113 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB121 }   /* [114] HOH114 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB122 }   /* [115] HOH115 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB123 }   /* [116] HOH116 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB124 }   /* [117] HOH117 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB125 }   /* [118] HOH118 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB126 }   /* [119] HOH119 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB127 }   /* [120] HOH120 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB128 }   /* [121] HOH121 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB129 }   /* [122] HOH122 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB130 }   /* [123] HOH123 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB131 }   /* [124] HOH124 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB132 }   /* [125] HOH125 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB133 }   /* [126] HOH126 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB134 }   /* [127] HOH127 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB135 }   /* [128] HOH128 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB136 }   /* [129] HOH129 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB137 }   /* [130] HOH130 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB138 }   /* [131] HOH131 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB139 }   /* [132] HOH132 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB140 }   /* [133] HOH133 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB141 }   /* [134] HOH134 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB142 }   /* [135] HOH135 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB143 }   /* [136] HOH136 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB144 }   /* [137] HOH137 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB145 }   /* [138] HOH138 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB146 }   /* [139] HOH139 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB147 }   /* [140] HOH140 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB148 }   /* [141] HOH141 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB149 }   /* [142] HOH142 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB150 }   /* [143] HOH143 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB151 }   /* [144] HOH144 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB152 }   /* [145] HOH145 */
#warning "BEVCDCFD-2652"
#if 0 /* BEVCDCFD-2652 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB153 }   /* [146] HOH146 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB004 }   /* [147] HOH147 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB005 }   /* [148] HOH148 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB006 }   /* [149] HOH149 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB007 }   /* [150] HOH150 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB008 }   /* [151] HOH151 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB009 }   /* [152] HOH152 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB010 }   /* [153] HOH153 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB011 }   /* [154] HOH154 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB012 }   /* [155] HOH155 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB013 }   /* [156] HOH156 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB014 }   /* [157] HOH157 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB015 }   /* [158] HOH158 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB016 }   /* [159] HOH159 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB017 }   /* [160] HOH160 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB018 }   /* [161] HOH161 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB019 }   /* [162] HOH162 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB020 }   /* [163] HOH163 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB021 }   /* [164] HOH164 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB022 }   /* [165] HOH165 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB023 }   /* [166] HOH166 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB024 }   /* [167] HOH167 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB025 }   /* [168] HOH168 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB026 }   /* [169] HOH169 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB027 }   /* [170] HOH170 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB028 }   /* [171] HOH171 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB029 }   /* [172] HOH172 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB030 }   /* [173] HOH173 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB031 }   /* [174] HOH174 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB032 }   /* [175] HOH175 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB033 }   /* [176] HOH176 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB034 }   /* [177] HOH177 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB035 }   /* [178] HOH178 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB036 }   /* [179] HOH179 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB037 }   /* [180] HOH180 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB038 }   /* [181] HOH181 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB039 }   /* [182] HOH182 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB040 }   /* [183] HOH183 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB041 }   /* [184] HOH184 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB042 }   /* [185] HOH185 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB043 }   /* [186] HOH186 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB044 }   /* [187] HOH187 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB045 }   /* [188] HOH188 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB046 }   /* [189] HOH189 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB047 }   /* [190] HOH190 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB048 }   /* [191] HOH191 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB049 }   /* [192] HOH192 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB050 }   /* [193] HOH193 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB051 }   /* [194] HOH194 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB052 }   /* [195] HOH195 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB053 }   /* [196] HOH196 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB054 }   /* [197] HOH197 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB055 }   /* [198] HOH198 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB056 }   /* [199] HOH199 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB057 }   /* [200] HOH200 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB058 }   /* [201] HOH201 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB059 }   /* [202] HOH202 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB060 }   /* [203] HOH203 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB061 }   /* [204] HOH204 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB062 }   /* [205] HOH205 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB063 }   /* [206] HOH206 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB064 }   /* [207] HOH207 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB065 }   /* [208] HOH208 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB066 }   /* [209] HOH209 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB067 }   /* [210] HOH210 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB068 }   /* [211] HOH211 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB069 }   /* [212] HOH212 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB070 }   /* [213] HOH213 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB071 }   /* [214] HOH214 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB072 }   /* [215] HOH215 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB073 }   /* [216] HOH216 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB074 }   /* [217] HOH217 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB075 }   /* [218] HOH218 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB076 }   /* [219] HOH219 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB077 }   /* [220] HOH220 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB078 }   /* [221] HOH221 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB079 }   /* [222] HOH222 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB080 }   /* [223] HOH223 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB081 }   /* [224] HOH224 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB082 }   /* [225] HOH225 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB083 }   /* [226] HOH226 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB084 }   /* [227] HOH227 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB085 }   /* [228] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB086 }   /* [229] HOH229 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB087 }   /* [230] HOH230 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB088 }   /* [231] HOH231 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB089 }   /* [232] HOH232 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB090 }   /* [233] HOH233 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB091 }   /* [234] HOH234 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB092 }   /* [235] HOH235 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB093 }   /* [236] HOH236 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB094 }   /* [237] HOH237 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB095 }   /* [238] HOH238 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB096 }   /* [239] HOH239 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB097 }   /* [240] HOH240 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB098 }   /* [241] HOH241 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB000 }   /* [242] HOH245 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB008 }   /* [243] HOH246 */
#else /* BEVCDCFD-2652 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB004 }   /* [146] HOH146 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB005 }   /* [147] HOH147 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB006 }   /* [148] HOH148 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB007 }   /* [149] HOH149 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB008 }   /* [150] HOH150 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB009 }   /* [151] HOH151 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB010 }   /* [152] HOH152 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB011 }   /* [153] HOH153 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB012 }   /* [154] HOH154 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB013 }   /* [155] HOH155 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB014 }   /* [156] HOH156 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB015 }   /* [157] HOH157 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB016 }   /* [158] HOH158 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB017 }   /* [159] HOH159 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB018 }   /* [160] HOH160 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB019 }   /* [161] HOH161 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB020 }   /* [162] HOH162 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB021 }   /* [163] HOH163 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB022 }   /* [164] HOH164 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB023 }   /* [165] HOH165 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB024 }   /* [166] HOH166 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB025 }   /* [167] HOH167 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB026 }   /* [168] HOH168 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB027 }   /* [169] HOH169 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB028 }   /* [170] HOH170 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB029 }   /* [171] HOH171 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB030 }   /* [172] HOH172 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB031 }   /* [173] HOH173 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB032 }   /* [174] HOH174 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB033 }   /* [175] HOH175 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB034 }   /* [176] HOH176 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB035 }   /* [177] HOH177 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB036 }   /* [178] HOH178 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB037 }   /* [179] HOH179 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB038 }   /* [180] HOH180 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB039 }   /* [181] HOH181 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB040 }   /* [182] HOH182 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB041 }   /* [183] HOH183 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB042 }   /* [184] HOH184 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB043 }   /* [185] HOH185 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB044 }   /* [186] HOH186 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB045 }   /* [187] HOH187 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB046 }   /* [188] HOH188 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB047 }   /* [189] HOH189 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB048 }   /* [190] HOH190 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB049 }   /* [191] HOH191 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB050 }   /* [192] HOH192 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB051 }   /* [193] HOH193 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB052 }   /* [194] HOH194 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB053 }   /* [195] HOH195 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB054 }   /* [196] HOH196 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB055 }   /* [197] HOH197 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB056 }   /* [198] HOH198 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB057 }   /* [199] HOH199 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB058 }   /* [200] HOH200 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB059 }   /* [201] HOH201 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB060 }   /* [202] HOH202 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB061 }   /* [203] HOH203 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB062 }   /* [204] HOH204 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB063 }   /* [205] HOH205 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB064 }   /* [206] HOH206 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB065 }   /* [207] HOH207 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB066 }   /* [208] HOH208 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB067 }   /* [209] HOH209 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB068 }   /* [210] HOH210 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB069 }   /* [211] HOH211 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB070 }   /* [212] HOH212 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB071 }   /* [213] HOH213 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB072 }   /* [214] HOH214 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB073 }   /* [215] HOH215 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB074 }   /* [216] HOH216 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB075 }   /* [217] HOH217 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB076 }   /* [218] HOH218 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB077 }   /* [219] HOH219 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB078 }   /* [220] HOH220 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB079 }   /* [221] HOH221 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB080 }   /* [222] HOH222 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB081 }   /* [223] HOH223 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB082 }   /* [224] HOH224 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB083 }   /* [225] HOH225 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB084 }   /* [226] HOH226 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB085 }   /* [227] HOH227 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB086 }   /* [228] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB087 }   /* [229] HOH229 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_3,  (uint8)CAN_MB001 }   /* [230] HOH233 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB008 }   /* [231] HOH234 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB009 }   /* [232] HOH235 */
#endif /* BEVCDCFD-2652 */
  /*========== User define Area [End] ============*/
};
#endif /* (CAN_CFG_TRANSMIT == CAN_USE) */


/*==================================================================*/
/* Baudrate Switch Configuration Table                              */
/*==================================================================*/
/* param1 : Baudrate Switch Number                                  */
/* value  : Baudrate Switch Configuration                           */
/*   - u4Baudrate       Nominal Baudrate                            */
/*   - u4DataBaudrate   Data Baudrate                               */
/*   - u4BaudrateInfo_1 Baudrate Information1(Dependence on MCU)    */
/*   - u4BaudrateInfo_2 Baudrate Information2(Dependence on MCU)    */
/*   - u4BaudrateInfo_3 Baudrate Information3(Dependence on MCU)    */
/*------------------------------------------------------------------*/
CanConst CanBaudrateSwtCfgType Can_stBaudrateSwtCfgTbl[ CAN_CFG_BRSCFGTBL_SIZE ] =
{
  /* u4Baudrate                     , u4DataBaudrate                  , u4BaudrateInfo_1            , u4BaudrateInfo_2            , u4BaudrateInfo_3              */
  /*================================================================== User define Area [Start] ==================================================================*/
     { (uint32)CAN_500KBPS_40M_PTN2 , (uint32)CAN_DB_2MBPS_40M_PTN2   , (uint32)CAN_BAUDRATEINFO_1_1, (uint32)CAN_BAUDRATEINFO_2_1, (uint32)CAN_BAUDRATEINFO_3_1 }   /* [0] Baudrate Switch Number00 */
  /*================================================================== User define Area [End] ====================================================================*/
};


/* Number of Baudrate Switch Configuration Table Elements (No need to change) */
CanConst uint8 Can_stBRSwtCfgTbl_ARYSIZE = CAN_CFG_BRSCFGTBL_SIZE;


/******************************************************************************/
/*                      USER Configuration                                    */
/******************************************************************************/


/******************************************************************************/
/*                      Static Configuration Table                            */
/******************************************************************************/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#endif /* (CAN_CFG_CAN == CAN_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
