#include "pch.h"
#include "hook.h"
#include "variables.h"
#include "menu.h"

//#define DEBUG

void start() {
#ifdef DEBUG
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Kyle's HaloCE hacks!");
#endif

	globals::init();
	hook::init();
	hack_menu.init();

	while (!glfwWindowShouldClose(hack_menu.get_window()))
		hack_menu.tick();

	hook::shutdown(); //unattaches functions, imgui, and glfw stuff
	globals::shutdown(); //cleans drawing hook

#ifdef DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();
#endif

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL);
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {}
	return TRUE;
}
