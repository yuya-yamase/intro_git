#if defined MCU_START_SEC_VAR_NO_INIT_GLOBAL_32
#pragma ghs section bss=".MCU_BSS_VAR_NO_INIT"
#undef MCU_START_SEC_VAR_NO_INIT_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined MCU_STOP_SEC_VAR_NO_INIT_GLOBAL_32
#pragma ghs section
#undef MCU_STOP_SEC_VAR_NO_INIT_GLOBAL_32
#undef MEMMAP_ERROR

#elif defined MCU_START_SEC_CONST_UNSPECIFIED
#pragma ghs section rodata=".MCU_RODATA_CONST"
#undef MCU_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined MCU_STOP_SEC_CONST_UNSPECIFIED
#pragma ghs section
#undef MCU_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined MCU_START_SEC_CODE_GLOBAL
#pragma ghs section text=".MCU_TEXT_CODE"
#undef MCU_START_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR
#elif defined MCU_STOP_SEC_CODE_GLOBAL
#pragma ghs section
#undef MCU_STOP_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR

#endif
