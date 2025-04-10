/* Can_MemMap_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Can/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef CAN_START_SEC_CODE
#pragma ghs section text = ".P_CAN"
#undef CAN_START_SEC_CODE
#endif

#ifdef CAN_STOP_SEC_CODE
#pragma ghs section text = default
#undef CAN_STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_CAN"
#undef CAN_START_SEC_VAR
#endif

#ifdef CAN_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef CAN_STOP_SEC_VAR
#endif

#ifdef CAN_START_SEC_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_CAN"
#undef CAN_START_SEC_CST
#endif

#ifdef CAN_STOP_SEC_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef CAN_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

