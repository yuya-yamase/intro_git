/* IdsM_Event_c_v2-0-1                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/Event/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include "../inc/IdsM_Cfg_Fixed.h"
#include "../inc/IdsM_Event.h"
#include "../inc/IdsM_Std.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_EVEBUF_CNT ((uint16)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2SetEveCnt;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2EveBuffHead;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2EveBuffTail;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2SetEveCntRed;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2EveBuffHeadRed;
static VAR(volatile uint16, IDSM_VAR_NO_INIT) IdsM_Event_u2EveBuffTailRed;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

#define IDSM_STOP_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define IDSM_START_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* Function Name | IdsM_Event_Init                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Event_Init
(
    void
)
{
    IdsM_Event_u2SetEveCnt = 0U;
    IdsM_Event_u2EveBuffHead = 0U;
    IdsM_Event_u2EveBuffTail = 0U;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Event_u2SetEveCntRed = IDSM_RED_INIT_U2;
    IdsM_Event_u2EveBuffHeadRed = IDSM_RED_INIT_U2;
    IdsM_Event_u2EveBuffTailRed = IDSM_RED_INIT_U2;
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Event_SetBuff                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptData :                                                 */
/* Return Value  | Std_ReturnType                                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, IDSM_CODE) IdsM_Event_SetBuff
(
    P2CONST(IdsMEventBuffType, AUTOMATIC, AUTOMATIC) ptData
)
{
    Std_ReturnType ud_StdRet = (Std_ReturnType)E_NOT_OK;
    uint16 u2_SetEveCnt      = IdsM_Event_u2SetEveCnt;
    uint16 u2_EveBuffTail    = IdsM_Event_u2EveBuffTail;
    P2VAR(volatile IdsMEventBuffType, AUTOMATIC, IDSM_VAR_NO_INIT) pt_EventBuff;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    uint16 u2_SetEveCntRed   = IdsM_Event_u2SetEveCntRed;
    uint16 u2_EveBuffTailRed = IdsM_Event_u2EveBuffTailRed;

    if( ( u2_SetEveCnt   == (uint16)(~u2_SetEveCntRed) ) &&
        ( u2_EveBuffTail == (uint16)(~u2_EveBuffTailRed) ) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        if( u2_SetEveCnt < IdsM_Cfg_EventBuffAcss.u2ConfigNum )
        {
            pt_EventBuff = IdsM_Cfg_EventBuffAcss.ptEventBuff;
            IdsM_Std_EventBuffCopy(&pt_EventBuff[u2_EveBuffTail], ptData);

            if(( u2_EveBuffTail + IDSM_EVEBUF_CNT ) >= IdsM_Cfg_EventBuffAcss.u2ConfigNum )
            {
                u2_EveBuffTail = 0U;
            }
            else
            {
                u2_EveBuffTail++;
            }
            u2_SetEveCnt++;
            IdsM_Event_u2SetEveCnt = u2_SetEveCnt;
            IdsM_Event_u2EveBuffTail = u2_EveBuffTail;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
            IdsM_Event_u2SetEveCntRed = (uint16)(~u2_SetEveCnt);
            IdsM_Event_u2EveBuffTailRed = (uint16)(~u2_EveBuffTail);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
            ud_StdRet = E_OK;
        }
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    }
    else
    {
        IdsM_General_SetRamError();
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    return ud_StdRet;
}

/****************************************************************************/
/* Function Name | IdsM_Event_GetSEvNum                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint16                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint16, IDSM_CODE) IdsM_Event_GetSEvNum 
(
    void
)
{
    uint16 u2_SetEveCnt    = IdsM_Event_u2SetEveCnt;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    uint16 u2_SetEveCntRed = IdsM_Event_u2SetEveCntRed;
    
    if( u2_SetEveCnt != (uint16)(~u2_SetEveCntRed) )
    {
        IdsM_General_SetRamError();
        u2_SetEveCnt = 0U;
        IdsM_Event_u2SetEveCnt = u2_SetEveCnt;
        IdsM_Event_u2SetEveCntRed = IDSM_RED_INIT_U2;
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
    return u2_SetEveCnt;
}

/****************************************************************************/
/* Function Name | IdsM_Event_GetSEvInfo                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                                                  */
/*               | ptData                                                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Event_GetSEvInfo 
(
    P2VAR(IdsMEventBuffType, AUTOMATIC, IDSM_APPL_DATA) ptData
)
{
    uint16 u2_EveBuffHead    = IdsM_Event_u2EveBuffHead;
    P2CONST(volatile IdsMEventBuffType, AUTOMATIC, IDSM_VAR_NO_INIT) pt_EventBuff;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    uint16 u2_EveBuffHeadRed = IdsM_Event_u2EveBuffHeadRed;

    if( u2_EveBuffHead == (uint16)(~u2_EveBuffHeadRed) )
    {
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */
        pt_EventBuff = IdsM_Cfg_EventBuffAcss.ptEventBuff;
        IdsM_Std_EventBuffCopy(ptData, &pt_EventBuff[u2_EveBuffHead]);

        if(( u2_EveBuffHead + IDSM_EVEBUF_CNT ) >= IdsM_Cfg_EventBuffAcss.u2ConfigNum )
        {
            u2_EveBuffHead = 0U;
        }
        else
        {
            u2_EveBuffHead++;
        }
        IdsM_Event_u2EveBuffHead = u2_EveBuffHead;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
        IdsM_Event_u2EveBuffHeadRed = (uint16)(~u2_EveBuffHead);
    }
    else
    {
        IdsM_General_SetRamError();
    }
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | IdsM_Event_ClearBuff                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, IDSM_CODE) IdsM_Event_ClearBuff
(
    uint16 u2EveBuffNum
)
{
    uint16 u2_SetEveCnt = IdsM_Event_u2SetEveCnt;
    
    u2_SetEveCnt -= u2EveBuffNum;
    IdsM_Event_u2SetEveCnt = u2_SetEveCnt;
#if (IDSM_CFG_RAM_ERROR_CHECK == STD_ON)
    IdsM_Event_u2SetEveCntRed = (uint16)(~u2_SetEveCnt);
#endif /* ( IDSM_CFG_RAM_ERROR_CHECK == STD_ON ) */

    
    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define IDSM_STOP_SEC_CODE
#include <IdsM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/04/10                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
