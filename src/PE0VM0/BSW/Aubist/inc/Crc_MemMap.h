/* MemMap_h_v2-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MemMap/HEADER                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define MEMMAP_ERROR

#if defined CRC_START_SEC_CODE
#undef CRC_START_SEC_CODE
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CODE
#undef CRC_STOP_SEC_CODE
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_APPL_DATA
#undef CRC_START_SEC_APPL_DATA
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_APPL_DATA
#undef CRC_STOP_SEC_APPL_DATA
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_CONST_8
#undef CRC_START_SEC_CONST_8
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CONST_8
#undef CRC_STOP_SEC_CONST_8
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_CONST_16
#undef CRC_START_SEC_CONST_16
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CONST_16
#undef CRC_STOP_SEC_CONST_16
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_CONST_32
#undef CRC_START_SEC_CONST_32
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CONST_32
#undef CRC_STOP_SEC_CONST_32
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#elif defined CRC_START_SEC_CONST_64
#undef CRC_START_SEC_CONST_64
/* Pragma statement Start */
#undef MEMMAP_ERROR

#elif defined CRC_STOP_SEC_CONST_64
#undef CRC_STOP_SEC_CONST_64
/* Pragma statement Stop */
#undef MEMMAP_ERROR

#endif


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#if defined MEMMAP_ERROR
#error "Crc_MemMap.h, wrong pragma command"
#endif /* MEMMAP_ERROR */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
