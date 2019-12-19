#include "pch.h"
#include "drawing.h"
#include "variables.h"

//would use gdi+ but couldn't get it work so here we are with gdi >:(
//might be because i got HDC wrong, now that i think about it...

namespace drawing {
	HDC HDC_Desktop;
	HBRUSH enemy_brush; //Brush to paint ESP etc
	HFONT Font;

	void init() {
		HDC_Desktop = GetDC(globals::engine->get_wnd_handle());
		enemy_brush = CreateSolidBrush(RGB(255, 0, 0));
	}

	void drawFilledRect(int x, int y, int w, int h)
	{
		RECT rect = { x, y, x + w, y + h };
		FillRect(HDC_Desktop, &rect, enemy_brush);
	}

	void drawBorderBox(int x, int y, int w, int h, int thickness)
	{
		drawFilledRect(x, y, w, thickness); //Top horiz line
		drawFilledRect(x, y, thickness, h); //Left vertical line
		drawFilledRect((x + w), y, thickness, h); //right vertical line
		drawFilledRect(x, y + h, w + thickness, thickness); //bottom horiz line
	}

	void drawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Pen)
	{
		int a, b = 0;
		HPEN hOPen;
		HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);// penstyle, width, color
		hOPen = (HPEN)SelectObject(HDC_Desktop, hNPen);
		MoveToEx(HDC_Desktop, StartX, StartY, NULL); //start
		a = LineTo(HDC_Desktop, EndX, EndY); //end
		DeleteObject(SelectObject(HDC_Desktop, hOPen));
	}

	void drawString(int x, int y, COLORREF color, const char* text)
	{
		SetTextAlign(HDC_Desktop, TA_CENTER | TA_NOUPDATECP);
		SetBkColor(HDC_Desktop, RGB(0, 0, 0));
		SetBkMode(HDC_Desktop, TRANSPARENT);
		SetTextColor(HDC_Desktop, color);
		SelectObject(HDC_Desktop, Font);
		TextOutA(HDC_Desktop, x, y, text, strlen(text));
		DeleteObject(Font);
	}
}
