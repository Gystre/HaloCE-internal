#pragma once

namespace drawing {
	void init();
	void drawFilledRect(int x, int y, int w, int h);
	void drawBorderBox(int x, int y, int w, int h, int thickness);
	void drawLine(float StartX, float StartY, float EndX, float EndY, COLORREF Pen);
	void drawString(int x, int y, COLORREF color, const char* text);
}