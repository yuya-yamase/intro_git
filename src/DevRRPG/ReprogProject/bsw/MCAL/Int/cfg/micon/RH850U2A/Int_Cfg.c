/* Int_Cfg_c */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RH850/U2Ax/Int/Cfg/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Int.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define INT_DEVCFG_RESERVED_IRQ_TYPE    (INT_RESERVED_IRQ_TYPE_U2A16_516)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#pragma ghs section rosdata = ".C_INT"

/* INT IRQ Setting Configuration Table */
static const Int_IrqSettingConfigType INT_CFG_IRQSETTING_DATA[] =
{
    {
        INT_IRQ_TAUJ0I0,
        1U
    },
    {
        INT_IRQ_TAUJ0I1,
        11U
    },
    {
        INT_IRQ_RCAN5REC,
        10U
    },
    {
        INT_IRQ_RCAN5TRX,
        10U
    }
};

/* INT IRQ Configuration Table */
static const Int_IrqConfigType INT_CFG_IRQ_DATA =
{
    4U,
    &INT_CFG_IRQSETTING_DATA[0]
};

/* Mask Pattern Table */
/*--------------------------------------------*/
/*  Mask Level 16 All Mask                    */
/*  Mask Level 15                             */
/*  Mask Level 14                             */
/*  Mask Level 13                             */
/*  Mask Level 12                             */
/*  Mask Level 11                             */
/*  Mask Level 10                             */
/*  Mask Level 9                              */
/*  Mask Level 8                              */
/*  Mask Level 7                              */
/*  Mask Level 6                              */
/*  Mask Level 5                              */
/*  Mask Level 4                              */
/*  Mask Level 3                              */
/*  Mask Level 2                              */
/*  Mask Level 1                              */
/*  Mask Level 0 Non Mask                     */
/*--------------------------------------------*/
static const U1 INT_CFG_MASKPATTERN_DATA[INT_MASKPATTERN_NUM] =
{
    16U,
    12U,
    4U,
    0U
};

/* INT Configuration Table */
const Int_ConfigType INT_CFG_DATA =
{
    &INT_CFG_IRQ_DATA,
    &INT_CFG_MASKPATTERN_DATA[0]
};

#if     (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A8_292)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A8 292pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A8_292[INT_RESERVED_IRQ_NUM_U2A8_292] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U, 224U,
    280U, 281U, 282U, 283U, 284U, 285U, 286U, 287U, 288U, 289U, 290U, 291U, 292U, 293U, 294U, 295U,
    464U, 465U, 466U, 467U, 468U, 469U, 470U, 471U, 472U, 473U, 474U, 475U, 476U, 477U, 478U, 479U,
    480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U, 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U,
    496U, 497U, 498U, 499U, 500U, 501U, 502U, 503U, 504U, 505U, 506U, 507U, 508U, 509U, 510U, 511U,
    582U, 583U, 695U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 717U, 718U, 719U, 720U, 721U,
    722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U, 734U, 735U, 736U, 737U,
    738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U, 750U, 751U, 752U, 753U,
    754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A8_292 =
{
    &INT_RESERVED_IRQ_LIST_U2A8_292[0],
    INT_RESERVED_IRQ_NUM_U2A8_292
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A8_373)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A8 373pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A8_373[INT_RESERVED_IRQ_NUM_U2A8_373] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U, 224U,
    292U, 293U, 294U, 295U, 695U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 717U, 718U, 719U,
    720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U, 734U, 735U,
    736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U, 750U, 751U,
    752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A8_373 =
{
    &INT_RESERVED_IRQ_LIST_U2A8_373[0],
    INT_RESERVED_IRQ_NUM_U2A8_373
};

#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_292)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A16 292pin]         */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A16_292[INT_RESERVED_IRQ_NUM_U2A16_292] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 280U, 281U, 282U, 283U, 284U, 285U, 286U, 287U, 288U, 289U,
    290U, 291U, 292U, 293U, 294U, 295U, 464U, 465U, 466U, 467U, 468U, 469U, 470U, 471U, 472U, 473U,
    474U, 475U, 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U, 488U, 489U,
    490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 498U, 499U, 500U, 501U, 502U, 503U, 504U, 505U,
    506U, 507U, 508U, 509U, 510U, 511U, 582U, 583U, 695U, 707U, 708U, 709U, 710U, 711U, 712U, 713U,
    714U, 717U, 718U, 719U, 720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U,
    732U, 733U, 734U, 735U, 736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U,
    748U, 749U, 750U, 751U, 752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U,
    764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A16_292 =
{
    &INT_RESERVED_IRQ_LIST_U2A16_292[0],
    INT_RESERVED_IRQ_NUM_U2A16_292
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_373)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A16 373pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A16_373[INT_RESERVED_IRQ_NUM_U2A16_373] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 292U, 293U, 294U, 295U, 695U, 707U, 708U, 709U, 710U, 711U,
    712U, 713U, 714U, 717U, 718U, 719U, 720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U,
    730U, 731U, 732U, 733U, 734U, 735U, 736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U,
    746U, 747U, 748U, 749U, 750U, 751U, 752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U,
    762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A16_373 =
{
    &INT_RESERVED_IRQ_LIST_U2A16_373[0],
    INT_RESERVED_IRQ_NUM_U2A16_373
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_516)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A16 516pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A16_516[INT_RESERVED_IRQ_NUM_U2A16_516] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 695U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 717U,
    718U, 719U, 720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U,
    734U, 735U, 736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U,
    750U, 751U, 752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U,
    766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A16_516 =
{
    &INT_RESERVED_IRQ_LIST_U2A16_516[0],
    INT_RESERVED_IRQ_NUM_U2A16_516
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_144)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A6 144pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A6_144[INT_RESERVED_IRQ_NUM_U2A6_144] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 165U, 166U, 167U, 168U, 169U, 170U, 171U, 172U, 173U, 174U,
    175U, 176U, 177U, 178U, 179U, 180U, 181U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U,
    224U, 272U, 273U, 274U, 275U, 276U ,277U, 278U, 279U, 280U, 281U, 282U, 283U, 284U, 285U, 286U,
    287U, 288U, 289U, 290U, 291U, 292U, 293U, 294U, 295U, 307U, 308U, 309U, 313U, 314U, 315U, 327U,
    328U, 329U, 330U, 331U, 332U, 333U, 334U, 335U, 336U, 337U, 338U, 339U, 340U, 341U, 342U, 343U,
    344U, 345U, 346U, 347U, 348U, 349U, 350U, 351U, 352U, 353U, 354U, 355U, 356U, 357U, 358U, 359U,
    420U, 421U, 422U, 423U, 440U, 441U, 442U, 443U, 464U, 465U, 466U, 467U, 468U, 469U, 470U, 471U,
    472U, 473U, 474U, 475U, 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U,
    488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 498U, 499U, 500U, 501U, 502U, 503U,
    504U, 505U, 506U, 507U, 508U, 509U, 510U, 511U, 524U, 525U, 526U, 527U, 534U, 535U, 536U, 537U,
    538U, 549U, 553U, 555U, 557U, 558U, 559U, 572U, 579U, 582U, 583U, 584U, 585U, 586U, 587U, 588U,
    589U, 590U, 591U, 603U, 604U, 605U, 612U, 613U, 614U, 615U, 616U, 617U, 618U, 619U, 620U, 621U,
    622U, 634U, 635U, 636U, 637U, 638U, 639U, 640U, 641U, 642U, 643U, 644U, 649U, 650U, 651U, 652U,
    653U, 673U, 674U, 675U, 676U, 677U, 678U, 679U, 680U, 681U, 682U, 683U, 684U, 689U, 690U, 691U,
    692U, 695U, 696U, 700U, 704U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 715U, 716U, 717U,
    718U, 719U, 720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U,
    734U, 735U, 736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U,
    750U, 751U, 752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U,
    766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A6_144 =
{
    &INT_RESERVED_IRQ_LIST_U2A6_144[0],
    INT_RESERVED_IRQ_NUM_U2A6_144
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_156)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A6 156pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A6_156[INT_RESERVED_IRQ_NUM_U2A6_156] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 165U, 166U, 167U, 168U, 169U, 170U, 171U, 172U, 173U, 174U,
    175U, 176U, 177U, 178U, 179U, 180U, 181U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U,
    224U, 238U, 239U, 240U, 241U, 242U, 243U, 280U, 281U, 282U, 283U, 284U, 285U, 286U, 287U, 288U,
    289U, 290U, 291U, 292U, 293U, 294U, 295U, 304U, 305U, 306U, 307U, 308U, 309U, 313U, 314U, 315U,
    319U, 320U, 321U, 336U, 337U, 338U, 339U, 340U, 341U, 342U, 343U, 344U, 345U, 346U, 347U, 348U,
    349U, 350U, 351U, 352U, 353U, 354U, 355U, 356U, 357U, 358U, 359U, 420U, 421U, 422U, 423U, 424U,
    425U, 426U, 427U, 440U, 441U, 442U, 443U, 444U, 445U, 446U, 447U, 464U, 465U, 466U, 467U, 468U,
    469U, 470U, 471U, 472U, 473U, 474U, 475U, 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U,
    485U, 486U, 487U, 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 498U, 499U, 500U,
    501U, 502U, 503U, 504U, 505U, 506U, 507U, 508U, 509U, 510U, 511U, 534U, 535U, 536U, 537U, 538U,
    539U, 540U, 541U, 542U, 543U, 556U, 557U, 558U, 559U, 562U, 566U, 572U, 573U, 576U, 579U, 582U,
    583U, 584U, 585U, 586U, 587U, 588U, 589U, 590U, 591U, 612U, 613U, 614U, 615U, 616U, 617U, 618U,
    619U, 620U, 621U, 622U, 634U, 635U, 636U, 637U, 638U, 639U, 640U, 641U, 642U, 643U, 644U, 645U,
    646U, 647U, 648U, 649U, 650U, 651U, 652U, 653U, 673U, 674U, 675U, 676U, 677U, 678U, 679U, 680U,
    681U, 682U, 683U, 684U, 693U, 694U, 695U, 696U, 700U, 704U, 707U, 708U, 709U, 710U, 711U, 712U,
    713U, 714U, 715U, 716U, 717U, 718U, 719U, 720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U,
    729U, 730U, 731U, 732U, 733U, 734U, 735U, 736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U,
    745U, 746U, 747U, 748U, 749U, 750U, 751U, 752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U,
    761U, 762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A6_156 =
{
    &INT_RESERVED_IRQ_LIST_U2A6_156[0],
    INT_RESERVED_IRQ_NUM_U2A6_156
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_176)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A6 176pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A6_176[INT_RESERVED_IRQ_NUM_U2A6_176] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U, 224U,
    280U, 281U, 282U, 283U, 284U, 285U, 286U, 287U, 288U, 289U, 290U, 291U, 292U, 293U, 294U, 295U,
    304U, 305U, 306U, 336U, 337U, 338U, 339U, 340U, 341U, 342U, 343U, 344U, 345U, 346U, 347U, 348U,
    349U, 350U, 351U, 352U, 353U, 354U, 355U, 356U, 357U, 358U, 359U, 464U, 465U, 466U, 467U, 468U,
    469U, 470U, 471U, 472U, 473U, 474U, 475U, 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U,
    485U, 486U, 487U, 488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 498U, 499U, 500U,
    501U, 502U, 503U, 504U, 505U, 506U, 507U, 508U, 509U, 510U, 511U, 534U, 535U, 536U, 537U, 538U,
    572U, 582U, 583U, 584U, 585U, 586U, 587U, 588U, 589U, 590U, 591U, 612U, 613U, 614U, 615U, 616U,
    617U, 618U, 619U, 620U, 621U, 622U, 634U, 635U, 636U, 637U, 638U, 639U, 640U, 641U, 642U, 643U,
    644U, 649U, 650U, 651U, 652U, 653U, 673U, 674U, 675U, 676U, 677U, 678U, 679U, 680U, 681U, 682U,
    683U, 684U, 695U, 704U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 716U, 717U, 718U, 719U,
    720U, 721U, 722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U, 734U, 735U,
    736U, 737U, 738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U, 750U, 751U,
    752U, 753U, 754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A6_176 =
{
    &INT_RESERVED_IRQ_LIST_U2A6_176[0],
    INT_RESERVED_IRQ_NUM_U2A6_176
};
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_292)
/*------------------------------------------------------------------------------------------*/
/* [Device Individuality Config] INT Reserved IRQ Configuration Table[U2A6 292pin]          */
/*------------------------------------------------------------------------------------------*/
/* Reserved IRQ List Table */
static const U2 INT_RESERVED_IRQ_LIST_U2A6_292[INT_RESERVED_IRQ_NUM_U2A6_292] =
{
     18U,  19U,  32U,  33U,  35U,  37U, 205U, 206U, 217U, 218U, 219U, 220U, 221U, 222U, 223U, 224U,
    280U, 281U, 282U, 283U, 284U, 285U, 286U, 287U, 288U, 289U, 290U, 291U, 292U, 293U, 294U, 295U,
    336U, 337U, 338U, 339U, 340U, 341U, 342U, 343U, 344U, 345U, 346U, 347U, 348U, 349U, 350U, 351U,
    352U, 353U, 354U, 355U, 356U, 357U, 358U, 359U, 464U, 465U, 466U, 467U, 468U, 469U, 470U, 471U,
    472U, 473U, 474U, 475U, 476U, 477U, 478U, 479U, 480U, 481U, 482U, 483U, 484U, 485U, 486U, 487U,
    488U, 489U, 490U, 491U, 492U, 493U, 494U, 495U, 496U, 497U, 498U, 499U, 500U, 501U, 502U, 503U,
    504U, 505U, 506U, 507U, 508U, 509U, 510U, 511U, 582U, 583U, 612U, 613U, 614U, 615U, 616U, 617U,
    618U, 619U, 620U, 621U, 622U, 634U, 635U, 636U, 637U, 638U, 639U, 640U, 641U, 642U, 643U, 644U,
    649U, 650U, 651U, 652U, 653U, 673U, 674U, 675U, 676U, 677U, 678U, 679U, 680U, 681U, 682U, 683U,
    684U, 695U, 704U, 707U, 708U, 709U, 710U, 711U, 712U, 713U, 714U, 717U, 718U, 719U, 720U, 721U,
    722U, 723U, 724U, 725U, 726U, 727U, 728U, 729U, 730U, 731U, 732U, 733U, 734U, 735U, 736U, 737U,
    738U, 739U, 740U, 741U, 742U, 743U, 744U, 745U, 746U, 747U, 748U, 749U, 750U, 751U, 752U, 753U,
    754U, 755U, 756U, 757U, 758U, 759U, 760U, 761U, 762U, 763U, 764U, 765U, 766U, 767U
};

/* INT Reserved IRQ Configuration Table */
static const Int_DevReservedIrqInfoType INT_DEVCFG_RSVINFO_DATA_U2A6_292 =
{
    &INT_RESERVED_IRQ_LIST_U2A6_292[0],
    INT_RESERVED_IRQ_NUM_U2A6_292
};
#endif

/* [Device Individuality Config] INT Device Individuality Configuration Table */
const Int_DevConfigType INT_DEVCFG_DATA =
{
#if     (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A8_292)
    &INT_DEVCFG_RSVINFO_DATA_U2A8_292
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A8_373)
    &INT_DEVCFG_RSVINFO_DATA_U2A8_373
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_292)
    &INT_DEVCFG_RSVINFO_DATA_U2A16_292
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_373)
    &INT_DEVCFG_RSVINFO_DATA_U2A16_373
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A16_516)
    &INT_DEVCFG_RSVINFO_DATA_U2A16_516
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_144)
    &INT_DEVCFG_RSVINFO_DATA_U2A6_144
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_156)
    &INT_DEVCFG_RSVINFO_DATA_U2A6_156
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_176)
    &INT_DEVCFG_RSVINFO_DATA_U2A6_176
#elif   (INT_DEVCFG_RESERVED_IRQ_TYPE == INT_RESERVED_IRQ_TYPE_U2A6_292)
    &INT_DEVCFG_RSVINFO_DATA_U2A6_292
#endif
};

#pragma ghs section rosdata = default


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/05/31 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/
/**** End of File *************************************************************/

