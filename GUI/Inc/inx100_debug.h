/**
 ******************************************************************************
 * @file        : inx100_debug.h
 * @author      : Ivan.Estudiez
 * @brief       : 
 * @date        : 18 jun 2026
 * @version     : 0.
 ******************************************************************************
 */
#ifndef INC_INX100_DEBUG_H_
#define INC_INX100_DEBUG_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * ----------------------------------------------------------------------------
 * @brief  Debug Screen private settings
 * ----------------------------------------------------------------------------
 */
typedef struct INX100DebugPrivate_t
{
	uint8_t status;
	bool redraw;
	bool init;
} INX100DebugPrivate_t;

typedef struct GUI_INX100Debug_t
{
	INX100DebugPrivate_t priv;
	void *pRet;
} GUI_INX100Debug_t;

// Public functions
// ----------------------------------------------------------------------------
void GUI_INX100DebugScreen(GUI_INX100Debug_t *this);

#endif /* INC_INX100_DEBUG_H_ */
