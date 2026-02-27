/**
 * @file
 ***********************************************************************************************
 * @brief File generated from @ref VMS resource configuration step.
 *        Strictly use the macros from this file as the macro values shall change, when new
 *        devices are added or some are removed.
 *
 ***********************************************************************************************

 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.

 ***********************************************************************************************/

#ifndef ECY_HSM_VMS_ARCH_CFG_H
#define ECY_HSM_VMS_ARCH_CFG_H

/*
 * Endianness macros used for the VMS architecture endianess definition below.
 * Is aligned with CPU_BYTE_ORDER from Platform_Types.h. But since these header is not included in our deliveries,
 * we generate the endianness information here as well.
 */
#define ECY_HSM_BIG_ENDIAN    0     /* Big endian byte ordering       */
#define ECY_HSM_LITTLE_ENDIAN 1     /* Little endian byte ordering    */


/* List of supported target families */
#define ECY_HSM_VMS_ARCH_FAMILY_CYPRESS                        1
#define ECY_HSM_VMS_ARCH_FAMILY_IFX                            2
#define ECY_HSM_VMS_ARCH_FAMILY_PC                             3
#define ECY_HSM_VMS_ARCH_FAMILY_POWER                          4
#define ECY_HSM_VMS_ARCH_FAMILY_RH850                          5
#define ECY_HSM_VMS_ARCH_FAMILY_STSR6                          6

/* List of supported HSM target types
 * There could be cases where the host core properties (memory maps) are different
 * but the HSM core architecture is common
 */
#define ECY_HSM_VMS_ARCH_GROUP_CYPRESS_TRAVEO2                 7
#define ECY_HSM_VMS_ARCH_GROUP_IFX_TC2XX                       8
#define ECY_HSM_VMS_ARCH_GROUP_IFX_TC3XX                       9
#define ECY_HSM_VMS_ARCH_GROUP_PC_PCX                         10
#define ECY_HSM_VMS_ARCH_GROUP_POWER_SPC                      11
#define ECY_HSM_VMS_ARCH_GROUP_POWER_MPC                      12
#define ECY_HSM_VMS_ARCH_GROUP_RH850_V1                       13
#define ECY_HSM_VMS_ARCH_GROUP_RH850_V2                       14
#define ECY_HSM_VMS_ARCH_GROUP_RH850_V3                       15
#define ECY_HSM_VMS_ARCH_GROUP_RH850_V4                       16
#define ECY_HSM_VMS_ARCH_GROUP_RH850_V5                       17
#define ECY_HSM_VMS_ARCH_GROUP_STSR6_COMMON                   18

/* List of supported HSM target core types. This defines the different HSM core architectures. */
#define ECY_HSM_VMS_ARCH_HSM_TYPE_CYPRESS_M0                  20
#define ECY_HSM_VMS_ARCH_HSM_TYPE_IFX_TC2XX                   23
#define ECY_HSM_VMS_ARCH_HSM_TYPE_IFX_TC3XX                   26
#define ECY_HSM_VMS_ARCH_HSM_TYPE_PC_PC                       29
#define ECY_HSM_VMS_ARCH_HSM_TYPE_POWER_PPC                   31
#define ECY_HSM_VMS_ARCH_HSM_TYPE_RH850_ICUMC                 37
#define ECY_HSM_VMS_ARCH_HSM_TYPE_RH850_ICUMD                 41
#define ECY_HSM_VMS_ARCH_HSM_TYPE_RH850_ICUMH                 46
#define ECY_HSM_VMS_ARCH_HSM_TYPE_RH850_ICUMHB                53
#define ECY_HSM_VMS_ARCH_HSM_TYPE_STSR6_COMMON                58

/* List of supported targets */
#define ECY_HSM_VMS_ARCH_TARGET_CYPRESS_TRAVEO2_B9            19
#define ECY_HSM_VMS_ARCH_TARGET_CYPRESS_TRAVEO2_BL            21
#define ECY_HSM_VMS_ARCH_TARGET_IFX_TC2XX_TC23X               22
#define ECY_HSM_VMS_ARCH_TARGET_IFX_TC2XX_TC2HX               24
#define ECY_HSM_VMS_ARCH_TARGET_IFX_TC3XX_TC3LX               25
#define ECY_HSM_VMS_ARCH_TARGET_IFX_TC3XX_TC3HX               27
#define ECY_HSM_VMS_ARCH_TARGET_PC_PCX_PCX32                  28
#define ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58NN84           30
#define ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58EC84           32
#define ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58EG84           33
#define ECY_HSM_VMS_ARCH_TARGET_POWER_SPC_SPC58NH9X           34
#define ECY_HSM_VMS_ARCH_TARGET_POWER_MPC_MPC5748X            35
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V1_D3                   36
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V2_D4                   38
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V2_D5                   39
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S4                   40
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S2                   42
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V3_E2G                  43
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V3_E2M                  44
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_D6                   45
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_D6_DM                47
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_D7                   48
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_D7_DM                49
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_U2A6                 50
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V4_U2A6_DM              51
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V5_U2B6                 52
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V5_U2B6_DM              54
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V5_U2B10                55
#define ECY_HSM_VMS_ARCH_TARGET_RH850_V5_U2B10_DM             56
#define ECY_HSM_VMS_ARCH_TARGET_STSR6_COMMON_P7               57
#define ECY_HSM_VMS_ARCH_TARGET_STSR6_COMMON_P6               59
#define ECY_HSM_VMS_ARCH_TARGET_STSR6_COMMON_P5               60
#define ECY_HSM_VMS_ARCH_TARGET_STSR6_COMMON_P3               61
#define ECY_HSM_VMS_ARCH_TARGET_STSR6_COMMON_P2               62

#define ECY_HSM_VMS_ARCH_FAMILY                               ECY_HSM_VMS_ARCH_FAMILY_RH850
#define ECY_HSM_VMS_ARCH_GROUP                                ECY_HSM_VMS_ARCH_GROUP_RH850_V4
#define ECY_HSM_VMS_ARCH_HSM_TYPE                             ECY_HSM_VMS_ARCH_HSM_TYPE_RH850_ICUMH
#define ECY_HSM_VMS_ARCH_TARGET                               ECY_HSM_VMS_ARCH_TARGET_RH850_V4_D7_DM

#define ECY_HSM_VMS_ARCH_ENDIANNESS                           ECY_HSM_LITTLE_ENDIAN

#define ECY_HSM_VMS_ARCH_SINGLE_ENDED                         FALSE
#define ECY_HSM_VMS_ARCH_OFFSET_SIGNED                        65536
#define ECY_HSM_VMS_ARCH_OFFSET_UNSIGNED                      65536U
#define ECY_HSM_VMS_ARCH_PHYS_SIZE_SIGNED                     196608
#define ECY_HSM_VMS_ARCH_PHYS_SIZE_UNSIGNED                   196608U

#define ECY_HSM_VMS_ARCH_MAX_HOST_SESSIONS_CORE               16U
#endif /* ECY_HSM_VMS_ARCH_CFG_H */
