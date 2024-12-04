/* Mscd_Types.h v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/TYPES/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_TYPES_H
#define MSCD_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Rte_Mscd_Type.h>
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MSCD_MAINFUNCTION_PROCESSED            (0x00U)
#define MSCD_MAINFUNCTION_NOT_PROCESSED        (0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


typedef uint8 Mscd_Dfai_StatusType;
typedef uint8 Mscd_Dfai_ReturnType;

/* FreeSpace (return) Type */
typedef uint8 Mscd_FreeSpaceReturnType;

/* FreeSpace (result) Type */
typedef uint8 Mscd_FreeSpaceResultType;

/* FreeSpace (information) Type */
typedef struct {
    Mscd_FreeSpaceResultType Result;
    uint16                   RcrdNum;
    uint32                   DataAreaByte;
} Mscd_FreeSpaceInfoType;

#endif /* MSCD_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/31                                              */
/*  2-0-0          :2021/03/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
