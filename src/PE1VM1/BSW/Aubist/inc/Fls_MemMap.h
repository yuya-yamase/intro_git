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

#if defined FLS_START_SEC_CODE
#undef FLS_START_SEC_CODE
#pragma ghs section text = ".bsw_fls_text"
#undef MEMMAP_ERROR

#elif defined FLS_STOP_SEC_CODE
#undef FLS_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined FLS_START_SEC_CONST_32
#undef FLS_START_SEC_CONST_32
#pragma ghs section rodata = ".bsw_fls_rodata"
#undef MEMMAP_ERROR

#elif defined FLS_STOP_SEC_CONST_32
#undef FLS_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined FLS_START_SEC_CONST_CONFIG_32
#undef FLS_START_SEC_CONST_CONFIG_32

#elif defined FLS_STOP_SEC_CONST_CONFIG_32
#undef FLS_STOP_SEC_CONST_CONFIG_32

#elif defined FLS_START_SEC_VAR_NO_INIT_32
#undef FLS_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = ".bsw_fls_bss"
#undef MEMMAP_ERROR

#elif defined FLS_STOP_SEC_VAR_NO_INIT_32
#undef FLS_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined FLS_START_SEC_VAR_INIT_WAKEUP_32
#undef FLS_START_SEC_VAR_INIT_WAKEUP_32

#elif defined FLS_STOP_SEC_VAR_INIT_WAKEUP_32
#undef FLS_STOP_SEC_VAR_INIT_WAKEUP_32

#elif defined FLS_START_SEC_VAR_CLEARED_32
#undef FLS_START_SEC_VAR_CLEARED_32

#elif defined FLS_STOP_SEC_VAR_CLEARED_32
#undef FLS_STOP_SEC_VAR_CLEARED_32

#elif defined FLS_START_SEC_VAR_CLEARED_WAKEUP_32
#undef FLS_START_SEC_VAR_CLEARED_WAKEUP_32

#elif defined FLS_STOP_SEC_VAR_CLEARED_WAKEUP_32
#undef FLS_STOP_SEC_VAR_CLEARED_WAKEUP_32

#elif defined FLS_START_SEC_APPL_DATA
#undef FLS_START_SEC_APPL_DATA

#elif defined FLS_STOP_SEC_APPL_DATA
#undef FLS_STOP_SEC_APPL_DATA

#elif defined FLS_START_SEC_APPL_CONST
#undef FLS_START_SEC_APPL_CONST

#elif defined FLS_STOP_SEC_APPL_CONST
#undef FLS_STOP_SEC_APPL_CONST

#elif defined FLS_START_SEC_APPL_CODE
#undef FLS_START_SEC_APPL_CODE

#elif defined FLS_STOP_SEC_APPL_CODE
#undef FLS_STOP_SEC_APPL_CODE

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
#error "Fls_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
