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

#if defined FEE_START_SEC_CODE
#undef FEE_START_SEC_CODE
#pragma ghs section text = "bsw_fee_text"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_CODE
#undef FEE_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_START_SEC_CODE
#undef FEE_PROXY_START_SEC_CODE
#pragma ghs section text = "bsw_fee_text"
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_STOP_SEC_CODE
#undef FEE_PROXY_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_START_SEC_CODE_TRUST
#undef FEE_PROXY_START_SEC_CODE_TRUST
#pragma ghs section text = "bsw_fee_text"
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_STOP_SEC_CODE_TRUST
#undef FEE_PROXY_STOP_SEC_CODE_TRUST
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_CONST_32
#undef FEE_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_fee_rodata"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_CONST_32
#undef FEE_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_CONST_CONFIG_32
#undef FEE_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_fee_rodata"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_CONST_CONFIG_32
#undef FEE_STOP_SEC_CONST_CONFIG_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_START_SEC_CONST_CONFIG
#undef FEE_PROXY_START_SEC_CONST_CONFIG
#pragma ghs section rodata = "bsw_fee_rodata"
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_STOP_SEC_CONST_CONFIG
#undef FEE_PROXY_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_VAR_NO_INIT_32
#undef FEE_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = "bsw_fee_bss"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_VAR_NO_INIT_32
#undef FEE_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_VAR_INIT_WAKEUP_32
#undef FEE_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = "bsw_fee_bss"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_VAR_INIT_WAKEUP_32
#undef FEE_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_VAR_CLEARED_32
#undef FEE_START_SEC_VAR_CLEARED_32
#pragma ghs section bss = "bsw_fee_bss"
#undef MEMMAP_ERROR

#elif defined FEE_STOP_SEC_VAR_CLEARED_32
#undef FEE_STOP_SEC_VAR_CLEARED_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_START_SEC_VAR_NO_INIT_SHARE
#undef FEE_PROXY_START_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = "bsw_fee_bss"
#undef MEMMAP_ERROR

#elif defined FEE_PROXY_STOP_SEC_VAR_NO_INIT_SHARE
#undef FEE_PROXY_STOP_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined FEE_START_SEC_APPL_DATA
#undef FEE_START_SEC_APPL_DATA

#elif defined FEE_STOP_SEC_APPL_DATA
#undef FEE_STOP_SEC_APPL_DATA

#elif defined FEE_START_SEC_APPL_CONST
#undef FEE_START_SEC_APPL_CONST

#elif defined FEE_STOP_SEC_APPL_CONST
#undef FEE_STOP_SEC_APPL_CONST

#elif defined FEE_START_SEC_APPL_CODE
#undef FEE_START_SEC_APPL_CODE

#elif defined FEE_STOP_SEC_APPL_CODE
#undef FEE_STOP_SEC_APPL_CODE

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
#error "Fee_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
