#if defined DMA_START_SEC_TEXT_CODE
#pragma ghs section text=".DMA_TEXT_CODE"
#undef DMA_START_SEC_TEXT_CODE
#undef MEMMAP_ERROR
#elif defined DMA_STOP_SEC_TEXT_CODE
#pragma ghs section
#undef DMA_STOP_SEC_TEXT_CODE
#undef MEMMAP_ERROR

#elif defined DMA_START_SEC_RODATA_CONST
#pragma ghs section rodata=".DMA_RODATA_CONST"
#undef DMA_START_SEC_RODATA_CONST
#undef MEMMAP_ERROR
#elif defined DMA_STOP_SEC_RODATA_CONST
#pragma ghs section
#undef DMA_STOP_SEC_RODATA_CONST
#undef MEMMAP_ERROR

#elif defined DMA_START_SEC_BSS_VAR_NO_INIT
#pragma ghs section bss=".DMA_BSS_VAR_NO_INIT"
#undef DMA_START_SEC_BSS_VAR_NO_INIT
#undef MEMMAP_ERROR
#elif defined DMA_STOP_SEC_BSS_VAR_NO_INIT
#pragma ghs section
#undef DMA_STOP_SEC_BSS_VAR_NO_INIT
#undef MEMMAP_ERROR

#endif
