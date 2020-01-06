#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace drawing {
	void init(IDirect3DDevice9* pDevice);
	void shutdown();

	void drawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, float width, D3DCOLOR color);
	void drawRectangle(D3DXVECTOR2 pos, float w, int h, D3DCOLOR color);
	void drawRegularPolygon(D3DXVECTOR2 pos, int Sides, float Radius, float DRotationOffset, D3DCOLOR color);
	void drawString(float x, float y, D3DCOLOR color, const char* fmt, ...);
}