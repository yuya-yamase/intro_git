/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  EV Communication Control                                                                                                         */
/*===================================================================================================================================*/

#ifndef EVCOM_H
#define EVCOM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVCOM_H_MAJOR						(1)
#define EVCOM_H_MINOR						(3)
#define EVCOM_H_PATCH						(0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Data Buffer ----------------------------------------------------------------------------------------------------------------------*/
typedef struct {
	U1 u1_id;				/* Signal Data : P_SETID		 */
	U1 u1_onoff;			/* Signal Data : P_SETON		 */
	U1 u1_type;				/* Signal Data : P_SETTYP		 */
	U2 u2_start_tim;		/* Signal Data : P_SETSTM		 */
	U2 u2_finish_tim;		/* Signal Data : P_SETFTM		 */
	U1 u1_wkd_bit;			/* Signal Data : P_SETWKD		 */
	U1 u1_nxt_id;			/* Signal Data : P_SETNXT		 */
}ST_EVCOM_TMCHG_SET;

typedef struct {
	U1 u1_id;				/* Signal Data : P_TMPID		 */
	U1 u1_type;				/* Signal Data : P_TMPTYP		 */
	U1 u1_acd;				/* Signal Data : P_TMPAND		 */
	U1 u1_acn;				/* Signal Data : P_TMPAND		 */
	U2 u2_stm;				/* Signal Data : P_TMPSTM		 */
	U2 u2_ftm;				/* Signal Data : P_TMPFTM		 */
	U1 u1_swk;				/* Signal Data : P_TMPSWK		 */
	U1 u1_nwk;				/* Signal Data : P_TMPNWK		 */
}ST_EVCOM_TMCHG_TMP;

typedef struct {
	U1 u1_type;				/* Signal Data : P_NCTYP		 */
	U1 u1_wkd;				/* Signal Data : P_NCWKD		 */
	U2 u2_stm;				/* Signal Data : P_NCSTM		 */
	U2 u2_ftm;				/* Signal Data : P_NCFTM		 */
	U1 u1_dsp;				/* Signal Data : P_NCDSP		 */
}ST_EVCOM_TMCHG_NXT;

/* Disp Contents --------------------------------------------------------------------------------------------------------------------*/
typedef struct {
	U1 u1_onoff;			/* Schedule : ON/OFF			 */
	U1 u1_chg_type;			/* Schedule : Charge Type		 */
	U1 u1_hour;				/* Schedule : Hour				 */
	U1 u1_min;				/* Schedule : Minute			 */
	U1 u1_ampm;				/* Scheduel : AM/PM				 */
	U1 u1_wkd_bit;			/* Schedule : Weekday(bit)		 */
}ST_EVCOM_TMCHG_DSP_SET;

typedef struct {
	U1 u1_chg_type;			/* Temp : Charge Type			 */
	U1 u1_hour;				/* Temp : Hour					 */
	U1 u1_min;				/* Temp : Minute				 */
	U1 u1_ampm;				/* Temp : AM/PM					 */
	U1 u1_wkd;				/* Temp : Weekday				 */
	U1 u1_wkd_bit;			/* Temp : Weekday(bit)			 */
}ST_EVCOM_TMCHG_DSP_TMP;

typedef struct {
	U1 u1_chg_type;			/* Next Charge : Charge Type	 */
	U1 u1_hour;				/* Next Charge : Hour			 */
	U1 u1_min;				/* Next Charge : Minute			 */
	U1 u1_ampm;				/* Next Charge : AM/PM			 */
	U1 u1_wkd;				/* Next Charge : Weekday		 */
}ST_EVCOM_TMCHG_DSP_NXT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Disp state */
#define EVCOM_DSP_NOAPLY					(0)									/* No-Apply											 */
#define EVCOM_DSP_APLY						(1)									/* Apply											 */
#define EVCOM_DSP_APLYGRAY					(2)									/* Apply & Grayout									 */

#define EVCOM_CNTT_CHGSET					(0)									/* Charge Current Setting							 */
#define EVCOM_CNTT_CONLK					(1)									/* Connector Lock Setting							 */
#define EVCOM_CNTT_CHGLMT					(2)									/* Charge Limit Setting								 */
#define EVCOM_CNTT_CHGSET_MAX				(3)									/* Charge Current Setting - MAX						 */
#define EVCOM_CNTT_CHGSET_16A				(4)									/* Charge Current Setting - 16A						 */
#define EVCOM_CNTT_CHGSET_8A				(5)									/* Charge Current Setting - 8A						 */
#define EVCOM_CNTT_CONLK_MNLLK				(6)									/* Connector Lock Settign - Manual Lock				 */
#define EVCOM_CNTT_CONLK_ATLK				(7)									/* Connector Lock Settign - Auto Lock				 */
#define EVCOM_CNTT_CONLK_ATLKULK			(8)									/* Connector Lock Settign - Auto Lock & Unlock		 */
#define EVCOM_CNTT_CHGLMT_FULL				(9)									/* Charge Limit Setting - Full						 */
#define EVCOM_CNTT_CHGLMT_90P				(10)								/* Charge Limit Setting - 90%						 */
#define EVCOM_CNTT_EXSPLY					(11)								/* External Supply									 */
#define EVCOM_CNTT_EXSPLY_EV				(12)								/* External Supply - EV Supply						 */
#define EVCOM_CNTT_EXSPLY_HV				(13)								/* External Supply - HV Supply						 */
#define EVCOM_CNTT_TMSCHD_ADD				(14)								/* Time Schedule - Add								 */
#define EVCOM_CNTT_TMSCHD_NXT				(15)								/* Time Schedule - Next Charge						 */
#define EVCOM_CNTT_NUM						(16)								/* Contents Num										 */

/* Disp Definition ------------------------------------------------------------------------------------------------------------------*/
/* Charge Now Button Disp State */
#define EVCOM_DSP_CHG_NOW_APLY				(0)									/* Charge Now : Apply								 */
#define EVCOM_DSP_CHG_NOW_APLYGRAY			(1)									/* Charge Now : Apply & Grayout						 */

/* Charge Schecule ON/OFF */
#define EVCOM_SCHD_OFF						(0)									/* OFF												 */
#define EVCOM_SCHD_ON						(1)									/* ON												 */

/* Charge Type */
#define EVCOM_CHG_TYPE_BLANK				(0)									/* Blank											 */
#define EVCOM_CHG_TYPE_START				(1)									/* Start											 */
#define EVCOM_CHG_TYPE_FIN_AC_OFF			(2)									/* Finish & Air-Conditioner OFF						 */
#define EVCOM_CHG_TYPE_FIN_AC_ON			(3)									/* Finish & Air-Conditioner ON						 */

/* AM/PM */
#define EVCOM_AMPM_NON						(0)									/* No Display										 */
#define EVCOM_AMPM_AM						(1)									/* AM												 */
#define EVCOM_AMPM_PM						(2)									/* PM												 */

/* Weekday */
#define EVCOM_WKD_BLANK						(0)									/* No Diaplay										 */
#define EVCOM_WKD_MON						(1)									/* Monday											 */
#define EVCOM_WKD_TUE						(2)									/* Tuesday											 */
#define EVCOM_WKD_WED						(3)									/* Wednesday										 */
#define EVCOM_WKD_THU						(4)									/* Thursday											 */
#define EVCOM_WKD_FRI						(5)									/* Friday											 */
#define EVCOM_WKD_SAT						(6)									/* Saturday											 */
#define EVCOM_WKD_SUN						(7)									/* Sunday											 */

/* Weekday (bit data) */
#define EVCOM_WKD_BIT_MON					(0x01)								/* Monday											 */
#define EVCOM_WKD_BIT_TUE					(0x02)								/* Tuesday											 */
#define EVCOM_WKD_BIT_WED					(0x04)								/* Wednesday										 */
#define EVCOM_WKD_BIT_THU					(0x08)								/* Thursday											 */
#define EVCOM_WKD_BIT_FRI					(0x10)								/* Friday											 */
#define EVCOM_WKD_BIT_SAT					(0x20)								/* Saturday											 */
#define EVCOM_WKD_BIT_SUN					(0x40)								/* Sunday											 */

/* Transition Definition ------------------------------------------------------------------------------------------------------------*/
/* Charge Schedule Initial Select Content */
#define EVCOM_TMCHG_SCHD_01					(0)									/* Select : Charge Schedule Content 01				 */
#define EVCOM_TMCHG_SCHD_02					(1)									/* Select : Charge Schedule Content 02				 */
#define EVCOM_TMCHG_SCHD_03					(2)									/* Select : Charge Schedule Content 03				 */
#define EVCOM_TMCHG_SCHD_04					(3)									/* Select : Charge Schedule Content 04				 */
#define EVCOM_TMCHG_SCHD_05					(4)									/* Select : Charge Schedule Content 05				 */
#define EVCOM_TMCHG_SCHD_06					(5)									/* Select : Charge Schedule Content 06				 */
#define EVCOM_TMCHG_SCHD_07					(6)									/* Select : Charge Schedule Content 07				 */
#define EVCOM_TMCHG_SCHD_08					(7)									/* Select : Charge Schedule Content 08				 */
#define EVCOM_TMCHG_SCHD_09					(8)									/* Select : Charge Schedule Content 09				 */
#define EVCOM_TMCHG_SCHD_10					(9)									/* Select : Charge Schedule Content 10				 */
#define EVCOM_TMCHG_SCHD_11					(10)								/* Select : Charge Schedule Content 11				 */
#define EVCOM_TMCHG_SCHD_12					(11)								/* Select : Charge Schedule Content 12				 */
#define EVCOM_TMCHG_SCHD_13					(12)								/* Select : Charge Schedule Content 13				 */
#define EVCOM_TMCHG_SCHD_14					(13)								/* Select : Charge Schedule Content 14				 */
#define EVCOM_TMCHG_SCHD_15					(14)								/* Select : Charge Schedule Content 15				 */
#define EVCOM_TMCHG_SCHD_ADD				(15)								/* Select : Charge Schedule Content Add				 */

/* Air-Conditioner Initial Select Content */
#define EVCOM_TMCHG_ACD_YES					(0)									/* Select : Yes										 */
#define EVCOM_TMCHG_ACD_NO					(1)									/* Select : No										 */

/* Schedule Data ID */
#define EVCOM_TMCHG_ID_INIT					(EVCOM_P_SETID_INIT)							/* Schedule Data ID Initial				 */
#define EVCOM_TMCHG_ID_HEAD					(0)												/* Schedule Data ID Header				 */
#define EVCOM_TMCHG_ID_01					(1)												/* Schedule Data ID 01					 */
#define EVCOM_TMCHG_ID_02					(2)												/* Schedule Data ID 02					 */
#define EVCOM_TMCHG_ID_03					(3)												/* Schedule Data ID 03					 */
#define EVCOM_TMCHG_ID_04					(4)												/* Schedule Data ID 04					 */
#define EVCOM_TMCHG_ID_05					(5)												/* Schedule Data ID 05					 */
#define EVCOM_TMCHG_ID_06					(6)												/* Schedule Data ID 09					 */
#define EVCOM_TMCHG_ID_07					(7)												/* Schedule Data ID 07					 */
#define EVCOM_TMCHG_ID_08					(8)												/* Schedule Data ID 08					 */
#define EVCOM_TMCHG_ID_09					(9)												/* Schedule Data ID 09					 */
#define EVCOM_TMCHG_ID_10					(10)											/* Schedule Data ID 10					 */
#define EVCOM_TMCHG_ID_11					(11)											/* Schedule Data ID 11					 */
#define EVCOM_TMCHG_ID_12					(12)											/* Schedule Data ID 12					 */
#define EVCOM_TMCHG_ID_13					(13)											/* Schedule Data ID 13					 */
#define EVCOM_TMCHG_ID_14					(14)											/* Schedule Data ID 14					 */
#define EVCOM_TMCHG_ID_15					(15)											/* Schedule Data ID 15					 */
#define EVCOM_TMCHG_ID_END					(0x3F)											/* Schedule Data ID Termination			 */

/* Schedule Data Cntents */
#define EVCOM_TMCHG_CNTT_01					(0)												/* Schedule Data Contents 01			 */
#define EVCOM_TMCHG_CNTT_02					(1)												/* Schedule Data Contents 02			 */
#define EVCOM_TMCHG_CNTT_03					(2)												/* Schedule Data Contents 03			 */
#define EVCOM_TMCHG_CNTT_04					(3)												/* Schedule Data Contents 04			 */
#define EVCOM_TMCHG_CNTT_05					(4)												/* Schedule Data Contents 05			 */
#define EVCOM_TMCHG_CNTT_06					(5)												/* Schedule Data Contents 06			 */
#define EVCOM_TMCHG_CNTT_07					(6)												/* Schedule Data Contents 07			 */
#define EVCOM_TMCHG_CNTT_08					(7)												/* Schedule Data Contents 08			 */
#define EVCOM_TMCHG_CNTT_09					(8)												/* Schedule Data Contents 09			 */
#define EVCOM_TMCHG_CNTT_10					(9)												/* Schedule Data Contents 10			 */
#define EVCOM_TMCHG_CNTT_11					(10)											/* Schedule Data Contents 11			 */
#define EVCOM_TMCHG_CNTT_12					(11)											/* Schedule Data Contents 12			 */
#define EVCOM_TMCHG_CNTT_13					(12)											/* Schedule Data Contents 13			 */
#define EVCOM_TMCHG_CNTT_14					(13)											/* Schedule Data Contents 14			 */
#define EVCOM_TMCHG_CNTT_15					(14)											/* Schedule Data Contents 15			 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void vd_g_EvcomBonInit(void);													/* B-ON Initial										 */
void vd_g_EvcomWkupInit(void);													/* Wakeup/Reset Initial								 */
void vd_g_EvcomRoutine(void);													/* Periodic Task									 */

/* Receive Signal */
U1   u1_g_EvcomGetPLG1S01MsgSts(void);											/* Message Status : PLG1S01							 */
U1   u1_g_EvcomGetChgNowMsgSts(void);											/* Message Status : Charge Now						 */
U1   u1_g_EvcomGetCur200(void);													/* Signal Data : P_CUR200							 */
U1   u1_g_EvcomGetCBlockSu(void);												/* Signal Data : CBLOCKSU							 */
U1   u1_g_EvcomGetLmtSet(void);													/* Signal Data : P_LMTSET							 */
U1   u1_g_EvcomGetPwSplAva(void);												/* Signal Data : PWSPLAVA							 */
U1   u1_g_EvcomGetCNowDsp(void);												/* Signal Data : PCNOWDSP							 */
U1   u1_g_EvcomGetTmpData(void);												/* Signal Data : P_TMPID							 */
U1   u1_g_EvcomGetNcTyp(void);													/* Signal Data : P_NCTYP							 */
U1   u1_g_EvcomGetNcDsp(void);													/* Signal Data : P_NCDSP							 */

/* Data Buffer */
ST_EVCOM_TMCHG_TMP st_g_EvcomGetTmpWrkData(void);								/* Get Receive Data "TMP_WORK"						 */

/* Disp state */
U1   u1_g_EvcomGetCnttSts(const U1 u1_a_cntt);									/* Appointed Content								 */
U1   u1_g_EvcomAcDcChaChgSetDspSts(void);										/* Charge Current Setting							 */
U1   u1_g_EvcomAcDcChaConLkDspSts(void);										/* Connector Lock Setting							 */
U1   u1_g_EvcomAcDcChaChgLmtDspSts(void);										/* Charge Limit Setting								 */
U1   u1_g_EvcomAcDcChaMaxDspSts(void);											/* Charge Current Setting - MAX						 */
U1   u1_g_EvcomAcDcCha16ADspSts(void);											/* Charge Current Setting - 16A						 */
U1   u1_g_EvcomAcDcCha8ADspSts(void);											/* Charge Current Setting - 8A						 */
U1   u1_g_EvcomAcDcChaMnlLkDspSts(void);										/* Connector Lock Settign - Manual Lock				 */
U1   u1_g_EvcomAcDcChaAtLkDspSts(void);											/* Connector Lock Settign - Auto Lock				 */
U1   u1_g_EvcomAcDcChaAtLkUlkDspSts(void);										/* Connector Lock Settign - Auto Lock & Unlock		 */
U1   u1_g_EvcomAcDcChaFullDspSts(void);											/* Charge Limit Setting - Full						 */
U1   u1_g_EvcomAcDcCha90pDspSts(void);											/* Charge Limit Setting - 90%						 */
U1   u1_g_EvcomAcDcSplyExSplyDspSts(void);										/* External Supply									 */
U1   u1_g_EvcomAcDcSplyEvSplyDspSts(void);										/* External Supply - EV Supply						 */
U1   u1_g_EvcomAcDcSplyHvSplyDspSts(void);										/* External Supply - HV Supply						 */
U1   u1_g_EvcomChgSchdAddDspSts(void);											/* Time Schedule - Add								 */
U1   u1_g_EvcomChgSchdNxtChgDspSts(void);										/* Time Schedule - Next Charge						 */

/* Disp Contents */
U1   u1_g_EvcomGetChgNowSts(void);												/* Charge Now Button Disp State						 */
ST_EVCOM_TMCHG_DSP_SET st_g_EvcomGetSetDspData(U1 u1_a_dsp_no);					/* Get Disp Contents - "SET"						 */
ST_EVCOM_TMCHG_DSP_TMP st_g_EvcomGetTmpDspData(void);							/* Get Disp Contents - "TMP"						 */
ST_EVCOM_TMCHG_DSP_TMP st_g_EvcomGetTmpWrkDspData(void);						/* Get Disp Contents - "TMP_WORK"					 */
ST_EVCOM_TMCHG_DSP_NXT st_g_EvcomGetNxtDspData(void);							/* Get Disp Contents - "NEXT"						 */

/* Transition */
U1   u1_g_EvcomGetChgSchdTransReq(void);										/* Get Charge Schedule Trans Request				 */
U1   u1_g_EvcomTmSetIsComp(void);												/* Time Setting Is Complete							 */
U1   u1_g_EvcomGetAcdDispReq(void);												/* Air-Conditioner Setting Request					 */
void vd_g_EvcomTmSetStart(void);												/* Time Setting Start Hook							 */
void vd_g_EvcomTmSetTypeUp(void);												/* Time Setting - Charge Type Up					 */
void vd_g_EvcomTmSetTypeDown(void);												/* Time Setting - Charge Type Down					 */
void vd_g_EvcomTmSetHourUp(void);												/* Time Setting - Hour Up							 */
void vd_g_EvcomTmSetHourDown(void);												/* Time Setting - Hour Down							 */
void vd_g_EvcomTmSetMinUp(void);												/* Time Setting - Minute Up							 */
void vd_g_EvcomTmSetMinDown(void);												/* Time Setting - Minute Down						 */
U1   u1_g_EvcomAcdSetInitSel(void);												/* Air-Conditioner Initial Select Content			 */
U1   u1_g_EvcomTmChgTransNxtSet(void);											/* Next Setting Trans Request						 */
U1   u1_g_EvcomGetExSplyTransReq(void);											/* Get External Supply Trans Request				 */
U4   u4_g_EvcomDispGetChgSchedSup(void);										/* Get Charge Schedule Support Bit					 */
U1   u1_g_EvcomChgSchdInitSel(void);											/* Charge Schedule Initial Select Content			 */
U1   u1_g_EvcomExistSchdData(const U1 u1_a_target_id);							/* Exist Schedule Data In List						 */
U1   u1_g_EvcomGetSchdDataIdByCntt(const U1 u1_a_cntt);							/* Get Schedule Data ID by Contents					 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* EVCOM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  evcom.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
