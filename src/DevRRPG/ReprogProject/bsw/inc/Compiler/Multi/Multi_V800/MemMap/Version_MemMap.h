/* Version_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Version/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef VERSION_START_SEC_CODE
#undef VERSION_START_SEC_CODE
#endif

#ifdef VERSION_STOP_SEC_CODE
#undef VERSION_STOP_SEC_CODE
#endif

#ifdef VERSION_START_SEC_VAR
#undef VERSION_START_SEC_VAR
#endif

#ifdef VERSION_STOP_SEC_VAR
#undef VERSION_STOP_SEC_VAR
#endif

#ifdef VERSION_START_SEC_CST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM_VER"
#undef VERSION_START_SEC_CST
#endif

#ifdef VERSION_STOP_SEC_CST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef VERSION_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

