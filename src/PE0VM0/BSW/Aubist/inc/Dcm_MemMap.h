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

#if defined DCM_START_SEC_CODE
#undef DCM_START_SEC_CODE
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_CODE
#undef DCM_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_CODE
#undef Dcm_START_SEC_CODE
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_CODE
#undef Dcm_STOP_SEC_CODE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_CODE_CALLOUT
#undef DCM_START_SEC_CODE_CALLOUT
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_CODE_CALLOUT
#undef DCM_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_CODE_CALLOUT
#undef Dcm_START_SEC_CODE_CALLOUT
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_CODE_CALLOUT
#undef Dcm_STOP_SEC_CODE_CALLOUT
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_CONST
#undef DCM_START_SEC_CONST
#pragma ghs section rodata = ".bsw_dcm_rodata"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_CONST
#undef DCM_STOP_SEC_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_CONST
#undef Dcm_START_SEC_CONST
#pragma ghs section rodata = ".bsw_dcm_rodata"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_CONST
#undef Dcm_STOP_SEC_CONST
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_VAR_NO_INIT
#undef DCM_START_SEC_VAR_NO_INIT
#pragma ghs section bss = ".bsw_dcm_bss"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_VAR_NO_INIT
#undef DCM_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_VAR_NO_INIT
#undef Dcm_START_SEC_VAR_NO_INIT
#pragma ghs section bss = ".bsw_dcm_bss"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_VAR_NO_INIT
#undef Dcm_STOP_SEC_VAR_NO_INIT
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_CONST_CONFIG
#undef DCM_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_dcm_rodata"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_CONST_CONFIG
#undef DCM_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_CONST_CONFIG
#undef Dcm_START_SEC_CONST_CONFIG
#pragma ghs section rodata = ".bsw_dcm_rodata"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_CONST_CONFIG
#undef Dcm_STOP_SEC_CONST_CONFIG
#pragma ghs section rodata = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_CODE_SHARE
#undef DCM_START_SEC_CODE_SHARE
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_CODE_SHARE
#undef DCM_STOP_SEC_CODE_SHARE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_CODE_SHARE
#undef Dcm_START_SEC_CODE_SHARE
#pragma ghs section text = ".bsw_dcm_text"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_CODE_SHARE
#undef Dcm_STOP_SEC_CODE_SHARE
#pragma ghs section text = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_VAR_SAVED_ZONE
#undef DCM_START_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = ".bsw_dcm_bss"
#undef MEMMAP_ERROR

#elif defined DCM_STOP_SEC_VAR_SAVED_ZONE
#undef DCM_STOP_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined Dcm_START_SEC_VAR_SAVED_ZONE
#undef Dcm_START_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = ".bsw_dcm_bss"
#undef MEMMAP_ERROR

#elif defined Dcm_STOP_SEC_VAR_SAVED_ZONE
#undef Dcm_STOP_SEC_VAR_SAVED_ZONE
#pragma ghs section bss = default
#undef MEMMAP_ERROR

#elif defined DCM_START_SEC_APPL_DATA
#undef DCM_START_SEC_APPL_DATA

#elif defined DCM_STOP_SEC_APPL_DATA
#undef DCM_STOP_SEC_APPL_DATA

#elif defined Dcm_START_SEC_APPL_DATA
#undef Dcm_START_SEC_APPL_DATA

#elif defined Dcm_STOP_SEC_APPL_DATA
#undef Dcm_STOP_SEC_APPL_DATA

#elif defined DCM_START_SEC_APPL_CONST
#undef DCM_START_SEC_APPL_CONST

#elif defined DCM_STOP_SEC_APPL_CONST
#undef DCM_STOP_SEC_APPL_CONST

#elif defined Dcm_START_SEC_APPL_CONST
#undef Dcm_START_SEC_APPL_CONST

#elif defined Dcm_STOP_SEC_APPL_CONST
#undef Dcm_STOP_SEC_APPL_CONST

#elif defined DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#undef DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01

#elif defined DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#undef DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01

#elif defined Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#undef Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01

#elif defined Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01
#undef Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE01

#elif defined DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#undef DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02

#elif defined DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#undef DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02

#elif defined Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#undef Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02

#elif defined Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02
#undef Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02

#elif defined DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#undef DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD

#elif defined DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#undef DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD

#elif defined Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#undef Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD

#elif defined Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD
#undef Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTPIDSERVICE02NOFFD

#elif defined DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#undef DCM_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE

#elif defined DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#undef DCM_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE

#elif defined Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#undef Dcm_START_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE

#elif defined Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE
#undef Dcm_STOP_SEC_CONST_PBCONFIG_DIRECTLY_SUPPORTVEHINFOINFOTYPE

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
#error "Dcm_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
