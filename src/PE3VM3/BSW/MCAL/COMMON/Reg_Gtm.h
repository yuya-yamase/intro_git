/* Reg_GTM-r04-30300-0000-a-v00 */
/************************************************************************************************/
/*																								*/
/*		GTM register definition (for microcontroller name)										*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	REG_GTM_H
#define	REG_GTM_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
/* Gtm register access structure */
typedef struct
{
	uint32				u4GtmRev;
	uint32				u4GtmRst;
	uint32				u4GtmCtrl;
	uint32				u4GtmAeiAddrXpt;
	uint32				u4GtmIrqNotify;
	uint32				u4GtmIrqEn;
	uint32				u4GtmIrqForcint;
	uint32				u4GtmIrqMode;
	uint32				u4GtmEirqEn;
	uint32				u4Dummy1[1];
	uint32				u4GtmCfg;
	uint32				u4GtmAeiStaXpt;
	uint32				u4GtmBridgeMode;
	uint32				u4GtmBridgePtr1;
	uint32				u4GtmBridgePtr2;
	uint32				u4GtmMcsAemDis;
	uint32				u4Dummy2[28];
	uint32				u4GtmClsClkCfg;
} Reg_Gtm_Type;

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/* GTM Address base */
#define GTM_BASE_ADDRESS				((uint32)0xFF600000U)		/* GTM base address */

/* GTM Register Access  */
#define REG_GTM							(*(volatile Reg_Gtm_Type*)		GTM_BASE_ADDRESS)

#endif	/* REG_GTM_H */
/*-- End Of File -------------------------------------------------------------------------------*/
