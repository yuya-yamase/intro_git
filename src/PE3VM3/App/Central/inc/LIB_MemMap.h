/* ---------------------------------------------------------------------------- */
/* file name	:	LIB_MemMap.h												*/
/* file version	:																*/
/* ---------------------------------------------------------------------------- */
#if defined		LIB_START_SEC_CODE
#undef			LIB_START_SEC_CODE
#pragma	ghs section text = ".LIB_CODE"

#elif defined	LIB_STOP_SEC_CODE
#undef			LIB_STOP_SEC_CODE
#pragma	ghs section text = default

#elif defined	LIB_START_SEC_CONST
#undef			LIB_START_SEC_CONST
#pragma	ghs section rodata = ".LIB_CONST"

#elif defined	LIB_STOP_SEC_CONST
#undef			LIB_STOP_SEC_CONST
#pragma	ghs section rodata = default

#elif defined	LIB_START_SEC_CAL
#undef			LIB_START_SEC_CAL
#pragma	ghs section rodata = ".LIB_CAL"

#elif defined	LIB_STOP_SEC_CAL
#undef			LIB_STOP_SEC_CAL
#pragma	ghs section rodata = default

#elif defined	LIB_START_SEC_VAR
#undef			LIB_START_SEC_VAR
#pragma	ghs section bss = ".LIB_VAR"

#elif defined	LIB_STOP_SEC_VAR
#undef			LIB_STOP_SEC_VAR
#pragma	ghs section bss = default

#elif defined	LIB_START_SEC_NV_VAR
#undef			LIB_START_SEC_NV_VAR
#pragma	ghs section bss = ".LIB_NV_VAR"

#elif defined	LIB_STOP_SEC_NV_VAR
#undef			LIB_STOP_SEC_NV_VAR
#pragma	ghs section bss = default

#elif defined	LIB_START_SEC_BACKUP
#undef			LIB_START_SEC_BACKUP
#pragma	ghs section bss = ".LIB_BACKUP_VAR"

#elif defined	LIB_STOP_SEC_BACKUP
#undef			LIB_STOP_SEC_BACKUP

#else
#error			"LIB_MemMap.h, error"
#endif
/* - End Of File -------------------------------------------------------------- */
