/************************************************************************************************/
/* file Name        : VIS_MemMap.h                                                              */
/* contents         : External header                                                           */
/* maker            : NCOS                                                                      */
/* change history   :                                                                           */
/* ---------------------------------------------------------------------------------------------*/
/* ver   | Comments                                                                             */
/* ---------------------------------------------------------------------------------------------*/
/* v1.00 | New created                                                                          */
/************************************************************************************************/

#if defined		VIS_START_SEC_CODE
#undef			VIS_START_SEC_CODE
#pragma	ghs section text = ".VIS_CODE"

#elif defined	VIS_STOP_SEC_CODE
#undef			VIS_STOP_SEC_CODE
#pragma	ghs section text = default

#elif defined	VIS_START_SEC_CONST
#undef			VIS_START_SEC_CONST
#pragma	ghs section rodata = ".VIS_CONST"

#elif defined	VIS_STOP_SEC_CONST
#undef			VIS_STOP_SEC_CONST
#pragma	ghs section rodata = default

#elif defined	VIS_START_SEC_VAR
#undef			VIS_START_SEC_VAR
#pragma	ghs section bss = ".VIS_VAR"

#elif defined	VIS_STOP_SEC_VAR
#undef			VIS_STOP_SEC_VAR
#pragma	ghs section bss = default

#else
#error			"VIS_MemMap.h, error"
#endif
/* - End Of File -------------------------------------------------------------- */
