/* can_rscf4_pbcfg_c_m10700_v2-2-0                                          */
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
     { (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB048 }   /* [0] HOH000 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB049 }   /* [1] HOH001 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB050 }   /* [2] HOH002 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB051 }   /* [3] HOH003 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB052 }   /* [4] HOH004 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB053 }   /* [5] HOH005 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB054 }   /* [6] HOH006 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB055 }   /* [7] HOH007 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB056 }   /* [8] HOH008 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB057 }   /* [9] HOH009 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB058 }   /* [10] HOH010 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB059 }   /* [11] HOH011 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB060 }   /* [12] HOH012 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB061 }   /* [13] HOH013 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB062 }   /* [14] HOH014 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB063 }   /* [15] HOH015 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB064 }   /* [16] HOH016 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB065 }   /* [17] HOH017 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB066 }   /* [18] HOH018 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB067 }   /* [19] HOH019 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB068 }   /* [20] HOH020 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB069 }   /* [21] HOH021 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB070 }   /* [22] HOH022 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB071 }   /* [23] HOH023 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB072 }   /* [24] HOH024 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB073 }   /* [25] HOH025 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB074 }   /* [26] HOH026 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB075 }   /* [27] HOH027 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB076 }   /* [28] HOH028 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB077 }   /* [29] HOH029 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB078 }   /* [30] HOH030 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB079 }   /* [31] HOH031 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB080 }   /* [32] HOH032 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB081 }   /* [33] HOH033 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB082 }   /* [34] HOH034 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB083 }   /* [35] HOH035 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB084 }   /* [36] HOH036 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB085 }   /* [37] HOH037 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB086 }   /* [38] HOH038 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB087 }   /* [39] HOH039 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB088 }   /* [40] HOH040 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB089 }   /* [41] HOH041 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB090 }   /* [42] HOH042 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB091 }   /* [43] HOH043 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB092 }   /* [44] HOH044 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB093 }   /* [45] HOH045 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB094 }   /* [46] HOH046 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB095 }   /* [47] HOH047 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB096 }   /* [48] HOH048 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB097 }   /* [49] HOH049 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB098 }   /* [50] HOH050 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB099 }   /* [51] HOH051 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB100 }   /* [52] HOH052 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB101 }   /* [53] HOH053 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB102 }   /* [54] HOH054 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB103 }   /* [55] HOH055 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB104 }   /* [56] HOH056 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB105 }   /* [57] HOH057 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB106 }   /* [58] HOH058 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB107 }   /* [59] HOH059 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB108 }   /* [60] HOH060 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB109 }   /* [61] HOH061 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB110 }   /* [62] HOH062 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB111 }   /* [63] HOH063 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB112 }   /* [64] HOH064 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB113 }   /* [65] HOH065 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB114 }   /* [66] HOH066 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB115 }   /* [67] HOH067 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB116 }   /* [68] HOH068 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB117 }   /* [69] HOH069 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB118 }   /* [70] HOH070 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB119 }   /* [71] HOH071 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB120 }   /* [72] HOH072 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB121 }   /* [73] HOH073 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB122 }   /* [74] HOH074 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB123 }   /* [75] HOH075 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB124 }   /* [76] HOH076 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB125 }   /* [77] HOH077 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB126 }   /* [78] HOH078 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB127 }   /* [79] HOH079 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB128 }   /* [80] HOH080 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB129 }   /* [81] HOH081 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB130 }   /* [82] HOH082 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB131 }   /* [83] HOH083 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB132 }   /* [84] HOH084 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB133 }   /* [85] HOH085 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB134 }   /* [86] HOH086 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB135 }   /* [87] HOH087 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB136 }   /* [88] HOH088 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB137 }   /* [89] HOH089 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB138 }   /* [90] HOH090 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB139 }   /* [91] HOH091 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB140 }   /* [92] HOH092 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB141 }   /* [93] HOH093 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB142 }   /* [94] HOH094 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB143 }   /* [95] HOH095 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB144 }   /* [96] HOH096 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB145 }   /* [97] HOH097 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB146 }   /* [98] HOH098 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB147 }   /* [99] HOH099 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB148 }   /* [100] HOH100 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB149 }   /* [101] HOH101 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB150 }   /* [102] HOH102 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB151 }   /* [103] HOH103 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB152 }   /* [104] HOH104 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB153 }   /* [105] HOH105 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB154 }   /* [106] HOH106 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB155 }   /* [107] HOH107 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB156 }   /* [108] HOH108 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB157 }   /* [109] HOH109 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB158 }   /* [110] HOH110 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB159 }   /* [111] HOH111 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB160 }   /* [112] HOH112 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB161 }   /* [113] HOH113 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB162 }   /* [114] HOH114 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB163 }   /* [115] HOH115 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB164 }   /* [116] HOH116 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB165 }   /* [117] HOH117 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB166 }   /* [118] HOH118 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB167 }   /* [119] HOH119 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB168 }   /* [120] HOH120 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB169 }   /* [121] HOH121 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB170 }   /* [122] HOH122 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB171 }   /* [123] HOH123 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB172 }   /* [124] HOH124 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB173 }   /* [125] HOH125 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB174 }   /* [126] HOH126 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB175 }   /* [127] HOH127 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB176 }   /* [128] HOH128 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB177 }   /* [129] HOH129 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB178 }   /* [130] HOH130 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB179 }   /* [131] HOH131 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB180 }   /* [132] HOH132 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB181 }   /* [133] HOH133 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB182 }   /* [134] HOH134 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB183 }   /* [135] HOH135 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB184 }   /* [136] HOH136 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB185 }   /* [137] HOH137 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB186 }   /* [138] HOH138 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB187 }   /* [139] HOH139 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB188 }   /* [140] HOH140 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB189 }   /* [141] HOH141 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB190 }   /* [142] HOH142 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB027 }   /* [143] HOH143 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB028 }   /* [144] HOH144 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB029 }   /* [145] HOH145 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB030 }   /* [146] HOH146 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB031 }   /* [147] HOH147 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB032 }   /* [148] HOH148 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB033 }   /* [149] HOH149 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB034 }   /* [150] HOH150 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB035 }   /* [151] HOH151 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB036 }   /* [152] HOH152 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB037 }   /* [153] HOH153 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB038 }   /* [154] HOH154 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB039 }   /* [155] HOH155 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB040 }   /* [156] HOH156 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB041 }   /* [157] HOH157 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB042 }   /* [158] HOH158 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB043 }   /* [159] HOH159 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB044 }   /* [160] HOH160 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB045 }   /* [161] HOH161 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB046 }   /* [162] HOH162 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB047 }   /* [163] HOH163 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB048 }   /* [164] HOH164 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB049 }   /* [165] HOH165 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB050 }   /* [166] HOH166 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB051 }   /* [167] HOH167 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB052 }   /* [168] HOH168 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB053 }   /* [169] HOH169 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB054 }   /* [170] HOH170 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB055 }   /* [171] HOH171 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB056 }   /* [172] HOH172 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB057 }   /* [173] HOH173 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB058 }   /* [174] HOH174 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB059 }   /* [175] HOH175 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB060 }   /* [176] HOH176 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB061 }   /* [177] HOH177 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB062 }   /* [178] HOH178 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB063 }   /* [179] HOH179 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB064 }   /* [180] HOH180 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB065 }   /* [181] HOH181 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB066 }   /* [182] HOH182 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB067 }   /* [183] HOH183 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB068 }   /* [184] HOH184 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB069 }   /* [185] HOH185 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB070 }   /* [186] HOH186 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB071 }   /* [187] HOH187 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB072 }   /* [188] HOH188 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB073 }   /* [189] HOH189 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB074 }   /* [190] HOH190 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB075 }   /* [191] HOH191 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB076 }   /* [192] HOH192 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB077 }   /* [193] HOH193 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB078 }   /* [194] HOH194 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB079 }   /* [195] HOH195 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB080 }   /* [196] HOH196 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB081 }   /* [197] HOH197 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB082 }   /* [198] HOH198 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB083 }   /* [199] HOH199 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB084 }   /* [200] HOH200 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB085 }   /* [201] HOH201 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB086 }   /* [202] HOH202 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB087 }   /* [203] HOH203 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB088 }   /* [204] HOH204 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB089 }   /* [205] HOH205 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB090 }   /* [206] HOH206 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB091 }   /* [207] HOH207 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB092 }   /* [208] HOH208 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB093 }   /* [209] HOH209 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB094 }   /* [210] HOH210 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB095 }   /* [211] HOH211 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB096 }   /* [212] HOH212 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB097 }   /* [213] HOH213 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB098 }   /* [214] HOH214 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB099 }   /* [215] HOH215 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB100 }   /* [216] HOH216 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB101 }   /* [217] HOH217 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB102 }   /* [218] HOH218 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB103 }   /* [219] HOH219 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB104 }   /* [220] HOH220 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB105 }   /* [221] HOH221 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB106 }   /* [222] HOH222 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB107 }   /* [223] HOH223 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB108 }   /* [224] HOH224 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB109 }   /* [225] HOH225 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB110 }   /* [226] HOH226 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB111 }   /* [227] HOH227 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB112 }   /* [228] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB113 }   /* [229] HOH229 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB114 }   /* [230] HOH230 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB115 }   /* [231] HOH231 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB116 }   /* [232] HOH232 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB117 }   /* [233] HOH233 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB118 }   /* [234] HOH234 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB119 }   /* [235] HOH235 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB120 }   /* [236] HOH236 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB121 }   /* [237] HOH237 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB046 }   /* [238] HOH238 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB047 }   /* [239] HOH239 */
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
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
