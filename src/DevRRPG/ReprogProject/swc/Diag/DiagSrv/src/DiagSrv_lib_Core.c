/* DiagSrv_lib_Core_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/lib/Core/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "DiagSrv_lib_Core.h"
#include "DiagSrv_lib_Core_Cfg.h"


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
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_RewriteAreaNumber;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* Function Name | DiagSrv_GetRewriteAreaNumber                               */
/* Description   | Acquires rewrite area number                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Rewrite area number                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaNumber (void)
{
    return DiagSrv_RewriteAreaNumber;
}

/******************************************************************************/
/* Function Name | DiagSrv_SetRewriteAreaNumber                               */
/* Description   | Sets rewrite area number                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Number : Rewrite area number                          */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_SetRewriteAreaNumber
(
    VAR(uint8, AUTOMATIC) Number
)
{
    DiagSrv_RewriteAreaNumber = Number;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_CheckRewriteArea                                   */
/* Description   | Checks rewrite area number                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum : Rewrite area number                  */
/*               | [IN] CheckAddr      : Check address                        */
/*               | [IN] CheckSize      : Check size                           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_CheckRewriteArea
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint32, AUTOMATIC) CheckAddr,
    VAR(uint32, AUTOMATIC) CheckSize
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0U; i < DiagSrv_RewriteAreaConfig.RewriteInfoNum; i++ )
    {
        if( RewriteAreaNum == DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaNum )
        {
            if( ( CheckAddr == DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaInfo.Addr ) &&
                ( CheckSize == DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaInfo.Size ) )
            {
                Ret = E_OK;
            }
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_CheckSblArea                                       */
/* Description   | Checks sbl area                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] CheckAddr : Check address                             */
/*               | [IN] CheckSize : Check size                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_CheckSblArea
(
    VAR(uint32, AUTOMATIC) CheckAddr,
    VAR(uint32, AUTOMATIC) CheckSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( ( CheckAddr == DiagSrv_SblAreaConfig.Addr ) &&
        ( CheckSize == DiagSrv_SblAreaConfig.Size ) )
    {
        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetRewriteAreaInfo                                 */
/* Description   | Acquires rewrite area                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN]  RewriteAreaNum : Rewrite area number                 */
/*               | [OUT] RewriteAddr    : Rewrite address                     */
/*               | [OUT] RewriteSize    : Rewrite size                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetRewriteAreaInfo
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) RewriteAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) RewriteSize
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < DiagSrv_RewriteAreaConfig.RewriteInfoNum; i++ )
    {
        if( RewriteAreaNum == DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaNum )
        {
            *RewriteAddr = DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaInfo.Addr;
            *RewriteSize = DiagSrv_RewriteAreaConfig.InfoPtr[i].RewriteAreaInfo.Size;
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_GetSblAreaInfo                                     */
/* Description   | Acquires sbl area                                          */
/* Preconditions |                                                            */
/* Parameters    | [OUT] SblAddr : Sbl address                                */
/*               | [OUT] SblSize : Sbl size                                   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_GetSblAreaInfo
(
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) SblAddr,
    P2VAR(uint32, AUTOMATIC, DIAGSRV_APPL_DATA) SblSize
)
{
    *SblAddr = DiagSrv_SblAreaConfig.Addr;
    *SblSize = DiagSrv_SblAreaConfig.Size;

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

