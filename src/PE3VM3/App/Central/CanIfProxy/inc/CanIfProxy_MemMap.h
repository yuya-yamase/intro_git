/* CanIfProxy_MemMap_h_v1-0-0                                               */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CanIfProxy_MemMap/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#ifdef CANIFPROXY_MEMMAP_SUPPORT

#define MEMMAP_ERROR

/* CODE */
#if defined CANIFPROXY_START_SEC_CODE
#undef CANIFPROXY_START_SEC_CODE
#pragma ghs section text=".canifproxy_code"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_CODE
#undef CANIFPROXY_STOP_SEC_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

/* CALLOUT CODE */
#elif defined CANIFPROXY_START_SEC_CALLOUT_CODE
#undef CANIFPROXY_START_SEC_CALLOUT_CODE
#pragma ghs section text=".canifproxy_callout_code"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_CALLOUT_CODE
#undef CANIFPROXY_STOP_SEC_CALLOUT_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

/* CONFIG DATA Alignment:4byte */
#elif defined CANIFPROXY_START_SEC_CONFIG_DATA_32
#undef CANIFPROXY_START_SEC_CONFIG_DATA_32
#pragma ghs section rodata=".canifproxy_config_data_32"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_CONFIG_DATA_32
#undef CANIFPROXY_STOP_SEC_CONFIG_DATA_32
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

/* CONST */
#elif defined CANIFPROXY_START_SEC_CONST
#undef CANIFPROXY_START_SEC_CONST
#pragma ghs section rodata=".canifproxy_const"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_CONST
#undef CANIFPROXY_STOP_SEC_CONST
#pragma ghs section rodata= default
#undef MEMMAP_ERROR

/* VAR CLEARED Alignment:4byte */
#elif defined CANIFPROXY_START_SEC_VAR_CLEARED_32
#undef CANIFPROXY_START_SEC_VAR_CLEARED_32
#pragma ghs section bss=".canifproxy_var_cleared_32"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_VAR_CLEARED_32
#undef CANIFPROXY_STOP_SEC_VAR_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR SLOW CLEARED Alignment:4byte */
#elif defined CANIFPROXY_START_SEC_VAR_SLOW_CLEARED_32
#undef CANIFPROXY_START_SEC_VAR_SLOW_CLEARED_32
#pragma ghs section bss=".canifproxy_var_slow_cleared_32"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_VAR_SLOW_CLEARED_32
#undef CANIFPROXY_STOP_SEC_VAR_SLOW_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR POWER ON CLEARED Alignment:4byte */
#elif defined CANIFPROXY_START_SEC_VAR_POWER_ON_CLEARED_32
#undef CANIFPROXY_START_SEC_VAR_POWER_ON_CLEARED_32
#pragma ghs section bss=".canifproxy_var_power_on_cleared_32"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_VAR_POWER_ON_CLEARED_32
#undef CANIFPROXY_STOP_SEC_VAR_POWER_ON_CLEARED_32
#pragma ghs section bss=default
#undef MEMMAP_ERROR

/* VAR INIT Alignment:4byte */
#elif defined CANIFPROXY_START_SEC_VAR_INIT_32
#undef CANIFPROXY_START_SEC_VAR_INIT_32
#pragma ghs section data=".canifproxy_var_init_32"
#undef MEMMAP_ERROR

#elif defined CANIFPROXY_STOP_SEC_VAR_INIT_32
#undef CANIFPROXY_STOP_SEC_VAR_INIT_32
#pragma ghs section data=default
#undef MEMMAP_ERROR

#endif

/* Error Check */
#if defined MEMMAP_ERROR
#error "CanIfProxy_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */

#endif /* CANIFPROXY_MEMMAP_SUPPORT */

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
