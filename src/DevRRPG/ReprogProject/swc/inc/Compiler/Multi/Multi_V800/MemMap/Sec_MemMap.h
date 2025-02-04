/* Sec_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef SEC_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_SEC"
 #else
 #pragma ghs section text = ".P_RAM_SEC"
 #endif
#undef SEC_START_SEC_CODE
#endif

#ifdef SEC_STOP_SEC_CODE
#pragma ghs section text = default
#undef SEC_STOP_SEC_CODE
#endif

#ifdef SEC_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_SEC"
#undef SEC_START_SEC_VAR
#endif

#ifdef SEC_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef SEC_STOP_SEC_VAR
#endif

#ifdef SEC_START_SEC_VAR_RANDOMSEED
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_SEC_RANDOMSEED_SHARED"
#undef SEC_START_SEC_VAR_RANDOMSEED
#endif

#ifdef SEC_STOP_SEC_VAR_RANDOMSEED
#pragma ghs section bss = default
#pragma ghs enddata
#undef SEC_STOP_SEC_VAR_RANDOMSEED
#endif

#ifdef SEC_START_SEC_VAR_RANDOM_SIZE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_SEC_RANDOMSIZE_SHARED"
#undef SEC_START_SEC_VAR_RANDOM_SIZE
#endif

#ifdef SEC_STOP_SEC_VAR_RANDOM_SIZE
#pragma ghs section bss = default
#pragma ghs enddata
#undef SEC_STOP_SEC_VAR_RANDOM_SIZE
#endif

#ifdef SEC_START_SEC_VAR_ENCRYPT_SIZE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_SEC_ENCRYPTSIZE_SHARED"
#undef SEC_START_SEC_VAR_ENCRYPT_SIZE
#endif

#ifdef SEC_STOP_SEC_VAR_ENCRYPT_SIZE
#pragma ghs section bss = default
#pragma ghs enddata
#undef SEC_STOP_SEC_VAR_ENCRYPT_SIZE
#endif

#ifdef SEC_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_SEC"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_SEC"
 #endif
#undef SEC_START_SEC_CST
#endif

#ifdef SEC_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef SEC_STOP_SEC_CST
#endif

#ifdef SEC_START_SEC_CST_KEY
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_SEC_KEY"
#undef SEC_START_SEC_CST_KEY
#endif

#ifdef SEC_STOP_SEC_CST_KEY
#pragma ghs section rodata = default
#pragma ghs enddata
#undef SEC_STOP_SEC_CST_KEY
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

