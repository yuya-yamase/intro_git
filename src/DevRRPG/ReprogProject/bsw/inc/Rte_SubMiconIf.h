/* Rte_SubMicon_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/SubMiconIf/HEADER                                       */
/******************************************************************************/
#ifndef RTE_SUBMICONIF_H
#define RTE_SUBMICONIF_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <SubMiconIf.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_SUBMICONIF_E_PENDING            (SUBMICONIF_E_PENDING)

#define RTE_SUBMICONIF_INITIAL              ((Rte_SubMiconIf_OpStatusType)SUBMICONIF_INITIAL)
#define RTE_SUBMICONIF_PENDING              ((Rte_SubMiconIf_OpStatusType)SUBMICONIF_PENDING)

/* Microcontroller identifier */
#define RTE_SUBMICONIF_ID_MAIN              (SUBMICONIF_ID_MAIN)
#define RTE_SUBMICONIF_ID_SUB_1             (SUBMICONIF_ID_SUB_1)
#define RTE_SUBMICONIF_ID_SUB_2             (SUBMICONIF_ID_SUB_2)
#define RTE_SUBMICONIF_ID_SUB_3             (SUBMICONIF_ID_SUB_3)
#define RTE_SUBMICONIF_ID_SUB_4             (SUBMICONIF_ID_SUB_4)
#define RTE_SUBMICONIF_ID_SUB_5             (SUBMICONIF_ID_SUB_5)
#define RTE_SUBMICONIF_ID_SUB_6             (SUBMICONIF_ID_SUB_6)
#define RTE_SUBMICONIF_ID_SUB_7             (SUBMICONIF_ID_SUB_7)
#define RTE_SUBMICONIF_ID_SUB_8             (SUBMICONIF_ID_SUB_8)
#define RTE_SUBMICONIF_ID_SUB_9             (SUBMICONIF_ID_SUB_9)
#define RTE_SUBMICONIF_ID_SUB_10            (SUBMICONIF_ID_SUB_10)
#define RTE_SUBMICONIF_ID_SUB_11            (SUBMICONIF_ID_SUB_11)
#define RTE_SUBMICONIF_ID_SUB_12            (SUBMICONIF_ID_SUB_12)
#define RTE_SUBMICONIF_ID_SUB_13            (SUBMICONIF_ID_SUB_13)
#define RTE_SUBMICONIF_ID_SUB_14            (SUBMICONIF_ID_SUB_14)
#define RTE_SUBMICONIF_ID_SUB_15            (SUBMICONIF_ID_SUB_15)
#define RTE_SUBMICONIF_ID_SUB_16            (SUBMICONIF_ID_SUB_16)
#define RTE_SUBMICONIF_ID_SUB_17            (SUBMICONIF_ID_SUB_17)
#define RTE_SUBMICONIF_ID_SUB_18            (SUBMICONIF_ID_SUB_18)
#define RTE_SUBMICONIF_ID_SUB_19            (SUBMICONIF_ID_SUB_19)
#define RTE_SUBMICONIF_ID_SUB_20            (SUBMICONIF_ID_SUB_20)
#define RTE_SUBMICONIF_ID_SUB_21            (SUBMICONIF_ID_SUB_21)
#define RTE_SUBMICONIF_ID_SUB_22            (SUBMICONIF_ID_SUB_22)
#define RTE_SUBMICONIF_ID_SUB_23            (SUBMICONIF_ID_SUB_23)
#define RTE_SUBMICONIF_ID_SUB_24            (SUBMICONIF_ID_SUB_24)
#define RTE_SUBMICONIF_ID_SUB_25            (SUBMICONIF_ID_SUB_25)
#define RTE_SUBMICONIF_ID_SUB_26            (SUBMICONIF_ID_SUB_26)
#define RTE_SUBMICONIF_ID_SUB_27            (SUBMICONIF_ID_SUB_27)
#define RTE_SUBMICONIF_ID_SUB_28            (SUBMICONIF_ID_SUB_28)
#define RTE_SUBMICONIF_ID_SUB_29            (SUBMICONIF_ID_SUB_29)
#define RTE_SUBMICONIF_ID_SUB_30            (SUBMICONIF_ID_SUB_30)
#define RTE_SUBMICONIF_ID_SUB_31            (SUBMICONIF_ID_SUB_31)

#define Rte_SubMiconIf_UserDataTransmit     (SubMiconIf_UserDataTransmit)
#define Rte_SubMiconIf_Main_RequestService  (SubMiconIf_Main_RequestService)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef SubMiconIf_OpStatusType             Rte_SubMiconIf_OpStatusType;
typedef SubMiconIf_ReqInfoType              Rte_SubMiconIf_ReqInfoType;
typedef SubMiconIf_RespInfoType             Rte_SubMiconIf_RespInfoType;
typedef SubMiconIf_UserDataInfoType         Rte_SubMiconIf_UserDataInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* RTE_SUBMICONIF_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*  v2.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

