/* E2E_P07_c_v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_P07/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes            | SWS_E2E_00215, PRS_E2E_00221, PRS_E2E_00217           */
/*                  | PRS_E2E_00012, PRS_E2E_00480                          */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <E2E.h>
#include "../inc/E2E_Local_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_U4_P07_FIRST_POS_IN_DATA            ((uint32)0UL)
#define E2E_U4_P07_LENGTH_POS_IN_DATA           ((uint32)8UL)
#define E2E_U4_P07_COUNTER_POS_IN_DATA          ((uint32)12UL)
#define E2E_U2_P07_DATAID_POS_IN_DATA           ((uint32)16UL)
#define E2E_U4_P07_CHECKCOUNTER_INIT            ((uint32)0xFFFFFFFFUL)
#define E2E_U8_P07_CRCSTARTVALUE                ((uint64)0xFFFFFFFFFFFFFFFFULL)
#define E2E_P07_CRC_BYTE_SIZE                   ((uint8)8U)
#define E2E_U4_P07_HEADER_BIT_LEN               ((uint32)160UL)
#define E2E_U4_P07_DATALEN_BIT_MAX              ((uint32)0x2000000UL)
#define E2E_U4_P07_COUNTER_NEGATIVE_TO_POSITIVE ((uint32)0xFFFFFFFFUL)
#define E2E_U4_P07_PSTATE_COUNTER_INIT          ((uint32)0UL)
#define E2E_U1_P07_LENGTH_HIGHBYTE_VALUE        ((uint8)0UL)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_1006] */
static FUNC(uint64, E2E_CODE) E2E_P07CalculateCrc( P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Offset, uint32 Length );
/* Implements [lib_SDD1-1_e2e_0107] */
/* [lib_SC1-1_e2e_1007] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckConf( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );
/* Implements [lib_SDD1-1_e2e_0108] */
/* [lib_SC1-1_e2e_1008] */
static FUNC(void, E2E_CODE) E2E_P07CheckData( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length );
/* Implements [lib_SDD1-1_e2e_0109] */
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
/* Function Name    | E2E_P07Protect                                        */
/* Description      | Protects the array|buffer to be transmitted using the */
/*                  | E2E profile 7 . This includes checksum calculation,   */
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
/* Notes            | SWS_E2E_00546, PRS_E2E_00486                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_1009] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07Protect
/* Implements [lib_SDD1-1_e2e_0102] */
( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    uint32          u4_Offset;
    uint64          u8_CrcResult;
    uint32          u4_CfgMinDataLengthByte;
    uint32          u4_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00487 */ /* Verify inputs of the protect function */
    if( (StatePtr != NULL_PTR) && (DataPtr != NULL_PTR) )
    {
        u1_Ret = E2E_P07CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            u4_CfgMinDataLengthByte = (uint32)(ConfigPtr->MinDataLength >> E2E_U4_BIT_SHIFT_3);
            u4_CfgMaxDataLengthByte = (uint32)(ConfigPtr->MaxDataLength >> E2E_U4_BIT_SHIFT_3);
            if( (Length >= u4_CfgMinDataLengthByte) && (Length <= u4_CfgMaxDataLengthByte) )
            {
                /* PRS_E2E_00488 */ /* Compute offset */ /* compute local variable uint32 Offset, which is in [byte] */
                u4_Offset = ConfigPtr->Offset >> E2E_USE_SHIFT_DIV_8;

                /* PRS_E2E_00489 */ /* Write Length */
                DataPtr[u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE] = (uint8)(Length & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO] = (uint8)((Length >> (uint32)E2E_BIT_SHIFT_8) & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE] = (uint8)(Length >> E2E_U4_BIT_SHIFT_16);
                DataPtr[u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA] = E2E_U1_P07_LENGTH_HIGHBYTE_VALUE; /* It will always be 0 due to the config maximum size */

                /* PRS_E2E_00490 */ /* Write Counter */
                DataPtr[u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE] = (uint8)(StatePtr->Counter & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO] = (uint8)((StatePtr->Counter >> (uint32)E2E_BIT_SHIFT_8) & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE] = (uint8)((StatePtr->Counter >> E2E_U4_BIT_SHIFT_16) & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA] = (uint8)(StatePtr->Counter >> E2E_U4_BIT_SHIFT_24);

                /* PRS_E2E_00491, PRS_E2E_00482 */ /* Write DataID */
                DataPtr[u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE] = (uint8)(ConfigPtr->DataID & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO] = (uint8)((ConfigPtr->DataID >> (uint32)E2E_BIT_SHIFT_8) & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE] = (uint8)((ConfigPtr->DataID >> E2E_U4_BIT_SHIFT_16) & (uint32)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA] = (uint8)(ConfigPtr->DataID >> E2E_U4_BIT_SHIFT_24);

                /* PRS_E2E_00492 */ /* Compute CRC */
                u8_CrcResult = E2E_P07CalculateCrc( DataPtr, u4_Offset, Length );

                /* PRS_E2E_00493 */ /* Write CRC */
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_SEVEN] = (uint8)(u8_CrcResult & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_SIX] = (uint8)((u8_CrcResult >> (uint64)E2E_BIT_SHIFT_8) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_FIVE] = (uint8)((u8_CrcResult >> E2E_U8_BIT_SHIFT_16) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_FOUR] = (uint8)((u8_CrcResult >> E2E_U8_BIT_SHIFT_24) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_THREE] = (uint8)((u8_CrcResult >> E2E_U8_BIT_SHIFT_32) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_TWO] = (uint8)((u8_CrcResult >> E2E_U8_BIT_SHIFT_40) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset + E2E_U4_ARRAY_INDEX_ONE] = (uint8)((u8_CrcResult >> E2E_U8_BIT_SHIFT_48) & (uint64)E2E_MASK_BYTE);
                DataPtr[u4_Offset] = (uint8)(u8_CrcResult >> (uint16)E2E_U8_BIT_SHIFT_56);

                /* PRS_E2E_00481, PRS_E2E_00494 */ /* Increment Counter */
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
/* Function Name    | E2E_P07ProtectInit                                    */
/* Description      | Initializes the protection state.[E2E Profile 07]     */
/* Preconditions    | None                                                  */
/* Parameters       | *StatePtr : Pointer to port|data communication state. */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00547                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1010] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07ProtectInit
/* Implements [lib_SDD1-1_e2e_0103] */
( P2VAR(E2E_P07ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00551 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        /* PRS_E2E_00481 */
        StatePtr->Counter = E2E_U4_P07_PSTATE_COUNTER_INIT;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P07Check                                          */
/* Description      | Checks the Data received using the E2E profile 7 .    */
/*                  | This includes CRC calculation, handling of Counter    */
/*                  | and Data ID.                                          */
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
/* Notes            | SWS_E2E_00548, PRS_E2E_00495                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_1011] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07Check
/* Implements [lib_SDD1-1_e2e_0104] */
( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    boolean         b_NewDataAvailable = (boolean)FALSE;
    uint32          u4_CfgMinDataLengthByte;
    uint32          u4_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00496 */ /* Verify inputs of the check function */
    if( StatePtr != NULL_PTR )
    {
        u1_Ret = E2E_P07CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            if( ((DataPtr != NULL_PTR) && (Length != E2E_U4_DATALEN_ZERO)) || ((DataPtr == NULL_PTR) && (Length == E2E_U4_DATALEN_ZERO)) )
            {
                if( DataPtr != NULL_PTR )
                {
                    u4_CfgMinDataLengthByte = (uint32)(ConfigPtr->MinDataLength >> E2E_U4_BIT_SHIFT_3);
                    u4_CfgMaxDataLengthByte = (uint32)(ConfigPtr->MaxDataLength >> E2E_U4_BIT_SHIFT_3);
                    if( (Length >= u4_CfgMinDataLengthByte) && (Length <= u4_CfgMaxDataLengthByte) )
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
                    E2E_P07CheckData( ConfigPtr, StatePtr, DataPtr, Length );
                }
                else
                {
                    StatePtr->Status = E2E_P07STATUS_NONEWDATA;
                }
            }
        }
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P07CheckInit                                      */
/* Description      | Initializes the check state[E2E Profile 07]           */
/* Preconditions    | None                                                  */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00549                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1012] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckInit
/* Implements [lib_SDD1-1_e2e_0105] */
( P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00552 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        StatePtr->Counter   = E2E_U4_P07_CHECKCOUNTER_INIT;
        StatePtr->Status    = E2E_P07STATUS_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P07MapStatusToSM                                  */
/* Description      | The function maps the check status of Profile 7 to a  */
/*                  | generic check status, which can be used by E2E state  */
/*                  | machine check function. The E2E Profile 7 delivers a  */
/*                  | more fine-granular status, but this is not relevant   */
/*                  | for the E2E state machine.                            */
/* Preconditions    | None                                                  */
/* Parameters       | CheckReturn       : Profile-independent status of the */
/*                  |                     reception on one single Data in   */
/*                  |                     one cycle.                        */
/*                  | Status            : Status determined by E2E_P07Check */
/*                  |                     function                          */
/* Return Value     | E2E_PCheckStatusType                                  */
/*                  | E2E_P_OK              : OK: the checks of the Data in */
/*                  |                         this cycle were successful    */
/*                  |                         [including counter check].    */
/*                  | E2E_P_REPEATED        : Data has a repeated counter.  */
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
/* Notes            | SWS_E2E_00550                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1013] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P07MapStatusToSM
/* Implements [lib_SDD1-1_e2e_0106] */
( Std_ReturnType CheckReturn, E2E_P07CheckStatusType Status )
{
    E2E_PCheckStatusType u1_Ret;

    if( CheckReturn == E2E_E_OK )
    {
        /* SWS_E2E_00553, PRS_E2E_00603 */
        if( (Status == E2E_P07STATUS_OK) || (Status == E2E_P07STATUS_OKSOMELOST))
        {
            u1_Ret = E2E_P_OK;
        }
        else if( Status == E2E_P07STATUS_ERROR )
        {
            u1_Ret = E2E_P_ERROR;
        }
        else if( Status == E2E_P07STATUS_REPEATED )
        {
            u1_Ret = E2E_P_REPEATED;
        }
        else if( Status == E2E_P07STATUS_NONEWDATA )
        {
            u1_Ret = E2E_P_NONEWDATA;
        }
        else if( Status == E2E_P07STATUS_WRONGSEQUENCE )
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
        /* SWS_E2E_00554 */
        u1_Ret = E2E_P_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_P07CalculateCrc                                   */
/* Description      | The diagram of the function E2E_P07Protect and        */
/*                  | E2E_P07Check have a sub-diagram specifying the        */
/*                  | calculation of CRC.                                   */
/* Preconditions    | None                                                  */
/* Parameters       | *DataPtr      : Pointer to Data to be transmitted.    */
/*                  | Offset        : E2E Offset                            */
/*                  | Length        : Data Length                           */
/* Return Value     | uint64        : Calculated CRC                        */
/* Notes            | Do not check parameter is NULL                        */
/****************************************************************************/
/* [lib_SC1-1_e2e_1014] */
static FUNC(uint64, E2E_CODE) E2E_P07CalculateCrc
/* Implements [lib_SDD1-1_e2e_0107] */
( P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Offset, uint32 Length )
{
    uint64   u8_CrcResult;

    /* PRS_E2E_00484, PRS_E2E_00485, PRS_E2E_00492 */
    if( Offset > E2E_U4_OFFSET_INVALID )
    {
        u8_CrcResult = Crc_CalculateCRC64( &DataPtr[E2E_U4_P07_FIRST_POS_IN_DATA], Offset, E2E_U8_P07_CRCSTARTVALUE, (boolean)TRUE );
        u8_CrcResult = Crc_CalculateCRC64( &DataPtr[Offset + E2E_P07_CRC_BYTE_SIZE], Length - (Offset + E2E_P07_CRC_BYTE_SIZE), u8_CrcResult, (boolean)FALSE );
    }
    else
    {
        /* Offset:0 */
        u8_CrcResult = Crc_CalculateCRC64( &DataPtr[E2E_P07_CRC_BYTE_SIZE], Length - E2E_P07_CRC_BYTE_SIZE, E2E_U8_P07_CRCSTARTVALUE, (boolean)TRUE );
    }

    return u8_CrcResult;
}

/****************************************************************************/
/* Function Name    | E2E_P07CheckConf                                      */
/* Description      | Check the E2E_P07ConfigType value.                    */
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
/* [lib_SC1-1_e2e_1015] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P07CheckConf
/* Implements [lib_SDD1-1_e2e_0108] */
( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_OK;
    uint32          u4_CfgOffsetMlti8;
    uint32          u4_CfgMinDataLengthMlti8;
    uint32          u4_CfgMaxDataLengthMlti8;

    /* SWS_E2E_00047 */
    if( ConfigPtr != NULL_PTR )
    {
        u4_CfgOffsetMlti8 = (uint32)(ConfigPtr->Offset & E2E_U4_MASK_MULTIPLE8);
        u4_CfgMinDataLengthMlti8 = (uint32)(ConfigPtr->MinDataLength & E2E_U4_MASK_MULTIPLE8);
        u4_CfgMaxDataLengthMlti8 = (uint32)(ConfigPtr->MaxDataLength & E2E_U4_MASK_MULTIPLE8);

        /* SWS_E2E_00047, SWS_E2E_00544 */
        if( (ConfigPtr->MinDataLength < E2E_U4_P07_HEADER_BIT_LEN) ||
                (ConfigPtr->MinDataLength > E2E_U4_P07_DATALEN_BIT_MAX) ||
                (u4_CfgMinDataLengthMlti8 != (uint32)E2E_REMAINDER_ZERO) ||
                (ConfigPtr->MaxDataLength < ConfigPtr->MinDataLength) ||
                (ConfigPtr->MaxDataLength > E2E_U4_P07_DATALEN_BIT_MAX) ||
                (u4_CfgMaxDataLengthMlti8 != (uint32)E2E_REMAINDER_ZERO) ||
                (u4_CfgOffsetMlti8 != (uint32)E2E_REMAINDER_ZERO) )
        {
            u1_Ret = E2E_E_INPUTERR_WRONG;
        }
        /* It will be processed after it is determined that MaxDataLength is equal to or greater than E2E_U4_P07_HEADER_BIT_LEN by the above judgment.  */
        if((ConfigPtr->MaxDataLength - E2E_U4_P07_HEADER_BIT_LEN) < ConfigPtr->Offset )
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
/* Function Name    | E2E_P07CheckData                                      */
/* Description      | Checks the Data received using the E2E profile 7 .    */
/*                  | This includes CRC calculation, handling of Counter.   */
/*                  | The function checks only one single data in one       */
/*                  | cycle, it does not determine|compute the accumulated  */
/*                  | state of the communication link.                      */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | None                                                  */
/* Notes            | None                                                  */
/****************************************************************************/
/* [lib_SC1-1_e2e_1016] */
static FUNC(void, E2E_CODE) E2E_P07CheckData
/* Implements [lib_SDD1-1_e2e_0109] */
( P2CONST(E2E_P07ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P07CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint32 Length )
{
    uint32          u4_Offset;
    uint32          u4_AryIndex;
    uint32          u4_ReceivedLength;
    uint32          u4_ReceivedCounter;
    uint32          u4_ReceivedDataID;
    uint64          u8_ReceivedCRC;
    uint64          u8_CrcResult;
    uint32          u4_DeltaCounter;

    /* PRS_E2E_00488 */ /* Compute offset */
    u4_Offset = ConfigPtr->Offset >> E2E_USE_SHIFT_DIV_8;

    /* PRS_E2E_00497 */ /* Read Length */
    u4_AryIndex  = u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA;
    u4_ReceivedLength = DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE;
    u4_ReceivedLength = (uint32)(u4_ReceivedLength << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO;
    u4_ReceivedLength = (uint32)(u4_ReceivedLength << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_LENGTH_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE;
    u4_ReceivedLength = (uint32)(u4_ReceivedLength << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];

    /* PRS_E2E_00498 */ /* Read Counter */
    u4_AryIndex  = u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA;
    u4_ReceivedCounter = DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE;
    u4_ReceivedCounter = (uint32)(u4_ReceivedCounter << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO;
    u4_ReceivedCounter = (uint32)(u4_ReceivedCounter << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_P07_COUNTER_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE;
    u4_ReceivedCounter = (uint32)(u4_ReceivedCounter << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];

    /* PRS_E2E_00499 */ /* Read DataID */
    u4_AryIndex  = u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA;
    u4_ReceivedDataID = DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_ONE;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_TWO;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U2_P07_DATAID_POS_IN_DATA + E2E_U4_ARRAY_INDEX_THREE;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];

    /* PRS_E2E_00500 */ /* Read CRC */
    u4_AryIndex  = u4_Offset;
    u8_ReceivedCRC = DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_ONE;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_TWO;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_THREE;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_FOUR;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_FIVE;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_SIX;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];
    u4_AryIndex  = u4_Offset + E2E_U4_ARRAY_INDEX_SEVEN;
    u8_ReceivedCRC = (uint64)(u8_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u4_AryIndex];

    /* PRS_E2E_00492 */ /* Compute CRC */
    u8_CrcResult = E2E_P07CalculateCrc( DataPtr, u4_Offset, Length );

    /* PRS_E2E_00501 */ /* Do Checks */
    if( u8_ReceivedCRC == u8_CrcResult )
    {
        if( u4_ReceivedDataID == ConfigPtr->DataID )
        {
            if( u4_ReceivedLength == Length )
            {
                /* taking into wrap around 0xFFFFFFFF */
                if( u4_ReceivedCounter >= StatePtr->Counter )
                {
                    u4_DeltaCounter = u4_ReceivedCounter - StatePtr->Counter;
                }
                else
                {
                    u4_DeltaCounter = (E2E_U4_P07_COUNTER_NEGATIVE_TO_POSITIVE - (StatePtr->Counter - u4_ReceivedCounter)) + (uint32)E2E_DELTA_COUNTER_WRAP_AROUND;
                }
                if( u4_DeltaCounter <= ConfigPtr->MaxDeltaCounter )
                {
                    if( u4_DeltaCounter > (uint32)E2E_DELTA_COUNTER_NUM_ZERO )
                    {
                        if( u4_DeltaCounter == (uint32)E2E_DELTA_COUNTER_NUM_ONE )
                        {
                            StatePtr->Status = E2E_P07STATUS_OK;
                        }
                        else
                        {
                            StatePtr->Status = E2E_P07STATUS_OKSOMELOST;
                        }
                    }
                    else
                    {
                        StatePtr->Status = E2E_P07STATUS_REPEATED;
                    }
                }
                else
                {
                    StatePtr->Status = E2E_P07STATUS_WRONGSEQUENCE;
                }
                StatePtr->Counter = u4_ReceivedCounter;
            }
            else
            {
                StatePtr->Status = E2E_P07STATUS_ERROR;
            }
        }
        else
        {
            StatePtr->Status = E2E_P07STATUS_ERROR;
        }
    }
    else
    {
        StatePtr->Status = E2E_P07STATUS_ERROR;
    }
    return;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/01/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
