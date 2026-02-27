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
 [ hal_v850_cfg.h ] - OS module's configuration file
****************************************************************************/

#ifndef HAL_V850_CFG_H
#define HAL_V850_CFG_H

/* size of interrupt controllers */
#define HAL_V850_INTERRUPT_CONTROLLERS_SIZE  (2U)

/* INTC1 : offset of logical interrupt number */
#define HAL_V850_INTC1_OFFSET (0U)

/* INTC1 : size of interrupt numbers which belongs to this */
#define HAL_V850_INTC1_SIZE   (32U)

/* INTC2 : offset of logical interrupt number */
#define HAL_V850_INTC2_OFFSET (0U)

/* INTC2 : size of interrupt numbers which belongs to this */
#define HAL_V850_INTC2_SIZE   (736U)


/* V850 implementation options : Number of priority bits */
#define HAL_V850_PRIORITY_MASK ( (1UL << 6U) - 1UL)


/* V850 implementation options : Number of MPU regions */
#define HAL_V850_NUMBERS_OF_MPU_REGION (32U)


/* V850 implementation options : Number of MPU regions (USER AVAILABLE) */
#define HAL_V850_NUMBERS_OF_MPU_REGION_USER_AVAILABLE (29U)


/* V850 implementation name : rh850g4mh */
#define HAL_V850_IMPLEMENTATION_TARGET_RH850G4MH


/*
 * Set controlled priority
 */
#define HAL_V850_PRIORITY_MAX      (63U)

#define HAL_V850_CPULOCK_MASK      (0x39U)

#endif /* #ifndef HAL_V850_CFG_H */
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
