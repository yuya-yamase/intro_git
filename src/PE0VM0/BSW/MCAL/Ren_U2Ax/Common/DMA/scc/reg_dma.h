/* reg_dma-r04-3000-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		DMA register definition (for RH850E2M)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef REG_DMA_H
#define REG_DMA_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/
#define	DMA_DTS_CH_NUM		(128)
#define	DMA_DTS_REQ_NUM		(16)
#define	DMA_DTS_PRI_NUM		(8)
#define DMA_DTS_SEL_BIT_NUM	(4)				/*Number of bits used per element in DTSSEL*/

#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
	#define	DMA_DMAC_UNIT_NUM	(2)
#else
	#define	DMA_DMAC_UNIT_NUM	(1)         /* U2B6 has only DMAC0 */
#endif

#define	DMA_DMAC_CH_NUM		(16)
#define	DMA_DMAC_REQ_NUM	(16)

#define DMA_DMAC_SEL_BIT_NUM	(2)         /*Number of bits used per element in sDMACSEL*/
#define	DMA_DMAC_DESCRIPTOR_NUM		(1024)	/* Descriptor RAM  */

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/

typedef	struct
{

	union												/* DMACSELj_m 0xFF090400   */
	{
		uint8	u1Data[4];								/* 8-bit Access            */
		uint16	u2Data[2];								/* 16-bit Access           */
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
			uint32	xSEL0					:1;			/* SEL0                    */
			uint32	xDummy1					:1;			/* Reserved Bits           */
			uint32	xSEL1					:1;			/* SEL1                    */
			uint32	xDummy2					:1;			/* Reserved Bits           */
			uint32	xSEL2					:1;			/* SEL2                    */
			uint32	xDummy3					:1;			/* Reserved Bits           */
			uint32	xSEL3					:1;			/* SEL3                    */
			uint32	xDummy4					:1;			/* Reserved Bits           */
			uint32	xSEL4					:1;			/* SEL4                    */
			uint32	xDummy5					:1;			/* Reserved Bits           */
			uint32	xSEL5					:1;			/* SEL5                    */
			uint32	xDummy6					:1;			/* Reserved Bits           */
			uint32	xSEL6					:1;			/* SEL6                    */
			uint32	xDummy7					:1;			/* Reserved Bits           */
			uint32	xSEL7					:1;			/* SEL7                    */
			uint32	xDummy8					:1;			/* Reserved Bits           */
			uint32	xSEL8					:1;			/* SEL8                    */
			uint32	xDummy9					:1;			/* Reserved Bits           */
			uint32	xSEL9					:1;			/* SEL9                    */
			uint32	xDummy10				:1;			/* Reserved Bits           */
			uint32	xSEL10					:1;			/* SEL10                   */
			uint32	xDummy11				:1;			/* Reserved Bits           */
			uint32	xSEL11					:1;			/* SEL11                   */
			uint32	xDummy12				:1;			/* Reserved Bits           */
			uint32	xSEL12					:1;			/* SEL12                   */
			uint32	xDummy13				:1;			/* Reserved Bits           */
			uint32	xSEL13					:1;			/* SEL13                   */
			uint32	xDummy14				:1;			/* Reserved Bits           */
			uint32	xSEL14					:1;			/* SEL14                   */
			uint32	xDummy15				:1;			/* Reserved Bits           */
			uint32	xSEL15					:1;			/* SEL15                   */
			uint32	xDummy16				:1;			/* Reserved Bits           */
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
			uint32	b2SEL0					:2;			/* SEL0                    */
			uint32	b2SEL1					:2;			/* SEL1                    */
			uint32	b2SEL2					:2;			/* SEL2                    */
			uint32	b2SEL3					:2;			/* SEL3                    */
			uint32	b2SEL4					:2;			/* SEL4                    */
			uint32	b2SEL5					:2;			/* SEL5                    */
			uint32	b2SEL6					:2;			/* SEL6                    */
			uint32	b2SEL7					:2;			/* SEL7                    */
			uint32	b2SEL8					:2;			/* SEL8                    */
			uint32	b2SEL9					:2;			/* SEL9                    */
			uint32	b2SEL10					:2;			/* SEL10                   */
			uint32	b2SEL11					:2;			/* SEL11                   */
			uint32	b2SEL12					:2;			/* SEL12                   */
			uint32	b2SEL13					:2;			/* SEL13                   */
			uint32	b2SEL14					:2;			/* SEL14                   */
			uint32	b2SEL15					:2;			/* SEL15                   */
#endif /* MCAL_SPAL_TARGET */
		} stBit;
	} unDMACSEL[DMA_DMAC_UNIT_NUM][DMA_DMAC_CH_NUM];

#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
	uint8	u1Dummy1[384];								/* 0xFF090480 - 0xFF0905FF */
#else
	uint8	u1Dummy1[448];								/* 0xFF090440 - 0xFF0905FF */
#endif

	union												/* DTSSELm 0xFF090600      */
	{
		uint8	u1Data[4];								/* 8-bit Access            */
		uint16	u2Data[2];								/* 16-bit Access           */
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
			uint32	b2SEL0					:2;			/* SEL0                    */
			uint32	b2Dummy1				:2;			/* Reserved Bits           */
			uint32	b2SEL1					:2;			/* SEL1                    */
			uint32	b2Dummy2				:2;			/* Reserved Bits           */
			uint32	b2SEL2					:2;			/* SEL2                    */
			uint32	b2Dummy3				:2;			/* Reserved Bits           */
			uint32	b2SEL3					:2;			/* SEL3                    */
			uint32	b2Dummy4				:2;			/* Reserved Bits           */
			uint32	b2SEL4					:2;			/* SEL4                    */
			uint32	b2Dummy5				:2;			/* Reserved Bits           */
			uint32	b2SEL5					:2;			/* SEL5                    */
			uint32	b2Dummy6				:2;			/* Reserved Bits           */
			uint32	b2SEL6					:2;			/* SEL6                    */
			uint32	b2Dummy7				:2;			/* Reserved Bits           */
			uint32	b2SEL7					:2;			/* SEL7                    */
			uint32	b2Dummy8				:2;			/* Reserved Bits           */
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
			uint32	b3SEL0					:3;			/* SEL0                    */
			uint32	xDummy1					:1;			/* Reserved Bits           */
			uint32	b3SEL1					:3;			/* SEL1                    */
			uint32	xDummy2					:1;			/* Reserved Bits           */
			uint32	b3SEL2					:3;			/* SEL2                    */
			uint32	xDummy3					:1;			/* Reserved Bits           */
			uint32	b3SEL3					:3;			/* SEL3                    */
			uint32	xDummy4					:1;			/* Reserved Bits           */
			uint32	b3SEL4					:3;			/* SEL4                    */
			uint32	xDummy5					:1;			/* Reserved Bits           */
			uint32	b3SEL5					:3;			/* SEL5                    */
			uint32	xDummy6					:1;			/* Reserved Bits           */
			uint32	b3SEL6					:3;			/* SEL6                    */
			uint32	xDummy7					:1;			/* Reserved Bits           */
			uint32	b3SEL7					:3;			/* SEL7                    */
			uint32	xDummy8					:1;			/* Reserved Bits           */
#endif /* MCAL_SPAL_TARGET */
		} stBit;
	} unDTSSEL[DMA_DTS_REQ_NUM];

} Reg_Dmatrgsel_Type;


typedef	struct
{

	/************************************/
	/*			Global Register			*/
	/************************************/
	/* 0xFFF88000 - 0xFFF88FFF */
	uint8	u1Dummy1[16];								/* 0xFFF88000 - 0xFFF8800F */

	union												/* DTSCTL1 0xFFF88010      */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	xDTSUST					:1;			/* DTSUST                  */
			uint32	b31Dummy1				:31;		/* Reserved Bits           */
		} stBit;
	} unDTSCTL1;

	union												/* DTSCTL2 0xFFF88014      */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	xDTSTIT					:1;			/* DTSTIT                  */
			uint32	b31Dummy1				:31;		/* Reserved Bits           */
		} stBit;
	} unDTSCTL2;

	union												/* DTSSTS 0xFFF88018       */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	xDTSACT					:1;			/* DTSACT                  */
			uint32	b7DTSACH				:7;			/* DTSACH                  */
			uint32	xDTSCYC					:1;			/* DTSCYC                  */
			uint32	b23Dummy1				:23;		/* Reserved Bits           */
		} stBit;
	} unDTSSTS;

	uint8	u1Dummy2[8];								/* 0xFFF8801C - 0xFFF88023 */

	union												/* DTSER 0xFFF88024        */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	xDTSER					:1;			/* DTSER                   */
			uint32	xDTSERWR				:1;			/* DTSERWR                 */
			uint32	b6Dummy1				:6;			/* Reserved Bits           */
			uint32	b7DTSERCH				:7;			/* DTSERCH                 */
			uint32	b17Dummy2				:17;		/* Reserved Bits           */
		} stBit;
	} unDTSER;

	uint8	u1Dummy3[56];								/* 0xFFF88028 - 0xFFF8805F */

	union												/* DTSPR0-7 0xFFF88060-07C */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b2DTS0PR				:2;			/* DTS0PR                  */
			uint32	b2DTS1PR				:2;			/* DTS1PR                  */
			uint32	b2DTS2PR				:2;			/* DTS2PR                  */
			uint32	b2DTS3PR				:2;			/* DTS3PR                  */
			uint32	b2DTS4PR				:2;			/* DTS4PR                  */
			uint32	b2DTS5PR				:2;			/* DTS5PR                  */
			uint32	b2DTS6PR				:2;			/* DTS6PR                  */
			uint32	b2DTS7PR				:2;			/* DTS7PR                  */
			uint32	b2DTS8PR				:2;			/* DTS8PR                  */
			uint32	b2DTS9PR				:2;			/* DTS9PR                  */
			uint32	b2DTS10PR				:2;			/* DTS10PR                 */
			uint32	b2DTS11PR				:2;			/* DTS11PR                 */
			uint32	b2DTS12PR				:2;			/* DTS12PR                 */
			uint32	b2DTS13PR				:2;			/* DTS13PR                 */
			uint32	b2DTS14PR				:2;			/* DTS14PR                 */
			uint32	b2DTS15PR				:2;			/* DTS15PR                 */
		} stBit;
	} unDTSPR[DMA_DTS_PRI_NUM];

	uint8	u1Dummy4[384];								/* 0xFFF88080 - 0xFFF881FF */

	union												/* DTSnnnCM 0xFFF88200     */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b16CMC					:16;		/* CMC                     */
			uint32	xDummy1					:1;			/* Reserved Bits           */
			uint32	xUM						:1;			/* UM                      */
			uint32	b5SPID					:5;			/* SPID                    */
			uint32	b2Dummy2				:2;			/* Reserved Bits           */
			uint32	xCHAIN_UM				:1;			/* CHAIN_UM                */
			uint32	b5CHAIN_SPID			:5;			/* CHAIN_SPID              */
			uint32	xCHAIN_RESTRICT			:1;			/* CHAIN_RESTRICT          */
		} stBit;
	} unDTSCM[DMA_DTS_CH_NUM];

	uint8	u1Dummy5[3072];								/* 0xFFF88400 - 0xFFF88FFF */

	/************************************/
	/*		 DTS Channel Register		*/
	/************************************/
	/* 0xFFF89000 - 0xFFF8AFEF */
	struct
	{
		uint32	u4DTSA;									/* DTSAnnn OFFSET 0x1000   */

		uint32	u4DTDA;									/* DTDAnnn OFFSET 0x1004   */

		union											/* DTTCnnn OFFSET 0x1008   */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		b16TRC			:16;		/* TRC                     */
				uint32		b16ARC			:16;		/* ARC                     */
			} stBit;
		} unDTTC;

		union											/* DTTCTnnn OFFSET 0x100C  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		b2TRM			:2;			/* TRM                     */
				uint32		b3DS			:3;			/* DS                      */
				uint32		b2SACM			:2;			/* SACM                    */
				uint32		b2DACM			:2;			/* DACM                    */
				uint32		b2RLD1M			:2;			/* RLD1M                   */
				uint32		b2RLD2M			:2;			/* RLD2M                   */
				uint32		xDummy1			:1;			/* Reserved Bits           */
				uint32		xTCE			:1;			/* TCE                     */
				uint32		xCCE			:1;			/* CCE                     */
				uint32		b2CHNE			:2;			/* CHNE                    */
				uint32		b7CHNSEL		:7;			/* CHNSEL                  */
				uint32		b2Dummy2		:2;			/* Reserved Bits           */
				uint32		xESE			:1;			/* ESE                     */
				uint32		b4Dummy3		:4;			/* Reserved Bits           */
			} stBit;
		} unDTTCT;

		uint32	u4DTRSA;								/* DTRSAnnn OFFSET 0x1010  */

		uint32	u4DTRDA;								/* DTRDAnnn OFFSET 0x1014  */

		union											/* DTRTCnnn OFFSET 0x1018  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		b16RTRC			:16;		/* RTRC                    */
				uint32		b16RARC			:16;		/* RARC                    */
			} stBit;
		} unDTRTC;

		union											/* DTTCCnnn OFFSET 0x101C  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		b16CMC			:16;		/* CMC                     */
				uint32		b16Dummy1		:16;		/* Reserved Bits           */
			} stBit;
		} unDTTCC;

		union											/* DTFSLnnn OFFSET 0x1020  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		xREQEN			:1;			/* REQEN                   */
				uint32		b31Dummy1		:31;		/* Reserved Bits           */
			} stBit;
		} unDTFSL;

		union											/* DTFSTnnn OFFSET 0x1024  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		xDRQ			:1;			/* DRQ                     */
				uint32		xOVF			:1;			/* OVF                     */
				uint32		b2Dummy1		:2;			/* Reserved Bits           */
				uint32		xTC				:1;			/* TC                      */
				uint32		xCC				:1;			/* CC                      */
				uint32		xDummy2			:1;			/* Reserved Bits           */
				uint32		xER				:1;			/* ER                      */
				uint32		b3Dummy3		:3;			/* Reserved Bits           */
				uint32		xERWR			:1;			/* ERWR                    */
				uint32		b20Dummy4		:20;		/* Reserved Bits           */
			} stBit;
		} unDTFST;

		union											/* DTFSSnnn OFFSET 0x1028  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		xDRQS			:1;			/* DRQS                    */
				uint32		b31Dummy1		:31;		/* Reserved Bits           */
			} stBit;
		} unDTFSS;

		union											/* DTFSCnnn OFFSET 0x102C  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32		xDRQC			:1;			/* DRQC                    */
				uint32		xOVFC			:1;			/* OVFC                    */
				uint32		b2Dummy1		:2;			/* Reserved Bits           */
				uint32		xTCC			:1;			/* TCC                     */
				uint32		xCCC			:1;			/* CCC                     */
				uint32		xDummy2			:1;			/* Reserved Bits           */
				uint32		xERC			:1;			/* ERC                     */
				uint32		b24Dummy3		:24;		/* Reserved Bits           */
			} stBit;
		} unDTFSC;

		uint8	u1Dummy6[16];							/* OFFSET 0x1030 - 0x103F */

	} stDTS_CH[DMA_DTS_CH_NUM];

} Reg_Dts_Type;


typedef	struct
{

	uint8	u1Dummy1[16];								/* OFFSET 0x00 - 0x0F      */

	union												/* DMAjESTA OFFSET 0x10    */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b16AEN					:16;		/* AEN                     */
			uint32	b16Dummy1				:16;		/* Reserved Bits           */
		} stBit;
	} unESTA;

	uint8	u1Dummy2[12];								/* OFFSET 0x14 - 0x1F      */

	union												/* DMAjISTA OFFSET 0x20    */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b16INT					:16;		/* INT                     */
			uint32	b16Dummy1				:16;		/* Reserved Bits           */
		} stBit;
	} unISTA;

	uint8	u1Dummy3[28];								/* OFFSET 0x24 - 0x3F      */

	union												/* DMAjCHPRI OFFSET 0x40   */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b16PRICNT				:16;		/* PRICNT                  */
			uint32	b16Dummy1				:16;		/* Reserved Bits           */
		} stBit;
	} unCHPRI;

	uint8	u1Dummy4[28];								/* OFFSET 0x44 - 0x5F      */

	union												/* DMAjOR OFFSET 0x60      */
	{
		uint16	u2Data;									/* 16-bit Access           */
		struct											/* Bit Access              */
		{
			uint16	xDME					:1;			/* DME                     */
			uint16	b7Dummy1				:7;			/* Reserved Bits           */
			uint16	b2PR					:2;			/* PR                      */
			uint16	b6Dummy2				:6;			/* Reserved Bits           */
		} stBit;
	} unOR;

	uint8	u1Dummy5[30];								/* OFFSET 0x62 - 0x7F      */

	union												/* DMAjCHRST OFFSET 0x80   */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b16CLR					:16;		/* CLR                     */
			uint32	b16Dummy1				:16;		/* Reserved Bits           */
		} stBit;
	} unCHRST;

	uint8	u1Dummy6[124];								/* OFFSET 0x84 - 0xFF      */

	union												/* DMAjCM_n OFFSET 0x100   */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	xUM						:1;			/* UM                      */
			uint32	b7Dummy1				:7;			/* Reserved Bits           */
			uint32	b5SPID					:5;			/* SPID                    */
			uint32	b19Dummy2				:19;		/* Reserved Bits           */
		} stBit;
	} unCM[DMA_DMAC_CH_NUM];

	uint8	u1Dummy7[3776];								/* OFFSET 0x140 - 0x0FFF   */
	
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
	uint8	u1Dummy8[4096];								/* OFFSET 0x1000 - 0x1FFF   */
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
	union												/* DMAjRCHS 0x1000 */
	{
		uint32	u4Data;									/* 32-bit Access           */
		struct											/* Bit Access              */
		{
			uint32	b8RCHS					:8;			/* RCHS                    */
			uint32	b24Dummy1				:24;		/* Reserved Bits           */
		} stBit;
	} unRCHS;
	
	uint8	u1Dummy8[4092];								/* OFFSET 0x1004 - 0x1FFF   */
#endif /* MCAL_SPAL_TARGET */

	struct												/* OFFSET 0x2000 - 0x27D8  */
	{
		uint32	u4SAR;									/* DMAjSAR_n OFFSET 0x00   */

		uint32	u4DAR;									/* DMAjDAR_n OFFSET 0x04   */

		uint32	u4TSR;									/* DMAjTSR_n OFFSET 0x08   */

		uint32	u4TSRB;									/* DMAjTSRB_n OFFSET 0x0C  */

		union											/* DMAjTMR_n OFFSET 0x10   */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
				uint32	b4STS				:4;			/* STS                     */
				uint32	b4DTS				:4;			/* DTS                     */
				uint32	b2SM				:2;			/* SM                      */
				uint32	b2DM				:2;			/* DM                      */
				uint32	xTRS				:1;			/* TRS                     */
				uint32	b3Dummy1			:3;			/* Reserved Bits           */
				uint32	b4PRI				:4;			/* PRI                     */
				uint32	b4SLM				:4;			/* SLM                     */
				uint32	b8Dummy2			:8;			/* Reserved Bits           */
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
				uint32	b4STS				:4;			/* STS                     */
				uint32	b4DTS				:4;			/* DTS                     */
				uint32	xSM				    :1;			/* SM                      */
				uint32	xDummy1			    :1;			/* Reserved Bit            */
				uint32	xDM				    :1;			/* DM                      */
				uint32	xDummy2			    :1;			/* Reserved Bit            */
				uint32	xTRS				:1;			/* TRS                     */
				uint32	b3Dummy3			:3;			/* Reserved Bits           */
				uint32	b4PRI				:4;			/* PRI                     */
				uint32	b4SLM				:4;			/* SLM                     */
				uint32	b8Dummy4			:8;			/* Reserved Bits           */
#endif /* MCAL_SPAL_TARGET */
			} stBit;
		} unTMR;

		union											/* DMAjCHCR_n OFFSET 0x14  */
		{
			uint16	u2Data;								/* 16-bit Access           */
			struct										/* Bit Access              */
			{
				uint16	xDE					:1;			/* DE                      */
				uint16	xIE					:1;			/* IE                      */
				uint16	xDSIE				:1;			/* DSIE                    */
				uint16	xCAIE				:1;			/* CAIE                    */
				uint16	xCAEE				:1;			/* CAEE                    */
				uint16	b3Dummy1			:3;			/* Reserved Bits           */
				uint16	xDPB				:1;			/* DPB                     */
				uint16	xDPE				:1;			/* DPE                     */
				uint16	b6Dummy2			:6;			/* Reserved Bits           */
			} stBit;
		} unCHCR;

		union											/* DMAjCHSTP_n OFFSET 0x16 */
		{
			uint16	u2Data;								/* 16-bit Access           */
			struct										/* Bit Access              */
			{
				uint16	xSTP				:1;			/* STP                     */
				uint16	b15Dummy1			:15;		/* Reserved Bits           */
			} stBit;
		} unCHSTP;

		union											/* DMAjCHSTA_n OFFSET 0x18 */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	xBUSY				:1;			/* BUSY                    */
				uint32	xTE					:1;			/* TE                      */
				uint32	xDSE				:1;			/* DSE                     */
				uint32	xCAE				:1;			/* CAE                     */
				uint32	b8Dummy1			:8;			/* Reserved Bits           */
				uint32	xDRQ				:1;			/* DRQ                     */
				uint32	xOVF				:1;			/* OVF                     */
				uint32	b18Dummy2			:18;		/* Reserved Bits           */
			} stBit;
		} unCHSTA;

		union											/* DMAjCHFCR_n OFFSET 0x1C */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	xDEC				:1;			/* DEC                     */
				uint32	xTEC				:1;			/* TEC                     */
				uint32	xDSEC				:1;			/* DSEC                    */
				uint32	xCAEC				:1;			/* CAEC                    */
				uint32	b5Dummy1			:5;			/* Reserved Bits           */
				uint32	xDPEC				:1;			/* DPEC                    */
				uint32	b2Dummy2			:2;			/* Reserved Bits           */
				uint32	xDRQC				:1;			/* DRQC                    */
				uint32	xOVFC				:1;			/* OVFC                    */
				uint32	b18Dummy3			:18;		/* Reserved Bits           */
			} stBit;
		} unCHFCR;

		uint32	u4GIAI;									/* DMAjGIAI_n OFFSET 0x20  */

		uint32	u4GOAI;									/* DMAjGOAI_n OFFSET 0x24  */

		uint32	u4SIAI;									/* DMAjSIAI_n OFFSET 0x28  */

		uint32	u4SOAI;									/* DMAjSOAI_n OFFSET 0x2C  */

		uint8	u1Dummy1[8];							/* OFFSET 0x30 - 0x37      */

		union											/* DMAjSGST_n OFFSET 0x38  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	b14GICNT			:14;		/* GICNT                   */
				uint32	b2Dummy1			:2;			/* Reserved Bits           */
				uint32	b14SICNT			:14;		/* SICNT                   */
				uint32	b2Dummy2			:2;			/* Reserved Bits           */
			} stBit;
		} unSGST;

		union											/* DMAjSGCR_n OFFSET 0x3C  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	b14GIRPT			:14;		/* GIRPT                   */
				uint32	xDummy1				:1;			/* Reserved Bits           */
				uint32	xGEN				:1;			/* GEN                     */
				uint32	b14SIRPT			:14;		/* SICNT                   */
				uint32	xZF					:1;			/* ZF                      */
				uint32	xSEN				:1;			/* SEN                     */
			} stBit;
		} unSGCR;

		union											/* DMAjRS_n OFFSET 0x40    */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	b8RS				:8;			/* RS                      */
				uint32	xDummy1				:1;			/* Reserved Bits           */
				uint32	xDRQI				:1;			/* DRQI                    */
				uint32	xPLE				:1;			/* PLE                     */
				uint32	xFPT				:1;			/* FPT                     */
				uint32	b3TL				:3;			/* TL                      */
				uint32	xDummy2				:1;			/* Reserved Bits           */
				uint32	b16TC				:16;		/* TC                      */
			} stBit;
		} unRS;

		uint8	u1Dummy2[4];							/* OFFSET 0x44 - 0x47      */

		union											/* DMAjBUFCR_n OFFSET 0x48 */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	b8ULB				:8;			/* ULB                     */
				uint32	b24Dummy1			:24;		/* Reserved Bits           */
			} stBit;
		} unBUFCR;

		uint8	u1Dummy3[4];							/* OFFSET 0x4C - 0x4F      */

		union											/* DMAjDPPTR_n OFFSET 0x50 */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	xCF					:1;			/* CF                      */
				uint32	xDIE				:1;			/* DIE                     */
				uint32	b10PTR				:10;		/* PTR                     */
				uint32	b20Dummy1			:20;		/* Reserved Bits           */
			} stBit;
		} unDPPTR;

		union											/* DMAjDPCR_n OFFSET 0x54  */
		{
			uint32	u4Data;								/* 32-bit Access           */
			struct										/* Bit Access              */
			{
				uint32	b11UPF				:11;		/* UPF                     */
				uint32	b21Dummy1			:21;		/* Reserved Bits           */
			} stBit;
		} unDPCR;

		uint8	u1Dummy4[40];							/* OFFSET 0x58 - 0x7F      */

	} stDMAC_CH[DMA_DMAC_CH_NUM];

} Reg_Dma_Type;

typedef	struct
{
	uint32	u4DesRAM[DMA_DMAC_DESCRIPTOR_NUM];			/* Descriptor RAM */
} Reg_Dram_Type;

/*==============================================================================================*/
/*	register BIT definition																		*/
/*==============================================================================================*/
/* DMACSEL */
#define		DMA_DMACSEL_SEL15				(BIT31 + BIT30)
#define		DMA_DMACSEL_SEL14				(BIT29 + BIT28)
#define		DMA_DMACSEL_SEL13				(BIT27 + BIT26)
#define		DMA_DMACSEL_SEL12				(BIT25 + BIT24)
#define		DMA_DMACSEL_SEL11				(BIT23 + BIT22)
#define		DMA_DMACSEL_SEL10				(BIT21 + BIT20)
#define		DMA_DMACSEL_SEL9				(BIT19 + BIT18)
#define		DMA_DMACSEL_SEL8				(BIT17 + BIT16)
#define		DMA_DMACSEL_SEL7				(BIT15 + BIT14)
#define		DMA_DMACSEL_SEL6				(BIT13 + BIT12)
#define		DMA_DMACSEL_SEL5				(BIT11 + BIT10)
#define		DMA_DMACSEL_SEL4				(BIT9 + BIT8)
#define		DMA_DMACSEL_SEL3				(BIT7 + BIT6)
#define		DMA_DMACSEL_SEL2				(BIT5 + BIT4)
#define		DMA_DMACSEL_SEL1				(BIT3 + BIT2)
#define		DMA_DMACSEL_SEL0				(BIT1 + BIT0)
	#define		DMA_DMACSEL_SEL_DMA0		(0)
	#define		DMA_DMACSEL_SEL_DMA1		(1)
	#define		DMA_DMACSEL_SEL_DMA2		(2)
	#define		DMA_DMACSEL_SEL_DMA3		(3)

#define		DMA_DMACSEL_SEL_ALL0			(0x00000000U)

/* DTSSEL */
#define		DMA_DTSSEL_SEL7					(BIT30 + BIT29 + BIT28)
#define		DMA_DTSSEL_SEL7_0				(BIT28)
#define		DMA_DTSSEL_SEL6					(BIT26 + BIT25 + BIT24)
#define		DMA_DTSSEL_SEL6_0				(BIT24)
#define		DMA_DTSSEL_SEL5					(BIT22 + BIT21 + BIT20)
#define		DMA_DTSSEL_SEL5_0				(BIT20)
#define		DMA_DTSSEL_SEL4					(BIT18 + BIT17 + BIT16)
#define		DMA_DTSSEL_SEL4_0				(BIT16)
#define		DMA_DTSSEL_SEL3					(BIT14 + BIT13 + BIT12)
#define		DMA_DTSSEL_SEL3_0				(BIT12)
#define		DMA_DTSSEL_SEL2					(BIT10 + BIT9 + BIT8)
#define		DMA_DTSSEL_SEL2_0				(BIT8)
#define		DMA_DTSSEL_SEL1					(BIT6 + BIT5 + BIT4)
#define		DMA_DTSSEL_SEL1_0				(BIT4)
#define		DMA_DTSSEL_SEL0					(BIT2 + BIT1 + BIT0)
#define		DMA_DTSSEL_SEL0_0				(BIT0)
	#define		DMA_DTSSEL_SEL_DMA0			(0)
	#define		DMA_DTSSEL_SEL_DMA1			(1)
	#define		DMA_DTSSEL_SEL_DMA2			(2)
	#define		DMA_DTSSEL_SEL_DMA3			(3)
	#define		DMA_DTSSEL_SEL_DMA4			(4)
	#define		DMA_DTSSEL_SEL_DMA5			(5)

#define		DMA_DTSSEL_SEL_ALL0				(0x00000000U)	/* DTS Transfer Request Group 0 */
	

/* DMAjRCHS */
#define		DMA_RCHS_RCHS7 					(BIT7)
#define		DMA_RCHS_RCHS6 					(BIT6)
#define		DMA_RCHS_RCHS5 					(BIT5)
#define		DMA_RCHS_RCHS4 					(BIT4)
#define		DMA_RCHS_RCHS3 					(BIT3)
#define		DMA_RCHS_RCHS2 					(BIT2)
#define		DMA_RCHS_RCHS1 					(BIT1)
#define		DMA_RCHS_RCHS0 					(BIT0)

	#define  DMA_RCHS_RCHS_DISABLE  		(0)
	#define  DMA_RCHS_RCHS_ENABLE  			(1)

/* DTSCTL1 */
#define		DMA_DTSCTL1_DTSUST				(BIT0)
	#define		DMA_DTSCTL1_DTSUST_START	(0)
	#define		DMA_DTSCTL1_DTSUST_SUSPEND	(1)

/* DTSCTL2 */
#define		DMA_DTSCTL2_DTSTIT				(BIT0)
	#define		DMA_DTSCTL2_DTSTIT_CANCEL	(1)

/* DTSSTS */
#define		DMA_DTSSTS_DTSCYC				(BIT8)
#define		DMA_DTSSTS_DTSACH				(BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1)
#define		DMA_DTSSTS_DTSACH_0				(BIT1)
	#define		DMA_DTSSTS_DTSACH_OFFSET	(1)
#define		DMA_DTSSTS_DTSACT				(BIT0)
	#define		DMA_DTSSTS_DTSACT_IDLE		(0)
	#define		DMA_DTSSTS_DTSACT_BUSY		(1)


/* DTSER */
#define		DMA_DTSER_DTSERCH				(BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		DMA_DTSER_DTSERCH_0				(BIT8)
#define		DMA_DTSER_DTSERWR				(BIT1)
	#define		DMA_DTSER_DTSERWR_READ		(0)
	#define		DMA_DTSER_DTSERWR_WRITE		(1)
#define		DMA_DTSER_DTSER					(BIT0)
	#define		DMA_DTSER_DTSER_NOERR		(0)
	#define		DMA_DTSER_DTSER_ERR			(1)

/* DTSPR0 */
#define		DMA_DTSPR0_DTS15PR				(BIT31 + BIT30)
#define		DMA_DTSPR0_DTS15PR_0			(BIT30)
#define		DMA_DTSPR0_DTS14PR				(BIT29 + BIT28)
#define		DMA_DTSPR0_DTS14PR_0			(BIT28)
#define		DMA_DTSPR0_DTS13PR				(BIT27 + BIT26)
#define		DMA_DTSPR0_DTS13PR_0			(BIT26)
#define		DMA_DTSPR0_DTS12PR				(BIT25 + BIT24)
#define		DMA_DTSPR0_DTS12PR_0			(BIT24)
#define		DMA_DTSPR0_DTS11PR				(BIT23 + BIT22)
#define		DMA_DTSPR0_DTS11PR_0			(BIT22)
#define		DMA_DTSPR0_DTS10PR				(BIT21 + BIT20)
#define		DMA_DTSPR0_DTS10PR_0			(BIT20)
#define		DMA_DTSPR0_DTS9PR				(BIT19 + BIT18)
#define		DMA_DTSPR0_DTS9PR_0				(BIT18)
#define		DMA_DTSPR0_DTS8PR				(BIT17 + BIT16)
#define		DMA_DTSPR0_DTS8PR_0				(BIT16)
#define		DMA_DTSPR0_DTS7PR				(BIT15 + BIT14)
#define		DMA_DTSPR0_DTS7PR_0				(BIT14)
#define		DMA_DTSPR0_DTS6PR				(BIT13 + BIT12)
#define		DMA_DTSPR0_DTS6PR_0				(BIT12)
#define		DMA_DTSPR0_DTS5PR				(BIT11 + BIT10)
#define		DMA_DTSPR0_DTS5PR_0				(BIT10)
#define		DMA_DTSPR0_DTS4PR				(BIT9 + BIT8)
#define		DMA_DTSPR0_DTS4PR_0				(BIT8)
#define		DMA_DTSPR0_DTS3PR				(BIT7 + BIT6)
#define		DMA_DTSPR0_DTS3PR_0				(BIT6)
#define		DMA_DTSPR0_DTS2PR				(BIT5 + BIT4)
#define		DMA_DTSPR0_DTS2PR_0				(BIT4)
#define		DMA_DTSPR0_DTS1PR				(BIT3 + BIT2)
#define		DMA_DTSPR0_DTS1PR_0				(BIT2)
#define		DMA_DTSPR0_DTS0PR				(BIT1 + BIT0)
#define		DMA_DTSPR0_DTS0PR_0				(BIT0)

/* DTSPR1 */
#define		DMA_DTSPR1_DTS31PR				(BIT31 + BIT30)
#define		DMA_DTSPR1_DTS31PR_0			(BIT30)
#define		DMA_DTSPR1_DTS30PR				(BIT29 + BIT28)
#define		DMA_DTSPR1_DTS30PR_0			(BIT28)
#define		DMA_DTSPR1_DTS29PR				(BIT27 + BIT26)
#define		DMA_DTSPR1_DTS29PR_0			(BIT26)
#define		DMA_DTSPR1_DTS28PR				(BIT25 + BIT24)
#define		DMA_DTSPR1_DTS28PR_0			(BIT24)
#define		DMA_DTSPR1_DTS27PR				(BIT23 + BIT22)
#define		DMA_DTSPR1_DTS27PR_0			(BIT22)
#define		DMA_DTSPR1_DTS26PR				(BIT21 + BIT20)
#define		DMA_DTSPR1_DTS26PR_0			(BIT20)
#define		DMA_DTSPR1_DTS25PR				(BIT19 + BIT18)
#define		DMA_DTSPR1_DTS25PR_0			(BIT18)
#define		DMA_DTSPR1_DTS24PR				(BIT17 + BIT16)
#define		DMA_DTSPR1_DTS24PR_0			(BIT16)
#define		DMA_DTSPR1_DTS23PR				(BIT15 + BIT14)
#define		DMA_DTSPR1_DTS23PR_0			(BIT14)
#define		DMA_DTSPR1_DTS22PR				(BIT13 + BIT12)
#define		DMA_DTSPR1_DTS22PR_0			(BIT12)
#define		DMA_DTSPR1_DTS21PR				(BIT11 + BIT10)
#define		DMA_DTSPR1_DTS21PR_0			(BIT10)
#define		DMA_DTSPR1_DTS20PR				(BIT9 + BIT8)
#define		DMA_DTSPR1_DTS20PR_0			(BIT8)
#define		DMA_DTSPR1_DTS19PR				(BIT7 + BIT6)
#define		DMA_DTSPR1_DTS19PR_0			(BIT6)
#define		DMA_DTSPR1_DTS18PR				(BIT5 + BIT4)
#define		DMA_DTSPR1_DTS18PR_0			(BIT4)
#define		DMA_DTSPR1_DTS17PR				(BIT3 + BIT2)
#define		DMA_DTSPR1_DTS17PR_0			(BIT2)
#define		DMA_DTSPR1_DTS16PR				(BIT1 + BIT0)
#define		DMA_DTSPR1_DTS16PR_0			(BIT0)

/* DTSPR2 */
#define		DMA_DTSPR2_DTS47PR				(BIT31 + BIT30)
#define		DMA_DTSPR2_DTS47PR_0			(BIT30)
#define		DMA_DTSPR2_DTS46PR				(BIT29 + BIT28)
#define		DMA_DTSPR2_DTS46PR_0			(BIT28)
#define		DMA_DTSPR2_DTS45PR				(BIT27 + BIT26)
#define		DMA_DTSPR2_DTS45PR_0			(BIT26)
#define		DMA_DTSPR2_DTS44PR				(BIT25 + BIT24)
#define		DMA_DTSPR2_DTS44PR_0			(BIT24)
#define		DMA_DTSPR2_DTS43PR				(BIT23 + BIT22)
#define		DMA_DTSPR2_DTS43PR_0			(BIT22)
#define		DMA_DTSPR2_DTS42PR				(BIT21 + BIT20)
#define		DMA_DTSPR2_DTS42PR_0			(BIT20)
#define		DMA_DTSPR2_DTS41PR				(BIT19 + BIT18)
#define		DMA_DTSPR2_DTS41PR_0			(BIT18)
#define		DMA_DTSPR2_DTS40PR				(BIT17 + BIT16)
#define		DMA_DTSPR2_DTS40PR_0			(BIT16)
#define		DMA_DTSPR2_DTS39PR				(BIT15 + BIT14)
#define		DMA_DTSPR2_DTS39PR_0			(BIT14)
#define		DMA_DTSPR2_DTS38PR				(BIT13 + BIT12)
#define		DMA_DTSPR2_DTS38PR_0			(BIT12)
#define		DMA_DTSPR2_DTS37PR				(BIT11 + BIT10)
#define		DMA_DTSPR2_DTS37PR_0			(BIT10)
#define		DMA_DTSPR2_DTS36PR				(BIT9 + BIT8)
#define		DMA_DTSPR2_DTS36PR_0			(BIT8)
#define		DMA_DTSPR2_DTS35PR				(BIT7 + BIT6)
#define		DMA_DTSPR2_DTS35PR_0			(BIT6)
#define		DMA_DTSPR2_DTS34PR				(BIT5 + BIT4)
#define		DMA_DTSPR2_DTS34PR_0			(BIT4)
#define		DMA_DTSPR2_DTS33PR				(BIT3 + BIT2)
#define		DMA_DTSPR2_DTS33PR_0			(BIT2)
#define		DMA_DTSPR2_DTS32PR				(BIT1 + BIT0)
#define		DMA_DTSPR2_DTS32PR_0			(BIT0)

/* DTSPR3 */
#define		DMA_DTSPR3_DTS63PR				(BIT31 + BIT30)
#define		DMA_DTSPR3_DTS63PR_0			(BIT30)
#define		DMA_DTSPR3_DTS62PR				(BIT29 + BIT28)
#define		DMA_DTSPR3_DTS62PR_0			(BIT28)
#define		DMA_DTSPR3_DTS61PR				(BIT27 + BIT26)
#define		DMA_DTSPR3_DTS61PR_0			(BIT26)
#define		DMA_DTSPR3_DTS60PR				(BIT25 + BIT24)
#define		DMA_DTSPR3_DTS60PR_0			(BIT24)
#define		DMA_DTSPR3_DTS59PR				(BIT23 + BIT22)
#define		DMA_DTSPR3_DTS59PR_0			(BIT22)
#define		DMA_DTSPR3_DTS58PR				(BIT21 + BIT20)
#define		DMA_DTSPR3_DTS58PR_0			(BIT20)
#define		DMA_DTSPR3_DTS57PR				(BIT19 + BIT18)
#define		DMA_DTSPR3_DTS57PR_0			(BIT18)
#define		DMA_DTSPR3_DTS56PR				(BIT17 + BIT16)
#define		DMA_DTSPR3_DTS56PR_0			(BIT16)
#define		DMA_DTSPR3_DTS55PR				(BIT15 + BIT14)
#define		DMA_DTSPR3_DTS55PR_0			(BIT14)
#define		DMA_DTSPR3_DTS54PR				(BIT13 + BIT12)
#define		DMA_DTSPR3_DTS54PR_0			(BIT12)
#define		DMA_DTSPR3_DTS53PR				(BIT11 + BIT10)
#define		DMA_DTSPR3_DTS53PR_0			(BIT10)
#define		DMA_DTSPR3_DTS52PR				(BIT9 + BIT8)
#define		DMA_DTSPR3_DTS52PR_0			(BIT8)
#define		DMA_DTSPR3_DTS51PR				(BIT7 + BIT6)
#define		DMA_DTSPR3_DTS51PR_0			(BIT6)
#define		DMA_DTSPR3_DTS50PR				(BIT5 + BIT4)
#define		DMA_DTSPR3_DTS50PR_0			(BIT4)
#define		DMA_DTSPR3_DTS49PR				(BIT3 + BIT2)
#define		DMA_DTSPR3_DTS49PR_0			(BIT2)
#define		DMA_DTSPR3_DTS48PR				(BIT1 + BIT0)
#define		DMA_DTSPR3_DTS48PR_0			(BIT0)

/* DTSPR4 */
#define		DMA_DTSPR4_DTS79PR				(BIT31 + BIT30)
#define		DMA_DTSPR4_DTS79PR_0			(BIT30)
#define		DMA_DTSPR4_DTS78PR				(BIT29 + BIT28)
#define		DMA_DTSPR4_DTS78PR_0			(BIT28)
#define		DMA_DTSPR4_DTS77PR				(BIT27 + BIT26)
#define		DMA_DTSPR4_DTS77PR_0			(BIT26)
#define		DMA_DTSPR4_DTS76PR				(BIT25 + BIT24)
#define		DMA_DTSPR4_DTS76PR_0			(BIT24)
#define		DMA_DTSPR4_DTS75PR				(BIT23 + BIT22)
#define		DMA_DTSPR4_DTS75PR_0			(BIT22)
#define		DMA_DTSPR4_DTS74PR				(BIT21 + BIT20)
#define		DMA_DTSPR4_DTS74PR_0			(BIT20)
#define		DMA_DTSPR4_DTS73PR				(BIT19 + BIT18)
#define		DMA_DTSPR4_DTS73PR_0			(BIT18)
#define		DMA_DTSPR4_DTS72PR				(BIT17 + BIT16)
#define		DMA_DTSPR4_DTS72PR_0			(BIT16)
#define		DMA_DTSPR4_DTS71PR				(BIT15 + BIT14)
#define		DMA_DTSPR4_DTS71PR_0			(BIT14)
#define		DMA_DTSPR4_DTS70PR				(BIT13 + BIT12)
#define		DMA_DTSPR4_DTS70PR_0			(BIT12)
#define		DMA_DTSPR4_DTS69PR				(BIT11 + BIT10)
#define		DMA_DTSPR4_DTS69PR_0			(BIT10)
#define		DMA_DTSPR4_DTS68PR				(BIT9 + BIT8)
#define		DMA_DTSPR4_DTS68PR_0			(BIT8)
#define		DMA_DTSPR4_DTS67PR				(BIT7 + BIT6)
#define		DMA_DTSPR4_DTS67PR_0			(BIT6)
#define		DMA_DTSPR4_DTS66PR				(BIT5 + BIT4)
#define		DMA_DTSPR4_DTS66PR_0			(BIT4)
#define		DMA_DTSPR4_DTS65PR				(BIT3 + BIT2)
#define		DMA_DTSPR4_DTS65PR_0			(BIT2)
#define		DMA_DTSPR4_DTS64PR				(BIT1 + BIT0)
#define		DMA_DTSPR4_DTS64PR_0			(BIT0)

/* DTSPR5 */
#define		DMA_DTSPR5_DTS95PR				(BIT31 + BIT30)
#define		DMA_DTSPR5_DTS95PR_0			(BIT30)
#define		DMA_DTSPR5_DTS94PR				(BIT29 + BIT28)
#define		DMA_DTSPR5_DTS94PR_0			(BIT28)
#define		DMA_DTSPR5_DTS93PR				(BIT27 + BIT26)
#define		DMA_DTSPR5_DTS93PR_0			(BIT26)
#define		DMA_DTSPR5_DTS92PR				(BIT25 + BIT24)
#define		DMA_DTSPR5_DTS92PR_0			(BIT24)
#define		DMA_DTSPR5_DTS91PR				(BIT23 + BIT22)
#define		DMA_DTSPR5_DTS91PR_0			(BIT22)
#define		DMA_DTSPR5_DTS90PR				(BIT21 + BIT20)
#define		DMA_DTSPR5_DTS90PR_0			(BIT20)
#define		DMA_DTSPR5_DTS89PR				(BIT19 + BIT18)
#define		DMA_DTSPR5_DTS89PR_0			(BIT18)
#define		DMA_DTSPR5_DTS88PR				(BIT17 + BIT16)
#define		DMA_DTSPR5_DTS88PR_0			(BIT16)
#define		DMA_DTSPR5_DTS87PR				(BIT15 + BIT14)
#define		DMA_DTSPR5_DTS87PR_0			(BIT14)
#define		DMA_DTSPR5_DTS86PR				(BIT13 + BIT12)
#define		DMA_DTSPR5_DTS86PR_0			(BIT12)
#define		DMA_DTSPR5_DTS85PR				(BIT11 + BIT10)
#define		DMA_DTSPR5_DTS85PR_0			(BIT10)
#define		DMA_DTSPR5_DTS84PR				(BIT9 + BIT8)
#define		DMA_DTSPR5_DTS84PR_0			(BIT8)
#define		DMA_DTSPR5_DTS83PR				(BIT7 + BIT6)
#define		DMA_DTSPR5_DTS83PR_0			(BIT6)
#define		DMA_DTSPR5_DTS82PR				(BIT5 + BIT4)
#define		DMA_DTSPR5_DTS82PR_0			(BIT4)
#define		DMA_DTSPR5_DTS81PR				(BIT3 + BIT2)
#define		DMA_DTSPR5_DTS81PR_0			(BIT2)
#define		DMA_DTSPR5_DTS80PR				(BIT1 + BIT0)
#define		DMA_DTSPR5_DTS80PR_0			(BIT0)

/* DTSPR6 */
#define		DMA_DTSPR6_DTS111PR				(BIT31 + BIT30)
#define		DMA_DTSPR6_DTS111PR_0			(BIT30)
#define		DMA_DTSPR6_DTS110PR				(BIT29 + BIT28)
#define		DMA_DTSPR6_DTS110PR_0			(BIT28)
#define		DMA_DTSPR6_DTS109PR				(BIT27 + BIT26)
#define		DMA_DTSPR6_DTS109PR_0			(BIT26)
#define		DMA_DTSPR6_DTS108PR				(BIT25 + BIT24)
#define		DMA_DTSPR6_DTS108PR_0			(BIT24)
#define		DMA_DTSPR6_DTS107PR				(BIT23 + BIT22)
#define		DMA_DTSPR6_DTS107PR_0			(BIT22)
#define		DMA_DTSPR6_DTS106PR				(BIT21 + BIT20)
#define		DMA_DTSPR6_DTS106PR_0			(BIT20)
#define		DMA_DTSPR6_DTS105PR				(BIT19 + BIT18)
#define		DMA_DTSPR6_DTS105PR_0			(BIT18)
#define		DMA_DTSPR6_DTS104PR				(BIT17 + BIT16)
#define		DMA_DTSPR6_DTS104PR_0			(BIT16)
#define		DMA_DTSPR6_DTS103PR				(BIT15 + BIT14)
#define		DMA_DTSPR6_DTS103PR_0			(BIT14)
#define		DMA_DTSPR6_DTS102PR				(BIT13 + BIT12)
#define		DMA_DTSPR6_DTS102PR_0			(BIT12)
#define		DMA_DTSPR6_DTS101PR				(BIT11 + BIT10)
#define		DMA_DTSPR6_DTS101PR_0			(BIT10)
#define		DMA_DTSPR6_DTS100PR				(BIT9 + BIT8)
#define		DMA_DTSPR6_DTS100PR_0			(BIT8)
#define		DMA_DTSPR6_DTS99PR				(BIT7 + BIT6)
#define		DMA_DTSPR6_DTS99PR_0			(BIT6)
#define		DMA_DTSPR6_DTS98PR				(BIT5 + BIT4)
#define		DMA_DTSPR6_DTS98PR_0			(BIT4)
#define		DMA_DTSPR6_DTS97PR				(BIT3 + BIT2)
#define		DMA_DTSPR6_DTS97PR_0			(BIT2)
#define		DMA_DTSPR6_DTS96PR				(BIT1 + BIT0)
#define		DMA_DTSPR6_DTS96PR_0			(BIT0)

/* DTSPR7 */
#define		DMA_DTSPR7_DTS127PR				(BIT31 + BIT30)
#define		DMA_DTSPR7_DTS127PR_0			(BIT30)
#define		DMA_DTSPR7_DTS126PR				(BIT29 + BIT28)
#define		DMA_DTSPR7_DTS126PR_0			(BIT28)
#define		DMA_DTSPR7_DTS125PR				(BIT27 + BIT26)
#define		DMA_DTSPR7_DTS125PR_0			(BIT26)
#define		DMA_DTSPR7_DTS124PR				(BIT25 + BIT24)
#define		DMA_DTSPR7_DTS124PR_0			(BIT24)
#define		DMA_DTSPR7_DTS123PR				(BIT23 + BIT22)
#define		DMA_DTSPR7_DTS123PR_0			(BIT22)
#define		DMA_DTSPR7_DTS122PR				(BIT21 + BIT20)
#define		DMA_DTSPR7_DTS122PR_0			(BIT20)
#define		DMA_DTSPR7_DTS121PR				(BIT19 + BIT18)
#define		DMA_DTSPR7_DTS121PR_0			(BIT18)
#define		DMA_DTSPR7_DTS120PR				(BIT17 + BIT16)
#define		DMA_DTSPR7_DTS120PR_0			(BIT16)
#define		DMA_DTSPR7_DTS119PR				(BIT15 + BIT14)
#define		DMA_DTSPR7_DTS119PR_0			(BIT14)
#define		DMA_DTSPR7_DTS118PR				(BIT13 + BIT12)
#define		DMA_DTSPR7_DTS118PR_0			(BIT12)
#define		DMA_DTSPR7_DTS117PR				(BIT11 + BIT10)
#define		DMA_DTSPR7_DTS117PR_0			(BIT10)
#define		DMA_DTSPR7_DTS116PR				(BIT9 + BIT8)
#define		DMA_DTSPR7_DTS116PR_0			(BIT8)
#define		DMA_DTSPR7_DTS115PR				(BIT7 + BIT6)
#define		DMA_DTSPR7_DTS115PR_0			(BIT6)
#define		DMA_DTSPR7_DTS114PR				(BIT5 + BIT4)
#define		DMA_DTSPR7_DTS114PR_0			(BIT4)
#define		DMA_DTSPR7_DTS113PR				(BIT3 + BIT2)
#define		DMA_DTSPR7_DTS113PR_0			(BIT2)
#define		DMA_DTSPR7_DTS112PR				(BIT1 + BIT0)
#define		DMA_DTSPR7_DTS112PR_0			(BIT0)

	#define		DMA_DTSPR_PR_ALL2			(0xAAAAAAAAU)

/* DTSCM */
#define		DMA_DTSCM_CHAIN_RESTRICT		(BIT31)
#define		DMA_DTSCM_CHAIN_SPID			(BIT30 + BIT29 + BIT28 + BIT27 + BIT26)
#define		DMA_DTSCM_CHAIN_SPID_0			(BIT26)
#define		DMA_DTSCM_CHAIN_UM				(BIT25)
#define		DMA_DTSCM_SPID					(BIT22 + BIT21 + BIT20 + BIT19 + BIT18)
#define		DMA_DTSCM_SPID_0				(BIT18)
#define		DMA_DTSCM_UM					(BIT17)
	#define		DMA_DTSCM_UM_SV				(0)
	#define		DMA_DTSCM_UM_UM				(1)
#define		DMA_DTSCM_CMC					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_DTSCM_CMC_0					(BIT0)

/* DTTC */
#define		DMA_DTTC_ARC					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_DTTC_ARC_0					(BIT16)
	#define		DMA_DTTC_ARC_NOUSE			(0)
#define		DMA_DTTC_TRC					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_DTTC_TRC_0					(BIT0)

/* DTTCT */
#define		DMA_DTTCT_ESE					(BIT27)
	#define		DMA_DTTCT_ESE_CONTINUE		(0)
	#define		DMA_DTTCT_ESE_ABORT			(1)
#define		DMA_DTTCT_CHNSEL				(BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18)
#define		DMA_DTTCT_CHNSEL_0				(BIT18)
	#define		DMA_DTTCT_CHNSEL_CH0		(0)
#define		DMA_DTTCT_CHNE					(BIT17 + BIT16)
#define		DMA_DTTCT_CHNE_0				(BIT16)
	#define		DMA_DTTCT_CHNE_DISABLE			(0)
	#define		DMA_DTTCT_CHNE_LAST_TRANS_CHAIN	(1)
	#define		DMA_DTTCT_CHNE_ALWAYS_CHAIN		(3)
#define		DMA_DTTCT_CCE					(BIT15)
	#define		DMA_DTTCT_CCE_DISABLE		(0)
	#define		DMA_DTTCT_CCE_ENABLE		(1)
#define		DMA_DTTCT_TCE					(BIT14)
	#define		DMA_DTTCT_TCE_DISABLE		(0)
	#define		DMA_DTTCT_TCE_ENABLE		(1)
#define		DMA_DTTCT_RLD2M					(BIT12 + BIT11)
#define		DMA_DTTCT_RLD2M_0				(BIT11)
	#define		DMA_DTTCT_RLD2M_DISABLE			(0)
	#define		DMA_DTTCT_RLD2M_SRC_ADR_RELOAD	(1)
	#define		DMA_DTTCT_RLD2M_DST_ADR_RELOAD	(2)
	#define		DMA_DTTCT_RLD2M_BOTH_RELOAD		(3)
#define		DMA_DTTCT_RLD1M					(BIT10 + BIT9)
#define		DMA_DTTCT_RLD1M_0				(BIT9)
	#define		DMA_DTTCT_RLD1M_DISABLE			(0)
	#define		DMA_DTTCT_RLD1M_SRC_ADR_RELOAD	(1)
	#define		DMA_DTTCT_RLD1M_DST_ADR_RELOAD	(2)
	#define		DMA_DTTCT_RLD1M_BOTH_RELOAD		(3)
#define		DMA_DTTCT_DACM					(BIT8 + BIT7)
#define		DMA_DTTCT_DACM_0				(BIT7)
	#define		DMA_DTTCT_DACM_ADDR_INC		(0)
	#define		DMA_DTTCT_DACM_ADDR_DEC		(1)
	#define		DMA_DTTCT_DACM_ADDR_FIX		(2)
#define		DMA_DTTCT_SACM					(BIT6 + BIT5)
#define		DMA_DTTCT_SACM_0				(BIT5)
	#define		DMA_DTTCT_SACM_ADDR_INC		(0)
	#define		DMA_DTTCT_SACM_ADDR_DEC		(1)
	#define		DMA_DTTCT_SACM_ADDR_FIX		(2)
#define		DMA_DTTCT_DS					(BIT4 + BIT3 + BIT2)
#define		DMA_DTTCT_DS_0					(BIT2)
	#define		DMA_DTTCT_DS_8BIT			(0)
	#define		DMA_DTTCT_DS_16BIT			(1)
	#define		DMA_DTTCT_DS_32BIT			(2)
	#define		DMA_DTTCT_DS_64BIT			(3)
	#define		DMA_DTTCT_DS_128BIT			(4)
#define		DMA_DTTCT_TRM					(BIT1 + BIT0)
#define		DMA_DTTCT_TRM_0					(BIT0)
	#define		DMA_DTTCT_TRM_SINGLE		(0)
	#define		DMA_DTTCT_TRM_BLOCK1		(1)
	#define		DMA_DTTCT_TRM_BLOCK2		(2)

/* DTRTC */
#define		DMA_DTRTC_RARC					(BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_DTRTC_RARC_0				(BIT16)
	#define		DMA_DTRTC_RARC_NOUSE		(0)
#define		DMA_DTRTC_RTRC					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_DTRTC_RTRC_0				(BIT0)

/* DTTCC */
#define		DMA_DTTCC_CMC					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_DTTCC_CMC_0					(BIT0)

/* DTFSL */
#define		DMA_DTFSL_REQEN					(BIT0)
	#define		DMA_DTFSL_REQEN_TRANS_DISABLE	(0)
	#define		DMA_DTFSL_REQEN_TRANS_ENABLE	(1)

/* DTFST */
#define		DMA_DTFST_ERWR					(BIT11)
	#define		DMA_DTFST_ERWR_READ			(0)
	#define		DMA_DTFST_ERWR_WRITE		(1)
#define		DMA_DTFST_ER					(BIT7)
	#define		DMA_DTFST_ER_TRANS_NOTERR	(0)
	#define		DMA_DTFST_ER_TRANS_ERR		(1)
#define		DMA_DTFST_CC					(BIT5)
	#define		DMA_DTFST_CC_NOTCOMPARE		(0)
	#define		DMA_DTFST_CC_COMPARE		(1)
#define		DMA_DTFST_TC					(BIT4)
	#define		DMA_DTFST_TC_NOTCOMPLETE	(0)
	#define		DMA_DTFST_TC_COMPLETE		(1)
#define		DMA_DTFST_OVF					(BIT1)
	#define		DMA_DTFST_OVF_NOTOVF		(0)
	#define		DMA_DTFST_OVF_OVF			(1)
#define		DMA_DTFST_DRQ					(BIT0)
	#define		DMA_DTFST_DRQ_TRANS_NOTREQ	(0)
	#define		DMA_DTFST_DRQ_TRANS_REQ		(1)

/* DTFSS */
#define		DMA_DTFSS_DRQS					(BIT0)
	#define		DMA_DTFSS_DRQS_TRANS_REQ_SET	(1)

/* DTFSC */
#define		DMA_DTFSC_ERC					(BIT7)
	#define		DMA_DTFSC_ERC_TRANS_ERR_CLEAR	(1)
#define		DMA_DTFSC_CCC					(BIT5)
	#define		DMA_DTFSC_CCC_COMPARE_CLEAR	(1)
#define		DMA_DTFSC_TCC					(BIT4)
	#define		DMA_DTFSC_TCC_COMPLETE_CLEAR	(1)
#define		DMA_DTFSC_OVFC					(BIT1)
	#define		DMA_DTFSC_OVFC_CLEAR	(1)
#define		DMA_DTFSC_DRQC					(BIT0)
	#define		DMA_DTFSC_DRQC_TRANS_REQ_CLEAR	(1)

/* DMAjESTA */
#define		DMA_ESTA_AEN					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_ESTA_AEN_0					(BIT0)

/* DMAjISTA */
#define		DMA_ISTA_INT					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_ISTA_INT_0					(BIT0)

/* DMAjCHPRI */
#define		DMA_CHPRI_PRICNT				(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_CHPRI_PRICNT_0				(BIT0)

/* DMAjOR */
#define		DMA_OR_PR						(BIT9 + BIT8)
#define		DMA_OR_PR_0						(BIT8)
	#define		DMA_OR_PR_CH				(0)
	#define		DMA_OR_PR_ROUND_ROBIN		(3)
#define		DMA_OR_DME						(BIT0)
	#define		DMA_OR_DME_TRANS_DISABLE	(0)
	#define		DMA_OR_DME_TRANS_ENABLE		(1)

/* DMAjCHRST */
#define		DMA_CHRST_CLR					(BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_CHRST_CLR_0					(BIT0)

/* DMAjCM_n */
#define		DMA_CM_SPID						(BIT12 + BIT11 + BIT10 + BIT9 + BIT8)
#define		DMA_CM_SPID_0					(BIT8)
#define		DMA_CM_UM						(BIT0)
	#define		DMA_CM_UM_SUPERVISOR		(0)
	#define		DMA_CM_UM_USER				(1)

/* DMAjTMR_n */
#define		DMA_TMR_SLM						(BIT23 + BIT22 + BIT21 + BIT20)
#define		DMA_TMR_SLM_0					(BIT20)
	#define		DMA_TMR_SLM_NORMAL			(0)
#define		DMA_TMR_PRI						(BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_TMR_PRI_0					(BIT16)
	#define		DMA_TMR_PRI_DISABLE			(0)
	#define		DMA_TMR_PRI0				(8)
	#define		DMA_TMR_PRI1				(9)
	#define		DMA_TMR_PRI2				(10)
	#define		DMA_TMR_PRI3				(11)
	#define		DMA_TMR_PRI4				(12)
	#define		DMA_TMR_PRI5				(13)
	#define		DMA_TMR_PRI6				(14)
	#define		DMA_TMR_PRI7				(15)
#define		DMA_TMR_TRS						(BIT12)
	#define		DMA_TMR_TRS_AUTO_REQ		(0)
	#define		DMA_TMR_TRS_HARDWARE_REQ	(1)
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define		DMA_TMR_DM						(BIT11 + BIT10)
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define		DMA_TMR_DM						(BIT10)
#endif /* MCAL_SPAL_TARGET */
#define		DMA_TMR_DM_0					(BIT10)
	#define		DMA_TMR_DM_FIX				(0)
	#define		DMA_TMR_DM_INCREMENT		(1)
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define		DMA_TMR_SM						(BIT9 + BIT8)
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define		DMA_TMR_SM						(BIT8)
#endif /* MCAL_SPAL_TARGET */
#define		DMA_TMR_SM_0					(BIT8)
	#define		DMA_TMR_SM_FIX				(0)
	#define		DMA_TMR_SM_INCREMENT		(1)
#define		DMA_TMR_DTS						(BIT7 + BIT6 + BIT5 + BIT4)
#define		DMA_TMR_DTS_0					(BIT4)
#define		DMA_TMR_STS						(BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_TMR_STS_0					(BIT0)

/* DMAjCHCR_n */
#define		DMA_CHCR_DPE					(BIT9)
	#define		DMA_CHCR_DPE_DISABLE		(0)
	#define		DMA_CHCR_DPE_ENABLE			(1)
#define		DMA_CHCR_DPB					(BIT8)
	#define		DMA_CHCR_DPB_REGISTER_SET	(0)
	#define		DMA_CHCR_DPB_AFTER_CH		(1)
#define		DMA_CHCR_CAEE					(BIT4)
	#define		DMA_CHCR_CAEE_DISABLE		(0)
	#define		DMA_CHCR_CAEE_ENABLE		(1)
#define		DMA_CHCR_CAIE					(BIT3)
	#define		DMA_CHCR_CAIE_DISABLE		(0)
	#define		DMA_CHCR_CAIE_ENABLE		(1)
#define		DMA_CHCR_DSIE					(BIT2)
	#define		DMA_CHCR_DSIE_DISABLE		(0)
	#define		DMA_CHCR_DSIE_ENABLE		(1)
#define		DMA_CHCR_IE						(BIT1)
	#define		DMA_CHCR_IE_DISABLE			(0)
	#define		DMA_CHCR_IE_ENABLE			(1)
#define		DMA_CHCR_DE						(BIT0)
	#define		DMA_CHCR_DE_DISABLE			(0)
	#define		DMA_CHCR_DE_ENABLE			(1)

/* DMAjCHSTP_n */
#define		DMA_CHSTP_STP					(BIT0)
	#define		DMA_CHSTP_STP_RESTART		(0)
	#define		DMA_CHSTP_STP_STOP			(1)

/* DMAjCHSTA_n */
#define		DMA_CHSTA_OVF					(BIT13)
	#define		DMA_CHSTA_OVF_NOTOVF		(0)
	#define		DMA_CHSTA_OVF_OVF			(1)
#define		DMA_CHSTA_DRQ					(BIT12)
	#define		DMA_CHSTA_DRQ_TRANS_NOTREQ	(0)
	#define		DMA_CHSTA_DRQ_TRANS_REQ		(1)
#define		DMA_CHSTA_CAE					(BIT3)
	#define		DMA_CHSTA_CAE_NOTERR		(0)
	#define		DMA_CHSTA_CAE_ERR			(1)
#define		DMA_CHSTA_DSE					(BIT2)
	#define		DMA_CHSTA_DSE_RUNNING		(0)
	#define		DMA_CHSTA_DSE_STOP			(1)
#define		DMA_CHSTA_TE					(BIT1)
	#define		DMA_CHSTA_TE_RUNNING		(0)
	#define		DMA_CHSTA_TE_END			(1)
#define		DMA_CHSTA_BUSY					(BIT0)
	#define		DMA_CHSTA_BUSY_IDLE			(0)
	#define		DMA_CHSTA_BUSY_BUSY			(1)

/* DMAjCHFCR_n */
#define		DMA_CHFCR_OVFC					(BIT13)
	#define		DMA_CHFCR_OVFC_CLEAR		(1)
#define		DMA_CHFCR_DRQC					(BIT12)
	#define		DMA_CHFCR_DRQC_CLEAR		(1)
#define		DMA_CHFCR_DPEC					(BIT9)
	#define		DMA_CHFCR_DPEC_CLEAR		(1)
#define		DMA_CHFCR_CAEC					(BIT3)
	#define		DMA_CHFCR_CAEC_CLEAR		(1)
#define		DMA_CHFCR_DSEC					(BIT2)
	#define		DMA_CHFCR_DSEC_CLEAR		(1)
#define		DMA_CHFCR_TEC					(BIT1)
	#define		DMA_CHFCR_TEC_CLEAR			(1)
#define		DMA_CHFCR_DEC					(BIT0)
	#define		DMA_CHFCR_DEC_CLEAR			(1)

/* DMAjSGST_n */
#define		DMA_SGST_SICNT					(BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_SGST_SICNT_0				(BIT16)
#define		DMA_SGST_GICNT					(BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_SGST_GICNT_0				(BIT0)

/* DMAjSGCR_n */
#define		DMA_SGCR_SEN					(BIT31)
	#define		DMA_SGCR_SEN_DISABLE		(0)
	#define		DMA_SGCR_SEN_ENABLE			(1)
#define		DMA_SGCR_ZF						(BIT30)
	#define		DMA_SGCR_ZF_DISABLE			(0)
	#define		DMA_SGCR_ZF_ENABLE			(1)
#define		DMA_SGCR_SIRPT					(BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_SGCR_SIRPT_0				(BIT16)
#define		DMA_SGCR_GEN					(BIT15)
	#define		DMA_SGCR_GEN_DISABLE		(0)
	#define		DMA_SGCR_GEN_ENABLE			(1)
#define		DMA_SGCR_GIRPT					(BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_SGCR_GIRPT_0				(BIT0)

/* DMAjRS_n */
#define		DMA_RS_TC						(BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16)
#define		DMA_RS_TC_0						(BIT16)
#define		DMA_RS_TL						(BIT14 + BIT13 + BIT12)
#define		DMA_RS_TL_0						(BIT12)
	#define		DMA_RS_TL_STS				(0)
	#define		DMA_RS_TL_DTS				(1)
	#define		DMA_RS_TL_TSR				(2)
	#define		DMA_RS_TL_DSE				(3)
	#define		DMA_RS_TL_TE				(4)
#define		DMA_RS_FPT						(BIT11)
	#define		DMA_RS_FPT_DE_SET			(0)
	#define		DMA_RS_FPT_HARDWARE_REQ		(1)
#define		DMA_RS_PLE						(BIT10)
	#define		DMA_RS_PLE_DISABLE			(0)
	#define		DMA_RS_PLE_ENABLE			(1)
#define		DMA_RS_DRQI						(BIT9)
	#define		DMA_RS_DRQI_DISABLE			(0)
	#define		DMA_RS_DRQI_ENABLE			(1)
#define		DMA_RS_RS						(BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_RS_RS_0						(BIT0)

/* DMAjBUFCR_n */
#define		DMA_BUFCR_ULB					(BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_BUFCR_ULB_0					(BIT0)

/* DMAjDPPTR_n */
#define		DMA_DPPTR_PTR					(BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2)
#define		DMA_DPPTR_PTR_0					(BIT2)
#define		DMA_DPPTR_DIE					(BIT1)
	#define		DMA_DPPTR_DIE_DISABLE		(0)
	#define		DMA_DPPTR_DIE_ENABLE		(1)
#define		DMA_DPPTR_CF					(BIT0)
	#define		DMA_DPPTR_CF_DISABLE		(0)
	#define		DMA_DPPTR_CF_ENABLE			(1)

/* DMAjDPCR_n */
#define		DMA_DPCR_UPF					(BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		DMA_DPCR_UPF_0					(BIT0)
	#define		DMA_DPCR_UPF_SAR_DISABLE	(0)
	#define		DMA_DPCR_UPF_SAR_ENABLE		(1)
#define		DMA_DPCR_UPF_1					(BIT1)
	#define		DMA_DPCR_UPF_DAR_DISABLE	(0)
	#define		DMA_DPCR_UPF_DAR_ENABLE		(1)
#define		DMA_DPCR_UPF_2					(BIT2)
	#define		DMA_DPCR_UPF_TSR_DISABLE	(0)
	#define		DMA_DPCR_UPF_TSR_ENABLE		(1)
#define		DMA_DPCR_UPF_3					(BIT3)
	#define		DMA_DPCR_UPF_TMR_DISABLE	(0)
	#define		DMA_DPCR_UPF_TMR_ENABLE		(1)


#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define	DMA_INTC2_INTSDMAC0CH0			(47U)
#define	DMA_INTC2_INTSDMAC0CH1			(48U)
#define	DMA_INTC2_INTSDMAC0CH2			(49U)
#define	DMA_INTC2_INTSDMAC0CH3			(50U)
#define	DMA_INTC2_INTSDMAC0CH4			(51U)
#define	DMA_INTC2_INTSDMAC0CH5			(52U)
#define	DMA_INTC2_INTSDMAC0CH6			(53U)
#define	DMA_INTC2_INTSDMAC0CH7			(54U)
#define	DMA_INTC2_INTSDMAC0CH8			(55U)
#define	DMA_INTC2_INTSDMAC0CH9			(56U)
#define	DMA_INTC2_INTSDMAC0CH10			(57U)
#define	DMA_INTC2_INTSDMAC0CH11			(58U)
#define	DMA_INTC2_INTSDMAC0CH12			(59U)
#define	DMA_INTC2_INTSDMAC0CH13			(60U)
#define	DMA_INTC2_INTSDMAC0CH14			(61U)
#define	DMA_INTC2_INTSDMAC0CH15			(62U)
#define	DMA_INTC2_INTSDMAC1CH0			(63U)
#define	DMA_INTC2_INTSDMAC1CH1			(64U)
#define	DMA_INTC2_INTSDMAC1CH2			(65U)
#define	DMA_INTC2_INTSDMAC1CH3			(66U)
#define	DMA_INTC2_INTSDMAC1CH4			(67U)
#define	DMA_INTC2_INTSDMAC1CH5			(68U)
#define	DMA_INTC2_INTSDMAC1CH6			(69U)
#define	DMA_INTC2_INTSDMAC1CH7			(70U)
#define	DMA_INTC2_INTSDMAC1CH8			(71U)
#define	DMA_INTC2_INTSDMAC1CH9			(72U)
#define	DMA_INTC2_INTSDMAC1CH10			(73U)
#define	DMA_INTC2_INTSDMAC1CH11			(74U)
#define	DMA_INTC2_INTSDMAC1CH12			(75U)
#define	DMA_INTC2_INTSDMAC1CH13			(76U)
#define	DMA_INTC2_INTSDMAC1CH14			(77U)
#define	DMA_INTC2_INTSDMAC1CH15			(78U)
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define	DMA_INTC2_INTSDMAC0CH0			(70U)
#define	DMA_INTC2_INTSDMAC0CH1			(71U)
#define	DMA_INTC2_INTSDMAC0CH2			(72U)
#define	DMA_INTC2_INTSDMAC0CH3			(73U)
#define	DMA_INTC2_INTSDMAC0CH4			(74U)
#define	DMA_INTC2_INTSDMAC0CH5			(75U)
#define	DMA_INTC2_INTSDMAC0CH6			(76U)
#define	DMA_INTC2_INTSDMAC0CH7			(77U)
#define	DMA_INTC2_INTSDMAC0CH8			(78U)
#define	DMA_INTC2_INTSDMAC0CH9			(79U)
#define	DMA_INTC2_INTSDMAC0CH10			(80U)
#define	DMA_INTC2_INTSDMAC0CH11			(81U)
#define	DMA_INTC2_INTSDMAC0CH12			(82U)
#define	DMA_INTC2_INTSDMAC0CH13			(83U)
#define	DMA_INTC2_INTSDMAC0CH14			(84U)
#define	DMA_INTC2_INTSDMAC0CH15			(85U)
#define	DMA_INTC2_INTSDMAC1CH0			(825U)
#define	DMA_INTC2_INTSDMAC1CH1			(826U)
#define	DMA_INTC2_INTSDMAC1CH2			(827U)
#define	DMA_INTC2_INTSDMAC1CH3			(828U)
#define	DMA_INTC2_INTSDMAC1CH4			(829U)
#define	DMA_INTC2_INTSDMAC1CH5			(830U)
#define	DMA_INTC2_INTSDMAC1CH6			(831U)
#define	DMA_INTC2_INTSDMAC1CH7			(832U)
#define	DMA_INTC2_INTSDMAC1CH8			(833U)
#define	DMA_INTC2_INTSDMAC1CH9			(834U)
#define	DMA_INTC2_INTSDMAC1CH10			(835U)
#define	DMA_INTC2_INTSDMAC1CH11			(836U)
#define	DMA_INTC2_INTSDMAC1CH12			(837U)
#define	DMA_INTC2_INTSDMAC1CH13			(838U)
#define	DMA_INTC2_INTSDMAC1CH14			(839U)
#define	DMA_INTC2_INTSDMAC1CH15			(840U)
#endif /* MCAL_SPAL_TARGET */

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
#define		INTC_CH_DTS_CH31TO0			(39U)	/* DTS CH31-0 transfer completion interrupt */
#define		INTC_CH_DTS_CH63TO32		(40U)	/* DTS CH63-32 transfer completion interrupt */
#define		INTC_CH_DTS_CH95TO64		(41U)	/* DTS CH95-64 transfer completion interrupt */
#define		INTC_CH_DTS_CH127TO96		(42U)	/* DTS CH127-96 transfer completion interrupt */
#define		INTC_CH_DTSCT_CH31TO0		(43U)	/* DTSCT CH31-0 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH63TO32		(44U)	/* DTSCT CH63-32 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH95TO64		(45U)	/* DTSCT CH95-64 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH127TO96		(46U)	/* DTSCT CH127-96 transfer count match interrupt */
#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
#define		INTC_CH_DTS_CH31TO0			(62U)	/* DTS CH31-0 transfer completion interrupt */
#define		INTC_CH_DTS_CH63TO32		(63U)	/* DTS CH63-32 transfer completion interrupt */
#define		INTC_CH_DTS_CH95TO64		(64U)	/* DTS CH95-64 transfer completion interrupt */
#define		INTC_CH_DTS_CH127TO96		(65U)	/* DTS CH127-96 transfer completion interrupt */
#define		INTC_CH_DTSCT_CH31TO0		(66U)	/* DTSCT CH31-0 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH63TO32		(67U)	/* DTSCT CH63-32 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH95TO64		(68U)	/* DTSCT CH95-64 transfer count match interrupt */
#define		INTC_CH_DTSCT_CH127TO96		(69U)	/* DTSCT CH127-96 transfer count match interrupt */
#endif /* MCAL_SPAL_TARGET */

/*==============================================================================================*/
/*	struct address definition																	*/
/*==============================================================================================*/
#define		Reg_DMATRGSEL	(*(volatile Reg_Dmatrgsel_Type*)(0xFF090400U))
#define		Reg_DTS			(*(volatile Reg_Dts_Type*)(0xFFF88000U))
#define		Reg_DMAC0		(*(volatile Reg_Dma_Type*)(0xFFF90000U))
#define		Reg_DMAC1		(*(volatile Reg_Dma_Type*)(0xFFF98000U))
#define		Reg_DesRAM0		(*(volatile Reg_Dram_Type*)(0xFFF94000U))
#define		Reg_DesRAM1		(*(volatile Reg_Dram_Type*)(0xFFF9C000U))

#endif /* REG_DMA_H */
/*-- End Of File -------------------------------------------------------------------------------*/
