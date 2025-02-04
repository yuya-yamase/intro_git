/* 0.0.19 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hudcom                                                                                                                           */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HCOM_C_MAJOR                      (0)
#define HCOM_C_MINOR                      (0)
#define HCOM_C_PATCH                      (19)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hudcom_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HCOM_C_MAJOR != HCOM_H_MAJOR) || \
	 (HCOM_C_MINOR != HCOM_H_MINOR) || \
	 (HCOM_C_PATCH != HCOM_H_PATCH))
#error "source and header files are inconsistent!"
#endif

#if ((HCOM_C_MAJOR != HCOM_CFG_H_MAJOR) || \
	 (HCOM_C_MINOR != HCOM_CFG_H_MINOR) || \
	 (HCOM_C_PATCH != HCOM_CFG_H_PATCH))
#error "source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* MSC Icon Indication Request State */
#define HCOM_MC_ICON_OFF				(0)
#define HCOM_MC_ICON_ON					(1)
#define HCOM_MC_ICON_FLASH				(2)

/* INFO Icon Indication Request State */
#define HCOM_INFO_ICON_REQ_OFF			(0)
#define HCOM_INFO_ICON_REQ_ON			(1)

/* TbT Interrupt State (Default)      */
#define HCOM_TBT_INT_OFF				(0)

/* Received Value from CAN            */
#define HCOM_NAV_MASK_ON				(1)

/* HUD_PWST Timer Max */
/* 150 = 3000ms / 20ms (Period)  */
#define HCOM_HUD_ON_TIM_MAX				(150)

/* Audio Feedback Interrupt Mask */
#define HCOM_AUD_FB_MASK_OFF			(FALSE)
#define HCOM_AUD_FB_MASK_ON				(TRUE)

/* HUD Soft SW State                  */
#define HCOM_HUD_PWST_BLANK				(0x00)
#define HCOM_HUD_PWST_OFF				(0x01)
#define HCOM_HUD_PWST_ON				(0x02)

#define HCOM_HUDSW_PS_OFF				(0x00)
#define HCOM_HUDSW_PS_ON				(0x01)
#define HCOM_HUDSW_PS_GRY				(0x02)

#define HCOM_HUDSW_RT_OFF				(0x00)
#define HCOM_HUDSW_RT_ON				(0x01)
#define HCOM_HUDSW_RT_GRY				(0x02)

#define HCOM_HUDSW_DC_OFF				(0x00)
#define HCOM_HUDSW_DC_ON				(0x01)
#define HCOM_HUDSW_DC_GRY				(0x02)

#define HCOM_HUDSW_PW_OFF				(0x00)
#define HCOM_HUDSW_PW_ON				(0x01)

#define HCOM_HUDBRMAX_OFF				(0x00)

#define HCOM_HUDBR_OFF					(0x00)

#define HCOM_CTTACEXT_OFF				(0x00)
#define HCOM_CTTACEXT_ECO				(0x01)
#define HCOM_CTTACEXT_HYBSYS			(0x02)

#define HCOM_CTNAVEXT_OFF				(0x00)
#define HCOM_CTNAVEXT_ON				(0x01)

#define HCOM_CTADSEXT_OFF				(0x00)
#define HCOM_CTADSEXT_ON				(0x01)

#define HCOM_CTCMPEXT_OFF				(0x00)
#define HCOM_CTCMPEXT_ON				(0x01)

#define HCOM_CTAUDEXT_OFF				(0x00)
#define HCOM_CTAUDEXT_ON				(0x01)

#define HCOM_CTLANEXT_OFF				(0x00)
#define HCOM_CTLANEXT_ON				(0x01)

#define HCOM_CTTACST_UNKNOWN			(0x00)
#define HCOM_CTTACST_OFF				(0x01)
#define HCOM_CTTACST_HYBSYS				(0x02)
#define HCOM_CTTACST_ECO				(0x03)
#define HCOM_CTTACST_TACHO				(0x04)

#define HCOM_CTNAVST_BLANK				(0x00)
#define HCOM_CTNAVST_DISP_OFF			(0x01)
#define HCOM_CTNAVST_DISP_ON			(0x02)

#define HCOM_CTADSST_BLANK				(0x00)
#define HCOM_CTADSST_DISP_OFF			(0x01)
#define HCOM_CTADSST_DISP_ON			(0x02)

#define HCOM_CTCMPST_BLANK				(0x00)
#define HCOM_CTCMPST_DISP_OFF			(0x01)
#define HCOM_CTCMPST_DISP_ON			(0x02)

#define HCOM_CTAUDST_BLANK				(0x00)
#define HCOM_CTAUDST_DISP_OFF			(0x01)
#define HCOM_CTAUDST_DISP_ON			(0x02)

#define HCOM_CTLANST_BLANK				(0x00)
#define HCOM_CTLANST_DISP_OFF			(0x01)
#define HCOM_CTLANST_DISP_ON			(0x02)

#define HCOM_MSGSTS_DEFAULT				(HCOM_ST_TIMEOUT | HCOM_ST_NO_RX)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static	U1	u1_s_hcom_hud_on_tim;
static	U1	u1_s_hcom_aud_fb_mask;

static	U1	u1_s_hcom_hud_pwst;
static	U1	u1_s_hcom_hudsw_ps;
static	U1	u1_s_hcom_hudsw_rt;
static	U1	u1_s_hcom_hudsw_dc;
static	U1	u1_s_hcom_hudsw_pw;
static	U1	u1_s_hcom_hudbrmax;
static	U1	u1_s_hcom_hudbr;
static	U1	u1_s_hcom_cttacext;
static	U1	u1_s_hcom_ctnavext;
static	U1	u1_s_hcom_ctadsext;
static	U1	u1_s_hcom_ctcmpext;
static	U1	u1_s_hcom_ctaudext;
static	U1	u1_s_hcom_ctlanext;
static	U1	u1_s_hcom_cttacst;
static	U1	u1_s_hcom_ctnavst;
static	U1	u1_s_hcom_ctadsst;
static	U1	u1_s_hcom_ctcmpst;
static	U1	u1_s_hcom_ctaudst;
static	U1	u1_s_hcom_ctlanst;

static	U1	u1_s_hcom_msgsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Elements of fp_TBL_HCOM_CAL_FUNC */
static U1 u1_s_HcomJdgAdjust(void);
static U1 u1_s_HcomJdgMnsw(void);
static U1 u1_s_HcomJdgCstm(void);
static U1 u1_s_HcomJdgTcset(void);
static U1 u1_s_HcomJdgTcsetEco(void);
static U1 u1_s_HcomJdgTcsetHv(void);
static U1 u1_s_HcomJdgNav(void);
static U1 u1_s_HcomJdgAds(void);
static U1 u1_s_HcomJdgCmp(void);
static U1 u1_s_HcomJdgAud(void);
static U1 u1_s_HcomJdgLan(void);
static U1 u1_s_HcomJdgRotadj(void);

/* Correspond to Order of hudcom.h::EN_HCOM_SETCNTT_STS */
static U1 (* const fp_TBL_HCOM_CAL_FUNC[EN_HCOM_SETCNTT_STS_TOTAL])(void) = {
	&u1_s_HcomJdgAdjust,
	&u1_s_HcomJdgMnsw,
	&u1_s_HcomJdgCstm,
	&u1_s_HcomJdgTcset,
	&u1_s_HcomJdgTcsetEco,
	&u1_s_HcomJdgTcsetHv,
	&u1_s_HcomJdgNav,
	&u1_s_HcomJdgAds,
	&u1_s_HcomJdgCmp,
	&u1_s_HcomJdgAud,
	&u1_s_HcomJdgLan,
	&u1_s_HcomJdgRotadj
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_HcomInit(void);
static U1   u1_s_HcomWrnSet(void);
static U1   u1_s_HcomInfIcnSet(void);
static void vd_s_HcomSndCan(void);
static void vd_s_HcomSetMask(void);
static void vd_s_HcomSetAudioFBMask(void);
static void vd_s_HcomGetSig(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  Battery First Connect Initialization                                                                                             */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_HcomBon(void)
{
	/* Init CAN Communication */
	U1 u1_t_mstcsts;
	U1 u1_t_infsts;
	U1 u1_t_tbtintsts;

	u1_t_mstcsts = (U1)HCOM_MC_ICON_OFF;
	u1_t_infsts = (U1)HCOM_INFO_ICON_REQ_OFF;
	u1_t_tbtintsts = (U1)HCOM_TBT_INT_OFF;
	/* Write to RIM */
    vd_HCOM_RIM_WR_NAV_MASK((U1)FALSE);

    vd_HCOM_MCICONRQ_WRITE_IMM(&u1_t_mstcsts);
    vd_HCOM_IFICONRQ_WRITE_IMM(&u1_t_infsts);
    vd_HCOM_TBTINT_WRITE_IMM(&u1_t_tbtintsts);

	vd_s_HcomInit();
}

/*===================================================================================================================================*/
/*  Wake Up Initialization                                                                                                           */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_HcomWakeup(void)
{
	/* Init CAN Communication */
	U1 u1_t_mstcsts;
	U1 u1_t_infsts;
	U1 u1_t_tbtintsts;

	u1_t_mstcsts = (U1)HCOM_MC_ICON_OFF;
	u1_t_infsts = (U1)HCOM_INFO_ICON_REQ_OFF;
	u1_t_tbtintsts = (U1)HCOM_TBT_INT_OFF;

    vd_HCOM_MCICONRQ_WRITE_IMM(&u1_t_mstcsts);
    vd_HCOM_IFICONRQ_WRITE_IMM(&u1_t_infsts);
    vd_HCOM_TBTINT_WRITE_IMM(&u1_t_tbtintsts);

	vd_s_HcomInit();
}

/*===================================================================================================================================*/
/*  Ignition Status OFF->ON Change Event                                                                                             */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_HcomIgon(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
	/* Init CAN Communication */
	U1 u1_t_mstcsts;
	U1 u1_t_infsts;
	U1 u1_t_tbtintsts;

	u1_t_mstcsts = (U1)HCOM_MC_ICON_OFF;
	u1_t_infsts = (U1)HCOM_INFO_ICON_REQ_OFF;
	u1_t_tbtintsts = (U1)HCOM_TBT_INT_OFF;

    vd_HCOM_MCICONRQ_WRITE_IMM(&u1_t_mstcsts);
    vd_HCOM_IFICONRQ_WRITE_IMM(&u1_t_infsts);
    vd_HCOM_TBTINT_WRITE_IMM(&u1_t_tbtintsts);

	vd_s_HcomInit();
}

/*===================================================================================================================================*/
/*  Ignition Status ON->OFF Change Event                                                                                             */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_HcomIgoff(const U4 u4_a_MDBIT, const U4 u4_a_EVTBIT)
{
	/* NOP */
}

/*===================================================================================================================================*/
/*  Speed Controller Internal Variables Initialization                                                                               */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HcomInit(void)
{
	/* Init HUD On Timer */
	u1_s_hcom_hud_on_tim = (U1)0;
	
	/* Init Audio Feedback Interrupt Mask */
	u1_s_hcom_aud_fb_mask = (U1)HCOM_AUD_FB_MASK_OFF;
	
	/* Init HUD Soft SW */
	u1_s_hcom_hud_pwst = (U1)HCOM_HUD_PWST_BLANK;
	u1_s_hcom_hudsw_ps = (U1)HCOM_HUDSW_PS_OFF;
	u1_s_hcom_hudsw_rt = (U1)HCOM_HUDSW_RT_OFF;
	u1_s_hcom_hudsw_dc = (U1)HCOM_HUDSW_DC_OFF;
	u1_s_hcom_hudsw_pw = (U1)HCOM_HUDSW_PW_OFF;
	u1_s_hcom_hudbrmax = (U1)HCOM_HUDBRMAX_OFF;
	u1_s_hcom_hudbr = (U1)HCOM_HUDBR_OFF;
	u1_s_hcom_cttacext = (U1)HCOM_CTTACEXT_OFF;
	u1_s_hcom_ctnavext = (U1)HCOM_CTNAVEXT_OFF;
	u1_s_hcom_ctadsext = (U1)HCOM_CTADSEXT_OFF;
	u1_s_hcom_ctcmpext = (U1)HCOM_CTCMPEXT_OFF;
	u1_s_hcom_ctaudext = (U1)HCOM_CTAUDEXT_OFF;
	u1_s_hcom_ctlanext = (U1)HCOM_CTLANEXT_OFF;
	u1_s_hcom_cttacst = (U1)HCOM_CTTACST_UNKNOWN;
	u1_s_hcom_ctnavst = (U1)HCOM_CTNAVST_BLANK;
	u1_s_hcom_ctadsst = (U1)HCOM_CTADSST_BLANK;
	u1_s_hcom_ctcmpst = (U1)HCOM_CTCMPST_BLANK;
	u1_s_hcom_ctaudst = (U1)HCOM_CTAUDST_BLANK;
	u1_s_hcom_ctlanst = (U1)HCOM_CTLANST_BLANK;
	
	u1_s_hcom_msgsts = (U1)HCOM_MSGSTS_DEFAULT;
	vd_g_HudCstmStsInit();
}

/*===================================================================================================================================*/
/*  Hudcom Fixed Task Called by sysmgr at 20ms Task                                                                                  */
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_HcomRoutine(void)
{
	U1 u1_t_igon;
	
	u1_t_igon = u1_HCOM_GETIG();
	
	if(u1_t_igon == (U1)TRUE){
		/* MSC Icon Indication Request  */
		/* INFO Icon Indication Request */
		vd_s_HcomSndCan();
	
		/* Receive CAN                  */
		u1_s_hcom_msgsts = u1_HCOM_CANMSGSTS_HUDSTS();
		
		/* Interrupt Mask Request       */
		vd_s_HcomSetMask();
		
		/* Get HUD Soft SW Signal       */
		vd_s_HcomGetSig();
		
		/* Audio Feedback Interrupt Mask Request */
		vd_s_HcomSetAudioFBMask();
		vd_g_HudCstmStsRoutine();
	}
	else
	{
		vd_s_HcomInit();
	}
}

/*===================================================================================================================================*/
/*  Hudcom : CAN transmission                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HcomSndCan(void)
{
	U1 u1_t_mstcsts;
	U1 u1_t_infsts;
	U1 u1_t_tbtintsts;

	/* MSC Icon Indication Request  */
	u1_t_mstcsts = u1_s_HcomWrnSet();

	/* INFO Icon Indication Request */
	u1_t_infsts = u1_s_HcomInfIcnSet();
	
	/* TbT Interrupt Display        */
	u1_t_tbtintsts = u1_HCOM_GET_TBT_INT_SUP();
	
	/* Transmit CAN                 */
	vd_HCOM_MCICONRQ_WRITE(&u1_t_mstcsts);
	vd_HCOM_IFICONRQ_WRITE(&u1_t_infsts);
	vd_HCOM_TBTINT_WRITE(&u1_t_tbtintsts);
}

/*===================================================================================================================================*/
/*  Hudcom : WRN Information Setting for HUD                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         MSC Icon Indication Request for HUD                                                                              */
/*===================================================================================================================================*/
static U1 u1_s_HcomWrnSet(void)
{
    U1 u1_t_mstcsts;
    U1 u1_t_ret;

    u1_t_mstcsts = u1_HCOM_GETMSTWRN();
    u1_t_ret = (U1)HCOM_MC_ICON_OFF;

    if(u1_t_mstcsts == (U1)HCOM_MC_STS_ON){
        u1_t_ret = (U1)HCOM_MC_ICON_ON;
    }
	else if((u1_t_mstcsts == (U1)HCOM_MC_STS_FLASH1) ||
		(u1_t_mstcsts == (U1)HCOM_MC_STS_FLASH2) || 
		(u1_t_mstcsts == (U1)HCOM_MC_STS_FLASH3))
	{
		u1_t_ret = (U1)HCOM_MC_ICON_FLASH;
	}
	else
	{
		/* NOP: QAC Measures */
	}
	
	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  Hudcom : INFO Icon Information Setting for HUD                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         INFO Icon Indication Request for HUD                                                                             */
/*===================================================================================================================================*/
static U1 u1_s_HcomInfIcnSet(void)
{
    U1 u1_t_ret;
	U1 u1_t_cntt;

	u1_t_cntt = u1_HCOM_GETCNTT();
    u1_t_ret = (U1)HCOM_INFO_ICON_REQ_OFF;

    if(u1_t_cntt == (U1)HCOM_DSPCNTT_PRPS){
        u1_t_ret = (U1)HCOM_INFO_ICON_REQ_ON;
    }
	
	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  Hudcom : Interrupt Mask Request                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HcomSetMask(void)
{
	U1 u1_t_msgsts;
	U1 u1_t_navmask_rim;
	U1 u1_t_navmask_can;
	
	u1_t_msgsts = u1_s_hcom_msgsts & (U1)(HCOM_ST_TIMEOUT | HCOM_ST_NO_RX);
	/* Normal Reception */
	if(u1_t_msgsts == (U1)0)
	{
		vd_HCOM_CANSGNL_NAV_MASK(&u1_t_navmask_can);
		if(u1_t_navmask_can == (U1)HCOM_NAV_MASK_ON)
		{
			u1_t_navmask_rim = (U1)TRUE;
		}
		else
		{
			u1_t_navmask_rim = (U1)FALSE;
		}
		vd_HCOM_RIM_WR_NAV_MASK(u1_t_navmask_rim);
	}
	/* Disruption      */
	else if((u1_t_msgsts & (U1)HCOM_ST_TIMEOUT) != (U1)0)
	{
		vd_HCOM_RIM_WR_NAV_MASK((U1)FALSE);
	}
	/* Not Received    */
	else if((u1_t_msgsts & (U1)HCOM_ST_NO_RX) != (U1)0)
	{
		/* NOP */
	}
	else
	{
		/* NOP: QAC Measures */
	}
}

/*===================================================================================================================================*/
/*  Hudcom : Audio Feedback Interrupt Mask Request                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_HcomSetAudioFBMask(void)
{
	u1_s_hcom_aud_fb_mask = (U1)HCOM_AUD_FB_MASK_OFF;

	if(u1_s_hcom_hud_pwst == (U1)HCOM_HUD_PWST_ON)
	{
		if((u1_s_hcom_hud_on_tim >= (U1)HCOM_HUD_ON_TIM_MAX)
		 &&(u1_s_hcom_ctaudst == (U1)HCOM_CTAUDST_DISP_ON))
		{
			u1_s_hcom_aud_fb_mask = (U1)HCOM_AUD_FB_MASK_ON;
		}
		if(u1_s_hcom_hud_on_tim >= (U1)U1_MAX)
		{
			u1_s_hcom_hud_on_tim = (U1)U1_MAX;
		}
		else
		{
			u1_s_hcom_hud_on_tim += (U1)1;
		}
	}
	else
	{
		u1_s_hcom_hud_on_tim = (U1)0;
	}
}

/*===================================================================================================================================*/
/*	Hudcom : Acquisition of HUD Soft SW Signal																						 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*	Return: 		-																												 */
/*===================================================================================================================================*/
static void vd_s_HcomGetSig(void)
{
	U1 u1_t_msgsts;
	
	u1_t_msgsts = u1_s_hcom_msgsts & (U1)(HCOM_ST_TIMEOUT | HCOM_ST_NO_RX);
	/* Normal Reception */
	if(u1_t_msgsts == (U1)0){
    vd_HCOMRX_GET_HUD_PWST(&u1_s_hcom_hud_pwst);
    vd_HCOMRX_GET_HUDSW_PS(&u1_s_hcom_hudsw_ps);
    vd_HCOMRX_GET_HUDSW_RT(&u1_s_hcom_hudsw_rt);
    vd_HCOMRX_GET_HUDSW_DC(&u1_s_hcom_hudsw_dc);
    vd_HCOMRX_GET_HUDSW_PW(&u1_s_hcom_hudsw_pw);
    vd_HCOMRX_GET_HUDBRMAX(&u1_s_hcom_hudbrmax);
    vd_HCOMRX_GET_HUDBR(&u1_s_hcom_hudbr);
    vd_HCOMRX_GET_CTTACEXT(&u1_s_hcom_cttacext);
    vd_HCOMRX_GET_CTNAVEXT(&u1_s_hcom_ctnavext);
    vd_HCOMRX_GET_CTADSEXT(&u1_s_hcom_ctadsext);
    vd_HCOMRX_GET_CTCMPEXT(&u1_s_hcom_ctcmpext);
    vd_HCOMRX_GET_CTAUDEXT(&u1_s_hcom_ctaudext);
    vd_HCOMRX_GET_CTLANEXT(&u1_s_hcom_ctlanext);
    vd_HCOMRX_GET_CTTACST(&u1_s_hcom_cttacst);
    vd_HCOMRX_GET_CTNAVST(&u1_s_hcom_ctnavst);
    vd_HCOMRX_GET_CTADSST(&u1_s_hcom_ctadsst);
    vd_HCOMRX_GET_CTCMPST(&u1_s_hcom_ctcmpst);
    vd_HCOMRX_GET_CTAUDST(&u1_s_hcom_ctaudst);
    vd_HCOMRX_GET_CTLANST(&u1_s_hcom_ctlanst);
	}
	/* Disruption      */
	else if((u1_t_msgsts & (U1)HCOM_ST_TIMEOUT) != (U1)0)
	{
		u1_s_hcom_hud_pwst = (U1)HCOM_HUD_PWST_BLANK;
		u1_s_hcom_hudbr = (U1)HCOM_HUDBR_OFF;
		u1_s_hcom_cttacst = (U1)HCOM_CTTACST_UNKNOWN;
		u1_s_hcom_ctnavst = (U1)HCOM_CTNAVST_BLANK;
		u1_s_hcom_ctadsst = (U1)HCOM_CTADSST_BLANK;
		u1_s_hcom_ctcmpst = (U1)HCOM_CTCMPST_BLANK;
		u1_s_hcom_ctaudst = (U1)HCOM_CTAUDST_BLANK;
		u1_s_hcom_ctlanst = (U1)HCOM_CTLANST_BLANK;
	}
	/* Not Received    */
	else if((u1_t_msgsts & (U1)HCOM_ST_NO_RX) != (U1)0)
	{
		vd_s_HcomInit();
	}
	else
	{
		vd_s_HcomInit();
	}
}

/*===================================================================================================================================*/
/*	Hudcom : Notification of Customize Contents State																				 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*	Return: 		-																												 */
/*===================================================================================================================================*/
U1	u1_g_HcomGetCstmCnttSts(U1 u1_t_cntt)
{
	U1 u1_t_ret;
	U1 (*	const	*	fp_t_getcnttsts)(void);

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;

	if(u1_t_cntt < (U1)EN_HCOM_SETCNTT_STS_TOTAL)
	{
		fp_t_getcnttsts = &fp_TBL_HCOM_CAL_FUNC[u1_t_cntt];
		if(vdp_PTR_NA != (*fp_t_getcnttsts))
		{
			u1_t_ret = (*fp_t_getcnttsts)();
		}
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  Hudcom : Notificationce of Navi Interrupt Mask Request                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         FALSE(No mask) / TRUE(Mask)                                                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomNavmask(void)
{
    U1 u1_t_rim_sts;      /* RIM読み出し状態 */
    U1 u1_t_navmask_rim;

    u1_t_rim_sts = u1_HCOM_RIM_RD_NAV_MASK(&u1_t_navmask_rim);

    if((u1_t_rim_sts & (U1)HCOM_RIM_STATUS_MASK) != (U1)HCOM_RIM_READ_OK) {  /* RIM Error */
        u1_t_navmask_rim = (U1)FALSE;
    }

	return(u1_t_navmask_rim);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "HUD position control"													 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return          HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgAdjust(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if(u1_s_hcom_hudsw_ps == (U1)HCOM_HUDSW_PS_ON)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if(u1_s_hcom_hudsw_ps == (U1)HCOM_HUDSW_PS_GRY)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "HUD On/Off control"													 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgMnsw(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if(u1_s_hcom_hudsw_pw == (U1)HCOM_HUDSW_PW_ON)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	
	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "HUD display customizing"												 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgCstm(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if(u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if(u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Tacho setting"															 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgTcset(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if(u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	{
		if((u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_ECO)
		 ||(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_HYBSYS))
		{
			u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
		}
	}
	else if(u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
	{
		if((u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_ECO)
		 ||(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_HYBSYS))
		{
			u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
		}
	}
	else 
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Tacho setting (Eco bar)"												 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgTcsetEco(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_ECO))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_ECO))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Tacho setting (Hybsys)"												 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgTcsetHv(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_HYBSYS))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_cttacext == (U1)HCOM_CTTACEXT_HYBSYS))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Navigation customizing"												 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgNav(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_ctnavext == (U1)HCOM_CTNAVEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_ctnavext == (U1)HCOM_CTNAVEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "ADAS customizing"														 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgAds(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_ctadsext == (U1)HCOM_CTADSEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_ctadsext == (U1)HCOM_CTADSEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Compass customizing"													 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgCmp(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_ctcmpext == (U1)HCOM_CTCMPEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_ctcmpext == (U1)HCOM_CTCMPEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else 
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Audio feedback customizing"											 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgAud(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_ctaudext == (U1)HCOM_CTAUDEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_ctaudext == (U1)HCOM_CTAUDEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "Lane display customizing"												 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgLan(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_ON)
	 &&(u1_s_hcom_ctlanext == (U1)HCOM_CTLANEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if((u1_s_hcom_hudsw_dc == (U1)HCOM_HUDSW_DC_GRY)
		  &&(u1_s_hcom_ctlanext == (U1)HCOM_CTLANEXT_ON))
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*	Hudcom :  Acquisition of Customizing Contents Status at "HUD display rotate control"											 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*	Arguments:		-																												 */
/*  Return:         HCOM_SET_CNTTSTS_OFF (No display) / HCOM_SET_CNTTSTS_ON (Display) / HCOM_SET_CNTTSTS_GRY (Gray out)              */
/*===================================================================================================================================*/
static U1 u1_s_HcomJdgRotadj(void)
{
	U1	u1_t_ret;

	u1_t_ret = (U1)HCOM_SET_CNTTSTS_OFF;
	if(u1_s_hcom_hudsw_rt == (U1)HCOM_HUDSW_RT_ON)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_ON;
	}
	else if(u1_s_hcom_hudsw_rt == (U1)HCOM_HUDSW_RT_GRY)
	{
		u1_t_ret = (U1)HCOM_SET_CNTTSTS_GRY;
	}
	else
	{
		/* NOP: QAC Measures */
	}

	return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  Hudcom : Notificationce of Audio Feedback Interrupt Mask Request                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         FALSE(No mask) / TRUE(Mask)                                                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomAudioFBmask(void)
{
	return((U1)HCOM_AUD_FB_MASK_OFF);/* 345D369D not support */
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Power Supply Status                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUD_PWST_OFF (Power OFF) / HCOM_HUD_PWST_ON (Power ON)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetPowerSts(void)
{
	return(u1_s_hcom_hud_pwst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Position Control Existence                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDSW_PS_OFF (No display) / HCOM_HUDSW_PS_ON (Display) / HCOM_HUDSW_PS_GRY (Gray out)                       */
/*===================================================================================================================================*/
U1 u1_g_HcomGetSwPos(void)
{
	return(u1_s_hcom_hudsw_ps);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Display Customizing Existence                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDSW_RT_OFF (No display) / HCOM_HUDSW_RT_ON (Display) / HCOM_HUDSW_RT_GRY (Gray out)                       */
/*===================================================================================================================================*/
U1 u1_g_HcomGetSwRot(void)
{
	return(u1_s_hcom_hudsw_rt);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Display Customizing Existence                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDSW_DC_OFF (No display) / HCOM_HUDSW_DC_ON (Display) / HCOM_HUDSW_DC_GRY (Gray out)                       */
/*===================================================================================================================================*/
U1 u1_g_HcomGetSwDsp(void)
{
	return(u1_s_hcom_hudsw_dc);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD On/Off Control Existence                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDSW_PW_OFF (No display) / HCOM_HUDSW_PW_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetSwPow(void)
{
	return(u1_s_hcom_hudsw_pw);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Brightness Max                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDBRMAX_OFF (Unknown) / Valid Value                                                                        */
/*===================================================================================================================================*/
U1 u1_g_HcomGetBrightnessMax(void)
{
	return(u1_s_hcom_hudbrmax);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Brightness                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_HUDBR_OFF (Unknown) / Valid Value                                                                           */
/*===================================================================================================================================*/
U1 u1_g_HcomGetBrightness(void)
{
	return(u1_s_hcom_hudbr);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Tachometer Switchover Existence                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTTACEXT_OFF (No display) / HCOM_CTTACEXT_ECO (Eco drive indicator) /                                       */
/*                  HCOM_CTTACEXT_HYBSYS (HV system indicator)                                                                       */
/*===================================================================================================================================*/
U1 u1_g_HcomGetTacExt(void)
{
	return(u1_s_hcom_cttacext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Navigation Customizing Existence                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTNAVEXT_OFF (No display) / HCOM_CTNAVEXT_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetNavExt(void)
{
	return(u1_s_hcom_ctnavext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD ADAS Customizing Existence                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTADSEXT_OFF (No display) / HCOM_CTADSEXT_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetAdsExt(void)
{
	return(u1_s_hcom_ctadsext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Compass Customizing Existence                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTCMPEXT_OFF (No display) / HCOM_CTCMPEXT_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetCmpExt(void)
{
	return(u1_s_hcom_ctcmpext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Audio Feedback Customizing Existence                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTAUDEXT_OFF (No display) / HCOM_CTAUDEXT_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetAudExt(void)
{
	return(u1_s_hcom_ctaudext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Lane Display Customizing Existence                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTLANEXT_OFF (No display) / HCOM_CTLANEXT_ON (Display)                                                      */
/*===================================================================================================================================*/
U1 u1_g_HcomGetLanExt(void)
{
	return(u1_s_hcom_ctlanext);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Tacho-area Display Status                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTTACST_UNKNOWN (Undefined) / HCOM_CTTACST_OFF(No display) / HCOM_CTTACST_HYBSYS (HV system indicator) /    */
/*                  HCOM_CTTACST_ECO (Eco drive indicator) /  HCOM_CTTACST_TACHO (Tacho)                                             */
/*===================================================================================================================================*/
U1 u1_g_HcomGetTacSts(void)
{
	return(u1_s_hcom_cttacst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Navi Customizing Status                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTNAVST_BLANK (No display) / HCOM_CTNAVST_DISP_OFF (Display "OFF") / HCOM_CTNAVST_DISP_ON (Display "ON")    */
/*===================================================================================================================================*/
U1 u1_g_HcomGetNavSts(void)
{
	return(u1_s_hcom_ctnavst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD ADAS Customizing Status                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTADSST_BLANK (No display) / HCOM_CTADSST_DISP_OFF (Display "OFF") / HCOM_CTADSST_DISP_ON (Display "ON")    */
/*===================================================================================================================================*/
U1 u1_g_HcomGetAdsSts(void)
{
	return(u1_s_hcom_ctadsst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Compass Customizing Status                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTCMPST_BLANK (No display) / HCOM_CTCMPST_DISP_OFF (Display "OFF") / HCOM_CTCMPST_DISP_ON (Display "ON")    */
/*===================================================================================================================================*/
U1 u1_g_HcomGetCmpSts(void)
{
	return(u1_s_hcom_ctcmpst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Audio Feedback Customizing Status                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTAUDST_BLANK (No display) / HCOM_CTAUDST_DISP_OFF (Display "OFF") / HCOM_CTAUDST_DISP_ON (Display "ON")    */
/*===================================================================================================================================*/
U1 u1_g_HcomGetAudSts(void)
{
	return(u1_s_hcom_ctaudst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of HUD Lane Display Customizing Status                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         HCOM_CTLANST_BLANK (No display) / HCOM_CTLANST_DISP_OFF (Display "OFF") / HCOM_CTLANST_DISP_ON (Display "ON")    */
/*===================================================================================================================================*/
U1 u1_g_HcomGetLanSts(void)
{
	return(u1_s_hcom_ctlanst);
}

/*===================================================================================================================================*/
/*  Hudcom : Notification of CAN Message Status about HUD                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         CAN Message Status                                                                                               */
/*===================================================================================================================================*/
U1 u1_g_HcomGetCanMsgSts(void)
{
	return(u1_s_hcom_msgsts);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  0.0.0           2015.11.26   YN      New                                                                                         */
/*  0.0.1           2015.12.04   YN      * Addition of CAN transmission initialization                                               */
/*                                       * Deletion of HUD indication vehicle speed output (shift to Speed domain)                   */
/*  0.0.2           2015.12.07   YN      * Change of module name (hcom -> hudcom)                                                    */
/*                                       * Deletion interim source codes                                                             */
/*                                       * Correction of timing to write to RIM (IG-ON -> initial)                                   */
/*                                       * Correction of Rx of NAV_MASK from the interim of the official                             */
/*  0.0.3           2015.12.10   YN      Correction of handling of calling vd_g_HcomInit() and writing to RIM order in vd_g_HcomBon()*/
/*  0.0.4           2015.12.12   YN      Correspondence to ACC/LKA interrupt mask                                                    */
/*  0.0.5           2016.01.08   YN      * Translation of comment from Japanese to English                                           */
/*                                       * Measure to QAC warning                                                                    */
/*                                         * Translation of comment from Japanese to English                                         */
/*                                         * Deletion of variable initialization                                                     */
/*                                         * Addition of else statement                                                              */
/*                                         * Correction of number of ()                                                              */
/*                                       * Change of filename (hudcom.prm -> hudcom_cfg.h)                                           */
/*  0.0.6           2016.01.26   YN      * Addition of fail processing                                                               */
/*  0.0.7           2016.02.16   YN      * Change of how to use RIM                                                                  */
/*                                       * Devide fail processing unreceived and disruption                                          */
/*  0.0.8           2016.02.29   YN      * Delete of control on IG-OFF                                                               */
/*  0.0.9           2016.03.21   YN      * Addition of control of HUD soft SW                                                        */
/*                                       * Correction of comments                                                                    */
/*                                       * Deletion ACC/LKA interrupt mask                                                           */
/*  0.0.10          2016.03.28   YN      * Deletion of unnecessary "else"                                                            */
/*                                       * Minor modifications of variable/function name                                             */
/*                                       * Change of how to use function pointer                                                     */
/*  0.0.11          2016.03.29   YN      * Change of "else" control of vd_s_HcomGetSig()                                             */
/*  0.0.12          2016.04.18   YN      * Change of HUD_PWST value in disruption                                                    */
/*  0.0.13          2016.06.22   YN      * Addition of TbT interrupt customizing status transmission                                 */
/*  0.0.14          2016.09.15   YN      * Addition of audio feedback interrupt mask notification                                    */
/*  0.0.15          2016.10.11   YN      * Measure to QAC warning                                                                    */
/*                                         * Correction listed ";" and comment                                                       */
/*                                         * Correction of number of () at "if" clause                                               */
/*  0.0.16          2016.10.21   YN      * Minor modifications of unrelated code from behvior                                        */
/*                                         * Deletion ternary operator                                                               */
/*                                         * Change of value of HCOM_MSGSTS_DEFAULT                                                  */
/*                                         * Correction of comments                                                                  */
/*  0.0.17          2017.05.24   YN      * Change of vd_g_HcomInit(), vd_g_HcomBon(), vd_g_HcomWakeup() and vd_g_HcomIgon()          */
/*  0.0.18          2017.08.03   SM      * Change of the Macroname in hudcom.h (HUDCOM_* -> HCOM_*)                                  */
/*  0.0.19          2018.07.27   TH      * ナビ割り込みマスク有無のRIM読み出し異常時の動作追加                                       */
/*                                                                                                                                   */
/*  * YN = Yousuke Nakashima, DENSO                                                                                                  */
/*  * SM = Shota Maegawa, Denso Techno                                                                                               */
/*  * TH = Taisuke Hirakawa                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/
