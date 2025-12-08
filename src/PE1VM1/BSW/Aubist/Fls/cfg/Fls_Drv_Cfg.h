/* Fls_Drv_Cfg.h v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS Corporation                                             */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Fls/Drv/Cfg/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FLS_DRV_CFG_H
#define FLS_DRV_CFG_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*** Microcontroller dependent constants for Data Flash ***/
#define FLS_Drv_CPU_FREQUENCY                       (400U)     /* CPU frequency(MHz) */

/* Change in ISU-S/ISU-M/ISU-OFF */
#define FLS_Drv_HSM_ICUM    ( 0x02U )    /* ICU-M */
#define FLS_Drv_HSM_OFF     ( 0x03U )    /* ICU-OFF */

#define FLS_Drv_HSM_VALUE    FLS_Drv_HSM_OFF    /* Effective ICU type */

/*=============================================================*/
/* set the target model to FLS_Drv_SELECT_DEVICE.              */
/*=============================================================*/
#define FLS_Drv_DEVICE_U2A6                         ( 0x01U )               /* U2A6    */
#define FLS_Drv_DEVICE_U2A8                         ( 0x02U )               /* U2A8    */
#define FLS_Drv_DEVICE_U2A16                        ( 0x03U )               /* U2A16   */
#define FLS_Drv_DEVICE_U2B6                         ( 0x04U )               /* U2B6    */
#define FLS_Drv_DEVICE_U2B10                        ( 0x05U )               /* U2B10   */

/* Flash Programing System */
#define FLS_Drv_FPSYS_ALL                           ( 0x01U )               /* Standard */
#define FLS_Drv_FPSYS_0                             ( 0x02U )               /* System 0 (U2A8 Only) */
#define FLS_Drv_FPSYS_1                             ( 0x03U )               /* System 1 (U2A8 Only) */

#define FLS_Drv_SELECT_DEVICE                       FLS_Drv_DEVICE_U2A16    /* The target model */

#if ( ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A8 ) || ( FLS_Drv_SELECT_DEVICE == FLS_Drv_DEVICE_U2A16 ) )
#define FLS_Drv_SELECT_FPSYS                        FLS_Drv_FPSYS_ALL       /* The target flash sequencer mode */
#else
#define FLS_Drv_SELECT_FPSYS                        FLS_Drv_FPSYS_ALL       /* FPSYS_ALL Only */
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


#endif /*FLS_DRV_CFG_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2024/07/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
