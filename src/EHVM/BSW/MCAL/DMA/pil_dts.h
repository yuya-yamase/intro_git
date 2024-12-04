/* pil_dts-r04-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIL DTS Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef PIL_DTS_H
#define PIL_DTS_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Mcal_SpalCmn.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A)
/* U2A */
/* DTS transfer request definition group 0(DTS has the same CH number and hard factor) */
#define    PIL_DTS_GR0_INTADCJ0I0        (0U)    /* ADCJ INTADCJ0I0 */
#define    PIL_DTS_GR0_INTADCJ0I1        (1U)    /* ADCJ INTADCJ0I1 */
#define    PIL_DTS_GR0_INTADCJ0I2        (2U)    /* ADCJ INTADCJ0I2 */
#define    PIL_DTS_GR0_INTADCJ0I3        (3U)    /* ADCJ INTADCJ0I3 */
#define    PIL_DTS_GR0_INTADCJ0I4        (4U)    /* ADCJ INTADCJ0I4 */
#define    PIL_DTS_GR0_ADC_CONV_END0        (5U)    /* ADCJ ADC_CONV_END0 */
#define    PIL_DTS_GR0_INTADCJ1I0        (6U)    /* ADCJ INTADCJ1I0 */
#define    PIL_DTS_GR0_INTADCJ1I1        (7U)    /* ADCJ INTADCJ1I1 */
#define    PIL_DTS_GR0_INTADCJ1I2        (8U)    /* ADCJ INTADCJ1I2 */
#define    PIL_DTS_GR0_INTADCJ1I3        (9U)    /* ADCJ INTADCJ1I3 */
#define    PIL_DTS_GR0_INTADCJ1I4        (10U)    /* ADCJ INTADCJ1I4 */
#define    PIL_DTS_GR0_ADC_CONV_END1        (11U)    /* ADCJ ADC_CONV_END1 */
#define    PIL_DTS_GR0_INTADCJ2I0        (12U)    /* ADCJ INTADCJ2I0 */
#define    PIL_DTS_GR0_INTADCJ2I1        (13U)    /* ADCJ INTADCJ2I1 */
#define    PIL_DTS_GR0_INTADCJ2I2        (14U)    /* ADCJ INTADCJ2I2 */
#define    PIL_DTS_GR0_INTADCJ2I3        (15U)    /* ADCJ INTADCJ2I3 */
#define    PIL_DTS_GR0_INTADCJ2I4        (16U)    /* ADCJ INTADCJ2I4 */
#define    PIL_DTS_GR0_ADC_CONV_END2        (17U)    /* ADCJ ADC_CONV_END2 */
#define    PIL_DTS_GR0_INTRCANCFDREQ0        (18U)    /* RS-CANFD INTRCANCFDREQ0 */
#define    PIL_DTS_GR0_INTRCANCFDREQ1        (19U)    /* RS-CANFD INTRCANCFDREQ1 */
#define    PIL_DTS_GR0_INTRCANCFDREQ2        (20U)    /* RS-CANFD INTRCANCFDREQ2 */
#define    PIL_DTS_GR0_INTRCANCFDREQ3        (21U)    /* RS-CANFD INTRCANCFDREQ3 */
#define    PIL_DTS_GR0_INTRCANCFDREQ4        (22U)    /* RS-CANFD INTRCANCFDREQ4 */
#define    PIL_DTS_GR0_INTRCANCFDREQ5        (23U)    /* RS-CANFD INTRCANCFDREQ5 */
#define    PIL_DTS_GR0_INTRCANCFDREQ6        (24U)    /* RS-CANFD INTRCANCFDREQ6 */
#define    PIL_DTS_GR0_INTRCANCFDREQ7        (25U)    /* RS-CANFD INTRCANCFDREQ7 */
#define    PIL_DTS_GR0_INTRCANCFDREQ8        (26U)    /* RS-CANFD INTRCANCFDREQ8 */
#define    PIL_DTS_GR0_INTRCANCFDREQ9        (27U)    /* RS-CANFD INTRCANCFDREQ9 */
#define    PIL_DTS_GR0_INTRCANCFDREQ10        (28U)    /* RS-CANFD INTRCANCFDREQ10 */
#define    PIL_DTS_GR0_INTRCANCFDREQ11        (29U)    /* RS-CANFD INTRCANCFDREQ11 */
#define    PIL_DTS_GR0_INTRCANCFDREQ12        (30U)    /* RS-CANFD INTRCANCFDREQ12 */
#define    PIL_DTS_GR0_INTRCANCFDREQ13        (31U)    /* RS-CANFD INTRCANCFDREQ13 */
#define    PIL_DTS_GR0_INTRCANCFDREQ14        (32U)    /* RS-CANFD INTRCANCFDREQ14 */
#define    PIL_DTS_GR0_INTRCANCFDREQ15        (33U)    /* RS-CANFD INTRCANCFDREQ15 */
#define    PIL_DTS_GR0_INTRCANRFDREQ0        (34U)    /* RS-CANFD INTRCANRFDREQ0 */
#define    PIL_DTS_GR0_INTRCANRFDREQ1        (35U)    /* RS-CANFD INTRCANRFDREQ1 */
#define    PIL_DTS_GR0_INTRCANRFDREQ2        (36U)    /* RS-CANFD INTRCANRFDREQ2 */
#define    PIL_DTS_GR0_INTRCANRFDREQ3        (37U)    /* RS-CANFD INTRCANRFDREQ3 */
#define    PIL_DTS_GR0_INTRCANRFDREQ4        (38U)    /* RS-CANFD INTRCANRFDREQ4 */
#define    PIL_DTS_GR0_INTRCANRFDREQ5        (39U)    /* RS-CANFD INTRCANRFDREQ5 */
#define    PIL_DTS_GR0_INTRCANRFDREQ6        (40U)    /* RS-CANFD INTRCANRFDREQ6 */
#define    PIL_DTS_GR0_INTRCANRFDREQ7        (41U)    /* RS-CANFD INTRCANRFDREQ7 */
#define    PIL_DTS_GR0_INTRCANRFDREQ8        (42U)    /* RS-CANFD INTRCANRFDREQ8 */
#define    PIL_DTS_GR0_INTRCANRFDREQ9        (43U)    /* RS-CANFD INTRCANRFDREQ9 */
#define    PIL_DTS_GR0_INTRCANRFDREQ10        (44U)    /* RS-CANFD INTRCANRFDREQ10 */
#define    PIL_DTS_GR0_INTRCANRFDREQ11        (45U)    /* RS-CANFD INTRCANRFDREQ11 */
#define    PIL_DTS_GR0_INTRCANRFDREQ12        (46U)    /* RS-CANFD INTRCANRFDREQ12 */
#define    PIL_DTS_GR0_INTRCANRFDREQ13        (47U)    /* RS-CANFD INTRCANRFDREQ13 */
#define    PIL_DTS_GR0_INTRCANRFDREQ14        (48U)    /* RS-CANFD INTRCANRFDREQ14 */
#define    PIL_DTS_GR0_INTRCANRFDREQ15        (49U)    /* RS-CANFD INTRCANRFDREQ15 */
#define    PIL_DTS_GR0_INTRLIN30UR0        (50U)    /* RLIN3 INTRLIN30UR0 */
#define    PIL_DTS_GR0_INTRLIN30UR1        (51U)    /* RLIN3 INTRLIN30UR1 */
#define    PIL_DTS_GR0_INTRLIN31UR0        (52U)    /* RLIN3 INTRLIN31UR0 */
#define    PIL_DTS_GR0_INTRLIN31UR1        (53U)    /* RLIN3 INTRLIN31UR1 */
#define    PIL_DTS_GR0_INTRLIN32UR0        (54U)    /* RLIN3 INTRLIN32UR0 */
#define    PIL_DTS_GR0_INTRLIN32UR1        (55U)    /* RLIN3 INTRLIN32UR1 */
#define    PIL_DTS_GR0_INTRLIN33UR0        (56U)    /* RLIN3 INTRLIN33UR0 */
#define    PIL_DTS_GR0_INTRLIN33UR1        (57U)    /* RLIN3 INTRLIN33UR1 */
#define    PIL_DTS_GR0_INTRLIN34UR0        (58U)    /* RLIN3 INTRLIN34UR0 */
#define    PIL_DTS_GR0_INTRLIN34UR1        (59U)    /* RLIN3 INTRLIN34UR1 */
#define    PIL_DTS_GR0_INTRLIN35UR0        (60U)    /* RLIN3 INTRLIN35UR0 */
#define    PIL_DTS_GR0_INTRLIN35UR1        (61U)    /* RLIN3 INTRLIN35UR1 */
#define    PIL_DTS_GR0_INTRLIN36UR0        (62U)    /* RLIN3 INTRLIN36UR0 */
#define    PIL_DTS_GR0_INTRLIN36UR1        (63U)    /* RLIN3 INTRLIN36UR1 */
#define    PIL_DTS_GR0_INTRLIN37UR0        (64U)    /* RLIN3 INTRLIN37UR0 */
#define    PIL_DTS_GR0_INTRLIN37UR1        (65U)    /* RLIN3 INTRLIN37UR1 */
#define    PIL_DTS_GR0_INTRLIN38UR0        (66U)    /* RLIN3 INTRLIN38UR0 */
#define    PIL_DTS_GR0_INTRLIN38UR1        (67U)    /* RLIN3 INTRLIN38UR1 */
#define    PIL_DTS_GR0_INTRLIN39UR0        (68U)    /* RLIN3 INTRLIN39UR0 */
#define    PIL_DTS_GR0_INTRLIN39UR1        (69U)    /* RLIN3 INTRLIN39UR1 */
#define    PIL_DTS_GR0_INTRLIN310UR0        (70U)    /* RLIN3 INTRLIN310UR0 */
#define    PIL_DTS_GR0_INTRLIN310UR1        (71U)    /* RLIN3 INTRLIN310UR1 */
#define    PIL_DTS_GR0_INTRLIN311UR0        (72U)    /* RLIN3 INTRLIN311UR0 */
#define    PIL_DTS_GR0_INTRLIN311UR1        (73U)    /* RLIN3 INTRLIN311UR1 */
#define    PIL_DTS_GR0_INTRLIN312UR0        (74U)    /* RLIN3 INTRLIN312UR0 */
#define    PIL_DTS_GR0_INTRLIN312UR1        (75U)    /* RLIN3 INTRLIN312UR1 */
#define    PIL_DTS_GR0_INTRLIN313UR0        (76U)    /* RLIN3 INTRLIN313UR0 */
#define    PIL_DTS_GR0_INTRLIN313UR1        (77U)    /* RLIN3 INTRLIN313UR1 */
#define    PIL_DTS_GR0_INTRLIN314UR0        (78U)    /* RLIN3 INTRLIN314UR0 */
#define    PIL_DTS_GR0_INTRLIN314UR1        (79U)    /* RLIN3 INTRLIN314UR1 */
#define    PIL_DTS_GR0_INTRLIN315UR0        (80U)    /* RLIN3 INTRLIN315UR0 */
#define    PIL_DTS_GR0_INTRLIN315UR1        (81U)    /* RLIN3 INTRLIN315UR1 */
#define    PIL_DTS_GR0_INTRLIN316UR0        (82U)    /* RLIN3 INTRLIN316UR0 */
#define    PIL_DTS_GR0_INTRLIN316UR1        (83U)    /* RLIN3 INTRLIN316UR1 */
#define    PIL_DTS_GR0_INTRLIN317UR0        (84U)    /* RLIN3 INTRLIN317UR0 */
#define    PIL_DTS_GR0_INTRLIN317UR1        (85U)    /* RLIN3 INTRLIN317UR1 */
#define    PIL_DTS_GR0_INTRLIN318UR0        (86U)    /* RLIN3 INTRLIN318UR0 */
#define    PIL_DTS_GR0_INTRLIN318UR1        (87U)    /* RLIN3 INTRLIN318UR1 */
#define    PIL_DTS_GR0_INTRLIN319UR0        (88U)    /* RLIN3 INTRLIN319UR0 */
#define    PIL_DTS_GR0_INTRLIN319UR1        (89U)    /* RLIN3 INTRLIN319UR1 */
#define    PIL_DTS_GR0_INTRLIN320UR0        (90U)    /* RLIN3 INTRLIN320UR0 */
#define    PIL_DTS_GR0_INTRLIN320UR1        (91U)    /* RLIN3 INTRLIN320UR1 */
#define    PIL_DTS_GR0_INTRLIN321UR0        (92U)    /* RLIN3 INTRLIN321UR0 */
#define    PIL_DTS_GR0_INTRLIN321UR1        (93U)    /* RLIN3 INTRLIN321UR1 */
#define    PIL_DTS_GR0_INTRLIN322UR0        (94U)    /* RLIN3 INTRLIN322UR0 */
#define    PIL_DTS_GR0_INTRLIN322UR1        (95U)    /* RLIN3 INTRLIN322UR1 */
#define    PIL_DTS_GR0_INTRLIN323UR0        (96U)    /* RLIN3 INTRLIN323UR0 */
#define    PIL_DTS_GR0_INTRLIN323UR1        (97U)    /* RLIN3 INTRLIN323UR1 */
#define    PIL_DTS_GR0_DTSMSPI40        (98U)    /* MSPI DTSMSPI40 */
#define    PIL_DTS_GR0_DTSMSPI41        (99U)    /* MSPI DTSMSPI41 */
#define    PIL_DTS_GR0_DTSMSPI42        (100U)    /* MSPI DTSMSPI42 */
#define    PIL_DTS_GR0_DTSMSPI43        (101U)    /* MSPI DTSMSPI43 */
#define    PIL_DTS_GR0_DTSMSPI44        (102U)    /* MSPI DTSMSPI44 */
#define    PIL_DTS_GR0_DTSMSPI45        (103U)    /* MSPI DTSMSPI45 */
#define    PIL_DTS_GR0_DTSMSPI46        (104U)    /* MSPI DTSMSPI46 */
#define    PIL_DTS_GR0_DTSMSPI47        (105U)    /* MSPI DTSMSPI47 */
#define    PIL_DTS_GR0_DTSMSPI48        (106U)    /* MSPI DTSMSPI48 */
#define    PIL_DTS_GR0_DTSMSPI49        (107U)    /* MSPI DTSMSPI49 */
#define    PIL_DTS_GR0_DTSMSPI50        (108U)    /* MSPI DTSMSPI50 */
#define    PIL_DTS_GR0_DTSMSPI51        (109U)    /* MSPI DTSMSPI51 */
#define    PIL_DTS_GR0_DTSMSPI52        (110U)    /* MSPI DTSMSPI52 */
#define    PIL_DTS_GR0_DTSMSPI53        (111U)    /* MSPI DTSMSPI53 */
#define    PIL_DTS_GR0_DTSMSPI54        (112U)    /* MSPI DTSMSPI54 */
#define    PIL_DTS_GR0_DTSMSPI55        (113U)    /* MSPI DTSMSPI55 */
#define    PIL_DTS_GR0_DTSMSPI56        (114U)    /* MSPI DTSMSPI56 */
#define    PIL_DTS_GR0_DTSMSPI57        (115U)    /* MSPI DTSMSPI57 */
#define    PIL_DTS_GR0_DTSMSPI58        (116U)    /* MSPI DTSMSPI58 */
#define    PIL_DTS_GR0_DTSMSPI59        (117U)    /* MSPI DTSMSPI59 */
#define    PIL_DTS_GR0_DTSMSPI60        (118U)    /* MSPI DTSMSPI60 */
#define    PIL_DTS_GR0_DTSMSPI61        (119U)    /* MSPI DTSMSPI61 */
#define    PIL_DTS_GR0_DTSMSPI62        (120U)    /* MSPI DTSMSPI62 */
#define    PIL_DTS_GR0_DTSMSPI63        (121U)    /* MSPI DTSMSPI63 */
#define    PIL_DTS_GR0_INTRIIC0RI        (122U)    /* RIIC INTRIIC0RI */
#define    PIL_DTS_GR0_INTRIIC0TI        (123U)    /* RIIC INTRIIC0TI */
#define    PIL_DTS_GR0_INTRIIC1RI        (124U)    /* RIIC INTRIIC1RI */
#define    PIL_DTS_GR0_INTRIIC1TI        (125U)    /* RIIC INTRIIC1TI */

/* DTS transfer request definition group 1(DTS has the same CH number and hard factor) */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH0        (143U)    /* PSI5S INTPSI5S0RXDMACH0 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH1        (144U)    /* PSI5S INTPSI5S0RXDMACH1 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH2        (145U)    /* PSI5S INTPSI5S0RXDMACH2 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH3        (146U)    /* PSI5S INTPSI5S0RXDMACH3 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH4        (147U)    /* PSI5S INTPSI5S0RXDMACH4 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH5        (148U)    /* PSI5S INTPSI5S0RXDMACH5 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH6        (149U)    /* PSI5S INTPSI5S0RXDMACH6 */
#define    PIL_DTS_GR1_INTPSI5S0RXDMACH7        (150U)    /* PSI5S INTPSI5S0RXDMACH7 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH1        (151U)    /* PSI5S INTPSI5S0TXDMACH1 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH2        (152U)    /* PSI5S INTPSI5S0TXDMACH2 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH3        (153U)    /* PSI5S INTPSI5S0TXDMACH3 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH4        (154U)    /* PSI5S INTPSI5S0TXDMACH4 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH5        (155U)    /* PSI5S INTPSI5S0TXDMACH5 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH6        (156U)    /* PSI5S INTPSI5S0TXDMACH6 */
#define    PIL_DTS_GR1_INTPSI5S0TXDMACH7        (157U)    /* PSI5S INTPSI5S0TXDMACH7 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH0        (158U)    /* PSI5S INTPSI5S1RXDMACH0 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH1        (159U)    /* PSI5S INTPSI5S1RXDMACH1 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH2        (160U)    /* PSI5S INTPSI5S1RXDMACH2 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH3        (161U)    /* PSI5S INTPSI5S1RXDMACH3 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH4        (162U)    /* PSI5S INTPSI5S1RXDMACH4 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH5        (163U)    /* PSI5S INTPSI5S1RXDMACH5 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH6        (164U)    /* PSI5S INTPSI5S1RXDMACH6 */
#define    PIL_DTS_GR1_INTPSI5S1RXDMACH7        (165U)    /* PSI5S INTPSI5S1RXDMACH7 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH1        (166U)    /* PSI5S INTPSI5S1TXDMACH1 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH2        (167U)    /* PSI5S INTPSI5S1TXDMACH2 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH3        (168U)    /* PSI5S INTPSI5S1TXDMACH3 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH4        (169U)    /* PSI5S INTPSI5S1TXDMACH4 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH5        (170U)    /* PSI5S INTPSI5S1TXDMACH5 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH6        (171U)    /* PSI5S INTPSI5S1TXDMACH6 */
#define    PIL_DTS_GR1_INTPSI5S1TXDMACH7        (172U)    /* PSI5S INTPSI5S1TXDMACH7 */
#define    PIL_DTS_GR1_DMAMMCA0        (173U)    /* MMCA DMAMMCA0 */
#define    PIL_DTS_GR1_INTTSG30I11        (174U)    /* TSG3 INTTSG30I11 */
#define    PIL_DTS_GR1_INTTSG30I12        (175U)    /* TSG3 INTTSG30I12 */
#define    PIL_DTS_GR1_INTTSG30IPEK        (176U)    /* TSG3 INTTSG30IPEK */
#define    PIL_DTS_GR1_INTTSG30IVLY        (177U)    /* TSG3 INTTSG30IVLY */
#define    PIL_DTS_GR1_INTTSG31I11        (178U)    /* TSG3 INTTSG31I11 */
#define    PIL_DTS_GR1_INTTSG31I12        (179U)    /* TSG3 INTTSG31I12 */
#define    PIL_DTS_GR1_INTTSG31IPEK        (180U)    /* TSG3 INTTSG31IPEK */
#define    PIL_DTS_GR1_INTTSG31IVLY        (181U)    /* TSG3 INTTSG31IVLY */
#define    PIL_DTS_GR1_INTENCA0IOV        (182U)    /* ENCA INTENCA0IOV */
#define    PIL_DTS_GR1_INTENCA0IUD        (183U)    /* ENCA INTENCA0IUD */
#define    PIL_DTS_GR1_INTENCA0I0        (184U)    /* ENCA INTENCA0I0 */
#define    PIL_DTS_GR1_INTENCA0I1        (185U)    /* ENCA INTENCA0I1 */
#define    PIL_DTS_GR1_INTENCA0IEC        (186U)    /* ENCA INTENCA0IEC */
#define    PIL_DTS_GR1_INTENCA1IOV        (187U)    /* ENCA INTENCA1IOV */
#define    PIL_DTS_GR1_INTENCA1IUD        (188U)    /* ENCA INTENCA1IUD */
#define    PIL_DTS_GR1_INTENCA1I0        (189U)    /* ENCA INTENCA1I0 */
#define    PIL_DTS_GR1_INTENCA1I1        (190U)    /* ENCA INTENCA1I1 */
#define    PIL_DTS_GR1_INTENCA1IEC        (191U)    /* ENCA INTENCA1IEC */
#define    PIL_DTS_GR1_INTTAUD0I0        (192U)    /* TAUD INTTAUD0I0 */
#define    PIL_DTS_GR1_INTTAUD0I1        (193U)    /* TAUD INTTAUD0I1 */
#define    PIL_DTS_GR1_INTTAUD0I2        (194U)    /* TAUD INTTAUD0I2 */
#define    PIL_DTS_GR1_INTTAUD0I3        (195U)    /* TAUD INTTAUD0I3 */
#define    PIL_DTS_GR1_INTTAUD0I4        (196U)    /* TAUD INTTAUD0I4 */
#define    PIL_DTS_GR1_INTTAUD0I5        (197U)    /* TAUD INTTAUD0I5 */
#define    PIL_DTS_GR1_INTTAUD0I6        (198U)    /* TAUD INTTAUD0I6 */
#define    PIL_DTS_GR1_INTTAUD0I7        (199U)    /* TAUD INTTAUD0I7 */
#define    PIL_DTS_GR1_INTTAUD0I8        (200U)    /* TAUD INTTAUD0I8 */
#define    PIL_DTS_GR1_INTTAUD0I9        (201U)    /* TAUD INTTAUD0I9 */
#define    PIL_DTS_GR1_INTTAUD0I10        (202U)    /* TAUD INTTAUD0I10 */
#define    PIL_DTS_GR1_INTTAUD0I11        (203U)    /* TAUD INTTAUD0I11 */
#define    PIL_DTS_GR1_INTTAUD0I12        (204U)    /* TAUD INTTAUD0I12 */
#define    PIL_DTS_GR1_INTTAUD0I13        (205U)    /* TAUD INTTAUD0I13 */
#define    PIL_DTS_GR1_INTTAUD0I14        (206U)    /* TAUD INTTAUD0I14 */
#define    PIL_DTS_GR1_INTTAUD0I15        (207U)    /* TAUD INTTAUD0I15 */
#define    PIL_DTS_GR1_INTTAUD1I0        (208U)    /* TAUD INTTAUD1I0 */
#define    PIL_DTS_GR1_INTTAUD1I1        (209U)    /* TAUD INTTAUD1I1 */
#define    PIL_DTS_GR1_INTTAUD1I2        (210U)    /* TAUD INTTAUD1I2 */
#define    PIL_DTS_GR1_INTTAUD1I3        (211U)    /* TAUD INTTAUD1I3 */
#define    PIL_DTS_GR1_INTTAUD1I4        (212U)    /* TAUD INTTAUD1I4 */
#define    PIL_DTS_GR1_INTTAUD1I5        (213U)    /* TAUD INTTAUD1I5 */
#define    PIL_DTS_GR1_INTTAUD1I6        (214U)    /* TAUD INTTAUD1I6 */
#define    PIL_DTS_GR1_INTTAUD1I7        (215U)    /* TAUD INTTAUD1I7 */
#define    PIL_DTS_GR1_INTTAUD1I8        (216U)    /* TAUD INTTAUD1I8 */
#define    PIL_DTS_GR1_INTTAUD1I9        (217U)    /* TAUD INTTAUD1I9 */
#define    PIL_DTS_GR1_INTTAUD1I10        (218U)    /* TAUD INTTAUD1I10 */
#define    PIL_DTS_GR1_INTTAUD1I11        (219U)    /* TAUD INTTAUD1I11 */
#define    PIL_DTS_GR1_INTTAUD1I12        (220U)    /* TAUD INTTAUD1I12 */
#define    PIL_DTS_GR1_INTTAUD1I13        (221U)    /* TAUD INTTAUD1I13 */
#define    PIL_DTS_GR1_INTTAUD1I14        (222U)    /* TAUD INTTAUD1I14 */
#define    PIL_DTS_GR1_INTTAUD1I15        (223U)    /* TAUD INTTAUD1I15 */
#define    PIL_DTS_GR1_INTTAUD2I0        (224U)    /* TAUD INTTAUD2I0 */
#define    PIL_DTS_GR1_INTTAUD2I1        (225U)    /* TAUD INTTAUD2I1 */
#define    PIL_DTS_GR1_INTTAUD2I2        (226U)    /* TAUD INTTAUD2I2 */
#define    PIL_DTS_GR1_INTTAUD2I3        (227U)    /* TAUD INTTAUD2I3 */
#define    PIL_DTS_GR1_INTTAUD2I4        (228U)    /* TAUD INTTAUD2I4 */
#define    PIL_DTS_GR1_INTTAUD2I5        (229U)    /* TAUD INTTAUD2I5 */
#define    PIL_DTS_GR1_INTTAUD2I6        (230U)    /* TAUD INTTAUD2I6 */
#define    PIL_DTS_GR1_INTTAUD2I7        (231U)    /* TAUD INTTAUD2I7 */
#define    PIL_DTS_GR1_INTTAUD2I8        (232U)    /* TAUD INTTAUD2I8 */
#define    PIL_DTS_GR1_INTTAUD2I9        (233U)    /* TAUD INTTAUD2I9 */
#define    PIL_DTS_GR1_INTTAUD2I10        (234U)    /* TAUD INTTAUD2I10 */
#define    PIL_DTS_GR1_INTTAUD2I11        (235U)    /* TAUD INTTAUD2I11 */
#define    PIL_DTS_GR1_INTTAUD2I12        (236U)    /* TAUD INTTAUD2I12 */
#define    PIL_DTS_GR1_INTTAUD2I13        (237U)    /* TAUD INTTAUD2I13 */
#define    PIL_DTS_GR1_INTTAUD2I14        (238U)    /* TAUD INTTAUD2I14 */
#define    PIL_DTS_GR1_INTTAUD2I15        (239U)    /* TAUD INTTAUD2I15 */
#define    PIL_DTS_GR1_INTTAUJ0I0        (240U)    /* TAUJ INTTAUJ0I0 */
#define    PIL_DTS_GR1_INTTAUJ0I1        (241U)    /* TAUJ INTTAUJ0I1 */
#define    PIL_DTS_GR1_INTTAUJ0I2        (242U)    /* TAUJ INTTAUJ0I2 */
#define    PIL_DTS_GR1_INTTAUJ0I3        (243U)    /* TAUJ INTTAUJ0I3 */
#define    PIL_DTS_GR1_INTTAUJ1I0        (244U)    /* TAUJ INTTAUJ1I0 */
#define    PIL_DTS_GR1_INTTAUJ1I1        (245U)    /* TAUJ INTTAUJ1I1 */
#define    PIL_DTS_GR1_INTTAUJ1I2        (246U)    /* TAUJ INTTAUJ1I2 */
#define    PIL_DTS_GR1_INTTAUJ1I3        (247U)    /* TAUJ INTTAUJ1I3 */
#define    PIL_DTS_GR1_INTTAUJ2I0        (248U)    /* TAUJ INTTAUJ2I0 */
#define    PIL_DTS_GR1_INTTAUJ2I1        (249U)    /* TAUJ INTTAUJ2I1 */
#define    PIL_DTS_GR1_INTTAUJ2I2        (250U)    /* TAUJ INTTAUJ2I2 */
#define    PIL_DTS_GR1_INTTAUJ2I3        (251U)    /* TAUJ INTTAUJ2I3 */
#define    PIL_DTS_GR1_INTTAUJ3I0        (252U)    /* TAUJ INTTAUJ3I0 */
#define    PIL_DTS_GR1_INTTAUJ3I1        (253U)    /* TAUJ INTTAUJ3I1 */
#define    PIL_DTS_GR1_INTTAUJ3I2        (254U)    /* TAUJ INTTAUJ3I2 */
#define    PIL_DTS_GR1_INTTAUJ3I3        (255U)    /* TAUJ INTTAUJ3I3 */

/* DTS transfer request definition group 2(DTS has the same CH number and hard factor) */
#define    PIL_DTS_GR2_DTSMSPI0        (256U)    /* MSPI DTSMSPI0 */
#define    PIL_DTS_GR2_DTSMSPI1        (257U)    /* MSPI DTSMSPI1 */
#define    PIL_DTS_GR2_DTSMSPI2        (258U)    /* MSPI DTSMSPI2 */
#define    PIL_DTS_GR2_DTSMSPI3        (259U)    /* MSPI DTSMSPI3 */
#define    PIL_DTS_GR2_DTSMSPI4        (260U)    /* MSPI DTSMSPI4 */
#define    PIL_DTS_GR2_DTSMSPI5        (261U)    /* MSPI DTSMSPI5 */
#define    PIL_DTS_GR2_DTSMSPI6        (262U)    /* MSPI DTSMSPI6 */
#define    PIL_DTS_GR2_DTSMSPI7        (263U)    /* MSPI DTSMSPI7 */
#define    PIL_DTS_GR2_DTSMSPI8        (264U)    /* MSPI DTSMSPI8 */
#define    PIL_DTS_GR2_DTSMSPI9        (265U)    /* MSPI DTSMSPI9 */
#define    PIL_DTS_GR2_DTSMSPI10        (266U)    /* MSPI DTSMSPI10 */
#define    PIL_DTS_GR2_DTSMSPI11        (267U)    /* MSPI DTSMSPI11 */
#define    PIL_DTS_GR2_DTSMSPI12        (268U)    /* MSPI DTSMSPI12 */
#define    PIL_DTS_GR2_DTSMSPI13        (269U)    /* MSPI DTSMSPI13 */
#define    PIL_DTS_GR2_DTSMSPI14        (270U)    /* MSPI DTSMSPI14 */
#define    PIL_DTS_GR2_DTSMSPI15        (271U)    /* MSPI DTSMSPI15 */
#define    PIL_DTS_GR2_DTSMSPI16        (272U)    /* MSPI DTSMSPI16 */
#define    PIL_DTS_GR2_DTSMSPI17        (273U)    /* MSPI DTSMSPI17 */
#define    PIL_DTS_GR2_DTSMSPI18        (274U)    /* MSPI DTSMSPI18 */
#define    PIL_DTS_GR2_DTSMSPI19        (275U)    /* MSPI DTSMSPI19 */
#define    PIL_DTS_GR2_DTSMSPI20        (276U)    /* MSPI DTSMSPI20 */
#define    PIL_DTS_GR2_DTSMSPI21        (277U)    /* MSPI DTSMSPI21 */
#define    PIL_DTS_GR2_DTSMSPI22        (278U)    /* MSPI DTSMSPI22 */
#define    PIL_DTS_GR2_DTSMSPI23        (279U)    /* MSPI DTSMSPI23 */
#define    PIL_DTS_GR2_DTSMSPI24        (280U)    /* MSPI DTSMSPI24 */
#define    PIL_DTS_GR2_DTSMSPI25        (281U)    /* MSPI DTSMSPI25 */
#define    PIL_DTS_GR2_DTSMSPI26        (282U)    /* MSPI DTSMSPI26 */
#define    PIL_DTS_GR2_DTSMSPI27        (283U)    /* MSPI DTSMSPI27 */
#define    PIL_DTS_GR2_DTSMSPI28        (284U)    /* MSPI DTSMSPI28 */
#define    PIL_DTS_GR2_DTSMSPI29        (285U)    /* MSPI DTSMSPI29 */
#define    PIL_DTS_GR2_DTSMSPI30        (286U)    /* MSPI DTSMSPI30 */
#define    PIL_DTS_GR2_DTSMSPI31        (287U)    /* MSPI DTSMSPI31 */
#define    PIL_DTS_GR2_DTSMSPI32        (288U)    /* MSPI DTSMSPI32 */
#define    PIL_DTS_GR2_DTSMSPI33        (289U)    /* MSPI DTSMSPI33 */
#define    PIL_DTS_GR2_DTSMSPI34        (290U)    /* MSPI DTSMSPI34 */
#define    PIL_DTS_GR2_DTSMSPI35        (291U)    /* MSPI DTSMSPI35 */
#define    PIL_DTS_GR2_DTSMSPI36        (292U)    /* MSPI DTSMSPI36 */
#define    PIL_DTS_GR2_DTSMSPI37        (293U)    /* MSPI DTSMSPI37 */
#define    PIL_DTS_GR2_DTSMSPI38        (294U)    /* MSPI DTSMSPI38 */
#define    PIL_DTS_GR2_DTSMSPI39        (295U)    /* MSPI DTSMSPI39 */
#define    PIL_DTS_GR2_INTRHSIF0INTCH0        (296U)    /* RHSIF INTRHSIF0INTCH0 */
#define    PIL_DTS_GR2_INTRHSIF0INTCH1        (297U)    /* RHSIF INTRHSIF0INTCH1 */
#define    PIL_DTS_GR2_INTRHSIF0INTCH2        (298U)    /* RHSIF INTRHSIF0INTCH2 */
#define    PIL_DTS_GR2_INTRHSIF0INTCH3        (299U)    /* RHSIF INTRHSIF0INTCH3 */
#define    PIL_DTS_GR2_INTGTMA0TIM00        (300U)    /* GTM INTGTMA0TIM00 */
#define    PIL_DTS_GR2_INTGTMA0TIM01        (301U)    /* GTM INTGTMA0TIM01 */
#define    PIL_DTS_GR2_INTGTMA0TIM02        (302U)    /* GTM INTGTMA0TIM02 */
#define    PIL_DTS_GR2_INTGTMA0TIM03        (303U)    /* GTM INTGTMA0TIM03 */
#define    PIL_DTS_GR2_INTGTMA0TIM04        (304U)    /* GTM INTGTMA0TIM04 */
#define    PIL_DTS_GR2_INTGTMA0TIM05        (305U)    /* GTM INTGTMA0TIM05 */
#define    PIL_DTS_GR2_INTGTMA0TIM06        (306U)    /* GTM INTGTMA0TIM06 */
#define    PIL_DTS_GR2_INTGTMA0TIM07        (307U)    /* GTM INTGTMA0TIM07 */
#define    PIL_DTS_GR2_INTGTMA0TIM10        (308U)    /* GTM INTGTMA0TIM10 */
#define    PIL_DTS_GR2_INTGTMA0TIM11        (309U)    /* GTM INTGTMA0TIM11 */
#define    PIL_DTS_GR2_INTGTMA0TIM12        (310U)    /* GTM INTGTMA0TIM12 */
#define    PIL_DTS_GR2_INTGTMA0TIM13        (311U)    /* GTM INTGTMA0TIM13 */
#define    PIL_DTS_GR2_INTGTMA0TIM14        (312U)    /* GTM INTGTMA0TIM14 */
#define    PIL_DTS_GR2_INTGTMA0TIM15        (313U)    /* GTM INTGTMA0TIM15 */
#define    PIL_DTS_GR2_INTGTMA0TIM16        (314U)    /* GTM INTGTMA0TIM16 */
#define    PIL_DTS_GR2_INTGTMA0TIM17        (315U)    /* GTM INTGTMA0TIM17 */
#define    PIL_DTS_GR2_INTGTMA0TIM20        (316U)    /* GTM INTGTMA0TIM20 */
#define    PIL_DTS_GR2_INTGTMA0TIM21        (317U)    /* GTM INTGTMA0TIM21 */
#define    PIL_DTS_GR2_INTGTMA0TIM22        (318U)    /* GTM INTGTMA0TIM22 */
#define    PIL_DTS_GR2_INTGTMA0TIM23        (319U)    /* GTM INTGTMA0TIM23 */
#define    PIL_DTS_GR2_INTGTMA0TIM24        (320U)    /* GTM INTGTMA0TIM24 */
#define    PIL_DTS_GR2_INTGTMA0TIM25        (321U)    /* GTM INTGTMA0TIM25 */
#define    PIL_DTS_GR2_INTGTMA0TIM26        (322U)    /* GTM INTGTMA0TIM26 */
#define    PIL_DTS_GR2_INTGTMA0TIM27        (323U)    /* GTM INTGTMA0TIM27 */
#define    PIL_DTS_GR2_INTGTMA0TIM30        (324U)    /* GTM INTGTMA0TIM30 */
#define    PIL_DTS_GR2_INTGTMA0TIM31        (325U)    /* GTM INTGTMA0TIM31 */
#define    PIL_DTS_GR2_INTGTMA0TIM32        (326U)    /* GTM INTGTMA0TIM32 */
#define    PIL_DTS_GR2_INTGTMA0TIM33        (327U)    /* GTM INTGTMA0TIM33 */
#define    PIL_DTS_GR2_INTGTMA0TIM34        (328U)    /* GTM INTGTMA0TIM34 */
#define    PIL_DTS_GR2_INTGTMA0TIM35        (329U)    /* GTM INTGTMA0TIM35 */
#define    PIL_DTS_GR2_INTGTMA0TIM36        (330U)    /* GTM INTGTMA0TIM36 */
#define    PIL_DTS_GR2_INTGTMA0TIM37        (331U)    /* GTM INTGTMA0TIM37 */
#define    PIL_DTS_GR2_INTGTMA0MCS00        (332U)    /* GTM INTGTMA0MCS00 */
#define    PIL_DTS_GR2_INTGTMA0MCS01        (333U)    /* GTM INTGTMA0MCS01 */
#define    PIL_DTS_GR2_INTGTMA0MCS02        (334U)    /* GTM INTGTMA0MCS02 */
#define    PIL_DTS_GR2_INTGTMA0MCS03        (335U)    /* GTM INTGTMA0MCS03 */
#define    PIL_DTS_GR2_INTGTMA0MCS04        (336U)    /* GTM INTGTMA0MCS04 */
#define    PIL_DTS_GR2_INTGTMA0MCS05        (337U)    /* GTM INTGTMA0MCS05 */
#define    PIL_DTS_GR2_INTGTMA0MCS06        (338U)    /* GTM INTGTMA0MCS06 */
#define    PIL_DTS_GR2_INTGTMA0MCS07        (339U)    /* GTM INTGTMA0MCS07 */
#define    PIL_DTS_GR2_INTGTMA0MCS10        (340U)    /* GTM INTGTMA0MCS10 */
#define    PIL_DTS_GR2_INTGTMA0MCS11        (341U)    /* GTM INTGTMA0MCS11 */
#define    PIL_DTS_GR2_INTGTMA0MCS12        (342U)    /* GTM INTGTMA0MCS12 */
#define    PIL_DTS_GR2_INTGTMA0MCS13        (343U)    /* GTM INTGTMA0MCS13 */
#define    PIL_DTS_GR2_INTGTMA0MCS14        (344U)    /* GTM INTGTMA0MCS14 */
#define    PIL_DTS_GR2_INTGTMA0MCS15        (345U)    /* GTM INTGTMA0MCS15 */
#define    PIL_DTS_GR2_INTGTMA0MCS16        (346U)    /* GTM INTGTMA0MCS16 */
#define    PIL_DTS_GR2_INTGTMA0MCS17        (347U)    /* GTM INTGTMA0MCS17 */
#define    PIL_DTS_GR2_INTGTMA0MCS20        (348U)    /* GTM INTGTMA0MCS20 */
#define    PIL_DTS_GR2_INTGTMA0MCS21        (349U)    /* GTM INTGTMA0MCS21 */
#define    PIL_DTS_GR2_INTGTMA0MCS22        (350U)    /* GTM INTGTMA0MCS22 */
#define    PIL_DTS_GR2_INTGTMA0MCS23        (351U)    /* GTM INTGTMA0MCS23 */
#define    PIL_DTS_GR2_INTGTMA0MCS24        (352U)    /* GTM INTGTMA0MCS24 */
#define    PIL_DTS_GR2_INTGTMA0MCS25        (353U)    /* GTM INTGTMA0MCS25 */
#define    PIL_DTS_GR2_INTGTMA0MCS26        (354U)    /* GTM INTGTMA0MCS26 */
#define    PIL_DTS_GR2_INTGTMA0MCS27        (355U)    /* GTM INTGTMA0MCS27 */
#define    PIL_DTS_GR2_INTGTMA0MCS30        (356U)    /* GTM INTGTMA0MCS30 */
#define    PIL_DTS_GR2_INTGTMA0MCS31        (357U)    /* GTM INTGTMA0MCS31 */
#define    PIL_DTS_GR2_INTGTMA0MCS32        (358U)    /* GTM INTGTMA0MCS32 */
#define    PIL_DTS_GR2_INTGTMA0MCS33        (359U)    /* GTM INTGTMA0MCS33 */
#define    PIL_DTS_GR2_INTGTMA0MCS34        (360U)    /* GTM INTGTMA0MCS34 */
#define    PIL_DTS_GR2_INTGTMA0MCS35        (361U)    /* GTM INTGTMA0MCS35 */
#define    PIL_DTS_GR2_INTGTMA0MCS36        (362U)    /* GTM INTGTMA0MCS36 */
#define    PIL_DTS_GR2_INTGTMA0MCS37        (363U)    /* GTM INTGTMA0MCS37 */
#define    PIL_DTS_GR2_INTGTMA0ATOM00        (364U)    /* GTM INTGTMA0ATOM00 */
#define    PIL_DTS_GR2_INTGTMA0ATOM01        (365U)    /* GTM INTGTMA0ATOM01 */
#define    PIL_DTS_GR2_INTGTMA0ATOM02        (366U)    /* GTM INTGTMA0ATOM02 */
#define    PIL_DTS_GR2_INTGTMA0ATOM03        (367U)    /* GTM INTGTMA0ATOM03 */
#define    PIL_DTS_GR2_INTGTMA0ATOM10        (368U)    /* GTM INTGTMA0ATOM10 */
#define    PIL_DTS_GR2_INTGTMA0ATOM11        (369U)    /* GTM INTGTMA0ATOM11 */
#define    PIL_DTS_GR2_INTGTMA0ATOM12        (370U)    /* GTM INTGTMA0ATOM12 */
#define    PIL_DTS_GR2_INTGTMA0ATOM13        (371U)    /* GTM INTGTMA0ATOM13 */
#define    PIL_DTS_GR2_INTGTMA0ATOM20        (372U)    /* GTM INTGTMA0ATOM20 */
#define    PIL_DTS_GR2_INTGTMA0ATOM21        (373U)    /* GTM INTGTMA0ATOM21 */
#define    PIL_DTS_GR2_INTGTMA0ATOM22        (374U)    /* GTM INTGTMA0ATOM22 */
#define    PIL_DTS_GR2_INTGTMA0ATOM23        (375U)    /* GTM INTGTMA0ATOM23 */
#define    PIL_DTS_GR2_INTGTMA0ATOM30        (376U)    /* GTM INTGTMA0ATOM30 */
#define    PIL_DTS_GR2_INTGTMA0ATOM31        (377U)    /* GTM INTGTMA0ATOM31 */
#define    PIL_DTS_GR2_INTGTMA0ATOM32        (378U)    /* GTM INTGTMA0ATOM32 */
#define    PIL_DTS_GR2_INTGTMA0ATOM33        (379U)    /* GTM INTGTMA0ATOM33 */

/* DTS transfer request definition group 3(DTS has the same CH number and hard factor) */
#define    PIL_DTS_GR3_INTP0        (384U)    /* PORT INTP0 */
#define    PIL_DTS_GR3_INTP1        (385U)    /* PORT INTP1 */
#define    PIL_DTS_GR3_INTP2        (386U)    /* PORT INTP2 */
#define    PIL_DTS_GR3_INTP3        (387U)    /* PORT INTP3 */
#define    PIL_DTS_GR3_INTP4        (388U)    /* PORT INTP4 */
#define    PIL_DTS_GR3_INTP5        (389U)    /* PORT INTP5 */
#define    PIL_DTS_GR3_INTP6        (390U)    /* PORT INTP6 */
#define    PIL_DTS_GR3_INTP7        (391U)    /* PORT INTP7 */
#define    PIL_DTS_GR3_INTP8        (392U)    /* PORT INTP8 */
#define    PIL_DTS_GR3_INTP9        (393U)    /* PORT INTP9 */
#define    PIL_DTS_GR3_INTSCI30RXI        (394U)    /* SCI3 INTSCI30RXI */
#define    PIL_DTS_GR3_INTSCI30TXI        (395U)    /* SCI3 INTSCI30TXI */
#define    PIL_DTS_GR3_INTSCI31RXI        (396U)    /* SCI3 INTSCI31RXI */
#define    PIL_DTS_GR3_INTSCI31TXI        (397U)    /* SCI3 INTSCI31TXI */
#define    PIL_DTS_GR3_INTSCI32RXI        (398U)    /* SCI3 INTSCI32RXI */
#define    PIL_DTS_GR3_INTSCI32TXI        (399U)    /* SCI3 INTSCI32TXI */
#define    PIL_DTS_GR3_INTPSI50RI        (400U)    /* PSI5 INTPSI50RI */
#define    PIL_DTS_GR3_INTPSI51RI        (401U)    /* PSI5 INTPSI51RI */
#define    PIL_DTS_GR3_INTPSI52RI        (402U)    /* PSI5 INTPSI52RI */
#define    PIL_DTS_GR3_INTPSI53RI        (403U)    /* PSI5 INTPSI53RI */
#define    PIL_DTS_GR3_INTTPTMU00        (410U)    /* TPTM INTTPTMU00 */
#define    PIL_DTS_GR3_INTTPTMU01        (411U)    /* TPTM INTTPTMU01 */
#define    PIL_DTS_GR3_INTTPTMU10        (412U)    /* TPTM INTTPTMU10 */
#define    PIL_DTS_GR3_INTTPTMU11        (413U)    /* TPTM INTTPTMU11 */
#define    PIL_DTS_GR3_INTTPTMU20        (414U)    /* TPTM INTTPTMU20 */
#define    PIL_DTS_GR3_INTTPTMU21        (415U)    /* TPTM INTTPTMU21 */
#define    PIL_DTS_GR3_INTTPTMU30        (416U)    /* TPTM INTTPTMU30 */
#define    PIL_DTS_GR3_INTTPTMU31        (417U)    /* TPTM INTTPTMU31 */
#define    PIL_DTS_GR3_INTDMAFL0        (418U)    /* Flash INTDMAFL0 */
#define    PIL_DTS_GR3_INTDMAFL1        (419U)    /* Flash INTDMAFL1 */
#define    PIL_DTS_GR3_INTDMAFL2        (420U)    /* Flash INTDMAFL2 */
#define    PIL_DTS_GR3_INTRSENT0RI        (426U)    /* RSENT INTRSENT0RI */
#define    PIL_DTS_GR3_INTRSENT1RI        (427U)    /* RSENT INTRSENT1RI */
#define    PIL_DTS_GR3_INTRSENT2RI        (428U)    /* RSENT INTRSENT2RI */
#define    PIL_DTS_GR3_INTRSENT3RI        (429U)    /* RSENT INTRSENT3RI */
#define    PIL_DTS_GR3_INTRSENT4RI        (430U)    /* RSENT INTRSENT4RI */
#define    PIL_DTS_GR3_INTRSENT5RI        (431U)    /* RSENT INTRSENT5RI */
#define    PIL_DTS_GR3_INTRSENT6RI        (432U)    /* RSENT INTRSENT6RI */
#define    PIL_DTS_GR3_INTRSENT7RI        (433U)    /* RSENT INTRSENT7RI */
#define    PIL_DTS_GR3_ATOMDREQ00        (434U)    /* GTM ATOMDREQ00 */
#define    PIL_DTS_GR3_ATOMDREQ01        (435U)    /* GTM ATOMDREQ01 */
#define    PIL_DTS_GR3_ATOMDREQ02        (436U)    /* GTM ATOMDREQ02 */
#define    PIL_DTS_GR3_ATOMDREQ03        (437U)    /* GTM ATOMDREQ03 */
#define    PIL_DTS_GR3_ATOMDREQ04        (438U)    /* GTM ATOMDREQ04 */
#define    PIL_DTS_GR3_ATOMDREQ05        (439U)    /* GTM ATOMDREQ05 */
#define    PIL_DTS_GR3_ATOMDREQ06        (440U)    /* GTM ATOMDREQ06 */
#define    PIL_DTS_GR3_ATOMDREQ07        (441U)    /* GTM ATOMDREQ07 */
#define    PIL_DTS_GR3_ATOMDREQ10        (442U)    /* GTM ATOMDREQ10 */
#define    PIL_DTS_GR3_ATOMDREQ11        (443U)    /* GTM ATOMDREQ11 */
#define    PIL_DTS_GR3_ATOMDREQ12        (444U)    /* GTM ATOMDREQ12 */
#define    PIL_DTS_GR3_ATOMDREQ13        (445U)    /* GTM ATOMDREQ13 */
#define    PIL_DTS_GR3_ATOMDREQ14        (446U)    /* GTM ATOMDREQ14 */
#define    PIL_DTS_GR3_ATOMDREQ15        (447U)    /* GTM ATOMDREQ15 */
#define    PIL_DTS_GR3_ATOMDREQ16        (448U)    /* GTM ATOMDREQ16 */
#define    PIL_DTS_GR3_ATOMDREQ17        (449U)    /* GTM ATOMDREQ17 */
#define    PIL_DTS_GR3_ATOMDREQ20        (450U)    /* GTM ATOMDREQ20 */
#define    PIL_DTS_GR3_ATOMDREQ21        (451U)    /* GTM ATOMDREQ21 */
#define    PIL_DTS_GR3_ATOMDREQ22        (452U)    /* GTM ATOMDREQ22 */
#define    PIL_DTS_GR3_ATOMDREQ23        (453U)    /* GTM ATOMDREQ23 */
#define    PIL_DTS_GR3_ATOMDREQ24        (454U)    /* GTM ATOMDREQ24 */
#define    PIL_DTS_GR3_ATOMDREQ25        (455U)    /* GTM ATOMDREQ25 */
#define    PIL_DTS_GR3_ATOMDREQ26        (456U)    /* GTM ATOMDREQ26 */
#define    PIL_DTS_GR3_ATOMDREQ27        (457U)    /* GTM ATOMDREQ27 */
#define    PIL_DTS_GR3_ATOMDREQ30        (458U)    /* GTM ATOMDREQ30 */
#define    PIL_DTS_GR3_ATOMDREQ31        (459U)    /* GTM ATOMDREQ31 */
#define    PIL_DTS_GR3_ATOMDREQ32        (460U)    /* GTM ATOMDREQ32 */
#define    PIL_DTS_GR3_ATOMDREQ33        (461U)    /* GTM ATOMDREQ33 */
#define    PIL_DTS_GR3_ATOMDREQ34        (462U)    /* GTM ATOMDREQ34 */
#define    PIL_DTS_GR3_ATOMDREQ35        (463U)    /* GTM ATOMDREQ35 */
#define    PIL_DTS_GR3_ATOMDREQ36        (464U)    /* GTM ATOMDREQ36 */
#define    PIL_DTS_GR3_ATOMDREQ37        (465U)    /* GTM ATOMDREQ37 */
#define    PIL_DTS_GR3_INTOSTM0TINT        (466U)    /* OSTM INTOSTM0TINT */
#define    PIL_DTS_GR3_INTOSTM1TINT        (467U)    /* OSTM INTOSTM1TINT */
#define    PIL_DTS_GR3_INTOSTM2TINT        (468U)    /* OSTM INTOSTM2TINT */
#define    PIL_DTS_GR3_INTOSTM3TINT        (469U)    /* OSTM INTOSTM3TINT */
#define    PIL_DTS_GR3_INTOSTM4TINT        (470U)    /* OSTM INTOSTM4TINT */
#define    PIL_DTS_GR3_INTOSTM5TINT        (471U)    /* OSTM INTOSTM5TINT */
#define    PIL_DTS_GR3_INTOSTM6TINT        (472U)    /* OSTM INTOSTM6TINT */
#define    PIL_DTS_GR3_INTOSTM7TINT        (473U)    /* OSTM INTOSTM7TINT */
#define    PIL_DTS_GR3_INTOSTM8TINT        (474U)    /* OSTM INTOSTM8TINT */
#define    PIL_DTS_GR3_INTOSTM9TINT        (475U)    /* OSTM INTOSTM9TINT */
#define    PIL_DTS_GR3_INTTPBA0IPRD        (476U)    /* TPBA INTTPBA0IPRD */
#define    PIL_DTS_GR3_INTTPBA0IDTY        (477U)    /* TPBA INTTPBA0IDTY */
#define    PIL_DTS_GR3_INTTPBA0IPAT        (478U)    /* TPBA INTTPBA0IPAT */
#define    PIL_DTS_GR3_INTTPBA1IPRD        (479U)    /* TPBA INTTPBA1IPRD */
#define    PIL_DTS_GR3_INTTPBA1IDTY        (480U)    /* TPBA INTTPBA1IDTY */
#define    PIL_DTS_GR3_INTTPBA1IPAT        (481U)    /* TPBA INTTPBA1IPAT */
#define    PIL_DTS_GR3_INTP10        (482U)    /* PORT INTP10 */
#define    PIL_DTS_GR3_INTP11        (483U)    /* PORT INTP11 */
#define    PIL_DTS_GR3_INTP12        (484U)    /* PORT INTP12 */
#define    PIL_DTS_GR3_INTP13        (485U)    /* PORT INTP13 */
#define    PIL_DTS_GR3_INTP14        (486U)    /* PORT INTP14 */
#define    PIL_DTS_GR3_INTP15        (487U)    /* PORT INTP15 */
#define    PIL_DTS_GR3_INTP16        (488U)    /* PORT INTP16 */
#define    PIL_DTS_GR3_INTP17        (489U)    /* PORT INTP17 */
#define    PIL_DTS_GR3_INTP18        (490U)    /* PORT INTP18 */
#define    PIL_DTS_GR3_INTP19        (491U)    /* PORT INTP19 */
#define    PIL_DTS_GR3_INTP20        (492U)    /* PORT INTP20 */
#define    PIL_DTS_GR3_INTP21        (493U)    /* PORT INTP21 */
#define    PIL_DTS_GR3_INTP22        (494U)    /* PORT INTP22 */
#define    PIL_DTS_GR3_INTP23        (495U)    /* PORT INTP23 */
#define    PIL_DTS_GR3_INTP24        (496U)    /* PORT INTP24 */
#define    PIL_DTS_GR3_INTP25        (497U)    /* PORT INTP25 */
#define    PIL_DTS_GR3_INTP26        (498U)    /* PORT INTP26 */
#define    PIL_DTS_GR3_INTP27        (499U)    /* PORT INTP27 */
#define    PIL_DTS_GR3_INTP28        (500U)    /* PORT INTP28 */
#define    PIL_DTS_GR3_INTP29        (501U)    /* PORT INTP29 */
#define    PIL_DTS_GR3_INTP30        (502U)    /* PORT INTP30 */
#define    PIL_DTS_GR3_INTP31        (503U)    /* PORT INTP31 */
#define    PIL_DTS_GR3_INTP32        (504U)    /* PORT INTP32 */
#define    PIL_DTS_GR3_INTP33        (505U)    /* PORT INTP33 */
#define    PIL_DTS_GR3_INTP34        (506U)    /* PORT INTP34 */
#define    PIL_DTS_GR3_INTP35        (507U)    /* PORT INTP35 */
#define    PIL_DTS_GR3_INTP36        (508U)    /* PORT INTP36 */
#define    PIL_DTS_GR3_INTP37        (509U)    /* PORT INTP37 */
#define    PIL_DTS_GR3_INTP38        (510U)    /* PORT INTP38 */
#define    PIL_DTS_GR3_INTP39        (511U)    /* PORT INTP39 */

#elif (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
/* U2B */

/* DTS transfer request definition group 0(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR0_EMU0_INT_0					(0U)		/* EMU EMU0_INT[0] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT0				(0U)		/* DFP DFP_INT_OUT0 */
#define		PIL_DTS_GR0_EMU0_INT_1					(1U)		/* EMU EMU0_INT[1] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT1				(1U)		/* DFP DFP_INT_OUT1 */
#define		PIL_DTS_GR0_EMU0_INT_2					(2U)		/* EMU EMU0_INT[2] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT2				(2U)		/* DFP DFP_INT_OUT2 */
#define		PIL_DTS_GR0_EMU0_INT_3					(3U)		/* EMU EMU0_INT[3]"" */
#define		PIL_DTS_GR0_DFP_INT_OUT3				(3U)		/* DFP DFP_INT_OUT3 */
#define		PIL_DTS_GR0_EMU0_INT_4					(4U)		/* EMU EMU0_INT[4]"" */
#define		PIL_DTS_GR0_DFP_INT_OUT4				(4U)		/* DFP DFP_INT_OUT4 */
#define		PIL_DTS_GR0_EMU0_INT_5					(5U)		/* EMU EMU0_INT[5] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT5				(5U)		/* DFP DFP_INT_OUT5 */
#define		PIL_DTS_GR0_EMU0_INT_6					(6U)		/* EMU EMU0_INT[6] "" */
#define		PIL_DTS_GR0_DFP_INT_OUT6				(6U)		/* DFP DFP_INT_OUT6 */
#define		PIL_DTS_GR0_EMU0_INT_7					(7U)		/* EMU EMU0_INT[7] "" */
#define		PIL_DTS_GR0_DFP_INT_OUT7				(7U)		/* DFP DFP_INT_OUT7 */

#define		PIL_DTS_GR0_DFP_INT_OUT8				(8U)		/* DFP DFP_INT_OUT8 */

#define		PIL_DTS_GR0_DFP_INT_OUT9				(9U)		/* DFP DFP_INT_OUT9 */
#define		PIL_DTS_GR0_EMU1_INT_0					(10U)	/* EMU EMU1_INT[0] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT10				(10U)	/* DFP DFP_INT_OUT10 */
#define		PIL_DTS_GR0_EMU1_INT_1					(11U)	/* EMU EMU1_INT[1] "" */
#define		PIL_DTS_GR0_DFP_INT_OUT11				(11U)	/* DFP DFP_INT_OUT11 */
#define		PIL_DTS_GR0_EMU1_INT_2					(12U)	/* EMU EMU1_INT[2] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT12				(12U)	/* DFP DFP_INT_OUT12 */
#define		PIL_DTS_GR0_EMU1_INT_3					(13U)	/* EMU EMU1_INT[3] "" */
#define		PIL_DTS_GR0_DFP_INT_OUT13				(13U)	/* DFP DFP_INT_OUT13 */
#define		PIL_DTS_GR0_EMU1_INT_4					(14U)	/* EMU EMU1_INT[4] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT14				(14U)	/* DFP DFP_INT_OUT14 */
#define		PIL_DTS_GR0_EMU1_INT_5					(15U)	/* EMU EMU1_INT[5] ""*/
#define		PIL_DTS_GR0_DFP_INT_OUT15				(15U)	/* DFP DFP_INT_OUT15 */
#define		PIL_DTS_GR0_EMU1_INT_6					(16U)	/* EMU EMU1_INT[6] ""*/
#define		PIL_DTS_GR0_INTRIIC0RI					(16U)	/* RIIC INTRIIC0RI */
#define		PIL_DTS_GR0_EMU1_INT_7					(17U)	/* EMU EMU1_INT[7] ""*/
#define		PIL_DTS_GR0_INTRIIC0TI					(17U)	/* RIIC INTRIIC0TI */

#define		PIL_DTS_GR0_INTRIIC1RI					(18U)	/* RIIC INTRIIC1RI */

#define		PIL_DTS_GR0_INTRIIC1TI					(19U)	/* RIIC INTRIIC1TI */
#define		PIL_DTS_GR0_INTENCA0IOV					(20U)	/* ENCA INTENCA0IOV  */
#define		PIL_DTS_GR0_INTENCA0I0					(21U)	/* ENCA INTENCA0I0 */
#define		PIL_DTS_GR0_INTENCA0I1					(22U)	/* ENCA INTENCA0I1 */
#define		PIL_DTS_GR0_INTENCA0IUD					(23U)	/* ENCA INTENCA0IUD */
#define		PIL_DTS_GR0_INTENCA0IEC					(24U)	/* ENCA INTENCA0IEC */
#define		PIL_DTS_GR0_INTENCA1IOV					(25U)	/* ENCA INTENCA1IOV */
#define		PIL_DTS_GR0_INTENCA1I0					(26U)	/* ENCA INTENCA1I0 */
#define		PIL_DTS_GR0_INTENCA1I1					(27U)	/* ENCA INTENCA1I1 */
#define		PIL_DTS_GR0_INTENCA1IUD					(28U)	/* ENCA INTENCA1IUD */
#define		PIL_DTS_GR0_INTENCA1IEC					(29U)	/* ENCA INTENCA1IEC */
#define		PIL_DTS_GR0_INTPSI50RI					(30U)	/* PSI5 INTPSI50RI */
#define		PIL_DTS_GR0_INTPSI51RI					(31U)	/* PSI5 INTPSI51RI */
#define		PIL_DTS_GR0_INTPSI52RI					(32U)	/* PSI5 INTPSI52RI */
#define		PIL_DTS_GR0_INTPSI53RI					(33U)	/* PSI5 INTPSI53RI */

#define		PIL_DTS_GR0_INTPSI5S0RXDMACH0			(35U)	/* PSI5S INTPSI5S0RXDMACH0 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH1			(36U)	/* PSI5S INTPSI5S0RXDMACH1 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH2			(37U)	/* PSI5S INTPSI5S0RXDMACH2 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH3			(38U)	/* PSI5S INTPSI5S0RXDMACH3 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH4			(39U)	/* PSI5S INTPSI5S0RXDMACH4 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH5			(40U)	/* PSI5S INTPSI5S0RXDMACH5 */
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH6			(41U)	/* PSI5S INTPSI5S0RXDMACH6*/
#define		PIL_DTS_GR0_INTPSI5S0RXDMACH7			(42U)	/* PSI5S INTPSI5S0RXDMACH7 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH1			(43U)	/* PSI5S INTPSI5S0TXDMACH1 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH2			(44U)	/* PSI5S INTPSI5S0TXDMACH2 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH3			(45U)	/* PSI5S INTPSI5S0TXDMACH3 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH4			(46U)	/* PSI5S INTPSI5S0TXDMACH4 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH5			(47U)	/* PSI5S INTPSI5S0TXDMACH5 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH6			(48U)	/* PSI5S INTPSI5S0TXDMACH6 */
#define		PIL_DTS_GR0_INTPSI5S0TXDMACH7			(49U)	/* PSI5S INTPSI5S0TXDMACH7 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH0			(50U)	/* PSI5S INTPSI5S1RXDMACH0 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH1			(51U)	/* PSI5S INTPSI5S1RXDMACH1 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH2			(52U)	/* PSI5S INTPSI5S1RXDMACH2 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH3			(53U)	/* PSI5S INTPSI5S1RXDMACH3 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH4			(54U)	/* PSI5S INTPSI5S1RXDMACH4 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH5			(55U)	/* PSI5S INTPSI5S1RXDMACH5 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH6			(56U)	/* PSI5S INTPSI5S1RXDMACH6 */
#define		PIL_DTS_GR0_INTPSI5S1RXDMACH7			(57U)	/* PSI5S INTPSI5S1RXDMACH7 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH1			(58U)	/* PSI5S INTPSI5S1TXDMACH1 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH2			(59U)	/* PSI5S INTPSI5S1TXDMACH2 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH3			(60U)	/* PSI5S INTPSI5S1TXDMACH3 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH4			(61U)	/* PSI5S INTPSI5S1TXDMACH4 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH5			(62U)	/* PSI5S INTPSI5S1TXDMACH5 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH6			(63U)	/* PSI5S INTPSI5S1TXDMACH6 */
#define		PIL_DTS_GR0_INTPSI5S1TXDMACH7			(64U)	/* PSI5S INTPSI5S1TXDMACH7 */
#define		PIL_DTS_GR0_FCMP0_DACDATACHG			(65U)	/* FCMP FCMP0_DACDATACHG */
#define		PIL_DTS_GR0_FCMP1_DACDATACHG			(66U)	/* FCMP FCMP1_DACDATACHG */
#define		PIL_DTS_GR0_FCMP2_DACDATACHG			(67U)	/* FCMP FCMP2_DACDATACHG */
#define		PIL_DTS_GR0_FCMP3_DACDATACHG			(68U)	/* FCMP FCMP3_DACDATACHG */
#define		PIL_DTS_GR0_FCMP4_DACDATACHG			(69U)	/* FCMP FCMP4_DACDATACHG */
#define		PIL_DTS_GR0_FCMP5_DACDATACHG			(70U)	/* FCMP FCMP5_DACDATACHG */
#define		PIL_DTS_GR0_FCMP6_DACDATACHG			(71U)	/* FCMP FCMP6_DACDATACHG */
#define		PIL_DTS_GR0_FCMP7_DACDATACHG			(72U)	/* FCMP FCMP7_DACDATACHG */
#define		PIL_DTS_GR0_FCMP8_DACDATACHG			(73U)	/* FCMP FCMP8_DACDATACHG */
#define		PIL_DTS_GR0_FCMP9_DACDATACHG			(74U)	/* FCMP FCMP9_DACDATACHG */
#define		PIL_DTS_GR0_INTRDC3AL0CMP2				(75U)	/* RDC (RDC3AL) INTRDC3AL0CMP2 */
#define		PIL_DTS_GR0_INTRDC3AS0CMP2				(75U)	/* RDC (RDC3AS) INTRDC3AS0CMP2 */
#define		PIL_DTS_GR0_INTRDC3AL0CMP1				(76U)	/* RDC (RDC3AL) INTRDC3AL0CMP1 */
#define		PIL_DTS_GR0_INTRDC3AS0CMP1				(76U)	/* RDC (RDC3AS) INTRDC3AS0CMP1 */
#define		PIL_DTS_GR0_INTRDC3AL0CMP0				(77U)	/* RDC (RDC3AL) INTRDC3AL0CMP0 */
#define		PIL_DTS_GR0_INTRDC3AS0CMP0				(77U)	/* RDC (RDC3AS) INTRDC3AS0CMP0 */
#define		PIL_DTS_GR0_INTRDC3AL0ENCZ				(78U)	/* RDC (RDC3AL) INTRDC3AL0ENCZ */
#define		PIL_DTS_GR0_INTRDC3AS0ENCZ				(78U)	/* RDC (RDC3AS) INTRDC3AS0ENCZ */
#define		PIL_DTS_GR0_INTRDC3AL0EZC				(79U)	/* RDC (RDC3AL) INTRDC3AL0EZC */
#define		PIL_DTS_GR0_INTRDC3AS0EZC				(79U)	/* RDC (RDC3AS) INTRDC3AS0EZC */
#define		PIL_DTS_GR0_DMARDC3AL0ET				(80U)	/* RDC (RDC3AL) DMARDC3AL0ET */
#define		PIL_DTS_GR0_DMARDC3AS0ET				(80U)	/* RDC (RDC3AS) DMARDC3AS0ET */
#define		PIL_DTS_GR0_INTRDC3AL1CMP2				(81U)	/* RDC (RDC3AL) INTRDC3AL1CMP2 */
#define		PIL_DTS_GR0_INTRDC3AS1CMP2				(81U)	/* RDC (RDC3AS) INTRDC3AS1CMP2 */
#define		PIL_DTS_GR0_INTRDC3AL1CMP1				(82U)	/* RDC (RDC3AL) INTRDC3AL1CMP1 */
#define		PIL_DTS_GR0_INTRDC3AS1CMP1				(82U)	/* RDC (RDC3AS) INTRDC3AS1CMP1 */
#define		PIL_DTS_GR0_INTRDC3AL1CMP0				(83U)	/* RDC (RDC3AL) INTRDC3AL1CMP0 */
#define		PIL_DTS_GR0_INTRDC3AS1CMP0				(83U)	/* RDC (RDC3AS) INTRDC3AS1CMP0 */
#define		PIL_DTS_GR0_INTRDC3AL1ENCZ				(84U)	/* RDC (RDC3AL) INTRDC3AL1ENCZ */
#define		PIL_DTS_GR0_INTRDC3AS1ENCZ				(84U)	/* RDC (RDC3AS) INTRDC3AS1ENCZ */
#define		PIL_DTS_GR0_INTRDC3AL1EZC				(85U)	/* RDC (RDC3AL) INTRDC3AL1EZC */
#define		PIL_DTS_GR0_INTRDC3AS1EZC				(85U)	/* RDC (RDC3AS) INTRDC3AS1EZC */
#define		PIL_DTS_GR0_DMARDC3AL1ET				(86U)	/* RDC (RDC3AL) DMARDC3AL1ET */
#define		PIL_DTS_GR0_DMARDC3AS1ET				(86U)	/* RDC (RDC3AS) DMARDC3AS1ET */

#define		PIL_DTS_GR0_INTTAPA0IPEK0				(91U)	/* TAPA INTTAPA0IPEK0 */
#define		PIL_DTS_GR0_INTTAPA0IVLY0				(92U)	/* TAPA INTTAPA0IVLY0 */
#define		PIL_DTS_GR0_INTTAPA1IPEK0				(93U)	/* TAPA INTTAPA1IPEK0 */
#define		PIL_DTS_GR0_INTTAPA1IVLY0				(94U)	/* TAPA INTTAPA1IVLY0 */
#define		PIL_DTS_GR0_INTTAPA2IPEK0				(95U)	/* TAPA INTTAPA2IPEK0 */
#define		PIL_DTS_GR0_INTTAPA2IVLY0				(96U)	/* TAPA INTTAPA2IVLY0 */
#define		PIL_DTS_GR0_INTTPBA0IPRD				(97U)	/* TPBA INTTPBA0IPRD */
#define		PIL_DTS_GR0_INTTPBA0IDTY				(98U)	/* TPBA INTTPBA0IDTY */
#define		PIL_DTS_GR0_INTTPBA0IPAT				(99U)	/* TPBA INTTPBA0IPAT */
#define		PIL_DTS_GR0_INTTPBA1IPRD				(100U)	/* TPBA INTTPBA1IPRD */
#define		PIL_DTS_GR0_INTTPBA1IDTY				(101U)	/* TPBA INTTPBA1IDTY */
#define		PIL_DTS_GR0_INTTPBA1IPAT				(102U)	/* TPBA INTTPBA1IPAT */
#define		PIL_DTS_GR0_INTTAUJ2I0					(103U)	/* TAUJ INTTAUJ2I0 */
#define		PIL_DTS_GR0_INTTAUJ2I1					(104U)	/* TAUJ INTTAUJ2I1 */
#define		PIL_DTS_GR0_INTTAUJ2I2					(105U)	/* TAUJ INTTAUJ2I2 */
#define		PIL_DTS_GR0_INTTAUJ2I3					(106U)	/* TAUJ INTTAUJ2I3 */
#define		PIL_DTS_GR0_INTTAUJ3I0					(107U)	/* TAUJ INTTAUJ3I0 */
#define		PIL_DTS_GR0_INTTAUJ3I1					(108U)	/* TAUJ INTTAUJ3I1 */
#define		PIL_DTS_GR0_INTTAUJ3I2					(109U)	/* TAUJ INTTAUJ3I2 */
#define		PIL_DTS_GR0_INTTAUJ3I3					(110U)	/* TAUJ INTTAUJ3I3 */
#define		PIL_DTS_GR0_INTTSG30I11					(111U)	/* TSG3 INTTSG30I11 */
#define		PIL_DTS_GR0_INTTSG30I12					(112U)	/* TSG3 INTTSG30I12 */
#define		PIL_DTS_GR0_INTTSG30IPEK				(113U)	/* TSG3 INTTSG30IPEK */
#define		PIL_DTS_GR0_INTTSG30IVLY				(114U)	/* TSG3 INTTSG30IVLY */
#define		PIL_DTS_GR0_INTTSG31I11					(115U)	/* TSG3 INTTSG31I11 */
#define		PIL_DTS_GR0_INTTSG31I12					(116U)	/* TSG3 INTTSG31I12 */
#define		PIL_DTS_GR0_INTTSG31IPEK				(117U)	/* TSG3 INTTSG31IPEK */
#define		PIL_DTS_GR0_INTTSG31IVLY				(118U)	/* TSG3 INTTSG31IVLY */
#define		PIL_DTS_GR0_INTTSG32I11					(119U)	/* TSG3 INTTSG32I11 */
#define		PIL_DTS_GR0_INTTSG32I12					(120U)	/* TSG3 INTTSG32I12 */
#define		PIL_DTS_GR0_INTTSG32IPEK				(121U)	/* TSG3 INTTSG32IPEK */
#define		PIL_DTS_GR0_INTTSG32IVLY				(122U)	/* TSG3 INTTSG32IVLY */

#define		PIL_DTS_GR0_INTDMAFL0					(124U)	/* FLASH INTDMAFL0 */

#define		PIL_DTS_GR0_INTDMAFL2					(126U)	/* FLASH INTDMAFL2 */
#define		PIL_DTS_GR0_DMAMMCA0					(127U)	/* EMMCA DMAMMCA0 */

/* DTS transfer request definition group 1(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR1_DTSMSPI0					(128U)	/* MSPI DTSMSPI0 */
#define		PIL_DTS_GR1_DTSMSPI1					(129U)	/* MSPI DTSMSPI1 */
#define		PIL_DTS_GR1_DTSMSPI2					(130U)	/* MSPI DTSMSPI2 */
#define		PIL_DTS_GR1_DTSMSPI3					(131U)	/* MSPI DTSMSPI3 */
#define		PIL_DTS_GR1_DTSMSPI4					(132U)	/* MSPI DTSMSPI4 */
#define		PIL_DTS_GR1_DTSMSPI5					(133U)	/* MSPI DTSMSPI5 */
#define		PIL_DTS_GR1_DTSMSPI6					(134U)	/* MSPI DTSMSPI6 */
#define		PIL_DTS_GR1_DTSMSPI7					(135U)	/* MSPI DTSMSPI7 */
#define		PIL_DTS_GR1_DTSMSPI8					(136U)	/* MSPI DTSMSPI8 */
#define		PIL_DTS_GR1_DTSMSPI9					(137U)	/* MSPI DTSMSPI9 */
#define		PIL_DTS_GR1_DTSMSPI10					(138U)	/* MSPI DTSMSPI10 */
#define		PIL_DTS_GR1_DTSMSPI11					(139U)	/* MSPI DTSMSPI11 */
#define		PIL_DTS_GR1_DTSMSPI12					(140U)	/* MSPI DTSMSPI12 */
#define		PIL_DTS_GR1_DTSMSPI13					(141U)	/* MSPI DTSMSPI13 */
#define		PIL_DTS_GR1_DTSMSPI14					(142U)	/* MSPI DTSMSPI14 */
#define		PIL_DTS_GR1_DTSMSPI15					(143U)	/* MSPI DTSMSPI15 */
#define		PIL_DTS_GR1_DTSMSPI16					(144U)	/* MSPI DTSMSPI16 */
#define		PIL_DTS_GR1_DTSMSPI17					(145U)	/* MSPI DTSMSPI17 */
#define		PIL_DTS_GR1_DTSMSPI18					(146U)	/* MSPI DTSMSPI18 */
#define		PIL_DTS_GR1_DTSMSPI19					(147U)	/* MSPI DTSMSPI19 */
#define		PIL_DTS_GR1_DTSMSPI20					(148U)	/* MSPI DTSMSPI20 */
#define		PIL_DTS_GR1_DTSMSPI21					(149U)	/* MSPI DTSMSPI21 */
#define		PIL_DTS_GR1_DTSMSPI22					(150U)	/* MSPI DTSMSPI22 */
#define		PIL_DTS_GR1_DTSMSPI23					(151U)	/* MSPI DTSMSPI23 */
#define		PIL_DTS_GR1_DTSMSPI24					(152U)	/* MSPI DTSMSPI24 */
#define		PIL_DTS_GR1_DTSMSPI25					(153U)	/* MSPI DTSMSPI25 */
#define		PIL_DTS_GR1_DTSMSPI26					(154U)	/* MSPI DTSMSPI26 */
#define		PIL_DTS_GR1_DTSMSPI27					(155U)	/* MSPI DTSMSPI27 */
#define		PIL_DTS_GR1_DTSMSPI28					(156U)	/* MSPI DTSMSPI28 */
#define		PIL_DTS_GR1_DTSMSPI29					(157U)	/* MSPI DTSMSPI29 */
#define		PIL_DTS_GR1_DTSMSPI30					(158U)	/* MSPI DTSMSPI30 */
#define		PIL_DTS_GR1_DTSMSPI31					(159U)	/* MSPI DTSMSPI31 */
#define		PIL_DTS_GR1_DTSMSPI32					(160U)	/* MSPI DTSMSPI32 */
#define		PIL_DTS_GR1_DTSMSPI33					(161U)	/* MSPI DTSMSPI33 */
#define		PIL_DTS_GR1_DTSMSPI34					(162U)	/* MSPI DTSMSPI34 */
#define		PIL_DTS_GR1_DTSMSPI35					(163U)	/* MSPI DTSMSPI35 */
#define		PIL_DTS_GR1_DTSMSPI36					(164U)	/* MSPI DTSMSPI36 */
#define		PIL_DTS_GR1_DTSMSPI37					(165U)	/* MSPI DTSMSPI37 */
#define		PIL_DTS_GR1_DTSMSPI38					(166U)	/* MSPI DTSMSPI38 */
#define		PIL_DTS_GR1_DTSMSPI39					(167U)	/* MSPI DTSMSPI39 */
#define		PIL_DTS_GR1_DTSMSPI40					(168U)	/* MSPI DTSMSPI40 */
#define		PIL_DTS_GR1_DTSMSPI41					(169U)	/* MSPI DTSMSPI41 */
#define		PIL_DTS_GR1_DTSMSPI42					(170U)	/* MSPI DTSMSPI42 */
#define		PIL_DTS_GR1_DTSMSPI43					(171U)	/* MSPI DTSMSPI43 */
#define		PIL_DTS_GR1_DTSMSPI44					(172U)	/* MSPI DTSMSPI44 */
#define		PIL_DTS_GR1_DTSMSPI45					(173U)	/* MSPI DTSMSPI45 */
#define		PIL_DTS_GR1_DTSMSPI46					(174U)	/* MSPI DTSMSPI46 */
#define		PIL_DTS_GR1_DTSMSPI47					(175U)	/* MSPI DTSMSPI47 */
#define		PIL_DTS_GR1_DTSMSPI48					(176U)	/* MSPI DTSMSPI48 */
#define		PIL_DTS_GR1_DTSMSPI49					(177U)	/* MSPI DTSMSPI49 */
#define		PIL_DTS_GR1_DTSMSPI50					(178U)	/* MSPI DTSMSPI50 */
#define		PIL_DTS_GR1_DTSMSPI51					(179U)	/* MSPI DTSMSPI51 */
#define		PIL_DTS_GR1_DTSMSPI52					(180U)	/* MSPI DTSMSPI52 */
#define		PIL_DTS_GR1_DTSMSPI53					(181U)	/* MSPI DTSMSPI53 */
#define		PIL_DTS_GR1_DTSMSPI54					(182U)	/* MSPI DTSMSPI54 */
#define		PIL_DTS_GR1_DTSMSPI55					(183U)	/* MSPI DTSMSPI55 */
#define		PIL_DTS_GR1_DTSMSPI56					(184U)	/* MSPI DTSMSPI56 */
#define		PIL_DTS_GR1_DTSMSPI57					(185U)	/* MSPI DTSMSPI57 */
#define		PIL_DTS_GR1_DTSMSPI58					(186U)	/* MSPI DTSMSPI58 */
#define		PIL_DTS_GR1_DTSMSPI59					(187U)	/* MSPI DTSMSPI59 */
#define		PIL_DTS_GR1_DTSMSPI60					(188U)	/* MSPI DTSMSPI60 */
#define		PIL_DTS_GR1_DTSMSPI61					(189U)	/* MSPI DTSMSPI61 */
#define		PIL_DTS_GR1_DTSMSPI62					(190U)	/* MSPI DTSMSPI62 */
#define		PIL_DTS_GR1_DTSMSPI63					(191U)	/* MSPI DTSMSPI63 */

#define		PIL_DTS_GR1_INTOSTM0TINT				(193U)	/* OSTM INTOSTM0TINT */
#define		PIL_DTS_GR1_INTOSTM1TINT				(194U)	/* OSTM INTOSTM1TINT */
#define		PIL_DTS_GR1_INTOSTM2TINT				(195U)	/* OSTM INTOSTM2TINT */
#define		PIL_DTS_GR1_INTOSTM3TINT				(196U)	/* OSTM INTOSTM3TINT */
#define		PIL_DTS_GR1_INTOSTM4TINT				(197U)	/* OSTM INTOSTM4TINT */
#define		PIL_DTS_GR1_INTOSTM5TINT				(198U)	/* OSTM INTOSTM5TINT */

#define		PIL_DTS_GR1_DRQRHSB0DWNCMDS				(208U)	/* RHSB DRQRHSB0DWNCMDS */
#define		PIL_DTS_GR1_DRQRHSB0DWNCMDD				(209U)	/* RHSB DRQRHSB0DWNCMDD */
#define		PIL_DTS_GR1_DRQRHSB0UPDATA 				(210U)	/* RHSB DRQRHSB0UPDATA  */
#define		PIL_DTS_GR1_DRQRHSB0DWNDATA				(211U)	/* RHSB DRQRHSB0DWNDATA */
#define		PIL_DTS_GR1_DRQRHSB0UPCMD				(212U)	/* RHSB DRQRHSB0UPCMD */
#define		PIL_DTS_GR1_DRQRHSB0EXI0				(213U)	/* RHSB DRQRHSB0EXI0 */
#define		PIL_DTS_GR1_DRQRHSB0EXI1				(214U)	/* RHSB DRQRHSB0EXI1 */
#define		PIL_DTS_GR1_DRQRHSB1DWNCMDS				(215U)	/* RHSB DRQRHSB1DWNCMDS */
#define		PIL_DTS_GR1_DRQRHSB1DWNCMDD				(216U)	/* RHSB DRQRHSB1DWNCMDD */
#define		PIL_DTS_GR1_DRQRHSB1UPDATA 				(217U)	/* RHSB DRQRHSB1UPDATA */
#define		PIL_DTS_GR1_DRQRHSB1DWNDATA 			(218U)	/* RHSB DRQRHSB1DWNDATA */
#define		PIL_DTS_GR1_DRQRHSB1UPCMD				(219U)	/* RHSB DRQRHSB1UPCMD */
#define		PIL_DTS_GR1_DRQRHSB1EXI0				(220U)	/* RHSB DRQRHSB1EXI0 */
#define		PIL_DTS_GR1_DRQRHSB1EXI1				(221U)	/* RHSB DRQRHSB1EXI1 */
#define		PIL_DTS_GR1_DRQRHSB2DWNCMDS				(222U)	/* RHSB DRQRHSB2DWNCMDS */
#define		PIL_DTS_GR1_DRQRHSB2DWNCMDD				(223U)	/* RHSB DRQRHSB2DWNCMDD */
#define		PIL_DTS_GR1_DRQRHSB2UPDATA 				(224U)	/* RHSB DRQRHSB2UPDATA */
#define		PIL_DTS_GR1_DRQRHSB2DWNDATA 			(225U)	/* RHSB DRQRHSB2DWNDATA */
#define		PIL_DTS_GR1_DRQRHSB2UPCMD				(226U)	/* RHSB DRQRHSB2UPCMD */
#define		PIL_DTS_GR1_DRQRHSB2EXI0				(227U)	/* RHSB DRQRHSB2EXI0 */
#define		PIL_DTS_GR1_DRQRHSB2EXI1				(228U)	/* RHSB DRQRHSB2EXI1 */
#define		PIL_DTS_GR1_DRQRHSB3DWNCMDS				(229U)	/* RHSB DRQRHSB3DWNCMDS */
#define		PIL_DTS_GR1_DRQRHSB3DWNCMDD				(230U)	/* RHSB DRQRHSB3DWNCMDD */
#define		PIL_DTS_GR1_DRQRHSB3UPDATA 				(231U)	/* RHSB DRQRHSB3UPDATA  */
#define		PIL_DTS_GR1_DRQRHSB3DWNDATA				(232U)	/* RHSB DRQRHSB3DWNDATA */
#define		PIL_DTS_GR1_DRQRHSB3UPCMD				(233U)	/* RHSB DRQRHSB3UPCMD */
#define		PIL_DTS_GR1_DRQRHSB3EXI0				(234U)	/* RHSB DRQRHSB3EXI0 */
#define		PIL_DTS_GR1_DRQRHSB3EXI1				(235U)	/* RHSB DRQRHSB3EXI1 */
#define		PIL_DTS_GR1_INTRHSIF0INTCH0				(236U)	/* RHSIF INTRHSIF0INTCH0 */
#define		PIL_DTS_GR1_INTRHSIF0INTCH1				(237U)	/* RHSIF INTRHSIF0INTCH1 */
#define		PIL_DTS_GR1_INTRHSIF0INTCH2				(238U)	/* RHSIF INTRHSIF0INTCH2 */
#define		PIL_DTS_GR1_INTRHSIF0INTCH3				(239U)	/* RHSIF INTRHSIF0INTCH3 */
#define		PIL_DTS_GR1_INTRHSIF1INTCH0				(240U)	/* RHSIF INTRHSIF1INTCH0 */
#define		PIL_DTS_GR1_INTRHSIF1INTCH1				(241U)	/* RHSIF INTRHSIF1INTCH1 */
#define		PIL_DTS_GR1_INTRHSIF1INTCH2				(242U)	/* RHSIF INTRHSIF1INTCH2 */
#define		PIL_DTS_GR1_INTRHSIF1INTCH3				(243U)	/* RHSIF INTRHSIF1INTCH3 */
#define		PIL_DTS_GR1_INTTPTMU00					(244U)	/* TPTM INTTPTMU00 */
#define		PIL_DTS_GR1_INTTPTMU01					(245U)	/* TPTM INTTPTMU01 */
#define		PIL_DTS_GR1_INTTPTMU10					(246U)	/* TPTM INTTPTMU10 */
#define		PIL_DTS_GR1_INTTPTMU11					(247U)	/* TPTM INTTPTMU11 */
#define		PIL_DTS_GR1_INTTPTMU20					(248U)	/* TPTM INTTPTMU20 */
#define		PIL_DTS_GR1_INTTPTMU21					(249U)	/* TPTM INTTPTMU21 */
#define		PIL_DTS_GR1_INTTPTMU30					(250U)	/* TPTM INTTPTMU30 */
#define		PIL_DTS_GR1_INTTPTMU31					(251U)	/* TPTM INTTPTMU31 */
#define		PIL_DTS_GR1_INTTPTMU40					(252U)	/* TPTM INTTPTMU40 */
#define		PIL_DTS_GR1_INTTPTMU41					(253U)	/* TPTM INTTPTMU41 */
#define		PIL_DTS_GR1_INTTPTMU50					(254U)	/* TPTM INTTPTMU50 */
#define		PIL_DTS_GR1_INTTPTMU51					(255U)	/* TPTM INTTPTMU51 */

/* DTS transfer request definition group 2(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR2_INTRLIN36UR0				(256U)	/* RLIN3 INTRLIN36UR0 */
#define		PIL_DTS_GR2_INTRLIN36UR1				(257U)	/* RLIN3 INTRLIN36UR1 */
#define		PIL_DTS_GR2_INTRLIN37UR0				(258U)	/* RLIN3 INTRLIN37UR0 */
#define		PIL_DTS_GR2_INTRLIN37UR1				(259U)	/* RLIN3 INTRLIN37UR1 */
#define		PIL_DTS_GR2_INTRLIN38UR0				(260U)	/* RLIN3 INTRLIN38UR0 */
#define		PIL_DTS_GR2_INTRLIN38UR1				(261U)	/* RLIN3 INTRLIN38UR1 */
#define		PIL_DTS_GR2_INTRLIN39UR0				(262U)	/* RLIN3 INTRLIN39UR0 */
#define		PIL_DTS_GR2_INTRLIN39UR1				(263U)	/* RLIN3 INTRLIN39UR1 */
#define		PIL_DTS_GR2_INTRLIN310UR0				(264U)	/* RLIN3 INTRLIN310UR0 */
#define		PIL_DTS_GR2_INTRLIN310UR1				(265U)	/* RLIN3 INTRLIN310UR1 */
#define		PIL_DTS_GR2_INTRLIN311UR0				(266U)	/* RLIN3 INTRLIN311UR0 */
#define		PIL_DTS_GR2_INTRLIN311UR1				(267U)	/* RLIN3 INTRLIN311UR1 */
#define		PIL_DTS_GR2_INTRLIN312UR0				(268U)	/* RLIN3 INTRLIN312UR0 */
#define		PIL_DTS_GR2_INTRLIN312UR1				(269U)	/* RLIN3 INTRLIN312UR1 */
#define		PIL_DTS_GR2_INTRLIN313UR0				(270U)	/* RLIN3 INTRLIN313UR0 */
#define		PIL_DTS_GR2_INTRLIN313UR1				(271U)	/* RLIN3 INTRLIN313UR1 */
#define		PIL_DTS_GR2_INTRLIN314UR0				(272U)	/* RLIN3 INTRLIN314UR0 */
#define		PIL_DTS_GR2_INTRLIN314UR1				(273U)	/* RLIN3 INTRLIN314UR1 */
#define		PIL_DTS_GR2_INTRLIN315UR0				(274U)	/* RLIN3 INTRLIN315UR0 */
#define		PIL_DTS_GR2_INTRLIN315UR1				(275U)	/* RLIN3 INTRLIN315UR1 */
#define		PIL_DTS_GR2_INTRLIN316UR0				(276U)	/* RLIN3 INTRLIN316UR0 */
#define		PIL_DTS_GR2_INTRLIN316UR1				(277U)	/* RLIN3 INTRLIN316UR1 */
#define		PIL_DTS_GR2_INTRLIN317UR0				(278U)	/* RLIN3 INTRLIN317UR0 */
#define		PIL_DTS_GR2_INTRLIN317UR1				(279U)	/* RLIN3 INTRLIN317UR1 */
#define		PIL_DTS_GR2_INTRLIN318UR0				(280U)	/* RLIN3 INTRLIN318UR0 */
#define		PIL_DTS_GR2_INTRLIN318UR1				(281U)	/* RLIN3 INTRLIN318UR1 */
#define		PIL_DTS_GR2_INTRLIN319UR0				(282U)	/* RLIN3 INTRLIN319UR0 */
#define		PIL_DTS_GR2_INTRLIN319UR1				(283U)	/* RLIN3 INTRLIN319UR1 */
#define		PIL_DTS_GR2_INTRLIN320UR0				(284U)	/* RLIN3 INTRLIN320UR0 */
#define		PIL_DTS_GR2_INTRLIN320UR1				(285U)	/* RLIN3 INTRLIN320UR1 */
#define		PIL_DTS_GR2_INTRLIN321UR0				(286U)	/* RLIN3 INTRLIN321UR0 */
#define		PIL_DTS_GR2_INTRLIN321UR1				(287U)	/* RLIN3 INTRLIN321UR1 */
#define		PIL_DTS_GR2_INTRLIN322UR0				(288U)	/* RLIN3 INTRLIN322UR0 */
#define		PIL_DTS_GR2_INTRLIN322UR1				(289U)	/* RLIN3 INTRLIN322UR1 */

#define		PIL_DTS_GR2_INTRCANCFDREQ0				(314U)	/* RSCANFD INTRCANCFDREQ0 */
#define		PIL_DTS_GR2_INTRCANCFDREQ1				(315U)	/* RSCANFD INTRCANCFDREQ1 */
#define		PIL_DTS_GR2_INTRCANCFDREQ2				(316U)	/* RSCANFD INTRCANCFDREQ2 */
#define		PIL_DTS_GR2_INTRCANCFDREQ3				(317U)	/* RSCANFD INTRCANCFDREQ3 */
#define		PIL_DTS_GR2_INTRCANCFDREQ4				(318U)	/* RSCANFD INTRCANCFDREQ4 */
#define		PIL_DTS_GR2_INTRCANCFDREQ5				(319U)	/* RSCANFD INTRCANCFDREQ5 */
#define		PIL_DTS_GR2_INTRCANCFDREQ6				(320U)	/* RSCANFD INTRCANCFDREQ6 */
#define		PIL_DTS_GR2_INTRCANCFDREQ7				(321U)	/* RSCANFD INTRCANCFDREQ7 */
#define		PIL_DTS_GR2_INTRCANCFDREQ8				(322U)	/* RSCANFD INTRCANCFDREQ8 */
#define		PIL_DTS_GR2_INTRCANCFDREQ9				(323U)	/* RSCANFD INTRCANCFDREQ9 */
#define		PIL_DTS_GR2_INTRCANRFDREQ0				(324U)	/* RSCANFD INTRCANRFDREQ0 */
#define		PIL_DTS_GR2_INTRCANRFDREQ1				(325U)	/* RSCANFD INTRCANRFDREQ1 */
#define		PIL_DTS_GR2_INTRCANRFDREQ2				(326U)	/* RSCANFD INTRCANRFDREQ2 */
#define		PIL_DTS_GR2_INTRCANRFDREQ3				(327U)	/* RSCANFD INTRCANRFDREQ3 */
#define		PIL_DTS_GR2_INTRCANRFDREQ4				(328U)	/* RSCANFD INTRCANRFDREQ4 */
#define		PIL_DTS_GR2_INTRCANRFDREQ5				(329U)	/* RSCANFD INTRCANRFDREQ5 */
#define		PIL_DTS_GR2_INTRCANRFDREQ6				(330U)	/* RSCANFD INTRCANRFDREQ6 */
#define		PIL_DTS_GR2_INTRCANRFDREQ7				(331U)	/* RSCANFD INTRCANRFDREQ7 */
#define		PIL_DTS_GR2_INTRCANRFDREQ8				(332U)	/* RSCANFD INTRCANRFDREQ8 */
#define		PIL_DTS_GR2_INTRCANRFDREQ9				(333U)	/* RSCANFD INTRCANRFDREQ9 */

#define		PIL_DTS_GR2_INTRSENT12RI				(336U)	/* RSENT INTRSENT12RI */
#define		PIL_DTS_GR2_INTRSENT13RI				(337U)	/* RSENT INTRSENT13RI */
#define		PIL_DTS_GR2_INTRSENT14RI				(338U)	/* RSENT INTRSENT14RI */
#define		PIL_DTS_GR2_INTRSENT15RI				(339U)	/* RSENT INTRSENT15RI */
#define		PIL_DTS_GR2_INTRSENT16RI				(340U)	/* RSENT INTRSENT16RI */
#define		PIL_DTS_GR2_INTRSENT17RI				(341U)	/* RSENT INTRSENT17RI */
#define		PIL_DTS_GR2_INTRSENT18RI				(342U)	/* RSENT INTRSENT18RI */
#define		PIL_DTS_GR2_INTRSENT19RI				(343U)	/* RSENT INTRSENT19RI */
#define		PIL_DTS_GR2_INTRSENT20RI				(344U)	/* RSENT INTRSENT20RI */
#define		PIL_DTS_GR2_INTRSENT21RI				(345U)	/* RSENT INTRSENT21RI */
#define		PIL_DTS_GR2_INTRSENT22RI				(346U)	/* RSENT INTRSENT22RI */
#define		PIL_DTS_GR2_INTRSENT23RI				(347U)	/* RSENT INTRSENT23RI */
#define		PIL_DTS_GR2_INTRSENT24RI				(348U)	/* RSENT INTRSENT24RI */
#define		PIL_DTS_GR2_INTRSENT25RI				(349U)	/* RSENT INTRSENT25RI */

#define		PIL_DTS_GR2_INTRLIN30UR0				(354U)	/* RLIN3 INTRLIN30UR0 */
#define		PIL_DTS_GR2_INTRLIN30UR1				(355U)	/* RLIN3 INTRLIN30UR1 */
#define		PIL_DTS_GR2_INTRLIN31UR0				(356U)	/* RLIN3 INTRLIN31UR0 */
#define		PIL_DTS_GR2_INTRLIN31UR1				(357U)	/* RLIN3 INTRLIN31UR1 */
#define		PIL_DTS_GR2_INTRLIN32UR0				(358U)	/* RLIN3 INTRLIN32UR0 */
#define		PIL_DTS_GR2_INTRLIN32UR1				(359U)	/* RLIN3 INTRLIN32UR1 */
#define		PIL_DTS_GR2_INTRLIN33UR0				(360U)	/* RLIN3 INTRLIN33UR0 */
#define		PIL_DTS_GR2_INTRLIN33UR1				(361U)	/* RLIN3 INTRLIN33UR1 */
#define		PIL_DTS_GR2_INTRLIN34UR0				(362U)	/* RLIN3 INTRLIN34UR0 */
#define		PIL_DTS_GR2_INTRLIN34UR1				(363U)	/* RLIN3 INTRLIN34UR1 */
#define		PIL_DTS_GR2_INTRLIN35UR0				(364U)	/* RLIN3 INTRLIN35UR0 */
#define		PIL_DTS_GR2_INTRLIN35UR1				(365U)	/* RLIN3 INTRLIN35UR1 */
#define		PIL_DTS_GR2_INTRLIN323UR0				(366U)	/* RLIN3 INTRLIN323UR0 */
#define		PIL_DTS_GR2_INTRLIN323UR1				(367U)	/* RLIN3 INTRLIN323UR1 */

#define		PIL_DTS_GR2_INTRSENT26RI				(368U)	/* RSENT INTRSENT26RI */
#define		PIL_DTS_GR2_INTRSENT27RI				(369U)	/* RSENT INTRSENT27RI */
#define		PIL_DTS_GR2_INTRSENT28RI				(370U)	/* RSENT INTRSENT28RI */
#define		PIL_DTS_GR2_INTRSENT29RI				(371U)	/* RSENT INTRSENT29RI */
#define		PIL_DTS_GR2_INTRSENT0RI					(372U)	/* RSENT INTRSENT0RI */
#define		PIL_DTS_GR2_INTRSENT1RI					(373U)	/* RSENT INTRSENT1RI */
#define		PIL_DTS_GR2_INTRSENT2RI					(374U)	/* RSENT INTRSENT2RI */
#define		PIL_DTS_GR2_INTRSENT3RI					(375U)	/* RSENT INTRSENT3RI */
#define		PIL_DTS_GR2_INTRSENT4RI					(376U)	/* RSENT INTRSENT4RI */
#define		PIL_DTS_GR2_INTRSENT5RI					(377U)	/* RSENT INTRSENT5RI */
#define		PIL_DTS_GR2_INTRSENT6RI					(378U)	/* RSENT INTRSENT6RI */
#define		PIL_DTS_GR2_INTRSENT7RI					(379U)	/* RSENT INTRSENT7RI */
#define		PIL_DTS_GR2_INTRSENT8RI					(380U)	/* RSENT INTRSENT8RI */
#define		PIL_DTS_GR2_INTRSENT9RI					(381U)	/* RSENT INTRSENT9RI */
#define		PIL_DTS_GR2_INTRSENT10RI				(382U)	/* RSENT INTRSENT10RI */
#define		PIL_DTS_GR2_INTRSENT11RI				(383U)	/* RSENT INTRSENT11RI */

/* DTS transfer request definition group 3(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR3_INTTAUD2I0					(384U)	/* TAUD INTTAUD2I0 */
#define		PIL_DTS_GR3_INTTAUD2I1					(385U)	/* TAUD INTTAUD2I1 */
#define		PIL_DTS_GR3_INTTAUD2I2					(386U)	/* TAUD INTTAUD2I2 */
#define		PIL_DTS_GR3_INTTAUD2I3					(387U)	/* TAUD INTTAUD2I3 */
#define		PIL_DTS_GR3_INTTAUD2I4					(388U)	/* TAUD INTTAUD2I4 */
#define		PIL_DTS_GR3_INTTAUD2I5					(389U)	/* TAUD INTTAUD2I5 */
#define		PIL_DTS_GR3_INTTAUD2I6					(390U)	/* TAUD INTTAUD2I6 */
#define		PIL_DTS_GR3_INTTAUD2I7					(391U)	/* TAUD INTTAUD2I7 */
#define		PIL_DTS_GR3_INTTAUD2I8					(392U)	/* TAUD INTTAUD2I8 */
#define		PIL_DTS_GR3_INTTAUD2I9					(393U)	/* TAUD INTTAUD2I9 */
#define		PIL_DTS_GR3_INTTAUD2I10					(394U)	/* TAUD INTTAUD2I10 */
#define		PIL_DTS_GR3_INTTAUD2I11					(395U)	/* TAUD INTTAUD2I11 */
#define		PIL_DTS_GR3_INTTAUD2I12					(396U)	/* TAUD INTTAUD2I12 */
#define		PIL_DTS_GR3_INTTAUD2I13					(397U)	/* TAUD INTTAUD2I13 */
#define		PIL_DTS_GR3_INTTAUD2I14					(398U)	/* TAUD INTTAUD2I14 */
#define		PIL_DTS_GR3_INTTAUD2I15					(399U)	/* TAUD INTTAUD2I15 */
#define		PIL_DTS_GR3_INTTAUD3I0					(400U)	/* TAUD INTTAUD3I0 */
#define		PIL_DTS_GR3_INTTAUD3I1					(401U)	/* TAUD INTTAUD3I1 */
#define		PIL_DTS_GR3_INTTAUD3I2					(402U)	/* TAUD INTTAUD3I2 */
#define		PIL_DTS_GR3_INTTAUD3I3					(403U)	/* TAUD INTTAUD3I3 */
#define		PIL_DTS_GR3_INTTAUD3I4					(404U)	/* TAUD INTTAUD3I4 */
#define		PIL_DTS_GR3_INTTAUD3I5					(405U)	/* TAUD INTTAUD3I5 */
#define		PIL_DTS_GR3_INTTAUD3I6					(406U)	/* TAUD INTTAUD3I6 */
#define		PIL_DTS_GR3_INTTAUD3I7					(407U)	/* TAUD INTTAUD3I7 */
#define		PIL_DTS_GR3_INTTAUD3I8					(408U)	/* TAUD INTTAUD3I8 */
#define		PIL_DTS_GR3_INTTAUD3I9					(409U)	/* TAUD INTTAUD3I9 */
#define		PIL_DTS_GR3_INTTAUD3I10					(410U)	/* TAUD INTTAUD3I10 */
#define		PIL_DTS_GR3_INTTAUD3I11					(411U)	/* TAUD INTTAUD3I11 */
#define		PIL_DTS_GR3_INTTAUD3I12					(412U)	/* TAUD INTTAUD3I12 */
#define		PIL_DTS_GR3_INTTAUD3I13					(413U)	/* TAUD INTTAUD3I13 */
#define		PIL_DTS_GR3_INTTAUD3I14					(414U)	/* TAUD INTTAUD3I14 */
#define		PIL_DTS_GR3_INTTAUD3I15					(415U)	/* TAUD INTTAUD3I15 */

#define		PIL_DTS_GR3_INTDFE0DOUTCND0				(416U)	/* DFE INTDFE0DOUTCND0 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND1				(417U)	/* DFE INTDFE0DOUTCND1 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND2				(418U)	/* DFE INTDFE0DOUTCND2 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND3				(419U)	/* DFE INTDFE0DOUTCND3 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND4				(420U)	/* DFE INTDFE0DOUTCND4 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND5				(421U)	/* DFE INTDFE0DOUTCND5 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND6				(422U)	/* DFE INTDFE0DOUTCND6 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND7				(423U)	/* DFE INTDFE0DOUTCND7 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND8				(424U)	/* DFE INTDFE0DOUTCND8 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND9				(425U)	/* DFE INTDFE0DOUTCND9 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND10			(426U)	/* DFE INTDFE0DOUTCND10 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND11			(427U)	/* DFE INTDFE0DOUTCND11 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND12			(428U)	/* DFE INTDFE0DOUTCND12 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND13			(429U)	/* DFE INTDFE0DOUTCND13 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND14			(430U)	/* DFE INTDFE0DOUTCND14 */
#define		PIL_DTS_GR3_INTDFE0DOUTCND15			(431U)	/* DFE INTDFE0DOUTCND15 */
#define		PIL_DTS_GR3_INTDFE0CND10				(432U)	/* DFE INTDFE0CND10 */
#define		PIL_DTS_GR3_INTDFE0CND11				(433U)	/* DFE INTDFE0CND11 */
#define		PIL_DTS_GR3_INTDFE0CND12				(434U)	/* DFE INTDFE0CND12 */
#define		PIL_DTS_GR3_INTDFE0CND13				(435U)	/* DFE INTDFE0CND13 */
#define		PIL_DTS_GR3_INTDFE0SUBOUT0				(436U)	/* DFE INTDFE0SUBOUT0 */
#define		PIL_DTS_GR3_INTDFE0SUBOUT1				(437U)	/* DFE INTDFE0SUBOUT1 */
#define		PIL_DTS_GR3_INTDFE0SUBOUT2				(438U)	/* DFE INTDFE0SUBOUT2 */
#define		PIL_DTS_GR3_INTDFE1DOUTCND0				(439U)	/* DFE INTDFE1DOUTCND0 */
#define		PIL_DTS_GR3_INTDFE1DOUTCND1				(440U)	/* DFE INTDFE1DOUTCND1 */
#define		PIL_DTS_GR3_INTDFE1DOUTCND2				(441U)	/* DFE INTDFE1DOUTCND2 */
#define		PIL_DTS_GR3_INTDFE1DOUTCND3				(442U)	/* DFE INTDFE1DOUTCND3 */
#define		PIL_DTS_GR3_INTDFE1SUBOUT0				(443U)	/* DFE INTDFE1SUBOUT0 */
#define		PIL_DTS_GR3_INTDFE1SUBOUT1				(444U)	/* DFE INTDFE1SUBOUT1 */
#define		PIL_DTS_GR3_INTDFE1SUBOUT2				(445U)	/* DFE INTDFE1SUBOUT2 */
#define		PIL_DTS_GR3_INTDFEFIFOOUTA				(446U)	/* DFE INTDFEFIFOOUTA */
#define		PIL_DTS_GR3_INTDFEFIFOOUTB				(447U)	/* DFE INTDFEFIFOOUTB */
#define		PIL_DTS_GR3_INTDFE0FEND0				(448U)	/* DFE INTDFE0FEND0 */
#define		PIL_DTS_GR3_INTTAUD0I0					(449U)	/* TAUD INTTAUD0I0 */
#define		PIL_DTS_GR3_INTTAUD0I1					(450U)	/* TAUD INTTAUD0I1 */
#define		PIL_DTS_GR3_INTTAUD0I2					(451U)	/* TAUD INTTAUD0I2 */
#define		PIL_DTS_GR3_INTTAUD0I3					(452U)	/* TAUD INTTAUD0I3 */
#define		PIL_DTS_GR3_INTTAUD0I4					(453U)	/* TAUD INTTAUD0I4 */
#define		PIL_DTS_GR3_INTTAUD0I5					(454U)	/* TAUD INTTAUD0I5 */
#define		PIL_DTS_GR3_INTTAUD0I6					(455U)	/* TAUD INTTAUD0I6 */
#define		PIL_DTS_GR3_INTTAUD0I7					(456U)	/* TAUD INTTAUD0I7 */
#define		PIL_DTS_GR3_INTTAUD0I8					(457U)	/* TAUD INTTAUD0I8 */
#define		PIL_DTS_GR3_INTTAUD0I9					(458U)	/* TAUD INTTAUD0I9 */
#define		PIL_DTS_GR3_INTTAUD0I10					(459U)	/* TAUD INTTAUD0I10 */
#define		PIL_DTS_GR3_INTTAUD0I11					(460U)	/* TAUD INTTAUD0I11 */
#define		PIL_DTS_GR3_INTTAUD0I12					(461U)	/* TAUD INTTAUD0I12 */
#define		PIL_DTS_GR3_INTTAUD0I13					(462U)	/* TAUD INTTAUD0I13 */
#define		PIL_DTS_GR3_INTTAUD0I14					(463U)	/* TAUD INTTAUD0I14 */
#define		PIL_DTS_GR3_INTTAUD0I15					(464U)	/* TAUD INTTAUD0I15 */
#define		PIL_DTS_GR3_INTTAUD1I0					(465U)	/* TAUD INTTAUD1I0 */
#define		PIL_DTS_GR3_INTTAUD1I1					(466U)	/* TAUD INTTAUD1I1 */
#define		PIL_DTS_GR3_INTTAUD1I2					(467U)	/* TAUD INTTAUD1I2 */
#define		PIL_DTS_GR3_INTTAUD1I3					(468U)	/* TAUD INTTAUD1I3 */
#define		PIL_DTS_GR3_INTTAUD1I4					(469U)	/* TAUD INTTAUD1I4 */
#define		PIL_DTS_GR3_INTTAUD1I5					(470U)	/* TAUD INTTAUD1I5 */
#define		PIL_DTS_GR3_INTTAUD1I6					(471U)	/* TAUD INTTAUD1I6 */
#define		PIL_DTS_GR3_INTTAUD1I7					(472U)	/* TAUD INTTAUD1I7 */
#define		PIL_DTS_GR3_INTTAUD1I8					(473U)	/* TAUD INTTAUD1I8 */
#define		PIL_DTS_GR3_INTTAUD1I9					(474U)	/* TAUD INTTAUD1I9 */
#define		PIL_DTS_GR3_INTTAUD1I10					(475U)	/* TAUD INTTAUD1I10 */
#define		PIL_DTS_GR3_INTTAUD1I11					(476U)	/* TAUD INTTAUD1I11 */
#define		PIL_DTS_GR3_INTTAUD1I12					(477U)	/* TAUD INTTAUD1I12 */
#define		PIL_DTS_GR3_INTTAUD1I13					(478U)	/* TAUD INTTAUD1I13 */
#define		PIL_DTS_GR3_INTTAUD1I14					(479U)	/* TAUD INTTAUD1I14 */
#define		PIL_DTS_GR3_INTTAUD1I15					(480U)	/* TAUD INTTAUD1I15 */

#define		PIL_DTS_GR3_INTDFE0FEND1				(493U)	/* DFE INTDFE0FEND1 */
#define		PIL_DTS_GR3_INTDFE0FEND2				(494U)	/* DFE INTDFE0FEND2 */
#define		PIL_DTS_GR3_INTDFE0FEND3				(495U)	/* DFE INTDFE0FEND3 */
#define		PIL_DTS_GR3_INTDFE0FEND4				(496U)	/* DFE INTDFE0FEND4 */
#define		PIL_DTS_GR3_INTDFE0FEND5				(497U)	/* DFE INTDFE0FEND5 */
#define		PIL_DTS_GR3_INTDFE0FEND6				(498U)	/* DFE INTDFE0FEND6 */
#define		PIL_DTS_GR3_INTDFE0FEND7				(499U)	/* DFE INTDFE0FEND7 */
#define		PIL_DTS_GR3_INTDFE0FEND8				(500U)	/* DFE INTDFE0FEND8 */
#define		PIL_DTS_GR3_INTDFE0FEND9				(501U)	/* DFE INTDFE0FEND9 */
#define		PIL_DTS_GR3_INTDFE0FEND10				(502U)	/* DFE INTDFE0FEND10 */
#define		PIL_DTS_GR3_INTDFE0FEND11				(503U)	/* DFE INTDFE0FEND11 */
#define		PIL_DTS_GR3_INTDFE0FEND12				(504U)	/* DFE INTDFE0FEND12 */
#define		PIL_DTS_GR3_INTDFE0FEND13				(505U)	/* DFE INTDFE0FEND13 */
#define		PIL_DTS_GR3_INTDFE0FEND14				(506U)	/* DFE INTDFE0FEND14 */
#define		PIL_DTS_GR3_INTDFE0FEND15				(507U)	/* DFE INTDFE0FEND15 */
#define		PIL_DTS_GR3_INTDFE1FEND0				(508U)	/* DFE INTDFE1FEND0 */
#define		PIL_DTS_GR3_INTDFE1FEND1				(509U)	/* DFE INTDFE1FEND1 */
#define		PIL_DTS_GR3_INTDFE1FEND2				(510U)	/* DFE INTDFE1FEND2 */
#define		PIL_DTS_GR3_INTDFE1FEND3				(511U)	/* DFE INTDFE1FEND3 */

/* DTS transfer request definition group 4(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR4_IRQ0						(512U)	/* PORT IRQ0 */
#define		PIL_DTS_GR4_IRQ1						(513U)	/* PORT IRQ1 */
#define		PIL_DTS_GR4_IRQ2						(514U)	/* PORT IRQ2 */
#define		PIL_DTS_GR4_IRQ3						(515U)	/* PORT IRQ3 */
#define		PIL_DTS_GR4_IRQ4						(516U)	/* PORT IRQ4 */
#define		PIL_DTS_GR4_IRQ5						(517U)	/* PORT IRQ5 */
#define		PIL_DTS_GR4_IRQ6						(518U)	/* PORT IRQ6 */
#define		PIL_DTS_GR4_IRQ7						(519U)	/* PORT IRQ7 */
#define		PIL_DTS_GR4_IRQ8						(520U)	/* PORT IRQ8 */
#define		PIL_DTS_GR4_IRQ9						(521U)	/* PORT IRQ9 */
#define		PIL_DTS_GR4_IRQ10						(522U)	/* PORT IRQ10 */
#define		PIL_DTS_GR4_IRQ11						(523U)	/* PORT IRQ11 */
#define		PIL_DTS_GR4_IRQ12						(524U)	/* PORT IRQ12 */
#define		PIL_DTS_GR4_IRQ13						(525U)	/* PORT IRQ13 */
#define		PIL_DTS_GR4_IRQ14						(526U)	/* PORT IRQ14 */
#define		PIL_DTS_GR4_IRQ15						(527U)	/* PORT IRQ15 */
#define		PIL_DTS_GR4_IRQ16						(528U)	/* PORT IRQ16 */
#define		PIL_DTS_GR4_IRQ17						(529U)	/* PORT IRQ17 */
#define		PIL_DTS_GR4_IRQ18						(530U)	/* PORT IRQ18 */
#define		PIL_DTS_GR4_IRQ19						(531U)	/* PORT IRQ19 */
#define		PIL_DTS_GR4_IRQ20						(532U)	/* PORT IRQ20 */
#define		PIL_DTS_GR4_IRQ21						(533U)	/* PORT IRQ21 */
#define		PIL_DTS_GR4_IRQ22						(534U)	/* PORT IRQ22 */
#define		PIL_DTS_GR4_IRQ23						(535U)	/* PORT IRQ23 */
#define		PIL_DTS_GR4_IRQ24						(536U)	/* PORT IRQ24 */
#define		PIL_DTS_GR4_IRQ25						(537U)	/* PORT IRQ25 */
#define		PIL_DTS_GR4_IRQ26						(538U)	/* PORT IRQ26 */
#define		PIL_DTS_GR4_IRQ27						(539U)	/* PORT IRQ27 */
#define		PIL_DTS_GR4_IRQ28						(540U)	/* PORT IRQ28 */
#define		PIL_DTS_GR4_IRQ29						(541U)	/* PORT IRQ29 */
#define		PIL_DTS_GR4_IRQ30						(542U)	/* PORT IRQ30 */
#define		PIL_DTS_GR4_IRQ31						(543U)	/* PORT IRQ31 */
#define		PIL_DTS_GR4_IRQ32						(544U)	/* PORT IRQ32 */
#define		PIL_DTS_GR4_IRQ33						(545U)	/* PORT IRQ33 */
#define		PIL_DTS_GR4_IRQ34						(546U)	/* PORT IRQ34 */
#define		PIL_DTS_GR4_IRQ35						(547U)	/* PORT IRQ35 */
#define		PIL_DTS_GR4_IRQ36						(548U)	/* PORT IRQ36 */
#define		PIL_DTS_GR4_IRQ37						(549U)	/* PORT IRQ37 */
#define		PIL_DTS_GR4_IRQ38						(550U)	/* PORT IRQ38 */
#define		PIL_DTS_GR4_IRQ39						(551U)	/* PORT IRQ39 */
#define		PIL_DTS_GR4_IRQ40						(552U)	/* PORT IRQ40 */
#define		PIL_DTS_GR4_IRQ41						(553U)	/* PORT IRQ41 */
#define		PIL_DTS_GR4_IRQ42						(554U)	/* PORT IRQ42 */
#define		PIL_DTS_GR4_IRQ43						(555U)	/* PORT IRQ43 */
#define		PIL_DTS_GR4_INTTAPA0ESO					(556U)	/* PORT INTTAPA0ESO */
#define		PIL_DTS_GR4_INTTAPA1ESO					(557U)	/* PORT INTTAPA1ESO */
#define		PIL_DTS_GR4_INTTAPA2ESO					(558U)	/* PORT INTTAPA2ESO */
#define		PIL_DTS_GR4_INTTAPA3ESO					(559U)	/* PORT INTTAPA3ESO */
#define		PIL_DTS_GR4_INTTAPA4ESO					(560U)	/* PORT INTTAPA4ESO */
#define		PIL_DTS_GR4_INTTAPA5ESO					(561U)	/* PORT INTTAPA5ESO */

#define		PIL_DTS_GR4_INTAIRDMAREQ0				(562U)	/* AIR INTAIRDMAREQ0 */
#define		PIL_DTS_GR4_INTAIRDMAREQ1				(563U)	/* AIR INTAIRDMAREQ1 */
#define		PIL_DTS_GR4_INTAIRDMAREQ2				(564U)	/* AIR INTAIRDMAREQ2 */
#define		PIL_DTS_GR4_INTAIRDMAREQ3				(565U)	/* AIR INTAIRDMAREQ3 */
#define		PIL_DTS_GR4_INTAIRDMAREQ4				(566U)	/* AIR INTAIRDMAREQ4 */
#define		PIL_DTS_GR4_INTAIRDMAREQ5				(567U)	/* AIR INTAIRDMAREQ5 */
#define		PIL_DTS_GR4_INTAIRDMAREQ6				(568U)	/* AIR INTAIRDMAREQ6 */
#define		PIL_DTS_GR4_INTAIRDMAREQ7				(569U)	/* AIR INTAIRDMAREQ7 */
#define		PIL_DTS_GR4_INTAIRDMAREQ8				(570U)	/* AIR INTAIRDMAREQ8 */
#define		PIL_DTS_GR4_INTAIRDMAREQ9				(571U)	/* AIR INTAIRDMAREQ9 */
#define		PIL_DTS_GR4_INTAIRDMAREQ10				(572U)	/* AIR INTAIRDMAREQ10 */
#define		PIL_DTS_GR4_INTAIRDMAREQ11				(573U)	/* AIR INTAIRDMAREQ11 */
#define		PIL_DTS_GR4_INTAIRDMAREQ12				(574U)	/* AIR INTAIRDMAREQ12 */
#define		PIL_DTS_GR4_INTAIRDMAREQ13				(575U)	/* AIR INTAIRDMAREQ13 */
#define		PIL_DTS_GR4_INTAIRDMAREQ14				(576U)	/* AIR INTAIRDMAREQ14 */
#define		PIL_DTS_GR4_INTAIRDMAREQ15				(577U)	/* AIR INTAIRDMAREQ15 */
#define		PIL_DTS_GR4_INTAIRDMAREQ16				(578U)	/* AIR INTAIRDMAREQ16 */
#define		PIL_DTS_GR4_INTAIRDMAREQ17				(579U)	/* AIR INTAIRDMAREQ17 */
#define		PIL_DTS_GR4_INTAIRDMAREQ18				(580U)	/* AIR INTAIRDMAREQ18 */
#define		PIL_DTS_GR4_INTAIRDMAREQ19				(581U)	/* AIR INTAIRDMAREQ19 */
#define		PIL_DTS_GR4_INTAIRDMAREQ20				(582U)	/* AIR INTAIRDMAREQ20 */
#define		PIL_DTS_GR4_INTAIRDMAREQ21				(583U)	/* AIR INTAIRDMAREQ21 */
#define		PIL_DTS_GR4_INTAIRDMAREQ22				(584U)	/* AIR INTAIRDMAREQ22 */
#define		PIL_DTS_GR4_INTAIRDMAREQ23				(585U)	/* AIR INTAIRDMAREQ23 */
#define		PIL_DTS_GR4_INTAIRDMAREQ24				(586U)	/* AIR INTAIRDMAREQ24 */
#define		PIL_DTS_GR4_INTAIRDMAREQ25				(587U)	/* AIR INTAIRDMAREQ25 */
#define		PIL_DTS_GR4_INTAIRDMAREQ26				(588U)	/* AIR INTAIRDMAREQ26 */
#define		PIL_DTS_GR4_INTAIRDMAREQ27				(589U)	/* AIR INTAIRDMAREQ27 */
#define		PIL_DTS_GR4_INTAIRDMAREQ28				(590U)	/* AIR INTAIRDMAREQ28 */
#define		PIL_DTS_GR4_INTAIRDMAREQ29				(591U)	/* AIR INTAIRDMAREQ29 */
#define		PIL_DTS_GR4_INTAIRDMAREQ30				(592U)	/* AIR INTAIRDMAREQ30 */
#define		PIL_DTS_GR4_INTAIRDMAREQ31				(593U)	/* AIR INTAIRDMAREQ31 */
#define		PIL_DTS_GR4_INTAIRDMAREQ32				(594U)	/* AIR INTAIRDMAREQ32 */
#define		PIL_DTS_GR4_INTAIRDMAREQ33				(595U)	/* AIR INTAIRDMAREQ33 */
#define		PIL_DTS_GR4_INTAIRDMAREQ34				(596U)	/* AIR INTAIRDMAREQ34 */
#define		PIL_DTS_GR4_INTAIRDMAREQ35				(597U)	/* AIR INTAIRDMAREQ35 */
#define		PIL_DTS_GR4_INTAIRDMAREQ36				(598U)	/* AIR INTAIRDMAREQ36 */
#define		PIL_DTS_GR4_INTAIRDMAREQ37				(599U)	/* AIR INTAIRDMAREQ37 */
#define		PIL_DTS_GR4_INTAIRDMAREQ38				(600U)	/* AIR INTAIRDMAREQ38 */
#define		PIL_DTS_GR4_INTAIRDMAREQ39				(601U)	/* AIR INTAIRDMAREQ39 */
#define		PIL_DTS_GR4_INTAIRDMAREQ40				(602U)	/* AIR INTAIRDMAREQ40 */
#define		PIL_DTS_GR4_INTAIRDMAREQ41				(603U)	/* AIR INTAIRDMAREQ41 */
#define		PIL_DTS_GR4_INTAIRDMAREQ42				(604U)	/* AIR INTAIRDMAREQ42 */
#define		PIL_DTS_GR4_INTAIRDMAREQ43				(605U)	/* AIR INTAIRDMAREQ43 */
#define		PIL_DTS_GR4_INTAIRDMAREQ44				(606U)	/* AIR INTAIRDMAREQ44 */
#define		PIL_DTS_GR4_INTAIRDMAREQ45				(607U)	/* AIR INTAIRDMAREQ45 */
#define		PIL_DTS_GR4_INTAIRDMAREQ46				(608U)	/* AIR INTAIRDMAREQ46 */
#define		PIL_DTS_GR4_INTAIRDMAREQ47				(609U)	/* AIR INTAIRDMAREQ47 */
#define		PIL_DTS_GR4_INTAIRDMAREQ48				(610U)	/* AIR INTAIRDMAREQ48 */
#define		PIL_DTS_GR4_INTAIRDMAREQ49				(611U)	/* AIR INTAIRDMAREQ49 */
#define		PIL_DTS_GR4_INTAIRDMAREQ50				(612U)	/* AIR INTAIRDMAREQ50 */
#define		PIL_DTS_GR4_INTAIRDMAREQ51				(613U)	/* AIR INTAIRDMAREQ51 */
#define		PIL_DTS_GR4_INTAIRDMAREQ52				(614U)	/* AIR INTAIRDMAREQ52 */
#define		PIL_DTS_GR4_INTAIRDMAREQ53				(615U)	/* AIR INTAIRDMAREQ53 */
#define		PIL_DTS_GR4_INTAIRDMAREQ54				(616U)	/* AIR INTAIRDMAREQ54 */
#define		PIL_DTS_GR4_INTAIRDMAREQ55				(617U)	/* AIR INTAIRDMAREQ55 */
#define		PIL_DTS_GR4_INTAIRDMAREQ56				(618U)	/* AIR INTAIRDMAREQ56 */
#define		PIL_DTS_GR4_INTAIRDMAREQ57				(619U)	/* AIR INTAIRDMAREQ57 */
#define		PIL_DTS_GR4_INTAIRDMAREQ58				(620U)	/* AIR INTAIRDMAREQ58 */
#define		PIL_DTS_GR4_INTAIRDMAREQ59				(621U)	/* AIR INTAIRDMAREQ59 */
#define		PIL_DTS_GR4_INTAIRDMAREQ60				(622U)	/* AIR INTAIRDMAREQ60 */
#define		PIL_DTS_GR4_INTAIRDMAREQ61				(623U)	/* AIR INTAIRDMAREQ61 */
#define		PIL_DTS_GR4_INTAIRDMAREQ62				(624U)	/* AIR INTAIRDMAREQ62 */
#define		PIL_DTS_GR4_INTAIRDMAREQ63				(625U)	/* AIR INTAIRDMAREQ63 */

#define		PIL_DTS_GR4_INTADCKAI0					(626U)	/* ADCK INTADCKAI0 */
#define		PIL_DTS_GR4_INTADCKAI1					(627U)	/* ADCK INTADCKAI1 */
#define		PIL_DTS_GR4_INTADCKAI2					(628U)	/* ADCK INTADCKAI2 */
#define		PIL_DTS_GR4_INTADCKAI3					(629U)	/* ADCK INTADCKAI3 */
#define		PIL_DTS_GR4_INTADCKAI4					(630U)	/* ADCK INTADCKAI4 */
#define		PIL_DTS_GR4_ADMPXIA						(631U)	/* ADCK ADMPXIA */

/* DTS transfer request definition group 5(DTS has the same CH number and hard factor) */
#define		PIL_DTS_GR5_INTATUAICIA0				(640U)	/* ATUVI INTATUAICIA0 */
#define		PIL_DTS_GR5_INTGTM0DOS00				(640U)	/* GTM	 INTGTM0DOS00 */
#define		PIL_DTS_GR5_INTATUAICIA1				(641U)	/* ATUVI INTATUAICIA1 */
#define		PIL_DTS_GR5_INTGTM0DOS01				(641U)	/* GTM	 INTGTM0DOS01 */
#define		PIL_DTS_GR5_INTATUAICIA2				(642U)	/* ATUVI INTATUAICIA2 */
#define		PIL_DTS_GR5_INTGTM0DOS02				(642U)	/* GTM	 INTGTM0DOS02 */
#define		PIL_DTS_GR5_INTATUAICIA3				(643U)	/* ATUVI INTATUAICIA3 */
#define		PIL_DTS_GR5_INTGTM0DOS03				(643U)	/* GTM	 INTGTM0DOS03 */
#define		PIL_DTS_GR5_INTATUAICIA4				(644U)	/* ATUVI INTATUAICIA4 */
#define		PIL_DTS_GR5_INTGTM0DOS04				(644U)	/* GTM	 INTGTM0DOS04 */
#define		PIL_DTS_GR5_INTATUAICIA5				(645U)	/* ATUVI INTATUAICIA5 */
#define		PIL_DTS_GR5_INTGTM0DOS05				(645U)	/* GTM	 INTGTM0DOS05 */
#define		PIL_DTS_GR5_INTATUAICIA6				(646U)	/* ATUVI INTATUAICIA6 */
#define		PIL_DTS_GR5_INTGTM0DOS06				(646U)	/* GTM	 INTGTM0DOS06 */
#define		PIL_DTS_GR5_INTATUAICIA7				(647U)	/* ATUVI INTATUAICIA7 */
#define		PIL_DTS_GR5_INTGTM0DOS07				(647U)	/* GTM	 INTGTM0DOS07 */
#define		PIL_DTS_GR5_INTATUFICIF0				(648U)	/* ATUVI INTATUFICIF0 */
#define		PIL_DTS_GR5_INTGTM0DOS10				(648U)	/* GTM	 INTGTM0DOS10 */
#define		PIL_DTS_GR5_INTATUFICIF1				(649U)	/* ATUVI INTATUFICIF1 */
#define		PIL_DTS_GR5_INTGTM0DOS11				(649U)	/* GTM	 INTGTM0DOS11 */
#define		PIL_DTS_GR5_INTATUFICIF2				(650U)	/* ATUVI INTATUFICIF2 */
#define		PIL_DTS_GR5_INTGTM0DOS12				(650U)	/* GTM	 INTGTM0DOS12 */
#define		PIL_DTS_GR5_INTATUFICIF3				(651U)	/* ATUVI INTATUFICIF3 */
#define		PIL_DTS_GR5_INTGTM0DOS13				(651U)	/* GTM	 INTGTM0DOS13 */
#define		PIL_DTS_GR5_INTATUFICIF4				(652U)	/* ATUVI INTATUFICIF4 */
#define		PIL_DTS_GR5_INTGTM0DOS14				(652U)	/* GTM	 INTGTM0DOS14 */
#define		PIL_DTS_GR5_INTATUFICIF5				(653U)	/* ATUVI INTATUFICIF5 */
#define		PIL_DTS_GR5_INTGTM0DOS15				(653U)	/* GTM	 INTGTM0DOS15 */
#define		PIL_DTS_GR5_INTATUFICIF6				(654U)	/* ATUVI INTATUFICIF6 */
#define		PIL_DTS_GR5_INTGTM0DOS16				(654U)	/* GTM 	 INTGTM0DOS16 */
#define		PIL_DTS_GR5_INTATUFICIF7				(655U)	/* ATUVI INTATUFICIF7 */
#define		PIL_DTS_GR5_INTGTM0DOS17				(655U)	/* GTM 	 INTGTM0DOS17 */
#define		PIL_DTS_GR5_INTATUFICIF8				(656U)	/* ATUVI INTATUFICIF8 */
#define		PIL_DTS_GR5_INTGTM0DOS20				(656U)	/* GTM 	 INTGTM0DOS20 */
#define		PIL_DTS_GR5_INTATUFICIF9				(657U)	/* ATUVI INTATUFICIF9 */
#define		PIL_DTS_GR5_INTGTM0DOS21				(657U)	/* GTM 	 INTGTM0DOS21 */
#define		PIL_DTS_GR5_INTATUFICIF10				(658U)	/* ATUVI INTATUFICIF10 */
#define		PIL_DTS_GR5_INTGTM0DOS22				(658U)	/* GTM 	 INTGTM0DOS22 */
#define		PIL_DTS_GR5_INTATUFICIF11				(659U)	/* ATUVI INTATUFICIF11 */
#define		PIL_DTS_GR5_INTGTM0DOS23				(659U)	/* GTM 	 INTGTM0DOS23 */
#define		PIL_DTS_GR5_INTATUFICIF12				(660U)	/* ATUVI INTATUFICIF12 */
#define		PIL_DTS_GR5_INTGTM0DOS24				(660U)	/* GTM   INTGTM0DOS24 */
#define		PIL_DTS_GR5_INTATUFICIF13				(661U)	/* ATUVI INTATUFICIF13 */
#define		PIL_DTS_GR5_INTGTM0DOS25				(661U)	/* GTM   INTGTM0DOS25 */
#define		PIL_DTS_GR5_INTATUFICIF14				(662U)	/* ATUVI INTATUFICIF14 */
#define		PIL_DTS_GR5_INTGTM0DOS26				(662U)	/* GTM   INTGTM0DOS26 */
#define		PIL_DTS_GR5_INTATUFICIF15				(663U)	/* ATUVI INTATUFICIF15 */
#define		PIL_DTS_GR5_INTGTM0DOS27				(663U)	/* GTM   INTGTM0DOS27 */
#define		PIL_DTS_GR5_INTATUFICIF16				(664U)	/* ATUVI INTATUFICIF16 */
#define		PIL_DTS_GR5_INTGTM0DOS30				(664U)	/* GTM   INTGTM0DOS30 */
#define		PIL_DTS_GR5_INTATUFICIF17				(665U)	/* ATUVI INTATUFICIF17 */
#define		PIL_DTS_GR5_INTGTM0DOS31				(665U)	/* GTM   INTGTM0DOS31 */
#define		PIL_DTS_GR5_INTATUFICIF18				(666U)	/* ATUVI INTATUFICIF18 */
#define		PIL_DTS_GR5_INTGTM0DOS32				(666U)	/* GTM   INTGTM0DOS32 */
#define		PIL_DTS_GR5_INTATUFICIF19				(667U)	/* ATUVI INTATUFICIF19 */
#define		PIL_DTS_GR5_INTGTM0DOS33				(667U)	/* GTM   INTGTM0DOS33 */
#define		PIL_DTS_GR5_INTATUGCMIG0				(668U)	/* ATUVI INTATUGCMIG0 */
#define		PIL_DTS_GR5_INTGTM0DOS34				(668U)	/* GTM   INTGTM0DOS34 */
#define		PIL_DTS_GR5_INTATUGCMIG1				(669U)	/* ATUVI INTATUGCMIG1*/
#define		PIL_DTS_GR5_INTGTM0DOS35				(669U)	/* GTM   INTGTM0DOS35 */
#define		PIL_DTS_GR5_INTATUGCMIG2				(670U)	/* ATUVI INTATUGCMIG2 */
#define		PIL_DTS_GR5_INTGTM0DOS36				(670U)	/* GTM   INTGTM0DOS36 */
#define		PIL_DTS_GR5_INTATUGCMIG3				(671U)	/* ATUVI INTATUGCMIG3 */
#define		PIL_DTS_GR5_INTGTM0DOS37				(671U)	/* GTM   INTGTM0DOS37 */
#define		PIL_DTS_GR5_INTATUGCMIG4				(672U)	/* ATUVI INTATUGCMIG4 */
#define		PIL_DTS_GR5_INTGTM0DOS40				(672U)	/* GTM   INTGTM0DOS40 */
#define		PIL_DTS_GR5_INTATUGCMIG5				(673U)	/* ATUVI INTATUGCMIG5 */
#define		PIL_DTS_GR5_INTGTM0DOS41				(673U)	/* GTM   INTGTM0DOS41 */
#define		PIL_DTS_GR5_INTATUGCMIG6				(674U)	/* ATUVI INTATUGCMIG6 */
#define		PIL_DTS_GR5_INTGTM0DOS42				(674U)	/* GTM   INTGTM0DOS42 */
#define		PIL_DTS_GR5_INTATUGCMIG7				(675U)	/* ATUVI INTATUGCMIG7 */
#define		PIL_DTS_GR5_INTGTM0DOS43				(675U)	/* GTM   INTGTM0DOS43 */
#define		PIL_DTS_GR5_INTATUGCMIG8				(676U)	/* ATUVI INTATUGCMIG8 */
#define		PIL_DTS_GR5_INTGTM0DOS44				(676U)	/* GTM   INTGTM0DOS44 */
#define		PIL_DTS_GR5_INTATUGCMIG9				(677U)	/* ATUVI INTATUGCMIG9 */
#define		PIL_DTS_GR5_INTGTM0DOS45				(677U)	/* GTM   INTGTM0DOS45 */
#define		PIL_DTS_GR5_INTATUGCMIG10				(678U)	/* ATUVI INTATUGCMIG10 */
#define		PIL_DTS_GR5_INTGTM0DOS46				(678U)	/* GTM   INTGTM0DOS46 */
#define		PIL_DTS_GR5_INTATUGCMIG11				(679U)	/* ATUVI INTATUGCMIG11 */
#define		PIL_DTS_GR5_INTGTM0DOS47				(679U)	/* GTM   INTGTM0DOS47 */
#define		PIL_DTS_GR5_INTATUGCMIG12				(680U)	/* ATUVI INTATUGCMIG12 */
#define		PIL_DTS_GR5_INTGTM0DOS50				(680U)	/* GTM   INTGTM0DOS50 */
#define		PIL_DTS_GR5_INTATUGCMIG13				(681U)	/* ATUVI INTATUGCMIG13 */
#define		PIL_DTS_GR5_INTGTM0DOS51				(681U)	/* GTM   INTGTM0DOS51 */
#define		PIL_DTS_GR5_INTATUBSLDB0				(682U)	/* ATUVI INTATUBSLDB0 */
#define		PIL_DTS_GR5_INTGTM0DOS52				(682U)	/* GTM   INTGTM0DOS52 */
#define		PIL_DTS_GR5_INTATUBSLDB1				(683U)	/* ATUVI INTATUBSLDB1 */
#define		PIL_DTS_GR5_INTGTM0DOS53				(683U)	/* GTM   INTGTM0DOS53 */
#define		PIL_DTS_GR5_INTATUBSLDB2				(684U)	/* ATUVI INTATUBSLDB2 */
#define		PIL_DTS_GR5_INTGTM0DOS54				(684U)	/* GTM   INTGTM0DOS54 */
#define		PIL_DTS_GR5_INTATUBSLDB3				(685U)	/* ATUVI INTATUBSLDB3 */
#define		PIL_DTS_GR5_INTGTM0DOS55				(685U)	/* GTM   INTGTM0DOS55 */
#define		PIL_DTS_GR5_INTATUBSLDB4				(686U)	/* ATUVI INTATUBSLDB4 */
#define		PIL_DTS_GR5_INTGTM0DOS56				(686U)	/* GTM   INTGTM0DOS56 */
#define		PIL_DTS_GR5_INTATUBSLDB5				(687U)	/* ATUVI INTATUBSLDB5 */
#define		PIL_DTS_GR5_INTGTM0DOS57				(687U)	/* GTM   INTGTM0DOS57 */
#define		PIL_DTS_GR5_INTATUBSLDB6				(688U)	/* ATUVI INTATUBSLDB6 */
#define		PIL_DTS_GR5_INTGTM0DOS60				(688U)	/* GTM   INTGTM0DOS60 */
#define		PIL_DTS_GR5_INTATUBSLDB7				(689U)	/* ATUVI INTATUBSLDB7 */
#define		PIL_DTS_GR5_INTGTM0DOS61				(689U)	/* GTM   INTGTM0DOS61 */
#define		PIL_DTS_GR5_INTATUCDSLDCD0				(690U)	/* ATUVI INTATUCDSLDCD0 */
#define		PIL_DTS_GR5_INTGTM0DOS62				(690U)	/* GTM   INTGTM0DOS62 */
#define		PIL_DTS_GR5_INTATUCDSLDCD1				(691U)	/* ATUVI INTATUCDSLDCD1 */
#define		PIL_DTS_GR5_INTGTM0DOS63				(691U)	/* GTM   INTGTM0DOS63 */
#define		PIL_DTS_GR5_INTATUCDSLDCD2				(692U)	/* ATUVI INTATUCDSLDCD2 */
#define		PIL_DTS_GR5_INTGTM0DOS64				(692U)	/* GTM   INTGTM0DOS64 */
#define		PIL_DTS_GR5_INTATUCDSLDCD3				(693U)	/* ATUVI INTATUCDSLDCD3 */
#define		PIL_DTS_GR5_INTGTM0DOS65				(693U)	/* GTM   INTGTM0DOS65 */
#define		PIL_DTS_GR5_INTATUCDSLDCD4				(694U)	/* ATUVI INTATUCDSLDCD4 */
#define		PIL_DTS_GR5_INTGTM0DOS66				(694U)	/* GTM   INTGTM0DOS66 */
#define		PIL_DTS_GR5_INTATUCDSLDCD5				(695U)	/* ATUVI INTATUCDSLDCD5 */
#define		PIL_DTS_GR5_INTGTM0DOS67				(695U)	/* GTM   INTGTM0DOS67 */
#define		PIL_DTS_GR5_INTATUCDSLDCD6				(696U)	/* ATUVI INTATUCDSLDCD6 */
#define		PIL_DTS_GR5_INTGTM0DOS70				(696U)	/* GTM   INTGTM0DOS70 */
#define		PIL_DTS_GR5_INTATUCDSLDCD7				(697U)	/* ATUVI INTATUCDSLDCD7 */
#define		PIL_DTS_GR5_INTGTM0DOS71				(697U)	/* GTM   INTGTM0DOS71 */
#define		PIL_DTS_GR5_INTATUCDSLDCD8				(698U)	/* ATUVI INTATUCDSLDCD8 */
#define		PIL_DTS_GR5_INTGTM0DOS72				(698U)	/* GTM   INTGTM0DOS72 */
#define		PIL_DTS_GR5_INTATUCDSLDCD9				(699U)	/* ATUVI INTATUCDSLDCD9 */
#define		PIL_DTS_GR5_INTGTM0DOS73				(699U)	/* GTM   INTGTM0DOS73 */
#define		PIL_DTS_GR5_INTATUCDSLDCD10				(700U)	/* ATUVI INTATUCDSLDCD10 */
#define		PIL_DTS_GR5_INTGTM0DOS74				(700U)	/* GTM   INTGTM0DOS74 */
#define		PIL_DTS_GR5_INTATUCDSLDCD11				(701U)	/* ATUVI INTATUCDSLDCD11 */
#define		PIL_DTS_GR5_INTGTM0DOS75				(701U)	/* GTM   INTGTM0DOS75 */
#define		PIL_DTS_GR5_INTATUCDSLDCD12				(702U)	/* ATUVI INTATUCDSLDCD12 */
#define		PIL_DTS_GR5_INTGTM0DOS76				(702U)	/* GTM   INTGTM0DOS76 */
#define		PIL_DTS_GR5_INTATUCDSLDCD13				(703U)	/* ATUVI INTATUCDSLDCD13 */
#define		PIL_DTS_GR5_INTGTM0DOS77				(703U)	/* GTM   INTGTM0DOS77 */
#define		PIL_DTS_GR5_INTATUCDSLDCD14				(704U)	/* ATUVI INTATUCDSLDCD14 */
#define		PIL_DTS_GR5_INTGTM0DOS80				(704U)	/* GTM   INTGTM0DOS80 */
#define		PIL_DTS_GR5_INTATUCDSLDCD15				(705U)	/* ATUVI INTATUCDSLDCD15 */
#define		PIL_DTS_GR5_INTGTM0DOS81				(705U)	/* GTM   INTGTM0DOS81 */
#define		PIL_DTS_GR5_INTATUCDSLDCD16				(706U)	/* ATUVI INTATUCDSLDCD16 */
#define		PIL_DTS_GR5_INTGTM0DOS82				(706U)	/* GTM   INTGTM0DOS82 */
#define		PIL_DTS_GR5_INTATUCDSLDCD17				(707U)	/* ATUVI INTATUCDSLDCD17 */
#define		PIL_DTS_GR5_INTGTM0DOS83				(707U)	/* GTM   INTGTM0DOS83 */
#define		PIL_DTS_GR5_INTATUCDSLDCD18				(708U)	/* ATUVI INTATUCDSLDCD18 */
#define		PIL_DTS_GR5_INTGTM0DOS84				(708U)	/* GTM   INTGTM0DOS84 */
#define		PIL_DTS_GR5_INTATUCDSLDCD19				(709U)	/* ATUVI INTATUCDSLDCD19 */
#define		PIL_DTS_GR5_INTGTM0DOS85				(709U)	/* GTM   INTGTM0DOS85 */
#define		PIL_DTS_GR5_INTATUCDSLDCD20				(710U)	/* ATUVI INTATUCDSLDCD20 */
#define		PIL_DTS_GR5_INTGTM0DOS86				(710U)	/* GTM   INTGTM0DOS86 */
#define		PIL_DTS_GR5_INTATUCDSLDCD21				(711U)	/* ATUVI INTATUCDSLDCD21 */
#define		PIL_DTS_GR5_INTGTM0DOS87				(711U)	/* GTM   INTGTM0DOS87 */
#define		PIL_DTS_GR5_INTATUCDSLDCD22				(712U)	/* ATUVI INTATUCDSLDCD22 */
#define		PIL_DTS_GR5_INTGTM0DOSO0				(712U)	/* GTM   INTGTM0DOSO0 */
#define		PIL_DTS_GR5_INTATUCDSLDCD23				(713U)	/* ATUVI INTATUCDSLDCD23 */
#define		PIL_DTS_GR5_INTGTM0DOSO1				(713U)	/* GTM   INTGTM0DOSO1 */
#define		PIL_DTS_GR5_INTATUCDSLDCD24				(714U)	/* ATUVI INTATUCDSLDCD24 */
#define		PIL_DTS_GR5_INTGTM0DOSO2				(714U)	/* GTM   INTGTM0DOSO2 */
#define		PIL_DTS_GR5_INTATUCDSLDCD25				(715U)	/* ATUVI INTATUCDSLDCD25 */
#define		PIL_DTS_GR5_INTGTM0DOSO3				(715U)	/* GTM   INTGTM0DOSO3 */
#define		PIL_DTS_GR5_INTATUCDSLDCD26				(716U)	/* ATUVI INTATUCDSLDCD26 */
#define		PIL_DTS_GR5_INTGTM0DOSO4				(716U)	/* GTM   INTGTM0DOSO4 */
#define		PIL_DTS_GR5_INTATUCDSLDCD27				(717U)	/* ATUVI INTATUCDSLDCD27 */
#define		PIL_DTS_GR5_INTGTM0DOSO5				(717U)	/* GTM   INTGTM0DOSO5 */
#define		PIL_DTS_GR5_INTATUCDSLDCD28				(718U)	/* ATUVI INTATUCDSLDCD28 */
#define		PIL_DTS_GR5_INTGTM0DOSO6				(718U)	/* GTM   INTGTM0DOSO6 */
#define		PIL_DTS_GR5_INTATUCDSLDCD29				(719U)	/* ATUVI INTATUCDSLDCD29 */
#define		PIL_DTS_GR5_INTGTM0DOSO7				(719U)	/* GTM   INTGTM0DOSO7 */
#define		PIL_DTS_GR5_INTATUCDSLDCD30				(720U)	/* ATUVI INTATUCDSLDCD30 */
#define		PIL_DTS_GR5_INTGTM0DOSO8				(720U)	/* GTM   INTGTM0DOSO8 */
#define		PIL_DTS_GR5_INTATUCDSLDCD31				(721U)	/* ATUVI INTATUCDSLDCD31 */
#define		PIL_DTS_GR5_INTGTM0DOSO9				(721U)	/* GTM   INTGTM0DOSO9 */
#define		PIL_DTS_GR5_INTATUCDSLDCD32				(722U)	/* ATUVI INTATUCDSLDCD32 */
#define		PIL_DTS_GR5_INTGTM0DOS90				(722U)	/* GTM   INTGTM0DOS90 */
#define		PIL_DTS_GR5_INTATUCDSLDCD33				(723U)	/* ATUVI INTATUCDSLDCD33 */
#define		PIL_DTS_GR5_INTGTM0DOS91				(723U)	/* GTM   INTGTM0DOS91 */
#define		PIL_DTS_GR5_INTATUCDSLDCD34				(724U)	/* ATUVI INTATUCDSLDCD34 */
#define		PIL_DTS_GR5_INTGTM0DOS92				(724U)	/* GTM   INTGTM0DOS92 */
#define		PIL_DTS_GR5_INTATUCDSLDCD35				(725U)	/* ATUVI INTATUCDSLDCD35 */
#define		PIL_DTS_GR5_INTGTM0DOS93				(725U)	/* GTM   INTGTM0DOS93 */
#define		PIL_DTS_GR5_INTATUCDSLDCD36				(726U)	/* ATUVI INTATUCDSLDCD36 */
#define		PIL_DTS_GR5_INTGTM0DOS94				(726U)	/* GTM   INTGTM0DOS94 */
#define		PIL_DTS_GR5_INTATUCDSLDCD37				(727U)	/* ATUVI INTATUCDSLDCD37 */
#define		PIL_DTS_GR5_INTGTM0DOS95				(727U)	/* GTM   INTGTM0DOS95 */
#define		PIL_DTS_GR5_INTATUCDSLDCD38				(728U)	/* ATUVI INTATUCDSLDCD38 */
#define		PIL_DTS_GR5_INTGTM0DOS96				(728U)	/* GTM   INTGTM0DOS96 */
#define		PIL_DTS_GR5_INTATUCDSLDCD39				(729U)	/* ATUVI INTATUCDSLDCD39 */
#define		PIL_DTS_GR5_INTGTM0DOS97				(729U)	/* GTM   INTGTM0DOS97 */
#define		PIL_DTS_GR5_INTATUCDSLDCD40				(730U)	/* ATUVI INTATUCDSLDCD40 */
#define		PIL_DTS_GR5_INTATUCDSLDCD41				(731U)	/* ATUVI INTATUCDSLDCD41 */
#define		PIL_DTS_GR5_INTATUCDSLDCD42				(732U)	/* ATUVI INTATUCDSLDCD42 */
#define		PIL_DTS_GR5_INTATUCDSLDCD43				(733U)	/* ATUVI INTATUCDSLDCD43 */
#define		PIL_DTS_GR5_INTATUCDSLDCD44				(734U)	/* ATUVI INTATUCDSLDCD44 */
#define		PIL_DTS_GR5_INTATUCDSLDCD45				(735U)	/* ATUVI INTATUCDSLDCD45 */
#define		PIL_DTS_GR5_INTATUCDSLDCD46				(736U)	/* ATUVI INTATUCDSLDCD46 */
#define		PIL_DTS_GR5_INTATUCDSLDCD47				(737U)	/* ATUVI INTATUCDSLDCD47 */
#define		PIL_DTS_GR5_INTATUCDSLDCD48				(738U)	/* ATUVI INTATUCDSLDCD48 */
#define		PIL_DTS_GR5_INTATUCDSLDCD49				(739U)	/* ATUVI INTATUCDSLDCD49 */
#define		PIL_DTS_GR5_INTATUCDSLDCD50				(740U)	/* ATUVI INTATUCDSLDCD50 */
#define		PIL_DTS_GR5_INTATUCDSLDCD51				(741U)	/* ATUVI INTATUCDSLDCD51 */
#define		PIL_DTS_GR5_INTATUCDSLDCD52				(742U)	/* ATUVI INTATUCDSLDCD52 */
#define		PIL_DTS_GR5_INTATUCDSLDCD53				(743U)	/* ATUVI INTATUCDSLDCD53 */
#define		PIL_DTS_GR5_INTATUCDSLDCD54				(744U)	/* ATUVI INTATUCDSLDCD54 */
#define		PIL_DTS_GR5_INTATUCDSLDCD55				(745U)	/* ATUVI INTATUCDSLDCD55 */
#define		PIL_DTS_GR5_INTATUCDSLDCD56				(746U)	/* ATUVI INTATUCDSLDCD56 */
#define		PIL_DTS_GR5_INTATUCDSLDCD57				(747U)	/* ATUVI INTATUCDSLDCD57 */
#define		PIL_DTS_GR5_INTATUCDSLDCD58				(748U)	/* ATUVI INTATUCDSLDCD58 */
#define		PIL_DTS_GR5_INTATUCDSLDCD59				(749U)	/* ATUVI INTATUCDSLDCD59 */
#define		PIL_DTS_GR5_INTATUCDSLDCD60				(750U)	/* ATUVI INTATUCDSLDCD60 */
#define		PIL_DTS_GR5_INTATUCDSLDCD61				(751U)	/* ATUVI INTATUCDSLDCD61 */
#define		PIL_DTS_GR5_INTATUCDSLDCD62				(752U)	/* ATUVI INTATUCDSLDCD62 */
#define		PIL_DTS_GR5_INTATUCDSLDCD63				(753U)	/* ATUVI INTATUCDSLDCD63 */
#define		PIL_DTS_GR5_INTATUESLDE0				(754U)	/* ATUVI INTATUESLDE0 */
#define		PIL_DTS_GR5_INTATUESLDE1				(755U)	/* ATUVI INTATUESLDE1 */
#define		PIL_DTS_GR5_INTATUESLDE2				(756U)	/* ATUVI INTATUESLDE2 */
#define		PIL_DTS_GR5_INTATUESLDE3				(757U)	/* ATUVI INTATUESLDE3 */
#define		PIL_DTS_GR5_INTATUESLDE4				(758U)	/* ATUVI INTATUESLDE4 */
#define		PIL_DTS_GR5_INTATUESLDE5				(759U)	/* ATUVI INTATUESLDE5 */
#define		PIL_DTS_GR5_INTATUESLDE6				(760U)	/* ATUVI INTATUESLDE6 */
#define		PIL_DTS_GR5_INTATUESLDE7				(761U)	/* ATUVI INTATUESLDE7 */
#define		PIL_DTS_GR5_INTATUESLDE8				(762U)	/* ATUVI INTATUESLDE8 */
#define		PIL_DTS_GR5_INTATUESLDE9				(763U)	/* ATUVI INTATUESLDE9 */
#define		PIL_DTS_GR5_INTATUCTRLDMAREQ00			(764U)	/* ATUVI INTATUCTRLDMAREQ00 */
#define		PIL_DTS_GR5_INTATUCTRLDMAREQ01			(765U)	/* ATUVI INTATUCTRLDMAREQ01 */
#define		PIL_DTS_GR5_INTATUCTRLDMAREQ10			(766U)	/* ATUVI INTATUCTRLDMAREQ10 */
#define		PIL_DTS_GR5_INTATUCTRLDMAREQ11			(767U)	/* ATUVI INTATUCTRLDMAREQ11 */

#endif /* MCAL_SPAL_TARGET */



/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*	API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/*	Service name	:	EnableTrans																*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_EnableTrans( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	DisableTrans															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_DisableTrans( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	SetTransMode															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*					:	TransSize - Size (SIZE_1/SIZE_2/SIZE_4)									*/
/*					:	DmaMode - DMA Mode (0-5)												*/
/*					:	SrcAdr(Async) - Pointer to Source Adrress								*/
/*					:	DestAdr(Async) - Pointer to Destination Adrress							*/
/*					:	TransNum - Trans number													*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_SetTransMode( U1 t_u1ChannelID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum );

/************************************************************************************************/
/*	Service name	:	SetTransModeTwoStepReload												*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*					:	TransSize - Size (SIZE_1/SIZE_2/SIZE_4)									*/
/*					:	DmaMode - DMA Mode (0-5)												*/
/*					:	SrcAdr(Async) - Pointer to Source Adrress								*/
/*					:	DestAdr(Async) - Pointer to Destination Adrress							*/
/*					:	TransNum - Trans number													*/
/*					:	AddrReloadCnt - Address reload count									*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_SetTransModeTwoStepReload( U1 t_u1ChannelID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2AddrReloadCnt );

/************************************************************************************************/
/*	Function		:	SetInterrupt															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*					:	HalfIe - Half End Interrupt E/D (OFF:DISABLE/ON:ENABLE)					*/
/*					:	EndIe - Trans End Interrupt E/D (OFF:DISABLE/ON:ENABLE)					*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_SetInterrupt( U1 t_u1ChannelID, U1 t_u1HalfIe, U1 t_u1EndIe );

/************************************************************************************************/
/*	Function		:	EnableIntcInterrupt														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	none																	*/
/*	caveat			:	Prohibited for use other than during Init								*/
/************************************************************************************************/
void	Pil_Dts_EnableIntcInterrupt( void );

/************************************************************************************************/
/*	Function		:	DisableIntcInterrupt													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	none																	*/
/*	caveat			:	Use is prohibited except during DeInit.									*/
/************************************************************************************************/
void	Pil_Dts_DisableIntcInterrupt( void );

/************************************************************************************************/
/*	Service name	:	IsTransferCompleted														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	Trans Completed Status (TRUE / FALSE)									*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U1		Pil_Dts_IsTransferCompleted( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	ClearMatchStatus														*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	Use is prohibited except during DeInit.									*/
/************************************************************************************************/
void	Pil_Dts_ClearMatchStatus( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	GetDestinationAddress													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	Destination Address - pointer to destination							*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void*	Pil_Dts_GetDestinationAddress( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	GetTransCount															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	Trans Count																*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U2		Pil_Dts_GetTransCount( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	ResetTransCount															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_ResetTransCount( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	GetTransStatus															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	Trans Status															*/
/*							( DMA_TRANS_STATUS_IDLE(=0) / DMA_TRANS_STATUS_BUSY(=1) )			*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U1		Pil_Dts_GetTransStatus( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	CheckDmaError															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	Error Status(With error(!=0) / No error(==0))							*/
/*	caveat			:	---																		*/
/************************************************************************************************/
ZORN	Pil_Dts_CheckDmaError( void );

/************************************************************************************************/
/*	Service name	:	ClearDmaError															*/
/*	Reentrancy		:	Concurrency Safe for different channel numbers							*/
/*					:	Non Re-entrant for the same channel numbers								*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_ClearDmaError( U1 t_u1ChannelID );

/************************************************************************************************/
/*	Service name	:	SetTransReqGroup														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	Request group number (0-767)											*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_SetTransReqGroup( U2 t_u2RequestGroup );

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/************************************************************************************************/
/*	Service name	:	CheckTransReqGroup														*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	Request group number (0-767)											*/
/*	Return value	:	Register error Status													*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U4	Pil_Dts_CheckTransReqGroup( U2 t_u2RequestGroup );

/************************************************************************************************/
/*	Service name	:	Check DTS INTC Register for interrupt enabling							*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	None																	*/
/*	Return value	:	Register error Status													*/
/*	caveat			:	---																		*/
/************************************************************************************************/
U4	Pil_Dts_CheckIntcReg( void );
#endif

/************************************************************************************************/
/*	Service name	:	ClearRam																*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*	Return value	:	none																	*/
/*	caveat			:	Processing is commented out in the hope that DTSRAM will be  			*/
/*					:	 initialized with a flash option byte.									*/
/************************************************************************************************/
/* void	Pil_Dts_ClearRam( U1 t_u1ChannelID )";" */

/************************************************************************************************/
/*	Service name	:	SetMasterCh																*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	none																	*/
/*	caveat			:	DTS SPID configuration only												*/
/*						 (Use only when using functional safety functions.)						*/
/*					:	Perform this function before turning on the DTS guard function			*/
/*						 of functional safety.													*/
/************************************************************************************************/
void	Pil_Dts_SetMasterCh( void );

/************************************************************************************************/
/*	Service name	:	SetPriority																*/
/*	Reentrancy		:	Non Re-entrant															*/
/*	Parameters (in)	:	ChannelID - DTS Channel													*/
/*					:	PriLevel - Priority Level												*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_SetPriority( U1 t_u1ChannelID, U1 t_u1PriLevel );

/************************************************************************************************/
/*	Service name	:	SetInitPriorityAllCh													*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	none																	*/
/*	caveat			:	The priority of the used CH is set with Pil_Dts_SetPriority ().			*/
/*					:	Processing is commented out because of the policy not to set unused CH.	*/
/************************************************************************************************/
/* void	Pil_Dts_SetInitPriorityAllCh( void )";" */

/************************************************************************************************/
/*	Service name	:	DisableTransAll															*/
/*	Reentrancy		:	Concurrency Safe														*/
/*	Parameters (in)	:	none																	*/
/*	Return value	:	none																	*/
/*	caveat			:	---																		*/
/************************************************************************************************/
void	Pil_Dts_DisableTransAll( void );

#endif /* PIL_DTS_H */
/*-- End Of File -------------------------------------------------------*/
