/* Dcm_DcmMain_TmrSrv_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/DcmMain_TmrSrv/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include <SchM_Dcm.h>

#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Main_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_MAIN_TMRSRV_CLR_TMRCNT      ((uint8)0x00U)  /* Queue position init */
#define DCM_MAIN_TMRSRV_CLR_TMRSTS      STD_OFF         /* Quene count init */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct                                      /* Timer infomation     */
{
    uint32  u4TmrCount;                             /* Timer count          */
    uint8   u1TmrState;                             /* Timer state          */
}Dcm_Main_TmrSrv_TmrInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_Main_TmrSrv_TmrInfoType, DCM_VAR_NO_INIT ) Dcm_Main_TmrSrv_stTmrInfo[DCM_M_TMRSRV_ID_NUM];
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Main_TmrSrv_u1TimeoutList[DCM_M_TMRSRV_ID_NUM];

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_Main_TmrSrv_Init                                     */
/* Description   | Timer service init                                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_Init
( void )
{
    uint8   u1_Index;
    uint8   u1_TmrSrvIdNum;

    u1_TmrSrvIdNum = Dcm_M_TmrSrv_u1IdNum;

    /* Timer infomation init */
    for( u1_Index = 0U; u1_Index < u1_TmrSrvIdNum; u1_Index++ )
    {
        Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u4TmrCount = DCM_MAIN_TMRSRV_CLR_TMRCNT;
        Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState = DCM_MAIN_TMRSRV_CLR_TMRSTS;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_TmrSrv_Main                                     */
/* Description   | Timer service periodic function                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_Main
( void )
{
    uint8   u1_TimerId;
    uint8   u1_TimeoutNum;
    uint8   u1_TimeoutIndex;
    uint8   u1_TmrState;
    uint8   u1_Index;
    uint8   u1_TmrSrvIdNum;
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_TmrState;

    u1_TimeoutNum = (uint8)0U;
    u1_TmrSrvIdNum = Dcm_M_TmrSrv_u1IdNum;

    /* Lock */
    SchM_Enter_Dcm_Main_TmrSrv();

    for( u1_Index = (uint8)0U; u1_Index < u1_TmrSrvIdNum; u1_Index++ )
    {
        /* RAM Refresh */
        pt_TmrState  = &Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState;
        u1_TmrState  = *pt_TmrState;
        *pt_TmrState = u1_TmrState;

        if( Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState == (uint8)STD_ON )
        {
            if( Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u4TmrCount < Dcm_M_General.u4TaskTime )
            {
                Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState = STD_OFF;
                Dcm_Main_TmrSrv_u1TimeoutList[u1_TimeoutNum] = u1_Index;
                u1_TimeoutNum = (uint8)(u1_TimeoutNum + (uint8)1U);
            }
            else
            {
                Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u4TmrCount -= Dcm_M_General.u4TaskTime; /* no wrap around */
            }
        }
    }

    /* Unlock */
    SchM_Exit_Dcm_Main_TmrSrv();

    for( u1_TimeoutIndex = (uint8)0U; u1_TimeoutIndex < u1_TimeoutNum; u1_TimeoutIndex++ )
    {
        u1_Index = Dcm_Main_TmrSrv_u1TimeoutList[u1_TimeoutIndex];

        u1_TimerId = Dcm_M_TmrSrv_NoticeTable[u1_Index].u1TimerId;

#ifndef JGXSTACK
        Dcm_M_TmrSrv_NoticeTable[u1_Index].ptFnc( u1_TimerId );
#else /* JGXSTACK */
        Dcm_Stack_TmrSrvNoticeFunc( u1_TimerId );
#endif /* JGXSTACK */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_TmrSrv_StartTimer                               */
/* Description   | Timer Start                                              */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1TimerId      : Timer ID                           */
/*               | [in] u4TimeoutValue : Timeout value                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_StartTimer
(
    const uint8 u1TimerId,
    const uint32 u4TimeoutValue
)
{
    uint8   u1_Index;
    uint8   u1_TmrSrvIdNum;

    u1_TmrSrvIdNum = Dcm_M_TmrSrv_u1IdNum;

    if( u1TimerId < DCM_M_TMRSRV_DEFINED_ALL_ID_NUM )
    {
        u1_Index = Dcm_M_TmrSrv_IdToIndex[u1TimerId];

        if( u1_Index < u1_TmrSrvIdNum )
        {
            /* Lock */
            SchM_Enter_Dcm_Main_TmrSrv();

            Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u4TmrCount = (uint32)( u4TimeoutValue + ( Dcm_M_General.u4TaskTime - (uint32)1U ) );    /* no wrap around */
            Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState = STD_ON;

            /* Unlock */
            SchM_Exit_Dcm_Main_TmrSrv();
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_TmrSrv_StopTimer                                */
/* Description   | Timer Stop                                               */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1TimerId      : Timer ID                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_StopTimer
(
    const uint8 u1TimerId
)
{
    uint8   u1_Index;
    uint8   u1_TmrSrvIdNum;

    u1_TmrSrvIdNum = Dcm_M_TmrSrv_u1IdNum;

    if( u1TimerId < DCM_M_TMRSRV_DEFINED_ALL_ID_NUM )
    {
        u1_Index = Dcm_M_TmrSrv_IdToIndex[u1TimerId];

        if( u1_Index < u1_TmrSrvIdNum )
        {
            /* Lock */
            SchM_Enter_Dcm_Main_TmrSrv();

            Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState = STD_OFF;

            /* Unlock */
            SchM_Exit_Dcm_Main_TmrSrv();
        }
    }

    return;
}

#if( DCM_AUTHENTICATION_USE == STD_ON  )
/****************************************************************************/
/* Function Name | Dcm_Main_TmrSrv_GetTimerState                            */
/* Description   | Get Timer State by Timer ID                              */
/* Preconditions | None                                                     */
/* Parameters    | [in]  u1TimerId      : Timer ID                          */
/*               | [out] ptTmrState     : Timer State                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK  : Successed to retrieve the Timer State          */
/*               |   E_NOT_OK : Failed to retrieve the Timer State          */
/* Notes         | Currently, only use for the authentication timer,        */
/*               | thus the compile swtich is used.                         */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_TmrSrv_GetTimerState
(
    const uint8 u1TimerId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTmrState
)
{
    Std_ReturnType u1_Result;
    uint8 u1_Index;
    uint8 u1_TmrSrvIdNum;
    uint8 u1_RetrievedTmrState;
    

    u1_TmrSrvIdNum = Dcm_M_TmrSrv_u1IdNum;
    *ptTmrState = (uint8)STD_OFF;
    u1_Result = (Std_ReturnType)E_NOT_OK;

    if( u1TimerId < DCM_M_TMRSRV_DEFINED_ALL_ID_NUM )
    {
        u1_Index = Dcm_M_TmrSrv_IdToIndex[u1TimerId];

        if( u1_Index < u1_TmrSrvIdNum )
        {
            
            /* Lock */
            SchM_Enter_Dcm_Main_TmrSrv();

            u1_RetrievedTmrState = Dcm_Main_TmrSrv_stTmrInfo[u1_Index].u1TmrState;

            /* Unlock */
            SchM_Exit_Dcm_Main_TmrSrv();

            if( u1_RetrievedTmrState == (uint8)STD_ON )
            {
                *ptTmrState = (uint8)STD_ON;
                u1_Result = (Std_ReturnType)E_OK;
            }
            else if( u1_RetrievedTmrState == (uint8)STD_OFF )
            {
                *ptTmrState = (uint8)STD_OFF;
                u1_Result = (Std_ReturnType)E_OK;
            }
            else
            {
                /* No process */
            }
        }
    }

    return u1_Result;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
