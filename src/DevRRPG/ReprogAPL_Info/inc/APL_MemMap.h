/* APL_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | APL/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef APL_START_SEC_VERSION
#pragma ghs startdata
#pragma ghs section rodata = ".APL_VERSION"
#undef APL_START_SEC_VERSION
#endif

#ifdef APL_STOP_SEC_VERSION
#pragma ghs section rodata = default
#pragma ghs enddata
#undef APL_STOP_SEC_VERSION
#endif

#ifdef APL_START_SEC_JUMPADDR
#pragma ghs startdata
#pragma ghs section rodata = ".APL_JUMPADDR"
#undef APL_START_SEC_JUMPADDR
#endif

#ifdef APL_STOP_SEC_JUMPADDR
#pragma ghs section rodata = default
#pragma ghs enddata
#undef APL_STOP_SEC_JUMPADDR
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Data       :Description                                      */
/*  v1.00       :2016/09/30 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

