/* Rte_RpgEvtHk_h_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/RpgEvtHk/HEADER                                         */
/******************************************************************************/
#ifndef RTE_RPGEVTHK_H
#define RTE_RPGEVTHK_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <RpgEvtHk.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_RPGEVTHK_E_PENDING         (RPGEVTHK_E_PENDING)

#define RTE_RPGEVTHK_EXCPT_RECOVER     ((uint32)RPGEVTHK_EXCPT_RECOVER)
#define RTE_RPGEVTHK_EXCPT_UNRECOVER   ((uint32)RPGEVTHK_EXCPT_UNRECOVER)

#define RTE_RPGEVTHK_CODEFLSCTRL_WRITE              (RPGEVTHK_CODEFLSCTRL_WRITE)
#define RTE_RPGEVTHK_CODEFLSCTRL_ERASE              (RPGEVTHK_CODEFLSCTRL_ERASE)
#define RTE_RPGEVTHK_CODEFLSCTRL_WRITABLECHECK      (RPGEVTHK_CODEFLSCTRL_WRITABLECHECK)
#define RTE_RPGEVTHK_CODEFLSCTRL_SWITCHVALIDAREA    (RPGEVTHK_CODEFLSCTRL_SWITCHVALIDAREA)

#define Rte_RpgEvtHk_PreCodeFlsCtrl                 (RpgEvtHk_PreCodeFlsCtrl)
#define Rte_RpgEvtHk_PostCodeFlsCtrl                (RpgEvtHk_PostCodeFlsCtrl)
#define Rte_RpgEvtHk_SendPositiveResponse           (RpgEvtHk_SendPositiveResponse)
#define Rte_RpgEvtHk_SendNegativeResponse           (RpgEvtHk_SendNegativeResponse)
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
#define Rte_RpgEvtHk_SendPendingResponse            (RpgEvtHk_SendPendingResponse)
#endif
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
#define Rte_RpgEvtHk_SubMicon_UserDataRxIndication  (RpgEvtHk_SubMicon_UserDataRxIndication)
#endif /* ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)) */


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_InitFirst (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_InitLast (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_DeInitFirst (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_DeInitLast (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_RunFirst (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_RunLast (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_MainFunction (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_TimeHigh (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SchEvt_TimeLow (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Def (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Ext (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_SessionEvt_Prg (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_UnlockSec (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_LockSec (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_FlsPrgNotReady (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_FlsPrgReady (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_PreMemErase (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_RpgEvt_PostPrgChk (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_CanStart (void);
#if (REPROG_CFG_ETH_USE == STD_ON)
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_EthStart (void);
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_CxpiStart (void);
#endif
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_AccOn (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_AccOff (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_IgOn (void);
FUNC(void, RTE_CODE_SLOW) Rte_RpgEvtHk_ModeEvt_IgOff (void);
FUNC(uint32, RTE_CODE_SLOW) Rte_RpgEvtHk_ExcptEvt
(
    VAR(uint32, AUTOMATIC) ExcptCode
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* RTE_RPGEVTHK_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/12/03 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

