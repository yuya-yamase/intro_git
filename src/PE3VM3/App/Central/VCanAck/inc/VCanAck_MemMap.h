/* VCanAck_MemMap_h_v1-0-0                                                  */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | VCanAck_MemMap/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#ifdef VCANACK_MEMMAP_SUPPORT

#define MEMMAP_ERROR

/* CODE */
#if defined VCANACK_START_SEC_CODE
#undef VCANACK_START_SEC_CODE
#pragma ghs section text=".vcanack_code"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_CODE
#undef VCANACK_STOP_SEC_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

/* CALLOUT CODE */
#elif defined VCANACK_START_SEC_CALLOUT_CODE
#undef VCANACK_START_SEC_CALLOUT_CODE
#pragma ghs section text=".vcanack_callout_code"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_CALLOUT_CODE
#undef VCANACK_STOP_SEC_CALLOUT_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

/* CONFIG DATA Alignment:4byte */
#elif defined VCANACK_START_SEC_CONFIG_DATA_32
#undef VCANACK_START_SEC_CONFIG_DATA_32
#pragma ghs section rodata=".vcanack_config_data_32"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_CONFIG_DATA_32
#undef VCANACK_STOP_SEC_CONFIG_DATA_32
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

/* CONST */
#elif defined VCANACK_START_SEC_CONST
#undef VCANACK_START_SEC_CONST
#pragma ghs section rodata=".vcanack_const"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_CONST
#undef VCANACK_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

/* VAR CLEARED Alignment:4byte */
#elif defined VCANACK_START_SEC_VAR_CLEARED_32
#undef VCANACK_START_SEC_VAR_CLEARED_32
#pragma ghs section bss=".vcanack_var_cleared_32"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_VAR_CLEARED_32
#undef VCANACK_STOP_SEC_VAR_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR SLOW CLEARED Alignment:4byte */
#elif defined VCANACK_START_SEC_VAR_SLOW_CLEARED_32
#undef VCANACK_START_SEC_VAR_SLOW_CLEARED_32
#pragma ghs section bss=".vcanack_var_slow_cleared_32"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_VAR_SLOW_CLEARED_32
#undef VCANACK_STOP_SEC_VAR_SLOW_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR POWER ON CLEARED Alignment:4byte */
#elif defined VCANACK_START_SEC_VAR_POWER_ON_CLEARED_32
#undef VCANACK_START_SEC_VAR_POWER_ON_CLEARED_32
#pragma ghs section bss=".vcanack_var_power_on_cleared_32"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_VAR_POWER_ON_CLEARED_32
#undef VCANACK_STOP_SEC_VAR_POWER_ON_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR INIT Alignment:4byte */
#elif defined VCANACK_START_SEC_VAR_INIT_32
#undef VCANACK_START_SEC_VAR_INIT_32
#pragma ghs section data=".vcanack_var_init_32"
#undef MEMMAP_ERROR

#elif defined VCANACK_STOP_SEC_VAR_INIT_32
#undef VCANACK_STOP_SEC_VAR_INIT_32
#pragma ghs section data=default
#undef MEMMAP_ERROR

#endif

/* Error Check */
#if defined MEMMAP_ERROR
#error "VCanAck_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */

#endif /* VCANACK_MEMMAP_SUPPORT */

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

/**** End of File ***********************************************************/
