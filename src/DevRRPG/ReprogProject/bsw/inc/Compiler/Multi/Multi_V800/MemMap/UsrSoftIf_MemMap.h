/* UsrSoftIf_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | UsrSoftIf/MemMap/HEADER                                     */
/******************************************************************************/

/* ROM */
#ifdef USRSOFTIF_START_SEC1_CODE
#pragma ghs section text = ".P_ROM"
#undef USRSOFTIF_START_SEC1_CODE
#endif

#ifdef USRSOFTIF_STOP_SEC1_CODE
#pragma ghs section text = default
#undef USRSOFTIF_STOP_SEC1_CODE
#endif

#ifdef USRSOFTIF_START_SEC1_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_1ST"
#undef USRSOFTIF_START_SEC1_VAR
#endif

#ifdef USRSOFTIF_STOP_SEC1_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef USRSOFTIF_STOP_SEC1_VAR
#endif

#ifdef USRSOFTIF_START_SEC1_CST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM"
#undef USRSOFTIF_START_SEC1_CST
#endif

#ifdef USRSOFTIF_STOP_SEC1_CST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef USRSOFTIF_STOP_SEC1_CST
#endif

/* RAM 2nd */
#ifdef USRSOFTIF_START_SEC2_CODE
#pragma ghs section text = ".P_RAM_2ND"
#undef USRSOFTIF_START_SEC2_CODE
#endif

#ifdef USRSOFTIF_STOP_SEC2_CODE
#pragma ghs section text = default
#undef USRSOFTIF_STOP_SEC2_CODE
#endif

#ifdef USRSOFTIF_START_SEC2_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef USRSOFTIF_START_SEC2_VAR
#endif

#ifdef USRSOFTIF_STOP_SEC2_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef USRSOFTIF_STOP_SEC2_VAR
#endif

#ifdef USRSOFTIF_START_SEC2_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_RAM_2ND"
#undef USRSOFTIF_START_SEC2_CST
#endif

#ifdef USRSOFTIF_STOP_SEC2_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef USRSOFTIF_STOP_SEC2_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

