/* Std_Types-r04-3000-0000-a-v03 */
/************************************************************************************************/
/*																								*/
/*		標準定義 ヘッダファイル																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef PF_TYPES_H
#define PF_TYPES_H

/*==============================================================================================*/
/*		汎用データ名定義																		*/
/*==============================================================================================*/
#ifndef HI	/* common.hで定義済であり、2重定義防止のため */
#define		HI						(1U)
#endif
#ifndef LO	/* common.hで定義済であり、2重定義防止のため */
#define		LO						(0U)
#endif

#ifndef ON	/* common.hで定義済であり、2重定義防止のため */
#define		ON						(HI)
#endif
#ifndef OFF	/* common.hで定義済であり、2重定義防止のため */
#define		OFF						(LO)
#endif

#ifndef OK	/* common.hで定義済であり、2重定義防止のため */
#define		OK						(0U)
#endif
#define		NG						(1U)
//#define		ERR						(1U)
#define		ERR_HI					(1U)
#define		ERR_LO					(2U)
#define		UNFIX					(3U)

/* #define		TRUE				((BOOL)0x01) */ /* AUBISTのPlatform_Types.hとの2重定義対応 */
/* #define		FALSE				((BOOL)0x00) */ /* AUBISTのPlatform_Types.hとの2重定義対応 */

/* #define		E_OK				(0) */ /* AUBISTのStd_Types.hとの2重定義対応 */
/* #define		E_NOT_OK			(1) */ /* AUBISTのStd_Types.hとの2重定義対応 */

#define		ADC_LSB					((PL)(5./65536.))		/* A/D値 LSB [v] */

#define		NULL_POINTER			((void*)0)

#define		BIT0					(0x00000001U)
#define		BIT1					(0x00000002U)
#define		BIT2					(0x00000004U)
#define		BIT3					(0x00000008U)
#define		BIT4					(0x00000010U)
#define		BIT5					(0x00000020U)
#define		BIT6					(0x00000040U)
#define		BIT7					(0x00000080U)
#define		BIT8					(0x00000100U)
#define		BIT9					(0x00000200U)
#define		BIT10					(0x00000400U)
#define		BIT11					(0x00000800U)
#define		BIT12					(0x00001000U)
#define		BIT13					(0x00002000U)
#define		BIT14					(0x00004000U)
#define		BIT15					(0x00008000U)
#define		BIT16					(0x00010000U)
#define		BIT17					(0x00020000U)
#define		BIT18					(0x00040000U)
#define		BIT19					(0x00080000U)
#define		BIT20					(0x00100000U)
#define		BIT21					(0x00200000U)
#define		BIT22					(0x00400000U)
#define		BIT23					(0x00800000U)
#define		BIT24					(0x01000000U)
#define		BIT25					(0x02000000U)
#define		BIT26					(0x04000000U)
#define		BIT27					(0x08000000U)
#define		BIT28					(0x10000000U)
#define		BIT29					(0x20000000U)
#define		BIT30					(0x40000000U)
#define		BIT31					(0x80000000U)

#endif // PF_TYPES_H
