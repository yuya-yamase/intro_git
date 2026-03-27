/**
 * @file
 ***********************************************************************************************
 * @brief CSAI certificate handling
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2014, all rights reserved
 **********************************************************************************************/

#ifndef APPLET_CERT_H
#define APPLET_CERT_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "ecy_hsm_applet.h"

/**
 * @addtogroup APPLET_IMPL
 * @{
 */
#define MAX_LEN_AUTHBITS 16U

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/
/**
 * @brief Possible states for certificate applet
 *
 * @details
 * @section APPLET_CERT Certificate handling applet
 *
 *  * @startuml
 * state "ecy_hsm_APPLET_CERT_STATE_INJECTCERT_E" as InjectCert             : Inject Certificate and get Public Key handle
 * state "ecy_hsm_APPLET_CERT_STATE_RELEASECERT_E" as ReleaseCert           : Release injected Certificate or Public Key
 * state "ecy_hsm_APPLET_CERT_STATE_INJECTCERTGENERIC_E" as InjectCertGen   : Inject Certificate and get Certificate Handle
 * state "ecy_hsm_APPLET_CERT_STATE_GETPUBKEYFROMCERT_E" as GetPubKey       : Get Public Key from injected cert
 *
 * [*] --> InjectCert
 * InjectCert --> [*]
 *
 * [*] --> ReleaseCert
 * ReleaseCert --> [*]
 *
 * [*] --> InjectCertGen
 * InjectCertGen --> [*]
  *
 * [*] --> GetPubKey
 * GetPubKey --> [*]
 *
 * @enduml
 *
 */
typedef enum ecy_hsm_Applet_Cert_StateT
{
    ecy_hsm_APPLET_CERT_STATE_INJECTCERT_E,             /**< Certificate injection */
    ecy_hsm_APPLET_CERT_STATE_RELEASECERT_E,            /**< Certificate release */
    ecy_hsm_APPLET_CERT_STATE_INJECTCERTGENERIC_E,      /**< Certificate injection with Root handling */
    ecy_hsm_APPLET_CERT_STATE_GETPUBKEYFROMCERT_E,      /**< Certificate get public key from injected certificate */
    ecy_hsm_APPLET_CERT_STATE_GENERICPARSER_E,          /**< Parse for specific tag tree in certificate */
    ecy_hsm_APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E, /**< Installation of self-signed root certificate */
    /* This needs to be the final entry */
    ecy_hsm_APPLET_CERT_NUMSTATES_E                     /**< Number of states */
} ecy_hsm_Applet_Cert_StateT;

/* *********** Deprecated enum definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_INJECTCERT_E
 */
#define APPLET_CERT_STATE_INJECTCERT_E ecy_hsm_APPLET_CERT_STATE_INJECTCERT_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_RELEASECERT_E
 */
#define APPLET_CERT_STATE_RELEASECERT_E ecy_hsm_APPLET_CERT_STATE_RELEASECERT_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_INJECTCERTGENERIC_E
 */
#define APPLET_CERT_STATE_INJECTCERTGENERIC_E ecy_hsm_APPLET_CERT_STATE_INJECTCERTGENERIC_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_GETPUBKEYFROMCERT_E
 */
#define APPLET_CERT_STATE_GETPUBKEYFROMCERT_E ecy_hsm_APPLET_CERT_STATE_GETPUBKEYFROMCERT_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_GENERICPARSER_E
 */
#define APPLET_CERT_STATE_GENERICPARSER_E ecy_hsm_APPLET_CERT_STATE_GENERICPARSER_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E
 */
#define APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E ecy_hsm_APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E
/**
 * @deprecated by @ref ecy_hsm_APPLET_CERT_STATE_INSTALLROOTCERTIFICATE_E
 */
#define APPLET_CERT_NUMSTATES_E ecy_hsm_APPLET_CERT_NUMSTATES_E
/* *********** Deprecated type definitions ***************/
/**
 * @deprecated by @ref ecy_hsm_Applet_Cert_StateT
 */
#define Applet_Cert_StateT ecy_hsm_Applet_Cert_StateT
/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_START_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/**
 * @brief CERT applet control structures
 */
extern const Applet_ts Applet_Cert_HSM;

/* PRQA S 5087 2 */ /* <Deviation: Include is used to map variables to special memory sections */
#define ECY_HSM_STOP_SEC_CONST_UNSPECIFIED
#include "ecy_hsm_MemMap.h"

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

/**
 * @}
 */
#endif // _APPLET_CHKSUM_H_
