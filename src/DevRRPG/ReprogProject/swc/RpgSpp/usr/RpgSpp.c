/* RpgSpp_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgSpp/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgSpp.h>


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
#define RPGSPP_START_SEC_VAR
#include <RpgSpp_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint8, RPGSPP_VAR_CLEARED) RpgSpp_InitFlag;
/*===== Sample ===============================================================*/

#define RPGSPP_STOP_SEC_VAR
#include <RpgSpp_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGSPP_START_SEC_CST
#include <RpgSpp_MemMap.h>

#define RPGSPP_STOP_SEC_CST
#include <RpgSpp_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RPGSPP_START_SEC_CODE
#include <RpgSpp_MemMap.h>

/******************************************************************************/
/* Function Name | RpgSpp_Init                                                */
/* Description   | Initializes RpgSpp                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGSPP_CODE_SLOW) RpgSpp_Init (void)
{
/*===== Sample ===============================================================*/
    RpgSpp_InitFlag = STD_ON;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | RpgSpp_DeInit                                              */
/* Description   | Deinitializes RpgSpp                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGSPP_CODE_SLOW) RpgSpp_DeInit (void)
{
/*===== Sample ===============================================================*/
    RpgSpp_InitFlag = STD_OFF;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | RpgSpp_Time                                                */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGSPP_CODE_SLOW) RpgSpp_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgSpp_MainFunction                                        */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGSPP_CODE_SLOW) RpgSpp_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgSpp_SidCheckCondition                                   */
/* Description   | Service Common Check                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Sid : SID                                             */
/* Return Value  | NRC                                                        */
/* Notes         | [ISO 14229-1:2020(E)][Figure 5]                            */
/*               |   - supplier specific failure detected?                    */
/******************************************************************************/
FUNC(uint8, RPGSPP_CODE_SLOW) RpgSpp_SidCheckCondition
(
    VAR(uint8, AUTOMATIC) Sid
)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    if( RpgSpp_InitFlag == (uint8)STD_ON )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgSpp_MsgCheckCondition                                   */
/* Description   | Service Specific Check                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | NRC                                                        */
/* Notes         | [ISO 14229-1:2020(E)]                                      */
/*               |   - supplier specific check                                */
/******************************************************************************/
FUNC(uint8, RPGSPP_CODE_SLOW) RpgSpp_MsgCheckCondition
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, RPGSPP_APPL_CONST) Msg
)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    if( (RpgSpp_InitFlag == (uint8)STD_ON) && (Msg != NULL_PTR) )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RPGSPP_STOP_SEC_CODE
#include <RpgSpp_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

