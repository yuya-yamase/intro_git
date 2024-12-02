/* 1.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3CRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef RIM_MOD_3CRAM_H
#define RIM_MOD_3CRAM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3CRAM_H_MAJOR                    (1U)
#define RIM_MOD_3CRAM_H_MINOR                    (2U)
#define RIM_MOD_3CRAM_H_PATCH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2  u2_index;
    U2  u2_size;
}ST_RIM_MOD_3CRAM_SIZE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __RIM_MOD_3CRAM_U1_USE__                 (TRUE)
#define __RIM_MOD_3CRAM_U2_USE__                 (TRUE)
#define __RIM_MOD_3CRAM_U4_USE__                 (TRUE)
#define __RIM_MOD_3CRAM_OTHER_USE__              (TRUE)

#define RIM_MOD_3CRAM_OTHER_ID_MAXSIZE           ((RIM_MOD_3CRAM_OTHER_ID_MAXBYTE + 3U) / 4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2 u2_d_RIM_MOD_3CRAM_DATA_ID_MASK;

#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3CRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3CRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3CRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3CRAM_OTR_ID_NUM;

extern const ST_RIM_MOD_3CRAM_SIZE st_d_RIM_MOD_3CRAM_OTR_SZ_CFG[];
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_d_RimMod_3CRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data);
U1      u1_d_RimMod_3CRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA);

U1      u1_d_RimMod_3CRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data);
U1      u1_d_RimMod_3CRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3CRAM_U1_USE__ == TRUE)
extern U1   u1_dp_rimmod_3cram_u1buf_main[];
extern U1   u1_dp_rimmod_3cram_u1buf_mirr1[];
extern U1   u1_dp_rimmod_3cram_u1buf_mirr2[];
#endif  /* #if (__RIM_MOD_3CRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U2_USE__ == TRUE)
extern U2   u2_dp_rimmod_3cram_u2buf_main[];
extern U2   u2_dp_rimmod_3cram_u2buf_mirr1[];
extern U2   u2_dp_rimmod_3cram_u2buf_mirr2[];
#endif  /* #if (__RIM_MOD_3CRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_U4_USE__ == TRUE)
extern U4   u4_dp_rimmod_3cram_u4buf_main[];
extern U4   u4_dp_rimmod_3cram_u4buf_mirr1[];
extern U4   u4_dp_rimmod_3cram_u4buf_mirr2[];
#endif  /* #if (__RIM_MOD_3CRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE)
extern U4   u4_dp_rimmod_3cram_otrbuf_main[];
extern U4   u4_dp_rimmod_3cram_otrbuf_mirr1[];
extern U4   u4_dp_rimmod_3cram_otrbuf_mirr2[];
#endif  /* #if (__RIM_MOD_3CRAM_OTHER_USE__ == TRUE) */


#endif /* RIM_MOD_3CRAM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see rim_mod_3cram.c                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
