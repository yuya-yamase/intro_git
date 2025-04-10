#if defined PORT_START_SEC_VAR_NO_INIT_GLOBAL_PTR
#pragma ghs section bss=".PORT_BSS_VAR_NO_INIT"
#undef PORT_START_SEC_VAR_NO_INIT_GLOBAL_PTR
#undef MEMMAP_ERROR
#elif defined PORT_STOP_SEC_VAR_NO_INIT_GLOBAL_PTR
#pragma ghs section
#undef PORT_STOP_SEC_VAR_NO_INIT_GLOBAL_PTR
#undef MEMMAP_ERROR

#elif defined PORT_START_SEC_CONST_UNSPECIFIED
#pragma ghs section rodata=".PORT_RODATA_CONST"
#undef PORT_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined PORT_STOP_SEC_CONST_UNSPECIFIED
#pragma ghs section
#undef PORT_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined PORT_START_SEC_CODE_GLOBAL
#pragma ghs section text=".PORT_TEXT_CODE"
#undef PORT_START_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR
#elif defined PORT_STOP_SEC_CODE_GLOBAL
#pragma ghs section
#undef PORT_STOP_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR

#endif
