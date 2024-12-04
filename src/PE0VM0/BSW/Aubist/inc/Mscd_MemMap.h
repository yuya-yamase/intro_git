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

#if defined MSCD_START_SEC_CODE
#undef MSCD_START_SEC_CODE
#pragma ghs section text = "bsw_mscd_text"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_CODE
#undef MSCD_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_CODE
#undef Mscd_START_SEC_CODE
#pragma ghs section text = "bsw_mscd_text"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_CODE
#undef Mscd_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_CODE_CALLOUT
#undef MSCD_START_SEC_CODE_CALLOUT
#pragma ghs section text = "bsw_mscd_text"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_CODE_CALLOUT
#undef MSCD_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_CODE_CALLOUT
#undef Mscd_START_SEC_CODE_CALLOUT
#pragma ghs section text = "bsw_mscd_text"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_CODE_CALLOUT
#undef Mscd_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_CONST_32
#undef MSCD_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_mscd_rodata"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_CONST_32
#undef MSCD_STOP_SEC_CONST_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_CONST_32
#undef Mscd_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_mscd_rodata"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_CONST_32
#undef Mscd_STOP_SEC_CONST_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_CONST_CONFIG_32
#undef MSCD_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_mscd_rodata"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_CONST_CONFIG_32
#undef MSCD_STOP_SEC_CONST_CONFIG_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_CONST_CONFIG_32
#undef Mscd_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_mscd_rodata"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_CONST_CONFIG_32
#undef Mscd_STOP_SEC_CONST_CONFIG_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_VAR_NO_INIT_32
#undef MSCD_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_VAR_NO_INIT_32
#undef MSCD_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_VAR_NO_INIT_32
#undef Mscd_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_VAR_NO_INIT_32
#undef Mscd_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_VAR_INIT_WAKEUP_32
#undef MSCD_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_VAR_INIT_WAKEUP_32
#undef MSCD_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_VAR_INIT_WAKEUP_32
#undef Mscd_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_VAR_INIT_WAKEUP_32
#undef Mscd_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_VAR_CLEARED_32
#undef MSCD_START_SEC_VAR_CLEARED_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined MSCD_STOP_SEC_VAR_CLEARED_32
#undef MSCD_STOP_SEC_VAR_CLEARED_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Mscd_START_SEC_VAR_CLEARED_32
#undef Mscd_START_SEC_VAR_CLEARED_32
#pragma ghs section bss = "bsw_mscd_bss"
#undef MEMMAP_ERROR

#elif defined Mscd_STOP_SEC_VAR_CLEARED_32
#undef Mscd_STOP_SEC_VAR_CLEARED_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MSCD_START_SEC_APPL_DATA
#undef MSCD_START_SEC_APPL_DATA

#elif defined MSCD_STOP_SEC_APPL_DATA
#undef MSCD_STOP_SEC_APPL_DATA

#elif defined Mscd_START_SEC_APPL_DATA
#undef Mscd_START_SEC_APPL_DATA

#elif defined Mscd_STOP_SEC_APPL_DATA
#undef Mscd_STOP_SEC_APPL_DATA

#elif defined MSCD_START_SEC_APPL_CONST
#undef MSCD_START_SEC_APPL_CONST

#elif defined MSCD_STOP_SEC_APPL_CONST
#undef MSCD_STOP_SEC_APPL_CONST

#elif defined Mscd_START_SEC_APPL_CONST
#undef Mscd_START_SEC_APPL_CONST

#elif defined Mscd_STOP_SEC_APPL_CONST
#undef Mscd_STOP_SEC_APPL_CONST

#elif defined MSCD_START_SEC_APPL_CODE
#undef MSCD_START_SEC_APPL_CODE

#elif defined MSCD_STOP_SEC_APPL_CODE
#undef MSCD_STOP_SEC_APPL_CODE

#elif defined Mscd_START_SEC_APPL_CODE
#undef Mscd_START_SEC_APPL_CODE

#elif defined Mscd_STOP_SEC_APPL_CODE
#undef Mscd_STOP_SEC_APPL_CODE

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
#error "Mscd_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
