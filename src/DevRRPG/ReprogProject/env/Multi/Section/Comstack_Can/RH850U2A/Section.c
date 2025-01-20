/* Section_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Section/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include "Section.h"
#include "Section_Compiler.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SECTION_RPG_STACK_MIN_SIZE      (256UL)

#define SECTION_1ST_COPY_TEXT_NUM       (sizeof(Section_1stTextInfo) / sizeof(Section_1stTextInfo[0]))
#define SECTION_1ST_COPY_CONST_NUM      (sizeof(Section_1stConstInfo) / sizeof(Section_1stConstInfo[0]))
#define SECTION_1ST_BSS_NUM             (sizeof(Section_1stBssInfo) / sizeof(Section_1stBssInfo[0]))
#define SECTION_2ND_COPY_TEXT_NUM       (sizeof(Section_2ndTextInfo) / sizeof(Section_2ndTextInfo[0]))
#define SECTION_2ND_COPY_CONST_NUM      (sizeof(Section_2ndConstInfo) / sizeof(Section_2ndConstInfo[0]))
#define SECTION_2ND_BSS_NUM             (sizeof(Section_2ndBssInfo) / sizeof(Section_2ndBssInfo[0]))
#define SECTION_DL_NUM                  (sizeof(Section_DlInfo) / sizeof(Section_DlInfo[0]))
#define SECTION_UNUSEDRAM_NUM           (sizeof(Section_UnusedRamInfo) / sizeof(Section_UnusedRamInfo[0]))


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SECTION_START_SEC_CST
#include <Section_MemMap.h>

/******************************************************************************/
/* Vector                                                                     */
/******************************************************************************/
static CONST(Section_VectorRomInfoType, SECTION_CONST) Section_VectorRomInfo = {
    SECTION_ROM_VECT_ADDR
};
static CONST(Section_VectorRamInfoType, SECTION_CONST) Section_VectorRamInfo = {
    SECTION_RAMCOPY_VECT_DST_ADDR,
    SECTION_RAMCOPY_VECT_SRC_ADDR,
    SECTION_RAMCOPY_VECT_SRC_END_ADDR
};
CONST(Section_VectorType, SECTION_CONST) Section_VectorData = {
    &Section_VectorRomInfo,
    &Section_VectorRamInfo
};

/******************************************************************************/
/* Stack                                                                      */
/******************************************************************************/
CONST(Section_StackType, SECTION_CONST) Section_StackData = {
    SECTION_RPG_STACK_HIGH_ADDR,
    SECTION_RPG_STACK_MIN_SIZE,
    SECTION_RPG_STACK_MAX_SIZE,
    SECTION_RPG_STACK_LOW_ADDR
};

/******************************************************************************/
/* Ram.text(Before clock up)                                                  */
/******************************************************************************/
static CONST(Section_RomRamCopyTextInfoType, SECTION_CONST) Section_1stTextInfo[] = {
     { SECTION_RAMCOPY_1ST_FIXED_CODE_DST_ADDR, SECTION_RAMCOPY_1ST_FIXED_CODE_SRC_ADDR, SECTION_RAMCOPY_1ST_FIXED_CODE_SRC_END_ADDR }
    ,{ SECTION_RAMCOPY_1ST_1_CODE_DST_ADDR,     SECTION_RAMCOPY_1ST_1_CODE_SRC_ADDR,     SECTION_RAMCOPY_1ST_1_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_1ST_2_CODE_DST_ADDR,     SECTION_RAMCOPY_1ST_2_CODE_SRC_ADDR,     SECTION_RAMCOPY_1ST_2_CODE_SRC_END_ADDR     }
};
static CONST(Section_RomRamCopyTextType, SECTION_CONST) Section_1stText = {
    SECTION_1ST_COPY_TEXT_NUM,
    &Section_1stTextInfo[0]
};

/******************************************************************************/
/* Ram.const(Before clock up)                                                 */
/******************************************************************************/
static CONST(Section_RomRamCopyDataInfoType, SECTION_CONST) Section_1stConstInfo[] = {
    /* .rosdata */
     { SECTION_RAMCOPY_1ST_1_CONST_DST_ADDR,  SECTION_RAMCOPY_1ST_1_CONST_SRC_ADDR,  SECTION_RAMCOPY_1ST_1_CONST_SRC_END_ADDR  }
    ,{ SECTION_RAMCOPY_1ST_2_CONST_DST_ADDR,  SECTION_RAMCOPY_1ST_2_CONST_SRC_ADDR,  SECTION_RAMCOPY_1ST_2_CONST_SRC_END_ADDR  }
    /* .rodata */
    ,{ SECTION_RAMCOPY_1ST_1_CONST2_DST_ADDR, SECTION_RAMCOPY_1ST_1_CONST2_SRC_ADDR, SECTION_RAMCOPY_1ST_1_CONST2_SRC_END_ADDR }

};
static CONST(Section_RomRamCopyDataType, SECTION_CONST) Section_1stConst = {
    SECTION_1ST_COPY_CONST_NUM,
    &Section_1stConstInfo[0]
};

/******************************************************************************/
/* bss(Before clock up)                                                       */
/******************************************************************************/
static CONST(Section_RomRamCopyBssInfoType, SECTION_CONST) Section_1stBssInfo[] = {
    /* .sbss */
     { SECTION_RAM_1ST_1_B_ADDR,  SECTION_RAM_1ST_1_B_END_ADDR  }
    ,{ SECTION_RAM_1ST_2_B_ADDR,  SECTION_RAM_1ST_2_B_END_ADDR  }
    /* .bss */
    ,{ SECTION_RAM_1ST_1_B2_ADDR, SECTION_RAM_1ST_1_B2_END_ADDR }
};
static CONST(Section_RomRamCopyBssType, SECTION_CONST) Section_1stBss = {
    SECTION_1ST_BSS_NUM,
    &Section_1stBssInfo[0]
};

/******************************************************************************/
/* Ram setup(Before clock up)                                                 */
/******************************************************************************/
CONST(Section_RomRamCopyType, SECTION_CONST) Section_1stInfo = {
    &Section_1stText,
    &Section_1stConst,
    &Section_1stBss
};

/******************************************************************************/
/* Ram.text(After clock up)                                                   */
/******************************************************************************/
static CONST(Section_RomRamCopyTextInfoType, SECTION_CONST) Section_2ndTextInfo[] = {
     { SECTION_RAMCOPY_2ND_FIXED_CODE_DST_ADDR, SECTION_RAMCOPY_2ND_FIXED_CODE_SRC_ADDR, SECTION_RAMCOPY_2ND_FIXED_CODE_SRC_END_ADDR }
    ,{ SECTION_RAMCOPY_2ND_1_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_1_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_1_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_2_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_2_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_2_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_3_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_3_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_3_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_4_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_4_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_4_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_5_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_5_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_5_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_6_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_6_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_6_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_7_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_7_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_7_CODE_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_8_CODE_DST_ADDR,     SECTION_RAMCOPY_2ND_8_CODE_SRC_ADDR,     SECTION_RAMCOPY_2ND_8_CODE_SRC_END_ADDR     }
#if (REPROG_CFG_SBL_TYPE_WITHIN == STD_ON)
    ,{ SECTION_RAMCOPY_2ND_SBL_DST_ADDR,        SECTION_RAMCOPY_2ND_SBL_SRC_ADDR,        SECTION_RAMCOPY_2ND_SBL_SRC_END_ADDR        }
#endif
};
static CONST(Section_RomRamCopyTextType, SECTION_CONST) Section_2ndText = {
    SECTION_2ND_COPY_TEXT_NUM,
    &Section_2ndTextInfo[0]
};

/******************************************************************************/
/* Ram.const(After clock up)                                                  */
/******************************************************************************/
static CONST(Section_RomRamCopyDataInfoType, SECTION_CONST) Section_2ndConstInfo[] = {
    /* .rosdata */
     { SECTION_RAMCOPY_2ND_FIXED_CONST_DST_ADDR, SECTION_RAMCOPY_2ND_FIXED_CONST_SRC_ADDR, SECTION_RAMCOPY_2ND_FIXED_CONST_SRC_END_ADDR }
    ,{ SECTION_RAMCOPY_2ND_1_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_1_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_1_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_2_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_2_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_2_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_3_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_3_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_3_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_4_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_4_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_4_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_5_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_5_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_5_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_6_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_6_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_6_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_7_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_7_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_7_CONST_SRC_END_ADDR     }
    ,{ SECTION_RAMCOPY_2ND_8_CONST_DST_ADDR,     SECTION_RAMCOPY_2ND_8_CONST_SRC_ADDR,     SECTION_RAMCOPY_2ND_8_CONST_SRC_END_ADDR     }
    /* .rodata */
    ,{ SECTION_RAMCOPY_2ND_1_CONST2_DST_ADDR,    SECTION_RAMCOPY_2ND_1_CONST2_SRC_ADDR,    SECTION_RAMCOPY_2ND_1_CONST2_SRC_END_ADDR    }
};
static CONST(Section_RomRamCopyDataType, SECTION_CONST) Section_2ndConst = {
    SECTION_2ND_COPY_CONST_NUM,
    &Section_2ndConstInfo[0]
};

/******************************************************************************/
/* bss(After clock up)                                                        */
/******************************************************************************/
static CONST(Section_RomRamCopyBssInfoType, SECTION_CONST) Section_2ndBssInfo[] = {
    /* .sbss */
     { SECTION_RAM_2ND_FIXED_B_ADDR, SECTION_RAM_2ND_FIXED_B_END_ADDR }
    ,{ SECTION_RAM_2ND_1_B_ADDR,     SECTION_RAM_2ND_1_B_END_ADDR     }
    ,{ SECTION_RAM_2ND_2_B_ADDR,     SECTION_RAM_2ND_2_B_END_ADDR     }
    /* .bss */
    ,{ SECTION_RAM_2ND_1_B2_ADDR,    SECTION_RAM_2ND_1_B2_END_ADDR    }
};
static CONST(Section_RomRamCopyBssType, SECTION_CONST) Section_2ndBss = {
    SECTION_2ND_BSS_NUM,
    &Section_2ndBssInfo[0]
};

/******************************************************************************/
/* Ram setup(After clock up)                                                  */
/******************************************************************************/
CONST(Section_RomRamCopyType, SECTION_CONST) Section_2ndInfo = {
    &Section_2ndText,
    &Section_2ndConst,
    &Section_2ndBss
};

/******************************************************************************/
/* SBL                                                                        */
/******************************************************************************/
static CONST(Section_DlInfoType, SECTION_CONST) Section_DlInfo[] = {
     { SECTION_SBL_DOWNLOAD_ADDR, SECTION_SBL_DOWNLOAD_END_ADDR }
};
CONST(Section_DlType, SECTION_CONST) Section_DlData = {
    SECTION_DL_NUM,
    &Section_DlInfo[0]
};

/******************************************************************************/
/* Unused RAM                                                                 */
/******************************************************************************/
static CONST(Section_UnusedRamInfoType, SECTION_CONST) Section_UnusedRamInfo[] = {
#if (SECTION_UNUSEDRAM_CLEAR == STD_ON)
     { SECTION_UNUSEDRAM_1_ADDR,     SECTION_UNUSEDRAM_1_END_ADDR     }
    ,{ SECTION_UNUSEDRAM_2_ADDR,     SECTION_UNUSEDRAM_2_END_ADDR     }
    ,{ SECTION_UNUSEDRAM_3_ADDR,     SECTION_UNUSEDRAM_3_END_ADDR     }
    ,{ SECTION_UNUSEDRAM_4_ADDR,     SECTION_UNUSEDRAM_4_END_ADDR     }
    ,{ SECTION_UNUSEDRAM_5_ADDR,     SECTION_UNUSEDRAM_5_END_ADDR     }
    ,{ SECTION_UNUSEDRAM_6_ADDR,     SECTION_UNUSEDRAM_6_END_ADDR     }
#else
     { SECTION_UNUSEDRAM_DUMMY_ADDR, SECTION_UNUSEDRAM_DUMMY_END_ADDR }
#endif
};
CONST(Section_UnusedRamType, SECTION_CONST) Section_UnusedRamData = {
    SECTION_UNUSEDRAM_NUM,
    &Section_UnusedRamInfo[0]
};

#define SECTION_STOP_SEC_CST
#include <Section_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/


