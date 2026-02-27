/**
 * @file
 ***********************************************************************************************
 * @brief Protections applet interface
 *
 ***********************************************************************************************
 * @copyright                                 Copyright (c) ETAS GmbH 2014, all rights reserved.
 **********************************************************************************************/

#ifndef APPLET_PROTECTIONS_H
#define APPLET_PROTECTIONS_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"
#include "ecy_hsm_csai_protections.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/

/**
 * @brief Possible states for the Protections applet
 *
 * @details
 * @section APPLET_PROTECTIONS Protections applet
 *
 * @subsection APPLET_PROTECTIONS_STATES Applet states
 *
 * @startuml
 * state "ecy_hsm_APPLET_SECCRITFUNC_STATE_DEACTIVATE_E" as SecCritFunc     : Disable the security critical features
 * state "ecy_hsm_APPLET_PROT_STATE_FLASHUNLOCK_E" as FlashUnlock           : Unlock Flash protections
 * state "ecy_hsm_APPLET_PROT_STATE_FLASHRESUME_E" as FlashResume           : Resume locking of Flash protections
 *
 * [*] --> SecCritFunc
 * SecCritFunc --> [*]
 *
 * [*] --> FlashUnlock
 * FlashUnlock --> [*]
 *
 * [*] --> FlashResume
 * FlashResume --> [*]
 *
 * @enduml
 *
 */
typedef enum ecy_hsm_Applet_Protections_StateT
{
    ecy_hsm_APPLET_SECCRITFUNC_STATE_DEACTIVATE_E, /**< Protecting the security critical function from misuse */
    ecy_hsm_APPLET_PROT_STATE_FLASHUNLOCK_E,       /**< Unlock Flash protections */
    ecy_hsm_APPLET_PROT_STATE_FLASHRESUME_E,       /**< Resume Flash protections */
    ecy_hsm_APPLET_PROT_STATE_SETPASSWORDS_E,      /**< Inject protection passwords */
    ecy_hsm_APPLET_PROT_STATE_GENERICUNLOCK_E,     /**< Generic protection unlock function */
    ecy_hsm_APPLET_PROT_STATE_RESUMEPROTECTION_E,  /**< Resuming protections by resetting the unlock operations */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_PROTECTIONS_NUMSTATES_E         /**< Number of states */
} ecy_hsm_Applet_Protections_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SECCRITFUNC_STATE_DEACTIVATE_E
 */
#define APPLET_SECCRITFUNC_STATE_DEACTIVATE_E ecy_hsm_APPLET_SECCRITFUNC_STATE_DEACTIVATE_E
/**
 * @deprecated by ecy_hsm_APPLET_PROT_STATE_FLASHUNLOCK_E
 */
#define APPLET_PROT_STATE_FLASHUNLOCK_E ecy_hsm_APPLET_PROT_STATE_FLASHUNLOCK_E
/**
 * @deprecated by ecy_hsm_APPLET_PROT_STATE_FLASHRESUME_E
 */
#define APPLET_PROT_STATE_FLASHRESUME_E ecy_hsm_APPLET_PROT_STATE_FLASHRESUME_E
/**
 * @deprecated by ecy_hsm_APPLET_PROT_STATE_SETPASSWORDS_E
 */
#define APPLET_PROT_STATE_SETPASSWORDS_E ecy_hsm_APPLET_PROT_STATE_SETPASSWORDS_E
/**
 * @deprecated by ecy_hsm_APPLET_PROT_STATE_GENERICUNLOCK_E
 */
#define APPLET_PROT_STATE_GENERICUNLOCK_E ecy_hsm_APPLET_PROT_STATE_GENERICUNLOCK_E
/**
 * @deprecated by ecy_hsm_APPLET_PROT_STATE_RESUMEPROTECTION_E
 */
#define APPLET_PROT_STATE_RESUMEPROTECTION_E ecy_hsm_APPLET_PROT_STATE_RESUMEPROTECTION_E
/**
 * @deprecated by ecy_hsm_APPLET_PROTECTIONS_NUMSTATES_E
 */
#define APPLET_PROTECTIONS_NUMSTATES_E ecy_hsm_APPLET_PROTECTIONS_NUMSTATES_E

/**
 * Applet parameter data for protection functions
 */
typedef struct ecy_hsm_ProtParamT {
    ecy_hsm_Csai_ProtSecLevelT secLevel;            /**< Security level of disabled functions   */
    uint32                     memRangeAddStart;    /**< start address of memory area           */
    uint32                     memRangeNumBytes;    /**< length in bytes of the memory area     */
} ecy_hsm_ProtParamT;

/**
 * Applet parameter data for set password functions
 */
typedef struct ecy_hsm_ProtSetPasswordParamT {
    ecy_hsm_Csai_ProtPasswordT* pList;          /**< list of password entries           */
    uint8                       numListEntries; /**< num of password entries            */
} ecy_hsm_ProtSetPasswordParamT;

/** Applet parameter data for generic unlock functions */
typedef struct ecy_hsm_ProtUnlockParamT
{
    ecy_hsm_Csai_ProtUseCaseIdT useCaseId;       /**< Specifies the type of protection that shall be unlocked */
    void*                       pUseCaseIdParam; /**< Pointer to parameters that are needed for unlocking purposes */
} ecy_hsm_ProtUnlockParamT;

/** Applet parameter for protection resume function */
typedef struct ecy_hsm_ProtResumeParamT
{
    ecy_hsm_Csai_ProtResumeProtIdT resumeProtId;       /**< Specifies the type of resumption */
    void*                          pResumeProtIdParam; /**< Pointer to parameters that are needed for resumption purposes */
} ecy_hsm_ProtResumeParamT;

/**
 * Parameter union type for protection applet
 */
/* PRQA S 0750 2 */ /* <Deviation: definition of union is appropriate here */
typedef union ecy_hsm_Applet_ProtectionParamTag
{
    ecy_hsm_ProtParamT            stProtParam;       /**< Parameters for protection functions */
    ecy_hsm_ProtSetPasswordParamT stProtSetPassword; /**< Parameters for setting the passwords */
    ecy_hsm_ProtUnlockParamT      stProtUnlockParam; /**< Parameters for protection unlock functions */
    ecy_hsm_ProtResumeParamT      stProtResumeParam; /**< Parameters for protection resumption */
} ecy_hsm_Applet_ProtectionParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_Protections_StateT
 */
#define Applet_Protections_StateT ecy_hsm_Applet_Protections_StateT
/**
 * @deprecated by ecy_hsm_ProtParamT
 */
#define HSM_ProtParamT ecy_hsm_ProtParamT
/**
 * @deprecated by ecy_hsm_ProtSetPasswordParamT
 */
#define HSM_ProtSetPasswordParamT ecy_hsm_ProtSetPasswordParamT
/**
 * @deprecated by ecy_hsm_ProtUnlockParamT
 */
#define HSM_ProtUnlockParamT ecy_hsm_ProtUnlockParamT
/**
 * @deprecated by ecy_hsm_ProtResumeParamT
 */
#define HSM_ProtResumeParamT ecy_hsm_ProtResumeParamT
/**
 * @deprecated by ecy_hsm_Applet_ProtectionParamTag
 */
#define Applet_ProtectionParamTag ecy_hsm_Applet_ProtectionParamTag
/**
 * @deprecated by ecy_hsm_Applet_ProtectionParamT
 */
#define Applet_ProtectionParamT ecy_hsm_Applet_ProtectionParamT
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief Protections applet control structure
 */
extern const Applet_ts Applet_Protections_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif // APPLET_PROTECTIONS_H
