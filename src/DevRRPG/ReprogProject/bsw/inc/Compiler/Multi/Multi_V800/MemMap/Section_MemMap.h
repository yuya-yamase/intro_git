/* Section_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Section/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef SECTION_START_SEC_CODE
#undef SECTION_START_SEC_CODE
#endif

#ifdef SECTION_STOP_SEC_CODE
#undef SECTION_STOP_SEC_CODE
#endif

#ifdef SECTION_START_SEC_VAR
#undef SECTION_START_SEC_VAR
#endif

#ifdef SECTION_STOP_SEC_VAR
#undef SECTION_STOP_SEC_VAR
#endif

#ifdef SECTION_START_SEC_CST
#pragma ghs startdata
#pragma ghs section rodata = ".C_ROM"
#undef SECTION_START_SEC_CST
#endif

#ifdef SECTION_STOP_SEC_CST
#pragma ghs section rodata = default
#pragma ghs enddata
#undef SECTION_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

