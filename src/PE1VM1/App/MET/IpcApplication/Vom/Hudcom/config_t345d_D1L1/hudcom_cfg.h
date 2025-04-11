/* 0.0.19 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hudcom                                                                                                                           */
/*===================================================================================================================================*/

#ifndef HCOM_CFG_H
#define HCOM_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HCOM_CFG_H_MAJOR                    (0)
#define HCOM_CFG_H_MINOR                    (0)
#define HCOM_CFG_H_PATCH                    (19)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include File                                                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* ! Caution for cross-reference with Vardef domain ! */
#include "aip_common.h"
#include "xspi_met_ch0.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

#include "vardef_esopt.h"
#include "mcst.h"

#include "hudcom.h"
#include "hudcstmsup.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type definition                                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HCOM_ST_TIMEOUT					(COM_TIMEOUT)
#define HCOM_ST_NO_RX					(COM_NO_RX)

#define HCOM_MC_STS_OFF					(0)
#define HCOM_MC_STS_ON					(1)
#define HCOM_MC_STS_FLASH1				(2)
#define HCOM_MC_STS_FLASH2				(3)
#define HCOM_MC_STS_FLASH3				(4)

#define HCOM_DSPCNTT_PRPS				(4)  /* DSPCNTT_PRPS */
#define HCOM_VOM_SHIFT                  (1U)
#define HCOM_HUD1S01_TO_THRSH           (5000U / OXCAN_MAIN_TICK)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV BSW provisionally */
#define u1_HCOM_GETIG()					((U1)((u4_g_VehopemdMdfield()&(U4)VEH_OPEMD_MDBIT_IGN)>>HCOM_VOM_SHIFT))           /* IG                             */ 
#else
#define u1_HCOM_GETIG()					((U1)((u4_g_VehopemdConvertMdfield()&(U4)VEH_OPEMD_MDBIT_IGN)>>HCOM_VOM_SHIFT))           /* IG                             */ 
#endif
#define u1_HCOM_GETMSTWRN()				(u1_g_XSpiCfgRxMstTtSts())                          /* MTC Disp Req                 */
#define u1_HCOM_GETCNTT()				(u1_g_XSpiGetDspSTM00Cntt())               /* DSP_STM00_CNTT       */
#define vd_HCOM_CANSGNL_NAV_MASK(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_NAV_MASK,  (x)))
#define u1_HCOM_GET_TBT_INT_SUP()		(u1_g_VardefEsOptAvaByCh(VDF_ESO_CH_MM_NAVI) & u1_g_McstBf(MCST_BFI_CROSS_ADV))
#define u1_HCOM_CANMSGSTS_HUDSTS()		((U1)u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_HUD1S01,(U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR),(U2)HCOM_HUD1S01_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX))  /*  HUD1S01              */
#define vd_HCOMRX_GET_HUD_PWST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUD_PWST,  (x)))
#define vd_HCOMRX_GET_HUDSW_PS(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUDSW_PS,  (x)))
#define vd_HCOMRX_GET_HUDSW_RT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUDSW_RT,  (x)))
#define vd_HCOMRX_GET_HUDSW_DC(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUDSW_DC,  (x)))
#define vd_HCOMRX_GET_HUDBRMAX(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUDBRMAX_1, (x)))
#define vd_HCOMRX_GET_HUDBR(x)			((void)Com_ReceiveSignal(ComConf_ComSignal_HUDBR_1, (x)))
#define vd_HCOMRX_GET_HUDSW_PW(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_HUDSW_PW,  (x)))
#define vd_HCOMRX_GET_CTTACEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTTACEXT,  (x)))
#define vd_HCOMRX_GET_CTNAVEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTNAVEXT,  (x)))
#define vd_HCOMRX_GET_CTADSEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTADSEXT,  (x)))
#define vd_HCOMRX_GET_CTCMPEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTCMPEXT,  (x)))
#define vd_HCOMRX_GET_CTAUDEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTAUDEXT,  (x)))
#define vd_HCOMRX_GET_CTLANEXT(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTLANEXT,  (x)))
#define vd_HCOMRX_GET_CTTACST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTTACST,  (x)))
#define vd_HCOMRX_GET_CTNAVST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTNAVST_1,  (x)))
#define vd_HCOMRX_GET_CTADSST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTADSST_1,  (x)))
#define vd_HCOMRX_GET_CTCMPST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTCMPST_1,  (x)))
#define vd_HCOMRX_GET_CTAUDST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTAUDST_1,  (x)))
#define vd_HCOMRX_GET_CTLANST(x)		((void)Com_ReceiveSignal(ComConf_ComSignal_CTLANST,  (x)))

/* CAN transmission (event) */
#define vd_HCOM_MCICONRQ_WRITE(x)		((void)Com_SendSignal(ComConf_ComSignal_MCICONRQ_1 , (x))) /* MTC          */
#define vd_HCOM_IFICONRQ_WRITE(x)		((void)Com_SendSignal(ComConf_ComSignal_IFICONRQ_1 , (x))) /* INFO Icon                        */
#define vd_HCOM_TBTINT_WRITE(x)			((void)Com_SendSignal(ComConf_ComSignal_MCTNAVST, (x))) /* Navi TBT                        */

/* CAN transmission (routine) */
#define vd_HCOM_MCICONRQ_WRITE_IMM(x)	((void)Com_SendSignal(ComConf_ComSignal_MCICONRQ_1 , (x)))    /* MTC          */
#define vd_HCOM_IFICONRQ_WRITE_IMM(x)	((void)Com_SendSignal(ComConf_ComSignal_IFICONRQ_1 , (x)))    /* INFO Icon                        */
#define vd_HCOM_TBTINT_WRITE_IMM(x)		((void)Com_SendSignal(ComConf_ComSignal_MCTNAVST, (x)))    /* Navi TBT                        */

/* Related to RIM */
#define u1_HCOM_RIM_RD_NAV_MASK(x)			(u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_HCOM_NAV_MASK, (x)))
#define vd_HCOM_RIM_WR_NAV_MASK(u1_a_sts)	(vd_g_Rim_WriteU1((U2)RIMID_U1_HCOM_NAV_MASK, (u1_a_sts)))

#define HCOM_RIM_STATUS_MASK            (RIM_RESULT_KIND_MASK)                        /* RIMID        */
#define HCOM_RIM_READ_OK                (RIM_RESULT_KIND_OK)                          /* RIM STS                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* HCOM_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  hudcom.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
