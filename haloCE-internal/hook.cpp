#include "pch.h"

#include "hook.h"
#include "constants.h"
#include "variables.h"
#include "aimbot.h"
#include "esp.h"
#include "drawing.h"
#include <detours.h>

D3D9EndScene_t originalD3D9EndScene;
D3D9BeginScene_t originalD3D9BeginScene;
D3D9DrawIndexedPrimitive_t originalD3D9DrawIndexedPrimitive;

//should move these 3 functions somewhere else
void detours_error(LONG detourResult) {
	if (detourResult != NO_ERROR) {
		throw;
	}
}

void AttachFunc(PVOID* originalFunc, PVOID replacementFunc) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	detours_error(DetourAttach(originalFunc, replacementFunc));
	detours_error(DetourTransactionCommit());
}

void DetachFunc(PVOID* originalFunc, PVOID replacementFunc) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(originalFunc, replacementFunc);
	DetourTransactionCommit();
}

//parameteres are wrong, look at more examples
HRESULT __stdcall hkD3D9DrawIndexedPrimitive(D3DPRIMITIVETYPE device, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount) {


	return originalD3D9DrawIndexedPrimitive(device, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
}

HRESULT __stdcall hkD3D9BeginScene(IDirect3DDevice9* pDevice) {

	return originalD3D9BeginScene(pDevice);
}

static bool is_down = false;
static bool is_clicked = false;
static engine_snapshot snapshot;

HRESULT __stdcall hkD3D9EndScene(IDirect3DDevice9* pDevice) {
	globals::engine->get_snapshot(snapshot);
	snapshot.filter_enemies();

	botaim.update(snapshot);
	pse.update(snapshot);

	if (GetAsyncKeyState(VK_F1)) {
		for (GameObject* entity : snapshot.gameObjects) {
			entity->position = snapshot.get_player()->position;
		}
	}

	if (GetAsyncKeyState(VK_F2)) {
		vec3_t look = *reinterpret_cast<vec3_t*>(addr::CAMERA_LOOK_VECTOR);
		snapshot.get_player()->position += look * 1.01;
	}

	if (GetAsyncKeyState(VK_LMENU))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GetAsyncKeyState(VK_LMENU) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (is_clicked)
	{
		menu::aim_enabled = !menu::aim_enabled;
	}

	return originalD3D9EndScene(pDevice);
}

void hook::init() {
	//get d3d9 handle
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow();
	d3dpp.Windowed = TRUE;

	//create dummy d3d9 device
	IDirect3DDevice9* dummyD3D9Device = nullptr;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &dummyD3D9Device);
	
	void** d3d9VTable = *reinterpret_cast<void***>(dummyD3D9Device);

	originalD3D9BeginScene = (D3D9BeginScene_t)(d3d9VTable[41]);
	AttachFunc(&(PVOID&)originalD3D9BeginScene, hkD3D9BeginScene);

	originalD3D9EndScene = (D3D9EndScene_t)(d3d9VTable[42]);
	AttachFunc(&(PVOID&)originalD3D9EndScene, hkD3D9EndScene);

	originalD3D9DrawIndexedPrimitive = (D3D9DrawIndexedPrimitive_t)(d3d9VTable[82]);
	AttachFunc(&(PVOID&)originalD3D9DrawIndexedPrimitive, hkD3D9DrawIndexedPrimitive);

	dummyD3D9Device->Release();
	pD3D->Release();
}

void hook::shutdown() {
	DetachFunc(&(PVOID&)originalD3D9EndScene, hkD3D9EndScene);
	DetachFunc(&(PVOID&)originalD3D9BeginScene, hkD3D9BeginScene);
	DetachFunc(&(PVOID&)originalD3D9DrawIndexedPrimitive, hkD3D9DrawIndexedPrimitive);
}