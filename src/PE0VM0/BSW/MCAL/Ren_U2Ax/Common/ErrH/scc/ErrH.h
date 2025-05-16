/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef ERRH_H 
#define ERRH_H 

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* defines																						*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*----------------------------------------------------------------------------------------------*/
/* ECM(NCF) Configuration																		*/
/*----------------------------------------------------------------------------------------------*/
/* ERROR Control Module(ECM) MODE Configuration Parameter */
																/* IRE NNNI*/
#define			ERRH_NCF_MODE_IRTYPE_EI			(0)				/* 000 0000 */ /* 割り込みタイプ：EIレベル割り込み		 */
#define			ERRH_NCF_MODE_IRTYPE_FE			(1)				/* 000 0001 */ /* 割り込みタイプ：FEレベル割り込み		 */

#define			ERRH_NCF_MODE_NOTIF_SHIFT		(1)				/* 通知先コアテーブル作成時のビットシフト数				 */
#define			ERRH_NCF_MODE_NOTIF_NONE		(0)				/* 0000 0000 */ /* ECM 割り込み禁止						 */
#define			ERRH_NCF_MODE_NOTIF_CORE0		(2)				/* 0000 0010 */ /* Core0から割り込み通知				 */
#define			ERRH_NCF_MODE_NOTIF_CORE1		(4)				/* 0000 0100 */ /* Core1から割り込み通知				 */
#define			ERRH_NCF_MODE_NOTIF_CORE2		(8)				/* 0000 1000 */ /* Core2から割り込み通知				 */
#define			ERRH_NCF_MODE_NOTIF_CORE3		(16)			/* 0001 0000 */ /* Core3から割り込み通知				 */

#define			ERRH_NCF_MODE_EOUT_SHIFT		(5)				/* エラー端子出力テーブル作成時のビットシフト数			 */
#define			ERRH_NCF_MODE_EOUT_0			(0)				/* 0000 0000 */ /* エラー端子出力をマスクしない			 */
#define			ERRH_NCF_MODE_EOUT_1			(32)			/* 0010 0000 */ /* エラー端子出力をマスク				 */

#define			ERRH_NCF_MODE_RESET_SHIFT		(6)				/* ECM内部リセットテーブル作成時のビットシフト数		 */
#define			ERRH_NCF_MODE_RESET_0			(0)				/* 0000 0000 */ /* ECM内部リセット不可					 */
#define			ERRH_NCF_MODE_RESET_1			(64)			/* 0100 0000 */ /* エラー発生でECM内部リセット			 */

#define			ERRH_NCF_MODE_INIT_INFORM_SHIFT	(7)				/* 初期化時通知テーブル作成時のビットシフト数			 */
#define			ERRH_NCF_MODE_INIT_INFORM_0		(0)				/* 0000 0000 */ /* 初期化時通知しない					 */
#define			ERRH_NCF_MODE_INIT_INFORM_1		(128)			/* 1000 0000 */ /* 初期化時通知する						 */

/* ERROR Control Module (ECM) Configuration Mask Parameter */
#define			ERRH_NCF_MASK_IRTYPE_1BIT		(1)				/* **** ***1 */
#define			ERRH_NCF_MASK_NOTIF_CORE0_1BIT	(2)				/* **** **1* */
#define			ERRH_NCF_MASK_NOTIF_CORE1_1BIT	(4)				/* **** *1** */
#define			ERRH_NCF_MASK_NOTIF_CORE2_1BIT	(8)				/* **** 1*** */
#define			ERRH_NCF_MASK_NOTIF_CORE3_1BIT	(16)			/* ***1 **** */
#define			ERRH_NCF_MASK_EOUT_1BIT			(32)			/* **1* **** */
#define			ERRH_NCF_MASK_RESET_1BIT		(64)			/* *1** **** */
#define			ERRH_NCF_MASK_INIT_INFORM_1BIT	(128)			/* 1*** **** */

/* ERROR Control Module (ECM) Configuration Bit Shift Value */
#define			ERRH_NCF_MASK_NOTIF_CORE0_RSHIFT1BIT	(1)		/* 1ビット右シフト */
#define			ERRH_NCF_MASK_NOTIF_CORE1_RSHIFT2BIT	(2)		/* 2ビット右シフト */
#define			ERRH_NCF_MASK_NOTIF_CORE2_RSHIFT3BIT	(3)		/* 3ビット右シフト */
#define			ERRH_NCF_MASK_NOTIF_CORE3_RSHIFT4BIT	(4)		/* 4ビット右シフト */
#define			ERRH_NCF_MASK_EOUT_RSHIFT5BIT			(5)		/* 5ビット右シフト */
#define			ERRH_NCF_MASK_RESET_RSHIFT6BIT			(6)		/* 6ビット右シフト */
#define			ERRH_NCF_MASK_INIT_INFORM_RSHIFT7BIT	(7)		/* 7ビット右シフト */

/* ERROR Control Module (ECM) NCF ID */
#define			u2ERRH_NCF0_ID					((U2)0U)		/* エラー出力モニタ */
#define			u2ERRH_NCF1_ID					((U2)1U)		/* 予約 */
#define			u2ERRH_NCF2_ID					((U2)2U)		/* ECMmESET モニタ */
#define			u2ERRH_NCF3_ID					((U2)3U)		/* ECMmESET0 モニタ */
#define			u2ERRH_NCF4_ID					((U2)4U)		/* ECMmESET1 モニタ */
#define			u2ERRH_NCF5_ID					((U2)5U)		/* ECMmESET2 モニタ */
#define			u2ERRH_NCF6_ID					((U2)6U)		/* ECMmESET3 モニタ */
#define			u2ERRH_NCF7_ID					((U2)7U)		/* 予約 */
#define			u2ERRH_NCF8_ID					((U2)8U)		/* 予約 */
#define			u2ERRH_NCF9_ID					((U2)9U)		/* 予約 */
#define			u2ERRH_NCF10_ID					((U2)10U)		/* 予約 */
#define			u2ERRH_NCF11_ID					((U2)11U)		/* ディレイタイマオーバーフロー(エラー出力) */
#define			u2ERRH_NCF12_ID					((U2)12U)		/* 予約 */
#define			u2ERRH_NCF13_ID					((U2)13U)		/* 予約 */
#define			u2ERRH_NCF14_ID					((U2)14U)		/* 予約 */
#define			u2ERRH_NCF15_ID					((U2)15U)		/* 予約 */
#define			u2ERRH_NCF16_ID					((U2)16U)		/* 予約 */
#define			u2ERRH_NCF17_ID					((U2)17U)		/* 予約 */
#define			u2ERRH_NCF18_ID					((U2)18U)		/* 予約 */
#define			u2ERRH_NCF19_ID					((U2)19U)		/* 予約 */
#define			u2ERRH_NCF20_ID					((U2)20U)		/* ECM コンペアエラー */
#define			u2ERRH_NCF21_ID					((U2)21U)		/* 予約 */
#define			u2ERRH_NCF22_ID					((U2)22U)		/* 予約 */
#define			u2ERRH_NCF23_ID					((U2)23U)		/* 予約 */
#define			u2ERRH_NCF24_ID					((U2)24U)		/* モードエラー 製造テストモードの意図しないアクティブ化 */
#define			u2ERRH_NCF25_ID					((U2)25U)		/* モードエラー 通常動作モードの意図しないアクティブ化 */
#define			u2ERRH_NCF26_ID					((U2)26U)		/* モードエラー 通常動作モードの意図しない非アクティブ化 */
#define			u2ERRH_NCF27_ID					((U2)27U)		/* モードエラー シリアルプログラミングモードの意図しないアクティブ化 */
#define			u2ERRH_NCF28_ID					((U2)28U)		/* モードエラー ユーザブートモードの意図しないアクティブ化 */
#define			u2ERRH_NCF29_ID					((U2)29U)		/* モードエラー ユーザブートモードの意図しない非アクティブ化 */
#define			u2ERRH_NCF30_ID					((U2)30U)		/* モードエラー モードチェックエラー */
#define			u2ERRH_NCF31_ID					((U2)31U)		/* 予約 */
#define			u2ERRH_NCF32_ID					((U2)32U)		/* フラッシュアクセスエラー */
#define			u2ERRH_NCF33_ID					((U2)33U)		/* FACI リセット転送エラー */
#define			u2ERRH_NCF34_ID					((U2)34U)		/* BIST パラメータ転送エラー */
#define			u2ERRH_NCF35_ID					((U2)35U)		/* 予約 */
#define			u2ERRH_NCF36_ID					((U2)36U)		/* DTS コンペアエラー */
#define			u2ERRH_NCF37_ID					((U2)37U)		/* sDMACのバスブリッジコンペアエラー */
#define			u2ERRH_NCF38_ID					((U2)38U)		/* バスブリッジコンペアエラー */
#define			u2ERRH_NCF39_ID					((U2)39U)		/* 予約 */
#define			u2ERRH_NCF40_ID					((U2)40U)		/* プロセッサ間要素バスルーティングエラー */
#define			u2ERRH_NCF41_ID					((U2)41U)		/* クラスタ間バス(IBus)ルーティングエラー */
#define			u2ERRH_NCF42_ID					((U2)42U)		/* 周辺機器バス(P-Bus)ルーティングエラー */
#define			u2ERRH_NCF43_ID					((U2)43U)		/* CRAMバスルーティングエラー */
#define			u2ERRH_NCF44_ID					((U2)44U)		/* システムバスルーティングエラー */
#define			u2ERRH_NCF45_ID					((U2)45U)		/* グローバルフラッシュバスルーティングエラー */
#define			u2ERRH_NCF46_ID					((U2)46U)		/* ローカルフラッシュバスルーティングエラー */
#define			u2ERRH_NCF47_ID					((U2)47U)		/* 予約 */
#define			u2ERRH_NCF48_ID					((U2)48U)		/* CLK_MOSCのクロックモニタエラー */
#define			u2ERRH_NCF49_ID					((U2)49U)		/* CLK_WDTのクロックモニ */
#define			u2ERRH_NCF50_ID					((U2)50U)		/* CLK_WDTのクロックモニタエラー */
#define			u2ERRH_NCF51_ID					((U2)51U)		/* CLK_LSIOSCのクロックモニタエラー */
#define			u2ERRH_NCF52_ID					((U2)52U)		/* CLK_LSBのクロックモニタエラー */
#define			u2ERRH_NCF53_ID					((U2)53U)		/* CLK_UHSBのクロックモニタエラー */
#define			u2ERRH_NCF54_ID					((U2)54U)		/* CLK_HBUSのクロックモニタエラー */
#define			u2ERRH_NCF55_ID					((U2)55U)		/* 予約 */
#define			u2ERRH_NCF56_ID					((U2)56U)		/* 予約 */
#define			u2ERRH_NCF57_ID					((U2)57U)		/* OSTM1割り込み */
#define			u2ERRH_NCF58_ID					((U2)58U)		/* OSTM2割り込み */
#define			u2ERRH_NCF59_ID					((U2)59U)		/* OSTM3割り込み */
#define			u2ERRH_NCF60_ID					((U2)60U)		/* OSTM4割り込み */
#define			u2ERRH_NCF61_ID					((U2)61U)		/* OSTM5割り込み */
#define			u2ERRH_NCF62_ID					((U2)62U)		/* OSTM6割り込み */
#define			u2ERRH_NCF63_ID					((U2)63U)		/* OSTM7割り込み */
#define			u2ERRH_NCF64_ID					((U2)64U)		/* OSTM8割り込み */
#define			u2ERRH_NCF65_ID					((U2)65U)		/* OSTM9割り込み */
#define			u2ERRH_NCF66_ID					((U2)66U)		/* 予約 */
#define			u2ERRH_NCF67_ID					((U2)67U)		/* 予約 */
#define			u2ERRH_NCF68_ID					((U2)68U)		/* 予約 */
#define			u2ERRH_NCF69_ID					((U2)69U)		/* 予約 */
#define			u2ERRH_NCF70_ID					((U2)70U)		/* 予約 */
#define			u2ERRH_NCF71_ID					((U2)71U)		/* 予約 */
#define			u2ERRH_NCF72_ID					((U2)72U)		/* 予約 */
#define			u2ERRH_NCF73_ID					((U2)73U)		/* A/Dコンバータパリティエラー */
#define			u2ERRH_NCF74_ID					((U2)74U)		/* 予約 */
#define			u2ERRH_NCF75_ID					((U2)75U)		/* 予約 */
#define			u2ERRH_NCF76_ID					((U2)76U)		/* 予約 */
#define			u2ERRH_NCF77_ID					((U2)77U)		/* 温度センサーエラー */
#define			u2ERRH_NCF78_ID					((U2)78U)		/* 予約 */
#define			u2ERRH_NCF79_ID					((U2)79U)		/* 予約 */
#define			u2ERRH_NCF80_ID					((U2)80U)		/* 予約 */
#define			u2ERRH_NCF81_ID					((U2)81U)		/* コードフラッシュ、アドレスパリティエラー */
#define			u2ERRH_NCF82_ID					((U2)82U)		/* コードフラッシュ、データECC 2ビットエラー */
#define			u2ERRH_NCF83_ID					((U2)83U)		/* コードフラッシュ、データECC 1ビットエラー */
#define			u2ERRH_NCF84_ID					((U2)84U)		/* コードフラッシュ、ECCオーバーフローエラー */
#define			u2ERRH_NCF85_ID					((U2)85U)		/* 予約 */
#define			u2ERRH_NCF86_ID					((U2)86U)		/* 予約 */
#define			u2ERRH_NCF87_ID					((U2)87U)		/* 予約 */
#define			u2ERRH_NCF88_ID					((U2)88U)		/* 予約 */
#define			u2ERRH_NCF89_ID					((U2)89U)		/* データフラッシュ、データECC 2ビットエラー */
#define			u2ERRH_NCF90_ID					((U2)90U)		/* データフラッシュ、データECC 1ビットエラー */
#define			u2ERRH_NCF91_ID					((U2)91U)		/* データフラッシュ、ECCオーバーフローエラー */
#define			u2ERRH_NCF92_ID					((U2)92U)		/* 予約 */
#define			u2ERRH_NCF93_ID					((U2)93U)		/* 予約 */
#define			u2ERRH_NCF94_ID					((U2)94U)		/* 予約 */
#define			u2ERRH_NCF95_ID					((U2)95U)		/* 予約 */
#define			u2ERRH_NCF96_ID					((U2)96U)		/* 予約 */
#define			u2ERRH_NCF97_ID					((U2)97U)		/* Local RAM、データECC 2ビットエラー */
#define			u2ERRH_NCF98_ID					((U2)98U)		/* Local RAM、データECC 1ビットエラー */
#define			u2ERRH_NCF99_ID					((U2)99U)		/* Local RAM、ECCオーバーフローエラー */
#define			u2ERRH_NCF100_ID				((U2)100U)		/* 予約 */
#define			u2ERRH_NCF101_ID				((U2)101U)		/* 予約 */
#define			u2ERRH_NCF102_ID				((U2)102U)		/* 予約 */
#define			u2ERRH_NCF103_ID				((U2)103U)		/* 予約 */
#define			u2ERRH_NCF104_ID				((U2)104U)		/* クラスタRAM、アドレスフィードバックコンペアエラー、データECC 2ビットエラー */
#define			u2ERRH_NCF105_ID				((U2)105U)		/* クラスタRAM、データECC 1ビットエラー */
#define			u2ERRH_NCF106_ID				((U2)106U)		/* クラスタRAM、ECCオーバーフローエラー */
#define			u2ERRH_NCF107_ID				((U2)107U)		/* 予約 */
#define			u2ERRH_NCF108_ID				((U2)108U)		/* 予約 */
#define			u2ERRH_NCF109_ID				((U2)109U)		/* 予約 */
#define			u2ERRH_NCF110_ID				((U2)110U)		/* 予約 */
#define			u2ERRH_NCF111_ID				((U2)111U)		/* 予約 */
#define			u2ERRH_NCF112_ID				((U2)112U)		/* DTSRAM、アドレスフィードバックコンペアエラー、データECC 2ビットエラー */
#define			u2ERRH_NCF113_ID				((U2)113U)		/* DTSRAM、データECC 1ビットエラー */
#define			u2ERRH_NCF114_ID				((U2)114U)		/* DTSRAM、ECCオーバーフローエラー */
#define			u2ERRH_NCF115_ID				((U2)115U)		/* 予約 */
#define			u2ERRH_NCF116_ID				((U2)116U)		/* 予約 */
#define			u2ERRH_NCF117_ID				((U2)117U)		/* 予約 */
#define			u2ERRH_NCF118_ID				((U2)118U)		/* 予約 */
#define			u2ERRH_NCF119_ID				((U2)119U)		/* 予約 */
#define			u2ERRH_NCF120_ID				((U2)120U)		/* sDMAC0 RAM ECC 2ビットエラー */
#define			u2ERRH_NCF121_ID				((U2)121U)		/* sDMAC0 RAM ECC 1ビットエラー */
#define			u2ERRH_NCF122_ID				((U2)122U)		/* sDMAC1 RAM ECC 2ビットエラー */
#define			u2ERRH_NCF123_ID				((U2)123U)		/* sDMAC1 RAM ECC 1ビットエラー */
#define			u2ERRH_NCF124_ID				((U2)124U)		/* 予約 */
#define			u2ERRH_NCF125_ID				((U2)125U)		/* 予約 */
#define			u2ERRH_NCF126_ID				((U2)126U)		/* 予約 */
#define			u2ERRH_NCF127_ID				((U2)127U)		/* 予約 */
#define			u2ERRH_NCF128_ID				((U2)128U)		/* 周辺(FlexRay RAM) ECC 2ビットエラー */
#define			u2ERRH_NCF129_ID				((U2)129U)		/* 周辺(FlexRay RAM) ECC 1ビットエラー */
#define			u2ERRH_NCF130_ID				((U2)130U)		/* 周辺(RS-CANFD) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF131_ID				((U2)131U)		/* 周辺(RS-CANFD) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF132_ID				((U2)132U)		/* 周辺(MSPI) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF133_ID				((U2)133U)		/* 周辺(MSPI) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF134_ID				((U2)134U)		/* 周辺(GTM) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF135_ID				((U2)135U)		/* 周辺(GTM) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF136_ID				((U2)136U)		/* 周辺(ファーストイーサネット) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF137_ID				((U2)137U)		/* 周辺(ファーストイーサネット) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF138_ID				((U2)138U)		/* 周辺(ギガビットイーサネット) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF139_ID				((U2)139U)		/* 周辺(ギガビットイーサネット) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF140_ID				((U2)140U)		/* 周辺(MMCA) RAM ECC 2ビットエラー */
#define			u2ERRH_NCF141_ID				((U2)141U)		/* 周辺(MMCA) RAM ECC 1ビットエラー */
#define			u2ERRH_NCF142_ID				((U2)142U)		/* 予約 */
#define			u2ERRH_NCF143_ID				((U2)143U)		/* 予約 */
#define			u2ERRH_NCF144_ID				((U2)144U)		/* 予約 */
#define			u2ERRH_NCF145_ID				((U2)145U)		/* 予約 */
#define			u2ERRH_NCF146_ID				((U2)146U)		/* 予約 */
#define			u2ERRH_NCF147_ID				((U2)147U)		/* 予約 */
#define			u2ERRH_NCF148_ID				((U2)148U)		/* 予約 */
#define			u2ERRH_NCF149_ID				((U2)149U)		/* 予約 */
#define			u2ERRH_NCF150_ID				((U2)150U)		/* 予約 */
#define			u2ERRH_NCF151_ID				((U2)151U)		/* 予約 */
#define			u2ERRH_NCF152_ID				((U2)152U)		/* 予約 */
#define			u2ERRH_NCF153_ID				((U2)153U)		/* 予約 */
#define			u2ERRH_NCF154_ID				((U2)154U)		/* 予約 */
#define			u2ERRH_NCF155_ID				((U2)155U)		/* 予約 */
#define			u2ERRH_NCF156_ID				((U2)156U)		/* 予約 */
#define			u2ERRH_NCF157_ID				((U2)157U)		/* 予約 */
#define			u2ERRH_NCF158_ID				((U2)158U)		/* 予約 */
#define			u2ERRH_NCF159_ID				((U2)159U)		/* 周辺(DTSを除く) RAM エラーアドレスオーバフロー */
#define			u2ERRH_NCF160_ID				((U2)160U)		/* Data transfer path アドレスEDC エラー */
#define			u2ERRH_NCF161_ID				((U2)161U)		/* Data transfer path ECC 2ビットエラー */
#define			u2ERRH_NCF162_ID				((U2)162U)		/* Data transfer path ECC 1ビットエラー */
#define			u2ERRH_NCF163_ID				((U2)163U)		/* 予約 */
#define			u2ERRH_NCF164_ID				((U2)164U)		/* 予約 */
#define			u2ERRH_NCF165_ID				((U2)165U)		/* 予約 */
#define			u2ERRH_NCF166_ID				((U2)166U)		/* 予約 */
#define			u2ERRH_NCF167_ID				((U2)167U)		/* 予約 */
#define			u2ERRH_NCF168_ID				((U2)168U)		/* CRAM ガードエラー */
#define			u2ERRH_NCF169_ID				((U2)169U)		/* I-Bus ガードエラー */
#define			u2ERRH_NCF170_ID				((U2)170U)		/* P-Bus ガードエラー (including INTC2, DTS and sDMAC Guard error) */
#define			u2ERRH_NCF171_ID				((U2)171U)		/* H-Bus ガードエラー */
#define			u2ERRH_NCF172_ID				((U2)172U)		/* 予約 */
#define			u2ERRH_NCF173_ID				((U2)173U)		/* 予約 */
#define			u2ERRH_NCF174_ID				((U2)174U)		/* 予約 */
#define			u2ERRH_NCF175_ID				((U2)175U)		/* 予約 */
#define			u2ERRH_NCF176_ID				((U2)176U)		/* 予約 */
#define			u2ERRH_NCF177_ID				((U2)177U)		/* 予約 */
#define			u2ERRH_NCF178_ID				((U2)178U)		/* 予約 */
#define			u2ERRH_NCF179_ID				((U2)179U)		/* 予約 */
#define			u2ERRH_NCF180_ID				((U2)180U)		/* 予約 */
#define			u2ERRH_NCF181_ID				((U2)181U)		/* 予約 */
#define			u2ERRH_NCF182_ID				((U2)182U)		/* DTS 転送エラー/DMA アドレスエラー */
#define			u2ERRH_NCF183_ID				((U2)183U)		/* H-Bus マスタ転送エラー */
#define			u2ERRH_NCF184_ID				((U2)184U)		/* 外部エラー入力 0 */
#define			u2ERRH_NCF185_ID				((U2)185U)		/* 外部エラー入力 1 */
#define			u2ERRH_NCF186_ID				((U2)186U)		/* 外部エラー入力 2 */
#define			u2ERRH_NCF187_ID				((U2)187U)		/* 外部エラー入力 3 */
#define			u2ERRH_NCF188_ID				((U2)188U)		/* 予約 */
#define			u2ERRH_NCF189_ID				((U2)189U)		/* 予約 */
#define			u2ERRH_NCF190_ID				((U2)190U)		/* 予約 */
#define			u2ERRH_NCF191_ID				((U2)191U)		/* 予約 */
#define			u2ERRH_NCF192_ID				((U2)192U)		/* ソフトウェアアラーム 0 */
#define			u2ERRH_NCF193_ID				((U2)193U)		/* ソフトウェアアラーム 1 */
#define			u2ERRH_NCF194_ID				((U2)194U)		/* ソフトウェアアラーム 2 */
#define			u2ERRH_NCF195_ID				((U2)195U)		/* ソフトウェアアラーム 3 */
#define			u2ERRH_NCF196_ID				((U2)196U)		/* 予約 */
#define			u2ERRH_NCF197_ID				((U2)197U)		/* 予約 */
#define			u2ERRH_NCF198_ID				((U2)198U)		/* 予約 */
#define			u2ERRH_NCF199_ID				((U2)199U)		/* 予約 */
#define			u2ERRH_NCF200_ID				((U2)200U)		/* 予約 */
#define			u2ERRH_NCF201_ID				((U2)201U)		/* 予約 */
#define			u2ERRH_NCF202_ID				((U2)202U)		/* 予約 */
#define			u2ERRH_NCF203_ID				((U2)203U)		/* 予約 */
#define			u2ERRH_NCF204_ID				((U2)204U)		/* 予約 */
#define			u2ERRH_NCF205_ID				((U2)205U)		/* 予約 */
#define			u2ERRH_NCF206_ID				((U2)206U)		/* 予約 */
#define			u2ERRH_NCF207_ID				((U2)207U)		/* 予約 */
#define			u2ERRH_NCF208_ID				((U2)208U)		/* 予約 */
#define			u2ERRH_NCF209_ID				((U2)209U)		/* 予約 */
#define			u2ERRH_NCF210_ID				((U2)210U)		/* 予約 */
#define			u2ERRH_NCF211_ID				((U2)211U)		/* 予約 */
#define			u2ERRH_NCF212_ID				((U2)212U)		/* 予約 */
#define			u2ERRH_NCF213_ID				((U2)213U)		/* 予約 */
#define			u2ERRH_NCF214_ID				((U2)214U)		/* 予約 */
#define			u2ERRH_NCF215_ID				((U2)215U)		/* 予約 */
#define			u2ERRH_NCF216_ID				((U2)216U)		/* 予約 */
#define			u2ERRH_NCF217_ID				((U2)217U)		/* 予約 */
#define			u2ERRH_NCF218_ID				((U2)218U)		/* 予約 */
#define			u2ERRH_NCF219_ID				((U2)219U)		/* 予約 */
#define			u2ERRH_NCF220_ID				((U2)220U)		/* 予約 */
#define			u2ERRH_NCF221_ID				((U2)221U)		/* 予約 */
#define			u2ERRH_NCF222_ID				((U2)222U)		/* 予約 */
#define			u2ERRH_NCF223_ID				((U2)223U)		/* 予約 */
#define			u2ERRH_NCF224_ID				((U2)224U)		/* DCLS コンペアエラー(PE0) */
#define			u2ERRH_NCF225_ID				((U2)225U)		/* 予約 */
#define			u2ERRH_NCF226_ID				((U2)226U)		/* 予約 */
#define			u2ERRH_NCF227_ID				((U2)227U)		/* 意図しないデバッグ許可を検出(PE0) */
#define			u2ERRH_NCF228_ID				((U2)228U)		/* ウォッチドッグタイマエラー(PE0) */
#define			u2ERRH_NCF229_ID				((U2)229U)		/* クロックモニタエラー (CLMA6) (PE0) */
#define			u2ERRH_NCF230_ID				((U2)230U)		/* 予約 */
#define			u2ERRH_NCF231_ID				((U2)231U)		/* 予約 */
#define			u2ERRH_NCF232_ID				((U2)232U)		/* Local RAM (PE0) ECC 2ビットエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF233_ID				((U2)233U)		/* Local RAM (PE0) ECC 1ビットエラー */
#define			u2ERRH_NCF234_ID				((U2)234U)		/* Local RAM (PE0) エラーアドレスオーバフロー */
#define			u2ERRH_NCF235_ID				((U2)235U)		/* 予約 */
#define			u2ERRH_NCF236_ID				((U2)236U)		/* 命令キャッシュRAM(PE0) データEDCエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF237_ID				((U2)237U)		/* 予約 */
#define			u2ERRH_NCF238_ID				((U2)238U)		/* 予約 */
#define			u2ERRH_NCF239_ID				((U2)239U)		/* 予約 */
#define			u2ERRH_NCF240_ID				((U2)240U)		/* PE ガードエラー (PE0) */
#define			u2ERRH_NCF241_ID				((U2)241U)		/* PE ガードエラー (PE0) PE0 から他のLRAM へのリード要求を検出 */
#define			u2ERRH_NCF242_ID				((U2)242U)		/* 予約 */
#define			u2ERRH_NCF243_ID				((U2)243U)		/* 予約 */
#define			u2ERRH_NCF244_ID				((U2)244U)		/* 予約 */
#define			u2ERRH_NCF245_ID				((U2)245U)		/* 予約 */
#define			u2ERRH_NCF246_ID				((U2)246U)		/* 予約 */
#define			u2ERRH_NCF247_ID				((U2)247U)		/* 予約 */
#define			u2ERRH_NCF248_ID				((U2)248U)		/* 予約 */
#define			u2ERRH_NCF249_ID				((U2)249U)		/* 予約 */
#define			u2ERRH_NCF250_ID				((U2)250U)		/* 予約 */
#define			u2ERRH_NCF251_ID				((U2)251U)		/* 予約 */
#define			u2ERRH_NCF252_ID				((U2)252U)		/* 予約 */
#define			u2ERRH_NCF253_ID				((U2)253U)		/* 予約 */
#define			u2ERRH_NCF254_ID				((U2)254U)		/* 予約 */
#define			u2ERRH_NCF255_ID				((U2)255U)		/* データアクセスエラー (PE0) */
#define			u2ERRH_NCF256_ID				((U2)256U)		/* DCLS コンペアエラー (PE1) */
#define			u2ERRH_NCF257_ID				((U2)257U)		/* 予約 */
#define			u2ERRH_NCF258_ID				((U2)258U)		/* 予約 */
#define			u2ERRH_NCF259_ID				((U2)259U)		/* 意図しないデバッグ許可を検出 (PE1) */
#define			u2ERRH_NCF260_ID				((U2)260U)		/* ウォッチドッグタイマエラー (PE1) */
#define			u2ERRH_NCF261_ID				((U2)261U)		/* クロックモニタエラー (CLMA7) (PE1) */
#define			u2ERRH_NCF262_ID				((U2)262U)		/* 予約 */
#define			u2ERRH_NCF263_ID				((U2)263U)		/* 予約 */
#define			u2ERRH_NCF264_ID				((U2)264U)		/* Local RAM (PE1) ECC 2ビットエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF265_ID				((U2)265U)		/* Local RAM (PE1) ECC 1ビットエラー */
#define			u2ERRH_NCF266_ID				((U2)266U)		/* Local RAM (PE1) エラーアドレスオーバフロー */
#define			u2ERRH_NCF267_ID				((U2)267U)		/* 予約 */
#define			u2ERRH_NCF268_ID				((U2)268U)		/* 命令キャッシュRAM(PE1) データEDCエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF269_ID				((U2)269U)		/* 予約 */
#define			u2ERRH_NCF270_ID				((U2)270U)		/* 予約 */
#define			u2ERRH_NCF271_ID				((U2)271U)		/* 予約 */
#define			u2ERRH_NCF272_ID				((U2)272U)		/* PE ガードエラー (PE1) */
#define			u2ERRH_NCF273_ID				((U2)273U)		/* PE ガードエラー (PE1) PE1 から他のLRAM へのリード要求を検出 */
#define			u2ERRH_NCF274_ID				((U2)274U)		/* 予約 */
#define			u2ERRH_NCF275_ID				((U2)275U)		/* 予約 */
#define			u2ERRH_NCF276_ID				((U2)276U)		/* 予約 */
#define			u2ERRH_NCF277_ID				((U2)277U)		/* 予約 */
#define			u2ERRH_NCF278_ID				((U2)278U)		/* 予約 */
#define			u2ERRH_NCF279_ID				((U2)279U)		/* 予約 */
#define			u2ERRH_NCF280_ID				((U2)280U)		/* 予約 */
#define			u2ERRH_NCF281_ID				((U2)281U)		/* 予約 */
#define			u2ERRH_NCF282_ID				((U2)282U)		/* 予約 */
#define			u2ERRH_NCF283_ID				((U2)283U)		/* 予約 */
#define			u2ERRH_NCF284_ID				((U2)284U)		/* 予約 */
#define			u2ERRH_NCF285_ID				((U2)285U)		/* 予約 */
#define			u2ERRH_NCF286_ID				((U2)286U)		/* 予約 */
#define			u2ERRH_NCF287_ID				((U2)287U)		/* データアクセスエラー(PE1) */
#define			u2ERRH_NCF288_ID				((U2)288U)		/* DCLS コンペアエラー (PE2) */
#define			u2ERRH_NCF289_ID				((U2)289U)		/* 予約 */
#define			u2ERRH_NCF290_ID				((U2)290U)		/* 予約 */
#define			u2ERRH_NCF291_ID				((U2)291U)		/* 意図しないデバッグ許可を検出 (PE2) */
#define			u2ERRH_NCF292_ID				((U2)292U)		/* ウォッチドッグタイマエラー (PE2) */
#define			u2ERRH_NCF293_ID				((U2)293U)		/* クロックモニタエラー (CLMA8) (PE2) */
#define			u2ERRH_NCF294_ID				((U2)294U)		/* 予約 */
#define			u2ERRH_NCF295_ID				((U2)295U)		/* 予約 */
#define			u2ERRH_NCF296_ID				((U2)296U)		/* Local RAM (PE2) ECC 2ビットエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF297_ID				((U2)297U)		/* Local RAM (PE2) ECC 1ビットエラー */
#define			u2ERRH_NCF298_ID				((U2)298U)		/* Local RAM (PE2) エラーアドレスオーバフロー */
#define			u2ERRH_NCF299_ID				((U2)299U)		/* 予約 */
#define			u2ERRH_NCF300_ID				((U2)300U)		/* 命令キャッシュRAM(PE2) ECC 2ビットエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF301_ID				((U2)301U)		/* 予約 */
#define			u2ERRH_NCF302_ID				((U2)302U)		/* 予約 */
#define			u2ERRH_NCF303_ID				((U2)303U)		/* 予約 */
#define			u2ERRH_NCF304_ID				((U2)304U)		/* PE ガードエラー (PE2) */
#define			u2ERRH_NCF305_ID				((U2)305U)		/* PE ガードエラー (PE2) PE2 から他のLRAM へのリード要求を検出 */
#define			u2ERRH_NCF306_ID				((U2)306U)		/* 予約 */
#define			u2ERRH_NCF307_ID				((U2)307U)		/* 予約 */
#define			u2ERRH_NCF308_ID				((U2)308U)		/* 予約 */
#define			u2ERRH_NCF309_ID				((U2)309U)		/* 予約 */
#define			u2ERRH_NCF310_ID				((U2)310U)		/* 予約 */
#define			u2ERRH_NCF311_ID				((U2)311U)		/* 予約 */
#define			u2ERRH_NCF312_ID				((U2)312U)		/* 予約 */
#define			u2ERRH_NCF313_ID				((U2)313U)		/* 予約 */
#define			u2ERRH_NCF314_ID				((U2)314U)		/* 予約 */
#define			u2ERRH_NCF315_ID				((U2)315U)		/* 予約 */
#define			u2ERRH_NCF316_ID				((U2)316U)		/* 予約 */
#define			u2ERRH_NCF317_ID				((U2)317U)		/* 予約 */
#define			u2ERRH_NCF318_ID				((U2)318U)		/* 予約 */
#define			u2ERRH_NCF319_ID				((U2)319U)		/* データアクセスエラー (PE2) */
#define			u2ERRH_NCF320_ID				((U2)320U)		/* DCLS コンペアエラー (PE3) */
#define			u2ERRH_NCF321_ID				((U2)321U)		/* 予約 */
#define			u2ERRH_NCF322_ID				((U2)322U)		/* 予約 */
#define			u2ERRH_NCF323_ID				((U2)323U)		/* 意図しないデバッグ許可を検出 (PE3) */
#define			u2ERRH_NCF324_ID				((U2)324U)		/* ウォッチドッグタイマエラー　(PE3) */
#define			u2ERRH_NCF325_ID				((U2)325U)		/* クロックモニタエラー (CLMA9) (PE3) */
#define			u2ERRH_NCF326_ID				((U2)326U)		/* 予約 */
#define			u2ERRH_NCF327_ID				((U2)327U)		/* 予約 */
#define			u2ERRH_NCF328_ID				((U2)328U)		/* Local RAM (PE3) ECC 2ビットエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF329_ID				((U2)329U)		/* Local RAM (PE3) ECC 1ビットエラー */
#define			u2ERRH_NCF330_ID				((U2)330U)		/* Local RAM (PE3) エラーアドレスオーバフロー */
#define			u2ERRH_NCF331_ID				((U2)331U)		/* 予約 */
#define			u2ERRH_NCF332_ID				((U2)332U)		/* 命令キャッシュRAM (PE3) データEDCエラー, アドレスフィードバックコンペアエラー */
#define			u2ERRH_NCF333_ID				((U2)333U)		/* 予約 */
#define			u2ERRH_NCF334_ID				((U2)334U)		/* 予約 */
#define			u2ERRH_NCF335_ID				((U2)335U)		/* 予約 */
#define			u2ERRH_NCF336_ID				((U2)336U)		/* PEガードエラー (PE3) */
#define			u2ERRH_NCF337_ID				((U2)337U)		/* PE ガードエラー (PE3) PE3 から他のLRAM へのリード要求を検出 */
#define			u2ERRH_NCF338_ID				((U2)338U)		/* 予約 */
#define			u2ERRH_NCF339_ID				((U2)339U)		/* 予約 */
#define			u2ERRH_NCF340_ID				((U2)340U)		/* 予約 */
#define			u2ERRH_NCF341_ID				((U2)341U)		/* 予約 */
#define			u2ERRH_NCF342_ID				((U2)342U)		/* 予約 */
#define			u2ERRH_NCF343_ID				((U2)343U)		/* 予約 */
#define			u2ERRH_NCF344_ID				((U2)344U)		/* 予約 */
#define			u2ERRH_NCF345_ID				((U2)345U)		/* 予約 */
#define			u2ERRH_NCF346_ID				((U2)346U)		/* 予約 */
#define			u2ERRH_NCF347_ID				((U2)347U)		/* 予約 */
#define			u2ERRH_NCF348_ID				((U2)348U)		/* 予約 */
#define			u2ERRH_NCF349_ID				((U2)349U)		/* 予約 */
#define			u2ERRH_NCF350_ID				((U2)350U)		/* 予約 */
#define			u2ERRH_NCF351_ID				((U2)351U)		/* データアクセスエラー (PE3) */

#define			ERRH_ERROR_ADDRESS_NORMAL		(0xFFFFFFFFU)	/* エラーアドレス初期値						 */
#define			ERRH_ERROR_ID_NORMAL			(0xFFFFU)		/* エラーID初期値=正常						 */
																/* ※エラーIDは最大351までのため問題なし	 */

/*----------------------------------------------------------------------------------------------*/
/* Slave Guard Configuration																	*/
/*----------------------------------------------------------------------------------------------*/
/* PEG,CRG,IBG,PBG,INTC2G,DTSG,DMACG Configuration Parameter */
/* Slave Guard Module Number */
// zantei MPUは2月末非対応
// #define		ERRH_SLG_PEGCAPM				(0)						/* PEGCAP_M_PEnCL0, PEGCAP_M_PEnCL1 */
// #define		ERRH_SLG_PEGCAPS				(1)						/* PEGCAP_S_PEnCL0, PEGCAP_S_PEnCL1 */
// #define		ERRH_SLG_CRGPE0CL0				(100)					/* CRGCAP_PE0CL0 */
// #define		ERRH_SLG_CRGPE1CL0				(101)					/* CRGCAP_PE1CL0 */
// #define		ERRH_SLG_CRGPE2CL1				(102)					/* CRGCAP_PE2CL1 */
// #define		ERRH_SLG_CRGCRAMHCL0			(103)					/* CRGCAP_CRAMHCL0 */
// #define		ERRH_SLG_CRGCRAMHCL1			(104)					/* CRGCAP_CRAMHCL1 */
// #define		ERRH_SLG_CRGCRAMLCL0			(105)					/* CRGCAP_CRAMLCL0 */
// #define		ERRH_SLG_CRGCRAMLCL1			(106)					/* CRGCAP_CRAMLCL1 */
// #define		ERRH_SLG_CRGSX2MBHCL0			(107)					/* CRGCAP_SX2MBHCL0 */
// #define		ERRH_SLG_CRGSX2MBHCL1			(108)					/* CRGCAP_SX2MBHCL1 */
// #define		ERRH_SLG_CRGSX2MBLCL0			(109)					/* CRGCAP_SX2MBLCL0 */
// #define		ERRH_SLG_CRGSX2MBLCL1			(110)					/* CRGCAP_SX2MBLCL1 */
// #define		ERRH_SLG_PBGPBG00				(300U)					/* PBG00 */
// #define		ERRH_SLG_PBGPBG01				(301U)					/* PBG01 */
// #define		ERRH_SLG_PBGPBG10				(302U)					/* PBG10 */
// #define		ERRH_SLG_PBGPBG20				(303U)					/* PBG20 */
// #define		ERRH_SLG_PBGPBG21				(304U)					/* PBG21 */
// #define		ERRH_SLG_PBGPBG22				(305U)					/* PBG22 */
// #define		ERRH_SLG_PBGPBG23				(306U)					/* PBG23 */
// #define		ERRH_SLG_PBGPBG24				(307U)					/* PBG24 */
// #define		ERRH_SLG_PBGPBG30				(308U)					/* PBG30 */
// #define		ERRH_SLG_PBGPBG31				(309U)					/* PBG31 */
// #define		ERRH_SLG_PBGPBG32				(310U)					/* PBG32 */
// #define		ERRH_SLG_PBGPBG40				(311U)					/* PBG40 */
// #define		ERRH_SLG_PBGPBG41				(312U)					/* PBG41 */
// #define		ERRH_SLG_PBGPBG50				(313U)					/* PBG50 */
// #define		ERRH_SLG_PBGPBG51				(314U)					/* PBG51 */
// #define		ERRH_SLG_PBGPBG60				(315U)					/* PBG60 */
// #define		ERRH_SLG_PBGPBG61				(316U)					/* PBG61 */
// #define		ERRH_SLG_PBGPBG62				(317U)					/* PBG62 */
// #define		ERRH_SLG_PBGPBG70				(318U)					/* PBG70 */
// #define		ERRH_SLG_PBGPBG71				(319U)					/* PBG71 */
// #define		ERRH_SLG_PBGPBG8H0				(320U)					/* PBG8H0 */
// #define		ERRH_SLG_PBGPBG8L0				(321U)					/* PBG8L0 */
// #define		ERRH_SLG_PBGPBG90				(322U)					/* PBG90 */
// #define		ERRH_SLG_PBGPBG92				(323U)					/* PBG92 */
// #define		ERRH_SLG_PBGPBG100				(324U)					/* PBG100 */
// #define		ERRH_SLG_PBGPBG11H0				(325U)					/* PBG11H0 */
// #define		ERRH_SLG_PBGPBG11H1				(326U)					/* PBG11H1 */
// #define		ERRH_SLG_PBGPBG11L0				(327U)					/* PBG11L0 */
// 
// #define		ERRH_SLG_BUSMASTER_SDMAC1		(0U)					/* BUS MASTER sDMAC1 */
// #define		ERRH_SLG_BUSMASTER_SDMAC0		(1U)					/* BUS MASTER sDMAC0 */
// #define		ERRH_SLG_BUSMASTER_DTS			(2U)					/* BUS MASTER DTS */

/*----------------------------------------------------------------------------------------------*/
/* ECC Configuration																			*/
/*----------------------------------------------------------------------------------------------*/
/* ECC ModuleNo for All Function */
// zantei ECCは2月末非対応
// #define		u1ERRH_ECC_CF					((U1)0U)				/* CF					*/
// #define		u1ERRH_ECC_DF					((U1)1U)				/* DF					*/
// #define		u1ERRH_ECC_LRAM_LRPE0			((U1)2U)				/* LRAM_LRPE0			*/
// #define		u1ERRH_ECC_LRAM_LRPE1			((U1)3U)				/* LRAM_LRPE1			*/
// #define		u1ERRH_ECC_LRAM_LRPE2			((U1)4U)				/* LRAM_LRPE2			*/
// #define		u1ERRH_ECC_LRAM_LRPE3			((U1)5U)				/* LRAM_LRPE3			*/
// #define		u1ERRH_ECC_LRAM_LRA				((U1)6U)				/* LRAM_LRA				*/
// #define		u1ERRH_ECC_CRAM_CRAM			((U1)7U)				/* CRAM_CRAM			*/
// #define		u1ERRH_ECC_IC_ITPE0				((U1)8U)				/* IC_ITPE0				*/
// #define		u1ERRH_ECC_IC_ITPE1				((U1)9U)				/* IC_ITPE1				*/
// #define		u1ERRH_ECC_IC_ITPE2				((U1)10U)				/* IC_ITPE2				*/
// #define		u1ERRH_ECC_IC_ITPE3				((U1)11U)				/* IC_ITPE3				*/
// #define		u1ERRH_ECC_IC_IDPE0				((U1)12U)				/* IC_IDPE0				*/
// #define		u1ERRH_ECC_IC_IDPE1				((U1)13U)				/* IC_IDPE1				*/
// #define		u1ERRH_ECC_IC_IDPE2				((U1)14U)				/* IC_IDPE2				*/
// #define		u1ERRH_ECC_IC_IDPE3				((U1)15U)				/* IC_IDPE3				*/
// #define		u1ERRH_ECC_DTS					((U1)16U)				/* DTS					*/
// #define		u1ERRH_ECC_DMDE_DMDE0			((U1)17U)				/* DMDE_DMDE0			*/
// #define		u1ERRH_ECC_DMDE_DMDE1			((U1)18U)				/* DMDE_DMDE1			*/
// #define		u1ERRH_ECC_DMDA_DMDA0			((U1)19U)				/* DMDA_DMDA0			*/
// #define		u1ERRH_ECC_DMDA_DMDA1			((U1)20U)				/* DMDA_DMDA1			*/
// #define		u1ERRH_ECC_PR32_E7RC01			((U1)21U)				/* PR32_E7RC01			*/
// #define		u1ERRH_ECC_PR32_E7RC02			((U1)22U)				/* PR32_E7RC02			*/
// #define		u1ERRH_ECC_PR32_E7RC03			((U1)23U)				/* PR32_E7RC03			*/
// #define		u1ERRH_ECC_PR32_E7RC04			((U1)24U)				/* PR32_E7RC04			*/
// #define		u1ERRH_ECC_PR32_E7FR00			((U1)25U)				/* PR32_E7FR00			*/
// #define		u1ERRH_ECC_PR32_E7FR01			((U1)26U)				/* PR32_E7FR01			*/
// #define		u1ERRH_ECC_PR32_E7FR02			((U1)27U)				/* PR32_E7FR02			*/
// #define		u1ERRH_ECC_PR32_E7GT00			((U1)28U)				/* PR32_E7GT00			*/
// #define		u1ERRH_ECC_PR32_E7GT01			((U1)29U)				/* PR32_E7GT01			*/
// #define		u1ERRH_ECC_PR32_E7GT10			((U1)30U)				/* PR32_E7GT10			*/
// #define		u1ERRH_ECC_PR32_E7GT11			((U1)31U)				/* PR32_E7GT11			*/
// #define		u1ERRH_ECC_PR32_E7GT20			((U1)32U)				/* PR32_E7GT20			*/
// #define		u1ERRH_ECC_PR32_E7GT21			((U1)33U)				/* PR32_E7GT21			*/
// #define		u1ERRH_ECC_PR32_E7GT30			((U1)34U)				/* PR32_E7GT30			*/
// #define		u1ERRH_ECC_PR32_E7GT31			((U1)35U)				/* PR32_E7GT31			*/
// #define		u1ERRH_ECC_PR32_E7GT40			((U1)36U)				/* PR32_E7GT40			*/
// #define		u1ERRH_ECC_PR32_E7GT41			((U1)37U)				/* PR32_E7GT41			*/
// #define		u1ERRH_ECC_PR32_E7GT50			((U1)38U)				/* PR32_E7GT50			*/
// #define		u1ERRH_ECC_PR32_E7GT51			((U1)39U)				/* PR32_E7GT51			*/
// #define		u1ERRH_ECC_PR32_E7GT60			((U1)40U)				/* PR32_E7GT60			*/
// #define		u1ERRH_ECC_PR32_E7GT61			((U1)41U)				/* PR32_E7GT61			*/
// #define		u1ERRH_ECC_PR32_E7GT100			((U1)42U)				/* PR32_E7GT100			*/
// #define		u1ERRH_ECC_PR32_E7GT101			((U1)43U)				/* PR32_E7GT101			*/
// #define		u1ERRH_ECC_PR32_E7GT102			((U1)44U)				/* PR32_E7GT102			*/
// #define		u1ERRH_ECC_PR32_E7GT110			((U1)45U)				/* PR32_E7GT110			*/
// #define		u1ERRH_ECC_PR32_E7GT111			((U1)46U)				/* PR32_E7GT111			*/
// #define		u1ERRH_ECC_PR32_E7GT112			((U1)47U)				/* PR32_E7GT112			*/
// #define		u1ERRH_ECC_PR32_E7MS00			((U1)48U)				/* PR32_E7MS00			*/
// #define		u1ERRH_ECC_PR32_E7MS01			((U1)49U)				/* PR32_E7MS01			*/
// #define		u1ERRH_ECC_PR32_E7MS02			((U1)50U)				/* PR32_E7MS02			*/
// #define		u1ERRH_ECC_PR32_E7MS03			((U1)51U)				/* PR32_E7MS03			*/
// #define		u1ERRH_ECC_PR32_E7MS04			((U1)52U)				/* PR32_E7MS04			*/
// #define		u1ERRH_ECC_PR32_E7MS05			((U1)53U)				/* PR32_E7MS05			*/
// #define		u1ERRH_ECC_PR32_E7MS06			((U1)54U)				/* PR32_E7MS06			*/
// #define		u1ERRH_ECC_PR32_E7MS07			((U1)55U)				/* PR32_E7MS07			*/
// #define		u1ERRH_ECC_PR32_E7MS08			((U1)56U)				/* PR32_E7MS08			*/
// #define		u1ERRH_ECC_PR32_E7MS09			((U1)57U)				/* PR32_E7MS09			*/
// #define		u1ERRH_ECC_PR32_E7MM00			((U1)58U)				/* PR32_E7MM00			*/
// #define		u1ERRH_ECC_PR32_E7MM01			((U1)59U)				/* PR32_E7MM01			*/
// #define		u1ERRH_ECC_PR32_E7ES00			((U1)60U)				/* PR32_E7ES00			*/
// #define		u1ERRH_ECC_PR32_E7ES01			((U1)61U)				/* PR32_E7ES01			*/
// #define		u1ERRH_ECC_PR32_E7ES02			((U1)62U)				/* PR32_E7ES02			*/
// #define		u1ERRH_ECC_PR32_E7ES03			((U1)63U)				/* PR32_E7ES03			*/
// #define		u1ERRH_ECC_PR32_E7ES04			((U1)64U)				/* PR32_E7ES04			*/
// #define		u1ERRH_ECC_PR32_E7ES05			((U1)65U)				/* PR32_E7ES05			*/
// #define		u1ERRH_ECC_PR32_E7DF00			((U1)66U)				/* PR32_E7DF00			*/
// #define		u1ERRH_ECC_PR32_E7DF10			((U1)67U)				/* PR32_E7DF10			*/
// #define		u1ERRH_ECC_PR16_E6DF00			((U1)68U)				/* PR16_E6DF00			*/
// #define		u1ERRH_ECC_PR16_E6DF01			((U1)69U)				/* PR16_E6DF01			*/
// #define		u1ERRH_ECC_PR16_E6DF10			((U1)70U)				/* PR16_E6DF10			*/
// #define		u1ERRH_ECC_PR16_E6DF11			((U1)71U)				/* PR16_E6DF11			*/
// #define		u1ERRH_ECC_DTP_LRAM_ADDR		((U1)72U)				/* DTP_LRAM_ADDR		*/
// #define		u1ERRH_ECC_DTP_CRAM_ADDR		((U1)73U)				/* DTP_CRAM_ADDR		*/
// #define		u1ERRH_ECC_DTP_CFL_ADDR			((U1)74U)				/* DTP_CFL_ADDR			*/
// #define		u1ERRH_ECC_DTP_PERI_ADDR		((U1)75U)				/* DTP_PERI_ADDR		*/
// #define		u1ERRH_ECC_DTP_EMU_ADDR			((U1)76U)				/* DTP_EMU_ADDR			*/
// #define		u1ERRH_ECC_DTP_HB90MECC_ADDR	((U1)77U)				/* DTP_HB90MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB90SECC_ADDR	((U1)78U)				/* DTP_HB90SECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB92MECC_ADDR	((U1)79U)				/* DTP_HB92MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB92SECC_ADDR	((U1)80U)				/* DTP_HB92SECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB94SECC_ADDR	((U1)81U)				/* DTP_HB94SECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB97MECC_ADDR	((U1)82U)				/* DTP_HB97MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB98MECC_ADDR	((U1)83U)				/* DTP_HB98MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB911MECC_ADDR	((U1)84U)				/* DTP_HB911MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_HB912MECC_ADDR	((U1)85U)				/* DTP_HB912MECC_ADDR	*/
// #define		u1ERRH_ECC_DTP_V2A1_ADDR		((U1)86U)				/* DTP_V2A1_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A2_ADDR		((U1)87U)				/* DTP_V2A2_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A3_ADDR		((U1)88U)				/* DTP_V2A3_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A4_ADDR		((U1)89U)				/* DTP_V2A4_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A5_ADDR		((U1)90U)				/* DTP_V2A5_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A6_ADDR		((U1)91U)				/* DTP_V2A6_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A7_ADDR		((U1)92U)				/* DTP_V2A7_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A8_ADDR		((U1)93U)				/* DTP_V2A8_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A9_ADDR		((U1)94U)				/* DTP_V2A9_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A10_ADDR		((U1)95U)				/* DTP_V2A10_ADDR		*/
// #define		u1ERRH_ECC_DTP_V2A11_ADDR		((U1)96U)				/* DTP_V2A11_ADDR		*/
// #define		u1ERRH_ECC_DTP_DFPFNT_ADDR		((U1)97U)				/* DTP_DFPFNT_ADDR		*/
// #define		u1ERRH_ECC_DTP_LRAM_DATA		((U1)98U)				/* DTP_LRAM_DATA		*/
// #define		u1ERRH_ECC_DTP_CRAM_DATA		((U1)99U)				/* DTP_CRAM_DATA		*/
// #define		u1ERRH_ECC_DTP_PERI_DATA		((U1)100U)				/* DTP_PERI_DATA		*/
// #define		u1ERRH_ECC_DTP_DMDT_DATA		((U1)101U)				/* DTP_DMDT_DATA		*/
// #define		u1ERRH_ECC_DTP_EMU_DATA			((U1)102U)				/* DTP_EMU_DATA			*/
// #define		u1ERRH_ECC_DTP_HB90MECC_DATA	((U1)103U)				/* DTP_HB90MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB90SECC_DATA	((U1)104U)				/* DTP_HB90SECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB92MECC_DATA	((U1)105U)				/* DTP_HB92MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB92SECC_DATA	((U1)106U)				/* DTP_HB92SECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB94SECC_DATA	((U1)107U)				/* DTP_HB94SECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB97MECC_DATA	((U1)108U)				/* DTP_HB97MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB98MECC_DATA	((U1)109U)				/* DTP_HB98MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB911MECC_DATA	((U1)110U)				/* DTP_HB911MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_HB912MECC_DATA	((U1)111U)				/* DTP_HB912MECC_DATA	*/
// #define		u1ERRH_ECC_DTP_V2A1_DATA		((U1)112U)				/* DTP_V2A1_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A2_DATA		((U1)113U)				/* DTP_V2A2_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A3_DATA		((U1)114U)				/* DTP_V2A3_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A4_DATA		((U1)115U)				/* DTP_V2A4_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A5_DATA		((U1)116U)				/* DTP_V2A5_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A6_DATA		((U1)117U)				/* DTP_V2A6_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A7_DATA		((U1)118U)				/* DTP_V2A7_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A8_DATA		((U1)119U)				/* DTP_V2A8_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A9_DATA		((U1)120U)				/* DTP_V2A9_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A10_DATA		((U1)121U)				/* DTP_V2A10_DATA		*/
// #define		u1ERRH_ECC_DTP_V2A11_DATA		((U1)122U)				/* DTP_V2A11_DATA		*/
// #define		u1ERRH_ECC_DTP_DFPROM_DATA		((U1)123U)				/* DTP_DFPROM_DATA		*/
// #define		u1ERRH_ECC_DTP_DFPSYS_DATA		((U1)124U)				/* DTP_DFPSYS_DATA		*/
// #define		u1ERRH_ECC_DTP_DFPFNT_DATA		((U1)125U)				/* CC_DTP_DFPFNT_DATA	*/
// 
// #define		ERRH_ECC_MODULE_NUM				(126)					/* ECC検出モジュール数：モジュールの増減に伴い変更する */
// 
// /* RAM Type for RamC */
// #define		u1ERRH_ECC_RAMTYPE_ALL			((U1)0U)				/* 全LocalRAM, Cluster RAM */
// #define		u1ERRH_ECC_RAMTYPE_LRAM			((U1)1U)				/* 自コアのLocal RAM */
// #define		u1ERRH_ECC_RAMTYPE_CRAM			((U1)2U)				/* Cluster RAM */

/*----------------------------------------------------------------------------------------------*/
/* BIST Configuration																			*/
/*----------------------------------------------------------------------------------------------*/
/* BIST RegNo for Read Function */
#define		u1ERRH_BIST_LBISTREF1			((U1)0U)				/* LBISTREF1 */
#define		u1ERRH_BIST_LBISTREF2			((U1)1U)				/* LBISTREF2 */
#define		u1ERRH_BIST_MBISTREF1			((U1)2U)				/* MBISTREF1 */
#define		u1ERRH_BIST_MBISTREF2			((U1)3U)				/* MBISTREF2 */
#define		u1ERRH_BIST_MBISTREF3			((U1)4U)				/* MBISTREF3 */
#define		u1ERRH_BIST_LBISTSIG1			((U1)5U)				/* LBISTSIG1 */
#define		u1ERRH_BIST_LBISTSIG2			((U1)6U)				/* LBISTSIG2 */
#define		u1ERRH_BIST_MBISTSIG1			((U1)7U)				/* MBISTSIG1 */
#define		u1ERRH_BIST_MBISTSIG2			((U1)8U)				/* MBISTSIG2 */
#define		u1ERRH_BIST_MBISTSIG3			((U1)9U)				/* MBISTSIG3 */
#define		u1ERRH_BIST_MBIST1FTAG0			((U1)10U)				/* MBIST1FTAG0 */
#define		u1ERRH_BIST_MBIST1FTAG1			((U1)11U)				/* MBIST1FTAG1 */
#define		u1ERRH_BIST_MBIST1FTAG2			((U1)12U)				/* MBIST1FTAG2 */
#define		u1ERRH_BIST_MBIST1FTAG3			((U1)13U)				/* MBIST1FTAG3 */
#define		u1ERRH_BIST_MBIST1FTAG4			((U1)14U)				/* MBIST1FTAG4 */
#define		u1ERRH_BIST_MBIST1FTAG5			((U1)15U)				/* MBIST1FTAG5 */
#define		u1ERRH_BIST_MBIST1FTAG6			((U1)16U)				/* MBIST1FTAG6 */
#define		u1ERRH_BIST_MBIST1FTAG7			((U1)17U)				/* MBIST1FTAG7 */
#define		u1ERRH_BIST_MBIST2FTAG0			((U1)18U)				/* MBIST2FTAG0 */
#define		u1ERRH_BIST_MBIST2FTAG1			((U1)19U)				/* MBIST2FTAG1 */
#define		u1ERRH_BIST_MBIST2FTAG2			((U1)20U)				/* MBIST2FTAG2 */
#define		u1ERRH_BIST_MBIST3FTAG0			((U1)21U)				/* MBIST3FTAG0 */
#define		u1ERRH_BIST_MBIST1ECC0			((U1)22U)				/* MBIST1ECC0 */
#define		u1ERRH_BIST_MBIST1ECC1			((U1)23U)				/* MBIST1ECC1 */
#define		u1ERRH_BIST_MBIST1ECC2			((U1)24U)				/* MBIST1ECC2 */
#define		u1ERRH_BIST_MBIST1ECC3			((U1)25U)				/* MBIST1ECC3 */
#define		u1ERRH_BIST_MBIST1ECC4			((U1)26U)				/* MBIST1ECC4 */
#define		u1ERRH_BIST_MBIST1ECC5			((U1)27U)				/* MBIST1ECC5 */
#define		u1ERRH_BIST_MBIST1ECC6			((U1)28U)				/* MBIST1ECC6 */
#define		u1ERRH_BIST_MBIST1ECC7			((U1)29U)				/* MBIST1ECC7 */
#define		u1ERRH_BIST_MBIST2ECC0			((U1)30U)				/* MBIST2ECC0 */
#define		u1ERRH_BIST_MBIST2ECC1			((U1)31U)				/* MBIST2ECC1 */
#define		u1ERRH_BIST_MBIST2ECC2			((U1)32U)				/* MBIST2ECC2 */
#define		u1ERRH_BIST_MBIST3ECC0			((U1)33U)				/* MBIST3ECC0 */
#define		u1ERRH_BIST_BSEQ0ST				((U1)34U)				/* BSEQ0ST */
#define		u1ERRH_BIST_BISTST				((U1)35U)				/* BISTST */
#define		u1ERRH_BIST_BSEQ0SEL			((U1)36U)				/* BSEQ0SEL */
#define		u1ERRH_BIST_BSEQ0CTL			((U1)37U)				/* BSEQ0CTL */

/*----------------------------------------------------------------------------------------------*/
/* レジスタ診断																					*/
/*----------------------------------------------------------------------------------------------*/
#define		u1ERRH_REGCHECK_COMPLETED		((U1)0U)				/* レジスタ診断開始待ち */
#define		u1ERRH_REGCHECK_BUSY			((U1)1U)				/* レジスタ診断中 */

// zantei ECCは2月末非対応	#define		ERRH_ECC_REG_4BYTE_PB5ECC_APEC_PROT	(0U)				/* ECC_REG_4BYTE_PB5ECC_APEC_PROT */
// zantei ECCは2月末非対応	#define		ERRH_ECC_REG_4BYTE_ECC_PROT			(1U)				/* ECC_REG_4BYTE_ECC_PROT */
// zantei REGCHKは2月末非対応 #define		ERRH_ECM_REG_4BYTE_ECM_PROT			(0U)				/* ECM_REG_4BYTE_ECM_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_CRG_CL0_PROT		(0U)				/* SLG_REG_4BYTE_CRG_CL0_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_CRG_CL1_PROT		(1U)				/* SLG_REG_4BYTE_CRG_CL1_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_PBG_PBG50_PROT	(2U)				/* SLG_REG_4BYTE_PBG_PBG50_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_PEG_CORE0_PROT	(3U)				/* SLG_REG_4BYTE_PEG_CORE0_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_PEG_CORE1_PROT	(4U)				/* SLG_REG_4BYTE_PEG_CORE1_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_PEG_CORE2_PROT	(5U)				/* SLG_REG_4BYTE_PEG_CORE2_PROT */
// zantei MPUは2月末非対応	#define		ERRH_SLG_REG_4BYTE_PEG_CORE3_PROT	(6U)				/* SLG_REG_4BYTE_PEG_CORE3_PROT */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* structs / unions																				*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*----------------------------------------------------------------------------------------------*/
/* PEG Configuration																			*/
/*----------------------------------------------------------------------------------------------*/
/* Region User Config Data Type Definition */
typedef	struct
{
	U4		u4AddvData;							/* チャネル有効ビット設定 */
	U4		u4BaseData;							/* チャネルベースアドレス設定 */
	U4		u4ConfigData;						/* チャネル保護制御 */
	U4		u4SpidMapData;						/* チャネル SPID 設定 */
}	ErrH_PegConfigType;

/*----------------------------------------------------------------------------------------------*/
/* CRG Configuration																			*/
/*----------------------------------------------------------------------------------------------*/
/* Region User Config Data Type Definition */
typedef	struct
{
	U4		u4ComBaseData;						/* チャネルベースアドレス設定 */
	U4		u4ComAddrData;						/* チャネル有効ビット設定 */
	U4		u4ProtData;							/* チャネル保護制御 */
	U4		u4SpidMapData;						/* チャネル SPID 設定 */
}	ErrH_CrgConfigType;

/*----------------------------------------------------------------------------------------------*/
/* PBG Configuration																			*/
/*----------------------------------------------------------------------------------------------*/
/* Region User Config Data Type Definition */
typedef	struct
{
	U4		u4ProtData;							/* チャネル保護制御 */
	U4		u4SpidData;							/* チャネル SPID 設定 */
}	ErrH_PbgChDataDefType;						/* CH毎情報 */

typedef	struct
{
	const	ErrH_PbgChDataDefType*	pstChDataConfig;		/* CH毎情報 */
	U1		u1GroupNum;										/* グループNo */
}	ErrH_PbgGpDataDefType;									/* グループ毎情報 */
/* Pbg UserConfigType */
typedef	struct
{
	const	ErrH_PbgGpDataDefType*	pstGpDataConfig;		/* グループ毎情報 */
	U1								u1GroupDataNum;			/* 使用グループ数 */
}	ErrH_PbgConfigType;

/*----------------------------------------------------------------------------------------------*/
/* レジスタ診断																					*/
/*----------------------------------------------------------------------------------------------*/
typedef	struct
{
	volatile	void*				pvdAddress;				/* レジスタアドレス */
				U4					u4ExpectValue;			/* 期待値 */
				U4					u4Mask;					/* マスク値 */
				U1					u1Prot;					/* 保護種 */
} ErrH_RegCheckType;

typedef	struct
{
	const	ErrH_RegCheckType		*pcstRegData;			/* レジスタ診断データ */
	U2								u2RegNum;				/* 診断データ数 */
} ErrH_RegCheckConfigType;

/* User Config Data Type Definition */
typedef	struct
{
	const	U4								*pcu4IrTypeCfg;			/* 割り込みタイプ設定テーブルアドレス */
	const	U4								*pcu4NotifCoreCfg;		/* 通知先コア設定テーブルアドレス */
	const	U4								*pcu4InitInfCfg;		/* ECM初期化時エラー通知テーブルアドレス */
	const	U4								*pcu4IrCfg;				/* ECMIRCFGn設定テーブルアドレス */
	const	U4								*pcu4EoutCfg;			/* ECMEMKn設定テーブルアドレス */
	const	ErrH_PegConfigType				*pcstPegCfg;			/* PEG設定テーブルアドレス */
	const	ErrH_CrgConfigType				*pcstCrgCrgCfg;			/* CRG CRG設定テーブルアドレス */
	const	ErrH_CrgConfigType				*pcstCrgCsgCfg;			/* CRG CSG設定テーブルアドレス */
	const	U4								*pcu4SpidMskCfg;		/* SPIDマスク設定テーブルアドレス */
	const	ErrH_PbgConfigType				*pcstPbgCfg;			/* PBG設定テーブルアドレス */
	const	ErrH_RegCheckConfigType			*pcstEcmRegCheckCfg;	/* ECMレジスタ診断テーブルアドレス */
	const	ErrH_RegCheckConfigType			*pcstEccRegCheckCfg;	/* ECCレジスタ診断テーブルアドレス */
	const	ErrH_RegCheckConfigType			*pcstSlgRegCheckCfg;	/* SLGレジスタ診断テーブルアドレス */
}	ErrH_UserConfigType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#if 0 // zantei MPUは2月末非対応
/************************************************************************************************/
/* Service name		:	Get MIPMDP Error Address												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	none																	*/
/* Return value		:	異常アドレス															*/
/* Caveats			:	本APIはメモリ保護違反通知フックからの実行に限定する。					*/
/************************************************************************************************/
U4		ErrH_GetMipMdpAddress( void );

/************************************************************************************************/
/* Service name		:	SlaveGuard Clear Error													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	ErrorID																	*/
/*					:	ModuleNumber															*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_ClearSlgErr( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	SlaveGuard Get Error Status												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ErrorID																	*/
/*					:	ModuleNumber															*/
/* Return value		:	Error Status															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_GetSlgErrStatus( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	SlaveGuard Get Error Address											*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ErrorID																	*/
/*					:	ModuleNumber															*/
/* Return value		:	Error Address															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_GetSlgErrAddress( U2 t_u2ErrorID, U2 t_u2ModuleNum );

/************************************************************************************************/
/* Service name		:	SlaveGuard Get Error Access info										*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ErrorID																	*/
/*					:	ModuleNumber															*/
/* Return value		:	Error Access info														*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U4	ErrH_GetSlgErrAccessInfo( U2 t_u2ErrorID, U2 t_u2ModuleNum );

#endif // zantei MPUは2月末非対応

#if 0 // zantei ECCは2月末非対応

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Clear													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	none																	*/
/* Caveats			:	・ECCモジュール番号としてデータ転送経路のH-Busのモジュール(モジュール	*/
/*					:	  番号：No.77～85)を指定した場合、同モジュールのデータバス、アドレス	*/
/*					:	  バスのECC2ビット、1ビットエラーをすべてクリアする。(詳細は、RH850/	*/
/*					:	  U2Aマイコン ユーザーズマニュアルのHBECSTCLRレジスタを参照)			*/
/*					:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_ClearEcc1bitErr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Clear													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	none																	*/
/* Caveats			:	・ECCモジュール番号としてデータ転送経路のH-Bus(モジュール番号：No.77～	*/
/*					:	  85、103～111)のモジュールを指定した場合、同モジュールのデータバス、	*/
/*					:	  アドレスバスのECC2ビット、1ビットエラーをすべてクリアする。(詳細は、	*/
/*					:	  RH850/U2Aマイコン ユーザーズマニュアルのHBECSTCLRレジスタを参照)		*/
/*					:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_ClearEccFatalErr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Status Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorStatus																*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_GetEcc1bitErrStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Status Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorStatus																*/
/* Caveats			:	・定常処理中は、本APIはECMアラーム割り込みからの実行に限定する。		*/
/*					:	・定常処理中は、ECMアラーム割り込みにて通知した異常IDを本APIの引数		*/
/*					:	  として指定すること。													*/
/************************************************************************************************/
U1		ErrH_GetEccFatalErrStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC Overflow Status Get													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	OverflowStatus															*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_GetEccOvfStatus( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Address Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, Address(Sync), ArrayNum									*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_GetEcc1bitErrAddr( U1 t_u1ModuleNum, U4* t_pu4Address, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Address Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorAddress															*/
/* Caveats			:	・定常処理中は、本APIはECMアラーム割り込みからの実行に限定する。		*/
/*					:	・定常処理中は、ECMアラーム割り込みにて通知した異常IDを本APIの引数		*/
/*					:	  として指定すること。													*/
/************************************************************************************************/
U4		ErrH_GetEccFatalErrAddr( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error Detailed Information Get									*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, DetailInformation(Sync), ArrayNum							*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
void	ErrH_GetEcc1bitErrDetail ( U1 t_u1ModuleNum, U1* t_pu1DetailInfo, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error Detailed Information Get								*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorDetailInformation													*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/************************************************************************************************/
U1		ErrH_GetEccFatalErrDetail ( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC 1bit Error SPID Get													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber, ErrorSpid(Sync), ArrayNum									*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/*					:	・ECC1ビットエラー発生時、ECC1ビットエラークリア処理を行うまでに新たな	*/
/*					:	  ECC1ビットエラーが発生した場合は、最初に発生したECC1ビットエラー、	*/
/*					:	  および新たなECC1ビットエラーのSPID情報を全て提供する。				*/
/************************************************************************************************/
void	ErrH_GetEcc1bitErrSpid( U1 t_u1ModuleNum, U4* t_pu4ErrSpid, U1 t_u1ArrayNum );

/************************************************************************************************/
/* Service name		:	ECC Fatal Error SPID Get												*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	ModuleNumber															*/
/* Return value		:	ErrorSPID																*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・ECMアラーム割り込みにて通知した異常IDを本APIの引数として指定すること。*/
/*					:	・ECC2ビットエラー、アドレスパリティエラー、またはアドレスフィード		*/
/*					:	  バックエラー(以降、ECCfatalエラーと記載する)発生時、ECCfatalエラー	*/
/*					:	  クリア処理を行うまでに新たなECCfatalエラーが発生した場合は、最初に	*/
/*					:	  発生したECCfatalエラー、および新たなECCfatalエラーのSPID情報を全て	*/
/*					:	  提供する。															*/
/************************************************************************************************/
U4		ErrH_GetEccFatalErrSpid( U1 t_u1ModuleNum );

/************************************************************************************************/
/* Service name		:	ECC/EDC Stop															*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Caveats			:	・本APIはECMアラーム割り込みからの実行に限定する。						*/
/*					:	・本APIはコア0からのコールに限定する。									*/
/************************************************************************************************/
void	ErrH_StopEccEdc( void );
#endif // zantei ECCは2月末非対応

/************************************************************************************************/
/* Service name		:	BIST Register Value Get													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	Register No																*/
/* Return value		:	Register Value															*/
/* Caveats			:	none																	*/
/************************************************************************************************/
U4	ErrH_GetBistRegValue( U1 t_u1RegNo );

#if 0 // zantei ECCは2月末非対応

/************************************************************************************************/
/* Service name		:	Clear ECC Error Status													*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	RAM Type																*/
/* Return value		:	none																	*/
/* Caveats			:	本APIはRamCの使用に限定する。											*/
/************************************************************************************************/
void	ErrH_ClearEccErrorStatus( U1 t_u1RamType );

/************************************************************************************************/
/* Service name		:   Get ECC Error Status													*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	RAM Type																*/
/* Return value		:	Error Detect Status(=0:not error detect, !=0:error detect)				*/
/* Caveats			:	none																	*/
/************************************************************************************************/
ZORN	ErrH_GetEccErrorStatus( U1 t_u1RamType );

/************************************************************************************************/
/* Service name		:	Clear ROM Ecc Ecm Error Status											*/
/* Reentrancy		:	Re-entrant																*/
/* Parameters(in)	:	none																	*/
/* Return value		:	none																	*/
/* Caveats			:	・Init時のみ使用可能。定常処理中は使用しないこと。						*/
/*					:	・本APIはASIL権限にて使用すること。										*/
/************************************************************************************************/
void	ErrH_ClearRomEccEcmErrorStatus( void );

#endif // zantei ECCは2月末非対応

#if 0 // zantei REGCHKは2月末非対応

/************************************************************************************************/
/* Service name		:	Request Register Diag Function											*/
/* Reentrancy		:	Non Re-entrant															*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Register Diag Result													*/
/* Caveats			:	・本APIはコア0からのコールに限定する。									*/
/*					:	・ErrH_StopEccEdc()コール後、本APIをコールしないこと。					*/
/************************************************************************************************/
U1	ErrH_CheckReg_ASIL( void );

/************************************************************************************************/
/* Service name		:	Get Register Diag Status Function										*/
/* Reentrancy		:	Concurrency Safe														*/
/* Parameters(in)	:	none																	*/
/* Return value		:	Register Diag Status													*/
/* Caveats			:	本APIはコア0からのコールに限定する。									*/
/************************************************************************************************/
U1	ErrH_GetRegStatus_ASIL( void );
#endif // zantei REGCHKは2月末非対応

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Function			:	Initialization in Boot													*/
/* Schedule			:	Boot																	*/
/* Parameters(in)	:	CoreId																	*/
/************************************************************************************************/
void	ErrH_InitBoot( U4 t_u4CoreId );

/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	EcuM_AL_DriverInitZero_Core0, EcuM_AL_DriverInitZero_Core1				*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_Init_0( void );

/************************************************************************************************/
/* Function			:	Initialization															*/
/* Schedule			:	EcuM_AL_DriverInitOne_Core0, EcuM_AL_DriverInitOne_Core1				*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_Init_1( void );

/************************************************************************************************/
/* Function			:	Alarm Interrupt															*/
/* Schedule			:	INTHDL_INTECMMI_COREx、INTHDL_INTECMDCLSMI_COREx						*/
/* Parameters(in)	:	none																	*/
/************************************************************************************************/
void	ErrH_AlarmInterrupt( void );

/************************************************************************************************/
/* Function			:	Protection Hook															*/
/* Schedule			:	INTHDL_MIPMDP															*/
/* Parameters(in)	:	ErrId  - Numeric identifier of the Error 								*/
/*					:	ErrPc  - Error Program Counter											*/
/*					:	ErrAdr - Error Address													*/
/************************************************************************************************/
void	ErrH_ProtectionHook( U4 t_u4ErrId, U4 t_u4ErrPc, U4 t_u4ErrAdr );


/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
extern	const	ErrH_UserConfigType		cstErrH_UcfgData;			/* user config data */

#endif	/* ERRH_H  */
/*-- End Of File -------------------------------------------------------------------------------*/
