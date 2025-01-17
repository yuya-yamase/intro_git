/* Rte_EcuM_h_Revision(v4.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/EcuM/HEADER                                             */
/******************************************************************************/
#ifndef RTE_ECUM_H
#define RTE_ECUM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_ECUM_MODULE_RPGMFR              ((uint16)ECUM_MODULE_RPGMFR)
#define RTE_ECUM_MODULE_RPGSPP              ((uint16)ECUM_MODULE_RPGSPP)
#define RTE_ECUM_MODULE_SEC                 ((uint16)ECUM_MODULE_SEC)
#define RTE_ECUM_MODULE_DECRYPT             ((uint16)ECUM_MODULE_DECRYPT)
#define RTE_ECUM_MODULE_PRGCHK              ((uint16)ECUM_MODULE_PRGCHK)
#define RTE_ECUM_MODULE_FSCDTCT             ((uint16)ECUM_MODULE_FSCDTCT)
#define RTE_ECUM_MODULE_RPGEVTHK            ((uint16)ECUM_MODULE_RPGEVTHK)
#define RTE_ECUM_MODULE_VEHINF              ((uint16)ECUM_MODULE_VEHINF)
#define RTE_ECUM_MODULE_CMPDECMP            ((uint16)ECUM_MODULE_CMPDECMP)
#define RTE_ECUM_MODULE_RPGLIB              ((uint16)ECUM_MODULE_RPGLIB)
#define RTE_ECUM_MODULE_DIAGLIB             ((uint16)ECUM_MODULE_DIAGLIB)
#define RTE_ECUM_MODULE_DIAGSRV             ((uint16)ECUM_MODULE_DIAGSRV)

#define RTE_ECUM_START_BOOT_ENTRY           ((uint8)ECUM_START_BOOT_ENTRY)
#define RTE_ECUM_START_AP_ENTRY             ((uint8)ECUM_START_AP_ENTRY)
#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
#define RTE_ECUM_START_BOOT_POSRES_ENTRY    ((uint8)ECUM_START_BOOT_POSRES_ENTRY)
#endif
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#define RTE_ECUM_START_STAYINBOOT_ENTRY     ((uint8)ECUM_START_STAYINBOOT_ENTRY)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef EcuM_ErrorType  Rte_EcuM_ErrorType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, RTE_CODE_SLOW) Rte_EcuM_ReportError
(
    P2CONST(Rte_EcuM_ErrorType, AUTOMATIC, RTE_APPL_CONST) ErrorInfo
);
FUNC(uint8, RTE_CODE_SLOW) Rte_EcuM_GetBootMode (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* RTE_ECUM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v4.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

