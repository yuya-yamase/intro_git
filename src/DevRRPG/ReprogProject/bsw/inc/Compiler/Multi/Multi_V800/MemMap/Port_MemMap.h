/* Port_MemMap_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Port/MemMap/HEADER                                          */
/******************************************************************************/

#ifdef PORT_START_SEC_CODE
#pragma ghs section text = ".P_PORT"
#undef PORT_START_SEC_CODE
#endif

#ifdef PORT_STOP_SEC_CODE
#pragma ghs section text = default
#undef PORT_STOP_SEC_CODE
#endif

#ifdef PORT_START_SEC_VAR
#pragma ghs startsda
#pragma ghs section sbss = ".B_PORT"
#undef PORT_START_SEC_VAR
#endif

#ifdef PORT_STOP_SEC_VAR
#pragma ghs section sbss = default
#pragma ghs endsda
#undef PORT_STOP_SEC_VAR
#endif

#ifdef PORT_START_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_PORT"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_PORT"
 #endif
#undef PORT_START_SEC_CST
#endif

#ifdef PORT_STOP_SEC_CST
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef PORT_STOP_SEC_CST
#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2020/06/16 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

