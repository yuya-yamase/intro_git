/* Sys_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sys/HEADER                                                  */
/******************************************************************************/
#ifndef SYS_H
#define SYS_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SYS_COUNTER_ID  ((CounterType)0x00U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint8       CounterType;
typedef uint32      TickType;
typedef TickType*   TickRefType;

/* StatusType is defined in Std_Types.h */


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(uint8, SYS_CODE_SLOW) MaskInterruptAll (void);
FUNC(void, SYS_CODE_SLOW) UnMaskInterruptAll
(
    VAR(uint8, AUTOMATIC) MaskPattern
);
FUNC(StatusType, SYS_CODE_SLOW) GetCounterValue
(
    VAR(CounterType, AUTOMATIC) CounterID,
    VAR(TickRefType, AUTOMATIC) Value
);
FUNC(void, SYS_CODE_SLOW) Rpg_MemCopy
(
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestAddress,
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcAddress,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(void, SYS_CODE_SLOW) Rpg_MemSet
(
    P2VAR(uint8, AUTOMATIC, SYS_APPL_DATA) DestAddress,
    VAR(uint8, AUTOMATIC) Value,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(uint32, SYS_CODE_SLOW) Rpg_ByteCombine
(
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) SrcAddress,
    VAR(uint8, AUTOMATIC) Size
);
FUNC(U4, SYS_CODE_SLOW) DisableInterrupt (void);
FUNC(void, SYS_CODE_SLOW) EnableInterrupt
(
    VAR(U4, AUTOMATIC) IntStatus
);
FUNC(void, SYS_CODE_SLOW) MemBarrier32
(
    P2CONST(uint32, AUTOMATIC, SYS_APPL_CONST) ReadAddress
);
FUNC(void, SYS_CODE_SLOW) MemBarrier16
(
    P2CONST(uint16, AUTOMATIC, SYS_APPL_CONST) ReadAddress
);
FUNC(void, SYS_CODE_SLOW) MemBarrier8
(
    P2CONST(uint8, AUTOMATIC, SYS_APPL_CONST) ReadAddress
);
FUNC(uint32, SYS_CODE_SLOW) Rpg_Div_u32
(
    VAR(uint32, AUTOMATIC) Dividend,
    VAR(uint32, AUTOMATIC) Divisor
);
FUNC(uint32, SYS_CODE_SLOW) Rpg_Mod_u32
(
    VAR(uint32, AUTOMATIC) Dividend,
    VAR(uint32, AUTOMATIC) Divisor
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* SYS_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

