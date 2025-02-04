/* CmpDecmp_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CmpDecmp/MemMap/HEADER                                      */
/******************************************************************************/

#ifdef CMPDECMP_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_CMPDECMP"
 #else
 #pragma ghs section text = ".P_RAM_CMPDECMP"
 #endif
#undef CMPDECMP_START_SEC_CODE
#endif

#ifdef CMPDECMP_STOP_SEC_CODE
#pragma ghs section text = default
#undef CMPDECMP_STOP_SEC_CODE
#endif

#ifdef CMPDECMP_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_CMPDECMP"
#undef CMPDECMP_START_SEC_VAR
#endif

#ifdef CMPDECMP_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef CMPDECMP_STOP_SEC_VAR
#endif

#ifdef CMPDECMP_START_SEC_VAR_LARGE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_CMPDECMP_LARGE"
#undef CMPDECMP_START_SEC_VAR_LARGE
#endif

#ifdef CMPDECMP_STOP_SEC_VAR_LARGE
#pragma ghs section bss = default
#pragma ghs enddata
#undef CMPDECMP_STOP_SEC_VAR_LARGE
#endif

#ifdef CMPDECMP_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_CMPDECMP"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_CMPDECMP"
 #endif
#undef CMPDECMP_START_SEC_CST
#endif

#ifdef CMPDECMP_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef CMPDECMP_STOP_SEC_CST
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

