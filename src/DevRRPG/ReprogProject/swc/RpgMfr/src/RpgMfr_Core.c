/* RpgMfr_Core_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgMfr/Core/CODE                                            */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgMfr.h>
#include "RpgMfr_Local.h"
#include "RpgMfr_Cfg.h"


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
#define RPGMFR_START_SEC_VAR
#include <RpgMfr_MemMap.h>

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
/* Function Name | RpgMfr_VoltCheckConditionForPrgSession                     */
/* Description   | Voltage Check for Programming Session                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Volt : Voltage [LSB=0.001V]                           */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_VTL                                              */
/*               |  DIAG_NRC_PR                                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_VoltCheckConditionForPrgSession
(
    VAR(uint16, AUTOMATIC) Volt
)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_PR;

    if( Volt < RpgMfr_VoltageInfoConfig.LowerLimit )
    {
        Nrc = DIAG_NRC_VTL;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | RpgMfr_ApEntryCheck                                        */
/* Description   | Checks startup procedures from APL                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Sid     : SID                                        */
/*               | [OUT] RespFlg : Response flag                              */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGMFR_CODE_SLOW) RpgMfr_ApEntryCheck
(
    VAR(uint8, AUTOMATIC) Sid,
    P2VAR(uint8, AUTOMATIC, RPGMFR_APPL_DATA) RespFlg
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( RespFlg != NULL_PTR )
    {
        if( Sid == RpgMfr_ApEntryInfoConfig.Sid )
        {
            *RespFlg = RpgMfr_ApEntryInfoConfig.Response;
            Ret = E_OK;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define RPGMFR_STOP_SEC_CODE
#include <RpgMfr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

