/* MemMap_h_v2-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemMap/HEADER                                             */
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

#if defined MEM_START_SEC_CODE
#undef MEM_START_SEC_CODE
#pragma ghs section text = ".P_OTA_CODEFLS"
#undef MEMMAP_ERROR

#elif defined MEM_STOP_SEC_CODE
#undef MEM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEM_START_SEC_CODE_FAR
#undef MEM_START_SEC_CODE_FAR
#pragma ghs section text = ".P_OTA_CODEFLS"
#undef MEMMAP_ERROR

#elif defined MEM_STOP_SEC_CODE_FAR
#undef MEM_STOP_SEC_CODE_FAR
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEM_START_SEC_CONST_32
#undef MEM_START_SEC_CONST_32
#pragma ghs section rodata = ".C_OTA_CODEFLS"
#undef MEMMAP_ERROR

#elif defined MEM_STOP_SEC_CONST_32
#undef MEM_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined MEM_START_SEC_CONST_CONFIG_32
#undef MEM_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = ".C_OTA_CODEFLS"
#undef MEMMAP_ERROR

#elif defined MEM_STOP_SEC_CONST_CONFIG_32
#undef MEM_STOP_SEC_CONST_CONFIG_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined MEM_START_SEC_VAR_NO_INIT_32
#undef MEM_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = ".B_OTA_CODEFLS"
#undef MEMMAP_ERROR

#elif defined MEM_STOP_SEC_VAR_NO_INIT_32
#undef MEM_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined MEM_START_SEC_APPL_CODE
#undef MEM_START_SEC_APPL_CODE

#elif defined MEM_STOP_SEC_APPL_CODE
#undef MEM_STOP_SEC_APPL_CODE

#elif defined MEM_START_SEC_APPL_DATA
#undef MEM_START_SEC_APPL_DATA

#elif defined MEM_STOP_SEC_APPL_DATA
#undef MEM_STOP_SEC_APPL_DATA

#elif defined MEM_START_SEC_APPL_CONST
#undef MEM_START_SEC_APPL_CONST

#elif defined MEM_STOP_SEC_APPL_CONST
#undef MEM_STOP_SEC_APPL_CONST

#endif


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


#if defined MEMMAP_ERROR
#error "Mem_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
