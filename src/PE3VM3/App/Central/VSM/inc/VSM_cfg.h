/****************************************************************************/
/*                                                                          */
/*    FILE NAME     :    VSM_cfg.h                                          */
/*    FUNCTION      :    CPU SleepWakeup                                    */
/*                       Data Select Layer                                  */
/*                                                                          */
/*    DEPARTMENT    :    DNJP                                               */
/*    AUTHOR        :                                                       */
/*                                                                          */
/****************************************************************************/
#ifndef VSM_CFG_H
#define VSM_CFG_H
/****************************************************************************/
#include "Std_Types.h"

/****************************************************************/
/* Typedef                                                      */
/****************************************************************/
typedef struct type_bitdata {
    U1  bit0:1;
    U1  bit1:1;
    U1  bit2:1;
    U1  bit3:1;
    U1  bit4:1;
    U1  bit5:1;
    U1  bit6:1;
    U1  bit7:1;
} TYPE_BITDATA;

typedef union type_u4data {
    U4      u4data;
    struct {
        U2  u2_0;
        U2  u2_1;
    } u2data;
    struct {
        U1  u1_0;
        U1  u1_1;
        U1  u1_2;
        U1  u1_3;
    } u1data;
    struct {
        TYPE_BITDATA    b1_0;
        TYPE_BITDATA    b1_1;
        TYPE_BITDATA    b1_2;
        TYPE_BITDATA    b1_3;
    } bitdata;
} TYPE_U4DATA;

/****************************************************************/
/* define                                                       */
/****************************************************************/
#define TYPE_SET            (1U)
#define TYPE_CLR            (0U)
/****************************************************************/
#endif/*VSM_CFG_H*/
