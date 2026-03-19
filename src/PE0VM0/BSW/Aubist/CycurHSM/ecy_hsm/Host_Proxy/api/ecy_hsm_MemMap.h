/**
 * @file
 ***********************************************************************************************
 * @brief AUTOSAR Memory Mapping for ecy
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

/* PRQA S 0883 EOF */ /* <Deviation: dir_4.10_0883 */

#if defined(ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section bss = ".hsm_shared.bss"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section bss = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section bss = ".hsm_shared.bss"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section bss = ".hsm_shared.bss" data = ".hsm_shared.data"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_8

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section bss = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_8

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section  bss = ".hsm_shared.bss"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
       #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_16

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section bss = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_16

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_32)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section bss = ".hsm_shared.bss"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
       #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_CLEARED_32

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_32)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section bss = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_CLEARED_32

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section data = ".hsm_shared.data"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.data"RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_8

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section data = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_8

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section data = ".hsm_shared.data"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.data" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_16

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section data = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_16

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section data = ".hsm_shared.data"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.data" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_32

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section data = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_32

#elif defined(ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section data = ".hsm_shared.data"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data=".hsm_shared.data" bss=".hsm_shared.bss"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all "hsm_shared"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".hsm_shared.data" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section data = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section all restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMSHARED_INIT_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss "hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".host_storage_cache.data" ".host_storage_cache.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
            #pragma clang section data = ".hsm_shared.hwcsp_keystore_table"
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section ".hsm_shared.hwcsp_keystore_table"
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data= ".hsm_shared.hwcsp_keystore_table"
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        #if defined(__clang__) /* clang based HT toolchain */
           #pragma clang section data = ""
        #else /* GCC based HT toolchain */
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
            #pragma section
        #endif /* __clang__ */
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HWCSP_KEYSTORE_TABLE_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss "hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".host_storage_cache.data" ".host_storage_cache.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_8

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_8)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_8

#elif defined(ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs startdata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = ".hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss "hsm_shared.host_storage_cache"
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA ".host_storage_cache.data" ".host_storage_cache.bss" RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_HSMHOSTSTORAGECACHE_16

#elif defined(ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_16)
    #if defined(__CANTATA_TESTING__)
        /* no section used for unit testing */
    #elif(COMPILER == COMPILER_HT) || (COMPILER == COMPILER_CLANG)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section
    #elif(COMPILER == COMPILER_GHS)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs enddata
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma ghs section data = default bss = default
    #elif(COMPILER == COMPILER_TASKING)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section farbss restore
    #elif(COMPILER == COMPILER_WINDRIVER_DIAB)
        /* PRQA S 3116 1 */ /* <Justification for directive_1.1_3116: The pragma pattern is defined by compiler */
        #pragma section DATA RW
    #else
        #error "ecy_hsm_MemMap.h: unknown COMPILER define"
    #endif
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_HSMHOSTSTORAGECACHE_16

#elif defined(ECY_HSM_START_SEC_VAR_INIT_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_INIT_8

#elif defined(ECY_HSM_STOP_SEC_VAR_INIT_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_INIT_8

#elif defined(ECY_HSM_START_SEC_VAR_INIT_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_INIT_16

#elif defined(ECY_HSM_STOP_SEC_VAR_INIT_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_INIT_16

#elif defined(ECY_HSM_START_SEC_VAR_INIT_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_INIT_32

#elif defined(ECY_HSM_STOP_SEC_VAR_INIT_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_INIT_32

#elif defined(ECY_HSM_START_SEC_VAR_INIT_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_INIT_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_INIT_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_VAR_CLEARED_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_CLEARED_8

#elif defined(ECY_HSM_STOP_SEC_VAR_CLEARED_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_CLEARED_8

#elif defined(ECY_HSM_START_SEC_VAR_CLEARED_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_CLEARED_16

#elif defined(ECY_HSM_STOP_SEC_VAR_CLEARED_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_CLEARED_16

#elif defined(ECY_HSM_START_SEC_VAR_CLEARED_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_CLEARED_32

#elif defined(ECY_HSM_STOP_SEC_VAR_CLEARED_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_CLEARED_32

#elif defined(ECY_HSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_CLEARED_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_CONST_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_CONST_8

#elif defined(ECY_HSM_STOP_SEC_CONST_8)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_CONST_8

#elif defined(ECY_HSM_START_SEC_CONST_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_CONST_16

#elif defined(ECY_HSM_STOP_SEC_CONST_16)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_CONST_16

#elif defined(ECY_HSM_START_SEC_CONST_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_CONST_32

#elif defined(ECY_HSM_STOP_SEC_CONST_32)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_CONST_32

#elif defined(ECY_HSM_START_SEC_CONST_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_CONST_UNSPECIFIED

#elif defined(ECY_HSM_STOP_SEC_CONST_UNSPECIFIED)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_CONST_UNSPECIFIED

#elif defined(ECY_HSM_START_SEC_CODE)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_CODE

#elif defined(ECY_HSM_STOP_SEC_CODE)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_CODE

#elif defined(ECY_HSM_START_SEC_VAR_PTR)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_START_SEC_VAR_PTR

#elif defined(ECY_HSM_STOP_SEC_VAR_PTR)
    /* PRQA S 0841 2 */ /* <Deviation: using #undef is intended here */
    /*lint -e(960) *//*Deviation: using #undef is intended here */
    #undef ECY_HSM_STOP_SEC_VAR_PTR

#else
    #error "ecy_hsm_MemMap.h: unknown MemMap define"
#endif
