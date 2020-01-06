#include "pch.h"

#include "hook.h"
#include "constants.h"
#include "variables.h"
#include "aimbot.h"
#include "esp.h"
#include "menu.h"
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

HRESULT __stdcall hkD3D9DrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE primType, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount) {
	pse.doChams(pDevice, primType, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
	
	return originalD3D9DrawIndexedPrimitive(pDevice, primType, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
}

HRESULT __stdcall hkD3D9BeginScene(IDirect3DDevice9* pDevice) {
	static bool runOnce = true;
	if (runOnce) {
		runOnce = false;
		//pse.createTexture(pDevice, (LPCVOID)&bRed, sizeof(bRed), &pse.texRed);
		drawing::init(pDevice);
	}
	return originalD3D9BeginScene(pDevice);
}


HRESULT __stdcall hkD3D9EndScene(IDirect3DDevice9* pDevice) {
	engine_snapshot snapshot;
	globals::engine->get_snapshot(snapshot);
	snapshot.filter_enemies();
	GameObject* local_player = snapshot.get_player(); //might be a little faster to define local variable at top???

	if (!local_player) return originalD3D9EndScene(pDevice);

	if (settings::aim_fov_enabled) {
		drawing::drawRegularPolygon(D3DXVECTOR2(globals::engine->get_width() / 2, globals::engine->get_height() / 2), 300, settings::aim_fov_size, 30, D3DCOLOR_XRGB(255, 0, 0));
	}

	if (settings::lock_health) {
		local_player->health = 1000;
	}

	if (settings::lock_shield) {
		local_player->shield = 1000;
	}

	if (settings::lock_frag_grenades) {
		local_player->frag_grenades = 4;
	}

	if (settings::lock_plasma_grenades) {
		local_player->plasma_grenades = 4;
	}

	if (settings::aim_enabled) {
		botaim.update(snapshot);
	}

	if (settings::esp_enabled) {
		pse.update(snapshot, local_player);
	}

	if (GetAsyncKeyState(VK_F1)) {
		for (GameObject* entity : snapshot.gameObjects) {
			entity->position = local_player->position;
		}
	}

	if (settings::speed && GetAsyncKeyState(VK_F2) ) {
		vec3_t look = *reinterpret_cast<vec3_t*>(addr::CAMERA_LOOK_VECTOR);
		local_player->position += look * settings::how_fast;
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

	//no idea why this not working, not getting any error messages
	//originalD3D9DrawIndexedPrimitive = (D3D9DrawIndexedPrimitive_t)(d3d9VTable[82]);
	//AttachFunc(&(PVOID&)originalD3D9DrawIndexedPrimitive, hkD3D9DrawIndexedPrimitive);

	dummyD3D9Device->Release();
	pD3D->Release();
}

void hook::shutdown() {
	hack_menu.shutdown();
	DetachFunc(&(PVOID&)originalD3D9EndScene, hkD3D9EndScene);
	DetachFunc(&(PVOID&)originalD3D9BeginScene, hkD3D9BeginScene);
	//DetachFunc(&(PVOID&)originalD3D9DrawIndexedPrimitive, hkD3D9DrawIndexedPrimitive);
}