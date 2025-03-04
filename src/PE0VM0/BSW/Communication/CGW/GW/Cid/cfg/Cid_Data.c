/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		Cid_Data.c
 * @brief		CANID探索
 * @details
 ****************************************************************************/
/*****************************************************************************
 * @note	ツール自動生成（Cid）
 * @note        CNIDS-IDテーブル：
 * @note            CNIDS-ID_Table.yml
 * @note        L3R-IDテーブル：
 * @note            L3R-ID_Table.yml
 * @note		テンプレートファイル：
 * @note            templates/ID_dataC.tmpl
 * @note	ツールバージョン
 * @note		1.8.0
 ****************************************************************************/
/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "CHM_LogicCh.h"

#include "Cid_Data.h"

/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/

#define GW_CID_START_SEC_CONST
#include "GW_Cid_Memmap.h"

/* 標準CANID探索用テーブル（CanidDataArraySet Cid_Data_CanId_UserTable[CID_SEARCH_MAX]）に対応したCNIDS側定義 */
static const uint16 CnidsId000[CHM_LOG_CAN_CH_NUM] = { 65535U,65535U,65535U,65535U };

/* 拡張CANID探索用テーブル（CanidDataArraySet Cid_Data_CanId_Ex_UserTable[CID_SEARCHEX_MAX]）に対応したCNIDS側定義 */
static const uint16 CnidsId00000000[CHM_LOG_CAN_CH_NUM] = { 65535U,65535U,65535U,65535U };


/* 標準CANID探索用テーブル */
CanidDataArraySet Cid_Data_CanId_UserTable[CID_SEARCH_MAX] = {
	{ 0x000U,0U,CnidsId000 },	/* 000 */
	{ 0x013U,1U,CnidsId000 },	/* 013 */
	{ 0x01BU,2U,CnidsId000 },	/* 01B */
	{ 0x049U,3U,CnidsId000 },	/* 049 */
	{ 0x062U,4U,CnidsId000 },	/* 062 */
	{ 0x069U,5U,CnidsId000 },	/* 069 */
	{ 0x06AU,6U,CnidsId000 },	/* 06A */
	{ 0x072U,7U,CnidsId000 },	/* 072 */
	{ 0x075U,8U,CnidsId000 },	/* 075 */
	{ 0x07EU,9U,CnidsId000 },	/* 07E */
	{ 0x086U,10U,CnidsId000 },	/* 086 */
	{ 0x09EU,11U,CnidsId000 },	/* 09E */
	{ 0x0A0U,12U,CnidsId000 },	/* 0A0 */
	{ 0x0A1U,13U,CnidsId000 },	/* 0A1 */
	{ 0x0A3U,14U,CnidsId000 },	/* 0A3 */
	{ 0x0A4U,15U,CnidsId000 },	/* 0A4 */
	{ 0x0A5U,16U,CnidsId000 },	/* 0A5 */
	{ 0x0A6U,17U,CnidsId000 },	/* 0A6 */
	{ 0x0A8U,18U,CnidsId000 },	/* 0A8 */
	{ 0x0A9U,19U,CnidsId000 },	/* 0A9 */
	{ 0x0B7U,20U,CnidsId000 },	/* 0B7 */
	{ 0x0B8U,21U,CnidsId000 },	/* 0B8 */
	{ 0x0F3U,22U,CnidsId000 },	/* 0F3 */
	{ 0x0FCU,23U,CnidsId000 },	/* 0FC */
	{ 0x100U,24U,CnidsId000 },	/* 100 */
	{ 0x10BU,25U,CnidsId000 },	/* 10B */
	{ 0x115U,26U,CnidsId000 },	/* 115 */
	{ 0x121U,27U,CnidsId000 },	/* 121 */
	{ 0x122U,28U,CnidsId000 },	/* 122 */
	{ 0x124U,29U,CnidsId000 },	/* 124 */
	{ 0x126U,30U,CnidsId000 },	/* 126 */
	{ 0x128U,31U,CnidsId000 },	/* 128 */
	{ 0x12BU,32U,CnidsId000 },	/* 12B */
	{ 0x140U,33U,CnidsId000 },	/* 140 */
	{ 0x141U,34U,CnidsId000 },	/* 141 */
	{ 0x143U,35U,CnidsId000 },	/* 143 */
	{ 0x144U,36U,CnidsId000 },	/* 144 */
	{ 0x148U,37U,CnidsId000 },	/* 148 */
	{ 0x14BU,38U,CnidsId000 },	/* 14B */
	{ 0x14CU,39U,CnidsId000 },	/* 14C */
	{ 0x14DU,40U,CnidsId000 },	/* 14D */
	{ 0x14FU,41U,CnidsId000 },	/* 14F */
	{ 0x150U,42U,CnidsId000 },	/* 150 */
	{ 0x155U,43U,CnidsId000 },	/* 155 */
	{ 0x159U,44U,CnidsId000 },	/* 159 */
	{ 0x15AU,45U,CnidsId000 },	/* 15A */
	{ 0x161U,46U,CnidsId000 },	/* 161 */
	{ 0x162U,47U,CnidsId000 },	/* 162 */
	{ 0x163U,48U,CnidsId000 },	/* 163 */
	{ 0x166U,49U,CnidsId000 },	/* 166 */
	{ 0x167U,50U,CnidsId000 },	/* 167 */
	{ 0x168U,51U,CnidsId000 },	/* 168 */
	{ 0x169U,52U,CnidsId000 },	/* 169 */
	{ 0x16AU,53U,CnidsId000 },	/* 16A */
	{ 0x16BU,54U,CnidsId000 },	/* 16B */
	{ 0x16CU,55U,CnidsId000 },	/* 16C */
	{ 0x16DU,56U,CnidsId000 },	/* 16D */
	{ 0x16EU,57U,CnidsId000 },	/* 16E */
	{ 0x17EU,58U,CnidsId000 },	/* 17E */
	{ 0x17FU,59U,CnidsId000 },	/* 17F */
	{ 0x180U,60U,CnidsId000 },	/* 180 */
	{ 0x185U,61U,CnidsId000 },	/* 185 */
	{ 0x186U,62U,CnidsId000 },	/* 186 */
	{ 0x18DU,63U,CnidsId000 },	/* 18D */
	{ 0x19AU,64U,CnidsId000 },	/* 19A */
	{ 0x1A1U,65U,CnidsId000 },	/* 1A1 */
	{ 0x1A2U,66U,CnidsId000 },	/* 1A2 */
	{ 0x1A3U,67U,CnidsId000 },	/* 1A3 */
	{ 0x1A4U,68U,CnidsId000 },	/* 1A4 */
	{ 0x1A5U,69U,CnidsId000 },	/* 1A5 */
	{ 0x1A7U,70U,CnidsId000 },	/* 1A7 */
	{ 0x1A8U,71U,CnidsId000 },	/* 1A8 */
	{ 0x1A9U,72U,CnidsId000 },	/* 1A9 */
	{ 0x1ABU,73U,CnidsId000 },	/* 1AB */
	{ 0x1ACU,74U,CnidsId000 },	/* 1AC */
	{ 0x1ADU,75U,CnidsId000 },	/* 1AD */
	{ 0x1AEU,76U,CnidsId000 },	/* 1AE */
	{ 0x1AFU,77U,CnidsId000 },	/* 1AF */
	{ 0x1B0U,78U,CnidsId000 },	/* 1B0 */
	{ 0x1B2U,79U,CnidsId000 },	/* 1B2 */
	{ 0x1B3U,80U,CnidsId000 },	/* 1B3 */
	{ 0x1B4U,81U,CnidsId000 },	/* 1B4 */
	{ 0x1B5U,82U,CnidsId000 },	/* 1B5 */
	{ 0x1B7U,83U,CnidsId000 },	/* 1B7 */
	{ 0x1B8U,84U,CnidsId000 },	/* 1B8 */
	{ 0x1B9U,85U,CnidsId000 },	/* 1B9 */
	{ 0x1BAU,86U,CnidsId000 },	/* 1BA */
	{ 0x1BBU,87U,CnidsId000 },	/* 1BB */
	{ 0x1BCU,88U,CnidsId000 },	/* 1BC */
	{ 0x1BDU,89U,CnidsId000 },	/* 1BD */
	{ 0x1BEU,90U,CnidsId000 },	/* 1BE */
	{ 0x1C0U,91U,CnidsId000 },	/* 1C0 */
	{ 0x1C5U,92U,CnidsId000 },	/* 1C5 */
	{ 0x1C7U,93U,CnidsId000 },	/* 1C7 */
	{ 0x1CAU,94U,CnidsId000 },	/* 1CA */
	{ 0x1CCU,95U,CnidsId000 },	/* 1CC */
	{ 0x1CFU,96U,CnidsId000 },	/* 1CF */
	{ 0x1D0U,97U,CnidsId000 },	/* 1D0 */
	{ 0x1D1U,98U,CnidsId000 },	/* 1D1 */
	{ 0x1D2U,99U,CnidsId000 },	/* 1D2 */
	{ 0x1D3U,100U,CnidsId000 },	/* 1D3 */
	{ 0x1D6U,101U,CnidsId000 },	/* 1D6 */
	{ 0x1D7U,102U,CnidsId000 },	/* 1D7 */
	{ 0x1D8U,103U,CnidsId000 },	/* 1D8 */
	{ 0x1D9U,104U,CnidsId000 },	/* 1D9 */
	{ 0x1DBU,105U,CnidsId000 },	/* 1DB */
	{ 0x1DCU,106U,CnidsId000 },	/* 1DC */
	{ 0x1DDU,107U,CnidsId000 },	/* 1DD */
	{ 0x1DEU,108U,CnidsId000 },	/* 1DE */
	{ 0x1DFU,109U,CnidsId000 },	/* 1DF */
	{ 0x1E1U,110U,CnidsId000 },	/* 1E1 */
	{ 0x1E3U,111U,CnidsId000 },	/* 1E3 */
	{ 0x1EAU,112U,CnidsId000 },	/* 1EA */
	{ 0x1EBU,113U,CnidsId000 },	/* 1EB */
	{ 0x1ECU,114U,CnidsId000 },	/* 1EC */
	{ 0x1EFU,115U,CnidsId000 },	/* 1EF */
	{ 0x1F0U,116U,CnidsId000 },	/* 1F0 */
	{ 0x1F1U,117U,CnidsId000 },	/* 1F1 */
	{ 0x1F2U,118U,CnidsId000 },	/* 1F2 */
	{ 0x1F4U,119U,CnidsId000 },	/* 1F4 */
	{ 0x1F5U,120U,CnidsId000 },	/* 1F5 */
	{ 0x1F6U,121U,CnidsId000 },	/* 1F6 */
	{ 0x1F7U,122U,CnidsId000 },	/* 1F7 */
	{ 0x1FAU,123U,CnidsId000 },	/* 1FA */
	{ 0x1FCU,124U,CnidsId000 },	/* 1FC */
	{ 0x1FDU,125U,CnidsId000 },	/* 1FD */
	{ 0x1FEU,126U,CnidsId000 },	/* 1FE */
	{ 0x1FFU,127U,CnidsId000 },	/* 1FF */
	{ 0x202U,128U,CnidsId000 },	/* 202 */
	{ 0x203U,129U,CnidsId000 },	/* 203 */
	{ 0x204U,130U,CnidsId000 },	/* 204 */
	{ 0x207U,131U,CnidsId000 },	/* 207 */
	{ 0x208U,132U,CnidsId000 },	/* 208 */
	{ 0x209U,133U,CnidsId000 },	/* 209 */
	{ 0x20AU,134U,CnidsId000 },	/* 20A */
	{ 0x20BU,135U,CnidsId000 },	/* 20B */
	{ 0x20EU,136U,CnidsId000 },	/* 20E */
	{ 0x20FU,137U,CnidsId000 },	/* 20F */
	{ 0x214U,138U,CnidsId000 },	/* 214 */
	{ 0x219U,139U,CnidsId000 },	/* 219 */
	{ 0x22EU,140U,CnidsId000 },	/* 22E */
	{ 0x230U,141U,CnidsId000 },	/* 230 */
	{ 0x235U,142U,CnidsId000 },	/* 235 */
	{ 0x247U,143U,CnidsId000 },	/* 247 */
	{ 0x24DU,144U,CnidsId000 },	/* 24D */
	{ 0x251U,145U,CnidsId000 },	/* 251 */
	{ 0x252U,146U,CnidsId000 },	/* 252 */
	{ 0x255U,147U,CnidsId000 },	/* 255 */
	{ 0x259U,148U,CnidsId000 },	/* 259 */
	{ 0x25AU,149U,CnidsId000 },	/* 25A */
	{ 0x261U,150U,CnidsId000 },	/* 261 */
	{ 0x262U,151U,CnidsId000 },	/* 262 */
	{ 0x26EU,152U,CnidsId000 },	/* 26E */
	{ 0x272U,153U,CnidsId000 },	/* 272 */
	{ 0x274U,154U,CnidsId000 },	/* 274 */
	{ 0x275U,155U,CnidsId000 },	/* 275 */
	{ 0x276U,156U,CnidsId000 },	/* 276 */
	{ 0x279U,157U,CnidsId000 },	/* 279 */
	{ 0x27BU,158U,CnidsId000 },	/* 27B */
	{ 0x27CU,159U,CnidsId000 },	/* 27C */
	{ 0x27DU,160U,CnidsId000 },	/* 27D */
	{ 0x27EU,161U,CnidsId000 },	/* 27E */
	{ 0x281U,162U,CnidsId000 },	/* 281 */
	{ 0x282U,163U,CnidsId000 },	/* 282 */
	{ 0x285U,164U,CnidsId000 },	/* 285 */
	{ 0x28AU,165U,CnidsId000 },	/* 28A */
	{ 0x295U,166U,CnidsId000 },	/* 295 */
	{ 0x296U,167U,CnidsId000 },	/* 296 */
	{ 0x2A0U,168U,CnidsId000 },	/* 2A0 */
	{ 0x2A1U,169U,CnidsId000 },	/* 2A1 */
	{ 0x2A6U,170U,CnidsId000 },	/* 2A6 */
	{ 0x2A7U,171U,CnidsId000 },	/* 2A7 */
	{ 0x2A8U,172U,CnidsId000 },	/* 2A8 */
	{ 0x2AAU,173U,CnidsId000 },	/* 2AA */
	{ 0x2AFU,174U,CnidsId000 },	/* 2AF */
	{ 0x2B2U,175U,CnidsId000 },	/* 2B2 */
	{ 0x2B3U,176U,CnidsId000 },	/* 2B3 */
	{ 0x2D2U,177U,CnidsId000 },	/* 2D2 */
	{ 0x2D3U,178U,CnidsId000 },	/* 2D3 */
	{ 0x2D4U,179U,CnidsId000 },	/* 2D4 */
	{ 0x2D5U,180U,CnidsId000 },	/* 2D5 */
	{ 0x2D6U,181U,CnidsId000 },	/* 2D6 */
	{ 0x2D7U,182U,CnidsId000 },	/* 2D7 */
	{ 0x2DAU,183U,CnidsId000 },	/* 2DA */
	{ 0x2DEU,184U,CnidsId000 },	/* 2DE */
	{ 0x2DFU,185U,CnidsId000 },	/* 2DF */
	{ 0x2E0U,186U,CnidsId000 },	/* 2E0 */
	{ 0x2E1U,187U,CnidsId000 },	/* 2E1 */
	{ 0x2E2U,188U,CnidsId000 },	/* 2E2 */
	{ 0x2E3U,189U,CnidsId000 },	/* 2E3 */
	{ 0x2E5U,190U,CnidsId000 },	/* 2E5 */
	{ 0x2E7U,191U,CnidsId000 },	/* 2E7 */
	{ 0x2E8U,192U,CnidsId000 },	/* 2E8 */
	{ 0x2EBU,193U,CnidsId000 },	/* 2EB */
	{ 0x2EEU,194U,CnidsId000 },	/* 2EE */
	{ 0x2EFU,195U,CnidsId000 },	/* 2EF */
	{ 0x2F0U,196U,CnidsId000 },	/* 2F0 */
	{ 0x2F2U,197U,CnidsId000 },	/* 2F2 */
	{ 0x2F3U,198U,CnidsId000 },	/* 2F3 */
	{ 0x2F4U,199U,CnidsId000 },	/* 2F4 */
	{ 0x2F5U,200U,CnidsId000 },	/* 2F5 */
	{ 0x2F6U,201U,CnidsId000 },	/* 2F6 */
	{ 0x2F7U,202U,CnidsId000 },	/* 2F7 */
	{ 0x2F8U,203U,CnidsId000 },	/* 2F8 */
	{ 0x2F9U,204U,CnidsId000 },	/* 2F9 */
	{ 0x2FAU,205U,CnidsId000 },	/* 2FA */
	{ 0x2FBU,206U,CnidsId000 },	/* 2FB */
	{ 0x2FDU,207U,CnidsId000 },	/* 2FD */
	{ 0x2FEU,208U,CnidsId000 },	/* 2FE */
	{ 0x305U,209U,CnidsId000 },	/* 305 */
	{ 0x306U,210U,CnidsId000 },	/* 306 */
	{ 0x30DU,211U,CnidsId000 },	/* 30D */
	{ 0x30EU,212U,CnidsId000 },	/* 30E */
	{ 0x30FU,213U,CnidsId000 },	/* 30F */
	{ 0x312U,214U,CnidsId000 },	/* 312 */
	{ 0x313U,215U,CnidsId000 },	/* 313 */
	{ 0x314U,216U,CnidsId000 },	/* 314 */
	{ 0x315U,217U,CnidsId000 },	/* 315 */
	{ 0x317U,218U,CnidsId000 },	/* 317 */
	{ 0x318U,219U,CnidsId000 },	/* 318 */
	{ 0x31AU,220U,CnidsId000 },	/* 31A */
	{ 0x31DU,221U,CnidsId000 },	/* 31D */
	{ 0x320U,222U,CnidsId000 },	/* 320 */
	{ 0x322U,223U,CnidsId000 },	/* 322 */
	{ 0x325U,224U,CnidsId000 },	/* 325 */
	{ 0x328U,225U,CnidsId000 },	/* 328 */
	{ 0x32AU,226U,CnidsId000 },	/* 32A */
	{ 0x32FU,227U,CnidsId000 },	/* 32F */
	{ 0x333U,228U,CnidsId000 },	/* 333 */
	{ 0x334U,229U,CnidsId000 },	/* 334 */
	{ 0x335U,230U,CnidsId000 },	/* 335 */
	{ 0x336U,231U,CnidsId000 },	/* 336 */
	{ 0x337U,232U,CnidsId000 },	/* 337 */
	{ 0x33AU,233U,CnidsId000 },	/* 33A */
	{ 0x33FU,234U,CnidsId000 },	/* 33F */
	{ 0x341U,235U,CnidsId000 },	/* 341 */
	{ 0x345U,236U,CnidsId000 },	/* 345 */
	{ 0x346U,237U,CnidsId000 },	/* 346 */
	{ 0x347U,238U,CnidsId000 },	/* 347 */
	{ 0x348U,239U,CnidsId000 },	/* 348 */
	{ 0x349U,240U,CnidsId000 },	/* 349 */
	{ 0x34CU,241U,CnidsId000 },	/* 34C */
	{ 0x34DU,242U,CnidsId000 },	/* 34D */
	{ 0x34EU,243U,CnidsId000 },	/* 34E */
	{ 0x34FU,244U,CnidsId000 },	/* 34F */
	{ 0x350U,245U,CnidsId000 },	/* 350 */
	{ 0x351U,246U,CnidsId000 },	/* 351 */
	{ 0x352U,247U,CnidsId000 },	/* 352 */
	{ 0x353U,248U,CnidsId000 },	/* 353 */
	{ 0x354U,249U,CnidsId000 },	/* 354 */
	{ 0x355U,250U,CnidsId000 },	/* 355 */
	{ 0x357U,251U,CnidsId000 },	/* 357 */
	{ 0x358U,252U,CnidsId000 },	/* 358 */
	{ 0x35AU,253U,CnidsId000 },	/* 35A */
	{ 0x35BU,254U,CnidsId000 },	/* 35B */
	{ 0x35DU,255U,CnidsId000 },	/* 35D */
	{ 0x35FU,256U,CnidsId000 },	/* 35F */
	{ 0x363U,257U,CnidsId000 },	/* 363 */
	{ 0x364U,258U,CnidsId000 },	/* 364 */
	{ 0x367U,259U,CnidsId000 },	/* 367 */
	{ 0x368U,260U,CnidsId000 },	/* 368 */
	{ 0x36AU,261U,CnidsId000 },	/* 36A */
	{ 0x36BU,262U,CnidsId000 },	/* 36B */
	{ 0x36EU,263U,CnidsId000 },	/* 36E */
	{ 0x36FU,264U,CnidsId000 },	/* 36F */
	{ 0x375U,265U,CnidsId000 },	/* 375 */
	{ 0x379U,266U,CnidsId000 },	/* 379 */
	{ 0x37BU,267U,CnidsId000 },	/* 37B */
	{ 0x37EU,268U,CnidsId000 },	/* 37E */
	{ 0x37FU,269U,CnidsId000 },	/* 37F */
	{ 0x380U,270U,CnidsId000 },	/* 380 */
	{ 0x381U,271U,CnidsId000 },	/* 381 */
	{ 0x382U,272U,CnidsId000 },	/* 382 */
	{ 0x384U,273U,CnidsId000 },	/* 384 */
	{ 0x385U,274U,CnidsId000 },	/* 385 */
	{ 0x386U,275U,CnidsId000 },	/* 386 */
	{ 0x387U,276U,CnidsId000 },	/* 387 */
	{ 0x388U,277U,CnidsId000 },	/* 388 */
	{ 0x389U,278U,CnidsId000 },	/* 389 */
	{ 0x38AU,279U,CnidsId000 },	/* 38A */
	{ 0x38BU,280U,CnidsId000 },	/* 38B */
	{ 0x38DU,281U,CnidsId000 },	/* 38D */
	{ 0x38EU,282U,CnidsId000 },	/* 38E */
	{ 0x38FU,283U,CnidsId000 },	/* 38F */
	{ 0x390U,284U,CnidsId000 },	/* 390 */
	{ 0x393U,285U,CnidsId000 },	/* 393 */
	{ 0x395U,286U,CnidsId000 },	/* 395 */
	{ 0x396U,287U,CnidsId000 },	/* 396 */
	{ 0x397U,288U,CnidsId000 },	/* 397 */
	{ 0x398U,289U,CnidsId000 },	/* 398 */
	{ 0x39AU,290U,CnidsId000 },	/* 39A */
	{ 0x39BU,291U,CnidsId000 },	/* 39B */
	{ 0x39CU,292U,CnidsId000 },	/* 39C */
	{ 0x39DU,293U,CnidsId000 },	/* 39D */
	{ 0x39EU,294U,CnidsId000 },	/* 39E */
	{ 0x39FU,295U,CnidsId000 },	/* 39F */
	{ 0x3A1U,296U,CnidsId000 },	/* 3A1 */
	{ 0x3A5U,297U,CnidsId000 },	/* 3A5 */
	{ 0x3A6U,298U,CnidsId000 },	/* 3A6 */
	{ 0x3A7U,299U,CnidsId000 },	/* 3A7 */
	{ 0x3A8U,300U,CnidsId000 },	/* 3A8 */
	{ 0x3A9U,301U,CnidsId000 },	/* 3A9 */
	{ 0x3ABU,302U,CnidsId000 },	/* 3AB */
	{ 0x3ACU,303U,CnidsId000 },	/* 3AC */
	{ 0x3AEU,304U,CnidsId000 },	/* 3AE */
	{ 0x3AFU,305U,CnidsId000 },	/* 3AF */
	{ 0x3B0U,306U,CnidsId000 },	/* 3B0 */
	{ 0x3B1U,307U,CnidsId000 },	/* 3B1 */
	{ 0x3B2U,308U,CnidsId000 },	/* 3B2 */
	{ 0x3B3U,309U,CnidsId000 },	/* 3B3 */
	{ 0x3B5U,310U,CnidsId000 },	/* 3B5 */
	{ 0x3B6U,311U,CnidsId000 },	/* 3B6 */
	{ 0x3B8U,312U,CnidsId000 },	/* 3B8 */
	{ 0x3B9U,313U,CnidsId000 },	/* 3B9 */
	{ 0x3BBU,314U,CnidsId000 },	/* 3BB */
	{ 0x3BCU,315U,CnidsId000 },	/* 3BC */
	{ 0x3BDU,316U,CnidsId000 },	/* 3BD */
	{ 0x3BEU,317U,CnidsId000 },	/* 3BE */
	{ 0x3BFU,318U,CnidsId000 },	/* 3BF */
	{ 0x3C0U,319U,CnidsId000 },	/* 3C0 */
	{ 0x3C2U,320U,CnidsId000 },	/* 3C2 */
	{ 0x3C4U,321U,CnidsId000 },	/* 3C4 */
	{ 0x3C6U,322U,CnidsId000 },	/* 3C6 */
	{ 0x3C7U,323U,CnidsId000 },	/* 3C7 */
	{ 0x3C8U,324U,CnidsId000 },	/* 3C8 */
	{ 0x3C9U,325U,CnidsId000 },	/* 3C9 */
	{ 0x3CAU,326U,CnidsId000 },	/* 3CA */
	{ 0x3CBU,327U,CnidsId000 },	/* 3CB */
	{ 0x3CDU,328U,CnidsId000 },	/* 3CD */
	{ 0x3D0U,329U,CnidsId000 },	/* 3D0 */
	{ 0x3D2U,330U,CnidsId000 },	/* 3D2 */
	{ 0x3D3U,331U,CnidsId000 },	/* 3D3 */
	{ 0x3D4U,332U,CnidsId000 },	/* 3D4 */
	{ 0x3D6U,333U,CnidsId000 },	/* 3D6 */
	{ 0x3D9U,334U,CnidsId000 },	/* 3D9 */
	{ 0x3DBU,335U,CnidsId000 },	/* 3DB */
	{ 0x3DCU,336U,CnidsId000 },	/* 3DC */
	{ 0x3DDU,337U,CnidsId000 },	/* 3DD */
	{ 0x3DEU,338U,CnidsId000 },	/* 3DE */
	{ 0x3E1U,339U,CnidsId000 },	/* 3E1 */
	{ 0x3E4U,340U,CnidsId000 },	/* 3E4 */
	{ 0x3E5U,341U,CnidsId000 },	/* 3E5 */
	{ 0x3E6U,342U,CnidsId000 },	/* 3E6 */
	{ 0x3E7U,343U,CnidsId000 },	/* 3E7 */
	{ 0x3EAU,344U,CnidsId000 },	/* 3EA */
	{ 0x3EBU,345U,CnidsId000 },	/* 3EB */
	{ 0x3ECU,346U,CnidsId000 },	/* 3EC */
	{ 0x3EEU,347U,CnidsId000 },	/* 3EE */
	{ 0x3EFU,348U,CnidsId000 },	/* 3EF */
	{ 0x3F0U,349U,CnidsId000 },	/* 3F0 */
	{ 0x3F1U,350U,CnidsId000 },	/* 3F1 */
	{ 0x3F2U,351U,CnidsId000 },	/* 3F2 */
	{ 0x3F3U,352U,CnidsId000 },	/* 3F3 */
	{ 0x3F5U,353U,CnidsId000 },	/* 3F5 */
	{ 0x3F6U,354U,CnidsId000 },	/* 3F6 */
	{ 0x3F7U,355U,CnidsId000 },	/* 3F7 */
	{ 0x3F9U,356U,CnidsId000 },	/* 3F9 */
	{ 0x3FBU,357U,CnidsId000 },	/* 3FB */
	{ 0x3FCU,358U,CnidsId000 },	/* 3FC */
	{ 0x3FDU,359U,CnidsId000 },	/* 3FD */
	{ 0x400U,360U,CnidsId000 },	/* 400 */
	{ 0x401U,361U,CnidsId000 },	/* 401 */
	{ 0x403U,362U,CnidsId000 },	/* 403 */
	{ 0x404U,363U,CnidsId000 },	/* 404 */
	{ 0x405U,364U,CnidsId000 },	/* 405 */
	{ 0x407U,365U,CnidsId000 },	/* 407 */
	{ 0x408U,366U,CnidsId000 },	/* 408 */
	{ 0x40BU,367U,CnidsId000 },	/* 40B */
	{ 0x40CU,368U,CnidsId000 },	/* 40C */
	{ 0x40DU,369U,CnidsId000 },	/* 40D */
	{ 0x40EU,370U,CnidsId000 },	/* 40E */
	{ 0x411U,371U,CnidsId000 },	/* 411 */
	{ 0x412U,372U,CnidsId000 },	/* 412 */
	{ 0x417U,373U,CnidsId000 },	/* 417 */
	{ 0x418U,374U,CnidsId000 },	/* 418 */
	{ 0x41AU,375U,CnidsId000 },	/* 41A */
	{ 0x421U,376U,CnidsId000 },	/* 421 */
	{ 0x422U,377U,CnidsId000 },	/* 422 */
	{ 0x423U,378U,CnidsId000 },	/* 423 */
	{ 0x426U,379U,CnidsId000 },	/* 426 */
	{ 0x427U,380U,CnidsId000 },	/* 427 */
	{ 0x428U,381U,CnidsId000 },	/* 428 */
	{ 0x429U,382U,CnidsId000 },	/* 429 */
	{ 0x42AU,383U,CnidsId000 },	/* 42A */
	{ 0x42BU,384U,CnidsId000 },	/* 42B */
	{ 0x42CU,385U,CnidsId000 },	/* 42C */
	{ 0x42EU,386U,CnidsId000 },	/* 42E */
	{ 0x42FU,387U,CnidsId000 },	/* 42F */
	{ 0x430U,388U,CnidsId000 },	/* 430 */
	{ 0x432U,389U,CnidsId000 },	/* 432 */
	{ 0x434U,390U,CnidsId000 },	/* 434 */
	{ 0x435U,391U,CnidsId000 },	/* 435 */
	{ 0x436U,392U,CnidsId000 },	/* 436 */
	{ 0x437U,393U,CnidsId000 },	/* 437 */
	{ 0x438U,394U,CnidsId000 },	/* 438 */
	{ 0x439U,395U,CnidsId000 },	/* 439 */
	{ 0x43AU,396U,CnidsId000 },	/* 43A */
	{ 0x43BU,397U,CnidsId000 },	/* 43B */
	{ 0x43EU,398U,CnidsId000 },	/* 43E */
	{ 0x442U,399U,CnidsId000 },	/* 442 */
	{ 0x480U,400U,CnidsId000 },	/* 480 */
	{ 0x484U,401U,CnidsId000 },	/* 484 */
	{ 0x489U,402U,CnidsId000 },	/* 489 */
	{ 0x48BU,403U,CnidsId000 },	/* 48B */
	{ 0x490U,404U,CnidsId000 },	/* 490 */
	{ 0x491U,405U,CnidsId000 },	/* 491 */
	{ 0x494U,406U,CnidsId000 },	/* 494 */
	{ 0x495U,407U,CnidsId000 },	/* 495 */
	{ 0x496U,408U,CnidsId000 },	/* 496 */
	{ 0x497U,409U,CnidsId000 },	/* 497 */
	{ 0x499U,410U,CnidsId000 },	/* 499 */
	{ 0x49AU,411U,CnidsId000 },	/* 49A */
	{ 0x49BU,412U,CnidsId000 },	/* 49B */
	{ 0x49DU,413U,CnidsId000 },	/* 49D */
	{ 0x4A0U,414U,CnidsId000 },	/* 4A0 */
	{ 0x4A1U,415U,CnidsId000 },	/* 4A1 */
	{ 0x4A3U,416U,CnidsId000 },	/* 4A3 */
	{ 0x4A4U,417U,CnidsId000 },	/* 4A4 */
	{ 0x4A8U,418U,CnidsId000 },	/* 4A8 */
	{ 0x4ACU,419U,CnidsId000 },	/* 4AC */
	{ 0x4AEU,420U,CnidsId000 },	/* 4AE */
	{ 0x4AFU,421U,CnidsId000 },	/* 4AF */
	{ 0x4B8U,422U,CnidsId000 },	/* 4B8 */
	{ 0x4BCU,423U,CnidsId000 },	/* 4BC */
	{ 0x500U,424U,CnidsId000 },	/* 500 */
	{ 0x506U,425U,CnidsId000 },	/* 506 */
	{ 0x507U,426U,CnidsId000 },	/* 507 */
	{ 0x515U,427U,CnidsId000 },	/* 515 */
	{ 0x51AU,428U,CnidsId000 },	/* 51A */
	{ 0x51BU,429U,CnidsId000 },	/* 51B */
	{ 0x51DU,430U,CnidsId000 },	/* 51D */
	{ 0x51EU,431U,CnidsId000 },	/* 51E */
	{ 0x51FU,432U,CnidsId000 },	/* 51F */
	{ 0x521U,433U,CnidsId000 },	/* 521 */
	{ 0x524U,434U,CnidsId000 },	/* 524 */
	{ 0x526U,435U,CnidsId000 },	/* 526 */
	{ 0x527U,436U,CnidsId000 },	/* 527 */
	{ 0x528U,437U,CnidsId000 },	/* 528 */
	{ 0x529U,438U,CnidsId000 },	/* 529 */
	{ 0x52AU,439U,CnidsId000 },	/* 52A */
	{ 0x52BU,440U,CnidsId000 },	/* 52B */
	{ 0x52CU,441U,CnidsId000 },	/* 52C */
	{ 0x530U,442U,CnidsId000 },	/* 530 */
	{ 0x531U,443U,CnidsId000 },	/* 531 */
	{ 0x532U,444U,CnidsId000 },	/* 532 */
	{ 0x534U,445U,CnidsId000 },	/* 534 */
	{ 0x535U,446U,CnidsId000 },	/* 535 */
	{ 0x537U,447U,CnidsId000 },	/* 537 */
	{ 0x538U,448U,CnidsId000 },	/* 538 */
	{ 0x56DU,449U,CnidsId000 },	/* 56D */
	{ 0x583U,450U,CnidsId000 },	/* 583 */
	{ 0x589U,451U,CnidsId000 },	/* 589 */
	{ 0x58AU,452U,CnidsId000 },	/* 58A */
	{ 0x58DU,453U,CnidsId000 },	/* 58D */
	{ 0x592U,454U,CnidsId000 },	/* 592 */
	{ 0x594U,455U,CnidsId000 },	/* 594 */
	{ 0x596U,456U,CnidsId000 },	/* 596 */
	{ 0x5F1U,457U,CnidsId000 },	/* 5F1 */
	{ 0x5F3U,458U,CnidsId000 },	/* 5F3 */
	{ 0x5F4U,459U,CnidsId000 },	/* 5F4 */
	{ 0x5F6U,460U,CnidsId000 },	/* 5F6 */
	{ 0x601U,461U,CnidsId000 },	/* 601 */
	{ 0x602U,462U,CnidsId000 },	/* 602 */
	{ 0x608U,463U,CnidsId000 },	/* 608 */
	{ 0x60CU,464U,CnidsId000 },	/* 60C */
	{ 0x610U,465U,CnidsId000 },	/* 610 */
	{ 0x611U,466U,CnidsId000 },	/* 611 */
	{ 0x613U,467U,CnidsId000 },	/* 613 */
	{ 0x614U,468U,CnidsId000 },	/* 614 */
	{ 0x615U,469U,CnidsId000 },	/* 615 */
	{ 0x618U,470U,CnidsId000 },	/* 618 */
	{ 0x621U,471U,CnidsId000 },	/* 621 */
	{ 0x622U,472U,CnidsId000 },	/* 622 */
	{ 0x623U,473U,CnidsId000 },	/* 623 */
	{ 0x624U,474U,CnidsId000 },	/* 624 */
	{ 0x626U,475U,CnidsId000 },	/* 626 */
	{ 0x629U,476U,CnidsId000 },	/* 629 */
	{ 0x62AU,477U,CnidsId000 },	/* 62A */
	{ 0x62CU,478U,CnidsId000 },	/* 62C */
	{ 0x633U,479U,CnidsId000 }	/* 633 */
};

/* 拡張CANID探索用テーブル */
CanidDataArraySet Cid_Data_CanId_Ex_UserTable[CID_SEARCHEX_MAX] = {
	{ 0x000U,0U,CnidsId00000000 }		/* dummy 0x000 */
};

#define GW_CID_STOP_SEC_CONST
#include "GW_Cid_Memmap.h"

