/**
 * @file
 ***********************************************************************************************
 * @brief Inter processor communication driver mcal interface
 *
 * [$Satisfies $COMPONENT IPC_MCAL]
 *
 * @details
 * Hardware specific routines to control communication between HSM and HOST controller
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_IPCMCAL_IF_H
#define ECY_HSM_IPCMCAL_IF_H

/**
 * @addtogroup IPCMCAL
 * @{
 */

/* *** includes *******************************************************************************/

#include "Platform_Types.h"
#include "Compiler.h"


/* *** defines ********************************************************************************/


/* *** type declarations **********************************************************************/

/* *** global constants ***********************************************************************/

/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_START_SEC_CODE
#include "ecy_hsm_MemMap.h"

/*
 * This define will be set by Unit tests which are stubbing these functions.
 * This define is necessary because the LOCAL_INLINE definition leads to build errors in the UTs.
 */
#ifndef TEST_IPC_MCAL_STUBBED

/**
 * [$DD 111]
 * @brief Initialize IPC driver
 * [$Satisfies $ARCH 13][$Satisfies $SW_ARCH 13_v1][$Satisfies $ARCH 856]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * Details:
 * 1.  The HSM status SHALL be cleared
 * 2.  All IPC-related HSM interrupts SHALL be disabled
 * 3.  All host-to-HSM events SHALL be acknowledged
 */
LOCAL_INLINE void ecy_hsm_IpcMcal_Initialize( void );


/*
 * HSM IRQ states
 */

/**
 * [$DD 112]
 * @brief Returns the enable/disable state of the IRQ for the specified host-to-HSM IPC event
 * [$Satisfies $ARCH 15][$Satisfies $SW_ARCH 15_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the IRQ enabling states of all
 *          events BIT_0 = EVENT_0, BIT_1=EVENT_1
 */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetIrqStates( void );

/**
 * [$DD 113]
 * @brief Enable / disable multiple IRQ for the specified host-to-HSM IPC event
 * [$Satisfies $ARCH 14][$Satisfies $SW_ARCH 14_v1][$Satisfies $SW_ARCH 437_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @param[in] hsmEventMask   Bit mask @ref IPCDRV_BITMSK indicating the host-to-HSM IPC
 *                           events for which the IRQs shall be modified
 *
 * @param[in] hsmEventValue  Bit mask @ref IPCDRV_BITMSK indicating the values for
 *                           events for which the IRQs shall be enabled / disabled
 */
LOCAL_INLINE void ecy_hsm_IpcMcal_ConfigureIrqs( uint32 hsmEventMask, uint32 hsmEventValue );

/*
 * HSM event states
 */

/**
 * [$DD 114]
 * @brief Returns the states of the host-to-HSM IPC events
 * [$Satisfies $ARCH 17][$Satisfies $SW_ARCH 17_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the states of all events
 *          BIT_0 = EVENT_0, BIT_1=EVENT_1
 */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHostEvents( void );

/**
 * [$DD 115]
 * @brief Acknowledge the specified host-to-HSM IPC events
 * [$Satisfies $ARCH 16][$Satisfies $SW_ARCH 16_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @param[in] hostEventMask  Bit mask indicating the events to be acknowledged
 *                          BIT_0 = EVENT_0, BIT_1=EVENT_1
 */
LOCAL_INLINE void ecy_hsm_IpcMcal_AcknowledgeEvents( uint32 hostEventMask );

/*
 * HOST events
 */

/**
 * [$DD 116]
 * @brief Returns the states of the HSM-to-host IPC events
 * [$Satisfies $ARCH 19][$Satisfies $SW_ARCH 19_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the states of all
 *          HSM-to-host events BIT_0 = EVENT_0, BIT_1=EVENT_1
 */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHsmEvents( void );

/**
 * [$DD 117]
 * @brief Signals specified HSM-to-host IPC events to the host
 * [$Satisfies $ARCH 18][$Satisfies $SW_ARCH 18_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @param[in] hsmEventMask  Bit mask @ref IPCDRV_BITMSK indicating the
 *                           HSM-to-host events to be signaled
 *                           BIT_0 = EVENT_0, BIT_1=EVENT_1
 */
LOCAL_INLINE void ecy_hsm_IpcMcal_SendEvents( uint32 hsmEventMask );

/*
 * HOST data
 */

/**
 * [$DD 118]
 * @brief Read 32-bit of data provided by the host through the IPC.
 *        The interpretation of this data is up to the application.
 * [$Satisfies $ARCH 20][$Satisfies $SW_ARCH 20_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @return  32-Bit data value from host
 */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHostStatus( void );

/*
 * HSM status flags
 */

/**
 * [$DD 119]
 * @brief Set specified HSM status flags at once to a defined value
 * [$Satisfies $ARCH 21][$Satisfies $SW_ARCH 21_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @param dataMask   Bit mask @ref IPCDRV_BITMSK indicating all HSM-to-host
 *                   status bits to be modified BIT_0 = FLAG_0, BIT_1=FLAG_1
 * @param dataValue  Bit mask  @ref IPCDRV_BITMSK indicating all HSM-to-host
 *                   status bit values be set BIT_0 = FLAG_0, BIT_1=FLAG_1
 */
LOCAL_INLINE void ecy_hsm_IpcMcal_SetStatus(uint32 dataMask, uint32 dataValue);


/**
 * [$DD 120]
 * @brief Return the state of all HSM-to-host status flags
 * [$Satisfies $ARCH 22][$Satisfies $SW_ARCH 22_v1]
 *
 * @note: On TC2x targets the HSM might trap when accessing the bridge, if the HSM has not been enabled.
 *        An additional check can be enabled to prevent that, see HSM_BRIDGE_ACCESSIBLE_CHECK.
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating all HSM-to-host status bit values
 *          BIT_0 = FLAG_0, BIT_1=FLAG_1
 */
LOCAL_INLINE uint32 ecy_hsm_IpcMcal_GetHsmStatus( void );

#endif /* TEST_IPC_MCAL_STUBBED */

/* PRQA S 5087 2 */ /** <Deviation: Include is used to map code to special memory sections */
#define ECY_HSM_STOP_SEC_CODE
#include "ecy_hsm_MemMap.h"

/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */


/**
 * @}
 */

#endif /* Multiple inclusion lock  */
