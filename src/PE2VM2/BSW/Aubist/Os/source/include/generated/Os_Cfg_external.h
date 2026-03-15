/****************************************************************************
 * Protected                                                                *
 * Copyright AUBASS CO., LTD.                                               *
 ****************************************************************************

    Copyright (C) 2024 eSOL Co.,Ltd. Tokyo, Japan

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
 [ Os_Cfg_external.h ] - OS module's configuration header file
****************************************************************************/

#ifndef OS_CFG_EXTERNAL_H
#define OS_CFG_EXTERNAL_H

/*
 * Function Prototypes
 */
extern TASK(eMCOS_TASK_High);
extern TASK(eMCOS_TASK_Idle);
extern TASK(eMCOS_TASK_Medium);

extern ISR(eMCOS_ISR_INTOSTM1TINT);
extern ISR(eMCOS_ISR_INTP38);
extern ISR(eMCOS_ISR_INTOSTM8TINT);
extern ISR(eMCOS_ISR_INTRIIC0EE);
extern ISR(eMCOS_ISR_INTRIIC0RI);
extern ISR(eMCOS_ISR_INTRIIC0TI);
extern ISR(eMCOS_ISR_INTRIIC0TEI);
extern ISR(eMCOS_ISR_INTRIIC1EE);
extern ISR(eMCOS_ISR_INTRIIC1RI);
extern ISR(eMCOS_ISR_INTRIIC1TI);
extern ISR(eMCOS_ISR_INTRIIC1TEI);

#endif /* OS_CFG_EXTERNAL_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/
