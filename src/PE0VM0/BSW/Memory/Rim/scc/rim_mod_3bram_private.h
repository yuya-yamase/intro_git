/* 1.3.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RIM : MODULE_3BRAM                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef RIM_MOD_3BRAM_H
#define RIM_MOD_3BRAM_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RIM_MOD_3BRAM_H_MAJOR                    (1U)
#define RIM_MOD_3BRAM_H_MINOR                    (3U)
#define RIM_MOD_3BRAM_H_PATCH                    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2  u2_index;
    U2  u2_size;
}ST_RIM_MOD_3BRAM_SIZE;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define __RIM_MOD_3BRAM_U1_USE__                 (TRUE)
#define __RIM_MOD_3BRAM_U2_USE__                 (TRUE)
#define __RIM_MOD_3BRAM_U4_USE__                 (TRUE)
#define __RIM_MOD_3BRAM_OTHER_USE__              (TRUE)

#define RIM_MOD_3BRAM_OTHER_ID_MAXSIZE           ((RIM_MOD_3BRAM_OTHER_ID_MAXBYTE + 3U) / 4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Externs                                                                                                        */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U2 u2_d_RIM_MOD_3BRAM_MODULE_ID;
extern const U2 u2_d_RIM_MOD_3BRAM_DATA_ID_MASK;

#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3BRAM_U1_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3BRAM_U2_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3BRAM_U4_ID_NUM;
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
extern const U2 u2_d_RIM_MOD_3BRAM_OTR_ID_NUM;

extern const ST_RIM_MOD_3BRAM_SIZE st_d_RIM_MOD_3BRAM_OTR_SZ_CFG[];
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U1      u1_d_RimMod_3BRam_ReadU4(const U2 u2_a_ID, U4 *u4_ap_data);
U1      u1_d_RimMod_3BRam_WriteU4(const U2 u2_a_ID, const U4 u4_a_DATA);

void    vd_d_RimMod_3BOth_Init(const U1 u1_a_WUI); /* u1_a_WUI : TRUE = ECU Wakeup Initialization, FALSE = Not */
U1      u1_d_RimMod_3BRam_ReadOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, U1 *u1_ap_data);
U1      u1_d_RimMod_3BRam_WriteOther(const U2 u2_a_ID, const U2 u2_a_NBYTE, const U1 * const u1_ap_DATA);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (__RIM_MOD_3BRAM_U1_USE__ == TRUE)
extern U1   u1_dp_rimmod_3b_byte_main[];
extern U1   u1_dp_rimmod_3b_byte_mirr1[];
extern U1   u1_dp_rimmod_3b_byte_mirr2[];
#endif  /* #if (__RIM_MOD_3BRAM_U1_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U2_USE__ == TRUE)
extern U2   u2_dp_rimmod_3b_half_main[];
extern U2   u2_dp_rimmod_3b_half_mirr1[];
extern U2   u2_dp_rimmod_3b_half_mirr2[];
#endif  /* #if (__RIM_MOD_3BRAM_U2_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_U4_USE__ == TRUE)
extern U4   u4_dp_rimmod_3b_word_main[];
extern U4   u4_dp_rimmod_3b_word_mirr1[];
extern U4   u4_dp_rimmod_3b_word_mirr2[];
#endif  /* #if (__RIM_MOD_3BRAM_U4_USE__ == TRUE) */

#if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE)
extern U4   u4_dp_rimmod_3b_oth_main[];
extern U4   u4_dp_rimmod_3b_oth_mirr1[];
extern U4   u4_dp_rimmod_3b_oth_mirr2[];

extern U4   u4_dp_rimmod_3b_oth_cs_main[];
extern U4   u4_dp_rimmod_3b_oth_cs_mirr1[];
extern U4   u4_dp_rimmod_3b_oth_cs_mirr2[];
#endif  /* #if (__RIM_MOD_3BRAM_OTHER_USE__ == TRUE) */


#endif /* RIM_MOD_3BRAM_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see rim_mod_3bram.c                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
