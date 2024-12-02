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

#if defined MEMIF_START_SEC_CODE
#undef MEMIF_START_SEC_CODE
#pragma ghs section text = "bsw_memif_text"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_CODE
#undef MEMIF_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_CONST_32
#undef MEMIF_START_SEC_CONST_32
#pragma ghs section rodata = "bsw_memif_rodata"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_CONST_32
#undef MEMIF_STOP_SEC_CONST_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_CONST_CONFIG_32
#undef MEMIF_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = "bsw_memif_rodata"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_CONST_CONFIG_32
#undef MEMIF_STOP_SEC_CONST_CONFIG_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_VAR_NO_INIT_32
#undef MEMIF_START_SEC_VAR_NO_INIT_32
#pragma ghs section rodata = "bsw_memif_bss"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_VAR_NO_INIT_32
#undef MEMIF_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_VAR_INIT_WAKEUP_32
#undef MEMIF_START_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section rodata = "bsw_memif_bss"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_VAR_INIT_WAKEUP_32
#undef MEMIF_STOP_SEC_VAR_INIT_WAKEUP_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_VAR_CLEARED_32
#undef MEMIF_START_SEC_VAR_CLEARED_32
#pragma ghs section rodata = "bsw_memif_bss"
#undef MEMMAP_ERROR

#elif defined MEMIF_STOP_SEC_VAR_CLEARED_32
#undef MEMIF_STOP_SEC_VAR_CLEARED_32
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMIF_START_SEC_APPL_DATA
#undef MEMIF_START_SEC_APPL_DATA

#elif defined MEMIF_STOP_SEC_APPL_DATA
#undef MEMIF_STOP_SEC_APPL_DATA

#elif defined MEMIF_START_SEC_APPL_CONST
#undef MEMIF_START_SEC_APPL_CONST

#elif defined MEMIF_STOP_SEC_APPL_CONST
#undef MEMIF_STOP_SEC_APPL_CONST

#elif defined MEMIF_START_SEC_APPL_CODE
#undef MEMIF_START_SEC_APPL_CODE

#elif defined MEMIF_STOP_SEC_APPL_CODE
#undef MEMIF_STOP_SEC_APPL_CODE

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
#error "MemIf_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
