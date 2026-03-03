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

#if defined IDSM_START_SEC_CODE
#undef IDSM_START_SEC_CODE
#pragma ghs section text = ".bsw_idsm_code"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_CODE
#undef IDSM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_CODE
#undef IdsM_START_SEC_CODE
#pragma ghs section text = ".bsw_idsm_code"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_CODE
#undef IdsM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_CONST_CONFIG
#undef IDSM_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_idsm_const_config"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_CONST_CONFIG
#undef IDSM_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_CONST_CONFIG
#undef IdsM_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_idsm_const_config"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_CONST_CONFIG
#undef IdsM_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_VAR_NO_INIT
#undef IDSM_START_SEC_VAR_NO_INIT
#pragma ghs section bss    = ".bsw_idsm_var_no_init"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_VAR_NO_INIT
#undef IDSM_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_VAR_NO_INIT
#undef IdsM_START_SEC_VAR_NO_INIT
#pragma ghs section bss    = ".bsw_idsm_var_no_init"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_VAR_NO_INIT
#undef IdsM_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_VAR_CLEARED_WAKEUP
#undef IDSM_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss    = ".bsw_idsm_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_VAR_CLEARED_WAKEUP
#undef IDSM_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_VAR_CLEARED_WAKEUP
#undef IdsM_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss    = ".bsw_idsm_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_VAR_CLEARED_WAKEUP
#undef IdsM_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_APPL_CODE
#undef IDSM_START_SEC_APPL_CODE
#pragma ghs section text = ".bsw_idsm_appl_code"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_APPL_CODE
#undef IDSM_STOP_SEC_APPL_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_APPL_CODE
#undef IdsM_START_SEC_APPL_CODE
#pragma ghs section text = ".bsw_idsm_appl_code"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_APPL_CODE
#undef IdsM_STOP_SEC_APPL_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_APPL_CONST
#undef IDSM_START_SEC_APPL_CONST
#pragma ghs section rodata = ".bsw_idsm_appl_const"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_APPL_CONST
#undef IDSM_STOP_SEC_APPL_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_APPL_CONST
#undef IdsM_START_SEC_APPL_CONST
#pragma ghs section rodata = ".bsw_idsm_appl_const"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_APPL_CONST
#undef IdsM_STOP_SEC_APPL_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_APPL_DATA
#undef IDSM_START_SEC_APPL_DATA
#pragma ghs section bss    = ".bsw_idsm_appl_data"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_APPL_DATA
#undef IDSM_STOP_SEC_APPL_DATA
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_APPL_DATA
#undef IdsM_START_SEC_APPL_DATA
#pragma ghs section bss    = ".bsw_idsm_appl_data"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_APPL_DATA
#undef IdsM_STOP_SEC_APPL_DATA
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IDSM_START_SEC_CONFIG_DATA
#undef IDSM_START_SEC_CONFIG_DATA
#pragma ghs section bss    = ".bsw_idsm_config_data"
#undef MEMMAP_ERROR

#elif defined IDSM_STOP_SEC_CONFIG_DATA
#undef IDSM_STOP_SEC_CONFIG_DATA
#pragma ghs section bss    = default
#undef MEMMAP_ERROR

#elif defined IdsM_START_SEC_CONFIG_DATA
#undef IdsM_START_SEC_CONFIG_DATA
#pragma ghs section bss    = ".bsw_idsm_config_data"
#undef MEMMAP_ERROR

#elif defined IdsM_STOP_SEC_CONFIG_DATA
#undef IdsM_STOP_SEC_CONFIG_DATA
#pragma ghs section bss    = default
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
#error "IdsM_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
