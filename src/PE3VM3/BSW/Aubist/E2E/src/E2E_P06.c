/* E2E_P06_c_v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_P06/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes            | SWS_E2E_00215, PRS_E2E_00221, PRS_E2E_00217           */
/*                  | PRS_E2E_00012, PRS_E2E_00479                          */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <E2E.h>
#include "../inc/E2E_Local_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_U2_P06_CRCSTARTVALUE                ((uint16)0xFFFFU)
#define E2E_U2_P06_DATALEN_BIT_MAX              ((uint16)32768U)
#define E2E_U1_P06_OFFSET_POS_IN_DATA           ((uint8)0U)
#define E2E_U4_P06_DATAID_BYTE_SIZE             ((uint32)2UL)
#define E2E_U4_P06_DATAID_BYTE_HALF_SIZE        ((uint32)(E2E_U4_P06_DATAID_BYTE_SIZE >> E2E_U4_BIT_SHIFT_1))
#define E2E_P06_CRC_BYTE_SIZE                   (2U)
#define E2E_U2_P06_LENGTH_POS_IN_DATA           ((uint16)2U)
#define E2E_U2_P06_COUNTER_POS_IN_DATA          ((uint16)4U)
#define E2E_U2_P06_HEADER_BIT_LEN               ((uint16)40U)
#define E2E_U1_P06_COUNTER_NEGATIVE_TO_POSITIVE ((uint8)0xFFU)
#define E2E_U1_P06_PROTECTCOUNTER_INIT          ((uint8)0U)
#define E2E_U1_P06_CHECKCOUNTER_INIT            ((uint8)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_1121] */
static FUNC(uint16, E2E_CODE) E2E_P06CalculateCrc( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Offset, uint16 Length );
/* Implements [lib_SDD1-1_e2e_0125] */
/* [lib_SC1-1_e2e_1122] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckConf( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );
/* Implements [lib_SDD1-1_e2e_0126] */
/* [lib_SC1-1_e2e_1123] */
static FUNC(void, E2E_CODE) E2E_P06CheckData( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length );
/* Implements [lib_SDD1-1_e2e_0127] */

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
/* Function Name    | E2E_P06Protect                                        */
/* Description      | Protects the array|buffer to be transmitted using the */
/*                  | E2E profile 6 . This includes checksum calculation,   */
/*                  | handling of counter and Data ID.                      */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data  communication   */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to Data to be transmitted.    */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | SWS_E2E_00393, PRS_E2E_00423                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_1124] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Protect
/* Implements [lib_SDD1-1_e2e_0117] */
( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    uint16          u2_Offset;
    uint16          u2_CrcResult;
    uint16          u2_CfgMinDataLengthByte;
    uint16          u2_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00424 */ /* Verify inputs of the protect function */
    if( (StatePtr != NULL_PTR) && (DataPtr != NULL_PTR) )
    {
        u1_Ret = E2E_P06CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            u2_CfgMinDataLengthByte = (uint16)(ConfigPtr->MinDataLength >> E2E_U2_BIT_SHIFT_3);
            u2_CfgMaxDataLengthByte = (uint16)(ConfigPtr->MaxDataLength >> E2E_U2_BIT_SHIFT_3);
            if( (Length >= u2_CfgMinDataLengthByte) && (Length <= u2_CfgMaxDataLengthByte) )
            {
                /* PRS_E2E_00470 */ /* Compute offset */ /* compute local variable uint16 Offset, which is in [byte] */
                u2_Offset = ConfigPtr->Offset >> E2E_USE_SHIFT_DIV_8;

                /* PRS_E2E_00425 */ /* Write Length */
                DataPtr[u2_Offset + E2E_U2_P06_LENGTH_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE] = (uint8)(Length & (uint16)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P06_LENGTH_POS_IN_DATA] = (uint8)(Length >> (uint16)E2E_BIT_SHIFT_8);

                /* PRS_E2E_00426 */ /* Write Counter */
                DataPtr[u2_Offset + E2E_U2_P06_COUNTER_POS_IN_DATA] = StatePtr->Counter;

                /* PRS_E2E_00427 */ /* Compute CRC */
                u2_CrcResult = E2E_P06CalculateCrc( ConfigPtr, DataPtr, u2_Offset, Length );

                /* PRS_E2E_00428 */ /* Write CRC */
                DataPtr[u2_Offset + E2E_U2_ARRAY_INDEX_ONE] = (uint8)(u2_CrcResult & (uint16)E2E_MASK_BYTE);
                DataPtr[u2_Offset] = (uint8)(u2_CrcResult >> (uint16)E2E_BIT_SHIFT_8);

                /* PRS_E2E_00417, PRS_E2E_00429 */ /* Increment Counter */
                StatePtr->Counter++; /* wrap around */
            }
            else
            {
                u1_Ret = E2E_E_INPUTERR_WRONG;
            }
        }
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P06ProtectInit                                    */
/* Description      | Initializes the protection state.[E2E Profile 06]     */
/* Preconditions    | None                                                  */
/* Parameters       | *StatePtr : Pointer to port|data communication state. */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00455                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1125] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06ProtectInit
/* Implements [lib_SDD1-1_e2e_0118] */
( P2VAR(E2E_P06ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00456 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        /* PRS_E2E_00417 */
        StatePtr->Counter = E2E_U1_P06_PROTECTCOUNTER_INIT;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P06Check                                          */
/* Description      | Checks the Data received using the E2E profile 6 .    */
/*                  | This includes CRC calculation, handling of Counter.   */
/*                  | The function checks only one single data in one       */
/*                  | cycle, it does not determine|compute the accumulated  */
/*                  | state of the communication link.                      */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to received data.             */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | SWS_E2E_00457, PRS_E2E_00430                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_1126] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06Check
/* Implements [lib_SDD1-1_e2e_0119] */
( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    boolean         b_NewDataAvailable = (boolean)FALSE;
    uint16          u2_CfgMinDataLengthByte;
    uint16          u2_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00431 */ /* Verify inputs of the check function */
    if( StatePtr != NULL_PTR )
    {
        u1_Ret = E2E_P06CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            if( ((DataPtr != NULL_PTR) && (Length != E2E_U2_DATALEN_ZERO)) || ((DataPtr == NULL_PTR) && (Length == E2E_U2_DATALEN_ZERO)) )
            {
                if( DataPtr != NULL_PTR )
                {
                    u2_CfgMinDataLengthByte = (uint16)(ConfigPtr->MinDataLength >> E2E_U2_BIT_SHIFT_3);
                    u2_CfgMaxDataLengthByte = (uint16)(ConfigPtr->MaxDataLength >> E2E_U2_BIT_SHIFT_3);
                    if( (Length >= u2_CfgMinDataLengthByte) && (Length <= u2_CfgMaxDataLengthByte) )
                    {
                        b_NewDataAvailable = (boolean)TRUE;
                    }
                    else
                    {
                        u1_Ret = E2E_E_INPUTERR_WRONG;
                    }
                }
            }
            else
            {
                u1_Ret = E2E_E_INPUTERR_WRONG;
            }

            if( u1_Ret == E2E_E_OK )
            {
                /* If any NEW data is available to be checked. */
                if( b_NewDataAvailable == (boolean)TRUE )
                {
                    E2E_P06CheckData( ConfigPtr, StatePtr, DataPtr, Length );
                }
                else
                {
                    StatePtr->Status = E2E_P06STATUS_NONEWDATA;
                }
            }
        }
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P06CheckInit                                      */
/* Description      | Initializes the check state[E2E Profile 06]           */
/* Preconditions    | None                                                  */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00458                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1127] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckInit
/* Implements [lib_SDD1-1_e2e_0120] */
( P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00459 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        StatePtr->Counter   = E2E_U1_P06_CHECKCOUNTER_INIT;
        StatePtr->Status    = E2E_P06STATUS_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P06MapStatusToSM                                  */
/* Description      | The function maps the check status of Profile 6 to a  */
/*                  | generic check status, which can be used by E2E state  */
/*                  | machine check function. The E2E Profile 6 delivers a  */
/*                  | more fine-granular status, but this is not relevant   */
/*                  | FOR the E2E state machine.                            */
/* Preconditions    | None                                                  */
/* Parameters       | CheckReturn       : Return value of the E2E_P06Check  */
/*                  |                     function                          */
/*                  | Status            : Status determined by E2E_P06Check */
/*                  |                     function                          */
/* Return Value     | E2E_PCheckStatusType                                  */
/*                  | E2E_P_OK              : OK: the checks of the Data in */
/*                  |                         this cycle were successful    */
/*                  |                         [including counter check].    */
/*                  | E2E_P_REPEATED        : Either no new data is         */
/*                  |                         available, or the new data    */
/*                  |                         has a repeated counter.       */
/*                  | E2E_P_ERROR           : Error not related to counters */
/*                  |                         occurred [e.g. wrong crc,     */
/*                  |                         wrong length, wrong Data ID]  */
/*                  |                         or the RETURN of the check    */
/*                  |                         function was not OK.          */
/*                  | E2E_P_WRONGSEQUENCE   : The checks of the Data in     */
/*                  |                         this cycle were successful,   */
/*                  |                         with the exception of counter */
/*                  |                         jump, which changed more than */
/*                  |                         the allowed delta.            */
/*                  | E2E_P_NONEWDATA       : No new Data is available.     */
/* Notes            | SWS_E2E_00460                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1128] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P06MapStatusToSM
/* Implements [lib_SDD1-1_e2e_0121] */
( Std_ReturnType CheckReturn, E2E_P06CheckStatusType Status )
{
    E2E_PCheckStatusType u1_Ret;

    if( CheckReturn == E2E_E_OK )
    {
        /* SWS_E2E_00461, PRS_E2E_00602 */
        if( (Status == E2E_P06STATUS_OK) ||
            (Status == E2E_P06STATUS_OKSOMELOST)  )
        {
            u1_Ret = E2E_P_OK;
        }
        else if(Status == E2E_P06STATUS_ERROR)
        {
            u1_Ret = E2E_P_ERROR;
        }
        else if(Status == E2E_P06STATUS_REPEATED)
        {
            u1_Ret = E2E_P_REPEATED;
        }
        else if(Status == E2E_P06STATUS_NONEWDATA)
        {
            u1_Ret = E2E_P_NONEWDATA;
        }
        else if(Status == E2E_P06STATUS_WRONGSEQUENCE)
        {
            u1_Ret = E2E_P_WRONGSEQUENCE;
        }
        else
        {
            u1_Ret = E2E_P_ERROR;
        }
    }
    else
    {
        /* SWS_E2E_00462 */
        u1_Ret = E2E_P_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_P06CalculateCrc                                   */
/* Description      | The diagram of the function E2E_P06Protect() and      */
/*                  | E2E_P06Check() have a sub-diagram specifying the      */
/*                  | calculation of CRC.                                   */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *DataPtr      : Pointer to Data to be transmitted.    */
/*                  | Offset        : offset                                */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | uint16        : Calculated CRC                        */
/* Notes            | Do not check parameter is NULL                        */
/****************************************************************************/
/* [lib_SC1-1_e2e_1129] */
static FUNC(uint16, E2E_CODE) E2E_P06CalculateCrc
/* Implements [lib_SDD1-1_e2e_0125] */
( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Offset, uint16 Length )
{
    uint16   u2_CrcFirst;
    uint16   u2_CrcSecond;
    uint8    u1_CrcParam;
    uint16   u2_CrcResult;

    /* PRS_E2E_00420, PRS_E2E_00421 */
    if( Offset > E2E_U2_OFFSET_INVALID )
    {
        /* PRS_E2E_00420, PRS_E2E_00421 */
        u2_CrcFirst = Crc_CalculateCRC16( &DataPtr[E2E_U1_P06_OFFSET_POS_IN_DATA], (uint32)Offset, E2E_U2_P06_CRCSTARTVALUE, (boolean)TRUE );
        /* PRS_E2E_00420, PRS_E2E_00421 */
        u2_CrcFirst = Crc_CalculateCRC16( &DataPtr[Offset + (uint16)E2E_P06_CRC_BYTE_SIZE], (uint32)Length - (uint32)Offset - (uint32)E2E_P06_CRC_BYTE_SIZE, u2_CrcFirst, (boolean)FALSE );
    }
    else
    {
        u2_CrcFirst = Crc_CalculateCRC16( &DataPtr[(uint16)E2E_P06_CRC_BYTE_SIZE], (uint32)Length - (uint32)E2E_P06_CRC_BYTE_SIZE, E2E_U2_P06_CRCSTARTVALUE, (boolean)TRUE );
    }
    /* PRS_E2E_00419 */
    u1_CrcParam = (uint8)(ConfigPtr->DataID >> (uint8)E2E_BIT_SHIFT_8);
    /* PRS_E2E_00420, PRS_E2E_00421 */
    u2_CrcSecond = Crc_CalculateCRC16(&u1_CrcParam, E2E_U4_P06_DATAID_BYTE_HALF_SIZE, u2_CrcFirst, (boolean)FALSE);
    /* PRS_E2E_00419 */
    u1_CrcParam = (uint8)(ConfigPtr->DataID & (uint16)E2E_MASK_BYTE);
    /* PRS_E2E_00420, PRS_E2E_00421 */
    u2_CrcResult = Crc_CalculateCRC16(&u1_CrcParam, E2E_U4_P06_DATAID_BYTE_HALF_SIZE, u2_CrcSecond, (boolean)FALSE);

    return u2_CrcResult;
}

/****************************************************************************/
/* Function Name    | E2E_P06CheckConf                                      */
/* Description      | Check the E2E_P06ConfigType value.                    */
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
/* [lib_SC1-1_e2e_1130] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P06CheckConf
/* Implements [lib_SDD1-1_e2e_0126] */
( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_OK;
    uint16          u2_CfgOffsetMlti8;
    uint16          u2_CfgMinDataLengthMlti8;
    uint16          u2_CfgMaxDataLengthMlti8;

    /* SWS_E2E_00047 */
    if( ConfigPtr != NULL_PTR )
    {
        u2_CfgOffsetMlti8 = (uint16)(ConfigPtr->Offset & E2E_U2_MASK_MULTIPLE8);
        u2_CfgMinDataLengthMlti8 = (uint16)(ConfigPtr->MinDataLength & E2E_U2_MASK_MULTIPLE8);
        u2_CfgMaxDataLengthMlti8 = (uint16)(ConfigPtr->MaxDataLength & E2E_U2_MASK_MULTIPLE8);

        /* SWS_E2E_00047, SWS_E2E_00441 */
        if( (ConfigPtr->MinDataLength < E2E_U2_P06_HEADER_BIT_LEN) ||
                (ConfigPtr->MinDataLength > E2E_U2_P06_DATALEN_BIT_MAX) ||
                (u2_CfgMinDataLengthMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                (ConfigPtr->MaxDataLength < ConfigPtr->MinDataLength) ||
                (ConfigPtr->MaxDataLength > E2E_U2_P06_DATALEN_BIT_MAX) ||
                (u2_CfgMaxDataLengthMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                (u2_CfgOffsetMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                ((ConfigPtr->MaxDataLength - E2E_U2_P06_HEADER_BIT_LEN) < ConfigPtr->Offset ) )
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

/****************************************************************************/
/* Function Name    | E2E_P06CheckData                                      */
/* Description      | Checks the Data received using the E2E profile 6 .    */
/*                  | This includes CRC calculation, handling of Counter.   */
/*                  | The function checks only one single data in one       */
/*                  | cycle, it does not determine|compute the accumulated  */
/*                  | state of the communication link.                      */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to received data.             */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | None                                                  */
/* Notes            | None                                                  */
/****************************************************************************/
/* [lib_SC1-1_e2e_1131] */
static FUNC(void, E2E_CODE) E2E_P06CheckData
/* Implements [lib_SDD1-1_e2e_0127] */
( P2CONST(E2E_P06ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P06CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    uint16          u2_Offset;
    uint16          u2_AryIndex;
    uint16          u2_ReceivedLength;
    uint8           u1_ReceivedCounter;
    uint16          u2_ReceivedCRC;
    uint16          u2_CrcResult;
    uint8           u1_DeltaCounter;

    /* PRS_E2E_00470 */ /* Compute offset */
    u2_Offset = ConfigPtr->Offset >> E2E_USE_SHIFT_DIV_8;

    /* PRS_E2E_00432 */ /* Read Length */
    u2_AryIndex  = u2_Offset + E2E_U2_P06_LENGTH_POS_IN_DATA;
    u2_ReceivedLength = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P06_LENGTH_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE;
    u2_ReceivedLength = (uint16)(u2_ReceivedLength << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* PRS_E2E_00433 */ /* Read Counter */
    u1_ReceivedCounter  = DataPtr[u2_Offset + E2E_U2_P06_COUNTER_POS_IN_DATA];

    /* PRS_E2E_00434 */ /* Read CRC */
    u2_AryIndex  = u2_Offset;
    u2_ReceivedCRC = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_ARRAY_INDEX_ONE;
    u2_ReceivedCRC = (uint16)(u2_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* PRS_E2E_00427 */ /* Compute CRC */
    u2_CrcResult = E2E_P06CalculateCrc( ConfigPtr, DataPtr, u2_Offset, Length );

    /* PRS_E2E_00436 */ /* Do Checks */
    if( u2_ReceivedCRC == u2_CrcResult )
    {
        if( u2_ReceivedLength == Length )
        {
            /* taking into wrap around 0xFF */
            if( u1_ReceivedCounter >= StatePtr->Counter )
            {
                u1_DeltaCounter = u1_ReceivedCounter - StatePtr->Counter;
            }
            else
            {
                u1_DeltaCounter = (E2E_U1_P06_COUNTER_NEGATIVE_TO_POSITIVE - (StatePtr->Counter - u1_ReceivedCounter)) + (uint8)E2E_DELTA_COUNTER_WRAP_AROUND;
            }

            if( u1_DeltaCounter <= ConfigPtr->MaxDeltaCounter )
            {
                if( u1_DeltaCounter > (uint8)E2E_DELTA_COUNTER_NUM_ZERO )
                {
                    if( u1_DeltaCounter == (uint8)E2E_DELTA_COUNTER_NUM_ONE )
                    {
                        StatePtr->Status = E2E_P06STATUS_OK;
                    }
                    else
                    {
                        StatePtr->Status = E2E_P06STATUS_OKSOMELOST;
                    }
                }
                else
                {
                    StatePtr->Status = E2E_P06STATUS_REPEATED;
                }
            }
            else
            {
                StatePtr->Status = E2E_P06STATUS_WRONGSEQUENCE;
            }
            StatePtr->Counter = u1_ReceivedCounter;
        }
        else
        {
            StatePtr->Status = E2E_P06STATUS_ERROR;
        }
    }
    else
    {
        StatePtr->Status = E2E_P06STATUS_ERROR;
    }
    return;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2022/06/03                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
