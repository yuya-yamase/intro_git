/* EcuM_MemMap_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | EcuM/MemMap/HEADER                                          */
/******************************************************************************/

/* 1st */
#ifdef ECUM_START_SEC1_CODE
#pragma ghs section text = ".P_RAM_1ST_FIXED"
#undef ECUM_START_SEC1_CODE
#endif

#ifdef ECUM_STOP_SEC1_CODE
#pragma ghs section text = default
#undef ECUM_STOP_SEC1_CODE
#endif

#ifdef ECUM_START_SEC1_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_1ST"
#undef ECUM_START_SEC1_VAR
#endif

#ifdef ECUM_STOP_SEC1_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef ECUM_STOP_SEC1_VAR
#endif

#ifdef ECUM_START_SEC1_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_RAM_1ST"
#undef ECUM_START_SEC1_CST
#endif

#ifdef ECUM_STOP_SEC1_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef ECUM_STOP_SEC1_CST
#endif

/* 2nd */
#ifdef ECUM_START_SEC2_CODE
#pragma ghs section text = ".P_RAM_2ND"
#undef ECUM_START_SEC2_CODE
#endif

#ifdef ECUM_STOP_SEC2_CODE
#pragma ghs section text = default
#undef ECUM_STOP_SEC2_CODE
#endif

#ifdef ECUM_START_SEC2_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef ECUM_START_SEC2_VAR
#endif

#ifdef ECUM_STOP_SEC2_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef ECUM_STOP_SEC2_VAR
#endif

#ifdef ECUM_START_SEC2_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_RAM_2ND"
#undef ECUM_START_SEC2_CST
#endif

#ifdef ECUM_STOP_SEC2_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef ECUM_STOP_SEC2_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

