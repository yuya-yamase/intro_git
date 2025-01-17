/* ExtCodeFlsIf_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | ExtCodeFlsIf/MemMap/HEADER                                  */
/******************************************************************************/

#ifdef EXTCODEFLSIF_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM"
 #else
 #pragma ghs section text = ".P_RAM_2ND"
 #endif
#undef EXTCODEFLSIF_START_SEC_CODE
#endif

#ifdef EXTCODEFLSIF_STOP_SEC_CODE
#pragma ghs section text = default
#undef EXTCODEFLSIF_STOP_SEC_CODE
#endif

#ifdef EXTCODEFLSIF_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef EXTCODEFLSIF_START_SEC_VAR
#endif

#ifdef EXTCODEFLSIF_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef EXTCODEFLSIF_STOP_SEC_VAR
#endif

#ifdef EXTCODEFLSIF_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_2ND"
 #endif
#undef EXTCODEFLSIF_START_SEC_CST
#endif

#ifdef EXTCODEFLSIF_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef EXTCODEFLSIF_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

