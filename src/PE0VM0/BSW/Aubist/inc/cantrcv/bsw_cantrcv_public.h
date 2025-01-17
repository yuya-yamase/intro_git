/* bsw_cantrcv_public_h_V2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTRCV/PUBLIC/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANTRCV_PUBLIC_H
#define BSW_CANTRCV_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define BSW_CANTRCV_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_CANTRCV_MODULE_ID                    (70U)

/* AUTOSAR Release Version */
#define BSW_CANTRCV_AR_RELEASE_MAJOR_VERSION             (4U)
#define BSW_CANTRCV_AR_RELEASE_MINOR_VERSION             (5U)
#define BSW_CANTRCV_AR_RELEASE_REVISION_VERSION               (0U)

/* Vendor Specification Version */
#define BSW_CANTRCV_SW_MAJOR_VERSION             (4U)
#define BSW_CANTRCV_SW_MINOR_VERSION             (5U)
#define BSW_CANTRCV_SW_PATCH_VERSION             (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8 Bsw_CanTrcv_PNActivationType;
typedef uint8 Bsw_CanTrcv_TrcvFlagStateType;

typedef struct
{
    uint8 Dummy;
} Bsw_CanTrcv_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void           bsw_cantrcv_st_Init( BswConst Bsw_CanTrcv_ConfigType* ConfigPtr );
void           bsw_cantrcv_st_DeInit( void );
Std_ReturnType bsw_cantrcv_st_SetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType OpMode);
Std_ReturnType bsw_cantrcv_st_GetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType* OpMode );
Std_ReturnType bsw_cantrcv_st_GetBusWuReason( uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason );
void           bsw_cantrcv_st_GetVersionInfo( Std_VersionInfoType* versioninfo );
Std_ReturnType bsw_cantrcv_st_SetWakeupMode( uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode );
Std_ReturnType bsw_cantrcv_st_GetTrcvSystemData( uint8 Transceiver, BswConstR uint32* TrcvSysData );
Std_ReturnType bsw_cantrcv_st_ClearTrcvWufFlag( uint8 Transceiver );
Std_ReturnType bsw_cantrcv_st_ReadTrcvTimeoutFlag( uint8 Transceiver, Bsw_CanTrcv_TrcvFlagStateType* FlagState );
Std_ReturnType bsw_cantrcv_st_ClearTrcvTimeoutFlg( uint8 Transceiver );
Std_ReturnType bsw_cantrcv_st_ReadTrcvSilenceFlag( uint8 Transceiver, Bsw_CanTrcv_TrcvFlagStateType* FlagState );
Std_ReturnType bsw_cantrcv_st_CheckWakeup( uint8 Transceiver );
Std_ReturnType bsw_cantrcv_st_SetPNActivationStat( Bsw_CanTrcv_PNActivationType ActivationState );
Std_ReturnType bsw_cantrcv_st_CheckWakeFlag( uint8 Transceiver );
void           bsw_cantrcv_st_MainFunction( void );
void           bsw_cantrcv_st_MainFunctionDiag( void );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CANTRCV_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/06/04                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
