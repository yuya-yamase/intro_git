/***************************************************************************/
/*[ Compiler_Cfg.h ] - Compiler dependency header file                     */
/***************************************************************************/

#ifndef COMPILER_CFG_H     /* SWS_COMPILER_00047 */
#define COMPILER_CFG_H     /* SWS_COMPILER_00047 */

/*------------------------*/
/*   memclass, ptrclass   */
/*------------------------*/
/*----------------------------------------------------*/
/*   Compiler,Platform  need keywords required follow:*/
/*                                                    */
/*   Cosmic, S12X                                     */
/*   Metrowerks, S12X                                 */
/*   IAR, HCS12 C/C++                                 */
/*   Tasking, ST10                                    */
/*                                                    */
/*   Compiler,Platform  no keywords required follow:  */
/*                                                    */
/*   Tasking, TC1796                                  */
/*   Greenhills, V850                                 */
/*   ADS, ST30                                        */
/*   DIABDATA, MPC5554                                */
/*----------------------------------------------------*/

/*--------------------------*/
/* memory Type : Pointer    */
/*--------------------------*/
#define REGSPACE

/*---------------------------*/
/*This section is DEPRECATED.*/
/*---------------------------*/
/*#define <PREFIX>_CALLOUT_CODE      -><PREFIX>_<CN>_CODE */
/*#define <PREFIX>_VAR_NOINIT        -><PREFIX>_VAR_<INIT_POLICY> */
/*#define <PREFIX>_VAR_POWER_ON_INIT -><PREFIX>_VAR_<INIT_POLICY> */
/*#define <PREFIX>_VAR_FAST          -><PREFIX>_VAR_FAST_<INIT_POLICY> */
/*#define <PREFIX>_VAR               -><PREFIX>_VAR_<INIT_POLICY> */
/*--------------------------*/

/* memory classes and pointer classes */ /* SWS_COMPILER_00040 */
/*-------------*/
/* <PREFIX>    */
/*-------------*/
/*! RpgMfr */
/*! RpgSpp */
/*! Sec */
/*! DatAccs */
/*! Routine */
/*! Crypto */
/*! PrgChk */
/*! FscDtct */
/*! UsrDiag */
/*! RpgEvtHk */
/*! VehInf */
/*! Rte */
/*! Startup */
/*! Shutdown */
/*! Sys */
/*! EcuM */
/*! BswM */
/*! SchM */
/*! Tm */
/*! WdgM */
/*! Com */
/*! Dcm */
/*! ComM */
/*! CanSM */
/*! PduR */
/*! CanTp */
/*! Gdn_TmrSrv */
/*! MemM */
/*! MemErrM */
/*! WdgIf */
/*! CanIf */
/*! Gdn_CanIf */
/*! CanTrcv */
/*! CodeFlsIf */
/*! ExtCodeFlsIf */
/*! CodeRamIf */
/*! UsrSoftIf */
/*! SleepIf */
/*! Mcu */
/*! Gpt */
/*! Int */
/*! IntHndlr */
/*! Vect */
/*! Wdg */
/*! Can */
/*! Port */
/*! Dio */
/*! CodeFls */
/*! Ecc */

/* RpgMfr */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define RPGMFR_CODE
#define RPGMFR_CALLOUT_CODE
#define RPGMFR_CODE_FAST
#define RPGMFR_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define RPGMFR_CONST
#define RPGMFR_CALIB
#define RPGMFR_CONFIG_DATA
#define RPGMFR_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define RPGMFR_APPL_DATA
#define RPGMFR_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*RPGMFR_VAR_<INIT_POLICY>*/
#define RPGMFR_VAR_NO_INIT
#define RPGMFR_VAR_INIT
#define RPGMFR_VAR_POWER_ON_INIT
#define RPGMFR_VAR_CLEARED
#define RPGMFR_VAR_POWER_ON_CLEARED
/*RPGMFR_VAR_FAST_<INIT_POLICY>*/
#define RPGMFR_VAR_FAST_NO_INIT
#define RPGMFR_VAR_FAST_INIT
#define RPGMFR_VAR_FAST_POWER_ON_INIT
#define RPGMFR_VAR_FAST_CLEARED
#define RPGMFR_VAR_FAST_POWER_ON_CLEARED
/*RPGMFR_VAR_SLOW_<INIT_POLICY>*/
#define RPGMFR_VAR_SLOW_NO_INIT
#define RPGMFR_VAR_SLOW_INIT
#define RPGMFR_VAR_SLOW_POWER_ON_INIT
#define RPGMFR_VAR_SLOW_CLEARED
#define RPGMFR_VAR_SLOW_POWER_ON_CLEARED
/*RPGMFR_INTERNAL_VAR_<INIT_POLICY>*/
#define RPGMFR_INTERNAL_VAR_NO_INIT
#define RPGMFR_INTERNAL_VAR_INIT
#define RPGMFR_INTERNAL_VAR_POWER_ON_INIT
#define RPGMFR_INTERNAL_VAR_CLEARED
#define RPGMFR_INTERNAL_VAR_POWER_ON_CLEARED
#define RPGMFR_VAR_SAVED_ZONEX

/* RpgSpp */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define RPGSPP_CODE
#define RPGSPP_CALLOUT_CODE
#define RPGSPP_CODE_FAST
#define RPGSPP_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define RPGSPP_CONST
#define RPGSPP_CALIB
#define RPGSPP_CONFIG_DATA
#define RPGSPP_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define RPGSPP_APPL_DATA
#define RPGSPP_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*RPGSPP_VAR_<INIT_POLICY>*/
#define RPGSPP_VAR_NO_INIT
#define RPGSPP_VAR_INIT
#define RPGSPP_VAR_POWER_ON_INIT
#define RPGSPP_VAR_CLEARED
#define RPGSPP_VAR_POWER_ON_CLEARED
/*RPGSPP_VAR_FAST_<INIT_POLICY>*/
#define RPGSPP_VAR_FAST_NO_INIT
#define RPGSPP_VAR_FAST_INIT
#define RPGSPP_VAR_FAST_POWER_ON_INIT
#define RPGSPP_VAR_FAST_CLEARED
#define RPGSPP_VAR_FAST_POWER_ON_CLEARED
/*RPGSPP_VAR_SLOW_<INIT_POLICY>*/
#define RPGSPP_VAR_SLOW_NO_INIT
#define RPGSPP_VAR_SLOW_INIT
#define RPGSPP_VAR_SLOW_POWER_ON_INIT
#define RPGSPP_VAR_SLOW_CLEARED
#define RPGSPP_VAR_SLOW_POWER_ON_CLEARED
/*RPGSPP_INTERNAL_VAR_<INIT_POLICY>*/
#define RPGSPP_INTERNAL_VAR_NO_INIT
#define RPGSPP_INTERNAL_VAR_INIT
#define RPGSPP_INTERNAL_VAR_POWER_ON_INIT
#define RPGSPP_INTERNAL_VAR_CLEARED
#define RPGSPP_INTERNAL_VAR_POWER_ON_CLEARED
#define RPGSPP_VAR_SAVED_ZONEX

/* Sec */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define SEC_CODE
#define SEC_CALLOUT_CODE
#define SEC_CODE_FAST
#define SEC_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define SEC_CONST
#define SEC_CALIB
#define SEC_CONFIG_DATA
#define SEC_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define SEC_APPL_DATA
#define SEC_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*SEC_VAR_<INIT_POLICY>*/
#define SEC_VAR_NO_INIT
#define SEC_VAR_INIT
#define SEC_VAR_POWER_ON_INIT
#define SEC_VAR_CLEARED
#define SEC_VAR_POWER_ON_CLEARED
/*SEC_VAR_FAST_<INIT_POLICY>*/
#define SEC_VAR_FAST_NO_INIT
#define SEC_VAR_FAST_INIT
#define SEC_VAR_FAST_POWER_ON_INIT
#define SEC_VAR_FAST_CLEARED
#define SEC_VAR_FAST_POWER_ON_CLEARED
/*SEC_VAR_SLOW_<INIT_POLICY>*/
#define SEC_VAR_SLOW_NO_INIT
#define SEC_VAR_SLOW_INIT
#define SEC_VAR_SLOW_POWER_ON_INIT
#define SEC_VAR_SLOW_CLEARED
#define SEC_VAR_SLOW_POWER_ON_CLEARED
/*SEC_INTERNAL_VAR_<INIT_POLICY>*/
#define SEC_INTERNAL_VAR_NO_INIT
#define SEC_INTERNAL_VAR_INIT
#define SEC_INTERNAL_VAR_POWER_ON_INIT
#define SEC_INTERNAL_VAR_CLEARED
#define SEC_INTERNAL_VAR_POWER_ON_CLEARED
#define SEC_VAR_SAVED_ZONEX

/* DatAccs */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define DATACCS_CODE
#define DATACCS_CALLOUT_CODE
#define DATACCS_CODE_FAST
#define DATACCS_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define DATACCS_CONST
#define DATACCS_CALIB
#define DATACCS_CONFIG_DATA
#define DATACCS_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define DATACCS_APPL_DATA
#define DATACCS_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*DATACCS_VAR_<INIT_POLICY>*/
#define DATACCS_VAR_NO_INIT
#define DATACCS_VAR_INIT
#define DATACCS_VAR_POWER_ON_INIT
#define DATACCS_VAR_CLEARED
#define DATACCS_VAR_POWER_ON_CLEARED
/*DATACCS_VAR_FAST_<INIT_POLICY>*/
#define DATACCS_VAR_FAST_NO_INIT
#define DATACCS_VAR_FAST_INIT
#define DATACCS_VAR_FAST_POWER_ON_INIT
#define DATACCS_VAR_FAST_CLEARED
#define DATACCS_VAR_FAST_POWER_ON_CLEARED
/*DATACCS_VAR_SLOW_<INIT_POLICY>*/
#define DATACCS_VAR_SLOW_NO_INIT
#define DATACCS_VAR_SLOW_INIT
#define DATACCS_VAR_SLOW_POWER_ON_INIT
#define DATACCS_VAR_SLOW_CLEARED
#define DATACCS_VAR_SLOW_POWER_ON_CLEARED
/*DATACCS_INTERNAL_VAR_<INIT_POLICY>*/
#define DATACCS_INTERNAL_VAR_NO_INIT
#define DATACCS_INTERNAL_VAR_INIT
#define DATACCS_INTERNAL_VAR_POWER_ON_INIT
#define DATACCS_INTERNAL_VAR_CLEARED
#define DATACCS_INTERNAL_VAR_POWER_ON_CLEARED
#define DATACCS_VAR_SAVED_ZONEX

/* Routine */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define ROUTINE_CODE
#define ROUTINE_CALLOUT_CODE
#define ROUTINE_CODE_FAST
#define ROUTINE_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define ROUTINE_CONST
#define ROUTINE_CALIB
#define ROUTINE_CONFIG_DATA
#define ROUTINE_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define ROUTINE_APPL_DATA
#define ROUTINE_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*ROUTINE_VAR_<INIT_POLICY>*/
#define ROUTINE_VAR_NO_INIT
#define ROUTINE_VAR_INIT
#define ROUTINE_VAR_POWER_ON_INIT
#define ROUTINE_VAR_CLEARED
#define ROUTINE_VAR_POWER_ON_CLEARED
/*ROUTINE_VAR_FAST_<INIT_POLICY>*/
#define ROUTINE_VAR_FAST_NO_INIT
#define ROUTINE_VAR_FAST_INIT
#define ROUTINE_VAR_FAST_POWER_ON_INIT
#define ROUTINE_VAR_FAST_CLEARED
#define ROUTINE_VAR_FAST_POWER_ON_CLEARED
/*ROUTINE_VAR_SLOW_<INIT_POLICY>*/
#define ROUTINE_VAR_SLOW_NO_INIT
#define ROUTINE_VAR_SLOW_INIT
#define ROUTINE_VAR_SLOW_POWER_ON_INIT
#define ROUTINE_VAR_SLOW_CLEARED
#define ROUTINE_VAR_SLOW_POWER_ON_CLEARED
/*ROUTINE_INTERNAL_VAR_<INIT_POLICY>*/
#define ROUTINE_INTERNAL_VAR_NO_INIT
#define ROUTINE_INTERNAL_VAR_INIT
#define ROUTINE_INTERNAL_VAR_POWER_ON_INIT
#define ROUTINE_INTERNAL_VAR_CLEARED
#define ROUTINE_INTERNAL_VAR_POWER_ON_CLEARED

/* Crypto */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CRYPTO_CODE
#define CRYPTO_CALLOUT_CODE
#define CRYPTO_CODE_FAST
#define CRYPTO_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CRYPTO_CONST
#define CRYPTO_CALIB
#define CRYPTO_CONFIG_DATA
#define CRYPTO_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CRYPTO_APPL_DATA
#define CRYPTO_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CRYPTO_VAR_<INIT_POLICY>*/
#define CRYPTO_VAR_NO_INIT
#define CRYPTO_VAR_INIT
#define CRYPTO_VAR_POWER_ON_INIT
#define CRYPTO_VAR_CLEARED
#define CRYPTO_VAR_POWER_ON_CLEARED
/*CRYPTO_VAR_FAST_<INIT_POLICY>*/
#define CRYPTO_VAR_FAST_NO_INIT
#define CRYPTO_VAR_FAST_INIT
#define CRYPTO_VAR_FAST_POWER_ON_INIT
#define CRYPTO_VAR_FAST_CLEARED
#define CRYPTO_VAR_FAST_POWER_ON_CLEARED
/*CRYPTO_VAR_SLOW_<INIT_POLICY>*/
#define CRYPTO_VAR_SLOW_NO_INIT
#define CRYPTO_VAR_SLOW_INIT
#define CRYPTO_VAR_SLOW_POWER_ON_INIT
#define CRYPTO_VAR_SLOW_CLEARED
#define CRYPTO_VAR_SLOW_POWER_ON_CLEARED
/*CRYPTO_INTERNAL_VAR_<INIT_POLICY>*/
#define CRYPTO_INTERNAL_VAR_NO_INIT
#define CRYPTO_INTERNAL_VAR_INIT
#define CRYPTO_INTERNAL_VAR_POWER_ON_INIT
#define CRYPTO_INTERNAL_VAR_CLEARED
#define CRYPTO_INTERNAL_VAR_POWER_ON_CLEARED
#define CRYPTO_VAR_SAVED_ZONEX

/* PrgChk */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define PRGCHK_CODE
#define PRGCHK_CALLOUT_CODE
#define PRGCHK_CODE_FAST
#define PRGCHK_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define PRGCHK_CONST
#define PRGCHK_CALIB
#define PRGCHK_CONFIG_DATA
#define PRGCHK_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define PRGCHK_APPL_DATA
#define PRGCHK_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*PRGCHK_VAR_<INIT_POLICY>*/
#define PRGCHK_VAR_NO_INIT
#define PRGCHK_VAR_INIT
#define PRGCHK_VAR_POWER_ON_INIT
#define PRGCHK_VAR_CLEARED
#define PRGCHK_VAR_POWER_ON_CLEARED
/*PRGCHK_VAR_FAST_<INIT_POLICY>*/
#define PRGCHK_VAR_FAST_NO_INIT
#define PRGCHK_VAR_FAST_INIT
#define PRGCHK_VAR_FAST_POWER_ON_INIT
#define PRGCHK_VAR_FAST_CLEARED
#define PRGCHK_VAR_FAST_POWER_ON_CLEARED
/*PRGCHK_VAR_SLOW_<INIT_POLICY>*/
#define PRGCHK_VAR_SLOW_NO_INIT
#define PRGCHK_VAR_SLOW_INIT
#define PRGCHK_VAR_SLOW_POWER_ON_INIT
#define PRGCHK_VAR_SLOW_CLEARED
#define PRGCHK_VAR_SLOW_POWER_ON_CLEARED
/*PRGCHK_INTERNAL_VAR_<INIT_POLICY>*/
#define PRGCHK_INTERNAL_VAR_NO_INIT
#define PRGCHK_INTERNAL_VAR_INIT
#define PRGCHK_INTERNAL_VAR_POWER_ON_INIT
#define PRGCHK_INTERNAL_VAR_CLEARED
#define PRGCHK_INTERNAL_VAR_POWER_ON_CLEARED
#define PRGCHK_VAR_SAVED_ZONEX

/* FscDtct */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define FSCDTCT_CODE
#define FSCDTCT_CALLOUT_CODE
#define FSCDTCT_CODE_FAST
#define FSCDTCT_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define FSCDTCT_CONST
#define FSCDTCT_CALIB
#define FSCDTCT_CONFIG_DATA
#define FSCDTCT_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define FSCDTCT_APPL_DATA
#define FSCDTCT_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*FSCDTCT_VAR_<INIT_POLICY>*/
#define FSCDTCT_VAR_NO_INIT
#define FSCDTCT_VAR_INIT
#define FSCDTCT_VAR_POWER_ON_INIT
#define FSCDTCT_VAR_CLEARED
#define FSCDTCT_VAR_POWER_ON_CLEARED
/*FSCDTCT_VAR_FAST_<INIT_POLICY>*/
#define FSCDTCT_VAR_FAST_NO_INIT
#define FSCDTCT_VAR_FAST_INIT
#define FSCDTCT_VAR_FAST_POWER_ON_INIT
#define FSCDTCT_VAR_FAST_CLEARED
#define FSCDTCT_VAR_FAST_POWER_ON_CLEARED
/*FSCDTCT_VAR_SLOW_<INIT_POLICY>*/
#define FSCDTCT_VAR_SLOW_NO_INIT
#define FSCDTCT_VAR_SLOW_INIT
#define FSCDTCT_VAR_SLOW_POWER_ON_INIT
#define FSCDTCT_VAR_SLOW_CLEARED
#define FSCDTCT_VAR_SLOW_POWER_ON_CLEARED
/*FSCDTCT_INTERNAL_VAR_<INIT_POLICY>*/
#define FSCDTCT_INTERNAL_VAR_NO_INIT
#define FSCDTCT_INTERNAL_VAR_INIT
#define FSCDTCT_INTERNAL_VAR_POWER_ON_INIT
#define FSCDTCT_INTERNAL_VAR_CLEARED
#define FSCDTCT_INTERNAL_VAR_POWER_ON_CLEARED
#define FSCDTCT_VAR_SAVED_ZONEX

/* UsrDiag */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define USRDIAG_CODE
#define USRDIAG_CALLOUT_CODE
#define USRDIAG_CODE_FAST
#define USRDIAG_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define USRDIAG_CONST
#define USRDIAG_CALIB
#define USRDIAG_CONFIG_DATA
#define USRDIAG_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define USRDIAG_APPL_DATA
#define USRDIAG_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*USRDIAG_VAR_<INIT_POLICY>*/
#define USRDIAG_VAR_NO_INIT
#define USRDIAG_VAR_INIT
#define USRDIAG_VAR_POWER_ON_INIT
#define USRDIAG_VAR_CLEARED
#define USRDIAG_VAR_POWER_ON_CLEARED
/*USRDIAG_VAR_FAST_<INIT_POLICY>*/
#define USRDIAG_VAR_FAST_NO_INIT
#define USRDIAG_VAR_FAST_INIT
#define USRDIAG_VAR_FAST_POWER_ON_INIT
#define USRDIAG_VAR_FAST_CLEARED
#define USRDIAG_VAR_FAST_POWER_ON_CLEARED
/*USRDIAG_VAR_SLOW_<INIT_POLICY>*/
#define USRDIAG_VAR_SLOW_NO_INIT
#define USRDIAG_VAR_SLOW_INIT
#define USRDIAG_VAR_SLOW_POWER_ON_INIT
#define USRDIAG_VAR_SLOW_CLEARED
#define USRDIAG_VAR_SLOW_POWER_ON_CLEARED
/*USRDIAG_INTERNAL_VAR_<INIT_POLICY>*/
#define USRDIAG_INTERNAL_VAR_NO_INIT
#define USRDIAG_INTERNAL_VAR_INIT
#define USRDIAG_INTERNAL_VAR_POWER_ON_INIT
#define USRDIAG_INTERNAL_VAR_CLEARED
#define USRDIAG_INTERNAL_VAR_POWER_ON_CLEARED
#define USRDIAG_VAR_SAVED_ZONEX

/* RpgEvtHk */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define RPGEVTHK_CODE
#define RPGEVTHK_CALLOUT_CODE
#define RPGEVTHK_CODE_FAST
#define RPGEVTHK_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define RPGEVTHK_CONST
#define RPGEVTHK_CALIB
#define RPGEVTHK_CONFIG_DATA
#define RPGEVTHK_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define RPGEVTHK_APPL_DATA
#define RPGEVTHK_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*RPGEVTHK_VAR_<INIT_POLICY>*/
#define RPGEVTHK_VAR_NO_INIT
#define RPGEVTHK_VAR_INIT
#define RPGEVTHK_VAR_POWER_ON_INIT
#define RPGEVTHK_VAR_CLEARED
#define RPGEVTHK_VAR_POWER_ON_CLEARED
/*RPGEVTHK_VAR_FAST_<INIT_POLICY>*/
#define RPGEVTHK_VAR_FAST_NO_INIT
#define RPGEVTHK_VAR_FAST_INIT
#define RPGEVTHK_VAR_FAST_POWER_ON_INIT
#define RPGEVTHK_VAR_FAST_CLEARED
#define RPGEVTHK_VAR_FAST_POWER_ON_CLEARED
/*RPGEVTHK_VAR_SLOW_<INIT_POLICY>*/
#define RPGEVTHK_VAR_SLOW_NO_INIT
#define RPGEVTHK_VAR_SLOW_INIT
#define RPGEVTHK_VAR_SLOW_POWER_ON_INIT
#define RPGEVTHK_VAR_SLOW_CLEARED
#define RPGEVTHK_VAR_SLOW_POWER_ON_CLEARED
/*RPGEVTHK_INTERNAL_VAR_<INIT_POLICY>*/
#define RPGEVTHK_INTERNAL_VAR_NO_INIT
#define RPGEVTHK_INTERNAL_VAR_INIT
#define RPGEVTHK_INTERNAL_VAR_POWER_ON_INIT
#define RPGEVTHK_INTERNAL_VAR_CLEARED
#define RPGEVTHK_INTERNAL_VAR_POWER_ON_CLEARED
#define RPGEVTHK_VAR_SAVED_ZONEX

/* VehInf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define VEHINF_CODE
#define VEHINF_CALLOUT_CODE
#define VEHINF_CODE_FAST
#define VEHINF_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define VEHINF_CONST
#define VEHINF_CALIB
#define VEHINF_CONFIG_DATA
#define VEHINF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define VEHINF_APPL_DATA
#define VEHINF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*VEHINF_VAR_<INIT_POLICY>*/
#define VEHINF_VAR_NO_INIT
#define VEHINF_VAR_INIT
#define VEHINF_VAR_POWER_ON_INIT
#define VEHINF_VAR_CLEARED
#define VEHINF_VAR_POWER_ON_CLEARED
/*VEHINF_VAR_FAST_<INIT_POLICY>*/
#define VEHINF_VAR_FAST_NO_INIT
#define VEHINF_VAR_FAST_INIT
#define VEHINF_VAR_FAST_POWER_ON_INIT
#define VEHINF_VAR_FAST_CLEARED
#define VEHINF_VAR_FAST_POWER_ON_CLEARED
/*VEHINF_VAR_SLOW_<INIT_POLICY>*/
#define VEHINF_VAR_SLOW_NO_INIT
#define VEHINF_VAR_SLOW_INIT
#define VEHINF_VAR_SLOW_POWER_ON_INIT
#define VEHINF_VAR_SLOW_CLEARED
#define VEHINF_VAR_SLOW_POWER_ON_CLEARED
/*VEHINF_INTERNAL_VAR_<INIT_POLICY>*/
#define VEHINF_INTERNAL_VAR_NO_INIT
#define VEHINF_INTERNAL_VAR_INIT
#define VEHINF_INTERNAL_VAR_POWER_ON_INIT
#define VEHINF_INTERNAL_VAR_CLEARED
#define VEHINF_INTERNAL_VAR_POWER_ON_CLEARED
#define VEHINF_VAR_SAVED_ZONEX

/* Rte */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define RTE_CODE
#define RTE_CALLOUT_CODE
#define RTE_CODE_FAST
#define RTE_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define RTE_CONST
#define RTE_CALIB
#define RTE_CONFIG_DATA
#define RTE_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define RTE_APPL_DATA
#define RTE_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*RTE_VAR_<INIT_POLICY>*/
#define RTE_VAR_NO_INIT
#define RTE_VAR_INIT
#define RTE_VAR_POWER_ON_INIT
#define RTE_VAR_CLEARED
#define RTE_VAR_POWER_ON_CLEARED
/*RTE_VAR_FAST_<INIT_POLICY>*/
#define RTE_VAR_FAST_NO_INIT
#define RTE_VAR_FAST_INIT
#define RTE_VAR_FAST_POWER_ON_INIT
#define RTE_VAR_FAST_CLEARED
#define RTE_VAR_FAST_POWER_ON_CLEARED
/*RTE_VAR_SLOW_<INIT_POLICY>*/
#define RTE_VAR_SLOW_NO_INIT
#define RTE_VAR_SLOW_INIT
#define RTE_VAR_SLOW_POWER_ON_INIT
#define RTE_VAR_SLOW_CLEARED
#define RTE_VAR_SLOW_POWER_ON_CLEARED
/*RTE_INTERNAL_VAR_<INIT_POLICY>*/
#define RTE_INTERNAL_VAR_NO_INIT
#define RTE_INTERNAL_VAR_INIT
#define RTE_INTERNAL_VAR_POWER_ON_INIT
#define RTE_INTERNAL_VAR_CLEARED
#define RTE_INTERNAL_VAR_POWER_ON_CLEARED
#define RTE_VAR_SAVED_ZONEX

/* Startup */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define STARTUP_CODE
#define STARTUP_CALLOUT_CODE
#define STARTUP_CODE_FAST
#define STARTUP_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define STARTUP_CONST
#define STARTUP_CALIB
#define STARTUP_CONFIG_DATA
#define STARTUP_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define STARTUP_APPL_DATA
#define STARTUP_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*STARTUP_VAR_<INIT_POLICY>*/
#define STARTUP_VAR_NO_INIT
#define STARTUP_VAR_INIT
#define STARTUP_VAR_POWER_ON_INIT
#define STARTUP_VAR_CLEARED
#define STARTUP_VAR_POWER_ON_CLEARED
/*STARTUP_VAR_FAST_<INIT_POLICY>*/
#define STARTUP_VAR_FAST_NO_INIT
#define STARTUP_VAR_FAST_INIT
#define STARTUP_VAR_FAST_POWER_ON_INIT
#define STARTUP_VAR_FAST_CLEARED
#define STARTUP_VAR_FAST_POWER_ON_CLEARED
/*STARTUP_VAR_SLOW_<INIT_POLICY>*/
#define STARTUP_VAR_SLOW_NO_INIT
#define STARTUP_VAR_SLOW_INIT
#define STARTUP_VAR_SLOW_POWER_ON_INIT
#define STARTUP_VAR_SLOW_CLEARED
#define STARTUP_VAR_SLOW_POWER_ON_CLEARED
/*STARTUP_INTERNAL_VAR_<INIT_POLICY>*/
#define STARTUP_INTERNAL_VAR_NO_INIT
#define STARTUP_INTERNAL_VAR_INIT
#define STARTUP_INTERNAL_VAR_POWER_ON_INIT
#define STARTUP_INTERNAL_VAR_CLEARED
#define STARTUP_INTERNAL_VAR_POWER_ON_CLEARED
#define STARTUP_VAR_SAVED_ZONEX

/* Shutdown */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define SHUTDOWN_CODE
#define SHUTDOWN_CALLOUT_CODE
#define SHUTDOWN_CODE_FAST
#define SHUTDOWN_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define SHUTDOWN_CONST
#define SHUTDOWN_CALIB
#define SHUTDOWN_CONFIG_DATA
#define SHUTDOWN_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define SHUTDOWN_APPL_DATA
#define SHUTDOWN_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*SHUTDOWN_VAR_<INIT_POLICY>*/
#define SHUTDOWN_VAR_NO_INIT
#define SHUTDOWN_VAR_INIT
#define SHUTDOWN_VAR_POWER_ON_INIT
#define SHUTDOWN_VAR_CLEARED
#define SHUTDOWN_VAR_POWER_ON_CLEARED
/*SHUTDOWN_VAR_FAST_<INIT_POLICY>*/
#define SHUTDOWN_VAR_FAST_NO_INIT
#define SHUTDOWN_VAR_FAST_INIT
#define SHUTDOWN_VAR_FAST_POWER_ON_INIT
#define SHUTDOWN_VAR_FAST_CLEARED
#define SHUTDOWN_VAR_FAST_POWER_ON_CLEARED
/*SHUTDOWN_VAR_SLOW_<INIT_POLICY>*/
#define SHUTDOWN_VAR_SLOW_NO_INIT
#define SHUTDOWN_VAR_SLOW_INIT
#define SHUTDOWN_VAR_SLOW_POWER_ON_INIT
#define SHUTDOWN_VAR_SLOW_CLEARED
#define SHUTDOWN_VAR_SLOW_POWER_ON_CLEARED
/*SHUTDOWN_INTERNAL_VAR_<INIT_POLICY>*/
#define SHUTDOWN_INTERNAL_VAR_NO_INIT
#define SHUTDOWN_INTERNAL_VAR_INIT
#define SHUTDOWN_INTERNAL_VAR_POWER_ON_INIT
#define SHUTDOWN_INTERNAL_VAR_CLEARED
#define SHUTDOWN_INTERNAL_VAR_POWER_ON_CLEARED
#define SHUTDOWN_VAR_SAVED_ZONEX

/* Sys */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define SYS_CODE
#define SYS_CALLOUT_CODE
#define SYS_CODE_FAST
#define SYS_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define SYS_CONST
#define SYS_CALIB
#define SYS_CONFIG_DATA
#define SYS_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define SYS_APPL_DATA
#define SYS_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*SYS_VAR_<INIT_POLICY>*/
#define SYS_VAR_NO_INIT
#define SYS_VAR_INIT
#define SYS_VAR_POWER_ON_INIT
#define SYS_VAR_CLEARED
#define SYS_VAR_POWER_ON_CLEARED
/*SYS_VAR_FAST_<INIT_POLICY>*/
#define SYS_VAR_FAST_NO_INIT
#define SYS_VAR_FAST_INIT
#define SYS_VAR_FAST_POWER_ON_INIT
#define SYS_VAR_FAST_CLEARED
#define SYS_VAR_FAST_POWER_ON_CLEARED
/*SYS_VAR_SLOW_<INIT_POLICY>*/
#define SYS_VAR_SLOW_NO_INIT
#define SYS_VAR_SLOW_INIT
#define SYS_VAR_SLOW_POWER_ON_INIT
#define SYS_VAR_SLOW_CLEARED
#define SYS_VAR_SLOW_POWER_ON_CLEARED
/*SYS_INTERNAL_VAR_<INIT_POLICY>*/
#define SYS_INTERNAL_VAR_NO_INIT
#define SYS_INTERNAL_VAR_INIT
#define SYS_INTERNAL_VAR_POWER_ON_INIT
#define SYS_INTERNAL_VAR_CLEARED
#define SYS_INTERNAL_VAR_POWER_ON_CLEARED
#define SYS_VAR_SAVED_ZONEX

/* EcuM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define ECUM_CODE
#define ECUM_CALLOUT_CODE
#define ECUM_CODE_FAST
#define ECUM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define ECUM_CONST
#define ECUM_CALIB
#define ECUM_CONFIG_DATA
#define ECUM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define ECUM_APPL_DATA
#define ECUM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*ECUM_VAR_<INIT_POLICY>*/
#define ECUM_VAR_NO_INIT
#define ECUM_VAR_INIT
#define ECUM_VAR_POWER_ON_INIT
#define ECUM_VAR_CLEARED
#define ECUM_VAR_POWER_ON_CLEARED
/*ECUM_VAR_FAST_<INIT_POLICY>*/
#define ECUM_VAR_FAST_NO_INIT
#define ECUM_VAR_FAST_INIT
#define ECUM_VAR_FAST_POWER_ON_INIT
#define ECUM_VAR_FAST_CLEARED
#define ECUM_VAR_FAST_POWER_ON_CLEARED
/*ECUM_VAR_SLOW_<INIT_POLICY>*/
#define ECUM_VAR_SLOW_NO_INIT
#define ECUM_VAR_SLOW_INIT
#define ECUM_VAR_SLOW_POWER_ON_INIT
#define ECUM_VAR_SLOW_CLEARED
#define ECUM_VAR_SLOW_POWER_ON_CLEARED
/*ECUM_INTERNAL_VAR_<INIT_POLICY>*/
#define ECUM_INTERNAL_VAR_NO_INIT
#define ECUM_INTERNAL_VAR_INIT
#define ECUM_INTERNAL_VAR_POWER_ON_INIT
#define ECUM_INTERNAL_VAR_CLEARED
#define ECUM_INTERNAL_VAR_POWER_ON_CLEARED
#define ECUM_VAR_SAVED_ZONEX

/* BswM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define BSWM_CODE
#define BSWM_CALLOUT_CODE
#define BSWM_CODE_FAST
#define BSWM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define BSWM_CONST
#define BSWM_CALIB
#define BSWM_CONFIG_DATA
#define BSWM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define BSWM_APPL_DATA
#define BSWM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*BSWM_VAR_<INIT_POLICY>*/
#define BSWM_VAR_NO_INIT
#define BSWM_VAR_INIT
#define BSWM_VAR_POWER_ON_INIT
#define BSWM_VAR_CLEARED
#define BSWM_VAR_POWER_ON_CLEARED
/*BSWM_VAR_FAST_<INIT_POLICY>*/
#define BSWM_VAR_FAST_NO_INIT
#define BSWM_VAR_FAST_INIT
#define BSWM_VAR_FAST_POWER_ON_INIT
#define BSWM_VAR_FAST_CLEARED
#define BSWM_VAR_FAST_POWER_ON_CLEARED
/*BSWM_VAR_SLOW_<INIT_POLICY>*/
#define BSWM_VAR_SLOW_NO_INIT
#define BSWM_VAR_SLOW_INIT
#define BSWM_VAR_SLOW_POWER_ON_INIT
#define BSWM_VAR_SLOW_CLEARED
#define BSWM_VAR_SLOW_POWER_ON_CLEARED
/*BSWM_INTERNAL_VAR_<INIT_POLICY>*/
#define BSWM_INTERNAL_VAR_NO_INIT
#define BSWM_INTERNAL_VAR_INIT
#define BSWM_INTERNAL_VAR_POWER_ON_INIT
#define BSWM_INTERNAL_VAR_CLEARED
#define BSWM_INTERNAL_VAR_POWER_ON_CLEARED
#define BSWM_VAR_SAVED_ZONEX

/* SchM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define SCHM_CODE
#define SCHM_CALLOUT_CODE
#define SCHM_CODE_FAST
#define SCHM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define SCHM_CONST
#define SCHM_CALIB
#define SCHM_CONFIG_DATA
#define SCHM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define SCHM_APPL_DATA
#define SCHM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*SCHM_VAR_<INIT_POLICY>*/
#define SCHM_VAR_NO_INIT
#define SCHM_VAR_INIT
#define SCHM_VAR_POWER_ON_INIT
#define SCHM_VAR_CLEARED
#define SCHM_VAR_POWER_ON_CLEARED
/*SCHM_VAR_FAST_<INIT_POLICY>*/
#define SCHM_VAR_FAST_NO_INIT
#define SCHM_VAR_FAST_INIT
#define SCHM_VAR_FAST_POWER_ON_INIT
#define SCHM_VAR_FAST_CLEARED
#define SCHM_VAR_FAST_POWER_ON_CLEARED
/*SCHM_VAR_SLOW_<INIT_POLICY>*/
#define SCHM_VAR_SLOW_NO_INIT
#define SCHM_VAR_SLOW_INIT
#define SCHM_VAR_SLOW_POWER_ON_INIT
#define SCHM_VAR_SLOW_CLEARED
#define SCHM_VAR_SLOW_POWER_ON_CLEARED
/*SCHM_INTERNAL_VAR_<INIT_POLICY>*/
#define SCHM_INTERNAL_VAR_NO_INIT
#define SCHM_INTERNAL_VAR_INIT
#define SCHM_INTERNAL_VAR_POWER_ON_INIT
#define SCHM_INTERNAL_VAR_CLEARED
#define SCHM_INTERNAL_VAR_POWER_ON_CLEARED
#define SCHM_VAR_SAVED_ZONEX

/* Tm */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define TM_CODE
#define TM_CALLOUT_CODE
#define TM_CODE_FAST
#define TM_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define TM_CONST
#define TM_CALIB
#define TM_CONFIG_DATA
#define TM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define TM_APPL_DATA
#define TM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*TM_VAR_<INIT_POLICY>*/
#define TM_VAR_NO_INIT
#define TM_VAR_INIT
#define TM_VAR_POWER_ON_INIT
#define TM_VAR_CLEARED
#define TM_VAR_POWER_ON_CLEARED
/*TM_VAR_FAST_<INIT_POLICY>*/
#define TM_VAR_FAST_NO_INIT
#define TM_VAR_FAST_INIT
#define TM_VAR_FAST_POWER_ON_INIT
#define TM_VAR_FAST_CLEARED
#define TM_VAR_FAST_POWER_ON_CLEARED
/*TM_VAR_SLOW_<INIT_POLICY>*/
#define TM_VAR_SLOW_NO_INIT
#define TM_VAR_SLOW_INIT
#define TM_VAR_SLOW_POWER_ON_INIT
#define TM_VAR_SLOW_CLEARED
#define TM_VAR_SLOW_POWER_ON_CLEARED
/*TM_INTERNAL_VAR_<INIT_POLICY>*/
#define TM_INTERNAL_VAR_NO_INIT
#define TM_INTERNAL_VAR_INIT
#define TM_INTERNAL_VAR_POWER_ON_INIT
#define TM_INTERNAL_VAR_CLEARED
#define TM_INTERNAL_VAR_POWER_ON_CLEARED
#define TM_VAR_SAVED_ZONEX

/* WdgM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define WDGM_CODE
#define WDGM_CALLOUT_CODE
#define WDGM_CODE_FAST
#define WDGM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define WDGM_CONST
#define WDGM_CALIB
#define WDGM_CONFIG_DATA
#define WDGM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define WDGM_APPL_DATA
#define WDGM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*WDGM_VAR_<INIT_POLICY>*/
#define WDGM_VAR_NO_INIT
#define WDGM_VAR_INIT
#define WDGM_VAR_POWER_ON_INIT
#define WDGM_VAR_CLEARED
#define WDGM_VAR_POWER_ON_CLEARED
/*WDGM_VAR_FAST_<INIT_POLICY>*/
#define WDGM_VAR_FAST_NO_INIT
#define WDGM_VAR_FAST_INIT
#define WDGM_VAR_FAST_POWER_ON_INIT
#define WDGM_VAR_FAST_CLEARED
#define WDGM_VAR_FAST_POWER_ON_CLEARED
/*WDGM_VAR_SLOW_<INIT_POLICY>*/
#define WDGM_VAR_SLOW_NO_INIT
#define WDGM_VAR_SLOW_INIT
#define WDGM_VAR_SLOW_POWER_ON_INIT
#define WDGM_VAR_SLOW_CLEARED
#define WDGM_VAR_SLOW_POWER_ON_CLEARED
/*WDGM_INTERNAL_VAR_<INIT_POLICY>*/
#define WDGM_INTERNAL_VAR_NO_INIT
#define WDGM_INTERNAL_VAR_INIT
#define WDGM_INTERNAL_VAR_POWER_ON_INIT
#define WDGM_INTERNAL_VAR_CLEARED
#define WDGM_INTERNAL_VAR_POWER_ON_CLEARED
#define WDGM_VAR_SAVED_ZONEX

/* Com */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define COM_CODE
#define COM_CALLOUT_CODE
#define COM_CODE_FAST
#define COM_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define COM_CONST
#define COM_CALIB
#define COM_CONFIG_DATA
#define COM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define COM_APPL_DATA
#define COM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*COM_VAR_<INIT_POLICY>*/
#define COM_VAR_NO_INIT
#define COM_VAR_INIT
#define COM_VAR_POWER_ON_INIT
#define COM_VAR_CLEARED
#define COM_VAR_POWER_ON_CLEARED
/*COM_VAR_FAST_<INIT_POLICY>*/
#define COM_VAR_FAST_NO_INIT
#define COM_VAR_FAST_INIT
#define COM_VAR_FAST_POWER_ON_INIT
#define COM_VAR_FAST_CLEARED
#define COM_VAR_FAST_POWER_ON_CLEARED
/*COM_VAR_SLOW_<INIT_POLICY>*/
#define COM_VAR_SLOW_NO_INIT
#define COM_VAR_SLOW_INIT
#define COM_VAR_SLOW_POWER_ON_INIT
#define COM_VAR_SLOW_CLEARED
#define COM_VAR_SLOW_POWER_ON_CLEARED
/*COM_INTERNAL_VAR_<INIT_POLICY>*/
#define COM_INTERNAL_VAR_NO_INIT
#define COM_INTERNAL_VAR_INIT
#define COM_INTERNAL_VAR_POWER_ON_INIT
#define COM_INTERNAL_VAR_CLEARED
#define COM_INTERNAL_VAR_POWER_ON_CLEARED
#define COM_VAR_SAVED_ZONEX

/* Dcm */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define DCM_CODE
#define DCM_CALLOUT_CODE
#define DCM_CODE_FAST
#define DCM_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define DCM_CONST
#define DCM_CALIB
#define DCM_CONFIG_DATA
#define DCM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define DCM_APPL_DATA
#define DCM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*DCM_VAR_<INIT_POLICY>*/
#define DCM_VAR_NO_INIT
#define DCM_VAR_INIT
#define DCM_VAR_POWER_ON_INIT
#define DCM_VAR_CLEARED
#define DCM_VAR_POWER_ON_CLEARED
/*DCM_VAR_FAST_<INIT_POLICY>*/
#define DCM_VAR_FAST_NO_INIT
#define DCM_VAR_FAST_INIT
#define DCM_VAR_FAST_POWER_ON_INIT
#define DCM_VAR_FAST_CLEARED
#define DCM_VAR_FAST_POWER_ON_CLEARED
/*DCM_VAR_SLOW_<INIT_POLICY>*/
#define DCM_VAR_SLOW_NO_INIT
#define DCM_VAR_SLOW_INIT
#define DCM_VAR_SLOW_POWER_ON_INIT
#define DCM_VAR_SLOW_CLEARED
#define DCM_VAR_SLOW_POWER_ON_CLEARED
/*DCM_INTERNAL_VAR_<INIT_POLICY>*/
#define DCM_INTERNAL_VAR_NO_INIT
#define DCM_INTERNAL_VAR_INIT
#define DCM_INTERNAL_VAR_POWER_ON_INIT
#define DCM_INTERNAL_VAR_CLEARED
#define DCM_INTERNAL_VAR_POWER_ON_CLEARED
#define DCM_VAR_SAVED_ZONEX

/* ComM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define COMM_CODE
#define COMM_CALLOUT_CODE
#define COMM_CODE_FAST
#define COMM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define COMM_CONST
#define COMM_CALIB
#define COMM_CONFIG_DATA
#define COMM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define COMM_APPL_DATA
#define COMM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*COMM_VAR_<INIT_POLICY>*/
#define COMM_VAR_NO_INIT
#define COMM_VAR_INIT
#define COMM_VAR_POWER_ON_INIT
#define COMM_VAR_CLEARED
#define COMM_VAR_POWER_ON_CLEARED
/*COMM_VAR_FAST_<INIT_POLICY>*/
#define COMM_VAR_FAST_NO_INIT
#define COMM_VAR_FAST_INIT
#define COMM_VAR_FAST_POWER_ON_INIT
#define COMM_VAR_FAST_CLEARED
#define COMM_VAR_FAST_POWER_ON_CLEARED
/*COMM_VAR_SLOW_<INIT_POLICY>*/
#define COMM_VAR_SLOW_NO_INIT
#define COMM_VAR_SLOW_INIT
#define COMM_VAR_SLOW_POWER_ON_INIT
#define COMM_VAR_SLOW_CLEARED
#define COMM_VAR_SLOW_POWER_ON_CLEARED
/*COMM_INTERNAL_VAR_<INIT_POLICY>*/
#define COMM_INTERNAL_VAR_NO_INIT
#define COMM_INTERNAL_VAR_INIT
#define COMM_INTERNAL_VAR_POWER_ON_INIT
#define COMM_INTERNAL_VAR_CLEARED
#define COMM_INTERNAL_VAR_POWER_ON_CLEARED
#define COMM_VAR_SAVED_ZONEX

/* CanSM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CANSM_CODE
#define CANSM_CALLOUT_CODE
#define CANSM_CODE_FAST
#define CANSM_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CANSM_CONST
#define CANSM_CALIB
#define CANSM_CONFIG_DATA
#define CANSM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CANSM_APPL_DATA
#define CANSM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CANSM_VAR_<INIT_POLICY>*/
#define CANSM_VAR_NO_INIT
#define CANSM_VAR_INIT
#define CANSM_VAR_POWER_ON_INIT
#define CANSM_VAR_CLEARED
#define CANSM_VAR_POWER_ON_CLEARED
/*CANSM_VAR_FAST_<INIT_POLICY>*/
#define CANSM_VAR_FAST_NO_INIT
#define CANSM_VAR_FAST_INIT
#define CANSM_VAR_FAST_POWER_ON_INIT
#define CANSM_VAR_FAST_CLEARED
#define CANSM_VAR_FAST_POWER_ON_CLEARED
/*CANSM_VAR_SLOW_<INIT_POLICY>*/
#define CANSM_VAR_SLOW_NO_INIT
#define CANSM_VAR_SLOW_INIT
#define CANSM_VAR_SLOW_POWER_ON_INIT
#define CANSM_VAR_SLOW_CLEARED
#define CANSM_VAR_SLOW_POWER_ON_CLEARED
/*CANSM_INTERNAL_VAR_<INIT_POLICY>*/
#define CANSM_INTERNAL_VAR_NO_INIT
#define CANSM_INTERNAL_VAR_INIT
#define CANSM_INTERNAL_VAR_POWER_ON_INIT
#define CANSM_INTERNAL_VAR_CLEARED
#define CANSM_INTERNAL_VAR_POWER_ON_CLEARED
#define CANSM_VAR_SAVED_ZONEX

/* PduR */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define PDUR_CODE
#define PDUR_CALLOUT_CODE
#define PDUR_CODE_FAST
#define PDUR_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define PDUR_CONST
#define PDUR_CALIB
#define PDUR_CONFIG_DATA
#define PDUR_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define PDUR_APPL_DATA
#define PDUR_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*PDUR_VAR_<INIT_POLICY>*/
#define PDUR_VAR_NO_INIT
#define PDUR_VAR_INIT
#define PDUR_VAR_POWER_ON_INIT
#define PDUR_VAR_CLEARED
#define PDUR_VAR_POWER_ON_CLEARED
/*PDUR_VAR_FAST_<INIT_POLICY>*/
#define PDUR_VAR_FAST_NO_INIT
#define PDUR_VAR_FAST_INIT
#define PDUR_VAR_FAST_POWER_ON_INIT
#define PDUR_VAR_FAST_CLEARED
#define PDUR_VAR_FAST_POWER_ON_CLEARED
/*PDUR_VAR_SLOW_<INIT_POLICY>*/
#define PDUR_VAR_SLOW_NO_INIT
#define PDUR_VAR_SLOW_INIT
#define PDUR_VAR_SLOW_POWER_ON_INIT
#define PDUR_VAR_SLOW_CLEARED
#define PDUR_VAR_SLOW_POWER_ON_CLEARED
/*PDUR_INTERNAL_VAR_<INIT_POLICY>*/
#define PDUR_INTERNAL_VAR_NO_INIT
#define PDUR_INTERNAL_VAR_INIT
#define PDUR_INTERNAL_VAR_POWER_ON_INIT
#define PDUR_INTERNAL_VAR_CLEARED
#define PDUR_INTERNAL_VAR_POWER_ON_CLEARED
#define PDUR_VAR_SAVED_ZONEX

/* CanTp */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CANTP_CODE
#define CANTP_CALLOUT_CODE
#define CANTP_CODE_FAST
#define CANTP_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CANTP_CONST
#define CANTP_CALIB
#define CANTP_CONFIG_DATA
#define CANTP_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CANTP_APPL_DATA
#define CANTP_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CANTP_VAR_<INIT_POLICY>*/
#define CANTP_VAR_NO_INIT
#define CANTP_VAR_INIT
#define CANTP_VAR_POWER_ON_INIT
#define CANTP_VAR_CLEARED
#define CANTP_VAR_POWER_ON_CLEARED
/*CANTP_VAR_FAST_<INIT_POLICY>*/
#define CANTP_VAR_FAST_NO_INIT
#define CANTP_VAR_FAST_INIT
#define CANTP_VAR_FAST_POWER_ON_INIT
#define CANTP_VAR_FAST_CLEARED
#define CANTP_VAR_FAST_POWER_ON_CLEARED
/*CANTP_VAR_SLOW_<INIT_POLICY>*/
#define CANTP_VAR_SLOW_NO_INIT
#define CANTP_VAR_SLOW_INIT
#define CANTP_VAR_SLOW_POWER_ON_INIT
#define CANTP_VAR_SLOW_CLEARED
#define CANTP_VAR_SLOW_POWER_ON_CLEARED
/*CANTP_INTERNAL_VAR_<INIT_POLICY>*/
#define CANTP_INTERNAL_VAR_NO_INIT
#define CANTP_INTERNAL_VAR_INIT
#define CANTP_INTERNAL_VAR_POWER_ON_INIT
#define CANTP_INTERNAL_VAR_CLEARED
#define CANTP_INTERNAL_VAR_POWER_ON_CLEARED
#define CANTP_VAR_SAVED_ZONEX

/* Gdn_TmrSrv */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define GDN_TMRSRV_CODE
#define GDN_TMRSRV_CALLOUT_CODE
#define GDN_TMRSRV_CODE_FAST
#define GDN_TMRSRV_CODE_SLOW    __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define GDN_TMRSRV_CONST
#define GDN_TMRSRV_CALIB
#define GDN_TMRSRV_CONFIG_DATA
#define GDN_TMRSRV_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define GDN_TMRSRV_APPL_DATA
#define GDN_TMRSRV_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*GDN_TMRSRV_VAR_<INIT_POLICY>*/
#define GDN_TMRSRV_VAR_NO_INIT
#define GDN_TMRSRV_VAR_INIT
#define GDN_TMRSRV_VAR_POWER_ON_INIT
#define GDN_TMRSRV_VAR_CLEARED
#define GDN_TMRSRV_VAR_POWER_ON_CLEARED
/*GDN_TMRSRV_VAR_FAST_<INIT_POLICY>*/
#define GDN_TMRSRV_VAR_FAST_NO_INIT
#define GDN_TMRSRV_VAR_FAST_INIT
#define GDN_TMRSRV_VAR_FAST_POWER_ON_INIT
#define GDN_TMRSRV_VAR_FAST_CLEARED
#define GDN_TMRSRV_VAR_FAST_POWER_ON_CLEARED
/*GDN_TMRSRV_VAR_SLOW_<INIT_POLICY>*/
#define GDN_TMRSRV_VAR_SLOW_NO_INIT
#define GDN_TMRSRV_VAR_SLOW_INIT
#define GDN_TMRSRV_VAR_SLOW_POWER_ON_INIT
#define GDN_TMRSRV_VAR_SLOW_CLEARED
#define GDN_TMRSRV_VAR_SLOW_POWER_ON_CLEARED
/*GDN_TMRSRV_INTERNAL_VAR_<INIT_POLICY>*/
#define GDN_TMRSRV_INTERNAL_VAR_NO_INIT
#define GDN_TMRSRV_INTERNAL_VAR_INIT
#define GDN_TMRSRV_INTERNAL_VAR_POWER_ON_INIT
#define GDN_TMRSRV_INTERNAL_VAR_CLEARED
#define GDN_TMRSRV_INTERNAL_VAR_POWER_ON_CLEARED
#define GDN_TMRSRV_VAR_SAVED_ZONEX

/* MemM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define MEMM_CODE
#define MEMM_CALLOUT_CODE
#define MEMM_CODE_FAST
#define MEMM_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define MEMM_CONST
#define MEMM_CALIB
#define MEMM_CONFIG_DATA
#define MEMM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define MEMM_APPL_DATA
#define MEMM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*MEMM_VAR_<INIT_POLICY>*/
#define MEMM_VAR_NO_INIT
#define MEMM_VAR_INIT
#define MEMM_VAR_POWER_ON_INIT
#define MEMM_VAR_CLEARED
#define MEMM_VAR_POWER_ON_CLEARED
/*MEMM_VAR_FAST_<INIT_POLICY>*/
#define MEMM_VAR_FAST_NO_INIT
#define MEMM_VAR_FAST_INIT
#define MEMM_VAR_FAST_POWER_ON_INIT
#define MEMM_VAR_FAST_CLEARED
#define MEMM_VAR_FAST_POWER_ON_CLEARED
/*MEMM_VAR_SLOW_<INIT_POLICY>*/
#define MEMM_VAR_SLOW_NO_INIT
#define MEMM_VAR_SLOW_INIT
#define MEMM_VAR_SLOW_POWER_ON_INIT
#define MEMM_VAR_SLOW_CLEARED
#define MEMM_VAR_SLOW_POWER_ON_CLEARED
/*MEMM_INTERNAL_VAR_<INIT_POLICY>*/
#define MEMM_INTERNAL_VAR_NO_INIT
#define MEMM_INTERNAL_VAR_INIT
#define MEMM_INTERNAL_VAR_POWER_ON_INIT
#define MEMM_INTERNAL_VAR_CLEARED
#define MEMM_INTERNAL_VAR_POWER_ON_CLEARED
#define MEMM_VAR_SAVED_ZONEX

/* MemErrM */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define MEMERRM_CODE
#define MEMERRM_CALLOUT_CODE
#define MEMERRM_CODE_FAST
#define MEMERRM_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define MEMERRM_CONST
#define MEMERRM_CALIB
#define MEMERRM_CONFIG_DATA
#define MEMERRM_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define MEMERRM_APPL_DATA
#define MEMERRM_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*MEMERRM_VAR_<INIT_POLICY>*/
#define MEMERRM_VAR_NO_INIT
#define MEMERRM_VAR_INIT
#define MEMERRM_VAR_POWER_ON_INIT
#define MEMERRM_VAR_CLEARED
#define MEMERRM_VAR_POWER_ON_CLEARED
/*MEMERRM_VAR_FAST_<INIT_POLICY>*/
#define MEMERRM_VAR_FAST_NO_INIT
#define MEMERRM_VAR_FAST_INIT
#define MEMERRM_VAR_FAST_POWER_ON_INIT
#define MEMERRM_VAR_FAST_CLEARED
#define MEMERRM_VAR_FAST_POWER_ON_CLEARED
/*MEMERRM_VAR_SLOW_<INIT_POLICY>*/
#define MEMERRM_VAR_SLOW_NO_INIT
#define MEMERRM_VAR_SLOW_INIT
#define MEMERRM_VAR_SLOW_POWER_ON_INIT
#define MEMERRM_VAR_SLOW_CLEARED
#define MEMERRM_VAR_SLOW_POWER_ON_CLEARED
/*MEMERRM_INTERNAL_VAR_<INIT_POLICY>*/
#define MEMERRM_INTERNAL_VAR_NO_INIT
#define MEMERRM_INTERNAL_VAR_INIT
#define MEMERRM_INTERNAL_VAR_POWER_ON_INIT
#define MEMERRM_INTERNAL_VAR_CLEARED
#define MEMERRM_INTERNAL_VAR_POWER_ON_CLEARED
#define MEMERRM_VAR_SAVED_ZONEX

/* WdgIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define WDGIF_CODE
#define WDGIF_CALLOUT_CODE
#define WDGIF_CODE_FAST
#define WDGIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define WDGIF_CONST
#define WDGIF_CALIB
#define WDGIF_CONFIG_DATA
#define WDGIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define WDGIF_APPL_DATA
#define WDGIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*WDGIF_VAR_<INIT_POLICY>*/
#define WDGIF_VAR_NO_INIT
#define WDGIF_VAR_INIT
#define WDGIF_VAR_POWER_ON_INIT
#define WDGIF_VAR_CLEARED
#define WDGIF_VAR_POWER_ON_CLEARED
/*WDGIF_VAR_FAST_<INIT_POLICY>*/
#define WDGIF_VAR_FAST_NO_INIT
#define WDGIF_VAR_FAST_INIT
#define WDGIF_VAR_FAST_POWER_ON_INIT
#define WDGIF_VAR_FAST_CLEARED
#define WDGIF_VAR_FAST_POWER_ON_CLEARED
/*WDGIF_VAR_SLOW_<INIT_POLICY>*/
#define WDGIF_VAR_SLOW_NO_INIT
#define WDGIF_VAR_SLOW_INIT
#define WDGIF_VAR_SLOW_POWER_ON_INIT
#define WDGIF_VAR_SLOW_CLEARED
#define WDGIF_VAR_SLOW_POWER_ON_CLEARED
/*WDGIF_INTERNAL_VAR_<INIT_POLICY>*/
#define WDGIF_INTERNAL_VAR_NO_INIT
#define WDGIF_INTERNAL_VAR_INIT
#define WDGIF_INTERNAL_VAR_POWER_ON_INIT
#define WDGIF_INTERNAL_VAR_CLEARED
#define WDGIF_INTERNAL_VAR_POWER_ON_CLEARED
#define WDGIF_VAR_SAVED_ZONEX

/* CanIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CANIF_CODE
#define CANIF_CALLOUT_CODE
#define CANIF_CODE_FAST
#define CANIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CANIF_CONST
#define CANIF_CALIB
#define CANIF_CONFIG_DATA
#define CANIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CANIF_APPL_DATA
#define CANIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CANIF_VAR_<INIT_POLICY>*/
#define CANIF_VAR_NO_INIT
#define CANIF_VAR_INIT
#define CANIF_VAR_POWER_ON_INIT
#define CANIF_VAR_CLEARED
#define CANIF_VAR_POWER_ON_CLEARED
/*CANIF_VAR_FAST_<INIT_POLICY>*/
#define CANIF_VAR_FAST_NO_INIT
#define CANIF_VAR_FAST_INIT
#define CANIF_VAR_FAST_POWER_ON_INIT
#define CANIF_VAR_FAST_CLEARED
#define CANIF_VAR_FAST_POWER_ON_CLEARED
/*CANIF_VAR_SLOW_<INIT_POLICY>*/
#define CANIF_VAR_SLOW_NO_INIT
#define CANIF_VAR_SLOW_INIT
#define CANIF_VAR_SLOW_POWER_ON_INIT
#define CANIF_VAR_SLOW_CLEARED
#define CANIF_VAR_SLOW_POWER_ON_CLEARED
/*CANIF_INTERNAL_VAR_<INIT_POLICY>*/
#define CANIF_INTERNAL_VAR_NO_INIT
#define CANIF_INTERNAL_VAR_INIT
#define CANIF_INTERNAL_VAR_POWER_ON_INIT
#define CANIF_INTERNAL_VAR_CLEARED
#define CANIF_INTERNAL_VAR_POWER_ON_CLEARED
#define CANIF_VAR_SAVED_ZONEX

/*--------------------------
 memory Type : CODE 
--------------------------*/
#define GDN_CANIF_CODE
#define GDN_CANIF_CALLOUT_CODE
#define GDN_CANIF_CODE_FAST
#define GDN_CANIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define GDN_CANIF_CONST
#define GDN_CANIF_CALIB
#define GDN_CANIF_CONFIG_DATA
#define GDN_CANIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define GDN_CANIF_APPL_DATA
#define GDN_CANIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*GDN_CANIF_VAR_<INIT_POLICY>*/
#define GDN_CANIF_VAR_NO_INIT
#define GDN_CANIF_VAR_INIT
#define GDN_CANIF_VAR_POWER_ON_INIT
#define GDN_CANIF_VAR_CLEARED
#define GDN_CANIF_VAR_POWER_ON_CLEARED
/*GDN_CANIF_VAR_FAST_<INIT_POLICY>*/
#define GDN_CANIF_VAR_FAST_NO_INIT
#define GDN_CANIF_VAR_FAST_INIT
#define GDN_CANIF_VAR_FAST_POWER_ON_INIT
#define GDN_CANIF_VAR_FAST_CLEARED
#define GDN_CANIF_VAR_FAST_POWER_ON_CLEARED
/*GDN_CANIF_VAR_SLOW_<INIT_POLICY>*/
#define GDN_CANIF_VAR_SLOW_NO_INIT
#define GDN_CANIF_VAR_SLOW_INIT
#define GDN_CANIF_VAR_SLOW_POWER_ON_INIT
#define GDN_CANIF_VAR_SLOW_CLEARED
#define GDN_CANIF_VAR_SLOW_POWER_ON_CLEARED
/*GDN_CANIF_INTERNAL_VAR_<INIT_POLICY>*/
#define GDN_CANIF_INTERNAL_VAR_NO_INIT
#define GDN_CANIF_INTERNAL_VAR_INIT
#define GDN_CANIF_INTERNAL_VAR_POWER_ON_INIT
#define GDN_CANIF_INTERNAL_VAR_CLEARED
#define GDN_CANIF_INTERNAL_VAR_POWER_ON_CLEARED
#define GDN_CANIF_VAR_SAVED_ZONEX

/* CanTrcv */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CANTRCV_CODE
#define CANTRCV_CALLOUT_CODE
#define CANTRCV_CODE_FAST
#define CANTRCV_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CANTRCV_CONST
#define CANTRCV_CALIB
#define CANTRCV_CONFIG_DATA
#define CANTRCV_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CANTRCV_APPL_DATA
#define CANTRCV_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CANTRCV_VAR_<INIT_POLICY>*/
#define CANTRCV_VAR_NO_INIT
#define CANTRCV_VAR_INIT
#define CANTRCV_VAR_POWER_ON_INIT
#define CANTRCV_VAR_CLEARED
#define CANTRCV_VAR_POWER_ON_CLEARED
/*CANTRCV_VAR_FAST_<INIT_POLICY>*/
#define CANTRCV_VAR_FAST_NO_INIT
#define CANTRCV_VAR_FAST_INIT
#define CANTRCV_VAR_FAST_POWER_ON_INIT
#define CANTRCV_VAR_FAST_CLEARED
#define CANTRCV_VAR_FAST_POWER_ON_CLEARED
/*CANTRCV_VAR_SLOW_<INIT_POLICY>*/
#define CANTRCV_VAR_SLOW_NO_INIT
#define CANTRCV_VAR_SLOW_INIT
#define CANTRCV_VAR_SLOW_POWER_ON_INIT
#define CANTRCV_VAR_SLOW_CLEARED
#define CANTRCV_VAR_SLOW_POWER_ON_CLEARED
/*CANTRCV_INTERNAL_VAR_<INIT_POLICY>*/
#define CANTRCV_INTERNAL_VAR_NO_INIT
#define CANTRCV_INTERNAL_VAR_INIT
#define CANTRCV_INTERNAL_VAR_POWER_ON_INIT
#define CANTRCV_INTERNAL_VAR_CLEARED
#define CANTRCV_INTERNAL_VAR_POWER_ON_CLEARED
#define CANTRCV_VAR_SAVED_ZONEX

/* CodeFlsIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CODEFLSIF_CODE
#define CODEFLSIF_CALLOUT_CODE
#define CODEFLSIF_CODE_FAST
#define CODEFLSIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CODEFLSIF_CONST
#define CODEFLSIF_CALIB
#define CODEFLSIF_CONFIG_DATA
#define CODEFLSIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CODEFLSIF_APPL_DATA
#define CODEFLSIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CODEFLSIF_VAR_<INIT_POLICY>*/
#define CODEFLSIF_VAR_NO_INIT
#define CODEFLSIF_VAR_INIT
#define CODEFLSIF_VAR_POWER_ON_INIT
#define CODEFLSIF_VAR_CLEARED
#define CODEFLSIF_VAR_POWER_ON_CLEARED
/*CODEFLSIF_VAR_FAST_<INIT_POLICY>*/
#define CODEFLSIF_VAR_FAST_NO_INIT
#define CODEFLSIF_VAR_FAST_INIT
#define CODEFLSIF_VAR_FAST_POWER_ON_INIT
#define CODEFLSIF_VAR_FAST_CLEARED
#define CODEFLSIF_VAR_FAST_POWER_ON_CLEARED
/*CODEFLSIF_VAR_SLOW_<INIT_POLICY>*/
#define CODEFLSIF_VAR_SLOW_NO_INIT
#define CODEFLSIF_VAR_SLOW_INIT
#define CODEFLSIF_VAR_SLOW_POWER_ON_INIT
#define CODEFLSIF_VAR_SLOW_CLEARED
#define CODEFLSIF_VAR_SLOW_POWER_ON_CLEARED
/*CODEFLSIF_INTERNAL_VAR_<INIT_POLICY>*/
#define CODEFLSIF_INTERNAL_VAR_NO_INIT
#define CODEFLSIF_INTERNAL_VAR_INIT
#define CODEFLSIF_INTERNAL_VAR_POWER_ON_INIT
#define CODEFLSIF_INTERNAL_VAR_CLEARED
#define CODEFLSIF_INTERNAL_VAR_POWER_ON_CLEARED
#define CODEFLSIF_VAR_SAVED_ZONEX

/* ExtCodeFlsIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define EXTCODEFLSIF_CODE
#define EXTCODEFLSIF_CALLOUT_CODE
#define EXTCODEFLSIF_CODE_FAST
#define EXTCODEFLSIF_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define EXTCODEFLSIF_CONST
#define EXTCODEFLSIF_CALIB
#define EXTCODEFLSIF_CONFIG_DATA
#define EXTCODEFLSIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define EXTCODEFLSIF_APPL_DATA
#define EXTCODEFLSIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*EXTCODEFLSIF_VAR_<INIT_POLICY>*/
#define EXTCODEFLSIF_VAR_NO_INIT
#define EXTCODEFLSIF_VAR_INIT
#define EXTCODEFLSIF_VAR_POWER_ON_INIT
#define EXTCODEFLSIF_VAR_CLEARED
#define EXTCODEFLSIF_VAR_POWER_ON_CLEARED
/*EXTCODEFLSIF_VAR_FAST_<INIT_POLICY>*/
#define EXTCODEFLSIF_VAR_FAST_NO_INIT
#define EXTCODEFLSIF_VAR_FAST_INIT
#define EXTCODEFLSIF_VAR_FAST_POWER_ON_INIT
#define EXTCODEFLSIF_VAR_FAST_CLEARED
#define EXTCODEFLSIF_VAR_FAST_POWER_ON_CLEARED
/*EXTCODEFLSIF_VAR_SLOW_<INIT_POLICY>*/
#define EXTCODEFLSIF_VAR_SLOW_NO_INIT
#define EXTCODEFLSIF_VAR_SLOW_INIT
#define EXTCODEFLSIF_VAR_SLOW_POWER_ON_INIT
#define EXTCODEFLSIF_VAR_SLOW_CLEARED
#define EXTCODEFLSIF_VAR_SLOW_POWER_ON_CLEARED
/*EXTCODEFLSIF_INTERNAL_VAR_<INIT_POLICY>*/
#define EXTCODEFLSIF_INTERNAL_VAR_NO_INIT
#define EXTCODEFLSIF_INTERNAL_VAR_INIT
#define EXTCODEFLSIF_INTERNAL_VAR_POWER_ON_INIT
#define EXTCODEFLSIF_INTERNAL_VAR_CLEARED
#define EXTCODEFLSIF_INTERNAL_VAR_POWER_ON_CLEARED
#define EXTCODEFLSIF_VAR_SAVED_ZONEX

/* CodeRamIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CODERAMIF_CODE
#define CODERAMIF_CALLOUT_CODE
#define CODERAMIF_CODE_FAST
#define CODERAMIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CODERAMIF_CONST
#define CODERAMIF_CALIB
#define CODERAMIF_CONFIG_DATA
#define CODERAMIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CODERAMIF_APPL_DATA
#define CODERAMIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CODERAMIF_VAR_<INIT_POLICY>*/
#define CODERAMIF_VAR_NO_INIT
#define CODERAMIF_VAR_INIT
#define CODERAMIF_VAR_POWER_ON_INIT
#define CODERAMIF_VAR_CLEARED
#define CODERAMIF_VAR_POWER_ON_CLEARED
/*CODERAMIF_VAR_FAST_<INIT_POLICY>*/
#define CODERAMIF_VAR_FAST_NO_INIT
#define CODERAMIF_VAR_FAST_INIT
#define CODERAMIF_VAR_FAST_POWER_ON_INIT
#define CODERAMIF_VAR_FAST_CLEARED
#define CODERAMIF_VAR_FAST_POWER_ON_CLEARED
/*CODERAMIF_VAR_SLOW_<INIT_POLICY>*/
#define CODERAMIF_VAR_SLOW_NO_INIT
#define CODERAMIF_VAR_SLOW_INIT
#define CODERAMIF_VAR_SLOW_POWER_ON_INIT
#define CODERAMIF_VAR_SLOW_CLEARED
#define CODERAMIF_VAR_SLOW_POWER_ON_CLEARED
/*CODERAMIF_INTERNAL_VAR_<INIT_POLICY>*/
#define CODERAMIF_INTERNAL_VAR_NO_INIT
#define CODERAMIF_INTERNAL_VAR_INIT
#define CODERAMIF_INTERNAL_VAR_POWER_ON_INIT
#define CODERAMIF_INTERNAL_VAR_CLEARED
#define CODERAMIF_INTERNAL_VAR_POWER_ON_CLEARED
#define CODERAMIF_VAR_SAVED_ZONEX

/* CodeRamIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CODERAMIF_CODE
#define CODERAMIF_CALLOUT_CODE
#define CODERAMIF_CODE_FAST
#define CODERAMIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CODERAMIF_CONST
#define CODERAMIF_CALIB
#define CODERAMIF_CONFIG_DATA
#define CODERAMIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CODERAMIF_APPL_DATA
#define CODERAMIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CODERAMIF_VAR_<INIT_POLICY>*/
#define CODERAMIF_VAR_NO_INIT
#define CODERAMIF_VAR_INIT
#define CODERAMIF_VAR_POWER_ON_INIT
#define CODERAMIF_VAR_CLEARED
#define CODERAMIF_VAR_POWER_ON_CLEARED
/*CODERAMIF_VAR_FAST_<INIT_POLICY>*/
#define CODERAMIF_VAR_FAST_NO_INIT
#define CODERAMIF_VAR_FAST_INIT
#define CODERAMIF_VAR_FAST_POWER_ON_INIT
#define CODERAMIF_VAR_FAST_CLEARED
#define CODERAMIF_VAR_FAST_POWER_ON_CLEARED
/*CODERAMIF_VAR_SLOW_<INIT_POLICY>*/
#define CODERAMIF_VAR_SLOW_NO_INIT
#define CODERAMIF_VAR_SLOW_INIT
#define CODERAMIF_VAR_SLOW_POWER_ON_INIT
#define CODERAMIF_VAR_SLOW_CLEARED
#define CODERAMIF_VAR_SLOW_POWER_ON_CLEARED
/*CODERAMIF_INTERNAL_VAR_<INIT_POLICY>*/
#define CODERAMIF_INTERNAL_VAR_NO_INIT
#define CODERAMIF_INTERNAL_VAR_INIT
#define CODERAMIF_INTERNAL_VAR_POWER_ON_INIT
#define CODERAMIF_INTERNAL_VAR_CLEARED
#define CODERAMIF_INTERNAL_VAR_POWER_ON_CLEARED
#define CODERAMIF_VAR_SAVED_ZONEX

/* UsrSoftIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define USRSOFTIF_CODE
#define USRSOFTIF_CALLOUT_CODE
#define USRSOFTIF_CODE_FAST
#define USRSOFTIF_CODE_SLOW __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define USRSOFTIF_CONST
#define USRSOFTIF_CALIB
#define USRSOFTIF_CONFIG_DATA
#define USRSOFTIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define USRSOFTIF_APPL_DATA
#define USRSOFTIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*USRSOFTIF_VAR_<INIT_POLICY>*/
#define USRSOFTIF_VAR_NO_INIT
#define USRSOFTIF_VAR_INIT
#define USRSOFTIF_VAR_POWER_ON_INIT
#define USRSOFTIF_VAR_CLEARED
#define USRSOFTIF_VAR_POWER_ON_CLEARED
/*USRSOFTIF_VAR_FAST_<INIT_POLICY>*/
#define USRSOFTIF_VAR_FAST_NO_INIT
#define USRSOFTIF_VAR_FAST_INIT
#define USRSOFTIF_VAR_FAST_POWER_ON_INIT
#define USRSOFTIF_VAR_FAST_CLEARED
#define USRSOFTIF_VAR_FAST_POWER_ON_CLEARED
/*USRSOFTIF_VAR_SLOW_<INIT_POLICY>*/
#define USRSOFTIF_VAR_SLOW_NO_INIT
#define USRSOFTIF_VAR_SLOW_INIT
#define USRSOFTIF_VAR_SLOW_POWER_ON_INIT
#define USRSOFTIF_VAR_SLOW_CLEARED
#define USRSOFTIF_VAR_SLOW_POWER_ON_CLEARED
/*USRSOFTIF_INTERNAL_VAR_<INIT_POLICY>*/
#define USRSOFTIF_INTERNAL_VAR_NO_INIT
#define USRSOFTIF_INTERNAL_VAR_INIT
#define USRSOFTIF_INTERNAL_VAR_POWER_ON_INIT
#define USRSOFTIF_INTERNAL_VAR_CLEARED
#define USRSOFTIF_INTERNAL_VAR_POWER_ON_CLEARED
#define USRSOFTIF_VAR_SAVED_ZONEX

/* SleepIf */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define SLEEPIF_CODE
#define SLEEPIF_CALLOUT_CODE
#define SLEEPIF_CODE_FAST
#define SLEEPIF_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define SLEEPIF_CONST
#define SLEEPIF_CALIB
#define SLEEPIF_CONFIG_DATA
#define SLEEPIF_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define SLEEPIF_APPL_DATA
#define SLEEPIF_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*SLEEPIF_VAR_<INIT_POLICY>*/
#define SLEEPIF_VAR_NO_INIT
#define SLEEPIF_VAR_INIT
#define SLEEPIF_VAR_POWER_ON_INIT
#define SLEEPIF_VAR_CLEARED
#define SLEEPIF_VAR_POWER_ON_CLEARED
/*SLEEPIF_VAR_FAST_<INIT_POLICY>*/
#define SLEEPIF_VAR_FAST_NO_INIT
#define SLEEPIF_VAR_FAST_INIT
#define SLEEPIF_VAR_FAST_POWER_ON_INIT
#define SLEEPIF_VAR_FAST_CLEARED
#define SLEEPIF_VAR_FAST_POWER_ON_CLEARED
/*SLEEPIF_VAR_SLOW_<INIT_POLICY>*/
#define SLEEPIF_VAR_SLOW_NO_INIT
#define SLEEPIF_VAR_SLOW_INIT
#define SLEEPIF_VAR_SLOW_POWER_ON_INIT
#define SLEEPIF_VAR_SLOW_CLEARED
#define SLEEPIF_VAR_SLOW_POWER_ON_CLEARED
/*SLEEPIF_INTERNAL_VAR_<INIT_POLICY>*/
#define SLEEPIF_INTERNAL_VAR_NO_INIT
#define SLEEPIF_INTERNAL_VAR_INIT
#define SLEEPIF_INTERNAL_VAR_POWER_ON_INIT
#define SLEEPIF_INTERNAL_VAR_CLEARED
#define SLEEPIF_INTERNAL_VAR_POWER_ON_CLEARED
#define SLEEPIF_VAR_SAVED_ZONEX

/* Mcu */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define MCU_CODE
#define MCU_CALLOUT_CODE
#define MCU_CODE_FAST
#define MCU_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define MCU_CONST
#define MCU_CALIB
#define MCU_CONFIG_DATA
#define MCU_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define MCU_APPL_DATA
#define MCU_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*MCU_VAR_<INIT_POLICY>*/
#define MCU_VAR_NO_INIT
#define MCU_VAR_INIT
#define MCU_VAR_POWER_ON_INIT
#define MCU_VAR_CLEARED
#define MCU_VAR_POWER_ON_CLEARED
/*MCU_VAR_FAST_<INIT_POLICY>*/
#define MCU_VAR_FAST_NO_INIT
#define MCU_VAR_FAST_INIT
#define MCU_VAR_FAST_POWER_ON_INIT
#define MCU_VAR_FAST_CLEARED
#define MCU_VAR_FAST_POWER_ON_CLEARED
/*MCU_VAR_SLOW_<INIT_POLICY>*/
#define MCU_VAR_SLOW_NO_INIT
#define MCU_VAR_SLOW_INIT
#define MCU_VAR_SLOW_POWER_ON_INIT
#define MCU_VAR_SLOW_CLEARED
#define MCU_VAR_SLOW_POWER_ON_CLEARED
/*MCU_INTERNAL_VAR_<INIT_POLICY>*/
#define MCU_INTERNAL_VAR_NO_INIT
#define MCU_INTERNAL_VAR_INIT
#define MCU_INTERNAL_VAR_POWER_ON_INIT
#define MCU_INTERNAL_VAR_CLEARED
#define MCU_INTERNAL_VAR_POWER_ON_CLEARED
#define MCU_VAR_SAVED_ZONEX

/* Gpt */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define GPT_CODE
#define GPT_CALLOUT_CODE
#define GPT_CODE_FAST
#define GPT_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define GPT_CONST
#define GPT_CALIB
#define GPT_CONFIG_DATA
#define GPT_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define GPT_APPL_DATA
#define GPT_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*GPT_VAR_<INIT_POLICY>*/
#define GPT_VAR_NO_INIT
#define GPT_VAR_INIT
#define GPT_VAR_POWER_ON_INIT
#define GPT_VAR_CLEARED
#define GPT_VAR_POWER_ON_CLEARED
/*GPT_VAR_FAST_<INIT_POLICY>*/
#define GPT_VAR_FAST_NO_INIT
#define GPT_VAR_FAST_INIT
#define GPT_VAR_FAST_POWER_ON_INIT
#define GPT_VAR_FAST_CLEARED
#define GPT_VAR_FAST_POWER_ON_CLEARED
/*GPT_VAR_SLOW_<INIT_POLICY>*/
#define GPT_VAR_SLOW_NO_INIT
#define GPT_VAR_SLOW_INIT
#define GPT_VAR_SLOW_POWER_ON_INIT
#define GPT_VAR_SLOW_CLEARED
#define GPT_VAR_SLOW_POWER_ON_CLEARED
/*GPT_INTERNAL_VAR_<INIT_POLICY>*/
#define GPT_INTERNAL_VAR_NO_INIT
#define GPT_INTERNAL_VAR_INIT
#define GPT_INTERNAL_VAR_POWER_ON_INIT
#define GPT_INTERNAL_VAR_CLEARED
#define GPT_INTERNAL_VAR_POWER_ON_CLEARED
#define GPT_VAR_SAVED_ZONEX

/* Int */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define INT_CODE
#define INT_CALLOUT_CODE
#define INT_CODE_FAST
#define INT_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define INT_CONST
#define INT_CALIB
#define INT_CONFIG_DATA
#define INT_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define INT_APPL_DATA
#define INT_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*INT_VAR_<INIT_POLICY>*/
#define INT_VAR_NO_INIT
#define INT_VAR_INIT
#define INT_VAR_POWER_ON_INIT
#define INT_VAR_CLEARED
#define INT_VAR_POWER_ON_CLEARED
/*INT_VAR_FAST_<INIT_POLICY>*/
#define INT_VAR_FAST_NO_INIT
#define INT_VAR_FAST_INIT
#define INT_VAR_FAST_POWER_ON_INIT
#define INT_VAR_FAST_CLEARED
#define INT_VAR_FAST_POWER_ON_CLEARED
/*INT_VAR_SLOW_<INIT_POLICY>*/
#define INT_VAR_SLOW_NO_INIT
#define INT_VAR_SLOW_INIT
#define INT_VAR_SLOW_POWER_ON_INIT
#define INT_VAR_SLOW_CLEARED
#define INT_VAR_SLOW_POWER_ON_CLEARED
/*INT_INTERNAL_VAR_<INIT_POLICY>*/
#define INT_INTERNAL_VAR_NO_INIT
#define INT_INTERNAL_VAR_INIT
#define INT_INTERNAL_VAR_POWER_ON_INIT
#define INT_INTERNAL_VAR_CLEARED
#define INT_INTERNAL_VAR_POWER_ON_CLEARED
#define INT_VAR_SAVED_ZONEX

/* IntHndlr */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define INTHNDLR_CODE
#define INTHNDLR_CALLOUT_CODE
#define INTHNDLR_CODE_FAST
#define INTHNDLR_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define INTHNDLR_CONST
#define INTHNDLR_CALIB
#define INTHNDLR_CONFIG_DATA
#define INTHNDLR_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define INTHNDLR_APPL_DATA
#define INTHNDLR_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*INTHNDLR_VAR_<INIT_POLICY>*/
#define INTHNDLR_VAR_NO_INIT
#define INTHNDLR_VAR_INIT
#define INTHNDLR_VAR_POWER_ON_INIT
#define INTHNDLR_VAR_CLEARED
#define INTHNDLR_VAR_POWER_ON_CLEARED
/*INTHNDLR_VAR_FAST_<INIT_POLICY>*/
#define INTHNDLR_VAR_FAST_NO_INIT
#define INTHNDLR_VAR_FAST_INIT
#define INTHNDLR_VAR_FAST_POWER_ON_INIT
#define INTHNDLR_VAR_FAST_CLEARED
#define INTHNDLR_VAR_FAST_POWER_ON_CLEARED
/*INTHNDLR_VAR_SLOW_<INIT_POLICY>*/
#define INTHNDLR_VAR_SLOW_NO_INIT
#define INTHNDLR_VAR_SLOW_INIT
#define INTHNDLR_VAR_SLOW_POWER_ON_INIT
#define INTHNDLR_VAR_SLOW_CLEARED
#define INTHNDLR_VAR_SLOW_POWER_ON_CLEARED
/*INTHNDLR_INTERNAL_VAR_<INIT_POLICY>*/
#define INTHNDLR_INTERNAL_VAR_NO_INIT
#define INTHNDLR_INTERNAL_VAR_INIT
#define INTHNDLR_INTERNAL_VAR_POWER_ON_INIT
#define INTHNDLR_INTERNAL_VAR_CLEARED
#define INTHNDLR_INTERNAL_VAR_POWER_ON_CLEARED
#define INTHNDLR_VAR_SAVED_ZONEX

/* Vect */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define VECT_CODE
#define VECT_CALLOUT_CODE
#define VECT_CODE_FAST
#define VECT_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define VECT_CONST
#define VECT_CALIB
#define VECT_CONFIG_DATA
#define VECT_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define VECT_APPL_DATA
#define VECT_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*VECT_VAR_<INIT_POLICY>*/
#define VECT_VAR_NO_INIT
#define VECT_VAR_INIT
#define VECT_VAR_POWER_ON_INIT
#define VECT_VAR_CLEARED
#define VECT_VAR_POWER_ON_CLEARED
/*VECT_VAR_FAST_<INIT_POLICY>*/
#define VECT_VAR_FAST_NO_INIT
#define VECT_VAR_FAST_INIT
#define VECT_VAR_FAST_POWER_ON_INIT
#define VECT_VAR_FAST_CLEARED
#define VECT_VAR_FAST_POWER_ON_CLEARED
/*VECT_VAR_SLOW_<INIT_POLICY>*/
#define VECT_VAR_SLOW_NO_INIT
#define VECT_VAR_SLOW_INIT
#define VECT_VAR_SLOW_POWER_ON_INIT
#define VECT_VAR_SLOW_CLEARED
#define VECT_VAR_SLOW_POWER_ON_CLEARED
/*VECT_INTERNAL_VAR_<INIT_POLICY>*/
#define VECT_INTERNAL_VAR_NO_INIT
#define VECT_INTERNAL_VAR_INIT
#define VECT_INTERNAL_VAR_POWER_ON_INIT
#define VECT_INTERNAL_VAR_CLEARED
#define VECT_INTERNAL_VAR_POWER_ON_CLEARED
#define VECT_VAR_SAVED_ZONEX

/* Wdg */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define WDG_CODE
#define WDG_CALLOUT_CODE
#define WDG_CODE_FAST
#define WDG_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define WDG_CONST
#define WDG_CALIB
#define WDG_CONFIG_DATA
#define WDG_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define WDG_APPL_DATA
#define WDG_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*WDG_VAR_<INIT_POLICY>*/
#define WDG_VAR_NO_INIT
#define WDG_VAR_INIT
#define WDG_VAR_POWER_ON_INIT
#define WDG_VAR_CLEARED
#define WDG_VAR_POWER_ON_CLEARED
/*WDG_VAR_FAST_<INIT_POLICY>*/
#define WDG_VAR_FAST_NO_INIT
#define WDG_VAR_FAST_INIT
#define WDG_VAR_FAST_POWER_ON_INIT
#define WDG_VAR_FAST_CLEARED
#define WDG_VAR_FAST_POWER_ON_CLEARED
/*WDG_VAR_SLOW_<INIT_POLICY>*/
#define WDG_VAR_SLOW_NO_INIT
#define WDG_VAR_SLOW_INIT
#define WDG_VAR_SLOW_POWER_ON_INIT
#define WDG_VAR_SLOW_CLEARED
#define WDG_VAR_SLOW_POWER_ON_CLEARED
/*WDG_INTERNAL_VAR_<INIT_POLICY>*/
#define WDG_INTERNAL_VAR_NO_INIT
#define WDG_INTERNAL_VAR_INIT
#define WDG_INTERNAL_VAR_POWER_ON_INIT
#define WDG_INTERNAL_VAR_CLEARED
#define WDG_INTERNAL_VAR_POWER_ON_CLEARED
#define WDG_VAR_SAVED_ZONEX

/* Can */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CAN_CODE
#define CAN_CALLOUT_CODE
#define CAN_CODE_FAST
#define CAN_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CAN_CONST
#define CAN_CALIB
#define CAN_CONFIG_DATA
#define CAN_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CAN_APPL_DATA
#define CAN_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CAN_VAR_<INIT_POLICY>*/
#define CAN_VAR_NO_INIT
#define CAN_VAR_INIT
#define CAN_VAR_POWER_ON_INIT
#define CAN_VAR_CLEARED
#define CAN_VAR_POWER_ON_CLEARED
/*CAN_VAR_FAST_<INIT_POLICY>*/
#define CAN_VAR_FAST_NO_INIT
#define CAN_VAR_FAST_INIT
#define CAN_VAR_FAST_POWER_ON_INIT
#define CAN_VAR_FAST_CLEARED
#define CAN_VAR_FAST_POWER_ON_CLEARED
/*CAN_VAR_SLOW_<INIT_POLICY>*/
#define CAN_VAR_SLOW_NO_INIT
#define CAN_VAR_SLOW_INIT
#define CAN_VAR_SLOW_POWER_ON_INIT
#define CAN_VAR_SLOW_CLEARED
#define CAN_VAR_SLOW_POWER_ON_CLEARED
/*CAN_INTERNAL_VAR_<INIT_POLICY>*/
#define CAN_INTERNAL_VAR_NO_INIT
#define CAN_INTERNAL_VAR_INIT
#define CAN_INTERNAL_VAR_POWER_ON_INIT
#define CAN_INTERNAL_VAR_CLEARED
#define CAN_INTERNAL_VAR_POWER_ON_CLEARED
#define CAN_VAR_SAVED_ZONEX

/* Port */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define PORT_CODE
#define PORT_CALLOUT_CODE
#define PORT_CODE_FAST
#define PORT_CODE_SLOW  __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define PORT_CONST
#define PORT_CALIB
#define PORT_CONFIG_DATA
#define PORT_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define PORT_APPL_DATA
#define PORT_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*PORT_VAR_<INIT_POLICY>*/
#define PORT_VAR_NO_INIT
#define PORT_VAR_INIT
#define PORT_VAR_POWER_ON_INIT
#define PORT_VAR_CLEARED
#define PORT_VAR_POWER_ON_CLEARED
/*PORT_VAR_FAST_<INIT_POLICY>*/
#define PORT_VAR_FAST_NO_INIT
#define PORT_VAR_FAST_INIT
#define PORT_VAR_FAST_POWER_ON_INIT
#define PORT_VAR_FAST_CLEARED
#define PORT_VAR_FAST_POWER_ON_CLEARED
/*PORT_VAR_SLOW_<INIT_POLICY>*/
#define PORT_VAR_SLOW_NO_INIT
#define PORT_VAR_SLOW_INIT
#define PORT_VAR_SLOW_POWER_ON_INIT
#define PORT_VAR_SLOW_CLEARED
#define PORT_VAR_SLOW_POWER_ON_CLEARED
/*PORT_INTERNAL_VAR_<INIT_POLICY>*/
#define PORT_INTERNAL_VAR_NO_INIT
#define PORT_INTERNAL_VAR_INIT
#define PORT_INTERNAL_VAR_POWER_ON_INIT
#define PORT_INTERNAL_VAR_CLEARED
#define PORT_INTERNAL_VAR_POWER_ON_CLEARED
#define PORT_VAR_SAVED_ZONEX

/* Dio */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define DIO_CODE
#define DIO_CALLOUT_CODE
#define DIO_CODE_FAST
#define DIO_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define DIO_CONST
#define DIO_CALIB
#define DIO_CONFIG_DATA
#define DIO_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define DIO_APPL_DATA
#define DIO_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*DIO_VAR_<INIT_POLICY>*/
#define DIO_VAR_NO_INIT
#define DIO_VAR_INIT
#define DIO_VAR_POWER_ON_INIT
#define DIO_VAR_CLEARED
#define DIO_VAR_POWER_ON_CLEARED
/*DIO_VAR_FAST_<INIT_POLICY>*/
#define DIO_VAR_FAST_NO_INIT
#define DIO_VAR_FAST_INIT
#define DIO_VAR_FAST_POWER_ON_INIT
#define DIO_VAR_FAST_CLEARED
#define DIO_VAR_FAST_POWER_ON_CLEARED
/*DIO_VAR_SLOW_<INIT_POLICY>*/
#define DIO_VAR_SLOW_NO_INIT
#define DIO_VAR_SLOW_INIT
#define DIO_VAR_SLOW_POWER_ON_INIT
#define DIO_VAR_SLOW_CLEARED
#define DIO_VAR_SLOW_POWER_ON_CLEARED
/*DIO_INTERNAL_VAR_<INIT_POLICY>*/
#define DIO_INTERNAL_VAR_NO_INIT
#define DIO_INTERNAL_VAR_INIT
#define DIO_INTERNAL_VAR_POWER_ON_INIT
#define DIO_INTERNAL_VAR_CLEARED
#define DIO_INTERNAL_VAR_POWER_ON_CLEARED
#define DIO_VAR_SAVED_ZONEX

/* CodeFls */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define CODEFLS_CODE
#define CODEFLS_CALLOUT_CODE
#define CODEFLS_CODE_FAST
#define CODEFLS_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define CODEFLS_CONST
#define CODEFLS_CALIB
#define CODEFLS_CONFIG_DATA
#define CODEFLS_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define CODEFLS_APPL_DATA
#define CODEFLS_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*CODEFLS_VAR_<INIT_POLICY>*/
#define CODEFLS_VAR_NO_INIT
#define CODEFLS_VAR_INIT
#define CODEFLS_VAR_POWER_ON_INIT
#define CODEFLS_VAR_CLEARED
#define CODEFLS_VAR_POWER_ON_CLEARED
/*CODEFLS_VAR_FAST_<INIT_POLICY>*/
#define CODEFLS_VAR_FAST_NO_INIT
#define CODEFLS_VAR_FAST_INIT
#define CODEFLS_VAR_FAST_POWER_ON_INIT
#define CODEFLS_VAR_FAST_CLEARED
#define CODEFLS_VAR_FAST_POWER_ON_CLEARED
/*CODEFLS_VAR_SLOW_<INIT_POLICY>*/
#define CODEFLS_VAR_SLOW_NO_INIT
#define CODEFLS_VAR_SLOW_INIT
#define CODEFLS_VAR_SLOW_POWER_ON_INIT
#define CODEFLS_VAR_SLOW_CLEARED
#define CODEFLS_VAR_SLOW_POWER_ON_CLEARED
/*CODEFLS_INTERNAL_VAR_<INIT_POLICY>*/
#define CODEFLS_INTERNAL_VAR_NO_INIT
#define CODEFLS_INTERNAL_VAR_INIT
#define CODEFLS_INTERNAL_VAR_POWER_ON_INIT
#define CODEFLS_INTERNAL_VAR_CLEARED
#define CODEFLS_INTERNAL_VAR_POWER_ON_CLEARED
#define CODEFLS_VAR_SAVED_ZONEX

/* Ecc */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define ECC_CODE
#define ECC_CALLOUT_CODE
#define ECC_CODE_FAST
#define ECC_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define ECC_CONST
#define ECC_CALIB
#define ECC_CONFIG_DATA
#define ECC_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define ECC_APPL_DATA
#define ECC_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*ECC_VAR_<INIT_POLICY>*/
#define ECC_VAR_NO_INIT
#define ECC_VAR_INIT
#define ECC_VAR_POWER_ON_INIT
#define ECC_VAR_CLEARED
#define ECC_VAR_POWER_ON_CLEARED
/*ECC_VAR_FAST_<INIT_POLICY>*/
#define ECC_VAR_FAST_NO_INIT
#define ECC_VAR_FAST_INIT
#define ECC_VAR_FAST_POWER_ON_INIT
#define ECC_VAR_FAST_CLEARED
#define ECC_VAR_FAST_POWER_ON_CLEARED
/*ECC_VAR_SLOW_<INIT_POLICY>*/
#define ECC_VAR_SLOW_NO_INIT
#define ECC_VAR_SLOW_INIT
#define ECC_VAR_SLOW_POWER_ON_INIT
#define ECC_VAR_SLOW_CLEARED
#define ECC_VAR_SLOW_POWER_ON_CLEARED
/*ECC_INTERNAL_VAR_<INIT_POLICY>*/
#define ECC_INTERNAL_VAR_NO_INIT
#define ECC_INTERNAL_VAR_INIT
#define ECC_INTERNAL_VAR_POWER_ON_INIT
#define ECC_INTERNAL_VAR_CLEARED
#define ECC_INTERNAL_VAR_POWER_ON_CLEARED
#define ECC_VAR_SAVED_ZONEX

/* APL */
/*--------------------------
 memory Type : CODE 
--------------------------*/
#define APL_CODE
#define APL_CALLOUT_CODE
#define APL_CODE_FAST
#define APL_CODE_SLOW   __farcall
/*--------------------------
 memory Type : Constants 
--------------------------*/
#define APL_CONST
#define APL_CALIB
#define APL_CONFIG_DATA
#define APL_CONST_SAVED_RECOVERY_ZONEX
/*--------------------------
 memory Type : Pointer 
--------------------------*/
#define APL_APPL_DATA
#define APL_APPL_CONST
/*REGSPACE*/
/*--------------------------*/
/* memory Type : Variables  */
/*--------------------------*/
/*--------------------------
<INIT_POLICY>
NO_INIT,INIT,POWER_ON_INIT,CLEARED,POWER_ON_CLEARED
--------------------------*/
/*APL_VAR_<INIT_POLICY>*/
#define APL_VAR_NO_INIT
#define APL_VAR_INIT
#define APL_VAR_POWER_ON_INIT
#define APL_VAR_CLEARED
#define APL_VAR_POWER_ON_CLEARED
/*STARTUP_VAR_FAST_<INIT_POLICY>*/
#define APL_VAR_FAST_NO_INIT
#define APL_VAR_FAST_INIT
#define APL_VAR_FAST_POWER_ON_INIT
#define APL_VAR_FAST_CLEARED
#define APL_VAR_FAST_POWER_ON_CLEARED
/*STARTUP_VAR_SLOW_<INIT_POLICY>*/
#define APL_VAR_SLOW_NO_INIT
#define APL_VAR_SLOW_INIT
#define APL_VAR_SLOW_POWER_ON_INIT
#define APL_VAR_SLOW_CLEARED
#define APL_VAR_SLOW_POWER_ON_CLEARED
/*STARTUP_INTERNAL_VAR_<INIT_POLICY>*/
#define APL_INTERNAL_VAR_NO_INIT
#define APL_INTERNAL_VAR_INIT
#define APL_INTERNAL_VAR_POWER_ON_INIT
#define APL_INTERNAL_VAR_CLEARED
#define APL_INTERNAL_VAR_POWER_ON_CLEARED
#define APL_VAR_SAVED_ZONEX

/*-------------
Please check whether the following items are necessary
-------------*/
/*! USER_CALLOUT */
/*! USER_SOFTWARECOMPONENT */
/*! USER_TASK_ISR */


#endif /* COMPILER_CFG_H */ /* SWS_COMPILER_00047 */
