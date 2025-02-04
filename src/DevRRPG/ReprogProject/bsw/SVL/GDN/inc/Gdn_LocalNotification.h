/* Gdn_LocalNotification_h_01_0004 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | GDN内部Notification定義                                      */
/* Notes       |                                                              */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  ##_####   yyyy/mm/dd   DNXXX    Header File Template                      */
/*  01_0000   2015/11/23   DC       マルチコア対応                            */
/*  01_0001   2016/01/07   DC       送信完了通知のコールバック対応            */
/*  01_0002   2018/02/13   AUBASS   リプログ対応                              */
/*  01_0003   2019/12/03   AUBASS   Update                                    */
/*  01_0004   2021/09/14   AUBASS   Update                                    */
/******************************************************************************/
#ifndef GDN_LOCALNOTIFICATION_H
#define GDN_LOCALNOTIFICATION_H

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <GdnWrapper/Gdn_Rte_EvtDistributor.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_DCP_EVENTID_SERVICE_PROCESSING  (0x00UL) /* Gdn_Dcm_Dcp_ServiceProcessingFuncTask() Event Id */
#define GDN_DCM_DCP_EVENTID_SERVICE_DONE        (0x01UL) /* Gdn_Dcm_Dcp_ProcessingDoneFuncTask() Event Id */
#define GDN_DCM_DCP_EVENTID_SESSION_TRANSITION  (0x02UL) /* Gdn_Dcm_Dcp_SessionTransitionFuncTask() Event Id */
#if ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON )
#define GDN_DCM_DCP_EVENTID_SUB_SERVICE_GW      (0x03UL) /* Gdn_Dcm_Dcp_SubMiconGatewayProcessingFuncTask() Event Id */
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables                                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define GDN_START_SEC_CST
#include <Gdn_MemMap.h>

#define GDN_STOP_SEC_CST
#include <Gdn_MemMap.h>

/******************************************************************************/
/* External Function Prototypes                                               */
/******************************************************************************/

#endif /* GDN_LOCALNOTIFICATION_H */
/**** End of File *************************************************************/
