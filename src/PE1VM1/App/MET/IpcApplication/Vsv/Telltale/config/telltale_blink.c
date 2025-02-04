/* 5.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Telltale Config                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TELLTALE_BLINK_C_MAJOR                   (5)
#define TELLTALE_BLINK_C_MINOR                   (5)
#define TELLTALE_BLINK_C_PATCH                   (1)

#define TELLTALE_BLINK_C_REV                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "telltale_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TELLTALE_BLINK_C_MAJOR != TELLTALE_H_MAJOR) || \
     (TELLTALE_BLINK_C_MINOR != TELLTALE_H_MINOR) || \
     (TELLTALE_BLINK_C_PATCH != TELLTALE_H_PATCH))
#error "telltale_cfg.c and telltale.h : source and header files are inconsistent!"
#endif

#if ((TELLTALE_BLINK_C_MAJOR != TELLTALE_BLINKID_H_MAJOR) || \
     (TELLTALE_BLINK_C_MINOR != TELLTALE_BLINKID_H_MINOR) || \
     (TELLTALE_BLINK_C_PATCH != TELLTALE_BLINKID_H_PATCH))
#error "telltale_cfg.c and telltale_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TT_NUMOPD(st_opd)      (sizeof(st_opd) / sizeof(ST_TT_OPD))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
 /* "st_sp_TT_CO_OFF____100P" is reserved by telltale.c. Do not Delete! */
static const ST_TT_OPD st_sp_TT_CO_OFF____100P[] = {
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_CO_ON_____100P[] = {
    {(U1)TRUE , (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_CO_1P00HZ__50P_S_ON[] = {
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_1P00HZ__50P_S_OF[] = {
    {(U1)FALSE, (U2)(  500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_1P00HZ__50P__3T_E_OF[] = {
    {(U1)FALSE, (U2)(  500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)}, 
    {(U1)FALSE, (U2)( 1500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 2000U/TT_MAINTICK)}, 
    {(U1)FALSE, (U2)( 2500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 3000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_1P00HZ__50P__4T_E_OF[] = {
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 2500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 3000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_1P00HZ__50P_10T_E_ON[] = {
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 2500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 3000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 4500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 5000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 5500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 6000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 6500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 7000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 7500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 8000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 8500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 9000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 9500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(10000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_1P00HZ__50P_62T_E_ON[] ={
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 2500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 3000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 4500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 5000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 5500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 6000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 6500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 7000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 7500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 8000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 8500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 9000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 9500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(10000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(10500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(11000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(11500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(12000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(12500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(13000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(13500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(14000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(14500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(15000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(15500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(16000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(16500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(17000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(17500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(18000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(18500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(19000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(19500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(20000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(20500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(21000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(21500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(22000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(22500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(23000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(23500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(24000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(24500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(25000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(25500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(26000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(26500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(27000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(27500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(28000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(28500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(29000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(29500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(30000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(30500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(31000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(31500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(32000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(32500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(33000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(33500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(34000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(34500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(35000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(35500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(36000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(36500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(37000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(37500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(38000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(38500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(39000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(39500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(40000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(40500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(41000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(41500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(42000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(42500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(43000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(43500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(44000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(44500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(45000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(45500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(46000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(46500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(47000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(47500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(48000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(48500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(49000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(49500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(50000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(50500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(51000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(51500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(52000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(52500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(53000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(53500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(54000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(54500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(55000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(55500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(56000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(56500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(57000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(57500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(58000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(58500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(59000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(59500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(60000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(60500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(61000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(61500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(62000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_CO_1P00HZ__70P[] = {
    {(U1)TRUE , (U2)(  700U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_0P83HZ__50P[] = {
    {(U1)TRUE , (U2)(  600U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1200U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_0P67HZ__50P[] = {
    {(U1)TRUE , (U2)(  750U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 1500U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_0P50HZ__25P[] = {
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_0P50HZ__50P[] = {
    {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_SI_0P50HZ__50P_8T_E_OF[] = {
    {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 5000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 6000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 7000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 8000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 9000U/TT_MAINTICK)}, {(U1)FALSE, (U2)(10000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(11000U/TT_MAINTICK)}, {(U1)FALSE, (U2)(12000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(13000U/TT_MAINTICK)}, {(U1)FALSE, (U2)(14000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(15000U/TT_MAINTICK)}, {(U1)FALSE, (U2)(16000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_0P50HZ__50P_3T_E_OF[] = {
    {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 5000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 6000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_CO_0P50HZ__75P[] = {
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_4P00HZ__50P[] = {
    {(U1)TRUE , (U2)(  125U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  250U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_4P00HZ__60P[] = {
    {(U1)TRUE , (U2)(  150U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  250U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_3P33HZ__50P[] = {
    {(U1)TRUE , (U2)(  150U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  300U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_2P50HZ__50P[] = {
    {(U1)TRUE , (U2)(  200U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  400U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_2P00HZ__50P_S_ON[] = {
    {(U1)TRUE , (U2)(  250U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  500U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_2P00HZ__50P_S_OF[] = {
    {(U1)FALSE, (U2)(  250U/TT_MAINTICK)}, {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_1P67HZ__50P[] = {
    {(U1)TRUE , (U2)(  300U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  600U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_CO_1P50HZ__50P[] = {
    {(U1)TRUE , (U2)(  333U/TT_MAINTICK)}, {(U1)FALSE, (U2)(  666U/TT_MAINTICK)}
};

static const ST_TT_OPD st_sp_TT_SI_0P29HZ__85P_3T_E_OF[] = {
    {(U1)TRUE , (U2)( 3000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 3500U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 7000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 7500U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(11000U/TT_MAINTICK)}, {(U1)FALSE, (U2)(11500U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_CO_0P25HZ__50P[] = {
    {(U1)TRUE , (U2)( 2000U/TT_MAINTICK)}, {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)}
};


static const ST_TT_OPD st_sp_TT_SI_TPMS_SYSSTOP[] = {
    {(U1)TRUE , (U2)( 1000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)( 1500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 2000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)( 2500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 3000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)( 3500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 4000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)( 4500U/TT_MAINTICK)}, {(U1)TRUE , (U2)( 5000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_1P00HZ__50P_5T_E_OF[] = {
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(1000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 2500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(3000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 4500U/TT_MAINTICK)}, {(U1)FALSE, (U2)(5000U/TT_MAINTICK)},
    {(U1)FALSE, (U2)TT_OPD_HOLD         }
};

static const ST_TT_OPD st_sp_TT_SI_1P00HZ__50P_63T_E_ON[] ={
    {(U1)TRUE , (U2)(  500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 1000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 1500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 2000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 2500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 3000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 3500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 4000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 4500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 5000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 5500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 6000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 6500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 7000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 7500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 8000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 8500U/TT_MAINTICK)} , {(U1)FALSE, (U2)( 9000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)( 9500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(10000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(10500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(11000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(11500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(12000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(12500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(13000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(13500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(14000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(14500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(15000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(15500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(16000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(16500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(17000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(17500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(18000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(18500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(19000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(19500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(20000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(20500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(21000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(21500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(22000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(22500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(23000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(23500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(24000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(24500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(25000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(25500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(26000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(26500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(27000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(27500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(28000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(28500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(29000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(29500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(30000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(30500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(31000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(31500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(32000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(32500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(33000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(33500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(34000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(34500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(35000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(35500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(36000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(36500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(37000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(37500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(38000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(38500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(39000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(39500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(40000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(40500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(41000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(41500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(42000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(42500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(43000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(43500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(44000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(44500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(45000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(45500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(46000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(46500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(47000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(47500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(48000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(48500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(49000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(49500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(50000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(50500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(51000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(51500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(52000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(52500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(53000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(53500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(54000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(54500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(55000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(55500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(56000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(56500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(57000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(57500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(58000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(58500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(59000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(59500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(60000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(60500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(61000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(61500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(62000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)(62500U/TT_MAINTICK)} , {(U1)FALSE, (U2)(63000U/TT_MAINTICK)},
    {(U1)TRUE , (U2)TT_OPD_HOLD         }
};

const ST_TT_BLINK st_gp_TT_BLINK[TT_NUM_BLINK] = {
    /* 0:TT_BL_CO_OFF____100P */
    {
        &st_sp_TT_CO_OFF____100P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_OFF____100P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 1:TT_BL_CO_ON_____100P */
    {
        &st_sp_TT_CO_ON_____100P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_ON_____100P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 2:TT_BL_CO_1P00HZ__50P_S__ON */
    {
        &st_sp_TT_CO_1P00HZ__50P_S_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__50P_S_ON),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 3:TT_BL_CO_1P00HZ__50P_S_OFF */
    {
        &st_sp_TT_CO_1P00HZ__50P_S_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__50P_S_OF),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 4:TT_BL_SI_1P00HZ__50P__3T_E_OFF */
    {
        &st_sp_TT_1P00HZ__50P__3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_1P00HZ__50P__3T_E_OF),   /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 5:TT_BL_SI_1P00HZ__50P__4T_E_OFF */
    {
        &st_sp_TT_SI_1P00HZ__50P__4T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_1P00HZ__50P__4T_E_OF),/* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 6:TT_BL_SI_1P00HZ__50P_10T_E__ON */
    {
        &st_sp_TT_SI_1P00HZ__50P_10T_E_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_1P00HZ__50P_10T_E_ON),/* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 7:TT_BL_SI_1P00HZ__50P_62T_E__ON */
    {
        &st_sp_TT_SI_1P00HZ__50P_62T_E_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_1P00HZ__50P_62T_E_ON),/* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 8:TT_BL_CO_1P00HZ__70P */
    {
        &st_sp_TT_CO_1P00HZ__70P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__70P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 9:TT_BL_CO_0P83HZ__50P */
    {
        &st_sp_TT_CO_0P83HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P83HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 10:TT_BL_CO_0P67HZ__50P */
    {
        &st_sp_TT_CO_0P67HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P67HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 11:TT_BL_CO_0P50HZ__25P */
    {
        &st_sp_TT_CO_0P50HZ__25P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P50HZ__25P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 12:TT_BL_CO_0P50HZ__50P */
    {
        &st_sp_TT_CO_0P50HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P50HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 13:TT_BL_SI_0P50HZ__50P_8T_E_OFF */
    {
        &st_sp_TT_SI_0P50HZ__50P_8T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_0P50HZ__50P_8T_E_OF), /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 14:TT_BL_SI_0P50HZ__50P_3T_E_OFF */
    {
        &st_sp_TT_SI_0P50HZ__50P_3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_0P50HZ__50P_3T_E_OF), /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 15:TT_BL_CO_0P50HZ__75P */
    {
        &st_sp_TT_CO_0P50HZ__75P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P50HZ__75P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 16:TT_BL_CO_4P00HZ__50P */
    {
        &st_sp_TT_CO_4P00HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_4P00HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 17:TT_BL_CO_4P00HZ__60P */
    {
        &st_sp_TT_CO_4P00HZ__60P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_4P00HZ__60P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 18:TT_BL_CO_3P33HZ__50P */
    {
        &st_sp_TT_CO_3P33HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_3P33HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 19:TT_BL_CO_2P50HZ__50P */
    {
        &st_sp_TT_CO_2P50HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_2P50HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 20:TT_BL_CO_2P00HZ__50P_S__ON */
    {
        &st_sp_TT_CO_2P00HZ__50P_S_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_2P00HZ__50P_S_ON),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 21:TT_BL_CO_2P00HZ__50P_S_OFF */
    {
        &st_sp_TT_CO_2P00HZ__50P_S_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_2P00HZ__50P_S_OF),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 22:TT_BL_CO_1P67HZ__50P */
    {
        &st_sp_TT_CO_1P67HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P67HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 23:TT_BL_CO_1P50HZ__50P */
    {
        &st_sp_TT_CO_1P50HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P50HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 24:TT_BL_SI_0P29HZ__85P_3T_E_OFF */
    {
        &st_sp_TT_SI_0P29HZ__85P_3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_0P29HZ__85P_3T_E_OF), /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 25:TT_BL_CO_0P25HZ__50P */
    {
        &st_sp_TT_CO_0P25HZ__50P[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_0P25HZ__50P),         /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 26:TT_BL_CO_1P00HZ__50P_S__ON_PRDWT */
    {
        &st_sp_TT_CO_1P00HZ__50P_S_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__50P_S_ON),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)TRUE                                        /* u1_swc_cycl  */
    },
    /* 27:TT_BL_CO_1P00HZ__50P_S__ON_MIN2 */
    {
        &st_sp_TT_CO_1P00HZ__50P_S_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__50P_S_ON),    /* u1_num_opd   */
        (U1)2U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 28:TT_BL_SI_TPMS_SYSSTOP */
    {
        &st_sp_TT_SI_TPMS_SYSSTOP[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_TPMS_SYSSTOP),        /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 29:TT_BL_CO_1P00HZ__50P_S_OFF_SWC */
    {
        &st_sp_TT_CO_1P00HZ__50P_S_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_CO_1P00HZ__50P_S_OF),    /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)TRUE                                        /* u1_swc_cycl  */
    },
    /* 30:TT_BL_SI_1P00HZ__50P__5T_E_OFF */
    {
        &st_sp_TT_SI_1P00HZ__50P_5T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_1P00HZ__50P_5T_E_OF), /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 31:TT_BL_SI_1P00HZ__50P_63T_E__ON */
    {
        &st_sp_TT_SI_1P00HZ__50P_63T_E_ON[0],
        (U1)TT_NUMOPD(st_sp_TT_SI_1P00HZ__50P_63T_E_ON),/* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 32:TT_BL_SI_1P00HZ__50P__3T_E_OFF2 */
    {
        &st_sp_TT_1P00HZ__50P__3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_1P00HZ__50P__3T_E_OF),   /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 33:TT_BL_SI_1P00HZ__50P__3T_E_OFF3 */
    {
        &st_sp_TT_1P00HZ__50P__3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_1P00HZ__50P__3T_E_OF),   /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    },
    /* 34:TT_BL_SI_1P00HZ__50P__3T_E_OFF4 */
    {
        &st_sp_TT_1P00HZ__50P__3T_E_OF[0],
        (U1)TT_NUMOPD(st_sp_TT_1P00HZ__50P__3T_E_OF),   /* u1_num_opd   */
        (U1)0U,                                         /* u1_min_cycl  */
        (U1)FALSE                                       /* u1_swc_cycl  */
    }
};

const U1    u1_g_TT_NUM_BLINK = (U1)TT_NUM_BLINK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  3.0.0    02/07/2018  TA       New.                                                                                               */
/*  3.1.0    02/07/2018  TA       telltale.c v3.0.0 -> v3.1.0                                                                        */
/*  3.2.0    05/06/2018  TA       telltale.c v3.1.0 -> v3.2.0                                                                        */
/*  3.2.1    12/06/2018  TA       telltale.c v3.2.0 -> v3.2.1                                                                        */
/*  3.3.0    01/10/2018  TA       telltale.c v3.2.1 -> v3.3.0                                                                        */
/*  5.0.0    07/11/2019  TA       telltale.c v3.3.0 -> v5.0.0                                                                        */
/*  5.1.0    04/23/2020  TA       telltale.c v5.0.0 -> v5.1.0                                                                        */
/*  5.2.0    04/29/2020  TA       telltale.c v5.1.0 -> v5.2.0                                                                        */
/*  5.4.0    07/15/2020  ST       telltale.c v5.3.0 -> v5.4.0                                                                        */
/*  5.5.0    07/12/2021  TA       telltale.c v5.4.0 -> v5.5.0                                                                        */
/*  5.5.1    10/18/2021  TA(M)    telltale.c v5.5.0 -> v5.5.1                                                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   07/15/2020  ST       Configured for 800B CV-R.                                                                          */
/*  19PFv3-1 10/30/2023  SH       Config merge                                                                                       */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * ST   = Syo Toyoda, KSE                                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
