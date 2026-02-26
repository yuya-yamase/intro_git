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

extern ISR(eMCOS_ISR_INTOSTM5TINT);
extern ISR(eMCOS_ISR_INTTAUD0I14);
extern ISR(eMCOS_ISR_INTRCAN3REC);
extern ISR(eMCOS_ISR_INTRCAN3TRX);
extern ISR(eMCOS_ISR_INTRCAN5REC);
extern ISR(eMCOS_ISR_INTRCAN5TRX);
extern ISR(eMCOS_ISR_INTRCAN7REC);
extern ISR(eMCOS_ISR_INTRCAN7TRX);
extern ISR(eMCOS_ISR_INTRCAN11REC);
extern ISR(eMCOS_ISR_INTRCAN11TRX);

#endif /* OS_CFG_EXTERNAL_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/
