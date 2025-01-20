/* Shutdown_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Shutdown/MemMap/HEADER                                      */
/******************************************************************************/

#ifdef SHUTDOWN_START_SEC_CODE
#pragma ghs section text = ".P_ROM_BOOT"
#undef SHUTDOWN_START_SEC_CODE
#endif

#ifdef SHUTDOWN_STOP_SEC_CODE
#pragma ghs section text = default
#undef SHUTDOWN_STOP_SEC_CODE
#endif

#ifdef SHUTDOWN_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_1ST"
#undef SHUTDOWN_START_SEC_VAR
#endif

#ifdef SHUTDOWN_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef SHUTDOWN_STOP_SEC_VAR
#endif

#ifdef SHUTDOWN_START_SEC_CST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_BOOT"
#undef SHUTDOWN_START_SEC_CST
#endif

#ifdef SHUTDOWN_STOP_SEC_CST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef SHUTDOWN_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

