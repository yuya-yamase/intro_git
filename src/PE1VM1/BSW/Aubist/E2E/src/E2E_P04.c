/* E2E_P04_c_v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_P04/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes            | SWS_E2E_00215, PRS_E2E_00221, PRS_E2E_00217           */
/*                  | PRS_E2E_00012, PRS_E2E_00372                          */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <E2E.h>
#include "../inc/E2E_Local_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_U4_P04_CRCSTARTVALUE                ((uint32)0xFFFFFFFFUL)
#define E2E_U2_P04_DATALEN_BIT_MAX              ((uint16)32768U)
#define E2E_P04_LENGTH_BYTE_SIZE                (2U)
#define E2E_U2_P04_COUNTER_POS_IN_DATA          ((uint16)2U)
#define E2E_P04_COUNTER_BYTE_SIZE               (2U)
#define E2E_U2_P04_DATAID_POS_IN_DATA           ((uint16)4U)
#define E2E_P04_DATAID_BYTE_SIZE                (4U)
#define E2E_U2_P04_CRC_POS_IN_DATA              ((uint16)8U)
#define E2E_P04_CRC_BYTE_SIZE                   (4U)
#define E2E_U1_P04_CRC_FIRST_CALC_POS_IN_DATA   ((uint8)0U)
#define E2E_U4_P04_CRC_FIRST_CALC_BYTE_SIZE     ((uint32)(E2E_P04_LENGTH_BYTE_SIZE + E2E_P04_COUNTER_BYTE_SIZE + E2E_P04_DATAID_BYTE_SIZE))
#define E2E_P04_HEADER_BYTE_SIZE                (E2E_P04_LENGTH_BYTE_SIZE + E2E_P04_COUNTER_BYTE_SIZE + E2E_P04_DATAID_BYTE_SIZE + E2E_P04_CRC_BYTE_SIZE)
#define E2E_U2_P04_HEADER_BIT_LEN               ((uint16)96U)
#define E2E_U2_P04_COUNTER_NEGATIVE_TO_POSITIVE ((uint16)0xFFFFU)
#define E2E_U2_P04_PROTECTCOUNTER_INIT          ((uint16)0x0000U)
#define E2E_U2_P04_CHECKCOUNTER_INIT            ((uint16)0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_0138] */
static FUNC(uint32, E2E_CODE) E2E_P04CalculateCrc( P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Offset, uint16 Length );
/* Implements [lib_SDD1-1_e2e_0038] */
/* [lib_SC1-1_e2e_0143] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckConf( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );
/* Implements [lib_SDD1-1_e2e_0043] */
/* [lib_SC1-1_e2e_0148] */
static FUNC(void, E2E_CODE) E2E_P04CheckData( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length );
/* Implements [lib_SDD1-1_e2e_0048] */

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
/* Function Name    | E2E_P04Protect                                        */
/* Description      | Protects the array|buffer to be transmitted using the */
/*                  | E2E profile 4 . This includes checksum calculation,   */
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
/* Notes            | SWS_E2E_00338, PRS_E2E_00362                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_0011] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect
/* Implements [lib_SDD1-1_e2e_0011] */
( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    uint16          u2_Offset;
    uint32          u4_CrcResult;
    uint16          u2_CfgMinDataLengthByte;
    uint16          u2_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00363 */ /* Verify inputs of the protect function */
    if( (StatePtr != NULL_PTR) && (DataPtr != NULL_PTR) )
    {
        u1_Ret = E2E_P04CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            u2_CfgMinDataLengthByte = (uint16)(ConfigPtr->MinDataLength >> E2E_U2_BIT_SHIFT_3);
            u2_CfgMaxDataLengthByte = (uint16)(ConfigPtr->MaxDataLength >> E2E_U2_BIT_SHIFT_3);
            if( (Length >= u2_CfgMinDataLengthByte) && (Length <= u2_CfgMaxDataLengthByte) )
            {
                /* PRS_E2E_00376 */ /* Compute offset */ /* compute local variable uint16 Offset, which is in [byte] */
                u2_Offset = (uint16)(ConfigPtr->Offset >> E2E_U2_BIT_SHIFT_3);

                /* PRS_E2E_00364 */ /* Write Length */
                DataPtr[u2_Offset + E2E_U2_ARRAY_INDEX_ONE] = (uint8)(Length & (uint16)E2E_MASK_BYTE);
                DataPtr[u2_Offset] = (uint8)(Length >> (uint16)E2E_BIT_SHIFT_8);

                /* PRS_E2E_00365 */ /* Write Counter */
                DataPtr[u2_Offset + E2E_U2_P04_COUNTER_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE] = (uint8)(StatePtr->Counter & (uint16)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_COUNTER_POS_IN_DATA] = (uint8)(StatePtr->Counter >> (uint16)E2E_BIT_SHIFT_8);

                /* PRS_E2E_00326, PRS_E2E_00366 */ /* Write DataID */
                DataPtr[u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_THREE] = (uint8)(ConfigPtr->DataID & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_TWO] = (uint8)((ConfigPtr->DataID >> (uint32)E2E_BIT_SHIFT_8) & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE] = (uint8)((ConfigPtr->DataID >> E2E_U4_BIT_SHIFT_16) & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA] = (uint8)(ConfigPtr->DataID >> E2E_U4_BIT_SHIFT_24);

                /* Compute CRC */
                u4_CrcResult = E2E_P04CalculateCrc( DataPtr, u2_Offset, Length );

                /* PRS_E2E_00368 */ /* Write CRC */
                DataPtr[u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_THREE] = (uint8)(u4_CrcResult & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_TWO] = (uint8)((u4_CrcResult >> (uint32)E2E_BIT_SHIFT_8) & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE] = (uint8)((u4_CrcResult >> E2E_U4_BIT_SHIFT_16) & (uint32)E2E_MASK_BYTE);
                DataPtr[u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA] = (uint8)(u4_CrcResult >> E2E_U4_BIT_SHIFT_24);

                /* PRS_E2E_00478, PRS_E2E_00369 */ /* Increment Counter */
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
/* Function Name    | E2E_P04ProtectInit                                    */
/* Description      | Initializes the protection state.[E2E Profile 04]     */
/* Preconditions    | None                                                  */
/* Parameters       | *StatePtr : Pointer to port|data communication state. */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00373                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_0012] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit
/* Implements [lib_SDD1-1_e2e_0012] */
( P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00377 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        StatePtr->Counter = E2E_U2_P04_PROTECTCOUNTER_INIT;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P04Check                                          */
/* Description      | Checks the Data received using the E2E profile 4 .    */
/*                  | This includes CRC calculation, handling of Counter    */
/*                  | and Data ID. The function checks only one single      */
/*                  | data in one cycle, it does not determine|compute the  */
/*                  | accumulated state of the communication link.          */
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
/* Notes            | SWS_E2E_00339, PRS_E2E_00355                          */
/****************************************************************************/
/* [lib_SC1-1_e2e_0013] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check
/* Implements [lib_SDD1-1_e2e_0013] */
( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    boolean         b_NewDataAvailable = (boolean)FALSE;
    uint16          u2_CfgMinDataLengthByte;
    uint16          u2_CfgMaxDataLengthByte;

    /* SWS_E2E_00047, PRS_E2E_00356 */ /* Verify inputs of the check function */
    if( StatePtr != NULL_PTR )
    {
        u1_Ret = E2E_P04CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            /* Check: Either both Data and Length mean that a message is available, or both */
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
                    E2E_P04CheckData( ConfigPtr, StatePtr, DataPtr, Length );
                }
                else
                {
                    StatePtr->Status = E2E_P04STATUS_NONEWDATA;
                }
            }
        }
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P04CheckInit                                      */
/* Description      | Initializes the check state[E2E Profile 04]           */
/* Preconditions    | None                                                  */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00350                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_0014] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit
/* Implements [lib_SDD1-1_e2e_0014] */
( P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00378 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        StatePtr->Counter   = E2E_U2_P04_CHECKCOUNTER_INIT;
        StatePtr->Status    = E2E_P04STATUS_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P04MapStatusToSM                                  */
/* Description      | The function maps the check status of Profile 4 to a  */
/*                  | generic check status, which can be used by E2E state  */
/*                  | machine check function. The E2E Profile 4 delivers a  */
/*                  | more fine-granular status, but this is not relevant   */
/*                  | FOR the E2E state machine.                            */
/* Preconditions    | None                                                  */
/* Parameters       | CheckReturn       : Return value of the E2E_P04Check  */
/*                  |                     function                          */
/*                  | Status            : Status determined by E2E_P04Check */
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
/* Notes            | SWS_E2E_00349                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_0015] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM
/* Implements [lib_SDD1-1_e2e_0015] */
( Std_ReturnType CheckReturn, E2E_P04CheckStatusType Status )
{
    E2E_PCheckStatusType u1_Ret;

    if( CheckReturn == E2E_E_OK )
    {
        /* SWS_E2E_00351, PRS_E2E_00600 */
        if( (Status == E2E_P04STATUS_OK) ||
            (Status == E2E_P04STATUS_OKSOMELOST)  )
        {
            u1_Ret = E2E_P_OK;
        }
        else if(Status == E2E_P04STATUS_ERROR)
        {
            u1_Ret = E2E_P_ERROR;
        }
        else if(Status == E2E_P04STATUS_REPEATED)
        {
            u1_Ret = E2E_P_REPEATED;
        }
        else if(Status == E2E_P04STATUS_NONEWDATA)
        {
            u1_Ret = E2E_P_NONEWDATA;
        }
        else if(Status == E2E_P04STATUS_WRONGSEQUENCE)
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
        /* SWS_E2E_00352 */
        u1_Ret = E2E_P_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_P04CalculateCrc                                   */
/* Description      | The diagram of the function E2E_P04Protect and        */
/*                  | E2E_P04Check have a sub-diagram specifying the        */
/*                  | calculation of CRC.                                   */
/* Preconditions    | None                                                  */
/* Parameters       | *DataPtr      : Pointer to Data to be transmitted.    */
/*                  | Offset        : E2E Offset                            */
/*                  | Length        : Data length                           */
/* Return Value     | uint32        : Calculated CRC                        */
/* Notes            | Do not check parameter is NULL                        */
/****************************************************************************/
/* [lib_SC1-1_e2e_0038] */
static FUNC(uint32, E2E_CODE) E2E_P04CalculateCrc
/* Implements [lib_SDD1-1_e2e_0038] */
( P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Offset, uint16 Length )
{
    uint32   u4_CrcFirst;
    uint32   u4_CrcSecond;
    uint32   u4_CrcResult;

    /* PRS_E2E_00367, PRS_E2E_00329, PRS_E2E_00330   */ /* Compute CRC */
    /* compute CRC over bytes that are before CRC.   */
    /* computation length: offset + 8, where:        */
    /* offset: number of bytes before the E2E header */
    /* 8: number of header bytes before E2E CRC      */
    u4_CrcFirst = Crc_CalculateCRC32P4( &DataPtr[E2E_U1_P04_CRC_FIRST_CALC_POS_IN_DATA], (uint32)Offset + E2E_U4_P04_CRC_FIRST_CALC_BYTE_SIZE, E2E_U4_P04_CRCSTARTVALUE, (boolean)TRUE );
    u4_CrcResult = u4_CrcFirst;
    if( (Offset + E2E_P04_HEADER_BYTE_SIZE) < Length )
    {
        /* PRS_E2E_00329, PRS_E2E_00330 */ /* Compute CRC over bytes that are after CRC [IF any]. */
        u4_CrcSecond = Crc_CalculateCRC32P4( &DataPtr[Offset+E2E_P04_HEADER_BYTE_SIZE], (uint32)Length - (uint32)Offset - (uint32)E2E_P04_HEADER_BYTE_SIZE, u4_CrcFirst, (boolean)FALSE );
        u4_CrcResult = u4_CrcSecond;
    }

    return u4_CrcResult;
}

/****************************************************************************/
/* Function Name    | E2E_P04CheckConf                                      */
/* Description      | Check the E2E_P04ConfigType value.                    */
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
/* [lib_SC1-1_e2e_0043] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckConf
/* Implements [lib_SDD1-1_e2e_0043] */
( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
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

        /* SWS_E2E_00047, SWS_E2E_00334 */
        if( (ConfigPtr->MinDataLength < E2E_U2_P04_HEADER_BIT_LEN) ||
                (ConfigPtr->MinDataLength > E2E_U2_P04_DATALEN_BIT_MAX) ||
                (u2_CfgMinDataLengthMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                (ConfigPtr->MaxDataLength < ConfigPtr->MinDataLength) ||
                (ConfigPtr->MaxDataLength > E2E_U2_P04_DATALEN_BIT_MAX) ||
                (u2_CfgMaxDataLengthMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                (u2_CfgOffsetMlti8 != (uint16)E2E_REMAINDER_ZERO) ||
                ((ConfigPtr->MaxDataLength - E2E_U2_P04_HEADER_BIT_LEN) < ConfigPtr->Offset ) )
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
/* Function Name    | E2E_P04CheckData                                      */
/* Description      | Checks the Data received using the E2E profile 4 .    */
/*                  | This includes CRC calculation, handling of Counter    */
/*                  | and Data ID. The function checks only one single      */
/*                  | data in one cycle, it does not determine|compute the  */
/*                  | accumulated state of the communication link.          */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | Length        : Length of the data in bytes           */
/* Return Value     | None                                                  */
/* Notes            | None                                                  */
/****************************************************************************/
/* [lib_SC1-1_e2e_0048] */
static FUNC(void, E2E_CODE) E2E_P04CheckData
/* Implements [lib_SDD1-1_e2e_0048] */
( P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint16 Length )
{
    uint16          u2_Offset;
    uint16          u2_ReceivedLength;
    uint16          u2_ReceivedCounter;
    uint32          u4_ReceivedDataID;
    uint32          u4_ReceivedCRC;
    uint32          u4_CrcResult;
    uint16          u2_DeltaCounter;
    uint16          u2_AryIndex;

    /* PRS_E2E_00376 */ /* Compute offset */
    u2_Offset = (uint16)(ConfigPtr->Offset >> E2E_U2_BIT_SHIFT_3);

    /* PRS_E2E_00357 */ /* Read Length value in Data */
    u2_AryIndex  = u2_Offset;
    u2_ReceivedLength = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_ARRAY_INDEX_ONE;
    u2_ReceivedLength = (uint16)(u2_ReceivedLength << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* PRS_E2E_00358 */ /* Read Counter value in Data */
    u2_AryIndex  = u2_Offset + E2E_U2_P04_COUNTER_POS_IN_DATA;
    u2_ReceivedCounter = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_COUNTER_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE;
    u2_ReceivedCounter = (uint16)(u2_ReceivedCounter << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* PRS_E2E_00359 */ /* Read DataID value in Data */
    u2_AryIndex  = u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA;
    u4_ReceivedDataID = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_TWO;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_DATAID_POS_IN_DATA + E2E_U2_ARRAY_INDEX_THREE;
    u4_ReceivedDataID = (uint32)(u4_ReceivedDataID << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* PRS_E2E_00360 */ /* Read CRC value in Data */
    u2_AryIndex  = u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA;
    u4_ReceivedCRC = DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_ONE;
    u4_ReceivedCRC = (uint32)(u4_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_TWO;
    u4_ReceivedCRC = (uint32)(u4_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];
    u2_AryIndex  = u2_Offset + E2E_U2_P04_CRC_POS_IN_DATA + E2E_U2_ARRAY_INDEX_THREE;
    u4_ReceivedCRC = (uint32)(u4_ReceivedCRC << E2E_BIT_SHIFT_8) | DataPtr[u2_AryIndex];

    /* Compute CRC */
    u4_CrcResult = E2E_P04CalculateCrc( DataPtr, u2_Offset, Length );

    /* PRS_E2E_00361 */ /* Do checks */
    if( u4_ReceivedCRC == u4_CrcResult )
    {
        if( u4_ReceivedDataID == ConfigPtr->DataID )
        {
            if( u2_ReceivedLength == Length )
            {
                /* taking into wrap around 0xFFFF */
                if( u2_ReceivedCounter >= StatePtr->Counter )
                {
                    u2_DeltaCounter = u2_ReceivedCounter - StatePtr->Counter;
                }
                else
                {
                    u2_DeltaCounter = (E2E_U2_P04_COUNTER_NEGATIVE_TO_POSITIVE - (StatePtr->Counter - u2_ReceivedCounter)) + (uint16)E2E_DELTA_COUNTER_WRAP_AROUND;
                }

                if( u2_DeltaCounter <= ConfigPtr->MaxDeltaCounter )
                {
                    if( u2_DeltaCounter > (uint16)E2E_DELTA_COUNTER_NUM_ZERO )
                    {
                        if( u2_DeltaCounter == (uint16)E2E_DELTA_COUNTER_NUM_ONE )
                        {
                            StatePtr->Status = E2E_P04STATUS_OK;
                        }
                        else
                        {
                            StatePtr->Status = E2E_P04STATUS_OKSOMELOST;
                        }
                    }
                    else
                    {
                        StatePtr->Status = E2E_P04STATUS_REPEATED;
                    }
                }
                else
                {
                    StatePtr->Status = E2E_P04STATUS_WRONGSEQUENCE;
                }
                StatePtr->Counter = u2_ReceivedCounter;
            }
            else
            {
                StatePtr->Status = E2E_P04STATUS_ERROR;
            }
        }
        else
        {
            StatePtr->Status = E2E_P04STATUS_ERROR;
        }
    }
    else
    {
        StatePtr->Status = E2E_P04STATUS_ERROR;
    }
    return;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2021/08/03                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
