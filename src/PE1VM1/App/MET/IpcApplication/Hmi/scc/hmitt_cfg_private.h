/* 1.9.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmitt                                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef HMITT_CFG_H
#define HMITT_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITT_CFG_H_MAJOR                     (1)
#define HMITT_CFG_H_MINOR                     (9)
#define HMITT_CFG_H_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "hmitt.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_HMITT_HB7(x)                           ((U4)((U4)(x) << 28U))
#define u4_HMITT_HB6(x)                           ((U4)((U4)(x) << 24U))
#define u4_HMITT_HB5(x)                           ((U4)((U4)(x) << 20U))
#define u4_HMITT_HB4(x)                           ((U4)((U4)(x) << 16U))
#define u4_HMITT_HB3(x)                           ((U4)((U4)(x) << 12U))
#define u4_HMITT_HB2(x)                           ((U4)((U4)(x) <<  8U))
#define u4_HMITT_HB1(x)                           ((U4)((U4)(x) <<  4U))
#define u4_HMITT_HB0(x)                           ((U4)((U4)(x)       ))

#define HMITT_BLINK_CO_OFF____100P                   (0U)
#define HMITT_BLINK_CO_ON_____100P                   (1U)
#define HMITT_BLINK_CO_ON_____100P_SPD_LO            (1U)
#define HMITT_BLINK_CO_ON_____100P_SPD_LOMID         (2U)
#define HMITT_BLINK_CO_ON_____100P_SPD_MID           (3U)
#define HMITT_BLINK_CO_ON_____100P_SPD_MIDHI         (4U)
#define HMITT_BLINK_CO_ON_____100P_SPD_HI            (5U)
#define HMITT_BLINK_CO_2P00HZ__50P                   (2U)
#define HMITT_BLINK_CO_4P00HZ__50P                   (3U)
#define HMITT_BLINK_CO_0P50HZ__50P                   (2U)
#define HMITT_BLINK_CO_1P00HZ__50P_S_OFF             (2U)
#define HMITT_BLINK_CO_1P00HZ__50P                   (2U)
#define HMITT_BLINK_CO_2P50HZ__50P_CLESON            (2U)
#define HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF       (2U)
#define HMITT_BLINK_CO_0P25HZ__50P                   (2U)
#define HMITT_BLINK_CO_3P33HZ__50P                   (4U)
#define HMITT_BLINK_SI_1P00HZ__50P_5TIMS_E_OFF       (4U)
#define HMITT_BLINK_CO_4P00HZ__50P_EPB               (4U)
#define HMITT_BLINK_CO_2P00HZ__50P_EPB               (3U)
#define HMITT_BLINK_CO_4P00HZ__50P_STEER             (2U)
#define HMITT_BLINK_CO_2P00HZ__50P_TMPIND            (1U)
#define HMITT_BLINK_SI_1P00HZ__50P_10TIMS_E__ON      (1U)
#define HMITT_BLINK_CO_1P00HZ__50P_63TIMS_E__ON      (5U)
#define HMITT_BLINK_CO_5P00HZ__50P                   (2U)
#define HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ3  (2U)
#define HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ4  (3U)
#define HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ5  (4U)
#define HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ6  (5U)
#define HMITT_BLINK_CO_1P00HZ__50P_TPMS              (3U)
#define HMITT_BLINK_CO_4P00HZ__50P_TPMS              (4U)
#define HMITT_BLINK_CO_1P00HZ__50P_STOSTA            (3U)
#define HMITT_BLINK_CO_ON_____100P_AIRBAG            (2U)
#define HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_OFF_THEVM (2U)
#define HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_ON_THEVM  (3U)
#define HMITT_BLINK_CO_1P00HZ__50P_S_OFF_THEVM       (3U)
#define HMITT_BLINK_CO_4P00HZ__50P_FACTMD            (1U)

#define HMITT_BLINK_CO_0P83HZ__50P                   (2U)
#define HMITT_BLINK_CO_2P50HZ__50P                   (3U)
#define HMITT_BLINK_CO_1P00HZ__50P_4WDTRF           (3U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_HmiTtCfgInit(void);
void    vd_g_HmiTtCfgReq(U4 * u4_ap_req);
void    vd_g_HmiTtCfgVarmask(U4 * u4_ap_varmask);
void    vd_g_HmiTtCfgDestmask(U4* u4_ap_varmask);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* HMITT_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  hmitt.c                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
