/* Wdg_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Wdg/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef WDG_START_SEC_CODE
#pragma ghs section text = ".P_WDG"
#undef WDG_START_SEC_CODE
#endif

#ifdef WDG_STOP_SEC_CODE
#pragma ghs section text = default
#undef WDG_STOP_SEC_CODE
#endif

#ifdef WDG_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_WDG"
#undef WDG_START_SEC_VAR
#endif

#ifdef WDG_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef WDG_STOP_SEC_VAR
#endif

#ifdef WDG_START_SEC_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_WDG"
#undef WDG_START_SEC_CST
#endif

#ifdef WDG_STOP_SEC_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef WDG_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

