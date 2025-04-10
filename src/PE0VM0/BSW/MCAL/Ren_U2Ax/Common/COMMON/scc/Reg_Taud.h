/* Reg_TAUD-r04-30700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		TAUD Register definition																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef REG_TAUD_H
#define REG_TAUD_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
#define TAUD_CHANNEL_NUM		((uint8)(16U))

/* TAUDnCDRm register */
typedef struct {
	uint16	u2TAUDnCDRm;
	uint8	u1Dummy[2];
} Taud_TAUDnCDRm_Type;

/* TAUDnCNTm register */
typedef struct {
	uint16	u2TAUDnCNTm;
	uint8	u1Dummy[2];
} Taud_TAUDnCNTm_Type;

/* TAUDnCMURm register */
typedef struct {
	union {
		uint8	u1Data;
		struct {
			uint8	b2TAUDnTIS		:2;
			uint8	b6Reserved		:6;
		} stBit;
	} unTAUDnCMUR;

	uint8	u1Dummy[3];
} Taud_TAUDnCMURm_Type;

/* TAUDnCSRm register */
typedef struct {
	uint8	u1TAUDnCSRm;
	uint8	u1Dummy[3];
} Taud_TAUDnCSRm_Type;

/* TAUDnCSCm register */
typedef struct {
	union {
		uint8	u1Data;
		struct {
			uint8	xTAUDnCLOV		:1;
			uint8	b7Reserved		:7;
		} stBit;
	} unTAUDnCSC;

	uint8	u1Dummy[3];
} Taud_TAUDnCSCm_Type;

/* TAUDnCMORm register */
typedef struct {
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnMD0		:1;
			uint16	b4TAUDnMD		:4;
			uint16	xReserved1		:1;
			uint16	b2TAUDnCOS		:2;
			uint16	b3TAUDnSTS		:3;
			uint16	xTAUDnMAS		:1;
			uint16	b2TAUDnCCS		:2;
			uint16	b2TAUDnCKS		:2;
		} stBit;
	} unTAUDnCMOR;

	uint8	u1Dummy[2];
} Taud_TAUDnCMORm_Type;

typedef	struct{
	
	/* TAUDnCDRm register */
	Taud_TAUDnCDRm_Type		stTAUDnCDRm[TAUD_CHANNEL_NUM];
	
	/* TAUDnTOL register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTOL00		:1;
			uint16	xTAUDnTOL01		:1;
			uint16	xTAUDnTOL02		:1;
			uint16	xTAUDnTOL03		:1;
			uint16	xTAUDnTOL04		:1;
			uint16	xTAUDnTOL05		:1;
			uint16	xTAUDnTOL06		:1;
			uint16	xTAUDnTOL07		:1;
			uint16	xTAUDnTOL08		:1;
			uint16	xTAUDnTOL09		:1;
			uint16	xTAUDnTOL10		:1;
			uint16	xTAUDnTOL11		:1;
			uint16	xTAUDnTOL12		:1;
			uint16	xTAUDnTOL13		:1;
			uint16	xTAUDnTOL14		:1;
			uint16	xTAUDnTOL15		:1;
		} stBit;
	} unTAUDnTOL;

	uint8	u1Dummy1[2];
	
	/* TAUDnRDT register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRDT00		:1;
			uint16	xTAUDnRDT01		:1;
			uint16	xTAUDnRDT02		:1;
			uint16	xTAUDnRDT03		:1;
			uint16	xTAUDnRDT04		:1;
			uint16	xTAUDnRDT05		:1;
			uint16	xTAUDnRDT06		:1;
			uint16	xTAUDnRDT07		:1;
			uint16	xTAUDnRDT08		:1;
			uint16	xTAUDnRDT09		:1;
			uint16	xTAUDnRDT10		:1;
			uint16	xTAUDnRDT11		:1;
			uint16	xTAUDnRDT12		:1;
			uint16	xTAUDnRDT13		:1;
			uint16	xTAUDnRDT14		:1;
			uint16	xTAUDnRDT15		:1;
		} stBit;
	} unTAUDnRDT;

	uint8	u1Dummy2[2];
	
	/* TAUDnRSF register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRSF00		:1;
			uint16	xTAUDnRSF01		:1;
			uint16	xTAUDnRSF02		:1;
			uint16	xTAUDnRSF03		:1;
			uint16	xTAUDnRSF04		:1;
			uint16	xTAUDnRSF05		:1;
			uint16	xTAUDnRSF06		:1;
			uint16	xTAUDnRSF07		:1;
			uint16	xTAUDnRSF08		:1;
			uint16	xTAUDnRSF09		:1;
			uint16	xTAUDnRSF10		:1;
			uint16	xTAUDnRSF11		:1;
			uint16	xTAUDnRSF12		:1;
			uint16	xTAUDnRSF13		:1;
			uint16	xTAUDnRSF14		:1;
			uint16	xTAUDnRSF15		:1;
		} stBit;
	} unTAUDnRSF;

	uint8	u1Dummy3[2];
	
	/* TAUDnTRO register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTRO00		:1;
			uint16	xTAUDnTRO01		:1;
			uint16	xTAUDnTRO02		:1;
			uint16	xTAUDnTRO03		:1;
			uint16	xTAUDnTRO04		:1;
			uint16	xTAUDnTRO05		:1;
			uint16	xTAUDnTRO06		:1;
			uint16	xTAUDnTRO07		:1;
			uint16	xTAUDnTRO08		:1;
			uint16	xTAUDnTRO09		:1;
			uint16	xTAUDnTRO10		:1;
			uint16	xTAUDnTRO11		:1;
			uint16	xTAUDnTRO12		:1;
			uint16	xTAUDnTRO13		:1;
			uint16	xTAUDnTRO14		:1;
			uint16	xTAUDnTRO15		:1;
		} stBit;
	} unTAUDnTRO;

	uint8	u1Dummy4[2];
	
	/* TAUDnTME register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTME00		:1;
			uint16	xTAUDnTME01		:1;
			uint16	xTAUDnTME02		:1;
			uint16	xTAUDnTME03		:1;
			uint16	xTAUDnTME04		:1;
			uint16	xTAUDnTME05		:1;
			uint16	xTAUDnTME06		:1;
			uint16	xTAUDnTME07		:1;
			uint16	xTAUDnTME08		:1;
			uint16	xTAUDnTME09		:1;
			uint16	xTAUDnTME10		:1;
			uint16	xTAUDnTME11		:1;
			uint16	xTAUDnTME12		:1;
			uint16	xTAUDnTME13		:1;
			uint16	xTAUDnTME14		:1;
			uint16	xTAUDnTME15		:1;
		} stBit;
	} unTAUDnTME;

	uint8	u1Dummy5[2];
	
	/* TAUDnTDL register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTDL00		:1;
			uint16	xTAUDnTDL01		:1;
			uint16	xTAUDnTDL02		:1;
			uint16	xTAUDnTDL03		:1;
			uint16	xTAUDnTDL04		:1;
			uint16	xTAUDnTDL05		:1;
			uint16	xTAUDnTDL06		:1;
			uint16	xTAUDnTDL07		:1;
			uint16	xTAUDnTDL08		:1;
			uint16	xTAUDnTDL09		:1;
			uint16	xTAUDnTDL10		:1;
			uint16	xTAUDnTDL11		:1;
			uint16	xTAUDnTDL12		:1;
			uint16	xTAUDnTDL13		:1;
			uint16	xTAUDnTDL14		:1;
			uint16	xTAUDnTDL15		:1;
		} stBit;
	} unTAUDnTDL;

	uint8	u1Dummy6[2];
	
	/* TAUDnTO register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTO00		:1;
			uint16	xTAUDnTO01		:1;
			uint16	xTAUDnTO02		:1;
			uint16	xTAUDnTO03		:1;
			uint16	xTAUDnTO04		:1;
			uint16	xTAUDnTO05		:1;
			uint16	xTAUDnTO06		:1;
			uint16	xTAUDnTO07		:1;
			uint16	xTAUDnTO08		:1;
			uint16	xTAUDnTO09		:1;
			uint16	xTAUDnTO10		:1;
			uint16	xTAUDnTO11		:1;
			uint16	xTAUDnTO12		:1;
			uint16	xTAUDnTO13		:1;
			uint16	xTAUDnTO14		:1;
			uint16	xTAUDnTO15		:1;
		} stBit;
	} unTAUDnTO;

	uint8	u1Dummy7[2];
	
	/* TAUDnTOE register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTOE00		:1;
			uint16	xTAUDnTOE01		:1;
			uint16	xTAUDnTOE02		:1;
			uint16	xTAUDnTOE03		:1;
			uint16	xTAUDnTOE04		:1;
			uint16	xTAUDnTOE05		:1;
			uint16	xTAUDnTOE06		:1;
			uint16	xTAUDnTOE07		:1;
			uint16	xTAUDnTOE08		:1;
			uint16	xTAUDnTOE09		:1;
			uint16	xTAUDnTOE10		:1;
			uint16	xTAUDnTOE11		:1;
			uint16	xTAUDnTOE12		:1;
			uint16	xTAUDnTOE13		:1;
			uint16	xTAUDnTOE14		:1;
			uint16	xTAUDnTOE15		:1;
		} stBit;
	} unTAUDnTOE;

	uint8	u1Dummy8[(0x80U) - (0x5CU + 0x2U)];
	
	/* TAUDnCNTm register */
	Taud_TAUDnCNTm_Type		stTAUDnCNTm[TAUD_CHANNEL_NUM];
	
	/* TAUDnCMURm register */
	Taud_TAUDnCMURm_Type	stTAUDnCMURm[TAUD_CHANNEL_NUM];
	uint8	u1Dummy9[64];
	
	/* TAUDnCSRm register */
	Taud_TAUDnCSRm_Type		stTAUDnCSRm[TAUD_CHANNEL_NUM];
	
	/* TAUDnCSCm register */
	Taud_TAUDnCSCm_Type		stTAUDnCSCm[TAUD_CHANNEL_NUM];
	
	/* TAUDnTE register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTE00		:1;
			uint16	xTAUDnTE01		:1;
			uint16	xTAUDnTE02		:1;
			uint16	xTAUDnTE03		:1;
			uint16	xTAUDnTE04		:1;
			uint16	xTAUDnTE05		:1;
			uint16	xTAUDnTE06		:1;
			uint16	xTAUDnTE07		:1;
			uint16	xTAUDnTE08		:1;
			uint16	xTAUDnTE09		:1;
			uint16	xTAUDnTE10		:1;
			uint16	xTAUDnTE11		:1;
			uint16	xTAUDnTE12		:1;
			uint16	xTAUDnTE13		:1;
			uint16	xTAUDnTE14		:1;
			uint16	xTAUDnTE15		:1;
		} stBit;
	} unTAUDnTE;

	uint8	u1Dummy10[2];
	
	/* TAUDnTS register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTS00		:1;
			uint16	xTAUDnTS01		:1;
			uint16	xTAUDnTS02		:1;
			uint16	xTAUDnTS03		:1;
			uint16	xTAUDnTS04		:1;
			uint16	xTAUDnTS05		:1;
			uint16	xTAUDnTS06		:1;
			uint16	xTAUDnTS07		:1;
			uint16	xTAUDnTS08		:1;
			uint16	xTAUDnTS09		:1;
			uint16	xTAUDnTS10		:1;
			uint16	xTAUDnTS11		:1;
			uint16	xTAUDnTS12		:1;
			uint16	xTAUDnTS13		:1;
			uint16	xTAUDnTS14		:1;
			uint16	xTAUDnTS15		:1;
		} stBit;
	} unTAUDnTS;

	uint8	u1Dummy11[2];
	
	/* TAUDnTT register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTT00		:1;
			uint16	xTAUDnTT01		:1;
			uint16	xTAUDnTT02		:1;
			uint16	xTAUDnTT03		:1;
			uint16	xTAUDnTT04		:1;
			uint16	xTAUDnTT05		:1;
			uint16	xTAUDnTT06		:1;
			uint16	xTAUDnTT07		:1;
			uint16	xTAUDnTT08		:1;
			uint16	xTAUDnTT09		:1;
			uint16	xTAUDnTT10		:1;
			uint16	xTAUDnTT11		:1;
			uint16	xTAUDnTT12		:1;
			uint16	xTAUDnTT13		:1;
			uint16	xTAUDnTT14		:1;
			uint16	xTAUDnTT15		:1;
		} stBit;
	} unTAUDnTT;

	uint8	u1Dummy12[(0x200U - (0x1C8U + 0x2U))];
	
	/* TAUDnCMORm register */
	Taud_TAUDnCMORm_Type	stTAUDnCMORm[TAUD_CHANNEL_NUM];
	
	/* TAUDnTPS register */
	union {
		uint16	u2Data;
		struct {
			uint16	b4TAUDnPRS0		:4;
			uint16	b4TAUDnPRS1		:4;
			uint16	b4TAUDnPRS2		:4;
			uint16	b4TAUDnPRS3		:4;
		} stBit;
	} unTAUDnTPS;

	uint8	u1Dummy13[2];
	
	/* TAUDnBRS register */
	uint8	u1TAUDnBRS;
	uint8	u1Dummy14[3];
	
	/* TAUDnTOM register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTOM00		:1;
			uint16	xTAUDnTOM01		:1;
			uint16	xTAUDnTOM02		:1;
			uint16	xTAUDnTOM03		:1;
			uint16	xTAUDnTOM04		:1;
			uint16	xTAUDnTOM05		:1;
			uint16	xTAUDnTOM06		:1;
			uint16	xTAUDnTOM07		:1;
			uint16	xTAUDnTOM08		:1;
			uint16	xTAUDnTOM09		:1;
			uint16	xTAUDnTOM10		:1;
			uint16	xTAUDnTOM11		:1;
			uint16	xTAUDnTOM12		:1;
			uint16	xTAUDnTOM13		:1;
			uint16	xTAUDnTOM14		:1;
			uint16	xTAUDnTOM15		:1;
		} stBit;
	} unTAUDnTOM;

	uint8	u1Dummy15[2];
	
	/* TAUDnTOC register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTOC00		:1;
			uint16	xTAUDnTOC01		:1;
			uint16	xTAUDnTOC02		:1;
			uint16	xTAUDnTOC03		:1;
			uint16	xTAUDnTOC04		:1;
			uint16	xTAUDnTOC05		:1;
			uint16	xTAUDnTOC06		:1;
			uint16	xTAUDnTOC07		:1;
			uint16	xTAUDnTOC08		:1;
			uint16	xTAUDnTOC09		:1;
			uint16	xTAUDnTOC10		:1;
			uint16	xTAUDnTOC11		:1;
			uint16	xTAUDnTOC12		:1;
			uint16	xTAUDnTOC13		:1;
			uint16	xTAUDnTOC14		:1;
			uint16	xTAUDnTOC15		:1;
		} stBit;
	} unTAUDnTOC;

	uint8	u1Dummy16[2];
	
	/* TAUDnTDE register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTDE00		:1;
			uint16	xTAUDnTDE01		:1;
			uint16	xTAUDnTDE02		:1;
			uint16	xTAUDnTDE03		:1;
			uint16	xTAUDnTDE04		:1;
			uint16	xTAUDnTDE05		:1;
			uint16	xTAUDnTDE06		:1;
			uint16	xTAUDnTDE07		:1;
			uint16	xTAUDnTDE08		:1;
			uint16	xTAUDnTDE09		:1;
			uint16	xTAUDnTDE10		:1;
			uint16	xTAUDnTDE11		:1;
			uint16	xTAUDnTDE12		:1;
			uint16	xTAUDnTDE13		:1;
			uint16	xTAUDnTDE14		:1;
			uint16	xTAUDnTDE15		:1;
		} stBit;
	} unTAUDnTDE;

	uint8	u1Dummy17[2];
	
	/* TAUDnTDM register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTDM00		:1;
			uint16	xTAUDnTDM01		:1;
			uint16	xTAUDnTDM02		:1;
			uint16	xTAUDnTDM03		:1;
			uint16	xTAUDnTDM04		:1;
			uint16	xTAUDnTDM05		:1;
			uint16	xTAUDnTDM06		:1;
			uint16	xTAUDnTDM07		:1;
			uint16	xTAUDnTDM08		:1;
			uint16	xTAUDnTDM09		:1;
			uint16	xTAUDnTDM10		:1;
			uint16	xTAUDnTDM11		:1;
			uint16	xTAUDnTDM12		:1;
			uint16	xTAUDnTDM13		:1;
			uint16	xTAUDnTDM14		:1;
			uint16	xTAUDnTDM15		:1;
		} stBit;
	} unTAUDnTDM;

	uint8	u1Dummy18[2];
	
	/* TAUDnTRE register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTRE00		:1;
			uint16	xTAUDnTRE01		:1;
			uint16	xTAUDnTRE02		:1;
			uint16	xTAUDnTRE03		:1;
			uint16	xTAUDnTRE04		:1;
			uint16	xTAUDnTRE05		:1;
			uint16	xTAUDnTRE06		:1;
			uint16	xTAUDnTRE07		:1;
			uint16	xTAUDnTRE08		:1;
			uint16	xTAUDnTRE09		:1;
			uint16	xTAUDnTRE10		:1;
			uint16	xTAUDnTRE11		:1;
			uint16	xTAUDnTRE12		:1;
			uint16	xTAUDnTRE13		:1;
			uint16	xTAUDnTRE14		:1;
			uint16	xTAUDnTRE15		:1;
		} stBit;
	} unTAUDnTRE;

	uint8	u1Dummy19[2];
	
	/* TAUDnTRC register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnTRC00		:1;
			uint16	xTAUDnTRC01		:1;
			uint16	xTAUDnTRC02		:1;
			uint16	xTAUDnTRC03		:1;
			uint16	xTAUDnTRC04		:1;
			uint16	xTAUDnTRC05		:1;
			uint16	xTAUDnTRC06		:1;
			uint16	xTAUDnTRC07		:1;
			uint16	xTAUDnTRC08		:1;
			uint16	xTAUDnTRC09		:1;
			uint16	xTAUDnTRC10		:1;
			uint16	xTAUDnTRC11		:1;
			uint16	xTAUDnTRC12		:1;
			uint16	xTAUDnTRC13		:1;
			uint16	xTAUDnTRC14		:1;
			uint16	xTAUDnTRC15		:1;
		} stBit;
	} unTAUDnTRC;

	uint8	u1Dummy20[2];
	
	/* TAUDnRDE register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRDE00		:1;
			uint16	xTAUDnRDE01		:1;
			uint16	xTAUDnRDE02		:1;
			uint16	xTAUDnRDE03		:1;
			uint16	xTAUDnRDE04		:1;
			uint16	xTAUDnRDE05		:1;
			uint16	xTAUDnRDE06		:1;
			uint16	xTAUDnRDE07		:1;
			uint16	xTAUDnRDE08		:1;
			uint16	xTAUDnRDE09		:1;
			uint16	xTAUDnRDE10		:1;
			uint16	xTAUDnRDE11		:1;
			uint16	xTAUDnRDE12		:1;
			uint16	xTAUDnRDE13		:1;
			uint16	xTAUDnRDE14		:1;
			uint16	xTAUDnRDE15		:1;
		} stBit;
	} unTAUDnRDE;

	uint8	u1Dummy21[2];
	
	/* TAUDnRDM register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRDM00		:1;
			uint16	xTAUDnRDM01		:1;
			uint16	xTAUDnRDM02		:1;
			uint16	xTAUDnRDM03		:1;
			uint16	xTAUDnRDM04		:1;
			uint16	xTAUDnRDM05		:1;
			uint16	xTAUDnRDM06		:1;
			uint16	xTAUDnRDM07		:1;
			uint16	xTAUDnRDM08		:1;
			uint16	xTAUDnRDM09		:1;
			uint16	xTAUDnRDM10		:1;
			uint16	xTAUDnRDM11		:1;
			uint16	xTAUDnRDM12		:1;
			uint16	xTAUDnRDM13		:1;
			uint16	xTAUDnRDM14		:1;
			uint16	xTAUDnRDM15		:1;
		} stBit;
	} unTAUDnRDM;

	uint8	u1Dummy22[2];
	
	/* TAUDnRDS register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRDS00		:1;
			uint16	xTAUDnRDS01		:1;
			uint16	xTAUDnRDS02		:1;
			uint16	xTAUDnRDS03		:1;
			uint16	xTAUDnRDS04		:1;
			uint16	xTAUDnRDS05		:1;
			uint16	xTAUDnRDS06		:1;
			uint16	xTAUDnRDS07		:1;
			uint16	xTAUDnRDS08		:1;
			uint16	xTAUDnRDS09		:1;
			uint16	xTAUDnRDS10		:1;
			uint16	xTAUDnRDS11		:1;
			uint16	xTAUDnRDS12		:1;
			uint16	xTAUDnRDS13		:1;
			uint16	xTAUDnRDS14		:1;
			uint16	xTAUDnRDS15		:1;
		} stBit;
	} unTAUDnRDS;

	uint8	u1Dummy23[2];
	
	/* TAUDnRDC register */
	union {
		uint16	u2Data;
		struct {
			uint16	xTAUDnRDC00		:1;
			uint16	xTAUDnRDC01		:1;
			uint16	xTAUDnRDC02		:1;
			uint16	xTAUDnRDC03		:1;
			uint16	xTAUDnRDC04		:1;
			uint16	xTAUDnRDC05		:1;
			uint16	xTAUDnRDC06		:1;
			uint16	xTAUDnRDC07		:1;
			uint16	xTAUDnRDC08		:1;
			uint16	xTAUDnRDC09		:1;
			uint16	xTAUDnRDC10		:1;
			uint16	xTAUDnRDC11		:1;
			uint16	xTAUDnRDC12		:1;
			uint16	xTAUDnRDC13		:1;
			uint16	xTAUDnRDC14		:1;
			uint16	xTAUDnRDC15		:1;
		} stBit;
	} unTAUDnRDC;

	uint8	u1Dummy24[2];
	
} Reg_Taud_Type;

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
/* TAUD Address base */
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define TAUD0_BASE_ADR		((uint32)(0xFFBF4000U))
#define TAUD1_BASE_ADR		((uint32)(0xFFBF5000U))
#define TAUD2_BASE_ADR		((uint32)(0xFFBF6000U))
#define TAUD3_BASE_ADR		TAUD2_BASE_ADR
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define TAUD0_BASE_ADR		((uint32)(0xFFBF4000U))
#define TAUD1_BASE_ADR		((uint32)(0xFF894000U))
#define TAUD2_BASE_ADR		((uint32)(0xFFBF6000U))
#define TAUD3_BASE_ADR		((uint32)(0xFF896000U))
#else	/* (MCAL_SPAL_TARGET == MCAL_TARGET_RCARS4_G4MH) */
#define TAUD0_BASE_ADR		((uint32)(0xFFBF4000U))
#define TAUD1_BASE_ADR		((uint32)(0xFFBF5000U))
#define TAUD2_BASE_ADR		TAUD1_BASE_ADR
#define TAUD3_BASE_ADR		TAUD1_BASE_ADR
#endif

/* TAUD Register Access  */
#define REG_TAUD0			(*(volatile Reg_Taud_Type*)			TAUD0_BASE_ADR)
#define REG_TAUD1			(*(volatile Reg_Taud_Type*)			TAUD1_BASE_ADR)
#define REG_TAUD2			(*(volatile Reg_Taud_Type*)			TAUD2_BASE_ADR)
#define REG_TAUD3			(*(volatile Reg_Taud_Type*)			TAUD3_BASE_ADR)

/*----------------------------------------------------------------------------------------------*/
/*	register setting definition																	*/
/*----------------------------------------------------------------------------------------------*/
/* TAUDnTPS register */
#define	TAUD_TAUDnPRS0		((uint16)(0x0001U))				/* BIT0 */
#define	TAUD_TAUDnPRS1		((uint16)(0x0010U))				/* BIT4 */
#define	TAUD_TAUDnPRS2		((uint16)(0x0100U))				/* BIT8 */
#define	TAUD_TAUDnPRS3		((uint16)(0x1000U))				/* BIT12 */

/* TAUDnTE register */
#define TAUD_TAUDnTE_DISABLE_COUNT_OPERATION			((uint16)(0x0000U))
#define TAUD_TAUDnTE_ENABLE_COUNT_OPERATION				((uint16)(0x0001U))

/* TAUDnTS register */
#define	TAUD_TAUDnTS0		((uint16)(0x0001U))			/* BIT0 */
#define	TAUD_TAUDnTS1		((uint16)(0x0002U))			/* BIT1 */
#define	TAUD_TAUDnTS2		((uint16)(0x0004U))			/* BIT2 */
#define	TAUD_TAUDnTS3		((uint16)(0x0008U))			/* BIT3 */
#define	TAUD_TAUDnTS4		((uint16)(0x0010U))			/* BIT4 */
#define	TAUD_TAUDnTS5		((uint16)(0x0020U))			/* BIT5 */
#define	TAUD_TAUDnTS6		((uint16)(0x0040U))			/* BIT6 */
#define	TAUD_TAUDnTS7		((uint16)(0x0080U))			/* BIT7 */
#define	TAUD_TAUDnTS8		((uint16)(0x0100U))			/* BIT8 */
#define	TAUD_TAUDnTS9		((uint16)(0x0200U))			/* BIT9 */
#define	TAUD_TAUDnTS10		((uint16)(0x0400U))			/* BIT10 */
#define	TAUD_TAUDnTS11		((uint16)(0x0800U))			/* BIT11 */
#define	TAUD_TAUDnTS12		((uint16)(0x1000U))			/* BIT12 */
#define	TAUD_TAUDnTS13		((uint16)(0x2000U))			/* BIT13 */
#define	TAUD_TAUDnTS14		((uint16)(0x4000U))			/* BIT14 */
#define	TAUD_TAUDnTS15		((uint16)(0x8000U))			/* BIT15 */
	#define TAUD_TAUDnTS_ENABLE_COUNT_OPERATION				((uint16)(0x0001U))

/* TAUDnTT register */
#define	TAUD_TAUDnTT0		((uint16)(0x0001U))			/* BIT0 */
#define	TAUD_TAUDnTT1		((uint16)(0x0002U))			/* BIT1 */
#define	TAUD_TAUDnTT2		((uint16)(0x0004U))			/* BIT2 */
#define	TAUD_TAUDnTT3		((uint16)(0x0008U))			/* BIT3 */
#define	TAUD_TAUDnTT4		((uint16)(0x0010U))			/* BIT4 */
#define	TAUD_TAUDnTT5		((uint16)(0x0020U))			/* BIT5 */
#define	TAUD_TAUDnTT6		((uint16)(0x0040U))			/* BIT6 */
#define	TAUD_TAUDnTT7		((uint16)(0x0080U))			/* BIT7 */
#define	TAUD_TAUDnTT8		((uint16)(0x0100U))			/* BIT8 */
#define	TAUD_TAUDnTT9		((uint16)(0x0200U))			/* BIT9 */
#define	TAUD_TAUDnTT10		((uint16)(0x0400U))			/* BIT10 */
#define	TAUD_TAUDnTT11		((uint16)(0x0800U))			/* BIT11 */
#define	TAUD_TAUDnTT12		((uint16)(0x1000U))			/* BIT12 */
#define	TAUD_TAUDnTT13		((uint16)(0x2000U))			/* BIT13 */
#define	TAUD_TAUDnTT14		((uint16)(0x4000U))			/* BIT14 */
#define	TAUD_TAUDnTT15		((uint16)(0x8000U))			/* BIT15 */
	#define TAUD_TAUDnTT_STOP_OPERATION			((uint16)(0x0001U))

/* TAUDnCMORm register */
#define	TAUD_TAUDnMD0		((uint16)(0x0001U))	/* BIT0 */
	#define	TAUD_TAUDnMD0_DISABLE						((uint16)(0U))
	#define	TAUD_TAUDnMD0_ENABLE						((uint16)(1U))
#define	TAUD_TAUDnMD		((uint16)(0x0002U))	/* BIT1 */
	#define	TAUD_TAUDnMD_INTERVAL_TIMER_MODE			((uint16)(0x00U))
	#define	TAUD_TAUDnMD_JUDGE_MODE						((uint16)(0x01U))
	#define	TAUD_TAUDnMD_CAPTURE_MODE					((uint16)(0x02U))
	#define	TAUD_TAUDnMD_EVENT_COUNT_MODE				((uint16)(0x03U))
	#define	TAUD_TAUDnMD_ONECOUNT_MODE					((uint16)(0x04U))
	#define	TAUD_TAUDnMD_CAPTURE_AND_ONECOUNT_MODE		((uint16)(0x06U))
	#define	TAUD_TAUDnMD_JUDGE_AND_ONECOUNT_MODE		((uint16)(0x07U))
	#define	TAUD_TAUDnMD_COUNT_UP_DOWN_MODE				((uint16)(0x09U))
	#define	TAUD_TAUDnMD_PLUSE_ONE_COUNT_MODE			((uint16)(0x0AU))
	#define	TAUD_TAUDnMD_COUNT_CAPTURE_MODE				((uint16)(0x0BU))
	#define	TAUD_TAUDnMD_GATE_COUNT_MODE				((uint16)(0x0CU))
	#define	TAUD_TAUDnMD_CAPTURE_AND_GATE_COUNT_MODE	((uint16)(0x0DU))
#define	TAUD_TAUDnCOS		((uint16)(0x0040U))	/* BIT6 */
#define	TAUD_TAUDnSTS		((uint16)(0x0100U))	/* BIT8 */
#define	TAUD_TAUDnMAS		((uint16)(0x0800U))	/* BIT11 */
	#define	TAUD_TAUDnMAS_SLAVE							((uint16)(0U))
	#define	TAUD_TAUDnMAS_MASTER						((uint16)(1U))
#define	TAUD_TAUDnCCS		((uint16)(0x1000U))	/* BIT12 */
#define	TAUD_TAUDnCKS		((uint16)(0x4000U))	/* BIT14 */
	#define	TAUD_TAUDnCKS_CK0							((uint16)(0U))
	#define	TAUD_TAUDnCKS_CK1							((uint16)(1U))
	#define	TAUD_TAUDnCKS_CK2							((uint16)(2U))
	#define	TAUD_TAUDnCKS_CK3							((uint16)(3U))

/* TAUDnCSCm register */
#define TAUD_TAUDnCSCm_CLEAR_OVERFLOW					((uint8)(0x01U))

/* TAUDnRDE register */
#define TAUD_TAUDnRDE_DISABLE							((uint8)(0x00U))
#define TAUD_TAUDnRDE_ENABLE							((uint8)(0x01U))

#endif /* REG_TAUD_H  */
/*-- End Of File -------------------------------------------------------------------------------*/
