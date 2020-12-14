// THIS IS DECOMPILED PROPRIETARY CODE - USE AT YOUR OWN RISK.
//
// The original code belongs to Daisuke "Pixel" Amaya.
//
// Modifications and custom code are under the MIT licence.
// See LICENCE.txt for details.

#pragma once

#include "WindowsWrapper.h"

struct DIRECTINPUTSTATUS
{
	BOOL bButton[128];	// The original `Input.cpp` assumed there were 32 buttons (because of DirectInput's `DIJOYSTATE` struct)
};

void ReleaseDirectInput(void);
BOOL InitDirectInput(void);
BOOL GetJoystickStatus(DIRECTINPUTSTATUS *status);
BOOL ResetJoystickStatus(void);
