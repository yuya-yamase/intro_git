/* SubMiconIf_Main_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SubMiconIf/Main/CODE                                        */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <SubMiconIf.h>


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
#define SUBMICONIF_START_SEC_VAR
#include <SubMiconIf_MemMap.h>

#define SUBMICONIF_STOP_SEC_VAR
#include <SubMiconIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SUBMICONIF_START_SEC_CST
#include <SubMiconIf_MemMap.h>

#define SUBMICONIF_STOP_SEC_CST
#include <SubMiconIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SUBMICONIF_START_SEC_CODE
#include <SubMiconIf_MemMap.h>

/******************************************************************************/
/* Function Name | SubMiconIf_Main_RequestService                             */
/* Description   | Request service for SubMicon                               */
/* Preconditions |                                                            */
/* Parameters    | [IN]    MiconId  : Microcontroller identifier              */
/*               |          SUBMICONIF_ID_SUB_XX [XX:1-31]                    */
/*               | [IN]    ReqInfo  : Request information                     */
/*               | [INOUT] RespInfo : Response information                    */
/*               | [IN]    OpStatus : Operation status                        */
/*               |          SUBMICONIF_INITIAL                                */
/*               |          SUBMICONIF_PENDING                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  SUBMICONIF_E_PENDING                                      */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_Main_RequestService
(
    VAR(uint8, AUTOMATIC) MiconId,
    P2CONST(SubMiconIf_ReqInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) ReqInfo,
    P2VAR(SubMiconIf_RespInfoType, AUTOMATIC, SUBMICONIF_APPL_DATA) RespInfo,
    VAR(SubMiconIf_OpStatusType, AUTOMATIC) OpStatus
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_OK;

    return Result;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | SubMiconIf_Main_NotifyEvent                                */
/* Description   | Notify SubMicon of event                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] User : The user that requests the mode                */
/*               | [IN] Mode : The requested mode                             */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Main_NotifyEvent
(
    VAR(uint16, AUTOMATIC) User,
    VAR(uint16, AUTOMATIC) Mode
)
{
    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SUBMICONIF_STOP_SEC_CODE
#include <SubMiconIf_MemMap.h>

#endif  /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */

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

