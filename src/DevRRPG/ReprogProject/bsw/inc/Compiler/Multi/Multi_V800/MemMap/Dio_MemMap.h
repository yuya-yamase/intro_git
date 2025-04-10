/* Dio_MemMap_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Dio/MemMap/HEADER                                           */
/******************************************************************************/

#ifdef DIO_START_SEC_CODE
#pragma ghs section text = ".P_DIO"
#undef DIO_START_SEC_CODE
#endif

#ifdef DIO_STOP_SEC_CODE
#pragma ghs section text = default
#undef DIO_STOP_SEC_CODE
#endif

#ifdef DIO_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_DIO"
#undef DIO_START_SEC_VAR
#endif

#ifdef DIO_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef DIO_STOP_SEC_VAR
#endif

#ifdef DIO_START_SEC_CST
#pragma ghs startsda
#pragma ghs section rosdata = ".C_DIO"
#undef DIO_START_SEC_CST
#endif

#ifdef DIO_STOP_SEC_CST
#pragma ghs section rosdata = default
#pragma ghs endsda
#undef DIO_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

