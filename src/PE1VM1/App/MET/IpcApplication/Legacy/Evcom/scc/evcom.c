/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  EV Communication Control                                                                                                         */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVCOM_C_MAJOR						(1)
#define EVCOM_C_MINOR						(3)
#define EVCOM_C_PATCH						(0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "evcom_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((EVCOM_C_MAJOR != EVCOM_H_MAJOR) ||\
	 (EVCOM_C_MINOR != EVCOM_H_MINOR) ||\
	 (EVCOM_C_PATCH != EVCOM_H_PATCH))
#error "source and header files are inconsistent!"
#endif

#if ((EVCOM_C_MAJOR != EVCOM_CFG_H_MAJOR) ||\
	 (EVCOM_C_MINOR != EVCOM_CFG_H_MINOR) ||\
	 (EVCOM_C_PATCH != EVCOM_CFG_H_PATCH))
#error "source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_evcom_ig_sts;													/* IG Status										 */
static U1 u1_s_evcom_msgsts_plg1s01;											/* Message Status : PLG1S01							 */
static U1 u1_s_evcom_msgsts_plg1g13;											/* Message Status : PLG1G13							 */
static U1 u1_s_evcom_pwsppurq_old;												/* Ex Supply : PWSPPURQ (Old)						 */
static U1 u1_s_evcom_plgtmsw_old;												/* Timer Charge : PLGTMSW (Old)						 */
static ST_EVCOM_TMCHG_TMP st_s_evcom_tmp_wrk;									/* Timer Charge : "TMP_WORK" Buffer					 */
static U1 u1_s_evcom_chg_cur_dsp_sts_no;										/* Charge Current Setting Display Pattern No.		 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 (* const fp_sp_TBL_EVCOM_DISP_STS[EVCOM_CNTT_NUM])(void) = {
	&u1_g_EvcomAcDcChaChgSetDspSts,												/* index : EVCOM_CNTT_CHGSET						 */
	&u1_g_EvcomAcDcChaConLkDspSts,												/* index : EVCOM_CNTT_CONLK							 */
	&u1_g_EvcomAcDcChaChgLmtDspSts,												/* index : EVCOM_CNTT_CHGLMT						 */
	&u1_g_EvcomAcDcChaMaxDspSts,												/* index : EVCOM_CNTT_CHGSET_MAX					 */
	&u1_g_EvcomAcDcCha16ADspSts,												/* index : EVCOM_CNTT_CHGSET_16A					 */
	&u1_g_EvcomAcDcCha8ADspSts,													/* index : EVCOM_CNTT_CHGSET_8A						 */
	&u1_g_EvcomAcDcChaMnlLkDspSts,												/* index : EVCOM_CNTT_CONLK_MNLLK					 */
	&u1_g_EvcomAcDcChaAtLkDspSts,												/* index : EVCOM_CNTT_CONLK_ATLK					 */
	&u1_g_EvcomAcDcChaAtLkUlkDspSts,											/* index : EVCOM_CNTT_CONLK_ATLKULK					 */
	&u1_g_EvcomAcDcChaFullDspSts,												/* index : EVCOM_CNTT_CHGLMT_FULL					 */
	&u1_g_EvcomAcDcCha90pDspSts,												/* index : EVCOM_CNTT_CHGLMT_90P					 */
	&u1_g_EvcomAcDcSplyExSplyDspSts,											/* index : EVCOM_CNTT_EXSPLY						 */
	&u1_g_EvcomAcDcSplyEvSplyDspSts,											/* index : EVCOM_CNTT_EXSPLY_EV						 */
	&u1_g_EvcomAcDcSplyHvSplyDspSts,											/* index : EVCOM_CNTT_EXSPLY_HV						 */
	&u1_g_EvcomChgSchdAddDspSts,												/* index : EVCOM_CNTT_TMSCHD_ADD					 */
	&u1_g_EvcomChgSchdNxtChgDspSts												/* index : EVCOM_CNTT_TMSCHD_NXT					 */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_EvcomBRamInit(void);											/* Backup RAM Initial								 */
static void vd_s_EvcomSRamInit(void);											/* Static RAM Initial								 */
static void vd_s_EvcomUpdateReceiveData(void);									/* Update : Receive Data							 */
static void vd_s_EvcomUpdateRxDataTmChgSet(void);								/* Update : Rx Data (Timer Charge "SET")			 */
static void vd_s_EvcomUpdateRxDataTmChgTmp(void);								/* Update : Rx Data (Timer Charge "TMP")			 */
static void vd_s_EvcomUpdateRxDataTmChgNxt(void);								/* Update : Rx Data (Timer Charge "NEXT")			 */
static ST_EVCOM_TMCHG_DSP_TMP st_s_EvcomMakeTmpDspData(const ST_EVCOM_TMCHG_TMP * st_a_tmp);	/* Make Disp Contents "TMP/TMP_WORK" */
static U1   u1_s_EvcomSigToHour24h(const U2 u2_a_time);							/* Get Disp Contents - Hour (24H format)			 */
static U1   u1_s_EvcomHour24hToDsp(const U1 u1_a_hour_24h);						/* Get Disp Contents - Hour (Disp format)			 */
static U1   u1_s_EvcomSigToMin(const U2 u2_a_time);								/* Get Disp Contents - Minutes						 */
static U1   u1_s_EvcomGetAmPm(const U1 u1_a_hour_24h);							/* Get Disp Contents - AM/PM						 */
static void vd_s_EvcomUpdateRxDataTmChgOthr(void);								/* Update : Rx Data (Timer Charge Other)			 */
static void vd_s_EvcomUpdateDspStsData(void);									/* Update : Display Status Data						 */
static U2   u2_s_EvcomMakeTimeSig(const U1 u1_a_hour, const U1 u1_a_min);		/* Make Time Signal									 */
static void vd_s_EvcomInitTmChgSchdData(void);									/* Initialize Schedule Data							 */
static U1   u1_s_EvcomGetSchdDataIdByPos(const U1 u1_a_pos);					/* Get Schedule Data ID by Position					 */
static U1   u1_s_EvcomGetSchdDataPosById(const U1 u1_a_target_id);				/* Get Schedule Data Position by ID					 */
static U1   u1_s_EvcomGetSchdDataNum(void);										/* Get Schedule Data Num							 */
static ST_EVCOM_TMCHG_SET st_s_EvcomGetSchdDataById(const U1 u1_a_id);			/* Get Schedule Data								 */
static U1   u1_s_EvcomChkSchdData(const U1 u1_a_id, const U1 * u1_ap_dupchk);	/* Schedule Data Check								 */

/*===================================================================================================================================*/
/* B-ON Initial                                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomBonInit(void)
{
	vd_s_EvcomBRamInit();
	vd_s_EvcomSRamInit();
}

/*===================================================================================================================================*/
/* Wakeup/Reset Initial                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomWkupInit(void)
{
	vd_s_EvcomSRamInit();
}

/*===================================================================================================================================*/
/* Backup RAM Initial                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomBRamInit(void)
{
	(void)u1_EVCOM_BW_P_CURDSP((U1)EVCOM_P_CURDSP_INIT);
	(void)u1_EVCOM_BW_P_CUR200((U1)EVCOM_P_CUR200_INIT);
	(void)u1_EVCOM_BW_P_CURSEL((U1)EVCOM_P_CURSEL_INIT);
	(void)u1_EVCOM_BW_CBLC_AVA((U1)EVCOM_CBLC_AVA_INIT);
	(void)u1_EVCOM_BW_CBLOCKSU((U1)EVCOM_CBLOCKSU_INIT);
	(void)u1_EVCOM_BW_P_LMTDSP((U1)EVCOM_P_LMTDSP_INIT);
	(void)u1_EVCOM_BW_P_LMTSET((U1)EVCOM_P_LMTSET_INIT);
	(void)u1_EVCOM_BW_PWSPLAVA((U1)EVCOM_PWSPLAVA_INIT);
	(void)u1_EVCOM_BW_PWSPPURQ((U1)EVCOM_PWSPPURQ_INIT);
	(void)u1_EVCOM_BW_EV_SLCT((U1)EVCOM_EV_SLCT_INIT);
	(void)u1_EVCOM_BW_HV_SLCT((U1)EVCOM_HV_SLCT_INIT);
	(void)u1_EVCOM_BW_P_ADDDSP((U1)EVCOM_P_ADDDSP_INIT);
	(void)u1_EVCOM_BW_PCNOWDSP((U1)EVCOM_PCNOWDSP_INIT);
	(void)u1_EVCOM_BW_PLGTMSW((U1)EVCOM_PLGTMSW_INIT);
	(void)u1_EVCOM_BW_P_TMPID((U1)EVCOM_P_TMPID_INIT);
	(void)u1_EVCOM_BW_P_TMPTYP((U1)EVCOM_P_TMPTYP_INIT);
	(void)u1_EVCOM_BW_P_TMPACD((U1)EVCOM_P_TMPACD_INIT);
	(void)u1_EVCOM_BW_P_TMPACN((U1)EVCOM_P_TMPACN_INIT);
	(void)u1_EVCOM_BW_P_TMPSTM((U2)EVCOM_P_TMPSTM_INIT);
	(void)u1_EVCOM_BW_P_TMPFTM((U2)EVCOM_P_TMPFTM_INIT);
	(void)u1_EVCOM_BW_P_TMPSWK((U1)EVCOM_P_TMPSWK_INIT);
	(void)u1_EVCOM_BW_P_TMPNWK((U1)EVCOM_P_TMPNWK_INIT);
	(void)u1_EVCOM_BW_P_NCTYP((U1)EVCOM_P_NCTYP_INIT);
	(void)u1_EVCOM_BW_P_NCWKD((U1)EVCOM_P_NCWKD_INIT);
	(void)u1_EVCOM_BW_P_NCSTM((U2)EVCOM_P_NCSTM_INIT);
	(void)u1_EVCOM_BW_P_NCFTM((U2)EVCOM_P_NCFTM_INIT);
	(void)u1_EVCOM_BW_P_NCDSP((U1)EVCOM_P_NCDSP_INIT);
	vd_s_EvcomInitTmChgSchdData();
}

/*===================================================================================================================================*/
/* Static RAM Initial                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomSRamInit(void)
{
	u1_s_evcom_ig_sts = (U1)FALSE;
	u1_s_evcom_msgsts_plg1s01 = (U1)EVCOM_ST_NO_RX;
	u1_s_evcom_msgsts_plg1g13 = (U1)EVCOM_ST_NO_RX;
	u1_s_evcom_pwsppurq_old = (U1)EVCOM_PWSPPURQ_INIT;
	u1_s_evcom_plgtmsw_old = (U1)EVCOM_PLGTMSW_INIT;
	st_s_evcom_tmp_wrk.u1_id   = (U1)EVCOM_P_TMPID_INIT;
	st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_INIT;
	st_s_evcom_tmp_wrk.u1_acd  = (U1)EVCOM_P_TMPACD_INIT;
	st_s_evcom_tmp_wrk.u1_acn  = (U1)EVCOM_P_TMPACN_INIT;
	st_s_evcom_tmp_wrk.u2_stm  = (U2)EVCOM_P_TMPSTM_INIT;
	st_s_evcom_tmp_wrk.u2_ftm  = (U2)EVCOM_P_TMPFTM_INIT;
	st_s_evcom_tmp_wrk.u1_swk  = (U1)EVCOM_P_TMPSWK_INIT;
	st_s_evcom_tmp_wrk.u1_nwk  = (U1)EVCOM_P_TMPNWK_INIT;
	u1_s_evcom_chg_cur_dsp_sts_no = (U1)EVCOM_CHG_CUR_DSP_NO_FAIL;
}

/*===================================================================================================================================*/
/* Periodic Task                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomRoutine(void)
{
	U1 u1_t_pwsppurq;						/* signal : PWSPPURQ	 */
	U1 u1_t_plgtmsw;						/* signal : PLGTMSW		 */
	
	u1_t_pwsppurq = (U1)EVCOM_PWSPPURQ_INIT;
	u1_t_plgtmsw  = (U1)EVCOM_PLGTMSW_INIT;
	
	(void)u1_EVCOM_BR_PWSPPURQ(&u1_t_pwsppurq);
	(void)u1_EVCOM_BR_PLGTMSW(&u1_t_plgtmsw);
	
	u1_s_evcom_pwsppurq_old = u1_t_pwsppurq;
	u1_s_evcom_plgtmsw_old  = u1_t_plgtmsw;
	
	u1_s_evcom_ig_sts = u1_EVCOM_GET_IG_STS();
	u1_s_evcom_msgsts_plg1s01 = u1_EVCOM_MSGSTS_PLG1S01();
	u1_s_evcom_msgsts_plg1g13 = u1_EVCOM_MSGSTS_PLG1G13();
	
	vd_s_EvcomUpdateReceiveData();
	vd_s_EvcomUpdateDspStsData();
}

/*===================================================================================================================================*/
/* Update : Receive Data                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateReceiveData(void)
{
	U1 u1_t_msgsts;							/* message status		 */
	U1 u1_t_p_curdsp;						/* signal : P_CURDSP	 */
	U1 u1_t_p_cur200;						/* signal : P_CUR200	 */
	U1 u1_t_p_cursel;						/* signal : P_CURSEL	 */
	U1 u1_t_cblc_ava;						/* signal : CBLC_AVA	 */
	U1 u1_t_cblocksu;						/* signal : CBLOCKSU	 */
	U1 u1_t_p_lmtdsp;						/* signal : P_LMTDSP	 */
	U1 u1_t_p_lmtset;						/* signal : P_LMTSET	 */
	U1 u1_t_pwsplava;						/* signal : pwsplava	 */
	U1 u1_t_pwsppurq;						/* signal : PWSPPURQ	 */
	U1 u1_t_ev_slct;						/* signal : EV_SLCT		 */
	U1 u1_t_hv_slct;						/* signal : HV_SLCT		 */
	
	u1_t_msgsts = u1_s_evcom_msgsts_plg1s01 & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts == (U1)0) {
		u1_t_p_curdsp = (U1)EVCOM_P_CURDSP_INIT;
		u1_t_p_cur200 = (U1)EVCOM_P_CUR200_INIT;
		u1_t_p_cursel = (U1)EVCOM_P_CURSEL_INIT;
		u1_t_cblc_ava = (U1)EVCOM_CBLC_AVA_INIT;
		u1_t_cblocksu = (U1)EVCOM_CBLOCKSU_INIT;
		u1_t_p_lmtdsp = (U1)EVCOM_P_LMTDSP_INIT;
		u1_t_p_lmtset = (U1)EVCOM_P_LMTSET_INIT;
		u1_t_pwsplava = (U1)EVCOM_PWSPLAVA_INIT;
		u1_t_pwsppurq = (U1)EVCOM_PWSPPURQ_INIT;
		u1_t_ev_slct  = (U1)EVCOM_EV_SLCT_INIT;
		u1_t_hv_slct  = (U1)EVCOM_HV_SLCT_INIT;
		
		vd_EVCOM_GET_P_CURDSP(&u1_t_p_curdsp);
		vd_EVCOM_GET_P_CUR200(&u1_t_p_cur200);
		vd_EVCOM_GET_P_CURSEL(&u1_t_p_cursel);
		vd_EVCOM_GET_CBLC_AVA(&u1_t_cblc_ava);
		vd_EVCOM_GET_CBLOCKSU(&u1_t_cblocksu);
		vd_EVCOM_GET_P_LMTDSP(&u1_t_p_lmtdsp);
		vd_EVCOM_GET_P_LMTSET(&u1_t_p_lmtset);
		vd_EVCOM_GET_PWSPLAVA(&u1_t_pwsplava);
		vd_EVCOM_GET_PWSPPURQ(&u1_t_pwsppurq);
		vd_EVCOM_GET_EV_SLCT(&u1_t_ev_slct);
		vd_EVCOM_GET_HV_SLCT(&u1_t_hv_slct);
		
		(void)u1_EVCOM_BW_P_CURDSP(u1_t_p_curdsp);
		(void)u1_EVCOM_BW_P_CUR200(u1_t_p_cur200);
		(void)u1_EVCOM_BW_P_CURSEL(u1_t_p_cursel);
		(void)u1_EVCOM_BW_CBLC_AVA(u1_t_cblc_ava);
		(void)u1_EVCOM_BW_CBLOCKSU(u1_t_cblocksu);
		(void)u1_EVCOM_BW_P_LMTDSP(u1_t_p_lmtdsp);
		(void)u1_EVCOM_BW_P_LMTSET(u1_t_p_lmtset);
		(void)u1_EVCOM_BW_PWSPLAVA(u1_t_pwsplava);
		(void)u1_EVCOM_BW_PWSPPURQ(u1_t_pwsppurq);
		(void)u1_EVCOM_BW_EV_SLCT(u1_t_ev_slct);
		(void)u1_EVCOM_BW_HV_SLCT(u1_t_hv_slct);
	} else if ((u1_t_msgsts & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		(void)u1_EVCOM_BW_P_CURDSP((U1)EVCOM_P_CURDSP_FAIL);
		/* P_CUR200 : HOLD */
		(void)u1_EVCOM_BW_P_CURSEL((U1)EVCOM_P_CURSEL_FAIL);
		(void)u1_EVCOM_BW_CBLC_AVA((U1)EVCOM_CBLC_AVA_FAIL);
		(void)u1_EVCOM_BW_P_LMTDSP((U1)EVCOM_P_LMTDSP_FAIL);
		(void)u1_EVCOM_BW_P_LMTSET((U1)EVCOM_P_LMTSET_FAIL);
		/* PWSPLAVA : HOLD */
		(void)u1_EVCOM_BW_PWSPPURQ((U1)EVCOM_PWSPPURQ_FAIL);
		(void)u1_EVCOM_BW_EV_SLCT((U1)EVCOM_EV_SLCT_FAIL);
		(void)u1_EVCOM_BW_HV_SLCT((U1)EVCOM_HV_SLCT_FAIL);
		
		if (u1_s_evcom_ig_sts != (U1)TRUE) {
			(void)u1_EVCOM_BW_CBLOCKSU((U1)EVCOM_CBLOCKSU_FAIL);
		}
		
	} else {
		/* Do Nothing */
	}
	
	vd_s_EvcomUpdateRxDataTmChgTmp();
	vd_s_EvcomUpdateRxDataTmChgNxt();
	vd_s_EvcomUpdateRxDataTmChgOthr();
	vd_s_EvcomUpdateRxDataTmChgSet();
}

/*===================================================================================================================================*/
/* Update : Receive Data (Timer Charge "TMP")                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateRxDataTmChgTmp(void)
{
	U1 u1_t_msgsts;							/* message status		 */
	U1 u1_t_tmpid;							/* signal : P_TMPID		 */
	U1 u1_t_tmptyp;							/* signal : P_TMPTYP	 */
	U1 u1_t_tmpacd;							/* signal : P_TMPACD	 */
	U1 u1_t_tmpacn;							/* signal : P_TMPACN	 */
	U2 u2_t_tmpstm;							/* signal : P_TMPSTM	 */
	U2 u2_t_tmpftm;							/* signal : P_TMPFTM	 */
	U1 u1_t_tmpswk;							/* signal : P_TMPSWK	 */
	U1 u1_t_tmpnwk;							/* signal : P_TMPNWK	 */
	
	u1_t_msgsts = u1_s_evcom_msgsts_plg1g13 & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts == (U1)0) {
		u1_t_tmpid  = (U1)EVCOM_P_TMPID_INIT;
		u1_t_tmptyp = (U1)EVCOM_P_TMPTYP_INIT;
		u1_t_tmpacd = (U1)EVCOM_P_TMPACD_INIT;
		u1_t_tmpacn = (U1)EVCOM_P_TMPACN_INIT;
		u2_t_tmpstm = (U2)EVCOM_P_TMPSTM_INIT;
		u2_t_tmpftm = (U2)EVCOM_P_TMPFTM_INIT;
		u1_t_tmpswk = (U1)EVCOM_P_TMPSWK_INIT;
		u1_t_tmpnwk = (U1)EVCOM_P_TMPNWK_INIT;
		
		vd_EVCOM_GET_P_TMPID(&u1_t_tmpid);
		vd_EVCOM_GET_P_TMPTYP(&u1_t_tmptyp);
		vd_EVCOM_GET_P_TMPACD(&u1_t_tmpacd);
		vd_EVCOM_GET_P_TMPACN(&u1_t_tmpacn);
		vd_EVCOM_GET_P_TMPSTM(&u2_t_tmpstm);
		vd_EVCOM_GET_P_TMPFTM(&u2_t_tmpftm);
		vd_EVCOM_GET_P_TMPSWK(&u1_t_tmpswk);
		vd_EVCOM_GET_P_TMPNWK(&u1_t_tmpnwk);
		
		(void)u1_EVCOM_BW_P_TMPID(u1_t_tmpid);
		(void)u1_EVCOM_BW_P_TMPTYP(u1_t_tmptyp);
		(void)u1_EVCOM_BW_P_TMPACD(u1_t_tmpacd);
		(void)u1_EVCOM_BW_P_TMPACN(u1_t_tmpacn);
		(void)u1_EVCOM_BW_P_TMPSTM(u2_t_tmpstm);
		(void)u1_EVCOM_BW_P_TMPFTM(u2_t_tmpftm);
		(void)u1_EVCOM_BW_P_TMPSWK(u1_t_tmpswk);
		(void)u1_EVCOM_BW_P_TMPNWK(u1_t_tmpnwk);
	} else if ((u1_t_msgsts & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		(void)u1_EVCOM_BW_P_TMPID((U1)EVCOM_P_TMPID_FAIL);
		(void)u1_EVCOM_BW_P_TMPTYP((U1)EVCOM_P_TMPTYP_FAIL);
		(void)u1_EVCOM_BW_P_TMPACD((U1)EVCOM_P_TMPACD_FAIL);
		(void)u1_EVCOM_BW_P_TMPACN((U1)EVCOM_P_TMPACN_FAIL);
		(void)u1_EVCOM_BW_P_TMPSTM((U2)EVCOM_P_TMPSTM_FAIL);
		(void)u1_EVCOM_BW_P_TMPFTM((U2)EVCOM_P_TMPFTM_FAIL);
		(void)u1_EVCOM_BW_P_TMPSWK((U1)EVCOM_P_TMPSWK_FAIL);
		(void)u1_EVCOM_BW_P_TMPNWK((U1)EVCOM_P_TMPNWK_FAIL);
	} else {
		/* Do Nothing */
	}
}

/*===================================================================================================================================*/
/* Update : Receive Data (Timer Charge "NEXT")                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateRxDataTmChgNxt(void)
{
	U1 u1_t_msgsts1G11;							/* message status : PLG1G11 */
	U1 u1_t_nctyp;								/* signal : P_NCTYP			*/
	U1 u1_t_ncwkd;								/* signal : P_NCWKD			*/
	U2 u2_t_ncstm;								/* signal : P_NCSTM			*/
	U2 u2_t_ncftm;								/* signal : P_NCFTM			*/
	U1 u1_t_ncdsp;								/* signal : P_NCDSP			*/
	
	u1_t_msgsts1G11 = u1_EVCOM_MSGSTS_PLG1G11() & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts1G11 == (U1)0) {
		u1_t_nctyp = (U1)EVCOM_P_NCTYP_INIT;
		u1_t_ncwkd = (U1)EVCOM_P_NCWKD_INIT;
		u2_t_ncstm = (U2)EVCOM_P_NCSTM_INIT;
		u2_t_ncftm = (U2)EVCOM_P_NCFTM_INIT;
		u1_t_ncdsp = (U1)EVCOM_P_NCDSP_INIT;
		
		vd_EVCOM_GET_P_NCTYP(&u1_t_nctyp);
		vd_EVCOM_GET_P_NCWKD(&u1_t_ncwkd);
		vd_EVCOM_GET_P_NCSTM(&u2_t_ncstm);
		vd_EVCOM_GET_P_NCFTM(&u2_t_ncftm);
		vd_EVCOM_GET_P_NCDSP(&u1_t_ncdsp);
		
		(void)u1_EVCOM_BW_P_NCTYP(u1_t_nctyp);
		(void)u1_EVCOM_BW_P_NCWKD(u1_t_ncwkd);
		(void)u1_EVCOM_BW_P_NCSTM(u2_t_ncstm);
		(void)u1_EVCOM_BW_P_NCFTM(u2_t_ncftm);
		(void)u1_EVCOM_BW_P_NCDSP(u1_t_ncdsp);
	} else if ((u1_t_msgsts1G11 & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		/* P_NCTYP : HOLD */
		/* P_NCWKD : HOLD */
		/* P_NCSTM : HOLD */
		/* P_NCFTM : HOLD */
		(void)u1_EVCOM_BW_P_NCDSP((U1)EVCOM_P_NCDSP_FAIL);
	} else {
		/* Do Nothing */
	}
}

/*===================================================================================================================================*/
/* Update : Receive Data Data (Timer Charge Other)                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateRxDataTmChgOthr(void)
{
	U1 u1_t_msgsts1G10;							/* message status : PLG1G10 */
	U1 u1_t_msgsts1G13;							/* message status : PLG1G13 */
	U1 u1_t_p_adddsp;							/* signal : P_ADDDSP		*/
	U1 u1_t_pcnowdsp;							/* signal : PCNOWDSP		*/
	U1 u1_t_plgtmsw;							/* signal : PLGTMSW			*/
	
	u1_t_msgsts1G10 = u1_EVCOM_MSGSTS_PLG1G10() & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts1G10 == (U1)0) {
		u1_t_plgtmsw = (U1)EVCOM_PLGTMSW_INIT;
		vd_EVCOM_GET_PLGTMSW(&u1_t_plgtmsw);
		(void)u1_EVCOM_BW_PLGTMSW(u1_t_plgtmsw);
	} else if ((u1_t_msgsts1G10 & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		(void)u1_EVCOM_BW_PLGTMSW((U1)EVCOM_PLGTMSW_FAIL);
	} else {
		/* Do Nothing */
	}
	
	u1_t_msgsts1G13 = u1_s_evcom_msgsts_plg1g13 & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts1G13 == (U1)0) {
		u1_t_p_adddsp = (U1)EVCOM_P_ADDDSP_INIT;
		u1_t_pcnowdsp = (U1)EVCOM_PCNOWDSP_INIT;
		
		vd_EVCOM_GET_P_ADDDSP(&u1_t_p_adddsp);
		vd_EVCOM_GET_PCNOWDSP(&u1_t_pcnowdsp);
		
		(void)u1_EVCOM_BW_P_ADDDSP(u1_t_p_adddsp);
		(void)u1_EVCOM_BW_PCNOWDSP(u1_t_pcnowdsp);
	} else if ((u1_t_msgsts1G13 & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		/* P_ADDDSP : HOLD */
		/* PCNOWDSP : HOLD */
	} else {
		/* Do Nothing */
	}
}

/*===================================================================================================================================*/
/* Update : Display Status Data                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateDspStsData(void)
{
	U1 u1_t_p_cursel;						/* signal : P_CURSEL	 */
	U1 u1_t_p_curdsp;						/* signal : P_CURDSP	 */
	U1 u1_t_p_cur200;						/* signal : P_CUR200	 */
	U1 u1_t_p_cur200_round;					/* P_CUR200 2bit round	 */
	U1 u1_t_chg_cur_jdg;					/* Charge Current Judge	 */
	
	u1_t_p_curdsp = (U1)EVCOM_P_CURDSP_INIT;
	u1_t_p_cur200 = (U1)EVCOM_P_CUR200_INIT;
	u1_t_p_cursel = (U1)EVCOM_P_CURSEL_INIT;
	
	(void)u1_EVCOM_BR_P_CURDSP(&u1_t_p_curdsp);
	(void)u1_EVCOM_BR_P_CUR200(&u1_t_p_cur200);
	(void)u1_EVCOM_BR_P_CURSEL(&u1_t_p_cursel);
	
	if (u1_t_p_cur200 > (U1)EVCOM_SHG_CUR_2BIT_MAX) {
		u1_t_p_cur200_round = (U1)EVCOM_SHG_CUR_2BIT_MAX;
	} else {
		u1_t_p_cur200_round = u1_t_p_cur200;
	}
	
	u1_t_chg_cur_jdg = u1_t_p_cursel;
	u1_t_chg_cur_jdg |= (U1)(u1_t_p_curdsp << EVCOM_CHG_CUR_P_CURDSP_SHIFT);
	u1_t_chg_cur_jdg |= (U1)(u1_t_p_cur200_round << EVCOM_CHG_CUR_P_CUR200_SHIFT);
	
	if ((u1_s_evcom_ig_sts == (U1)TRUE) &&
	    (u1_t_chg_cur_jdg < (U1)EVCOM_CHG_CUR_DSP_NO_NUM)) {
		u1_s_evcom_chg_cur_dsp_sts_no = u1_s_EVCOM_CHG_CUR_DSP_NO_JDG[u1_t_chg_cur_jdg];
	} else {
		u1_s_evcom_chg_cur_dsp_sts_no = (U1)EVCOM_CHG_CUR_DSP_NO_FAIL;
	}
}

/*===================================================================================================================================*/
/* Message Status : PLG1S01                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Message status                                                                                                       */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetPLG1S01MsgSts(void)
{
	return (u1_s_evcom_msgsts_plg1s01);
}

/*===================================================================================================================================*/
/* Message Status : Charge Now                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Message status                                                                                                       */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetChgNowMsgSts(void)
{
	return (u1_s_evcom_msgsts_plg1g13);
}

/*===================================================================================================================================*/
/* Signal Data : P_CUR200                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetCur200(void)
{
	U1 u1_t_p_cur200;						/* signal : P_CUR200	 */
	
	u1_t_p_cur200 = (U1)EVCOM_P_CUR200_INIT;
	(void)u1_EVCOM_BR_P_CUR200(&u1_t_p_cur200);
	
	return (u1_t_p_cur200);
}

/*===================================================================================================================================*/
/* Signal Data : CBLOCKSU                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetCBlockSu(void)
{
	U1 u1_t_cblocksu;						/* signal : CBLOCKSU	 */
	
	u1_t_cblocksu = (U1)EVCOM_CBLOCKSU_INIT;
	(void)u1_EVCOM_BR_CBLOCKSU(&u1_t_cblocksu);
	
	return (u1_t_cblocksu);
}

/*===================================================================================================================================*/
/* Signal Data : P_LMTSET                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetLmtSet(void)
{
	U1 u1_t_lmtset;							/* signal : P_LMTSET	 */
	
	u1_t_lmtset = (U1)EVCOM_P_LMTSET_INIT;
	(void)u1_EVCOM_BR_P_LMTSET(&u1_t_lmtset);
	
	return (u1_t_lmtset);
}

/*===================================================================================================================================*/
/* Signal Data : PWSPLAVA                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetPwSplAva(void)
{
	U1 u1_t_pwsplava;						/* signal : PWSPLAVA	 */
	
	u1_t_pwsplava = (U1)EVCOM_PWSPLAVA_INIT;
	(void)u1_EVCOM_BR_PWSPLAVA(&u1_t_pwsplava);
	
	return (u1_t_pwsplava);
}

/*===================================================================================================================================*/
/* Signal Data : PCNOWDSP                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetCNowDsp(void)
{
	U1 u1_t_pcnowdsp;						/* signal : PCNOWDSP	 */
	
	u1_t_pcnowdsp = (U1)EVCOM_PCNOWDSP_INIT;
	(void)u1_EVCOM_BR_PCNOWDSP(&u1_t_pcnowdsp);
	
	return (u1_t_pcnowdsp);
}

/*===================================================================================================================================*/
/* Signal Data : P_TMPID                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetTmpData(void)
{
	U1 u1_t_p_tmpid;						/* signal : P_TMPID	 */
	
	u1_t_p_tmpid = (U1)EVCOM_P_TMPID_INIT;
	(void)u1_EVCOM_BR_P_TMPID(&u1_t_p_tmpid);
	
	return (u1_t_p_tmpid);
}

/*===================================================================================================================================*/
/* Signal Data : P_NCTYP                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetNcTyp(void)
{
	U1 u1_t_p_nctyp;						/* signal : P_NCTYP	 */
	
	u1_t_p_nctyp = (U1)EVCOM_P_NCTYP_INIT;
	(void)u1_EVCOM_BR_P_NCTYP(&u1_t_p_nctyp);
	
	return (u1_t_p_nctyp);
}

/*===================================================================================================================================*/
/* Signal Data : P_NCDSP                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  Signal data                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetNcDsp(void)
{
	U1 u1_t_p_ncdsp;						/* signal : P_NCDSP	 */
	
	u1_t_p_ncdsp = (U1)EVCOM_P_NCDSP_INIT;
	(void)u1_EVCOM_BR_P_NCDSP(&u1_t_p_ncdsp);
	
	return (u1_t_p_ncdsp);
}

/*===================================================================================================================================*/
/* Get Receive Data "TMP_WORK"                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_TMP st_s_evcom_tmp_wrk                                                                                */
/*===================================================================================================================================*/
ST_EVCOM_TMCHG_TMP st_g_EvcomGetTmpWrkData(void)
{
	return (st_s_evcom_tmp_wrk);
}

/*===================================================================================================================================*/
/* Disp State : Appointed Content                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_cntt                                                                                                     */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetCnttSts(const U1 u1_a_cntt)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	if (u1_a_cntt < (U1)EVCOM_CNTT_NUM) {
		if (fp_sp_TBL_EVCOM_DISP_STS[u1_a_cntt] != NULL) {
			u1_t_dspsts = fp_sp_TBL_EVCOM_DISP_STS[u1_a_cntt]();
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Current Setting                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaChgSetDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_p_curdsp;						/* signal : P_CURDSP	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_p_curdsp = (U1)EVCOM_P_CURDSP_INIT;
	(void)u1_EVCOM_BR_P_CURDSP(&u1_t_p_curdsp);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_p_curdsp == (U1)EVCOM_P_CURDSP_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Connector Lock Setting                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaConLkDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	U1 u1_t_cblc_ava;						/* signal : CBLC_AVA	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_cblc_ava = (U1)EVCOM_CBLC_AVA_INIT;
	(void)u1_EVCOM_BR_CBLC_AVA(&u1_t_cblc_ava);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_cblc_ava == (U1)EVCOM_CBLC_AVA_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Limit Setting                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaChgLmtDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_p_lmtdsp;						/* signal : P_LMTDSP	 */

	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_p_lmtdsp = (U1)EVCOM_P_LMTDSP_INIT;
	(void)u1_EVCOM_BR_P_LMTDSP(&u1_t_p_lmtdsp);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_p_lmtdsp == (U1)EVCOM_P_LMTDSP_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Current Setting - MAX                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaMaxDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_chg_cur_dsp_sts_no < (U1)EVCOM_CHG_CUR_DSP_STS_NUM) {
		u1_t_dspsts = st_s_EVCOM_CHG_CUR_DSP_STS[u1_s_evcom_chg_cur_dsp_sts_no].u1_max;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Current Setting - 16A                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcCha16ADspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_chg_cur_dsp_sts_no < (U1)EVCOM_CHG_CUR_DSP_STS_NUM) {
		u1_t_dspsts = st_s_EVCOM_CHG_CUR_DSP_STS[u1_s_evcom_chg_cur_dsp_sts_no].u1_16a;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Current Setting - 8A                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcCha8ADspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_chg_cur_dsp_sts_no < (U1)EVCOM_CHG_CUR_DSP_STS_NUM) {
		u1_t_dspsts = st_s_EVCOM_CHG_CUR_DSP_STS[u1_s_evcom_chg_cur_dsp_sts_no].u1_8a;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Connector Lock Settign - Manual Lock                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaMnlLkDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		u1_t_dspsts = (U1)EVCOM_DSP_APLY;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Connector Lock Settign - Auto Lock                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaAtLkDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		u1_t_dspsts = (U1)EVCOM_DSP_APLY;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Connector Lock Settign - Auto Lock & Unlock                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaAtLkUlkDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		u1_t_dspsts = (U1)EVCOM_DSP_APLY;
	} else {
		u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Limit Setting - Full                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcChaFullDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_p_lmtdsp;						/* signal : P_LMTDSP	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_p_lmtdsp = (U1)EVCOM_P_LMTDSP_INIT;
	(void)u1_EVCOM_BR_P_LMTDSP(&u1_t_p_lmtdsp);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_p_lmtdsp == (U1)EVCOM_P_LMTDSP_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Charge Limit Setting - 90%                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcCha90pDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status */
	U1 u1_t_p_lmtdsp;						/* signal : P_LMTDSP	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_p_lmtdsp = (U1)EVCOM_P_LMTDSP_INIT;
	(void)u1_EVCOM_BR_P_LMTDSP(&u1_t_p_lmtdsp);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_p_lmtdsp == (U1)EVCOM_P_LMTDSP_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : External Supply                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcSplyExSplyDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_pwsplava;						/* signal : PWSPLAVA	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_pwsplava = (U1)EVCOM_PWSPLAVA_INIT;
	(void)u1_EVCOM_BR_PWSPLAVA(&u1_t_pwsplava);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_pwsplava == (U1)EVCOM_PWSPLAVA_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else if (u1_t_pwsplava == (U1)EVCOM_PWSPLAVA_GRAY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		} else {
			/* init value */
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : External Supply - EV Supply                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcSplyEvSplyDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status		 */
	U1 u1_t_ev_slct;						/* signal : EV_SLCT	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_ev_slct = (U1)EVCOM_EV_SLCT_INIT;
	(void)u1_EVCOM_BR_EV_SLCT(&u1_t_ev_slct);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_ev_slct == (U1)EVCOM_EV_SLCT_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}


/*===================================================================================================================================*/
/* Disp State : External Supply - HV Supply                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcDcSplyHvSplyDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status		 */
	U1 u1_t_hv_slct;						/* signal : HV_SLCT	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_NOAPLY;
	u1_t_hv_slct = (U1)EVCOM_HV_SLCT_INIT;
	(void)u1_EVCOM_BR_HV_SLCT(&u1_t_hv_slct);
	
	if (u1_s_evcom_ig_sts == (U1)TRUE) {
		if (u1_t_hv_slct == (U1)EVCOM_HV_SLCT_APLY) {
			u1_t_dspsts = (U1)EVCOM_DSP_APLY;
		} else {
			u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
		}
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Time Schedule - Add                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomChgSchdAddDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_p_adddsp;						/* signal : P_ADDDSP	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
	u1_t_p_adddsp = (U1)EVCOM_P_ADDDSP_INIT;
	(void)u1_EVCOM_BR_P_ADDDSP(&u1_t_p_adddsp);
	
	if (u1_t_p_adddsp == (U1)EVCOM_P_ADDDSP_APLY) {
		u1_t_dspsts = (U1)EVCOM_DSP_APLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Disp State : Time Schedule - Next Charge                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomChgSchdNxtChgDspSts(void)
{
	U1 u1_t_dspsts;							/* Disp status		 */
	U1 u1_t_p_nctyp;						/* signal ; P_NCTYP	 */
	
	u1_t_p_nctyp = (U1)EVCOM_P_NCTYP_INIT;
	(void)u1_EVCOM_BR_P_NCTYP(&u1_t_p_nctyp);
	
	u1_t_dspsts = (U1)EVCOM_DSP_APLYGRAY;
	
	if (((u1_t_p_nctyp == (U1)EVCOM_P_NCTYP_START) ||
	     (u1_t_p_nctyp == (U1)EVCOM_P_NCTYP_FIN_AC_OFF)) ||
	     (u1_t_p_nctyp == (U1)EVCOM_P_NCTYP_FIN_AC_ON)) {
		u1_t_dspsts = (U1)EVCOM_DSP_APLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Charge Now Button Disp State                                                                                                      */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_dspsts : Disp status                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetChgNowSts(void)
{
	U1 u1_t_dspsts;							/* Disp status			 */
	U1 u1_t_pcnowdsp;						/* signal : PCNOWDSP	 */
	
	u1_t_dspsts = (U1)EVCOM_DSP_CHG_NOW_APLYGRAY;
	u1_t_pcnowdsp = (U1)EVCOM_PCNOWDSP_INIT;
	(void)u1_EVCOM_BR_PCNOWDSP(&u1_t_pcnowdsp);
	
	if ((u1_t_pcnowdsp == (U1)EVCOM_PCNOWDSP_OFF_APLY) ||
	    (u1_t_pcnowdsp == (U1)EVCOM_PCNOWDSP_ON_APLY)) {
		u1_t_dspsts = (U1)EVCOM_DSP_CHG_NOW_APLY;
	}
	
	return (u1_t_dspsts);
}

/*===================================================================================================================================*/
/* Get Disp Contents - "SET"                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_DSP_SET st_t_set_dsp                                                                                  */
/*===================================================================================================================================*/
ST_EVCOM_TMCHG_DSP_SET st_g_EvcomGetSetDspData(U1 u1_a_dsp_no)
{
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_onoff;							/* ON/OFF				 */
	U1 u1_t_chg_type;						/* Charge Type			 */
	U2 u2_t_time;							/* Time (signal)		 */
	U1 u1_t_hour_24h;						/* Hour (24h format)	 */
	U1 u1_t_hour_dsp;						/* Hour (Disp format)	 */
	U1 u1_t_min_dsp;						/* Minute (Disp format)	 */
	U1 u1_t_ampm;							/* AM/PM				 */
	ST_EVCOM_TMCHG_DSP_SET st_t_set_dsp;	/* Disp Data (SET)		 */
	ST_EVCOM_TMCHG_SET     st_t_set;		/* Schedule Data		 */
	
	u1_t_id = u1_s_EvcomGetSchdDataIdByPos(u1_a_dsp_no);
	st_t_set = st_s_EvcomGetSchdDataById(u1_t_id);
	
	if (st_t_set.u1_onoff == (U1)EVCOM_P_SETON_ON) {
		u1_t_onoff = (U1)EVCOM_SCHD_ON;
	} else {
		u1_t_onoff = (U1)EVCOM_SCHD_OFF;
	}
	
	if (st_t_set.u1_type < (U1)EVCOM_SET_CHGTYPE_SIG_NUM) {
		u1_t_chg_type = u1_s_EVCOM_SET_CHGTYPE_SIG2DSP[st_t_set.u1_type];
	} else {
		u1_t_chg_type = (U1)EVCOM_CHG_TYPE_BLANK;
	}
	
	if (u1_t_chg_type == (U1)EVCOM_CHG_TYPE_START) {
		u2_t_time = st_t_set.u2_start_tim;
	} else {
		u2_t_time = st_t_set.u2_finish_tim;
	}
	
	u1_t_hour_24h = u1_s_EvcomSigToHour24h(u2_t_time);
	u1_t_hour_dsp = u1_s_EvcomHour24hToDsp(u1_t_hour_24h);
	u1_t_min_dsp = u1_s_EvcomSigToMin(u2_t_time);
	u1_t_ampm = u1_s_EvcomGetAmPm(u1_t_hour_24h);
	
	st_t_set_dsp.u1_onoff    = u1_t_onoff;
	st_t_set_dsp.u1_chg_type = u1_t_chg_type;
	st_t_set_dsp.u1_hour     = u1_t_hour_dsp;
	st_t_set_dsp.u1_min      = u1_t_min_dsp;
	st_t_set_dsp.u1_ampm     = u1_t_ampm;
	st_t_set_dsp.u1_wkd_bit  = st_t_set.u1_wkd_bit;
	
	return (st_t_set_dsp);
}

/*===================================================================================================================================*/
/* Get Disp Contents - "TMP"                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_DSP_TMP st_t_dsp_tmp                                                                                  */
/*===================================================================================================================================*/
ST_EVCOM_TMCHG_DSP_TMP st_g_EvcomGetTmpDspData(void)
{
	ST_EVCOM_TMCHG_DSP_TMP st_t_dsp_tmp;		/* Disp Data (TEMP)			 */
	ST_EVCOM_TMCHG_TMP st_t_tmp;				/* "TMP" Buffer				 */
	
	st_t_tmp.u1_id   = (U1)EVCOM_P_TMPID_INIT;
	st_t_tmp.u1_type = (U1)EVCOM_P_TMPTYP_INIT;
	st_t_tmp.u1_acd  = (U1)EVCOM_P_TMPACD_INIT;
	st_t_tmp.u1_acn  = (U1)EVCOM_P_TMPACN_INIT;
	st_t_tmp.u2_stm  = (U2)EVCOM_P_TMPSTM_INIT;
	st_t_tmp.u2_ftm  = (U2)EVCOM_P_TMPFTM_INIT;
	st_t_tmp.u1_swk  = (U1)EVCOM_P_TMPSWK_INIT;
	st_t_tmp.u1_nwk  = (U1)EVCOM_P_TMPNWK_INIT;
	
	(void)u1_EVCOM_BR_P_TMPID(&(st_t_tmp.u1_id));
	(void)u1_EVCOM_BR_P_TMPTYP(&(st_t_tmp.u1_type));
	(void)u1_EVCOM_BR_P_TMPACD(&(st_t_tmp.u1_acd));
	(void)u1_EVCOM_BR_P_TMPACN(&(st_t_tmp.u1_acn));
	(void)u1_EVCOM_BR_P_TMPSTM(&(st_t_tmp.u2_stm));
	(void)u1_EVCOM_BR_P_TMPFTM(&(st_t_tmp.u2_ftm));
	(void)u1_EVCOM_BR_P_TMPSWK(&(st_t_tmp.u1_swk));
	(void)u1_EVCOM_BR_P_TMPNWK(&(st_t_tmp.u1_nwk));
	
	st_t_dsp_tmp = st_s_EvcomMakeTmpDspData(&st_t_tmp);
	
	return (st_t_dsp_tmp);
}

/*===================================================================================================================================*/
/* Get Disp Contents - "TMP_WORK"                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_DSP_TMP st_t_tmp                                                                                      */
/*===================================================================================================================================*/
ST_EVCOM_TMCHG_DSP_TMP st_g_EvcomGetTmpWrkDspData(void)
{
	ST_EVCOM_TMCHG_DSP_TMP st_t_tmp;		/* Disp Data (TEMP_WORK)	 */
	
	st_t_tmp = st_s_EvcomMakeTmpDspData(&st_s_evcom_tmp_wrk);
	
	return (st_t_tmp);
}

/*===================================================================================================================================*/
/* Make Disp Contents - "TMP/TMP_WORK"                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_DSP_TMP st_t_tmp                                                                                      */
/*===================================================================================================================================*/
static ST_EVCOM_TMCHG_DSP_TMP st_s_EvcomMakeTmpDspData(const ST_EVCOM_TMCHG_TMP * st_a_tmp)
{
	U1 u1_t_chg_type;						/* Charge Type			 */
	U2 u2_t_time;							/* Time (signal)		 */
	U1 u1_t_hour_24h;						/* Hour (24h format)	 */
	U1 u1_t_hour_dsp;						/* Hour (Disp format)	 */
	U1 u1_t_min_dsp;						/* Minute (Disp format)	 */
	U1 u1_t_ampm;							/* AM/PM				 */
	U1 u1_t_nwk;							/* No. Weekday			 */
	ST_EVCOM_TMCHG_DSP_TMP st_t_tmp;		/* Disp Data (TEMP)		 */
	
	if (st_a_tmp->u1_type == (U1)EVCOM_P_TMPTYP_START) {
		u1_t_chg_type = (U1)EVCOM_CHG_TYPE_START;
	} else if (st_a_tmp->u1_type == (U1)EVCOM_P_TMPTYP_FINISH){
		if (st_a_tmp->u1_acn == (U1)EVCOM_P_TMPACN_ON) {
			u1_t_chg_type = (U1)EVCOM_CHG_TYPE_FIN_AC_ON;
		} else {
			u1_t_chg_type = (U1)EVCOM_CHG_TYPE_FIN_AC_OFF;
		}
	} else {
		u1_t_chg_type = (U1)EVCOM_CHG_TYPE_BLANK;
	}
	
	if (st_a_tmp->u1_nwk < (U1)EVCOM_TMP_WKD_SIG_NUM) {
		u1_t_nwk = u1_s_EVCOM_TMP_WKD_SIG2DSP[st_a_tmp->u1_nwk];
	} else {
		u1_t_nwk = (U1)EVCOM_CHG_TYPE_BLANK;
	}
	
	if (u1_t_chg_type == (U1)EVCOM_CHG_TYPE_START) {
		u2_t_time = st_a_tmp->u2_stm;
	} else {
		u2_t_time = st_a_tmp->u2_ftm;
	}
	
	u1_t_hour_24h = u1_s_EvcomSigToHour24h(u2_t_time);
	u1_t_hour_dsp = u1_s_EvcomHour24hToDsp(u1_t_hour_24h);
	u1_t_min_dsp = u1_s_EvcomSigToMin(u2_t_time);
	u1_t_ampm = u1_s_EvcomGetAmPm(u1_t_hour_24h);
	
	st_t_tmp.u1_chg_type = u1_t_chg_type;
	st_t_tmp.u1_hour     = u1_t_hour_dsp;
	st_t_tmp.u1_min      = u1_t_min_dsp;
	st_t_tmp.u1_ampm     = u1_t_ampm;
	st_t_tmp.u1_wkd      = u1_t_nwk;
	st_t_tmp.u1_wkd_bit  = st_a_tmp->u1_swk;
	
	return (st_t_tmp);
}

/*===================================================================================================================================*/
/* Get Disp Contents - "NEXT"                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  ST_EVCOM_TMCHG_DSP_NXT st_t_next                                                                                     */
/*===================================================================================================================================*/
ST_EVCOM_TMCHG_DSP_NXT st_g_EvcomGetNxtDspData(void)
{
	U1 u1_t_p_nctyp;						/* signal : P_NCTYP		 */
	U1 u1_t_p_ncwkd;						/* signal : P_NCWKD		 */
	U2 u2_t_p_ncstm;						/* signal : P_NCSTM		 */
	U2 u2_t_p_ncftm;						/* signal : P_NCFTM		 */
	U1 u1_t_chg_type;						/* Charge Type			 */
	U2 u2_t_time;							/* Time (signal)		 */
	U1 u1_t_hour_24h;						/* Hour (24h format)	 */
	U1 u1_t_hour_dsp;						/* Hour (Disp format)	 */
	U1 u1_t_min_dsp;						/* Minute (Disp format)	 */
	U1 u1_t_ampm;							/* AM/PM				 */
	U1 u1_t_wkd;							/* Weekday				 */
	ST_EVCOM_TMCHG_DSP_NXT st_t_next;		/* Disp Data (NEXT)		 */
	
	u1_t_p_nctyp = (U1)EVCOM_P_NCTYP_INIT;
	u1_t_p_ncwkd = (U1)EVCOM_P_NCWKD_INIT;
	u2_t_p_ncstm = (U2)EVCOM_P_NCSTM_INIT;
	u2_t_p_ncftm = (U2)EVCOM_P_NCFTM_INIT;
	
	(void)u1_EVCOM_BR_P_NCTYP(&u1_t_p_nctyp);
	(void)u1_EVCOM_BR_P_NCWKD(&u1_t_p_ncwkd);
	(void)u1_EVCOM_BR_P_NCSTM(&u2_t_p_ncstm);
	(void)u1_EVCOM_BR_P_NCFTM(&u2_t_p_ncftm);
	
	if (u1_t_p_nctyp < (U1)EVCOM_NXT_CHGTYPE_SIG_NUM) {
		u1_t_chg_type = u1_s_EVCOM_NXT_CHGTYPE_SIG2DSP[u1_t_p_nctyp];
	} else {
		u1_t_chg_type = (U1)EVCOM_CHG_TYPE_BLANK;
	}
	
	if (u1_t_p_ncwkd < (U1)EVCOM_NXT_WKD_SIG_NUM) {
		u1_t_wkd = u1_s_EVCOM_NXT_WKD_SIG2DSP[u1_t_p_ncwkd];
	} else {
		u1_t_wkd = (U1)EVCOM_WKD_BLANK;
	}
	
	if (u1_t_chg_type == (U1)EVCOM_CHG_TYPE_START) {
		u2_t_time = u2_t_p_ncstm;
	} else {
		u2_t_time = u2_t_p_ncftm;
	}
	
	u1_t_hour_24h = u1_s_EvcomSigToHour24h(u2_t_time);
	u1_t_hour_dsp = u1_s_EvcomHour24hToDsp(u1_t_hour_24h);
	u1_t_min_dsp = u1_s_EvcomSigToMin(u2_t_time);
	u1_t_ampm = u1_s_EvcomGetAmPm(u1_t_hour_24h);
	
	st_t_next.u1_chg_type = u1_t_chg_type;
	st_t_next.u1_hour     = u1_t_hour_dsp;
	st_t_next.u1_min      = u1_t_min_dsp;
	st_t_next.u1_ampm     = u1_t_ampm;
	st_t_next.u1_wkd      = u1_t_wkd;
	
	return (st_t_next);
}

/*===================================================================================================================================*/
/* Get Disp Contents - Hour (24H format)                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_time : signal data (smt / fmt)                                                                         */
/*  Return   :  U1 u1_t_hour_24h                                                                                                     */
/*===================================================================================================================================*/
static   U1 u1_s_EvcomSigToHour24h(const U2 u2_a_time)
{
	U1 u1_t_hour_24h;						/* hour (24H format) */
	U2 u2_t_min_raw;						/* minute			 */
	
	u2_t_min_raw = u2_a_time * (U2)EVCOM_TIME_LSB;
	u1_t_hour_24h = (U1)(u2_t_min_raw / (U2)EVCOM_MIN_TO_HOUR) % (U1)EVCOM_HOUR_MOD;
	
	return (u1_t_hour_24h);
}

/*===================================================================================================================================*/
/* Get Disp Contents - Hour (Disp format)                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_time : signal data (smt / fmt)                                                                         */
/*  Return   :  U1 u1_t_hour_dsp                                                                                                     */
/*===================================================================================================================================*/
static   U1 u1_s_EvcomHour24hToDsp(const U1 u1_a_hour_24h)
{
	U1 u1_t_hour_dsp;						/* Hour (Disp format)	 */
	U1 u1_t_clk_fmt;						/* Clock format	 */
	
	u1_t_clk_fmt = u1_EVCOM_GET_CLK_FMT();
	if (u1_t_clk_fmt == (U1)EVCOM_CLK_FMT_12H) {
		u1_t_hour_dsp = u1_a_hour_24h % (U1)EVCOM_HOUR_12H;
		if (u1_t_hour_dsp == (U1)0) {
			u1_t_hour_dsp = (U1)EVCOM_HOUR_12H;
		}
	} else {
		u1_t_hour_dsp = u1_a_hour_24h;
	}
	
	return (u1_t_hour_dsp);
}

/*===================================================================================================================================*/
/* Get Disp Contents - Minutes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U2 u2_a_time : signal data (smt / fmt)                                                                         */
/*  Return   :  U1 u1_t_min_dsp                                                                                                      */
/*===================================================================================================================================*/
static   U1 u1_s_EvcomSigToMin(const U2 u2_a_time)
{
	U2 u2_t_min_raw;						/* minute (raw)	 */
	U1 u1_t_min_dsp;						/* minute (disp) */
	
	u2_t_min_raw = u2_a_time * (U2)EVCOM_TIME_LSB;
	u1_t_min_dsp = (U1)(u2_t_min_raw % (U2)EVCOM_MIN_TO_HOUR);
	
	return (u1_t_min_dsp);
}

/*===================================================================================================================================*/
/* Get Disp Contents - AM/PM                                                                                                         */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  U1 u1_a_hour_24h : hour (24H format)                                                                                 */
/*  Return   :  U1 u1_t_ampm                                                                                                         */
/*===================================================================================================================================*/
static   U1 u1_s_EvcomGetAmPm(const U1 u1_a_hour_24h)
{
	U1 u1_t_ampm;							/* AM/PM		 */
	U1 u1_t_clk_fmt;						/* Clock format	 */
	
	u1_t_clk_fmt = u1_EVCOM_GET_CLK_FMT();
	if (u1_t_clk_fmt == (U1)EVCOM_CLK_FMT_12H) {
		if (u1_a_hour_24h <= (U1)EVCOM_AM_HOUR_MAX) {
			u1_t_ampm = (U1)EVCOM_AMPM_AM;
		} else {
			u1_t_ampm = (U1)EVCOM_AMPM_PM;
		}
	} else {
		u1_t_ampm = (U1)EVCOM_AMPM_NON;
	}
	
	return (u1_t_ampm);
}

/*===================================================================================================================================*/
/* Get Charge Schedule Trans Request                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  transition request                                                                                                   */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetChgSchdTransReq(void)
{
	U1 u1_t_trans_req;						/* transition request */
	U1 u1_t_plgtmsw;						/* signal : PLGTMSW	  */
	
	u1_t_plgtmsw  = (U1)EVCOM_PLGTMSW_INIT;
	(void)u1_EVCOM_BR_PLGTMSW(&u1_t_plgtmsw);
	
	u1_t_trans_req = (U1)FALSE;
	if ((u1_s_evcom_plgtmsw_old == (U1)EVCOM_PLGTMSW_NOREQ) &&
	    (u1_t_plgtmsw == (U1)EVCOM_PLGTMSW_REQ)) {
		u1_t_trans_req = (U1)TRUE;
	}
	
	return (u1_t_trans_req);
}

/*===================================================================================================================================*/
/* Time Setting Is Complete                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  judge result                                                                                                         */
/*===================================================================================================================================*/
U1   u1_g_EvcomTmSetIsComp(void)
{
	U1 u1_t_result;							/* Judge Result			 */
	U1 u1_t_p_tmptyp;						/* signal : P_TMPTYP	 */
	U2 u2_t_p_tmpstm;						/* signal : P_TMPSTM	 */
	U2 u2_t_p_tmpftm;						/* signal : P_TMPFTM	 */
	
	u1_t_p_tmptyp = (U1)EVCOM_P_TMPTYP_INIT;
	u2_t_p_tmpstm = (U2)EVCOM_P_TMPSTM_INIT;
	u2_t_p_tmpftm = (U2)EVCOM_P_TMPFTM_INIT;
	
	(void)u1_EVCOM_BR_P_TMPTYP(&u1_t_p_tmptyp);
	(void)u1_EVCOM_BR_P_TMPSTM(&u2_t_p_tmpstm);
	(void)u1_EVCOM_BR_P_TMPFTM(&u2_t_p_tmpftm);
	
	u1_t_result = (U1)FALSE;
	if (st_s_evcom_tmp_wrk.u1_type == (U1)EVCOM_P_TMPTYP_START) {
		if ((st_s_evcom_tmp_wrk.u1_type == u1_t_p_tmptyp) &&
		    (st_s_evcom_tmp_wrk.u2_stm == u2_t_p_tmpstm)) {
			u1_t_result = (U1)TRUE;
		}
	} else {
		if ((st_s_evcom_tmp_wrk.u1_type ==u1_t_p_tmptyp) &&
		    (st_s_evcom_tmp_wrk.u2_ftm == u2_t_p_tmpftm)) {
			u1_t_result = (U1)TRUE;
		}
	}
	
	return (u1_t_result);
}

/*===================================================================================================================================*/
/* Air-Conditioner Setting Request                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_req                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetAcdDispReq(void)
{
	U1 u1_t_req;							/* Request				 */
	U1 u1_t_p_tmpacd;						/* signal : P_TMPACD	 */
	
	u1_t_p_tmpacd = (U1)EVCOM_P_TMPACD_INIT;
	(void)u1_EVCOM_BR_P_TMPACD(&u1_t_p_tmpacd);
	
	u1_t_req = (U1)FALSE;
	if (u1_t_p_tmpacd == (U1)EVCOM_P_TMPACD_REQ) {
		u1_t_req = (U1)TRUE;
	}
	
	return (u1_t_req);
}

/*===================================================================================================================================*/
/* Time Setting Start Hook                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetStart(void)
{
	st_s_evcom_tmp_wrk.u1_id   = (U1)EVCOM_P_TMPID_INIT;
	st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_INIT;
	st_s_evcom_tmp_wrk.u1_acd  = (U1)EVCOM_P_TMPACD_INIT;
	st_s_evcom_tmp_wrk.u1_acn  = (U1)EVCOM_P_TMPACN_INIT;
	st_s_evcom_tmp_wrk.u2_stm  = (U2)EVCOM_P_TMPSTM_INIT;
	st_s_evcom_tmp_wrk.u2_ftm  = (U2)EVCOM_P_TMPFTM_INIT;
	st_s_evcom_tmp_wrk.u1_swk  = (U1)EVCOM_P_TMPSWK_INIT;
	st_s_evcom_tmp_wrk.u1_nwk  = (U1)EVCOM_P_TMPNWK_INIT;
	
	(void)u1_EVCOM_BR_P_TMPID(&(st_s_evcom_tmp_wrk.u1_id));
	(void)u1_EVCOM_BR_P_TMPTYP(&(st_s_evcom_tmp_wrk.u1_type));
	(void)u1_EVCOM_BR_P_TMPACD(&(st_s_evcom_tmp_wrk.u1_acd));
	(void)u1_EVCOM_BR_P_TMPACN(&(st_s_evcom_tmp_wrk.u1_acn));
	(void)u1_EVCOM_BR_P_TMPSTM(&(st_s_evcom_tmp_wrk.u2_stm));
	(void)u1_EVCOM_BR_P_TMPFTM(&(st_s_evcom_tmp_wrk.u2_ftm));
	(void)u1_EVCOM_BR_P_TMPSWK(&(st_s_evcom_tmp_wrk.u1_swk));
	(void)u1_EVCOM_BR_P_TMPNWK(&(st_s_evcom_tmp_wrk.u1_nwk));
	
	if (st_s_evcom_tmp_wrk.u1_type == (U1)EVCOM_P_TMPTYP_START) {
		st_s_evcom_tmp_wrk.u2_ftm = st_s_evcom_tmp_wrk.u2_stm;
	} else {
		st_s_evcom_tmp_wrk.u2_stm = st_s_evcom_tmp_wrk.u2_ftm;
	}
}

/*===================================================================================================================================*/
/* Time Setting - Charge Type Up                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetTypeUp(void)
{
	if (st_s_evcom_tmp_wrk.u1_type == (U1)EVCOM_P_TMPTYP_START) {
		st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_FINISH;
	} else {
		st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_START;
	}
}

/*===================================================================================================================================*/
/* Time Setting - Charge Type Down                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetTypeDown(void)
{
	if (st_s_evcom_tmp_wrk.u1_type == (U1)EVCOM_P_TMPTYP_START) {
		st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_FINISH;
	} else {
		st_s_evcom_tmp_wrk.u1_type = (U1)EVCOM_P_TMPTYP_START;
	}
}

/*===================================================================================================================================*/
/* Time Setting - Hour Up                                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetHourUp(void)
{
	U1 u1_t_hour;							/* hour				 */
	U1 u1_t_min;							/* min				 */
	
	u1_t_hour = u1_s_EvcomSigToHour24h(st_s_evcom_tmp_wrk.u2_stm);
	u1_t_min  = u1_s_EvcomSigToMin(st_s_evcom_tmp_wrk.u2_stm);
	
	u1_t_hour = ((u1_t_hour + (U1)EVCOM_HOUR_UPDN_VAL) % (U1)EVCOM_HOUR_MOD);
	
	st_s_evcom_tmp_wrk.u2_stm = u2_s_EvcomMakeTimeSig(u1_t_hour, u1_t_min);
	st_s_evcom_tmp_wrk.u2_ftm = st_s_evcom_tmp_wrk.u2_stm;
}

/*===================================================================================================================================*/
/* Time Setting - Hour Down                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetHourDown(void)
{
	U1 u1_t_hour;							/* hour				 */
	U1 u1_t_min;							/* min				 */
	
	u1_t_hour = u1_s_EvcomSigToHour24h(st_s_evcom_tmp_wrk.u2_stm);
	u1_t_min  = u1_s_EvcomSigToMin(st_s_evcom_tmp_wrk.u2_stm);
	
	if (u1_t_hour >= (U1)EVCOM_HOUR_UPDN_VAL) {
		u1_t_hour -= (U1)EVCOM_HOUR_UPDN_VAL;
	} else {
		u1_t_hour = (U1)EVCOM_HOUR_MOD - (((U1)EVCOM_HOUR_UPDN_VAL - u1_t_hour) % (U1)EVCOM_HOUR_MOD);
	}
	
	st_s_evcom_tmp_wrk.u2_stm = u2_s_EvcomMakeTimeSig(u1_t_hour, u1_t_min);
	st_s_evcom_tmp_wrk.u2_ftm = st_s_evcom_tmp_wrk.u2_stm;
}

/*===================================================================================================================================*/
/* Time Setting - Minute Up                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetMinUp(void)
{
	U1 u1_t_hour;							/* hour				 */
	U1 u1_t_min;							/* min				 */
	
	u1_t_hour = u1_s_EvcomSigToHour24h(st_s_evcom_tmp_wrk.u2_stm);
	u1_t_min  = u1_s_EvcomSigToMin(st_s_evcom_tmp_wrk.u2_stm);
	
	u1_t_min = ((u1_t_min + (U1)EVCOM_MIN_UPDN_VAL) % (U1)EVCOM_MIN_MOD);
	
	st_s_evcom_tmp_wrk.u2_stm = u2_s_EvcomMakeTimeSig(u1_t_hour, u1_t_min);
	st_s_evcom_tmp_wrk.u2_ftm = st_s_evcom_tmp_wrk.u2_stm;
}

/*===================================================================================================================================*/
/* Time Setting - Minute Down                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_EvcomTmSetMinDown(void)
{
	U1 u1_t_hour;							/* hour				 */
	U1 u1_t_min;							/* min				 */
	
	u1_t_hour = u1_s_EvcomSigToHour24h(st_s_evcom_tmp_wrk.u2_stm);
	u1_t_min  = u1_s_EvcomSigToMin(st_s_evcom_tmp_wrk.u2_stm);
	
	if (u1_t_min >= (U1)EVCOM_MIN_UPDN_VAL) {
		u1_t_min -= (U1)EVCOM_MIN_UPDN_VAL;
	} else {
		u1_t_min = (U1)EVCOM_MIN_MOD - (((U1)EVCOM_MIN_UPDN_VAL - u1_t_min) % (U1)EVCOM_MIN_MOD);
	}
	
	st_s_evcom_tmp_wrk.u2_stm = u2_s_EvcomMakeTimeSig(u1_t_hour, u1_t_min);
	st_s_evcom_tmp_wrk.u2_ftm = st_s_evcom_tmp_wrk.u2_stm;
}

/*===================================================================================================================================*/
/* Make Time Signal                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  U1 u1_a_hour                                                                                                         */
/*              U1 u1_a_min                                                                                                          */
/*  Return   :  U2 u2_t_tim                                                                                                          */
/*===================================================================================================================================*/
static   U2 u2_s_EvcomMakeTimeSig(const U1 u1_a_hour, const U1 u1_a_min)
{
	U2 u2_t_tim;							/* tim (signal)	 */
	
	u2_t_tim = (((U2)u1_a_hour * (U2)EVCOM_MIN_TO_HOUR) + (U2)u1_a_min) / (U2)EVCOM_TIME_LSB;
	
	return (u2_t_tim);
}

/*===================================================================================================================================*/
/* Air-Conditioner Initial Select Content                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_sel                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomAcdSetInitSel(void)
{
	U1 u1_t_sel;							/* select				 */
	U1 u1_t_p_tmpacn;						/* signal : P_TMPACN	 */
	
	u1_t_p_tmpacn = (U1)EVCOM_P_TMPACN_INIT;
	(void)u1_EVCOM_BR_P_TMPACN(&u1_t_p_tmpacn);
	
	u1_t_sel = (U1)EVCOM_TMCHG_ACD_NO;
	if (u1_t_p_tmpacn == (U1)EVCOM_P_TMPACN_ON) {
		u1_t_sel = (U1)EVCOM_TMCHG_ACD_YES;
	}
	
	return (u1_t_sel);
}

/*===================================================================================================================================*/
/* Next Setting Trans Request                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_req                                                                                                          */
/*===================================================================================================================================*/
U1   u1_g_EvcomTmChgTransNxtSet(void)
{
	U1 u1_t_req;							/* Trans Request (Next Setting)	 */
	U1 u1_t_p_tmpid;						/* signal : P_TMPID				 */
	
	u1_t_p_tmpid = (U1)EVCOM_P_TMPID_INIT;
	(void)u1_EVCOM_BR_P_TMPID(&u1_t_p_tmpid);
	
	if (u1_t_p_tmpid == (U1)EVCOM_P_TMPID_NEXT) {
		u1_t_req = (U1)TRUE;
	} else {
		u1_t_req = (U1)FALSE;
	}
	
	return (u1_t_req);
}

/*===================================================================================================================================*/
/* Get External Supply Trans Request                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  transition request                                                                                                   */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetExSplyTransReq(void)
{
	U1 u1_t_trans_req;						/* transition request	 */
	U1 u1_t_pwsppurq;						/* signal : PWSPPURQ	 */
	
	u1_t_pwsppurq = (U1)EVCOM_PWSPPURQ_INIT;
	(void)u1_EVCOM_BR_PWSPPURQ(&u1_t_pwsppurq);
	
	u1_t_trans_req = (U1)FALSE;
	if (((u1_s_evcom_ig_sts == (U1)TRUE) &&
	     (u1_s_evcom_pwsppurq_old == (U1)EVCOM_PWSPPURQ_NOREQ)) &&
	     (u1_t_pwsppurq == (U1)EVCOM_PWSPPURQ_REQ)) {
		u1_t_trans_req = (U1)TRUE;
	}
	
	return (u1_t_trans_req);
}

/*===================================================================================================================================*/
/* Get Charge Schedule Support Bit                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  support bit                                                                                                          */
/*===================================================================================================================================*/
U4   u4_g_EvcomDispGetChgSchedSup(void)
{
	U4 u4_t_supbit;							/* support bit			 */
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_chk_res;						/* Check Result			 */
	U1 u1_t_sc;								/* search count			 */
	U1 u1_t_dup_chk[EVCOM_TMCHG_LINK_SIZE];	/* duplication check	 */
	U2 u2_t_rimid;							/* RIM ID				 */
	
	u4_t_supbit = (U4)0;
	vd_EVCOM_MEMFILL_U1(&u1_t_dup_chk[0], (U1)FALSE, (U4)EVCOM_TMCHG_LINK_SIZE);
	u1_t_dup_chk[EVCOM_TMCHG_ID_HEAD] = (U1)TRUE;
	u1_t_id = (U1)EVCOM_TMCHG_ID_HEAD;
	
	for (u1_t_sc = (U1)0; (u1_t_sc < (U1)EVCOM_TMCHG_LINK_SIZE) && (u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE); u1_t_sc++) {
		u1_t_chk_res = u1_s_EvcomChkSchdData(u1_t_id, &u1_t_dup_chk[0]);
		if (u1_t_chk_res != (U1)TRUE) {
			break;
		} else {
			u4_t_supbit |= u4_s_EVCOM_TMSCHD_SUPBIT[u1_t_sc];
			u1_t_dup_chk[u1_t_id] = (U1)TRUE;
			u2_t_rimid = u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id];
			u1_t_id = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_t_rimid, &u1_t_id);
		}
	}
	
	return (u4_t_supbit);
}

/*===================================================================================================================================*/
/* Charge Schedule Initial Select Content                                                                                            */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  select content                                                                                                       */
/*===================================================================================================================================*/
U1   u1_g_EvcomChgSchdInitSel(void)
{
	U1 u1_t_select;							/* Initial select	 */
	U1 u1_t_id;								/* ID				 */
	U1 u1_t_pos;							/* Position			 */
	U1 u1_t_num;							/* Schedule Num		 */
	U1 u1_t_start;							/* Start position	 */
	
	u1_t_id = (U1)EVCOM_P_TMPID_INIT;
	(void)u1_EVCOM_BR_P_TMPID(&u1_t_id);
	u1_t_pos = u1_s_EvcomGetSchdDataPosById(u1_t_id);
	u1_t_num = u1_s_EvcomGetSchdDataNum();
	
	if ((u1_t_pos < (U1)EVCOM_TMCHG_POS_FIRST) ||
	    (u1_t_pos > (U1)EVCOM_TMCHG_POS_MAX)) {
		u1_t_pos = (U1)EVCOM_TMCHG_POS_FIRST;
	}
	
	if ((u1_t_num > (U1)EVCOM_TMCHG_POS_MAX) ||
	    (u1_t_pos < (U1)EVCOM_TMCHG_POS_OFST)) {
		u1_t_select = (U1)EVCOM_TMCHG_SCHD_ADD;
	} else {
		u1_t_start = (U1)EVCOM_TMCHG_POS_MAX - u1_t_num;
		u1_t_select = (u1_t_start + u1_t_pos) - (U1)EVCOM_TMCHG_POS_OFST;
	}
	
	return (u1_t_select);
}

/*===================================================================================================================================*/
/* Initialize Schedule Data                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomInitTmChgSchdData(void)
{
	U1 u1_t_id;								/* ID	 */
	
	for (u1_t_id = (U1)0; u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE; u1_t_id++) {
		(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETID[u1_t_id],  (U1)EVCOM_P_SETID_INIT);
		(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETON[u1_t_id],  (U1)EVCOM_P_SETON_INIT);
		(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETTYP[u1_t_id], (U1)EVCOM_P_SETTYP_INIT);
		(void)u1_EVCOM_BW_U2(u2_s_EVCOM_RIMID_P_SETSTM[u1_t_id], (U2)EVCOM_P_SETSTM_INIT);
		(void)u1_EVCOM_BW_U2(u2_s_EVCOM_RIMID_P_SETFTM[u1_t_id], (U2)EVCOM_P_SETFTM_INIT);
		(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETWKD[u1_t_id], (U1)EVCOM_P_SETWKD_INIT);
		(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id], (U1)EVCOM_P_SETNXT_INIT);
	}
}

/*===================================================================================================================================*/
/* Update : Rx Data (Timer Charge "SET")                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_EvcomUpdateRxDataTmChgSet(void)
{
	U1 u1_t_msgsts1G12;						/* message status : PLG1G12	 */
	U1 u1_t_p_setid;						/* signal : P_SETID			 */
	U1 u1_t_p_seton;						/* signal : P_SETON			 */
	U1 u1_t_p_settyp;						/* signal : P_SETTYP		 */
	U2 u2_t_p_setstm;						/* signal : P_SETSTM		 */
	U2 u2_t_p_setftm;						/* signal : P_SETFTM		 */
	U1 u1_t_p_setwkd;						/* signal : P_SETWKD		 */
	U1 u1_t_p_setnxt;						/* signal : P_SETNXT		 */
	
	u1_t_msgsts1G12 = u1_EVCOM_MSGSTS_PLG1G12() & (U1)((U1)EVCOM_ST_TIMEOUT | (U1)EVCOM_ST_NO_RX);
	if (u1_t_msgsts1G12 == (U1)0) {
		u1_t_p_setid = (U1)EVCOM_P_SETID_INIT;
		vd_EVCOM_GET_P_SETID(&u1_t_p_setid);
		if (u1_t_p_setid < (U1)EVCOM_TMCHG_LINK_SIZE) {
			u1_t_p_seton  = (U1)EVCOM_P_SETON_INIT;
			u1_t_p_settyp = (U1)EVCOM_P_SETTYP_INIT;
			u2_t_p_setstm = (U2)EVCOM_P_SETSTM_INIT;
			u2_t_p_setftm = (U2)EVCOM_P_SETFTM_INIT;
			u1_t_p_setwkd = (U1)EVCOM_P_SETWKD_INIT;
			u1_t_p_setnxt = (U1)EVCOM_P_SETNXT_INIT;
			
			vd_EVCOM_GET_P_SETON(&u1_t_p_seton);
			vd_EVCOM_GET_P_SETTYP(&u1_t_p_settyp);
			vd_EVCOM_GET_P_SETSTM(&u2_t_p_setstm);
			vd_EVCOM_GET_P_SETFTM(&u2_t_p_setftm);
			vd_EVCOM_GET_P_SETWKD(&u1_t_p_setwkd);
			vd_EVCOM_GET_P_SETNXT(&u1_t_p_setnxt);
			
			(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETID[u1_t_p_setid],  u1_t_p_setid);
			(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETON[u1_t_p_setid],  u1_t_p_seton);
			(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETTYP[u1_t_p_setid], u1_t_p_settyp);
			(void)u1_EVCOM_BW_U2(u2_s_EVCOM_RIMID_P_SETSTM[u1_t_p_setid], u2_t_p_setstm);
			(void)u1_EVCOM_BW_U2(u2_s_EVCOM_RIMID_P_SETFTM[u1_t_p_setid], u2_t_p_setftm);
			(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETWKD[u1_t_p_setid], u1_t_p_setwkd);
			(void)u1_EVCOM_BW_U1(u2_s_EVCOM_RIMID_P_SETNXT[u1_t_p_setid], u1_t_p_setnxt);
		}
	} else if ((u1_t_msgsts1G12 & (U1)EVCOM_ST_TIMEOUT) != (U1)0) {
		/* Do Nothing */
	} else {
		/* Do Nothing */
	}
}

/*===================================================================================================================================*/
/* Get Schedule Data ID by Position                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_pos (First position's value is 0.)                                                                     */
/*  Return   :  U1 u1_t_id                                                                                                           */
/*===================================================================================================================================*/
static U1   u1_s_EvcomGetSchdDataIdByPos(const U1 u1_a_pos)
{
	U1 u1_t_jdg_pos;						/* judege position		 */
	U1 u1_t_result_id;						/* Resulet ID			 */
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_chk_res;						/* Check Result			 */
	U1 u1_t_sc;								/* Search count			 */
	U1 u1_t_dup_chk[EVCOM_TMCHG_LINK_SIZE];	/* duplication check	 */
	U2 u2_t_rimid;							/* RIM ID				 */
	
	vd_EVCOM_MEMFILL_U1(&u1_t_dup_chk[0], (U1)FALSE, (U4)EVCOM_TMCHG_LINK_SIZE);
	u1_t_dup_chk[EVCOM_TMCHG_ID_HEAD] = (U1)TRUE;
	u1_t_id = (U1)EVCOM_TMCHG_ID_HEAD;
	u1_t_result_id = (U1)EVCOM_TMCHG_ID_END;
	u1_t_jdg_pos = u1_a_pos + (U1)EVCOM_TMCHG_POS_OFST;
	
	for (u1_t_sc = (U1)0; (u1_t_sc < (U1)EVCOM_TMCHG_LINK_SIZE) && (u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE); u1_t_sc++) {
		u1_t_chk_res = u1_s_EvcomChkSchdData(u1_t_id, &u1_t_dup_chk[0]);
		if (u1_t_chk_res != (U1)TRUE) {
			break;
		} else {
			if (u1_t_jdg_pos == u1_t_sc) {
				u1_t_result_id = u1_t_id;
			}
			u1_t_dup_chk[u1_t_id] = (U1)TRUE;
			u2_t_rimid = u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id];
			u1_t_id = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_t_rimid, &u1_t_id);
		}
	}
	
	return (u1_t_result_id);
}

/*===================================================================================================================================*/
/* Get Schedule Data Position by ID                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  U1 u1_a_id                                                                                                           */
/*  Return   :  U1 u1_t_pos (First position's value is 1. 0:No-schedule or ID error)                                                 */
/*===================================================================================================================================*/
static U1   u1_s_EvcomGetSchdDataPosById(const U1 u1_a_target_id)
{
	U1 u1_t_pos;							/* Position				 */
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_chk_res;						/* Check Result			 */
	U1 u1_t_sc;								/* Search count			 */
	U1 u1_t_dup_chk[EVCOM_TMCHG_LINK_SIZE];	/* duplication check	 */
	U2 u2_t_rimid;							/* RIM ID				 */
	
	vd_EVCOM_MEMFILL_U1(&u1_t_dup_chk[0], (U1)FALSE, (U4)EVCOM_TMCHG_LINK_SIZE);
	u1_t_dup_chk[EVCOM_TMCHG_ID_HEAD] = (U1)TRUE;
	u1_t_id = (U1)EVCOM_TMCHG_ID_HEAD;
	u1_t_pos = (U1)EVCOM_TMCHG_POS_ERROR;
	
	for (u1_t_sc = (U1)0; (u1_t_sc < (U1)EVCOM_TMCHG_LINK_SIZE) && (u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE); u1_t_sc++) {
		u1_t_chk_res = u1_s_EvcomChkSchdData(u1_t_id, &u1_t_dup_chk[0]);
		if (u1_t_chk_res != (U1)TRUE) {
			break;
		} else {
			if (u1_t_id == u1_a_target_id) {
				u1_t_pos = u1_t_sc;
			}
			u1_t_dup_chk[u1_t_id] = (U1)TRUE;
			u2_t_rimid = u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id];
			u1_t_id = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_t_rimid, &u1_t_id);
		}
	}
	
	return (u1_t_pos);
}

/*===================================================================================================================================*/
/* Get Schedule Data Num                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_num                                                                                                          */
/*===================================================================================================================================*/
static U1   u1_s_EvcomGetSchdDataNum(void)
{
	U1 u1_t_num;							/* Schedule Num			 */
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_chk_res;						/* Check Result			 */
	U1 u1_t_sc;								/* Search count			 */
	U1 u1_t_dup_chk[EVCOM_TMCHG_LINK_SIZE];	/* duplication check	 */
	U2 u2_t_rimid;							/* RIM ID				 */
	
	vd_EVCOM_MEMFILL_U1(&u1_t_dup_chk[0], (U1)FALSE, (U4)EVCOM_TMCHG_LINK_SIZE);
	u1_t_dup_chk[EVCOM_TMCHG_ID_HEAD] = (U1)TRUE;
	u1_t_id = (U1)EVCOM_TMCHG_ID_HEAD;
	u1_t_num = (U1)0;
	
	for (u1_t_sc = (U1)0; (u1_t_sc < (U1)EVCOM_TMCHG_LINK_SIZE) && (u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE); u1_t_sc++) {
		u1_t_chk_res = u1_s_EvcomChkSchdData(u1_t_id, &u1_t_dup_chk[0]);
		if (u1_t_chk_res != (U1)TRUE) {
			break;
		} else {
			if (u1_t_id != (U1)EVCOM_TMCHG_ID_HEAD) {
				u1_t_num++;
			}
			u1_t_dup_chk[u1_t_id] = (U1)TRUE;
			u2_t_rimid = u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id];
			u1_t_id = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_t_rimid, &u1_t_id);
		}
	}
	
	return (u1_t_num);
}

/*===================================================================================================================================*/
/* Exist Schedule Data In List                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_target_id                                                                                              */
/*  Return   :  U1 u1_t_exist                                                                                                        */
/*===================================================================================================================================*/
U1   u1_g_EvcomExistSchdData(const U1 u1_a_target_id)
{
	U1 u1_t_exist;							/* Exist				 */
	U1 u1_t_id;								/* ID					 */
	U1 u1_t_chk_res;						/* Check Result			 */
	U1 u1_t_sc;								/* Search count			 */
	U1 u1_t_dup_chk[EVCOM_TMCHG_LINK_SIZE];	/* duplication check	 */
	U2 u2_t_rimid;							/* RIM ID				 */
	
	vd_EVCOM_MEMFILL_U1(&u1_t_dup_chk[0], (U1)FALSE, (U4)EVCOM_TMCHG_LINK_SIZE);
	u1_t_dup_chk[EVCOM_TMCHG_ID_HEAD] = (U1)TRUE;
	u1_t_id = (U1)EVCOM_TMCHG_ID_HEAD;
	u1_t_exist = (U1)FALSE;
	
	for (u1_t_sc = (U1)0; (u1_t_sc < (U1)EVCOM_TMCHG_LINK_SIZE) && (u1_t_id < (U1)EVCOM_TMCHG_LINK_SIZE); u1_t_sc++) {
		u1_t_chk_res = u1_s_EvcomChkSchdData(u1_t_id, &u1_t_dup_chk[0]);
		if (u1_t_chk_res != (U1)TRUE) {
			break;
		} else {
			if (u1_t_id == u1_a_target_id) {
				u1_t_exist = (U1)TRUE;
			}
			u1_t_dup_chk[u1_t_id] = (U1)TRUE;
			u2_t_rimid = u2_s_EVCOM_RIMID_P_SETNXT[u1_t_id];
			u1_t_id = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_t_rimid, &u1_t_id);
		}
	}
	
	return (u1_t_exist);
}

/*===================================================================================================================================*/
/* Get Schedule Data                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_id                                                                                                     */
/*  Return   :  ST_EVCOM_TMCHG_SET st_t_set                                                                                          */
/*===================================================================================================================================*/
static ST_EVCOM_TMCHG_SET st_s_EvcomGetSchdDataById(const U1 u1_a_id)
{
	ST_EVCOM_TMCHG_SET st_t_set;			/* Schedule data	 */
	
	st_t_set.u1_id         = (U1)EVCOM_P_SETID_INIT;
	st_t_set.u1_onoff      = (U1)EVCOM_P_SETON_INIT;
	st_t_set.u1_type       = (U1)EVCOM_P_SETTYP_INIT;
	st_t_set.u2_start_tim  = (U2)EVCOM_P_SETSTM_INIT;
	st_t_set.u2_finish_tim = (U2)EVCOM_P_SETFTM_INIT;
	st_t_set.u1_wkd_bit    = (U1)EVCOM_P_SETWKD_INIT;
	st_t_set.u1_nxt_id     = (U1)EVCOM_P_SETNXT_INIT;
	
	if (u1_a_id < (U1)EVCOM_TMCHG_LINK_SIZE) {
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETID[u1_a_id],  &(st_t_set.u1_id));
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETON[u1_a_id],  &(st_t_set.u1_onoff));
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETTYP[u1_a_id], &(st_t_set.u1_type));
		(void)u1_EVCOM_BR_U2(u2_s_EVCOM_RIMID_P_SETSTM[u1_a_id], &(st_t_set.u2_start_tim));
		(void)u1_EVCOM_BR_U2(u2_s_EVCOM_RIMID_P_SETFTM[u1_a_id], &(st_t_set.u2_finish_tim));
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETWKD[u1_a_id], &(st_t_set.u1_wkd_bit));
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETNXT[u1_a_id], &(st_t_set.u1_nxt_id));
	} else {
		/* Initial value */
	}
	return (st_t_set);
}

/*===================================================================================================================================*/
/* Schedule Data Check                                                                                                               */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  -                                                                                                                    */
/*  Return   :  U1 u1_t_result                                                                                                       */
/*===================================================================================================================================*/
static U1   u1_s_EvcomChkSchdData(const U1 u1_a_id, const U1 * u1_ap_dupchk)
{
	U1 u1_t_result;							/* check result		 */
	U1 u1_t_p_setid;						/* signal : P_SETID	 */
	U1 u1_t_p_setnxt;						/* signal : P_SETNXT */
	
	u1_t_result = (U1)FALSE;
	
	if (u1_a_id < (U1)EVCOM_TMCHG_LINK_SIZE) {
		u1_t_p_setid = (U1)EVCOM_P_SETID_INIT;
		(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETID[u1_a_id],  &u1_t_p_setid);
		if (u1_t_p_setid == u1_a_id) {
			u1_t_p_setnxt = (U1)EVCOM_P_SETNXT_INIT;
			(void)u1_EVCOM_BR_U1(u2_s_EVCOM_RIMID_P_SETNXT[u1_a_id], &u1_t_p_setnxt);
			if (u1_t_p_setnxt == (U1)EVCOM_TMCHG_ID_END) {
				u1_t_result = (U1)TRUE;
			} else if (u1_t_p_setnxt < (U1)EVCOM_TMCHG_LINK_SIZE) {
				if (u1_ap_dupchk[u1_t_p_setnxt] == (U1)FALSE) {
					u1_t_result = (U1)TRUE;
				}
			} else {
				/* NG: Next ID is abnormal. */
			}
		}
	}
	
	return (u1_t_result);
}

/*===================================================================================================================================*/
/* Get Schedule Data ID by Contents                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Arguments:  const U1 u1_a_cntt                                                                                                   */
/*  Return   :  U1 u1_t_id                                                                                                           */
/*===================================================================================================================================*/
U1   u1_g_EvcomGetSchdDataIdByCntt(const U1 u1_a_cntt)
{
	U1 u1_t_pos;							/* Position			 */
	U1 u1_t_num;							/* Schedule Num		 */
	U1 u1_t_start;							/* Start position	 */
	U1 u1_t_id;								/* ID				 */
	
	u1_t_num = u1_s_EvcomGetSchdDataNum();
	u1_t_start = (U1)EVCOM_TMCHG_POS_MAX - u1_t_num;
	u1_t_pos = u1_a_cntt - u1_t_start;
	u1_t_id = u1_s_EvcomGetSchdDataIdByPos(u1_t_pos);
	
	return (u1_t_id);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  ---------------------------------------------------------------------------------------------*/
/*  1.0.0           2018.10.19  KS      New                                                                                          */
/*  1.0.1           2018.11.26  KS      Keeping transition requests is not need.                                                     */
/*  1.1.0           2018.11.26  KS      Receive signals are changed to backup RAM.                                                   */
/*  1.1.1           2018.12.06  KS      Fix : Timeout Judgement                                                                      */
/*  1.1.2           2019.02.22  KS      Add : Comments of variable definitions                                                       */
/*  1.2.0           2019.03.19  KS      Change : Disp State Judge (Charge Limit Setting)                                             */
/*  1.3.0           2020.03.27  KS      Change : CAN API                                                                             */
/*                                                                                                                                   */
/*  * KS = Koichiro Sano, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
