#include "pch.h"
#include "hook.h"
#include "variables.h"

void start() {
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Kyle's HaloCE hacks!");

	globals::init();
	

	while (!GetAsyncKeyState(VK_END))
		loop();
		//look into way to split loop() into another thread
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));

	fclose((FILE*)stdin);
	fclose((FILE*)stdout);
	FreeConsole();

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
