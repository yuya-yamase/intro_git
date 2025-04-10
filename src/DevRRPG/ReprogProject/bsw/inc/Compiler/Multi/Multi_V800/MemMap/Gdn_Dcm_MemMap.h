/* Gdn_Dcm_MemMap_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Gdn_Dcm/MemMap/HEADER                                       */
/******************************************************************************/

#ifdef GDN_DCM_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_GDN"
 #else
 #pragma ghs section text = ".P_RAM_GDN"
 #endif
#undef GDN_DCM_START_SEC_CODE
#endif

#ifdef GDN_DCM_STOP_SEC_CODE
#pragma ghs section text = default
#undef GDN_DCM_STOP_SEC_CODE
#endif

#ifdef GDN_DCM_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef GDN_DCM_START_SEC_VAR
#endif

#ifdef GDN_DCM_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef GDN_DCM_STOP_SEC_VAR
#endif

#ifdef GDN_DCM_START_SEC_VAR_LARGE
#pragma ghs startdata
#pragma ghs section bss = ".B_RAM_2ND_LARGE"
#undef GDN_DCM_START_SEC_VAR_LARGE
#endif

#ifdef GDN_DCM_STOP_SEC_VAR_LARGE
#pragma ghs section bss = default
#pragma ghs enddata
#undef GDN_DCM_STOP_SEC_VAR_LARGE
#endif

#ifdef GDN_DCM_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_GDN"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_GDN"
 #endif
#undef GDN_DCM_START_SEC_CST
#endif

#ifdef GDN_DCM_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef GDN_DCM_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/12/11 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

