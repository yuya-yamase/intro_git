/* 1.3.0-800B-1*/
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  EV Communication Control                                                                                                         */
/*===================================================================================================================================*/

#ifndef EVCOM_CFG_H
#define EVCOM_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVCOM_CFG_H_MAJOR					(1)
#define EVCOM_CFG_H_MINOR					(3)
#define EVCOM_CFG_H_PATCH					(0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

#include "memfill_u1.h"
#include "veh_opemd.h"
#include "locale.h"
/*#include "dsptimchgctl.h" *This parameter is used only by Tm-2. */
#include "rim_ctl_cfg.h"

#include "evcom.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
	U1 u1_max;		/* Display Status (Charge Current Setting - MAX)	 */
	U1 u1_16a;		/* Display Status (Charge Current Setting - 16A)	 */
	U1 u1_8a;		/* Display Status (Charge Current Setting -  8A)	 */
}ST_EVCOM_CHGCUR_DSP;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __EVCOM_15PF__						(15)								/* 15PF												 */
#define __EVCOM_19PF__						(19)								/* Above 19PF										 */
#define __EVCOM_PF_VER__					(__EVCOM_19PF__)					/* Platform Versin									 */

#define __EVCOM_CHARGE_CURRENT_SUP__		(0)									/* Charge Current Setting (0:unsupport, 1:support)	 */
#define __EVCOM_CONNECTOR_LOCK_SUP__		(0)									/* Connector Lock Setting (0:unsupport, 1:support)	 */
#define __EVCOM_CHARGE_LIMIT_SUP__			(0)									/* Charge Limit Setting (0:unsupport, 1:support)	 */
#define __EVCOM_EXTERNAL_SUPPLY_SUP__		(0)									/* External Supply (0:unsupport, 1:support)			 */

#define u1_EVCOM_GET_IG_STS()				(u1_g_VehopemdIgnOn())				/* IG Status										 */

#define u1_EVCOM_GET_CLK_FMT()				(u1_g_TimeFormat12H24H())			/* Clock Format (12H/24H)							 */
#define EVCOM_CLK_FMT_12H					(TIMEFMT_VAL_12H)					/* 12H												 */
#define EVCOM_CLK_FMT_24H					(TIMEFMT_VAL_24H)					/* 24H												 */

#define u1_EVCOM_MSGSTS_PLG1S01()			((U1)COM_NO_RX)/*((U1)Com_GetIPDUStatus(MSG_PLG1S01_RXCH0))*/		/* Message Status : PLG1S01			 */

#if (__EVCOM_PF_VER__ == __EVCOM_15PF__)
#define u1_EVCOM_MSGSTS_PLG1G10()			((U1)Com_GetIPDUStatus(MSG_PLG1S08_10_RXCH0))	/* Message Status : PLG1S08 SubID:10 */
#define u1_EVCOM_MSGSTS_PLG1G11()			((U1)Com_GetIPDUStatus(MSG_PLG1S08_11_RXCH0))	/* Message Status : PLG1S08 SubID:11 */
#define u1_EVCOM_MSGSTS_PLG1G12()			((U1)Com_GetIPDUStatus(MSG_PLG1S08_12_RXCH0))	/* Message Status : PLG1S08 SubID:12 */
#define u1_EVCOM_MSGSTS_PLG1G13()			((U1)Com_GetIPDUStatus(MSG_PLG1S08_13_RXCH0))	/* Message Status : PLG1S08 SubID:13 */
#else
#define u1_EVCOM_MSGSTS_PLG1G10()			(COM_NO_RX)/*((U1)Com_GetIPDUStatus(MSG_PLG1G10_RXCH0))*/		/* Message Status : PLG1G10			 */
#define u1_EVCOM_MSGSTS_PLG1G11()			((U1)Com_GetIPDUStatus(MSG_PLG1G11_RXCH0))		/* Message Status : PLG1G11			 */
#define u1_EVCOM_MSGSTS_PLG1G12()			(COM_NO_RX)/*((U1)Com_GetIPDUStatus(MSG_PLG1G12_RXCH0))*/		/* Message Status : PLG1G12			 */
#define u1_EVCOM_MSGSTS_PLG1G13()			((U1)Com_GetIPDUStatus(MSG_PLG1G13_RXCH0))		/* Message Status : PLG1G13			 */
#endif

#define EVCOM_ST_TIMEOUT					(COM_TIMEOUT)									/* Time out								 */
#define EVCOM_ST_NO_RX						(COM_NO_RX)										/* No Receive							 */

#if (__EVCOM_CHARGE_CURRENT_SUP__ == 1)
#define vd_EVCOM_GET_P_CURDSP(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_P_CURDSP,(x)))	/* Get Rx Data : P_CURDSP	 */
#define vd_EVCOM_GET_P_CUR200(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_P_CUR200,(x)))	/* Get Rx Data : P_CUR200	 */
#define vd_EVCOM_GET_P_CURSEL(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_P_CURSEL,(x)))	/* Get Rx Data : P_CURSEL	 */
#else
#define vd_EVCOM_GET_P_CURDSP(x)																		/* Get Rx Data : P_CURDSP	 */
#define vd_EVCOM_GET_P_CUR200(x)																		/* Get Rx Data : P_CUR200	 */
#define vd_EVCOM_GET_P_CURSEL(x)																		/* Get Rx Data : P_CURSEL	 */
#endif

#if (__EVCOM_CONNECTOR_LOCK_SUP__ == 1)
#define vd_EVCOM_GET_CBLC_AVA(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_CBLC_AVA,(x)))	/* Get Rx Data : CBLC_AVA	 */
#define vd_EVCOM_GET_CBLOCKSU(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_CBLOCKSU,(x)))	/* Get Rx Data : CBLOCKSU	 */
#else
#define vd_EVCOM_GET_CBLC_AVA(x)																		/* Get Rx Data : CBLC_AVA	 */
#define vd_EVCOM_GET_CBLOCKSU(x)																		/* Get Rx Data : CBLOCKSU	 */
#endif

#if (__EVCOM_CHARGE_LIMIT_SUP__ == 1)
#define vd_EVCOM_GET_P_LMTDSP(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_P_LMTDSP,(x)))	/* Get Rx Data : P_LMTDSP	 */
#define vd_EVCOM_GET_P_LMTSET(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_P_LMTSET,(x)))	/* Get Rx Data : P_LMTSET	 */
#else
#define vd_EVCOM_GET_P_LMTDSP(x)																		/* Get Rx Data : P_LMTDSP	 */
#define vd_EVCOM_GET_P_LMTSET(x)																		/* Get Rx Data : P_LMTSET	 */
#endif

#if (__EVCOM_EXTERNAL_SUPPLY_SUP__ == 1)
#define vd_EVCOM_GET_PWSPLAVA(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_PWSPLAVA,(x)))	/* Get Rx Data : PWSPLAVA	 */
#define vd_EVCOM_GET_PWSPPURQ(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_PWSPPURQ,(x)))	/* Get Rx Data : PWSPPURQ	 */
#define vd_EVCOM_GET_EV_SLCT(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_EV_SLCT,(x)))	/* Get Rx Data : EV_SLCT	 */
#define vd_EVCOM_GET_HV_SLCT(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_HV_SLCT,(x)))	/* Get Rx Data : HV_SLCT	 */
#else
#define vd_EVCOM_GET_PWSPLAVA(x)																		/* Get Rx Data : PWSPLAVA	 */
#define vd_EVCOM_GET_PWSPPURQ(x)																		/* Get Rx Data : PWSPPURQ	 */
#define vd_EVCOM_GET_EV_SLCT(x)																			/* Get Rx Data : EV_SLCT	 */
#define vd_EVCOM_GET_HV_SLCT(x)																			/* Get Rx Data : HV_SLCT	 */
#endif

#define vd_EVCOM_GET_P_SETID(x)				/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETID,(x)))*/	/* Get Rx Data : P_SETID	 */
#define vd_EVCOM_GET_P_SETON(x)				/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETON,(x)))*/	/* Get Rx Data : P_SETON	 */
#define vd_EVCOM_GET_P_SETTYP(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETTYP,(x)))*/	/* Get Rx Data : P_SETTYP	 */
#define vd_EVCOM_GET_P_SETSTM(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETSTM,(x)))*/	/* Get Rx Data : P_SETSTM	 */
#define vd_EVCOM_GET_P_SETFTM(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETFTM,(x)))*/	/* Get Rx Data : P_SETFTM	 */
#define vd_EVCOM_GET_P_SETWKD(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETWKD,(x)))*/	/* Get Rx Data : P_SETWKD	 */
#define vd_EVCOM_GET_P_SETNXT(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_SETNXT,(x)))*/	/* Get Rx Data : P_SETNXT	 */
#define vd_EVCOM_GET_P_NCTYP(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_P_NCTYP,(x)))	/* Get Rx Data : P_NCTYP	 */
#define vd_EVCOM_GET_P_NCWKD(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_P_NCWKD,(x)))	/* Get Rx Data : P_NCWKD	 */
#define vd_EVCOM_GET_P_NCSTM(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_P_NCSTM,(x)))	/* Get Rx Data : P_NCSTM	 */
#define vd_EVCOM_GET_P_NCFTM(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_P_NCFTM,(x)))	/* Get Rx Data : P_NCFTM	 */
#define vd_EVCOM_GET_P_ADDDSP(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_ADDDSP,(x)))*/	/* Get Rx Data : P_ADDDSP	 */
#define vd_EVCOM_GET_PCNOWDSP(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_PCNOWDSP,(x)))	/* Get Rx Data : PCNOWDSP	 */
#define vd_EVCOM_GET_PLGTMSW(x)				/*((void)Com_ReceiveSignal(ComConf_ComSignal_PLGTMSW,(x)))*/	/* Get Rx Data : PLGTMSW	 */
#define vd_EVCOM_GET_P_NCDSP(x)				((void)Com_ReceiveSignal(ComConf_ComSignal_P_NCDSP,(x)))	/* Get Rx Data : P_NCDSP	 */
#define vd_EVCOM_GET_P_TMPID(x)				/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPID,(x)))*/	/* Get Rx Data : P_TMPID	 */
#define vd_EVCOM_GET_P_TMPTYP(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPTYP,(x)))*/	/* Get Rx Data : P_TMPTYP	 */
#define vd_EVCOM_GET_P_TMPACD(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPACD,(x)))*/	/* Get Rx Data : P_TMPACD	 */
#define vd_EVCOM_GET_P_TMPACN(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPACN,(x)))*/	/* Get Rx Data : P_TMPACN	 */
#define vd_EVCOM_GET_P_TMPSTM(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPSTM,(x)))*/	/* Get Rx Data : P_TMPSTM	 */
#define vd_EVCOM_GET_P_TMPFTM(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPFTM,(x)))*/	/* Get Rx Data : P_TMPFTM	 */
#define vd_EVCOM_GET_P_TMPSWK(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPSWK,(x)))*/	/* Get Rx Data : P_TMPSWK	 */
#define vd_EVCOM_GET_P_TMPNWK(x)			/*((void)Com_ReceiveSignal(ComConf_ComSignal_P_TMPNWK,(x)))*/	/* Get Rx Data : P_TMPNWK	 */

#define EVCOM_P_CURDSP_INIT					(0)												/* Initial Data : P_CURDSP				 */
#define EVCOM_P_CUR200_INIT					(0)												/* Initial Data : P_CUR200				 */
#define EVCOM_P_CURSEL_INIT					(0)												/* Initial Data : P_CURSEL				 */
#define EVCOM_CBLC_AVA_INIT					(0)												/* Initial Data : CBLC_AVA				 */
#define EVCOM_CBLOCKSU_INIT					(0)												/* Initial Data : CBLOCKSU				 */
#define EVCOM_P_LMTDSP_INIT					(0)												/* Initial Data : P_LMTDSP				 */
#define EVCOM_P_LMTSET_INIT					(0)												/* Initial Data : P_LMTSET				 */
#define EVCOM_PWSPLAVA_INIT					(0)												/* Initial Data : PWSPLVA				 */
#define EVCOM_PWSPPURQ_INIT					(0)												/* Initial Data : PWSPPURQ				 */
#define EVCOM_EV_SLCT_INIT					(0)												/* Initial Data : EV_SLCT				 */
#define EVCOM_HV_SLCT_INIT					(0)												/* Initial Data : HV_SLCT				 */

#define EVCOM_P_SETID_INIT					(0)												/* Initial Data : P_SETID				 */
#define EVCOM_P_SETON_INIT					(0)												/* Initial Data : P_SETON				 */
#define EVCOM_P_SETTYP_INIT					(0)												/* Initial Data : P_SETTYP				 */
#define EVCOM_P_SETSTM_INIT					(0x01FF)										/* Initial Data : P_SETSTM				 */
#define EVCOM_P_SETFTM_INIT					(0x01FF)										/* Initial Data : P_SETFTM				 */
#define EVCOM_P_SETWKD_INIT					(0)												/* Initial Data : P_SETWKD				 */
#define EVCOM_P_SETNXT_INIT					(0x3F)											/* Initial Data : P_SETNXT				 */
#define EVCOM_P_NCTYP_INIT					(0)												/* Initial Data : P_NCTYP				 */
#define EVCOM_P_NCWKD_INIT					(0)												/* Initial Data : P_NCWKD				 */
#define EVCOM_P_NCSTM_INIT					(0x01FF)										/* Initial Data : P_NCSTM				 */
#define EVCOM_P_NCFTM_INIT					(0x01FF)										/* Initial Data : P_NCFTM				 */
#define EVCOM_P_ADDDSP_INIT					(0)												/* Initial Data : P_ADDDSP				 */
#define EVCOM_PCNOWDSP_INIT					(0)												/* Initial Data : PCNOWDSP				 */
#define EVCOM_PLGTMSW_INIT					(0)												/* Initial Data : PLGTMSW				 */
#define EVCOM_P_NCDSP_INIT					(0)												/* Initial Data : P_NCDSP				 */
#define EVCOM_P_TMPID_INIT					(0x3F)											/* Initial Data : P_TMPID				 */
#define EVCOM_P_TMPTYP_INIT					(0)												/* Initial Data : P_TMPTYP				 */
#define EVCOM_P_TMPACD_INIT					(0)												/* Initial Data : P_TMPACD				 */
#define EVCOM_P_TMPACN_INIT					(0)												/* Initial Data : P_TMPACN				 */
#define EVCOM_P_TMPSTM_INIT					(0x01FF)										/* Initial Data : P_TMPSTM				 */
#define EVCOM_P_TMPFTM_INIT					(0x01FF)										/* Initial Data : P_TMPFTM				 */
#define EVCOM_P_TMPSWK_INIT					(0)												/* Initial Data : P_TMPSWK				 */
#define EVCOM_P_TMPNWK_INIT					(0)												/* Initial Data : P_TMPNWK				 */

#define EVCOM_P_CURDSP_FAIL					(0)												/* Rx Fail Data : P_CURDSP				 */
#define EVCOM_P_CURSEL_FAIL					(0)												/* Rx Fail Data : P_CURSEL				 */
#define EVCOM_CBLC_AVA_FAIL					(0)												/* Rx Fail Data : CBLC_AVA				 */
#define EVCOM_CBLOCKSU_FAIL					(0)												/* Rx Fail Data : CBLOCKSU				 */
#define EVCOM_P_LMTDSP_FAIL					(0)												/* Rx Fail Data : P_LMTDSP				 */
#define EVCOM_P_LMTSET_FAIL					(0)												/* Rx Fail Data : P_LMTSET				 */
#define EVCOM_PWSPPURQ_FAIL					(0)												/* Rx Fail Data : PWSPPURQ				 */
#define EVCOM_EV_SLCT_FAIL					(0)												/* Rx Fail Data : EV_SLCT				 */
#define EVCOM_HV_SLCT_FAIL					(0)												/* Rx Fail Data : HV_SLCT				 */

#define EVCOM_PLGTMSW_FAIL					(0)												/* Rx Fail Data : PLGTMSW				 */
#define EVCOM_P_NCDSP_FAIL					(0)												/* Rx Fail Data : P_NCDSP				 */
#define EVCOM_P_TMPID_FAIL					(0x3F)											/* Rx Fail Data : P_TMPID				 */
#define EVCOM_P_TMPTYP_FAIL					(0)												/* Rx Fail Data : P_TMPTYP				 */
#define EVCOM_P_TMPACD_FAIL					(0)												/* Rx Fail Data : P_TMPACD				 */
#define EVCOM_P_TMPACN_FAIL					(0)												/* Rx Fail Data : P_TMPACN				 */
#define EVCOM_P_TMPSTM_FAIL					(0x01FF)										/* Rx Fail Data : P_TMPSTM				 */
#define EVCOM_P_TMPFTM_FAIL					(0x01FF)										/* Rx Fail Data : P_TMPFTM				 */
#define EVCOM_P_TMPSWK_FAIL					(0)												/* Rx Fail Data : P_TMPSWK				 */
#define EVCOM_P_TMPNWK_FAIL					(0)												/* Rx Fail Data : P_TMPNWK				 */

#define EVCOM_P_CURDSP_APLY					(1)												/* P_CURDSP : Disp Apply				 */
#define EVCOM_P_CURDSP_GRAY					(0)												/* P_CURDSP : Disp Grayout				 */

#define EVCOM_CBLC_AVA_APLY					(1)												/* CBLC_AVA : Disp Apply				 */
#define EVCOM_CBLC_AVA_NOAPLY				(0)												/* CBLC_AVA : Disp No-Apply				 */

#define EVCOM_P_LMTDSP_APLY					(1)												/* P_LMTDSP : Disp Apply				 */
#define EVCOM_P_LMTDSP_NOAPLY				(0)												/* P_LMTDSP : Disp No-Apply				 */

#define EVCOM_P_CURSEL_16A_ON				(1)												/* P_CURSEL : 16A Disp Apply			 */
#define EVCOM_P_CURSEL_16A_OFF				(0)												/* P_CURSEL : 16A Disp No-Apply			 */

#define EVCOM_PWSPLAVA_APLY					(2)												/* PWSPLAVA : Disp Apply				 */
#define EVCOM_PWSPLAVA_GRAY					(1)												/* PWSPLAVA : Disp Grayout				 */

#define EVCOM_PWSPPURQ_NOREQ				(0)												/* PWSPPURQ : Disp Apply				 */
#define EVCOM_PWSPPURQ_REQ					(1)												/* PWSPPURQ : Disp Grayout				 */

#define EVCOM_EV_SLCT_APLY					(1)												/* EV_SLCT : Disp Apply					 */
#define EVCOM_EV_SLCT_GRAY					(0)												/* EV_SLCT : Disp Grayout				 */

#define EVCOM_HV_SLCT_APLY					(1)												/* BV_SLCT : Disp Apply					 */
#define EVCOM_HV_SLCT_GRAY					(0)												/* BV_SLCT : Disp Grayout				 */

#define EVCOM_P_NCTYP_START					(1)												/* P_NCTYP : Start						 */
#define EVCOM_P_NCTYP_FIN_AC_OFF			(2)												/* P_NCTYP : Fin & Air-Conditioner OFF	 */
#define EVCOM_P_NCTYP_FIN_AC_ON				(3)												/* P_NCTYP : Fin & Air-Conditioner ON	 */

#define EVCOM_P_ADDDSP_APLY					(0)												/* P_ADDDSP : Disp Apply				 */
#define EVCOM_P_ADDDSP_GRAY					(1)												/* P_ADDDSP : Disp Grayout				 */

#define EVCOM_PCNOWDSP_OFF_APLY				(0)												/* PCNOWDSP : Disp OFF Apply			 */
#define EVCOM_PCNOWDSP_ON_APLY				(1)												/* PCNOWDSP : Disp ON Apply				 */
#define EVCOM_PCNOWDSP_UNDEF				(2)												/* PCNOWDSP : Disp undefinition			 */
#define EVCOM_PCNOWDSP_GRAY					(3)												/* PCNOWDSP : Disp Grayout				 */

#define EVCOM_PLGTMSW_NOREQ					(0)												/* PLGTMSW : No Request					 */
#define EVCOM_PLGTMSW_REQ					(1)												/* PLGTMSW : Request					 */

#define EVCOM_P_TMPID_NEXT					(0x3D)											/* P_TMPID : Next Setting				 */

#define EVCOM_P_TMPTYP_START				(1)												/* P_TMPTYP : Start						 */
#define EVCOM_P_TMPTYP_FINISH				(2)												/* P_TMPTYP : Finish					 */

#define EVCOM_P_TMPACD_NOREQ				(0)												/* P_TMPACD : No Request				 */
#define EVCOM_P_TMPACD_REQ					(1)												/* P_TMPACD : Request					 */

#define EVCOM_P_TMPACN_OFF					(1)												/* P_TMPACN : Air-Conditioner ON		 */
#define EVCOM_P_TMPACN_ON					(2)												/* P_TMPACN : Air-Conditioner OFF		 */

#define EVCOM_TIME_LSB						(5)												/* TIME LSB : 5 (minutes)				 */
#define EVCOM_MIN_TO_HOUR					(60)											/* Minutes to Hour						 */
#define EVCOM_AM_HOUR_MAX					(11)											/* AM hour Max							 */
#define EVCOM_HOUR_12H						(12)											/* Hour 12H								 */
#define EVCOM_HOUR_UPDN_VAL					(1)												/* Hour UP/DOWN Value					 */
#define EVCOM_MIN_UPDN_VAL					(5)												/* Minute UP/DOWN Value					 */
#define EVCOM_HOUR_MAX						(23)											/* Hour Max								 */
#define EVCOM_HOUR_MOD						(EVCOM_HOUR_MAX + 1)							/* Hour Mod Value						 */
#define EVCOM_MIN_MAX						(59)											/* Minute Max							 */
#define EVCOM_MIN_MOD						(EVCOM_MIN_MAX + 1)								/* Minute Mod Value						 */


#define EVCOM_TMCHG_LINK_SIZE				(16)											/* Schedule Data (include header)		 */
#define vd_EVCOM_MEMFILL_U1(b,v,l)			(vd_g_MemfillU1(b,v,l))							/* Init Array							 */
#define EVCOM_TMCHG_POS_OFST				(1)												/* Counter to position offset			 */
#define EVCOM_TMCHG_POS_ERROR				(0)												/* Schedule Data Position Error			 */
#define EVCOM_TMCHG_POS_FIRST				(1)												/* Schedule Data Position First			 */
#define EVCOM_TMCHG_POS_MAX					(15)											/* Schedule Data Position Max			 */

#define EVCOM_P_SETON_OFF					(0)												/* P_SETON : OFF						 */
#define EVCOM_P_SETON_ON					(1)												/* P_SETON : ON							 */

/* Backup RAM -----------------------------------------------------------------------------------------------------------------------*/
#define u1_EVCOM_BR_U1(id,x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((id), (x)))*/							/* Read : U1 Signal		 */
#define u1_EVCOM_BR_U2(id,x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU2withStatus((id), (x)))*/							/* Read : U2 Signal		 */
#define u1_EVCOM_BR_P_CURDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_CURDSP, (x)))*/	/* Read : P_CURDSP		 */
#define u1_EVCOM_BR_P_CUR200(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_CUR200, (x)))*/	/* Read : P_CUR200		 */
#define u1_EVCOM_BR_P_CURSEL(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_CURSEL, (x)))*/	/* Read : P_CURSEL		 */
#define u1_EVCOM_BR_CBLC_AVA(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_CBLC_AVA, (x)))*/	/* Read : CBLC_AVA		 */
#define u1_EVCOM_BR_CBLOCKSU(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_CBLOCKSU, (x)))*/	/* Read : CBLOCKSU		 */
#define u1_EVCOM_BR_P_LMTDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_LMTDSP, (x)))*/	/* Read : P_LMTDSP		 */
#define u1_EVCOM_BR_P_LMTSET(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_LMTSET, (x)))*/	/* Read : P_LMTSET		 */
#define u1_EVCOM_BR_PWSPLAVA(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_PWSPLAVA, (x)))*/	/* Read : PWSPLAVA		 */
#define u1_EVCOM_BR_PWSPPURQ(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_PWSPPURQ, (x)))*/	/* Read : PWSPPURQ		 */
#define u1_EVCOM_BR_EV_SLCT(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_EV_SLCT, (x)))*/	/* Read : EV_SLCT		 */
#define u1_EVCOM_BR_HV_SLCT(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_HV_SLCT, (x)))*/	/* Read : HV_SLCT		 */
#define u1_EVCOM_BR_P_NCTYP(x)				(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_NCTYP, (x)))	/* Read : P_NCTYP		 */
#define u1_EVCOM_BR_P_NCWKD(x)				(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_NCWKD, (x)))	/* Read : P_NCWKD		 */
#define u1_EVCOM_BR_P_NCSTM(x)				(u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_EVCOM_P_NCSTM, (x)))	/* Read : P_NCSTM		 */
#define u1_EVCOM_BR_P_NCFTM(x)				(u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_EVCOM_P_NCFTM, (x)))	/* Read : P_NCFTM		 */
#define u1_EVCOM_BR_P_ADDDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_ADDDSP, (x)))*/	/* Read : P_ADDDSP		 */
#define u1_EVCOM_BR_PCNOWDSP(x)				(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_PCNOWDSP, (x)))	/* Read : PCNOWDSP		 */
#define u1_EVCOM_BR_PLGTMSW(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_PLGTMSW, (x)))*/	/* Read : PLGTMSW		 */
#define u1_EVCOM_BR_P_NCDSP(x)				(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_NCDSP, (x)))	/* Read : P_NCDSP		 */
#define u1_EVCOM_BR_P_TMPID(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPID, (x)))*/	/* Read : P_TMPID		 */
#define u1_EVCOM_BR_P_TMPTYP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPTYP, (x)))*/	/* Read : P_TMPTYP		 */
#define u1_EVCOM_BR_P_TMPACD(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPACD, (x)))*/	/* Read : P_TMPACD		 */
#define u1_EVCOM_BR_P_TMPACN(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPACN, (x)))*/	/* Read : P_TMPACN		 */
#define u1_EVCOM_BR_P_TMPSTM(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_EVCOM_P_TMPSTM, (x)))*/	/* Read : P_TMPSTM		 */
#define u1_EVCOM_BR_P_TMPFTM(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_EVCOM_P_TMPFTM, (x)))*/	/* Read : P_TMPFTM		 */
#define u1_EVCOM_BR_P_TMPSWK(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPSWK, (x)))*/	/* Read : P_TMPSWK		 */
#define u1_EVCOM_BR_P_TMPNWK(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_EVCOM_P_TMPNWK, (x)))*/	/* Read : P_TMPNWK		 */

#define u1_EVCOM_BW_U1(id,x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((id), (x)))*/							/* Write : U1 Signal	 */
#define u1_EVCOM_BW_U2(id,x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU2withStatus((id), (x)))*/							/* Write : U2 Signal	 */
#define u1_EVCOM_BW_P_CURDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_CURDSP, (x)))*/	/* Write : P_CURDSP		 */
#define u1_EVCOM_BW_P_CUR200(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_CUR200, (x)))*/	/* Write : P_CUR200		 */
#define u1_EVCOM_BW_P_CURSEL(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_CURSEL, (x)))*/	/* Write : P_CURSEL		 */
#define u1_EVCOM_BW_CBLC_AVA(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_CBLC_AVA, (x)))*/	/* Write : CBLC_AVA		 */
#define u1_EVCOM_BW_CBLOCKSU(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_CBLOCKSU, (x)))*/	/* Write : CBLOCKSU		 */
#define u1_EVCOM_BW_P_LMTDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_LMTDSP, (x)))*/	/* Write : P_LMTDSP		 */
#define u1_EVCOM_BW_P_LMTSET(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_LMTSET, (x)))*/	/* Write : P_LMTSET		 */
#define u1_EVCOM_BW_PWSPLAVA(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_PWSPLAVA, (x)))*/	/* Write : PWSPLAVA		 */
#define u1_EVCOM_BW_PWSPPURQ(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_PWSPPURQ, (x)))*/	/* Write : PWSPPURQ		 */
#define u1_EVCOM_BW_EV_SLCT(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_EV_SLCT, (x)))*/	/* Write : EV_SLCT		 */
#define u1_EVCOM_BW_HV_SLCT(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_HV_SLCT, (x)))*/	/* Write : HV_SLCT		 */
#define u1_EVCOM_BW_P_NCTYP(x)				(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_NCTYP, (x)))	/* Write : P_NCTYP		 */
#define u1_EVCOM_BW_P_NCWKD(x)				(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_NCWKD, (x)))	/* Write : P_NCWKD		 */
#define u1_EVCOM_BW_P_NCSTM(x)				(u1_g_Rim_WriteU2withStatus((U2)RIMID_U2_EVCOM_P_NCSTM, (x)))	/* Write : P_NCSTM		 */
#define u1_EVCOM_BW_P_NCFTM(x)				(u1_g_Rim_WriteU2withStatus((U2)RIMID_U2_EVCOM_P_NCFTM, (x)))	/* Write : P_NCFTM		 */
#define u1_EVCOM_BW_P_ADDDSP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_ADDDSP, (x)))*/	/* Write : P_ADDDSP		 */
#define u1_EVCOM_BW_PCNOWDSP(x)				(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_PCNOWDSP, (x)))	/* Write : PCNOWDSP		 */
#define u1_EVCOM_BW_PLGTMSW(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_PLGTMSW, (x)))*/	/* Write : PLGTMSW		 */
#define u1_EVCOM_BW_P_NCDSP(x)				(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_NCDSP, (x)))	/* Write : P_NCDSP		 */
#define u1_EVCOM_BW_P_TMPID(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPID, (x)))*/	/* Write : P_TMPID		 */
#define u1_EVCOM_BW_P_TMPTYP(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPTYP, (x)))*/	/* Write : P_TMPTYP		 */
#define u1_EVCOM_BW_P_TMPACD(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPACD, (x)))*/	/* Write : P_TMPACD		 */
#define u1_EVCOM_BW_P_TMPACN(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPACN, (x)))*/	/* Write : P_TMPACN		 */
#define u1_EVCOM_BW_P_TMPSTM(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU2withStatus((U2)RIMID_U2_EVCOM_P_TMPSTM, (x)))*/	/* Write : P_TMPSTM		 */
#define u1_EVCOM_BW_P_TMPFTM(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU2withStatus((U2)RIMID_U2_EVCOM_P_TMPFTM, (x)))*/	/* Write : P_TMPFTM		 */
#define u1_EVCOM_BW_P_TMPSWK(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPSWK, (x))) */	/* Write : P_TMPSWK		 */
#define u1_EVCOM_BW_P_TMPNWK(x)				((U1)RIM_RESULT_NG)/*(u1_g_Rim_WriteU1withStatus((U2)RIMID_U1_EVCOM_P_TMPNWK, (x))) */	/* Write : P_TMPNWK		 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVCOM_NXT_CHGTYPE_SIG_NUM			(4)									/* Next : Number of Charge Type						 */
static const U1 u1_s_EVCOM_NXT_CHGTYPE_SIG2DSP[EVCOM_NXT_CHGTYPE_SIG_NUM] = {
	(U1)EVCOM_CHG_TYPE_BLANK,
	(U1)EVCOM_CHG_TYPE_START,
	(U1)EVCOM_CHG_TYPE_FIN_AC_OFF,
	(U1)EVCOM_CHG_TYPE_FIN_AC_ON
};

#define EVCOM_NXT_WKD_SIG_NUM				(8)									/* Next : Number of Weekday							 */
static const U1 u1_s_EVCOM_NXT_WKD_SIG2DSP[EVCOM_NXT_WKD_SIG_NUM] = {
	(U1)EVCOM_WKD_BLANK,
	(U1)EVCOM_WKD_MON,
	(U1)EVCOM_WKD_TUE,
	(U1)EVCOM_WKD_WED,
	(U1)EVCOM_WKD_THU,
	(U1)EVCOM_WKD_FRI,
	(U1)EVCOM_WKD_SAT,
	(U1)EVCOM_WKD_SUN
};

#define EVCOM_TMP_WKD_SIG_NUM				(8)									/* Temp : Number of Weekday							 */
static const U1 u1_s_EVCOM_TMP_WKD_SIG2DSP[EVCOM_TMP_WKD_SIG_NUM] = {
	(U1)EVCOM_WKD_BLANK,
	(U1)EVCOM_WKD_MON,
	(U1)EVCOM_WKD_TUE,
	(U1)EVCOM_WKD_WED,
	(U1)EVCOM_WKD_THU,
	(U1)EVCOM_WKD_FRI,
	(U1)EVCOM_WKD_SAT,
	(U1)EVCOM_WKD_SUN
};

#define EVCOM_SET_CHGTYPE_SIG_NUM			(4)									/* Set : Number of Charge Type						 */
static const U1 u1_s_EVCOM_SET_CHGTYPE_SIG2DSP[EVCOM_SET_CHGTYPE_SIG_NUM] = {
	(U1)EVCOM_CHG_TYPE_BLANK,
	(U1)EVCOM_CHG_TYPE_START,
	(U1)EVCOM_CHG_TYPE_FIN_AC_OFF,
	(U1)EVCOM_CHG_TYPE_FIN_AC_ON
};

static const U4 u4_s_EVCOM_TMSCHD_SUPBIT[EVCOM_TMCHG_LINK_SIZE] = {
	(U4)0,																		/* Header											 */
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_15 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_14 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_13 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_12 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_11 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_10 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_09 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_08 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_07 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_06 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_05 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_04 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_03 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_02 *This parameter is used only by Tm-2. */,
	(U4)0/*DSPTIMCHG_SUPBITCHGSCHED_01 *This parameter is used only by Tm-2. */
};

#define EVCOM_SHG_CUR_2BIT_MAX				(3)
#define EVCOM_CHG_CUR_P_CURDSP_SHIFT		(1)
#define EVCOM_CHG_CUR_P_CUR200_SHIFT		(2)
#define EVCOM_CHG_CUR_DSP_NO_FAIL			(10)
#define EVCOM_CHG_CUR_DSP_NO_NUM			(16)
static const U1 u1_s_EVCOM_CHG_CUR_DSP_NO_JDG[EVCOM_CHG_CUR_DSP_NO_NUM] = {
	(U1)2,
	(U1)7,
	(U1)0,
	(U1)4,
	(U1)3,
	(U1)9,
	(U1)1,
	(U1)6,
	(U1)10,
	(U1)8,
	(U1)10,
	(U1)5,
	(U1)10,
	(U1)10,
	(U1)10,
	(U1)10
};

#define EVCOM_CHG_CUR_DSP_STS_NUM			(11)								/* Charge Current Setting Display Parttern			 */
static const ST_EVCOM_CHGCUR_DSP st_s_EVCOM_CHG_CUR_DSP_STS[EVCOM_CHG_CUR_DSP_STS_NUM] = {
	/*   MAX						16A						8A */
	{(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_NOAPLY,	(U1)EVCOM_DSP_APLY		},		/* Charge Current Setting : No.1			 */
	{(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_NOAPLY,	(U1)EVCOM_DSP_APLY		},		/* Charge Current Setting : No.2			 */
	{(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_NOAPLY,	(U1)EVCOM_DSP_APLYGRAY	},		/* Charge Current Setting : No.3			 */
	{(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_NOAPLY,	(U1)EVCOM_DSP_APLYGRAY	},		/* Charge Current Setting : No.4			 */
	{(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY		},		/* Charge Current Setting : No.5			 */
	{(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY		},		/* Charge Current Setting : No.6			 */
	{(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY,		(U1)EVCOM_DSP_APLY		},		/* Charge Current Setting : No.7			 */
	{(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY	},		/* Charge Current Setting : No.8			 */
	{(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY	},		/* Charge Current Setting : No.9			 */
	{(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY,	(U1)EVCOM_DSP_APLYGRAY	},		/* Charge Current Setting : No.10			 */
	{(U1)EVCOM_DSP_NOAPLY,		(U1)EVCOM_DSP_NOAPLY,	(U1)EVCOM_DSP_NOAPLY	}		/* Charge Current Setting : No.11 (Fail)	 */
};

/* Backup RAM -----------------------------------------------------------------------------------------------------------------------*/
static const U2 u2_s_EVCOM_RIMID_P_SETID[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETID_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETON[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETON_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETTYP[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETTYP_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETSTM[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETSTM_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETFTM[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U2_EVCOM_P_SETFTM_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETWKD[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETWKD_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

static const U2 u2_s_EVCOM_RIMID_P_SETNXT[EVCOM_TMCHG_LINK_SIZE] = {
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_00 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_01 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_02 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_03 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_04 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_05 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_06 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_07 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_08 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_09 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_10 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_11 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_12 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_13 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_14 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */,
	(U2)0xFFFF/*RIMID_U1_EVCOM_P_SETNXT_15 *If activate u1_EVCOM_B[RW]_U[12], configure this paramter to right value. */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  extern declaration                                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* EVCOM_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  evcom.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
