/* bsw_ipdum_public_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/IPDUM/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_IPDUM_PUBLIC_H
#define BSW_IPDUM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define BSW_IPDUM_VENDOR_ID                     (83U)

/* Module ID */
#define BSW_IPDUM_MODULE_ID                     (52U)

/* AUTOSAR Release Version */
#define BSW_IPDUM_AR_RELEASE_MAJOR_VERSION              (4U)
#define BSW_IPDUM_AR_RELEASE_MINOR_VERSION              (5U)
#define BSW_IPDUM_AR_RELEASE_REVISION_VERSION                (0U)

/* Vendor Specification Version */
#define BSW_IPDUM_SW_MAJOR_VERSION              (4U)
#define BSW_IPDUM_SW_MINOR_VERSION              (5U)
#define BSW_IPDUM_SW_PATCH_VERSION              (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint8 Dummy;
} Bsw_IpduM_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
Std_ReturnType bsw_ipdum_trx_Transmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_ipdum_trx_CancelTransmit( PduIdType TxPduId );
void           bsw_ipdum_st_MainFunctionTx( void );
void           bsw_ipdum_st_MainFunctionRx( void );
void           bsw_ipdum_st_Init( BswConst Bsw_IpduM_ConfigType* config );
void           bsw_ipdum_st_shutdown( void );
void           bsw_ipdum_st_GetVersionInfo( Std_VersionInfoType* versioninfo );

void           bsw_ipdum_trx_RxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void           bsw_ipdum_trx_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
Std_ReturnType bsw_ipdum_trx_TriggerTransmit( PduIdType TxPduId, PduInfoType* PduInfoPtr );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_IPDUM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/31                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
