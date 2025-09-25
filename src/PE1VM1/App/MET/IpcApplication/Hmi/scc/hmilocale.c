/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*   Hmilocale                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMILOCALE_C_MAJOR                         (1)
#define HMILOCALE_C_MINOR                         (1)
#define HMILOCALE_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#if 0   /* BEV Rebase provisionally */
#include "locale.h"
#endif   /* BEV Rebase provisionally */

#include "hmilocale.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMILOCALE_C_MAJOR != HMILOCALE_H_MAJOR) || \
     (HMILOCALE_C_MINOR != HMILOCALE_H_MINOR) || \
     (HMILOCALE_C_PATCH != HMILOCALE_H_PATCH))
#error "hmiodo.c and hmiodo.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMILOCALE_FUELCO_KMPL       (0U)    /* km/L         */
#define HMILOCALE_FUELCO_LP100KM    (1U)    /* L/100km      */
#define HMILOCALE_FUELCO_MPGUS      (2U)    /* MPG US       */
#define HMILOCALE_FUELCO_MPGUK      (3U)    /* MPG UK       */
#define HMILOCALE_FUELCO_MPGUKIMP   (4U)    /* MPG Imperial */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_HMILOCALE st_s_hmilocale_put;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiLocaleInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiLocaleInit(void)
{
    st_s_hmilocale_put.u1_language    = (U1)U1_MAX;
    st_s_hmilocale_put.u1_unit_dist   = (U1)U1_MAX;
    st_s_hmilocale_put.u1_unit_speed  = (U1)U1_MAX;
    st_s_hmilocale_put.u1_unit_fueco  = (U1)U1_MAX;
    st_s_hmilocale_put.u1_unit_eleco  = (U1)U1_MAX;
    st_s_hmilocale_put.u1_unit_ambtmp = (U1)U1_MAX;
    st_s_hmilocale_put.u1_timeformat  = (U1)U1_MAX;
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiLocaleMainTask(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiLocaleMainTask(void)
{
#if 0   /* BEV Rebase provisionally */
    if (st_s_hmilocale_put.u1_language <= (U1)HMILOCALE_LANG){
        vd_g_LanguagePut(st_s_hmilocale_put.u1_language);
    }

    /* if (st_s_hmilocale_put.u1_unit_dist <= (U1)HMILOCALE_DIST){ */
    /*    vd_g_UnitPut((U1)UNIT_IDX_DIST , st_s_hmilocale_put.u1_unit_dist); */
    /* } */
    /* if (st_s_hmilocale_put.u1_unit_speed <= (U1)HMILOCALE_SPEED){ */
    /*    vd_g_UnitPut((U1)UNIT_IDX_SPEED ,st_s_hmilocale_put.u1_unit_speed ); */
    /* } */

    if (st_s_hmilocale_put.u1_unit_fueco <= (U1)HMILOCALE_FUELCO){
        if(st_s_hmilocale_put.u1_unit_fueco == (U1)HMILOCALE_FUELCO_MPGUKIMP){
            st_s_hmilocale_put.u1_unit_fueco = (U1)HMILOCALE_FUELCO_MPGUK;
        }
        vd_g_UnitPut((U1)UNIT_IDX_FUECO , st_s_hmilocale_put.u1_unit_fueco);

        switch(st_s_hmilocale_put.u1_unit_fueco){
            case (U1)HMILOCALE_FUELCO_KMPL:
                vd_g_UnitPut((U1)UNIT_IDX_DIST , (U1)UNIT_VAL_DIST_KM);
                vd_g_UnitPut((U1)UNIT_IDX_SPEED ,(U1)UNIT_VAL_SPEED_KMPH);
                vd_g_UnitPut((U1)UNIT_IDX_ELECO , (U1)UNIT_VAL_ELECO_KMPKWH);
                break;
            case (U1)HMILOCALE_FUELCO_LP100KM:
                vd_g_UnitPut((U1)UNIT_IDX_DIST , (U1)UNIT_VAL_DIST_KM);
                vd_g_UnitPut((U1)UNIT_IDX_SPEED ,(U1)UNIT_VAL_SPEED_KMPH);
                vd_g_UnitPut((U1)UNIT_IDX_ELECO , (U1)UNIT_VAL_ELECO_KWHP100KM);
                break;
            case (U1)HMILOCALE_FUELCO_MPGUS:
            case (U1)HMILOCALE_FUELCO_MPGUK:
            case (U1)HMILOCALE_FUELCO_MPGUKIMP:
                vd_g_UnitPut((U1)UNIT_IDX_DIST , (U1)UNIT_VAL_DIST_MILE);
                vd_g_UnitPut((U1)UNIT_IDX_SPEED ,(U1)UNIT_VAL_SPEED_MPH);
                vd_g_UnitPut((U1)UNIT_IDX_ELECO , (U1)UNIT_VAL_ELECO_MILEPKWH);
                break;
            default:
                /* Do nothing */
                break;
        }
    }

/*   if (st_s_hmilocale_put.u1_unit_eleco <= (U1)HMILOCALE_ELECO){ */
/*        vd_g_UnitPut((U1)UNIT_IDX_ELECO , st_s_hmilocale_put.u1_unit_eleco); */
/*    } */
    if (st_s_hmilocale_put.u1_unit_ambtmp <= (U1)HMILOCALE_AMBTMP){
        vd_g_UnitPut((U1)UNIT_IDX_AMBTMP, st_s_hmilocale_put.u1_unit_ambtmp);
    }
    if (st_s_hmilocale_put.u1_timeformat <= (U1)HMILOCALE_TIMEFORMAT){
        vd_g_TimeFormat12H24HPut(st_s_hmilocale_put.u1_timeformat);
    }
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiLocalePut(const ST_HMILOCALE * stp_a_HMILOCALE)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_HmiLocalePut(const ST_HMILOCALE * stp_a_HMILOCALE)
{
    if(stp_a_HMILOCALE != vdp_PTR_NA){
        st_s_hmilocale_put.u1_language    = stp_a_HMILOCALE->u1_language    ;
        st_s_hmilocale_put.u1_unit_dist   = stp_a_HMILOCALE->u1_unit_dist   ;
        st_s_hmilocale_put.u1_unit_speed  = stp_a_HMILOCALE->u1_unit_speed  ;
        st_s_hmilocale_put.u1_unit_fueco  = stp_a_HMILOCALE->u1_unit_fueco  ;
        st_s_hmilocale_put.u1_unit_eleco  = stp_a_HMILOCALE->u1_unit_eleco  ;
        st_s_hmilocale_put.u1_unit_ambtmp = stp_a_HMILOCALE->u1_unit_ambtmp ;
        st_s_hmilocale_put.u1_timeformat  = stp_a_HMILOCALE->u1_timeformat  ;
    }
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2019  TA       New.                                                                                               */
/*  1.1.0    09/02/2020  TA       See hmiproxy.c                                                                                     */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/
