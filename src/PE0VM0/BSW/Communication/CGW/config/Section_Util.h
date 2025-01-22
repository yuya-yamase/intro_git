/****************************************************************************/
/* Copyright DENSO Corporation. All rights reserved                         */
/****************************************************************************/
/* Object name: Section_Util.h                                             */
/****************************************************************************/
#ifndef SECTION_UTIL_H
#define SECTION_UTIL_H

#define GW_SECTION_PRAGMA(x)  _Pragma(#x)

/* 後述の通り、コンパイラ共通で使用可能なセクションタイプは bss/data/rodata/textの4つのみ */
/* sbssやzbss等はArmで使用できないため原則使用しないこと                                  */
#if defined __ghs__
    /* multiで有効なセクションタイプ(sec)は、bss/data/rodata/text/sbss/sdata/rosdata/zbss/zdata/rozdata */
    #define PRAGMA_SECTION(sec, name)      GW_SECTION_PRAGMA( ghs section sec = name )
    #define PRAGMA_SECTION_DEFAULT(sec)    GW_SECTION_PRAGMA( ghs section sec = default )

    /* GHSではpragmaでセクション配置可能なため、何もしない */
    #define ATTRIBUTE_SECTION(name)
#elif defined __arm__
    /* arm compilerで有効なセクションタイプ(sec)は、bss/data/rodata/textの4つのみ */
    #define PRAGMA_SECTION(sec, name)      GW_SECTION_PRAGMA( clang section sec = name )
    #define PRAGMA_SECTION_DEFAULT(sec)    GW_SECTION_PRAGMA( clang section sec = "" )

    /* ARMではpragmaでセクション配置できないケースがあるため、attributeを使用する */
    #define ATTRIBUTE_SECTION(name) __attribute__ ( (section ((name)) ) )
#else
    #define PRAGMA_SECTION(sec, name)
    #define PRAGMA_SECTION_DEFAULT(sec)

    #define ATTRIBUTE_SECTION(name)
#endif

#endif
