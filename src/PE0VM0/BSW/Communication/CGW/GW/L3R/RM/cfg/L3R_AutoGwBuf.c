/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_AutoGwBuf.c
 * @brief		ルータテーブル定義
 * @details		Router専用
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成
 * @note		制御フレームルーティングマップ：
 * @note            Ctrl_RTM.xlsx
 * @note		ダイアグ/リプログフレームルーティングマップ：
 * @note            Diag_RTM.xlsx
 * @note		チャンネル定義ファイル：
 * @note            channelDef.yml
 * @note		チャンネル定義ファイル(L3R)：
 * @note            channelDef_L3R.yml
 * @note		例外フレーム定義ファイル：
 * @note            exceptionalMessages.yml
 * @note		テンプレートファイル：
 * @note            templates/L3R_AutoGwBufC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "L3R_Common.h"
#include "L3R_GwBuffer_cfg.h"
#include "L3R_Timer.h"

#include "L3R_GwBuffer.h"
#include "L3R_GwIdRouter.h"

#include "L3R_AutoGwBuf.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/

/* 最大データ長 */
#define L3R_DATAMAX000 (0x0008U)
#define L3R_DATAMAX001 (0x0040U)	/* CAN ID:013 */
#define L3R_DATAMAX002 (0x0040U)	/* CAN ID:01B */
#define L3R_DATAMAX003 (0x0040U)	/* CAN ID:049 */
#define L3R_DATAMAX004 (0x0040U)	/* CAN ID:062 */
#define L3R_DATAMAX005 (0x0040U)	/* CAN ID:069 */
#define L3R_DATAMAX006 (0x0040U)	/* CAN ID:06A */
#define L3R_DATAMAX007 (0x0040U)	/* CAN ID:072 */
#define L3R_DATAMAX008 (0x0040U)	/* CAN ID:075 */
#define L3R_DATAMAX009 (0x0040U)	/* CAN ID:07E */
#define L3R_DATAMAX010 (0x0040U)	/* CAN ID:086 */
#define L3R_DATAMAX011 (0x0040U)	/* CAN ID:09E */
#define L3R_DATAMAX012 (0x0040U)	/* CAN ID:0A0 */
#define L3R_DATAMAX013 (0x0040U)	/* CAN ID:0A1 */
#define L3R_DATAMAX014 (0x0040U)	/* CAN ID:0A3 */
#define L3R_DATAMAX015 (0x0040U)	/* CAN ID:0A4 */
#define L3R_DATAMAX016 (0x0040U)	/* CAN ID:0A5 */
#define L3R_DATAMAX017 (0x0040U)	/* CAN ID:0A6 */
#define L3R_DATAMAX018 (0x0040U)	/* CAN ID:0A8 */
#define L3R_DATAMAX019 (0x0040U)	/* CAN ID:0A9 */
#define L3R_DATAMAX020 (0x0040U)	/* CAN ID:0B7 */
#define L3R_DATAMAX021 (0x0040U)	/* CAN ID:0B8 */
#define L3R_DATAMAX022 (0x0040U)	/* CAN ID:0F3 */
#define L3R_DATAMAX023 (0x0040U)	/* CAN ID:0FC */
#define L3R_DATAMAX024 (0x0040U)	/* CAN ID:100 */
#define L3R_DATAMAX025 (0x0040U)	/* CAN ID:10B */
#define L3R_DATAMAX026 (0x0040U)	/* CAN ID:115 */
#define L3R_DATAMAX027 (0x0040U)	/* CAN ID:121 */
#define L3R_DATAMAX028 (0x0040U)	/* CAN ID:122 */
#define L3R_DATAMAX029 (0x0040U)	/* CAN ID:124 */
#define L3R_DATAMAX030 (0x0040U)	/* CAN ID:126 */
#define L3R_DATAMAX031 (0x0040U)	/* CAN ID:128 */
#define L3R_DATAMAX032 (0x0040U)	/* CAN ID:12B */
#define L3R_DATAMAX033 (0x0040U)	/* CAN ID:140 */
#define L3R_DATAMAX034 (0x0040U)	/* CAN ID:141 */
#define L3R_DATAMAX035 (0x0040U)	/* CAN ID:143 */
#define L3R_DATAMAX036 (0x0040U)	/* CAN ID:144 */
#define L3R_DATAMAX037 (0x0040U)	/* CAN ID:148 */
#define L3R_DATAMAX038 (0x0040U)	/* CAN ID:14B */
#define L3R_DATAMAX039 (0x0040U)	/* CAN ID:14C */
#define L3R_DATAMAX040 (0x0040U)	/* CAN ID:14D */
#define L3R_DATAMAX041 (0x0040U)	/* CAN ID:14F */
#define L3R_DATAMAX042 (0x0040U)	/* CAN ID:150 */
#define L3R_DATAMAX043 (0x0040U)	/* CAN ID:155 */
#define L3R_DATAMAX044 (0x0040U)	/* CAN ID:159 */
#define L3R_DATAMAX045 (0x0040U)	/* CAN ID:15A */
#define L3R_DATAMAX046 (0x0040U)	/* CAN ID:161 */
#define L3R_DATAMAX047 (0x0040U)	/* CAN ID:162 */
#define L3R_DATAMAX048 (0x0040U)	/* CAN ID:163 */
#define L3R_DATAMAX049 (0x0040U)	/* CAN ID:166 */
#define L3R_DATAMAX050 (0x0040U)	/* CAN ID:167 */
#define L3R_DATAMAX051 (0x0040U)	/* CAN ID:168 */
#define L3R_DATAMAX052 (0x0040U)	/* CAN ID:169 */
#define L3R_DATAMAX053 (0x0040U)	/* CAN ID:16A */
#define L3R_DATAMAX054 (0x0040U)	/* CAN ID:16B */
#define L3R_DATAMAX055 (0x0040U)	/* CAN ID:16C */
#define L3R_DATAMAX056 (0x0040U)	/* CAN ID:16D */
#define L3R_DATAMAX057 (0x0040U)	/* CAN ID:16E */
#define L3R_DATAMAX058 (0x0040U)	/* CAN ID:17E */
#define L3R_DATAMAX059 (0x0040U)	/* CAN ID:17F */
#define L3R_DATAMAX060 (0x0040U)	/* CAN ID:180 */
#define L3R_DATAMAX061 (0x0040U)	/* CAN ID:185 */
#define L3R_DATAMAX062 (0x0040U)	/* CAN ID:186 */
#define L3R_DATAMAX063 (0x0040U)	/* CAN ID:18D */
#define L3R_DATAMAX064 (0x0040U)	/* CAN ID:19A */
#define L3R_DATAMAX065 (0x0040U)	/* CAN ID:1A1 */
#define L3R_DATAMAX066 (0x0040U)	/* CAN ID:1A2 */
#define L3R_DATAMAX067 (0x0040U)	/* CAN ID:1A3 */
#define L3R_DATAMAX068 (0x0040U)	/* CAN ID:1A4 */
#define L3R_DATAMAX069 (0x0040U)	/* CAN ID:1A5 */
#define L3R_DATAMAX070 (0x0040U)	/* CAN ID:1A7 */
#define L3R_DATAMAX071 (0x0040U)	/* CAN ID:1A8 */
#define L3R_DATAMAX072 (0x0040U)	/* CAN ID:1A9 */
#define L3R_DATAMAX073 (0x0040U)	/* CAN ID:1AB */
#define L3R_DATAMAX074 (0x0040U)	/* CAN ID:1AC */
#define L3R_DATAMAX075 (0x0040U)	/* CAN ID:1AD */
#define L3R_DATAMAX076 (0x0040U)	/* CAN ID:1AE */
#define L3R_DATAMAX077 (0x0040U)	/* CAN ID:1AF */
#define L3R_DATAMAX078 (0x0040U)	/* CAN ID:1B0 */
#define L3R_DATAMAX079 (0x0040U)	/* CAN ID:1B2 */
#define L3R_DATAMAX080 (0x0040U)	/* CAN ID:1B3 */
#define L3R_DATAMAX081 (0x0040U)	/* CAN ID:1B4 */
#define L3R_DATAMAX082 (0x0040U)	/* CAN ID:1B5 */
#define L3R_DATAMAX083 (0x0040U)	/* CAN ID:1B7 */
#define L3R_DATAMAX084 (0x0040U)	/* CAN ID:1B8 */
#define L3R_DATAMAX085 (0x0040U)	/* CAN ID:1B9 */
#define L3R_DATAMAX086 (0x0040U)	/* CAN ID:1BA */
#define L3R_DATAMAX087 (0x0040U)	/* CAN ID:1BB */
#define L3R_DATAMAX088 (0x0040U)	/* CAN ID:1BC */
#define L3R_DATAMAX089 (0x0040U)	/* CAN ID:1BD */
#define L3R_DATAMAX090 (0x0040U)	/* CAN ID:1BE */
#define L3R_DATAMAX091 (0x0040U)	/* CAN ID:1C0 */
#define L3R_DATAMAX092 (0x0040U)	/* CAN ID:1C5 */
#define L3R_DATAMAX093 (0x0040U)	/* CAN ID:1C7 */
#define L3R_DATAMAX094 (0x0040U)	/* CAN ID:1CA */
#define L3R_DATAMAX095 (0x0040U)	/* CAN ID:1CC */
#define L3R_DATAMAX096 (0x0040U)	/* CAN ID:1CF */
#define L3R_DATAMAX097 (0x0040U)	/* CAN ID:1D0 */
#define L3R_DATAMAX098 (0x0040U)	/* CAN ID:1D1 */
#define L3R_DATAMAX099 (0x0040U)	/* CAN ID:1D2 */
#define L3R_DATAMAX100 (0x0040U)	/* CAN ID:1D3 */
#define L3R_DATAMAX101 (0x0040U)	/* CAN ID:1D6 */
#define L3R_DATAMAX102 (0x0040U)	/* CAN ID:1D7 */
#define L3R_DATAMAX103 (0x0040U)	/* CAN ID:1D8 */
#define L3R_DATAMAX104 (0x0040U)	/* CAN ID:1D9 */
#define L3R_DATAMAX105 (0x0040U)	/* CAN ID:1DB */
#define L3R_DATAMAX106 (0x0040U)	/* CAN ID:1DC */
#define L3R_DATAMAX107 (0x0040U)	/* CAN ID:1DD */
#define L3R_DATAMAX108 (0x0040U)	/* CAN ID:1DE */
#define L3R_DATAMAX109 (0x0040U)	/* CAN ID:1DF */
#define L3R_DATAMAX110 (0x0040U)	/* CAN ID:1E1 */
#define L3R_DATAMAX111 (0x0040U)	/* CAN ID:1E3 */
#define L3R_DATAMAX112 (0x0040U)	/* CAN ID:1EA */
#define L3R_DATAMAX113 (0x0040U)	/* CAN ID:1EB */
#define L3R_DATAMAX114 (0x0040U)	/* CAN ID:1EC */
#define L3R_DATAMAX115 (0x0040U)	/* CAN ID:1EF */
#define L3R_DATAMAX116 (0x0040U)	/* CAN ID:1F0 */
#define L3R_DATAMAX117 (0x0040U)	/* CAN ID:1F1 */
#define L3R_DATAMAX118 (0x0040U)	/* CAN ID:1F2 */
#define L3R_DATAMAX119 (0x0040U)	/* CAN ID:1F4 */
#define L3R_DATAMAX120 (0x0040U)	/* CAN ID:1F5 */
#define L3R_DATAMAX121 (0x0040U)	/* CAN ID:1F6 */
#define L3R_DATAMAX122 (0x0040U)	/* CAN ID:1F7 */
#define L3R_DATAMAX123 (0x0040U)	/* CAN ID:1FA */
#define L3R_DATAMAX124 (0x0040U)	/* CAN ID:1FC */
#define L3R_DATAMAX125 (0x0040U)	/* CAN ID:1FD */
#define L3R_DATAMAX126 (0x0040U)	/* CAN ID:1FE */
#define L3R_DATAMAX127 (0x0040U)	/* CAN ID:1FF */
#define L3R_DATAMAX128 (0x0040U)	/* CAN ID:202 */
#define L3R_DATAMAX129 (0x0040U)	/* CAN ID:203 */
#define L3R_DATAMAX130 (0x0040U)	/* CAN ID:204 */
#define L3R_DATAMAX131 (0x0040U)	/* CAN ID:207 */
#define L3R_DATAMAX132 (0x0040U)	/* CAN ID:208 */
#define L3R_DATAMAX133 (0x0040U)	/* CAN ID:209 */
#define L3R_DATAMAX134 (0x0040U)	/* CAN ID:20A */
#define L3R_DATAMAX135 (0x0040U)	/* CAN ID:20B */
#define L3R_DATAMAX136 (0x0040U)	/* CAN ID:20E */
#define L3R_DATAMAX137 (0x0040U)	/* CAN ID:20F */
#define L3R_DATAMAX138 (0x0040U)	/* CAN ID:214 */
#define L3R_DATAMAX139 (0x0040U)	/* CAN ID:219 */
#define L3R_DATAMAX140 (0x0040U)	/* CAN ID:22E */
#define L3R_DATAMAX141 (0x0040U)	/* CAN ID:230 */
#define L3R_DATAMAX142 (0x0040U)	/* CAN ID:235 */
#define L3R_DATAMAX143 (0x0040U)	/* CAN ID:247 */
#define L3R_DATAMAX144 (0x0040U)	/* CAN ID:24D */
#define L3R_DATAMAX145 (0x0040U)	/* CAN ID:251 */
#define L3R_DATAMAX146 (0x0040U)	/* CAN ID:252 */
#define L3R_DATAMAX147 (0x0040U)	/* CAN ID:255 */
#define L3R_DATAMAX148 (0x0040U)	/* CAN ID:259 */
#define L3R_DATAMAX149 (0x0040U)	/* CAN ID:25A */
#define L3R_DATAMAX150 (0x0040U)	/* CAN ID:261 */
#define L3R_DATAMAX151 (0x0040U)	/* CAN ID:262 */
#define L3R_DATAMAX152 (0x0040U)	/* CAN ID:26E */
#define L3R_DATAMAX153 (0x0040U)	/* CAN ID:272 */
#define L3R_DATAMAX154 (0x0040U)	/* CAN ID:274 */
#define L3R_DATAMAX155 (0x0040U)	/* CAN ID:275 */
#define L3R_DATAMAX156 (0x0040U)	/* CAN ID:276 */
#define L3R_DATAMAX157 (0x0040U)	/* CAN ID:279 */
#define L3R_DATAMAX158 (0x0040U)	/* CAN ID:27B */
#define L3R_DATAMAX159 (0x0040U)	/* CAN ID:27C */
#define L3R_DATAMAX160 (0x0040U)	/* CAN ID:27D */
#define L3R_DATAMAX161 (0x0040U)	/* CAN ID:27E */
#define L3R_DATAMAX162 (0x0040U)	/* CAN ID:281 */
#define L3R_DATAMAX163 (0x0040U)	/* CAN ID:282 */
#define L3R_DATAMAX164 (0x0040U)	/* CAN ID:285 */
#define L3R_DATAMAX165 (0x0040U)	/* CAN ID:28A */
#define L3R_DATAMAX166 (0x0040U)	/* CAN ID:295 */
#define L3R_DATAMAX167 (0x0040U)	/* CAN ID:296 */
#define L3R_DATAMAX168 (0x0040U)	/* CAN ID:2A0 */
#define L3R_DATAMAX169 (0x0040U)	/* CAN ID:2A1 */
#define L3R_DATAMAX170 (0x0040U)	/* CAN ID:2A6 */
#define L3R_DATAMAX171 (0x0040U)	/* CAN ID:2A7 */
#define L3R_DATAMAX172 (0x0040U)	/* CAN ID:2A8 */
#define L3R_DATAMAX173 (0x0040U)	/* CAN ID:2AA */
#define L3R_DATAMAX174 (0x0040U)	/* CAN ID:2AF */
#define L3R_DATAMAX175 (0x0040U)	/* CAN ID:2B2 */
#define L3R_DATAMAX176 (0x0040U)	/* CAN ID:2B3 */
#define L3R_DATAMAX177 (0x0040U)	/* CAN ID:2D2 */
#define L3R_DATAMAX178 (0x0040U)	/* CAN ID:2D3 */
#define L3R_DATAMAX179 (0x0040U)	/* CAN ID:2D4 */
#define L3R_DATAMAX180 (0x0040U)	/* CAN ID:2D5 */
#define L3R_DATAMAX181 (0x0040U)	/* CAN ID:2D6 */
#define L3R_DATAMAX182 (0x0040U)	/* CAN ID:2D7 */
#define L3R_DATAMAX183 (0x0040U)	/* CAN ID:2DA */
#define L3R_DATAMAX184 (0x0040U)	/* CAN ID:2DE */
#define L3R_DATAMAX185 (0x0040U)	/* CAN ID:2DF */
#define L3R_DATAMAX186 (0x0040U)	/* CAN ID:2E0 */
#define L3R_DATAMAX187 (0x0040U)	/* CAN ID:2E1 */
#define L3R_DATAMAX188 (0x0040U)	/* CAN ID:2E2 */
#define L3R_DATAMAX189 (0x0040U)	/* CAN ID:2E3 */
#define L3R_DATAMAX190 (0x0040U)	/* CAN ID:2E5 */
#define L3R_DATAMAX191 (0x0040U)	/* CAN ID:2E7 */
#define L3R_DATAMAX192 (0x0040U)	/* CAN ID:2E8 */
#define L3R_DATAMAX193 (0x0040U)	/* CAN ID:2EB */
#define L3R_DATAMAX194 (0x0040U)	/* CAN ID:2EE */
#define L3R_DATAMAX195 (0x0040U)	/* CAN ID:2EF */
#define L3R_DATAMAX196 (0x0040U)	/* CAN ID:2F0 */
#define L3R_DATAMAX197 (0x0040U)	/* CAN ID:2F2 */
#define L3R_DATAMAX198 (0x0040U)	/* CAN ID:2F3 */
#define L3R_DATAMAX199 (0x0040U)	/* CAN ID:2F4 */
#define L3R_DATAMAX200 (0x0040U)	/* CAN ID:2F5 */
#define L3R_DATAMAX201 (0x0040U)	/* CAN ID:2F6 */
#define L3R_DATAMAX202 (0x0040U)	/* CAN ID:2F7 */
#define L3R_DATAMAX203 (0x0040U)	/* CAN ID:2F8 */
#define L3R_DATAMAX204 (0x0040U)	/* CAN ID:2F9 */
#define L3R_DATAMAX205 (0x0040U)	/* CAN ID:2FA */
#define L3R_DATAMAX206 (0x0040U)	/* CAN ID:2FB */
#define L3R_DATAMAX207 (0x0040U)	/* CAN ID:2FD */
#define L3R_DATAMAX208 (0x0040U)	/* CAN ID:2FE */
#define L3R_DATAMAX209 (0x0040U)	/* CAN ID:305 */
#define L3R_DATAMAX210 (0x0040U)	/* CAN ID:306 */
#define L3R_DATAMAX211 (0x0040U)	/* CAN ID:30D */
#define L3R_DATAMAX212 (0x0040U)	/* CAN ID:30E */
#define L3R_DATAMAX213 (0x0040U)	/* CAN ID:30F */
#define L3R_DATAMAX214 (0x0040U)	/* CAN ID:312 */
#define L3R_DATAMAX215 (0x0040U)	/* CAN ID:313 */
#define L3R_DATAMAX216 (0x0040U)	/* CAN ID:314 */
#define L3R_DATAMAX217 (0x0040U)	/* CAN ID:315 */
#define L3R_DATAMAX218 (0x0040U)	/* CAN ID:317 */
#define L3R_DATAMAX219 (0x0040U)	/* CAN ID:318 */
#define L3R_DATAMAX220 (0x0040U)	/* CAN ID:31A */
#define L3R_DATAMAX221 (0x0040U)	/* CAN ID:31D */
#define L3R_DATAMAX222 (0x0040U)	/* CAN ID:320 */
#define L3R_DATAMAX223 (0x0040U)	/* CAN ID:322 */
#define L3R_DATAMAX224 (0x0040U)	/* CAN ID:325 */
#define L3R_DATAMAX225 (0x0040U)	/* CAN ID:328 */
#define L3R_DATAMAX226 (0x0040U)	/* CAN ID:32A */
#define L3R_DATAMAX227 (0x0040U)	/* CAN ID:32F */
#define L3R_DATAMAX228 (0x0040U)	/* CAN ID:333 */
#define L3R_DATAMAX229 (0x0040U)	/* CAN ID:334 */
#define L3R_DATAMAX230 (0x0040U)	/* CAN ID:335 */
#define L3R_DATAMAX231 (0x0040U)	/* CAN ID:336 */
#define L3R_DATAMAX232 (0x0040U)	/* CAN ID:337 */
#define L3R_DATAMAX233 (0x0040U)	/* CAN ID:33A */
#define L3R_DATAMAX234 (0x0040U)	/* CAN ID:33F */
#define L3R_DATAMAX235 (0x0040U)	/* CAN ID:341 */
#define L3R_DATAMAX236 (0x0040U)	/* CAN ID:345 */
#define L3R_DATAMAX237 (0x0040U)	/* CAN ID:346 */
#define L3R_DATAMAX238 (0x0040U)	/* CAN ID:347 */
#define L3R_DATAMAX239 (0x0040U)	/* CAN ID:348 */
#define L3R_DATAMAX240 (0x0040U)	/* CAN ID:349 */
#define L3R_DATAMAX241 (0x0040U)	/* CAN ID:34C */
#define L3R_DATAMAX242 (0x0040U)	/* CAN ID:34D */
#define L3R_DATAMAX243 (0x0040U)	/* CAN ID:34E */
#define L3R_DATAMAX244 (0x0040U)	/* CAN ID:34F */
#define L3R_DATAMAX245 (0x0040U)	/* CAN ID:350 */
#define L3R_DATAMAX246 (0x0040U)	/* CAN ID:351 */
#define L3R_DATAMAX247 (0x0040U)	/* CAN ID:352 */
#define L3R_DATAMAX248 (0x0040U)	/* CAN ID:353 */
#define L3R_DATAMAX249 (0x0040U)	/* CAN ID:354 */
#define L3R_DATAMAX250 (0x0040U)	/* CAN ID:355 */
#define L3R_DATAMAX251 (0x0040U)	/* CAN ID:357 */
#define L3R_DATAMAX252 (0x0040U)	/* CAN ID:358 */
#define L3R_DATAMAX253 (0x0040U)	/* CAN ID:35A */
#define L3R_DATAMAX254 (0x0040U)	/* CAN ID:35B */
#define L3R_DATAMAX255 (0x0040U)	/* CAN ID:35D */
#define L3R_DATAMAX256 (0x0040U)	/* CAN ID:35F */
#define L3R_DATAMAX257 (0x0040U)	/* CAN ID:363 */
#define L3R_DATAMAX258 (0x0040U)	/* CAN ID:364 */
#define L3R_DATAMAX259 (0x0040U)	/* CAN ID:367 */
#define L3R_DATAMAX260 (0x0040U)	/* CAN ID:368 */
#define L3R_DATAMAX261 (0x0040U)	/* CAN ID:36A */
#define L3R_DATAMAX262 (0x0040U)	/* CAN ID:36B */
#define L3R_DATAMAX263 (0x0040U)	/* CAN ID:36E */
#define L3R_DATAMAX264 (0x0040U)	/* CAN ID:36F */
#define L3R_DATAMAX265 (0x0040U)	/* CAN ID:375 */
#define L3R_DATAMAX266 (0x0040U)	/* CAN ID:379 */
#define L3R_DATAMAX267 (0x0040U)	/* CAN ID:37B */
#define L3R_DATAMAX268 (0x0040U)	/* CAN ID:37E */
#define L3R_DATAMAX269 (0x0040U)	/* CAN ID:37F */
#define L3R_DATAMAX270 (0x0040U)	/* CAN ID:380 */
#define L3R_DATAMAX271 (0x0040U)	/* CAN ID:381 */
#define L3R_DATAMAX272 (0x0040U)	/* CAN ID:382 */
#define L3R_DATAMAX273 (0x0040U)	/* CAN ID:384 */
#define L3R_DATAMAX274 (0x0040U)	/* CAN ID:385 */
#define L3R_DATAMAX275 (0x0040U)	/* CAN ID:386 */
#define L3R_DATAMAX276 (0x0040U)	/* CAN ID:387 */
#define L3R_DATAMAX277 (0x0040U)	/* CAN ID:388 */
#define L3R_DATAMAX278 (0x0040U)	/* CAN ID:389 */
#define L3R_DATAMAX279 (0x0040U)	/* CAN ID:38A */
#define L3R_DATAMAX280 (0x0040U)	/* CAN ID:38B */
#define L3R_DATAMAX281 (0x0040U)	/* CAN ID:38D */
#define L3R_DATAMAX282 (0x0040U)	/* CAN ID:38E */
#define L3R_DATAMAX283 (0x0040U)	/* CAN ID:38F */
#define L3R_DATAMAX284 (0x0040U)	/* CAN ID:390 */
#define L3R_DATAMAX285 (0x0040U)	/* CAN ID:393 */
#define L3R_DATAMAX286 (0x0040U)	/* CAN ID:395 */
#define L3R_DATAMAX287 (0x0040U)	/* CAN ID:396 */
#define L3R_DATAMAX288 (0x0040U)	/* CAN ID:397 */
#define L3R_DATAMAX289 (0x0040U)	/* CAN ID:398 */
#define L3R_DATAMAX290 (0x0040U)	/* CAN ID:39A */
#define L3R_DATAMAX291 (0x0040U)	/* CAN ID:39B */
#define L3R_DATAMAX292 (0x0040U)	/* CAN ID:39C */
#define L3R_DATAMAX293 (0x0040U)	/* CAN ID:39D */
#define L3R_DATAMAX294 (0x0040U)	/* CAN ID:39E */
#define L3R_DATAMAX295 (0x0040U)	/* CAN ID:39F */
#define L3R_DATAMAX296 (0x0040U)	/* CAN ID:3A1 */
#define L3R_DATAMAX297 (0x0040U)	/* CAN ID:3A5 */
#define L3R_DATAMAX298 (0x0040U)	/* CAN ID:3A6 */
#define L3R_DATAMAX299 (0x0040U)	/* CAN ID:3A7 */
#define L3R_DATAMAX300 (0x0040U)	/* CAN ID:3A8 */
#define L3R_DATAMAX301 (0x0040U)	/* CAN ID:3A9 */
#define L3R_DATAMAX302 (0x0040U)	/* CAN ID:3AB */
#define L3R_DATAMAX303 (0x0040U)	/* CAN ID:3AC */
#define L3R_DATAMAX304 (0x0040U)	/* CAN ID:3AE */
#define L3R_DATAMAX305 (0x0040U)	/* CAN ID:3AF */
#define L3R_DATAMAX306 (0x0040U)	/* CAN ID:3B0 */
#define L3R_DATAMAX307 (0x0040U)	/* CAN ID:3B1 */
#define L3R_DATAMAX308 (0x0040U)	/* CAN ID:3B2 */
#define L3R_DATAMAX309 (0x0040U)	/* CAN ID:3B3 */
#define L3R_DATAMAX310 (0x0040U)	/* CAN ID:3B5 */
#define L3R_DATAMAX311 (0x0040U)	/* CAN ID:3B6 */
#define L3R_DATAMAX312 (0x0040U)	/* CAN ID:3B8 */
#define L3R_DATAMAX313 (0x0040U)	/* CAN ID:3B9 */
#define L3R_DATAMAX314 (0x0040U)	/* CAN ID:3BB */
#define L3R_DATAMAX315 (0x0040U)	/* CAN ID:3BC */
#define L3R_DATAMAX316 (0x0040U)	/* CAN ID:3BD */
#define L3R_DATAMAX317 (0x0040U)	/* CAN ID:3BE */
#define L3R_DATAMAX318 (0x0040U)	/* CAN ID:3BF */
#define L3R_DATAMAX319 (0x0040U)	/* CAN ID:3C0 */
#define L3R_DATAMAX320 (0x0040U)	/* CAN ID:3C2 */
#define L3R_DATAMAX321 (0x0040U)	/* CAN ID:3C4 */
#define L3R_DATAMAX322 (0x0040U)	/* CAN ID:3C6 */
#define L3R_DATAMAX323 (0x0040U)	/* CAN ID:3C7 */
#define L3R_DATAMAX324 (0x0040U)	/* CAN ID:3C8 */
#define L3R_DATAMAX325 (0x0040U)	/* CAN ID:3C9 */
#define L3R_DATAMAX326 (0x0040U)	/* CAN ID:3CA */
#define L3R_DATAMAX327 (0x0040U)	/* CAN ID:3CB */
#define L3R_DATAMAX328 (0x0040U)	/* CAN ID:3CD */
#define L3R_DATAMAX329 (0x0040U)	/* CAN ID:3D0 */
#define L3R_DATAMAX330 (0x0040U)	/* CAN ID:3D2 */
#define L3R_DATAMAX331 (0x0040U)	/* CAN ID:3D3 */
#define L3R_DATAMAX332 (0x0040U)	/* CAN ID:3D4 */
#define L3R_DATAMAX333 (0x0040U)	/* CAN ID:3D6 */
#define L3R_DATAMAX334 (0x0040U)	/* CAN ID:3D9 */
#define L3R_DATAMAX335 (0x0040U)	/* CAN ID:3DB */
#define L3R_DATAMAX336 (0x0040U)	/* CAN ID:3DC */
#define L3R_DATAMAX337 (0x0040U)	/* CAN ID:3DD */
#define L3R_DATAMAX338 (0x0040U)	/* CAN ID:3DE */
#define L3R_DATAMAX339 (0x0040U)	/* CAN ID:3E1 */
#define L3R_DATAMAX340 (0x0040U)	/* CAN ID:3E4 */
#define L3R_DATAMAX341 (0x0040U)	/* CAN ID:3E5 */
#define L3R_DATAMAX342 (0x0040U)	/* CAN ID:3E6 */
#define L3R_DATAMAX343 (0x0040U)	/* CAN ID:3E7 */
#define L3R_DATAMAX344 (0x0040U)	/* CAN ID:3EA */
#define L3R_DATAMAX345 (0x0040U)	/* CAN ID:3EB */
#define L3R_DATAMAX346 (0x0040U)	/* CAN ID:3EC */
#define L3R_DATAMAX347 (0x0040U)	/* CAN ID:3EE */
#define L3R_DATAMAX348 (0x0040U)	/* CAN ID:3EF */
#define L3R_DATAMAX349 (0x0040U)	/* CAN ID:3F0 */
#define L3R_DATAMAX350 (0x0040U)	/* CAN ID:3F1 */
#define L3R_DATAMAX351 (0x0040U)	/* CAN ID:3F2 */
#define L3R_DATAMAX352 (0x0040U)	/* CAN ID:3F3 */
#define L3R_DATAMAX353 (0x0040U)	/* CAN ID:3F5 */
#define L3R_DATAMAX354 (0x0040U)	/* CAN ID:3F6 */
#define L3R_DATAMAX355 (0x0040U)	/* CAN ID:3F7 */
#define L3R_DATAMAX356 (0x0040U)	/* CAN ID:3F9 */
#define L3R_DATAMAX357 (0x0040U)	/* CAN ID:3FB */
#define L3R_DATAMAX358 (0x0040U)	/* CAN ID:3FC */
#define L3R_DATAMAX359 (0x0040U)	/* CAN ID:3FD */
#define L3R_DATAMAX360 (0x0040U)	/* CAN ID:400 */
#define L3R_DATAMAX361 (0x0040U)	/* CAN ID:401 */
#define L3R_DATAMAX362 (0x0040U)	/* CAN ID:403 */
#define L3R_DATAMAX363 (0x0040U)	/* CAN ID:404 */
#define L3R_DATAMAX364 (0x0040U)	/* CAN ID:405 */
#define L3R_DATAMAX365 (0x0040U)	/* CAN ID:407 */
#define L3R_DATAMAX366 (0x0040U)	/* CAN ID:408 */
#define L3R_DATAMAX367 (0x0040U)	/* CAN ID:40B */
#define L3R_DATAMAX368 (0x0040U)	/* CAN ID:40C */
#define L3R_DATAMAX369 (0x0040U)	/* CAN ID:40D */
#define L3R_DATAMAX370 (0x0040U)	/* CAN ID:40E */
#define L3R_DATAMAX371 (0x0040U)	/* CAN ID:411 */
#define L3R_DATAMAX372 (0x0040U)	/* CAN ID:412 */
#define L3R_DATAMAX373 (0x0040U)	/* CAN ID:417 */
#define L3R_DATAMAX374 (0x0040U)	/* CAN ID:418 */
#define L3R_DATAMAX375 (0x0040U)	/* CAN ID:41A */
#define L3R_DATAMAX376 (0x0040U)	/* CAN ID:421 */
#define L3R_DATAMAX377 (0x0040U)	/* CAN ID:422 */
#define L3R_DATAMAX378 (0x0040U)	/* CAN ID:423 */
#define L3R_DATAMAX379 (0x0040U)	/* CAN ID:426 */
#define L3R_DATAMAX380 (0x0040U)	/* CAN ID:427 */
#define L3R_DATAMAX381 (0x0040U)	/* CAN ID:428 */
#define L3R_DATAMAX382 (0x0040U)	/* CAN ID:429 */
#define L3R_DATAMAX383 (0x0040U)	/* CAN ID:42A */
#define L3R_DATAMAX384 (0x0040U)	/* CAN ID:42B */
#define L3R_DATAMAX385 (0x0040U)	/* CAN ID:42C */
#define L3R_DATAMAX386 (0x0040U)	/* CAN ID:42E */
#define L3R_DATAMAX387 (0x0040U)	/* CAN ID:42F */
#define L3R_DATAMAX388 (0x0040U)	/* CAN ID:430 */
#define L3R_DATAMAX389 (0x0040U)	/* CAN ID:432 */
#define L3R_DATAMAX390 (0x0040U)	/* CAN ID:434 */
#define L3R_DATAMAX391 (0x0040U)	/* CAN ID:435 */
#define L3R_DATAMAX392 (0x0040U)	/* CAN ID:436 */
#define L3R_DATAMAX393 (0x0040U)	/* CAN ID:437 */
#define L3R_DATAMAX394 (0x0040U)	/* CAN ID:438 */
#define L3R_DATAMAX395 (0x0040U)	/* CAN ID:439 */
#define L3R_DATAMAX396 (0x0040U)	/* CAN ID:43A */
#define L3R_DATAMAX397 (0x0040U)	/* CAN ID:43B */
#define L3R_DATAMAX398 (0x0040U)	/* CAN ID:43E */
#define L3R_DATAMAX399 (0x0040U)	/* CAN ID:442 */
#define L3R_DATAMAX400 (0x0040U)	/* CAN ID:480 */
#define L3R_DATAMAX401 (0x0040U)	/* CAN ID:484 */
#define L3R_DATAMAX402 (0x0040U)	/* CAN ID:489 */
#define L3R_DATAMAX403 (0x0040U)	/* CAN ID:48B */
#define L3R_DATAMAX404 (0x0040U)	/* CAN ID:490 */
#define L3R_DATAMAX405 (0x0040U)	/* CAN ID:491 */
#define L3R_DATAMAX406 (0x0040U)	/* CAN ID:494 */
#define L3R_DATAMAX407 (0x0040U)	/* CAN ID:495 */
#define L3R_DATAMAX408 (0x0040U)	/* CAN ID:496 */
#define L3R_DATAMAX409 (0x0040U)	/* CAN ID:497 */
#define L3R_DATAMAX410 (0x0040U)	/* CAN ID:499 */
#define L3R_DATAMAX411 (0x0040U)	/* CAN ID:49A */
#define L3R_DATAMAX412 (0x0040U)	/* CAN ID:49B */
#define L3R_DATAMAX413 (0x0040U)	/* CAN ID:49D */
#define L3R_DATAMAX414 (0x0040U)	/* CAN ID:4A0 */
#define L3R_DATAMAX415 (0x0040U)	/* CAN ID:4A1 */
#define L3R_DATAMAX416 (0x0040U)	/* CAN ID:4A3 */
#define L3R_DATAMAX417 (0x0040U)	/* CAN ID:4A4 */
#define L3R_DATAMAX418 (0x0040U)	/* CAN ID:4A8 */
#define L3R_DATAMAX419 (0x0040U)	/* CAN ID:4AC */
#define L3R_DATAMAX420 (0x0040U)	/* CAN ID:4AE */
#define L3R_DATAMAX421 (0x0040U)	/* CAN ID:4AF */
#define L3R_DATAMAX422 (0x0040U)	/* CAN ID:4B8 */
#define L3R_DATAMAX423 (0x0040U)	/* CAN ID:4BC */
#define L3R_DATAMAX424 (0x0040U)	/* CAN ID:500 */
#define L3R_DATAMAX425 (0x0040U)	/* CAN ID:506 */
#define L3R_DATAMAX426 (0x0040U)	/* CAN ID:507 */
#define L3R_DATAMAX427 (0x0040U)	/* CAN ID:515 */
#define L3R_DATAMAX428 (0x0040U)	/* CAN ID:51A */
#define L3R_DATAMAX429 (0x0040U)	/* CAN ID:51B */
#define L3R_DATAMAX430 (0x0040U)	/* CAN ID:51D */
#define L3R_DATAMAX431 (0x0040U)	/* CAN ID:51E */
#define L3R_DATAMAX432 (0x0040U)	/* CAN ID:51F */
#define L3R_DATAMAX433 (0x0040U)	/* CAN ID:521 */
#define L3R_DATAMAX434 (0x0040U)	/* CAN ID:524 */
#define L3R_DATAMAX435 (0x0040U)	/* CAN ID:526 */
#define L3R_DATAMAX436 (0x0040U)	/* CAN ID:527 */
#define L3R_DATAMAX437 (0x0040U)	/* CAN ID:528 */
#define L3R_DATAMAX438 (0x0040U)	/* CAN ID:529 */
#define L3R_DATAMAX439 (0x0040U)	/* CAN ID:52A */
#define L3R_DATAMAX440 (0x0040U)	/* CAN ID:52B */
#define L3R_DATAMAX441 (0x0040U)	/* CAN ID:52C */
#define L3R_DATAMAX442 (0x0040U)	/* CAN ID:530 */
#define L3R_DATAMAX443 (0x0040U)	/* CAN ID:531 */
#define L3R_DATAMAX444 (0x0040U)	/* CAN ID:532 */
#define L3R_DATAMAX445 (0x0040U)	/* CAN ID:534 */
#define L3R_DATAMAX446 (0x0040U)	/* CAN ID:535 */
#define L3R_DATAMAX447 (0x0040U)	/* CAN ID:537 */
#define L3R_DATAMAX448 (0x0040U)	/* CAN ID:538 */
#define L3R_DATAMAX449 (0x0040U)	/* CAN ID:56D */
#define L3R_DATAMAX450 (0x0040U)	/* CAN ID:583 */
#define L3R_DATAMAX451 (0x0040U)	/* CAN ID:589 */
#define L3R_DATAMAX452 (0x0040U)	/* CAN ID:58A */
#define L3R_DATAMAX453 (0x0040U)	/* CAN ID:58D */
#define L3R_DATAMAX454 (0x0040U)	/* CAN ID:592 */
#define L3R_DATAMAX455 (0x0040U)	/* CAN ID:594 */
#define L3R_DATAMAX456 (0x0040U)	/* CAN ID:596 */
#define L3R_DATAMAX457 (0x0040U)	/* CAN ID:5F1 */
#define L3R_DATAMAX458 (0x0040U)	/* CAN ID:5F3 */
#define L3R_DATAMAX459 (0x0040U)	/* CAN ID:5F4 */
#define L3R_DATAMAX460 (0x0040U)	/* CAN ID:5F6 */
#define L3R_DATAMAX461 (0x0040U)	/* CAN ID:601 */
#define L3R_DATAMAX462 (0x0040U)	/* CAN ID:602 */
#define L3R_DATAMAX463 (0x0040U)	/* CAN ID:608 */
#define L3R_DATAMAX464 (0x0040U)	/* CAN ID:60C */
#define L3R_DATAMAX465 (0x0040U)	/* CAN ID:610 */
#define L3R_DATAMAX466 (0x0040U)	/* CAN ID:611 */
#define L3R_DATAMAX467 (0x0040U)	/* CAN ID:613 */
#define L3R_DATAMAX468 (0x0040U)	/* CAN ID:614 */
#define L3R_DATAMAX469 (0x0040U)	/* CAN ID:615 */
#define L3R_DATAMAX470 (0x0040U)	/* CAN ID:618 */
#define L3R_DATAMAX471 (0x0040U)	/* CAN ID:621 */
#define L3R_DATAMAX472 (0x0040U)	/* CAN ID:622 */
#define L3R_DATAMAX473 (0x0040U)	/* CAN ID:623 */
#define L3R_DATAMAX474 (0x0040U)	/* CAN ID:624 */
#define L3R_DATAMAX475 (0x0040U)	/* CAN ID:626 */
#define L3R_DATAMAX476 (0x0040U)	/* CAN ID:629 */
#define L3R_DATAMAX477 (0x0040U)	/* CAN ID:62A */
#define L3R_DATAMAX478 (0x0040U)	/* CAN ID:62C */
#define L3R_DATAMAX479 (0x0040U)	/* CAN ID:633 */

/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
/* GWバッファのGWヘッダ情報 */
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static CommonBufferFields GWHdr000;
static CommonBufferFields GWHdr001;
static CommonBufferFields GWHdr002;
static CommonBufferFields GWHdr003;
static CommonBufferFields GWHdr004;
static CommonBufferFields GWHdr005;
static CommonBufferFields GWHdr006;
static CommonBufferFields GWHdr007;
static CommonBufferFields GWHdr008;
static CommonBufferFields GWHdr009;
static CommonBufferFields GWHdr010;
static CommonBufferFields GWHdr011;
static CommonBufferFields GWHdr012;
static CommonBufferFields GWHdr013;
static CommonBufferFields GWHdr014;
static CommonBufferFields GWHdr015;
static CommonBufferFields GWHdr016;
static CommonBufferFields GWHdr017;
static CommonBufferFields GWHdr018;
static CommonBufferFields GWHdr019;
static CommonBufferFields GWHdr020;
static CommonBufferFields GWHdr021;
static CommonBufferFields GWHdr022;
static CommonBufferFields GWHdr023;
static CommonBufferFields GWHdr024;
static CommonBufferFields GWHdr025;
static CommonBufferFields GWHdr026;
static CommonBufferFields GWHdr027;
static CommonBufferFields GWHdr028;
static CommonBufferFields GWHdr029;
static CommonBufferFields GWHdr030;
static CommonBufferFields GWHdr031;
static CommonBufferFields GWHdr032;
static CommonBufferFields GWHdr033;
static CommonBufferFields GWHdr034;
static CommonBufferFields GWHdr035;
static CommonBufferFields GWHdr036;
static CommonBufferFields GWHdr037;
static CommonBufferFields GWHdr038;
static CommonBufferFields GWHdr039;
static CommonBufferFields GWHdr040;
static CommonBufferFields GWHdr041;
static CommonBufferFields GWHdr042;
static CommonBufferFields GWHdr043;
static CommonBufferFields GWHdr044;
static CommonBufferFields GWHdr045;
static CommonBufferFields GWHdr046;
static CommonBufferFields GWHdr047;
static CommonBufferFields GWHdr048;
static CommonBufferFields GWHdr049;
static CommonBufferFields GWHdr050;
static CommonBufferFields GWHdr051;
static CommonBufferFields GWHdr052;
static CommonBufferFields GWHdr053;
static CommonBufferFields GWHdr054;
static CommonBufferFields GWHdr055;
static CommonBufferFields GWHdr056;
static CommonBufferFields GWHdr057;
static CommonBufferFields GWHdr058;
static CommonBufferFields GWHdr059;
static CommonBufferFields GWHdr060;
static CommonBufferFields GWHdr061;
static CommonBufferFields GWHdr062;
static CommonBufferFields GWHdr063;
static CommonBufferFields GWHdr064;
static CommonBufferFields GWHdr065;
static CommonBufferFields GWHdr066;
static CommonBufferFields GWHdr067;
static CommonBufferFields GWHdr068;
static CommonBufferFields GWHdr069;
static CommonBufferFields GWHdr070;
static CommonBufferFields GWHdr071;
static CommonBufferFields GWHdr072;
static CommonBufferFields GWHdr073;
static CommonBufferFields GWHdr074;
static CommonBufferFields GWHdr075;
static CommonBufferFields GWHdr076;
static CommonBufferFields GWHdr077;
static CommonBufferFields GWHdr078;
static CommonBufferFields GWHdr079;
static CommonBufferFields GWHdr080;
static CommonBufferFields GWHdr081;
static CommonBufferFields GWHdr082;
static CommonBufferFields GWHdr083;
static CommonBufferFields GWHdr084;
static CommonBufferFields GWHdr085;
static CommonBufferFields GWHdr086;
static CommonBufferFields GWHdr087;
static CommonBufferFields GWHdr088;
static CommonBufferFields GWHdr089;
static CommonBufferFields GWHdr090;
static CommonBufferFields GWHdr091;
static CommonBufferFields GWHdr092;
static CommonBufferFields GWHdr093;
static CommonBufferFields GWHdr094;
static CommonBufferFields GWHdr095;
static CommonBufferFields GWHdr096;
static CommonBufferFields GWHdr097;
static CommonBufferFields GWHdr098;
static CommonBufferFields GWHdr099;
static CommonBufferFields GWHdr100;
static CommonBufferFields GWHdr101;
static CommonBufferFields GWHdr102;
static CommonBufferFields GWHdr103;
static CommonBufferFields GWHdr104;
static CommonBufferFields GWHdr105;
static CommonBufferFields GWHdr106;
static CommonBufferFields GWHdr107;
static CommonBufferFields GWHdr108;
static CommonBufferFields GWHdr109;
static CommonBufferFields GWHdr110;
static CommonBufferFields GWHdr111;
static CommonBufferFields GWHdr112;
static CommonBufferFields GWHdr113;
static CommonBufferFields GWHdr114;
static CommonBufferFields GWHdr115;
static CommonBufferFields GWHdr116;
static CommonBufferFields GWHdr117;
static CommonBufferFields GWHdr118;
static CommonBufferFields GWHdr119;
static CommonBufferFields GWHdr120;
static CommonBufferFields GWHdr121;
static CommonBufferFields GWHdr122;
static CommonBufferFields GWHdr123;
static CommonBufferFields GWHdr124;
static CommonBufferFields GWHdr125;
static CommonBufferFields GWHdr126;
static CommonBufferFields GWHdr127;
static CommonBufferFields GWHdr128;
static CommonBufferFields GWHdr129;
static CommonBufferFields GWHdr130;
static CommonBufferFields GWHdr131;
static CommonBufferFields GWHdr132;
static CommonBufferFields GWHdr133;
static CommonBufferFields GWHdr134;
static CommonBufferFields GWHdr135;
static CommonBufferFields GWHdr136;
static CommonBufferFields GWHdr137;
static CommonBufferFields GWHdr138;
static CommonBufferFields GWHdr139;
static CommonBufferFields GWHdr140;
static CommonBufferFields GWHdr141;
static CommonBufferFields GWHdr142;
static CommonBufferFields GWHdr143;
static CommonBufferFields GWHdr144;
static CommonBufferFields GWHdr145;
static CommonBufferFields GWHdr146;
static CommonBufferFields GWHdr147;
static CommonBufferFields GWHdr148;
static CommonBufferFields GWHdr149;
static CommonBufferFields GWHdr150;
static CommonBufferFields GWHdr151;
static CommonBufferFields GWHdr152;
static CommonBufferFields GWHdr153;
static CommonBufferFields GWHdr154;
static CommonBufferFields GWHdr155;
static CommonBufferFields GWHdr156;
static CommonBufferFields GWHdr157;
static CommonBufferFields GWHdr158;
static CommonBufferFields GWHdr159;
static CommonBufferFields GWHdr160;
static CommonBufferFields GWHdr161;
static CommonBufferFields GWHdr162;
static CommonBufferFields GWHdr163;
static CommonBufferFields GWHdr164;
static CommonBufferFields GWHdr165;
static CommonBufferFields GWHdr166;
static CommonBufferFields GWHdr167;
static CommonBufferFields GWHdr168;
static CommonBufferFields GWHdr169;
static CommonBufferFields GWHdr170;
static CommonBufferFields GWHdr171;
static CommonBufferFields GWHdr172;
static CommonBufferFields GWHdr173;
static CommonBufferFields GWHdr174;
static CommonBufferFields GWHdr175;
static CommonBufferFields GWHdr176;
static CommonBufferFields GWHdr177;
static CommonBufferFields GWHdr178;
static CommonBufferFields GWHdr179;
static CommonBufferFields GWHdr180;
static CommonBufferFields GWHdr181;
static CommonBufferFields GWHdr182;
static CommonBufferFields GWHdr183;
static CommonBufferFields GWHdr184;
static CommonBufferFields GWHdr185;
static CommonBufferFields GWHdr186;
static CommonBufferFields GWHdr187;
static CommonBufferFields GWHdr188;
static CommonBufferFields GWHdr189;
static CommonBufferFields GWHdr190;
static CommonBufferFields GWHdr191;
static CommonBufferFields GWHdr192;
static CommonBufferFields GWHdr193;
static CommonBufferFields GWHdr194;
static CommonBufferFields GWHdr195;
static CommonBufferFields GWHdr196;
static CommonBufferFields GWHdr197;
static CommonBufferFields GWHdr198;
static CommonBufferFields GWHdr199;
static CommonBufferFields GWHdr200;
static CommonBufferFields GWHdr201;
static CommonBufferFields GWHdr202;
static CommonBufferFields GWHdr203;
static CommonBufferFields GWHdr204;
static CommonBufferFields GWHdr205;
static CommonBufferFields GWHdr206;
static CommonBufferFields GWHdr207;
static CommonBufferFields GWHdr208;
static CommonBufferFields GWHdr209;
static CommonBufferFields GWHdr210;
static CommonBufferFields GWHdr211;
static CommonBufferFields GWHdr212;
static CommonBufferFields GWHdr213;
static CommonBufferFields GWHdr214;
static CommonBufferFields GWHdr215;
static CommonBufferFields GWHdr216;
static CommonBufferFields GWHdr217;
static CommonBufferFields GWHdr218;
static CommonBufferFields GWHdr219;
static CommonBufferFields GWHdr220;
static CommonBufferFields GWHdr221;
static CommonBufferFields GWHdr222;
static CommonBufferFields GWHdr223;
static CommonBufferFields GWHdr224;
static CommonBufferFields GWHdr225;
static CommonBufferFields GWHdr226;
static CommonBufferFields GWHdr227;
static CommonBufferFields GWHdr228;
static CommonBufferFields GWHdr229;
static CommonBufferFields GWHdr230;
static CommonBufferFields GWHdr231;
static CommonBufferFields GWHdr232;
static CommonBufferFields GWHdr233;
static CommonBufferFields GWHdr234;
static CommonBufferFields GWHdr235;
static CommonBufferFields GWHdr236;
static CommonBufferFields GWHdr237;
static CommonBufferFields GWHdr238;
static CommonBufferFields GWHdr239;
static CommonBufferFields GWHdr240;
static CommonBufferFields GWHdr241;
static CommonBufferFields GWHdr242;
static CommonBufferFields GWHdr243;
static CommonBufferFields GWHdr244;
static CommonBufferFields GWHdr245;
static CommonBufferFields GWHdr246;
static CommonBufferFields GWHdr247;
static CommonBufferFields GWHdr248;
static CommonBufferFields GWHdr249;
static CommonBufferFields GWHdr250;
static CommonBufferFields GWHdr251;
static CommonBufferFields GWHdr252;
static CommonBufferFields GWHdr253;
static CommonBufferFields GWHdr254;
static CommonBufferFields GWHdr255;
static CommonBufferFields GWHdr256;
static CommonBufferFields GWHdr257;
static CommonBufferFields GWHdr258;
static CommonBufferFields GWHdr259;
static CommonBufferFields GWHdr260;
static CommonBufferFields GWHdr261;
static CommonBufferFields GWHdr262;
static CommonBufferFields GWHdr263;
static CommonBufferFields GWHdr264;
static CommonBufferFields GWHdr265;
static CommonBufferFields GWHdr266;
static CommonBufferFields GWHdr267;
static CommonBufferFields GWHdr268;
static CommonBufferFields GWHdr269;
static CommonBufferFields GWHdr270;
static CommonBufferFields GWHdr271;
static CommonBufferFields GWHdr272;
static CommonBufferFields GWHdr273;
static CommonBufferFields GWHdr274;
static CommonBufferFields GWHdr275;
static CommonBufferFields GWHdr276;
static CommonBufferFields GWHdr277;
static CommonBufferFields GWHdr278;
static CommonBufferFields GWHdr279;
static CommonBufferFields GWHdr280;
static CommonBufferFields GWHdr281;
static CommonBufferFields GWHdr282;
static CommonBufferFields GWHdr283;
static CommonBufferFields GWHdr284;
static CommonBufferFields GWHdr285;
static CommonBufferFields GWHdr286;
static CommonBufferFields GWHdr287;
static CommonBufferFields GWHdr288;
static CommonBufferFields GWHdr289;
static CommonBufferFields GWHdr290;
static CommonBufferFields GWHdr291;
static CommonBufferFields GWHdr292;
static CommonBufferFields GWHdr293;
static CommonBufferFields GWHdr294;
static CommonBufferFields GWHdr295;
static CommonBufferFields GWHdr296;
static CommonBufferFields GWHdr297;
static CommonBufferFields GWHdr298;
static CommonBufferFields GWHdr299;
static CommonBufferFields GWHdr300;
static CommonBufferFields GWHdr301;
static CommonBufferFields GWHdr302;
static CommonBufferFields GWHdr303;
static CommonBufferFields GWHdr304;
static CommonBufferFields GWHdr305;
static CommonBufferFields GWHdr306;
static CommonBufferFields GWHdr307;
static CommonBufferFields GWHdr308;
static CommonBufferFields GWHdr309;
static CommonBufferFields GWHdr310;
static CommonBufferFields GWHdr311;
static CommonBufferFields GWHdr312;
static CommonBufferFields GWHdr313;
static CommonBufferFields GWHdr314;
static CommonBufferFields GWHdr315;
static CommonBufferFields GWHdr316;
static CommonBufferFields GWHdr317;
static CommonBufferFields GWHdr318;
static CommonBufferFields GWHdr319;
static CommonBufferFields GWHdr320;
static CommonBufferFields GWHdr321;
static CommonBufferFields GWHdr322;
static CommonBufferFields GWHdr323;
static CommonBufferFields GWHdr324;
static CommonBufferFields GWHdr325;
static CommonBufferFields GWHdr326;
static CommonBufferFields GWHdr327;
static CommonBufferFields GWHdr328;
static CommonBufferFields GWHdr329;
static CommonBufferFields GWHdr330;
static CommonBufferFields GWHdr331;
static CommonBufferFields GWHdr332;
static CommonBufferFields GWHdr333;
static CommonBufferFields GWHdr334;
static CommonBufferFields GWHdr335;
static CommonBufferFields GWHdr336;
static CommonBufferFields GWHdr337;
static CommonBufferFields GWHdr338;
static CommonBufferFields GWHdr339;
static CommonBufferFields GWHdr340;
static CommonBufferFields GWHdr341;
static CommonBufferFields GWHdr342;
static CommonBufferFields GWHdr343;
static CommonBufferFields GWHdr344;
static CommonBufferFields GWHdr345;
static CommonBufferFields GWHdr346;
static CommonBufferFields GWHdr347;
static CommonBufferFields GWHdr348;
static CommonBufferFields GWHdr349;
static CommonBufferFields GWHdr350;
static CommonBufferFields GWHdr351;
static CommonBufferFields GWHdr352;
static CommonBufferFields GWHdr353;
static CommonBufferFields GWHdr354;
static CommonBufferFields GWHdr355;
static CommonBufferFields GWHdr356;
static CommonBufferFields GWHdr357;
static CommonBufferFields GWHdr358;
static CommonBufferFields GWHdr359;
static CommonBufferFields GWHdr360;
static CommonBufferFields GWHdr361;
static CommonBufferFields GWHdr362;
static CommonBufferFields GWHdr363;
static CommonBufferFields GWHdr364;
static CommonBufferFields GWHdr365;
static CommonBufferFields GWHdr366;
static CommonBufferFields GWHdr367;
static CommonBufferFields GWHdr368;
static CommonBufferFields GWHdr369;
static CommonBufferFields GWHdr370;
static CommonBufferFields GWHdr371;
static CommonBufferFields GWHdr372;
static CommonBufferFields GWHdr373;
static CommonBufferFields GWHdr374;
static CommonBufferFields GWHdr375;
static CommonBufferFields GWHdr376;
static CommonBufferFields GWHdr377;
static CommonBufferFields GWHdr378;
static CommonBufferFields GWHdr379;
static CommonBufferFields GWHdr380;
static CommonBufferFields GWHdr381;
static CommonBufferFields GWHdr382;
static CommonBufferFields GWHdr383;
static CommonBufferFields GWHdr384;
static CommonBufferFields GWHdr385;
static CommonBufferFields GWHdr386;
static CommonBufferFields GWHdr387;
static CommonBufferFields GWHdr388;
static CommonBufferFields GWHdr389;
static CommonBufferFields GWHdr390;
static CommonBufferFields GWHdr391;
static CommonBufferFields GWHdr392;
static CommonBufferFields GWHdr393;
static CommonBufferFields GWHdr394;
static CommonBufferFields GWHdr395;
static CommonBufferFields GWHdr396;
static CommonBufferFields GWHdr397;
static CommonBufferFields GWHdr398;
static CommonBufferFields GWHdr399;
static CommonBufferFields GWHdr400;
static CommonBufferFields GWHdr401;
static CommonBufferFields GWHdr402;
static CommonBufferFields GWHdr403;
static CommonBufferFields GWHdr404;
static CommonBufferFields GWHdr405;
static CommonBufferFields GWHdr406;
static CommonBufferFields GWHdr407;
static CommonBufferFields GWHdr408;
static CommonBufferFields GWHdr409;
static CommonBufferFields GWHdr410;
static CommonBufferFields GWHdr411;
static CommonBufferFields GWHdr412;
static CommonBufferFields GWHdr413;
static CommonBufferFields GWHdr414;
static CommonBufferFields GWHdr415;
static CommonBufferFields GWHdr416;
static CommonBufferFields GWHdr417;
static CommonBufferFields GWHdr418;
static CommonBufferFields GWHdr419;
static CommonBufferFields GWHdr420;
static CommonBufferFields GWHdr421;
static CommonBufferFields GWHdr422;
static CommonBufferFields GWHdr423;
static CommonBufferFields GWHdr424;
static CommonBufferFields GWHdr425;
static CommonBufferFields GWHdr426;
static CommonBufferFields GWHdr427;
static CommonBufferFields GWHdr428;
static CommonBufferFields GWHdr429;
static CommonBufferFields GWHdr430;
static CommonBufferFields GWHdr431;
static CommonBufferFields GWHdr432;
static CommonBufferFields GWHdr433;
static CommonBufferFields GWHdr434;
static CommonBufferFields GWHdr435;
static CommonBufferFields GWHdr436;
static CommonBufferFields GWHdr437;
static CommonBufferFields GWHdr438;
static CommonBufferFields GWHdr439;
static CommonBufferFields GWHdr440;
static CommonBufferFields GWHdr441;
static CommonBufferFields GWHdr442;
static CommonBufferFields GWHdr443;
static CommonBufferFields GWHdr444;
static CommonBufferFields GWHdr445;
static CommonBufferFields GWHdr446;
static CommonBufferFields GWHdr447;
static CommonBufferFields GWHdr448;
static CommonBufferFields GWHdr449;
static CommonBufferFields GWHdr450;
static CommonBufferFields GWHdr451;
static CommonBufferFields GWHdr452;
static CommonBufferFields GWHdr453;
static CommonBufferFields GWHdr454;
static CommonBufferFields GWHdr455;
static CommonBufferFields GWHdr456;
static CommonBufferFields GWHdr457;
static CommonBufferFields GWHdr458;
static CommonBufferFields GWHdr459;
static CommonBufferFields GWHdr460;
static CommonBufferFields GWHdr461;
static CommonBufferFields GWHdr462;
static CommonBufferFields GWHdr463;
static CommonBufferFields GWHdr464;
static CommonBufferFields GWHdr465;
static CommonBufferFields GWHdr466;
static CommonBufferFields GWHdr467;
static CommonBufferFields GWHdr468;
static CommonBufferFields GWHdr469;
static CommonBufferFields GWHdr470;
static CommonBufferFields GWHdr471;
static CommonBufferFields GWHdr472;
static CommonBufferFields GWHdr473;
static CommonBufferFields GWHdr474;
static CommonBufferFields GWHdr475;
static CommonBufferFields GWHdr476;
static CommonBufferFields GWHdr477;
static CommonBufferFields GWHdr478;
static CommonBufferFields GWHdr479;

/* GWバッファのデータ要素 */
static uint8 GWData000[L3R_DATAMAX000];
static uint8 GWData001[L3R_DATAMAX001];
static uint8 GWData002[L3R_DATAMAX002];
static uint8 GWData003[L3R_DATAMAX003];
static uint8 GWData004[L3R_DATAMAX004];
static uint8 GWData005[L3R_DATAMAX005];
static uint8 GWData006[L3R_DATAMAX006];
static uint8 GWData007[L3R_DATAMAX007];
static uint8 GWData008[L3R_DATAMAX008];
static uint8 GWData009[L3R_DATAMAX009];
static uint8 GWData010[L3R_DATAMAX010];
static uint8 GWData011[L3R_DATAMAX011];
static uint8 GWData012[L3R_DATAMAX012];
static uint8 GWData013[L3R_DATAMAX013];
static uint8 GWData014[L3R_DATAMAX014];
static uint8 GWData015[L3R_DATAMAX015];
static uint8 GWData016[L3R_DATAMAX016];
static uint8 GWData017[L3R_DATAMAX017];
static uint8 GWData018[L3R_DATAMAX018];
static uint8 GWData019[L3R_DATAMAX019];
static uint8 GWData020[L3R_DATAMAX020];
static uint8 GWData021[L3R_DATAMAX021];
static uint8 GWData022[L3R_DATAMAX022];
static uint8 GWData023[L3R_DATAMAX023];
static uint8 GWData024[L3R_DATAMAX024];
static uint8 GWData025[L3R_DATAMAX025];
static uint8 GWData026[L3R_DATAMAX026];
static uint8 GWData027[L3R_DATAMAX027];
static uint8 GWData028[L3R_DATAMAX028];
static uint8 GWData029[L3R_DATAMAX029];
static uint8 GWData030[L3R_DATAMAX030];
static uint8 GWData031[L3R_DATAMAX031];
static uint8 GWData032[L3R_DATAMAX032];
static uint8 GWData033[L3R_DATAMAX033];
static uint8 GWData034[L3R_DATAMAX034];
static uint8 GWData035[L3R_DATAMAX035];
static uint8 GWData036[L3R_DATAMAX036];
static uint8 GWData037[L3R_DATAMAX037];
static uint8 GWData038[L3R_DATAMAX038];
static uint8 GWData039[L3R_DATAMAX039];
static uint8 GWData040[L3R_DATAMAX040];
static uint8 GWData041[L3R_DATAMAX041];
static uint8 GWData042[L3R_DATAMAX042];
static uint8 GWData043[L3R_DATAMAX043];
static uint8 GWData044[L3R_DATAMAX044];
static uint8 GWData045[L3R_DATAMAX045];
static uint8 GWData046[L3R_DATAMAX046];
static uint8 GWData047[L3R_DATAMAX047];
static uint8 GWData048[L3R_DATAMAX048];
static uint8 GWData049[L3R_DATAMAX049];
static uint8 GWData050[L3R_DATAMAX050];
static uint8 GWData051[L3R_DATAMAX051];
static uint8 GWData052[L3R_DATAMAX052];
static uint8 GWData053[L3R_DATAMAX053];
static uint8 GWData054[L3R_DATAMAX054];
static uint8 GWData055[L3R_DATAMAX055];
static uint8 GWData056[L3R_DATAMAX056];
static uint8 GWData057[L3R_DATAMAX057];
static uint8 GWData058[L3R_DATAMAX058];
static uint8 GWData059[L3R_DATAMAX059];
static uint8 GWData060[L3R_DATAMAX060];
static uint8 GWData061[L3R_DATAMAX061];
static uint8 GWData062[L3R_DATAMAX062];
static uint8 GWData063[L3R_DATAMAX063];
static uint8 GWData064[L3R_DATAMAX064];
static uint8 GWData065[L3R_DATAMAX065];
static uint8 GWData066[L3R_DATAMAX066];
static uint8 GWData067[L3R_DATAMAX067];
static uint8 GWData068[L3R_DATAMAX068];
static uint8 GWData069[L3R_DATAMAX069];
static uint8 GWData070[L3R_DATAMAX070];
static uint8 GWData071[L3R_DATAMAX071];
static uint8 GWData072[L3R_DATAMAX072];
static uint8 GWData073[L3R_DATAMAX073];
static uint8 GWData074[L3R_DATAMAX074];
static uint8 GWData075[L3R_DATAMAX075];
static uint8 GWData076[L3R_DATAMAX076];
static uint8 GWData077[L3R_DATAMAX077];
static uint8 GWData078[L3R_DATAMAX078];
static uint8 GWData079[L3R_DATAMAX079];
static uint8 GWData080[L3R_DATAMAX080];
static uint8 GWData081[L3R_DATAMAX081];
static uint8 GWData082[L3R_DATAMAX082];
static uint8 GWData083[L3R_DATAMAX083];
static uint8 GWData084[L3R_DATAMAX084];
static uint8 GWData085[L3R_DATAMAX085];
static uint8 GWData086[L3R_DATAMAX086];
static uint8 GWData087[L3R_DATAMAX087];
static uint8 GWData088[L3R_DATAMAX088];
static uint8 GWData089[L3R_DATAMAX089];
static uint8 GWData090[L3R_DATAMAX090];
static uint8 GWData091[L3R_DATAMAX091];
static uint8 GWData092[L3R_DATAMAX092];
static uint8 GWData093[L3R_DATAMAX093];
static uint8 GWData094[L3R_DATAMAX094];
static uint8 GWData095[L3R_DATAMAX095];
static uint8 GWData096[L3R_DATAMAX096];
static uint8 GWData097[L3R_DATAMAX097];
static uint8 GWData098[L3R_DATAMAX098];
static uint8 GWData099[L3R_DATAMAX099];
static uint8 GWData100[L3R_DATAMAX100];
static uint8 GWData101[L3R_DATAMAX101];
static uint8 GWData102[L3R_DATAMAX102];
static uint8 GWData103[L3R_DATAMAX103];
static uint8 GWData104[L3R_DATAMAX104];
static uint8 GWData105[L3R_DATAMAX105];
static uint8 GWData106[L3R_DATAMAX106];
static uint8 GWData107[L3R_DATAMAX107];
static uint8 GWData108[L3R_DATAMAX108];
static uint8 GWData109[L3R_DATAMAX109];
static uint8 GWData110[L3R_DATAMAX110];
static uint8 GWData111[L3R_DATAMAX111];
static uint8 GWData112[L3R_DATAMAX112];
static uint8 GWData113[L3R_DATAMAX113];
static uint8 GWData114[L3R_DATAMAX114];
static uint8 GWData115[L3R_DATAMAX115];
static uint8 GWData116[L3R_DATAMAX116];
static uint8 GWData117[L3R_DATAMAX117];
static uint8 GWData118[L3R_DATAMAX118];
static uint8 GWData119[L3R_DATAMAX119];
static uint8 GWData120[L3R_DATAMAX120];
static uint8 GWData121[L3R_DATAMAX121];
static uint8 GWData122[L3R_DATAMAX122];
static uint8 GWData123[L3R_DATAMAX123];
static uint8 GWData124[L3R_DATAMAX124];
static uint8 GWData125[L3R_DATAMAX125];
static uint8 GWData126[L3R_DATAMAX126];
static uint8 GWData127[L3R_DATAMAX127];
static uint8 GWData128[L3R_DATAMAX128];
static uint8 GWData129[L3R_DATAMAX129];
static uint8 GWData130[L3R_DATAMAX130];
static uint8 GWData131[L3R_DATAMAX131];
static uint8 GWData132[L3R_DATAMAX132];
static uint8 GWData133[L3R_DATAMAX133];
static uint8 GWData134[L3R_DATAMAX134];
static uint8 GWData135[L3R_DATAMAX135];
static uint8 GWData136[L3R_DATAMAX136];
static uint8 GWData137[L3R_DATAMAX137];
static uint8 GWData138[L3R_DATAMAX138];
static uint8 GWData139[L3R_DATAMAX139];
static uint8 GWData140[L3R_DATAMAX140];
static uint8 GWData141[L3R_DATAMAX141];
static uint8 GWData142[L3R_DATAMAX142];
static uint8 GWData143[L3R_DATAMAX143];
static uint8 GWData144[L3R_DATAMAX144];
static uint8 GWData145[L3R_DATAMAX145];
static uint8 GWData146[L3R_DATAMAX146];
static uint8 GWData147[L3R_DATAMAX147];
static uint8 GWData148[L3R_DATAMAX148];
static uint8 GWData149[L3R_DATAMAX149];
static uint8 GWData150[L3R_DATAMAX150];
static uint8 GWData151[L3R_DATAMAX151];
static uint8 GWData152[L3R_DATAMAX152];
static uint8 GWData153[L3R_DATAMAX153];
static uint8 GWData154[L3R_DATAMAX154];
static uint8 GWData155[L3R_DATAMAX155];
static uint8 GWData156[L3R_DATAMAX156];
static uint8 GWData157[L3R_DATAMAX157];
static uint8 GWData158[L3R_DATAMAX158];
static uint8 GWData159[L3R_DATAMAX159];
static uint8 GWData160[L3R_DATAMAX160];
static uint8 GWData161[L3R_DATAMAX161];
static uint8 GWData162[L3R_DATAMAX162];
static uint8 GWData163[L3R_DATAMAX163];
static uint8 GWData164[L3R_DATAMAX164];
static uint8 GWData165[L3R_DATAMAX165];
static uint8 GWData166[L3R_DATAMAX166];
static uint8 GWData167[L3R_DATAMAX167];
static uint8 GWData168[L3R_DATAMAX168];
static uint8 GWData169[L3R_DATAMAX169];
static uint8 GWData170[L3R_DATAMAX170];
static uint8 GWData171[L3R_DATAMAX171];
static uint8 GWData172[L3R_DATAMAX172];
static uint8 GWData173[L3R_DATAMAX173];
static uint8 GWData174[L3R_DATAMAX174];
static uint8 GWData175[L3R_DATAMAX175];
static uint8 GWData176[L3R_DATAMAX176];
static uint8 GWData177[L3R_DATAMAX177];
static uint8 GWData178[L3R_DATAMAX178];
static uint8 GWData179[L3R_DATAMAX179];
static uint8 GWData180[L3R_DATAMAX180];
static uint8 GWData181[L3R_DATAMAX181];
static uint8 GWData182[L3R_DATAMAX182];
static uint8 GWData183[L3R_DATAMAX183];
static uint8 GWData184[L3R_DATAMAX184];
static uint8 GWData185[L3R_DATAMAX185];
static uint8 GWData186[L3R_DATAMAX186];
static uint8 GWData187[L3R_DATAMAX187];
static uint8 GWData188[L3R_DATAMAX188];
static uint8 GWData189[L3R_DATAMAX189];
static uint8 GWData190[L3R_DATAMAX190];
static uint8 GWData191[L3R_DATAMAX191];
static uint8 GWData192[L3R_DATAMAX192];
static uint8 GWData193[L3R_DATAMAX193];
static uint8 GWData194[L3R_DATAMAX194];
static uint8 GWData195[L3R_DATAMAX195];
static uint8 GWData196[L3R_DATAMAX196];
static uint8 GWData197[L3R_DATAMAX197];
static uint8 GWData198[L3R_DATAMAX198];
static uint8 GWData199[L3R_DATAMAX199];
static uint8 GWData200[L3R_DATAMAX200];
static uint8 GWData201[L3R_DATAMAX201];
static uint8 GWData202[L3R_DATAMAX202];
static uint8 GWData203[L3R_DATAMAX203];
static uint8 GWData204[L3R_DATAMAX204];
static uint8 GWData205[L3R_DATAMAX205];
static uint8 GWData206[L3R_DATAMAX206];
static uint8 GWData207[L3R_DATAMAX207];
static uint8 GWData208[L3R_DATAMAX208];
static uint8 GWData209[L3R_DATAMAX209];
static uint8 GWData210[L3R_DATAMAX210];
static uint8 GWData211[L3R_DATAMAX211];
static uint8 GWData212[L3R_DATAMAX212];
static uint8 GWData213[L3R_DATAMAX213];
static uint8 GWData214[L3R_DATAMAX214];
static uint8 GWData215[L3R_DATAMAX215];
static uint8 GWData216[L3R_DATAMAX216];
static uint8 GWData217[L3R_DATAMAX217];
static uint8 GWData218[L3R_DATAMAX218];
static uint8 GWData219[L3R_DATAMAX219];
static uint8 GWData220[L3R_DATAMAX220];
static uint8 GWData221[L3R_DATAMAX221];
static uint8 GWData222[L3R_DATAMAX222];
static uint8 GWData223[L3R_DATAMAX223];
static uint8 GWData224[L3R_DATAMAX224];
static uint8 GWData225[L3R_DATAMAX225];
static uint8 GWData226[L3R_DATAMAX226];
static uint8 GWData227[L3R_DATAMAX227];
static uint8 GWData228[L3R_DATAMAX228];
static uint8 GWData229[L3R_DATAMAX229];
static uint8 GWData230[L3R_DATAMAX230];
static uint8 GWData231[L3R_DATAMAX231];
static uint8 GWData232[L3R_DATAMAX232];
static uint8 GWData233[L3R_DATAMAX233];
static uint8 GWData234[L3R_DATAMAX234];
static uint8 GWData235[L3R_DATAMAX235];
static uint8 GWData236[L3R_DATAMAX236];
static uint8 GWData237[L3R_DATAMAX237];
static uint8 GWData238[L3R_DATAMAX238];
static uint8 GWData239[L3R_DATAMAX239];
static uint8 GWData240[L3R_DATAMAX240];
static uint8 GWData241[L3R_DATAMAX241];
static uint8 GWData242[L3R_DATAMAX242];
static uint8 GWData243[L3R_DATAMAX243];
static uint8 GWData244[L3R_DATAMAX244];
static uint8 GWData245[L3R_DATAMAX245];
static uint8 GWData246[L3R_DATAMAX246];
static uint8 GWData247[L3R_DATAMAX247];
static uint8 GWData248[L3R_DATAMAX248];
static uint8 GWData249[L3R_DATAMAX249];
static uint8 GWData250[L3R_DATAMAX250];
static uint8 GWData251[L3R_DATAMAX251];
static uint8 GWData252[L3R_DATAMAX252];
static uint8 GWData253[L3R_DATAMAX253];
static uint8 GWData254[L3R_DATAMAX254];
static uint8 GWData255[L3R_DATAMAX255];
static uint8 GWData256[L3R_DATAMAX256];
static uint8 GWData257[L3R_DATAMAX257];
static uint8 GWData258[L3R_DATAMAX258];
static uint8 GWData259[L3R_DATAMAX259];
static uint8 GWData260[L3R_DATAMAX260];
static uint8 GWData261[L3R_DATAMAX261];
static uint8 GWData262[L3R_DATAMAX262];
static uint8 GWData263[L3R_DATAMAX263];
static uint8 GWData264[L3R_DATAMAX264];
static uint8 GWData265[L3R_DATAMAX265];
static uint8 GWData266[L3R_DATAMAX266];
static uint8 GWData267[L3R_DATAMAX267];
static uint8 GWData268[L3R_DATAMAX268];
static uint8 GWData269[L3R_DATAMAX269];
static uint8 GWData270[L3R_DATAMAX270];
static uint8 GWData271[L3R_DATAMAX271];
static uint8 GWData272[L3R_DATAMAX272];
static uint8 GWData273[L3R_DATAMAX273];
static uint8 GWData274[L3R_DATAMAX274];
static uint8 GWData275[L3R_DATAMAX275];
static uint8 GWData276[L3R_DATAMAX276];
static uint8 GWData277[L3R_DATAMAX277];
static uint8 GWData278[L3R_DATAMAX278];
static uint8 GWData279[L3R_DATAMAX279];
static uint8 GWData280[L3R_DATAMAX280];
static uint8 GWData281[L3R_DATAMAX281];
static uint8 GWData282[L3R_DATAMAX282];
static uint8 GWData283[L3R_DATAMAX283];
static uint8 GWData284[L3R_DATAMAX284];
static uint8 GWData285[L3R_DATAMAX285];
static uint8 GWData286[L3R_DATAMAX286];
static uint8 GWData287[L3R_DATAMAX287];
static uint8 GWData288[L3R_DATAMAX288];
static uint8 GWData289[L3R_DATAMAX289];
static uint8 GWData290[L3R_DATAMAX290];
static uint8 GWData291[L3R_DATAMAX291];
static uint8 GWData292[L3R_DATAMAX292];
static uint8 GWData293[L3R_DATAMAX293];
static uint8 GWData294[L3R_DATAMAX294];
static uint8 GWData295[L3R_DATAMAX295];
static uint8 GWData296[L3R_DATAMAX296];
static uint8 GWData297[L3R_DATAMAX297];
static uint8 GWData298[L3R_DATAMAX298];
static uint8 GWData299[L3R_DATAMAX299];
static uint8 GWData300[L3R_DATAMAX300];
static uint8 GWData301[L3R_DATAMAX301];
static uint8 GWData302[L3R_DATAMAX302];
static uint8 GWData303[L3R_DATAMAX303];
static uint8 GWData304[L3R_DATAMAX304];
static uint8 GWData305[L3R_DATAMAX305];
static uint8 GWData306[L3R_DATAMAX306];
static uint8 GWData307[L3R_DATAMAX307];
static uint8 GWData308[L3R_DATAMAX308];
static uint8 GWData309[L3R_DATAMAX309];
static uint8 GWData310[L3R_DATAMAX310];
static uint8 GWData311[L3R_DATAMAX311];
static uint8 GWData312[L3R_DATAMAX312];
static uint8 GWData313[L3R_DATAMAX313];
static uint8 GWData314[L3R_DATAMAX314];
static uint8 GWData315[L3R_DATAMAX315];
static uint8 GWData316[L3R_DATAMAX316];
static uint8 GWData317[L3R_DATAMAX317];
static uint8 GWData318[L3R_DATAMAX318];
static uint8 GWData319[L3R_DATAMAX319];
static uint8 GWData320[L3R_DATAMAX320];
static uint8 GWData321[L3R_DATAMAX321];
static uint8 GWData322[L3R_DATAMAX322];
static uint8 GWData323[L3R_DATAMAX323];
static uint8 GWData324[L3R_DATAMAX324];
static uint8 GWData325[L3R_DATAMAX325];
static uint8 GWData326[L3R_DATAMAX326];
static uint8 GWData327[L3R_DATAMAX327];
static uint8 GWData328[L3R_DATAMAX328];
static uint8 GWData329[L3R_DATAMAX329];
static uint8 GWData330[L3R_DATAMAX330];
static uint8 GWData331[L3R_DATAMAX331];
static uint8 GWData332[L3R_DATAMAX332];
static uint8 GWData333[L3R_DATAMAX333];
static uint8 GWData334[L3R_DATAMAX334];
static uint8 GWData335[L3R_DATAMAX335];
static uint8 GWData336[L3R_DATAMAX336];
static uint8 GWData337[L3R_DATAMAX337];
static uint8 GWData338[L3R_DATAMAX338];
static uint8 GWData339[L3R_DATAMAX339];
static uint8 GWData340[L3R_DATAMAX340];
static uint8 GWData341[L3R_DATAMAX341];
static uint8 GWData342[L3R_DATAMAX342];
static uint8 GWData343[L3R_DATAMAX343];
static uint8 GWData344[L3R_DATAMAX344];
static uint8 GWData345[L3R_DATAMAX345];
static uint8 GWData346[L3R_DATAMAX346];
static uint8 GWData347[L3R_DATAMAX347];
static uint8 GWData348[L3R_DATAMAX348];
static uint8 GWData349[L3R_DATAMAX349];
static uint8 GWData350[L3R_DATAMAX350];
static uint8 GWData351[L3R_DATAMAX351];
static uint8 GWData352[L3R_DATAMAX352];
static uint8 GWData353[L3R_DATAMAX353];
static uint8 GWData354[L3R_DATAMAX354];
static uint8 GWData355[L3R_DATAMAX355];
static uint8 GWData356[L3R_DATAMAX356];
static uint8 GWData357[L3R_DATAMAX357];
static uint8 GWData358[L3R_DATAMAX358];
static uint8 GWData359[L3R_DATAMAX359];
static uint8 GWData360[L3R_DATAMAX360];
static uint8 GWData361[L3R_DATAMAX361];
static uint8 GWData362[L3R_DATAMAX362];
static uint8 GWData363[L3R_DATAMAX363];
static uint8 GWData364[L3R_DATAMAX364];
static uint8 GWData365[L3R_DATAMAX365];
static uint8 GWData366[L3R_DATAMAX366];
static uint8 GWData367[L3R_DATAMAX367];
static uint8 GWData368[L3R_DATAMAX368];
static uint8 GWData369[L3R_DATAMAX369];
static uint8 GWData370[L3R_DATAMAX370];
static uint8 GWData371[L3R_DATAMAX371];
static uint8 GWData372[L3R_DATAMAX372];
static uint8 GWData373[L3R_DATAMAX373];
static uint8 GWData374[L3R_DATAMAX374];
static uint8 GWData375[L3R_DATAMAX375];
static uint8 GWData376[L3R_DATAMAX376];
static uint8 GWData377[L3R_DATAMAX377];
static uint8 GWData378[L3R_DATAMAX378];
static uint8 GWData379[L3R_DATAMAX379];
static uint8 GWData380[L3R_DATAMAX380];
static uint8 GWData381[L3R_DATAMAX381];
static uint8 GWData382[L3R_DATAMAX382];
static uint8 GWData383[L3R_DATAMAX383];
static uint8 GWData384[L3R_DATAMAX384];
static uint8 GWData385[L3R_DATAMAX385];
static uint8 GWData386[L3R_DATAMAX386];
static uint8 GWData387[L3R_DATAMAX387];
static uint8 GWData388[L3R_DATAMAX388];
static uint8 GWData389[L3R_DATAMAX389];
static uint8 GWData390[L3R_DATAMAX390];
static uint8 GWData391[L3R_DATAMAX391];
static uint8 GWData392[L3R_DATAMAX392];
static uint8 GWData393[L3R_DATAMAX393];
static uint8 GWData394[L3R_DATAMAX394];
static uint8 GWData395[L3R_DATAMAX395];
static uint8 GWData396[L3R_DATAMAX396];
static uint8 GWData397[L3R_DATAMAX397];
static uint8 GWData398[L3R_DATAMAX398];
static uint8 GWData399[L3R_DATAMAX399];
static uint8 GWData400[L3R_DATAMAX400];
static uint8 GWData401[L3R_DATAMAX401];
static uint8 GWData402[L3R_DATAMAX402];
static uint8 GWData403[L3R_DATAMAX403];
static uint8 GWData404[L3R_DATAMAX404];
static uint8 GWData405[L3R_DATAMAX405];
static uint8 GWData406[L3R_DATAMAX406];
static uint8 GWData407[L3R_DATAMAX407];
static uint8 GWData408[L3R_DATAMAX408];
static uint8 GWData409[L3R_DATAMAX409];
static uint8 GWData410[L3R_DATAMAX410];
static uint8 GWData411[L3R_DATAMAX411];
static uint8 GWData412[L3R_DATAMAX412];
static uint8 GWData413[L3R_DATAMAX413];
static uint8 GWData414[L3R_DATAMAX414];
static uint8 GWData415[L3R_DATAMAX415];
static uint8 GWData416[L3R_DATAMAX416];
static uint8 GWData417[L3R_DATAMAX417];
static uint8 GWData418[L3R_DATAMAX418];
static uint8 GWData419[L3R_DATAMAX419];
static uint8 GWData420[L3R_DATAMAX420];
static uint8 GWData421[L3R_DATAMAX421];
static uint8 GWData422[L3R_DATAMAX422];
static uint8 GWData423[L3R_DATAMAX423];
static uint8 GWData424[L3R_DATAMAX424];
static uint8 GWData425[L3R_DATAMAX425];
static uint8 GWData426[L3R_DATAMAX426];
static uint8 GWData427[L3R_DATAMAX427];
static uint8 GWData428[L3R_DATAMAX428];
static uint8 GWData429[L3R_DATAMAX429];
static uint8 GWData430[L3R_DATAMAX430];
static uint8 GWData431[L3R_DATAMAX431];
static uint8 GWData432[L3R_DATAMAX432];
static uint8 GWData433[L3R_DATAMAX433];
static uint8 GWData434[L3R_DATAMAX434];
static uint8 GWData435[L3R_DATAMAX435];
static uint8 GWData436[L3R_DATAMAX436];
static uint8 GWData437[L3R_DATAMAX437];
static uint8 GWData438[L3R_DATAMAX438];
static uint8 GWData439[L3R_DATAMAX439];
static uint8 GWData440[L3R_DATAMAX440];
static uint8 GWData441[L3R_DATAMAX441];
static uint8 GWData442[L3R_DATAMAX442];
static uint8 GWData443[L3R_DATAMAX443];
static uint8 GWData444[L3R_DATAMAX444];
static uint8 GWData445[L3R_DATAMAX445];
static uint8 GWData446[L3R_DATAMAX446];
static uint8 GWData447[L3R_DATAMAX447];
static uint8 GWData448[L3R_DATAMAX448];
static uint8 GWData449[L3R_DATAMAX449];
static uint8 GWData450[L3R_DATAMAX450];
static uint8 GWData451[L3R_DATAMAX451];
static uint8 GWData452[L3R_DATAMAX452];
static uint8 GWData453[L3R_DATAMAX453];
static uint8 GWData454[L3R_DATAMAX454];
static uint8 GWData455[L3R_DATAMAX455];
static uint8 GWData456[L3R_DATAMAX456];
static uint8 GWData457[L3R_DATAMAX457];
static uint8 GWData458[L3R_DATAMAX458];
static uint8 GWData459[L3R_DATAMAX459];
static uint8 GWData460[L3R_DATAMAX460];
static uint8 GWData461[L3R_DATAMAX461];
static uint8 GWData462[L3R_DATAMAX462];
static uint8 GWData463[L3R_DATAMAX463];
static uint8 GWData464[L3R_DATAMAX464];
static uint8 GWData465[L3R_DATAMAX465];
static uint8 GWData466[L3R_DATAMAX466];
static uint8 GWData467[L3R_DATAMAX467];
static uint8 GWData468[L3R_DATAMAX468];
static uint8 GWData469[L3R_DATAMAX469];
static uint8 GWData470[L3R_DATAMAX470];
static uint8 GWData471[L3R_DATAMAX471];
static uint8 GWData472[L3R_DATAMAX472];
static uint8 GWData473[L3R_DATAMAX473];
static uint8 GWData474[L3R_DATAMAX474];
static uint8 GWData475[L3R_DATAMAX475];
static uint8 GWData476[L3R_DATAMAX476];
static uint8 GWData477[L3R_DATAMAX477];
static uint8 GWData478[L3R_DATAMAX478];
static uint8 GWData479[L3R_DATAMAX479];

#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"

static CommonBuffer GwBufferMember000 = { &GwIdRouter_funcList[0], GWData000, L3R_FRAMECLASS_NON, L3R_DATAMAX000,
		&GWHdr000, L3R_PRTCL_BIT_NONE, 1, 0}; /* GW-ID:000 */
static CommonBuffer GwBufferMember001 = { &GwIdRouter_funcList[0], GWData001, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX001,
		&GWHdr001, L3R_PRTCL_BIT_CAN3, 64, 0 }; /* GW-ID:001(0x013) */
static CommonBuffer GwBufferMember002 = { &GwIdRouter_funcList[0], GWData002, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX002,
		&GWHdr002, L3R_PRTCL_BIT_CAN3, 64, 0 }; /* GW-ID:002(0x01B) */
static CommonBuffer GwBufferMember003 = { &GwIdRouter_funcList[0], GWData003, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX003,
		&GWHdr003, L3R_PRTCL_BIT_CAN3, 32, 8 }; /* GW-ID:003(0x049) */
static CommonBuffer GwBufferMember004 = { &GwIdRouter_funcList[0], GWData004, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX004,
		&GWHdr004, L3R_PRTCL_BIT_CAN3, 64, 10 }; /* GW-ID:004(0x062) */
static CommonBuffer GwBufferMember005 = { &GwIdRouter_funcList[0], GWData005, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX005,
		&GWHdr005, L3R_PRTCL_BIT_CAN3, 32, 10 }; /* GW-ID:005(0x069) */
static CommonBuffer GwBufferMember006 = { &GwIdRouter_funcList[0], GWData006, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX006,
		&GWHdr006, L3R_PRTCL_BIT_CAN3, 32, 10 }; /* GW-ID:006(0x06A) */
static CommonBuffer GwBufferMember007 = { &GwIdRouter_funcList[0], GWData007, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX007,
		&GWHdr007, L3R_PRTCL_BIT_CAN3, 32, 12 }; /* GW-ID:007(0x072) */
static CommonBuffer GwBufferMember008 = { &GwIdRouter_funcList[0], GWData008, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX008,
		&GWHdr008, L3R_PRTCL_BIT_CAN3, 32, 16 }; /* GW-ID:008(0x075) */
static CommonBuffer GwBufferMember009 = { &GwIdRouter_funcList[0], GWData009, L3R_FRAMECLASS_CTRL_0, L3R_DATAMAX009,
		&GWHdr009, L3R_PRTCL_BIT_CAN3, 8, 16 }; /* GW-ID:009(0x07E) */
static CommonBuffer GwBufferMember010 = { &GwIdRouter_funcList[0], GWData010, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX010,
		&GWHdr010, L3R_PRTCL_BIT_CAN3, 32, 20 }; /* GW-ID:010(0x086) */
static CommonBuffer GwBufferMember011 = { &GwIdRouter_funcList[0], GWData011, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX011,
		&GWHdr011, L3R_PRTCL_BIT_CAN3, 32, 20 }; /* GW-ID:011(0x09E) */
static CommonBuffer GwBufferMember012 = { &GwIdRouter_funcList[0], GWData012, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX012,
		&GWHdr012, L3R_PRTCL_BIT_CAN3, 32, 24 }; /* GW-ID:012(0x0A0) */
static CommonBuffer GwBufferMember013 = { &GwIdRouter_funcList[0], GWData013, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX013,
		&GWHdr013, L3R_PRTCL_BIT_CAN3, 32, 24 }; /* GW-ID:013(0x0A1) */
static CommonBuffer GwBufferMember014 = { &GwIdRouter_funcList[0], GWData014, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX014,
		&GWHdr014, L3R_PRTCL_BIT_CAN3, 8, 24 }; /* GW-ID:014(0x0A3) */
static CommonBuffer GwBufferMember015 = { &GwIdRouter_funcList[0], GWData015, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX015,
		&GWHdr015, L3R_PRTCL_BIT_CAN3, 32, 24 }; /* GW-ID:015(0x0A4) */
static CommonBuffer GwBufferMember016 = { &GwIdRouter_funcList[0], GWData016, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX016,
		&GWHdr016, L3R_PRTCL_BIT_CAN3, 8, 24 }; /* GW-ID:016(0x0A5) */
static CommonBuffer GwBufferMember017 = { &GwIdRouter_funcList[0], GWData017, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX017,
		&GWHdr017, L3R_PRTCL_BIT_CAN3, 8, 24 }; /* GW-ID:017(0x0A6) */
static CommonBuffer GwBufferMember018 = { &GwIdRouter_funcList[0], GWData018, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX018,
		&GWHdr018, L3R_PRTCL_BIT_CAN3, 64, 25 }; /* GW-ID:018(0x0A8) */
static CommonBuffer GwBufferMember019 = { &GwIdRouter_funcList[0], GWData019, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX019,
		&GWHdr019, L3R_PRTCL_BIT_CAN3, 64, 25 }; /* GW-ID:019(0x0A9) */
static CommonBuffer GwBufferMember020 = { &GwIdRouter_funcList[0], GWData020, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX020,
		&GWHdr020, L3R_PRTCL_BIT_CAN3, 32, 30 }; /* GW-ID:020(0x0B7) */
static CommonBuffer GwBufferMember021 = { &GwIdRouter_funcList[0], GWData021, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX021,
		&GWHdr021, L3R_PRTCL_BIT_CAN3, 64, 30 }; /* GW-ID:021(0x0B8) */
static CommonBuffer GwBufferMember022 = { &GwIdRouter_funcList[0], GWData022, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX022,
		&GWHdr022, L3R_PRTCL_BIT_CAN3, 8, 50 }; /* GW-ID:022(0x0F3) */
static CommonBuffer GwBufferMember023 = { &GwIdRouter_funcList[0], GWData023, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX023,
		&GWHdr023, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:023(0x0FC) */
static CommonBuffer GwBufferMember024 = { &GwIdRouter_funcList[0], GWData024, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX024,
		&GWHdr024, L3R_PRTCL_BIT_CAN3, 8, 50 }; /* GW-ID:024(0x100) */
static CommonBuffer GwBufferMember025 = { &GwIdRouter_funcList[0], GWData025, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX025,
		&GWHdr025, L3R_PRTCL_BIT_CAN3, 32, 52 }; /* GW-ID:025(0x10B) */
static CommonBuffer GwBufferMember026 = { &GwIdRouter_funcList[0], GWData026, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX026,
		&GWHdr026, L3R_PRTCL_BIT_CAN3, 8, 96 }; /* GW-ID:026(0x115) */
static CommonBuffer GwBufferMember027 = { &GwIdRouter_funcList[0], GWData027, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX027,
		&GWHdr027, L3R_PRTCL_BIT_CAN0, 8, 100 }; /* GW-ID:027(0x121) */
static CommonBuffer GwBufferMember028 = { &GwIdRouter_funcList[0], GWData028, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX028,
		&GWHdr028, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:028(0x122) */
static CommonBuffer GwBufferMember029 = { &GwIdRouter_funcList[0], GWData029, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX029,
		&GWHdr029, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:029(0x124) */
static CommonBuffer GwBufferMember030 = { &GwIdRouter_funcList[0], GWData030, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX030,
		&GWHdr030, L3R_PRTCL_BIT_CAN2, 8, 100 }; /* GW-ID:030(0x126) */
static CommonBuffer GwBufferMember031 = { &GwIdRouter_funcList[0], GWData031, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX031,
		&GWHdr031, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:031(0x128) */
static CommonBuffer GwBufferMember032 = { &GwIdRouter_funcList[0], GWData032, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX032,
		&GWHdr032, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:032(0x12B) */
static CommonBuffer GwBufferMember033 = { &GwIdRouter_funcList[0], GWData033, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX033,
		&GWHdr033, L3R_PRTCL_BIT_CAN3, 8, 0 }; /* GW-ID:033(0x140) */
static CommonBuffer GwBufferMember034 = { &GwIdRouter_funcList[0], GWData034, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX034,
		&GWHdr034, L3R_PRTCL_BIT_CAN2, 32, 100 }; /* GW-ID:034(0x141) */
static CommonBuffer GwBufferMember035 = { &GwIdRouter_funcList[0], GWData035, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX035,
		&GWHdr035, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:035(0x143) */
static CommonBuffer GwBufferMember036 = { &GwIdRouter_funcList[0], GWData036, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX036,
		&GWHdr036, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:036(0x144) */
static CommonBuffer GwBufferMember037 = { &GwIdRouter_funcList[0], GWData037, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX037,
		&GWHdr037, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:037(0x148) */
static CommonBuffer GwBufferMember038 = { &GwIdRouter_funcList[0], GWData038, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX038,
		&GWHdr038, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:038(0x14B) */
static CommonBuffer GwBufferMember039 = { &GwIdRouter_funcList[0], GWData039, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX039,
		&GWHdr039, L3R_PRTCL_BIT_CAN0, 8, 100 }; /* GW-ID:039(0x14C) */
static CommonBuffer GwBufferMember040 = { &GwIdRouter_funcList[0], GWData040, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX040,
		&GWHdr040, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:040(0x14D) */
static CommonBuffer GwBufferMember041 = { &GwIdRouter_funcList[0], GWData041, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX041,
		&GWHdr041, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:041(0x14F) */
static CommonBuffer GwBufferMember042 = { &GwIdRouter_funcList[0], GWData042, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX042,
		&GWHdr042, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:042(0x150) */
static CommonBuffer GwBufferMember043 = { &GwIdRouter_funcList[0], GWData043, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX043,
		&GWHdr043, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:043(0x155) */
static CommonBuffer GwBufferMember044 = { &GwIdRouter_funcList[0], GWData044, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX044,
		&GWHdr044, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:044(0x159) */
static CommonBuffer GwBufferMember045 = { &GwIdRouter_funcList[0], GWData045, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX045,
		&GWHdr045, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:045(0x15A) */
static CommonBuffer GwBufferMember046 = { &GwIdRouter_funcList[0], GWData046, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX046,
		&GWHdr046, L3R_PRTCL_BIT_CAN3, 32, 0 }; /* GW-ID:046(0x161) */
static CommonBuffer GwBufferMember047 = { &GwIdRouter_funcList[0], GWData047, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX047,
		&GWHdr047, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:047(0x162) */
static CommonBuffer GwBufferMember048 = { &GwIdRouter_funcList[0], GWData048, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX048,
		&GWHdr048, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:048(0x163) */
static CommonBuffer GwBufferMember049 = { &GwIdRouter_funcList[0], GWData049, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX049,
		&GWHdr049, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:049(0x166) */
static CommonBuffer GwBufferMember050 = { &GwIdRouter_funcList[0], GWData050, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX050,
		&GWHdr050, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:050(0x167) */
static CommonBuffer GwBufferMember051 = { &GwIdRouter_funcList[0], GWData051, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX051,
		&GWHdr051, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:051(0x168) */
static CommonBuffer GwBufferMember052 = { &GwIdRouter_funcList[0], GWData052, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX052,
		&GWHdr052, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:052(0x169) */
static CommonBuffer GwBufferMember053 = { &GwIdRouter_funcList[0], GWData053, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX053,
		&GWHdr053, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:053(0x16A) */
static CommonBuffer GwBufferMember054 = { &GwIdRouter_funcList[0], GWData054, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX054,
		&GWHdr054, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:054(0x16B) */
static CommonBuffer GwBufferMember055 = { &GwIdRouter_funcList[0], GWData055, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX055,
		&GWHdr055, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:055(0x16C) */
static CommonBuffer GwBufferMember056 = { &GwIdRouter_funcList[0], GWData056, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX056,
		&GWHdr056, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:056(0x16D) */
static CommonBuffer GwBufferMember057 = { &GwIdRouter_funcList[0], GWData057, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX057,
		&GWHdr057, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:057(0x16E) */
static CommonBuffer GwBufferMember058 = { &GwIdRouter_funcList[0], GWData058, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX058,
		&GWHdr058, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:058(0x17E) */
static CommonBuffer GwBufferMember059 = { &GwIdRouter_funcList[0], GWData059, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX059,
		&GWHdr059, L3R_PRTCL_BIT_CAN2, 8, 100 }; /* GW-ID:059(0x17F) */
static CommonBuffer GwBufferMember060 = { &GwIdRouter_funcList[0], GWData060, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX060,
		&GWHdr060, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:060(0x180) */
static CommonBuffer GwBufferMember061 = { &GwIdRouter_funcList[0], GWData061, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX061,
		&GWHdr061, L3R_PRTCL_BIT_CAN0, 32, 100 }; /* GW-ID:061(0x185) */
static CommonBuffer GwBufferMember062 = { &GwIdRouter_funcList[0], GWData062, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX062,
		&GWHdr062, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:062(0x186) */
static CommonBuffer GwBufferMember063 = { &GwIdRouter_funcList[0], GWData063, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX063,
		&GWHdr063, L3R_PRTCL_BIT_CAN3, 32, 100 }; /* GW-ID:063(0x18D) */
static CommonBuffer GwBufferMember064 = { &GwIdRouter_funcList[0], GWData064, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX064,
		&GWHdr064, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:064(0x19A) */
static CommonBuffer GwBufferMember065 = { &GwIdRouter_funcList[0], GWData065, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX065,
		&GWHdr065, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:065(0x1A1) */
static CommonBuffer GwBufferMember066 = { &GwIdRouter_funcList[0], GWData066, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX066,
		&GWHdr066, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:066(0x1A2) */
static CommonBuffer GwBufferMember067 = { &GwIdRouter_funcList[0], GWData067, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX067,
		&GWHdr067, L3R_PRTCL_BIT_CAN2, 8, 200 }; /* GW-ID:067(0x1A3) */
static CommonBuffer GwBufferMember068 = { &GwIdRouter_funcList[0], GWData068, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX068,
		&GWHdr068, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:068(0x1A4) */
static CommonBuffer GwBufferMember069 = { &GwIdRouter_funcList[0], GWData069, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX069,
		&GWHdr069, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:069(0x1A5) */
static CommonBuffer GwBufferMember070 = { &GwIdRouter_funcList[0], GWData070, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX070,
		&GWHdr070, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:070(0x1A7) */
static CommonBuffer GwBufferMember071 = { &GwIdRouter_funcList[0], GWData071, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX071,
		&GWHdr071, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:071(0x1A8) */
static CommonBuffer GwBufferMember072 = { &GwIdRouter_funcList[0], GWData072, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX072,
		&GWHdr072, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:072(0x1A9) */
static CommonBuffer GwBufferMember073 = { &GwIdRouter_funcList[0], GWData073, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX073,
		&GWHdr073, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:073(0x1AB) */
static CommonBuffer GwBufferMember074 = { &GwIdRouter_funcList[0], GWData074, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX074,
		&GWHdr074, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:074(0x1AC) */
static CommonBuffer GwBufferMember075 = { &GwIdRouter_funcList[0], GWData075, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX075,
		&GWHdr075, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:075(0x1AD) */
static CommonBuffer GwBufferMember076 = { &GwIdRouter_funcList[0], GWData076, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX076,
		&GWHdr076, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:076(0x1AE) */
static CommonBuffer GwBufferMember077 = { &GwIdRouter_funcList[0], GWData077, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX077,
		&GWHdr077, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:077(0x1AF) */
static CommonBuffer GwBufferMember078 = { &GwIdRouter_funcList[0], GWData078, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX078,
		&GWHdr078, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:078(0x1B0) */
static CommonBuffer GwBufferMember079 = { &GwIdRouter_funcList[0], GWData079, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX079,
		&GWHdr079, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:079(0x1B2) */
static CommonBuffer GwBufferMember080 = { &GwIdRouter_funcList[0], GWData080, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX080,
		&GWHdr080, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:080(0x1B3) */
static CommonBuffer GwBufferMember081 = { &GwIdRouter_funcList[0], GWData081, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX081,
		&GWHdr081, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:081(0x1B4) */
static CommonBuffer GwBufferMember082 = { &GwIdRouter_funcList[0], GWData082, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX082,
		&GWHdr082, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:082(0x1B5) */
static CommonBuffer GwBufferMember083 = { &GwIdRouter_funcList[0], GWData083, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX083,
		&GWHdr083, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:083(0x1B7) */
static CommonBuffer GwBufferMember084 = { &GwIdRouter_funcList[0], GWData084, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX084,
		&GWHdr084, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:084(0x1B8) */
static CommonBuffer GwBufferMember085 = { &GwIdRouter_funcList[0], GWData085, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX085,
		&GWHdr085, L3R_PRTCL_BIT_CAN2, 32, 200 }; /* GW-ID:085(0x1B9) */
static CommonBuffer GwBufferMember086 = { &GwIdRouter_funcList[0], GWData086, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX086,
		&GWHdr086, L3R_PRTCL_BIT_CAN3, 8, 200 }; /* GW-ID:086(0x1BA) */
static CommonBuffer GwBufferMember087 = { &GwIdRouter_funcList[0], GWData087, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX087,
		&GWHdr087, L3R_PRTCL_BIT_CAN3, 8, 200 }; /* GW-ID:087(0x1BB) */
static CommonBuffer GwBufferMember088 = { &GwIdRouter_funcList[0], GWData088, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX088,
		&GWHdr088, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:088(0x1BC) */
static CommonBuffer GwBufferMember089 = { &GwIdRouter_funcList[0], GWData089, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX089,
		&GWHdr089, L3R_PRTCL_BIT_CAN0, 8, 200 }; /* GW-ID:089(0x1BD) */
static CommonBuffer GwBufferMember090 = { &GwIdRouter_funcList[0], GWData090, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX090,
		&GWHdr090, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:090(0x1BE) */
static CommonBuffer GwBufferMember091 = { &GwIdRouter_funcList[0], GWData091, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX091,
		&GWHdr091, L3R_PRTCL_BIT_CAN3, 32, 200 }; /* GW-ID:091(0x1C0) */
static CommonBuffer GwBufferMember092 = { &GwIdRouter_funcList[0], GWData092, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX092,
		&GWHdr092, L3R_PRTCL_BIT_CAN3, 8, 250 }; /* GW-ID:092(0x1C5) */
static CommonBuffer GwBufferMember093 = { &GwIdRouter_funcList[0], GWData093, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX093,
		&GWHdr093, L3R_PRTCL_BIT_CAN3, 64, 0 }; /* GW-ID:093(0x1C7) */
static CommonBuffer GwBufferMember094 = { &GwIdRouter_funcList[0], GWData094, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX094,
		&GWHdr094, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:094(0x1CA) */
static CommonBuffer GwBufferMember095 = { &GwIdRouter_funcList[0], GWData095, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX095,
		&GWHdr095, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:095(0x1CC) */
static CommonBuffer GwBufferMember096 = { &GwIdRouter_funcList[0], GWData096, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX096,
		&GWHdr096, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:096(0x1CF) */
static CommonBuffer GwBufferMember097 = { &GwIdRouter_funcList[0], GWData097, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX097,
		&GWHdr097, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:097(0x1D0) */
static CommonBuffer GwBufferMember098 = { &GwIdRouter_funcList[0], GWData098, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX098,
		&GWHdr098, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:098(0x1D1) */
static CommonBuffer GwBufferMember099 = { &GwIdRouter_funcList[0], GWData099, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX099,
		&GWHdr099, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:099(0x1D2) */
static CommonBuffer GwBufferMember100 = { &GwIdRouter_funcList[0], GWData100, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX100,
		&GWHdr100, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:100(0x1D3) */
static CommonBuffer GwBufferMember101 = { &GwIdRouter_funcList[0], GWData101, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX101,
		&GWHdr101, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:101(0x1D6) */
static CommonBuffer GwBufferMember102 = { &GwIdRouter_funcList[0], GWData102, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX102,
		&GWHdr102, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:102(0x1D7) */
static CommonBuffer GwBufferMember103 = { &GwIdRouter_funcList[0], GWData103, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX103,
		&GWHdr103, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:103(0x1D8) */
static CommonBuffer GwBufferMember104 = { &GwIdRouter_funcList[0], GWData104, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX104,
		&GWHdr104, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:104(0x1D9) */
static CommonBuffer GwBufferMember105 = { &GwIdRouter_funcList[0], GWData105, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX105,
		&GWHdr105, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:105(0x1DB) */
static CommonBuffer GwBufferMember106 = { &GwIdRouter_funcList[0], GWData106, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX106,
		&GWHdr106, L3R_PRTCL_BIT_CAN0, 8, 300 }; /* GW-ID:106(0x1DC) */
static CommonBuffer GwBufferMember107 = { &GwIdRouter_funcList[0], GWData107, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX107,
		&GWHdr107, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:107(0x1DD) */
static CommonBuffer GwBufferMember108 = { &GwIdRouter_funcList[0], GWData108, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX108,
		&GWHdr108, L3R_PRTCL_BIT_CAN3, 8, 300 }; /* GW-ID:108(0x1DE) */
static CommonBuffer GwBufferMember109 = { &GwIdRouter_funcList[0], GWData109, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX109,
		&GWHdr109, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:109(0x1DF) */
static CommonBuffer GwBufferMember110 = { &GwIdRouter_funcList[0], GWData110, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX110,
		&GWHdr110, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:110(0x1E1) */
static CommonBuffer GwBufferMember111 = { &GwIdRouter_funcList[0], GWData111, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX111,
		&GWHdr111, L3R_PRTCL_BIT_CAN3, 32, 300 }; /* GW-ID:111(0x1E3) */
static CommonBuffer GwBufferMember112 = { &GwIdRouter_funcList[0], GWData112, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX112,
		&GWHdr112, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:112(0x1EA) */
static CommonBuffer GwBufferMember113 = { &GwIdRouter_funcList[0], GWData113, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX113,
		&GWHdr113, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:113(0x1EB) */
static CommonBuffer GwBufferMember114 = { &GwIdRouter_funcList[0], GWData114, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX114,
		&GWHdr114, L3R_PRTCL_BIT_CAN0, 8, 500 }; /* GW-ID:114(0x1EC) */
static CommonBuffer GwBufferMember115 = { &GwIdRouter_funcList[0], GWData115, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX115,
		&GWHdr115, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:115(0x1EF) */
static CommonBuffer GwBufferMember116 = { &GwIdRouter_funcList[0], GWData116, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX116,
		&GWHdr116, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:116(0x1F0) */
static CommonBuffer GwBufferMember117 = { &GwIdRouter_funcList[0], GWData117, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX117,
		&GWHdr117, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:117(0x1F1) */
static CommonBuffer GwBufferMember118 = { &GwIdRouter_funcList[0], GWData118, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX118,
		&GWHdr118, L3R_PRTCL_BIT_CAN0, 8, 500 }; /* GW-ID:118(0x1F2) */
static CommonBuffer GwBufferMember119 = { &GwIdRouter_funcList[0], GWData119, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX119,
		&GWHdr119, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:119(0x1F4) */
static CommonBuffer GwBufferMember120 = { &GwIdRouter_funcList[0], GWData120, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX120,
		&GWHdr120, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:120(0x1F5) */
static CommonBuffer GwBufferMember121 = { &GwIdRouter_funcList[0], GWData121, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX121,
		&GWHdr121, L3R_PRTCL_BIT_CAN0, 8, 500 }; /* GW-ID:121(0x1F6) */
static CommonBuffer GwBufferMember122 = { &GwIdRouter_funcList[0], GWData122, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX122,
		&GWHdr122, L3R_PRTCL_BIT_CAN0, 32, 500 }; /* GW-ID:122(0x1F7) */
static CommonBuffer GwBufferMember123 = { &GwIdRouter_funcList[0], GWData123, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX123,
		&GWHdr123, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:123(0x1FA) */
static CommonBuffer GwBufferMember124 = { &GwIdRouter_funcList[0], GWData124, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX124,
		&GWHdr124, L3R_PRTCL_BIT_CAN2, 8, 500 }; /* GW-ID:124(0x1FC) */
static CommonBuffer GwBufferMember125 = { &GwIdRouter_funcList[0], GWData125, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX125,
		&GWHdr125, L3R_PRTCL_BIT_CAN2, 8, 500 }; /* GW-ID:125(0x1FD) */
static CommonBuffer GwBufferMember126 = { &GwIdRouter_funcList[0], GWData126, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX126,
		&GWHdr126, L3R_PRTCL_BIT_CAN2, 8, 500 }; /* GW-ID:126(0x1FE) */
static CommonBuffer GwBufferMember127 = { &GwIdRouter_funcList[0], GWData127, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX127,
		&GWHdr127, L3R_PRTCL_BIT_CAN2, 8, 500 }; /* GW-ID:127(0x1FF) */
static CommonBuffer GwBufferMember128 = { &GwIdRouter_funcList[0], GWData128, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX128,
		&GWHdr128, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:128(0x202) */
static CommonBuffer GwBufferMember129 = { &GwIdRouter_funcList[0], GWData129, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX129,
		&GWHdr129, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:129(0x203) */
static CommonBuffer GwBufferMember130 = { &GwIdRouter_funcList[0], GWData130, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX130,
		&GWHdr130, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:130(0x204) */
static CommonBuffer GwBufferMember131 = { &GwIdRouter_funcList[0], GWData131, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX131,
		&GWHdr131, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:131(0x207) */
static CommonBuffer GwBufferMember132 = { &GwIdRouter_funcList[0], GWData132, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX132,
		&GWHdr132, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:132(0x208) */
static CommonBuffer GwBufferMember133 = { &GwIdRouter_funcList[0], GWData133, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX133,
		&GWHdr133, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:133(0x209) */
static CommonBuffer GwBufferMember134 = { &GwIdRouter_funcList[0], GWData134, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX134,
		&GWHdr134, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:134(0x20A) */
static CommonBuffer GwBufferMember135 = { &GwIdRouter_funcList[0], GWData135, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX135,
		&GWHdr135, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:135(0x20B) */
static CommonBuffer GwBufferMember136 = { &GwIdRouter_funcList[0], GWData136, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX136,
		&GWHdr136, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:136(0x20E) */
static CommonBuffer GwBufferMember137 = { &GwIdRouter_funcList[0], GWData137, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX137,
		&GWHdr137, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:137(0x20F) */
static CommonBuffer GwBufferMember138 = { &GwIdRouter_funcList[0], GWData138, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX138,
		&GWHdr138, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:138(0x214) */
static CommonBuffer GwBufferMember139 = { &GwIdRouter_funcList[0], GWData139, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX139,
		&GWHdr139, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:139(0x219) */
static CommonBuffer GwBufferMember140 = { &GwIdRouter_funcList[0], GWData140, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX140,
		&GWHdr140, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:140(0x22E) */
static CommonBuffer GwBufferMember141 = { &GwIdRouter_funcList[0], GWData141, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX141,
		&GWHdr141, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:141(0x230) */
static CommonBuffer GwBufferMember142 = { &GwIdRouter_funcList[0], GWData142, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX142,
		&GWHdr142, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:142(0x235) */
static CommonBuffer GwBufferMember143 = { &GwIdRouter_funcList[0], GWData143, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX143,
		&GWHdr143, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:143(0x247) */
static CommonBuffer GwBufferMember144 = { &GwIdRouter_funcList[0], GWData144, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX144,
		&GWHdr144, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:144(0x24D) */
static CommonBuffer GwBufferMember145 = { &GwIdRouter_funcList[0], GWData145, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX145,
		&GWHdr145, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:145(0x251) */
static CommonBuffer GwBufferMember146 = { &GwIdRouter_funcList[0], GWData146, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX146,
		&GWHdr146, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:146(0x252) */
static CommonBuffer GwBufferMember147 = { &GwIdRouter_funcList[0], GWData147, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX147,
		&GWHdr147, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:147(0x255) */
static CommonBuffer GwBufferMember148 = { &GwIdRouter_funcList[0], GWData148, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX148,
		&GWHdr148, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:148(0x259) */
static CommonBuffer GwBufferMember149 = { &GwIdRouter_funcList[0], GWData149, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX149,
		&GWHdr149, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:149(0x25A) */
static CommonBuffer GwBufferMember150 = { &GwIdRouter_funcList[0], GWData150, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX150,
		&GWHdr150, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:150(0x261) */
static CommonBuffer GwBufferMember151 = { &GwIdRouter_funcList[0], GWData151, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX151,
		&GWHdr151, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:151(0x262) */
static CommonBuffer GwBufferMember152 = { &GwIdRouter_funcList[0], GWData152, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX152,
		&GWHdr152, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:152(0x26E) */
static CommonBuffer GwBufferMember153 = { &GwIdRouter_funcList[0], GWData153, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX153,
		&GWHdr153, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:153(0x272) */
static CommonBuffer GwBufferMember154 = { &GwIdRouter_funcList[0], GWData154, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX154,
		&GWHdr154, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:154(0x274) */
static CommonBuffer GwBufferMember155 = { &GwIdRouter_funcList[0], GWData155, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX155,
		&GWHdr155, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:155(0x275) */
static CommonBuffer GwBufferMember156 = { &GwIdRouter_funcList[0], GWData156, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX156,
		&GWHdr156, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:156(0x276) */
static CommonBuffer GwBufferMember157 = { &GwIdRouter_funcList[0], GWData157, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX157,
		&GWHdr157, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:157(0x279) */
static CommonBuffer GwBufferMember158 = { &GwIdRouter_funcList[0], GWData158, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX158,
		&GWHdr158, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:158(0x27B) */
static CommonBuffer GwBufferMember159 = { &GwIdRouter_funcList[0], GWData159, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX159,
		&GWHdr159, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:159(0x27C) */
static CommonBuffer GwBufferMember160 = { &GwIdRouter_funcList[0], GWData160, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX160,
		&GWHdr160, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:160(0x27D) */
static CommonBuffer GwBufferMember161 = { &GwIdRouter_funcList[0], GWData161, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX161,
		&GWHdr161, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:161(0x27E) */
static CommonBuffer GwBufferMember162 = { &GwIdRouter_funcList[0], GWData162, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX162,
		&GWHdr162, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:162(0x281) */
static CommonBuffer GwBufferMember163 = { &GwIdRouter_funcList[0], GWData163, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX163,
		&GWHdr163, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:163(0x282) */
static CommonBuffer GwBufferMember164 = { &GwIdRouter_funcList[0], GWData164, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX164,
		&GWHdr164, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:164(0x285) */
static CommonBuffer GwBufferMember165 = { &GwIdRouter_funcList[0], GWData165, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX165,
		&GWHdr165, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:165(0x28A) */
static CommonBuffer GwBufferMember166 = { &GwIdRouter_funcList[0], GWData166, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX166,
		&GWHdr166, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:166(0x295) */
static CommonBuffer GwBufferMember167 = { &GwIdRouter_funcList[0], GWData167, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX167,
		&GWHdr167, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:167(0x296) */
static CommonBuffer GwBufferMember168 = { &GwIdRouter_funcList[0], GWData168, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX168,
		&GWHdr168, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:168(0x2A0) */
static CommonBuffer GwBufferMember169 = { &GwIdRouter_funcList[0], GWData169, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX169,
		&GWHdr169, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:169(0x2A1) */
static CommonBuffer GwBufferMember170 = { &GwIdRouter_funcList[0], GWData170, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX170,
		&GWHdr170, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:170(0x2A6) */
static CommonBuffer GwBufferMember171 = { &GwIdRouter_funcList[0], GWData171, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX171,
		&GWHdr171, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:171(0x2A7) */
static CommonBuffer GwBufferMember172 = { &GwIdRouter_funcList[0], GWData172, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX172,
		&GWHdr172, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:172(0x2A8) */
static CommonBuffer GwBufferMember173 = { &GwIdRouter_funcList[0], GWData173, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX173,
		&GWHdr173, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:173(0x2AA) */
static CommonBuffer GwBufferMember174 = { &GwIdRouter_funcList[0], GWData174, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX174,
		&GWHdr174, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:174(0x2AF) */
static CommonBuffer GwBufferMember175 = { &GwIdRouter_funcList[0], GWData175, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX175,
		&GWHdr175, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:175(0x2B2) */
static CommonBuffer GwBufferMember176 = { &GwIdRouter_funcList[0], GWData176, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX176,
		&GWHdr176, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:176(0x2B3) */
static CommonBuffer GwBufferMember177 = { &GwIdRouter_funcList[0], GWData177, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX177,
		&GWHdr177, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:177(0x2D2) */
static CommonBuffer GwBufferMember178 = { &GwIdRouter_funcList[0], GWData178, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX178,
		&GWHdr178, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:178(0x2D3) */
static CommonBuffer GwBufferMember179 = { &GwIdRouter_funcList[0], GWData179, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX179,
		&GWHdr179, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:179(0x2D4) */
static CommonBuffer GwBufferMember180 = { &GwIdRouter_funcList[0], GWData180, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX180,
		&GWHdr180, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:180(0x2D5) */
static CommonBuffer GwBufferMember181 = { &GwIdRouter_funcList[0], GWData181, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX181,
		&GWHdr181, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:181(0x2D6) */
static CommonBuffer GwBufferMember182 = { &GwIdRouter_funcList[0], GWData182, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX182,
		&GWHdr182, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:182(0x2D7) */
static CommonBuffer GwBufferMember183 = { &GwIdRouter_funcList[0], GWData183, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX183,
		&GWHdr183, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:183(0x2DA) */
static CommonBuffer GwBufferMember184 = { &GwIdRouter_funcList[0], GWData184, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX184,
		&GWHdr184, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:184(0x2DE) */
static CommonBuffer GwBufferMember185 = { &GwIdRouter_funcList[0], GWData185, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX185,
		&GWHdr185, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:185(0x2DF) */
static CommonBuffer GwBufferMember186 = { &GwIdRouter_funcList[0], GWData186, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX186,
		&GWHdr186, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:186(0x2E0) */
static CommonBuffer GwBufferMember187 = { &GwIdRouter_funcList[0], GWData187, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX187,
		&GWHdr187, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:187(0x2E1) */
static CommonBuffer GwBufferMember188 = { &GwIdRouter_funcList[0], GWData188, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX188,
		&GWHdr188, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:188(0x2E2) */
static CommonBuffer GwBufferMember189 = { &GwIdRouter_funcList[0], GWData189, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX189,
		&GWHdr189, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:189(0x2E3) */
static CommonBuffer GwBufferMember190 = { &GwIdRouter_funcList[0], GWData190, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX190,
		&GWHdr190, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:190(0x2E5) */
static CommonBuffer GwBufferMember191 = { &GwIdRouter_funcList[0], GWData191, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX191,
		&GWHdr191, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:191(0x2E7) */
static CommonBuffer GwBufferMember192 = { &GwIdRouter_funcList[0], GWData192, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX192,
		&GWHdr192, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:192(0x2E8) */
static CommonBuffer GwBufferMember193 = { &GwIdRouter_funcList[0], GWData193, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX193,
		&GWHdr193, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:193(0x2EB) */
static CommonBuffer GwBufferMember194 = { &GwIdRouter_funcList[0], GWData194, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX194,
		&GWHdr194, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:194(0x2EE) */
static CommonBuffer GwBufferMember195 = { &GwIdRouter_funcList[0], GWData195, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX195,
		&GWHdr195, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:195(0x2EF) */
static CommonBuffer GwBufferMember196 = { &GwIdRouter_funcList[0], GWData196, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX196,
		&GWHdr196, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:196(0x2F0) */
static CommonBuffer GwBufferMember197 = { &GwIdRouter_funcList[0], GWData197, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX197,
		&GWHdr197, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:197(0x2F2) */
static CommonBuffer GwBufferMember198 = { &GwIdRouter_funcList[0], GWData198, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX198,
		&GWHdr198, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:198(0x2F3) */
static CommonBuffer GwBufferMember199 = { &GwIdRouter_funcList[0], GWData199, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX199,
		&GWHdr199, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:199(0x2F4) */
static CommonBuffer GwBufferMember200 = { &GwIdRouter_funcList[0], GWData200, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX200,
		&GWHdr200, L3R_PRTCL_BIT_CAN0, 64, 1000 }; /* GW-ID:200(0x2F5) */
static CommonBuffer GwBufferMember201 = { &GwIdRouter_funcList[0], GWData201, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX201,
		&GWHdr201, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:201(0x2F6) */
static CommonBuffer GwBufferMember202 = { &GwIdRouter_funcList[0], GWData202, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX202,
		&GWHdr202, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:202(0x2F7) */
static CommonBuffer GwBufferMember203 = { &GwIdRouter_funcList[0], GWData203, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX203,
		&GWHdr203, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:203(0x2F8) */
static CommonBuffer GwBufferMember204 = { &GwIdRouter_funcList[0], GWData204, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX204,
		&GWHdr204, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:204(0x2F9) */
static CommonBuffer GwBufferMember205 = { &GwIdRouter_funcList[0], GWData205, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX205,
		&GWHdr205, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:205(0x2FA) */
static CommonBuffer GwBufferMember206 = { &GwIdRouter_funcList[0], GWData206, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX206,
		&GWHdr206, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:206(0x2FB) */
static CommonBuffer GwBufferMember207 = { &GwIdRouter_funcList[0], GWData207, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX207,
		&GWHdr207, L3R_PRTCL_BIT_CAN3, 32, 2000 }; /* GW-ID:207(0x2FD) */
static CommonBuffer GwBufferMember208 = { &GwIdRouter_funcList[0], GWData208, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX208,
		&GWHdr208, L3R_PRTCL_BIT_CAN3, 32, 2000 }; /* GW-ID:208(0x2FE) */
static CommonBuffer GwBufferMember209 = { &GwIdRouter_funcList[0], GWData209, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX209,
		&GWHdr209, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:209(0x305) */
static CommonBuffer GwBufferMember210 = { &GwIdRouter_funcList[0], GWData210, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX210,
		&GWHdr210, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:210(0x306) */
static CommonBuffer GwBufferMember211 = { &GwIdRouter_funcList[0], GWData211, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX211,
		&GWHdr211, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:211(0x30D) */
static CommonBuffer GwBufferMember212 = { &GwIdRouter_funcList[0], GWData212, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX212,
		&GWHdr212, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:212(0x30E) */
static CommonBuffer GwBufferMember213 = { &GwIdRouter_funcList[0], GWData213, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX213,
		&GWHdr213, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:213(0x30F) */
static CommonBuffer GwBufferMember214 = { &GwIdRouter_funcList[0], GWData214, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX214,
		&GWHdr214, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:214(0x312) */
static CommonBuffer GwBufferMember215 = { &GwIdRouter_funcList[0], GWData215, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX215,
		&GWHdr215, L3R_PRTCL_BIT_CAN0, 8, 0 }; /* GW-ID:215(0x313) */
static CommonBuffer GwBufferMember216 = { &GwIdRouter_funcList[0], GWData216, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX216,
		&GWHdr216, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:216(0x314) */
static CommonBuffer GwBufferMember217 = { &GwIdRouter_funcList[0], GWData217, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX217,
		&GWHdr217, L3R_PRTCL_BIT_CAN0, 8, 0 }; /* GW-ID:217(0x315) */
static CommonBuffer GwBufferMember218 = { &GwIdRouter_funcList[0], GWData218, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX218,
		&GWHdr218, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:218(0x317) */
static CommonBuffer GwBufferMember219 = { &GwIdRouter_funcList[0], GWData219, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX219,
		&GWHdr219, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:219(0x318) */
static CommonBuffer GwBufferMember220 = { &GwIdRouter_funcList[0], GWData220, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX220,
		&GWHdr220, L3R_PRTCL_BIT_CAN0, 8, 3000 }; /* GW-ID:220(0x31A) */
static CommonBuffer GwBufferMember221 = { &GwIdRouter_funcList[0], GWData221, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX221,
		&GWHdr221, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:221(0x31D) */
static CommonBuffer GwBufferMember222 = { &GwIdRouter_funcList[0], GWData222, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX222,
		&GWHdr222, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:222(0x320) */
static CommonBuffer GwBufferMember223 = { &GwIdRouter_funcList[0], GWData223, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX223,
		&GWHdr223, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:223(0x322) */
static CommonBuffer GwBufferMember224 = { &GwIdRouter_funcList[0], GWData224, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX224,
		&GWHdr224, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:224(0x325) */
static CommonBuffer GwBufferMember225 = { &GwIdRouter_funcList[0], GWData225, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX225,
		&GWHdr225, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:225(0x328) */
static CommonBuffer GwBufferMember226 = { &GwIdRouter_funcList[0], GWData226, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX226,
		&GWHdr226, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:226(0x32A) */
static CommonBuffer GwBufferMember227 = { &GwIdRouter_funcList[0], GWData227, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX227,
		&GWHdr227, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:227(0x32F) */
static CommonBuffer GwBufferMember228 = { &GwIdRouter_funcList[0], GWData228, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX228,
		&GWHdr228, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:228(0x333) */
static CommonBuffer GwBufferMember229 = { &GwIdRouter_funcList[0], GWData229, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX229,
		&GWHdr229, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:229(0x334) */
static CommonBuffer GwBufferMember230 = { &GwIdRouter_funcList[0], GWData230, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX230,
		&GWHdr230, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:230(0x335) */
static CommonBuffer GwBufferMember231 = { &GwIdRouter_funcList[0], GWData231, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX231,
		&GWHdr231, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:231(0x336) */
static CommonBuffer GwBufferMember232 = { &GwIdRouter_funcList[0], GWData232, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX232,
		&GWHdr232, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:232(0x337) */
static CommonBuffer GwBufferMember233 = { &GwIdRouter_funcList[0], GWData233, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX233,
		&GWHdr233, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:233(0x33A) */
static CommonBuffer GwBufferMember234 = { &GwIdRouter_funcList[0], GWData234, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX234,
		&GWHdr234, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:234(0x33F) */
static CommonBuffer GwBufferMember235 = { &GwIdRouter_funcList[0], GWData235, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX235,
		&GWHdr235, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:235(0x341) */
static CommonBuffer GwBufferMember236 = { &GwIdRouter_funcList[0], GWData236, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX236,
		&GWHdr236, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:236(0x345) */
static CommonBuffer GwBufferMember237 = { &GwIdRouter_funcList[0], GWData237, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX237,
		&GWHdr237, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:237(0x346) */
static CommonBuffer GwBufferMember238 = { &GwIdRouter_funcList[0], GWData238, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX238,
		&GWHdr238, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:238(0x347) */
static CommonBuffer GwBufferMember239 = { &GwIdRouter_funcList[0], GWData239, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX239,
		&GWHdr239, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:239(0x348) */
static CommonBuffer GwBufferMember240 = { &GwIdRouter_funcList[0], GWData240, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX240,
		&GWHdr240, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:240(0x349) */
static CommonBuffer GwBufferMember241 = { &GwIdRouter_funcList[0], GWData241, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX241,
		&GWHdr241, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:241(0x34C) */
static CommonBuffer GwBufferMember242 = { &GwIdRouter_funcList[0], GWData242, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX242,
		&GWHdr242, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:242(0x34D) */
static CommonBuffer GwBufferMember243 = { &GwIdRouter_funcList[0], GWData243, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX243,
		&GWHdr243, L3R_PRTCL_BIT_CAN2, 8, 20000 }; /* GW-ID:243(0x34E) */
static CommonBuffer GwBufferMember244 = { &GwIdRouter_funcList[0], GWData244, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX244,
		&GWHdr244, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:244(0x34F) */
static CommonBuffer GwBufferMember245 = { &GwIdRouter_funcList[0], GWData245, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX245,
		&GWHdr245, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:245(0x350) */
static CommonBuffer GwBufferMember246 = { &GwIdRouter_funcList[0], GWData246, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX246,
		&GWHdr246, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:246(0x351) */
static CommonBuffer GwBufferMember247 = { &GwIdRouter_funcList[0], GWData247, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX247,
		&GWHdr247, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:247(0x352) */
static CommonBuffer GwBufferMember248 = { &GwIdRouter_funcList[0], GWData248, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX248,
		&GWHdr248, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:248(0x353) */
static CommonBuffer GwBufferMember249 = { &GwIdRouter_funcList[0], GWData249, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX249,
		&GWHdr249, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:249(0x354) */
static CommonBuffer GwBufferMember250 = { &GwIdRouter_funcList[0], GWData250, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX250,
		&GWHdr250, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:250(0x355) */
static CommonBuffer GwBufferMember251 = { &GwIdRouter_funcList[0], GWData251, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX251,
		&GWHdr251, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:251(0x357) */
static CommonBuffer GwBufferMember252 = { &GwIdRouter_funcList[0], GWData252, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX252,
		&GWHdr252, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:252(0x358) */
static CommonBuffer GwBufferMember253 = { &GwIdRouter_funcList[0], GWData253, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX253,
		&GWHdr253, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:253(0x35A) */
static CommonBuffer GwBufferMember254 = { &GwIdRouter_funcList[0], GWData254, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX254,
		&GWHdr254, L3R_PRTCL_BIT_CAN0, 8, 20000 }; /* GW-ID:254(0x35B) */
static CommonBuffer GwBufferMember255 = { &GwIdRouter_funcList[0], GWData255, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX255,
		&GWHdr255, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:255(0x35D) */
static CommonBuffer GwBufferMember256 = { &GwIdRouter_funcList[0], GWData256, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX256,
		&GWHdr256, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:256(0x35F) */
static CommonBuffer GwBufferMember257 = { &GwIdRouter_funcList[0], GWData257, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX257,
		&GWHdr257, L3R_PRTCL_BIT_CAN3, 32, 0 }; /* GW-ID:257(0x363) */
static CommonBuffer GwBufferMember258 = { &GwIdRouter_funcList[0], GWData258, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX258,
		&GWHdr258, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:258(0x364) */
static CommonBuffer GwBufferMember259 = { &GwIdRouter_funcList[0], GWData259, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX259,
		&GWHdr259, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:259(0x367) */
static CommonBuffer GwBufferMember260 = { &GwIdRouter_funcList[0], GWData260, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX260,
		&GWHdr260, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:260(0x368) */
static CommonBuffer GwBufferMember261 = { &GwIdRouter_funcList[0], GWData261, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX261,
		&GWHdr261, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:261(0x36A) */
static CommonBuffer GwBufferMember262 = { &GwIdRouter_funcList[0], GWData262, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX262,
		&GWHdr262, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:262(0x36B) */
static CommonBuffer GwBufferMember263 = { &GwIdRouter_funcList[0], GWData263, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX263,
		&GWHdr263, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:263(0x36E) */
static CommonBuffer GwBufferMember264 = { &GwIdRouter_funcList[0], GWData264, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX264,
		&GWHdr264, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:264(0x36F) */
static CommonBuffer GwBufferMember265 = { &GwIdRouter_funcList[0], GWData265, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX265,
		&GWHdr265, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:265(0x375) */
static CommonBuffer GwBufferMember266 = { &GwIdRouter_funcList[0], GWData266, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX266,
		&GWHdr266, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:266(0x379) */
static CommonBuffer GwBufferMember267 = { &GwIdRouter_funcList[0], GWData267, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX267,
		&GWHdr267, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:267(0x37B) */
static CommonBuffer GwBufferMember268 = { &GwIdRouter_funcList[0], GWData268, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX268,
		&GWHdr268, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:268(0x37E) */
static CommonBuffer GwBufferMember269 = { &GwIdRouter_funcList[0], GWData269, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX269,
		&GWHdr269, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:269(0x37F) */
static CommonBuffer GwBufferMember270 = { &GwIdRouter_funcList[0], GWData270, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX270,
		&GWHdr270, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:270(0x380) */
static CommonBuffer GwBufferMember271 = { &GwIdRouter_funcList[0], GWData271, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX271,
		&GWHdr271, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:271(0x381) */
static CommonBuffer GwBufferMember272 = { &GwIdRouter_funcList[0], GWData272, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX272,
		&GWHdr272, L3R_PRTCL_BIT_CAN3, 8, 5000 }; /* GW-ID:272(0x382) */
static CommonBuffer GwBufferMember273 = { &GwIdRouter_funcList[0], GWData273, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX273,
		&GWHdr273, L3R_PRTCL_BIT_CAN0, 32, 3000 }; /* GW-ID:273(0x384) */
static CommonBuffer GwBufferMember274 = { &GwIdRouter_funcList[0], GWData274, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX274,
		&GWHdr274, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:274(0x385) */
static CommonBuffer GwBufferMember275 = { &GwIdRouter_funcList[0], GWData275, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX275,
		&GWHdr275, L3R_PRTCL_BIT_CAN2, 32, 3000 }; /* GW-ID:275(0x386) */
static CommonBuffer GwBufferMember276 = { &GwIdRouter_funcList[0], GWData276, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX276,
		&GWHdr276, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:276(0x387) */
static CommonBuffer GwBufferMember277 = { &GwIdRouter_funcList[0], GWData277, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX277,
		&GWHdr277, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:277(0x388) */
static CommonBuffer GwBufferMember278 = { &GwIdRouter_funcList[0], GWData278, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX278,
		&GWHdr278, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:278(0x389) */
static CommonBuffer GwBufferMember279 = { &GwIdRouter_funcList[0], GWData279, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX279,
		&GWHdr279, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:279(0x38A) */
static CommonBuffer GwBufferMember280 = { &GwIdRouter_funcList[0], GWData280, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX280,
		&GWHdr280, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:280(0x38B) */
static CommonBuffer GwBufferMember281 = { &GwIdRouter_funcList[0], GWData281, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX281,
		&GWHdr281, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:281(0x38D) */
static CommonBuffer GwBufferMember282 = { &GwIdRouter_funcList[0], GWData282, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX282,
		&GWHdr282, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:282(0x38E) */
static CommonBuffer GwBufferMember283 = { &GwIdRouter_funcList[0], GWData283, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX283,
		&GWHdr283, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:283(0x38F) */
static CommonBuffer GwBufferMember284 = { &GwIdRouter_funcList[0], GWData284, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX284,
		&GWHdr284, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:284(0x390) */
static CommonBuffer GwBufferMember285 = { &GwIdRouter_funcList[0], GWData285, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX285,
		&GWHdr285, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:285(0x393) */
static CommonBuffer GwBufferMember286 = { &GwIdRouter_funcList[0], GWData286, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX286,
		&GWHdr286, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:286(0x395) */
static CommonBuffer GwBufferMember287 = { &GwIdRouter_funcList[0], GWData287, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX287,
		&GWHdr287, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:287(0x396) */
static CommonBuffer GwBufferMember288 = { &GwIdRouter_funcList[0], GWData288, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX288,
		&GWHdr288, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:288(0x397) */
static CommonBuffer GwBufferMember289 = { &GwIdRouter_funcList[0], GWData289, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX289,
		&GWHdr289, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:289(0x398) */
static CommonBuffer GwBufferMember290 = { &GwIdRouter_funcList[0], GWData290, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX290,
		&GWHdr290, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:290(0x39A) */
static CommonBuffer GwBufferMember291 = { &GwIdRouter_funcList[0], GWData291, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX291,
		&GWHdr291, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:291(0x39B) */
static CommonBuffer GwBufferMember292 = { &GwIdRouter_funcList[0], GWData292, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX292,
		&GWHdr292, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:292(0x39C) */
static CommonBuffer GwBufferMember293 = { &GwIdRouter_funcList[0], GWData293, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX293,
		&GWHdr293, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:293(0x39D) */
static CommonBuffer GwBufferMember294 = { &GwIdRouter_funcList[0], GWData294, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX294,
		&GWHdr294, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:294(0x39E) */
static CommonBuffer GwBufferMember295 = { &GwIdRouter_funcList[0], GWData295, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX295,
		&GWHdr295, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:295(0x39F) */
static CommonBuffer GwBufferMember296 = { &GwIdRouter_funcList[0], GWData296, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX296,
		&GWHdr296, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:296(0x3A1) */
static CommonBuffer GwBufferMember297 = { &GwIdRouter_funcList[0], GWData297, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX297,
		&GWHdr297, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:297(0x3A5) */
static CommonBuffer GwBufferMember298 = { &GwIdRouter_funcList[0], GWData298, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX298,
		&GWHdr298, L3R_PRTCL_BIT_CAN2, 8, 3000 }; /* GW-ID:298(0x3A6) */
static CommonBuffer GwBufferMember299 = { &GwIdRouter_funcList[0], GWData299, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX299,
		&GWHdr299, L3R_PRTCL_BIT_CAN2, 8, 3000 }; /* GW-ID:299(0x3A7) */
static CommonBuffer GwBufferMember300 = { &GwIdRouter_funcList[0], GWData300, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX300,
		&GWHdr300, L3R_PRTCL_BIT_CAN2, 8, 3000 }; /* GW-ID:300(0x3A8) */
static CommonBuffer GwBufferMember301 = { &GwIdRouter_funcList[0], GWData301, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX301,
		&GWHdr301, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:301(0x3A9) */
static CommonBuffer GwBufferMember302 = { &GwIdRouter_funcList[0], GWData302, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX302,
		&GWHdr302, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:302(0x3AB) */
static CommonBuffer GwBufferMember303 = { &GwIdRouter_funcList[0], GWData303, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX303,
		&GWHdr303, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:303(0x3AC) */
static CommonBuffer GwBufferMember304 = { &GwIdRouter_funcList[0], GWData304, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX304,
		&GWHdr304, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:304(0x3AE) */
static CommonBuffer GwBufferMember305 = { &GwIdRouter_funcList[0], GWData305, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX305,
		&GWHdr305, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:305(0x3AF) */
static CommonBuffer GwBufferMember306 = { &GwIdRouter_funcList[0], GWData306, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX306,
		&GWHdr306, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:306(0x3B0) */
static CommonBuffer GwBufferMember307 = { &GwIdRouter_funcList[0], GWData307, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX307,
		&GWHdr307, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:307(0x3B1) */
static CommonBuffer GwBufferMember308 = { &GwIdRouter_funcList[0], GWData308, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX308,
		&GWHdr308, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:308(0x3B2) */
static CommonBuffer GwBufferMember309 = { &GwIdRouter_funcList[0], GWData309, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX309,
		&GWHdr309, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:309(0x3B3) */
static CommonBuffer GwBufferMember310 = { &GwIdRouter_funcList[0], GWData310, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX310,
		&GWHdr310, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:310(0x3B5) */
static CommonBuffer GwBufferMember311 = { &GwIdRouter_funcList[0], GWData311, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX311,
		&GWHdr311, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:311(0x3B6) */
static CommonBuffer GwBufferMember312 = { &GwIdRouter_funcList[0], GWData312, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX312,
		&GWHdr312, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:312(0x3B8) */
static CommonBuffer GwBufferMember313 = { &GwIdRouter_funcList[0], GWData313, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX313,
		&GWHdr313, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:313(0x3B9) */
static CommonBuffer GwBufferMember314 = { &GwIdRouter_funcList[0], GWData314, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX314,
		&GWHdr314, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:314(0x3BB) */
static CommonBuffer GwBufferMember315 = { &GwIdRouter_funcList[0], GWData315, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX315,
		&GWHdr315, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:315(0x3BC) */
static CommonBuffer GwBufferMember316 = { &GwIdRouter_funcList[0], GWData316, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX316,
		&GWHdr316, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:316(0x3BD) */
static CommonBuffer GwBufferMember317 = { &GwIdRouter_funcList[0], GWData317, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX317,
		&GWHdr317, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:317(0x3BE) */
static CommonBuffer GwBufferMember318 = { &GwIdRouter_funcList[0], GWData318, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX318,
		&GWHdr318, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:318(0x3BF) */
static CommonBuffer GwBufferMember319 = { &GwIdRouter_funcList[0], GWData319, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX319,
		&GWHdr319, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:319(0x3C0) */
static CommonBuffer GwBufferMember320 = { &GwIdRouter_funcList[0], GWData320, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX320,
		&GWHdr320, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:320(0x3C2) */
static CommonBuffer GwBufferMember321 = { &GwIdRouter_funcList[0], GWData321, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX321,
		&GWHdr321, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:321(0x3C4) */
static CommonBuffer GwBufferMember322 = { &GwIdRouter_funcList[0], GWData322, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX322,
		&GWHdr322, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:322(0x3C6) */
static CommonBuffer GwBufferMember323 = { &GwIdRouter_funcList[0], GWData323, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX323,
		&GWHdr323, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:323(0x3C7) */
static CommonBuffer GwBufferMember324 = { &GwIdRouter_funcList[0], GWData324, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX324,
		&GWHdr324, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:324(0x3C8) */
static CommonBuffer GwBufferMember325 = { &GwIdRouter_funcList[0], GWData325, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX325,
		&GWHdr325, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:325(0x3C9) */
static CommonBuffer GwBufferMember326 = { &GwIdRouter_funcList[0], GWData326, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX326,
		&GWHdr326, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:326(0x3CA) */
static CommonBuffer GwBufferMember327 = { &GwIdRouter_funcList[0], GWData327, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX327,
		&GWHdr327, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:327(0x3CB) */
static CommonBuffer GwBufferMember328 = { &GwIdRouter_funcList[0], GWData328, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX328,
		&GWHdr328, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:328(0x3CD) */
static CommonBuffer GwBufferMember329 = { &GwIdRouter_funcList[0], GWData329, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX329,
		&GWHdr329, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:329(0x3D0) */
static CommonBuffer GwBufferMember330 = { &GwIdRouter_funcList[0], GWData330, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX330,
		&GWHdr330, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:330(0x3D2) */
static CommonBuffer GwBufferMember331 = { &GwIdRouter_funcList[0], GWData331, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX331,
		&GWHdr331, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:331(0x3D3) */
static CommonBuffer GwBufferMember332 = { &GwIdRouter_funcList[0], GWData332, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX332,
		&GWHdr332, L3R_PRTCL_BIT_CAN3, 32, 3000 }; /* GW-ID:332(0x3D4) */
static CommonBuffer GwBufferMember333 = { &GwIdRouter_funcList[0], GWData333, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX333,
		&GWHdr333, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:333(0x3D6) */
static CommonBuffer GwBufferMember334 = { &GwIdRouter_funcList[0], GWData334, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX334,
		&GWHdr334, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:334(0x3D9) */
static CommonBuffer GwBufferMember335 = { &GwIdRouter_funcList[0], GWData335, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX335,
		&GWHdr335, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:335(0x3DB) */
static CommonBuffer GwBufferMember336 = { &GwIdRouter_funcList[0], GWData336, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX336,
		&GWHdr336, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:336(0x3DC) */
static CommonBuffer GwBufferMember337 = { &GwIdRouter_funcList[0], GWData337, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX337,
		&GWHdr337, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:337(0x3DD) */
static CommonBuffer GwBufferMember338 = { &GwIdRouter_funcList[0], GWData338, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX338,
		&GWHdr338, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:338(0x3DE) */
static CommonBuffer GwBufferMember339 = { &GwIdRouter_funcList[0], GWData339, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX339,
		&GWHdr339, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:339(0x3E1) */
static CommonBuffer GwBufferMember340 = { &GwIdRouter_funcList[0], GWData340, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX340,
		&GWHdr340, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:340(0x3E4) */
static CommonBuffer GwBufferMember341 = { &GwIdRouter_funcList[0], GWData341, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX341,
		&GWHdr341, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:341(0x3E5) */
static CommonBuffer GwBufferMember342 = { &GwIdRouter_funcList[0], GWData342, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX342,
		&GWHdr342, L3R_PRTCL_BIT_CAN0, 32, 3000 }; /* GW-ID:342(0x3E6) */
static CommonBuffer GwBufferMember343 = { &GwIdRouter_funcList[0], GWData343, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX343,
		&GWHdr343, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:343(0x3E7) */
static CommonBuffer GwBufferMember344 = { &GwIdRouter_funcList[0], GWData344, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX344,
		&GWHdr344, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:344(0x3EA) */
static CommonBuffer GwBufferMember345 = { &GwIdRouter_funcList[0], GWData345, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX345,
		&GWHdr345, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:345(0x3EB) */
static CommonBuffer GwBufferMember346 = { &GwIdRouter_funcList[0], GWData346, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX346,
		&GWHdr346, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:346(0x3EC) */
static CommonBuffer GwBufferMember347 = { &GwIdRouter_funcList[0], GWData347, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX347,
		&GWHdr347, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:347(0x3EE) */
static CommonBuffer GwBufferMember348 = { &GwIdRouter_funcList[0], GWData348, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX348,
		&GWHdr348, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:348(0x3EF) */
static CommonBuffer GwBufferMember349 = { &GwIdRouter_funcList[0], GWData349, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX349,
		&GWHdr349, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:349(0x3F0) */
static CommonBuffer GwBufferMember350 = { &GwIdRouter_funcList[0], GWData350, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX350,
		&GWHdr350, L3R_PRTCL_BIT_CAN2, 64, 0 }; /* GW-ID:350(0x3F1) */
static CommonBuffer GwBufferMember351 = { &GwIdRouter_funcList[0], GWData351, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX351,
		&GWHdr351, L3R_PRTCL_BIT_CAN2, 8, 20000 }; /* GW-ID:351(0x3F2) */
static CommonBuffer GwBufferMember352 = { &GwIdRouter_funcList[0], GWData352, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX352,
		&GWHdr352, L3R_PRTCL_BIT_CAN3, 8, 1008 }; /* GW-ID:352(0x3F3) */
static CommonBuffer GwBufferMember353 = { &GwIdRouter_funcList[0], GWData353, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX353,
		&GWHdr353, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:353(0x3F5) */
static CommonBuffer GwBufferMember354 = { &GwIdRouter_funcList[0], GWData354, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX354,
		&GWHdr354, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:354(0x3F6) */
static CommonBuffer GwBufferMember355 = { &GwIdRouter_funcList[0], GWData355, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX355,
		&GWHdr355, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:355(0x3F7) */
static CommonBuffer GwBufferMember356 = { &GwIdRouter_funcList[0], GWData356, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX356,
		&GWHdr356, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:356(0x3F9) */
static CommonBuffer GwBufferMember357 = { &GwIdRouter_funcList[0], GWData357, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX357,
		&GWHdr357, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:357(0x3FB) */
static CommonBuffer GwBufferMember358 = { &GwIdRouter_funcList[0], GWData358, L3R_FRAMECLASS_CTRL_1, L3R_DATAMAX358,
		&GWHdr358, L3R_PRTCL_BIT_CAN3, 8, 50 }; /* GW-ID:358(0x3FC) */
static CommonBuffer GwBufferMember359 = { &GwIdRouter_funcList[0], GWData359, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX359,
		&GWHdr359, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:359(0x3FD) */
static CommonBuffer GwBufferMember360 = { &GwIdRouter_funcList[0], GWData360, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX360,
		&GWHdr360, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:360(0x400) */
static CommonBuffer GwBufferMember361 = { &GwIdRouter_funcList[0], GWData361, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX361,
		&GWHdr361, L3R_PRTCL_BIT_CAN3, 8, 1024 }; /* GW-ID:361(0x401) */
static CommonBuffer GwBufferMember362 = { &GwIdRouter_funcList[0], GWData362, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX362,
		&GWHdr362, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:362(0x403) */
static CommonBuffer GwBufferMember363 = { &GwIdRouter_funcList[0], GWData363, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX363,
		&GWHdr363, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:363(0x404) */
static CommonBuffer GwBufferMember364 = { &GwIdRouter_funcList[0], GWData364, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX364,
		&GWHdr364, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:364(0x405) */
static CommonBuffer GwBufferMember365 = { &GwIdRouter_funcList[0], GWData365, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX365,
		&GWHdr365, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:365(0x407) */
static CommonBuffer GwBufferMember366 = { &GwIdRouter_funcList[0], GWData366, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX366,
		&GWHdr366, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:366(0x408) */
static CommonBuffer GwBufferMember367 = { &GwIdRouter_funcList[0], GWData367, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX367,
		&GWHdr367, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:367(0x40B) */
static CommonBuffer GwBufferMember368 = { &GwIdRouter_funcList[0], GWData368, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX368,
		&GWHdr368, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:368(0x40C) */
static CommonBuffer GwBufferMember369 = { &GwIdRouter_funcList[0], GWData369, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX369,
		&GWHdr369, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:369(0x40D) */
static CommonBuffer GwBufferMember370 = { &GwIdRouter_funcList[0], GWData370, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX370,
		&GWHdr370, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:370(0x40E) */
static CommonBuffer GwBufferMember371 = { &GwIdRouter_funcList[0], GWData371, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX371,
		&GWHdr371, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:371(0x411) */
static CommonBuffer GwBufferMember372 = { &GwIdRouter_funcList[0], GWData372, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX372,
		&GWHdr372, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:372(0x412) */
static CommonBuffer GwBufferMember373 = { &GwIdRouter_funcList[0], GWData373, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX373,
		&GWHdr373, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:373(0x417) */
static CommonBuffer GwBufferMember374 = { &GwIdRouter_funcList[0], GWData374, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX374,
		&GWHdr374, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:374(0x418) */
static CommonBuffer GwBufferMember375 = { &GwIdRouter_funcList[0], GWData375, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX375,
		&GWHdr375, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:375(0x41A) */
static CommonBuffer GwBufferMember376 = { &GwIdRouter_funcList[0], GWData376, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX376,
		&GWHdr376, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:376(0x421) */
static CommonBuffer GwBufferMember377 = { &GwIdRouter_funcList[0], GWData377, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX377,
		&GWHdr377, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:377(0x422) */
static CommonBuffer GwBufferMember378 = { &GwIdRouter_funcList[0], GWData378, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX378,
		&GWHdr378, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:378(0x423) */
static CommonBuffer GwBufferMember379 = { &GwIdRouter_funcList[0], GWData379, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX379,
		&GWHdr379, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:379(0x426) */
static CommonBuffer GwBufferMember380 = { &GwIdRouter_funcList[0], GWData380, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX380,
		&GWHdr380, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:380(0x427) */
static CommonBuffer GwBufferMember381 = { &GwIdRouter_funcList[0], GWData381, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX381,
		&GWHdr381, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:381(0x428) */
static CommonBuffer GwBufferMember382 = { &GwIdRouter_funcList[0], GWData382, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX382,
		&GWHdr382, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:382(0x429) */
static CommonBuffer GwBufferMember383 = { &GwIdRouter_funcList[0], GWData383, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX383,
		&GWHdr383, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:383(0x42A) */
static CommonBuffer GwBufferMember384 = { &GwIdRouter_funcList[0], GWData384, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX384,
		&GWHdr384, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:384(0x42B) */
static CommonBuffer GwBufferMember385 = { &GwIdRouter_funcList[0], GWData385, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX385,
		&GWHdr385, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:385(0x42C) */
static CommonBuffer GwBufferMember386 = { &GwIdRouter_funcList[0], GWData386, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX386,
		&GWHdr386, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:386(0x42E) */
static CommonBuffer GwBufferMember387 = { &GwIdRouter_funcList[0], GWData387, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX387,
		&GWHdr387, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:387(0x42F) */
static CommonBuffer GwBufferMember388 = { &GwIdRouter_funcList[0], GWData388, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX388,
		&GWHdr388, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:388(0x430) */
static CommonBuffer GwBufferMember389 = { &GwIdRouter_funcList[0], GWData389, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX389,
		&GWHdr389, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:389(0x432) */
static CommonBuffer GwBufferMember390 = { &GwIdRouter_funcList[0], GWData390, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX390,
		&GWHdr390, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:390(0x434) */
static CommonBuffer GwBufferMember391 = { &GwIdRouter_funcList[0], GWData391, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX391,
		&GWHdr391, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:391(0x435) */
static CommonBuffer GwBufferMember392 = { &GwIdRouter_funcList[0], GWData392, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX392,
		&GWHdr392, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:392(0x436) */
static CommonBuffer GwBufferMember393 = { &GwIdRouter_funcList[0], GWData393, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX393,
		&GWHdr393, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:393(0x437) */
static CommonBuffer GwBufferMember394 = { &GwIdRouter_funcList[0], GWData394, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX394,
		&GWHdr394, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:394(0x438) */
static CommonBuffer GwBufferMember395 = { &GwIdRouter_funcList[0], GWData395, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX395,
		&GWHdr395, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:395(0x439) */
static CommonBuffer GwBufferMember396 = { &GwIdRouter_funcList[0], GWData396, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX396,
		&GWHdr396, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:396(0x43A) */
static CommonBuffer GwBufferMember397 = { &GwIdRouter_funcList[0], GWData397, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX397,
		&GWHdr397, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:397(0x43B) */
static CommonBuffer GwBufferMember398 = { &GwIdRouter_funcList[0], GWData398, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX398,
		&GWHdr398, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:398(0x43E) */
static CommonBuffer GwBufferMember399 = { &GwIdRouter_funcList[0], GWData399, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX399,
		&GWHdr399, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:399(0x442) */
static CommonBuffer GwBufferMember400 = { &GwIdRouter_funcList[0], GWData400, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX400,
		&GWHdr400, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:400(0x480) */
static CommonBuffer GwBufferMember401 = { &GwIdRouter_funcList[0], GWData401, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX401,
		&GWHdr401, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:401(0x484) */
static CommonBuffer GwBufferMember402 = { &GwIdRouter_funcList[0], GWData402, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX402,
		&GWHdr402, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:402(0x489) */
static CommonBuffer GwBufferMember403 = { &GwIdRouter_funcList[0], GWData403, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX403,
		&GWHdr403, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:403(0x48B) */
static CommonBuffer GwBufferMember404 = { &GwIdRouter_funcList[0], GWData404, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX404,
		&GWHdr404, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:404(0x490) */
static CommonBuffer GwBufferMember405 = { &GwIdRouter_funcList[0], GWData405, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX405,
		&GWHdr405, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:405(0x491) */
static CommonBuffer GwBufferMember406 = { &GwIdRouter_funcList[0], GWData406, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX406,
		&GWHdr406, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:406(0x494) */
static CommonBuffer GwBufferMember407 = { &GwIdRouter_funcList[0], GWData407, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX407,
		&GWHdr407, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:407(0x495) */
static CommonBuffer GwBufferMember408 = { &GwIdRouter_funcList[0], GWData408, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX408,
		&GWHdr408, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:408(0x496) */
static CommonBuffer GwBufferMember409 = { &GwIdRouter_funcList[0], GWData409, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX409,
		&GWHdr409, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:409(0x497) */
static CommonBuffer GwBufferMember410 = { &GwIdRouter_funcList[0], GWData410, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX410,
		&GWHdr410, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:410(0x499) */
static CommonBuffer GwBufferMember411 = { &GwIdRouter_funcList[0], GWData411, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX411,
		&GWHdr411, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:411(0x49A) */
static CommonBuffer GwBufferMember412 = { &GwIdRouter_funcList[0], GWData412, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX412,
		&GWHdr412, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:412(0x49B) */
static CommonBuffer GwBufferMember413 = { &GwIdRouter_funcList[0], GWData413, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX413,
		&GWHdr413, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:413(0x49D) */
static CommonBuffer GwBufferMember414 = { &GwIdRouter_funcList[0], GWData414, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX414,
		&GWHdr414, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:414(0x4A0) */
static CommonBuffer GwBufferMember415 = { &GwIdRouter_funcList[0], GWData415, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX415,
		&GWHdr415, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:415(0x4A1) */
static CommonBuffer GwBufferMember416 = { &GwIdRouter_funcList[0], GWData416, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX416,
		&GWHdr416, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:416(0x4A3) */
static CommonBuffer GwBufferMember417 = { &GwIdRouter_funcList[0], GWData417, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX417,
		&GWHdr417, L3R_PRTCL_BIT_CAN3, 32, 500 }; /* GW-ID:417(0x4A4) */
static CommonBuffer GwBufferMember418 = { &GwIdRouter_funcList[0], GWData418, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX418,
		&GWHdr418, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:418(0x4A8) */
static CommonBuffer GwBufferMember419 = { &GwIdRouter_funcList[0], GWData419, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX419,
		&GWHdr419, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:419(0x4AC) */
static CommonBuffer GwBufferMember420 = { &GwIdRouter_funcList[0], GWData420, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX420,
		&GWHdr420, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:420(0x4AE) */
static CommonBuffer GwBufferMember421 = { &GwIdRouter_funcList[0], GWData421, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX421,
		&GWHdr421, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:421(0x4AF) */
static CommonBuffer GwBufferMember422 = { &GwIdRouter_funcList[0], GWData422, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX422,
		&GWHdr422, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:422(0x4B8) */
static CommonBuffer GwBufferMember423 = { &GwIdRouter_funcList[0], GWData423, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX423,
		&GWHdr423, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:423(0x4BC) */
static CommonBuffer GwBufferMember424 = { &GwIdRouter_funcList[0], GWData424, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX424,
		&GWHdr424, L3R_PRTCL_BIT_CAN3, 32, 2000 }; /* GW-ID:424(0x500) */
static CommonBuffer GwBufferMember425 = { &GwIdRouter_funcList[0], GWData425, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX425,
		&GWHdr425, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:425(0x506) */
static CommonBuffer GwBufferMember426 = { &GwIdRouter_funcList[0], GWData426, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX426,
		&GWHdr426, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:426(0x507) */
static CommonBuffer GwBufferMember427 = { &GwIdRouter_funcList[0], GWData427, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX427,
		&GWHdr427, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:427(0x515) */
static CommonBuffer GwBufferMember428 = { &GwIdRouter_funcList[0], GWData428, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX428,
		&GWHdr428, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:428(0x51A) */
static CommonBuffer GwBufferMember429 = { &GwIdRouter_funcList[0], GWData429, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX429,
		&GWHdr429, L3R_PRTCL_BIT_CAN2, 32, 1000 }; /* GW-ID:429(0x51B) */
static CommonBuffer GwBufferMember430 = { &GwIdRouter_funcList[0], GWData430, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX430,
		&GWHdr430, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:430(0x51D) */
static CommonBuffer GwBufferMember431 = { &GwIdRouter_funcList[0], GWData431, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX431,
		&GWHdr431, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:431(0x51E) */
static CommonBuffer GwBufferMember432 = { &GwIdRouter_funcList[0], GWData432, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX432,
		&GWHdr432, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:432(0x51F) */
static CommonBuffer GwBufferMember433 = { &GwIdRouter_funcList[0], GWData433, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX433,
		&GWHdr433, L3R_PRTCL_BIT_CAN0, 8, 3000 }; /* GW-ID:433(0x521) */
static CommonBuffer GwBufferMember434 = { &GwIdRouter_funcList[0], GWData434, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX434,
		&GWHdr434, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:434(0x524) */
static CommonBuffer GwBufferMember435 = { &GwIdRouter_funcList[0], GWData435, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX435,
		&GWHdr435, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:435(0x526) */
static CommonBuffer GwBufferMember436 = { &GwIdRouter_funcList[0], GWData436, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX436,
		&GWHdr436, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:436(0x527) */
static CommonBuffer GwBufferMember437 = { &GwIdRouter_funcList[0], GWData437, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX437,
		&GWHdr437, L3R_PRTCL_BIT_CAN3, 8, 0 }; /* GW-ID:437(0x528) */
static CommonBuffer GwBufferMember438 = { &GwIdRouter_funcList[0], GWData438, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX438,
		&GWHdr438, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:438(0x529) */
static CommonBuffer GwBufferMember439 = { &GwIdRouter_funcList[0], GWData439, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX439,
		&GWHdr439, L3R_PRTCL_BIT_CAN0, 8, 10000 }; /* GW-ID:439(0x52A) */
static CommonBuffer GwBufferMember440 = { &GwIdRouter_funcList[0], GWData440, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX440,
		&GWHdr440, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:440(0x52B) */
static CommonBuffer GwBufferMember441 = { &GwIdRouter_funcList[0], GWData441, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX441,
		&GWHdr441, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:441(0x52C) */
static CommonBuffer GwBufferMember442 = { &GwIdRouter_funcList[0], GWData442, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX442,
		&GWHdr442, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:442(0x530) */
static CommonBuffer GwBufferMember443 = { &GwIdRouter_funcList[0], GWData443, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX443,
		&GWHdr443, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:443(0x531) */
static CommonBuffer GwBufferMember444 = { &GwIdRouter_funcList[0], GWData444, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX444,
		&GWHdr444, L3R_PRTCL_BIT_CAN3, 8, 0 }; /* GW-ID:444(0x532) */
static CommonBuffer GwBufferMember445 = { &GwIdRouter_funcList[0], GWData445, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX445,
		&GWHdr445, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:445(0x534) */
static CommonBuffer GwBufferMember446 = { &GwIdRouter_funcList[0], GWData446, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX446,
		&GWHdr446, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:446(0x535) */
static CommonBuffer GwBufferMember447 = { &GwIdRouter_funcList[0], GWData447, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX447,
		&GWHdr447, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:447(0x537) */
static CommonBuffer GwBufferMember448 = { &GwIdRouter_funcList[0], GWData448, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX448,
		&GWHdr448, L3R_PRTCL_BIT_CAN3, 64, 1000 }; /* GW-ID:448(0x538) */
static CommonBuffer GwBufferMember449 = { &GwIdRouter_funcList[0], GWData449, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX449,
		&GWHdr449, L3R_PRTCL_BIT_CAN2, 8, 1000 }; /* GW-ID:449(0x56D) */
static CommonBuffer GwBufferMember450 = { &GwIdRouter_funcList[0], GWData450, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX450,
		&GWHdr450, L3R_PRTCL_BIT_CAN3, 8, 1500 }; /* GW-ID:450(0x583) */
static CommonBuffer GwBufferMember451 = { &GwIdRouter_funcList[0], GWData451, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX451,
		&GWHdr451, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:451(0x589) */
static CommonBuffer GwBufferMember452 = { &GwIdRouter_funcList[0], GWData452, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX452,
		&GWHdr452, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:452(0x58A) */
static CommonBuffer GwBufferMember453 = { &GwIdRouter_funcList[0], GWData453, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX453,
		&GWHdr453, L3R_PRTCL_BIT_CAN0, 8, 0 }; /* GW-ID:453(0x58D) */
static CommonBuffer GwBufferMember454 = { &GwIdRouter_funcList[0], GWData454, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX454,
		&GWHdr454, L3R_PRTCL_BIT_CAN3, 32, 1500 }; /* GW-ID:454(0x592) */
static CommonBuffer GwBufferMember455 = { &GwIdRouter_funcList[0], GWData455, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX455,
		&GWHdr455, L3R_PRTCL_BIT_CAN3, 32, 5000 }; /* GW-ID:455(0x594) */
static CommonBuffer GwBufferMember456 = { &GwIdRouter_funcList[0], GWData456, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX456,
		&GWHdr456, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:456(0x596) */
static CommonBuffer GwBufferMember457 = { &GwIdRouter_funcList[0], GWData457, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX457,
		&GWHdr457, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:457(0x5F1) */
static CommonBuffer GwBufferMember458 = { &GwIdRouter_funcList[0], GWData458, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX458,
		&GWHdr458, L3R_PRTCL_BIT_CAN3, 8, 100 }; /* GW-ID:458(0x5F3) */
static CommonBuffer GwBufferMember459 = { &GwIdRouter_funcList[0], GWData459, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX459,
		&GWHdr459, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:459(0x5F4) */
static CommonBuffer GwBufferMember460 = { &GwIdRouter_funcList[0], GWData460, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX460,
		&GWHdr460, L3R_PRTCL_BIT_CAN3, 8, 500 }; /* GW-ID:460(0x5F6) */
static CommonBuffer GwBufferMember461 = { &GwIdRouter_funcList[0], GWData461, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX461,
		&GWHdr461, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:461(0x601) */
static CommonBuffer GwBufferMember462 = { &GwIdRouter_funcList[0], GWData462, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX462,
		&GWHdr462, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:462(0x602) */
static CommonBuffer GwBufferMember463 = { &GwIdRouter_funcList[0], GWData463, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX463,
		&GWHdr463, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:463(0x608) */
static CommonBuffer GwBufferMember464 = { &GwIdRouter_funcList[0], GWData464, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX464,
		&GWHdr464, L3R_PRTCL_BIT_CAN0, 32, 1000 }; /* GW-ID:464(0x60C) */
static CommonBuffer GwBufferMember465 = { &GwIdRouter_funcList[0], GWData465, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX465,
		&GWHdr465, L3R_PRTCL_BIT_CAN3, 32, 1000 }; /* GW-ID:465(0x610) */
static CommonBuffer GwBufferMember466 = { &GwIdRouter_funcList[0], GWData466, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX466,
		&GWHdr466, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:466(0x611) */
static CommonBuffer GwBufferMember467 = { &GwIdRouter_funcList[0], GWData467, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX467,
		&GWHdr467, L3R_PRTCL_BIT_CAN3, 32, 0 }; /* GW-ID:467(0x613) */
static CommonBuffer GwBufferMember468 = { &GwIdRouter_funcList[0], GWData468, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX468,
		&GWHdr468, L3R_PRTCL_BIT_CAN0, 8, 1000 }; /* GW-ID:468(0x614) */
static CommonBuffer GwBufferMember469 = { &GwIdRouter_funcList[0], GWData469, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX469,
		&GWHdr469, L3R_PRTCL_BIT_CAN0, 8, 10000 }; /* GW-ID:469(0x615) */
static CommonBuffer GwBufferMember470 = { &GwIdRouter_funcList[0], GWData470, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX470,
		&GWHdr470, L3R_PRTCL_BIT_CAN0, 8, 10000 }; /* GW-ID:470(0x618) */
static CommonBuffer GwBufferMember471 = { &GwIdRouter_funcList[0], GWData471, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX471,
		&GWHdr471, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:471(0x621) */
static CommonBuffer GwBufferMember472 = { &GwIdRouter_funcList[0], GWData472, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX472,
		&GWHdr472, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:472(0x622) */
static CommonBuffer GwBufferMember473 = { &GwIdRouter_funcList[0], GWData473, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX473,
		&GWHdr473, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:473(0x623) */
static CommonBuffer GwBufferMember474 = { &GwIdRouter_funcList[0], GWData474, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX474,
		&GWHdr474, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:474(0x624) */
static CommonBuffer GwBufferMember475 = { &GwIdRouter_funcList[0], GWData475, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX475,
		&GWHdr475, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:475(0x626) */
static CommonBuffer GwBufferMember476 = { &GwIdRouter_funcList[0], GWData476, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX476,
		&GWHdr476, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:476(0x629) */
static CommonBuffer GwBufferMember477 = { &GwIdRouter_funcList[0], GWData477, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX477,
		&GWHdr477, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:477(0x62A) */
static CommonBuffer GwBufferMember478 = { &GwIdRouter_funcList[0], GWData478, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX478,
		&GWHdr478, L3R_PRTCL_BIT_CAN3, 8, 0 }; /* GW-ID:478(0x62C) */
static CommonBuffer GwBufferMember479 = { &GwIdRouter_funcList[0], GWData479, L3R_FRAMECLASS_CTRL_2, L3R_DATAMAX479,
		&GWHdr479, L3R_PRTCL_BIT_CAN3, 8, 1000 }; /* GW-ID:479(0x633) */

/* GWバッファ */
CommonBuffer *const gwIdRouterBuffer[L3R_GWID_FRMNUM] = {
	&GwBufferMember000, /* GW-ID:000	0x000 */
	&GwBufferMember001, /* GW-ID:001	0x013 */
	&GwBufferMember002, /* GW-ID:002	0x01B */
	&GwBufferMember003, /* GW-ID:003	0x049 */
	&GwBufferMember004, /* GW-ID:004	0x062 */
	&GwBufferMember005, /* GW-ID:005	0x069 */
	&GwBufferMember006, /* GW-ID:006	0x06A */
	&GwBufferMember007, /* GW-ID:007	0x072 */
	&GwBufferMember008, /* GW-ID:008	0x075 */
	&GwBufferMember009, /* GW-ID:009	0x07E */
	&GwBufferMember010, /* GW-ID:010	0x086 */
	&GwBufferMember011, /* GW-ID:011	0x09E */
	&GwBufferMember012, /* GW-ID:012	0x0A0 */
	&GwBufferMember013, /* GW-ID:013	0x0A1 */
	&GwBufferMember014, /* GW-ID:014	0x0A3 */
	&GwBufferMember015, /* GW-ID:015	0x0A4 */
	&GwBufferMember016, /* GW-ID:016	0x0A5 */
	&GwBufferMember017, /* GW-ID:017	0x0A6 */
	&GwBufferMember018, /* GW-ID:018	0x0A8 */
	&GwBufferMember019, /* GW-ID:019	0x0A9 */
	&GwBufferMember020, /* GW-ID:020	0x0B7 */
	&GwBufferMember021, /* GW-ID:021	0x0B8 */
	&GwBufferMember022, /* GW-ID:022	0x0F3 */
	&GwBufferMember023, /* GW-ID:023	0x0FC */
	&GwBufferMember024, /* GW-ID:024	0x100 */
	&GwBufferMember025, /* GW-ID:025	0x10B */
	&GwBufferMember026, /* GW-ID:026	0x115 */
	&GwBufferMember027, /* GW-ID:027	0x121 */
	&GwBufferMember028, /* GW-ID:028	0x122 */
	&GwBufferMember029, /* GW-ID:029	0x124 */
	&GwBufferMember030, /* GW-ID:030	0x126 */
	&GwBufferMember031, /* GW-ID:031	0x128 */
	&GwBufferMember032, /* GW-ID:032	0x12B */
	&GwBufferMember033, /* GW-ID:033	0x140 */
	&GwBufferMember034, /* GW-ID:034	0x141 */
	&GwBufferMember035, /* GW-ID:035	0x143 */
	&GwBufferMember036, /* GW-ID:036	0x144 */
	&GwBufferMember037, /* GW-ID:037	0x148 */
	&GwBufferMember038, /* GW-ID:038	0x14B */
	&GwBufferMember039, /* GW-ID:039	0x14C */
	&GwBufferMember040, /* GW-ID:040	0x14D */
	&GwBufferMember041, /* GW-ID:041	0x14F */
	&GwBufferMember042, /* GW-ID:042	0x150 */
	&GwBufferMember043, /* GW-ID:043	0x155 */
	&GwBufferMember044, /* GW-ID:044	0x159 */
	&GwBufferMember045, /* GW-ID:045	0x15A */
	&GwBufferMember046, /* GW-ID:046	0x161 */
	&GwBufferMember047, /* GW-ID:047	0x162 */
	&GwBufferMember048, /* GW-ID:048	0x163 */
	&GwBufferMember049, /* GW-ID:049	0x166 */
	&GwBufferMember050, /* GW-ID:050	0x167 */
	&GwBufferMember051, /* GW-ID:051	0x168 */
	&GwBufferMember052, /* GW-ID:052	0x169 */
	&GwBufferMember053, /* GW-ID:053	0x16A */
	&GwBufferMember054, /* GW-ID:054	0x16B */
	&GwBufferMember055, /* GW-ID:055	0x16C */
	&GwBufferMember056, /* GW-ID:056	0x16D */
	&GwBufferMember057, /* GW-ID:057	0x16E */
	&GwBufferMember058, /* GW-ID:058	0x17E */
	&GwBufferMember059, /* GW-ID:059	0x17F */
	&GwBufferMember060, /* GW-ID:060	0x180 */
	&GwBufferMember061, /* GW-ID:061	0x185 */
	&GwBufferMember062, /* GW-ID:062	0x186 */
	&GwBufferMember063, /* GW-ID:063	0x18D */
	&GwBufferMember064, /* GW-ID:064	0x19A */
	&GwBufferMember065, /* GW-ID:065	0x1A1 */
	&GwBufferMember066, /* GW-ID:066	0x1A2 */
	&GwBufferMember067, /* GW-ID:067	0x1A3 */
	&GwBufferMember068, /* GW-ID:068	0x1A4 */
	&GwBufferMember069, /* GW-ID:069	0x1A5 */
	&GwBufferMember070, /* GW-ID:070	0x1A7 */
	&GwBufferMember071, /* GW-ID:071	0x1A8 */
	&GwBufferMember072, /* GW-ID:072	0x1A9 */
	&GwBufferMember073, /* GW-ID:073	0x1AB */
	&GwBufferMember074, /* GW-ID:074	0x1AC */
	&GwBufferMember075, /* GW-ID:075	0x1AD */
	&GwBufferMember076, /* GW-ID:076	0x1AE */
	&GwBufferMember077, /* GW-ID:077	0x1AF */
	&GwBufferMember078, /* GW-ID:078	0x1B0 */
	&GwBufferMember079, /* GW-ID:079	0x1B2 */
	&GwBufferMember080, /* GW-ID:080	0x1B3 */
	&GwBufferMember081, /* GW-ID:081	0x1B4 */
	&GwBufferMember082, /* GW-ID:082	0x1B5 */
	&GwBufferMember083, /* GW-ID:083	0x1B7 */
	&GwBufferMember084, /* GW-ID:084	0x1B8 */
	&GwBufferMember085, /* GW-ID:085	0x1B9 */
	&GwBufferMember086, /* GW-ID:086	0x1BA */
	&GwBufferMember087, /* GW-ID:087	0x1BB */
	&GwBufferMember088, /* GW-ID:088	0x1BC */
	&GwBufferMember089, /* GW-ID:089	0x1BD */
	&GwBufferMember090, /* GW-ID:090	0x1BE */
	&GwBufferMember091, /* GW-ID:091	0x1C0 */
	&GwBufferMember092, /* GW-ID:092	0x1C5 */
	&GwBufferMember093, /* GW-ID:093	0x1C7 */
	&GwBufferMember094, /* GW-ID:094	0x1CA */
	&GwBufferMember095, /* GW-ID:095	0x1CC */
	&GwBufferMember096, /* GW-ID:096	0x1CF */
	&GwBufferMember097, /* GW-ID:097	0x1D0 */
	&GwBufferMember098, /* GW-ID:098	0x1D1 */
	&GwBufferMember099, /* GW-ID:099	0x1D2 */
	&GwBufferMember100, /* GW-ID:100	0x1D3 */
	&GwBufferMember101, /* GW-ID:101	0x1D6 */
	&GwBufferMember102, /* GW-ID:102	0x1D7 */
	&GwBufferMember103, /* GW-ID:103	0x1D8 */
	&GwBufferMember104, /* GW-ID:104	0x1D9 */
	&GwBufferMember105, /* GW-ID:105	0x1DB */
	&GwBufferMember106, /* GW-ID:106	0x1DC */
	&GwBufferMember107, /* GW-ID:107	0x1DD */
	&GwBufferMember108, /* GW-ID:108	0x1DE */
	&GwBufferMember109, /* GW-ID:109	0x1DF */
	&GwBufferMember110, /* GW-ID:110	0x1E1 */
	&GwBufferMember111, /* GW-ID:111	0x1E3 */
	&GwBufferMember112, /* GW-ID:112	0x1EA */
	&GwBufferMember113, /* GW-ID:113	0x1EB */
	&GwBufferMember114, /* GW-ID:114	0x1EC */
	&GwBufferMember115, /* GW-ID:115	0x1EF */
	&GwBufferMember116, /* GW-ID:116	0x1F0 */
	&GwBufferMember117, /* GW-ID:117	0x1F1 */
	&GwBufferMember118, /* GW-ID:118	0x1F2 */
	&GwBufferMember119, /* GW-ID:119	0x1F4 */
	&GwBufferMember120, /* GW-ID:120	0x1F5 */
	&GwBufferMember121, /* GW-ID:121	0x1F6 */
	&GwBufferMember122, /* GW-ID:122	0x1F7 */
	&GwBufferMember123, /* GW-ID:123	0x1FA */
	&GwBufferMember124, /* GW-ID:124	0x1FC */
	&GwBufferMember125, /* GW-ID:125	0x1FD */
	&GwBufferMember126, /* GW-ID:126	0x1FE */
	&GwBufferMember127, /* GW-ID:127	0x1FF */
	&GwBufferMember128, /* GW-ID:128	0x202 */
	&GwBufferMember129, /* GW-ID:129	0x203 */
	&GwBufferMember130, /* GW-ID:130	0x204 */
	&GwBufferMember131, /* GW-ID:131	0x207 */
	&GwBufferMember132, /* GW-ID:132	0x208 */
	&GwBufferMember133, /* GW-ID:133	0x209 */
	&GwBufferMember134, /* GW-ID:134	0x20A */
	&GwBufferMember135, /* GW-ID:135	0x20B */
	&GwBufferMember136, /* GW-ID:136	0x20E */
	&GwBufferMember137, /* GW-ID:137	0x20F */
	&GwBufferMember138, /* GW-ID:138	0x214 */
	&GwBufferMember139, /* GW-ID:139	0x219 */
	&GwBufferMember140, /* GW-ID:140	0x22E */
	&GwBufferMember141, /* GW-ID:141	0x230 */
	&GwBufferMember142, /* GW-ID:142	0x235 */
	&GwBufferMember143, /* GW-ID:143	0x247 */
	&GwBufferMember144, /* GW-ID:144	0x24D */
	&GwBufferMember145, /* GW-ID:145	0x251 */
	&GwBufferMember146, /* GW-ID:146	0x252 */
	&GwBufferMember147, /* GW-ID:147	0x255 */
	&GwBufferMember148, /* GW-ID:148	0x259 */
	&GwBufferMember149, /* GW-ID:149	0x25A */
	&GwBufferMember150, /* GW-ID:150	0x261 */
	&GwBufferMember151, /* GW-ID:151	0x262 */
	&GwBufferMember152, /* GW-ID:152	0x26E */
	&GwBufferMember153, /* GW-ID:153	0x272 */
	&GwBufferMember154, /* GW-ID:154	0x274 */
	&GwBufferMember155, /* GW-ID:155	0x275 */
	&GwBufferMember156, /* GW-ID:156	0x276 */
	&GwBufferMember157, /* GW-ID:157	0x279 */
	&GwBufferMember158, /* GW-ID:158	0x27B */
	&GwBufferMember159, /* GW-ID:159	0x27C */
	&GwBufferMember160, /* GW-ID:160	0x27D */
	&GwBufferMember161, /* GW-ID:161	0x27E */
	&GwBufferMember162, /* GW-ID:162	0x281 */
	&GwBufferMember163, /* GW-ID:163	0x282 */
	&GwBufferMember164, /* GW-ID:164	0x285 */
	&GwBufferMember165, /* GW-ID:165	0x28A */
	&GwBufferMember166, /* GW-ID:166	0x295 */
	&GwBufferMember167, /* GW-ID:167	0x296 */
	&GwBufferMember168, /* GW-ID:168	0x2A0 */
	&GwBufferMember169, /* GW-ID:169	0x2A1 */
	&GwBufferMember170, /* GW-ID:170	0x2A6 */
	&GwBufferMember171, /* GW-ID:171	0x2A7 */
	&GwBufferMember172, /* GW-ID:172	0x2A8 */
	&GwBufferMember173, /* GW-ID:173	0x2AA */
	&GwBufferMember174, /* GW-ID:174	0x2AF */
	&GwBufferMember175, /* GW-ID:175	0x2B2 */
	&GwBufferMember176, /* GW-ID:176	0x2B3 */
	&GwBufferMember177, /* GW-ID:177	0x2D2 */
	&GwBufferMember178, /* GW-ID:178	0x2D3 */
	&GwBufferMember179, /* GW-ID:179	0x2D4 */
	&GwBufferMember180, /* GW-ID:180	0x2D5 */
	&GwBufferMember181, /* GW-ID:181	0x2D6 */
	&GwBufferMember182, /* GW-ID:182	0x2D7 */
	&GwBufferMember183, /* GW-ID:183	0x2DA */
	&GwBufferMember184, /* GW-ID:184	0x2DE */
	&GwBufferMember185, /* GW-ID:185	0x2DF */
	&GwBufferMember186, /* GW-ID:186	0x2E0 */
	&GwBufferMember187, /* GW-ID:187	0x2E1 */
	&GwBufferMember188, /* GW-ID:188	0x2E2 */
	&GwBufferMember189, /* GW-ID:189	0x2E3 */
	&GwBufferMember190, /* GW-ID:190	0x2E5 */
	&GwBufferMember191, /* GW-ID:191	0x2E7 */
	&GwBufferMember192, /* GW-ID:192	0x2E8 */
	&GwBufferMember193, /* GW-ID:193	0x2EB */
	&GwBufferMember194, /* GW-ID:194	0x2EE */
	&GwBufferMember195, /* GW-ID:195	0x2EF */
	&GwBufferMember196, /* GW-ID:196	0x2F0 */
	&GwBufferMember197, /* GW-ID:197	0x2F2 */
	&GwBufferMember198, /* GW-ID:198	0x2F3 */
	&GwBufferMember199, /* GW-ID:199	0x2F4 */
	&GwBufferMember200, /* GW-ID:200	0x2F5 */
	&GwBufferMember201, /* GW-ID:201	0x2F6 */
	&GwBufferMember202, /* GW-ID:202	0x2F7 */
	&GwBufferMember203, /* GW-ID:203	0x2F8 */
	&GwBufferMember204, /* GW-ID:204	0x2F9 */
	&GwBufferMember205, /* GW-ID:205	0x2FA */
	&GwBufferMember206, /* GW-ID:206	0x2FB */
	&GwBufferMember207, /* GW-ID:207	0x2FD */
	&GwBufferMember208, /* GW-ID:208	0x2FE */
	&GwBufferMember209, /* GW-ID:209	0x305 */
	&GwBufferMember210, /* GW-ID:210	0x306 */
	&GwBufferMember211, /* GW-ID:211	0x30D */
	&GwBufferMember212, /* GW-ID:212	0x30E */
	&GwBufferMember213, /* GW-ID:213	0x30F */
	&GwBufferMember214, /* GW-ID:214	0x312 */
	&GwBufferMember215, /* GW-ID:215	0x313 */
	&GwBufferMember216, /* GW-ID:216	0x314 */
	&GwBufferMember217, /* GW-ID:217	0x315 */
	&GwBufferMember218, /* GW-ID:218	0x317 */
	&GwBufferMember219, /* GW-ID:219	0x318 */
	&GwBufferMember220, /* GW-ID:220	0x31A */
	&GwBufferMember221, /* GW-ID:221	0x31D */
	&GwBufferMember222, /* GW-ID:222	0x320 */
	&GwBufferMember223, /* GW-ID:223	0x322 */
	&GwBufferMember224, /* GW-ID:224	0x325 */
	&GwBufferMember225, /* GW-ID:225	0x328 */
	&GwBufferMember226, /* GW-ID:226	0x32A */
	&GwBufferMember227, /* GW-ID:227	0x32F */
	&GwBufferMember228, /* GW-ID:228	0x333 */
	&GwBufferMember229, /* GW-ID:229	0x334 */
	&GwBufferMember230, /* GW-ID:230	0x335 */
	&GwBufferMember231, /* GW-ID:231	0x336 */
	&GwBufferMember232, /* GW-ID:232	0x337 */
	&GwBufferMember233, /* GW-ID:233	0x33A */
	&GwBufferMember234, /* GW-ID:234	0x33F */
	&GwBufferMember235, /* GW-ID:235	0x341 */
	&GwBufferMember236, /* GW-ID:236	0x345 */
	&GwBufferMember237, /* GW-ID:237	0x346 */
	&GwBufferMember238, /* GW-ID:238	0x347 */
	&GwBufferMember239, /* GW-ID:239	0x348 */
	&GwBufferMember240, /* GW-ID:240	0x349 */
	&GwBufferMember241, /* GW-ID:241	0x34C */
	&GwBufferMember242, /* GW-ID:242	0x34D */
	&GwBufferMember243, /* GW-ID:243	0x34E */
	&GwBufferMember244, /* GW-ID:244	0x34F */
	&GwBufferMember245, /* GW-ID:245	0x350 */
	&GwBufferMember246, /* GW-ID:246	0x351 */
	&GwBufferMember247, /* GW-ID:247	0x352 */
	&GwBufferMember248, /* GW-ID:248	0x353 */
	&GwBufferMember249, /* GW-ID:249	0x354 */
	&GwBufferMember250, /* GW-ID:250	0x355 */
	&GwBufferMember251, /* GW-ID:251	0x357 */
	&GwBufferMember252, /* GW-ID:252	0x358 */
	&GwBufferMember253, /* GW-ID:253	0x35A */
	&GwBufferMember254, /* GW-ID:254	0x35B */
	&GwBufferMember255, /* GW-ID:255	0x35D */
	&GwBufferMember256, /* GW-ID:256	0x35F */
	&GwBufferMember257, /* GW-ID:257	0x363 */
	&GwBufferMember258, /* GW-ID:258	0x364 */
	&GwBufferMember259, /* GW-ID:259	0x367 */
	&GwBufferMember260, /* GW-ID:260	0x368 */
	&GwBufferMember261, /* GW-ID:261	0x36A */
	&GwBufferMember262, /* GW-ID:262	0x36B */
	&GwBufferMember263, /* GW-ID:263	0x36E */
	&GwBufferMember264, /* GW-ID:264	0x36F */
	&GwBufferMember265, /* GW-ID:265	0x375 */
	&GwBufferMember266, /* GW-ID:266	0x379 */
	&GwBufferMember267, /* GW-ID:267	0x37B */
	&GwBufferMember268, /* GW-ID:268	0x37E */
	&GwBufferMember269, /* GW-ID:269	0x37F */
	&GwBufferMember270, /* GW-ID:270	0x380 */
	&GwBufferMember271, /* GW-ID:271	0x381 */
	&GwBufferMember272, /* GW-ID:272	0x382 */
	&GwBufferMember273, /* GW-ID:273	0x384 */
	&GwBufferMember274, /* GW-ID:274	0x385 */
	&GwBufferMember275, /* GW-ID:275	0x386 */
	&GwBufferMember276, /* GW-ID:276	0x387 */
	&GwBufferMember277, /* GW-ID:277	0x388 */
	&GwBufferMember278, /* GW-ID:278	0x389 */
	&GwBufferMember279, /* GW-ID:279	0x38A */
	&GwBufferMember280, /* GW-ID:280	0x38B */
	&GwBufferMember281, /* GW-ID:281	0x38D */
	&GwBufferMember282, /* GW-ID:282	0x38E */
	&GwBufferMember283, /* GW-ID:283	0x38F */
	&GwBufferMember284, /* GW-ID:284	0x390 */
	&GwBufferMember285, /* GW-ID:285	0x393 */
	&GwBufferMember286, /* GW-ID:286	0x395 */
	&GwBufferMember287, /* GW-ID:287	0x396 */
	&GwBufferMember288, /* GW-ID:288	0x397 */
	&GwBufferMember289, /* GW-ID:289	0x398 */
	&GwBufferMember290, /* GW-ID:290	0x39A */
	&GwBufferMember291, /* GW-ID:291	0x39B */
	&GwBufferMember292, /* GW-ID:292	0x39C */
	&GwBufferMember293, /* GW-ID:293	0x39D */
	&GwBufferMember294, /* GW-ID:294	0x39E */
	&GwBufferMember295, /* GW-ID:295	0x39F */
	&GwBufferMember296, /* GW-ID:296	0x3A1 */
	&GwBufferMember297, /* GW-ID:297	0x3A5 */
	&GwBufferMember298, /* GW-ID:298	0x3A6 */
	&GwBufferMember299, /* GW-ID:299	0x3A7 */
	&GwBufferMember300, /* GW-ID:300	0x3A8 */
	&GwBufferMember301, /* GW-ID:301	0x3A9 */
	&GwBufferMember302, /* GW-ID:302	0x3AB */
	&GwBufferMember303, /* GW-ID:303	0x3AC */
	&GwBufferMember304, /* GW-ID:304	0x3AE */
	&GwBufferMember305, /* GW-ID:305	0x3AF */
	&GwBufferMember306, /* GW-ID:306	0x3B0 */
	&GwBufferMember307, /* GW-ID:307	0x3B1 */
	&GwBufferMember308, /* GW-ID:308	0x3B2 */
	&GwBufferMember309, /* GW-ID:309	0x3B3 */
	&GwBufferMember310, /* GW-ID:310	0x3B5 */
	&GwBufferMember311, /* GW-ID:311	0x3B6 */
	&GwBufferMember312, /* GW-ID:312	0x3B8 */
	&GwBufferMember313, /* GW-ID:313	0x3B9 */
	&GwBufferMember314, /* GW-ID:314	0x3BB */
	&GwBufferMember315, /* GW-ID:315	0x3BC */
	&GwBufferMember316, /* GW-ID:316	0x3BD */
	&GwBufferMember317, /* GW-ID:317	0x3BE */
	&GwBufferMember318, /* GW-ID:318	0x3BF */
	&GwBufferMember319, /* GW-ID:319	0x3C0 */
	&GwBufferMember320, /* GW-ID:320	0x3C2 */
	&GwBufferMember321, /* GW-ID:321	0x3C4 */
	&GwBufferMember322, /* GW-ID:322	0x3C6 */
	&GwBufferMember323, /* GW-ID:323	0x3C7 */
	&GwBufferMember324, /* GW-ID:324	0x3C8 */
	&GwBufferMember325, /* GW-ID:325	0x3C9 */
	&GwBufferMember326, /* GW-ID:326	0x3CA */
	&GwBufferMember327, /* GW-ID:327	0x3CB */
	&GwBufferMember328, /* GW-ID:328	0x3CD */
	&GwBufferMember329, /* GW-ID:329	0x3D0 */
	&GwBufferMember330, /* GW-ID:330	0x3D2 */
	&GwBufferMember331, /* GW-ID:331	0x3D3 */
	&GwBufferMember332, /* GW-ID:332	0x3D4 */
	&GwBufferMember333, /* GW-ID:333	0x3D6 */
	&GwBufferMember334, /* GW-ID:334	0x3D9 */
	&GwBufferMember335, /* GW-ID:335	0x3DB */
	&GwBufferMember336, /* GW-ID:336	0x3DC */
	&GwBufferMember337, /* GW-ID:337	0x3DD */
	&GwBufferMember338, /* GW-ID:338	0x3DE */
	&GwBufferMember339, /* GW-ID:339	0x3E1 */
	&GwBufferMember340, /* GW-ID:340	0x3E4 */
	&GwBufferMember341, /* GW-ID:341	0x3E5 */
	&GwBufferMember342, /* GW-ID:342	0x3E6 */
	&GwBufferMember343, /* GW-ID:343	0x3E7 */
	&GwBufferMember344, /* GW-ID:344	0x3EA */
	&GwBufferMember345, /* GW-ID:345	0x3EB */
	&GwBufferMember346, /* GW-ID:346	0x3EC */
	&GwBufferMember347, /* GW-ID:347	0x3EE */
	&GwBufferMember348, /* GW-ID:348	0x3EF */
	&GwBufferMember349, /* GW-ID:349	0x3F0 */
	&GwBufferMember350, /* GW-ID:350	0x3F1 */
	&GwBufferMember351, /* GW-ID:351	0x3F2 */
	&GwBufferMember352, /* GW-ID:352	0x3F3 */
	&GwBufferMember353, /* GW-ID:353	0x3F5 */
	&GwBufferMember354, /* GW-ID:354	0x3F6 */
	&GwBufferMember355, /* GW-ID:355	0x3F7 */
	&GwBufferMember356, /* GW-ID:356	0x3F9 */
	&GwBufferMember357, /* GW-ID:357	0x3FB */
	&GwBufferMember358, /* GW-ID:358	0x3FC */
	&GwBufferMember359, /* GW-ID:359	0x3FD */
	&GwBufferMember360, /* GW-ID:360	0x400 */
	&GwBufferMember361, /* GW-ID:361	0x401 */
	&GwBufferMember362, /* GW-ID:362	0x403 */
	&GwBufferMember363, /* GW-ID:363	0x404 */
	&GwBufferMember364, /* GW-ID:364	0x405 */
	&GwBufferMember365, /* GW-ID:365	0x407 */
	&GwBufferMember366, /* GW-ID:366	0x408 */
	&GwBufferMember367, /* GW-ID:367	0x40B */
	&GwBufferMember368, /* GW-ID:368	0x40C */
	&GwBufferMember369, /* GW-ID:369	0x40D */
	&GwBufferMember370, /* GW-ID:370	0x40E */
	&GwBufferMember371, /* GW-ID:371	0x411 */
	&GwBufferMember372, /* GW-ID:372	0x412 */
	&GwBufferMember373, /* GW-ID:373	0x417 */
	&GwBufferMember374, /* GW-ID:374	0x418 */
	&GwBufferMember375, /* GW-ID:375	0x41A */
	&GwBufferMember376, /* GW-ID:376	0x421 */
	&GwBufferMember377, /* GW-ID:377	0x422 */
	&GwBufferMember378, /* GW-ID:378	0x423 */
	&GwBufferMember379, /* GW-ID:379	0x426 */
	&GwBufferMember380, /* GW-ID:380	0x427 */
	&GwBufferMember381, /* GW-ID:381	0x428 */
	&GwBufferMember382, /* GW-ID:382	0x429 */
	&GwBufferMember383, /* GW-ID:383	0x42A */
	&GwBufferMember384, /* GW-ID:384	0x42B */
	&GwBufferMember385, /* GW-ID:385	0x42C */
	&GwBufferMember386, /* GW-ID:386	0x42E */
	&GwBufferMember387, /* GW-ID:387	0x42F */
	&GwBufferMember388, /* GW-ID:388	0x430 */
	&GwBufferMember389, /* GW-ID:389	0x432 */
	&GwBufferMember390, /* GW-ID:390	0x434 */
	&GwBufferMember391, /* GW-ID:391	0x435 */
	&GwBufferMember392, /* GW-ID:392	0x436 */
	&GwBufferMember393, /* GW-ID:393	0x437 */
	&GwBufferMember394, /* GW-ID:394	0x438 */
	&GwBufferMember395, /* GW-ID:395	0x439 */
	&GwBufferMember396, /* GW-ID:396	0x43A */
	&GwBufferMember397, /* GW-ID:397	0x43B */
	&GwBufferMember398, /* GW-ID:398	0x43E */
	&GwBufferMember399, /* GW-ID:399	0x442 */
	&GwBufferMember400, /* GW-ID:400	0x480 */
	&GwBufferMember401, /* GW-ID:401	0x484 */
	&GwBufferMember402, /* GW-ID:402	0x489 */
	&GwBufferMember403, /* GW-ID:403	0x48B */
	&GwBufferMember404, /* GW-ID:404	0x490 */
	&GwBufferMember405, /* GW-ID:405	0x491 */
	&GwBufferMember406, /* GW-ID:406	0x494 */
	&GwBufferMember407, /* GW-ID:407	0x495 */
	&GwBufferMember408, /* GW-ID:408	0x496 */
	&GwBufferMember409, /* GW-ID:409	0x497 */
	&GwBufferMember410, /* GW-ID:410	0x499 */
	&GwBufferMember411, /* GW-ID:411	0x49A */
	&GwBufferMember412, /* GW-ID:412	0x49B */
	&GwBufferMember413, /* GW-ID:413	0x49D */
	&GwBufferMember414, /* GW-ID:414	0x4A0 */
	&GwBufferMember415, /* GW-ID:415	0x4A1 */
	&GwBufferMember416, /* GW-ID:416	0x4A3 */
	&GwBufferMember417, /* GW-ID:417	0x4A4 */
	&GwBufferMember418, /* GW-ID:418	0x4A8 */
	&GwBufferMember419, /* GW-ID:419	0x4AC */
	&GwBufferMember420, /* GW-ID:420	0x4AE */
	&GwBufferMember421, /* GW-ID:421	0x4AF */
	&GwBufferMember422, /* GW-ID:422	0x4B8 */
	&GwBufferMember423, /* GW-ID:423	0x4BC */
	&GwBufferMember424, /* GW-ID:424	0x500 */
	&GwBufferMember425, /* GW-ID:425	0x506 */
	&GwBufferMember426, /* GW-ID:426	0x507 */
	&GwBufferMember427, /* GW-ID:427	0x515 */
	&GwBufferMember428, /* GW-ID:428	0x51A */
	&GwBufferMember429, /* GW-ID:429	0x51B */
	&GwBufferMember430, /* GW-ID:430	0x51D */
	&GwBufferMember431, /* GW-ID:431	0x51E */
	&GwBufferMember432, /* GW-ID:432	0x51F */
	&GwBufferMember433, /* GW-ID:433	0x521 */
	&GwBufferMember434, /* GW-ID:434	0x524 */
	&GwBufferMember435, /* GW-ID:435	0x526 */
	&GwBufferMember436, /* GW-ID:436	0x527 */
	&GwBufferMember437, /* GW-ID:437	0x528 */
	&GwBufferMember438, /* GW-ID:438	0x529 */
	&GwBufferMember439, /* GW-ID:439	0x52A */
	&GwBufferMember440, /* GW-ID:440	0x52B */
	&GwBufferMember441, /* GW-ID:441	0x52C */
	&GwBufferMember442, /* GW-ID:442	0x530 */
	&GwBufferMember443, /* GW-ID:443	0x531 */
	&GwBufferMember444, /* GW-ID:444	0x532 */
	&GwBufferMember445, /* GW-ID:445	0x534 */
	&GwBufferMember446, /* GW-ID:446	0x535 */
	&GwBufferMember447, /* GW-ID:447	0x537 */
	&GwBufferMember448, /* GW-ID:448	0x538 */
	&GwBufferMember449, /* GW-ID:449	0x56D */
	&GwBufferMember450, /* GW-ID:450	0x583 */
	&GwBufferMember451, /* GW-ID:451	0x589 */
	&GwBufferMember452, /* GW-ID:452	0x58A */
	&GwBufferMember453, /* GW-ID:453	0x58D */
	&GwBufferMember454, /* GW-ID:454	0x592 */
	&GwBufferMember455, /* GW-ID:455	0x594 */
	&GwBufferMember456, /* GW-ID:456	0x596 */
	&GwBufferMember457, /* GW-ID:457	0x5F1 */
	&GwBufferMember458, /* GW-ID:458	0x5F3 */
	&GwBufferMember459, /* GW-ID:459	0x5F4 */
	&GwBufferMember460, /* GW-ID:460	0x5F6 */
	&GwBufferMember461, /* GW-ID:461	0x601 */
	&GwBufferMember462, /* GW-ID:462	0x602 */
	&GwBufferMember463, /* GW-ID:463	0x608 */
	&GwBufferMember464, /* GW-ID:464	0x60C */
	&GwBufferMember465, /* GW-ID:465	0x610 */
	&GwBufferMember466, /* GW-ID:466	0x611 */
	&GwBufferMember467, /* GW-ID:467	0x613 */
	&GwBufferMember468, /* GW-ID:468	0x614 */
	&GwBufferMember469, /* GW-ID:469	0x615 */
	&GwBufferMember470, /* GW-ID:470	0x618 */
	&GwBufferMember471, /* GW-ID:471	0x621 */
	&GwBufferMember472, /* GW-ID:472	0x622 */
	&GwBufferMember473, /* GW-ID:473	0x623 */
	&GwBufferMember474, /* GW-ID:474	0x624 */
	&GwBufferMember475, /* GW-ID:475	0x626 */
	&GwBufferMember476, /* GW-ID:476	0x629 */
	&GwBufferMember477, /* GW-ID:477	0x62A */
	&GwBufferMember478, /* GW-ID:478	0x62C */
	&GwBufferMember479  /* GW-ID:479	0x633 */
};

#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"


/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
