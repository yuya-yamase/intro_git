/* SubMiconIf_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SubMiconIf/CODE                                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON))
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
/* Function Name | SubMiconIf_Init                                            */
/* Description   | Initializes SubMiconIf                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Init (void)
{
    return;
}

/******************************************************************************/
/* Function Name | SubMiconIf_DeInit                                          */
/* Description   | Deinitializes SubMiconIf                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_DeInit (void)
{
    return;
}

/******************************************************************************/
/* Function Name | SubMiconIf_MainFunction                                    */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | SubMiconIf_Time                                            */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(void, SUBMICONIF_CODE_SLOW) SubMiconIf_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | SubMiconIf_UserDataTransmit                                */
/* Description   | UserData Transmit                                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] MiconId      : Microcontroller identifier             */
/*               |       SUBMICONIF_ID_MAIN                                   */
/*               |       SUBMICONIF_ID_SUB_XX [XX:1-31]                       */
/*               | [IN] UserDataInfo : User data                              */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function is valid when either of the following is     */
/*               | defined.                                                   */
/*               |  * REPROG_CFG_SUBMICON_USE_MAIN                            */
/*               |  * REPROG_CFG_SUBMICON_USE_SUB                             */
/******************************************************************************/
FUNC(Std_ReturnType, SUBMICONIF_CODE_SLOW) SubMiconIf_UserDataTransmit
(
    VAR(uint8, AUTOMATIC) MiconId,
    P2CONST(SubMiconIf_UserDataInfoType, AUTOMATIC, SUBMICONIF_APPL_CONST) UserDataInfo
)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SUBMICONIF_STOP_SEC_CODE
#include <SubMiconIf_MemMap.h>

#endif  /* ((REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) || (REPROG_CFG_SUBMICON_USE_SUB == STD_ON)) */

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

