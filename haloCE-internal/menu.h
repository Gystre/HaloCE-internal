#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class menu {
public:
	static void init(HWND window, IDirect3DDevice9* pDevice);
	static void shutdown();
	static void tick();
	static void checkInputs();
};