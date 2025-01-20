/* DIO-r04-303 */
/************************************************************************************************/
/*																								*/
/*		DIO Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef DIO_H
#define DIO_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Dio_Cfg.h"
#include "Dio_Symbols.h"

/*==============================================================================================*/
/* data types / structs / unions / macros														*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* AR Type Definitions																			*/
/*----------------------------------------------------------------------------------------------*/
typedef uint16 Dio_ChannelType;
typedef uint8  Dio_PortType;
typedef uint8  Dio_LevelType;
typedef uint16 Dio_PortLevelType;
typedef struct {
	Dio_PortLevelType		mask;			/* a mask indicating the channel group				*/
	uint8					offset;			/* Offset value from LSB to mask					*/
	Dio_PortType			port;			/* port ID											*/
} Dio_ChannelGroupType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define DIO_START_SEC_CODE_GLOBAL
#include "Dio_MemMap.h"
/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name		:	Dio_ReadChannel															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	ChannelId - ID of DIO channel											*/
/* Return value		:	Dio_LevelType -															*/
/*							STD_HIGH/STD_LOW depending on the physical level of the Pin			*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel( VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId );

/************************************************************************************************/
/* Service name		:	Dio_WriteChannel														*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	ChannelId - ID of DIO channel											*/
/*						Level	  - Value to be written											*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannel( VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId, VAR(Dio_LevelType, DIO_VAR_INIT) Level );

/************************************************************************************************/
/* Service name		:	Dio_ReadPort															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	PortId - ID of DIO Port													*/
/* Return value		:	Dio_PortLevelType - Level of all channels of that port					*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort( VAR(Dio_PortType, DIO_VAR_INIT) PortId );

/************************************************************************************************/
/* Service name		:	Dio_ReadChannelGroup													*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	Dio_ChannelGroupType - Pointer to ChannelGroup							*/
/* Return value		:	Dio_PortLevelType - Level of a subset of the adjoining bits of a port	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup( P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONST) ChannelGroupIdPtr );

/************************************************************************************************/
/* Service name		:	Dio_WritePort															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	PortId - ID of DIO Port													*/
/*						Level  - Value to be written											*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WritePort( VAR(Dio_PortType, DIO_VAR_INIT) PortId, VAR(Dio_PortLevelType, DIO_VAR_INIT) Level );

/************************************************************************************************/
/* Service name		:	Dio_WriteChannelGroup													*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	Dio_ChannelGroupType - Pointer to ChannelGroup							*/
/*						Level				 - Value to be written								*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannelGroup( P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONST) ChannelGroupIdPtr, VAR(Dio_PortLevelType, DIO_VAR_INIT) Level );

#if ( DIO_FLIP_CHANNEL_API == STD_ON )
/************************************************************************************************/
/* Service name		:	Dio_FlipChannel															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	ChannelId - ID of DIO channel											*/
/* Return value		:	Dio_LevelType -															*/
/*							STD_HIGH/STD_LOW depending on the physical level of the Pin			*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_FlipChannel( VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId );
#endif /* DIO_FLIP_CHANNEL_API == STD_ON */

#define DIO_STOP_SEC_CODE_GLOBAL
#include "Dio_MemMap.h"

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#define DIO_START_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

extern CONST(Dio_ChannelGroupType, DIO_CONST) cstDio_ChannelGroupArray[DIO_CFG_CH_GRP_ARRAY_SIZE];

#define DIO_STOP_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

#endif /* DIO_H	 */
/*-- End Of File -------------------------------------------------------------------------------*/
