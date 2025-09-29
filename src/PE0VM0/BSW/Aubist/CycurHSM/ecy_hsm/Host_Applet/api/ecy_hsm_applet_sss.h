/**
 * @cond SSS_DOXYGEN_ENABLED
 * @file
 ***********************************************************************************************
 * @brief SSS applet implementation
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2021, all rights reserved
 **********************************************************************************************/

/* *** prologue  ******************************************************************************/

#ifndef ECY_HSM_APPLET_SSS_H
# define ECY_HSM_APPLET_SSS_H

/**
 * @addtogroup SSS_IMPL Secure Space Scripting applet implementation
 * @{
 */

/* *** includes *******************************************************************************/

# include "ecy_hsm_applet.h"
# include "ecy_hsm_csai_sss.h"

/* *** defines ********************************************************************************/

/* *** type declarations **********************************************************************/

/**
 * @brief Possible states of the SSS applet
 */
typedef enum ecy_hsm_Applet_Sss_StateTag
{
    ecy_hsm_APPLET_SSS_FUNC_INIT_SCRIPT,       /**< Initialize a script for execution */
    ecy_hsm_APPLET_SSS_FUNC_SET_SCRIPT_INPUTS, /**< Pass script inputs from the host */
    ecy_hsm_APPLET_SSS_FUNC_RUN_SCRIPT,        /**< Run an initialized script */

    /* This needs to be the final entry */
    ecy_hsm_APPLET_SSS_NUMSTATES /**< Number of states */
} ecy_hsm_Applet_Sss_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by ecy_hsm_APPLET_SSS_FUNC_INIT_SCRIPT
 */
# define APPLET_SSS_FUNC_INIT_SCRIPT       ecy_hsm_APPLET_SSS_FUNC_INIT_SCRIPT
/**
 * @deprecated by ecy_hsm_APPLET_SSS_FUNC_SET_SCRIPT_INPUTS
 */
# define APPLET_SSS_FUNC_SET_SCRIPT_INPUTS ecy_hsm_APPLET_SSS_FUNC_SET_SCRIPT_INPUTS
/**
 * @deprecated by ecy_hsm_APPLET_SSS_FUNC_RUN_SCRIPT
 */
# define APPLET_SSS_FUNC_RUN_SCRIPT        ecy_hsm_APPLET_SSS_FUNC_RUN_SCRIPT
/**
 * @deprecated by ecy_hsm_APPLET_SSS_NUMSTATES
 */
# define APPLET_SSS_NUMSTATES              ecy_hsm_APPLET_SSS_NUMSTATES
/**
 * @brief Parameters for ecy_hsm_Csai_Sss_ScriptInit
 */
typedef struct ecy_hsm_Applet_Sss_ScriptInit_ParamTag
{
    uint32 scriptId;  /**< Script identifiers */
    void*  pParam;    /**< void Pointer to a type defined parameter */
    uint32 paramSize; /**< size of the parameters from the void pointer */
} ecy_hsm_Applet_Sss_ScriptInit_ParamT;

/**
 * @brief Parameters for ecy_hsm_Csai_Sss_SetScriptInputs
 */
typedef struct ecy_hsm_Applet_Sss_ScriptInput_ParamTag
{
    uint32                               scriptInputsCount; /**< Script input count */
    const ecy_hsm_Csai_Sss_ScriptInputT* pScriptInputs;     /**< Script inputs */
    void*                                pParam;            /**< void Pointer to a type defined parameter */
    uint32                               paramSize;         /**< size of the parameters from the void pointer */
} ecy_hsm_Applet_Sss_ScriptInput_ParamT;

/**
 * @brief Parameters for ecy_hsm_Csai_Sss_GetStatus and ecy_hsm_Csai_Sss_RunScript
 */
typedef struct ecy_hsm_Applet_Sss_RunScript_ParamTag
{
    ecy_hsm_Csai_Sss_StatusInfoT* pStatusInfo; /**< Pointer to status/error info structure */
    void*                         pParam;      /**< void Pointer to a type defined parameter */
    uint32                        paramSize;   /**< size of the parameters from the void pointer */
} ecy_hsm_Applet_Sss_RunScript_ParamT;

/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by ecy_hsm_Applet_Sss_RunScript_ParamTag
 */
# define Applet_Sss_RunScript_ParamTag   ecy_hsm_Applet_Sss_RunScript_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_Sss_RunScript_ParamT
 */
# define Applet_Sss_RunScript_ParamT     ecy_hsm_Applet_Sss_RunScript_ParamT
/**
 * @deprecated by ecy_hsm_Applet_Sss_ScriptInput_ParamTag
 */
# define Applet_Sss_ScriptInput_ParamTag ecy_hsm_Applet_Sss_ScriptInput_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_Sss_ScriptInput_ParamT
 */
# define Applet_Sss_ScriptInput_ParamT   ecy_hsm_Applet_Sss_ScriptInput_ParamT
/**
 * @deprecated by ecy_hsm_Applet_Sss_ScriptInit_ParamTag
 */
# define Applet_Sss_ScriptInit_ParamTag  ecy_hsm_Applet_Sss_ScriptInit_ParamTag
/**
 * @deprecated by ecy_hsm_Applet_Sss_ScriptInit_ParamT
 */
# define Applet_Sss_ScriptInit_ParamT    ecy_hsm_Applet_Sss_ScriptInit_ParamT
/**
 * @deprecated by ecy_hsm_Applet_Sss_StateTag
 */
# define Applet_Sss_StateTag             ecy_hsm_Applet_Sss_StateTag
/**
 * @deprecated by ecy_hsm_Applet_Sss_StateT
 */
# define Applet_Sss_StateT               ecy_hsm_Applet_Sss_StateT

/* *** extern declarations ********************************************************************/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_START_SEC_CONST_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/**
 * @brief SSS applet control structure
 */
extern const Applet_ts Applet_Sss_Hsm;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
# define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
# include "ecy_hsm_MemMap.h"

/**
 * @}
 */
#endif /* ECY_HSM_APPLET_SSS_H */

/**
 * @endcond
 */
