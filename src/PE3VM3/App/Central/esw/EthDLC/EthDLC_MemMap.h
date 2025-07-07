#if 0
/* -------------------------------------------------------------------------- */
/* file name	:	EthDLC_MemMap.h                                           */
/* -------------------------------------------------------------------------- */
#if defined		EthDLC_START_SEC_CODE
#undef			EthDLC_START_SEC_CODE
#pragma			clang section text   = ".EthSW_EthDLC_CODE"
#elif defined	EthDLC_STOP_SEC_CODE
#undef			EthDLC_STOP_SEC_CODE
#pragma			clang section text = ""
/* -------------------------------------------------------------------------- */
#elif defined	EthDLC_START_SEC_CONST
#undef			EthDLC_START_SEC_CONST
#pragma			clang section rodata = ".EthSW_EthDLC_CONST"
#elif defined	EthDLC_STOP_SEC_CONST
#undef			EthDLC_STOP_SEC_CONST
#pragma			clang section rodata = ""
/* -------------------------------------------------------------------------- */
#elif defined	EthDLC_START_SEC_CAL
#undef			EthDLC_START_SEC_CAL
#pragma			clang section rodata = ".EthSW_EthDLC_CAL"
#elif defined	EthDLC_STOP_SEC_CAL
#undef			EthDLC_STOP_SEC_CAL
#pragma			clang section rodata = ""
/* -------------------------------------------------------------------------- */
#elif defined	EthDLC_START_SEC_VAR
#undef			EthDLC_START_SEC_VAR
#pragma			clang section bss    = ".EthSW_EthDLC_VAR"
#elif defined	EthDLC_STOP_SEC_VAR
#undef			EthDLC_STOP_SEC_VAR
#pragma			clang section bss    = ""
/* -------------------------------------------------------------------------- */
#elif defined	EthDLC_START_SEC_NV_VAR
#undef			EthDLC_START_SEC_NV_VAR
#pragma			clang section bss    = ".EthSW_EthDLC_NVVAR"
#elif defined	EthDLC_STOP_SEC_NV_VAR
#undef			EthDLC_STOP_SEC_NV_VAR
#pragma			clang section bss    = ""
/* -------------------------------------------------------------------------- */
#else
#error			"EthDLC_MemMap.h, error"
#endif
/* - End Of File ------------------------------------------------------------ */
#endif
