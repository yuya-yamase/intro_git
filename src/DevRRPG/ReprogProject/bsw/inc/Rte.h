/* Rte_h_Revision(v5.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/HEADER                                                  */
/******************************************************************************/
#ifndef RTE_H
#define RTE_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Rte_BswM.h>
#include <Rte_CanIf.h>
#include <Rte_CanSM.h>
#include <Rte_CmpDecmp.h>
#include <Rte_CodeFlsIf.h>
#include <Rte_Decrypt.h>
#include <Rte_EcuM.h>
#include <Rte_FscDtct.h>
#include <Rte_MemErrM.h>
#include <Rte_MemM.h>
#include <Rte_PrgChk.h>
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
#include <Rte_SubMiconIf.h> /* This header file is need to include before Rte_RpgEvtHk.h */
#endif
#include <Rte_RpgEvtHk.h>
#include <Rte_RpgLib.h>
#include <Rte_RpgMfr.h>
#include <Rte_RpgSpp.h>
#include <Rte_SchM.h>
#include <Rte_Sec.h>
#include <Rte_Sys.h>
#include <Rte_Tm.h>
#include <Rte_UsrSoftIf.h>
#include <Rte_VehInf.h>
#if ((REPROG_CFG_ETH_USE == STD_ON) && (REPROG_CFG_ETH_DOIP_USE == STD_ON))
#include <Rte_DoIP.h>
#endif /* ((REPROG_CFG_ETH_USE == STD_ON) && (REPROG_CFG_ETH_DOIP_USE == STD_ON)) */


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* RTE_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v5.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

