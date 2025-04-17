/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/


#if 0 // zantei MPUは2月末非対応

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"ErrH_cfg.h"
#include	"ErrH_mcu_def.h"
#include	"ErrH.h"
#include	"ErrH_slg.h"

#include	"ErrH_pbg.h"

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		u2ERRH_PBG_MODULEMASK					((U2)ERRH_SLG_PBGPBG00)	/* マスクデータ(SLGモジュール番号、PBGの先頭値) */
#define		u4ERRH_PBG_REGPROTMASK					((U4)0x00000153U)	/* PROT用マスク */

#define		u4ERRH_PBG_PBGSPIDERRCLR_ALLBIT_CLR		((U4)0xFFFFFFFFU)	/* PBGSPIDERRCLRレジスタ、全ビットクリア値 */
#define		u4ERRH_PBG_PBGSPIDERRSTAT_NOERR			((U4)0x00000000U)	/* PBGSPIDERRSTAT、エラーなし */
#define		u4ERRH_PBG_ERRSTAT_SPIDERR				((U4)0x00000001U)	/* SPIDエラー発生 */
#define		u4ERRH_PBG_NOERR						((U4)0x00000000U)	/* エラーなし */
#define		u4ERRH_PBG_INVALID_ADDR					((U4)0x00000000U)	/* エラーアドレス無効値 */
#define		u4ERRH_PBG_INVALID_INFO					((U4)0x00000000U)	/* エラーアクセス情報無効値 */
#define		u1ERRH_PBG_PBGERRSLV_NUM				((U1)15U)			/* PBGERRSLVモジュール数 */
#if ( MCU_TYPE_SERIES == MCU_RH850U2B6 )
#define		u2ERRH_PBG_PBGPROTSETCH_NUM				((U2)312U)			/* PBG保護設定チャネル数 */
#elif ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
#define		u2ERRH_PBG_PBGPROTSETCH_NUM				((U2)327U)			/* PBG保護設定チャネル数 */
#else
	#error "MCU_TYPE_SERIES is not supported"
#endif
#define		u4ERRH_PBG_NO_GUARD						((U4)0x00000000U)	/* PBG保護無効 */

/* ErrH Pbg Protection Setting Channel Type */
typedef	struct
{
	volatile	Reg_Pbg_PbgType*	pstPbgGrp;							/* PBGグループ */
				U1					u1PbgGrpChNum;						/* PBGグループチャネル */
}	ErrH_PbgProtSetChType;

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".ERRH_RODATA_CONST"
/* PBGレジスタ */
static volatile Reg_Pbg_PbgType* const cstErrH_Pbg_Reg[ERRH_SLG_PBG_GROUP_NUM] = {
			&Reg_PBG_PBG00,
			&Reg_PBG_PBG01,
			&Reg_PBG_PBG10,
			&Reg_PBG_PBG20,
			&Reg_PBG_PBG21,
			&Reg_PBG_PBG22,
			&Reg_PBG_PBG23,
			&Reg_PBG_PBG24,
			&Reg_PBG_PBG30,
			&Reg_PBG_PBG31,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_PBG_PBG32,
#else	/* MCU_RH850U2B6 */
			NULL_POINTER,
#endif
			&Reg_PBG_PBG40,
			&Reg_PBG_PBG41,
			&Reg_PBG_PBG50,
			&Reg_PBG_PBG51,
			&Reg_PBG_PBG60,
			&Reg_PBG_PBG61,
			&Reg_PBG_PBG62,
			&Reg_PBG_PBG70,
			&Reg_PBG_PBG71,
			&Reg_PBG_PBG8H0,
			&Reg_PBG_PBG8L0,
			&Reg_PBG_PBG90,
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
			&Reg_PBG_PBG92,
#else	/* MCU_RH850U2B6 */
			NULL_POINTER,
#endif
			&Reg_PBG_PBG100,
			&Reg_PBG_PBG11H0,
			&Reg_PBG_PBG11H1,
			&Reg_PBG_PBG11L0
};

static volatile Reg_Pbg_PbgErrSlvType* const cstErrH_PbgErrSlv_Reg[ERRH_SLG_PBG_GROUP_NUM] = {
			&Reg_PBG_PBGERRSLV00,
			&Reg_PBG_PBGERRSLV00,
			&Reg_PBG_PBGERRSLV10,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV30,
			&Reg_PBG_PBGERRSLV30,
			&Reg_PBG_PBGERRSLV30,
			&Reg_PBG_PBGERRSLV40,
			&Reg_PBG_PBGERRSLV40,
			&Reg_PBG_PBGERRSLV50,
			&Reg_PBG_PBGERRSLV50,
			&Reg_PBG_PBGERRSLV60,
			&Reg_PBG_PBGERRSLV60,
			&Reg_PBG_PBGERRSLV62,
			&Reg_PBG_PBGERRSLV70,
			&Reg_PBG_PBGERRSLV70,
			&Reg_PBG_PBGERRSLV8H0,
			&Reg_PBG_PBGERRSLV8L0,
			&Reg_PBG_PBGERRSLV90,
			&Reg_PBG_PBGERRSLV90,
			&Reg_PBG_PBGERRSLV100,
			&Reg_PBG_PBGERRSLV11H0,
			&Reg_PBG_PBGERRSLV11H0,
			&Reg_PBG_PBGERRSLV11L0,
};

static volatile Reg_Pbg_PbgErrSlvType* const cstErrH_PbgErrSlv[u1ERRH_PBG_PBGERRSLV_NUM] = {
			&Reg_PBG_PBGERRSLV00,
			&Reg_PBG_PBGERRSLV10,
			&Reg_PBG_PBGERRSLV20,
			&Reg_PBG_PBGERRSLV30,
			&Reg_PBG_PBGERRSLV40,
			&Reg_PBG_PBGERRSLV50,
			&Reg_PBG_PBGERRSLV60,
			&Reg_PBG_PBGERRSLV62,
			&Reg_PBG_PBGERRSLV70,
			&Reg_PBG_PBGERRSLV8H0,
			&Reg_PBG_PBGERRSLV8L0,
			&Reg_PBG_PBGERRSLV90,
			&Reg_PBG_PBGERRSLV100,
			&Reg_PBG_PBGERRSLV11H0,
			&Reg_PBG_PBGERRSLV11L0
};

static volatile ErrH_PbgProtSetChType const cstErrH_PbgProtSetCh[u2ERRH_PBG_PBGPROTSETCH_NUM] = {
	{	&Reg_PBG_PBG00,		(U1)0U	},
	{	&Reg_PBG_PBG00,		(U1)1U	},
	{	&Reg_PBG_PBG00,		(U1)2U	},
	{	&Reg_PBG_PBG00,		(U1)3U	},
	{	&Reg_PBG_PBG00,		(U1)4U	},
	{	&Reg_PBG_PBG00,		(U1)5U	},
	{	&Reg_PBG_PBG00,		(U1)7U	},
	{	&Reg_PBG_PBG00,		(U1)8U	},
	{	&Reg_PBG_PBG00,		(U1)9U	},
	{	&Reg_PBG_PBG00,		(U1)10U	},
	{	&Reg_PBG_PBG01,		(U1)0U	},
	{	&Reg_PBG_PBG01,		(U1)1U	},
	{	&Reg_PBG_PBG01,		(U1)2U	},
	{	&Reg_PBG_PBG01,		(U1)3U	},
	{	&Reg_PBG_PBG01,		(U1)4U	},
	{	&Reg_PBG_PBG01,		(U1)5U	},
	{	&Reg_PBG_PBG01,		(U1)8U	},
	{	&Reg_PBG_PBG01,		(U1)9U	},
	{	&Reg_PBG_PBG01,		(U1)10U	},
	{	&Reg_PBG_PBG01,		(U1)11U	},
	{	&Reg_PBG_PBG01,		(U1)12U	},
	{	&Reg_PBG_PBG01,		(U1)13U	},
	{	&Reg_PBG_PBG10,		(U1)0U	},
	{	&Reg_PBG_PBG10,		(U1)1U	},
	{	&Reg_PBG_PBG10,		(U1)2U	},
	{	&Reg_PBG_PBG20,		(U1)0U	},
	{	&Reg_PBG_PBG20,		(U1)1U	},
	{	&Reg_PBG_PBG20,		(U1)2U	},
	{	&Reg_PBG_PBG20,		(U1)3U	},
	{	&Reg_PBG_PBG20,		(U1)4U	},
	{	&Reg_PBG_PBG20,		(U1)5U	},
	{	&Reg_PBG_PBG20,		(U1)6U	},
	{	&Reg_PBG_PBG20,		(U1)7U	},
	{	&Reg_PBG_PBG20,		(U1)8U	},
	{	&Reg_PBG_PBG20,		(U1)9U	},
	{	&Reg_PBG_PBG20,		(U1)10U	},
	{	&Reg_PBG_PBG20,		(U1)11U	},
	{	&Reg_PBG_PBG20,		(U1)12U	},
	{	&Reg_PBG_PBG20,		(U1)13U	},
	{	&Reg_PBG_PBG20,		(U1)14U	},
	{	&Reg_PBG_PBG20,		(U1)15U	},
	{	&Reg_PBG_PBG21,		(U1)0U	},
	{	&Reg_PBG_PBG21,		(U1)1U	},
	{	&Reg_PBG_PBG21,		(U1)2U	},
	{	&Reg_PBG_PBG21,		(U1)3U	},
	{	&Reg_PBG_PBG21,		(U1)4U	},
	{	&Reg_PBG_PBG21,		(U1)5U	},
	{	&Reg_PBG_PBG21,		(U1)6U	},
	{	&Reg_PBG_PBG21,		(U1)7U	},
	{	&Reg_PBG_PBG21,		(U1)8U	},
	{	&Reg_PBG_PBG21,		(U1)9U	},
	{	&Reg_PBG_PBG21,		(U1)10U	},
	{	&Reg_PBG_PBG21,		(U1)11U	},
	{	&Reg_PBG_PBG21,		(U1)12U	},
	{	&Reg_PBG_PBG21,		(U1)13U	},
	{	&Reg_PBG_PBG21,		(U1)14U	},
	{	&Reg_PBG_PBG21,		(U1)15U	},
	{	&Reg_PBG_PBG22,		(U1)0U	},
	{	&Reg_PBG_PBG22,		(U1)1U	},
	{	&Reg_PBG_PBG22,		(U1)2U	},
	{	&Reg_PBG_PBG22,		(U1)4U	},
	{	&Reg_PBG_PBG22,		(U1)5U	},
	{	&Reg_PBG_PBG22,		(U1)6U	},
	{	&Reg_PBG_PBG22,		(U1)7U	},
	{	&Reg_PBG_PBG22,		(U1)8U	},
	{	&Reg_PBG_PBG22,		(U1)9U	},
	{	&Reg_PBG_PBG22,		(U1)10U	},
	{	&Reg_PBG_PBG22,		(U1)11U	},
	{	&Reg_PBG_PBG22,		(U1)12U	},
	{	&Reg_PBG_PBG22,		(U1)13U	},
	{	&Reg_PBG_PBG22,		(U1)14U	},
	{	&Reg_PBG_PBG22,		(U1)15U	},
	{	&Reg_PBG_PBG23,		(U1)0U	},
	{	&Reg_PBG_PBG23,		(U1)1U	},
	{	&Reg_PBG_PBG23,		(U1)2U	},
	{	&Reg_PBG_PBG23,		(U1)3U	},
	{	&Reg_PBG_PBG23,		(U1)4U	},
	{	&Reg_PBG_PBG23,		(U1)5U	},
	{	&Reg_PBG_PBG23,		(U1)6U	},
	{	&Reg_PBG_PBG23,		(U1)7U	},
	{	&Reg_PBG_PBG23,		(U1)8U	},
	{	&Reg_PBG_PBG23,		(U1)9U	},
	{	&Reg_PBG_PBG23,		(U1)10U	},
	{	&Reg_PBG_PBG23,		(U1)11U	},
	{	&Reg_PBG_PBG23,		(U1)12U	},
	{	&Reg_PBG_PBG23,		(U1)13U	},
	{	&Reg_PBG_PBG23,		(U1)14U	},
	{	&Reg_PBG_PBG23,		(U1)15U	},
	{	&Reg_PBG_PBG24,		(U1)0U	},
	{	&Reg_PBG_PBG24,		(U1)1U	},
	{	&Reg_PBG_PBG30,		(U1)0U	},
	{	&Reg_PBG_PBG30,		(U1)1U	},
	{	&Reg_PBG_PBG30,		(U1)2U	},
	{	&Reg_PBG_PBG30,		(U1)3U	},
	{	&Reg_PBG_PBG30,		(U1)4U	},
	{	&Reg_PBG_PBG30,		(U1)5U	},
	{	&Reg_PBG_PBG30,		(U1)6U	},
	{	&Reg_PBG_PBG30,		(U1)7U	},
	{	&Reg_PBG_PBG30,		(U1)8U	},
	{	&Reg_PBG_PBG30,		(U1)10U	},
	{	&Reg_PBG_PBG30,		(U1)11U	},
	{	&Reg_PBG_PBG30,		(U1)12U	},
	{	&Reg_PBG_PBG30,		(U1)13U	},
	{	&Reg_PBG_PBG30,		(U1)14U	},
	{	&Reg_PBG_PBG30,		(U1)15U	},
	{	&Reg_PBG_PBG31,		(U1)0U	},
	{	&Reg_PBG_PBG31,		(U1)1U	},
	{	&Reg_PBG_PBG31,		(U1)2U	},
	{	&Reg_PBG_PBG31,		(U1)3U	},
	{	&Reg_PBG_PBG31,		(U1)4U	},
	{	&Reg_PBG_PBG31,		(U1)5U	},
	{	&Reg_PBG_PBG31,		(U1)7U	},
	{	&Reg_PBG_PBG31,		(U1)8U	},
	{	&Reg_PBG_PBG31,		(U1)9U	},
	{	&Reg_PBG_PBG31,		(U1)10U	},
	{	&Reg_PBG_PBG31,		(U1)11U	},
	{	&Reg_PBG_PBG31,		(U1)12U	},
	{	&Reg_PBG_PBG31,		(U1)13U	},
	{	&Reg_PBG_PBG31,		(U1)14U	},
	{	&Reg_PBG_PBG31,		(U1)15U	},
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	{	&Reg_PBG_PBG32,		(U1)0U	},
	{	&Reg_PBG_PBG32,		(U1)1U	},
	{	&Reg_PBG_PBG32,		(U1)2U	},
	{	&Reg_PBG_PBG32,		(U1)3U	},
	{	&Reg_PBG_PBG32,		(U1)4U	},
	{	&Reg_PBG_PBG32,		(U1)5U	},
	{	&Reg_PBG_PBG32,		(U1)6U	},
#endif
	{	&Reg_PBG_PBG40,		(U1)0U	},
	{	&Reg_PBG_PBG40,		(U1)1U	},
	{	&Reg_PBG_PBG40,		(U1)2U	},
	{	&Reg_PBG_PBG40,		(U1)3U	},
	{	&Reg_PBG_PBG40,		(U1)4U	},
	{	&Reg_PBG_PBG40,		(U1)5U	},
	{	&Reg_PBG_PBG40,		(U1)6U	},
	{	&Reg_PBG_PBG40,		(U1)7U	},
	{	&Reg_PBG_PBG40,		(U1)8U	},
	{	&Reg_PBG_PBG40,		(U1)10U	},
	{	&Reg_PBG_PBG40,		(U1)11U	},
	{	&Reg_PBG_PBG40,		(U1)12U	},
	{	&Reg_PBG_PBG40,		(U1)13U	},
	{	&Reg_PBG_PBG40,		(U1)14U	},
	{	&Reg_PBG_PBG40,		(U1)15U	},
	{	&Reg_PBG_PBG41,		(U1)0U	},
	{	&Reg_PBG_PBG41,		(U1)1U	},
	{	&Reg_PBG_PBG41,		(U1)2U	},
	{	&Reg_PBG_PBG41,		(U1)3U	},
	{	&Reg_PBG_PBG41,		(U1)4U	},
	{	&Reg_PBG_PBG41,		(U1)5U	},
	{	&Reg_PBG_PBG41,		(U1)6U	},
	{	&Reg_PBG_PBG41,		(U1)7U	},
	{	&Reg_PBG_PBG41,		(U1)8U	},
	{	&Reg_PBG_PBG41,		(U1)9U	},
	{	&Reg_PBG_PBG41,		(U1)10U	},
	{	&Reg_PBG_PBG41,		(U1)11U	},
	{	&Reg_PBG_PBG41,		(U1)12U	},
	{	&Reg_PBG_PBG41,		(U1)13U	},
	{	&Reg_PBG_PBG41,		(U1)14U	},
	{	&Reg_PBG_PBG50,		(U1)0U	},
	{	&Reg_PBG_PBG50,		(U1)1U	},
	{	&Reg_PBG_PBG50,		(U1)2U	},
	{	&Reg_PBG_PBG50,		(U1)3U	},
	{	&Reg_PBG_PBG50,		(U1)4U	},
	{	&Reg_PBG_PBG50,		(U1)5U	},
	{	&Reg_PBG_PBG50,		(U1)6U	},
	{	&Reg_PBG_PBG50,		(U1)7U	},
	{	&Reg_PBG_PBG50,		(U1)8U	},
	{	&Reg_PBG_PBG50,		(U1)9U	},
	{	&Reg_PBG_PBG50,		(U1)10U	},
	{	&Reg_PBG_PBG50,		(U1)13U	},
	{	&Reg_PBG_PBG50,		(U1)14U	},
	{	&Reg_PBG_PBG50,		(U1)15U	},
	{	&Reg_PBG_PBG51,		(U1)0U	},
	{	&Reg_PBG_PBG51,		(U1)1U	},
	{	&Reg_PBG_PBG51,		(U1)2U	},
	{	&Reg_PBG_PBG51,		(U1)3U	},
	{	&Reg_PBG_PBG51,		(U1)4U	},
	{	&Reg_PBG_PBG51,		(U1)6U	},
	{	&Reg_PBG_PBG51,		(U1)7U	},
	{	&Reg_PBG_PBG51,		(U1)8U	},
	{	&Reg_PBG_PBG51,		(U1)11U	},
	{	&Reg_PBG_PBG51,		(U1)12U	},
	{	&Reg_PBG_PBG51,		(U1)13U	},
	{	&Reg_PBG_PBG51,		(U1)14U	},
	{	&Reg_PBG_PBG51,		(U1)15U	},
	{	&Reg_PBG_PBG60,		(U1)0U	},
	{	&Reg_PBG_PBG60,		(U1)1U	},
	{	&Reg_PBG_PBG60,		(U1)2U	},
	{	&Reg_PBG_PBG60,		(U1)3U	},
	{	&Reg_PBG_PBG60,		(U1)4U	},
	{	&Reg_PBG_PBG60,		(U1)5U	},
	{	&Reg_PBG_PBG60,		(U1)7U	},
	{	&Reg_PBG_PBG60,		(U1)8U	},
	{	&Reg_PBG_PBG60,		(U1)9U	},
	{	&Reg_PBG_PBG60,		(U1)10U	},
	{	&Reg_PBG_PBG60,		(U1)11U	},
	{	&Reg_PBG_PBG60,		(U1)12U	},
	{	&Reg_PBG_PBG60,		(U1)13U	},
	{	&Reg_PBG_PBG60,		(U1)14U	},
	{	&Reg_PBG_PBG60,		(U1)15U	},
	{	&Reg_PBG_PBG61,		(U1)0U	},
	{	&Reg_PBG_PBG61,		(U1)1U	},
	{	&Reg_PBG_PBG61,		(U1)2U	},
	{	&Reg_PBG_PBG61,		(U1)3U	},
	{	&Reg_PBG_PBG61,		(U1)4U	},
	{	&Reg_PBG_PBG61,		(U1)5U	},
	{	&Reg_PBG_PBG61,		(U1)6U	},
	{	&Reg_PBG_PBG61,		(U1)7U	},
	{	&Reg_PBG_PBG61,		(U1)8U	},
	{	&Reg_PBG_PBG62,		(U1)0U	},
	{	&Reg_PBG_PBG62,		(U1)1U	},
	{	&Reg_PBG_PBG62,		(U1)2U	},
	{	&Reg_PBG_PBG62,		(U1)3U	},
	{	&Reg_PBG_PBG70,		(U1)0U	},
	{	&Reg_PBG_PBG70,		(U1)1U	},
	{	&Reg_PBG_PBG70,		(U1)2U	},
	{	&Reg_PBG_PBG70,		(U1)3U	},
	{	&Reg_PBG_PBG70,		(U1)4U	},
	{	&Reg_PBG_PBG70,		(U1)5U	},
	{	&Reg_PBG_PBG70,		(U1)6U	},
	{	&Reg_PBG_PBG70,		(U1)7U	},
	{	&Reg_PBG_PBG70,		(U1)8U	},
	{	&Reg_PBG_PBG70,		(U1)9U	},
	{	&Reg_PBG_PBG70,		(U1)10U	},
	{	&Reg_PBG_PBG70,		(U1)11U	},
	{	&Reg_PBG_PBG70,		(U1)12U	},
	{	&Reg_PBG_PBG70,		(U1)13U	},
	{	&Reg_PBG_PBG70,		(U1)14U	},
	{	&Reg_PBG_PBG70,		(U1)15U	},
	{	&Reg_PBG_PBG71,		(U1)0U	},
	{	&Reg_PBG_PBG71,		(U1)1U	},
	{	&Reg_PBG_PBG71,		(U1)2U	},
	{	&Reg_PBG_PBG71,		(U1)3U	},
	{	&Reg_PBG_PBG8H0,	(U1)0U	},
	{	&Reg_PBG_PBG8H0,	(U1)1U	},
	{	&Reg_PBG_PBG8H0,	(U1)2U	},
	{	&Reg_PBG_PBG8H0,	(U1)3U	},
	{	&Reg_PBG_PBG8H0,	(U1)4U	},
	{	&Reg_PBG_PBG8H0,	(U1)5U	},
	{	&Reg_PBG_PBG8H0,	(U1)6U	},
	{	&Reg_PBG_PBG8H0,	(U1)7U	},
	{	&Reg_PBG_PBG8H0,	(U1)8U	},
	{	&Reg_PBG_PBG8H0,	(U1)9U	},
	{	&Reg_PBG_PBG8H0,	(U1)10U	},
	{	&Reg_PBG_PBG8L0,	(U1)0U	},
	{	&Reg_PBG_PBG8L0,	(U1)1U	},
	{	&Reg_PBG_PBG8L0,	(U1)2U	},
	{	&Reg_PBG_PBG8L0,	(U1)3U	},
	{	&Reg_PBG_PBG8L0,	(U1)4U	},
	{	&Reg_PBG_PBG8L0,	(U1)6U	},
	{	&Reg_PBG_PBG8L0,	(U1)7U	},
	{	&Reg_PBG_PBG8L0,	(U1)8U	},
	{	&Reg_PBG_PBG8L0,	(U1)9U	},
	{	&Reg_PBG_PBG8L0,	(U1)10U	},
	{	&Reg_PBG_PBG8L0,	(U1)11U	},
	{	&Reg_PBG_PBG8L0,	(U1)12U	},
	{	&Reg_PBG_PBG8L0,	(U1)14U	},
	{	&Reg_PBG_PBG8L0,	(U1)15U	},
	{	&Reg_PBG_PBG90,		(U1)0U	},
	{	&Reg_PBG_PBG90,		(U1)1U	},
	{	&Reg_PBG_PBG90,		(U1)2U	},
	{	&Reg_PBG_PBG90,		(U1)3U	},
	{	&Reg_PBG_PBG90,		(U1)4U	},
	{	&Reg_PBG_PBG90,		(U1)5U	},
	{	&Reg_PBG_PBG90,		(U1)6U	},
	{	&Reg_PBG_PBG90,		(U1)7U	},
	{	&Reg_PBG_PBG90,		(U1)8U	},
	{	&Reg_PBG_PBG90,		(U1)9U	},
#if ( MCU_TYPE_SERIES == MCU_RH850U2B10 )
	{	&Reg_PBG_PBG92,		(U1)0U	},
	{	&Reg_PBG_PBG92,		(U1)1U	},
	{	&Reg_PBG_PBG92,		(U1)2U	},
	{	&Reg_PBG_PBG92,		(U1)3U	},
	{	&Reg_PBG_PBG92,		(U1)4U	},
	{	&Reg_PBG_PBG92,		(U1)5U	},
	{	&Reg_PBG_PBG92,		(U1)6U	},
	{	&Reg_PBG_PBG92,		(U1)7U	},
#endif
	{	&Reg_PBG_PBG100,	(U1)0U	},
	{	&Reg_PBG_PBG100,	(U1)1U	},
	{	&Reg_PBG_PBG100,	(U1)2U	},
	{	&Reg_PBG_PBG100,	(U1)3U	},
	{	&Reg_PBG_PBG100,	(U1)4U	},
	{	&Reg_PBG_PBG100,	(U1)5U	},
	{	&Reg_PBG_PBG100,	(U1)6U	},
	{	&Reg_PBG_PBG100,	(U1)7U	},
	{	&Reg_PBG_PBG100,	(U1)8U	},
	{	&Reg_PBG_PBG100,	(U1)9U	},
	{	&Reg_PBG_PBG100,	(U1)10U	},
	{	&Reg_PBG_PBG100,	(U1)11U	},
	{	&Reg_PBG_PBG100,	(U1)13U	},
	{	&Reg_PBG_PBG100,	(U1)14U	},
	{	&Reg_PBG_PBG100,	(U1)15U	},
	{	&Reg_PBG_PBG11H0,	(U1)0U	},
	{	&Reg_PBG_PBG11H0,	(U1)1U	},
	{	&Reg_PBG_PBG11H0,	(U1)2U	},
	{	&Reg_PBG_PBG11H0,	(U1)3U	},
	{	&Reg_PBG_PBG11H0,	(U1)4U	},
	{	&Reg_PBG_PBG11H0,	(U1)5U	},
	{	&Reg_PBG_PBG11H0,	(U1)6U	},
	{	&Reg_PBG_PBG11H0,	(U1)7U	},
	{	&Reg_PBG_PBG11H0,	(U1)8U	},
	{	&Reg_PBG_PBG11H0,	(U1)9U	},
	{	&Reg_PBG_PBG11H0,	(U1)10U	},
	{	&Reg_PBG_PBG11H0,	(U1)11U	},
	{	&Reg_PBG_PBG11H0,	(U1)12U	},
	{	&Reg_PBG_PBG11H0,	(U1)14U	},
	{	&Reg_PBG_PBG11H0,	(U1)15U	},
	{	&Reg_PBG_PBG11H1,	(U1)0U	},
	{	&Reg_PBG_PBG11H1,	(U1)3U	},
	{	&Reg_PBG_PBG11H1,	(U1)4U	},
	{	&Reg_PBG_PBG11H1,	(U1)5U	},
	{	&Reg_PBG_PBG11H1,	(U1)6U	},
	{	&Reg_PBG_PBG11H1,	(U1)7U	},
	{	&Reg_PBG_PBG11H1,	(U1)8U	},
	{	&Reg_PBG_PBG11H1,	(U1)9U	},
	{	&Reg_PBG_PBG11H1,	(U1)10U	},
	{	&Reg_PBG_PBG11H1,	(U1)11U	},
	{	&Reg_PBG_PBG11H1,	(U1)12U	},
	{	&Reg_PBG_PBG11H1,	(U1)13U	},
	{	&Reg_PBG_PBG11H1,	(U1)14U	},
	{	&Reg_PBG_PBG11H1,	(U1)15U	},
	{	&Reg_PBG_PBG11L0,	(U1)0U	},
	{	&Reg_PBG_PBG11L0,	(U1)2U	},
	{	&Reg_PBG_PBG11L0,	(U1)3U	},
	{	&Reg_PBG_PBG11L0,	(U1)4U	},
	{	&Reg_PBG_PBG11L0,	(U1)5U	},
	{	&Reg_PBG_PBG11L0,	(U1)6U	},
	{	&Reg_PBG_PBG11L0,	(U1)7U	},
	{	&Reg_PBG_PBG11L0,	(U1)8U	}
};

#pragma ghs section rodata=default

/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".ERRH_TEXT_CODE"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Set Mode & Start Guard Function																*/
/* Return		: none																			*/
/* Parameters	: GroupNum	- Group Number( 0～27 )												*/
/*				: ChNum		- Channel Number( 0～15 )											*/
/*				: Prot		- unPBGPROT0n Value													*/
/*				: Spid		- unPBGPROT1n Value													*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Pbg_SetModeStartGuard( U1 t_u1GroupNum , U1 t_u1ChNum , U4 t_u4Prot , U4 t_u4Spid )
{
	volatile	Reg_Pbg_PbgType*		t_pstRegPbg;
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstRegPbgSlv;
				U4						t_u4RegTemp;

	t_pstRegPbg = (volatile Reg_Pbg_PbgType*)cstErrH_Pbg_Reg[t_u1GroupNum];
	t_pstRegPbgSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv_Reg[t_u1GroupNum];

	if ( t_pstRegPbg != NULL_POINTER ) 
	{
		/* PBGKCPROT - PB ガードキーコード保護レジスタ 保護解除 */
		t_pstRegPbgSlv->unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_ENABLE;

		t_u4RegTemp = u4ERRH_PBG_REGPROTMASK & t_u4Prot;												/* 必要なビットのみを抽出 */
		t_pstRegPbg->stPBGPROT01[ t_u1ChNum ].u4PBGPROT1		= (U4)t_u4Spid;							/* チャネル SPID 設定 */
		t_pstRegPbg->stPBGPROT01[ t_u1ChNum ].unPBGPROT0.u4Data	= t_u4RegTemp;							/* チャネル保護制御 */

		/* PBGKCPROT - PB ガードキーコード保護レジスタ 保護設定 */
		t_pstRegPbgSlv->unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstRegPbgSlv->unPBGKCPROT.u4Data );
	}

}

/*----------------------------------------------------------------------------------------------*/
/* PBG Clear Error Function																		*/
/* Return		: none																			*/
/* Parameters	: ModuleNum - PBG Module Number( 300～327  )									*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Pbg_ClearError( U2 t_u2ModuleNum )
{
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstRegPbgSlv;
				U1						t_u1GroupNum;
	
	t_u1GroupNum = (U1)(t_u2ModuleNum - u2ERRH_PBG_MODULEMASK);		/* モジュールNo→グループNo */

	if ( t_u1GroupNum <= (U1)ERRH_SLG_PBG_GROUP_NUM )
	{
		t_pstRegPbgSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv_Reg[t_u1GroupNum];

		/* エラーステータスクリア */
		t_pstRegPbgSlv->unPBGOVFCLR.u4Data	=	(U4)( (U4)PBG_PBGOVFCLR_CLRO * (U4)PBG_PBGOVFCLR_CLRO_CLEAR );
		t_pstRegPbgSlv->u4PBGSPIDERRCLR	=	u4ERRH_PBG_PBGSPIDERRCLR_ALLBIT_CLR;

		Bswlib_Sync_Pipeline_4( t_pstRegPbgSlv->unPBGOVFCLR.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* PBG Get Error Status Function																*/
/* Return		: Error Status																	*/
/* Parameters	: ModuleNum - PBG Module Number( 300～327  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Pbg_GetErrorStatus( U2 t_u2ModuleNum )
{
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstRegPbgSlv;
				U1						t_u1GroupNum;		/* グループNo */
				U4						t_u4ErrorStatus;	/* エラーステータス */

	t_u4ErrorStatus = u4ERRH_PBG_NOERR;	/* エラーなしで初期化 */

	t_u1GroupNum = (U1)(t_u2ModuleNum - u2ERRH_PBG_MODULEMASK);		/* モジュールNo→グループNo */

	if ( t_u1GroupNum <= (U1)ERRH_SLG_PBG_GROUP_NUM )
	{
		t_pstRegPbgSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv_Reg[t_u1GroupNum];

		/* エラーステータス取得 */
		t_u4ErrorStatus = t_pstRegPbgSlv->unPBGOVFSTAT.u4Data;

		if( t_pstRegPbgSlv->u4PBGSPIDERRSTAT != u4ERRH_PBG_PBGSPIDERRSTAT_NOERR )
		{
			t_u4ErrorStatus |= u4ERRH_PBG_ERRSTAT_SPIDERR;
		}
	}
	
	return( t_u4ErrorStatus );
}

/*----------------------------------------------------------------------------------------------*/
/* PBG Get Error Address Function																*/
/* Return		: Error Address																	*/
/* Parameters	: ModuleNum - PBG Module Number( 300～327  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Pbg_GetErrAddress( U2 t_u2ModuleNum  )
{
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstRegPbgSlv;
				U1						t_u1GroupNum;		/* グループNo */
				U4						t_u4ErrorAddress;	/* エラーアドレス */

	t_u4ErrorAddress = u4ERRH_PBG_INVALID_ADDR;	/* エラーアドレス無効値で初期化 */

	t_u1GroupNum = (U1)(t_u2ModuleNum - u2ERRH_PBG_MODULEMASK);		/* モジュールNo→グループNo */

	if ( t_u1GroupNum <= (U1)ERRH_SLG_PBG_GROUP_NUM )
	{
		t_pstRegPbgSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv_Reg[t_u1GroupNum];

		/* エラーアドレス取得 */
		t_u4ErrorAddress = t_pstRegPbgSlv->u4PBGERRADDR;
	}

	return( t_u4ErrorAddress );
}

/*----------------------------------------------------------------------------------------------*/
/* PBG Get Error Access info Function															*/
/* Return		: Error Access info																*/
/* Parameters	: ModuleNum - PBG Module Number( 300～327  )									*/
/*----------------------------------------------------------------------------------------------*/
U4	ErrH_Pbg_GetErrAccessInfo( U2 t_u2ModuleNum )
{
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstRegPbgSlv;
				U1						t_u1GroupNum;			/* グループNo */
				U4						t_u4ErrorAccessInfo;	/* エラーアクセス情報 */

	t_u4ErrorAccessInfo =  u4ERRH_PBG_INVALID_INFO;	/* エラーアクセス情報無効値で初期化 */

	t_u1GroupNum = (U1)(t_u2ModuleNum - u2ERRH_PBG_MODULEMASK);		/* モジュールNo→グループNo */

	if ( t_u1GroupNum <= (U1)ERRH_SLG_PBG_GROUP_NUM )
	{
		t_pstRegPbgSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv_Reg[t_u1GroupNum];
	
		/* エラーアクセス情報取得 */
		t_u4ErrorAccessInfo = t_pstRegPbgSlv->unPBGERRTYPE.u4Data;
	}

	return( t_u4ErrorAccessInfo );
}

/*----------------------------------------------------------------------------------------------*/
/* PBG Disable All Guard Function																*/
/* Return		: none																			*/
/* Parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	ErrH_Pbg_DisableAllGuard( void )
{
	volatile	Reg_Pbg_PbgType*		t_pstReg_Pbg;
	volatile	Reg_Pbg_PbgErrSlvType*	t_pstReg_PbgErrSlv;
				S4						i;
				U1						t_u1ChNum;

	/* PBGレジスタのKey Code Protection解除 */
	for( i = (S4)0; i < (S4)u1ERRH_PBG_PBGERRSLV_NUM; i++ )
	{
		t_pstReg_PbgErrSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv[i];
		t_pstReg_PbgErrSlv->unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_ENABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbgErrSlv->unPBGKCPROT.u4Data );
	}

	/* PBGの保護無効化 */
	for( i = (S4)0; i < (S4)u2ERRH_PBG_PBGPROTSETCH_NUM; i++ )
	{
		t_pstReg_Pbg = (volatile Reg_Pbg_PbgType*)cstErrH_PbgProtSetCh[i].pstPbgGrp;
		t_u1ChNum = cstErrH_PbgProtSetCh[i].u1PbgGrpChNum;
		t_pstReg_Pbg->stPBGPROT01[ t_u1ChNum ].unPBGPROT0.u4Data	= u4ERRH_PBG_NO_GUARD;
		Bswlib_Sync_Pipeline_4( t_pstReg_Pbg->stPBGPROT01[ t_u1ChNum ].unPBGPROT0.u4Data );
	}

	/* PBGレジスタのKey Code Protection再開 */
	for( i = (S4)0; i < (S4)u1ERRH_PBG_PBGERRSLV_NUM; i++ )
	{
		t_pstReg_PbgErrSlv = (volatile Reg_Pbg_PbgErrSlvType*)cstErrH_PbgErrSlv[i];
		t_pstReg_PbgErrSlv->unPBGKCPROT.u4Data = (U4)PBG_PBGKCPROT_KCE_DISABLE;
		Bswlib_Sync_Pipeline_4( t_pstReg_PbgErrSlv->unPBGKCPROT.u4Data );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/

#pragma ghs section text=default

#endif // zantei MPUは2月末非対応
/*-- End Of File -------------------------------------------------------------------------------*/
