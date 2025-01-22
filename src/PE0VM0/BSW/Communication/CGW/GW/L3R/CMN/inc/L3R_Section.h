/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/*************************************************************************//**
 * @file L3R_Section.h
 ****************************************************************************/
#ifndef L3R_SECTION_H
#define L3R_SECTION_H

#include "Section_Util.h"

#define L3R_PRAGMA_SECTION_CODE_START PRAGMA_SECTION(text, ".gw_l3r_code")
#define L3R_PRAGMA_SECTION_CODE_STOP  PRAGMA_SECTION_DEFAULT(text)

#define L3R_PRAGMA_SECTION_CONST_START PRAGMA_SECTION(rodata, ".gw_l3r_const")
#define L3R_PRAGMA_SECTION_CONST_STOP  PRAGMA_SECTION_DEFAULT(rodata)

#define L3R_PRAGMA_SECTION_NBVA_ZI_START PRAGMA_SECTION(bss, ".gw_l3r_nbva_zi")
#define L3R_PRAGMA_SECTION_NBVA_ZI_STOP  PRAGMA_SECTION_DEFAULT(bss)

#define L3R_PRAGMA_SECTION_BUVA_ZI_START PRAGMA_SECTION(bss, ".gw_l3r_buva_zi")
#define L3R_PRAGMA_SECTION_BUVA_ZI_STOP  PRAGMA_SECTION_DEFAULT(bss)


#endif /* L3R_SECTION_H */

