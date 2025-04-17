/* reg_spid-r04-3000-0000-a-v02 */
/************************************************************************************************/
/*																								*/
/*		SPID register definition (for RH850U2B)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#if 0 // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

#ifndef REG_SPID_H
#define REG_SPID_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	defines																						*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
typedef	struct											/* SPID */
{

	U1	u1Dummy1[40];									/* 0xFF0A8000 - 0xFF0A8027 */

	union												/* BM10SPID 0xFF0A8028	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM10SPID;

	union												/* BM11SPID 0xFF0A802C	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM11SPID;

	union												/* BM12SPID 0xFF0A8030	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM12SPID;

	union												/* BM13SPID 0xFF0A8034	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM13SPID;

	union												/* BM14SPID 0xFF0A8038	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM14SPID;

	union												/* BM15SPID 0xFF0A803C	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM15SPID;

	union												/* BM16SPID 0xFF0A8040	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM16SPID;

	union												/* BM17SPID 0xFF0A8044	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM17SPID;

	union												/* BM18SPID 0xFF0A8048	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM18SPID;

	U1	u1Dummy2[4];									/* 0xFF0A804C - 0xFF0A804F */

	union												/* BM20SPID 0xFF0A8050	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM20SPID;

	U1	u1Dummy3[4];									/* 0xFF0A8054 - 0xFF0A8057 */

	union												/* BM22SPID 0xFF0A8058	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM22SPID;

	union												/* BM23SPID 0xFF0A805C	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM23SPID;

	union												/* BM24SPID 0xFF0A8060	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM24SPID;

	U1	u1Dummy4[8];									/* 0xFF0A8064 - 0xFF0A806B */

	union												/* BM27SPID 0xFF0A806C	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM27SPID;

	union												/* BM28SPID 0xFF0A8070	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM28SPID;

	U1	u1Dummy5[12];									/* 0xFF0A8074 - 0xFF0A807F */

	union												/* BM32SPID 0xFF0A8080	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM32SPID;

	union												/* BM33SPID 0xFF0A8084	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM33SPID;
	
	union												/* BM34SPID 0xFF0A8088	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM34SPID;

	union												/* BM35SPID 0xFF0A808C	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM35SPID;

	union												/* BM36SPID 0xFF0A8090	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM36SPID;

	union												/* BM37SPID 0xFF0A8094	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM37SPID;

	U1	u1Dumm6[20];									/* 0xFF0A8098 - 0xFF0A80AB */

	union												/* BM43SPID 0xFF0A80AC	   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	b5SPID					:5;				/* SPID					   */
			U4	b27Dummy1				:27;			/* Reserved Bits		   */
		} stBit;
	} unBM43SPID;

	U1	u1Dummy6[80];									/* 0xFF0A80B0 - 0xFF0A80FF */

	U4	u4BM00SPIDMSK;									/* BM00SPIDMSK 0xFF0A8100  */

	U4	u4BM01SPIDMSK;									/* BM01SPIDMSK 0xFF0A8104  */

	U4	u4BM02SPIDMSK;									/* BM02SPIDMSK 0xFF0A8108  */

	U4	u4BM03SPIDMSK;									/* BM03SPIDMSK 0xFF0A810C  */

	U4	u4BM04SPIDMSK;									/* BM04SPIDMSK 0xFF0A8110  */

	U4	u4BM05SPIDMSK;									/* BM05SPIDMSK 0xFF0A8114  */

	U1	u1Dummy7[16];									/* 0xFF0A8118 - 0xFF0A8127 */

	U4	u4BM10SPIDMSK;									/* BM10SPIDMSK 0xFF0A8128  */

	U4	u4BM11SPIDMSK;									/* BM11SPIDMSK 0xFF0A812C  */

	U4	u4BM12SPIDMSK;									/* BM12SPIDMSK 0xFF0A8130  */

	U4	u4BM13SPIDMSK;									/* BM13SPIDMSK 0xFF0A8134  */

	U4	u4BM14SPIDMSK;									/* BM14SPIDMSK 0xFF0A8138  */

	U4	u4BM15SPIDMSK;									/* BM15SPIDMSK 0xFF0A813C  */

	U4	u4BM16SPIDMSK;									/* BM16SPIDMSK 0xFF0A8140  */

	U4	u4BM17SPIDMSK;									/* BM17SPIDMSK 0xFF0A8144  */

	U4	u4BM18SPIDMSK;									/* BM18SPIDMSK 0xFF0A8148  */

	U1	u1Dummy8[4];									/* 0xFF0A814C - 0xFF0A814F */

	U4	u4BM20SPIDMSK;									/* BM20SPIDMSK 0xFF0A8150  */

	U1	u1Dummy9[4];									/* 0xFF0A8154 - 0xFF0A8157 */

	U4	u4BM22SPIDMSK;									/* BM22SPIDMSK 0xFF0A8158  */

	U4	u4BM23SPIDMSK;									/* BM23SPIDMSK 0xFF0A815C  */

	U4	u4BM24SPIDMSK;									/* BM24SPIDMSK 0xFF0A8160  */

	U1	u1Dummy10[8];									/* 0xFF0A8164 - 0xFF0A816B */

	U4	u4BM27SPIDMSK;									/* BM27SPIDMSK 0xFF0A816C  */

	U4	u4BM28SPIDMSK;									/* BM28SPIDMSK 0xFF0A8170  */

	U1	u1Dummy11[12];									/* 0xFF0A8174 - 0xFF0A817F */

	U4	u4BM32SPIDMSK;									/* BM32SPIDMSK 0xFF0A8180  */

	U4	u4BM33SPIDMSK;									/* BM33SPIDMSK 0xFF0A8184  */

	U4	u4BM34SPIDMSK;									/* BM34SPIDMSK 0xFF0A8188  */

	U4	u4BM35SPIDMSK;									/* BM35SPIDMSK 0xFF0A818C  */

	U4	u4BM36SPIDMSK;									/* BM36SPIDMSK 0xFF0A8190  */

	U4	u4BM37SPIDMSK;									/* BM37SPIDMSK 0xFF0A8194  */

	U4	u4BM38SPIDMSK;									/* BM38SPIDMSK 0xFF0A8198  */

	U4	u4BM39SPIDMSK;									/* BM39SPIDMSK 0xFF0A819C  */

	U4	u4BM40SPIDMSK;									/* BM40SPIDMSK 0xFF0A81A0  */

	U4	u4BM41SPIDMSK;									/* BM41SPIDMSK 0xFF0A81A4  */

	U4	u4BM42SPIDMSK;									/* BM42SPIDMSK 0xFF0A81A8  */

	U4	u4BM43SPIDMSK;									/* BM43SPIDMSK 0xFF0A81AC  */

	U1	u1Dummy12[80];									/* 0xFF0A81B0 - 0xFF0A81FF */

	union												/* BM00SPIDMSKLOCK 0xFF0A8200 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM00SPIDMSKLOCK;

	union												/* BM01SPIDMSKLOCK 0xFF0A8204 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM01SPIDMSKLOCK;

	union												/* BM02SPIDMSKLOCK 0xFF0A8208 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM02SPIDMSKLOCK;

	union												/* BM03SPIDMSKLOCK 0xFF0A820C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM03SPIDMSKLOCK;

	union												/* BM04SPIDMSKLOCK 0xFF0A8210 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM04SPIDMSKLOCK;

	union												/* BM05SPIDMSKLOCK 0xFF0A8214 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM05SPIDMSKLOCK;

	U1	u1Dummy13[16];									/* 0xFF0A8218 - 0xFF0A8227 */

	union												/* BM10SPIDMSKLOCK 0xFF0A8228 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM10SPIDMSKLOCK;

	union												/* BM11SPIDMSKLOCK 0xFF0A822C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM11SPIDMSKLOCK;

	union												/* BM12SPIDMSKLOCK 0xFF0A8230 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM12SPIDMSKLOCK;

	union												/* BM13SPIDMSKLOCK 0xFF0A8234 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM13SPIDMSKLOCK;

	union												/* BM14SPIDMSKLOCK 0xFF0A8238 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM14SPIDMSKLOCK;

	union												/* BM15SPIDMSKLOCK 0xFF0A823C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM15SPIDMSKLOCK;

	union												/* BM16SPIDMSKLOCK 0xFF0A8240 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM16SPIDMSKLOCK;

	union												/* BM17SPIDMSKLOCK 0xFF0A8244 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM17SPIDMSKLOCK;

	union												/* BM18SPIDMSKLOCK 0xFF0A8248 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM18SPIDMSKLOCK;

	U1	u1Dummy14[4];									/* 0xFF0A824C - 0xFF0A824F */

	union												/* BM20SPIDMSKLOCK 0xFF0A8250 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM20SPIDMSKLOCK;

	U1	u1Dummy15[4];									/* 0xFF0A8254 - 0xFF0A8257 */

	union												/* BM22SPIDMSKLOCK 0xFF0A8258 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM22SPIDMSKLOCK;

	union												/* BM23SPIDMSKLOCK 0xFF0A825C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM23SPIDMSKLOCK;

	union												/* BM24SPIDMSKLOCK 0xFF0A8260 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM24SPIDMSKLOCK;

	U1	u1Dummy16[8];									/* 0xFF0A8264 - 0xFF0A826B */

	union												/* BM27SPIDMSKLOCK 0xFF0A826C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM27SPIDMSKLOCK;

	union												/* BM28SPIDMSKLOCK 0xFF0A8270 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM28SPIDMSKLOCK;

	U1	u1Dummy17[12];									/* 0xFF0A8274 - 0xFF0A827F */

	union												/* BM32SPIDMSKLOCK 0xFF0A8280 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM32SPIDMSKLOCK;

	union												/* BM33SPIDMSKLOCK 0xFF0A8284 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM33SPIDMSKLOCK;

	union												/* BM34SPIDMSKLOCK 0xFF0A8288 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM34SPIDMSKLOCK;

	union												/* BM35SPIDMSKLOCK 0xFF0A828C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM35SPIDMSKLOCK;

	union												/* BM36SPIDMSKLOCK 0xFF0A8290 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM36SPIDMSKLOCK;

	union												/* BM37SPIDMSKLOCK 0xFF0A8294 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM37SPIDMSKLOCK;

	union												/* BM38SPIDMSKLOCK 0xFF0A8298 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM38SPIDMSKLOCK;

	union												/* BM39SPIDMSKLOCK 0xFF0A829C */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM39SPIDMSKLOCK;

	union												/* BM40SPIDMSKLOCK 0xFF0A82A0 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM40SPIDMSKLOCK;

	union												/* BM41SPIDMSKLOCK 0xFF0A82A4 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM41SPIDMSKLOCK;

	union												/* BM42SPIDMSKLOCK 0xFF0A82A8 */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM42SPIDMSKLOCK;

	union												/* BM43SPIDMSKLOCK 0xFF0A82AC */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xLOCK					:1;				/* LOCK					   */
			U4	b31Dummy1				:31;			/* Reserved Bits		   */
		} stBit;
	} unBM43SPIDMSKLOCK;

	U1	u1Dummy18[80];									/* 0xFF0A82B0 - 0xFF0A827B */

	union												/* SPIDKCPROT 0xFF0A8300   */
	{
		U4	u4Data;										/* 32-bit Access		   */
		struct											/* Bit Access			   */
		{
			U4	xKCE					:1;				/* KCE					   */
			U4	b31KCPROT				:31;			/* KCPROT				   */
		} stBit;
	} unSPIDKCPROT;

} Reg_Spid_SpidType;


/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* BMnSPID */
#define		SPID_BMSPID_SPID					(BIT4+BIT3+BIT2+BIT1+BIT0)
#define		SPID_BMSPID_SPID_0					(BIT0)

/* BMnSPIDMSK */

/* BMnSPIDMSKLOCK */
#define		SPID_BMSPIDMSKLOCK_LOCK				(BIT0)
	#define		SPID_BMSPIDMSKLOCK_LOCK_UNLOCK	(0)
	#define		SPID_BMSPIDMSKLOCK_LOCK_LOCK	(1)

/* SPIDKCPROT */
#define		SPID_SPIDKCPROT_KCPROT				(BIT31+BIT30+BIT29+BIT28+BIT27+BIT26+BIT25+BIT24+BIT23+BIT22+BIT21+BIT20+BIT19+BIT18+BIT17+BIT16+BIT15+BIT14+BIT13+BIT12+BIT11+BIT10+BIT9+BIT8+BIT7+BIT6+BIT5+BIT4+BIT3+BIT2+BIT1)
#define		SPID_SPIDKCPROT_KCPROT_0			(BIT1)
#define		SPID_SPIDKCPROT_KCE					(BIT0)
	#define		SPID_SPIDKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		SPID_SPIDKCPROT_KCE_ENABLE		(0xA5A5A501U)

/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		Reg_SPID			(*(volatile Reg_Spid_SpidType	 *)(0xFF0A8000U))



#endif /* REG_SPID_H */

#endif // zantei MPU‚Í2ŒŽ––”ñ‘Î‰ž

/*-- End Of File -------------------------------------------------------------------------------*/
