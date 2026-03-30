/**
 * @file ecy_hsm_general_pubcfg.h
 ***********************************************************************************************
 * @brief CycurHSM configuration file.
 * CycurHSM configuration file.
 *
 * Customers having h/w specific header files may come across to double register definitions by
 * including this file.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_GENERAL_PUBCFG_H
#define ECY_HSM_GENERAL_PUBCFG_H

#include "ecy_hsm_vms_arch_cfg.h"
#include "ecy_hsm_general_pubcfg_temp.h"
#include "ecy_hsm_vms_compiler.h"

#ifndef CYCURHSM_CONFIG_WITH_CLOSESESSION_LEGACY
/** Switch the ecy_hsm_Csai_CloseSession() API between synchronous & asynchronous interfaces according to the configuration */
#define CYCURHSM_CONFIG_WITH_CLOSESESSION_LEGACY DISABLED
#endif

/**
* @brief Switch to enable CMAC quick route fail fast when CMAC quick route is not successful.
* Default Qualified value : ecy_hsm_QUICK_ROUTE_FAILFAST = DISABLED
*/
#define ecy_hsm_QUICK_ROUTE_FAILFAST (DISABLED)

/**
* @brief Macro to change CMAC quick route max size.
*
* @details
* This macro change the maximum msg bytes that CMAC quick route allow
*
* @note
* The macro is configurable but with limitation( it has upper limit of 512 bytes)
* Changing the macro higher than the upper limit will cause compilation error
* Changing the macro to 0 will cause compilation error
*
* @note
* Changing the macro to different value could lead to different running time(during this time the HSM will not respond)
* So increasing ecy_hsm_MAX_QUICK_ROUTE_BYTES will increase the potential jitter
*
* Default Qualified value : ecy_hsm_MAX_QUICK_ROUTE_BYTES = 256U
*/
#define ecy_hsm_MAX_QUICK_ROUTE_BYTES       (256U)

/* Typedefs for the register pointers */
typedef unsigned char   uchar_reg;
typedef unsigned short  ushort_reg;
typedef unsigned long   ulong_reg;

#if (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_IFX)
#include "ecy_hsm_Reg_bridge_ifx.h"

/* HSM/HOST Communication interface registers*/
#define HSM_BRIDGE_HSM2HTF         BRIDGE.HSM2HTF
#define HSM_BRIDGE_HSM2HTIE        BRIDGE.HSM2HTIE
#define HSM_BRIDGE_HSM2HTS         BRIDGE.HSM2HTS
#define HSM_BRIDGE_HT2HSMF         BRIDGE.HT2HSMF
#define HSM_BRIDGE_HT2HSMS         BRIDGE.HT2HSMS


#define HOST_BRIDGE_HT2HSMF        BRIDGE.HT2HSMF
#define HOST_BRIDGE_HT2HSMS        BRIDGE.HT2HSMS
#define HOST_BRIDGE_HSM2HTF        BRIDGE.HSM2HTF
#define HOST_BRIDGE_HSM2HTIE       BRIDGE.HSM2HTIE
#define HOST_BRIDGE_HSM2HTS        BRIDGE.HSM2HTS

/* On the TC2xx targets the HSM Bridge is not accessible when the HSM is disabled.
 * The HSM Bridge is always accessible on the TC3xx targets.*/
# if ( ( ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_IFX_TC2XX ) && ( ENABLED == HSM_BRIDGE_ACCESSIBLE_CHECK ) )
#define PROCON_HSM_COTP             ( *( volatile uint32 * ) ( 0xF8002034UL ) )    /**< Address of the HSM Code Flash OTP
                                                                                        Protection Configuration register.
                                                                                        Position 0 HSMBOOTEN flag */
#define HSMBOOTEN_MSK               ( 0x01UL )
#define IS_HSM_BRIDGE_ACCESSIBLE()  ( PROCON_HSM_COTP & HSMBOOTEN_MSK )
# else
#define IS_HSM_BRIDGE_ACCESSIBLE()  ( 1UL )
# endif

#elif (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_RH850)

#define BYTEREG(reg)    ((*(volatile uchar_reg *) (reg)))
#define SHORTREG(reg)   ((*(volatile ushort_reg *) (reg)))
#define LONGREG(reg)    ((*(volatile ulong_reg *) (reg)))

#define ICUMACTFLAG LONGREG(0xFF1F0018UL)     /**< ICUMC Activation flag register                             */

#define ICU2PES     LONGREG(0xFF1F0010UL)     /**< ICUMC to PE status register                                */

#define PE2ICUS     LONGREG(0xFF1F0014UL)     /**< PE to ICUMC status register                                */

#define PE2ICUF     LONGREG(0xFF1F0040UL)     /**< PE to ICUMC interrupt flags (read only)                    */
#define PE2ICUFS    LONGREG(0xFF1F0044UL)     /**< PE to ICUMC interrupt flags (PE can write 1 to set)        */
#define PE2ICUFC    LONGREG(0xFF1F0048UL)     /**< PE to ICUMC interrupt flags (ICUMC can write 1 to clear)   */

#define PE2ICUIE    LONGREG(0xFF1F004CUL)     /**< PE to ICUMC interrupt enables                              */

#define ICU2PEF     LONGREG(0xFF1F0050UL)     /**< ICUMC to PE interrupt flags (read only)                    */
#define ICU2PEFS    LONGREG(0xFF1F0054UL)     /**< ICUMC to PE interrupt flags (ICUMC can write 1 to set)     */
#define ICU2PEFC    LONGREG(0xFF1F0058UL)     /**< ICUMC to PE interrupt flags (PE can write 1 to clear)      */

#define ICU2PEIE    LONGREG(0xFF1F005CUL)     /**< ICUMC to PE interrupt enables                              */
#define ICU2PEIS    LONGREG(0xFF1F0060UL)     /**< b0 controls interrupt destination, 0-PE1, 1-PE2            */

#define PEFLPRG0REQ       LONGREG(0xFF1F0020UL)    /* PE D-flash prog request on bank 0         */
#define PEFLPRG1REQ       LONGREG(0xFF1F0024UL)    /* PE D-flash prog request on bank 1         */
#define PEFLPRG0ACK       LONGREG(0xFF1F0028UL)    /* PE D-flash prog req. ACK on bank 0        */
#define PEFLPRG1ACK       LONGREG(0xFF1F002CUL)    /* PE D-flash prog req. ACK on bank 1        */

#if ( (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V3)  ||   \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4)  ||   \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V5) )
#define PE2ICUSF     LONGREG(0xFF1F0070UL)     /**< PE to ICUMC single interrupt flags (read only)                    */
#define PE2ICUSFS    LONGREG(0xFF1F0074UL)     /**< PE to ICUMC single interrupt flags (PE can write 1 to set)        */
#define PE2ICUSFC    LONGREG(0xFF1F0078UL)     /**< PE to ICUMC single interrupt flags (ICUMC can write 1 to clear)   */
#define PE2ICUSIE    LONGREG(0xFF1F007CUL)     /**< PE to ICUMC single interrupt enables                              */
#endif /* #if ( (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V3)  ||   \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V4)  ||   \
      (ECY_HSM_VMS_ARCH_GROUP == ECY_HSM_VMS_ARCH_GROUP_RH850_V5)) */

#if (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S4) || \
    (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S2)
/* Semaphore Register */
#define ICUM_CMDREG_ADDR      (0xFF1F0000UL)
#define ICUM_SEMAPE1_ADDR     (ICUM_CMDREG_ADDR + 0x00A0UL)
#define ICUM_SEMAPE1_VAL      LONGREG(ICUM_SEMAPE1_ADDR)
#endif /* (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_RH850_V3_S4) */

#elif (ECY_HSM_VMS_ARCH_FAMILY == ECY_HSM_VMS_ARCH_FAMILY_POWER)

#define ECY_HSM_REGISTER(kind, addr)         (*(volatile kind *) (addr))
#define ECY_HSM_REGISTER_ADDR(kind, addr)    ((volatile kind *) (addr))


#if (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_POWER_MPC_MPC5748X)
#define HOST_BRIDGE_HSM2HTF         ECY_HSM_REGISTER(ulong_reg, 0xFFF30000UL)   /** HSM to Host flags  (HSM sets, host clears)                      */
#define HOST_BRIDGE_HSM2HTIE        ECY_HSM_REGISTER(ulong_reg, 0xFFF30004UL)   /** HSM to Host interrupt enables (HSM can read)                    */
#define HOST_BRIDGE_HT2HSMF         ECY_HSM_REGISTER(ulong_reg, 0xFFF30008UL)   /** Host to HSM flags (Host sets, HSM clears)                       */
#define HOST_BRIDGE_HT2HSMIE        ECY_HSM_REGISTER(ulong_reg, 0xFFF3000CUL)   /** Host to HSM interrupt enables (always reads as zero from host)  */
#define HOST_BRIDGE_HSM2HTS         ECY_HSM_REGISTER(ulong_reg, 0xFFF30010UL)   /** HSM to Host status / command (not used in CycurHSM)             */
#define HOST_BRIDGE_HT2HSMS         ECY_HSM_REGISTER(ulong_reg, 0xFFF30014UL)   /** Host to HSM status / command word (only host can write)         */
#else
#define HOST_BRIDGE_HSM2HTF         ECY_HSM_REGISTER(ulong_reg, 0xF7F30000UL)   /** HSM to Host flags  (HSM sets, host clears)                      */
#define HOST_BRIDGE_HSM2HTIE        ECY_HSM_REGISTER(ulong_reg, 0xF7F30004UL)   /** HSM to Host interrupt enables (HSM can read)                    */
#define HOST_BRIDGE_HT2HSMF         ECY_HSM_REGISTER(ulong_reg, 0xF7F30008UL)   /** Host to HSM flags (Host sets, HSM clears)                       */
#define HOST_BRIDGE_HT2HSMIE        ECY_HSM_REGISTER(ulong_reg, 0xF7F3000CUL)   /** Host to HSM interrupt enables (always reads as zero from host)  */
#define HOST_BRIDGE_HSM2HTS         ECY_HSM_REGISTER(ulong_reg, 0xF7F30010UL)   /** HSM to Host status / command (not used in CycurHSM)             */
#define HOST_BRIDGE_HT2HSMS         ECY_HSM_REGISTER(ulong_reg, 0xF7F30014UL)   /** Host to HSM status / command word (only host can write)         */
#endif /* (ECY_HSM_VMS_ARCH_TARGET == ECY_HSM_VMS_ARCH_TARGET_POWER_MPC_MPC5748X) */

#define PFLASH_PFAPR      ECY_HSM_REGISTER(ulong_reg, 0xF403000CUL)
#define PFAPR_M14AP       (0x0000000CUL)
#define ME_MCTL           ECY_HSM_REGISTER(ulong_reg, 0xF7FB8004UL)
#define MCTL_KEY          (0x00005AF0UL)
#define MCTL_INV_KEY      (0x0000A50FUL)
#define ME_CADDR4         ECY_HSM_REGISTER(ulong_reg, 0xF7FB81F0UL)
#define ME_CCTL4          ECY_HSM_REGISTER(ushort_reg, 0xF7FB81CCUL)
#define ME_CS             ECY_HSM_REGISTER(ulong_reg, 0xF7FB81C0UL)
#define ME_CS_CORE_HSM    (0x00000010UL)
#endif

/**
 * @addtogroup GROUP_CYCURHSM_CONFIG
 * @{
 */

/* *** includes *******************************************************************************/


/* *** defines ********************************************************************************/
/**
 *
 */

/** Global switch to enable error handling in HSM bridge resource locking and unlocking. Error handling will check that
 * the resource is never falsely locked or unlocked twice.
 */
#ifndef ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING
    /**
     * Enable / disable HSM bridge resource locking/unlocking error handling
     */
    #define ecy_hsm_ENABLE_RESOURCE_ERROR_HANDLING                  (DISABLED)
#endif

/**
 *
 */

/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/**
 * @}
 */
#endif /* ECY_HSM_GENERAL_PUBCFG_H  */
