/* RpgEvtHk_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgEvtHk/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgEvtHk.h>
#include <Rte.h>


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
#define RPGEVTHK_START_SEC_VAR
#include <RpgEvtHk_MemMap.h>

/*===== Sample ===============================================================*/
#if ((REPROG_CFG_ETH_USE == STD_ON) && (REPROG_CFG_ETH_DOIP_USE == STD_ON))
VAR(uint8, RPGEVTHK_VAR_CLEARED) RpgEvtHk_EthStartflag;
#endif
/*===== Sample ===============================================================*/

#define RPGEVTHK_STOP_SEC_VAR
#include <RpgEvtHk_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGEVTHK_START_SEC_CST
#include <RpgEvtHk_MemMap.h>

#define RPGEVTHK_STOP_SEC_CST
#include <RpgEvtHk_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RPGEVTHK_START_SEC_CODE
#include <RpgEvtHk_MemMap.h>

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_InitFirst                                  */
/* Description   | Schedule event(First of the initialization process)        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_InitFirst (void)
{
/*===== Sample ===============================================================*/
#if ((REPROG_CFG_ETH_USE == STD_ON) && (REPROG_CFG_ETH_DOIP_USE == STD_ON))
    RpgEvtHk_EthStartflag = STD_OFF;
#endif
/*===== Sample ===============================================================*/
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_InitLast                                   */
/* Description   | Schedule event(Last of the initialization process)         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_InitLast (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_DeInitFirst                                */
/* Description   | Schedule event(First of the deinitialization process)      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_DeInitFirst (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_DeInitLast                                 */
/* Description   | Schedule event(Last of the deinitialization process)       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_DeInitLast (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_RunFirst                                   */
/* Description   | Schedule event(First of the running process)               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_RunFirst (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_RunLast                                    */
/* Description   | Schedule event(Last of the running process)                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_RunLast (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_MainFunction                               */
/* Description   | Schedule event(Base process)                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_TimeHigh                                   */
/* Description   | Schedule event(High priority 1ms timer interrupt)          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_TimeHigh (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SchEvt_TimeLow                                    */
/* Description   | Schedule event(Low priority 1ms timer interrupt)           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SchEvt_TimeLow (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_CanStart                                  */
/* Description   | Mode change event(CAN start)                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_CanStart (void)
{
    return;
}

#if (REPROG_CFG_ETH_USE == STD_ON)
/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_EthStart                                  */
/* Description   | Mode change event(Ether start)                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_EthStart (void)
{
/*===== Sample ===============================================================*/
 #if (REPROG_CFG_ETH_DOIP_USE == STD_ON)
    RpgEvtHk_EthStartflag = STD_ON;
 #endif
/*===== Sample ===============================================================*/

    return;
}
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_CxpiStart                                 */
/* Description   | Mode change event(CXPI start)                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_CxpiStart (void)
{
    return;
}
#endif

/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_AccOn                                     */
/* Description   | Mode change event(ACC ON)                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_AccOn (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_AccOff                                    */
/* Description   | Mode change event(ACC OFF)                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_AccOff (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_IgOn                                      */
/* Description   | Mode change event(IG ON)                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_IgOn (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_ModeEvt_IgOff                                     */
/* Description   | Mode change event(IG OFF)                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_ModeEvt_IgOff (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_ExcptEvt                                          */
/* Description   | Exception event                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] ExcptCode : Exception code                            */
/* Return Value  | Recovery status                                            */
/*               |  RPGEVTHK_EXCPT_RECOVER                                    */
/*               |  RPGEVTHK_EXCPT_UNRECOVER                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, RPGEVTHK_CODE_SLOW) RpgEvtHk_ExcptEvt
(
    VAR(uint32, AUTOMATIC) ExcptCode
)
{
/*===== Sample ===============================================================*/
    return RPGEVTHK_EXCPT_RECOVER;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgEvtHk_PreCodeFlsCtrl                                    */
/* Description   | Before controlling CodeFls                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] Ctrl    : CodeFls control type                        */
/*               |       RPGEVTHK_CODEFLSCTRL_WRITE                           */
/*               |       RPGEVTHK_CODEFLSCTRL_ERASE                           */
/*               |       RPGEVTHK_CODEFLSCTRL_WRITABLECHECK                   */
/*               |       RPGEVTHK_CODEFLSCTRL_SWITCHVALIDAREA                 */
/*               | [IN] Address : Address                                     */
/*               | [IN] Size    : Size                                        */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  RPGEVTHK_E_PENDING                                        */
/* Notes         | - Call with the following combination of arguments.        */
/*               |    | Ctrl            | Address       | Size       |        */
/*               |    ------------------------------------------------        */
/*               |    | WRITE           | Write address | Write size |        */
/*               |    | ERASE           | Erase address | Erase size |        */
/*               |    | WRITABLECHECK   | Check address | Check size |        */
/*               |    | SWITCHVALIDAREA | 0             | 0          |        */
/*               | - Depending on the return value, the caller behaves as     */
/*               |   follows.                                                 */
/*               |    OK      : CodeFls control is started.                   */
/*               |    NOT_OK  : Abnormal termination(Negative response).      */
/*               |    PENDING : Call it again with the same arguments at      */
/*               |              the next base timing.                         */
/******************************************************************************/
FUNC(Std_ReturnType, RPGEVTHK_CODE_SLOW) RpgEvtHk_PreCodeFlsCtrl
(
    VAR(uint8, AUTOMATIC) Ctrl,
    VAR(uint32, AUTOMATIC) Address,
    VAR(uint32, AUTOMATIC) Size
)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgEvtHk_PostCodeFlsCtrl                                   */
/* Description   | After controlling CodeFls                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  RPGEVTHK_E_PENDING                                        */
/* Notes         | Depending on the return value, the caller behaves as       */
/*               | follows.                                                   */
/*               |  OK      : Ends post-processing of CodeFls control.        */
/*               |  NOT_OK  : Abnormal termination(Negative response).        */
/*               |  PENDING : Call at the next base timing.                   */
/******************************************************************************/
FUNC(Std_ReturnType, RPGEVTHK_CODE_SLOW) RpgEvtHk_PostCodeFlsCtrl (void)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SendPositiveResponse                              */
/* Description   | Before sending a positive response                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Sid         : SID                                     */
/*               | [IN] RspData     : Positive response message               */
/*               | [IN] RspDataSize : Positive response message size          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendPositiveResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgEvtHk_SendNegativeResponse                              */
/* Description   | Before sending a negative response                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Sid         : SID                                     */
/*               | [IN] RspData     : Negative response message               */
/*               | [IN] RspDataSize : Negative response message size          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendNegativeResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
)
{
    return;
}

#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
/******************************************************************************/
/* Function Name | RpgEvtHk_SendPendingResponse                               */
/* Description   | Before sending a pending response                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] Sid         : SID                                     */
/*               | [IN] RspData     : Pending response message                */
/*               | [IN] RspDataSize : Pending response message size           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SendPendingResponse
(
    VAR(uint8, AUTOMATIC) Sid,
    P2CONST(uint8, AUTOMATIC, RPGEVTHK_APPL_CONST) RspData,
    VAR(uint16, AUTOMATIC) RspDataSize
)
{
    return;
}
#endif

#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
/******************************************************************************/
/* Function Name | RpgEvtHk_SubMicon_UserDataRxIndication                     */
/* Description   | Indication of Rx user data                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] UserDataInfo : Information about user data            */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(void, RPGEVTHK_CODE_SLOW) RpgEvtHk_SubMicon_UserDataRxIndication
(
    P2CONST(Rte_SubMiconIf_UserDataInfoType, AUTOMATIC, RPGEVTHK_APPL_CONST) UserDataInfo
)
{
    return;
}
#endif /* ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)) */


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
#define RPGEVTHK_STOP_SEC_CODE
#include <RpgEvtHk_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*  v2.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

