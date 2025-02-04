/* RpgEvtHk_h_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgEvtHk/HEADER                                             */
/******************************************************************************/
#ifndef RPGEVTHK_H
#define RPGEVTHK_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
#include <Rte.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RPGEVTHK_E_PENDING          ((Std_ReturnType)2U)

#define RPGEVTHK_EXCPT_RECOVER      (0UL)
#define RPGEVTHK_EXCPT_UNRECOVER    (1UL)

#define RPGEVTHK_CODEFLSCTRL_WRITE              ((uint8)0U)
#define RPGEVTHK_CODEFLSCTRL_ERASE              ((uint8)1U)
#define RPGEVTHK_CODEFLSCTRL_WRITABLECHECK      ((uint8)2U)
#define RPGEVTHK_CODEFLSCTRL_SWITCHVALIDAREA    ((uint8)3U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_InitFirst (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_InitLast (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_DeInitFirst (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_DeInitLast (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_RunFirst (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_RunLast (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_MainFunction (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_TimeHigh (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_TimeLow (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_CanStart (void);
#if (REPROG_CFG_ETH_USE == STD_ON)
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_EthStart (void);
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_CxpiStart (void);
#endif
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_AccOn (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_AccOff (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_IgOn (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_IgOff (void);
FUNC(uint32, RPGEVTHK_CODE_SLOW) RpgEvtHk_ExcptEvt
(
    VAR(uint32, AUTOMATIC) ExcptCode
);
FUNC(Std_ReturnType, RPGEVTHK_CODE_SLOW) RpgEvtHk_PreCodeFlsCtrl
(
    VAR(uint8, AUTOMATIC) Ctrl,
    VAR(uint32, AUTOMATIC) Address,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(Std_ReturnType, RPGEVTHK_CODE_SLOW) RpgEvtHk_PostCodeFlsCtrl (void);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendPositiveResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
);
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendNegativeResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
);
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendPendingResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
);
#endif
#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SubMicon_UserDataRxIndication
(
    P2CONST(Rte_SubMiconIf_UserDataInfoType, AUTOMATIC, RPGEVTHK_APPL_CONST) UserDataInfo
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define RPGEVTHK_START_SEC_VAR
#include <RpgEvtHk_MemMap.h>

#if ((REPROG_CFG_ETH_USE == STD_ON) && (REPROG_CFG_ETH_DOIP_USE == STD_ON))
extern VAR(uint8, RPGEVTHK_VAR_CLEARED) RpgEvtHk_EthStartflag;
#endif

#define RPGEVTHK_STOP_SEC_VAR
#include <RpgEvtHk_MemMap.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGEVTHK_START_SEC_CST
#include <RpgEvtHk_MemMap.h>

#define RPGEVTHK_STOP_SEC_CST
#include <RpgEvtHk_MemMap.h>


#endif /* RPGEVTHK_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*  v2.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

