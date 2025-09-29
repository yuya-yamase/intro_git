/* MemMap_h_v2-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemMap/HEADER                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define MEMMAP_ERROR

#if defined SECOC_START_SEC_CODE
#undef SECOC_START_SEC_CODE
#pragma ghs section text=".bsw_secoc_code"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CODE
#undef SECOC_STOP_SEC_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CODE
#undef SecOC_START_SEC_CODE
#pragma ghs section text=".bsw_secoc_code"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CODE
#undef SecOC_STOP_SEC_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_CODE_CALLOUT
#undef SECOC_START_SEC_CODE_CALLOUT
#pragma ghs section text=".bsw_secoc_code_callout"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CODE_CALLOUT
#undef SECOC_STOP_SEC_CODE_CALLOUT
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CODE_CALLOUT
#undef SecOC_START_SEC_CODE_CALLOUT
#pragma ghs section text=".bsw_secoc_code_callout"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CODE_CALLOUT
#undef SecOC_STOP_SEC_CODE_CALLOUT
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_CONST
#undef SECOC_START_SEC_CONST
#pragma ghs section rodata=".bsw_secoc_const"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CONST
#undef SECOC_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CONST
#undef SecOC_START_SEC_CONST
#pragma ghs section rodata=".bsw_secoc_const"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CONST
#undef SecOC_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_CONST_CONFIG
#undef SECOC_START_SEC_CONST_CONFIG
#pragma ghs section rodata=".bsw_secoc_const_config"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CONST_CONFIG
#undef SECOC_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CONST_CONFIG
#undef SecOC_START_SEC_CONST_CONFIG
#pragma ghs section rodata=".bsw_secoc_const_config"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CONST_CONFIG
#undef SecOC_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_VAR_NO_INIT
#undef SECOC_START_SEC_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_VAR_NO_INIT
#undef SECOC_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_VAR_NO_INIT
#undef SecOC_START_SEC_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_VAR_NO_INIT
#undef SecOC_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_VAR_CLEARED_WAKEUP
#undef SECOC_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=".bsw_secoc_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_VAR_CLEARED_WAKEUP
#undef SECOC_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_VAR_CLEARED_WAKEUP
#undef SecOC_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=".bsw_secoc_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_VAR_CLEARED_WAKEUP
#undef SecOC_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_CD_FV_CODE
#undef SECOC_START_SEC_CD_FV_CODE
#pragma ghs section text=".bsw_secoc_cd_fv_code"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CD_FV_CODE
#undef SECOC_STOP_SEC_CD_FV_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CD_FV_CODE
#undef SecOC_START_SEC_CD_FV_CODE
#pragma ghs section text=".bsw_secoc_cd_fv_code"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CD_FV_CODE
#undef SecOC_STOP_SEC_CD_FV_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_CD_FV_VAR_NO_INIT
#undef SECOC_START_SEC_CD_FV_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_cd_fv_var_no_init"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_CD_FV_VAR_NO_INIT
#undef SECOC_STOP_SEC_CD_FV_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_CD_FV_VAR_NO_INIT
#undef SecOC_START_SEC_CD_FV_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_cd_fv_var_no_init"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_CD_FV_VAR_NO_INIT
#undef SecOC_STOP_SEC_CD_FV_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_RXAUTH_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_RXAUTH_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_RXAUTH_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_RXAUTH_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_RXAUTH_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_RXAUTH_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_RXAUTH_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_RXAUTH_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_RXMSG_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_RXMSG_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_RXMSG_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_RXMSG_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_RXMSG_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_RXMSG_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_RXMSG_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_RXMSG_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_TXAUTH_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_TXAUTH_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_TXAUTH_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_TXAUTH_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_TXAUTH_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_TXAUTH_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_TXAUTH_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_TXAUTH_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_TXMSG_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_TXMSG_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_TXMSG_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_TXMSG_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_TXMSG_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_TXMSG_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_TXMSG_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_TXMSG_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_RXRESULT_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_RXRESULT_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_RXRESULT_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_RXRESULT_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_RXRESULT_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_RXRESULT_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_RXRESULT_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_RXRESULT_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SECOC_START_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#undef SECOC_START_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SECOC_STOP_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#undef SECOC_STOP_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined SecOC_START_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#undef SecOC_START_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#pragma ghs section bss=".bsw_secoc_var_no_init_gram"
#undef MEMMAP_ERROR

#elif defined SecOC_STOP_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#undef SecOC_STOP_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#endif


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#if defined MEMMAP_ERROR
#error "SecOC_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
