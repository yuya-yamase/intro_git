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

#if defined CRYPTO_83_sw_START_SEC_CODE
#undef CRYPTO_83_sw_START_SEC_CODE
#pragma ghs section text = ".P_ROM_CRYPTO"
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_STOP_SEC_CODE
#undef CRYPTO_83_sw_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_START_SEC_CONST
#undef CRYPTO_83_sw_START_SEC_CONST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_CRYPTO"
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_STOP_SEC_CONST
#undef CRYPTO_83_sw_STOP_SEC_CONST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_START_SEC_CONST_CONFIG
#undef CRYPTO_83_sw_START_SEC_CONST_CONFIG
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_CRYPTO"
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_STOP_SEC_CONST_CONFIG
#undef CRYPTO_83_sw_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#pragma ghs enddata
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#undef CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_CRYPTO"
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#undef CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss = default
#pragma ghs enddata
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_START_SEC_VAR_CLEARED_WAKEUP
#undef CRYPTO_83_sw_START_SEC_VAR_CLEARED_WAKEUP
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_CRYPTO"
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_STOP_SEC_VAR_CLEARED_WAKEUP
#undef CRYPTO_83_sw_STOP_SEC_VAR_CLEARED_WAKEUP
#pragma ghs section bss = default
#pragma ghs enddata
#undef MEMMAP_ERROR

#elif defined CRYPTO_83_sw_START_SEC_APPL_CODE
#undef CRYPTO_83_sw_START_SEC_APPL_CODE

#elif defined CRYPTO_83_sw_STOP_SEC_APPL_CODE
#undef CRYPTO_83_sw_STOP_SEC_APPL_CODE

#elif defined CRYPTO_83_sw_START_SEC_APPL_DATA
#undef CRYPTO_83_sw_START_SEC_APPL_DATA

#elif defined CRYPTO_83_sw_STOP_SEC_APPL_DATA
#undef CRYPTO_83_sw_STOP_SEC_APPL_DATA

#elif defined CRYPTO_83_sw_START_SEC_CONFIG_DATA
#undef CRYPTO_83_sw_START_SEC_CONFIG_DATA

#elif defined CRYPTO_83_sw_STOP_SEC_CONFIG_DATA
#undef CRYPTO_83_sw_STOP_SEC_CONFIG_DATA

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
#error "Crypto_83_sw_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
