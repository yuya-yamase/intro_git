/* ADCDIAG-r04-303 */
#if defined ADCDIAG_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#pragma ghs section bss=".ADCDIAG_BSS_VAR_NO_INIT"
#undef ADCDIAG_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#pragma ghs section
#undef ADCDIAG_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CONST_8
#pragma ghs section rodata=".ADCDIAG_RODATA_CONST"
#undef ADCDIAG_START_SEC_CONST_8
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CONST_8
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CONST_8
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CONST_16
#pragma ghs section rodata=".ADCDIAG_RODATA_CONST"
#undef ADCDIAG_START_SEC_CONST_16
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CONST_16
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CONST_16
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CONST_32
#pragma ghs section rodata=".ADCDIAG_RODATA_CONST"
#undef ADCDIAG_START_SEC_CONST_32
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CONST_32
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CONST_32
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CONST_PTR
#pragma ghs section rodata=".ADCDIAG_RODATA_CONST"
#undef ADCDIAG_START_SEC_CONST_PTR
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CONST_PTR
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CONST_PTR
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CONST_UNSPECIFIED
#pragma ghs section rodata=".ADCDIAG_RODATA_CONST"
#undef ADCDIAG_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CONST_UNSPECIFIED
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CODE_GLOBAL
#pragma ghs section text=".ADCDIAG_TEXT_CODE"
#undef ADCDIAG_START_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CODE_GLOBAL
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR

#elif defined ADCDIAG_START_SEC_CODE_FAST_GLOBAL
#pragma ghs section text=".ADCDIAG_TEXT_CODE_FAST"
#undef ADCDIAG_START_SEC_CODE_FAST_GLOBAL
#undef MEMMAP_ERROR
#elif defined ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#pragma ghs section
#undef ADCDIAG_STOP_SEC_CODE_FAST_GLOBAL
#undef MEMMAP_ERROR

#endif
