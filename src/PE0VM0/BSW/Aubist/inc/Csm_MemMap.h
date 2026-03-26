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

#if defined CSM_START_SEC_CODE
#undef CSM_START_SEC_CODE
#pragma ghs section text=".bsw_csm_code"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_CODE
#undef CSM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_CODE
#undef Csm_START_SEC_CODE
#pragma ghs section text=".bsw_csm_code"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_CODE
#undef Csm_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_CONST
#undef CSM_START_SEC_CONST
#pragma ghs section rodata=".bsw_csm_const"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_CONST
#undef CSM_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_CONST
#undef Csm_START_SEC_CONST
#pragma ghs section rodata=".bsw_csm_const"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_CONST
#undef Csm_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_CONST_CONFIG
#undef CSM_START_SEC_CONST_CONFIG
#pragma ghs section rodata=".bsw_csm_const_config"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_CONST_CONFIG
#undef CSM_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_CONST_CONFIG
#undef Csm_START_SEC_CONST_CONFIG
#pragma ghs section rodata=".bsw_csm_const_config"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_CONST_CONFIG
#undef Csm_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_VAR_NO_INIT
#undef CSM_START_SEC_VAR_NO_INIT
#pragma ghs section bss=".bsw_csm_var_no_init"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_VAR_NO_INIT
#undef CSM_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_VAR_NO_INIT
#undef Csm_START_SEC_VAR_NO_INIT
#pragma ghs section bss=".bsw_csm_var_no_init"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_VAR_NO_INIT
#undef Csm_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_VAR_CLEARED_WAKEUP
#undef CSM_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=".bsw_csm_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_VAR_CLEARED_WAKEUP
#undef CSM_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_VAR_CLEARED_WAKEUP
#undef Csm_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=".bsw_csm_var_cleared_wakeup"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_VAR_CLEARED_WAKEUP
#undef Csm_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss=default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_APPL_CODE
#undef CSM_START_SEC_APPL_CODE

#elif defined CSM_STOP_SEC_APPL_CODE
#undef CSM_STOP_SEC_APPL_CODE

#elif defined Csm_START_SEC_APPL_CODE
#undef Csm_START_SEC_APPL_CODE

#elif defined Csm_STOP_SEC_APPL_CODE
#undef Csm_STOP_SEC_APPL_CODE

#elif defined CSM_START_SEC_APPL_DATA
#undef CSM_START_SEC_APPL_DATA

#elif defined CSM_STOP_SEC_APPL_DATA
#undef CSM_STOP_SEC_APPL_DATA

#elif defined Csm_START_SEC_APPL_DATA
#undef Csm_START_SEC_APPL_DATA

#elif defined Csm_STOP_SEC_APPL_DATA
#undef Csm_STOP_SEC_APPL_DATA

#elif defined CSM_START_SEC_CONFIG_DATA
#undef CSM_START_SEC_CONFIG_DATA

#elif defined CSM_STOP_SEC_CONFIG_DATA
#undef CSM_STOP_SEC_CONFIG_DATA

#elif defined Csm_START_SEC_CONFIG_DATA
#undef Csm_START_SEC_CONFIG_DATA

#elif defined Csm_STOP_SEC_CONFIG_DATA
#undef Csm_STOP_SEC_CONFIG_DATA

#elif defined CSM_START_SEC_SHARED_CONST_CONFIG
#undef CSM_START_SEC_SHARED_CONST_CONFIG
#pragma ghs section rodata=".bsw_csm_shared_const_config"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_SHARED_CONST_CONFIG
#undef CSM_STOP_SEC_SHARED_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_SHARED_CONST_CONFIG
#undef Csm_START_SEC_SHARED_CONST_CONFIG
#pragma ghs section rodata=".bsw_csm_shared_const_config"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_SHARED_CONST_CONFIG
#undef Csm_STOP_SEC_SHARED_CONST_CONFIG
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

#elif defined CSM_START_SEC_SHARED_VAR_NO_INIT
#undef CSM_START_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss=".bsw_csm_shared_var_no_init"
#undef MEMMAP_ERROR

#elif defined CSM_STOP_SEC_SHARED_VAR_NO_INIT
#undef CSM_STOP_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss= default
#undef MEMMAP_ERROR

#elif defined Csm_START_SEC_SHARED_VAR_NO_INIT
#undef Csm_START_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss=".bsw_csm_shared_var_no_init"
#undef MEMMAP_ERROR

#elif defined Csm_STOP_SEC_SHARED_VAR_NO_INIT
#undef Csm_STOP_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss= default
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
#error "Csm_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
