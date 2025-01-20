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
     { (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB044 }   /* [0] HOH000 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB045 }   /* [1] HOH001 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB046 }   /* [2] HOH002 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB047 }   /* [3] HOH003 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB048 }   /* [4] HOH004 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB049 }   /* [5] HOH005 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB050 }   /* [6] HOH006 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB051 }   /* [7] HOH007 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB052 }   /* [8] HOH008 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB053 }   /* [9] HOH009 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB054 }   /* [10] HOH010 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB055 }   /* [11] HOH011 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB056 }   /* [12] HOH012 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB057 }   /* [13] HOH013 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB058 }   /* [14] HOH014 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB059 }   /* [15] HOH015 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB060 }   /* [16] HOH016 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB061 }   /* [17] HOH017 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB062 }   /* [18] HOH018 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB063 }   /* [19] HOH019 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB064 }   /* [20] HOH020 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB065 }   /* [21] HOH021 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB066 }   /* [22] HOH022 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB067 }   /* [23] HOH023 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB068 }   /* [24] HOH024 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB069 }   /* [25] HOH025 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB070 }   /* [26] HOH026 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB071 }   /* [27] HOH027 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB072 }   /* [28] HOH028 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB073 }   /* [29] HOH029 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB074 }   /* [30] HOH030 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB075 }   /* [31] HOH031 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB076 }   /* [32] HOH032 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB077 }   /* [33] HOH033 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB078 }   /* [34] HOH034 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB079 }   /* [35] HOH035 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB080 }   /* [36] HOH036 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB081 }   /* [37] HOH037 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB082 }   /* [38] HOH038 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB083 }   /* [39] HOH039 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB084 }   /* [40] HOH040 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB085 }   /* [41] HOH041 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB086 }   /* [42] HOH042 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB087 }   /* [43] HOH043 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB088 }   /* [44] HOH044 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB089 }   /* [45] HOH045 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB090 }   /* [46] HOH046 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB091 }   /* [47] HOH047 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB092 }   /* [48] HOH048 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB093 }   /* [49] HOH049 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB094 }   /* [50] HOH050 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB095 }   /* [51] HOH051 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB096 }   /* [52] HOH052 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB097 }   /* [53] HOH053 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB098 }   /* [54] HOH054 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB099 }   /* [55] HOH055 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB100 }   /* [56] HOH056 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB101 }   /* [57] HOH057 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB102 }   /* [58] HOH058 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB103 }   /* [59] HOH059 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB104 }   /* [60] HOH060 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB105 }   /* [61] HOH061 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB106 }   /* [62] HOH062 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB107 }   /* [63] HOH063 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB108 }   /* [64] HOH064 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB109 }   /* [65] HOH065 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB110 }   /* [66] HOH066 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB111 }   /* [67] HOH067 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB112 }   /* [68] HOH068 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB113 }   /* [69] HOH069 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB114 }   /* [70] HOH070 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB115 }   /* [71] HOH071 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB116 }   /* [72] HOH072 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB117 }   /* [73] HOH073 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB118 }   /* [74] HOH074 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB119 }   /* [75] HOH075 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB120 }   /* [76] HOH076 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB121 }   /* [77] HOH077 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB122 }   /* [78] HOH078 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB123 }   /* [79] HOH079 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB124 }   /* [80] HOH080 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB125 }   /* [81] HOH081 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB126 }   /* [82] HOH082 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB127 }   /* [83] HOH083 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB128 }   /* [84] HOH084 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB129 }   /* [85] HOH085 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB130 }   /* [86] HOH086 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB131 }   /* [87] HOH087 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB132 }   /* [88] HOH088 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB133 }   /* [89] HOH089 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB134 }   /* [90] HOH090 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB135 }   /* [91] HOH091 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB136 }   /* [92] HOH092 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB137 }   /* [93] HOH093 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB138 }   /* [94] HOH094 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB139 }   /* [95] HOH095 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB140 }   /* [96] HOH096 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB141 }   /* [97] HOH097 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB142 }   /* [98] HOH098 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB143 }   /* [99] HOH099 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB144 }   /* [100] HOH100 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB145 }   /* [101] HOH101 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB146 }   /* [102] HOH102 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB147 }   /* [103] HOH103 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB148 }   /* [104] HOH104 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB149 }   /* [105] HOH105 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB150 }   /* [106] HOH106 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB151 }   /* [107] HOH107 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB152 }   /* [108] HOH108 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB153 }   /* [109] HOH109 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB154 }   /* [110] HOH110 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB155 }   /* [111] HOH111 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB156 }   /* [112] HOH112 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB157 }   /* [113] HOH113 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB158 }   /* [114] HOH114 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB159 }   /* [115] HOH115 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB160 }   /* [116] HOH116 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB161 }   /* [117] HOH117 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB162 }   /* [118] HOH118 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB163 }   /* [119] HOH119 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB164 }   /* [120] HOH120 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB165 }   /* [121] HOH121 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB166 }   /* [122] HOH122 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB167 }   /* [123] HOH123 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB168 }   /* [124] HOH124 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB169 }   /* [125] HOH125 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB170 }   /* [126] HOH126 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB171 }   /* [127] HOH127 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB172 }   /* [128] HOH128 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB173 }   /* [129] HOH129 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB174 }   /* [130] HOH130 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB175 }   /* [131] HOH131 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB176 }   /* [132] HOH132 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB177 }   /* [133] HOH133 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB178 }   /* [134] HOH134 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB179 }   /* [135] HOH135 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB180 }   /* [136] HOH136 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB181 }   /* [137] HOH137 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB182 }   /* [138] HOH138 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB183 }   /* [139] HOH139 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB184 }   /* [140] HOH140 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB185 }   /* [141] HOH141 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB186 }   /* [142] HOH142 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB187 }   /* [143] HOH143 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB188 }   /* [144] HOH144 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB189 }   /* [145] HOH145 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB190 }   /* [146] HOH146 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB191 }   /* [147] HOH147 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB023 }   /* [148] HOH148 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB024 }   /* [149] HOH149 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB025 }   /* [150] HOH150 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB026 }   /* [151] HOH151 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB027 }   /* [152] HOH152 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB028 }   /* [153] HOH153 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB029 }   /* [154] HOH154 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB030 }   /* [155] HOH155 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB031 }   /* [156] HOH156 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB032 }   /* [157] HOH157 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB033 }   /* [158] HOH158 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB034 }   /* [159] HOH159 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB035 }   /* [160] HOH160 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB036 }   /* [161] HOH161 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB037 }   /* [162] HOH162 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB038 }   /* [163] HOH163 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB039 }   /* [164] HOH164 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB040 }   /* [165] HOH165 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB041 }   /* [166] HOH166 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB042 }   /* [167] HOH167 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB043 }   /* [168] HOH168 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB044 }   /* [169] HOH169 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB045 }   /* [170] HOH170 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB046 }   /* [171] HOH171 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB047 }   /* [172] HOH172 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB048 }   /* [173] HOH173 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB049 }   /* [174] HOH174 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB050 }   /* [175] HOH175 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB051 }   /* [176] HOH176 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB052 }   /* [177] HOH177 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB053 }   /* [178] HOH178 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB054 }   /* [179] HOH179 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB055 }   /* [180] HOH180 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB056 }   /* [181] HOH181 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB057 }   /* [182] HOH182 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB058 }   /* [183] HOH183 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB059 }   /* [184] HOH184 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB060 }   /* [185] HOH185 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB061 }   /* [186] HOH186 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB062 }   /* [187] HOH187 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB063 }   /* [188] HOH188 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB064 }   /* [189] HOH189 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB065 }   /* [190] HOH190 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB066 }   /* [191] HOH191 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB067 }   /* [192] HOH192 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB068 }   /* [193] HOH193 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB069 }   /* [194] HOH194 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB070 }   /* [195] HOH195 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB071 }   /* [196] HOH196 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB072 }   /* [197] HOH197 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB073 }   /* [198] HOH198 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB074 }   /* [199] HOH199 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB075 }   /* [200] HOH200 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB076 }   /* [201] HOH201 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB077 }   /* [202] HOH202 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB078 }   /* [203] HOH203 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB079 }   /* [204] HOH204 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB080 }   /* [205] HOH205 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB081 }   /* [206] HOH206 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB082 }   /* [207] HOH207 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB083 }   /* [208] HOH208 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB084 }   /* [209] HOH209 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB085 }   /* [210] HOH210 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB086 }   /* [211] HOH211 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB087 }   /* [212] HOH212 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB088 }   /* [213] HOH213 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB089 }   /* [214] HOH214 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB090 }   /* [215] HOH215 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB091 }   /* [216] HOH216 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB092 }   /* [217] HOH217 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB093 }   /* [218] HOH218 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB094 }   /* [219] HOH219 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB095 }   /* [220] HOH220 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB096 }   /* [221] HOH221 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB097 }   /* [222] HOH222 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB098 }   /* [223] HOH223 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB099 }   /* [224] HOH224 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB100 }   /* [225] HOH225 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB101 }   /* [226] HOH226 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB102 }   /* [227] HOH227 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB103 }   /* [228] HOH228 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB104 }   /* [229] HOH229 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB105 }   /* [230] HOH230 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB106 }   /* [231] HOH231 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB107 }   /* [232] HOH232 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB108 }   /* [233] HOH233 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB109 }   /* [234] HOH234 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB110 }   /* [235] HOH235 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB111 }   /* [236] HOH236 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB112 }   /* [237] HOH237 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB113 }   /* [238] HOH238 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB114 }   /* [239] HOH239 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB115 }   /* [240] HOH240 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB116 }   /* [241] HOH241 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB117 }   /* [242] HOH242 */
  /*--- Transmission -----------------------------*/
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB000 }   /* [243] HOH243 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB001 }   /* [244] HOH244 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB002 }   /* [245] HOH245 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB003 }   /* [246] HOH246 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB004 }   /* [247] HOH247 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB005 }   /* [248] HOH248 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB006 }   /* [249] HOH249 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB007 }   /* [250] HOH250 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB008 }   /* [251] HOH251 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB009 }   /* [252] HOH252 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB010 }   /* [253] HOH253 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB011 }   /* [254] HOH254 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB012 }   /* [255] HOH255 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB013 }   /* [256] HOH256 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB014 }   /* [257] HOH257 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB015 }   /* [258] HOH258 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB016 }   /* [259] HOH259 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB017 }   /* [260] HOH260 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB018 }   /* [261] HOH261 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB019 }   /* [262] HOH262 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB020 }   /* [263] HOH263 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB021 }   /* [264] HOH264 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB022 }   /* [265] HOH265 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB023 }   /* [266] HOH266 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB024 }   /* [267] HOH267 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB025 }   /* [268] HOH268 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB026 }   /* [269] HOH269 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB027 }   /* [270] HOH270 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB028 }   /* [271] HOH271 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB029 }   /* [272] HOH272 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB030 }   /* [273] HOH273 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB031 }   /* [274] HOH274 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB032 }   /* [275] HOH275 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB033 }   /* [276] HOH276 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB034 }   /* [277] HOH277 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB035 }   /* [278] HOH278 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB036 }   /* [279] HOH279 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB037 }   /* [280] HOH280 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB038 }   /* [281] HOH281 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB039 }   /* [282] HOH282 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB040 }   /* [283] HOH283 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB041 }   /* [284] HOH284 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB042 }   /* [285] HOH285 */
    ,{ (uint8)CAN_CONTROLLER_5,  (uint8)CAN_MB043 }   /* [286] HOH286 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB000 }   /* [287] HOH287 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB001 }   /* [288] HOH288 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB002 }   /* [289] HOH289 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB003 }   /* [290] HOH290 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB004 }   /* [291] HOH291 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB005 }   /* [292] HOH292 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB006 }   /* [293] HOH293 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB007 }   /* [294] HOH294 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB008 }   /* [295] HOH295 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB009 }   /* [296] HOH296 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB010 }   /* [297] HOH297 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB011 }   /* [298] HOH298 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB012 }   /* [299] HOH299 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB013 }   /* [300] HOH300 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB014 }   /* [301] HOH301 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB015 }   /* [302] HOH302 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB016 }   /* [303] HOH303 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB017 }   /* [304] HOH304 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB018 }   /* [305] HOH305 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB019 }   /* [306] HOH306 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB020 }   /* [307] HOH307 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB021 }   /* [308] HOH308 */
    ,{ (uint8)CAN_CONTROLLER_7,  (uint8)CAN_MB022 }   /* [309] HOH309 */
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
