/**
 * @file
 ***********************************************************************************************
 * @brief Public timing diagnostic function header
 * @details Public header for the timing diagnostic functions. Will deactivate timing diagnostics
 * for customer builds or if it is disabled.
 *
 ***********************************************************************************************
 * @copyright                      Copyright (c) ETAS GmbH 2019, all rights reserved
 **********************************************************************************************/

#ifndef ECY_HSM_TIMING_DIAGNOSTICS_H
#define ECY_HSM_TIMING_DIAGNOSTICS_H

#if defined(GUAM)

#include "timing_diagnostics.h"

#else

/* Dummy definitions for all compatibility */
#define ecy_hsm_ClearDiagnosticValues()
#define ecy_hsm_AddDiagnosticValue(_tag, _value)
#define ecy_hsm_AddDiagnosticStopwatch(_tag)
#define ecy_hsm_AddStopwatch(_class, _tag)
#define ecy_hsm_ListDiagnosticValues()

#endif


#endif /* ECY_HSM_TIMING_DIAGNOSTICS_H */
