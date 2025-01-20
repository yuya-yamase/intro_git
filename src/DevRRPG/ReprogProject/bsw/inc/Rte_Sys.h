/* Rte_Sys_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Rte/Sys/HEADER                                              */
/******************************************************************************/
#ifndef RTE_SYS_H
#define RTE_SYS_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Sys.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RTE_SYS_COUNTER_ID      (SYS_COUNTER_ID)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef CounterType     Rte_CounterType;
typedef TickRefType     Rte_TickRefType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(uint8, RTE_CODE_SLOW) Rte_MaskInterruptAll (void);
FUNC(void, RTE_CODE_SLOW) Rte_UnMaskInterruptAll
(
    VAR(uint8, AUTOMATIC) MaskPattern
);
FUNC(StatusType, RTE_CODE_SLOW) Rte_GetCounterValue
(
    VAR(Rte_CounterType, AUTOMATIC) CounterID,
    VAR(Rte_TickRefType, AUTOMATIC) Value
);
FUNC(void, RTE_CODE_SLOW) Rte_Rpg_MemCopy
(
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestAddress,
    P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) SrcAddress,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(void, RTE_CODE_SLOW) Rte_Rpg_MemSet
(
    P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DestAddress,
    VAR(uint8, AUTOMATIC) Value,
    VAR(uint32, AUTOMATIC) Size
);
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_ByteCombine
(
    P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) SrcAddress,
    VAR(uint8, AUTOMATIC) Size
);
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_Div_u32
(
    VAR(uint32, AUTOMATIC) Dividend,
    VAR(uint32, AUTOMATIC) Divisor
);
FUNC(uint32, RTE_CODE_SLOW) Rte_Rpg_Mod_u32
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


#endif /* RTE_SYS_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

