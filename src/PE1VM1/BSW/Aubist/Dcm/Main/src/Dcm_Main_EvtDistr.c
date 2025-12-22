/* Dcm_DcmMain_EvtDistr_c(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/DcmMain_EvtDistr/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Main_EvtDistr.h>

#include <Dcm.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_MAIN_EVTDISTR_CLR_QUEPOS    ((uint8)0x00U)  /* Queue position init */
#define DCM_MAIN_EVTDISTR_CLR_QUECNT    ((uint8)0x00U)  /* Quene count init */
#define DCM_M_EVTDISTR_ID_EX_INDEX_CALC ((uint8)235U)   /* Extend Service index calculation */
#define DCM_M_EVTDISTR_ID_EX_MIN        ((uint8)235U)   /* Extend Event ID Min */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct                                      /* Event queue infomation */
{
    uint8   u1WritePos;                             /* Write position       */
    uint8   u1ReadPos;                              /* Read position        */
    uint8   u1Count;                                /* Queue count          */
}Dcm_Main_EvtDistr_EvtInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Main_EvtDistr_CheckEventId
(
    const uint8 u1EventId
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_Main_EvtDistr_EvtInfoType, DCM_VAR_NO_INIT ) Dcm_Main_EvtDistr_stEvtInfo;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Main_EvtDistr_u1EvtQueue[ DCM_M_EVTDISTR_QUEUE_MAX ];

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
/* Function Name | Dcm_Main_EvtDistr_Init                                   */
/* Description   | Event distributor init                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_EvtDistr_Init
( void )
{
    /* Event infomation init */
    Dcm_Main_EvtDistr_stEvtInfo.u1WritePos = DCM_MAIN_EVTDISTR_CLR_QUEPOS;
    Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos  = DCM_MAIN_EVTDISTR_CLR_QUEPOS;
    Dcm_Main_EvtDistr_stEvtInfo.u1Count    = DCM_MAIN_EVTDISTR_CLR_QUECNT;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_EvtDistr_Main                                   */
/* Description   | Event distributor periodic function                      */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Main_EvtDistr_Main
( void )
{
    P2VAR(volatile uint8, AUTOMATIC, DCM_APPL_DATA) pt_EvtInfoCount;
    uint8   u1_QueNum;
    uint8   u1_EventId;
    uint8   u1_QueCnt;
    uint8   u1_EventIdExIndex;
    uint8   u1_EvtInfoCount;
    uint8   u1_EventIdNum;
    uint8   u1_EventIdExNum;
    uint8   u1_Index;
    uint8   u1_CalcNumOfEvents;
    uint8   u1_EvtInfoWritePos;
    uint8   u1_EvtInfoReadPos;

    /* Lock */
    SchM_Enter_Dcm_Main_EvtDistr();

    /* RAM Refresh */
    pt_EvtInfoCount  = &Dcm_Main_EvtDistr_stEvtInfo.u1Count;
    u1_EvtInfoCount  = *pt_EvtInfoCount;
    *pt_EvtInfoCount = u1_EvtInfoCount;

    u1_EvtInfoWritePos  = Dcm_Main_EvtDistr_stEvtInfo.u1WritePos;
    u1_EvtInfoReadPos   = Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos;

    /* Check whether the relationship between u1WritePos, u1ReadPos, and u1Count is broken. */
    if( u1_EvtInfoWritePos >= u1_EvtInfoReadPos )
    {
        u1_CalcNumOfEvents = (uint8)(u1_EvtInfoWritePos - u1_EvtInfoReadPos);
    }
    else
    {
        /* u1WritePos goes beyond the last element of the ring buffer. */
        u1_CalcNumOfEvents = (uint8)(( DCM_M_EVTDISTR_QUEUE_MAX + u1_EvtInfoWritePos ) - u1_EvtInfoReadPos);
    }
    if( u1_EvtInfoCount == u1_CalcNumOfEvents )
    {
        /* No Proc because correct */
    }
    else
    {
        /* If the relationship is broken, initialize the data */
        Dcm_Main_EvtDistr_stEvtInfo.u1WritePos  = (uint8)0U;
        Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos   = (uint8)0U;
        Dcm_Main_EvtDistr_stEvtInfo.u1Count     = (uint8)0U;
    }

    /* Unlock */
    SchM_Exit_Dcm_Main_EvtDistr();

    u1_QueNum = Dcm_Main_EvtDistr_stEvtInfo.u1Count;
    u1_EventId = DCM_M_EVTDISTR_ID_DELETED;
    u1_QueCnt = (uint8)0U;

    u1_EventIdNum = Dcm_M_EvtDistr_u1EventIdNum;
    u1_EventIdExNum = Dcm_M_EvtDistr_u1EventIdExNum;

    /* Dequeue */
    while( ( u1_QueCnt < u1_QueNum ) &&
           ( ( (uint8)DCM_M_EVTDISTR_DEQUEUENUM == (uint8)0U ) || ( u1_QueCnt < DCM_M_EVTDISTR_DEQUEUENUM ) ) )
    {
        u1_QueCnt = (uint8)(u1_QueCnt + (uint8)1U);

        /* Lock */
        SchM_Enter_Dcm_Main_EvtDistr();

        if( Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos < DCM_M_EVTDISTR_QUEUE_MAX )
        {
            u1_EventId = Dcm_Main_EvtDistr_u1EvtQueue[ Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos ];
            Dcm_Main_EvtDistr_u1EvtQueue[ Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos ] = DCM_M_EVTDISTR_ID_DELETED;
        }

        /* Read position update */
        if( Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos >= (uint8)( DCM_M_EVTDISTR_QUEUE_MAX - (uint8)1U ) )
        {
            Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos = (uint8)0U;
        }
        else
        {
            Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos = (uint8)(Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos + (uint8)1U);
        }

        Dcm_Main_EvtDistr_stEvtInfo.u1Count = (uint8)(Dcm_Main_EvtDistr_stEvtInfo.u1Count - (uint8)1U);

        /* Unlock */
        SchM_Exit_Dcm_Main_EvtDistr();

        if( u1_EventId != DCM_M_EVTDISTR_ID_DELETED )
        {
            if( u1_EventId < DCM_M_EVTDISTR_ID_EX_MIN )
            {
                if( u1_EventId < DCM_M_EVTDISTR_DEFINED_ALL_ID_NUM )
                {
                    u1_Index = Dcm_M_EvtDistr_IdToIndex[u1_EventId];

                    if( u1_Index < u1_EventIdNum )
                    {
#ifndef JGXSTACK
                        Dcm_M_EvtDistr_NoticeTable[u1_Index]( u1_EventId );
#else /* JGXSTACK */
                        Dcm_Stack_EvtDistrNoticeFunc( u1_EventId );
#endif /* JGXSTACK */
                    }
                }
            }
            else
            {
                u1_EventIdExIndex = u1_EventId - DCM_M_EVTDISTR_ID_EX_INDEX_CALC;
                if( u1_EventIdExIndex < u1_EventIdExNum )
                {
#ifndef JGXSTACK
                    Dcm_M_EvtDistr_NoticeTable_Ex[u1_EventIdExIndex]( u1_EventId );
#else /* JGXSTACK */
                /* user-defined */
#endif /* JGXSTACK */
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Main_EvtDistr_SendEvent                              */
/* Description   | Event distributor send event                             */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1EventId : Event ID                                */
/* Return Value  | Dcm_Main_EvtDistr_RetType                                */
/*               |   DCM_MAIN_EVTDISTR_E_OK       :OK                       */
/*               |   DCM_MAIN_EVTDISTR_E_ID       :Invalid ID               */
/*               |   DCM_MAIN_EVTDISTR_E_OVERFLOW :Queue overflow           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dcm_Main_EvtDistr_RetType, DCM_CODE ) Dcm_Main_EvtDistr_SendEvent
(
    const uint8 u1EventId
)
{
    Dcm_Main_EvtDistr_RetType   u1_RetVal;
    Std_ReturnType              u1_RetCheckEvtId;

    u1_RetVal = DCM_MAIN_EVTDISTR_E_ID;

    u1_RetCheckEvtId = Dcm_Main_EvtDistr_CheckEventId(u1EventId);

    /* Event ID check */
    if( u1_RetCheckEvtId == (Std_ReturnType)E_OK )
    {
        /* Lock */
        SchM_Enter_Dcm_Main_EvtDistr();

        /* Queue overflow check */
        if( Dcm_Main_EvtDistr_stEvtInfo.u1Count < (uint8)DCM_M_EVTDISTR_QUEUE_MAX )
        {
            /* Enqueue */
            u1_RetVal = DCM_MAIN_EVTDISTR_E_OK;

            if( Dcm_Main_EvtDistr_stEvtInfo.u1WritePos < DCM_M_EVTDISTR_QUEUE_MAX )
            {
                Dcm_Main_EvtDistr_u1EvtQueue[ Dcm_Main_EvtDistr_stEvtInfo.u1WritePos ] = u1EventId;
            }

            /* Write position update */
            if( Dcm_Main_EvtDistr_stEvtInfo.u1WritePos >= (uint8)( DCM_M_EVTDISTR_QUEUE_MAX - (uint8)1U ) )
            {
                Dcm_Main_EvtDistr_stEvtInfo.u1WritePos = (uint8)0U;
            }
            else
            {
                Dcm_Main_EvtDistr_stEvtInfo.u1WritePos = (uint8)(Dcm_Main_EvtDistr_stEvtInfo.u1WritePos + (uint8)1U);
            }

            Dcm_Main_EvtDistr_stEvtInfo.u1Count = (uint8)(Dcm_Main_EvtDistr_stEvtInfo.u1Count + (uint8)1U);
        }
        else
        {
            u1_RetVal = DCM_MAIN_EVTDISTR_E_OVERFLOW;
        }

        /* Unlock */
        SchM_Exit_Dcm_Main_EvtDistr();
    }

    return ( u1_RetVal );
}


/****************************************************************************/
/* Function Name | Dcm_Main_EvtDistr_DeleteEvent                            */
/* Description   | Event distributor delete event                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1DelEvendId : Event ID                             */
/*               | [in] bOneEntry : Delete Entry One(TRUE) or All(FALSE)    */
/* Return Value  | Dcm_Main_EvtDistr_RetType                                */
/*               |   DCM_MAIN_EVTDISTR_E_OK       :ID Detele OK             */
/*               |   DCM_MAIN_EVTDISTR_E_ID       :ID Not Found             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Dcm_Main_EvtDistr_RetType, DCM_CODE ) Dcm_Main_EvtDistr_DeleteEvent
(
    const uint8   u1DelEvendId,
    const boolean bOneEntry
)
{
    uint8                       u1_QueNum;
    uint8                       u1_EventId;
    uint8                       u1_QueCnt;
    uint8                       u1_ReadPos;
    Dcm_Main_EvtDistr_RetType   u1_RetVal;
    Std_ReturnType              u1_RetCheckEvtId;

    u1_QueCnt       = (uint8)0U;
    u1_RetVal       = DCM_MAIN_EVTDISTR_E_ID;

    u1_RetCheckEvtId = Dcm_Main_EvtDistr_CheckEventId(u1DelEvendId);

    /* Event ID check */
    if( u1_RetCheckEvtId == (Std_ReturnType)E_OK )
    {
        u1_RetVal       = DCM_MAIN_EVTDISTR_E_NOTFOUND;

        /* Lock */
        SchM_Enter_Dcm_Main_EvtDistr();

        u1_QueNum       = Dcm_Main_EvtDistr_stEvtInfo.u1Count;
        u1_ReadPos      = Dcm_Main_EvtDistr_stEvtInfo.u1ReadPos;

        while( u1_QueCnt < u1_QueNum )
        {
            u1_QueCnt = (uint8)(u1_QueCnt + (uint8)1U);

            if( u1_ReadPos < DCM_M_EVTDISTR_QUEUE_MAX )
            {
                u1_EventId = Dcm_Main_EvtDistr_u1EvtQueue[ u1_ReadPos ];

                if( u1DelEvendId == u1_EventId )
                {
                    /* Overwrite with TargetID in DCM_M_EVTDISTR_ID_DELETED */
                    Dcm_Main_EvtDistr_u1EvtQueue[ u1_ReadPos ] = DCM_M_EVTDISTR_ID_DELETED;
                    /* Deleted the target entry */
                    u1_RetVal = DCM_MAIN_EVTDISTR_E_OK;
                    if( bOneEntry == (boolean)TRUE )
                    {
                      /* Loop End */
                      break;
                    }
                }
            }

            /* Read position update */
            if( u1_ReadPos >= (uint8)( DCM_M_EVTDISTR_QUEUE_MAX - (uint8)1U ) )
            {
                u1_ReadPos = (uint8)0U;
            }
            else
            {
                u1_ReadPos = (uint8)(u1_ReadPos + (uint8)1U);
            }
        }
        /* Unlock */
        SchM_Exit_Dcm_Main_EvtDistr();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Main_EvtDistr_CheckEventId                           */
/* Description   | Check whether EventId is unjust                          */
/* Preconditions |                                                          */
/* Parameters    | [IN]   const uint8              : u1EventId              */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | E_NOT_OK      0x01                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Main_EvtDistr_CheckEventId
(
    const uint8    u1EventId
)
{
    Std_ReturnType    u1_RetVal;
    uint8    u1_Index;
    uint8    u1_EventIdNum;
    uint8    u1_EventIdExNum;

    u1_RetVal = E_NOT_OK;
    u1_EventIdNum = Dcm_M_EvtDistr_u1EventIdNum;
    u1_EventIdExNum = Dcm_M_EvtDistr_u1EventIdExNum;

    if( u1EventId < DCM_M_EVTDISTR_DEFINED_ALL_ID_NUM )
    {
        u1_Index = Dcm_M_EvtDistr_IdToIndex[u1EventId];

        if( u1_Index < u1_EventIdNum )
        {
            u1_RetVal = E_OK;
        }
    }
    else
    {
        if( DCM_M_EVTDISTR_ID_EX_MIN <= u1EventId )
        {
            if( u1EventId < ( DCM_M_EVTDISTR_ID_EX_MIN + u1_EventIdExNum ) )
            {
                u1_RetVal = E_OK;
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
    }

    return u1_RetVal;
}


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
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
