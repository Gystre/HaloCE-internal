#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef HRESULT(__stdcall* D3D9BeginScene_t)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9EndScene_t)(IDirect3DDevice9* pDevice);
typedef HRESULT(__stdcall* D3D9DrawIndexedPrimitive_t)(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE primType, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount);

HRESULT __stdcall hkD3D9EndScene(IDirect3DDevice9* pDevice);
HRESULT __stdcall hkD3D9BeginScene(IDirect3DDevice9* pDevice);
HRESULT __stdcall hkD3D9DrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE primType, INT baseVertexIndex, UINT minVertexIndex, UINT numVertices, UINT startIndex, UINT primCount);


namespace hook {
	void init();
	void shutdown();
}