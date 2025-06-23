/* Cdd_Canic-r03-5000-0100-a */
/************************************************************************************************/
/*																								*/
/*		CAN Transceiver IC Communication Driver (TJA1145A)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	CDD_CANIC_LCFG_H
#define	CDD_CANIC_LCFG_H

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/

#define		CDD_CANIC_UCFG_IC0_CANFD_TOLERANCE	(CDD_CANIC_CANFD_TOLERATE)
#define		CDD_CANIC_UCFG_IC0_PARTIAL_NETWORK	(CDD_CANIC_PN_ENABLE)
#define		CDD_CANIC_UCFG_IC0_CWE_DETECTION	(CDD_CANIC_CWE_ENABLE)
#define		CDD_CANIC_UCFG_IC0_COREID			(BSW_CORE_ID_CORE0)
#define		CDD_CANIC_UCFG_IC0_WUF_DATARATE		(CDD_CANIC_WUF_DATARATE_500)
#define		CDD_CANIC_UCFG_IC0_WUF_ID0			((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_ID1			((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_ID2			((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_ID3			((U1)0x11)
#define		CDD_CANIC_UCFG_IC0_WUF_IDMASK0		((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_IDMASK1		((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_IDMASK2		((U1)0xFC)
#define		CDD_CANIC_UCFG_IC0_WUF_IDMASK3		((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_IDE				(CDD_CANIC_IDE_STANDAERD)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK		(CDD_CANIC_WUF_DATAMASK_ON)
#define		CDD_CANIC_UCFG_IC0_DLC				(CDD_CANIC_DLC8)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK0	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK1	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK2	((U1)0x01)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK3	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK4	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK5	((U1)0x19)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK6	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WUF_DATAMASK7	((U1)0x00)
#define		CDD_CANIC_UCFG_IC0_WAKEPIN_EN_WPRE  (CDD_CANIC_WPRE_DISABLE)
#define		CDD_CANIC_UCFG_IC0_WAKEPIN_EN_WPFE  (CDD_CANIC_WPFE_ENABLE)

#define		CDD_CANIC_UCFG_IC1_CANFD_TOLERANCE	(CDD_CANIC_CANFD_TOLERATE)
#define		CDD_CANIC_UCFG_IC1_PARTIAL_NETWORK	(CDD_CANIC_PN_ENABLE)
#define		CDD_CANIC_UCFG_IC1_CWE_DETECTION	(CDD_CANIC_CWE_ENABLE)
#define		CDD_CANIC_UCFG_IC1_COREID			(BSW_CORE_ID_CORE0)
#define		CDD_CANIC_UCFG_IC1_WUF_DATARATE		(CDD_CANIC_WUF_DATARATE_500)
#define		CDD_CANIC_UCFG_IC1_WUF_ID0			((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_ID1			((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_ID2			((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_ID3			((U1)0x11)
#define		CDD_CANIC_UCFG_IC1_WUF_IDMASK0		((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_IDMASK1		((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_IDMASK2		((U1)0xFC)
#define		CDD_CANIC_UCFG_IC1_WUF_IDMASK3		((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_IDE				(CDD_CANIC_IDE_STANDAERD)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK		(CDD_CANIC_WUF_DATAMASK_ON)
#define		CDD_CANIC_UCFG_IC1_DLC				(CDD_CANIC_DLC8)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK0	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK1	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK2	((U1)0x01)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK3	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK4	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK5	((U1)0x19)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK6	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WUF_DATAMASK7	((U1)0x00)
#define		CDD_CANIC_UCFG_IC1_WAKEPIN_EN_WPRE  (CDD_CANIC_WPRE_DISABLE)
#define		CDD_CANIC_UCFG_IC1_WAKEPIN_EN_WPFE  (CDD_CANIC_WPFE_ENABLE)

#define		DIOH_ID_O_CANIC_WAKE_0              (DIO_ID_APORT5_CH2)
#define		DIOH_ID_O_CANIC_WAKE_1              (DIO_ID_PORT2_CH15)
/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/

#endif	/* CDD_CANIC_LCFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/

