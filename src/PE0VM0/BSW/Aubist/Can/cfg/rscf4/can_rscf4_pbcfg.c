/* can_rscf4_pbcfg_c_m10700_v2-2-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
     { (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB046 }   /* [0] HOH000 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB047 }   /* [1] HOH001 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB048 }   /* [2] HOH002 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB049 }   /* [3] HOH003 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB050 }   /* [4] HOH004 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB051 }   /* [5] HOH005 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB052 }   /* [6] HOH006 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB053 }   /* [7] HOH007 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB054 }   /* [8] HOH008 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB055 }   /* [9] HOH009 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB056 }   /* [10] HOH010 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB057 }   /* [11] HOH011 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB058 }   /* [12] HOH012 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB059 }   /* [13] HOH013 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB060 }   /* [14] HOH014 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB061 }   /* [15] HOH015 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB062 }   /* [16] HOH016 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB063 }   /* [17] HOH017 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB064 }   /* [18] HOH018 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB065 }   /* [19] HOH019 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB066 }   /* [20] HOH020 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB067 }   /* [21] HOH021 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB068 }   /* [22] HOH022 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB069 }   /* [23] HOH023 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB070 }   /* [24] HOH024 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB071 }   /* [25] HOH025 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB072 }   /* [26] HOH026 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB073 }   /* [27] HOH027 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB074 }   /* [28] HOH028 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB075 }   /* [29] HOH029 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB076 }   /* [30] HOH030 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB077 }   /* [31] HOH031 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB078 }   /* [32] HOH032 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB079 }   /* [33] HOH033 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB080 }   /* [34] HOH034 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB081 }   /* [35] HOH035 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB082 }   /* [36] HOH036 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB083 }   /* [37] HOH037 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB084 }   /* [38] HOH038 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB085 }   /* [39] HOH039 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB086 }   /* [40] HOH040 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB087 }   /* [41] HOH041 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB088 }   /* [42] HOH042 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB089 }   /* [43] HOH043 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB090 }   /* [44] HOH044 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB091 }   /* [45] HOH045 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB092 }   /* [46] HOH046 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB093 }   /* [47] HOH047 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB094 }   /* [48] HOH048 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB095 }   /* [49] HOH049 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB096 }   /* [50] HOH050 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB097 }   /* [51] HOH051 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB098 }   /* [52] HOH052 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB099 }   /* [53] HOH053 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB100 }   /* [54] HOH054 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB101 }   /* [55] HOH055 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB102 }   /* [56] HOH056 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB103 }   /* [57] HOH057 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB104 }   /* [58] HOH058 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB105 }   /* [59] HOH059 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB106 }   /* [60] HOH060 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB107 }   /* [61] HOH061 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB108 }   /* [62] HOH062 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB109 }   /* [63] HOH063 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB110 }   /* [64] HOH064 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB111 }   /* [65] HOH065 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB112 }   /* [66] HOH066 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB113 }   /* [67] HOH067 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB114 }   /* [68] HOH068 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB115 }   /* [69] HOH069 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB116 }   /* [70] HOH070 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB117 }   /* [71] HOH071 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB118 }   /* [72] HOH072 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB119 }   /* [73] HOH073 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB120 }   /* [74] HOH074 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB121 }   /* [75] HOH075 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB122 }   /* [76] HOH076 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB123 }   /* [77] HOH077 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB124 }   /* [78] HOH078 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB125 }   /* [79] HOH079 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB126 }   /* [80] HOH080 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB127 }   /* [81] HOH081 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB128 }   /* [82] HOH082 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB129 }   /* [83] HOH083 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB130 }   /* [84] HOH084 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB131 }   /* [85] HOH085 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB132 }   /* [86] HOH086 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB133 }   /* [87] HOH087 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB134 }   /* [88] HOH088 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB135 }   /* [89] HOH089 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB136 }   /* [90] HOH090 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB137 }   /* [91] HOH091 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB138 }   /* [92] HOH092 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB139 }   /* [93] HOH093 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB140 }   /* [94] HOH094 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB141 }   /* [95] HOH095 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB142 }   /* [96] HOH096 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB143 }   /* [97] HOH097 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB144 }   /* [98] HOH098 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB145 }   /* [99] HOH099 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB146 }   /* [100] HOH100 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB147 }   /* [101] HOH101 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB148 }   /* [102] HOH102 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB149 }   /* [103] HOH103 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB150 }   /* [104] HOH104 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB151 }   /* [105] HOH105 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB152 }   /* [106] HOH106 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB153 }   /* [107] HOH107 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB154 }   /* [108] HOH108 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB155 }   /* [109] HOH109 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB156 }   /* [110] HOH110 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB157 }   /* [111] HOH111 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB158 }   /* [112] HOH112 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB159 }   /* [113] HOH113 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB160 }   /* [114] HOH114 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB161 }   /* [115] HOH115 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB162 }   /* [116] HOH116 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB163 }   /* [117] HOH117 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB164 }   /* [118] HOH118 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB165 }   /* [119] HOH119 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB166 }   /* [120] HOH120 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB167 }   /* [121] HOH121 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB168 }   /* [122] HOH122 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB169 }   /* [123] HOH123 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB170 }   /* [124] HOH124 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB171 }   /* [125] HOH125 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB172 }   /* [126] HOH126 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB173 }   /* [127] HOH127 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB174 }   /* [128] HOH128 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB175 }   /* [129] HOH129 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB176 }   /* [130] HOH130 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB177 }   /* [131] HOH131 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB178 }   /* [132] HOH132 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB179 }   /* [133] HOH133 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB180 }   /* [134] HOH134 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB181 }   /* [135] HOH135 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB182 }   /* [136] HOH136 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB183 }   /* [137] HOH137 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB184 }   /* [138] HOH138 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB185 }   /* [139] HOH139 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB186 }   /* [140] HOH140 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB187 }   /* [141] HOH141 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB188 }   /* [142] HOH142 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB189 }   /* [143] HOH143 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB190 }   /* [144] HOH144 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB191 }   /* [145] HOH145 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB027 }   /* [146] HOH146 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB028 }   /* [147] HOH147 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB029 }   /* [148] HOH148 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB030 }   /* [149] HOH149 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB031 }   /* [150] HOH150 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB032 }   /* [151] HOH151 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB033 }   /* [152] HOH152 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB034 }   /* [153] HOH153 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB035 }   /* [154] HOH154 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB036 }   /* [155] HOH155 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB037 }   /* [156] HOH156 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB038 }   /* [157] HOH157 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB039 }   /* [158] HOH158 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB040 }   /* [159] HOH159 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB041 }   /* [160] HOH160 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB042 }   /* [161] HOH161 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB043 }   /* [162] HOH162 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB044 }   /* [163] HOH163 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB045 }   /* [164] HOH164 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB046 }   /* [165] HOH165 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB047 }   /* [166] HOH166 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB048 }   /* [167] HOH167 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB049 }   /* [168] HOH168 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB050 }   /* [169] HOH169 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB051 }   /* [170] HOH170 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB052 }   /* [171] HOH171 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB053 }   /* [172] HOH172 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB054 }   /* [173] HOH173 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB055 }   /* [174] HOH174 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB056 }   /* [175] HOH175 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB057 }   /* [176] HOH176 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB058 }   /* [177] HOH177 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB059 }   /* [178] HOH178 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB060 }   /* [179] HOH179 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB061 }   /* [180] HOH180 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB062 }   /* [181] HOH181 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB063 }   /* [182] HOH182 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB064 }   /* [183] HOH183 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB065 }   /* [184] HOH184 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB066 }   /* [185] HOH185 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB067 }   /* [186] HOH186 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB068 }   /* [187] HOH187 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB069 }   /* [188] HOH188 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB070 }   /* [189] HOH189 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB071 }   /* [190] HOH190 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB072 }   /* [191] HOH191 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB073 }   /* [192] HOH192 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB074 }   /* [193] HOH193 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB075 }   /* [194] HOH194 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB076 }   /* [195] HOH195 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB077 }   /* [196] HOH196 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB078 }   /* [197] HOH197 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB079 }   /* [198] HOH198 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB080 }   /* [199] HOH199 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB081 }   /* [200] HOH200 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB082 }   /* [201] HOH201 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB083 }   /* [202] HOH202 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB084 }   /* [203] HOH203 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB085 }   /* [204] HOH204 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB086 }   /* [205] HOH205 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB087 }   /* [206] HOH206 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB088 }   /* [207] HOH207 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB089 }   /* [208] HOH208 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB090 }   /* [209] HOH209 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB091 }   /* [210] HOH210 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB092 }   /* [211] HOH211 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB093 }   /* [212] HOH212 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB094 }   /* [213] HOH213 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB095 }   /* [214] HOH214 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB096 }   /* [215] HOH215 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB097 }   /* [216] HOH216 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB098 }   /* [217] HOH217 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB099 }   /* [218] HOH218 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB100 }   /* [219] HOH219 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB101 }   /* [220] HOH220 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB102 }   /* [221] HOH221 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB103 }   /* [222] HOH222 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB104 }   /* [223] HOH223 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB105 }   /* [224] HOH224 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB106 }   /* [225] HOH225 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB107 }   /* [226] HOH226 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB108 }   /* [227] HOH227 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB109 }   /* [228] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB110 }   /* [229] HOH229 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB111 }   /* [230] HOH230 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB112 }   /* [231] HOH231 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB113 }   /* [232] HOH232 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB114 }   /* [233] HOH233 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB115 }   /* [234] HOH234 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB116 }   /* [235] HOH235 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB117 }   /* [236] HOH236 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB118 }   /* [237] HOH237 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB119 }   /* [238] HOH238 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB120 }   /* [239] HOH239 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB121 }   /* [240] HOH240 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB004 }   /* [241] HOH241 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB005 }   /* [242] HOH242 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB006 }   /* [243] HOH243 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB007 }   /* [244] HOH244 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB008 }   /* [245] HOH245 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB009 }   /* [246] HOH246 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB010 }   /* [247] HOH247 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB011 }   /* [248] HOH248 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB012 }   /* [249] HOH249 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB013 }   /* [250] HOH250 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB014 }   /* [251] HOH251 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB015 }   /* [252] HOH252 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB016 }   /* [253] HOH253 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB017 }   /* [254] HOH254 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB018 }   /* [255] HOH255 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB019 }   /* [256] HOH256 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB020 }   /* [257] HOH257 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB021 }   /* [258] HOH258 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB022 }   /* [259] HOH259 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB023 }   /* [260] HOH260 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB024 }   /* [261] HOH261 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB025 }   /* [262] HOH262 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB026 }   /* [263] HOH263 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB027 }   /* [264] HOH264 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB028 }   /* [265] HOH265 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB029 }   /* [266] HOH266 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB030 }   /* [267] HOH267 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB031 }   /* [268] HOH268 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB032 }   /* [269] HOH269 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB033 }   /* [270] HOH270 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB034 }   /* [271] HOH271 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB035 }   /* [272] HOH272 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB036 }   /* [273] HOH273 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB037 }   /* [274] HOH274 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB038 }   /* [275] HOH275 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB039 }   /* [276] HOH276 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB040 }   /* [277] HOH277 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB041 }   /* [278] HOH278 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB042 }   /* [279] HOH279 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB043 }   /* [280] HOH280 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB044 }   /* [281] HOH281 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB045 }   /* [282] HOH282 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB004 }   /* [283] HOH283 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB005 }   /* [284] HOH284 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB006 }   /* [285] HOH285 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB007 }   /* [286] HOH286 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB008 }   /* [287] HOH287 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB009 }   /* [288] HOH288 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB010 }   /* [289] HOH289 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB011 }   /* [290] HOH290 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB012 }   /* [291] HOH291 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB013 }   /* [292] HOH292 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB014 }   /* [293] HOH293 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB015 }   /* [294] HOH294 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB016 }   /* [295] HOH295 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB017 }   /* [296] HOH296 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB018 }   /* [297] HOH297 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB019 }   /* [298] HOH298 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB020 }   /* [299] HOH299 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB021 }   /* [300] HOH300 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB022 }   /* [301] HOH301 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB023 }   /* [302] HOH302 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB024 }   /* [303] HOH303 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB025 }   /* [304] HOH304 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB026 }   /* [305] HOH305 */
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
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
