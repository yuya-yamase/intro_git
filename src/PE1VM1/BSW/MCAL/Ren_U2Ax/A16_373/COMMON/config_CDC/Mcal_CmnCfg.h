/* Common-r04-31700-0000-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL Common Configration Header															*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef	MCAL_CMNCFG_H
#define	MCAL_CMNCFG_H

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/* Target package for RH850U2A	*/
#define	MCAL_PKG_U2A6_292PIN		(1U)
#define	MCAL_PKG_U2A16_373PIN		(2U)
#define	MCAL_PKG_U2A16_516PIN		(3U)
#define	MCAL_PKG_U2A8_292PIN		(4U)
#define	MCAL_PKG_U2A6_144PIN		(5U)
#define	MCAL_PKG_U2A16_292PIN		(6U)
#define	MCAL_PKG_U2A8_373PIN		(7U)

#define	MCAL_PKG_U2A_TARGET			(MCAL_PKG_U2A16_373PIN)

/* Target package for RH850U2B is supported only U2B6_292PIN.	*/
/* Therefore, do not have to configure it.						*/

#endif	/* MCAL_CMNCFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
