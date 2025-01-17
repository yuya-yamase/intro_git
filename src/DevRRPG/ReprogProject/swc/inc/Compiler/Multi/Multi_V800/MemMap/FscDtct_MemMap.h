/* FscDtct_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | FscDtct/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef FSCDTCT_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_FSCDTCT"
 #else
 #pragma ghs section text = ".P_RAM_FSCDTCT"
 #endif
#undef FSCDTCT_START_SEC_CODE
#endif

#ifdef FSCDTCT_STOP_SEC_CODE
#pragma ghs section text = default
#undef FSCDTCT_STOP_SEC_CODE
#endif

#ifdef FSCDTCT_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_FSCDTCT"
#undef FSCDTCT_START_SEC_VAR
#endif

#ifdef FSCDTCT_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef FSCDTCT_STOP_SEC_VAR
#endif

#ifdef FSCDTCT_START_SEC_VAR_SIG_TARGET
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_FSCDTCT_SIGTARGET_SHARED"
#undef FSCDTCT_START_SEC_VAR_SIG_TARGET
#endif

#ifdef FSCDTCT_STOP_SEC_VAR_SIG_TARGET
#pragma ghs section bss = default
#pragma ghs enddata
#undef FSCDTCT_STOP_SEC_VAR_SIG_TARGET
#endif

#ifdef FSCDTCT_START_SEC_VAR_SIG_DATA
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_FSCDTCT_SIGDATA_SHARED"
#undef FSCDTCT_START_SEC_VAR_SIG_DATA
#endif

#ifdef FSCDTCT_STOP_SEC_VAR_SIG_DATA
#pragma ghs section bss = default
#pragma ghs enddata
#undef FSCDTCT_STOP_SEC_VAR_SIG_DATA
#endif

#ifdef FSCDTCT_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_FSCDTCT"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_FSCDTCT"
 #endif
#undef FSCDTCT_START_SEC_CST
#endif

#ifdef FSCDTCT_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef FSCDTCT_STOP_SEC_CST
#endif

#ifdef FSCDTCT_START_SEC_CST_KEY
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_FSCDTCT_KEY"
#undef FSCDTCT_START_SEC_CST_KEY
#endif

#ifdef FSCDTCT_STOP_SEC_CST_KEY
#pragma ghs section rodata = default
#pragma ghs enddata
#undef FSCDTCT_STOP_SEC_CST_KEY
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

