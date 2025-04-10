/* Rte_BswM_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/BswM/HEADER                                             */
/******************************************************************************/
#ifndef RTE_BSWM_H
#define RTE_BSWM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_BSWM_MODE_USR_RESET_EXECUTE     ((uint16)BSWM_MODE_USR_RESET_EXECUTE)
#if 0   /* Nbr1503(SleepAPI) */
#define RTE_BSWM_MODE_USR_SLEEP_EXECUTE     ((uint16)BSWM_MODE_USR_SLEEP_EXECUTE)
#endif

#define RTE_BSWM_MODE_ACC_OFF               ((uint16)BSWM_MODE_ACC_OFF)
#define RTE_BSWM_MODE_ACC_ON                ((uint16)BSWM_MODE_ACC_ON)

#define RTE_BSWM_MODE_IG_OFF                ((uint16)BSWM_MODE_IG_OFF)
#define RTE_BSWM_MODE_IG_ON                 ((uint16)BSWM_MODE_IG_ON)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_RpgEvtHkUsrReset
(
    VAR(uint16, AUTOMATIC) Mode
);
#if 0   /* Nbr1503(SleepAPI) */
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_RpgEvtHkUsrSleep
(
    VAR(uint16, AUTOMATIC) Mode
);
#endif
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_VehInfAccControl
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(void, RTE_CODE_SLOW) Rte_BswM_Switch_VehInfIgControl
(
    VAR(uint16, AUTOMATIC) Mode
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

#endif /* RTE_BSWM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

