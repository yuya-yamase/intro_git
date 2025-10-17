/* Fls_Cfg_h_Revision(v1_0_0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS Corporation                                             */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FLS/CFG/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FLS_CFG_H
#define FLS_CFG_H


#include <MemIf_Types.h>
#include <Fee_Cbk.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** Microcontroller dependent constants for Data Flash ***/
#define FLS_SECTOR_SIZE_000      ( 0x00001000UL )               /* sector size                  */
#define FLS_SECTOR_NUMBER_000    ( 128UL )                      /* total number of sectors      */
#define FLS_WRITE_UNIT_SIZE_000  ( 4UL )                        /* data flash writing size unit */
#define FLS_BASE_ADDRESS_000     ( 0xFF200000UL )               /* DataFlashBaseAddress         */
#define FLS_END_ADDRESS_000      ( FLS_BASE_ADDRESS_000 + ( FLS_SECTOR_SIZE_000 * FLS_SECTOR_NUMBER_000 ) - 1UL ) /* DataFlashEndAddress         */

/*** Setting of API loading/non-loading ***/
#define FLS_GET_STATUS_API       ( STD_ON  )    /* Enable/Disable of Processing State Acquisition Request    */
#define FLS_READ_API             ( STD_OFF )    /* Enable/Disable of Read Request                            */
#define FLS_COMPARE_API          ( STD_OFF )    /* Enable/Disable of Comparison Request                      */
#define FLS_GET_JOB_RESULT_API   ( STD_ON  )    /* Enable/Disable of Processing Result Acquisition Request   */
#define FLS_SET_MODE_API         ( STD_OFF )    /* Enable/Disable of Mode Setting Request                    */
#define FLS_VERSION_INFO_API     ( STD_ON  )    /* Enable/Disable of Version Information Acquisition Request */
#define FLS_DEV_ERROR_DETECT     ( STD_ON  )    /* Enable/Disable of Report Content Notification             */
#define FLS_CANCEL_API           ( STD_ON  )    /* Enable/Disable of Cancel Request                          */

#define FLS_BASE_ADDRESS           FLS_BASE_ADDRESS_000
#define FLS_END_ADDRESS            FLS_END_ADDRESS_000
#define FLS_SECTOR_SIZE            FLS_SECTOR_SIZE_000
#define FLS_SECTOR_NUMBER          FLS_SECTOR_NUMBER_000
#define FLS_CFG_WRITE_UNIT_SIZE    FLS_WRITE_UNIT_SIZE_000

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


#endif /*FLS_CFG_H */


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
