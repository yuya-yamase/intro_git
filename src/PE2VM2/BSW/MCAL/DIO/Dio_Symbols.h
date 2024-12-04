/* DIO-r04-303 */
/************************************************************************************************/
/*																								*/
/*		DIO Driver																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
#ifndef DIO_SYMBOLS_H
#define DIO_SYMBOLS_H

#include "Mcal_SpalCmn.h"

#if ( MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A )

/*==============================================================================================*/
/* defines																						*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/* U2A DIO Channel ID Symbols																	*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_ID_PORT0_CH0		((Dio_ChannelType)0U)		/* PORT0 CH0	*/
#define DIO_ID_PORT0_CH1		((Dio_ChannelType)1U)		/* PORT0 CH1	*/
#define DIO_ID_PORT0_CH2		((Dio_ChannelType)2U)		/* PORT0 CH2	*/
#define DIO_ID_PORT0_CH3		((Dio_ChannelType)3U)		/* PORT0 CH3	*/
#define DIO_ID_PORT0_CH4		((Dio_ChannelType)4U)		/* PORT0 CH4	*/
#define DIO_ID_PORT0_CH5		((Dio_ChannelType)5U)		/* PORT0 CH5	*/
#define DIO_ID_PORT0_CH6		((Dio_ChannelType)6U)		/* PORT0 CH6	*/
#define DIO_ID_PORT0_CH7		((Dio_ChannelType)7U)		/* PORT0 CH7	*/
#define DIO_ID_PORT0_CH8		((Dio_ChannelType)8U)		/* PORT0 CH8	*/
#define DIO_ID_PORT0_CH9		((Dio_ChannelType)9U)		/* PORT0 CH9	*/
#define DIO_ID_PORT0_CH10		((Dio_ChannelType)10U)		/* PORT0 CH10	*/
#define DIO_ID_PORT0_CH11		((Dio_ChannelType)11U)		/* PORT0 CH11	*/
#define DIO_ID_PORT0_CH12		((Dio_ChannelType)12U)		/* PORT0 CH12	*/
#define DIO_ID_PORT1_CH0		((Dio_ChannelType)13U)		/* PORT1 CH0	*/
#define DIO_ID_PORT1_CH1		((Dio_ChannelType)14U)		/* PORT1 CH1	*/
#define DIO_ID_PORT1_CH2		((Dio_ChannelType)15U)		/* PORT1 CH2	*/
#define DIO_ID_PORT1_CH3		((Dio_ChannelType)16U)		/* PORT1 CH3	*/
#define DIO_ID_PORT1_CH4		((Dio_ChannelType)17U)		/* PORT1 CH4	*/
#define DIO_ID_PORT1_CH5		((Dio_ChannelType)18U)		/* PORT1 CH5	*/
#define DIO_ID_PORT1_CH6		((Dio_ChannelType)19U)		/* PORT1 CH6	*/
#define DIO_ID_PORT1_CH7		((Dio_ChannelType)20U)		/* PORT1 CH7	*/
#define DIO_ID_PORT1_CH8		((Dio_ChannelType)21U)		/* PORT1 CH8	*/
#define DIO_ID_PORT1_CH9		((Dio_ChannelType)22U)		/* PORT1 CH9	*/
#define DIO_ID_PORT1_CH10		((Dio_ChannelType)23U)		/* PORT1 CH10	*/
#define DIO_ID_PORT1_CH11		((Dio_ChannelType)24U)		/* PORT1 CH11	*/
#define DIO_ID_PORT1_CH12		((Dio_ChannelType)25U)		/* PORT1 CH12	*/
#define DIO_ID_PORT1_CH13		((Dio_ChannelType)26U)		/* PORT1 CH13	*/
#define DIO_ID_PORT1_CH14		((Dio_ChannelType)27U)		/* PORT1 CH14	*/
#define DIO_ID_PORT1_CH15		((Dio_ChannelType)28U)		/* PORT1 CH15	*/
#define DIO_ID_PORT2_CH0		((Dio_ChannelType)29U)		/* PORT2 CH0	*/
#define DIO_ID_PORT2_CH1		((Dio_ChannelType)30U)		/* PORT2 CH1	*/
#define DIO_ID_PORT2_CH2		((Dio_ChannelType)31U)		/* PORT2 CH2	*/
#define DIO_ID_PORT2_CH3		((Dio_ChannelType)32U)		/* PORT2 CH3	*/
#define DIO_ID_PORT2_CH4		((Dio_ChannelType)33U)		/* PORT2 CH4	*/
#define DIO_ID_PORT2_CH5		((Dio_ChannelType)34U)		/* PORT2 CH5	*/
#define DIO_ID_PORT2_CH6		((Dio_ChannelType)35U)		/* PORT2 CH6	*/
#define DIO_ID_PORT2_CH7		((Dio_ChannelType)36U)		/* PORT2 CH7	*/
#define DIO_ID_PORT2_CH8		((Dio_ChannelType)37U)		/* PORT2 CH8	*/
#define DIO_ID_PORT2_CH9		((Dio_ChannelType)38U)		/* PORT2 CH9	*/
#define DIO_ID_PORT2_CH10		((Dio_ChannelType)39U)		/* PORT2 CH10	*/
#define DIO_ID_PORT2_CH11		((Dio_ChannelType)40U)		/* PORT2 CH11	*/
#define DIO_ID_PORT2_CH12		((Dio_ChannelType)41U)		/* PORT2 CH12	*/
#define DIO_ID_PORT2_CH13		((Dio_ChannelType)42U)		/* PORT2 CH13	*/
#define DIO_ID_PORT2_CH14		((Dio_ChannelType)43U)		/* PORT2 CH14	*/
#define DIO_ID_PORT2_CH15		((Dio_ChannelType)44U)		/* PORT2 CH15	*/
#define DIO_ID_PORT3_CH0		((Dio_ChannelType)45U)		/* PORT3 CH0	*/
#define DIO_ID_PORT3_CH1		((Dio_ChannelType)46U)		/* PORT3 CH1	*/
#define DIO_ID_PORT3_CH2		((Dio_ChannelType)47U)		/* PORT3 CH2	*/
#define DIO_ID_PORT3_CH3		((Dio_ChannelType)48U)		/* PORT3 CH3	*/
#define DIO_ID_PORT3_CH4		((Dio_ChannelType)49U)		/* PORT3 CH4	*/
#define DIO_ID_PORT3_CH5		((Dio_ChannelType)50U)		/* PORT3 CH5	*/
#define DIO_ID_PORT3_CH6		((Dio_ChannelType)51U)		/* PORT3 CH6	*/
#define DIO_ID_PORT3_CH7		((Dio_ChannelType)52U)		/* PORT3 CH7	*/
#define DIO_ID_PORT3_CH8		((Dio_ChannelType)53U)		/* PORT3 CH8	*/
#define DIO_ID_PORT3_CH9		((Dio_ChannelType)54U)		/* PORT3 CH9	*/
#define DIO_ID_PORT3_CH10		((Dio_ChannelType)55U)		/* PORT3 CH10	*/
#define DIO_ID_PORT3_CH11		((Dio_ChannelType)56U)		/* PORT3 CH11	*/
#define DIO_ID_PORT3_CH12		((Dio_ChannelType)57U)		/* PORT3 CH12	*/
#define DIO_ID_PORT3_CH13		((Dio_ChannelType)58U)		/* PORT3 CH13	*/
#define DIO_ID_PORT3_CH14		((Dio_ChannelType)59U)		/* PORT3 CH14	*/
#define DIO_ID_PORT3_CH15		((Dio_ChannelType)60U)		/* PORT3 CH15	*/
#define DIO_ID_PORT4_CH0		((Dio_ChannelType)61U)		/* PORT4 CH0	*/
#define DIO_ID_PORT4_CH1		((Dio_ChannelType)62U)		/* PORT4 CH1	*/
#define DIO_ID_PORT4_CH2		((Dio_ChannelType)63U)		/* PORT4 CH2	*/
#define DIO_ID_PORT4_CH3		((Dio_ChannelType)64U)		/* PORT4 CH3	*/
#define DIO_ID_PORT4_CH4		((Dio_ChannelType)65U)		/* PORT4 CH4	*/
#define DIO_ID_PORT4_CH5		((Dio_ChannelType)66U)		/* PORT4 CH5	*/
#define DIO_ID_PORT4_CH6		((Dio_ChannelType)67U)		/* PORT4 CH6	*/
#define DIO_ID_PORT4_CH7		((Dio_ChannelType)68U)		/* PORT4 CH7	*/
#define DIO_ID_PORT4_CH8		((Dio_ChannelType)69U)		/* PORT4 CH8	*/
#define DIO_ID_PORT4_CH9		((Dio_ChannelType)70U)		/* PORT4 CH9	*/
#define DIO_ID_PORT4_CH10		((Dio_ChannelType)71U)		/* PORT4 CH10	*/
#define DIO_ID_PORT4_CH11		((Dio_ChannelType)72U)		/* PORT4 CH11	*/
#define DIO_ID_PORT4_CH12		((Dio_ChannelType)73U)		/* PORT4 CH12	*/
#define DIO_ID_PORT4_CH13		((Dio_ChannelType)74U)		/* PORT4 CH13	*/
#define DIO_ID_PORT4_CH14		((Dio_ChannelType)75U)		/* PORT4 CH14	*/
#define DIO_ID_PORT4_CH15		((Dio_ChannelType)76U)		/* PORT4 CH15	*/
#define DIO_ID_PORT5_CH2		((Dio_ChannelType)77U)		/* PORT5 CH2	*/
#define DIO_ID_PORT5_CH3		((Dio_ChannelType)78U)		/* PORT5 CH3	*/
#define DIO_ID_PORT5_CH4		((Dio_ChannelType)79U)		/* PORT5 CH4	*/
#define DIO_ID_PORT5_CH6		((Dio_ChannelType)80U)		/* PORT5 CH6	*/
#define DIO_ID_PORT6_CH0		((Dio_ChannelType)81U)		/* PORT6 CH0	*/
#define DIO_ID_PORT6_CH2		((Dio_ChannelType)82U)		/* PORT6 CH2	*/
#define DIO_ID_PORT6_CH3		((Dio_ChannelType)83U)		/* PORT6 CH3	*/
#define DIO_ID_PORT6_CH4		((Dio_ChannelType)84U)		/* PORT6 CH4	*/
#define DIO_ID_PORT6_CH5		((Dio_ChannelType)85U)		/* PORT6 CH5	*/
#define DIO_ID_PORT6_CH6		((Dio_ChannelType)86U)		/* PORT6 CH6	*/
#define DIO_ID_PORT6_CH7		((Dio_ChannelType)87U)		/* PORT6 CH7	*/
#define DIO_ID_PORT6_CH8		((Dio_ChannelType)88U)		/* PORT6 CH8	*/
#define DIO_ID_PORT6_CH9		((Dio_ChannelType)89U)		/* PORT6 CH9	*/
#define DIO_ID_PORT6_CH10		((Dio_ChannelType)90U)		/* PORT6 CH10	*/
#define DIO_ID_PORT6_CH11		((Dio_ChannelType)91U)		/* PORT6 CH11	*/
#define DIO_ID_PORT6_CH12		((Dio_ChannelType)92U)		/* PORT6 CH12	*/
#define DIO_ID_PORT6_CH13		((Dio_ChannelType)93U)		/* PORT6 CH13	*/
#define DIO_ID_PORT6_CH14		((Dio_ChannelType)94U)		/* PORT6 CH14	*/
#define DIO_ID_PORT6_CH15		((Dio_ChannelType)95U)		/* PORT6 CH15	*/
#define DIO_ID_PORT8_CH0		((Dio_ChannelType)96U)		/* PORT8 CH0	*/
#define DIO_ID_PORT8_CH1		((Dio_ChannelType)97U)		/* PORT8 CH1	*/
#define DIO_ID_PORT8_CH2		((Dio_ChannelType)98U)		/* PORT8 CH2	*/
#define DIO_ID_PORT8_CH3		((Dio_ChannelType)99U)		/* PORT8 CH3	*/
#define DIO_ID_PORT8_CH4		((Dio_ChannelType)100U)		/* PORT8 CH4	*/
#define DIO_ID_PORT8_CH5		((Dio_ChannelType)101U)		/* PORT8 CH5	*/
#define DIO_ID_PORT8_CH6		((Dio_ChannelType)102U)		/* PORT8 CH6	*/
#define DIO_ID_PORT8_CH7		((Dio_ChannelType)103U)		/* PORT8 CH7	*/
#define DIO_ID_PORT8_CH8		((Dio_ChannelType)104U)		/* PORT8 CH8	*/
#define DIO_ID_PORT8_CH9		((Dio_ChannelType)105U)		/* PORT8 CH9	*/
#define DIO_ID_PORT8_CH10		((Dio_ChannelType)106U)		/* PORT8 CH10	*/
#define DIO_ID_PORT9_CH0		((Dio_ChannelType)107U)		/* PORT9 CH0	*/
#define DIO_ID_PORT9_CH1		((Dio_ChannelType)108U)		/* PORT9 CH1	*/
#define DIO_ID_PORT9_CH2		((Dio_ChannelType)109U)		/* PORT9 CH2	*/
#define DIO_ID_PORT9_CH3		((Dio_ChannelType)110U)		/* PORT9 CH3	*/
#define DIO_ID_PORT9_CH4		((Dio_ChannelType)111U)		/* PORT9 CH4	*/
#define DIO_ID_PORT9_CH5		((Dio_ChannelType)112U)		/* PORT9 CH5	*/
#define DIO_ID_PORT9_CH6		((Dio_ChannelType)113U)		/* PORT9 CH6	*/
#define DIO_ID_PORT9_CH7		((Dio_ChannelType)114U)		/* PORT9 CH7	*/
#define DIO_ID_PORT9_CH8		((Dio_ChannelType)115U)		/* PORT9 CH8	*/
#define DIO_ID_PORT10_CH0		((Dio_ChannelType)116U)		/* PORT10 CH0	*/
#define DIO_ID_PORT10_CH1		((Dio_ChannelType)117U)		/* PORT10 CH1	*/
#define DIO_ID_PORT10_CH2		((Dio_ChannelType)118U)		/* PORT10 CH2	*/
#define DIO_ID_PORT10_CH3		((Dio_ChannelType)119U)		/* PORT10 CH3	*/
#define DIO_ID_PORT10_CH4		((Dio_ChannelType)120U)		/* PORT10 CH4	*/
#define DIO_ID_PORT10_CH5		((Dio_ChannelType)121U)		/* PORT10 CH5	*/
#define DIO_ID_PORT10_CH6		((Dio_ChannelType)122U)		/* PORT10 CH6	*/
#define DIO_ID_PORT10_CH7		((Dio_ChannelType)123U)		/* PORT10 CH7	*/
#define DIO_ID_PORT10_CH8		((Dio_ChannelType)124U)		/* PORT10 CH8	*/
#define DIO_ID_PORT10_CH9		((Dio_ChannelType)125U)		/* PORT10 CH9	*/
#define DIO_ID_PORT10_CH10		((Dio_ChannelType)126U)		/* PORT10 CH10	*/
#define DIO_ID_PORT10_CH11		((Dio_ChannelType)127U)		/* PORT10 CH11	*/
#define DIO_ID_PORT10_CH12		((Dio_ChannelType)128U)		/* PORT10 CH12	*/
#define DIO_ID_PORT10_CH13		((Dio_ChannelType)129U)		/* PORT10 CH13	*/
#define DIO_ID_PORT10_CH14		((Dio_ChannelType)130U)		/* PORT10 CH14	*/
#define DIO_ID_PORT11_CH0		((Dio_ChannelType)131U)		/* PORT11 CH0	*/
#define DIO_ID_PORT11_CH1		((Dio_ChannelType)132U)		/* PORT11 CH1	*/
#define DIO_ID_PORT11_CH2		((Dio_ChannelType)133U)		/* PORT11 CH2	*/
#define DIO_ID_PORT11_CH3		((Dio_ChannelType)134U)		/* PORT11 CH3	*/
#define DIO_ID_PORT11_CH4		((Dio_ChannelType)135U)		/* PORT11 CH4	*/
#define DIO_ID_PORT11_CH5		((Dio_ChannelType)136U)		/* PORT11 CH5	*/
#define DIO_ID_PORT11_CH6		((Dio_ChannelType)137U)		/* PORT11 CH6	*/
#define DIO_ID_PORT11_CH7		((Dio_ChannelType)138U)		/* PORT11 CH7	*/
#define DIO_ID_PORT11_CH8		((Dio_ChannelType)139U)		/* PORT11 CH8	*/
#define DIO_ID_PORT11_CH9		((Dio_ChannelType)140U)		/* PORT11 CH9	*/
#define DIO_ID_PORT11_CH10		((Dio_ChannelType)141U)		/* PORT11 CH10	*/
#define DIO_ID_PORT11_CH11		((Dio_ChannelType)142U)		/* PORT11 CH11	*/
#define DIO_ID_PORT11_CH12		((Dio_ChannelType)143U)		/* PORT11 CH12	*/
#define DIO_ID_PORT11_CH13		((Dio_ChannelType)144U)		/* PORT11 CH13	*/
#define DIO_ID_PORT11_CH14		((Dio_ChannelType)145U)		/* PORT11 CH14	*/
#define DIO_ID_PORT11_CH15		((Dio_ChannelType)146U)		/* PORT11 CH15	*/
#define DIO_ID_PORT12_CH0		((Dio_ChannelType)147U)		/* PORT12 CH0	*/
#define DIO_ID_PORT12_CH1		((Dio_ChannelType)148U)		/* PORT12 CH1	*/
#define DIO_ID_PORT12_CH2		((Dio_ChannelType)149U)		/* PORT12 CH2	*/
#define DIO_ID_PORT12_CH3		((Dio_ChannelType)150U)		/* PORT12 CH3	*/
#define DIO_ID_PORT12_CH4		((Dio_ChannelType)151U)		/* PORT12 CH4	*/
#define DIO_ID_PORT12_CH5		((Dio_ChannelType)152U)		/* PORT12 CH5	*/
#define DIO_ID_PORT17_CH0		((Dio_ChannelType)153U)		/* PORT17 CH0	*/
#define DIO_ID_PORT17_CH1		((Dio_ChannelType)154U)		/* PORT17 CH1	*/
#define DIO_ID_PORT17_CH2		((Dio_ChannelType)155U)		/* PORT17 CH2	*/
#define DIO_ID_PORT17_CH3		((Dio_ChannelType)156U)		/* PORT17 CH3	*/
#define DIO_ID_PORT17_CH4		((Dio_ChannelType)157U)		/* PORT17 CH4	*/
#define DIO_ID_PORT17_CH5		((Dio_ChannelType)158U)		/* PORT17 CH5	*/
#define DIO_ID_PORT17_CH6		((Dio_ChannelType)159U)		/* PORT17 CH6	*/
#define DIO_ID_PORT18_CH0		((Dio_ChannelType)160U)		/* PORT18 CH0	*/
#define DIO_ID_PORT18_CH1		((Dio_ChannelType)161U)		/* PORT18 CH1	*/
#define DIO_ID_PORT18_CH2		((Dio_ChannelType)162U)		/* PORT18 CH2	*/
#define DIO_ID_PORT18_CH3		((Dio_ChannelType)163U)		/* PORT18 CH3	*/
#define DIO_ID_PORT18_CH4		((Dio_ChannelType)164U)		/* PORT18 CH4	*/
#define DIO_ID_PORT18_CH5		((Dio_ChannelType)165U)		/* PORT18 CH5	*/
#define DIO_ID_PORT18_CH6		((Dio_ChannelType)166U)		/* PORT18 CH6	*/
#define DIO_ID_PORT18_CH7		((Dio_ChannelType)167U)		/* PORT18 CH7	*/
#define DIO_ID_PORT18_CH8		((Dio_ChannelType)168U)		/* PORT18 CH8	*/
#define DIO_ID_PORT18_CH9		((Dio_ChannelType)169U)		/* PORT18 CH9	*/
#define DIO_ID_PORT18_CH10		((Dio_ChannelType)170U)		/* PORT18 CH10	*/
#define DIO_ID_PORT18_CH11		((Dio_ChannelType)171U)		/* PORT18 CH11	*/
#define DIO_ID_PORT18_CH12		((Dio_ChannelType)172U)		/* PORT18 CH12	*/
#define DIO_ID_PORT18_CH13		((Dio_ChannelType)173U)		/* PORT18 CH13	*/
#define DIO_ID_PORT18_CH14		((Dio_ChannelType)174U)		/* PORT18 CH14	*/
#define DIO_ID_PORT18_CH15		((Dio_ChannelType)175U)		/* PORT18 CH15	*/
#define DIO_ID_PORT19_CH0		((Dio_ChannelType)176U)		/* PORT19 CH0	*/
#define DIO_ID_PORT19_CH1		((Dio_ChannelType)177U)		/* PORT19 CH1	*/
#define DIO_ID_PORT19_CH2		((Dio_ChannelType)178U)		/* PORT19 CH2	*/
#define DIO_ID_PORT19_CH3		((Dio_ChannelType)179U)		/* PORT19 CH3	*/
#define DIO_ID_PORT19_CH4		((Dio_ChannelType)180U)		/* PORT19 CH4	*/
#define DIO_ID_PORT19_CH5		((Dio_ChannelType)181U)		/* PORT19 CH5	*/
#define DIO_ID_PORT20_CH0		((Dio_ChannelType)182U)		/* PORT20 CH0	*/
#define DIO_ID_PORT20_CH1		((Dio_ChannelType)183U)		/* PORT20 CH1	*/
#define DIO_ID_PORT20_CH2		((Dio_ChannelType)184U)		/* PORT20 CH2	*/
#define DIO_ID_PORT20_CH3		((Dio_ChannelType)185U)		/* PORT20 CH3	*/
#define DIO_ID_PORT20_CH4		((Dio_ChannelType)186U)		/* PORT20 CH4	*/
#define DIO_ID_PORT20_CH5		((Dio_ChannelType)187U)		/* PORT20 CH5	*/
#define DIO_ID_PORT20_CH6		((Dio_ChannelType)188U)		/* PORT20 CH6	*/
#define DIO_ID_PORT20_CH7		((Dio_ChannelType)189U)		/* PORT20 CH7	*/
#define DIO_ID_PORT20_CH8		((Dio_ChannelType)190U)		/* PORT20 CH8	*/
#define DIO_ID_PORT20_CH9		((Dio_ChannelType)191U)		/* PORT20 CH9	*/
#define DIO_ID_PORT20_CH10		((Dio_ChannelType)192U)		/* PORT20 CH10	*/
#define DIO_ID_PORT20_CH12		((Dio_ChannelType)193U)		/* PORT20 CH12	*/
#define DIO_ID_PORT20_CH13		((Dio_ChannelType)194U)		/* PORT20 CH13	*/
#define DIO_ID_PORT20_CH14		((Dio_ChannelType)195U)		/* PORT20 CH14	*/
#define DIO_ID_PORT20_CH15		((Dio_ChannelType)196U)		/* PORT20 CH15	*/
#define DIO_ID_PORT21_CH0		((Dio_ChannelType)197U)		/* PORT21 CH0	*/
#define DIO_ID_PORT21_CH1		((Dio_ChannelType)198U)		/* PORT21 CH1	*/
#define DIO_ID_PORT21_CH2		((Dio_ChannelType)199U)		/* PORT21 CH2	*/
#define DIO_ID_PORT21_CH3		((Dio_ChannelType)200U)		/* PORT21 CH3	*/
#define DIO_ID_PORT21_CH4		((Dio_ChannelType)201U)		/* PORT21 CH4	*/
#define DIO_ID_PORT21_CH5		((Dio_ChannelType)202U)		/* PORT21 CH5	*/
#define DIO_ID_PORT21_CH6		((Dio_ChannelType)203U)		/* PORT21 CH6	*/
#define DIO_ID_PORT21_CH7		((Dio_ChannelType)204U)		/* PORT21 CH7	*/
#define DIO_ID_PORT21_CH12		((Dio_ChannelType)205U)		/* PORT21 CH12	*/
#define DIO_ID_PORT21_CH13		((Dio_ChannelType)206U)		/* PORT21 CH13	*/
#define DIO_ID_PORT22_CH0		((Dio_ChannelType)207U)		/* PORT22 CH0	*/
#define DIO_ID_PORT22_CH1		((Dio_ChannelType)208U)		/* PORT22 CH1	*/
#define DIO_ID_PORT22_CH2		((Dio_ChannelType)209U)		/* PORT22 CH2	*/
#define DIO_ID_PORT22_CH3		((Dio_ChannelType)210U)		/* PORT22 CH3	*/
#define DIO_ID_PORT22_CH4		((Dio_ChannelType)211U)		/* PORT22 CH4	*/
#define DIO_ID_PORT23_CH0		((Dio_ChannelType)212U)		/* PORT23 CH0	*/
#define DIO_ID_PORT23_CH1		((Dio_ChannelType)213U)		/* PORT23 CH1	*/
#define DIO_ID_PORT23_CH2		((Dio_ChannelType)214U)		/* PORT23 CH2	*/
#define DIO_ID_PORT23_CH3		((Dio_ChannelType)215U)		/* PORT23 CH3	*/
#define DIO_ID_PORT23_CH4		((Dio_ChannelType)216U)		/* PORT23 CH4	*/
#define DIO_ID_PORT23_CH5		((Dio_ChannelType)217U)		/* PORT23 CH5	*/
#define DIO_ID_PORT23_CH6		((Dio_ChannelType)218U)		/* PORT23 CH6	*/
#define DIO_ID_PORT23_CH7		((Dio_ChannelType)219U)		/* PORT23 CH7	*/
#define DIO_ID_PORT23_CH8		((Dio_ChannelType)220U)		/* PORT23 CH8	*/
#define DIO_ID_PORT23_CH9		((Dio_ChannelType)221U)		/* PORT23 CH9	*/
#define DIO_ID_PORT23_CH10		((Dio_ChannelType)222U)		/* PORT23 CH10	*/
#define DIO_ID_PORT23_CH11		((Dio_ChannelType)223U)		/* PORT23 CH11	*/
#define DIO_ID_PORT23_CH12		((Dio_ChannelType)224U)		/* PORT23 CH12	*/
#define DIO_ID_PORT23_CH13		((Dio_ChannelType)225U)		/* PORT23 CH13	*/
#define DIO_ID_PORT24_CH4		((Dio_ChannelType)226U)		/* PORT24 CH4	*/
#define DIO_ID_PORT24_CH5		((Dio_ChannelType)227U)		/* PORT24 CH5	*/
#define DIO_ID_PORT24_CH6		((Dio_ChannelType)228U)		/* PORT24 CH6	*/
#define DIO_ID_PORT24_CH7		((Dio_ChannelType)229U)		/* PORT24 CH7	*/
#define DIO_ID_PORT24_CH8		((Dio_ChannelType)230U)		/* PORT24 CH8	*/
#define DIO_ID_PORT24_CH9		((Dio_ChannelType)231U)		/* PORT24 CH9	*/
#define DIO_ID_PORT24_CH10		((Dio_ChannelType)232U)		/* PORT24 CH10	*/
#define DIO_ID_PORT24_CH11		((Dio_ChannelType)233U)		/* PORT24 CH11	*/
#define DIO_ID_PORT24_CH12		((Dio_ChannelType)234U)		/* PORT24 CH12	*/
#define DIO_ID_PORT24_CH13		((Dio_ChannelType)235U)		/* PORT24 CH13	*/
#define DIO_ID_APORT0_CH0		((Dio_ChannelType)236U)		/* APORT0 CH0	*/
#define DIO_ID_APORT0_CH1		((Dio_ChannelType)237U)		/* APORT0 CH1	*/
#define DIO_ID_APORT0_CH2		((Dio_ChannelType)238U)		/* APORT0 CH2	*/
#define DIO_ID_APORT0_CH3		((Dio_ChannelType)239U)		/* APORT0 CH3	*/
#define DIO_ID_APORT0_CH4		((Dio_ChannelType)240U)		/* APORT0 CH4	*/
#define DIO_ID_APORT0_CH5		((Dio_ChannelType)241U)		/* APORT0 CH5	*/
#define DIO_ID_APORT0_CH6		((Dio_ChannelType)242U)		/* APORT0 CH6	*/
#define DIO_ID_APORT0_CH7		((Dio_ChannelType)243U)		/* APORT0 CH7	*/
#define DIO_ID_APORT0_CH8		((Dio_ChannelType)244U)		/* APORT0 CH8	*/
#define DIO_ID_APORT0_CH9		((Dio_ChannelType)245U)		/* APORT0 CH9	*/
#define DIO_ID_APORT0_CH10		((Dio_ChannelType)246U)		/* APORT0 CH10	*/
#define DIO_ID_APORT0_CH11		((Dio_ChannelType)247U)		/* APORT0 CH11	*/
#define DIO_ID_APORT0_CH12		((Dio_ChannelType)248U)		/* APORT0 CH12	*/
#define DIO_ID_APORT0_CH13		((Dio_ChannelType)249U)		/* APORT0 CH13	*/
#define DIO_ID_APORT0_CH14		((Dio_ChannelType)250U)		/* APORT0 CH14	*/
#define DIO_ID_APORT0_CH15		((Dio_ChannelType)251U)		/* APORT0 CH15	*/
#define DIO_ID_APORT1_CH0		((Dio_ChannelType)252U)		/* APORT1 CH0	*/
#define DIO_ID_APORT1_CH1		((Dio_ChannelType)253U)		/* APORT1 CH1	*/
#define DIO_ID_APORT1_CH2		((Dio_ChannelType)254U)		/* APORT1 CH2	*/
#define DIO_ID_APORT1_CH3		((Dio_ChannelType)255U)		/* APORT1 CH3	*/
#define DIO_ID_APORT2_CH0		((Dio_ChannelType)256U)		/* APORT2 CH0	*/
#define DIO_ID_APORT2_CH1		((Dio_ChannelType)257U)		/* APORT2 CH1	*/
#define DIO_ID_APORT2_CH2		((Dio_ChannelType)258U)		/* APORT2 CH2	*/
#define DIO_ID_APORT2_CH3		((Dio_ChannelType)259U)		/* APORT2 CH3	*/
#define DIO_ID_APORT2_CH4		((Dio_ChannelType)260U)		/* APORT2 CH4	*/
#define DIO_ID_APORT2_CH5		((Dio_ChannelType)261U)		/* APORT2 CH5	*/
#define DIO_ID_APORT2_CH6		((Dio_ChannelType)262U)		/* APORT2 CH6	*/
#define DIO_ID_APORT2_CH7		((Dio_ChannelType)263U)		/* APORT2 CH7	*/
#define DIO_ID_APORT2_CH8		((Dio_ChannelType)264U)		/* APORT2 CH8	*/
#define DIO_ID_APORT2_CH9		((Dio_ChannelType)265U)		/* APORT2 CH9	*/
#define DIO_ID_APORT2_CH10		((Dio_ChannelType)266U)		/* APORT2 CH10	*/
#define DIO_ID_APORT2_CH11		((Dio_ChannelType)267U)		/* APORT2 CH11	*/
#define DIO_ID_APORT2_CH12		((Dio_ChannelType)268U)		/* APORT2 CH12	*/
#define DIO_ID_APORT2_CH13		((Dio_ChannelType)269U)		/* APORT2 CH13	*/
#define DIO_ID_APORT2_CH14		((Dio_ChannelType)270U)		/* APORT2 CH14	*/
#define DIO_ID_APORT2_CH15		((Dio_ChannelType)271U)		/* APORT2 CH15	*/
#define DIO_ID_APORT3_CH0		((Dio_ChannelType)272U)		/* APORT3 CH0	*/
#define DIO_ID_APORT3_CH1		((Dio_ChannelType)273U)		/* APORT3 CH1	*/
#define DIO_ID_APORT3_CH2		((Dio_ChannelType)274U)		/* APORT3 CH2	*/
#define DIO_ID_APORT3_CH3		((Dio_ChannelType)275U)		/* APORT3 CH3	*/
#define DIO_ID_APORT4_CH0		((Dio_ChannelType)276U)		/* APORT4 CH0	*/
#define DIO_ID_APORT4_CH1		((Dio_ChannelType)277U)		/* APORT4 CH1	*/
#define DIO_ID_APORT4_CH2		((Dio_ChannelType)278U)		/* APORT4 CH2	*/
#define DIO_ID_APORT4_CH3		((Dio_ChannelType)279U)		/* APORT4 CH3	*/
#define DIO_ID_APORT4_CH4		((Dio_ChannelType)280U)		/* APORT4 CH4	*/
#define DIO_ID_APORT4_CH5		((Dio_ChannelType)281U)		/* APORT4 CH5	*/
#define DIO_ID_APORT4_CH6		((Dio_ChannelType)282U)		/* APORT4 CH6	*/
#define DIO_ID_APORT4_CH7		((Dio_ChannelType)283U)		/* APORT4 CH7	*/
#define DIO_ID_APORT4_CH8		((Dio_ChannelType)284U)		/* APORT4 CH8	*/
#define DIO_ID_APORT4_CH9		((Dio_ChannelType)285U)		/* APORT4 CH9	*/
#define DIO_ID_APORT4_CH10		((Dio_ChannelType)286U)		/* APORT4 CH10	*/
#define DIO_ID_APORT4_CH11		((Dio_ChannelType)287U)		/* APORT4 CH11	*/
#define DIO_ID_APORT4_CH12		((Dio_ChannelType)288U)		/* APORT4 CH12	*/
#define DIO_ID_APORT4_CH13		((Dio_ChannelType)289U)		/* APORT4 CH13	*/
#define DIO_ID_APORT4_CH14		((Dio_ChannelType)290U)		/* APORT4 CH14	*/
#define DIO_ID_APORT4_CH15		((Dio_ChannelType)291U)		/* APORT4 CH15	*/
#define DIO_ID_APORT5_CH0		((Dio_ChannelType)292U)		/* APORT5 CH0	*/
#define DIO_ID_APORT5_CH1		((Dio_ChannelType)293U)		/* APORT5 CH1	*/
#define DIO_ID_APORT5_CH2		((Dio_ChannelType)294U)		/* APORT5 CH2	*/
#define DIO_ID_APORT5_CH3		((Dio_ChannelType)295U)		/* APORT5 CH3	*/
#define DIO_ID_JPORT0_CH0		((Dio_ChannelType)296U)		/* JPORT0 CH0	*/
#define DIO_ID_JPORT0_CH1		((Dio_ChannelType)297U)		/* JPORT0 CH1	*/
#define DIO_ID_JPORT0_CH2		((Dio_ChannelType)298U)		/* JPORT0 CH2	*/
#define DIO_ID_JPORT0_CH3		((Dio_ChannelType)299U)		/* JPORT0 CH3	*/
#define DIO_ID_JPORT0_CH5		((Dio_ChannelType)300U)		/* JPORT0 CH5	*/

#define DIO_ASSIGN_ID_CH_MAX	((Dio_ChannelType)301U)

/*----------------------------------------------------------------------------------------------*/
/* U2A DIO Port ID Symbols																		*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_ID_PORT0			((Dio_PortType)0U)			/* PORT0		*/
#define DIO_ID_PORT1			((Dio_PortType)1U)			/* PORT1		*/
#define DIO_ID_PORT2			((Dio_PortType)2U)			/* PORT2		*/
#define DIO_ID_PORT3			((Dio_PortType)3U)			/* PORT3		*/
#define DIO_ID_PORT4			((Dio_PortType)4U)			/* PORT4		*/
#define DIO_ID_PORT5			((Dio_PortType)5U)			/* PORT5		*/
#define DIO_ID_PORT6			((Dio_PortType)6U)			/* PORT6		*/
#define DIO_ID_PORT8			((Dio_PortType)7U)			/* PORT8		*/
#define DIO_ID_PORT9			((Dio_PortType)8U)			/* PORT9		*/
#define DIO_ID_PORT10			((Dio_PortType)9U)			/* PORT10		*/
#define DIO_ID_PORT11			((Dio_PortType)10U)			/* PORT11		*/
#define DIO_ID_PORT12			((Dio_PortType)11U)			/* PORT12		*/
#define DIO_ID_PORT17			((Dio_PortType)12U)			/* PORT17		*/
#define DIO_ID_PORT18			((Dio_PortType)13U)			/* PORT18		*/
#define DIO_ID_PORT19			((Dio_PortType)14U)			/* PORT19		*/
#define DIO_ID_PORT20			((Dio_PortType)15U)			/* PORT20		*/
#define DIO_ID_PORT21			((Dio_PortType)16U)			/* PORT21		*/
#define DIO_ID_PORT22			((Dio_PortType)17U)			/* PORT22		*/
#define DIO_ID_PORT23			((Dio_PortType)18U)			/* PORT23		*/
#define DIO_ID_PORT24			((Dio_PortType)19U)			/* PORT24		*/
#define DIO_ID_APORT0			((Dio_PortType)20U)			/* APORT0		*/
#define DIO_ID_APORT1			((Dio_PortType)21U)			/* APORT1		*/
#define DIO_ID_APORT2			((Dio_PortType)22U)			/* APORT2		*/
#define DIO_ID_APORT3			((Dio_PortType)23U)			/* APORT3		*/
#define DIO_ID_APORT4			((Dio_PortType)24U)			/* APORT4		*/
#define DIO_ID_APORT5			((Dio_PortType)25U)			/* APORT5		*/
#define DIO_ID_JPORT0			((Dio_PortType)26U)			/* JPORT0		*/

#define DIO_ASSIGN_ID_PORT_MAX	((Dio_PortType)27U)

#else

/*----------------------------------------------------------------------------------------------*/
/* U2B DIO Channel ID Symbols																	*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_ID_PORT0_CH0		((Dio_ChannelType)0U)		/* PORT0 CH0	*/
#define DIO_ID_PORT0_CH1		((Dio_ChannelType)1U)		/* PORT0 CH1	*/
#define DIO_ID_PORT0_CH2		((Dio_ChannelType)2U)		/* PORT0 CH2	*/
#define DIO_ID_PORT0_CH3		((Dio_ChannelType)3U)		/* PORT0 CH3	*/
#define DIO_ID_PORT0_CH4		((Dio_ChannelType)4U)		/* PORT0 CH4	*/
#define DIO_ID_PORT0_CH5		((Dio_ChannelType)5U)		/* PORT0 CH5	*/
#define DIO_ID_PORT0_CH6		((Dio_ChannelType)6U)		/* PORT0 CH6	*/
#define DIO_ID_PORT0_CH7		((Dio_ChannelType)7U)		/* PORT0 CH7	*/
#define DIO_ID_PORT2_CH0		((Dio_ChannelType)8U)		/* PORT2 CH0	*/
#define DIO_ID_PORT2_CH1		((Dio_ChannelType)9U)		/* PORT2 CH1	*/
#define DIO_ID_PORT2_CH2		((Dio_ChannelType)10U)		/* PORT2 CH2	*/
#define DIO_ID_PORT2_CH3		((Dio_ChannelType)11U)		/* PORT2 CH3	*/
#define DIO_ID_PORT2_CH4		((Dio_ChannelType)12U)		/* PORT2 CH4	*/
#define DIO_ID_PORT2_CH5		((Dio_ChannelType)13U)		/* PORT2 CH5	*/
#define DIO_ID_PORT2_CH6		((Dio_ChannelType)14U)		/* PORT2 CH6	*/
#define DIO_ID_PORT2_CH7		((Dio_ChannelType)15U)		/* PORT2 CH7	*/
#define DIO_ID_PORT2_CH8		((Dio_ChannelType)16U)		/* PORT2 CH8	*/
#define DIO_ID_PORT2_CH9		((Dio_ChannelType)17U)		/* PORT2 CH9	*/
#define DIO_ID_PORT2_CH10		((Dio_ChannelType)18U)		/* PORT2 CH10	*/
#define DIO_ID_PORT10_CH0		((Dio_ChannelType)19U)		/* PORT10 CH0	*/
#define DIO_ID_PORT10_CH1		((Dio_ChannelType)20U)		/* PORT10 CH1	*/
#define DIO_ID_PORT10_CH2		((Dio_ChannelType)21U)		/* PORT10 CH2	*/
#define DIO_ID_PORT10_CH3		((Dio_ChannelType)22U)		/* PORT10 CH3	*/
#define DIO_ID_PORT10_CH4		((Dio_ChannelType)23U)		/* PORT10 CH4	*/
#define DIO_ID_PORT10_CH5		((Dio_ChannelType)24U)		/* PORT10 CH5	*/
#define DIO_ID_PORT10_CH6		((Dio_ChannelType)25U)		/* PORT10 CH6	*/
#define DIO_ID_PORT10_CH7		((Dio_ChannelType)26U)		/* PORT10 CH7	*/
#define DIO_ID_PORT10_CH8		((Dio_ChannelType)27U)		/* PORT10 CH8	*/
#define DIO_ID_PORT11_CH0		((Dio_ChannelType)28U)		/* PORT11 CH0	*/
#define DIO_ID_PORT11_CH1		((Dio_ChannelType)29U)		/* PORT11 CH1	*/
#define DIO_ID_PORT11_CH2		((Dio_ChannelType)30U)		/* PORT11 CH2	*/
#define DIO_ID_PORT11_CH3		((Dio_ChannelType)31U)		/* PORT11 CH3	*/
#define DIO_ID_PORT11_CH4		((Dio_ChannelType)32U)		/* PORT11 CH4	*/
#define DIO_ID_PORT11_CH5		((Dio_ChannelType)33U)		/* PORT11 CH5	*/
#define DIO_ID_PORT11_CH6		((Dio_ChannelType)34U)		/* PORT11 CH6	*/
#define DIO_ID_PORT11_CH7		((Dio_ChannelType)35U)		/* PORT11 CH7	*/
#define DIO_ID_PORT11_CH8		((Dio_ChannelType)36U)		/* PORT11 CH8	*/
#define DIO_ID_PORT11_CH9		((Dio_ChannelType)37U)		/* PORT11 CH9	*/
#define DIO_ID_PORT11_CH10		((Dio_ChannelType)38U)		/* PORT11 CH10	*/
#define DIO_ID_PORT12_CH0		((Dio_ChannelType)39U)		/* PORT12 CH0	*/
#define DIO_ID_PORT12_CH1		((Dio_ChannelType)40U)		/* PORT12 CH1	*/
#define DIO_ID_PORT12_CH2		((Dio_ChannelType)41U)		/* PORT12 CH2	*/
#define DIO_ID_PORT12_CH3		((Dio_ChannelType)42U)		/* PORT12 CH3	*/
#define DIO_ID_PORT12_CH4		((Dio_ChannelType)43U)		/* PORT12 CH4	*/
#define DIO_ID_PORT12_CH5		((Dio_ChannelType)44U)		/* PORT12 CH5	*/
#define DIO_ID_PORT12_CH6		((Dio_ChannelType)45U)		/* PORT12 CH6	*/
#define DIO_ID_PORT12_CH7		((Dio_ChannelType)46U)		/* PORT12 CH7	*/
#define DIO_ID_PORT12_CH8		((Dio_ChannelType)47U)		/* PORT12 CH8	*/
#define DIO_ID_PORT12_CH9		((Dio_ChannelType)48U)		/* PORT12 CH9	*/
#define DIO_ID_PORT13_CH0		((Dio_ChannelType)49U)		/* PORT13 CH0	*/
#define DIO_ID_PORT13_CH1		((Dio_ChannelType)50U)		/* PORT13 CH1	*/
#define DIO_ID_PORT13_CH2		((Dio_ChannelType)51U)		/* PORT13 CH2	*/
#define DIO_ID_PORT13_CH3		((Dio_ChannelType)52U)		/* PORT13 CH3	*/
#define DIO_ID_PORT14_CH0		((Dio_ChannelType)53U)		/* PORT14 CH0	*/
#define DIO_ID_PORT14_CH1		((Dio_ChannelType)54U)		/* PORT14 CH1	*/
#define DIO_ID_PORT14_CH2		((Dio_ChannelType)55U)		/* PORT14 CH2	*/
#define DIO_ID_PORT14_CH3		((Dio_ChannelType)56U)		/* PORT14 CH3	*/
#define DIO_ID_PORT14_CH4		((Dio_ChannelType)57U)		/* PORT14 CH4	*/
#define DIO_ID_PORT14_CH5		((Dio_ChannelType)58U)		/* PORT14 CH5	*/
#define DIO_ID_PORT20_CH0		((Dio_ChannelType)59U)		/* PORT20 CH0	*/
#define DIO_ID_PORT20_CH1		((Dio_ChannelType)60U)		/* PORT20 CH1	*/
#define DIO_ID_PORT20_CH2		((Dio_ChannelType)61U)		/* PORT20 CH2	*/
#define DIO_ID_PORT20_CH3		((Dio_ChannelType)62U)		/* PORT20 CH3	*/
#define DIO_ID_PORT20_CH4		((Dio_ChannelType)63U)		/* PORT20 CH4	*/
#define DIO_ID_PORT20_CH5		((Dio_ChannelType)64U)		/* PORT20 CH5	*/
#define DIO_ID_PORT20_CH6		((Dio_ChannelType)65U)		/* PORT20 CH6	*/
#define DIO_ID_PORT20_CH7		((Dio_ChannelType)66U)		/* PORT20 CH7	*/
#define DIO_ID_PORT21_CH2		((Dio_ChannelType)67U)		/* PORT21 CH2	*/
#define DIO_ID_PORT21_CH3		((Dio_ChannelType)68U)		/* PORT21 CH3	*/
#define DIO_ID_PORT21_CH4		((Dio_ChannelType)69U)		/* PORT21 CH4	*/
#define DIO_ID_PORT21_CH5		((Dio_ChannelType)70U)		/* PORT21 CH5	*/
#define DIO_ID_PORT22_CH0		((Dio_ChannelType)71U)		/* PORT22 CH0	*/
#define DIO_ID_PORT22_CH1		((Dio_ChannelType)72U)		/* PORT22 CH1	*/
#define DIO_ID_PORT22_CH2		((Dio_ChannelType)73U)		/* PORT22 CH2	*/
#define DIO_ID_PORT22_CH3		((Dio_ChannelType)74U)		/* PORT22 CH3	*/
#define DIO_ID_PORT22_CH4		((Dio_ChannelType)75U)		/* PORT22 CH4	*/
#define DIO_ID_PORT22_CH5		((Dio_ChannelType)76U)		/* PORT22 CH5	*/
#define DIO_ID_PORT22_CH6		((Dio_ChannelType)77U)		/* PORT22 CH6	*/
#define DIO_ID_PORT22_CH7		((Dio_ChannelType)78U)		/* PORT22 CH7	*/
#define DIO_ID_PORT22_CH8		((Dio_ChannelType)79U)		/* PORT22 CH8	*/
#define DIO_ID_PORT22_CH9		((Dio_ChannelType)80U)		/* PORT22 CH9	*/
#define DIO_ID_PORT22_CH10		((Dio_ChannelType)81U)		/* PORT22 CH10	*/
#define DIO_ID_PORT22_CH11		((Dio_ChannelType)82U)		/* PORT22 CH11	*/
#define DIO_ID_PORT22_CH12		((Dio_ChannelType)83U)		/* PORT22 CH12	*/
#define DIO_ID_PORT22_CH13		((Dio_ChannelType)84U)		/* PORT22 CH13	*/
#define DIO_ID_PORT23_CH0		((Dio_ChannelType)85U)		/* PORT23 CH0	*/
#define DIO_ID_PORT23_CH1		((Dio_ChannelType)86U)		/* PORT23 CH1	*/
#define DIO_ID_PORT23_CH2		((Dio_ChannelType)87U)		/* PORT23 CH2	*/
#define DIO_ID_PORT23_CH3		((Dio_ChannelType)88U)		/* PORT23 CH3	*/
#define DIO_ID_PORT23_CH4		((Dio_ChannelType)89U)		/* PORT23 CH4	*/
#define DIO_ID_PORT23_CH5		((Dio_ChannelType)90U)		/* PORT23 CH5	*/
#define DIO_ID_PORT23_CH6		((Dio_ChannelType)91U)		/* PORT23 CH6	*/
#define DIO_ID_PORT23_CH7		((Dio_ChannelType)92U)		/* PORT23 CH7	*/
#define DIO_ID_PORT25_CH2		((Dio_ChannelType)93U)		/* PORT25 CH2	*/
#define DIO_ID_PORT25_CH3		((Dio_ChannelType)94U)		/* PORT25 CH3	*/
#define DIO_ID_PORT25_CH4		((Dio_ChannelType)95U)		/* PORT25 CH4	*/
#define DIO_ID_PORT25_CH5		((Dio_ChannelType)96U)		/* PORT25 CH5	*/
#define DIO_ID_PORT25_CH6		((Dio_ChannelType)97U)		/* PORT25 CH6	*/
#define DIO_ID_PORT27_CH0		((Dio_ChannelType)98U)		/* PORT27 CH0	*/
#define DIO_ID_PORT32_CH0		((Dio_ChannelType)99U)		/* PORT32 CH0	*/
#define DIO_ID_PORT32_CH1		((Dio_ChannelType)100U)		/* PORT32 CH1	*/
#define DIO_ID_PORT32_CH2		((Dio_ChannelType)101U)		/* PORT32 CH2	*/
#define DIO_ID_PORT32_CH3		((Dio_ChannelType)102U)		/* PORT32 CH3	*/
#define DIO_ID_PORT32_CH4		((Dio_ChannelType)103U)		/* PORT32 CH4	*/
#define DIO_ID_PORT32_CH5		((Dio_ChannelType)104U)		/* PORT32 CH5	*/
#define DIO_ID_PORT32_CH6		((Dio_ChannelType)105U)		/* PORT32 CH6	*/
#define DIO_ID_PORT33_CH0		((Dio_ChannelType)106U)		/* PORT33 CH0	*/
#define DIO_ID_PORT33_CH1		((Dio_ChannelType)107U)		/* PORT33 CH1	*/
#define DIO_ID_PORT33_CH2		((Dio_ChannelType)108U)		/* PORT33 CH2	*/
#define DIO_ID_PORT33_CH3		((Dio_ChannelType)109U)		/* PORT33 CH3	*/
#define DIO_ID_PORT33_CH4		((Dio_ChannelType)110U)		/* PORT33 CH4	*/
#define DIO_ID_PORT33_CH5		((Dio_ChannelType)111U)		/* PORT33 CH5	*/
#define DIO_ID_PORT33_CH6		((Dio_ChannelType)112U)		/* PORT33 CH6	*/
#define DIO_ID_PORT33_CH7		((Dio_ChannelType)113U)		/* PORT33 CH7	*/
#define DIO_ID_PORT33_CH8		((Dio_ChannelType)114U)		/* PORT33 CH8	*/
#define DIO_ID_PORT34_CH0		((Dio_ChannelType)115U)		/* PORT34 CH0	*/
#define DIO_ID_PORT34_CH1		((Dio_ChannelType)116U)		/* PORT34 CH1	*/
#define DIO_ID_PORT34_CH2		((Dio_ChannelType)117U)		/* PORT34 CH2	*/
#define DIO_ID_PORT34_CH3		((Dio_ChannelType)118U)		/* PORT34 CH3	*/
#define DIO_ID_PORT34_CH4		((Dio_ChannelType)119U)		/* PORT34 CH4	*/
#define DIO_ID_PORT37_CH0		((Dio_ChannelType)120U)		/* PORT37 CH0	*/
#define DIO_ID_PORT37_CH1		((Dio_ChannelType)121U)		/* PORT37 CH1	*/
#define DIO_ID_PORT37_CH2		((Dio_ChannelType)122U)		/* PORT37 CH2	*/
#define DIO_ID_PORT37_CH3		((Dio_ChannelType)123U)		/* PORT37 CH3	*/
#define DIO_ID_PORT37_CH4		((Dio_ChannelType)124U)		/* PORT37 CH4	*/
#define DIO_ID_PORT37_CH5		((Dio_ChannelType)125U)		/* PORT37 CH5	*/
#define DIO_ID_PORT37_CH6		((Dio_ChannelType)126U)		/* PORT37 CH6	*/
#define DIO_ID_PORT37_CH7		((Dio_ChannelType)127U)		/* PORT37 CH7	*/
#define DIO_ID_PORT37_CH8		((Dio_ChannelType)128U)		/* PORT37 CH8	*/
#define DIO_ID_PORT37_CH9		((Dio_ChannelType)129U)		/* PORT37 CH9	*/
#define DIO_ID_PORT37_CH10		((Dio_ChannelType)130U)		/* PORT37 CH10	*/
#define DIO_ID_PORT37_CH11		((Dio_ChannelType)131U)		/* PORT37 CH11	*/
#define DIO_ID_PORT37_CH12		((Dio_ChannelType)132U)		/* PORT37 CH12	*/
#define DIO_ID_PORT37_CH13		((Dio_ChannelType)133U)		/* PORT37 CH13	*/
#define DIO_ID_PORT37_CH14		((Dio_ChannelType)134U)		/* PORT37 CH14	*/
#define DIO_ID_PORT37_CH15		((Dio_ChannelType)135U)		/* PORT37 CH15	*/
#define DIO_ID_PORT38_CH0		((Dio_ChannelType)136U)		/* PORT38 CH0	*/
#define DIO_ID_PORT38_CH1		((Dio_ChannelType)137U)		/* PORT38 CH1	*/
#define DIO_ID_PORT38_CH2		((Dio_ChannelType)138U)		/* PORT38 CH2	*/
#define DIO_ID_PORT38_CH3		((Dio_ChannelType)139U)		/* PORT38 CH3	*/
#define DIO_ID_PORT38_CH4		((Dio_ChannelType)140U)		/* PORT38 CH4	*/
#define DIO_ID_PORT38_CH5		((Dio_ChannelType)141U)		/* PORT38 CH5	*/
#define DIO_ID_PORT38_CH6		((Dio_ChannelType)142U)		/* PORT38 CH6	*/
#define DIO_ID_PORT38_CH7		((Dio_ChannelType)143U)		/* PORT38 CH7	*/
#define DIO_ID_PORT38_CH8		((Dio_ChannelType)144U)		/* PORT38 CH8	*/
#define DIO_ID_PORT38_CH9		((Dio_ChannelType)145U)		/* PORT38 CH9	*/
#define DIO_ID_PORT38_CH10		((Dio_ChannelType)146U)		/* PORT38 CH10	*/
#define DIO_ID_PORT38_CH11		((Dio_ChannelType)147U)		/* PORT38 CH11	*/
#define DIO_ID_PORT38_CH12		((Dio_ChannelType)148U)		/* PORT38 CH12	*/
#define DIO_ID_PORT38_CH13		((Dio_ChannelType)149U)		/* PORT38 CH13	*/
#define DIO_ID_PORT38_CH14		((Dio_ChannelType)150U)		/* PORT38 CH14	*/
#define DIO_ID_PORT38_CH15		((Dio_ChannelType)151U)		/* PORT38 CH15	*/
#define DIO_ID_PORT40_CH0		((Dio_ChannelType)152U)		/* PORT40 CH0	*/
#define DIO_ID_PORT40_CH1		((Dio_ChannelType)153U)		/* PORT40 CH1	*/
#define DIO_ID_PORT40_CH2		((Dio_ChannelType)154U)		/* PORT40 CH2	*/
#define DIO_ID_PORT40_CH3		((Dio_ChannelType)155U)		/* PORT40 CH3	*/
#define DIO_ID_PORT40_CH4		((Dio_ChannelType)156U)		/* PORT40 CH4	*/
#define DIO_ID_PORT40_CH5		((Dio_ChannelType)157U)		/* PORT40 CH5	*/
#define DIO_ID_PORT40_CH6		((Dio_ChannelType)158U)		/* PORT40 CH6	*/
#define DIO_ID_PORT40_CH7		((Dio_ChannelType)159U)		/* PORT40 CH7	*/
#define DIO_ID_PORT40_CH8		((Dio_ChannelType)160U)		/* PORT40 CH8	*/
#define DIO_ID_PORT40_CH9		((Dio_ChannelType)161U)		/* PORT40 CH9	*/
#define DIO_ID_PORT40_CH10		((Dio_ChannelType)162U)		/* PORT40 CH10	*/
#define DIO_ID_PORT40_CH11		((Dio_ChannelType)163U)		/* PORT40 CH11	*/
#define DIO_ID_PORT40_CH12		((Dio_ChannelType)164U)		/* PORT40 CH12	*/
#define DIO_ID_PORT40_CH13		((Dio_ChannelType)165U)		/* PORT40 CH13	*/
#define DIO_ID_PORT40_CH14		((Dio_ChannelType)166U)		/* PORT40 CH14	*/
#define DIO_ID_PORT40_CH15		((Dio_ChannelType)167U)		/* PORT40 CH15	*/
#define DIO_ID_PORT41_CH0		((Dio_ChannelType)168U)		/* PORT41 CH0	*/
#define DIO_ID_PORT41_CH1		((Dio_ChannelType)169U)		/* PORT41 CH1	*/
#define DIO_ID_PORT41_CH2		((Dio_ChannelType)170U)		/* PORT41 CH2	*/
#define DIO_ID_PORT41_CH3		((Dio_ChannelType)171U)		/* PORT41 CH3	*/
#define DIO_ID_PORT41_CH4		((Dio_ChannelType)172U)		/* PORT41 CH4	*/
#define DIO_ID_PORT41_CH5		((Dio_ChannelType)173U)		/* PORT41 CH5	*/
#define DIO_ID_PORT41_CH6		((Dio_ChannelType)174U)		/* PORT41 CH6	*/
#define DIO_ID_PORT41_CH7		((Dio_ChannelType)175U)		/* PORT41 CH7	*/
#define DIO_ID_PORT41_CH8		((Dio_ChannelType)176U)		/* PORT41 CH8	*/
#define DIO_ID_PORT41_CH9		((Dio_ChannelType)177U)		/* PORT41 CH9	*/
#define DIO_ID_PORT41_CH10		((Dio_ChannelType)178U)		/* PORT41 CH10	*/
#define DIO_ID_PORT41_CH11		((Dio_ChannelType)179U)		/* PORT41 CH11	*/
#define DIO_ID_PORT41_CH12		((Dio_ChannelType)180U)		/* PORT41 CH12	*/
#define DIO_ID_PORT41_CH13		((Dio_ChannelType)181U)		/* PORT41 CH13	*/
#define DIO_ID_PORT41_CH14		((Dio_ChannelType)182U)		/* PORT41 CH14	*/
#define DIO_ID_PORT41_CH15		((Dio_ChannelType)183U)		/* PORT41 CH15	*/
#define DIO_ID_PORT42_CH0		((Dio_ChannelType)184U)		/* PORT42 CH0	*/
#define DIO_ID_PORT42_CH1		((Dio_ChannelType)185U)		/* PORT42 CH1	*/
#define DIO_ID_PORT42_CH2		((Dio_ChannelType)186U)		/* PORT42 CH2	*/
#define DIO_ID_PORT42_CH3		((Dio_ChannelType)187U)		/* PORT42 CH3	*/
#define DIO_ID_PORT42_CH4		((Dio_ChannelType)188U)		/* PORT42 CH4	*/
#define DIO_ID_PORT42_CH5		((Dio_ChannelType)189U)		/* PORT42 CH5	*/
#define DIO_ID_PORT42_CH6		((Dio_ChannelType)190U)		/* PORT42 CH6	*/
#define DIO_ID_PORT42_CH7		((Dio_ChannelType)191U)		/* PORT42 CH7	*/
#define DIO_ID_PORT42_CH8		((Dio_ChannelType)192U)		/* PORT42 CH8	*/
#define DIO_ID_PORT42_CH9		((Dio_ChannelType)193U)		/* PORT42 CH9	*/
#define DIO_ID_PORT42_CH10		((Dio_ChannelType)194U)		/* PORT42 CH10	*/
#define DIO_ID_PORT42_CH11		((Dio_ChannelType)195U)		/* PORT42 CH11	*/
#define DIO_ID_PORT42_CH12		((Dio_ChannelType)196U)		/* PORT42 CH12	*/
#define DIO_ID_PORT42_CH13		((Dio_ChannelType)197U)		/* PORT42 CH13	*/
#define DIO_ID_PORT42_CH14		((Dio_ChannelType)198U)		/* PORT42 CH14	*/
#define DIO_ID_PORT42_CH15		((Dio_ChannelType)199U)		/* PORT42 CH15	*/
#define DIO_ID_PORT43_CH0		((Dio_ChannelType)200U)		/* PORT43 CH0	*/
#define DIO_ID_PORT43_CH1		((Dio_ChannelType)201U)		/* PORT43 CH1	*/
#define DIO_ID_PORT43_CH2		((Dio_ChannelType)202U)		/* PORT43 CH2	*/
#define DIO_ID_PORT43_CH3		((Dio_ChannelType)203U)		/* PORT43 CH3	*/
#define DIO_ID_PORT43_CH4		((Dio_ChannelType)204U)		/* PORT43 CH4	*/
#define DIO_ID_PORT43_CH5		((Dio_ChannelType)205U)		/* PORT43 CH5	*/
#define DIO_ID_PORT43_CH6		((Dio_ChannelType)206U)		/* PORT43 CH6	*/
#define DIO_ID_PORT43_CH7		((Dio_ChannelType)207U)		/* PORT43 CH7	*/
#define DIO_ID_PORT43_CH8		((Dio_ChannelType)208U)		/* PORT43 CH8	*/
#define DIO_ID_PORT43_CH9		((Dio_ChannelType)209U)		/* PORT43 CH9	*/
#define DIO_ID_PORT43_CH10		((Dio_ChannelType)210U)		/* PORT43 CH10	*/
#define DIO_ID_PORT43_CH11		((Dio_ChannelType)211U)		/* PORT43 CH11	*/
#define DIO_ID_PORT43_CH12		((Dio_ChannelType)212U)		/* PORT43 CH12	*/
#define DIO_ID_PORT43_CH13		((Dio_ChannelType)213U)		/* PORT43 CH13	*/
#define DIO_ID_PORT43_CH14		((Dio_ChannelType)214U)		/* PORT43 CH14	*/
#define DIO_ID_PORT43_CH15		((Dio_ChannelType)215U)		/* PORT43 CH15	*/
#define DIO_ID_PORT44_CH0		((Dio_ChannelType)216U)		/* PORT44 CH0	*/
#define DIO_ID_PORT44_CH1		((Dio_ChannelType)217U)		/* PORT44 CH1	*/
#define DIO_ID_PORT44_CH2		((Dio_ChannelType)218U)		/* PORT44 CH2	*/
#define DIO_ID_PORT44_CH3		((Dio_ChannelType)219U)		/* PORT44 CH3	*/
#define DIO_ID_PORT44_CH4		((Dio_ChannelType)220U)		/* PORT44 CH4	*/
#define DIO_ID_PORT44_CH5		((Dio_ChannelType)221U)		/* PORT44 CH5	*/
#define DIO_ID_PORT44_CH6		((Dio_ChannelType)222U)		/* PORT44 CH6	*/
#define DIO_ID_PORT44_CH7		((Dio_ChannelType)223U)		/* PORT44 CH7	*/
#define DIO_ID_PORT44_CH8		((Dio_ChannelType)224U)		/* PORT44 CH8	*/
#define DIO_ID_PORT44_CH9		((Dio_ChannelType)225U)		/* PORT44 CH9	*/
#define DIO_ID_PORT44_CH10		((Dio_ChannelType)226U)		/* PORT44 CH10	*/
#define DIO_ID_PORT44_CH11		((Dio_ChannelType)227U)		/* PORT44 CH11	*/
#define DIO_ID_PORT44_CH12		((Dio_ChannelType)228U)		/* PORT44 CH12	*/
#define DIO_ID_PORT44_CH13		((Dio_ChannelType)229U)		/* PORT44 CH13	*/
#define DIO_ID_PORT44_CH14		((Dio_ChannelType)230U)		/* PORT44 CH14	*/
#define DIO_ID_PORT44_CH15		((Dio_ChannelType)231U)		/* PORT44 CH15	*/
#define DIO_ID_PORT45_CH0		((Dio_ChannelType)232U)		/* PORT45 CH0	*/
#define DIO_ID_PORT45_CH1		((Dio_ChannelType)233U)		/* PORT45 CH1	*/
#define DIO_ID_PORT45_CH2		((Dio_ChannelType)234U)		/* PORT45 CH2	*/
#define DIO_ID_PORT45_CH3		((Dio_ChannelType)235U)		/* PORT45 CH3	*/
#define DIO_ID_PORT45_CH4		((Dio_ChannelType)236U)		/* PORT45 CH4	*/
#define DIO_ID_PORT45_CH5		((Dio_ChannelType)237U)		/* PORT45 CH5	*/
#define DIO_ID_PORT45_CH6		((Dio_ChannelType)238U)		/* PORT45 CH6	*/
#define DIO_ID_PORT45_CH7		((Dio_ChannelType)239U)		/* PORT45 CH7	*/
#define DIO_ID_PORT45_CH8		((Dio_ChannelType)240U)		/* PORT45 CH8	*/
#define DIO_ID_PORT45_CH9		((Dio_ChannelType)241U)		/* PORT45 CH9	*/
#define DIO_ID_PORT45_CH10		((Dio_ChannelType)242U)		/* PORT45 CH10	*/
#define DIO_ID_PORT45_CH11		((Dio_ChannelType)243U)		/* PORT45 CH11	*/
#define DIO_ID_PORT45_CH12		((Dio_ChannelType)244U)		/* PORT45 CH12	*/
#define DIO_ID_PORT45_CH13		((Dio_ChannelType)245U)		/* PORT45 CH13	*/
#define DIO_ID_PORT45_CH14		((Dio_ChannelType)246U)		/* PORT45 CH14	*/
#define DIO_ID_PORT45_CH15		((Dio_ChannelType)247U)		/* PORT45 CH15	*/
#define DIO_ID_PORT46_CH0		((Dio_ChannelType)248U)		/* PORT46 CH0	*/
#define DIO_ID_PORT46_CH1		((Dio_ChannelType)249U)		/* PORT46 CH1	*/
#define DIO_ID_PORT46_CH2		((Dio_ChannelType)250U)		/* PORT46 CH2	*/
#define DIO_ID_PORT46_CH3		((Dio_ChannelType)251U)		/* PORT46 CH3	*/
#define DIO_ID_PORT46_CH4		((Dio_ChannelType)252U)		/* PORT46 CH4	*/
#define DIO_ID_PORT46_CH5		((Dio_ChannelType)253U)		/* PORT46 CH5	*/
#define DIO_ID_PORT46_CH6		((Dio_ChannelType)254U)		/* PORT46 CH6	*/
#define DIO_ID_PORT46_CH7		((Dio_ChannelType)255U)		/* PORT46 CH7	*/
#define DIO_ID_PORT46_CH8		((Dio_ChannelType)256U)		/* PORT46 CH8	*/
#define DIO_ID_PORT46_CH9		((Dio_ChannelType)257U)		/* PORT46 CH9	*/
#define DIO_ID_PORT46_CH10		((Dio_ChannelType)258U)		/* PORT46 CH10	*/
#define DIO_ID_PORT46_CH11		((Dio_ChannelType)259U)		/* PORT46 CH11	*/
#define DIO_ID_PORT46_CH12		((Dio_ChannelType)260U)		/* PORT46 CH12	*/
#define DIO_ID_PORT46_CH13		((Dio_ChannelType)261U)		/* PORT46 CH13	*/
#define DIO_ID_PORT46_CH14		((Dio_ChannelType)262U)		/* PORT46 CH14	*/
#define DIO_ID_PORT46_CH15		((Dio_ChannelType)263U)		/* PORT46 CH15	*/
#define DIO_ID_PORT47_CH0		((Dio_ChannelType)264U)		/* PORT47 CH0	*/
#define DIO_ID_PORT47_CH1		((Dio_ChannelType)265U)		/* PORT47 CH1	*/
#define DIO_ID_PORT47_CH2		((Dio_ChannelType)266U)		/* PORT47 CH2	*/
#define DIO_ID_PORT47_CH3		((Dio_ChannelType)267U)		/* PORT47 CH3	*/
#define DIO_ID_PORT47_CH4		((Dio_ChannelType)268U)		/* PORT47 CH4	*/
#define DIO_ID_PORT47_CH5		((Dio_ChannelType)269U)		/* PORT47 CH5	*/
#define DIO_ID_PORT47_CH6		((Dio_ChannelType)270U)		/* PORT47 CH6	*/
#define DIO_ID_PORT47_CH7		((Dio_ChannelType)271U)		/* PORT47 CH7	*/
#define DIO_ID_PORT47_CH8		((Dio_ChannelType)272U)		/* PORT47 CH8	*/
#define DIO_ID_PORT47_CH9		((Dio_ChannelType)273U)		/* PORT47 CH9	*/
#define DIO_ID_PORT47_CH10		((Dio_ChannelType)274U)		/* PORT47 CH10	*/
#define DIO_ID_PORT47_CH11		((Dio_ChannelType)275U)		/* PORT47 CH11	*/
#define DIO_ID_PORT47_CH12		((Dio_ChannelType)276U)		/* PORT47 CH12	*/
#define DIO_ID_PORT47_CH13		((Dio_ChannelType)277U)		/* PORT47 CH13	*/
#define DIO_ID_PORT47_CH14		((Dio_ChannelType)278U)		/* PORT47 CH14	*/
#define DIO_ID_PORT47_CH15		((Dio_ChannelType)279U)		/* PORT47 CH15	*/
#define DIO_ID_PORT48_CH0		((Dio_ChannelType)280U)		/* PORT48 CH0	*/
#define DIO_ID_PORT48_CH1		((Dio_ChannelType)281U)		/* PORT48 CH1	*/
#define DIO_ID_PORT48_CH2		((Dio_ChannelType)282U)		/* PORT48 CH2	*/
#define DIO_ID_PORT48_CH3		((Dio_ChannelType)283U)		/* PORT48 CH3	*/
#define DIO_ID_PORT48_CH4		((Dio_ChannelType)284U)		/* PORT48 CH4	*/
#define DIO_ID_PORT48_CH5		((Dio_ChannelType)285U)		/* PORT48 CH5	*/
#define DIO_ID_PORT48_CH6		((Dio_ChannelType)286U)		/* PORT48 CH6	*/
#define DIO_ID_PORT48_CH7		((Dio_ChannelType)287U)		/* PORT48 CH7	*/
#define DIO_ID_PORT48_CH8		((Dio_ChannelType)288U)		/* PORT48 CH8	*/
#define DIO_ID_PORT48_CH9		((Dio_ChannelType)289U)		/* PORT48 CH9	*/
#define DIO_ID_PORT48_CH10		((Dio_ChannelType)290U)		/* PORT48 CH10	*/
#define DIO_ID_PORT48_CH11		((Dio_ChannelType)291U)		/* PORT48 CH11	*/
#define DIO_ID_PORT48_CH12		((Dio_ChannelType)292U)		/* PORT48 CH12	*/
#define DIO_ID_PORT48_CH13		((Dio_ChannelType)293U)		/* PORT48 CH13	*/
#define DIO_ID_PORT48_CH14		((Dio_ChannelType)294U)		/* PORT48 CH14	*/
#define DIO_ID_PORT48_CH15		((Dio_ChannelType)295U)		/* PORT48 CH15	*/
#define DIO_ID_PORT49_CH0		((Dio_ChannelType)296U)		/* PORT49 CH0	*/
#define DIO_ID_PORT49_CH1		((Dio_ChannelType)297U)		/* PORT49 CH1	*/
#define DIO_ID_PORT49_CH2		((Dio_ChannelType)298U)		/* PORT49 CH2	*/
#define DIO_ID_PORT49_CH3		((Dio_ChannelType)299U)		/* PORT49 CH3	*/
#define DIO_ID_PORT49_CH4		((Dio_ChannelType)300U)		/* PORT49 CH4	*/
#define DIO_ID_PORT49_CH5		((Dio_ChannelType)301U)		/* PORT49 CH5	*/
#define DIO_ID_PORT49_CH6		((Dio_ChannelType)302U)		/* PORT49 CH6	*/
#define DIO_ID_PORT49_CH7		((Dio_ChannelType)303U)		/* PORT49 CH7	*/
#define DIO_ID_PORT49_CH8		((Dio_ChannelType)304U)		/* PORT49 CH8	*/
#define DIO_ID_PORT49_CH9		((Dio_ChannelType)305U)		/* PORT49 CH9	*/
#define DIO_ID_PORT49_CH10		((Dio_ChannelType)306U)		/* PORT49 CH10	*/
#define DIO_ID_PORT49_CH11		((Dio_ChannelType)307U)		/* PORT49 CH11	*/
#define DIO_ID_PORT49_CH12		((Dio_ChannelType)308U)		/* PORT49 CH12	*/
#define DIO_ID_PORT49_CH13		((Dio_ChannelType)309U)		/* PORT49 CH13	*/
#define DIO_ID_PORT49_CH14		((Dio_ChannelType)310U)		/* PORT49 CH14	*/
#define DIO_ID_PORT49_CH15		((Dio_ChannelType)311U)		/* PORT49 CH15	*/
#define DIO_ID_PORT50_CH0		((Dio_ChannelType)312U)		/* PORT50 CH0	*/
#define DIO_ID_PORT50_CH1		((Dio_ChannelType)313U)		/* PORT50 CH1	*/
#define DIO_ID_PORT50_CH2		((Dio_ChannelType)314U)		/* PORT50 CH2	*/
#define DIO_ID_PORT50_CH3		((Dio_ChannelType)315U)		/* PORT50 CH3	*/
#define DIO_ID_PORT50_CH4		((Dio_ChannelType)316U)		/* PORT50 CH4	*/
#define DIO_ID_PORT50_CH5		((Dio_ChannelType)317U)		/* PORT50 CH5	*/
#define DIO_ID_PORT50_CH6		((Dio_ChannelType)318U)		/* PORT50 CH6	*/
#define DIO_ID_PORT50_CH7		((Dio_ChannelType)319U)		/* PORT50 CH7	*/
#define DIO_ID_PORT50_CH8		((Dio_ChannelType)320U)		/* PORT50 CH8	*/
#define DIO_ID_PORT50_CH9		((Dio_ChannelType)321U)		/* PORT50 CH9	*/
#define DIO_ID_PORT50_CH10		((Dio_ChannelType)322U)		/* PORT50 CH10	*/
#define DIO_ID_PORT50_CH11		((Dio_ChannelType)323U)		/* PORT50 CH11	*/
#define DIO_ID_PORT50_CH12		((Dio_ChannelType)324U)		/* PORT50 CH12	*/
#define DIO_ID_PORT50_CH13		((Dio_ChannelType)325U)		/* PORT50 CH13	*/
#define DIO_ID_PORT50_CH14		((Dio_ChannelType)326U)		/* PORT50 CH14	*/
#define DIO_ID_PORT50_CH15		((Dio_ChannelType)327U)		/* PORT50 CH15	*/
#define DIO_ID_PORT51_CH0		((Dio_ChannelType)328U)		/* PORT51 CH0	*/
#define DIO_ID_PORT51_CH1		((Dio_ChannelType)329U)		/* PORT51 CH1	*/
#define DIO_ID_PORT51_CH2		((Dio_ChannelType)330U)		/* PORT51 CH2	*/
#define DIO_ID_PORT51_CH3		((Dio_ChannelType)331U)		/* PORT51 CH3	*/
#define DIO_ID_PORT51_CH4		((Dio_ChannelType)332U)		/* PORT51 CH4	*/
#define DIO_ID_PORT51_CH5		((Dio_ChannelType)333U)		/* PORT51 CH5	*/
#define DIO_ID_PORT51_CH6		((Dio_ChannelType)334U)		/* PORT51 CH6	*/
#define DIO_ID_PORT51_CH7		((Dio_ChannelType)335U)		/* PORT51 CH7	*/
#define DIO_ID_PORT51_CH8		((Dio_ChannelType)336U)		/* PORT51 CH8	*/
#define DIO_ID_PORT51_CH9		((Dio_ChannelType)337U)		/* PORT51 CH9	*/
#define DIO_ID_PORT51_CH10		((Dio_ChannelType)338U)		/* PORT51 CH10	*/
#define DIO_ID_PORT51_CH11		((Dio_ChannelType)339U)		/* PORT51 CH11	*/
#define DIO_ID_PORT51_CH12		((Dio_ChannelType)340U)		/* PORT51 CH12	*/
#define DIO_ID_PORT51_CH13		((Dio_ChannelType)341U)		/* PORT51 CH13	*/
#define DIO_ID_PORT51_CH14		((Dio_ChannelType)342U)		/* PORT51 CH14	*/
#define DIO_ID_PORT51_CH15		((Dio_ChannelType)343U)		/* PORT51 CH15	*/
#define DIO_ID_PORT52_CH0		((Dio_ChannelType)344U)		/* PORT52 CH0	*/
#define DIO_ID_PORT52_CH1		((Dio_ChannelType)345U)		/* PORT52 CH1	*/
#define DIO_ID_PORT52_CH2		((Dio_ChannelType)346U)		/* PORT52 CH2	*/
#define DIO_ID_PORT52_CH3		((Dio_ChannelType)347U)		/* PORT52 CH3	*/
#define DIO_ID_PORT52_CH4		((Dio_ChannelType)348U)		/* PORT52 CH4	*/
#define DIO_ID_PORT52_CH5		((Dio_ChannelType)349U)		/* PORT52 CH5	*/
#define DIO_ID_PORT52_CH6		((Dio_ChannelType)350U)		/* PORT52 CH6	*/
#define DIO_ID_PORT52_CH7		((Dio_ChannelType)351U)		/* PORT52 CH7	*/
#define DIO_ID_PORT52_CH8		((Dio_ChannelType)352U)		/* PORT52 CH8	*/
#define DIO_ID_PORT52_CH9		((Dio_ChannelType)353U)		/* PORT52 CH9	*/
#define DIO_ID_PORT52_CH10		((Dio_ChannelType)354U)		/* PORT52 CH10	*/
#define DIO_ID_PORT52_CH11		((Dio_ChannelType)355U)		/* PORT52 CH11	*/
#define DIO_ID_PORT52_CH12		((Dio_ChannelType)356U)		/* PORT52 CH12	*/
#define DIO_ID_PORT52_CH13		((Dio_ChannelType)357U)		/* PORT52 CH13	*/
#define DIO_ID_PORT52_CH14		((Dio_ChannelType)358U)		/* PORT52 CH14	*/
#define DIO_ID_PORT52_CH15		((Dio_ChannelType)359U)		/* PORT52 CH15	*/
#define DIO_ID_JPORT0_CH0		((Dio_ChannelType)360U)		/* JPORT0 CH0	*/
#define DIO_ID_JPORT0_CH1		((Dio_ChannelType)361U)		/* JPORT0 CH1	*/
#define DIO_ID_JPORT0_CH2		((Dio_ChannelType)362U)		/* JPORT0 CH2	*/
#define DIO_ID_JPORT0_CH3		((Dio_ChannelType)363U)		/* JPORT0 CH3	*/
#define DIO_ID_JPORT0_CH5		((Dio_ChannelType)364U)		/* JPORT0 CH5	*/

#define DIO_ASSIGN_ID_CH_MAX	((Dio_ChannelType)365U)

/*----------------------------------------------------------------------------------------------*/
/* U2B DIO Port ID Symbols																		*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_ID_PORT0			((Dio_PortType)0U)			/* PORT0		*/
#define DIO_ID_PORT2			((Dio_PortType)1U)			/* PORT2		*/
#define DIO_ID_PORT10			((Dio_PortType)2U)			/* PORT10		*/
#define DIO_ID_PORT11			((Dio_PortType)3U)			/* PORT11		*/
#define DIO_ID_PORT12			((Dio_PortType)4U)			/* PORT12		*/
#define DIO_ID_PORT13			((Dio_PortType)5U)			/* PORT13		*/
#define DIO_ID_PORT14			((Dio_PortType)6U)			/* PORT14		*/
#define DIO_ID_PORT20			((Dio_PortType)7U)			/* PORT20		*/
#define DIO_ID_PORT21			((Dio_PortType)8U)			/* PORT21		*/
#define DIO_ID_PORT22			((Dio_PortType)9U)			/* PORT22		*/
#define DIO_ID_PORT23			((Dio_PortType)10U)			/* PORT23		*/
#define DIO_ID_PORT25			((Dio_PortType)11U)			/* PORT25		*/
#define DIO_ID_PORT27			((Dio_PortType)12U)			/* PORT27		*/
#define DIO_ID_PORT32			((Dio_PortType)13U)			/* PORT32		*/
#define DIO_ID_PORT33			((Dio_PortType)14U)			/* PORT33		*/
#define DIO_ID_PORT34			((Dio_PortType)15U)			/* PORT34		*/
#define DIO_ID_PORT37			((Dio_PortType)16U)			/* PORT37		*/
#define DIO_ID_PORT38			((Dio_PortType)17U)			/* PORT38		*/
#define DIO_ID_PORT40			((Dio_PortType)18U)			/* PORT40		*/
#define DIO_ID_PORT41			((Dio_PortType)19U)			/* PORT41		*/
#define DIO_ID_PORT42			((Dio_PortType)20U)			/* PORT42		*/
#define DIO_ID_PORT43			((Dio_PortType)21U)			/* PORT43		*/
#define DIO_ID_PORT44			((Dio_PortType)22U)			/* PORT44		*/
#define DIO_ID_PORT45			((Dio_PortType)23U)			/* PORT45		*/
#define DIO_ID_PORT46			((Dio_PortType)24U)			/* PORT46		*/
#define DIO_ID_PORT47			((Dio_PortType)25U)			/* PORT47		*/
#define DIO_ID_PORT48			((Dio_PortType)26U)			/* PORT48		*/
#define DIO_ID_PORT49			((Dio_PortType)27U)			/* PORT49		*/
#define DIO_ID_PORT50			((Dio_PortType)28U)			/* PORT50		*/
#define DIO_ID_PORT51			((Dio_PortType)29U)			/* PORT51		*/
#define DIO_ID_PORT52			((Dio_PortType)30U)			/* PORT52		*/
#define DIO_ID_JPORT0			((Dio_PortType)31U)			/* JPORT0		*/

#define DIO_ASSIGN_ID_PORT_MAX	((Dio_PortType)32U)

#endif /* MCAL_TARGET_RH850U2A */

/*----------------------------------------------------------------------------------------------*/
/* Mask value indicating channel group (Adjacent bit combinations only)							*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_CH_GRP_MASK_1_0		((Dio_PortLevelType)0x0001U)		/* 00000000 00000001 */
#define DIO_CH_GRP_MASK_1_1		((Dio_PortLevelType)0x0002U)		/* 00000000 00000010 */
#define DIO_CH_GRP_MASK_1_2		((Dio_PortLevelType)0x0004U)		/* 00000000 00000100 */
#define DIO_CH_GRP_MASK_1_3		((Dio_PortLevelType)0x0008U)		/* 00000000 00001000 */
#define DIO_CH_GRP_MASK_1_4		((Dio_PortLevelType)0x0010U)		/* 00000000 00010000 */
#define DIO_CH_GRP_MASK_1_5		((Dio_PortLevelType)0x0020U)		/* 00000000 00100000 */
#define DIO_CH_GRP_MASK_1_6		((Dio_PortLevelType)0x0040U)		/* 00000000 01000000 */
#define DIO_CH_GRP_MASK_1_7		((Dio_PortLevelType)0x0080U)		/* 00000000 10000000 */
#define DIO_CH_GRP_MASK_1_8		((Dio_PortLevelType)0x0100U)		/* 00000001 00000000 */
#define DIO_CH_GRP_MASK_1_9		((Dio_PortLevelType)0x0200U)		/* 00000010 00000000 */
#define DIO_CH_GRP_MASK_1_10	((Dio_PortLevelType)0x0400U)		/* 00000100 00000000 */
#define DIO_CH_GRP_MASK_1_11	((Dio_PortLevelType)0x0800U)		/* 00001000 00000000 */
#define DIO_CH_GRP_MASK_1_12	((Dio_PortLevelType)0x1000U)		/* 00010000 00000000 */
#define DIO_CH_GRP_MASK_1_13	((Dio_PortLevelType)0x2000U)		/* 00100000 00000000 */
#define DIO_CH_GRP_MASK_1_14	((Dio_PortLevelType)0x4000U)		/* 01000000 00000000 */
#define DIO_CH_GRP_MASK_1_15	((Dio_PortLevelType)0x8000U)		/* 10000000 00000000 */
#define DIO_CH_GRP_MASK_2_0		((Dio_PortLevelType)0x0003U)		/* 00000000 00000011 */
#define DIO_CH_GRP_MASK_2_1		((Dio_PortLevelType)0x0006U)		/* 00000000 00000110 */
#define DIO_CH_GRP_MASK_2_2		((Dio_PortLevelType)0x000CU)		/* 00000000 00001100 */
#define DIO_CH_GRP_MASK_2_3		((Dio_PortLevelType)0x0018U)		/* 00000000 00011000 */
#define DIO_CH_GRP_MASK_2_4		((Dio_PortLevelType)0x0030U)		/* 00000000 00110000 */
#define DIO_CH_GRP_MASK_2_5		((Dio_PortLevelType)0x0060U)		/* 00000000 01100000 */
#define DIO_CH_GRP_MASK_2_6		((Dio_PortLevelType)0x00C0U)		/* 00000000 11000000 */
#define DIO_CH_GRP_MASK_2_7		((Dio_PortLevelType)0x0180U)		/* 00000001 10000000 */
#define DIO_CH_GRP_MASK_2_8		((Dio_PortLevelType)0x0300U)		/* 00000011 00000000 */
#define DIO_CH_GRP_MASK_2_9		((Dio_PortLevelType)0x0600U)		/* 00000110 00000000 */
#define DIO_CH_GRP_MASK_2_10	((Dio_PortLevelType)0x0C00U)		/* 00001100 00000000 */
#define DIO_CH_GRP_MASK_2_11	((Dio_PortLevelType)0x1800U)		/* 00011000 00000000 */
#define DIO_CH_GRP_MASK_2_12	((Dio_PortLevelType)0x3000U)		/* 00110000 00000000 */
#define DIO_CH_GRP_MASK_2_13	((Dio_PortLevelType)0x6000U)		/* 01100000 00000000 */
#define DIO_CH_GRP_MASK_2_14	((Dio_PortLevelType)0xC000U)		/* 11000000 00000000 */
#define DIO_CH_GRP_MASK_3_0		((Dio_PortLevelType)0x0007U)		/* 00000000 00000111 */
#define DIO_CH_GRP_MASK_3_1		((Dio_PortLevelType)0x000EU)		/* 00000000 00001110 */
#define DIO_CH_GRP_MASK_3_2		((Dio_PortLevelType)0x001CU)		/* 00000000 00011100 */
#define DIO_CH_GRP_MASK_3_3		((Dio_PortLevelType)0x0038U)		/* 00000000 00111000 */
#define DIO_CH_GRP_MASK_3_4		((Dio_PortLevelType)0x0070U)		/* 00000000 01110000 */
#define DIO_CH_GRP_MASK_3_5		((Dio_PortLevelType)0x00E0U)		/* 00000000 11100000 */
#define DIO_CH_GRP_MASK_3_6		((Dio_PortLevelType)0x01C0U)		/* 00000001 11000000 */
#define DIO_CH_GRP_MASK_3_7		((Dio_PortLevelType)0x0380U)		/* 00000011 10000000 */
#define DIO_CH_GRP_MASK_3_8		((Dio_PortLevelType)0x0700U)		/* 00000111 00000000 */
#define DIO_CH_GRP_MASK_3_9		((Dio_PortLevelType)0x0E00U)		/* 00001110 00000000 */
#define DIO_CH_GRP_MASK_3_10	((Dio_PortLevelType)0x1C00U)		/* 00011100 00000000 */
#define DIO_CH_GRP_MASK_3_11	((Dio_PortLevelType)0x3800U)		/* 00111000 00000000 */
#define DIO_CH_GRP_MASK_3_12	((Dio_PortLevelType)0x7000U)		/* 01110000 00000000 */
#define DIO_CH_GRP_MASK_3_13	((Dio_PortLevelType)0xE000U)		/* 11100000 00000000 */
#define DIO_CH_GRP_MASK_4_0		((Dio_PortLevelType)0x000FU)		/* 00000000 00001111 */
#define DIO_CH_GRP_MASK_4_1		((Dio_PortLevelType)0x001EU)		/* 00000000 00011110 */
#define DIO_CH_GRP_MASK_4_2		((Dio_PortLevelType)0x003CU)		/* 00000000 00111100 */
#define DIO_CH_GRP_MASK_4_3		((Dio_PortLevelType)0x0078U)		/* 00000000 01111000 */
#define DIO_CH_GRP_MASK_4_4		((Dio_PortLevelType)0x00F0U)		/* 00000000 11110000 */
#define DIO_CH_GRP_MASK_4_5		((Dio_PortLevelType)0x01E0U)		/* 00000001 11100000 */
#define DIO_CH_GRP_MASK_4_6		((Dio_PortLevelType)0x03C0U)		/* 00000011 11000000 */
#define DIO_CH_GRP_MASK_4_7		((Dio_PortLevelType)0x0780U)		/* 00000111 10000000 */
#define DIO_CH_GRP_MASK_4_8		((Dio_PortLevelType)0x0F00U)		/* 00001111 00000000 */
#define DIO_CH_GRP_MASK_4_9		((Dio_PortLevelType)0x1E00U)		/* 00011110 00000000 */
#define DIO_CH_GRP_MASK_4_10	((Dio_PortLevelType)0x3C00U)		/* 00111100 00000000 */
#define DIO_CH_GRP_MASK_4_11	((Dio_PortLevelType)0x7800U)		/* 01111000 00000000 */
#define DIO_CH_GRP_MASK_4_12	((Dio_PortLevelType)0xF000U)		/* 11110000 00000000 */
#define DIO_CH_GRP_MASK_5_0		((Dio_PortLevelType)0x001FU)		/* 00000000 00011111 */
#define DIO_CH_GRP_MASK_5_1		((Dio_PortLevelType)0x003EU)		/* 00000000 00111110 */
#define DIO_CH_GRP_MASK_5_2		((Dio_PortLevelType)0x007CU)		/* 00000000 01111100 */
#define DIO_CH_GRP_MASK_5_3		((Dio_PortLevelType)0x00F8U)		/* 00000000 11111000 */
#define DIO_CH_GRP_MASK_5_4		((Dio_PortLevelType)0x01F0U)		/* 00000001 11110000 */
#define DIO_CH_GRP_MASK_5_5		((Dio_PortLevelType)0x03E0U)		/* 00000011 11100000 */
#define DIO_CH_GRP_MASK_5_6		((Dio_PortLevelType)0x07C0U)		/* 00000111 11000000 */
#define DIO_CH_GRP_MASK_5_7		((Dio_PortLevelType)0x0F80U)		/* 00001111 10000000 */
#define DIO_CH_GRP_MASK_5_8		((Dio_PortLevelType)0x1F00U)		/* 00011111 00000000 */
#define DIO_CH_GRP_MASK_5_9		((Dio_PortLevelType)0x3E00U)		/* 00111110 00000000 */
#define DIO_CH_GRP_MASK_5_10	((Dio_PortLevelType)0x7C00U)		/* 01111100 00000000 */
#define DIO_CH_GRP_MASK_5_11	((Dio_PortLevelType)0xF800U)		/* 11111000 00000000 */
#define DIO_CH_GRP_MASK_6_0		((Dio_PortLevelType)0x003FU)		/* 00000000 00111111 */
#define DIO_CH_GRP_MASK_6_1		((Dio_PortLevelType)0x007EU)		/* 00000000 01111110 */
#define DIO_CH_GRP_MASK_6_2		((Dio_PortLevelType)0x00FCU)		/* 00000000 11111100 */
#define DIO_CH_GRP_MASK_6_3		((Dio_PortLevelType)0x01F8U)		/* 00000001 11111000 */
#define DIO_CH_GRP_MASK_6_4		((Dio_PortLevelType)0x03F0U)		/* 00000011 11110000 */
#define DIO_CH_GRP_MASK_6_5		((Dio_PortLevelType)0x07E0U)		/* 00000111 11100000 */
#define DIO_CH_GRP_MASK_6_6		((Dio_PortLevelType)0x0FC0U)		/* 00001111 11000000 */
#define DIO_CH_GRP_MASK_6_7		((Dio_PortLevelType)0x1F80U)		/* 00011111 10000000 */
#define DIO_CH_GRP_MASK_6_8		((Dio_PortLevelType)0x3F00U)		/* 00111111 00000000 */
#define DIO_CH_GRP_MASK_6_9		((Dio_PortLevelType)0x7E00U)		/* 01111110 00000000 */
#define DIO_CH_GRP_MASK_6_10	((Dio_PortLevelType)0xFC00U)		/* 11111100 00000000 */
#define DIO_CH_GRP_MASK_7_0		((Dio_PortLevelType)0x007FU)		/* 00000000 01111111 */
#define DIO_CH_GRP_MASK_7_1		((Dio_PortLevelType)0x00FEU)		/* 00000000 11111110 */
#define DIO_CH_GRP_MASK_7_2		((Dio_PortLevelType)0x01FCU)		/* 00000001 11111100 */
#define DIO_CH_GRP_MASK_7_3		((Dio_PortLevelType)0x03F8U)		/* 00000011 11111000 */
#define DIO_CH_GRP_MASK_7_4		((Dio_PortLevelType)0x07F0U)		/* 00000111 11110000 */
#define DIO_CH_GRP_MASK_7_5		((Dio_PortLevelType)0x0FE0U)		/* 00001111 11100000 */
#define DIO_CH_GRP_MASK_7_6		((Dio_PortLevelType)0x1FC0U)		/* 00011111 11000000 */
#define DIO_CH_GRP_MASK_7_7		((Dio_PortLevelType)0x3F80U)		/* 00111111 10000000 */
#define DIO_CH_GRP_MASK_7_8		((Dio_PortLevelType)0x7F00U)		/* 01111111 00000000 */
#define DIO_CH_GRP_MASK_7_9		((Dio_PortLevelType)0xFE00U)		/* 11111110 00000000 */
#define DIO_CH_GRP_MASK_8_0		((Dio_PortLevelType)0x00FFU)		/* 00000000 11111111 */
#define DIO_CH_GRP_MASK_8_1		((Dio_PortLevelType)0x01FEU)		/* 00000001 11111110 */
#define DIO_CH_GRP_MASK_8_2		((Dio_PortLevelType)0x03FCU)		/* 00000011 11111100 */
#define DIO_CH_GRP_MASK_8_3		((Dio_PortLevelType)0x07F8U)		/* 00000111 11111000 */
#define DIO_CH_GRP_MASK_8_4		((Dio_PortLevelType)0x0FF0U)		/* 00001111 11110000 */
#define DIO_CH_GRP_MASK_8_5		((Dio_PortLevelType)0x1FE0U)		/* 00011111 11100000 */
#define DIO_CH_GRP_MASK_8_6		((Dio_PortLevelType)0x3FC0U)		/* 00111111 11000000 */
#define DIO_CH_GRP_MASK_8_7		((Dio_PortLevelType)0x7F80U)		/* 01111111 10000000 */
#define DIO_CH_GRP_MASK_8_8		((Dio_PortLevelType)0xFF00U)		/* 11111111 00000000 */
#define DIO_CH_GRP_MASK_9_0		((Dio_PortLevelType)0x01FFU)		/* 00000001 11111111 */
#define DIO_CH_GRP_MASK_9_1		((Dio_PortLevelType)0x03FEU)		/* 00000011 11111110 */
#define DIO_CH_GRP_MASK_9_2		((Dio_PortLevelType)0x07FCU)		/* 00000111 11111100 */
#define DIO_CH_GRP_MASK_9_3		((Dio_PortLevelType)0x0FF8U)		/* 00001111 11111000 */
#define DIO_CH_GRP_MASK_9_4		((Dio_PortLevelType)0x1FF0U)		/* 00011111 11110000 */
#define DIO_CH_GRP_MASK_9_5		((Dio_PortLevelType)0x3FE0U)		/* 00111111 11100000 */
#define DIO_CH_GRP_MASK_9_6		((Dio_PortLevelType)0x7FC0U)		/* 01111111 11000000 */
#define DIO_CH_GRP_MASK_9_7		((Dio_PortLevelType)0xFF80U)		/* 11111111 10000000 */
#define DIO_CH_GRP_MASK_10_0	((Dio_PortLevelType)0x03FFU)		/* 00000011 11111111 */
#define DIO_CH_GRP_MASK_10_1	((Dio_PortLevelType)0x07FEU)		/* 00000111 11111110 */
#define DIO_CH_GRP_MASK_10_2	((Dio_PortLevelType)0x0FFCU)		/* 00001111 11111100 */
#define DIO_CH_GRP_MASK_10_3	((Dio_PortLevelType)0x1FF8U)		/* 00011111 11111000 */
#define DIO_CH_GRP_MASK_10_4	((Dio_PortLevelType)0x3FF0U)		/* 00111111 11110000 */
#define DIO_CH_GRP_MASK_10_5	((Dio_PortLevelType)0x7FE0U)		/* 01111111 11100000 */
#define DIO_CH_GRP_MASK_10_6	((Dio_PortLevelType)0xFFC0U)		/* 11111111 11000000 */
#define DIO_CH_GRP_MASK_11_0	((Dio_PortLevelType)0x07FFU)		/* 00000111 11111111 */
#define DIO_CH_GRP_MASK_11_1	((Dio_PortLevelType)0x0FFEU)		/* 00001111 11111110 */
#define DIO_CH_GRP_MASK_11_2	((Dio_PortLevelType)0x1FFCU)		/* 00011111 11111100 */
#define DIO_CH_GRP_MASK_11_3	((Dio_PortLevelType)0x3FF8U)		/* 00111111 11111000 */
#define DIO_CH_GRP_MASK_11_4	((Dio_PortLevelType)0x7FF0U)		/* 01111111 11110000 */
#define DIO_CH_GRP_MASK_11_5	((Dio_PortLevelType)0xFFE0U)		/* 11111111 11100000 */
#define DIO_CH_GRP_MASK_12_0	((Dio_PortLevelType)0x0FFFU)		/* 00001111 11111111 */
#define DIO_CH_GRP_MASK_12_1	((Dio_PortLevelType)0x1FFEU)		/* 00011111 11111110 */
#define DIO_CH_GRP_MASK_12_2	((Dio_PortLevelType)0x3FFCU)		/* 00111111 11111100 */
#define DIO_CH_GRP_MASK_12_3	((Dio_PortLevelType)0x7FF8U)		/* 01111111 11111000 */
#define DIO_CH_GRP_MASK_12_4	((Dio_PortLevelType)0xFFF0U)		/* 11111111 11110000 */
#define DIO_CH_GRP_MASK_13_0	((Dio_PortLevelType)0x1FFFU)		/* 00011111 11111111 */
#define DIO_CH_GRP_MASK_13_1	((Dio_PortLevelType)0x3FFEU)		/* 00111111 11111110 */
#define DIO_CH_GRP_MASK_13_2	((Dio_PortLevelType)0x7FFCU)		/* 01111111 11111100 */
#define DIO_CH_GRP_MASK_13_3	((Dio_PortLevelType)0xFFF8U)		/* 11111111 11111000 */
#define DIO_CH_GRP_MASK_14_0	((Dio_PortLevelType)0x3FFFU)		/* 00111111 11111111 */
#define DIO_CH_GRP_MASK_14_1	((Dio_PortLevelType)0x7FFEU)		/* 01111111 11111110 */
#define DIO_CH_GRP_MASK_14_2	((Dio_PortLevelType)0xFFFCU)		/* 11111111 11111100 */
#define DIO_CH_GRP_MASK_15_0	((Dio_PortLevelType)0x7FFFU)		/* 01111111 11111111 */
#define DIO_CH_GRP_MASK_15_1	((Dio_PortLevelType)0xFFFEU)		/* 11111111 11111110 */
#define DIO_CH_GRP_MASK_16_0	((Dio_PortLevelType)0xFFFFU)		/* 11111111 11111111 */

/*----------------------------------------------------------------------------------------------*/
/* Offset value from LSB																		*/
/*----------------------------------------------------------------------------------------------*/
#define DIO_OFFSET_0			((uint8)0U)
#define DIO_OFFSET_1			((uint8)1U)
#define DIO_OFFSET_2			((uint8)2U)
#define DIO_OFFSET_3			((uint8)3U)
#define DIO_OFFSET_4			((uint8)4U)
#define DIO_OFFSET_5			((uint8)5U)
#define DIO_OFFSET_6			((uint8)6U)
#define DIO_OFFSET_7			((uint8)7U)
#define DIO_OFFSET_8			((uint8)8U)
#define DIO_OFFSET_9			((uint8)9U)
#define DIO_OFFSET_10			((uint8)10U)
#define DIO_OFFSET_11			((uint8)11U)
#define DIO_OFFSET_12			((uint8)12U)
#define DIO_OFFSET_13			((uint8)13U)
#define DIO_OFFSET_14			((uint8)14U)
#define DIO_OFFSET_15			((uint8)15U)

#endif /* DIO_SYMBOLS_H */
/*-- End Of File -------------------------------------------------------------------------------*/
