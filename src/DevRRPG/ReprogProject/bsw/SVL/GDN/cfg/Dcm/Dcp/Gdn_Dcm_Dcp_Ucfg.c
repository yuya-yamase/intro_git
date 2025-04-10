/* Gdn_Dcm_Dcp_Ucfg_c_00_0002 */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Module Name | Gdn_Dcm_Dcp_Ucfg.c                                           */
/* Notes       | ツールバージョン：GUARDIAN_218v41_MET_Tool217                */
/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision  Date         By       Description                               */
/*----------------------------------------------------------------------------*/
/*  00_0000   2014/03/dd   DN矢加部 新規作成                                  */
/*  00_0001   2018/06/19   AUBASS   リプログ対応                              */
/*  00_0002   2019/12/03   AUBASS   Update                                    */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Header Files                                                               */
/*----------------------------------------------------------------------------*/
#include <Gdn.h>
#include <Gdn_Ucfg.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

#define     Gdn_Dcm_Dcp_Set_RxPduConfig(index)                                  \
{                                                                               \
    (Gdn_PduIdType)GDN_DCM_DCP_RXPDUID_##index##_ID,                            \
    (Gdn_Dcm_MsgAddInfoReqTypeType)GDN_DCM_DCP_RXPDUID_##index##_RXTYPE,        \
    (gdn_uint8)GDN_DCM_DCP_RXPDUID_##index##_CONNECTIONID                       \
}

#define     Gdn_Dcm_Dcp_Set_ConnectionConfig(index)                             \
{                                                                               \
    (gdn_uint8)GDN_DCM_DCP_CONNECTION_##index##_PRIORITY,                       \
    (Gdn_PduIdType)GDN_DCM_DCP_CONNECTION_##index##_TXCONF_ID,                  \
    (Gdn_PduIdType)GDN_DCM_DCP_CONNECTION_##index##_TXREF_ID                    \
}

/*----------------------------------------------------------------------------*/
/* Static Variables                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

#define GDN_DCM_STOP_SEC_VAR
#include <Gdn_Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Static Constants                                                           */
/*----------------------------------------------------------------------------*/
#define GDN_DCM_START_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/* RXPDUコンフィグレーション項目 */
GdnConst Gdn_Dcm_Dcp_RxPduConfigType Gdn_Dcm_Dcp_RxPduIdConfig[GDN_DCM_DCP_ALL_RXPDUID_NUM] = {
    Gdn_Dcm_Dcp_Set_RxPduConfig( 0 ),
    Gdn_Dcm_Dcp_Set_RxPduConfig( 1 ),
    Gdn_Dcm_Dcp_Set_RxPduConfig( 2 ),
    Gdn_Dcm_Dcp_Set_RxPduConfig( 3 )
};

/* Connectionコンフィグレーション項目 */
GdnConst Gdn_Dcm_Dcp_ConnectionConfigType Gdn_Dcm_Dcp_ConnectionConfig[GDN_DCM_DCP_ALL_CONNECTION_NUM] = {
    Gdn_Dcm_Dcp_Set_ConnectionConfig( 0 ),
    Gdn_Dcm_Dcp_Set_ConnectionConfig( 1 ),
    Gdn_Dcm_Dcp_Set_ConnectionConfig( 2 ),
    Gdn_Dcm_Dcp_Set_ConnectionConfig( 3 )
};

#define GDN_DCM_STOP_SEC_CST
#include <Gdn_Dcm_MemMap.h>

/*-- End Of File -------------------------------------------------------*/

