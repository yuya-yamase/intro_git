/* 1.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Operational Mode                                                                                                         */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  WARNING :                                                                                                                        */
/*  veh_opemd_xmode.h is included in veh_opemd.h.                                                                                     */
/*  DO NOT include this file in any file even though this configuration header is public.                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef VEH_OPEMD_XMODE_H
#define VEH_OPEMD_XMODE_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_OEM_TYCAN                      (1)
#define __VEH_OPEMD_OEM__                        (VEH_OPEMD_OEM_TYCAN)

#define VEH_OPEMD_XMODE_H_MAJOR                  (1)
#define VEH_OPEMD_XMODE_H_MINOR                  (3)
#define VEH_OPEMD_XMODE_H_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_MDBIT_OFF                      (0x00000000U)
#define VEH_OPEMD_MDBIT_PAR                      (0x00000001U)    /* Parking                               */
#define VEH_OPEMD_MDBIT_RID                      (0x00000002U)    /* Riding                                */
#define VEH_OPEMD_MDBIT_PON                      (0x00000004U)    /* PowerOnNormal                         */
#define VEH_OPEMD_MDBIT_POE                      (0x00000008U)    /* PowerOnEmergency                      */
#define VEH_OPEMD_MDBIT_PAR_HV                   (0x00000010U)    /* ParkingHighVoltage                    */
#define VEH_OPEMD_MDBIT_PAR_HVHC                 (0x00000020U)    /* ParkingHighVoltageAndHeatConditioning */
#define VEH_OPEMD_MDBIT_CHK                      (0x00000040U)    /* Checking                              */
#define VEH_OPEMD_MDBIT_PDM                      (0x00000080U)    /* Pre-Delivery mode                     */
#define VEH_OPEMD_MDBIT_OTA1                     (0x00000100U)    /* OTA Special status No.1               */
#define VEH_OPEMD_MDBIT_OTA2                     (0x00000200U)    /* OTA Special status No.2               */
#define VEH_OPEMD_MDBIT_OTA3                     (0x00000400U)    /* OTA Special status No.3               */
#define VEH_OPEMD_MDBIT_OTA4                     (0x00000800U)    /* OTA Special status No.4               */
#define VEH_OPEMD_MDBIT_WRP                      (0x00001000U)    /* Wired reprogramming                   */
#define VEH_OPEMD_MDBIT_EDS                      (0x00002000U)    /* Emergency driving stop                */
#define VEH_OPEMD_MDBIT_PAO                      (0x00004000U)    /* Power all off                         */

#define VEH_OPEMD_MDBIT_FIELDS                   (0x00007FFFU)
#define VEH_OPEMD_EVTBIT_FIELDS                  (0x7FFF7FFFU)

#define VEH_OPEMD_EVTBIT_RID_TO_ON               (0x00000002U)
#define VEH_OPEMD_EVTBIT_POE_TO_ON               (0x00000008U)
#define VEH_OPEMD_EVTBIT_PON_TO_ON               (0x00000004U)
#define VEH_OPEMD_EVTBIT_PAR_TO_ON               (0x00000001U)

#define VEH_OPEMD_EVTBIT_RID_TO_OFF              (0x00020000U)
#define VEH_OPEMD_EVTBIT_POE_TO_OFF              (0x00080000U)
#define VEH_OPEMD_EVTBIT_PON_TO_OFF              (0x00040000U)
#define VEH_OPEMD_EVTBIT_PAR_TO_OFF              (0x00010000U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_VehopemdPonEmr()                    (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_POE, (U4)VEH_OPEMD_MDBIT_POE))
#define u1_g_VehopemdRiding()                    (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_RID, (U4)VEH_OPEMD_MDBIT_RID))
#define u1_g_VehopemdPonNml()                    (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_PON, (U4)VEH_OPEMD_MDBIT_PON))


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* VEH_OPEMD_XMODE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see veh_opemd_tybev3.c                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
