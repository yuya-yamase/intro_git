/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name MemMap/HEADER                                                */
/*----------------------------------------------------------------          */
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v1_0_0      :2017/02/16 :New created                                   */
/*----------------------------------------------------------------          */
/* Notes                                                                    */
/****************************************************************************/

#define MEMMAP_ERROR

#if defined CRC_START_SEC_CODE
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section text = ".P_ROM_CRC"
 #else
 #pragma ghs section text = ".P_RAM_CRC"
 #endif
#undef CRC_START_SEC_CODE
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CODE
#pragma ghs section text = default
#undef CRC_STOP_SEC_CODE
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_CONST_32
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs startdata
 #pragma ghs section rodata = ".C_ROM_CRC"
 #else
 #pragma ghs startsda
 #pragma ghs section rosdata = ".C_RAM_CRC"
 #endif
#undef CRC_START_SEC_CONST_32
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CONST_32
 #if (REPROG_CFG_SMALL_RAM_USE == STD_ON)
 #pragma ghs section rodata = default
 #pragma ghs enddata
 #else
 #pragma ghs section rosdata = default
 #pragma ghs endsda
 #endif
#undef CRC_STOP_SEC_CONST_32
#undef MEMMAP_ERROR

#endif

#if defined MEMMAP_ERROR
#error "Crc_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */

