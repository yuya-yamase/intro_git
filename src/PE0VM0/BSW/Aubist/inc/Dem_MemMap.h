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

#if defined DEM_START_SEC_CODE
#undef DEM_START_SEC_CODE
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CODE
#undef DEM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CODE
#undef Dem_START_SEC_CODE
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CODE
#undef Dem_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_CONST
#undef DEM_START_SEC_CONST
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CONST
#undef DEM_STOP_SEC_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CONST
#undef Dem_START_SEC_CONST
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CONST
#undef Dem_STOP_SEC_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_CONST_CONFIG
#undef DEM_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CONST_CONFIG
#undef DEM_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CONST_CONFIG
#undef Dem_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CONST_CONFIG
#undef Dem_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_VAR_NO_INIT
#undef DEM_START_SEC_VAR_NO_INIT
#pragma ghs section bss = ".bsw_dem_bss"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_VAR_NO_INIT
#undef DEM_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_VAR_NO_INIT
#undef Dem_START_SEC_VAR_NO_INIT
#pragma ghs section bss = ".bsw_dem_bss"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_VAR_NO_INIT
#undef Dem_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_VAR_SAVED_ZONE
#undef DEM_START_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = ".bsw_dem_bss"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_VAR_SAVED_ZONE
#undef DEM_STOP_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_VAR_SAVED_ZONE
#undef Dem_START_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = ".bsw_dem_bss"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_VAR_SAVED_ZONE
#undef Dem_STOP_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_CODE_CALLOUT
#undef DEM_START_SEC_CODE_CALLOUT
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CODE_CALLOUT
#undef DEM_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CODE_CALLOUT
#undef Dem_START_SEC_CODE_CALLOUT
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CODE_CALLOUT
#undef Dem_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_APPL_DATA
#undef DEM_START_SEC_APPL_DATA

#elif defined DEM_STOP_SEC_APPL_DATA
#undef DEM_STOP_SEC_APPL_DATA

#elif defined Dem_START_SEC_APPL_DATA
#undef Dem_START_SEC_APPL_DATA

#elif defined Dem_STOP_SEC_APPL_DATA
#undef Dem_STOP_SEC_APPL_DATA

#elif defined DEM_START_SEC_APPL_CONST
#undef DEM_START_SEC_APPL_CONST

#elif defined DEM_STOP_SEC_APPL_CONST
#undef DEM_STOP_SEC_APPL_CONST

#elif defined Dem_START_SEC_APPL_CONST
#undef Dem_START_SEC_APPL_CONST

#elif defined Dem_STOP_SEC_APPL_CONST
#undef Dem_STOP_SEC_APPL_CONST

#elif defined DEM_START_SEC_CODE_TRUST
#undef DEM_START_SEC_CODE_TRUST
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CODE_TRUST
#undef DEM_STOP_SEC_CODE_TRUST
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CODE_TRUST
#undef Dem_START_SEC_CODE_TRUST
#pragma ghs section text = ".bsw_dem_text"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CODE_TRUST
#undef Dem_STOP_SEC_CODE_TRUST
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_CODE_CALLOUT_TRUST
#undef DEM_START_SEC_CODE_CALLOUT_TRUST

#elif defined DEM_STOP_SEC_CODE_CALLOUT_TRUST
#undef DEM_STOP_SEC_CODE_CALLOUT_TRUST

#elif defined Dem_START_SEC_CODE_CALLOUT_TRUST
#undef Dem_START_SEC_CODE_CALLOUT_TRUST

#elif defined Dem_STOP_SEC_CODE_CALLOUT_TRUST
#undef Dem_STOP_SEC_CODE_CALLOUT_TRUST

#elif defined DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#undef DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#undef DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#undef Dem_START_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#undef Dem_STOP_SEC_CONST_PBCONFIG_DIRECTLY_EVENTPARAMETERATTRIBUTE
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#undef DEM_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#undef DEM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dem_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#undef Dem_START_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#pragma ghs section rodata = ".bsw_dem_rodata"
#undef MEMMAP_ERROR

#elif defined Dem_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#undef Dem_STOP_SEC_CONST_PBCONFIG_DIRECTLY_FAILURECYCLECOUNTERTHRESHOLD
#pragma ghs section rodata = default
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
#error "Dem_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
