/* DiagSrv_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef DIAGSRV_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_DIAGSRV"
 #else
 #pragma ghs section text = ".P_RAM_DIAGSRV"
 #endif
#undef DIAGSRV_START_SEC_CODE
#endif

#ifdef DIAGSRV_STOP_SEC_CODE
#pragma ghs section text = default
#undef DIAGSRV_STOP_SEC_CODE
#endif

#ifdef DIAGSRV_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_DIAGSRV"
#undef DIAGSRV_START_SEC_VAR
#endif

#ifdef DIAGSRV_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef DIAGSRV_STOP_SEC_VAR
#endif

#ifdef DIAGSRV_START_SEC_VAR_SEED
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DIAGSRV_SEED_SHARED"
#undef DIAGSRV_START_SEC_VAR_SEED
#endif

#ifdef DIAGSRV_STOP_SEC_VAR_SEED
#pragma ghs section bss = default
#pragma ghs enddata
#undef DIAGSRV_STOP_SEC_VAR_SEED
#endif

#ifdef DIAGSRV_START_SEC_VAR_KEY
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DIAGSRV_KEY_SHARED"
#undef DIAGSRV_START_SEC_VAR_KEY
#endif

#ifdef DIAGSRV_STOP_SEC_VAR_KEY
#pragma ghs section bss = default
#pragma ghs enddata
#undef DIAGSRV_STOP_SEC_VAR_KEY
#endif

#ifdef DIAGSRV_START_SEC_VAR_NONCE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DIAGSRV_NONCE_SHARED"
#undef DIAGSRV_START_SEC_VAR_NONCE
#endif

#ifdef DIAGSRV_STOP_SEC_VAR_NONCE
#pragma ghs section bss = default
#pragma ghs enddata
#undef DIAGSRV_STOP_SEC_VAR_NONCE
#endif

#ifdef DIAGSRV_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_DIAGSRV"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_DIAGSRV"
 #endif
#undef DIAGSRV_START_SEC_CST
#endif

#ifdef DIAGSRV_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef DIAGSRV_STOP_SEC_CST
#endif

#ifdef DIAGSRV_START_SEC_CST_ENCRYPTION_FLAG
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_DIAGSRV_ENCRYPTION_FLAG"
#undef DIAGSRV_START_SEC_CST_ENCRYPTION_FLAG
#endif

#ifdef DIAGSRV_STOP_SEC_CST_ENCRYPTION_FLAG
#pragma ghs section rodata = default
#pragma ghs enddata
#undef DIAGSRV_STOP_SEC_CST_ENCRYPTION_FLAG
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

