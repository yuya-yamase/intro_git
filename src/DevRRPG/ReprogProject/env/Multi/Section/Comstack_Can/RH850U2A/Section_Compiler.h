/* Section_Compiler_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Section/Compiler/HEADER                                     */
/******************************************************************************/
#ifndef SECTION_COMPILER_H
#define SECTION_COMPILER_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>


/******************************************************************************/
/* Vector                                                                     */
/******************************************************************************/
extern char __ghsbegin_P_ROM_VECT[];
extern char __ghsbegin_P_RAM_VECT[];
extern char __ghsbegin_ROM_P_RAM_VECT[];
extern char __ghsend_ROM_P_RAM_VECT[];
#define SECTION_ROM_VECT_ADDR                           ((uint32 *)(void *)__ghsbegin_P_ROM_VECT)
#define SECTION_RAMCOPY_VECT_DST_ADDR                   ((uint32 *)(void *)__ghsbegin_P_RAM_VECT)
#define SECTION_RAMCOPY_VECT_SRC_ADDR                   ((uint32 *)(void *)__ghsbegin_ROM_P_RAM_VECT)
#define SECTION_RAMCOPY_VECT_SRC_END_ADDR               ((uint32 *)(void *)__ghsend_ROM_P_RAM_VECT)


/******************************************************************************/
/* Stack                                                                      */
/******************************************************************************/
extern char __ghsbegin_RpgStackHigh[];
extern char __ghsbegin_RpgStackLow[];
extern char __ghssize_RpgStackLow[];
#define SECTION_RPG_STACK_HIGH_ADDR                     ((uint32 *)(void *)__ghsbegin_RpgStackHigh)
#define SECTION_RPG_STACK_LOW_ADDR                      ((uint32 *)(void *)__ghsbegin_RpgStackLow)
#define SECTION_RPG_STACK_MAX_SIZE                      ((uint32)__ghssize_RpgStackLow)


/******************************************************************************/
/* Ram.text(Before clock up)                                                  */
/******************************************************************************/
extern char __ghsbegin_RamCopy1st_CodeFixed_DstStart[];
extern char __ghsbegin_RamCopy1st_CodeFixed_SrcStart[];
extern char __ghsbegin_RamCopy1st_CodeFixed_SrcEnd[];
extern char __ghsbegin_RamCopy1st_1_Code_DstStart[];
extern char __ghsbegin_RamCopy1st_1_Code_SrcStart[];
extern char __ghsbegin_RamCopy1st_1_Code_SrcEnd[];
extern char __ghsbegin_RamCopy1st_2_Code_DstStart[];
extern char __ghsbegin_RamCopy1st_2_Code_SrcStart[];
extern char __ghsbegin_RamCopy1st_2_Code_SrcEnd[];
#define SECTION_RAMCOPY_1ST_FIXED_CODE_DST_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy1st_CodeFixed_DstStart)
#define SECTION_RAMCOPY_1ST_FIXED_CODE_SRC_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy1st_CodeFixed_SrcStart)
#define SECTION_RAMCOPY_1ST_FIXED_CODE_SRC_END_ADDR     ((uint32 *)(void *)__ghsbegin_RamCopy1st_CodeFixed_SrcEnd)
#define SECTION_RAMCOPY_1ST_1_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Code_DstStart)
#define SECTION_RAMCOPY_1ST_1_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Code_SrcStart)
#define SECTION_RAMCOPY_1ST_1_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Code_SrcEnd)
#define SECTION_RAMCOPY_1ST_2_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Code_DstStart)
#define SECTION_RAMCOPY_1ST_2_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Code_SrcStart)
#define SECTION_RAMCOPY_1ST_2_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Code_SrcEnd)


/******************************************************************************/
/* Ram.const(Before clock up)                                                 */
/******************************************************************************/
extern char __ghsbegin_RamCopy1st_1_Cst_DstStart[];
extern char __ghsbegin_RamCopy1st_1_Cst_SrcStart[];
extern char __ghsbegin_RamCopy1st_1_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy1st_2_Cst_DstStart[];
extern char __ghsbegin_RamCopy1st_2_Cst_SrcStart[];
extern char __ghsbegin_RamCopy1st_2_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy1st_1_Cst2_DstStart[];
extern char __ghsbegin_RamCopy1st_1_Cst2_SrcStart[];
extern char __ghsbegin_RamCopy1st_1_Cst2_SrcEnd[];
#define SECTION_RAMCOPY_1ST_1_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst_DstStart)
#define SECTION_RAMCOPY_1ST_1_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst_SrcStart)
#define SECTION_RAMCOPY_1ST_1_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst_SrcEnd)
#define SECTION_RAMCOPY_1ST_2_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Cst_DstStart)
#define SECTION_RAMCOPY_1ST_2_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Cst_SrcStart)
#define SECTION_RAMCOPY_1ST_2_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy1st_2_Cst_SrcEnd)
#define SECTION_RAMCOPY_1ST_1_CONST2_DST_ADDR           ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst2_DstStart)
#define SECTION_RAMCOPY_1ST_1_CONST2_SRC_ADDR           ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst2_SrcStart)
#define SECTION_RAMCOPY_1ST_1_CONST2_SRC_END_ADDR       ((uint32 *)(void *)__ghsbegin_RamCopy1st_1_Cst2_SrcEnd)


/******************************************************************************/
/* bss(Before clock up)                                                       */
/******************************************************************************/
extern char __ghsbegin_Ram1st_1_B_Start[];
extern char __ghsbegin_Ram1st_1_B_End[];
extern char __ghsbegin_Ram1st_2_B_Start[];
extern char __ghsbegin_Ram1st_2_B_End[];
extern char __ghsbegin_Ram1st_1_B2_Start[];
extern char __ghsbegin_Ram1st_1_B2_End[];
#define SECTION_RAM_1ST_1_B_ADDR                        ((uint32 *)(void *)__ghsbegin_Ram1st_1_B_Start)
#define SECTION_RAM_1ST_1_B_END_ADDR                    ((uint32 *)(void *)__ghsbegin_Ram1st_1_B_End)
#define SECTION_RAM_1ST_2_B_ADDR                        ((uint32 *)(void *)__ghsbegin_Ram1st_2_B_Start)
#define SECTION_RAM_1ST_2_B_END_ADDR                    ((uint32 *)(void *)__ghsbegin_Ram1st_2_B_End)
#define SECTION_RAM_1ST_1_B2_ADDR                       ((uint32 *)(void *)__ghsbegin_Ram1st_1_B2_Start)
#define SECTION_RAM_1ST_1_B2_END_ADDR                   ((uint32 *)(void *)__ghsbegin_Ram1st_1_B2_End)


/******************************************************************************/
/* Ram.text(After clock up)                                                   */
/******************************************************************************/
extern char __ghsbegin_RamCopy2nd_CodeFixed_DstStart[];
extern char __ghsbegin_RamCopy2nd_CodeFixed_SrcStart[];
extern char __ghsbegin_RamCopy2nd_CodeFixed_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_1_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_1_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_1_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_2_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_2_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_2_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_3_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_3_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_3_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_4_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_4_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_4_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_5_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_5_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_5_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_6_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_6_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_6_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_7_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_7_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_7_Code_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_8_Code_DstStart[];
extern char __ghsbegin_RamCopy2nd_8_Code_SrcStart[];
extern char __ghsbegin_RamCopy2nd_8_Code_SrcEnd[];
#define SECTION_RAMCOPY_2ND_FIXED_CODE_DST_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CodeFixed_DstStart)
#define SECTION_RAMCOPY_2ND_FIXED_CODE_SRC_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CodeFixed_SrcStart)
#define SECTION_RAMCOPY_2ND_FIXED_CODE_SRC_END_ADDR     ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CodeFixed_SrcEnd)
#define SECTION_RAMCOPY_2ND_1_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Code_DstStart)
#define SECTION_RAMCOPY_2ND_1_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_1_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_2_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Code_DstStart)
#define SECTION_RAMCOPY_2ND_2_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_2_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_3_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Code_DstStart)
#define SECTION_RAMCOPY_2ND_3_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_3_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_4_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Code_DstStart)
#define SECTION_RAMCOPY_2ND_4_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_4_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_5_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Code_DstStart)
#define SECTION_RAMCOPY_2ND_5_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_5_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_6_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Code_DstStart)
#define SECTION_RAMCOPY_2ND_6_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_6_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_7_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Code_DstStart)
#define SECTION_RAMCOPY_2ND_7_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_7_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Code_SrcEnd)
#define SECTION_RAMCOPY_2ND_8_CODE_DST_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Code_DstStart)
#define SECTION_RAMCOPY_2ND_8_CODE_SRC_ADDR             ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Code_SrcStart)
#define SECTION_RAMCOPY_2ND_8_CODE_SRC_END_ADDR         ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Code_SrcEnd)

#if (REPROG_CFG_SBL_TYPE_WITHIN == STD_ON)
extern char __ghsbegin_RamCopy2nd_Sbl_DstStart[];
extern char __ghsbegin_RamCopy2nd_Sbl_SrcStart[];
extern char __ghsbegin_RamCopy2nd_Sbl_SrcEnd[];
#define SECTION_RAMCOPY_2ND_SBL_DST_ADDR                ((uint32 *)(void *)__ghsbegin_RamCopy2nd_Sbl_DstStart)
#define SECTION_RAMCOPY_2ND_SBL_SRC_ADDR                ((uint32 *)(void *)__ghsbegin_RamCopy2nd_Sbl_SrcStart)
#define SECTION_RAMCOPY_2ND_SBL_SRC_END_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_Sbl_SrcEnd)
#endif


/******************************************************************************/
/* Ram.const(After clock up)                                                  */
/******************************************************************************/
extern char __ghsbegin_RamCopy2nd_CstFixed_DstStart[];
extern char __ghsbegin_RamCopy2nd_CstFixed_SrcStart[];
extern char __ghsbegin_RamCopy2nd_CstFixed_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_1_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_1_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_1_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_2_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_2_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_2_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_3_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_3_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_3_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_4_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_4_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_4_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_5_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_5_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_5_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_6_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_6_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_6_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_7_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_7_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_7_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_8_Cst_DstStart[];
extern char __ghsbegin_RamCopy2nd_8_Cst_SrcStart[];
extern char __ghsbegin_RamCopy2nd_8_Cst_SrcEnd[];
extern char __ghsbegin_RamCopy2nd_1_Cst2_DstStart[];
extern char __ghsbegin_RamCopy2nd_1_Cst2_SrcStart[];
extern char __ghsbegin_RamCopy2nd_1_Cst2_SrcEnd[];
#define SECTION_RAMCOPY_2ND_FIXED_CONST_DST_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CstFixed_DstStart)
#define SECTION_RAMCOPY_2ND_FIXED_CONST_SRC_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CstFixed_SrcStart)
#define SECTION_RAMCOPY_2ND_FIXED_CONST_SRC_END_ADDR    ((uint32 *)(void *)__ghsbegin_RamCopy2nd_CstFixed_SrcEnd)
#define SECTION_RAMCOPY_2ND_1_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_1_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_1_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_2_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_2_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_2_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_2_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_3_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_3_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_3_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_3_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_4_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_4_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_4_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_4_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_5_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_5_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_5_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_5_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_6_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_6_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_6_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_6_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_7_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_7_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_7_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_7_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_8_CONST_DST_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Cst_DstStart)
#define SECTION_RAMCOPY_2ND_8_CONST_SRC_ADDR            ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Cst_SrcStart)
#define SECTION_RAMCOPY_2ND_8_CONST_SRC_END_ADDR        ((uint32 *)(void *)__ghsbegin_RamCopy2nd_8_Cst_SrcEnd)
#define SECTION_RAMCOPY_2ND_1_CONST2_DST_ADDR           ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst2_DstStart)
#define SECTION_RAMCOPY_2ND_1_CONST2_SRC_ADDR           ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst2_SrcStart)
#define SECTION_RAMCOPY_2ND_1_CONST2_SRC_END_ADDR       ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst2_SrcEnd)


/******************************************************************************/
/* bss(After clock up)                                                        */
/******************************************************************************/
extern char __ghsbegin_Ram2nd_B_Fixed_Start[];
extern char __ghsbegin_Ram2nd_B_Fixed_End[];
extern char __ghsbegin_Ram2nd_1_B_Start[];
extern char __ghsbegin_Ram2nd_1_B_End[];
extern char __ghsbegin_Ram2nd_2_B_Start[];
extern char __ghsbegin_Ram2nd_2_B_End[];
extern char __ghsbegin_Ram2nd_1_B2_Start[];
extern char __ghsbegin_Ram2nd_1_B2_End[];
#define SECTION_RAM_2ND_FIXED_B_ADDR                    ((uint32 *)(void *)__ghsbegin_Ram2nd_B_Fixed_Start)
#define SECTION_RAM_2ND_FIXED_B_END_ADDR                ((uint32 *)(void *)__ghsbegin_Ram2nd_B_Fixed_End)
#define SECTION_RAM_2ND_1_B_ADDR                        ((uint32 *)(void *)__ghsbegin_Ram2nd_1_B_Start)
#define SECTION_RAM_2ND_1_B_END_ADDR                    ((uint32 *)(void *)__ghsbegin_Ram2nd_1_B_End)
#define SECTION_RAM_2ND_2_B_ADDR                        ((uint32 *)(void *)__ghsbegin_Ram2nd_2_B_Start)
#define SECTION_RAM_2ND_2_B_END_ADDR                    ((uint32 *)(void *)__ghsbegin_Ram2nd_2_B_End)
#define SECTION_RAM_2ND_1_B2_ADDR                       ((uint32 *)(void *)__ghsbegin_Ram2nd_1_B2_Start)
#define SECTION_RAM_2ND_1_B2_END_ADDR                   ((uint32 *)(void *)__ghsbegin_Ram2nd_1_B2_End)


/******************************************************************************/
/* SBL                                                                        */
/******************************************************************************/
extern char __ghsbegin_RamCopy2nd_Sbl_DstStart[];
#if (REPROG_CFG_SBL_TYPE_DOWNLOAD == STD_ON)
extern char __ghsbegin_RamCopy2nd_Sbl_DstEnd[];
#endif
#define SECTION_SBL_DOWNLOAD_ADDR                       ((uint32 *)(void *)__ghsbegin_RamCopy2nd_Sbl_DstStart)
#if (REPROG_CFG_SBL_TYPE_DOWNLOAD == STD_ON)
  #define SECTION_SBL_DOWNLOAD_END_ADDR                 ((uint32 *)(void *)__ghsbegin_RamCopy2nd_Sbl_DstEnd)
#else
  #define SECTION_SBL_DOWNLOAD_END_ADDR                 (SECTION_SBL_DOWNLOAD_ADDR)
#endif


/******************************************************************************/
/* Unused RAM                                                                 */
/******************************************************************************/
#define SECTION_UNUSEDRAM_CLEAR                         (STD_ON)

#if (SECTION_UNUSEDRAM_CLEAR == STD_ON)
  extern char __ghsbegin_LocalRamStart[];
  extern char __ghsbegin_RpgRam1Start[];
  extern char __ghsbegin_RpgRam1End[];
  extern char __ghsbegin_LocalRamEndNext[];
  extern char __ghsbegin_Cluster0RamStart[];
  extern char __ghsbegin_RpgRam2Start[];
  extern char __ghsbegin_RamCopy2nd_1_Cst2_DstEnd[];
  extern char __ghsbegin_RpgRam2End[];
  extern char __ghsbegin_Cluster0RamEndNext[];
  #define SECTION_UNUSEDRAM_1_ADDR                      ((uint32 *)(void *)__ghsbegin_LocalRamStart)
  #define SECTION_UNUSEDRAM_1_END_ADDR                  ((uint32 *)(void *)__ghsbegin_RpgRam1Start)
  #define SECTION_UNUSEDRAM_2_ADDR                      ((uint32 *)(void *)__ghsbegin_RpgStackHigh)
  #define SECTION_UNUSEDRAM_2_END_ADDR                  ((uint32 *)(void *)__ghsbegin_RpgRam1End)
  #define SECTION_UNUSEDRAM_3_ADDR                      ((uint32 *)(void *)__ghsbegin_RpgRam1End)
  #define SECTION_UNUSEDRAM_3_END_ADDR                  ((uint32 *)(void *)__ghsbegin_LocalRamEndNext)
  #define SECTION_UNUSEDRAM_4_ADDR                      ((uint32 *)(void *)__ghsbegin_Cluster0RamStart)
  #define SECTION_UNUSEDRAM_4_END_ADDR                  ((uint32 *)(void *)__ghsbegin_RpgRam2Start)
  #define SECTION_UNUSEDRAM_5_ADDR                      ((uint32 *)(void *)__ghsbegin_RamCopy2nd_1_Cst2_DstEnd)
  #define SECTION_UNUSEDRAM_5_END_ADDR                  ((uint32 *)(void *)__ghsbegin_RpgRam2End)
  #define SECTION_UNUSEDRAM_6_ADDR                      ((uint32 *)(void *)__ghsbegin_RpgRam2End)
  #define SECTION_UNUSEDRAM_6_END_ADDR                  ((uint32 *)(void *)__ghsbegin_Cluster0RamEndNext)
#else
  extern char __ghsbegin_RpgRam1Start[];
  #define SECTION_UNUSEDRAM_DUMMY_ADDR                  ((uint32 *)(void *)__ghsbegin_RpgRam1Start)
  #define SECTION_UNUSEDRAM_DUMMY_END_ADDR              ((uint32 *)(void *)__ghsbegin_RpgRam1Start)
#endif

#endif

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/


