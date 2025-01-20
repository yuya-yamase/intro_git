/* Sec_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/CODE                                                    */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Sec_Local.h"

/*===== Sample ===============================================================*/
#include "Sec_Usr_GenSeedCallback.h"
#include <Csm.h>
#include <Rte.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define SEC_USR_STAT_IDLE                   ((uint8)0x00U)
#define SEC_USR_STAT_BUSY                   ((uint8)0x01U)
#define SEC_USR_STAT_RANDOMSEED_FIN         ((uint8)0x02U)
#define SEC_USR_STAT_RANDOMGEN_FIN          ((uint8)0x03U)
#define SEC_USR_STAT_FAILED                 ((uint8)0xFFU)

#define SEC_USR_SEED_SIZE                   ((uint8)16U)
#define SEC_USR_RANDOMVALUE_SIZE            (SEC_USR_SEED_SIZE)
#define SEC_USR_RANDOMVALUE_SET_LOOP        ((uint8)(SEC_USR_RANDOMVALUE_SIZE >> 1U))

#define SEC_USR_CALC_8BITSHIFT              ((uint16)8U)

#define SEC_USR_RANDOMSEED_KEYID            ((uint32)0x00000004UL)      /* Must be equivalent to Csm config */
#define SEC_USR_RANDOMSEED_JOBID            ((uint32)0x00000003UL)      /* Must be equivalent to Csm config */
#define SEC_USR_RANDOMGEN_JOBID             ((uint32)0x00000004UL)      /* Must be equivalent to Csm config */
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    uint32 SeedSize;
    P2VAR(uint8, SEC_VAR_CLEARED, SEC_APPL_DATA) SeedPtr;
    uint8 PreSeed[SEC_USR_SEED_SIZE];
} Sec_Usr_SeedInfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_StartRandomSeed (void);
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_StartRandomGenerate (void);
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_VAR
#include <Sec_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint8, SEC_VAR_CLEARED) Sec_Usr_JobStatus;
static VAR(Sec_Usr_SeedInfoType, SEC_VAR_CLEARED) Sec_Usr_SeedInfo;
/*===== Sample ===============================================================*/

#define SEC_STOP_SEC_VAR
#include <Sec_MemMap.h>

#define SEC_START_SEC_VAR_RANDOMSEED
#include <Sec_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint8, SEC_VAR_CLEARED) Sec_Usr_RandomSeed[SEC_USR_RANDOMVALUE_SIZE];
/*===== Sample ===============================================================*/

#define SEC_STOP_SEC_VAR_RANDOMSEED
#include <Sec_MemMap.h>

#define SEC_START_SEC_VAR_RANDOM_SIZE
#include <Sec_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(uint32, SEC_VAR_CLEARED) Sec_Usr_RandomSize;
/*===== Sample ===============================================================*/

#define SEC_STOP_SEC_VAR_RANDOM_SIZE
#include <Sec_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_CST
#include <Sec_MemMap.h>

#define SEC_STOP_SEC_CST
#include <Sec_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SEC_START_SEC_CODE
#include <Sec_MemMap.h>

/******************************************************************************/
/* Function Name | Sec_Usr_Init                                               */
/* Description   | Initializes                                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_FAST) Sec_Usr_Init (void)
{
/*===== Sample ===============================================================*/
    Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;

    Sec_Usr_SeedInfo.SeedSize = 0UL;
    Sec_Usr_SeedInfo.SeedPtr = NULL_PTR;
    Rte_Rpg_MemSet(Sec_Usr_SeedInfo.PreSeed, 0U, sizeof(Sec_Usr_SeedInfo.PreSeed));

    Rte_Rpg_MemSet(Sec_Usr_RandomSeed, 0U, sizeof(Sec_Usr_RandomSeed));

    Sec_Usr_RandomSize = 0UL;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | Sec_Usr_DeInit                                             */
/* Description   | Deinitializes                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_FAST) Sec_Usr_DeInit (void)
{
/*===== Sample ===============================================================*/
    Sec_Usr_RandomSize = 0UL;

    Rte_Rpg_MemSet(Sec_Usr_RandomSeed, 0U, sizeof(Sec_Usr_RandomSeed));

    Rte_Rpg_MemSet(Sec_Usr_SeedInfo.PreSeed, 0U, sizeof(Sec_Usr_SeedInfo.PreSeed));
    Sec_Usr_SeedInfo.SeedPtr = NULL_PTR;
    Sec_Usr_SeedInfo.SeedSize = 0UL;

    Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | Sec_Usr_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_FAST) Sec_Usr_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | Sec_Usr_MainFunction                                       */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_FAST) Sec_Usr_MainFunction (void)
{
    return;
}

/******************************************************************************/
/* Function Name | Sec_Usr_GenSeedValue                                       */
/* Description   | Generates seed value                                       */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Op       : Operation                                 */
/*               |  SEC_GENSEED_START                                         */
/*               |  SEC_GENSEED_GET                                           */
/*               |  SEC_GENSEED_STOP                                          */
/*               | [OUT] Seed     : Seed value                                */
/*               | [IN]  SeedSize : Seed size                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  SEC_E_PENDING                                             */
/* Notes         | - This function is called in the order of                  */
/*               |   SEC_GENSEED_START, SEC_GENSEED_GET, SEC_GENSEED_STOP.    */
/*               | - When call with SEC_GENSEED_START and SEC_GENSEED_STOP,   */
/*               |   'Seed'=NULL_PTR and 'SeedSize'=0.                        */
/*               | - If the process is not completed, return SEC_E_PENDING.   */
/*               |   It will be called again with the same 'Op' after a       */
/*               |   certain period of time.                                  */
/*               | - This Seed value is used in SID 0x27. Please generate it  */
/*               |   according to the OEM specifications.                     */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_GenSeedValue
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(uint8, AUTOMATIC, SEC_APPL_DATA) Seed,
    VAR(uint8, AUTOMATIC) SeedSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( (Op == SEC_GENSEED_START) && (Seed == NULL_PTR) && (SeedSize == (uint8)0U) )
    {
        if( Sec_Usr_JobStatus == SEC_USR_STAT_IDLE )
        {
            FuncRet = Sec_Usr_StartRandomSeed();
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                /* Wait callback */
                Sec_Usr_JobStatus = SEC_USR_STAT_BUSY;
                Ret = SEC_E_PENDING;
            }
            else
            {
                Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
            }
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_BUSY )
        {
            Ret = SEC_E_PENDING;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_RANDOMSEED_FIN )
        {
            /* Callback OK */
            Ret = E_OK;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_FAILED )
        {
            /* Callback NG */
            Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
        }
        else
        {
            /* No process */
        }
    }
    else if( (Op == SEC_GENSEED_GET) && (Seed != NULL_PTR) && (SeedSize == SEC_USR_SEED_SIZE) )
    {
        if( Sec_Usr_JobStatus == SEC_USR_STAT_RANDOMSEED_FIN )
        {
            Sec_Usr_SeedInfo.SeedSize = (uint32)SeedSize;
            Sec_Usr_SeedInfo.SeedPtr = Seed;

            FuncRet = Sec_Usr_StartRandomGenerate();
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                /* Wait callback */
                Sec_Usr_JobStatus = SEC_USR_STAT_BUSY;
                Ret = SEC_E_PENDING;
            }
            else
            {
                Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
            }
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_BUSY )
        {
            Ret = SEC_E_PENDING;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_RANDOMGEN_FIN )
        {
            /* Callback OK */
            Ret = E_OK;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_FAILED )
        {
            /* Callback NG */
            Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
        }
        else
        {
            /* No process */
        }
    }
    else if( (Op == SEC_GENSEED_STOP) && (Seed == NULL_PTR) && (SeedSize == (uint8)0U) )
    {
        if( Sec_Usr_JobStatus == SEC_USR_STAT_RANDOMGEN_FIN )
        {
            Ret = E_OK;
            Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_BUSY )
        {
            Ret = SEC_E_PENDING;
        }
        else if( Sec_Usr_JobStatus == SEC_USR_STAT_FAILED )
        {
            Sec_Usr_JobStatus = SEC_USR_STAT_IDLE;
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

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | Sec_Usr_Get_ToolAuthKey                                    */
/* Description   | Get ToolAuthKey value                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN]  RomPtr  : Pointer to Key data on ROM                 */
/*               | [IN]  KeySize : Key data size                              */
/*               | [OUT] KeyPtr  : Pointer to Key data                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_FAST) Sec_Usr_Get_ToolAuthKey
(
    P2CONST(uint8, AUTOMATIC, SEC_APPL_CONST) RomPtr,
    VAR(uint32, AUTOMATIC) KeySize,
    P2VAR(uint8, AUTOMATIC, SEC_APPL_DATA) KeyPtr
)
{
/*===== Sample ===============================================================*/
    /* The value set in the configuration(= RomPtr) is ToolAuthKey value. */
    Rte_Rpg_MemCopy(KeyPtr, RomPtr, KeySize);
/*===== Sample ===============================================================*/

    return;
}

/*===== Sample ===============================================================*/
/******************************************************************************/
/* Function Name | Sec_Usr_CallbackRandomSeed                                 */
/* Description   | Callback for Csm_JobRandomSeed()                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId  : JobId                                        */
/*               | [IN] Result : Result of Csm_JobRandomSeed()                */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_Usr_CallbackRandomSeed
(
    VAR(uint32, AUTOMATIC) JobId,
    VAR(Crypto_ResultType, AUTOMATIC) Result
)
{
    if( Result == (Crypto_ResultType)E_OK )
    {
        Sec_Usr_JobStatus = SEC_USR_STAT_RANDOMSEED_FIN;
    }
    else
    {
        Sec_Usr_JobStatus = SEC_USR_STAT_FAILED;
    }

    /* Clear */
    Rte_Rpg_MemSet(Sec_Usr_RandomSeed, 0U, sizeof(Sec_Usr_RandomSeed));

    return;
}

/******************************************************************************/
/* Function Name | Sec_Usr_CallbackRandomGenerate                             */
/* Description   | Callback for Csm_RandomGenerate()                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId  : JobId                                        */
/*               | [IN] Result : Result of Csm_RandomGenerate()               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_Usr_CallbackRandomGenerate
(
    VAR(uint32, AUTOMATIC) JobId,
    VAR(Crypto_ResultType, AUTOMATIC) Result
)
{
    VAR(uint8, AUTOMATIC) SameValueFlag;
    VAR(uint32, AUTOMATIC) i;

    if( (Result == (Crypto_ResultType)E_OK) &&
        (Sec_Usr_RandomSize == Sec_Usr_SeedInfo.SeedSize) )
    {
        SameValueFlag = STD_ON;
        for( i = 0UL; i < Sec_Usr_SeedInfo.SeedSize; i++ )
        {
            if( Sec_Usr_SeedInfo.SeedPtr[i] != Sec_Usr_SeedInfo.PreSeed[i] )
            {
                SameValueFlag = STD_OFF;
                break;
            }
        }

        if( SameValueFlag == (uint8)STD_OFF )
        {
            Rte_Rpg_MemCopy(Sec_Usr_SeedInfo.PreSeed, Sec_Usr_SeedInfo.SeedPtr, sizeof(Sec_Usr_SeedInfo.PreSeed));

            Sec_Usr_JobStatus = SEC_USR_STAT_RANDOMGEN_FIN;
            Sec_Usr_SeedInfo.SeedPtr = NULL_PTR;
            Sec_Usr_SeedInfo.SeedSize = 0UL;
            Sec_Usr_RandomSize = 0UL;
        }
        else
        {
            /* Retry because seed value generated this time and last time are the same. */
            Sec_Usr_JobStatus = SEC_USR_STAT_RANDOMSEED_FIN;
        }
    }
    else
    {
        Sec_Usr_JobStatus = SEC_USR_STAT_FAILED;
    }

    return;
}
/*===== Sample ===============================================================*/


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/*===== Sample ===============================================================*/
/******************************************************************************/
/* Function Name | Sec_Usr_StartRandomSeed                                    */
/* Description   | Execute Csm_JobRandomSeed()                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_StartRandomSeed (void)
{
    VAR(uint8, AUTOMATIC) RndIndex;
    VAR(Std_ReturnType, AUTOMATIC) CsmRet;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint16, AUTOMATIC) TempValue;
    VAR(uint32, AUTOMATIC) i;
    VAR(uint32, AUTOMATIC) CounterValue;

    Result = E_NOT_OK;
    RndIndex = 0U;
    CounterValue = 0UL;

    /* Generating random seed via free running timer value. */
    for( i = 0U; i < SEC_USR_RANDOMVALUE_SET_LOOP; i++ )
    {
        /* As the first argument is correct, the return value of Rte_GetCounterValue() is always E_OK. */
        /* Therefore, the return value's type is converted void type. */
        (void)Rte_GetCounterValue(RTE_SYS_COUNTER_ID, (Rte_TickRefType)&CounterValue);

        TempValue = (uint16)CounterValue;

        Sec_Usr_RandomSeed[RndIndex] = (uint8)(TempValue >> SEC_USR_CALC_8BITSHIFT);
        RndIndex++;
        Sec_Usr_RandomSeed[RndIndex] = (uint8)TempValue;
        RndIndex++;
    }

    /* Set random seed. */
    /* The pointer arguments to Csm_JobRandomSeed() are arranged as follows. */
    /*  - seedPtr(Sec_Usr_RandomSeed) : ".B_RAM_SEC_RANDOMSEED_SHARED"       */
    CsmRet = Csm_JobRandomSeed(SEC_USR_RANDOMSEED_JOBID,
                                SEC_USR_RANDOMSEED_KEYID,
                                Sec_Usr_RandomSeed,
                                sizeof(Sec_Usr_RandomSeed));
    if( CsmRet == (Std_ReturnType)E_OK )
    {
        Result = E_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | Sec_Usr_StartRandomGenerate                                */
/* Description   | Execute Csm_RandomGenerate                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_Usr_StartRandomGenerate (void)
{
    VAR(Std_ReturnType, AUTOMATIC) CsmRet;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    Sec_Usr_RandomSize = Sec_Usr_SeedInfo.SeedSize;

    /* Generate random seed */
    /* The pointer arguments to Csm_RandomGenerate() are arranged as follows.   */
    /*  - resultPtr(Sec_Usr_SeedInfo.SeedPtr)  : ".B_RAM_DIAGSRV_SEED_SHARED"   */
    /*  - resultLengthPtr(&Sec_Usr_RandomSize) : ".B_RAM_SEC_RANDOMSIZE_SHARED" */
    CsmRet = Csm_RandomGenerate(SEC_USR_RANDOMGEN_JOBID,
                                Sec_Usr_SeedInfo.SeedPtr,
                                &Sec_Usr_RandomSize);
    if( CsmRet == (Std_ReturnType)E_OK )
    {
        Result = E_OK;
    }

    return Result;
}
/*===== Sample ===============================================================*/


#define SEC_STOP_SEC_CODE
#include <Sec_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

