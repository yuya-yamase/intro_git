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

#if defined MEMACC_START_SEC_CODE
#undef MEMACC_START_SEC_CODE
#pragma ghs section text = ".bsw_memacc_text"
#undef MEMMAP_ERROR

#elif defined MEMACC_STOP_SEC_CODE
#undef MEMACC_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMACC_PROXY_START_SEC_CODE
#undef MEMACC_PROXY_START_SEC_CODE
#pragma ghs section text = ".bsw_memacc_text"
#undef MEMMAP_ERROR

#elif defined MEMACC_PROXY_STOP_SEC_CODE
#undef MEMACC_PROXY_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined MEMACC_START_SEC_CONST_32
#undef MEMACC_START_SEC_CONST_32
#pragma ghs section rodata = ".bsw_memacc_rodata"
#undef MEMMAP_ERROR

#elif defined MEMACC_STOP_SEC_CONST_32
#undef MEMACC_STOP_SEC_CONST_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined MEMACC_START_SEC_CONST_CONFIG_32
#undef MEMACC_START_SEC_CONST_CONFIG_32
#pragma ghs section rodata = ".bsw_memacc_rodata"
#undef MEMMAP_ERROR

#elif defined MEMACC_STOP_SEC_CONST_CONFIG_32
#undef MEMACC_STOP_SEC_CONST_CONFIG_32
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined MEMACC_START_SEC_VAR_NO_INIT_32
#undef MEMACC_START_SEC_VAR_NO_INIT_32
#pragma ghs section bss = ".bsw_memacc_bss"
#undef MEMMAP_ERROR

#elif defined MEMACC_STOP_SEC_VAR_NO_INIT_32
#undef MEMACC_STOP_SEC_VAR_NO_INIT_32
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined MEMACC_START_SEC_VAR_NO_INIT_SHARE
#undef MEMACC_START_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = ".bsw_memacc_bss"
#undef MEMMAP_ERROR

#elif defined MEMACC_STOP_SEC_VAR_NO_INIT_SHARE
#undef MEMACC_STOP_SEC_VAR_NO_INIT_SHARE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined MEMACC_START_SEC_APPL_DATA
#undef MEMACC_START_SEC_APPL_DATA

#elif defined MEMACC_STOP_SEC_APPL_DATA
#undef MEMACC_STOP_SEC_APPL_DATA

#elif defined MEMACC_START_SEC_APPL_CONST
#undef MEMACC_START_SEC_APPL_CONST

#elif defined MEMACC_STOP_SEC_APPL_CONST
#undef MEMACC_STOP_SEC_APPL_CONST

#elif defined MEMACC_START_SEC_APPL_CODE
#undef MEMACC_START_SEC_APPL_CODE

#elif defined MEMACC_STOP_SEC_APPL_CODE
#undef MEMACC_STOP_SEC_APPL_CODE

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
#error "MemAcc_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
