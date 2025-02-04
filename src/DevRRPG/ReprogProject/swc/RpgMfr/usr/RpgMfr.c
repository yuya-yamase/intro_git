/* RpgMfr_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgMfr/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgMfr.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define RPGMFR_VOLT_LOWERLIMIT_VALUE    ((uint16)10000U)    /* Sample Value 10V */
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RPGMFR_START_SEC_VAR
#include <RpgMfr_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint8, RPGMFR_VAR_CLEARED) RpgMfr_InitFlag;
/*===== Sample ===============================================================*/

#define RPGMFR_STOP_SEC_VAR
#include <RpgMfr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGMFR_START_SEC_CST
#include <RpgMfr_MemMap.h>

#define RPGMFR_STOP_SEC_CST
#include <RpgMfr_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RPGMFR_START_SEC_CODE
#include <RpgMfr_MemMap.h>

/******************************************************************************/
/* Function Name | RpgMfr_Init                                                */
/* Description   | Initializes RpgMfr                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_Init (void)
{
/*===== Sample ===============================================================*/
    RpgMfr_InitFlag = STD_ON;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | RpgMfr_DeInit                                              */
/* Description   | Deinitializes RpgMfr                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_DeInit (void)
{
/*===== Sample ===============================================================*/
    RpgMfr_InitFlag = STD_OFF;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | RpgMfr_Time                                                */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgMfr_MainFunction                                        */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgMfr_CommonCheckCondition                                */
/* Description   | Service Common Check                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/* Notes         | [ISO 14229-1:2020(E)][Figure 5]                            */
/*               |   - manufacturer specific failure detected?                */
/******************************************************************************/
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_CommonCheckCondition (void)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    if( RpgMfr_InitFlag == (uint8)STD_ON )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgMfr_MsgCheckCondition                                   */
/* Description   | Service Specific Check                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | NRC                                                        */
/* Notes         | [ISO 14229-1:2020(E)]                                      */
/*               |   - manufacturer specific check                            */
/******************************************************************************/
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_MsgCheckCondition
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, RPGMFR_APPL_CONST) Msg
)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_GR;

    if( (RpgMfr_InitFlag == (uint8)STD_ON) && (Msg != NULL_PTR) )
    {
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | RpgMfr_VoltCheckConditionForDataWrite                      */
/* Description   | Voltage Check for Data Write                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Volt : Voltage [LSB=0.001V]                           */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_VoltCheckConditionForDataWrite
(
    VAR(uint16, AUTOMATIC) Volt
)
{
/*===== Sample ===============================================================*/
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    if( RpgMfr_InitFlag == (uint8)STD_ON )
    {
        if( Volt < RPGMFR_VOLT_LOWERLIMIT_VALUE )
        {
            Nrc = DIAG_NRC_VTL;
        }
    }
    else
    {
        Nrc = DIAG_NRC_GR;
    }

    return Nrc;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RPGMFR_STOP_SEC_CODE
#include <RpgMfr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

