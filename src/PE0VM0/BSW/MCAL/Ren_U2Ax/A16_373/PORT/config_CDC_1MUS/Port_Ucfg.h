/* Port-r04-303 */
/************************************************************************************************/
/*                                                                                              */
/*     PORT Driver                                                                              */
/*                                                                                              */
/*      Copyright : DENSO CORPORATION                                                           */
/*                                                                                              */
/************************************************************************************************/
#ifndef PORT_UCFG_H
#define PORT_UCFG_H

/*==============================================================================================*/
/* defines / data types / structs / unions / macros                                             */
/*==============================================================================================*/
/* IOHOLD */
#define PORT_CFG_REL_IO_BUF_HOLD_STATE			(STD_OFF)	/* STD_ON : I/O buffer hold state is released in Port_Init() */
															/* STD_OFF: I/O buffer hold state is released at where user defines */
#define PORT_CFG_REG_CHK						(STD_OFF)

#define PORT_CFG_REG_REFRESH					(STD_OFF)

#define PORT_CFG_PROTECTION_CONTROL				(STD_OFF)

#endif /* PORT_UCFG_H */
/*-- End Of File -------------------------------------------------------------------------------*/
