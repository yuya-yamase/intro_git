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
 [ Os_Cfg_base.h ] - OS module's configuration header file
****************************************************************************/


#ifndef OS_CFG_BASE_H
#define OS_CFG_BASE_H

/*
 * Scalability Class
 */
#define AR_OS_USE_SCALABILITYCLASS1         (1U)
#define AR_OS_USE_SCALABILITYCLASS          AR_OS_USE_SCALABILITYCLASS1
#define AR_OS_USE_SCALABILITYCLASS_3_OR_4   (STD_OFF)

/*
 * Hook Switch
 */
#define AR_OS_USE_ERRORHOOK             (STD_ON)
#define AR_OS_USE_SYSTEM_ERRORHOOK      (STD_ON)
#define AR_OS_USE_POSTTASKHOOK          (STD_OFF)
#define AR_OS_USE_PRETASKHOOK           (STD_OFF)
#define AR_OS_USE_PROTECTIONHOOK        (STD_ON)
#define AR_OS_USE_STARTUPHOOK           (STD_OFF)
#define AR_OS_USE_SYSTEM_STARTUPHOOK    (STD_OFF)
#define AR_OS_USE_SHUTDOWNHOOK          (STD_ON)
#define AR_OS_USE_SYSTEM_SHUTDOWNHOOK   (STD_ON)

/*
 * OS Switch
 */
#define AR_OS_USE_MULTICORE             (STD_OFF)
#define AR_OS_USE_STACKMONITORING       (STD_OFF)
#define AR_OS_USE_EXTENDEDSTATUS        (STD_ON)
#define AR_OS_USE_IOC_DIRECT_ACCESS     (STD_ON)

#endif /* OS_CFG_BASE_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-2                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
