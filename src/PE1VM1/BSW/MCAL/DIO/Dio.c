/* DIO-r04-303 */
/************************************************************************************************/
/*																								*/
/*		DIO Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Mcal_SpalCmn.h"

#include "Dio.h"
#include "Reg_Port.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* defines																						*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_DIRECTION_OUTPUT	((uint16)0x0000U)	/* A value that indicates the output mode	*/
#define DIO_SHIFT_16			(16)				/* 16-bit shift value						*/

/*----------------------------------------------------------------------------------------------*/
/* enums																						*/
/*----------------------------------------------------------------------------------------------*/
/* port type */
typedef enum {
	DIO_PORT_TYPE_NORMAL = 0,				/* Normal Port										*/
	DIO_PORT_TYPE_ANALOG = 1,				/* Analog Port										*/
	DIO_PORT_TYPE_JTAG	 = 2				/* Jtag Port										*/
} Dio_PortGroupType;

/*----------------------------------------------------------------------------------------------*/
/* structs																						*/
/*----------------------------------------------------------------------------------------------*/
/* Channel Information */
typedef struct {
	uint8				u1PinPos;			/* pin position										*/
	Dio_PortType		u1PortId;			/* equal to index of cstPortInfoArray				*/
} Dio_ChannelInfoType;

/* Port Information */
typedef struct {
	Dio_PortGroupType	enPortType;			/* Normal or Analog or Jtag							*/
	uint32				u4PweWriteValue;	/* A value that makes port group writable			*/
	uint8				u1PortGroupNo;		/* equal to index of register structure array		*/
} Dio_PortInfoType;

#if ( DIO_CFG_PROTECTION_CONTROL == STD_ON )
/************************************************************************************************/
/*	Macro name		:	Calling function to disable protection									*/
/*	Parameters (in)	:	x - Function parameter													*/
/*	Return value	:	Calling function														*/
/*	Limitation		:	none																	*/
/************************************************************************************************/
#define DIO_FUNC_DISABLE_PROTECTION( x )		Dio_DisableProtection( x )
/************************************************************************************************/
/*	Macro name		:	Calling function to enable protection									*/
/*	Parameters (in)	:	x - Function parameter													*/
/*	Return value	:	Calling function														*/
/*	Limitation		:	none																	*/
/************************************************************************************************/
#define DIO_FUNC_ENABLE_PROTECTION( x )			Dio_EnableProtection( x )
#else
#define DIO_FUNC_DISABLE_PROTECTION( x )
#define DIO_FUNC_ENABLE_PROTECTION( x )
#endif /* DIO_CFG_PROTECTION_CONTROL == STD_ON */

/*==============================================================================================*/
/* prototypes																					*/
/*==============================================================================================*/
#define DIO_START_SEC_CODE_GLOBAL
#include "Dio_MemMap.h"

#if ( DIO_CFG_PROTECTION_CONTROL == STD_ON )
static FUNC(void, DIO_CODE) Dio_DisableProtection( CONST(uint32, DIO_CONST) t_cu4PweWriteValue );
static FUNC(void, DIO_CODE) Dio_EnableProtection( CONST(uint32, DIO_CONST) t_cu4PweWriteValue );
#endif /* DIO_CFG_PROTECTION_CONTROL == STD_ON */

#define DIO_STOP_SEC_CODE_GLOBAL
#include "Dio_MemMap.h"

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
#define DIO_START_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

static CONST(Dio_ChannelInfoType, DIO_CONST) s_cstDio_ChannelInfoArray[DIO_ASSIGN_ID_CH_MAX] = {
	{0U,  DIO_ID_PORT0},				/* PORT0 CH0	*/
	{1U,  DIO_ID_PORT0},				/* PORT0 CH1	*/
	{2U,  DIO_ID_PORT0},				/* PORT0 CH2	*/
	{3U,  DIO_ID_PORT0},				/* PORT0 CH3	*/
	{4U,  DIO_ID_PORT0},				/* PORT0 CH4	*/
	{5U,  DIO_ID_PORT0},				/* PORT0 CH5	*/
	{6U,  DIO_ID_PORT0},				/* PORT0 CH6	*/
	{7U,  DIO_ID_PORT0},				/* PORT0 CH7	*/
	{8U,  DIO_ID_PORT0},				/* PORT0 CH8	*/
	{9U,  DIO_ID_PORT0},				/* PORT0 CH9	*/
	{10U, DIO_ID_PORT0},				/* PORT0 CH10	*/
	{11U, DIO_ID_PORT0},				/* PORT0 CH11	*/
	{12U, DIO_ID_PORT0},				/* PORT0 CH12	*/
	{0U,  DIO_ID_PORT1},				/* PORT1 CH0	*/
	{1U,  DIO_ID_PORT1},				/* PORT1 CH1	*/
	{2U,  DIO_ID_PORT1},				/* PORT1 CH2	*/
	{3U,  DIO_ID_PORT1},				/* PORT1 CH3	*/
	{4U,  DIO_ID_PORT1},				/* PORT1 CH4	*/
	{5U,  DIO_ID_PORT1},				/* PORT1 CH5	*/
	{6U,  DIO_ID_PORT1},				/* PORT1 CH6	*/
	{7U,  DIO_ID_PORT1},				/* PORT1 CH7	*/
	{8U,  DIO_ID_PORT1},				/* PORT1 CH8	*/
	{9U,  DIO_ID_PORT1},				/* PORT1 CH9	*/
	{10U, DIO_ID_PORT1},				/* PORT1 CH10	*/
	{11U, DIO_ID_PORT1},				/* PORT1 CH11	*/
	{12U, DIO_ID_PORT1},				/* PORT1 CH12	*/
	{13U, DIO_ID_PORT1},				/* PORT1 CH13	*/
	{14U, DIO_ID_PORT1},				/* PORT1 CH14	*/
	{15U, DIO_ID_PORT1},				/* PORT1 CH15	*/
	{0U,  DIO_ID_PORT2},				/* PORT2 CH0	*/
	{1U,  DIO_ID_PORT2},				/* PORT2 CH1	*/
	{2U,  DIO_ID_PORT2},				/* PORT2 CH2	*/
	{3U,  DIO_ID_PORT2},				/* PORT2 CH3	*/
	{4U,  DIO_ID_PORT2},				/* PORT2 CH4	*/
	{5U,  DIO_ID_PORT2},				/* PORT2 CH5	*/
	{6U,  DIO_ID_PORT2},				/* PORT2 CH6	*/
	{7U,  DIO_ID_PORT2},				/* PORT2 CH7	*/
	{8U,  DIO_ID_PORT2},				/* PORT2 CH8	*/
	{9U,  DIO_ID_PORT2},				/* PORT2 CH9	*/
	{10U, DIO_ID_PORT2},				/* PORT2 CH10	*/
	{11U, DIO_ID_PORT2},				/* PORT2 CH11	*/
	{12U, DIO_ID_PORT2},				/* PORT2 CH12	*/
	{13U, DIO_ID_PORT2},				/* PORT2 CH13	*/
	{14U, DIO_ID_PORT2},				/* PORT2 CH14	*/
	{15U, DIO_ID_PORT2},				/* PORT2 CH15	*/
	{0U,  DIO_ID_PORT3},				/* PORT3 CH0	*/
	{1U,  DIO_ID_PORT3},				/* PORT3 CH1	*/
	{2U,  DIO_ID_PORT3},				/* PORT3 CH2	*/
	{3U,  DIO_ID_PORT3},				/* PORT3 CH3	*/
	{4U,  DIO_ID_PORT3},				/* PORT3 CH4	*/
	{5U,  DIO_ID_PORT3},				/* PORT3 CH5	*/
	{6U,  DIO_ID_PORT3},				/* PORT3 CH6	*/
	{7U,  DIO_ID_PORT3},				/* PORT3 CH7	*/
	{8U,  DIO_ID_PORT3},				/* PORT3 CH8	*/
	{9U,  DIO_ID_PORT3},				/* PORT3 CH9	*/
	{10U, DIO_ID_PORT3},				/* PORT3 CH10	*/
	{11U, DIO_ID_PORT3},				/* PORT3 CH11	*/
	{12U, DIO_ID_PORT3},				/* PORT3 CH12	*/
	{13U, DIO_ID_PORT3},				/* PORT3 CH13	*/
	{14U, DIO_ID_PORT3},				/* PORT3 CH14	*/
	{15U, DIO_ID_PORT3},				/* PORT3 CH15	*/
	{0U,  DIO_ID_PORT4},				/* PORT4 CH0	*/
	{1U,  DIO_ID_PORT4},				/* PORT4 CH1	*/
	{2U,  DIO_ID_PORT4},				/* PORT4 CH2	*/
	{3U,  DIO_ID_PORT4},				/* PORT4 CH3	*/
	{4U,  DIO_ID_PORT4},				/* PORT4 CH4	*/
	{5U,  DIO_ID_PORT4},				/* PORT4 CH5	*/
	{6U,  DIO_ID_PORT4},				/* PORT4 CH6	*/
	{7U,  DIO_ID_PORT4},				/* PORT4 CH7	*/
	{8U,  DIO_ID_PORT4},				/* PORT4 CH8	*/
	{9U,  DIO_ID_PORT4},				/* PORT4 CH9	*/
	{10U, DIO_ID_PORT4},				/* PORT4 CH10	*/
	{11U, DIO_ID_PORT4},				/* PORT4 CH11	*/
	{12U, DIO_ID_PORT4},				/* PORT4 CH12	*/
	{13U, DIO_ID_PORT4},				/* PORT4 CH13	*/
	{14U, DIO_ID_PORT4},				/* PORT4 CH14	*/
	{15U, DIO_ID_PORT4},				/* PORT4 CH15	*/
	{2U,  DIO_ID_PORT5},				/* PORT5 CH2	*/
	{3U,  DIO_ID_PORT5},				/* PORT5 CH3	*/
	{4U,  DIO_ID_PORT5},				/* PORT5 CH4	*/
	{6U,  DIO_ID_PORT5},				/* PORT5 CH6	*/
	{0U,  DIO_ID_PORT6},				/* PORT6 CH0	*/
	{2U,  DIO_ID_PORT6},				/* PORT6 CH2	*/
	{3U,  DIO_ID_PORT6},				/* PORT6 CH3	*/
	{4U,  DIO_ID_PORT6},				/* PORT6 CH4	*/
	{5U,  DIO_ID_PORT6},				/* PORT6 CH5	*/
	{6U,  DIO_ID_PORT6},				/* PORT6 CH6	*/
	{7U,  DIO_ID_PORT6},				/* PORT6 CH7	*/
	{8U,  DIO_ID_PORT6},				/* PORT6 CH8	*/
	{9U,  DIO_ID_PORT6},				/* PORT6 CH9	*/
	{10U, DIO_ID_PORT6},				/* PORT6 CH10	*/
	{11U, DIO_ID_PORT6},				/* PORT6 CH11	*/
	{12U, DIO_ID_PORT6},				/* PORT6 CH12	*/
	{13U, DIO_ID_PORT6},				/* PORT6 CH13	*/
	{14U, DIO_ID_PORT6},				/* PORT6 CH14	*/
	{15U, DIO_ID_PORT6},				/* PORT6 CH15	*/
	{0U,  DIO_ID_PORT8},				/* PORT8 CH0	*/
	{1U,  DIO_ID_PORT8},				/* PORT8 CH1	*/
	{2U,  DIO_ID_PORT8},				/* PORT8 CH2	*/
	{3U,  DIO_ID_PORT8},				/* PORT8 CH3	*/
	{4U,  DIO_ID_PORT8},				/* PORT8 CH4	*/
	{5U,  DIO_ID_PORT8},				/* PORT8 CH5	*/
	{6U,  DIO_ID_PORT8},				/* PORT8 CH6	*/
	{7U,  DIO_ID_PORT8},				/* PORT8 CH7	*/
	{8U,  DIO_ID_PORT8},				/* PORT8 CH8	*/
	{9U,  DIO_ID_PORT8},				/* PORT8 CH9	*/
	{10U, DIO_ID_PORT8},				/* PORT8 CH10	*/
	{0U,  DIO_ID_PORT9},				/* PORT9 CH0	*/
	{1U,  DIO_ID_PORT9},				/* PORT9 CH1	*/
	{2U,  DIO_ID_PORT9},				/* PORT9 CH2	*/
	{3U,  DIO_ID_PORT9},				/* PORT9 CH3	*/
	{4U,  DIO_ID_PORT9},				/* PORT9 CH4	*/
	{5U,  DIO_ID_PORT9},				/* PORT9 CH5	*/
	{6U,  DIO_ID_PORT9},				/* PORT9 CH6	*/
	{7U,  DIO_ID_PORT9},				/* PORT9 CH7	*/
	{8U,  DIO_ID_PORT9},				/* PORT9 CH8	*/
	{0U,  DIO_ID_PORT10},				/* PORT10 CH0	*/
	{1U,  DIO_ID_PORT10},				/* PORT10 CH1	*/
	{2U,  DIO_ID_PORT10},				/* PORT10 CH2	*/
	{3U,  DIO_ID_PORT10},				/* PORT10 CH3	*/
	{4U,  DIO_ID_PORT10},				/* PORT10 CH4	*/
	{5U,  DIO_ID_PORT10},				/* PORT10 CH5	*/
	{6U,  DIO_ID_PORT10},				/* PORT10 CH6	*/
	{7U,  DIO_ID_PORT10},				/* PORT10 CH7	*/
	{8U,  DIO_ID_PORT10},				/* PORT10 CH8	*/
	{9U,  DIO_ID_PORT10},				/* PORT10 CH9	*/
	{10U, DIO_ID_PORT10},				/* PORT10 CH10	*/
	{11U, DIO_ID_PORT10},				/* PORT10 CH11	*/
	{12U, DIO_ID_PORT10},				/* PORT10 CH12	*/
	{13U, DIO_ID_PORT10},				/* PORT10 CH13	*/
	{14U, DIO_ID_PORT10},				/* PORT10 CH14	*/
	{0U,  DIO_ID_PORT11},				/* PORT11 CH0	*/
	{1U,  DIO_ID_PORT11},				/* PORT11 CH1	*/
	{2U,  DIO_ID_PORT11},				/* PORT11 CH2	*/
	{3U,  DIO_ID_PORT11},				/* PORT11 CH3	*/
	{4U,  DIO_ID_PORT11},				/* PORT11 CH4	*/
	{5U,  DIO_ID_PORT11},				/* PORT11 CH5	*/
	{6U,  DIO_ID_PORT11},				/* PORT11 CH6	*/
	{7U,  DIO_ID_PORT11},				/* PORT11 CH7	*/
	{8U,  DIO_ID_PORT11},				/* PORT11 CH8	*/
	{9U,  DIO_ID_PORT11},				/* PORT11 CH9	*/
	{10U, DIO_ID_PORT11},				/* PORT11 CH10	*/
	{11U, DIO_ID_PORT11},				/* PORT11 CH11	*/
	{12U, DIO_ID_PORT11},				/* PORT11 CH12	*/
	{13U, DIO_ID_PORT11},				/* PORT11 CH13	*/
	{14U, DIO_ID_PORT11},				/* PORT11 CH14	*/
	{15U, DIO_ID_PORT11},				/* PORT11 CH15	*/
	{0U,  DIO_ID_PORT12},				/* PORT12 CH0	*/
	{1U,  DIO_ID_PORT12},				/* PORT12 CH1	*/
	{2U,  DIO_ID_PORT12},				/* PORT12 CH2	*/
	{3U,  DIO_ID_PORT12},				/* PORT12 CH3	*/
	{4U,  DIO_ID_PORT12},				/* PORT12 CH4	*/
	{5U,  DIO_ID_PORT12},				/* PORT12 CH5	*/
	{0U,  DIO_ID_PORT17},				/* PORT17 CH0	*/
	{1U,  DIO_ID_PORT17},				/* PORT17 CH1	*/
	{2U,  DIO_ID_PORT17},				/* PORT17 CH2	*/
	{3U,  DIO_ID_PORT17},				/* PORT17 CH3	*/
	{4U,  DIO_ID_PORT17},				/* PORT17 CH4	*/
	{5U,  DIO_ID_PORT17},				/* PORT17 CH5	*/
	{6U,  DIO_ID_PORT17},				/* PORT17 CH6	*/
	{0U,  DIO_ID_PORT18},				/* PORT18 CH0	*/
	{1U,  DIO_ID_PORT18},				/* PORT18 CH1	*/
	{2U,  DIO_ID_PORT18},				/* PORT18 CH2	*/
	{3U,  DIO_ID_PORT18},				/* PORT18 CH3	*/
	{4U,  DIO_ID_PORT18},				/* PORT18 CH4	*/
	{5U,  DIO_ID_PORT18},				/* PORT18 CH5	*/
	{6U,  DIO_ID_PORT18},				/* PORT18 CH6	*/
	{7U,  DIO_ID_PORT18},				/* PORT18 CH7	*/
	{8U,  DIO_ID_PORT18},				/* PORT18 CH8	*/
	{9U,  DIO_ID_PORT18},				/* PORT18 CH9	*/
	{10U, DIO_ID_PORT18},				/* PORT18 CH10	*/
	{11U, DIO_ID_PORT18},				/* PORT18 CH11	*/
	{12U, DIO_ID_PORT18},				/* PORT18 CH12	*/
	{13U, DIO_ID_PORT18},				/* PORT18 CH13	*/
	{14U, DIO_ID_PORT18},				/* PORT18 CH14	*/
	{15U, DIO_ID_PORT18},				/* PORT18 CH15	*/
	{0U,  DIO_ID_PORT19},				/* PORT19 CH0	*/
	{1U,  DIO_ID_PORT19},				/* PORT19 CH1	*/
	{2U,  DIO_ID_PORT19},				/* PORT19 CH2	*/
	{3U,  DIO_ID_PORT19},				/* PORT19 CH3	*/
	{4U,  DIO_ID_PORT19},				/* PORT19 CH4	*/
	{5U,  DIO_ID_PORT19},				/* PORT19 CH5	*/
	{0U,  DIO_ID_PORT20},				/* PORT20 CH0	*/
	{1U,  DIO_ID_PORT20},				/* PORT20 CH1	*/
	{2U,  DIO_ID_PORT20},				/* PORT20 CH2	*/
	{3U,  DIO_ID_PORT20},				/* PORT20 CH3	*/
	{4U,  DIO_ID_PORT20},				/* PORT20 CH4	*/
	{5U,  DIO_ID_PORT20},				/* PORT20 CH5	*/
	{6U,  DIO_ID_PORT20},				/* PORT20 CH6	*/
	{7U,  DIO_ID_PORT20},				/* PORT20 CH7	*/
	{8U,  DIO_ID_PORT20},				/* PORT20 CH8	*/
	{9U,  DIO_ID_PORT20},				/* PORT20 CH9	*/
	{10U, DIO_ID_PORT20},				/* PORT20 CH10	*/
	{12U, DIO_ID_PORT20},				/* PORT20 CH12	*/
	{13U, DIO_ID_PORT20},				/* PORT20 CH13	*/
	{14U, DIO_ID_PORT20},				/* PORT20 CH14	*/
	{15U, DIO_ID_PORT20},				/* PORT20 CH15	*/
	{0U,  DIO_ID_PORT21},				/* PORT21 CH0	*/
	{1U,  DIO_ID_PORT21},				/* PORT21 CH1	*/
	{2U,  DIO_ID_PORT21},				/* PORT21 CH2	*/
	{3U,  DIO_ID_PORT21},				/* PORT21 CH3	*/
	{4U,  DIO_ID_PORT21},				/* PORT21 CH4	*/
	{5U,  DIO_ID_PORT21},				/* PORT21 CH5	*/
	{6U,  DIO_ID_PORT21},				/* PORT21 CH6	*/
	{7U,  DIO_ID_PORT21},				/* PORT21 CH7	*/
	{12U, DIO_ID_PORT21},				/* PORT21 CH12	*/
	{13U, DIO_ID_PORT21},				/* PORT21 CH13	*/
	{0U,  DIO_ID_PORT22},				/* PORT22 CH0	*/
	{1U,  DIO_ID_PORT22},				/* PORT22 CH1	*/
	{2U,  DIO_ID_PORT22},				/* PORT22 CH2	*/
	{3U,  DIO_ID_PORT22},				/* PORT22 CH3	*/
	{4U,  DIO_ID_PORT22},				/* PORT22 CH4	*/
	{0U,  DIO_ID_PORT23},				/* PORT23 CH0	*/
	{1U,  DIO_ID_PORT23},				/* PORT23 CH1	*/
	{2U,  DIO_ID_PORT23},				/* PORT23 CH2	*/
	{3U,  DIO_ID_PORT23},				/* PORT23 CH3	*/
	{4U,  DIO_ID_PORT23},				/* PORT23 CH4	*/
	{5U,  DIO_ID_PORT23},				/* PORT23 CH5	*/
	{6U,  DIO_ID_PORT23},				/* PORT23 CH6	*/
	{7U,  DIO_ID_PORT23},				/* PORT23 CH7	*/
	{8U,  DIO_ID_PORT23},				/* PORT23 CH8	*/
	{9U,  DIO_ID_PORT23},				/* PORT23 CH9	*/
	{10U, DIO_ID_PORT23},				/* PORT23 CH10	*/
	{11U, DIO_ID_PORT23},				/* PORT23 CH11	*/
	{12U, DIO_ID_PORT23},				/* PORT23 CH12	*/
	{13U, DIO_ID_PORT23},				/* PORT23 CH13	*/
	{4U,  DIO_ID_PORT24},				/* PORT24 CH4	*/
	{5U,  DIO_ID_PORT24},				/* PORT24 CH5	*/
	{6U,  DIO_ID_PORT24},				/* PORT24 CH6	*/
	{7U,  DIO_ID_PORT24},				/* PORT24 CH7	*/
	{8U,  DIO_ID_PORT24},				/* PORT24 CH8	*/
	{9U,  DIO_ID_PORT24},				/* PORT24 CH9	*/
	{10U, DIO_ID_PORT24},				/* PORT24 CH10	*/
	{11U, DIO_ID_PORT24},				/* PORT24 CH11	*/
	{12U, DIO_ID_PORT24},				/* PORT24 CH12	*/
	{13U, DIO_ID_PORT24},				/* PORT24 CH13	*/
	{0U,  DIO_ID_APORT0},				/* APORT0 CH0	*/
	{1U,  DIO_ID_APORT0},				/* APORT0 CH1	*/
	{2U,  DIO_ID_APORT0},				/* APORT0 CH2	*/
	{3U,  DIO_ID_APORT0},				/* APORT0 CH3	*/
	{4U,  DIO_ID_APORT0},				/* APORT0 CH4	*/
	{5U,  DIO_ID_APORT0},				/* APORT0 CH5	*/
	{6U,  DIO_ID_APORT0},				/* APORT0 CH6	*/
	{7U,  DIO_ID_APORT0},				/* APORT0 CH7	*/
	{8U,  DIO_ID_APORT0},				/* APORT0 CH8	*/
	{9U,  DIO_ID_APORT0},				/* APORT0 CH9	*/
	{10U, DIO_ID_APORT0},				/* APORT0 CH10	*/
	{11U, DIO_ID_APORT0},				/* APORT0 CH11	*/
	{12U, DIO_ID_APORT0},				/* APORT0 CH12	*/
	{13U, DIO_ID_APORT0},				/* APORT0 CH13	*/
	{14U, DIO_ID_APORT0},				/* APORT0 CH14	*/
	{15U, DIO_ID_APORT0},				/* APORT0 CH15	*/
	{0U,  DIO_ID_APORT1},				/* APORT1 CH0	*/
	{1U,  DIO_ID_APORT1},				/* APORT1 CH1	*/
	{2U,  DIO_ID_APORT1},				/* APORT1 CH2	*/
	{3U,  DIO_ID_APORT1},				/* APORT1 CH3	*/
	{0U,  DIO_ID_APORT2},				/* APORT2 CH0	*/
	{1U,  DIO_ID_APORT2},				/* APORT2 CH1	*/
	{2U,  DIO_ID_APORT2},				/* APORT2 CH2	*/
	{3U,  DIO_ID_APORT2},				/* APORT2 CH3	*/
	{4U,  DIO_ID_APORT2},				/* APORT2 CH4	*/
	{5U,  DIO_ID_APORT2},				/* APORT2 CH5	*/
	{6U,  DIO_ID_APORT2},				/* APORT2 CH6	*/
	{7U,  DIO_ID_APORT2},				/* APORT2 CH7	*/
	{8U,  DIO_ID_APORT2},				/* APORT2 CH8	*/
	{9U,  DIO_ID_APORT2},				/* APORT2 CH9	*/
	{10U, DIO_ID_APORT2},				/* APORT2 CH10	*/
	{11U, DIO_ID_APORT2},				/* APORT2 CH11	*/
	{12U, DIO_ID_APORT2},				/* APORT2 CH12	*/
	{13U, DIO_ID_APORT2},				/* APORT2 CH13	*/
	{14U, DIO_ID_APORT2},				/* APORT2 CH14	*/
	{15U, DIO_ID_APORT2},				/* APORT2 CH15	*/
	{0U,  DIO_ID_APORT3},				/* APORT3 CH0	*/
	{1U,  DIO_ID_APORT3},				/* APORT3 CH1	*/
	{2U,  DIO_ID_APORT3},				/* APORT3 CH2	*/
	{3U,  DIO_ID_APORT3},				/* APORT3 CH3	*/
	{0U,  DIO_ID_APORT4},				/* APORT4 CH0	*/
	{1U,  DIO_ID_APORT4},				/* APORT4 CH1	*/
	{2U,  DIO_ID_APORT4},				/* APORT4 CH2	*/
	{3U,  DIO_ID_APORT4},				/* APORT4 CH3	*/
	{4U,  DIO_ID_APORT4},				/* APORT4 CH4	*/
	{5U,  DIO_ID_APORT4},				/* APORT4 CH5	*/
	{6U,  DIO_ID_APORT4},				/* APORT4 CH6	*/
	{7U,  DIO_ID_APORT4},				/* APORT4 CH7	*/
	{8U,  DIO_ID_APORT4},				/* APORT4 CH8	*/
	{9U,  DIO_ID_APORT4},				/* APORT4 CH9	*/
	{10U, DIO_ID_APORT4},				/* APORT4 CH10	*/
	{11U, DIO_ID_APORT4},				/* APORT4 CH11	*/
	{12U, DIO_ID_APORT4},				/* APORT4 CH12	*/
	{13U, DIO_ID_APORT4},				/* APORT4 CH13	*/
	{14U, DIO_ID_APORT4},				/* APORT4 CH14	*/
	{15U, DIO_ID_APORT4},				/* APORT4 CH15	*/
	{0U,  DIO_ID_APORT5},				/* APORT5 CH0	*/
	{1U,  DIO_ID_APORT5},				/* APORT5 CH1	*/
	{2U,  DIO_ID_APORT5},				/* APORT5 CH2	*/
	{3U,  DIO_ID_APORT5},				/* APORT5 CH3	*/
	{0U,  DIO_ID_JPORT0},				/* JPORT0 CH0	*/
	{1U,  DIO_ID_JPORT0},				/* JPORT0 CH1	*/
	{2U,  DIO_ID_JPORT0},				/* JPORT0 CH2	*/
	{3U,  DIO_ID_JPORT0},				/* JPORT0 CH3	*/
	{5U,  DIO_ID_JPORT0}				/* JPORT0 CH5	*/
};

static CONST(Dio_PortInfoType, DIO_CONST) s_cstDio_PortInfoArray[DIO_ASSIGN_ID_PORT_MAX] = {
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 0U},		/* PORT0		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 1U},		/* PORT1		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_P2,	2U},		/* PORT2		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 3U},		/* PORT3		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 4U},		/* PORT4		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 5U},		/* PORT5		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_P6,	6U},		/* PORT6		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 8U},		/* PORT8		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 9U},		/* PORT9		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 10U},		/* PORT10		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 11U},		/* PORT11		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 12U},		/* PORT12		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 17U},		/* PORT17		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 18U},		/* PORT18		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 19U},		/* PORT19		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 20U},		/* PORT20		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 21U},		/* PORT21		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 22U},		/* PORT22		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 23U},		/* PORT23		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 24U},		/* PORT24		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 0U},		/* APORT0		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 1U},		/* APORT1		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 2U},		/* APORT2		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 3U},		/* APORT3		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 4U},		/* APORT4		*/
	{DIO_PORT_TYPE_ANALOG, PORT_PWE_TARGET_NOT, 5U},		/* APORT5		*/
	{DIO_PORT_TYPE_JTAG,   PORT_PWE_TARGET_NOT, 0U}			/* JPORT0		*/
};

#else

static CONST(Dio_ChannelInfoType, DIO_CONST) s_cstDio_ChannelInfoArray[DIO_ASSIGN_ID_CH_MAX] = {
	{0U,  DIO_ID_PORT0},				/* PORT0 CH0	*/
	{1U,  DIO_ID_PORT0},				/* PORT0 CH1	*/
	{2U,  DIO_ID_PORT0},				/* PORT0 CH2	*/
	{3U,  DIO_ID_PORT0},				/* PORT0 CH3	*/
	{4U,  DIO_ID_PORT0},				/* PORT0 CH4	*/
	{5U,  DIO_ID_PORT0},				/* PORT0 CH5	*/
	{6U,  DIO_ID_PORT0},				/* PORT0 CH6	*/
	{7U,  DIO_ID_PORT0},				/* PORT0 CH7	*/
	{0U,  DIO_ID_PORT2},				/* PORT2 CH0	*/
	{1U,  DIO_ID_PORT2},				/* PORT2 CH1	*/
	{2U,  DIO_ID_PORT2},				/* PORT2 CH2	*/
	{3U,  DIO_ID_PORT2},				/* PORT2 CH3	*/
	{4U,  DIO_ID_PORT2},				/* PORT2 CH4	*/
	{5U,  DIO_ID_PORT2},				/* PORT2 CH5	*/
	{6U,  DIO_ID_PORT2},				/* PORT2 CH6	*/
	{7U,  DIO_ID_PORT2},				/* PORT2 CH7	*/
	{8U,  DIO_ID_PORT2},				/* PORT2 CH8	*/
	{9U,  DIO_ID_PORT2},				/* PORT2 CH9	*/
	{10U, DIO_ID_PORT2},				/* PORT2 CH10	*/
	{0U,  DIO_ID_PORT10},				/* PORT10 CH0	*/
	{1U,  DIO_ID_PORT10},				/* PORT10 CH1	*/
	{2U,  DIO_ID_PORT10},				/* PORT10 CH2	*/
	{3U,  DIO_ID_PORT10},				/* PORT10 CH3	*/
	{4U,  DIO_ID_PORT10},				/* PORT10 CH4	*/
	{5U,  DIO_ID_PORT10},				/* PORT10 CH5	*/
	{6U,  DIO_ID_PORT10},				/* PORT10 CH6	*/
	{7U,  DIO_ID_PORT10},				/* PORT10 CH7	*/
	{8U,  DIO_ID_PORT10},				/* PORT10 CH8	*/
	{0U,  DIO_ID_PORT11},				/* PORT11 CH0	*/
	{1U,  DIO_ID_PORT11},				/* PORT11 CH1	*/
	{2U,  DIO_ID_PORT11},				/* PORT11 CH2	*/
	{3U,  DIO_ID_PORT11},				/* PORT11 CH3	*/
	{4U,  DIO_ID_PORT11},				/* PORT11 CH4	*/
	{5U,  DIO_ID_PORT11},				/* PORT11 CH5	*/
	{6U,  DIO_ID_PORT11},				/* PORT11 CH6	*/
	{7U,  DIO_ID_PORT11},				/* PORT11 CH7	*/
	{8U,  DIO_ID_PORT11},				/* PORT11 CH8	*/
	{9U,  DIO_ID_PORT11},				/* PORT11 CH9	*/
	{10U, DIO_ID_PORT11},				/* PORT11 CH10	*/
	{0U,  DIO_ID_PORT12},				/* PORT12 CH0	*/
	{1U,  DIO_ID_PORT12},				/* PORT12 CH1	*/
	{2U,  DIO_ID_PORT12},				/* PORT12 CH2	*/
	{3U,  DIO_ID_PORT12},				/* PORT12 CH3	*/
	{4U,  DIO_ID_PORT12},				/* PORT12 CH4	*/
	{5U,  DIO_ID_PORT12},				/* PORT12 CH5	*/
	{6U,  DIO_ID_PORT12},				/* PORT12 CH6	*/
	{7U,  DIO_ID_PORT12},				/* PORT12 CH7	*/
	{8U,  DIO_ID_PORT12},				/* PORT12 CH8	*/
	{9U,  DIO_ID_PORT12},				/* PORT12 CH9	*/
	{0U,  DIO_ID_PORT13},				/* PORT13 CH0	*/
	{1U,  DIO_ID_PORT13},				/* PORT13 CH1	*/
	{2U,  DIO_ID_PORT13},				/* PORT13 CH2	*/
	{3U,  DIO_ID_PORT13},				/* PORT13 CH3	*/
	{0U,  DIO_ID_PORT14},				/* PORT14 CH0	*/
	{1U,  DIO_ID_PORT14},				/* PORT14 CH1	*/
	{2U,  DIO_ID_PORT14},				/* PORT14 CH2	*/
	{3U,  DIO_ID_PORT14},				/* PORT14 CH3	*/
	{4U,  DIO_ID_PORT14},				/* PORT14 CH4	*/
	{5U,  DIO_ID_PORT14},				/* PORT14 CH5	*/
	{0U,  DIO_ID_PORT20},				/* PORT20 CH0	*/
	{1U,  DIO_ID_PORT20},				/* PORT20 CH1	*/
	{2U,  DIO_ID_PORT20},				/* PORT20 CH2	*/
	{3U,  DIO_ID_PORT20},				/* PORT20 CH3	*/
	{4U,  DIO_ID_PORT20},				/* PORT20 CH4	*/
	{5U,  DIO_ID_PORT20},				/* PORT20 CH5	*/
	{6U,  DIO_ID_PORT20},				/* PORT20 CH6	*/
	{7U,  DIO_ID_PORT20},				/* PORT20 CH7	*/
	{2U,  DIO_ID_PORT21},				/* PORT21 CH2	*/
	{3U,  DIO_ID_PORT21},				/* PORT21 CH3	*/
	{4U,  DIO_ID_PORT21},				/* PORT21 CH4	*/
	{5U,  DIO_ID_PORT21},				/* PORT21 CH5	*/
	{0U,  DIO_ID_PORT22},				/* PORT22 CH0	*/
	{1U,  DIO_ID_PORT22},				/* PORT22 CH1	*/
	{2U,  DIO_ID_PORT22},				/* PORT22 CH2	*/
	{3U,  DIO_ID_PORT22},				/* PORT22 CH3	*/
	{4U,  DIO_ID_PORT22},				/* PORT22 CH4	*/
	{5U,  DIO_ID_PORT22},				/* PORT22 CH5	*/
	{6U,  DIO_ID_PORT22},				/* PORT22 CH6	*/
	{7U,  DIO_ID_PORT22},				/* PORT22 CH7	*/
	{8U,  DIO_ID_PORT22},				/* PORT22 CH8	*/
	{9U,  DIO_ID_PORT22},				/* PORT22 CH9	*/
	{10U, DIO_ID_PORT22},				/* PORT22 CH10	*/
	{11U, DIO_ID_PORT22},				/* PORT22 CH11	*/
	{12U, DIO_ID_PORT22},				/* PORT22 CH12	*/
	{13U, DIO_ID_PORT22},				/* PORT22 CH13	*/
	{0U,  DIO_ID_PORT23},				/* PORT23 CH0	*/
	{1U,  DIO_ID_PORT23},				/* PORT23 CH1	*/
	{2U,  DIO_ID_PORT23},				/* PORT23 CH2	*/
	{3U,  DIO_ID_PORT23},				/* PORT23 CH3	*/
	{4U,  DIO_ID_PORT23},				/* PORT23 CH4	*/
	{5U,  DIO_ID_PORT23},				/* PORT23 CH5	*/
	{6U,  DIO_ID_PORT23},				/* PORT23 CH6	*/
	{7U,  DIO_ID_PORT23},				/* PORT23 CH7	*/
	{2U,  DIO_ID_PORT25},				/* PORT25 CH2	*/
	{3U,  DIO_ID_PORT25},				/* PORT25 CH3	*/
	{4U,  DIO_ID_PORT25},				/* PORT25 CH4	*/
	{5U,  DIO_ID_PORT25},				/* PORT25 CH5	*/
	{6U,  DIO_ID_PORT25},				/* PORT25 CH6	*/
	{0U,  DIO_ID_PORT27},				/* PORT27 CH0	*/
	{0U,  DIO_ID_PORT32},				/* PORT32 CH0	*/
	{1U,  DIO_ID_PORT32},				/* PORT32 CH1	*/
	{2U,  DIO_ID_PORT32},				/* PORT32 CH2	*/
	{3U,  DIO_ID_PORT32},				/* PORT32 CH3	*/
	{4U,  DIO_ID_PORT32},				/* PORT32 CH4	*/
	{5U,  DIO_ID_PORT32},				/* PORT32 CH5	*/
	{6U,  DIO_ID_PORT32},				/* PORT32 CH6	*/
	{0U,  DIO_ID_PORT33},				/* PORT33 CH0	*/
	{1U,  DIO_ID_PORT33},				/* PORT33 CH1	*/
	{2U,  DIO_ID_PORT33},				/* PORT33 CH2	*/
	{3U,  DIO_ID_PORT33},				/* PORT33 CH3	*/
	{4U,  DIO_ID_PORT33},				/* PORT33 CH4	*/
	{5U,  DIO_ID_PORT33},				/* PORT33 CH5	*/
	{6U,  DIO_ID_PORT33},				/* PORT33 CH6	*/
	{7U,  DIO_ID_PORT33},				/* PORT33 CH7	*/
	{8U,  DIO_ID_PORT33},				/* PORT33 CH8	*/
	{0U,  DIO_ID_PORT34},				/* PORT34 CH0	*/
	{1U,  DIO_ID_PORT34},				/* PORT34 CH1	*/
	{2U,  DIO_ID_PORT34},				/* PORT34 CH2	*/
	{3U,  DIO_ID_PORT34},				/* PORT34 CH3	*/
	{4U,  DIO_ID_PORT34},				/* PORT34 CH4	*/
	{0U,  DIO_ID_PORT37},				/* PORT37 CH0	*/
	{1U,  DIO_ID_PORT37},				/* PORT37 CH1	*/
	{2U,  DIO_ID_PORT37},				/* PORT37 CH2	*/
	{3U,  DIO_ID_PORT37},				/* PORT37 CH3	*/
	{4U,  DIO_ID_PORT37},				/* PORT37 CH4	*/
	{5U,  DIO_ID_PORT37},				/* PORT37 CH5	*/
	{6U,  DIO_ID_PORT37},				/* PORT37 CH6	*/
	{7U,  DIO_ID_PORT37},				/* PORT37 CH7	*/
	{8U,  DIO_ID_PORT37},				/* PORT37 CH8	*/
	{9U,  DIO_ID_PORT37},				/* PORT37 CH9	*/
	{10U, DIO_ID_PORT37},				/* PORT37 CH10	*/
	{11U, DIO_ID_PORT37},				/* PORT37 CH11	*/
	{12U, DIO_ID_PORT37},				/* PORT37 CH12	*/
	{13U, DIO_ID_PORT37},				/* PORT37 CH13	*/
	{14U, DIO_ID_PORT37},				/* PORT37 CH14	*/
	{15U, DIO_ID_PORT37},				/* PORT37 CH15	*/
	{0U,  DIO_ID_PORT38},				/* PORT38 CH0	*/
	{1U,  DIO_ID_PORT38},				/* PORT38 CH1	*/
	{2U,  DIO_ID_PORT38},				/* PORT38 CH2	*/
	{3U,  DIO_ID_PORT38},				/* PORT38 CH3	*/
	{4U,  DIO_ID_PORT38},				/* PORT38 CH4	*/
	{5U,  DIO_ID_PORT38},				/* PORT38 CH5	*/
	{6U,  DIO_ID_PORT38},				/* PORT38 CH6	*/
	{7U,  DIO_ID_PORT38},				/* PORT38 CH7	*/
	{8U,  DIO_ID_PORT38},				/* PORT38 CH8	*/
	{9U,  DIO_ID_PORT38},				/* PORT38 CH9	*/
	{10U, DIO_ID_PORT38},				/* PORT38 CH10	*/
	{11U, DIO_ID_PORT38},				/* PORT38 CH11	*/
	{12U, DIO_ID_PORT38},				/* PORT38 CH12	*/
	{13U, DIO_ID_PORT38},				/* PORT38 CH13	*/
	{14U, DIO_ID_PORT38},				/* PORT38 CH14	*/
	{15U, DIO_ID_PORT38},				/* PORT38 CH15	*/
	{0U,  DIO_ID_PORT40},				/* PORT40 CH0	*/
	{1U,  DIO_ID_PORT40},				/* PORT40 CH1	*/
	{2U,  DIO_ID_PORT40},				/* PORT40 CH2	*/
	{3U,  DIO_ID_PORT40},				/* PORT40 CH3	*/
	{4U,  DIO_ID_PORT40},				/* PORT40 CH4	*/
	{5U,  DIO_ID_PORT40},				/* PORT40 CH5	*/
	{6U,  DIO_ID_PORT40},				/* PORT40 CH6	*/
	{7U,  DIO_ID_PORT40},				/* PORT40 CH7	*/
	{8U,  DIO_ID_PORT40},				/* PORT40 CH8	*/
	{9U,  DIO_ID_PORT40},				/* PORT40 CH9	*/
	{10U, DIO_ID_PORT40},				/* PORT40 CH10	*/
	{11U, DIO_ID_PORT40},				/* PORT40 CH11	*/
	{12U, DIO_ID_PORT40},				/* PORT40 CH12	*/
	{13U, DIO_ID_PORT40},				/* PORT40 CH13	*/
	{14U, DIO_ID_PORT40},				/* PORT40 CH14	*/
	{15U, DIO_ID_PORT40},				/* PORT40 CH15	*/
	{0U,  DIO_ID_PORT41},				/* PORT41 CH0	*/
	{1U,  DIO_ID_PORT41},				/* PORT41 CH1	*/
	{2U,  DIO_ID_PORT41},				/* PORT41 CH2	*/
	{3U,  DIO_ID_PORT41},				/* PORT41 CH3	*/
	{4U,  DIO_ID_PORT41},				/* PORT41 CH4	*/
	{5U,  DIO_ID_PORT41},				/* PORT41 CH5	*/
	{6U,  DIO_ID_PORT41},				/* PORT41 CH6	*/
	{7U,  DIO_ID_PORT41},				/* PORT41 CH7	*/
	{8U,  DIO_ID_PORT41},				/* PORT41 CH8	*/
	{9U,  DIO_ID_PORT41},				/* PORT41 CH9	*/
	{10U, DIO_ID_PORT41},				/* PORT41 CH10	*/
	{11U, DIO_ID_PORT41},				/* PORT41 CH11	*/
	{12U, DIO_ID_PORT41},				/* PORT41 CH12	*/
	{13U, DIO_ID_PORT41},				/* PORT41 CH13	*/
	{14U, DIO_ID_PORT41},				/* PORT41 CH14	*/
	{15U, DIO_ID_PORT41},				/* PORT41 CH15	*/
	{0U,  DIO_ID_PORT42},				/* PORT42 CH0	*/
	{1U,  DIO_ID_PORT42},				/* PORT42 CH1	*/
	{2U,  DIO_ID_PORT42},				/* PORT42 CH2	*/
	{3U,  DIO_ID_PORT42},				/* PORT42 CH3	*/
	{4U,  DIO_ID_PORT42},				/* PORT42 CH4	*/
	{5U,  DIO_ID_PORT42},				/* PORT42 CH5	*/
	{6U,  DIO_ID_PORT42},				/* PORT42 CH6	*/
	{7U,  DIO_ID_PORT42},				/* PORT42 CH7	*/
	{8U,  DIO_ID_PORT42},				/* PORT42 CH8	*/
	{9U,  DIO_ID_PORT42},				/* PORT42 CH9	*/
	{10U, DIO_ID_PORT42},				/* PORT42 CH10	*/
	{11U, DIO_ID_PORT42},				/* PORT42 CH11	*/
	{12U, DIO_ID_PORT42},				/* PORT42 CH12	*/
	{13U, DIO_ID_PORT42},				/* PORT42 CH13	*/
	{14U, DIO_ID_PORT42},				/* PORT42 CH14	*/
	{15U, DIO_ID_PORT42},				/* PORT42 CH15	*/
	{0U,  DIO_ID_PORT43},				/* PORT43 CH0	*/
	{1U,  DIO_ID_PORT43},				/* PORT43 CH1	*/
	{2U,  DIO_ID_PORT43},				/* PORT43 CH2	*/
	{3U,  DIO_ID_PORT43},				/* PORT43 CH3	*/
	{4U,  DIO_ID_PORT43},				/* PORT43 CH4	*/
	{5U,  DIO_ID_PORT43},				/* PORT43 CH5	*/
	{6U,  DIO_ID_PORT43},				/* PORT43 CH6	*/
	{7U,  DIO_ID_PORT43},				/* PORT43 CH7	*/
	{8U,  DIO_ID_PORT43},				/* PORT43 CH8	*/
	{9U,  DIO_ID_PORT43},				/* PORT43 CH9	*/
	{10U, DIO_ID_PORT43},				/* PORT43 CH10	*/
	{11U, DIO_ID_PORT43},				/* PORT43 CH11	*/
	{12U, DIO_ID_PORT43},				/* PORT43 CH12	*/
	{13U, DIO_ID_PORT43},				/* PORT43 CH13	*/
	{14U, DIO_ID_PORT43},				/* PORT43 CH14	*/
	{15U, DIO_ID_PORT43},				/* PORT43 CH15	*/
	{0U,  DIO_ID_PORT44},				/* PORT44 CH0	*/
	{1U,  DIO_ID_PORT44},				/* PORT44 CH1	*/
	{2U,  DIO_ID_PORT44},				/* PORT44 CH2	*/
	{3U,  DIO_ID_PORT44},				/* PORT44 CH3	*/
	{4U,  DIO_ID_PORT44},				/* PORT44 CH4	*/
	{5U,  DIO_ID_PORT44},				/* PORT44 CH5	*/
	{6U,  DIO_ID_PORT44},				/* PORT44 CH6	*/
	{7U,  DIO_ID_PORT44},				/* PORT44 CH7	*/
	{8U,  DIO_ID_PORT44},				/* PORT44 CH8	*/
	{9U,  DIO_ID_PORT44},				/* PORT44 CH9	*/
	{10U, DIO_ID_PORT44},				/* PORT44 CH10	*/
	{11U, DIO_ID_PORT44},				/* PORT44 CH11	*/
	{12U, DIO_ID_PORT44},				/* PORT44 CH12	*/
	{13U, DIO_ID_PORT44},				/* PORT44 CH13	*/
	{14U, DIO_ID_PORT44},				/* PORT44 CH14	*/
	{15U, DIO_ID_PORT44},				/* PORT44 CH15	*/
	{0U,  DIO_ID_PORT45},				/* PORT45 CH0	*/
	{1U,  DIO_ID_PORT45},				/* PORT45 CH1	*/
	{2U,  DIO_ID_PORT45},				/* PORT45 CH2	*/
	{3U,  DIO_ID_PORT45},				/* PORT45 CH3	*/
	{4U,  DIO_ID_PORT45},				/* PORT45 CH4	*/
	{5U,  DIO_ID_PORT45},				/* PORT45 CH5	*/
	{6U,  DIO_ID_PORT45},				/* PORT45 CH6	*/
	{7U,  DIO_ID_PORT45},				/* PORT45 CH7	*/
	{8U,  DIO_ID_PORT45},				/* PORT45 CH8	*/
	{9U,  DIO_ID_PORT45},				/* PORT45 CH9	*/
	{10U, DIO_ID_PORT45},				/* PORT45 CH10	*/
	{11U, DIO_ID_PORT45},				/* PORT45 CH11	*/
	{12U, DIO_ID_PORT45},				/* PORT45 CH12	*/
	{13U, DIO_ID_PORT45},				/* PORT45 CH13	*/
	{14U, DIO_ID_PORT45},				/* PORT45 CH14	*/
	{15U, DIO_ID_PORT45},				/* PORT45 CH15	*/
	{0U,  DIO_ID_PORT46},				/* PORT46 CH0	*/
	{1U,  DIO_ID_PORT46},				/* PORT46 CH1	*/
	{2U,  DIO_ID_PORT46},				/* PORT46 CH2	*/
	{3U,  DIO_ID_PORT46},				/* PORT46 CH3	*/
	{4U,  DIO_ID_PORT46},				/* PORT46 CH4	*/
	{5U,  DIO_ID_PORT46},				/* PORT46 CH5	*/
	{6U,  DIO_ID_PORT46},				/* PORT46 CH6	*/
	{7U,  DIO_ID_PORT46},				/* PORT46 CH7	*/
	{8U,  DIO_ID_PORT46},				/* PORT46 CH8	*/
	{9U,  DIO_ID_PORT46},				/* PORT46 CH9	*/
	{10U, DIO_ID_PORT46},				/* PORT46 CH10	*/
	{11U, DIO_ID_PORT46},				/* PORT46 CH11	*/
	{12U, DIO_ID_PORT46},				/* PORT46 CH12	*/
	{13U, DIO_ID_PORT46},				/* PORT46 CH13	*/
	{14U, DIO_ID_PORT46},				/* PORT46 CH14	*/
	{15U, DIO_ID_PORT46},				/* PORT46 CH15	*/
	{0U,  DIO_ID_PORT47},				/* PORT47 CH0	*/
	{1U,  DIO_ID_PORT47},				/* PORT47 CH1	*/
	{2U,  DIO_ID_PORT47},				/* PORT47 CH2	*/
	{3U,  DIO_ID_PORT47},				/* PORT47 CH3	*/
	{4U,  DIO_ID_PORT47},				/* PORT47 CH4	*/
	{5U,  DIO_ID_PORT47},				/* PORT47 CH5	*/
	{6U,  DIO_ID_PORT47},				/* PORT47 CH6	*/
	{7U,  DIO_ID_PORT47},				/* PORT47 CH7	*/
	{8U,  DIO_ID_PORT47},				/* PORT47 CH8	*/
	{9U,  DIO_ID_PORT47},				/* PORT47 CH9	*/
	{10U, DIO_ID_PORT47},				/* PORT47 CH10	*/
	{11U, DIO_ID_PORT47},				/* PORT47 CH11	*/
	{12U, DIO_ID_PORT47},				/* PORT47 CH12	*/
	{13U, DIO_ID_PORT47},				/* PORT47 CH13	*/
	{14U, DIO_ID_PORT47},				/* PORT47 CH14	*/
	{15U, DIO_ID_PORT47},				/* PORT47 CH15	*/
	{0U,  DIO_ID_PORT48},				/* PORT48 CH0	*/
	{1U,  DIO_ID_PORT48},				/* PORT48 CH1	*/
	{2U,  DIO_ID_PORT48},				/* PORT48 CH2	*/
	{3U,  DIO_ID_PORT48},				/* PORT48 CH3	*/
	{4U,  DIO_ID_PORT48},				/* PORT48 CH4	*/
	{5U,  DIO_ID_PORT48},				/* PORT48 CH5	*/
	{6U,  DIO_ID_PORT48},				/* PORT48 CH6	*/
	{7U,  DIO_ID_PORT48},				/* PORT48 CH7	*/
	{8U,  DIO_ID_PORT48},				/* PORT48 CH8	*/
	{9U,  DIO_ID_PORT48},				/* PORT48 CH9	*/
	{10U, DIO_ID_PORT48},				/* PORT48 CH10	*/
	{11U, DIO_ID_PORT48},				/* PORT48 CH11	*/
	{12U, DIO_ID_PORT48},				/* PORT48 CH12	*/
	{13U, DIO_ID_PORT48},				/* PORT48 CH13	*/
	{14U, DIO_ID_PORT48},				/* PORT48 CH14	*/
	{15U, DIO_ID_PORT48},				/* PORT48 CH15	*/
	{0U,  DIO_ID_PORT49},				/* PORT49 CH0	*/
	{1U,  DIO_ID_PORT49},				/* PORT49 CH1	*/
	{2U,  DIO_ID_PORT49},				/* PORT49 CH2	*/
	{3U,  DIO_ID_PORT49},				/* PORT49 CH3	*/
	{4U,  DIO_ID_PORT49},				/* PORT49 CH4	*/
	{5U,  DIO_ID_PORT49},				/* PORT49 CH5	*/
	{6U,  DIO_ID_PORT49},				/* PORT49 CH6	*/
	{7U,  DIO_ID_PORT49},				/* PORT49 CH7	*/
	{8U,  DIO_ID_PORT49},				/* PORT49 CH8	*/
	{9U,  DIO_ID_PORT49},				/* PORT49 CH9	*/
	{10U, DIO_ID_PORT49},				/* PORT49 CH10	*/
	{11U, DIO_ID_PORT49},				/* PORT49 CH11	*/
	{12U, DIO_ID_PORT49},				/* PORT49 CH12	*/
	{13U, DIO_ID_PORT49},				/* PORT49 CH13	*/
	{14U, DIO_ID_PORT49},				/* PORT49 CH14	*/
	{15U, DIO_ID_PORT49},				/* PORT49 CH15	*/
	{0U,  DIO_ID_PORT50},				/* PORT50 CH0	*/
	{1U,  DIO_ID_PORT50},				/* PORT50 CH1	*/
	{2U,  DIO_ID_PORT50},				/* PORT50 CH2	*/
	{3U,  DIO_ID_PORT50},				/* PORT50 CH3	*/
	{4U,  DIO_ID_PORT50},				/* PORT50 CH4	*/
	{5U,  DIO_ID_PORT50},				/* PORT50 CH5	*/
	{6U,  DIO_ID_PORT50},				/* PORT50 CH6	*/
	{7U,  DIO_ID_PORT50},				/* PORT50 CH7	*/
	{8U,  DIO_ID_PORT50},				/* PORT50 CH8	*/
	{9U,  DIO_ID_PORT50},				/* PORT50 CH9	*/
	{10U, DIO_ID_PORT50},				/* PORT50 CH10	*/
	{11U, DIO_ID_PORT50},				/* PORT50 CH11	*/
	{12U, DIO_ID_PORT50},				/* PORT50 CH12	*/
	{13U, DIO_ID_PORT50},				/* PORT50 CH13	*/
	{14U, DIO_ID_PORT50},				/* PORT50 CH14	*/
	{15U, DIO_ID_PORT50},				/* PORT50 CH15	*/
	{0U,  DIO_ID_PORT51},				/* PORT51 CH0	*/
	{1U,  DIO_ID_PORT51},				/* PORT51 CH1	*/
	{2U,  DIO_ID_PORT51},				/* PORT51 CH2	*/
	{3U,  DIO_ID_PORT51},				/* PORT51 CH3	*/
	{4U,  DIO_ID_PORT51},				/* PORT51 CH4	*/
	{5U,  DIO_ID_PORT51},				/* PORT51 CH5	*/
	{6U,  DIO_ID_PORT51},				/* PORT51 CH6	*/
	{7U,  DIO_ID_PORT51},				/* PORT51 CH7	*/
	{8U,  DIO_ID_PORT51},				/* PORT51 CH8	*/
	{9U,  DIO_ID_PORT51},				/* PORT51 CH9	*/
	{10U, DIO_ID_PORT51},				/* PORT51 CH10	*/
	{11U, DIO_ID_PORT51},				/* PORT51 CH11	*/
	{12U, DIO_ID_PORT51},				/* PORT51 CH12	*/
	{13U, DIO_ID_PORT51},				/* PORT51 CH13	*/
	{14U, DIO_ID_PORT51},				/* PORT51 CH14	*/
	{15U, DIO_ID_PORT51},				/* PORT51 CH15	*/
	{0U,  DIO_ID_PORT52},				/* PORT52 CH0	*/
	{1U,  DIO_ID_PORT52},				/* PORT52 CH1	*/
	{2U,  DIO_ID_PORT52},				/* PORT52 CH2	*/
	{3U,  DIO_ID_PORT52},				/* PORT52 CH3	*/
	{4U,  DIO_ID_PORT52},				/* PORT52 CH4	*/
	{5U,  DIO_ID_PORT52},				/* PORT52 CH5	*/
	{6U,  DIO_ID_PORT52},				/* PORT52 CH6	*/
	{7U,  DIO_ID_PORT52},				/* PORT52 CH7	*/
	{8U,  DIO_ID_PORT52},				/* PORT52 CH8	*/
	{9U,  DIO_ID_PORT52},				/* PORT52 CH9	*/
	{10U, DIO_ID_PORT52},				/* PORT52 CH10	*/
	{11U, DIO_ID_PORT52},				/* PORT52 CH11	*/
	{12U, DIO_ID_PORT52},				/* PORT52 CH12	*/
	{13U, DIO_ID_PORT52},				/* PORT52 CH13	*/
	{14U, DIO_ID_PORT52},				/* PORT52 CH14	*/
	{15U, DIO_ID_PORT52},				/* PORT52 CH15	*/
	{0U,  DIO_ID_JPORT0},				/* JPORT0 CH0	*/
	{1U,  DIO_ID_JPORT0},				/* JPORT0 CH1	*/
	{2U,  DIO_ID_JPORT0},				/* JPORT0 CH2	*/
	{3U,  DIO_ID_JPORT0},				/* JPORT0 CH3	*/
	{5U,  DIO_ID_JPORT0}				/* JPORT0 CH5	*/
};

static CONST(Dio_PortInfoType, DIO_CONST) s_cstDio_PortInfoArray[DIO_ASSIGN_ID_PORT_MAX] = {
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 0U},		/* PORT0		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 2U},		/* PORT2		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 10U},		/* PORT10		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 11U},		/* PORT11		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 12U},		/* PORT12		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 13U},		/* PORT13		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 14U},		/* PORT14		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 20U},		/* PORT20		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_P21, 21U},		/* PORT21		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 22U},		/* PORT22		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 23U},		/* PORT23		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_P25, 25U},		/* PORT25		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_P27, 27U},		/* PORT27		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 32U},		/* PORT32		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 33U},		/* PORT33		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 34U},		/* PORT34		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 37U},		/* PORT37		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 38U},		/* PORT38		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 40U},		/* PORT40		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 41U},		/* PORT41		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 42U},		/* PORT42		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 43U},		/* PORT43		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 44U},		/* PORT44		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 45U},		/* PORT45		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 46U},		/* PORT46		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 47U},		/* PORT47		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 48U},		/* PORT48		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 49U},		/* PORT49		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 50U},		/* PORT50		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 51U},		/* PORT51		*/
	{DIO_PORT_TYPE_NORMAL, PORT_PWE_TARGET_NOT, 52U},		/* PORT52		*/
	{DIO_PORT_TYPE_JTAG,   PORT_PWE_TARGET_NOT, 0U}			/* JPORT0		*/
};

#endif /* MCAL_TARGET_RH850U2A */

#define DIO_STOP_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

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
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel( VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId )
{
	P2CONST(Dio_ChannelInfoType, AUTOMATIC, DIO_CONST) t_pstChannel;
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	VAR(Dio_LevelType, DIO_VAR_INIT) t_u1RetVal;
	VAR(Dio_PortType, DIO_VAR_INIT) t_u1PortId;
	VAR(uint16, DIO_VAR_INIT) t_u2Level;
	VAR(uint16, DIO_VAR_INIT) t_u2Mask;

	t_u1RetVal = STD_LOW;

	if ( DIO_ASSIGN_ID_CH_MAX > ChannelId )
	{
		t_pstChannel = &s_cstDio_ChannelInfoArray[ChannelId];
		/* Actions for QAC Warning Number 2934 */
		t_u1PortId	 = t_pstChannel->u1PortId;

		if ( DIO_ASSIGN_ID_PORT_MAX > t_u1PortId )
		{
			t_pstPort = &s_cstDio_PortInfoArray[t_u1PortId];
			t_u2Mask  = (uint16)( (uint16)1 << (uint16)t_pstChannel->u1PinPos );
			t_u2Level = 0U;

			switch ( t_pstPort->enPortType )
			{
				case DIO_PORT_TYPE_NORMAL:
					t_u2Level = Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2PPR & t_u2Mask;
					break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
				case DIO_PORT_TYPE_ANALOG:
					t_u2Level = Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2APPR & t_u2Mask;
					break;
#endif
				case DIO_PORT_TYPE_JTAG:
					t_u2Level = (uint16)( Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JPPR ) & t_u2Mask;
					break;
				default:
					/* No action required */
					break;
			}

			/* Set return value */
			if ( t_u2Level == t_u2Mask )
			{
				t_u1RetVal = STD_HIGH;
			}
		}
	}

	return( t_u1RetVal );
}

/************************************************************************************************/
/* Service name		:	Dio_WriteChannel														*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	ChannelId - ID of DIO channel											*/
/*						Level	  - Value to be written											*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannel(
	VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId, VAR(Dio_LevelType, DIO_VAR_INIT) Level )
{
	P2CONST(Dio_ChannelInfoType, AUTOMATIC, DIO_CONST) t_pstChannel;
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	VAR(Dio_PortType, DIO_VAR_INIT) t_u1PortId;
	VAR(uint32, DIO_VAR_INIT) t_u4PSRContent;
	VAR(uint16, DIO_VAR_INIT) t_u2Mask;

	if ( DIO_ASSIGN_ID_CH_MAX > ChannelId )
	{
		t_pstChannel = &s_cstDio_ChannelInfoArray[ChannelId];
		/* Actions for QAC Warning Number 2934 */
		t_u1PortId	 = t_pstChannel->u1PortId;

		if ( DIO_ASSIGN_ID_PORT_MAX > t_u1PortId )
		{
			/*--------------------------------------------------------------------------------------------------*/
			/* In order to support the output data latch setting when the pin direction is changed by the port, */
			/* Dio also write to the input channel.																*/
			/* Unsupported pins shall not be specified in accordance with UM restrictions.						*/
			/*--------------------------------------------------------------------------------------------------*/
			t_pstPort = &s_cstDio_PortInfoArray[t_u1PortId];
			t_u2Mask  = (uint16)( (uint16)1 << (uint16)t_pstChannel->u1PinPos );

			/* Set upper 16bits of PSR register */
			t_u4PSRContent = (uint32)t_u2Mask << DIO_SHIFT_16;
			if ( Level == (Dio_LevelType)STD_HIGH )
			{
				/* Set lower 16bits of PSR register */
				t_u4PSRContent = t_u4PSRContent | (uint32)t_u2Mask;
			}

			/* Exclusive Start */
			DIO_ENTER_CRITICAL_SECTION();

			DIO_FUNC_DISABLE_PROTECTION( t_pstPort->u4PweWriteValue );

			switch ( t_pstPort->enPortType )
			{
				case DIO_PORT_TYPE_NORMAL:
					Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u4PSR = t_u4PSRContent;
					break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
				case DIO_PORT_TYPE_ANALOG:
					Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u4APSR = t_u4PSRContent;
					break;
#endif
				case DIO_PORT_TYPE_JTAG:
					Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u4JPSR = t_u4PSRContent;
					break;
				default:
					/* No action required */
					break;
			}

			DIO_FUNC_ENABLE_PROTECTION( t_pstPort->u4PweWriteValue );

			/* Exclusive End */
			DIO_EXIT_CRITICAL_SECTION();
		}
	}

	return;
}

#if ( DIO_FLIP_CHANNEL_API == STD_ON )
/************************************************************************************************/
/* Service name		:	Dio_FlipChannel															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	ChannelId - ID of DIO channel											*/
/* Return value		:	Dio_LevelType -															*/
/*							STD_HIGH/STD_LOW depending on the physical level of the Pin			*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_FlipChannel( VAR(Dio_ChannelType, DIO_VAR_INIT) ChannelId )
{
	P2CONST(Dio_ChannelInfoType, AUTOMATIC, DIO_CONST) t_pstChannel;
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	P2VAR(volatile uint32, AUTOMATIC, REGSPACE) t_pu4PSRn_Addr;
	VAR(Dio_LevelType, DIO_VAR_INIT) t_u1RetVal;
	VAR(Dio_PortType, DIO_VAR_INIT) t_u1PortId;
	VAR(uint32, DIO_VAR_INIT) t_u4PSRContent;
	VAR(uint16, DIO_VAR_INIT) t_u2Level;
	VAR(uint16, DIO_VAR_INIT) t_u2Direction;
	VAR(uint16, DIO_VAR_INIT) t_u2Mask;

	t_u1RetVal = STD_LOW;

	if ( DIO_ASSIGN_ID_CH_MAX > ChannelId )
	{
		t_pstChannel = &s_cstDio_ChannelInfoArray[ChannelId];
		/* Actions for QAC Warning Number 2934 */
		t_u1PortId	 = t_pstChannel->u1PortId;

		if ( DIO_ASSIGN_ID_PORT_MAX > t_u1PortId )
		{
			t_pstPort	   = &s_cstDio_PortInfoArray[t_u1PortId];
			t_u2Mask	   = (uint16)( (uint16)1 << (uint16)t_pstChannel->u1PinPos );
			t_pu4PSRn_Addr = NULL_PTR;
			t_u2Direction  = 0U;
			t_u2Level	   = 0U;

			/* Exclusive Start */
			DIO_ENTER_CRITICAL_SECTION();

			/* Get pin direction and current level */
			/* direction is 1 for input, 0 for output */
			switch ( t_pstPort->enPortType )
			{
				case DIO_PORT_TYPE_NORMAL:
					t_u2Direction  = Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2PM & t_u2Mask;
					t_u2Level	   = Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2PPR & t_u2Mask;
					break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
				case DIO_PORT_TYPE_ANALOG:
					t_u2Direction  = Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2APM & t_u2Mask;
					t_u2Level	   = Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2APPR & t_u2Mask;
					break;
#endif
				case DIO_PORT_TYPE_JTAG:
					t_u2Direction  = (uint16)( Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JPM ) & t_u2Mask;
					t_u2Level	   = (uint16)( Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JPPR ) & t_u2Mask;
					break;
				default:
					/* No action required */
					break;
			}

			/*--------------------------------------------------------------*/
			/* Flip only on output											*/
			/*	Judgment premise											*/
			/*	1.PM register 0 means output.								*/
			/*	2.t_u2Direction is set to 0 except for the Flip target bit. */
			/*--------------------------------------------------------------*/
			if ( t_u2Direction == DIO_DIRECTION_OUTPUT )
			{
				/* Split Switch for QAC Warning Number 2982 */
				/* Get write destination register */
				switch ( t_pstPort->enPortType )
				{
					case DIO_PORT_TYPE_NORMAL:
						t_pu4PSRn_Addr = &Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u4PSR;
						break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
					case DIO_PORT_TYPE_ANALOG:
						t_pu4PSRn_Addr = &Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u4APSR;
						break;
#endif
					case DIO_PORT_TYPE_JTAG:
						t_pu4PSRn_Addr = &Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u4JPSR;
						break;
					default:
						/* No action required */
						break;
				}

				if ( t_pu4PSRn_Addr != NULL_PTR )
				{
					/* Set upper 16bits of PSR register */
					t_u4PSRContent = (uint32)t_u2Mask << DIO_SHIFT_16;

					DIO_FUNC_DISABLE_PROTECTION( t_pstPort->u4PweWriteValue );

					/* Set lower 16bits of PSR register and Write to PSR register */
					(*t_pu4PSRn_Addr) = t_u4PSRContent | (uint32)( (uint16)( ~t_u2Level ) );

					DIO_FUNC_ENABLE_PROTECTION( t_pstPort->u4PweWriteValue );

					/* set output mode return value */
					if ( t_u2Level != t_u2Mask )
					{
						t_u1RetVal = STD_HIGH;
					}
				}
			}
			else
			{
				/* set input mode return value */
				if ( t_u2Level == t_u2Mask )
				{
					t_u1RetVal = STD_HIGH;
				}
			}

			/* Exclusive End */
			DIO_EXIT_CRITICAL_SECTION();
		}
	}

	return( t_u1RetVal );
}
#endif /* DIO_FLIP_CHANNEL_API == STD_ON */

/************************************************************************************************/
/* Service name		:	Dio_ReadPort															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	PortId - ID of DIO Port													*/
/* Return value		:	Dio_PortLevelType - Level of all channels of that port					*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort( VAR(Dio_PortType, DIO_VAR_INIT) PortId )
{
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	VAR(Dio_PortLevelType, DIO_VAR_INIT) t_u2RetVal;

	t_u2RetVal = 0U;

	if ( DIO_ASSIGN_ID_PORT_MAX > PortId )
	{
		t_pstPort = &s_cstDio_PortInfoArray[PortId];

		switch ( t_pstPort->enPortType )
		{
			case DIO_PORT_TYPE_NORMAL:
				t_u2RetVal = Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2PPR;
				break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
			case DIO_PORT_TYPE_ANALOG:
				t_u2RetVal = Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2APPR;
				break;
#endif
			case DIO_PORT_TYPE_JTAG:
				t_u2RetVal = (Dio_PortLevelType)( Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JPPR );
				break;
			default:
				/* No action required */
				break;
		}
	}

	return( t_u2RetVal );
}

/************************************************************************************************/
/* Service name		:	Dio_WritePort															*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	PortId - ID of DIO Port													*/
/*						Level  - Value to be written											*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WritePort(
	VAR(Dio_PortType, DIO_VAR_INIT) PortId, VAR(Dio_PortLevelType, DIO_VAR_INIT) Level)
{
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;

	if ( DIO_ASSIGN_ID_PORT_MAX > PortId )
	{
		/*--------------------------------------------------------------------------------------------------*/
		/* In order to support the output data latch setting when the pin direction is changed by the port, */
		/* Dio also write to the input channel.																*/
		/* For unsupported pins, the HW initial values are assumed in accordance with UM constraints.		*/
		/*--------------------------------------------------------------------------------------------------*/
		t_pstPort = &s_cstDio_PortInfoArray[PortId];

		/* Exclusive Start */
		DIO_ENTER_CRITICAL_SECTION();

		DIO_FUNC_DISABLE_PROTECTION( t_pstPort->u4PweWriteValue );

		switch ( t_pstPort->enPortType )
		{
			case DIO_PORT_TYPE_NORMAL:
				Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2P = Level;
				break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
			case DIO_PORT_TYPE_ANALOG:
				Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2AP = Level;
				break;
#endif
			case DIO_PORT_TYPE_JTAG:
				Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JP = (uint8)Level;
				break;
			default:
				/* No action required */
				break;
		}

		DIO_FUNC_ENABLE_PROTECTION( t_pstPort->u4PweWriteValue );

		/* Exclusive End */
		DIO_EXIT_CRITICAL_SECTION();
	}

	return;
}

/************************************************************************************************/
/* Service name		:	Dio_ReadChannelGroup													*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	Dio_ChannelGroupType - Pointer to ChannelGroup							*/
/* Return value		:	Dio_PortLevelType - Level of a subset of the adjoining bits of a port	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup(
	P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONST) ChannelGroupIdPtr )
{
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	VAR(Dio_PortLevelType, DIO_VAR_INIT) t_u2RetVal;

	t_u2RetVal = 0U;

	if ( DIO_ASSIGN_ID_PORT_MAX > ChannelGroupIdPtr->port )
	{
		t_pstPort = &s_cstDio_PortInfoArray[ChannelGroupIdPtr->port];

		switch ( t_pstPort->enPortType )
		{
			case DIO_PORT_TYPE_NORMAL:
				t_u2RetVal = Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u2PPR;
				break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
			case DIO_PORT_TYPE_ANALOG:
				t_u2RetVal = Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u2APPR;
				break;
#endif
			case DIO_PORT_TYPE_JTAG:
				t_u2RetVal = (Dio_PortLevelType)( Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u1JPPR );
				break;
			default:
				/* No action required */
				break;
		}

		/* Shift logical product of Level and mask by offset */
		t_u2RetVal = t_u2RetVal & ChannelGroupIdPtr->mask;
		t_u2RetVal = t_u2RetVal >> ChannelGroupIdPtr->offset;
	}

	return( t_u2RetVal );
}

/************************************************************************************************/
/* Service name		:	Dio_WriteChannelGroup													*/
/* Reentrancy		:	Reentrant																*/
/* Parameters(in)	:	Dio_ChannelGroupType - Pointer to ChannelGroup							*/
/*						Level				 - Value to be written								*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/************************************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannelGroup(
	P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONST) ChannelGroupIdPtr,
	VAR(Dio_PortLevelType, DIO_VAR_INIT) Level)
{
	P2CONST(Dio_PortInfoType, AUTOMATIC, DIO_CONST) t_pstPort;
	VAR(uint32, DIO_VAR_INIT) t_u4PSRContent;

	if ( DIO_ASSIGN_ID_PORT_MAX > ChannelGroupIdPtr->port )
	{
		/*--------------------------------------------------------------------------------------------------*/
		/* In order to support the output data latch setting when the pin direction is changed by the port, */
		/* Dio also write to the input channel.																*/
		/* Unsupported pins shall not be specified in accordance with UM restrictions.						*/
		/*--------------------------------------------------------------------------------------------------*/
		t_pstPort = &s_cstDio_PortInfoArray[ChannelGroupIdPtr->port];
		/* Set upper 16bits of PSR register */
		t_u4PSRContent = (uint32)ChannelGroupIdPtr->mask << DIO_SHIFT_16;
		/* Set lower 16bits of PSR register and Write to PSR register */
		t_u4PSRContent = t_u4PSRContent | (uint32)( (uint16)( Level << ChannelGroupIdPtr->offset ) );

		/* Exclusive Start */
		DIO_ENTER_CRITICAL_SECTION();

		DIO_FUNC_DISABLE_PROTECTION( t_pstPort->u4PweWriteValue );

		switch ( t_pstPort->enPortType )
		{
			case DIO_PORT_TYPE_NORMAL:
				Reg_PORT_PORT->stPORT0[t_pstPort->u1PortGroupNo].u4PSR = t_u4PSRContent;
				break;
#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )
			case DIO_PORT_TYPE_ANALOG:
				Reg_PORT_APORT->stANALOG0[t_pstPort->u1PortGroupNo].u4APSR = t_u4PSRContent;
				break;
#endif
			case DIO_PORT_TYPE_JTAG:
				Reg_PORT_JPORT->stJPORT0[t_pstPort->u1PortGroupNo].u4JPSR = t_u4PSRContent;
				break;
			default:
				/* No action required */
				break;
		}

		DIO_FUNC_ENABLE_PROTECTION( t_pstPort->u4PweWriteValue );

		/* Exclusive End */
		DIO_EXIT_CRITICAL_SECTION();
	}

	return;
}

/*----------------------------------------------------------------------------------------------*/
/* Local Functions																				*/
/*----------------------------------------------------------------------------------------------*/
#if ( DIO_CFG_PROTECTION_CONTROL == STD_ON )
/************************************************************************************************/
/* Service name		:	Dio_DisableProtection													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_cu4PweWriteValue - A value that makes port group writable				*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/*						Call in an exclusive interval.											*/
/************************************************************************************************/
static FUNC(void, DIO_CODE) Dio_DisableProtection( CONST(uint32, DIO_CONST) t_cu4PweWriteValue )
{
	if ( t_cu4PweWriteValue != PORT_PWE_TARGET_NOT )
	{
		/* Allow writing to PWE register */
		Reg_PORT_PORT->u4PKCPROT = PORT_PROTECT_DISABLE;
		/* Allow writing to port group */
		Reg_PORT_PORT->u4PWE = Reg_PORT_PORT->u4PWE | t_cu4PweWriteValue;
	}

	return;
}

/************************************************************************************************/
/* Service name		:	Dio_EnableProtection													*/
/* Reentrancy		:	Non Reentrant															*/
/* Parameters(in)	:	t_cu4PweWriteValue - A value that makes port group writable				*/
/* Return value		:	none																	*/
/* Limitation		:	Call after Port_Init().													*/
/*						Call in an exclusive interval.											*/
/************************************************************************************************/
static FUNC(void, DIO_CODE) Dio_EnableProtection( CONST(uint32, DIO_CONST) t_cu4PweWriteValue )
{
	if ( t_cu4PweWriteValue != PORT_PWE_TARGET_NOT )
	{
		/* Deny writing to port group */
		Reg_PORT_PORT->u4PWE = Reg_PORT_PORT->u4PWE & ( (uint32)( ~t_cu4PweWriteValue ) );
		/* Deny writing to PWE register */
		Reg_PORT_PORT->u4PKCPROT = PORT_PROTECT_ENABLE;
	}

	return;
}
#endif /* DIO_CFG_PROTECTION_CONTROL == STD_ON */

#define DIO_STOP_SEC_CODE_GLOBAL
#include "Dio_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
