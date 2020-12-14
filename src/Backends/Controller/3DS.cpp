// Released under the MIT licence.
// See LICENCE.txt for details.

#include "../Controller.h"

#include <string.h>

#include <3ds.h>

bool ControllerBackend_Init(void)
{
	return true;
}

void ControllerBackend_Deinit(void)
{
	
}

bool ControllerBackend_GetJoystickStatus(bool **buttons, unsigned int *button_count, short **axes, unsigned int *axis_count)
{
	static bool button_buffer[22];

	*buttons = button_buffer;
	*axes = NULL;

	*button_count = sizeof(button_buffer) / sizeof(button_buffer[0]);
	*axis_count = 0;

	// Read controller
	hidScanInput();

	u32 hid_buttons = hidKeysHeld();

	// Handle button inputs
	button_buffer[0] = hid_buttons & KEY_Y;          // Shoot
	button_buffer[1] = hid_buttons & KEY_B;          // Jump
	button_buffer[2] = hid_buttons & KEY_X;          // Map
	button_buffer[3] = hid_buttons & KEY_L;          // Weapon left
	button_buffer[4] = hid_buttons & KEY_R;          // Weapon right
	button_buffer[5] = hid_buttons & KEY_A;          // Inventory
	button_buffer[6] = hid_buttons & KEY_START;      // Pause
	button_buffer[7] = hid_buttons & KEY_CPAD_UP;    // Up
	button_buffer[8] = hid_buttons & KEY_CPAD_DOWN;  // Down
	button_buffer[9] = hid_buttons & KEY_CPAD_LEFT;  // Left
	button_buffer[10] = hid_buttons & KEY_CPAD_RIGHT;// Right
	button_buffer[11] = hid_buttons & KEY_ZL;
	button_buffer[12] = hid_buttons & KEY_ZR;
	button_buffer[13] = hid_buttons & KEY_SELECT;
	button_buffer[14] = hid_buttons & KEY_DLEFT;
	button_buffer[15] = hid_buttons & KEY_DRIGHT;
	button_buffer[16] = hid_buttons & KEY_DUP;
	button_buffer[17] = hid_buttons & KEY_DDOWN;
	button_buffer[18] = hid_buttons & KEY_CSTICK_LEFT;
	button_buffer[19] = hid_buttons & KEY_CSTICK_RIGHT;
	button_buffer[20] = hid_buttons & KEY_CSTICK_UP;
	button_buffer[21] = hid_buttons & KEY_CSTICK_DOWN;

	return true;
}

const char* ControllerBackend_GetButtonName(unsigned int button_id)
{
	const char *button_names[22] = {
		"Y",
		"B",
		"X",
		"L",
		"R",
		"A",
		"Start",
		"Circle Pad Up",
		"Circle Pad Down",
		"Circle Pad Left",
		"Circle Pad Right",
		"ZL",
		"ZR",
		"Select",
		"D-Pad Left",
		"D-Pad Right",
		"D-Pad Up",
		"D-Pad Down",
		"C-Stick Left",
		"C-Stick Right",
		"C-Stick Up",
		"C-Stick Down"
	};

	if (button_id >= sizeof(button_names) / sizeof(button_names[0]))
		return "Unknown";

	return button_names[button_id];
}
