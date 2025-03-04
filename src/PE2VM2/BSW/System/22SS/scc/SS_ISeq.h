/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ISeq.h
 * [Module]			Initialize Sequencer
 * [Function]		Initialize at updating status
 * [Notes]			None
 ****************************************************************************/
#ifndef SS_ISEQ_H
#define SS_ISEQ_H

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_Internal.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
/* core synchronize ID */
/* ISeq Component */
#define SS_ISEQ_u2SID_ISEQ_STUPBOOT_A ((uint16)0x0010U)
#define SS_ISEQ_u2SID_ISEQ_STUPBOOT_B ((uint16)0x0011U)
#define SS_ISEQ_u2SID_ISEQ_STUPBOOT_C ((uint16)0x0012U)
#define SS_ISEQ_u2SID_ISEQ_STUPBOOT_D ((uint16)0x0013U)
#define SS_ISEQ_u2SID_ISEQ_STUPBOOT_E ((uint16)0x0014U)

#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_A ((uint16)0x0020U)
#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_B ((uint16)0x0021U)
#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_C ((uint16)0x0022U)
#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_D ((uint16)0x0023U)
#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_E ((uint16)0x0024U)
#define SS_ISEQ_u2SID_ISEQ_WKUPBOOT_F ((uint16)0x0025U)

#define SS_ISEQ_u2SID_ISEQ_INITZERO_A ((uint16)0x0030U)
#define SS_ISEQ_u2SID_ISEQ_INITZERO_B ((uint16)0x0031U)

#define SS_ISEQ_u2SID_ISEQ_INITONE_A ((uint16)0x0040U)
#define SS_ISEQ_u2SID_ISEQ_INITONE_B ((uint16)0x0041U)
#define SS_ISEQ_u2SID_ISEQ_INITONE_D ((uint16)0x0043U)
#define SS_ISEQ_u2SID_ISEQ_INITONE_E ((uint16)0x0044U)
#define SS_ISEQ_u2SID_ISEQ_INITONE_L ((uint16)0x004BU)

#define SS_ISEQ_u2SID_ISEQ_POSTOS_A ((uint16)0x0050U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_B ((uint16)0x0051U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_C ((uint16)0x0052U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_D ((uint16)0x0053U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_E ((uint16)0x0054U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_F ((uint16)0x0055U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_G ((uint16)0x0056U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_H ((uint16)0x0057U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_I ((uint16)0x0058U)
#define SS_ISEQ_u2SID_ISEQ_POSTOS_J ((uint16)0x0059U)

#define SS_ISEQ_u2SID_ISEQ_SLEEP_A ((uint16)0x0060U)
#define SS_ISEQ_u2SID_ISEQ_SLEEP_B ((uint16)0x0061U)
#define SS_ISEQ_u2SID_ISEQ_SLEEP_C ((uint16)0x0062U)

#define SS_ISEQ_u2SID_ISEQ_CLRUPREQ_A ((uint16)0x0064U)
#define SS_ISEQ_u2SID_ISEQ_CLRUPREQ_B ((uint16)0x0065U)

#define SS_ISEQ_u2SID_ISEQ_GETBOOT_A ((uint16)0x0070U)

#define SS_ISEQ_u2SID_ISEQ_RESLEEP_A ((uint16)0x0080U)
#define SS_ISEQ_u2SID_ISEQ_RESLEEP_B ((uint16)0x0081U)
#define SS_ISEQ_u2SID_ISEQ_RESLEEP_C ((uint16)0x0082U)
#define SS_ISEQ_u2SID_ISEQ_RESLEEP_D ((uint16)0x0083U)

/* ResetM Component */
#define SS_ISEQ_u2SID_RESETM_RSTREQ_A ((uint16)0x0100U)
#define SS_ISEQ_u2SID_RESETM_RSTREQ_B ((uint16)0x0110U)

/* State Component */
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_A ((uint16)0x0200U)
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_B ((uint16)0x0201U)
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_C ((uint16)0x0202U)
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_D ((uint16)0x0203U)
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_E ((uint16)0x0204U)
#define SS_ISEQ_u2SID_STATE_CHKSLEEP_F ((uint16)0x0205U)

#define SS_ISEQ_u2SID_STATE_CHKWUP_A ((uint16)0x020EU)
#define SS_ISEQ_u2SID_STATE_CHKWUP_B ((uint16)0x020FU)
#define SS_ISEQ_u2SID_STATE_CHKWUP_C ((uint16)0x0045U)

#define SS_ISEQ_u2SID_STATE_TRANSIT_A ((uint16)0x0210U)
#define SS_ISEQ_u2SID_STATE_TRANSIT_B ((uint16)0x0211U)
#define SS_ISEQ_u2SID_STATE_TRANSIT_C ((uint16)0x0212U)

#define SS_ISEQ_u2SID_STATE_ENTMODE_A ((uint16)0x0220U)
#define SS_ISEQ_u2SID_STATE_ENTMODE_B ((uint16)0x0221U)

#define SS_ISEQ_u2SID_STATE_INIT_A ((uint16)0x0230U)
#define SS_ISEQ_u2SID_STATE_INIT_B ((uint16)0x0231U)

/* Error Component */
#define SS_ISEQ_u2SID_ERROR_CHKHNDL_A ((uint16)0x0500U)
#define SS_ISEQ_u2SID_ERROR_CHKHNDL_B ((uint16)0x0510U)
#define SS_ISEQ_u2SID_ERROR_CHKHNDL_C ((uint16)0x0511U)

/* Shutdown Component */
#define SS_ISEQ_u2SID_SHUTDOWN_REQ_A ((uint16)0x0600U)
#define SS_ISEQ_u2SID_SHUTDOWN_REQ_B ((uint16)0x0610U)
#define SS_ISEQ_u2SID_SHUTDOWN_REQ_C ((uint16)0x0620U)

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/

void SS_ISeq_stupBoot(SS_BootType u4BootSource);
#if (SS_USE_SLEEP == STD_ON)
void SS_ISeq_checkWakeupAndReSleep(void);
void SS_ISeq_sleep(void);
void SS_Pm_requestWakeup(void);
#endif
void SS_Pm_DriverInitZero(void);
void SS_Pm_DriverInitOne(void);
#if (SS_USE_UP == STD_ON)
void SS_Pm_postStartOS(void);
#endif
#if (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC))
void SS_Pm_requestUp(void);
void SS_Pm_mainFunction(void);
#endif
#if (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT))
void SS_Pm_releaseUp(void);
void SS_Pm_transit(void);
#endif

#if (SS_USE_CORE_COUNT >= 2u)

void SS_ISeq_syncCores(uint16 u2_syncID);

#else /* (SS_USE_CORE_COUNT >= 2u) */

#define SS_ISeq_syncCores(ID)

#endif /* (SS_USE_CORE_COUNT >= 2u) */

#if ((SS_USE_SHUTDOWN == STD_ON) && (SS_USE_UP == STD_ON))
void SS_ISeq_shutdown(void);
#endif /* (SS_USE_SHUTDOWN == STD_ON) && (SS_USE_UP == STD_ON) */

#if (SS_USE_CORE_COUNT >= 2u)
volatile extern uint32 SS_ISeq_u4SyncCheck_1;
#endif
#if (SS_USE_CORE_COUNT >= 3u)
volatile extern uint32 SS_ISeq_u4SyncCheck_2;
#endif
#if (SS_USE_CORE_COUNT >= 4u)
volatile extern uint32 SS_ISeq_u4SyncCheck_3;
#endif

#endif /* SS_ISEQ_H */
