/* Rte_RpgEvtHk_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/RpgEvtHk/MemMap/HEADER                                  */
/******************************************************************************/

#ifdef RTE_RPGEVTHK_START_SEC_CODE
#pragma ghs section text = ".P_RAM_2ND"
#undef RTE_RPGEVTHK_START_SEC_CODE
#endif

#ifdef RTE_RPGEVTHK_STOP_SEC_CODE
#pragma ghs section text = default
#undef RTE_RPGEVTHK_STOP_SEC_CODE
#endif

#ifdef RTE_RPGEVTHK_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_RAM_2ND"
#undef RTE_RPGEVTHK_START_SEC_VAR
#endif

#ifdef RTE_RPGEVTHK_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef RTE_RPGEVTHK_STOP_SEC_VAR
#endif

#ifdef RTE_RPGEVTHK_START_SEC_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_RAM_2ND"
#undef RTE_RPGEVTHK_START_SEC_CST
#endif

#ifdef RTE_RPGEVTHK_STOP_SEC_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef RTE_RPGEVTHK_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

