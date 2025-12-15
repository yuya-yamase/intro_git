#if 0
#define MEMMAP_ERROR
#if defined ETHSWT_START_SEC_CODE
#undef ETHSWT_START_SEC_CODE
#pragma ghs section text=".ETHSWT_CODE"
#pragma ghs section rodata=".ETHSWT_CONST"
#pragma ghs section data=".ETHSWT_DATA"
#undef MEMMAP_ERROR
#elif defined ETHSWT_STOP_SEC_CODE
#undef ETHSWT_STOP_SEC_CODE
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section data=default
#undef MEMMAP_ERROR
#elif defined ETHSWT_START_SEC_VAR_CLEARED
#undef ETHSWT_START_SEC_VAR_CLEARED
#pragma ghs section bss=".ETHSWT_BSS"
#undef MEMMAP_ERROR
#elif defined ETHSWT_STOP_SEC_VAR_CLEARED
#undef ETHSWT_STOP_SEC_VAR_CLEARED
#pragma ghs section bss=default
#undef MEMMAP_ERROR
#elif defined ETHSWT_START_SEC_CONST
#undef ETHSWT_START_SEC_CONST
#pragma ghs section rodata=".ETHSWT_CONST"
#pragma ghs section data=".ETHSWT_DATA"
#undef MEMMAP_ERROR
#elif defined ETHSWT_STOP_SEC_CONST
#undef ETHSWT_STOP_SEC_CONST
#pragma ghs section rodata=default
#pragma ghs section data=default
#undef MEMMAP_ERROR
#elif defined ETHSWT_START_SEC_RRAM
#undef ETHSWT_START_SEC_RRAM
#pragma ghs section bss=".ETHSWT_RRAM"
#undef MEMMAP_ERROR
#elif defined ETHSWT_STOP_SEC_RRAM
#undef ETHSWT_STOP_SEC_RRAM
#pragma ghs section bss=default
#undef MEMMAP_ERROR
#elif defined ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#undef ETHSWT_START_SEC_CONFIG_DATA_PREBUILD
#pragma ghs section rodata=".ETHSWT_CONST"
#pragma ghs section data=".ETHSWT_DATA"
#undef MEMMAP_ERROR
#elif defined ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#undef ETHSWT_STOP_SEC_CONFIG_DATA_PREBUILD
#pragma ghs section rodata=default
#pragma ghs section data=default
#undef MEMMAP_ERROR

#endif
#endif
