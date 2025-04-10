/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | Compiler_Cfg/HEADER                                        */
/*----------------------------------------------------------------          */
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v0_0_1      :2016/09/14 :New created                                   */
/*                            (This file is not created by a generator)     */
/*   v0_0_2      :2016/10/07 :Added Define STATIC and _INTERRUPT_           */
/*   v0_0_3      :2018/06/19 :Update                                        */
/*   v0_0_4      :2018/10/23 :Update                                        */
/*   v0_0_5      :2019/12/03 :Update                                        */
/*   v0_0_6      :2022/03/01 :Update                                        */
/*----------------------------------------------------------------          */
/* Notes  Made modifications for Reprog                                     */
/****************************************************************************/

#ifndef COMPILER_CFG_H     /* SWS_COMPILER_00047 */
#define COMPILER_CFG_H     /* SWS_COMPILER_00047 */

#include <Compiler_parts_Csm.h>

#define REGSPACE
#define COMSTACK_DATA

/*--------------------------*/
/* memory Type : Code       */
/*  - XXX_CALLOUT_CODE      */
/*  - XXX_CODE_FAST         */
/*  - XXX_CODE_SLOW         */
/*                          */
/* memory Type : Constants  */
/*  - XXX_CONST             */
/*  - XXX_CONFIG_DATA       */
/*                          */
/* memory Type : Pointer    */
/*  - XXX_APPL_DATA         */
/*  - XXX_APPL_CONST        */
/*                          */
/* memory Type : Variables  */
/*  - XXX_VAR_CLEARED       */
/*--------------------------*/

/* bsw/EAL */
#define CANIF_CALLOUT_CODE 
#define CANIF_CODE_FAST 
#define CANIF_CODE_SLOW     __farcall
#define CANIF_CONST 
#define CANIF_CONFIG_DATA 
#define CANIF_APPL_DATA 
#define CANIF_APPL_CONST 
#define CANIF_VAR_CLEARED 

#define CANTRCV_CALLOUT_CODE 
#define CANTRCV_CODE_FAST 
#define CANTRCV_CODE_SLOW   __farcall
#define CANTRCV_CONST 
#define CANTRCV_CONFIG_DATA 
#define CANTRCV_APPL_DATA 
#define CANTRCV_APPL_CONST 
#define CANTRCV_VAR_CLEARED 

#define CODEFLSIF_CALLOUT_CODE 
#define CODEFLSIF_CODE_FAST 
#define CODEFLSIF_CODE_SLOW __farcall
#define CODEFLSIF_CONST 
#define CODEFLSIF_CONFIG_DATA 
#define CODEFLSIF_APPL_DATA 
#define CODEFLSIF_APPL_CONST 
#define CODEFLSIF_VAR_CLEARED 

#define CODERAMIF_CALLOUT_CODE 
#define CODERAMIF_CODE_FAST 
#define CODERAMIF_CODE_SLOW __farcall
#define CODERAMIF_CONST 
#define CODERAMIF_CONFIG_DATA 
#define CODERAMIF_APPL_DATA 
#define CODERAMIF_APPL_CONST 
#define CODERAMIF_VAR_CLEARED 

#define EXTCODEFLSIF_CALLOUT_CODE 
#define EXTCODEFLSIF_CODE_FAST 
#define EXTCODEFLSIF_CODE_SLOW  __farcall
#define EXTCODEFLSIF_CONST 
#define EXTCODEFLSIF_CONFIG_DATA 
#define EXTCODEFLSIF_APPL_DATA 
#define EXTCODEFLSIF_APPL_CONST 
#define EXTCODEFLSIF_VAR_CLEARED 

#define SLEEPIF_CALLOUT_CODE 
#define SLEEPIF_CODE_FAST 
#define SLEEPIF_CODE_SLOW   __farcall
#define SLEEPIF_CONST 
#define SLEEPIF_CONFIG_DATA 
#define SLEEPIF_APPL_DATA 
#define SLEEPIF_APPL_CONST 
#define SLEEPIF_VAR_CLEARED 

#define SUBMICONIF_CALLOUT_CODE 
#define SUBMICONIF_CODE_FAST 
#define SUBMICONIF_CODE_SLOW    __farcall
#define SUBMICONIF_CONST 
#define SUBMICONIF_CONFIG_DATA 
#define SUBMICONIF_APPL_DATA 
#define SUBMICONIF_APPL_CONST 
#define SUBMICONIF_VAR_CLEARED 

#define USRSOFTIF_CALLOUT_CODE 
#define USRSOFTIF_CODE_FAST 
#define USRSOFTIF_CODE_SLOW __farcall
#define USRSOFTIF_CONST 
#define USRSOFTIF_CONFIG_DATA 
#define USRSOFTIF_APPL_DATA 
#define USRSOFTIF_APPL_CONST 
#define USRSOFTIF_VAR_CLEARED 

#define WDGIF_CALLOUT_CODE 
#define WDGIF_CODE_FAST 
#define WDGIF_CODE_SLOW     __farcall
#define WDGIF_CONST 
#define WDGIF_CONFIG_DATA 
#define WDGIF_APPL_DATA 
#define WDGIF_APPL_CONST 
#define WDGIF_VAR_CLEARED 

/* bsw/MCAL */
#define CAN_CALLOUT_CODE 
#define CAN_CODE_FAST 
#define CAN_CODE_SLOW       __farcall
#define CAN_CONST 
#define CAN_CONFIG_DATA 
#define CAN_APPL_DATA 
#define CAN_APPL_CONST 
#define CAN_VAR_CLEARED 

#define CODEFLS_CALLOUT_CODE 
#define CODEFLS_CODE_FAST 
#define CODEFLS_CODE_SLOW   __farcall
#define CODEFLS_CONST 
#define CODEFLS_CONFIG_DATA 
#define CODEFLS_APPL_DATA 
#define CODEFLS_APPL_CONST 
#define CODEFLS_VAR_CLEARED 

#define DIO_CALLOUT_CODE 
#define DIO_CODE_FAST 
#define DIO_CODE_SLOW       __farcall
#define DIO_CONST 
#define DIO_CONFIG_DATA 
#define DIO_APPL_DATA 
#define DIO_APPL_CONST 
#define DIO_VAR_CLEARED 

#define ECC_CALLOUT_CODE 
#define ECC_CODE_FAST 
#define ECC_CODE_SLOW       __farcall
#define ECC_CONST 
#define ECC_CONFIG_DATA 
#define ECC_APPL_DATA 
#define ECC_APPL_CONST 
#define ECC_VAR_CLEARED 

#define GPT_CALLOUT_CODE 
#define GPT_CODE_FAST 
#define GPT_CODE_SLOW       __farcall
#define GPT_CONST 
#define GPT_CONFIG_DATA 
#define GPT_APPL_DATA 
#define GPT_APPL_CONST 
#define GPT_VAR_CLEARED 

#define INT_CALLOUT_CODE 
#define INT_CODE_FAST 
#define INT_CODE_SLOW       __farcall
#define INT_CONST 
#define INT_CONFIG_DATA 
#define INT_APPL_DATA 
#define INT_APPL_CONST 
#define INT_VAR_CLEARED 

#define INTHNDLR_CALLOUT_CODE 
#define INTHNDLR_CODE_FAST 
#define INTHNDLR_CODE_SLOW  __farcall
#define INTHNDLR_CONST 
#define INTHNDLR_CONFIG_DATA 
#define INTHNDLR_APPL_DATA 
#define INTHNDLR_APPL_CONST 
#define INTHNDLR_VAR_CLEARED 

#define MCU_CALLOUT_CODE 
#define MCU_CODE_FAST 
#define MCU_CODE_SLOW       __farcall
#define MCU_CONST 
#define MCU_CONFIG_DATA 
#define MCU_APPL_DATA 
#define MCU_APPL_CONST 
#define MCU_VAR_CLEARED 

#define PORT_CALLOUT_CODE 
#define PORT_CODE_FAST 
#define PORT_CODE_SLOW      __farcall
#define PORT_CONST 
#define PORT_CONFIG_DATA 
#define PORT_APPL_DATA 
#define PORT_APPL_CONST 
#define PORT_VAR_CLEARED 

#define VECT_CALLOUT_CODE 
#define VECT_CODE_FAST 
#define VECT_CODE_SLOW      __farcall
#define VECT_CONST 
#define VECT_CONFIG_DATA 
#define VECT_APPL_DATA 
#define VECT_APPL_CONST 
#define VECT_VAR_CLEARED 

#define WDG_CALLOUT_CODE 
#define WDG_CODE_FAST 
#define WDG_CODE_SLOW       __farcall
#define WDG_CONST 
#define WDG_CONFIG_DATA 
#define WDG_APPL_DATA 
#define WDG_APPL_CONST 
#define WDG_VAR_CLEARED 

/* bsw/RTE */
#define RTE_CALLOUT_CODE 
#define RTE_CODE_FAST 
#define RTE_CODE_SLOW       __farcall
#define RTE_CONST 
#define RTE_CONFIG_DATA 
#define RTE_APPL_DATA 
#define RTE_APPL_CONST 
#define RTE_VAR_CLEARED 

/* bsw/SVL */
#define BSWM_CALLOUT_CODE 
#define BSWM_CODE_FAST 
#define BSWM_CODE_SLOW      __farcall
#define BSWM_CONST 
#define BSWM_CONFIG_DATA 
#define BSWM_APPL_DATA 
#define BSWM_APPL_CONST 
#define BSWM_VAR_CLEARED 

#define CANSM_CALLOUT_CODE 
#define CANSM_CODE_FAST 
#define CANSM_CODE_SLOW     __farcall
#define CANSM_CONST 
#define CANSM_CONFIG_DATA 
#define CANSM_APPL_DATA 
#define CANSM_APPL_CONST 
#define CANSM_VAR_CLEARED 

#define COMM_CALLOUT_CODE 
#define COMM_CODE_FAST 
#define COMM_CODE_SLOW      __farcall
#define COMM_CONST 
#define COMM_CONFIG_DATA 
#define COMM_APPL_DATA 
#define COMM_APPL_CONST 
#define COMM_VAR_CLEARED 

#define ECUM_CALLOUT_CODE 
#define ECUM_CODE_FAST 
#define ECUM_CODE_SLOW      __farcall
#define ECUM_CONST 
#define ECUM_CONFIG_DATA 
#define ECUM_APPL_DATA 
#define ECUM_APPL_CONST 
#define ECUM_VAR_CLEARED 

#define GDN_CALLOUT_CODE 
#define GDN_CODE_FAST 
#define GDN_CODE_SLOW       __farcall
#define GDN_CONST 
#define GDN_CONFIG_DATA 
#define GDN_APPL_DATA 
#define GDN_APPL_CONST 
#define GDN_VAR_CLEARED 

#define GDN_TMRSRV_CALLOUT_CODE 
#define GDN_TMRSRV_CODE_FAST 
#define GDN_TMRSRV_CODE_SLOW    __farcall
#define GDN_TMRSRV_CONST 
#define GDN_TMRSRV_CONFIG_DATA 
#define GDN_TMRSRV_APPL_DATA 
#define GDN_TMRSRV_APPL_CONST 
#define GDN_TMRSRV_VAR_CLEARED 

#define GDN_CANIF_CALLOUT_CODE 
#define GDN_CANIF_CODE_FAST 
#define GDN_CANIF_CODE_SLOW __farcall
#define GDN_CANIF_CONST 
#define GDN_CANIF_CONFIG_DATA 
#define GDN_CANIF_APPL_DATA 
#define GDN_CANIF_APPL_CONST 
#define GDN_CANIF_VAR_CLEARED 

#define DCM_CALLOUT_CODE 
#define DCM_CODE_FAST 
#define DCM_CODE_SLOW       __farcall
#define DCM_CONST 
#define DCM_CONFIG_DATA 
#define DCM_APPL_DATA 
#define DCM_APPL_CONST 
#define DCM_VAR_CLEARED 

#define CANTP_CALLOUT_CODE 
#define CANTP_CODE_FAST 
#define CANTP_CODE_SLOW     __farcall
#define CANTP_CONST 
#define CANTP_CONFIG_DATA 
#define CANTP_APPL_DATA 
#define CANTP_APPL_CONST 
#define CANTP_VAR_CLEARED 

#define MEMERRM_CALLOUT_CODE 
#define MEMERRM_CODE_FAST 
#define MEMERRM_CODE_SLOW   __farcall
#define MEMERRM_CONST 
#define MEMERRM_CONFIG_DATA 
#define MEMERRM_APPL_DATA 
#define MEMERRM_APPL_CONST 
#define MEMERRM_VAR_CLEARED 

#define MEMM_CALLOUT_CODE 
#define MEMM_CODE_FAST 
#define MEMM_CODE_SLOW      __farcall
#define MEMM_CONST 
#define MEMM_CONFIG_DATA 
#define MEMM_APPL_DATA 
#define MEMM_APPL_CONST 
#define MEMM_VAR_CLEARED 

#define PDUR_CALLOUT_CODE 
#define PDUR_CODE_FAST 
#define PDUR_CODE_SLOW      __farcall
#define PDUR_CONST 
#define PDUR_CONFIG_DATA 
#define PDUR_APPL_DATA 
#define PDUR_APPL_CONST 
#define PDUR_VAR_CLEARED 

#define SCHM_CALLOUT_CODE 
#define SCHM_CODE_FAST 
#define SCHM_CODE_SLOW      __farcall
#define SCHM_CONST 
#define SCHM_CONFIG_DATA 
#define SCHM_APPL_DATA 
#define SCHM_APPL_CONST 
#define SCHM_VAR_CLEARED 

#define SHUTDOWN_CALLOUT_CODE 
#define SHUTDOWN_CODE_FAST 
#define SHUTDOWN_CODE_SLOW  __farcall
#define SHUTDOWN_CONST 
#define SHUTDOWN_CONFIG_DATA 
#define SHUTDOWN_APPL_DATA 
#define SHUTDOWN_APPL_CONST 
#define SHUTDOWN_VAR_CLEARED 

#define STARTUP_CALLOUT_CODE 
#define STARTUP_CODE_FAST 
#define STARTUP_CODE_SLOW   __farcall
#define STARTUP_CONST 
#define STARTUP_CONFIG_DATA 
#define STARTUP_APPL_DATA 
#define STARTUP_APPL_CONST 
#define STARTUP_VAR_CLEARED 

#define SYS_CALLOUT_CODE 
#define SYS_CODE_FAST 
#define SYS_CODE_SLOW       __farcall
#define SYS_CONST 
#define SYS_CONFIG_DATA 
#define SYS_APPL_DATA 
#define SYS_APPL_CONST 
#define SYS_VAR_CLEARED 

#define TM_CALLOUT_CODE 
#define TM_CODE_FAST 
#define TM_CODE_SLOW        __farcall
#define TM_CONST 
#define TM_CONFIG_DATA 
#define TM_APPL_DATA 
#define TM_APPL_CONST 
#define TM_VAR_CLEARED 

#define WDGM_CALLOUT_CODE 
#define WDGM_CODE_FAST 
#define WDGM_CODE_SLOW      __farcall
#define WDGM_CONST 
#define WDGM_CONFIG_DATA 
#define WDGM_APPL_DATA 
#define WDGM_APPL_CONST 
#define WDGM_VAR_CLEARED 

/* swc */
#define CMPDECMP_CALLOUT_CODE 
#define CMPDECMP_CODE_FAST 
#define CMPDECMP_CODE_SLOW  __farcall
#define CMPDECMP_CONST 
#define CMPDECMP_CONFIG_DATA 
#define CMPDECMP_APPL_DATA 
#define CMPDECMP_APPL_CONST 
#define CMPDECMP_VAR_CLEARED 

#define DECRYPT_CALLOUT_CODE 
#define DECRYPT_CODE_FAST 
#define DECRYPT_CODE_SLOW    __farcall
#define DECRYPT_CONST 
#define DECRYPT_CONFIG_DATA 
#define DECRYPT_APPL_DATA 
#define DECRYPT_APPL_CONST 
#define DECRYPT_VAR_CLEARED 

#define DIAGSRV_CALLOUT_CODE 
#define DIAGSRV_CODE_FAST 
#define DIAGSRV_CODE_SLOW   __farcall
#define DIAGSRV_CONST 
#define DIAGSRV_CONFIG_DATA 
#define DIAGSRV_APPL_DATA 
#define DIAGSRV_APPL_CONST 
#define DIAGSRV_VAR_CLEARED 

#define DIAGLIB_CALLOUT_CODE 
#define DIAGLIB_CODE_FAST 
#define DIAGLIB_CODE_SLOW   __farcall
#define DIAGLIB_CONST 
#define DIAGLIB_CONFIG_DATA 
#define DIAGLIB_APPL_DATA 
#define DIAGLIB_APPL_CONST 
#define DIAGLIB_VAR_CLEARED 

#define FSCDTCT_CALLOUT_CODE 
#define FSCDTCT_CODE_FAST 
#define FSCDTCT_CODE_SLOW   __farcall
#define FSCDTCT_CONST 
#define FSCDTCT_CONFIG_DATA 
#define FSCDTCT_APPL_DATA 
#define FSCDTCT_APPL_CONST 
#define FSCDTCT_VAR_CLEARED 

#define PRGCHK_CALLOUT_CODE 
#define PRGCHK_CODE_FAST 
#define PRGCHK_CODE_SLOW    __farcall
#define PRGCHK_CONST 
#define PRGCHK_CONFIG_DATA 
#define PRGCHK_APPL_DATA 
#define PRGCHK_APPL_CONST 
#define PRGCHK_VAR_CLEARED 

#define RPGEVTHK_CALLOUT_CODE 
#define RPGEVTHK_CODE_FAST 
#define RPGEVTHK_CODE_SLOW  __farcall
#define RPGEVTHK_CONST 
#define RPGEVTHK_CONFIG_DATA 
#define RPGEVTHK_APPL_DATA 
#define RPGEVTHK_APPL_CONST 
#define RPGEVTHK_VAR_CLEARED 

#define RPGLIB_CALLOUT_CODE 
#define RPGLIB_CODE_FAST 
#define RPGLIB_CODE_SLOW    __farcall
#define RPGLIB_CONST 
#define RPGLIB_CONFIG_DATA 
#define RPGLIB_APPL_DATA 
#define RPGLIB_APPL_CONST 
#define RPGLIB_VAR_CLEARED 

#define RPGMFR_CALLOUT_CODE 
#define RPGMFR_CODE_FAST 
#define RPGMFR_CODE_SLOW    __farcall
#define RPGMFR_CONST 
#define RPGMFR_CONFIG_DATA 
#define RPGMFR_APPL_DATA 
#define RPGMFR_APPL_CONST 
#define RPGMFR_VAR_CLEARED 

#define RPGSPP_CALLOUT_CODE 
#define RPGSPP_CODE_FAST 
#define RPGSPP_CODE_SLOW    __farcall
#define RPGSPP_CONST 
#define RPGSPP_CONFIG_DATA 
#define RPGSPP_APPL_DATA 
#define RPGSPP_APPL_CONST 
#define RPGSPP_VAR_CLEARED 

#define SEC_CALLOUT_CODE 
#define SEC_CODE_FAST 
#define SEC_CODE_SLOW       __farcall
#define SEC_CONST 
#define SEC_CONFIG_DATA 
#define SEC_APPL_DATA 
#define SEC_APPL_CONST 
#define SEC_VAR_CLEARED 

#define VEHINF_CALLOUT_CODE 
#define VEHINF_CODE_FAST 
#define VEHINF_CODE_SLOW    __farcall
#define VEHINF_CONST 
#define VEHINF_CONFIG_DATA 
#define VEHINF_APPL_DATA 
#define VEHINF_APPL_CONST 
#define VEHINF_VAR_CLEARED 

/* parts */
#define CRC_CODE            __farcall
#define CRC_CONST_32 
#define CRC_APPL_DATA 
#define CRC_APPL_CONST 

#define WRAPCRYPTO_CALLOUT_CODE 
#define WRAPCRYPTO_CODE_FAST 
#define WRAPCRYPTO_CODE_SLOW    __farcall
#define WRAPCRYPTO_CONST 
#define WRAPCRYPTO_CONFIG_DATA 
#define WRAPCRYPTO_APPL_DATA 
#define WRAPCRYPTO_APPL_CONST 
#define WRAPCRYPTO_VAR_CLEARED 

/* env */
#define SECTION_CONST 
#define SECTION_APPL_DATA 
#define SECTION_APPL_CONST 
#define REPROGOPT_CONFIG_DATA 
#define VERSION_CONST 


#endif /* COMPILER_CFG_H */ /* SWS_COMPILER_00047 */
