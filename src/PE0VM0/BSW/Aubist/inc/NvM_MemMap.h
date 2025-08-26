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

#if defined NVM_START_SEC_CODE
#undef NVM_START_SEC_CODE
#pragma ghs section text = "bsw_nvm_text"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_CODE
#undef NVM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_CODE
#undef NvM_START_SEC_CODE
#pragma ghs section text = "bsw_nvm_text"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_CODE
#undef NvM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_CODE_TRUST
#undef NVM_START_SEC_CODE_TRUST
#pragma ghs section text = "bsw_nvm_text"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_CODE_TRUST
#undef NVM_STOP_SEC_CODE_TRUST
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_CODE_TRUST
#undef NvM_START_SEC_CODE_TRUST
#pragma ghs section text = "bsw_nvm_text"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_CODE_TRUST
#undef NvM_STOP_SEC_CODE_TRUST
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_CONST_32
#undef NVM_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_nvm_rodata"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_CONST_32
#undef NVM_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_CONST_32
#undef NvM_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_nvm_rodata"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_CONST_32
#undef NvM_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_CONST_CONFIG_32
#undef NVM_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_nvm_rodata"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_CONST_CONFIG_32
#undef NVM_STOP_SEC_CONST_CONFIG_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_CONST_CONFIG_32
#undef NvM_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_nvm_rodata"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_CONST_CONFIG_32
#undef NvM_STOP_SEC_CONST_CONFIG_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_VAR_SAVED_ZONE_32
#undef NVM_START_SEC_VAR_SAVED_ZONE_32
#pragma ghs section bss = "bsw_nvm_bss_saved_zone"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_VAR_SAVED_ZONE_32
#undef NVM_STOP_SEC_VAR_SAVED_ZONE_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_VAR_SAVED_ZONE_32
#undef NvM_START_SEC_VAR_SAVED_ZONE_32
#pragma ghs section bss = "bsw_nvm_bss_saved_zone"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_VAR_SAVED_ZONE_32
#undef NvM_STOP_SEC_VAR_SAVED_ZONE_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_VAR_NO_INIT_32
#undef NVM_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_VAR_NO_INIT_32
#undef NVM_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_VAR_NO_INIT_32
#undef NvM_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_VAR_NO_INIT_32
#undef NvM_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_VAR_NO_INIT_SHARE
#undef NVM_START_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_VAR_NO_INIT_SHARE
#undef NVM_STOP_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_VAR_NO_INIT_SHARE
#undef NvM_START_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_VAR_NO_INIT_SHARE
#undef NvM_STOP_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_VAR_INIT_WAKEUP_32
#undef NVM_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_VAR_INIT_WAKEUP_32
#undef NVM_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss= default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_VAR_INIT_WAKEUP_32
#undef NvM_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_VAR_INIT_WAKEUP_32
#undef NvM_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss= default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_VAR_CLEARED_32
#undef NVM_START_SEC_VAR_CLEARED_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NVM_STOP_SEC_VAR_CLEARED_32
#undef NVM_STOP_SEC_VAR_CLEARED_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NvM_START_SEC_VAR_CLEARED_32
#undef NvM_START_SEC_VAR_CLEARED_32
#pragma ghs section bss = "bsw_nvm_bss"
#undef MEMMAP_ERROR

#elif defined NvM_STOP_SEC_VAR_CLEARED_32
#undef NvM_STOP_SEC_VAR_CLEARED_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined NVM_START_SEC_APPL_DATA
#undef NVM_START_SEC_APPL_DATA

#elif defined NVM_STOP_SEC_APPL_DATA
#undef NVM_STOP_SEC_APPL_DATA

#elif defined NvM_START_SEC_APPL_DATA
#undef NvM_START_SEC_APPL_DATA

#elif defined NvM_STOP_SEC_APPL_DATA
#undef NvM_STOP_SEC_APPL_DATA

#elif defined NVM_START_SEC_APPL_CONST
#undef NVM_START_SEC_APPL_CONST

#elif defined NVM_STOP_SEC_APPL_CONST
#undef NVM_STOP_SEC_APPL_CONST

#elif defined NvM_START_SEC_APPL_CONST
#undef NvM_START_SEC_APPL_CONST

#elif defined NvM_STOP_SEC_APPL_CONST
#undef NvM_STOP_SEC_APPL_CONST

#elif defined NVM_START_SEC_APPL_CODE
#undef NVM_START_SEC_APPL_CODE

#elif defined NVM_STOP_SEC_APPL_CODE
#undef NVM_STOP_SEC_APPL_CODE

#elif defined NvM_START_SEC_APPL_CODE
#undef NvM_START_SEC_APPL_CODE

#elif defined NvM_STOP_SEC_APPL_CODE
#undef NvM_STOP_SEC_APPL_CODE

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
#error "NvM_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
