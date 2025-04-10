/* Decrypt_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Decrypt/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef DECRYPT_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_DECRYPT"
 #else
 #pragma ghs section text = ".P_RAM_DECRYPT"
 #endif
#undef DECRYPT_START_SEC_CODE
#endif

#ifdef DECRYPT_STOP_SEC_CODE
#pragma ghs section text = default
#undef DECRYPT_STOP_SEC_CODE
#endif

#ifdef DECRYPT_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_DECRYPT"
#undef DECRYPT_START_SEC_VAR
#endif

#ifdef DECRYPT_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef DECRYPT_STOP_SEC_VAR
#endif

#ifdef DECRYPT_START_SEC_VAR_CIPHERTEXT
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DECRYPT_CIPHER_SHARED"
#undef DECRYPT_START_SEC_VAR_CIPHERTEXT
#endif

#ifdef DECRYPT_STOP_SEC_VAR_CIPHERTEXT
#pragma ghs section bss = default
#pragma ghs enddata
#undef DECRYPT_STOP_SEC_VAR_CIPHERTEXT
#endif

#ifdef DECRYPT_START_SEC_VAR_PLAINTEXT
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DECRYPT_PLAIN_SHARED"
#undef DECRYPT_START_SEC_VAR_PLAINTEXT
#endif

#ifdef DECRYPT_STOP_SEC_VAR_PLAINTEXT
#pragma ghs section bss = default
#pragma ghs enddata
#undef DECRYPT_STOP_SEC_VAR_PLAINTEXT
#endif

#ifdef DECRYPT_START_SEC_VAR_PLAINTEXTSIZE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_DECRYPT_PLAINSIZE_SHARED"
#undef DECRYPT_START_SEC_VAR_PLAINTEXTSIZE
#endif

#ifdef DECRYPT_STOP_SEC_VAR_PLAINTEXTSIZE
#pragma ghs section bss = default
#pragma ghs enddata
#undef DECRYPT_STOP_SEC_VAR_PLAINTEXTSIZE
#endif

#ifdef DECRYPT_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_DECRYPT"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_DECRYPT"
 #endif
#undef DECRYPT_START_SEC_CST
#endif

#ifdef DECRYPT_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef DECRYPT_STOP_SEC_CST
#endif

#ifdef DECRYPT_START_SEC_CST_KEY
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_DECRYPT_KEY"
#undef DECRYPT_START_SEC_CST_KEY
#endif

#ifdef DECRYPT_STOP_SEC_CST_KEY
#pragma ghs section rodata = default
#pragma ghs enddata
#undef DECRYPT_STOP_SEC_CST_KEY
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

