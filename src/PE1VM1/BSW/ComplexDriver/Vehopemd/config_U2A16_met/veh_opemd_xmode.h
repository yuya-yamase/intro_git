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
#define VEH_OPEMD_MDBIT_ACC                      (0x00000010U)
#define VEH_OPEMD_MDBIT_STA                      (0x00000020U)
#define VEH_OPEMD_MDBIT_IGN                      (0x00000040U)
#define VEH_OPEMD_MDBIT_TST                      (0x00000080U)  /* TC    */
#define VEH_OPEMD_MDBIT_RDY                      (0x00000100U)  /* Ready */
#define VEH_OPEMD_MDBIT_IGNP                     (0x00000200U)  /* IGP   */
#define VEH_OPEMD_MDBIT_PBA                      (0x00000400U)  /* PBA   */


#define VEH_OPEMD_MDBIT_FIELDS                   (0x000007f0U)
#define VEH_OPEMD_MDLSB_FIELDS                   (4U)

#define VEH_OPEMD_EVTBIT_ACC_TO_ON               (0x00000010U)
#define VEH_OPEMD_EVTBIT_STA_TO_ON               (0x00000020U)
#define VEH_OPEMD_EVTBIT_IGN_TO_ON               (0x00000040U)
#define VEH_OPEMD_EVTBIT_TST_TO_ON               (0x00000080U)
#define VEH_OPEMD_EVTBIT_RDY_TO_ON               (0x00000100U)
#define VEH_OPEMD_EVTBIT_IGNP_TO_ON              (0x00000200U)
#define VEH_OPEMD_EVTBIT_PBA_TO_ON               (0x00000400U)


#define VEH_OPEMD_EVTBIT_ACC_TO_OFF              (0x00001000U)
#define VEH_OPEMD_EVTBIT_STA_TO_OFF              (0x00002000U)
#define VEH_OPEMD_EVTBIT_IGN_TO_OFF              (0x00004000U)
#define VEH_OPEMD_EVTBIT_TST_TO_OFF              (0x00008000U)
#define VEH_OPEMD_EVTBIT_RDY_TO_OFF              (0x00010000U)
#define VEH_OPEMD_EVTBIT_IGNP_TO_OFF             (0x00020000U)
#define VEH_OPEMD_EVTBIT_PBA_TO_OFF              (0x00040000U)


#define VEH_OPEMD_EVTBIT_FIELDS                  (0x0007f7f0U)
#define VEH_OPEMD_EVTLSB_TO_ON                   (4U)
#define VEH_OPEMD_EVTLSB_TO_OFF                  (12U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VEH_OPEMD_TM_VOM_NRML                    (0U) /* Ig-On & St-Off */
#define VEH_OPEMD_TM_IGN_OFF                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_VehopemdIgnOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_IGN, (U4)VEH_OPEMD_MDBIT_IGN))
#define u1_g_VehopemdStaOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_STA, (U4)VEH_OPEMD_MDBIT_STA))
#define u1_g_VehopemdAccOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_ACC, (U4)VEH_OPEMD_MDBIT_ACC))
#define u1_g_VehopemdTstOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_TST, (U4)VEH_OPEMD_MDBIT_TST))
#define u1_g_VehopemdRdyOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_RDY, (U4)VEH_OPEMD_MDBIT_RDY))
#define u1_g_VehopemdIgnpOn()                    (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_IGNP, (U4)VEH_OPEMD_MDBIT_IGNP))
#define u1_g_VehopemdPbaOn()                     (u1_g_VehopemdMdchk((U4)VEH_OPEMD_MDBIT_PBA, (U4)VEH_OPEMD_MDBIT_PBA))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_g_VehopemdTmElapsed(const U1 u1_a_TM, const U2 u2_a_THRSHLD); /* Return : True = elapsed / False = not elapsed yet */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* VEH_OPEMD_XMODE_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see veh_opemd_tycan.c                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
