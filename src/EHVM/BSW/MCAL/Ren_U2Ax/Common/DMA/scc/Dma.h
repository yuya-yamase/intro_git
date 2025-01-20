/* Dma-r04-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL DMA Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef DMA_H
#define DMA_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Mcal_SpalCmn.h"
#include	"Std_Types.h"
#include	"Dma_Cfg.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
/* To build through engine MCALs in a standard MCAL environment */
#ifndef PLATFORM_EXTDEFS_H
typedef		unsigned char		U1;
typedef		unsigned short		U2;
typedef		unsigned long		U4;
typedef		signed char			S1;
typedef		signed short		S2;
typedef		signed long			S4;
typedef		signed long			ZORN;
typedef		float				PL;			/* Physical (floating point) */
#endif
typedef		float				F4;

/*==============================================================================================*/
/*		Bit data name definition																		*/
/*==============================================================================================*/
#define		BIT0		(0x00000001U)
#define		BIT1		(0x00000002U)
#define		BIT2		(0x00000004U)
#define		BIT3		(0x00000008U)
#define		BIT4		(0x00000010U)
#define		BIT5		(0x00000020U)
#define		BIT6		(0x00000040U)
#define		BIT7		(0x00000080U)
#define		BIT8		(0x00000100U)
#define		BIT9		(0x00000200U)
#define		BIT10		(0x00000400U)
#define		BIT11		(0x00000800U)
#define		BIT12		(0x00001000U)
#define		BIT13		(0x00002000U)
#define		BIT14		(0x00004000U)
#define		BIT15		(0x00008000U)
#define		BIT16		(0x00010000U)
#define		BIT17		(0x00020000U)
#define		BIT18		(0x00040000U)
#define		BIT19		(0x00080000U)
#define		BIT20		(0x00100000U)
#define		BIT21		(0x00200000U)
#define		BIT22		(0x00400000U)
#define		BIT23		(0x00800000U)
#define		BIT24		(0x01000000U)
#define		BIT25		(0x02000000U)
#define		BIT26		(0x04000000U)
#define		BIT27		(0x08000000U)
#define		BIT28		(0x10000000U)
#define		BIT29		(0x20000000U)
#define		BIT30		(0x40000000U)
#define		BIT31		(0x80000000U)

/* DMA channel ID(API argument (ChDataID)) */
#define	DMA_CH_DATA_ID_0	(0U)
#define	DMA_CH_DATA_ID_1	(1U)
#define	DMA_CH_DATA_ID_2	(2U)
#define	DMA_CH_DATA_ID_3	(3U)
#define	DMA_CH_DATA_ID_4	(4U)
#define	DMA_CH_DATA_ID_5	(5U)
#define	DMA_CH_DATA_ID_6	(6U)
#define	DMA_CH_DATA_ID_7	(7U)
#define	DMA_CH_DATA_ID_8	(8U)
#define	DMA_CH_DATA_ID_9	(9U)
#define	DMA_CH_DATA_ID_10	(10U)
#define	DMA_CH_DATA_ID_11	(11U)
#define	DMA_CH_DATA_ID_12	(12U)
#define	DMA_CH_DATA_ID_13	(13U)
#define	DMA_CH_DATA_ID_14	(14U)
#define	DMA_CH_DATA_ID_15	(15U)
#define	DMA_CH_DATA_ID_16	(16U)
#define	DMA_CH_DATA_ID_17	(17U)
#define	DMA_CH_DATA_ID_18	(18U)
#define	DMA_CH_DATA_ID_19	(19U)
#define	DMA_CH_DATA_ID_20	(20U)
#define	DMA_CH_DATA_ID_21	(21U)
#define	DMA_CH_DATA_ID_22	(22U)
#define	DMA_CH_DATA_ID_23	(23U)
#define	DMA_CH_DATA_ID_24	(24U)
#define	DMA_CH_DATA_ID_25	(25U)
#define	DMA_CH_DATA_ID_26	(26U)
#define	DMA_CH_DATA_ID_27	(27U)
#define	DMA_CH_DATA_ID_28	(28U)
#define	DMA_CH_DATA_ID_29	(29U)
#define	DMA_CH_DATA_ID_30	(30U)
#define	DMA_CH_DATA_ID_31	(31U)
#define	DMA_CH_DATA_ID_32	(32U)
#define	DMA_CH_DATA_ID_33	(33U)
#define	DMA_CH_DATA_ID_34	(34U)
#define	DMA_CH_DATA_ID_35	(35U)
#define	DMA_CH_DATA_ID_36	(36U)
#define	DMA_CH_DATA_ID_37	(37U)
#define	DMA_CH_DATA_ID_38	(38U)
#define	DMA_CH_DATA_ID_39	(39U)
#define	DMA_CH_DATA_ID_40	(40U)
#define	DMA_CH_DATA_ID_41	(41U)
#define	DMA_CH_DATA_ID_42	(42U)
#define	DMA_CH_DATA_ID_43	(43U)
#define	DMA_CH_DATA_ID_44	(44U)
#define	DMA_CH_DATA_ID_45	(45U)
#define	DMA_CH_DATA_ID_46	(46U)
#define	DMA_CH_DATA_ID_47	(47U)
#define	DMA_CH_DATA_ID_48	(48U)
#define	DMA_CH_DATA_ID_49	(49U)
#define	DMA_CH_DATA_ID_50	(50U)
#define	DMA_CH_DATA_ID_51	(51U)
#define	DMA_CH_DATA_ID_52	(52U)
#define	DMA_CH_DATA_ID_53	(53U)
#define	DMA_CH_DATA_ID_54	(54U)
#define	DMA_CH_DATA_ID_55	(55U)
#define	DMA_CH_DATA_ID_56	(56U)
#define	DMA_CH_DATA_ID_57	(57U)
#define	DMA_CH_DATA_ID_58	(58U)
#define	DMA_CH_DATA_ID_59	(59U)
#define	DMA_CH_DATA_ID_60	(60U)
#define	DMA_CH_DATA_ID_61	(61U)
#define	DMA_CH_DATA_ID_62	(62U)
#define	DMA_CH_DATA_ID_63	(63U)
#define	DMA_CH_DATA_ID_64	(64U)
#define	DMA_CH_DATA_ID_65	(65U)
#define	DMA_CH_DATA_ID_66	(66U)
#define	DMA_CH_DATA_ID_67	(67U)
#define	DMA_CH_DATA_ID_68	(68U)
#define	DMA_CH_DATA_ID_69	(69U)
#define	DMA_CH_DATA_ID_70	(70U)
#define	DMA_CH_DATA_ID_71	(71U)
#define	DMA_CH_DATA_ID_72	(72U)
#define	DMA_CH_DATA_ID_73	(73U)
#define	DMA_CH_DATA_ID_74	(74U)
#define	DMA_CH_DATA_ID_75	(75U)
#define	DMA_CH_DATA_ID_76	(76U)
#define	DMA_CH_DATA_ID_77	(77U)
#define	DMA_CH_DATA_ID_78	(78U)
#define	DMA_CH_DATA_ID_79	(79U)
#define	DMA_CH_DATA_ID_80	(80U)
#define	DMA_CH_DATA_ID_81	(81U)
#define	DMA_CH_DATA_ID_82	(82U)
#define	DMA_CH_DATA_ID_83	(83U)
#define	DMA_CH_DATA_ID_84	(84U)
#define	DMA_CH_DATA_ID_85	(85U)
#define	DMA_CH_DATA_ID_86	(86U)
#define	DMA_CH_DATA_ID_87	(87U)
#define	DMA_CH_DATA_ID_88	(88U)
#define	DMA_CH_DATA_ID_89	(89U)
#define	DMA_CH_DATA_ID_90	(90U)
#define	DMA_CH_DATA_ID_91	(91U)
#define	DMA_CH_DATA_ID_92	(92U)
#define	DMA_CH_DATA_ID_93	(93U)
#define	DMA_CH_DATA_ID_94	(94U)
#define	DMA_CH_DATA_ID_95	(95U)
#define	DMA_CH_DATA_ID_96	(96U)
#define	DMA_CH_DATA_ID_97	(97U)
#define	DMA_CH_DATA_ID_98	(98U)
#define	DMA_CH_DATA_ID_99	(99U)
#define	DMA_CH_DATA_ID_100	(100U)
#define	DMA_CH_DATA_ID_101	(101U)
#define	DMA_CH_DATA_ID_102	(102U)
#define	DMA_CH_DATA_ID_103	(103U)
#define	DMA_CH_DATA_ID_104	(104U)
#define	DMA_CH_DATA_ID_105	(105U)
#define	DMA_CH_DATA_ID_106	(106U)
#define	DMA_CH_DATA_ID_107	(107U)
#define	DMA_CH_DATA_ID_108	(108U)
#define	DMA_CH_DATA_ID_109	(109U)
#define	DMA_CH_DATA_ID_110	(110U)
#define	DMA_CH_DATA_ID_111	(111U)
#define	DMA_CH_DATA_ID_112	(112U)
#define	DMA_CH_DATA_ID_113	(113U)
#define	DMA_CH_DATA_ID_114	(114U)
#define	DMA_CH_DATA_ID_115	(115U)
#define	DMA_CH_DATA_ID_116	(116U)
#define	DMA_CH_DATA_ID_117	(117U)
#define	DMA_CH_DATA_ID_118	(118U)
#define	DMA_CH_DATA_ID_119	(119U)
#define	DMA_CH_DATA_ID_120	(120U)
#define	DMA_CH_DATA_ID_121	(121U)
#define	DMA_CH_DATA_ID_122	(122U)
#define	DMA_CH_DATA_ID_123	(123U)
#define	DMA_CH_DATA_ID_124	(124U)
#define	DMA_CH_DATA_ID_125	(125U)
#define	DMA_CH_DATA_ID_126	(126U)
#define	DMA_CH_DATA_ID_127	(127U)
#define	DMA_CH_DATA_ID_128	(128U)
#define	DMA_CH_DATA_ID_129	(129U)
#define	DMA_CH_DATA_ID_130	(130U)
#define	DMA_CH_DATA_ID_131	(131U)
#define	DMA_CH_DATA_ID_132	(132U)
#define	DMA_CH_DATA_ID_133	(133U)
#define	DMA_CH_DATA_ID_134	(134U)
#define	DMA_CH_DATA_ID_135	(135U)
#define	DMA_CH_DATA_ID_136	(136U)
#define	DMA_CH_DATA_ID_137	(137U)
#define	DMA_CH_DATA_ID_138	(138U)
#define	DMA_CH_DATA_ID_139	(139U)
#define	DMA_CH_DATA_ID_140	(140U)
#define	DMA_CH_DATA_ID_141	(141U)
#define	DMA_CH_DATA_ID_142	(142U)
#define	DMA_CH_DATA_ID_143	(143U)
#define	DMA_CH_DATA_ID_144	(144U)
#define	DMA_CH_DATA_ID_145	(145U)
#define	DMA_CH_DATA_ID_146	(146U)
#define	DMA_CH_DATA_ID_147	(147U)
#define	DMA_CH_DATA_ID_148	(148U)
#define	DMA_CH_DATA_ID_149	(149U)
#define	DMA_CH_DATA_ID_150	(150U)
#define	DMA_CH_DATA_ID_151	(151U)
#define	DMA_CH_DATA_ID_152	(152U)
#define	DMA_CH_DATA_ID_153	(153U)
#define	DMA_CH_DATA_ID_154	(154U)
#define	DMA_CH_DATA_ID_155	(155U)
#define	DMA_CH_DATA_ID_156	(156U)
#define	DMA_CH_DATA_ID_157	(157U)
#define	DMA_CH_DATA_ID_158	(158U)
#define	DMA_CH_DATA_ID_159	(159U)

/* On-Off */
#define    DMA_ON       (1)
#define    DMA_OFF      (0)

/* Trans Status */
#define		u1DMA_TRANS_STATUS_IDLE		((U1)0U)
#define		u1DMA_TRANS_STATUS_BUSY		((U1)1U)

/* Trans Size */
#define		u1DMA_TRANSSIZE_1			((U1)0U)	/* 1byte  */
#define		u1DMA_TRANSSIZE_2			((U1)1U)	/* 2byte  */
#define		u1DMA_TRANSSIZE_4			((U1)2U)	/* 4byte  */
#define		u1DMA_TRANSSIZE_8			((U1)3U)	/* 8byte  */
#define		u1DMA_TRANSSIZE_16			((U1)4U)	/* 16byte */
#define		u1DMA_TRANSSIZE_32			((U1)5U)	/* 32byte */
#define		u1DMA_TRANSSIZE_64			((U1)6U)	/* 64byte */

#define	u2DMA_DTS_GROUP_REQ_MASK   ((U2)0x007FU)
#define	u2DMA_DMAC_GROUP_REQ_MASK	((U2)0x00FFU)

/* DMA Type */
#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
#define		DMA_DMAC0					(0U)	/* DMA DMAC0 */
#define		DMA_DMAC1					(1U)	/* DMA DMAC1 */
#define		DMA_DTS						(2U)	/* DMA DTS   */
#else
#define		DMA_DMAC0					(0U)	/* DMA DMAC0 */
#define		DMA_DTS						(2U)	/* DMA DTS   */
#endif

/* Priority */
#define		DMA_PRIORITY0				(0)	/* DMA Priority 0 */
#define		DMA_PRIORITY1				(1)	/* DMA Priority 1 */
#define		DMA_PRIORITY2				(2)	/* DMA Priority 2 */
#define		DMA_PRIORITY3				(3)	/* DMA Priority 3 */
#define		DMA_PRIORITY_NOUSE			(4)	/* No DMA priority */

/* DMA MODE */
#define		DMA_DMAMODE0				(0)	/* DMA Mode 0 */
#define		DMA_DMAMODE1				(1)	/* DMA Mode 1 */
#define		DMA_DMAMODE2				(2)	/* DMA Mode 2 */
#define		DMA_DMAMODE3				(3)	/* DMA Mode 3 */
#define		DMA_DMAMODE4				(4)	/* DMA Mode 4 */
#define		DMA_DMAMODE5				(5)	/* DMA Mode 5 */
#define		DMA_DMAMODE6				(6)	/* DMA Mode 6 */

/* No applicable logical CH */
#define		DMA_DTS_CH_NOUSE			(255)	/* Used in DTS logical channel reverse tables */

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/* Register Check */
#define DMA_REGCHK_OK						((U4)0x00000000U)	/* Register Failure Not Detect */
#define DMA_REGCHK_NG						((U4)0x00000001U)	/* Register Failure Detect */
#define DMA_REGCHK_REFRESH_SUCCESS			((U4)0x00000002U)	/* Register Refresh Success */
#define DMA_REGCHK_REFRESH_IMPOSSIBLE		((U4)0x00000004U)	/* Register Refresh Impossible */
#define DMA_REGCHK_REFRESH_FAILED			((U4)0x00000008U)	/* Register Refresh Failed */
#endif

typedef	struct {
	U1		u1DmaNotificationRequest;	/* Whether there is a Dma Notification(0:Notify None / 1:Notify Yes) */
}Dma_ChannelDataType;

/* DMA logical channels */
typedef	struct {
	void (*pvdNotification)(void);				/* Callback function	*/
	Dma_ChannelDataType*	pstChDataType;		/* Pointer for notification request structure */
	U2						u2HwCh;				/* DMA channel			*/
	U2						u2DmaReq;			/* DMA factor			*/
	U1						u1DmaType;			/* DMA Type				*/
	U1						u1PriLevel;			/* DTS Priority			*/
}Dma_ChDataDefType;

/* Dma UserConfigType */
typedef	struct{
	const	Dma_ChDataDefType*	pstChDataConfig;
	U1								u1ChDataNum;
}Dma_UserConfigType;

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*	API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Service name	:	EnableTrans																*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Dma_EnableTrans( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	DisableTrans															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Dma_DisableTrans( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	SetTransMode															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*					:	TransSize - Size (SIZE_1/SIZE_2/SIZE_4)									*/
/*					:	DmaMode - DMA Mode (0-2)												*/
/*					:	SrcAdr(Async) - Pointer to Source Adrress								*/
/*					:	DestAdr(Async) - Pointer to Destination Adrress							*/
/*					:	TransNum - Trans number													*/
/*	Return value	:	none																	*/
/*	caveat			:	Disallow calling this interface during DMA transfer						*/
/*					:	Because the DMA transfer settings you set may be overwritten			*/
/*					:	 by DTS write-back.														*/
/*					:	When using the reload feature, use SetTransModeTwoStepReload.			*/
/*					:	sDMAC only supports mode = 3, so calls to this interface are prohibited.*/
/************************************************************************************************/
void	Dma_SetTransMode( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile  const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum );

/************************************************************************************************/
/*	Service name	:	SetTransModeTwoStepReload												*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*					:	TransSize - Size (SIZE_1/SIZE_2/SIZE_4)									*/
/*					:	DmaMode - DMA Mode (3-5)												*/
/*					:	SrcAdr(Async) - Pointer to Source Adrress								*/
/*					:	DestAdr(Async) - Pointer to Destination Adrress							*/
/*					:	TransNum - Trans number													*/
/*					:	AddrReloadCnt - Address reload count									*/
/*	Return value	:	none																	*/
/*	caveat			:	Disallow calling this interface during DMA transfer						*/
/*					:	Because the DMA transfer settings you set may be overwritten			*/
/*					:	 by DTS write-back.														*/
/*					:	When mode is set to anything other than 5, AddrReloadCnt is disabled	*/
/*					:	 (only one stage reload)												*/
/*					:	When using sDMAC, setting mode to anything other than 3 is not			*/
/*					:	 guaranteed.															*/
/************************************************************************************************/
void	Dma_SetTransModeTwoStepReload( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2AddrReloadCnt );

/************************************************************************************************/
/*	Function		:	SetInterrupt															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*					:	HalfIe - Half End Interrupt E/D (OFF:DISABLE/ON:ENABLE)					*/
/*					:	EndIe - Trans End Interrupt E/D (OFF:DISABLE/ON:ENABLE)					*/
/*	Return value	:	none																	*/
/*	caveat			:	Disallow calls after and before issuing Dma _ EnableTrans for 			*/
/*					:	 the same channel.														*/
/*					:	Half-interrupts are not supported when using sDMAC.						*/
/************************************************************************************************/
void	Dma_SetInterrupt( U1 t_u1ChDataID, U1 t_u1HalfIe, U1 t_u1EndIe );

/************************************************************************************************/
/*	Service name	:	GetDestinationAddress													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Destination Address - pointer to destination							*/
/*	caveat			:	Do not call before Dma_SetTransMode and Dma_SetTransModeTwoStepReload.	*/
/************************************************************************************************/
void*	Dma_GetDestinationAddress( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	GetTransCount															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Trans Count																*/
/*	caveat			:	Prohibited calls before Dma_SetTransMode and Dma_SetTransModeTwoStepReload	*/
/*						If sDMAC has 0 transfers left, returns 1 if in transit						*/
/************************************************************************************************/
U2		Dma_GetTransCount( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	ResetTransCount															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	Disallow calling this interface during DMA transfer						*/
/************************************************************************************************/
void	Dma_ResetTransCount( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	GetTransStatus															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Trans Status															*/
/*							( DMA_TRANS_STATUS_IDLE(=0) / DMA_TRANS_STATUS_BUSY(=1) )			*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U1		Dma_GetTransStatus( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	CheckDmaError															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Error Status(With errors(!=0) / No error(==0))							*/
/*	caveat			:	In the case of DTS, if an error occurs on any channel, 					*/
/*						 it returns with an error.												*/
/*						For DTS, an interface dedicated to DFE. Redesign required if error 		*/
/*						 information is needed outside of DFE. 									*/
/*						For sDMAC, if an error occurred in the specified logical CH, return		*/
/*						 with an error.															*/
/************************************************************************************************/
ZORN	Dma_CheckDmaError( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	ClearDmaError															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	In the case of DTS, the error information is cleared even if an 		*/
/*						 error occurs on another channel.										*/
/*						For DTS, an interface dedicated to DFE. Redesign required if error		*/
/*						 information is needed outside of DFE. 									*/
/*						For sDMAC, clear error information for the specified logical CH.		*/
/*						For sDMAC, set the DMA enable flag to disable DMA transfers				*/
/*						 for clearing.															*/
/************************************************************************************************/
void	Dma_ClearDmaError( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	GetReloadStatus															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Descriptor Status														*/
/*							( DMA_CHSTA_DSE_RUNNING(=0) / DMA_CHSTA_DSE_STOP(=1) )				*/
/*	caveat			:	Regular AD SCAN only(Available when using sDMAC)						*/
/*					:	※Use only for interrupt-prohibited CHs when using mode 3 (AD Multi)	*/
/************************************************************************************************/
U1		Dma_GetReloadStatus( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	ClearDescriptorStatus													*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	Regular AD SCAN only(Available when using sDMAC)						*/
/*					:	※Use only for interrupt-prohibited CHs when using mode 3 (AD Mulit)	*/
/************************************************************************************************/
void	Dma_ClearReloadStatus( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	IsTransferCompleted														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	Trans Completed Status (TRUE / FALSE)									*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U1		Dma_IsTransferCompleted( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Service name	:	ClearTransferEndFlag													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Dma_ClearTransferEndFlag( U1 t_u1ChDataID );

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Function		:	Initialization															*/
/*	Schedule		:	Init																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/************************************************************************************************/
void	Dma_Init( void );

/************************************************************************************************/
/*	Function		:	De-Initialization														*/
/*	Schedule		:	DeInit																	*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/************************************************************************************************/
void	Dma_DeInit( void );

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/************************************************************************************************/
/*	Function		:	Dma_Regchk_All															*/
/*	Schedule		:	Regchk																	*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	Check Result															*/
/*	Relation Module	:	none																	*/
/************************************************************************************************/
U4	Dma_Regchk_All( void );
#endif

/************************************************************************************************/
/*	Function		:	Interrupt																*/
/*	Schedule		:	DMA Trans End / Descriptor End Interrupt								*/
/*	Parameters (in)	:	ChDataID - ChannelDataID												*/
/*	Relation Module	:	none																	*/
/************************************************************************************************/
void	Dma_Interrupt( U1 t_u1ChDataID );

/************************************************************************************************/
/*	Function		:	Set Master Channel														*/
/*	Schedule		:	EcuM_AL_DriverInitOne_Core0, EcuM_AL_DriverInitOne_Core1				*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/*	caveat			:	DTS SPID configuration only(Use the function safety function only when	*/
/*						 using it.)																*/
/*					:	Perform this function before turning on the DTS guard function of		*/
/*						 functional safety.														*/
/*					:	Disallow calling this interface during a DMA transfer.					*/
/************************************************************************************************/
void	Dma_SetMasterCh( void );

/*----------------------------------------------------------------------------------------------*/
/* ISR Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Function		:	DTS ISR Functions 														*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/*	caveat			:	none																	*/
/************************************************************************************************/
void Dma_INTDTS31TO0( void );
void Dma_INTDTS63TO32( void );
void Dma_INTDTS95TO64( void );
void Dma_INTDTS127TO96( void );
void Dma_INTDTSCT31TO0( void );
void Dma_INTDTSCT63TO32( void );
void Dma_INTDTSCT95TO64( void );
void Dma_INTDTSCT127TO96( void );

/************************************************************************************************/
/*	Function		:	sDMAC ISR Functions 													*/
/*	Parameters (in)	:	none																	*/
/*	Relation Module	:	none																	*/
/*	caveat			:	none																	*/
/************************************************************************************************/
void Dma_INTSDMAC0CH0( void );
void Dma_INTSDMAC0CH1( void );
void Dma_INTSDMAC0CH2( void );
void Dma_INTSDMAC0CH3( void );
void Dma_INTSDMAC0CH4( void );
void Dma_INTSDMAC0CH5( void );
void Dma_INTSDMAC0CH6( void );
void Dma_INTSDMAC0CH7( void );
void Dma_INTSDMAC0CH8( void );
void Dma_INTSDMAC0CH9( void );
void Dma_INTSDMAC0CH10( void );
void Dma_INTSDMAC0CH11( void );
void Dma_INTSDMAC0CH12( void );
void Dma_INTSDMAC0CH13( void );
void Dma_INTSDMAC0CH14( void );
void Dma_INTSDMAC0CH15( void );
void Dma_INTSDMAC1CH0( void );
void Dma_INTSDMAC1CH1( void );
void Dma_INTSDMAC1CH2( void );
void Dma_INTSDMAC1CH3( void );
void Dma_INTSDMAC1CH4( void );
void Dma_INTSDMAC1CH5( void );
void Dma_INTSDMAC1CH6( void );
void Dma_INTSDMAC1CH7( void );
void Dma_INTSDMAC1CH8( void );
void Dma_INTSDMAC1CH9( void );
void Dma_INTSDMAC1CH10( void );
void Dma_INTSDMAC1CH11( void );
void Dma_INTSDMAC1CH12( void );
void Dma_INTSDMAC1CH13( void );
void Dma_INTSDMAC1CH14( void );
void Dma_INTSDMAC1CH15( void );

#endif /* DMA_H */
/*-- End Of File -------------------------------------------------------*/
