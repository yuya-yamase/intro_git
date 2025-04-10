/* E2E_P01_c_v2-1-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name      | E2E/E2E_P01/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes            | SWS_E2E_00215, PRS_E2E_00221, PRS_E2E_00217           */
/*                  | PRS_E2E_00012, PRS_E2E_00218, PRS_E2E_00070           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <E2E.h>
#include "../inc/E2E_Local_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define E2E_U1_P01_CRCSTARTVALUE                        ((uint8)0xFFU)
#define E2E_U2_P01_DATALEN_BIT_MAX                      ((uint16)240U)
#define E2E_U2_P01_CRC_BIT_LEN                          ((uint16)8U)
#define E2E_U2_P01_COUNTER_BIT_LEN                      ((uint16)4U)
#define E2E_U2_P01_NIBBLE_BIT_LEN                       ((uint16)4U)
#define E2E_U2_P01_MIN_BIT_LEN_CHK                      ((uint16)4U)
#define E2E_U2_P01_MIN_BIT_LENGTH                       ((uint16)(E2E_U2_P01_CRC_BIT_LEN + (E2E_U2_P01_COUNTER_BIT_LEN + E2E_U2_P01_MIN_BIT_LEN_CHK)))
#define E2E_U1_P01_COUNTER_MAX                          ((uint8)0x0EU)
#define E2E_U1_P01_RECEIVEDCOUNTER_CHECK                ((uint8)0x0FU)
#define E2E_U4_P01_DATAID_BYTE_SIZE                     ((uint32)1UL)
#define E2E_U1_P01_DATAID_NIBBLE_CRC_DATA               ((uint8)0U)
#define E2E_U1_P01_CRC_XOR_VALUE                        ((uint8)0xFFU)
#define E2E_U2_P01_CRC_POS_CHECK_VALUE                  ((uint16)8U)
#define E2E_P01_CRC_BYTE_SIZE                           (1U)
#define E2E_U1_P01_COUNTER_NEGATIVE_TO_POSITIVE         ((uint8)0x0EU)
#define E2E_U1_P01_PROTECTCOUNTER_INIT                  ((uint8)0U)
#define E2E_U1_P01_CHECKLASTVALIDCOUNTER_INIT           ((uint8)0U)
#define E2E_U1_P01_CHECKMAXDELTACOUNTER_INIT            ((uint8)0U)
#define E2E_U1_P01_CHECKLOSTDATA_INIT                   ((uint8)0U)
#define E2E_U1_P01_CHECKNONEWORREPEATEDDATACOUNTER_INIT ((uint8)0U)
#define E2E_U1_P01_CHECKSYNCCOUNTER_INIT                ((uint8)0U)
#define E2E_U1_P01_CRC_CALCFIRST_INIT                   ((uint8)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#define E2E_START_SEC_CODE
#include <E2E_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/* [lib_SC1-1_e2e_1110] */
static FUNC(uint8, E2E_CODE) E2E_P01CalculateCrc( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint8 Counter );
/* Implements [lib_SDD1-1_e2e_0122] */
/* [lib_SC1-1_e2e_1111] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckConf( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr );
/* Implements [lib_SDD1-1_e2e_0123] */
/* [lib_SC1-1_e2e_1112] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckData( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr );
/* Implements [lib_SDD1-1_e2e_0124] */

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
/* Function Name    | E2E_P01Protect                                        */
/* Description      | Protects the array|buffer to be transmitted using the */
/*                  | E2E profile 1 . This includes checksum calculation,   */
/*                  | handling of counter and Data ID.                      */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to Data to be transmitted.    */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | SWS_E2E_00166                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1113] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01Protect
/* Implements [lib_SDD1-1_e2e_0112] */
( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;
    uint8           u1_CrcResult;
    uint16          u2_CfgCounterOffsetMlti8;
    uint16          u2_CfgDataIDNibOffsetMlti8;
    uint16          u2_CfgCounterOffsetByte;
    uint16          u2_CfgCRCOffsetByte;
    uint16          u2_DataIDNibbleOffsetByte;

    /* SWS_E2E_00047 */
    if( (StatePtr != NULL_PTR) && (DataPtr != NULL_PTR) )
    {
        u1_Ret = E2E_P01CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            if( StatePtr->Counter <= E2E_U1_P01_COUNTER_MAX )
            {
                u2_CfgCounterOffsetMlti8    = (uint16)(ConfigPtr->CounterOffset & E2E_U2_MASK_MULTIPLE8);
                u2_CfgCounterOffsetByte     = (uint16)(ConfigPtr->CounterOffset >> E2E_U2_BIT_SHIFT_3);
                /* PRS_E2E_00195 */
                if( u2_CfgCounterOffsetMlti8 == (uint16)E2E_REMAINDER_ZERO )
                {
                    /* write counter */
                    DataPtr[u2_CfgCounterOffsetByte] = (uint8)(DataPtr[u2_CfgCounterOffsetByte] & E2E_U1_MASK_HIGH_NIBBLE) | (uint8)(StatePtr->Counter);
                }
                else
                {
                    /* write counter */
                    DataPtr[u2_CfgCounterOffsetByte] = (uint8)(DataPtr[u2_CfgCounterOffsetByte] & E2E_U1_MASK_LOW_NIBBLE) | (uint8)(StatePtr->Counter << E2E_U1_BIT_SHIFT_4);
                }

                /* PRS_E2E_00163 */
                if( ConfigPtr->DataIDMode == (uint16)E2E_P01_DATAID_NIBBLE )
                {
                    u2_CfgDataIDNibOffsetMlti8 = (uint16)(ConfigPtr->DataIDNibbleOffset & E2E_U2_MASK_MULTIPLE8);
                    u2_DataIDNibbleOffsetByte = (uint16)(ConfigPtr->DataIDNibbleOffset >> E2E_U2_BIT_SHIFT_3);
                    if( u2_CfgDataIDNibOffsetMlti8 == (uint16)E2E_REMAINDER_ZERO )
                    {
                        /* write dataid */
                        DataPtr[u2_DataIDNibbleOffsetByte] = (DataPtr[u2_DataIDNibbleOffsetByte] & E2E_U1_MASK_HIGH_NIBBLE) | (uint8)(ConfigPtr->DataID >> (uint8)E2E_BIT_SHIFT_8);
                    }
                    else
                    {
                        /* write dataid */
                        DataPtr[u2_DataIDNibbleOffsetByte] = (DataPtr[u2_DataIDNibbleOffsetByte] & E2E_U1_MASK_LOW_NIBBLE) | ((uint8)(ConfigPtr->DataID >> E2E_U1_BIT_SHIFT_4) & E2E_U1_MASK_HIGH_NIBBLE);
                    }
                }

                /* PRS_E2E_00082 */ /* Calculate CRC overDataId and Data */
                u1_CrcResult = E2E_P01CalculateCrc( ConfigPtr, DataPtr, StatePtr->Counter );

                u2_CfgCRCOffsetByte = (uint16)(ConfigPtr->CRCOffset >> E2E_U2_BIT_SHIFT_3);
                /* CRC is written to the Data at configured location */
                DataPtr[u2_CfgCRCOffsetByte] = u1_CrcResult;

                /* PRS_E2E_00075 */
                StatePtr->Counter++;
                if( E2E_U1_P01_COUNTER_MAX < StatePtr->Counter ) 
                {
                    StatePtr->Counter = E2E_U1_P01_PROTECTCOUNTER_INIT;
                }
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
/* Function Name    | E2E_P01ProtectInit                                    */
/* Description      | Initializes the protection state.[E2E Profile 01]     */
/* Preconditions    | None                                                  */
/* Parameters       | *StatePtr : Pointer to port|data communication state. */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00385                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1114] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01ProtectInit
/* Implements [lib_SDD1-1_e2e_0113] */
( P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00386 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        /* PRS_E2E_00075 */
        StatePtr->Counter = E2E_U1_P01_PROTECTCOUNTER_INIT;
    }

    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P01Check                                          */
/* Description      | Checks the Data received using the E2E profile 1 .    */
/*                  | This includes CRC calculation, handling of Counter    */
/*                  | and Data ID.                                          */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to received data.             */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | SWS_E2E_00158                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1115] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01Check
/* Implements [lib_SDD1-1_e2e_0114] */
( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_INPUTERR_NULL;

    /* SWS_E2E_00047 */
    if( (StatePtr != NULL_PTR) && (DataPtr != NULL_PTR) )
    {
        u1_Ret = E2E_P01CheckConf( ConfigPtr );

        if( u1_Ret == E2E_E_OK )
        {
            /* PRS_E2E_00196 */
            /* At every function invocation, the maximum allowed delta between previous and current Counter is incremented. */
            StatePtr->MaxDeltaCounter++;
            if( StatePtr->MaxDeltaCounter > E2E_U1_P01_COUNTER_MAX )
            {
                StatePtr->MaxDeltaCounter = E2E_U1_P01_COUNTER_MAX;
            }

            /* If any NEW data is available to be checked. */
            if( StatePtr->NewDataAvailable == (boolean)TRUE )
            {
                u1_Ret = E2E_P01CheckData( ConfigPtr, StatePtr, DataPtr );
            }
            else
            {
                if( StatePtr->NoNewOrRepeatedDataCounter < E2E_U1_P01_COUNTER_MAX )
                {
                    StatePtr->NoNewOrRepeatedDataCounter++;
                }
                StatePtr->Status = E2E_P01STATUS_NONEWDATA;
            }
        }
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P01CheckInit                                      */
/* Description      | Initializes the check state[E2E Profile 01]           */
/* Preconditions    | None                                                  */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_NULL   : At least one pointer          */
/*                  |                         parameter is a NULL pointer   */
/* Notes            | SWS_E2E_00390                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1116] */
FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckInit
/* Implements [lib_SDD1-1_e2e_0115] */
( P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
    Std_ReturnType u1_Ret = E2E_E_OK;

    /* SWS_E2E_00389 */
    if( StatePtr == NULL_PTR )
    {
        u1_Ret = E2E_E_INPUTERR_NULL;
    }
    else
    {
        StatePtr->LastValidCounter              = E2E_U1_P01_CHECKLASTVALIDCOUNTER_INIT;
        StatePtr->MaxDeltaCounter               = E2E_U1_P01_CHECKMAXDELTACOUNTER_INIT;
        StatePtr->WaitForFirstData              = (boolean)TRUE;
        StatePtr->NewDataAvailable              = (boolean)TRUE;
        StatePtr->LostData                      = E2E_U1_P01_CHECKLOSTDATA_INIT;
        StatePtr->Status                        = E2E_P01STATUS_NONEWDATA;
        StatePtr->NoNewOrRepeatedDataCounter    = E2E_U1_P01_CHECKNONEWORREPEATEDDATACOUNTER_INIT;
        StatePtr->SyncCounter                   = E2E_U1_P01_CHECKSYNCCOUNTER_INIT;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Function Name    | E2E_P01MapStatusToSM                                  */
/* Description      | The function maps the check status of Profile 1 to a  */
/*                  | generic check status, which can be used by E2E state  */
/*                  | machine check function. The E2E Profile 1 delivers a  */
/*                  | more fine-granular status, but this is not relevant   */
/*                  | FOR the E2E state machine.                            */
/* Preconditions    | None                                                  */
/* Parameters       | CheckReturn       : Return value of the E2E_P01Check  */
/*                  |                     function                          */
/*                  | Status            : Status determined by E2E_P01Check */
/*                  |                     function                          */
/*                  | profileBehavior   : FALSE: check has the legacy       */
/*                  |                     behavior, before R4 . 2           */
/*                  |                     TRUE: check behaves like new      */
/*                  |                     P4|P5|P6 profiles introduced      */
/*                  |                     in R4 . 2                         */
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
/* Notes            | SWS_E2E_00382                                         */
/****************************************************************************/
/* [lib_SC1-1_e2e_1117] */
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P01MapStatusToSM
/* Implements [lib_SDD1-1_e2e_0116] */
( Std_ReturnType CheckReturn, E2E_P01CheckStatusType Status, boolean profileBehavior )
{
    E2E_PCheckStatusType u1_Ret;

    if( (CheckReturn == E2E_E_OK) && (profileBehavior == (boolean)TRUE) )
    {
        /* SWS_E2E_00383, PRS_E2E_00598 */
        if( (Status == E2E_P01STATUS_OK) ||
            (Status == E2E_P01STATUS_OKSOMELOST) ||
            (Status == E2E_P01STATUS_SYNC)  )
        {
            u1_Ret = E2E_P_OK;
        }
        else if(Status == E2E_P01STATUS_WRONGCRC)
        {
            u1_Ret = E2E_P_ERROR;
        }
        else if(Status == E2E_P01STATUS_REPEATED)
        {
            u1_Ret = E2E_P_REPEATED;
        }
        else if(Status == E2E_P01STATUS_NONEWDATA)
        {
            u1_Ret = E2E_P_NONEWDATA;
        }
        else if((Status == E2E_P01STATUS_WRONGSEQUENCE) ||
                (Status == E2E_P01STATUS_INITIAL)  )
        {
            u1_Ret = E2E_P_WRONGSEQUENCE;
        }
        else
        {
            u1_Ret = E2E_P_ERROR;
        }
    }
    else if( (CheckReturn == E2E_E_OK) && (profileBehavior == (boolean)FALSE) )
    {
        /* SWS_E2E_00476 */
        if( (Status == E2E_P01STATUS_OK) ||
            (Status == E2E_P01STATUS_OKSOMELOST) ||
            (Status == E2E_P01STATUS_INITIAL)  )
        {
            u1_Ret = E2E_P_OK;
        }
        else if(Status == E2E_P01STATUS_WRONGCRC)
        {
            u1_Ret = E2E_P_ERROR;
        }
        else if(Status == E2E_P01STATUS_REPEATED)
        {
            u1_Ret = E2E_P_REPEATED;
        }
        else if(Status == E2E_P01STATUS_NONEWDATA)
        {
            u1_Ret = E2E_P_NONEWDATA;
        }
        else if((Status == E2E_P01STATUS_WRONGSEQUENCE) ||
                (Status == E2E_P01STATUS_SYNC)  )
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
        /* SWS_E2E_00384 */
        u1_Ret = E2E_P_ERROR;
    }

    /* SWS_E2E_00011 */
    return u1_Ret;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name    | E2E_P01CalculateCrc                                   */
/* Description      | The diagram of the function E2E_P01Protect() and      */
/*                  | E2E_P01Check() have a sub-diagram specifying the      */
/*                  | calculation of CRC.                                   */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *DataPtr      : Pointer to Data to be transmitted.    */
/*                  | Counter       : Counter                               */
/* Return Value     | uint8         : Calculated CRC                        */
/* Notes            | Do not check parameter is NULL                        */
/****************************************************************************/
/* [lib_SC1-1_e2e_1118] */
static FUNC(uint8, E2E_CODE) E2E_P01CalculateCrc
/* Implements [lib_SDD1-1_e2e_0122] */
( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr, uint8 Counter )
{
    uint8   u1_DataID;
    uint8   u1_CrcFirstTmp;
    uint8   u1_CrcFirst = E2E_U1_P01_CRC_CALCFIRST_INIT;
    uint8   u1_CrcSecond;
    uint8   u1_CrcResult;
    uint8   u1_CounterMlti2;
    uint16  u2_CfgDataLengthByte;
    uint16  u2_CfgCRCOffsetByte;
    uint8   u1_DataIdNibbleUseData = E2E_U1_P01_DATAID_NIBBLE_CRC_DATA;

    /* PRS_E2E_00082 */ /* Calculate CRC overDataId and Data */
    if(ConfigPtr->DataIDMode == E2E_P01_DATAID_BOTH)
    {
        /* PRS_E2E_00085 */
        u1_DataID = (uint8)(ConfigPtr->DataID & (uint16)E2E_MASK_BYTE);
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcFirstTmp = Crc_CalculateCRC8( (uint8*)&u1_DataID, E2E_U4_P01_DATAID_BYTE_SIZE, E2E_U1_P01_CRCSTARTVALUE, (boolean)FALSE );
        u1_DataID = (uint8)(ConfigPtr->DataID >> (uint8)E2E_BIT_SHIFT_8);
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcFirst = Crc_CalculateCRC8( (uint8*)&u1_DataID, E2E_U4_P01_DATAID_BYTE_SIZE, u1_CrcFirstTmp, (boolean)FALSE );
    }
    else if(ConfigPtr->DataIDMode == E2E_P01_DATAID_LOW)
    {
        u1_DataID = (uint8)(ConfigPtr->DataID & (uint16)E2E_MASK_BYTE);
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcFirst = Crc_CalculateCRC8( (uint8*)&u1_DataID, E2E_U4_P01_DATAID_BYTE_SIZE, E2E_U1_P01_CRCSTARTVALUE, (boolean)FALSE );
    }
    else if(ConfigPtr->DataIDMode == E2E_P01_DATAID_ALT)
    {
        /* PRS_E2E_00085 */
        u1_CounterMlti2 = (uint8)(Counter & E2E_U1_MASK_MULTIPLE2);
        u1_DataID = (uint8)(ConfigPtr->DataID >> (uint8)E2E_BIT_SHIFT_8);
        if( u1_CounterMlti2 == (uint8)E2E_REMAINDER_ZERO )
        {
            u1_DataID = (uint8)(ConfigPtr->DataID & (uint16)E2E_MASK_BYTE);
        }
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcFirst = Crc_CalculateCRC8( (uint8*)&u1_DataID, E2E_U4_P01_DATAID_BYTE_SIZE, E2E_U1_P01_CRCSTARTVALUE, (boolean)FALSE );
    }
    else if(ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE)
    {
        u1_DataID = (uint8)(ConfigPtr->DataID & (uint16)E2E_MASK_BYTE);
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcFirstTmp = Crc_CalculateCRC8( (uint8*)&u1_DataID, E2E_U4_P01_DATAID_BYTE_SIZE, E2E_U1_P01_CRCSTARTVALUE, (boolean)FALSE );
        u1_CrcFirst = Crc_CalculateCRC8( &u1_DataIdNibbleUseData, E2E_U4_P01_DATAID_BYTE_SIZE, u1_CrcFirstTmp, (boolean)FALSE );
    }
    else
    {
        (void) 0;/* DO nothing */
    }

    u2_CfgDataLengthByte    = (uint16)(ConfigPtr->DataLength >> E2E_U2_BIT_SHIFT_3);
    u2_CfgCRCOffsetByte     = (uint16)(ConfigPtr->CRCOffset >> E2E_U2_BIT_SHIFT_3);
    u1_CrcSecond = u1_CrcFirst;
    /* IF CRC is not the first byte */
    if( ConfigPtr->CRCOffset >= E2E_U2_P01_CRC_POS_CHECK_VALUE )
    {
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcSecond = Crc_CalculateCRC8( DataPtr, (uint32)u2_CfgCRCOffsetByte, u1_CrcFirst, (boolean)FALSE );
    }
    u1_CrcResult = u1_CrcSecond;
    if( u2_CfgCRCOffsetByte < (uint16)(u2_CfgDataLengthByte - (uint16)E2E_P01_CRC_BYTE_SIZE) )
    {
        /* PRS_E2E_00070, PRS_E2E_00190, PRS_E2E_00082 */
        u1_CrcResult = Crc_CalculateCRC8( &DataPtr[u2_CfgCRCOffsetByte+(uint16)E2E_P01_CRC_BYTE_SIZE], (uint32)u2_CfgDataLengthByte - (uint32)u2_CfgCRCOffsetByte - (uint32)E2E_P01_CRC_BYTE_SIZE, u1_CrcSecond, (boolean)FALSE );
    }
    u1_CrcResult = u1_CrcResult ^ E2E_U1_P01_CRC_XOR_VALUE;

    return u1_CrcResult;
}

/****************************************************************************/
/* Function Name    | E2E_P01CheckConf                                      */
/* Description      | Check the E2E_P01ConfigType value.                    */
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
/* [lib_SC1-1_e2e_1119] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckConf
/* Implements [lib_SDD1-1_e2e_0123] */
( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_OK;
    uint8           u1_DataIdUpperByte;
    uint8           u1_DataIdUpperByteTopNibble;
    uint16          u2_CfgDataLengthMlti8;
    uint16          u2_CfgCounterOffsetMlti4;
    uint16          u2_CfgCRCOffsetMlti8;
    uint16          u2_CfgNibbleOffsetMlti4;

    /* SWS_E2E_00047 */
    if( ConfigPtr != NULL_PTR )
    {
        u1_DataIdUpperByte          = (uint8)(ConfigPtr->DataID >> E2E_BIT_SHIFT_8);
        u1_DataIdUpperByteTopNibble = (uint8)(u1_DataIdUpperByte >> E2E_U1_BIT_SHIFT_4);
        u2_CfgDataLengthMlti8       = (uint16)(ConfigPtr->DataLength & E2E_U2_MASK_MULTIPLE8);
        u2_CfgCounterOffsetMlti4    = (uint16)(ConfigPtr->CounterOffset & E2E_U2_MASK_MULTIPLE4);
        u2_CfgCRCOffsetMlti8        = (uint16)(ConfigPtr->CRCOffset & E2E_U2_MASK_MULTIPLE8);
        u2_CfgNibbleOffsetMlti4     = (uint16)(ConfigPtr->DataIDNibbleOffset & E2E_U2_MASK_MULTIPLE4);

        /* SWS_E2E_00047, SWS_E2E_00018, PRS_E2E_00169, PRS_E2E_00306 */
        if( (u2_CfgDataLengthMlti8 != (uint16)E2E_REMAINDER_ZERO) || (u2_CfgCounterOffsetMlti4 != (uint16)E2E_REMAINDER_ZERO) ||
                (u2_CfgCRCOffsetMlti8 != (uint16)E2E_REMAINDER_ZERO) || (u2_CfgNibbleOffsetMlti4 != (uint16)E2E_REMAINDER_ZERO) ||
                (ConfigPtr->DataLength < E2E_U2_P01_MIN_BIT_LENGTH) || (E2E_U2_P01_DATALEN_BIT_MAX < ConfigPtr->DataLength) ||
                ((ConfigPtr->DataLength - E2E_U2_P01_COUNTER_BIT_LEN) < ConfigPtr->CounterOffset) ||
                ((ConfigPtr->DataLength - E2E_U2_P01_CRC_BIT_LEN) < ConfigPtr->CRCOffset) ||
                ((ConfigPtr->DataLength - E2E_U2_P01_NIBBLE_BIT_LEN) < ConfigPtr->DataIDNibbleOffset) ||
                (ConfigPtr->DataIDMode > E2E_P01_DATAID_NIBBLE) ||
                ((ConfigPtr->DataIDMode == E2E_P01_DATAID_LOW) && (u1_DataIdUpperByte != (uint8)E2E_DATAID_ZERO_VALUE)) ||
                ((ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) && (u1_DataIdUpperByteTopNibble != (uint8)E2E_DATAID_ZERO_VALUE)) ||
                ((ConfigPtr->DataIDMode != E2E_P01_DATAID_NIBBLE) && (ConfigPtr->DataIDNibbleOffset != (uint16)E2E_OFFSET_INIT_VALUE)) ||
                (ConfigPtr->MaxDeltaCounterInit > E2E_U1_P01_COUNTER_MAX) )
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
/* Function Name    | E2E_P01CheckData                                      */
/* Description      | Checks the Data received using the E2E profile 1 .    */
/*                  | This includes CRC calculation, handling of Counter    */
/*                  | and Data ID.                                          */
/* Preconditions    | None                                                  */
/* Parameters       | *ConfigPtr    : Pointer to STATIC configuration.      */
/*                  | *StatePtr     : Pointer to port|data communication    */
/*                  |                 state.                                */
/*                  | *DataPtr      : Pointer to received data.             */
/* Return Value     | Std_ReturnType                                        */
/*                  | E2E_E_OK              : Function completed            */
/*                  |                         successfully                  */
/*                  | E2E_E_INPUTERR_WRONG  : Function executed in wrong    */
/*                  |                         state                         */
/* Notes            | None                                                  */
/****************************************************************************/
/* [lib_SC1-1_e2e_1120] */
static FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckData
/* Implements [lib_SDD1-1_e2e_0124] */
( P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_DATA) ConfigPtr, P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr )
{
    Std_ReturnType  u1_Ret = E2E_E_OK;
    uint8           u1_ReceivedDataIDNibble;
    uint8           u1_DeltaCounter;
    uint8           u1_CalculatedResult;
    uint8           u1_ReceivedCounter;
    uint8           u1_ReceivedCRC;
    uint8           u1_dataid_highbyte;
    uint16          u2_CfgCounterOffsetByte;
    uint16          u2_CfgCounterOffsetMlti8;
    uint16          u2_CfgCRCOffsetByte;
    uint16          u2_CfgDataIDNibOffsetMlti8;
    uint16          u2_DataIDNibbleOffsetByte;

    u2_CfgCounterOffsetByte = (uint16)(ConfigPtr->CounterOffset >> E2E_U2_BIT_SHIFT_3);
    u2_CfgCounterOffsetMlti8 = (uint16)(ConfigPtr->CounterOffset & E2E_U2_MASK_MULTIPLE8);
    /* Read the Counter from Data, at the configured offset. */
    if( u2_CfgCounterOffsetMlti8 == (uint16)E2E_REMAINDER_ZERO )
    {
        u1_ReceivedCounter = DataPtr[u2_CfgCounterOffsetByte] & E2E_U1_MASK_LOW_NIBBLE;
    }
    else
    {
        u1_ReceivedCounter = DataPtr[u2_CfgCounterOffsetByte] >> E2E_U1_BIT_SHIFT_4;
    }

    if( u1_ReceivedCounter < E2E_U1_P01_RECEIVEDCOUNTER_CHECK )
    {
        u2_CfgCRCOffsetByte = (uint16)(ConfigPtr->CRCOffset >> E2E_U2_BIT_SHIFT_3);
        /* Read CRC from DataCalculate */
        u1_ReceivedCRC = DataPtr[u2_CfgCRCOffsetByte];

        if( ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE )
        {
            u2_CfgDataIDNibOffsetMlti8 = (uint16)(ConfigPtr->DataIDNibbleOffset & E2E_U2_MASK_MULTIPLE8);
            u2_DataIDNibbleOffsetByte = (uint16)(ConfigPtr->DataIDNibbleOffset >> E2E_U2_BIT_SHIFT_3);
            /* Read low nibble of high byte of Data ID from Data. */
            if( u2_CfgDataIDNibOffsetMlti8 == (uint16)E2E_REMAINDER_ZERO )
            {
                u1_ReceivedDataIDNibble = DataPtr[u2_DataIDNibbleOffsetByte] & E2E_U1_MASK_LOW_NIBBLE;
            }
            else
            {
                u1_ReceivedDataIDNibble = DataPtr[u2_DataIDNibbleOffsetByte] >> E2E_U1_BIT_SHIFT_4;
            }
        }

        /* Calculate CRC in the same way as the Sender did. */ /* Calculate CRC overDataId and Data */
        u1_CalculatedResult = E2E_P01CalculateCrc( ConfigPtr, DataPtr, u1_ReceivedCounter );

        if( u1_ReceivedCRC == u1_CalculatedResult )
        {
            /* Check IF received nibble is identical to the one in DataID. */
            u1_dataid_highbyte = (uint8)(ConfigPtr->DataID >> E2E_BIT_SHIFT_8);
            if( (ConfigPtr->DataIDMode == E2E_P01_DATAID_NIBBLE) && (u1_ReceivedDataIDNibble != u1_dataid_highbyte) )
            {
                StatePtr->Status = E2E_P01STATUS_WRONGCRC;
            }
            else
            {
                if( StatePtr->WaitForFirstData == (boolean)TRUE )
                {
                    /* This is the first message with correct CRC, WaitForFirstData is therefore set to false. Counter is not checked as it cannot be done yet. */
                    StatePtr->WaitForFirstData = (boolean)FALSE;

                    StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
                    StatePtr->LastValidCounter = u1_ReceivedCounter;
                    /* Revise [SWS]E2E_P01STATUS_INTIAL to E2E_P01STATUS_INITIAL */
                    StatePtr->Status = E2E_P01STATUS_INITIAL;
                }
                else
                {
                    /* PRS_E2E_00076 */
                    /* Compute the delta, taking into account the overflow. */
                    if( u1_ReceivedCounter >= StatePtr->LastValidCounter )
                    {
                        u1_DeltaCounter = u1_ReceivedCounter - StatePtr->LastValidCounter;
                    }
                    else
                    {
                        u1_DeltaCounter = (E2E_U1_P01_COUNTER_NEGATIVE_TO_POSITIVE - (StatePtr->LastValidCounter - u1_ReceivedCounter)) + (uint8)E2E_DELTA_COUNTER_WRAP_AROUND;
                    }
                    /* The previous and the current data have correct CRC, verify the counter. */
                    if( u1_DeltaCounter == (uint8)E2E_DELTA_COUNTER_NUM_ZERO )
                    {
                        if( StatePtr->NoNewOrRepeatedDataCounter < E2E_U1_P01_COUNTER_MAX )
                        {
                            StatePtr->NoNewOrRepeatedDataCounter++;
                        }
                        StatePtr->Status = E2E_P01STATUS_REPEATED;
                    }
                    else if(u1_DeltaCounter > StatePtr->MaxDeltaCounter)
                    {
                        StatePtr->NoNewOrRepeatedDataCounter = E2E_U1_P01_CHECKNONEWORREPEATEDDATACOUNTER_INIT;
                        StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
                        if( StatePtr->SyncCounter > E2E_U1_SYNC_COUNTER_NUM_ZERO )
                        {
                            StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
                            StatePtr->LastValidCounter = u1_ReceivedCounter;
                        }
                        StatePtr->Status = E2E_P01STATUS_WRONGSEQUENCE;
                    }
                    else
                    {
                        StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
                        StatePtr->LastValidCounter = u1_ReceivedCounter;
                        StatePtr->LostData = u1_DeltaCounter - (uint8)E2E_DELTA_COUNTER_NUM_ONE;
                        if( StatePtr->NoNewOrRepeatedDataCounter > ConfigPtr->MaxNoNewOrRepeatedData )
                        {
                            StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
                            StatePtr->NoNewOrRepeatedDataCounter = E2E_U1_P01_CHECKNONEWORREPEATEDDATACOUNTER_INIT;
                            StatePtr->Status = E2E_P01STATUS_SYNC;
                        }
                        else
                        {
                            StatePtr->NoNewOrRepeatedDataCounter = E2E_U1_P01_CHECKNONEWORREPEATEDDATACOUNTER_INIT;
                            if( StatePtr->SyncCounter > E2E_U1_SYNC_COUNTER_NUM_ZERO )
                            {
                                StatePtr->SyncCounter--;
                                StatePtr->Status = E2E_P01STATUS_SYNC;
                            }
                            else
                            {
                                if( u1_DeltaCounter == (uint8)E2E_DELTA_COUNTER_NUM_ONE )
                                {
                                    StatePtr->Status = E2E_P01STATUS_OK;
                                }
                                else
                                {
                                    StatePtr->Status = E2E_P01STATUS_OKSOMELOST;
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            StatePtr->Status = E2E_P01STATUS_WRONGCRC;
        }
    }
    else
    {
        u1_Ret = E2E_E_INPUTERR_WRONG;
    }

    return u1_Ret;
}

#define E2E_STOP_SEC_CODE
#include <E2E_MemMap.h>
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2022/06/03                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
