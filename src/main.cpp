#include "gui.h"
#include <thread>

//Software basics
#include "status.h"
#include "globals.h"

// Cheat tools
#include "tools/vector.h"
#include "tools/memory.h"

//Offsets
#include "tools/csgo_offsets.h"

// Cheat Library
#include "Aimbot/aimbot.h"

#include <iostream>

INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	
	gui::CreateHOverlay("test", "test");

	//Revoir la boucle avec les threads etc...
	while (status::running) {
		// GUI Render
		gui::BeginRender();


		// Check if memory has been defined (Game started)
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (status::aimbotEnabled) {
			aimbot::aimbot();
		}

		

		// What should we render
		gui::Render();
		gui::EndRender();
	}

	// Terminate thread
	std::terminate();

	//Destroy display components
	gui::DestroyHLayout();
	global::memory.~Memory();
	
	//End
	return 0;
}