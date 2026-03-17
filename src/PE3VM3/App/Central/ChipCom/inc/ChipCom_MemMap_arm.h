/* ChipCom_MemMap_h_v1-0-0                                                  */
/****************************************************************************/
/* Copyright (C) 2025 Denso Co.,Ltd. All rights reserved.                   */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | ChipCom_MemMap/HEADER                                     */
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

/* CODE */
#if defined CHIPCOM_START_SEC_CODE
#undef CHIPCOM_START_SEC_CODE
#pragma clang section text=".chipcom_code"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_CODE
#undef CHIPCOM_STOP_SEC_CODE
#pragma clang section text=""
#undef MEMMAP_ERROR

/* CALLOUT CODE */
#elif defined CHIPCOM_START_SEC_CALLOUT_CODE
#undef CHIPCOM_START_SEC_CALLOUT_CODE
#pragma clang section text=".chipcom_callout_code"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_CALLOUT_CODE
#undef CHIPCOM_STOP_SEC_CALLOUT_CODE
#pragma clang section text=""
#undef MEMMAP_ERROR

/* CONFIG DATA Alignment:4byte */
#elif defined CHIPCOM_START_SEC_CONFIG_DATA_32
#undef CHIPCOM_START_SEC_CONFIG_DATA_32
#pragma clang section rodata=".chipcom_config_data_32"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_CONFIG_DATA_32
#undef CHIPCOM_STOP_SEC_CONFIG_DATA_32
#pragma clang section rodata= ""
#undef MEMMAP_ERROR

/* CONST */
#elif defined CHIPCOM_START_SEC_CONST
#undef CHIPCOM_START_SEC_CONST
#pragma clang section rodata=".chipcom_const"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_CONST
#undef CHIPCOM_STOP_SEC_CONST
#pragma clang section rodata= ""
#undef MEMMAP_ERROR

/* VAR CLEARED Alignment:4byte */
#elif defined CHIPCOM_START_SEC_VAR_CLEARED_32
#undef CHIPCOM_START_SEC_VAR_CLEARED_32
#pragma clang section bss=".chipcom_var_cleared_32"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_VAR_CLEARED_32
#undef CHIPCOM_STOP_SEC_VAR_CLEARED_32
#pragma clang section bss=""
#undef MEMMAP_ERROR

/* VAR SLOW CLEARED Alignment:4byte */
#elif defined CHIPCOM_START_SEC_VAR_SLOW_CLEARED_32
#undef CHIPCOM_START_SEC_VAR_SLOW_CLEARED_32
#pragma clang section bss=".chipcom_var_slow_cleared_32"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_VAR_SLOW_CLEARED_32
#undef CHIPCOM_STOP_SEC_VAR_SLOW_CLEARED_32
#pragma clang section bss=""
#undef MEMMAP_ERROR

/* VAR POWER ON CLEARED Alignment:4byte */
#elif defined CHIPCOM_START_SEC_VAR_POWER_ON_CLEARED_32
#undef CHIPCOM_START_SEC_VAR_POWER_ON_CLEARED_32
#pragma clang section bss=".chipcom_var_power_on_cleared_32"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_VAR_POWER_ON_CLEARED_32
#undef CHIPCOM_STOP_SEC_VAR_POWER_ON_CLEARED_32
#pragma clang section bss=""
#undef MEMMAP_ERROR

/* VAR INIT Alignment:4byte */
#elif defined CHIPCOM_START_SEC_VAR_INIT_32
#undef CHIPCOM_START_SEC_VAR_INIT_32
#pragma clang section data=".chipcom_var_init_32"
#undef MEMMAP_ERROR

#elif defined CHIPCOM_STOP_SEC_VAR_INIT_32
#undef CHIPCOM_STOP_SEC_VAR_INIT_32
#pragma clang section data=""
#undef MEMMAP_ERROR

#endif

/* Error Check */
#if defined MEMMAP_ERROR
#error "ChipCom_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */

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
