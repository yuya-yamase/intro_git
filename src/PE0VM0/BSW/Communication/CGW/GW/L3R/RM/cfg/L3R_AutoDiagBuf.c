/****************************************************************************/
/*	Copyright DENSO Corporation. All rights reserved.                       */
/****************************************************************************/
/*************************************************************************//**
 * @file		L3R_AutoDiagBuf.c
 * @brief		ダイアグバッファ制御
 * @details		ダイアグバッファの設定を行う。
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
 * @note            templates/L3R_AutoDiagBufC.tmpl
 * @note	ツールバージョン
 * @note		SMC_4.0.1
 ****************************************************************************/

/*--------------------------------------------------------------------------*/
/*		ファイルインクルード												*/
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"

#include "L3R_GwBuffer_cfg.h"

#include "L3R_DiagBuffer.h"
#include "L3R_DiagQueRouter.h"
#include "L3R_Fail.h"


/*--------------------------------------------------------------------------*/
/*		マクロ定義															*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		外部公開変数														*/
/*--------------------------------------------------------------------------*/
#define GW_L3R_START_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"
static CommonBufferFields DiagHdr000;
static CommonBufferFields DiagHdr001;
static CommonBufferFields DiagHdr002;
static CommonBufferFields DiagHdr003;
static CommonBufferFields DiagHdr004;
static CommonBufferFields DiagHdr005;
static CommonBufferFields DiagHdr006;
static CommonBufferFields DiagHdr007;
static CommonBufferFields DiagHdr008;
static CommonBufferFields DiagHdr009;
static CommonBufferFields DiagHdr010;
static CommonBufferFields DiagHdr011;
static CommonBufferFields DiagHdr012;
static CommonBufferFields DiagHdr013;
static CommonBufferFields DiagHdr014;
static CommonBufferFields DiagHdr015;
static CommonBufferFields DiagHdr016;
static CommonBufferFields DiagHdr017;
static CommonBufferFields DiagHdr018;
static CommonBufferFields DiagHdr019;
static CommonBufferFields DiagHdr020;
static CommonBufferFields DiagHdr021;
static CommonBufferFields DiagHdr022;
static CommonBufferFields DiagHdr023;
static CommonBufferFields DiagHdr024;
static CommonBufferFields DiagHdr025;
static CommonBufferFields DiagHdr026;
static CommonBufferFields DiagHdr027;
static CommonBufferFields DiagHdr028;
static CommonBufferFields DiagHdr029;
static CommonBufferFields DiagHdr030;
static CommonBufferFields DiagHdr031;
static CommonBufferFields DiagHdr032;
static CommonBufferFields DiagHdr033;
static CommonBufferFields DiagHdr034;
static CommonBufferFields DiagHdr035;
static CommonBufferFields DiagHdr036;
static CommonBufferFields DiagHdr037;
static CommonBufferFields DiagHdr038;
static CommonBufferFields DiagHdr039;
static CommonBufferFields DiagHdr040;
static CommonBufferFields DiagHdr041;
static CommonBufferFields DiagHdr042;
static CommonBufferFields DiagHdr043;
static CommonBufferFields DiagHdr044;
static CommonBufferFields DiagHdr045;
static CommonBufferFields DiagHdr046;
static CommonBufferFields DiagHdr047;
static CommonBufferFields DiagHdr048;
static CommonBufferFields DiagHdr049;
static CommonBufferFields DiagHdr050;
static CommonBufferFields DiagHdr051;
static CommonBufferFields DiagHdr052;
static CommonBufferFields DiagHdr053;
static CommonBufferFields DiagHdr054;
static CommonBufferFields DiagHdr055;
static CommonBufferFields DiagHdr056;
static CommonBufferFields DiagHdr057;
static CommonBufferFields DiagHdr058;
static CommonBufferFields DiagHdr059;
static CommonBufferFields DiagHdr060;
static CommonBufferFields DiagHdr061;
static CommonBufferFields DiagHdr062;
static CommonBufferFields DiagHdr063;
static CommonBufferFields DiagHdr064;
static CommonBufferFields DiagHdr065;
static CommonBufferFields DiagHdr066;
static CommonBufferFields DiagHdr067;
static CommonBufferFields DiagHdr068;
static CommonBufferFields DiagHdr069;
static CommonBufferFields DiagHdr070;
static CommonBufferFields DiagHdr071;
static CommonBufferFields DiagHdr072;
static CommonBufferFields DiagHdr073;
static CommonBufferFields DiagHdr074;
static CommonBufferFields DiagHdr075;
static CommonBufferFields DiagHdr076;
static CommonBufferFields DiagHdr077;
static CommonBufferFields DiagHdr078;
static CommonBufferFields DiagHdr079;
static CommonBufferFields DiagHdr080;
static CommonBufferFields DiagHdr081;
static CommonBufferFields DiagHdr082;
static CommonBufferFields DiagHdr083;
static CommonBufferFields DiagHdr084;
static CommonBufferFields DiagHdr085;
static CommonBufferFields DiagHdr086;
static CommonBufferFields DiagHdr087;
static CommonBufferFields DiagHdr088;
static CommonBufferFields DiagHdr089;
static CommonBufferFields DiagHdr090;
static CommonBufferFields DiagHdr091;
static CommonBufferFields DiagHdr092;
static CommonBufferFields DiagHdr093;
static CommonBufferFields DiagHdr094;
static CommonBufferFields DiagHdr095;
static CommonBufferFields DiagHdr096;
static CommonBufferFields DiagHdr097;
static CommonBufferFields DiagHdr098;
static CommonBufferFields DiagHdr099;
static CommonBufferFields DiagHdr100;
static CommonBufferFields DiagHdr101;
static CommonBufferFields DiagHdr102;
static CommonBufferFields DiagHdr103;
static CommonBufferFields DiagHdr104;
static CommonBufferFields DiagHdr105;
static CommonBufferFields DiagHdr106;
static CommonBufferFields DiagHdr107;
static CommonBufferFields DiagHdr108;
static CommonBufferFields DiagHdr109;
static CommonBufferFields DiagHdr110;
static CommonBufferFields DiagHdr111;
static CommonBufferFields DiagHdr112;
static CommonBufferFields DiagHdr113;
static CommonBufferFields DiagHdr114;
static CommonBufferFields DiagHdr115;
static CommonBufferFields DiagHdr116;
static CommonBufferFields DiagHdr117;
static CommonBufferFields DiagHdr118;
static CommonBufferFields DiagHdr119;
static CommonBufferFields DiagHdr120;
static CommonBufferFields DiagHdr121;
static CommonBufferFields DiagHdr122;
static CommonBufferFields DiagHdr123;
static CommonBufferFields DiagHdr124;
static CommonBufferFields DiagHdr125;
static CommonBufferFields DiagHdr126;
static CommonBufferFields DiagHdr127;
static CommonBufferFields DiagHdr128;
static CommonBufferFields DiagHdr129;
static CommonBufferFields DiagHdr130;
static CommonBufferFields DiagHdr131;
static CommonBufferFields DiagHdr132;
static CommonBufferFields DiagHdr133;
static CommonBufferFields DiagHdr134;
static CommonBufferFields DiagHdr135;
static CommonBufferFields DiagHdr136;
static CommonBufferFields DiagHdr137;
static CommonBufferFields DiagHdr138;
static CommonBufferFields DiagHdr139;
static CommonBufferFields DiagHdr140;
static CommonBufferFields DiagHdr141;
static CommonBufferFields DiagHdr142;
static CommonBufferFields DiagHdr143;
static CommonBufferFields DiagHdr144;
static CommonBufferFields DiagHdr145;
static CommonBufferFields DiagHdr146;
static CommonBufferFields DiagHdr147;
static CommonBufferFields DiagHdr148;
static CommonBufferFields DiagHdr149;
static CommonBufferFields DiagHdr150;
static CommonBufferFields DiagHdr151;
static CommonBufferFields DiagHdr152;
static CommonBufferFields DiagHdr153;
static CommonBufferFields DiagHdr154;
static CommonBufferFields DiagHdr155;
static CommonBufferFields DiagHdr156;
static CommonBufferFields DiagHdr157;
static CommonBufferFields DiagHdr158;
static CommonBufferFields DiagHdr159;
static CommonBufferFields DiagHdr160;
static CommonBufferFields DiagHdr161;
static CommonBufferFields DiagHdr162;
static CommonBufferFields DiagHdr163;
static CommonBufferFields DiagHdr164;
static CommonBufferFields DiagHdr165;
static CommonBufferFields DiagHdr166;
static CommonBufferFields DiagHdr167;
static CommonBufferFields DiagHdr168;
static CommonBufferFields DiagHdr169;
static CommonBufferFields DiagHdr170;
static CommonBufferFields DiagHdr171;
static CommonBufferFields DiagHdr172;
static CommonBufferFields DiagHdr173;
static CommonBufferFields DiagHdr174;
static CommonBufferFields DiagHdr175;
static CommonBufferFields DiagHdr176;
static CommonBufferFields DiagHdr177;
static CommonBufferFields DiagHdr178;
static CommonBufferFields DiagHdr179;
static CommonBufferFields DiagHdr180;
static CommonBufferFields DiagHdr181;
static CommonBufferFields DiagHdr182;
static CommonBufferFields DiagHdr183;
static CommonBufferFields DiagHdr184;
static CommonBufferFields DiagHdr185;
static CommonBufferFields DiagHdr186;
static CommonBufferFields DiagHdr187;
static CommonBufferFields DiagHdr188;
static CommonBufferFields DiagHdr189;
static CommonBufferFields DiagHdr190;
static CommonBufferFields DiagHdr191;
static CommonBufferFields DiagHdr192;
static CommonBufferFields DiagHdr193;
static CommonBufferFields DiagHdr194;
static CommonBufferFields DiagHdr195;
static CommonBufferFields DiagHdr196;
static CommonBufferFields DiagHdr197;
static CommonBufferFields DiagHdr198;
static CommonBufferFields DiagHdr199;
static CommonBufferFields DiagHdr200;
static CommonBufferFields DiagHdr201;
static CommonBufferFields DiagHdr202;
static CommonBufferFields DiagHdr203;
static CommonBufferFields DiagHdr204;
static CommonBufferFields DiagHdr205;
static CommonBufferFields DiagHdr206;
static CommonBufferFields DiagHdr207;
static CommonBufferFields DiagHdr208;
static CommonBufferFields DiagHdr209;
static CommonBufferFields DiagHdr210;
static CommonBufferFields DiagHdr211;
static CommonBufferFields DiagHdr212;
static CommonBufferFields DiagHdr213;
static CommonBufferFields DiagHdr214;
static CommonBufferFields DiagHdr215;
static CommonBufferFields DiagHdr216;
static CommonBufferFields DiagHdr217;
static CommonBufferFields DiagHdr218;
static CommonBufferFields DiagHdr219;
static CommonBufferFields DiagHdr220;
static CommonBufferFields DiagHdr221;
static CommonBufferFields DiagHdr222;
static CommonBufferFields DiagHdr223;
static CommonBufferFields DiagHdr224;
static CommonBufferFields DiagHdr225;
static CommonBufferFields DiagHdr226;
static CommonBufferFields DiagHdr227;
static CommonBufferFields DiagHdr228;
static CommonBufferFields DiagHdr229;
static CommonBufferFields DiagHdr230;
static CommonBufferFields DiagHdr231;
static CommonBufferFields DiagHdr232;
static CommonBufferFields DiagHdr233;
static CommonBufferFields DiagHdr234;
static CommonBufferFields DiagHdr235;
static CommonBufferFields DiagHdr236;
static CommonBufferFields DiagHdr237;
static CommonBufferFields DiagHdr238;
static CommonBufferFields DiagHdr239;
static CommonBufferFields DiagHdr240;
static CommonBufferFields DiagHdr241;
static CommonBufferFields DiagHdr242;
static CommonBufferFields DiagHdr243;
static CommonBufferFields DiagHdr244;
static CommonBufferFields DiagHdr245;
static CommonBufferFields DiagHdr246;
static CommonBufferFields DiagHdr247;
static CommonBufferFields DiagHdr248;
static CommonBufferFields DiagHdr249;
static CommonBufferFields DiagHdr250;
static CommonBufferFields DiagHdr251;
static CommonBufferFields DiagHdr252;
static CommonBufferFields DiagHdr253;
static CommonBufferFields DiagHdr254;
static CommonBufferFields DiagHdr255;
static CommonBufferFields DiagHdr256;
static CommonBufferFields DiagHdr257;
static CommonBufferFields DiagHdr258;
static CommonBufferFields DiagHdr259;
static CommonBufferFields DiagHdr260;
static CommonBufferFields DiagHdr261;
static CommonBufferFields DiagHdr262;
static CommonBufferFields DiagHdr263;
static CommonBufferFields DiagHdr264;
static CommonBufferFields DiagHdr265;
static CommonBufferFields DiagHdr266;
static CommonBufferFields DiagHdr267;
static CommonBufferFields DiagHdr268;
static CommonBufferFields DiagHdr269;
static CommonBufferFields DiagHdr270;
static CommonBufferFields DiagHdr271;
static CommonBufferFields DiagHdr272;
static CommonBufferFields DiagHdr273;
static CommonBufferFields DiagHdr274;
static CommonBufferFields DiagHdr275;
static CommonBufferFields DiagHdr276;
static CommonBufferFields DiagHdr277;
static CommonBufferFields DiagHdr278;
static CommonBufferFields DiagHdr279;
static CommonBufferFields DiagHdr280;
static CommonBufferFields DiagHdr281;
static CommonBufferFields DiagHdr282;
static CommonBufferFields DiagHdr283;
static CommonBufferFields DiagHdr284;
static CommonBufferFields DiagHdr285;
static CommonBufferFields DiagHdr286;
static CommonBufferFields DiagHdr287;
static CommonBufferFields DiagHdr288;
static CommonBufferFields DiagHdr289;
static CommonBufferFields DiagHdr290;
static CommonBufferFields DiagHdr291;
static CommonBufferFields DiagHdr292;
static CommonBufferFields DiagHdr293;
static CommonBufferFields DiagHdr294;
static CommonBufferFields DiagHdr295;
static CommonBufferFields DiagHdr296;
static CommonBufferFields DiagHdr297;
static CommonBufferFields DiagHdr298;
static CommonBufferFields DiagHdr299;
static CommonBufferFields DiagHdr300;
static CommonBufferFields DiagHdr301;
static CommonBufferFields DiagHdr302;
static CommonBufferFields DiagHdr303;
static CommonBufferFields DiagHdr304;
static CommonBufferFields DiagHdr305;
static CommonBufferFields DiagHdr306;
static CommonBufferFields DiagHdr307;
static CommonBufferFields DiagHdr308;
static CommonBufferFields DiagHdr309;
static CommonBufferFields DiagHdr310;
static CommonBufferFields DiagHdr311;
static CommonBufferFields DiagHdr312;
static CommonBufferFields DiagHdr313;
static CommonBufferFields DiagHdr314;
static CommonBufferFields DiagHdr315;
static CommonBufferFields DiagHdr316;
static CommonBufferFields DiagHdr317;
static CommonBufferFields DiagHdr318;
static CommonBufferFields DiagHdr319;
static CommonBufferFields DiagHdr320;
static CommonBufferFields DiagHdr321;
static CommonBufferFields DiagHdr322;
static CommonBufferFields DiagHdr323;
static CommonBufferFields DiagHdr324;
static CommonBufferFields DiagHdr325;
static CommonBufferFields DiagHdr326;
static CommonBufferFields DiagHdr327;
static CommonBufferFields DiagHdr328;
static CommonBufferFields DiagHdr329;
static CommonBufferFields DiagHdr330;
static CommonBufferFields DiagHdr331;
static CommonBufferFields DiagHdr332;
static CommonBufferFields DiagHdr333;
static CommonBufferFields DiagHdr334;
static CommonBufferFields DiagHdr335;
static CommonBufferFields DiagHdr336;
static CommonBufferFields DiagHdr337;
static CommonBufferFields DiagHdr338;
static CommonBufferFields DiagHdr339;
static CommonBufferFields DiagHdr340;
static CommonBufferFields DiagHdr341;
static CommonBufferFields DiagHdr342;
static CommonBufferFields DiagHdr343;
static CommonBufferFields DiagHdr344;
static CommonBufferFields DiagHdr345;
static CommonBufferFields DiagHdr346;
static CommonBufferFields DiagHdr347;
static CommonBufferFields DiagHdr348;
static CommonBufferFields DiagHdr349;
static CommonBufferFields DiagHdr350;
static CommonBufferFields DiagHdr351;
static CommonBufferFields DiagHdr352;
static CommonBufferFields DiagHdr353;
static CommonBufferFields DiagHdr354;
static CommonBufferFields DiagHdr355;
static CommonBufferFields DiagHdr356;
static CommonBufferFields DiagHdr357;
static CommonBufferFields DiagHdr358;
static CommonBufferFields DiagHdr359;
static CommonBufferFields DiagHdr360;
static CommonBufferFields DiagHdr361;
static CommonBufferFields DiagHdr362;
static CommonBufferFields DiagHdr363;
static CommonBufferFields DiagHdr364;
static CommonBufferFields DiagHdr365;
static CommonBufferFields DiagHdr366;
static CommonBufferFields DiagHdr367;
static CommonBufferFields DiagHdr368;
static CommonBufferFields DiagHdr369;
static CommonBufferFields DiagHdr370;
static CommonBufferFields DiagHdr371;
static CommonBufferFields DiagHdr372;
static CommonBufferFields DiagHdr373;
static CommonBufferFields DiagHdr374;
static CommonBufferFields DiagHdr375;
static CommonBufferFields DiagHdr376;
static CommonBufferFields DiagHdr377;
static CommonBufferFields DiagHdr378;
static CommonBufferFields DiagHdr379;
static CommonBufferFields DiagHdr380;
static CommonBufferFields DiagHdr381;
static CommonBufferFields DiagHdr382;
static CommonBufferFields DiagHdr383;
static CommonBufferFields DiagHdr384;
static CommonBufferFields DiagHdr385;
static CommonBufferFields DiagHdr386;
static CommonBufferFields DiagHdr387;
static CommonBufferFields DiagHdr388;
static CommonBufferFields DiagHdr389;
static CommonBufferFields DiagHdr390;
static CommonBufferFields DiagHdr391;
static CommonBufferFields DiagHdr392;
static CommonBufferFields DiagHdr393;
static CommonBufferFields DiagHdr394;
static CommonBufferFields DiagHdr395;
static CommonBufferFields DiagHdr396;
static CommonBufferFields DiagHdr397;
static CommonBufferFields DiagHdr398;
static CommonBufferFields DiagHdr399;
static CommonBufferFields DiagHdr400;
static CommonBufferFields DiagHdr401;
static CommonBufferFields DiagHdr402;
static CommonBufferFields DiagHdr403;
static CommonBufferFields DiagHdr404;
static CommonBufferFields DiagHdr405;
static CommonBufferFields DiagHdr406;
static CommonBufferFields DiagHdr407;
static CommonBufferFields DiagHdr408;
static CommonBufferFields DiagHdr409;
static CommonBufferFields DiagHdr410;
static CommonBufferFields DiagHdr411;
static CommonBufferFields DiagHdr412;
static CommonBufferFields DiagHdr413;
static CommonBufferFields DiagHdr414;
static CommonBufferFields DiagHdr415;
static CommonBufferFields DiagHdr416;
static CommonBufferFields DiagHdr417;
static CommonBufferFields DiagHdr418;
static CommonBufferFields DiagHdr419;
static CommonBufferFields DiagHdr420;
static CommonBufferFields DiagHdr421;
static CommonBufferFields DiagHdr422;
static CommonBufferFields DiagHdr423;
static CommonBufferFields DiagHdr424;
static CommonBufferFields DiagHdr425;
static CommonBufferFields DiagHdr426;
static CommonBufferFields DiagHdr427;
static CommonBufferFields DiagHdr428;
static CommonBufferFields DiagHdr429;
static CommonBufferFields DiagHdr430;
static CommonBufferFields DiagHdr431;
static CommonBufferFields DiagHdr432;
static CommonBufferFields DiagHdr433;
static CommonBufferFields DiagHdr434;
static CommonBufferFields DiagHdr435;
static CommonBufferFields DiagHdr436;
static CommonBufferFields DiagHdr437;
static CommonBufferFields DiagHdr438;
static CommonBufferFields DiagHdr439;
static CommonBufferFields DiagHdr440;
static CommonBufferFields DiagHdr441;
static CommonBufferFields DiagHdr442;
static CommonBufferFields DiagHdr443;
static CommonBufferFields DiagHdr444;
static CommonBufferFields DiagHdr445;
static CommonBufferFields DiagHdr446;
static CommonBufferFields DiagHdr447;
static CommonBufferFields DiagHdr448;
static CommonBufferFields DiagHdr449;
static CommonBufferFields DiagHdr450;
static CommonBufferFields DiagHdr451;
static CommonBufferFields DiagHdr452;
static CommonBufferFields DiagHdr453;
static CommonBufferFields DiagHdr454;
static CommonBufferFields DiagHdr455;
static CommonBufferFields DiagHdr456;
static CommonBufferFields DiagHdr457;
static CommonBufferFields DiagHdr458;
static CommonBufferFields DiagHdr459;
static CommonBufferFields DiagHdr460;
static CommonBufferFields DiagHdr461;
static CommonBufferFields DiagHdr462;
static CommonBufferFields DiagHdr463;
static CommonBufferFields DiagHdr464;
static CommonBufferFields DiagHdr465;
static CommonBufferFields DiagHdr466;
static CommonBufferFields DiagHdr467;
static CommonBufferFields DiagHdr468;
static CommonBufferFields DiagHdr469;
static CommonBufferFields DiagHdr470;
static CommonBufferFields DiagHdr471;
static CommonBufferFields DiagHdr472;
static CommonBufferFields DiagHdr473;
static CommonBufferFields DiagHdr474;
static CommonBufferFields DiagHdr475;
static CommonBufferFields DiagHdr476;
static CommonBufferFields DiagHdr477;
static CommonBufferFields DiagHdr478;
static CommonBufferFields DiagHdr479;
static CommonBufferFields DiagHdr480;
static CommonBufferFields DiagHdr481;
static CommonBufferFields DiagHdr482;
static CommonBufferFields DiagHdr483;
static CommonBufferFields DiagHdr484;
static CommonBufferFields DiagHdr485;
static CommonBufferFields DiagHdr486;
static CommonBufferFields DiagHdr487;
static CommonBufferFields DiagHdr488;
static CommonBufferFields DiagHdr489;
static CommonBufferFields DiagHdr490;
static CommonBufferFields DiagHdr491;
static CommonBufferFields DiagHdr492;
static CommonBufferFields DiagHdr493;
static CommonBufferFields DiagHdr494;
static CommonBufferFields DiagHdr495;
static CommonBufferFields DiagHdr496;
static CommonBufferFields DiagHdr497;
static CommonBufferFields DiagHdr498;
static CommonBufferFields DiagHdr499;
static CommonBufferFields DiagHdr500;
static CommonBufferFields DiagHdr501;
static CommonBufferFields DiagHdr502;
static CommonBufferFields DiagHdr503;
static CommonBufferFields DiagHdr504;
static CommonBufferFields DiagHdr505;
static CommonBufferFields DiagHdr506;
static CommonBufferFields DiagHdr507;
static CommonBufferFields DiagHdr508;
static CommonBufferFields DiagHdr509;
static CommonBufferFields DiagHdr510;
static CommonBufferFields DiagHdr511;
static CommonBufferFields DiagHdr512;
static CommonBufferFields DiagHdr513;
static CommonBufferFields DiagHdr514;
static CommonBufferFields DiagHdr515;
static CommonBufferFields DiagHdr516;
static CommonBufferFields DiagHdr517;
static CommonBufferFields DiagHdr518;
static CommonBufferFields DiagHdr519;
static CommonBufferFields DiagHdr520;
static CommonBufferFields DiagHdr521;
static CommonBufferFields DiagHdr522;
static CommonBufferFields DiagHdr523;
static CommonBufferFields DiagHdr524;
static CommonBufferFields DiagHdr525;
static CommonBufferFields DiagHdr526;
static CommonBufferFields DiagHdr527;
static CommonBufferFields DiagHdr528;
static CommonBufferFields DiagHdr529;
static CommonBufferFields DiagHdr530;
static CommonBufferFields DiagHdr531;
static CommonBufferFields DiagHdr532;
static CommonBufferFields DiagHdr533;
static CommonBufferFields DiagHdr534;
static CommonBufferFields DiagHdr535;
static CommonBufferFields DiagHdr536;
static CommonBufferFields DiagHdr537;
static CommonBufferFields DiagHdr538;
static CommonBufferFields DiagHdr539;
static CommonBufferFields DiagHdr540;
static CommonBufferFields DiagHdr541;
static CommonBufferFields DiagHdr542;
static CommonBufferFields DiagHdr543;
static CommonBufferFields DiagHdr544;
static CommonBufferFields DiagHdr545;
static CommonBufferFields DiagHdr546;
static CommonBufferFields DiagHdr547;
static CommonBufferFields DiagHdr548;
static CommonBufferFields DiagHdr549;
static CommonBufferFields DiagHdr550;
static CommonBufferFields DiagHdr551;
static CommonBufferFields DiagHdr552;
static CommonBufferFields DiagHdr553;
static CommonBufferFields DiagHdr554;
static CommonBufferFields DiagHdr555;
static CommonBufferFields DiagHdr556;
static CommonBufferFields DiagHdr557;
static CommonBufferFields DiagHdr558;
static CommonBufferFields DiagHdr559;
static CommonBufferFields DiagHdr560;
static CommonBufferFields DiagHdr561;
static CommonBufferFields DiagHdr562;
static CommonBufferFields DiagHdr563;
static CommonBufferFields DiagHdr564;
static CommonBufferFields DiagHdr565;
static CommonBufferFields DiagHdr566;
static CommonBufferFields DiagHdr567;
static CommonBufferFields DiagHdr568;
static CommonBufferFields DiagHdr569;
static CommonBufferFields DiagHdr570;
static CommonBufferFields DiagHdr571;
static CommonBufferFields DiagHdr572;
static CommonBufferFields DiagHdr573;
static CommonBufferFields DiagHdr574;
static CommonBufferFields DiagHdr575;
static CommonBufferFields DiagHdr576;
static CommonBufferFields DiagHdr577;
static CommonBufferFields DiagHdr578;
static CommonBufferFields DiagHdr579;
static CommonBufferFields DiagHdr580;
static CommonBufferFields DiagHdr581;
static CommonBufferFields DiagHdr582;
static CommonBufferFields DiagHdr583;
static CommonBufferFields DiagHdr584;
static CommonBufferFields DiagHdr585;
static CommonBufferFields DiagHdr586;
static CommonBufferFields DiagHdr587;
static CommonBufferFields DiagHdr588;
static CommonBufferFields DiagHdr589;
static CommonBufferFields DiagHdr590;
static CommonBufferFields DiagHdr591;
static CommonBufferFields DiagHdr592;
static CommonBufferFields DiagHdr593;
static CommonBufferFields DiagHdr594;
static CommonBufferFields DiagHdr595;
static CommonBufferFields DiagHdr596;
static CommonBufferFields DiagHdr597;
static CommonBufferFields DiagHdr598;
static CommonBufferFields DiagHdr599;
static CommonBufferFields DiagHdr600;
static CommonBufferFields DiagHdr601;
static CommonBufferFields DiagHdr602;
static CommonBufferFields DiagHdr603;
static CommonBufferFields DiagHdr604;
static CommonBufferFields DiagHdr605;
static CommonBufferFields DiagHdr606;
static CommonBufferFields DiagHdr607;
static CommonBufferFields DiagHdr608;
static CommonBufferFields DiagHdr609;
static CommonBufferFields DiagHdr610;
static CommonBufferFields DiagHdr611;
static CommonBufferFields DiagHdr612;
static CommonBufferFields DiagHdr613;
static CommonBufferFields DiagHdr614;
static CommonBufferFields DiagHdr615;
static CommonBufferFields DiagHdr616;
static CommonBufferFields DiagHdr617;
static CommonBufferFields DiagHdr618;
static CommonBufferFields DiagHdr619;
static CommonBufferFields DiagHdr620;
static CommonBufferFields DiagHdr621;
static CommonBufferFields DiagHdr622;
static CommonBufferFields DiagHdr623;
static CommonBufferFields DiagHdr624;
static CommonBufferFields DiagHdr625;
static CommonBufferFields DiagHdr626;
static CommonBufferFields DiagHdr627;
static CommonBufferFields DiagHdr628;
static CommonBufferFields DiagHdr629;
static CommonBufferFields DiagHdr630;
static CommonBufferFields DiagHdr631;
static CommonBufferFields DiagHdr632;
static CommonBufferFields DiagHdr633;
static CommonBufferFields DiagHdr634;
static CommonBufferFields DiagHdr635;
static CommonBufferFields DiagHdr636;
static CommonBufferFields DiagHdr637;
static CommonBufferFields DiagHdr638;
static CommonBufferFields DiagHdr639;
static CommonBufferFields DiagHdr640;
static CommonBufferFields DiagHdr641;
static CommonBufferFields DiagHdr642;
static CommonBufferFields DiagHdr643;
static CommonBufferFields DiagHdr644;
static CommonBufferFields DiagHdr645;
static CommonBufferFields DiagHdr646;
static CommonBufferFields DiagHdr647;
static CommonBufferFields DiagHdr648;
static CommonBufferFields DiagHdr649;
static CommonBufferFields DiagHdr650;
static CommonBufferFields DiagHdr651;
static CommonBufferFields DiagHdr652;
static CommonBufferFields DiagHdr653;
static CommonBufferFields DiagHdr654;
static CommonBufferFields DiagHdr655;
static CommonBufferFields DiagHdr656;
static CommonBufferFields DiagHdr657;
static CommonBufferFields DiagHdr658;
static CommonBufferFields DiagHdr659;
static CommonBufferFields DiagHdr660;
static CommonBufferFields DiagHdr661;
static CommonBufferFields DiagHdr662;
static CommonBufferFields DiagHdr663;
static CommonBufferFields DiagHdr664;
static CommonBufferFields DiagHdr665;
static CommonBufferFields DiagHdr666;
static CommonBufferFields DiagHdr667;
static CommonBufferFields DiagHdr668;
static CommonBufferFields DiagHdr669;
static CommonBufferFields DiagHdr670;
static CommonBufferFields DiagHdr671;
static CommonBufferFields DiagHdr672;
static CommonBufferFields DiagHdr673;
static CommonBufferFields DiagHdr674;
static CommonBufferFields DiagHdr675;
static CommonBufferFields DiagHdr676;
static CommonBufferFields DiagHdr677;
static CommonBufferFields DiagHdr678;
static CommonBufferFields DiagHdr679;
static CommonBufferFields DiagHdr680;
static CommonBufferFields DiagHdr681;


static uint8 DiagData000[L3R_DIAG_DATASIZE];
static uint8 DiagData001[L3R_DIAG_DATASIZE];
static uint8 DiagData002[L3R_DIAG_DATASIZE];
static uint8 DiagData003[L3R_DIAG_DATASIZE];
static uint8 DiagData004[L3R_DIAG_DATASIZE];
static uint8 DiagData005[L3R_DIAG_DATASIZE];
static uint8 DiagData006[L3R_DIAG_DATASIZE];
static uint8 DiagData007[L3R_DIAG_DATASIZE];
static uint8 DiagData008[L3R_DIAG_DATASIZE];
static uint8 DiagData009[L3R_DIAG_DATASIZE];
static uint8 DiagData010[L3R_DIAG_DATASIZE];
static uint8 DiagData011[L3R_DIAG_DATASIZE];
static uint8 DiagData012[L3R_DIAG_DATASIZE];
static uint8 DiagData013[L3R_DIAG_DATASIZE];
static uint8 DiagData014[L3R_DIAG_DATASIZE];
static uint8 DiagData015[L3R_DIAG_DATASIZE];
static uint8 DiagData016[L3R_DIAG_DATASIZE];
static uint8 DiagData017[L3R_DIAG_DATASIZE];
static uint8 DiagData018[L3R_DIAG_DATASIZE];
static uint8 DiagData019[L3R_DIAG_DATASIZE];
static uint8 DiagData020[L3R_DIAG_DATASIZE];
static uint8 DiagData021[L3R_DIAG_DATASIZE];
static uint8 DiagData022[L3R_DIAG_DATASIZE];
static uint8 DiagData023[L3R_DIAG_DATASIZE];
static uint8 DiagData024[L3R_DIAG_DATASIZE];
static uint8 DiagData025[L3R_DIAG_DATASIZE];
static uint8 DiagData026[L3R_DIAG_DATASIZE];
static uint8 DiagData027[L3R_DIAG_DATASIZE];
static uint8 DiagData028[L3R_DIAG_DATASIZE];
static uint8 DiagData029[L3R_DIAG_DATASIZE];
static uint8 DiagData030[L3R_DIAG_DATASIZE];
static uint8 DiagData031[L3R_DIAG_DATASIZE];
static uint8 DiagData032[L3R_DIAG_DATASIZE];
static uint8 DiagData033[L3R_DIAG_DATASIZE];
static uint8 DiagData034[L3R_DIAG_DATASIZE];
static uint8 DiagData035[L3R_DIAG_DATASIZE];
static uint8 DiagData036[L3R_DIAG_DATASIZE];
static uint8 DiagData037[L3R_DIAG_DATASIZE];
static uint8 DiagData038[L3R_DIAG_DATASIZE];
static uint8 DiagData039[L3R_DIAG_DATASIZE];
static uint8 DiagData040[L3R_DIAG_DATASIZE];
static uint8 DiagData041[L3R_DIAG_DATASIZE];
static uint8 DiagData042[L3R_DIAG_DATASIZE];
static uint8 DiagData043[L3R_DIAG_DATASIZE];
static uint8 DiagData044[L3R_DIAG_DATASIZE];
static uint8 DiagData045[L3R_DIAG_DATASIZE];
static uint8 DiagData046[L3R_DIAG_DATASIZE];
static uint8 DiagData047[L3R_DIAG_DATASIZE];
static uint8 DiagData048[L3R_DIAG_DATASIZE];
static uint8 DiagData049[L3R_DIAG_DATASIZE];
static uint8 DiagData050[L3R_DIAG_DATASIZE];
static uint8 DiagData051[L3R_DIAG_DATASIZE];
static uint8 DiagData052[L3R_DIAG_DATASIZE];
static uint8 DiagData053[L3R_DIAG_DATASIZE];
static uint8 DiagData054[L3R_DIAG_DATASIZE];
static uint8 DiagData055[L3R_DIAG_DATASIZE];
static uint8 DiagData056[L3R_DIAG_DATASIZE];
static uint8 DiagData057[L3R_DIAG_DATASIZE];
static uint8 DiagData058[L3R_DIAG_DATASIZE];
static uint8 DiagData059[L3R_DIAG_DATASIZE];
static uint8 DiagData060[L3R_DIAG_DATASIZE];
static uint8 DiagData061[L3R_DIAG_DATASIZE];
static uint8 DiagData062[L3R_DIAG_DATASIZE];
static uint8 DiagData063[L3R_DIAG_DATASIZE];
static uint8 DiagData064[L3R_DIAG_DATASIZE];
static uint8 DiagData065[L3R_DIAG_DATASIZE];
static uint8 DiagData066[L3R_DIAG_DATASIZE];
static uint8 DiagData067[L3R_DIAG_DATASIZE];
static uint8 DiagData068[L3R_DIAG_DATASIZE];
static uint8 DiagData069[L3R_DIAG_DATASIZE];
static uint8 DiagData070[L3R_DIAG_DATASIZE];
static uint8 DiagData071[L3R_DIAG_DATASIZE];
static uint8 DiagData072[L3R_DIAG_DATASIZE];
static uint8 DiagData073[L3R_DIAG_DATASIZE];
static uint8 DiagData074[L3R_DIAG_DATASIZE];
static uint8 DiagData075[L3R_DIAG_DATASIZE];
static uint8 DiagData076[L3R_DIAG_DATASIZE];
static uint8 DiagData077[L3R_DIAG_DATASIZE];
static uint8 DiagData078[L3R_DIAG_DATASIZE];
static uint8 DiagData079[L3R_DIAG_DATASIZE];
static uint8 DiagData080[L3R_DIAG_DATASIZE];
static uint8 DiagData081[L3R_DIAG_DATASIZE];
static uint8 DiagData082[L3R_DIAG_DATASIZE];
static uint8 DiagData083[L3R_DIAG_DATASIZE];
static uint8 DiagData084[L3R_DIAG_DATASIZE];
static uint8 DiagData085[L3R_DIAG_DATASIZE];
static uint8 DiagData086[L3R_DIAG_DATASIZE];
static uint8 DiagData087[L3R_DIAG_DATASIZE];
static uint8 DiagData088[L3R_DIAG_DATASIZE];
static uint8 DiagData089[L3R_DIAG_DATASIZE];
static uint8 DiagData090[L3R_DIAG_DATASIZE];
static uint8 DiagData091[L3R_DIAG_DATASIZE];
static uint8 DiagData092[L3R_DIAG_DATASIZE];
static uint8 DiagData093[L3R_DIAG_DATASIZE];
static uint8 DiagData094[L3R_DIAG_DATASIZE];
static uint8 DiagData095[L3R_DIAG_DATASIZE];
static uint8 DiagData096[L3R_DIAG_DATASIZE];
static uint8 DiagData097[L3R_DIAG_DATASIZE];
static uint8 DiagData098[L3R_DIAG_DATASIZE];
static uint8 DiagData099[L3R_DIAG_DATASIZE];
static uint8 DiagData100[L3R_DIAG_DATASIZE];
static uint8 DiagData101[L3R_DIAG_DATASIZE];
static uint8 DiagData102[L3R_DIAG_DATASIZE];
static uint8 DiagData103[L3R_DIAG_DATASIZE];
static uint8 DiagData104[L3R_DIAG_DATASIZE];
static uint8 DiagData105[L3R_DIAG_DATASIZE];
static uint8 DiagData106[L3R_DIAG_DATASIZE];
static uint8 DiagData107[L3R_DIAG_DATASIZE];
static uint8 DiagData108[L3R_DIAG_DATASIZE];
static uint8 DiagData109[L3R_DIAG_DATASIZE];
static uint8 DiagData110[L3R_DIAG_DATASIZE];
static uint8 DiagData111[L3R_DIAG_DATASIZE];
static uint8 DiagData112[L3R_DIAG_DATASIZE];
static uint8 DiagData113[L3R_DIAG_DATASIZE];
static uint8 DiagData114[L3R_DIAG_DATASIZE];
static uint8 DiagData115[L3R_DIAG_DATASIZE];
static uint8 DiagData116[L3R_DIAG_DATASIZE];
static uint8 DiagData117[L3R_DIAG_DATASIZE];
static uint8 DiagData118[L3R_DIAG_DATASIZE];
static uint8 DiagData119[L3R_DIAG_DATASIZE];
static uint8 DiagData120[L3R_DIAG_DATASIZE];
static uint8 DiagData121[L3R_DIAG_DATASIZE];
static uint8 DiagData122[L3R_DIAG_DATASIZE];
static uint8 DiagData123[L3R_DIAG_DATASIZE];
static uint8 DiagData124[L3R_DIAG_DATASIZE];
static uint8 DiagData125[L3R_DIAG_DATASIZE];
static uint8 DiagData126[L3R_DIAG_DATASIZE];
static uint8 DiagData127[L3R_DIAG_DATASIZE];
static uint8 DiagData128[L3R_DIAG_DATASIZE];
static uint8 DiagData129[L3R_DIAG_DATASIZE];
static uint8 DiagData130[L3R_DIAG_DATASIZE];
static uint8 DiagData131[L3R_DIAG_DATASIZE];
static uint8 DiagData132[L3R_DIAG_DATASIZE];
static uint8 DiagData133[L3R_DIAG_DATASIZE];
static uint8 DiagData134[L3R_DIAG_DATASIZE];
static uint8 DiagData135[L3R_DIAG_DATASIZE];
static uint8 DiagData136[L3R_DIAG_DATASIZE];
static uint8 DiagData137[L3R_DIAG_DATASIZE];
static uint8 DiagData138[L3R_DIAG_DATASIZE];
static uint8 DiagData139[L3R_DIAG_DATASIZE];
static uint8 DiagData140[L3R_DIAG_DATASIZE];
static uint8 DiagData141[L3R_DIAG_DATASIZE];
static uint8 DiagData142[L3R_DIAG_DATASIZE];
static uint8 DiagData143[L3R_DIAG_DATASIZE];
static uint8 DiagData144[L3R_DIAG_DATASIZE];
static uint8 DiagData145[L3R_DIAG_DATASIZE];
static uint8 DiagData146[L3R_DIAG_DATASIZE];
static uint8 DiagData147[L3R_DIAG_DATASIZE];
static uint8 DiagData148[L3R_DIAG_DATASIZE];
static uint8 DiagData149[L3R_DIAG_DATASIZE];
static uint8 DiagData150[L3R_DIAG_DATASIZE];
static uint8 DiagData151[L3R_DIAG_DATASIZE];
static uint8 DiagData152[L3R_DIAG_DATASIZE];
static uint8 DiagData153[L3R_DIAG_DATASIZE];
static uint8 DiagData154[L3R_DIAG_DATASIZE];
static uint8 DiagData155[L3R_DIAG_DATASIZE];
static uint8 DiagData156[L3R_DIAG_DATASIZE];
static uint8 DiagData157[L3R_DIAG_DATASIZE];
static uint8 DiagData158[L3R_DIAG_DATASIZE];
static uint8 DiagData159[L3R_DIAG_DATASIZE];
static uint8 DiagData160[L3R_DIAG_DATASIZE];
static uint8 DiagData161[L3R_DIAG_DATASIZE];
static uint8 DiagData162[L3R_DIAG_DATASIZE];
static uint8 DiagData163[L3R_DIAG_DATASIZE];
static uint8 DiagData164[L3R_DIAG_DATASIZE];
static uint8 DiagData165[L3R_DIAG_DATASIZE];
static uint8 DiagData166[L3R_DIAG_DATASIZE];
static uint8 DiagData167[L3R_DIAG_DATASIZE];
static uint8 DiagData168[L3R_DIAG_DATASIZE];
static uint8 DiagData169[L3R_DIAG_DATASIZE];
static uint8 DiagData170[L3R_DIAG_DATASIZE];
static uint8 DiagData171[L3R_DIAG_DATASIZE];
static uint8 DiagData172[L3R_DIAG_DATASIZE];
static uint8 DiagData173[L3R_DIAG_DATASIZE];
static uint8 DiagData174[L3R_DIAG_DATASIZE];
static uint8 DiagData175[L3R_DIAG_DATASIZE];
static uint8 DiagData176[L3R_DIAG_DATASIZE];
static uint8 DiagData177[L3R_DIAG_DATASIZE];
static uint8 DiagData178[L3R_DIAG_DATASIZE];
static uint8 DiagData179[L3R_DIAG_DATASIZE];
static uint8 DiagData180[L3R_DIAG_DATASIZE];
static uint8 DiagData181[L3R_DIAG_DATASIZE];
static uint8 DiagData182[L3R_DIAG_DATASIZE];
static uint8 DiagData183[L3R_DIAG_DATASIZE];
static uint8 DiagData184[L3R_DIAG_DATASIZE];
static uint8 DiagData185[L3R_DIAG_DATASIZE];
static uint8 DiagData186[L3R_DIAG_DATASIZE];
static uint8 DiagData187[L3R_DIAG_DATASIZE];
static uint8 DiagData188[L3R_DIAG_DATASIZE];
static uint8 DiagData189[L3R_DIAG_DATASIZE];
static uint8 DiagData190[L3R_DIAG_DATASIZE];
static uint8 DiagData191[L3R_DIAG_DATASIZE];
static uint8 DiagData192[L3R_DIAG_DATASIZE];
static uint8 DiagData193[L3R_DIAG_DATASIZE];
static uint8 DiagData194[L3R_DIAG_DATASIZE];
static uint8 DiagData195[L3R_DIAG_DATASIZE];
static uint8 DiagData196[L3R_DIAG_DATASIZE];
static uint8 DiagData197[L3R_DIAG_DATASIZE];
static uint8 DiagData198[L3R_DIAG_DATASIZE];
static uint8 DiagData199[L3R_DIAG_DATASIZE];
static uint8 DiagData200[L3R_DIAG_DATASIZE];
static uint8 DiagData201[L3R_DIAG_DATASIZE];
static uint8 DiagData202[L3R_DIAG_DATASIZE];
static uint8 DiagData203[L3R_DIAG_DATASIZE];
static uint8 DiagData204[L3R_DIAG_DATASIZE];
static uint8 DiagData205[L3R_DIAG_DATASIZE];
static uint8 DiagData206[L3R_DIAG_DATASIZE];
static uint8 DiagData207[L3R_DIAG_DATASIZE];
static uint8 DiagData208[L3R_DIAG_DATASIZE];
static uint8 DiagData209[L3R_DIAG_DATASIZE];
static uint8 DiagData210[L3R_DIAG_DATASIZE];
static uint8 DiagData211[L3R_DIAG_DATASIZE];
static uint8 DiagData212[L3R_DIAG_DATASIZE];
static uint8 DiagData213[L3R_DIAG_DATASIZE];
static uint8 DiagData214[L3R_DIAG_DATASIZE];
static uint8 DiagData215[L3R_DIAG_DATASIZE];
static uint8 DiagData216[L3R_DIAG_DATASIZE];
static uint8 DiagData217[L3R_DIAG_DATASIZE];
static uint8 DiagData218[L3R_DIAG_DATASIZE];
static uint8 DiagData219[L3R_DIAG_DATASIZE];
static uint8 DiagData220[L3R_DIAG_DATASIZE];
static uint8 DiagData221[L3R_DIAG_DATASIZE];
static uint8 DiagData222[L3R_DIAG_DATASIZE];
static uint8 DiagData223[L3R_DIAG_DATASIZE];
static uint8 DiagData224[L3R_DIAG_DATASIZE];
static uint8 DiagData225[L3R_DIAG_DATASIZE];
static uint8 DiagData226[L3R_DIAG_DATASIZE];
static uint8 DiagData227[L3R_DIAG_DATASIZE];
static uint8 DiagData228[L3R_DIAG_DATASIZE];
static uint8 DiagData229[L3R_DIAG_DATASIZE];
static uint8 DiagData230[L3R_DIAG_DATASIZE];
static uint8 DiagData231[L3R_DIAG_DATASIZE];
static uint8 DiagData232[L3R_DIAG_DATASIZE];
static uint8 DiagData233[L3R_DIAG_DATASIZE];
static uint8 DiagData234[L3R_DIAG_DATASIZE];
static uint8 DiagData235[L3R_DIAG_DATASIZE];
static uint8 DiagData236[L3R_DIAG_DATASIZE];
static uint8 DiagData237[L3R_DIAG_DATASIZE];
static uint8 DiagData238[L3R_DIAG_DATASIZE];
static uint8 DiagData239[L3R_DIAG_DATASIZE];
static uint8 DiagData240[L3R_DIAG_DATASIZE];
static uint8 DiagData241[L3R_DIAG_DATASIZE];
static uint8 DiagData242[L3R_DIAG_DATASIZE];
static uint8 DiagData243[L3R_DIAG_DATASIZE];
static uint8 DiagData244[L3R_DIAG_DATASIZE];
static uint8 DiagData245[L3R_DIAG_DATASIZE];
static uint8 DiagData246[L3R_DIAG_DATASIZE];
static uint8 DiagData247[L3R_DIAG_DATASIZE];
static uint8 DiagData248[L3R_DIAG_DATASIZE];
static uint8 DiagData249[L3R_DIAG_DATASIZE];
static uint8 DiagData250[L3R_DIAG_DATASIZE];
static uint8 DiagData251[L3R_DIAG_DATASIZE];
static uint8 DiagData252[L3R_DIAG_DATASIZE];
static uint8 DiagData253[L3R_DIAG_DATASIZE];
static uint8 DiagData254[L3R_DIAG_DATASIZE];
static uint8 DiagData255[L3R_DIAG_DATASIZE];
static uint8 DiagData256[L3R_DIAG_DATASIZE];
static uint8 DiagData257[L3R_DIAG_DATASIZE];
static uint8 DiagData258[L3R_DIAG_DATASIZE];
static uint8 DiagData259[L3R_DIAG_DATASIZE];
static uint8 DiagData260[L3R_DIAG_DATASIZE];
static uint8 DiagData261[L3R_DIAG_DATASIZE];
static uint8 DiagData262[L3R_DIAG_DATASIZE];
static uint8 DiagData263[L3R_DIAG_DATASIZE];
static uint8 DiagData264[L3R_DIAG_DATASIZE];
static uint8 DiagData265[L3R_DIAG_DATASIZE];
static uint8 DiagData266[L3R_DIAG_DATASIZE];
static uint8 DiagData267[L3R_DIAG_DATASIZE];
static uint8 DiagData268[L3R_DIAG_DATASIZE];
static uint8 DiagData269[L3R_DIAG_DATASIZE];
static uint8 DiagData270[L3R_DIAG_DATASIZE];
static uint8 DiagData271[L3R_DIAG_DATASIZE];
static uint8 DiagData272[L3R_DIAG_DATASIZE];
static uint8 DiagData273[L3R_DIAG_DATASIZE];
static uint8 DiagData274[L3R_DIAG_DATASIZE];
static uint8 DiagData275[L3R_DIAG_DATASIZE];
static uint8 DiagData276[L3R_DIAG_DATASIZE];
static uint8 DiagData277[L3R_DIAG_DATASIZE];
static uint8 DiagData278[L3R_DIAG_DATASIZE];
static uint8 DiagData279[L3R_DIAG_DATASIZE];
static uint8 DiagData280[L3R_DIAG_DATASIZE];
static uint8 DiagData281[L3R_DIAG_DATASIZE];
static uint8 DiagData282[L3R_DIAG_DATASIZE];
static uint8 DiagData283[L3R_DIAG_DATASIZE];
static uint8 DiagData284[L3R_DIAG_DATASIZE];
static uint8 DiagData285[L3R_DIAG_DATASIZE];
static uint8 DiagData286[L3R_DIAG_DATASIZE];
static uint8 DiagData287[L3R_DIAG_DATASIZE];
static uint8 DiagData288[L3R_DIAG_DATASIZE];
static uint8 DiagData289[L3R_DIAG_DATASIZE];
static uint8 DiagData290[L3R_DIAG_DATASIZE];
static uint8 DiagData291[L3R_DIAG_DATASIZE];
static uint8 DiagData292[L3R_DIAG_DATASIZE];
static uint8 DiagData293[L3R_DIAG_DATASIZE];
static uint8 DiagData294[L3R_DIAG_DATASIZE];
static uint8 DiagData295[L3R_DIAG_DATASIZE];
static uint8 DiagData296[L3R_DIAG_DATASIZE];
static uint8 DiagData297[L3R_DIAG_DATASIZE];
static uint8 DiagData298[L3R_DIAG_DATASIZE];
static uint8 DiagData299[L3R_DIAG_DATASIZE];
static uint8 DiagData300[L3R_DIAG_DATASIZE];
static uint8 DiagData301[L3R_DIAG_DATASIZE];
static uint8 DiagData302[L3R_DIAG_DATASIZE];
static uint8 DiagData303[L3R_DIAG_DATASIZE];
static uint8 DiagData304[L3R_DIAG_DATASIZE];
static uint8 DiagData305[L3R_DIAG_DATASIZE];
static uint8 DiagData306[L3R_DIAG_DATASIZE];
static uint8 DiagData307[L3R_DIAG_DATASIZE];
static uint8 DiagData308[L3R_DIAG_DATASIZE];
static uint8 DiagData309[L3R_DIAG_DATASIZE];
static uint8 DiagData310[L3R_DIAG_DATASIZE];
static uint8 DiagData311[L3R_DIAG_DATASIZE];
static uint8 DiagData312[L3R_DIAG_DATASIZE];
static uint8 DiagData313[L3R_DIAG_DATASIZE];
static uint8 DiagData314[L3R_DIAG_DATASIZE];
static uint8 DiagData315[L3R_DIAG_DATASIZE];
static uint8 DiagData316[L3R_DIAG_DATASIZE];
static uint8 DiagData317[L3R_DIAG_DATASIZE];
static uint8 DiagData318[L3R_DIAG_DATASIZE];
static uint8 DiagData319[L3R_DIAG_DATASIZE];
static uint8 DiagData320[L3R_DIAG_DATASIZE];
static uint8 DiagData321[L3R_DIAG_DATASIZE];
static uint8 DiagData322[L3R_DIAG_DATASIZE];
static uint8 DiagData323[L3R_DIAG_DATASIZE];
static uint8 DiagData324[L3R_DIAG_DATASIZE];
static uint8 DiagData325[L3R_DIAG_DATASIZE];
static uint8 DiagData326[L3R_DIAG_DATASIZE];
static uint8 DiagData327[L3R_DIAG_DATASIZE];
static uint8 DiagData328[L3R_DIAG_DATASIZE];
static uint8 DiagData329[L3R_DIAG_DATASIZE];
static uint8 DiagData330[L3R_DIAG_DATASIZE];
static uint8 DiagData331[L3R_DIAG_DATASIZE];
static uint8 DiagData332[L3R_DIAG_DATASIZE];
static uint8 DiagData333[L3R_DIAG_DATASIZE];
static uint8 DiagData334[L3R_DIAG_DATASIZE];
static uint8 DiagData335[L3R_DIAG_DATASIZE];
static uint8 DiagData336[L3R_DIAG_DATASIZE];
static uint8 DiagData337[L3R_DIAG_DATASIZE];
static uint8 DiagData338[L3R_DIAG_DATASIZE];
static uint8 DiagData339[L3R_DIAG_DATASIZE];
static uint8 DiagData340[L3R_DIAG_DATASIZE];
static uint8 DiagData341[L3R_DIAG_DATASIZE];
static uint8 DiagData342[L3R_DIAG_DATASIZE];
static uint8 DiagData343[L3R_DIAG_DATASIZE];
static uint8 DiagData344[L3R_DIAG_DATASIZE];
static uint8 DiagData345[L3R_DIAG_DATASIZE];
static uint8 DiagData346[L3R_DIAG_DATASIZE];
static uint8 DiagData347[L3R_DIAG_DATASIZE];
static uint8 DiagData348[L3R_DIAG_DATASIZE];
static uint8 DiagData349[L3R_DIAG_DATASIZE];
static uint8 DiagData350[L3R_DIAG_DATASIZE];
static uint8 DiagData351[L3R_DIAG_DATASIZE];
static uint8 DiagData352[L3R_DIAG_DATASIZE];
static uint8 DiagData353[L3R_DIAG_DATASIZE];
static uint8 DiagData354[L3R_DIAG_DATASIZE];
static uint8 DiagData355[L3R_DIAG_DATASIZE];
static uint8 DiagData356[L3R_DIAG_DATASIZE];
static uint8 DiagData357[L3R_DIAG_DATASIZE];
static uint8 DiagData358[L3R_DIAG_DATASIZE];
static uint8 DiagData359[L3R_DIAG_DATASIZE];
static uint8 DiagData360[L3R_DIAG_DATASIZE];
static uint8 DiagData361[L3R_DIAG_DATASIZE];
static uint8 DiagData362[L3R_DIAG_DATASIZE];
static uint8 DiagData363[L3R_DIAG_DATASIZE];
static uint8 DiagData364[L3R_DIAG_DATASIZE];
static uint8 DiagData365[L3R_DIAG_DATASIZE];
static uint8 DiagData366[L3R_DIAG_DATASIZE];
static uint8 DiagData367[L3R_DIAG_DATASIZE];
static uint8 DiagData368[L3R_DIAG_DATASIZE];
static uint8 DiagData369[L3R_DIAG_DATASIZE];
static uint8 DiagData370[L3R_DIAG_DATASIZE];
static uint8 DiagData371[L3R_DIAG_DATASIZE];
static uint8 DiagData372[L3R_DIAG_DATASIZE];
static uint8 DiagData373[L3R_DIAG_DATASIZE];
static uint8 DiagData374[L3R_DIAG_DATASIZE];
static uint8 DiagData375[L3R_DIAG_DATASIZE];
static uint8 DiagData376[L3R_DIAG_DATASIZE];
static uint8 DiagData377[L3R_DIAG_DATASIZE];
static uint8 DiagData378[L3R_DIAG_DATASIZE];
static uint8 DiagData379[L3R_DIAG_DATASIZE];
static uint8 DiagData380[L3R_DIAG_DATASIZE];
static uint8 DiagData381[L3R_DIAG_DATASIZE];
static uint8 DiagData382[L3R_DIAG_DATASIZE];
static uint8 DiagData383[L3R_DIAG_DATASIZE];
static uint8 DiagData384[L3R_DIAG_DATASIZE];
static uint8 DiagData385[L3R_DIAG_DATASIZE];
static uint8 DiagData386[L3R_DIAG_DATASIZE];
static uint8 DiagData387[L3R_DIAG_DATASIZE];
static uint8 DiagData388[L3R_DIAG_DATASIZE];
static uint8 DiagData389[L3R_DIAG_DATASIZE];
static uint8 DiagData390[L3R_DIAG_DATASIZE];
static uint8 DiagData391[L3R_DIAG_DATASIZE];
static uint8 DiagData392[L3R_DIAG_DATASIZE];
static uint8 DiagData393[L3R_DIAG_DATASIZE];
static uint8 DiagData394[L3R_DIAG_DATASIZE];
static uint8 DiagData395[L3R_DIAG_DATASIZE];
static uint8 DiagData396[L3R_DIAG_DATASIZE];
static uint8 DiagData397[L3R_DIAG_DATASIZE];
static uint8 DiagData398[L3R_DIAG_DATASIZE];
static uint8 DiagData399[L3R_DIAG_DATASIZE];
static uint8 DiagData400[L3R_DIAG_DATASIZE];
static uint8 DiagData401[L3R_DIAG_DATASIZE];
static uint8 DiagData402[L3R_DIAG_DATASIZE];
static uint8 DiagData403[L3R_DIAG_DATASIZE];
static uint8 DiagData404[L3R_DIAG_DATASIZE];
static uint8 DiagData405[L3R_DIAG_DATASIZE];
static uint8 DiagData406[L3R_DIAG_DATASIZE];
static uint8 DiagData407[L3R_DIAG_DATASIZE];
static uint8 DiagData408[L3R_DIAG_DATASIZE];
static uint8 DiagData409[L3R_DIAG_DATASIZE];
static uint8 DiagData410[L3R_DIAG_DATASIZE];
static uint8 DiagData411[L3R_DIAG_DATASIZE];
static uint8 DiagData412[L3R_DIAG_DATASIZE];
static uint8 DiagData413[L3R_DIAG_DATASIZE];
static uint8 DiagData414[L3R_DIAG_DATASIZE];
static uint8 DiagData415[L3R_DIAG_DATASIZE];
static uint8 DiagData416[L3R_DIAG_DATASIZE];
static uint8 DiagData417[L3R_DIAG_DATASIZE];
static uint8 DiagData418[L3R_DIAG_DATASIZE];
static uint8 DiagData419[L3R_DIAG_DATASIZE];
static uint8 DiagData420[L3R_DIAG_DATASIZE];
static uint8 DiagData421[L3R_DIAG_DATASIZE];
static uint8 DiagData422[L3R_DIAG_DATASIZE];
static uint8 DiagData423[L3R_DIAG_DATASIZE];
static uint8 DiagData424[L3R_DIAG_DATASIZE];
static uint8 DiagData425[L3R_DIAG_DATASIZE];
static uint8 DiagData426[L3R_DIAG_DATASIZE];
static uint8 DiagData427[L3R_DIAG_DATASIZE];
static uint8 DiagData428[L3R_DIAG_DATASIZE];
static uint8 DiagData429[L3R_DIAG_DATASIZE];
static uint8 DiagData430[L3R_DIAG_DATASIZE];
static uint8 DiagData431[L3R_DIAG_DATASIZE];
static uint8 DiagData432[L3R_DIAG_DATASIZE];
static uint8 DiagData433[L3R_DIAG_DATASIZE];
static uint8 DiagData434[L3R_DIAG_DATASIZE];
static uint8 DiagData435[L3R_DIAG_DATASIZE];
static uint8 DiagData436[L3R_DIAG_DATASIZE];
static uint8 DiagData437[L3R_DIAG_DATASIZE];
static uint8 DiagData438[L3R_DIAG_DATASIZE];
static uint8 DiagData439[L3R_DIAG_DATASIZE];
static uint8 DiagData440[L3R_DIAG_DATASIZE];
static uint8 DiagData441[L3R_DIAG_DATASIZE];
static uint8 DiagData442[L3R_DIAG_DATASIZE];
static uint8 DiagData443[L3R_DIAG_DATASIZE];
static uint8 DiagData444[L3R_DIAG_DATASIZE];
static uint8 DiagData445[L3R_DIAG_DATASIZE];
static uint8 DiagData446[L3R_DIAG_DATASIZE];
static uint8 DiagData447[L3R_DIAG_DATASIZE];
static uint8 DiagData448[L3R_DIAG_DATASIZE];
static uint8 DiagData449[L3R_DIAG_DATASIZE];
static uint8 DiagData450[L3R_DIAG_DATASIZE];
static uint8 DiagData451[L3R_DIAG_DATASIZE];
static uint8 DiagData452[L3R_DIAG_DATASIZE];
static uint8 DiagData453[L3R_DIAG_DATASIZE];
static uint8 DiagData454[L3R_DIAG_DATASIZE];
static uint8 DiagData455[L3R_DIAG_DATASIZE];
static uint8 DiagData456[L3R_DIAG_DATASIZE];
static uint8 DiagData457[L3R_DIAG_DATASIZE];
static uint8 DiagData458[L3R_DIAG_DATASIZE];
static uint8 DiagData459[L3R_DIAG_DATASIZE];
static uint8 DiagData460[L3R_DIAG_DATASIZE];
static uint8 DiagData461[L3R_DIAG_DATASIZE];
static uint8 DiagData462[L3R_DIAG_DATASIZE];
static uint8 DiagData463[L3R_DIAG_DATASIZE];
static uint8 DiagData464[L3R_DIAG_DATASIZE];
static uint8 DiagData465[L3R_DIAG_DATASIZE];
static uint8 DiagData466[L3R_DIAG_DATASIZE];
static uint8 DiagData467[L3R_DIAG_DATASIZE];
static uint8 DiagData468[L3R_DIAG_DATASIZE];
static uint8 DiagData469[L3R_DIAG_DATASIZE];
static uint8 DiagData470[L3R_DIAG_DATASIZE];
static uint8 DiagData471[L3R_DIAG_DATASIZE];
static uint8 DiagData472[L3R_DIAG_DATASIZE];
static uint8 DiagData473[L3R_DIAG_DATASIZE];
static uint8 DiagData474[L3R_DIAG_DATASIZE];
static uint8 DiagData475[L3R_DIAG_DATASIZE];
static uint8 DiagData476[L3R_DIAG_DATASIZE];
static uint8 DiagData477[L3R_DIAG_DATASIZE];
static uint8 DiagData478[L3R_DIAG_DATASIZE];
static uint8 DiagData479[L3R_DIAG_DATASIZE];
static uint8 DiagData480[L3R_DIAG_DATASIZE];
static uint8 DiagData481[L3R_DIAG_DATASIZE];
static uint8 DiagData482[L3R_DIAG_DATASIZE];
static uint8 DiagData483[L3R_DIAG_DATASIZE];
static uint8 DiagData484[L3R_DIAG_DATASIZE];
static uint8 DiagData485[L3R_DIAG_DATASIZE];
static uint8 DiagData486[L3R_DIAG_DATASIZE];
static uint8 DiagData487[L3R_DIAG_DATASIZE];
static uint8 DiagData488[L3R_DIAG_DATASIZE];
static uint8 DiagData489[L3R_DIAG_DATASIZE];
static uint8 DiagData490[L3R_DIAG_DATASIZE];
static uint8 DiagData491[L3R_DIAG_DATASIZE];
static uint8 DiagData492[L3R_DIAG_DATASIZE];
static uint8 DiagData493[L3R_DIAG_DATASIZE];
static uint8 DiagData494[L3R_DIAG_DATASIZE];
static uint8 DiagData495[L3R_DIAG_DATASIZE];
static uint8 DiagData496[L3R_DIAG_DATASIZE];
static uint8 DiagData497[L3R_DIAG_DATASIZE];
static uint8 DiagData498[L3R_DIAG_DATASIZE];
static uint8 DiagData499[L3R_DIAG_DATASIZE];
static uint8 DiagData500[L3R_DIAG_DATASIZE];
static uint8 DiagData501[L3R_DIAG_DATASIZE];
static uint8 DiagData502[L3R_DIAG_DATASIZE];
static uint8 DiagData503[L3R_DIAG_DATASIZE];
static uint8 DiagData504[L3R_DIAG_DATASIZE];
static uint8 DiagData505[L3R_DIAG_DATASIZE];
static uint8 DiagData506[L3R_DIAG_DATASIZE];
static uint8 DiagData507[L3R_DIAG_DATASIZE];
static uint8 DiagData508[L3R_DIAG_DATASIZE];
static uint8 DiagData509[L3R_DIAG_DATASIZE];
static uint8 DiagData510[L3R_DIAG_DATASIZE];
static uint8 DiagData511[L3R_DIAG_DATASIZE];
static uint8 DiagData512[L3R_DIAG_DATASIZE];
static uint8 DiagData513[L3R_DIAG_DATASIZE];
static uint8 DiagData514[L3R_DIAG_DATASIZE];
static uint8 DiagData515[L3R_DIAG_DATASIZE];
static uint8 DiagData516[L3R_DIAG_DATASIZE];
static uint8 DiagData517[L3R_DIAG_DATASIZE];
static uint8 DiagData518[L3R_DIAG_DATASIZE];
static uint8 DiagData519[L3R_DIAG_DATASIZE];
static uint8 DiagData520[L3R_DIAG_DATASIZE];
static uint8 DiagData521[L3R_DIAG_DATASIZE];
static uint8 DiagData522[L3R_DIAG_DATASIZE];
static uint8 DiagData523[L3R_DIAG_DATASIZE];
static uint8 DiagData524[L3R_DIAG_DATASIZE];
static uint8 DiagData525[L3R_DIAG_DATASIZE];
static uint8 DiagData526[L3R_DIAG_DATASIZE];
static uint8 DiagData527[L3R_DIAG_DATASIZE];
static uint8 DiagData528[L3R_DIAG_DATASIZE];
static uint8 DiagData529[L3R_DIAG_DATASIZE];
static uint8 DiagData530[L3R_DIAG_DATASIZE];
static uint8 DiagData531[L3R_DIAG_DATASIZE];
static uint8 DiagData532[L3R_DIAG_DATASIZE];
static uint8 DiagData533[L3R_DIAG_DATASIZE];
static uint8 DiagData534[L3R_DIAG_DATASIZE];
static uint8 DiagData535[L3R_DIAG_DATASIZE];
static uint8 DiagData536[L3R_DIAG_DATASIZE];
static uint8 DiagData537[L3R_DIAG_DATASIZE];
static uint8 DiagData538[L3R_DIAG_DATASIZE];
static uint8 DiagData539[L3R_DIAG_DATASIZE];
static uint8 DiagData540[L3R_DIAG_DATASIZE];
static uint8 DiagData541[L3R_DIAG_DATASIZE];
static uint8 DiagData542[L3R_DIAG_DATASIZE];
static uint8 DiagData543[L3R_DIAG_DATASIZE];
static uint8 DiagData544[L3R_DIAG_DATASIZE];
static uint8 DiagData545[L3R_DIAG_DATASIZE];
static uint8 DiagData546[L3R_DIAG_DATASIZE];
static uint8 DiagData547[L3R_DIAG_DATASIZE];
static uint8 DiagData548[L3R_DIAG_DATASIZE];
static uint8 DiagData549[L3R_DIAG_DATASIZE];
static uint8 DiagData550[L3R_DIAG_DATASIZE];
static uint8 DiagData551[L3R_DIAG_DATASIZE];
static uint8 DiagData552[L3R_DIAG_DATASIZE];
static uint8 DiagData553[L3R_DIAG_DATASIZE];
static uint8 DiagData554[L3R_DIAG_DATASIZE];
static uint8 DiagData555[L3R_DIAG_DATASIZE];
static uint8 DiagData556[L3R_DIAG_DATASIZE];
static uint8 DiagData557[L3R_DIAG_DATASIZE];
static uint8 DiagData558[L3R_DIAG_DATASIZE];
static uint8 DiagData559[L3R_DIAG_DATASIZE];
static uint8 DiagData560[L3R_DIAG_DATASIZE];
static uint8 DiagData561[L3R_DIAG_DATASIZE];
static uint8 DiagData562[L3R_DIAG_DATASIZE];
static uint8 DiagData563[L3R_DIAG_DATASIZE];
static uint8 DiagData564[L3R_DIAG_DATASIZE];
static uint8 DiagData565[L3R_DIAG_DATASIZE];
static uint8 DiagData566[L3R_DIAG_DATASIZE];
static uint8 DiagData567[L3R_DIAG_DATASIZE];
static uint8 DiagData568[L3R_DIAG_DATASIZE];
static uint8 DiagData569[L3R_DIAG_DATASIZE];
static uint8 DiagData570[L3R_DIAG_DATASIZE];
static uint8 DiagData571[L3R_DIAG_DATASIZE];
static uint8 DiagData572[L3R_DIAG_DATASIZE];
static uint8 DiagData573[L3R_DIAG_DATASIZE];
static uint8 DiagData574[L3R_DIAG_DATASIZE];
static uint8 DiagData575[L3R_DIAG_DATASIZE];
static uint8 DiagData576[L3R_DIAG_DATASIZE];
static uint8 DiagData577[L3R_DIAG_DATASIZE];
static uint8 DiagData578[L3R_DIAG_DATASIZE];
static uint8 DiagData579[L3R_DIAG_DATASIZE];
static uint8 DiagData580[L3R_DIAG_DATASIZE];
static uint8 DiagData581[L3R_DIAG_DATASIZE];
static uint8 DiagData582[L3R_DIAG_DATASIZE];
static uint8 DiagData583[L3R_DIAG_DATASIZE];
static uint8 DiagData584[L3R_DIAG_DATASIZE];
static uint8 DiagData585[L3R_DIAG_DATASIZE];
static uint8 DiagData586[L3R_DIAG_DATASIZE];
static uint8 DiagData587[L3R_DIAG_DATASIZE];
static uint8 DiagData588[L3R_DIAG_DATASIZE];
static uint8 DiagData589[L3R_DIAG_DATASIZE];
static uint8 DiagData590[L3R_DIAG_DATASIZE];
static uint8 DiagData591[L3R_DIAG_DATASIZE];
static uint8 DiagData592[L3R_DIAG_DATASIZE];
static uint8 DiagData593[L3R_DIAG_DATASIZE];
static uint8 DiagData594[L3R_DIAG_DATASIZE];
static uint8 DiagData595[L3R_DIAG_DATASIZE];
static uint8 DiagData596[L3R_DIAG_DATASIZE];
static uint8 DiagData597[L3R_DIAG_DATASIZE];
static uint8 DiagData598[L3R_DIAG_DATASIZE];
static uint8 DiagData599[L3R_DIAG_DATASIZE];
static uint8 DiagData600[L3R_DIAG_DATASIZE];
static uint8 DiagData601[L3R_DIAG_DATASIZE];
static uint8 DiagData602[L3R_DIAG_DATASIZE];
static uint8 DiagData603[L3R_DIAG_DATASIZE];
static uint8 DiagData604[L3R_DIAG_DATASIZE];
static uint8 DiagData605[L3R_DIAG_DATASIZE];
static uint8 DiagData606[L3R_DIAG_DATASIZE];
static uint8 DiagData607[L3R_DIAG_DATASIZE];
static uint8 DiagData608[L3R_DIAG_DATASIZE];
static uint8 DiagData609[L3R_DIAG_DATASIZE];
static uint8 DiagData610[L3R_DIAG_DATASIZE];
static uint8 DiagData611[L3R_DIAG_DATASIZE];
static uint8 DiagData612[L3R_DIAG_DATASIZE];
static uint8 DiagData613[L3R_DIAG_DATASIZE];
static uint8 DiagData614[L3R_DIAG_DATASIZE];
static uint8 DiagData615[L3R_DIAG_DATASIZE];
static uint8 DiagData616[L3R_DIAG_DATASIZE];
static uint8 DiagData617[L3R_DIAG_DATASIZE];
static uint8 DiagData618[L3R_DIAG_DATASIZE];
static uint8 DiagData619[L3R_DIAG_DATASIZE];
static uint8 DiagData620[L3R_DIAG_DATASIZE];
static uint8 DiagData621[L3R_DIAG_DATASIZE];
static uint8 DiagData622[L3R_DIAG_DATASIZE];
static uint8 DiagData623[L3R_DIAG_DATASIZE];
static uint8 DiagData624[L3R_DIAG_DATASIZE];
static uint8 DiagData625[L3R_DIAG_DATASIZE];
static uint8 DiagData626[L3R_DIAG_DATASIZE];
static uint8 DiagData627[L3R_DIAG_DATASIZE];
static uint8 DiagData628[L3R_DIAG_DATASIZE];
static uint8 DiagData629[L3R_DIAG_DATASIZE];
static uint8 DiagData630[L3R_DIAG_DATASIZE];
static uint8 DiagData631[L3R_DIAG_DATASIZE];
static uint8 DiagData632[L3R_DIAG_DATASIZE];
static uint8 DiagData633[L3R_DIAG_DATASIZE];
static uint8 DiagData634[L3R_DIAG_DATASIZE];
static uint8 DiagData635[L3R_DIAG_DATASIZE];
static uint8 DiagData636[L3R_DIAG_DATASIZE];
static uint8 DiagData637[L3R_DIAG_DATASIZE];
static uint8 DiagData638[L3R_DIAG_DATASIZE];
static uint8 DiagData639[L3R_DIAG_DATASIZE];
static uint8 DiagData640[L3R_DIAG_DATASIZE];
static uint8 DiagData641[L3R_DIAG_DATASIZE];
static uint8 DiagData642[L3R_DIAG_DATASIZE];
static uint8 DiagData643[L3R_DIAG_DATASIZE];
static uint8 DiagData644[L3R_DIAG_DATASIZE];
static uint8 DiagData645[L3R_DIAG_DATASIZE];
static uint8 DiagData646[L3R_DIAG_DATASIZE];
static uint8 DiagData647[L3R_DIAG_DATASIZE];
static uint8 DiagData648[L3R_DIAG_DATASIZE];
static uint8 DiagData649[L3R_DIAG_DATASIZE];
static uint8 DiagData650[L3R_DIAG_DATASIZE];
static uint8 DiagData651[L3R_DIAG_DATASIZE];
static uint8 DiagData652[L3R_DIAG_DATASIZE];
static uint8 DiagData653[L3R_DIAG_DATASIZE];
static uint8 DiagData654[L3R_DIAG_DATASIZE];
static uint8 DiagData655[L3R_DIAG_DATASIZE];
static uint8 DiagData656[L3R_DIAG_DATASIZE];
static uint8 DiagData657[L3R_DIAG_DATASIZE];
static uint8 DiagData658[L3R_DIAG_DATASIZE];
static uint8 DiagData659[L3R_DIAG_DATASIZE];
static uint8 DiagData660[L3R_DIAG_DATASIZE];
static uint8 DiagData661[L3R_DIAG_DATASIZE];
static uint8 DiagData662[L3R_DIAG_DATASIZE];
static uint8 DiagData663[L3R_DIAG_DATASIZE];
static uint8 DiagData664[L3R_DIAG_DATASIZE];
static uint8 DiagData665[L3R_DIAG_DATASIZE];
static uint8 DiagData666[L3R_DIAG_DATASIZE];
static uint8 DiagData667[L3R_DIAG_DATASIZE];
static uint8 DiagData668[L3R_DIAG_DATASIZE];
static uint8 DiagData669[L3R_DIAG_DATASIZE];
static uint8 DiagData670[L3R_DIAG_DATASIZE];
static uint8 DiagData671[L3R_DIAG_DATASIZE];
static uint8 DiagData672[L3R_DIAG_DATASIZE];
static uint8 DiagData673[L3R_DIAG_DATASIZE];
static uint8 DiagData674[L3R_DIAG_DATASIZE];
static uint8 DiagData675[L3R_DIAG_DATASIZE];
static uint8 DiagData676[L3R_DIAG_DATASIZE];
static uint8 DiagData677[L3R_DIAG_DATASIZE];
static uint8 DiagData678[L3R_DIAG_DATASIZE];
static uint8 DiagData679[L3R_DIAG_DATASIZE];
static uint8 DiagData680[L3R_DIAG_DATASIZE];
static uint8 DiagData681[L3R_DIAG_DATASIZE];

#define GW_L3R_STOP_SEC_NBVA_ZI
#include "GW_L3R_Memmap.h"

#define GW_L3R_START_SEC_CONST
#include "GW_L3R_Memmap.h"


static CommonBuffer DiagBufferMember000 = { &DiagQueRouter_funcList[0], DiagData000, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr000, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember001 = { &DiagQueRouter_funcList[0], DiagData001, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr001, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember002 = { &DiagQueRouter_funcList[0], DiagData002, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr002, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember003 = { &DiagQueRouter_funcList[0], DiagData003, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr003, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember004 = { &DiagQueRouter_funcList[0], DiagData004, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr004, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember005 = { &DiagQueRouter_funcList[0], DiagData005, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr005, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember006 = { &DiagQueRouter_funcList[0], DiagData006, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr006, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember007 = { &DiagQueRouter_funcList[0], DiagData007, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr007, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember008 = { &DiagQueRouter_funcList[0], DiagData008, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr008, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember009 = { &DiagQueRouter_funcList[0], DiagData009, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr009, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember010 = { &DiagQueRouter_funcList[0], DiagData010, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr010, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember011 = { &DiagQueRouter_funcList[0], DiagData011, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr011, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember012 = { &DiagQueRouter_funcList[0], DiagData012, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr012, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember013 = { &DiagQueRouter_funcList[0], DiagData013, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr013, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember014 = { &DiagQueRouter_funcList[0], DiagData014, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr014, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember015 = { &DiagQueRouter_funcList[0], DiagData015, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr015, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember016 = { &DiagQueRouter_funcList[0], DiagData016, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr016, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember017 = { &DiagQueRouter_funcList[0], DiagData017, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr017, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember018 = { &DiagQueRouter_funcList[0], DiagData018, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr018, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember019 = { &DiagQueRouter_funcList[0], DiagData019, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr019, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember020 = { &DiagQueRouter_funcList[0], DiagData020, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr020, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember021 = { &DiagQueRouter_funcList[0], DiagData021, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr021, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember022 = { &DiagQueRouter_funcList[0], DiagData022, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr022, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember023 = { &DiagQueRouter_funcList[0], DiagData023, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr023, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember024 = { &DiagQueRouter_funcList[0], DiagData024, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr024, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember025 = { &DiagQueRouter_funcList[0], DiagData025, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr025, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember026 = { &DiagQueRouter_funcList[0], DiagData026, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr026, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember027 = { &DiagQueRouter_funcList[0], DiagData027, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr027, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember028 = { &DiagQueRouter_funcList[0], DiagData028, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr028, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember029 = { &DiagQueRouter_funcList[0], DiagData029, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr029, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember030 = { &DiagQueRouter_funcList[0], DiagData030, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr030, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember031 = { &DiagQueRouter_funcList[0], DiagData031, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr031, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember032 = { &DiagQueRouter_funcList[0], DiagData032, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr032, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember033 = { &DiagQueRouter_funcList[0], DiagData033, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr033, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember034 = { &DiagQueRouter_funcList[0], DiagData034, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr034, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember035 = { &DiagQueRouter_funcList[0], DiagData035, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr035, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember036 = { &DiagQueRouter_funcList[0], DiagData036, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr036, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember037 = { &DiagQueRouter_funcList[0], DiagData037, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr037, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember038 = { &DiagQueRouter_funcList[0], DiagData038, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr038, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember039 = { &DiagQueRouter_funcList[0], DiagData039, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr039, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember040 = { &DiagQueRouter_funcList[0], DiagData040, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr040, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember041 = { &DiagQueRouter_funcList[0], DiagData041, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr041, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember042 = { &DiagQueRouter_funcList[0], DiagData042, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr042, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember043 = { &DiagQueRouter_funcList[0], DiagData043, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr043, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember044 = { &DiagQueRouter_funcList[0], DiagData044, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr044, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember045 = { &DiagQueRouter_funcList[0], DiagData045, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr045, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember046 = { &DiagQueRouter_funcList[0], DiagData046, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr046, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember047 = { &DiagQueRouter_funcList[0], DiagData047, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr047, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember048 = { &DiagQueRouter_funcList[0], DiagData048, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr048, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember049 = { &DiagQueRouter_funcList[0], DiagData049, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr049, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember050 = { &DiagQueRouter_funcList[0], DiagData050, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr050, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember051 = { &DiagQueRouter_funcList[0], DiagData051, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr051, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember052 = { &DiagQueRouter_funcList[0], DiagData052, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr052, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember053 = { &DiagQueRouter_funcList[0], DiagData053, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr053, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember054 = { &DiagQueRouter_funcList[0], DiagData054, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr054, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember055 = { &DiagQueRouter_funcList[0], DiagData055, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr055, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember056 = { &DiagQueRouter_funcList[0], DiagData056, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr056, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember057 = { &DiagQueRouter_funcList[0], DiagData057, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr057, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember058 = { &DiagQueRouter_funcList[0], DiagData058, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr058, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember059 = { &DiagQueRouter_funcList[0], DiagData059, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr059, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember060 = { &DiagQueRouter_funcList[0], DiagData060, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr060, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember061 = { &DiagQueRouter_funcList[0], DiagData061, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr061, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember062 = { &DiagQueRouter_funcList[0], DiagData062, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr062, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember063 = { &DiagQueRouter_funcList[0], DiagData063, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr063, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember064 = { &DiagQueRouter_funcList[0], DiagData064, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr064, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember065 = { &DiagQueRouter_funcList[0], DiagData065, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr065, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember066 = { &DiagQueRouter_funcList[0], DiagData066, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr066, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember067 = { &DiagQueRouter_funcList[0], DiagData067, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr067, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember068 = { &DiagQueRouter_funcList[0], DiagData068, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr068, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember069 = { &DiagQueRouter_funcList[0], DiagData069, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr069, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember070 = { &DiagQueRouter_funcList[0], DiagData070, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr070, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember071 = { &DiagQueRouter_funcList[0], DiagData071, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr071, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember072 = { &DiagQueRouter_funcList[0], DiagData072, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr072, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember073 = { &DiagQueRouter_funcList[0], DiagData073, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr073, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember074 = { &DiagQueRouter_funcList[0], DiagData074, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr074, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember075 = { &DiagQueRouter_funcList[0], DiagData075, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr075, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember076 = { &DiagQueRouter_funcList[0], DiagData076, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr076, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember077 = { &DiagQueRouter_funcList[0], DiagData077, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr077, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember078 = { &DiagQueRouter_funcList[0], DiagData078, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr078, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember079 = { &DiagQueRouter_funcList[0], DiagData079, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr079, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember080 = { &DiagQueRouter_funcList[0], DiagData080, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr080, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember081 = { &DiagQueRouter_funcList[0], DiagData081, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr081, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember082 = { &DiagQueRouter_funcList[0], DiagData082, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr082, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember083 = { &DiagQueRouter_funcList[0], DiagData083, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr083, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember084 = { &DiagQueRouter_funcList[0], DiagData084, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr084, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember085 = { &DiagQueRouter_funcList[0], DiagData085, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr085, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember086 = { &DiagQueRouter_funcList[0], DiagData086, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr086, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember087 = { &DiagQueRouter_funcList[0], DiagData087, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr087, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember088 = { &DiagQueRouter_funcList[0], DiagData088, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr088, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember089 = { &DiagQueRouter_funcList[0], DiagData089, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr089, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember090 = { &DiagQueRouter_funcList[0], DiagData090, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr090, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember091 = { &DiagQueRouter_funcList[0], DiagData091, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr091, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember092 = { &DiagQueRouter_funcList[0], DiagData092, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr092, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember093 = { &DiagQueRouter_funcList[0], DiagData093, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr093, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember094 = { &DiagQueRouter_funcList[0], DiagData094, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr094, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember095 = { &DiagQueRouter_funcList[0], DiagData095, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr095, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember096 = { &DiagQueRouter_funcList[0], DiagData096, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr096, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember097 = { &DiagQueRouter_funcList[0], DiagData097, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr097, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember098 = { &DiagQueRouter_funcList[0], DiagData098, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr098, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember099 = { &DiagQueRouter_funcList[0], DiagData099, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr099, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember100 = { &DiagQueRouter_funcList[0], DiagData100, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr100, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember101 = { &DiagQueRouter_funcList[0], DiagData101, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr101, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember102 = { &DiagQueRouter_funcList[0], DiagData102, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr102, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember103 = { &DiagQueRouter_funcList[0], DiagData103, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr103, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember104 = { &DiagQueRouter_funcList[0], DiagData104, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr104, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember105 = { &DiagQueRouter_funcList[0], DiagData105, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr105, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember106 = { &DiagQueRouter_funcList[0], DiagData106, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr106, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember107 = { &DiagQueRouter_funcList[0], DiagData107, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr107, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember108 = { &DiagQueRouter_funcList[0], DiagData108, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr108, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember109 = { &DiagQueRouter_funcList[0], DiagData109, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr109, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember110 = { &DiagQueRouter_funcList[0], DiagData110, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr110, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember111 = { &DiagQueRouter_funcList[0], DiagData111, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr111, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember112 = { &DiagQueRouter_funcList[0], DiagData112, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr112, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember113 = { &DiagQueRouter_funcList[0], DiagData113, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr113, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember114 = { &DiagQueRouter_funcList[0], DiagData114, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr114, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember115 = { &DiagQueRouter_funcList[0], DiagData115, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr115, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember116 = { &DiagQueRouter_funcList[0], DiagData116, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr116, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember117 = { &DiagQueRouter_funcList[0], DiagData117, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr117, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember118 = { &DiagQueRouter_funcList[0], DiagData118, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr118, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember119 = { &DiagQueRouter_funcList[0], DiagData119, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr119, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember120 = { &DiagQueRouter_funcList[0], DiagData120, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr120, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember121 = { &DiagQueRouter_funcList[0], DiagData121, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr121, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember122 = { &DiagQueRouter_funcList[0], DiagData122, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr122, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember123 = { &DiagQueRouter_funcList[0], DiagData123, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr123, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember124 = { &DiagQueRouter_funcList[0], DiagData124, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr124, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember125 = { &DiagQueRouter_funcList[0], DiagData125, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr125, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember126 = { &DiagQueRouter_funcList[0], DiagData126, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr126, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember127 = { &DiagQueRouter_funcList[0], DiagData127, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr127, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember128 = { &DiagQueRouter_funcList[0], DiagData128, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr128, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember129 = { &DiagQueRouter_funcList[0], DiagData129, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr129, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember130 = { &DiagQueRouter_funcList[0], DiagData130, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr130, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember131 = { &DiagQueRouter_funcList[0], DiagData131, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr131, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember132 = { &DiagQueRouter_funcList[0], DiagData132, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr132, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember133 = { &DiagQueRouter_funcList[0], DiagData133, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr133, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember134 = { &DiagQueRouter_funcList[0], DiagData134, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr134, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember135 = { &DiagQueRouter_funcList[0], DiagData135, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr135, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember136 = { &DiagQueRouter_funcList[0], DiagData136, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr136, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember137 = { &DiagQueRouter_funcList[0], DiagData137, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr137, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember138 = { &DiagQueRouter_funcList[0], DiagData138, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr138, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember139 = { &DiagQueRouter_funcList[0], DiagData139, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr139, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember140 = { &DiagQueRouter_funcList[0], DiagData140, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr140, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember141 = { &DiagQueRouter_funcList[0], DiagData141, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr141, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember142 = { &DiagQueRouter_funcList[0], DiagData142, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr142, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember143 = { &DiagQueRouter_funcList[0], DiagData143, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr143, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember144 = { &DiagQueRouter_funcList[0], DiagData144, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr144, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember145 = { &DiagQueRouter_funcList[0], DiagData145, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr145, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember146 = { &DiagQueRouter_funcList[0], DiagData146, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr146, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember147 = { &DiagQueRouter_funcList[0], DiagData147, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr147, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember148 = { &DiagQueRouter_funcList[0], DiagData148, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr148, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember149 = { &DiagQueRouter_funcList[0], DiagData149, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr149, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember150 = { &DiagQueRouter_funcList[0], DiagData150, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr150, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember151 = { &DiagQueRouter_funcList[0], DiagData151, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr151, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember152 = { &DiagQueRouter_funcList[0], DiagData152, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr152, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember153 = { &DiagQueRouter_funcList[0], DiagData153, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr153, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember154 = { &DiagQueRouter_funcList[0], DiagData154, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr154, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember155 = { &DiagQueRouter_funcList[0], DiagData155, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr155, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember156 = { &DiagQueRouter_funcList[0], DiagData156, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr156, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember157 = { &DiagQueRouter_funcList[0], DiagData157, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr157, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember158 = { &DiagQueRouter_funcList[0], DiagData158, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr158, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember159 = { &DiagQueRouter_funcList[0], DiagData159, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr159, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember160 = { &DiagQueRouter_funcList[0], DiagData160, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr160, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember161 = { &DiagQueRouter_funcList[0], DiagData161, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr161, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember162 = { &DiagQueRouter_funcList[0], DiagData162, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr162, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember163 = { &DiagQueRouter_funcList[0], DiagData163, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr163, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember164 = { &DiagQueRouter_funcList[0], DiagData164, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr164, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember165 = { &DiagQueRouter_funcList[0], DiagData165, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr165, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember166 = { &DiagQueRouter_funcList[0], DiagData166, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr166, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember167 = { &DiagQueRouter_funcList[0], DiagData167, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr167, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember168 = { &DiagQueRouter_funcList[0], DiagData168, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr168, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember169 = { &DiagQueRouter_funcList[0], DiagData169, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr169, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember170 = { &DiagQueRouter_funcList[0], DiagData170, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr170, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember171 = { &DiagQueRouter_funcList[0], DiagData171, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr171, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember172 = { &DiagQueRouter_funcList[0], DiagData172, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr172, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember173 = { &DiagQueRouter_funcList[0], DiagData173, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr173, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember174 = { &DiagQueRouter_funcList[0], DiagData174, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr174, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember175 = { &DiagQueRouter_funcList[0], DiagData175, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr175, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember176 = { &DiagQueRouter_funcList[0], DiagData176, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr176, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember177 = { &DiagQueRouter_funcList[0], DiagData177, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr177, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember178 = { &DiagQueRouter_funcList[0], DiagData178, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr178, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember179 = { &DiagQueRouter_funcList[0], DiagData179, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr179, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember180 = { &DiagQueRouter_funcList[0], DiagData180, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr180, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember181 = { &DiagQueRouter_funcList[0], DiagData181, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr181, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember182 = { &DiagQueRouter_funcList[0], DiagData182, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr182, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember183 = { &DiagQueRouter_funcList[0], DiagData183, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr183, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember184 = { &DiagQueRouter_funcList[0], DiagData184, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr184, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember185 = { &DiagQueRouter_funcList[0], DiagData185, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr185, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember186 = { &DiagQueRouter_funcList[0], DiagData186, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr186, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember187 = { &DiagQueRouter_funcList[0], DiagData187, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr187, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember188 = { &DiagQueRouter_funcList[0], DiagData188, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr188, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember189 = { &DiagQueRouter_funcList[0], DiagData189, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr189, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember190 = { &DiagQueRouter_funcList[0], DiagData190, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr190, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember191 = { &DiagQueRouter_funcList[0], DiagData191, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr191, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember192 = { &DiagQueRouter_funcList[0], DiagData192, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr192, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember193 = { &DiagQueRouter_funcList[0], DiagData193, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr193, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember194 = { &DiagQueRouter_funcList[0], DiagData194, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr194, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember195 = { &DiagQueRouter_funcList[0], DiagData195, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr195, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember196 = { &DiagQueRouter_funcList[0], DiagData196, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr196, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember197 = { &DiagQueRouter_funcList[0], DiagData197, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr197, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember198 = { &DiagQueRouter_funcList[0], DiagData198, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr198, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember199 = { &DiagQueRouter_funcList[0], DiagData199, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr199, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember200 = { &DiagQueRouter_funcList[0], DiagData200, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr200, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember201 = { &DiagQueRouter_funcList[0], DiagData201, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr201, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember202 = { &DiagQueRouter_funcList[0], DiagData202, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr202, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember203 = { &DiagQueRouter_funcList[0], DiagData203, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr203, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember204 = { &DiagQueRouter_funcList[0], DiagData204, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr204, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember205 = { &DiagQueRouter_funcList[0], DiagData205, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr205, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember206 = { &DiagQueRouter_funcList[0], DiagData206, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr206, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember207 = { &DiagQueRouter_funcList[0], DiagData207, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr207, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember208 = { &DiagQueRouter_funcList[0], DiagData208, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr208, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember209 = { &DiagQueRouter_funcList[0], DiagData209, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr209, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember210 = { &DiagQueRouter_funcList[0], DiagData210, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr210, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember211 = { &DiagQueRouter_funcList[0], DiagData211, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr211, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember212 = { &DiagQueRouter_funcList[0], DiagData212, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr212, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember213 = { &DiagQueRouter_funcList[0], DiagData213, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr213, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember214 = { &DiagQueRouter_funcList[0], DiagData214, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr214, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember215 = { &DiagQueRouter_funcList[0], DiagData215, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr215, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember216 = { &DiagQueRouter_funcList[0], DiagData216, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr216, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember217 = { &DiagQueRouter_funcList[0], DiagData217, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr217, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember218 = { &DiagQueRouter_funcList[0], DiagData218, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr218, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember219 = { &DiagQueRouter_funcList[0], DiagData219, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr219, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember220 = { &DiagQueRouter_funcList[0], DiagData220, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr220, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember221 = { &DiagQueRouter_funcList[0], DiagData221, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr221, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember222 = { &DiagQueRouter_funcList[0], DiagData222, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr222, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember223 = { &DiagQueRouter_funcList[0], DiagData223, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr223, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember224 = { &DiagQueRouter_funcList[0], DiagData224, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr224, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember225 = { &DiagQueRouter_funcList[0], DiagData225, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr225, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember226 = { &DiagQueRouter_funcList[0], DiagData226, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr226, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember227 = { &DiagQueRouter_funcList[0], DiagData227, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr227, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember228 = { &DiagQueRouter_funcList[0], DiagData228, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr228, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember229 = { &DiagQueRouter_funcList[0], DiagData229, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr229, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember230 = { &DiagQueRouter_funcList[0], DiagData230, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr230, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember231 = { &DiagQueRouter_funcList[0], DiagData231, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr231, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember232 = { &DiagQueRouter_funcList[0], DiagData232, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr232, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember233 = { &DiagQueRouter_funcList[0], DiagData233, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr233, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember234 = { &DiagQueRouter_funcList[0], DiagData234, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr234, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember235 = { &DiagQueRouter_funcList[0], DiagData235, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr235, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember236 = { &DiagQueRouter_funcList[0], DiagData236, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr236, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember237 = { &DiagQueRouter_funcList[0], DiagData237, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr237, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember238 = { &DiagQueRouter_funcList[0], DiagData238, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr238, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember239 = { &DiagQueRouter_funcList[0], DiagData239, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr239, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember240 = { &DiagQueRouter_funcList[0], DiagData240, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr240, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember241 = { &DiagQueRouter_funcList[0], DiagData241, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr241, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember242 = { &DiagQueRouter_funcList[0], DiagData242, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr242, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember243 = { &DiagQueRouter_funcList[0], DiagData243, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr243, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember244 = { &DiagQueRouter_funcList[0], DiagData244, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr244, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember245 = { &DiagQueRouter_funcList[0], DiagData245, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr245, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember246 = { &DiagQueRouter_funcList[0], DiagData246, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr246, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember247 = { &DiagQueRouter_funcList[0], DiagData247, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr247, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember248 = { &DiagQueRouter_funcList[0], DiagData248, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr248, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember249 = { &DiagQueRouter_funcList[0], DiagData249, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr249, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember250 = { &DiagQueRouter_funcList[0], DiagData250, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr250, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember251 = { &DiagQueRouter_funcList[0], DiagData251, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr251, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember252 = { &DiagQueRouter_funcList[0], DiagData252, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr252, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember253 = { &DiagQueRouter_funcList[0], DiagData253, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr253, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember254 = { &DiagQueRouter_funcList[0], DiagData254, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr254, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember255 = { &DiagQueRouter_funcList[0], DiagData255, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr255, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember256 = { &DiagQueRouter_funcList[0], DiagData256, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr256, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember257 = { &DiagQueRouter_funcList[0], DiagData257, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr257, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember258 = { &DiagQueRouter_funcList[0], DiagData258, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr258, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember259 = { &DiagQueRouter_funcList[0], DiagData259, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr259, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember260 = { &DiagQueRouter_funcList[0], DiagData260, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr260, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember261 = { &DiagQueRouter_funcList[0], DiagData261, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr261, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember262 = { &DiagQueRouter_funcList[0], DiagData262, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr262, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember263 = { &DiagQueRouter_funcList[0], DiagData263, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr263, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember264 = { &DiagQueRouter_funcList[0], DiagData264, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr264, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember265 = { &DiagQueRouter_funcList[0], DiagData265, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr265, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember266 = { &DiagQueRouter_funcList[0], DiagData266, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr266, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember267 = { &DiagQueRouter_funcList[0], DiagData267, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr267, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember268 = { &DiagQueRouter_funcList[0], DiagData268, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr268, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember269 = { &DiagQueRouter_funcList[0], DiagData269, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr269, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember270 = { &DiagQueRouter_funcList[0], DiagData270, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr270, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember271 = { &DiagQueRouter_funcList[0], DiagData271, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr271, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember272 = { &DiagQueRouter_funcList[0], DiagData272, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr272, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember273 = { &DiagQueRouter_funcList[0], DiagData273, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr273, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember274 = { &DiagQueRouter_funcList[0], DiagData274, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr274, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember275 = { &DiagQueRouter_funcList[0], DiagData275, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr275, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember276 = { &DiagQueRouter_funcList[0], DiagData276, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr276, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember277 = { &DiagQueRouter_funcList[0], DiagData277, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr277, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember278 = { &DiagQueRouter_funcList[0], DiagData278, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr278, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember279 = { &DiagQueRouter_funcList[0], DiagData279, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr279, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember280 = { &DiagQueRouter_funcList[0], DiagData280, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr280, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember281 = { &DiagQueRouter_funcList[0], DiagData281, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr281, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember282 = { &DiagQueRouter_funcList[0], DiagData282, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr282, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember283 = { &DiagQueRouter_funcList[0], DiagData283, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr283, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember284 = { &DiagQueRouter_funcList[0], DiagData284, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr284, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember285 = { &DiagQueRouter_funcList[0], DiagData285, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr285, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember286 = { &DiagQueRouter_funcList[0], DiagData286, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr286, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember287 = { &DiagQueRouter_funcList[0], DiagData287, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr287, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember288 = { &DiagQueRouter_funcList[0], DiagData288, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr288, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember289 = { &DiagQueRouter_funcList[0], DiagData289, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr289, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember290 = { &DiagQueRouter_funcList[0], DiagData290, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr290, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember291 = { &DiagQueRouter_funcList[0], DiagData291, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr291, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember292 = { &DiagQueRouter_funcList[0], DiagData292, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr292, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember293 = { &DiagQueRouter_funcList[0], DiagData293, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr293, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember294 = { &DiagQueRouter_funcList[0], DiagData294, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr294, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember295 = { &DiagQueRouter_funcList[0], DiagData295, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr295, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember296 = { &DiagQueRouter_funcList[0], DiagData296, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr296, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember297 = { &DiagQueRouter_funcList[0], DiagData297, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr297, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember298 = { &DiagQueRouter_funcList[0], DiagData298, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr298, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember299 = { &DiagQueRouter_funcList[0], DiagData299, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr299, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember300 = { &DiagQueRouter_funcList[0], DiagData300, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr300, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember301 = { &DiagQueRouter_funcList[0], DiagData301, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr301, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember302 = { &DiagQueRouter_funcList[0], DiagData302, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr302, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember303 = { &DiagQueRouter_funcList[0], DiagData303, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr303, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember304 = { &DiagQueRouter_funcList[0], DiagData304, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr304, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember305 = { &DiagQueRouter_funcList[0], DiagData305, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr305, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember306 = { &DiagQueRouter_funcList[0], DiagData306, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr306, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember307 = { &DiagQueRouter_funcList[0], DiagData307, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr307, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember308 = { &DiagQueRouter_funcList[0], DiagData308, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr308, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember309 = { &DiagQueRouter_funcList[0], DiagData309, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr309, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember310 = { &DiagQueRouter_funcList[0], DiagData310, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr310, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember311 = { &DiagQueRouter_funcList[0], DiagData311, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr311, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember312 = { &DiagQueRouter_funcList[0], DiagData312, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr312, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember313 = { &DiagQueRouter_funcList[0], DiagData313, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr313, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember314 = { &DiagQueRouter_funcList[0], DiagData314, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr314, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember315 = { &DiagQueRouter_funcList[0], DiagData315, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr315, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember316 = { &DiagQueRouter_funcList[0], DiagData316, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr316, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember317 = { &DiagQueRouter_funcList[0], DiagData317, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr317, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember318 = { &DiagQueRouter_funcList[0], DiagData318, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr318, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember319 = { &DiagQueRouter_funcList[0], DiagData319, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr319, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember320 = { &DiagQueRouter_funcList[0], DiagData320, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr320, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember321 = { &DiagQueRouter_funcList[0], DiagData321, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr321, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember322 = { &DiagQueRouter_funcList[0], DiagData322, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr322, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember323 = { &DiagQueRouter_funcList[0], DiagData323, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr323, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember324 = { &DiagQueRouter_funcList[0], DiagData324, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr324, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember325 = { &DiagQueRouter_funcList[0], DiagData325, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr325, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember326 = { &DiagQueRouter_funcList[0], DiagData326, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr326, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember327 = { &DiagQueRouter_funcList[0], DiagData327, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr327, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember328 = { &DiagQueRouter_funcList[0], DiagData328, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr328, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember329 = { &DiagQueRouter_funcList[0], DiagData329, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr329, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember330 = { &DiagQueRouter_funcList[0], DiagData330, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr330, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember331 = { &DiagQueRouter_funcList[0], DiagData331, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr331, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember332 = { &DiagQueRouter_funcList[0], DiagData332, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr332, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember333 = { &DiagQueRouter_funcList[0], DiagData333, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr333, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember334 = { &DiagQueRouter_funcList[0], DiagData334, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr334, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember335 = { &DiagQueRouter_funcList[0], DiagData335, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr335, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember336 = { &DiagQueRouter_funcList[0], DiagData336, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr336, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember337 = { &DiagQueRouter_funcList[0], DiagData337, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr337, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember338 = { &DiagQueRouter_funcList[0], DiagData338, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr338, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember339 = { &DiagQueRouter_funcList[0], DiagData339, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr339, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember340 = { &DiagQueRouter_funcList[0], DiagData340, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr340, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember341 = { &DiagQueRouter_funcList[0], DiagData341, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr341, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember342 = { &DiagQueRouter_funcList[0], DiagData342, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr342, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember343 = { &DiagQueRouter_funcList[0], DiagData343, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr343, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember344 = { &DiagQueRouter_funcList[0], DiagData344, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr344, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember345 = { &DiagQueRouter_funcList[0], DiagData345, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr345, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember346 = { &DiagQueRouter_funcList[0], DiagData346, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr346, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember347 = { &DiagQueRouter_funcList[0], DiagData347, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr347, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember348 = { &DiagQueRouter_funcList[0], DiagData348, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr348, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember349 = { &DiagQueRouter_funcList[0], DiagData349, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr349, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember350 = { &DiagQueRouter_funcList[0], DiagData350, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr350, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember351 = { &DiagQueRouter_funcList[0], DiagData351, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr351, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember352 = { &DiagQueRouter_funcList[0], DiagData352, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr352, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember353 = { &DiagQueRouter_funcList[0], DiagData353, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr353, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember354 = { &DiagQueRouter_funcList[0], DiagData354, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr354, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember355 = { &DiagQueRouter_funcList[0], DiagData355, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr355, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember356 = { &DiagQueRouter_funcList[0], DiagData356, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr356, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember357 = { &DiagQueRouter_funcList[0], DiagData357, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr357, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember358 = { &DiagQueRouter_funcList[0], DiagData358, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr358, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember359 = { &DiagQueRouter_funcList[0], DiagData359, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr359, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember360 = { &DiagQueRouter_funcList[0], DiagData360, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr360, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember361 = { &DiagQueRouter_funcList[0], DiagData361, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr361, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember362 = { &DiagQueRouter_funcList[0], DiagData362, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr362, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember363 = { &DiagQueRouter_funcList[0], DiagData363, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr363, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember364 = { &DiagQueRouter_funcList[0], DiagData364, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr364, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember365 = { &DiagQueRouter_funcList[0], DiagData365, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr365, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember366 = { &DiagQueRouter_funcList[0], DiagData366, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr366, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember367 = { &DiagQueRouter_funcList[0], DiagData367, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr367, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember368 = { &DiagQueRouter_funcList[0], DiagData368, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr368, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember369 = { &DiagQueRouter_funcList[0], DiagData369, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr369, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember370 = { &DiagQueRouter_funcList[0], DiagData370, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr370, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember371 = { &DiagQueRouter_funcList[0], DiagData371, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr371, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember372 = { &DiagQueRouter_funcList[0], DiagData372, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr372, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember373 = { &DiagQueRouter_funcList[0], DiagData373, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr373, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember374 = { &DiagQueRouter_funcList[0], DiagData374, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr374, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember375 = { &DiagQueRouter_funcList[0], DiagData375, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr375, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember376 = { &DiagQueRouter_funcList[0], DiagData376, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr376, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember377 = { &DiagQueRouter_funcList[0], DiagData377, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr377, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember378 = { &DiagQueRouter_funcList[0], DiagData378, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr378, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember379 = { &DiagQueRouter_funcList[0], DiagData379, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr379, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember380 = { &DiagQueRouter_funcList[0], DiagData380, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr380, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember381 = { &DiagQueRouter_funcList[0], DiagData381, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr381, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember382 = { &DiagQueRouter_funcList[0], DiagData382, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr382, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember383 = { &DiagQueRouter_funcList[0], DiagData383, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr383, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember384 = { &DiagQueRouter_funcList[0], DiagData384, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr384, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember385 = { &DiagQueRouter_funcList[0], DiagData385, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr385, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember386 = { &DiagQueRouter_funcList[0], DiagData386, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr386, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember387 = { &DiagQueRouter_funcList[0], DiagData387, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr387, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember388 = { &DiagQueRouter_funcList[0], DiagData388, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr388, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember389 = { &DiagQueRouter_funcList[0], DiagData389, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr389, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember390 = { &DiagQueRouter_funcList[0], DiagData390, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr390, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember391 = { &DiagQueRouter_funcList[0], DiagData391, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr391, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember392 = { &DiagQueRouter_funcList[0], DiagData392, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr392, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember393 = { &DiagQueRouter_funcList[0], DiagData393, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr393, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember394 = { &DiagQueRouter_funcList[0], DiagData394, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr394, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember395 = { &DiagQueRouter_funcList[0], DiagData395, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr395, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember396 = { &DiagQueRouter_funcList[0], DiagData396, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr396, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember397 = { &DiagQueRouter_funcList[0], DiagData397, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr397, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember398 = { &DiagQueRouter_funcList[0], DiagData398, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr398, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember399 = { &DiagQueRouter_funcList[0], DiagData399, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr399, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember400 = { &DiagQueRouter_funcList[0], DiagData400, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr400, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember401 = { &DiagQueRouter_funcList[0], DiagData401, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr401, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember402 = { &DiagQueRouter_funcList[0], DiagData402, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr402, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember403 = { &DiagQueRouter_funcList[0], DiagData403, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr403, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember404 = { &DiagQueRouter_funcList[0], DiagData404, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr404, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember405 = { &DiagQueRouter_funcList[0], DiagData405, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr405, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember406 = { &DiagQueRouter_funcList[0], DiagData406, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr406, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember407 = { &DiagQueRouter_funcList[0], DiagData407, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr407, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember408 = { &DiagQueRouter_funcList[0], DiagData408, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr408, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember409 = { &DiagQueRouter_funcList[0], DiagData409, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr409, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember410 = { &DiagQueRouter_funcList[0], DiagData410, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr410, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember411 = { &DiagQueRouter_funcList[0], DiagData411, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr411, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember412 = { &DiagQueRouter_funcList[0], DiagData412, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr412, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember413 = { &DiagQueRouter_funcList[0], DiagData413, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr413, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember414 = { &DiagQueRouter_funcList[0], DiagData414, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr414, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember415 = { &DiagQueRouter_funcList[0], DiagData415, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr415, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember416 = { &DiagQueRouter_funcList[0], DiagData416, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr416, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember417 = { &DiagQueRouter_funcList[0], DiagData417, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr417, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember418 = { &DiagQueRouter_funcList[0], DiagData418, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr418, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember419 = { &DiagQueRouter_funcList[0], DiagData419, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr419, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember420 = { &DiagQueRouter_funcList[0], DiagData420, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr420, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember421 = { &DiagQueRouter_funcList[0], DiagData421, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr421, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember422 = { &DiagQueRouter_funcList[0], DiagData422, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr422, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember423 = { &DiagQueRouter_funcList[0], DiagData423, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr423, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember424 = { &DiagQueRouter_funcList[0], DiagData424, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr424, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember425 = { &DiagQueRouter_funcList[0], DiagData425, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr425, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember426 = { &DiagQueRouter_funcList[0], DiagData426, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr426, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember427 = { &DiagQueRouter_funcList[0], DiagData427, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr427, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember428 = { &DiagQueRouter_funcList[0], DiagData428, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr428, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember429 = { &DiagQueRouter_funcList[0], DiagData429, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr429, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember430 = { &DiagQueRouter_funcList[0], DiagData430, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr430, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember431 = { &DiagQueRouter_funcList[0], DiagData431, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr431, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember432 = { &DiagQueRouter_funcList[0], DiagData432, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr432, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember433 = { &DiagQueRouter_funcList[0], DiagData433, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr433, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember434 = { &DiagQueRouter_funcList[0], DiagData434, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr434, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember435 = { &DiagQueRouter_funcList[0], DiagData435, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr435, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember436 = { &DiagQueRouter_funcList[0], DiagData436, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr436, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember437 = { &DiagQueRouter_funcList[0], DiagData437, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr437, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember438 = { &DiagQueRouter_funcList[0], DiagData438, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr438, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember439 = { &DiagQueRouter_funcList[0], DiagData439, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr439, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember440 = { &DiagQueRouter_funcList[0], DiagData440, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr440, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember441 = { &DiagQueRouter_funcList[0], DiagData441, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr441, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember442 = { &DiagQueRouter_funcList[0], DiagData442, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr442, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember443 = { &DiagQueRouter_funcList[0], DiagData443, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr443, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember444 = { &DiagQueRouter_funcList[0], DiagData444, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr444, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember445 = { &DiagQueRouter_funcList[0], DiagData445, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr445, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember446 = { &DiagQueRouter_funcList[0], DiagData446, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr446, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember447 = { &DiagQueRouter_funcList[0], DiagData447, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr447, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember448 = { &DiagQueRouter_funcList[0], DiagData448, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr448, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember449 = { &DiagQueRouter_funcList[0], DiagData449, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr449, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember450 = { &DiagQueRouter_funcList[0], DiagData450, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr450, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember451 = { &DiagQueRouter_funcList[0], DiagData451, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr451, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember452 = { &DiagQueRouter_funcList[0], DiagData452, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr452, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember453 = { &DiagQueRouter_funcList[0], DiagData453, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr453, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember454 = { &DiagQueRouter_funcList[0], DiagData454, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr454, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember455 = { &DiagQueRouter_funcList[0], DiagData455, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr455, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember456 = { &DiagQueRouter_funcList[0], DiagData456, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr456, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember457 = { &DiagQueRouter_funcList[0], DiagData457, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr457, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember458 = { &DiagQueRouter_funcList[0], DiagData458, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr458, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember459 = { &DiagQueRouter_funcList[0], DiagData459, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr459, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember460 = { &DiagQueRouter_funcList[0], DiagData460, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr460, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember461 = { &DiagQueRouter_funcList[0], DiagData461, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr461, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember462 = { &DiagQueRouter_funcList[0], DiagData462, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr462, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember463 = { &DiagQueRouter_funcList[0], DiagData463, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr463, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember464 = { &DiagQueRouter_funcList[0], DiagData464, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr464, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember465 = { &DiagQueRouter_funcList[0], DiagData465, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr465, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember466 = { &DiagQueRouter_funcList[0], DiagData466, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr466, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember467 = { &DiagQueRouter_funcList[0], DiagData467, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr467, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember468 = { &DiagQueRouter_funcList[0], DiagData468, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr468, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember469 = { &DiagQueRouter_funcList[0], DiagData469, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr469, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember470 = { &DiagQueRouter_funcList[0], DiagData470, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr470, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember471 = { &DiagQueRouter_funcList[0], DiagData471, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr471, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember472 = { &DiagQueRouter_funcList[0], DiagData472, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr472, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember473 = { &DiagQueRouter_funcList[0], DiagData473, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr473, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember474 = { &DiagQueRouter_funcList[0], DiagData474, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr474, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember475 = { &DiagQueRouter_funcList[0], DiagData475, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr475, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember476 = { &DiagQueRouter_funcList[0], DiagData476, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr476, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember477 = { &DiagQueRouter_funcList[0], DiagData477, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr477, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember478 = { &DiagQueRouter_funcList[0], DiagData478, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr478, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember479 = { &DiagQueRouter_funcList[0], DiagData479, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr479, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember480 = { &DiagQueRouter_funcList[0], DiagData480, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr480, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember481 = { &DiagQueRouter_funcList[0], DiagData481, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr481, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember482 = { &DiagQueRouter_funcList[0], DiagData482, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr482, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember483 = { &DiagQueRouter_funcList[0], DiagData483, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr483, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember484 = { &DiagQueRouter_funcList[0], DiagData484, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr484, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember485 = { &DiagQueRouter_funcList[0], DiagData485, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr485, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember486 = { &DiagQueRouter_funcList[0], DiagData486, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr486, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember487 = { &DiagQueRouter_funcList[0], DiagData487, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr487, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember488 = { &DiagQueRouter_funcList[0], DiagData488, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr488, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember489 = { &DiagQueRouter_funcList[0], DiagData489, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr489, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember490 = { &DiagQueRouter_funcList[0], DiagData490, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr490, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember491 = { &DiagQueRouter_funcList[0], DiagData491, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr491, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember492 = { &DiagQueRouter_funcList[0], DiagData492, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr492, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember493 = { &DiagQueRouter_funcList[0], DiagData493, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr493, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember494 = { &DiagQueRouter_funcList[0], DiagData494, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr494, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember495 = { &DiagQueRouter_funcList[0], DiagData495, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr495, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember496 = { &DiagQueRouter_funcList[0], DiagData496, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr496, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember497 = { &DiagQueRouter_funcList[0], DiagData497, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr497, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember498 = { &DiagQueRouter_funcList[0], DiagData498, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr498, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember499 = { &DiagQueRouter_funcList[0], DiagData499, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr499, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember500 = { &DiagQueRouter_funcList[0], DiagData500, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr500, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember501 = { &DiagQueRouter_funcList[0], DiagData501, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr501, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember502 = { &DiagQueRouter_funcList[0], DiagData502, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr502, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember503 = { &DiagQueRouter_funcList[0], DiagData503, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr503, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember504 = { &DiagQueRouter_funcList[0], DiagData504, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr504, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember505 = { &DiagQueRouter_funcList[0], DiagData505, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr505, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember506 = { &DiagQueRouter_funcList[0], DiagData506, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr506, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember507 = { &DiagQueRouter_funcList[0], DiagData507, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr507, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember508 = { &DiagQueRouter_funcList[0], DiagData508, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr508, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember509 = { &DiagQueRouter_funcList[0], DiagData509, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr509, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember510 = { &DiagQueRouter_funcList[0], DiagData510, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr510, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember511 = { &DiagQueRouter_funcList[0], DiagData511, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr511, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember512 = { &DiagQueRouter_funcList[0], DiagData512, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr512, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember513 = { &DiagQueRouter_funcList[0], DiagData513, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr513, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember514 = { &DiagQueRouter_funcList[0], DiagData514, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr514, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember515 = { &DiagQueRouter_funcList[0], DiagData515, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr515, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember516 = { &DiagQueRouter_funcList[0], DiagData516, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr516, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember517 = { &DiagQueRouter_funcList[0], DiagData517, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr517, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember518 = { &DiagQueRouter_funcList[0], DiagData518, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr518, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember519 = { &DiagQueRouter_funcList[0], DiagData519, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr519, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember520 = { &DiagQueRouter_funcList[0], DiagData520, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr520, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember521 = { &DiagQueRouter_funcList[0], DiagData521, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr521, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember522 = { &DiagQueRouter_funcList[0], DiagData522, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr522, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember523 = { &DiagQueRouter_funcList[0], DiagData523, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr523, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember524 = { &DiagQueRouter_funcList[0], DiagData524, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr524, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember525 = { &DiagQueRouter_funcList[0], DiagData525, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr525, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember526 = { &DiagQueRouter_funcList[0], DiagData526, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr526, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember527 = { &DiagQueRouter_funcList[0], DiagData527, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr527, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember528 = { &DiagQueRouter_funcList[0], DiagData528, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr528, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember529 = { &DiagQueRouter_funcList[0], DiagData529, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr529, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember530 = { &DiagQueRouter_funcList[0], DiagData530, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr530, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember531 = { &DiagQueRouter_funcList[0], DiagData531, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr531, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember532 = { &DiagQueRouter_funcList[0], DiagData532, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr532, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember533 = { &DiagQueRouter_funcList[0], DiagData533, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr533, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember534 = { &DiagQueRouter_funcList[0], DiagData534, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr534, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember535 = { &DiagQueRouter_funcList[0], DiagData535, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr535, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember536 = { &DiagQueRouter_funcList[0], DiagData536, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr536, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember537 = { &DiagQueRouter_funcList[0], DiagData537, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr537, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember538 = { &DiagQueRouter_funcList[0], DiagData538, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr538, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember539 = { &DiagQueRouter_funcList[0], DiagData539, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr539, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember540 = { &DiagQueRouter_funcList[0], DiagData540, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr540, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember541 = { &DiagQueRouter_funcList[0], DiagData541, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr541, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember542 = { &DiagQueRouter_funcList[0], DiagData542, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr542, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember543 = { &DiagQueRouter_funcList[0], DiagData543, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr543, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember544 = { &DiagQueRouter_funcList[0], DiagData544, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr544, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember545 = { &DiagQueRouter_funcList[0], DiagData545, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr545, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember546 = { &DiagQueRouter_funcList[0], DiagData546, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr546, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember547 = { &DiagQueRouter_funcList[0], DiagData547, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr547, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember548 = { &DiagQueRouter_funcList[0], DiagData548, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr548, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember549 = { &DiagQueRouter_funcList[0], DiagData549, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr549, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember550 = { &DiagQueRouter_funcList[0], DiagData550, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr550, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember551 = { &DiagQueRouter_funcList[0], DiagData551, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr551, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember552 = { &DiagQueRouter_funcList[0], DiagData552, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr552, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember553 = { &DiagQueRouter_funcList[0], DiagData553, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr553, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember554 = { &DiagQueRouter_funcList[0], DiagData554, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr554, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember555 = { &DiagQueRouter_funcList[0], DiagData555, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr555, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember556 = { &DiagQueRouter_funcList[0], DiagData556, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr556, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember557 = { &DiagQueRouter_funcList[0], DiagData557, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr557, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember558 = { &DiagQueRouter_funcList[0], DiagData558, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr558, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember559 = { &DiagQueRouter_funcList[0], DiagData559, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr559, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember560 = { &DiagQueRouter_funcList[0], DiagData560, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr560, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember561 = { &DiagQueRouter_funcList[0], DiagData561, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr561, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember562 = { &DiagQueRouter_funcList[0], DiagData562, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr562, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember563 = { &DiagQueRouter_funcList[0], DiagData563, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr563, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember564 = { &DiagQueRouter_funcList[0], DiagData564, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr564, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember565 = { &DiagQueRouter_funcList[0], DiagData565, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr565, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember566 = { &DiagQueRouter_funcList[0], DiagData566, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr566, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember567 = { &DiagQueRouter_funcList[0], DiagData567, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr567, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember568 = { &DiagQueRouter_funcList[0], DiagData568, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr568, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember569 = { &DiagQueRouter_funcList[0], DiagData569, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr569, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember570 = { &DiagQueRouter_funcList[0], DiagData570, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr570, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember571 = { &DiagQueRouter_funcList[0], DiagData571, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr571, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember572 = { &DiagQueRouter_funcList[0], DiagData572, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr572, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember573 = { &DiagQueRouter_funcList[0], DiagData573, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr573, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember574 = { &DiagQueRouter_funcList[0], DiagData574, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr574, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember575 = { &DiagQueRouter_funcList[0], DiagData575, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr575, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember576 = { &DiagQueRouter_funcList[0], DiagData576, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr576, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember577 = { &DiagQueRouter_funcList[0], DiagData577, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr577, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember578 = { &DiagQueRouter_funcList[0], DiagData578, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr578, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember579 = { &DiagQueRouter_funcList[0], DiagData579, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr579, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember580 = { &DiagQueRouter_funcList[0], DiagData580, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr580, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember581 = { &DiagQueRouter_funcList[0], DiagData581, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr581, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember582 = { &DiagQueRouter_funcList[0], DiagData582, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr582, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember583 = { &DiagQueRouter_funcList[0], DiagData583, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr583, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember584 = { &DiagQueRouter_funcList[0], DiagData584, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr584, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember585 = { &DiagQueRouter_funcList[0], DiagData585, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr585, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember586 = { &DiagQueRouter_funcList[0], DiagData586, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr586, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember587 = { &DiagQueRouter_funcList[0], DiagData587, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr587, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember588 = { &DiagQueRouter_funcList[0], DiagData588, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr588, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember589 = { &DiagQueRouter_funcList[0], DiagData589, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr589, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember590 = { &DiagQueRouter_funcList[0], DiagData590, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr590, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember591 = { &DiagQueRouter_funcList[0], DiagData591, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr591, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember592 = { &DiagQueRouter_funcList[0], DiagData592, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr592, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember593 = { &DiagQueRouter_funcList[0], DiagData593, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr593, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember594 = { &DiagQueRouter_funcList[0], DiagData594, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr594, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember595 = { &DiagQueRouter_funcList[0], DiagData595, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr595, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember596 = { &DiagQueRouter_funcList[0], DiagData596, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr596, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember597 = { &DiagQueRouter_funcList[0], DiagData597, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr597, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember598 = { &DiagQueRouter_funcList[0], DiagData598, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr598, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember599 = { &DiagQueRouter_funcList[0], DiagData599, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr599, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember600 = { &DiagQueRouter_funcList[0], DiagData600, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr600, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember601 = { &DiagQueRouter_funcList[0], DiagData601, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr601, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember602 = { &DiagQueRouter_funcList[0], DiagData602, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr602, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember603 = { &DiagQueRouter_funcList[0], DiagData603, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr603, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember604 = { &DiagQueRouter_funcList[0], DiagData604, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr604, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember605 = { &DiagQueRouter_funcList[0], DiagData605, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr605, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember606 = { &DiagQueRouter_funcList[0], DiagData606, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr606, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember607 = { &DiagQueRouter_funcList[0], DiagData607, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr607, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember608 = { &DiagQueRouter_funcList[0], DiagData608, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr608, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember609 = { &DiagQueRouter_funcList[0], DiagData609, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr609, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember610 = { &DiagQueRouter_funcList[0], DiagData610, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr610, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember611 = { &DiagQueRouter_funcList[0], DiagData611, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr611, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember612 = { &DiagQueRouter_funcList[0], DiagData612, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr612, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember613 = { &DiagQueRouter_funcList[0], DiagData613, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr613, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember614 = { &DiagQueRouter_funcList[0], DiagData614, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr614, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember615 = { &DiagQueRouter_funcList[0], DiagData615, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr615, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember616 = { &DiagQueRouter_funcList[0], DiagData616, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr616, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember617 = { &DiagQueRouter_funcList[0], DiagData617, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr617, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember618 = { &DiagQueRouter_funcList[0], DiagData618, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr618, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember619 = { &DiagQueRouter_funcList[0], DiagData619, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr619, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember620 = { &DiagQueRouter_funcList[0], DiagData620, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr620, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember621 = { &DiagQueRouter_funcList[0], DiagData621, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr621, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember622 = { &DiagQueRouter_funcList[0], DiagData622, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr622, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember623 = { &DiagQueRouter_funcList[0], DiagData623, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr623, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember624 = { &DiagQueRouter_funcList[0], DiagData624, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr624, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember625 = { &DiagQueRouter_funcList[0], DiagData625, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr625, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember626 = { &DiagQueRouter_funcList[0], DiagData626, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr626, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember627 = { &DiagQueRouter_funcList[0], DiagData627, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr627, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember628 = { &DiagQueRouter_funcList[0], DiagData628, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr628, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember629 = { &DiagQueRouter_funcList[0], DiagData629, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr629, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember630 = { &DiagQueRouter_funcList[0], DiagData630, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr630, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember631 = { &DiagQueRouter_funcList[0], DiagData631, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr631, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember632 = { &DiagQueRouter_funcList[0], DiagData632, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr632, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember633 = { &DiagQueRouter_funcList[0], DiagData633, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr633, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember634 = { &DiagQueRouter_funcList[0], DiagData634, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr634, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember635 = { &DiagQueRouter_funcList[0], DiagData635, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr635, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember636 = { &DiagQueRouter_funcList[0], DiagData636, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr636, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember637 = { &DiagQueRouter_funcList[0], DiagData637, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr637, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember638 = { &DiagQueRouter_funcList[0], DiagData638, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr638, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember639 = { &DiagQueRouter_funcList[0], DiagData639, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr639, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember640 = { &DiagQueRouter_funcList[0], DiagData640, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr640, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember641 = { &DiagQueRouter_funcList[0], DiagData641, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr641, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember642 = { &DiagQueRouter_funcList[0], DiagData642, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr642, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember643 = { &DiagQueRouter_funcList[0], DiagData643, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr643, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember644 = { &DiagQueRouter_funcList[0], DiagData644, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr644, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember645 = { &DiagQueRouter_funcList[0], DiagData645, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr645, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember646 = { &DiagQueRouter_funcList[0], DiagData646, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr646, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember647 = { &DiagQueRouter_funcList[0], DiagData647, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr647, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember648 = { &DiagQueRouter_funcList[0], DiagData648, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr648, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember649 = { &DiagQueRouter_funcList[0], DiagData649, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr649, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember650 = { &DiagQueRouter_funcList[0], DiagData650, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr650, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember651 = { &DiagQueRouter_funcList[0], DiagData651, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr651, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember652 = { &DiagQueRouter_funcList[0], DiagData652, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr652, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember653 = { &DiagQueRouter_funcList[0], DiagData653, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr653, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember654 = { &DiagQueRouter_funcList[0], DiagData654, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr654, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember655 = { &DiagQueRouter_funcList[0], DiagData655, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr655, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember656 = { &DiagQueRouter_funcList[0], DiagData656, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr656, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember657 = { &DiagQueRouter_funcList[0], DiagData657, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr657, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember658 = { &DiagQueRouter_funcList[0], DiagData658, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr658, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember659 = { &DiagQueRouter_funcList[0], DiagData659, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr659, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember660 = { &DiagQueRouter_funcList[0], DiagData660, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr660, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember661 = { &DiagQueRouter_funcList[0], DiagData661, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr661, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember662 = { &DiagQueRouter_funcList[0], DiagData662, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr662, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember663 = { &DiagQueRouter_funcList[0], DiagData663, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr663, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember664 = { &DiagQueRouter_funcList[0], DiagData664, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr664, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember665 = { &DiagQueRouter_funcList[0], DiagData665, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr665, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember666 = { &DiagQueRouter_funcList[0], DiagData666, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr666, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember667 = { &DiagQueRouter_funcList[0], DiagData667, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr667, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember668 = { &DiagQueRouter_funcList[0], DiagData668, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr668, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember669 = { &DiagQueRouter_funcList[0], DiagData669, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr669, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember670 = { &DiagQueRouter_funcList[0], DiagData670, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr670, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember671 = { &DiagQueRouter_funcList[0], DiagData671, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr671, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember672 = { &DiagQueRouter_funcList[0], DiagData672, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr672, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember673 = { &DiagQueRouter_funcList[0], DiagData673, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr673, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember674 = { &DiagQueRouter_funcList[0], DiagData674, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr674, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember675 = { &DiagQueRouter_funcList[0], DiagData675, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr675, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember676 = { &DiagQueRouter_funcList[0], DiagData676, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr676, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember677 = { &DiagQueRouter_funcList[0], DiagData677, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr677, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember678 = { &DiagQueRouter_funcList[0], DiagData678, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr678, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember679 = { &DiagQueRouter_funcList[0], DiagData679, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr679, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember680 = { &DiagQueRouter_funcList[0], DiagData680, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr680, 0U, 48, 0
		};
static CommonBuffer DiagBufferMember681 = { &DiagQueRouter_funcList[0], DiagData681, L3R_FRAMECLASS_DIAG, L3R_DIAG_DATASIZE,
		&DiagHdr681, 0U, 48, 0
		};

/* 共有バッファ */
CommonBuffer *const diagQueRouterBuffer[L3R_DIAG_FRMNUM] = {
	&DiagBufferMember000,
	&DiagBufferMember001,
	&DiagBufferMember002,
	&DiagBufferMember003,
	&DiagBufferMember004,
	&DiagBufferMember005,
	&DiagBufferMember006,
	&DiagBufferMember007,
	&DiagBufferMember008,
	&DiagBufferMember009,
	&DiagBufferMember010,
	&DiagBufferMember011,
	&DiagBufferMember012,
	&DiagBufferMember013,
	&DiagBufferMember014,
	&DiagBufferMember015,
	&DiagBufferMember016,
	&DiagBufferMember017,
	&DiagBufferMember018,
	&DiagBufferMember019,
	&DiagBufferMember020,
	&DiagBufferMember021,
	&DiagBufferMember022,
	&DiagBufferMember023,
	&DiagBufferMember024,
	&DiagBufferMember025,
	&DiagBufferMember026,
	&DiagBufferMember027,
	&DiagBufferMember028,
	&DiagBufferMember029,
	&DiagBufferMember030,
	&DiagBufferMember031,
	&DiagBufferMember032,
	&DiagBufferMember033,
	&DiagBufferMember034,
	&DiagBufferMember035,
	&DiagBufferMember036,
	&DiagBufferMember037,
	&DiagBufferMember038,
	&DiagBufferMember039,
	&DiagBufferMember040,
	&DiagBufferMember041,
	&DiagBufferMember042,
	&DiagBufferMember043,
	&DiagBufferMember044,
	&DiagBufferMember045,
	&DiagBufferMember046,
	&DiagBufferMember047,
	&DiagBufferMember048,
	&DiagBufferMember049,
	&DiagBufferMember050,
	&DiagBufferMember051,
	&DiagBufferMember052,
	&DiagBufferMember053,
	&DiagBufferMember054,
	&DiagBufferMember055,
	&DiagBufferMember056,
	&DiagBufferMember057,
	&DiagBufferMember058,
	&DiagBufferMember059,
	&DiagBufferMember060,
	&DiagBufferMember061,
	&DiagBufferMember062,
	&DiagBufferMember063,
	&DiagBufferMember064,
	&DiagBufferMember065,
	&DiagBufferMember066,
	&DiagBufferMember067,
	&DiagBufferMember068,
	&DiagBufferMember069,
	&DiagBufferMember070,
	&DiagBufferMember071,
	&DiagBufferMember072,
	&DiagBufferMember073,
	&DiagBufferMember074,
	&DiagBufferMember075,
	&DiagBufferMember076,
	&DiagBufferMember077,
	&DiagBufferMember078,
	&DiagBufferMember079,
	&DiagBufferMember080,
	&DiagBufferMember081,
	&DiagBufferMember082,
	&DiagBufferMember083,
	&DiagBufferMember084,
	&DiagBufferMember085,
	&DiagBufferMember086,
	&DiagBufferMember087,
	&DiagBufferMember088,
	&DiagBufferMember089,
	&DiagBufferMember090,
	&DiagBufferMember091,
	&DiagBufferMember092,
	&DiagBufferMember093,
	&DiagBufferMember094,
	&DiagBufferMember095,
	&DiagBufferMember096,
	&DiagBufferMember097,
	&DiagBufferMember098,
	&DiagBufferMember099,
	&DiagBufferMember100,
	&DiagBufferMember101,
	&DiagBufferMember102,
	&DiagBufferMember103,
	&DiagBufferMember104,
	&DiagBufferMember105,
	&DiagBufferMember106,
	&DiagBufferMember107,
	&DiagBufferMember108,
	&DiagBufferMember109,
	&DiagBufferMember110,
	&DiagBufferMember111,
	&DiagBufferMember112,
	&DiagBufferMember113,
	&DiagBufferMember114,
	&DiagBufferMember115,
	&DiagBufferMember116,
	&DiagBufferMember117,
	&DiagBufferMember118,
	&DiagBufferMember119,
	&DiagBufferMember120,
	&DiagBufferMember121,
	&DiagBufferMember122,
	&DiagBufferMember123,
	&DiagBufferMember124,
	&DiagBufferMember125,
	&DiagBufferMember126,
	&DiagBufferMember127,
	&DiagBufferMember128,
	&DiagBufferMember129,
	&DiagBufferMember130,
	&DiagBufferMember131,
	&DiagBufferMember132,
	&DiagBufferMember133,
	&DiagBufferMember134,
	&DiagBufferMember135,
	&DiagBufferMember136,
	&DiagBufferMember137,
	&DiagBufferMember138,
	&DiagBufferMember139,
	&DiagBufferMember140,
	&DiagBufferMember141,
	&DiagBufferMember142,
	&DiagBufferMember143,
	&DiagBufferMember144,
	&DiagBufferMember145,
	&DiagBufferMember146,
	&DiagBufferMember147,
	&DiagBufferMember148,
	&DiagBufferMember149,
	&DiagBufferMember150,
	&DiagBufferMember151,
	&DiagBufferMember152,
	&DiagBufferMember153,
	&DiagBufferMember154,
	&DiagBufferMember155,
	&DiagBufferMember156,
	&DiagBufferMember157,
	&DiagBufferMember158,
	&DiagBufferMember159,
	&DiagBufferMember160,
	&DiagBufferMember161,
	&DiagBufferMember162,
	&DiagBufferMember163,
	&DiagBufferMember164,
	&DiagBufferMember165,
	&DiagBufferMember166,
	&DiagBufferMember167,
	&DiagBufferMember168,
	&DiagBufferMember169,
	&DiagBufferMember170,
	&DiagBufferMember171,
	&DiagBufferMember172,
	&DiagBufferMember173,
	&DiagBufferMember174,
	&DiagBufferMember175,
	&DiagBufferMember176,
	&DiagBufferMember177,
	&DiagBufferMember178,
	&DiagBufferMember179,
	&DiagBufferMember180,
	&DiagBufferMember181,
	&DiagBufferMember182,
	&DiagBufferMember183,
	&DiagBufferMember184,
	&DiagBufferMember185,
	&DiagBufferMember186,
	&DiagBufferMember187,
	&DiagBufferMember188,
	&DiagBufferMember189,
	&DiagBufferMember190,
	&DiagBufferMember191,
	&DiagBufferMember192,
	&DiagBufferMember193,
	&DiagBufferMember194,
	&DiagBufferMember195,
	&DiagBufferMember196,
	&DiagBufferMember197,
	&DiagBufferMember198,
	&DiagBufferMember199,
	&DiagBufferMember200,
	&DiagBufferMember201,
	&DiagBufferMember202,
	&DiagBufferMember203,
	&DiagBufferMember204,
	&DiagBufferMember205,
	&DiagBufferMember206,
	&DiagBufferMember207,
	&DiagBufferMember208,
	&DiagBufferMember209,
	&DiagBufferMember210,
	&DiagBufferMember211,
	&DiagBufferMember212,
	&DiagBufferMember213,
	&DiagBufferMember214,
	&DiagBufferMember215,
	&DiagBufferMember216,
	&DiagBufferMember217,
	&DiagBufferMember218,
	&DiagBufferMember219,
	&DiagBufferMember220,
	&DiagBufferMember221,
	&DiagBufferMember222,
	&DiagBufferMember223,
	&DiagBufferMember224,
	&DiagBufferMember225,
	&DiagBufferMember226,
	&DiagBufferMember227,
	&DiagBufferMember228,
	&DiagBufferMember229,
	&DiagBufferMember230,
	&DiagBufferMember231,
	&DiagBufferMember232,
	&DiagBufferMember233,
	&DiagBufferMember234,
	&DiagBufferMember235,
	&DiagBufferMember236,
	&DiagBufferMember237,
	&DiagBufferMember238,
	&DiagBufferMember239,
	&DiagBufferMember240,
	&DiagBufferMember241,
	&DiagBufferMember242,
	&DiagBufferMember243,
	&DiagBufferMember244,
	&DiagBufferMember245,
	&DiagBufferMember246,
	&DiagBufferMember247,
	&DiagBufferMember248,
	&DiagBufferMember249,
	&DiagBufferMember250,
	&DiagBufferMember251,
	&DiagBufferMember252,
	&DiagBufferMember253,
	&DiagBufferMember254,
	&DiagBufferMember255,
	&DiagBufferMember256,
	&DiagBufferMember257,
	&DiagBufferMember258,
	&DiagBufferMember259,
	&DiagBufferMember260,
	&DiagBufferMember261,
	&DiagBufferMember262,
	&DiagBufferMember263,
	&DiagBufferMember264,
	&DiagBufferMember265,
	&DiagBufferMember266,
	&DiagBufferMember267,
	&DiagBufferMember268,
	&DiagBufferMember269,
	&DiagBufferMember270,
	&DiagBufferMember271,
	&DiagBufferMember272,
	&DiagBufferMember273,
	&DiagBufferMember274,
	&DiagBufferMember275,
	&DiagBufferMember276,
	&DiagBufferMember277,
	&DiagBufferMember278,
	&DiagBufferMember279,
	&DiagBufferMember280,
	&DiagBufferMember281,
	&DiagBufferMember282,
	&DiagBufferMember283,
	&DiagBufferMember284,
	&DiagBufferMember285,
	&DiagBufferMember286,
	&DiagBufferMember287,
	&DiagBufferMember288,
	&DiagBufferMember289,
	&DiagBufferMember290,
	&DiagBufferMember291,
	&DiagBufferMember292,
	&DiagBufferMember293,
	&DiagBufferMember294,
	&DiagBufferMember295,
	&DiagBufferMember296,
	&DiagBufferMember297,
	&DiagBufferMember298,
	&DiagBufferMember299,
	&DiagBufferMember300,
	&DiagBufferMember301,
	&DiagBufferMember302,
	&DiagBufferMember303,
	&DiagBufferMember304,
	&DiagBufferMember305,
	&DiagBufferMember306,
	&DiagBufferMember307,
	&DiagBufferMember308,
	&DiagBufferMember309,
	&DiagBufferMember310,
	&DiagBufferMember311,
	&DiagBufferMember312,
	&DiagBufferMember313,
	&DiagBufferMember314,
	&DiagBufferMember315,
	&DiagBufferMember316,
	&DiagBufferMember317,
	&DiagBufferMember318,
	&DiagBufferMember319,
	&DiagBufferMember320,
	&DiagBufferMember321,
	&DiagBufferMember322,
	&DiagBufferMember323,
	&DiagBufferMember324,
	&DiagBufferMember325,
	&DiagBufferMember326,
	&DiagBufferMember327,
	&DiagBufferMember328,
	&DiagBufferMember329,
	&DiagBufferMember330,
	&DiagBufferMember331,
	&DiagBufferMember332,
	&DiagBufferMember333,
	&DiagBufferMember334,
	&DiagBufferMember335,
	&DiagBufferMember336,
	&DiagBufferMember337,
	&DiagBufferMember338,
	&DiagBufferMember339,
	&DiagBufferMember340,
	&DiagBufferMember341,
	&DiagBufferMember342,
	&DiagBufferMember343,
	&DiagBufferMember344,
	&DiagBufferMember345,
	&DiagBufferMember346,
	&DiagBufferMember347,
	&DiagBufferMember348,
	&DiagBufferMember349,
	&DiagBufferMember350,
	&DiagBufferMember351,
	&DiagBufferMember352,
	&DiagBufferMember353,
	&DiagBufferMember354,
	&DiagBufferMember355,
	&DiagBufferMember356,
	&DiagBufferMember357,
	&DiagBufferMember358,
	&DiagBufferMember359,
	&DiagBufferMember360,
	&DiagBufferMember361,
	&DiagBufferMember362,
	&DiagBufferMember363,
	&DiagBufferMember364,
	&DiagBufferMember365,
	&DiagBufferMember366,
	&DiagBufferMember367,
	&DiagBufferMember368,
	&DiagBufferMember369,
	&DiagBufferMember370,
	&DiagBufferMember371,
	&DiagBufferMember372,
	&DiagBufferMember373,
	&DiagBufferMember374,
	&DiagBufferMember375,
	&DiagBufferMember376,
	&DiagBufferMember377,
	&DiagBufferMember378,
	&DiagBufferMember379,
	&DiagBufferMember380,
	&DiagBufferMember381,
	&DiagBufferMember382,
	&DiagBufferMember383,
	&DiagBufferMember384,
	&DiagBufferMember385,
	&DiagBufferMember386,
	&DiagBufferMember387,
	&DiagBufferMember388,
	&DiagBufferMember389,
	&DiagBufferMember390,
	&DiagBufferMember391,
	&DiagBufferMember392,
	&DiagBufferMember393,
	&DiagBufferMember394,
	&DiagBufferMember395,
	&DiagBufferMember396,
	&DiagBufferMember397,
	&DiagBufferMember398,
	&DiagBufferMember399,
	&DiagBufferMember400,
	&DiagBufferMember401,
	&DiagBufferMember402,
	&DiagBufferMember403,
	&DiagBufferMember404,
	&DiagBufferMember405,
	&DiagBufferMember406,
	&DiagBufferMember407,
	&DiagBufferMember408,
	&DiagBufferMember409,
	&DiagBufferMember410,
	&DiagBufferMember411,
	&DiagBufferMember412,
	&DiagBufferMember413,
	&DiagBufferMember414,
	&DiagBufferMember415,
	&DiagBufferMember416,
	&DiagBufferMember417,
	&DiagBufferMember418,
	&DiagBufferMember419,
	&DiagBufferMember420,
	&DiagBufferMember421,
	&DiagBufferMember422,
	&DiagBufferMember423,
	&DiagBufferMember424,
	&DiagBufferMember425,
	&DiagBufferMember426,
	&DiagBufferMember427,
	&DiagBufferMember428,
	&DiagBufferMember429,
	&DiagBufferMember430,
	&DiagBufferMember431,
	&DiagBufferMember432,
	&DiagBufferMember433,
	&DiagBufferMember434,
	&DiagBufferMember435,
	&DiagBufferMember436,
	&DiagBufferMember437,
	&DiagBufferMember438,
	&DiagBufferMember439,
	&DiagBufferMember440,
	&DiagBufferMember441,
	&DiagBufferMember442,
	&DiagBufferMember443,
	&DiagBufferMember444,
	&DiagBufferMember445,
	&DiagBufferMember446,
	&DiagBufferMember447,
	&DiagBufferMember448,
	&DiagBufferMember449,
	&DiagBufferMember450,
	&DiagBufferMember451,
	&DiagBufferMember452,
	&DiagBufferMember453,
	&DiagBufferMember454,
	&DiagBufferMember455,
	&DiagBufferMember456,
	&DiagBufferMember457,
	&DiagBufferMember458,
	&DiagBufferMember459,
	&DiagBufferMember460,
	&DiagBufferMember461,
	&DiagBufferMember462,
	&DiagBufferMember463,
	&DiagBufferMember464,
	&DiagBufferMember465,
	&DiagBufferMember466,
	&DiagBufferMember467,
	&DiagBufferMember468,
	&DiagBufferMember469,
	&DiagBufferMember470,
	&DiagBufferMember471,
	&DiagBufferMember472,
	&DiagBufferMember473,
	&DiagBufferMember474,
	&DiagBufferMember475,
	&DiagBufferMember476,
	&DiagBufferMember477,
	&DiagBufferMember478,
	&DiagBufferMember479,
	&DiagBufferMember480,
	&DiagBufferMember481,
	&DiagBufferMember482,
	&DiagBufferMember483,
	&DiagBufferMember484,
	&DiagBufferMember485,
	&DiagBufferMember486,
	&DiagBufferMember487,
	&DiagBufferMember488,
	&DiagBufferMember489,
	&DiagBufferMember490,
	&DiagBufferMember491,
	&DiagBufferMember492,
	&DiagBufferMember493,
	&DiagBufferMember494,
	&DiagBufferMember495,
	&DiagBufferMember496,
	&DiagBufferMember497,
	&DiagBufferMember498,
	&DiagBufferMember499,
	&DiagBufferMember500,
	&DiagBufferMember501,
	&DiagBufferMember502,
	&DiagBufferMember503,
	&DiagBufferMember504,
	&DiagBufferMember505,
	&DiagBufferMember506,
	&DiagBufferMember507,
	&DiagBufferMember508,
	&DiagBufferMember509,
	&DiagBufferMember510,
	&DiagBufferMember511,
	&DiagBufferMember512,
	&DiagBufferMember513,
	&DiagBufferMember514,
	&DiagBufferMember515,
	&DiagBufferMember516,
	&DiagBufferMember517,
	&DiagBufferMember518,
	&DiagBufferMember519,
	&DiagBufferMember520,
	&DiagBufferMember521,
	&DiagBufferMember522,
	&DiagBufferMember523,
	&DiagBufferMember524,
	&DiagBufferMember525,
	&DiagBufferMember526,
	&DiagBufferMember527,
	&DiagBufferMember528,
	&DiagBufferMember529,
	&DiagBufferMember530,
	&DiagBufferMember531,
	&DiagBufferMember532,
	&DiagBufferMember533,
	&DiagBufferMember534,
	&DiagBufferMember535,
	&DiagBufferMember536,
	&DiagBufferMember537,
	&DiagBufferMember538,
	&DiagBufferMember539,
	&DiagBufferMember540,
	&DiagBufferMember541,
	&DiagBufferMember542,
	&DiagBufferMember543,
	&DiagBufferMember544,
	&DiagBufferMember545,
	&DiagBufferMember546,
	&DiagBufferMember547,
	&DiagBufferMember548,
	&DiagBufferMember549,
	&DiagBufferMember550,
	&DiagBufferMember551,
	&DiagBufferMember552,
	&DiagBufferMember553,
	&DiagBufferMember554,
	&DiagBufferMember555,
	&DiagBufferMember556,
	&DiagBufferMember557,
	&DiagBufferMember558,
	&DiagBufferMember559,
	&DiagBufferMember560,
	&DiagBufferMember561,
	&DiagBufferMember562,
	&DiagBufferMember563,
	&DiagBufferMember564,
	&DiagBufferMember565,
	&DiagBufferMember566,
	&DiagBufferMember567,
	&DiagBufferMember568,
	&DiagBufferMember569,
	&DiagBufferMember570,
	&DiagBufferMember571,
	&DiagBufferMember572,
	&DiagBufferMember573,
	&DiagBufferMember574,
	&DiagBufferMember575,
	&DiagBufferMember576,
	&DiagBufferMember577,
	&DiagBufferMember578,
	&DiagBufferMember579,
	&DiagBufferMember580,
	&DiagBufferMember581,
	&DiagBufferMember582,
	&DiagBufferMember583,
	&DiagBufferMember584,
	&DiagBufferMember585,
	&DiagBufferMember586,
	&DiagBufferMember587,
	&DiagBufferMember588,
	&DiagBufferMember589,
	&DiagBufferMember590,
	&DiagBufferMember591,
	&DiagBufferMember592,
	&DiagBufferMember593,
	&DiagBufferMember594,
	&DiagBufferMember595,
	&DiagBufferMember596,
	&DiagBufferMember597,
	&DiagBufferMember598,
	&DiagBufferMember599,
	&DiagBufferMember600,
	&DiagBufferMember601,
	&DiagBufferMember602,
	&DiagBufferMember603,
	&DiagBufferMember604,
	&DiagBufferMember605,
	&DiagBufferMember606,
	&DiagBufferMember607,
	&DiagBufferMember608,
	&DiagBufferMember609,
	&DiagBufferMember610,
	&DiagBufferMember611,
	&DiagBufferMember612,
	&DiagBufferMember613,
	&DiagBufferMember614,
	&DiagBufferMember615,
	&DiagBufferMember616,
	&DiagBufferMember617,
	&DiagBufferMember618,
	&DiagBufferMember619,
	&DiagBufferMember620,
	&DiagBufferMember621,
	&DiagBufferMember622,
	&DiagBufferMember623,
	&DiagBufferMember624,
	&DiagBufferMember625,
	&DiagBufferMember626,
	&DiagBufferMember627,
	&DiagBufferMember628,
	&DiagBufferMember629,
	&DiagBufferMember630,
	&DiagBufferMember631,
	&DiagBufferMember632,
	&DiagBufferMember633,
	&DiagBufferMember634,
	&DiagBufferMember635,
	&DiagBufferMember636,
	&DiagBufferMember637,
	&DiagBufferMember638,
	&DiagBufferMember639,
	&DiagBufferMember640,
	&DiagBufferMember641,
	&DiagBufferMember642,
	&DiagBufferMember643,
	&DiagBufferMember644,
	&DiagBufferMember645,
	&DiagBufferMember646,
	&DiagBufferMember647,
	&DiagBufferMember648,
	&DiagBufferMember649,
	&DiagBufferMember650,
	&DiagBufferMember651,
	&DiagBufferMember652,
	&DiagBufferMember653,
	&DiagBufferMember654,
	&DiagBufferMember655,
	&DiagBufferMember656,
	&DiagBufferMember657,
	&DiagBufferMember658,
	&DiagBufferMember659,
	&DiagBufferMember660,
	&DiagBufferMember661,
	&DiagBufferMember662,
	&DiagBufferMember663,
	&DiagBufferMember664,
	&DiagBufferMember665,
	&DiagBufferMember666,
	&DiagBufferMember667,
	&DiagBufferMember668,
	&DiagBufferMember669,
	&DiagBufferMember670,
	&DiagBufferMember671,
	&DiagBufferMember672,
	&DiagBufferMember673,
	&DiagBufferMember674,
	&DiagBufferMember675,
	&DiagBufferMember676,
	&DiagBufferMember677,
	&DiagBufferMember678,
	&DiagBufferMember679,
	&DiagBufferMember680,
	&DiagBufferMember681
 };

#define GW_L3R_STOP_SEC_CONST
#include "GW_L3R_Memmap.h"

/*--------------------------------------------------------------------------*/
/*		ファイル内変数														*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*		プロトタイプ宣言													*/
/*--------------------------------------------------------------------------*/
