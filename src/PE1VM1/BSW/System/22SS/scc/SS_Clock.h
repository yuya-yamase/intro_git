/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_Clock.h
 * [Module]			Clock
 * [Function]		Clock
 * [Notes]			None
 ****************************************************************************/

#ifndef SS_CLOCK_H
#define SS_CLOCK_H

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
#if (SS_USE_LWH == SS_LWH_NONE)
void SS_Clock_up(void);
#else /* SS_USE_LWH == SS_LWH_NONE */
#define SS_Clock_up()
#endif /* SS_USE_LWH == SS_LWH_NONE */

#endif /* SS_CLOCK_H */
