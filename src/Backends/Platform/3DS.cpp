// Released under the MIT licence.
// See LICENCE.txt for details.

#include "../Misc.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#include <3ds.h>

bool Backend_Init(void (*drag_and_drop_callback)(const char *path), void (*window_focus_callback)(bool focus))
{
	(void)drag_and_drop_callback;
	(void)window_focus_callback;

	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);

	if (R_SUCCEEDED(romfsInit()))
	{
//		osSetSpeedupEnable(true); // Enable New3DS speedup, since this doesn't run very well on Old3DSs yet

		return true;
	}
	else
	{
		Backend_PrintError("Could not initialise romfs");
	}

	return false;
}

void Backend_Deinit(void)
{
	romfsExit();

	gfxExit();
}

void Backend_PostWindowCreation(void)
{
	// Nothing to do here
}

bool Backend_GetPaths(std::string *module_path, std::string *data_path)
{
	// Create the CSE2 folder if it doesn't already exist
	mkdir("sdmc:/3ds", 0777);
	mkdir("sdmc:/3ds/data", 0777);
	mkdir("sdmc:/3ds/data/cse2", 0777);

	// Configuration files and save data goes on the read-write SD card
	*module_path = "sdmc:/3ds/data/cse2";

	// Data goes in the read-only ROMFS
	*data_path = "romfs:";

	return true;
}

void Backend_HideMouse(void)
{
	
}

void Backend_SetWindowIcon(const unsigned char *rgb_pixels, size_t width, size_t height)
{
	(void)rgb_pixels;
	(void)width;
	(void)height;
}

void Backend_SetCursor(const unsigned char *rgba_pixels, size_t width, size_t height)
{
	(void)rgba_pixels;
	(void)width;
	(void)height;
}

void Backend_EnableDragAndDrop(void)
{
	
}

bool Backend_SystemTask(bool active)
{
	(void)active;

	return true;
}

void Backend_GetKeyboardState(bool *keyboard_state)
{
	memset(keyboard_state, 0, sizeof(bool) * BACKEND_KEYBOARD_TOTAL);
}

void Backend_ShowMessageBox(const char *title, const char *message)
{
	Backend_PrintInfo("ShowMessageBox - %s - %s", title, message);
}

ATTRIBUTE_FORMAT_PRINTF(1, 2) void Backend_PrintError(const char *format, ...)
{
	va_list argumentList;
	va_start(argumentList, format);
	fputs("ERROR: ", stderr);
	vfprintf(stderr, format, argumentList);
	fputc('\n', stderr);
	va_end(argumentList);
}

ATTRIBUTE_FORMAT_PRINTF(1, 2) void Backend_PrintInfo(const char *format, ...)
{
	va_list argumentList;
	va_start(argumentList, format);
	fputs("INFO: ", stdout);
	vfprintf(stdout, format, argumentList);
	fputc('\n', stdout);
	va_end(argumentList);
}

unsigned long Backend_GetTicks(void)
{
	return svcGetSystemTick() / CPU_TICKS_PER_MSEC;
}

void Backend_Delay(unsigned int ticks)
{
	// svcSleepThread measures in nanoseconds
	svcSleepThread(ticks * 1000000);
}

void Backend_GetDisplayMode(Backend_DisplayMode *display_mode)
{
	display_mode->width = 400;
	display_mode->height = 240;
	display_mode->refresh_rate = 60;
}
