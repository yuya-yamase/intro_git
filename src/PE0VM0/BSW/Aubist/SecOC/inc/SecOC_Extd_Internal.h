/* SecOC_Extd_Internal_h_v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Extd/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_EXTD_INTERNAL_H
#define SECOC_EXTD_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC_Extd.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (SECOC_AB_EXTD_INIT == STD_ON)
FUNC(void, SECOC_CODE) SecOC_Extd_Init
(
    void
);
#endif

#if (SECOC_AB_EXTD_DEINIT == STD_ON)
FUNC(void, SECOC_CODE) SecOC_Extd_DeInit
(
    void
);
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
#if (SECOC_AB_EXTD_FV_UPDATE_JUDGE == STD_ON)
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Extd_PreFvUpdate
(
    uint16 u2Index,
    Std_ReturnType udmacResult
);
#endif

#if (SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON)
FUNC(boolean, SECOC_CODE) SecOC_Extd_MessageNotifyJudge
(
    uint16 u2Index
);
#endif
#endif

#if (SECOC_AB_EXTD_VERIFY_STATUS_OVERRIDE == STD_ON)
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Extd_VerifyStatusOverride
(
    uint32 ValueID,
    SecOC_OverrideStatusType overrideStatus,
    uint8 numberOfMessagesToOverride
);
#endif

#if (SECOC_AB_EXTD_MEMUTIL == STD_ON)
FUNC(void, SECOC_CODE) SecOC_Extd_MemCpy
(
    P2VAR(void, AUTOMATIC, SECOC_APPL_DATA) ptDst,
    P2CONST(void, AUTOMATIC, SECOC_APPL_DATA) ptSrc,
    uint32 u4Size
);
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_EXTD_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
