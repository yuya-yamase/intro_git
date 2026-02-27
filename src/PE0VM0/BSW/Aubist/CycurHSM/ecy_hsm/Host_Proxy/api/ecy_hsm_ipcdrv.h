/**
 * @file
 ***********************************************************************************************
 * @brief Inter-processor communication (IPC) driver adapter interface
 *
 * [$Satisfies $COMPONENT IPC_Driver]
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_IPCDRV_H
#define ECY_HSM_IPCDRV_H

/**
 * @addtogroup IPCDRV
 * @{
 */

/* *** includes *******************************************************************************/

#include "Platform_Types.h"
#include "ecy_hsm_ipcmcal.h"

/* *** defines ********************************************************************************/

/**
 * Create uint32 bit mask from event number
 */
#define IPCDRV_BITMSK(_bitNum) (uint32)(1UL << (_bitNum))

/**
 * Check if specified bit is set within specified bit mask
 */
#define IPCDRV_ISBITSET(_bitMask, _bitNum) (((_bitMask) & IPCDRV_BITMSK((_bitNum))) != 0UL)

#define ALL_FLAGS_ON  0xFFFFFFFFU /**< uint32 mask with all bits set */
#define ALL_FLAGS_OFF 0x00000000U /**< uint32 mask with all bits unset */

/* *** type declarations **********************************************************************/

/**
 * IPC driver Event numbers
 */
typedef enum ecy_hsm_IpcDrv_EventIdTag
{
    ecy_hsm_IPCDRV_EVENT_ID_0,
    ecy_hsm_IPCDRV_EVENT_ID_1,
    ecy_hsm_IPCDRV_EVENT_ID_2,
    ecy_hsm_IPCDRV_EVENT_ID_3,
    ecy_hsm_IPCDRV_EVENT_ID_4,
    ecy_hsm_IPCDRV_EVENT_ID_5,
    ecy_hsm_IPCDRV_EVENT_ID_6,
    ecy_hsm_IPCDRV_EVENT_ID_7,
    ecy_hsm_IPCDRV_EVENT_ID_8,
    ecy_hsm_IPCDRV_EVENT_ID_9,
    ecy_hsm_IPCDRV_EVENT_ID_10,
    ecy_hsm_IPCDRV_EVENT_ID_11,
    ecy_hsm_IPCDRV_EVENT_ID_12,
    ecy_hsm_IPCDRV_EVENT_ID_13,
    ecy_hsm_IPCDRV_EVENT_ID_14,
    ecy_hsm_IPCDRV_EVENT_ID_15,
    ecy_hsm_IPCDRV_EVENT_ID_16,
    ecy_hsm_IPCDRV_EVENT_ID_17,
    ecy_hsm_IPCDRV_EVENT_ID_18,
    ecy_hsm_IPCDRV_EVENT_ID_19,
    ecy_hsm_IPCDRV_EVENT_ID_20,
    ecy_hsm_IPCDRV_EVENT_ID_21,
    ecy_hsm_IPCDRV_EVENT_ID_22,
    ecy_hsm_IPCDRV_EVENT_ID_23,
    ecy_hsm_IPCDRV_EVENT_ID_24,
    ecy_hsm_IPCDRV_EVENT_ID_25,
    ecy_hsm_IPCDRV_EVENT_ID_26,
    ecy_hsm_IPCDRV_EVENT_ID_27,
    ecy_hsm_IPCDRV_EVENT_ID_28,
    ecy_hsm_IPCDRV_EVENT_ID_29,
    ecy_hsm_IPCDRV_EVENT_ID_30,
    ecy_hsm_IPCDRV_EVENT_ID_31,
    ecy_hsm_IPCDRV_EVENT_ID_RESERVED = 0x7FFFFFFFUL
} ecy_hsm_IpcDrv_EventIdT;

/**
 * IPC driver state Flag numbers
 */
typedef enum ecy_hsm_IpcDrv_FlagIdTag
{
    ecy_hsm_IPCDRV_FLAG_ID_0,
    ecy_hsm_IPCDRV_FLAG_ID_1,
    ecy_hsm_IPCDRV_FLAG_ID_2,
    ecy_hsm_IPCDRV_FLAG_ID_3,
    ecy_hsm_IPCDRV_FLAG_ID_4,
    ecy_hsm_IPCDRV_FLAG_ID_5,
    ecy_hsm_IPCDRV_FLAG_ID_6,
    ecy_hsm_IPCDRV_FLAG_ID_7,
    ecy_hsm_IPCDRV_FLAG_ID_8,
    ecy_hsm_IPCDRV_FLAG_ID_9,
    ecy_hsm_IPCDRV_FLAG_ID_10,
    ecy_hsm_IPCDRV_FLAG_ID_11,
    ecy_hsm_IPCDRV_FLAG_ID_12,
    ecy_hsm_IPCDRV_FLAG_ID_13,
    ecy_hsm_IPCDRV_FLAG_ID_14,
    ecy_hsm_IPCDRV_FLAG_ID_15,
    ecy_hsm_IPCDRV_FLAG_ID_16,
    ecy_hsm_IPCDRV_FLAG_ID_17,
    ecy_hsm_IPCDRV_FLAG_ID_18,
    ecy_hsm_IPCDRV_FLAG_ID_19,
    ecy_hsm_IPCDRV_FLAG_ID_20,
    ecy_hsm_IPCDRV_FLAG_ID_21,
    ecy_hsm_IPCDRV_FLAG_ID_22,
    ecy_hsm_IPCDRV_FLAG_ID_23,
    ecy_hsm_IPCDRV_FLAG_ID_24,
    ecy_hsm_IPCDRV_FLAG_ID_25,
    ecy_hsm_IPCDRV_FLAG_ID_26,
    ecy_hsm_IPCDRV_FLAG_ID_27,
    ecy_hsm_IPCDRV_FLAG_ID_28,
    ecy_hsm_IPCDRV_FLAG_ID_29,
    ecy_hsm_IPCDRV_FLAG_ID_30,
    ecy_hsm_IPCDRV_FLAG_ID_31,
    ecy_hsm_IPCDRV_FLAG_ID_RESERVED = 0x7FFFFFFFUL
} ecy_hsm_IpcDrv_FlagIdT;


/* *** global constants ***********************************************************************/


/* *** exported interfaces ********************************************************************/

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

/**
 * @brief Initialize IPC driver
 *
 * Details:
 * 1.  The HSM status SHALL be cleared
 * 2.  All IPC-related HSM interrupts SHALL be disabled
 * 3.  All host-to-HSM events SHALL be acknowledged
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_Initialize().
 * */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_Initialize() ecy_hsm_IpcMcal_Initialize()

/*
 * HSM IRQ states
 */

/**
 * @brief Configures the IRQs for the specified host-to-HSM IPC events.
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_ConfigureIrqs().
 *
 * @note This function is only implemented in HSM BUILD
 *
 * @param[in] hsmEventMask   Bit mask @ref IPCDRV_BITMSK indicating which bits of hsmEventValue shall
 *                           be applied BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 * @param[in] hsmEventValue  Bit mask  @ref IPCDRV_BITMSK indicating the values for events for which the
 *                           IRQs shall be enabled / disabled
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_ConfigureIrqs(hsmEventMask, hsmEventValue ) ecy_hsm_IpcMcal_ConfigureIrqs( hsmEventMask, hsmEventValue )

/**
 * @brief Returns the enable/disable state of the IRQs
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_GetIrqStates().
 *
 * @note This function is only implemented in HSM BUILD
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the IRQ enabling states of all events
 *          BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_GetIrqStates() ecy_hsm_IpcMcal_GetIrqStates()


/*
 * HSM event states
 */

/**
 * @brief Acknowledge the specified host-to-HSM IPC events
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_AcknowledgeEvents().
 *
 * @note This function is only implemented in HSM BUILD
 *
 * @param[in] hsmEventMask  Bit mask @ref IPCDRV_BITMSK indicating the events to be acknowledged
 *                          BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_AcknowledgeEvents( hsmEventMask ) ecy_hsm_IpcMcal_AcknowledgeEvents( hsmEventMask )


/**
 * @brief Returns the states of the host-to-HSM IPC events
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_GetHostEvents().
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the states of all events
 *          BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_GetHostEvents() ecy_hsm_IpcMcal_GetHostEvents()

/**
 * @brief Send specified IPC events to the IPC partner
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_SendEvents().
 *
 * @note This function is only implemented in HSM BUILD
 *
 * @param[in] hostEventMask  Bit mask @ref IPCDRV_BITMSK indicating the HSM-to-host events to be signaled
 *                           BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_SendEvents( hostEventMask ) ecy_hsm_IpcMcal_SendEvents( hostEventMask )

/**
 * @brief Returns the states of the HSM-to-host IPC events
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_GetHsmEvents().
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating the states of all HSM-to-host events
 *          BIT_0=@ref ecy_hsm_IPCDRV_EVENT_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_EVENT_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_GetHsmEvents() ecy_hsm_IpcMcal_GetHsmEvents()

/**
 * @brief Read 32-bit of data provided by the host through the IPC.
 *        The interpretation of this data is up to the application.
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_GetHostStatus().
 *
 * @return  32-Bit data value from host
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_GetHostData() ecy_hsm_IpcMcal_GetHostStatus()

/*
 * HSM status flags
 */

/**
 * @brief Set IPC status flags
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_SetStatus().
 *
 * @note This function is only implemented in HSM BUILD
 *
 * @param hsmStatusFlagMask   Bit mask @ref IPCDRV_BITMSK indicating all HSM-to-host status
 *                            bits to be modified BIT_0 = FLAG_0, BIT_1 = FLAG_1
 * @param hsmStatusFlagValue  Bit mask  @ref IPCDRV_BITMSK indicating all HSM-to-host status
 *                            bit values be set BIT_0 = FLAG_0, BIT_1 = FLAG_1
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_SetStatus( hsmStatusFlagMask, hsmStatusFlagValue ) ecy_hsm_IpcMcal_SetStatus( hsmStatusFlagMask, hsmStatusFlagValue )

/**
 * @brief Return the state of all HSM-to-host status flags
 *
 * This IPC driver adapter function calls the IPC-MCAL
 * layer function ecy_hsm_IpcMcal_GetHsmStatus().
 *
 * @return  Bit mask @ref IPCDRV_BITMSK indicating all HSM-to-host status bit values
 *          BIT_0=@ref ecy_hsm_IPCDRV_FLAG_ID_0, BIT_1=@ref ecy_hsm_IPCDRV_FLAG_ID_1 ...
 */
/* PRQA S 1503 1 */ /* Deviation: rule_2.1_1503_Proxy */
#define ecy_hsm_IpcDrv_GetHsmStatus() ecy_hsm_IpcMcal_GetHsmStatus()


/* *INDENT-OFF* */
#ifdef __cplusplus
} /* extern "C" */
#endif
/* *INDENT-ON* */


/**
 * @}
 */

#endif /* ECY_HSM_IPCDRV_H */
