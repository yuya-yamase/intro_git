/* VehInf_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | VehInf/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <VehInf.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define VEHINF_VOLT_SAMPLE_VALUE    (12000U)    /* Sample Value 12V */
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
#define VEHINF_START_SEC_VAR
#include <VehInf_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint8, VEHINF_VAR_CLEARED) VehInf_VoltFlag;
static VAR(uint16, VEHINF_VAR_CLEARED) VehInf_VoltValueForPrgSession;
static VAR(uint16, VEHINF_VAR_CLEARED) VehInf_VoltValueForDataWrite;
/*===== Sample ===============================================================*/

#define VEHINF_STOP_SEC_VAR
#include <VehInf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define VEHINF_START_SEC_CST
#include <VehInf_MemMap.h>

#define VEHINF_STOP_SEC_CST
#include <VehInf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define VEHINF_START_SEC_CODE
#include <VehInf_MemMap.h>

/******************************************************************************/
/* Function Name | VehInf_Init                                                */
/* Description   | Initializes VehInf                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, VEHINF_CODE_SLOW) VehInf_Init (void)
{
/*===== Sample ===============================================================*/
    VehInf_VoltFlag = STD_OFF;
    VehInf_VoltValueForPrgSession = 0U;
    VehInf_VoltValueForDataWrite = 0U;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | VehInf_DeInit                                              */
/* Description   | Deinitializes VehInf                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, VEHINF_CODE_SLOW) VehInf_DeInit (void)
{
/*===== Sample ===============================================================*/
    VehInf_VoltFlag = STD_OFF;
    VehInf_VoltValueForPrgSession = 0U;
    VehInf_VoltValueForDataWrite = 0U;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | VehInf_Time                                                */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, VEHINF_CODE_SLOW) VehInf_Time (void)
{
/*===== Sample ===============================================================*/
    VehInf_VoltValueForPrgSession = VEHINF_VOLT_SAMPLE_VALUE;
    VehInf_VoltValueForDataWrite = VEHINF_VOLT_SAMPLE_VALUE;
    VehInf_VoltFlag = STD_ON;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | VehInf_MainFunction                                        */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, VEHINF_CODE_SLOW) VehInf_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | VehInf_GetVoltForPrgSession                                */
/* Description   | Acquires voltage value for Programming Session[LSB=0.001V] */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Volt : Voltage value                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, VEHINF_CODE_SLOW) VehInf_GetVoltForPrgSession
(
    P2VAR(uint16, AUTOMATIC, VEHINF_APPL_DATA) Volt
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( VehInf_VoltFlag == (uint8)STD_ON )
    {
        Ret = E_OK;
        *Volt = VehInf_VoltValueForPrgSession;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | VehInf_GetVoltForDataWrite                                 */
/* Description   | Acquires voltage value for Data Write[LSB=0.001V]          */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Volt : Voltage value                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, VEHINF_CODE_SLOW) VehInf_GetVoltForDataWrite
(
    P2VAR(uint16, AUTOMATIC, VEHINF_APPL_DATA) Volt
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( VehInf_VoltFlag == (uint8)STD_ON )
    {
        Ret = E_OK;
        *Volt = VehInf_VoltValueForDataWrite;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define VEHINF_STOP_SEC_CODE
#include <VehInf_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

