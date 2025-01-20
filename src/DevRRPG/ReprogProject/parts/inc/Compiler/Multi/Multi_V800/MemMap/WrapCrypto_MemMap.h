/* WrapCrypto_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/MemMap/HEADER                                    */
/******************************************************************************/

#ifdef WRAPCRYPTO_START_SEC_CODE
#pragma ghs section text = ".P_ROM_WRAPCRYPTO"
#undef WRAPCRYPTO_START_SEC_CODE
#endif

#ifdef WRAPCRYPTO_STOP_SEC_CODE
#pragma ghs section text = default
#undef WRAPCRYPTO_STOP_SEC_CODE
#endif

#ifdef WRAPCRYPTO_START_SEC_VAR
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_WRAPCRYPTO"
#undef WRAPCRYPTO_START_SEC_VAR
#endif

#ifdef WRAPCRYPTO_STOP_SEC_VAR
#pragma ghs section bss = default
#pragma ghs enddata
#undef WRAPCRYPTO_STOP_SEC_VAR
#endif

#ifdef WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_BUFF
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_WRAPCRYPTO_DECRYPT_DUMMYBUFF_SHARED"
#undef WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_BUFF
#endif

#ifdef WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_BUFF
#pragma ghs section bss = default
#pragma ghs enddata
#undef WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_BUFF
#endif

#ifdef WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_SIZE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_WRAPCRYPTO_DECRYPT_DUMMYSIZE_SHARED"
#undef WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_SIZE
#endif

#ifdef WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_SIZE
#pragma ghs section bss = default
#pragma ghs enddata
#undef WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_SIZE
#endif

#ifdef WRAPCRYPTO_START_SEC_VAR_SIGVERIFY_RET
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_WRAPCRYPTO_SIGVERIFY_RET_SHARED"
#undef WRAPCRYPTO_START_SEC_VAR_SIGVERIFY_RET
#endif

#ifdef WRAPCRYPTO_STOP_SEC_VAR_SIGVERIFY_RET
#pragma ghs section bss = default
#pragma ghs enddata
#undef WRAPCRYPTO_STOP_SEC_VAR_SIGVERIFY_RET
#endif

#ifdef WRAPCRYPTO_START_SEC_CST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_WRAPCRYPTO"
#undef WRAPCRYPTO_START_SEC_CST
#endif

#ifdef WRAPCRYPTO_STOP_SEC_CST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef WRAPCRYPTO_STOP_SEC_CST
#endif


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
