#if defined DIO_START_SEC_CONST_UNSPECIFIED
#pragma ghs section rodata=".DIO_RODATA_CONST"
#undef DIO_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined DIO_STOP_SEC_CONST_UNSPECIFIED
#pragma ghs section
#undef DIO_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined DIO_START_SEC_CODE_GLOBAL
#pragma ghs section text=".DIO_TEXT_CODE"
#undef DIO_START_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR
#elif defined DIO_STOP_SEC_CODE_GLOBAL
#pragma ghs section
#undef DIO_STOP_SEC_CODE_GLOBAL
#undef MEMMAP_ERROR

#endif
