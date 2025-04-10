/* Dcm_FuncSwitchOBD_cfg_h(v5-3-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/FuncSwitchOBD/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_FUNCSWITCHOBD_CFG_H
#define DCM_FUNCSWITCHOBD_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* DcmOBDType */
#define DCM_OBDTYPE_TYPE_OBD                 (STD_ON)
#define DCM_OBDTYPE_TYPE_MOBD                (STD_ON)
#define DCM_OBD_SYSTEM_ON_UNIFIED_DS         (STD_OFF)   /* Use Legislated OBDSystem OBDonUDS */
#define DCM_OBD_SYSTEM_ON_EMISSION_DS        (STD_ON)    /* Use Legislated OBDSystem OBDonEDS */
#define DCM_OBD_DTC_ALL_CLEAR_BY_FFFF33      (STD_OFF)   /* Use DTC All Clear by FFFF33 */
#define DCM_OBD_RANGE_DID_USE                (STD_OFF)   /* Read Data by OBD Range DID */
#define DCM_OBD_RANGE_RID_USE                (STD_OFF)   /* Start Routine by OBD Range RID */
#define DCM_SUPPORT_SID01                    (STD_OFF)      /* Use ServiceId 01     */
#define DCM_SUPPORT_SID02                    (STD_OFF)      /* Use ServiceId 02     */
#define DCM_SUPPORT_SID03                    (STD_OFF)      /* Use ServiceId 03     */
#define DCM_SUPPORT_SID04                    (STD_OFF)      /* Use ServiceId 04     */
#define DCM_SUPPORT_SID06                    (STD_OFF)      /* Use ServiceId 06     */
#define DCM_SUPPORT_SID07                    (STD_OFF)      /* Use ServiceId 07     */
#define DCM_SUPPORT_SID08                    (STD_OFF)      /* Use ServiceId 08     */
#define DCM_SUPPORT_SID09                    (STD_OFF)      /* Use ServiceId 09     */
#define DCM_SUPPORT_SID0A                    (STD_OFF)      /* Use ServiceId 0A     */


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


#endif /* DCM_FUNCSWITCHOBD_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v5-5-1                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
