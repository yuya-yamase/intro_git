/**
 * @file
 ***********************************************************************************************
 * @brief File shall automatically generate the COMPILER macro to be used in customer
 *        environment.
 *
 ***********************************************************************************************

 * @copyright                                 Copyright (c) ETAS GmbH 2023, all rights reserved.

 ***********************************************************************************************/

#ifndef ECY_HSM_VMS_COMPILER_H
#define ECY_HSM_VMS_COMPILER_H

#if !defined(GUAM)
    /* List of supported compilers */
    #define COMPILER_GHS               1
    #define COMPILER_HT                2
    #define COMPILER_RENESAS           3
    #define COMPILER_TASKING           4
    #define COMPILER_WINDRIVER_DIAB    5
    #define COMPILER_CLANG             6

    /* compiler is automatically set from chosen target */
    #if !defined(COMPILER)
        #define COMPILER COMPILER_GHS
    #endif // !defined(COMPILER)
#endif // !defined(GUAM)

#endif // ECY_HSM_VMS_COMPILER_H
