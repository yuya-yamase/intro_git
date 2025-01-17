/* Port_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Port/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Port.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define PORT_REG_BASE               (0xFFD90000UL)
#define PORT_REG_PCR(n, m)          (*(volatile U4 *)(PORT_REG_BASE + 0x2000UL + (0x40UL * (n)) + (0x4UL * (m))))
#define PORT_REG_PKCPROT            (*(volatile U4 *)(PORT_REG_BASE + 0x2F40UL))
#define PORT_REG_PWE                (*(volatile U4 *)(PORT_REG_BASE + 0x2F44UL))

#define PORT_PCR_DEFAULT_VALUE      (0x5B5CE000UL)      /* Default Value */
#define PORT_PCR_SET_PM             (0x00000010UL)      /* Input mode */
#define PORT_PCR_CLEAR_PM           (0xFFFFFFEFUL)      /* Input mode */
#define PORT_PCR_SET_PMC            (0x00000040UL)      /* Alternative mode */
#define PORT_PCR_ALT_OUT_SETTING    (0xFFFCFFFFUL)      /* ALT Output setting */
#define PORT_PCR_ALT_IN(x)          (0x00000050UL + ((x) - 1UL))
#define PORT_PCR_ALT_OUT(x)         (0x00000040UL + ((x) - 1UL))

#define PORT_PKCPROT_ENABLE         (0xA5A5A501UL)
#define PORT_PKCPROT_DISABLE        (0xA5A5A500UL)
#define PORT_PWE_ENABLE_P0_P6(n)    (1UL << ((n) + 1UL))
#define PORT_PWE_ENABLE_P8_P12(n)   (1UL << ((n)      ))
#define PORT_PWE_DISABLE            (0x00000000UL)

#define PORT_ALT_IN                 ((U1)0U)
#define PORT_ALT_OUT                ((U1)1U)

#define PORT_NO_P6                  ((U1)6U)

#define PORT_SETTABLE_NUM           (sizeof(Port_SetTable) / sizeof(Port_SetTable[0]))
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    U1 Pn;      /* Pn_m, ALT_IN/OUT, ALTx */
    U1 Pm;
    U1 AltInOut;
    U1 Altx;
} Port_SetTableType;

typedef struct {
    U4 Num;
    P2CONST(Port_SetTableType, TYPEDEF, PORT_APPL_CONST) TablePtr;
} Port_SetInfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define PORT_START_SEC_VAR
#include <Port_MemMap.h>

#define PORT_STOP_SEC_VAR
#include <Port_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define PORT_START_SEC_CST
#include <Port_MemMap.h>

/*===== Sample ===============================================================*/
static CONST(Port_SetTableType, PORT_CONST) Port_SetTable[] = {
     /* Pn_m,    ALT_IN/OUT,    ALTx */
     {  4U, 12U, PORT_ALT_IN,   2U }    /* CAN5RX(P04_12, ALT_IN 2) */
    ,{  4U, 11U, PORT_ALT_OUT,  2U }    /* CAN5TX(P04_11, ALT_OUT2) */
};

static CONST(volatile Port_SetInfoType, PORT_CONST) Port_SetInfo = {
    PORT_SETTABLE_NUM,
    &Port_SetTable[0]
};
/*===== Sample ===============================================================*/

#define PORT_STOP_SEC_CST
#include <Port_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include <Port_MemMap.h>

/******************************************************************************/
/* Function Name | Port_Init                                                  */
/* Description   | Initializes Port                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Config : Dummy argument                               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PORT_CODE_SLOW) Port_Init
(
    P2CONST(void, AUTOMATIC, PORT_APPL_CONST) Config
)
{
/*===== Sample ===============================================================*/
    VAR(U4, AUTOMATIC) i;
    VAR(U4, AUTOMATIC) Pn;
    VAR(U4, AUTOMATIC) Pm;
    VAR(U4, AUTOMATIC) Altx;

    for( i = 0UL; i < Port_SetInfo.Num; i++ )
    {
        Pn   = (U4)Port_SetInfo.TablePtr[i].Pn;
        Pm   = (U4)Port_SetInfo.TablePtr[i].Pm;
        Altx = (U4)Port_SetInfo.TablePtr[i].Altx;

        PORT_REG_PKCPROT     = PORT_PKCPROT_ENABLE;

        if( Pn <= PORT_NO_P6 )
        {
            PORT_REG_PWE     = PORT_PWE_ENABLE_P0_P6(Pn);
        }
        else
        {
            PORT_REG_PWE     = PORT_PWE_ENABLE_P8_P12(Pn);
        }

        PORT_REG_PCR(Pn, Pm) = (PORT_REG_PCR(Pn, Pm) & PORT_PCR_DEFAULT_VALUE) | PORT_PCR_SET_PM;

        if( Port_SetInfo.TablePtr[i].AltInOut == PORT_ALT_IN )
        {
            PORT_REG_PCR(Pn, Pm) |= PORT_PCR_ALT_IN(Altx);
            PORT_REG_PCR(Pn, Pm) |= PORT_PCR_SET_PMC;
        }
        else
        {
            PORT_REG_PCR(Pn, Pm) |= PORT_PCR_ALT_OUT(Altx);
            PORT_REG_PCR(Pn, Pm) |= PORT_PCR_SET_PMC;
            PORT_REG_PCR(Pn, Pm) &= PORT_PCR_CLEAR_PM;
            PORT_REG_PCR(Pn, Pm) &= PORT_PCR_ALT_OUT_SETTING;
        }

        PORT_REG_PWE     = PORT_PWE_DISABLE;
        PORT_REG_PKCPROT = PORT_PKCPROT_DISABLE;
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | Port_DeInit                                                */
/* Description   | Deinitializes Port                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, PORT_CODE_SLOW) Port_DeInit (void)
{

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define PORT_STOP_SEC_CODE
#include <Port_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

