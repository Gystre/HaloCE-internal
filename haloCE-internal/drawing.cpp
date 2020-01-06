#include "pch.h"
#include "drawing.h"
#include "math.h"

//dont know if it better to use floats or D3DXVECTOR2 for parameters...
//example call:
//drawing::drawString(100, 100, D3DCOLOR_ARGB(255, 255, 0, 0), "wow!");

namespace drawing {
	LPD3DXFONT pFont = NULL;
	LPD3DXLINE pLine = NULL;

	void init(IDirect3DDevice9* pDevice) {
		D3DXCreateFont(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		D3DXCreateLine(pDevice, &pLine);
	}

	void shutdown() {
		pFont->Release();
		pLine->Release();
	}

	void drawLine(D3DXVECTOR2 start, D3DXVECTOR2 end, float width, D3DCOLOR color) {
		D3DXVECTOR2 vLine[2];

		vLine[0].x = start.x;
		vLine[0].y = start.y;
		vLine[1].x = end.x;
		vLine[1].y = end.y;

		pLine->SetWidth(width);
		pLine->SetAntialias(true);
		pLine->SetGLLines(false);
		pLine->Begin();
		pLine->Draw(vLine, 2, color);
		pLine->End();
	}

	void drawRectangle(D3DXVECTOR2 pos, float w, int h, D3DCOLOR color) {
		D3DXVECTOR2 vLine1[2];
		D3DXVECTOR2 vLine2[2];
		D3DXVECTOR2 vLine3[2];
		D3DXVECTOR2 vLine4[2];

		vLine1[0].x = pos.x;
		vLine1[0].y = pos.y;
		vLine1[1].x = pos.x;
		vLine1[1].y = pos.y + h;

		vLine2[0].x = pos.x + w;
		vLine2[0].y = pos.y;
		vLine2[1].x = pos.x + w;
		vLine2[1].y = pos.y + h;

		vLine3[0].x = pos.x;
		vLine3[0].y = pos.y;
		vLine3[1].x = pos.x + w;
		vLine3[1].y = pos.y;

		vLine4[0].x = pos.x;;
		vLine4[0].y = pos.y + h;
		vLine4[1].x = pos.x + w;
		vLine4[1].y = pos.y + h;

		pLine->SetWidth(2);
		pLine->SetAntialias(false);
		pLine->SetGLLines(false);
		pLine->Begin();
		pLine->Draw(vLine1, 2, color);
		pLine->Draw(vLine2, 2, color);
		pLine->Draw(vLine3, 2, color);
		pLine->Draw(vLine4, 2, color);
		pLine->End();
	}

	//300 sides for circle
	void drawRegularPolygon(D3DXVECTOR2 pos, int Sides, float Radius, float DRotationOffset, D3DCOLOR color) {
		D3DXVECTOR2* vLine = new D3DXVECTOR2[Sides + 1];
		float Theta;
		float WedgeAngle;
		//Precompute WedgeAngle
		WedgeAngle = (float)((2 * M_PI) / Sides);
		for (int i = 0; i <= Sides; i++)
		{
			Theta = i * WedgeAngle + (DRotationOffset / 57.29578);
			vLine[i].x = (pos.x + Radius * cos(Theta));
			vLine[i].y = (pos.y - Radius * sin(Theta));
		}
		pLine->SetWidth(2);
		pLine->SetAntialias(false);
		pLine->SetGLLines(false);
		pLine->Begin();
		pLine->Draw(vLine, (Sides + 1), color);
		pLine->End();
	}

	void drawString(float x, float y, D3DCOLOR color, const char* fmt, ...) {
		RECT FontPos = { x, y, x + 120, y + 16 };
		char buf[1024] = { '\0' };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
	}
}
