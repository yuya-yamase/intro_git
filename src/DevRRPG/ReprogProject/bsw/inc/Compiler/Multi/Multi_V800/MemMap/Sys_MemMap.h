/* Sys_MemMap_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sys/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef SYS_START_SEC_CODE
#pragma ghs section text = ".P_RAM_1ST_FIXED"
#undef SYS_START_SEC_CODE
#endif

#ifdef SYS_STOP_SEC_CODE
#pragma ghs section text = default
#undef SYS_STOP_SEC_CODE
#endif

#ifdef SYS_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_1ST"
#undef SYS_START_SEC_VAR
#endif

#ifdef SYS_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef SYS_STOP_SEC_VAR
#endif

#ifdef SYS_START_SEC_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_RAM_1ST"
#undef SYS_START_SEC_CST
#endif

#ifdef SYS_STOP_SEC_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef SYS_STOP_SEC_CST
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

