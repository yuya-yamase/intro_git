/* E2E_SM_c_v2-0-0                                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_SM/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes            |                                                       */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <E2E.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_U1_SM_VALUE_ONE                     ((uint8)1U)
#define E2E_U1_SM_WS_VALID_MIN                  ((uint8)1U)
#define E2E_U1_SM_MINOKSTATE_MIN                ((uint8)1U)
#define E2E_U1_SM_WINDOWSIZE_ZERO               ((uint8)0U)
#define E2E_U1_SM_WINDOWTOPINDEX_INIT           ((uint8)0U)
#define E2E_U1_SM_OKTOTAL_INIT                  ((uint8)0U)
#define E2E_U1_SM_ERRORTOTAL_INIT               ((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_0134] */
static FUNC(void, E2E_CODE) E2E_SMAddStatus( E2E_PCheckStatusType ProfileStatus, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );
/* Implements [lib_SDD1-1_e2e_0034] */
/* [lib_SC1-1_e2e_0135] */
static FUNC(void, E2E_CODE) E2E_SMClearStatus( P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );
/* Implements [lib_SDD1-1_e2e_0035] */
/* [lib_SC1-1_e2e_1017] */
static FUNC(void, E2E_CODE) E2E_SMClearRemainingStatus( P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, E2E_SMStateType NextState );
/* Implements [lib_SDD1-1_e2e_0110] */
/* [lib_SC1-1_e2e_1018] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckConf( P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );
/* Implements [lib_SDD1-1_e2e_0111] */

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_SMCheck                                           */
/* Description      | Checks the communication channel. It determines IF    */
/*                  | the data can be used FOR safety-related application,  */
/*                  | based on history of checks performed by a             */
/*                  | corresponding E2E_P0XCheck() function.                */
/* Preconditions    | None                                                  */
/* Parameters       | ProfileStatus         : Profile-independent status of */
/*                  |                         the reception on one single   */
/*                  |                         Data in one cycle             */
/*                  | *ConfigPtr            : Pointer to                    */
/*                  |                         STATIC configuration.         */
/*                  | *StatePtr             : Pointer to port|data          */
/*                  |                         communication state.          */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | SWS_E2E_00340, PRS_E2E_00354, PRS_E2E_00345           */
/****************************************************************************/
/* [lib_SC1-1_e2e_0026] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck
/* Implements [lib_SDD1-1_e2e_0026] */
( E2E_PCheckStatusType ProfileStatus, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret;
    uint8 u1_CurrentWindowSize;

    /* SWS_E2E_00371 */
    if( StatePtr != NULL_PTR )
    {
        if( StatePtr->ProfileStatusWindow != NULL_PTR )
        {
            u1_Ret = E2E_SMCheckConf( ConfigPtr );
            if( u1_Ret == E2E_E_OK )
            {
                if( StatePtr->SMState == E2E_SM_VALID )
                {
                    u1_CurrentWindowSize = ConfigPtr->WindowSizeValid;
                }
                else if( StatePtr->SMState == E2E_SM_INIT )
                {
                    u1_CurrentWindowSize = ConfigPtr->WindowSizeInit;
                }
                else if( StatePtr->SMState == E2E_SM_INVALID )
                {
                    u1_CurrentWindowSize = ConfigPtr->WindowSizeInvalid;
                }
                else
                {
                    (void) 0;/* DO nothing */
                }

                if( (StatePtr->SMState == E2E_SM_VALID) || (StatePtr->SMState == E2E_SM_INIT) || (StatePtr->SMState == E2E_SM_INVALID) )
                {
                    if( StatePtr->WindowTopIndex < u1_CurrentWindowSize )
                    {
                        if( (ProfileStatus == E2E_P_OK) ||
                                (ProfileStatus == E2E_P_REPEATED) ||
                                (ProfileStatus == E2E_P_WRONGSEQUENCE) ||
                                (ProfileStatus == E2E_P_ERROR) ||
                                (ProfileStatus == E2E_P_NONEWDATA) )
                        {
                            if( StatePtr->SMState == E2E_SM_INIT )
                            {
                                E2E_SMAddStatus( ProfileStatus, ConfigPtr, StatePtr );

                                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInit) && (StatePtr->OkCount >= ConfigPtr->MinOkStateInit) )
                                {
                                    E2E_SMClearRemainingStatus(StatePtr, ConfigPtr, E2E_SM_VALID);
                                    StatePtr->SMState = E2E_SM_VALID;
                                }
                                else if( StatePtr->ErrorCount > ConfigPtr->MaxErrorStateInit )
                                {
                                    if( ConfigPtr->ClearToInvalid == (boolean)TRUE )
                                    {
                                        E2E_SMClearStatus(ConfigPtr, StatePtr);
                                        StatePtr->SMState = E2E_SM_INVALID;
                                    }
                                    else
                                    {
                                        E2E_SMClearRemainingStatus(StatePtr, ConfigPtr, E2E_SM_INVALID);
                                        StatePtr->SMState = E2E_SM_INVALID;
                                    }
                                }
                                else
                                {
                                    (void) 0;/* DO nothing */
                                }

                            }
                            else if( StatePtr->SMState == E2E_SM_VALID )
                            {
                                E2E_SMAddStatus( ProfileStatus, ConfigPtr, StatePtr );

                                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateValid) && (StatePtr->OkCount >= ConfigPtr->MinOkStateValid) )
                                {
                                    (void) 0;/* DO nothing */
                                }
                                else
                                {
                                    if( ConfigPtr->ClearToInvalid == (boolean)TRUE )
                                    {
                                        E2E_SMClearStatus(ConfigPtr, StatePtr);
                                    }
                                    else
                                    {
                                        if( ConfigPtr->WindowSizeInvalid != E2E_U1_SM_WINDOWSIZE_ZERO )
                                        {
                                            if( StatePtr->WindowTopIndex > (ConfigPtr->WindowSizeInvalid - E2E_U1_SM_VALUE_ONE) )
                                            {
                                                StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
                                            }
                                        }
                                        else
                                        {
                                            StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
                                        }
                                    }
                                    StatePtr->SMState = E2E_SM_INVALID;
                                }
                            }
                            else /* StatePtr->SMState == E2E_SM_INVALID */
                            {
                                E2E_SMAddStatus( ProfileStatus, ConfigPtr, StatePtr );

                                if( (StatePtr->ErrorCount <= ConfigPtr->MaxErrorStateInvalid) && (StatePtr->OkCount >= ConfigPtr->MinOkStateInvalid) )
                                {
                                    E2E_SMClearRemainingStatus(StatePtr, ConfigPtr, E2E_SM_VALID);
                                    StatePtr->SMState = E2E_SM_VALID;
                                }
                                else
                                {
                                    if( ConfigPtr->ClearToInvalid == (boolean)TRUE )
                                    {
                                        E2E_SMClearStatus(ConfigPtr, StatePtr);
                                    }
                                }
                            }
                        }
                        else
                        {
                            u1_Ret = E2E_E_INPUTERR_WRONG;
                        }
                    }
                    else
                    {
                        u1_Ret = E2E_E_INPUTERR_WRONG;
                    }
                }
                else
                {
                    if( (ProfileStatus == E2E_P_OK) ||
                            (ProfileStatus == E2E_P_REPEATED) ||
                            (ProfileStatus == E2E_P_WRONGSEQUENCE) ||
                            (ProfileStatus == E2E_P_ERROR) ||
                            (ProfileStatus == E2E_P_NONEWDATA) )
                    {
                        if( StatePtr->SMState != E2E_SM_DEINIT )
                        {
                            if( StatePtr->SMState == E2E_SM_NODATA )
                            {
                                if( (ProfileStatus != E2E_P_ERROR) && (ProfileStatus != E2E_P_NONEWDATA) )
                                {
                                    StatePtr->SMState = E2E_SM_INIT;
                                }
                            }
                            else
                            {
                                u1_Ret = E2E_E_INPUTERR_WRONG;
                            }
                        }
                        else
                        {
                            u1_Ret = E2E_E_WRONGSTATE;
                        }
                    }
                    else
                    {
                        u1_Ret = E2E_E_INPUTERR_WRONG;
                    }
                }
            }
        }
        else
        {
            u1_Ret = E2E_E_INPUTERR_NULL;
        }
    }
    else
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_SMCheckInit                                       */
/* Description      | Initializes the state machine.                        */
/* Preconditions    | None                                                  */
/*                  | *ConfigPtr            : Pointer to                    */
/*                  |                         STATIC configuration.         */
/*                  | *StatePtr             : Pointer to port|data          */
/*                  |                         communication state.          */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00353, PRS_E2E_00354, PRS_E2E_00375           */
/****************************************************************************/
/* [lib_SC1-1_e2e_0027] */
FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit
/* Implements [lib_SDD1-1_e2e_0027] */
( P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
{
    Std_ReturnType u1_Ret = E2E_E_INPUTERR_NULL;

    /* SWS_E2E_00370 */
    if( (StatePtr != NULL_PTR) && (ConfigPtr != NULL_PTR) )
    {
        u1_Ret = E2E_E_OK;
        E2E_SMClearStatus(ConfigPtr, StatePtr);
        StatePtr->SMState = E2E_SM_NODATA;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_SMAddStatus                                       */
/* Description      | Update E2E_SMCheckStateType                           */
/* Preconditions    | None                                                  */
/* Parameters       | ProfileStatus         : Profile-independent status of */
/*                  |                         the reception on one single   */
/*                  |                         Data in one cycle             */
/*                  | *ConfigPtr            : Pointer to                    */
/*                  |                         STATIC configuration.         */
/*                  | *StatePtr             : Pointer to port|data          */
/*                  |                         communication state.          */
/* Return Value     | None                                                  */
/* Notes            | PRS_E2E_00466                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_0034] */
static FUNC(void, E2E_CODE) E2E_SMAddStatus
/* Implements [lib_SDD1-1_e2e_0034] */
( E2E_PCheckStatusType ProfileStatus, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    uint8 u1_index;
    uint8 u1_OkTotal    = E2E_U1_SM_OKTOTAL_INIT;
    uint8 u1_ErrorTotal = E2E_U1_SM_ERRORTOTAL_INIT;
    uint8 u1_CurrentWindowSize;

    StatePtr->ProfileStatusWindow[StatePtr->WindowTopIndex] = ProfileStatus;

    if( StatePtr->SMState == E2E_SM_VALID )
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeValid;
    }
    else if( StatePtr->SMState == E2E_SM_INIT )
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeInit;
    }
    else /* SMState is only  E2E_SM_INVALID */
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeInvalid;
    }

    for( u1_index = 0U; u1_index < u1_CurrentWindowSize; u1_index++ )
    {
        if( StatePtr->ProfileStatusWindow[u1_index] == E2E_P_OK )
        {
            u1_OkTotal++;
        }
        else if( StatePtr->ProfileStatusWindow[u1_index] == E2E_P_ERROR )
        {
            u1_ErrorTotal++;
        }
        else
        {
            (void) 0;/* DO nothing */
        }
    }
    StatePtr->OkCount = u1_OkTotal;
    StatePtr->ErrorCount = u1_ErrorTotal;

    /* The processing of the E2E_SMCheck function guarantees that u1_CurrentWindowSize is greater than 0. */
    if( StatePtr->WindowTopIndex == (u1_CurrentWindowSize - E2E_U1_SM_VALUE_ONE) )
    {
        StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
    }
    else
    {
        StatePtr->WindowTopIndex++;
    }

    return;
}

/****************************************************************************/
/* Function Name    | E2E_SMClearStatus                                     */
/* Description      | Initializes the state machine.                        */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr            : Pointer to                    */
/*                  |                         STATIC configuration.         */
/*                  | *StatePtr             : Pointer to port|data          */
/*                  |                         communication state.          */
/* Return Value     | None                                                  */
/* Notes            | SWS_E2E_00370, PRS_E2E_00467                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_0035] */
static FUNC(void, E2E_CODE) E2E_SMClearStatus
/* Implements [lib_SDD1-1_e2e_0035] */
( P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    uint8 u1_index;

    for( u1_index = 0U; u1_index < ConfigPtr->WindowSizeValid; u1_index++ )
    {
        StatePtr->ProfileStatusWindow[u1_index] = E2E_P_NOTAVAILABLE;
    }
    StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
    StatePtr->OkCount = E2E_U1_SM_OKTOTAL_INIT;
    StatePtr->ErrorCount = E2E_U1_SM_ERRORTOTAL_INIT;

    return;
}

/****************************************************************************/
/* Function Name    | E2E_SMClearRemainingStatus                            */
/* Description      | Update ProfileStatusWindow settings according to      */
/*                  | SMState                                               */
/* Preconditions    | None                                                  */
/* Parameters       | *StatePtr             : Pointer to port|data          */
/*                  |                         communication state.          */
/*                  | *ConfigPtr            : Pointer to                    */
/*                  |                         STATIC configuration.         */
/*                  | NextState             : State machine state after     */
/*                  |                         change                        */
/* Return Value     | None                                                  */
/* Notes            | PRS_E2E_00607                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1019] */
static FUNC(void, E2E_CODE) E2E_SMClearRemainingStatus
/* Implements [lib_SDD1-1_e2e_0110] */
( P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, E2E_SMStateType NextState)
{

    uint8 u1_CurrentWindowSize;
    uint8 u1_NextWindowSize;
    uint8 u1_index;
    uint8 u1_lasttimeWindowTopIndex;

    if( StatePtr->SMState == E2E_SM_VALID )
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeValid;
    }
    else if( StatePtr->SMState == E2E_SM_INIT )
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeInit;
    }
    else /* SMState is only  E2E_SM_INVALID */
    {
        u1_CurrentWindowSize = ConfigPtr->WindowSizeInvalid;
    }

    if( NextState == E2E_SM_VALID )
    {
        u1_NextWindowSize = ConfigPtr->WindowSizeValid;
    }
    else /* NextState is only  E2E_SM_INVALID */
    {
        u1_NextWindowSize = ConfigPtr->WindowSizeInvalid;
    }

    if( u1_CurrentWindowSize < u1_NextWindowSize )
    {
        /* Save last time  WindowTopIndex in a local variable */
        if( StatePtr->WindowTopIndex == E2E_U1_SM_WINDOWTOPINDEX_INIT )
        {
            /* The processing of the E2E_SMCheck function guarantees that u1_CurrentWindowSize is greater than 0. */
            u1_lasttimeWindowTopIndex = u1_CurrentWindowSize - E2E_U1_SM_VALUE_ONE;
            StatePtr->WindowTopIndex = u1_lasttimeWindowTopIndex + E2E_U1_SM_VALUE_ONE; /* Set WindowTopIndex to continue from last time */
        }
        else
        {
            u1_lasttimeWindowTopIndex = StatePtr->WindowTopIndex - E2E_U1_SM_VALUE_ONE;
        }
        /* Set all elements in State->ProfileStatusWindow[] to E2E_P_NOTAVAILABLE */
        for( u1_index = 0U; u1_index < ConfigPtr->WindowSizeValid; u1_index++ )
        {
            if( u1_index != u1_lasttimeWindowTopIndex )
            {
                StatePtr->ProfileStatusWindow[u1_index] = E2E_P_NOTAVAILABLE;
            }
        }
    }

    if( u1_NextWindowSize != E2E_U1_SM_WINDOWSIZE_ZERO )
    {
        if( StatePtr->WindowTopIndex > (u1_NextWindowSize - E2E_U1_SM_VALUE_ONE) )
        {
            StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
        }
    }
    else
    {
        StatePtr->WindowTopIndex = E2E_U1_SM_WINDOWTOPINDEX_INIT;
    }

    return;
}

/****************************************************************************/
/* Function Name    | E2E_SMCheckConf                                       */
/* Description      | Check the E2E_SMConfigType value.                     */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | None                                                  */
/****************************************************************************/
/* [lib_SC1-1_e2e_1020] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckConf
/* Implements [lib_SDD1-1_e2e_0111] */
( P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_OK;

    if( ConfigPtr != NULL_PTR )
    {
        /* constr_3176, constr_6301, constr_6302, constr_3177, constr_3178, constr_3179, constr_3180, constr_3181 */
        if((ConfigPtr->WindowSizeValid < E2E_U1_SM_WS_VALID_MIN) ||
                (ConfigPtr->WindowSizeInvalid > ConfigPtr->WindowSizeValid) ||
                (ConfigPtr->WindowSizeInit > ConfigPtr->WindowSizeValid) ||
                ((ConfigPtr->MaxErrorStateValid < ConfigPtr->MaxErrorStateInit) ||
                (ConfigPtr->MaxErrorStateInit < ConfigPtr->MaxErrorStateInvalid)) ||
                ((E2E_U1_SM_MINOKSTATE_MIN > ConfigPtr->MinOkStateValid) ||
                (ConfigPtr->MinOkStateValid > ConfigPtr->MinOkStateInit) ||
                (ConfigPtr->MinOkStateInit > ConfigPtr->MinOkStateInvalid)) ||
                ((ConfigPtr->MinOkStateInit + ConfigPtr->MaxErrorStateInit) > ConfigPtr->WindowSizeValid) ||
                ((ConfigPtr->MinOkStateValid + ConfigPtr->MaxErrorStateValid) > ConfigPtr->WindowSizeValid) ||
                ((ConfigPtr->MinOkStateInvalid + ConfigPtr->MaxErrorStateInvalid) > ConfigPtr->WindowSizeValid))
        {
            u1_Ret = E2E_E_INPUTERR_WRONG;
        }
    }
    else
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }

    return u1_Ret;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2020/12/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
