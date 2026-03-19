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

#if defined CRYIF_START_SEC_CODE
#undef CRYIF_START_SEC_CODE
#pragma ghs section text=".bsw_cryif_code"
#undef MEMMAP_ERROR

#elif defined CRYIF_STOP_SEC_CODE
#undef CRYIF_STOP_SEC_CODE
#pragma ghs section text=default
#undef MEMMAP_ERROR

#elif defined CRYIF_START_SEC_APPL_DATA
#undef CRYIF_START_SEC_APPL_DATA

#elif defined CRYIF_STOP_SEC_APPL_DATA
#undef CRYIF_STOP_SEC_APPL_DATA

#elif defined CRYIF_START_SEC_SHARED_VAR_NO_INIT
#undef CRYIF_START_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss=".bsw_cryif_shared_var_no_init"
#undef MEMMAP_ERROR

#elif defined CRYIF_STOP_SEC_SHARED_VAR_NO_INIT
#undef CRYIF_STOP_SEC_SHARED_VAR_NO_INIT
#pragma ghs section bss=default
#undef MEMMAP_ERROR

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
#error "CryIf_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
