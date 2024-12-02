/****************************************************************************
 * Protected                                                                *
 * Copyright AUBASS CO., LTD.                                               *
 ****************************************************************************

    Copyright (C) 2022 eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/****************************************************************************
 [ Os_Cfg_internal.h ] - OS module's configuration data file
****************************************************************************/

#ifndef OS_CFG_INTERNAL_H
#define OS_CFG_INTERNAL_H

/*
 * Function Prototypes
 */
#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
extern TASK(Ecu_IdleTask);
extern TASK(Ecu_InitTask);
extern TASK(Task_MM_High);
extern TASK(Task_MM_Low);
extern TASK(Task_MM_Medium);
#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"


#define OS_START_SEC_CODE_GLOBAL
#include "Os_MemMap.h"
extern ISR(INTSDMAC0CH5_ISR);
extern ISR(INTOSTM3_ISR);
extern ISR(INTP4_ISR);
extern ISR(OS_SYSTEM_COUNTER_ISR0);
#define OS_STOP_SEC_CODE_GLOBAL
#include "Os_MemMap.h"



/*
 * Category 2 ISR control blocks
 */


#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

extern ar_isrcb_t ar_isrcb_INTSDMAC0CH5_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

extern ar_isrcb_t ar_isrcb_INTOSTM3_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

extern ar_isrcb_t ar_isrcb_INTP4_ISR;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"


#define OS_START_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"

extern ar_isrcb_t ar_isrcb_OS_SYSTEM_COUNTER_ISR0;

#define OS_STOP_SEC_VAR_LOCAL0_NO_INIT_32
#include "Os_MemMap.h"




#endif /* OS_CFG_INTERNAL_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
