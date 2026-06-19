/**
 ******************************************************************************
 * @file        : inx100_debug.c
 * @author      : Ivan.Estudiez
 * @brief       : 
 * @date        : 18 jun 2026
 * @version     : 0.
 ******************************************************************************
 */

#include <stdio.h>
#include <stdbool.h>
#include "inx100_debug.h"
#include "app.h"
#include "gui_utils.h"
#include "pwrboard.h"
#include "system_cx100.h"
#include "glcd.h"
#include "fonts.h"
#include "ftx100_bitmaps.h"
#include "keyboard.h"

// Private functions
// ----------------------------------------------------------------------------
void inx100DebugScreen_Init(GUI_INX100Debug_t *this);
bool inx100DebugScreen_KeyActions(GUI_INX100Debug_t *this);
void inx100DebugScreen_Draw(GUI_INX100Debug_t *this);

/**
 * -----------------------------------------------------------------------------
 * @brief			INX100 Fertilizer debug screen
 *-----------------------------------------------------------------------------
 * @param info		Pointer to INX100 debug screen structure
 * -----------------------------------------------------------------------------
 */
void GUI_INX100DebugScreen(GUI_INX100Debug_t *this)
{
	// Exit if state is inactive
	if (this->priv.status == GUI_STATUS_DISABLED)
		return;

	// If there was a jump from a previous menu,
	// perform the keyboard reading in the next cycle
	if (this->priv.status == GUI_STATUS_JUMP)
	{
		this->priv.status = GUI_STATUS_ENABLED;
		return;
	}

	// Initialization
	if (this->priv.init == false)
		inx100DebugScreen_Init(this);

	// Process keyboard actions
	if (inx100DebugScreen_KeyActions(this))
		return;

	// Draw the menu on screen
	if (this->priv.redraw)
		inx100DebugScreen_Draw(this);
}

/**
 * ----------------------------------------------------------------------------
 * @brief 				INX100 calibration screen initialization
 * ----------------------------------------------------------------------------
 * @param info			Pointer to INX100Debug type structure
 * ----------------------------------------------------------------------------
 */
void inx100DebugScreen_Init(GUI_INX100Debug_t *this)
{
	this->priv.init = true;
	this->priv.redraw = true;
}

/**
 * ----------------------------------------------------------------------------
 * @brief 				Perform keyboard actions
 * ----------------------------------------------------------------------------
 * @param info			Pointer to INX100Debug type structure
 * @return				False = Continue, True = Exit current control.
 * ----------------------------------------------------------------------------
 */
bool inx100DebugScreen_KeyActions(GUI_INX100Debug_t *this)
{
	// Escape action
	if (KEYBOARD_Event.Esc == 1)
	{
		GUI_TransferControl(&this->priv.status, this->pRet);
		this->priv.redraw = true;
		return true;
	}

	this->priv.redraw = true;
	return false;
}

/**
 * ----------------------------------------------------------------------------
 * @brief 				Draw INX100 Debug screen
 * ----------------------------------------------------------------------------
 * @param info			Pointer to INX100Debug type structure
 * ----------------------------------------------------------------------------
 */
void inx100DebugScreen_Draw(GUI_INX100Debug_t *this)
{
	const uint8_t ROW1_Y = 10;
	const uint8_t ROW2_Y = 28;
	const uint8_t ROW3_Y = 46;

	const uint8_t COL1_X = 62;
	const uint8_t COL2_X = 98;

	char sTxtBox[10];
	uint8_t xPos;

	// Draw Debug Screen
	GLCD_ScreenBitmap(INX100Debug_Screen_128x64);
	SYSTEM_DelayUs(5);

	// Text boxes section
	// ========================================================================

	// Setpoint text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) (APP_RpmSetpoint / 10));
	xPos = COL1_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW1_Y, Font_NumVerdanaBlack, 1, 1);

	// Motor speed text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) (PowerBoard.Freq[0].Rpm / 10));
	xPos = COL2_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW1_Y, Font_NumVerdanaBlack, 1, 1);

	// Error text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) APP_PidMotor.err);
	xPos = COL1_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW2_Y, Font_NumVerdanaBlack, 1, 1);

	// PWM text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) PowerBoard.Out[0].DutyCycle);
	xPos = COL2_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW2_Y, Font_NumVerdanaBlack, 1, 1);

	// Speed text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) APP_Speed);
	GUI_DecimalPoint(sTxtBox, 1);
	xPos = COL1_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW3_Y, Font_NumVerdanaBlack, 1, 1);

	// Temperature text box
	// ------------------------------------------------------------------------
	sprintf(sTxtBox, "%d", (int) PowerBoard.Status.Temp);
	GUI_DecimalPoint(sTxtBox, 1);
	xPos = COL2_X - GLCD_TextWidth(sTxtBox, Font_NumVerdanaBlack, 1);
	GLCD_DrawText(sTxtBox, xPos, ROW3_Y, Font_NumVerdanaBlack, 1, 1);
}
