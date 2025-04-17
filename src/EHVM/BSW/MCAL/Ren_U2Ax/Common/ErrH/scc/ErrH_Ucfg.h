/* ErrH-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		ErrH Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef ERRH_UCFG_H
#define ERRH_UCFG_H
/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* Interrupt Service Routine */
#define		T_INTECMMI_CORE0()			ErrH_AlarmInterrupt()
#define		T_INTECMDCLSMI_CORE0()		ErrH_AlarmInterrupt()
#define		T_INTECMMI_CORE1()			ErrH_AlarmInterrupt()
#define		T_INTECMDCLSMI_CORE1()		ErrH_AlarmInterrupt()
#if ( MCU_TYPE_SERIES == MCU_RH850U2A16 )
#define		T_INTECMMI_CORE2()			ErrH_AlarmInterrupt()
#define		T_INTECMDCLSMI_CORE2()		ErrH_AlarmInterrupt()
#define		T_INTECMMI_CORE3()			ErrH_AlarmInterrupt()
#define		T_INTECMDCLSMI_CORE3()		ErrH_AlarmInterrupt()
#endif

#endif /*ERRH_UCFG_H*/
/*-- End Of File -------------------------------------------------------------------------------*/
